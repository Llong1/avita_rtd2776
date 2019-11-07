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
// ID Code      : RL6410_Series_FormatConversionCommonInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#define GET_FMTCNV_EXTENSION_LEN()                  (ScalerGetBit(P31_66_EXTENSION_NUM, 0x1F))
#define SET_FMTCNV_EXTENSION_LEN(x)                 {\
                                                        ScalerSetBit(P31_66_EXTENSION_NUM, ~0x1F, ((BYTE)(x) & 0x1F));\
                                                        ScalerSetBit(P35_30_EXTENSION_EXTRA_WIN, ~_BIT0, (((BYTE)(x) != 0) ? _BIT0 : 0x00));\
                                                    }

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern bit ScalerFmtCnvFBGetStatus(void);
