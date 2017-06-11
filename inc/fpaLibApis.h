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
* fpaLibApis.h
*
* DESCRIPTION:
*       OpenFlow FPA Library APIs.
*
* FILE REVISION NUMBER:
*       $Revision: 04 $
*
*******************************************************************************/
#ifndef __INCLUDE_FPA_API_H
#define __INCLUDE_FPA_API_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdint.h>
#include <sys/time.h>
#include <netinet/in.h>

#include "fpaLibTypes.h"

/*******************************************************************************
* fpaLibPreInit
*
* DESCRIPTION:
*       Initialize the FPA library.
*
* INPUTS:
*       None
*
* OUTPUTS:
*       None
*
* RETURNS:
*
* COMMENTS: init table params before calling to cpss
*
*******************************************************************************/
void fpaLibPreInit
(
    IN void
);

/*******************************************************************************
* fpaLibInitialize
*
* DESCRIPTION:
*       Initialize the FPA library.
*
* INPUTS:
*       None
*
* OUTPUTS:
*       None
*
* RETURNS:
*       FPA_OK                    - Operation succeeded
*       FPA_FAIL                  - Operation failed
*
* COMMENTS:
*       All memory pools for the various structures, including tables, flows
*       and groups are allocated here. Only CPSS and packet processor config 
*       that is needed for FPA software done here.
*
*******************************************************************************/
FPA_STATUS fpaLibInitialize
(
    IN FPA_LIB_INFO_STC *fpaLibInfoPtr
);

/*******************************************************************************
* fpaLibFlowConvertPrivToCookie
*
* DESCRIPTION:
*       Convert entry priv to cookie.
*
* INPUTS:
*       entryPriv - pointer to private struct which hold the flow cookie
*
* OUTPUTS:
*       privCookie - retrun cookie number
*
* RETURNS:
*       FPA_OK                    - Operation succeeded
*       FPA_FAIL                  - Operation failed
*
* COMMENTS:
*       some OF client use a private pointer to hold the flow's cookie number,
*		and use the pointer to delete the flow
*******************************************************************************/
FPA_STATUS fpaLibFlowConvertPrivToCookie(
	IN	void		*entryPriv, 
	OUT	uint64_t	*privCookie
);

/*******************************************************************************
* fpaLibFlowEntryInit
*
* DESCRIPTION:
*       Initialize flow entry according flow table type.
*
* INPUTS:
*       switchId      - The logical OpenFlow switch number.
*       flowTableNo   - Flow Table number in OpenFlow pipeline
*       flowEntryPtr  - pointer to a flow entry
*
* OUTPUTS:
*       flowEntryPtr  - entry is initialized
*
* RETURNS:
*       FPA_OK                    - on success.
*       FPA_BAD_PARAM             - wrong parameters
*
* COMMENTS:
*       If a matching entry exists in the table, it must be deleted, 
*
*******************************************************************************/
FPA_STATUS fpaLibFlowEntryInit
(
    IN    uint32_t                       switchId,
    IN    uint32_t                       flowTableNo,
    INOUT FPA_FLOW_TABLE_ENTRY_STC       *flowEntryPtr
);


/*******************************************************************************
* fpaLibFlowEntryAddPriv
*
* DESCRIPTION:
*       Add new flow entry to flow table.
*       Used to support execution of OFPFC_ADD OF protocol messages.
*
* INPUTS:
*       switchId      - The logical OpenFlow switch number.
*       flowTableNo   - Flow Table number in OpenFlow pipeline
*       flowEntryPtr  - pointer to a flow entry
*
* OUTPUTS:
*       entryPriv - private struct which hold the flow's cookie, to use later on
*
* RETURNS:
*       FPA_OK                    - on success.
*       FPA_BAD_PARAM             - wrong parameters
*
* COMMENTS:
*       If a matching entry exists in the table, it must be deleted, 
*       and if the existing entry has the FPA_SEND_FLOW_REM flag set, 
*       it should generate a flow removed message. 
*       If no flow entry currently residing in the requested table matches the 
*       request, no error is recorded, and no flow table modification occurs.
*
*******************************************************************************/
FPA_STATUS fpaLibFlowEntryAddPriv
(
    IN   uint32_t                       switchId,
    IN   uint32_t                       flowTableNo,
    IN   FPA_FLOW_TABLE_ENTRY_STC       *flowEntryPtr,
	OUT	 void							**entryPriv
);

/*******************************************************************************
* fpaLibFlowEntryAdd
*
* DESCRIPTION:
*       Add new flow entry to flow table.
*       Used to support execution of OFPFC_ADD OF protocol messages.
*
* INPUTS:
*       switchId      - The logical OpenFlow switch number.
*       flowTableNo   - Flow Table number in OpenFlow pipeline
*       flowEntryPtr  - pointer to a flow entry
*
* OUTPUTS:
*       None
*
* RETURNS:
*       FPA_OK                    - on success.
*       FPA_BAD_PARAM             - wrong parameters
*
* COMMENTS:
*       If a matching entry exists in the table, it must be deleted, 
*       and if the existing entry has the FPA_SEND_FLOW_REM flag set, 
*       it should generate a flow removed message. 
*       If no flow entry currently residing in the requested table matches the 
*       request, no error is recorded, and no flow table modification occurs.
*
*******************************************************************************/
FPA_STATUS fpaLibFlowEntryAdd
(
    IN   uint32_t                       switchId,
    IN   uint32_t                       flowTableNo,
    IN   FPA_FLOW_TABLE_ENTRY_STC       *flowEntryPtr
);

/*******************************************************************************
* fpaLibFlowEntryModify
*
* DESCRIPTION:
*       Modify one or more matching flow entries.
*       Used to support execution of OFPFC_MODIFY and OFPFC_MODIFY_STRICT
*
* INPUTS:
*       switchId      - The logical OpenFlow switch number.
*       flowTableNo   - Flow Table number in OpenFlow pipeline
*       flowEntryPtr  - pointer to a request flow entry
*       matchingMode  - 0: match entry strictly wildcards and priority.
*                       1: non-strict mode, modify all matching flows
*
* OUTPUTS:
*       None
*
* RETURNS:
*       FPA_OK                    - on success.
*       FPA_BAD_PARAM             - wrong parameters
*
* COMMENTS:
*       If a matching entry exists in the table, the instructions field of this
*       entry is replaced with the value from the request entry, whereas its 
*       cookie, idle_timeout, hard_timeout, flags, counters and duration fields
*       are left unchanged. If the FPA_RESET_COUNTS flag is set, the flow 
*       entry counters must be cleared. 
*       If no flow entry currently residing in the requested table matches
*       the request, no error is recorded, and no flow modification occurs.
*
*******************************************************************************/
FPA_STATUS fpaLibFlowEntryModify
(
    IN   uint32_t                       switchId,
    IN   uint32_t                       flowTableNo,
    IN   FPA_FLOW_TABLE_ENTRY_STC       *flowEntryPtr,
    IN   uint32_t                       matchingMode
);


/*******************************************************************************
* fpaLibFlowEntryDelete
*
* DESCRIPTION:
*       Delete one or more matching flow entries.
*       Used to support execution of OFPFC_DELETE and OFPFC_DELETE_STRICT
*       OpenFlow protocol messages.
*
* INPUTS:
*       switchId      - The logical OpenFlow switch number.
*       flowTableNo   - Flow Table number in OpenFlow pipeline
*       flowEntryPtr  - pointer to request flow entry
*       matchingMode  - 0: delete entry strictly wildcards and priority.
*                       1: non-strict mode, delete all matching flows
*
* OUTPUTS:
*       None
*
* RETURNS:
*       FPA_OK                    - on success.
*       FPA_BAD_PARAM             - wrong parameters
*
* COMMENTS:
*       If a matching entry exists in the table, it must be deleted, 
*       and if the existing entry has the FPA_SEND_FLOW_REM flag set, 
*       it should generate a 
flow removed message. 
*       If no
flow entry currently residing in the requested table matches the 
*       request, no error is recorded, and no 
flow table modification occurs.
*
*******************************************************************************/
FPA_STATUS fpaLibFlowEntryDelete
(
    IN   uint32_t                       switchId,
    IN   uint32_t                       flowTableNo,
    IN   FPA_FLOW_TABLE_ENTRY_STC       *flowEntryPtr,
    IN   uint32_t                       matchingMode
);


/*******************************************************************************
* fpaLibFlowTableCookieDelete
*
* DESCRIPTION:
*       Delete from the flow table one entry with given cookie.
*
* INPUTS:
*       switchId      - The logical OpenFlow switch number.
*       flowTableNo   - Flow Table number in OpenFlow pipeline
*       cookie        - given cookie 
*
* OUTPUTS:
*       None
*
* RETURNS:
*       FPA_OK                    - on success.
*       FPA_BAD_PARAM             - wrong parameters
*
* COMMENTS:
*       If no
flow entry currently residing in the table matches the 
*       cookie, no error is recorded, and no flow table modification occurs.
*
*******************************************************************************/
FPA_STATUS fpaLibFlowTableCookieDelete
(
    IN   uint32_t                       switchId,
    IN   uint32_t                       flowTableNo,
    IN   uint64_t                       cookie
);



/*******************************************************************************
* fpaLibFlowTableGetByCookie
*
* DESCRIPTION:
*       Retrives the flow table entry with given coockie.
*
* INPUTS:
*       switchId      - The logical OpenFlow switch number.
*       flowTableNo   - Flow Table number in OpenFlow pipeline
*       flowEntryPtr  - pointer to flow entry with coockie written
*
* OUTPUTS:
*       flowEntryPtr  - flow entry will be filled by flow table entry content
*
* RETURNS:
*       FPA_OK                    - on success.
*       FPA_NOT_FOUND             - entry not found
*       FPA_BAD_PARAM             - wrong parameters
*
* COMMENTS:
*       The given coockie should be written into flow entry coockie field
*
*******************************************************************************/
FPA_STATUS fpaLibFlowTableGetByCookie
(
    IN    uint32_t                       switchId,
    IN    uint32_t                       flowTableNo,
    INOUT FPA_FLOW_TABLE_ENTRY_STC       *flowEntryPtr
);

/*******************************************************************************
* fpaLibFlowTableGetByEntry
*
* DESCRIPTION:
*       Retrives the flow table entry with given entry.
*
* INPUTS:
*       switchId      - The logical OpenFlow switch number.
*       flowTableNo   - Flow Table number in OpenFlow pipeline
*       flowEntryPtr  - pointer to flow entry 
*
* OUTPUTS:
*       flowEntryPtr  - flow entry will be filled by flow table entry content
*
* RETURNS:
*       FPA_OK                    - on success.
*       FPA_NOT_FOUND             - entry not found
*       FPA_BAD_PARAM             - wrong parameters
*
* COMMENTS:
*
*******************************************************************************/
FPA_STATUS fpaLibFlowTableGetByEntry
(
    IN    uint32_t                       switchId,
    IN    uint32_t                       flowTableNo,
    INOUT FPA_FLOW_TABLE_ENTRY_STC       *flowEntryPtr
);

/*******************************************************************************
* fpaLibFlowTableGetNext
*
* DESCRIPTION:
*       Retrives the next flow table entry.
*
* INPUTS:
*       switchId      - The logical OpenFlow switch number.
*       flowTableNo   - Flow Table number in OpenFlow pipeline
*       firstEntry    -  if 1 - return the firstEntry and start itterator
*       flowEntryPtr  - pointer to flow entry with coockie written
*
* OUTPUTS:
*       flowEntryPtr  - flow entry will be filled by flow table entry content
*
* RETURNS:
*       FPA_OK                    - on success.
*       FPA_BAD_PARAM             - wrong parameters
*       FPA_NOT_FOUND             - end of the table
*
* COMMENTS:
*       The given coockie should be written into flow entry coockie field
*
*******************************************************************************/
FPA_STATUS fpaLibFlowTableGetNext
(
    IN    uint32_t                       switchId,
    IN    uint32_t                       flowTableNo,
    IN    uint32_t                       firstEntry,
    INOUT FPA_FLOW_TABLE_ENTRY_STC       *flowEntryPtr

);

/*******************************************************************************
* fpaLibFlowEntryStatisticsGet
*
* DESCRIPTION:
*       Retrives the per flow entry statistics.
*
* INPUTS:
*       switchId      - The logical OpenFlow switch number.
*       flowTableNo   - Flow Table number in OpenFlow pipeline
*       flowEntryPtr  - pointer to request flow entry
*       statisticsPtr - pointer to per flow entry statistics
*
* OUTPUTS:
*       flowEntryPtr  - flow entry will be filled by flow table entry content
*
* RETURNS:
*       FPA_OK                    - on success.
*       FPA_NOT_FOUND             - entry not found
*       FPA_BAD_PARAM             - wrong parameters
*
* COMMENTS:
*       The given coockie should be written into flow entry coockie field
*
*******************************************************************************/
FPA_STATUS fpaLibFlowEntryStatisticsGet
(
    IN    uint32_t                        switchId,
    IN    uint32_t                        flowTableNo,
    IN    FPA_FLOW_TABLE_ENTRY_STC        *flowEntryPtr,
    INOUT FPA_FLOW_ENTRY_COUNTERS_STC *statisticsPtr

);


/*******************************************************************************
* fpaLibFlowTableStatisticsGet
*
* DESCRIPTION:
*       Retrives the per flow table statistics.
*
* INPUTS:
*       switchId      - The logical OpenFlow switch number.
*       flowTableNo   - Flow Table number in OpenFlow pipeline
*       statisticsPtr - pointer to per flow table statistics
*
* OUTPUTS:
*       flowEntryPtr  - flow entry will be filled by flow table entry content
*
* RETURNS:
*       FPA_OK                    - on success.
*       FPA_BAD_PARAM             - wrong parameters
*
* COMMENTS:
*       The given coockie should be written into flow entry coockie field
*
*******************************************************************************/
FPA_STATUS fpaLibFlowTableStatisticsGet
(
    IN    uint32_t                        switchId,
    IN    uint32_t                        flowTableNo,
    INOUT FPA_FLOW_TABLE_COUNTERS_STC *statisticsPtr
);

/*******************************************************************************
* fpaLibFlowEntryHitStatusGet
*
* DESCRIPTION:
*       Retrives and reset hit status for an entry.
*
* INPUTS:
*       switchId      - The logical OpenFlow switch number.
*       flowTableNo   - Flow Table number in OpenFlow pipeline
*       cookie		  - the flow cookie.
*
* OUTPUTS:
*       hitStatus  - hit_status True if entry hit since last time API was called
*
* RETURNS:
*       FPA_OK                    - on success.
*       FPA_BAD_PARAM             - wrong parameters
*
* COMMENTS:
*       The given coockie should be written into flow entry coockie field
*
*******************************************************************************/
FPA_STATUS fpaLibFlowEntryHitStatusGet
(
    IN    uint32_t                      switchId,
    IN    uint32_t                      flowTableNo,
	IN    uint64_t                      cookie,
	OUT	  bool							*hitStatus
);

FPA_STATUS fpaLibFlowTableShowName
(
    IN    uint32_t                        switchId
);

FPA_STATUS fpaLibFlowTableDump
(    
	IN    uint32_t                        switchId,
    IN    uint32_t                        flowTableNo
);

/******************************************************************************* 
                            Group Table APIs
*******************************************************************************/

/*******************************************************************************
* fpaLibGroupIdentifierParse
*
* DESCRIPTION:
*       Parse the 32 bit opaque group identifier and retrives the group type
*       and all fields according group type.
*
* INPUTS:
*       groupIdentifier      - 32 bit opaque group identifier.
*
* OUTPUTS:
*       parsedGroupIdentifierPtr - pointer to group type
*
* RETURNS:
*       FPA_OK                    - on success.
* COMMENTS:
*       
*******************************************************************************/
FPA_STATUS fpaLibGroupIdentifierParse
(
    IN    uint32_t                          groupIdentifier,
    OUT   FPA_GROUP_ENTRY_IDENTIFIER_STC    *parsedGroupIdentifierPtr
);

/*******************************************************************************
* fpaLibGroupIdentifierBuild
*
* DESCRIPTION:
*       Build the 32 bit opaque group identifier using the group type
*       and all fields from the structure.
*
* INPUTS:
*       parsedGroupIdentifierPtr - pointer to parsed group id struct
*
* OUTPUTS:
*       groupIdentifierPtr      - pointer to 32 bit opaque group identifier
*
* RETURNS:
*       FPA_OK                    - on success.
* COMMENTS:
*       
*******************************************************************************/
FPA_STATUS fpaLibGroupIdentifierBuild
(
    IN   FPA_GROUP_ENTRY_IDENTIFIER_STC    *parsedGroupIdentifierPtr,
    OUT  uint32_t                          *groupIdentifierPtr;
);


/*******************************************************************************
* fpaLibGroupTableEntryAdd
*
* DESCRIPTION:
*       Adds the entry.
*
* INPUTS:
*       switchId      - logical switch id
*       groupEntryPtr - group entry
*
* OUTPUTS:
*       None
*
* RETURNS:
*       FPA_OK                    - on success.
* COMMENTS:
*       
*******************************************************************************/
FPA_STATUS fpaLibGroupTableEntryAdd
(
    IN   uint32_t                   switchId,
    IN   FPA_GROUP_TABLE_ENTRY_STC  *groupEntryPtr
);



/*******************************************************************************
* fpaLibGroupTableEntryDelete
*
* DESCRIPTION:
*       Delete the entry.
*
* INPUTS:
*       switchId        - logical switch id
*       groupIdentifier - 32 bit opaque group identifier
*
* OUTPUTS:
*       None
*
* RETURNS:
*       FPA_OK                    - on success.
*
* COMMENTS:
*       
*******************************************************************************/
FPA_STATUS fpaLibGroupTableEntryDelete
(
    IN   uint32_t   switchId,
    IN   uint32_t   groupIdentifier
);

/*******************************************************************************
* fpaLibGroupTableGetEntry
*
* DESCRIPTION:
*       Get group table entry.
*
* INPUTS:
*       switchId        - logical switch id
*       groupIdentifier - 32 bit opaque group identifier
*
* OUTPUTS:
*       groupEntryPtr   - group table entry
*
* RETURNS:
*       FPA_OK                    - on success.
*       FPA_BAD_PARAM             - wrong parameters
*       FPA_NOT_FOUND             - end of the table
*
* COMMENTS:
*
*******************************************************************************/
FPA_STATUS fpaLibGroupTableGetEntry
(
    IN   uint32_t   switchId,
    IN   uint32_t   groupIdentifier,
    OUT  FPA_GROUP_TABLE_ENTRY_STC  *groupEntryPtr
);

/*******************************************************************************
* fpaLibGroupTableGetNext
*
* DESCRIPTION:
*       Get next group table entry.
*
* INPUTS:
*       switchId        - logical switch id
*       groupIdentifier - 32 bit opaque group identifier
*
* OUTPUTS:
*       groupEntryPtr   - group table entry
*
* RETURNS:
*       FPA_OK                    - on success.
*       FPA_BAD_PARAM             - wrong parameters
*       FPA_NOT_FOUND             - end of the table
*
* COMMENTS:
*       
*******************************************************************************/
FPA_STATUS fpaLibGroupTableGetNext
(
    IN   uint32_t   switchId,
    IN   uint32_t   groupIdentifier,
    OUT  FPA_GROUP_TABLE_ENTRY_STC  *groupEntryPtr
);


/*******************************************************************************
* fpaLibGroupEntryStatisticsGet
*
* DESCRIPTION:
*       Retrives the group entry statistics.
*
* INPUTS:
*       switchId      - The logical OpenFlow switch number.
*       groupIdentifier   - 32 bit opaque group identifier
*
* OUTPUTS:
*       countersPtr  - group entry counters 
*
* RETURNS:
*       FPA_OK                    - on success.
*       FPA_NOT_FOUND             - entry not found
*       FPA_BAD_PARAM             - wrong parameters
*
* COMMENTS:
*
*******************************************************************************/
FPA_STATUS fpaLibGroupEntryStatisticsGet
(
    IN   uint32_t   switchId,
    IN   uint32_t   groupIdentifier,
    OUT  FPA_GROUP_COUNTERS_STC  *countersPtr
);


FPA_STATUS fpaLibGroupEntryBucketAdd
(
    IN   uint32_t                   switchId,
    IN   FPA_GROUP_BUCKET_ENTRY_STC *bucketPtr
);

FPA_STATUS fpaLibGroupEntryBucketModify
(
    IN   uint32_t                   switchId,
    IN   FPA_GROUP_BUCKET_ENTRY_STC *bucketPtr
);

FPA_STATUS fpaLibGroupEntryBucketDelete
(
    IN   uint32_t   switchId,
    IN   uint32_t   groupIdentifier,
    IN   uint32_t   bucketIndex         /* if == -1 - delete all buckets */
);

/* FPA_NOT_FOUND if not exist for itterator */
FPA_STATUS fpaLibGroupEntryBucketGet
(
    IN   uint32_t   switchId,
    IN   uint32_t   groupIdentifier,
    IN   uint32_t   bucketIndex,
    OUT  FPA_GROUP_BUCKET_ENTRY_STC *bucketPtr
);

/* FPA_NO_MORE - after the last entry */
FPA_STATUS fpaLibGroupEntryBucketGetNext
(
    IN   uint32_t   switchId,
    IN   uint32_t   groupIdentifier,
    IN   uint32_t   bucketIndex,
    OUT  FPA_GROUP_BUCKET_ENTRY_STC *bucketPtr
);

/*******************************************************************************
* fpaLibGroupEntryBucketGetIndexByEntry
*
* DESCRIPTION:
*       Get bucket index from a bucket data.
*       supported only wheb bucket type is FPA_GROUP_BUCKET_L2_REFERENCE_E
*
* INPUTS:
*   	switchId      - The logical OpenFlow switch number.
*	    entryPtr - bucket reference parameters.
*
* OUTPUTS:
*       entryPtr   - the wanted bucket index. 
* RETURNS:
*       FPA_OK                    - on success.
*       FPA_NOT_FOUND             - entry not found
*       FPA_BAD_PARAM             - wrong parameters
*
* COMMENTS:
*
*******************************************************************************/
FPA_STATUS fpaLibGroupEntryBucketGetIndexByEntry
(
    IN    uint32_t   			switchId,
    INOUT FPA_GROUP_BUCKET_ENTRY_STC   *entryPtr
);

/*******************************************************************************
* fpaLibPortPropertiesGet
*
* DESCRIPTION:
*       Get various port & peer information.
*
* INPUTS:
*       switchId    - The logical OpenFlow switch number.
*       portNum     - The port
*       propertiesPtr - requested flags.
*
* OUTPUTS:
*       propertiesPtr   - (pointer to) the generic port properties structure.
*
* RETURNS:
*       FPA_OK          - on success
*       FPA_BAD_PTR     - on NULL pointer
*       FPA_BAD_PARAM   - wrong parameters
*
* COMMENTS:
*
*******************************************************************************/
FPA_STATUS fpaLibPortPropertiesGet
(
    IN   uint32_t                   switchId,
    IN   uint32_t                   portNum,
    OUT  FPA_PORT_PROPERTIES_STC    *propertiesPtr
);

/*******************************************************************************
* fpaLibPortPropertiesSet
*
* DESCRIPTION:
*       Set various port configurations, state & advertise abilities.
*
* INPUTS:
*       switchId        - The logical OpenFlow switch number.
*       portNum         - The port
*       propertiesPtr   - (pointer to)the generic port properties structure.
*
* OUTPUTS:
*       None.
*
* RETURNS:
*       FPA_OK          - on success
*       FPA_BAD_PTR     - on NULL pointer
*       FPA_BAD_PARAM   - wrong parameters
*
* COMMENTS:
*       Only write fields of generic port properties sturcture are allowed to be
*       accessed.
*
*******************************************************************************/
FPA_STATUS fpaLibPortPropertiesSet
(
    IN  uint32_t                   switchId,
    IN  uint32_t                   portNum,
    IN  FPA_PORT_PROPERTIES_STC    *propertiesPtr
);

/*******************************************************************************
* fpaLibPortStatisticsGet
*
* DESCRIPTION:
*       Get various port counters.
*
* INPUTS:
*       switchId        - The logical OpenFlow switch number.
*       portNum         - The port
*
* OUTPUTS:
*       statisticsPtr   - (pointer to) port counters.
*
* RETURNS:
*       FPA_OK          - on success
*       FPA_BAD_PTR     - on NULL pointer
*       FPA_BAD_PARAM   - wrong parameters
*
* COMMENTS:
*
*******************************************************************************/
FPA_STATUS fpaLibPortStatisticsGet
(
    IN   uint32_t                   switchId,
    IN   uint32_t                   portNum,
    OUT  FPA_PORT_COUNTERS_STC    *statisticsPtr
);

/*******************************************************************************
* fpaLibPortStatisticsExtGet
*
* DESCRIPTION:
*       Get various extended port counters.
*
* INPUTS:
*       switchId        - The logical OpenFlow switch number.
*       portNum         - The port
*
* OUTPUTS:
*       statisticsPtr   - (pointer to) extended port counters.
*
* RETURNS:
*       FPA_OK          - on success
*       FPA_BAD_PTR     - on NULL pointer
*       FPA_BAD_PARAM   - wrong parameters
*
* COMMENTS:
*
*******************************************************************************/
FPA_STATUS fpaLibPortStatisticsExtGet
(
    IN   uint32_t                   switchId,
    IN   uint32_t                   portNum,
    OUT  FPA_PORT_COUNTERS_EXT_STC  *statisticsPtr
);

/*******************************************************************************
* fpaLibPortStatisticsClear
*
* DESCRIPTION:
*       Clear port counters.
*
* INPUTS:
*       switchId        - The logical OpenFlow switch number.
*       portNum         - The port
*
* OUTPUTS:
*       None
*
* RETURNS:
*       FPA_OK          - on success
*       FPA_BAD_PARAM   - wrong parameters
*
* COMMENTS:
*
*******************************************************************************/
FPA_STATUS fpaLibPortStatisticsClear
(
    IN   uint32_t                   switchId,
    IN   uint32_t                   portNum
);

/*******************************************************************************
* fpaLibPortPktSend
*
* DESCRIPTION:
*       Transmit a single packet that the Controller sent to the switch (from CPU) 
*
* INPUTS:
*       switchId      - The logical OpenFlow switch number
*       inPortNum     - Source port that the packet was ingressed
*       pktPtr	      - (pointer to) packet buffer
*
* OUTPUTS:
*       None
*
* RETURNS:
*       FPA_OK                   - on success.
*       FPA_FAIL	             - on failure
*       FPA_BAD_PTR              - on NULL pointer
*
* COMMENTS:
*
*******************************************************************************/
FPA_STATUS fpaLibPortPktSend
(
    IN   uint32_t               switchId,
    IN   uint32_t               inPortNum,
    IN   FPA_PACKET_OUT_BUFFER_STC  *pktPtr
);


/******************************************************************************* 
                            Meter Table APIs
*******************************************************************************/

/*******************************************************************************
* fpaLibMeterTableEntryAdd
*
* DESCRIPTION:
*       Adds the entry.
*
* INPUTS:
*       switchId      - logical switch id
*       meterEntryPtr - meter entry
*
* OUTPUTS:
*       None
*
* RETURNS:
*       FPA_OK            - on success.
*       FPA_ALREADY_EXIST - entry with this identifier already exist
*       FPA_NO_RESOURCE   - add the entry impossible due to lack of space
*
* COMMENTS:
*       If a meter entry with the specified meter identifier already exist, then 
*       the switch must refuse to add the meter entry and returns EXIST code.
* 
*******************************************************************************/
FPA_STATUS fpaLibMeterTableEntryAdd
(
    IN   uint32_t                   switchId,
    IN   FPA_METER_TABLE_ENTRY_STC  *meterEntryPtr
);



/*******************************************************************************
* fpaLibMeterTableEntryDelete
*
* DESCRIPTION:
*       Delete the entry.
*
* INPUTS:
*       switchId        - logical switch id
*       meterIdentifier - meter identifier
*
* OUTPUTS:
*       None
*
* RETURNS:
*       FPA_OK                    - on success.
*
* COMMENTS:
*       If no meter entry with this identifier exists, no error is recorded, 
*       and no meter modification occurs. Else the meter is removed, and all
*       flows that include the meter in their instruction set are also removed.
*       If meterId is OFPM_ALL, delete all meters (except virtual).
*       
*******************************************************************************/
FPA_STATUS fpaLibMeterTableEntryDelete
(
    IN   uint32_t   switchId,
    IN   uint32_t   meterIdentifier
);


/*******************************************************************************
* fpaLibMeterStatisticsGet
*
* DESCRIPTION:
*       Retrives the per Meter statistics.
*
* INPUTS:
*       switchId      - The logical OpenFlow switch number
*       meterIdentifier - the requested meter id
*
* OUTPUTS:
*       statisticsPtr - pointer to per meter statistics
*
* RETURNS:
*       FPA_OK                    - on success.
*       FPA_NOT_FOUND             - entry not found
*
* COMMENTS:
*
*******************************************************************************/
FPA_STATUS fpaLibMeterStatisticsGet
(
    IN    uint32_t                   switchId,
    IN    uint32_t                   meterIdentifier,
    INOUT FPA_METER_COUNTERS_STC *statisticsPtr
);


/******************************************************************************* 
                            Events APIs
*******************************************************************************/

int fpaLibCpssEventsFdGet
(
    IN   uint32_t  switchId,
    IN   uint32_t  events
);

int fpaLibCpssEventsFdWait
(
    IN   uint32_t  switchId,
    IN   uint32_t  events,
    IN   uint32_t  timeout
); 

/*******************************************************************************
* fpaLibPktReceive
*
* DESCRIPTION:
*       Retrieve a single packet that the switch sent to the Controller (CPU)
*
* INPUTS:
*       switchId      - The logical OpenFlow switch number
*       timeout       - Indicates if the function is blocking or not
*                       timeout == 0: blocking; function returns only if message arrives
*                       timeout != 0: non-blocking; function returns after timeout 
*
* OUTPUTS:
*       pktPtr	      - (pointer to) packet buffer
*
* RETURNS:
*       FPA_OK                    - on success.
*       FPA_FAIL	              - on failure
*       FPA_NO_MORE		          - Currently no more packets in queue
*
* COMMENTS:
*
*******************************************************************************/
FPA_STATUS fpaLibPktReceive
(
    IN   uint32_t               switchId,
    IN   uint32_t               timeout, 
    OUT  FPA_PACKET_BUFFER_STC  *pktPtr
);


/******************************************************************************* 
                            Port and Queue APIs
*******************************************************************************/

/* calls this function to get the number of queues on a port. */
FPA_STATUS fpaLibPortQueuesGet
(
    IN   uint32_t                   switchId,
    IN   uint32_t                   portNum,
    OUT  uint32_t          *numQueuesPtr
);

/* get the statistics of a queue on a port. */
FPA_STATUS fpaLibPortQueueStatisticsGet
(
    IN   uint32_t                       switchId,
    IN   uint32_t                       portNum,
    IN   uint32_t                       queueId,
    OUT  FPA_QUEUE_STATISTICS_STC  *statisticsPtr
);

/* clear statistics of a queue on a port. */
FPA_STATUS fpaLibPortQueueStatisticsClear
(
    IN   uint32_t                   switchId,
    IN   uint32_t                   portNum,
    IN   uint32_t                   queueId
);

/* set minimum and maximum bandwidth on a queue on a given port */
FPA_STATUS fpaLibPortQueueRateSet
(
    IN   uint32_t                       switchId,
    IN   uint32_t                       portNum,
    IN   uint32_t                       queueId,
    IN   uint32_t minRate, 
    IN   uint32_t maxRate
);


/* get minimum and maximum bandwidth on a queue on a given port */
FPA_STATUS fpaLibPortQueueRateGet
(
    IN   uint32_t   switchId,
    IN   uint32_t   portNum,
    IN   uint32_t   queueId,
    OUT  uint32_t   *minRatePtr, 
    OUT  uint32_t   *maxRatePtr
);

/*******************************************************************************
                                 Mac address
********************************************************************************/
/*******************************************************************************
* fpaLibSwitchSrcMacAddressSet
*
* DESCRIPTION:
*       Set switch source MAC adddress, used for MAC layer packets (as pause, etc.) 
*
* INPUTS:
*       switchId    - The logical OpenFlow switch number.
*       srcMacPtr   - The switch source MAC address
*       mode        - Unique MAC address per port(1) or same for all ports(0)
*
* OUTPUTS:
*       None
*
* RETURNS:
*       FPA_OK                    - on success.
*       FPA_BAD_PARAM             - wrong parameters
*
* COMMENTS:
*       The default mode is 0 - unique per port mode. In this mode the least 
*       significant byte of the MAC SA of a port is set to port number.
*
*******************************************************************************/
FPA_STATUS fpaLibSwitchSrcMacAddressSet
(
    IN  uint32_t                switchId, 
    IN  uint32_t                mode,
    IN  FPA_MAC_ADDRESS_STC     *srcMacPtr
);

/*******************************************************************************
* fpaLibSwitchSrcMacAddressGet
*
* DESCRIPTION:
*       Get switch source MAC adddress, used for MAC layer packets (as pause, etc.) 
*
* INPUTS:
*       switchId    - The logical OpenFlow switch number.
*
* OUTPUTS:
*       srcMacPtr   - The switch source MAC address
*       mode        - Unique MAC address per port(1) or same for all ports(0)
*
* RETURNS:
*       FPA_OK                    - on success.
*       FPA_BAD_PARAM             - wrong parameters
*
* COMMENTS:
*       Read the address from the hardware registers.
*
*******************************************************************************/
FPA_STATUS fpaLibSwitchSrcMacAddressGet
(
    IN   uint32_t                switchId, 
    OUT  uint32_t                *modePtr,
    OUT  FPA_MAC_ADDRESS_STC     *srcMacPtr

);

/*******************************************************************************
* fpaLibPortSrcMacAddressGet
*
* DESCRIPTION:
*       Get switch source MAC adddress, used for MAC layer packets (as pause, etc.) 
*
* INPUTS:
*       switchId    - The logical OpenFlow switch number.
*       port        - The port
*
* OUTPUTS:
*       srcMacPtr   - The port source MAC address
*
* RETURNS:
*       FPA_OK                    - on success.
*       FPA_BAD_PARAM             - wrong parameters
*
* COMMENTS:
*       Read the address from the hardware registers.
*
*******************************************************************************/
FPA_STATUS fpaLibPortSrcMacAddressGet
(
    IN   uint32_t                switchId, 
    IN   uint32_t                port,
    OUT  FPA_MAC_ADDRESS_STC     *srcMacPtr
);

/*******************************************************************************
* fpaLibSwitchSrcMacLearningSet
*
* DESCRIPTION:
*       Set switch source MAC learning mode. 
*
* INPUTS:
*       switchId    - The logical OpenFlow switch number.
*       mode        - The source MAC learning mode
*
* OUTPUTS:
*       None
*
* RETURNS:
*       FPA_OK                    - on success.
*       FPA_BAD_PARAM             - wrong parameters
*
* COMMENTS:
*       Set the source MAC learning mode of the whole switch, applyed to all ports.
*       Allows copieng the packets with unknown source address to CPU. Used in the 
*       initialization period. The default mode is FPA_SRCMAC_LEARNING_FRWD_NONE_E.
*       To prevent a rapid stream of PACKET_IN learning messages, the FPA adds a 
*       storm prevention (SP) FDB entry the first time the PACKET_IN is sent to the
*       CPU. This entry will be aged out if the controller does not update the FDB 
*       with regular entry.
*
*******************************************************************************/
FPA_STATUS fpaLibSwitchSrcMacLearningSet
(
    IN   uint32_t                       switchId,
    IN   FPA_SRCMAC_LEARNING_MODE_ENT   mode
);

/*******************************************************************************
* fpaLibSwitchSrcMacLearningGet
*
* DESCRIPTION:
*       Get the switch source MAC learning mode. 
*
* INPUTS:
*       switchId    - The logical OpenFlow switch number.
*
* OUTPUTS:
*       modePtr     - The source MAC learning mode
*
* RETURNS:
*       FPA_OK                    - on success.
*       FPA_BAD_PARAM             - wrong parameters
*
* COMMENTS:
*       Get the source MAC learning mode of the whole switch.
*
*******************************************************************************/
FPA_STATUS fpaLibSwitchSrcMacLearningGet
(
    IN   uint32_t                       switchId,
    IN   FPA_SRCMAC_LEARNING_MODE_ENT   *modePtr
);

/*******************************************************************************
* fpaLibPortSrcMacLearningSet
*
* DESCRIPTION:
*       Set per port source MAC learning mode. 
*
* INPUTS:
*       switchId    - The logical OpenFlow switch number.
*       portNum     - The port
*       mode        - The source MAC learning mode
*
* OUTPUTS:
*       None
*
* RETURNS:
*       FPA_OK                    - on success.
*       FPA_BAD_PARAM             - wrong parameters
*
* COMMENTS:
*       Set the port MAC learning mode, different from the switch mode.
*       The default mode is FPA_SRCMAC_LEARNING_MAX_E - same as switch mode.
*
*******************************************************************************/
FPA_STATUS fpaLibPortSrcMacLearningSet
(
    IN   uint32_t                       switchId,
    IN   uint32_t                       portNum,
    IN   FPA_SRCMAC_LEARNING_MODE_ENT   mode
);

/*******************************************************************************
* fpaLibPortSrcMacLearningGet
*
* DESCRIPTION:
*       Get per port source MAC learning mode. 
*
* INPUTS:
*       switchId    - The logical OpenFlow switch number.
*       portNum     - The port
*
* OUTPUTS:
*       modePtr     - The source MAC learning mode
*
* RETURNS:
*       FPA_OK                    - on success.
*       FPA_BAD_PARAM             - wrong parameters
*
* COMMENTS:
*
*******************************************************************************/
FPA_STATUS fpaLibPortSrcMacLearningGet
(
    IN   uint32_t                       switchId,
    IN   uint32_t                       portNum,
    IN   FPA_SRCMAC_LEARNING_MODE_ENT   *modePtr
);

/*******************************************************************************
* fpaLibSwitchAgingTimeoutSet
*
* DESCRIPTION:
*       Set FDB aging timeout. 
*
* INPUTS:
*       timeout     - Aging timeout value 0 - timeout disabled
*
* OUTPUTS:
*       None
*
* RETURNS:
*       FPA_OK                    - on success.
*       FPA_BAD_PARAM             - wrong parameters
*
* COMMENTS:
*
*******************************************************************************/
FPA_STATUS fpaLibSwitchAgingTimeoutSet
(
    IN   uint32_t     switchId,
    IN   uint32_t     timeout
);

/*******************************************************************************
* fpaLibSwitchAgingTimeoutGet
*
* DESCRIPTION:
*       Get FDB aging timeout. 
*
* INPUTS:
*       timeout     - Aging timeout value 0 - timeout disabled
*
* OUTPUTS:
*       None
*
* RETURNS:
*       FPA_OK                    - on success.
*       FPA_BAD_PARAM             - wrong parameters
*
* COMMENTS:
*
*******************************************************************************/
FPA_STATUS fpaLibSwitchAgingTimeoutGet
(
    IN   uint32_t     switchId,
    IN   uint32_t     *timeoutPtr
);

/*******************************************************************************
* fpaLibBridgingAuMsgGet
*
* DESCRIPTION:
*       Get New Address event every call returns one event at most
*
* INPUTS:
*   	non_blocking     - Indicates if the functions is blocking or not.
*   					   Blocking - function returns only if a message arrives
*   					   Non Blocking - functions returns even if no message exist
*
* OUTPUTS:
*       msg_PTR			 - Msg data.
*
* RETURNS:
*       FPA_OK                   - on success.
*   	FPA_FAIL	             - could not get new address message
*       FPA_NO_MORE				 - Currently no more messages in queue - Valid only in non-blocking mode
*
* COMMENTS:
*
*******************************************************************************/
FPA_STATUS fpaLibBridgingAuMsgGet
(
	IN   	uint32_t     switchId,
	IN   	bool         non_blocking,
	OUT 	FPA_EVENT_ADDRESS_MSG_STC *msg_ptr
);

/*******************************************************************************
* fpaLibInit
*
* DESCRIPTION:
*      Initialize packet processor and FPA library
*
* INPUTS:
*
* OUTPUTS:
*
*
* RETURNS:
*      FPA_OK                   - on success.
*      FPA_ERROR             - on initialization error
*
* COMMENTS:
*
*******************************************************************************/
FPA_STATUS fpaLibInit
(
    void
);



/*******************************************************************************
* fpaLibDevicePortsParametes
*
* DESCRIPTION:
*      Set the device ports mapping configuration
*
* INPUTS:
*
* OUTPUTS:
*
*
* RETURNS:
*      FPA_OK                - on success.
*      FPA_ERROR             - on initialization error
*
* COMMENTS:
*
*******************************************************************************/

FPA_STATUS fpaLibDevicePortsParametes
(
	IN	uint32_t			portsMapArraySize,
	IN 	uint32_t			portsConfigArraySize,
	IN	FPA_PORT_MAP_STC	*portsMapArray,
	IN	FPA_PORT_CONFIG_STC	*portsConfigArray
);

#ifdef __cplusplus
}
#endif /* __cplusplus */ 

#endif /* INCLUDE_FPA_API_H */
