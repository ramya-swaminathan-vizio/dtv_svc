
#include "mdns.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <netinet/in.h>


UINT8 *mdns_write_u16(UINT8 *ptr, const UINT16 v) {
	ptr[0] = (UINT8) (v >> 8) & 0xFF;
	ptr[1] = (UINT8) (v >> 0) & 0xFF;
	return ptr;
}

UINT8 *mdns_write_u32(UINT8 *ptr, const UINT32 v) {
	ptr[0] = (UINT8) (v >> 24) & 0xFF;
	ptr[1] = (UINT8) (v >> 16) & 0xFF;
	ptr[2] = (UINT8) (v >>  8) & 0xFF;
	ptr[3] = (UINT8) (v >>  0) & 0xFF;
	return ptr;
}

UINT16 mdns_read_u16(const UINT8 *ptr) {
	return  ((ptr[0] & 0xFF) << 8) |
			((ptr[1] & 0xFF) << 0);
}

UINT32 mdns_read_u32(const UINT8 *ptr) {
	return  ((ptr[0] & 0xFF) << 24) |
			((ptr[1] & 0xFF) << 16) |
			((ptr[2] & 0xFF) <<  8) |
			((ptr[3] & 0xFF) <<  0);
}


UINT16 mdns_get_nlabel_len(mdns_packet_t *pkt, UINT16 off)
{
	UINT8 *p;
	UINT8 *e;
	UINT16 len = 0;

	if(!pkt || off > pkt->u2PktSize)
	{
		c_dbg_stmt("zile_mdns,para invalid! line=%d,func=%s,file=%s\n",__LINE__,__FUNCTION__,__FILE__);
        return MDNS_FAIL_PARA;
	}
	e = pkt->buffer + pkt->u2PktSize;

	for (p = pkt->buffer + off; p < e; p++)
	{
		if (*p == 0)
		{
			return len + 1;
		}
		else if ((*p & 0xC0) == 0xC0)
		{
			return len + 2;
		}
		else
		{
			len += *p + 1;
			p += *p;
		}
	}

	return len;

}


INT32 mdns_uncompress_nlabel(mdns_packet_t *pkt, UINT16 off,mdns_qn_entry_t *q)
{
	UINT8 *p;
	UINT8 *e;
	UINT16 len = 0;
	UINT8 *sp;


	if(!pkt || !q || off > pkt->u2PktSize)
	{
		c_dbg_stmt("zile_mdns,para invalid! line=%d,func=%s,file=%s\n",__LINE__,__FUNCTION__,__FILE__);
        return MDNS_FAIL_PARA;
	}
	q->u2LabelLen = mdns_get_nlabel_len(pkt,off);

	// calculate length of uncompressed label
	e = pkt->buffer + pkt->u2PktSize;
	for (p = pkt->buffer + off; p < e;)
	{
		if(*p == 0)//for the root
		{
            len += 2;//for root and '\0'
            break;
		}
		else if ((*p & 0xC0) == 0xC0)
		{
			UINT8 *p2 = pkt->buffer + (((p[0] & ~0xC0) << 8) | p[1]);
			p = p2;
		}
		else
		{
			len += *p + 1;
			p += *p + 1;
		}
	}


	q->u2NameSize = len;

	sp = (UINT8*)c_mem_alloc(len);//free
	if (sp == NULL)
	{
		c_dbg_stmt("zile_mdns,c_mem_alloc qname fail! line=%d,func=%s,file=%s\n",__LINE__,__FUNCTION__,__FILE__);
		return -1;
	}
	memset((VOID*)sp,0,len);
	q->pQName = sp;


	e = pkt->buffer + pkt->u2PktSize;
	for (p = pkt->buffer + off; p < e;)
	{
		if(*p == 0)//for the root
		{
            break;
		}
		else if ((*p & 0xC0) == 0xC0)
		{
			UINT8 *p2 = pkt->buffer + (((p[0] & ~0xC0) << 8) | p[1]);
			p = p2;
		}
		else
		{
			strncpy((VOID*)sp,(VOID*)(p+1),*p);
			sp += *p;
			p += *p + 1;

			*sp = '.';
			sp += 1;
		}
	}


    /*{
        INT32 i;
	    c_dbg_stmt("zile_mdns,print the question name! line=%d,func=%s,file=%s\n",__LINE__,__FUNCTION__,__FILE__);
        for(i = 0; i< len;++i)
        {
            if(q->pQName[i] < 32 || q->pQName[i] > 126)
            {
                c_dbg_stmt("(%d)",q->pQName[i]);
            }
            else
            {
                c_dbg_stmt("[%c]",q->pQName[i]);
            }
        }
    }*/


	return 0;
}


INT32 mdns_parse_qname(UINT8 **name,UINT8 *start)
{
    INT32 len = 0;
    UINT8 *p = start;
    UINT8 *question_name;
    if(!name || !p)
    {
		c_dbg_stmt("zile_mdns,question name or start invalid! line=%d,func=%s,file=%s\n",__LINE__,__FUNCTION__,__FILE__);
        return MDNS_FAIL_PARA;
    }
    while(*p)
    {
        len += (*p+1);
        p += len;
    }

    len += 1;

    *name = (UINT8*)c_mem_alloc(len);
    if(!(*name))
    {
		c_dbg_stmt("zile_mdns,alloc question name fail! line=%d,func=%s,file=%s\n",__LINE__,__FUNCTION__,__FILE__);
        return MDNS_FAIL_PARA;
    }
    memset((VOID*)*name,0,len);
    question_name = *name;

    p=start;
    while(*p)
    {
        strncpy((VOID*)question_name,(void*)(p+1),*p);
        question_name += *p;
        *question_name = '.';
        question_name += 1;
        p += *p + 1;
    }
    /*{
        INT32 i;
	    c_dbg_stmt("zile_mdns,print the question name! line=%d,func=%s,file=%s\n",__LINE__,__FUNCTION__,__FILE__);
        for(i = 0; i< len;++i)
        {
            if(question_name[i] < 32 || question_name[i] > 126)
            {
                c_dbg_stmt("(%d)",question_name[i]);
            }
            else
            {
                c_dbg_stmt("[%c]",question_name[i]);
            }
        }
    }*/

	//c_dbg_stmt("zile_mdns,len,is %d:the question name is:%s! line=%d,func=%s,file=%s\n",len,(CHAR*)question_name,__LINE__,__FUNCTION__,__FILE__);
    return len;
}
INT32 mdns_free_question(mdns_packet_t *pkt)
{
	INT32 i;

    if(!pkt)
    {
		c_dbg_stmt("zile_mdns,PKG is NULL! line=%d,func=%s,file=%s\n",__LINE__,__FUNCTION__,__FILE__);
        return MDNS_FAIL_PARA;
    }

    for(i = 0;i < pkt->u2NumQr;++i)
    {
        if(pkt->pQn[i].pQName)
        {
            c_mem_free(pkt->pQn[i].pQName);
            pkt->pQn[i].pQName = NULL;
        }
    }
    c_mem_free(pkt->pQn);
    pkt->pQn = NULL;
    return 0;
}
INT32 mdns_parse_question(mdns_packet_t *pkt)
{
	//UINT8 *question_start = 0 ;
	INT32 i;
	INT32 question_offset = 0;

    if(!pkt)
    {
		c_dbg_stmt("zile_mdns,PKG is NULL! line=%d,func=%s,file=%s\n",__LINE__,__FUNCTION__,__FILE__);
        return MDNS_FAIL_PARA;
    }
    question_offset = sizeof(pkt->u2Id)+sizeof(pkt->u2Flags)+sizeof(pkt->u2NumQr)+sizeof(pkt->u2NumAns)
                    +sizeof(pkt->u2NumAuth)+sizeof(pkt->u2NumAdd);


    if(pkt->u2NumQr == 0)
    {
		//c_dbg_stmt("zile_mdns,question number is 0! line=%d,func=%s,file=%s\n",__LINE__,__FUNCTION__,__FILE__);
        return -1;
    }

    pkt->pQn = c_mem_alloc(sizeof(mdns_qn_entry_t)*pkt->u2NumQr); //free 1
    if(!pkt->pQn)
    {
		c_dbg_stmt("zile_mdns,c_mem_alloc question fail! line=%d,func=%s,file=%s\n",__LINE__,__FUNCTION__,__FILE__);
        return MDNS_FAIL_PARA;
    }
    memset(pkt->pQn,0,sizeof(mdns_qn_entry_t)*pkt->u2NumQr);

    for(i = 0;i < pkt->u2NumQr;++i)
    {
    	UINT8 *p = 0 ;
    	INT32 ret;

        ret = mdns_uncompress_nlabel(pkt,question_offset,&pkt->pQn[i]);
        if(ret < 0)
        {
            INT32 j;
            for(j = 0;j < i; ++j)
            {
                if(pkt->pQn[i].pQName)
                {
                    c_mem_free(pkt->pQn[i].pQName);
                    pkt->pQn[i].pQName = NULL;
                }
            }
            c_mem_free(pkt->pQn);
            pkt->pQn = NULL;
    		c_dbg_stmt("zile_mdns,uncompress_nlabel fail! line=%d,func=%s,file=%s\n",__LINE__,__FUNCTION__,__FILE__);
            return ret;
        }

        p = pkt->buffer + question_offset+ pkt->pQn[i].u2LabelLen;

        pkt->pQn[i].u2QType = mdns_read_u16(p);
        p += sizeof(UINT16);

        pkt->pQn[i].u2QClass = mdns_read_u16(p);
        p += sizeof(UINT16);

        question_offset += pkt->pQn[i].u2LabelLen;
        question_offset += sizeof(UINT16);//sizeof(QTYPE)
        question_offset += sizeof(UINT16);//sizeof(QCLASS)
    }

	return 0;
}

/*
INT32 mdns_parse_question(mdns_packet_t *pkt)
{
	UINT8 *p ;
	INT32 i;
	INT32 question_offset = 0;
    mdns_qn_entry_t **q;

    if(!pkt)
    {
		c_dbg_stmt("PKG is NULL! line=%d,func=%s,file=%s\n",__LINE__,__FUNCTION__,__FILE__);
        return MDNS_FAIL_PARA;
    }
    question_offset = sizeof(pkt->u2Id)+sizeof(pkt->u2Flags)+sizeof(pkt->u2NumQr)+sizeof(pkt->u2NumAns)
                    +sizeof(pkt->u2NumAuth)+sizeof(pkt->u2NumAdd);


    p = pkt->buffer + question_offset;
    q = &(pkt->pQn);

    for(i = 0;i < pkt->u2NumQr;++i)
    {
        INT32 name_len = 0;

        (*q) = c_mem_alloc(sizeof(mdns_qn_entry_t));
        if(!(*q))
        {
    		c_dbg_stmt("zile_mdns,c_mem_alloc question fail! line=%d,func=%s,file=%s\n",__LINE__,__FUNCTION__,__FILE__);
            return MDNS_FAIL_PARA;
        }
        memset((*q),0,sizeof(mdns_qn_entry_t));

        name_len = mdns_parse_qname(&((*q)->pQName),p);
        if(name_len <= 0)
        {
    		c_dbg_stmt("zile_mdns,parse question name fail! line=%d,func=%s,file=%s\n",__LINE__,__FUNCTION__,__FILE__);
            return MDNS_FAIL_PARA;
        }

        p += name_len;

        (*q)->u2QType = mdns_read_u16(p);
        p += sizeof(UINT16);

        (*q)->u2QClass = mdns_read_u16(p);
        p += sizeof(UINT16);

        q = &((*q)->next);
    }

	return 0;
}
*/
// parse a MDNS packet into an mdns_pkt struct
INT32 mdns_parse_pkt(mdns_packet_t *pkt)
{
	UINT8 *p;
	INT32 ret;

    if(!pkt)
    {
		c_dbg_stmt("zile_mdns PKG is NULL! line=%d,func=%s,file=%s\n",__LINE__,__FUNCTION__,__FILE__);
        return MDNS_FAIL_PARA;
    }

    p = pkt->buffer;
	if (pkt->u2PktSize < 12)
    {
		c_dbg_stmt("zile_mdns,PKG len invalid! line=%d,func=%s,file=%s\n",__LINE__,__FUNCTION__,__FILE__);
    	return MDNS_FAIL_PARA;
	}

	// parse header
	pkt->u2Id 		= mdns_read_u16(p); p += sizeof(UINT16);
	pkt->u2Flags 	= mdns_read_u16(p); p += sizeof(UINT16);
	pkt->u2NumQr 	= mdns_read_u16(p); p += sizeof(UINT16);
	pkt->u2NumAns 	= mdns_read_u16(p); p += sizeof(UINT16);
	pkt->u2NumAuth 	= mdns_read_u16(p); p += sizeof(UINT16);
	pkt->u2NumAdd 	= mdns_read_u16(p); p += sizeof(UINT16);

	// parse questions
	ret = mdns_parse_question(pkt);
	//mdns_parse_answer(pkt);
	//mdns_parse_authority(pkt);
	//mdns_parse_additional(pkt);

	return ret;

}

