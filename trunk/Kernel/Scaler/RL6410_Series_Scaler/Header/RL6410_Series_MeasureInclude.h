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
// ID Code      : RL6410_Series_MeasureInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _ACTIVE_REGION_TYPE = 0x00,
    _WHOLE_FRAME_TYPE = _BIT3,
    _BACK_PORCH_TYPE = _BIT4,
    _FRONT_PORCH_TYPE = (_BIT4 | _BIT3),
}EnumActiveRegionType;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern bit ScalerMeasureFinalSetting(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort);
extern bit ScalerMeasureCheckVsBypass(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort);
extern void ScalerMeasureAutoFuncVBoundInitial(WORD usVBoundStart, WORD usVBoundEnd, EnumInputDataPath enumInputDataPath);
extern bit ScalerMeasureGetAutoResult(StructAutoActiveData *pstActiveRegion, EnumInputDataPath enumInputDataPath, bit bWait);
extern void ScalerMeasureUpdateInputTimingPolarity(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort, StructMeasureSyncData *pstMeasureSyncHV);
extern bit ScalerMeasureGetOfflineMeasureResult(StructMeasureSyncData *pstMeasureSyncHV);
extern bit ScalerMeasureGetOnlineMeasureResult(StructMeasureSyncData *pstMeasureSyncHV, EnumInputDataPath enumInputDataPath);
extern void ScalerMeasureSetAuto(EnumMeasureFieldSelect enumFieldSelect, EnumInputDataPath enumInputDataPath);
extern void ScalerMeasureSetInputRegionCount(EnumInputDataPath enumInputDataPath, EnumActiveRegionType enumRegion);
extern void ScalerMeasureSetDisplayRegionCount(EnumDisplayDataPath enumDisplayDataPath, EnumActiveRegionType enumRegion);
extern void ScalerMeasureSetOfflineMeasure(EnumSourceSearchPort enumSourcePort);
extern void ScalerMeasureInitialSetting(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort);
extern void ScalerMeasureInterfaceInitial(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort *penumSourceSearchPort);
extern void ScalerMeasureUpdateInputTimingData(StructMeasureSyncData *pstMeasureSyncHV, StructAutoActiveData *pstActiveRegion);
extern bit ScalerMeasureInterlaceCheck(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort);
extern void ScalerMeasureInterlaceInitial(EnumSourceTypeDef enumSourceType, EnumSourceSearchPort enumSourceSearchPort);

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
extern void ScalerMeasureCheckFirstLineShift(EnumSourceSearchPort enumSourceSearchPort, WORD usFrameHwidth);

#if(_DUAL_DVI_SUPPORT == _ON)
extern bit ScalerMeasureDualDviMergedCheck(EnumSourceSearchPort enumSourceSearchPort);
extern bit ScalerMeasureDualDviOfflineCheck(EnumSourceSearchPort enumSourceSearchPort);
#endif

#endif

#if(_MULTI_DISPLAY_MAX != 0x01)
extern bit ScalerMeasureDuplicateFinalSetting(BYTE ucDuplicateIndex);
#endif

