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
// ID Code      : ScalerSyncInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************

#if(_DIGITAL_PORT_SUPPORT == _ON)
//--------------------------------------------------
// Macros of HDMI HotPlug Toggle Support
//--------------------------------------------------
#define GET_DP_DC_OFF_HPD_HIGH()                            (g_bDpDCOffHPDHigh)
#define SET_DP_DC_OFF_HPD_HIGH()                            (g_bDpDCOffHPDHigh = _TRUE)
#define CLR_DP_DC_OFF_HPD_HIGH()                            (g_bDpDCOffHPDHigh = _FALSE)

#define GET_HDMI_HOTPLUG_TOGGLE()                           ((g_ucHDMIHotPlug & _BIT7) >> 7)
#define SET_HDMI_HOTPLUG_TOGGLE()                           (g_ucHDMIHotPlug |= _BIT7)
#define CLR_HDMI_HOTPLUG_TOGGLE()                           (g_ucHDMIHotPlug &= ~_BIT7)

#define GET_HDMI_HOTPLUG_TIME()                             ((WORD)(g_ucHDMIHotPlug & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) * 100)
#define SET_HDMI_HOTPLUG_TIME(x)                            (g_ucHDMIHotPlug = (g_ucHDMIHotPlug & ~(_BIT3 | _BIT2 | _BIT1 | _BIT0)) | (x))

//--------------------------------------------------
// Macros of Digital Color Change Reset Enable
//--------------------------------------------------
#define GET_DIGITAL_COLOR_INFO_CHANGE_RESET()               (g_bDigitalColorInfoChangeReset)
#define SET_DIGITAL_COLOR_INFO_CHANGE_RESET()               (g_bDigitalColorInfoChangeReset = _TRUE)
#define CLR_DIGITAL_COLOR_INFO_CHANGE_RESET()               (g_bDigitalColorInfoChangeReset = _FALSE)

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of DP Marginal Link
//--------------------------------------------------
#define GET_DP_RX_D0_MARGIN_LINK_HBR_RBR()                  (g_stDpMarginLink.b1D0MarginLinkHBRRBR)
#define SET_DP_RX_D0_MARGIN_LINK_HBR_RBR()                  (g_stDpMarginLink.b1D0MarginLinkHBRRBR = _TRUE)
#define CLR_DP_RX_D0_MARGIN_LINK_HBR_RBR()                  (g_stDpMarginLink.b1D0MarginLinkHBRRBR = _FALSE)

#define GET_DP_RX_D1_MARGIN_LINK_HBR_RBR()                  (g_stDpMarginLink.b1D1MarginLinkHBRRBR)
#define SET_DP_RX_D1_MARGIN_LINK_HBR_RBR()                  (g_stDpMarginLink.b1D1MarginLinkHBRRBR = _TRUE)
#define CLR_DP_RX_D1_MARGIN_LINK_HBR_RBR()                  (g_stDpMarginLink.b1D1MarginLinkHBRRBR = _FALSE)

#define GET_DP_RX_D2_MARGIN_LINK_HBR_RBR()                  (g_stDpMarginLink.b1D2MarginLinkHBRRBR)
#define SET_DP_RX_D2_MARGIN_LINK_HBR_RBR()                  (g_stDpMarginLink.b1D2MarginLinkHBRRBR = _TRUE)
#define CLR_DP_RX_D2_MARGIN_LINK_HBR_RBR()                  (g_stDpMarginLink.b1D2MarginLinkHBRRBR = _FALSE)

#define GET_DP_RX_D6_MARGIN_LINK_HBR_RBR()                  (g_stDpMarginLink.b1D6MarginLinkHBRRBR)
#define SET_DP_RX_D6_MARGIN_LINK_HBR_RBR()                  (g_stDpMarginLink.b1D6MarginLinkHBRRBR = _TRUE)
#define CLR_DP_RX_D6_MARGIN_LINK_HBR_RBR()                  (g_stDpMarginLink.b1D6MarginLinkHBRRBR = _FALSE)
#endif

#endif

//--------------------------------------------------
// Macros of HDR Support
//--------------------------------------------------
#if(_ULTRA_HDR_SUPPORT == _ON)
#define SET_HDR_INFO_DATA(region, x)                        (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)] = (x))

#define GET_HDR_EOTF(region)                                (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].ucEOTF)
#define SET_HDR_EOTF(region, x)                             (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].ucEOTF = (x))
#define CLR_HDR_EOTF(region)                                (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].ucEOTF = _FALSE)

#define GET_HDR_METADATA_ID(region)                         (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].ucStaticMetadataID)
#define SET_HDR_METADATA_ID(region, x)                      (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].ucStaticMetadataID = (x))
#define CLR_HDR_METADATA_ID(region)                         (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].ucStaticMetadataID = _FALSE)

#define GET_HDR_DISPALY_PRIMARIES_X0(region)                (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].usDisplayPrimariesX0)
#define SET_HDR_DISPALY_PRIMARIES_X0(region, x)             (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].usDisplayPrimariesX0 = (x))
#define CLR_HDR_DISPALY_PRIMARIES_X0(region)                (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].usDisplayPrimariesX0 = (0))

#define GET_HDR_DISPALY_PRIMARIES_Y0(region)                (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].usDisplayPrimariesY0)
#define SET_HDR_DISPALY_PRIMARIES_Y0(region, x)             (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].usDisplayPrimariesY0 = (x))
#define CLR_HDR_DISPALY_PRIMARIES_Y0(region)                (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].usDisplayPrimariesY0 = (0))

#define GET_HDR_DISPALY_PRIMARIES_X1(region)                (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].usDisplayPrimariesX1)
#define SET_HDR_DISPALY_PRIMARIES_X1(region, x)             (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].usDisplayPrimariesX1 = (x))
#define CLR_HDR_DISPALY_PRIMARIES_X1(region)                (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].usDisplayPrimariesX1 = (0))

#define GET_HDR_DISPALY_PRIMARIES_Y1(region)                (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].usDisplayPrimariesY1)
#define SET_HDR_DISPALY_PRIMARIES_Y1(region, x)             (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].usDisplayPrimariesY1 = (x))
#define CLR_HDR_DISPALY_PRIMARIES_Y1(region)                (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].usDisplayPrimariesY1 = (0))

#define GET_HDR_DISPALY_PRIMARIES_X2(region)                (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].usDisplayPrimariesX2)
#define SET_HDR_DISPALY_PRIMARIES_X2(region, x)             (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].usDisplayPrimariesX2 = (x))
#define CLR_HDR_DISPALY_PRIMARIES_X2(region)                (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].usDisplayPrimariesX2 = (0))

#define GET_HDR_DISPALY_PRIMARIES_Y2(region)                (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].usDisplayPrimariesY2)
#define SET_HDR_DISPALY_PRIMARIES_Y2(region, x)             (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].usDisplayPrimariesY2 = (x))
#define CLR_HDR_DISPALY_PRIMARIES_Y2(region)                (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].usDisplayPrimariesY2 = (0))

#define GET_HDR_WHITE_POINT_X(region)                       (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].usWhitePointX)
#define SET_HDR_WHITE_POINT_X(region, x)                    (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].usWhitePointX = (x))
#define CLR_HDR_WHITE_POINT_X(region)                       (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].usWhitePointX = (0))

#define GET_HDR_WHITE_POINT_Y(region)                       (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].usWhitePointY)
#define SET_HDR_WHITE_POINT_Y(region, x)                    (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].usWhitePointY = (x))
#define CLR_HDR_WHITE_POINT_Y(region)                       (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].usWhitePointY = (0))

#define GET_HDR_MAX_DISPLAY_MASTERING_LV(region)            (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].usMaxDisplayMasteringLv)
#define SET_HDR_MAX_DISPLAY_MASTERING_LV(region, x)         (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].usMaxDisplayMasteringLv = (x))
#define CLR_HDR_MAX_DISPLAY_MASTERING_LV(region)            (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].usMaxDisplayMasteringLv = (0))

#define GET_HDR_MIN_DISPLAY_MASTERING_LV(region)            (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].usMinDisplayMasteringLv)
#define SET_HDR_MIN_DISPLAY_MASTERING_LV(region, x)         (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].usMinDisplayMasteringLv = (x))
#define CLR_HDR_MIN_DISPLAY_MASTERING_LV(region)            (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].usMinDisplayMasteringLv = (0))

#define GET_HDR_MAX_CLL(region)                             (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].usMaxCLL)
#define SET_HDR_MAX_CLL(region, x)                          (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].usMaxCLL = (x))
#define CLR_HDR_MAX_CLL(region)                             (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].usMaxCLL = (0))

#define GET_HDR_MAX_FALL(region)                            (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].usMaxFALL)
#define SET_HDR_MAX_FALL(region, x)                         (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].usMaxFALL = (x))
#define CLR_HDR_MAX_FALL(region)                            (g_pstHDRSaticMetadata[ScalerRegionGetIndex(region)].usMaxFALL = (0))
#endif

typedef enum
{
    _HDR_EOTF_CHG = _BIT0,
    _HDR_DIS_PRIMARIES_CHG = _BIT1,
    _HDR_MAX_LUM_CHG = _BIT2,
}EnumHDRChange;

//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************

#if(_DIGITAL_PORT_SUPPORT == _ON)
extern BYTE g_ucDigitalSwitch;
extern bit g_bDpDCOffHPDHigh;
extern BYTE g_ucHDMIHotPlug;
extern bit g_bDigitalColorInfoChangeReset;

#if(_DP_SUPPORT == _ON)
extern StructDPMarginLinkInfo g_stDpMarginLink;
#endif

#endif

#if(_ULTRA_HDR_SUPPORT == _ON)
extern StructHDRStaticMetaData g_pstHDRSaticMetadata[_MULTI_DISPLAY_MAX];
#endif

//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
#if(_FREESYNC_SUPPORT == _ON)
extern bit ScalerSyncGetFREESYNCEnable(void);
extern void ScalerSyncSetFREESYNCSupport(bit bEnable);

#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
extern BYTE ScalerSyncGetHDMIFREESYNCVcp_EXINT1(void);
extern void ScalerSyncSetHDMIFREESYNCVcp_EXINT1(BYTE ucVcpCode);
#endif
#endif

#if(_ULTRA_HDR_SUPPORT == _ON)
extern bit ScalerSyncHDRGetCurrentStatus(StructHDRStaticMetaData *pstHDRSaticMetadata, EnumSourceSearchPort enumSourceSearchPort);

#if(_DP_SUPPORT == _ON)
extern void ScalerSyncDPHDRInfoFrameRSV0Check(EnumSourceSearchPort enumSourceSearchPort);
extern void ScalerSyncDPHDRInfoFramePacketDetect(EnumSourceSearchPort enumSourceSearchPort);
#endif
#endif

#if(_DP_SUPPORT == _ON)
extern void ScalerSyncDpScanInitial(BYTE ucInputPort);
extern void ScalerSyncDpSecDataReset(BYTE ucInputPort);
extern bit ScalerSyncDpNormalPreDetect(BYTE ucInputPort);
extern BYTE ScalerSyncDpScanInputPort(BYTE ucInputPort);
extern bit ScalerSyncDpPSPreDetect(BYTE ucInputPort);
extern bit ScalerSyncDpStableDetect(BYTE ucInputPort);
extern void ScalerSyncDpCapabilitySwitchProc(void);
extern void ScalerSyncJudgeHPDToggle(EnumPowerAction enumPowerAction);

#if(_DP_FREESYNC_SUPPORT == _ON)
extern void ScalerSyncDpFREESYNCSupportSwitch(EnumDpFREESYNCCapabilitySwitch enumDpFREESYNCCapSwitch, bit bEn);
#endif

#if((_DP_TX_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))
extern bit ScalerSyncDpFakePowerSavingCheck(void);
#endif

#if(_DP_TX_SUPPORT == _ON)
void ScalerSyncDpTxHdcpUpstreamSwitchProc(EnumDisplayMode enumDisplayMode, BYTE ucInputPort);
#endif
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
#if(_DP_TX_SUPPORT == _ON)
extern void ScalerSyncHdcpEnableDownLoadDPTxKey(bit bEnable);
extern void ScalerSyncHdcpDownLoadDPTxAKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
extern void ScalerSyncHdcpDownLoadDPTxAKey(WORD usLength, BYTE *pucReadArray);
#endif

extern bit ScalerSyncHdcpCheckEnabled(BYTE ucInputPort);
#endif

#if(_URGENT_EVENT_CHECK_MODE == _ON)
extern bit ScalerSyncCheckUrgentEvent(void);
extern bit ScalerSyncGetUrgentEventFlg(void);
extern void ScalerSyncClrUrgentEventFlg(void);
#endif

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
extern BYTE ScalerSyncDdcDetect_EXINT1(void);

#if(_HDMI_SUPPORT == _ON)
extern void ScalerSyncTMDSEdidSwitch(BYTE ucPortSelect);
extern void ScalerSyncHDMIDdcCheckBusy(BYTE ucInputPort);
#endif
extern void ScalerSyncTMDSHPDToggleProc(void);

#if(_DUAL_DVI_SUPPORT == _ON)
extern bit ScalerSyncGetDualDVIMode(EnumSourceSearchPort enumInputPort);
#endif
#endif

#if(_MHL_SUPPORT == _ON)
extern bit ScalerSyncMHLVBusPowerExist(void);
#endif

extern void ScalerSyncActiveProc(BYTE ucSourceType);
extern void ScalerSyncResetProc(BYTE ucInputPort);
extern void ScalerSyncPowerProc(EnumPowerAction enumPowerAction);
extern void ScalerSyncAdcApllPowerDown(void);
extern void ScalerSyncSetDdcForceNack(BYTE ucInputPort, bit bSelect);
extern bit ScalerSyncGetDdcForceNackStatus(BYTE ucInputPort);

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
extern void ScalerSyncInterfaceRx0Proc(bit bEnable);
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
extern void ScalerSyncInterfaceRx1Proc(bit bEnable);
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
extern void ScalerSyncInterfaceRx2Proc(bit bEnable);
#endif

#if((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
extern void ScalerSyncInterfaceRx3Proc(bit bEnable);
#endif

#if((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
extern void ScalerSyncInterfaceRx4Proc(bit bEnable);
#endif

#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
extern void ScalerSyncInterfaceRx5Proc(bit bEnable);
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
extern bit ScalerSyncDigitalGetColorimetryChanged(EnumSourceSearchPort enumSourceSearchPort);
extern bit ScalerSyncDigitalGetColorimetryExtChanged(EnumSourceSearchPort enumSourceSearchPort);
extern bit ScalerSyncDigitalGetQuantizationChanged(EnumSourceSearchPort enumSourceSearchPort);
extern void ScalerSyncDigitalClrColorimetryChanged(EnumSourceSearchPort enumSourceSearchPort);
extern void ScalerSyncDigitalClrColorimetryExtChanged(EnumSourceSearchPort enumSourceSearchPort);
extern void ScalerSyncDigitalClrQuantizationChanged(EnumSourceSearchPort enumSourceSearchPort);
#endif
