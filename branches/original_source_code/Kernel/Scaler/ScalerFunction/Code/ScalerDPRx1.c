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
// ID Code      : ScalerDPRx1.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DPRX1__

#include "ScalerFunctionInclude.h"

#if(_D1_DP_EXIST == _ON)

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
bit g_bDpRx1PSAuxToggle = _FALSE;

// Add for DPCD 2002h Bug
bit g_bDpRx1PowerStateIntoPS = _FALSE;
bit g_bDpRx1AuxCommandNoReply = _FALSE;

BYTE g_ucDpRx1LinkStatus01;
BYTE g_ucDpRx1LinkStatus23;
BYTE g_ucDpRx1LinkRequest01;
BYTE g_ucDpRx1LinkRequest23;
BYTE g_ucDpRx1Temp;
BYTE g_ucDpRx1Info;
BYTE g_ucDpRx1MSAFailMacRsetCount;
BYTE g_ucDpRx1LinkRate;
BYTE g_ucDpRx1LaneCount;
BYTE g_ucDpRx1TrainingPatternSet;

BYTE g_ucDpRx1EQCRC;
BYTE g_ucRx1AuxTemp;
BYTE g_ucRx1AuxTemp_EXINT;
WORD g_usDpRx1Vfrontporch;
EnumDisplayDataPath g_enumDPRx1IrqForceBackgrd;
StructDpLanesMapping g_stDpRx1LanesMapping;

#if(_DP_MST_SUPPORT == _ON)
StructDPRxMiscInfo g_stDpRx1MiscInfo;
BYTE g_pucDpRx1MstTimeSlotBackup[13];
bit g_bDpMSTRx1BackupLinkStatusFlg_INT;
BYTE g_pucDpRx1LinkStatusBackup_INT[2];
#endif

#if(_DP_TX_SUPPORT == _ON)
bit g_bDpRx1HdcpAksvWritten = 0;
WORD g_usDpRx1HdcpKsvFifoOffset;
WORD g_usDpRx1MstToSstVfrontporch;
StructDPRxHDCPAuthInfo g_stDpRx1HDCPAuthInfo;
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
BYTE g_pucDPRx1Caps[3];
#endif

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
bit g_bDpRx1VscSdpColorMode;

#if(_HW_DP_VSC_SDP_REG_SUPPORT != _ON)
bit g_bDpRx1RSV1PacketDetecting;

#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
bit g_bDpRx1MstToSstRSV1PacketDetecting;
#endif
#endif
#endif

#if(_ULTRA_HDR_SUPPORT == _ON)
BYTE g_pucDPRx1HDRBackup[_HW_DP_INFOFRAME_RSV0_LENGTH];
BYTE g_pucDPRx1RSV0Backup[_HW_DP_INFOFRAME_RSV0_LENGTH];
StructDPInfoFrameRSV0Ctrl g_stDPRx1InfoFrameRSV0Ctrl;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
//--------------------------------------------------
void ScalerDpRx1Initial(EnumDpVersionType enumDpVersion, EnumDpLaneCount enumDpLaneCount, EnumDPMSTPort enumDpRxMstPort, EnumDisplayMode enumDisplayMode);
void ScalerDpRx1SetDpLaneMapping(BYTE ucLanetype);
void ScalerDpRx1DpcdInitial(EnumDpVersionType enumDpVersion, EnumDpLaneCount enumDpLaneCount, EnumDPMSTPort enumDpRxMstPort, EnumDisplayMode enumDisplayMode);
void ScalerDpRx1InterfaceInitial(void);
void ScalerDpRx1ChangeDpcdVersion(EnumDpVersionType enumDpVersion, EnumDPMSTPort enumDpRxMstPort);
void ScalerDpRx1DpcdLinkStatusReset(EnumDpResetStatus enumDpResetStatus);

#if(_WD_TIMER_INT_SUPPORT == _ON)
void ScalerDpRx1DpcdLinkStatusReset_WDINT(void);
#endif

void ScalerDpRx1HotPlugEvent(EnumDpHotPlugAssertType enumHpdType);
bit ScalerDpRx1MarginLinkCheck(void);
void ScalerDpRx1LinkStatusIRQ(void);
void ScalerDpRx1HotPlugDuration(WORD usMs);
void ScalerDpRx1MacInitial(void);
void ScalerDpRx1SecDataBlockReset(void);
BYTE ScalerDpRx1TrainingPattern1_EXINT0(EnumDpLinkTrainingType enumDpLtType);
BYTE ScalerDpRx1TrainingPattern2_EXINT0(EnumDpLinkTrainingType enumDpLtType);
void ScalerDpRx1TrainingPatternEnd_EXINT0(void);
BYTE ScalerDpRx1Tp1Check_EXINT0(EnumDpLinkTrainingType enumDpLtType);
BYTE ScalerDpRx1Tp2Check_EXINT0(EnumDpLinkTrainingType enumDpLtType);
bit ScalerDpRx1AlignCheck(void);
bit ScalerDpRx1DecodeCheck(void);
bit ScalerDpRx1DFECheck(void);
bit ScalerDpRx1SignalCheck(BYTE ucDpLinkRate, BYTE ucDpcdLane);
BYTE ScalerDpRx1DFECheck_EXINT0(void);

#if(_WD_TIMER_INT_SUPPORT == _ON)
BYTE ScalerDpRx1DFECheck_WDINT(void);
#endif

bit ScalerDpRx1GetVideoStream(void);
bit ScalerDpRx1MSACheck(void);
bit ScalerDpRx1MiscCheck(void);

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
bit ScalerDpRx1VscCheck(void);

#if(_HW_DP_VSC_SDP_REG_SUPPORT != _ON)
void ScalerDpRx1RSV1PacketDetectEvent(void);
void ScalerDpRx1SetInitialRSV1InfoType(void);
#endif
#endif
bit ScalerDpRx1MSAActiveChange(void);
void ScalerDpRx1AVMute(void);

#if(_DP_TX_SUPPORT == _ON)
void ScalerDpRx1UpdateSinkCount(void);
#endif

#if(_WD_TIMER_INT_SUPPORT == _ON)
void ScalerDpRx1WDTimerEventProc_WDINT(EnumScalerWDTimerEventID enumEventID);
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
WORD ScalerDpRx1GetBStoHSDelay(WORD usDpHtotal);
WORD ScalerDpRx1GetVFreq(void);
WORD ScalerDpRx1GetVPeriod(void);
WORD ScalerDpRx1GetHPeriod(void);
WORD ScalerDpRx1GetHSW(void);
bit ScalerDpRx1GetFREESYNCStatusChange(void);
BYTE ScalerDpRx1GetAmdSpdInfo(EnumAmdSpdInfoContent enumContent);
BYTE ScalerDpRx1GetAmdSpdBackupInfo(EnumAmdSpdInfoContent enumContent);
#endif

#if(_ULTRA_HDR_SUPPORT == _ON)
void ScalerDpRx1InfoFrameRSV0Check(void);
void ScalerDpRx1RSV0PacketDetectEvent(void);
void ScalerDpRx1GetInfoFrameRSV0(BYTE *pucDPRx1RSV0Data);
#endif

void ScalerDpRx1SetInitialRSV0InfoType(void);
DWORD ScalerDpRx1GetBStoVSDelay(void);
bit ScalerDpRx1InterlaceCheck(WORD *pusVTotal, BYTE *pucOddFlg);
bit ScalerDpRx1GetVideoInfo(void);
void ScalerDpRx1SetColorInfo(void);
void ScalerDpRx1VideoSetting(void);
void ScalerDpRx1ColorimetrySetting(BYTE ucInputPort, BYTE ucColorimetryValue);
#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
void ScalerDpRx1ColorimetryExtSetting(BYTE ucInputPort, BYTE ucColorimetryValue);
#endif
void ScalerDpRx1QuantizationSetting(BYTE ucInputPort, BYTE ucQuantizationValue);

bit ScalerDpRx1StreamClkRegenerate(void);
void ScalerDpRx1AdjustVsyncDelay(void);
void ScalerDpRx1SinkStatusSet(EnumDpSinkReceivePort enumReceiverPort, EnumDpSinkStatus enumInSync);
void ScalerDpRx1SinkStatusSet_EXINT0(EnumDpSinkReceivePort enumReceiverPort, EnumDpSinkStatus enumInSync);
void ScalerDpRx1CrcCalculate(void);
#if(_HW_HS_TRACKING_GEN_TYPE == _HS_TRACKING_GEN_2)
void ScalerDpRx1HSActiveTrackingMode(EnumDpHSTrackingType enumHSTrackingType);
#endif
void ScalerDpRx1CheckHdcpCpirqStatus(void);
bit ScalerDpRx1HdcpCheck(void);
bit ScalerDpRx1HdcpReAuthStatusCheck(void);
bit ScalerDpRx1HdcpMeasureCheck(void);
void ScalerDpRx1CpIRQ(EnumDpRxBStatusType enumBStatusType);
bit ScalerDpRx1HdcpEnebled(void);
BYTE ScalerDpRx1GetDpcdInfo(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
BYTE ScalerDpRx1GetDpcdBitInfo(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit);
BYTE ScalerDpRx1GetDpcdInfo_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
BYTE ScalerDpRx1GetDpcdBitInfo_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit);
void ScalerDpRx1SetDpcdValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
void ScalerDpRx1SetDpcdBitValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucNotDpcdBit, BYTE ucDpcdBit);
void ScalerDpRx1SetDpcdValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
void ScalerDpRx1SetDpcdBitValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucNotDpcdBit, BYTE ucDpcdBit);

#if(_WD_TIMER_INT_SUPPORT == _ON)
BYTE ScalerDpRx1GetDpcdInfo_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
void ScalerDpRx1SetDpcdValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
#endif

#if(_DP_ASSR_MODE_SUPPORT == _ON)
void ScalerDpRx1ASSRModeSetting(void);
#endif

bit ScalerDpRx1NormalPreDetect(void);
BYTE ScalerDpRx1ScanInputPort(void);
bit ScalerDpRx1PSPreDetect(void);
bit ScalerDpRx1StableDetect(void);
void ScalerDpRx1HPDPowerOfftoNormalProc(BYTE ucDpHotPlugDCOffHighStatus);
bit ScalerDpRx1CheckVgipVsBypass(void);

#if(_DP_MST_SUPPORT == _ON)

bit ScalerDpRx1LTStatusCheck(void);
void ScalerDpRx1AuxChPowerStatusCheck(bit bCableStatus);
void ScalerDpRx1MstInfoBackup(EnumDpMstBackup enumDpMstBackup);
void ScalerDpRx1MstReset(void);

#if(_DP_TX_SUPPORT == _ON)
void ScalerDpRx1HDCPHandler(void);
void ScalerDpRx1HDCPChangeAuthState(EnumDPRxHDCPAuthState enumHDCPAuthState);
void ScalerDpRx1HDCPSetRepeaterProcTimeout(void);
void ScalerDpRx1HDCPSetReadIrqTimeout(void);
void ScalerDpRx1HDCPEnableReadIrq(bit bEnable);
bit ScalerDpRx1HDCPCheckBinfo(void);
void ScalerDpRx1HDCPLoadKsvFifo(void);
void ScalerDpRx1HDCPSetKsvFifoFirst(void);
void ScalerDpRx1HDCPWriteShaInput(void);
void ScalerDpRx1HDCPAuthShaRun(bit bIsFirst);
void ScalerDpRx1HDCPLoadShaToDpcd(void);

#if(_D1_DP_MST_PORT_SUPPORT == _ON)
void ScalerDpRx1HDCPResetKsvFifoToFirst_EXINT0(void);
void ScalerDpRx1HDCPSetKsvFifo_EXINT0(void);

#if(_WD_TIMER_INT_SUPPORT == _ON)
void ScalerDpRx1HDCPResetDpcdInfo_WDINT(void);
#endif

void ScalerDpRx1HDCPResetDpcdInfo_EXINT0(void);
void ScalerDpRx1HDCPBlockReset(void);
#endif

bit ScalerDpRx1HDCPCheckLvp(void);
void ScalerDpRx1HDCPFakeAuthenProc(void);
void ScalerDpRx1HDCPSha1Calculate(BYTE *pucInputArray, BYTE ucCalCount);

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
#if(_HW_DP_VSC_SDP_REG_SUPPORT != _ON)
void ScalerDpRx1MstToSstRSV1PacketDetectEvent(void);
#endif
#endif

#endif
#endif // #if(_DP_MST_SUPPORT == _ON)

bit ScalerDpRx1ValidSignalDetectionDCOnCheck(void);

#if(_DP_TX_SUPPORT == _ON)
void ScalerDpRx1MstToSstProc(void);
void ScalerDpRx1MstToSstSetColorInfo(void);
bit ScalerDpRx1MstToSstStableDetect(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : Initial Setting for DP
// Input Value  : _DP_VERSION_1_1 or _DP_VERSION_1_2
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1Initial(EnumDpVersionType enumDpVersion, EnumDpLaneCount enumDpLaneCount, EnumDPMSTPort enumDpRxMstPort, EnumDisplayMode enumDisplayMode)
{
    ScalerDpRx1AuxIntInitial();

    ScalerDpRx1DpcdInitial(enumDpVersion, enumDpLaneCount, enumDpRxMstPort, enumDisplayMode);

#if(_DP_ASSR_MODE_SUPPORT == _ON)
    SET_DP_RX1_AUX_MANUAL_MODE();
    ScalerDpRx1SetDpcdValue(0x00, 0x01, 0x0A, 0x00);
    SET_DP_RX1_AUX_AUTO_MODE();
#endif

    SET_DP_RX1_LINK_TRAINING_STATUS(_DP_LINK_TRAINING_NONE);

    SET_DP_RX1_FAKE_LINK_TRAINING();

    CLR_DP_RX_D1_MARGIN_LINK_HBR_RBR();

    SET_DP_RX_TARGET_MST_PORT(enumDpRxMstPort);
    SET_DP_RX_D1_PORT_TARGET_VERSION(enumDpVersion);
    SET_DP_RX_D1_PORT_TARGET_LANE_COUNT(enumDpLaneCount);

    ScalerDpRx1SetDpLaneMapping(_DP_LANE_MAPPING_NORMAL_TYPE);

#if(_DP_MST_SUPPORT == _ON)
    CLR_DP_RX1_CHECK_AUX_CH_NO_POWER_DEBOUNCE();
    CLR_DP_RX1_CHECK_AUX_CH_POWER_OFF();
#endif

#if(_DP_TX_SUPPORT == _ON)
    CLR_DP_RX1_HDCP_AUTH_AKSV_WRITTEN();
#endif
}

//--------------------------------------------------
// Description  : Set DP Lane Mapping Type
// Input Value  : ucLanetype --> Lane Mapping Type
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetDpLaneMapping(BYTE ucLanetype)
{
    if(ucLanetype == _DP_LANE_MAPPING_TYPE_C_ASSIGNMENT_E_TYPE)
    {
        // Lane 0 <--> Lane 2
        // Lane 1 <--> Lane 3
        SET_DP_RX1_PCB_LANE0_MAPPING(_D1_DP_PCB_LANE2_MAPPING);
        SET_DP_RX1_PCB_LANE1_MAPPING(_D1_DP_PCB_LANE3_MAPPING);
        SET_DP_RX1_PCB_LANE2_MAPPING(_D1_DP_PCB_LANE0_MAPPING);
        SET_DP_RX1_PCB_LANE3_MAPPING(_D1_DP_PCB_LANE1_MAPPING);

        if(_D1_DP_PCB_PN_SWAP == _ON)
        {
            SET_DP_RX1_PCB_PN_SWAP(_OFF);
        }
        else
        {
            SET_DP_RX1_PCB_PN_SWAP(_ON);
        }

        // Enable Aux Digital Phy Swap
        ScalerSetBit(PBA_72_AUX_DIG_PHY2, ~_BIT0, _BIT0);
    }
    else // Normal Cable Mode
    {
        SET_DP_RX1_PCB_LANE0_MAPPING(_D1_DP_PCB_LANE0_MAPPING);
        SET_DP_RX1_PCB_LANE1_MAPPING(_D1_DP_PCB_LANE1_MAPPING);
        SET_DP_RX1_PCB_LANE2_MAPPING(_D1_DP_PCB_LANE2_MAPPING);
        SET_DP_RX1_PCB_LANE3_MAPPING(_D1_DP_PCB_LANE3_MAPPING);
        SET_DP_RX1_PCB_PN_SWAP(_D1_DP_PCB_PN_SWAP);

        // Disable Aux Digital Phy PN Swap
        ScalerSetBit(PBA_72_AUX_DIG_PHY2, ~_BIT0, 0x00);
    }
}

//--------------------------------------------------
// Description  : DPCD Table Initial
// Input Value  : _DP_VERSION_1_1 or _DP_VERSION_1_2
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1DpcdInitial(EnumDpVersionType enumDpVersion, EnumDpLaneCount enumDpLaneCount, EnumDPMSTPort enumDpRxMstPort, EnumDisplayMode enumDisplayMode)
{
    enumDisplayMode = enumDisplayMode;

    ScalerDpRx1SinkStatusSet(_DP_SINK_REVEICE_PORT0, _DP_SINK_OUT_OF_SYNC);
    ScalerDpRx1SinkStatusSet(_DP_SINK_REVEICE_PORT1, _DP_SINK_OUT_OF_SYNC);

    ScalerDpRx1ChangeDpcdVersion(enumDpVersion, enumDpRxMstPort);

    // Enhanced Framing Support(Bit7) and DP Lane Count(Bit[4:0])
    pData[0] = ScalerDpRx1GetDpcdInfo(0x00, 0x00, 0x02);
    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x02, ((pData[0] & ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) | _BIT7 | enumDpLaneCount));

    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x03, 0x01);
    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x04, 0x01);
    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x06, 0x01);
    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x08, 0x02);
    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x09, 0x00);

    // Set TRAINING_AUX_RD_INTERVAL
    ScalerDpRx1SetDpcdBitValue(0x00, 0x00, 0x0E, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _DP_RX_DPCD_TRAINING_AUX_RD_INTERVAL);

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
    // Set EXTENDED_RECEIVER_CAPABILITY_FIELD_PRESENT bit
    ScalerDpRx1SetDpcdBitValue(0x00, 0x00, 0x0E, ~_BIT7, _BIT7);
#endif

#if(_AUDIO_SUPPORT == _ON)
    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x0A, 0x06);
#else
    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x0A, 0x00);
#endif

    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x0B, 0x00);

#if(_DP_ASSR_MODE_SUPPORT == _ON)
    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x0D, 0x01);
#endif

    // DPCD Link Status Field Setting
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x00, 0x41);
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x01, 0x00);
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x05, 0x00);
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x08, 0x00);
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x09, 0x00);
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x0A, 0x00);
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x0B, 0x00);
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x10, 0x00);
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x11, 0x00);
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x12, 0x00);
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x13, 0x00);
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x14, 0x00);
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x15, 0x00);
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x16, 0x00);
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x17, 0x00);
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x46, 0x20);

#if(_HDCP_2_2_FUNCTION_GEN != _GEN_NONE)
#if(_DP_HDCP_2_2_SUPPORT == _ON)

    // Load Certrx to DPCD Table
    ScalerDpRx1Hdcp2LoadCertRrxKey();
#else

    // Clear 69XXXh to 0s for avoiding SRAM initial state values remained
    for(PDATA_WORD(0) = 0x9000; PDATA_WORD(0) <= 0x951F; PDATA_WORD(0)++)
    {
        ScalerDpRx1SetDpcdValue(0x06, pData[0], pData[1], 0x00);
    }
#endif
#endif

#if((_DP_TX_SUPPORT == _ON) && (_D1_DP_MST_PORT_SUPPORT == _ON))
    // _BIT3:0, Down Stream Port Counter
    pData[0] = ScalerDpRx1GetDpcdInfo(0x00, 0x00, 0x07);
    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x07, ((pData[0] & ~(_BIT3 | _BIT2 | _BIT1 | _BIT0)) | _BIT0));

    // Down Stream Port is HPD Aware
    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x80, 0x08);

    // _BIT1: Repeater,  _BIT0: HDCP Capable
    ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x28, 0x03);

#if(_DP_HDCP_2_2_SUPPORT == _ON)

    // Set HDCP_Capable and Repeater Bit
    g_pucDPRx1Caps[0] = 0x02;
    g_pucDPRx1Caps[1] = 0x00;
    g_pucDPRx1Caps[2] = 0x02;

    // Load RxCaps to DPCD Table
    for(pData[0] = 0; pData[0] < 3; pData[0]++)
    {
        ScalerDpRx1SetDpcdValue(0x06, 0x92, (0x1D + pData[0]), g_pucDPRx1Caps[pData[0]]);
    }
#endif

#else
    // _BIT3:0, Down Stream Port Counter
    pData[0] = ScalerDpRx1GetDpcdInfo(0x00, 0x00, 0x07);
    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x07, (pData[0] & ~(_BIT3 | _BIT2 | _BIT1 | _BIT0)));

    // Down Stream Port isn't HPD Aware
    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x80, 0x00);

    // _BIT1: Repeater,  _BIT0: HDCP Capable
    ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x28, 0x01);

#if(_DP_HDCP_2_2_SUPPORT == _ON)

    // Set HDCP_Capable
    g_pucDPRx1Caps[0] = 0x02;
    g_pucDPRx1Caps[1] = 0x00;
    g_pucDPRx1Caps[2] = 0x02;

    // Load RxCaps to DPCD Table
    for(pData[0] = 0; pData[0] < 3; pData[0]++)
    {
        ScalerDpRx1SetDpcdValue(0x06, 0x92, (0x1D + pData[0]), g_pucDPRx1Caps[pData[0]]);
    }
#endif
#endif

    ScalerDpRx1HdcpCapableModify();
}

//--------------------------------------------------
// Description  : DP Rx1 Interface Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1InterfaceInitial(void)
{
    SET_DP_RX1_FAKE_LINK_TRAINING();

    SET_DP_RX1_AUX_MANUAL_MODE();

    if(GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_LINK_TRAINING_PASS)
    {
        SET_DP_RX1_LINK_TRAINING_STATUS(_DP_FAKE_LINK_TRAINING_PASS);
    }

    SET_DP_RX1_AUX_AUTO_MODE();
}

//--------------------------------------------------
// Description  : Dp Version Switch
// Input Value  : _DP_VERSION_1_1 or _DP_VERSION_1_2
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1ChangeDpcdVersion(EnumDpVersionType enumDpVersion, EnumDPMSTPort enumDpRxMstPort)
{
#if(_D1_DP_LINK_CLK_RATE == _DP_LOW_SPEED_162MHZ)
    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x01, _DP_LINK_RBR);
#elif(_D1_DP_LINK_CLK_RATE == _DP_HIGH_SPEED_270MHZ)
    ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x01, _DP_LINK_HBR);
#endif

    if(enumDpVersion >= _DP_VERSION_1_2)
    {
        // DPCD Capability Field Initial
        ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x00, enumDpVersion);

#if(_D1_DP_LINK_CLK_RATE == _DP_HIGH_SPEED2_540MHZ)
        ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x01, _DP_LINK_HBR2);
#endif

        pData[0] = ScalerDpRx1GetDpcdInfo(0x00, 0x00, 0x02);

        if(ScalerDpRx1GetDpcdInfo(0x00, 0x00, 0x01) == _DP_LINK_HBR2)
        {
            // TPS3 Support
            ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x02, ((pData[0] & ~_BIT6) | _BIT6));
        }
        else
        {
            // TPS3 NonSupport
            ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x02, (pData[0] & ~_BIT6));
        }

        // _BIT7 = 1: Always IEEE OUI Support Under DP1.2
        pData[0] = ScalerDpRx1GetDpcdInfo(0x00, 0x00, 0x07);
        ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x07, ((pData[0] & ~_BIT7) | _BIT7));

        // Sink IEEE OUI
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x00, _DP_SINK_RTK_IEEE_OUI_L);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x01, _DP_SINK_RTK_IEEE_OUI_M);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x02, _DP_SINK_RTK_IEEE_OUI_H);

        // Sink IEEE OUI LSB For DP1.2
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x03, _DP_SINK_RTK_ID_STRING_0);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x04, _DP_SINK_RTK_ID_STRING_1);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x05, _DP_SINK_RTK_ID_STRING_2);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x06, _DP_SINK_RTK_ID_STRING_3);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x07, _DP_SINK_RTK_ID_STRING_4);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x08, _DP_SINK_RTK_ID_STRING_5);

        // Sink HW/FW Version For DP1.2
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x09, _DP_SINK_RTK_HW_VERSION);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x0A, _DP_SINK_RTK_FW_VERSION_H);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x0B, _DP_SINK_RTK_FW_VERSION_L);

#if((_DP_TX_SUPPORT == _ON) && (_D1_DP_MST_PORT_SUPPORT == _ON))
        // Branch IEEE OUI
        ScalerDpRx1SetDpcdValue(0x00, 0x05, 0x00, _DP_BRANCH_RTK_IEEE_OUI_L);
        ScalerDpRx1SetDpcdValue(0x00, 0x05, 0x01, _DP_BRANCH_RTK_IEEE_OUI_M);
        ScalerDpRx1SetDpcdValue(0x00, 0x05, 0x02, _DP_BRANCH_RTK_IEEE_OUI_H);

        // Branch IEEE OUI LSB For DP1.2
        ScalerDpRx1SetDpcdValue(0x00, 0x05, 0x03, _DP_BRANCH_RTK_ID_STRING_0);
        ScalerDpRx1SetDpcdValue(0x00, 0x05, 0x04, _DP_BRANCH_RTK_ID_STRING_1);
        ScalerDpRx1SetDpcdValue(0x00, 0x05, 0x05, _DP_BRANCH_RTK_ID_STRING_2);
        ScalerDpRx1SetDpcdValue(0x00, 0x05, 0x06, _DP_BRANCH_RTK_ID_STRING_3);
        ScalerDpRx1SetDpcdValue(0x00, 0x05, 0x07, _DP_BRANCH_RTK_ID_STRING_4);
        ScalerDpRx1SetDpcdValue(0x00, 0x05, 0x08, _DP_BRANCH_RTK_ID_STRING_5);

        // Branch HW/FW Version
        ScalerDpRx1SetDpcdValue(0x00, 0x05, 0x09, _DP_BRANCH_RTK_HW_VERSION);
        ScalerDpRx1SetDpcdValue(0x00, 0x05, 0x0A, _DP_BRANCH_RTK_FW_VERSION_H);
        ScalerDpRx1SetDpcdValue(0x00, 0x05, 0x0B, _DP_BRANCH_RTK_FW_VERSION_L);
#endif

        if(enumDpRxMstPort == _DP_MST_RX1_PORT)
        {
            // Down Sream Port is Present
            ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x05, 0x01);

            ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x21, 0x01);
        }
        else
        {
            // Down Sream Port isn't Present
            ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x05, 0x00);

            ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x21, 0x00);
        }
    }
    else
    {
        // DPCD Capability Field Initial
        ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x00, 0x11);

#if(_D1_DP_LINK_CLK_RATE == _DP_HIGH_SPEED2_540MHZ)
        ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x01, _DP_LINK_HBR);
#endif

        // TPS3 NonSupport
        pData[0] = ScalerDpRx1GetDpcdInfo(0x00, 0x00, 0x02);
        ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x02, (pData[0] & ~_BIT6));

        // Back DPCD Table Address 0x00007
        pData[0] = ScalerDpRx1GetDpcdInfo(0x00, 0x00, 0x07);

#if(_DP_SINK_VER11_OUI_SUPPORT == _ON)
        // _BIT7 = 1: IEEE OUI Support
        ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x07, ((pData[0] & ~_BIT7) | _BIT7));

        // Sink IEEE OUI
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x00, _DP_SINK_RTK_IEEE_OUI_L);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x01, _DP_SINK_RTK_IEEE_OUI_M);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x02, _DP_SINK_RTK_IEEE_OUI_H);
#else
        // _BIT7 = 0: IEEE OUI Not Support
        ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x07, (pData[0] & ~_BIT7));

        // Sink IEEE OUI
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x00, 0x00);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x01, 0x00);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x02, 0x00);
#endif

        // Sink IEEE OUI LSB For DP1.1
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x03, 0x00);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x04, 0x00);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x05, 0x00);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x06, 0x00);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x07, 0x00);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x08, 0x00);

        // Sink HW/FW Version For DP1.1
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x09, 0x00);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x0A, 0x00);
        ScalerDpRx1SetDpcdValue(0x00, 0x04, 0x0B, 0x00);

#if((_DP_TX_SUPPORT == _ON) && (_D1_DP_MST_PORT_SUPPORT == _ON))
#if(_DP_SINK_VER11_OUI_SUPPORT == _ON)
        // Branch IEEE OUI
        ScalerDpRx1SetDpcdValue(0x00, 0x05, 0x00, _DP_BRANCH_RTK_IEEE_OUI_L);
        ScalerDpRx1SetDpcdValue(0x00, 0x05, 0x01, _DP_BRANCH_RTK_IEEE_OUI_M);
        ScalerDpRx1SetDpcdValue(0x00, 0x05, 0x02, _DP_BRANCH_RTK_IEEE_OUI_H);
#else
        // Branch IEEE OUI
        ScalerDpRx1SetDpcdValue(0x00, 0x05, 0x00, 0x00);
        ScalerDpRx1SetDpcdValue(0x00, 0x05, 0x01, 0x00);
        ScalerDpRx1SetDpcdValue(0x00, 0x05, 0x02, 0x00);
#endif

        // Branch IEEE OUI LSB For DP1.1
        ScalerDpRx1SetDpcdValue(0x00, 0x05, 0x03, 0x00);
        ScalerDpRx1SetDpcdValue(0x00, 0x05, 0x04, 0x00);
        ScalerDpRx1SetDpcdValue(0x00, 0x05, 0x05, 0x00);
        ScalerDpRx1SetDpcdValue(0x00, 0x05, 0x06, 0x00);
        ScalerDpRx1SetDpcdValue(0x00, 0x05, 0x07, 0x00);
        ScalerDpRx1SetDpcdValue(0x00, 0x05, 0x08, 0x00);

        // Branch HW/FW Version For DP1.1
        ScalerDpRx1SetDpcdValue(0x00, 0x05, 0x09, 0x00);
        ScalerDpRx1SetDpcdValue(0x00, 0x05, 0x0A, 0x00);
        ScalerDpRx1SetDpcdValue(0x00, 0x05, 0x0B, 0x00);
#endif

        // Down Sream Port isn't Present
        ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x05, 0x00);

        // MST Capability Disable
        ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x21, 0x00);
    }

#if((_DP_TX_SUPPORT == _ON) && (_D1_DP_MST_PORT_SUPPORT == _ON))
    ScalerDpRx1HDCPBlockReset();
#endif
}

//--------------------------------------------------
// Description  : DPCD Link Status Field Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1DpcdLinkStatusReset(EnumDpResetStatus enumDpResetStatus)
{
    pData[0] = ScalerGetByte(PBA_D0_AUX_MODE_SET);

    SET_DP_RX1_AUX_MANUAL_MODE();

    if(enumDpResetStatus == _DP_DPCD_LINK_STATUS_INITIAL)
    {
        // Set DPCD 00600h to 0x01
        ScalerDpRx1SetDpcdBitValue(0x00, 0x06, 0x00, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
    }

    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x02, 0x00);
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x03, 0x00);
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x04, 0x80);
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x05, 0x00);
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x06, 0x00);
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x07, 0x00);

    SET_DP_RX1_LINK_TRAINING_STATUS(_DP_LINK_TRAINING_NONE);

#if(_DP_MST_SUPPORT == _ON)
    CLR_DP_RX1_BACKUP_PD_LINK_STATUS_FLG();
#endif

    if((pData[0] & _BIT1) == _BIT1)
    {
        SET_DP_RX1_AUX_AUTO_MODE();
    }

#if(_DP_MST_SUPPORT == _ON)

    if(g_enumDpMSTCapablePort == _DP_MST_RX1_PORT)
    {
        pData[0] = ScalerGetByte(PBA_D0_AUX_MODE_SET);

        SET_DP_RX1_AUX_AUTO_MODE();

        pData[1] = ScalerDpRx1GetDpcdInfo(0x00, 0x20, 0x05);
        ScalerDpRx1SetDpcdValue(0x00, 0x20, 0x05, (pData[1] | _BIT1));

        ScalerDpRx1SetDpcdValue(0x00, 0x02, 0xC0, (ScalerDpRx1GetDpcdInfo(0x00, 0x02, 0xC0) & ~_BIT1));

        if((pData[0] & _BIT1) != _BIT1)
        {
            SET_DP_RX1_AUX_MANUAL_MODE();
        }
    }

#endif
}

#if(_WD_TIMER_INT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DPCD Link Status Field Reset in INT0
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1DpcdLinkStatusReset_WDINT(void) using 3
{
    pData_EXINT[0] = ScalerGetByte_EXINT(PBA_D0_AUX_MODE_SET);

    SET_DP_RX1_AUX_MANUAL_MODE_EXINT();

    if(GET_DP_RX1_LINK_TRAINING_STATUS() != _DP_FAKE_LINK_TRAINING_PASS_VBIOS)
    {
        ScalerDpRx1SetDpcdValue_WDINT(0x00, 0x01, 0x00, 0x00);
        ScalerDpRx1SetDpcdValue_WDINT(0x00, 0x01, 0x01, 0x00);
    }

    // Set DPCD 00600h to 0x01
    ScalerDpRx1SetDpcdValue_WDINT(0x00, 0x06, 0x00, 0x01);

    ScalerDpRx1SetDpcdValue_WDINT(0x00, 0x02, 0x02, 0x00);
    ScalerDpRx1SetDpcdValue_WDINT(0x00, 0x02, 0x03, 0x00);
    ScalerDpRx1SetDpcdValue_WDINT(0x00, 0x02, 0x04, 0x80);
    ScalerDpRx1SetDpcdValue_WDINT(0x00, 0x02, 0x05, 0x00);
    ScalerDpRx1SetDpcdValue_WDINT(0x00, 0x02, 0x06, 0x00);
    ScalerDpRx1SetDpcdValue_WDINT(0x00, 0x02, 0x07, 0x00);

    SET_DP_RX1_LINK_TRAINING_STATUS(_DP_LINK_TRAINING_NONE);

    if((pData_EXINT[0] & _BIT1) == _BIT1)
    {
        SET_DP_RX1_AUX_AUTO_MODE_EXINT();
    }
}
#endif

//--------------------------------------------------
// Description  : Dp HotPlug Event
// Input Value  : Hot Plug Type
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HotPlugEvent(EnumDpHotPlugAssertType enumHpdType)
{
    // ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_RX1_DP_LINK_STATUS_FAIL);

    if(enumHpdType == _DP_HPD_ASSERTED)
    {
        if(PCB_D1_HOTPLUG_DETECT() == _D1_HOT_PLUG_HIGH)
        {
            return;
        }
    }
    else
    {
        ScalerDpRx1AVMute();
    }

    if(enumHpdType == _DP_HPD_NONE)
    {
        return;
    }

    if(enumHpdType == _DP_HPD_LOW)
    {
        PCB_D1_HOTPLUG(_D1_HOT_PLUG_LOW);

        return;
    }
    else if(enumHpdType == _DP_HPD_LOW_RESET_AUX)
    {
        // Reset Aux
        ScalerSetBit(PBA_C0_DPCD_CTRL, ~_BIT7, _BIT7);

        PCB_D1_HOTPLUG(_D1_HOT_PLUG_LOW);

        return;
    }

    // Reset DDC1
    MCU_FF2D_DDC1_DDC_CONTROL_1 |= _BIT1;

    // Release Aux
    ScalerSetBit(PBA_C0_DPCD_CTRL, ~_BIT7, 0x00);

    ScalerDpRx1DpcdLinkStatusReset(_DP_DPCD_LINK_STATUS_INITIAL);

#if(_DP_FREESYNC_SUPPORT == _ON)
    SET_DP_RX1_AUX_MANUAL_MODE();
    ScalerDpRx1SetDpcdValue(0x00, 0x01, 0x07, 0x00);
    SET_DP_RX1_AUX_AUTO_MODE();
#endif

#if((_DP_TX_SUPPORT == _ON) && (_D1_DP_MST_PORT_SUPPORT == _ON))
    ScalerDpRx1HDCPBlockReset();
#endif

#if(_DP_ASSR_MODE_SUPPORT == _ON)
    SET_DP_RX1_AUX_MANUAL_MODE();
    ScalerDpRx1SetDpcdValue(0x00, 0x01, 0x0A, 0x00);
    SET_DP_RX1_AUX_AUTO_MODE();
#endif

    if(enumHpdType == _DP_LONG_HPD_EVENT)
    {
        ScalerDpRx1HotPlugDuration(800);
    }
    else if(enumHpdType == _DP_HDCP_LONG_HPD_EVENT)
    {
        ScalerDpRx1HotPlugDuration(800);
    }
    else if(enumHpdType == _DP_MST_LONG_HPD_EVENT)
    {
        // Reset Aux
        ScalerSetBit(PBA_C0_DPCD_CTRL, ~_BIT7, _BIT7);

        ScalerDpRx1HotPlugDuration(800);
    }
    else
    {
        ScalerDpRx1HotPlugDuration(0);
    }

    // Reset Aux
    ScalerSetBit(PBA_C0_DPCD_CTRL, ~_BIT7, _BIT7);

    // Release Aux
    ScalerSetBit(PBA_C0_DPCD_CTRL, ~_BIT7, 0x00);

    ScalerSetBit(PBA_D0_AUX_MODE_SET, ~_BIT1, 0x00);

    ScalerDpRx1SetDpcdValue(0x00, 0x01, 0x00, 0x00);
    ScalerDpRx1SetDpcdValue(0x00, 0x01, 0x01, (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0xE0));

    ScalerSetBit(PBA_D0_AUX_MODE_SET, ~_BIT1, _BIT1);

    if(GET_D1_CABLE_STATUS() == _TRUE)
    {
#if(_DP_MST_SUPPORT == _ON)
        ScalerTimerActiveTimerEvent(SEC(3), _SCALER_TIMER_EVENT_DP_RX1_VALID_SIGNAL_DETECT_CHECK);
#else
        ScalerTimerActiveTimerEvent(SEC(1.2), _SCALER_TIMER_EVENT_DP_RX1_VALID_SIGNAL_DETECT_CHECK);
#endif
    }
}

//--------------------------------------------------
// Description  : DP Margin Link Check
// Input Value  : None
// Output Value : _TRUE : Link ok ; _FALSE : Margin Link
//--------------------------------------------------
bit ScalerDpRx1MarginLinkCheck(void)
{
    switch(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00))
    {
        case _DP_LINK_RBR:
        case _DP_LINK_HBR:

            if((GET_DP_RX_D1_MARGIN_LINK_HBR_RBR() == _FALSE) && (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_LINK_STATUS_FAIL))
            {
                return _FALSE;
            }

            break;

        case _DP_LINK_HBR2:
            return _TRUE;
            break;

        default:
            return _TRUE;
            break;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Dp Interrupt Request
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1LinkStatusIRQ(void)
{
    SET_DP_RX1_AUX_MANUAL_MODE();

    if((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_LINK_TRAINING_FAIL) || (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_LINK_STATUS_FAIL))
    {
        if((ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) <= _DP_LINK_HBR) && (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_LINK_STATUS_FAIL))
        {
            if(GET_D1_CABLE_STATUS() == _TRUE)
            {
                SET_DP_RX_D1_MARGIN_LINK_HBR_RBR();
            }
        }

        ScalerDpRx1DpcdLinkStatusReset(_DP_DPCD_LINK_STATUS_IRQ);

        SET_DP_RX1_AUX_AUTO_MODE();

#if((_DP_TX_SUPPORT == _ON) && (_D1_DP_MST_PORT_SUPPORT == _ON))
        ScalerDpRx1HDCPBlockReset();
#endif
        if((ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) != _BIT1) &&
           (ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) != (_BIT2 | _BIT0)))
        {
            ScalerDpRx1HotPlugDuration(1);
        }
    }

    SET_DP_RX1_AUX_AUTO_MODE();
}

//--------------------------------------------------
// Description  : Hot Plug Low Pulse Duration
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HotPlugDuration(WORD usMs)
{
#if(_DP_TX_SUPPORT == _ON)
    BYTE ucBackUp1 = 0;
#endif
    BYTE ucBackUp2 = 0;

    if(GET_D1_CABLE_STATUS() == _TRUE)
    {
        if(usMs != 1)
        {
            if(usMs != 0)
            {
                PCB_D1_HOTPLUG(_D1_HOT_PLUG_LOW);
                ScalerTimerDelayXms(usMs);
            }

#if(_DP_TX_SUPPORT == _ON)
            // Update sink count
            ScalerDpRx1UpdateSinkCount();
#endif

            PCB_D1_HOTPLUG(_D1_HOT_PLUG_HIGH);
        }
        else
        {
#if(_DP_TX_SUPPORT == _ON)
            // Disable IRQs that take too long
            ucBackUp1 = ScalerGetBit(PBB_72_HPD_IRQ_EN, _BIT6);
            ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, 0x00);
#endif

            ucBackUp2 = ScalerGetByte(PBA_D0_AUX_MODE_SET);

            SET_DP_RX1_AUX_MANUAL_MODE();

            PCB_D1_HOTPLUG(_D1_HOT_PLUG_LOW);

            for(pData[0] = 0; pData[0] < 85; pData[0]++)
            {
                Delay5us(g_ucDelay5usN);
            }

            PCB_D1_HOTPLUG(_D1_HOT_PLUG_HIGH);

            if((ucBackUp2 & _BIT1) == _BIT1)
            {
                SET_DP_RX1_AUX_AUTO_MODE();
            }

#if(_DP_TX_SUPPORT == _ON)
            ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, ucBackUp1);
#endif
        }
    }
}

//--------------------------------------------------
// Description  : Dp Mac Initial Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1MacInitial(void)
{
    // Set Digital Phy to Normal
    ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);

    // Select DP
    ScalerSetBit(PB0_00_HD_DP_SEL, ~_BIT0, 0x00);

    // DP Lane Swap Setting
    ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT7 | _BIT6), _D1_DP_LANE3 << 6);
    ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT5 | _BIT4), _D1_DP_LANE2 << 4);
    ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT3 | _BIT2), _D1_DP_LANE1 << 2);
    ScalerSetBit(PB0_03_LANE_MUX, ~(_BIT1 | _BIT0), _D1_DP_LANE0);

#if(_D1_DP_PCB_PN_SWAP == _ON)
    ScalerSetBit(PB0_06_DECODE_10B8B_ERROR, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
#else
    ScalerSetBit(PB0_06_DECODE_10B8B_ERROR, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
#endif

    // DP RGB Output Enable
    ScalerSetBit(PB8_31_DP_OUTPUT_CTRL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

    // DP CLK Output Enable
    ScalerSetBit(PB8_B8_MN_SCLKG_SDM_CTRL, ~_BIT6, _BIT6);

    // 0x00:disable error correction, 0xF4:enable all error correction
    ScalerSetBit(PB9_00_MN_STRM_ATTR_CTRL, ~_BIT1, _BIT1);

    // Disable DP Fifo Under/OverFlow Watch Dog
    ScalerDpRx1SetFifoWD(_DISABLE);

    // Disable DP Fifo Under/OverFlow IRQ
    ScalerDpRx1SetFifoIRQ(_DISABLE);

    ScalerDpRx1SetInitialRSV0InfoType();

#if((_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON) && (_HW_DP_VSC_SDP_REG_SUPPORT != _ON))
    ScalerDpRx1SetInitialRSV1InfoType();
#endif

    CLR_DP_RX1_MSA_FAIL_MAC_RESET_COUNT();
}

//--------------------------------------------------
// Description  : Dp Secondary Data Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SecDataBlockReset(void)
{
    // Set S code by FW manual
    ScalerSetBit(PB9_58_SCODE_0, ~_BIT7, _BIT7);

    // Sec Data Block Reset
    ScalerSetBit(PB8_00_MAC_DIG_RESET_CTRL, ~_BIT4, _BIT4);
    ScalerSetBit(PB8_00_MAC_DIG_RESET_CTRL, ~_BIT4, 0x00);

    // Set S code by HW auto
    ScalerSetBit(PB9_58_SCODE_0, ~_BIT7, 0x00);
}

//--------------------------------------------------
// Description  : Check Dp Training Pattern 1
// Input Value  : Normal or Fake LT
// Output Value : TRUE --> TP1 Pass
//--------------------------------------------------
BYTE ScalerDpRx1TrainingPattern1_EXINT0(EnumDpLinkTrainingType enumDpLtType) using 1
{
#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
    if(ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x00, 0x0E, _BIT7) == _BIT7)
    {
        if(g_ucDpRx1LinkRate > _D1_DP_LINK_CLK_RATE)
        {
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x00);
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x00);
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x80);

            return _FALSE;
        }
    }
    else
#endif
    {
        if(g_ucDpRx1LinkRate > ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x00, 0x01))
        {
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x00);
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x00);
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x80);

            return _FALSE;
        }
    }

    if(enumDpLtType == _DP_NORMAL_LT)
    {
        ScalerDpRx1Tp1SetPhy_EXINT0(_DP_NF_REF_XTAL);
    }

    if(ScalerDpRx1Tp1Check_EXINT0(enumDpLtType) == _TRUE)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check Dp Training Pattern 2
// Input Value  : Normal or Fake LT
// Output Value : TRUE --> TP2 Pass
//--------------------------------------------------
BYTE ScalerDpRx1TrainingPattern2_EXINT0(EnumDpLinkTrainingType enumDpLtType) using 1
{
    if(enumDpLtType == _DP_NORMAL_LT)
    {
        if((g_ucDpRx1LinkRate <= _DP_LINK_HBR) ||
           (((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x03) & _BIT2) != _BIT2) &&
            ((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x03) & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0))))
        {
            ScalerDpRx1Tp2SetPhy_EXINT0();
        }
    }

    if(ScalerDpRx1Tp2Check_EXINT0(enumDpLtType) == _TRUE)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Settings after Link Training Pass
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1TrainingPatternEnd_EXINT0(void) using 1
{
    switch(g_ucDpRx1LaneCount)
    {
        case _DP_ONE_LANE:
            ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT3);
            break;

        case _DP_TWO_LANE:
            ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT4);
            break;

        case _DP_FOUR_LANE:
        default:
            ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
            break;
    }

    // De-Skew Circuit Reset
    ScalerSetBit_EXINT(PB0_0E_DESKEW_PHY, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetBit_EXINT(PB0_0E_DESKEW_PHY, ~(_BIT7 | _BIT6), _BIT6);

    if((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x01) & _BIT7) == _BIT7)
    {
        // Enable Enhancement Control Mode --> MAC
        ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT2, _BIT2);
    }
    else
    {
        // Disable Enhancement Control Mode --> MAC
        ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT2, 0x00);
    }

    if((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x02) & _BIT5) == _BIT5)
    {
        // Disable Scrambling
        ScalerSetBit_EXINT(PB0_07_SCRAMBLE_CTRL, ~_BIT5, _BIT5);
    }
    else
    {
        // Enable Scrambling
        ScalerSetBit_EXINT(PB0_07_SCRAMBLE_CTRL, ~_BIT5, 0x00);
    }
}

//--------------------------------------------------
// Description  : Check Dp Training Pattern 1
// Input Value  : Normal or Fake LT
// Output Value : TRUE --> TP1 Pass
//--------------------------------------------------
BYTE ScalerDpRx1Tp1Check_EXINT0(EnumDpLinkTrainingType enumDpLtType) using 1
{
    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x00);
    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x00);
    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x80);

    if(enumDpLtType == _DP_NORMAL_LT)
    {
        if((GET_DP_RX1_LINK_TRAINING_STATUS() != _DP_NORMAL_TRAINING_PATTERN_1_FAIL) && (GET_DP_RX1_LINK_TRAINING_STATUS() != _DP_FAKE_TRAINING_PATTERN_1_FAIL))
        {
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x01, 0x03, 0x00);
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x01, 0x04, 0x00);
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x01, 0x05, 0x00);
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x01, 0x06, 0x00);

            if(GET_DP_RX_D1_MARGIN_LINK_HBR_RBR() == _TRUE)
            {
                SET_DP_RX_D1_LANE0_MARGIN_LINK_HBR_RBR();
                SET_DP_RX_D1_LANE1_MARGIN_LINK_HBR_RBR();
                SET_DP_RX_D1_LANE2_MARGIN_LINK_HBR_RBR();
                SET_DP_RX_D1_LANE3_MARGIN_LINK_HBR_RBR();
            }
            else
            {
                CLR_DP_RX_D1_LANE0_MARGIN_LINK_HBR_RBR();
                CLR_DP_RX_D1_LANE1_MARGIN_LINK_HBR_RBR();
                CLR_DP_RX_D1_LANE2_MARGIN_LINK_HBR_RBR();
                CLR_DP_RX_D1_LANE3_MARGIN_LINK_HBR_RBR();
            }
        }

        pData_EXINT[0] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x03);
        pData_EXINT[1] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x04);
        pData_EXINT[2] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x05);
        pData_EXINT[3] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x06);

        g_ucDpRx1LinkStatus01 = 0;
        g_ucDpRx1LinkStatus23 = 0;
        g_ucDpRx1LinkRequest01 = (pData_EXINT[0] & 0x03) | ((pData_EXINT[1] << 4) & 0x30);
        g_ucDpRx1LinkRequest23 = (pData_EXINT[2] & 0x03) | ((pData_EXINT[3] << 4) & 0x30);

        switch(g_ucDpRx1LaneCount)
        {
            case _DP_FOUR_LANE:

                // Read Back Lane2 Vth
                ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), _D1_DP_LANE2 << 6);

                ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                // Lane2 Check
                if(((GET_DP_RX1_PCB_LANE2_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT4) == _BIT4)) ||
                   ((GET_DP_RX1_PCB_LANE2_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT5) == _BIT5)) ||
                   ((GET_DP_RX1_PCB_LANE2_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT6) == _BIT6)) ||
                   ((GET_DP_RX1_PCB_LANE2_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT7) == _BIT7)))
                {
                    if(g_ucDpRx1LinkRate <= _DP_LINK_HBR)
                    {
                        if(((pData_EXINT[2] & _BIT2) == _BIT2) || ((pData_EXINT[2] & (_BIT1 | _BIT0)) >= _BIT1))
                        {
                            g_ucDpRx1LinkStatus23 = g_ucDpRx1LinkStatus23 | 0x01;
                        }
                        else if((ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F) > 3)
                        {
                            if(GET_DP_RX_D1_LANE2_MARGIN_LINK_HBR_RBR() == _FALSE)
                            {
                                g_ucDpRx1LinkStatus23 = g_ucDpRx1LinkStatus23 | 0x01;
                            }
                            else
                            {
                                g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xFC) | (pData_EXINT[2] & (_BIT1 | _BIT0))) + 0x01;
                                CLR_DP_RX_D1_LANE2_MARGIN_LINK_HBR_RBR();
                            }
                        }
                        else
                        {
                            g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xFC) | (pData_EXINT[2] & (_BIT1 | _BIT0))) + 0x01;
                        }
                    }
                    else if(((pData_EXINT[2] & _BIT2) == _BIT2) || ((pData_EXINT[2] & (_BIT1 | _BIT0)) >= _BIT1))
                    {
                        g_ucDpRx1LinkStatus23 = g_ucDpRx1LinkStatus23 | 0x01;
                    }
                    else
                    {
                        g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xFC) | (pData_EXINT[2] & (_BIT1 | _BIT0))) + 0x01;
                    }
                }
                else
                {
                    if((g_ucDpRx1LinkRate == _DP_LINK_HBR2) && (((pData_EXINT[2] & _BIT2) == _BIT2) && ((pData_EXINT[2] & (_BIT1 | _BIT0)) == _BIT1)))
                    {
                        g_ucDpRx1LinkStatus23 = g_ucDpRx1LinkStatus23 | 0x01;
                    }
                    else if(((pData_EXINT[2] & _BIT2) != _BIT2) &&
                            ((pData_EXINT[2] & (_BIT1 | _BIT0)) != (_BIT1 | _BIT0)))
                    {
                        g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xFC) | (pData_EXINT[2] & (_BIT1 | _BIT0))) + 0x01;
                    }
                }

                // Read Back Lane3 Vth
                ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), _D1_DP_LANE3 << 6);

                ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                // Lane3 Check
                if(((GET_DP_RX1_PCB_LANE3_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT4) == _BIT4)) ||
                   ((GET_DP_RX1_PCB_LANE3_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT5) == _BIT5)) ||
                   ((GET_DP_RX1_PCB_LANE3_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT6) == _BIT6)) ||
                   ((GET_DP_RX1_PCB_LANE3_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT7) == _BIT7)))
                {
                    if(g_ucDpRx1LinkRate <= _DP_LINK_HBR)
                    {
                        if(((pData_EXINT[3] & _BIT2) == _BIT2) || ((pData_EXINT[3] & (_BIT1 | _BIT0)) >= _BIT1))
                        {
                            g_ucDpRx1LinkStatus23 = g_ucDpRx1LinkStatus23 | 0x10;
                        }
                        else if((ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F) > 3)
                        {
                            if(GET_DP_RX_D1_LANE3_MARGIN_LINK_HBR_RBR() == _FALSE)
                            {
                                g_ucDpRx1LinkStatus23 = g_ucDpRx1LinkStatus23 | 0x10;
                            }
                            else
                            {
                                g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xCF) | ((pData_EXINT[3] << 4) & (_BIT5 | _BIT4))) + 0x10;
                                CLR_DP_RX_D1_LANE3_MARGIN_LINK_HBR_RBR();
                            }
                        }
                        else
                        {
                            g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xCF) | ((pData_EXINT[3] << 4) & (_BIT5 | _BIT4))) + 0x10;
                        }
                    }
                    else if(((pData_EXINT[3] & _BIT2) == _BIT2) || ((pData_EXINT[3] & (_BIT1 | _BIT0)) >= _BIT1))
                    {
                        g_ucDpRx1LinkStatus23 = g_ucDpRx1LinkStatus23 | 0x10;
                    }
                    else
                    {
                        g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xCF) | ((pData_EXINT[3] << 4) & (_BIT5 | _BIT4))) + 0x10;
                    }
                }
                else
                {
                    if((g_ucDpRx1LinkRate == _DP_LINK_HBR2) && (((pData_EXINT[3] & _BIT2) == _BIT2) && ((pData_EXINT[3] & (_BIT1 | _BIT0)) == _BIT1)))
                    {
                        g_ucDpRx1LinkStatus23 = g_ucDpRx1LinkStatus23 | 0x10;
                    }
                    else if(((pData_EXINT[3] & _BIT2) != _BIT2) &&
                            ((pData_EXINT[3] & (_BIT1 | _BIT0)) != (_BIT1 | _BIT0)))
                    {
                        g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xCF) | ((pData_EXINT[3] << 4) & (_BIT5 | _BIT4))) + 0x10;
                    }
                }

                // Read Back Lane1 Vth
                ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE1 << 6));

                ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                // Lane1 Check
                if(((GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT4) == _BIT4)) ||
                   ((GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT5) == _BIT5)) ||
                   ((GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT6) == _BIT6)) ||
                   ((GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT7) == _BIT7)))
                {
                    if(g_ucDpRx1LinkRate <= _DP_LINK_HBR)
                    {
                        if(((pData_EXINT[1] & _BIT2) == _BIT2) || ((pData_EXINT[1] & (_BIT1 | _BIT0)) >= _BIT1))
                        {
                            g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x10;
                        }
                        else if((ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F) > 3)
                        {
                            if(GET_DP_RX_D1_LANE1_MARGIN_LINK_HBR_RBR() == _FALSE)
                            {
                                g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x10;
                            }
                            else
                            {
                                g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | ((pData_EXINT[1] << 4) & (_BIT5 | _BIT4))) + 0x10;
                                CLR_DP_RX_D1_LANE1_MARGIN_LINK_HBR_RBR();
                            }
                        }
                        else
                        {
                            g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | ((pData_EXINT[1] << 4) & (_BIT5 | _BIT4))) + 0x10;
                        }
                    }
                    else if(((pData_EXINT[1] & _BIT2) == _BIT2) || ((pData_EXINT[1] & (_BIT1 | _BIT0)) >= _BIT1))
                    {
                        g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x10;
                    }
                    else
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | ((pData_EXINT[1] << 4) & (_BIT5 | _BIT4))) + 0x10;
                    }
                }
                else
                {
                    if((g_ucDpRx1LinkRate == _DP_LINK_HBR2) && (((pData_EXINT[1] & _BIT2) == _BIT2) && ((pData_EXINT[1] & (_BIT1 | _BIT0)) == _BIT1)))
                    {
                        g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x10;
                    }
                    else if(((pData_EXINT[1] & _BIT2) != _BIT2) &&
                            ((pData_EXINT[1] & (_BIT1 | _BIT0)) != (_BIT1 | _BIT0)))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | ((pData_EXINT[1] << 4) & (_BIT5 | _BIT4))) + 0x10;
                    }
                }

                // Read Back Lane0 Vth
                ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE0 << 6));

                ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                // Lane0 Check
                if(((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT4) == _BIT4)) ||
                   ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT5) == _BIT5)) ||
                   ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT6) == _BIT6)) ||
                   ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT7) == _BIT7)))
                {
                    if(g_ucDpRx1LinkRate <= _DP_LINK_HBR)
                    {
                        if(((pData_EXINT[0] & _BIT2) == _BIT2) || ((pData_EXINT[0] & (_BIT1 | _BIT0)) >= _BIT1))
                        {
                            g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x01;
                        }
                        else if((ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F) > 3)
                        {
                            if(GET_DP_RX_D1_LANE0_MARGIN_LINK_HBR_RBR() == _FALSE)
                            {
                                g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x01;
                            }
                            else
                            {
                                g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                                CLR_DP_RX_D1_LANE0_MARGIN_LINK_HBR_RBR();
                            }
                        }
                        else
                        {
                            g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                        }
                    }
                    else if(((pData_EXINT[0] & _BIT2) == _BIT2) || ((pData_EXINT[0] & (_BIT1 | _BIT0)) >= _BIT1))
                    {
                        g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x01;
                    }
                    else
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                    }
                }
                else
                {
                    if((g_ucDpRx1LinkRate == _DP_LINK_HBR2) && (((pData_EXINT[0] & _BIT2) == _BIT2) && ((pData_EXINT[0] & (_BIT1 | _BIT0)) == _BIT1)))
                    {
                        g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x01;
                    }
                    else if(((pData_EXINT[0] & _BIT2) != _BIT2) &&
                            ((pData_EXINT[0] & (_BIT1 | _BIT0)) != (_BIT1 | _BIT0)))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                    }
                }

                break;

            case _DP_TWO_LANE:

                // Read Back Lane1 Vth
                ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), _D1_DP_LANE1 << 6);

                ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                // Lane1 Check
                if(((GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT4) == _BIT4)) ||
                   ((GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT5) == _BIT5)) ||
                   ((GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT6) == _BIT6)) ||
                   ((GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT7) == _BIT7)))
                {
                    if(g_ucDpRx1LinkRate <= _DP_LINK_HBR)
                    {
                        if(((pData_EXINT[1] & _BIT2) == _BIT2) || ((pData_EXINT[1] & (_BIT1 | _BIT0)) >= _BIT1))
                        {
                            g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x10;
                        }
                        else if((ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F) > 3)
                        {
                            if(GET_DP_RX_D1_LANE1_MARGIN_LINK_HBR_RBR() == _FALSE)
                            {
                                g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x10;
                            }
                            else
                            {
                                g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | ((pData_EXINT[1] << 4) & (_BIT5 | _BIT4))) + 0x10;
                                CLR_DP_RX_D1_LANE1_MARGIN_LINK_HBR_RBR();
                            }
                        }
                        else
                        {
                            g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | ((pData_EXINT[1] << 4) & (_BIT5 | _BIT4))) + 0x10;
                        }
                    }
                    else if(((pData_EXINT[1] & _BIT2) == _BIT2) || ((pData_EXINT[1] & (_BIT1 | _BIT0)) >= _BIT1))
                    {
                        g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x10;
                    }
                    else
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | ((pData_EXINT[1] << 4) & (_BIT5 | _BIT4))) + 0x10;
                    }
                }
                else
                {
                    if((g_ucDpRx1LinkRate == _DP_LINK_HBR2) && (((pData_EXINT[1] & _BIT2) == _BIT2) && ((pData_EXINT[1] & (_BIT1 | _BIT0)) == _BIT1)))
                    {
                        g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x10;
                    }
                    else if(((pData_EXINT[1] & _BIT2) != _BIT2) &&
                            ((pData_EXINT[1] & (_BIT1 | _BIT0)) != (_BIT1 | _BIT0)))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | ((pData_EXINT[1] << 4) & (_BIT5 | _BIT4))) + 0x10;
                    }
                }

                // Read Back Lane0 Vth
                ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE0 << 6));

                ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                // Lane0 Check
                if(((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT4) == _BIT4)) ||
                   ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT5) == _BIT5)) ||
                   ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT6) == _BIT6)) ||
                   ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT7) == _BIT7)))
                {
                    if(g_ucDpRx1LinkRate <= _DP_LINK_HBR)
                    {
                        if(((pData_EXINT[0] & _BIT2) == _BIT2) || ((pData_EXINT[0] & (_BIT1 | _BIT0)) >= _BIT1))
                        {
                            g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x01;
                        }
                        else if((ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F) > 3)
                        {
                            if(GET_DP_RX_D1_LANE0_MARGIN_LINK_HBR_RBR() == _FALSE)
                            {
                                g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x01;
                            }
                            else
                            {
                                g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                                CLR_DP_RX_D1_LANE0_MARGIN_LINK_HBR_RBR();
                            }
                        }
                        else
                        {
                            g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                        }
                    }
                    else if(((pData_EXINT[0] & _BIT2) == _BIT2) || ((pData_EXINT[0] & (_BIT1 | _BIT0)) >= _BIT1))
                    {
                        g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x01;
                    }
                    else
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                    }
                }
                else
                {
                    if((g_ucDpRx1LinkRate == _DP_LINK_HBR2) && (((pData_EXINT[0] & _BIT2) == _BIT2) && ((pData_EXINT[0] & (_BIT1 | _BIT0)) == _BIT1)))
                    {
                        g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x01;
                    }
                    else if(((pData_EXINT[0] & _BIT2) != _BIT2) &&
                            ((pData_EXINT[0] & (_BIT1 | _BIT0)) != (_BIT1 | _BIT0)))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                    }
                }

                break;

            case _DP_ONE_LANE:
            default:

                // Read Back Lane0 Vth
                ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), _D1_DP_LANE0 << 6);

                ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

                // Lane0 Check
                if(((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT4) == _BIT4)) ||
                   ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT5) == _BIT5)) ||
                   ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT6) == _BIT6)) ||
                   ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit_EXINT(PB0_14_EQ_CRC_3, _BIT7) == _BIT7)))
                {
                    if(g_ucDpRx1LinkRate <= _DP_LINK_HBR)
                    {
                        if(((pData_EXINT[0] & _BIT2) == _BIT2) || ((pData_EXINT[0] & (_BIT1 | _BIT0)) >= _BIT1))
                        {
                            g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x01;
                        }
                        else if((ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F) > 3)
                        {
                            if(GET_DP_RX_D1_LANE0_MARGIN_LINK_HBR_RBR() == _FALSE)
                            {
                                g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x01;
                            }
                            else
                            {
                                g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                                CLR_DP_RX_D1_LANE0_MARGIN_LINK_HBR_RBR();
                            }
                        }
                        else
                        {
                            g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                        }
                    }
                    else if(((pData_EXINT[0] & _BIT2) == _BIT2) || ((pData_EXINT[0] & (_BIT1 | _BIT0)) >= _BIT1))
                    {
                        g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x01;
                    }
                    else
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                    }
                }
                else
                {
                    if((g_ucDpRx1LinkRate == _DP_LINK_HBR2) && (((pData_EXINT[0] & _BIT2) == _BIT2) && ((pData_EXINT[0] & (_BIT1 | _BIT0)) == _BIT1)))
                    {
                        g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x01;
                    }
                    else if(((pData_EXINT[0] & _BIT2) != _BIT2) &&
                            ((pData_EXINT[0] & (_BIT1 | _BIT0)) != (_BIT1 | _BIT0)))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                    }
                }

                break;
        }

        ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, g_ucDpRx1LinkStatus01);
        ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x03, g_ucDpRx1LinkStatus23);
        ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpRx1LinkRequest01);
        ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x07, g_ucDpRx1LinkRequest23);

        switch(g_ucDpRx1LaneCount)
        {
            case _DP_ONE_LANE:

                if((g_ucDpRx1LinkStatus01 & _BIT0) == _BIT0)
                {
                    return _TRUE;
                }

                break;

            case _DP_TWO_LANE:

                if((g_ucDpRx1LinkStatus01 & (_BIT4 | _BIT0)) == (_BIT4 | _BIT0))
                {
                    return _TRUE;
                }

                break;

            case _DP_FOUR_LANE:
            default:

                if(((g_ucDpRx1LinkStatus01 & (_BIT4 | _BIT0)) == (_BIT4 | _BIT0)) && (((g_ucDpRx1LinkStatus23 & (_BIT4 | _BIT0)) == (_BIT4 | _BIT0))))
                {
                    return _TRUE;
                }

                break;
        }
    }
    else
    {
        if(GET_DP_RX1_LINK_TRAINING_STATUS() != _DP_FAKE_TRAINING_PATTERN_1_FAIL)
        {
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x01, 0x03, 0x00);
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x01, 0x04, 0x00);
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x01, 0x05, 0x00);
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x01, 0x06, 0x00);
        }

        pData_EXINT[0] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x03);
        pData_EXINT[1] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x04);
        pData_EXINT[2] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x05);
        pData_EXINT[3] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x06);

        g_ucDpRx1LinkRequest01 = (pData_EXINT[0] & 0x03) | ((pData_EXINT[1] << 4) & 0x30);
        g_ucDpRx1LinkRequest23 = (pData_EXINT[2] & 0x03) | ((pData_EXINT[3] << 4) & 0x30);

        switch(g_ucDpRx1LaneCount)
        {
            case _DP_ONE_LANE:

                if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
                {
                    if(((pData_EXINT[0] & _BIT2) != _BIT2) && ((pData_EXINT[0] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                    }
                }
                else
                {
                    if(((pData_EXINT[0] & _BIT2) != _BIT2) && ((pData_EXINT[0] & (_BIT1 | _BIT0)) < _BIT0))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                    }
                }

                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpRx1LinkRequest01);
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x07, 0x00);

                if(((pData_EXINT[0] & _BIT2) == _BIT2) || ((pData_EXINT[0] & (_BIT1 | _BIT0)) == (ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x06) & (_BIT1 | _BIT0))))
                {
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x01);

                    return _TRUE;
                }

                break;

            case _DP_TWO_LANE:

                if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
                {
                    if(((pData_EXINT[0] & _BIT2) != _BIT2) && ((pData_EXINT[0] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                    }

                    if(((pData_EXINT[1] & _BIT2) != _BIT2) && ((pData_EXINT[1] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | ((pData_EXINT[1] & (_BIT1 | _BIT0)) << 4)) + 0x10;
                    }
                }
                else
                {
                    if(((pData_EXINT[0] & _BIT2) != _BIT2) && ((pData_EXINT[0] & (_BIT1 | _BIT0)) < _BIT0))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                    }

                    if(((pData_EXINT[1] & _BIT2) != _BIT2) && ((pData_EXINT[1] & (_BIT1 | _BIT0)) < _BIT0))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | ((pData_EXINT[1] & (_BIT1 | _BIT0)) << 4)) + 0x10;
                    }
                }

                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpRx1LinkRequest01);
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x07, 0x00);

                if((((pData_EXINT[0] & _BIT2) == _BIT2) || ((pData_EXINT[0] & (_BIT1 | _BIT0)) == (ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x06) & (_BIT1 | _BIT0)))) &&
                   (((pData_EXINT[1] & _BIT2) == _BIT2) || ((pData_EXINT[1] & (_BIT1 | _BIT0)) == ((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x06) >> 4) & (_BIT1 | _BIT0)))))
                {
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x11);

                    return _TRUE;
                }


                break;

            case _DP_FOUR_LANE:
            default:

                if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
                {
                    if(((pData_EXINT[0] & _BIT2) != _BIT2) && ((pData_EXINT[0] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                    }

                    if(((pData_EXINT[1] & _BIT2) != _BIT2) && ((pData_EXINT[1] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | ((pData_EXINT[1] & (_BIT1 | _BIT0)) << 4)) + 0x10;
                    }

                    if(((pData_EXINT[2] & _BIT2) != _BIT2) && ((pData_EXINT[2] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                    {
                        g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xFC) | (pData_EXINT[2] & (_BIT1 | _BIT0))) + 0x01;
                    }

                    if(((pData_EXINT[3] & _BIT2) != _BIT2) && ((pData_EXINT[3] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                    {
                        g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xCF) | ((pData_EXINT[3] & (_BIT1 | _BIT0)) << 4)) + 0x10;
                    }
                }
                else
                {
                    if(((pData_EXINT[0] & _BIT2) != _BIT2) && ((pData_EXINT[0] & (_BIT1 | _BIT0)) < _BIT0))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                    }

                    if(((pData_EXINT[1] & _BIT2) != _BIT2) && ((pData_EXINT[1] & (_BIT1 | _BIT0)) < _BIT0))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | ((pData_EXINT[1] & (_BIT1 | _BIT0)) << 4)) + 0x10;
                    }

                    if(((pData_EXINT[2] & _BIT2) != _BIT2) && ((pData_EXINT[2] & (_BIT1 | _BIT0)) < _BIT0))
                    {
                        g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xFC) | (pData_EXINT[2] & (_BIT1 | _BIT0))) + 0x01;
                    }

                    if(((pData_EXINT[3] & _BIT2) != _BIT2) && ((pData_EXINT[3] & (_BIT1 | _BIT0)) < _BIT0))
                    {
                        g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xCF) | ((pData_EXINT[3] & (_BIT1 | _BIT0)) << 4)) + 0x10;
                    }
                }

                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpRx1LinkRequest01);
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x07, g_ucDpRx1LinkRequest23);

                if((((pData_EXINT[0] & _BIT2) == _BIT2) || ((pData_EXINT[0] & (_BIT1 | _BIT0)) == (ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x06) & (_BIT1 | _BIT0)))) &&
                   (((pData_EXINT[1] & _BIT2) == _BIT2) || ((pData_EXINT[1] & (_BIT1 | _BIT0)) == ((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x06) >> 4) & (_BIT1 | _BIT0)))) &&
                   (((pData_EXINT[2] & _BIT2) == _BIT2) || ((pData_EXINT[2] & (_BIT1 | _BIT0)) == (ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x07) & (_BIT1 | _BIT0)))) &&
                   (((pData_EXINT[3] & _BIT2) == _BIT2) || ((pData_EXINT[3] & (_BIT1 | _BIT0)) == ((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x07) >> 4) & (_BIT1 | _BIT0)))))
                {
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x11);
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x11);

                    return _TRUE;
                }

                break;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check Dp Training Pattern 2
// Input Value  : Normal or Fake LT
// Output Value : TRUE --> TP2 Pass
//--------------------------------------------------
BYTE ScalerDpRx1Tp2Check_EXINT0(EnumDpLinkTrainingType enumDpLtType) using 1
{
    BYTE ucEQCRCStatus = 0;
    BYTE ucEQCRCStatus1 = 0;
    BYTE ucEQCRCStatus2 = 0;

    pData_EXINT[0] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x03);
    pData_EXINT[1] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x04);
    pData_EXINT[2] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x05);
    pData_EXINT[3] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x06);

    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x80);

    if(enumDpLtType == _DP_NORMAL_LT)
    {
        // Clear 8b/10b Decode Error
        ScalerSetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        g_ucDpRx1LinkRequest01 = ((pData_EXINT[0] & 0x03) |
                                  ((pData_EXINT[0] >> 1) & 0x0C) |
                                  ((pData_EXINT[1] << 4) & 0x30) |
                                  ((pData_EXINT[1] << 3) & 0xC0));

        g_ucDpRx1LinkRequest23 = ((pData_EXINT[2] & 0x03) |
                                  ((pData_EXINT[2] >> 1) & 0x0C) |
                                  ((pData_EXINT[3] << 4) & 0x30) |
                                  ((pData_EXINT[3] << 3) & 0xC0));

        // Enable EQ-CRC and Clear EQ-CRC Status(- K28.5)
        ScalerSetBit_EXINT(PB0_12_EQ_CRC_1, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

        for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 2; g_ucDpRx1Temp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        ucEQCRCStatus1 = ScalerGetByte_EXINT(PB0_12_EQ_CRC_1);

        if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
        {
            for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 30; g_ucDpRx1Temp++)
            {
                ucEQCRCStatus1 = ucEQCRCStatus1 & ScalerGetByte_EXINT(PB0_12_EQ_CRC_1);
            }
        }
        else
        {
            for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 5; g_ucDpRx1Temp++)
            {
                ucEQCRCStatus1 = ucEQCRCStatus1 & ScalerGetByte_EXINT(PB0_12_EQ_CRC_1);
            }
        }

        // Disable EQ-CRC
        ScalerSetBit_EXINT(PB0_12_EQ_CRC_1, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        // Enable EQ-CRC and Clear EQ-CRC Status(+ K28.5)
        ScalerSetBit_EXINT(PB0_12_EQ_CRC_1, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

        for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 2; g_ucDpRx1Temp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        ucEQCRCStatus2 = ScalerGetByte_EXINT(PB0_12_EQ_CRC_1);

        for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 5; g_ucDpRx1Temp++)
        {
            ucEQCRCStatus2 = ucEQCRCStatus2 & ScalerGetByte_EXINT(PB0_12_EQ_CRC_1);
        }

        // Disable EQ-CRC
        ScalerSetBit_EXINT(PB0_12_EQ_CRC_1, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        ucEQCRCStatus = (ucEQCRCStatus1 | ucEQCRCStatus2);

        g_ucDpRx1EQCRC = 0x00;

        if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0)
        {
            g_ucDpRx1EQCRC |= (ucEQCRCStatus & 0x01);
        }
        else if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1)
        {
            g_ucDpRx1EQCRC |= ((ucEQCRCStatus & 0x02) >> 1);
        }
        else if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2)
        {
            g_ucDpRx1EQCRC |= ((ucEQCRCStatus & 0x04) >> 2);
        }
        else if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3)
        {
            g_ucDpRx1EQCRC |= ((ucEQCRCStatus & 0x08) >> 3);
        }

        if(GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0)
        {
            g_ucDpRx1EQCRC |= ((ucEQCRCStatus & 0x01) << 1);
        }
        else if(GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1)
        {
            g_ucDpRx1EQCRC |= (ucEQCRCStatus & 0x02);
        }
        else if(GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2)
        {
            g_ucDpRx1EQCRC |= ((ucEQCRCStatus & 0x04) >> 1);
        }
        else if(GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)
        {
            g_ucDpRx1EQCRC |= ((ucEQCRCStatus & 0x08) >> 2);
        }

        if(GET_DP_RX1_PCB_LANE2_MAPPING() == _DP_SCALER_LANE0)
        {
            g_ucDpRx1EQCRC |= ((ucEQCRCStatus & 0x01) << 2);
        }
        else if(GET_DP_RX1_PCB_LANE2_MAPPING() == _DP_SCALER_LANE1)
        {
            g_ucDpRx1EQCRC |= ((ucEQCRCStatus & 0x02) << 1);
        }
        else if(GET_DP_RX1_PCB_LANE2_MAPPING() == _DP_SCALER_LANE2)
        {
            g_ucDpRx1EQCRC |= (ucEQCRCStatus & 0x04);
        }
        else if(GET_DP_RX1_PCB_LANE2_MAPPING() == _DP_SCALER_LANE3)
        {
            g_ucDpRx1EQCRC |= ((ucEQCRCStatus & 0x08) >> 1);
        }

        if(GET_DP_RX1_PCB_LANE3_MAPPING() == _DP_SCALER_LANE0)
        {
            g_ucDpRx1EQCRC |= ((ucEQCRCStatus & 0x01) << 3);
        }
        else if(GET_DP_RX1_PCB_LANE3_MAPPING() == _DP_SCALER_LANE1)
        {
            g_ucDpRx1EQCRC |= ((ucEQCRCStatus & 0x02) << 2);
        }
        else if(GET_DP_RX1_PCB_LANE3_MAPPING() == _DP_SCALER_LANE2)
        {
            g_ucDpRx1EQCRC |= ((ucEQCRCStatus & 0x04) << 1);
        }
        else if(GET_DP_RX1_PCB_LANE3_MAPPING() == _DP_SCALER_LANE3)
        {
            g_ucDpRx1EQCRC |= (ucEQCRCStatus & 0x08);
        }

        ucEQCRCStatus = g_ucDpRx1EQCRC;

        if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
        {
            if(((pData_EXINT[0] & _BIT2) == _BIT2) || ((pData_EXINT[0] & (_BIT1 | _BIT0)) >= (_BIT1 | _BIT0)))
            {
                ucEQCRCStatus |= _BIT0;
            }

            if(((pData_EXINT[1] & _BIT2) == _BIT2) || ((pData_EXINT[1] & (_BIT1 | _BIT0)) >= (_BIT1 | _BIT0)))
            {
                ucEQCRCStatus |= _BIT1;
            }

            if(((pData_EXINT[2] & _BIT2) == _BIT2) || ((pData_EXINT[2] & (_BIT1 | _BIT0)) >= (_BIT1 | _BIT0)))
            {
                ucEQCRCStatus |= _BIT2;
            }

            if(((pData_EXINT[3] & _BIT2) == _BIT2) || ((pData_EXINT[3] & (_BIT1 | _BIT0)) >= (_BIT1 | _BIT0)))
            {
                ucEQCRCStatus |= _BIT3;
            }
        }
        else
        {
            if(g_ucDpRx1TrainingPatternSet == _DP_TRAINING_PATTERN_3)
            {
                if(ScalerGetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, _BIT0) == 0x00)
                {
                    if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0)
                    {
                        ucEQCRCStatus |= _BIT0;
                    }
                    else if(GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0)
                    {
                        ucEQCRCStatus |= _BIT1;
                    }
                    else if(GET_DP_RX1_PCB_LANE2_MAPPING() == _DP_SCALER_LANE0)
                    {
                        ucEQCRCStatus |= _BIT2;
                    }
                    else if(GET_DP_RX1_PCB_LANE3_MAPPING() == _DP_SCALER_LANE0)
                    {
                        ucEQCRCStatus |= _BIT3;
                    }
                }

                if(ScalerGetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, _BIT1) == 0x00)
                {
                    if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1)
                    {
                        ucEQCRCStatus |= _BIT0;
                    }
                    else if(GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1)
                    {
                        ucEQCRCStatus |= _BIT1;
                    }
                    else if(GET_DP_RX1_PCB_LANE2_MAPPING() == _DP_SCALER_LANE1)
                    {
                        ucEQCRCStatus |= _BIT2;
                    }
                    else if(GET_DP_RX1_PCB_LANE3_MAPPING() == _DP_SCALER_LANE1)
                    {
                        ucEQCRCStatus |= _BIT3;
                    }
                }

                if(ScalerGetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, _BIT2) == 0x00)
                {
                    if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2)
                    {
                        ucEQCRCStatus |= _BIT0;
                    }
                    else if(GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2)
                    {
                        ucEQCRCStatus |= _BIT1;
                    }
                    else if(GET_DP_RX1_PCB_LANE2_MAPPING() == _DP_SCALER_LANE2)
                    {
                        ucEQCRCStatus |= _BIT2;
                    }
                    else if(GET_DP_RX1_PCB_LANE3_MAPPING() == _DP_SCALER_LANE2)
                    {
                        ucEQCRCStatus |= _BIT3;
                    }
                }

                if(ScalerGetBit_EXINT(PB0_06_DECODE_10B8B_ERROR, _BIT3) == 0x00)
                {
                    if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3)
                    {
                        ucEQCRCStatus |= _BIT0;
                    }
                    else if(GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)
                    {
                        ucEQCRCStatus |= _BIT1;
                    }
                    else if(GET_DP_RX1_PCB_LANE2_MAPPING() == _DP_SCALER_LANE3)
                    {
                        ucEQCRCStatus |= _BIT2;
                    }
                    else if(GET_DP_RX1_PCB_LANE3_MAPPING() == _DP_SCALER_LANE3)
                    {
                        ucEQCRCStatus |= _BIT3;
                    }
                }
            }
        }

        switch(g_ucDpRx1LaneCount)
        {
            case _DP_FOUR_LANE:

                if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
                {
                    if((ucEQCRCStatus & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) != (_BIT3 | _BIT2 | _BIT1 | _BIT0))
                    {
                        ucEQCRCStatus &= ~(_BIT3 | _BIT2 | _BIT1 | _BIT0);
                    }
                }

                // Lane2 EQ-CRC Check
                if((ucEQCRCStatus & _BIT2) == _BIT2)
                {
                    if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
                    {
                        if(((pData_EXINT[2] & _BIT2) == _BIT2) || ((pData_EXINT[2] & (_BIT1 | _BIT0)) >= (_BIT1 | _BIT0)))
                        {
                            g_ucDpRx1LinkStatus23 = g_ucDpRx1LinkStatus23 | 0x07;
                        }
                        else if((ucEQCRCStatus & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT3 | _BIT2 | _BIT1 | _BIT0))
                        {
                            g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xFC) | (pData_EXINT[2] & (_BIT1 | _BIT0))) + 0x01;
                        }
                    }
                    else
                    {
                        g_ucDpRx1LinkStatus23 = g_ucDpRx1LinkStatus23 | 0x07;
                    }
                }
                else
                {
                    if(((pData_EXINT[2] & _BIT5) != _BIT5) &&
                       (((g_ucDpRx1LinkRequest23 & 0x03) + ((g_ucDpRx1LinkRequest23 >> 2) & 0x03)) < 3) &&
                       (g_ucDpRx1LinkRate <= _DP_LINK_HBR))
                    {
                        g_ucDpRx1LinkRequest23 = g_ucDpRx1LinkRequest23 + 0x04;
                    }
                }

                // Lane3 EQ-CRC Check
                if((ucEQCRCStatus & _BIT3) == _BIT3)
                {
                    if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
                    {
                        if(((pData_EXINT[3] & _BIT2) == _BIT2) || ((pData_EXINT[3] & (_BIT1 | _BIT0)) >= (_BIT1 | _BIT0)))
                        {
                            g_ucDpRx1LinkStatus23 = g_ucDpRx1LinkStatus23 | 0x70;
                        }
                        else if((ucEQCRCStatus & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == (_BIT3 | _BIT2 | _BIT1 | _BIT0))
                        {
                            g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xCF) | ((pData_EXINT[3] << 4) & (_BIT5 | _BIT4))) + 0x10;
                        }
                    }
                    else
                    {
                        g_ucDpRx1LinkStatus23 = g_ucDpRx1LinkStatus23 | 0x70;
                    }
                }
                else
                {
                    if(((pData_EXINT[3] & _BIT5) != _BIT5) &&
                       ((((g_ucDpRx1LinkRequest23 >> 4) & 0x03) + ((g_ucDpRx1LinkRequest23 >> 6) & 0x03)) < 3) &&
                       (g_ucDpRx1LinkRate <= _DP_LINK_HBR))
                    {
                        g_ucDpRx1LinkRequest23 = g_ucDpRx1LinkRequest23 + 0x40;
                    }
                }

                // Lane1 EQ-CRC Check
                if((ucEQCRCStatus & _BIT1) == _BIT1)
                {
                    if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
                    {
                        if(((pData_EXINT[1] & _BIT2) == _BIT2) || ((pData_EXINT[1] & (_BIT1 | _BIT0)) >= (_BIT1 | _BIT0)))
                        {
                            g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x70;
                        }
                        else if((ucEQCRCStatus & (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
                        {
                            g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | ((pData_EXINT[1] << 4) & (_BIT5 | _BIT4))) + 0x10;
                        }
                    }
                    else
                    {
                        g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x70;
                    }
                }
                else
                {
                    if(((pData_EXINT[1] & _BIT5) != _BIT5) &&
                       ((((g_ucDpRx1LinkRequest01 >> 4) & 0x03) + ((g_ucDpRx1LinkRequest01 >> 6) & 0x03)) < 3) &&
                       (g_ucDpRx1LinkRate <= _DP_LINK_HBR))
                    {
                        g_ucDpRx1LinkRequest01 = g_ucDpRx1LinkRequest01 + 0x40;
                    }
                }

                // Lane0 EQ-CRC Check
                if((ucEQCRCStatus & _BIT0) == _BIT0)
                {
                    if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
                    {
                        if(((pData_EXINT[0] & _BIT2) == _BIT2) || ((pData_EXINT[0] & (_BIT1 | _BIT0)) >= (_BIT1 | _BIT0)))
                        {
                            g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x07;
                        }
                        else if((ucEQCRCStatus & _BIT0) == _BIT0)
                        {
                            g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                        }
                    }
                    else
                    {
                        g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x07;
                    }
                }
                else
                {
                    if(((pData_EXINT[0] & _BIT5) != _BIT5) &&
                       (((g_ucDpRx1LinkRequest01 & 0x03) + ((g_ucDpRx1LinkRequest01 >> 2) & 0x03)) < 3) &&
                       (g_ucDpRx1LinkRate <= _DP_LINK_HBR))
                    {
                        g_ucDpRx1LinkRequest01 = g_ucDpRx1LinkRequest01 + 0x04;
                    }
                }

                break;

            case _DP_TWO_LANE:

                if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
                {
                    if((ucEQCRCStatus & (_BIT1 | _BIT0)) != (_BIT1 | _BIT0))
                    {
                        ucEQCRCStatus &= ~(_BIT1 | _BIT0);
                    }
                }

                // Lane1 EQ-CRC Check
                if((ucEQCRCStatus & _BIT1) == _BIT1)
                {
                    if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
                    {
                        if(((pData_EXINT[1] & _BIT2) == _BIT2) || ((pData_EXINT[1] & (_BIT1 | _BIT0)) >= (_BIT1 | _BIT0)))
                        {
                            g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x70;
                        }
                        else if((ucEQCRCStatus & (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
                        {
                            g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | ((pData_EXINT[1] << 4) & (_BIT5 | _BIT4))) + 0x10;
                        }
                    }
                    else
                    {
                        g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x70;
                    }
                }
                else
                {
                    if(((pData_EXINT[1] & _BIT5) != _BIT5) &&
                       ((((g_ucDpRx1LinkRequest01 >> 4) & 0x03) + ((g_ucDpRx1LinkRequest01 >> 6) & 0x03)) < 3) &&
                       (g_ucDpRx1LinkRate <= _DP_LINK_HBR))
                    {
                        g_ucDpRx1LinkRequest01 = g_ucDpRx1LinkRequest01 + 0x40;
                    }
                }

                // Lane0 EQ-CRC Check
                if((ucEQCRCStatus & _BIT0) == _BIT0)
                {
                    if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
                    {
                        if(((pData_EXINT[0] & _BIT2) == _BIT2) || ((pData_EXINT[0] & (_BIT1 | _BIT0)) >= (_BIT1 | _BIT0)))
                        {
                            g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x07;
                        }
                        else if((ucEQCRCStatus & _BIT0) == _BIT0)
                        {
                            g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                        }
                    }
                    else
                    {
                        g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x07;
                    }
                }
                else
                {
                    if(((pData_EXINT[0] & _BIT5) != _BIT5) &&
                       (((g_ucDpRx1LinkRequest01 & 0x03) + ((g_ucDpRx1LinkRequest01 >> 2) & 0x03)) < 3) &&
                       (g_ucDpRx1LinkRate <= _DP_LINK_HBR))
                    {
                        g_ucDpRx1LinkRequest01 = g_ucDpRx1LinkRequest01 + 0x04;
                    }
                }

                break;

            case _DP_ONE_LANE:
            default:

                if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
                {
                    if((ucEQCRCStatus & _BIT0) != _BIT0)
                    {
                        ucEQCRCStatus &= ~_BIT0;
                    }
                }

                // Lane0 EQ-CRC Check
                if((ucEQCRCStatus & _BIT0) == _BIT0)
                {
                    if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
                    {
                        if(((pData_EXINT[0] & _BIT2) == _BIT2) || ((pData_EXINT[0] & (_BIT1 | _BIT0)) >= (_BIT1 | _BIT0)))
                        {
                            g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x07;
                        }
                        else if((ucEQCRCStatus & _BIT0) == _BIT0)
                        {
                            g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                        }
                    }
                    else
                    {
                        g_ucDpRx1LinkStatus01 = g_ucDpRx1LinkStatus01 | 0x07;
                    }
                }
                else
                {
                    if(((pData_EXINT[0] & _BIT5) != _BIT5) &&
                       (((g_ucDpRx1LinkRequest01 & 0x03) + ((g_ucDpRx1LinkRequest01 >> 2) & 0x03)) < 3) &&
                       (g_ucDpRx1LinkRate <= _DP_LINK_HBR))
                    {
                        g_ucDpRx1LinkRequest01 = g_ucDpRx1LinkRequest01 + 0x04;
                    }
                }

                break;
        }

        ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, g_ucDpRx1LinkStatus01);
        ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x03, g_ucDpRx1LinkStatus23);
        ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpRx1LinkRequest01);
        ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x07, g_ucDpRx1LinkRequest23);

        switch(g_ucDpRx1LaneCount)
        {
            case _DP_ONE_LANE:

                if((g_ucDpRx1LinkStatus01 & 0x07) == 0x07)
                {
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x81);
                    return _TRUE;
                }

                break;

            case _DP_TWO_LANE:

                if((g_ucDpRx1LinkStatus01 & 0x77) == 0x77)
                {
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x81);
                    return _TRUE;
                }

                break;

            case _DP_FOUR_LANE:
            default:

                if(((g_ucDpRx1LinkStatus01 & 0x77) == 0x77) && (((g_ucDpRx1LinkStatus23 & 0x77) == 0x77)))
                {
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x81);
                    return _TRUE;
                }

                break;
        }
    }
    else
    {
        g_ucDpRx1LinkRequest01 = (pData_EXINT[0] & 0x03) | ((pData_EXINT[1] << 4) & 0x30);
        g_ucDpRx1LinkRequest23 = (pData_EXINT[2] & 0x03) | ((pData_EXINT[3] << 4) & 0x30);

        ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x80);

        switch(g_ucDpRx1LaneCount)
        {
            case _DP_ONE_LANE:

                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x01);
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x00);

                if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
                {
                    if(((pData_EXINT[0] & _BIT2) != _BIT2) && ((pData_EXINT[0] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                    }
                }
                else
                {
                    if(((pData_EXINT[0] & _BIT2) != _BIT2) && ((pData_EXINT[0] & (_BIT1 | _BIT0)) < _BIT1))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                    }
                }

                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpRx1LinkRequest01);
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x07, 0x00);

                if(((pData_EXINT[0] & _BIT5) == _BIT5) || ((pData_EXINT[0] & _BIT2) == _BIT2) || ((pData_EXINT[0] & (_BIT1 | _BIT0)) == (ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x06) & (_BIT1 | _BIT0))))
                {
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x07);
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x81);

                    return _TRUE;
                }

                break;

            case _DP_TWO_LANE:

                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x11);
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x00);

                if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
                {
                    if(((pData_EXINT[0] & _BIT2) != _BIT2) && ((pData_EXINT[0] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                    }

                    if(((pData_EXINT[1] & _BIT2) != _BIT2) && ((pData_EXINT[1] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | ((pData_EXINT[1] & (_BIT1 | _BIT0)) << 4)) + 0x10;
                    }
                }
                else
                {
                    if(((pData_EXINT[0] & _BIT2) != _BIT2) && ((pData_EXINT[0] & (_BIT1 | _BIT0)) < _BIT1))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                    }

                    if(((pData_EXINT[1] & _BIT2) != _BIT2) && ((pData_EXINT[1] & (_BIT1 | _BIT0)) < _BIT1))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | ((pData_EXINT[1] & (_BIT1 | _BIT0)) << 4)) + 0x10;
                    }
                }

                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpRx1LinkRequest01);
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x07, 0x00);

                if((((pData_EXINT[0] & _BIT5) == _BIT5) || ((pData_EXINT[0] & _BIT2) == _BIT2) || ((pData_EXINT[0] & (_BIT1 | _BIT0)) == (ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x06) & (_BIT1 | _BIT0)))) &&
                   (((pData_EXINT[1] & _BIT5) == _BIT5) || ((pData_EXINT[1] & _BIT2) == _BIT2) || ((pData_EXINT[1] & (_BIT1 | _BIT0)) == ((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x06) & (_BIT5 | _BIT4)) >> 4))))
                {
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x77);
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x81);

                    return _TRUE;
                }


                break;

            case _DP_FOUR_LANE:
            default:

                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x11);
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x11);

                if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
                {
                    if(((pData_EXINT[0] & _BIT2) != _BIT2) && ((pData_EXINT[0] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                    }

                    if(((pData_EXINT[1] & _BIT2) != _BIT2) && ((pData_EXINT[1] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | ((pData_EXINT[1] & (_BIT1 | _BIT0)) << 4)) + 0x10;
                    }

                    if(((pData_EXINT[2] & _BIT2) != _BIT2) && ((pData_EXINT[2] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                    {
                        g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xFC) | (pData_EXINT[2] & (_BIT1 | _BIT0))) + 0x01;
                    }

                    if(((pData_EXINT[3] & _BIT2) != _BIT2) && ((pData_EXINT[3] & (_BIT1 | _BIT0)) < (_BIT1 | _BIT0)))
                    {
                        g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xCF) | ((pData_EXINT[3] & (_BIT1 | _BIT0)) << 4)) + 0x10;
                    }
                }
                else
                {
                    if(((pData_EXINT[0] & _BIT2) != _BIT2) && ((pData_EXINT[0] & (_BIT1 | _BIT0)) < _BIT1))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xFC) | (pData_EXINT[0] & (_BIT1 | _BIT0))) + 0x01;
                    }

                    if(((pData_EXINT[1] & _BIT2) != _BIT2) && ((pData_EXINT[1] & (_BIT1 | _BIT0)) < _BIT1))
                    {
                        g_ucDpRx1LinkRequest01 = ((g_ucDpRx1LinkRequest01 & 0xCF) | ((pData_EXINT[1] & (_BIT1 | _BIT0)) << 4)) + 0x10;
                    }

                    if(((pData_EXINT[2] & _BIT2) != _BIT2) && ((pData_EXINT[2] & (_BIT1 | _BIT0)) < _BIT1))
                    {
                        g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xFC) | (pData_EXINT[2] & (_BIT1 | _BIT0))) + 0x01;
                    }

                    if(((pData_EXINT[3] & _BIT2) != _BIT2) && ((pData_EXINT[3] & (_BIT1 | _BIT0)) < _BIT1))
                    {
                        g_ucDpRx1LinkRequest23 = ((g_ucDpRx1LinkRequest23 & 0xCF) | ((pData_EXINT[3] & (_BIT1 | _BIT0)) << 4)) + 0x10;
                    }
                }

                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x06, g_ucDpRx1LinkRequest01);
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x07, g_ucDpRx1LinkRequest23);

                if((((pData_EXINT[0] & _BIT5) == _BIT5) || ((pData_EXINT[0] & _BIT2) == _BIT2) || ((pData_EXINT[0] & (_BIT1 | _BIT0)) == (ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x06) & (_BIT1 | _BIT0)))) &&
                   (((pData_EXINT[1] & _BIT5) == _BIT5) || ((pData_EXINT[1] & _BIT2) == _BIT2) || ((pData_EXINT[1] & (_BIT1 | _BIT0)) == ((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x06) & (_BIT5 | _BIT4)) >> 4))) &&
                   (((pData_EXINT[2] & _BIT5) == _BIT5) || ((pData_EXINT[2] & _BIT2) == _BIT2) || ((pData_EXINT[2] & (_BIT1 | _BIT0)) == (ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x07) & (_BIT1 | _BIT0)))) &&
                   (((pData_EXINT[3] & _BIT5) == _BIT5) || ((pData_EXINT[3] & _BIT2) == _BIT2) || ((pData_EXINT[3] & (_BIT1 | _BIT0)) == ((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x07) & (_BIT5 | _BIT4)) >> 4))))
                {
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x77);
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x77);
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x81);

                    return _TRUE;
                }

                break;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check Valid Lane Alignment
// Input Value  : None
// Output Value : True --> Align
//--------------------------------------------------
bit ScalerDpRx1AlignCheck(void)
{
    if((ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F) == _DP_ONE_LANE)
    {
        return _TRUE;
    }
    else
    {
        if(ScalerGetBit(PB0_0E_DESKEW_PHY, _BIT4) == 0x00)
        {
            if(ScalerGetBit(PB0_0E_DESKEW_PHY, (_BIT7 | _BIT6)) != (_BIT7 | _BIT6))
            {
                ScalerSetBit(PB0_0E_DESKEW_PHY, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

                ScalerTimerDelayXms(3);
            }
            else
            {
                return _FALSE;
            }
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description : check DP 8b/10b Decode Error
// Input Value  : None
// Output Value : True --> ok, False --> 8b/10b Decode Error
//--------------------------------------------------
bit ScalerDpRx1DecodeCheck(void)
{
    pData[1] = 3;

    while(pData[1] > 0)
    {
        // Clear 8b/10b Decode Error Flag
        ScalerSetBit(PB0_06_DECODE_10B8B_ERROR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

        for(pData[0] = 0; pData[0] <= 20; pData[0]++)
        {
            Delay5us(g_ucDelay5usN);
        }

        switch(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)
        {
            case _DP_ONE_LANE:

                if(((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, _BIT0) == 0x00)) ||
                   ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, _BIT1) == 0x00)) ||
                   ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, _BIT2) == 0x00)) ||
                   ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, _BIT3) == 0x00)))
                {
                    return _TRUE;
                }

                break;

            case _DP_TWO_LANE:

                if(((((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1)) || ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0))) &&
                    (ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, (_BIT1 | _BIT0)) == 0x00)) ||
                   ((((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2)) || ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0))) &&
                    (ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, (_BIT2 | _BIT0)) == 0x00)) ||
                   ((((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)) || ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0))) &&
                    (ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, (_BIT3 | _BIT0)) == 0x00)) ||
                   ((((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2)) || ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1))) &&
                    (ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, (_BIT2 | _BIT1)) == 0x00)) ||
                   ((((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)) || ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1))) &&
                    (ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, (_BIT3 | _BIT1)) == 0x00)) ||
                   ((((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)) || ((GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3) && (GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2))) &&
                    (ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, (_BIT3 | _BIT2)) == 0x00)))
                {
                    return _TRUE;
                }

                break;

            case _DP_FOUR_LANE:

                if(ScalerGetBit(PB0_06_DECODE_10B8B_ERROR, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x00)
                {
                    return _TRUE;
                }

                break;

            default:

                return _FALSE;

                break;
        }

        pData[1]--;
    }

    DebugMessageRx1("7. DP 8b/10b Decode Error", 0);

    return _FALSE;
}

//--------------------------------------------------
// Description : check DFE Coef
// Input Value  : None
// Output Value : True --> valid, False --> invalid
//--------------------------------------------------
bit ScalerDpRx1DFECheck(void)
{
    if(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR2)
    {
        return _TRUE;
    }

    switch(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)
    {
        case _DP_FOUR_LANE:

            // Read Lane2 DFE
            ScalerSetBit(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE2 << 6));

            // Read Back Vth
            ScalerSetBit(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(P7A_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(P7A_F1_COEF_2) & 0x1F);

            if(PDATA_WORD(0) == 0x0015)
            {
                DebugMessageRx1("7. Lane2 DFE Fail", 0);

                return _FALSE;
            }

            // Read Lane3 DFE
            ScalerSetBit(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE3 << 6));

            // Read Back Vth
            ScalerSetBit(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(P7A_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(P7A_F1_COEF_2) & 0x1F);

            if(PDATA_WORD(0) == 0x0015)
            {
                DebugMessageRx1("7. Lane3 DFE Fail", 0);

                return _FALSE;
            }

            // Read Lane1 DFE
            ScalerSetBit(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE1 << 6));

            // Read Back Vth
            ScalerSetBit(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(P7A_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(P7A_F1_COEF_2) & 0x1F);

            if(PDATA_WORD(0) == 0x0015)
            {
                DebugMessageRx1("7. Lane1 DFE Fail", 0);

                return _FALSE;
            }

            // Read Lane0 DFE
            ScalerSetBit(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE0 << 6));

            // Read Back Vth
            ScalerSetBit(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(P7A_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(P7A_F1_COEF_2) & 0x1F);

            if(PDATA_WORD(0) == 0x0015)
            {
                DebugMessageRx1("7. Lane0 DFE Fail", 0);

                return _FALSE;
            }

            break;

        case _DP_TWO_LANE:

            // Read Lane1 DFE
            ScalerSetBit(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE1 << 6));

            // Read Back Vth
            ScalerSetBit(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(P7A_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(P7A_F1_COEF_2) & 0x1F);

            if(PDATA_WORD(0) == 0x0015)
            {
                DebugMessageRx1("7. Lane1 DFE Fail", 0);

                return _FALSE;
            }

            // Read Lane0 DFE
            ScalerSetBit(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE0 << 6));

            // Read Back Vth
            ScalerSetBit(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(P7A_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(P7A_F1_COEF_2) & 0x1F);

            if(PDATA_WORD(0) == 0x0015)
            {
                DebugMessageRx1("7. Lane0 DFE Fail", 0);

                return _FALSE;
            }

            break;

        case _DP_ONE_LANE:

            // Read Lane0 DFE
            ScalerSetBit(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE0 << 6));

            // Read Back Vth
            ScalerSetBit(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData[0] = (ScalerGetByte(P7A_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData[1] = (ScalerGetByte(P7A_F1_COEF_2) & 0x1F);

            if(PDATA_WORD(0) == 0x0015)
            {
                DebugMessageRx1("7. Lane0 DFE Fail", 0);

                return _FALSE;
            }

            break;

        default:

            return _FALSE;

            break;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description : Check Valid Signal
// Input Value  : DP Link Rate and Lane Count
// Output Value : True --> valid, False --> invalid
//--------------------------------------------------
bit ScalerDpRx1SignalCheck(BYTE ucDpLinkRate, BYTE ucDpcdLane)
{
    WORD usDataStreamL0 = 0;
    WORD usDataStreamL1 = 0;
    WORD usDataStreamL2 = 0;
    WORD usDataStreamL3 = 0;

    if((ucDpLinkRate == _DP_LINK_HBR2) && (GET_DP_RX1_VALID_VIDEO_CHECK() == _FALSE))
    {
        return _TRUE;
    }

    // [5] ln_ck_sel = 1'b0 -> data stream
    // [4:0] DP_XTAL_CYCLE = 4'b00100 -> XTAL Counter Cycles = 2000 need to wait at least 75us
    ScalerSetBit(PB0_50_DP_SIG_DET_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);

    switch(ucDpcdLane)
    {
        case _DP_ONE_LANE:

            // [1:0] freqdet_lane_sel = 2'b00 -> Lane0
            ScalerSetBit(PB0_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), _D1_DP_LANE0);

            // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
            ScalerSetBit(PB0_52_DP_SIG_DET_2, ~_BIT6, 0x00);

            // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
            ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);
            ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

            // Waiting for Measure Done -> 150us
            for(pData[0] = 0; pData[0] <= 30; pData[0]++)
            {
                Delay5us(g_ucDelay5usN);

                if(ScalerGetBit(PB0_50_DP_SIG_DET_0, _BIT6) == _BIT6)
                {
                    usDataStreamL0 = ((((WORD)ScalerGetByte(PB0_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB0_54_DP_SIG_DET_4));

                    break;
                }
            }

            break;

        case _DP_TWO_LANE:

            // [1:0] freqdet_lane_sel = 2'b00 -> Lane0
            ScalerSetBit(PB0_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), _D1_DP_LANE0);

            // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
            ScalerSetBit(PB0_52_DP_SIG_DET_2, ~_BIT6, 0x00);

            // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
            ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);
            ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

            // Waiting for Measure Done -> 150us
            for(pData[0] = 0; pData[0] <= 30; pData[0]++)
            {
                Delay5us(g_ucDelay5usN);

                if(ScalerGetBit(PB0_50_DP_SIG_DET_0, _BIT6) == _BIT6)
                {
                    usDataStreamL0 = ((((WORD)ScalerGetByte(PB0_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB0_54_DP_SIG_DET_4));

                    break;
                }
            }

            // [1:0] freqdet_lane_sel = 2'b01 -> Lane1
            ScalerSetBit(PB0_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), _D1_DP_LANE1);

            // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
            ScalerSetBit(PB0_52_DP_SIG_DET_2, ~_BIT6, 0x00);

            // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
            ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);
            ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

            // Waiting for Measure Done -> 150us
            for(pData[0] = 0; pData[0] <= 30; pData[0]++)
            {
                Delay5us(g_ucDelay5usN);

                if(ScalerGetBit(PB0_50_DP_SIG_DET_0, _BIT6) == _BIT6)
                {
                    usDataStreamL1 = ((((WORD)ScalerGetByte(PB0_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB0_54_DP_SIG_DET_4));

                    break;
                }
            }

            break;

        default:
        case _DP_FOUR_LANE:

            // [1:0] freqdet_lane_sel = 2'b00 -> Lane0
            ScalerSetBit(PB0_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), _D1_DP_LANE0);

            // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
            ScalerSetBit(PB0_52_DP_SIG_DET_2, ~_BIT6, 0x00);

            // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
            ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);
            ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

            // Waiting for Measure Done -> 150us
            for(pData[0] = 0; pData[0] <= 30; pData[0]++)
            {
                Delay5us(g_ucDelay5usN);

                if(ScalerGetBit(PB0_50_DP_SIG_DET_0, _BIT6) == _BIT6)
                {
                    usDataStreamL0 = ((((WORD)ScalerGetByte(PB0_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB0_54_DP_SIG_DET_4));

                    break;
                }
            }

            // [1:0] freqdet_lane_sel = 2'b01 -> Lane1
            ScalerSetBit(PB0_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), _D1_DP_LANE1);

            // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
            ScalerSetBit(PB0_52_DP_SIG_DET_2, ~_BIT6, 0x00);

            // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
            ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);
            ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

            // Waiting for Measure Done -> 150us
            for(pData[0] = 0; pData[0] <= 30; pData[0]++)
            {
                Delay5us(g_ucDelay5usN);

                if(ScalerGetBit(PB0_50_DP_SIG_DET_0, _BIT6) == _BIT6)
                {
                    usDataStreamL1 = ((((WORD)ScalerGetByte(PB0_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB0_54_DP_SIG_DET_4));

                    break;
                }
            }

            // [1:0] freqdet_lane_sel = 2'b10 -> Lane2
            ScalerSetBit(PB0_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), _D1_DP_LANE2);

            // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
            ScalerSetBit(PB0_52_DP_SIG_DET_2, ~_BIT6, 0x00);

            // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
            ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);
            ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

            // Waiting for Measure Done -> 150us
            for(pData[0] = 0; pData[0] <= 30; pData[0]++)
            {
                Delay5us(g_ucDelay5usN);

                if(ScalerGetBit(PB0_50_DP_SIG_DET_0, _BIT6) == _BIT6)
                {
                    usDataStreamL2 = ((((WORD)ScalerGetByte(PB0_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB0_54_DP_SIG_DET_4));

                    break;
                }
            }

            // [1:0] freqdet_lane_sel = 2'b11 -> Lane3
            ScalerSetBit(PB0_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), _D1_DP_LANE3);

            // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT Value
            ScalerSetBit(PB0_52_DP_SIG_DET_2, ~_BIT6, 0x00);

            // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
            ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);
            ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

            // Waiting for Measure Done -> 150us
            for(pData[0] = 0; pData[0] <= 30; pData[0]++)
            {
                Delay5us(g_ucDelay5usN);

                if(ScalerGetBit(PB0_50_DP_SIG_DET_0, _BIT6) == _BIT6)
                {
                    usDataStreamL3 = ((((WORD)ScalerGetByte(PB0_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB0_54_DP_SIG_DET_4));

                    break;
                }
            }

            break;
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);

#if(_DP_MST_SUPPORT == _ON)
    // Data Stream Count Upper Bound = (VCO target count) x 2 x 0.65
    // Data Stream Count Lower Bound = (VCO target count) x 2 x 0.4
    switch(ucDpLinkRate)
    {
        case _DP_LINK_HBR2:

            switch(ucDpcdLane)
            {
                case _DP_ONE_LANE:

                    if((usDataStreamL0 > 0x32C8) || (usDataStreamL0 < 0x1F40))
                    {
                        return _FALSE;
                    }

                    break;

                case _DP_TWO_LANE:

                    if(((usDataStreamL1 > 0x32C8) || (usDataStreamL1 < 0x1F40)) || ((usDataStreamL0 > 0x32C8) || (usDataStreamL0 < 0x1F40)))
                    {
                        return _FALSE;
                    }

                    break;

                default:
                case _DP_FOUR_LANE:

                    if(((usDataStreamL3 > 0x32C8) || (usDataStreamL3 < 0x1F40)) ||
                       ((usDataStreamL2 > 0x32C8) || (usDataStreamL2 < 0x1F40)) ||
                       ((usDataStreamL1 > 0x32C8) || (usDataStreamL1 < 0x1F40)) ||
                       ((usDataStreamL0 > 0x32C8) || (usDataStreamL0 < 0x1F40)))
                    {
                        return _FALSE;
                    }

                    break;
            }

            break;

        case _DP_LINK_HBR:

            switch(ucDpcdLane)
            {
                case _DP_ONE_LANE:

                    if((usDataStreamL0 > 0x1964) || (usDataStreamL0 < 0xFA0))
                    {
                        return _FALSE;
                    }

                    break;

                case _DP_TWO_LANE:

                    if(((usDataStreamL1 > 0x1964) || (usDataStreamL1 < 0xFA0)) || ((usDataStreamL0 > 0x1964) || (usDataStreamL0 < 0xFA0)))
                    {
                        return _FALSE;
                    }

                    break;

                default:
                case _DP_FOUR_LANE:

                    if(((usDataStreamL3 > 0x1964) || (usDataStreamL3 < 0xFA0)) ||
                       ((usDataStreamL2 > 0x1964) || (usDataStreamL2 < 0xFA0)) ||
                       ((usDataStreamL1 > 0x1964) || (usDataStreamL1 < 0xFA0)) ||
                       ((usDataStreamL0 > 0x1964) || (usDataStreamL0 < 0xFA0)))
                    {
                        return _FALSE;
                    }

                    break;
            }

            break;

        default:
        case _DP_LINK_RBR:

            switch(ucDpcdLane)
            {
                case _DP_ONE_LANE:

                    if((usDataStreamL0 > 0xF3C) || (usDataStreamL0 < 0x960))
                    {
                        return _FALSE;
                    }

                    break;

                case _DP_TWO_LANE:

                    if(((usDataStreamL1 > 0xF3C) || (usDataStreamL1 < 0x960)) || ((usDataStreamL0 > 0xF3C) || (usDataStreamL0 < 0x960)))
                    {
                        return _FALSE;
                    }

                    break;

                default:
                case _DP_FOUR_LANE:

                    if(((usDataStreamL3 > 0xF3C) || (usDataStreamL3 < 0x960)) ||
                       ((usDataStreamL2 > 0xF3C) || (usDataStreamL2 < 0x960)) ||
                       ((usDataStreamL1 > 0xF3C) || (usDataStreamL1 < 0x960)) ||
                       ((usDataStreamL0 > 0xF3C) || (usDataStreamL0 < 0x960)))
                    {
                        return _FALSE;
                    }

                    break;
            }

            break;
    }
#else
    // Data Stream Count Upper Bound = (VCO target count) x 2 x 0.65
    // Data Stream Count Lower Bound = (VCO target count) x 2 x 0.55
    switch(ucDpLinkRate)
    {
        case _DP_LINK_HBR2:

            switch(ucDpcdLane)
            {
                case _DP_ONE_LANE:

                    if((usDataStreamL0 > 0x32C8) || (usDataStreamL0 < 0x2AF8))
                    {
                        return _FALSE;
                    }

                    break;

                case _DP_TWO_LANE:

                    if(((usDataStreamL1 > 0x32C8) || (usDataStreamL1 < 0x2AF8)) || ((usDataStreamL0 > 0x32C8) || (usDataStreamL0 < 0x2AF8)))
                    {
                        return _FALSE;
                    }

                    break;

                default:
                case _DP_FOUR_LANE:

                    if(((usDataStreamL3 > 0x32C8) || (usDataStreamL3 < 0x2AF8)) ||
                       ((usDataStreamL2 > 0x32C8) || (usDataStreamL2 < 0x2AF8)) ||
                       ((usDataStreamL1 > 0x32C8) || (usDataStreamL1 < 0x2AF8)) ||
                       ((usDataStreamL0 > 0x32C8) || (usDataStreamL0 < 0x2AF8)))
                    {
                        return _FALSE;
                    }

                    break;
            }

            break;

        case _DP_LINK_HBR:

            switch(ucDpcdLane)
            {
                case _DP_ONE_LANE:

                    if((usDataStreamL0 > 0x1964) || (usDataStreamL0 < 0x157C))
                    {
                        return _FALSE;
                    }

                    break;

                case _DP_TWO_LANE:

                    if(((usDataStreamL1 > 0x1964) || (usDataStreamL1 < 0x157C)) || ((usDataStreamL0 > 0x1964) || (usDataStreamL0 < 0x157C)))
                    {
                        return _FALSE;
                    }

                    break;

                default:
                case _DP_FOUR_LANE:

                    if(((usDataStreamL3 > 0x1964) || (usDataStreamL3 < 0x157C)) ||
                       ((usDataStreamL2 > 0x1964) || (usDataStreamL2 < 0x157C)) ||
                       ((usDataStreamL1 > 0x1964) || (usDataStreamL1 < 0x157C)) ||
                       ((usDataStreamL0 > 0x1964) || (usDataStreamL0 < 0x157C)))
                    {
                        return _FALSE;
                    }

                    break;
            }

            break;

        default:
        case _DP_LINK_RBR:

            switch(ucDpcdLane)
            {
                case _DP_ONE_LANE:

                    if((usDataStreamL0 > 0xF3C) || (usDataStreamL0 < 0xCE4))
                    {
                        return _FALSE;
                    }

                    break;

                case _DP_TWO_LANE:

                    if(((usDataStreamL1 > 0xF3C) || (usDataStreamL1 < 0xCE4)) || ((usDataStreamL0 > 0xF3C) || (usDataStreamL0 < 0xCE4)))
                    {
                        return _FALSE;
                    }

                    break;

                default:
                case _DP_FOUR_LANE:

                    if(((usDataStreamL3 > 0xF3C) || (usDataStreamL3 < 0xCE4)) ||
                       ((usDataStreamL2 > 0xF3C) || (usDataStreamL2 < 0xCE4)) ||
                       ((usDataStreamL1 > 0xF3C) || (usDataStreamL1 < 0xCE4)) ||
                       ((usDataStreamL0 > 0xF3C) || (usDataStreamL0 < 0xCE4)))
                    {
                        return _FALSE;
                    }

                    break;
            }

            break;
    }
#endif

    return _TRUE;
}

//--------------------------------------------------
// Description : check DFE Coef in INT0
// Input Value  : None
// Output Value : True --> valid, False --> invalid
//--------------------------------------------------
BYTE ScalerDpRx1DFECheck_EXINT0(void) using 1
{
    if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
    {
        return _TRUE;
    }

    switch(g_ucDpRx1LaneCount)
    {
        case _DP_FOUR_LANE:

            // Read Lane2 DFE
            ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE2 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData_EXINT[0] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData_EXINT[1] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x1F);

            if(PDATA_WORD_EXINT(0) == 0x0015)
            {
                return _FALSE;
            }

            // Read Lane3 DFE
            ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE3 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData_EXINT[0] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData_EXINT[1] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x1F);

            if(PDATA_WORD_EXINT(0) == 0x0015)
            {
                return _FALSE;
            }

            // Read Lane1 DFE
            ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE1 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData_EXINT[0] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData_EXINT[1] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x1F);

            if(PDATA_WORD_EXINT(0) == 0x0015)
            {
                return _FALSE;
            }

            // Read Lane0 DFE
            ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE0 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData_EXINT[0] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData_EXINT[1] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x1F);

            if(PDATA_WORD_EXINT(0) == 0x0015)
            {
                return _FALSE;
            }

            break;

        case _DP_TWO_LANE:

            // Read Lane1 DFE
            ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE1 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData_EXINT[0] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData_EXINT[1] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x1F);

            if(PDATA_WORD_EXINT(0) == 0x0015)
            {
                return _FALSE;
            }

            // Read Lane0 DFE
            ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE0 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData_EXINT[0] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData_EXINT[1] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x1F);

            if(PDATA_WORD_EXINT(0) == 0x0015)
            {
                return _FALSE;
            }

            break;

        case _DP_ONE_LANE:

            // Read Lane0 DFE
            ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE0 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData_EXINT[0] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData_EXINT[1] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x1F);

            if(PDATA_WORD_EXINT(0) == 0x0015)
            {
                return _FALSE;
            }

            break;

        default:

            return _FALSE;

            break;
    }

    return _TRUE;
}

#if(_WD_TIMER_INT_SUPPORT == _ON)
//--------------------------------------------------
// Description : check DFE Coef in WDINT
// Input Value  : None
// Output Value : True --> valid, False --> invalid
//--------------------------------------------------
BYTE ScalerDpRx1DFECheck_WDINT(void) using 3
{
    if(ScalerDpRx1GetDpcdInfo_WDINT(0x00, 0x01, 0x01) == _DP_LINK_HBR2)
    {
        return _TRUE;
    }

    switch(ScalerDpRx1GetDpcdInfo_WDINT(0x00, 0x01, 0x01) & 0x1F)
    {
        case _DP_FOUR_LANE:

            // Read Lane2 DFE
            ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE2 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData_EXINT[0] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData_EXINT[1] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x1F);

            if(PDATA_WORD_EXINT(0) == 0x0015)
            {
                return _FALSE;
            }

            // Read Lane3 DFE
            ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE3 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData_EXINT[0] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData_EXINT[1] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x1F);

            if(PDATA_WORD_EXINT(0) == 0x0015)
            {
                return _FALSE;
            }

            // Read Lane1 DFE
            ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE1 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData_EXINT[0] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData_EXINT[1] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x1F);

            if(PDATA_WORD_EXINT(0) == 0x0015)
            {
                return _FALSE;
            }

            // Read Lane0 DFE
            ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE0 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData_EXINT[0] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData_EXINT[1] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x1F);

            if(PDATA_WORD_EXINT(0) == 0x0015)
            {
                return _FALSE;
            }

            break;

        case _DP_TWO_LANE:

            // Read Lane1 DFE
            ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE1 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData_EXINT[0] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData_EXINT[1] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x1F);

            if(PDATA_WORD_EXINT(0) == 0x0015)
            {
                return _FALSE;
            }

            // Read Lane0 DFE
            ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE0 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData_EXINT[0] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData_EXINT[1] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x1F);

            if(PDATA_WORD_EXINT(0) == 0x0015)
            {
                return _FALSE;
            }

            break;

        case _DP_ONE_LANE:

            // Read Lane0 DFE
            ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_D1_DP_LANE0 << 6));

            // Read Back Vth
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            pData_EXINT[0] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F);

            // Read Back Tap0
            ScalerSetBit_EXINT(P7A_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            pData_EXINT[1] = (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x1F);

            if(PDATA_WORD_EXINT(0) == 0x0015)
            {
                return _FALSE;
            }

            break;

        default:

            return _FALSE;

            break;
    }

    return _TRUE;
}
#endif

//--------------------------------------------------
// Description  : Check Dp Video Straam VBID
// Input Value  : None
// Output Value : True --> Get Video Stream
//--------------------------------------------------
bit ScalerDpRx1GetVideoStream(void)
{
    if(ScalerGetBit(PB9_01_DP_VBID, _BIT3) == 0x00)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check Dp Video Straam VBID
// Input Value  : None
// Output Value : True --> Get Video Stream
//--------------------------------------------------
bit ScalerDpRx1MSACheck(void)
{
    // Pop up Main Stream Attributes
    ScalerSetBit(PB9_00_MN_STRM_ATTR_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT3));

    // Get Hactive
    ScalerRead(PB9_0C_MSA_HWD_0, 2, &pData[4], _AUTOINC);

    // Get Vactive
    ScalerRead(PB9_16_MSA_VHT_0, 2, &pData[12], _AUTOINC);

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_ENABLED() == _TRUE)
    {
        if((PDATA_WORD(2) == 0x00) || (PDATA_WORD(6) == 0x00))
        {
            return _FALSE;
        }
    }
    else
#endif
    {
#if((_ULTRA_HDR_SUPPORT == _ON) && (_AUDIO_SUPPORT == _ON))
        // Set Audio Info Type to RSV0 for HDR application
        ScalerSetByte(PB9_2C_DP_INFO_FM_RSV0, _DP_AUDIO_TIMESTAMP);
#endif
        // Get Htotal
        ScalerRead(PB9_08_MSA_HTT_0, 2, &pData[0], _AUTOINC);

        // Get Hstart
        ScalerRead(PB9_0A_MSA_HST_0, 2, &pData[2], _AUTOINC);

        // Get HSW
        ScalerRead(PB9_0E_MSA_HSW_0, 2, &pData[6], _AUTOINC);

        // Get Vtotal
        ScalerRead(PB9_10_MSA_VTTE_0, 2, &pData[8], _AUTOINC);

        // Get Vstart
        ScalerRead(PB9_14_MSA_VST_0, 2, &pData[10], _AUTOINC);

        // Get VSW
        ScalerRead(PB9_18_MSA_VSW_0, 2, &pData[14], _AUTOINC);

        if((PDATA_WORD(0) == 0x00) || (PDATA_WORD(1) == 0x00) || (PDATA_WORD(2) == 0x00) || ((PDATA_WORD(3) & 0x7FFF) == 0x00) ||
           (PDATA_WORD(4) == 0x00) || (PDATA_WORD(5) == 0x00) || (PDATA_WORD(6) == 0x00) || ((PDATA_WORD(7) & 0x7FFF) == 0x00))
        {
            if((PDATA_WORD(0) == 0x00) && (PDATA_WORD(1) == 0x00) && (PDATA_WORD(2) == 0x00) && ((PDATA_WORD(3) & 0x7FFF) == 0x00) &&
               (PDATA_WORD(4) == 0x00) && (PDATA_WORD(5) == 0x00) && (PDATA_WORD(6) == 0x00) && ((PDATA_WORD(7) & 0x7FFF) == 0x00))
            {
#if(_DP_MST_SUPPORT == _ON)
                if(GET_REG_DP_RX_MST_ENABLE() == _FALSE)
#endif
                {
                    if(ScalerDpRx1HdcpEnebled() == _TRUE)
                    {
                        if(GET_DP_RX1_MSA_FAIL_MAC_RESET_COUNT() < 10)
                        {
                            ADD_DP_RX1_MSA_FAIL_MAC_RESET_COUNT();
                        }
                        else
                        {
                            CLR_DP_RX1_MSA_FAIL_MAC_RESET_COUNT();

                            ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT1, _BIT1);
                            ScalerTimerDelayXms(30);
                            ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);

                            // Delay a Complete Frame
                            ScalerTimerDelayXms(30);
                        }
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
            }

            return _FALSE;
        }

        CLR_DP_RX1_MSA_FAIL_MAC_RESET_COUNT();
    }

    // Get Mvid
    ScalerRead(PB9_1A_MSA_MVID_0, 3, pData, _AUTOINC);

    if((((DWORD)pData[0] << 16) | ((DWORD)pData[1] << 8) | ((DWORD)pData[2] << 0)) == 0x00)
    {
        return _FALSE;
    }

    // Get Nvid
    ScalerRead(PB9_1D_MSA_NVID_0, 3, pData, _AUTOINC);

    if((((DWORD)pData[0] << 16) | ((DWORD)pData[1] << 8) | ((DWORD)pData[2] << 0)) == 0x00)
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Check DP Misc Information
// Input Value  : None
// Output Value : True --> DP Misc Check Ok
//--------------------------------------------------
bit ScalerDpRx1MiscCheck(void)
{
    BYTE ucInputPort = _D1_INPUT_PORT;

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
    // Check MISC1[6]
    if((ScalerGetBit(PB9_03_MN_STRM_ATTR_MISC1, _BIT6)) == _BIT6)
    {
        return ScalerDpRx1VscCheck();
    }
    else
#endif
    {
        // Get MISC Info
        BYTE ucMisc0 = ScalerGetByte(PB9_02_MN_STRM_ATTR_MISC);
        BYTE ucColorSpaceValue = (ScalerGetBit(PB9_03_MN_STRM_ATTR_MISC1, _BIT7)) | (ucMisc0 & (_BIT2 | _BIT1));

        // Color Space Check
#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)

        // Color format info source change from VSC --> MISC
        if(GET_DP_RX1_VSC_SDP_COLOR_MODE() == _TRUE)
        {
            switch(ucColorSpaceValue)
            {
                case _BIT1:
                    if(GET_COLOR_SPACE(ucInputPort) != _COLOR_SPACE_YCBCR422)
                    {
                        DebugMessageRx1("Misc change: Color Format, _COLOR_SPACE_YCBCR422", 0);
                        return _FALSE;
                    }
                    break;

                case _BIT2:
                    if(GET_COLOR_SPACE(ucInputPort) != _COLOR_SPACE_YCBCR444)
                    {
                        DebugMessageRx1("Misc change: Color Format, _COLOR_SPACE_YCBCR444", 0);
                        return _FALSE;
                    }
                    break;

                case _BIT7:
                    if(GET_COLOR_SPACE(ucInputPort) != _COLOR_SPACE_Y_ONLY)
                    {
                        DebugMessageRx1("Misc change: Color Format, _COLOR_SPACE_Y_ONLY", 0);
                        return _FALSE;
                    }
                    break;

                case (_BIT7 | _BIT1):
                    if(GET_COLOR_SPACE(ucInputPort) != _COLOR_SPACE_RAW)
                    {
                        DebugMessageRx1("Misc change: Color Format, _COLOR_SPACE_RAW", 0);
                        return _FALSE;
                    }
                    break;

                default:
                    if(GET_COLOR_SPACE(ucInputPort) != _COLOR_SPACE_RGB)
                    {
                        DebugMessageRx1("Misc change: Color Format, _COLOR_SPACE_RGB", 0);
                        return _FALSE;
                    }
                    break;
            }
        }
        else
#endif
        {
            if(ucColorSpaceValue != g_pstDigitalColorInfo[1].ucDigitalColorSpacePreValue)
            {
                return _FALSE;
            }
        }

        // Color Depth Check
        if((((ucMisc0 & (_BIT7 | _BIT6 | _BIT5))) >> 5) != g_pstDigitalColorInfo[1].b3DigitalColorDepthPreValue)
        {
            DebugMessageRx1("Misc change: Color Depth", (((ucMisc0 & (_BIT7 | _BIT6 | _BIT5))) >> 5));
            return _FALSE;
        }

        // Colorimetry Check
        if(GET_COLORIMETRY(ucInputPort) != _COLORIMETRY_EXT)
        {
            if(((ucMisc0 & (_BIT4 | _BIT3 | _BIT2 | _BIT1)) >> 1) != g_pstDigitalColorInfo[1].b4DigitalColorimetryPreValue)
            {
                if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
                {
                    DebugMessageRx1("Misc change: Colorimetry", 0);
                    return _FALSE;
                }
                else
                {
                    ScalerDpRx1ColorimetrySetting(ucInputPort, ((ucMisc0 & (_BIT4 | _BIT3 | _BIT2 | _BIT1)) >> 1));
                    SET_DIGITAL_COLORIMETRY_CHANGED(ucInputPort);
                }
            }
        }
        else
        {
            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
            {
                DebugMessageRx1("Misc change: Ext Colorimetry", 0);
                return _FALSE;
            }
            else
            {
                ScalerDpRx1ColorimetrySetting(ucInputPort, ((ucMisc0 & (_BIT4 | _BIT3 | _BIT2 | _BIT1)) >> 1));
                SET_DIGITAL_COLORIMETRY_CHANGED(ucInputPort);
            }
        }

        // Dynamic Range Check
        if((GET_COLOR_SPACE(ucInputPort) == _COLOR_SPACE_YCBCR444) || (GET_COLOR_SPACE(ucInputPort) == _COLOR_SPACE_YCBCR422))
        {
#if(_YCC_QUANTIZATION_RANGE_SUPPORT == _ON)
            if(((ucMisc0 & _BIT3) >> 3) != g_pstDigitalColorInfo[1].b2DigitalQuantizationPreValue)
            {
                if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
                {
                    DebugMessageRx1("Misc change: Dynamic Range", 0);
                    return _FALSE;
                }
                else
                {
                    ScalerDpRx1QuantizationSetting(ucInputPort, ((ucMisc0 & _BIT3) >> 3));
                    SET_DIGITAL_QUANTIZATION_CHANGED(ucInputPort);
                }
            }
#endif
        }
        else
        {
#if(_RGB_QUANTIZATION_RANGE_SUPPORT == _ON)
            if(((ucMisc0 & _BIT3) >> 3) != g_pstDigitalColorInfo[1].b2DigitalQuantizationPreValue)
            {
                if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
                {
                    DebugMessageRx1("Misc change: Dynamic Range", 0);
                    return _FALSE;
                }
                else
                {
                    ScalerDpRx1QuantizationSetting(ucInputPort, ((ucMisc0 & _BIT3) >> 3));
                    SET_DIGITAL_QUANTIZATION_CHANGED(ucInputPort);
                }
            }
#endif
        }

#if(_DP_FREESYNC_SUPPORT == _ON)
        if(GET_FREESYNC_ENABLED() == _FALSE)
#endif
        {
            // Get HSW
            ScalerRead(PB9_0E_MSA_HSW_0, 2, &pData[0], _AUTOINC);

            // Get VSW
            ScalerRead(PB9_18_MSA_VSW_0, 2, &pData[2], _AUTOINC);

            if(((PDATA_WORD(0) & 0x7FFF) == 0x00) || ((PDATA_WORD(1) & 0x7FFF) == 0x00))
            {
                return _FALSE;
            }
        }

        return _TRUE;
    }
}

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check DP VSC SDP Information
// Input Value  : None
// Output Value : True --> DP VSC SDP Check Ok
//--------------------------------------------------
bit ScalerDpRx1VscCheck(void)
{
    BYTE ucInputPort = _D1_INPUT_PORT;
    BYTE pucVscColorFormat[3];

    memset(pucVscColorFormat, 0, sizeof(pucVscColorFormat));

    // Read DB16~18 --> pucVscColorFormat[0:2]
#if(_HW_DP_VSC_SDP_REG_SUPPORT == _ON)
    ScalerRead(PB9_46_VSC15, 3, pucVscColorFormat, _AUTOINC);
#else
    if(GET_DP_RX1_RSV1_DETECTING() == _FALSE)
    {
        // Read DB16~18 --> pucVscColorFormat[0:2]
        ScalerGetDataPortByte(PB9_30_DP_INFO_FM_ADR, _DP_INFO_RSV1_DB16, 3, pucVscColorFormat, _AUTOINC);

        SET_DP_RX1_RSV1_DETECTING();
        ScalerTimerActiveTimerEvent((_DP_ONE_FRAME_TIME_MAX * 3), _SCALER_TIMER_EVENT_DP_RX1_RSV1_PACKET_DETECT);
    }
    else
    {
        return _TRUE;
    }
#endif

    // Color Space Check
    if(GET_DP_RX1_VSC_SDP_COLOR_MODE() == _FALSE)
    {
        // Color format info source change from MISC --> VSC
        switch(pucVscColorFormat[0] & (_BIT7 | _BIT6 | _BIT5 | _BIT4))
        {
            case _VSC_COLOR_SPACE_0:
                if(GET_COLOR_SPACE(ucInputPort) != _COLOR_SPACE_RGB)
                {
                    DebugMessageRx1("VSC change: Color Space, _COLOR_SPACE_RGB", 0);
                    return _FALSE;
                }

                break;

            case _VSC_COLOR_SPACE_1:
                if(GET_COLOR_SPACE(ucInputPort) != _COLOR_SPACE_YCBCR444)
                {
                    DebugMessageRx1("VSC change: Color Space, _COLOR_SPACE_YCBCR444", 0);
                    return _FALSE;
                }

                break;

            case _VSC_COLOR_SPACE_2:
                if(GET_COLOR_SPACE(ucInputPort) != _COLOR_SPACE_YCBCR422)
                {
                    DebugMessageRx1("VSC change: Color Space, _COLOR_SPACE_YCBCR422", 0);
                    return _FALSE;
                }

                break;

            case _VSC_COLOR_SPACE_3:
                if(GET_COLOR_SPACE(ucInputPort) != _COLOR_SPACE_YCBCR420)
                {
                    DebugMessageRx1("VSC change: Color Space, _COLOR_SPACE_YCBCR420", 0);
                    return _FALSE;
                }

                break;

            case _VSC_COLOR_SPACE_4:
                if(GET_COLOR_SPACE(ucInputPort) != _COLOR_SPACE_Y_ONLY)
                {
                    DebugMessageRx1("VSC change: Color Space, _COLOR_SPACE_Y_ONLY", 0);
                    return _FALSE;
                }

                break;

            case _VSC_COLOR_SPACE_5:
                if(GET_COLOR_SPACE(ucInputPort) != _COLOR_SPACE_RAW)
                {
                    DebugMessageRx1("VSC change: Color Space, _COLOR_SPACE_RAW", 0);
                    return _FALSE;
                }

                break;

            default:
                if(GET_COLOR_SPACE(ucInputPort) != _COLOR_SPACE_RGB)
                {
                    DebugMessageRx1("VSC change: Color Space, _COLOR_SPACE_RGB", 0);
                    return _FALSE;
                }

                break;
        }
    }
    else
    {
        if((pucVscColorFormat[0] & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) != g_pstDigitalColorInfo[1].ucDigitalColorSpacePreValue)
        {
            return _FALSE;
        }
    }

    // Color Depth Check
    if((pucVscColorFormat[1] & (_BIT2 | _BIT1 | _BIT0)) != g_pstDigitalColorInfo[1].b3DigitalColorDepthPreValue)
    {
        return _FALSE;
    }

    // Colorimetry Ext Check
    if(GET_COLORIMETRY(ucInputPort) == _COLORIMETRY_EXT)
    {
        if((pucVscColorFormat[0] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) != g_pstDigitalColorInfo[1].b4DigitalColorimetryExtPreValue)
        {
            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
            {
                DebugMessageRx1("VSC change: Colorimetry Ext", 0);
                return _FALSE;
            }
            else
            {
                ScalerDpRx1ColorimetryExtSetting(ucInputPort, (pucVscColorFormat[0] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)));
                SET_DIGITAL_COLORIMETRY_EXT_CHANGED(ucInputPort);
            }
        }
    }
    else
    {
        if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
        {
            DebugMessageRx1("VSC change: Colorimetry", 0);
            return _FALSE;
        }
        else
        {
            ScalerDpRx1ColorimetryExtSetting(ucInputPort, (pucVscColorFormat[0] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)));
            SET_DIGITAL_COLORIMETRY_EXT_CHANGED(ucInputPort);
        }
    }

    // Dynamic Range Check
    if((GET_COLOR_SPACE(ucInputPort) == _COLOR_SPACE_YCBCR444) || (GET_COLOR_SPACE(ucInputPort) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(ucInputPort) == _COLOR_SPACE_YCBCR420))
    {
#if(_YCC_QUANTIZATION_RANGE_SUPPORT == _ON)
        if(((pucVscColorFormat[1] & _BIT7) >> 7) != g_pstDigitalColorInfo[1].b2DigitalQuantizationPreValue)
        {
            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
            {
                DebugMessageRx1("VSC change: Dynamic Range", ((pucVscColorFormat[1] & _BIT7) >> 7));
                return _FALSE;
            }
            else
            {
                ScalerDpRx1QuantizationSetting(ucInputPort, ((pucVscColorFormat[1] & _BIT7) >> 7));
                SET_DIGITAL_QUANTIZATION_CHANGED(ucInputPort);
            }
        }
#endif
    }
    else
    {
#if(_RGB_QUANTIZATION_RANGE_SUPPORT == _ON)
        if(((pucVscColorFormat[1] & _BIT7) >> 7) != g_pstDigitalColorInfo[1].b2DigitalQuantizationPreValue)
        {
            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _TRUE)
            {
                DebugMessageRx1("VSC change: Dynamic Range", ((pucVscColorFormat[1] & _BIT7) >> 7));
                return _FALSE;
            }
            else
            {
                ScalerDpRx1QuantizationSetting(ucInputPort, ((pucVscColorFormat[1] & _BIT7) >> 7));
                SET_DIGITAL_QUANTIZATION_CHANGED(ucInputPort);
            }
        }
#endif
    }

    return _TRUE;
}

#if(_HW_DP_VSC_SDP_REG_SUPPORT != _ON)
//--------------------------------------------------
// Description  : DP Rx1 VSC Packet Detect Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1RSV1PacketDetectEvent(void)
{
    CLR_DP_RX1_RSV1_DETECTING();
}

//--------------------------------------------------
// Description  : Set DP Rx1 RSV1 infoframe type to VSC
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetInitialRSV1InfoType(void)
{
    // Set Packet Type of RSV1 to VSC
    ScalerSetByte(PB9_2D_DP_INFO_FM_RSV1, _DP_SDP_TYPE_VSC);

    CLR_DP_RX1_RSV1_DETECTING();
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_RSV1_PACKET_DETECT);

#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
    ScalerSetByte(PBC_54_DP_INFO_FM_RSV1, _DP_SDP_TYPE_VSC);

    CLR_DP_RX1_MST2SST_RSV1_DETECTING();
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_MST2SST_RSV1_PACKET_DETECT);
#endif
}
#endif
#endif

//--------------------------------------------------
// Description  : Check DP MSA Vactive / Hactive Change
// Input Value  : None
// Output Value : True --> DP Vactive / Hactive Information Check Ok
//--------------------------------------------------
bit ScalerDpRx1MSAActiveChange(void)
{
    // Pop up Main Stream Attributes
    ScalerSetBit(PB9_00_MN_STRM_ATTR_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT3));

    // Get Display Format Hactive
    ScalerRead(PB8_45_MN_DPF_HWD_M, 2, &pData[0], _AUTOINC);

    // Get MSA Hactive
    ScalerRead(PB9_0C_MSA_HWD_0, 2, &pData[2], _AUTOINC);

    // Get Display Format Vactive
    ScalerRead(PB8_4D_MN_DPF_VHT_M, 2, &pData[4], _AUTOINC);

    // Get MSA Vactive
    ScalerRead(PB9_16_MSA_VHT_0, 2, &pData[6], _AUTOINC);

    if((PDATA_WORD(0) != PDATA_WORD(1)) || (PDATA_WORD(2) != PDATA_WORD(3)))
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP RGB Output Disable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1AVMute(void)
{
    // Disable fifo overflwo/ underflwo IRQ
    ScalerSetBit(PB9_3A_DP_IRQ_CTRL0, ~(_BIT1 | _BIT0), 0x00);

    // Disable RGB Output
    ScalerSetBit(PB8_31_DP_OUTPUT_CTRL, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

#if(_AUDIO_SUPPORT == _ON)
    // Disable Audio Channel
    ScalerAudioDpAudioEnable(_DISABLE, _D1_INPUT_PORT);
#endif
}

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Sink Count Update
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1UpdateSinkCount(void)
{
    if(GET_DP_TX_HPD_DEBOUNCE_LEVEL() == _HIGH)
    {
        // Align Reported Cable status with Downstream Port
        SET_DP_RX_REPORT_DOWNSTREAM_DP_CABLE_STATUS(_DP_PLUG);

#if(_DP_MST_SUPPORT == _ON)
        if(g_enumDpMSTCapablePort == _DP_MST_RX1_PORT)
        {
            // Read Sink Count
            if(ScalerDpTxAuxNativeRead(0x00, 0x02, 0x00, 1, pData) == _TRUE)
            {
                // Set Rx Sink Count
                pData[1] = ScalerDpRx1GetDpcdInfo(0x00, 0x02, 0x00);

                // Downstream sink count number plus Branch device itself
                pData[1] = ((pData[1] & _BIT6) | (pData[0] & 0xBF)) + 1;
                ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x00, pData[1]);
            }
            else
            {
                ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x00, 0x41);
            }
        }
        else
#endif // End of #if(_DP_MST_SUPPORT == _ON)
        {
            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x00, 0x41);
        }
    }
    else
    {
        ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x00, 0x41);

        // Align Reported Cable status with Downstream Port
        SET_DP_RX_REPORT_DOWNSTREAM_DP_CABLE_STATUS(_DP_UNPLUG);
    }
}
#endif // End of #if(_DP_TX_SUPPORT == _ON)

#if(_WD_TIMER_INT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Handle DP Related WD Timer Event
// Input Value  : ucEventID
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1WDTimerEventProc_WDINT(EnumScalerWDTimerEventID enumEventID) using 3
{
    g_pucDpRx1Backup[0] = ScalerGetByte_EXINT(PBA_C1_DPCD_ADDR_PORT_H);
    g_pucDpRx1Backup[1] = ScalerGetByte_EXINT(PBA_C2_DPCD_ADDR_PORT_M);
    g_pucDpRx1Backup[2] = ScalerGetByte_EXINT(PBA_C3_DPCD_ADDR_PORT_L);

    if(enumEventID == _SCALER_WD_TIMER_EVENT_RX1_DP_LINK_STATUS_FAIL)
    {
        if(ScalerDpRx1DFECheck_WDINT() == _FALSE)
        {
            ScalerDpRx1DpcdLinkStatusReset_WDINT();

#if((_DP_TX_SUPPORT == _ON) && (_D1_DP_MST_PORT_SUPPORT == _ON))
            ScalerDpRx1HDCPResetDpcdInfo_WDINT();
#endif
            if(GET_D1_CABLE_STATUS() == _TRUE)
            {
                PCB_D1_HOTPLUG(_D1_HOT_PLUG_LOW);

                for(pData_EXINT[0] = 0; pData_EXINT[0] < 85; pData_EXINT[0]++)
                {
                    Delay5us_EXINT(g_ucDelay5usN);
                }

                PCB_D1_HOTPLUG(_D1_HOT_PLUG_HIGH);
            }
        }
    }

    ScalerSetByte_EXINT(PBA_C1_DPCD_ADDR_PORT_H, g_pucDpRx1Backup[0]);
    ScalerSetByte_EXINT(PBA_C2_DPCD_ADDR_PORT_M, g_pucDpRx1Backup[1]);
    ScalerSetByte_EXINT(PBA_C3_DPCD_ADDR_PORT_L, g_pucDpRx1Backup[2]);
}
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP BS to HS Delay Calculation
// Input Value  : None
// Output Value : BS to VS Delay
//--------------------------------------------------
WORD ScalerDpRx1GetBStoHSDelay(WORD usDpHtotal)
{
    WORD usFifoOffset = 0;
    BYTE ucInputPort = _D1_INPUT_PORT;

    pData[15] = GET_COLOR_DEPTH(ucInputPort);

    // DP fifo size = 256 x 96bit
    if(GET_COLOR_SPACE(ucInputPort) == _COLOR_SPACE_YCBCR422)
    {
        // FifoOffset = (1/2 * (256 * 96) / (2 * depth per color)), color format is YCbCr 4:2:2
        usFifoOffset = _HW_DP_RX_VIDEO_FIFO_SIZE / (4 * (WORD)pData[15]);
    }
    else
    {
        // FifoOffset = (1/2 * (256 * 96) / (3 * depth per color)), color format is RGB or YCbCr 4:4:4 or others
        usFifoOffset = _HW_DP_RX_VIDEO_FIFO_SIZE / (6 * (WORD)pData[15]);
    }

    // Get Hstart
    ScalerRead(PB8_43_MN_DPF_HST_M, 2, &pData[0], _AUTOINC);

    // Get Hactive
    ScalerRead(PB8_45_MN_DPF_HWD_M, 2, &pData[2], _AUTOINC);

    // H Blanking = HTotal - HActive
    PDATA_WORD(2) = usDpHtotal - PDATA_WORD(1);

    // Set BS to HS delay to (HBlanking + 1/2 FIFO - HStart), BS2HS delay: 2 pixel mode
    return ((WORD)((PDATA_WORD(2) + usFifoOffset - PDATA_WORD(0)) >> 1));
}

//--------------------------------------------------
// Description  : Get Current DP V Freq
// Input Value  : None
// Output Value : VFreq in 0.1Hz
//--------------------------------------------------
WORD ScalerDpRx1GetVFreq(void)
{
    // Pop up The result
    ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~_BIT5, _BIT5);

    PDATA_DWORD(0) = ((((DWORD)(ScalerGetByte(PB8_58_MN_MEAS_CTRL) & 0x1F)) << 16) | (((DWORD)ScalerGetByte(PB8_59_MN_MEAS_VLN_M)) << 8) | ((DWORD)ScalerGetByte(PB8_5A_MN_MEAS_VLN_L)));

    return (DWORD)_GDI_CLK_KHZ * 1000 / (PDATA_DWORD(0) / 10);
}

//--------------------------------------------------
// Description  : Get Current DP V Period
// Input Value  : None
// Output Value : V period in line
//--------------------------------------------------
WORD ScalerDpRx1GetVPeriod(void)
{
    DWORD ulVBs2BsCount = 0;
    WORD usHBs2BsCount = 0;

    // Pop up The result
    ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~_BIT5, _BIT5);

    // VBs2BS count in GDI clk
    ulVBs2BsCount = ((((DWORD)(ScalerGetByte(PB8_58_MN_MEAS_CTRL) & 0x1F)) << 16) | (((DWORD)ScalerGetByte(PB8_59_MN_MEAS_VLN_M)) << 8) | ((DWORD)ScalerGetByte(PB8_5A_MN_MEAS_VLN_L)));

    // HBs2Bs count in Link Clk / 2
    usHBs2BsCount = (((DWORD)ScalerGetByte(PB8_5B_MN_MEAS_HLN_M)) << 8) | ((DWORD)ScalerGetByte(PB8_5C_MN_MEAS_HLN_L));

    // VTotal in line, Link Clk / 2 : (Link Rate * 27 / 2)
    return (ulVBs2BsCount * (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) * 27 / 2) / usHBs2BsCount * 1000 / _GDI_CLK_KHZ);
}

//--------------------------------------------------
// Description  : Get Current DP H Period
// Input Value  : None
// Output Value : H period in nano sec
//--------------------------------------------------
WORD ScalerDpRx1GetHPeriod(void)
{
    // Pop up The result
    ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~_BIT5, _BIT5);

    // HBs2Bs count in Link Clk / 2
    PDATA_DWORD(0) = (((WORD)ScalerGetByte(PB8_5B_MN_MEAS_HLN_M)) << 8) | (ScalerGetByte(PB8_5C_MN_MEAS_HLN_L));

    return ((PDATA_DWORD(0) * 1000) / (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) * 27 / 2));
}

//--------------------------------------------------
// Description  : Get Current DP H Sync Width
// Input Value  : None
// Output Value : H Sync Width in pixel clk
//--------------------------------------------------
WORD ScalerDpRx1GetHSW(void)
{
    return ((((WORD)ScalerGetByte(PB8_47_MN_DPF_HSW_M) << 8) | (ScalerGetByte(PB8_48_MN_DPF_HSW_L))) & 0x7FFF);
}

//--------------------------------------------------
// Description  : Check FREESYNC Enable
// Input Value  : None
// Output Value : _TRUE: FREESYNC change
//--------------------------------------------------
bit ScalerDpRx1GetFREESYNCStatusChange(void)
{
    if((GET_FREESYNC_ENABLED() == _TRUE) && ((ScalerDpRx1GetVFreq() < (_PANEL_FREESYNC_MIN_FRAME_RATE - _FRAME_SYNC_MARGIN)) || (ScalerDpRx1GetVFreq() > (_PANEL_FREESYNC_MAX_FRAME_RATE + _FRAME_SYNC_MARGIN))))
    {
        DebugMessageRx1("7.FREESYNC IVF out of panel range", ScalerDpRx1GetVFreq());
        return _TRUE;
    }

    if((bit)(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x07) & _BIT7) != GET_FREESYNC_ENABLED())
    {
        DebugMessageRx1("7.FREESYNC ignore MSA 0 -> 1", 0);
        return _TRUE;
    }

    if((GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P) &&
       (GET_DP_RX1_FREESYNC_SUPPORT() != GET_FREESYNC_SUPPORT()))
    {
        SET_DP_RX_CAPABILITY_SWITCHED();
        SET_DP_RX1_FREESYNC_CAPABILITY_SWITCH();
        SET_DP_RX1_FREESYNC_SUPPORT(GET_FREESYNC_SUPPORT());

        if(GET_FREESYNC_SUPPORT() == _ON)
        {
            pData[0] = ScalerDpRx1GetDpcdInfo(0x00, 0x00, 0x07);
            ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x07, (pData[0] | _BIT6));
        }
        else
        {
            pData[0] = ScalerDpRx1GetDpcdInfo(0x00, 0x00, 0x07);
            ScalerDpRx1SetDpcdValue(0x00, 0x00, 0x07, (pData[0] & ~_BIT6));
        }

        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get AMD SPD Info Contents
// Input Value  : Content of Interest
// Output Value : Content Value
//--------------------------------------------------
BYTE ScalerDpRx1GetAmdSpdInfo(EnumAmdSpdInfoContent enumContent)
{
    if(ScalerGetByte(PB9_2C_DP_INFO_FM_RSV0) == _SPD_INFO_TYPE)
    {
        // Get AMD OUI
        ScalerGetDataPortByte(PB9_30_DP_INFO_FM_ADR, _DP_INFO_RSV0_DB1, 3, pData, _AUTOINC);

        if((pData[0] == 0x1A) && (pData[1] == 0x00) && (pData[2] == 0x00))
        {
            switch(enumContent)
            {
                case _SPD_INFO_FREESYNC_SUPPORT:

                    pData[0] = ScalerGetDataPortBit(PB9_30_DP_INFO_FM_ADR, _DP_INFO_RSV0_DB6, _BIT0);
                    return ((bit)pData[0]);

                case _SPD_INFO_FREESYNC_ENABLE:

                    pData[0] = ScalerGetDataPortBit(PB9_30_DP_INFO_FM_ADR, _DP_INFO_RSV0_DB6, _BIT1);
                    return ((bit)pData[0]);

                case _SPD_INFO_FREESYNC_ACTIVE:

                    pData[0] = ScalerGetDataPortBit(PB9_30_DP_INFO_FM_ADR, _DP_INFO_RSV0_DB6, _BIT2);
                    return ((bit)pData[0]);

                case _SPD_INFO_FREESYNC_MIN_VFREQ:

                    ScalerGetDataPortByte(PB9_30_DP_INFO_FM_ADR, _DP_INFO_RSV0_DB7, 1, pData, _NON_AUTOINC);

                    if(((WORD)pData[0] * 10) < _PANEL_FREESYNC_MIN_FRAME_RATE)
                    {
                        pData[0] = _PANEL_FREESYNC_MIN_FRAME_RATE / 10;
                        DebugMessageRx1("Freesync SPD info abnormal", 0);
                    }
                    else if(((WORD)pData[0] * 10) > _PANEL_FREESYNC_MAX_FRAME_RATE)
                    {
                        pData[0] = _PANEL_FREESYNC_MAX_FRAME_RATE / 10;
                        DebugMessageRx1("Freesync SPD info abnormal", 1);
                    }

                    return pData[0];

                case _SPD_INFO_FREESYNC_MAX_VFREQ:

                    ScalerGetDataPortByte(PB9_30_DP_INFO_FM_ADR, _DP_INFO_RSV0_DB8, 1, pData, _NON_AUTOINC);

                    if(((WORD)pData[0] * 10) < _PANEL_FREESYNC_MIN_FRAME_RATE)
                    {
                        pData[0] = _PANEL_FREESYNC_MIN_FRAME_RATE / 10;
                        DebugMessageRx1("Freesync SPD info abnormal", 0);
                    }
                    else if(((WORD)pData[0] * 10) > _PANEL_FREESYNC_MAX_FRAME_RATE)
                    {
                        pData[0] = _PANEL_FREESYNC_MAX_FRAME_RATE / 10;
                        DebugMessageRx1("Freesync SPD info abnormal", 1);
                    }

                    return pData[0];

                default:

                    return 0x00;
            }
        }

        return 0x00;
    }

    return 0x00;
}

//--------------------------------------------------
// Description  : Get AMD SPD Backup Info Contents
// Input Value  : Content of Interest
// Output Value : Content Value
//--------------------------------------------------
BYTE ScalerDpRx1GetAmdSpdBackupInfo(EnumAmdSpdInfoContent enumContent)
{
#if(_ULTRA_HDR_SUPPORT == _ON)
    if((GET_FREESYNC_ENABLED() == _TRUE) && (GET_DP_RX1_FREESYNC_INFO_FRAME_RECEIVED() == _TRUE))
    {
        // Check AMD OUI
        if((g_pucDPRx1RSV0Backup[1] == 0x1A) && (g_pucDPRx1RSV0Backup[2] == 0x00) && (g_pucDPRx1RSV0Backup[3] == 0x00))
        {
            switch(enumContent)
            {
                case _SPD_INFO_FREESYNC_SUPPORT:

                    return ((bit)(g_pucDPRx1RSV0Backup[6] & _BIT0));

                case _SPD_INFO_FREESYNC_ENABLE:

                    return ((bit)(g_pucDPRx1RSV0Backup[6] & _BIT1));

                case _SPD_INFO_FREESYNC_ACTIVE:

                    return ((bit)(g_pucDPRx1RSV0Backup[6] & _BIT2));

                case _SPD_INFO_FREESYNC_MIN_VFREQ:

                    pData[0] = g_pucDPRx1RSV0Backup[7];

                    if(((WORD)pData[0] * 10) < _PANEL_FREESYNC_MIN_FRAME_RATE)
                    {
                        pData[0] = _PANEL_FREESYNC_MIN_FRAME_RATE / 10;
                        DebugMessageRx1("Freesync SPD info abnormal", 0);
                    }
                    else if(((WORD)pData[0] * 10) > _PANEL_FREESYNC_MAX_FRAME_RATE)
                    {
                        pData[0] = _PANEL_FREESYNC_MAX_FRAME_RATE / 10;
                        DebugMessageRx1("Freesync SPD info abnormal", 1);
                    }

                    return pData[0];

                case _SPD_INFO_FREESYNC_MAX_VFREQ:

                    pData[0] = g_pucDPRx1RSV0Backup[8];

                    if(((WORD)pData[0] * 10) < _PANEL_FREESYNC_MIN_FRAME_RATE)
                    {
                        pData[0] = _PANEL_FREESYNC_MIN_FRAME_RATE / 10;
                        DebugMessageRx1("Freesync SPD info abnormal", 0);
                    }
                    else if(((WORD)pData[0] * 10) > _PANEL_FREESYNC_MAX_FRAME_RATE)
                    {
                        pData[0] = _PANEL_FREESYNC_MAX_FRAME_RATE / 10;
                        DebugMessageRx1("Freesync SPD info abnormal", 1);
                    }

                    return pData[0];

                default:

                    return 0x00;
            }
        }

        return 0x00;
    }

    return 0x00;
#else
    return ScalerDpRx1GetAmdSpdInfo(enumContent);
#endif
}
#endif // End of #if(_DP_FREESYNC_SUPPORT == _ON)

#if(_ULTRA_HDR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP InfoFrame RSV0 Check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1InfoFrameRSV0Check(void)
{
    BYTE pucDPRx1RSV0Data[_HW_DP_INFOFRAME_RSV0_LENGTH];
    BYTE ucInfoFrameType = 0;

    memset(pucDPRx1RSV0Data, 0, _HW_DP_INFOFRAME_RSV0_LENGTH);

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_ENABLED() == _TRUE)
    {
        ucInfoFrameType = _SPD_INFO_TYPE;
        CLR_DP_RX1_AUDIO_INFO_FRAME_RECEIVED();
    }
    else
#endif
    {
        ucInfoFrameType = _DP_AUDIO_TIMESTAMP;
        CLR_DP_RX1_FREESYNC_INFO_FRAME_RECEIVED();
    }

    ScalerDpRx1GetInfoFrameRSV0(pucDPRx1RSV0Data);

    if(ScalerGetByte(PB9_2C_DP_INFO_FM_RSV0) == _HDR_INFO_TYPE)
    {
        ScalerSetByte(PB9_2C_DP_INFO_FM_RSV0, ucInfoFrameType);

#if(_DP_FREESYNC_SUPPORT == _ON)
        if(((ucInfoFrameType == _SPD_INFO_TYPE) && (memcmp(pucDPRx1RSV0Data, g_pucDPRx1RSV0Backup, _HW_DP_INFOFRAME_RSV0_LENGTH) == 0)) ||
           ((ucInfoFrameType == _DP_AUDIO_TIMESTAMP) && (memcmp(&pucDPRx1RSV0Data[16], &g_pucDPRx1RSV0Backup[16], 12) == 0)))
#else
        if((ucInfoFrameType == _DP_AUDIO_TIMESTAMP) && (memcmp(&pucDPRx1RSV0Data[16], &g_pucDPRx1RSV0Backup[16], 12) == 0))
#endif
        {
            CLR_DP_RX1_HDR_INFO_FRAME_RECEIVED();
            DebugMessageRx1("no receive DP Rx1 HDR info frame", 0);
        }
        else
        {
            SET_DP_RX1_HDR_INFO_FRAME_RECEIVED();

            memcpy(g_pucDPRx1HDRBackup, pucDPRx1RSV0Data, _HW_DP_INFOFRAME_RSV0_LENGTH);
        }
    }
    else
    {
        ScalerSetByte(PB9_2C_DP_INFO_FM_RSV0, _HDR_INFO_TYPE);

        // Freesync or Audio info frame doesn't update
        if(memcmp(pucDPRx1RSV0Data, g_pucDPRx1HDRBackup, _HW_DP_INFOFRAME_RSV0_LENGTH) == 0)
        {
#if(_DP_FREESYNC_SUPPORT == _ON)
            if(ucInfoFrameType == _SPD_INFO_TYPE)
            {
                CLR_DP_RX1_FREESYNC_INFO_FRAME_RECEIVED();
            }
            else
#endif
            {
                CLR_DP_RX1_AUDIO_INFO_FRAME_RECEIVED();
            }

            DebugMessageRx1("no receive DP Rx1 Freesync or audio info frame", 0);
        }
        else
        {
#if(_DP_FREESYNC_SUPPORT == _ON)
            if(ucInfoFrameType == _SPD_INFO_TYPE)
            {
                SET_DP_RX1_FREESYNC_INFO_FRAME_RECEIVED();
            }
            else
#endif
            {
                SET_DP_RX1_AUDIO_INFO_FRAME_RECEIVED();
            }

            memcpy(g_pucDPRx1RSV0Backup, pucDPRx1RSV0Data, _HW_DP_INFOFRAME_RSV0_LENGTH);
        }
    }
}

//--------------------------------------------------
// Description  : HDMI Info Frame Packet Detect Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1RSV0PacketDetectEvent(void)
{
    CLR_DP_RX1_RSV0_DETECTING();
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpRx1GetInfoFrameRSV0(BYTE *pucDPRx1RSV0Data)
{
    BYTE ucTemp = 0;

    do
    {
        ScalerSetByte(PB9_30_DP_INFO_FM_ADR, (_DP_INFO_RSV0_DB0 + ucTemp));
        pucDPRx1RSV0Data[ucTemp] = ScalerGetByte(PB9_31_DP_INFO_FM_DAT);

        ucTemp ++;
    }
    while(ucTemp < _HW_DP_INFOFRAME_RSV0_LENGTH);
}
#endif

//--------------------------------------------------
// Description  : Set DP RSV0 infoframe type
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetInitialRSV0InfoType(void)
{
#if(_DP_FREESYNC_SUPPORT == _ON)
    // Set Freesync Info Type to RSV0
    ScalerSetByte(PB9_2C_DP_INFO_FM_RSV0, _SPD_INFO_TYPE);
#else
#if((_ULTRA_HDR_SUPPORT == _ON) && (_AUDIO_SUPPORT == _ON))
    // Set Audio Info Type to RSV0
    ScalerSetByte(PB9_2C_DP_INFO_FM_RSV0, _DP_AUDIO_TIMESTAMP);
#endif
#endif

#if(_ULTRA_HDR_SUPPORT == _ON)
    CLR_DP_RX1_RSV0_DETECTING();
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_RSV0_PACKET_DETECT);
#endif
}

//--------------------------------------------------
// Description  : DP BS to VS Delay Calculation
// Input Value  : None
// Output Value : BS to VS Delay
//--------------------------------------------------
DWORD ScalerDpRx1GetBStoVSDelay(void)
{
    DWORD ulVFrontPorch = 0;
    DWORD ulHFrontPorch = 0;
    WORD usFifoOffset = 0;
    BYTE ucInputPort = _D1_INPUT_PORT;

    // Get Htotal
    ScalerRead(PB9_08_MSA_HTT_0, 2, &pData[2], _AUTOINC);

    // VFrontPorch = 3 * Htotal * (Link Clk / Stream CLK)
    ulVFrontPorch = ((DWORD)GET_DP_RX1_VFRONT_PORCH()) * ((DWORD)PDATA_WORD(1) * 256) / ((DWORD)GET_D1_INPUT_PIXEL_CLK()) *
                    ((DWORD)ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) * 270) / 256;

    // Get Hactive
    ScalerRead(PB9_0C_MSA_HWD_0, 2, pData, _AUTOINC);

    // Get HSW
    pData[4] = ScalerGetBit(PB9_0E_MSA_HSW_0, (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    pData[5] = ScalerGetByte(PB9_0F_MSA_HSW_1);

    // Get HSW min by Measure clock
    PDATA_WORD(3) = ((DWORD) _DP_HSYNC_WIDTH_MEASURE_COUNTER * GET_D1_INPUT_PIXEL_CLK() * 100) / _MEASURE_CLK + 1;

    // Check HSW <= HSW min
    if(PDATA_WORD(2) <= PDATA_WORD(3))
    {
        // Check if H porch is more than HSW min
        if((PDATA_WORD(1) - PDATA_WORD(0)) >= PDATA_WORD(3))
        {
            // HSW = HSW min
            PDATA_WORD(2) = PDATA_WORD(3);
        }
        else
        {
            // HSW = Max H Porch
            PDATA_WORD(2) = (PDATA_WORD(1) - PDATA_WORD(0));
        }
    }

    // DPF H Front Porch must not be less than 8 (HW constraint)
    // Check if H porch is more than 8
    if((PDATA_WORD(1) - PDATA_WORD(0) - PDATA_WORD(2)) <= _DP_HSYNC_FRONT_PORCH)
    {
        // HSW < HSW min
        if(PDATA_WORD(2) < PDATA_WORD(3))
        {
            // Hstart = HSW
            PDATA_WORD(4) = PDATA_WORD(2);
        }
        else if((PDATA_WORD(1) - PDATA_WORD(0) - PDATA_WORD(3) >= _DP_HSYNC_FRONT_PORCH))
        {
            // HSW = H porch - _DP_HSYNC_FRONT_PORCH
            PDATA_WORD(2) = PDATA_WORD(1) - PDATA_WORD(0) - _DP_HSYNC_FRONT_PORCH;

            // Hstart = HSW
            PDATA_WORD(4) = PDATA_WORD(2);
        }
        else
        {
            // HSW = HSW min
            PDATA_WORD(2) = PDATA_WORD(3);

            // Hstart = HSW min
            PDATA_WORD(4) = PDATA_WORD(3);
        }
    }
    else
    {
        // Hstart = Htotal - Hactive - _DP_HSYNC_FRONT_PORCH
        PDATA_WORD(4) = PDATA_WORD(1) - PDATA_WORD(0) - _DP_HSYNC_FRONT_PORCH;
    }

    // HFrontPorch = (Htotal - Hactive - Hstart) * (Link Clk / Stream CLK)
    ulHFrontPorch = (((DWORD)(PDATA_WORD(1) - PDATA_WORD(0) - PDATA_WORD(4))) * (((DWORD)ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00)) * 270) / ((DWORD)GET_D1_INPUT_PIXEL_CLK()));

    pData[15] = GET_COLOR_DEPTH(ucInputPort);

    // DP fifo size = 256 x 96bit
    if(GET_COLOR_SPACE(ucInputPort) == _COLOR_SPACE_YCBCR422)
    {
        // FifoOffset = (1/2 * (256 * 96) / (2 * depth per color)), color format is YCbCr 4:2:2
        usFifoOffset = _HW_DP_RX_VIDEO_FIFO_SIZE / (4 * (WORD)pData[15]);
    }
    else
    {
        // FifoOffset = (1/2 * (256 * 96) / (3 * depth per color)), color format is RGB or YCbCr 4:4:4 or others
        usFifoOffset = _HW_DP_RX_VIDEO_FIFO_SIZE / (6 * (WORD)pData[15]);
    }

    // FifoOffset = (1/2 * (256 * 96) / (3 * depth per color)) * (Link Clk / Stream CLK))
    usFifoOffset = (WORD)(((DWORD)usFifoOffset) * (((DWORD)ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00)) * 270) / ((DWORD)GET_D1_INPUT_PIXEL_CLK()));

    return ((ulVFrontPorch + ulHFrontPorch + (DWORD)usFifoOffset) / 2);
}

//--------------------------------------------------
// Description  : Check Dp Interlace by VBID or Measure
// Input Value  : None
// Output Value : True --> Interlace
//--------------------------------------------------
bit ScalerDpRx1InterlaceCheck(WORD *pusVTotal, BYTE *pucOddFlg)
{
    DWORD ulLinkClk = 0;
    WORD usTempVTotal = *pusVTotal;
    WORD usHTotalCount = 0;
    WORD usVsyncWidth = 0;
    WORD usVstart = 0;
    WORD usVactive = 0;

    // Set Vfront Porch
    SET_DP_RX1_VFRONT_PORCH(_DP_VSYNC_FRONT_PORCH);

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_ENABLED() == _TRUE)
    {
        // Field inverse disable
        ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~_BIT4, 0x00);

        if(ScalerGetBit(PB9_01_DP_VBID, _BIT2) == _BIT2) // Interlace
        {
            // Start to Measure Vertical BS to BS Counter by GDI Clock
            ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~_BIT7, 0x00);
            ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~_BIT7, _BIT7);

            if(ScalerTimerPollingFlagProc(_DP_MEASURE_POLLING_TIMEOUT, PB8_58_MN_MEAS_CTRL, _BIT6, _TRUE) == _FALSE)
            {
                return _FALSE;
            }

            // Pop up The result
            ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~_BIT5, _BIT5);

            // Get Measure Result
            ScalerRead(PB8_58_MN_MEAS_CTRL, 3, &pData[5], _AUTOINC);

            // Delay 2ms To Get VBID
            ScalerTimerDelayXms(2);

            // Get VBID
            ScalerRead(PB9_01_DP_VBID, 1, &pData[1], _NON_AUTOINC);

            // Delay 1 frame
            ScalerTimerDelayXms((((PDATA_DWORD(1) & 0x001FFFFF) / (_GDI_CLK_KHZ)) + 2));

            // Pop up Measure Result
            ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~_BIT5, _BIT5);

            // Get Measure Result
            ScalerRead(PB8_58_MN_MEAS_CTRL, 3, &pData[9], _AUTOINC);

            // Get VBID
            ScalerRead(PB9_01_DP_VBID, 1, &pData[2], _NON_AUTOINC);

            PDATA_DWORD(1) = (PDATA_DWORD(1) & 0x001FFFFF);
            PDATA_DWORD(2) = (PDATA_DWORD(2) & 0x001FFFFF);

            if((pData[1] & _BIT1) != (pData[2] & _BIT1))
            {
                // Enable DP Interlace, Field Information reference to VBID
                ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT6), _BIT7);

                if((ScalerGetBit(PB8_57_INTERLACE_MODE_CONFIG, _BIT0) == 0x00) &&
                   ((((pData[1] & _BIT1) == _BIT1) && ((pData[2] & _BIT1) == 0x00) && (PDATA_DWORD(1) < PDATA_DWORD(2))) ||
                    (((pData[1] & _BIT1) == 0x00) && ((pData[2] & _BIT1) == _BIT1) && (PDATA_DWORD(1) > PDATA_DWORD(2)))))
                {
                    // Field inverse enable
                    ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~_BIT4, _BIT4);
                }
            }
            else
            {
                // Enable interlace mode, field reference HW
                ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
            }

            *pusVTotal = usTempVTotal;

            return _TRUE;
        }
    }
    else
#endif
    {
        // [5] ln_ck_sel = 1'b1 -> CDR Clock
        // [4:0] DP_XTAL_CYCLE = 5'b00100 -> XTAL Counter Cycles = 2000
        ScalerSetBit(PB0_50_DP_SIG_DET_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT2));

        // [1:0] freqdet_lane_sel = 2'b00 -> Lane0
        ScalerSetBit(PB0_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), _D1_DP_LANE0);

        // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
        ScalerSetBit(PB0_52_DP_SIG_DET_2, ~_BIT6, 0x00);

        // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
        ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);
        ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

        // Waiting for Measure Done
        ScalerTimerDelayXms(2);

        if(ScalerGetBit(PB0_50_DP_SIG_DET_0, _BIT6) == _BIT6)
        {
            PDATA_WORD(0) = ((((WORD)ScalerGetByte(PB0_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB0_54_DP_SIG_DET_4));
        }
        else
        {
            if(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR2)
            {
                PDATA_WORD(0) = 0x4E20;
            }
            else if(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR)
            {
                PDATA_WORD(0) = 0x2710;
            }
            else // Both Default && _DP_LINK_RBR Case
            {
                PDATA_WORD(0) = 0x1770;
            }
        }

        // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
        ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);

        PDATA_DWORD(0) = (((DWORD)PDATA_WORD(0)) * _GDI_CLK_KHZ);

        // Link Clk in KHz
        ulLinkClk = (PDATA_DWORD(0) / 1000);

        DebugMessageRx1("Current Link Clk", ulLinkClk);

        // Field inverse disable
        ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~_BIT4, 0x00);

        // Start to Measure Vertical BS to BS Counter by GDI Clock
        ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~_BIT7, 0x00);
        ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~_BIT7, _BIT7);

        if(ScalerTimerPollingFlagProc(_DP_MEASURE_POLLING_TIMEOUT, PB8_58_MN_MEAS_CTRL, _BIT6, _TRUE) == _FALSE)
        {
            return _FALSE;
        }

        // Pop up The result
        ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~_BIT5, _BIT5);

        // Get Measure Result
        ScalerRead(PB8_58_MN_MEAS_CTRL, 3, &pData[5], _AUTOINC);

        // Delay 2ms To Get VBID
        ScalerTimerDelayXms(2);

        // Get VBID
        ScalerRead(PB9_01_DP_VBID, 1, &pData[1], _NON_AUTOINC);

        // Delay 1 frame
        ScalerTimerDelayXms((((PDATA_DWORD(1) & 0x001FFFFF) / (_GDI_CLK_KHZ)) + 2));

        // Pop up Measure Result
        ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~_BIT5, _BIT5);

        // Get Measure Result
        ScalerRead(PB8_58_MN_MEAS_CTRL, 3, &pData[9], _AUTOINC);

        // Get Measure Htotal Counts
        ScalerRead(PB8_5B_MN_MEAS_HLN_M, 2, &pData[12], _AUTOINC);

        // Get VBID
        ScalerRead(PB9_01_DP_VBID, 1, &pData[2], _NON_AUTOINC);

        PDATA_DWORD(1) = (PDATA_DWORD(1) & 0x001FFFFF);
        PDATA_DWORD(2) = (PDATA_DWORD(2) & 0x001FFFFF);

        // Disable Measure Block
        ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~_BIT7, 0x00);

        // Convert HTotal Count from 1/2 Link Clk to GDI Clk
        usHTotalCount = ((DWORD)PDATA_WORD(6) * _GDI_CLK_KHZ * 2 + (ulLinkClk >> 1)) / ulLinkClk;

        DebugMessageRx1("HTotal Count", usHTotalCount);

        // if VTotal Difference > 1/2 HTotal
        if((ABSDWORD(PDATA_DWORD(1), PDATA_DWORD(2))) > (usHTotalCount / 2))
        {
            if(PDATA_DWORD(1) < PDATA_DWORD(2))
            {
                usTempVTotal = ((PDATA_DWORD(1) * 8 + (usHTotalCount >> 1)) / usHTotalCount);
            }
            else
            {
                usTempVTotal = ((PDATA_DWORD(2) * 8 + (usHTotalCount >> 1)) / usHTotalCount);
            }

            usTempVTotal = (usTempVTotal + 4) / 8;

            *pucOddFlg = _TRUE;
        }
        else
        {
            *pucOddFlg = _FALSE;
        }

        DebugMessageRx1("####Calculated usVTotal####", usTempVTotal);

        DebugMessageRx1("7. DelayTime", (((PDATA_DWORD(1) & 0x000FFFFF) / (_GDI_CLK_KHZ)) + 2));
        DebugMessageRx1("7. PDATA_DWORD(1)", PDATA_DWORD(1));
        DebugMessageRx1("7. PDATA_DWORD(2)", PDATA_DWORD(2));
        DebugMessageRx1("7. PDATA_DWORD(ABS)", (ABSDWORD(PDATA_DWORD(1), PDATA_DWORD(2))));

        if(ScalerGetBit(PB9_01_DP_VBID, _BIT2) == _BIT2) // Interlace
        {
            // Get VSW
            usVsyncWidth = ((WORD)ScalerGetByte(PB9_18_MSA_VSW_0) << 8) | ScalerGetByte(PB9_19_MSA_VSW_1);
            usVsyncWidth &= 0x7FFF;

            // Get VStart
            usVstart = ((WORD)ScalerGetByte(PB9_14_MSA_VST_0) << 8) | ScalerGetByte(PB9_15_MSA_VST_1);

            // usVbackporch = usVstart - Fixed V-Sync Pulse Width, usVbackporch > usVsyncWidth + 2 lines, here 2 lines is for V-Sync Falling edge to DEN Rising Edge distance margion
            if(((pData[1] & _BIT1) != (pData[2] & _BIT1)) && (usVstart > (usVsyncWidth + _DP_VSYNC_WIDTH + 2)))
            {
                // Enable DP Interlace, Field Information reference to VBID
                ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT6), _BIT7);

                // Get Vactive
                usVactive = ((WORD)ScalerGetByte(PB9_16_MSA_VHT_0) << 8) | ScalerGetByte(PB9_17_MSA_VHT_1);

                // Set Front Porch = VTotal - Active height - MSA V Start + V Sync Pulse Width
                SET_DP_RX1_VFRONT_PORCH(usTempVTotal - usVactive - usVstart + usVsyncWidth);

                if((ScalerGetBit(PB8_57_INTERLACE_MODE_CONFIG, _BIT0) == 0x00) &&
                   ((((pData[1] & _BIT1) == _BIT1) && ((pData[2] & _BIT1) == 0x00) && (PDATA_DWORD(1) < PDATA_DWORD(2))) ||
                    (((pData[1] & _BIT1) == 0x00) && ((pData[2] & _BIT1) == _BIT1) && (PDATA_DWORD(1) > PDATA_DWORD(2)))))
                {
                    // Field inverse enable
                    ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~_BIT4, _BIT4);
                }
            }
            else
            {
                // Enable interlace mode, field reference HW
                ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
            }

            *pusVTotal = usTempVTotal;

            return _TRUE;
        }
        else if((ABSDWORD(PDATA_DWORD(1), PDATA_DWORD(2))) > (usHTotalCount / 2))
        {
            // Enable interlace mode, field reference HW
            ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            *pusVTotal = usTempVTotal;

            return _TRUE;
        }
    }

    // Disable DP Interlace
    ScalerSetBit(PB8_57_INTERLACE_MODE_CONFIG, ~(_BIT7 | _BIT6), 0x00);

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Get Video Info
// Input Value  : None
// Output Value : TRUE --> Get successfully
//--------------------------------------------------
bit ScalerDpRx1GetVideoInfo(void)
{
#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
    CLR_DP_RX1_VSC_SDP_COLOR_MODE();

    // Check MISC1[6]
    if((ScalerGetBit(PB9_03_MN_STRM_ATTR_MISC1, _BIT6)) == _BIT6)
    {
        // Use VSC SDP
        SET_DP_RX1_VSC_SDP_COLOR_MODE();

#if(_HW_DP_VSC_SDP_REG_SUPPORT == _ON)

        // Read DB16~18 --> pData[0:2]
        ScalerRead(PB9_46_VSC15, 3, pData, _AUTOINC);
#else
        // Delay 2 frames for SRAM ready (worst case)
        ScalerTimerDelayXms(_DP_ONE_FRAME_TIME_MAX * 2);

        SET_DP_RX1_RSV1_DETECTING();

        ScalerTimerActiveTimerEvent((_DP_ONE_FRAME_TIME_MAX * 3), _SCALER_TIMER_EVENT_DP_RX1_RSV1_PACKET_DETECT);

        // Read DB16~18 --> pData[0:2]
        ScalerGetDataPortByte(PB9_30_DP_INFO_FM_ADR, _DP_INFO_RSV1_DB16, 3, pData, _AUTOINC);
#endif
        // Set Color Info PreValue
        g_pstDigitalColorInfo[1].b4DigitalColorimetryExtPreValue = (pData[0] & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
        g_pstDigitalColorInfo[1].b2DigitalQuantizationPreValue = ((pData[1] & _BIT7) >> 7);
        g_pstDigitalColorInfo[1].b3DigitalColorDepthPreValue = (pData[1] & (_BIT2 | _BIT1 | _BIT0));
        g_pstDigitalColorInfo[1].ucDigitalColorSpacePreValue = (pData[0] & (_BIT7 | _BIT6 | _BIT5 | _BIT4));

        DebugMessageRx1("VSC DB16", pData[0]);
        DebugMessageRx1("VSC DB17", pData[1]);
    }
    else
#endif
    {
        // Get MISC Info
        pData[0] = ScalerGetByte(PB9_02_MN_STRM_ATTR_MISC);

        // Set ColorimetryPreValue & QuantizationPreValue
        g_pstDigitalColorInfo[1].b4DigitalColorimetryPreValue = (pData[0] & (_BIT4 | _BIT3 | _BIT2 | _BIT1)) >> 1;
        g_pstDigitalColorInfo[1].b2DigitalQuantizationPreValue = (pData[0] & _BIT3) >> 3;
        g_pstDigitalColorInfo[1].b3DigitalColorDepthPreValue = (pData[0] & (_BIT7 | _BIT6 | _BIT5)) >> 5;
        g_pstDigitalColorInfo[1].ucDigitalColorSpacePreValue = ((ScalerGetBit(PB9_03_MN_STRM_ATTR_MISC1, _BIT7)) | (pData[0] & (_BIT2 | _BIT1)));
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Set Color Info Macros
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetColorInfo(void)
{
    BYTE ucInputPort = _D1_INPUT_PORT;

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
    if(GET_DP_RX1_VSC_SDP_COLOR_MODE() == _TRUE)
    {
        // Use VSC SDP
        // Set Color Space Macro
        switch(g_pstDigitalColorInfo[1].ucDigitalColorSpacePreValue)
        {
            case _VSC_COLOR_SPACE_0:
                SET_COLOR_SPACE(ucInputPort, _COLOR_SPACE_RGB);
                break;

            case _VSC_COLOR_SPACE_1:
                SET_COLOR_SPACE(ucInputPort, _COLOR_SPACE_YCBCR444);
                break;

            case _VSC_COLOR_SPACE_2:
                SET_COLOR_SPACE(ucInputPort, _COLOR_SPACE_YCBCR422);
                break;

            case _VSC_COLOR_SPACE_3:
                SET_COLOR_SPACE(ucInputPort, _COLOR_SPACE_YCBCR420);
                break;

            case _VSC_COLOR_SPACE_4:
                SET_COLOR_SPACE(ucInputPort, _COLOR_SPACE_Y_ONLY);
                break;

            case _VSC_COLOR_SPACE_5:
                SET_COLOR_SPACE(ucInputPort, _COLOR_SPACE_RAW);
                break;

            default:
                SET_COLOR_SPACE(ucInputPort, _COLOR_SPACE_RGB);
                break;
        }

        // Set Colorimetry Ext
        ScalerDpRx1ColorimetryExtSetting(ucInputPort, g_pstDigitalColorInfo[1].b4DigitalColorimetryExtPreValue);
    }
    else
#endif
    {
        // Set Color Space Macro
        switch(g_pstDigitalColorInfo[1].ucDigitalColorSpacePreValue)
        {
            case _BIT1:
                SET_COLOR_SPACE(ucInputPort, _COLOR_SPACE_YCBCR422);
                break;

            case _BIT2:
                SET_COLOR_SPACE(ucInputPort, _COLOR_SPACE_YCBCR444);
                break;

            case _BIT7:
                SET_COLOR_SPACE(ucInputPort, _COLOR_SPACE_Y_ONLY);
                break;

            case (_BIT7 | _BIT1):
                SET_COLOR_SPACE(ucInputPort, _COLOR_SPACE_RAW);
                break;

            default:
                SET_COLOR_SPACE(ucInputPort, _COLOR_SPACE_RGB);
                break;
        }

        // Set Colorimetry
        ScalerDpRx1ColorimetrySetting(ucInputPort, (g_pstDigitalColorInfo[1].b4DigitalColorimetryPreValue << 1));
    }

    // Set Color Depth Macro
    if(GET_COLOR_SPACE(ucInputPort) != _COLOR_SPACE_RAW)
    {
        switch(g_pstDigitalColorInfo[1].b3DigitalColorDepthPreValue)
        {
            case 0:
                SET_COLOR_DEPTH(ucInputPort, _COLOR_DEPTH_6_BITS);
                break;

            case 1:
                SET_COLOR_DEPTH(ucInputPort, _COLOR_DEPTH_8_BITS);
                break;

            case 2:
                SET_COLOR_DEPTH(ucInputPort, _COLOR_DEPTH_10_BITS);
                break;

            case 3:
                SET_COLOR_DEPTH(ucInputPort, _COLOR_DEPTH_12_BITS);
                break;

            case 4:
                SET_COLOR_DEPTH(ucInputPort, _COLOR_DEPTH_16_BITS);
                break;

            default:
                SET_COLOR_DEPTH(ucInputPort, _COLOR_DEPTH_8_BITS);
                break;
        }
    }
    else
    {
        switch(g_pstDigitalColorInfo[1].b3DigitalColorDepthPreValue)
        {
            case 1:
                SET_COLOR_DEPTH(ucInputPort, _COLOR_DEPTH_6_BITS);
                break;

            case 2:
                SET_COLOR_DEPTH(ucInputPort, _COLOR_DEPTH_7_BITS);
                break;

            case 3:
                SET_COLOR_DEPTH(ucInputPort, _COLOR_DEPTH_8_BITS);
                break;

            case 4:
                SET_COLOR_DEPTH(ucInputPort, _COLOR_DEPTH_10_BITS);
                break;

            case 5:
                SET_COLOR_DEPTH(ucInputPort, _COLOR_DEPTH_12_BITS);
                break;

            case 6:
                SET_COLOR_DEPTH(ucInputPort, _COLOR_DEPTH_14_BITS);
                break;

            case 7:
                SET_COLOR_DEPTH(ucInputPort, _COLOR_DEPTH_16_BITS);
                break;

            default:
                SET_COLOR_DEPTH(ucInputPort, _COLOR_DEPTH_8_BITS);
                break;
        }
    }

    // Set Porch Color
    if((GET_COLOR_SPACE(ucInputPort) == _COLOR_SPACE_YCBCR444) || (GET_COLOR_SPACE(ucInputPort) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(ucInputPort) == _COLOR_SPACE_YCBCR420))
    {
        if(g_pstDigitalColorInfo[1].b2DigitalQuantizationPreValue == _DP_COLOR_QUANTIZATION_LIMIT)
        {
            SET_DP_RX1_PORCH_COLOR_YCC_LIMIT(ucInputPort);
        }
        else if(g_pstDigitalColorInfo[1].b2DigitalQuantizationPreValue == _DP_COLOR_QUANTIZATION_FULL)
        {
            SET_DP_RX1_PORCH_COLOR_YCC_FULL(ucInputPort);
        }
    }
    else
    {
        SET_DP_RX1_PORCH_COLOR_RGB();
    }

    // Set Quantization Range
    ScalerDpRx1QuantizationSetting(ucInputPort, g_pstDigitalColorInfo[1].b2DigitalQuantizationPreValue);
}

//--------------------------------------------------
// Description  : DP Video Setting for PG
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1VideoSetting(void)
{
    BYTE ucInputPort = _D1_INPUT_PORT;

    // Set Color Space for Display Format Gen.
    switch(GET_COLOR_SPACE(ucInputPort))
    {
        case _COLOR_SPACE_RGB:
            DebugMessageRx1("_COLOR_SPACE_RGB", 0);
            ScalerSetBit(PB8_20_PG_CTRL_0, ~(_BIT4 | _BIT3), 0x00);
            break;

        case _COLOR_SPACE_YCBCR444:
            DebugMessageRx1("_COLOR_SPACE_YCBCR444", 0);
            ScalerSetBit(PB8_20_PG_CTRL_0, ~(_BIT4 | _BIT3), _BIT4);
            break;

        case _COLOR_SPACE_YCBCR422:
            DebugMessageRx1("_COLOR_SPACE_YCBCR422", 0);
            ScalerSetBit(PB8_20_PG_CTRL_0, ~(_BIT4 | _BIT3), _BIT3);
            break;

        case _COLOR_SPACE_YCBCR420:
            DebugMessageRx1("_COLOR_SPACE_YCBCR420", 0);
            ScalerSetBit(PB8_20_PG_CTRL_0, ~(_BIT4 | _BIT3), 0x00);
            break;

        case _COLOR_SPACE_Y_ONLY:
            DebugMessageRx1("_COLOR_SPACE_Y_ONLY", 0);
            ScalerSetBit(PB8_20_PG_CTRL_0, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
            break;

        case _COLOR_SPACE_RAW:
            DebugMessageRx1("_COLOR_SPACE_RAW", 0);
            ScalerSetBit(PB8_20_PG_CTRL_0, ~(_BIT4 | _BIT3), 0x00);
            break;

        default:
            // RGB
            ScalerSetBit(PB8_20_PG_CTRL_0, ~(_BIT4 | _BIT3), 0x00);
            break;
    }

    // Set Color Depth for Display Format Gen.
    ScalerSetBit(PB8_20_PG_CTRL_0, ~(_BIT2 | _BIT1 | _BIT0), g_pstDigitalColorInfo[1].b3DigitalColorDepthPreValue);
    DebugMessageRx1("_COLOR_DEPTH", GET_COLOR_DEPTH(ucInputPort));
}

//--------------------------------------------------
// Description  : DP Rx1 Colorimetry Setting
// Input Value  : ucInputPort, ucColorimetryValue
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1ColorimetrySetting(BYTE ucInputPort, BYTE ucColorimetryValue)
{
    if((GET_COLOR_SPACE(ucInputPort) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(ucInputPort) == _COLOR_SPACE_YCBCR444))
    {
        switch(ucColorimetryValue & (_BIT4 | _BIT3))
        {
            case 0:
                SET_COLORIMETRY(ucInputPort, _COLORIMETRY_YCC_XVYCC601);
                DebugMessageRx1("_COLORIMETRY_YCC_XVYCC601", 0);
                break;

            case _BIT3:
                SET_COLORIMETRY(ucInputPort, _COLORIMETRY_YCC_ITUR_BT601);
                DebugMessageRx1("_COLORIMETRY_YCC_ITUR_BT601", 0);
                break;

            case _BIT4:
                SET_COLORIMETRY(ucInputPort, _COLORIMETRY_YCC_XVYCC709);
                DebugMessageRx1("_COLORIMETRY_YCC_XVYCC709", 0);
                break;

            case (_BIT4 | _BIT3):
                SET_COLORIMETRY(ucInputPort, _COLORIMETRY_YCC_ITUR_BT709);
                DebugMessageRx1("_COLORIMETRY_YCC_ITUR_BT709", 0);
                break;

            default:
                break;
        }
    }
    else if(GET_COLOR_SPACE(ucInputPort) == _COLOR_SPACE_RGB)
    {
        switch(ucColorimetryValue & (_BIT4 | _BIT3 | _BIT2 | _BIT1))
        {
            case 0:
                SET_COLORIMETRY(ucInputPort, _COLORIMETRY_RGB_SRGB);
                DebugMessageRx1("_COLORIMETRY_RGB_SRGB", 0);
                break;

            case _BIT3:
                SET_COLORIMETRY(ucInputPort, _COLORIMETRY_RGB_SRGB);
                DebugMessageRx1("_COLORIMETRY_RGB_SRGB", 0);
                break;

            case (_BIT2 | _BIT1):
                SET_COLORIMETRY(ucInputPort, _COLORIMETRY_RGB_XRRGB);
                DebugMessageRx1("_COLORIMETRY_RGB_XRRGB", 0);
                break;

            case (_BIT4 | _BIT2 | _BIT1):
                SET_COLORIMETRY(ucInputPort, _COLORIMETRY_RGB_SCRGB);
                DebugMessageRx1("_COLORIMETRY_RGB_SCRGB", 0);
                break;

            case (_BIT4 | _BIT3):
                SET_COLORIMETRY(ucInputPort, _COLORIMETRY_RGB_ADOBERGB);
                DebugMessageRx1("_COLORIMETRY_RGB_ADOBERGB", 0);
                break;

            case (_BIT3 | _BIT2 | _BIT1):
                SET_COLORIMETRY(ucInputPort, _COLORIMETRY_RGB_DCI_P3);
                DebugMessageRx1("_COLORIMETRY_RGB_DCI_P3", 0);
                break;

            case (_BIT4 | _BIT3 | _BIT2 | _BIT1):
                SET_COLORIMETRY(ucInputPort, _COLORIMETRY_RGB_COLOR_PROFILE);
                DebugMessageRx1("_COLORIMETRY_RGB_COLOR_PROFILE", 0);
                break;

            default:
                SET_COLORIMETRY(ucInputPort, _COLORIMETRY_RGB_SRGB);
                DebugMessageRx1("_COLORIMETRY_RGB_SRGB", 0);
                break;
        }
    }
    else if(GET_COLOR_SPACE(ucInputPort) == _COLOR_SPACE_Y_ONLY)
    {
        SET_COLORIMETRY(ucInputPort, _COLORIMETRY_Y_ONLY);
        DebugMessageRx1("_COLORIMETRY_Y_ONLY", 0);
    }
    else if(GET_COLOR_SPACE(ucInputPort) == _COLOR_SPACE_RAW)
    {
        SET_COLORIMETRY(ucInputPort, _COLORIMETRY_RAW);
        DebugMessageRx1("_COLORIMETRY_RAW", 0);
    }
}

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Rx1 Colorimetry Extended Setting
// Input Value  : ucInputPort, ucColorimetryValue
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1ColorimetryExtSetting(BYTE ucInputPort, BYTE ucColorimetryValue)
{
    SET_COLORIMETRY(ucInputPort, _COLORIMETRY_EXT);

    if((GET_COLOR_SPACE(ucInputPort) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(ucInputPort) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(ucInputPort) == _COLOR_SPACE_YCBCR444))
    {
        switch(ucColorimetryValue)
        {
            case _VSC_COLORIMETRY_0:
                SET_EXT_COLORIMETRY(ucInputPort, _COLORIMETRY_EXT_YCC_ITUR_BT601);
                DebugMessageRx1("_COLORIMETRY_EXT_YCC_ITUR_BT601", 0);
                break;

            case _VSC_COLORIMETRY_1:
                SET_EXT_COLORIMETRY(ucInputPort, _COLORIMETRY_EXT_YCC_ITUR_BT709);
                DebugMessageRx1("_COLORIMETRY_EXT_YCC_ITUR_BT709", 0);
                break;

            case _VSC_COLORIMETRY_2:
                SET_EXT_COLORIMETRY(ucInputPort, _COLORIMETRY_EXT_YCC_XVYCC601);
                DebugMessageRx1("_COLORIMETRY_EXT_YCC_XVYCC601", 0);
                break;

            case _VSC_COLORIMETRY_3:
                SET_EXT_COLORIMETRY(ucInputPort, _COLORIMETRY_EXT_YCC_XVYCC709);
                DebugMessageRx1("_COLORIMETRY_EXT_YCC_XVYCC709", 0);
                break;

            case _VSC_COLORIMETRY_4:
                SET_EXT_COLORIMETRY(ucInputPort, _COLORIMETRY_EXT_YCC_SYCC601);
                DebugMessageRx1("_COLORIMETRY_EXT_YCC_SYCC601", 0);
                break;

            case _VSC_COLORIMETRY_5:
                SET_EXT_COLORIMETRY(ucInputPort, _COLORIMETRY_EXT_YCC_ADOBEYCC601);
                DebugMessageRx1("_COLORIMETRY_EXT_YCC_ADOBEYCC601", 0);
                break;

            case _VSC_COLORIMETRY_6:
                SET_EXT_COLORIMETRY(ucInputPort, _COLORIMETRY_EXT_YCC_ITUR_BT2020_CL);
                DebugMessageRx1("_COLORIMETRY_EXT_YCC_ITUR_BT2020_CL", 0);
                break;

            case _VSC_COLORIMETRY_7:
                SET_EXT_COLORIMETRY(ucInputPort, _COLORIMETRY_EXT_YCC_ITUR_BT2020_NCL);
                DebugMessageRx1("_COLORIMETRY_EXT_YCC_ITUR_BT2020_NCL", 0);
                break;

            default:
                SET_EXT_COLORIMETRY(ucInputPort, _COLORIMETRY_EXT_RESERVED);
                DebugMessageRx1("_COLORIMETRY_EXT_RESERVED", 0);
                break;
        }
    }
    else if(GET_COLOR_SPACE(ucInputPort) == _COLOR_SPACE_RGB)
    {
        switch(ucColorimetryValue)
        {
            case _VSC_COLORIMETRY_0:
                SET_EXT_COLORIMETRY(ucInputPort, _COLORIMETRY_EXT_RGB_SRGB);
                DebugMessageRx1("_COLORIMETRY_EXT_RGB_SRGB", 0);
                break;

            case _VSC_COLORIMETRY_1:
                SET_EXT_COLORIMETRY(ucInputPort, _COLORIMETRY_EXT_RGB_XRRGB);
                DebugMessageRx1("_COLORIMETRY_EXT_RGB_XRRGB", 0);
                break;

            case _VSC_COLORIMETRY_2:
                SET_EXT_COLORIMETRY(ucInputPort, _COLORIMETRY_EXT_RGB_SCRGB);
                DebugMessageRx1("_COLORIMETRY_EXT_RGB_SCRGB", 0);
                break;

            case _VSC_COLORIMETRY_3:
                SET_EXT_COLORIMETRY(ucInputPort, _COLORIMETRY_EXT_RGB_ADOBERGB);
                DebugMessageRx1("_COLORIMETRY_EXT_RGB_ADOBERGB", 0);
                break;

            case _VSC_COLORIMETRY_4:
                SET_EXT_COLORIMETRY(ucInputPort, _COLORIMETRY_EXT_RGB_DCI_P3);
                DebugMessageRx1("_COLORIMETRY_EXT_RGB_DCI_P3", 0);
                break;

            case _VSC_COLORIMETRY_5:
                SET_EXT_COLORIMETRY(ucInputPort, _COLORIMETRY_EXT_RGB_CUSTOM_COLOR_PROFILE);
                DebugMessageRx1("_COLORIMETRY_EXT_RGB_CUSTOM_COLOR_PROFILE", 0);
                break;

            case _VSC_COLORIMETRY_6:
                SET_EXT_COLORIMETRY(ucInputPort, _COLORIMETRY_EXT_RGB_ITUR_BT2020);
                DebugMessageRx1("_COLORIMETRY_EXT_RGB_ITUR_BT2020", 0);
                break;

            default:
                SET_EXT_COLORIMETRY(ucInputPort, _COLORIMETRY_EXT_RESERVED);
                DebugMessageRx1("_COLORIMETRY_EXT_RESERVED", 0);
                break;
        }
    }
    else if(GET_COLOR_SPACE(ucInputPort) == _COLOR_SPACE_Y_ONLY)
    {
        SET_EXT_COLORIMETRY(ucInputPort, _COLORIMETRY_EXT_Y_ONLY_DICOM_PART14);
        DebugMessageRx1("_COLORIMETRY_EXT_Y_ONLY_DICOM_PART14", 0);
    }
    else if(GET_COLOR_SPACE(ucInputPort) == _COLOR_SPACE_RAW)
    {
        SET_EXT_COLORIMETRY(ucInputPort, _COLORIMETRY_EXT_RAW_CUSTOM_COLOR_PROFILE);
        DebugMessageRx1("_COLORIMETRY_EXT_RAW_CUSTOM_COLOR_PROFILE", 0);
    }
}
#endif

//--------------------------------------------------
// Description  : DP Rx1 Quantization Setting
// Input Value  : ucInputPort, ucQuantizationValue
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1QuantizationSetting(BYTE ucInputPort, BYTE ucQuantizationValue)
{
    if((GET_COLOR_SPACE(ucInputPort) == _COLOR_SPACE_YCBCR420) || (GET_COLOR_SPACE(ucInputPort) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(ucInputPort) == _COLOR_SPACE_YCBCR444))
    {
        if(ucQuantizationValue == _DP_COLOR_QUANTIZATION_FULL)
        {
            SET_COLOR_YCC_QUANTIZATION_RANGE(ucInputPort, _YCC_QUANTIZATION_FULL_RANGE);
            DebugMessageRx1("_YCC_QUANTIZATION_FULL_RANGE", 0);
        }
        else
        {
            SET_COLOR_YCC_QUANTIZATION_RANGE(ucInputPort, _YCC_QUANTIZATION_LIMIT_RANGE);
            DebugMessageRx1("_YCC_QUANTIZATION_LIMIT_RANGE", 0);
        }

        SET_COLOR_RGB_QUANTIZATION_RANGE(ucInputPort, _RGB_QUANTIZATION_RESERVED);
    }
    else
    {
        if(ucQuantizationValue == _DP_COLOR_QUANTIZATION_FULL)
        {
            SET_COLOR_RGB_QUANTIZATION_RANGE(ucInputPort, _RGB_QUANTIZATION_FULL_RANGE);
            DebugMessageRx1("_RGB_QUANTIZATION_FULL_RANGE", 0);
        }
        else
        {
            SET_COLOR_RGB_QUANTIZATION_RANGE(ucInputPort, _RGB_QUANTIZATION_LIMIT_RANGE);
            DebugMessageRx1("_RGB_QUANTIZATION_LIMIT_RANGE", 0);
        }

        SET_COLOR_YCC_QUANTIZATION_RANGE(ucInputPort, _YCC_QUANTIZATION_FULL_RANGE);
    }
}

//--------------------------------------------------
// Description  : DP Stream Clk PLL Setting
// Input Value  : None
// Output Value : True --> Stream CLK Regen. ok
//--------------------------------------------------
bit ScalerDpRx1StreamClkRegenerate(void)
{
    DWORD ulStreamClkValue = 0;
    SDWORD lOffsetValue = 0;
    DWORD ulpllm = 0;
    DWORD ulXtal_clk = 0;
    WORD usDpHtotal = 0;
    WORD usDpVtotal = 0;
    DWORD ulVBs2BsCount = 0;
    DWORD ulDpNvidValue = 0;
    BYTE ucpllo = 0;
    BYTE ucdivs = 0;
    BYTE ucdiv2 = 0;
    BYTE ucplln = 0;
    BYTE ucBuf = 0;
    BYTE ucdiv_pllo = 0;
    BYTE ucdiv_divs = 0;

#if(_DP_FREESYNC_SUPPORT == _ON)
    DWORD ulDpMvidValue = 0;
#endif

    if(ScalerDpLinkClockValid() != _DP_LCLK_FAIL)
    {
        // PLL Input Clock select to Link Clock, Output Clock Select to PLL Clock, Double Buffer.
        ScalerSetBit(PB8_A0_MN_SCLKG_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));
    }
    else
    {
        // PLL Input Clock select to XTAL, Output Clock Select to PLL Clock, Double Buffer.
        ScalerSetBit(PB8_A0_MN_SCLKG_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);
    }

    ulDpNvidValue = ((((DWORD)ScalerGetByte(PB9_1D_MSA_NVID_0)) << 16) | (((DWORD)ScalerGetByte(PB9_1E_MSA_NVID_1)) << 8) | ((DWORD)ScalerGetByte(PB9_1F_MSA_NVID_2)));

    usDpHtotal = ((((WORD)ScalerGetByte(PB8_41_MN_DPF_HTT_M)) << 8) | ((WORD)ScalerGetByte(PB8_42_MN_DPF_HTT_L)));

    usDpVtotal = ((((WORD)ScalerGetByte(PB8_49_MN_DPF_VTT_M)) << 8) | ((WORD)ScalerGetByte(PB8_4A_MN_DPF_VTT_L)));

    // [5] ln_ck_sel = 1'b1 -> CDR Clock
    // [4:0] DP_XTAL_CYCLE = 5'b00100 -> XTAL Counter Cycles = 2000
    ScalerSetBit(PB0_50_DP_SIG_DET_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT2));

    // [1:0] freqdet_lane_sel = 2'b00 -> Lane0
    ScalerSetBit(PB0_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), _D1_DP_LANE0);

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
    ScalerSetBit(PB0_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
    ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);
    ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

    // Waiting for Measure Done
    ScalerTimerDelayXms(2);

    if(ScalerDpLinkClockValid() == _DP_LCLK_DIVIDE_BY_1)
    {
        if(ScalerGetBit(PB0_50_DP_SIG_DET_0, _BIT6) == _BIT6)
        {
            PDATA_WORD(0) = ((((WORD)ScalerGetByte(PB0_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB0_54_DP_SIG_DET_4));
        }
        else
        {
            if(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR2)
            {
                PDATA_WORD(0) = 0x4E20;
            }
            else if(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR)
            {
                PDATA_WORD(0) = 0x2710;
            }
            else // Both Default && _DP_LINK_RBR Case
            {
                PDATA_WORD(0) = 0x1770;
            }
        }

        // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
        ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);

        PDATA_DWORD(0) = (((DWORD)PDATA_WORD(0)) * _GDI_CLK_KHZ);

        // PLL Reference Clock is Link_Clk
        ulXtal_clk = PDATA_DWORD(0) / 1000;

        ucplln = ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00);
    }
    else if(ScalerDpLinkClockValid() == _DP_LCLK_DIVIDE_BY_2)
    {
        if(ScalerGetBit(PB0_50_DP_SIG_DET_0, _BIT6) == _BIT6)
        {
            PDATA_WORD(0) = ((((WORD)ScalerGetByte(PB0_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB0_54_DP_SIG_DET_4));
        }
        else
        {
            if(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR2)
            {
                PDATA_WORD(0) = 0x4E20;
            }
            else if(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR)
            {
                PDATA_WORD(0) = 0x2710;
            }
            else // Both Default && _DP_LINK_RBR Case
            {
                PDATA_WORD(0) = 0x1770;
            }
        }

        // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
        ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);

        PDATA_DWORD(0) = (((DWORD)PDATA_WORD(0)) * _GDI_CLK_KHZ);

        // PLL Reference Clock is Link_Clk/2
        ulXtal_clk = (PDATA_DWORD(0) / 1000 / 2);

        ucplln = (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) / 2);
    }
    else
    {
        if(ScalerGetBit(PB0_50_DP_SIG_DET_0, _BIT6) == _BIT6)
        {
            PDATA_WORD(0) = ((((WORD)ScalerGetByte(PB0_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB0_54_DP_SIG_DET_4));
        }
        else
        {
            if(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR2)
            {
                PDATA_WORD(0) = 0x4E20;
            }
            else if(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR)
            {
                PDATA_WORD(0) = 0x2710;
            }
            else // Both Default && _DP_LINK_RBR Case
            {
                PDATA_WORD(0) = 0x1770;
            }
        }

        // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
        ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);

        PDATA_DWORD(0) = (((DWORD)PDATA_WORD(0)) * _GDI_CLK_KHZ);

        ulXtal_clk = _GDI_CLK_KHZ;

        ucplln = 2;
    }

    // Measurement Enable
    ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~_BIT7, 0x00);
    ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~_BIT7, _BIT7);

    if(ScalerTimerPollingFlagProc(_DP_MEASURE_POLLING_TIMEOUT, PB8_58_MN_MEAS_CTRL, _BIT6, _TRUE) == _FALSE)
    {
        return _FALSE;
    }

    // Pop up The result
    ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~_BIT5, _BIT5);

    ulVBs2BsCount = ((((DWORD)(ScalerGetByte(PB8_58_MN_MEAS_CTRL) & 0x1F)) << 16) | ((DWORD)ScalerGetByte(PB8_59_MN_MEAS_VLN_M) << 8) | ((DWORD)ScalerGetByte(PB8_5A_MN_MEAS_VLN_L)));

    // Measurement Disable
    ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~_BIT7, 0x00);

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_ENABLED() == _TRUE)
    {
        ulDpMvidValue = ((((DWORD)ScalerGetByte(PB9_1A_MSA_MVID_0)) << 16) | (((DWORD)ScalerGetByte(PB9_1B_MSA_MVID_1)) << 8) | ((DWORD)ScalerGetByte(PB9_1C_MSA_MVID_2)));

        // Calculate streamclk
        ulStreamClkValue = ((DWORD)ulDpMvidValue * (PDATA_DWORD(0) / ulDpNvidValue) + (PDATA_DWORD(0) % ulDpNvidValue * 100 / ulDpNvidValue * (DWORD)ulDpMvidValue / 100));
    }
    else
#endif
    {
        // Calculate streamclk (Unit is Hz)
        ulStreamClkValue = (((((DWORD)usDpHtotal) * ((DWORD)usDpVtotal) * 100) / ulVBs2BsCount) * _GDI_CLK_KHZ * 10);
    }

    // Input Pixel CLK Unit is 0.1 M
    SET_D1_INPUT_PIXEL_CLK(ulStreamClkValue / 100000);

    DebugMessageRx1("Stream Clk", ulStreamClkValue);

    // Get DPLL parameter
    // If "600Mhz > ulStreamClkValue > 270Mhz"
    if((600000000 > ulStreamClkValue) && (ulStreamClkValue >= 270000000))
    {
        ucpllo = 0;
        ucdivs = 0;

        ucdiv_divs = 1;
        ucdiv_pllo = 1;

        ulpllm = ((((ulStreamClkValue / 4) * ucdiv_divs * ucdiv_pllo) * ucplln / 250 + (ulXtal_clk / 4)) / (ulXtal_clk));

        if(ulpllm > 257)
        {
            return _FALSE;
        }
    }
    // If "270MHz > ulStreamClkValue > 4.21875Mhz"
    else if((ulStreamClkValue < 270000000) && (ulStreamClkValue >= 4218750))
    {
        ucpllo = 1;

        if((ulStreamClkValue < 270000000) && (ulStreamClkValue >= 135000000))
        {
            ucdivs = 0;
        }
        else if((ulStreamClkValue < 135000000) && (ulStreamClkValue >= 67500000))
        {
            ucdivs = 1;
        }
        else if((ulStreamClkValue < 67500000) && (ulStreamClkValue >= 33750000))
        {
            ucdivs = 2;
        }
        else if((ulStreamClkValue < 33750000) && (ulStreamClkValue >= 16875000))
        {
            ucdivs = 4;
        }
        else if((ulStreamClkValue < 16875000) && (ulStreamClkValue >= 8437500))
        {
            ucdivs = 8;
        }
        else
        {
            ucdivs = 16;
        }

        // Because set 17 get minimum error for recovery stream clk , close to fact clk.
        if(ucdivs == 0)
        {
            ucdiv_divs = 1;
        }
        else
        {
            ucdiv_divs = 2 * ucdivs;
        }

        ucdiv_pllo = 1;

        if(ucpllo != 0)
        {
            ucdiv_pllo = 1;

            for(ucBuf = 0; ucBuf < ucpllo; ucBuf++)
            {
                ucdiv_pllo = 2 * ucdiv_pllo;
            }
        }

        ulpllm = ((((ulStreamClkValue / 4) * ucdiv_divs * ucdiv_pllo) * ucplln / 250 + (ulXtal_clk / 4)) / (ulXtal_clk));

        if(ulpllm > 257)
        {
            return _FALSE;
        }
    }
    else
    {
        return _FALSE;
    }

    ulpllm++;

    // offset = (m/n*f_ref - f)/(m/n*f_ref)*2^21
    // seperate *2^21 to *32*16384*4
    lOffsetValue = ((SDWORD)((ulXtal_clk * 1000 / ucplln) * ulpllm) - (SDWORD)(ulStreamClkValue * ucdiv_pllo * ucdiv_divs)) * 32 / ulpllm * ucplln / ulXtal_clk * 16384 / 1000 * 4;

    lOffsetValue = 0x7FFFF - lOffsetValue + 1;

    // DPPLL Power Down
    ScalerSetBit(PB8_BD_MN_SCLKG_PLL_PWR, ~_BIT7, _BIT7);

    /*
    // Disable M/N Tracking
    ScalerSetBit(PB8_A7_MN_SCLKG_TRK_CTRL, ~_BIT7, 0x00);
    */

    // Disable HSync Tracking
    ScalerSetBit(PB8_A7_MN_SCLKG_TRK_CTRL, ~_BIT6, 0x00);

    // Set VCOMD, phase Swallow Circuit Clock Select, SCLKGSTOP
    ScalerSetBit(PB8_BF_MN_SCLKG_PLL_WD, ~(0x7F), 0x16);

    // Set DPPLL Div_2 & Div_s
    ScalerSetByte(PB8_A3_MN_SCLKG_DIVS, (((ucdiv2) << 7) | ((ucdivs) << 0)));

    // Set DPPLL Div_O.
    ScalerSetBit(PB8_BD_MN_SCLKG_PLL_PWR, ~(_BIT1 | _BIT0), ucpllo);

    // Offset Value Setting
    ScalerSetByte(PB8_A6_MN_SCLKG_OFFS_L, (BYTE)lOffsetValue);
    ScalerSetByte(PB8_A5_MN_SCLKG_OFFS_M, (BYTE)(lOffsetValue >> 8));
    ScalerSetBit(PB8_A4_MN_SCLKG_OFFS_H, ~(_BIT2 | _BIT1 | _BIT0), ((BYTE)(lOffsetValue >> 16)) & (_BIT2 | _BIT1 | _BIT0));

    // Enable phase swallow
    ScalerSetBit(PB8_B8_MN_SCLKG_SDM_CTRL, ~(_BIT5 | _BIT4), 0x00);
    ScalerSetBit(PB8_B8_MN_SCLKG_SDM_CTRL, ~(_BIT5 | _BIT4), _BIT4);

    // Set DPPLL M Code
    ScalerSetBit(PB8_A0_MN_SCLKG_CTRL, ~(_BIT1 | _BIT0), (((ulpllm - 2) >> 8) & 0x03));
    ScalerSetByte(PB8_A1_MN_SCLKG_DIVM, ((ulpllm - 2) & 0xFF));

    // Set DPPLL N Code
    ScalerSetByte(PB8_A2_MN_SCLKG_DIVN, (ucplln - 2));

    // Load offset value
    ScalerSetBit(PB8_A4_MN_SCLKG_OFFS_H, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT7);

    // Double Buffer for M/N Tracking
    ScalerSetBit(PB8_A0_MN_SCLKG_CTRL, ~_BIT4, _BIT4);

    // DPLL VCORSTB Set to Normal
    ScalerSetBit(PB8_C0_MN_SCLKG_PLL_INSEL, ~_BIT0, _DPLL_VCORSTB_NORMAL_VALUE);

    // DPLL Power On
    ScalerSetBit(PB8_BD_MN_SCLKG_PLL_PWR, ~_BIT7, 0x00);

    ScalerTimerDelayXms(2);


    ////////////////////////////////
    // DPPLL VCO Band Calibration //
    ////////////////////////////////

    // Reg DPLL_CMPEN
    ScalerSetBit(PB8_BD_MN_SCLKG_PLL_PWR, ~_BIT2, _BIT2);

    ScalerTimerDelayXms(2);

    // Reg DPLL_CALLCH
    ScalerSetBit(PB8_BD_MN_SCLKG_PLL_PWR, ~_BIT3, _BIT3);

    ScalerTimerDelayXms(2);

    // Reg DPLL_CALSW
    ScalerSetBit(PB8_BD_MN_SCLKG_PLL_PWR, ~_BIT4, _BIT4);

    // VCO Band : 01 ---> KVCO = 1340
    // VCO Band : 10 ---> KVCO = 1880
    // VCO Band : 11 ---> KVCO = 2340
    // R : 13
    // Icp = 6.28 * 700 * M / KVCO / R
    // Icp   = 2.5u + D0[0] * 2.5u + D0[1] * 5u + D0[2] * 10u (A)
    // Icp = 2.5uA, 5uA, 7.5uA, 10uA......
    if(ScalerGetBit(PB8_C0_MN_SCLKG_PLL_INSEL, (_BIT5 | _BIT4)) == _BIT5)
    {
        pData[5] = 4396 * ulpllm / 1880 / 13;
    }
    else if(ScalerGetBit(PB8_C0_MN_SCLKG_PLL_INSEL, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
    {
        pData[5] = 4396 * ulpllm / 2340 / 13;
    }
    else
    {
        // For ICP default Setting
        pData[5] = 4396 * ulpllm / 1340 / 13;
    }

    pData[5] = ((20 * pData[5]) + 25) / 50;
    pData[5] -= (pData[5] == 0) ? 0 : 1;

    // Set PLL Charge Pump Current
    ScalerSetByte(PB8_BE_MN_SCLKG_PLL_CHP, (0x78 | (pData[5] & 0x07)));

    /*
    ////////////////////////////////
    // DPPLL M/N Tracking Setting //
    ////////////////////////////////

    // Don't Use M/N Tracking for Nvid > 0x40000 or Nvid < 0xFF

    //////////////////// Enable M/N auto tracking /////////////////////////
    // I = (2^22)*( (Tdds / Tmn) * (1 / n), n = 8
    // 1. Fdds = 1/4 * Fvco = (ulLinkClkValue / 8) * (ulpllm / ucplln) / 4 --> Tdds = (32 / ulLinkClkValue) * (plln / ulpllm)
    // 2. Tmn = Nvid * (1 / ulLinkClkValue)
    // from1,2 we can get : I = (2^27) * (ucplln / ulpllm) / Nvid / n = (2^24) * (ucplln / ulpllm) / Nvid

    ulIcodeValue = (16777216 / g_ulDpNvidValue) * ucplln / ulpllm;  //I = (2^24) * (ucplln / ulpllm) / Nvid

    ScalerSetBit(PB8_A8_MN_SCLKG_TRK_MN_I_H, ~(_BIT2 | _BIT1 | _BIT0), ((BYTE)(ulIcodeValue >> 16) & 0x03));
    ScalerSetByte(PB8_A9_MN_SCLKG_TRK_MN_I_M, (BYTE)(ulIcodeValue >> 8));
    ScalerSetByte(PB8_AA_MN_SCLKG_TRK_MN_I_L, (BYTE)ulIcodeValue);

    // Set P Code
    ScalerSetBit(PB8_AB_MN_SCLKG_TRK_MN_P_H, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
    ScalerSetByte(PB8_AC_MN_SCLKG_TRK_MN_P_M, 0xFF);
    ScalerSetByte(PB8_AD_MN_SCLKG_TRK_MN_P_L, 0xFF);
    */

    ////////////////////////////////////////
    // DPPLL HS Tracking Tracking Setting //
    ////////////////////////////////////////

    // Disable Tracking New Mode
    ScalerSetBit(PB8_B8_MN_SCLKG_SDM_CTRL, ~(_BIT2 | _BIT1), _BIT1);

    // Set Initial I/P Code
    ScalerSetByte(PB8_B1_MN_SCLKG_TRK_VS_I_M, 0x00);
    ScalerSetByte(PB8_B2_MN_SCLKG_TRK_VS_I_L, 0x04);
    ScalerSetByte(PB8_B3_MN_SCLKG_TRK_VS_P_H, 0x07);
    ScalerSetByte(PB8_B4_MN_SCLKG_TRK_VS_P_M, 0xFF);
    ScalerSetByte(PB8_B5_MN_SCLKG_TRK_VS_P_L, 0xFF);

    // Get How Many Lines per SSC Period
    pData[0] = ulStreamClkValue / usDpHtotal / 33000;

    if(pData[0] > 15)
    {
        pData[0] = 15;
    }

    // Set Tracking Freq 8 Line for 33K SSC at 4K2K60Hz
    ScalerSetBit(PB8_A8_MN_SCLKG_TRK_MN_I_H, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (pData[0] << 4));

    // Set Tracking Lock PE
    ScalerSetByte(PB8_B7_MN_SCLKG_TRK_VS_NLOCK, 0x7F);

    // Enable H Sync Tracking
    ScalerSetByte(PB8_A7_MN_SCLKG_TRK_CTRL, 0x58);

    // Double Buffer for H Sync Tracking
    ScalerSetBit(PB8_A0_MN_SCLKG_CTRL, ~_BIT4, _BIT4);

    // Get Frame Period
    pData[15] = 1000 / (ulStreamClkValue / usDpHtotal / usDpVtotal) + 1;

    pData[0] = 0;
    // Waiting for Stream Clk Stable
    do
    {
        // Clear PE Flag
        ScalerSetBit(PB8_B7_MN_SCLKG_TRK_VS_NLOCK, ~_BIT7, _BIT7);
        ScalerTimerDelayXms(pData[15]);

        pData[0]++;
    }
    while((ScalerGetBit(PB8_B7_MN_SCLKG_TRK_VS_NLOCK, _BIT7) == _BIT7) && (pData[0] < 10));

    // Set Final I/P Code
    ScalerSetByte(PB8_B1_MN_SCLKG_TRK_VS_I_M, 0x00);
    ScalerSetByte(PB8_B2_MN_SCLKG_TRK_VS_I_L, 0x02);

    // Start Generate Display Format
    ScalerSetBit(PB8_30_DPF_CTRL_0, ~_BIT7, _BIT7);

    // Polling Vertical BS
    ScalerTimerPollingFlagProc(50, PB9_01_DP_VBID, _BIT0, _TRUE);

    // Don't Enable HS Tracking New Mode for DE Only Mode
    if(ScalerGetBit(PB8_30_DPF_CTRL_0, (_BIT5 | _BIT4)) != _BIT4)
    {
        // Need to be Moved to FIFO Ready
        // Only Enable Tracking at Active Region when PE is Small
        PDATA_WORD(0) = ulVBs2BsCount / usDpVtotal / 2;

        ScalerSetBit(PB8_C2_HS_TRACKING_NEW_MODE1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[0] & 0x0F));
        ScalerSetByte(PB8_C3_HS_TRACKING_NEW_MODE2, pData[1]);

#if(_HW_HS_TRACKING_GEN_TYPE == _HS_TRACKING_GEN_2)
        ScalerDpRx1HSActiveTrackingMode(_DP_HS_TRACKING_FW_MODE);
#endif

        // Enable Tracking New Mode
        ScalerSetBit(PB8_B8_MN_SCLKG_SDM_CTRL, ~(_BIT2 | _BIT1), _BIT2);
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Adjust Vsync Delay
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1AdjustVsyncDelay(void)
{
    DWORD ulBStoVSDelayDeltaOverflow = 0;
    DWORD ulBStoVSDelayDeltaUnderflow = 0;

    if(ScalerGetBit(PB8_21_PG_CTRL_1, (_BIT1 | _BIT0)) == 0x00)// Fifo Ok
    {
        return;
    }
    else if(ScalerGetBit(PB8_21_PG_CTRL_1, _BIT0) == _BIT0) // Fifo Overflow
    {
        // Get Htotal
        ScalerRead(PB9_08_MSA_HTT_0, 2, &pData[0], _AUTOINC);

        // ((Link Clk * 256)/ Stream CLK) * Htotal / 256 --> 1 Line
        ulBStoVSDelayDeltaOverflow = (((DWORD)ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) * 270UL) * 256) / ((DWORD)GET_D1_INPUT_PIXEL_CLK()) * ((DWORD)PDATA_WORD(0)) / 256;

        DebugMessageRx1("7. Fifo Overflow --> nVidia Case", ulBStoVSDelayDeltaOverflow);
    }
    else if(ScalerGetBit(PB8_21_PG_CTRL_1, _BIT1) == _BIT1) // Fifo Underflow
    {
        // Get Hactive
        ScalerRead(PB9_0C_MSA_HWD_0, 2, &pData[0], _AUTOINC);

        if(PDATA_WORD(0) != 1366)
        {
            return;
        }

        PDATA_WORD(0) = PDATA_WORD(0) - 2;

        // Set Hactive
        ScalerSetByte(PB8_45_MN_DPF_HWD_M, pData[0]);
        ScalerSetByte(PB8_46_MN_DPF_HWD_L, pData[1]);

        // ((Link Clk * 2)/ Stream CLK) --> 2 pixels
        ulBStoVSDelayDeltaUnderflow = (((DWORD)ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) * 270) * 2) / ((DWORD)GET_D1_INPUT_PIXEL_CLK());

        DebugMessageRx1("7. Fifo Underflow --> QD882 Case", ulBStoVSDelayDeltaUnderflow);
    }

    // For Initial Value Before Use PDATA_DWORD(0)
    pData[0] = 0;

    // Get BStoVSDelay Even
    ScalerRead(PB8_32_EVBLK2VS_H, 3, &pData[1], _AUTOINC);

    // For Initial Value Before Use PDATA_DWORD(1)
    pData[4] = 0;

    // Get BStoVSDelay Odd
    ScalerRead(PB8_35_OVBLK2VS_H, 3, &pData[5], _AUTOINC);

    // BStoVSDelay = BStoVSDelay + (Nvid * 256 / Mvid) * ((DWORD)Htotal) / 256;
    PDATA_DWORD(0) = PDATA_DWORD(0) - ((ulBStoVSDelayDeltaOverflow + ulBStoVSDelayDeltaUnderflow) / 2);

    // BStoVSDelay = BStoVSDelay + (Nvid * 256 / Mvid) * ((DWORD)Htotal) / 256;
    PDATA_DWORD(1) = PDATA_DWORD(1) - ((ulBStoVSDelayDeltaOverflow + ulBStoVSDelayDeltaUnderflow) / 2);

    // Set Even Field BS to VS Delay
    ScalerSetByte(PB8_32_EVBLK2VS_H, pData[1]);
    ScalerSetByte(PB8_33_EVBLK2VS_M, pData[2]);
    ScalerSetByte(PB8_34_EVBLK2VS_L, pData[3]);

    // Set Odd Field BS to VS Delay
    ScalerSetByte(PB8_35_OVBLK2VS_H, pData[5]);
    ScalerSetByte(PB8_36_OVBLK2VS_M, pData[6]);
    ScalerSetByte(PB8_37_OVBLK2VS_L, pData[7]);

    // Enable Double Buffer
    ScalerSetBit(PB8_30_DPF_CTRL_0, ~_BIT6, _BIT6);

    // Reset Display Format Gen
    ScalerSetBit(PB8_30_DPF_CTRL_0, ~_BIT7, 0x00);
    ScalerSetBit(PB8_30_DPF_CTRL_0, ~_BIT7, _BIT7);

    ScalerTimerDelayXms(30);
}

//--------------------------------------------------
// Description  : DP Sink Status Setting
// Input Value  : Receive Port, Sync Status
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SinkStatusSet(EnumDpSinkReceivePort enumReceiverPort, EnumDpSinkStatus enumInSync)
{
    if(enumInSync == _DP_SINK_IN_SYNC)
    {
        if(enumReceiverPort == _DP_SINK_REVEICE_PORT0)
        {
            // Set Receive Port 0 in Sync
            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x05, (ScalerDpRx1GetDpcdInfo(0x00, 0x02, 0x05) | _BIT0));
        }
        else if(enumReceiverPort == _DP_SINK_REVEICE_PORT1)
        {
            // Set Receive Port 1 in Sync
            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x05, (ScalerDpRx1GetDpcdInfo(0x00, 0x02, 0x05) | _BIT1));
        }
    }
    else
    {
        if(enumReceiverPort == _DP_SINK_REVEICE_PORT0)
        {
            // Set Receive Port 0 Out of Sync
            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x05, (ScalerDpRx1GetDpcdInfo(0x00, 0x02, 0x05) & ~_BIT0));
        }
        else if(enumReceiverPort == _DP_SINK_REVEICE_PORT1)
        {
            // Set Receive Port 1 Out of Sync
            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x05, (ScalerDpRx1GetDpcdInfo(0x00, 0x02, 0x05) & ~_BIT1));
        }
    }
}

//--------------------------------------------------
// Description  : DP Sink Status Setting in EXINT
// Input Value  : Receive Port, Sync Status
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SinkStatusSet_EXINT0(EnumDpSinkReceivePort enumReceiverPort, EnumDpSinkStatus enumInSync) using 1
{
    if(enumInSync == _DP_SINK_IN_SYNC)
    {
        if(enumReceiverPort == _DP_SINK_REVEICE_PORT0)
        {
            // Set Receive Port 0 in Sync
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x05, (ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x05) | _BIT0));
        }
        else if(enumReceiverPort == _DP_SINK_REVEICE_PORT1)
        {
            // Set Receive Port 1 in Sync
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x05, (ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x05) | _BIT1));
        }
    }
    else
    {
        if(enumReceiverPort == _DP_SINK_REVEICE_PORT0)
        {
            // Set Receive Port 0 Out of Sync
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x05, (ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x05) & ~_BIT0));
        }
        else if(enumReceiverPort == _DP_SINK_REVEICE_PORT1)
        {
            // Set Receive Port 1 Out of Sync
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x05, (ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x05) & ~_BIT1));
        }
    }
}

//--------------------------------------------------
// Description  : DP CRC Calculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1CrcCalculate(void)
{
    if(GET_DP_RX1_CRC_CALCULATE() == _TRUE)
    {
        DebugMessageRx1("7. DP CRC Test Start", 0);

        // Start CRC Calculation
        ScalerSetBit(PB8_70_DP_CRC_CTRL, ~_BIT7, _BIT7);

        if(ScalerTimerPollingFlagProc(_DP_MEASURE_POLLING_TIMEOUT, PB8_70_DP_CRC_CTRL, _BIT6, _TRUE) == _TRUE)
        {
            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x40, ScalerGetByte(PB8_72_DP_CRC_R_L));
            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x41, ScalerGetByte(PB8_71_DP_CRC_R_M));
            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x42, ScalerGetByte(PB8_74_DP_CRC_G_L));
            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x43, ScalerGetByte(PB8_73_DP_CRC_G_M));
            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x44, ScalerGetByte(PB8_76_DP_CRC_B_L));
            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x45, ScalerGetByte(PB8_75_DP_CRC_B_M));

            CLR_DP_RX1_CRC_CALCULATE();

            // Update _TEST_CRC_COUNT
            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x46, 0x21);
        }

        // Stop CRC Calculation
        ScalerSetBit(PB8_70_DP_CRC_CTRL, ~_BIT7, 0x00);
    }
}

#if(_HW_HS_TRACKING_GEN_TYPE == _HS_TRACKING_GEN_2)
//--------------------------------------------------
// Description  : DP Hs Tracking Active Region Setting
// Input Value  : Hs Tracking Type
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HSActiveTrackingMode(EnumDpHSTrackingType enumHSTrackingType)
{
    if(enumHSTrackingType == _DP_HS_TRACKING_FW_MODE)
    {
        // HS Tracking Region By FW Setting
        ScalerSetBit(PB8_B9_MN_SCLKG_SDM_TEST, ~_BIT7, _BIT7);

        // BE Start Num = 2 line
        ScalerSetBit(PB8_C7_VBID_MAN_MADE, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT5);

        // BE End Num = 2 line
        ScalerSetBit(PB8_C7_VBID_MAN_MADE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
    }
    else
    {
        // HS Tracking Region By FW Setting
        ScalerSetBit(PB8_B9_MN_SCLKG_SDM_TEST, ~_BIT7, 0x00);
    }
}
#endif

//--------------------------------------------------
// Description  : Clear CPIRQ Flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1CheckHdcpCpirqStatus(void)
{
    if((ScalerGetByte(PB0_1E_HDCP_INTGT_VRF_ANS_MSB) == 0x53) && (ScalerGetByte(PB0_1F_HDCP_INTGT_VRF_ANS_LSB) == 0x1F))
    {
        if(((ScalerDpRx1GetDpcdInfo(0x00, 0x02, 0x01) & _BIT2) == _BIT2) && (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x29) == 0x00))
        {
            // Clear Link Status CPIRQ Flag
            ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x01, (ScalerDpRx1GetDpcdInfo(0x00, 0x02, 0x01) & ~_BIT2));
        }
    }
}

//--------------------------------------------------
// Description  : Check DP Link Integrity
// Input Value  : None
// Output Value : FALSE => DP Link Integrity Fail
//--------------------------------------------------
bit ScalerDpRx1HdcpCheck(void)
{
    // Check for HDCP Block work in 1.4
    if(ScalerGetBit(PB0_1A_HDCP_IRQ, _BIT1) == 0x00)
    {
        if(ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x0B) == 0x00)
        {
            return _TRUE;
        }
    }
#if(_DP_HDCP_2_2_SUPPORT == _ON)
    else
    {
        if(GET_DP_RX1_HDCP2_AUTHENTICATION_DONE() == _FALSE)
        {
            return _TRUE;
        }
    }
#endif

    if(((ScalerGetByte(PB0_1E_HDCP_INTGT_VRF_ANS_MSB) == 0x53) || (ScalerGetByte(PB0_1E_HDCP_INTGT_VRF_ANS_MSB) == 0x00)) &&
       ((ScalerGetByte(PB0_1F_HDCP_INTGT_VRF_ANS_LSB) == 0x1F) || (ScalerGetByte(PB0_1F_HDCP_INTGT_VRF_ANS_LSB) == 0x00)))
    {
        return _TRUE;
    }

    // Check for HDCP Block work in 1.4
    if((ScalerGetBit(PB0_1A_HDCP_IRQ, _BIT1) == 0x00) && ((ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x11) & _BIT2) == 0x00))
    {
        return _FALSE;
    }

    if((ScalerGetBit(PB0_1A_HDCP_IRQ, _BIT1) == 0x00) && (ScalerDpRx1HdcpMeasureCheck() == _TRUE))
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check DP Hdcp ReAuth Process
// Input Value  : None
// Output Value : TRUE or FALSE
//--------------------------------------------------
bit ScalerDpRx1HdcpReAuthStatusCheck(void)
{
    if((ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x07) != 0x00) || (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x08) != 0x00) ||
       (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x09) != 0x00) || (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x0A) != 0x00) ||
       (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x0B) != 0x00))
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : DP HDCP Measure Check
// Input Value  : None
// Output Value : FALSE => Measure Check Fail
//--------------------------------------------------
bit ScalerDpRx1HdcpMeasureCheck(void)
{
    DWORD ulLinkClk = 0;
    WORD usHTotalCount = 0;

    // Pop up Main Stream Attributes
    ScalerSetBit(PB9_00_MN_STRM_ATTR_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT3));

    // Get Vtotal
    ScalerRead(PB9_10_MSA_VTTE_0, 2, &pData[10], _AUTOINC);

    if(PDATA_WORD(5) == 0)
    {
        return _FALSE;
    }

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_ENABLED() == _TRUE)
    {
        return _FALSE;
    }
#endif

    // [5] ln_ck_sel = 1'b1 -> CDR Clock
    // [4:0] DP_XTAL_CYCLE = 5'b00100 -> XTAL Counter Cycles = 2000
    ScalerSetBit(PB0_50_DP_SIG_DET_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT2));

    // [1:0] freqdet_lane_sel = 2'b00 -> Lane0
    ScalerSetBit(PB0_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), _D1_DP_LANE0);

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
    ScalerSetBit(PB0_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
    ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);
    ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

    // Waiting for Measure Done
    ScalerTimerDelayXms(2);

    if(ScalerGetBit(PB0_50_DP_SIG_DET_0, _BIT6) == _BIT6)
    {
        PDATA_WORD(0) = ((((WORD)ScalerGetByte(PB0_53_DP_SIG_DET_3)) << 8) | ScalerGetByte(PB0_54_DP_SIG_DET_4));
    }
    else
    {
        if(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR2)
        {
            PDATA_WORD(0) = 0x4E20;
        }
        else if(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == _DP_LINK_HBR)
        {
            PDATA_WORD(0) = 0x2710;
        }
        else // Both Default && _DP_LINK_RBR Case
        {
            PDATA_WORD(0) = 0x1770;
        }
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);

    PDATA_DWORD(0) = (((DWORD)PDATA_WORD(0)) * _GDI_CLK_KHZ);

    // Link Clk in KHz
    ulLinkClk = (PDATA_DWORD(0) / 1000);

    DebugMessageRx1("Current Link Clk", ulLinkClk);

    // Start to Measure Vertical BS to BS Counter by GDI Clock
    ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~_BIT7, 0x00);
    ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~_BIT7, _BIT7);

    if(ScalerTimerPollingFlagProc(_DP_MEASURE_POLLING_TIMEOUT, PB8_58_MN_MEAS_CTRL, _BIT6, _TRUE) == _FALSE)
    {
        return _FALSE;
    }

    // Pop up The result
    ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~_BIT5, _BIT5);

    // Get Measure Result
    ScalerRead(PB8_58_MN_MEAS_CTRL, 3, &pData[1], _AUTOINC);

    // Get Measure Htotal Counts
    ScalerRead(PB8_5B_MN_MEAS_HLN_M, 2, &pData[6], _AUTOINC);

    // Disable Measure Block
    ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~_BIT7, 0x00);

    // Convert HTotal Count from 1/2 Link Clk to GDI Clk
    usHTotalCount = ((DWORD)PDATA_WORD(3) * _GDI_CLK_KHZ * 2 + (ulLinkClk >> 1)) / ulLinkClk;

    PDATA_DWORD(0) = (PDATA_DWORD(0) & 0x001FFFFF);
    PDATA_DWORD(1) = ((DWORD)usHTotalCount & 0x0000FFFF);

    PDATA_WORD(2) = PDATA_DWORD(0) / PDATA_DWORD(1);

    // 2% Tolerance
    if((ABSDWORD(PDATA_WORD(2), PDATA_WORD(5))) > (PDATA_WORD(5) * 2 / 100))
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Content Protection Interrupt Request
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1CpIRQ(EnumDpRxBStatusType enumBStatusType)
{
    switch(enumBStatusType)
    {
        case _DP_HDCP_BSTATUS_LINK_INTEGRITY_FAIL:
        case _DP_HDCP_BSTATUS_REAUTH_REQ:

            if(ScalerGetBit(PB0_1A_HDCP_IRQ, _BIT1) == 0x00)
            {
#if(_DP_MST_SUPPORT == _ON)
                if((ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x11) & _BIT0) == 0x00)
                {
                    // Reset HDCP Block
                    ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT0, _BIT0);
                    ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT0, 0x00);
                }

                if((ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x11) & _BIT1) == _BIT1)
                {
                    ScalerDpRx1SetDpcdValue(0x00, 0x20, 0x05, (ScalerDpRx1GetDpcdInfo(0x00, 0x20, 0x05) | _BIT2));
                }
#else
                // Reset HDCP Block
                ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT0, _BIT0);
                ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT0, 0x00);
#endif

                SET_DP_RX1_AUX_MANUAL_MODE();

                // Clear Aksv
                ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x07, 0x00);
                ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x08, 0x00);
                ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x09, 0x00);
                ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x0A, 0x00);
                ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x0B, 0x00);

                SET_DP_RX1_AUX_AUTO_MODE();

                // Set B Status
                ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x29, (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x29) | enumBStatusType));
            }
#if(_DP_HDCP_2_2_SUPPORT == _ON)
            else
            {
                // Disable HDCP 2.2 Module
                ScalerSetBit(PB0_1A_HDCP_IRQ, ~_BIT1, 0x00);

                // Disable HDCP2.2 Auth. Done
                ScalerSetBit(PB0_20_HDCP_DEBUG, ~_BIT4, 0x00);

                // Reset HDCP Block
                ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT0, _BIT0);
                ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT0, 0x00);

                ScalerDpRx1SetDpcdValue(0x06, 0x94, 0x93, (ScalerDpRx1GetDpcdInfo(0x06, 0x94, 0x93) | _BIT4));

                // Clear Authentication Done Flag
                CLR_DP_RX1_HDCP2_AUTHENTICATION_DONE();
            }
#endif
            break;

        case _DP_HDCP_BSTATUS_V_READY:
        case _DP_HDCP_BSTATUS_R0_AVAILABLE:

            // Set B Status
            ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x29, (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x29) | enumBStatusType));

            break;

#if(_DP_HDCP_2_2_SUPPORT == _ON)
        case _DP_HDCP2_H_PRIME_AVAILABLE:
        case _DP_HDCP2_PARING_AVAILABLE:

            ScalerDpRx1SetDpcdValue(0x06, 0x94, 0x93, (ScalerDpRx1GetDpcdInfo(0x06, 0x94, 0x93) | (enumBStatusType >> 3)));

            break;
#endif

            break;

        default:

            break;
    }

    // Link Status CPIRQ Flag
    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x01, (ScalerDpRx1GetDpcdInfo(0x00, 0x02, 0x01) | _BIT2));

    ScalerDpRx1HotPlugDuration(1);
}

//--------------------------------------------------
// Description  : Check whether HDCP is enabled
// Input Value  : None
// Output Value : TRUE => HDCP Enabled
//--------------------------------------------------
bit ScalerDpRx1HdcpEnebled(void)
{
    if(ScalerGetBit(PB0_1A_HDCP_IRQ, _BIT1) == 0x00)
    {
        if(ScalerGetBit(PB0_20_HDCP_DEBUG, (_BIT7 | _BIT6 | _BIT5)) == (_BIT7 | _BIT6 | _BIT5))
        {
            return _TRUE;
        }
    }
#if(_DP_HDCP_2_2_SUPPORT == _ON)
    else
    {
        if(ScalerGetBit(PB0_20_HDCP_DEBUG, _BIT4) == _BIT4)
        {
            return _TRUE;
        }
    }
#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
// Output Value : DPCD Information
//--------------------------------------------------
BYTE ScalerDpRx1GetDpcdInfo(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL)
{
    // Release Aux
    ScalerSetBit(PBA_C0_DPCD_CTRL, ~_BIT7, 0x00);

    ScalerSetByte(PBA_C1_DPCD_ADDR_PORT_H, ucDpcdAccessPortH);
    ScalerSetByte(PBA_C2_DPCD_ADDR_PORT_M, ucDpcdAccessPortM);
    ScalerSetByte(PBA_C3_DPCD_ADDR_PORT_L, ucDpcdAccessPortL);

    return ScalerGetByte(PBA_C4_DPCD_DATA_PORT);
}

//--------------------------------------------------
// Description  : Get DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
// Output Value : DPCD Information
//--------------------------------------------------
BYTE ScalerDpRx1GetDpcdBitInfo(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit)
{
    // Release Aux
    ScalerSetBit(PBA_C0_DPCD_CTRL, ~_BIT7, 0x00);

    ScalerSetByte(PBA_C1_DPCD_ADDR_PORT_H, ucDpcdAccessPortH);
    ScalerSetByte(PBA_C2_DPCD_ADDR_PORT_M, ucDpcdAccessPortM);
    ScalerSetByte(PBA_C3_DPCD_ADDR_PORT_L, ucDpcdAccessPortL);

    return ScalerGetBit(PBA_C4_DPCD_DATA_PORT, ucDpcdBit);
}

//--------------------------------------------------
// Description  : Get DPCD Table Information in INT0
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
// Output Value : DPCD Information
//--------------------------------------------------
BYTE ScalerDpRx1GetDpcdInfo_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL) using 1
{
    ScalerSetByte_EXINT(PBA_C1_DPCD_ADDR_PORT_H, ucDpcdAccessPortH);
    ScalerSetByte_EXINT(PBA_C2_DPCD_ADDR_PORT_M, ucDpcdAccessPortM);
    ScalerSetByte_EXINT(PBA_C3_DPCD_ADDR_PORT_L, ucDpcdAccessPortL);

    return ScalerGetByte_EXINT(PBA_C4_DPCD_DATA_PORT);
}

//--------------------------------------------------
// Description  : Get DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
// Output Value : DPCD Information
//--------------------------------------------------
BYTE ScalerDpRx1GetDpcdBitInfo_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit) using 1
{
    ScalerSetByte_EXINT(PBA_C1_DPCD_ADDR_PORT_H, ucDpcdAccessPortH);
    ScalerSetByte_EXINT(PBA_C2_DPCD_ADDR_PORT_M, ucDpcdAccessPortM);
    ScalerSetByte_EXINT(PBA_C3_DPCD_ADDR_PORT_L, ucDpcdAccessPortL);

    return ScalerGetBit_EXINT(PBA_C4_DPCD_DATA_PORT, ucDpcdBit);
}

//--------------------------------------------------
// Description  : Set DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetDpcdValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue)
{
    // Release Aux
    ScalerSetBit(PBA_C0_DPCD_CTRL, ~_BIT7, 0x00);

    ScalerSetByte(PBA_C1_DPCD_ADDR_PORT_H, ucDpcdAccessPortH);
    ScalerSetByte(PBA_C2_DPCD_ADDR_PORT_M, ucDpcdAccessPortM);
    ScalerSetByte(PBA_C3_DPCD_ADDR_PORT_L, ucDpcdAccessPortL);
    ScalerSetByte(PBA_C4_DPCD_DATA_PORT, ucDpcdValue);
}

//--------------------------------------------------
// Description  : Set DPCD Table Information
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetDpcdBitValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucNotDpcdBit, BYTE ucDpcdBit)
{
    // Release Aux
    ScalerSetBit(PBA_C0_DPCD_CTRL, ~_BIT7, 0x00);

    ScalerSetByte(PBA_C1_DPCD_ADDR_PORT_H, ucDpcdAccessPortH);
    ScalerSetByte(PBA_C2_DPCD_ADDR_PORT_M, ucDpcdAccessPortM);
    ScalerSetByte(PBA_C3_DPCD_ADDR_PORT_L, ucDpcdAccessPortL);
    ScalerSetBit(PBA_C4_DPCD_DATA_PORT, ~(~ucNotDpcdBit), ucDpcdBit);
}

//--------------------------------------------------
// Description  : Set DPCD Table Information in INT0
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetDpcdValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue) using 1
{
    ScalerSetByte_EXINT(PBA_C1_DPCD_ADDR_PORT_H, ucDpcdAccessPortH);
    ScalerSetByte_EXINT(PBA_C2_DPCD_ADDR_PORT_M, ucDpcdAccessPortM);
    ScalerSetByte_EXINT(PBA_C3_DPCD_ADDR_PORT_L, ucDpcdAccessPortL);
    ScalerSetByte_EXINT(PBA_C4_DPCD_DATA_PORT, ucDpcdValue);
}

//--------------------------------------------------
// Description  : Set DPCD Table Information in INT0
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetDpcdBitValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucNotDpcdBit, BYTE ucDpcdBit) using 1
{
    ScalerSetByte_EXINT(PBA_C1_DPCD_ADDR_PORT_H, ucDpcdAccessPortH);
    ScalerSetByte_EXINT(PBA_C2_DPCD_ADDR_PORT_M, ucDpcdAccessPortM);
    ScalerSetByte_EXINT(PBA_C3_DPCD_ADDR_PORT_L, ucDpcdAccessPortL);
    ScalerSetBit_EXINT(PBA_C4_DPCD_DATA_PORT, ~(~ucNotDpcdBit), ucDpcdBit);
}

#if(_WD_TIMER_INT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get DPCD Table Information in WDINT
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
// Output Value : DPCD Information
//--------------------------------------------------
BYTE ScalerDpRx1GetDpcdInfo_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL) using 3
{
    ScalerSetByte_EXINT(PBA_C1_DPCD_ADDR_PORT_H, ucDpcdAccessPortH);
    ScalerSetByte_EXINT(PBA_C2_DPCD_ADDR_PORT_M, ucDpcdAccessPortM);
    ScalerSetByte_EXINT(PBA_C3_DPCD_ADDR_PORT_L, ucDpcdAccessPortL);

    return ScalerGetByte_EXINT(PBA_C4_DPCD_DATA_PORT);
}

//--------------------------------------------------
// Description  : Set DPCD Table Information in INT0
// Input Value  : ucDpcdAccessPortH --> High Byte of DPCD Address
//                ucDpcdAccessPortM --> Middle Byte of DPCD Address
//                ucDpcdAccessPortL --> Low Bye of DPCD Adress
//                ucDpcdValue --> DPCD Value
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetDpcdValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue) using 3
{
    ScalerSetByte_EXINT(PBA_C1_DPCD_ADDR_PORT_H, ucDpcdAccessPortH);
    ScalerSetByte_EXINT(PBA_C2_DPCD_ADDR_PORT_M, ucDpcdAccessPortM);
    ScalerSetByte_EXINT(PBA_C3_DPCD_ADDR_PORT_L, ucDpcdAccessPortL);
    ScalerSetByte_EXINT(PBA_C4_DPCD_DATA_PORT, ucDpcdValue);
}
#endif

#if(_DP_ASSR_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP ASSR Mode On/ Off
// Input Value  : _ON/ _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1ASSRModeSetting(void)
{
    if((ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x0A) & _BIT0) == _BIT0)
    {
        // Scramble seed equal to 0xFFFE
        ScalerSetBit(PB0_07_SCRAMBLE_CTRL, ~_BIT4, _BIT4);
    }
    else
    {
        // Scramble seed equal to 0xFFFF
        ScalerSetBit(PB0_07_SCRAMBLE_CTRL, ~_BIT4, 0x00);
    }
}
#endif // End of #if(_DP_ASSR_MODE_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Signal PreDetection for DP(Power Normal)
// Input Value  : None
// Output Value : True : DP Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerDpRx1NormalPreDetect(void)
{
    // For Dp PHY CTS Test
    if(GET_DP_RX1_PHY_CTS_FLG() == _TRUE)
    {
        ScalerDpRx1PhyCTS();

        return _FALSE;
    }

#if(_DP_MST_SUPPORT == _ON)

    if(GET_DP_RX1_AUX_CH_POWER_ON_WAKE_UP() == _TRUE)
    {
        CLR_DP_RX1_AUX_CH_POWER_ON_WAKE_UP();
    }

#endif

#if(_DP_ASSR_MODE_SUPPORT == _ON)

    // ASSR Mode Setting
    ScalerDpRx1ASSRModeSetting();

#endif

    // ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_RX1_DP_LINK_STATUS_FAIL);

    switch(GET_DP_RX1_LINK_TRAINING_STATUS())
    {
        case _DP_NORMAL_LINK_TRAINING_PASS:
        case _DP_LINK_STATUS_FAIL:

            CLR_DP_RX1_VALID_VIDEO_CHECK();

#if(_DP_MST_SUPPORT == _ON)
            ScalerDpRx1MstInfoBackup(_DP_MST_BACKUP_INFO_RESET);
#endif
            if((ScalerDpRx1CDRCheck(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _TRUE) &&
               ((ScalerDpRx1DFECheck() == _TRUE) || (ScalerDpRx1SignalCheck(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _TRUE)) &&
               (ScalerDpRx1MarginLinkCheck() == _TRUE) &&
               (ScalerDpRx1AlignCheck() == _TRUE) &&
               (ScalerDpRx1DecodeCheck() == _TRUE))
            {
                /*
                DebugMessageRx1("9. Lane0 LE Diff", (g_pucDpRx1LEMaxTemp[0] - g_pucDpRx1LEMinTemp[0]));
                DebugMessageRx1("9. Lane1 LE Diff", (g_pucDpRx1LEMaxTemp[1] - g_pucDpRx1LEMinTemp[1]));
                DebugMessageRx1("9. Lane2 LE Diff", (g_pucDpRx1LEMaxTemp[2] - g_pucDpRx1LEMinTemp[2]));
                DebugMessageRx1("9. Lane3 LE Diff", (g_pucDpRx1LEMaxTemp[3] - g_pucDpRx1LEMinTemp[3]));
                DebugMessageRx1("9. Lane0 LE Min", g_pucDpRx1LEMinTemp[0]);
                DebugMessageRx1("9. Lane1 LE Min", g_pucDpRx1LEMinTemp[1]);
                DebugMessageRx1("9. Lane2 LE Min", g_pucDpRx1LEMinTemp[2]);
                DebugMessageRx1("9. Lane3 LE Min", g_pucDpRx1LEMinTemp[3]);
                DebugMessageRx1("9. Lane0 Tap0 Diff", (g_pucDpRx1Tap0MaxTemp[0] - g_pucDpRx1Tap0MinTemp[0]));
                DebugMessageRx1("9. Lane1 Tap0 Diff", (g_pucDpRx1Tap0MaxTemp[1] - g_pucDpRx1Tap0MinTemp[1]));
                DebugMessageRx1("9. Lane2 Tap0 Diff", (g_pucDpRx1Tap0MaxTemp[2] - g_pucDpRx1Tap0MinTemp[2]));
                DebugMessageRx1("9. Lane3 Tap0 Diff", (g_pucDpRx1Tap0MaxTemp[3] - g_pucDpRx1Tap0MinTemp[3]));
                DebugMessageRx1("9. Lane0 Tap0 Max", g_pucDpRx1Tap0MaxTemp[0]);
                DebugMessageRx1("9. Lane1 Tap0 Max", g_pucDpRx1Tap0MaxTemp[1]);
                DebugMessageRx1("9. Lane2 Tap0 Max", g_pucDpRx1Tap0MaxTemp[2]);
                DebugMessageRx1("9. Lane3 Tap0 Max", g_pucDpRx1Tap0MaxTemp[3]);
                DebugMessageRx1("9. FLD Band", ScalerGetByte(PB0_BF_LANE0_A_CDR_02));
                DebugMessageRx1("9. Best FLD Band", ScalerGetByte(PB0_BE_LANE0_A_CDR_01));
                DebugMessageRx1("9. Lane0 Tap0 Diff 2", (g_pucDpRx1Tap0MaxTemp2[0] - g_pucDpRx1Tap0MinTemp2[0]));
                DebugMessageRx1("9. Lane1 Tap0 Diff 2", (g_pucDpRx1Tap0MaxTemp2[1] - g_pucDpRx1Tap0MinTemp2[1]));
                DebugMessageRx1("9. Lane2 Tap0 Diff 2", (g_pucDpRx1Tap0MaxTemp2[2] - g_pucDpRx1Tap0MinTemp2[2]));
                DebugMessageRx1("9. Lane3 Tap0 Diff 2", (g_pucDpRx1Tap0MaxTemp2[3] - g_pucDpRx1Tap0MinTemp2[3]));
                DebugMessageRx1("9. Lane0 Tap0 Max 2", g_pucDpRx1Tap0MaxTemp2[0]);
                DebugMessageRx1("9. Lane1 Tap0 Max 2", g_pucDpRx1Tap0MaxTemp2[1]);
                DebugMessageRx1("9. Lane2 Tap0 Max 2", g_pucDpRx1Tap0MaxTemp2[2]);
                DebugMessageRx1("9. Lane3 Tap0 Max 2", g_pucDpRx1Tap0MaxTemp2[3]);
                DebugMessageRx1("9. TP2 Check Result", g_ucDpRx1EQCRC);
                */

                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_LINK_STATUS_IRQ);

                SET_DP_RX1_AUX_MANUAL_MODE();

                if(GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_LINK_STATUS_FAIL)
                {
                    SET_DP_RX1_LINK_TRAINING_STATUS(_DP_NORMAL_LINK_TRAINING_PASS);
                }

                SET_DP_RX1_AUX_AUTO_MODE();

                if((ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT1) ||
                   (ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)))
                {
                    return _FALSE;
                }

                return _TRUE;
            }
            else
            {
                DebugMessageRx1("7. Link Status Fail IRQ", 0);

                SET_DP_RX1_AUX_MANUAL_MODE();

                if((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_LINK_TRAINING_PASS) || (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_LINK_STATUS_FAIL))
                {
                    SET_DP_RX1_LINK_TRAINING_STATUS(_DP_LINK_STATUS_FAIL);

                    ScalerTimerActiveTimerEvent(SEC(0.05), _SCALER_TIMER_EVENT_DP_RX1_LINK_STATUS_IRQ);
                }

                SET_DP_RX1_AUX_AUTO_MODE();
            }

            break;

        case _DP_LINK_TRAINING_FAIL:

            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_LINK_STATUS_IRQ);

            ScalerDpRx1LinkStatusIRQ();

            break;

        case _DP_FAKE_LINK_TRAINING_PASS:
        case _DP_FAKE_LINK_TRAINING_PASS_VBIOS:

            CLR_DP_RX1_VALID_VIDEO_CHECK();

#if(_DP_MST_SUPPORT == _ON)
            ScalerDpRx1MstInfoBackup(_DP_MST_BACKUP_INFO_RESET);
#endif
            ScalerTimerDelayXms(30);

            DebugMessageRx1("7. DP Rebuild PHY", GET_DP_RX1_LINK_TRAINING_STATUS());

            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_LINK_STATUS_IRQ);

            SET_DP_RX1_AUX_MANUAL_MODE();

            if((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS) || (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS_VBIOS))
            {
                ScalerDpRx1RebuildPhy(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00), ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01));
            }

            SET_DP_RX1_AUX_AUTO_MODE();

            // De-Skew Circuit Reset
            ScalerSetBit(PB0_0E_DESKEW_PHY, ~(_BIT7 | _BIT6), 0x00);
            ScalerSetBit(PB0_0E_DESKEW_PHY, ~(_BIT7 | _BIT6), _BIT6);

            // Mac Reset After Link Clock Stable
            ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT1, _BIT1);
            ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);

            // Delay for Lane Alignment after Mac Reset
            ScalerTimerDelayXms(2);

            if((ScalerDpRx1CDRCheck(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _TRUE) &&
               ((ScalerDpRx1DFECheck() == _TRUE) || (ScalerDpRx1SignalCheck(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _TRUE)) &&
               (ScalerDpRx1MarginLinkCheck() == _TRUE) &&
               (ScalerDpRx1AlignCheck() == _TRUE) &&
               (ScalerDpRx1DecodeCheck() == _TRUE))
            {
                DebugMessageRx1("7. Rebuild Phy Pass", 0);

                /*
                DebugMessageRx1("9. Lane0 LE Diff", (g_pucDpRx1LEMaxTemp[0] - g_pucDpRx1LEMinTemp[0]));
                DebugMessageRx1("9. Lane1 LE Diff", (g_pucDpRx1LEMaxTemp[1] - g_pucDpRx1LEMinTemp[1]));
                DebugMessageRx1("9. Lane2 LE Diff", (g_pucDpRx1LEMaxTemp[2] - g_pucDpRx1LEMinTemp[2]));
                DebugMessageRx1("9. Lane3 LE Diff", (g_pucDpRx1LEMaxTemp[3] - g_pucDpRx1LEMinTemp[3]));
                DebugMessageRx1("9. Lane0 LE Min", g_pucDpRx1LEMinTemp[0]);
                DebugMessageRx1("9. Lane1 LE Min", g_pucDpRx1LEMinTemp[1]);
                DebugMessageRx1("9. Lane2 LE Min", g_pucDpRx1LEMinTemp[2]);
                DebugMessageRx1("9. Lane3 LE Min", g_pucDpRx1LEMinTemp[3]);
                DebugMessageRx1("9. Lane0 Tap0 Diff", (g_pucDpRx1Tap0MaxTemp[0] - g_pucDpRx1Tap0MinTemp[0]));
                DebugMessageRx1("9. Lane1 Tap0 Diff", (g_pucDpRx1Tap0MaxTemp[1] - g_pucDpRx1Tap0MinTemp[1]));
                DebugMessageRx1("9. Lane2 Tap0 Diff", (g_pucDpRx1Tap0MaxTemp[2] - g_pucDpRx1Tap0MinTemp[2]));
                DebugMessageRx1("9. Lane3 Tap0 Diff", (g_pucDpRx1Tap0MaxTemp[3] - g_pucDpRx1Tap0MinTemp[3]));
                DebugMessageRx1("9. Lane0 Tap0 Max", g_pucDpRx1Tap0MaxTemp[0]);
                DebugMessageRx1("9. Lane1 Tap0 Max", g_pucDpRx1Tap0MaxTemp[1]);
                DebugMessageRx1("9. Lane2 Tap0 Max", g_pucDpRx1Tap0MaxTemp[2]);
                DebugMessageRx1("9. Lane3 Tap0 Max", g_pucDpRx1Tap0MaxTemp[3]);
                DebugMessageRx1("9. FLD Band", ScalerGetByte(PB0_BF_LANE0_A_CDR_02));
                DebugMessageRx1("9. Best FLD Band", ScalerGetByte(PB0_BE_LANE0_A_CDR_01));
                DebugMessageRx1("9. D10.2 Counter", g_usDpRx1ClockCount);
                DebugMessageRx1("9. D10.2 Counter1", g_usDpRx1ClockCount1);
                DebugMessageRx1("9. Lane0 Tap0 Diff 2", (g_pucDpRx1Tap0MaxTemp2[0] - g_pucDpRx1Tap0MinTemp2[0]));
                DebugMessageRx1("9. Lane1 Tap0 Diff 2", (g_pucDpRx1Tap0MaxTemp2[1] - g_pucDpRx1Tap0MinTemp2[1]));
                DebugMessageRx1("9. Lane2 Tap0 Diff 2", (g_pucDpRx1Tap0MaxTemp2[2] - g_pucDpRx1Tap0MinTemp2[2]));
                DebugMessageRx1("9. Lane3 Tap0 Diff 2", (g_pucDpRx1Tap0MaxTemp2[3] - g_pucDpRx1Tap0MinTemp2[3]));
                DebugMessageRx1("9. Lane0 Tap0 Max 2", g_pucDpRx1Tap0MaxTemp2[0]);
                DebugMessageRx1("9. Lane1 Tap0 Max 2", g_pucDpRx1Tap0MaxTemp2[1]);
                DebugMessageRx1("9. Lane2 Tap0 Max 2", g_pucDpRx1Tap0MaxTemp2[2]);
                DebugMessageRx1("9. Lane3 Tap0 Max 2", g_pucDpRx1Tap0MaxTemp2[3]);
                DebugMessageRx1("9. Best FLD Band", ScalerGetByte(PB0_BE_LANE0_A_CDR_01));
                DebugMessageRx1("9. TP2 Check Result", g_ucDpRx1EQCRC);
                DebugMessageRx1("9. DP Requeset", ScalerDpRx1GetDpcdInfo(0x00, 0x02, 0x06));
                DebugMessageRx1("9. DP Requeset", ScalerDpRx1GetDpcdInfo(0x00, 0x02, 0x07));
                DebugMessageRx1("9. Lane0 Tap1 Max", ScalerGetByte(P7A_A5_L0_INIT_3));
                DebugMessageRx1("9. Lane1 Tap1 Max", ScalerGetByte(P7A_B5_L1_INIT_3));
                DebugMessageRx1("9. Lane2 Tap1 Max", ScalerGetByte(P7A_C5_L2_INIT_3));
                DebugMessageRx1("9. Lane3 Tap1 Max", ScalerGetByte(P7A_D5_L3_INIT_3));
                */

                ScalerTimerDelayXms(_DP_ONE_FRAME_TIME_MAX);

                SET_DP_RX1_AUX_MANUAL_MODE();

                if((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS) || (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS_VBIOS))
                {
                    SET_DP_RX1_LINK_TRAINING_STATUS(_DP_NORMAL_LINK_TRAINING_PASS);
                }

                SET_DP_RX1_AUX_AUTO_MODE();

                if((ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT1) ||
                   (ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)))
                {
                    return _FALSE;
                }

                return _TRUE;
            }
            else
            {
                DebugMessageRx1("7. DP Rebuild PHY Fail", 0);

                SET_DP_RX1_AUX_MANUAL_MODE();

                if(GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS_VBIOS)
                {
                    ScalerDpRx1DpcdLinkStatusReset(_DP_DPCD_LINK_STATUS_INITIAL);

#if((_DP_TX_SUPPORT == _ON) && (_D1_DP_MST_PORT_SUPPORT == _ON))
                    ScalerDpRx1HDCPBlockReset();
#endif
                }
                else if(GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS)
                {
                    SET_DP_RX1_LINK_TRAINING_STATUS(_DP_LINK_STATUS_FAIL);
                }

                SET_DP_RX1_AUX_AUTO_MODE();
            }

            break;

        case _DP_LINK_TRAINING_NONE:

            if(GET_DP_RX1_VALID_VIDEO_CHECK() == _TRUE)
            {
                ScalerDpRx1ValidSignalDetection();

                DebugMessageRx1("7. VBIOS Check !!!!!!!", GET_DP_RX1_FAKE_LINK_TRAINING());
            }

            break;

        default:

            break;
    }

    if(GET_DP_RX1_VALID_VIDEO_CHECK() == _TRUE)
    {
        CLR_DP_RX1_VALID_VIDEO_CHECK();

#if(_DP_MST_SUPPORT == _ON)
        ScalerDpRx1MstInfoBackup(_DP_MST_BACKUP_INFO_RESET);
#endif
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Port Source/Sync Scanning and Setting
// Input Value  : None
// Output Value : Source DP --> DP Sync Stable
//                Source None --> No Stable Sync
//--------------------------------------------------
BYTE ScalerDpRx1ScanInputPort(void)
{
    if(GET_DP_RX1_LINK_TRAINING_STATUS() != _DP_NORMAL_LINK_TRAINING_PASS)
    {
        return _SOURCE_NONE;
    }

    if(ScalerDpRx1HdcpCheck() == _FALSE)
    {
        DebugMessageRx1("7. DP HDCP Check Fail", 0);

        ScalerDpRx1CpIRQ(_DP_HDCP_BSTATUS_LINK_INTEGRITY_FAIL);

        if((ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x11) & _BIT0) == 0x00)
        {
            ScalerTimerReactiveTimerEvent(SEC(1), _SCALER_TIMER_EVENT_DP_RX1_HDCP_LONG_HOTPLUG_EVENT);
        }

        return _SOURCE_NONE;
    }

    if(ScalerDpRx1GetVideoStream() == _FALSE)
    {
        DebugMessageRx1("7. DP Video Stream Fail", 0);

        return _SOURCE_NONE;
    }

#if(_DP_FREESYNC_SUPPORT == _ON)
    if((ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x07) & _BIT7) == _BIT7)
    {
        SET_DP_FREESYNC_ENABLED();
    }
    else
    {
        CLR_FREESYNC_ENABLED();
    }
#endif

    if(ScalerDpRx1MSACheck() == _FALSE)
    {
        DebugMessageRx1("7. DP MSA Fail", 0);

        return _SOURCE_NONE;
    }

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if((ScalerSyncCheckUrgentEvent() == _TRUE))
    {
        return _SOURCE_NONE;
    }
#endif

    if(ScalerDpRx1GetVideoInfo() == _FALSE)
    {
        DebugMessageRx1("7. DP Get Video Info Fail", 0);

        return _SOURCE_NONE;
    }
    else
    {
        ScalerDpRx1SetColorInfo();
    }

    if(ScalerDpRx1DisplayFormatSetting() == _FALSE)
    {
        DebugMessageRx1("7. DP Display Format Fail", 0);

        return _SOURCE_NONE;
    }

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if((ScalerSyncCheckUrgentEvent() == _TRUE))
    {
        return _SOURCE_NONE;
    }
#endif

    if(ScalerDpRx1StreamClkRegenerate() == _FALSE)
    {
        DebugMessageRx1("7. DP SteamClk Fail", 0);

        return _SOURCE_NONE;
    }

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if((ScalerSyncCheckUrgentEvent() == _TRUE))
    {
        return _SOURCE_NONE;
    }
#endif

    if(ScalerDpRx1FifoCheck(_DP_FIFO_DELAY_CHECK) == _FALSE)
    {
#if(_DP_FREESYNC_SUPPORT == _ON)
        if(GET_FREESYNC_ENABLED() == _TRUE)
        {
            return _SOURCE_NONE;
        }
        else
#endif
        {
#if(_URGENT_EVENT_CHECK_MODE == _ON)
            if((ScalerSyncCheckUrgentEvent() == _TRUE))
            {
                return _SOURCE_NONE;
            }
#endif

            ScalerDpRx1AdjustVsyncDelay();

#if(_URGENT_EVENT_CHECK_MODE == _ON)
            if((ScalerSyncCheckUrgentEvent() == _TRUE))
            {
                return _SOURCE_NONE;
            }
#endif

            if(ScalerDpRx1FifoCheck(_DP_FIFO_DELAY_CHECK) == _FALSE)
            {
#if(_URGENT_EVENT_CHECK_MODE == _ON)
                if((ScalerSyncCheckUrgentEvent() == _TRUE))
                {
                    return _SOURCE_NONE;
                }
#endif

                ScalerDpRx1AdjustVsyncDelay();

#if(_URGENT_EVENT_CHECK_MODE == _ON)
                if((ScalerSyncCheckUrgentEvent() == _TRUE))
                {
                    return _SOURCE_NONE;
                }
#endif

                if(ScalerDpRx1FifoCheck(_DP_FIFO_DELAY_CHECK) == _FALSE)
                {
                    DebugMessageRx1("7. DP Fifo Fail", 0);

                    return _SOURCE_NONE;
                }
            }
        }
    }

    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HDCP_LONG_HOTPLUG_EVENT);

#if(_DP_FREESYNC_SUPPORT == _ON)
    // Measurement Enable for On-Line VFreq check
    ScalerSetBit(PB8_58_MN_MEAS_CTRL, ~_BIT7, _BIT7);
#endif

    ScalerSetBit(PB8_31_DP_OUTPUT_CTRL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

#if(_AUDIO_SUPPORT == _ON)
    // Enable Audio Channel
    ScalerAudioDpAudioEnable(_ENABLE, _D1_INPUT_PORT);
#endif

#if(_DP_MST_SUPPORT == _ON)
    CLR_DP_RX1_SOURCE_FIRST_POWER_ON();
#endif

#if(_ULTRA_HDR_SUPPORT == _ON)
    ScalerDpRx1GetInfoFrameRSV0(g_pucDPRx1RSV0Backup);

    // Set DP RSV0 info type: HDR
    ScalerSetByte(PB9_2C_DP_INFO_FM_RSV0, _HDR_INFO_TYPE);
#endif

    return _SOURCE_DP;
}

//--------------------------------------------------
// Description  : Signal Detection for DP(Power Saving)
// Input Value  : None
// Output Value : True : DP Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerDpRx1PSPreDetect(void)
{
    // Back to noraml for DP PHY CTS
    if(GET_DP_RX1_PHY_CTS_FLG() == _TRUE)
    {
        return _TRUE;
    }

    if(GET_DP_RX1_VALID_VIDEO_CHECK() == _TRUE)
    {
        DebugMessageRx1("7. Valid Video Check", 0);

        return _TRUE;
    }

    if(GET_DP_RX1_PS_AUX_TOGGLE() == _TRUE)
    {
        DebugMessageRx1("7. Power Saving Aux Handshake", 0);

        return _TRUE;
    }

#if(_DP_MST_SUPPORT == _ON)

    if(GET_REG_DP_RX_MST_ST1_SOURCE_STATUS() != 0x00)
    {
        return _TRUE;
    }

    if(GET_DP_RX1_AUX_CH_POWER_ON_WAKE_UP() == _TRUE)
    {
        CLR_DP_RX1_AUX_CH_POWER_ON_WAKE_UP();

        return _TRUE;
    }
#endif

    if(((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS) &&
        ((ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) != _BIT1) &&
         (ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) != (_BIT2 | _BIT0)))) ||
       (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS_VBIOS))
    {
#if((_SLEEP_AUDIO_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))

        if(ScalerAudioGetDigitalAudioSource(_D1_INPUT_PORT) == _DIGITAL_AUDIO_SOURCE_DP)
        {
            DebugMessageAudio("00. DP Power Saving Audio : Idle Pattern Case", ScalerAudioGetDigitalAudioSource(_D1_INPUT_PORT));
            return _TRUE;
        }
#endif
        DebugMessageRx1("7. Idle Pattern Case", 0);

        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : On Line Check DP stability
// Input Value  : None
// Output Value : True --> DP Stable
//                False --> DP Unstable
//--------------------------------------------------
bit ScalerDpRx1StableDetect(void)
{
#if(_DP_POWER_MANAGEMENT_FOR_FAST_DISPLAY_RECOVER == _ON)
    if(ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT1)
#else
    if((ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT1) ||
       (ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)))
#endif
    {
        DebugMessageRx1("7. DP Power Down", 0);

        return _FALSE;
    }

    if((ScalerDpRx1CDRCheck(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _FALSE) || (ScalerDpRx1AlignCheck() == _FALSE) || (ScalerDpRx1DecodeCheck() == _FALSE) ||
       ((ScalerDpRx1DFECheck() == _FALSE) && (ScalerDpRx1SignalCheck(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _FALSE)))
    {
        SET_DP_RX1_AUX_MANUAL_MODE();

        if(GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_LINK_TRAINING_PASS)
        {
            SET_DP_RX1_LINK_TRAINING_STATUS(_DP_LINK_STATUS_FAIL);
        }

        SET_DP_RX1_AUX_AUTO_MODE();

        DebugMessageRx1("7. DP Link Fail", 0);

        return _FALSE;
    }

    if(ScalerDpRx1GetVideoStream() == _FALSE)
    {
        DebugMessageRx1("7. DP Video Stream Fail", 0);

        return _FALSE;
    }

    if(ScalerDpRx1MiscCheck() == _FALSE)
    {
        DebugMessageRx1("7. DP Misc Change", 0);

        return _FALSE;
    }

    if(ScalerDpRx1FifoCheck(_DP_FIFO_POLLING_CHECK) == _FALSE)
    {
        DebugMessageRx1("7. Fifo Under/Overflow", 0);

        return _FALSE;
    }

    if(ScalerDpRx1MSAActiveChange() == _TRUE)
    {
        DebugMessageRx1("7. MSA Timing Change", 0);

        return _FALSE;
    }

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(ScalerDpRx1GetFREESYNCStatusChange() == _TRUE)
    {
        return _FALSE;
    }
#endif

    // Clear CPIRQ Flag
    ScalerDpRx1CheckHdcpCpirqStatus();

    ScalerDpRx1CrcCalculate();

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP DC OFF to Normal HPD Process
// Input Value  : UserData -> _DP_HOT_PLUG_DC_OFF_HIGH status
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HPDPowerOfftoNormalProc(BYTE ucDpHotPlugDCOffHighStatus)
{
    if((ucDpHotPlugDCOffHighStatus) == _TRUE)
    {
        //////////////////////////////////////////////////////////////////////////////////////
        // For 6193 case, HDCP moudle in Power isolation region, so system go to ps/pd mode,
        // system flow will change HDCP capablity, this lead to in the second time DC on need
        // Rx notify Tx re-link up HDCP handle by pulling a long HPD Evnet, future RL6410 no
        // need this case
        //////////////////////////////////////////////////////////////////////////////////////
#if(_DP_DELL_D3_TEST_SUPPORT == _OFF)
        if(ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT0)
#endif
        {
            DebugMessageDigital("7. Long HPD Event", ucDpHotPlugDCOffHighStatus);

            ScalerDpRx1HotPlugEvent(_DP_LONG_HPD_EVENT);
        }
    }
#if(_DP_MST_SUPPORT == _ON)
    else if(ucDpHotPlugDCOffHighStatus == _LOW_FOR_MST)
    {
        // In MST mode, It should be reset certainly moudle for MSG link up between Tx and Rx
        // In addition, "AC On to Normal", aux reset bit has not be set, It's better do MST reset and then pull high hpd.
        // "PS/PD to Normal", It has done MST reset success in "Normal to PS/PD", here operating MST reset is treated as no effect in order to look after "AC On to Normal" order.
        ScalerDpMstReset(_DP_MST_RX1_PORT);

        // In MST Mode, It should be give enough HPD Low time between two times DC on/off operation prevent no picture light up happen
        ScalerDpRx1HotPlugEvent(_DP_MST_LONG_HPD_EVENT);
    }
#endif
    else
    {
        DebugMessageDigital("7. HPD Asserted", ucDpHotPlugDCOffHighStatus);

        ScalerDpRx1HotPlugEvent(_DP_HPD_ASSERTED);
    }
}

//--------------------------------------------------
// Description  : Check VGIP VS bypass for DP
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDpRx1CheckVgipVsBypass(void)
{
    // Get Hstart
    ScalerRead(PB8_43_MN_DPF_HST_M, 2, &pData[0], _AUTOINC);

    // Get Vstart
    ScalerRead(PB8_4B_MN_DPF_VST_M, 2, &pData[2], _AUTOINC);

    // Check for nVedia 2560x1440@144Hz timing (reduced blanking)
    if((PDATA_WORD(0) < _VGIP_IH_CAPTURE_MIN_VALUE) ||
       (PDATA_WORD(1) <= _VGIP_IV_CAPTURE_MIN_VALUE))
    {
        DebugMessageRx1("DP RX1 VGIP VS Bypass Mode", PDATA_WORD(0));

        return _TRUE;
    }

    return _FALSE;
}

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp Rx LT Status Check
// Input Value  : None
// Output Value : True --> LT Status Pass
//                False --> LT Status Fail
//--------------------------------------------------
bit ScalerDpRx1LTStatusCheck(void)
{
    if((ScalerDpRx1CDRCheck(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _TRUE) && (ScalerDpRx1AlignCheck() == _TRUE) && (ScalerDpRx1DecodeCheck() == _TRUE) &&
       ((ScalerDpRx1DFECheck() == _TRUE) || (ScalerDpRx1SignalCheck(ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00), (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x01) & 0x1F)) == _TRUE)))
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Dp Rx Aux Ch Power Status Check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1AuxChPowerStatusCheck(bit bCableStatus)
{
    if(g_enumDpMSTCapablePort == _DP_MST_RX1_PORT)
    {
        if(bCableStatus == _TRUE)
        {
            if(bD1_HPD == _D1_HOT_PLUG_HIGH)
            {
                // Whether to Start Debounce
                if((GET_PCB_D1_DP_SOURCE_POWER() == _OFF) &&
                   (GET_DP_RX1_CHECK_AUX_CH_NO_POWER_DEBOUNCE() == _FALSE) &&
                   (GET_DP_RX1_CHECK_AUX_CH_POWER_OFF() == _FALSE))
                {
                    SET_DP_RX1_CHECK_AUX_CH_NO_POWER_DEBOUNCE();

                    ScalerTimerActiveTimerEvent(SEC(0.2), _SCALER_TIMER_EVENT_DP_RX1_AUX_CH_NO_POWER_CHECK_DEBOUNCE);
                }

                // Debouncing
                if(GET_DP_RX1_CHECK_AUX_CH_NO_POWER_DEBOUNCE() == _TRUE)
                {
                    if(GET_PCB_D1_DP_SOURCE_POWER() == _ON)
                    {
                        CLR_DP_RX1_CHECK_AUX_CH_NO_POWER_DEBOUNCE();
                        ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_AUX_CH_NO_POWER_CHECK_DEBOUNCE);
                    }
                }

                // Enable 1.5s Hotplug when Source Power On
                if((GET_DP_RX1_CHECK_AUX_CH_POWER_OFF() == _TRUE) && (GET_PCB_D1_DP_SOURCE_POWER() == _ON))
                {
                    CLR_DP_RX1_CHECK_AUX_CH_POWER_OFF();

                    SET_DP_RX1_AUX_CH_POWER_ON_WAKE_UP();

                    SET_DP_RX1_SOURCE_FIRST_POWER_ON();

                    ScalerDpMstReset(g_enumDpMSTCapablePort);

                    ScalerDpRx1HotPlugEvent(_DP_HPD_LOW);

                    ScalerTimerActiveTimerEvent(SEC(1.5), _SCALER_TIMER_EVENT_DP_RX1_AUX_CH_POWER_ON_WAIT_HOTPLUG_HIGH);

#if(_DP_TX_SUPPORT == _ON)

                    if((GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG) && (GET_DP_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_MSG_SUPPORT))
                    {
                        // Clear Payload ID Only if Downstream PID Table is Not Empty
                        if(ScalerDpTxAuxNativeRead(0x00, 0x02, 0xC1, 1, pData) == _TRUE)
                        {
                            if(pData[0] != 0x00)
                            {
                                // Set Flag to Gen Clear ID Table Msg
                                SET_DP_GEN_DOWN_REQUEST_MSG(_DP_MSG_CLEAR_PAYLOAD_ID_TABLE);
                            }
                        }
                        else
                        {
                            // Set Flag to Gen Clear ID Table Msg
                            SET_DP_GEN_DOWN_REQUEST_MSG(_DP_MSG_CLEAR_PAYLOAD_ID_TABLE);
                        }
                    }
#endif
                }
            }
        }
        else
        {
            CLR_DP_RX1_CHECK_AUX_CH_NO_POWER_DEBOUNCE();
            CLR_DP_RX1_CHECK_AUX_CH_POWER_OFF();

            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_AUX_CH_NO_POWER_CHECK_DEBOUNCE);
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_AUX_CH_POWER_ON_WAIT_HOTPLUG_HIGH);
        }
    }
}

//--------------------------------------------------
// Description  : Backup MST Info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1MstInfoBackup(EnumDpMstBackup enumDpMstBackup)
{
    switch(enumDpMstBackup)
    {
        case _DP_MST_BACKUP_INFO:

            if((ScalerGetBit(PB0_01_PHY_DIG_RESET_CTRL, _BIT7) == _BIT7) &&
               (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_FAKE_LINK_TRAINING_PASS))
            {
                // Backup MST Enable
                g_stDpRx1MiscInfo.b1DpMstEnableBackup = _TRUE;

                // Backup TimeSlot Info
                g_pucDpRx1MstTimeSlotBackup[0] = ScalerGetByte(PB8_03_STHD_CTRL_2);
                g_pucDpRx1MstTimeSlotBackup[1] = ScalerGetByte(PB8_04_STHD_CTRL_3);
                g_pucDpRx1MstTimeSlotBackup[2] = ScalerGetByte(PB8_05_STHD_CTRL_4);
                g_pucDpRx1MstTimeSlotBackup[3] = ScalerGetByte(PB8_06_STHD_CTRL_5);
                g_pucDpRx1MstTimeSlotBackup[4] = ScalerGetByte(PB8_07_STHD_CTRL_6);
                g_pucDpRx1MstTimeSlotBackup[5] = ScalerGetByte(PB8_08_STHD_CTRL_7);
                g_pucDpRx1MstTimeSlotBackup[6] = ScalerGetByte(PB8_09_STHD_CTRL_8);
                g_pucDpRx1MstTimeSlotBackup[7] = ScalerGetByte(PB8_0A_STHD_CTRL_9);
                g_pucDpRx1MstTimeSlotBackup[8] = ScalerGetByte(PB8_0B_STHD_CTRL_10);
                g_pucDpRx1MstTimeSlotBackup[9] = ScalerGetByte(PB8_0C_STHD_CTRL_11);
                g_pucDpRx1MstTimeSlotBackup[10] = ScalerGetByte(PB8_0D_SOURCE_SEL_0);
                g_pucDpRx1MstTimeSlotBackup[11] = ScalerGetByte(PB8_0E_SOURCE_SEL_1);
                g_pucDpRx1MstTimeSlotBackup[12] = ScalerGetByte(PB8_0F_SOURCE_SEL_2);
            }

            break;

        case _DP_MST_BACKUP_INFO_RESTORE:

            if(((ScalerDpRx1GetDpcdInfo(0x00, 0x00, 0x21) & _BIT0) == _BIT0) && (g_stDpRx1MiscInfo.b1DpMstEnableBackup == _TRUE))
            {
                // Enable MST Decode
                ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT7, _BIT7);

                // Restore TimeSlot Info
                ScalerSetByte(PB8_03_STHD_CTRL_2, g_pucDpRx1MstTimeSlotBackup[0]);
                ScalerSetByte(PB8_04_STHD_CTRL_3, g_pucDpRx1MstTimeSlotBackup[1]);
                ScalerSetByte(PB8_05_STHD_CTRL_4, g_pucDpRx1MstTimeSlotBackup[2]);
                ScalerSetByte(PB8_06_STHD_CTRL_5, g_pucDpRx1MstTimeSlotBackup[3]);
                ScalerSetByte(PB8_07_STHD_CTRL_6, g_pucDpRx1MstTimeSlotBackup[4]);
                ScalerSetByte(PB8_08_STHD_CTRL_7, g_pucDpRx1MstTimeSlotBackup[5]);
                ScalerSetByte(PB8_09_STHD_CTRL_8, g_pucDpRx1MstTimeSlotBackup[6]);
                ScalerSetByte(PB8_0A_STHD_CTRL_9, g_pucDpRx1MstTimeSlotBackup[7]);
                ScalerSetByte(PB8_0B_STHD_CTRL_10, g_pucDpRx1MstTimeSlotBackup[8]);
                ScalerSetByte(PB8_0C_STHD_CTRL_11, g_pucDpRx1MstTimeSlotBackup[9]);
                ScalerSetByte(PB8_0D_SOURCE_SEL_0, g_pucDpRx1MstTimeSlotBackup[10]);
                ScalerSetByte(PB8_0E_SOURCE_SEL_1, g_pucDpRx1MstTimeSlotBackup[11]);
                ScalerSetByte(PB8_0F_SOURCE_SEL_2, g_pucDpRx1MstTimeSlotBackup[12]);
            }

            g_stDpRx1MiscInfo.b1DpMstEnableBackup = _FALSE;

            break;

        case _DP_MST_BACKUP_INFO_RESET:
        default:

            g_stDpRx1MiscInfo.b1DpMstEnableBackup = _FALSE;

            break;
    }
}

//--------------------------------------------------
// Description  : DP Rx1 Mst Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1MstReset(void)
{
    SET_DP_RX1_AUX_MANUAL_MODE();

    // Reset GUID
    for(pData[0] = 0; pData[0] < 16; pData[0]++)
    {
        ScalerDpRx1SetDpcdValue(0x00, 0x00, (0x30 + pData[0]), 0x00);
    }

    ScalerDpRx1SetDpcdValue(0x00, 0x02, 0x00, ((ScalerDpRx1GetDpcdInfo(0x00, 0x02, 0x00) & 0xC0) | 0x01));

    // Disable 0x111 IRQ
    ScalerSetBit(PBA_B2_AUX_SPECIAL_IRQ_EN, ~_BIT7, 0x00);

    ScalerDpRx1SetDpcdValue(0x00, 0x01, 0x11, 0x00);

    // CLR 0x111 IRQ Flag
    ScalerSetBit(PBA_B3_AUX_SPECIAL_IRQ_FLAG, ~(_BIT7 | _BIT4), _BIT7);

    // Enable 0x111 IRQ
    ScalerSetBit(PBA_B2_AUX_SPECIAL_IRQ_EN, ~_BIT7, _BIT7);

    SET_DP_RX1_AUX_AUTO_MODE();

    // Disable MST
    ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT7, 0x00);

    // Clear Payload ID Table
    ScalerSetBit(PBA_B0_AUX_PAYLOAD_CLEAR, ~_BIT6, _BIT6);
    ScalerSetBit(PBA_B0_AUX_PAYLOAD_CLEAR, ~_BIT6, 0x00);

    // Reset ST1 ~ ST5
    for(pData[0] = 0; pData[0] < 5; pData[0]++)
    {
        // Reset Start Position
        ScalerSetByte(PB8_03_STHD_CTRL_2 + (pData[0] << 1), 0x00);

        // Reset End Position
        ScalerSetByte(PB8_04_STHD_CTRL_3 + (pData[0] << 1), 0x00);
    }

    // Reset ST1_Source ~ ST5_Source
    ScalerSetBit(PB8_0D_SOURCE_SEL_0, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
    ScalerSetBit(PB8_0D_SOURCE_SEL_0, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(PB8_0E_SOURCE_SEL_1, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
    ScalerSetBit(PB8_0E_SOURCE_SEL_1, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(PB8_0F_SOURCE_SEL_2, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

    // Reset Daisy Chain ST3 ~ ST5
    for(pData[0] = 0; pData[0] < 3; pData[0]++)
    {
        // Reset Start Position
        ScalerSetByte(RET_REG_ADDR_DP_RX1_DAIZY_ST3_START() + (pData[0] << 1), 0x00);

        // Reset End Position
        ScalerSetByte(RET_REG_ADDR_DP_RX1_DAIZY_ST3_END() + (pData[0] << 1), 0x00);
    }

    if((GET_REG_DP_RX_DOWN_REQUEST_BUF0_MSG_FINISH() == 0x01) || (GET_REG_DP_RX_DOWN_REQUEST_BUF1_MSG_FINISH() == 0x01))
    {
        SET_DP_RX1_AUX_COMMAND_NO_REPLY();
    }

    // Disable Buf0 / Buf1 Receive Capability
    CLR_REG_DP_RX_DOWN_REQUEST_MSG_RECEIVE_CRC_IGNORE_ENABLE();

    // Clr Buf0/Buf1 DownRequest MSG Finish Flag
    CLR_REG_DP_RX_DOWN_REQUEST_MSG_FINISH();

    // Clr Buf0 / Buf1
    CLR_REG_DP_RX_DOWN_REQUEST_BUF0_BUF1();

    // Clr Buf0/Buf1 MSG Error Flag
    CLR_REG_DP_RX_DOWN_REQUEST_MSG_ERROR();

    // Disable MST Related IRQ
    CLR_REG_DP_RX_DOWN_REPLY_UP_REQUEST_READY_BIT_IRQ();

    // Clr 1000h Has Been Write
    CLR_REG_DP_RX_DOWN_REQUEST_ADDR_WRITTEN();

    // Disable Rx Igrone Error
    ScalerSetBit(PBA_D1_DP_IIC_SET, ~_BIT3, 0x00);

    // Message Upstream Disable
    CLR_REG_DP_RX_UPSTREAM_REPLY();

    // Reset Rx MSG Block
    ScalerSetBit(PBA_C0_DPCD_CTRL, ~_BIT6, _BIT6);
    ScalerSetBit(PBA_C0_DPCD_CTRL, ~_BIT6, 0x00);

    if(g_enumDpMSTCapablePort == _DP_MST_RX1_PORT)
    {
        // Enable DownRequest Buf0 / Buf1 Receive Capability
        SET_REG_DP_RX_DOWN_REQUEST_MSG_RECEIVE_CRC_IGNORE_ENABLE();

        // Enable UpReply Buf0 / Buf1 Receive Capability
        SET_REG_DP_RX_UP_REPLY_MSG_RECEIVE_CRC_IGNORE_ENABLE();
    }
}

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp Rx HDCP Auth Handler
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpRx1HDCPHandler(void)
{
    CLR_DP_RX1_HDCP_UPSTREAM_EVENT();

    if(GET_DP_RX1_HDCP_REPEATER_SUPPORT() == _TRUE)
    {
        // After receiving AKSV, handler must initialize authentication
        if(GET_DP_RX1_HDCP_AUTH_AKSV_WRITTEN() == _TRUE)
        {
            CLR_DP_RX1_HDCP_AUTH_AKSV_WRITTEN();
            CLR_DP_RX1_HDCP_AUTH_CPIRQ_TIMRE();

            ScalerDpRx1HDCPChangeAuthState(_DP_RX_HDCP_STATE_IDLE);

            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HDCP_CPIRQ_EVENT);
        }

        if(GET_DP_RX_HDCP_UPSTREAM_PORT() == _HDCP_D1_PORT)
        {
            // In MST mode
            if((ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x11) & _BIT0) == _BIT0)
            {
                if((ScalerDpRx1HdcpEnebled() == _TRUE) && (GET_DP_RX1_HDCP_AUTH_CPIRQ_TIMRE() == _FALSE))
                {
                    if(ScalerDpRx1HDCPCheckLvp() == _FALSE)
                    {
                        SET_DP_RX1_HDCP_AUTH_CPIRQ_TIMRE();

                        ScalerDpRx1CpIRQ(_DP_HDCP_BSTATUS_LINK_INTEGRITY_FAIL);

                        ScalerTimerActiveTimerEvent(SEC(0.02), _SCALER_TIMER_EVENT_DP_RX1_HDCP_CPIRQ_EVENT);
                    }
                }
            }
            else
            {
                // In SST mode, issue HPD event for upstream device if DPTX connect a new downstream device.
                if((ScalerDpRx1HdcpEnebled() == _TRUE) && (ScalerDpRx1HDCPCheckLvp() == _TRUE))
                {
                    if(GET_DP_TX_HDCP_DOWNSTREAM_EVENT() == _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_REAUTH)
                    {
                        ScalerDpRx1HotPlugEvent(_DP_HDCP_LONG_HPD_EVENT);
                    }
                }
            }
        }

        if((GET_DP_RX1_HDCP_AUTH_STATE() != _DP_RX_HDCP_STATE_IDLE) && (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_LINK_TRAINING_NONE))
        {
            ScalerDpRx1HDCPChangeAuthState(_DP_RX_HDCP_STATE_IDLE);
        }
    }

    switch(GET_DP_RX1_HDCP_AUTH_STATE())
    {
        case _DP_RX_HDCP_STATE_IDLE:

            if(GET_DP_RX1_HDCP_AUTH_STATE_CHANGE() == _TRUE)
            {
                CLR_DP_RX1_HDCP_AUTH_STATE_CHANGE();
                CLR_DP_RX1_HDCP_AUTH_REPEATER_PROC_TIMEOUT();
                CLR_DP_RX1_HDCP_AUTH_CPIRQ_TIMRE();

                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HDCP_REPEATER_PROC_TIMEOUT);
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HDCP_READ_IRQ_TIMEOUT);
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HDCP_CPIRQ_EVENT);

                ScalerDpRx1HDCPEnableReadIrq(_DISABLE);

                SET_DP_RX1_HDCP_UPSTREAM_EVENT(_DP_RX_HDCP_UPSTREAM_AUTH_EVENT_STOP_ENCRYPTION);
            }

            if(GET_DP_RX1_HDCP_REPEATER_SUPPORT() == _TRUE)
            {
                // Check if R0' was read already by upstream device.
                if((ScalerGetBit(PB0_20_HDCP_DEBUG, (_BIT7 | _BIT5)) == (_BIT7 | _BIT5)) &&
                   ((ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x05) != 0x00) || (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x06) != 0x00)) &&
                   ((ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x29) & _DP_HDCP_BSTATUS_R0_AVAILABLE) == 0x00))
                {
                    ScalerDpRx1HDCPChangeAuthState(_DP_RX_HDCP_STATE_AUTH_1);
                }
            }

            break;

        case _DP_RX_HDCP_STATE_AUTH_1:

            if(GET_DP_RX1_HDCP_AUTH_STATE_CHANGE() == _TRUE)
            {
                CLR_DP_RX1_HDCP_AUTH_STATE_CHANGE();

                if(GET_DP_RX_HDCP_UPSTREAM_PORT() == _HDCP_D1_PORT)
                {
                    // Check if downstream device support HDCP capability.
                    if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
                    {
                        // Issue event to make DPTX start HDCP handshake.
                        SET_DP_RX1_HDCP_UPSTREAM_EVENT(_DP_RX_HDCP_UPSTREAM_AUTH_EVENT_R0_PASS);

                        ScalerTimerActiveTimerEvent(SEC(6), _SCALER_TIMER_EVENT_DP_RX1_HDCP_REPEATER_PROC_TIMEOUT);
                    }
                    else
                    {
                        ScalerDpRx1HDCPChangeAuthState(_DP_RX_HDCP_STATE_AUTH_2);
                    }
                }
                else
                {
                    ScalerDpRx1HDCPChangeAuthState(_DP_RX_HDCP_STATE_AUTH_FAKE);
                }
            }

            // Wait for downstream pass event or device/depth max event
            if((GET_DP_TX_HDCP_DOWNSTREAM_EVENT() == _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_PASS) ||
               (GET_DP_TX_HDCP_DOWNSTREAM_EVENT() == _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_DEVICE_DEPTH_MAX))
            {
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HDCP_REPEATER_PROC_TIMEOUT);

                ScalerDpRx1HDCPChangeAuthState(_DP_RX_HDCP_STATE_AUTH_2);
            }
            else if(GET_DP_RX1_HDCP_AUTH_REPEATER_PROC_TIMEOUT() == _TRUE)
            {
                CLR_DP_RX1_HDCP_AUTH_REPEATER_PROC_TIMEOUT();

                SET_DP_RX1_HDCP_UPSTREAM_EVENT(_DP_RX_HDCP_UPSTREAM_AUTH_EVENT_TIMEOUT);

                ScalerDpRx1HDCPChangeAuthState(_DP_RX_HDCP_STATE_AUTH_DONE);
            }

            break;

        case _DP_RX_HDCP_STATE_AUTH_2:

            if(GET_DP_RX1_HDCP_AUTH_STATE_CHANGE() == _TRUE)
            {
                CLR_DP_RX1_HDCP_AUTH_STATE_CHANGE();
            }

            if(ScalerDpRx1HDCPCheckBinfo() == _TRUE)
            {
                // Load KSV List to RX KSV FIFO
                ScalerDpRx1HDCPLoadKsvFifo();

                // Input KSV FIFO to SHA-1 and Compute V'
                ScalerDpRx1HDCPWriteShaInput();

                // Write V' into DPCD table
                ScalerDpRx1HDCPLoadShaToDpcd();

                // Set 1st KSV FIFO to DPCD table
                ScalerDpRx1HDCPSetKsvFifoFirst();

                // Enable 68xxx Read INT
                ScalerDpRx1HDCPEnableReadIrq(_ENABLE);

                ScalerTimerActiveTimerEvent(SEC(5), _SCALER_TIMER_EVENT_DP_RX1_HDCP_READ_IRQ_TIMEOUT);
            }

            // Set V' Ready Bit and Issue CP_IRQ
            ScalerDpRx1CpIRQ(_DP_HDCP_BSTATUS_V_READY);

            ScalerDpRx1HDCPChangeAuthState(_DP_RX_HDCP_STATE_AUTH_DONE);

            break;

        case _DP_RX_HDCP_STATE_AUTH_FAKE:

            if(GET_DP_RX1_HDCP_AUTH_STATE_CHANGE() == _TRUE)
            {
                CLR_DP_RX1_HDCP_AUTH_STATE_CHANGE();
            }

            // Enable 68xxx Read INT
            ScalerDpRx1HDCPEnableReadIrq(_DISABLE);

            // Fake Authentication
            ScalerDpRx1HDCPFakeAuthenProc();

            // Set V' Ready Bit and Issue CP_IRQ
            ScalerDpRx1CpIRQ(_DP_HDCP_BSTATUS_V_READY);

            ScalerDpRx1HDCPChangeAuthState(_DP_RX_HDCP_STATE_AUTH_DONE);

            break;

        case _DP_RX_HDCP_STATE_AUTH_DONE:

            if(GET_DP_RX1_HDCP_AUTH_STATE_CHANGE() == _TRUE)
            {
                CLR_DP_RX1_HDCP_AUTH_STATE_CHANGE();
            }

            if(GET_DP_RX1_HDCP_AUTH_READ_IRQ_TIMEOUT() == _TRUE)
            {
                ScalerDpRx1HDCPEnableReadIrq(_DISABLE);
            }

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Change HDCP Auth State
// Input Value  : Target HDCP Auth State
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HDCPChangeAuthState(EnumDPRxHDCPAuthState enumHDCPAuthState)
{
    SET_DP_RX1_HDCP_AUTH_STATE(enumHDCPAuthState);
    SET_DP_RX1_HDCP_AUTH_STATE_CHANGE();
}

//--------------------------------------------------
// Description  : Set HDCP Repeater Proc Timeout
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HDCPSetRepeaterProcTimeout(void)
{
    SET_DP_RX1_HDCP_AUTH_REPEATER_PROC_TIMEOUT();
}

//--------------------------------------------------
// Description  : Set HDCP Read IRQ Timeout
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HDCPSetReadIrqTimeout(void)
{
    SET_DP_RX1_HDCP_AUTH_READ_IRQ_TIMEOUT();
}

//--------------------------------------------------
// Description  : Enable HDCP Read IRQ Function
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HDCPEnableReadIrq(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        if(ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x2A) > 3)
        {
            CLR_DP_RX1_HDCP_KSV_FIFO_INT_FLAG();

            ScalerSetBit(PBA_FA_DUMMY_0, ~(_BIT3 | _BIT1), (_BIT3 | _BIT1));
        }
    }
    else
    {
        ScalerSetBit(PBA_FA_DUMMY_0, ~(_BIT3 | _BIT1), 0x00);

        CLR_DP_RX1_HDCP_AUTH_READ_IRQ_TIMEOUT();
    }
}

//--------------------------------------------------
// Description  : Check B info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpRx1HDCPCheckBinfo(void)
{
    BYTE ucBInfoDevice = 0;
    BYTE ucBInfoDepth = 0;

    if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
    {
        if(GET_DP_TX_HDCP_DOWNSTREAM_REPEATER() == _TRUE)
        {
            ucBInfoDevice = (GET_DP_TX_HDCP_DOWNSTREAM_DEVICE_COUNT() <= 125) ? GET_DP_TX_HDCP_DOWNSTREAM_DEVICE_COUNT() : 0x80;
            ucBInfoDepth = (GET_DP_TX_HDCP_DOWNSTREAM_DEPTH() <= 6) ? GET_DP_TX_HDCP_DOWNSTREAM_DEPTH() : 0x08;
        }

        if(ucBInfoDevice != 0x80)
        {
            ucBInfoDevice++;
        }
    }

    if(ucBInfoDevice != 0x80)
    {
        ucBInfoDevice++;
    }

    if(ucBInfoDepth != 0x08)
    {
        ucBInfoDepth++;
    }

    ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x2A, ucBInfoDevice);
    ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x2B, ucBInfoDepth);

    if((ucBInfoDevice == 0x80) || (ucBInfoDepth == 0x08))
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Load KSV List to Rx KSV FIFO
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HDCPLoadKsvFifo(void)
{
    PDATA_WORD(0) = 0;
    PDATA_WORD(1) = 0;

    if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
    {
        if(GET_DP_TX_HDCP_DOWNSTREAM_REPEATER() == _TRUE)
        {
            PDATA_WORD(1) = (WORD) GET_DP_TX_HDCP_DOWNSTREAM_DEVICE_COUNT() * 5;
        }

        ScalerRead(PBB_4F_BKSV_0, 5, &pData[4], _AUTOINC);

        // Load BKSV of Downstream into KSV FIFO
        for(PDATA_WORD(0) = 0; PDATA_WORD(0) < 5; PDATA_WORD(0)++)
        {
            g_pucDpTxHdcpKsvFifo[PDATA_WORD(1)] = pData[4 + PDATA_WORD(0)];

            PDATA_WORD(1)++;
        }
    }

    // Load KSV of TX into KSV FIFO
    for(PDATA_WORD(0) = 0; PDATA_WORD(0) < 5; PDATA_WORD(0)++)
    {
        g_pucDpTxHdcpKsvFifo[PDATA_WORD(1)] = g_pucHdcpAksvBackup[PDATA_WORD(0)];

        PDATA_WORD(1)++;
    }

    for(PDATA_WORD(0) = PDATA_WORD(1); PDATA_WORD(0) < ((WORD) _DP_TX_HDCP_DEVICE_COUNT_MAX * 5); PDATA_WORD(0)++)
    {
        g_pucDpTxHdcpKsvFifo[PDATA_WORD(0)] = 0x00;
    }
}

//--------------------------------------------------
// Description  : Load KSV List to Rx KSV FIFO
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HDCPSetKsvFifoFirst(void)
{
    SET_DP_RX1_AUX_MANUAL_MODE();

    for(g_usDpRx1HdcpKsvFifoOffset = 0; g_usDpRx1HdcpKsvFifoOffset < 15; g_usDpRx1HdcpKsvFifoOffset++)
    {
        ScalerDpRx1SetDpcdValue(0x06, 0x80, (0x2C + g_usDpRx1HdcpKsvFifoOffset), g_pucDpTxHdcpKsvFifo[g_usDpRx1HdcpKsvFifoOffset]);
    }

    // Aux HW Control
    SET_DP_RX1_AUX_AUTO_MODE();
}

//--------------------------------------------------
// Description  : Load KSV FIFO to SHA-1 Input
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HDCPWriteShaInput(void)
{
    WORD usKsvFifoLength = 0;
    WORD usShaInputBitNumbers = 0;
    WORD usKsvLengthTemp = 0;

    usKsvFifoLength = (WORD) ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x2A) * 5;

    // Total bit numbers of SHA-1 input = KSV FIFO + B_info + M0'
    usShaInputBitNumbers = (usKsvFifoLength + 2 + 8) * 8;

    // Reset SHA Block counter
    ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT3, _BIT3);

    // Start to Write SHA-1 Transform Input
    ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT3, 0x00);

    // Write the KSV List into SHA-1 Transform Input
    do
    {
        ScalerSetByte(PB0_31_SHA_DATA1, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp]);
        ScalerSetByte(PB0_32_SHA_DATA2, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp + 1]);
        ScalerSetByte(PB0_33_SHA_DATA3, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp + 2]);
        ScalerSetByte(PB0_34_SHA_DATA4, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp + 3]);

        // Enable write 32-bit data to SHA-1 block
        ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);

        usKsvLengthTemp += 4;

        if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
        {
            ScalerDpRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
        }
    }
    while((usKsvFifoLength - usKsvLengthTemp) >= 4);

    // Write the remaining KSV, B info and M0' into SHA-1 Transform Input
    switch(usKsvFifoLength - usKsvLengthTemp)
    {
        case 1:

            ScalerSetByte(PB0_31_SHA_DATA1, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp]);
            ScalerSetByte(PB0_32_SHA_DATA2, ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x2A));
            ScalerSetByte(PB0_33_SHA_DATA3, ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x2B));
            ScalerSetByte(PB0_34_SHA_DATA4, ScalerGetByte(PB0_2F_M0_BYTE_0));

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PB0_31_SHA_DATA1, ScalerGetByte(PB0_2E_M0_BYTE_1));
            ScalerSetByte(PB0_32_SHA_DATA2, ScalerGetByte(PB0_2D_M0_BYTE_2));
            ScalerSetByte(PB0_33_SHA_DATA3, ScalerGetByte(PB0_2C_M0_BYTE_3));
            ScalerSetByte(PB0_34_SHA_DATA4, ScalerGetByte(PB0_2B_M0_BYTE_4));

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PB0_31_SHA_DATA1, ScalerGetByte(PB0_2A_M0_BYTE_5));
            ScalerSetByte(PB0_32_SHA_DATA2, ScalerGetByte(PB0_29_M0_BYTE_6));
            ScalerSetByte(PB0_33_SHA_DATA3, ScalerGetByte(PB0_28_M0_BYTE_7));
            ScalerSetByte(PB0_34_SHA_DATA4, 0x80);

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            break;

        case 2:

            ScalerSetByte(PB0_31_SHA_DATA1, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp]);
            ScalerSetByte(PB0_32_SHA_DATA2, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp + 1]);
            ScalerSetByte(PB0_33_SHA_DATA3, ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x2A));
            ScalerSetByte(PB0_34_SHA_DATA4, ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x2B));

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PB0_31_SHA_DATA1, ScalerGetByte(PB0_2F_M0_BYTE_0));
            ScalerSetByte(PB0_32_SHA_DATA2, ScalerGetByte(PB0_2E_M0_BYTE_1));
            ScalerSetByte(PB0_33_SHA_DATA3, ScalerGetByte(PB0_2D_M0_BYTE_2));
            ScalerSetByte(PB0_34_SHA_DATA4, ScalerGetByte(PB0_2C_M0_BYTE_3));

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PB0_31_SHA_DATA1, ScalerGetByte(PB0_2B_M0_BYTE_4));
            ScalerSetByte(PB0_32_SHA_DATA2, ScalerGetByte(PB0_2A_M0_BYTE_5));
            ScalerSetByte(PB0_33_SHA_DATA3, ScalerGetByte(PB0_29_M0_BYTE_6));
            ScalerSetByte(PB0_34_SHA_DATA4, ScalerGetByte(PB0_28_M0_BYTE_7));

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PB0_31_SHA_DATA1, 0x80);
            ScalerSetByte(PB0_32_SHA_DATA2, 0x00);
            ScalerSetByte(PB0_33_SHA_DATA3, 0x00);
            ScalerSetByte(PB0_34_SHA_DATA4, 0x00);

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            break;

        case 3:

            ScalerSetByte(PB0_31_SHA_DATA1, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp]);
            ScalerSetByte(PB0_32_SHA_DATA2, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp + 1]);
            ScalerSetByte(PB0_33_SHA_DATA3, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp + 2]);
            ScalerSetByte(PB0_34_SHA_DATA4, ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x2A));

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PB0_31_SHA_DATA1, ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x2B));
            ScalerSetByte(PB0_32_SHA_DATA2, ScalerGetByte(PB0_2F_M0_BYTE_0));
            ScalerSetByte(PB0_33_SHA_DATA3, ScalerGetByte(PB0_2E_M0_BYTE_1));
            ScalerSetByte(PB0_34_SHA_DATA4, ScalerGetByte(PB0_2D_M0_BYTE_2));

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PB0_31_SHA_DATA1, ScalerGetByte(PB0_2C_M0_BYTE_3));
            ScalerSetByte(PB0_32_SHA_DATA2, ScalerGetByte(PB0_2B_M0_BYTE_4));
            ScalerSetByte(PB0_33_SHA_DATA3, ScalerGetByte(PB0_2A_M0_BYTE_5));
            ScalerSetByte(PB0_34_SHA_DATA4, ScalerGetByte(PB0_29_M0_BYTE_6));

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PB0_31_SHA_DATA1, ScalerGetByte(PB0_28_M0_BYTE_7));
            ScalerSetByte(PB0_32_SHA_DATA2, 0x80);
            ScalerSetByte(PB0_33_SHA_DATA3, 0x00);
            ScalerSetByte(PB0_34_SHA_DATA4, 0x00);

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            break;

        default:

            ScalerSetByte(PB0_31_SHA_DATA1, ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x2A));
            ScalerSetByte(PB0_32_SHA_DATA2, ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x2B));
            ScalerSetByte(PB0_33_SHA_DATA3, ScalerGetByte(PB0_2F_M0_BYTE_0));
            ScalerSetByte(PB0_34_SHA_DATA4, ScalerGetByte(PB0_2E_M0_BYTE_1));

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PB0_31_SHA_DATA1, ScalerGetByte(PB0_2D_M0_BYTE_2));
            ScalerSetByte(PB0_32_SHA_DATA2, ScalerGetByte(PB0_2C_M0_BYTE_3));
            ScalerSetByte(PB0_33_SHA_DATA3, ScalerGetByte(PB0_2B_M0_BYTE_4));
            ScalerSetByte(PB0_34_SHA_DATA4, ScalerGetByte(PB0_2A_M0_BYTE_5));

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PB0_31_SHA_DATA1, ScalerGetByte(PB0_29_M0_BYTE_6));
            ScalerSetByte(PB0_32_SHA_DATA2, ScalerGetByte(PB0_28_M0_BYTE_7));
            ScalerSetByte(PB0_33_SHA_DATA3, 0x80);
            ScalerSetByte(PB0_34_SHA_DATA4, 0x00);

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            break;
    }

    if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 60)
    {
        ScalerSetByte(PB0_31_SHA_DATA1, 0x00);
        ScalerSetByte(PB0_32_SHA_DATA2, 0x00);
        ScalerSetByte(PB0_33_SHA_DATA3, 0x00);
        ScalerSetByte(PB0_34_SHA_DATA4, 0x00);

        // Enable write 32-bit data to SHA-1 block
        ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);

        usKsvLengthTemp += 4;

        if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
        {
            ScalerDpRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
        }
    }

    // Write 0x00 into the remaining SHA-1 Transform Input space
    if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) <= 56)
    {
        while((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) < 56)
        {
            ScalerSetByte(PB0_31_SHA_DATA1, 0x00);
            ScalerSetByte(PB0_32_SHA_DATA2, 0x00);
            ScalerSetByte(PB0_33_SHA_DATA3, 0x00);
            ScalerSetByte(PB0_34_SHA_DATA4, 0x00);

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;
        }

        // The length of SHA-1 input is equal to 2^64(8 bytes)
        ScalerSetByte(PB0_31_SHA_DATA1, 0x00);
        ScalerSetByte(PB0_32_SHA_DATA2, 0x00);
        ScalerSetByte(PB0_33_SHA_DATA3, 0x00);
        ScalerSetByte(PB0_34_SHA_DATA4, 0x00);

        // Enable write 32-bit data to SHA-1 block
        ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);

        // Write the valid bit numbers into SHA-1 Transform Input
        ScalerSetByte(PB0_31_SHA_DATA1, 0x00);
        ScalerSetByte(PB0_32_SHA_DATA2, 0x00);
        ScalerSetByte(PB0_33_SHA_DATA3, HIBYTE(usShaInputBitNumbers));
        ScalerSetByte(PB0_34_SHA_DATA4, LOBYTE(usShaInputBitNumbers));

        // Enable write 32-bit data to SHA-1 block
        ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);

        usKsvLengthTemp += 8;

        ScalerDpRx1HDCPAuthShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
    }
}

//--------------------------------------------------
// Description  : Dp Rx HDCP - SHA circuit Run
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HDCPAuthShaRun(bit bIsFirst)
{
    // Set First Run For SHA-1 Circuit
    ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT1, ((bIsFirst == _TRUE) ? _BIT1 : 0x00));

    // Run SHA-1 Circuit
    ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT2, _BIT2);

    ScalerTimerPollingFlagProc(5, PB0_30_SHA_CONTRL, _BIT4, _TRUE);

    // Disable First Run and Disable SHA-1 Circuit
    ScalerSetBit(PB0_30_SHA_CONTRL, ~(_BIT2 | _BIT1), 0x00);
}

//--------------------------------------------------
// Description  : Dp Rx HDCP - Load SHA Result to DPCD table
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HDCPLoadShaToDpcd(void)
{
    SET_DP_RX1_AUX_MANUAL_MODE();

    for(pData[0] = 0; pData[0] < 5; pData[0]++)
    {
        for(pData[1] = 0; pData[1] < 4; pData[1]++)
        {
            ScalerDpRx1SetDpcdValue(0x06, 0x80, (0x14 + (pData[0] * 4) + pData[1]), ScalerGetByte(PB0_39_SHA_3 + (pData[0] * 4) - pData[1]));
        }
    }

    SET_DP_RX1_AUX_AUTO_MODE();
}

#if(_D1_DP_MST_PORT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Load KSV List to Rx KSV FIFO
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HDCPResetKsvFifoToFirst_EXINT0(void) using 1
{
    for(g_usDpRx1HdcpKsvFifoOffset = 0; g_usDpRx1HdcpKsvFifoOffset < 15; g_usDpRx1HdcpKsvFifoOffset++)
    {
        ScalerDpRx1SetDpcdValue_EXINT0(0x06, 0x80, (0x2C + g_usDpRx1HdcpKsvFifoOffset), g_pucDpTxHdcpKsvFifo[g_usDpRx1HdcpKsvFifoOffset]);
    }
}

//--------------------------------------------------
// Description  : Load KSV List to Rx KSV FIFO
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HDCPSetKsvFifo_EXINT0(void) using 1
{
    for(pData_EXINT[0] = 0; pData_EXINT[0] < 15; pData_EXINT[0]++)
    {
        ScalerDpRx1SetDpcdValue_EXINT0(0x06, 0x80, (0x2C + pData_EXINT[0]), g_pucDpTxHdcpKsvFifo[g_usDpRx1HdcpKsvFifoOffset + pData_EXINT[0]]);
    }

    g_usDpRx1HdcpKsvFifoOffset += pData_EXINT[0];
}

#if(_WD_TIMER_INT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Reset Dp Rx HDCP info in WD Timer INT
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpRx1HDCPResetDpcdInfo_WDINT(void) using 3
{
    // Reset HDCP Block
    ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT0, _BIT0);
    ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT0, 0x00);

    ScalerDpRx1SetDpcdValue_WDINT(0x06, 0x80, 0x29, 0x00);
    ScalerDpRx1SetDpcdValue_WDINT(0x06, 0x80, 0x2A, 0x00);
    ScalerDpRx1SetDpcdValue_WDINT(0x06, 0x80, 0x2B, 0x00);

    for(pData_EXINT[0] = 0; pData_EXINT[0] < 20; pData_EXINT[0]++)
    {
        ScalerDpRx1SetDpcdValue_WDINT(0x06, 0x80, (0x14 + pData_EXINT[0]), 0x00);
    }

    for(pData_EXINT[0] = 0; pData_EXINT[0] < 15; pData_EXINT[0]++)
    {
        ScalerDpRx1SetDpcdValue_WDINT(0x06, 0x80, (0x2C + pData_EXINT[0]), 0x00);
    }
}
#endif

//--------------------------------------------------
// Description  : Reset Dp Rx HDCP info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HDCPResetDpcdInfo_EXINT0(void) using 1
{
    if((ScalerDpRx1GetDpcdInfo_EXINT0(0x06, 0x80, 0x2A) != 0x00) || (ScalerDpRx1GetDpcdInfo_EXINT0(0x06, 0x80, 0x2B) != 0x00))
    {
        ScalerDpRx1SetDpcdValue_EXINT0(0x06, 0x80, 0x29, 0x00);
        ScalerDpRx1SetDpcdValue_EXINT0(0x06, 0x80, 0x2A, 0x00);
        ScalerDpRx1SetDpcdValue_EXINT0(0x06, 0x80, 0x2B, 0x00);

        for(pData_EXINT[0] = 0; pData_EXINT[0] < 20; pData_EXINT[0]++)
        {
            ScalerDpRx1SetDpcdValue_EXINT0(0x06, 0x80, (0x14 + pData_EXINT[0]), 0x00);
        }

        for(pData_EXINT[0] = 0; pData_EXINT[0] < 15; pData_EXINT[0]++)
        {
            ScalerDpRx1SetDpcdValue_EXINT0(0x06, 0x80, (0x2C + pData_EXINT[0]), 0x00);
        }

        // Waiting for R0 Calculate Finish
        for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 40; g_ucDpRx1Temp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        ScalerDpRx1SetDpcdValue_EXINT0(0x06, 0x80, 0x29, 0x02);
    }
}

//--------------------------------------------------
// Description  : Upplug Reset For Dp Rx1
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HDCPBlockReset(void)
{
    // Reset HDCP Block
    ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT0, _BIT0);
    ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT0, 0x00);

    ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x29, 0x00);
    ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x2A, 0x00);
    ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x2B, 0x00);

    for(pData[0] = 0; pData[0] < 20; pData[0]++)
    {
        ScalerDpRx1SetDpcdValue(0x06, 0x80, (0x14 + pData[0]), 0x00);
    }

    for(pData[0] = 0; pData[0] < 15; pData[0]++)
    {
        ScalerDpRx1SetDpcdValue(0x06, 0x80, (0x2C + pData[0]), 0x00);
    }

    ScalerDpRx1HDCPChangeAuthState(_DP_RX_HDCP_STATE_IDLE);
}
#endif

//--------------------------------------------------
// Description  : Check Dp Rx HDCP Link Veriffication Pattern (0x531F) for MST Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpRx1HDCPCheckLvp(void)
{
    if(((ScalerGetByte(PB0_1E_HDCP_INTGT_VRF_ANS_MSB) == 0x53) || (ScalerGetByte(PB0_1E_HDCP_INTGT_VRF_ANS_MSB) == 0x00)) &&
       ((ScalerGetByte(PB0_1F_HDCP_INTGT_VRF_ANS_LSB) == 0x1F) || (ScalerGetByte(PB0_1F_HDCP_INTGT_VRF_ANS_LSB) == 0x00)))
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Fake HDCP Authentication
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HDCPFakeAuthenProc(void)
{
    BYTE pucSHAInput[64];

    // Set Device Count and Depth
    ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x2A, 0x01);
    ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x2B, 0x01);

    // Load KSV
    memcpy(pucSHAInput, g_pucHdcpAksvBackup, 5);

    // Load Device Count and Depth
    pucSHAInput[5] = ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x2A);
    pucSHAInput[6] = ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x2B);

    // Load M0'
    for(pData[0] = 0; pData[0] < 8; pData[0]++)
    {
        pucSHAInput[7 + pData[0]] = ScalerGetByte(PB0_2F_M0_BYTE_0 - pData[0]);
    }

    memset(&pucSHAInput[15], 0, 49);

    pucSHAInput[15] = 0x80;

    // Total bit numbers of SHA-1 input = KSV FIFO + B_info + M0'
    pucSHAInput[63] = 0x78;

    // Compute V'
    ScalerDpRx1HDCPSha1Calculate(pucSHAInput, 0);

    // Write Ksv to DPCD table
    SET_DP_RX1_AUX_MANUAL_MODE();

    for(pData[0] = 0; pData[0] < 15; pData[0]++)
    {
        if(pData[0] < 5)
        {
            ScalerDpRx1SetDpcdValue(0x06, 0x80, (0x2C + pData[0]), g_pucHdcpAksvBackup[pData[0]]);
        }
        else
        {
            ScalerDpRx1SetDpcdValue(0x06, 0x80, (0x2C + pData[0]), 0x00);
        }
    }

    SET_DP_RX1_AUX_AUTO_MODE();

    // Write V' to DPCD table
    ScalerDpRx1HDCPLoadShaToDpcd();
}

//--------------------------------------------------
// Description  : Calculate SHA-1 Input
// Input Value  : Inpute Array, First Run
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1HDCPSha1Calculate(BYTE *pucInputArray, BYTE ucCalCount)
{
    // Reset SHA Block counter
    ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT3, _BIT3);

    // Start to Write SHA-1 Transform Input
    ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT3, 0x00);

    // Write SHA-1 Input Data, Total 512 bits
    for(pData[1] = 0; pData[1] < 16; pData[1]++)
    {
        ScalerSetByte(PB0_31_SHA_DATA1, pucInputArray[pData[1] * 4]);
        ScalerSetByte(PB0_32_SHA_DATA2, pucInputArray[1 + pData[1] * 4]);
        ScalerSetByte(PB0_33_SHA_DATA3, pucInputArray[2 + pData[1] * 4]);
        ScalerSetByte(PB0_34_SHA_DATA4, pucInputArray[3 + pData[1] * 4]);

        // Enable write 32-bit data to SHA-1 block
        ScalerSetBit(PB0_30_SHA_CONTRL, ~_BIT0, _BIT0);
    }

    ScalerDpRx1HDCPAuthShaRun(((ucCalCount == 0x00) ? _TRUE : _FALSE));
}

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)

#if(_HW_DP_VSC_SDP_REG_SUPPORT != _ON)
//--------------------------------------------------
// Description  : DP Rx1 MstToSst VSC Packet Detect Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1MstToSstRSV1PacketDetectEvent(void)
{
    CLR_DP_RX1_MST2SST_RSV1_DETECTING();
}
#endif // End of #if(_HW_DP_VSC_SDP_REG_SUPPORT != _ON)
#endif // End of #if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
#endif // End of #if(_DP_TX_SUPPORT == _ON)
#endif // End of #if(_DP_MST_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Check ScalerDpRx1ValidSignalDetection Process @ DC ON
// Input Value  : None
// Output Value : _TRUE -> Process / _FALSE -> Not Process
//--------------------------------------------------
bit ScalerDpRx1ValidSignalDetectionDCOnCheck(void)
{
    if((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_LINK_TRAINING_NONE) && (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00) == 0x00) && ((ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x11) & 0x03) != 0x03))
    {
        return _TRUE;
    }

    return _FALSE;
}

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Handle DP MST to SST Flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1MstToSstProc(void)
{
    if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_NONE)
    {
        if(ScalerDpRx1MstToSstScanInputPort() == _TRUE)
        {
            if(ScalerDpRx1MstToSstMeasureInput() == _TRUE)
            {
                ScalerDpTxSetStreamSource(_DP_TX_SOURCE_MST2SST);
            }
        }
    }
    else
    {
        // Stable Check
        if(ScalerDpRx1MstToSstStableDetect() == _FALSE)
        {
            ScalerDpTxSetStreamSource(_DP_TX_SOURCE_NONE);

            // Disabel MST2SST Watch Dog
            CLR_REG_DP_RX_MST2SST_WATCH_DOG_ENABLE();
        }
    }
}

//--------------------------------------------------
// Description  : DP MST2SST Set Color Info Macros
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1MstToSstSetColorInfo(void)
{
#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
    if(GET_DP_TX_VSC_SDP_COLOR_MODE() == _TRUE)
    {
        // Set Color Space Macro
        switch(g_stDpTxColorInfo.ucColorSpacePreValue)
        {
            case _VSC_COLOR_SPACE_0:
                SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_RGB);
                break;

            case _VSC_COLOR_SPACE_1:
                SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_YCBCR444);
                break;

            case _VSC_COLOR_SPACE_2:
                SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_YCBCR422);
                break;

            case _VSC_COLOR_SPACE_3:
                SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_YCBCR420);
                break;

            case _VSC_COLOR_SPACE_4:
                SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_Y_ONLY);
                break;

            case _VSC_COLOR_SPACE_5:
                SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_RAW);
                break;

            default:
                SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_RGB);
                break;
        }
    }
    else
#endif
    {
        // Set Color Space Macro
        switch(g_stDpTxColorInfo.ucColorSpacePreValue)
        {
            case _BIT1:
                SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_YCBCR422);
                break;

            case _BIT2:
                SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_YCBCR444);
                break;

            case _BIT7:
                SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_Y_ONLY);
                break;

            case (_BIT7 | _BIT1):
                SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_RAW);
                break;

            default:
                SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_RGB);
                break;
        }
    }

    // Set Porch Color
    if((GET_DP_TX_INPUT_COLOR_SPACE() == _COLOR_SPACE_YCBCR444) || (GET_DP_TX_INPUT_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) || (GET_DP_TX_INPUT_COLOR_SPACE() == _COLOR_SPACE_YCBCR420))
    {
        SET_DP_TX_PORCH_COLOR_YCC_FULL();
    }
    else
    {
        SET_DP_TX_PORCH_COLOR_RGB();
    }

    // Set Color Depth Macro
    SET_DP_TX_INPUT_COLOR_DEPTH(g_stDpTxColorInfo.b3ColorDepthPreValue);
}

//--------------------------------------------------
// Description  : On Line Check DP MST2SST stability
// Input Value  : None
// Output Value : True --> DP MST2SST Stable
//                False --> DP MST2SST Unstable
//--------------------------------------------------
bit ScalerDpRx1MstToSstStableDetect(void)
{
    if(ScalerDpRx1MstToSstMiscCheck() == _FALSE)
    {
        return _FALSE;
    }

    if(ScalerDpRx1MstToSstFifoCheck(_DP_FIFO_POLLING_CHECK) == _FALSE)
    {
        return _FALSE;
    }

    if(ScalerDpRx1MstToSstMSAActiveChange() == _TRUE)
    {
        return _FALSE;
    }

    if(ScalerDpRxMstToSstTxMeasureTimingChange() == _TRUE)
    {
        return _FALSE;
    }

    return _TRUE;
}
#endif
#endif // End of #if(_D1_DP_EXIST == _ON)
