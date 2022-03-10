#ifndef mDNS_h
#define mDNS_h


struct mDNSHeader {
    unsigned short transactionID;
    unsigned short flags;

    unsigned short questions;
    unsigned short answers;
    unsigned short authorityRRs;
    unsigned short additionalRRs;


};

struct mDNS {
    mDNSHeader header;
    unsigned char *data;
};

struct mDNSQuery {
	unsigned char *name;
	unsigned short type;
	unsigned short classAndQu;
};

struct mDNSRecordHeader {
    unsigned char *name;
    unsigned short type;
    unsigned short classAndCache;
    unsigned int timetoLive;
};

struct mDNSAnswers {
    unsigned char *data;
};

static const unsigned short TYPE_PTR = 0x000c;


struct mDNSAdditionalRecordsTXTItem {
    unsigned char txtLength;
    unsigned char *txt;
};


struct mDNSAdditionalRecordsTXTData {
    mDNSAdditionalRecordsTXTItem *items;
    unsigned short itemsCount;
};

static const unsigned short TYPE_TXT = 0x0010;

struct mDNSAdditionalRecordsSRVData {
    unsigned short property;
    unsigned short weight;
    unsigned short port;
    unsigned char *target;
};

static const unsigned short TYPE_SRV = 0x0021;

struct mDNSAdditionalRecordsAData {
    unsigned int address;
};

static const unsigned short TYPE_A = 0x0001;


struct mDNSRecord {
    mDNSRecordHeader header;
    unsigned short dataLength;
    unsigned char *data;
};


int mDNSPacket(unsigned char *name, unsigned char **packet);

unsigned char* parsePacket(unsigned char * packet);

#endif
