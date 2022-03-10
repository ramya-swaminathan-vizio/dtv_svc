#include <json/value.h>
#include <json/reader.h>
#include "json/writer.h"
#include "handler.h"

#define MAX_SUB_URI_LEN 45  //define the max sub uri length in an uri
#define MAX_MAIN_URI_NUMBER 64  //define the max main uri number for calc searching
#define MAX_CHILDREN_NUM 30  //define the max children number on a node
#define MAX_ONE_URL_LEN 128  //one url length we though

/* Struct for the priority Event */
typedef enum _VSSP_MODEL_TYPE
{
    VSSP_MODEL_ORIGINAL=0,
    VSSP_MODEL_MAP1,
    VSSP_MODEL_MAX,
}VSSP_MODEL_TYPE;

/* Struct for storage the original URL */
typedef struct _VSSP_EVENT
{
	int i4_offset; //this byte for mapping the real function ptr array
	VSSP_MODEL_TYPE i1_priority_uri_value; //0:Original uri  1:mapping  2:mapping 3..... the numer biger means it is differ model in searching
	char *p_uri; //the uri
}VSSP_EVENT;

/* Struct for tree Node */
typedef struct _VSSP_TREE_NODE
{
    int i4_offset; //this byte for mapping the real function ptr array
    char p_sub_uri[MAX_SUB_URI_LEN];  //the uri string
    int i4_node_num;  //its child node number
    struct _VSSP_TREE_NODE* t_sub_node[MAX_CHILDREN_NUM]; //its child node
}VTN;

typedef struct _VSSP_HEAD_URI  //for mapping
{
	int i4_start;  //record the start offset
	int i4_end;  //record the end offset
	char p_uri[MAX_SUB_URI_LEN*2];  //for init rank
	handler *h_fun;
}VSSP_HEAD_URI;

typedef struct _MAPPING_RULES //for mapping new uri to old uri
{
	char p_dst[MAX_ONE_URL_LEN]; //old uri like 2019
	char p_src[MAX_ONE_URL_LEN]; //new uri like 2020
}MAPPING_RULES;


//extern enum _VSSP_TRUE_URI VSSP_MSGID;
extern VSSP_EVENT p_uri_event[];
extern int g_uri_number; //the uri number
extern VSSP_HEAD_URI gp_main_uri[]; // We calcul the offset and use it tranfer to handler offset
extern int g_header_number;
extern MAPPING_RULES gp_mp_rules[];
extern int g_map_rules_number;


