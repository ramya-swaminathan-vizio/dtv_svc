/*******************************************************************************
*   For save the CPU resources and more efficient for our code running ,we had write such for
*   to supply a API for replace some simply shell comand run by system("") function. 
*   Author:  haoyuan.li@mediatek.com
*   Date:     2019/09/25
********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

#include "c_dbg.h"
#include "u_common.h"
#include "rest_system.h"

INT32 i4_s_dbg_level = 2;  //1: Error 2:Waring 3:Info

/*****************************************************************
* Function:
*    INT32 s_echo(CHAR* p_path, CHAR* p_string, INT32 i4_strlen)
* Description: 
*   Like : "echo > /dir/file"
*   Write string to specific file ,please notice it will rewrite it's previous content
*   and could not write data more than 512B ,Auth: rw-
* Inputs:
*    p_path:    your destination file
*    p_string:  the string you want to write to your destnation file 
*    i4_strlen:  the string length
* Output:
*    NULL
* Return:
*    success :  S_SYSTEM_OK
*    faild:        S_SYSTEM_ERR +
*****************************************************************/
INT32 s_echo(CHAR* p_path, CHAR* p_string, INT32 i4_strlen)
{
    S_DBG_I("Enter\n");

    FILE *f_dstfile=NULL;
    INT32 i4_ret = S_SYSTEM_ERR;
    const CHAR i1_file_tail = 0x0A;                     //the end tail of a file
    const CHAR i4_file_tail_len = sizeof(CHAR);  //tail length
    CHAR p_writebuff[MAX_CACHE_BUFFER_LEN] = {0};

    if(NULL==p_path)
    {
        S_DBG_E("input path is NULL\n");
	 i4_ret = S_SYSTEM_ARGUMENT_ERR;
    }
    else if(NULL==p_string)
    {
         S_DBG_E("input string is NULL\n");
         i4_ret  = S_SYSTEM_ARGUMENT_ERR;
    }
    else if(i4_strlen<0)
    {
         S_DBG_E("input strlen less than ZERO\n");
         i4_ret  = S_SYSTEM_ARGUMENT_ERR;
    }
    else if(i4_strlen >= MAX_CACHE_BUFFER_LEN -1)
    {
         S_DBG_E("input strlen too longth than %d\n",MAX_CACHE_BUFFER_LEN);
         i4_ret  = S_SYSTEM_CACHE_OVERFLOW;
    }
    else
    {
        if(NULL==(f_dstfile=fopen(p_path,"w")))
        {
            S_DBG_E("open file %s error\n",p_path);
            i4_ret = S_SYSTEM_ERR;
        }
        else
        {
            do
            {
                memcpy(p_writebuff, p_string, i4_strlen);                                //user data
                memcpy(p_writebuff+i4_strlen, &i1_file_tail, i4_file_tail_len);  //file tail

                //write data to file
                i4_ret = fwrite(p_writebuff, sizeof(CHAR), i4_strlen+i4_file_tail_len, f_dstfile);
                if(i4_ret != (i4_strlen+i4_file_tail_len))
                {
                    S_DBG_E("write file tail error\n");
                    i4_ret = S_SYSTEM_ERR;
                    break;
                }
                i4_ret=S_SYSTEM_OK;
                S_DBG_I("write file succeed\n");
            }
            while(0);
            fclose(f_dstfile);
        }
    }
    return i4_ret;
}



/***************************************************************
*  Function:
*   VOID s_sync(VOID)
* Description: 
*    Like "sync"
*    sync cache to flash
* Inputs:
*    NULL
* Output:
*    NULL
* Return:
*    NULL
***************************************************************/
VOID s_sync(VOID)
{
    S_DBG_I("Enter\n");
    sync();
}

/**************************************************************
Function:
    VOID s_touch(CHAR* p_path)
Description: 
    Like "touch file"
    Create a file ,please notice if file existed it will rewrite it to an empty file 
    ,Auth: rw-
Inputs:
    p_path: your destination file
Output:
    NULL
Return:
    success :  S_SYSTEM_OK
    faild:        S_SYSTEM_ERR +
***************************************************************/
INT32 s_touch(CHAR* p_path)
{
    S_DBG_I("Enter\n");
    INT32 i4_ret=S_SYSTEM_ERR;
    FILE *f_dstfile=NULL;

    if(NULL!=p_path)
    {
        if(NULL==(f_dstfile=fopen(p_path,"w")))
        {
             S_DBG_E("open file %s error\n",p_path); 
        }
        else
        {
             S_DBG_I("touch %s file succeed\n",p_path);
             fclose(f_dstfile);
             i4_ret = S_SYSTEM_OK;
        }
    }
    else
    {
        S_DBG_E("input argments error\n");
        i4_ret = S_SYSTEM_ARGUMENT_ERR;
    }
    return i4_ret;
}



/* recurse to remove file/directory */
INT32 _s_remove_recurse(CHAR* p_path)
{
    S_DBG_I("Enter\n");

    DIR *t_dir=NULL;
    struct dirent* p_dirent;
    INT32 i4_ret=S_SYSTEM_OK;
    CHAR p_dir_path_recurse[256]={0};
    CHAR p_file_path_recurse[256]={0};
    if(NULL==p_path)
    {
        S_DBG_E("input argments error\n");
	 i4_ret = S_SYSTEM_ARGUMENT_ERR;
    }
    else
    {
        if(NULL==(t_dir=opendir(p_path)))
        {
            S_DBG_E("can't open dir %s\n",p_path);
            i4_ret = S_SYSTEM_ERR;
        }
        else
        {
            while((p_dirent = readdir(t_dir)) != NULL)
            {
                switch(p_dirent->d_type)
                {
                    case DT_DIR:	        /* This is a directory. */
                    {
                        if(strcmp(p_dirent->d_name,".")==0 ||\
                           strcmp(p_dirent->d_name,"..")==0)
                        {
                            S_DBG_I("tmp directory or upper directory");
                            break;
                        }
                        sprintf(p_dir_path_recurse,"%s/%s",p_path,p_dirent->d_name);
                        S_DBG_I("recurse dir %s\n",p_dir_path_recurse);
                        _s_remove_recurse(p_dir_path_recurse);
                        i4_ret = rmdir(p_dir_path_recurse);
                        if(i4_ret!=0)
                        {
                            S_DBG_E("recurse dir %s faild, errno %s\n",p_dir_path_recurse,strerror(errno));
                            i4_ret = S_SYSTEM_ERR;
                        }
                    }
                    break;
                    case DT_BLK:	        /* This is a block device. */
                    case DT_CHR:	 /*This is a character device. */
                    case DT_FIFO:       /* This is a named pipe (FIFO). */
                    case DT_LNK:        /* This is a symbolic link. */
                    case DT_REG:	        /* This is a regular file. */
                    case DT_SOCK:	 /* This is a UNIX domain socket. */
                    {
                        sprintf(p_file_path_recurse,"%s/%s",p_path,p_dirent->d_name);
                        S_DBG_I("remove  file %s\n",p_file_path_recurse);
                        i4_ret=remove(p_file_path_recurse);
                        if(i4_ret!=S_SYSTEM_OK)
                        {
                            S_DBG_E("recurse remove %s type %d faild, errorno %s\n",p_file_path_recurse,p_dirent->d_type,strerror(errno));
                            i4_ret = S_SYSTEM_ERR;
                        }
                    }
                    break;
                    default:
                        S_DBG_E("unable to remove unknow file %s\n",p_dirent->d_name);	
                        i4_ret = S_SYSTEM_ERR;
                    break;
                }
            }
            closedir(t_dir);
        }
    }
    return i4_ret;
}



/**************************************************************************************
Function:
    INT32 s_rm(CHAR* p_path)
Description: 
    Like "rm  /dir/file"
    Like "rm -rf /dir/dir"
    Like "rm -rf /dir/dir/"
    Remove file or directory from flash ,please notice it could remove file on flash but not file had open.
    if file had open,it would be delete after it's free or release ,and take catious it will delete it's content.
    And if you do not know whether it is a dir or a file ,just use "dir/dir" instead "dir/dir/" . 
Inputs:
    p_path: your destination file
Output:
    NULL
Todo:
    need to handle * pattern matching
Return:
    success :  S_SYSTEM_OK
    faild:        S_SYSTEM_ERR
***************************************************************************************/

INT32 s_rm(CHAR* p_path)
{
    S_DBG_I("Enter\n");
    INT32 i4_ret=S_SYSTEM_OK;

    if(NULL==p_path)
    {
        S_DBG_E("input argments error\n");
	 i4_ret = S_SYSTEM_ARGUMENT_ERR;
    }
    else
    {
        if(access(p_path,F_OK)!=0)
        {
            S_DBG_I("delete file/dir %s not exist\n",p_path);
            //link to a un-exist file
            CHAR s_ln_path[20]={0};
            if(readlink(p_path,s_ln_path,sizeof(s_ln_path)) > 0)
            {
                S_DBG_I("linking un-exist file ,just delete\n");
                i4_ret = remove(p_path);
            }
        }
        else
        {
            do
            {
                //link file
                CHAR s_ln_path[20]={0};
                if(readlink(p_path,s_ln_path,sizeof(s_ln_path)) > 0)
                {
                     S_DBG_I("linking file ,just delete\n");
                     i4_ret = remove(p_path);
                     break;
                }

                //normal file
                struct stat t_input;
                stat(p_path, &t_input);
                if(!S_ISDIR(t_input.st_mode))
                {
                     S_DBG_I("not a directory ,just delete\n");
                     i4_ret = remove(p_path);
                     if(i4_ret != S_SYSTEM_OK)
                     {
                         S_DBG_E("remove directory %s faild, errorno %s \n",p_path,strerror(errno));
                         i4_ret=S_SYSTEM_ERR;
                     }
                     break;
                }

                //directory
                i4_ret = _s_remove_recurse(p_path);
                if(i4_ret != S_SYSTEM_OK)
                {
                     S_DBG_E("remove directory %s faild, errorno %s \n",p_path,strerror(errno));
                }
                else
                {
                    i4_ret = remove(p_path);
                    if(i4_ret != S_SYSTEM_OK)
                    {
                         S_DBG_E("remove directory content %s faild, errorno %s \n",p_path,strerror(errno));
                    }
                }
            }
            while(0);
        }
    }
    if(i4_ret == S_SYSTEM_OK)
    {
        S_DBG_I("remove file/directory succeed\n");
    }
    return i4_ret;
}


/***************************************************************
*  Function:
*   INT32 s_ln(CHAR *p_old_path ,CHAR *p_new_path)
* Description:
*    Like "ln -s <dest dir/file> <src dir/file>"
*    Create a soft link with a file already exist
* Inputs:
*    p_old_path:   the file you want to link to
*    p_new_path:  the link file created after linking
* Output:
*    NULL
* Return:
*   success :  S_SYSTEM_OK
*   faild:        S_SYSTEM_ERR
***************************************************************/
INT32 s_ln(CHAR *p_old_path ,CHAR *p_new_path)
{
    S_DBG_I("Enter\n");
    INT32 i4_ret=S_SYSTEM_ERR;

    if(p_old_path==NULL || p_new_path==NULL)
    {
        S_DBG_E("input arguments empty\n");
    }
    else
    {
        i4_ret = symlink(p_old_path,p_new_path);
        if(S_SYSTEM_OK != i4_ret)
        {
            S_DBG_E("link file %s -> %s faild ,errno %s \n",p_new_path,p_old_path,strerror(errno));
        }
        else
        {
            S_DBG_I("soft link successful\n");
        }
    }
    return i4_ret;
}

/***************************************************************
*  Function:
*   INT32 s_mkdir(CHAR *p_dir_path)
* Description:
*    Like "mkdir /dir"
*    Create a directory ,please noticy it would create a directory with AUTH 0777
* Inputs:
*    p_dir_path: directory path
* Output:
*    NULL
* Return:
*   success :  S_SYSTEM_OK
*   faild:        S_SYSTEM_ERR
***************************************************************/
INT32 s_mkdir(CHAR *p_dir_path)
{
    S_DBG_I("Enter\n");
    INT32 i4_ret=S_SYSTEM_ERR;

    if(p_dir_path==NULL)
    {
        S_DBG_E("input arguments empty\n");
    }
    else
    {
        i4_ret = mkdir(p_dir_path,0777);
        if(S_SYSTEM_OK != i4_ret)
        {
            S_DBG_E("create dir %s faild ,errno %s \n",p_dir_path,strerror(errno));
        }
        else
        {
            S_DBG_I("create dir %s successful\n",p_dir_path);
        }
    }
    return i4_ret;
}



/***************************************************************
*  Function:
*   INT32 s_chmod(CHAR* p_path, INT32 i_mode)
* Description:
*    Like "chmod 777 /dir/file"
*    Change one file/dir its authority ,please notice you should input octonary 
*    number:  0777
* Inputs:
*    p_path:   the file/dir path
*    i_mode:  the file/dir mode ,should be octonary number like s_chown(file,0777)
* Output:
*    NULL
* Return:
*   success :  S_SYSTEM_OK
*   faild:        S_SYSTEM_ERR
***************************************************************/
INT32 s_chmod(CHAR* p_path, INT32 i_mode)
{
    if(p_path==NULL)
    {
        S_DBG_E("input arguments empty\n");
    }
    {
        if(0==chmod(p_path,i_mode))
        {
            return S_SYSTEM_OK;
        }
    }
    return S_SYSTEM_ERR;
}

/***************************************************************
*  Function:
*   INT32 s_chown(CHAR* p_path, INT32 t_user_id ,INT32 t_group_id)
* Description:
*    Like "chown system:system file_path"
*    Change one file/dir its owner ,please notice you should input octonary 
*    number: 
* Inputs:
*    p_path:   the file/dir path
*    i_mode:  the file/dir mode ,should be octonary number like s_chown(file,100,100)
* Output:
*    NULL
* Return:
*   success :  S_SYSTEM_OK
*   faild:        S_SYSTEM_ERR
***************************************************************/
INT32 s_chown(CHAR* p_path, INT32 t_user_id ,INT32 t_group_id)
{
    if(p_path==NULL)
    {
        S_DBG_E("input arguments empty\n");
    }
    {
        if(0==chown(p_path,t_user_id,t_group_id))
        {
            return S_SYSTEM_OK;
        }
    }
    return S_SYSTEM_ERR;
}

/***************************************************************
*  Function:
*   INT32 s_r_chown(CHAR* p_path, INT32 t_user_id ,INT32 t_group_id)
* Description:
*    Like "chown -R system:system file_path"
*    Change one file/dir its owner recurse ,please notice you should input octonary 
*    number: 
* Inputs:
*    p_path:   the file/dir path
*    i_mode:  the file/dir mode ,should be octonary number like s_r_chown(file,100,100)
* Output:
*    NULL
* Return:
*   success :  S_SYSTEM_OK
*   faild:        S_SYSTEM_ERR
***************************************************************/
INT32 s_r_chown(CHAR* p_path, INT32 t_user_id ,INT32 t_group_id)
{
    S_DBG_I("Enter\n");

    DIR *t_dir=NULL;
    struct dirent* p_dirent;
    INT32 i4_ret=S_SYSTEM_OK;
    CHAR p_dir_path_recurse[256]={0};
    CHAR p_file_path_recurse[256]={0};

    if(NULL==p_path)
    {
        S_DBG_E("input argments error\n");
	 i4_ret = S_SYSTEM_ARGUMENT_ERR;
    }
    else
    {
        s_chown(p_path, t_user_id ,t_group_id);
        if(NULL==(t_dir=opendir(p_path)))
        {
            S_DBG_E("can't open dir %s\n",p_path);
            i4_ret = S_SYSTEM_ERR;
        }
        else
        {
            while((p_dirent = readdir(t_dir)) != NULL)
            {
                switch(p_dirent->d_type)
                {
                    case DT_DIR:	        /* This is a directory. */
                    {
                        if(strcmp(p_dirent->d_name,".")==0 ||\
                           strcmp(p_dirent->d_name,"..")==0)
                        {
                            S_DBG_I("tmp directory or upper directory");
                            break;
                        }
                        snprintf(p_dir_path_recurse,sizeof(p_dir_path_recurse),"%s/%s",p_path,p_dirent->d_name);
                        S_DBG_I("recurse dir %s\n",p_dir_path_recurse);
                        i4_ret = s_r_chown(p_dir_path_recurse, t_user_id ,t_group_id);
                        if(i4_ret!=0)
                        {
                            S_DBG_E("recurse dir %s faild, errno %s\n",p_dir_path_recurse,strerror(errno));
                            i4_ret = S_SYSTEM_ERR;
                        }
                    }
                    break;
                    case DT_BLK:	        /* This is a block device. */
                    case DT_CHR:	 /*This is a character device. */
                    case DT_FIFO:       /* This is a named pipe (FIFO). */
                    case DT_LNK:        /* This is a symbolic link. */
                    case DT_REG:	        /* This is a regular file. */
                    case DT_SOCK:	 /* This is a UNIX domain socket. */
                    {
                        snprintf(p_file_path_recurse,sizeof(p_file_path_recurse),"%s/%s",p_path,p_dirent->d_name);
                        S_DBG_I("remove  file %s\n",p_file_path_recurse);
                        s_chown(p_file_path_recurse, t_user_id ,t_group_id);
                    }
                    break;
                    default:
                        S_DBG_E("unable to remove unknow file %s\n",p_dirent->d_name);	
                        i4_ret = S_SYSTEM_ERR;
                    break;
                }
            }
            closedir(t_dir);
        }
    }
    return i4_ret; 
}


/* test for all  api */
VOID s_test(VOID)
{
    INT32 i4_ret=S_SYSTEM_OK;
    unsigned long ui8_runtime =0;

    /*****************  SYSTEM CMD *******************/
    system("rm -rf /tmp/test_system/");
    system("mkdir /tmp/test_system/");
    system("mkdir /tmp/test_system/recurse_a");
    system("touch /tmp/test_system/recurse_a/a");
    system("echo  hello world > /tmp/test_system/recurse_a/c");
    system("ln -s /tmp/test_system/recurse_a/c /tmp/test_system/recurse_a/d");
    system("touch /tmp/test_system/cm111");
    system("touch /tmp/test_system/cm777");
    S_DBG_W("---------- SYSTEM Create /tmp/test_system/ ----------\n\n");
    system("ls /tmp/test_system/ -la");

    /******************* Test API ************************/
    do
    {
        S_DBG_W("\n------------ TEST Create DIR [ /tmp/test_system/recurse_c ] ----------\n\n\n");
        i4_ret = s_mkdir("/tmp/test_system/recurse_c");
        if(i4_ret==S_SYSTEM_OK){
            S_DBG_W("   >>  test OK <<\n");
        }
        else{
            S_DBG_E("   >>  test Faild <<\n");
            break;
        }

        S_DBG_W("\n------------ TEST Create DIR [ /tmp/test_system/recurse_d/ ] ----------\n\n\n");
        i4_ret = s_mkdir("/tmp/test_system/recurse_d/");
        if(i4_ret==S_SYSTEM_OK){
            S_DBG_W("   >>  test OK <<\n");
        }
        else{
            S_DBG_E("   >>  test Faild <<\n");
            break;
        }

        S_DBG_W("\n------------ TEST Touch file [ /tmp/test_system/recurse_c/a ] ----------\n\n\n");
        i4_ret = s_touch("/tmp/test_system/recurse_c/a");
        if(i4_ret==S_SYSTEM_OK){
            S_DBG_W("   >>  test OK <<\n");
        }
        else{
            S_DBG_W("   >>  test Faild <<\n");
            break;
        }

        S_DBG_W("\n----- TEST echo  [ echo hello world > /tmp/test_system/recurse_c/b ] ----\n\n\n");
        i4_ret = s_echo("/tmp/test_system/recurse_c/b", "hello world", strlen("hello world"));
        if(i4_ret==S_SYSTEM_OK){
            S_DBG_W("   >>  test OK <<\n");
        }
        else{
            S_DBG_E("   >>  test Faild <<\n");
            break;
        }

        S_DBG_W("\n----- TEST echo ""  [ echo \"\" > /tmp/test_system/recurse_c/ba ] ----\n\n\n");
        i4_ret = s_echo("/tmp/test_system/recurse_c/ba", "", strlen(""));
        if(i4_ret==S_SYSTEM_OK){
            S_DBG_W("   >>  test OK <<\n");
        }
        else{
            S_DBG_E("   >>  test Faild <<\n");
            break;
        }


        S_DBG_W("\n----- TEST echo file md5  [ /tmp/test_system/recurse_c/b ] ----\n\n\n");
        FILE *f_test_fp=NULL;
        CHAR p_md5sum_ori[100]={0};
        CHAR p_md5sum_api[100]={0};
        CHAR p_md5sum_oriname[100]={0};
        CHAR p_md5sum_apiname[100]={0};

        if(NULL==(f_test_fp=popen("/bin/md5sum /tmp/test_system/recurse_a/c /tmp/test_system/recurse_c/b","r")))
        {
            S_DBG_E("test 3 popen command error\n");
            S_DBG_I("call system\n");
            system("md5sum /tmp/test_system/recurse_a/c");
            system("md5sum /tmp/test_system/recurse_c/b");
        }
        else
        {
            fscanf(f_test_fp,"%s",p_md5sum_ori);
            fscanf(f_test_fp,"%s",p_md5sum_oriname);
            fscanf(f_test_fp,"%s",p_md5sum_api);
            fscanf(f_test_fp,"%s",p_md5sum_apiname);

            S_DBG_W("original name and md5 is [%s][%s]\n",p_md5sum_ori,p_md5sum_oriname);
            S_DBG_W("api name and md5 is [%s][%s]\n",p_md5sum_api,p_md5sum_apiname);
            if(0!=strncmp(p_md5sum_ori,p_md5sum_api,32))
           {
               S_DBG_E("	>>	test Faild <<\n");
               pclose(f_test_fp);
               break;
           }
           else
           {
               S_DBG_W("  >>	test OK <<\n");
           }
           pclose(f_test_fp);
        }

        S_DBG_W("\n----- TEST ln  [ /tmp/test_system/recurse_c/b  <- /tmp/test_system/recurse_c/c] ----\n\\n\n");
        i4_ret = s_ln("/tmp/test_system/recurse_c/b", "/tmp/test_system/recurse_c/c");
        if(i4_ret==S_SYSTEM_OK){
            S_DBG_W("   >>  test OK <<\n");
        }
        else{
            S_DBG_E("   >>  test Faild <<\n");
            break;
        }

        S_DBG_W("\n----- TEST sync [ sync ] ----\n\n\n");
        s_sync();
        S_DBG_W("   >>  test  OK <<\n");

        S_DBG_W("\n ---- TEST chmod 777 /tmp/test_system/cm777 \n\n\n");
        i4_ret = s_chmod("/tmp/test_system/cm777",0777);
        if(i4_ret==S_SYSTEM_OK){
            S_DBG_W("   >>  test OK <<\n");
        }
        else{
            S_DBG_E("   >>  test Faild <<\n");
            break;
        }

        S_DBG_W("\n ---- TEST chmod 111 /tmp/test_system/cm111 \n\n\n");
        i4_ret = s_chmod("/tmp/test_system/cm111",0111);
        if(i4_ret==S_SYSTEM_OK){
            S_DBG_W("   >>  test OK <<\n");
        }
        else{
            S_DBG_E("   >>  test Faild <<\n");
            break;
        }

        system("cp /tmp/test_system/recurse_c /tmp/test_system/recurse_d -rf");
        system("touch /tmp/test_system/recurse_e");
        system("ls -lR /tmp/test_system/");
        sleep(10);
        sync();

        S_DBG_W("\n----- TEST rm dir  [ rm /tmp/test_system/recurse_c ] ----\n\n\n");
        i4_ret = s_rm("/tmp/test_system/recurse_c");
        if(i4_ret==S_SYSTEM_OK){
            S_DBG_W("   >>  test OK <<\n");
        }
        else{
            S_DBG_E("   >>  test Faild <<\n");
            break;
        }

        S_DBG_W("\n----- TEST rm dir [ rm /tmp/test_system/recurse_d/ ] ----\n\n\n");
        i4_ret = s_rm("/tmp/test_system/recurse_d/");
        if(i4_ret==S_SYSTEM_OK){
            S_DBG_W("   >>  test OK << \n");
        }
        else{
            S_DBG_E("   >>  test Faild <<\n");
            break;
        }

        S_DBG_W("\n----- TEST rm file [ rm /tmp/test_system/recurse_e ] ----\n\n\n");
        i4_ret = s_rm("/tmp/test_system/recurse_e");
        if(i4_ret==S_SYSTEM_OK){
            S_DBG_W("   >>  test OK <<\n");
        }
        else{
            S_DBG_E("   >>  test Faild <<\n");
            break;
        }

        S_DBG_W("\n**************************************\n"
                           "***** TEST ALL API SUCCESSFUL *****\n"
                           "***************  %ld  ***************\n",ui8_runtime);

	 system("ls -lR /tmp/test_system/");
        ui8_runtime++;

        if(ui8_runtime >= 10*10000)
        {
            S_DBG_W("have run over 100 000 time \n");
            break;
        }
    }
    while(access("/tmp/system_api_cycle",F_OK)==0);
    if(i4_ret!=S_SYSTEM_OK)
    {
        S_DBG_E("\n***************************************\n"
                      "********* TEST ALL API FAILD *********\n"
                      "*****************  %ld ***************\n",ui8_runtime);
    }
    return;
}

