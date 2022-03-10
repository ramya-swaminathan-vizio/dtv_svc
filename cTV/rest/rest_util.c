#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "u_common.h"
#include "c_os.h"
#include "c_dbg.h"

#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <openssl/x509_vfy.h>
#include <sys/statfs.h>

extern char * bcrypt(const char *pass, const char *salt);

static UCHAR * read_file_to_buffer(const CHAR * path, UINT32 * ui4_length) {

    UCHAR * ps_file_buf = NULL;
    FILE * pf_file = NULL;
    UINT32 ui4_file_size = 0;
    size_t t_read_result;

    if(ui4_length) {
        *ui4_length = 0;
    }

    pf_file = fopen(path, "rb");
    if( pf_file == NULL ) {
        return NULL;
    }
    fseek(pf_file, 0, SEEK_END);
    ui4_file_size = ftell(pf_file);
    rewind(pf_file);
    if( ui4_file_size == 0 ) {
        fclose(pf_file);
        return NULL;
    }
    ps_file_buf = (UCHAR*)c_mem_alloc(sizeof(CHAR) * ui4_file_size);
    if( ps_file_buf == NULL ){
        fclose(pf_file);
        return NULL;
    }
    t_read_result = fread(ps_file_buf, 1, ui4_file_size, pf_file);
    fclose(pf_file);
    if( t_read_result != ui4_file_size ) {
        c_mem_free(ps_file_buf);
        ps_file_buf = NULL;
    }

    if(ui4_length) {
        *ui4_length = ui4_file_size;
    }

    return ps_file_buf;

}

static INT32 write_buffer_to_file(const CHAR * path, VOID * buffer, UINT32 ui4_length) {

    FILE * pf_file = NULL;
    size_t t_write_result = 0;

    pf_file = fopen(path, "wb");
    if( pf_file == NULL ) {
        return 1;
    }

    t_write_result = fwrite(buffer, 1, ui4_length, pf_file);
    if(t_write_result != ui4_length) {
        fclose(pf_file);
        return 2;
    }

    fclose(pf_file);
    return 0;

}

static VOID SHA256_digest(const UCHAR * message, size_t message_len, UCHAR * digest) {

    EVP_MD_CTX mdctx;
    unsigned int digest_len;

    EVP_MD_CTX_init(&mdctx);

    EVP_DigestInit_ex(&mdctx, EVP_sha256(), NULL);
    EVP_DigestUpdate(&mdctx, message, message_len);
    EVP_DigestFinal_ex(&mdctx, digest, &digest_len);

    EVP_MD_CTX_cleanup(&mdctx);

}

static INT32 RSAVerifySignature(RSA* rsa, const UCHAR* MsgHash, size_t MsgHashLen, const UCHAR* Msg, size_t MsgLen, INT32* Authentic) {

    EVP_PKEY* pubKey  = EVP_PKEY_new();
    EVP_PKEY_assign_RSA(pubKey, rsa);
    EVP_MD_CTX* m_RSAVerifyCtx = EVP_MD_CTX_create();

    *Authentic = 0;

    if (EVP_DigestVerifyInit(m_RSAVerifyCtx, NULL, EVP_sha256(), NULL, pubKey)<=0) {
        return 0;
    }

    if (EVP_DigestVerifyUpdate(m_RSAVerifyCtx, Msg, MsgLen) <= 0) {
        return 0;
    }

    int AuthStatus = EVP_DigestVerifyFinal(m_RSAVerifyCtx, MsgHash, MsgHashLen);
    if (AuthStatus==1) {
        *Authentic = 1;
        EVP_MD_CTX_cleanup(m_RSAVerifyCtx);
        return 1;
    } else if(AuthStatus==0){
        *Authentic = 0;
        EVP_MD_CTX_cleanup(m_RSAVerifyCtx);
        return 1;
    } else{
        *Authentic = 0;
        EVP_MD_CTX_cleanup(m_RSAVerifyCtx);
        return 0;
    }

}

static INT32 AESCBCdecrypt(const UCHAR * key, const UCHAR *iv, const UCHAR *ciphertext, INT32 ciphertext_len, UCHAR * plaintext, UINT32 * plaintext_len) {

    EVP_CIPHER_CTX *ctx;
    INT32 i4_len;

    if(ciphertext_len < 16) {
        return 1;
    }

    if(*plaintext_len != ciphertext_len) {
        return 1;
    }

    memset(plaintext, 0, *plaintext_len);

    if(!(ctx = EVP_CIPHER_CTX_new())) {
        return 1;
    }

    if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv)) {
        EVP_CIPHER_CTX_free(ctx);
        return 1;
    }

    EVP_CIPHER_CTX_set_key_length(ctx, EVP_MAX_KEY_LENGTH);

    if(1 != EVP_DecryptUpdate(ctx, plaintext, &i4_len, ciphertext, ciphertext_len)) {
        EVP_CIPHER_CTX_free(ctx);
        return 1;
    }
    *plaintext_len = i4_len;

    if(1 != EVP_DecryptFinal_ex(ctx, plaintext + i4_len, &i4_len)) {
        EVP_CIPHER_CTX_free(ctx);
        return 1;
    }
    *plaintext_len += i4_len;

    EVP_CIPHER_CTX_free(ctx);

    return 0;

}

static CHAR * remove_prefix(CHAR * str, const CHAR * prefix) {

    if(c_strstr(str, prefix) == str) {
        return str + c_strlen(prefix);
    } else {
        return str;
    }

}

INT32 rest_decrypt_localassets(const CHAR * ps_x509_pub_path, const CHAR * ps_enc_sig_file_path, const CHAR * ps_output_file_path) {

    UCHAR * ps_x509_pub_buf = NULL;
    UCHAR * ps_enc_sig_file_buf = NULL;
    UCHAR * ps_output_file_buf = NULL;
    UCHAR a_iv_key[SHA256_DIGEST_LENGTH];
    UCHAR a_temphash[SHA256_DIGEST_LENGTH];
    UINT32 ui4_x509_pub_file_size = 0;
    UINT32 ui4_enc_sig_file_size = 0;
    UINT32 ui4_output_file_size = 0;
    INT32 authentic, result;

    /* Read x509 public key file to buffer */
    ps_x509_pub_buf = read_file_to_buffer(ps_x509_pub_path, &ui4_x509_pub_file_size);
    if( ps_x509_pub_buf == NULL ) {
        return 1;
    }

    /* Check ui4_x509_pub_file_size and content of file */
    if( ui4_x509_pub_file_size < 451 || c_strstr((const CHAR *)ps_x509_pub_buf, "-----BEGIN PUBLIC KEY-----") == NULL || c_strstr((const CHAR *)ps_x509_pub_buf, "-----END PUBLIC KEY-----") == NULL ) {
        c_mem_free(ps_x509_pub_buf);
        return 2;
    }

    /* Generate iv & key via SHA-256 processing */
    SHA256_digest((const UCHAR *)ps_x509_pub_buf, ui4_x509_pub_file_size, a_iv_key);

    /* Read enc_sig file to buffer */
    ps_enc_sig_file_buf = read_file_to_buffer(ps_enc_sig_file_path, &ui4_enc_sig_file_size);
    if( ps_enc_sig_file_buf == NULL ) {
        c_mem_free(ps_x509_pub_buf);
        return 3;
    }

    /* Check ui4_enc_sig_file_size */
    //printf("<rest> [rest_decrypt_localassets] ui4_enc_sig_file_size = %d\n\r", ui4_enc_sig_file_size);
    //if( ui4_enc_sig_file_size < 16 + 256 || (ui4_enc_sig_file_size % 16) != 0 ) {
    if (ui4_enc_sig_file_size < 16 + 256) {
        c_mem_free(ps_x509_pub_buf);
        c_mem_free(ps_enc_sig_file_buf);
        return 4;
    }

    /* Calculate temphash */
    SHA256_digest((const UCHAR *)ps_enc_sig_file_buf, ui4_enc_sig_file_size - 256, a_temphash);

    /* Verify */
    RSA * publicRSA = NULL;
    BIO * keybio;
    keybio = BIO_new_mem_buf((void*)ps_x509_pub_buf, -1);
    if( keybio == NULL ) {
        c_mem_free(ps_x509_pub_buf);
        c_mem_free(ps_enc_sig_file_buf);
        return 5;
    }
    publicRSA = PEM_read_bio_RSA_PUBKEY(keybio, &publicRSA, NULL, NULL);
    result = RSAVerifySignature(publicRSA, (const UCHAR *)ps_enc_sig_file_buf + ui4_enc_sig_file_size - 256, 256, a_temphash, SHA256_DIGEST_LENGTH, &authentic);
    if( (result & authentic) == 0 ) {
        c_mem_free(ps_x509_pub_buf);
        c_mem_free(ps_enc_sig_file_buf);
        return 6;
    }

    /* Decrypt */
    ps_output_file_buf = (UCHAR*)c_mem_alloc(sizeof(CHAR) * (ui4_enc_sig_file_size - 256));
    if( ps_output_file_buf == NULL ){
        c_mem_free(ps_x509_pub_buf);
        c_mem_free(ps_enc_sig_file_buf);
        return 7;
    }
    ui4_output_file_size = ui4_enc_sig_file_size - 256;
    result = AESCBCdecrypt(a_iv_key+16, a_iv_key, ps_enc_sig_file_buf, ui4_enc_sig_file_size - 256, ps_output_file_buf, &ui4_output_file_size);
    if( result != 0 ) {
        c_mem_free(ps_x509_pub_buf);
        c_mem_free(ps_enc_sig_file_buf);
        c_mem_free(ps_output_file_buf);
        return 8;
    }

    /* Output file */
    result = write_buffer_to_file(ps_output_file_path, ps_output_file_buf, ui4_output_file_size);
    if( result != 0 ) {
        c_mem_free(ps_x509_pub_buf);
        c_mem_free(ps_enc_sig_file_buf);
        c_mem_free(ps_output_file_buf);
        return 9;
    }

    /* Final */
    c_mem_free(ps_x509_pub_buf);
    c_mem_free(ps_enc_sig_file_buf);
    c_mem_free(ps_output_file_buf);

    return 0;

}

INT32 rest_decompress_localassets(const CHAR * ps_in_path, const CHAR * ps_out_path) {

    CHAR cmd_buf[256];
    INT32 ret;

    snprintf(cmd_buf, sizeof(cmd_buf), "mkdir -p %s", ps_out_path);
    system(cmd_buf);

    snprintf(cmd_buf, sizeof(cmd_buf), "miniunz -o %s -d %s", ps_in_path, ps_out_path);
    ret = system(cmd_buf);

    if(ret) {
        return 1;
    } else {
        return 0;
    }

}

CHAR * rest_security_hash_token(const CHAR * token) {

    const char * SALT = "$2a$04$ObVgwZF1d0Eg20eXFYl8pe";

    return remove_prefix(bcrypt(token, SALT), SALT);

}

static void printsize(long long n)
{
    char unit = 'K';
    n /= 1024;
    if (n > 1024) {
        n /= 1024;
        unit = 'M';
    }
    if (n > 1024) {
        n /= 1024;
        unit = 'G';
    }
    DBG_INFO(("%4lld%c \n", n, unit));
}

INT32 rest_check_block_size(const CHAR * ps_block)
{
    struct statfs st;
    long long free_size = 0;
    if (statfs(ps_block, &st) < 0) {
        DBG_INFO(("read block fail \n"));
    } else {
        DBG_INFO(("blocks size:"));
        printsize((long long)st.f_blocks * (long long)st.f_bsize);
        DBG_INFO(("block used size:"));
        printsize((long long)(st.f_blocks - (long long)st.f_bfree) * st.f_bsize);
        DBG_INFO(("block free size:"));
        printsize((long long)st.f_bfree * (long long)st.f_bsize);
        DBG_INFO(("bsize:%d\n", (int) st.f_bsize));
    }
    free_size = (long long)st.f_bfree * (long long)st.f_bsize;
    
    free_size /= 1024;
    if (free_size > 1024) {
        free_size /= 1024;
    }//Unit: M

    DBG_INFO(("free_size:%d\n", (INT32) free_size));
    return (INT32)free_size;
}

