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
// ID Code      : ScalerOSDLibInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#include "ScalerOSDLibInterface.h"

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#define _OSD_OFFSET_DRAW_WINDOW_H                               10
#define _OSD_OFFSET_DRAW_WINDOW_V                               0

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
//--------------------------------------------------
// Command
//--------------------------------------------------

//--------------------------------------------------
// Windows
//--------------------------------------------------

//--------------------------------------------------
// SRAM
//--------------------------------------------------
extern void ScalerOsdSramAddressSet(WORD usSramAddress, EnumOsdWriteType enumOsdWriteType);
extern void ScalerOsdFontLibraryRotation(void);

//--------------------------------------------------
// Function
//--------------------------------------------------
extern void ScalerOsdVerticalStartSelect(EnumOsdVsyncSelectType enumOsdVsyncSelectType);
extern void ScalerOsdCircuitActivated(bit bEnable);
extern void ScalerOsdFontWindowVericalAlignemnt(bit bOnOff);

