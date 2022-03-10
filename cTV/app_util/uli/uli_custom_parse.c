/*----------------------------------------------------------------------------*
 * Copyright Statement:                                                       *
 *                                                                            *
 *   This software/firmware and related documentation ("MediaTek Software")   *
 * are protected under international and related jurisdictions'copyright laws *
 * as unpublished works. The information contained herein is confidential and *
 * proprietary to MediaTek Inc. Without the prior written permission of       *
 * MediaTek Inc., any reproduction, modification, use or disclosure of        *
 * MediaTek Software, and information contained herein, in whole or in part,  *
 * shall be strictly prohibited.                                              *
 * MediaTek Inc. Copyright (C) 2010. All rights reserved.                     *
 *                                                                            *
 *   BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND     *
 * AGREES TO THE FOLLOWING:                                                   *
 *                                                                            *
 *   1)Any and all intellectual property rights (including without            *
 * limitation, patent, copyright, and trade secrets) in and to this           *
 * Software/firmware and related documentation ("MediaTek Software") shall    *
 * remain the exclusive property of MediaTek Inc. Any and all intellectual    *
 * property rights (including without limitation, patent, copyright, and      *
 * trade secrets) in and to any modifications and derivatives to MediaTek     *
 * Software, whoever made, shall also remain the exclusive property of        *
 * MediaTek Inc.  Nothing herein shall be construed as any transfer of any    *
 * title to any intellectual property right in MediaTek Software to Receiver. *
 *                                                                            *
 *   2)This MediaTek Software Receiver received from MediaTek Inc. and/or its *
 * representatives is provided to Receiver on an "AS IS" basis only.          *
 * MediaTek Inc. expressly disclaims all warranties, expressed or implied,    *
 * including but not limited to any implied warranties of merchantability,    *
 * non-infringement and fitness for a particular purpose and any warranties   *
 * arising out of course of performance, course of dealing or usage of trade. *
 * MediaTek Inc. does not provide any warranty whatsoever with respect to the *
 * software of any third party which may be used by, incorporated in, or      *
 * supplied with the MediaTek Software, and Receiver agrees to look only to   *
 * such third parties for any warranty claim relating thereto.  Receiver      *
 * expressly acknowledges that it is Receiver's sole responsibility to obtain *
 * from any third party all proper licenses contained in or delivered with    *
 * MediaTek Software.  MediaTek is not responsible for any MediaTek Software  *
 * releases made to Receiver's specifications or to conform to a particular   *
 * standard or open forum.                                                    *
 *                                                                            *
 *   3)Receiver further acknowledge that Receiver may, either presently       *
 * and/or in the future, instruct MediaTek Inc. to assist it in the           *
 * development and the implementation, in accordance with Receiver's designs, *
 * of certain softwares relating to Receiver's product(s) (the "Services").   *
 * Except as may be otherwise agreed to in writing, no warranties of any      *
 * kind, whether express or implied, are given by MediaTek Inc. with respect  *
 * to the Services provided, and the Services are provided on an "AS IS"      *
 * basis. Receiver further acknowledges that the Services may contain errors  *
 * that testing is important and it is solely responsible for fully testing   *
 * the Services and/or derivatives thereof before they are used, sublicensed  *
 * or distributed. Should there be any third party action brought against     *
 * MediaTek Inc. arising out of or relating to the Services, Receiver agree   *
 * to fully indemnify and hold MediaTek Inc. harmless.  If the parties        *
 * mutually agree to enter into or continue a business relationship or other  *
 * arrangement, the terms and conditions set forth herein shall remain        *
 * effective and, unless explicitly stated otherwise, shall prevail in the    *
 * event of a conflict in the terms in any agreements entered into between    *
 * the parties.                                                               *
 *                                                                             *
 *   4)Receiver's sole and exclusive remedy and MediaTek Inc.'s entire and    *
 * cumulative liability with respect to MediaTek Software released hereunder  *
 * will be, at MediaTek Inc.'s sole discretion, to replace or revise the      *
 * MediaTek Software at issue.                                                *
 *                                                                            *
 *   5)The transaction contemplated hereunder shall be construed in           *
 * accordance with the laws of Singapore, excluding its conflict of laws      *
 * principles.  Any disputes, controversies or claims arising thereof and     *
 * related thereto shall be settled via arbitration in Singapore, under the   *
 * then current rules of the International Chamber of Commerce (ICC).  The    *
 * arbitration shall be conducted in English. The awards of the arbitration   *
 * shall be final and binding upon both parties and shall be entered and      *
 * enforceable in any court of competent jurisdiction.                        *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * $RCSfile: uli_custom.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: Mark Chen $
 * $CCRevision: /main/DTV_X_ATSC/6 $
 * $SWAuthor: $
 * $MD5HEX: ecd1c8c573bd47ddeb3a3eefdacc447b $
 *
 * Description:
 *
 *
 *
 *---------------------------------------------------------------------------*/

 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <dirent.h>
#include <cJSON.h>
#include "u_common.h"
#include "u_dbg.h"


static CHAR* base64_chars ="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

 // Add these twp protos to your supervisor C code
 VOID base64_C_decode(const CHAR* inbuf, size_t inlen, UCHAR** extOutBuf, size_t *extOutLen);
 CHAR* json_C_getString(CHAR *jsonString, CHAR *key,CHAR* value);
 
 #define  maxInt  1024*2

 /*-----------------------------------------------------------------------------
					 uli function implement start
  ----------------------------------------------------------------------------*/
 static BOOL is_base64(UCHAR c)
 {
   return (isalnum(c) || (c == '+') || (c == '/'));
 }
 static INT32 stringtogetindex(UCHAR value)
 {
 	INT32 index = 0;
	for(index=0;*(base64_chars+index)!='\0';index++)
	{
		if(*(base64_chars+index) == value)
		{
			//DBG_LOG_PRINT(("stringtogetindex index:%d \n",index));
			return index;
		}
	}
	return -1;
 }
 void base64_decode(const CHAR* inbuf, size_t inlen, UCHAR* outbuf, size_t* outlen)
 {
   INT32			 i	 = 0;
   INT32			 j	 = 0;
   INT32			 in_ = 0;
  INT32 u4outlen = 0;
   UCHAR char_array_4[4], char_array_3[3];
   //DBG_LOG_PRINT(("base64_decode inbuf:%s inlen:%d \n",inbuf,inlen));
  UCHAR *outbuf_value = (UCHAR*)(c_mem_alloc((((inlen * 3) + 3) / 4) + 1));
   if (outbuf != NULL)
   {
     //DBG_LOG_PRINT(("base64_decode222 inbuf:%s inlen:%d  is_base64:%d value:%d\n",inbuf,inlen,is_base64(inbuf[in_]),inbuf[in_]));
	 while (inlen-- && (inbuf[in_] != '=') && is_base64(inbuf[in_]))
	 {
	  // DBG_LOG_PRINT(("inbuf[in_]:%d in_:%d \n",inbuf[in_],in_));
	   char_array_4[i++] = inbuf[in_];
	   in_++;
	   if (i == 4)
	   {
		 for (i = 0; i < 4; i++)
		 {
		   char_array_4[i] =stringtogetindex(char_array_4[i]);
		 }
 
		 char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		 char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
		 char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
 
		 for (i = 0; (i < 3); i++)
		 {
		   outbuf_value[u4outlen++] = char_array_3[i];
		 }
		 i = 0;
	   }
	 }
 	 //DBG_LOG_PRINT(("base64_decode222 i:%d  outbuf:%s u4outlen:%d \n",i,(UCHAR*)outbuf_value,u4outlen));
	 if (i)
	 {
	   for (j = 0; j < i; j++)
	   {
		 char_array_4[j] = stringtogetindex(char_array_4[j]);
	   }
 
	   char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
	   char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
 
	   for (j = 0; (j < i - 1); j++)
	   {
		 outbuf_value[u4outlen++] = char_array_3[j];
	   }
	 }
	 outbuf_value[u4outlen] = '\0';
	 *outlen = u4outlen;
	 c_strncpy(outbuf, outbuf_value, u4outlen);
	 c_mem_free(outbuf_value);
   }
 }
 
 // BEGIN C INTERFACE
CHAR* json_C_getString(CHAR *jsonString, CHAR *key,CHAR* value)
 {

   cJSON *proot,*pc_value;
   DBG_LOG_PRINT(("json_C_getString \n"));
   	if(NULL == (proot = cJSON_Parse(jsonString)))
	{
		printf("failed to parse content cJSON_Parse !\n");
		return NULL;
	}
	 DBG_LOG_PRINT(("json_C_getStrin1g1 \n"));
	pc_value = cJSON_GetObjectItem(proot,key);
	DBG_LOG_PRINT(("valueint:%d valuestring:%s valueint:%d \n",c_strlen(pc_value->valuestring),pc_value->valuestring,c_strlen(pc_value->valuestring)));
	cJSON_Delete(proot);
	c_strncpy(value, pc_value->valuestring, c_strlen(pc_value->valuestring));
	 DBG_LOG_PRINT(("value:%s \n",(CHAR*)value));
	 return value;
 }

void base64_C_decode(const CHAR* inbuf, size_t inlen, UCHAR** extOutBuf, size_t *extOutLen)
 {
   size_t outlen;
   UCHAR *outbuf = (UCHAR*)(c_mem_alloc((((inlen * 3) + 3) / 4) + 1));
   
   //DBG_LOG_PRINT(("base64_C_decode inbuf:%s inlen:%d \n",inbuf,inlen));
   base64_decode(inbuf, inlen, outbuf, &outlen);
   //DBG_LOG_PRINT(("base64_C_decode outbuf:%s outlen:%d \n",outbuf,outlen));
   *extOutBuf = outbuf;
   *extOutLen = outlen;
 }


 static VOID getJWTSub( CHAR* str,CHAR* outbuf)
 {
   CHAR*  jwtGrant;
   size_t jwtOutLen;
   DBG_LOG_PRINT(("getJWTSub \n"));
   // look for both flavors
   CHAR value[maxInt]={0};
   cJSON *proot,*pc_value;
   cJSON *proot_sub,*pc_value_sub;

    if(NULL == (proot = cJSON_Parse(str)))
	{
		printf("failed to parse content cJSON_Parse !\n");
		return;
	}
	 DBG_LOG_PRINT(("getJWTSub start \n"));
	pc_value = cJSON_GetObjectItem(proot,"gidToken");
	if(pc_value)
	{
		DBG_LOG_PRINT(("valueint:%d valuestring:%s valueint:%d \n",c_strlen(pc_value->valuestring),pc_value->valuestring,c_strlen(pc_value->valuestring)));
		c_strncpy(value, pc_value->valuestring, c_strlen(pc_value->valuestring));
	}
	else
    {
		pc_value = cJSON_GetObjectItem(proot,"token");
		if(pc_value)
		{
			DBG_LOG_PRINT(("valueint:%d valuestring:%s valueint:%d \n",c_strlen(pc_value->valuestring),pc_value->valuestring,c_strlen(pc_value->valuestring)));
			c_strncpy(value, pc_value->valuestring, c_strlen(pc_value->valuestring));
		}
		else
		{
			return;
		}
    }
 //	DBG_LOG_PRINT(("getJWTSub11 \n"));
   if ( value[0] == 0 )
   {
	 return;
   }
 	DBG_LOG_PRINT(("getJWTSub22  value:%s \n",(CHAR*)value));
   strtok( value, ".");
   
   CHAR * base64Grant = strtok( NULL, ".");
   if ( NULL == base64Grant )
   {
	 return;
   }
 
   // decode it
   //DBG_LOG_PRINT(("getJWTSub33 base64Grant:%s length:%d \n",base64Grant,c_strlen(base64Grant)));
   base64_C_decode((const CHAR*)base64Grant, c_strlen(base64Grant), &jwtGrant, &jwtOutLen);
   //DBG_LOG_PRINT(("getJWTSub44 jwtGrant:%s \n",jwtGrant));

  if(NULL == (proot_sub = cJSON_Parse(jwtGrant)))
  {
 	 printf("failed to parse content cJSON_Parse !\n");
	 c_mem_free(jwtGrant);
 	 return;
  }
  pc_value_sub = cJSON_GetObjectItem(proot_sub,"sub");
  if(pc_value_sub == NULL)
  {
  	c_mem_free(jwtGrant);
  	return;
  }
 // DBG_LOG_PRINT(("pc_value_sub:%d pc_value_sub:%s pc_value_sub:%d \n",c_strlen(pc_value_sub->valuestring),pc_value_sub->valuestring,c_strlen(pc_value_sub->valuestring)));
  if(c_strlen(pc_value_sub->valuestring) < 256)
  {
  	c_strncpy(outbuf, pc_value_sub->valuestring, c_strlen(pc_value_sub->valuestring));
  }
  else
  {
  	c_strncpy(outbuf, pc_value_sub->valuestring, 255);
  }
  c_mem_free(jwtGrant);

   cJSON_Delete(proot);
   cJSON_Delete(proot_sub);
 }
 
VOID  getTokenFromFile(CHAR* directory, CHAR * prefix,CHAR* outbuf)
 {
   DIR* dir = NULL;
   struct dirent* ent = NULL;
   struct stat	  st;

   dir = opendir(directory);
   if (dir == NULL)
   {
	 return;
   }
   while ((ent = readdir(dir)) != NULL)
   {
	 CHAR* full_file_name;
 
	 // skip if the file name doesn't start with prefix
	 if (strncmp(ent->d_name, prefix, strlen(prefix)))
	 {
	   continue;
	 }

	 // create full file name to test for directories
	 if ( NULL == (full_file_name = (CHAR*)c_mem_alloc(strlen( directory ) + strlen( ent->d_name ) + 2 )))
	 {
	  closedir(dir);
	   return;
	 }
	 strcpy( full_file_name, directory );
	 strcat( full_file_name, "/" );
	 strcat( full_file_name, ent->d_name );
 
	 // skip if it is a directory
	 if (stat(full_file_name, &st) == -1)
	 {
	   c_mem_free(full_file_name);
	   continue;
	 }
	 INT32 is_directory = (st.st_mode & S_IFDIR) != 0;
	 if (is_directory)
	 {
	   c_mem_free(full_file_name);
	   continue;
	 }
	 {
	   FILE *fp;
	   CHAR *str;
	   INT32 sz;
	   
	   if ( NULL == (fp = fopen(full_file_name, "r" )))
	   {
		 c_mem_free(full_file_name);
		 closedir(dir);
		 return NULL;
	   }
	   c_mem_free(full_file_name);
 
	   fseek(fp, 0L, SEEK_END);
	   sz = ftell(fp) + 1;
	   rewind(fp);
	   str = (CHAR*)c_mem_alloc( sz );
	   if ( NULL == fgets(str, sz, fp))
	   {
		 c_mem_free(str);
		 closedir(dir);
		 return;
	   }

 	  //DBG_LOG_PRINT(("str:%s \n",str));
	   getJWTSub(str,outbuf);

	   c_mem_free(str);

	   fclose (fp);

	 }
   }

   closedir(dir);
 }

 /*-----------------------------------------------------------------------------
					 uli function implement end
  ----------------------------------------------------------------------------*/

