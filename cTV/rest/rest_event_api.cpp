/*************************************************************************************
* Description:
*    Use the newly tv_settings part REST-VSSP-PYTHON  to replace the old one ,please notice we
*    are using uncompletely multi-tree to achieve such function. And I had assign specific the relative
*    variables size .So you have to modify it if init failed or the number not enough.
* TODO:
*    The modify the tree struct ,for example using brother address to replace the original pointer ,it is
*    because we had use the dead number and it could not be change dynamic and would waste too
*    manay memory
*  Author:
*    dolphin / haoyuan.li@mediatek.com
*  Date:
*    2020/03/27
**************************************************************************************/
#include <vector>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "common.h"

#include "handler.h"
#include "method.h"
#include "rest_event_api.h"
#include "rest_api_variables.h"


#ifdef __cplusplus
extern "C" {
#endif

#include "c_dbg.h"
#include "u_dbg.h"
#include "u_common.h"

#ifdef __cplusplus
}
#endif

static VTN* _gt_tree[VSSP_MODEL_MAX]; //record the tree

#if 0
#define _rest_debug_log(fmt,...) \
        REST_LOG_E(fmt,##__VA_ARGS__);

void _rest_print_vector(std::vector<std::string> v_str)
{
	_rest_debug_log("size is %d\n",v_str.size());
	for(int i=0;i<v_str.size();i++)
	{
		_rest_debug_log("Item[%d][%s]\n",i,v_str[i].c_str());
	}
}

void _rest_vector_to_uri(std::vector<std::string> v_str ,std::string &s_str)
{
	for(int i=0;i<v_str.size();i++)
	{
		s_str.append(v_str[i]);
		if(i+1 != v_str.size())
			s_str.append("/");
	}
}

/* Fun for debug ,Search by depth */
int _rest_print_tree(VTN *t_tree,std::vector<std::string> &v_str)
{
	int i4_ret=-1;
	if(t_tree->i4_node_num != 0)
	{
		for(int i=0;i<t_tree->i4_node_num;i++)
		{
			v_str.push_back(std::string(t_tree->p_sub_uri));
			VTN* t_sub_tree = t_tree->t_sub_node[i];
			_rest_print_tree(t_sub_tree,v_str);
			v_str.pop_back();
		}
		if(t_tree->i4_offset != 0)
		{
			std::string s_str;
			_rest_vector_to_uri(v_str,s_str);
			_rest_debug_log("One Uri: -%s offset %d\n",s_str.c_str(),t_tree->i4_offset);
		}
	}
	else
	{
		v_str.push_back(std::string(t_tree->p_sub_uri));
		std::string s_str;
		_rest_vector_to_uri(v_str,s_str);
		_rest_debug_log("One Uri: %s offset %d\n",s_str.c_str(),t_tree->i4_offset);
		v_str.pop_back();
	}
	return i4_ret;
}

void _rest_print_all_tree(void)
{
	for(int i4_uri_num1=0;i4_uri_num1<VSSP_MODEL_MAX;i4_uri_num1++) //search the whole storage array
	{
		std::vector<std::string> v_str;
		_rest_debug_log("Print tree >>>> %d\n",i4_uri_num1);
		_rest_print_tree(_gt_tree[i4_uri_num1],v_str);
	}
}

#else
#define _rest_debug_log(fmt,...) {}
#define _rest_print_vector(fmt,...) {}
#define _rest_vector_to_uri(fmt,...) {}
#define _rest_print_all_tree(fmt,...) {}
#endif


/************************************************************************
*  Fun:
*	static std::vector<std::string> splitString(const std::string& inputStr, char splitChar)
*  Description:
*	create to seperate a URI to a vector
*  Author:
*	dolphin/haoyuan.li@mediatek.com
*  Date:
*	20200326
*************************************************************************/
static std::vector<std::string> splitString(const std::string& inputStr, char splitChar)
{
	std::vector<std::string> outStrVec;
	std::string::size_type loc_start = 0;
	std::string::size_type loc_stop = inputStr.find_first_of(splitChar);

	while (1)
	{
		if (loc_stop == std::string::npos)
		{
			outStrVec.push_back(inputStr.substr(loc_start));
			break;
		}
		if (loc_start != loc_stop)
		{
			if (loc_stop != std::string::npos)
			{
				outStrVec.push_back(inputStr.substr(loc_start, loc_stop - loc_start));
			}
			else
			{
				outStrVec.push_back(inputStr.substr(loc_start));
			}
		}
		loc_start = loc_stop + 1;
		loc_stop = inputStr.find_first_of(splitChar, loc_start);
	}
	return outStrVec;
}

/************************************************************************
*  Fun:
*	int _apply_mapping_rules(MAPPING_RULES t_rules,std::string &s_uri_src ,std::string &s_uri_dst)
*  Description:
*	Get the new mapping uri if match to the rules tables
*  Input:
*     t_rules : replace rules
*	v_uri_src: the uri to be replace
*  Output:
*	v_uri_dst: the uri replaced
*  Return:
*	  0: succeed
*	-1: failed
*  Author:
*	dolphin/haoyuan.li@mediatek.com
*  Date:
*	20200328
*************************************************************************/
static int _apply_mapping_rules(MAPPING_RULES t_rules,std::string &s_uri_src ,std::string &s_uri_dst)
{
	int ret=-1;
	_rest_debug_log("Comparing (%d) src %s dst %s ",strlen(t_rules.p_src),t_rules.p_src,s_uri_src.c_str());
	if(strncmp(s_uri_src.c_str(),t_rules.p_src,strlen(t_rules.p_src))==0)
	{
		_rest_debug_log("Match %s \n",t_rules.p_src);
		s_uri_dst = s_uri_src.replace(0,strlen(t_rules.p_src),t_rules.p_dst);
		_rest_debug_log("Replace :\n=>%s \n=>%s\n",s_uri_src.c_str(),s_uri_dst.c_str());
		ret = 0;
	}
	return ret;
}


/************************************************************************
*  Fun:
*	int _rest_search_uri(VTN *t_tree, std::vector<std::string> v_uri)
*  Description:
*	Get the offset of the handler from the tree
*  Input:
*	t_tree: the tree to be added
*	v_uri:  the uri to be search
*  Output:
*	i4_n_channel: the n channel value
*  Return:
*	>= 0: the offset of the uri
*	-1: failed
*     -2: not found
*     -3: tree unexpected size
*  Author:
*	dolphin/haoyuan.li@mediatek.com
*  Date:
*	20200326
*************************************************************************/
static int _rest_search_uri(VTN *t_tree, std::vector<std::string> v_uri,int *i4_n_channel)
{
	int i4_ret=-1;
	if(t_tree->i4_node_num>0)
	{
		for(int i=0;i<t_tree->i4_node_num;i++)
		{
			VTN* t_sub_tree = t_tree->t_sub_node[i];
			//_rest_debug_log("%s , %s\n",t_sub_tree->p_sub_uri,v_uri[0].c_str());
			if((strcmp(t_sub_tree->p_sub_uri,v_uri[0].c_str())==0) || (strncmp(t_sub_tree->p_sub_uri,"*",1)==0))
			{
				if(strncmp(t_sub_tree->p_sub_uri,"*",1)==0)
				{
					char p_number[MAX_SUB_URI_LEN]={0};
					char *p_end=NULL;
					strcpy(p_number,v_uri[0].c_str());
					//sscanf(v_uri[0].c_str(),"%*[^0-9]%d",i4_n_channel);
					for( int j=0;j<strlen(p_number);j++)
					{
						if(p_number[j]-'0' >=0 && p_number[j]-'0' <=9) //channel_n Or n_ire ,we have to ensure the number in all please could be parsed
						{
							*i4_n_channel = (int)strtol(&p_number[j], &p_end, 10);
							if(p_end==NULL)
							{
								REST_LOG_E("N value parse error\n");
							}
							break;
						}
					}
					_rest_debug_log("Get channel %d\n",*i4_n_channel);
				}
				if(v_uri.size()>1)
				{
					//Sub Search
					//_rest_debug_log("Get match %s %s\n",t_sub_tree->p_sub_uri,v_uri[0].c_str());
					std::vector<std::string> v_sub_uri;
					v_sub_uri.insert(v_sub_uri.begin(),v_uri.begin()+1,v_uri.end());
					i4_ret = _rest_search_uri(t_sub_tree,v_sub_uri,i4_n_channel);
					break;
				}
				else
				{
					i4_ret = t_sub_tree->i4_offset;
					_rest_debug_log("Get match all %s succeed ,offset %d\n",v_uri[0].c_str(),t_sub_tree->i4_offset);
					return i4_ret;
				}
			}
		}
	}
	else  //search to the bottom of the tree
	{
		if(v_uri.size()>0)
		{
			i4_ret = -3;
			//_rest_debug_log("Tree short than url ,Failed\n");
		}
	}
	if(i4_ret==-1)
	{
		//_rest_debug_log("Unmatch URI ,Failed\n");
	}
	return i4_ret;
}

/************************************************************************
*  Fun:
*	int rest_search_uri(std::string s_uri,int *i4_n_channel)
*  Description:
*	Get the offset of the handler from the tree ,search by the priority we set
*  Input:
*	t_tree: the tree to be added
*	s_uri:  the uri to be search
*  Output:
*	i4_n_channel: the n channel value
*  Return:
*	>= 0: the offset of the uri
*	-1: failed
*  Author:
*	dolphin/haoyuan.li@mediatek.com
*  Date:
*	20200326
*************************************************************************/
int rest_search_uri(std::string s_uri,int *i4_n_channel)
{
	int i4_ret = -1;
	int i4_need_run = 1;
	std::vector<std::string> v_uri = splitString(s_uri,'/');

	//Search in the exist url table
	for(int i=VSSP_MODEL_MAX-1;i>=0;i--)
	{
		//REST_LOG_I("Search in Tree : %s\n",_gt_tree[i]->p_sub_uri);
		if((i4_ret = _rest_search_uri(_gt_tree[i],v_uri,i4_n_channel)) >= 0)
		{
			i4_need_run = 0;//Had found
			break;
		}
	}

	if(i4_need_run==1)
	{
		//Search by associate/mapping rules
		for(int j=0;j<g_map_rules_number;j++)
		{
			std::string s_replace_uri;
			std::string s_src_tmp = s_uri;
			i4_ret = _apply_mapping_rules(gp_mp_rules[j],s_src_tmp,s_replace_uri);
			if(i4_ret==0)
			{
				v_uri = splitString(s_replace_uri,'/');
				if((i4_ret = _rest_search_uri(_gt_tree[VSSP_MODEL_ORIGINAL],v_uri,i4_n_channel)) >= 0)
				{
					i4_need_run = 0;//Had found
					break;
				}
			}
		}
	}

	if(i4_ret==-1)
	{
		REST_LOG_E("Could not find the uri %s\n",s_uri.c_str());
	}

	return i4_ret;
}

/************************************************************************
*  Fun:
*	int _rest_add_uri(VTN *t_tree, std::vector<std::string> v_uri)
*  Description:
*	Add a uri as a node to a tree
*  Input:
*	i4_offset: the offset in the function handler array
*	t_tree: the tree to be added
*	v_uri:  the uri to be add to the tree
*  Return:
*	0: Succeed
*	1: Url already exist /Node already exist
*	2: Unexpect error
*  Author:
*	dolphin/haoyuan.li@mediatek.com
*  Date:
*	20200326
*************************************************************************/
static int _rest_add_uri(VTN *t_tree, std::vector<std::string> v_uri, int i4_offset)
{
	enum _errcode
	{
		RET_ERROR = -2,     /* Create failed */
		RET_DEFAULT = -1,
		RET_SUCCEED = 0, /* Create Succeed */
		RET_EXISTED = 1,  /* Child already exist */
	};
	int i4_create_finish=RET_DEFAULT;
	//_rest_print_vector(v_uri);

	//Search the Node
	while(i4_create_finish==RET_DEFAULT)
	{
		//Have children
		for(int i=0 ;i<t_tree->i4_node_num ;i++)
		{
			VTN *t_sub_tree=t_tree->t_sub_node[i];   //get the child
			//_rest_debug_log("child number rank %d [%s] [%s]\n",i,t_sub_tree->p_sub_uri,v_uri[0].c_str());
			if(strcmp(t_sub_tree->p_sub_uri,v_uri[0].c_str())==0)   //child match
			{
				if(v_uri.size()>1) //Jump to child
				{
					std::vector<std::string> v_sub_uri;
					v_sub_uri.insert(v_sub_uri.begin(),v_uri.begin()+1,v_uri.end());
					//_rest_debug_log("Jump to child %s\n",t_sub_tree->p_sub_uri);
					i4_create_finish = _rest_add_uri(t_sub_tree,v_sub_uri,i4_offset);
					//_rest_debug_log("Back to parent %s\n",t_tree->p_sub_uri);
					break;
				}
				else //Child/Node exist
				{
					//_rest_debug_log("Child %s Already exist\n",t_sub_tree->p_sub_uri);
					if(t_sub_tree->i4_offset != 0)  //the node not being a bottom node & be created & not inited
					{
						t_sub_tree->i4_offset = i4_offset;
						_rest_debug_log("Create name %s offset %d middle node\n",t_sub_tree->p_sub_uri,t_sub_tree->i4_offset);
					}
					i4_create_finish = RET_EXISTED;
					break;
				}
			}
		}

		if(i4_create_finish==RET_DEFAULT)
		{
			//No Children Existed / Found
			if(v_uri.size()>1)
			{
				//Create Child
				VTN *t_sub_tree=NULL;
				t_sub_tree = (VTN*)malloc(sizeof(VTN));
				if(t_sub_tree==NULL)
				{
					REST_LOG_E("malloc memory failed\n");
					i4_create_finish = RET_ERROR;
					break;
				}

				//Set the Child Address And Init
				t_tree->t_sub_node[t_tree->i4_node_num] = t_sub_tree;  //not found ,so use the new number
				t_sub_tree->i4_node_num=0;
				t_sub_tree->i4_offset=0;
				memset(t_sub_tree->p_sub_uri,0x0,MAX_SUB_URI_LEN);

				//Check name
				if(v_uri[0].length() >= MAX_SUB_URI_LEN)
				{
					REST_LOG_E("Create sub uri %s too long ,failed\n",v_uri[0].c_str());
					i4_create_finish = RET_ERROR;
					break;
				}

				//Name the child
				strcpy(t_sub_tree->p_sub_uri,v_uri[0].c_str());

				//Parent node's child number accumulate
				t_tree->i4_node_num++;
				//_rest_debug_log("child name number %s %d\n",t_sub_tree->p_sub_uri,t_tree->i4_node_num);

				//Jump to the child
				//_rest_debug_log("Enter child %s\n",t_sub_tree->p_sub_uri);
				std::vector<std::string> v_sub_uri;
				v_sub_uri.insert(v_sub_uri.begin(),v_uri.begin()+1,v_uri.end());
				i4_create_finish = _rest_add_uri(t_sub_tree,v_sub_uri,i4_offset);
				//_rest_debug_log("Back parent %s\n",t_tree->p_sub_uri);
				break;
			}
			else
			{
				if(t_tree->i4_node_num + 1 > MAX_CHILDREN_NUM)  //Children on one Node overflow
				{
					REST_LOG_E("Too many child %d on a node %s than %d ,please help to modify \n",t_tree->i4_node_num + 1,t_tree->p_sub_uri,MAX_CHILDREN_NUM);
					i4_create_finish = RET_ERROR;
					break;
				}

				//Create Child
				VTN *t_sub_tree=NULL;
				t_sub_tree = (VTN*)malloc(sizeof(VTN));
				if(t_sub_tree==NULL)
				{
					REST_LOG_E("malloc memory failed\n");
					i4_create_finish = RET_ERROR;
					break;
				}

				//Set the Child Address And Init
				t_tree->t_sub_node[t_tree->i4_node_num] = t_sub_tree;  //not found ,so use the new number
				t_sub_tree->i4_node_num=0;
				t_sub_tree->i4_offset=0;
				memset(t_sub_tree->p_sub_uri,0x0,MAX_SUB_URI_LEN);

				//Check name
				if(v_uri[0].length() >= MAX_SUB_URI_LEN)
				{
					REST_LOG_E("Create sub uri %s too long ,failed\n",v_uri[0].c_str());
					i4_create_finish = RET_ERROR;
					break;
				}

				//Name the child
				strcpy(t_sub_tree->p_sub_uri,v_uri[0].c_str());

				//Parent node's child number accumulate
				t_tree->i4_node_num++;
				//_rest_debug_log("child name number %s %d\n",t_sub_tree->p_sub_uri,t_tree->i4_node_num);

				//Create finish
				//_rest_debug_log("Create Finish\n");
				t_sub_tree->i4_offset = i4_offset;
				//_rest_debug_log("Create name %s offset %d bottom node\n",t_sub_tree->p_sub_uri,t_sub_tree->i4_offset);
				i4_create_finish = RET_SUCCEED;
				break;
			}
		}
		else
		{
			_rest_debug_log("Finish Flag Reach %d ,Stop!\n",i4_create_finish);
		}
	}
	_rest_debug_log("Return\n");
	return i4_create_finish;
}

/***********************************
*  Fun:
*	int rest_init_vssp_uri(void)
*  Description:
*	init the vssp uri module
*  Return:
*	0: Succeed
*	-1: Failed
*  Author:
*	dolphin/haoyuan.li@mediatek.com
*  Date:
*	20200326
************************************/
int rest_init_vssp_uri(void)
{
	int i4_ret = 0;
	int i4_count=0;
	int i4_uri_num1 = 0;
	int i4_uri_num2 = -1;
	int i4_header=0;
	int i4_model=0;

	REST_LOG_I("Enter\n");

	/* Step 1. Init the original URL storage Array */
	for(i4_uri_num1=0 ;i4_uri_num1<g_uri_number ;i4_uri_num1++)
	{
		if(p_uri_event[i4_uri_num1].i1_priority_uri_value == VSSP_MODEL_ORIGINAL) //record the real offset ,if mapping url ,the no change
		{
			i4_uri_num2++;
			p_uri_event[i4_uri_num1].i4_offset=i4_uri_num2;	//the real offset accumulate
			for(i4_header=0;i4_header<g_header_number;i4_header++)  //Init header
			{
				if(strncmp(gp_main_uri[i4_header].p_uri ,p_uri_event[i4_uri_num1].p_uri ,strlen(gp_main_uri[i4_header].p_uri))==0)
				{
					if(gp_main_uri[i4_header].i4_start == gp_main_uri[i4_header].i4_end)
					{
						gp_main_uri[i4_header].i4_start = i4_uri_num2;
						gp_main_uri[i4_header].i4_end = i4_uri_num2;
					}
					gp_main_uri[i4_header].i4_end ++;
				}
			}
		}
		else
		{
			p_uri_event[i4_uri_num1].i4_offset=i4_uri_num2;	//the mapping url ,offset not change
		}
	}

	for(i4_header=0;i4_header<g_header_number;i4_header++)
	{
		REST_LOG_I("Header[%d][%s][%d - %d)\n",i4_header,gp_main_uri[i4_header].p_uri,gp_main_uri[i4_header].i4_start,gp_main_uri[i4_header].i4_end);
	}

	/* Step 2. Init the tree Parent Node */
	for(i4_count=0;i4_count<VSSP_MODEL_MAX;i4_count++)
	{
		_gt_tree[i4_count] = (VTN*)malloc(sizeof(VTN));
		_gt_tree[i4_count]->i4_node_num=0;
		_gt_tree[i4_count]->i4_offset=0;
		memset(_gt_tree[i4_count]->p_sub_uri,0x0,MAX_SUB_URI_LEN);
		sprintf(_gt_tree[i4_count]->p_sub_uri,"Tree_%d",i4_count); //parent
	}

	/* Step 3. Building Tree */
	for(i4_uri_num1=0;i4_uri_num1<g_uri_number;i4_uri_num1++) //search the whole storage array
	{
		i4_model = p_uri_event[i4_uri_num1].i1_priority_uri_value;
		//_rest_debug_log("URI is %s model %d offset %d\n",p_uri_event[i4_uri_num1].p_uri ,i4_model,p_uri_event[i4_uri_num1].i4_offset);

		//Init According to Priority
		i4_ret = _rest_add_uri(_gt_tree[i4_model] ,splitString(std::string(p_uri_event[i4_uri_num1].p_uri),'/') ,p_uri_event[i4_uri_num1].i4_offset);
		if(i4_ret < 0)
		{
			REST_LOG_E("Init Vssp uri model failed\n");
			goto VSSP_FAILED;
		}
	}
	REST_LOG_I("Init Done!\n");
	_rest_print_all_tree();

	return 0;

VSSP_FAILED:
	rest_vssp_destroy();
	return -1;
}

/***********************************
*  Fun:
*	int rest_parse_endpoint_query(std::string request, std::map<std::string,std::string>& query)
*  Description:
*	parse endpoint query into map structure
*  Return:
*	0: Succeed
*	-1: Failed
************************************/
int rest_parse_endpoint_query(const std::string& request, std::map<std::string,std::string>& query)
{
    REST_LOG_E("Request is %s\n",request.c_str());
    if(request.empty())
    {
        REST_LOG_E("Request is empty.\n");
        return -1;
    }
    std::vector<std::string> content = splitString(request, '&');
    for(std::vector<std::string>::iterator it = content.begin(); it != content.end(); it++)
    {
        std::string::size_type location = it->find_first_of("=");
        if(location == std::string::npos || location == it->length()-1)
        {
            // Such as "vendor_id="
            REST_LOG_E("Value is empty.\n");
            return -1;
        }
        if(location == 0)
        {
            // Such as "=xyz"
            REST_LOG_E("Key is empty.\n");
            return -1;
        }
        std::string key = it->substr(0, location);
        std::string value = it->substr(location+1);
        query[key] = value;
    }

    return 0;
}

/*************************************************
*  Fun:
*	int rest_tree_destory(VTN *t_tree)
*  Description:
*	destory the tree and free the memory ,depth first search
*  Return:
*	0: Succeed
*	-1: Failed
*  Author:
*	dolphin/haoyuan.li@mediatek.com
*  Date:
*	20200326
**************************************************/
static int _rest_tree_destory(VTN *t_tree)
{
	if(t_tree->i4_node_num>0)
	{
		for(int i=0;i<t_tree->i4_node_num;i++)
		{
			_rest_tree_destory(t_tree->t_sub_node[i]);
		}
	}
	else
	{
		if(t_tree != NULL)
		{
			free(t_tree);
			t_tree=NULL;
		}
	}
	return 0;
}

int rest_vssp_destroy(void)
{
	for(int i=0;i<VSSP_MODEL_MAX;i++)
	{
		_rest_tree_destory(_gt_tree[i]);
	}
	return 0;
}



/******************************************************************************/
/************     Below is for transfer /Mapping id to hander offset    *******************/
/*****************************************************************************/
int rest_init_offset_handler(int i4_offset ,Json::Value & root, Json::Value & response)
{
	int ret = -2;
	int i4_real_offset=-1;
	for(int i=0;i<g_header_number;i++)
	{
		if(i4_offset >= gp_main_uri[i].i4_start && i4_offset < gp_main_uri[i].i4_end)
		{
			i4_real_offset = i4_offset -gp_main_uri[i].i4_start;
			_rest_debug_log("gp_main_uri(%s)[%d][%d] => name:%s\n",gp_main_uri[i].p_uri,i,i4_real_offset);
			ret = gp_main_uri[i].h_fun[i4_real_offset](root,response);
		}
	}
	if(ret ==-2)
	{
		REST_LOG_E("Function not found\n");
		ret = -1;
	}
	return ret;
}

