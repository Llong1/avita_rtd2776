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
// ID Code      : ScalerVGATopInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_VGA_SUPPORT == _ON)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************

//--------------------------------------------------
// Definitions of HS Phase Delay Calibration
//--------------------------------------------------
#define _HS_DELAY_DVTOTAL                           (100UL) // line
#define _HS_DELAY_TARGET_DHFREQ                     (3600UL) // 0.1KHz
#define _HS_DELAY_DHTOTAL                           ((WORD)(GET_D_CLK_FREQ() * 10 / _HS_DELAY_TARGET_DHFREQ)) // pixel
#define _HS_DELAY_REAL_DHFREQ                       ((WORD)(GET_D_CLK_FREQ() * 10 / _HS_DELAY_DHTOTAL)) // 0.1kHz
#define _HS_DELAY_ICLK_RATE                         (200UL) // MHz
#define _HS_DELAY_IHTOTAL                           ((DWORD)_HS_DELAY_DHTOTAL * 1000 * _HS_DELAY_ICLK_RATE / GET_D_CLK_FREQ())

#define SET_HS_DELAY_LATCH_EDGE()                   {\
                                                        ScalerSetBit(P30_A2_VGATOP_VGIP_DELAY_CTRL, ~_BIT3, 0x00);\
                                                    }

#define SAVE_HS_DELAY_SETTING(pucBackup)            {\
                                                        ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_00_DISPLAY_HOR_TOTAL_H, 3, (pucBackup), _AUTOINC);\
                                                        (pucBackup)[3] = ScalerGetByte(P1_C6_DCLK_SPREAD_SPECTRUM);\
                                                        ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_30_FIXED_DVTOTAL_MSB, 4, &((pucBackup)[4]), _AUTOINC);\
                                                    }

#define LOAD_HS_DELAY_SETTING(pucBackup)            {\
                                                        ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_00_DISPLAY_HOR_TOTAL_H, (pucBackup)[0]);\
                                                        ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_01_DISPLAY_HOR_TOTAL_L, (pucBackup)[1]);\
                                                        ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_02_DISPLAY_HOR_SYNC_END, (pucBackup)[2]);\
                                                        ScalerSetByte(P1_C6_DCLK_SPREAD_SPECTRUM, (pucBackup)[3]);\
                                                        ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_30_FIXED_DVTOTAL_MSB, (pucBackup)[4]);\
                                                        ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_31_FIXED_DVTOTAL_LSB, (pucBackup)[5]);\
                                                        ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_32_FIXED_LAST_LINE_MSB, (pucBackup)[6]);\
                                                        ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_33_FIXED_LAST_LINE_LSB, (pucBackup)[7]);\
                                                    }

//--------------------------------------------------
// VGA Mode Table Start
//--------------------------------------------------
#define GET_VGA_MODE_HSTART()                       (g_usVgaModeHstart)
#define SET_VGA_MODE_HSTART(x)                      (g_usVgaModeHstart = (x))

#define GET_VGA_MODE_VSTART()                       (g_usVgaModeVstart)
#define SET_VGA_MODE_VSTART(x)                      (g_usVgaModeVstart = (x))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//--------------------------------------------------
// Enumerations of VGATOP Waiting Events (P30_E4)
//--------------------------------------------------
typedef enum
{
    _EVENT_VGA_IVS = _BIT4,
    _EVENT_VGA_IEN_START = _BIT5,
    _EVENT_VGA_IEN_STOP = _BIT6,
} EnumVgaTopWaitEventType;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

extern WORD g_usPhaseDelayTime;

extern WORD g_usVgaModeHstart;
extern WORD g_usVgaModeVstart;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern bit ScalerVgaTopModifyVsLatchEdge(bit bWait);
extern void ScalerVgaTopModifyPolarity(void);
extern void ScalerVgaTopAutoFuncHBoundInitial(WORD usHBoundStart, WORD usHBoundEnd);
extern void ScalerVgaTopAutoFuncVBoundInitial(WORD usVBoundStart, WORD usVBoundEnd);
extern void ScalerVgaTopSetAuto(EnumMeasureFieldSelect enumFieldSelect, EnumMeasureBoundType enumBoundType, WORD usHTotal);
extern bit ScalerVgaTopGetAutoResult(StructAutoActiveData *pstActiveRegion, bit bWait);
extern bit ScalerVgaTopAutoFuncWaitFinish(void);
extern bit ScalerVgaTopWaitForEvent(EnumVgaTopWaitEventType enumEvent);
extern void ScalerVgaTopDoubleBufferApply(void);
extern void ScalerVgaTopDoubleBufferEnable(bit bEn);

extern WORD ScalerVgaTopGetCaptureVStartPosition(void);
extern void ScalerVgaTopSetCaptureVStartPosition(WORD usIVstart);

extern void ScalerVgaTopSetCaptureVHeight(WORD usIVheight);
extern WORD ScalerVgaTopGetCaptureVDelay(void);
extern void ScalerVgaTopSetCaptureVDelay(WORD usIVSDelay);
extern WORD ScalerVgaTopGetCaptureHStartPosition(void);
extern void ScalerVgaTopSetCaptureHStartPosition(WORD usIHstart);
extern void ScalerVgaTopSetCaptureHWidth(WORD usIHwidth);
extern WORD ScalerVgaTopGetCaptureHDelay(void);
extern void ScalerVgaTopSetCaptureHDelay(WORD usIHSDelay);
extern void ScalerVgaTopSetCapture(void);

#endif // End of #if(_VGA_SUPPORT == _ON)
