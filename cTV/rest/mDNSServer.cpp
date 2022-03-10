#include <arpa/inet.h>
#include <net/if.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

#include <iostream>
#include <string>
#include "mDNS.h"
#include "log.h"
#include <errno.h>
#include <time.h>

static int const mDNS_PORT = 5353;
static std::string const mDNS_GROUP = "224.0.0.251";
static int const BUFFER_SIZE = 4096;

static int running = 0;
static int fd;

void msleep(int ms) {
	struct timespec req;
	req.tv_sec = ms / 1000;
	int mod = ms % 1000;
	req.tv_nsec = mod * 1000 * 1000;
	nanosleep(&req, NULL);	
}

std::string getInterface() {
	struct ifconf ifc = {0};
	char addr[INET_ADDRSTRLEN] = {0};
	int s;
	char *buf = (char*)malloc(BUFFER_SIZE);

	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == s) 
	{
		log::Log::log(log::Log::LEVEL_ERROR, "DNSSERVER", "getInterface socket fail %d", errno);
		free(buf);
		return "";
	}

	while(running) 
	{	
		ifc.ifc_len = BUFFER_SIZE;
		ifc.ifc_buf = buf;

		if (0 > ioctl(s, SIOCGIFCONF, &ifc)) 
		{
			perror("SIOCGIFCONF");
			log::Log::log(log::Log::LEVEL_ERROR, "DNSSERVER", "getInterface ioctl fail %d", errno);
			close(s);
			free(buf);
			return "";
		}

		if (ifc.ifc_len == BUFFER_SIZE) 
		{
			fprintf(stderr, "SIOCGIFCONF output too long");
			close(s);
			free(buf);
			return "";
		}

		for (unsigned int i = 0; i < ifc.ifc_len/sizeof(ifc.ifc_req[0]); i++) 
		{
			if ((strcmp("127.0.0.1", addr) != 0) 
				|| (strcmp("0.0.0.0", addr) != 0)
				|| (strncmp("169.254", addr, 7) != 0)) 
			{
				if ((strcmp(ifc.ifc_req[i].ifr_name, "uap0")==0)
					|| (strcmp(ifc.ifc_req[i].ifr_name, "wlan0")==0)
					|| (strcmp(ifc.ifc_req[i].ifr_name, "eth0")==0))
				{
					close(s);
					free(buf);
					return std::string(ifc.ifc_req[i].ifr_name);
				}
			}
		}

		msleep(1000);
	}
	close(s);
	free(buf);
	return "";
}

void addRoute() {
}

void delRoute() {
}



void* mDNS(void*arg) {

    std::string iface = getInterface();
    int port(mDNS_PORT);	
	
	log::Log::log(log::Log::LEVEL_DEBUG, "DNSSERVER", "start mDNS Server thread\n");

	std::string i = getInterface();

	log::Log::log(log::Log::LEVEL_DEBUG, "DNSSERVER", "Interface : %s", i.c_str());

	while (running)
	{	    
		if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		{
			log::Log::log(log::Log::LEVEL_ERROR, "DNSSERVER", "socket fail %d", errno);
			return NULL;
		}

		u_int yes = 1;

		if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) < 0)
		{
			log::Log::log(log::Log::LEVEL_ERROR, "DNSSERVER", "setsockopt reuse fail %d", errno);
			close(fd);
			return NULL;
		}

		struct sockaddr_in addr;
		memset(&addr, 0, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		addr.sin_addr.s_addr = (iface.empty() ? htonl(INADDR_ANY) : inet_addr(iface.c_str()));

		if (bind(fd,(struct sockaddr *)&addr, sizeof(addr)) < 0)
		{
			log::Log::log(log::Log::LEVEL_ERROR, "DNSSERVER", "bind fail %d", errno);
			close(fd);
			return NULL;
		}

		struct ip_mreq mreq;
		mreq.imr_multiaddr.s_addr = inet_addr(mDNS_GROUP.c_str());
		mreq.imr_interface.s_addr = (iface.empty() ? htonl(INADDR_ANY) : inet_addr(iface.c_str()));

		if (setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0)
		{
			log::Log::log(log::Log::LEVEL_ERROR, "DNSSERVER", "setsockopt add member fail %d", errno);
			close(fd);
			return NULL;
		}

		socklen_t addrlen;
		int nbytes;
		char * msgbuf = new char[BUFFER_SIZE];

    
		log::Log::log(log::Log::LEVEL_ERROR, "DNSSERVER", "starting running");

        memset(msgbuf, 0, BUFFER_SIZE);

        addrlen = sizeof(addr);
        if ((nbytes = recvfrom(fd, msgbuf, BUFFER_SIZE, 0, (struct sockaddr *)&addr, &addrlen)) < 0)
        {        
			delete msgbuf;
			close(fd);
			return NULL;
        }

		log::Log::log(log::Log::LEVEL_ERROR, "DNSSERVER", "recv %d", nbytes);

        unsigned char * name = parsePacket((unsigned char *)msgbuf);
        if (name != NULL)
        {
			log::Log::log(log::Log::LEVEL_ERROR, "DNSSERVER", "parse name %s", name);

            unsigned char * send_buf = NULL;
            int send_size = mDNSPacket(name, &send_buf);

            /*for (int i = 0; i < send_size; ++i) {
                if (i%16 == 0) {
                    printf("\n");
                }
                printf("%02x ", send_buf[i]);

            }*/

			memset(&addr, 0, sizeof(addr));
			addr.sin_family = AF_INET;
			addr.sin_port = htons(port);
			addr.sin_addr.s_addr = inet_addr(mDNS_GROUP.c_str());

			log::Log::log(log::Log::LEVEL_ERROR, "DNSSERVER", "send to %d", send_size);

            int iret = sendto(fd, send_buf, send_size, 0, (struct sockaddr *)&addr, addrlen);
            if (-1 == iret)
            {
				close(fd);
				delete msgbuf;
				delete send_buf;
				return NULL;
            }
            delete send_buf;
        }
		delete msgbuf;
		close(fd);
    }
    return NULL;
}



#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
}
#endif


int startServer()
{
    pthread_t t_mdns_thread;

	running = 1;

	log::Log::log(log::Log::LEVEL_DEBUG, "DNSSERVER", "start mDNS Server \n");

    pthread_create(&t_mdns_thread, NULL, &mDNS, NULL);
	
    pthread_join(t_mdns_thread, NULL);
    pthread_cancel(t_mdns_thread);
    return 0;
}

int stopServer() {
	running = 0;
	close(fd);
	return 0;
}
