#ifndef CVT_COMMON_H
#define CVT_COMMON_H

#define CVT_SUCCESS    0
#define CVT_FAILURE    1

#define PATH_LEN_MAX      128
#define FILEID_LEN_MAX    32
#define FLODER_NAME_MAX   32
#define HEX_KEYID_SIZE    4

int CVTE_GetChIndexInStr(unsigned char *str, unsigned char ch);
int CVTE_GetLastChIndexInStr(unsigned char *str, unsigned char ch);
int CVTE_CatchSubStr(unsigned char *srcStr, unsigned char *subStr, unsigned char beiginCh, unsigned char endCh);
int CVTE_CatchOneFileUnderDir(unsigned char *filePath, unsigned int filePathSize, unsigned char *dirPath);
int CVTE_CatchFileUnderDirWithSubStr(unsigned char *filePath, unsigned int filePathSize, unsigned char *dirPath, unsigned char *subStr);
int CVTE_CatchWholeFileData(unsigned char *filePath, unsigned char **pDataBuff, unsigned int *pFileSize);

#endif
