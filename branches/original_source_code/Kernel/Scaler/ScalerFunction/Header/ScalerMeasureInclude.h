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
// ID Code      : ScalerMeasureInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of Measure Clock Frequency
//--------------------------------------------------
#define _MEASURE_CLK_DIV                             (ScalerGetBit(P40_07_MEASURE_CLK_DIVIDER, (_BIT3 | _BIT2 | _BIT1 | _BIT0)))
#define _MEASURE_USE_M2PLL_CLK                       ((bit)ScalerGetBit(P40_07_MEASURE_CLK_DIVIDER, _BIT4) ? _TRUE : _FALSE)
#define _MEASURE_CLK                                 (DWORD)((bit)ScalerGetBit(P1_E5_M2PLL_WD, _BIT0) ? _EXT_XTAL : (_MEASURE_USE_M2PLL_CLK ? (((DWORD)_M2PLL_CLK_KHZ) / _MEASURE_CLK_DIV) : _EXT_XTAL))

//--------------------------------------------------
// Definitions Of Measure Polling Time
// timeout clk = measure clk / 16384
// timeout = 512 / timeout clock + 10(tolerance) (ms)
// reset time = 1 / timeout clock, with min = 2 (ms)
//--------------------------------------------------
#define _MEASURE_TIMEOUT_CLK                         (_MEASURE_CLK / (16384 / 10)) // (0.1k)
#define _MEASURE_TIMEOUT                             ((WORD)(((DWORD)512 * 10 / _MEASURE_TIMEOUT_CLK) + 10)) // (ms)
#define _MEASURE_RESET_TIME                          ((_MEASURE_TIMEOUT_CLK >= 10) ? 2 : (2 * 10 / _MEASURE_TIMEOUT_CLK)) // (ms)

//--------------------------------------------------
// Definitions of Measure block limitation
//--------------------------------------------------
#define _MEASURE_H_FREQ_MIN                          (_MEASURE_CLK * 10 / (WORD)0x1FFF) // Unit: 0.1k

//--------------------------------------------------
// Macro of Sync Measurement Result
//--------------------------------------------------
#define GET_INPUT_TIMING_H_POLARITY()                (g_pstRegionTimingInfoPointer->stTimingInfo.b1HSP)
#define GET_INPUT_TIMING_V_POLARITY()                (g_pstRegionTimingInfoPointer->stTimingInfo.b1VSP)
#define GET_INPUT_TIMING_INTERLACE_FLG()             (g_pstRegionTimingInfoPointer->stTimingInfo.b1Interlace)
#define GET_INPUT_TIMING_DATA_PATH()                 (g_pstRegionTimingInfoPointer->stTimingInfo.enumInputDataPath)
#define GET_INPUT_TIMING_HFREQ()                     (g_pstRegionTimingInfoPointer->stTimingInfo.usHFreq)
#define GET_INPUT_TIMING_HTOTAL()                    (g_pstRegionTimingInfoPointer->stTimingInfo.usHTotal)
#define GET_INPUT_TIMING_HWIDTH()                    (g_pstRegionTimingInfoPointer->stTimingInfo.usHWidth)
#define GET_INPUT_TIMING_HSTART()                    (g_pstRegionTimingInfoPointer->stTimingInfo.usHStart)
#define GET_INPUT_TIMING_HSYNCWIDTH()                (g_pstRegionTimingInfoPointer->stTimingInfo.usHSWidth)
#define GET_INPUT_TIMING_VFREQ()                     (g_pstRegionTimingInfoPointer->stTimingInfo.usVFreq)
#define GET_INPUT_TIMING_VTOTAL()                    (g_pstRegionTimingInfoPointer->stTimingInfo.usVTotal)
#define GET_INPUT_TIMING_VHEIGHT()                   (g_pstRegionTimingInfoPointer->stTimingInfo.usVHeight)
#define GET_INPUT_TIMING_VSTART()                    (g_pstRegionTimingInfoPointer->stTimingInfo.usVStart)
#define GET_INPUT_TIMING_VSYNCWIDTH()                (g_pstRegionTimingInfoPointer->stTimingInfo.usVSWidth)

//--------------------------------------------------
// Macro of Sync Measurement Result
//--------------------------------------------------
#define GET_SYNC_H_POLARITY()                        (g_pstRegionTimingInfoPointer->stMeasureSyncData.b1HSP)
#define GET_SYNC_V_POLARITY()                        (g_pstRegionTimingInfoPointer->stMeasureSyncData.b1VSP)
#define GET_SYNC_H_PERIOD()                          (g_pstRegionTimingInfoPointer->stMeasureSyncData.usHSPeriod)
#define GET_SYNC_H_SYNCWIDTH()                       (g_pstRegionTimingInfoPointer->stMeasureSyncData.usHSWidth)
#define GET_SYNC_V_PERIOD()                          (g_pstRegionTimingInfoPointer->stMeasureSyncData.usVSPeriod)
#define GET_SYNC_V_SYNCWIDTH()                       (g_pstRegionTimingInfoPointer->stMeasureSyncData.usVSWidth)
#define GET_SYNC_H_TOTAL()                           (g_pstRegionTimingInfoPointer->stMeasureSyncData.usHTotal)
#define GET_SYNC_H_WIDTH()                           (g_pstRegionTimingInfoPointer->stMeasureSyncData.usHWidth)
#define GET_SYNC_V_HEIGHT()                          (g_pstRegionTimingInfoPointer->stMeasureSyncData.usVHeight)

//--------------------------------------------------
// Macro of Active Measurement Result
//--------------------------------------------------
#define GET_ACTIVE_V_START()                         (g_pstRegionTimingInfoPointer->stAutoActiveData.usVActiveStart)
#define GET_ACTIVE_V_END()                           (g_pstRegionTimingInfoPointer->stAutoActiveData.usVActiveEnd)
#define GET_ACTIVE_H_START()                         (g_pstRegionTimingInfoPointer->stAutoActiveData.usHActiveStart)
#define GET_ACTIVE_H_END()                           (g_pstRegionTimingInfoPointer->stAutoActiveData.usHActiveEnd)
#define GET_ACTIVE_H_WIDTH()                         ((g_pstRegionTimingInfoPointer->stAutoActiveData.usHActiveEnd - g_pstRegionTimingInfoPointer->stAutoActiveData.usHActiveStart) + 1)
#define GET_ACTIVE_V_HEIGHT()                        ((g_pstRegionTimingInfoPointer->stAutoActiveData.usVActiveEnd - g_pstRegionTimingInfoPointer->stAutoActiveData.usVActiveStart) + 1)

//--------------------------------------------------
// Macro of input timing infor. modification
//--------------------------------------------------
#define SET_INPUT_TIMING_HSTART(x)                   (g_pstRegionTimingInfoPointer->stTimingInfo.usHStart = (x))
#define SET_INPUT_TIMING_HWIDTH(x)                   (g_pstRegionTimingInfoPointer->stTimingInfo.usHWidth = (x))
#define SET_INPUT_TIMING_HTOTAL(x)                   (g_pstRegionTimingInfoPointer->stTimingInfo.usHTotal = (x))

#define SET_INPUT_TIMING_VSTART(x)                   (g_pstRegionTimingInfoPointer->stTimingInfo.usVStart = (x))
#define SET_INPUT_TIMING_VHEIGHT(x)                  (g_pstRegionTimingInfoPointer->stTimingInfo.usVHeight = (x))
#define SET_INPUT_TIMING_VTOTAL(x)                   (g_pstRegionTimingInfoPointer->stTimingInfo.usVTotal = (x))

#define GET_MEASURE_INPUT_PATH()                     (g_pstRegionTimingInfoPointer->stTimingInfo.enumInputDataPath)
#define SET_MEASURE_INPUT_PATH(x)                    (g_pstRegionTimingInfoPointer->stTimingInfo.enumInputDataPath = (x))

#define GET_PAGED_ADDR(page, addr)                   ((WORD)(((WORD)((BYTE)(page)) << 8) | ((BYTE)(addr))))
#define SET_PAGED_BIT(page, pucAddr, ucAnd, ucOr)    (ScalerSetBit(GET_PAGED_ADDR((page), (pucAddr)), (ucAnd), (ucOr)))
#define GET_PAGED_BIT(page, pucAddr, ucAnd)          (ScalerGetBit(GET_PAGED_ADDR((page), (pucAddr)), (ucAnd)))
#define SET_PAGED_BYTE(page, pucAddr, ucValue)       (ScalerSetByte(GET_PAGED_ADDR((page), (pucAddr)), (ucValue)))
#define GET_PAGED_BYTE(page, pucAddr)                (ScalerGetByte(GET_PAGED_ADDR((page), (pucAddr))))


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

extern StructRegionTimingInfo g_pstRegionTimingInfo[_MULTI_DISPLAY_MAX];
extern StructRegionTimingInfo *g_pstRegionTimingInfoPointer;

extern DWORD g_ulInputActiveRegionBackUp;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerMeasureResetTimingInfo(EnumInputDataPath enumInputDataPath);
extern BYTE ScalerMeasureGetPageOffset(EnumInputDataPath enumInputDataPath);
extern bit ScalerMeasureGetStableMeasureResult(StructMeasureSyncData *pstMeasureSyncHV);

#if(_VGA_SUPPORT == _ON)
extern bit ScalerMeasureSetSourceResultIndex(EnumFormatConversionSourceType enumFormatConversionSourceType);
extern bit ScalerMeasureVgaInterlaceCheck(EnumSourceSearchPort enumSourceSearchPort);
#endif

extern bit ScalerMeasureCheckWDTriggerStatus(BYTE ucResultIndex);
extern bit ScalerMeasureInputActiveRegionChange(void);
extern EnumSourceSearchPort ScalerMeasureGetOfflineMeasurePort(void);
extern void ScalerMeasureSetOnlineMeasure(EnumInputDataPath enumInputDataPath);
extern DWORD ScalerMeasureGetInputRegionCountResult(bit bWait);
extern DWORD ScalerMeasureGetDisplayRegionCountResult(bit bWait);
extern bit ScalerMeasureAutoFuncWaitFinish(EnumInputDataPath enumInputDataPath);
extern void ScalerMeasureAutoFuncHBoundInitial(WORD usHBoundStart, WORD usHBoundEnd, EnumInputDataPath enumInputDataPath);

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
extern bit ScalerMeasureCheckInterlaceVst(WORD usVstart, WORD usVend);
#endif

