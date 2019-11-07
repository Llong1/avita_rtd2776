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
// ID Code      : RL6410_Series_MemoryInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#define SET_IVS2DVS_DELAY_16ICLK1(usBackup)         {\
                                                        ScalerSetBit(P0_3F_DISPLAY_ALIGN_CONTROL, ~(_BIT5 | _BIT4), ((HIBYTE(usBackup) & 0x03) << 4));\
                                                        ScalerSetByte(P0_41_IVS2DVS_DLY_TUNE_ODD, LOBYTE(usBackup));\
                                                    }

#define SET_IVS2DVS_DELAY_16ICLK2(usBackup)         {\
                                                        ScalerSetBit(P0_3F_DISPLAY_ALIGN_CONTROL, ~(_BIT1 | _BIT0), (HIBYTE(usBackup) & 0x03));\
                                                        ScalerSetByte(P0_42_IVS2DVS_DLY_TUNE_EVEN, LOBYTE(usBackup));\
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
extern void ScalerMemoryFrameSyncSetDt(void);
extern DWORD ScalerMemoryGetIVS2DVSDelayPixel(void);
