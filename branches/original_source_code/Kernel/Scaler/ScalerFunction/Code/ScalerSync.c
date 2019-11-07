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
// ID Code      : ScalerSync.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_SYNC__

#include "ScalerFunctionInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if((_DVI_SUPPORT != _ON) && (_HDMI_SUPPORT != _ON))
#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
#warning "Z0 Toggle Solution Is Not Available !!!!"
#endif
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE data pData_EXINT[6];

#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
WORD g_usA0PixelClk;
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
WORD g_usD0PixelClk;

#if(_D0_TMDS_SUPPORT == _ON)
WORD g_usTmdsD0OffLineMeasureClk;
#endif

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
BYTE g_ucDpRx0LTStatus = _DP_LINK_TRAINING_NONE;
#endif
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
WORD g_usD1PixelClk;

#if(_D1_TMDS_SUPPORT == _ON)
WORD g_usTmdsD1OffLineMeasureClk;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
BYTE g_ucDpRx1LTStatus = _DP_LINK_TRAINING_NONE;
#endif
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
WORD g_usD2PixelClk;
WORD g_usTmdsD2OffLineMeasureClk;
#endif

#if((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
WORD g_usD3PixelClk;
WORD g_usTmdsD3OffLineMeasureClk;
#endif

#if((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
WORD g_usD4PixelClk;
WORD g_usTmdsD4OffLineMeasureClk;
#endif

#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
WORD g_usD5PixelClk;
WORD g_usTmdsD5OffLineMeasureClk;
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
BYTE idata g_pucHdcpBksvBackup[5];
bit g_bDpDCOffHPDHigh = 0;
BYTE g_ucDigitalSwitch;
BYTE g_ucHDMIHotPlug;

#if(_DP_TX_SUPPORT == _ON)
BYTE idata g_pucHdcpAksvBackup[5];
#endif
#endif

#if(_DP_SUPPORT == _ON)
StructDPCapSwitchInfo g_stDpCapSwitch;
StructDPMarginLinkInfo g_stDpMarginLink;
#endif

#if(_DP_TX_SUPPORT == _ON)
StructDPTxStatusInfo g_stDpTxStatus;
StructDpTxColorInfo g_stDpTxColorInfo;
#endif

#if(_FREESYNC_SUPPORT == _ON)

#if(_DP_FREESYNC_SUPPORT == _ON)
StructDPFREESYNCENABLE g_stDpFREESYNCInfo;
#endif

#if(_HDMI_FREESYNC_SUPPORT == _ON)
StructHDMIFREESYNCENABLE g_stHDMIFREESYNCInfo;

#if(_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE)
BYTE g_ucHDMIFREESYNCVCPReceive;
#endif
#endif

BYTE g_ucFREESYNCSupport;
WORD g_usFREESYNCVFreq;
#endif

#if(_ULTRA_HDR_SUPPORT == _ON)
StructHDRStaticMetaData g_pstHDRSaticMetadata[_MULTI_DISPLAY_MAX];
#endif

#if(_URGENT_EVENT_CHECK_MODE == _ON)
BYTE g_ucCheckUrgentEventOccured;
#endif

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
WORD g_usDDCDebounceCnt;

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
bit g_bTMDSRx0Z0Toggle = 0;
bit g_bTMDSRx1Z0Toggle = 0;
bit g_bTMDSRx2Z0Toggle = 0;
bit g_bTMDSRx3Z0Toggle = 0;
bit g_bTMDSRx4Z0Toggle = 0;
bit g_bTMDSRx5Z0Toggle = 0;
bit g_bTMDSRx0GlobalZ0Toggle = 0;
bit g_bTMDSRx1GlobalZ0Toggle = 0;
bit g_bTMDSRx2GlobalZ0Toggle = 0;
bit g_bTMDSRx3GlobalZ0Toggle = 0;
bit g_bTMDSRx4GlobalZ0Toggle = 0;
bit g_bTMDSRx5GlobalZ0Toggle = 0;
#endif

#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
bit g_bDigitalColorInfoChangeReset;
StructDigitalColorInfo g_pstDigitalColorInfo[_NO_INPUT_PORT - 3]; // Subtract A0, D6, D7
StructDigitalColorInfoChanged g_pstDigitalColorInfoChanged[_NO_INPUT_PORT];
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_FREESYNC_SUPPORT == _ON)
bit ScalerSyncGetFREESYNCEnable(void);
void ScalerSyncSetFREESYNCSupport(bit bEnable);

#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
BYTE ScalerSyncGetHDMIFREESYNCVcp_EXINT1(void);
void ScalerSyncSetHDMIFREESYNCVcp_EXINT1(BYTE ucVcpCode);
#endif

void ScalerSyncFREESYNCTestPinEnable(void);
#endif

#if(_ULTRA_HDR_SUPPORT == _ON)
bit ScalerSyncHDRGetCurrentStatus(StructHDRStaticMetaData *pstHDRSaticMetadata, EnumSourceSearchPort enumSourceSearchPort);

#if(_DP_SUPPORT == _ON)
void ScalerSyncDPHDRInfoFrameRSV0Check(EnumSourceSearchPort enumSourceSearchPort);
void ScalerSyncDPHDRInfoFramePacketDetect(EnumSourceSearchPort enumSourceSearchPort);
#endif
#endif

#if(_DP_SUPPORT == _ON)
void ScalerSyncDpScanInitial(BYTE ucInputPort);
void ScalerSyncDpSecDataReset(BYTE ucInputPort);
bit ScalerSyncDpNormalPreDetect(BYTE ucInputPort);
BYTE ScalerSyncDpScanInputPort(BYTE ucInputPort);
bit ScalerSyncDpPSPreDetect(BYTE ucInputPort);
bit ScalerSyncDpStableDetect(BYTE ucInputPort);
void ScalerSyncDpLowPowerProc(void);
void ScalerSyncDpCapabilitySwitchProc(void);
void ScalerSyncJudgeHPDToggle(EnumPowerAction enumPowerAction);

#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D1_INPUT_PORT_TYPE == _D1_DP_PORT))
void ScalerSyncDpDualPortHotPlugEvent(EnumDpHotPlugAssertType enumHpdType);
void ScalerSyncDpDualPortHotPlugDuration(WORD usMs);
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
void ScalerSyncDpFREESYNCSupportSwitch(EnumDpFREESYNCCapabilitySwitch enumDpFREESYNCCapSwitch, bit bEn);
#endif

#if((_DP_TX_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))
bit ScalerSyncDpFakePowerSavingCheck(void);
#endif

#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
bit ScalerSyncDualDpDoubleCheck(EnumSourceSearchPort enumSourceSearchPort);
#endif
#endif

#if(_DP_TX_SUPPORT == _ON)
void ScalerSyncDpTxPowerProc(EnumPowerAction enumPowerAction);
void ScalerSyncDpTxHdcpUpstreamSwitchProc(EnumDisplayMode enumDisplayMode, BYTE ucInputPort);
EnumDPRxHDCPUpstreamAuthStatus ScalerSyncDpHdcpGetUpstreamEvent(void);
bit ScalerSyncDpHdcpGetUpstreamEncryptStatus(void);
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
#if(_DP_TX_SUPPORT == _ON)
void ScalerSyncHdcpEnableDownLoadDPTxKey(bit bEnable);
void ScalerSyncHdcpDownLoadDPTxAKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
void ScalerSyncHdcpDownLoadDPTxAKey(WORD usLength, BYTE *pucReadArray);
#endif

bit ScalerSyncHdcpCheckEnabled(BYTE ucInputPort);
#endif

#if(_URGENT_EVENT_CHECK_MODE == _ON)
bit ScalerSyncCheckUrgentEvent(void);
bit ScalerSyncGetUrgentEventFlg(void);
void ScalerSyncClrUrgentEventFlg(void);
#endif

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
BYTE ScalerSyncDdcDetect_EXINT1(void);
#if(_HDMI_SUPPORT == _ON)
void ScalerSyncTMDSEdidSwitch(BYTE ucPortSelect);
void ScalerSyncHDMIDdcCheckBusy(BYTE ucInputPort);
#endif
void ScalerSyncTMDSHPDToggleProc(void);

#if(_DUAL_DVI_SUPPORT == _ON)
bit ScalerSyncGetDualDVIMode(EnumSourceSearchPort enumInputPort);
bit ScalerSyncDualDVIDoubleCheck(EnumSourceSearchPort enumSourceSearchPort, WORD usHwidth, WORD usVHeight);
void ScalerSyncDualDVIClockInvert(EnumSourceSearchPort enumSourceSearchPort);
#endif

#endif

#if(_MHL_SUPPORT == _ON)
bit ScalerSyncMHLVBusPowerExist(void);
#endif

void ScalerSyncActiveProc(BYTE ucSourceType);
void ScalerSyncResetProc(BYTE ucInputPort);
void ScalerSyncResetAllProc(void);
void ScalerSyncPowerProc(EnumPowerAction enumPowerAction);
void ScalerSyncAdcApllPowerDown(void);
void ScalerSyncSetDdcForceNack(BYTE ucInputPort, bit bSelect);
bit ScalerSyncGetDdcForceNackStatus(BYTE ucInputPort);

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
void ScalerSyncInterfaceRx0Proc(bit bEnable);
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
void ScalerSyncInterfaceRx1Proc(bit bEnable);
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
void ScalerSyncInterfaceRx2Proc(bit bEnable);
#endif

#if((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
void ScalerSyncInterfaceRx3Proc(bit bEnable);
#endif

#if((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
void ScalerSyncInterfaceRx4Proc(bit bEnable);
#endif

#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
void ScalerSyncInterfaceRx5Proc(bit bEnable);
#endif

#if(_D0_HDMI_EXIST == _ON)
void ScalerSyncTMDSRx0HdmiVideoSetting(void);
void ScalerSyncTMDSRx0HdmiColorimetrySetting(void);
void ScalerSyncTMDSRx0HdmiColorimetryExtSetting(void);
#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) || (_YCC_QUANTIZATION_RANGE_SUPPORT == _ON))
void ScalerSyncTMDSRx0HdmiQuantizationSetting(void);
#endif

bit ScalerSyncTMDSRx0HdmiColorInfoChanged(void);
#endif

#if(_D1_HDMI_EXIST == _ON)
void ScalerSyncTMDSRx1HdmiVideoSetting(void);
void ScalerSyncTMDSRx1HdmiColorimetrySetting(void);
void ScalerSyncTMDSRx1HdmiColorimetryExtSetting(void);
#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) || (_YCC_QUANTIZATION_RANGE_SUPPORT == _ON))
void ScalerSyncTMDSRx1HdmiQuantizationSetting(void);
#endif
bit ScalerSyncTMDSRx1HdmiColorInfoChanged(void);
#endif

#if(_D2_HDMI_EXIST == _ON)
#if(_D2_INPUT_PORT_TYPE != _D2_DUAL_DVI_PORT)
void ScalerSyncTMDSRx2HdmiVideoSetting(void);
#endif

void ScalerSyncTMDSRx2HdmiColorimetrySetting(void);
void ScalerSyncTMDSRx2HdmiColorimetryExtSetting(void);
#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) || (_YCC_QUANTIZATION_RANGE_SUPPORT == _ON))
void ScalerSyncTMDSRx2HdmiQuantizationSetting(void);
#endif
bit ScalerSyncTMDSRx2HdmiColorInfoChanged(void);
#endif

#if(_D3_HDMI_EXIST == _ON)
#if(_D3_INPUT_PORT_TYPE != _D3_DUAL_DVI_PORT)
void ScalerSyncTMDSRx3HdmiVideoSetting(void);
#endif

void ScalerSyncTMDSRx3HdmiColorimetrySetting(void);
void ScalerSyncTMDSRx3HdmiColorimetryExtSetting(void);
#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) || (_YCC_QUANTIZATION_RANGE_SUPPORT == _ON))
void ScalerSyncTMDSRx3HdmiQuantizationSetting(void);
#endif
bit ScalerSyncTMDSRx3HdmiColorInfoChanged(void);
#endif

#if(_D4_HDMI_EXIST == _ON)
#if(_D4_INPUT_PORT_TYPE != _D4_DUAL_DVI_PORT)
void ScalerSyncTMDSRx4HdmiVideoSetting(void);
#endif

void ScalerSyncTMDSRx4HdmiColorimetrySetting(void);
void ScalerSyncTMDSRx4HdmiColorimetryExtSetting(void);
#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) || (_YCC_QUANTIZATION_RANGE_SUPPORT == _ON))
void ScalerSyncTMDSRx4HdmiQuantizationSetting(void);
#endif
bit ScalerSyncTMDSRx4HdmiColorInfoChanged(void);
#endif

#if(_D5_HDMI_EXIST == _ON)
void ScalerSyncTMDSRx5HdmiVideoSetting(void);
void ScalerSyncTMDSRx5HdmiColorimetrySetting(void);
void ScalerSyncTMDSRx5HdmiColorimetryExtSetting(void);
#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) || (_YCC_QUANTIZATION_RANGE_SUPPORT == _ON))
void ScalerSyncTMDSRx5HdmiQuantizationSetting(void);
#endif
bit ScalerSyncTMDSRx5HdmiColorInfoChanged(void);
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
bit ScalerSyncDigitalGetColorimetryChanged(EnumSourceSearchPort enumSourceSearchPort);
bit ScalerSyncDigitalGetColorimetryExtChanged(EnumSourceSearchPort enumSourceSearchPort);
bit ScalerSyncDigitalGetQuantizationChanged(EnumSourceSearchPort enumSourceSearchPort);
void ScalerSyncDigitalClrColorimetryChanged(EnumSourceSearchPort enumSourceSearchPort);
void ScalerSyncDigitalClrColorimetryExtChanged(EnumSourceSearchPort enumSourceSearchPort);
void ScalerSyncDigitalClrQuantizationChanged(EnumSourceSearchPort enumSourceSearchPort);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

#if(_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Dp FREESYNC Mode Enabled
// Input Value  : None
// Output Value : True  --> Enabled
//                False --> Disabled
//--------------------------------------------------
bit ScalerSyncGetFREESYNCEnable(void)
{
    return GET_FREESYNC_ENABLED();
}

//--------------------------------------------------
// Description  : Set FREESYNC Support
// Input Value  : Enable --> Support
// Output Value : None
//--------------------------------------------------
void ScalerSyncSetFREESYNCSupport(bit bEnable)
{
    SET_FREESYNC_SUPPORT(bEnable);
}

#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
//--------------------------------------------------
// Description  : Get HDMI FREESYNC VCP
// Input Value  : None
// Output Value : HDMI FREESYNC VCP
//                False --> Disabled
//--------------------------------------------------
BYTE ScalerSyncGetHDMIFREESYNCVcp_EXINT1(void) using 2
{
    return GET_HDMI_FREESYNC_VCP();
}

//--------------------------------------------------
// Description  : Set HDMI FREESYNC VCP
// Input Value  : HDMI FREESYNC VCP
// Output Value : None
//--------------------------------------------------
void ScalerSyncSetHDMIFREESYNCVcp_EXINT1(BYTE ucVcpCode) using 2
{
    g_ucHDMIFREESYNCVCPReceive = ucVcpCode;
}
#endif

//--------------------------------------------------
// Description  : Enable Freesync Test Pin
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncFREESYNCTestPinEnable(void)
{
    // Set DVS test pin (TestOut0) and DHS test pin (TestOut1)
    ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_48_D_DOMAIN_TESTOUT, 0x0A);
    ScalerSetDataPortByte(P0_8D_TEST_MODE_PORT_ADDR, _P0_8E_PT_00_TEST_MODE, 0x8A);
    ScalerSetDataPortByte(P0_8D_TEST_MODE_PORT_ADDR, _P0_8E_PT_01_TEST_MODE_CTRL, 0x01);
    ScalerSetDataPortByte(P0_8D_TEST_MODE_PORT_ADDR, _P0_8E_PT_20_TESTOUT_SEL0, 0x67);
    ScalerSetDataPortByte(P0_8D_TEST_MODE_PORT_ADDR, _P0_8E_PT_21_TESTOUT_SEL1, 0x66);
}
#endif

#if(_ULTRA_HDR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Current HDR data
// Input Value  : stHDRSaticMetadata --> HDR data
//                enumSourceSearchPort --> Input port
// Output Value : _FALSE: no receive
//--------------------------------------------------
bit ScalerSyncHDRGetCurrentStatus(StructHDRStaticMetaData *pstHDRSaticMetadata, EnumSourceSearchPort enumSourceSearchPort)
{
    bit bHDRInfoReceive = 0;
    BYTE pucHDRInfoData[_HW_DP_INFOFRAME_RSV0_LENGTH];

    memset(pucHDRInfoData, 0, _HW_DP_INFOFRAME_RSV0_LENGTH);

    switch(enumSourceSearchPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif
            bHDRInfoReceive = GET_DP_RX0_HDR_INFO_FRAME_RECEIVED();
            memcpy(pucHDRInfoData, g_pucDPRx0HDRBackup, _HW_DP_INFOFRAME_RSV0_LENGTH);

            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

        case _D1_INPUT_PORT:

            bHDRInfoReceive = GET_DP_RX1_HDR_INFO_FRAME_RECEIVED();
            memcpy(pucHDRInfoData, g_pucDPRx1HDRBackup, _HW_DP_INFOFRAME_RSV0_LENGTH);

            break;
#endif

#if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
        case _D2_INPUT_PORT:

            bHDRInfoReceive = GET_HDMI_RX2_HDR_INFO_FRAME_RECEIVED();

            ScalerTMDSRx2GetHDRData(pucHDRInfoData);

            break;
#endif

#if((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT))
        case _D3_INPUT_PORT:

            bHDRInfoReceive = GET_HDMI_RX3_HDR_INFO_FRAME_RECEIVED();

            ScalerTMDSRx3GetHDRData(pucHDRInfoData);

            break;
#endif

        default:
            break;
    }

    // Check HDR Version/ Length & InfoFrame receive bit
    if((pucHDRInfoData[0] == 0x01) && (pucHDRInfoData[1] == 0x1A) && (bHDRInfoReceive == _TRUE))
    {
        pstHDRSaticMetadata->ucEOTF = pucHDRInfoData[2];
        pstHDRSaticMetadata->ucStaticMetadataID = pucHDRInfoData[3];

        pstHDRSaticMetadata->usDisplayPrimariesX0 = ((WORD)(pucHDRInfoData[5] << 8) | (pucHDRInfoData[4]));
        pstHDRSaticMetadata->usDisplayPrimariesY0 = ((WORD)(pucHDRInfoData[7] << 8) | (pucHDRInfoData[6]));

        pstHDRSaticMetadata->usDisplayPrimariesX1 = ((WORD)(pucHDRInfoData[9] << 8) | (pucHDRInfoData[8]));
        pstHDRSaticMetadata->usDisplayPrimariesY1 = ((WORD)(pucHDRInfoData[11] << 8) | (pucHDRInfoData[10]));

        pstHDRSaticMetadata->usDisplayPrimariesX2 = ((WORD)(pucHDRInfoData[13] << 8) | (pucHDRInfoData[12]));
        pstHDRSaticMetadata->usDisplayPrimariesY2 = ((WORD)(pucHDRInfoData[15] << 8) | (pucHDRInfoData[14]));

        pstHDRSaticMetadata->usWhitePointX = ((WORD)(pucHDRInfoData[17] << 8) | (pucHDRInfoData[16]));
        pstHDRSaticMetadata->usWhitePointY = ((WORD)(pucHDRInfoData[19] << 8) | (pucHDRInfoData[18]));

        pstHDRSaticMetadata->usMaxDisplayMasteringLv = ((WORD)(pucHDRInfoData[21] << 8) | (pucHDRInfoData[20]));
        pstHDRSaticMetadata->usMinDisplayMasteringLv = ((WORD)(pucHDRInfoData[23] << 8) | (pucHDRInfoData[22]));

        pstHDRSaticMetadata->usMaxCLL = ((WORD)(pucHDRInfoData[25] << 8) | (pucHDRInfoData[24]));
        pstHDRSaticMetadata->usMaxFALL = ((WORD)(pucHDRInfoData[27] << 8) | (pucHDRInfoData[26]));

        return _TRUE;
    }
    else
    {
        pstHDRSaticMetadata->ucEOTF = 0x00;
        pstHDRSaticMetadata->ucStaticMetadataID = 0x00;

        pstHDRSaticMetadata->usDisplayPrimariesX0 = 0x0000;
        pstHDRSaticMetadata->usDisplayPrimariesY0 = 0x0000;

        pstHDRSaticMetadata->usDisplayPrimariesX1 = 0x0000;
        pstHDRSaticMetadata->usDisplayPrimariesY1 = 0x0000;

        pstHDRSaticMetadata->usDisplayPrimariesX2 = 0x0000;
        pstHDRSaticMetadata->usDisplayPrimariesY2 = 0x0000;

        pstHDRSaticMetadata->usWhitePointX = 0x0000;
        pstHDRSaticMetadata->usWhitePointY = 0x0000;

        pstHDRSaticMetadata->usMaxDisplayMasteringLv = 0x0000;
        pstHDRSaticMetadata->usMinDisplayMasteringLv = 0x0000;

        pstHDRSaticMetadata->usMaxCLL = 0x0000;
        pstHDRSaticMetadata->usMaxFALL = 0x0000;

        return _FALSE;
    }
}

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDR Infoframe RSV0 Check
// Input Value  : Input source port
// Output Value : None
//--------------------------------------------------
void ScalerSyncDPHDRInfoFrameRSV0Check(EnumSourceSearchPort enumSourceSearchPort)
{
    switch(enumSourceSearchPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif
            ScalerDpRx0InfoFrameRSV0Check();

            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

        case _D1_INPUT_PORT:

            ScalerDpRx1InfoFrameRSV0Check();

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : HDR Infoframe packet detect
// Input Value  : Input source port
// Output Value : None
//--------------------------------------------------
void ScalerSyncDPHDRInfoFramePacketDetect(EnumSourceSearchPort enumSourceSearchPort)
{
    switch(enumSourceSearchPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif

            if(GET_DP_RX0_RSV0_DETECTING() == _FALSE)
            {
                SET_DP_RX0_RSV0_DETECTING();
                ScalerDpRx0InfoFrameRSV0Check();

#if(_DP_FREESYNC_SUPPORT == _ON)
                // Activate Packet Detection Event
                ScalerTimerActiveTimerEvent(SEC(0.13), _SCALER_TIMER_EVENT_DP_RX0_RSV0_PACKET_DETECT);
#else
                // Activate Packet Detection Event
                ScalerTimerActiveTimerEvent(((WORD)2 * 10000 / GET_INPUT_TIMING_VFREQ()), _SCALER_TIMER_EVENT_DP_RX0_RSV0_PACKET_DETECT);
#endif
            }

            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

        case _D1_INPUT_PORT:

            if(GET_DP_RX1_RSV0_DETECTING() == _FALSE)
            {
                SET_DP_RX1_RSV0_DETECTING();
                ScalerDpRx1InfoFrameRSV0Check();

#if(_DP_FREESYNC_SUPPORT == _ON)
                // Activate Packet Detection Event
                ScalerTimerActiveTimerEvent(SEC(0.13), _SCALER_TIMER_EVENT_DP_RX1_RSV0_PACKET_DETECT);
#else
                // Activate Packet Detection Event
                ScalerTimerActiveTimerEvent(((WORD)2 * 10000 / GET_INPUT_TIMING_VFREQ()), _SCALER_TIMER_EVENT_DP_RX1_RSV0_PACKET_DETECT);
#endif
            }

            break;
#endif

        default:

            break;
    }
}
#endif
#endif

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Initial Setting for DP Scanning Port(Power Normal)
// Input Value  : _D0_INPUT_PORT or _D1_INPUT_PORT
// Output Value : None
//--------------------------------------------------
void ScalerSyncDpScanInitial(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif
            ScalerDpRx0MacInitial();

            ScalerDpRx0PhyInitial();

            CLR_DP_RX0_FAKE_LINK_TRAINING();

            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

        case _D1_INPUT_PORT:

            ScalerDpRx1MacInitial();

            ScalerDpRx1PhyInitial();

            CLR_DP_RX1_FAKE_LINK_TRAINING();

            break;
#endif

#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)

        case _D7_INPUT_PORT:

            ScalerDpRx0MacInitial();
            ScalerDpRx0PhyInitial();
            CLR_DP_RX0_FAKE_LINK_TRAINING();

            ScalerDpRx1MacInitial();
            ScalerDpRx1PhyInitial();
            CLR_DP_RX1_FAKE_LINK_TRAINING();

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DP Sec Data Reset
// Input Value  : ucInputPort
// Output Value : None
//--------------------------------------------------
void ScalerSyncDpSecDataReset(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif
            ScalerDpRx0SecDataBlockReset();

            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

        case _D1_INPUT_PORT:

            ScalerDpRx1SecDataBlockReset();

            break;
#endif

#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)

        case _D7_INPUT_PORT:

            ScalerDpRx0SecDataBlockReset();
            ScalerDpRx1SecDataBlockReset();

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Signal PreDetection for DP(Power Normal)
// Input Value  : _D0_INPUT_PORT or _D1_INPUT_PORT
// Output Value : True : DP Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerSyncDpNormalPreDetect(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif
            return ScalerDpRx0NormalPreDetect();
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

        case _D1_INPUT_PORT:

            return ScalerDpRx1NormalPreDetect();
#endif

#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)

        case _D7_INPUT_PORT:

            if(ScalerDpRx0NormalPreDetect() == _TRUE)
            {
                if(ScalerDpRx1NormalPreDetect() == _TRUE)
                {
                    SET_D7_SWITCH_SELECT(_D7_INPUT_PORT);
                }
                else
                {
                    SET_D7_SWITCH_SELECT(_D0_INPUT_PORT);
                }

                return _TRUE;
            }
            else if(ScalerDpRx1NormalPreDetect() == _TRUE)
            {
                SET_D7_SWITCH_SELECT(_D1_INPUT_PORT);
                return _TRUE;
            }
            break;
#endif

        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Port Source/Sync Scanning and Setting
// Input Value  : _D0_INPUT_PORT or _D1_INPUT_PORT
// Output Value : Source DP --> DP Sync Stable
//                Source None --> No Stable Sync
//--------------------------------------------------
BYTE ScalerSyncDpScanInputPort(BYTE ucInputPort)
{
    switch((ucInputPort))
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif
            return ScalerDpRx0ScanInputPort();
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:

            return ScalerDpRx1ScanInputPort();
#endif

#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
        case _D7_INPUT_PORT:

            switch(GET_D7_SWITCH_SELECT())
            {
                case _D0_INPUT_PORT:

                    if(ScalerDpRx0ScanInputPort() != _SOURCE_DP)
                    {
                        return _SOURCE_NONE;
                    }
                    break;

                case _D1_INPUT_PORT:

                    if(ScalerDpRx1ScanInputPort() != _SOURCE_DP)
                    {
                        return _SOURCE_NONE;
                    }
                    break;

                default:
                case _D7_INPUT_PORT:

                    if((ScalerDpRx0ScanInputPort() != _SOURCE_DP) ||
                       (ScalerDpRx1ScanInputPort() != _SOURCE_DP))
                    {
                        return _SOURCE_NONE;
                    }
                    break;
            }

            // Check dual DP resolution
            if(ScalerSyncDualDpDoubleCheck(GET_D7_SWITCH_SELECT()) == _TRUE)
            {
                return _SOURCE_DP;
            }
            else
            {
                return _SOURCE_NONE;
            }
#endif

        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Signal Detection for DP(Power Saving)
// Input Value  : _D0_INPUT_PORT or _D1_INPUT_PORT
// Output Value : True : DP Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerSyncDpPSPreDetect(BYTE ucInputPort)
{
    switch((ucInputPort))
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif
            return ScalerDpRx0PSPreDetect();
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:

            return ScalerDpRx1PSPreDetect();
#endif

#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
        case _D7_INPUT_PORT:

            if(ScalerDpRx0PSPreDetect() == _TRUE)
            {
                if(ScalerDpRx1PSPreDetect() == _TRUE)
                {
                    SET_D7_SWITCH_SELECT(_D7_INPUT_PORT);
                }
                else
                {
                    SET_D7_SWITCH_SELECT(_D0_INPUT_PORT);
                }

                return _TRUE;
            }
            else if(ScalerDpRx1PSPreDetect() == _TRUE)
            {
                SET_D7_SWITCH_SELECT(_D1_INPUT_PORT);
                return _TRUE;
            }
            break;
#endif

        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : On Line Check DP stability
// Input Value  : _D0_INPUT_PORT or _D1_INPUT_PORT
// Output Value : True --> DP Stable
//                False --> DP Unstable
//--------------------------------------------------
bit ScalerSyncDpStableDetect(BYTE ucInputPort)
{
    switch((ucInputPort))
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif
            return ScalerDpRx0StableDetect();
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:

            return ScalerDpRx1StableDetect();
#endif

#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
        case _D7_INPUT_PORT:

            if(GET_D7_SWITCH_SELECT() == _D0_INPUT_PORT)
            {
                return ScalerDpRx0StableDetect();
            }
            else if(GET_D7_SWITCH_SELECT() == _D1_INPUT_PORT)
            {
                return ScalerDpRx1StableDetect();
            }
            else
            {
                return ((ScalerDpRx0StableDetect() == _TRUE) &&
                        (ScalerDpRx1StableDetect() == _TRUE));
            }
#endif

        default:

            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Low Power Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncDpLowPowerProc(void)
{
#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D1_INPUT_PORT_TYPE == _D1_DP_PORT))

    // Turn Off Output Clock
    ScalerSetBit(PB5_B8_MN_SCLKG_SDM_CTRL, ~_BIT6, 0x00);

    // Turn Off SCLK PLL
    ScalerSetBit(PB5_BD_MN_SCLKG_PLL_PWR, ~_BIT7, _BIT7);

    // Turn Off Output Clock
    ScalerSetBit(PB8_B8_MN_SCLKG_SDM_CTRL, ~_BIT6, 0x00);

    // Turn Off SCLK PLL
    ScalerSetBit(PB8_BD_MN_SCLKG_PLL_PWR, ~_BIT7, _BIT7);

    // Set end to idle trigger Aux Int, Clear Aux INT Flag
    ScalerSetBit(PB7_7A_AUX_DIG_PHYA, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));

    // Clear Manchester/Stop pattern/Sync_end pattern/Byte boundary check Error
    ScalerSetBit(PB7_79_AUX_DIG_PHY9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Set end to idle trigger Aux Int, Clear Aux INT Flag
    ScalerSetBit(PBA_7A_AUX_DIG_PHYA, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));

    // Clear Manchester/Stop pattern/Sync_end pattern/Byte boundary check Error
    ScalerSetBit(PBA_79_AUX_DIG_PHY9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    ScalerTimerDelayXms(2);

    if((ScalerGetBit(PB7_7A_AUX_DIG_PHYA, _BIT0) == 0x00) && (ScalerGetBit(PBA_7A_AUX_DIG_PHYA, _BIT0) == 0x00))
    {
        // Aux PHY Power Saving Mode
        ScalerSetBit(PB7_62_AUX_2, ~_BIT1, _BIT1);

        // Aux Bias Current From POR
        ScalerSetBit(PB7_63_AUX_3, ~_BIT7, _BIT7);

        // Aux comm current select min
        ScalerSetBit(PB7_64_AUX_4, ~(_BIT7 | _BIT6), 0x00);

        // Aux PHY Power Saving Mode
        ScalerSetBit(PBA_62_AUX_2, ~_BIT1, _BIT1);

        // Aux Bias Current From POR
        ScalerSetBit(PBA_63_AUX_3, ~_BIT7, _BIT7);

        // Aux comm current select min
        ScalerSetBit(PBA_64_AUX_4, ~(_BIT7 | _BIT6), 0x00);

        // Disable GDI Bandgap
        ScalerGDIPhyBandgap(_OFF);

        IP = 0x81;

        CLR_DP_RX0_PS_AUX_TOGGLE();

        CLR_DP_RX1_PS_AUX_TOGGLE();

        // Enable Aux INT
        ScalerSetBit(PB7_7A_AUX_DIG_PHYA, ~(_BIT4 | _BIT0), (_BIT4));

        // Enable Aux INT
        ScalerSetBit(PBA_7A_AUX_DIG_PHYA, ~(_BIT4 | _BIT0), (_BIT4));

        DebugMessageDigital("7. Low Power Event", 0);
    }
    else
    {
        SET_DP_RX0_PS_AUX_TOGGLE();

        SET_DP_RX1_PS_AUX_TOGGLE();
    }

#elif(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

    // Turn Off Output Clock
    ScalerSetBit(PB5_B8_MN_SCLKG_SDM_CTRL, ~_BIT6, 0x00);

    // Turn Off SCLK PLL
    ScalerSetBit(PB5_BD_MN_SCLKG_PLL_PWR, ~_BIT7, _BIT7);

    // Set end to idle trigger Aux Int, Clear Aux INT Flag
    ScalerSetBit(PB7_7A_AUX_DIG_PHYA, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));

    // Clear Manchester/Stop pattern/Sync_end pattern/Byte boundary check Error
    ScalerSetBit(PB7_79_AUX_DIG_PHY9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    ScalerTimerDelayXms(2);

    if(ScalerGetBit(PB7_7A_AUX_DIG_PHYA, _BIT0) == 0x00)
    {
        // Aux PHY Power Saving Mode
        ScalerSetBit(PB7_62_AUX_2, ~_BIT1, _BIT1);

        // Aux Bias Current From POR
        ScalerSetBit(PB7_63_AUX_3, ~_BIT7, _BIT7);

        // Aux comm current select min
        ScalerSetBit(PB7_64_AUX_4, ~(_BIT7 | _BIT6), 0x00);

        // Disable GDI Bandgap
        ScalerGDIPhyBandgap(_OFF);

        IP = 0x81;

        CLR_DP_RX0_PS_AUX_TOGGLE();

        // Enable Aux INT
        ScalerSetBit(PB7_7A_AUX_DIG_PHYA, ~(_BIT4 | _BIT0), (_BIT4));

        DebugMessageDigital("7. Low Power Event", 0);
    }
    else
    {
        SET_DP_RX0_PS_AUX_TOGGLE();
    }

#elif(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

    // Turn Off Output Clock
    ScalerSetBit(PB8_B8_MN_SCLKG_SDM_CTRL, ~_BIT6, 0x00);

    // Turn Off SCLK PLL
    ScalerSetBit(PB8_BD_MN_SCLKG_PLL_PWR, ~_BIT7, _BIT7);

    // Set end to idle trigger Aux Int, Clear Aux INT Flag
    ScalerSetBit(PBA_7A_AUX_DIG_PHYA, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));

    // Clear Manchester/Stop pattern/Sync_end pattern/Byte boundary check Error
    ScalerSetBit(PBA_79_AUX_DIG_PHY9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    ScalerTimerDelayXms(2);

    if(ScalerGetBit(PBA_7A_AUX_DIG_PHYA, _BIT0) == 0x00)
    {
        // Aux PHY Power Saving Mode
        ScalerSetBit(PBA_62_AUX_2, ~_BIT1, _BIT1);

        // Aux Bias Current From POR
        ScalerSetBit(PBA_63_AUX_3, ~_BIT7, _BIT7);

        // Aux comm current select min
        ScalerSetBit(PBA_64_AUX_4, ~(_BIT7 | _BIT6), 0x00);

        // Disable GDI Bandgap
        ScalerGDIPhyBandgap(_OFF);

        IP = 0x81;

        CLR_DP_RX1_PS_AUX_TOGGLE();

        // Enable Aux INT
        ScalerSetBit(PBA_7A_AUX_DIG_PHYA, ~(_BIT4 | _BIT0), (_BIT4));

        DebugMessageDigital("7. Low Power Event", 0);
    }
    else
    {
        SET_DP_RX1_PS_AUX_TOGGLE();
    }
#endif
}

//--------------------------------------------------
// Description  : Dp Capability Switch
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncDpCapabilitySwitchProc(void)
{
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    bit bDPRx0DoLongHotPlug = _FALSE;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    bit bDPRx1DoLongHotPlug = _FALSE;
#endif

    if(GET_DP_RX_CAPABILITY_SWITCHED() == _TRUE)
    {
        DebugMessageMst("MST Cap Switch", GET_DP_RX_TARGET_MST_PORT());

        // D0 Port Version Switch
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

#if(_DP_FREESYNC_SUPPORT == _ON)

        if(GET_DP_RX0_FREESYNC_CAPABILITY_SWITCH() == _TRUE)
        {
            CLR_DP_RX0_FREESYNC_CAPABILITY_SWITCH();
            bDPRx0DoLongHotPlug = _TRUE;
        }
#endif

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

        if(GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT)
#endif
        {
            if(ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x02, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != GET_DP_RX_D0_PORT_TARGET_LANE_COUNT())
            {
                ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x02, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_RX_D0_PORT_TARGET_LANE_COUNT());

                bDPRx0DoLongHotPlug = _TRUE;
            }

            if(GET_DP_RX_D0_EDID_SWITCH() == _TRUE)
            {
                CLR_DP_RX_D0_EDID_SWITCH();

#if(_DP_MST_SUPPORT == _ON)
                if(g_enumDpMSTCapablePort == _DP_MST_RX0_PORT)
                {
                    ScalerDpMstReset(_DP_MST_RX0_PORT);
                }
#endif

                bDPRx0DoLongHotPlug = _TRUE;
            }

            CLR_DP_RX_D6_EDID_SWITCH();

            // Set DP 1.2 @ DP MST Port
            if((GET_DP_RX_TARGET_MST_PORT() == _DP_MST_RX0_PORT) && (GET_DP_RX_D0_PORT_TARGET_VERSION() == _DP_VERSION_1_1))
            {
                SET_DP_RX_D0_PORT_TARGET_VERSION(_DP_VERSION_1_2);
            }

            if(ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x00) != GET_DP_RX_D0_PORT_TARGET_VERSION())
            {
#if(_DP_MST_SUPPORT == _ON)
                if((GET_REG_DP_RX_DOWN_REQUEST_ADDR_WRITTEN() == _TRUE) ||
#if(_DP_TX_SUPPORT == _ON)
                   (GET_DP_TOTAL_RECEIVED_MSG_COUNT() != 0) ||
#endif
                   (GET_DP_RX_REPLY_BUF_FREE() == _FALSE))
                {
                    return;
                }
#endif
                ScalerDpRx0ChangeDpcdVersion(GET_DP_RX_D0_PORT_TARGET_VERSION(), GET_DP_RX_TARGET_MST_PORT());

#if(_DP_MST_SUPPORT == _ON)

                // DP Version Switch to 1.1 ==> Reset/Clear MST Fake PS Related Events/Flags
                if(GET_DP_RX_D0_PORT_TARGET_VERSION() == _DP_VERSION_1_1)
                {
                    CLR_DP_RX0_CHECK_AUX_CH_NO_POWER_DEBOUNCE();
                    CLR_DP_RX0_CHECK_AUX_CH_POWER_OFF();

                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_AUX_CH_NO_POWER_CHECK_DEBOUNCE);
                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_AUX_CH_POWER_ON_WAIT_HOTPLUG_HIGH);
                }
#endif

                bDPRx0DoLongHotPlug = _TRUE;
            }
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
            else
            {
                ScalerDpRx0ChangeDpcdVersion(GET_DP_RX_D0_PORT_TARGET_VERSION(), GET_DP_RX_TARGET_MST_PORT());
            }
#endif
        }
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

        else if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
        {
            if(ScalerDpRx0GetDpcdBitInfo(0x00, 0x00, 0x02, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != GET_DP_RX_D6_PORT_TARGET_LANE_COUNT())
            {
                ScalerDpRx0SetDpcdBitValue(0x00, 0x00, 0x02, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_RX_D6_PORT_TARGET_LANE_COUNT());

                bDPRx0DoLongHotPlug = _TRUE;
            }

            if(GET_DP_RX_D6_EDID_SWITCH() == _TRUE)
            {
                CLR_DP_RX_D6_EDID_SWITCH();

#if(_DP_MST_SUPPORT == _ON)
                if(g_enumDpMSTCapablePort == _DP_MST_RX0_PORT)
                {
                    ScalerDpMstReset(_DP_MST_RX0_PORT);
                }
#endif

                bDPRx0DoLongHotPlug = _TRUE;
            }

            CLR_DP_RX_D0_EDID_SWITCH();

            // Set DP 1.2 @ DP MST Port
            if((GET_DP_RX_TARGET_MST_PORT() == _DP_MST_RX6_PORT) && (GET_DP_RX_D6_PORT_TARGET_VERSION() == _DP_VERSION_1_1))
            {
                SET_DP_RX_D6_PORT_TARGET_VERSION(_DP_VERSION_1_2);
            }

            if(ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x00) != GET_DP_RX_D6_PORT_TARGET_VERSION())
            {
#if(_DP_MST_SUPPORT == _ON)
                if((GET_REG_DP_RX_DOWN_REQUEST_ADDR_WRITTEN() == _TRUE) ||
#if(_DP_TX_SUPPORT == _ON)
                   (GET_DP_TOTAL_RECEIVED_MSG_COUNT() != 0) ||
#endif
                   (GET_DP_RX_REPLY_BUF_FREE() == _FALSE))
                {
                    return;
                }
#endif
                ScalerDpRx0ChangeDpcdVersion(GET_DP_RX_D6_PORT_TARGET_VERSION(), GET_DP_RX_TARGET_MST_PORT());

#if(_DP_MST_SUPPORT == _ON)

                // DP Version Switch to 1.1 ==> Reset/Clear MST Fake PS Related Events/Flags
                if(GET_DP_RX_D6_PORT_TARGET_VERSION() == _DP_VERSION_1_1)
                {
                    CLR_DP_RX0_CHECK_AUX_CH_NO_POWER_DEBOUNCE();
                    CLR_DP_RX0_CHECK_AUX_CH_POWER_OFF();

                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_AUX_CH_NO_POWER_CHECK_DEBOUNCE);
                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_AUX_CH_POWER_ON_WAIT_HOTPLUG_HIGH);
                }
#endif

                bDPRx0DoLongHotPlug = _TRUE;
            }
            else
            {
                ScalerDpRx0ChangeDpcdVersion(GET_DP_RX_D6_PORT_TARGET_VERSION(), GET_DP_RX_TARGET_MST_PORT());
            }
        }
#endif

#endif // End of #if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)


        // D1 Port Version Switch
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

#if(_DP_FREESYNC_SUPPORT == _ON)

        if(GET_DP_RX1_FREESYNC_CAPABILITY_SWITCH() == _TRUE)
        {
            CLR_DP_RX1_FREESYNC_CAPABILITY_SWITCH();
            bDPRx1DoLongHotPlug = _TRUE;
        }
#endif
        if(ScalerDpRx1GetDpcdBitInfo(0x00, 0x00, 0x02, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) != GET_DP_RX_D1_PORT_TARGET_LANE_COUNT())
        {
            ScalerDpRx1SetDpcdBitValue(0x00, 0x00, 0x02, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), GET_DP_RX_D1_PORT_TARGET_LANE_COUNT());

            bDPRx1DoLongHotPlug = _TRUE;
        }

        if(GET_DP_RX_D1_EDID_SWITCH() == _TRUE)
        {
            CLR_DP_RX_D1_EDID_SWITCH();

#if(_DP_MST_SUPPORT == _ON)
            if(g_enumDpMSTCapablePort == _DP_MST_RX1_PORT)
            {
                ScalerDpMstReset(_DP_MST_RX1_PORT);
            }
#endif

            bDPRx1DoLongHotPlug = _TRUE;
        }

        // Set DP 1.2 @ DP MST Port
        if((GET_DP_RX_TARGET_MST_PORT() == _DP_MST_RX1_PORT) && (GET_DP_RX_D1_PORT_TARGET_VERSION() == _DP_VERSION_1_1))
        {
            SET_DP_RX_D1_PORT_TARGET_VERSION(_DP_VERSION_1_2);
        }

        if(ScalerDpRx1GetDpcdInfo(0x00, 0x00, 0x00) != GET_DP_RX_D1_PORT_TARGET_VERSION())
        {
#if(_DP_MST_SUPPORT == _ON)
            if((GET_REG_DP_RX_DOWN_REQUEST_ADDR_WRITTEN() == _TRUE) ||
#if(_DP_TX_SUPPORT == _ON)
               (GET_DP_TOTAL_RECEIVED_MSG_COUNT() != 0) ||
#endif
               (GET_DP_RX_REPLY_BUF_FREE() == _FALSE))
            {
                return;
            }
#endif
            ScalerDpRx1ChangeDpcdVersion(GET_DP_RX_D1_PORT_TARGET_VERSION(), GET_DP_RX_TARGET_MST_PORT());

#if(_DP_MST_SUPPORT == _ON)

            // DP Version Switch to 1.1 ==> Reset/Clear MST Fake PS Related Events/Flags
            if(GET_DP_RX_D1_PORT_TARGET_VERSION() == _DP_VERSION_1_1)
            {
                CLR_DP_RX1_CHECK_AUX_CH_NO_POWER_DEBOUNCE();
                CLR_DP_RX1_CHECK_AUX_CH_POWER_OFF();

                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_AUX_CH_NO_POWER_CHECK_DEBOUNCE);
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_AUX_CH_POWER_ON_WAIT_HOTPLUG_HIGH);
            }
#endif

            bDPRx1DoLongHotPlug = _TRUE;
        }
#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)

        if(GET_DP_RX_D7_EDID_SWITCH() == _TRUE)
        {
            CLR_DP_RX_D7_EDID_SWITCH();

            bDPRx0DoLongHotPlug = _TRUE;
            bDPRx1DoLongHotPlug = _TRUE;
        }

#endif // End of #if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)

        // Mst Port Switch
#if(_DP_MST_SUPPORT == _ON)

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        // Target MST Port != Current Capable Port or External-Switching port case
        if(((GET_DP_RX_TARGET_MST_PORT() == _DP_MST_NO_PORT) && (g_enumDpMSTCapablePort != _DP_MST_NO_PORT)) ||
           ((GET_DP_RX_TARGET_MST_PORT() == _DP_MST_RX0_PORT) && (g_enumDpMSTCapablePort == _DP_MST_NO_PORT)) ||
           ((GET_DP_RX_TARGET_MST_PORT() == _DP_MST_RX0_PORT) && ((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) && (g_bDpMSTD6Capable == _TRUE))) ||
           ((GET_DP_RX_TARGET_MST_PORT() == _DP_MST_RX6_PORT) && (g_enumDpMSTCapablePort == _DP_MST_NO_PORT)) ||
           ((GET_DP_RX_TARGET_MST_PORT() == _DP_MST_RX6_PORT) && ((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) && (g_bDpMSTD6Capable == _FALSE))))
#else
        if(GET_DP_RX_TARGET_MST_PORT() != g_enumDpMSTCapablePort)
#endif
        {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

            if(GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT)
#endif
            {
                // No Port or Rx1 or Rx6 => Rx0
                // RX0 => NO Port or RX1 or Rx6
                if(((g_enumDpMSTCapablePort != _DP_MST_RX0_PORT) && (GET_DP_RX_TARGET_MST_PORT() == _DP_MST_RX0_PORT)) ||
                   ((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) && (GET_DP_RX_TARGET_MST_PORT() != _DP_MST_RX0_PORT)))
                {
                    CLR_DP_RX0_CHECK_AUX_CH_NO_POWER_DEBOUNCE();
                    CLR_DP_RX0_CHECK_AUX_CH_POWER_OFF();

                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_AUX_CH_NO_POWER_CHECK_DEBOUNCE);
                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_AUX_CH_POWER_ON_WAIT_HOTPLUG_HIGH);

                    bDPRx0DoLongHotPlug = _TRUE;

                    DebugMessageMst("MST Switch Long Plug : 1", GET_DP_RX_TARGET_MST_PORT());
                }

                ScalerDpMstReset(_DP_MST_RX0_PORT);

                if(GET_DP_RX_TARGET_MST_PORT() == _DP_MST_RX0_PORT)
                {
                    ScalerDpRx0ChangeDpcdVersion(GET_DP_RX_D0_PORT_TARGET_VERSION(), _DP_MST_RX0_PORT);
                }
                else
                {
                    ScalerDpRx0ChangeDpcdVersion(GET_DP_RX_D0_PORT_TARGET_VERSION(), _DP_MST_NO_PORT);
                }
            }
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
            else if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
            {
                // No Port or Rx0 or Rx1 => Rx6
                // RX6 => NO Port or RX0 or Rx1
                if(((g_enumDpMSTCapablePort != _DP_MST_RX0_PORT) && (GET_DP_RX_TARGET_MST_PORT() == _DP_MST_RX6_PORT)) ||
                   ((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) && (GET_DP_RX_TARGET_MST_PORT() != _DP_MST_RX6_PORT)))
                {
                    CLR_DP_RX0_CHECK_AUX_CH_NO_POWER_DEBOUNCE();
                    CLR_DP_RX0_CHECK_AUX_CH_POWER_OFF();

                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_AUX_CH_NO_POWER_CHECK_DEBOUNCE);
                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_AUX_CH_POWER_ON_WAIT_HOTPLUG_HIGH);

                    bDPRx0DoLongHotPlug = _TRUE;

                    DebugMessageMst("MST Switch Long Plug : 2", GET_DP_RX_TARGET_MST_PORT());
                }

                ScalerDpMstReset(_DP_MST_RX0_PORT);

                if(GET_DP_RX_TARGET_MST_PORT() == _DP_MST_RX6_PORT)
                {
                    ScalerDpRx0ChangeDpcdVersion(GET_DP_RX_D6_PORT_TARGET_VERSION(), _DP_MST_RX6_PORT);
                }
                else
                {
                    ScalerDpRx0ChangeDpcdVersion(GET_DP_RX_D6_PORT_TARGET_VERSION(), _DP_MST_NO_PORT);
                }
            }
#endif

#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

            // No Port or Rx0 or Rx6 => Rx1
            // RX1 => NO Port or RX0 or Rx6
            if(((g_enumDpMSTCapablePort != _DP_MST_RX1_PORT) && (GET_DP_RX_TARGET_MST_PORT() == _DP_MST_RX1_PORT)) ||
               ((g_enumDpMSTCapablePort == _DP_MST_RX1_PORT) && (GET_DP_RX_TARGET_MST_PORT() != _DP_MST_RX1_PORT)))
            {
                CLR_DP_RX1_CHECK_AUX_CH_NO_POWER_DEBOUNCE();
                CLR_DP_RX1_CHECK_AUX_CH_POWER_OFF();

                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_AUX_CH_NO_POWER_CHECK_DEBOUNCE);
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_AUX_CH_POWER_ON_WAIT_HOTPLUG_HIGH);

                bDPRx1DoLongHotPlug = _TRUE;
            }

            ScalerDpMstReset(_DP_MST_RX1_PORT);

            if(GET_DP_RX_TARGET_MST_PORT() == _DP_MST_RX1_PORT)
            {
                ScalerDpRx1ChangeDpcdVersion(GET_DP_RX_D1_PORT_TARGET_VERSION(), _DP_MST_RX1_PORT);
            }
            else
            {
                ScalerDpRx1ChangeDpcdVersion(GET_DP_RX_D1_PORT_TARGET_VERSION(), _DP_MST_NO_PORT);
            }
#endif

#if(_DP_TX_SUPPORT == _ON)

            ScalerDpTxSetStreamSource(_DP_TX_SOURCE_NONE);

            if(GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG)
            {
                pData[0] = 0x00;

                ScalerDpTxAuxNativeWrite(0x00, 0x01, 0x11, 1, pData);

#if(_DP_FREESYNC_SUPPORT == _ON)
                // Clear freesync enable bit
                ScalerDpTxAuxNativeRead(0x00, 0x01, 0x07, 1, pData);

                if((pData[0] & _BIT7) == _BIT7)
                {
                    pData[0] &= ~_BIT7;
                    ScalerDpTxAuxNativeWrite(0x00, 0x01, 0x07, 1, pData);
                }
#endif
            }
#endif

            ScalerDpRxMstInitial(GET_DP_RX_TARGET_MST_PORT());
        }
#endif // End of #if(_DP_MST_SUPPORT == _ON)

        CLR_DP_RX_CAPABILITY_SWITCHED();
    }

#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D1_INPUT_PORT_TYPE == _D1_DP_PORT))

    if((bDPRx0DoLongHotPlug == _TRUE) && (bDPRx1DoLongHotPlug == _TRUE))
    {
        ScalerSyncDpDualPortHotPlugEvent(_DP_MST_LONG_HPD_EVENT);
        bDPRx0DoLongHotPlug = _FALSE;
        bDPRx1DoLongHotPlug = _FALSE;
    }

#endif

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

    if(bDPRx0DoLongHotPlug == _TRUE)
    {
        ScalerDpRx0HotPlugEvent(_DP_MST_LONG_HPD_EVENT);
        bDPRx0DoLongHotPlug = _FALSE;
    }

#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

    if(bDPRx1DoLongHotPlug == _TRUE)
    {
        ScalerDpRx1HotPlugEvent(_DP_MST_LONG_HPD_EVENT);
        bDPRx1DoLongHotPlug = _FALSE;
    }

#endif
}

//--------------------------------------------------
// Description  : Decision DP HPD Toggle Behavior
// Input Value  : Power Action State
// Output Value : None
//--------------------------------------------------
void ScalerSyncJudgeHPDToggle(EnumPowerAction enumPowerAction)
{
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

    // Add for DPCD 2002h Bug
    // 2002h Has Been Read and Cancel Rx Mst Msg Finish during PS/ PD
    if(((enumPowerAction == _POWER_ACTION_OFF_TO_NORMAL) || (enumPowerAction == _POWER_ACTION_PS_TO_NORMAL)) && (GET_DP_RX0_AUX_COMMAND_NO_REPLY() == _TRUE))
    {
        CLR_DP_RX0_AUX_COMMAND_NO_REPLY();

        ScalerDpRx0HotPlugEvent(_DP_MST_LONG_HPD_EVENT);
    }
    else if(enumPowerAction == _POWER_ACTION_OFF_TO_NORMAL)
    {
#if(_DP_MST_SUPPORT == _ON)

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        if((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) || (g_enumDpMSTCapablePort == _DP_MST_RX6_PORT))
#else
        if(g_enumDpMSTCapablePort == _DP_MST_RX0_PORT)
#endif
        {
            ScalerDpRx0HPDPowerOfftoNormalProc(_LOW_FOR_MST);
        }
        else
#endif
        {
            ScalerDpRx0HPDPowerOfftoNormalProc(GET_DP_DC_OFF_HPD_HIGH());
        }
    }

    CLR_DP_RX0_POWER_STATE_INTO_PS();
#endif // End of #if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)


#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

    // Add for DPCD 2002h Bug
    // 2002h Has Been Read and Cancel Rx Mst Msg Finish during PS/ PD
    if(((enumPowerAction == _POWER_ACTION_OFF_TO_NORMAL) || (enumPowerAction == _POWER_ACTION_PS_TO_NORMAL)) && (GET_DP_RX1_AUX_COMMAND_NO_REPLY() == _TRUE))
    {
        CLR_DP_RX1_AUX_COMMAND_NO_REPLY();

        ScalerDpRx1HotPlugEvent(_DP_MST_LONG_HPD_EVENT);
    }
    else if(enumPowerAction == _POWER_ACTION_OFF_TO_NORMAL)
    {
#if(_DP_MST_SUPPORT == _ON)

        if(g_enumDpMSTCapablePort == _DP_MST_RX1_PORT)
        {
            ScalerDpRx1HPDPowerOfftoNormalProc(_LOW_FOR_MST);
        }
        else
#endif
        {
            ScalerDpRx1HPDPowerOfftoNormalProc(GET_DP_DC_OFF_HPD_HIGH());
        }
    }

    CLR_DP_RX1_POWER_STATE_INTO_PS();
#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
}

#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D1_INPUT_PORT_TYPE == _D1_DP_PORT))
//--------------------------------------------------
// Description  : Dp HotPlug Event
// Input Value  : Hot Plug Type
// Output Value : None
//--------------------------------------------------
void ScalerSyncDpDualPortHotPlugEvent(EnumDpHotPlugAssertType enumHpdType)
{
    if(enumHpdType == _DP_HPD_ASSERTED)
    {
        if((PCB_D0_HOTPLUG_DETECT() == _D0_HOT_PLUG_HIGH) && (PCB_D1_HOTPLUG_DETECT() == _D1_HOT_PLUG_HIGH))
        {
            return;
        }
    }
    else
    {
        ScalerDpRx0AVMute();
        ScalerDpRx1AVMute();
    }

    if(enumHpdType == _DP_HPD_NONE)
    {
        return;
    }

    if(enumHpdType == _DP_HPD_LOW)
    {
        PCB_D0_HOTPLUG(_D0_HOT_PLUG_LOW);
        PCB_D1_HOTPLUG(_D1_HOT_PLUG_LOW);

        return;
    }
    else if(enumHpdType == _DP_HPD_LOW_RESET_AUX)
    {
        // Reset Aux
        ScalerSetBit(PB7_C0_DPCD_CTRL, ~_BIT7, _BIT7);
        ScalerSetBit(PBA_C0_DPCD_CTRL, ~_BIT7, _BIT7);

        PCB_D0_HOTPLUG(_D0_HOT_PLUG_LOW);
        PCB_D1_HOTPLUG(_D1_HOT_PLUG_LOW);

        return;
    }

    // Reset DDC0
    MCU_FF1F_DDC0_DDC_CONTROL_1 |= _BIT1;
    MCU_FF2D_DDC1_DDC_CONTROL_1 |= _BIT1;

    // Release Aux
    ScalerSetBit(PB7_C0_DPCD_CTRL, ~_BIT7, 0x00);
    ScalerSetBit(PBA_C0_DPCD_CTRL, ~_BIT7, 0x00);

    ScalerDpRx0DpcdLinkStatusReset(_DP_DPCD_LINK_STATUS_INITIAL);
    ScalerDpRx1DpcdLinkStatusReset(_DP_DPCD_LINK_STATUS_INITIAL);

#if(_DP_FREESYNC_SUPPORT == _ON)
    SET_DP_RX0_AUX_MANUAL_MODE();
    ScalerDpRx0SetDpcdValue(0x00, 0x01, 0x07, 0x00);
    SET_DP_RX0_AUX_AUTO_MODE();

    SET_DP_RX1_AUX_MANUAL_MODE();
    ScalerDpRx1SetDpcdValue(0x00, 0x01, 0x07, 0x00);
    SET_DP_RX1_AUX_AUTO_MODE();
#endif

#if(_DP_TX_SUPPORT == _ON)
#if(_D0_DP_MST_PORT_SUPPORT == _ON)
    ScalerDpRx0HDCPBlockReset();
#endif

#if(_D1_DP_MST_PORT_SUPPORT == _ON)
    ScalerDpRx1HDCPBlockReset();
#endif
#endif

#if(_DP_ASSR_MODE_SUPPORT == _ON)
    SET_DP_RX0_AUX_MANUAL_MODE();
    ScalerDpRx0SetDpcdValue(0x00, 0x01, 0x0A, 0x00);
    SET_DP_RX0_AUX_AUTO_MODE();

    SET_DP_RX1_AUX_MANUAL_MODE();
    ScalerDpRx1SetDpcdValue(0x00, 0x01, 0x0A, 0x00);
    SET_DP_RX1_AUX_AUTO_MODE();
#endif

    if(enumHpdType == _DP_LONG_HPD_EVENT)
    {
        ScalerSyncDpDualPortHotPlugDuration(800);
    }
    else if(enumHpdType == _DP_HDCP_LONG_HPD_EVENT)
    {
        ScalerSyncDpDualPortHotPlugDuration(800);
    }
    else if(enumHpdType == _DP_MST_LONG_HPD_EVENT)
    {
        // Reset Aux
        ScalerSetBit(PB7_C0_DPCD_CTRL, ~_BIT7, _BIT7);
        ScalerSetBit(PBA_C0_DPCD_CTRL, ~_BIT7, _BIT7);

        ScalerSyncDpDualPortHotPlugDuration(800);
    }
    else
    {
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

        if(GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT)
        {
            PCB_DIGITAL_D0_D6_SWITCH_LANE(_DP_D0_D6_SWITCH_D0);
            PCB_DIGITAL_D0_D6_SWITCH_AUX_HPD(_DP_D0_D6_SWITCH_D0);
            ScalerMcuDdcRamEDIDAddrSelect(_D0_DDCRAM, _DDCRAM_TOP_ADDR);
        }
        else if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
        {
            PCB_DIGITAL_D0_D6_SWITCH_LANE(_DP_D0_D6_SWITCH_D6);
            PCB_DIGITAL_D0_D6_SWITCH_AUX_HPD(_DP_D0_D6_SWITCH_D6);
            ScalerMcuDdcRamEDIDAddrSelect(_D0_DDCRAM, _DDCRAM_BOTTOM_ADDR);
        }

        PCB_DIGITAL_D6_SWITCH_POWER(_DIGITAL_D6_SWITCH_POWER_ON);
#endif
        ScalerSyncDpDualPortHotPlugDuration(0);
    }

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
    if((GET_D6_SWITCH_POWER_STATUS() == _DIGITAL_D6_SWITCH_POWER_ON) &&
       (((GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT) && (GET_D0_CABLE_STATUS() == _TRUE)) ||
        ((GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT) && (GET_D6_CABLE_STATUS() == _TRUE))))
#else
    if(GET_D0_CABLE_STATUS() == _TRUE)
#endif
    {
#if(_DP_MST_SUPPORT == _ON)

        ScalerTimerActiveTimerEvent(SEC(3), _SCALER_TIMER_EVENT_DP_RX0_VALID_SIGNAL_DETECT_CHECK);
#else
        ScalerTimerActiveTimerEvent(SEC(1.2), _SCALER_TIMER_EVENT_DP_RX0_VALID_SIGNAL_DETECT_CHECK);
#endif
    }

    if(GET_D1_CABLE_STATUS() == _TRUE)
    {
#if(_DP_MST_SUPPORT == _ON)

        ScalerTimerActiveTimerEvent(SEC(3), _SCALER_TIMER_EVENT_DP_RX1_VALID_SIGNAL_DETECT_CHECK);
#else
        ScalerTimerActiveTimerEvent(SEC(1.2), _SCALER_TIMER_EVENT_DP_RX1_VALID_SIGNAL_DETECT_CHECK);
#endif
    }

    // Reset Aux
    ScalerSetBit(PB7_C0_DPCD_CTRL, ~_BIT7, _BIT7);
    ScalerSetBit(PBA_C0_DPCD_CTRL, ~_BIT7, _BIT7);

    // Release Aux
    ScalerSetBit(PB7_C0_DPCD_CTRL, ~_BIT7, 0x00);
    ScalerSetBit(PBA_C0_DPCD_CTRL, ~_BIT7, 0x00);
}

//--------------------------------------------------
// Description  : Two Port Hot Plug Low Pulse Duration
// Input Value  : usMs
// Output Value : None
//--------------------------------------------------
void ScalerSyncDpDualPortHotPlugDuration(WORD usMs)
{
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
    if((((GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT) && (GET_D0_CABLE_STATUS() == _TRUE)) ||
        ((GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT) && (GET_D6_CABLE_STATUS() == _TRUE))) &&
       (GET_D1_CABLE_STATUS() == _TRUE))
#else
    if((GET_D0_CABLE_STATUS() == _TRUE) && (GET_D1_CABLE_STATUS() == _TRUE))
#endif
    {
        if(usMs != 1)
        {
            if(usMs != 0)
            {
                DebugMessageOsd("HPD LOW - 2Port", 0);
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                if(GET_D6_SWITCH_POWER_STATUS() == _DIGITAL_D6_SWITCH_POWER_ON)
#endif
                {
                    PCB_D0_HOTPLUG(_D0_HOT_PLUG_LOW);
                }

                PCB_D1_HOTPLUG(_D1_HOT_PLUG_LOW);
                ScalerTimerDelayXms(usMs);
            }

#if(_DP_TX_SUPPORT == _ON)
            // Update sink count
            ScalerDpRx0UpdateSinkCount();
            ScalerDpRx1UpdateSinkCount();
#endif

            PCB_D0_HOTPLUG(_D0_HOT_PLUG_HIGH);
            PCB_D1_HOTPLUG(_D1_HOT_PLUG_HIGH);

            DebugMessageOsd("HPD High - 2Port", 0);
        }
    }
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
    else if(((GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT) && (GET_D0_CABLE_STATUS() == _TRUE)) ||
            ((GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT) && (GET_D6_CABLE_STATUS() == _TRUE)))
#else
    else if(GET_D0_CABLE_STATUS() == _TRUE)
#endif
    {
        ScalerDpRx0HotPlugDuration(usMs);
    }
    else if(GET_D1_CABLE_STATUS() == _TRUE)
    {
        ScalerDpRx1HotPlugDuration(usMs);
    }
}
#endif //#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D1_INPUT_PORT_TYPE == _D1_DP_PORT))


#if(_DP_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Switch DP FREESYNC Support
// Input Value  : Hotplug Type and FREESYNC Enable or Not
// Output Value : None
//--------------------------------------------------
void ScalerSyncDpFREESYNCSupportSwitch(EnumDpFREESYNCCapabilitySwitch enumDpFREESYNCCapSwitch, bit bEn)
{
    if(enumDpFREESYNCCapSwitch == _DP_FREESYNC_CAPABILITY_SWITCH)

    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        if(((bit)(ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x07) & _BIT6)) != bEn)
        {
            SET_DP_RX_CAPABILITY_SWITCHED();
            SET_DP_RX0_FREESYNC_CAPABILITY_SWITCH();
        }
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        if(((bit)(ScalerDpRx1GetDpcdInfo(0x00, 0x00, 0x07) & _BIT6)) != bEn)
        {
            SET_DP_RX_CAPABILITY_SWITCHED();
            SET_DP_RX1_FREESYNC_CAPABILITY_SWITCH();
        }
#endif
    }

    SET_FREESYNC_SUPPORT(bEn);

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

    SET_DP_RX0_FREESYNC_SUPPORT(bEn);

    if(bEn == _ON)
    {
        pData[0] = ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x07);
        ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x07, (pData[0] | _BIT6));
    }
    else
    {
        CLR_FREESYNC_ENABLED();
        pData[0] = ScalerDpRx0GetDpcdInfo(0x00, 0x00, 0x07);
        ScalerDpRx0SetDpcdValue(0x00, 0x00, 0x07, (pData[0] & ~_BIT6));
    }
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

    SET_DP_RX1_FREESYNC_SUPPORT(bEn);

    if(bEn == _ON)
    {
        pData[0] = ScalerDpRx1GetDpcdInfo(0x00, 0x00, 0x07);
        ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x07, (pData[0] | _BIT6));
    }
    else
    {
        CLR_FREESYNC_ENABLED();
        pData[0] = ScalerDpRx1GetDpcdInfo(0x00, 0x00, 0x07);
        ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x07, (pData[0] & ~_BIT6));
    }
#endif
}

#endif

#if((_DP_TX_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Dp Rx Fake Power Saving Check
// Input Value  : None
// Output Value : True  --> Fake Power Saving
//                False --> Power Saving
//--------------------------------------------------
bit ScalerSyncDpFakePowerSavingCheck(void)
{
    if(g_enumDpMSTCapablePort != _DP_MST_NO_PORT)
    {
        if(GET_DP_SOURCE_FIRST_POWER_ON() == _TRUE)
        {
            return _TRUE;
        }

        if(GET_DP_CHECK_AUX_CH_POWER_OFF() == _TRUE)
        {
            return _FALSE;
        }

        if((GET_REG_DP_DPCD_INFO(0x00, 0x01, 0x11) & _BIT0) == _BIT0)
        {
            return _TRUE;
        }

        // Check if MSG Processing or Stream Propagating
        if((ScalerDpRxMstCheckMsgTransition() == _TRUE) || (GET_REG_DP_DPCD_INFO(0x00, 0x02, 0xC1) != 0))
        {
            return _TRUE;
        }

        return GET_DP_LT_STATUS_CHCEK();
    }

    return _FALSE;
}
#endif

#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
//--------------------------------------------------
// Description  : Check whether Current Timing is Reasonable
// Input Value  : Hwidth and VHeight
// Output Value : TRUE => OK
//--------------------------------------------------
bit ScalerSyncDualDpDoubleCheck(EnumSourceSearchPort enumSourceSearchPort)
{
    WORD usHwidth = 0;
    WORD usVHeight = 0;

    switch(enumSourceSearchPort)
    {
        case _D0_INPUT_PORT:
            usHwidth = (((WORD)ScalerGetByte(PB5_45_MN_DPF_HWD_M) << 8) | ScalerGetByte(PB5_46_MN_DPF_HWD_L));
            usVHeight = (((WORD)ScalerGetByte(PB5_4D_MN_DPF_VHT_M) << 8) | ScalerGetByte(PB5_4E_MN_DPF_VHT_L));

            if(GET_DP_RX0_INTERLACE_STATUS() == _TRUE)
            {
                usVHeight *= 2;
            }

            break;

        case _D1_INPUT_PORT:
            usHwidth = (((WORD)ScalerGetByte(PB8_45_MN_DPF_HWD_M) << 8) | ScalerGetByte(PB8_46_MN_DPF_HWD_L));
            usVHeight = (((WORD)ScalerGetByte(PB8_4D_MN_DPF_VHT_M) << 8) | ScalerGetByte(PB8_4E_MN_DPF_VHT_L));

            if(GET_DP_RX1_INTERLACE_STATUS() == _TRUE)
            {
                usVHeight *= 2;
            }

            break;

        default:
        case _D7_INPUT_PORT:
            usHwidth = (((WORD)ScalerGetByte(PB5_45_MN_DPF_HWD_M) << 8) | ScalerGetByte(PB5_46_MN_DPF_HWD_L)) +
                       (((WORD)ScalerGetByte(PB8_45_MN_DPF_HWD_M) << 8) | ScalerGetByte(PB8_46_MN_DPF_HWD_L));

            usVHeight = (((WORD)ScalerGetByte(PB5_4D_MN_DPF_VHT_M) << 8) | ScalerGetByte(PB5_4E_MN_DPF_VHT_L));

            break;
    }

    // Check aspect ratio
    if(usHwidth > usVHeight)
    {
        // For Normal Aspect Ratio
        if((usHwidth >> 1) < usVHeight)
        {
            return _TRUE;
        }
        else
        {
            PDATA_WORD(0) = ((DWORD)usHwidth * 100 / usVHeight);

            // For 21:9 Aspect
            if((PDATA_WORD(0) > 230) && (PDATA_WORD(0) < 240))
            {
                return _TRUE;
            }
        }
    }

    return _FALSE;
}
#endif
#endif // #if(_DP_SUPPORT == _ON)

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp Tx PowerProc
// Input Value  : EnumPowerAction
// Output Value : None
//--------------------------------------------------
void ScalerSyncDpTxPowerProc(EnumPowerAction enumPowerAction)
{
    switch(enumPowerAction)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:

            ScalerDpTxInitial();

            // Power CMU PHY But use power down mode
            ScalerGDIPhyTxCMUPowerDownMode();

            break;

        case _POWER_ACTION_NORMAL_TO_PS:
        case _POWER_ACTION_NOSUPPORT_PS_TO_PS:
        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_NOSUPPORT_PS_TO_OFF:
        case _POWER_ACTION_FAKE_PS_TO_OFF:

            ScalerDpTxStateChangeEvent(_DP_TX_MODE_STATUS_INITIAL);
            ScalerDpTxHDCPChangeAuthState(_DP_TX_HDCP_STATE_IDLE);

            CLR_DP_TX_DOWNSTREAM_INFO_READY();

            // Power Down ML PHY
            ScalerGDIPhyTxMLPowerOff();

            // Power CMU PHY
            ScalerGDIPhyTxCMUPowerOff();

            // Power Down Aux CH
            ScalerSetBit(PBD_A0_AUX_TX_CTRL, ~_BIT0, 0x00);

            // Clear HPD IRQ Flag
            ScalerSetByte(PBB_71_HPD_IRQ, 0xFE);

            // Clear IRQ HPD Type Flag
            CLR_DP_TX_IRQ_HPD_TYPE();
            CLR_DP_TX_IRQ_HPD_TYPE_INT();
            CLR_DP_TX_IRQ_HPD_DETECTED();
            CLR_DP_TX_IRQ_HDCP_TYPE();

            CLR_DP_TX_HDCP_DOWNSTREAM_SUPPORTED();
            CLR_DP_TX_HDCP_DOWNSTREAM_REPEATER();
            CLR_DP_TX_HDCP_AUTH_START();
            CLR_DP_TX_HDCP_AUTH_HOLD();

            // Disable HDCP function, Encryption and Reset Repeater Flag
            ScalerSetBit(PBB_30_DPTX_HDCP_CTRL1, ~(_BIT4 | _BIT1 | _BIT0), 0x00);

            break;

        case _POWER_ACTION_PS_TO_OFF:

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Dp Hdcp Port Switch
// Input Value  : enumDisplayMode, ucInputPort
// Output Value : None
//--------------------------------------------------
void ScalerSyncDpTxHdcpUpstreamSwitchProc(EnumDisplayMode enumDisplayMode, BYTE ucInputPort)
{
    if(enumDisplayMode == _DISPLAY_MODE_1P)
    {
#if(_DP_MST_SUPPORT == _ON)
#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) || ((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0)))
        if(g_enumDpMSTCapablePort == _DP_MST_RX0_PORT)
        {
            SET_DP_RX_HDCP_UPSTREAM_PORT(_HDCP_D0_PORT);

            return;
        }
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        if(g_enumDpMSTCapablePort == _DP_MST_RX1_PORT)
        {
            SET_DP_RX_HDCP_UPSTREAM_PORT(_HDCP_D1_PORT);

            return;
        }
#endif
#endif

#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) || ((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0)))
        if((ucInputPort == _D0_INPUT_PORT) || (ucInputPort == _D6_INPUT_PORT))
        {
            if((GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_NORMAL_LINK_TRAINING_PASS))
            {
                SET_DP_RX_HDCP_UPSTREAM_PORT(_HDCP_D0_PORT);

                return;
            }
        }
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        if(ucInputPort == _D1_INPUT_PORT)
        {
            if((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_LINK_TRAINING_PASS))
            {
                SET_DP_RX_HDCP_UPSTREAM_PORT(_HDCP_D1_PORT);

                return;
            }
        }
#endif
    }
    else
    {
#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) || ((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0)))
        if((ucInputPort == _D0_INPUT_PORT) || (ucInputPort == _D6_INPUT_PORT))
        {
            SET_DP_RX_HDCP_UPSTREAM_PORT(_HDCP_D0_PORT);

            return;
        }
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        if(ucInputPort == _D1_INPUT_PORT)
        {
            SET_DP_RX_HDCP_UPSTREAM_PORT(_HDCP_D1_PORT);

            return;
        }
#endif
    }

    SET_DP_RX_HDCP_UPSTREAM_PORT(_HDCP_NO_PORT);
}

//--------------------------------------------------
// Description  : Get Upstream HDCP event
// Input Value  : None
// Output Value : EnumDPRxHDCPUpstreamAuthStatus
//--------------------------------------------------
EnumDPRxHDCPUpstreamAuthStatus ScalerSyncDpHdcpGetUpstreamEvent(void)
{
#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) || ((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0)))
    if(GET_DP_RX_HDCP_UPSTREAM_PORT() == _HDCP_D0_PORT)
    {
        return GET_DP_RX0_HDCP_UPSTREAM_EVENT();
    }
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    if(GET_DP_RX_HDCP_UPSTREAM_PORT() == _HDCP_D1_PORT)
    {
        return GET_DP_RX1_HDCP_UPSTREAM_EVENT();
    }
#endif

    return _DP_RX_HDCP_UPSTREAM_AUTH_EVENT_NONE;
}

//--------------------------------------------------
// Description  : Get Upstream HDCP status
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerSyncDpHdcpGetUpstreamEncryptStatus(void)
{
#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) || ((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0)))
    if(GET_DP_RX_HDCP_UPSTREAM_PORT() == _HDCP_D0_PORT)
    {
        return ((ScalerDpRx0HdcpEnebled() == _TRUE) && (ScalerDpRx0HDCPCheckLvp() == _TRUE));
    }
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    if(GET_DP_RX_HDCP_UPSTREAM_PORT() == _HDCP_D1_PORT)
    {
        return ((ScalerDpRx1HdcpEnebled() == _TRUE) && (ScalerDpRx1HDCPCheckLvp() == _TRUE));
    }
#endif

    return _FALSE;
}
#endif // End of #if(_DP_TX_SUPPORT == _ON)

#if(_DIGITAL_PORT_SUPPORT == _ON)
#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable/Disable DownLoad DPTx HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncHdcpEnableDownLoadDPTxKey(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Enable Key download port
        ScalerSetBit(PBB_30_DPTX_HDCP_CTRL1, ~_BIT3, _BIT3);
    }
    else
    {
        // Disable Key download port
        ScalerSetBit(PBB_30_DPTX_HDCP_CTRL1, ~_BIT3, 0x00);
    }
}

//--------------------------------------------------
// Description  : DownLoad TX HDCP AKsv
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncHdcpDownLoadDPTxAKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray)
{
    for(pData[0] = ucSubAddr; pData[0] < ucLength; pData[0]++)
    {
        g_pucHdcpAksvBackup[pData[0]] = pucReadArray[pData[0]];
    }

    DebugMessageDigital("8. HDCP Aksv Backup", g_pucHdcpAksvBackup[0]);
    DebugMessageDigital("8. HDCP Aksv Backup", g_pucHdcpAksvBackup[1]);
    DebugMessageDigital("8. HDCP Aksv Backup", g_pucHdcpAksvBackup[2]);
    DebugMessageDigital("8. HDCP Aksv Backup", g_pucHdcpAksvBackup[3]);
    DebugMessageDigital("8. HDCP Aksv Backup", g_pucHdcpAksvBackup[4]);
}

//--------------------------------------------------
// Description  : DownLoad TX HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncHdcpDownLoadDPTxAKey(WORD usLength, BYTE *pucReadArray)
{
    ScalerWrite(PBB_32_DP_HDCP_KEY_DL_PORT, usLength, pucReadArray, _NON_AUTOINC);
}
#endif

//--------------------------------------------------
// Description  : Check whether HDCP is enabled
// Input Value  : Input Port
// Output Value : TRUE => HDCP Enabled
//--------------------------------------------------
bit ScalerSyncHdcpCheckEnabled(BYTE ucInputPort)
{
    if(ucInputPort == _D0_INPUT_PORT)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        return ScalerDpRx0HdcpEnebled();
#elif((_D0_INPUT_PORT_TYPE == _D0_DVI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT))
        return ScalerTMDSRx0HdcpEnabled();
#endif
    }
    else if(ucInputPort == _D1_INPUT_PORT)
    {
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        return ScalerDpRx1HdcpEnebled();
#elif((_D1_INPUT_PORT_TYPE == _D1_DVI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
        return ScalerTMDSRx1HdcpEnabled();
#endif
    }
    else if(ucInputPort == _D2_INPUT_PORT)
    {
#if((_D2_INPUT_PORT_TYPE == _D2_DVI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
        return ScalerTMDSRx2HdcpEnabled();
#elif(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)
        return ScalerTMDSRx3HdcpEnabled();
#endif
    }
    else if(ucInputPort == _D3_INPUT_PORT)
    {
#if((_D3_INPUT_PORT_TYPE == _D3_DVI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT))
        return ScalerTMDSRx3HdcpEnabled();
#elif(_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT)
        return ScalerTMDSRx4HdcpEnabled();
#endif
    }
    else if(ucInputPort == _D4_INPUT_PORT)
    {
#if((_D4_INPUT_PORT_TYPE == _D4_DVI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT))
        return ScalerTMDSRx4HdcpEnabled();
#elif(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
        return ScalerTMDSRx5HdcpEnabled();
#endif
    }
    else if(ucInputPort == _D5_INPUT_PORT)
    {
#if(_D5_TMDS_SUPPORT == _ON)
        return ScalerTMDSRx5HdcpEnabled();
#endif
    }
    else if(ucInputPort == _D6_INPUT_PORT)
    {
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        return ScalerDpRx0HdcpEnebled();
#endif
    }
    else if(ucInputPort == _D7_INPUT_PORT)
    {
#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
        switch(GET_D7_SWITCH_SELECT())
        {
            case _D0_INPUT_PORT:
                return ScalerDpRx0HdcpEnebled();
            case _D1_INPUT_PORT:
                return ScalerDpRx1HdcpEnebled();
            default:
            case _D7_INPUT_PORT:
                return ((ScalerDpRx0HdcpEnebled() == _TRUE) &&
                        (ScalerDpRx1HdcpEnebled() == _TRUE));
        }
#endif
    }

    return _FALSE;
}
#endif // End of #if(_DIGITAL_PORT_SUPPORT == _ON)

#if(_URGENT_EVENT_CHECK_MODE == _ON)
//--------------------------------------------------
// Description  : Check Urgent Event Occur
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerSyncCheckUrgentEvent(void)
{
#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
    if(ScalerDpRxMstCheckMsgTransition() == _TRUE)
    {
        SET_URGENT_EVENT_OCCUR_FLG();

        return _TRUE;
    }
#endif

#if(_HDCP_2_2_SUPPORT == _ON)
    if(GET_HDCP_2_2_AUTHENTICATION_ACTIVE() == _TRUE)
    {
        DebugMessageHDCP2("HDCP2 Urgent", g_ucHdcp2AuthActive);

        SET_URGENT_EVENT_OCCUR_FLG();

        return _TRUE;
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get Urgent Event Occured Flag
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerSyncGetUrgentEventFlg(void)
{
    return GET_URGENT_EVENT_OCCUR_FLG();
}

//--------------------------------------------------
// Description  : Clear Urgent Event Occured Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncClrUrgentEventFlg(void)
{
    CLR_URGENT_EVENT_OCCUR_FLG();
}
#endif // End of #if(_URGENT_EVENT_CHECK_MODE == _ON)

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
//--------------------------------------------------
// Description  : TMDS Power Saving Detect DDC Handshake
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerSyncDdcDetect_EXINT1(void) using 2
{
    WORD usDebounceCnt = 0;

#if(((_D0_TMDS_SUPPORT == _ON) && (_D0_DDC_CHANNEL_SEL == _DDC0)) || ((_D1_TMDS_SUPPORT == _ON) && (_D1_DDC_CHANNEL_SEL == _DDC0)) || ((_D2_TMDS_SUPPORT == _ON) && (_D2_DDC_CHANNEL_SEL == _DDC0)))

    // DDC0 Detect SCL Toggle
    if((MCU_FFE4_DDC0_EDID_IRQ & 0x0C) == 0x0C)
    {
        // Debounce 300us
        for(usDebounceCnt = 0; usDebounceCnt < g_usDDCDebounceCnt; usDebounceCnt++) {};

        // Clear SCL Toggle
        MCU_FFE4_DDC0_EDID_IRQ |= _BIT2;

        // EDID read freq. 100K about 20us
        Delay5us_EXINT(g_ucDelay5usN);
        Delay5us_EXINT(g_ucDelay5usN);
        Delay5us_EXINT(g_ucDelay5usN);
        Delay5us_EXINT(g_ucDelay5usN);

        // Double check SCL Toggle again
        if((MCU_FFE4_DDC0_EDID_IRQ & 0x0C) == 0x0C)
        {
            // Disable SCL Toggle IRQ
            MCU_FFE4_DDC0_EDID_IRQ &= ~_BIT3;
            // Clear SCL Toggle
            MCU_FFE4_DDC0_EDID_IRQ |= _BIT2;

#if((_D0_TMDS_SUPPORT == _ON) && (_D0_DDC_CHANNEL_SEL == _DDC0))
            if(GET_DIGITAL_PORT_SWITCH_TO_D0() == _TRUE)
            {
                SET_TMDS_RX0_DDC_DETECTED();
            }
#endif
            return _TRUE;
        }
    }
#endif

#if(((_D0_TMDS_SUPPORT == _ON) && (_D0_DDC_CHANNEL_SEL == _DDC1)) || ((_D1_TMDS_SUPPORT == _ON) && (_D1_DDC_CHANNEL_SEL == _DDC1)) || ((_D2_TMDS_SUPPORT == _ON) && (_D2_DDC_CHANNEL_SEL == _DDC1)))

    // DDC1 Detect SCL Toggle
    if((MCU_FFE5_DDC1_EDID_IRQ & 0x0C) == 0x0C)
    {
        // Debounce 300us
        for(usDebounceCnt = 0; usDebounceCnt < g_usDDCDebounceCnt; usDebounceCnt++) {};

        // Clear SCL Toggle
        MCU_FFE5_DDC1_EDID_IRQ |= _BIT2;

        // EDID read freq. 100K about 20us
        Delay5us_EXINT(g_ucDelay5usN);
        Delay5us_EXINT(g_ucDelay5usN);
        Delay5us_EXINT(g_ucDelay5usN);
        Delay5us_EXINT(g_ucDelay5usN);

        // Double check SCL Toggle again
        if((MCU_FFE5_DDC1_EDID_IRQ & 0x0C) == 0x0C)
        {
            // Disable SCL Toggle IRQ
            MCU_FFE5_DDC1_EDID_IRQ &= ~_BIT3;
            // Clear SCL Toggle
            MCU_FFE5_DDC1_EDID_IRQ |= _BIT2;

#if((_D1_TMDS_SUPPORT == _ON) && (_D1_DDC_CHANNEL_SEL == _DDC1))
            if(GET_DIGITAL_PORT_SWITCH_TO_D1() == _TRUE)
            {
                SET_TMDS_RX1_DDC_DETECTED();
            }
#endif
            return _TRUE;
        }
    }
#endif

#if(((_D0_TMDS_SUPPORT == _ON) && (_D0_DDC_CHANNEL_SEL == _DDC2)) || ((_D1_TMDS_SUPPORT == _ON) && (_D1_DDC_CHANNEL_SEL == _DDC2)) || ((_D2_TMDS_SUPPORT == _ON) && (_D2_DDC_CHANNEL_SEL == _DDC2)))

    // DDC2 Detect SCL Toggle
    if((MCU_FE69_DDC2_EDID_IRQ & 0x0C) == 0x0C)
    {
        // Debounce 300us
        for(usDebounceCnt = 0; usDebounceCnt < g_usDDCDebounceCnt; usDebounceCnt++) {};

        // Clear SCL Toggle
        MCU_FE69_DDC2_EDID_IRQ |= _BIT2;

        // EDID read freq. 100K about 20us
        Delay5us_EXINT(g_ucDelay5usN);
        Delay5us_EXINT(g_ucDelay5usN);
        Delay5us_EXINT(g_ucDelay5usN);
        Delay5us_EXINT(g_ucDelay5usN);

        // Double check SCL Toggle again
        if((MCU_FE69_DDC2_EDID_IRQ & 0x0C) == 0x0C)
        {
            // Disable SCL Toggle IRQ
            MCU_FE69_DDC2_EDID_IRQ &= ~_BIT3;
            // Clear SCL Toggle
            MCU_FE69_DDC2_EDID_IRQ |= _BIT2;

#if((_D2_TMDS_SUPPORT == _ON) && (_D2_DDC_CHANNEL_SEL == _DDC2))
            if(GET_DIGITAL_PORT_SWITCH_TO_D2() == _TRUE)
            {
                SET_TMDS_RX2_DDC_DETECTED();
            }
#endif

            return _TRUE;
        }
    }
#endif

#if((_D3_TMDS_SUPPORT == _ON) && (_D3_DDC_CHANNEL_SEL == _DDC3))

    // DDC3 Detect SCL Toggle
    if((MCU_FE72_DDC3_EDID_IRQ & 0x0C) == 0x0C)
    {
        // Debounce 300us
        for(usDebounceCnt = 0; usDebounceCnt < g_usDDCDebounceCnt; usDebounceCnt++) {};

        // Clear SCL Toggle
        MCU_FE72_DDC3_EDID_IRQ |= _BIT2;

        // EDID read freq. 100K about 20us
        Delay5us_EXINT(g_ucDelay5usN);
        Delay5us_EXINT(g_ucDelay5usN);
        Delay5us_EXINT(g_ucDelay5usN);
        Delay5us_EXINT(g_ucDelay5usN);

        // Double check SCL Toggle again
        if((MCU_FE72_DDC3_EDID_IRQ & 0x0C) == 0x0C)
        {
            // Disable SCL Toggle IRQ
            MCU_FE72_DDC3_EDID_IRQ &= ~_BIT3;
            // Clear SCL Toggle
            MCU_FE72_DDC3_EDID_IRQ |= _BIT2;

            if(GET_DIGITAL_PORT_SWITCH_TO_D3() == _TRUE)
            {
                SET_TMDS_RX3_DDC_DETECTED();
            }

            return _TRUE;
        }
    }
#endif

#if((_D4_TMDS_SUPPORT == _ON) && (_D4_DDC_CHANNEL_SEL == _DDC4))

    // DDC4 Detect SCL Toggle
    if((MCU_FE7B_DDC4_EDID_IRQ & 0x0C) == 0x0C)
    {
        // Debounce 300us
        for(usDebounceCnt = 0; usDebounceCnt < g_usDDCDebounceCnt; usDebounceCnt++) {};

        // Clear SCL Toggle
        MCU_FE7B_DDC4_EDID_IRQ |= _BIT2;

        // EDID read freq. 100K about 20us
        Delay5us_EXINT(g_ucDelay5usN);
        Delay5us_EXINT(g_ucDelay5usN);
        Delay5us_EXINT(g_ucDelay5usN);
        Delay5us_EXINT(g_ucDelay5usN);

        // Double check SCL Toggle again
        if((MCU_FE7B_DDC4_EDID_IRQ & 0x0C) == 0x0C)
        {
            // Disable SCL Toggle IRQ
            MCU_FE7B_DDC4_EDID_IRQ &= ~_BIT3;
            // Clear SCL Toggle
            MCU_FE7B_DDC4_EDID_IRQ |= _BIT2;

            if(GET_DIGITAL_PORT_SWITCH_TO_D4() == _TRUE)
            {
                SET_TMDS_RX4_DDC_DETECTED();
            }

            return _TRUE;
        }
    }
#endif

#if((_D5_TMDS_SUPPORT == _ON) && (_D5_DDC_CHANNEL_SEL == _DDC5))

    // DDC5 Detect SCL Toggle
    if((MCU_FE84_DDC5_EDID_IRQ & 0x0C) == 0x0C)
    {
        // Debounce 300us
        for(usDebounceCnt = 0; usDebounceCnt < g_usDDCDebounceCnt; usDebounceCnt++) {};

        // Clear SCL Toggle
        MCU_FE84_DDC5_EDID_IRQ |= _BIT2;

        // EDID read freq. 100K about 20us
        Delay5us_EXINT(g_ucDelay5usN);
        Delay5us_EXINT(g_ucDelay5usN);
        Delay5us_EXINT(g_ucDelay5usN);
        Delay5us_EXINT(g_ucDelay5usN);

        // Double check SCL Toggle again
        if((MCU_FE84_DDC5_EDID_IRQ & 0x0C) == 0x0C)
        {
            // Disable SCL Toggle IRQ
            MCU_FE84_DDC5_EDID_IRQ &= ~_BIT3;
            // Clear SCL Toggle
            MCU_FE84_DDC5_EDID_IRQ |= _BIT2;

            if(GET_DIGITAL_PORT_SWITCH_TO_D5() == _TRUE)
            {
                SET_TMDS_RX5_DDC_DETECTED();
            }

            return _TRUE;
        }
    }
#endif

    return _FALSE;
}

#if(_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : TMDS EDID Switch
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSEdidSwitch(BYTE ucPortSelect)
{
    switch(ucPortSelect)
    {
        // For User, DVI and DUAL_DVI Port can not pull HPD
#if((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT))
        case _D0_INPUT_PORT:

            SET_TMDS_RX0_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);

            break;
#endif

#if((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
        case _D1_INPUT_PORT:

            SET_TMDS_RX1_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);

            break;
#endif

#if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
        case _D2_INPUT_PORT:

            SET_TMDS_RX2_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);

            break;
#endif

#if((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT))
        case _D3_INPUT_PORT:

            SET_TMDS_RX3_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);

            break;
#endif

#if((_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT))
        case _D4_INPUT_PORT:

            SET_TMDS_RX4_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);

            break;
#endif

#if((_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT))
        case _D5_INPUT_PORT:

            SET_TMDS_RX5_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Check DDC channel Idle
// Input Value  : ucInputPort
// Output Value : None
//--------------------------------------------------
void ScalerSyncHDMIDdcCheckBusy(BYTE ucInputPort)
{
    WORD ustemp = 0;

    switch(ucInputPort)
    {
#if(_D0_HDMI_SUPPORT == _ON)
        case _D0_INPUT_PORT:

#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
            if(GET_D0_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
            {
                // Disable SCL Toggle IRQ
                MCU_FFE4_DDC0_EDID_IRQ &= ~_BIT3;
                MCU_FFE4_DDC0_EDID_IRQ |= _BIT2;

                // set a polling duration
                for(ustemp = 0; ustemp < 1500; ustemp++)
                {
                    // delay 20us for IIC 100k
                    Delay5us_EXINT(g_ucDelay5usN);
                    Delay5us_EXINT(g_ucDelay5usN);
                    Delay5us_EXINT(g_ucDelay5usN);
                    Delay5us_EXINT(g_ucDelay5usN);

                    if((MCU_FFE4_DDC0_EDID_IRQ & _BIT2) == _BIT2)
                    {
                        MCU_FFE4_DDC0_EDID_IRQ |= _BIT2;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            break;
#endif

#if(_D1_HDMI_SUPPORT == _ON)
        case _D1_INPUT_PORT:

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
            if(GET_D1_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
            {
                // Disable SCL Toggle IRQ
                MCU_FFE5_DDC1_EDID_IRQ &= ~_BIT3;
                MCU_FFE5_DDC1_EDID_IRQ |= _BIT2;

                // set a polling duration
                for(ustemp = 0; ustemp < 1500; ustemp++)
                {
                    // Delay 20us for IIC 100k
                    Delay5us_EXINT(g_ucDelay5usN);
                    Delay5us_EXINT(g_ucDelay5usN);
                    Delay5us_EXINT(g_ucDelay5usN);
                    Delay5us_EXINT(g_ucDelay5usN);

                    if((MCU_FFE5_DDC1_EDID_IRQ & _BIT2) == _BIT2)
                    {
                        MCU_FFE5_DDC1_EDID_IRQ |= _BIT2;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            break;
#endif

#if(_D2_HDMI_SUPPORT == _ON)
        case _D2_INPUT_PORT:

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
            if(GET_D2_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
            {
                // Disable SCL Toggle IRQ
                MCU_FE69_DDC2_EDID_IRQ &= ~_BIT3;
                MCU_FE69_DDC2_EDID_IRQ |= _BIT2;

                // Set a Polling Duration: 30ms
                for(ustemp = 0; ustemp < 1500; ustemp++)
                {
                    // delay 20us for IIC 100k
                    Delay5us_EXINT(g_ucDelay5usN);
                    Delay5us_EXINT(g_ucDelay5usN);
                    Delay5us_EXINT(g_ucDelay5usN);
                    Delay5us_EXINT(g_ucDelay5usN);

                    if((MCU_FE69_DDC2_EDID_IRQ & _BIT2) == _BIT2)
                    {
                        MCU_FE69_DDC2_EDID_IRQ |= _BIT2;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            break;
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
            if(GET_D3_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
            {
                // Disable SCL Toggle IRQ
                MCU_FE72_DDC3_EDID_IRQ &= ~_BIT3;
                MCU_FE72_DDC3_EDID_IRQ |= _BIT2;

                // Set a Polling Duration: 30ms
                for(ustemp = 0; ustemp < 1500; ustemp++)
                {
                    // delay 20us for IIC 100k
                    Delay5us_EXINT(g_ucDelay5usN);
                    Delay5us_EXINT(g_ucDelay5usN);
                    Delay5us_EXINT(g_ucDelay5usN);
                    Delay5us_EXINT(g_ucDelay5usN);

                    if((MCU_FE72_DDC3_EDID_IRQ & _BIT2) == _BIT2)
                    {
                        MCU_FE72_DDC3_EDID_IRQ |= _BIT2;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            break;
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        case _D4_INPUT_PORT:

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
            if(GET_D4_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
            {
                // Disable SCL Toggle IRQ
                MCU_FE7B_DDC4_EDID_IRQ &= ~_BIT3;
                MCU_FE7B_DDC4_EDID_IRQ |= _BIT2;

                // Set a Polling Duration: 30ms
                for(ustemp = 0; ustemp < 1500; ustemp++)
                {
                    // delay 20us for IIC 100k
                    Delay5us_EXINT(g_ucDelay5usN);
                    Delay5us_EXINT(g_ucDelay5usN);
                    Delay5us_EXINT(g_ucDelay5usN);
                    Delay5us_EXINT(g_ucDelay5usN);

                    if((MCU_FE7B_DDC4_EDID_IRQ & _BIT2) == _BIT2)
                    {
                        MCU_FE7B_DDC4_EDID_IRQ |= _BIT2;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            break;
#endif

#if(_D5_HDMI_SUPPORT == _ON)
        case _D5_INPUT_PORT:

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
            if(GET_D5_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
            {
                // Disable SCL Toggle IRQ
                MCU_FE84_DDC5_EDID_IRQ &= ~_BIT3;
                MCU_FE84_DDC5_EDID_IRQ |= _BIT2;

                // Set a Polling Duration: 30ms
                for(ustemp = 0; ustemp < 1500; ustemp++)
                {
                    // delay 20us for IIC 100k
                    Delay5us_EXINT(g_ucDelay5usN);
                    Delay5us_EXINT(g_ucDelay5usN);
                    Delay5us_EXINT(g_ucDelay5usN);
                    Delay5us_EXINT(g_ucDelay5usN);

                    if((MCU_FE84_DDC5_EDID_IRQ & _BIT2) == _BIT2)
                    {
                        MCU_FE84_DDC5_EDID_IRQ |= _BIT2;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            break;
#endif

        default:

            break;
    }
}
#endif

//--------------------------------------------------
// Description  : TMDS HPD Toggle Process
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSHPDToggleProc(void)
{
#if(_D0_TMDS_SUPPORT == _ON)
    if(GET_TMDS_RX0_HPD_TRIGGER_EVENT() != _TMDS_HPD_NONE)
    {
        ScalerTMDSRx0HotPlugEvent();
    }
#endif

#if(_D1_TMDS_SUPPORT == _ON)
    if(GET_TMDS_RX1_HPD_TRIGGER_EVENT() != _TMDS_HPD_NONE)
    {
        ScalerTMDSRx1HotPlugEvent();
    }
#endif

#if(_D2_TMDS_SUPPORT == _ON)
    if(GET_TMDS_RX2_HPD_TRIGGER_EVENT() != _TMDS_HPD_NONE)
    {
        ScalerTMDSRx2HotPlugEvent();
    }
#endif

#if(_D3_TMDS_SUPPORT == _ON)
    if(GET_TMDS_RX3_HPD_TRIGGER_EVENT() != _TMDS_HPD_NONE)
    {
        ScalerTMDSRx3HotPlugEvent();
    }
#endif

#if(_D4_TMDS_SUPPORT == _ON)
    if(GET_TMDS_RX4_HPD_TRIGGER_EVENT() != _TMDS_HPD_NONE)
    {
        ScalerTMDSRx4HotPlugEvent();
    }
#endif

#if(_D5_TMDS_SUPPORT == _ON)
    if(GET_TMDS_RX5_HPD_TRIGGER_EVENT() != _TMDS_HPD_NONE)
    {
        ScalerTMDSRx5HotPlugEvent();
    }
#endif
}

#if(_DUAL_DVI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get whether this port is dual DVI Port
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
bit ScalerSyncGetDualDVIMode(EnumSourceSearchPort enumInputPort)
{
    switch(enumInputPort)
    {
#if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)
        case _D2_INPUT_PORT:
            return ScalerTMDSRx2GetDualDVIMode();
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT)
        case _D3_INPUT_PORT:
            return ScalerTMDSRx3GetDualDVIMode();
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
        case _D4_INPUT_PORT:
            return ScalerTMDSRx4GetDualDVIMode();
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check whether Current Timing is Reasonable
// Input Value  : Hwidth and VHeight
// Output Value : TRUE => OK
//--------------------------------------------------
bit ScalerSyncDualDVIDoubleCheck(EnumSourceSearchPort enumSourceSearchPort, WORD usHwidth, WORD usVHeight)
{
    if(usHwidth > usVHeight)
    {
        // For Normal Aspect Ratio
        if((usHwidth >> 1) < usVHeight)
        {
            return _TRUE;
        }
        else
        {
            PDATA_WORD(0) = ((DWORD)usHwidth * 100 / usVHeight);

            // For 21:9 Aspect
            if((PDATA_WORD(0) > 230) && (PDATA_WORD(0) < 240))
            {
                return _TRUE;
            }

            // Ignore Interlace Timing
#if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)
            if((enumSourceSearchPort == _D3_INPUT_PORT) && (ScalerTMDSRx2GetDualDVIMode() == _FALSE) &&
               ((usVHeight == 240) || (usVHeight == 288) || (usVHeight == 384) || (usVHeight == 517) || (usVHeight == 518) || (usVHeight == 540)))
            {
                return _TRUE;
            }
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT)
            if((enumSourceSearchPort == _D4_INPUT_PORT) && (ScalerTMDSRx3GetDualDVIMode() == _FALSE) &&
               ((usVHeight == 240) || (usVHeight == 288) || (usVHeight == 384) || (usVHeight == 517) || (usVHeight == 518) || (usVHeight == 540)))
            {
                return _TRUE;
            }
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
            if((enumSourceSearchPort == _D5_INPUT_PORT) && (ScalerTMDSRx4GetDualDVIMode() == _FALSE) &&
               ((usVHeight == 240) || (usVHeight == 288) || (usVHeight == 384) || (usVHeight == 517) || (usVHeight == 518) || (usVHeight == 540)))
            {
                return _TRUE;
            }
#endif
        }
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : Invert duali phy-to-MAC 1x clock
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncDualDVIClockInvert(EnumSourceSearchPort enumSourceSearchPort)
{
    enumSourceSearchPort = enumSourceSearchPort;

    switch(ScalerGetBit(P31_03_FC_DUAL_DVI_CTRL1, (_BIT7 | _BIT6 | _BIT5)))
    {
#if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)
        case (_BIT7):                 // D2 dual DVI
            ScalerSetBit(P71_A6_TMDS_OUTCTL, ~_BIT2, (~ScalerGetBit(P71_A6_TMDS_OUTCTL, _BIT2) & _BIT2));
            ScalerSetBit(P72_A6_TMDS_OUTCTL, ~_BIT2, (~ScalerGetBit(P72_A6_TMDS_OUTCTL, _BIT2) & _BIT2));
            break;
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT)
        case (_BIT7 | _BIT5):         // D3 dual DVI
            ScalerSetBit(P72_A6_TMDS_OUTCTL, ~_BIT2, (~ScalerGetBit(P72_A6_TMDS_OUTCTL, _BIT2) & _BIT2));
            ScalerSetBit(P73_A6_TMDS_OUTCTL, ~_BIT2, (~ScalerGetBit(P73_A6_TMDS_OUTCTL, _BIT2) & _BIT2));
            break;
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
        case (_BIT7 | _BIT6):         // D4 dual DVI
            ScalerSetBit(P73_A6_TMDS_OUTCTL, ~_BIT2, (~ScalerGetBit(P73_A6_TMDS_OUTCTL, _BIT2) & _BIT2));
            ScalerSetBit(P74_A6_TMDS_OUTCTL, ~_BIT2, (~ScalerGetBit(P74_A6_TMDS_OUTCTL, _BIT2) & _BIT2));
            break;
#endif

#if((_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT) ||\
    (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
        case (_BIT7 | _BIT6 | _BIT5):
            switch(enumSourceSearchPort)
            {
                case _D2_INPUT_PORT:    // D2 dual DVI
                    ScalerSetBit(P71_A6_TMDS_OUTCTL, ~_BIT2, (~ScalerGetBit(P71_A6_TMDS_OUTCTL, _BIT2) & _BIT2));
                    ScalerSetBit(P72_A6_TMDS_OUTCTL, ~_BIT2, (~ScalerGetBit(P72_A6_TMDS_OUTCTL, _BIT2) & _BIT2));
                    break;

                case _D4_INPUT_PORT:    // D4 dual DVI
                    ScalerSetBit(P73_A6_TMDS_OUTCTL, ~_BIT2, (~ScalerGetBit(P73_A6_TMDS_OUTCTL, _BIT2) & _BIT2));
                    ScalerSetBit(P74_A6_TMDS_OUTCTL, ~_BIT2, (~ScalerGetBit(P74_A6_TMDS_OUTCTL, _BIT2) & _BIT2));
                    break;

                default:
                    break;
            }
            break;
#endif

        default:
            return;
    }
}
#endif // End of #if(_DUAL_DVI_SUPPORT == _ON)

#endif // End of #if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))

#if(_MHL_SUPPORT == _ON)
//--------------------------------------------------
// Description  : MHL VBus Power Exist
// Input Value  : None
// Output Value : _TRUE : VBUS Power Exist
//--------------------------------------------------
bit ScalerSyncMHLVBusPowerExist(void)
{
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
    if(PCB_GET_D0_MHL_VBUS_SWITCH() == _MHL_VBUS_ON)
    {
        return _TRUE;
    }
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
    if(PCB_GET_D1_MHL_VBUS_SWITCH() == _MHL_VBUS_ON)
    {
        return _TRUE;
    }
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
    if(PCB_GET_D2_MHL_VBUS_SWITCH() == _MHL_VBUS_ON)
    {
        return _TRUE;
    }
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
    if(PCB_GET_D3_MHL_VBUS_SWITCH() == _MHL_VBUS_ON)
    {
        return _TRUE;
    }
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
    if(PCB_GET_D4_MHL_VBUS_SWITCH() == _MHL_VBUS_ON)
    {
        return _TRUE;
    }
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
    if(PCB_GET_D5_MHL_VBUS_SWITCH() == _MHL_VBUS_ON)
    {
        return _TRUE;
    }
#endif

    return _FALSE;
}
#endif

//--------------------------------------------------
// Description  : Process Required to be Performed for Active State
// Input Value  : Current Source Type
// Output Value : None
//--------------------------------------------------
void ScalerSyncActiveProc(BYTE ucSourceType)
{
    switch(ucSourceType)
    {
#if(_VGA_SUPPORT == _ON)
        case _SOURCE_VGA:

            break;
#endif

#if(_DVI_SUPPORT == _ON)
        case _SOURCE_DVI:
            break;
#endif

#if(_HDMI_SUPPORT == _ON)
        case _SOURCE_HDMI:
#if(_D0_HDMI_SUPPORT == _ON)
            if(GET_DIGITAL_PORT_SWITCH_TO_D0() == _TRUE)
            {
                ScalerTMDSRx0HdmiAVMuteProc();
            }
#endif

#if(_D1_HDMI_SUPPORT == _ON)
            if(GET_DIGITAL_PORT_SWITCH_TO_D1() == _TRUE)
            {
                ScalerTMDSRx1HdmiAVMuteProc();
            }
#endif

#if(_D2_HDMI_SUPPORT == _ON)
            if(GET_DIGITAL_PORT_SWITCH_TO_D2() == _TRUE)
            {
                ScalerTMDSRx2HdmiAVMuteProc();
            }
#endif

#if(_D3_HDMI_SUPPORT == _ON)
            if(GET_DIGITAL_PORT_SWITCH_TO_D3() == _TRUE)
            {
                ScalerTMDSRx3HdmiAVMuteProc();
            }
#endif

#if(_D4_HDMI_SUPPORT == _ON)
            if(GET_DIGITAL_PORT_SWITCH_TO_D4() == _TRUE)
            {
                ScalerTMDSRx4HdmiAVMuteProc();
            }
#endif

#if(_D5_HDMI_SUPPORT == _ON)
            if(GET_DIGITAL_PORT_SWITCH_TO_D5() == _TRUE)
            {
                ScalerTMDSRx5HdmiAVMuteProc();
            }
#endif

            break;
#endif

#if(_DP_SUPPORT == _ON)
        case _SOURCE_DP:

            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Sync reset Process for Mode Reset
// Input Value  : ucInputPort       --> Input Port
// Output Value : None
//--------------------------------------------------
void ScalerSyncResetProc(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_A0_INPUT_PORT_TYPE == _A0_VGA_PORT)
        case _A0_INPUT_PORT:
            break;
#endif

        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

            // Disable DP Fifo Under/OverFlow Watch Dog
            ScalerDpRx0SetFifoWD(_DISABLE);

            // Disable DP Fifo Under/OverFlow IRQ
            ScalerDpRx0SetFifoIRQ(_DISABLE);

#if(_ULTRA_HDR_SUPPORT == _ON)
            ScalerDpRx0SetInitialRSV0InfoType();

            memset(g_pucDPRx0HDRBackup, 0, sizeof(g_pucDPRx0HDRBackup));
            memset(g_pucDPRx0RSV0Backup, 0, sizeof(g_pucDPRx0RSV0Backup));
#endif

#if(_FREESYNC_SUPPORT == _ON)
            CLR_FREESYNC_ENABLED();
#endif

#endif

#if(_D0_TMDS_SUPPORT == _ON)
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX0_TMDS_VIDEO_DETECT);

#if(_D0_HDMI_SUPPORT == _ON)
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX0_TMDS_HDMI_PACKET_DETECT);
            ScalerTMDSRx0HdmiWatchDog((_HDMI_AVI_INFO_VARIATION_WD | _HDMI_AV_MUTE_WD), _DISABLE);
#if(_D0_HDMI_2_0_SUPPORT == _ON)
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX0_HDMI2_FORMAT_RESET_WAIT);
            ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_RX0_HDMI_RR_RETRY);
#endif // End of #if(_D0_HDMI_2_0_SUPPORT == _ON)
#endif // End of #if(_D0_HDMI_SUPPORT == _ON)
#endif // End of #if(_D0_TMDS_SUPPORT == _ON)

            break;

        case _D1_INPUT_PORT:

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

            // Disable DP Fifo Under/OverFlow Watch Dog
            ScalerDpRx1SetFifoWD(_DISABLE);

            // Disable DP Fifo Under/OverFlow IRQ
            ScalerDpRx1SetFifoIRQ(_DISABLE);

#if(_ULTRA_HDR_SUPPORT == _ON)
            ScalerDpRx1SetInitialRSV0InfoType();

            memset(g_pucDPRx1HDRBackup, 0, sizeof(g_pucDPRx1HDRBackup));
            memset(g_pucDPRx1RSV0Backup, 0, sizeof(g_pucDPRx1RSV0Backup));
#endif

#if(_FREESYNC_SUPPORT == _ON)
            CLR_FREESYNC_ENABLED();
#endif

#endif

#if(_D1_TMDS_SUPPORT == _ON)
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX1_TMDS_VIDEO_DETECT);

#if(_D1_HDMI_SUPPORT == _ON)
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX1_TMDS_HDMI_PACKET_DETECT);
            ScalerTMDSRx1HdmiWatchDog((_HDMI_AVI_INFO_VARIATION_WD | _HDMI_AV_MUTE_WD), _DISABLE);
#if(_D1_HDMI_2_0_SUPPORT == _ON)
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX1_HDMI2_FORMAT_RESET_WAIT);
            ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_RX1_HDMI_RR_RETRY);
#endif // End of #if(_D1_HDMI_2_0_SUPPORT == _ON)
#endif // End of #if(_D1_HDMI_SUPPORT == _ON)
#endif // End of #if(_D1_TMDS_SUPPORT == _ON)

            break;

        case _D2_INPUT_PORT:

#if(_D2_TMDS_SUPPORT == _ON)
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX2_TMDS_VIDEO_DETECT);

#if(_D2_HDMI_SUPPORT == _ON)
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX2_TMDS_HDMI_PACKET_DETECT);
            ScalerTMDSRx2HdmiWatchDog((_HDMI_AVI_INFO_VARIATION_WD | _HDMI_AV_MUTE_WD), _DISABLE);
#if(_D2_HDMI_2_0_SUPPORT == _ON)
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX2_HDMI2_FORMAT_RESET_WAIT);
            ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_RX2_HDMI_RR_RETRY);
#endif // End of #if(_D2_HDMI_2_0_SUPPORT == _ON)
#endif // End of #if(_D2_HDMI_SUPPORT == _ON)

#endif // End of #if(_D2_TMDS_SUPPORT == _ON)

            break;

        case _D3_INPUT_PORT:

#if(_D3_TMDS_SUPPORT == _ON)
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX3_TMDS_VIDEO_DETECT);

#if(_D3_HDMI_SUPPORT == _ON)
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX3_TMDS_HDMI_PACKET_DETECT);
            ScalerTMDSRx3HdmiWatchDog((_HDMI_AVI_INFO_VARIATION_WD | _HDMI_AV_MUTE_WD), _DISABLE);
#if(_D3_HDMI_2_0_SUPPORT == _ON)
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX3_HDMI2_FORMAT_RESET_WAIT);
            ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_RX3_HDMI_RR_RETRY);
#endif // End of #if(_D3_HDMI_2_0_SUPPORT == _ON)
#endif // End of #if(_D3_HDMI_SUPPORT == _ON)

#endif // End of #if(_D3_TMDS_SUPPORT == _ON)

            break;

        case _D4_INPUT_PORT:

#if(_D4_TMDS_SUPPORT == _ON)
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX4_TMDS_VIDEO_DETECT);

#if(_D4_HDMI_SUPPORT == _ON)
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX4_TMDS_HDMI_PACKET_DETECT);
            ScalerTMDSRx4HdmiWatchDog((_HDMI_AVI_INFO_VARIATION_WD | _HDMI_AV_MUTE_WD), _DISABLE);
#if(_D4_HDMI_2_0_SUPPORT == _ON)
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX4_HDMI2_FORMAT_RESET_WAIT);
            ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_RX4_HDMI_RR_RETRY);
#endif // End of #if(_D4_HDMI_2_0_SUPPORT == _ON)
#endif // End of #if(_D4_HDMI_SUPPORT == _ON)

#endif // End of #if(_D4_TMDS_SUPPORT == _ON)

            break;

        case _D5_INPUT_PORT:

#if(_D5_TMDS_SUPPORT == _ON)
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX5_TMDS_VIDEO_DETECT);

#if(_D5_HDMI_SUPPORT == _ON)
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX5_TMDS_HDMI_PACKET_DETECT);
            ScalerTMDSRx5HdmiWatchDog((_HDMI_AVI_INFO_VARIATION_WD | _HDMI_AV_MUTE_WD), _DISABLE);
#if(_D5_HDMI_2_0_SUPPORT == _ON)
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX5_HDMI2_FORMAT_RESET_WAIT);
            ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_RX5_HDMI_RR_RETRY);
#endif // End of #if(_D5_HDMI_2_0_SUPPORT == _ON)
#endif // End of #if(_D5_HDMI_SUPPORT == _ON)
#endif // End of #if(_D5_TMDS_SUPPORT == _ON)

            break;


#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
        case _D7_INPUT_PORT:

            // Disable DP Fifo Under/OverFlow Watch Dog
            ScalerDpRx0SetFifoWD(_DISABLE);

            // Disable DP Fifo Under/OverFlow IRQ
            ScalerDpRx0SetFifoIRQ(_DISABLE);

            // Disable DP Fifo Under/OverFlow Watch Dog
            ScalerDpRx1SetFifoWD(_DISABLE);

            // Disable DP Fifo Under/OverFlow IRQ
            ScalerDpRx1SetFifoIRQ(_DISABLE);

#if(_FREESYNC_SUPPORT == _ON)
            CLR_FREESYNC_ENABLED();
#endif

            break;

#endif

        default:
            break;
    }

#if(_DP_TX_SUPPORT == _ON)
    if(ScalerDpTxCloneGetCurrentInputPort() == ucInputPort)
    {
        if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_CLONE)
        {
            ScalerDpTxSetStreamSource(_DP_TX_SOURCE_NONE);
        }
        else if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_NONE) // for Clone OOR Case
        {
            DebugMessageMst("Dp TX Clone: Clear Exceed BW", 0);

            // Clear Exceed BW Flag for Clone Mode
            CLR_DP_TX_EXCEED_LINK_BANDWIDTH();
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Sync reset all port rocess for Mode Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncResetAllProc(void)
{
    BYTE ucPort = 0;

    for(ucPort = _A0_INPUT_PORT; ucPort < _NO_INPUT_PORT; ++ucPort)
    {
        ScalerSyncResetProc(ucPort);

        if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
        {
            CLR_DIGITAL_COLORIMETRY_CHANGED(ucPort);
            CLR_DIGITAL_COLORIMETRY_EXT_CHANGED(ucPort);
            CLR_DIGITAL_QUANTIZATION_CHANGED(ucPort);
        }
    }
}

//--------------------------------------------------
// Description  : Power Process for Interface
// Input Value  : Power Action
// Output Value : None
//--------------------------------------------------
void ScalerSyncPowerProc(EnumPowerAction enumPowerAction)
{
    switch(enumPowerAction)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:

            // ADC Bandgap Enable
            ScalerADCBandgap(_ON);

            // GDI Bandgap Enable
            ScalerGDIPhyBandgap(_ON);

#if(_DP_SUPPORT == _ON)
            ScalerDpPowerSwitch(enumPowerAction);
#endif

#if(_FREESYNC_SUPPORT == _ON)
            ScalerSyncFREESYNCTestPinEnable();
#endif

            if(enumPowerAction == _POWER_ACTION_PS_TO_NORMAL)
            {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
                ScalerGDIPhyRx0PowerProc(enumPowerAction);
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
                ScalerGDIPhyRx1PowerProc(enumPowerAction);
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
                ScalerGDIPhyRx2PowerProc(enumPowerAction);
#endif

#if((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
                ScalerGDIPhyRx3PowerProc(enumPowerAction);
#endif

#if((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
                ScalerGDIPhyRx4PowerProc(enumPowerAction);
#endif

#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
                ScalerGDIPhyRx5PowerProc(enumPowerAction);
#endif
            }

#if(_URGENT_EVENT_CHECK_MODE == _ON)
            // Clear Urgent Event Occured Flag When System Flow Is Runing to Normal
            ScalerSyncClrUrgentEventFlg();
#endif

            break;

        case _POWER_ACTION_NORMAL_TO_PS:
        case _POWER_ACTION_NOSUPPORT_PS_TO_PS:

            // Power down ADC/APLL
            ScalerSyncAdcApllPowerDown();

            // ADC Bandgap Disable
            ScalerADCBandgap(_OFF);

#if(_DP_SUPPORT == _ON)
            ScalerDpPowerSwitch(enumPowerAction);
#else
            ScalerGDIPhyBandgap(_OFF);
#endif

#if(_DP_TX_SUPPORT == _ON)
            ScalerSyncDpTxPowerProc(enumPowerAction);
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
            ScalerGDIPhyRx0PowerProc(enumPowerAction);
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
            ScalerGDIPhyRx1PowerProc(enumPowerAction);
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
            ScalerGDIPhyRx2PowerProc(enumPowerAction);
#endif

#if((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
            ScalerGDIPhyRx3PowerProc(enumPowerAction);
#endif

#if((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
            ScalerGDIPhyRx4PowerProc(enumPowerAction);
#endif

#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
            ScalerGDIPhyRx5PowerProc(enumPowerAction);
#endif
            // Schmitt trigger setting old mode in power saving.
            ScalerSetByte(P0_F4_HS_SCHMITT_TRIGGE_CTRL, 0xC2);

            // Disable Sync proc clock
            ScalerSetBit(P0_47_SYNC_SELECT, ~_BIT7, _BIT7);

            break;

        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_NOSUPPORT_PS_TO_OFF:
        case _POWER_ACTION_FAKE_PS_TO_OFF:
        case _POWER_ACTION_PS_TO_OFF:

            // Power down ADC/APLL
            ScalerSyncAdcApllPowerDown();

            // ADC Bandgap Disable
            ScalerADCBandgap(_OFF);

#if(_MHL_SUPPORT == _ON)
            if(enumPowerAction == _POWER_ACTION_AC_ON_TO_OFF)
            {
                ScalerGDIPhyBandgap(_ON);
            }
#endif

#if(_DP_SUPPORT == _ON)
            ScalerDpPowerSwitch(enumPowerAction);
#else
            ScalerGDIPhyBandgap(_OFF);
#endif

#if(_DP_TX_SUPPORT == _ON)
            ScalerSyncDpTxPowerProc(enumPowerAction);
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
            ScalerGDIPhyRx0PowerProc(enumPowerAction);
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
            ScalerGDIPhyRx1PowerProc(enumPowerAction);
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
            ScalerGDIPhyRx2PowerProc(enumPowerAction);
#endif

#if((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
            ScalerGDIPhyRx3PowerProc(enumPowerAction);
#endif

#if((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
            ScalerGDIPhyRx4PowerProc(enumPowerAction);
#endif

#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
            ScalerGDIPhyRx5PowerProc(enumPowerAction);
#endif

#if((_DP_SUPPORT != _ON) && (_MHL_SUPPORT != _ON))
            EX0 = 0;
#endif

#if(_VGA_SUPPORT == _ON)
            // Disable sync pulse detect
            ScalerSyncProcPulseDetectEnable(_DISABLE);
#endif
            // Schmitt trigger setting old mode in power saving.
            ScalerSetByte(P0_F4_HS_SCHMITT_TRIGGE_CTRL, 0x42);

            // Disable Sync proc clock
            ScalerSetBit(P0_47_SYNC_SELECT, ~_BIT7, _BIT7);

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Power Down VGA Function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncAdcApllPowerDown(void)
{
    // Power down APLL
    ScalerSetBit(P1_AF_PLL_WD, ~_BIT0, _BIT0);

    // Power down APLL by Misc Control
    ScalerSetBit(P1_F2_APLL_MISC, ~_BIT7, _BIT7);

    // Power down ADC VCM/ADC clock/SOG Power/RGB Channel
    ScalerSetBit(P0_C6_ADC_POWER, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2 | _BIT1 | _BIT0), 0x00);
}

//--------------------------------------------------
// Description  : Force nack DDC channel
// Input Value  : bSelect --> _ON: force nack
// Output Value : NONE
//--------------------------------------------------
void ScalerSyncSetDdcForceNack(BYTE ucInputPort, bit bSelect)
{
    if(bSelect == _ON)
    {
        switch(ucInputPort)
        {
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
            case _A0_INPUT_PORT:

                // A0 DDC force Nack
                MCU_FFE7_VGA_EDID_IRQ |= _BIT5;

                break;
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
            case _D0_INPUT_PORT:

#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
                if(GET_D0_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
                {
                    // DDC0 force nack
                    MCU_FFE4_DDC0_EDID_IRQ |= _BIT5;
                }
                break;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
            case _D1_INPUT_PORT:

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
                if(GET_D1_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
                {
                    // DDC1 force nack
                    MCU_FFE5_DDC1_EDID_IRQ |= _BIT5;
                }
                break;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
            case _D2_INPUT_PORT:

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
                if(GET_D2_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
                {
                    // DDC2 force nack
                    MCU_FE69_DDC2_EDID_IRQ |= _BIT5;
                }
                break;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
            case _D3_INPUT_PORT:

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
                if(GET_D3_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
                {
                    // DDC3 force nack
                    MCU_FE72_DDC3_EDID_IRQ |= _BIT5;
                }

                break;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
            case _D4_INPUT_PORT:

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
                if(GET_D4_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
                {
                    // DDC4 force nack
                    MCU_FE7B_DDC4_EDID_IRQ |= _BIT5;
                }

                break;
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
            case _D5_INPUT_PORT:

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
                if(GET_D5_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
                {
                    // DDC5 force nack
                    MCU_FE84_DDC5_EDID_IRQ |= _BIT5;
                }

                break;
#endif
            default:

                break;
        }
    }
    else
    {
        switch(ucInputPort)
        {
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
            case _A0_INPUT_PORT:

                // A0 DDC nack off
                MCU_FFE7_VGA_EDID_IRQ &= ~_BIT5;
                break;
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
            case _D0_INPUT_PORT:

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

                // Disable DDC0 Force Nack
                MCU_FFE4_DDC0_EDID_IRQ &= ~_BIT5;

                // Enable Segment Control
                MCU_FF20_DDC0_DDC_CONTROL_2 |= _BIT2;

#elif(_D0_TMDS_SUPPORT == _ON)

#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
                if(GET_D0_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
                {
                    // DDC0 nack off
                    MCU_FFE4_DDC0_EDID_IRQ &= ~_BIT5;
                }
#endif
                break;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
            case _D1_INPUT_PORT:

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

                // Disable DDC1 Force Nack
                MCU_FFE5_DDC1_EDID_IRQ &= ~_BIT5;

                // Disable Segment Control for Link Layer CTS
                MCU_FF2E_DDC1_DDC_CONTROL_2 |= _BIT2;

#elif(_D1_TMDS_SUPPORT == _ON)

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
                if(GET_D1_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
                {
                    // DDC1 nack off
                    MCU_FFE5_DDC1_EDID_IRQ &= ~_BIT5;
                }
#endif
                break;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
            case _D2_INPUT_PORT:

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
                if(GET_D2_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
                {
                    // DDC2 nack off
                    MCU_FE69_DDC2_EDID_IRQ &= ~_BIT5;
                }

                break;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
            case _D3_INPUT_PORT:

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
                if(GET_D3_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
                {
                    // DDC3 nack off
                    MCU_FE72_DDC3_EDID_IRQ &= ~_BIT5;
                }

                break;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
            case _D4_INPUT_PORT:

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
                if(GET_D4_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
                {
                    // DDC4 nack off
                    MCU_FE7B_DDC4_EDID_IRQ &= ~_BIT5;
                }

                break;
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
            case _D5_INPUT_PORT:

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
                if(GET_D5_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
                {
                    // DDC5 nack off
                    MCU_FE84_DDC5_EDID_IRQ &= ~_BIT5;
                }

                break;
#endif
            default:

                break;
        }
    }
}

//--------------------------------------------------
// Description  : Force nack DDC channel
// Input Value  : ucInputPort
// Output Value : _TRUE --> Force Nack State
//--------------------------------------------------
bit ScalerSyncGetDdcForceNackStatus(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
        case _A0_INPUT_PORT:
#if(_HW_PC99_VGADDC2_SUPPORT == _ON)
            if((((MCU_FFE7_VGA_EDID_IRQ & _BIT5) == _BIT5) && ((MCU_FD37_ADC_DDC2_EDID_IRQ & _BIT5) == _BIT5)) == _TRUE)
            {
                return _TRUE;
            }
#else
            if((MCU_FFE7_VGA_EDID_IRQ & _BIT5) == _BIT5)
            {
                return _TRUE;
            }
#endif
            break;
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:

#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
            if(GET_D0_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
            {
                // DDC0 force nack
#if(_D0_DDC_CHANNEL_SEL == _DDC0)
                if((MCU_FFE4_DDC0_EDID_IRQ & _BIT5) == _BIT5)
                {
                    return _TRUE;
                }
#elif(_D0_DDC_CHANNEL_SEL == _DDC1)
                if((MCU_FFE5_DDC1_EDID_IRQ & _BIT5) == _BIT5)
                {
                    return _TRUE;
                }
#elif(_D0_DDC_CHANNEL_SEL == _DDC2)
                if((MCU_FE69_DDC2_EDID_IRQ & _BIT5) == _BIT5)
                {
                    return _TRUE;
                }
#endif
            }
            break;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
            if(GET_D1_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
            {
                // DDC1 force nack
#if(_D1_DDC_CHANNEL_SEL == _DDC0)
                if((MCU_FFE4_DDC0_EDID_IRQ & _BIT5) == _BIT5)
                {
                    return _TRUE;
                }
#elif(_D1_DDC_CHANNEL_SEL == _DDC1)
                if((MCU_FFE5_DDC1_EDID_IRQ & _BIT5) == _BIT5)
                {
                    return _TRUE;
                }
#elif(_D1_DDC_CHANNEL_SEL == _DDC2)
                if((MCU_FE69_DDC2_EDID_IRQ & _BIT5) == _BIT5)
                {
                    return _TRUE;
                }
#endif
            }
            break;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
            if(GET_D2_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
            {
                // DDC2 force nack
#if(_D2_DDC_CHANNEL_SEL == _DDC0)
                if((MCU_FFE4_DDC0_EDID_IRQ & _BIT5) == _BIT5)
                {
                    return _TRUE;
                }
#elif(_D2_DDC_CHANNEL_SEL == _DDC1)
                if((MCU_FFE5_DDC1_EDID_IRQ & _BIT5) == _BIT5)
                {
                    return _TRUE;
                }
#elif(_D2_DDC_CHANNEL_SEL == _DDC2)
                if((MCU_FE69_DDC2_EDID_IRQ & _BIT5) == _BIT5)
                {
                    return _TRUE;
                }
#endif
            }
            break;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        case _D3_INPUT_PORT:

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
            if(GET_D3_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
            {
                if((MCU_FE72_DDC3_EDID_IRQ & _BIT5) == _BIT5)
                {
                    return _TRUE;
                }
            }
            break;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        case _D4_INPUT_PORT:

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
            if(GET_D4_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
            {
                if((MCU_FE7B_DDC4_EDID_IRQ & _BIT5) == _BIT5)
                {
                    return _TRUE;
                }
            }
            break;
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
        case _D5_INPUT_PORT:

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
            if(GET_D5_TMDS_MODE() == _TMDS_HDMI_MODE)
#endif
            {
                if((MCU_FE84_DDC5_EDID_IRQ & _BIT5) == _BIT5)
                {
                    return _TRUE;
                }
            }
            break;
#endif

        default:
            break;
    }

    return _FALSE;
}

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
//--------------------------------------------------
// Description  : GDI Rx0 Interface Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncInterfaceRx0Proc(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
#if((_D0_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT))
        if(GET_DIGITAL_PORT_SWITCH_TO_D0() == _FALSE)
        {
            SET_TMDS_RX0_HPD_TRIGGER_EVENT(_TMDS_HPD_ACER);
            ScalerTMDSRx0HotPlugEvent();
        }
#endif
        if(GET_TMDS_RX0_TOGGLE_Z0_EVENT() == _TRUE)
        {
            SET_TMDS_RX0_HPD_TRIGGER_EVENT(_TMDS_HPD_ACER);
            ScalerTMDSRx0HotPlugEvent();
        }

#else // Else of #if((_D0_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT))
        if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_DIGITAL_PORT_SWITCH_TO_D0() == _FALSE))
        {
            SET_TMDS_RX0_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);
            ScalerTMDSRx0HotPlugEvent();
        }
#endif

#endif // End of #if((_D0_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

        if(GET_DIGITAL_PORT_SWITCH_TO_D0() == _FALSE)
        {
            ScalerGDIPhyRx0PowerProc(_POWER_ACTION_OFF_TO_NORMAL);
        }
    }
    else
    {
        if(GET_DIGITAL_PORT_SWITCH_TO_D0() == _TRUE)
        {
            ScalerGDIPhyRx0PowerProc(_POWER_ACTION_NORMAL_TO_OFF);
        }
    }
}
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
//--------------------------------------------------
// Description  : GDI Rx0 Interface Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncInterfaceRx1Proc(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
#if((_D1_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
        if(GET_DIGITAL_PORT_SWITCH_TO_D1() == _FALSE)
        {
            SET_TMDS_RX1_HPD_TRIGGER_EVENT(_TMDS_HPD_ACER);
            ScalerTMDSRx1HotPlugEvent();
        }
#endif
        if(GET_TMDS_RX1_TOGGLE_Z0_EVENT() == _TRUE)
        {
            SET_TMDS_RX1_HPD_TRIGGER_EVENT(_TMDS_HPD_ACER);
            ScalerTMDSRx1HotPlugEvent();
        }

#else // Else of #if((_D1_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
        if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_DIGITAL_PORT_SWITCH_TO_D1() == _FALSE))
        {
            SET_TMDS_RX1_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);
            ScalerTMDSRx1HotPlugEvent();
        }
#endif

#endif // End of #if((_D1_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

        if(GET_DIGITAL_PORT_SWITCH_TO_D1() == _FALSE)
        {
            ScalerGDIPhyRx1PowerProc(_POWER_ACTION_OFF_TO_NORMAL);
        }
    }
    else
    {
        if(GET_DIGITAL_PORT_SWITCH_TO_D1() == _TRUE)
        {
            ScalerGDIPhyRx1PowerProc(_POWER_ACTION_NORMAL_TO_OFF);
        }
    }
}
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
//--------------------------------------------------
// Description  : GDI Rx0 Interface Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncInterfaceRx2Proc(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
#if((_D2_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
        if(GET_DIGITAL_PORT_SWITCH_TO_D2() == _FALSE)
        {
            SET_TMDS_RX2_HPD_TRIGGER_EVENT(_TMDS_HPD_ACER);
            ScalerTMDSRx2HotPlugEvent();
        }
#endif
        if(GET_TMDS_RX2_TOGGLE_Z0_EVENT() == _TRUE)
        {
            SET_TMDS_RX2_HPD_TRIGGER_EVENT(_TMDS_HPD_ACER);
            ScalerTMDSRx2HotPlugEvent();
        }

#else // Else of #if((_D2_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
        if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_DIGITAL_PORT_SWITCH_TO_D2() == _FALSE))
        {
            SET_TMDS_RX2_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);
            ScalerTMDSRx2HotPlugEvent();
        }
#endif

#endif // End of #if((_D2_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

        if(GET_DIGITAL_PORT_SWITCH_TO_D2() == _FALSE)
        {
            ScalerGDIPhyRx2PowerProc(_POWER_ACTION_OFF_TO_NORMAL);
        }
    }
    else
    {
        if(GET_DIGITAL_PORT_SWITCH_TO_D2() == _TRUE)
        {
            ScalerGDIPhyRx2PowerProc(_POWER_ACTION_NORMAL_TO_OFF);
        }
    }
}
#endif

#if((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
//--------------------------------------------------
// Description  : GDI Rx0 Interface Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncInterfaceRx3Proc(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
#if((_D3_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT))
        if(GET_DIGITAL_PORT_SWITCH_TO_D3() == _FALSE)
        {
            SET_TMDS_RX3_HPD_TRIGGER_EVENT(_TMDS_HPD_ACER);
            ScalerTMDSRx3HotPlugEvent();
        }
#endif
        if(GET_TMDS_RX3_TOGGLE_Z0_EVENT() == _TRUE)
        {
            SET_TMDS_RX3_HPD_TRIGGER_EVENT(_TMDS_HPD_ACER);
            ScalerTMDSRx3HotPlugEvent();
        }

#else // Else of #if((_D3_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT))
        if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_DIGITAL_PORT_SWITCH_TO_D3() == _FALSE))
        {
            SET_TMDS_RX3_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);
            ScalerTMDSRx3HotPlugEvent();
        }
#endif

#endif // End of #if((_D3_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

        if(GET_DIGITAL_PORT_SWITCH_TO_D3() == _FALSE)
        {
            ScalerGDIPhyRx3PowerProc(_POWER_ACTION_OFF_TO_NORMAL);
        }
    }
    else
    {
        if(GET_DIGITAL_PORT_SWITCH_TO_D3() == _TRUE)
        {
            ScalerGDIPhyRx3PowerProc(_POWER_ACTION_NORMAL_TO_OFF);
        }
    }
}
#endif

#if((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
//--------------------------------------------------
// Description  : GDI Rx0 Interface Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncInterfaceRx4Proc(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
#if((_D4_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if((_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT))
        if(GET_DIGITAL_PORT_SWITCH_TO_D4() == _FALSE)
        {
            SET_TMDS_RX4_HPD_TRIGGER_EVENT(_TMDS_HPD_ACER);
            ScalerTMDSRx4HotPlugEvent();
        }
#endif
        if(GET_TMDS_RX4_TOGGLE_Z0_EVENT() == _TRUE)
        {
            SET_TMDS_RX4_HPD_TRIGGER_EVENT(_TMDS_HPD_ACER);
            ScalerTMDSRx4HotPlugEvent();
        }

#else // Else of #if((_D4_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if((_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT))
        if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_DIGITAL_PORT_SWITCH_TO_D4() == _FALSE))
        {
            SET_TMDS_RX4_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);
            ScalerTMDSRx4HotPlugEvent();
        }
#endif

#endif // End of #if((_D4_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

        if(GET_DIGITAL_PORT_SWITCH_TO_D4() == _FALSE)
        {
            ScalerGDIPhyRx4PowerProc(_POWER_ACTION_OFF_TO_NORMAL);
        }
    }
    else
    {
        if(GET_DIGITAL_PORT_SWITCH_TO_D4() == _TRUE)
        {
            ScalerGDIPhyRx4PowerProc(_POWER_ACTION_NORMAL_TO_OFF);
        }
    }
}
#endif

#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
//--------------------------------------------------
// Description  : GDI Rx0 Interface Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncInterfaceRx5Proc(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
#if((_D5_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if((_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT))
        if(GET_DIGITAL_PORT_SWITCH_TO_D5() == _FALSE)
        {
            SET_TMDS_RX5_HPD_TRIGGER_EVENT(_TMDS_HPD_ACER);
            ScalerTMDSRx5HotPlugEvent();
        }
#endif
        if(GET_TMDS_RX5_TOGGLE_Z0_EVENT() == _TRUE)
        {
            SET_TMDS_RX5_HPD_TRIGGER_EVENT(_TMDS_HPD_ACER);
            ScalerTMDSRx5HotPlugEvent();
        }

#else // Else of #if((_D5_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

#if((_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT))
        if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_DIGITAL_PORT_SWITCH_TO_D5() == _FALSE))
        {
            SET_TMDS_RX5_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);
            ScalerTMDSRx5HotPlugEvent();
        }
#endif

#endif // End of #if((_D5_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))

        if(GET_DIGITAL_PORT_SWITCH_TO_D5() == _FALSE)
        {
            ScalerGDIPhyRx5PowerProc(_POWER_ACTION_OFF_TO_NORMAL);
        }
    }
    else
    {
        if(GET_DIGITAL_PORT_SWITCH_TO_D5() == _TRUE)
        {
            ScalerGDIPhyRx5PowerProc(_POWER_ACTION_NORMAL_TO_OFF);
        }
    }
}
#endif

#if(_D0_HDMI_EXIST == _ON)
//--------------------------------------------------
// Description  : TMDS Rx0 Video Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx0HdmiVideoSetting(void)
{
    if(GET_HDMI_RX0_AVI_INFO_FRAME_RECEIVED() == _TRUE)
    {
        // Color Space Auto/ Pixel Repetition auto mode
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_51_PORT_PAGE2_HDMI_ACRCR, ~(_BIT6 | _BIT2), (_BIT6 | _BIT2));

        pData[0] = ScalerTMDSRx0HdmiGetAVIInfo(_AVI_INFO_COLOR_SPACE);

        // Get Color Space
        if(pData[0] == _AVI_COLOR_SPACE_00)
        {
            // Color Space RGB
            DebugMessageRx0("Get Color Space RGB", pData[0]);
            SET_COLOR_SPACE(_D0_INPUT_PORT, _COLOR_SPACE_RGB);
        }
        else if(pData[0] == _AVI_COLOR_SPACE_01)
        {
            // YCC422
            DebugMessageRx0("Get Color Space YUV422", pData[0]);
            SET_COLOR_SPACE(_D0_INPUT_PORT, _COLOR_SPACE_YCBCR422);
        }
        else if(pData[0] == _AVI_COLOR_SPACE_11)
        {
            // YCC420
            DebugMessageRx0("Get Color Space YUV420", pData[0]);
            SET_COLOR_SPACE(_D0_INPUT_PORT, _COLOR_SPACE_YCBCR420);
        }
        else
        {
            // YCC444
            DebugMessageRx0("Get Color Space YUV444", pData[0]);
            SET_COLOR_SPACE(_D0_INPUT_PORT, _COLOR_SPACE_YCBCR444);
        }

        // Set Pixel Repetition
        switch(ScalerTMDSRx0HdmiGetAVIInfo(_AVI_INFO_PIXEL_REPETITION))
        {
            case _AVI_PIXEL_REPETITION_0:

                DebugMessageRx0("Get Pixel Repetition 0", 0x00);
                SET_TMDS_RX0_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

                break;

            case _AVI_PIXEL_REPETITION_1:

                DebugMessageRx0("Get Pixel Repetition 1", 0x00);
                SET_TMDS_RX0_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_1);

                break;

            case _AVI_PIXEL_REPETITION_2:

                DebugMessageRx0("Get Pixel Repetition 2", 0x00);
                SET_TMDS_RX0_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_2);

                break;

            case _AVI_PIXEL_REPETITION_3:

                DebugMessageRx0("Get Pixel Repetition 3", 0x00);
                SET_TMDS_RX0_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_3);

                break;

            case _AVI_PIXEL_REPETITION_4:

                DebugMessageRx0("Get Pixel Repetition 4", 0x00);
                SET_TMDS_RX0_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_4);

                break;

            case _AVI_PIXEL_REPETITION_5:

                DebugMessageRx0("Get Pixel Repetition 5", 0x00);
                SET_TMDS_RX0_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_5);

                break;

            default:

                DebugMessageRx0("Get Pixel Repetition Error", 0x00);
                SET_TMDS_RX0_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

                break;
        }

        // Set Colorimetry
        ScalerSyncTMDSRx0HdmiColorimetrySetting();

        // Set Quantization
#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) || (_YCC_QUANTIZATION_RANGE_SUPPORT == _ON))
        ScalerSyncTMDSRx0HdmiQuantizationSetting();
#endif
    }
    else    // No Info Frame Received
    {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
        if(GET_TMDS_RX0_CLK_MODE() == _TMDS_MHL_PPMODE_PHY_SETTING)
        {
            SET_COLOR_SPACE(_D0_INPUT_PORT, _COLOR_SPACE_YCBCR422);
            SET_COLOR_YCC_QUANTIZATION_RANGE(_D0_INPUT_PORT, _YCC_QUANTIZATION_LIMIT_RANGE);

            // Manual Set Color Space to YCbCr422 and disable pixel repetition
            ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_51_PORT_PAGE2_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT3);
        }
        else
#endif

        {
            SET_COLOR_SPACE(_D0_INPUT_PORT, _COLOR_SPACE_RGB);
            SET_COLOR_RGB_QUANTIZATION_RANGE(_D0_INPUT_PORT, _RGB_QUANTIZATION_RESERVED);

            // Manual Set Color Space to RGB and disable pixel repetition
            ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_51_PORT_PAGE2_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);
        }

        // Disable down sampling
        ScalerSetDataPortBit(P2_C9_HDMI_AP, _P2_CA_PT_50_PORT_PAGE2_HDMI_VCR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        SET_TMDS_RX0_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

        // Waiting for down sampling  effect
        ScalerTimerDelayXms(20);
    }

    ScalerTMDSRx0SetPorchColor(GET_COLOR_SPACE(_D0_INPUT_PORT));
}

//--------------------------------------------------
// Description  : TMDS Rx0 Colorimetry Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx0HdmiColorimetrySetting(void)
{
    if((GET_COLOR_SPACE(_D0_INPUT_PORT) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(_D0_INPUT_PORT) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(_D0_INPUT_PORT) == _COLOR_SPACE_YCBCR444))
    {
        switch(ScalerTMDSRx0HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY))
        {
            case _AVI_COLORIMETRY_00:

                DebugMessageRx0("Get Colorimetry YCC_SMPTE_170M", 0x00);

                g_pstDigitalColorInfo[0].b4DigitalColorimetryPreValue = _AVI_COLORIMETRY_00;

                SET_COLORIMETRY(_D0_INPUT_PORT, _COLORIMETRY_YCC_SMPTE_170M);

                break;

            case _AVI_COLORIMETRY_01:

                DebugMessageRx0("Get Colorimetry YCC_SMPTE_170M", 0x00);

                g_pstDigitalColorInfo[0].b4DigitalColorimetryPreValue = _AVI_COLORIMETRY_01;

                SET_COLORIMETRY(_D0_INPUT_PORT, _COLORIMETRY_YCC_SMPTE_170M);

                break;

            case _AVI_COLORIMETRY_10:

                DebugMessageRx0("Get Colorimetry 709", 0x00);

                g_pstDigitalColorInfo[0].b4DigitalColorimetryPreValue = _AVI_COLORIMETRY_10;

                SET_COLORIMETRY(_D0_INPUT_PORT, _COLORIMETRY_YCC_ITUR_BT709);

                break;

            case _AVI_COLORIMETRY_11:

                DebugMessageRx0("Get Colorimetry Extended", 0x00);

                g_pstDigitalColorInfo[0].b4DigitalColorimetryPreValue = _AVI_COLORIMETRY_11;

                SET_COLORIMETRY(_D0_INPUT_PORT, _COLORIMETRY_EXT);

                ScalerSyncTMDSRx0HdmiColorimetryExtSetting();

                break;

            default:

                DebugMessageRx0("Get Colorimetry INTO_DEFAULT", 0x00);

                break;
        }
    }
    else if(GET_COLOR_SPACE(_D0_INPUT_PORT) == _COLOR_SPACE_RGB)
    {
        g_pstDigitalColorInfo[0].b4DigitalColorimetryPreValue = ScalerTMDSRx0HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY);

        switch(g_pstDigitalColorInfo[0].b4DigitalColorimetryPreValue)
        {
            case _AVI_COLORIMETRY_00:

                DebugMessageRx0("Get Colorimetry RGB_SRGB", 0x00);

                SET_COLORIMETRY(_D0_INPUT_PORT, _COLORIMETRY_RGB_SRGB);

                break;

            case _AVI_COLORIMETRY_11:

                DebugMessageRx0("Get Colorimetry Extended", 0x00);

                SET_COLORIMETRY(_D0_INPUT_PORT, _COLORIMETRY_EXT);

                ScalerSyncTMDSRx0HdmiColorimetryExtSetting();

                break;

            default:

                DebugMessageRx0("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_COLORIMETRY(_D0_INPUT_PORT, _COLORIMETRY_RGB_SRGB);

                break;
        }
    }
}

//--------------------------------------------------
// Description  : TMDS Rx0 Colorimetry Extended Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx0HdmiColorimetryExtSetting(void)
{
    if((GET_COLOR_SPACE(_D0_INPUT_PORT) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(_D0_INPUT_PORT) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(_D0_INPUT_PORT) == _COLOR_SPACE_YCBCR444))
    {
        // Get extended colorimetry
        g_pstDigitalColorInfo[0].b4DigitalColorimetryExtPreValue = ScalerTMDSRx0HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY);

        switch(g_pstDigitalColorInfo[0].b4DigitalColorimetryExtPreValue)
        {
            case _AVI_COLORIMETRY_EXT_000:

                DebugMessageRx0("Get Colorimetry EXT_YCC_XVYCC601", 0x00);

                SET_EXT_COLORIMETRY(_D0_INPUT_PORT, _COLORIMETRY_EXT_YCC_XVYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_001:

                DebugMessageRx0("Get Colorimetry EXT_YCC_XVYCC709", 0x00);

                SET_EXT_COLORIMETRY(_D0_INPUT_PORT, _COLORIMETRY_EXT_YCC_XVYCC709);

                break;

            case _AVI_COLORIMETRY_EXT_010:

                DebugMessageRx0("Get Colorimetry EXT_YCC_SYCC601", 0x00);

                SET_EXT_COLORIMETRY(_D0_INPUT_PORT, _COLORIMETRY_EXT_YCC_SYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_011:

                DebugMessageRx0("Get Colorimetry EXT_YCC_ADOBEYCC601", 0x00);

                SET_EXT_COLORIMETRY(_D0_INPUT_PORT, _COLORIMETRY_EXT_YCC_ADOBEYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_101:

                DebugMessageRx0("Get Colorimetry EXT_YCC_ITUR_BT2020_CL", 0x00);

                SET_EXT_COLORIMETRY(_D0_INPUT_PORT, _COLORIMETRY_EXT_YCC_ITUR_BT2020_CL);

                break;

            case _AVI_COLORIMETRY_EXT_110:

                DebugMessageRx0("Get Colorimetry EXT_YCC_ITUR_BT2020_NCL", 0x00);

                SET_EXT_COLORIMETRY(_D0_INPUT_PORT, _COLORIMETRY_EXT_YCC_ITUR_BT2020_NCL);

                break;

            default:

                DebugMessageRx0("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_EXT_COLORIMETRY(_D0_INPUT_PORT, _COLORIMETRY_EXT_RESERVED);

                break;
        }
    }
    else if(GET_COLOR_SPACE(_D0_INPUT_PORT) == _COLOR_SPACE_RGB)
    {
        g_pstDigitalColorInfo[0].b4DigitalColorimetryExtPreValue = ScalerTMDSRx0HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY);

        switch(g_pstDigitalColorInfo[0].b4DigitalColorimetryExtPreValue)
        {
            case _AVI_COLORIMETRY_EXT_100:

                DebugMessageRx0("Get Colorimetry EXT_RGB_ADOBERGB", 0x00);

                SET_EXT_COLORIMETRY(_D0_INPUT_PORT, _COLORIMETRY_EXT_RGB_ADOBERGB);

                break;

            case _AVI_COLORIMETRY_EXT_110:

                DebugMessageRx0("Get Colorimetry EXT_RGB_ITUR_BT2020", 0x00);

                SET_EXT_COLORIMETRY(_D0_INPUT_PORT, _COLORIMETRY_EXT_RGB_ITUR_BT2020);

                break;

            default:

                DebugMessageRx0("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_EXT_COLORIMETRY(_D0_INPUT_PORT, _COLORIMETRY_EXT_RESERVED);

                break;
        }
    }
}
#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) || (_YCC_QUANTIZATION_RANGE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : TMDS Rx0 Quantization Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx0HdmiQuantizationSetting(void)
{
    if((GET_COLOR_SPACE(_D0_INPUT_PORT) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(_D0_INPUT_PORT) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(_D0_INPUT_PORT) == _COLOR_SPACE_YCBCR444))
    {
        g_pstDigitalColorInfo[0].b2DigitalQuantizationPreValue = ScalerTMDSRx0HdmiGetAVIInfo(_AVI_INFO_YCC_QUANTIZATION);

        switch(g_pstDigitalColorInfo[0].b2DigitalQuantizationPreValue)
        {
            case _AVI_YCC_QUANTIZATION_FULL:

                DebugMessageRx0("Get YCC FULL RANGE", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(_D0_INPUT_PORT, _YCC_QUANTIZATION_FULL_RANGE);

                break;

            case _AVI_YCC_QUANTIZATION_LIMITED:

                DebugMessageRx0("Get YCC LIMIT RANGE", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(_D0_INPUT_PORT, _YCC_QUANTIZATION_LIMIT_RANGE);

                break;

            default:

                DebugMessageRx0("Get YCC RANGE Error", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(_D0_INPUT_PORT, _YCC_QUANTIZATION_FULL_RANGE);

                break;
        }
    }
    else if(GET_COLOR_SPACE(_D0_INPUT_PORT) == _COLOR_SPACE_RGB)
    {
        switch(ScalerTMDSRx0HdmiGetAVIInfo(_AVI_INFO_RGB_QUANTIZATION))
        {
            case _AVI_RGB_QUANTIZATION_LIMITED:

                DebugMessageRx0("Get RGB LIMIT RANGE", 0x00);

                g_pstDigitalColorInfo[0].b2DigitalQuantizationPreValue = _AVI_RGB_QUANTIZATION_LIMITED;

                SET_COLOR_RGB_QUANTIZATION_RANGE(_D0_INPUT_PORT, _RGB_QUANTIZATION_LIMIT_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_FULL:

                DebugMessageRx0("Get RGB FULL RANGE", 0x00);

                g_pstDigitalColorInfo[0].b2DigitalQuantizationPreValue = _AVI_RGB_QUANTIZATION_FULL;

                SET_COLOR_RGB_QUANTIZATION_RANGE(_D0_INPUT_PORT, _RGB_QUANTIZATION_FULL_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_DEFAULT:

                DebugMessageRx0("Get RGB DEFAULT RANGE", 0x00);

                g_pstDigitalColorInfo[0].b2DigitalQuantizationPreValue = _AVI_RGB_QUANTIZATION_DEFAULT;

                SET_COLOR_RGB_QUANTIZATION_RANGE(_D0_INPUT_PORT, _RGB_QUANTIZATION_DEFAULT_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_RESERVED:

                DebugMessageRx0("Get RGB RESERVED RANGE", 0x00);

                g_pstDigitalColorInfo[0].b2DigitalQuantizationPreValue = _AVI_RGB_QUANTIZATION_RESERVED;

                SET_COLOR_RGB_QUANTIZATION_RANGE(_D0_INPUT_PORT, _RGB_QUANTIZATION_RESERVED);

                break;

            default:

                DebugMessageRx0("Get RGB RANGE Error", 0x00);

                g_pstDigitalColorInfo[0].b2DigitalQuantizationPreValue = _AVI_RGB_QUANTIZATION_FULL;

                SET_COLOR_RGB_QUANTIZATION_RANGE(_D0_INPUT_PORT, _RGB_QUANTIZATION_FULL_RANGE);

                break;
        }
    }
}
#endif

//--------------------------------------------------
// Description  : TMDS Rx0 HDMI ColorInfo Changed Detect
// Input Value  : None
// Output Value : Changed ==> _TRUE; No Changed ==> _FALSE;
//--------------------------------------------------
bit ScalerSyncTMDSRx0HdmiColorInfoChanged(void)
{
    BYTE pucTemp[2];
    memset(&pucTemp, 0, sizeof(pucTemp));

    // Check Color Space
    if(ScalerTMDSRx0HdmiGetAVIInfo(_AVI_INFO_COLOR_SPACE) != GET_COLOR_SPACE(_D0_INPUT_PORT))
    {
        DebugMessageRx0("Color Space Changed", 0x00);
        return _TRUE;
    }

    // Check Colorimetry
    if(ScalerTMDSRx0HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY) != g_pstDigitalColorInfo[0].b4DigitalColorimetryPreValue)
    {
        DebugMessageRx0("Colorimetry Changed", 0x00);

        if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
        {
            pucTemp[0] = ScalerTMDSRx0HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY);

            pucTemp[1] = g_pstDigitalColorInfo[0].b4DigitalColorimetryPreValue;

            ScalerSyncTMDSRx0HdmiColorimetrySetting();

            if((GET_COLOR_SPACE(_D0_INPUT_PORT) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(_D0_INPUT_PORT) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(_D0_INPUT_PORT) == _COLOR_SPACE_YCBCR444))
            {
                if(!(((pucTemp[0] == _AVI_COLORIMETRY_00) && (pucTemp[1] == _AVI_COLORIMETRY_01)) || ((pucTemp[0] == _AVI_COLORIMETRY_01) && (pucTemp[1] == _AVI_COLORIMETRY_00))))
                {
                    SET_DIGITAL_COLORIMETRY_CHANGED(_D0_INPUT_PORT);
                }
            }
            else if(GET_COLOR_SPACE(_D0_INPUT_PORT) == _COLOR_SPACE_RGB)
            {
                if((pucTemp[0] == _AVI_COLORIMETRY_11) || (pucTemp[1] == _AVI_COLORIMETRY_11))
                {
                    SET_DIGITAL_COLORIMETRY_CHANGED(_D0_INPUT_PORT);
                }
            }
        }
        else
        {
            return _TRUE;
        }
    }
    else
    {
        if(GET_COLORIMETRY(_D0_INPUT_PORT) == _COLORIMETRY_EXT)
        {
            if(ScalerTMDSRx0HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY) != g_pstDigitalColorInfo[0].b4DigitalColorimetryExtPreValue)
            {
                DebugMessageRx0("Ext Colorimetry Changed", 0x00);

                if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
                {
                    pucTemp[0] = ScalerTMDSRx0HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY);

                    pucTemp[1] = g_pstDigitalColorInfo[0].b4DigitalColorimetryExtPreValue;

                    ScalerSyncTMDSRx0HdmiColorimetryExtSetting();

                    if((GET_COLOR_SPACE(_D0_INPUT_PORT) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(_D0_INPUT_PORT) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(_D0_INPUT_PORT) == _COLOR_SPACE_YCBCR444))
                    {
                        if(!(((pucTemp[0] == _AVI_COLORIMETRY_EXT_100) && (pucTemp[1] == _AVI_COLORIMETRY_EXT_111)) || ((pucTemp[1] == _AVI_COLORIMETRY_EXT_100) && (pucTemp[0] == _AVI_COLORIMETRY_EXT_111))))
                        {
                            SET_DIGITAL_COLORIMETRY_EXT_CHANGED(_D0_INPUT_PORT);
                        }
                    }
                    else if(GET_COLOR_SPACE(_D0_INPUT_PORT) == _COLOR_SPACE_RGB)
                    {
                        if(!(((pucTemp[0] != _AVI_COLORIMETRY_EXT_100) && (pucTemp[0] != _AVI_COLORIMETRY_EXT_110)) && ((pucTemp[1] != _AVI_COLORIMETRY_EXT_100) && (pucTemp[1] != _AVI_COLORIMETRY_EXT_110))))
                        {
                            SET_DIGITAL_COLORIMETRY_EXT_CHANGED(_D0_INPUT_PORT);
                        }
                    }
                }
                else
                {
                    return _TRUE;
                }
            }
        }
    }

#if(_YCC_QUANTIZATION_RANGE_SUPPORT == _ON)
    if((GET_COLOR_SPACE(_D0_INPUT_PORT) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(_D0_INPUT_PORT) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(_D0_INPUT_PORT) == _COLOR_SPACE_YCBCR444))
    {
        if(ScalerTMDSRx0HdmiGetAVIInfo(_AVI_INFO_YCC_QUANTIZATION) != g_pstDigitalColorInfo[0].b2DigitalQuantizationPreValue)
        {
            DebugMessageRx0("YCC Quantization Range Changed", 0x00);

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
            {
                pucTemp[0] = ScalerTMDSRx0HdmiGetAVIInfo(_AVI_INFO_YCC_QUANTIZATION);

                pucTemp[1] = g_pstDigitalColorInfo[0].b2DigitalQuantizationPreValue;

                ScalerSyncTMDSRx0HdmiQuantizationSetting();

                if((pucTemp[0] == _AVI_YCC_QUANTIZATION_LIMITED) || (pucTemp[1] == _AVI_YCC_QUANTIZATION_LIMITED))
                {
                    SET_DIGITAL_QUANTIZATION_CHANGED(_D0_INPUT_PORT);
                }
            }
            else
            {
                return _TRUE;
            }
        }
    }
#endif

#if(_RGB_QUANTIZATION_RANGE_SUPPORT == _ON)
    if(GET_COLOR_SPACE(_D0_INPUT_PORT) == _COLOR_SPACE_RGB)
    {
        if(ScalerTMDSRx0HdmiGetAVIInfo(_AVI_INFO_RGB_QUANTIZATION) != g_pstDigitalColorInfo[0].b2DigitalQuantizationPreValue)
        {
            DebugMessageRx0("RGB Quantization Range Changed", 0x00);

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
            {
                ScalerSyncTMDSRx0HdmiQuantizationSetting();

                SET_DIGITAL_QUANTIZATION_CHANGED(_D0_INPUT_PORT);
            }
            else
            {
                return _TRUE;
            }
        }
    }
#endif

    return _FALSE;
}
#endif

#if(_D1_HDMI_EXIST == _ON)
//--------------------------------------------------
// Description  : TMDS Rx1 Video Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx1HdmiVideoSetting(void)
{
    if(GET_HDMI_RX1_AVI_INFO_FRAME_RECEIVED() == _TRUE)
    {
        // Color Space Auto/ Pixel Repetition auto mode
        ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_51_PORT_PAGE70_HDMI_ACRCR, ~(_BIT6 | _BIT2), (_BIT6 | _BIT2));

        pData[0] = ScalerTMDSRx1HdmiGetAVIInfo(_AVI_INFO_COLOR_SPACE);

        // Get Color Space
        if(pData[0] == _AVI_COLOR_SPACE_00)
        {
            // Color Space RGB
            DebugMessageRx1("Get Color Space RGB", pData[0]);
            SET_COLOR_SPACE(_D1_INPUT_PORT, _COLOR_SPACE_RGB);
        }
        else if(pData[0] == _AVI_COLOR_SPACE_01)
        {
            // YCC422
            DebugMessageRx1("Get Color Space YUV422", pData[0]);
            SET_COLOR_SPACE(_D1_INPUT_PORT, _COLOR_SPACE_YCBCR422);
        }
        else if(pData[0] == _AVI_COLOR_SPACE_11)
        {
            // YCC420
            DebugMessageRx1("Get Color Space YUV420", pData[0]);
            SET_COLOR_SPACE(_D1_INPUT_PORT, _COLOR_SPACE_YCBCR420);
        }
        else
        {
            // YCC444
            DebugMessageRx1("Get Color Space YUV444", pData[0]);
            SET_COLOR_SPACE(_D1_INPUT_PORT, _COLOR_SPACE_YCBCR444);
        }

        // Set Pixel Repetition
        switch(ScalerTMDSRx1HdmiGetAVIInfo(_AVI_INFO_PIXEL_REPETITION))
        {
            case _AVI_PIXEL_REPETITION_0:

                DebugMessageRx1("Get Pixel Repetition 0", 0x00);
                SET_TMDS_RX1_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

                break;

            case _AVI_PIXEL_REPETITION_1:

                DebugMessageRx1("Get Pixel Repetition 1", 0x00);
                SET_TMDS_RX1_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_1);

                break;

            case _AVI_PIXEL_REPETITION_2:

                DebugMessageRx1("Get Pixel Repetition 2", 0x00);
                SET_TMDS_RX1_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_2);

                break;

            case _AVI_PIXEL_REPETITION_3:

                DebugMessageRx1("Get Pixel Repetition 3", 0x00);
                SET_TMDS_RX1_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_3);

                break;

            case _AVI_PIXEL_REPETITION_4:

                DebugMessageRx1("Get Pixel Repetition 4", 0x00);
                SET_TMDS_RX1_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_4);

                break;

            case _AVI_PIXEL_REPETITION_5:

                DebugMessageRx1("Get Pixel Repetition 5", 0x00);
                SET_TMDS_RX1_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_5);

                break;

            default:

                DebugMessageRx1("Get Pixel Repetition Error", 0x00);
                SET_TMDS_RX1_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

                break;
        }

        // Set Colorimetry
        ScalerSyncTMDSRx1HdmiColorimetrySetting();

        // Set Quantization
#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) || (_YCC_QUANTIZATION_RANGE_SUPPORT == _ON))
        ScalerSyncTMDSRx1HdmiQuantizationSetting();
#endif
    }
    else    // No Info Frame Received
    {
#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
        if(GET_TMDS_RX1_CLK_MODE() == _TMDS_MHL_PPMODE_PHY_SETTING)
        {
            SET_COLOR_SPACE(_D1_INPUT_PORT, _COLOR_SPACE_YCBCR422);
            SET_COLOR_YCC_QUANTIZATION_RANGE(_D1_INPUT_PORT, _YCC_QUANTIZATION_LIMIT_RANGE);

            // Manual Set Color Space to YCbCr422 and disable pixel repetition
            ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_51_PORT_PAGE70_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT3);
        }
        else
#endif

        {
            SET_COLOR_SPACE(_D1_INPUT_PORT, _COLOR_SPACE_RGB);
            SET_COLOR_RGB_QUANTIZATION_RANGE(_D1_INPUT_PORT, _RGB_QUANTIZATION_RESERVED);

            // Manual Set Color Space to RGB and disable pixel repetition
            ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_51_PORT_PAGE70_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);
        }

        // Disable down sampling
        ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_50_PORT_PAGE70_HDMI_VCR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        SET_TMDS_RX1_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

        // Waiting for down sampling  effect
        ScalerTimerDelayXms(20);
    }

    ScalerTMDSRx1SetPorchColor(GET_COLOR_SPACE(_D1_INPUT_PORT));
}

//--------------------------------------------------
// Description  : TMDS Rx1 Colorimetry Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx1HdmiColorimetrySetting(void)
{
    if((GET_COLOR_SPACE(_D1_INPUT_PORT) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(_D1_INPUT_PORT) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(_D1_INPUT_PORT) == _COLOR_SPACE_YCBCR444))
    {
        switch(ScalerTMDSRx1HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY))
        {
            case _AVI_COLORIMETRY_00:

                DebugMessageRx1("Get Colorimetry YCC_SMPTE_170M", 0x00);

                g_pstDigitalColorInfo[1].b4DigitalColorimetryPreValue = _AVI_COLORIMETRY_00;

                SET_COLORIMETRY(_D1_INPUT_PORT, _COLORIMETRY_YCC_SMPTE_170M);

                break;

            case _AVI_COLORIMETRY_01:

                DebugMessageRx1("Get Colorimetry YCC_SMPTE_170M", 0x00);

                g_pstDigitalColorInfo[1].b4DigitalColorimetryPreValue = _AVI_COLORIMETRY_01;

                SET_COLORIMETRY(_D1_INPUT_PORT, _COLORIMETRY_YCC_SMPTE_170M);

                break;

            case _AVI_COLORIMETRY_10:

                DebugMessageRx1("Get Colorimetry 709", 0x00);

                g_pstDigitalColorInfo[1].b4DigitalColorimetryPreValue = _AVI_COLORIMETRY_10;

                SET_COLORIMETRY(_D1_INPUT_PORT, _COLORIMETRY_YCC_ITUR_BT709);

                break;

            case _AVI_COLORIMETRY_11:

                DebugMessageRx1("Get Colorimetry Extended", 0x00);

                g_pstDigitalColorInfo[1].b4DigitalColorimetryPreValue = _AVI_COLORIMETRY_11;

                SET_COLORIMETRY(_D1_INPUT_PORT, _COLORIMETRY_EXT);

                ScalerSyncTMDSRx1HdmiColorimetryExtSetting();

                break;

            default:

                DebugMessageRx1("Get Colorimetry INTO_DEFAULT", 0x00);

                break;
        }
    }
    else if(GET_COLOR_SPACE(_D1_INPUT_PORT) == _COLOR_SPACE_RGB)
    {
        g_pstDigitalColorInfo[1].b4DigitalColorimetryPreValue = ScalerTMDSRx1HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY);

        switch(g_pstDigitalColorInfo[1].b4DigitalColorimetryPreValue)
        {
            case _AVI_COLORIMETRY_00:

                DebugMessageRx1("Get Colorimetry RGB_SRGB", 0x00);

                SET_COLORIMETRY(_D1_INPUT_PORT, _COLORIMETRY_RGB_SRGB);

                break;

            case _AVI_COLORIMETRY_11:

                DebugMessageRx1("Get Colorimetry Extended", 0x00);

                SET_COLORIMETRY(_D1_INPUT_PORT, _COLORIMETRY_EXT);

                ScalerSyncTMDSRx1HdmiColorimetryExtSetting();

                break;

            default:

                DebugMessageRx1("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_COLORIMETRY(_D1_INPUT_PORT, _COLORIMETRY_RGB_SRGB);

                break;
        }
    }
}

//--------------------------------------------------
// Description  : TMDS Rx1 Colorimetry Extended Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx1HdmiColorimetryExtSetting(void)
{
    if((GET_COLOR_SPACE(_D1_INPUT_PORT) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(_D1_INPUT_PORT) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(_D1_INPUT_PORT) == _COLOR_SPACE_YCBCR444))
    {
        // Get extended colorimetry
        g_pstDigitalColorInfo[1].b4DigitalColorimetryExtPreValue = ScalerTMDSRx1HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY);

        // Get extended colorimetry
        switch(g_pstDigitalColorInfo[1].b4DigitalColorimetryExtPreValue)
        {
            case _AVI_COLORIMETRY_EXT_000:

                DebugMessageRx1("Get Colorimetry EXT_YCC_XVYCC601", 0x00);

                SET_EXT_COLORIMETRY(_D1_INPUT_PORT, _COLORIMETRY_EXT_YCC_XVYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_001:

                DebugMessageRx1("Get Colorimetry EXT_YCC_XVYCC709", 0x00);

                SET_EXT_COLORIMETRY(_D1_INPUT_PORT, _COLORIMETRY_EXT_YCC_XVYCC709);

                break;

            case _AVI_COLORIMETRY_EXT_010:

                DebugMessageRx1("Get Colorimetry EXT_YCC_SYCC601", 0x00);

                SET_EXT_COLORIMETRY(_D1_INPUT_PORT, _COLORIMETRY_EXT_YCC_SYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_011:

                DebugMessageRx1("Get Colorimetry EXT_YCC_ADOBEYCC601", 0x00);

                SET_EXT_COLORIMETRY(_D1_INPUT_PORT, _COLORIMETRY_EXT_YCC_ADOBEYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_101:

                DebugMessageRx1("Get Colorimetry EXT_YCC_ITUR_BT2020_CL", 0x00);

                SET_EXT_COLORIMETRY(_D1_INPUT_PORT, _COLORIMETRY_EXT_YCC_ITUR_BT2020_CL);

                break;

            case _AVI_COLORIMETRY_EXT_110:

                DebugMessageRx1("Get Colorimetry EXT_YCC_ITUR_BT2020_NCL", 0x00);

                SET_EXT_COLORIMETRY(_D1_INPUT_PORT, _COLORIMETRY_EXT_YCC_ITUR_BT2020_NCL);

                break;

            default:

                DebugMessageRx1("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_EXT_COLORIMETRY(_D1_INPUT_PORT, _COLORIMETRY_EXT_RESERVED);

                break;
        }
    }
    else if(GET_COLOR_SPACE(_D1_INPUT_PORT) == _COLOR_SPACE_RGB)
    {
        g_pstDigitalColorInfo[1].b4DigitalColorimetryExtPreValue = ScalerTMDSRx1HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY);

        switch(g_pstDigitalColorInfo[1].b4DigitalColorimetryExtPreValue)
        {
            case _AVI_COLORIMETRY_EXT_100:

                DebugMessageRx1("Get Colorimetry EXT_RGB_ADOBERGB", 0x00);

                SET_EXT_COLORIMETRY(_D1_INPUT_PORT, _COLORIMETRY_EXT_RGB_ADOBERGB);

                break;

            case _AVI_COLORIMETRY_EXT_110:

                DebugMessageRx1("Get Colorimetry EXT_RGB_ITUR_BT2020", 0x00);

                SET_EXT_COLORIMETRY(_D1_INPUT_PORT, _COLORIMETRY_EXT_RGB_ITUR_BT2020);

                break;

            default:

                DebugMessageRx1("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_EXT_COLORIMETRY(_D1_INPUT_PORT, _COLORIMETRY_EXT_RESERVED);

                break;
        }
    }
}
#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) || (_YCC_QUANTIZATION_RANGE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : TMDS Rx1 Quantization Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx1HdmiQuantizationSetting(void)
{
    if((GET_COLOR_SPACE(_D1_INPUT_PORT) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(_D1_INPUT_PORT) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(_D1_INPUT_PORT) == _COLOR_SPACE_YCBCR444))
    {
        g_pstDigitalColorInfo[1].b2DigitalQuantizationPreValue = ScalerTMDSRx1HdmiGetAVIInfo(_AVI_INFO_YCC_QUANTIZATION);

        switch(g_pstDigitalColorInfo[1].b2DigitalQuantizationPreValue)
        {
            case _AVI_YCC_QUANTIZATION_FULL:

                DebugMessageRx1("Get YCC FULL RANGE", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(_D1_INPUT_PORT, _YCC_QUANTIZATION_FULL_RANGE);

                break;

            case _AVI_YCC_QUANTIZATION_LIMITED:

                DebugMessageRx1("Get YCC LIMIT RANGE", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(_D1_INPUT_PORT, _YCC_QUANTIZATION_LIMIT_RANGE);

                break;

            default:

                DebugMessageRx1("Get YCC RANGE Error", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(_D1_INPUT_PORT, _YCC_QUANTIZATION_FULL_RANGE);

                break;
        }
    }
    else if(GET_COLOR_SPACE(_D1_INPUT_PORT) == _COLOR_SPACE_RGB)
    {
        switch(ScalerTMDSRx1HdmiGetAVIInfo(_AVI_INFO_RGB_QUANTIZATION))
        {
            case _AVI_RGB_QUANTIZATION_LIMITED:

                DebugMessageRx1("Get RGB LIMIT RANGE", 0x00);

                g_pstDigitalColorInfo[1].b2DigitalQuantizationPreValue = _AVI_RGB_QUANTIZATION_LIMITED;

                SET_COLOR_RGB_QUANTIZATION_RANGE(_D1_INPUT_PORT, _RGB_QUANTIZATION_LIMIT_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_FULL:

                DebugMessageRx1("Get RGB FULL RANGE", 0x00);

                g_pstDigitalColorInfo[1].b2DigitalQuantizationPreValue = _AVI_RGB_QUANTIZATION_FULL;

                SET_COLOR_RGB_QUANTIZATION_RANGE(_D1_INPUT_PORT, _RGB_QUANTIZATION_FULL_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_DEFAULT:

                DebugMessageRx1("Get RGB DEFAULT RANGE", 0x00);

                g_pstDigitalColorInfo[1].b2DigitalQuantizationPreValue = _AVI_RGB_QUANTIZATION_DEFAULT;

                SET_COLOR_RGB_QUANTIZATION_RANGE(_D1_INPUT_PORT, _RGB_QUANTIZATION_DEFAULT_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_RESERVED:

                DebugMessageRx1("Get RGB RESERVED RANGE", 0x00);

                g_pstDigitalColorInfo[1].b2DigitalQuantizationPreValue = _AVI_RGB_QUANTIZATION_RESERVED;

                SET_COLOR_RGB_QUANTIZATION_RANGE(_D1_INPUT_PORT, _RGB_QUANTIZATION_RESERVED);

                break;

            default:

                DebugMessageRx1("Get RGB RANGE Error", 0x00);

                g_pstDigitalColorInfo[1].b2DigitalQuantizationPreValue = _AVI_RGB_QUANTIZATION_FULL;

                SET_COLOR_RGB_QUANTIZATION_RANGE(_D1_INPUT_PORT, _RGB_QUANTIZATION_FULL_RANGE);

                break;
        }
    }
}
#endif

//--------------------------------------------------
// Description  : TMDS Rx1 HDMI ColorInfo Changed Detect
// Input Value  : None
// Output Value : Changed ==> _TRUE; No Changed ==> _FALSE;
//--------------------------------------------------
bit ScalerSyncTMDSRx1HdmiColorInfoChanged(void)
{
    BYTE pucTemp[2];
    memset(&pucTemp, 0, sizeof(pucTemp));

    // Check Color Space
    if(ScalerTMDSRx1HdmiGetAVIInfo(_AVI_INFO_COLOR_SPACE) != GET_COLOR_SPACE(_D1_INPUT_PORT))
    {
        DebugMessageRx1("Color Space Changed", 0x00);
        return _TRUE;
    }

    // Check Colorimetry
    if(ScalerTMDSRx1HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY) != g_pstDigitalColorInfo[1].b4DigitalColorimetryPreValue)
    {
        DebugMessageRx1("Colorimetry Changed", 0x00);

        if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
        {
            pucTemp[0] = ScalerTMDSRx1HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY);

            pucTemp[1] = g_pstDigitalColorInfo[1].b4DigitalColorimetryPreValue;

            ScalerSyncTMDSRx1HdmiColorimetrySetting();

            if((GET_COLOR_SPACE(_D1_INPUT_PORT) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(_D1_INPUT_PORT) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(_D1_INPUT_PORT) == _COLOR_SPACE_YCBCR444))
            {
                if(!(((pucTemp[0] == _AVI_COLORIMETRY_00) && (pucTemp[1] == _AVI_COLORIMETRY_01)) || ((pucTemp[0] == _AVI_COLORIMETRY_01) && (pucTemp[1] == _AVI_COLORIMETRY_00))))
                {
                    SET_DIGITAL_COLORIMETRY_CHANGED(_D1_INPUT_PORT);
                }
            }
            else if(GET_COLOR_SPACE(_D1_INPUT_PORT) == _COLOR_SPACE_RGB)
            {
                if((pucTemp[0] == _AVI_COLORIMETRY_11) || (pucTemp[1] == _AVI_COLORIMETRY_11))
                {
                    SET_DIGITAL_COLORIMETRY_CHANGED(_D1_INPUT_PORT);
                }
            }
        }
        else
        {
            return _TRUE;
        }
    }
    else
    {
        if(GET_COLORIMETRY(_D1_INPUT_PORT) == _COLORIMETRY_EXT)
        {
            if(ScalerTMDSRx1HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY) != g_pstDigitalColorInfo[1].b4DigitalColorimetryExtPreValue)
            {
                DebugMessageRx1("Ext Colorimetry Changed", 0x00);

                if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
                {
                    pucTemp[0] = ScalerTMDSRx1HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY);

                    pucTemp[1] = g_pstDigitalColorInfo[1].b4DigitalColorimetryExtPreValue;

                    ScalerSyncTMDSRx1HdmiColorimetryExtSetting();

                    if((GET_COLOR_SPACE(_D1_INPUT_PORT) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(_D1_INPUT_PORT) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(_D1_INPUT_PORT) == _COLOR_SPACE_YCBCR444))
                    {
                        if(!(((pucTemp[0] == _AVI_COLORIMETRY_EXT_100) && (pucTemp[1] == _AVI_COLORIMETRY_EXT_111)) || ((pucTemp[1] == _AVI_COLORIMETRY_EXT_100) && (pucTemp[0] == _AVI_COLORIMETRY_EXT_111))))
                        {
                            SET_DIGITAL_COLORIMETRY_EXT_CHANGED(_D1_INPUT_PORT);
                        }
                    }
                    else if(GET_COLOR_SPACE(_D1_INPUT_PORT) == _COLOR_SPACE_RGB)
                    {
                        if(!(((pucTemp[0] != _AVI_COLORIMETRY_EXT_100) && (pucTemp[0] != _AVI_COLORIMETRY_EXT_110)) && ((pucTemp[1] != _AVI_COLORIMETRY_EXT_100) && (pucTemp[1] != _AVI_COLORIMETRY_EXT_110))))
                        {
                            SET_DIGITAL_COLORIMETRY_EXT_CHANGED(_D1_INPUT_PORT);
                        }
                    }
                }
                else
                {
                    return _TRUE;
                }
            }
        }
    }

#if(_YCC_QUANTIZATION_RANGE_SUPPORT == _ON)
    if((GET_COLOR_SPACE(_D1_INPUT_PORT) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(_D1_INPUT_PORT) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(_D1_INPUT_PORT) == _COLOR_SPACE_YCBCR444))
    {
        if(ScalerTMDSRx1HdmiGetAVIInfo(_AVI_INFO_YCC_QUANTIZATION) != g_pstDigitalColorInfo[1].b2DigitalQuantizationPreValue)
        {
            DebugMessageRx1("YCC Quantization Range Changed", 0x00);

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
            {
                pucTemp[0] = ScalerTMDSRx1HdmiGetAVIInfo(_AVI_INFO_YCC_QUANTIZATION);

                pucTemp[1] = g_pstDigitalColorInfo[1].b2DigitalQuantizationPreValue;

                ScalerSyncTMDSRx1HdmiQuantizationSetting();

                if((pucTemp[0] == _AVI_YCC_QUANTIZATION_LIMITED) || (pucTemp[1] == _AVI_YCC_QUANTIZATION_LIMITED))
                {
                    SET_DIGITAL_QUANTIZATION_CHANGED(_D1_INPUT_PORT);
                }
            }
            else
            {
                return _TRUE;
            }
        }
    }
#endif

#if(_RGB_QUANTIZATION_RANGE_SUPPORT == _ON)
    if(GET_COLOR_SPACE(_D1_INPUT_PORT) == _COLOR_SPACE_RGB)
    {
        if(ScalerTMDSRx1HdmiGetAVIInfo(_AVI_INFO_RGB_QUANTIZATION) != g_pstDigitalColorInfo[1].b2DigitalQuantizationPreValue)
        {
            DebugMessageRx1("RGB Quantization Range Changed", 0x00);

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
            {
                ScalerSyncTMDSRx1HdmiQuantizationSetting();

                SET_DIGITAL_QUANTIZATION_CHANGED(_D1_INPUT_PORT);
            }
            else
            {
                return _TRUE;
            }
        }
    }
#endif

    return _FALSE;
}
#endif

#if(_D2_HDMI_EXIST == _ON)
#if(_D2_INPUT_PORT_TYPE != _D2_DUAL_DVI_PORT)
//--------------------------------------------------
// Description  : TMDS Rx2 Video Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx2HdmiVideoSetting(void)
{
    if(GET_HDMI_RX2_AVI_INFO_FRAME_RECEIVED() == _TRUE)
    {
        // Color Space Auto/ Pixel Repetition auto mode
        ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_51_PORT_PAGE71_HDMI_ACRCR, ~(_BIT6 | _BIT2), (_BIT6 | _BIT2));

        pData[0] = ScalerTMDSRx2HdmiGetAVIInfo(_AVI_INFO_COLOR_SPACE);

        // Get Color Space
        if(pData[0] == _AVI_COLOR_SPACE_00)
        {
            // Color Space RGB
            DebugMessageRx2("Get Color Space RGB", pData[0]);
            SET_COLOR_SPACE(_D2_INPUT_PORT, _COLOR_SPACE_RGB);
        }
        else if(pData[0] == _AVI_COLOR_SPACE_01)
        {
            // YCC422
            DebugMessageRx2("Get Color Space YUV422", pData[0]);
            SET_COLOR_SPACE(_D2_INPUT_PORT, _COLOR_SPACE_YCBCR422);
        }
        else if(pData[0] == _AVI_COLOR_SPACE_11)
        {
            // YCC420
            DebugMessageRx2("Get Color Space YUV420", pData[0]);
            SET_COLOR_SPACE(_D2_INPUT_PORT, _COLOR_SPACE_YCBCR420);
        }
        else
        {
            // YCC444
            DebugMessageRx2("Get Color Space YUV444", pData[0]);
            SET_COLOR_SPACE(_D2_INPUT_PORT, _COLOR_SPACE_YCBCR444);
        }

        // Set Pixel Repetition
        switch(ScalerTMDSRx2HdmiGetAVIInfo(_AVI_INFO_PIXEL_REPETITION))
        {
            case _AVI_PIXEL_REPETITION_0:

                DebugMessageRx2("Get Pixel Repetition 0", 0x00);
                SET_TMDS_RX2_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

                break;

            case _AVI_PIXEL_REPETITION_1:

                DebugMessageRx2("Get Pixel Repetition 1", 0x00);
                SET_TMDS_RX2_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_1);

                break;

            case _AVI_PIXEL_REPETITION_2:

                DebugMessageRx2("Get Pixel Repetition 2", 0x00);
                SET_TMDS_RX2_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_2);

                break;

            case _AVI_PIXEL_REPETITION_3:

                DebugMessageRx2("Get Pixel Repetition 3", 0x00);
                SET_TMDS_RX2_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_3);

                break;

            case _AVI_PIXEL_REPETITION_4:

                DebugMessageRx2("Get Pixel Repetition 4", 0x00);
                SET_TMDS_RX2_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_4);

                break;

            case _AVI_PIXEL_REPETITION_5:

                DebugMessageRx2("Get Pixel Repetition 5", 0x00);
                SET_TMDS_RX2_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_5);

                break;

            default:

                DebugMessageRx2("Get Pixel Repetition Error", 0x00);
                SET_TMDS_RX2_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

                break;
        }

        // Set Colorimetry
        ScalerSyncTMDSRx2HdmiColorimetrySetting();

        // Set Quantization
#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) || (_YCC_QUANTIZATION_RANGE_SUPPORT == _ON))
        ScalerSyncTMDSRx2HdmiQuantizationSetting();
#endif
    }
    else    // No Info Frame Received
    {
#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
        if(GET_TMDS_RX2_CLK_MODE() == _TMDS_MHL_PPMODE_PHY_SETTING)
        {
            SET_COLOR_SPACE(_D2_INPUT_PORT, _COLOR_SPACE_YCBCR422);
            SET_COLOR_YCC_QUANTIZATION_RANGE(_D2_INPUT_PORT, _YCC_QUANTIZATION_LIMIT_RANGE);

            // Manual Set Color Space to YCbCr422 and disable pixel repetition
            ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_51_PORT_PAGE71_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT3);
        }
        else
#endif

        {
            SET_COLOR_SPACE(_D2_INPUT_PORT, _COLOR_SPACE_RGB);
            SET_COLOR_RGB_QUANTIZATION_RANGE(_D2_INPUT_PORT, _RGB_QUANTIZATION_RESERVED);

            // Manual Set Color Space to RGB and disable pixel repetition
            ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_51_PORT_PAGE71_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);
        }

        // Disable down sampling
        ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_50_PORT_PAGE71_HDMI_VCR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        SET_TMDS_RX2_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

        // Waiting for down sampling  effect
        ScalerTimerDelayXms(20);
    }

    ScalerTMDSRx2SetPorchColor(GET_COLOR_SPACE(_D2_INPUT_PORT));
}
#endif

//--------------------------------------------------
// Description  : TMDS Rx2 Colorimetry Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx2HdmiColorimetrySetting(void)
{
    if((GET_COLOR_SPACE(_D2_INPUT_PORT) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(_D2_INPUT_PORT) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(_D2_INPUT_PORT) == _COLOR_SPACE_YCBCR444))
    {
        switch(ScalerTMDSRx2HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY))
        {
            case _AVI_COLORIMETRY_00:

                DebugMessageRx2("Get Colorimetry YCC_SMPTE_170M", 0x00);

                g_pstDigitalColorInfo[2].b4DigitalColorimetryPreValue = _AVI_COLORIMETRY_00;

                SET_COLORIMETRY(_D2_INPUT_PORT, _COLORIMETRY_YCC_SMPTE_170M);

                break;

            case _AVI_COLORIMETRY_01:

                DebugMessageRx2("Get Colorimetry YCC_SMPTE_170M", 0x00);

                g_pstDigitalColorInfo[2].b4DigitalColorimetryPreValue = _AVI_COLORIMETRY_01;

                SET_COLORIMETRY(_D2_INPUT_PORT, _COLORIMETRY_YCC_SMPTE_170M);

                break;

            case _AVI_COLORIMETRY_10:

                DebugMessageRx2("Get Colorimetry 709", 0x00);

                g_pstDigitalColorInfo[2].b4DigitalColorimetryPreValue = _AVI_COLORIMETRY_10;

                SET_COLORIMETRY(_D2_INPUT_PORT, _COLORIMETRY_YCC_ITUR_BT709);

                break;

            case _AVI_COLORIMETRY_11:

                DebugMessageRx2("Get Colorimetry Extended", 0x00);

                g_pstDigitalColorInfo[2].b4DigitalColorimetryPreValue = _AVI_COLORIMETRY_11;

                SET_COLORIMETRY(_D2_INPUT_PORT, _COLORIMETRY_EXT);

                ScalerSyncTMDSRx2HdmiColorimetryExtSetting();

                break;

            default:

                DebugMessageRx2("Get Colorimetry INTO_DEFAULT", 0x00);

                break;
        }
    }
    else if(GET_COLOR_SPACE(_D2_INPUT_PORT) == _COLOR_SPACE_RGB)
    {
        g_pstDigitalColorInfo[2].b4DigitalColorimetryPreValue = ScalerTMDSRx2HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY);

        switch(g_pstDigitalColorInfo[2].b4DigitalColorimetryPreValue)
        {
            case _AVI_COLORIMETRY_00:

                DebugMessageRx2("Get Colorimetry RGB_SRGB", 0x00);

                SET_COLORIMETRY(_D2_INPUT_PORT, _COLORIMETRY_RGB_SRGB);

                break;

            case _AVI_COLORIMETRY_11:

                DebugMessageRx2("Get Colorimetry Extended", 0x00);

                SET_COLORIMETRY(_D2_INPUT_PORT, _COLORIMETRY_EXT);

                ScalerSyncTMDSRx2HdmiColorimetryExtSetting();

                break;

            default:

                DebugMessageRx2("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_COLORIMETRY(_D2_INPUT_PORT, _COLORIMETRY_RGB_SRGB);

                break;
        }
    }
}

//--------------------------------------------------
// Description  : TMDS Rx2 Colorimetry Extended Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx2HdmiColorimetryExtSetting(void)
{
    if((GET_COLOR_SPACE(_D2_INPUT_PORT) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(_D2_INPUT_PORT) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(_D2_INPUT_PORT) == _COLOR_SPACE_YCBCR444))
    {
        // Get extended colorimetry
        g_pstDigitalColorInfo[2].b4DigitalColorimetryExtPreValue = ScalerTMDSRx2HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY);

        // Get extended colorimetry
        switch(g_pstDigitalColorInfo[2].b4DigitalColorimetryExtPreValue)
        {
            case _AVI_COLORIMETRY_EXT_000:

                DebugMessageRx2("Get Colorimetry EXT_YCC_XVYCC601", 0x00);

                SET_EXT_COLORIMETRY(_D2_INPUT_PORT, _COLORIMETRY_EXT_YCC_XVYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_001:

                DebugMessageRx2("Get Colorimetry EXT_YCC_XVYCC709", 0x00);

                SET_EXT_COLORIMETRY(_D2_INPUT_PORT, _COLORIMETRY_EXT_YCC_XVYCC709);

                break;

            case _AVI_COLORIMETRY_EXT_010:

                DebugMessageRx2("Get Colorimetry EXT_YCC_SYCC601", 0x00);

                SET_EXT_COLORIMETRY(_D2_INPUT_PORT, _COLORIMETRY_EXT_YCC_SYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_011:

                DebugMessageRx2("Get Colorimetry EXT_YCC_ADOBEYCC601", 0x00);

                SET_EXT_COLORIMETRY(_D2_INPUT_PORT, _COLORIMETRY_EXT_YCC_ADOBEYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_101:

                DebugMessageRx2("Get Colorimetry EXT_YCC_ITUR_BT2020_CL", 0x00);

                SET_EXT_COLORIMETRY(_D2_INPUT_PORT, _COLORIMETRY_EXT_YCC_ITUR_BT2020_CL);

                break;

            case _AVI_COLORIMETRY_EXT_110:

                DebugMessageRx2("Get Colorimetry EXT_YCC_ITUR_BT2020_NCL", 0x00);

                SET_EXT_COLORIMETRY(_D2_INPUT_PORT, _COLORIMETRY_EXT_YCC_ITUR_BT2020_NCL);

                break;

            default:

                DebugMessageRx2("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_EXT_COLORIMETRY(_D2_INPUT_PORT, _COLORIMETRY_EXT_RESERVED);

                break;
        }
    }
    else if(GET_COLOR_SPACE(_D2_INPUT_PORT) == _COLOR_SPACE_RGB)
    {
        g_pstDigitalColorInfo[2].b4DigitalColorimetryExtPreValue = ScalerTMDSRx2HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY);

        switch(g_pstDigitalColorInfo[2].b4DigitalColorimetryExtPreValue)
        {
            case _AVI_COLORIMETRY_EXT_100:

                DebugMessageRx2("Get Colorimetry EXT_RGB_ADOBERGB", 0x00);

                SET_EXT_COLORIMETRY(_D2_INPUT_PORT, _COLORIMETRY_EXT_RGB_ADOBERGB);

                break;

            case _AVI_COLORIMETRY_EXT_110:

                DebugMessageRx2("Get Colorimetry EXT_RGB_ITUR_BT2020", 0x00);

                SET_EXT_COLORIMETRY(_D2_INPUT_PORT, _COLORIMETRY_EXT_RGB_ITUR_BT2020);

                break;

            default:

                DebugMessageRx2("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_EXT_COLORIMETRY(_D2_INPUT_PORT, _COLORIMETRY_EXT_RESERVED);

                break;
        }
    }
}
#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) || (_YCC_QUANTIZATION_RANGE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : TMDS Rx2 Quantization Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx2HdmiQuantizationSetting(void)
{
    if((GET_COLOR_SPACE(_D2_INPUT_PORT) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(_D2_INPUT_PORT) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(_D2_INPUT_PORT) == _COLOR_SPACE_YCBCR444))
    {
        g_pstDigitalColorInfo[2].b2DigitalQuantizationPreValue = ScalerTMDSRx2HdmiGetAVIInfo(_AVI_INFO_YCC_QUANTIZATION);

        switch(g_pstDigitalColorInfo[2].b2DigitalQuantizationPreValue)
        {
            case _AVI_YCC_QUANTIZATION_FULL:

                DebugMessageRx2("Get YCC FULL RANGE", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(_D2_INPUT_PORT, _YCC_QUANTIZATION_FULL_RANGE);

                break;

            case _AVI_YCC_QUANTIZATION_LIMITED:

                DebugMessageRx2("Get YCC LIMIT RANGE", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(_D2_INPUT_PORT, _YCC_QUANTIZATION_LIMIT_RANGE);

                break;

            default:

                DebugMessageRx2("Get YCC RANGE Error", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(_D2_INPUT_PORT, _YCC_QUANTIZATION_FULL_RANGE);

                break;
        }
    }
    else if(GET_COLOR_SPACE(_D2_INPUT_PORT) == _COLOR_SPACE_RGB)
    {
        switch(ScalerTMDSRx2HdmiGetAVIInfo(_AVI_INFO_RGB_QUANTIZATION))
        {
            case _AVI_RGB_QUANTIZATION_LIMITED:

                DebugMessageRx2("Get RGB LIMIT RANGE", 0x00);

                g_pstDigitalColorInfo[2].b2DigitalQuantizationPreValue = _AVI_RGB_QUANTIZATION_LIMITED;

                SET_COLOR_RGB_QUANTIZATION_RANGE(_D2_INPUT_PORT, _RGB_QUANTIZATION_LIMIT_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_FULL:

                DebugMessageRx2("Get RGB FULL RANGE", 0x00);

                g_pstDigitalColorInfo[2].b2DigitalQuantizationPreValue = _AVI_RGB_QUANTIZATION_FULL;

                SET_COLOR_RGB_QUANTIZATION_RANGE(_D2_INPUT_PORT, _RGB_QUANTIZATION_FULL_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_DEFAULT:

                DebugMessageRx2("Get RGB DEFAULT RANGE", 0x00);

                g_pstDigitalColorInfo[2].b2DigitalQuantizationPreValue = _AVI_RGB_QUANTIZATION_DEFAULT;

                SET_COLOR_RGB_QUANTIZATION_RANGE(_D2_INPUT_PORT, _RGB_QUANTIZATION_DEFAULT_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_RESERVED:

                DebugMessageRx2("Get RGB RESERVED RANGE", 0x00);

                g_pstDigitalColorInfo[2].b2DigitalQuantizationPreValue = _AVI_RGB_QUANTIZATION_RESERVED;

                SET_COLOR_RGB_QUANTIZATION_RANGE(_D2_INPUT_PORT, _RGB_QUANTIZATION_RESERVED);

                break;

            default:

                DebugMessageRx2("Get RGB RANGE Error", 0x00);

                g_pstDigitalColorInfo[2].b2DigitalQuantizationPreValue = _AVI_RGB_QUANTIZATION_FULL;

                SET_COLOR_RGB_QUANTIZATION_RANGE(_D2_INPUT_PORT, _RGB_QUANTIZATION_FULL_RANGE);

                break;
        }
    }
}
#endif

//--------------------------------------------------
// Description  : TMDS Rx2 HDMI ColorInfo Changed Detect
// Input Value  : None
// Output Value : Changed ==> _TRUE; No Changed ==> _FALSE;
//--------------------------------------------------
bit ScalerSyncTMDSRx2HdmiColorInfoChanged(void)
{
    BYTE pucTemp[2];
    memset(&pucTemp, 0, sizeof(pucTemp));

    // Check Color Space
    if(ScalerTMDSRx2HdmiGetAVIInfo(_AVI_INFO_COLOR_SPACE) != GET_COLOR_SPACE(_D2_INPUT_PORT))
    {
        DebugMessageRx2("Color Space Changed", 0x00);
        return _TRUE;
    }

    // Check Colorimetry
    if(ScalerTMDSRx2HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY) != g_pstDigitalColorInfo[2].b4DigitalColorimetryPreValue)
    {
        DebugMessageRx2("Colorimetry Changed", 0x00);

        if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
        {
            pucTemp[0] = ScalerTMDSRx2HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY);

            pucTemp[1] = g_pstDigitalColorInfo[2].b4DigitalColorimetryPreValue;

            ScalerSyncTMDSRx2HdmiColorimetrySetting();

            if((GET_COLOR_SPACE(_D2_INPUT_PORT) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(_D2_INPUT_PORT) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(_D2_INPUT_PORT) == _COLOR_SPACE_YCBCR444))
            {
                if(!(((pucTemp[0] == _AVI_COLORIMETRY_00) && (pucTemp[1] == _AVI_COLORIMETRY_01)) || ((pucTemp[0] == _AVI_COLORIMETRY_01) && (pucTemp[1] == _AVI_COLORIMETRY_00))))
                {
                    SET_DIGITAL_COLORIMETRY_CHANGED(_D2_INPUT_PORT);
                }
            }
            else if(GET_COLOR_SPACE(_D2_INPUT_PORT) == _COLOR_SPACE_RGB)
            {
                if((pucTemp[0] == _AVI_COLORIMETRY_11) || (pucTemp[1] == _AVI_COLORIMETRY_11))
                {
                    SET_DIGITAL_COLORIMETRY_CHANGED(_D2_INPUT_PORT);
                }
            }
        }
        else
        {
            return _TRUE;
        }
    }
    else
    {
        if(GET_COLORIMETRY(_D2_INPUT_PORT) == _COLORIMETRY_EXT)
        {
            if(ScalerTMDSRx2HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY) != g_pstDigitalColorInfo[2].b4DigitalColorimetryExtPreValue)
            {
                DebugMessageRx2("Ext Colorimetry Changed", 0x00);

                if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
                {
                    pucTemp[0] = ScalerTMDSRx2HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY);

                    pucTemp[1] = g_pstDigitalColorInfo[2].b4DigitalColorimetryExtPreValue;

                    ScalerSyncTMDSRx2HdmiColorimetryExtSetting();

                    if((GET_COLOR_SPACE(_D2_INPUT_PORT) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(_D2_INPUT_PORT) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(_D2_INPUT_PORT) == _COLOR_SPACE_YCBCR444))
                    {
                        if(!(((pucTemp[0] == _AVI_COLORIMETRY_EXT_100) && (pucTemp[1] == _AVI_COLORIMETRY_EXT_111)) || ((pucTemp[1] == _AVI_COLORIMETRY_EXT_100) && (pucTemp[0] == _AVI_COLORIMETRY_EXT_111))))
                        {
                            SET_DIGITAL_COLORIMETRY_EXT_CHANGED(_D2_INPUT_PORT);
                        }
                    }
                    else if(GET_COLOR_SPACE(_D2_INPUT_PORT) == _COLOR_SPACE_RGB)
                    {
                        if(!(((pucTemp[0] != _AVI_COLORIMETRY_EXT_100) && (pucTemp[0] != _AVI_COLORIMETRY_EXT_110)) && ((pucTemp[1] != _AVI_COLORIMETRY_EXT_100) && (pucTemp[1] != _AVI_COLORIMETRY_EXT_110))))
                        {
                            SET_DIGITAL_COLORIMETRY_EXT_CHANGED(_D2_INPUT_PORT);
                        }
                    }
                }
                else
                {
                    return _TRUE;
                }
            }
        }
    }

#if(_YCC_QUANTIZATION_RANGE_SUPPORT == _ON)
    if((GET_COLOR_SPACE(_D2_INPUT_PORT) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(_D2_INPUT_PORT) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(_D2_INPUT_PORT) == _COLOR_SPACE_YCBCR444))
    {
        if(ScalerTMDSRx2HdmiGetAVIInfo(_AVI_INFO_YCC_QUANTIZATION) != g_pstDigitalColorInfo[2].b2DigitalQuantizationPreValue)
        {
            DebugMessageRx2("YCC Quantization Range Changed", 0x00);

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
            {
                pucTemp[0] = ScalerTMDSRx2HdmiGetAVIInfo(_AVI_INFO_YCC_QUANTIZATION);

                pucTemp[1] = g_pstDigitalColorInfo[2].b2DigitalQuantizationPreValue;

                ScalerSyncTMDSRx2HdmiQuantizationSetting();

                if((pucTemp[0] == _AVI_YCC_QUANTIZATION_LIMITED) || (pucTemp[1] == _AVI_YCC_QUANTIZATION_LIMITED))
                {
                    SET_DIGITAL_QUANTIZATION_CHANGED(_D2_INPUT_PORT);
                }
            }
            else
            {
                return _TRUE;
            }
        }
    }
#endif

#if(_RGB_QUANTIZATION_RANGE_SUPPORT == _ON)
    if(GET_COLOR_SPACE(_D2_INPUT_PORT) == _COLOR_SPACE_RGB)
    {
        if(ScalerTMDSRx2HdmiGetAVIInfo(_AVI_INFO_RGB_QUANTIZATION) != g_pstDigitalColorInfo[2].b2DigitalQuantizationPreValue)
        {
            DebugMessageRx2("RGB Quantization Range Changed", 0x00);

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
            {
                ScalerSyncTMDSRx2HdmiQuantizationSetting();

                SET_DIGITAL_QUANTIZATION_CHANGED(_D2_INPUT_PORT);
            }
            else
            {
                return _TRUE;
            }
        }
    }
#endif

    return _FALSE;
}
#endif

#if(_D3_HDMI_EXIST == _ON)
#if(_D3_INPUT_PORT_TYPE != _D3_DUAL_DVI_PORT)
//--------------------------------------------------
// Description  : TMDS Rx3 Video Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx3HdmiVideoSetting(void)
{
    if(GET_HDMI_RX3_AVI_INFO_FRAME_RECEIVED() == _TRUE)
    {
        // Color Space Auto/ Pixel Repetition auto mode
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_51_PORT_PAGE72_HDMI_ACRCR, ~(_BIT6 | _BIT2), (_BIT6 | _BIT2));

        pData[0] = ScalerTMDSRx3HdmiGetAVIInfo(_AVI_INFO_COLOR_SPACE);

        // Get Color Space
        if(pData[0] == _AVI_COLOR_SPACE_00)
        {
            // Color Space RGB
            DebugMessageRx3("Get Color Space RGB", pData[0]);
            SET_COLOR_SPACE(_D3_INPUT_PORT, _COLOR_SPACE_RGB);
        }
        else if(pData[0] == _AVI_COLOR_SPACE_01)
        {
            // YCC422
            DebugMessageRx3("Get Color Space YUV422", pData[0]);
            SET_COLOR_SPACE(_D3_INPUT_PORT, _COLOR_SPACE_YCBCR422);
        }
        else if(pData[0] == _AVI_COLOR_SPACE_11)
        {
            // YCC420
            DebugMessageRx3("Get Color Space YUV420", pData[0]);
            SET_COLOR_SPACE(_D3_INPUT_PORT, _COLOR_SPACE_YCBCR420);
        }
        else
        {
            // YCC444
            DebugMessageRx3("Get Color Space YUV444", pData[0]);
            SET_COLOR_SPACE(_D3_INPUT_PORT, _COLOR_SPACE_YCBCR444);
        }

        // Set Pixel Repetition
        switch(ScalerTMDSRx3HdmiGetAVIInfo(_AVI_INFO_PIXEL_REPETITION))
        {
            case _AVI_PIXEL_REPETITION_0:

                DebugMessageRx3("Get Pixel Repetition 0", 0x00);
                SET_TMDS_RX3_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

                break;

            case _AVI_PIXEL_REPETITION_1:

                DebugMessageRx3("Get Pixel Repetition 1", 0x00);
                SET_TMDS_RX3_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_1);

                break;

            case _AVI_PIXEL_REPETITION_2:

                DebugMessageRx3("Get Pixel Repetition 2", 0x00);
                SET_TMDS_RX3_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_2);

                break;

            case _AVI_PIXEL_REPETITION_3:

                DebugMessageRx3("Get Pixel Repetition 3", 0x00);
                SET_TMDS_RX3_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_3);

                break;

            case _AVI_PIXEL_REPETITION_4:

                DebugMessageRx3("Get Pixel Repetition 4", 0x00);
                SET_TMDS_RX3_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_4);

                break;

            case _AVI_PIXEL_REPETITION_5:

                DebugMessageRx3("Get Pixel Repetition 5", 0x00);
                SET_TMDS_RX3_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_5);

                break;

            default:

                DebugMessageRx3("Get Pixel Repetition Error", 0x00);
                SET_TMDS_RX3_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

                break;
        }

        // Set Colorimetry
        ScalerSyncTMDSRx3HdmiColorimetrySetting();

        // Set Quantization
#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) || (_YCC_QUANTIZATION_RANGE_SUPPORT == _ON))
        ScalerSyncTMDSRx3HdmiQuantizationSetting();
#endif
    }
    else    // No Info Frame Received
    {
#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
        if(GET_TMDS_RX3_CLK_MODE() == _TMDS_MHL_PPMODE_PHY_SETTING)
        {
            SET_COLOR_SPACE(_D3_INPUT_PORT, _COLOR_SPACE_YCBCR422);
            SET_COLOR_YCC_QUANTIZATION_RANGE(_D3_INPUT_PORT, _YCC_QUANTIZATION_LIMIT_RANGE);

            // Manual Set Color Space to YCbCr422 and disable pixel repetition
            ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_51_PORT_PAGE72_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT3);
        }
        else
#endif

        {
            SET_COLOR_SPACE(_D3_INPUT_PORT, _COLOR_SPACE_RGB);
            SET_COLOR_RGB_QUANTIZATION_RANGE(_D3_INPUT_PORT, _RGB_QUANTIZATION_RESERVED);

            // Manual Set Color Space to RGB and disable pixel repetition
            ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_51_PORT_PAGE72_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);
        }

        // Disable down sampling
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_50_PORT_PAGE72_HDMI_VCR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        SET_TMDS_RX3_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

        // Waiting for down sampling  effect
        ScalerTimerDelayXms(20);
    }

    ScalerTMDSRx3SetPorchColor(GET_COLOR_SPACE(_D3_INPUT_PORT));
}
#endif

//--------------------------------------------------
// Description  : TMDS Rx3 Colorimetry Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx3HdmiColorimetrySetting(void)
{
    if((GET_COLOR_SPACE(_D3_INPUT_PORT) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(_D3_INPUT_PORT) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(_D3_INPUT_PORT) == _COLOR_SPACE_YCBCR444))
    {
        switch(ScalerTMDSRx3HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY))
        {
            case _AVI_COLORIMETRY_00:

                DebugMessageRx3("Get Colorimetry YCC_SMPTE_170M", 0x00);

                g_pstDigitalColorInfo[3].b4DigitalColorimetryPreValue = _AVI_COLORIMETRY_00;

                SET_COLORIMETRY(_D3_INPUT_PORT, _COLORIMETRY_YCC_SMPTE_170M);

                break;

            case _AVI_COLORIMETRY_01:

                DebugMessageRx3("Get Colorimetry YCC_SMPTE_170M", 0x00);

                g_pstDigitalColorInfo[3].b4DigitalColorimetryPreValue = _AVI_COLORIMETRY_01;

                SET_COLORIMETRY(_D3_INPUT_PORT, _COLORIMETRY_YCC_SMPTE_170M);

                break;

            case _AVI_COLORIMETRY_10:

                DebugMessageRx3("Get Colorimetry 709", 0x00);

                g_pstDigitalColorInfo[3].b4DigitalColorimetryPreValue = _AVI_COLORIMETRY_10;

                SET_COLORIMETRY(_D3_INPUT_PORT, _COLORIMETRY_YCC_ITUR_BT709);

                break;

            case _AVI_COLORIMETRY_11:

                DebugMessageRx3("Get Colorimetry Extended", 0x00);

                g_pstDigitalColorInfo[3].b4DigitalColorimetryPreValue = _AVI_COLORIMETRY_11;

                SET_COLORIMETRY(_D3_INPUT_PORT, _COLORIMETRY_EXT);

                ScalerSyncTMDSRx3HdmiColorimetryExtSetting();

                break;

            default:

                DebugMessageRx3("Get Colorimetry INTO_DEFAULT", 0x00);

                break;
        }
    }
    else if(GET_COLOR_SPACE(_D3_INPUT_PORT) == _COLOR_SPACE_RGB)
    {
        g_pstDigitalColorInfo[3].b4DigitalColorimetryPreValue = ScalerTMDSRx3HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY);

        switch(g_pstDigitalColorInfo[3].b4DigitalColorimetryPreValue)
        {
            case _AVI_COLORIMETRY_00:

                DebugMessageRx3("Get Colorimetry RGB_SRGB", 0x00);

                SET_COLORIMETRY(_D3_INPUT_PORT, _COLORIMETRY_RGB_SRGB);

                break;

            case _AVI_COLORIMETRY_11:

                DebugMessageRx3("Get Colorimetry Extended", 0x00);

                SET_COLORIMETRY(_D3_INPUT_PORT, _COLORIMETRY_EXT);

                ScalerSyncTMDSRx3HdmiColorimetryExtSetting();

                break;

            default:

                DebugMessageRx3("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_COLORIMETRY(_D3_INPUT_PORT, _COLORIMETRY_RGB_SRGB);

                break;
        }
    }
}

//--------------------------------------------------
// Description  : TMDS Rx3 Colorimetry Extended Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx3HdmiColorimetryExtSetting(void)
{
    if((GET_COLOR_SPACE(_D3_INPUT_PORT) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(_D3_INPUT_PORT) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(_D3_INPUT_PORT) == _COLOR_SPACE_YCBCR444))
    {
        // Get extended colorimetry
        g_pstDigitalColorInfo[3].b4DigitalColorimetryExtPreValue = ScalerTMDSRx3HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY);

        // Get extended colorimetry
        switch(g_pstDigitalColorInfo[3].b4DigitalColorimetryExtPreValue)
        {
            case _AVI_COLORIMETRY_EXT_000:

                DebugMessageRx3("Get Colorimetry EXT_YCC_XVYCC601", 0x00);

                SET_EXT_COLORIMETRY(_D3_INPUT_PORT, _COLORIMETRY_EXT_YCC_XVYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_001:

                DebugMessageRx3("Get Colorimetry EXT_YCC_XVYCC709", 0x00);

                SET_EXT_COLORIMETRY(_D3_INPUT_PORT, _COLORIMETRY_EXT_YCC_XVYCC709);

                break;

            case _AVI_COLORIMETRY_EXT_010:

                DebugMessageRx3("Get Colorimetry EXT_YCC_SYCC601", 0x00);

                SET_EXT_COLORIMETRY(_D3_INPUT_PORT, _COLORIMETRY_EXT_YCC_SYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_011:

                DebugMessageRx3("Get Colorimetry EXT_YCC_ADOBEYCC601", 0x00);

                SET_EXT_COLORIMETRY(_D3_INPUT_PORT, _COLORIMETRY_EXT_YCC_ADOBEYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_101:

                DebugMessageRx3("Get Colorimetry EXT_YCC_ITUR_BT2020_CL", 0x00);

                SET_EXT_COLORIMETRY(_D3_INPUT_PORT, _COLORIMETRY_EXT_YCC_ITUR_BT2020_CL);

                break;

            case _AVI_COLORIMETRY_EXT_110:

                DebugMessageRx3("Get Colorimetry EXT_YCC_ITUR_BT2020_NCL", 0x00);

                SET_EXT_COLORIMETRY(_D3_INPUT_PORT, _COLORIMETRY_EXT_YCC_ITUR_BT2020_NCL);

                break;

            default:

                DebugMessageRx3("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_EXT_COLORIMETRY(_D3_INPUT_PORT, _COLORIMETRY_EXT_RESERVED);

                break;
        }
    }
    else if(GET_COLOR_SPACE(_D3_INPUT_PORT) == _COLOR_SPACE_RGB)
    {
        g_pstDigitalColorInfo[3].b4DigitalColorimetryExtPreValue = ScalerTMDSRx3HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY);

        switch(g_pstDigitalColorInfo[3].b4DigitalColorimetryExtPreValue)
        {
            case _AVI_COLORIMETRY_EXT_100:

                DebugMessageRx3("Get Colorimetry EXT_RGB_ADOBERGB", 0x00);

                SET_EXT_COLORIMETRY(_D3_INPUT_PORT, _COLORIMETRY_EXT_RGB_ADOBERGB);

                break;

            case _AVI_COLORIMETRY_EXT_110:

                DebugMessageRx3("Get Colorimetry EXT_RGB_ITUR_BT2020", 0x00);

                SET_EXT_COLORIMETRY(_D3_INPUT_PORT, _COLORIMETRY_EXT_RGB_ITUR_BT2020);

                break;

            default:

                DebugMessageRx3("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_EXT_COLORIMETRY(_D3_INPUT_PORT, _COLORIMETRY_EXT_RESERVED);

                break;
        }
    }
}
#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) || (_YCC_QUANTIZATION_RANGE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : TMDS Rx3 Quantization Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx3HdmiQuantizationSetting(void)
{
    if((GET_COLOR_SPACE(_D3_INPUT_PORT) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(_D3_INPUT_PORT) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(_D3_INPUT_PORT) == _COLOR_SPACE_YCBCR444))
    {
        g_pstDigitalColorInfo[3].b2DigitalQuantizationPreValue = ScalerTMDSRx3HdmiGetAVIInfo(_AVI_INFO_YCC_QUANTIZATION);

        switch(g_pstDigitalColorInfo[3].b2DigitalQuantizationPreValue)
        {
            case _AVI_YCC_QUANTIZATION_FULL:

                DebugMessageRx3("Get YCC FULL RANGE", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(_D3_INPUT_PORT, _YCC_QUANTIZATION_FULL_RANGE);

                break;

            case _AVI_YCC_QUANTIZATION_LIMITED:

                DebugMessageRx3("Get YCC LIMIT RANGE", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(_D3_INPUT_PORT, _YCC_QUANTIZATION_LIMIT_RANGE);

                break;

            default:

                DebugMessageRx3("Get YCC RANGE Error", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(_D3_INPUT_PORT, _YCC_QUANTIZATION_FULL_RANGE);

                break;
        }
    }
    else if(GET_COLOR_SPACE(_D3_INPUT_PORT) == _COLOR_SPACE_RGB)
    {
        switch(ScalerTMDSRx3HdmiGetAVIInfo(_AVI_INFO_RGB_QUANTIZATION))
        {
            case _AVI_RGB_QUANTIZATION_LIMITED:

                DebugMessageRx3("Get RGB LIMIT RANGE", 0x00);

                g_pstDigitalColorInfo[3].b2DigitalQuantizationPreValue = _AVI_RGB_QUANTIZATION_LIMITED;

                SET_COLOR_RGB_QUANTIZATION_RANGE(_D3_INPUT_PORT, _RGB_QUANTIZATION_LIMIT_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_FULL:

                DebugMessageRx3("Get RGB FULL RANGE", 0x00);

                g_pstDigitalColorInfo[3].b2DigitalQuantizationPreValue = _AVI_RGB_QUANTIZATION_FULL;

                SET_COLOR_RGB_QUANTIZATION_RANGE(_D3_INPUT_PORT, _RGB_QUANTIZATION_FULL_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_DEFAULT:

                DebugMessageRx3("Get RGB DEFAULT RANGE", 0x00);

                g_pstDigitalColorInfo[3].b2DigitalQuantizationPreValue = _AVI_RGB_QUANTIZATION_DEFAULT;

                SET_COLOR_RGB_QUANTIZATION_RANGE(_D3_INPUT_PORT, _RGB_QUANTIZATION_DEFAULT_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_RESERVED:

                DebugMessageRx3("Get RGB RESERVED RANGE", 0x00);

                g_pstDigitalColorInfo[3].b2DigitalQuantizationPreValue = _AVI_RGB_QUANTIZATION_RESERVED;

                SET_COLOR_RGB_QUANTIZATION_RANGE(_D3_INPUT_PORT, _RGB_QUANTIZATION_RESERVED);

                break;

            default:

                DebugMessageRx3("Get RGB RANGE Error", 0x00);

                g_pstDigitalColorInfo[3].b2DigitalQuantizationPreValue = _AVI_RGB_QUANTIZATION_FULL;

                SET_COLOR_RGB_QUANTIZATION_RANGE(_D3_INPUT_PORT, _RGB_QUANTIZATION_FULL_RANGE);

                break;
        }
    }
}
#endif

//--------------------------------------------------
// Description  : TMDS Rx3 HDMI ColorInfo Changed Detect
// Input Value  : None
// Output Value : Changed ==> _TRUE; No Changed ==> _FALSE;
//--------------------------------------------------
bit ScalerSyncTMDSRx3HdmiColorInfoChanged(void)
{
    BYTE pucTemp[2];
    memset(&pucTemp, 0, sizeof(pucTemp));

    // Check Color Space
    if(ScalerTMDSRx3HdmiGetAVIInfo(_AVI_INFO_COLOR_SPACE) != GET_COLOR_SPACE(_D3_INPUT_PORT))
    {
        DebugMessageRx3("Color Space Changed", 0x00);
        return _TRUE;
    }

    // Check Colorimetry
    if(ScalerTMDSRx3HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY) != g_pstDigitalColorInfo[3].b4DigitalColorimetryPreValue)
    {
        DebugMessageRx3("Colorimetry Changed", 0x00);

        if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
        {
            pucTemp[0] = ScalerTMDSRx3HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY);

            pucTemp[1] = g_pstDigitalColorInfo[3].b4DigitalColorimetryPreValue;

            ScalerSyncTMDSRx3HdmiColorimetrySetting();

            if((GET_COLOR_SPACE(_D3_INPUT_PORT) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(_D3_INPUT_PORT) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(_D3_INPUT_PORT) == _COLOR_SPACE_YCBCR444))
            {
                if(!(((pucTemp[0] == _AVI_COLORIMETRY_00) && (pucTemp[1] == _AVI_COLORIMETRY_01)) || ((pucTemp[0] == _AVI_COLORIMETRY_01) && (pucTemp[1] == _AVI_COLORIMETRY_00))))
                {
                    SET_DIGITAL_COLORIMETRY_CHANGED(_D3_INPUT_PORT);
                }
            }
            else if(GET_COLOR_SPACE(_D3_INPUT_PORT) == _COLOR_SPACE_RGB)
            {
                if((pucTemp[0] == _AVI_COLORIMETRY_11) || (pucTemp[1] == _AVI_COLORIMETRY_11))
                {
                    SET_DIGITAL_COLORIMETRY_CHANGED(_D3_INPUT_PORT);
                }
            }
        }
        else
        {
            return _TRUE;
        }
    }
    else
    {
        if(GET_COLORIMETRY(_D3_INPUT_PORT) == _COLORIMETRY_EXT)
        {
            if(ScalerTMDSRx3HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY) != g_pstDigitalColorInfo[3].b4DigitalColorimetryExtPreValue)
            {
                DebugMessageRx3("Ext Colorimetry Changed", 0x00);

                if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
                {
                    pucTemp[0] = ScalerTMDSRx3HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY);

                    pucTemp[1] = g_pstDigitalColorInfo[3].b4DigitalColorimetryExtPreValue;

                    ScalerSyncTMDSRx3HdmiColorimetryExtSetting();

                    if((GET_COLOR_SPACE(_D3_INPUT_PORT) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(_D3_INPUT_PORT) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(_D3_INPUT_PORT) == _COLOR_SPACE_YCBCR444))
                    {
                        if(!(((pucTemp[0] == _AVI_COLORIMETRY_EXT_100) && (pucTemp[1] == _AVI_COLORIMETRY_EXT_111)) || ((pucTemp[1] == _AVI_COLORIMETRY_EXT_100) && (pucTemp[0] == _AVI_COLORIMETRY_EXT_111))))
                        {
                            SET_DIGITAL_COLORIMETRY_EXT_CHANGED(_D3_INPUT_PORT);
                        }
                    }
                    else if(GET_COLOR_SPACE(_D3_INPUT_PORT) == _COLOR_SPACE_RGB)
                    {
                        if(!(((pucTemp[0] != _AVI_COLORIMETRY_EXT_100) && (pucTemp[0] != _AVI_COLORIMETRY_EXT_110)) && ((pucTemp[1] != _AVI_COLORIMETRY_EXT_100) && (pucTemp[1] != _AVI_COLORIMETRY_EXT_110))))
                        {
                            SET_DIGITAL_COLORIMETRY_EXT_CHANGED(_D3_INPUT_PORT);
                        }
                    }
                }
                else
                {
                    return _TRUE;
                }
            }
        }
    }

#if(_YCC_QUANTIZATION_RANGE_SUPPORT == _ON)
    if((GET_COLOR_SPACE(_D3_INPUT_PORT) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(_D3_INPUT_PORT) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(_D3_INPUT_PORT) == _COLOR_SPACE_YCBCR444))
    {
        if(ScalerTMDSRx3HdmiGetAVIInfo(_AVI_INFO_YCC_QUANTIZATION) != g_pstDigitalColorInfo[3].b2DigitalQuantizationPreValue)
        {
            DebugMessageRx3("YCC Quantization Range Changed", 0x00);

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
            {
                pucTemp[0] = ScalerTMDSRx3HdmiGetAVIInfo(_AVI_INFO_YCC_QUANTIZATION);

                pucTemp[1] = g_pstDigitalColorInfo[3].b2DigitalQuantizationPreValue;

                ScalerSyncTMDSRx3HdmiQuantizationSetting();

                if((pucTemp[0] == _AVI_YCC_QUANTIZATION_LIMITED) || (pucTemp[1] == _AVI_YCC_QUANTIZATION_LIMITED))
                {
                    SET_DIGITAL_QUANTIZATION_CHANGED(_D3_INPUT_PORT);
                }
            }
            else
            {
                return _TRUE;
            }
        }
    }
#endif

#if(_RGB_QUANTIZATION_RANGE_SUPPORT == _ON)
    if(GET_COLOR_SPACE(_D3_INPUT_PORT) == _COLOR_SPACE_RGB)
    {
        if(ScalerTMDSRx3HdmiGetAVIInfo(_AVI_INFO_RGB_QUANTIZATION) != g_pstDigitalColorInfo[3].b2DigitalQuantizationPreValue)
        {
            DebugMessageRx3("RGB Quantization Range Changed", 0x00);

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
            {
                ScalerSyncTMDSRx3HdmiQuantizationSetting();

                SET_DIGITAL_QUANTIZATION_CHANGED(_D3_INPUT_PORT);
            }
            else
            {
                return _TRUE;
            }
        }
    }
#endif

    return _FALSE;
}
#endif

#if(_D4_HDMI_EXIST == _ON)
#if(_D4_INPUT_PORT_TYPE != _D4_DUAL_DVI_PORT)
//--------------------------------------------------
// Description  : TMDS Rx4 Video Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx4HdmiVideoSetting(void)
{
    if(GET_HDMI_RX4_AVI_INFO_FRAME_RECEIVED() == _TRUE)
    {
        // Color Space Auto/ Pixel Repetition auto mode
        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_51_PORT_PAGE73_HDMI_ACRCR, ~(_BIT6 | _BIT2), (_BIT6 | _BIT2));

        pData[0] = ScalerTMDSRx4HdmiGetAVIInfo(_AVI_INFO_COLOR_SPACE);

        // Get Color Space
        if(pData[0] == _AVI_COLOR_SPACE_00)
        {
            // Color Space RGB
            DebugMessageRx4("Get Color Space RGB", pData[0]);
            SET_COLOR_SPACE(_D4_INPUT_PORT, _COLOR_SPACE_RGB);
        }
        else if(pData[0] == _AVI_COLOR_SPACE_01)
        {
            // YCC422
            DebugMessageRx4("Get Color Space YUV422", pData[0]);
            SET_COLOR_SPACE(_D4_INPUT_PORT, _COLOR_SPACE_YCBCR422);
        }
        else if(pData[0] == _AVI_COLOR_SPACE_11)
        {
            // YCC420
            DebugMessageRx4("Get Color Space YUV420", pData[0]);
            SET_COLOR_SPACE(_D4_INPUT_PORT, _COLOR_SPACE_YCBCR420);
        }
        else
        {
            // YCC444
            DebugMessageRx4("Get Color Space YUV444", pData[0]);
            SET_COLOR_SPACE(_D4_INPUT_PORT, _COLOR_SPACE_YCBCR444);
        }

        // Set Pixel Repetition
        switch(ScalerTMDSRx4HdmiGetAVIInfo(_AVI_INFO_PIXEL_REPETITION))
        {
            case _AVI_PIXEL_REPETITION_0:

                DebugMessageRx4("Get Pixel Repetition 0", 0x00);
                SET_TMDS_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

                break;

            case _AVI_PIXEL_REPETITION_1:

                DebugMessageRx4("Get Pixel Repetition 1", 0x00);
                SET_TMDS_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_1);

                break;

            case _AVI_PIXEL_REPETITION_2:

                DebugMessageRx4("Get Pixel Repetition 2", 0x00);
                SET_TMDS_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_2);

                break;

            case _AVI_PIXEL_REPETITION_3:

                DebugMessageRx4("Get Pixel Repetition 3", 0x00);
                SET_TMDS_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_3);

                break;

            case _AVI_PIXEL_REPETITION_4:

                DebugMessageRx4("Get Pixel Repetition 4", 0x00);
                SET_TMDS_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_4);

                break;

            case _AVI_PIXEL_REPETITION_5:

                DebugMessageRx4("Get Pixel Repetition 5", 0x00);
                SET_TMDS_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_5);

                break;

            default:

                DebugMessageRx4("Get Pixel Repetition Error", 0x00);
                SET_TMDS_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

                break;
        }

        // Set Colorimetry
        ScalerSyncTMDSRx4HdmiColorimetrySetting();

        // Set Quantization
#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) || (_YCC_QUANTIZATION_RANGE_SUPPORT == _ON))
        ScalerSyncTMDSRx4HdmiQuantizationSetting();
#endif
    }
    else    // No Info Frame Received
    {
#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
        if(GET_TMDS_RX4_CLK_MODE() == _TMDS_MHL_PPMODE_PHY_SETTING)
        {
            SET_COLOR_SPACE(_D4_INPUT_PORT, _COLOR_SPACE_YCBCR422);
            SET_COLOR_YCC_QUANTIZATION_RANGE(_D4_INPUT_PORT, _YCC_QUANTIZATION_LIMIT_RANGE);

            // Manual Set Color Space to YCbCr422 and disable pixel repetition
            ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_51_PORT_PAGE73_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT3);
        }
        else
#endif

        {
            SET_COLOR_SPACE(_D4_INPUT_PORT, _COLOR_SPACE_RGB);
            SET_COLOR_RGB_QUANTIZATION_RANGE(_D4_INPUT_PORT, _RGB_QUANTIZATION_RESERVED);

            // Manual Set Color Space to RGB and disable pixel repetition
            ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_51_PORT_PAGE73_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);
        }

        // Disable down sampling
        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_50_PORT_PAGE73_HDMI_VCR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        SET_TMDS_RX4_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

        // Waiting for down sampling  effect
        ScalerTimerDelayXms(20);
    }

    ScalerTMDSRx4SetPorchColor(GET_COLOR_SPACE(_D4_INPUT_PORT));
}
#endif

//--------------------------------------------------
// Description  : TMDS Rx4 Colorimetry Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx4HdmiColorimetrySetting(void)
{
    if((GET_COLOR_SPACE(_D4_INPUT_PORT) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(_D4_INPUT_PORT) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(_D4_INPUT_PORT) == _COLOR_SPACE_YCBCR444))
    {
        switch(ScalerTMDSRx4HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY))
        {
            case _AVI_COLORIMETRY_00:

                DebugMessageRx4("Get Colorimetry YCC_SMPTE_170M", 0x00);

                g_pstDigitalColorInfo[4].b4DigitalColorimetryPreValue = _AVI_COLORIMETRY_00;

                SET_COLORIMETRY(_D4_INPUT_PORT, _COLORIMETRY_YCC_SMPTE_170M);

                break;

            case _AVI_COLORIMETRY_01:

                DebugMessageRx4("Get Colorimetry YCC_SMPTE_170M", 0x00);

                g_pstDigitalColorInfo[4].b4DigitalColorimetryPreValue = _AVI_COLORIMETRY_01;

                SET_COLORIMETRY(_D4_INPUT_PORT, _COLORIMETRY_YCC_SMPTE_170M);

                break;

            case _AVI_COLORIMETRY_10:

                DebugMessageRx4("Get Colorimetry 709", 0x00);

                g_pstDigitalColorInfo[4].b4DigitalColorimetryPreValue = _AVI_COLORIMETRY_10;

                SET_COLORIMETRY(_D4_INPUT_PORT, _COLORIMETRY_YCC_ITUR_BT709);

                break;

            case _AVI_COLORIMETRY_11:

                DebugMessageRx4("Get Colorimetry Extended", 0x00);

                g_pstDigitalColorInfo[4].b4DigitalColorimetryPreValue = _AVI_COLORIMETRY_11;

                SET_COLORIMETRY(_D4_INPUT_PORT, _COLORIMETRY_EXT);

                ScalerSyncTMDSRx4HdmiColorimetryExtSetting();

                break;

            default:

                DebugMessageRx4("Get Colorimetry INTO_DEFAULT", 0x00);

                break;
        }
    }
    else if(GET_COLOR_SPACE(_D4_INPUT_PORT) == _COLOR_SPACE_RGB)
    {
        g_pstDigitalColorInfo[4].b4DigitalColorimetryPreValue = ScalerTMDSRx4HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY);

        switch(g_pstDigitalColorInfo[4].b4DigitalColorimetryPreValue)
        {
            case _AVI_COLORIMETRY_00:

                DebugMessageRx4("Get Colorimetry RGB_SRGB", 0x00);

                SET_COLORIMETRY(_D4_INPUT_PORT, _COLORIMETRY_RGB_SRGB);

                break;

            case _AVI_COLORIMETRY_11:

                DebugMessageRx4("Get Colorimetry Extended", 0x00);

                SET_COLORIMETRY(_D4_INPUT_PORT, _COLORIMETRY_EXT);

                ScalerSyncTMDSRx4HdmiColorimetryExtSetting();

                break;

            default:

                DebugMessageRx4("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_COLORIMETRY(_D4_INPUT_PORT, _COLORIMETRY_RGB_SRGB);

                break;
        }
    }
}

//--------------------------------------------------
// Description  : TMDS Rx4 Colorimetry Extended Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx4HdmiColorimetryExtSetting(void)
{
    if((GET_COLOR_SPACE(_D4_INPUT_PORT) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(_D4_INPUT_PORT) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(_D4_INPUT_PORT) == _COLOR_SPACE_YCBCR444))
    {
        // Get extended colorimetry
        g_pstDigitalColorInfo[4].b4DigitalColorimetryExtPreValue = ScalerTMDSRx4HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY);

        // Get extended colorimetry
        switch(g_pstDigitalColorInfo[4].b4DigitalColorimetryExtPreValue)
        {
            case _AVI_COLORIMETRY_EXT_000:

                DebugMessageRx4("Get Colorimetry EXT_YCC_XVYCC601", 0x00);

                SET_EXT_COLORIMETRY(_D4_INPUT_PORT, _COLORIMETRY_EXT_YCC_XVYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_001:

                DebugMessageRx4("Get Colorimetry EXT_YCC_XVYCC709", 0x00);

                SET_EXT_COLORIMETRY(_D4_INPUT_PORT, _COLORIMETRY_EXT_YCC_XVYCC709);

                break;

            case _AVI_COLORIMETRY_EXT_010:

                DebugMessageRx4("Get Colorimetry EXT_YCC_SYCC601", 0x00);

                SET_EXT_COLORIMETRY(_D4_INPUT_PORT, _COLORIMETRY_EXT_YCC_SYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_011:

                DebugMessageRx4("Get Colorimetry EXT_YCC_ADOBEYCC601", 0x00);

                SET_EXT_COLORIMETRY(_D4_INPUT_PORT, _COLORIMETRY_EXT_YCC_ADOBEYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_101:

                DebugMessageRx4("Get Colorimetry EXT_YCC_ITUR_BT2020_CL", 0x00);

                SET_EXT_COLORIMETRY(_D4_INPUT_PORT, _COLORIMETRY_EXT_YCC_ITUR_BT2020_CL);

                break;

            case _AVI_COLORIMETRY_EXT_110:

                DebugMessageRx4("Get Colorimetry EXT_YCC_ITUR_BT2020_NCL", 0x00);

                SET_EXT_COLORIMETRY(_D4_INPUT_PORT, _COLORIMETRY_EXT_YCC_ITUR_BT2020_NCL);

                break;

            default:

                DebugMessageRx4("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_EXT_COLORIMETRY(_D4_INPUT_PORT, _COLORIMETRY_EXT_RESERVED);

                break;
        }
    }
    else if(GET_COLOR_SPACE(_D4_INPUT_PORT) == _COLOR_SPACE_RGB)
    {
        g_pstDigitalColorInfo[4].b4DigitalColorimetryExtPreValue = ScalerTMDSRx4HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY);

        switch(g_pstDigitalColorInfo[4].b4DigitalColorimetryExtPreValue)
        {
            case _AVI_COLORIMETRY_EXT_100:

                DebugMessageRx4("Get Colorimetry EXT_RGB_ADOBERGB", 0x00);

                SET_EXT_COLORIMETRY(_D4_INPUT_PORT, _COLORIMETRY_EXT_RGB_ADOBERGB);

                break;

            case _AVI_COLORIMETRY_EXT_110:

                DebugMessageRx4("Get Colorimetry EXT_RGB_ITUR_BT2020", 0x00);

                SET_EXT_COLORIMETRY(_D4_INPUT_PORT, _COLORIMETRY_EXT_RGB_ITUR_BT2020);

                break;

            default:

                DebugMessageRx4("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_EXT_COLORIMETRY(_D4_INPUT_PORT, _COLORIMETRY_EXT_RESERVED);

                break;
        }
    }
}
#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) || (_YCC_QUANTIZATION_RANGE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : TMDS Rx4 Quantization Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx4HdmiQuantizationSetting(void)
{
    if((GET_COLOR_SPACE(_D4_INPUT_PORT) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(_D4_INPUT_PORT) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(_D4_INPUT_PORT) == _COLOR_SPACE_YCBCR444))
    {
        g_pstDigitalColorInfo[4].b2DigitalQuantizationPreValue = ScalerTMDSRx4HdmiGetAVIInfo(_AVI_INFO_YCC_QUANTIZATION);

        switch(g_pstDigitalColorInfo[4].b2DigitalQuantizationPreValue)
        {
            case _AVI_YCC_QUANTIZATION_FULL:

                DebugMessageRx4("Get YCC FULL RANGE", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(_D4_INPUT_PORT, _YCC_QUANTIZATION_FULL_RANGE);

                break;

            case _AVI_YCC_QUANTIZATION_LIMITED:

                DebugMessageRx4("Get YCC LIMIT RANGE", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(_D4_INPUT_PORT, _YCC_QUANTIZATION_LIMIT_RANGE);

                break;

            default:

                DebugMessageRx4("Get YCC RANGE Error", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(_D4_INPUT_PORT, _YCC_QUANTIZATION_FULL_RANGE);

                break;
        }
    }
    else if(GET_COLOR_SPACE(_D4_INPUT_PORT) == _COLOR_SPACE_RGB)
    {
        switch(ScalerTMDSRx4HdmiGetAVIInfo(_AVI_INFO_RGB_QUANTIZATION))
        {
            case _AVI_RGB_QUANTIZATION_LIMITED:

                DebugMessageRx4("Get RGB LIMIT RANGE", 0x00);

                g_pstDigitalColorInfo[4].b2DigitalQuantizationPreValue = _AVI_RGB_QUANTIZATION_LIMITED;

                SET_COLOR_RGB_QUANTIZATION_RANGE(_D4_INPUT_PORT, _RGB_QUANTIZATION_LIMIT_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_FULL:

                DebugMessageRx4("Get RGB FULL RANGE", 0x00);

                g_pstDigitalColorInfo[4].b2DigitalQuantizationPreValue = _AVI_RGB_QUANTIZATION_FULL;

                SET_COLOR_RGB_QUANTIZATION_RANGE(_D4_INPUT_PORT, _RGB_QUANTIZATION_FULL_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_DEFAULT:

                DebugMessageRx4("Get RGB DEFAULT RANGE", 0x00);

                g_pstDigitalColorInfo[4].b2DigitalQuantizationPreValue = _AVI_RGB_QUANTIZATION_DEFAULT;

                SET_COLOR_RGB_QUANTIZATION_RANGE(_D4_INPUT_PORT, _RGB_QUANTIZATION_DEFAULT_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_RESERVED:

                DebugMessageRx4("Get RGB RESERVED RANGE", 0x00);

                g_pstDigitalColorInfo[4].b2DigitalQuantizationPreValue = _AVI_RGB_QUANTIZATION_RESERVED;

                SET_COLOR_RGB_QUANTIZATION_RANGE(_D4_INPUT_PORT, _RGB_QUANTIZATION_RESERVED);

                break;

            default:

                DebugMessageRx4("Get RGB RANGE Error", 0x00);

                g_pstDigitalColorInfo[4].b2DigitalQuantizationPreValue = _AVI_RGB_QUANTIZATION_FULL;

                SET_COLOR_RGB_QUANTIZATION_RANGE(_D4_INPUT_PORT, _RGB_QUANTIZATION_FULL_RANGE);

                break;
        }
    }
}
#endif

//--------------------------------------------------
// Description  : TMDS Rx4 HDMI ColorInfo Changed Detect
// Input Value  : None
// Output Value : Changed ==> _TRUE; No Changed ==> _FALSE;
//--------------------------------------------------
bit ScalerSyncTMDSRx4HdmiColorInfoChanged(void)
{
    BYTE pucTemp[2];
    memset(&pucTemp, 0, sizeof(pucTemp));

    // Check Color Space
    if(ScalerTMDSRx4HdmiGetAVIInfo(_AVI_INFO_COLOR_SPACE) != GET_COLOR_SPACE(_D4_INPUT_PORT))
    {
        DebugMessageRx4("Color Space Changed", 0x00);
        return _TRUE;
    }

    // Check Colorimetry
    if(ScalerTMDSRx4HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY) != g_pstDigitalColorInfo[4].b4DigitalColorimetryPreValue)
    {
        DebugMessageRx4("Colorimetry Changed", 0x00);

        if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
        {
            pucTemp[0] = ScalerTMDSRx4HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY);

            pucTemp[1] = g_pstDigitalColorInfo[4].b4DigitalColorimetryPreValue;

            ScalerSyncTMDSRx4HdmiColorimetrySetting();

            if((GET_COLOR_SPACE(_D4_INPUT_PORT) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(_D4_INPUT_PORT) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(_D4_INPUT_PORT) == _COLOR_SPACE_YCBCR444))
            {
                if(!(((pucTemp[0] == _AVI_COLORIMETRY_00) && (pucTemp[1] == _AVI_COLORIMETRY_01)) || ((pucTemp[0] == _AVI_COLORIMETRY_01) && (pucTemp[1] == _AVI_COLORIMETRY_00))))
                {
                    SET_DIGITAL_COLORIMETRY_CHANGED(_D4_INPUT_PORT);
                }
            }
            else if(GET_COLOR_SPACE(_D4_INPUT_PORT) == _COLOR_SPACE_RGB)
            {
                if((pucTemp[0] == _AVI_COLORIMETRY_11) || (pucTemp[1] == _AVI_COLORIMETRY_11))
                {
                    SET_DIGITAL_COLORIMETRY_CHANGED(_D4_INPUT_PORT);
                }
            }
        }
        else
        {
            return _TRUE;
        }
    }
    else
    {
        if(GET_COLORIMETRY(_D4_INPUT_PORT) == _COLORIMETRY_EXT)
        {
            if(ScalerTMDSRx4HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY) != g_pstDigitalColorInfo[4].b4DigitalColorimetryExtPreValue)
            {
                DebugMessageRx4("Ext Colorimetry Changed", 0x00);

                if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
                {
                    pucTemp[0] = ScalerTMDSRx4HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY);

                    pucTemp[1] = g_pstDigitalColorInfo[4].b4DigitalColorimetryExtPreValue;

                    ScalerSyncTMDSRx4HdmiColorimetryExtSetting();

                    if((GET_COLOR_SPACE(_D4_INPUT_PORT) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(_D4_INPUT_PORT) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(_D4_INPUT_PORT) == _COLOR_SPACE_YCBCR444))
                    {
                        if(!(((pucTemp[0] == _AVI_COLORIMETRY_EXT_100) && (pucTemp[1] == _AVI_COLORIMETRY_EXT_111)) || ((pucTemp[1] == _AVI_COLORIMETRY_EXT_100) && (pucTemp[0] == _AVI_COLORIMETRY_EXT_111))))
                        {
                            SET_DIGITAL_COLORIMETRY_EXT_CHANGED(_D4_INPUT_PORT);
                        }
                    }
                    else if(GET_COLOR_SPACE(_D4_INPUT_PORT) == _COLOR_SPACE_RGB)
                    {
                        if(!(((pucTemp[0] != _AVI_COLORIMETRY_EXT_100) && (pucTemp[0] != _AVI_COLORIMETRY_EXT_110)) && ((pucTemp[1] != _AVI_COLORIMETRY_EXT_100) && (pucTemp[1] != _AVI_COLORIMETRY_EXT_110))))
                        {
                            SET_DIGITAL_COLORIMETRY_EXT_CHANGED(_D4_INPUT_PORT);
                        }
                    }
                }
                else
                {
                    return _TRUE;
                }
            }
        }
    }

#if(_YCC_QUANTIZATION_RANGE_SUPPORT == _ON)
    if((GET_COLOR_SPACE(_D4_INPUT_PORT) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(_D4_INPUT_PORT) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(_D4_INPUT_PORT) == _COLOR_SPACE_YCBCR444))
    {
        if(ScalerTMDSRx4HdmiGetAVIInfo(_AVI_INFO_YCC_QUANTIZATION) != g_pstDigitalColorInfo[4].b2DigitalQuantizationPreValue)
        {
            DebugMessageRx4("YCC Quantization Range Changed", 0x00);

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
            {
                pucTemp[0] = ScalerTMDSRx4HdmiGetAVIInfo(_AVI_INFO_YCC_QUANTIZATION);

                pucTemp[1] = g_pstDigitalColorInfo[4].b2DigitalQuantizationPreValue;

                ScalerSyncTMDSRx4HdmiQuantizationSetting();

                if((pucTemp[0] == _AVI_YCC_QUANTIZATION_LIMITED) || (pucTemp[1] == _AVI_YCC_QUANTIZATION_LIMITED))
                {
                    SET_DIGITAL_QUANTIZATION_CHANGED(_D4_INPUT_PORT);
                }
            }
            else
            {
                return _TRUE;
            }
        }
    }
#endif

#if(_RGB_QUANTIZATION_RANGE_SUPPORT == _ON)
    if(GET_COLOR_SPACE(_D4_INPUT_PORT) == _COLOR_SPACE_RGB)
    {
        if(ScalerTMDSRx4HdmiGetAVIInfo(_AVI_INFO_RGB_QUANTIZATION) != g_pstDigitalColorInfo[4].b2DigitalQuantizationPreValue)
        {
            DebugMessageRx4("RGB Quantization Range Changed", 0x00);

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
            {
                ScalerSyncTMDSRx4HdmiQuantizationSetting();

                SET_DIGITAL_QUANTIZATION_CHANGED(_D4_INPUT_PORT);
            }
            else
            {
                return _TRUE;
            }
        }
    }
#endif

    return _FALSE;
}
#endif

#if(_D5_HDMI_EXIST == _ON)
//--------------------------------------------------
// Description  : TMDS Rx5 Video Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx5HdmiVideoSetting(void)
{
    if(GET_HDMI_RX5_AVI_INFO_FRAME_RECEIVED() == _TRUE)
    {
        // Color Space Auto/ Pixel Repetition auto mode
        ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_51_PORT_PAGE74_HDMI_ACRCR, ~(_BIT6 | _BIT2), (_BIT6 | _BIT2));

        pData[0] = ScalerTMDSRx5HdmiGetAVIInfo(_AVI_INFO_COLOR_SPACE);

        // Get Color Space
        if(pData[0] == _AVI_COLOR_SPACE_00)
        {
            // Color Space RGB
            DebugMessageRx5("Get Color Space RGB", pData[0]);
            SET_COLOR_SPACE(_D5_INPUT_PORT, _COLOR_SPACE_RGB);
        }
        else if(pData[0] == _AVI_COLOR_SPACE_01)
        {
            // YCC422
            DebugMessageRx5("Get Color Space YUV422", pData[0]);
            SET_COLOR_SPACE(_D5_INPUT_PORT, _COLOR_SPACE_YCBCR422);
        }
        else if(pData[0] == _AVI_COLOR_SPACE_11)
        {
            // YCC420
            DebugMessageRx5("Get Color Space YUV420", pData[0]);
            SET_COLOR_SPACE(_D5_INPUT_PORT, _COLOR_SPACE_YCBCR420);
        }
        else
        {
            // YCC444
            DebugMessageRx5("Get Color Space YUV444", pData[0]);
            SET_COLOR_SPACE(_D5_INPUT_PORT, _COLOR_SPACE_YCBCR444);
        }

        // Set Pixel Repetition
        switch(ScalerTMDSRx5HdmiGetAVIInfo(_AVI_INFO_PIXEL_REPETITION))
        {
            case _AVI_PIXEL_REPETITION_0:

                DebugMessageRx5("Get Pixel Repetition 0", 0x00);
                SET_TMDS_RX5_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

                break;

            case _AVI_PIXEL_REPETITION_1:

                DebugMessageRx5("Get Pixel Repetition 1", 0x00);
                SET_TMDS_RX5_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_1);

                break;

            case _AVI_PIXEL_REPETITION_2:

                DebugMessageRx5("Get Pixel Repetition 2", 0x00);
                SET_TMDS_RX5_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_2);

                break;

            case _AVI_PIXEL_REPETITION_3:

                DebugMessageRx5("Get Pixel Repetition 5", 0x00);
                SET_TMDS_RX5_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_3);

                break;

            case _AVI_PIXEL_REPETITION_4:

                DebugMessageRx5("Get Pixel Repetition 4", 0x00);
                SET_TMDS_RX5_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_4);

                break;

            case _AVI_PIXEL_REPETITION_5:

                DebugMessageRx5("Get Pixel Repetition 5", 0x00);
                SET_TMDS_RX5_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_5);

                break;

            default:

                DebugMessageRx5("Get Pixel Repetition Error", 0x00);
                SET_TMDS_RX5_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

                break;
        }

        // Set Colorimetry
        ScalerSyncTMDSRx5HdmiColorimetrySetting();

        // Set Quantization
#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) || (_YCC_QUANTIZATION_RANGE_SUPPORT == _ON))
        ScalerSyncTMDSRx5HdmiQuantizationSetting();
#endif
    }
    else    // No Info Frame Received
    {
#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
        if(GET_TMDS_RX5_CLK_MODE() == _TMDS_MHL_PPMODE_PHY_SETTING)
        {
            SET_COLOR_SPACE(_D5_INPUT_PORT, _COLOR_SPACE_YCBCR422);
            SET_COLOR_YCC_QUANTIZATION_RANGE(_D5_INPUT_PORT, _YCC_QUANTIZATION_LIMIT_RANGE);

            // Manual Set Color Space to YCbCr422 and disable pixel repetition
            ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_51_PORT_PAGE74_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), _BIT3);
        }
        else
#endif

        {
            SET_COLOR_SPACE(_D5_INPUT_PORT, _COLOR_SPACE_RGB);
            SET_COLOR_RGB_QUANTIZATION_RANGE(_D5_INPUT_PORT, _RGB_QUANTIZATION_RESERVED);

            // Manual Set Color Space to RGB and disable pixel repetition
            ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_51_PORT_PAGE74_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);
        }

        // Disable down sampling
        ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_50_PORT_PAGE74_HDMI_VCR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        SET_TMDS_RX5_AVI_PIXEL_REPETITION(_AVI_PIXEL_REPETITION_0);

        // Waiting for down sampling  effect
        ScalerTimerDelayXms(20);
    }

    ScalerTMDSRx5SetPorchColor(GET_COLOR_SPACE(_D5_INPUT_PORT));
}

//--------------------------------------------------
// Description  : TMDS Rx5 Colorimetry Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx5HdmiColorimetrySetting(void)
{
    if((GET_COLOR_SPACE(_D5_INPUT_PORT) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(_D5_INPUT_PORT) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(_D5_INPUT_PORT) == _COLOR_SPACE_YCBCR444))
    {
        switch(ScalerTMDSRx5HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY))
        {
            case _AVI_COLORIMETRY_00:

                DebugMessageRx5("Get Colorimetry YCC_SMPTE_170M", 0x00);

                g_pstDigitalColorInfo[5].b4DigitalColorimetryPreValue = _AVI_COLORIMETRY_00;

                SET_COLORIMETRY(_D5_INPUT_PORT, _COLORIMETRY_YCC_SMPTE_170M);

                break;

            case _AVI_COLORIMETRY_01:

                DebugMessageRx5("Get Colorimetry YCC_SMPTE_170M", 0x00);

                g_pstDigitalColorInfo[5].b4DigitalColorimetryPreValue = _AVI_COLORIMETRY_01;

                SET_COLORIMETRY(_D5_INPUT_PORT, _COLORIMETRY_YCC_SMPTE_170M);

                break;

            case _AVI_COLORIMETRY_10:

                DebugMessageRx5("Get Colorimetry 709", 0x00);

                g_pstDigitalColorInfo[5].b4DigitalColorimetryPreValue = _AVI_COLORIMETRY_10;

                SET_COLORIMETRY(_D5_INPUT_PORT, _COLORIMETRY_YCC_ITUR_BT709);

                break;

            case _AVI_COLORIMETRY_11:

                DebugMessageRx5("Get Colorimetry Extended", 0x00);

                g_pstDigitalColorInfo[5].b4DigitalColorimetryPreValue = _AVI_COLORIMETRY_11;

                SET_COLORIMETRY(_D5_INPUT_PORT, _COLORIMETRY_EXT);

                ScalerSyncTMDSRx5HdmiColorimetryExtSetting();

                break;

            default:

                DebugMessageRx5("Get Colorimetry INTO_DEFAULT", 0x00);

                break;
        }
    }
    else if(GET_COLOR_SPACE(_D5_INPUT_PORT) == _COLOR_SPACE_RGB)
    {
        g_pstDigitalColorInfo[5].b4DigitalColorimetryPreValue = ScalerTMDSRx5HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY);

        switch(g_pstDigitalColorInfo[5].b4DigitalColorimetryPreValue)
        {
            case _AVI_COLORIMETRY_00:

                DebugMessageRx5("Get Colorimetry RGB_SRGB", 0x00);

                SET_COLORIMETRY(_D5_INPUT_PORT, _COLORIMETRY_RGB_SRGB);

                break;

            case _AVI_COLORIMETRY_11:

                DebugMessageRx5("Get Colorimetry Extended", 0x00);

                SET_COLORIMETRY(_D5_INPUT_PORT, _COLORIMETRY_EXT);

                ScalerSyncTMDSRx5HdmiColorimetryExtSetting();

                break;

            default:

                DebugMessageRx5("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_COLORIMETRY(_D5_INPUT_PORT, _COLORIMETRY_RGB_SRGB);

                break;
        }
    }
}

//--------------------------------------------------
// Description  : TMDS Rx5 Colorimetry Extended Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx5HdmiColorimetryExtSetting(void)
{
    if((GET_COLOR_SPACE(_D5_INPUT_PORT) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(_D5_INPUT_PORT) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(_D5_INPUT_PORT) == _COLOR_SPACE_YCBCR444))
    {
        // Get extended colorimetry
        g_pstDigitalColorInfo[5].b4DigitalColorimetryExtPreValue = ScalerTMDSRx5HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY);

        // Get extended colorimetry
        switch(g_pstDigitalColorInfo[5].b4DigitalColorimetryExtPreValue)
        {
            case _AVI_COLORIMETRY_EXT_000:

                DebugMessageRx5("Get Colorimetry EXT_YCC_XVYCC601", 0x00);

                SET_EXT_COLORIMETRY(_D5_INPUT_PORT, _COLORIMETRY_EXT_YCC_XVYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_001:

                DebugMessageRx5("Get Colorimetry EXT_YCC_XVYCC709", 0x00);

                SET_EXT_COLORIMETRY(_D5_INPUT_PORT, _COLORIMETRY_EXT_YCC_XVYCC709);

                break;

            case _AVI_COLORIMETRY_EXT_010:

                DebugMessageRx5("Get Colorimetry EXT_YCC_SYCC601", 0x00);

                SET_EXT_COLORIMETRY(_D5_INPUT_PORT, _COLORIMETRY_EXT_YCC_SYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_011:

                DebugMessageRx5("Get Colorimetry EXT_YCC_ADOBEYCC601", 0x00);

                SET_EXT_COLORIMETRY(_D5_INPUT_PORT, _COLORIMETRY_EXT_YCC_ADOBEYCC601);

                break;

            case _AVI_COLORIMETRY_EXT_101:

                DebugMessageRx5("Get Colorimetry EXT_YCC_ITUR_BT2020_CL", 0x00);

                SET_EXT_COLORIMETRY(_D5_INPUT_PORT, _COLORIMETRY_EXT_YCC_ITUR_BT2020_CL);

                break;

            case _AVI_COLORIMETRY_EXT_110:

                DebugMessageRx5("Get Colorimetry EXT_YCC_ITUR_BT2020_NCL", 0x00);

                SET_EXT_COLORIMETRY(_D5_INPUT_PORT, _COLORIMETRY_EXT_YCC_ITUR_BT2020_NCL);

                break;

            default:

                DebugMessageRx5("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_EXT_COLORIMETRY(_D5_INPUT_PORT, _COLORIMETRY_EXT_RESERVED);

                break;
        }
    }
    else if(GET_COLOR_SPACE(_D5_INPUT_PORT) == _COLOR_SPACE_RGB)
    {
        g_pstDigitalColorInfo[5].b4DigitalColorimetryExtPreValue = ScalerTMDSRx5HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY);

        switch(g_pstDigitalColorInfo[5].b4DigitalColorimetryExtPreValue)
        {
            case _AVI_COLORIMETRY_EXT_100:

                DebugMessageRx5("Get Colorimetry EXT_RGB_ADOBERGB", 0x00);

                SET_EXT_COLORIMETRY(_D5_INPUT_PORT, _COLORIMETRY_EXT_RGB_ADOBERGB);

                break;

            case _AVI_COLORIMETRY_EXT_110:

                DebugMessageRx5("Get Colorimetry EXT_RGB_ITUR_BT2020", 0x00);

                SET_EXT_COLORIMETRY(_D5_INPUT_PORT, _COLORIMETRY_EXT_RGB_ITUR_BT2020);

                break;

            default:

                DebugMessageRx5("Get Colorimetry INTO_DEFAULT", 0x00);

                SET_EXT_COLORIMETRY(_D5_INPUT_PORT, _COLORIMETRY_EXT_RESERVED);

                break;
        }
    }
}
#if((_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) || (_YCC_QUANTIZATION_RANGE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : TMDS Rx5 Quantization Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncTMDSRx5HdmiQuantizationSetting(void)
{
    if((GET_COLOR_SPACE(_D5_INPUT_PORT) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(_D5_INPUT_PORT) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(_D5_INPUT_PORT) == _COLOR_SPACE_YCBCR444))
    {
        g_pstDigitalColorInfo[5].b2DigitalQuantizationPreValue = ScalerTMDSRx5HdmiGetAVIInfo(_AVI_INFO_YCC_QUANTIZATION);

        switch(g_pstDigitalColorInfo[5].b2DigitalQuantizationPreValue)
        {
            case _AVI_YCC_QUANTIZATION_FULL:

                DebugMessageRx5("Get YCC FULL RANGE", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(_D5_INPUT_PORT, _YCC_QUANTIZATION_FULL_RANGE);

                break;

            case _AVI_YCC_QUANTIZATION_LIMITED:

                DebugMessageRx5("Get YCC LIMIT RANGE", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(_D5_INPUT_PORT, _YCC_QUANTIZATION_LIMIT_RANGE);

                break;

            default:

                DebugMessageRx5("Get YCC RANGE Error", 0x00);

                SET_COLOR_YCC_QUANTIZATION_RANGE(_D5_INPUT_PORT, _YCC_QUANTIZATION_FULL_RANGE);

                break;
        }
    }
    else if(GET_COLOR_SPACE(_D5_INPUT_PORT) == _COLOR_SPACE_RGB)
    {
        switch(ScalerTMDSRx5HdmiGetAVIInfo(_AVI_INFO_RGB_QUANTIZATION))
        {
            case _AVI_RGB_QUANTIZATION_LIMITED:

                DebugMessageRx5("Get RGB LIMIT RANGE", 0x00);

                g_pstDigitalColorInfo[5].b2DigitalQuantizationPreValue = _AVI_RGB_QUANTIZATION_LIMITED;

                SET_COLOR_RGB_QUANTIZATION_RANGE(_D5_INPUT_PORT, _RGB_QUANTIZATION_LIMIT_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_FULL:

                DebugMessageRx5("Get RGB FULL RANGE", 0x00);

                g_pstDigitalColorInfo[5].b2DigitalQuantizationPreValue = _AVI_RGB_QUANTIZATION_FULL;

                SET_COLOR_RGB_QUANTIZATION_RANGE(_D5_INPUT_PORT, _RGB_QUANTIZATION_FULL_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_DEFAULT:

                DebugMessageRx5("Get RGB DEFAULT RANGE", 0x00);

                g_pstDigitalColorInfo[5].b2DigitalQuantizationPreValue = _AVI_RGB_QUANTIZATION_DEFAULT;

                SET_COLOR_RGB_QUANTIZATION_RANGE(_D5_INPUT_PORT, _RGB_QUANTIZATION_DEFAULT_RANGE);

                break;

            case _AVI_RGB_QUANTIZATION_RESERVED:

                DebugMessageRx5("Get RGB RESERVED RANGE", 0x00);

                g_pstDigitalColorInfo[5].b2DigitalQuantizationPreValue = _AVI_RGB_QUANTIZATION_RESERVED;

                SET_COLOR_RGB_QUANTIZATION_RANGE(_D5_INPUT_PORT, _RGB_QUANTIZATION_RESERVED);

                break;

            default:

                DebugMessageRx5("Get RGB RANGE Error", 0x00);

                g_pstDigitalColorInfo[5].b2DigitalQuantizationPreValue = _AVI_RGB_QUANTIZATION_FULL;

                SET_COLOR_RGB_QUANTIZATION_RANGE(_D5_INPUT_PORT, _RGB_QUANTIZATION_FULL_RANGE);

                break;
        }
    }
}
#endif

//--------------------------------------------------
// Description  : TMDS Rx5 HDMI ColorInfo Changed Detect
// Input Value  : None
// Output Value : Changed ==> _TRUE; No Changed ==> _FALSE;
//--------------------------------------------------
bit ScalerSyncTMDSRx5HdmiColorInfoChanged(void)
{
    BYTE pucTemp[2];
    memset(&pucTemp, 0, sizeof(pucTemp));

    // Check Color Space
    if(ScalerTMDSRx5HdmiGetAVIInfo(_AVI_INFO_COLOR_SPACE) != GET_COLOR_SPACE(_D5_INPUT_PORT))
    {
        DebugMessageRx5("Color Space Changed", 0x00);
        return _TRUE;
    }

    // Check Colorimetry
    if(ScalerTMDSRx5HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY) != g_pstDigitalColorInfo[5].b4DigitalColorimetryPreValue)
    {
        DebugMessageRx5("Colorimetry Changed", 0x00);

        if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
        {
            pucTemp[0] = ScalerTMDSRx5HdmiGetAVIInfo(_AVI_INFO_COLORIMETRY);

            pucTemp[1] = g_pstDigitalColorInfo[5].b4DigitalColorimetryPreValue;

            ScalerSyncTMDSRx5HdmiColorimetrySetting();

            if((GET_COLOR_SPACE(_D5_INPUT_PORT) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(_D5_INPUT_PORT) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(_D5_INPUT_PORT) == _COLOR_SPACE_YCBCR444))
            {
                if(!(((pucTemp[0] == _AVI_COLORIMETRY_00) && (pucTemp[1] == _AVI_COLORIMETRY_01)) || ((pucTemp[0] == _AVI_COLORIMETRY_01) && (pucTemp[1] == _AVI_COLORIMETRY_00))))
                {
                    SET_DIGITAL_COLORIMETRY_CHANGED(_D5_INPUT_PORT);
                }
            }
            else if(GET_COLOR_SPACE(_D5_INPUT_PORT) == _COLOR_SPACE_RGB)
            {
                if((pucTemp[0] == _AVI_COLORIMETRY_11) || (pucTemp[1] == _AVI_COLORIMETRY_11))
                {
                    SET_DIGITAL_COLORIMETRY_CHANGED(_D5_INPUT_PORT);
                }
            }
        }
        else
        {
            return _TRUE;
        }
    }
    else
    {
        if(GET_COLORIMETRY(_D5_INPUT_PORT) == _COLORIMETRY_EXT)
        {
            if(ScalerTMDSRx5HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY) != g_pstDigitalColorInfo[5].b4DigitalColorimetryExtPreValue)
            {
                DebugMessageRx5("Ext Colorimetry Changed", 0x00);

                if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
                {
                    pucTemp[0] = ScalerTMDSRx5HdmiGetAVIInfo(_AVI_INFO_EXTENDED_COLORIMETRY);

                    pucTemp[1] = g_pstDigitalColorInfo[5].b4DigitalColorimetryExtPreValue;

                    ScalerSyncTMDSRx5HdmiColorimetryExtSetting();

                    if((GET_COLOR_SPACE(_D5_INPUT_PORT) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(_D5_INPUT_PORT) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(_D5_INPUT_PORT) == _COLOR_SPACE_YCBCR444))
                    {
                        if(!(((pucTemp[0] == _AVI_COLORIMETRY_EXT_100) && (pucTemp[1] == _AVI_COLORIMETRY_EXT_111)) || ((pucTemp[1] == _AVI_COLORIMETRY_EXT_100) && (pucTemp[0] == _AVI_COLORIMETRY_EXT_111))))
                        {
                            SET_DIGITAL_COLORIMETRY_EXT_CHANGED(_D5_INPUT_PORT);
                        }
                    }
                    else if(GET_COLOR_SPACE(_D5_INPUT_PORT) == _COLOR_SPACE_RGB)
                    {
                        if(!(((pucTemp[0] != _AVI_COLORIMETRY_EXT_100) && (pucTemp[0] != _AVI_COLORIMETRY_EXT_110)) && ((pucTemp[1] != _AVI_COLORIMETRY_EXT_100) && (pucTemp[1] != _AVI_COLORIMETRY_EXT_110))))
                        {
                            SET_DIGITAL_COLORIMETRY_EXT_CHANGED(_D5_INPUT_PORT);
                        }
                    }
                }
                else
                {
                    return _TRUE;
                }
            }
        }
    }

#if(_YCC_QUANTIZATION_RANGE_SUPPORT == _ON)
    if((GET_COLOR_SPACE(_D5_INPUT_PORT) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(_D5_INPUT_PORT) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(_D5_INPUT_PORT) == _COLOR_SPACE_YCBCR444))
    {
        if(ScalerTMDSRx5HdmiGetAVIInfo(_AVI_INFO_YCC_QUANTIZATION) != g_pstDigitalColorInfo[5].b2DigitalQuantizationPreValue)
        {
            DebugMessageRx5("YCC Quantization Range Changed", 0x00);

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
            {
                pucTemp[0] = ScalerTMDSRx5HdmiGetAVIInfo(_AVI_INFO_YCC_QUANTIZATION);

                pucTemp[1] = g_pstDigitalColorInfo[5].b2DigitalQuantizationPreValue;

                ScalerSyncTMDSRx5HdmiQuantizationSetting();

                if((pucTemp[0] == _AVI_YCC_QUANTIZATION_LIMITED) || (pucTemp[1] == _AVI_YCC_QUANTIZATION_LIMITED))
                {
                    SET_DIGITAL_QUANTIZATION_CHANGED(_D5_INPUT_PORT);
                }
            }
            else
            {
                return _TRUE;
            }
        }
    }
#endif

#if(_RGB_QUANTIZATION_RANGE_SUPPORT == _ON)
    if(GET_COLOR_SPACE(_D5_INPUT_PORT) == _COLOR_SPACE_RGB)
    {
        if(ScalerTMDSRx5HdmiGetAVIInfo(_AVI_INFO_RGB_QUANTIZATION) != g_pstDigitalColorInfo[5].b2DigitalQuantizationPreValue)
        {
            DebugMessageRx5("RGB Quantization Range Changed", 0x00);

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
            {
                ScalerSyncTMDSRx5HdmiQuantizationSetting();

                SET_DIGITAL_QUANTIZATION_CHANGED(_D5_INPUT_PORT);
            }
            else
            {
                return _TRUE;
            }
        }
    }
#endif

    return _FALSE;
}
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Digital Get Colorimetry Changed
// Input Value  : EnumSourceSearchPort
// Output Value : Changed ==> _TRUE; No Changed ==> _FALSE;
//--------------------------------------------------
bit ScalerSyncDigitalGetColorimetryChanged(EnumSourceSearchPort enumSourceSearchPort)
{
    return GET_DIGITAL_COLORIMETRY_CHANGED(enumSourceSearchPort);
}

//--------------------------------------------------
// Description  : Digital Get Colorimetry Extended Changed
// Input Value  : EnumSourceSearchPort
// Output Value : Changed ==> _TRUE; No Changed ==> _FALSE;
//--------------------------------------------------
bit ScalerSyncDigitalGetColorimetryExtChanged(EnumSourceSearchPort enumSourceSearchPort)
{
    return GET_DIGITAL_COLORIMETRY_EXT_CHANGED(enumSourceSearchPort);
}

//--------------------------------------------------
// Description  : Digital Get Quantization Changed
// Input Value  : EnumSourceSearchPort
// Output Value : Changed ==> _TRUE; No Changed ==> _FALSE;
//--------------------------------------------------
bit ScalerSyncDigitalGetQuantizationChanged(EnumSourceSearchPort enumSourceSearchPort)
{
    return GET_DIGITAL_QUANTIZATION_CHANGED(enumSourceSearchPort);
}

//--------------------------------------------------
// Description  : Digital Clr Colorimetry Changed
// Input Value  : EnumSourceSearchPort
// Output Value : None
//--------------------------------------------------
void ScalerSyncDigitalClrColorimetryChanged(EnumSourceSearchPort enumSourceSearchPort)
{
    CLR_DIGITAL_COLORIMETRY_CHANGED(enumSourceSearchPort);
}

//--------------------------------------------------
// Description  : Digital Clr Colorimetry Extended Changed
// Input Value  : EnumSourceSearchPort
// Output Value : None
//--------------------------------------------------
void ScalerSyncDigitalClrColorimetryExtChanged(EnumSourceSearchPort enumSourceSearchPort)
{
    CLR_DIGITAL_COLORIMETRY_EXT_CHANGED(enumSourceSearchPort);
}

//--------------------------------------------------
// Description  : Digital Clr Quantization Changed
// Input Value  : EnumSourceSearchPort
// Output Value : None
//--------------------------------------------------
void ScalerSyncDigitalClrQuantizationChanged(EnumSourceSearchPort enumSourceSearchPort)
{
    CLR_DIGITAL_QUANTIZATION_CHANGED(enumSourceSearchPort);
}
#endif
