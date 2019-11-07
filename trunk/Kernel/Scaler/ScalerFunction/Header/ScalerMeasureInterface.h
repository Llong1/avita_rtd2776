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
// ID Code      : ScalerMeasureInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************

//--------------------------------------------------
// Macros of Picture Active Measurement Result
//--------------------------------------------------
#define GET_ACTIVE_V_START()                         (g_pstRegionTimingInfoPointer->stAutoActiveData.usVActiveStart)
#define GET_ACTIVE_V_END()                           (g_pstRegionTimingInfoPointer->stAutoActiveData.usVActiveEnd)
#define GET_ACTIVE_H_START()                         (g_pstRegionTimingInfoPointer->stAutoActiveData.usHActiveStart)
#define GET_ACTIVE_H_END()                           (g_pstRegionTimingInfoPointer->stAutoActiveData.usHActiveEnd)
#define GET_ACTIVE_H_WIDTH()                         ((g_pstRegionTimingInfoPointer->stAutoActiveData.usHActiveEnd - g_pstRegionTimingInfoPointer->stAutoActiveData.usHActiveStart) + 1)
#define GET_ACTIVE_V_HEIGHT()                        ((g_pstRegionTimingInfoPointer->stAutoActiveData.usVActiveEnd - g_pstRegionTimingInfoPointer->stAutoActiveData.usVActiveStart) + 1)

//--------------------------------------------------
// Macros of Sync Measurement Result
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
// Macros of Input Timing Info.
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
// Macros of input timing info. modification
//--------------------------------------------------
#define SET_INPUT_TIMING_HSTART(x)                   (g_pstRegionTimingInfoPointer->stTimingInfo.usHStart = (x))
#define SET_INPUT_TIMING_HWIDTH(x)                   (g_pstRegionTimingInfoPointer->stTimingInfo.usHWidth = (x))
#define SET_INPUT_TIMING_HTOTAL(x)                   (g_pstRegionTimingInfoPointer->stTimingInfo.usHTotal = (x))

#define SET_INPUT_TIMING_VSTART(x)                   (g_pstRegionTimingInfoPointer->stTimingInfo.usVStart = (x))
#define SET_INPUT_TIMING_VHEIGHT(x)                  (g_pstRegionTimingInfoPointer->stTimingInfo.usVHeight = (x))
#define SET_INPUT_TIMING_VTOTAL(x)                   (g_pstRegionTimingInfoPointer->stTimingInfo.usVTotal = (x))

//--------------------------------------------------
// Macros of region timing info.
//--------------------------------------------------
#define GET_RGN_TIMING_H_POLARITY(region)            (g_pstRegionTimingInfo[ScalerRegionGetIndex(region)].stTimingInfo.b1HSP)
#define GET_RGN_TIMING_V_POLARITY(region)            (g_pstRegionTimingInfo[ScalerRegionGetIndex(region)].stTimingInfo.b1VSP)
#define GET_RGN_TIMING_INTERLACE_FLG(region)         (g_pstRegionTimingInfo[ScalerRegionGetIndex(region)].stTimingInfo.b1Interlace)
#define GET_RGN_TIMING_DATA_PATH(region)             (g_pstRegionTimingInfo[ScalerRegionGetIndex(region)].stTimingInfo.enumInputDataPath)
#define GET_RGN_TIMING_HFREQ(region)                 (g_pstRegionTimingInfo[ScalerRegionGetIndex(region)].stTimingInfo.usHFreq)
#define GET_RGN_TIMING_HTOTAL(region)                (g_pstRegionTimingInfo[ScalerRegionGetIndex(region)].stTimingInfo.usHTotal)
#define GET_RGN_TIMING_HWIDTH(region)                (g_pstRegionTimingInfo[ScalerRegionGetIndex(region)].stTimingInfo.usHWidth)
#define GET_RGN_TIMING_HSTART(region)                (g_pstRegionTimingInfo[ScalerRegionGetIndex(region)].stTimingInfo.usHStart)
#define GET_RGN_TIMING_HSYNCWIDTH(region)            (g_pstRegionTimingInfo[ScalerRegionGetIndex(region)].stTimingInfo.usHSWidth)
#define GET_RGN_TIMING_VFREQ(region)                 (g_pstRegionTimingInfo[ScalerRegionGetIndex(region)].stTimingInfo.usVFreq)
#define GET_RGN_TIMING_VTOTAL(region)                (g_pstRegionTimingInfo[ScalerRegionGetIndex(region)].stTimingInfo.usVTotal)
#define GET_RGN_TIMING_VHEIGHT(region)               (g_pstRegionTimingInfo[ScalerRegionGetIndex(region)].stTimingInfo.usVHeight)
#define GET_RGN_TIMING_VSTART(region)                (g_pstRegionTimingInfo[ScalerRegionGetIndex(region)].stTimingInfo.usVStart)
#define GET_RGN_TIMING_VSYNCWIDTH(region)            (g_pstRegionTimingInfo[ScalerRegionGetIndex(region)].stTimingInfo.usVSWidth)

//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************

extern StructRegionTimingInfo g_pstRegionTimingInfo[_MULTI_DISPLAY_MAX];
extern StructRegionTimingInfo *g_pstRegionTimingInfoPointer;


//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
extern void ScalerMeasureSetIndex(EnumRegionIndex enumRegionIndex);
extern void ScalerMeasureSetInputPath(EnumInputDataPath enumInputDataPath);
extern bit ScalerMeasureInputInfo(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort);

#if(_VGA_SUPPORT == _ON)
extern bit ScalerMeasureVgaInputInfo(void);
#endif

extern void ScalerMeasureSetOnlineMeasure(EnumInputDataPath enumInputDataPath);

#if(_MULTI_DISPLAY_MAX != 0x01)
extern bit ScalerMeasureDuplicateInputInfo(BYTE ucDuplicateIndex);
#endif
