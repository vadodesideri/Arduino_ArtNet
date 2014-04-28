#ifndef constants_h
#define constants_h

#define ARTNET_UDP_PORT		0x1936

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

#endif