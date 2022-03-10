#include "mDNS.h"


#include <string>

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <assert.h>
#include <vector>


static const std::string GOOGLECAST_TCP_LOCAL = "\v_googlecast\004_tcp\005local\000";
static const std::string VIZIOCAST_TCP_LOCAL = "\012_viziocast\004_tcp\005local\000";


static const std::string WIFI = "wlan0";
static const std::string ETHERNET = "eth0";

static const int BUFFER_SIZE = 4096;
static const int MAX_NET_CARDS = 16;

unsigned short netToU2(unsigned char ** packet)
{
	unsigned short i;

	i = **packet;
	i <<= 8;
	i |= *(*packet + 1);
	
	return i;
}

unsigned int netToU4(unsigned char **packet)
{
	unsigned int l;
	l = **packet;
	l <<= 8;
	l |= *(*packet + 1);
	l <<= 8;
	l |= *(*packet + 2);
	l <<= 8;
	l |= *(*packet + 3);
	
	return l;
}



int u2ToNet(unsigned char ** packet, unsigned short data)
{
	*(*packet + 1) = (unsigned char)data;
	data >>= 8;
	**packet = (unsigned char)data;
	
	return 2;
}

int u4ToNet(unsigned char ** packet, unsigned int data)
{
	*(*packet + 3) = (unsigned char)data;
	data >>= 8;
	*(*packet + 2) = (unsigned char)data;
	data >>= 8;
	*(*packet + 1) = (unsigned char)data;
	data >>= 8;
	**packet = (unsigned char)data;
	
	return 4;
}

static void msleep(int ms) {
	struct timespec req;

	req.tv_sec = ms / 1000;
	int mod = ms % 1000;
	req.tv_nsec = mod * 1000 * 1000;

	::nanosleep(&req, NULL);
}


std::string getHostname() {

	int ret;
	char buf[64];
	ret = gethostname(buf, sizeof buf);
	if (ret == -1)
	{
		return "";
	}
	return std::string(buf);
}


std::string getDomainname() {
	std::string host = getHostname();
	char size[] = {(char)host.size()};
	std::string name = size;
	name.append(host).append(GOOGLECAST_TCP_LOCAL);
	/*name.append(host).append(VIZIOCAST_TCP_LOCAL);*/

	return name;
}


std::string getDomainname(std::string name) {
	std::string host = getHostname();
	char size[] = {(char)host.size()};
	std::string domain = size;
	if (name.find(GOOGLECAST_TCP_LOCAL) != std::string::npos) {
		domain.append(host).append(GOOGLECAST_TCP_LOCAL);
	} else {
		domain.append(host).append(VIZIOCAST_TCP_LOCAL);
	}
	return domain;
}

struct Interface
{
	std::string name;
	int flag;
	int address;
	std::string addr;
	std::string mac;
};

std::vector<Interface> getInterfaces() {
	struct ifconf ifc;
	struct ifreq ifbuf[MAX_NET_CARDS];

	int s = -1;

	std::vector<Interface> interfaces;


	{
		s = socket(AF_INET, SOCK_DGRAM, 0);
		if (-1 == s) {
			perror("socket");
		}
		ifc.ifc_len = sizeof(ifbuf);
		ifc.ifc_buf = (caddr_t)ifbuf;

		if (0 > ioctl(s, SIOCGIFCONF, &ifc)) {
			perror("SIOCGIFCONF");
		}


		for (unsigned int i = 0; i < ifc.ifc_len / sizeof(ifc.ifc_req[0]); i++) {

			if (ioctl(s, SIOCGIFFLAGS, (char*)&ifbuf[i]) == 0) {
				if ((ifbuf[i].ifr_flags & IFF_UP) &&
					(ifbuf[i].ifr_flags & IFF_RUNNING) &&
					((strcmp("127.0.0.1", inet_ntoa(((struct sockaddr_in*)&ifbuf[i].ifr_addr)->sin_addr)) != 0) &&
						(strcmp("0.0.0.0", inet_ntoa(((struct sockaddr_in*)&ifbuf[i].ifr_addr)->sin_addr)) != 0) &&
						(strncmp("169.254", inet_ntoa(((struct sockaddr_in*)&ifbuf[i].ifr_addr)->sin_addr), 7)) != 0)) {

					Interface interface;
					interface.flag = ifbuf[i].ifr_flags;
					interface.name = ifbuf[i].ifr_name;


					if (ioctl(s, SIOCGIFADDR, &ifbuf[i]) == 0) {
						std::string address = inet_ntoa((((struct sockaddr_in*)&ifbuf[i].ifr_addr)->sin_addr));
						interface.addr = address;
						interface.address = (int)(((struct sockaddr_in*)&ifbuf[i].ifr_addr)->sin_addr.s_addr);
					}

					if (ioctl(s, SIOCGIFHWADDR, (char *) &ifbuf[i]) == 0) {
						char mac[13] = {0};
						sprintf(mac,
						"%02x%02x%02x%02x%02x%02x",
								(unsigned char)ifbuf[i].ifr_hwaddr.sa_data[0],
								(unsigned char)ifbuf[i].ifr_hwaddr.sa_data[1],
								(unsigned char)ifbuf[i].ifr_hwaddr.sa_data[2],
								(unsigned char)ifbuf[i].ifr_hwaddr.sa_data[3],
								(unsigned char)ifbuf[i].ifr_hwaddr.sa_data[4],
								(unsigned char)ifbuf[i].ifr_hwaddr.sa_data[5]
						);

						std::string hw = (char*)mac;

						printf("mac is %s \n", hw.c_str());
						interface.mac = hw;

					}

					interfaces.push_back(interface);
				}
			}

		}

		close(s);
	}



	return interfaces;
}



std::string getMac(std::string device) {

	std::vector<Interface> interfaces ;

	while (1) {
		interfaces = getInterfaces();
		if (interfaces.size() == 0)
{
			msleep(1000);
			continue;
		} else if (interfaces.size() == 1) {
			return interfaces[0].mac;
		}
		else {
			for (Interface item : interfaces) {
				if(item.name == device) {
					return  item.mac;
				}
			}
		}
	
	}
}


int getIp(std::string device) {
	std::vector<Interface> interfaces ;

	while (1) {
		interfaces = getInterfaces();
		if (interfaces.size() == 0)
	{
			msleep(1000);
			continue;
		}
		else if (interfaces.size() == 1) {
			return interfaces[0].address;
		}
		else {
			for (Interface item : interfaces) {
				if(item.name == device) {
					return  item.address;
				}
			}
	}

	}
}


int getLocalIpAddr(void)
{
	std::vector<Interface> interfaces ;

	while (1) {
		interfaces = getInterfaces();
		if (interfaces.size() == 0)
	{
			msleep(1000);
			continue;
		}
		if (interfaces.size() == 1) {
			return interfaces[0].address;
		}		
		else if (interfaces.size() > 1) {

			return getIp(WIFI);
	}

	}

}


unsigned char* parsePacket(unsigned char * packet)
{
	unsigned char * p;
	unsigned short ptr = 0;
	mDNSHeader header;


	p = packet + ptr;

	header.transactionID = netToU2(&p);
	ptr += 2;
	p = packet + ptr;
	header.flags = netToU2(&p);
	ptr += 2;
	p = packet + ptr;
	header.questions = netToU2(&p);
	ptr += 2;
	p = packet + ptr;
	header.answers = netToU2(&p);
	ptr += 2;
	p = packet + ptr;
	header.authorityRRs = netToU2(&p);
	ptr += 2;
	p = packet + ptr;
	header.additionalRRs = netToU2(&p);
	ptr += 2;
	p = packet + ptr;

	if (header.questions != 0)
	{
		for (int i = 0; i < header.questions; i++)
		{
			mDNSQuery query;
			query.name = (unsigned char*)(p);
			ptr += strlen((const char*)query.name);
			ptr++;
			p = packet + ptr;
			query.type = netToU2(&p);
			ptr += 2;
			p = packet + ptr;
			query.classAndQu = netToU2(&p);
			ptr += 2;
			p = packet + ptr;

			if (TYPE_PTR == query.type)
			{
				unsigned char * name = (unsigned char *)strdup((const char*)query.name);
				return name;
			}
		}
	}

	if(header.questions != 0) {

	}

	if (header.authorityRRs != 0)
	{
	}

	if (header.additionalRRs != 0)
	{
	}

	return NULL;
}


template<class T> int getObjectSize(T & object)
{
	int size = strlen((const char *)object.header.name) + 1;
	size += 2;
	size += 2;
	size += 4;
	size += 2;
	size += object.dataLength;
	return size;
}


int writeHeader(unsigned char ** packet, mDNSHeader & header)
{
	int ptr = 0;
	unsigned char * p = (*packet)+ptr;

	ptr += u2ToNet(&p, header.transactionID);
	p = (*packet)+ptr;
	ptr += u2ToNet(&p, header.flags);
	p = (*packet)+ptr;
	ptr += u2ToNet(&p, header.questions);
	p = (*packet)+ptr;
	ptr += u2ToNet(&p, header.answers);
	p = (*packet)+ptr;
	ptr += u2ToNet(&p, header.authorityRRs);
	p = (*packet)+ptr;
	ptr += u2ToNet(&p, header.additionalRRs);
	return ptr;
}

template<class T> int writeRecord(unsigned char ** packet, T & object) {
	int ptr = strlen((const char*)object.header.name) + 1;
	memcpy((*packet), object.header.name, ptr);
	unsigned char * p = (*packet)+ptr;
	ptr += u2ToNet(&p, object.header.type);
	p = (*packet)+ptr;
	ptr += u2ToNet(&p, object.header.classAndCache);
	p = (*packet)+ptr;
	ptr += u4ToNet(&p, object.header.timetoLive);
	p = (*packet)+ptr;
	ptr += u2ToNet(&p, object.dataLength);
	memcpy(((*packet) + ptr), object.data, object.dataLength);
	ptr += object.dataLength;
	return ptr;
}





int writeTxt(unsigned char ** packet, mDNSAdditionalRecordsTXTData & txt)
{
	int ptr = 0;
	for (int i = 0; i < txt.itemsCount; i++)
	{
		*(*packet + ptr) = txt.items[i].txtLength;
		ptr++;
		memcpy(((*packet) + ptr), txt.items[i].txt, txt.items[i].txtLength);
		ptr += txt.items[i].txtLength;
	}
	return ptr;
}

int writeSrv(unsigned char ** packet, mDNSAdditionalRecordsSRVData & srvData)
{
	int ptr = 0;
	unsigned char * p = (*packet)+ptr;
	ptr = u2ToNet(&p, srvData.property);
	p = (*packet)+ptr;
	ptr += u2ToNet(&p, srvData.weight);
	p = (*packet)+ptr;
	ptr += u2ToNet(&p, srvData.port);

	strcpy((char*)((*packet) + ptr), (const char*)srvData.target);
	ptr += strlen((const char *)srvData.target) + 1;

	return ptr;
}


int mDNSPacket(unsigned char * name, unsigned char ** packet)
{
	mDNSHeader header;
	header.transactionID = 0x0000;
	header.flags = 0x8400;
	header.questions = 0x0000;
	header.answers = 0x0001;
	header.authorityRRs = 0x0000;
	header.additionalRRs = 0x0003;


	mDNSRecord answer;

	answer.header.name = name;
	answer.header.type = TYPE_PTR;
	answer.header.classAndCache = 0x0001;
	answer.header.timetoLive = 0x00000078;

	std::string domain = (char*)name;
	domain = getDomainname(domain);
	answer.data = (unsigned char *)strdup(domain.c_str());
	answer.dataLength = strlen((const char *)answer.data) + 1;

	mDNSAdditionalRecordsTXTData txtData;

	mDNSRecord txt;

	txt.header.name = answer.data;
	txt.header.type = TYPE_TXT;
	txt.header.classAndCache = 0x8001;
	txt.header.timetoLive = 0x00001194;
	
	mDNSAdditionalRecordsTXTItem * items = NULL;

	getInterfaces();

	if (std::string((char*)name).find(GOOGLECAST_TCP_LOCAL) != std::string::npos) {
	txtData.itemsCount = 9;
		items = new mDNSAdditionalRecordsTXTItem[txtData.itemsCount];

		items[0].txt = (unsigned char*)"id=fa9d6de6755f4f5b9feb4585d63b77f3";

	items[1].txt = (unsigned char*)"ve=02";

		items[2].txt = (unsigned char*)"md=Chromecast";

		items[3].txt = (unsigned char*)"ic=/setup/icon.png";

	std::string fn = "fn=";
	fn.append(getHostname());
	items[4].txt = (unsigned char *)fn.c_str();

	items[5].txt = (unsigned char*)"ca=2053";

	items[6].txt = (unsigned char*)"st=0";

	items[7].txt = (unsigned char*)"bs=ffffffffffff";

	items[8].txt = (unsigned char*)"rs=";


	} else {

		txtData.itemsCount = 14;

		items = new mDNSAdditionalRecordsTXTItem[txtData.itemsCount];

		items[0].txt = (unsigned char*)"id=fa9d6de6755f4f5b9feb4585d63b77f3";

		std::string wifi = "wifi=";
		wifi.append(getMac(WIFI));
		items[1].txt = (unsigned char*)wifi.c_str();

		items[2].txt = (unsigned char*)"fver=0.9.14.3";

		items[3].txt = (unsigned char*)"rver=1.0.12";

		items[4].txt = (unsigned char*)"mver=0.6.0";

		items[5].txt = (unsigned char*)"bver=0.6.0";

		items[6].txt = (unsigned char*)"dt=1";

		items[7].txt = (unsigned char*)"pwr=0";

		items[8].txt = (unsigned char*)"oobe=2";

		items[9].txt = (unsigned char*)"uli=2";

		items[10].txt = (unsigned char*)"tos=1";

		std::string name = "name=";
		name.append(getHostname());
		items[11].txt = (unsigned char*)name.c_str();

		std::string mdl = "mdl=";
		mdl.append("E50");
		items[12].txt = (unsigned char*)mdl.c_str();

		items[13].txt = (unsigned char*)"soc=MTK";
	}





	for (int i = 0; i < txtData.itemsCount ; ++i) {
		items[i].txtLength = strlen((const char *)items[i].txt);
	}

	txtData.items = items;
	txt.dataLength = 0;
	for (int i = 0; i < txtData.itemsCount; i++)
	{
		txt.dataLength += items[i].txtLength;
		txt.dataLength ++;
	}

	txt.data = new unsigned char[txt.dataLength];

	int ptr = writeTxt(&txt.data, txtData);

	assert(ptr == txt.dataLength);



	mDNSAdditionalRecordsSRVData srvData;

	mDNSRecord srv;

	srv.header.name = answer.data;
	srv.header.type = TYPE_SRV;
	srv.header.classAndCache = 0x8001;
	srv.header.timetoLive = 0x00000078;	

	

	srvData.property = 0;
	srvData.weight = 0;
//	srvData.port = 8009;
	srvData.port = 9000;

	srvData.target = txt.header.name;

	srv.dataLength = 6 + strlen((const char *)srvData.target) + 1;
	srv.data = new unsigned char[srv.dataLength];
	
	ptr = writeSrv(&srv.data, srvData);

	assert(ptr == srv.dataLength);

	mDNSAdditionalRecordsAData  aData;

	mDNSRecord a;

	a.header.name = srvData.target;
	a.header.type = TYPE_A;
	a.header.classAndCache = 0x8001;
	a.header.timetoLive = 0x00000078;
	a.dataLength = 4;

	aData.address = getLocalIpAddr();

	aData.address = htonl(aData.address);

	a.data = new unsigned char[a.dataLength];

	u4ToNet(&a.data, aData.address);


	int packetsize = sizeof(mDNSHeader);

	packetsize += getObjectSize(answer);

	packetsize += getObjectSize(txt);
	packetsize += getObjectSize(srv);
	packetsize += getObjectSize(a);


	*packet = new unsigned char[packetsize];

	ptr = 0;

	unsigned char * p = (*packet)+ptr;

	ptr += writeHeader(&p, header);

	p = (*packet)+ptr;

	ptr += writeRecord(&p, answer);

	p = (*packet)+ptr;
	ptr += writeRecord(&p, txt);
	p = (*packet)+ptr;
	ptr += writeRecord(&p, srv);
	p = (*packet)+ptr;
	ptr += writeRecord(&p, a);

	delete answer.data;
	delete txt.data;
	delete srv.data;
	delete a.data;

	return packetsize;
}