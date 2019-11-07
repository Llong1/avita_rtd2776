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
// ID Code      : ScalerTMDSRx2.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_TMDSRX2__

#include "ScalerFunctionInclude.h"

#if(_D2_TMDS_SUPPORT == _ON)

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
StructTMDSCtrlInfo g_stTMDSRx2CtrlInfo;
WORD g_usTMDSRx2ClkCount;

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
BYTE g_ucTMDSRx2ClkMode = _TMDS_24BIT_PHY_SETTING;
#endif

#if(_D2_HDMI_SUPPORT == _ON)
BYTE g_ucTMDSRx2AviInfo;
#endif

EnumDisplayDataPath g_enumTMDSRx2IrqForceBackgrd;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerTMDSRx2DviVideoSetting(void);
void ScalerTMDSRx2SetPorchColor(EnumColorSpace enumColorFormat);

#if(_D2_HDMI_SUPPORT == _ON)

#if(_D2_INPUT_PORT_TYPE != _D2_DUAL_DVI_PORT)
bit ScalerTMDSRx2HdmiDeepColorProc(WORD usTmdsClkCnt);
bit ScalerTMDSRx2HdmiWaitDeepColorPllLock(void);
#endif

void ScalerTMDSRx2HdmiPacketDetect(bit bWait);
void ScalerTMDSRx2HdmiPacketDetectEvent(void);
BYTE ScalerTMDSRx2HdmiGetAVIInfo(EnumAviInfoContent enumContent);
bit ScalerTMDSRx2HdmiAviPixelRepInfoChanged(void);
BYTE ScalerTMDSRx2HdmiGetColorDepth(void);
void ScalerTMDSRx2HdmiWatchDog(BYTE ucWDType, bit bEnable);

#if(_HDMI_FREESYNC_SUPPORT == _ON)
BYTE ScalerTMDSRx2HdmiGetAmdSpdInfo(EnumAmdSpdInfoContent enumContent);
#endif

#if(_ULTRA_HDR_SUPPORT == _ON)
void ScalerTMDSRx2GetHDRData(BYTE *pucHDRData);
#endif
#endif

void ScalerTMDSRx2PowerOffProc(void);
void ScalerTMDSRx2FreqDetectDisable(void);
void ScalerTMDSRx2FirstActiveProc(BYTE ucSourceType);

#if(_D2_INPUT_PORT_TYPE != _D2_DUAL_DVI_PORT)

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
void ScalerTMDSRx2TMDSScanInitial(BYTE ucInputPort);
bit ScalerTMDSRx2TMDSPSPreDetect(BYTE ucInputPort);
bit ScalerTMDSRx2TMDSNormalPreDetect(BYTE ucInputPort);
#endif

bit ScalerTMDSRx2HdcpEnabled(void);
#endif

BYTE ScalerTMDSRx2TMDSVideoDetect(bit bWait);
void ScalerTMDSRx2TMDSVideoDetectEvent(void);

#if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)
void ScalerTMDSRx2DualDVIScanInitial(BYTE ucInputPort);
bit ScalerTMDSRx2DualDVIPSPreDetect(BYTE ucInputPort);
bit ScalerTMDSRx2DualDVINormalPreDetect(BYTE ucInputPort);
BYTE ScalerTMDSRx2DualDVIScanInputPort(BYTE ucInputType);
void ScalerTMDSRx2DualDVISwitch(bit bEnable);
bit ScalerTMDSRx2DualDVICheck(void);
#endif
bit ScalerTMDSRx2CheckCDRStable(WORD usClkCount);
BYTE ScalerTMDSRx2CheckCDRStable_EXINT0(WORD usClkCount);

#if(_D2_HDMI_SUPPORT == _ON)
void ScalerTMDSRx2HdmiAVMuteProc(void);
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_DUAL_DVI_PORT)
BYTE ScalerTMDSRx2FormatDetect(void);
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)
bit ScalerTMDSRx2GetDualDVIMode(void);
BYTE ScalerTMDSRx2GetDualDVIMode_EXINT0(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : TMDS Video Setting
// Input Value  : Source Type
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx2DviVideoSetting(void)
{
    // Manual Set Color Space and disable pixel repetition
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_51_PORT_PAGE71_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);

    // Disable Down Sampling
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_50_PORT_PAGE71_HDMI_VCR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Waiting for Down Sampling Effect
    ScalerTimerDelayXms(20);

    SET_COLOR_SPACE(_D2_INPUT_PORT, _COLOR_SPACE_RGB);
    SET_COLOR_RGB_QUANTIZATION_RANGE(_D2_INPUT_PORT, _RGB_QUANTIZATION_FULL_RANGE);

    ScalerTMDSRx2SetPorchColor(GET_COLOR_SPACE(_D2_INPUT_PORT));
}

//--------------------------------------------------
// Description  : Set Back Ground Color
// Input Value  : Current Color Space
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx2SetPorchColor(EnumColorSpace enumColorFormat)
{
    // Manual Set Background Color Enable
    ScalerSetBit(P71_B9_TMDS_OUT_CTRL, ~_BIT7, 0x00);

    if((enumColorFormat == _COLOR_SPACE_YCBCR444) || (enumColorFormat == _COLOR_SPACE_YCBCR422))
    {
        ScalerSetByte(P71_BA_TMDS_ROUT_HIGH_BYTE, 0x80);
        ScalerSetByte(P71_BB_TMDS_ROUT_LOW_BYTE, 0x00);
        ScalerSetByte(P71_BC_TMDS_GOUT_HIGH_BYTE, 0x0F);
        ScalerSetByte(P71_BD_TMDS_GOUT_LOW_BYTE, 0x00);
        ScalerSetByte(P71_BE_TMDS_BOUT_HIGH_BYTE, 0x80);
        ScalerSetByte(P71_BF_TMDS_BOUT_LOW_BYTE, 0x00);
    }
#if(_HDMI_2_0_YCBCR420_SUPPORT == _ON)
    else if(enumColorFormat == _COLOR_SPACE_YCBCR420)
    {
        ScalerSetByte(P71_BA_TMDS_ROUT_HIGH_BYTE, 0x10);
        ScalerSetByte(P71_BB_TMDS_ROUT_LOW_BYTE, 0x00);
        ScalerSetByte(P71_BC_TMDS_GOUT_HIGH_BYTE, 0x10);
        ScalerSetByte(P71_BD_TMDS_GOUT_LOW_BYTE, 0x00);
        ScalerSetByte(P71_BE_TMDS_BOUT_HIGH_BYTE, 0x80);
        ScalerSetByte(P71_BF_TMDS_BOUT_LOW_BYTE, 0x00);
    }
#endif
    else
    {
        ScalerSetByte(P71_BA_TMDS_ROUT_HIGH_BYTE, 0x00);
        ScalerSetByte(P71_BB_TMDS_ROUT_LOW_BYTE, 0x00);
        ScalerSetByte(P71_BC_TMDS_GOUT_HIGH_BYTE, 0x00);
        ScalerSetByte(P71_BD_TMDS_GOUT_LOW_BYTE, 0x00);
        ScalerSetByte(P71_BE_TMDS_BOUT_HIGH_BYTE, 0x00);
        ScalerSetByte(P71_BF_TMDS_BOUT_LOW_BYTE, 0x00);
    }
}

#if(_D2_HDMI_SUPPORT == _ON)

#if(_D2_INPUT_PORT_TYPE != _D2_DUAL_DVI_PORT)
//--------------------------------------------------
// Description  : HDMI Deep Color Proc
// Input Value  : void
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerTMDSRx2HdmiDeepColorProc(WORD usTmdsClkCnt)
{
    // Setting Deep Color PLL
    if(ScalerTMDSRx2HdmiSetDeepColorPll(usTmdsClkCnt, GET_COLOR_DEPTH(_D2_INPUT_PORT)) == _FALSE)
    {
        return _FALSE;
    }

    // Wait for Phase lock
    if(ScalerTMDSRx2HdmiWaitDeepColorPllLock() == _FALSE)
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Wait for Deep Color PLL Phase Lock
// Input Value  : None
// Output Value : _TRUE = > Phase Locked
//--------------------------------------------------
bit ScalerTMDSRx2HdmiWaitDeepColorPllLock(void)
{
    BYTE ucTemp = 0;

    do
    {
        ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_82_PORT_PAGE71_HDMI_DPC_SET2, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));

        // Delay for PLL Phase Lock
        ScalerTimerDelayXms(2);

        ucTemp++;
    }
    while((ScalerGetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_82_PORT_PAGE71_HDMI_DPC_SET2, _BIT1) != 0) && (ucTemp <= 15));

    if(ucTemp > 15)
    {
        return _FALSE;
    }

    return _TRUE;
}

#endif // End of #(_D2_INPUT_PORT_TYPE != _D2_DUAL_DVI_PORT)

//--------------------------------------------------
// Description  : Detect HDMI Info Frame
// Input Value  : bWait => Whether to wait then read
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx2HdmiPacketDetect(bit bWait)
{
    if(bWait == _WAIT)
    {
        // Polling 3 frame for detect Packet signals
        if(ScalerTimerPollingFlagProc(130, P71_CC_HDMI_GPVS, (_BIT6 | _BIT5), _TRUE) == _TRUE)
        {
            // Both GCP & AVI infoframe packet have been received
            if(ScalerGetBit(P71_CC_HDMI_GPVS, (_BIT6 | _BIT5)) == (_BIT6 | _BIT5))
            {
                SET_HDMI_RX2_GCP_RECEIVED();

                SET_HDMI_RX2_AVI_INFO_FRAME_RECEIVED();
            }
            // Only AVI infoframe packet have been received
            else if(ScalerGetBit(P71_CC_HDMI_GPVS, (_BIT6 | _BIT5)) == _BIT5)
            {
                SET_HDMI_RX2_AVI_INFO_FRAME_RECEIVED();

                // Polling more 1 frame to wait GCP packet for HW can't update bit 6 & bit 5 simultaneously
                if(ScalerTimerPollingFlagProc(45, P71_CC_HDMI_GPVS, _BIT6, _TRUE) == _TRUE)
                {
                    SET_HDMI_RX2_GCP_RECEIVED();
                }
                else
                {
                    CLR_HDMI_RX2_GCP_RECEIVED();
                }
            }
            // Only GCP Packet have been received
            else if(ScalerGetBit(P71_CC_HDMI_GPVS, (_BIT6 | _BIT5)) == _BIT6)
            {
                SET_HDMI_RX2_GCP_RECEIVED();

                // Polling more 1 frame to wait AVI infoframe packet for HW can't update bit 6 & bit 5 simultaneously
                if(ScalerTimerPollingFlagProc(45, P71_CC_HDMI_GPVS, _BIT5, _TRUE) == _TRUE)
                {
                    SET_HDMI_RX2_AVI_INFO_FRAME_RECEIVED();
                }
                else
                {
                    CLR_HDMI_RX2_AVI_INFO_FRAME_RECEIVED();
                }
            }
        }
        // Neither AVI infoframe nor GCP packet received
        else
        {
            CLR_HDMI_RX2_GCP_RECEIVED();

            CLR_HDMI_RX2_AVI_INFO_FRAME_RECEIVED();
        }

#if(_HDMI_FREESYNC_SUPPORT == _ON)
#if(_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE)
        // Polling 3 frame for detect Packet signals P71_CA_00[7]
        if((GET_HDMI_FREESYNC_VCP() == 0x01) && (ScalerTimerPollingDataBitFlagProc(130, P71_C9_HDMI_AP, _P71_CA_PT_00_PORT_PAGE71_HDMI_SCR, _BIT7, _TRUE) == _TRUE))
#else
        // Polling 3 frame for detect Packet signals P71_CA_00[7]
        if(ScalerTimerPollingDataBitFlagProc(130, P71_C9_HDMI_AP, _P71_CA_PT_00_PORT_PAGE71_HDMI_SCR, _BIT7, _TRUE) == _TRUE)
#endif
        {
            SET_TMDS_RX2_SPD_INFO_FRAME_RECEIVED();
        }
        else
        {
            CLR_TMDS_RX2_SPD_INFO_FRAME_RECEIVED();
        }
#endif

#if(_ULTRA_HDR_SUPPORT == _ON)
        // Polling 3 frame for detect Packet signals P71_CA_00[6]
        if(ScalerTimerPollingDataBitFlagProc(130, P71_C9_HDMI_AP, _P71_CA_PT_00_PORT_PAGE71_HDMI_SCR, _BIT6, _TRUE) == _TRUE)
        {
            SET_HDMI_RX2_HDR_INFO_FRAME_RECEIVED();
        }
        else
        {
            CLR_HDMI_RX2_HDR_INFO_FRAME_RECEIVED();
        }
#endif

        // Wait at least 3 frame for HW auto update color depth value
        ScalerTimerDelayXms(130);

        CLR_HDMI_RX2_PACKET_DETECTING();
    }
    else
    {
        if(ScalerGetBit(P71_CC_HDMI_GPVS, _BIT6) == _BIT6)
        {
            ScalerTMDSRx2HdmiWatchDog(_HDMI_AV_MUTE_WD, _ENABLE);

            SET_HDMI_RX2_GCP_RECEIVED();
        }
        else
        {
            ScalerTMDSRx2HdmiWatchDog(_HDMI_AV_MUTE_WD, _DISABLE);

            CLR_HDMI_RX2_GCP_RECEIVED();
        }

        if(ScalerGetBit(P71_CC_HDMI_GPVS, _BIT5) == _BIT5)
        {
            // Color Space Auto/ Pixel Repetition auto mode
            ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_51_PORT_PAGE71_HDMI_ACRCR, ~(_BIT6 | _BIT2), (_BIT6 | _BIT2));

            ScalerTMDSRx2HdmiWatchDog(_HDMI_AVI_INFO_VARIATION_WD, _ENABLE);

            SET_HDMI_RX2_AVI_INFO_FRAME_RECEIVED();
        }
        else
        {
            // Mannal Set Color Space and disable pixel  repetition
            ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_51_PORT_PAGE71_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);

            // Disable down sampling
            ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_50_PORT_PAGE71_HDMI_VCR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // Waiting for Down Sampling Effect
            ScalerTimerDelayXms(20);

            ScalerTMDSRx2HdmiWatchDog(_HDMI_AVI_INFO_VARIATION_WD, _DISABLE);

            CLR_HDMI_RX2_AVI_INFO_FRAME_RECEIVED();
        }

#if(_HDMI_FREESYNC_SUPPORT == _ON)
#if(_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE)
        if((GET_HDMI_FREESYNC_VCP() == 0x01) && (ScalerGetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_00_PORT_PAGE71_HDMI_SCR, _BIT7) == _BIT7))
#else
        if(ScalerGetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_00_PORT_PAGE71_HDMI_SCR, _BIT7) == _BIT7)
#endif
        {
            SET_TMDS_RX2_SPD_INFO_FRAME_RECEIVED();
        }
        else
        {
            CLR_TMDS_RX2_SPD_INFO_FRAME_RECEIVED();
        }
#endif

#if(_ULTRA_HDR_SUPPORT == _ON)
        if(ScalerGetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_00_PORT_PAGE71_HDMI_SCR, _BIT6) == _BIT6)
        {
            SET_HDMI_RX2_HDR_INFO_FRAME_RECEIVED();
        }
        else
        {
            CLR_HDMI_RX2_HDR_INFO_FRAME_RECEIVED();
        }
#endif

        // Clear Detection Flag
        ScalerSetBit(P71_CC_HDMI_GPVS, ~_BIT6, _BIT6);

        ScalerSetBit(P71_CC_HDMI_GPVS, ~_BIT5, _BIT5);

        ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_00_PORT_PAGE71_HDMI_SCR, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        SET_HDMI_RX2_PACKET_DETECTING();

        // Activate Packet Detection Event
        ScalerTimerActiveTimerEvent(SEC(0.13), _SCALER_TIMER_EVENT_RX2_TMDS_HDMI_PACKET_DETECT);
    }
}

//--------------------------------------------------
// Description  : HDMI Info Frame Packet Detect Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx2HdmiPacketDetectEvent(void)
{
    CLR_HDMI_RX2_PACKET_DETECTING();
}

//--------------------------------------------------
// Description  : Get HDMI AVI Info Contents
// Input Value  : Content of Interest
// Output Value : Content Value
//--------------------------------------------------
BYTE ScalerTMDSRx2HdmiGetAVIInfo(EnumAviInfoContent enumContent)
{
    if(GET_HDMI_RX2_AVI_INFO_FRAME_RECEIVED() == _TRUE)
    {
        switch(enumContent)
        {
            case _AVI_INFO_COLOR_SPACE:

                return (ScalerGetDataPortBit(P71_CD_HDMI_PSAP, 0x04, (_BIT6 | _BIT5)) >> 5);

            case _AVI_INFO_COLORIMETRY:

                return (ScalerGetDataPortBit(P71_CD_HDMI_PSAP, 0x05, (_BIT7 | _BIT6)) >> 6);

            case _AVI_INFO_EXTENDED_COLORIMETRY:

                return (ScalerGetDataPortBit(P71_CD_HDMI_PSAP, 0x06, (_BIT6 | _BIT5 | _BIT4)) >> 4);

            case _AVI_INFO_RGB_QUANTIZATION:

                return (ScalerGetDataPortBit(P71_CD_HDMI_PSAP, 0x06, (_BIT3 | _BIT2)) >> 2);

            case _AVI_INFO_YCC_QUANTIZATION:

                return (ScalerGetDataPortBit(P71_CD_HDMI_PSAP, 0x08, (_BIT7 | _BIT6)) >> 6);

            case _AVI_INFO_SCAN_INFO:

                return ScalerGetDataPortBit(P71_CD_HDMI_PSAP, 0x04, (_BIT1 | _BIT0));

            case _AVI_INFO_IT_CONTENT:

                return (ScalerGetDataPortBit(P71_CD_HDMI_PSAP, 0x06, _BIT7) >> 7);

            case _AVI_INFO_PIXEL_REPETITION:

                return (ScalerGetDataPortBit(P71_CD_HDMI_PSAP, 0x08, (_BIT3 | _BIT2 | _BIT1 | _BIT0)));

            case _AVI_INFO_AR:

                return (ScalerGetDataPortBit(P71_CD_HDMI_PSAP, 0x05, (_BIT5 | _BIT4)) >> 4);

            case _AVI_INFO_VIC:

                return (ScalerGetDataPortBit(P71_CD_HDMI_PSAP, 0x07, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)));

            default:

                break;
        }
    }

    return 0xFF;
}

//--------------------------------------------------
// Description  : Detect HDMI AVI pixel repetition
// Input Value  : None
// Output Value : _TRUE => Current Info is different from previous setting
//--------------------------------------------------
bit ScalerTMDSRx2HdmiAviPixelRepInfoChanged(void)
{
    // Check Tmds Pixel Repetition
    if(ScalerTMDSRx2HdmiGetAVIInfo(_AVI_INFO_PIXEL_REPETITION) != GET_TMDS_RX2_AVI_PIXEL_REPETITION())
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get Color Depth
// Input Value  : None
// Output Value : Received Color Depth
//--------------------------------------------------
BYTE ScalerTMDSRx2HdmiGetColorDepth(void)
{
    if(GET_COLOR_SPACE(_D2_INPUT_PORT) == _COLOR_SPACE_YCBCR422)
    {
        return _COLOR_DEPTH_12_BITS;
    }

    if(GET_HDMI_RX2_GCP_RECEIVED() == _TRUE)
    {
        if(ScalerGetBit(P71_B4_TMDS_DPC0, 0x07) == 0x05)
        {
            return _COLOR_DEPTH_10_BITS;
        }
        else if(ScalerGetBit(P71_B4_TMDS_DPC0, 0x07) == 0x06)
        {
            return _COLOR_DEPTH_12_BITS;
        }
        else if(ScalerGetBit(P71_B4_TMDS_DPC0, 0x07) == 0x07)
        {
            return _COLOR_DEPTH_16_BITS;
        }
    }

    return _COLOR_DEPTH_8_BITS;
}

//--------------------------------------------------
// Description  : Hdmi Enable Watch Dog
// Input Value  : ucWDType => Watch Dog type, bEnable => Enable watch dog flag
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx2HdmiWatchDog(BYTE ucWDType, bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        if((ucWDType & _HDMI_AVI_INFO_VARIATION_WD) == _HDMI_AVI_INFO_VARIATION_WD)
        {
            if(ScalerGetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_41_PORT_PAGE71_HDMI_VWDSR, _BIT0) == 0x00)
            {
                // Clear AVI Info Frame Variation flag
                ScalerSetBit(P71_CC_HDMI_GPVS, ~(_BIT6 | _BIT5 | _BIT0), _BIT0);

                if((GET_COLOR_SPACE(_D2_INPUT_PORT) == _COLOR_SPACE_YCBCR444) || (GET_COLOR_SPACE(_D2_INPUT_PORT) == _COLOR_SPACE_YCBCR422))
                {
                    // Enable Color Space/ Colorimetry Change Detection
                    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_45_PORT_PAGE71_HDMI_PVGCR0, ~(_BIT3 | _BIT0), (_BIT3 | _BIT0));
                }
                else
                {
                    // Enable Color Space Change Detection
                    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_45_PORT_PAGE71_HDMI_PVGCR0, ~(_BIT3 | _BIT0), _BIT0);
                }

                // Enable AVI Info Frame Variation Watch Dog
                ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_41_PORT_PAGE71_HDMI_VWDSR, ~_BIT0, _BIT0);
            }
        }

        if((ucWDType & _HDMI_AV_MUTE_WD) == _HDMI_AV_MUTE_WD)
        {
            if(ScalerGetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_31_PORT_PAGE71_HDMI_WDCR0, _BIT7) == 0x00)
            {
                // CLR AVMute Flag
                ScalerSetBit(P71_CB_HDMI_SR, ~_BIT7, _BIT7);

                // Enable AVMute WD
                ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_31_PORT_PAGE71_HDMI_WDCR0, ~_BIT7, _BIT7);
            }
        }
    }
    else
    {
        if((ucWDType & _HDMI_AVI_INFO_VARIATION_WD) == _HDMI_AVI_INFO_VARIATION_WD)
        {
            // Disable packet variation Watch Dog
            ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_41_PORT_PAGE71_HDMI_VWDSR, ~_BIT0, 0x00);

            ScalerSetDataPortByte(P71_C9_HDMI_AP, _P71_CA_PT_45_PORT_PAGE71_HDMI_PVGCR0, 0x00);

            ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_46_PORT_PAGE71_HDMI_PVGCR1, ~_BIT0, 0x00);
        }

        if((ucWDType & _HDMI_AV_MUTE_WD) == _HDMI_AV_MUTE_WD)
        {
            // Disable AV Mute Watch Dog
            ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_31_PORT_PAGE71_HDMI_WDCR0, ~_BIT7, 0x00);
        }
    }
}

#if(_HDMI_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get AMD SPD Info Contents
// Input Value  : Content of Interest
// Output Value : Content Value
//--------------------------------------------------
BYTE ScalerTMDSRx2HdmiGetAmdSpdInfo(EnumAmdSpdInfoContent enumContent)
{
    if(GET_TMDS_RX2_SPD_INFO_FRAME_RECEIVED() == _TRUE)
    {
        // Get AMD OUI
        ScalerGetDataPortByte(P71_CD_HDMI_PSAP, 0x90, 3, pData, _AUTOINC);
        if((pData[0] == 0x1A) && (pData[1] == 0x00) && (pData[2] == 0x00))
        {
            switch(enumContent)
            {
                case _SPD_INFO_FREESYNC_SUPPORT:

                    return ((bit)ScalerGetDataPortBit(P71_CD_HDMI_PSAP, 0x95, _BIT0));

                case _SPD_INFO_FREESYNC_ENABLE:

                    return ((bit)ScalerGetDataPortBit(P71_CD_HDMI_PSAP, 0x95, _BIT1));

                case _SPD_INFO_FREESYNC_ACTIVE:

                    return ((bit)ScalerGetDataPortBit(P71_CD_HDMI_PSAP, 0x95, _BIT2));

                case _SPD_INFO_FREESYNC_MIN_VFREQ:

                    ScalerGetDataPortByte(P71_CD_HDMI_PSAP, 0x96, 1, pData, _AUTOINC);

                    if(((WORD)pData[0] * 10) < _PANEL_FREESYNC_MIN_FRAME_RATE)
                    {
                        pData[0] = _PANEL_FREESYNC_MIN_FRAME_RATE / 10;
                        DebugMessageRx2("Freesync SPD info abnormal", 0);
                    }
                    else if(((WORD)pData[0] * 10) > _PANEL_FREESYNC_MAX_FRAME_RATE)
                    {
                        pData[0] = _PANEL_FREESYNC_MAX_FRAME_RATE / 10;
                        DebugMessageRx2("Freesync SPD info abnormal", 1);
                    }

                    return pData[0];

                case _SPD_INFO_FREESYNC_MAX_VFREQ:

                    ScalerGetDataPortByte(P71_CD_HDMI_PSAP, 0x97, 1, pData, _AUTOINC);

                    if(((WORD)pData[0] * 10) < _PANEL_FREESYNC_MIN_FRAME_RATE)
                    {
                        pData[0] = _PANEL_FREESYNC_MIN_FRAME_RATE / 10;
                        DebugMessageRx2("Freesync SPD info abnormal", 0);
                    }
                    else if(((WORD)pData[0] * 10) > _PANEL_FREESYNC_MAX_FRAME_RATE)
                    {
                        pData[0] = _PANEL_FREESYNC_MAX_FRAME_RATE / 10;
                        DebugMessageRx2("Freesync SPD info abnormal", 1);
                    }

                    return pData[0];

                default:

                    return 0x00;
            }
        }
    }

    return 0x00;
}
#endif // End of #if(_HDMI_FREESYNC_SUPPORT == _ON)

#if(_ULTRA_HDR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get TMDS HDR Data
// Input Value  : pucHDRData --> HDR data
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx2GetHDRData(BYTE *pucHDRData)
{
    ScalerGetDataPortByte(P71_CD_HDMI_PSAP, _HDR_INFO_HDMI_VERSION, 2, &pucHDRData[0], _AUTOINC);
    ScalerGetDataPortByte(P71_CD_HDMI_PSAP, _HDR_INFO_HDMI_EOTF, 2, &pucHDRData[2], _AUTOINC);
    ScalerGetDataPortByte(P71_CD_HDMI_PSAP, _HDR_INFO_HDMI_DISPLAY_PRIMARIES_X0_LSB, 24, &pucHDRData[4], _AUTOINC);
}
#endif // End of #if(_ULTRA_HDR_SUPPORT == _ON)
#endif // End of #if(_D2_HDMI_SUPPORT == _ON)

//--------------------------------------------------
// Description  : TMDS Power Off Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx2PowerOffProc(void)
{
    // Disable EDID read/ SCL toggle IRQ
    MCU_FE69_DDC2_EDID_IRQ = ((MCU_FE69_DDC2_EDID_IRQ & ~(_BIT3 | _BIT1)) | (_BIT2 | _BIT0));

    ScalerTMDSRx2FreqDetectDisable();
}

//--------------------------------------------------
// Description  : TMDS Freq. Detection IRQ Disable and Clear Clock Counter
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx2FreqDetectDisable(void)
{
    // Disable TMDS Freq. Detect IRQ
    ScalerSetBit(P71_E6_HDMI_FREQDET_CTRL, ~_BIT1, 0x00);
    ScalerSetBit(P71_EF_HDMI_ERROR_TH, ~_BIT7, 0x00);

    // Clear TMDS Clk Count
    g_usTMDSRx2ClkCount = 0;

#if(_D2_HDMI_2_0_SUPPORT == _ON)
    // Disable CED Function
    ScalerSetBit(P71_0B_HDMI_CTRL_0B, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);

    // Pop Up CED Error For Clear Error Counter
    ScalerSetBit(P71_0C_HDMI_CTRL_0C, ~_BIT7, _BIT7);

    // Disable CED Lock Transition IRQ & Flag
    ScalerSetBit(P71_17_HDMI_CTRL_17, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P71_18_HDMI_CTRL_18, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
#endif
}

//--------------------------------------------------
// Description  : Process Required when Switched to Active State
// Input Value  : Input Source
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx2FirstActiveProc(BYTE ucSourceType)
{
    ucSourceType = ucSourceType;
}

#if(_D2_INPUT_PORT_TYPE != _D2_DUAL_DVI_PORT)
//--------------------------------------------------
// Description  : Initial Setting for TMDS Scanning Port(Power Normal)
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx2TMDSScanInitial(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

    // Set Power Saving DDC Debounce Counter
    g_usDDCDebounceCnt = _TMDS_DDC_DEBOUNCE_NORMAL;

    ScalerTMDSRx2Initial(ucInputPort);

    ScalerTMDSRx2InterruptInitial();
}

//--------------------------------------------------
// Description  : Signal Detection for TMDS(Power Saving)
// Input Value  : Input Port
// Output Value : True : TMDS Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerTMDSRx2TMDSPSPreDetect(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

    // DDC handshake Detected
    if(GET_TMDS_RX2_DDC_DETECTED() == _TRUE)
    {
        DebugMessageRx2("7. PowerSaving D2 DDC", 0);

        CLR_TMDS_RX2_DDC_DETECTED();

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
        SET_TMDS_RX2_TOGGLE_Z0();
#endif
        return _TRUE;
    }

    // Enable DDC Toggle IRQ
    if(((MCU_FE69_DDC2_EDID_IRQ & _BIT3) != _BIT3) && (GET_TMDS_RX2_DDC_DETECTED() != _TRUE))
    {
        MCU_FE69_DDC2_EDID_IRQ |= _BIT2;
        MCU_FE69_DDC2_EDID_IRQ |= _BIT3;
    }

    // Reset Freq. Detect Counter(Toggle) & Choose Measure Clk to TMDS Clk
    ScalerSetBit(P71_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT5 | _BIT4), 0x00);
    ScalerSetBit(P71_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);

    // Clear Freq. Stable Flag
    ScalerSetBit(P71_EF_HDMI_ERROR_TH, ~_BIT6, _BIT6);

    // Clear Unstable Flag
    ScalerSetBit(P71_E6_HDMI_FREQDET_CTRL, ~_BIT2, _BIT2);

    // Delay enough time for freq. measure (calculated for measure 5 times)
    ScalerTimerDelayXms(5);

    // Detect Freq. Measure Stable
    if((ScalerGetBit(P71_E6_HDMI_FREQDET_CTRL, (_BIT6 | _BIT2)) == _BIT6) && (ScalerGetBit(P71_EF_HDMI_ERROR_TH, _BIT6) == _BIT6))
    {
#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
        SET_TMDS_RX2_TOGGLE_Z0();
#endif
        return _TRUE;
    }
    else
    {
        // Disable Freq. Detection
        ScalerSetBit(P71_E6_HDMI_FREQDET_CTRL, ~_BIT7, 0x00);

        return _FALSE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Signal PreDetection for TMDS(Power Normal)
// Input Value  : Input Port
// Output Value : True : TMDS Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerTMDSRx2TMDSNormalPreDetect(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

    // DDC handshake Detected
    if(GET_TMDS_RX2_DDC_DETECTED() == _TRUE)
    {
        DebugMessageRx2("7. Normal D2 DDC", 0);

        CLR_TMDS_RX2_DDC_DETECTED();

        return _TRUE;
    }

    // Enable DDC Toggle IRQ
    if(((MCU_FE69_DDC2_EDID_IRQ & _BIT3) != _BIT3) && (GET_TMDS_RX2_DDC_DETECTED() != _TRUE))
    {
        MCU_FE69_DDC2_EDID_IRQ |= _BIT2;
        MCU_FE69_DDC2_EDID_IRQ |= _BIT3;

        CLR_TMDS_RX2_DDC_DETECTED();
    }

    ScalerTimerDelayXms(6);

    if(GET_TMDS_RX2_PHY_SET() == _TRUE)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check whether HDCP is enabled
// Input Value  : None
// Output Value : TRUE => HDCP Enabled
//--------------------------------------------------
bit ScalerTMDSRx2HdcpEnabled(void)
{
    BYTE pucHDCPFrameCount[2];
    memset(pucHDCPFrameCount, 0, sizeof(pucHDCPFrameCount));

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
    if((ScalerGetBit(P71_C0_HDCP_CR, _BIT0) == _BIT0) && (ScalerGetBit(P2D_26_HDCP_I2C_CTRL_0, _BIT7) == 0x00))
#endif
    {
        ScalerGetDataPortByte(P71_C3_HDCP_AP, _P71_C4_PT_C0_PORT_PAGE71_HDCP_FCR, 1, &pucHDCPFrameCount[0], _NON_AUTOINC);

        // Wait 2Vsync to make sure frame counter changing, and timeout 45ms (margin + 1/24 frame+rate)
        ScalerSetBit(P71_A4_TMDS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT3);
        ScalerTimerPollingFlagProc(45, P71_A4_TMDS_CTRL, _BIT3, _TRUE);
        ScalerSetBit(P71_A4_TMDS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT3);
        ScalerTimerPollingFlagProc(45, P71_A4_TMDS_CTRL, _BIT3, _TRUE);

        ScalerGetDataPortByte(P71_C3_HDCP_AP, _P71_C4_PT_C0_PORT_PAGE71_HDCP_FCR, 1, &pucHDCPFrameCount[1], _NON_AUTOINC);

        if(pucHDCPFrameCount[0] != pucHDCPFrameCount[1])
        {
            return _TRUE;
        }

        return _FALSE;
    }
#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
    else if((ScalerGetBit(P71_C0_HDCP_CR, _BIT0) == 0x00) && (ScalerGetBit(P2D_26_HDCP_I2C_CTRL_0, _BIT7) == _BIT7))
    {
        if(ScalerGetByte(P2D_2C_HDCP_I2C_CTRL_6) == 0x10)
        {
            return _TRUE;
        }
        else
        {
            return _FALSE;
        }
    }
    else
    {
        return _FALSE;
    }
#endif
}

#endif // End of #if(_D2_INPUT_PORT_TYPE != _D2_DUAL_DVI_PORT)

//--------------------------------------------------
// Description  : Detect TMDS video mode
// Input Value  : bWait => Whether to wait then read
// Output Value : TMDS video type
//--------------------------------------------------
BYTE ScalerTMDSRx2TMDSVideoDetect(bit bWait)
{
    BYTE ucTemp = _TMDS_VIDEO_DATA_NONE;

    if(bWait == _WAIT)
    {
        // Wait at least 1 frame for HW auto update TMDS video RGBHV valid value
        ScalerTimerPollingFlagProc(45, P71_A4_TMDS_CTRL, _BIT3, _TRUE);

        // Wait for HW update DE flag
        if(ScalerTimerPollingFlagProc(20, P71_A4_TMDS_CTRL, (_BIT7 | _BIT6 | _BIT5), _TRUE) == _TRUE)
        {
            // H/Vsync received
            if(ScalerGetBit(P71_A4_TMDS_CTRL, (_BIT4 | _BIT3)) == (_BIT4 | _BIT3))
            {
                ucTemp = _TMDS_VIDEO_DATA_RGBHV;
            }
            else
            {
                ucTemp = _TMDS_VIDEO_DATA_DE_ONLY;
            }
        }
        else
        {
            ucTemp = _TMDS_VIDEO_DATA_NONE;
        }

        CLR_TMDS_RX2_RGBHV_DETECTING();

        return ucTemp;
    }
    else
    {
        // R/G/B data detected
        if(ScalerGetBit(P71_A4_TMDS_CTRL, (_BIT7 | _BIT6 | _BIT5)) == (_BIT7 | _BIT6 | _BIT5))
        {
            // H/Vsync received
            if(ScalerGetBit(P71_A4_TMDS_CTRL, (_BIT4 | _BIT3)) == (_BIT4 | _BIT3))
            {
                ucTemp = _TMDS_VIDEO_DATA_RGBHV;
            }
            else
            {
                ucTemp = _TMDS_VIDEO_DATA_DE_ONLY;
            }
        }
        else
        {
            ucTemp = _TMDS_VIDEO_DATA_NONE;
        }

        // Clear video Detection Flag
        ScalerSetBit(P71_A4_TMDS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));

        SET_TMDS_RX2_RGBHV_DETECTING();

        // Activate TMDS video Detection Event
        ScalerTimerActiveTimerEvent(SEC(0.045), _SCALER_TIMER_EVENT_RX2_TMDS_VIDEO_DETECT);

        return ucTemp;
    }
}

//--------------------------------------------------
// Description  : TMDS video Detect Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx2TMDSVideoDetectEvent(void)
{
    CLR_TMDS_RX2_RGBHV_DETECTING();
}

#if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)
//--------------------------------------------------
// Description  : Initial Setting for Dual DVI Scanning Port(Power Normal)
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx2DualDVIScanInitial(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

    // Both Initial D2 Port & D3 Port TMDS
    ScalerTMDSRx2Initial(ucInputPort);
    ScalerTMDSRx3Initial(ucInputPort);

    // Both Initial D2 Port & D3 Port Interrupt Initial
    ScalerTMDSRx2InterruptInitial();
    ScalerTMDSRx3InterruptInitial();
}

//--------------------------------------------------
// Description  : Signal Detection for Dual DVI(Power Saving)
// Input Value  : Input Port
// Output Value : True : TMDS Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerTMDSRx2DualDVIPSPreDetect(BYTE ucInputPort)
{
    BYTE ucTemp = 0;

    ucInputPort = ucInputPort;

    // DDC handshake Detected
    if(GET_TMDS_RX2_DDC_DETECTED() == _TRUE)
    {
        DebugMessageRx2("7. PowerSaving D2 DDC", 0);

        CLR_TMDS_RX2_DDC_DETECTED();

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
        SET_TMDS_RX2_TOGGLE_Z0();
#endif
        return _TRUE;
    }

    // Enable DDC Toggle IRQ
    if(((MCU_FE69_DDC2_EDID_IRQ & _BIT3) != _BIT3) && (GET_TMDS_RX2_DDC_DETECTED() != _TRUE))
    {
        MCU_FE69_DDC2_EDID_IRQ |= _BIT2;
        MCU_FE69_DDC2_EDID_IRQ |= _BIT3;
    }

    // Reset Freq. Detect Counter & Choose Measure Clk to TMDS Clk
    ScalerSetBit(P71_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT5 | _BIT4), 0x00);
    ScalerSetBit(P71_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);

    // Clear D2 Port Freq. Stable Flag
    ScalerSetBit(P71_EF_HDMI_ERROR_TH, ~_BIT6, _BIT6);

    // Clear D2 Port Unstable Flag
    ScalerSetBit(P71_E6_HDMI_FREQDET_CTRL, ~_BIT2, _BIT2);

    // Delay enough time for freq. measure (calculated for measure 10 times)
    ScalerTimerDelayXms(5);

    // Detect Freq. Measure Stable
    if((ScalerGetBit(P71_E6_HDMI_FREQDET_CTRL, (_BIT6 | _BIT2)) == _BIT6) && (ScalerGetBit(P71_EF_HDMI_ERROR_TH, _BIT6) == _BIT6))
    {
#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
        SET_TMDS_RX2_TOGGLE_Z0();
#endif
        return _TRUE;
    }
    else
    {
        // Disable Freq. Detection
        ScalerSetBit(P71_E6_HDMI_FREQDET_CTRL, ~_BIT7, 0x00);

        return _FALSE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Signal PreDetection for Dual DVI(Power Normal)
// Input Value  : Input Port
// Output Value : True : TMDS Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerTMDSRx2DualDVINormalPreDetect(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

    // DDC handshake Detected
    if(GET_TMDS_RX2_DDC_DETECTED() == _TRUE)
    {
        DebugMessageRx2("7. Normal D2 DDC", 0);

        CLR_TMDS_RX2_DDC_DETECTED();

        return _TRUE;
    }

    // Enable DDC Toggle IRQ
    if(((MCU_FE69_DDC2_EDID_IRQ & _BIT3) != _BIT3) && (GET_TMDS_RX2_DDC_DETECTED() != _TRUE))
    {
        MCU_FE69_DDC2_EDID_IRQ |= _BIT2;
        MCU_FE69_DDC2_EDID_IRQ |= _BIT3;
    }

    ScalerTimerDelayXms(6);

    if((GET_TMDS_RX2_PHY_SET() == _TRUE) && (GET_TMDS_RX3_PHY_SET() == _TRUE))
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : TMDS Port Source/Sync Scanning and Setting
// Input Value  : Input Port
// Output Value : Source DVI --> DVI Format
//                Source HDMI --> HDMI Format
//                Source DUAL_DVI --- > DUAL DVI Format
//                Source None --> No Stable Sync
//--------------------------------------------------
BYTE ScalerTMDSRx2DualDVIScanInputPort(BYTE ucInputType)
{
    bit bDualDviMode = _FALSE;

    ucInputType = ucInputType;

    if((GET_TMDS_RX2_PHY_SET() == _TRUE) && (GET_TMDS_RX3_PHY_SET() == _TRUE))
    {
        BYTE ucTMDSType = _SOURCE_NONE;

        BYTE ucTMDSRx2VideoDataType = _TMDS_VIDEO_DATA_NONE;
        BYTE ucTMDSRx3VideoDataType = _TMDS_VIDEO_DATA_NONE;

        // Delay for PHY Stable
        ScalerTimerDelayXms(2);

        ucTMDSRx2VideoDataType = ScalerTMDSRx2TMDSVideoDetect(_WAIT);

        if((ucTMDSRx2VideoDataType != _TMDS_VIDEO_DATA_NONE) && (ScalerTMDSRx2DualDVICheck() == _TRUE))
        {
            if((ScalerTMDSRx2CheckCDRStable(g_usTMDSRx2ClkCount) == _FALSE) || (ScalerTMDSRx3CheckCDRStable(g_usTMDSRx3ClkCount) == _FALSE))
            {
                //-------- Set Port2 Stable Bound Start ----//
#if(_TMDS_LOW_SPEED_PORT_SPEED_LIMIT == _OFF)
                // Set Upper Bound
                ScalerSetByte(P71_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
                ScalerSetByte(P71_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
#else
                ScalerSetByte(P71_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
                ScalerSetByte(P71_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
#endif
                // Set Lower Bound
                ScalerSetByte(P71_EA_HDMI_FREQDET_LOWER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));
                ScalerSetByte(P71_EB_HDMI_FREQDET_LOWER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));

                // Set Stable Time (0x7F = about 5ms)
                ScalerSetByte(P71_EC_HDMI_FREQDET_STABLE, 0x7F);
                //-------- Set Port2 Stable Bound End ----//

                //-------- Set Port3 Stable Bound Start ----//
#if(_TMDS_LOW_SPEED_PORT_SPEED_LIMIT == _OFF)
                // Set Upper Bound
                ScalerSetByte(P72_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
                ScalerSetByte(P72_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
#else
                ScalerSetByte(P72_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
                ScalerSetByte(P72_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
#endif
                // Set Lower Bound
                ScalerSetByte(P72_EA_HDMI_FREQDET_LOWER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));
                ScalerSetByte(P72_EB_HDMI_FREQDET_LOWER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));

                // Set Stable Time (0x7F = about 5ms)
                ScalerSetByte(P72_EC_HDMI_FREQDET_STABLE, 0x7F);
                //-------- Set Port3 Stable Bound End ----//

                CLR_TMDS_RX2_PHY_SET();
                CLR_TMDS_RX3_PHY_SET();

                // Disable port2 Freq. Unstable IRQ
                ScalerSetBit(P71_E6_HDMI_FREQDET_CTRL, ~_BIT1, 0x00);

                // Reset Freq. Detect Counter
                ScalerSetBit(P71_E6_HDMI_FREQDET_CTRL, ~_BIT7, 0x00);
                ScalerSetBit(P71_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);

                // Enable Port2 Freq. Stable IRQ
                ScalerSetBit(P71_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

                // Disable Port3 Freq. Unstable IRQ
                ScalerSetBit(P72_E6_HDMI_FREQDET_CTRL, ~_BIT1, 0x00);

                // Reset Freq. Detect Counter
                ScalerSetBit(P72_E6_HDMI_FREQDET_CTRL, ~_BIT7, 0x00);
                ScalerSetBit(P72_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);

                // Enable Port3 Freq. Stable IRQ
                ScalerSetBit(P72_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

                return _SOURCE_NONE;
            }

            bDualDviMode = _TRUE;
        }
        else
        {
            if(ScalerTMDSRx3CheckCDRStable(g_usTMDSRx3ClkCount) == _FALSE)
            {
                //-------- Set Port3 Stable Bound Start ----//
#if(_TMDS_LOW_SPEED_PORT_SPEED_LIMIT == _OFF)
                // Set Upper Bound
                ScalerSetByte(P72_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
                ScalerSetByte(P72_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
#else
                ScalerSetByte(P72_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
                ScalerSetByte(P72_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
#endif
                // Set Lower Bound
                ScalerSetByte(P72_EA_HDMI_FREQDET_LOWER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));
                ScalerSetByte(P72_EB_HDMI_FREQDET_LOWER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));

                // Set Stable Time (0x7F = about 5ms)
                ScalerSetByte(P72_EC_HDMI_FREQDET_STABLE, 0x7F);
                //-------- Set Port3 Stable Bound End ----//

                CLR_TMDS_RX3_PHY_SET();

                // Disable Port3 Freq. Unstable IRQ
                ScalerSetBit(P72_E6_HDMI_FREQDET_CTRL, ~_BIT1, 0x00);

                // Reset Freq. Detect Counter
                ScalerSetBit(P72_E6_HDMI_FREQDET_CTRL, ~_BIT7, 0x00);
                ScalerSetBit(P72_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);

                // Enable Port3 Freq. Stable IRQ
                ScalerSetBit(P72_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

                return _SOURCE_NONE;
            }

            bDualDviMode = _FALSE;
        }

        DebugMessageRx2("9. Freq Check Pass => Pixel Clock", GET_D2_INPUT_PIXEL_CLK());

        // Clear Port2 RGBHV Flag
        ScalerSetBit(P71_A4_TMDS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));

        // Clear port2 Info Packet SRAM
        ScalerSetBit(P71_AD_TMDS_CPS, ~_BIT3, _BIT3);
        ScalerSetBit(P71_AD_TMDS_CPS, ~_BIT3, 0x00);

        // Clear Port2 AVI infoframe & GCP packet Detection Flag
        ScalerSetBit(P71_CC_HDMI_GPVS, ~_BIT6, _BIT6);
        ScalerSetBit(P71_CC_HDMI_GPVS, ~_BIT5, _BIT5);

        // Clear Port3 RGBHV Flag
        ScalerSetBit(P72_A4_TMDS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));

        // Clear Port3 Info Packet SRAM
        ScalerSetBit(P72_AD_TMDS_CPS, ~_BIT3, _BIT3);
        ScalerSetBit(P72_AD_TMDS_CPS, ~_BIT3, 0x00);

        // Clear Port3 AVI infoframe & GCP packet Detection Flag
        ScalerSetBit(P72_CC_HDMI_GPVS, ~_BIT6, _BIT6);
        ScalerSetBit(P72_CC_HDMI_GPVS, ~_BIT5, _BIT5);

        // Reset

        if(ScalerTMDSRx3FormatDetect() == _SOURCE_HDMI)
        {
            DebugMessageRx2("Format Detect HDMI", 0x00);

            ScalerSetDataPortBit(P72_C3_HDCP_AP, _P72_C4_PT_40_PORT_PAGE72_BCAPS, ~_BIT1, _BIT1);

#if(_HDMI_FROM_DVI_CONNECT == _OFF)
            return _SOURCE_NONE;
#endif

            ucTMDSRx3VideoDataType = ScalerTMDSRx3TMDSVideoDetect(_WAIT);

            if(ucTMDSRx3VideoDataType == _TMDS_VIDEO_DATA_DE_ONLY)
            {
                DebugMessageRx2("DE Only Mode", 0x00);

                return _SOURCE_NONE;
            }
            else if(ucTMDSRx3VideoDataType == _TMDS_VIDEO_DATA_RGBHV)
            {
                // Enable DE Only Mode
                ScalerSetBit(P72_A7_TMDS_PWDCTL, ~_BIT7, _BIT7);
            }
            else
            {
                return _SOURCE_NONE;
            }

            ucTMDSType = _SOURCE_HDMI;
        }
        else
        {
            ScalerSetDataPortBit(P71_C3_HDCP_AP, _P71_C4_PT_40_PORT_PAGE71_BCAPS, ~_BIT1, 0x00);
            ScalerSetDataPortBit(P72_C3_HDCP_AP, _P72_C4_PT_40_PORT_PAGE72_BCAPS, ~_BIT1, 0x00);

            ScalerSetBit(P71_AF_TMDS_WDC, ~_BIT0, _BIT0);

            if(GET_D2_TMDS_MODE() == _TMDS_HDMI_MODE)
            {
#if(_D2_HDMI_2_0_SUPPORT == _ON)
                if(ScalerGetBit(P71_00_HDMI_CTRL_00, _BIT0) == _BIT0)
                {
                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX2_HDMI2_FORMAT_RESET_WAIT);
                }
#endif
                // Set Format Detect HW Auto Mode
                ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_00_PORT_PAGE71_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), 0x00);
            }
#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
            else
            {
                // Manual Set to DVI Mode
                ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_00_PORT_PAGE71_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), _BIT3);
            }
#endif

            ucTMDSRx2VideoDataType = ScalerTMDSRx2TMDSVideoDetect(_NOT_WAIT);
            ucTMDSRx3VideoDataType = ScalerTMDSRx3TMDSVideoDetect(_NOT_WAIT);

            DebugMessageRx2("D2 Video Detect", ucTMDSRx2VideoDataType);
            DebugMessageRx2("D3 Video Detect", ucTMDSRx3VideoDataType);

            if(ucTMDSRx3VideoDataType == _TMDS_VIDEO_DATA_DE_ONLY)
            {
                DebugMessageRx2("DE Only Mode", 0x00);

#if(_DVI_DE_ONLY_SUPPORT == _ON)
                // Enable D2 DE Only Mode
                ScalerSetBit(P72_A7_TMDS_PWDCTL, ~_BIT7, _BIT7);

                if(bDualDviMode == _TRUE)
                {
                    // Enable DE Only Mode
                    ScalerSetBit(P71_A7_TMDS_PWDCTL, ~_BIT7, _BIT7);
                }

                ucTMDSType = _SOURCE_DVI;
#else
                return _SOURCE_NONE;
#endif
            }
            else if(ucTMDSRx3VideoDataType == _TMDS_VIDEO_DATA_RGBHV)
            {
                // Enable DE Only Mode
                ScalerSetBit(P72_A7_TMDS_PWDCTL, ~_BIT7, _BIT7);

                if(bDualDviMode == _TRUE)
                {
                    // Enable DE Only Mode
                    ScalerSetBit(P71_A7_TMDS_PWDCTL, ~_BIT7, _BIT7);
                }

                ucTMDSType = _SOURCE_DVI;
            }
            else
            {
                return _SOURCE_NONE;
            }
        }

        DebugMessageRx2("Source Type", ucTMDSType);

        // [1] De_inverse = 1'b1 --> Adapation Only for Data Area (Transition Minimum)
        // [0] De_brank_en = 1'b1 --> Enable Blank Function of gdi_de
        if(bDualDviMode == _TRUE)
        {
            ScalerSetBit(P7B_AF_L0_GDI_DE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit(P7B_BF_L1_GDI_DE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit(P7B_CF_L2_GDI_DE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        }

        ScalerSetBit(P7C_AF_L0_GDI_DE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit(P7C_BF_L1_GDI_DE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit(P7C_CF_L2_GDI_DE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

#if(_D3_HDMI_SUPPORT == _ON)
        if(ucTMDSType == _SOURCE_HDMI)
        {
            // HDMI packet detect --> AVI infoframe & GCP packet
            ScalerTMDSRx3HdmiPacketDetect(_WAIT);

            ScalerSyncTMDSRx3HdmiVideoSetting();

            SET_COLOR_DEPTH(_D2_INPUT_PORT, ScalerTMDSRx3HdmiGetColorDepth());

            if((GET_COLOR_DEPTH(_D2_INPUT_PORT) != _COLOR_DEPTH_8_BITS) && (GET_COLOR_SPACE(_D2_INPUT_PORT) != _COLOR_SPACE_YCBCR422))
            {
                DebugMessageRx2("Deep Color Mode Detected", GET_COLOR_DEPTH(_D2_INPUT_PORT));

                SET_D2_INPUT_PIXEL_CLK((GET_D2_INPUT_PIXEL_CLK() << 3) / GET_COLOR_DEPTH(_D2_INPUT_PORT));

                if(ScalerTMDSRx3HdmiDeepColorProc(g_usTMDSRx3ClkCount) == _FALSE)
                {
                    return _SOURCE_NONE;
                }

                // Turn On Deep Color Block
                ScalerSetBit(P72_B5_TMDS_UDC0, ~_BIT7, _BIT7);
            }
            else
            {
                // Turn off Deep Color Block
                ScalerSetBit(P72_B5_TMDS_UDC0, ~_BIT7, 0x00);
            }
        }
        else
        {
            CLR_HDMI_RX2_AVI_INFO_FRAME_RECEIVED();
            CLR_HDMI_RX3_AVI_INFO_FRAME_RECEIVED();

            CLR_HDMI_RX2_GCP_RECEIVED();
            CLR_HDMI_RX3_GCP_RECEIVED();

            // Disable D2 Port All WD when DVI
            ScalerTMDSRx2HdmiWatchDog((_HDMI_AVI_INFO_VARIATION_WD | _HDMI_AV_MUTE_WD), _DISABLE);

            // Disable D3 Port All WD when DVI
            ScalerTMDSRx3HdmiWatchDog((_HDMI_AVI_INFO_VARIATION_WD | _HDMI_AV_MUTE_WD), _DISABLE);

            // D2 Port DVI Setting
            ScalerTMDSRx2DviVideoSetting();

            // D3 Port DVI Setting
            ScalerTMDSRx3DviVideoSetting();

            SET_COLOR_DEPTH(_D2_INPUT_PORT, _COLOR_DEPTH_8_BITS);

            // Turn off D2 Port Deep Color Block
            ScalerSetBit(P71_B5_TMDS_UDC0, ~_BIT7, 0x00);

            // Turn off D3 Port Deep Color Block
            ScalerSetBit(P72_B5_TMDS_UDC0, ~_BIT7, 0x00);
        }
#else

        ScalerTMDSRx3DviVideoSetting();

        SET_COLOR_DEPTH(_D2_INPUT_PORT, _COLOR_DEPTH_8_BITS);

        // Turn off Deep Color Block
        ScalerSetBit(P72_B5_TMDS_UDC0, ~_BIT7, 0x00);
#endif

        if(bDualDviMode == _TRUE)
        {
            ScalerTMDSRx2DualDVISwitch(_ENABLE);
        }
        else
        {
            ScalerTMDSRx2DualDVISwitch(_DISABLE);
        }

        return ucTMDSType;
    }

    return _SOURCE_NONE;
}

//--------------------------------------------------
// Description  : Switch Dual DVI
// Input Value  : _Enable/ Disable
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx2DualDVISwitch(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Disable D2 Port All WD when DVI
        ScalerTMDSRx2DviVideoSetting();

        // Turn off D2 Port Deep Color Block
        ScalerSetBit(P71_B5_TMDS_UDC0, ~_BIT7, 0x00);

        // Reset Dual DVI FIFO
        ScalerSetBit(P31_03_FC_DUAL_DVI_CTRL1, ~_BIT2, _BIT2);

        ScalerSetBit(P31_03_FC_DUAL_DVI_CTRL1, ~_BIT2, 0x00);

        // Enable Dual DVI FIFO
        ScalerSetBit(P31_04_FC_DUAL_DVI_CTRL2, ~(_BIT7 | _BIT5), (_BIT7 | _BIT5));

        // Enable Dual DVI Output from D2 + D3 Port
        switch(ScalerGetBit(P31_03_FC_DUAL_DVI_CTRL1, (_BIT7 | _BIT6 | _BIT5)))
        {
#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
            case (_BIT7 | _BIT6 | _BIT5):
            case (_BIT7 | _BIT6):
                ScalerSetBit(P31_03_FC_DUAL_DVI_CTRL1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
                break;
#endif
            default:
                ScalerSetBit(P31_03_FC_DUAL_DVI_CTRL1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT4));
                break;
        }

        // Enable Video Output
        ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_30_PORT_PAGE71_HDMI_AVMCR, ~_BIT3, _BIT3);
        ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_80_PORT_PAGE71_HDMI_DPC_SET0, ~_BIT7, _BIT7);

        // Enable RGB Clk Output
        ScalerSetBit(P71_A6_TMDS_OUTCTL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT5 | _BIT4 | _BIT3));

        // Enable Video Output
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_30_PORT_PAGE72_HDMI_AVMCR, ~_BIT3, _BIT3);
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_80_PORT_PAGE72_HDMI_DPC_SET0, ~_BIT7, _BIT7);

        // Enable RGB Clk Output
        ScalerSetBit(P72_A6_TMDS_OUTCTL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT5 | _BIT4 | _BIT3));
    }
    else
    {
        // Reset Dual DVI FIFO
        ScalerSetBit(P31_03_FC_DUAL_DVI_CTRL1, ~_BIT2, _BIT2);

        ScalerSetBit(P31_03_FC_DUAL_DVI_CTRL1, ~_BIT2, 0x00);

        // Disable Dual DVI FIFO
        ScalerSetBit(P31_04_FC_DUAL_DVI_CTRL2, ~(_BIT7 | _BIT5), 0x00);

        // Disable Dual DVI Output from D2 + D3 Port
        switch(ScalerGetBit(P31_03_FC_DUAL_DVI_CTRL1, (_BIT7 | _BIT6 | _BIT5)))
        {
#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
            case (_BIT7 | _BIT6 | _BIT5):
                ScalerSetBit(P31_03_FC_DUAL_DVI_CTRL1, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6));
                break;
            case (_BIT7 | _BIT6):
                break;
#endif
            default:
                ScalerSetBit(P31_03_FC_DUAL_DVI_CTRL1, ~_BIT7, 0x00);
                break;
        }

        // Enable Video Output
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_30_PORT_PAGE72_HDMI_AVMCR, ~_BIT3, _BIT3);
        ScalerSetDataPortBit(P72_C9_HDMI_AP, _P72_CA_PT_80_PORT_PAGE72_HDMI_DPC_SET0, ~_BIT7, _BIT7);

        // Enable RGB Clk Output
        ScalerSetBit(P72_A6_TMDS_OUTCTL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT5 | _BIT4 | _BIT3));
    }
}

//--------------------------------------------------
// Description  : TMDS Double Check Dual DVI Format
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerTMDSRx2DualDVICheck(void)
{
    SBYTE pchTMDSRx2Vth[3];
    SBYTE pchTMDSRx3Vth[3];
    SBYTE pchTMDSRx2Tap0[3];
    SBYTE pchTMDSRx3Tap0[3];

    // Disable Rx2 DFE VTH Adaptation, Disable Rx3 DFE VTH Adaptation
    ScalerSetBit(P7B_A1_L0_DFE_EN_2, ~_BIT6, 0x00);
    ScalerSetBit(P7B_B1_L1_DFE_EN_2, ~_BIT6, 0x00);
    ScalerSetBit(P7B_C1_L2_DFE_EN_2, ~_BIT6, 0x00);

    ScalerSetBit(P7C_A1_L0_DFE_EN_2, ~_BIT6, 0x00);
    ScalerSetBit(P7C_B1_L1_DFE_EN_2, ~_BIT6, 0x00);
    ScalerSetBit(P7C_C1_L2_DFE_EN_2, ~_BIT6, 0x00);

    // Read Out Rx2 DFE VTH Value
    ScalerSetBit(P7B_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Lane0 VTH adapt Value
    ScalerSetBit(P7B_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
    pchTMDSRx2Vth[0] = (ScalerGetByte(P7B_F1_COEF_2) & 0x0F);

    // Lane1 VTH adapt Value
    ScalerSetBit(P7B_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
    pchTMDSRx2Vth[1] = (ScalerGetByte(P7B_F1_COEF_2) & 0x0F);

    // Lane2 VTH adapt Value
    ScalerSetBit(P7B_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
    pchTMDSRx2Vth[2] = (ScalerGetByte(P7B_F1_COEF_2) & 0x0F);

    // Read Out Rx3 DFE VTH Value
    ScalerSetBit(P7C_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Lane0 VTH adapt Value
    ScalerSetBit(P7C_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
    pchTMDSRx3Vth[0] = (ScalerGetByte(P7C_F1_COEF_2) & 0x0F);

    // Lane1 VTH adapt Value
    ScalerSetBit(P7C_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
    pchTMDSRx3Vth[1] = (ScalerGetByte(P7C_F1_COEF_2) & 0x0F);

    // Lane2 VTH adapt Value
    ScalerSetBit(P7C_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
    pchTMDSRx3Vth[2] = (ScalerGetByte(P7C_F1_COEF_2) & 0x0F);

    // Read Out Rx2 DFE Tap0 Value
    ScalerSetBit(P7B_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

    // Lane0 Tap0 adapt Value
    ScalerSetBit(P7B_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
    pchTMDSRx2Tap0[0] = ScalerGetByte(P7B_F1_COEF_2);

    // Lane1 Tap0 adapt Value
    ScalerSetBit(P7B_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
    pchTMDSRx2Tap0[1] = ScalerGetByte(P7B_F1_COEF_2);

    // Lane2 Tap0 adapt Value
    ScalerSetBit(P7B_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
    pchTMDSRx2Tap0[2] = ScalerGetByte(P7B_F1_COEF_2);

    // Read Out Rx3 DFE Tap0 Value
    ScalerSetBit(P7C_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

    // Lane0 Tap0 adapt Value
    ScalerSetBit(P7C_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
    pchTMDSRx3Tap0[0] = ScalerGetByte(P7C_F1_COEF_2);

    // Lane1 Tap0 adapt Value
    ScalerSetBit(P7C_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
    pchTMDSRx3Tap0[1] = ScalerGetByte(P7C_F1_COEF_2);

    // Lane2 Tap0 adapt Value
    ScalerSetBit(P7C_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
    pchTMDSRx3Tap0[2] = ScalerGetByte(P7C_F1_COEF_2);

    // Check 2 Dual Port Vth Adapt Value
    if((abs(pchTMDSRx3Vth[0] - pchTMDSRx2Vth[0]) < 4) &&
       (abs(pchTMDSRx3Vth[1] - pchTMDSRx2Vth[1]) < 4) &&
       (abs(pchTMDSRx3Vth[2] - pchTMDSRx2Vth[2]) < 4))
    {
        // Double Check Tap0
        if((abs(pchTMDSRx2Tap0[0] - pchTMDSRx3Tap0[0]) < 10) &&
           (abs(pchTMDSRx2Tap0[1] - pchTMDSRx3Tap0[1]) < 10) &&
           (abs(pchTMDSRx2Tap0[2] - pchTMDSRx3Tap0[2]) < 10))
        {
            return _TRUE;
        }
    }

    return _FALSE;
}
#endif // End of #if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)

//--------------------------------------------------
// Description  : Check CDR Locked
// Input Value  : Measured Clk Count to be compared
// Output Value : _TRUE => Stable
//--------------------------------------------------
bit ScalerTMDSRx2CheckCDRStable(WORD usClkCount)
{
#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

    if(GET_D2_TMDS_MODE() == _TMDS_MHL_MODE)
    {
        switch(GET_TMDS_RX2_CLK_MODE())
        {
            // Check if Packed Pixel Mode
            case _TMDS_MHL_PPMODE_PHY_SETTING:

                // Check Current Measured Freq. is the same as previously locked
                if(abs(usClkCount - (ScalerTMDSRx2MeasureClk(_CLK_SOURCE_RED) * 4)) > (usClkCount >> 6))
                {
                    DebugMessageRx2("R Channel CDR Unstable", ScalerTMDSRx2MeasureClk(_CLK_SOURCE_RED));
                    return _FALSE;
                }

                break;

            // Check if 24 Bit Mode
            case _TMDS_24BIT_PHY_SETTING:

                // Check Current Measured Freq. is the same as previously locked
                if(abs(usClkCount - (ScalerTMDSRx2MeasureClk(_CLK_SOURCE_RED) * 3)) > (usClkCount >> 6))
                {
                    DebugMessageRx2("R Channel CDR Unstable", ScalerTMDSRx2MeasureClk(_CLK_SOURCE_RED));
                    return _FALSE;
                }

                break;

#if(_D2_MHL_VERSION >= _MHL_VERSION_3_0)

            // Check if 1.5G, 3.0G, 6.0G Mode
            case _TMDS_MHL_ECBUS_PHY_SETTING:

                // Check Current Measured Freq. is the same as previously locked
                if(abs(usClkCount - (ScalerTMDSRx2MeasureClk(_CLK_SOURCE_RED) * GET_MHL3_RX2_AV_LINK_N_CODE())) > (usClkCount >> 5))
                {
                    DebugMessageRx2("R Channel CDR Unstable", (ScalerTMDSRx2MeasureClk(_CLK_SOURCE_RED)* GET_MHL3_RX2_AV_LINK_N_CODE()));
                    return _FALSE;
                }

                break;

#endif // End of #if(_D2_MHL_VERSION >= _MHL_VERSION_3_0)

            default:

                return _FALSE;
                break;
        }
    }
    else
#endif // End of #if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
    {
#if(_D2_HDMI_2_0_SUPPORT == _ON)

        if(GET_TMDS_RX2_HIGH_SPEED_MODE() == _TRUE)
        {
            // Check Current Measured Freq. is the same as previously locked
            if(abs(usClkCount - (ScalerTMDSRx2MeasureClk(_CLK_SOURCE_RED) * 4)) > (usClkCount >> 6))
            {
                return _FALSE;
            }

            if(abs(usClkCount - (ScalerTMDSRx2MeasureClk(_CLK_SOURCE_BLUE) * 4)) > (usClkCount >> 6))
            {
                return _FALSE;
            }

            if(abs(usClkCount - (ScalerTMDSRx2MeasureClk(_CLK_SOURCE_GREEN) * 4)) > (usClkCount >> 6))
            {
                return _FALSE;
            }
        }
        else
#endif
        {
            // Check Current Measured Freq. is the same as previously locked
            if(abs(usClkCount - ScalerTMDSRx2MeasureClk(_CLK_SOURCE_RED)) > (usClkCount >> 6))
            {
                DebugMessageRx2("R Channel CDR Unstable", ScalerTMDSRx2MeasureClk(_CLK_SOURCE_RED));
                return _FALSE;
            }

            if(abs(usClkCount - ScalerTMDSRx2MeasureClk(_CLK_SOURCE_BLUE)) > (usClkCount >> 6))
            {
                DebugMessageRx2("B Channel CDR Unstable", ScalerTMDSRx2MeasureClk(_CLK_SOURCE_BLUE));
                return _FALSE;
            }

            if(abs(usClkCount - ScalerTMDSRx2MeasureClk(_CLK_SOURCE_GREEN)) > (usClkCount >> 6))
            {
                DebugMessageRx2("G Channel CDR Unstable", ScalerTMDSRx2MeasureClk(_CLK_SOURCE_GREEN));
                return _FALSE;
            }
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Check CDR Locked (EXINT0 Only)
// Input Value  : Measured Clk Count to be compared
// Output Value : _TRUE => Stable
//--------------------------------------------------
BYTE ScalerTMDSRx2CheckCDRStable_EXINT0(WORD usClkCount) using 1
{
#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

    if(GET_D2_TMDS_MODE() == _TMDS_MHL_MODE)
    {
        switch(GET_TMDS_RX2_CLK_MODE())
        {
            // Check if Packed Pixel Mode
            case _TMDS_MHL_PPMODE_PHY_SETTING:

                // Check Current Measured Freq. is the same as previously locked
                if(abs(usClkCount - ScalerTMDSRx2MeasureClk_EXINT0(_CLK_SOURCE_TMDS)) > (usClkCount >> 6))
                {
                    return _FALSE;
                }

                // Check Current Measured Freq. is the same as previously locked
                if(abs(usClkCount - (ScalerTMDSRx2MeasureClk_EXINT0(_CLK_SOURCE_RED) * 4)) > (usClkCount >> 6))
                {
                    return _FALSE;
                }

                break;

            // Check if 24 Bit Mode
            case _TMDS_24BIT_PHY_SETTING:

                // Check Current Measured Freq. is the same as previously locked
                if(abs(usClkCount - ScalerTMDSRx2MeasureClk_EXINT0(_CLK_SOURCE_TMDS)) > (usClkCount >> 6))
                {
                    return _FALSE;
                }

                // Check Current Measured Freq. is the same as previously locked
                if(abs(usClkCount - (ScalerTMDSRx2MeasureClk_EXINT0(_CLK_SOURCE_RED) * 3)) > (usClkCount >> 6))
                {
                    return _FALSE;
                }

                break;

#if(_D2_MHL_VERSION >= _MHL_VERSION_3_0)

            // Check if 1.5G, 3.0G, 6.0G Mode
            case _TMDS_MHL_ECBUS_PHY_SETTING:

                // Check Current Measured Freq. is the same as previously locked
                if(abs(usClkCount - ScalerTMDSRx2MeasureClk_EXINT0(_CLK_SOURCE_TMDS)) > (usClkCount >> 6))
                {
                    return _FALSE;
                }

                // Check Current Measured Freq. is the same as previously locked
                if(abs(usClkCount - (ScalerTMDSRx2MeasureClk_EXINT0(_CLK_SOURCE_RED) * GET_MHL3_RX2_AV_LINK_N_CODE())) > (usClkCount >> 5))
                {
                    return _FALSE;
                }

                break;

#endif // End of #if(_D2_MHL_VERSION >= _MHL_VERSION_3_0)

            default:

                return _FALSE;
                break;
        }
    }
    else
#endif // End of #if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
    {
#if(_D2_HDMI_2_0_SUPPORT == _ON)
        if(GET_TMDS_RX2_HIGH_SPEED_MODE() == _TRUE)
        {
            // Check Current Measured Freq. is the same as previously locked
            if(abs(usClkCount - ScalerTMDSRx2MeasureClk_EXINT0(_CLK_SOURCE_TMDS)) > (usClkCount >> 6))
            {
                return _FALSE;
            }

            if(abs(usClkCount - (ScalerTMDSRx2MeasureClk_EXINT0(_CLK_SOURCE_RED) * 4)) > (usClkCount >> 6))
            {
                return _FALSE;
            }

            if(abs(usClkCount - (ScalerTMDSRx2MeasureClk_EXINT0(_CLK_SOURCE_BLUE) * 4)) > (usClkCount >> 6))
            {
                return _FALSE;
            }

            if(abs(usClkCount - (ScalerTMDSRx2MeasureClk_EXINT0(_CLK_SOURCE_GREEN) * 4)) > (usClkCount >> 6))
            {
                return _FALSE;
            }
        }
        else
#endif
        {
            // Check Current Measured Freq. is the same as previously locked
            if(abs(usClkCount - ScalerTMDSRx2MeasureClk_EXINT0(_CLK_SOURCE_TMDS)) > (usClkCount >> 6))
            {
                return _FALSE;
            }

            if(abs(usClkCount - ScalerTMDSRx2MeasureClk_EXINT0(_CLK_SOURCE_RED)) > (usClkCount >> 6))
            {
                return _FALSE;
            }

            if(abs(usClkCount - ScalerTMDSRx2MeasureClk_EXINT0(_CLK_SOURCE_BLUE)) > (usClkCount >> 6))
            {
                return _FALSE;
            }

            if(abs(usClkCount - ScalerTMDSRx2MeasureClk_EXINT0(_CLK_SOURCE_GREEN)) > (usClkCount >> 6))
            {
                return _FALSE;
            }
        }
    }

    return _TRUE;
}

#if(_D2_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Hdmi Handle AVMute Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx2HdmiAVMuteProc(void)
{
#if((_D2_INPUT_PORT_TYPE == _D2_MHL_PORT) && (_D2_MHL_VERSION >= _MHL_VERSION_3_0))

    if((GET_D2_TMDS_MODE() == _TMDS_MHL_MODE) && (GET_MHL3_RX2_ECBUS_MODE() == _ON))
    {
        if((ScalerGetBit(P71_CB_HDMI_SR, _BIT6) == 0x00) && (ScalerGetBit(P76_10_REG_MHL3_OUTPUT_0, _BIT3) == _BIT3))
        {
            // Clear AVMute Flag
            ScalerSetBit(P71_CB_HDMI_SR, ~_BIT7, _BIT7);

            // Disable AVMute Watch Dog
            ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_31_PORT_PAGE71_HDMI_WDCR0, ~_BIT7, 0x00);
            ScalerSetBit(P76_10_REG_MHL3_OUTPUT_0, ~_BIT3, 0x00);

            // Enable Video/Audio Output
            ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_30_PORT_PAGE71_HDMI_AVMCR, ~(_BIT5 | _BIT3), (_BIT5 | _BIT3));

            // Enable AVMute Watch Dog
            ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_31_PORT_PAGE71_HDMI_WDCR0, ~_BIT7, _BIT7);
            ScalerSetBit(P76_10_REG_MHL3_OUTPUT_0, ~_BIT3, _BIT3);
        }
    }
    else
#endif // End of #if((_D2_INPUT_PORT_TYPE == _D2_MHL_PORT) && (_D2_MHL_VERSION >= _MHL_VERSION_3_0))
    {
        // if AVMute Has been triggered
        if((ScalerGetBit(P71_CB_HDMI_SR, _BIT6) == 0x00) && (ScalerGetBit(P71_A6_TMDS_OUTCTL, (_BIT6 | _BIT5 | _BIT4)) == 0x00))
        {
            // Clear AVMute Flag
            ScalerSetBit(P71_CB_HDMI_SR, ~_BIT7, _BIT7);

            // Disable AVMute Watch Dog
            ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_31_PORT_PAGE71_HDMI_WDCR0, ~_BIT7, 0x00);

            // Enable Video/Audio Output
            ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_30_PORT_PAGE71_HDMI_AVMCR, ~(_BIT5 | _BIT3), (_BIT5 | _BIT3));

            // Enable RGB Output
            ScalerSetBit(P71_A6_TMDS_OUTCTL, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));

            // Enable AVMute Watch Dog
            ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_31_PORT_PAGE71_HDMI_WDCR0, ~_BIT7, _BIT7);
        }
    }
}
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_DUAL_DVI_PORT)
//--------------------------------------------------
// Description  : Detect TMDS Format
// Input Value  : None
// Output Value : Return DVI or HDMI format
//--------------------------------------------------
BYTE ScalerTMDSRx2FormatDetect(void)
{
    // Polling at least 3 frame for HW auto detect TMDS format
    if(ScalerTimerPollingFlagProc(130, P71_CB_HDMI_SR, _BIT0, _TRUE) == _TRUE)
    {
        ScalerSetBit(P71_AF_TMDS_WDC, ~_BIT0, 0x00);

#if(_D2_HDMI_2_0_SUPPORT == _ON)
        if(GET_D2_TMDS_MODE() == _TMDS_HDMI_MODE)
        {
            // Check if HDMI 2.0 ON
            if(ScalerGetBit(P71_00_HDMI_CTRL_00, _BIT0) == _BIT0)
            {
                // Set Manual Format to HDMI
                ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_00_PORT_PAGE71_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT3 | _BIT2));

                // Toggle HW Format Detect Flag Reset
                ScalerSetBit(P71_01_HDMI_CTRL_01, ~(_BIT7 | _BIT3), _BIT7);
                ScalerSetBit(P71_01_HDMI_CTRL_01, ~(_BIT7 | _BIT3), 0x00);

                SET_TMDS_RX2_HDMI_2_0_FORMAT_RESET_WAITING();

                ScalerTimerReactiveTimerEvent(130, _SCALER_TIMER_EVENT_RX2_HDMI2_FORMAT_RESET_WAIT);
            }

            // Detect Scrambling Control Symbol
            if(ScalerGetBit(P71_01_HDMI_CTRL_01, _BIT3) == _BIT3)
            {
                // Enable Scrambling Status in SCDC
                ScalerSetDataPortBit(P71_39_HDMI_CTRL_39, _P71_3A_PT_21_PORT_PAGE71_HDMI_SCDC_21, ~_BIT0, _BIT0);
            }
        }
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        if(GET_D2_TMDS_MODE() == _TMDS_MHL_MODE)
        {
            // Set Manual Format to HDMI
            ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_00_PORT_PAGE71_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT3 | _BIT2));
        }
#endif
        return _SOURCE_HDMI;
    }
    else
    {
        ScalerSetBit(P71_AF_TMDS_WDC, ~_BIT0, _BIT0);

        if(GET_D2_TMDS_MODE() == _TMDS_HDMI_MODE)
        {
#if(_D2_HDMI_2_0_SUPPORT == _ON)
            if(ScalerGetBit(P71_00_HDMI_CTRL_00, _BIT0) == _BIT0)
            {
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX2_HDMI2_FORMAT_RESET_WAIT);
            }
#endif
            // Set Format Detect HW Auto Mode
            ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_00_PORT_PAGE71_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), 0x00);
        }
#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
        else
        {
            // Manual Set to DVI Mode
            ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_00_PORT_PAGE71_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), _BIT3);
        }
#endif
        return _SOURCE_DVI;
    }
}
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)
//--------------------------------------------------
// Description  : Get Whehter Current Mode is Dual DVI Mode
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerTMDSRx2GetDualDVIMode(void)
{
    switch(ScalerGetBit(P31_03_FC_DUAL_DVI_CTRL1, (_BIT7 | _BIT6 | _BIT5)))
    {
        case _BIT7:
#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
        case (_BIT7 | _BIT6 | _BIT5):
#endif
            return _TRUE;

        default:
            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Get Whehter Current Mode is Dual DVI Mode in Interupt
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
BYTE ScalerTMDSRx2GetDualDVIMode_EXINT0(void) using 1
{
    switch(ScalerGetBit_EXINT(P31_03_FC_DUAL_DVI_CTRL1, (_BIT7 | _BIT6 | _BIT5)))
    {
        case _BIT7:
#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
        case (_BIT7 | _BIT6 | _BIT5):
#endif
            return _TRUE;

        default:
            return _FALSE;
    }
}
#endif
#endif // End of #if(_D2_TMDS_SUPPORT == _ON)
