/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2012>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : RL6410_Series_OSDLibInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "RL6410_Series_OSDLibInterface.h"

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#ifndef __RL6410_SERIES_QC_OSD__
extern void ScalerOsdFont24x36OnOff(bit bOnOff);
#endif

extern void ScalerOsdPosition(EnumOsdPositionType enumOsdPositionType, WORD usX, WORD usY);
extern void ScalerOsdSetTransparency(BYTE ucTransparency);
extern void ScalerOsdAutoRotateFontBStartAddr(BYTE ucStartAddr);

