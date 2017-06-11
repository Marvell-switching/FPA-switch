/*
 *  Copyright (C) 2016. Marvell International Ltd. ALL RIGHTS RESERVED.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License"); you may
 *    not use this file except in compliance with the License. You may obtain
 *    a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 *    THIS CODE IS PROVIDED ON AN  *AS IS* BASIS, WITHOUT WARRANTIES OR
 *    CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 *    LIMITATION ANY IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS
 *    FOR A PARTICULAR PURPOSE, MERCHANTABLITY OR NON-INFRINGEMENT.
 *
 *    See the Apache Version 2.0 License for specific language governing
 *    permissions and limitations under the License.
 *
 */
/*
********************************************************************************
* fpaLibTypes.h
*
* DESCRIPTION:
*       OpenFlow FPA Library datatypes.
*
* FILE REVISION NUMBER:
*       $Revision: 04 $
*
*******************************************************************************/
#ifndef INCLUDE_FPA_DATATYPES_H
#define INCLUDE_FPA_DATATYPES_H


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
 
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

#undef IN
#define IN
#undef OUT
#define OUT
#undef INOUT
#define INOUT

#define FPA_INPORT_EXACT_MASK       0xFFFFFFFFu
#define FPA_INPORT_FIELD_MASK       0x00000000u
#define FPA_INPORT_INDEX_MASK       0x0000FFFFu
#define FPA_INPORT_TYPE_MASK        0xFFFF0000u
#define FPA_IPV4_ADDR_EXACT_MASK    0xFFFFFFFFu
#define FPA_IPV4_ADDR_FIELD_MASK    0x00000000u

#define FPA_FLOW_VLAN_MASK_TAG      0x1FFF
#define FPA_FLOW_VLAN_MASK_UNTAG    0x1000
#define FPA_FLOW_VLAN_IGNORE_VAL    0xFFFF
#define FPA_FLOW_INVALID_VAL        0xFFFFFFFF
 
#define FPA_MAC_ADDRESS_SIZE    6
#define FPA_IPV6_ADDRESS_SIZE   16

#define FPA_OUTPUT_CONTROLLER           0xfffffffd

/* MAC address type */
typedef struct
{
  uint8_t     addr[FPA_MAC_ADDRESS_SIZE];
} FPA_MAC_ADDRESS_STC;

#define FPA_MAC_ADDRESS_IS_BC(macAddr)  ((macAddr.addr[0] == 0xFF) && (macAddr.addr[1] == 0xFF) && (macAddr.addr[2] == 0xFF) && (macAddr.addr[3] == 0xFF) && (macAddr.addr[4] == 0xFF) && (macAddr.addr[5] == 0xFF))
#define FPA_MAC_ADDRESS_IS_EMPTY(macAddr)  ((macAddr.addr[0] == 0) && (macAddr.addr[1] == 0) && (macAddr.addr[2] == 0) && (macAddr.addr[3] == 0) && (macAddr.addr[4] == 0) && (macAddr.addr[5] == 0))
#define FPA_MAC_ADDRESS_IS_INVALID(macAddr) (FPA_MAC_ADDRESS_IS_BC(macAddr) || FPA_MAC_ADDRESS_IS_EMPTY(macAddr)) 

/*
 * Typedef: enum FPA_STATUS
 *
 * Description: Values to be returned by all FPA functions
 *
 */
typedef enum
{
    FPA_ERROR                 = (-1),
    FPA_OK                    = (0x00), /* Operation succeeded */
    FPA_FAIL                  = (0x01), /* Operation failed    */

    FPA_BAD_VALUE             = (0x02), /* Illegal value        */
    FPA_OUT_OF_RANGE          = (0x03), /* Value is out of range*/
    FPA_BAD_PARAM             = (0x04), /* Illegal parameter in function called  */
    FPA_BAD_PTR               = (0x05), /* Illegal pointer value                 */
    FPA_BAD_SIZE              = (0x06), /* Illegal size                          */
    FPA_BAD_STATE             = (0x07), /* Illegal state of state machine        */
    FPA_SET_ERROR             = (0x08), /* Set operation failed                  */
    FPA_GET_ERROR             = (0x09), /* Get operation failed                  */
    FPA_CREATE_ERROR          = (0x0A), /* Fail while creating an item           */
    FPA_NOT_FOUND             = (0x0B), /* Item not found                        */
    FPA_NO_MORE               = (0x0C), /* No more items found                   */
    FPA_NO_SUCH               = (0x0D), /* No such item                          */
    FPA_TIMEOUT               = (0x0E), /* Time Out                              */
    FPA_NO_CHANGE             = (0x0F), /* The parameter is already in this value*/
    FPA_NOT_SUPPORTED         = (0x10), /* This request is not support           */
    FPA_NOT_IMPLEMENTED       = (0x11), /* This request is not implemented       */
    FPA_NOT_INITIALIZED       = (0x12), /* The item is not initialized           */
    FPA_NO_RESOURCE           = (0x13), /* Resource not available = (memory ...),   */
    FPA_FULL                  = (0x14), /* Item is full = (Queue or table etc...),  */
    FPA_EMPTY                 = (0x15), /* Item is empty = (Queue or table etc...), */
    FPA_INIT_ERROR            = (0x16), /* Error occured while INIT process      */
    FPA_NOT_READY             = (0x1A), /* The other side is not ready yet       */
    FPA_ALREADY_EXIST         = (0x1B), /* Tried to create existing item         */
    FPA_OUT_OF_CPU_MEM        = (0x1C), /* Cpu memory allocation failed.         */
    FPA_ABORTED               = (0x1D), /* Operation has been aborted.           */
    FPA_NOT_APPLICABLE_DEVICE = (0x1E), /* API not applicable to device , can be returned only on devNum parameter  */

    FPA_UNFIXABLE_ECC_ERROR   = (0x1F), /* CPSS detected memory ECC error that can't be fixed. */
    FPA_UNFIXABLE_BIST_ERROR  = (0x20), /* Built-in self-test detected unfixable error */
    FPA_CHECKSUM_ERROR        = (0x21), /* checksum doesn't fits received data */
    FPA_DSA_PARSING_ERROR     = (0x22), /* DSA tag parsing error */ 

    FPA_STATUS_MAX              = 0xFFFFFFFF /* set enum type of unsigned int */
} FPA_STATUS;

/*
 * typedef: enum FPA_FLOW_TABLE_ENTRY_TYPE_ENT
 *
 * Description: Enumeration of FPA flow table entry type.
 *
 * Enumerations:
 *  FPA_FLOW_TABLE_TYPE_VLAN_E        		-   VLAN filtering and assignment. 
 *  FPA_FLOW_TABLE_TYPE_TERMINATION_E 		-   MAC2ME termination.
 *  FPA_FLOW_TABLE_TYPE_PCL0_E        		-   TCAM table pcl0.
 *  FPA_FLOW_TABLE_TYPE_PCL1_E        		-   TCAM table pcl0.
 *  FPA_FLOW_TABLE_TYPE_PCL2_E        		-   TCAM table pcl0.
 *  FPA_FLOW_TABLE_TYPE_L2_BRIDGING_E 		-   FDB L2 bridging forwarding table entry.
 *  FPA_FLOW_TABLE_TYPE_L2_FDB_E            -   All mac address in fdb table (static+dynamic)
 *  FPA_FLOW_TABLE_TYPE_L3_UNICAST_E  		-   L3 IPv4 unicast routing table entry.
 *  FPA_FLOW_TABLE_TYPE_L3_UNICAST_IPV6_E  	-   L3 IPv6 unicast routing table entry.
 *  FPA_FLOW_TABLE_TYPE_EPL_E         		-   egress policy table entry.
 *
 * Comments:
 *         None.
 */
typedef enum
{
    FPA_FLOW_TABLE_TYPE_CONTROL_PKT_E,
    FPA_FLOW_TABLE_TYPE_VLAN_E,
    FPA_FLOW_TABLE_TYPE_TERMINATION_E,
    FPA_FLOW_TABLE_TYPE_PCL0_E,
    FPA_FLOW_TABLE_TYPE_PCL1_E,
    FPA_FLOW_TABLE_TYPE_PCL2_E,
    FPA_FLOW_TABLE_TYPE_VR_ID_E,
    FPA_FLOW_TABLE_TYPE_L2_BRIDGING_E,
    FPA_FLOW_TABLE_TYPE_L2_FDB_E,
    FPA_FLOW_TABLE_TYPE_L3_UNICAST_E, /* IPv4 table */
	FPA_FLOW_TABLE_TYPE_L3_UNICAST_IPV6_E,
    FPA_FLOW_TABLE_TYPE_EPCL_E,
    FPA_FLOW_TABLE_TYPE_LAST_E = FPA_FLOW_TABLE_TYPE_EPCL_E,
    FPA_FLOW_TABLE_TYPE_MAX = 0xFFFFFFFF
} FPA_FLOW_TABLE_ENTRY_TYPE_ENT;

#define FPA_FLOW_TABLE_MAX  (FPA_FLOW_TABLE_TYPE_LAST_E+1)

/* pcl actions bits */
#define FPA_FLOW_TABLE_PCL_ACTION_OUTPUT_FLAG          (1 << 0)
#define FPA_FLOW_TABLE_PCL_ACTION_GROUP_FLAG           (1 << 1)
#define FPA_FLOW_TABLE_PCL_ACTION_QUEUE_FLAG           (1 << 2)
#define FPA_FLOW_TABLE_PCL_ACTION_VLAN_PCP_FLAG        (1 << 3)
#define FPA_FLOW_TABLE_PCL_ACTION_DSCP_FLAG            (1 << 4)
#define FPA_FLOW_TABLE_PCL_ACTION_METER_FLAG           (1 << 5)
#define FPA_FLOW_TABLE_PCL_ACTION_METADATA_FLAG        (1 << 6)
#define FPA_FLOW_TABLE_PCL_ACTION_CLEAR_ACTION_FLAG    (1 << 7)
#define FPA_FLOW_TABLE_PCL_ACTION_GOTO_FLAG            (1 << 8)
#define FPA_FLOW_TABLE_PCL_ACTION_VLAN_ID_FLAG         (1 << 9)
#define FPA_FLOW_TABLE_PCL_ACTION_VR_ID_FLAG           (1 << 10)

#define FPA_FLOW_TABLE_METADATA_DATA_BIT               (0xFFF)
#define FPA_FLOW_TABLE_METADATA_MAC2ME_BIT             (1 << 12)
/*
 * typedef: struct FPA_FLOW_TABLE_ENTRY_VLAN_STC
 *
 * Description: 
 *
 * Fields:
 *      inPort   - Ingress port. Numerical representation of incoming port, starting at 1. 
 *                 This may be a physical or switch-dened logical port..
 *
 */
typedef struct 
{
  /* Match Fields  */
  uint32_t    inPort;
  uint16_t    vlanId;       /* VLAN-ID from 802.1Q header. The CFI bit indicate */
                            /* the presence of a valid VLAN-ID.                 */
  uint16_t    vlanIdMask;

  /* Write Actions Instruction */
  uint16_t    newTagVid;    /* VLAN VID to assign or (-1) no change */
  uint16_t    newTagPcp;    /* VLAN-PCP from 802.1Q header or (-1) no change */

  /* GOTO instruction */
  uint32_t   gotoTableNo;   /* the next table in the lookup pipeline or 0 to drop */

} FPA_FLOW_TABLE_ENTRY_VLAN_STC;

/*
 * typedef: struct FPA_FLOW_TABLE_ENTRY_VR_ID_STC
 *
 * Description: add virtual router.
 *              only one of the critria inPort or vlanId can be valid
 *
 * Fields:
 *      inPort   - Ingress port. Numerical representation of incoming port, starting at 1. 
 *                 This may be a physical or switch-dened logical port..
 *
 */
typedef struct 
{
  /* Match Fields  */
  uint32_t    inPort;
  uint32_t    inPortMask;
  uint16_t    vlanId;       /* VLAN-ID field. The CFI bit indicates a valid one. */
  uint16_t    vlanIdMask;   

  /* Write Actions Instruction */
  uint16_t    assignVrId;   /* Assign VR-ID metadata if it current value is 0. */

  /* GOTO instruction */
  uint32_t   gotoTableNo;   /* the next table in the lookup pipeline */

} FPA_FLOW_TABLE_ENTRY_VR_ID_STC;

/*
 * typedef: struct FPA_FLOW_TABLE_MATCH_FIELDS_TERMINATION_STC
 *
 * Description: 
 *
 * Fields:
 *      inPort   - Ingress port. Numerical representation of incoming port, starting at 1. 
 *                 This may be a physical or switch-dened logical port..
 *
 */
typedef struct 
{
  
  uint32_t              inPort;         /*  Ingress Port number */
  uint32_t              inPortMask;     /* Field maskable only */

  uint16_t              etherType;      /* 0x0800 or 0x86dd */
  uint16_t              etherTypeMask;  /* Field maskable only */

  FPA_MAC_ADDRESS_STC   destMac;
  FPA_MAC_ADDRESS_STC   destMacMask;

  uint16_t              vlanId;
  uint16_t              vlanIdMask;     /* Field maskable only */

} FPA_FLOW_TABLE_MATCH_FIELDS_TERMINATION_STC;

/*
 * typedef: struct FPA_FLOW_TABLE_ENTRY_TERMINATION_STC
 *
 * Description: 
 *
 * Fields:
 *      match       - flow entry match fields.
 *      outputPort  - must be CONTROLLER, set to 0 otherwise
 *      gotoTableNo - the next table in the lookup pipeline or 0 to drop 
 *      
 *
 */
typedef struct
{
  FPA_FLOW_TABLE_MATCH_FIELDS_TERMINATION_STC  match;

  /* Write-Metadata Instruction */
  uint64_t    metadataValue;        /* only MAC2ME bit valid */
  uint64_t    metadataMask;

  /* GOTO instruction */
  uint32_t   gotoTableNo; 

} FPA_FLOW_TABLE_ENTRY_TERMINATION_STC;

/*
 * typedef: struct FPA_FLOW_TABLE_ENTRY_L2_BRIDGING_STC
 *
 * Description: 
 *
 * Fields:
 *      match       - flow entry match fields.
 *      outputPort  - must be CONTROLLER, set to 0 otherwise
 *      groupId     - must be one of L2: Interface,  Multicast or Flood. If no - drop.
 *      gotoTableNo - the next table in the lookup pipeline 
 *      clearActions - used w/o group for drop  (if both - Default:erroor Option: Group)
 *                      drop - "hard drop"
 *
 */
typedef struct
{
  /* Match Fields */
  struct
  {
    uint16_t    vlanId;
    uint16_t    vlanIdMask;

    FPA_MAC_ADDRESS_STC destMac;
    FPA_MAC_ADDRESS_STC destMacMask;  /* UNKNOWN rule if masked */
  } match;

  /* Apply-Action(s) instruction */
  uint32_t    outputPort;

  /* Write-Actions Instruction */
  uint32_t    groupId; 

  /* GOTO instruction */
  uint32_t   gotoTableNo; 

  uint32_t   clearActions;

} FPA_FLOW_TABLE_ENTRY_L2_BRIDGING_STC;

/*
 * typedef: struct FPA_FLOW_TABLE_ENTRY_L3_UNICAST_STC
 *
 * Description: IPv4 and IPv6 unicast routing
 *
 * Fields:
 *      etherType   - must be 0x0800 or 0x86dd
 *      vrfId       - VRF-ID, default is 0
 *      dstIp4      - IPv4 unicast address
 *      dstIp6      - IPv6 unicast address
 *      groupId     - must be L3 Unicast category group
 *      gotoTableNo - the next table in the lookup pipeline or 0 to drop 
 *
 */
typedef struct fpaUnicastRoutingFlowEntry_s
{
  /* Match Fields */
  struct
  {
      uint16_t          etherType;
      uint16_t          vrfId;
      in_addr_t         dstIp4;
      in_addr_t         dstIp4Mask;
      struct in6_addr   dstIp6;
      struct in6_addr   dstIp6Mask;      
  } match;
 
  /* Apply-Action(s) instruction */
  uint32_t    outputPort;

  /* Write-Actions Instruction */
  uint32_t    groupId; 

  uint32_t   clearActions;

  /* GOTO instruction */
  uint32_t   gotoTableNo; 

} FPA_FLOW_TABLE_ENTRY_L3_UNICAST_STC;


typedef struct
{
 
  struct in6_addr   srcIp6;
  struct in6_addr   srcIp6Mask;

  struct in6_addr   dstIp6;
  struct in6_addr   dstIp6Mask;

  uint8_t     icmpV6Type; 
  uint8_t     icmpV6TypeMask;

  uint8_t     icmpV6Code;
  uint8_t     icmpV6CodeMask;

  struct in6_addr   ip6NdTarget;
  struct in6_addr   ip6NdTargetMask;

  FPA_MAC_ADDRESS_STC ip6NdSll;
  FPA_MAC_ADDRESS_STC ip6NdSllMask;

  FPA_MAC_ADDRESS_STC ip6NdTll;
  FPA_MAC_ADDRESS_STC ip6NdTllMask;
  
} FPA_FLOW_TABLE_MATCH_FIELDS_ACL_POLICY_IPV6_STC;

/*
 * typedef: struct FPA_FLOW_TABLE_MATCH_FIELDS_ACL_POLICY_STC
 *
 * Description: 
 *
 * Fields:
 */
typedef struct
{
  uint32_t    inPort;
  uint32_t    inPortMask;
  
  uint32_t    outPort;      /* used only for epcl */
  uint32_t    outPortMask;  /* used only for epcl */

  FPA_MAC_ADDRESS_STC srcMac;
  FPA_MAC_ADDRESS_STC srcMacMask;

  FPA_MAC_ADDRESS_STC dstMac;
  FPA_MAC_ADDRESS_STC dstMacMask;

  uint16_t    etherType;
  uint16_t    etherTypeMask;
  
  uint16_t    vlanId;
  uint16_t    vlanIdMask;

  uint16_t    vlanPcp;     
  uint16_t    vlanPcpMask;

  in_addr_t   srcIp4;
  in_addr_t   srcIp4Mask;

  in_addr_t   dstIp4;
  in_addr_t   dstIp4Mask;

  uint16_t    ipProtocol;  
  uint16_t    ipProtocolMask;

  uint16_t    dscp;
  uint16_t    dscpMask;

  uint32_t    srcL4Port;  
  uint32_t    srcL4PortMask;

  uint32_t    dstL4Port;
  uint32_t    dstL4PortMask;

  uint8_t     ipEcn;
  uint8_t     ipEcnMask;
  
  uint8_t     icmpV4Type; 
  uint8_t     icmpV4TypeMask;

  uint8_t     icmpV4Code;
  uint8_t     icmpV4CodeMask;
  
  uint16_t    arpOpcode;
  uint16_t    arpOpcodeMask;

  uint32_t    arpSpa;
  uint32_t    arpSpaMask;
  
  uint32_t    arpTpa;
  uint32_t    arpTpaMask;
 
  FPA_MAC_ADDRESS_STC arpSmac;
  FPA_MAC_ADDRESS_STC arpSmacMask;

  FPA_MAC_ADDRESS_STC arpTmac;
  FPA_MAC_ADDRESS_STC arpTmacMask;

  FPA_FLOW_TABLE_MATCH_FIELDS_ACL_POLICY_IPV6_STC ipv6;
  
} FPA_FLOW_TABLE_MATCH_FIELDS_ACL_POLICY_STC;

/*
 * typedef: struct FPA_FLOW_TABLE_ENTRY_TERMINATION_STC
 *
 * Description: 
 *
 * Fields:
 *      match       - flow entry match fields.
 *      outputPort  - must be CONTROLLER, set to 0 otherwise
 *      gotoTableNo - the next table in the lookup pipeline or 0 to drop 
 *      
 *
 */
typedef struct
{
  FPA_FLOW_TABLE_MATCH_FIELDS_ACL_POLICY_STC  match;

  /* Instructions - flags bitmap */
  uint32_t    instructionFlags; /* 1 - instruction data valid */


  /* Meter */
  uint32_t    meterId;          /* meter identifier to apply to the flow (rate limiter) */

  /* Apply-Actions instructions */
  uint32_t    outputPort;  

  /* Write-Actions instruction */
  uint32_t    groupId;      
  uint8_t     queueId;          /* data for SET_QUEUE action, exclusive with vrId */
  uint8_t     vlanPcp;          /* data for SET_VLAN_PCP action */
  uint8_t     dscp;             /* data for SET_IP_DSCP action */
  uint16_t    vlanId;          /* data for SET_VLAN_ID action */
  uint16_t    vrId;             /* VR-ID metadata, exclusive with groupId */

  /* Write-Metadata instruction */
  uint64_t    metadataValue;    /* only MAC2ME bit valid */
  uint64_t    metadataMask;

  /* Clear-Actions instruction */
  uint32_t    clearActions;     /* packet dropped (all other instructions ignored) */

  /* GOTO instruction */
  uint32_t   gotoTableNo; 

} FPA_FLOW_TABLE_ENTRY_ACL_POLICY_STC;



/******************************************************************************* 
                            Control Packets flow
*******************************************************************************/
/*
 * typedef: enum FPA_FLOW_TABLE_ENTRY_TYPE_ENT
 *
 * Description: Enumeration of FPA Control Packets flow table
 *              entry type.
 *
 * Enumerations:
 *
 * Comments:
 *         None.
 */
typedef enum
{
  FPA_CONTROL_PKTS_TYPE_IEEE_RESERVED_MULTICAST_E = 1,
  FPA_CONTROL_PKTS_TYPE_PROPRIETRY_L2_MULTICAST_E,
  FPA_CONTROL_PKTS_TYPE_IGMP_CTRL_MESSAGES_E,
  FPA_CONTROL_PKTS_TYPE_IPV6_MLD_ICMP_MESSAGES_E,
  FPA_CONTROL_PKTS_TYPE_UDP_BROADCAST_CTRL_E,
  FPA_CONTROL_PKTS_TYPE_ARP_REQUEST_MESSAGES_E,
  FPA_CONTROL_PKTS_TYPE_ARP_RESPONSE_MESSAGES_E,
  FPA_CONTROL_PKTS_TYPE_IPV6_NEIGHBOR_SOLICITATION_E,
  FPA_CONTROL_PKTS_TYPE_IPV4_LINK_LOCAL_E,
  FPA_CONTROL_PKTS_TYPE_IPV6_LINK_LOCAL_E,
  FPA_CONTROL_PKTS_TYPE_RIPV1_CTRL_MESSAGES_E,
  FPA_CONTROL_PKTS_ENTRY_TYPE_LAST = FPA_CONTROL_PKTS_TYPE_RIPV1_CTRL_MESSAGES_E,
  FPA_CONTROL_PKTS_ENTRY_TYPE_MAX = 0xFFFFFFFF
} FPA_CONTROL_PKTS_ENTRY_TYPE_ENT;

/*
 * typedef: struct FPA_FLOW_TABLE_MATCH_FIELDS_CONTROL_PKTS_STC
 *
 * Description: 
 *
 * Fields:
 */
typedef struct
{
  uint32_t    inPort;
  uint32_t    inPortMask;
  
  FPA_MAC_ADDRESS_STC dstMac;
  FPA_MAC_ADDRESS_STC dstMacMask;

  uint16_t    etherType;
  uint16_t    etherTypeMask;
  
  uint16_t    vlanId;
  uint16_t    vlanIdMask;

  uint16_t    ipProtocol;  
  uint16_t    ipProtocolMask;

  uint32_t    dstL4Port;
  uint32_t    dstL4PortMask;
  
  uint8_t     icmpV6Type; 
  uint8_t     icmpV6TypeMask;
  
  struct in_addr    dstIpv4;
  struct in_addr    dstIpv4Mask;

  struct in6_addr   dstIpv6;
  struct in6_addr   dstIpv6Mask;

} FPA_FLOW_TABLE_MATCH_FIELDS_CONTROL_PKTS_STC;

/*
 * typedef: struct FPA_FLOW_TABLE_ENTRY_CONTROL_PKTS_STC
 *
 * Description: 
 *
 * Fields:
 *      match       - flow entry match fields.
 *      outputPort  - must be CONTROLLER, set to 0 otherwise
 *      gotoTableNo - the next table in the lookup pipeline or 0 to drop 
 *      
 *
 */
typedef struct
{
  FPA_CONTROL_PKTS_ENTRY_TYPE_ENT               entry_type;
  FPA_FLOW_TABLE_MATCH_FIELDS_CONTROL_PKTS_STC  match;


  /* Apply-Actions instructions */
  uint32_t    outputPort;           /* 0 or Controller only*/

  /* Clear-Actions instruction */
  uint32_t    clearActions;     /* packet dropped (all other instructions ignored) */

  /* GOTO instruction */
  uint32_t   gotoTableNo; 

} FPA_FLOW_TABLE_ENTRY_CONTROL_PKTS_STC;


/*     Packet Action:   outputPort      clearActions  gotoTableNo 
 *       DROP               ---           TRUE          ---
 *       MIRROR           CONTROLLER      FALSE         >0
 *       TRAP             CONTROLLER      FALSE         =0
 *       FORWARD          =0              FALSE         >0
 */


/*
 * typedef: struct FPA_FLOW_TABLE_ENTRY_STC
 *
 * Description: Used in flow operations, represents the generic flow entry
 *
 * Fields:
 *      data         - flow entry data per flow table type.
 *      priority     - must be CONTROLLER, set to 0 otherwise
 *      flowModFlags - flags alter the way flow entries are managed,
 *                     for example FPA_SEND_FLOW_REM 
 *      
 *
 */
typedef struct
{
  FPA_FLOW_TABLE_ENTRY_TYPE_ENT     entryType;
  uint32_t                          priority;  

  union
  {
      FPA_FLOW_TABLE_ENTRY_CONTROL_PKTS_STC control_pkt;
      FPA_FLOW_TABLE_ENTRY_VLAN_STC         vlan;
      FPA_FLOW_TABLE_ENTRY_TERMINATION_STC  termination;
      FPA_FLOW_TABLE_ENTRY_L2_BRIDGING_STC  l2_bridging;
      FPA_FLOW_TABLE_ENTRY_VR_ID_STC        vr_id;
      FPA_FLOW_TABLE_ENTRY_L3_UNICAST_STC   l3_unicast;
      FPA_FLOW_TABLE_ENTRY_ACL_POLICY_STC   acl_policy;
  } data;

    uint32_t    timeoutHardTime;  /* 0 - no */
    uint32_t    timeoutIdleTime;  /* 0 - no */
    uint64_t    cookie;           /* 0 - no */
    uint32_t    flowModFlags;   

} FPA_FLOW_TABLE_ENTRY_STC;

/*
 * typedef: struct FPA_FLOW_ENTRY_COUNTERS_STC
 *
 * Description: Used in retrive per flow entry statistics. Counters are unsigned
 *      and wrap around with no overflow indicator. If a counter is not available
 *      in the switch, its value is the maximum field value (unsigned value -1).
 *
 * Fields:
 *      packetCount - number of packets, counting all packets processed by the flow.
 *      byteCount   - number of bytes, counting all packets processed by the flow.
 *      durationSec - time the flow has been alive in seconds.
 * 
 */
typedef struct 
{
    uint64_t packetCount; 
    uint64_t byteCount;  
    uint32_t durationSec;
} FPA_FLOW_ENTRY_COUNTERS_STC;

/*
 * typedef: struct FPA_FLOW_TABLE_COUNTERS_STC
 *
 * Description: Used in retrive per flow table statistics. Counters are unsigned
 *      and wrap around with no overflow indicator. If a counter is not available
 *      in the switch, its value is the maximum field value (unsigned value -1).
 *
 * Fields:
 *      packetLookupsCount - number of packets looked up in the table.
 *      packetMatchesCount - number of packets that hit the table.
 *      activeEntriesCount - number of active entries (reference counter).
 *
 */
typedef struct 
{
    uint64_t packetLookupsCount; 
    uint64_t packetMatchesCount; 
    uint32_t activeEntriesCount; 
} FPA_FLOW_TABLE_COUNTERS_STC;


/******************************************************************************* 
                            Group Table APIs
*******************************************************************************/
/*
 * typedef: enum FPA_GROUP_TABLE_ENTRY_TYPE_ENT
 *
 * Description: Enumeration of FPA group table category type.
 *
 * Enumerations:
 *      FPA_GROUP_L2_INTERFACE_E - Group type L2 Interface
 *      FPA_GROUP_L2_MULTICAST_E - Group type L2 Multicast
 *      FPA_GROUP_L2_FLOOD_E     - Group type L2 Flood 
 *      FPA_GROUP_L2_REWRITE_E   - Group type L2 Rewrite
 *      FPA_GROUP_L3_UNICAST_E   - Group type L3 Unicast
 *      FPA_GROUP_L3_ECMP_E      - Group type L3 ECMP
 *      FPA_GROUP_L3_INTERFACE_E - Group type L3 Interface
 *      FPA_GROUP_L2_LAG_E       - Group type L2 LAG
 *
 * Comments:
 *         None.
 */
typedef enum
{ 
    FPA_GROUP_L2_INTERFACE_E,
    FPA_GROUP_L2_MULTICAST_E,  
    FPA_GROUP_L2_FLOOD_E, 
    FPA_GROUP_L2_REWRITE_E,    
    FPA_GROUP_L3_UNICAST_E,
    FPA_GROUP_L3_ECMP_E,
    FPA_GROUP_L3_INTERFACE_E, 
    FPA_GROUP_L2_LAG_E, 
    FPA_GROUP_POE_E          = 15, 
    FPA_GROUP_LAST_E,
    FPA_GROUP_TYPE_MAX_E     = 0xFFFFFFFF
} FPA_GROUP_TABLE_ENTRY_TYPE_ENT;

/*
 *The Group Table contains one entry for each Group.  The table is indexed
 *  by the groupId which identifies the group entry.  Data is
 *  encoded into the groupId to specify the FPA group entry type
 *  and information required by FPA to configure the datapath.
 *
 * The groupId encoding method is:
 */

/*
 * typedef: struct FPA_GROUP_ENTRY_IDENTIFIER_STC
 *
 * Description: Group identifier fields according naming convention
 *
 * Fields:
 *      
 *
 */
typedef struct 
{
    uint32_t                          identifier;     /* [31: 0] */
    FPA_GROUP_TABLE_ENTRY_TYPE_ENT    groupType;      /* [31:28] */
    uint32_t                          vlanId;         /* [27:16] */
    uint32_t                          portNum;        /* [15: 0]  */
    uint32_t                          multicastId;    /* [15: 0]  */
    uint32_t                          index;          /* [27: 0]  */
} FPA_GROUP_ENTRY_IDENTIFIER_STC;

/*
 * typedef: enum FPA_GROUP_ALGORITHM_ENT
 *
 * Description: Enumeration of FPA group algorithm.
 *
 * Enumerations:
 *      FPA_GROUP_ALGORITHM_HASH_ECMP_E - CRC hash value based
 *      FPA_GROUP_ALGORITHM_INDX_ECMP_E - pseudo-random index
 *
 * Comments:
 *         None.
 */
typedef enum
{ 
    FPA_GROUP_ALGORITHM_HASH_ECMP_E, 
    FPA_GROUP_ALGORITHM_INDX_ECMP_E,
    FPA_GROUP_ALGORITHM_LAST_E = FPA_GROUP_ALGORITHM_INDX_ECMP_E,
} FPA_GROUP_ALGORITHM_ENT;

/*
 * typedef: struct FPA_GROUP_TABLE_ENTRY_STC
 *
 * Description: Format of entry in group table 
 *
 * Fields:
 *      groupIdentifier    - 32 bit opaque group identifier.
 *	    groupTypeSemantics - the ofp group type OFPGT_ALL =  All group. 
 *                                        OFPGT_SELECT =  Select group (ecmp). 
 *                                        OFPGT_INDIRECT =  Indirect group. 
 *                                        OFPGT_FF =  Fast failover group.
 *      selectionAlgorithm - load balancing mechanism
 *                           FPA_GROUP_ALGORITHM_HASH_ECMP_E  CRC hash value based
 *                           FPA_GROUP_ALGORITHM_INDX_ECMP_E  pseudo-random index
 *                           0 - default 
 *
 */
typedef struct
{
    uint32_t    groupIdentifier;
    uint32_t    groupTypeSemantics;
    uint32_t    selectionAlgorithm; /* 0 - default */
} FPA_GROUP_TABLE_ENTRY_STC;


/*
 * typedef: struct FPA_GROUP_COUNTERS_STC
 *
 * Description: Used in retrive a group statistics. Counters are unsigned
 *      and wrap around with no overflow indicator. If a counter is not available
 *      in the switch, its value is the maximum field value (unsigned value -1).
 *
 * Fields:
 *      packetCount - number of packets processed by the group.
 *      byteCount   - number of bytes processed by group.
 *      durationSec - time group has been alive in seconds.
 *      referenceCount - number of flows or groups that directly forward to this group.
 *
 */
typedef struct
{
    uint64_t  packetCount;
    uint64_t  byteCount;
    uint32_t  referenceCount;
    uint32_t  durationSec;  
} FPA_GROUP_COUNTERS_STC;


/*
 * typedef: struct FPA_GROUP_BUCKET_COUNTERS_STC
 *
 * Description: Used in retrive a group bucket statistics. Counters are unsigned
 *      and wrap around with no overflow indicator. If a counter is not available
 *      in the switch, its value is the maximum field value (unsigned value -1).
 *
 * Fields:
 *      packetCount - number of packets processed by the bucket.
 *      byteCount   - number of bytes processed by the bucket.
 *
 */
typedef struct
{
    uint64_t  packetCount;
    uint64_t  byteCount;
} FPA_GROUP_BUCKET_COUNTERS_STC;


/*
 * typedef: struct FPA_GROUP_BUCKET_L2_INTERFACE_STC
 *
 * Description: Represents IEEE 801.Q compliant L2_INTERFACE group bucket structure.
 *
 * Fields:
 *      outputPort       - physical output port number.
 *      popVlanTagAction - output port is untagged (1) or tagged (0) in VLAN of the
 *          group. Untagged input packet recieved default tag in VLAN Flow Table. 
 *
 */
typedef struct 
{
    uint32_t  outputPort;
    uint32_t  popVlanTagAction;
} FPA_GROUP_BUCKET_L2_INTERFACE_STC;

/*
 * typedef: struct FPA_GROUP_BUCKET_L2_REFERENCE_STC
 *
 * Description: Represents IEEE 801.Q compliant L2_INTERFACE group bucket structure.
 *
 * Fields:
 *      referenceGroupId - specify another group, for example in a multicast group or ecmp group
 *
 */
typedef struct 
{
    uint32_t    referenceGroupId;
} FPA_GROUP_BUCKET_L2_REFERENCE_STC;

/*
 * typedef: struct FPA_GROUP_BUCKET_L3_INTERFACE_STC
 *
 * Description: Represents IEEE 801.Q compliant L2_INTERFACE group bucket structure.
 *
 * Fields:
 *      outputPort       - physical output port number.
 *      popVlanTagAction - output port is untagged (1) or tagged (0) in VLAN of the
 *                         group. Untagged input packet recieved default tag in
 *                         VLAN Flow Table. 
 *
 */
typedef struct
{
    uint32_t              vlanId;
    FPA_MAC_ADDRESS_STC   srcMac;
} FPA_GROUP_BUCKET_L3_INTERFACE_STC;


typedef struct 
{
  uint32_t                refGroupId;  /* reference L2 interface */
  uint32_t              vlanId;
  uint32_t              mtu;
  FPA_MAC_ADDRESS_STC   srcMac;
  FPA_MAC_ADDRESS_STC   dstMac;
} FPA_GROUP_BUCKET_L3_UNICAST_STC;

typedef struct
{
  uint32_t                refGroupId;  /* reference L2 interface */
  uint32_t                vlanId;
  FPA_MAC_ADDRESS_STC   srcMac;
  FPA_MAC_ADDRESS_STC   dstMac;
} FPA_GROUP_BUCKET_L2_REWRITE_STC;


/*
 * typedef: enum FPA_GROUP_BUCKET_TYPE_ENT
 *
 * Description: Enumeration of FPA group bucket type.
 *
 * Enumerations:
 *      FPA_GROUP_BUCKET_L2_INTERFACE_E - Group bucket type L2 Interface
 *      FPA_GROUP_BUCKET_L2_REFERENCE_E - bucket used for group reference(l2 multicast or l3 ecmp)
 *
 * Comments:
 *         None.
 */
typedef enum
{ 
    FPA_GROUP_BUCKET_L2_INTERFACE_E, 
    FPA_GROUP_BUCKET_L2_REFERENCE_E,
    FPA_GROUP_BUCKET_L2_REWRITE_E,    
    FPA_GROUP_BUCKET_L3_UNICAST_E,
    FPA_GROUP_BUCKET_L3_INTERFACE_E,
    FPA_GROUP_BUCKET_TYPE_LAST_E,
    FPA_GROUP_BUCKET_TYPE_MAX_E     = 0xFFFFFFFF
} FPA_GROUP_BUCKET_TYPE_ENT;

/* Group types.  Values in the range [128, 255] are reserved for experimental
 * use. */
enum fpaGroupType {
    FPA_GROUP_ALL      = 0, /* All (multicast/broadcast) group.  */
    FPA_GROUP_SELECT   = 1, /* Select group. (ecmp)*/
    FPA_GROUP_INDIRECT = 2, /* Indirect group. */
    FPA_GROUP_FF       = 3, /* Fast failover group. */
};

/*
 * typedef: struct FPA_GROUP_BUCKET_ENTRY_STC
 *
 * Description: Represents group bucket.
 *
 * Fields:
 *      groupIdentifier - 32-bit identifier of the group container.
 *      index           - index of the group bucket in the group.
 *      type            - the bucket type. 
 *
 */
typedef struct
{
  uint32_t                  groupIdentifier;
  uint32_t                  index;
  FPA_GROUP_BUCKET_TYPE_ENT type;

  union
  {
    FPA_GROUP_BUCKET_L2_INTERFACE_STC  l2Interface;
    FPA_GROUP_BUCKET_L2_REFERENCE_STC  l2Reference;
    FPA_GROUP_BUCKET_L2_REWRITE_STC    l2Rewrite;    
    FPA_GROUP_BUCKET_L3_INTERFACE_STC  l3Interface;
    FPA_GROUP_BUCKET_L3_UNICAST_STC    l3Unicast;
  } data;

} FPA_GROUP_BUCKET_ENTRY_STC;


/******************************************************************************* 
                            Meter Table Section
*******************************************************************************/

#define FPA_METER_BANDS_MAX 2
/*
 * typedef: struct FPA_METER_COUNTERS_STC
 *
 * Description: Used in retrive per meter statistics. Counters are unsigned
 *      and wrap around with no overflow indicator. If counter is not available
 *      in the switch, its value is the maximum field value (unsigned value -1).
 *
 * Fields:
 *      flowReferenceCount  - number of flows bound to meter.
 *      durationSec         - time meter has been alive in seconds.
 *      inMeterPacketCount  - counts all packets processed by the meter
 *      inMeterByteCount    - bytes in all packets processed by the meter
 *      inBandPacketCount[] - array, number of packets in a band.
 *      inBandByteCount[]   - array, number of bytes in a band.      
 *
 */
typedef struct 
{
    uint32_t  flowReferenceCount;
    uint32_t  durationSec;
    uint64_t  inMeterPacketCount;
    uint64_t  inMeterByteCount;
    uint64_t  inBandPacketCount[FPA_METER_BANDS_MAX];
    uint64_t  inBandByteCount[FPA_METER_BANDS_MAX];
} FPA_METER_COUNTERS_STC;


/* Meter band types */
/*enum ofp_meter_band_type {
    OFPMBT_DROP            = 1,      / * Drop packet. * /
    OFPMBT_DSCP_REMARK     = 2,      / * Remark DSCP in the IP header. * /
    OFPMBT_EXPERIMENTER    = 0xFFFF  / * Experimenter meter band. * /
};*/

/*
 * typedef: struct FPA_METER_BAND_STC
 *
 * Description: Meter band 
 *
 * Fields:
 *      type -  OFPMBT_ band type supported values
 *              OFPMBT_DROP        = 1, Drop packet.
 *              OFPMBT_DSCP_REMARK = 2, Remark DSCP in the IP header.
 *      rate -  Rate for drop/remarking packets. value in kb/s
 *      burst_size - Size of bursts in bytes.
 *      prec_level - remark value.
 */
typedef struct
{
  uint16_t      type;
  uint32_t      rate;
  uint32_t      burst_size;
  uint8_t       prec_level;
} FPA_METER_BAND_STC;



/* Meter configuration flags */
/*enum ofp_meter_flags {
    OFPMF_KBPS    = 1 << 0,     / * Rate value in kb/s (kilo-bit per second). * /
    OFPMF_PKTPS   = 1 << 1,     / * Rate value in packet/sec. * /
    OFPMF_BURST   = 1 << 2,     / * Do burst size. * /
    OFPMF_STATS   = 1 << 3,     / * Collect statistics. * /
};*/

/*
 * typedef: struct FPA_METER_TABLE_ENTRY_STC
 *
 * Description: Meter table entry
 *
 * Fields:
 *      meterId - Meter instance
 *      flags   - Bitmap of OFPMF_* flags
 *      band    - bands array
 *
 */
typedef struct
{
  uint32_t              meterId;  
  uint16_t              flags;    
  FPA_METER_BAND_STC    band[FPA_METER_BANDS_MAX];
} FPA_METER_TABLE_ENTRY_STC;


/******************************************************************************* 
                            Ports and Queues Section
*******************************************************************************/

/* Flags to administrate behavior of the physical port.
 * Notes: corresponds to ofp_port_config of OFPPC_.
 */
typedef enum
{
  FPA_PORT_CONFIG_DOWN         = 1 << 0,  /* Port is administratively down. */
  FPA_PORT_CONFIG_NO_RECV      = 1 << 2,  /* Drop all packets received by port. */
  FPA_PORT_CONFIG_NO_FWD       = 1 << 5,  /* Drop packets forwarded to port. */
  FPA_PORT_CONFIG_NO_PACKET_IN = 1 << 6   /* Reserved */
} FPA_PORT_CONFIG_ENT;

/* Current (oper) state of the physical port - read only. 
 */
typedef enum
{
  FPA_PORT_STATE_LINK_DOWN = 1 << 0,  /* No physical link present. */
  FPA_PORT_STATE_BLOCKED   = 1 << 1,  /* Port is blocked */
  FPA_PORT_STATE_LIVE      = 1 << 2,  /* Resreved */
} FPA_PORT_STATE_ENT;


/*
 * typedef: enum FPA_PORT_FEATURE_ENT
 *
 * Description: Features of ports available in a datapath. 
 */
typedef enum
{
  FPA_PORT_FEAT_10MB_HD     = 1 << 0,   /* 10 Mb half-duplex rate. */
  FPA_PORT_FEAT_10MB_FD     = 1 << 1,   /* 10 Mb full-duplex rate. */
  FPA_PORT_FEAT_100MB_HD    = 1 << 2,   /* 100 Mb half-duplex rate. */
  FPA_PORT_FEAT_100MB_FD    = 1 << 3,   /* 100 Mb full-duplex rate. */
  FPA_PORT_FEAT_1GB_HD      = 1 << 4,   /* 1 Gb half-duplex rate. */
  FPA_PORT_FEAT_1GB_FD      = 1 << 5,   /* 1 Gb full-duplex rate. */
  FPA_PORT_FEAT_2_5GB_FD    = 1 << 6,   /* 2.5 Gb full-duplex rate. */
  FPA_PORT_FEAT_10GB_FD     = 1 << 7,   /* 10 Gb full-duplex rate. */
  FPA_PORT_FEAT_20GB_FD     = 1 << 8,   /* 20 Gb full-duplex rate. */
  FPA_PORT_FEAT_25GB_FD     = 1 << 9,   /* 25 Gb full-duplex rate. */
  FPA_PORT_FEAT_40GB_FD     = 1 << 10,  /* 40 Gb full-duplex rate. */
  FPA_PORT_FEAT_100GB_FD    = 1 << 11,  /* 100 Gb full-duplex rate. */
  FPA_PORT_FEAT_1TB_FD      = 1 << 12,  /* 1 Tb rate. */
  FPA_PORT_FEAT_OTHER       = 1 << 13,  /* Other rate, not in the list. */
  FPA_PORT_FEAT_COPPER      = 1 << 14,  /* Copper medium. */
  FPA_PORT_FEAT_FIBER       = 1 << 15,  /* Fiber medium. */
  FPA_PORT_FEAT_AUTONEG     = 1 << 16,  /* Auto-negotiation. */
  FPA_PORT_FEAT_PAUSE       = 1 << 17,  /* Pause. */
  FPA_PORT_FEAT_PAUSE_ASYM  = 1 << 18   /* Asymmetric pause. */

} FPA_PORT_FEATURE_ENT;

/*
 * typedef: enum FPA_PORT_PROPERTIES_FLAGS_ENT
 *
 * Description: Features of ports available in a datapath. Every flag
 *     corresponds to a FPA_PORT_PROPERTIES_STC field.
 */
typedef enum
{
    FPA_PORT_PROPERTIES_STATE_FLAG        = 1 << 0, 
    FPA_PORT_PROPERTIES_CONFIG_FLAG       = 1 << 1, 
    FPA_PORT_PROPERTIES_MAXSPEED_FLAG     = 1 << 2, 
    FPA_PORT_PROPERTIES_CURRSPEED_FLAG    = 1 << 3, 
    FPA_PORT_PROPERTIES_FEATURES_FLAG     = 1 << 4, 
    FPA_PORT_PROPERTIES_ADVERTISED_FLAG   = 1 << 5,
    FPA_PORT_PROPERTIES_SUPPORTED_FLAG    = 1 << 6, 
    FPA_PORT_PROPERTIES_PEER_FLAG         = 1 << 7
} FPA_PORT_PROPERTIES_FLAGS_ENT;

/*
 * typedef: struct FPA_PORT_PROPERTIES_STC
 *
 * Description: Used in set/get port properties. The FPA_PORT_FEATURE_ENT is used
 *     to build the features bitmaps.
 *
 * Fields:
 *      flags       - FPA_PORT_PROPERTIES_FLAGS_ENT, shows relevant fields
 *                    for write(set) and read(get) APIs.
 *      state       - link state, read only.
 *      config      - port administrative state, read/write
 *      maxSpeed    - port maximum speed, read only.
 *      currSpeed   - port current speed, read only.
 *      featuresBmp - current features bitmap, read/write.
 *      advBmp      - adverised features, read/write.
 *      supportedBmp    - features supported by the port, read only.
 *      peerBmp         - features advertised by peer, read only.
 * 
 */
typedef struct
{
    uint32_t            flags;      /* relevant field in the structure*/
    FPA_PORT_STATE_ENT  state;      /* link state, read only */
    uint32_t            config;     /* port administrative state, read/write */
    uint32_t            maxSpeed;   /* port maximum speed, read only */
    uint32_t            currSpeed;  /* port current speed, read only */
    uint32_t            featuresBmp; /* Current features, read/write. */
    uint32_t            advertBmp;   /* Features being advertised, r/w */
    uint32_t            supportedBmp;/* Features supported by the port, read only */
    uint32_t            peerBmp;     /* Features advertised by peer, read only. */
} FPA_PORT_PROPERTIES_STC;

/*
 * typedef: struct FPA_PORT_COUNTERS_STC
 *
 * Description: Used in get per port statistics. Counters are unsigned
 *      and wrap around with no overflow indicator. If a counter is not available
 *      in the switch, its value is the maximum field value (unsigned value -1).
 *
 * Fields:
 *      rxPackets  - number of received packets.
 *      txPackets  - number of transmitted packets.
 *      rxBytes    - number of received bytes.
 *      txBytes    - number of transmitted bytes.
 *      rxDropped  - number of packets dropped by RX.
 *      txDropped  - number of packets dropped by TX.
 *      rxErrors - number of receive errors. This is a super-set of more specific
 *                 receive errors and should be greater than or equal to the sum of
 *                 all rxXxxErr values - see below.
 *      txErrors - number of transmit errors. This is a super-set of more specific
 *                 transmit errors and should be greater than or equal to the sum of
 *                 all txXxxErr values (none currently defined.) 
 *      rxFrameErr - number of frame alignment errors.
 *      rxOverErr  - number of packets with RX overrun.
 *      rxCrcErr   - number of CRC errors.
 *      collisions - number of collisions.
 *      durationSec - time port has been alive in seconds.
 * 
 */
typedef struct 
{
    uint64_t  rxPackets;
    uint64_t  txPackets; 
    uint64_t  rxBytes; 
    uint64_t  txBytes; 
    uint64_t  rxDropped; 
    uint64_t  txDropped; 
    uint64_t  rxErrors; 
    uint64_t  txErrors; 
    uint64_t  rxFrameErr; 
    uint64_t  rxOverErr; 
    uint64_t  rxCrcErr; 
    uint64_t  collisions;
    uint32_t  durationSec;
} FPA_PORT_COUNTERS_STC;

/*
 * typedef: struct FPA_PORT_COUNTERS_EXT_STC
 *
 * Description: Used in extended get per port statistics. Counters are unsigned
 *      and wrap around with no overflow indicator. If a counter is not available
 *      in the switch, its value is the maximum field value (unsigned value -1).
 *
 * Fields:
 *      goodOctetsReceived - The sum of lengths of all good Ethernet frames
 *                           received, namely, frames that are not bad frames or
 *                           MAC Control packets.
 *                           This sum does not include 802.3x pause messages,
 *                           but does include bridge control packets like LCAP
 *                           and BPDU.    
 *    badOctetsReceived - Sum of the lengths of all bad Ethernet frames received.     
 *    crcErrorsSent - Invalid frame transmitted when one of the following occurs:
 *                    1. A frame with a bad CRC was read from the memory.
 *                    2. Underrun occurs.         
 *    goodUnicastFramesReceived - Number of Ethernet Unicast frames received
 *                                that are not bad Ethernet frames or MAC
 *                                Control packets.
 *                                This number includes Bridge Control packets
 *                                such as LACP and BPDU.
 *    reserved4_sentDeferred - reserved.
 *    broadcastFramesReceived - Number of good frames received that had a
 *                              Broadcast destination MAC Address.
 *    multicastFramesReceived - The number of good frames received that had a
 *                              Multicast destination MAC Address.
 *                              This does NOT include 802.3 Flow Control
 *                              messages, as they are considered MAC Control
 *                              packets.
 *    rxFrames64Octets - The number of received and transmitted good and bad
 *                       frames that are 64 bytes in size.
 *                       This does not include MAC Control Frames.      
 *    rxFrames65to127Octets - The number of received and transmitted good and
 *                            bad frames that are 65 to 127 bytes in size.
 *                            This does not include MAC Control Frames.  
 *    rxFrames128to255Octets - The number of received and transmitted good and
 *                             bad frames that are 128 to 255 bytes in size.
 *                             This does not include MAC Control Frames. 
 *    rxFrames256to511Octets - The number of received and transmitted good and
 *                             bad frames that are 256 to 511 bytes in size.
 *                             This does not include MAC Control Frames.
 *    rxFrames512to1023Octets - The number of received and transmitted good and
 *                              bad frames that are 512 to 1023 bytes in size.
 *                              This does not include MAC Control Frames.
 *    rxFrames1024toMaxOctets - The number of received and transmitted of good and
 *                              bad frames that are more than 1023 bytes in size.
 *                              This does not include MAC Control Frames.
 *    rxFrames1024to1518Octet - The number of received and transmitted good and
 *                              bad frames that are 1024 to 1518 bytes in size.
 *                              This does not include MAC Control Frames.
 *    rxFrames1519toMaxOctets - The number of received and transmitted of good and
 *                              bad frames that are more than 1519 bytes in size.
 *                              This does not include MAC Control Frames.
 *    goodOctetsSent - The sum of lengths of all good Ethernet frames sent from
 *                     this MAC.
 *                     This does not include 802.3 Flow Control frames or
 *                     packets with Transmit Error Event counted in CRCErrorSent.        
 *    unicastFrameSent - Number of good frames sent that had a Unicast
 *                       destination MAC Address.      
 *    reserved15 - reserved.            
 *    multicastFramesSent - Number of good frames sent that had a Multicast
 *                          destination MAC Address.
 *                          This does not include IEEE 802.3 Flow Control frames.
 *    broadcastFramesSent - Number of good frames sent that had a Broadcast
 *                          destination MAC Address.
 *                          This does not include IEEE 802.3 Flow Control frames.                             
 *    reserved18 - reserved.            
 *    FCSent - Number of 802.x3 Flow Control frames sent.                
 *    receiveFIFOoverrun - Number of instances that the port was unable to
 *                         receive packets due to insufficient bandwidth to one
 *                         of the packet processor internal resources.
 *                         This counter counts overruns on the Rx FIFO.    
 *    undersizePktsRecieved - Number of undersized packets received. 
 *    fragmentsRecieved - Number of fragments received.     
 *    oversizePktsRecieved - Number of oversize packets received.  
 *    rxJabberPksRecieved - Number of jabber packets received.   
 *    rxErrorFrameReceived - Number of Rx Error events seen by the receive side
 *                           of the MAC.  
 *    badCRC - Number of CRC error events.                
 *    collisions - If working in Half Duplex, this is the transmit with
 *                 collision counter.            
 *    lateCollision - If working in Half Duplex, this is the transmit with late
 *                    collision counter.         
 * 
 */
typedef struct 
{
    uint64_t    goodOctetsReceived;
    uint64_t    badOctetsReceived;
    uint64_t    crcErrorsSent;
    uint64_t    goodUnicastFramesReceived;
    uint64_t    reserved4_sentDeferred;
    uint64_t    broadcastFramesReceived;
    uint64_t    multicastFramesReceived;

    uint64_t    rxFrames64Octets;
    uint64_t    rxFrames65to127Octets;
    uint64_t    rxFrames128to255Octets;
    uint64_t    rxFrames256to511Octets;
    uint64_t    rxFrames512to1023Octets;
    uint64_t    rxFrames1024toMaxOctets;
    uint64_t    rxFrames1024to1518Octets;
    uint64_t    rxFrames1519toMaxOctets; 

    uint64_t    goodOctetsSent;
    uint64_t    unicastFrameSent;
    uint64_t    reserved15;
    uint64_t    multicastFramesSent;
    uint64_t    broadcastFramesSent;

    uint64_t    reserved18;

    uint64_t    FCSent;
    uint64_t    FCReceived;
    uint64_t    receiveFIFOoverrun;
    uint64_t    undersizePktsRecieved;
    uint64_t    fragmentsRecieved;
    uint64_t    oversizePktsRecieved;
    uint64_t    rxJabberPksRecieved;
    uint64_t    rxErrorFrameReceived;
    uint64_t    badCRC;
    uint64_t    collisions;
    uint64_t    lateCollision;
        
} FPA_PORT_COUNTERS_EXT_STC;

typedef uint32_t FPA_FLOW_TABLE_ID_t;

/* Packet In reason codes  */
typedef enum
{
  /* No Match */
  FPA_PACKET_IN_REASON_NO_MATCH = 0,
  /* Action */
  FPA_PACKET_IN_REASON_ACTION,
  /* Invalid TTL */
  FPA_PACKET_IN_REASON_INVALID_TTL,
  
  FPA_PACKET_IN_REASON_MTU_EXCEEDED

} FPA_PACKET_IN_REASON_ENT;

/* Packet buffer */
typedef struct 
{
  FPA_PACKET_IN_REASON_ENT  reason;

  FPA_FLOW_TABLE_ID_t       tableId;

  uint32_t                  inPortNum;

  uint32_t                  pktDataSize;

  uint8_t                   *pktDataPtr;

  uint16_t					vid;

} FPA_PACKET_BUFFER_STC;

typedef struct 
{
  uint32_t                  outPortNum;

  uint32_t                  pktDataSize;
  
  uint8_t                   *pktDataPtr;

} FPA_PACKET_OUT_BUFFER_STC;

/* Asynchronous Control Events */

/* Port event type */
typedef enum
{
  /* Port created */
  FPA_EVENT_PORT_CREATE = 1 << 0,

  /* Port deleted */
  FPA_EVENT_PORT_DELETE = 1 << 1,

  /* Port link state has changed */
  FPA_EVENT_PORT_STATE = 1 << 2,

} FPA_PORT_EVENT_MASK_ENT;

/* Port events */
typedef struct 
{
  /* Event mask indication the event type */
  FPA_PORT_EVENT_MASK_ENT eventMask;

  /* Port number associated with the port event */
  uint32_t                portNum;

  /* Port Link state */
  FPA_PORT_STATE_ENT      state;

} FPA_PORT_EVENT_STC;

/* Flow event type */
typedef enum
{
  /* Flow idle timeout event */
  FPA_FLOW_EVENT_IDLE_TIMEOUT = 1 << 0,

  /* Flow hard timeout event */
  FPA_FLOW_EVENT_HARD_TIMEOUT = 1 << 1

} FPA_FLOW_EVENT_MASK_ENT;

/* Flow events */
typedef struct 
{
  /* events that have occurred for this flow */
  FPA_FLOW_EVENT_MASK_ENT   eventMask;

  /* Flow match criteria */
  /*FPA_FLOW_TABLE_ENTRY_MASK_ENT flowMatch;*/

} FPA_FLOW_TABLE_EVENT_STC;


/*
 * typedef: struct FPA_QUEUE_STATISTICS_STC
 *
 * Description: Used in get per queue statistics. Counters are unsigned and
 *      wrap around with no overflow indicator. If a counter is not available
 *      in the switch, its value is the maximum field value (unsigned value -1).
 *
 * Fields:
 *      txPackets   - number of transmitted packets.
 *      txBytes     - number of transmitted bytes.
 *      txErrors    - number of packets dropped due to overrun.
 *      durationSec - time port has been alive in seconds.
 * 
 */
typedef struct 
{
    uint64_t  txBytes;
    uint64_t  txPackets; 
    uint64_t  txErrors;
    uint32_t  durationSec;
} FPA_QUEUE_STATISTICS_STC;


/******************************************************************************/
typedef struct 
{
  
  char  controllerIp[32];
} FPA_LIB_INFO_SYSTEM_STC;

typedef struct 
{
  uint32_t  mode; /* 0-FRWD_NONE, 1-DROP_NONE, 2-FRWD_CTRL, 3-DROP_CTRL, 4-AUTO */ 
} FPA_LIB_INFO_BRIDGE_STC;

typedef struct 
{
  
  uint32_t              ipcl0_size;      
  uint32_t              ipcl0_scheme; /*0- disabled, 1- v1.0, 2- v1.3_ipv4, 3- v1.3_ipv6*/    

  uint32_t              ipcl1_size;      
  uint32_t              ipcl1_scheme; /*0- disabled, 1- v1.0, 2- v1.3_ipv4, 3- v1.3_ipv6*/    

  uint32_t              ipcl2_size;      
  uint32_t              ipcl2_scheme; /*0- disabled, 1- v1.0, 2- v1.3_ipv4, 3- v1.3_ipv6*/    

} FPA_LIB_INFO_IPCL_STC;

typedef struct 
{
  
  uint32_t              size;      
  uint32_t              scheme; /*0- disabled, 1- v1.0, 2- v1.3_ipv4, 3- v1.3_ipv6*/    

} FPA_LIB_INFO_EPCL_STC;

typedef struct 
{  
  uint32_t              memory_mode;  /*0- disabled, 1- use all memories, 2- use memory 1+2, 3- use memory 1 only*/    
  uint32_t              ipcl_size;      
  uint32_t              epcl_size;      
  uint32_t			    num_entries_ingress_stage0;
  uint32_t              num_entries_ingress_stage1;
} FPA_LIB_INFO_METER_STC;

typedef struct 
{  
  bool                  cpuFilterEnable;
  uint32_t              icmpv6_mode;  /*0- add entry per vlan 1- add entry per switch*/    
} FPA_LIB_INFO_CONTROL_PKT_STC;

typedef struct 
{ 
    FPA_LIB_INFO_SYSTEM_STC      system;
    FPA_LIB_INFO_CONTROL_PKT_STC ctrlPkt;
    FPA_LIB_INFO_BRIDGE_STC      bridge;
    FPA_LIB_INFO_IPCL_STC        ipcl;
    FPA_LIB_INFO_EPCL_STC        epcl;
    FPA_LIB_INFO_METER_STC       meter;
} FPA_LIB_INFO_STC;

extern FPA_LIB_INFO_STC         fpaLibInfo;
/*******************************************************************************
                                 Mac address
********************************************************************************/

/*
 * typedef: enum FPA_SRCMAC_LEARNING_MODE_ENT
 *
 * Description: Enumeration of source MAC learning mode.
 *
 * Enumerations:
 *      FPA_SRCMAC_LEARNING_FRWD_NONE_E - DLF frame is forwarded, no message sent to CONTROLLER
 *      FPA_SRCMAC_LEARNING_DROP_NONE_E - DLF frame is dropped, no message sent to CONTROLLER
 *
 * Comments:
 *         None.
 */
typedef enum
{ 
    FPA_SRCMAC_LEARNING_FRWD_NONE_E,
    FPA_SRCMAC_LEARNING_DROP_NONE_E,
    FPA_SRCMAC_LEARNING_FRWD_CTRL_E,
    FPA_SRCMAC_LEARNING_DROP_CTRL_E,
    FPA_SRCMAC_LEARNING_AUTO_E,  
    FPA_SRCMAC_LEARNING_MAX_E = 0xFFFFFFFF
} FPA_SRCMAC_LEARNING_MODE_ENT;


typedef enum {
    FPA_EVENT_ADDRESS_UPDATE_NEW_E,
    FPA_EVENT_ADDRESS_UPDATE_AGED_E,
    FPA_EVENT_ADDRESS_UPDATE_MAX_E = 0xFFFFFFFF
} FPA_EVENT_ADDRESS_UPDATE_TYPE_ENT;

typedef enum {
    FPA_INTERFACE_PORT_E = 0,
    FPA_INTERFACE_TRUNK_E,
    FPA_INTERFACE_VIDX_E,
    FPA_INTERFACE_VID_E,
    FPA_INTERFACE_DEVICE_E,
    FPA_INTERFACE_FABRIC_VIDX_E,
    FPA_INTERFACE_INDEX_E
}FPA_INTERFACE_TYPE_ENT;

typedef struct 
{  
    uint16_t                            vid;
    FPA_MAC_ADDRESS_STC                 address;
    FPA_INTERFACE_TYPE_ENT				interfaceType;
    uint32_t							interfaceNum;
    FPA_EVENT_ADDRESS_UPDATE_TYPE_ENT   type;
} FPA_EVENT_ADDRESS_MSG_STC;


typedef FPA_STATUS (*FPA_PACKET_TO_CONTROLLER_CB_FUN)
(
    uint32_t        port,
    uint32_t        numOfBuff,
    uint8_t         *packetBuffs[],
    uint32_t        buffLen[]
);

typedef struct
{
    FPA_PACKET_TO_CONTROLLER_CB_FUN toController;
} FPA_NOTIFICATIONS_CB_STC;



typedef enum
 {
     FPA_PORT_TYPE_ETHERNET_MAC_E = 0
    ,FPA_PORT_TYPE_CPU_SDMA_E
    ,FPA_PORT_TYPE_ILKN_CHANNEL_E
    ,FPA_PORT_TYPE_REMOTE_PHYSICAL_PORT_E
    ,FPA_PORT_TYPE_MAX_E
    ,FPA_PORT_TYPE_INVALID_E = ~0
}FPA_PORT_TYPE_ENT;

typedef struct
{
    uint32_t			physicalPortNumber;
    FPA_PORT_TYPE_ENT   mappingType;
    uint32_t            portGroup;
    uint32_t            interfaceNum;
    uint32_t            txqPortNumber;
    bool		        tmEnable;
    uint32_t            tmPortInd;
}FPA_PORT_MAP_STC;


typedef enum
{
     FPA_PHY_SMI_INTERFACE_0_E = 0
    ,FPA_PHY_SMI_INTERFACE_1_E
    ,FPA_PHY_SMI_INTERFACE_2_E
    ,FPA_PHY_SMI_INTERFACE_3_E
    ,FPA_PHY_SMI_INTERFACE_MAX_E
    ,FPA_PHY_SMI_INTERFACE_INVALID_E = (~0)
} FPA_PHY_SMI_INTERFACE_ENT;

typedef enum
{
    FPA_PHY_XSMI_INTERFACE_0_E,
    FPA_PHY_XSMI_INTERFACE_1_E
} FPA_PHY_XSMI_INTERFACE_ENT;

typedef enum
{
    FPA_PORT_INTERFACE_MODE_REDUCED_10BIT_E,   /* 0 */
    FPA_PORT_INTERFACE_MODE_REDUCED_GMII_E,    /* 1 */
    FPA_PORT_INTERFACE_MODE_MII_E,             /* 2 */
    FPA_PORT_INTERFACE_MODE_SGMII_E,           /* 3 */ /* FPA_PORT_SPEED_1000_E , FPA_PORT_SPEED_2500_E   */
    FPA_PORT_INTERFACE_MODE_XGMII_E,           /* 4 */ /* FPA_PORT_SPEED_10000_E, FPA_PORT_SPEED_12000_E, FPA_PORT_SPEED_16000_E, FPA_PORT_SPEED_20000_E, */
    FPA_PORT_INTERFACE_MODE_MGMII_E,           /* 5 */
    FPA_PORT_INTERFACE_MODE_1000BASE_X_E,      /* 6 */ /* FPA_PORT_SPEED_1000_E, */
    FPA_PORT_INTERFACE_MODE_GMII_E,            /* 7 */
    FPA_PORT_INTERFACE_MODE_MII_PHY_E,         /* 8 */
    FPA_PORT_INTERFACE_MODE_QX_E,              /* 9 */  /* FPA_PORT_SPEED_2500_E,  FPA_PORT_SPEED_5000_E,  */
    FPA_PORT_INTERFACE_MODE_HX_E,              /* 10 */ /* FPA_PORT_SPEED_5000_E,  FPA_PORT_SPEED_10000_E, */
    FPA_PORT_INTERFACE_MODE_RXAUI_E,           /* 11 */ /* FPA_PORT_SPEED_10000_E  */
    FPA_PORT_INTERFACE_MODE_100BASE_FX_E,      /* 12 */ 
    FPA_PORT_INTERFACE_MODE_QSGMII_E,          /* 13 */ /* FPA_PORT_SPEED_1000_E, */
    FPA_PORT_INTERFACE_MODE_XLG_E,             /* 14 */
    FPA_PORT_INTERFACE_MODE_LOCAL_XGMII_E,     /* 15 */
    FPA_PORT_INTERFACE_MODE_NO_SERDES_PORT_E =
                                        FPA_PORT_INTERFACE_MODE_LOCAL_XGMII_E,

    FPA_PORT_INTERFACE_MODE_KR_E,              /* 16 */ /* FPA_PORT_SPEED_10000_E, FPA_PORT_SPEED_12000_E, FPA_PORT_SPEED_20000_E, FPA_PORT_SPEED_40000_E, FPA_PORT_SPEED_100G_E, */
    FPA_PORT_INTERFACE_MODE_HGL_E,             /* 17 */ /* FPA_PORT_SPEED_15000_E, FPA_PORT_SPEED_16000_E, FPA_PORT_SPEED_40000_E */
    FPA_PORT_INTERFACE_MODE_CHGL_12_E,         /* 18 */ /* FPA_PORT_SPEED_100G_E , */
    FPA_PORT_INTERFACE_MODE_ILKN12_E,          /* 19 */
    FPA_PORT_INTERFACE_MODE_SR_LR_E,           /* 20 */ /* FPA_PORT_SPEED_5000_E, FPA_PORT_SPEED_10000_E, FPA_PORT_SPEED_12000_E, FPA_PORT_SPEED_20000_E, FPA_PORT_SPEED_40000_E */
    FPA_PORT_INTERFACE_MODE_ILKN16_E,          /* 21 */
    FPA_PORT_INTERFACE_MODE_ILKN24_E,          /* 22 */ 
    FPA_PORT_INTERFACE_MODE_ILKN4_E,           /* 23 */ /* FPA_PORT_SPEED_12000_E, FPA_PORT_SPEED_20000_E, */
    FPA_PORT_INTERFACE_MODE_ILKN8_E,           /* 24 */ /* FPA_PORT_SPEED_20000_E, FPA_PORT_SPEED_40000_E, */

    FPA_PORT_INTERFACE_MODE_XHGS_E,            /* 25 */ /* FPA_PORT_SPEED_11800_E, FPA_PORT_SPEED_47200_E, */
    FPA_PORT_INTERFACE_MODE_XHGS_SR_E,         /* 26 */ /* FPA_PORT_SPEED_11800_E, FPA_PORT_SPEED_47200_E, */

    FPA_PORT_INTERFACE_MODE_NA_E               /* 27 */

}FPA_PORT_INTERFACE_MODE_ENT;

typedef enum
{
    FPA_PORT_SPEED_10_E,       /* 0 */
    FPA_PORT_SPEED_100_E,      /* 1 */
    FPA_PORT_SPEED_1000_E,     /* 2 */
    FPA_PORT_SPEED_10000_E,    /* 3 */
    FPA_PORT_SPEED_12000_E,    /* 4 */
    FPA_PORT_SPEED_2500_E,     /* 5 */
    FPA_PORT_SPEED_5000_E,     /* 6 */
    FPA_PORT_SPEED_13600_E,    /* 7 */
    FPA_PORT_SPEED_20000_E,    /* 8 */
    FPA_PORT_SPEED_40000_E,    /* 9 */
    FPA_PORT_SPEED_16000_E,    /* 10 */
    FPA_PORT_SPEED_15000_E,    /* 11 */
    FPA_PORT_SPEED_75000_E,    /* 12 */
    FPA_PORT_SPEED_100G_E,     /* 13 */
    FPA_PORT_SPEED_50000_E,    /* 14 */
    FPA_PORT_SPEED_140G_E,     /* 15 */

    FPA_PORT_SPEED_11800_E,    /* 16  */ /*used in combination with FPA_PORT_INTERFACE_MODE_XHGS_E or FPA_PORT_INTERFACE_MODE_XHGS_SR_E */
    FPA_PORT_SPEED_47200_E,    /* 17  */ /*used in combination with FPA_PORT_INTERFACE_MODE_XHGS_E or FPA_PORT_INTERFACE_MODE_XHGS_SR_E */
    FPA_PORT_SPEED_22000_E,    /* 18  */ /*used in combination with FPA_PORT_INTERFACE_MODE_XHGS_SR_E */
    FPA_PORT_SPEED_23600_E,    /* 19  */ /*used in combination with FPA_PORT_INTERFACE_MODE_XHGS_E or FPA_PORT_INTERFACE_MODE_XHGS_SR_E */
    FPA_PORT_SPEED_12500_E,    /* 20  */ /* used in combination with FPA_PORT_INTERFACE_MODE_XHGS_E */
    FPA_PORT_SPEED_25000_E,    /* 21  */ /* used in combination with FPA_PORT_INTERFACE_MODE_XHGS_E */

    FPA_PORT_SPEED_NA_E        /* 22 */

}FPA_PORT_SPEED_ENT;

typedef struct{
    uint32_t 					portNum;
    FPA_PORT_SPEED_ENT	 		speed;
    FPA_PORT_INTERFACE_MODE_ENT interfaceMode;
    FPA_PHY_SMI_INTERFACE_ENT 	smiInterface;
	FPA_PHY_XSMI_INTERFACE_ENT 	xsmiInterface;
}FPA_PORT_CONFIG_STC;

#ifdef __cplusplus
}
#endif /* __cplusplus */ 

#endif /* INCLUDE_FPA_DATATYPES_H */
