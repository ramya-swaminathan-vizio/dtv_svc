#ifndef REST_UTIL_H
#define REST_UTIL_H

INT32 rest_decrypt_localassets(const CHAR * ps_x509_pub_path, const CHAR * ps_enc_sig_file_path, const CHAR * ps_output_file_path);
INT32 rest_decompress_localassets(const CHAR * ps_in_path, const CHAR * ps_out_path);
CHAR * rest_security_hash_token(const CHAR * token);
INT32 rest_check_block_size(const CHAR * ps_block);

#endif
