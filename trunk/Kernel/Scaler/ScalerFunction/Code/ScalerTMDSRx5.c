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
// ID Code      : ScalerTMDSRx5.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_TMDSRX5__

#include "ScalerFunctionInclude.h"

#if(_D5_TMDS_SUPPORT == _ON)

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
StructTMDSCtrlInfo g_stTMDSRx5CtrlInfo;
WORD g_usTMDSRx5ClkCount;

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
BYTE g_ucTMDSRx5ClkMode = _TMDS_24BIT_PHY_SETTING;
#endif

#if(_D5_HDMI_SUPPORT == _ON)
BYTE g_ucTMDSRx5AviInfo;
#endif

EnumDisplayDataPath g_enumTMDSRx5IrqForceBackgrd;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerTMDSRx5DviVideoSetting(void);
void ScalerTMDSRx5SetPorchColor(EnumColorSpace enumColorFormat);

#if(_D5_HDMI_SUPPORT == _ON)

bit ScalerTMDSRx5HdmiDeepColorProc(WORD usTmdsClkCnt);
bit ScalerTMDSRx5HdmiWaitDeepColorPllLock(void);

void ScalerTMDSRx5HdmiPacketDetect(bit bWait);
void ScalerTMDSRx5HdmiPacketDetectEvent(void);
BYTE ScalerTMDSRx5HdmiGetAVIInfo(EnumAviInfoContent enumContent);
bit ScalerTMDSRx5HdmiAviPixelRepInfoChanged(void);
BYTE ScalerTMDSRx5HdmiGetColorDepth(void);
void ScalerTMDSRx5HdmiWatchDog(BYTE ucWDType, bit bEnable);

#if(_HDMI_FREESYNC_SUPPORT == _ON)
BYTE ScalerTMDSRx5HdmiGetAmdSpdInfo(EnumAmdSpdInfoContent enumContent);
#endif
#endif

void ScalerTMDSRx5PowerOffProc(void);
void ScalerTMDSRx5FreqDetectDisable(void);
void ScalerTMDSRx5FirstActiveProc(BYTE ucSourceType);

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
void ScalerTMDSRx5TMDSScanInitial(BYTE ucInputPort);
bit ScalerTMDSRx5TMDSPSPreDetect(BYTE ucInputPort);
bit ScalerTMDSRx5TMDSNormalPreDetect(BYTE ucInputPort);
#endif

bit ScalerTMDSRx5HdcpEnabled(void);
BYTE ScalerTMDSRx5TMDSVideoDetect(bit bWait);
void ScalerTMDSRx5TMDSVideoDetectEvent(void);
bit ScalerTMDSRx5CheckCDRStable(WORD usClkCount);
BYTE ScalerTMDSRx5CheckCDRStable_EXINT0(WORD usClkCount);
void ScalerTMDSRx5Initial(BYTE ucInputPort);
void ScalerTMDSRx5PowerSavingProc(void);

#if(_D5_HDMI_SUPPORT == _ON)
void ScalerTMDSRx5HdmiAVMuteProc(void);
#endif

BYTE ScalerTMDSRx5FormatDetect(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : TMDS Video Setting
// Input Value  : Source Type
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx5DviVideoSetting(void)
{
    // Manual Set Color Space and disable pixel repetition
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_51_PORT_PAGE74_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);

    // Disable Down Sampling
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_50_PORT_PAGE74_HDMI_VCR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Waiting for Down Sampling Effect
    ScalerTimerDelayXms(20);

    SET_COLOR_SPACE(_D5_INPUT_PORT, _COLOR_SPACE_RGB);
    SET_COLOR_RGB_QUANTIZATION_RANGE(_D5_INPUT_PORT, _RGB_QUANTIZATION_FULL_RANGE);

    ScalerTMDSRx5SetPorchColor(GET_COLOR_SPACE(_D5_INPUT_PORT));
}

//--------------------------------------------------
// Description  : Set Back Ground Color
// Input Value  : Current Color Space
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx5SetPorchColor(EnumColorSpace enumColorFormat)
{
    // Manual Set Background Color Enable
    ScalerSetBit(P74_B9_TMDS_OUT_CTRL, ~_BIT7, 0x00);

    if((enumColorFormat == _COLOR_SPACE_YCBCR444) || (enumColorFormat == _COLOR_SPACE_YCBCR422))
    {
        ScalerSetByte(P74_BA_TMDS_ROUT_HIGH_BYTE, 0x80);
        ScalerSetByte(P74_BB_TMDS_ROUT_LOW_BYTE, 0x00);
        ScalerSetByte(P74_BC_TMDS_GOUT_HIGH_BYTE, 0x0F);
        ScalerSetByte(P74_BD_TMDS_GOUT_LOW_BYTE, 0x00);
        ScalerSetByte(P74_BE_TMDS_BOUT_HIGH_BYTE, 0x80);
        ScalerSetByte(P74_BF_TMDS_BOUT_LOW_BYTE, 0x00);
    }
#if(_HDMI_2_0_YCBCR420_SUPPORT == _ON)
    else if(enumColorFormat == _COLOR_SPACE_YCBCR420)
    {
        ScalerSetByte(P74_BA_TMDS_ROUT_HIGH_BYTE, 0x10);
        ScalerSetByte(P74_BB_TMDS_ROUT_LOW_BYTE, 0x00);
        ScalerSetByte(P74_BC_TMDS_GOUT_HIGH_BYTE, 0x10);
        ScalerSetByte(P74_BD_TMDS_GOUT_LOW_BYTE, 0x00);
        ScalerSetByte(P74_BE_TMDS_BOUT_HIGH_BYTE, 0x80);
        ScalerSetByte(P74_BF_TMDS_BOUT_LOW_BYTE, 0x00);
    }
#endif
    else
    {
        ScalerSetByte(P74_BA_TMDS_ROUT_HIGH_BYTE, 0x00);
        ScalerSetByte(P74_BB_TMDS_ROUT_LOW_BYTE, 0x00);
        ScalerSetByte(P74_BC_TMDS_GOUT_HIGH_BYTE, 0x00);
        ScalerSetByte(P74_BD_TMDS_GOUT_LOW_BYTE, 0x00);
        ScalerSetByte(P74_BE_TMDS_BOUT_HIGH_BYTE, 0x00);
        ScalerSetByte(P74_BF_TMDS_BOUT_LOW_BYTE, 0x00);
    }
}

#if(_D5_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDMI Deep Color Proc
// Input Value  : void
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerTMDSRx5HdmiDeepColorProc(WORD usTmdsClkCnt)
{
    // Setting Deep Color PLL
    if(ScalerTMDSRx5HdmiSetDeepColorPll(usTmdsClkCnt, GET_COLOR_DEPTH(_D5_INPUT_PORT)) == _FALSE)
    {
        return _FALSE;
    }

    // Wait for Phase lock
    if(ScalerTMDSRx5HdmiWaitDeepColorPllLock() == _FALSE)
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
bit ScalerTMDSRx5HdmiWaitDeepColorPllLock(void)
{
    BYTE ucTemp = 0;

    do
    {
        ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_82_PORT_PAGE74_HDMI_DPC_SET2, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));

        // Delay for PLL Phase Lock
        ScalerTimerDelayXms(2);

        ucTemp++;
    }
    while((ScalerGetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_82_PORT_PAGE74_HDMI_DPC_SET2, _BIT1) != 0) && (ucTemp <= 15));

    if(ucTemp > 15)
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Detect HDMI Info Frame
// Input Value  : bWait => Whether to wait then read
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx5HdmiPacketDetect(bit bWait)
{
    if(bWait == _WAIT)
    {
        // Polling 3 frame for detect Packet signals
        if(ScalerTimerPollingFlagProc(130, P74_CC_HDMI_GPVS, (_BIT6 | _BIT5), _TRUE) == _TRUE)
        {
            // Both GCP & AVI infoframe packet have been received
            if(ScalerGetBit(P74_CC_HDMI_GPVS, (_BIT6 | _BIT5)) == (_BIT6 | _BIT5))
            {
                SET_HDMI_RX5_GCP_RECEIVED();

                SET_HDMI_RX5_AVI_INFO_FRAME_RECEIVED();
            }
            // Only AVI infoframe packet have been received
            else if(ScalerGetBit(P74_CC_HDMI_GPVS, (_BIT6 | _BIT5)) == _BIT5)
            {
                SET_HDMI_RX5_AVI_INFO_FRAME_RECEIVED();

                // Polling more 1 frame to wait GCP packet for HW can't update bit 6 & bit 5 simultaneously
                if(ScalerTimerPollingFlagProc(45, P74_CC_HDMI_GPVS, _BIT6, _TRUE) == _TRUE)
                {
                    SET_HDMI_RX5_GCP_RECEIVED();
                }
                else
                {
                    CLR_HDMI_RX5_GCP_RECEIVED();
                }
            }
            // Only GCP Packet have been received
            else if(ScalerGetBit(P74_CC_HDMI_GPVS, (_BIT6 | _BIT5)) == _BIT6)
            {
                SET_HDMI_RX5_GCP_RECEIVED();

                // Polling more 1 frame to wait AVI infoframe packet for HW can't update bit 6 & bit 5 simultaneously
                if(ScalerTimerPollingFlagProc(45, P74_CC_HDMI_GPVS, _BIT5, _TRUE) == _TRUE)
                {
                    SET_HDMI_RX5_AVI_INFO_FRAME_RECEIVED();
                }
                else
                {
                    CLR_HDMI_RX5_AVI_INFO_FRAME_RECEIVED();
                }
            }
        }
        // Neither AVI infoframe nor GCP packet received
        else
        {
            CLR_HDMI_RX5_GCP_RECEIVED();

            CLR_HDMI_RX5_AVI_INFO_FRAME_RECEIVED();
        }

#if(_HDMI_FREESYNC_SUPPORT == _ON)
#if(_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE)
        // Polling 3 frame for detect Packet signals P74_CA_00[7]
        if((GET_HDMI_FREESYNC_VCP() == 0x01) && (ScalerTimerPollingDataBitFlagProc(130, P74_C9_HDMI_AP, _P74_CA_PT_00_PORT_PAGE74_HDMI_SCR, _BIT7, _TRUE) == _TRUE))
#else
        // Polling 3 frame for detect Packet signals P74_CA_00[7]
        if(ScalerTimerPollingDataBitFlagProc(130, P74_C9_HDMI_AP, _P74_CA_PT_00_PORT_PAGE74_HDMI_SCR, _BIT7, _TRUE) == _TRUE)
#endif
        {
            SET_TMDS_RX5_SPD_INFO_FRAME_RECEIVED();
        }
        else
        {
            CLR_TMDS_RX5_SPD_INFO_FRAME_RECEIVED();
        }
#endif

        // Wait at least 3 frame for HW auto update color depth value
        ScalerTimerDelayXms(130);

        CLR_HDMI_RX5_PACKET_DETECTING();
    }
    else
    {
        if(ScalerGetBit(P74_CC_HDMI_GPVS, _BIT6) == _BIT6)
        {
            ScalerTMDSRx5HdmiWatchDog(_HDMI_AV_MUTE_WD, _ENABLE);

            SET_HDMI_RX5_GCP_RECEIVED();
        }
        else
        {
            ScalerTMDSRx5HdmiWatchDog(_HDMI_AV_MUTE_WD, _DISABLE);

            CLR_HDMI_RX5_GCP_RECEIVED();
        }

        if(ScalerGetBit(P74_CC_HDMI_GPVS, _BIT5) == _BIT5)
        {
            // Color Space Auto/ Pixel Repetition auto mode
            ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_51_PORT_PAGE74_HDMI_ACRCR, ~(_BIT6 | _BIT2), (_BIT6 | _BIT2));

            ScalerTMDSRx5HdmiWatchDog(_HDMI_AVI_INFO_VARIATION_WD, _ENABLE);

            SET_HDMI_RX5_AVI_INFO_FRAME_RECEIVED();
        }
        else
        {
            // Mannal Set Color Space and disable pixel  repetition
            ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_51_PORT_PAGE74_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);

            // Disable down sampling
            ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_50_PORT_PAGE74_HDMI_VCR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // Waiting for Down Sampling Effect
            ScalerTimerDelayXms(20);

            ScalerTMDSRx5HdmiWatchDog(_HDMI_AVI_INFO_VARIATION_WD, _DISABLE);

            CLR_HDMI_RX5_AVI_INFO_FRAME_RECEIVED();
        }

#if(_HDMI_FREESYNC_SUPPORT == _ON)
#if(_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE)
        if((GET_HDMI_FREESYNC_VCP() == 0x01) && (ScalerGetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_00_PORT_PAGE74_HDMI_SCR, _BIT7) == _BIT7))
#else
        if(ScalerGetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_00_PORT_PAGE74_HDMI_SCR, _BIT7) == _BIT7)
#endif
        {
            SET_TMDS_RX5_SPD_INFO_FRAME_RECEIVED();
        }
        else
        {
            CLR_TMDS_RX5_SPD_INFO_FRAME_RECEIVED();
        }
#endif

        // Clear Detection Flag
        ScalerSetBit(P74_CC_HDMI_GPVS, ~_BIT6, _BIT6);

        ScalerSetBit(P74_CC_HDMI_GPVS, ~_BIT5, _BIT5);

        ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_00_PORT_PAGE74_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT7);

        SET_HDMI_RX5_PACKET_DETECTING();

        // Activate Packet Detection Event
        ScalerTimerActiveTimerEvent(SEC(0.13), _SCALER_TIMER_EVENT_RX5_TMDS_HDMI_PACKET_DETECT);
    }
}

//--------------------------------------------------
// Description  : HDMI Info Frame Packet Detect Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx5HdmiPacketDetectEvent(void)
{
    CLR_HDMI_RX5_PACKET_DETECTING();
}

//--------------------------------------------------
// Description  : Get HDMI AVI Info Contents
// Input Value  : Content of Interest
// Output Value : Content Value
//--------------------------------------------------
BYTE ScalerTMDSRx5HdmiGetAVIInfo(EnumAviInfoContent enumContent)
{
    if(GET_HDMI_RX5_AVI_INFO_FRAME_RECEIVED() == _TRUE)
    {
        switch(enumContent)
        {
            case _AVI_INFO_COLOR_SPACE:

                return (ScalerGetDataPortBit(P74_CD_HDMI_PSAP, 0x04, (_BIT6 | _BIT5)) >> 5);

            case _AVI_INFO_COLORIMETRY:

                return (ScalerGetDataPortBit(P74_CD_HDMI_PSAP, 0x05, (_BIT7 | _BIT6)) >> 6);

            case _AVI_INFO_EXTENDED_COLORIMETRY:

                return (ScalerGetDataPortBit(P74_CD_HDMI_PSAP, 0x06, (_BIT6 | _BIT5 | _BIT4)) >> 4);

            case _AVI_INFO_RGB_QUANTIZATION:

                return (ScalerGetDataPortBit(P74_CD_HDMI_PSAP, 0x06, (_BIT3 | _BIT2)) >> 2);

            case _AVI_INFO_YCC_QUANTIZATION:

                return (ScalerGetDataPortBit(P74_CD_HDMI_PSAP, 0x08, (_BIT7 | _BIT6)) >> 6);

            case _AVI_INFO_SCAN_INFO:

                return ScalerGetDataPortBit(P74_CD_HDMI_PSAP, 0x04, (_BIT1 | _BIT0));

            case _AVI_INFO_IT_CONTENT:

                return (ScalerGetDataPortBit(P74_CD_HDMI_PSAP, 0x06, _BIT7) >> 7);

            case _AVI_INFO_PIXEL_REPETITION:

                return (ScalerGetDataPortBit(P74_CD_HDMI_PSAP, 0x08, (_BIT3 | _BIT2 | _BIT1 | _BIT0)));

            case _AVI_INFO_AR:

                return (ScalerGetDataPortBit(P74_CD_HDMI_PSAP, 0x05, (_BIT5 | _BIT4)) >> 4);

            case _AVI_INFO_VIC:

                return (ScalerGetDataPortBit(P74_CD_HDMI_PSAP, 0x07, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)));

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
bit ScalerTMDSRx5HdmiAviPixelRepInfoChanged(void)
{
    // Check Tmds Pixel Repetition
    if(ScalerTMDSRx5HdmiGetAVIInfo(_AVI_INFO_PIXEL_REPETITION) != GET_TMDS_RX5_AVI_PIXEL_REPETITION())
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
BYTE ScalerTMDSRx5HdmiGetColorDepth(void)
{
    if(GET_COLOR_SPACE(_D5_INPUT_PORT) == _COLOR_SPACE_YCBCR422)
    {
        return _COLOR_DEPTH_12_BITS;
    }

    if(GET_HDMI_RX5_GCP_RECEIVED() == _TRUE)
    {
        if(ScalerGetBit(P74_B4_TMDS_DPC0, 0x07) == 0x05)
        {
            return _COLOR_DEPTH_10_BITS;
        }
        else if(ScalerGetBit(P74_B4_TMDS_DPC0, 0x07) == 0x06)
        {
            return _COLOR_DEPTH_12_BITS;
        }
        else if(ScalerGetBit(P74_B4_TMDS_DPC0, 0x07) == 0x07)
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
void ScalerTMDSRx5HdmiWatchDog(BYTE ucWDType, bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        if((ucWDType & _HDMI_AVI_INFO_VARIATION_WD) == _HDMI_AVI_INFO_VARIATION_WD)
        {
            if(ScalerGetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_41_PORT_PAGE74_HDMI_VWDSR, _BIT0) == 0x00)
            {
                // Clear AVI Info Frame Variation flag
                ScalerSetBit(P74_CC_HDMI_GPVS, ~(_BIT6 | _BIT5 | _BIT0), _BIT0);

                if((GET_COLOR_SPACE(_D5_INPUT_PORT) == _COLOR_SPACE_YCBCR444) || (GET_COLOR_SPACE(_D5_INPUT_PORT) == _COLOR_SPACE_YCBCR422))
                {
                    // Enable Color Space/ Colorimetry Change Detection
                    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_45_PORT_PAGE74_HDMI_PVGCR0, ~(_BIT3 | _BIT0), (_BIT3 | _BIT0));
                }
                else
                {
                    // Enable Color Space Change Detection
                    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_45_PORT_PAGE74_HDMI_PVGCR0, ~(_BIT3 | _BIT0), _BIT0);
                }

                // Enable AVI Info Frame Variation Watch Dog
                ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_41_PORT_PAGE74_HDMI_VWDSR, ~_BIT0, _BIT0);
            }
        }

        if((ucWDType & _HDMI_AV_MUTE_WD) == _HDMI_AV_MUTE_WD)
        {
            if(ScalerGetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_31_PORT_PAGE74_HDMI_WDCR0, _BIT7) == 0x00)
            {
                // CLR AVMute Flag
                ScalerSetBit(P74_CB_HDMI_SR, ~_BIT7, _BIT7);

                // Enable AVMute WD
                ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_31_PORT_PAGE74_HDMI_WDCR0, ~_BIT7, _BIT7);
            }
        }
    }
    else
    {
        if((ucWDType & _HDMI_AVI_INFO_VARIATION_WD) == _HDMI_AVI_INFO_VARIATION_WD)
        {
            // Disable packet variation Watch Dog
            ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_41_PORT_PAGE74_HDMI_VWDSR, ~_BIT0, 0x00);

            ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_45_PORT_PAGE74_HDMI_PVGCR0, 0x00);

            ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_46_PORT_PAGE74_HDMI_PVGCR1, ~_BIT0, 0x00);
        }

        if((ucWDType & _HDMI_AV_MUTE_WD) == _HDMI_AV_MUTE_WD)
        {
            // Disable AV Mute Watch Dog
            ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_31_PORT_PAGE74_HDMI_WDCR0, ~_BIT7, 0x00);
        }
    }
}

#if(_HDMI_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get AMD SPD Info Contents
// Input Value  : Content of Interest
// Output Value : Content Value
//--------------------------------------------------
BYTE ScalerTMDSRx5HdmiGetAmdSpdInfo(EnumAmdSpdInfoContent enumContent)
{
    if(GET_TMDS_RX5_SPD_INFO_FRAME_RECEIVED() == _TRUE)
    {
        // Get AMD OUI
        ScalerGetDataPortByte(P74_CD_HDMI_PSAP, 0x90, 3, pData, _AUTOINC);
        if((pData[0] == 0x1A) && (pData[1] == 0x00) && (pData[2] == 0x00))
        {
            switch(enumContent)
            {
                case _SPD_INFO_FREESYNC_SUPPORT:

                    return ((bit)ScalerGetDataPortBit(P74_CD_HDMI_PSAP, 0x95, _BIT0));

                case _SPD_INFO_FREESYNC_ENABLE:

                    return ((bit)ScalerGetDataPortBit(P74_CD_HDMI_PSAP, 0x95, _BIT1));

                case _SPD_INFO_FREESYNC_ACTIVE:

                    return ((bit)ScalerGetDataPortBit(P74_CD_HDMI_PSAP, 0x95, _BIT2));

                case _SPD_INFO_FREESYNC_MIN_VFREQ:

                    ScalerGetDataPortByte(P74_CD_HDMI_PSAP, 0x96, 1, pData, _AUTOINC);

                    if(((WORD)pData[0] * 10) < _PANEL_FREESYNC_MIN_FRAME_RATE)
                    {
                        pData[0] = _PANEL_FREESYNC_MIN_FRAME_RATE / 10;
                        DebugMessageRx5("Freesync SPD info abnormal", 0);
                    }
                    else if(((WORD)pData[0] * 10) > _PANEL_FREESYNC_MAX_FRAME_RATE)
                    {
                        pData[0] = _PANEL_FREESYNC_MAX_FRAME_RATE / 10;
                        DebugMessageRx5("Freesync SPD info abnormal", 1);
                    }

                    return pData[0];

                case _SPD_INFO_FREESYNC_MAX_VFREQ:

                    ScalerGetDataPortByte(P74_CD_HDMI_PSAP, 0x97, 1, pData, _AUTOINC);

                    if(((WORD)pData[0] * 10) < _PANEL_FREESYNC_MIN_FRAME_RATE)
                    {
                        pData[0] = _PANEL_FREESYNC_MIN_FRAME_RATE / 10;
                        DebugMessageRx5("Freesync SPD info abnormal", 0);
                    }
                    else if(((WORD)pData[0] * 10) > _PANEL_FREESYNC_MAX_FRAME_RATE)
                    {
                        pData[0] = _PANEL_FREESYNC_MAX_FRAME_RATE / 10;
                        DebugMessageRx5("Freesync SPD info abnormal", 1);
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

#endif // End of #if(_D5_HDMI_SUPPORT == _ON)

//--------------------------------------------------
// Description  : TMDS Power Off Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx5PowerOffProc(void)
{
    // Disable EDID read/ SCL toggle IRQ
    MCU_FE84_DDC5_EDID_IRQ = ((MCU_FE84_DDC5_EDID_IRQ & ~(_BIT3 | _BIT1)) | (_BIT2 | _BIT0));

    ScalerTMDSRx5FreqDetectDisable();
}

//--------------------------------------------------
// Description  : TMDS Freq. Detection IRQ Disable and Clear Clock Counter
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx5FreqDetectDisable(void)
{
    // Disable TMDS Freq. Detect IRQ
    ScalerSetBit(P74_E6_HDMI_FREQDET_CTRL, ~_BIT1, 0x00);
    ScalerSetBit(P74_EF_HDMI_ERROR_TH, ~_BIT7, 0x00);

    // Clear TMDS Clk Count
    g_usTMDSRx5ClkCount = 0;

#if(_D5_HDMI_2_0_SUPPORT == _ON)
    // Disable CED Function
    ScalerSetBit(P74_0B_HDMI_CTRL_0B, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);

    // Pop Up CED Error For Clear Error Counter
    ScalerSetBit(P74_0C_HDMI_CTRL_0C, ~_BIT7, _BIT7);

    // Disable CED Lock Transition IRQ & Flag
    ScalerSetBit(P74_17_HDMI_CTRL_17, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P74_18_HDMI_CTRL_18, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
#endif
}

//--------------------------------------------------
// Description  : Process Required when Switched to Active State
// Input Value  : Input Source
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx5FirstActiveProc(BYTE ucSourceType)
{
    ucSourceType = ucSourceType;
}

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
//--------------------------------------------------
// Description  : Initial Setting for TMDS Scanning Port(Power Normal)
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx5TMDSScanInitial(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

    // Set Power Saving DDC Debounce Counter
    g_usDDCDebounceCnt = _TMDS_DDC_DEBOUNCE_NORMAL;

    ScalerTMDSRx5Initial(ucInputPort);

    ScalerTMDSRx5InterruptInitial();
}

//--------------------------------------------------
// Description  : Signal Detection for TMDS(Power Saving)
// Input Value  : Input Port
// Output Value : True : TMDS Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerTMDSRx5TMDSPSPreDetect(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

    // DDC handshake Detected
    if(GET_TMDS_RX5_DDC_DETECTED() == _TRUE)
    {
        DebugMessageRx5("7. PowerSaving D5 DDC", 0);

        CLR_TMDS_RX5_DDC_DETECTED();

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
        SET_TMDS_RX5_TOGGLE_Z0();
#endif
        return _TRUE;
    }

    // Enable DDC Toggle IRQ
    if(((MCU_FE84_DDC5_EDID_IRQ & _BIT3) != _BIT3) && (GET_TMDS_RX5_DDC_DETECTED() != _TRUE))
    {
        MCU_FE84_DDC5_EDID_IRQ |= _BIT2;
        MCU_FE84_DDC5_EDID_IRQ |= _BIT3;
    }

    // Reset Freq. Detect Counter(Toggle) & Choose Measure Clk to TMDS Clk
    ScalerSetBit(P74_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT5 | _BIT4), 0x00);
    ScalerSetBit(P74_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);

    // Clear Freq. Stable Flag
    ScalerSetBit(P74_EF_HDMI_ERROR_TH, ~_BIT6, _BIT6);

    // Clear Unstable Flag
    ScalerSetBit(P74_E6_HDMI_FREQDET_CTRL, ~_BIT2, _BIT2);

    // Delay enough time for freq. measure (calculated for measure 5 times)
    ScalerTimerDelayXms(5);

    // Detect Freq. Measure Stable
    if((ScalerGetBit(P74_E6_HDMI_FREQDET_CTRL, (_BIT6 | _BIT2)) == _BIT6) && (ScalerGetBit(P74_EF_HDMI_ERROR_TH, _BIT6) == _BIT6))
    {
#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
        SET_TMDS_RX5_TOGGLE_Z0();
#endif
        return _TRUE;
    }
    else
    {
        // Disable Freq. Detection
        ScalerSetBit(P74_E6_HDMI_FREQDET_CTRL, ~_BIT7, 0x00);

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
bit ScalerTMDSRx5TMDSNormalPreDetect(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

    // DDC handshake Detected
    if(GET_TMDS_RX5_DDC_DETECTED() == _TRUE)
    {
        DebugMessageRx5("7. Normal D5 DDC", 0);

        CLR_TMDS_RX5_DDC_DETECTED();

        return _TRUE;
    }

    // Enable DDC Toggle IRQ
    if(((MCU_FE84_DDC5_EDID_IRQ & _BIT3) != _BIT3) && (GET_TMDS_RX5_DDC_DETECTED() != _TRUE))
    {
        MCU_FE84_DDC5_EDID_IRQ |= _BIT2;
        MCU_FE84_DDC5_EDID_IRQ |= _BIT3;

        CLR_TMDS_RX5_DDC_DETECTED();
    }

    ScalerTimerDelayXms(6);

    if(GET_TMDS_RX5_PHY_SET() == _TRUE)
    {
        return _TRUE;
    }

    return _FALSE;
}

#endif // End of #if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)

//--------------------------------------------------
// Description  : Check whether HDCP is enabled
// Input Value  : None
// Output Value : TRUE => HDCP Enabled
//--------------------------------------------------
bit ScalerTMDSRx5HdcpEnabled(void)
{
    BYTE pucHDCPFrameCount[2];
    memset(pucHDCPFrameCount, 0, sizeof(pucHDCPFrameCount));

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
    if((ScalerGetBit(P74_C0_HDCP_CR, _BIT0) == _BIT0) && (ScalerGetBit(P6E_26_HDCP_I2C_CTRL_0, _BIT7) == 0x00))
#endif
    {
        ScalerGetDataPortByte(P74_C3_HDCP_AP, _P74_C4_PT_C0_PORT_PAGE74_HDCP_FCR, 1, &pucHDCPFrameCount[0], _NON_AUTOINC);

        // Wait 2Vsync to make sure frame counter changing, and timeout 45ms (margin + 1/24 frame+rate)
        ScalerSetBit(P74_A4_TMDS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT3);
        ScalerTimerPollingFlagProc(45, P74_A4_TMDS_CTRL, _BIT3, _TRUE);
        ScalerSetBit(P74_A4_TMDS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT3);
        ScalerTimerPollingFlagProc(45, P74_A4_TMDS_CTRL, _BIT3, _TRUE);

        ScalerGetDataPortByte(P74_C3_HDCP_AP, _P74_C4_PT_C0_PORT_PAGE74_HDCP_FCR, 1, &pucHDCPFrameCount[1], _NON_AUTOINC);

        if(pucHDCPFrameCount[0] != pucHDCPFrameCount[1])
        {
            return _TRUE;
        }

        return _FALSE;
    }
#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
    else if((ScalerGetBit(P74_C0_HDCP_CR, _BIT0) == 0x00) && (ScalerGetBit(P6E_26_HDCP_I2C_CTRL_0, _BIT7) == _BIT7))
    {
        if(ScalerGetByte(P6E_2C_HDCP_I2C_CTRL_6) == 0x10)
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

//--------------------------------------------------
// Description  : Detect TMDS video mode
// Input Value  : bWait => Whether to wait then read
// Output Value : TMDS video type
//--------------------------------------------------
BYTE ScalerTMDSRx5TMDSVideoDetect(bit bWait)
{
    BYTE ucTemp = _TMDS_VIDEO_DATA_NONE;

    if(bWait == _WAIT)
    {
        // Wait at least 1 frame for HW auto update TMDS video RGBHV valid value
        ScalerTimerPollingFlagProc(45, P74_A4_TMDS_CTRL, _BIT3, _TRUE);

        // Wait for HW update DE flag
        if(ScalerTimerPollingFlagProc(20, P74_A4_TMDS_CTRL, (_BIT7 | _BIT6 | _BIT5), _TRUE) == _TRUE)
        {
            // H/Vsync received
            if(ScalerGetBit(P74_A4_TMDS_CTRL, (_BIT4 | _BIT3)) == (_BIT4 | _BIT3))
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

        CLR_TMDS_RX5_RGBHV_DETECTING();

        return ucTemp;
    }
    else
    {
        // R/G/B data detected
        if(ScalerGetBit(P74_A4_TMDS_CTRL, (_BIT7 | _BIT6 | _BIT5)) == (_BIT7 | _BIT6 | _BIT5))
        {
            // H/Vsync received
            if(ScalerGetBit(P74_A4_TMDS_CTRL, (_BIT4 | _BIT3)) == (_BIT4 | _BIT3))
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
        ScalerSetBit(P74_A4_TMDS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));

        SET_TMDS_RX5_RGBHV_DETECTING();

        // Activate TMDS video Detection Event
        ScalerTimerActiveTimerEvent(SEC(0.045), _SCALER_TIMER_EVENT_RX5_TMDS_VIDEO_DETECT);

        return ucTemp;
    }
}

//--------------------------------------------------
// Description  : TMDS video Detect Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx5TMDSVideoDetectEvent(void)
{
    CLR_TMDS_RX5_RGBHV_DETECTING();
}

//--------------------------------------------------
// Description  : Check CDR Locked
// Input Value  : Measured Clk Count to be compared
// Output Value : _TRUE => Stable
//--------------------------------------------------
bit ScalerTMDSRx5CheckCDRStable(WORD usClkCount)
{
#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

    if(GET_D5_TMDS_MODE() == _TMDS_MHL_MODE)
    {
        switch(GET_TMDS_RX5_CLK_MODE())
        {
            // Check if Packed Pixel Mode
            case _TMDS_MHL_PPMODE_PHY_SETTING:

                // Check Current Measured Freq. is the same as previously locked
                if(abs(usClkCount - (ScalerTMDSRx5MeasureClk(_CLK_SOURCE_RED) * 4)) > (usClkCount >> 6))
                {
                    DebugMessageRx5("R Channel CDR Unstable", ScalerTMDSRx5MeasureClk(_CLK_SOURCE_RED));
                    return _FALSE;
                }

                break;

            // Check if 24 Bit Mode
            case _TMDS_24BIT_PHY_SETTING:

                // Check Current Measured Freq. is the same as previously locked
                if(abs(usClkCount - (ScalerTMDSRx5MeasureClk(_CLK_SOURCE_RED) * 3)) > (usClkCount >> 6))
                {
                    DebugMessageRx5("R Channel CDR Unstable", ScalerTMDSRx5MeasureClk(_CLK_SOURCE_RED));
                    return _FALSE;
                }

                break;

#if(_D5_MHL_VERSION >= _MHL_VERSION_3_0)

            // Check if 1.5G, 3.0G, 6.0G Mode
            case _TMDS_MHL_ECBUS_PHY_SETTING:

                // Check Current Measured Freq. is the same as previously locked
                if(abs(usClkCount - (ScalerTMDSRx5MeasureClk(_CLK_SOURCE_RED) * GET_MHL3_RX5_AV_LINK_N_CODE())) > (usClkCount >> 5))
                {
                    DebugMessageRx5("R Channel CDR Unstable", (ScalerTMDSRx5MeasureClk(_CLK_SOURCE_RED)* GET_MHL3_RX5_AV_LINK_N_CODE()));
                    return _FALSE;
                }

                break;

#endif // End of #if(_D5_MHL_VERSION >= _MHL_VERSION_3_0)

            default:

                return _FALSE;
                break;
        }
    }
    else
#endif // End of #if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
    {
#if(_D5_HDMI_2_0_SUPPORT == _ON)

        if(GET_TMDS_RX5_HIGH_SPEED_MODE() == _TRUE)
        {
            // Check Current Measured Freq. is the same as previously locked
            if(abs(usClkCount - (ScalerTMDSRx5MeasureClk(_CLK_SOURCE_RED) * 4)) > (usClkCount >> 6))
            {
                return _FALSE;
            }

            if(abs(usClkCount - (ScalerTMDSRx5MeasureClk(_CLK_SOURCE_BLUE) * 4)) > (usClkCount >> 6))
            {
                return _FALSE;
            }

            if(abs(usClkCount - (ScalerTMDSRx5MeasureClk(_CLK_SOURCE_GREEN) * 4)) > (usClkCount >> 6))
            {
                return _FALSE;
            }
        }
        else
#endif
        {
            // Check Current Measured Freq. is the same as previously locked
            if(abs(usClkCount - ScalerTMDSRx5MeasureClk(_CLK_SOURCE_RED)) > (usClkCount >> 6))
            {
                DebugMessageRx5("R Channel CDR Unstable", ScalerTMDSRx5MeasureClk(_CLK_SOURCE_RED));
                return _FALSE;
            }

            if(abs(usClkCount - ScalerTMDSRx5MeasureClk(_CLK_SOURCE_BLUE)) > (usClkCount >> 6))
            {
                DebugMessageRx5("B Channel CDR Unstable", ScalerTMDSRx5MeasureClk(_CLK_SOURCE_BLUE));
                return _FALSE;
            }

            if(abs(usClkCount - ScalerTMDSRx5MeasureClk(_CLK_SOURCE_GREEN)) > (usClkCount >> 6))
            {
                DebugMessageRx5("G Channel CDR Unstable", ScalerTMDSRx5MeasureClk(_CLK_SOURCE_GREEN));
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
BYTE ScalerTMDSRx5CheckCDRStable_EXINT0(WORD usClkCount) using 1
{
#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
    if(GET_D5_TMDS_MODE() == _TMDS_MHL_MODE)
    {
        switch(GET_TMDS_RX5_CLK_MODE())
        {
            // Check if Packed Pixel Mode
            case _TMDS_MHL_PPMODE_PHY_SETTING:

                // Check Current Measured Freq. is the same as previously locked
                if(abs(usClkCount - ScalerTMDSRx5MeasureClk_EXINT0(_CLK_SOURCE_TMDS)) > (usClkCount >> 6))
                {
                    return _FALSE;
                }

                // Check Current Measured Freq. is the same as previously locked
                if(abs(usClkCount - (ScalerTMDSRx5MeasureClk_EXINT0(_CLK_SOURCE_RED) * 4)) > (usClkCount >> 6))
                {
                    return _FALSE;
                }

                break;

            // Check if 24 Bit Mode
            case _TMDS_24BIT_PHY_SETTING:

                // Check Current Measured Freq. is the same as previously locked
                if(abs(usClkCount - ScalerTMDSRx5MeasureClk_EXINT0(_CLK_SOURCE_TMDS)) > (usClkCount >> 6))
                {
                    return _FALSE;
                }

                // Check Current Measured Freq. is the same as previously locked
                if(abs(usClkCount - (ScalerTMDSRx5MeasureClk_EXINT0(_CLK_SOURCE_RED) * 3)) > (usClkCount >> 6))
                {
                    return _FALSE;
                }

                break;

#if(_D5_MHL_VERSION >= _MHL_VERSION_3_0)

            // Check if 1.5G, 3.0G, 6.0G Mode
            case _TMDS_MHL_ECBUS_PHY_SETTING:

                // Check Current Measured Freq. is the same as previously locked
                if(abs(usClkCount - ScalerTMDSRx5MeasureClk_EXINT0(_CLK_SOURCE_TMDS)) > (usClkCount >> 6))
                {
                    return _FALSE;
                }

                // Check Current Measured Freq. is the same as previously locked
                if(abs(usClkCount - (ScalerTMDSRx5MeasureClk_EXINT0(_CLK_SOURCE_RED) * GET_MHL3_RX5_AV_LINK_N_CODE())) > (usClkCount >> 5))
                {
                    return _FALSE;
                }

                break;

#endif // End of #if(_D5_MHL_VERSION >= _MHL_VERSION_3_0)

            default:

                return _FALSE;
                break;
        }
    }
    else
#endif // End of #if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
    {
#if(_D5_HDMI_2_0_SUPPORT == _ON)
        if(GET_TMDS_RX5_HIGH_SPEED_MODE() == _TRUE)
        {
            // Check Current Measured Freq. is the same as previously locked
            if(abs(usClkCount - ScalerTMDSRx5MeasureClk_EXINT0(_CLK_SOURCE_TMDS)) > (usClkCount >> 6))
            {
                return _FALSE;
            }

            if(abs(usClkCount - (ScalerTMDSRx5MeasureClk_EXINT0(_CLK_SOURCE_RED) * 4)) > (usClkCount >> 6))
            {
                return _FALSE;
            }

            if(abs(usClkCount - (ScalerTMDSRx5MeasureClk_EXINT0(_CLK_SOURCE_BLUE) * 4)) > (usClkCount >> 6))
            {
                return _FALSE;
            }

            if(abs(usClkCount - (ScalerTMDSRx5MeasureClk_EXINT0(_CLK_SOURCE_GREEN) * 4)) > (usClkCount >> 6))
            {
                return _FALSE;
            }
        }
        else
#endif
        {
            // Check Current Measured Freq. is the same as previously locked
            if(abs(usClkCount - ScalerTMDSRx5MeasureClk_EXINT0(_CLK_SOURCE_TMDS)) > (usClkCount >> 6))
            {
                return _FALSE;
            }

            if(abs(usClkCount - ScalerTMDSRx5MeasureClk_EXINT0(_CLK_SOURCE_RED)) > (usClkCount >> 6))
            {
                return _FALSE;
            }

            if(abs(usClkCount - ScalerTMDSRx5MeasureClk_EXINT0(_CLK_SOURCE_BLUE)) > (usClkCount >> 6))
            {
                return _FALSE;
            }

            if(abs(usClkCount - ScalerTMDSRx5MeasureClk_EXINT0(_CLK_SOURCE_GREEN)) > (usClkCount >> 6))
            {
                return _FALSE;
            }
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Initialize TMDS setting for search
// Input Value  : Current Search Port
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx5Initial(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

#if((_D5_INPUT_PORT_TYPE == _D5_MHL_PORT) && (_D5_MHL_VERSION >= _MHL_VERSION_3_0))
    // Disable MHL3 Output
    ScalerSetBit(P79_10_REG_MHL3_OUTPUT_0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
#endif

    // Disable TMDS output
    ScalerSetBit(P74_A6_TMDS_OUTCTL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

    // Set HS Width(DE only) and HDCP Reference VS
    ScalerSetBit(P74_AB_TMDS_ACC2, ~(_BIT7 | _BIT6), 0x00);

    // Set TMDS Hsync/Vsync Polarity as Input Raw Polarity
    ScalerSetBit(P74_AF_TMDS_WDC, ~(_BIT3 | _BIT2), 0x00);

    // Disable C9/CA Port Auto-Inc
    ScalerSetBit(P74_C8_HDMI_APC, ~_BIT0, 0x00);

#if(_D5_HDMI_SUPPORT == _ON)

    ScalerTMDSRx5HdmiWatchDog((_HDMI_AVI_INFO_VARIATION_WD | _HDMI_AV_MUTE_WD), _DISABLE);

    // Deep Color Mode clock and detection auto
    ScalerSetBit(P74_B8_TMDS_DPC1, ~(_BIT3 | _BIT2), _BIT2);

    // Enable BCH Detection
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_02_PORT_PAGE74_HDMI_BCHCR, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1), (_BIT6 | _BIT3 | _BIT2 | _BIT1));

    // DVI mode don't disable Audio Clk
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_00_PORT_PAGE74_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

    // Set Video Watch Dog New Mode
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_32_PORT_PAGE74_HDMI_WDCR1, ~_BIT5, _BIT5);

    // Specify Packet Detect Type
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_43_PORT_PAGE74_HDMI_PTRSV0, _HDMI_AVI_INFO_TYPE);
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_44_PORT_PAGE74_HDMI_PTRSV1, _HDMI_GENERAL_CONTROL_TYPE);

#if(_HDMI_FREESYNC_SUPPORT == _ON)
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_A4_PORT_PAGE74_HDMI_PTRSV_2, _SPD_INFO_TYPE);
#endif

    // Packet Variation Detect Disable
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_45_PORT_PAGE74_HDMI_PVGCR0, 0x00);
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_46_PORT_PAGE74_HDMI_PVGCR1, 0x00);
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_47_PORT_PAGE74_HDMI_PVGCR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_A9_PORT_PAGE74_HDMI_PVSR_4, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
    ScalerSetDataPortByte(P74_C9_HDMI_AP, _P74_CA_PT_AA_PORT_PAGE74_HDMI_PVGCR3, 0x00);
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_AB_PORT_PAGE74_HDMI_PVGCR4, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

#if(_D5_HDMI_2_0_SUPPORT == _ON)

    if(ScalerGetBit(P74_E6_HDMI_FREQDET_CTRL, _BIT1) == 0x00)
    {
        // Disable HDMI 2.0 SCDC Function
        ScalerSetBit(P74_19_HDMI_CTRL_19, ~_BIT7, 0x00);

        CLR_TMDS_RX5_HIGH_SPEED_MODE();
    }

    // Disable SCDC Scrambling Status
    ScalerSetDataPortBit(P74_39_HDMI_CTRL_39, _P74_3A_PT_21_PORT_PAGE74_HDMI_SCDC_21, ~_BIT0, 0x00);

    // Set Scrambling detection SSCP Number = 8, Enable HW Auto Detect Scrambling Control Symbol
    ScalerSetBit(P74_01_HDMI_CTRL_01, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT2 | _BIT1 | _BIT0));

    // Set SCDC Port not auto increase
    ScalerSetBit(P74_38_HDMI_CTRL_38, ~(_BIT4 | _BIT0), _BIT4);

    // Disable Ignore Source Transimit Read Request Enable
    ScalerSetBit(P74_1C_HDMI_CTRL_1C, ~_BIT2, 0x00);

    // Enable HDMI 2.0 Function
    ScalerSetBit(P74_00_HDMI_CTRL_00, ~_BIT0, _BIT0);

    // Enable HDMI 2.0 SCDC Module
    ScalerSetBit(P74_19_HDMI_CTRL_19, ~_BIT7, _BIT7);

#else

    // Disable HDMI 2.0 Function
    ScalerSetBit(P74_00_HDMI_CTRL_00, ~_BIT0, 0x00);

    // Disable HDMI 2.0 SCDC Function
    ScalerSetBit(P74_19_HDMI_CTRL_19, ~_BIT7, 0x00);
#endif

#endif // End of #if(_D5_HDMI_SUPPORT == _ON)

    // Set HDCP DDC Channel
    ScalerSetBit(P74_C2_HDCP_PCR, ~(_BIT2 | _BIT1), 0x00);

    // Set HDCP DDC Debounce, TMDS Function
    ScalerSetBit(P74_AC_TMDS_Z0CC2, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

    // Set D5 Port HDCP Address is 0x74
    ScalerSetDataPortBit(P74_C3_HDCP_AP, _P74_C4_PT_C2_PORT_PAGE74_HDCP_SLAVE_ADD, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x3A);

    // Set HDCP Feature
#if(_D5_HDMI_SUPPORT == _ON)

#if(_TMDS_HDCP_FEATURE == _HDCP_FEATURE_1_0)
    ScalerSetDataPortByte(P74_C3_HDCP_AP, _P74_C4_PT_40_PORT_PAGE74_BCAPS, 0x81);
#elif(_TMDS_HDCP_FEATURE == _HDCP_FEATURE_1_1)
    ScalerSetDataPortByte(P74_C3_HDCP_AP, _P74_C4_PT_40_PORT_PAGE74_BCAPS, 0x83);
#else
    ScalerSetDataPortByte(P74_C3_HDCP_AP, _P74_C4_PT_40_PORT_PAGE74_BCAPS, 0x81);
#endif

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
    // Set Support HDCP 2.2 Feature
    ScalerSetDataPortByte(P74_C3_HDCP_AP, _P74_C4_PT_50_PORT_PAGE74_HDCP2_VER, 0x04);

    g_pucTmdsRx5Caps[0] = 0x02;
    g_pucTmdsRx5Caps[1] = 0x00;
    g_pucTmdsRx5Caps[2] = 0x00;
#endif

#else // Else of #if(_D5_HDMI_SUPPORT == _ON)

#if(_TMDS_HDCP_FEATURE == _HDCP_FEATURE_1_0)
    ScalerSetDataPortByte(P74_C3_HDCP_AP, _P74_C4_PT_40_PORT_PAGE74_BCAPS, 0x01);
#elif(_TMDS_HDCP_FEATURE == _HDCP_FEATURE_1_1)
    ScalerSetDataPortByte(P74_C3_HDCP_AP, _P74_C4_PT_40_PORT_PAGE74_BCAPS, 0x03);
#else
    ScalerSetDataPortByte(P74_C3_HDCP_AP, _P74_C4_PT_40_PORT_PAGE74_BCAPS, 0x01);
#endif

#endif // End of #if(_D5_HDMI_SUPPORT == _ON)

#if(_D5_HDMI_2_0_SUPPORT == _ON)
    // Enable New Advance Cipher Mode
    ScalerSetBit(P74_C0_HDCP_CR, ~_BIT7, _BIT7);
#else
    // Disable HDMI 2.0 Function
    ScalerSetBit(P74_00_HDMI_CTRL_00, ~_BIT0, 0x00);

    // Enable New Advance Cipher Mode, Enable HDCP Module
    ScalerSetBit(P74_C0_HDCP_CR, ~(_BIT7 | _BIT0), (_BIT7 | _BIT0));
#endif

    // Disable HDMI MAC Global Power Down
    ScalerSetBit(P74_AD_TMDS_CPS, ~_BIT1, 0x00);

    // Enable MAC Input
    ScalerSetBit(P74_A7_TMDS_PWDCTL, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Set MAC Signal Swap
    ScalerSetBit(P74_A7_TMDS_PWDCTL, ~(_BIT6 | _BIT5), ((_D5_TMDS_BR_SWAP << 6) | (_D5_TMDS_PN_SWAP << 5)));

    // Auto switch to DVI when no signal
    ScalerSetBit(P74_AD_TMDS_CPS, ~_BIT2, _BIT2);

    // Detect TMDS Format by Data Island Packet Preamble & Guard Band
    ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_00_PORT_PAGE74_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT4 | _BIT1), _BIT1);

    // Enable TMDS MAC Error Correction
    ScalerSetBit(P74_B7_TMDS_UDC2, ~(_BIT7 | _BIT6 | _BIT5), (_BIT6 | _BIT5));

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
    if(GET_D5_TMDS_MODE() == _TMDS_MHL_MODE)
    {
        // Enable MHL Mac and Set MHL MAC Signal Swap
        ScalerSetBit(P79_A0_MHL_CTRL_00, ~(_BIT5 | _BIT0), ((_D5_TMDS_PN_SWAP << 5) | _BIT0));

        // Enable New Algorithm for Packed Pixel Mode
        ScalerSetBit(P79_A1_MHL_CTRL_01, ~_BIT7, _BIT7);

        // Guard Band reference enable for data remapping
        ScalerSetBit(P79_B2_MHL_CTRL_12, ~_BIT7, _BIT7);

        // Set 24Bit Mode Threshold
        ScalerSetByte(P79_AA_MHL_CTRL_0A, 0x00);
        ScalerSetByte(P79_AB_MHL_CTRL_0B, 0x09);

        // Set PP Mode Threshold
        ScalerSetByte(P79_AC_MHL_CTRL_0C, 0x00);
        ScalerSetByte(P79_AD_MHL_CTRL_0D, 0x09);

        // Set Detection Period
        ScalerSetByte(P79_A8_MHL_CTRL_08, 0x69);
        ScalerSetByte(P79_A9_MHL_CTRL_09, 0x78);

        // Set Detection by Video Leading and Detection Period by Xtal
        ScalerSetBit(P79_A7_MHL_CTRL_07, ~(_BIT4 | _BIT3 | _BIT2 | _BIT0), _BIT2);
    }
    else
#endif
    {
        // Disable MHL Mac and Revert CDR Data Polarity
        ScalerSetBit(P79_A0_MHL_CTRL_00, ~(_BIT5 | _BIT0), 0x00);

        // Guard Band reference disable for data remapping
        ScalerSetBit(P79_B2_MHL_CTRL_12, ~_BIT7, 0x00);

#if(_D5_HDMI_2_0_SUPPORT == _OFF)
        // Set HDMI/DVI switch to Auto Mode
        ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_00_PORT_PAGE74_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT3), 0x00);
#endif
    }
}

//--------------------------------------------------
// Description  : TMDS Power Saving Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx5PowerSavingProc(void)
{
    // Set Power Saving DDC Debounce Counter
    g_usDDCDebounceCnt = _TMDS_DDC_DEBOUNCE_PS;

    ScalerTMDSRx5FreqDetectDisable();

    // Switch TMDS Input/Output to Auto
    ScalerSetBit(P74_A6_TMDS_OUTCTL, ~_BIT7, _BIT7);
    ScalerSetBit(P74_A7_TMDS_PWDCTL, ~_BIT4, _BIT4);

    // Set Freq. Stable Time: 5 times
    ScalerSetByte(P74_EC_HDMI_FREQDET_STABLE, 0x05);

    // Set Freq. Shift Offset to Max
    ScalerSetBit(P74_E7_HDMI_FREQDET_OFFSET, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
    if(GET_D5_TMDS_MODE() == _TMDS_MHL_MODE)
    {
        // Set Upper Bound
        ScalerSetByte(P74_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_MHL_FREQ_PS_UPPER_BOUND));
        ScalerSetByte(P74_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_MHL_FREQ_PS_UPPER_BOUND));
    }
    else
#endif
    {
#if(_TMDS_LOW_SPEED_PORT_SPEED_LIMIT == _OFF)
        // Set Upper Bound
        ScalerSetByte(P74_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_PS_HIGH_SPEED_UPPER_BOUND));
        ScalerSetByte(P74_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_PS_HIGH_SPEED_UPPER_BOUND));
#else
        ScalerSetByte(P74_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_PS_LOW_SPEED_UPPER_BOUND));
        ScalerSetByte(P74_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_PS_LOW_SPEED_UPPER_BOUND));
#endif
    }

    // Set Lower Bound
    ScalerSetByte(P74_EA_HDMI_FREQDET_LOWER_M, HIBYTE(_TMDS_FREQ_PS_LOWER_BOUND));
    ScalerSetByte(P74_EB_HDMI_FREQDET_LOWER_L, LOBYTE(_TMDS_FREQ_PS_LOWER_BOUND));
}

#if(_D5_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Hdmi Handle AVMute Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx5HdmiAVMuteProc(void)
{
#if((_D5_INPUT_PORT_TYPE == _D5_MHL_PORT) && (_D5_MHL_VERSION >= _MHL_VERSION_3_0))

    if((GET_D5_TMDS_MODE() == _TMDS_MHL_MODE) && (GET_MHL3_RX5_ECBUS_MODE() == _ON))
    {
        if((ScalerGetBit(P74_CB_HDMI_SR, _BIT6) == 0x00) && (ScalerGetBit(P79_10_REG_MHL3_OUTPUT_0, _BIT3) == _BIT3))
        {
            // Clear AVMute Flag
            ScalerSetBit(P74_CB_HDMI_SR, ~_BIT7, _BIT7);

            // Disable AVMute Watch Dog
            ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_31_PORT_PAGE74_HDMI_WDCR0, ~_BIT7, 0x00);
            ScalerSetBit(P79_10_REG_MHL3_OUTPUT_0, ~_BIT3, 0x00);

            // Enable Video/Audio Output
            ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_30_PORT_PAGE74_HDMI_AVMCR, ~(_BIT5 | _BIT3), (_BIT5 | _BIT3));

            // Enable AVMute Watch Dog
            ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_31_PORT_PAGE74_HDMI_WDCR0, ~_BIT7, _BIT7);
            ScalerSetBit(P79_10_REG_MHL3_OUTPUT_0, ~_BIT3, _BIT3);
        }
    }
    else
#endif // End of #if((_D5_INPUT_PORT_TYPE == _D5_MHL_PORT) && (_D5_MHL_VERSION >= _MHL_VERSION_3_0))
    {
        // if AVMute Has been triggered
        if((ScalerGetBit(P74_CB_HDMI_SR, _BIT6) == 0x00) && (ScalerGetBit(P74_A6_TMDS_OUTCTL, (_BIT6 | _BIT5 | _BIT4)) == 0x00))
        {
            // Clear AVMute Flag
            ScalerSetBit(P74_CB_HDMI_SR, ~_BIT7, _BIT7);

            // Disable AVMute Watch Dog
            ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_31_PORT_PAGE74_HDMI_WDCR0, ~_BIT7, 0x00);

            // Enable Video/Audio Output
            ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_30_PORT_PAGE74_HDMI_AVMCR, ~(_BIT5 | _BIT3), (_BIT5 | _BIT3));

            // Enable RGB Output
            ScalerSetBit(P74_A6_TMDS_OUTCTL, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));

            // Enable AVMute Watch Dog
            ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_31_PORT_PAGE74_HDMI_WDCR0, ~_BIT7, _BIT7);
        }
    }
}
#endif

//--------------------------------------------------
// Description  : Detect TMDS Format
// Input Value  : None
// Output Value : Return DVI or HDMI format
//--------------------------------------------------
BYTE ScalerTMDSRx5FormatDetect(void)
{
    // Polling at least 3 frame for HW auto detect TMDS format
    if(ScalerTimerPollingFlagProc(130, P74_CB_HDMI_SR, _BIT0, _TRUE) == _TRUE)
    {
        ScalerSetBit(P74_AF_TMDS_WDC, ~_BIT0, 0x00);

#if(_D5_HDMI_2_0_SUPPORT == _ON)
        if(GET_D5_TMDS_MODE() == _TMDS_HDMI_MODE)
        {
            // Check if HDMI 2.0 ON
            if(ScalerGetBit(P74_00_HDMI_CTRL_00, _BIT0) == _BIT0)
            {
                // Set Manual Format to HDMI
                ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_00_PORT_PAGE74_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT3 | _BIT2));

                // Toggle HW Format Detect Flag Reset
                ScalerSetBit(P74_01_HDMI_CTRL_01, ~(_BIT7 | _BIT3), _BIT7);
                ScalerSetBit(P74_01_HDMI_CTRL_01, ~(_BIT7 | _BIT3), 0x00);

                SET_TMDS_RX5_HDMI_2_0_FORMAT_RESET_WAITING();

                ScalerTimerReactiveTimerEvent(130, _SCALER_TIMER_EVENT_RX5_HDMI2_FORMAT_RESET_WAIT);
            }

            // Detect Scrambling Control Symbol
            if(ScalerGetBit(P74_01_HDMI_CTRL_01, _BIT3) == _BIT3)
            {
                // Enable Scrambling Status in SCDC
                ScalerSetDataPortBit(P74_39_HDMI_CTRL_39, _P74_3A_PT_21_PORT_PAGE74_HDMI_SCDC_21, ~_BIT0, _BIT0);
            }
        }
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

        if(GET_D5_TMDS_MODE() == _TMDS_MHL_MODE)
        {
            // Set Manual Format to HDMI
            ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_00_PORT_PAGE74_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT3 | _BIT2));
        }
#endif
        return _SOURCE_HDMI;
    }
    else
    {
        ScalerSetBit(P74_AF_TMDS_WDC, ~_BIT0, _BIT0);

        if(GET_D5_TMDS_MODE() == _TMDS_HDMI_MODE)
        {
#if(_D5_HDMI_2_0_SUPPORT == _ON)
            if(ScalerGetBit(P74_00_HDMI_CTRL_00, _BIT0) == _BIT0)
            {
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX5_HDMI2_FORMAT_RESET_WAIT);
            }
#endif
            // Set Format Detect HW Auto Mode
            ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_00_PORT_PAGE74_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), 0x00);
        }
#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
        else
        {
            // Manual Set to DVI Mode
            ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_00_PORT_PAGE74_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), _BIT3);
        }
#endif
        return _SOURCE_DVI;
    }
}
#endif // End of #if(_D5_TMDS_SUPPORT == _ON)
