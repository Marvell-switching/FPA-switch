/*******************************************************************************
*              (c), Copyright 2001, Marvell International Ltd.                 *
* THIS CODE CONTAINS CONFIDENTIAL INFORMATION OF MARVELL SEMICONDUCTOR, INC.   *
* NO RIGHTS ARE GRANTED HEREIN UNDER ANY PATENT, MASK WORK RIGHT OR COPYRIGHT  *
* OF MARVELL OR ANY THIRD PARTY. MARVELL RESERVES THE RIGHT AT ITS SOLE        *
* DISCRETION TO REQUEST THAT THIS CODE BE IMMEDIATELY RETURNED TO MARVELL.     *
* THIS CODE IS PROVIDED "AS IS". MARVELL MAKES NO WARRANTIES, EXPRESSED,       *
* IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY, COMPLETENESS OR PERFORMANCE.   *
********************************************************************************
* mrvlHalProfile.h
*
* DESCRIPTION:
*       initialize system
*
* FILE REVISION NUMBER:
*       $Revision: 1 $
*
*******************************************************************************/
#ifndef __INCLUDE_MRVL_HAL_PROFILE_API_H
#define __INCLUDE_MRVL_HAL_PROFILE_API_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define PROFILE_SPEED_UNITS_CNS 100 /* units of 100MB */

typedef enum {
	PROFILE_TYPE_INVALID_E=0,
	PROFILE_TYPE_PORT_MAP_E,
	PROFILE_TYPE_APP_PORT_MAP_E,
	PROFILE_TYPE_LANE_SWAP_E,
	PROFILE_TYPE_SERDES_MAP_E,
	PROFILE_TYPE_SIM_INIFILE_E,
	/* MUST BE LAST */
	PROFILE_TYPE_MAX_E,
	PROFILE_TYPE_LAST_E = 0xFF
}PROFILE_TYPE_ENT;

typedef enum
{
    PROFILE_INTERFACE_MODE_1000BASE_X_E = 6,	/* 1000BASE_X_E 1G, */
    PROFILE_INTERFACE_MODE_KR_E         = 16,	/* KR_E 10G, 12G, 20G, 40G */
    PROFILE_INTERFACE_MODE_SR_LR_E		= 20,	/* SR_LR_E 10G, 12G, 20G, 40G, */
	PROFILE_INTERFACE_MODE_KR4_E		= 28	/* KR4_E 100G */
}PROFILE_INTERFACE_MODE_ENT;


typedef struct {
	unsigned int				portNum;
	unsigned int				macNum;
	unsigned int				txQNum;
	PROFILE_INTERFACE_MODE_ENT	interfaceMode;
	unsigned int				interfaceSpeed; /* in units of PROFILE_SPEED_UNITS_CNS  */
}PORT_MAP_STC;

typedef struct
{
	unsigned int	laneNum;
	unsigned int	invertTx;
	unsigned int	invertRx;
}SERDES_LANE_POLARITY_STC;

typedef union {
	PORT_MAP_STC 				portMap; /* PROFILE_TYPE_PORT_MAP_E */
	SERDES_LANE_POLARITY_STC	serdes_polarity; /* PROFILE_TYPE_LANE_SWAP_E */
	char  						sim_inifile[64]; /*PROFILE_TYPE_SIM_INIFILE_E*/
	/* last */
	unsigned int				no_param;
}PROFILE_VALUE;

typedef struct {
	PROFILE_TYPE_ENT	profileType;
	PROFILE_VALUE		profileValue;
}PROFILE_STC;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*__INCLUDE_MRVL_HAL_PROFILE_API_H*/
