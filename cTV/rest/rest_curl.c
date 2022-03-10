#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "rest_system.h"
#include "curl/curl.h"
#include "rest_curl.h"
#include "c_common.h"
#include "u_common.h"
#include "c_dbg.h"

//static MemoryStruct t_MemoryStruct;

#if 1 //variable size for multi-download

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) 
{		
    size_t	realsize = size * nmemb;		
    MemoryStruct *mem = (MemoryStruct *)userp;
    mem->memory	= realloc(mem->memory, mem->size + realsize	+ 1);
    //char *ptr = realloc(mem->memory, mem->size + realsize + 1);

    if(mem->memory == NULL) {
        /* out of memory! */ 
        S_DBG_E("\n\n\nnot enough memory (realloc returned NULL)\n\n\n");
        return 0;
    }

    S_DBG_I("WriteMemoryCallback ptr realloc ok!!");
    //mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents,	realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    
    int i=0;
    S_DBG_I("\ncontents:");
    for(i=0;i<realsize;i++)
    {
        S_DBG_I("%c",mem->memory[i]);
    }
    S_DBG_I("\n");
    
    return realsize;
}
#else

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) 
{		
    size_t	realsize =	size * nmemb;		
    MemoryStruct *mem = (MemoryStruct *)userp;

    memcpy(mem->memory, contents,	realsize);		
    mem->size = realsize;	
    mem->memory[realsize] = 0;

    S_DBG_I("%s",mem->memory);

    return realsize; 
}

#endif

// remove APIs: they are not used and have to be re-written bcz the MemoryStruct is changed.
#if 0
/* int rest_http_post_req(char *p_url, HeaderList t_list ,char* p_sndbuf, MemoryStruct *t_revbuf)
*   Description:
*     Send a POST request with http header ,timeout 2s
*   Input:
*     p_url: the url to send request
*     t_list:  the header list, if empty you should set HeaderList->num = 0
*     p_sndbuf: sending buffer
*     t_revbuf: receive buffer
*   Return:
*     0: succeed
*     1: send failed
*     2: create request failed
*   Author:
*     dolphin / haoyuan.li@mediatek.com
*   Date:
*     2020/03/23
*/
int rest_http_post_req(char *p_url, HeaderList t_list ,char* p_sndbuf, MemoryStruct *t_revbuf)
{
    int ret = 0; 
    int i=0;
    int info = 0;
    CURL *curl;
    CURLcode res;
    struct curl_slist *headers=NULL; 

    MemoryStruct chunk;
    memset(chunk.memory,0x0,MAX_BUFFER_SIZE);
    chunk.size = 0;

    curl = curl_easy_init();
    if (curl)
    {
        if(t_list.num>0)
        {
            for(i=0;i<t_list.num;i++)
            {
                headers = curl_slist_append(headers,t_list.header[i]);
            }
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        }
        curl_easy_setopt(curl, CURLOPT_URL, p_url);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 2L);  //timeout 2s
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA,	(void *)&chunk);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS,p_sndbuf); //send buff
        curl_easy_setopt(curl, CURLOPT_POST, 1L); 
        curl_easy_setopt(curl, CURLOPT_VERBOSE,1L);
        
        res = curl_easy_perform(curl);  //send
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE  , &info);
        if(res != CURLE_OK || info != 200)
        {
            ret = 1;
            S_DBG_E("curl failed to perform url='%s' res=[%d] rcode=%d\n",p_url, res,info);
        }
        else
        {
            memcpy(t_revbuf->memory,chunk.memory,chunk.size);
            t_revbuf->size = chunk.size;
            t_revbuf->memory[t_revbuf->size] = '\0';
            S_DBG_I("[%s, %d]%d bytes received, message [%s]\n", __FUNCTION__, __LINE__, t_revbuf->size ,t_revbuf->memory);
        }
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
    else
    {
        ret = 2;
    }

    return ret;
}

/* int rest_http_get_req(char *p_url,struct HeaderList t_list ,struct MemoryStruct *t_revbuf)
*   Description:
*     Send a GET request with http header ,timeout 2s
*   Input:
*     p_url: the url to send request
*     t_list:  the header list, if empty you should set HeaderList->num = 0
*     t_revbuf: receive buffer
*   Return:
*     0: succeed
*     1: send failed
*     2: create request failed
*   Author:
*     dolphin / haoyuan.li@mediatek.com
*   Date:
*     2020/03/23
*/
int rest_http_get_req(char *p_url, HeaderList t_list ,MemoryStruct *t_revbuf)
{
    int ret = 0; 
    int i=0;
    int info = 0;
    CURL *curl;
    CURLcode res;
    struct curl_slist *headers=NULL; 

    MemoryStruct chunk;
    memset(chunk.memory,0x0,MAX_BUFFER_SIZE);
    chunk.size = 0;
    
    curl = curl_easy_init();
    if (curl)
    {
        if(t_list.num>0)
        {
            for(i=0;i<t_list.num;i++)
            {
                headers = curl_slist_append(headers,t_list.header[i]);
            }
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        }
        curl_easy_setopt(curl, CURLOPT_URL, p_url);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 2L);  //timeout 2s
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA,	(void *)&chunk);
        //curl_easy_setopt(curl, CURLOPT_POST, 1L);   //not set means default is GET
        curl_easy_setopt(curl, CURLOPT_VERBOSE,1L);
        
        res = curl_easy_perform(curl);  //send
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE  , &info);
        if(res != CURLE_OK || info != 200)
        {
            ret = 1;
            S_DBG_E("curl failed to perform url='%s' res=[%d] rcode=%d\n",p_url, res,info);
        }
        else
        {
            memcpy(t_revbuf->memory,chunk.memory,chunk.size);
            t_revbuf->size = chunk.size;
            t_revbuf->memory[t_revbuf->size] = '\0';
            printf("[%s, %d]%d	bytes received ,message [%s]\n", __FUNCTION__, __LINE__, t_revbuf->size ,t_revbuf->memory);
        }
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
    else
    {
        ret = 2;
    }
    return ret;
}


/* int rest_https_post_req(char *p_url, HeaderList t_list ,char* p_sndbuf, MemoryStruct *t_revbuf)
*   Description:
*     Send a POST request with https header ,timeout 2s ,skip SSL verify
*   Input:
*     p_url: the url to send request
*     t_list:  the header list, if empty you should set HeaderList->num = 0
*     p_sndbuf: sending buffer
*     t_revbuf: receive buffer
*   Return:
*     0: succeed
*     1: send failed
*     2: create request failed
*   Author:
*     dolphin / haoyuan.li@mediatek.com
*   Date:
*     2020/03/23
*/
int rest_https_post_req(char *p_url, HeaderList t_list ,char* p_sndbuf, MemoryStruct *t_revbuf)
{
    int ret = 0; 
    int i=0;
    int info = 0;
    CURL *curl;
    CURLcode res;
    struct curl_slist *headers=NULL; 

    MemoryStruct chunk;
    memset(chunk.memory,0x0,MAX_BUFFER_SIZE);
    chunk.size = 0;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl)
    {
        if(t_list.num>0)
        {
            for(i=0;i<t_list.num;i++)
            {
                headers = curl_slist_append(headers,t_list.header[i]);
            }
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        }
        curl_easy_setopt(curl, CURLOPT_URL, p_url);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 2L);  //timeout 2s
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA,	(void *)&chunk);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS,p_sndbuf); //send buff
        curl_easy_setopt(curl, CURLOPT_POST, 1L); 
        curl_easy_setopt(curl, CURLOPT_VERBOSE,1L);

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);  //skip https verify
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        res = curl_easy_perform(curl);  //send
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE  , &info);
        if(res != CURLE_OK || info != 200)
        {
            ret = 1;
            printf("curl failed to perform url='%s' res=[%d] rcode=%d\n",p_url, res,info);
        }
        else
        {
            memcpy(t_revbuf->memory,chunk.memory,chunk.size);
            t_revbuf->size = chunk.size;
            t_revbuf->memory[t_revbuf->size] = '\0';
            printf("[%s, %d]%d	bytes received ,message [%s]\n", __FUNCTION__, __LINE__, t_revbuf->size ,t_revbuf->memory);
        }
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
    else
    {
        ret = 2;
    }

    curl_global_cleanup();
    return ret;
}

#endif

/* int rest_https_get_req(char *p_url, HeaderList t_list , MemoryStruct *t_revbuf)
*   Description:
*     Send a GET request with https header ,timeout 2s ,skip SSL verify
*   Input:
*     p_url: the url to send request
*     t_list:  the header list, if empty you should set HeaderList->num = 0
*     t_revbuf: receive buffer
*   Return:
*     0: succeed
*     1: send failed
*     2: create request failed
*   Author:
*     dolphin / haoyuan.li@mediatek.com
*   Date:
*     2020/03/23
*/
int rest_curl_https_get_req(char *p_url, HeaderList t_list , MemoryStruct *tmp_revbuf)
{
    int ret = 0; 
    int i=0;
    int info = 0;
    CURL *curl;
    CURLcode res;
    struct curl_slist *headers=NULL; 

    tmp_revbuf->memory = malloc(1);  /* will be grown as needed by the realloc above */ 
    tmp_revbuf->size = 0;    /* no data at this point */     

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl)
    {
        if(t_list.num>0)
        {
            for(i=0;i<t_list.num;i++)
            {
                headers = curl_slist_append(headers,t_list.header[i]);
            }
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        }
        curl_easy_setopt(curl, CURLOPT_URL, p_url);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 4L);  //timeout 2s change to 4s,due to http request always timeout
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)tmp_revbuf);
        //curl_easy_setopt(curl, CURLOPT_POST, 1L);   //no set means get request
        curl_easy_setopt(curl, CURLOPT_VERBOSE,1L);

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);  //skip https verify
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        res = curl_easy_perform(curl);  //send
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE  , &info);
        if(res != CURLE_OK || info != 200)
        {
            ret = 1;
            S_DBG_E("curl failed to perform url='%s' res=[%d] rcode=%d\n",p_url, res,info);
        }
        else
        {
            S_DBG_I("[%s, %d] curl gets memory %s, size_t %d\n", __FUNCTION__, __LINE__, tmp_revbuf->memory, (int)tmp_revbuf->size);
        }
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
    else
    {
        ret = 2;
        S_DBG_E("[%s, %d] Error, curl returns ret = %d\n", __FUNCTION__, __LINE__, ret);
    }

    curl_global_cleanup();
    return ret;
}

int rest_https_get_req(char *p_url, HeaderList t_list , MemoryStruct *t_revbuf)
{
    int ret = 0;

    ret = rest_curl_https_get_req(p_url, t_list, t_revbuf);
    if (ret == 0)
    {
        S_DBG_I("[%s, %d]address of t_revbuf is %p, %d bytes received, message [%s]\n", __FUNCTION__, __LINE__, t_revbuf, t_revbuf->size ,t_revbuf->memory);
    }
    else
    {
        S_DBG_E("[%s, %d]Error, curl returns ret = %d\n", __FUNCTION__, __LINE__, ret);
    }

    return ret;
}
