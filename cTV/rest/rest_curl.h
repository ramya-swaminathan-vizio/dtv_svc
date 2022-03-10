/* dolphin 20200323 add  this for use curl API */
#ifndef _REST_CURL_H
#define _REST_CURL_H

#define MAX_BUFFER_SIZE 4096
#define MAX_HEADER_NUM 12

#if 1 //variable size for multi-download

typedef struct _MemoryStruct
{		
    char *memory;		
    size_t size; 
}MemoryStruct;

#else

typedef struct _MemoryStruct
{
    char memory[MAX_BUFFER_SIZE]; //data
    size_t size; //data size
}MemoryStruct;

#endif

typedef struct _HeaderList
{
    char* header[MAX_HEADER_NUM];
    int num; //header number
}HeaderList;

// remove APIs: they are not used and have to be re-written bcz the MemoryStruct is changed.
#if 0 
int rest_http_post_req(char *p_url,HeaderList t_list ,char* p_sndbuf,MemoryStruct *t_revbuf);
int rest_http_get_req(char *p_url,HeaderList t_list ,MemoryStruct *t_revbuf);
int rest_https_post_req(char *p_url,HeaderList t_list ,char* p_sndbuf,MemoryStruct *t_revbuf);
#endif
int rest_https_get_req(char *p_url,HeaderList t_list ,MemoryStruct *t_revbuf);

#endif //_REST_CURL_H

