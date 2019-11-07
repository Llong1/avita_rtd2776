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
// ID Code      : ScalerOsd.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_OSD__

#include "ScalerFunctionInclude.h"


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_OSD_POSITION_OFFSET_CORRECTION == _OFF)
BYTE g_ucOsdPositionGlobalOffsetH;
BYTE g_ucOsdPositionGlobalOffsetV;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerOsdPositionOffset(EnumOsdPositionOffsetType enumOsdPositionOffsetType, BYTE ucHOffset, BYTE ucVOffset);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : Set osd position
// Input Value  : EnumOsdPositionOffsetType -> _OSD_POSITION_OFFSET_GLOBAL or _OSD_POSITION_OFFSET_WINDOW
//                usHOffset                 -> Horizontal Offset
//                usVOffset                 -> Vertical  Offset
// Output Value :
//--------------------------------------------------
void ScalerOsdPositionOffset(EnumOsdPositionOffsetType enumOsdPositionOffsetType, BYTE ucHOffset, BYTE ucVOffset)
{
    if(enumOsdPositionOffsetType == _OSD_POSITION_OFFSET_GLOBAL)
    {
#if(_OSD_POSITION_OFFSET_CORRECTION == _OFF)
        SET_OSD_POSITION_GOLOBAL_OFFSET_H(ucHOffset);
        SET_OSD_POSITION_GOLOBAL_OFFSET_V(ucVOffset);

        ucVOffset = ScalerOsdPositionOffsetVerticalAlignByDVBGStart(ucVOffset);
#endif

        ScalerSetByte(P3A_2C_FRAME_CTRL_2C, ucVOffset);
        ScalerSetByte(P3A_2F_FRAME_CTRL_2F, ucHOffset);
    }
    else
    {
        // adjust OSD window V start
        ucVOffset = OSD_POSITION_OFFSET_WINDOW_V_OFFSET_ADJUST(ucVOffset);

        ScalerSetBit(P3A_32_FRAME_CTRL_32, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((ucVOffset & 0x0F) << 4));
        ScalerSetBit(P3A_32_FRAME_CTRL_32, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ucHOffset & 0x0F));
    }
}

