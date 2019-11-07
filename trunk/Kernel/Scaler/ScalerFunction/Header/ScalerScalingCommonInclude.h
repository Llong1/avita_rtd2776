/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2011>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : ScalerScalingCommonInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#define GET_MDOMAIN_EXTENSION_LEN()                  (ScalerGetDataPortBit(P0_30_FIFO_WINDOW_ADDR_PORT, _P0_31_PT_08_DISPLAY_READ_EXTENSION_MAIN, 0x1F))
#define SET_MDOMAIN_EXTENSION_LEN(x)                 (ScalerSetDataPortBit(P0_30_FIFO_WINDOW_ADDR_PORT, _P0_31_PT_08_DISPLAY_READ_EXTENSION_MAIN, ~0x1F, ((BYTE)(x) & 0x1F)))

#define GET_DDOMAIN_EXTENSION_LEN()                  (ScalerGetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_1F_DISPLAY_EXTENSION_FB_MAIN, 0xFF))
#define SET_DDOMAIN_EXTENSION_LEN(x)                 (ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_1F_DISPLAY_EXTENSION_FB_MAIN, ~0xFF, ((BYTE)(x) & 0xFF)))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
