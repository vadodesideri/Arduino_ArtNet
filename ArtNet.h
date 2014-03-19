/*
 *  ArtNet.h
 *
 *  Created by Tobias Ebsen
 *
 *  Implementation of the Art-Net protocol for use with the Arduino platform.
 *
 *  This file is free software; you can redistribute it and/or modify
 *  it under the terms of GNU General Public License version 3 as
 *  published by the Free Software Foundation.
 *
 *  Art-Net(TM) Designed by and Copyright Artistic Licence Holdings Ltd
 *
 */

#ifndef ArtNet_h
#define ArtNet_h

#include <Ethernet.h>
#include <EthernetUdp.h>

#define ARTNET_OPCODE_POLL          0x2000
#define ARTNET_OPCODE_POLLREPLY     0x2100
#define ARTNET_OPCODE_DMX           0x5000
#define ARTNET_OPCODE_IPPROG        0xF800
#define ARTNET_OPCODE_IPREPLY       0xF900
#define ARTNET_OPCODE_ADDRESS       0x6000
#define ARTNET_OPCODE_TODREQUEST    0x8000
#define ARTNET_OPCODE_TODDATA       0x8100

#define ARTNET_TYPE_DMX		0
#define ARTNET_TYPE_MIDI	1
#define ARTNET_TYPE_AVAB	2
#define ARTNET_TYPE_CMX		3
#define ARTNET_TYPE_ADB		4
#define ARTNET_TYPE_ARTNET	5

#define ARTNET_TYPE_INPUT	0x40
#define ARTNET_TYPE_OUTPUT	0x80

#define ARTNET_IPCMD_PROGRAM    0x80
#define ARTNET_IPCMD_DHCP       0x40
#define ARTNET_IPCMD_DEFAULT    0x08
#define ARTNET_IPCMD_IP         0x04
#define ARTNET_IPCMD_SUBNET     0x02
#define ARTNET_IPCMD_PORT       0x01

#define ARTNET_DHCP_ENABLED     0x40

typedef struct _artnet_header {
	uint8_t  id[8];
    uint16_t opCode;
} artnet_header;

typedef struct _artnet_poll {
	uint8_t protVerHi;
	uint8_t protVerLo;
	uint8_t talkToMe;
	uint8_t priority;
} artnet_poll;

typedef struct _artnet_poll_reply {
    uint8_t  ip[4];
    uint16_t port;
    uint8_t  verHi;
    uint8_t  verLo;
    uint8_t  netSwitch;
    uint8_t  subSwitch;
    uint8_t  oemHi;
    uint8_t  oemLo;
    uint8_t  ubeaVer;
    uint8_t  status;
    uint8_t  estaManLo;
    uint8_t  estaManHi;
    char     shortName[18];
    char     longName[64];
    char     nodeReport[64];
    uint8_t  numPortsHi;
    uint8_t  numPortsLo;
    uint8_t  portTypes[4];
    uint8_t  goodInput[4];
    uint8_t  goodOutput[4];
    uint8_t  swIn[4];
    uint8_t  swOut[4];
    uint8_t  swVideo;
    uint8_t  swMacro;
    uint8_t  swRemote;
    uint8_t  spare[3];
    uint8_t  style;
    uint8_t  mac[6];
    uint8_t  bindIp[4];
    uint8_t  bindIndex;
    uint8_t  status2;
    uint8_t  filler[26];
} artnet_poll_reply;

typedef struct _artnet_dmx_header {
	uint8_t  protVerHi;
	uint8_t  protVerLo;
	uint8_t  sequence;
	uint8_t  physical;
	uint8_t  subUni;
	uint8_t  net;
	uint16_t length;
} artnet_dmx_header;

typedef struct _artnet_ip_prog {
	uint8_t  protVerHi;
	uint8_t  protVerLo;
    uint8_t  filler1;
    uint8_t  filler2;
    uint8_t  command;
    uint8_t  filler4;
    uint8_t  ip[4];
    uint8_t  subnet[4];
    uint16_t port;
    uint8_t  status;
    uint8_t  spare[7];
} artnet_ip_prog;

typedef struct _artnet_address {
	uint8_t protVerHi;
	uint8_t protVerLo;
    uint8_t netSwitch;
    uint8_t filler2;
    char shortName[18];
    char longName[64];
    uint8_t swIn[4];
    uint8_t swOut[4];
    uint8_t subSwitch;
    uint8_t swVideo;
    uint8_t command;
} artnet_address;

typedef struct _artnet_tod_request {
    uint8_t protVerHi;
    uint8_t protVerLo;
    uint8_t filler[2];
    uint8_t spare[7];
    uint8_t net;
    uint8_t command;
    uint8_t addCount;
} artnet_tod_request;

typedef struct _artnet_tod_data {
    uint8_t  protVerHi;
    uint8_t  protVerLo;
    uint8_t  filler[2];
    uint8_t  spare[7];
    uint8_t  net;
    uint8_t  command;
    uint8_t  address;
    uint16_t uidTotal;
    uint8_t  blockCount;
    uint8_t  uidCount;
} artnet_tod_data;

typedef struct _ArtnetConfig {
    uint8_t  mac[6];
    uint8_t  ip[4];
    uint8_t  mask[4];
    uint16_t udpPort;
    uint8_t  dhcp;
    uint8_t  net;
    uint8_t  subnet;
    char     shortName[18];
    char     longName[64];
    uint8_t  numPorts;
    uint8_t  portTypes[4];
    uint8_t  portAddrIn[4];
    uint8_t  portAddrOut[4];
    uint8_t  verHi;
    uint8_t  verLo;
} ArtNetConfig;

class ArtNet {
public:

    ArtNet(uint16_t bufferSize = 1024);
    ArtNet(ArtNetConfig & config, uint16_t bufferSize = 1024);
	
	void begin();
    void begin(const uint8_t* mac);
	void stop();
	
    void setVersion(uint8_t verHi, uint8_t verLo);
	void setNet(uint8_t net);
	void setSubNet(uint8_t subnet);
	void setShortName(const char *shortName);
	void setLongName(const char *longName);
	void setNumPorts(uint8_t numPorts);
	void setPortType(uint8_t port, uint8_t type);
	void setPortAddress(uint8_t port, uint8_t address);
	void setMac(const uint8_t *mac);
    	
	int parsePacket();
	
	uint16_t getOpCode();
    void     setOpCode(uint16_t opCode);
    
    void*    getData();
    
    // DMX Accessors
    uint8_t* getDmxData();
    uint16_t getDmxLength();
    uint8_t  getDmxPort();
    
    // IpProg Accessors
    uint8_t  getIpCommand();
    
    // Member Accessors
    char*    getShortName();
    char*    getLongName();
    uint8_t  getPortType(uint8_t port);
    uint8_t  getPortAddress(uint8_t port);
    uint8_t  getPortOutFromUni(uint8_t uni);
	   
    void readPoll();
    void readPollReply();
    void readDmx();
    void readIpProg();
    void readAddress();
    void readTodRequest();
	
	void flush();
	
	void sendPollReply();
    void sendIpProgReply();
    void sendTodData();

    void handlePoll();
    void handlePollReply();
    void handleDmx();
    void handleIpProg();
    void handleAddress();
    void handleAny();
    void handleTodRequest();

private:
	EthernetUDP udp;
    
    uint8_t* buffer;
    uint16_t bufferSize;
    
    /*uint8_t  verHi;
    uint8_t  verLo;
    uint8_t  net;
    uint8_t  subnet;
    char     shortName[18];
    char     longName[64];
    uint8_t  numPorts;
    uint8_t  portTypes[4];
    uint8_t  portAddrIn[4];
    uint8_t  portAddrOut[4];
    const uint8_t *mac;*/
    ArtNetConfig *config;
};

#endif