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
// ID Code      : SysSource.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SYSTEM_SOURCE__

#include "SysInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

#if(_MULTI_DISPLAY_MAX == 0x04)
#define GET_SOURCE_ALL_JUDGED()             (\
                                                (GET_MODE_DISPLAY_MODE() == _DISPLAY_MODE_4P) ?\
                                                ((GET_RGN_SOURCE_JUDGE(0) == _TRUE) &&\
                                                 (GET_RGN_SOURCE_JUDGE(1) == _TRUE) &&\
                                                 (GET_RGN_SOURCE_JUDGE(2) == _TRUE) &&\
                                                 (GET_RGN_SOURCE_JUDGE(3) == _TRUE)) :\
                                                ((GET_MODE_DISPLAY_MODE() > _DISPLAY_MODE_1P) ?\
                                                 ((GET_RGN_SOURCE_JUDGE(0) == _TRUE) &&\
                                                  (GET_RGN_SOURCE_JUDGE(1) == _TRUE)) :\
                                                 (GET_RGN_SOURCE_JUDGE(0) == _TRUE))\
                                            )
#elif(_MULTI_DISPLAY_MAX == 0x02)
#define GET_SOURCE_ALL_JUDGED()             (\
                                                (GET_MODE_DISPLAY_MODE() > _DISPLAY_MODE_1P) ?\
                                                ((GET_RGN_SOURCE_JUDGE(0) == _TRUE) &&\
                                                 (GET_RGN_SOURCE_JUDGE(1) == _TRUE)) :\
                                                (GET_RGN_SOURCE_JUDGE(0) == _TRUE)\
                                            )
#elif(_MULTI_DISPLAY_MAX == 0x01)
#define GET_SOURCE_ALL_JUDGED()             (GET_RGN_SOURCE_JUDGE(0) == _TRUE)
#endif

//--------------------------------------------------
// Macro of Getting Input Port Type
//--------------------------------------------------
#define GET_INPUTPORT_TYPE(x)               (g_pucINPUT_PORT_TYPE[g_pucSourceSearchPriority[x]])

//--------------------------------------------------
// Macro of Getting Input Port Group Type
//--------------------------------------------------
#define GET_INPUTPORT_GROUP(x)              (g_pucSourceSearchGroup[g_pucSourceSearchPriority[x]])


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************
BYTE g_pucINPUT_PORT_TYPE[] =
{
    _A0_INPUT_PORT_TYPE,
    _D0_INPUT_PORT_TYPE,
    _D1_INPUT_PORT_TYPE,
    _D2_INPUT_PORT_TYPE,
    _D3_INPUT_PORT_TYPE,
    _D4_INPUT_PORT_TYPE,
    _D5_INPUT_PORT_TYPE,
    _D6_INPUT_PORT_TYPE,
    _D7_INPUT_PORT_TYPE,
};


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructSourceInfoType g_pstSourceInfo[_INPUT_PORT_VALID];
StructSourceInfoType g_stSourceInfoBackup;
// SourceInfo bit[0:2] -- Source Type
//#define _SOURCE_NONE                      0
//#define _SOURCE_VGA                       1
//#define _SOURCE_DVI                       2
//#define _SOURCE_HDMI                      3
//#define _SOURCE_DP                        4
//#define _SOURCE_MHL                       5
//#define _SOURCE_HDMI20                    6
//                                        = 000 => no Source
//                                        = 001 => VGA Source
//                                        = 010 => DVI Source
//                                        = 011 => HDMI Source
//                                        = 100 => DP Source
//                                        = 101 => Video Source
//                                        = 110 => HDMI 2.0 Source
//                                        = 111 => Dual DVI

// SourceInfo bit[3:4] -- Source Search Times
//                                     = 0~3 => Counter

// SourceInfo bit[5] -- Cable detect
//            = 0 => No
//            = 1 => Yes

// SourceInfo bit[7] -- Source Chosen
//                                      = 0 => Unchosen
//                                      = 1 => Chosen

BYTE g_ucSearchIndex;

BYTE g_ucSourceMeasureTargetIndex;

StructInputInfoType g_stInputInfo;

BYTE g_pucSourceSearchPriority[9] =
{
    _INPUT_PORT_SEARCH_PRI_0, _INPUT_PORT_SEARCH_PRI_1,
    _INPUT_PORT_SEARCH_PRI_2, _INPUT_PORT_SEARCH_PRI_3,
    _INPUT_PORT_SEARCH_PRI_4, _INPUT_PORT_SEARCH_PRI_5,
    _INPUT_PORT_SEARCH_PRI_6, _INPUT_PORT_SEARCH_PRI_7,
    _INPUT_PORT_SEARCH_PRI_8,
};

BYTE g_pucSourceSearchGroup[9] =
{
    _A0_INPUT_PORT_GROUP, _D0_INPUT_PORT_GROUP,
    _D1_INPUT_PORT_GROUP, _D2_INPUT_PORT_GROUP,
    _D3_INPUT_PORT_GROUP, _D4_INPUT_PORT_GROUP,
    _D5_INPUT_PORT_GROUP, _D6_INPUT_PORT_GROUP,
    _D7_INPUT_PORT_GROUP
};

#if(_VGA_PORT_EXIST == _ON)
WORD g_usSourceDefaultSearchTimeVga;
WORD g_usSourceNoCableSearchTimeVga;
#endif

#if(_HDMI_PORT_EXIST == _ON)
WORD g_usSourceDefaultSearchTimeHdmi;
WORD g_usSourceNoCableSearchTimeHdmi;
#endif

#if(_DVI_PORT_EXIST == _ON)
WORD g_usSourceDefaultSearchTimeDvi;
WORD g_usSourceNoCableSearchTimeDvi;
#endif

#if(_DP_PORT_EXIST == _ON)
WORD g_usSourceDefaultSearchTimeDp;
WORD g_usSourceNoCableSearchTimeDp;
#endif

StructPortCableStatus g_stPortCableStatus;

#if(_DP_SUPPORT == _ON)
#if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)
BYTE g_ucD6SwitchSelect = _NO_INPUT_PORT;
bit g_bD6SwitchPowerStatus = _DISABLE;
#endif

#if(_D7_INPUT_PORT_TYPE != _D7_NO_PORT)
BYTE g_ucD7SwitchSelect = _D7_INPUT_PORT;
#endif

bit g_bDpAutoSearchSwitch = _DISABLE;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void SysSourceHandler(void);
void SysSourceDetectPort(void);
void SysSourceClearDetectingEvent(void);
void SysSourceSearchTimeInitial(void);
void SysSourceJudge(void);
void SysSourceSwitchPort(void);
void SysSource1pSwitchPort(void);

#if(_MULTI_DISPLAY_MAX != 0x01)
void SysSourceMultiSwitchPort(void);
#endif

void SysSourceScanPortInitial(void);
void SysSourceInitial(void);
bit SysSourceStableCheck(BYTE ucRegionIndex);
BYTE SysSourceGetSourceType(void);
BYTE SysSourceGetInputPort(void);
BYTE SysSourceGetSpecificInputPort(BYTE ucIndex);
BYTE SysSourceGetInputPortType(BYTE ucInputPort);

#if((_SLEEP_AUDIO_SUPPORT == _ON) && ((_DP_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP))))
BYTE SysSourceGetAudioPlaybackPort(void);
#endif

void SysSourceSwitchInputPort(BYTE ucInputPort);
void SysSourceSwitchRegionSearchPort(BYTE ucInputPort);

void SysSourceSearchTimeReset(void);
void SysSourceInfoResetToDisplayInitial(void);
void SysSourceInfoReset(void);
void SysSourceResetRegion(BYTE ucRegionIndex);

void SysSourceCableDetection(void);
bit SysSourceCheckTargetTimes(BYTE ucTargetTimes);
void SysSourceSetScanType(BYTE ucScanType);
BYTE SysSourceGetScanType(void);
BYTE SysSourceConvertSearchPort(BYTE ucInputPort);
bit SysSourceGetCableDetect(BYTE ucInputPort);
bit SysSourceGetCableStatusChange(BYTE ucInputPort);

void SysSourceCableResetProc(void);
void SysSourceFirstActiveProc(void);
void SysSourcePowerOffProc(void);
void SysSourceSetSearchPriority(EnumSourceSearchPort enumPort, EnumSourceSearchPortPriority enumSourcePriority);
void SysSourceSetSearchGroup(EnumSourceSearchPort enumPort, EnumSourceSearchGroup enumSourceGroup);
void SysSourceSetDefaultSearchTime(EnumSourceInputType enumInputType, WORD usDefaultSearchTime);
void SysSourceSetNoCableSearchTime(EnumSourceInputType enumInputType, WORD usNoCableSearchTime);

#if(_MULTI_DISPLAY_MAX != 0x01)
bit SysSourceCheckMultiFixedPortTarget(BYTE ucSearchIndex);
bit SysSourceCheckMultiAutoSearchTarget(BYTE ucSearchIndex);
#endif

void SysSourceSetMultiAutoSearchTarget(EnumDisplayRegion enumDisplayRegion);

void SysSourceInterfaceSwitch(BYTE ucInputPort, BYTE ucPortType, BYTE ucSourceSearchDelayMode);

void SysSourceMeasureProc(void);
bit SysSourceUpdateMeasureTarget(void);
void SysSourceMeasureInputTiming(void);

#if(_MULTI_DISPLAY_MAX != 0x01)
bit SysSourceDuplicateInputTiming(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : Source Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceHandler(void)
{
    SysSourceCableDetection();

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if((ScalerSyncCheckUrgentEvent() == _TRUE) &&
       ((GET_POWER_STATUS() == _POWER_STATUS_NORMAL) ||
        (GET_POWER_STATUS() == _POWER_STATUS_FAKE_SAVING) ||
        (GET_POWER_STATUS() == _POWER_STATUS_NOSUPPORT_SAVING)))
    {
        return;
    }
#endif

    if((GET_MODE_STATE() != _MODE_STATUS_POWER_OFF) &&
       (GET_MODE_STATE() != _MODE_STATUS_INITIAL) &&
       (UserInterfaceGetForcePSStatus() == _FALSE))
    {
        if(GET_SOURCE_ALL_JUDGED() != _TRUE)
        {
            if(GET_SOURCE_DETECTING() == _FALSE)
            {
                SysSourceSwitchPort();
            }

            if(GET_SOURCE_JUDGE(g_ucSearchIndex) == _FALSE)
            {
                if(GET_SOURCE_SEARCH_PORT_INITIAL() == _TRUE)
                {
                    SysSourceScanPortInitial();

                    CLR_SOURCE_SEARCH_PORT_INITIAL();
                }

                if(GET_SOURCE_SEARCH_TIME_INITIAL() == _TRUE)
                {
                    SysSourceSearchTimeInitial();

                    CLR_SOURCE_SEARCH_TIME_INITIAL();
                }

                // Port Detection
                SysSourceDetectPort();

                // Decide if this port is about to be chosen
                SysSourceJudge();
            }
        }

        // Measure input source
        SysSourceMeasureProc();
    }

    CLR_MODE_STATE_CHANGE_SOURCE();
}

//--------------------------------------------------
// Description  : Port Detection
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceDetectPort(void)
{
    SET_SOURCE_TYPE(g_ucSearchIndex, _SOURCE_NONE);

    switch(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex)))
    {
        case _A0_INPUT_PORT:

            switch(GET_PORT_TYPE(GET_INPUTPORT_TYPE(g_ucSearchIndex)))
            {
#if(_VGA_SUPPORT == _ON)

                case _PORT_VGA:

                    if(GET_POWER_STATUS() == _POWER_STATUS_SAVING)
                    {
                        SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerSyncProcPreDetect());
                    }
                    else if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
                    {
                        SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerSyncProcPreDetect());

                        if((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE) && (GET_SOURCE_PREDETECT(g_ucSearchIndex) == _TRUE))
                        {
                            SET_SOURCE_TYPE(g_ucSearchIndex, SysVgaScanInputPort());
                        }
                    }

                    break;
#endif

                default:

                    break;
            }

            break;

        case _D0_INPUT_PORT:

            switch(GET_PORT_TYPE(GET_INPUTPORT_TYPE(g_ucSearchIndex)))
            {
#if((_D0_INPUT_PORT_TYPE == _D0_DVI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT))

                case _PORT_DVI:
                case _PORT_HDMI:

                    if(GET_POWER_STATUS() == _POWER_STATUS_SAVING)
                    {
                        SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerTMDSRx0TMDSPSPreDetect(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex))));
                    }
                    else if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
                    {
                        SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerTMDSRx0TMDSNormalPreDetect(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex))));

                        if((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE) && (GET_SOURCE_PREDETECT(g_ucSearchIndex) == _TRUE))
                        {
                            SET_SOURCE_TYPE(g_ucSearchIndex, ScalerTMDSRx0TMDSScanInputPort(GET_INPUTPORT_TYPE(g_ucSearchIndex)));
                        }
                    }

                    break;
#endif

#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

                case _PORT_MHL:

                    if(GET_D0_TMDS_MODE() == _TMDS_HDMI_MODE)
                    {
                        if(GET_POWER_STATUS() == _POWER_STATUS_SAVING)
                        {
                            SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerTMDSRx0TMDSPSPreDetect(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex))));
                        }
                        else if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
                        {
                            SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerTMDSRx0TMDSNormalPreDetect(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex))));

                            if((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE) && (GET_SOURCE_PREDETECT(g_ucSearchIndex) == _TRUE))
                            {
                                SET_SOURCE_TYPE(g_ucSearchIndex, ScalerTMDSRx0TMDSScanInputPort(GET_INPUTPORT_TYPE(g_ucSearchIndex)));
                            }
                        }
                    }
                    else if(GET_D0_TMDS_MODE() == _TMDS_MHL_MODE)
                    {
                        if(GET_POWER_STATUS() == _POWER_STATUS_SAVING)
                        {
                            SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerMHLRx0PSPreDetect());
                        }
                        else if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
                        {
                            SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerMHLRx0NormalPreDetect());

                            if((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE) && (GET_SOURCE_PREDETECT(g_ucSearchIndex) == _TRUE))
                            {
                                SET_SOURCE_TYPE(g_ucSearchIndex, ScalerTMDSRx0TMDSScanInputPort(GET_INPUTPORT_TYPE(g_ucSearchIndex)));
                            }
                        }
                    }
                    break;
#endif

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

                case _PORT_DP:

                    if(GET_POWER_STATUS() == _POWER_STATUS_SAVING)
                    {
                        SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerSyncDpPSPreDetect(SysSourceGetInputPort()));
                    }
                    else if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
                    {
                        SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerSyncDpNormalPreDetect(SysSourceGetInputPort()));

                        if((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE) && (GET_SOURCE_PREDETECT(g_ucSearchIndex) == _TRUE))
                        {
                            SET_SOURCE_TYPE(g_ucSearchIndex, ScalerSyncDpScanInputPort(SysSourceGetInputPort()));
                        }
                    }

                    break;
#endif

                default:

                    break;
            }

            break;

        case _D1_INPUT_PORT:

            switch(GET_PORT_TYPE(GET_INPUTPORT_TYPE(g_ucSearchIndex)))
            {
#if((_D1_INPUT_PORT_TYPE == _D1_DVI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT))

                case _PORT_DVI:
                case _PORT_HDMI:

                    if(GET_POWER_STATUS() == _POWER_STATUS_SAVING)
                    {
                        SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerTMDSRx1TMDSPSPreDetect(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex))));
                    }
                    else if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
                    {
                        SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerTMDSRx1TMDSNormalPreDetect(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex))));

                        if((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE) && (GET_SOURCE_PREDETECT(g_ucSearchIndex) == _TRUE))
                        {
                            SET_SOURCE_TYPE(g_ucSearchIndex, ScalerTMDSRx1TMDSScanInputPort(GET_INPUTPORT_TYPE(g_ucSearchIndex)));
                        }
                    }

                    break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

                case _PORT_MHL:

                    if(GET_D1_TMDS_MODE() == _TMDS_HDMI_MODE)
                    {
                        if(GET_POWER_STATUS() == _POWER_STATUS_SAVING)
                        {
                            SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerTMDSRx1TMDSPSPreDetect(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex))));
                        }
                        else if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
                        {
                            SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerTMDSRx1TMDSNormalPreDetect(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex))));

                            if((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE) && (GET_SOURCE_PREDETECT(g_ucSearchIndex) == _TRUE))
                            {
                                SET_SOURCE_TYPE(g_ucSearchIndex, ScalerTMDSRx1TMDSScanInputPort(GET_INPUTPORT_TYPE(g_ucSearchIndex)));
                            }
                        }
                    }
                    else if(GET_D1_TMDS_MODE() == _TMDS_MHL_MODE)
                    {
                        if(GET_POWER_STATUS() == _POWER_STATUS_SAVING)
                        {
                            SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerMHLRx1PSPreDetect());
                        }
                        else if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
                        {
                            SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerMHLRx1NormalPreDetect());

                            if((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE) && (GET_SOURCE_PREDETECT(g_ucSearchIndex) == _TRUE))
                            {
                                SET_SOURCE_TYPE(g_ucSearchIndex, ScalerTMDSRx1TMDSScanInputPort(GET_INPUTPORT_TYPE(g_ucSearchIndex)));
                            }
                        }
                    }
                    break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

                case _PORT_DP:

                    if(GET_POWER_STATUS() == _POWER_STATUS_SAVING)
                    {
                        SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerSyncDpPSPreDetect(SysSourceGetInputPort()));
                    }
                    else if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
                    {
                        SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerSyncDpNormalPreDetect(SysSourceGetInputPort()));

                        if((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE) && (GET_SOURCE_PREDETECT(g_ucSearchIndex) == _TRUE))
                        {
                            SET_SOURCE_TYPE(g_ucSearchIndex, ScalerSyncDpScanInputPort(SysSourceGetInputPort()));
                        }
                    }

                    break;
#endif

                default:

                    break;
            }

            break;

        case _D2_INPUT_PORT:

            switch(GET_PORT_TYPE(GET_INPUTPORT_TYPE(g_ucSearchIndex)))
            {
#if((_D2_INPUT_PORT_TYPE == _D2_DVI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT))

                case _PORT_DVI:
                case _PORT_HDMI:

                    if(GET_POWER_STATUS() == _POWER_STATUS_SAVING)
                    {
                        SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerTMDSRx2TMDSPSPreDetect(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex))));
                    }
                    else if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
                    {
                        SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerTMDSRx2TMDSNormalPreDetect(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex))));

                        if((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE) && (GET_SOURCE_PREDETECT(g_ucSearchIndex) == _TRUE))
                        {
                            SET_SOURCE_TYPE(g_ucSearchIndex, ScalerTMDSRx2TMDSScanInputPort(GET_INPUTPORT_TYPE(g_ucSearchIndex)));
                        }
                    }

                    break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)

                case _PORT_DUAL_DVI:

                    if(GET_POWER_STATUS() == _POWER_STATUS_SAVING)
                    {
                        SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerTMDSRx2DualDVIPSPreDetect(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex))));
                    }
                    else if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
                    {
                        SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerTMDSRx2DualDVINormalPreDetect(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex))));

                        if((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE) && (GET_SOURCE_PREDETECT(g_ucSearchIndex) == _TRUE))
                        {
                            SET_SOURCE_TYPE(g_ucSearchIndex, ScalerTMDSRx2DualDVIScanInputPort(GET_INPUTPORT_TYPE(g_ucSearchIndex)));
                        }
                    }

                    break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

                case _PORT_MHL:

                    if(GET_D2_TMDS_MODE() == _TMDS_HDMI_MODE)
                    {
                        if(GET_POWER_STATUS() == _POWER_STATUS_SAVING)
                        {
                            SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerTMDSRx2TMDSPSPreDetect(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex))));
                        }
                        else if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
                        {
                            SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerTMDSRx2TMDSNormalPreDetect(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex))));

                            if((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE) && (GET_SOURCE_PREDETECT(g_ucSearchIndex) == _TRUE))
                            {
                                SET_SOURCE_TYPE(g_ucSearchIndex, ScalerTMDSRx2TMDSScanInputPort(GET_INPUTPORT_TYPE(g_ucSearchIndex)));
                            }
                        }
                    }
                    else if(GET_D2_TMDS_MODE() == _TMDS_MHL_MODE)
                    {
                        if(GET_POWER_STATUS() == _POWER_STATUS_SAVING)
                        {
                            SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerMHLRx2PSPreDetect());
                        }
                        else if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
                        {
                            SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerMHLRx2NormalPreDetect());

                            if((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE) && (GET_SOURCE_PREDETECT(g_ucSearchIndex) == _TRUE))
                            {
                                SET_SOURCE_TYPE(g_ucSearchIndex, ScalerTMDSRx2TMDSScanInputPort(GET_INPUTPORT_TYPE(g_ucSearchIndex)));
                            }
                        }
                    }
                    break;
#endif

                default:

                    break;
            }

            break;

        case _D3_INPUT_PORT:

            switch(GET_PORT_TYPE(GET_INPUTPORT_TYPE(g_ucSearchIndex)))
            {
#if((_D3_INPUT_PORT_TYPE == _D3_DVI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT))

                case _PORT_DVI:
                case _PORT_HDMI:

                    if(GET_POWER_STATUS() == _POWER_STATUS_SAVING)
                    {
                        SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerTMDSRx3TMDSPSPreDetect(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex))));
                    }
                    else if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
                    {
                        SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerTMDSRx3TMDSNormalPreDetect(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex))));

                        if((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE) && (GET_SOURCE_PREDETECT(g_ucSearchIndex) == _TRUE))
                        {
                            SET_SOURCE_TYPE(g_ucSearchIndex, ScalerTMDSRx3TMDSScanInputPort(GET_INPUTPORT_TYPE(g_ucSearchIndex)));
                        }
                    }

                    break;
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT)

                case _PORT_DUAL_DVI:

                    if(GET_POWER_STATUS() == _POWER_STATUS_SAVING)
                    {
                        SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerTMDSRx3DualDVIPSPreDetect(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex))));
                    }
                    else if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
                    {
                        SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerTMDSRx3DualDVINormalPreDetect(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex))));

                        if((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE) && (GET_SOURCE_PREDETECT(g_ucSearchIndex) == _TRUE))
                        {
                            SET_SOURCE_TYPE(g_ucSearchIndex, ScalerTMDSRx3DualDVIScanInputPort(GET_INPUTPORT_TYPE(g_ucSearchIndex)));
                        }
                    }

                    break;
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)

                case _PORT_MHL:

                    if(GET_D3_TMDS_MODE() == _TMDS_HDMI_MODE)
                    {
                        if(GET_POWER_STATUS() == _POWER_STATUS_SAVING)
                        {
                            SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerTMDSRx3TMDSPSPreDetect(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex))));
                        }
                        else if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
                        {
                            SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerTMDSRx3TMDSNormalPreDetect(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex))));

                            if((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE) && (GET_SOURCE_PREDETECT(g_ucSearchIndex) == _TRUE))
                            {
                                SET_SOURCE_TYPE(g_ucSearchIndex, ScalerTMDSRx3TMDSScanInputPort(GET_INPUTPORT_TYPE(g_ucSearchIndex)));
                            }
                        }
                    }
                    else if(GET_D3_TMDS_MODE() == _TMDS_MHL_MODE)
                    {
                        if(GET_POWER_STATUS() == _POWER_STATUS_SAVING)
                        {
                            SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerMHLRx3PSPreDetect());
                        }
                        else if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
                        {
                            SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerMHLRx3NormalPreDetect());

                            if((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE) && (GET_SOURCE_PREDETECT(g_ucSearchIndex) == _TRUE))
                            {
                                SET_SOURCE_TYPE(g_ucSearchIndex, ScalerTMDSRx3TMDSScanInputPort(GET_INPUTPORT_TYPE(g_ucSearchIndex)));
                            }
                        }
                    }
                    break;

#endif

                default:

                    break;
            }

            break;

        case _D4_INPUT_PORT:

            switch(GET_PORT_TYPE(GET_INPUTPORT_TYPE(g_ucSearchIndex)))
            {
#if((_D4_INPUT_PORT_TYPE == _D4_DVI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT))

                case _PORT_DVI:
                case _PORT_HDMI:

                    if(GET_POWER_STATUS() == _POWER_STATUS_SAVING)
                    {
                        SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerTMDSRx4TMDSPSPreDetect(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex))));
                    }
                    else if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
                    {
                        SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerTMDSRx4TMDSNormalPreDetect(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex))));

                        if((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE) && (GET_SOURCE_PREDETECT(g_ucSearchIndex) == _TRUE))
                        {
                            SET_SOURCE_TYPE(g_ucSearchIndex, ScalerTMDSRx4TMDSScanInputPort(GET_INPUTPORT_TYPE(g_ucSearchIndex)));
                        }
                    }

                    break;
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)

                case _PORT_DUAL_DVI:

                    if(GET_POWER_STATUS() == _POWER_STATUS_SAVING)
                    {
                        SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerTMDSRx4DualDVIPSPreDetect(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex))));
                    }
                    else if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
                    {
                        SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerTMDSRx4DualDVINormalPreDetect(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex))));

                        if((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE) && (GET_SOURCE_PREDETECT(g_ucSearchIndex) == _TRUE))
                        {
                            SET_SOURCE_TYPE(g_ucSearchIndex, ScalerTMDSRx4DualDVIScanInputPort(GET_INPUTPORT_TYPE(g_ucSearchIndex)));
                        }
                    }

                    break;
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)

                case _PORT_MHL:

                    if(GET_D4_TMDS_MODE() == _TMDS_HDMI_MODE)
                    {
                        if(GET_POWER_STATUS() == _POWER_STATUS_SAVING)
                        {
                            SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerTMDSRx4TMDSPSPreDetect(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex))));
                        }
                        else if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
                        {
                            SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerTMDSRx4TMDSNormalPreDetect(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex))));

                            if((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE) && (GET_SOURCE_PREDETECT(g_ucSearchIndex) == _TRUE))
                            {
                                SET_SOURCE_TYPE(g_ucSearchIndex, ScalerTMDSRx4TMDSScanInputPort(GET_INPUTPORT_TYPE(g_ucSearchIndex)));
                            }
                        }
                    }
                    else if(GET_D4_TMDS_MODE() == _TMDS_MHL_MODE)
                    {
                        if(GET_POWER_STATUS() == _POWER_STATUS_SAVING)
                        {
                            SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerMHLRx4PSPreDetect());
                        }
                        else if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
                        {
                            SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerMHLRx4NormalPreDetect());

                            if((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE) && (GET_SOURCE_PREDETECT(g_ucSearchIndex) == _TRUE))
                            {
                                SET_SOURCE_TYPE(g_ucSearchIndex, ScalerTMDSRx4TMDSScanInputPort(GET_INPUTPORT_TYPE(g_ucSearchIndex)));
                            }
                        }
                    }

                    break;
#endif

                default:

                    break;
            }

            break;

        case _D5_INPUT_PORT:

            switch(GET_PORT_TYPE(GET_INPUTPORT_TYPE(g_ucSearchIndex)))
            {
#if((_D5_INPUT_PORT_TYPE == _D5_DVI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT))

                case _PORT_DVI:
                case _PORT_HDMI:

                    if(GET_POWER_STATUS() == _POWER_STATUS_SAVING)
                    {
                        SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerTMDSRx5TMDSPSPreDetect(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex))));
                    }
                    else if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
                    {
                        SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerTMDSRx5TMDSNormalPreDetect(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex))));

                        if((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE) && (GET_SOURCE_PREDETECT(g_ucSearchIndex) == _TRUE))
                        {
                            SET_SOURCE_TYPE(g_ucSearchIndex, ScalerTMDSRx5TMDSScanInputPort(GET_INPUTPORT_TYPE(g_ucSearchIndex)));
                        }
                    }

                    break;
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

                case _PORT_MHL:

                    if(GET_D5_TMDS_MODE() == _TMDS_HDMI_MODE)
                    {
                        if(GET_POWER_STATUS() == _POWER_STATUS_SAVING)
                        {
                            SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerTMDSRx5TMDSPSPreDetect(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex))));
                        }
                        else if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
                        {
                            SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerTMDSRx5TMDSNormalPreDetect(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex))));

                            if((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE) && (GET_SOURCE_PREDETECT(g_ucSearchIndex) == _TRUE))
                            {
                                SET_SOURCE_TYPE(g_ucSearchIndex, ScalerTMDSRx5TMDSScanInputPort(GET_INPUTPORT_TYPE(g_ucSearchIndex)));
                            }
                        }
                    }
                    else if(GET_D5_TMDS_MODE() == _TMDS_MHL_MODE)
                    {
                        if(GET_POWER_STATUS() == _POWER_STATUS_SAVING)
                        {
                            SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerMHLRx5PSPreDetect());
                        }
                        else if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
                        {
                            SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerMHLRx5NormalPreDetect());

                            if((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE) && (GET_SOURCE_PREDETECT(g_ucSearchIndex) == _TRUE))
                            {
                                SET_SOURCE_TYPE(g_ucSearchIndex, ScalerTMDSRx5TMDSScanInputPort(GET_INPUTPORT_TYPE(g_ucSearchIndex)));
                            }
                        }
                    }

                    break;
#endif

                default:

                    break;
            }

            break;

        case _D6_INPUT_PORT:

#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)

            if(GET_POWER_STATUS() == _POWER_STATUS_SAVING)
            {
                SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerSyncDpPSPreDetect(SysSourceGetInputPort()));
            }
            else if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
            {
                SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerSyncDpNormalPreDetect(SysSourceGetInputPort()));

                if((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE) && (GET_SOURCE_PREDETECT(g_ucSearchIndex) == _TRUE))
                {
                    SET_SOURCE_TYPE(g_ucSearchIndex, ScalerSyncDpScanInputPort(SysSourceGetInputPort()));
                }
            }
#endif

            break;

        case _D7_INPUT_PORT:

            switch(GET_PORT_TYPE(GET_INPUTPORT_TYPE(g_ucSearchIndex)))
            {
#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)

                case _PORT_DP:

                    if(GET_POWER_STATUS() == _POWER_STATUS_SAVING)
                    {
                        SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerSyncDpPSPreDetect(SysSourceGetInputPort()));
                    }
                    else if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
                    {
                        SET_SOURCE_PREDETECT(g_ucSearchIndex, ScalerSyncDpNormalPreDetect(SysSourceGetInputPort()));

                        if((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE) && (GET_SOURCE_PREDETECT(g_ucSearchIndex) == _TRUE))
                        {
                            SET_SOURCE_TYPE(g_ucSearchIndex, ScalerSyncDpScanInputPort(SysSourceGetInputPort()));
                        }
                    }

                    break;
#endif

                default:

                    break;
            }

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Event to clear detection and finish flag
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceClearDetectingEvent(void)
{
#if((_SLEEP_AUDIO_SUPPORT == _ON) && (_DP_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))
    if((GET_MODE_DISPLAY_MODE() == _DISPLAY_MODE_1P) && (GET_AUDIO_PLAYING_ALONE() == _TRUE) && (UserInterfaceGetAudioSource() == _DIGITAL_AUDIO))
    {
        if(GET_MODE_STATE() == _MODE_STATUS_DISPLAY_CHECK)
        {
            SET_SOURCE_SWITCH_FINISH();
        }

        ScalerTimerActiveTimerEvent(SEC(0), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);

        if(GET_RGN_DISPLAY_STATE(_REGION_INDEX_0) != _DISPLAY_ACTION_NO_SIGNAL)
        {
            SET_RGN_DISPLAY_ACTION(_REGION_INDEX_0, _DISPLAY_ACTION_NO_SIGNAL);
        }

        return;
    }
#endif

    CLR_SOURCE_DETECTING();
}

//--------------------------------------------------
// Description  : Decide how much time will be spent on the first port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceSearchTimeInitial(void)
{
    SET_SOURCE_DETECTING();

    if(GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_POLLING_MODE)
    {
        ScalerTimerReactiveTimerEvent(SEC(0), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
    }

#if(_SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT == _ON)
    else if(GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_DELAY_NVRAM_PORT_MODE)
    {
        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);

        ScalerTimerReactiveTimerEvent(_SOURCE_DOUBLE_CHECK_SEARCH_TIME_NVRAM_PORT, _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
    }
#endif

    else if(GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_DELAY_REACTIVE_MODE)
    {
        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

        switch(GET_PORT_TYPE(GET_INPUTPORT_TYPE(g_ucSearchIndex)))
        {
            case _PORT_VGA:

                ScalerTimerReactiveTimerEvent(SEC(2), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);

                break;

            case _PORT_DVI:
            case _PORT_HDMI:
            case _PORT_DUAL_DVI:

                ScalerTimerReactiveTimerEvent(SEC(4.5), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);

                break;

            case _PORT_MHL:

                switch(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex)))
                {
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

                    case _D0_INPUT_PORT:

                        if(GET_D0_TMDS_MODE() == _TMDS_MHL_MODE)
                        {
                            ScalerTimerReactiveTimerEvent(SEC(6), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }
                        else
                        {
                            ScalerTimerReactiveTimerEvent(SEC(4.5), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }

                        break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

                    case _D1_INPUT_PORT:

                        if(GET_D1_TMDS_MODE() == _TMDS_MHL_MODE)
                        {
                            ScalerTimerReactiveTimerEvent(SEC(6), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }
                        else
                        {
                            ScalerTimerReactiveTimerEvent(SEC(4.5), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }

                        break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

                    case _D2_INPUT_PORT:

                        if(GET_D2_TMDS_MODE() == _TMDS_MHL_MODE)
                        {
                            ScalerTimerReactiveTimerEvent(SEC(6), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }
                        else
                        {
                            ScalerTimerReactiveTimerEvent(SEC(4.5), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }

                        break;
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)

                    case _D3_INPUT_PORT:

                        if(GET_D3_TMDS_MODE() == _TMDS_MHL_MODE)
                        {
                            ScalerTimerReactiveTimerEvent(SEC(6), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }
                        else
                        {
                            ScalerTimerReactiveTimerEvent(SEC(4.5), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }

                        break;
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)

                    case _D4_INPUT_PORT:

                        if(GET_D4_TMDS_MODE() == _TMDS_MHL_MODE)
                        {
                            ScalerTimerReactiveTimerEvent(SEC(6), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }
                        else
                        {
                            ScalerTimerReactiveTimerEvent(SEC(4.5), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }

                        break;
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

                    case _D5_INPUT_PORT:

                        if(GET_D5_TMDS_MODE() == _TMDS_MHL_MODE)
                        {
                            ScalerTimerReactiveTimerEvent(SEC(6), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }
                        else
                        {
                            ScalerTimerReactiveTimerEvent(SEC(4.5), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }

                        break;
#endif

                    default:
                        break;
                }

                break;

            case _PORT_DP:

                ScalerTimerReactiveTimerEvent(SEC(4), _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);

                break;

            default:
                break;
        }
    }
    else
    {
        switch(GET_SOURCE_SCAN_TYPE())
        {
            case _SOURCE_SWITCH_FIXED_PORT:
            case _SOURCE_SWITCH_AUTO_IN_GROUP:
            case _SOURCE_SWITCH_DELL_HOTKEY_FIXED:
            case _SOURCE_SWITCH_DELL_HOTKEY_AUTO:

#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_IN_SEARCH_STATE)

                ScalerTimerReactiveTimerEvent(_SOURCE_DEFAULT_SEARCH_TIME_ALL_PORT, _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);

#else
                switch(GET_PORT_TYPE(GET_INPUTPORT_TYPE(g_ucSearchIndex)))
                {
#if(_VGA_PORT_EXIST == _ON)
                    case _PORT_VGA:

                        if(GET_CABLE_DETECT(g_ucSearchIndex) == _TRUE)
                        {
                            ScalerTimerReactiveTimerEvent(g_usSourceDefaultSearchTimeVga, _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }
                        else
                        {
                            ScalerTimerReactiveTimerEvent(g_usSourceNoCableSearchTimeVga, _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }

                        break;
#endif

#if(_HDMI_PORT_EXIST == _ON)
                    case _PORT_HDMI:
                    case _PORT_MHL:

                        if(GET_CABLE_DETECT(g_ucSearchIndex) == _TRUE)
                        {
                            ScalerTimerReactiveTimerEvent(g_usSourceDefaultSearchTimeHdmi, _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }
                        else
                        {
                            ScalerTimerReactiveTimerEvent(g_usSourceNoCableSearchTimeHdmi, _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }

                        break;
#endif

#if(_DVI_PORT_EXIST == _ON)
                    case _PORT_DVI:
                    case _PORT_DUAL_DVI:

                        if(GET_CABLE_DETECT(g_ucSearchIndex) == _TRUE)
                        {
                            ScalerTimerReactiveTimerEvent(g_usSourceDefaultSearchTimeDvi, _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }
                        else
                        {
                            ScalerTimerReactiveTimerEvent(g_usSourceNoCableSearchTimeDvi, _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }

                        break;
#endif

#if(_DP_PORT_EXIST == _ON)
                    case _PORT_DP:

                        if(GET_CABLE_DETECT(g_ucSearchIndex) == _TRUE)
                        {
                            ScalerTimerReactiveTimerEvent(g_usSourceDefaultSearchTimeDp, _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }
                        else
                        {
                            ScalerTimerReactiveTimerEvent(g_usSourceNoCableSearchTimeDp, _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
                        }

                        break;
#endif

                    default:
                        break;
                }
#endif
                break;

            default:
                break;
        }
    }
}

//--------------------------------------------------
// Description  : Judge if the port with source will be chosen
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceJudge(void)
{
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
    BYTE ucDpSwitchPortBackup = GET_D6_SWITCH_SELECT();
#endif

    switch(GET_SOURCE_SCAN_TYPE())
    {
        case _SOURCE_SWITCH_FIXED_PORT:
        case _SOURCE_SWITCH_AUTO_IN_GROUP:
        case _SOURCE_SWITCH_DELL_HOTKEY_FIXED:
        case _SOURCE_SWITCH_DELL_HOTKEY_AUTO:

            if(GET_SOURCE_TYPE(g_ucSearchIndex) != _SOURCE_NONE)
            {
                SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                // Choose Current Source to proceed
                SET_SOURCE_JUDGE(g_ucSearchIndex, _TRUE);

                CLR_SOURCE_DETECTING();

                if(GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_DELL_HOTKEY_FIXED)
                {
                    SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_FIXED_PORT);
                }
                else if(GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_DELL_HOTKEY_AUTO)
                {
                    SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_AUTO_IN_GROUP);
                }

                ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

                if(SysSourceGetInputPort() == _D0_INPUT_PORT)
                {
                    SET_D6_SWITCH_SELECT(_D0_INPUT_PORT);
                }
                else if(SysSourceGetInputPort() == _D6_INPUT_PORT)
                {
                    SET_D6_SWITCH_SELECT(_D6_INPUT_PORT);
                }
                else
                {
                    if((SysRegionConvertPortToRegionIndex(_D0_INPUT_PORT) == _REGION_INDEX_NONE) &&
                       (SysRegionConvertPortToRegionIndex(_D6_INPUT_PORT) == _REGION_INDEX_NONE))
                    {
                        SET_D6_SWITCH_SELECT(UserInterfaceGetDpSwitchSelectPort());
                    }
                }

                if(ucDpSwitchPortBackup != GET_D6_SWITCH_SELECT())
                {
                    PCB_DIGITAL_D6_SWITCH_POWER(_DIGITAL_D6_SWITCH_POWER_DOWN);
                    SET_D6_SWITCH_POWER_STATUS(_DIGITAL_D6_SWITCH_POWER_DOWN);
                    CLR_DP_AUTO_SEARCH_SWITCH();

                    if(GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT)
                    {
                        ScalerDpVersionSwitch(_D0_INPUT_PORT, UserInterfaceGetDPVersion(_D0_INPUT_PORT), UserInterfaceGetDpMSTCapablePort());
                    }
                    else if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
                    {
                        ScalerDpVersionSwitch(_D6_INPUT_PORT, UserInterfaceGetDPVersion(_D6_INPUT_PORT), UserInterfaceGetDpMSTCapablePort());
                    }
                }
#elif(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)

                if((GET_MODE_DISPLAY_MODE() == _DISPLAY_MODE_1P) &&
                   (SysSourceGetInputPort() != _D0_INPUT_PORT) &&
                   (SysSourceGetInputPort() != _D1_INPUT_PORT) &&
                   (SysSourceGetInputPort() != _D7_INPUT_PORT))
                {
                    if(UserInterfaceGetDpDualDefaultPort() == _TRUE)
                    {
                        if(UserCommonInterfaceDpGetDualPortEdidSelectStatus() == _FALSE)
                        {
                            UserCommonInterfaceDpDualPortEdidTableSwitch(_D7_INPUT_PORT);
                        }
                    }
                    else
                    {
                        if(UserCommonInterfaceDpGetDualPortEdidSelectStatus() == _TRUE)
                        {
                            UserCommonInterfaceDpDualPortEdidTableSwitch(_D0_INPUT_PORT);
                            UserCommonInterfaceDpDualPortEdidTableSwitch(_D1_INPUT_PORT);
                        }
                    }
                }
#endif
            }
            else if(GET_SOURCE_PREDETECT(g_ucSearchIndex) == _TRUE)
            {
                if(GET_SOURCE_SEARCH_TIME_REACTIVE() == _TRUE)
                {
                    ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);

                    SET_SOURCE_DETECTING();

                    SET_SOURCE_SEARCH_TIME_INITIAL();

                    SET_SOURCE_SEARCH_PORT_INITIAL();

#if(_SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT == _ON)
                    //--------------------------------------------------
                    // Check NVRAM port when:
                    // 1. "NVRAM check" flagged
                    // 2. in auto-search mode, and search index belongs to auto-search target
                    // 3. search index & saved index are in the same group but different
                    // 4. source search times is not 0
                    //--------------------------------------------------
                    if((GET_SOURCE_SEARCH_CHECK_NVRAM_PORT() == _TRUE) &&
                       (GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_POLLING_MODE) &&
                       (GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_AUTO_IN_GROUP) &&
                       (g_ucSearchIndex == GET_RGN_SOURCE_INDEX(GET_SOURCE_AUTO_TARGET())) &&
                       (GET_INPUTPORT_GROUP(g_ucSearchIndex) == GET_INPUTPORT_GROUP(SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0 + GET_SOURCE_AUTO_TARGET())))) &&
                       (g_ucSearchIndex != SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0 + GET_SOURCE_AUTO_TARGET()))) &&
                       (GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex) != 0x00))
                    {
                        DebugMessageSystem("Switch NVRAM port", g_ucSearchIndex);

                        g_ucSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0 + GET_SOURCE_AUTO_TARGET()));

                        SET_RGN_SOURCE_INDEX(GET_SOURCE_AUTO_TARGET(), g_ucSearchIndex);

                        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_NVRAM_PORT_MODE);

                        CLR_SOURCE_SEARCH_CHECK_NVRAM_PORT();
                    }
                    else
                    {
                        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_REACTIVE_MODE);

                        CLR_SOURCE_SEARCH_TIME_REACTIVE();
                    }
#else
                    SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_REACTIVE_MODE);

                    CLR_SOURCE_SEARCH_TIME_REACTIVE();
#endif
                }

                if(GET_POWER_STATUS() == _POWER_STATUS_SAVING)
                {
                    SET_TARGET_POWER_STATUS(_POWER_STATUS_NORMAL);
                }
            }

            if((GET_POWER_STATUS() == _POWER_STATUS_NOSUPPORT_SAVING) || (GET_POWER_STATUS() == _POWER_STATUS_FAKE_SAVING))
            {
                // For Nosupport Power Saving Mode Change
                SET_TARGET_POWER_STATUS(_POWER_STATUS_NORMAL);
            }

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Port Switch Function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceSwitchPort(void)
{
    if(GET_MODE_DISPLAY_MODE() == _DISPLAY_MODE_1P)
    {
        SysSource1pSwitchPort();
    }
#if(_MULTI_DISPLAY_MAX != 0x01)
    else
    {
        SysSourceMultiSwitchPort();
    }
#endif
}

//--------------------------------------------------
// Description  : Port Switch Function for 1P
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSource1pSwitchPort(void)
{
    BYTE ucCount = 0;
    BYTE ucBackupSearchIndex = g_ucSearchIndex;

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
    BYTE ucDpSwitchPortBackup = GET_D6_SWITCH_SELECT();
#endif

    switch(GET_SOURCE_SCAN_TYPE())
    {
        case _SOURCE_SWITCH_FIXED_PORT:

            if(GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex) == 0x00)
            {
                INCREASE_SOURCE_SEARCH_TIMES(g_ucSearchIndex);

                SET_SOURCE_SWITCH_FINISH();
                SET_RGN_DISPLAY_ACTION(_REGION_INDEX_0, _DISPLAY_ACTION_NO_SIGNAL);
            }

            break;

        case _SOURCE_SWITCH_AUTO_IN_GROUP:

            // Switch to the next port by search priority with group limit.
            do
            {
#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_IN_SEARCH_STATE)

                if(GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex) == 0x00)
                {
                    INCREASE_SOURCE_SEARCH_TIMES(g_ucSearchIndex);

                    if(SysSourceCheckTargetTimes(1) == _TRUE)
                    {
                        SET_SOURCE_SWITCH_FINISH();
                        SET_RGN_DISPLAY_ACTION(_REGION_INDEX_0, _DISPLAY_ACTION_NO_SIGNAL);
                    }
                }

#elif(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_AFTER_NOSIGNAL_STATE)

                if(GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex) == 0x00)
                {
                    INCREASE_SOURCE_SEARCH_TIMES(g_ucSearchIndex);

                    if(SysSourceCheckTargetTimes(1) == _TRUE)
                    {
                        SET_SOURCE_SWITCH_FINISH();

                        if(GET_RGN_DISPLAY_STATE(_REGION_INDEX_0) != _DISPLAY_STATE_NO_SIGNAL)
                        {
                            SET_RGN_DISPLAY_ACTION(_REGION_INDEX_0, _DISPLAY_ACTION_NO_SIGNAL);

                            g_ucSearchIndex = ucBackupSearchIndex;

                            return;
                        }
                    }
                }

#elif(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_ACER_STYLE)

                if(GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex) <= 1)
                {
                    if(SysSourceCheckTargetTimes(1) == _TRUE)
                    {
                        SET_SOURCE_SWITCH_FINISH();

                        if(GET_RGN_DISPLAY_STATE(_REGION_INDEX_0) != _DISPLAY_STATE_NO_SIGNAL)
                        {
                            SET_RGN_DISPLAY_ACTION(_REGION_INDEX_0, _DISPLAY_ACTION_NO_SIGNAL);

                            g_ucSearchIndex = ucBackupSearchIndex;

                            return;
                        }
                    }

                    if(GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex) == 0x00)
                    {
                        INCREASE_SOURCE_SEARCH_TIMES(g_ucSearchIndex);
                    }
                }

#elif(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_ASUS_STYLE)

                if(GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex) == 0x00)
                {
                    INCREASE_SOURCE_SEARCH_TIMES(g_ucSearchIndex);

                    if(SysSourceCheckTargetTimes(1) == _TRUE)
                    {
                        if(GET_MODE_STATE() == _MODE_STATUS_POWER_SAVING)
                        {
                            SET_SOURCE_SWITCH_FINISH();
                            SET_RGN_DISPLAY_ACTION(_REGION_INDEX_0, _DISPLAY_ACTION_NO_SIGNAL);
                        }
                    }
                }

#elif(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_DELL_STYLE)

                if(GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex) == 0x00)
                {
                    INCREASE_SOURCE_SEARCH_TIMES(g_ucSearchIndex);

                    if(SysSourceCheckTargetTimes(1) == _TRUE)
                    {
                        SET_SOURCE_SWITCH_FINISH();
                        SET_RGN_DISPLAY_ACTION(_REGION_INDEX_0, _DISPLAY_ACTION_NO_SIGNAL);
                    }
                }

#endif // End of #if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_IN_SEARCH_STATE)

                g_ucSearchIndex = (g_ucSearchIndex + 1) % _INPUT_PORT_VALID;

                if(GET_INPUTPORT_GROUP(g_ucSearchIndex) == GET_INPUTPORT_GROUP(ucBackupSearchIndex))
                {
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

                    if((GET_INPUTPORT_GROUP(SysSourceConvertSearchPort(_D0_INPUT_PORT))) == (GET_INPUTPORT_GROUP(SysSourceConvertSearchPort(_D6_INPUT_PORT))))
                    {
                        if((GET_RGN_DISPLAY_STATE(_REGION_INDEX_0) == _DISPLAY_STATE_NO_SIGNAL) && (GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE))
                        {
                            ScalerTimerActiveTimerEvent(_SOURCE_DP_SWITCH_TIMEOUT_TIME, _SYSTEM_TIMER_EVENT_SOURCE_DP_SWITCH_TIMEOUT);
                            CLR_SOURCE_DP_SWITCH_TIMEOUT();
                        }

                        if((SysSourceGetInputPort() == _D0_INPUT_PORT) || (SysSourceGetInputPort() == _D6_INPUT_PORT))
                        {
                            if((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE) || (GET_SOURCE_DP_SWITCH_TIMEOUT() == _TRUE))
                            {
                                if((GET_D6_SWITCH_POWER_STATUS() == _DIGITAL_D6_SWITCH_POWER_ON) && (SysSourceGetInputPort() != GET_D6_SWITCH_SELECT()))
                                {
                                    if(GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_POLLING_MODE)
                                    {
                                        ScalerTimerActiveTimerEvent(_SOURCE_DP_SWITCH_TIMEOUT_TIME, _SYSTEM_TIMER_EVENT_SOURCE_DP_SWITCH_TIMEOUT);
                                        CLR_SOURCE_DP_SWITCH_TIMEOUT();
                                    }

                                    if(SysSourceGetInputPort() == _D0_INPUT_PORT)
                                    {
                                        SET_D6_SWITCH_SELECT(_D0_INPUT_PORT);
                                    }
                                    else if(SysSourceGetInputPort() == _D6_INPUT_PORT)
                                    {
                                        SET_D6_SWITCH_SELECT(_D6_INPUT_PORT);
                                    }

                                    if(ucDpSwitchPortBackup != GET_D6_SWITCH_SELECT())
                                    {
                                        PCB_DIGITAL_D6_SWITCH_POWER(_DIGITAL_D6_SWITCH_POWER_DOWN);
                                        SET_D6_SWITCH_POWER_STATUS(_DIGITAL_D6_SWITCH_POWER_DOWN);

                                        if(GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE)
                                        {
                                            CLR_DP_AUTO_SEARCH_SWITCH();
                                        }
                                        else
                                        {
                                            SET_DP_AUTO_SEARCH_SWITCH();
                                        }

                                        if(GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT)
                                        {
                                            ScalerDpVersionSwitch(_D0_INPUT_PORT, UserInterfaceGetDPVersion(_D0_INPUT_PORT), UserInterfaceGetDpMSTCapablePort());
                                        }
                                        else if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
                                        {
                                            ScalerDpVersionSwitch(_D6_INPUT_PORT, UserInterfaceGetDPVersion(_D6_INPUT_PORT), UserInterfaceGetDpMSTCapablePort());
                                        }
                                    }
                                }

                                break;
                            }
                            else
                            {
                                if(SysSourceGetInputPort() == GET_D6_SWITCH_SELECT())
                                {
                                    break;
                                }
                            }
                        }
                        else
                        {
                            if(GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE)
                            {
                                SET_D6_SWITCH_SELECT(UserInterfaceGetDpSwitchSelectPort());
                            }

                            if(ucDpSwitchPortBackup != GET_D6_SWITCH_SELECT())
                            {
                                PCB_DIGITAL_D6_SWITCH_POWER(_DIGITAL_D6_SWITCH_POWER_DOWN);
                                SET_D6_SWITCH_POWER_STATUS(_DIGITAL_D6_SWITCH_POWER_DOWN);
                                CLR_DP_AUTO_SEARCH_SWITCH();

                                if(GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT)
                                {
                                    ScalerDpVersionSwitch(_D0_INPUT_PORT, UserInterfaceGetDPVersion(_D0_INPUT_PORT), UserInterfaceGetDpMSTCapablePort());
                                }
                                else if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
                                {
                                    ScalerDpVersionSwitch(_D6_INPUT_PORT, UserInterfaceGetDPVersion(_D6_INPUT_PORT), UserInterfaceGetDpMSTCapablePort());
                                }
                            }

                            break;
                        }
                    }
                    else // D0 DP Port and D6 DP Port are Not in the Same Group
                    {
                        if(SysSourceGetInputPort() == _D0_INPUT_PORT)
                        {
                            SET_D6_SWITCH_SELECT(_D0_INPUT_PORT);
                        }
                        else if(SysSourceGetInputPort() == _D6_INPUT_PORT)
                        {
                            SET_D6_SWITCH_SELECT(_D6_INPUT_PORT);
                        }

                        if(ucDpSwitchPortBackup != GET_D6_SWITCH_SELECT())
                        {
                            PCB_DIGITAL_D6_SWITCH_POWER(_DIGITAL_D6_SWITCH_POWER_DOWN);
                            SET_D6_SWITCH_POWER_STATUS(_DIGITAL_D6_SWITCH_POWER_DOWN);
                            CLR_DP_AUTO_SEARCH_SWITCH();

                            if(GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT)
                            {
                                ScalerDpVersionSwitch(_D0_INPUT_PORT, UserInterfaceGetDPVersion(_D0_INPUT_PORT), UserInterfaceGetDpMSTCapablePort());
                            }
                            else if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
                            {
                                ScalerDpVersionSwitch(_D6_INPUT_PORT, UserInterfaceGetDPVersion(_D6_INPUT_PORT), UserInterfaceGetDpMSTCapablePort());
                            }
                        }

                        break;
                    }

#elif(_D7_INPUT_PORT_TYPE == _D7_DP_PORT) // Else of #elif((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

                    if((GET_RGN_DISPLAY_STATE(_REGION_INDEX_0) == _DISPLAY_STATE_NO_SIGNAL) && (GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE))
                    {
                        ScalerTimerReactiveTimerEvent(_SOURCE_DP_DUAL_SWITCH_TIMEOUT_TIME, _SYSTEM_TIMER_EVENT_SOURCE_DP_DUAL_SWITCH_TIMEOUT);
                        CLR_SOURCE_DP_DUAL_SWITCH_TIMEOUT();
                    }

                    if((SysSourceGetInputPort() == _D0_INPUT_PORT) || (SysSourceGetInputPort() == _D1_INPUT_PORT) || (SysSourceGetInputPort() == _D7_INPUT_PORT))
                    {
                        if((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE) || (GET_SOURCE_DP_DUAL_SWITCH_TIMEOUT() == _TRUE))
                        {
                            if(UserCommonInterfaceDpGetDualPortEdidSelectStatus() == _FALSE)
                            {
                                if(SysSourceGetInputPort() == _D7_INPUT_PORT)
                                {
                                    UserCommonInterfaceDpDualPortEdidTableSwitch(_D7_INPUT_PORT);

                                    if(GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_POLLING_MODE)
                                    {
                                        ScalerTimerActiveTimerEvent(_SOURCE_DP_DUAL_SWITCH_TIMEOUT_TIME, _SYSTEM_TIMER_EVENT_SOURCE_DP_DUAL_SWITCH_TIMEOUT);
                                        CLR_SOURCE_DP_DUAL_SWITCH_TIMEOUT();
                                    }
                                }
                            }
                            else
                            {
                                if((SysSourceGetInputPort() == _D0_INPUT_PORT) || (SysSourceGetInputPort() == _D1_INPUT_PORT))
                                {
                                    UserCommonInterfaceDpDualPortEdidTableSwitch(_D0_INPUT_PORT);
                                    UserCommonInterfaceDpDualPortEdidTableSwitch(_D1_INPUT_PORT);

                                    if(GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_POLLING_MODE)
                                    {
                                        ScalerTimerActiveTimerEvent(_SOURCE_DP_DUAL_SWITCH_TIMEOUT_TIME, _SYSTEM_TIMER_EVENT_SOURCE_DP_DUAL_SWITCH_TIMEOUT);
                                        CLR_SOURCE_DP_DUAL_SWITCH_TIMEOUT();
                                    }
                                }
                            }

                            break;
                        }
                        else
                        {
                            if(UserCommonInterfaceDpGetDualPortEdidSelectStatus() == _TRUE)
                            {
                                if((SysSourceGetInputPort() != _D0_INPUT_PORT) && (SysSourceGetInputPort() != _D1_INPUT_PORT))
                                {
                                    break;
                                }
                            }
                            else
                            {
                                if(SysSourceGetInputPort() != _D7_INPUT_PORT)
                                {
                                    break;
                                }
                            }
                        }
                    }
                    else
                    {
                        if(GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE)
                        {
                            if(UserInterfaceGetDpDualDefaultPort() == _TRUE)
                            {
                                if(UserCommonInterfaceDpGetDualPortEdidSelectStatus() == _FALSE)
                                {
                                    UserCommonInterfaceDpDualPortEdidTableSwitch(_D7_INPUT_PORT);
                                }
                            }
                        }

                        break;
                    }
#else
                    break;
#endif // End of #if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                }

                ucCount++;
            }
            while(ucCount < _INPUT_PORT_VALID);

            if(g_ucSearchIndex != ucBackupSearchIndex)
            {
                SET_SOURCE_SEARCH_TIME_INITIAL();

                SET_SOURCE_SEARCH_PORT_INITIAL();

#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_IN_SEARCH_STATE)

#if(_SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT == _ON)
                if((GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_DELAY_DEFAULT_MODE) ||
                   ((ucBackupSearchIndex != SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0))) && (GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_DELAY_REACTIVE_MODE)))
                {
                    SET_SOURCE_SEARCH_CHECK_NVRAM_PORT();
                }
#endif
                SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);

#elif((_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_AFTER_NOSIGNAL_STATE) ||\
      (_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_ACER_STYLE))

                if(GET_RGN_DISPLAY_STATE(_REGION_INDEX_0) != _DISPLAY_STATE_NO_SIGNAL)
                {
                    SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);
                }
                else
                {
#if(_SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT == _ON)
                    if((GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_DELAY_DEFAULT_MODE) ||
                       ((ucBackupSearchIndex != SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0))) && (GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_DELAY_REACTIVE_MODE)))
                    {
                        SET_SOURCE_SEARCH_CHECK_NVRAM_PORT();
                    }
#endif
                    SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);
                }

#elif(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_ASUS_STYLE)

                if((GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex) == 0) &&
                   (GET_RGN_DISPLAY_STATE(_REGION_INDEX_0) != _DISPLAY_STATE_NO_SIGNAL))
                {
                    SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);
                }
                else
                {
#if(_SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT == _ON)
                    if((GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_DELAY_DEFAULT_MODE) ||
                       ((ucBackupSearchIndex != SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0))) && (GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_DELAY_REACTIVE_MODE)))
                    {
                        SET_SOURCE_SEARCH_CHECK_NVRAM_PORT();
                    }
#endif
                    SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);
                }

#elif(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_DELL_STYLE)

                pData[1] = 0;

                for(pData[0] = 0; pData[0] < _INPUT_PORT_VALID; pData[0]++)
                {
                    if(GET_SOURCE_SEARCH_TIMES(pData[0]) == 1)
                    {
                        pData[1]++;
                    }
                }

                if(pData[1] >= 2)
                {
#if(_SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT == _ON)
                    if((GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_DELAY_DEFAULT_MODE) ||
                       ((ucBackupSearchIndex != SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0))) && (GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_DELAY_REACTIVE_MODE)))
                    {
                        SET_SOURCE_SEARCH_CHECK_NVRAM_PORT();
                    }
#endif
                    SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);
                }
                else
                {
                    SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);
                }
#endif
                SET_SOURCE_SEARCH_TIME_REACTIVE();
            }

            break;

        case _SOURCE_SWITCH_DELL_HOTKEY_FIXED:
        case _SOURCE_SWITCH_DELL_HOTKEY_AUTO:

            do
            {
                if(GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex) == 0x00)
                {
                    INCREASE_SOURCE_SEARCH_TIMES(g_ucSearchIndex);

                    if(SysSourceCheckTargetTimes(1) == _TRUE)
                    {
                        SET_SOURCE_SWITCH_FINISH();
                        SET_RGN_DISPLAY_ACTION(_REGION_INDEX_0, _DISPLAY_ACTION_NO_SIGNAL);

                        if(GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_DELL_HOTKEY_FIXED)
                        {
                            g_ucSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0));

                            SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_FIXED_PORT);
                        }
                        else if(GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_DELL_HOTKEY_AUTO)
                        {
                            SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_AUTO_IN_GROUP);
                        }

                        SET_SOURCE_SEARCH_TIME_INITIAL();

                        SET_SOURCE_SEARCH_PORT_INITIAL();

                        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                        SET_SOURCE_SEARCH_TIME_REACTIVE();

                        return;
                    }
                }

                g_ucSearchIndex = (g_ucSearchIndex + 1) % _INPUT_PORT_VALID;

                if(GET_INPUTPORT_GROUP(g_ucSearchIndex) == GET_INPUTPORT_GROUP(ucBackupSearchIndex))
                {
                    break;
                }

                ucCount++;
            }
            while(ucCount < _INPUT_PORT_VALID);

            if(g_ucSearchIndex != ucBackupSearchIndex)
            {
                SET_SOURCE_SEARCH_TIME_INITIAL();

                SET_SOURCE_SEARCH_PORT_INITIAL();

                SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

                SET_SOURCE_SEARCH_TIME_REACTIVE();
            }

            break;

        default:
            break;
    }

    // Assign search index to 1P
    SET_RGN_SOURCE_INDEX(_DISPLAY_RGN_1P, g_ucSearchIndex);
}

#if(_MULTI_DISPLAY_MAX != 0x01)
//--------------------------------------------------
// Description  : Multi Port Switch Function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceMultiSwitchPort(void)
{
    BYTE ucCount = 0;
    BYTE ucBackupSearchIndex = g_ucSearchIndex;
    BYTE ucRegionIndex = 0;

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
    BYTE ucDpSwitchPortBackup = GET_D6_SWITCH_SELECT();
#endif

    switch(GET_SOURCE_SCAN_TYPE())
    {
        case _SOURCE_SWITCH_FIXED_PORT:

            for(ucRegionIndex = 0; ucRegionIndex < GET_RGN_MAX_DISPLAY_REGION(); ucRegionIndex++)
            {
                if((GET_SOURCE_JUDGE(g_ucSearchIndex) == _FALSE) &&
                   (GET_RGN_SOURCE_INDEX(ucRegionIndex) == g_ucSearchIndex) &&
                   (GET_RGN_DISPLAY_STATE(ucRegionIndex) != _DISPLAY_STATE_NO_SIGNAL) &&
                   (GET_RGN_DISPLAY_ACTION(ucRegionIndex) != _DISPLAY_ACTION_NO_SIGNAL))
                {
                    SET_RGN_DISPLAY_ACTION(ucRegionIndex, _DISPLAY_ACTION_NO_SIGNAL);

                    // Flag switch finish when all no signal
                    if(SysRegionCheckAllDisplayState(_DISPLAY_STATE_NO_SIGNAL) == _TRUE)
                    {
                        SET_SOURCE_SWITCH_FINISH();
                    }
                }
            }

            do
            {
                g_ucSearchIndex = (g_ucSearchIndex + 1) % _INPUT_PORT_VALID;

                if(SysSourceCheckMultiFixedPortTarget(g_ucSearchIndex) == _TRUE)
                {
                    break;
                }

                ucCount++;
            }
            while(ucCount < _INPUT_PORT_VALID);

            SET_SOURCE_SEARCH_TIME_INITIAL();
            SET_SOURCE_SEARCH_PORT_INITIAL();
            SET_SOURCE_SEARCH_TIME_REACTIVE();

            if((g_ucSearchIndex != ucBackupSearchIndex) ||
               (GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_DELAY_REACTIVE_MODE))
            {
                if(GET_MODE_STATE() == _MODE_STATUS_POWER_SAVING)
                {
                    SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);
                }
                else
                {
                    if((SysRegionGetDisplayStateCount(_DISPLAY_STATE_NO_SIGNAL) +
                        SysRegionGetDisplayStateCount(_DISPLAY_STATE_OOR) +
                        SysRegionGetDisplayStateCount(_DISPLAY_STATE_ACTIVE)) ==
                       GET_RGN_MAX_DISPLAY_REGION())
                    {
                        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);
                        SET_SOURCE_SEARCH_TIME_REACTIVE();
                    }
                    else
                    {
                        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);
                    }
                }
            }

            break;

        case _SOURCE_SWITCH_AUTO_IN_GROUP:

            for(ucRegionIndex = 0; ucRegionIndex < GET_RGN_MAX_DISPLAY_REGION(); ucRegionIndex++)
            {
                if((GET_SOURCE_JUDGE(g_ucSearchIndex) == _FALSE) &&
                   (GET_RGN_SOURCE_INDEX(ucRegionIndex) == g_ucSearchIndex) &&
                   (ucRegionIndex != GET_SOURCE_AUTO_TARGET()) &&
                   (GET_RGN_DISPLAY_STATE(ucRegionIndex) != _DISPLAY_STATE_NO_SIGNAL) &&
                   (GET_RGN_DISPLAY_ACTION(ucRegionIndex) != _DISPLAY_ACTION_NO_SIGNAL))
                {
                    // Set display no signal for non-auto source
                    SET_RGN_DISPLAY_ACTION(ucRegionIndex, _DISPLAY_ACTION_NO_SIGNAL);

                    // Flag switch finish when all signal
                    if(SysRegionCheckAllDisplayState(_DISPLAY_STATE_NO_SIGNAL) == _TRUE)
                    {
                        SET_SOURCE_SWITCH_FINISH();
                    }
                }
            }

            // Switch to the next port by search priority with group limit.
            do
            {
#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_AFTER_NOSIGNAL_STATE)

                if(GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex) == 0x00)
                {
                    INCREASE_SOURCE_SEARCH_TIMES(g_ucSearchIndex);

                    if(SysSourceCheckTargetTimes(1) == _TRUE)
                    {
                        // Flag switch finish when all signal
                        if(SysRegionCheckAllDisplayState(_DISPLAY_STATE_NO_SIGNAL) == _TRUE)
                        {
                            SET_SOURCE_SWITCH_FINISH();
                        }

                        if((GET_RGN_SOURCE_JUDGE(GET_SOURCE_AUTO_TARGET()) == _FALSE) &&
                           (GET_RGN_DISPLAY_STATE(GET_SOURCE_AUTO_TARGET()) != _DISPLAY_STATE_NO_SIGNAL) &&
                           (GET_RGN_DISPLAY_ACTION(GET_SOURCE_AUTO_TARGET()) != _DISPLAY_ACTION_NO_SIGNAL))
                        {
                            // Set display no signal for auto search source
                            SysRegionSetDisplayStateBySearchIndex(GET_RGN_SOURCE_INDEX(GET_SOURCE_AUTO_TARGET()), _DISPLAY_STATE_NO_SIGNAL);

                            return;
                        }
                    }
                }

#elif(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_ACER_STYLE)

                if(GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex) <= 1)
                {
                    if(SysSourceCheckTargetTimes(1) == _TRUE)
                    {
                        // Flag switch finish when all signal
                        if(SysRegionCheckAllDisplayState(_DISPLAY_STATE_NO_SIGNAL) == _TRUE)
                        {
                            SET_SOURCE_SWITCH_FINISH();
                        }

                        if((GET_RGN_SOURCE_JUDGE(GET_SOURCE_AUTO_TARGET()) == _FALSE) &&
                           (GET_RGN_DISPLAY_STATE(GET_SOURCE_AUTO_TARGET()) != _DISPLAY_STATE_NO_SIGNAL) &&
                           (GET_RGN_DISPLAY_ACTION(GET_SOURCE_AUTO_TARGET()) != _DISPLAY_ACTION_NO_SIGNAL))
                        {
                            // Set display no signal for auto search source
                            SysRegionSetDisplayStateBySearchIndex(GET_RGN_SOURCE_INDEX(GET_SOURCE_AUTO_TARGET()), _DISPLAY_STATE_NO_SIGNAL);

                            return;
                        }
                    }

                    if(GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex) == 0x00)
                    {
                        INCREASE_SOURCE_SEARCH_TIMES(g_ucSearchIndex);
                    }
                }
#else
                if(GET_SOURCE_SEARCH_TIMES(g_ucSearchIndex) == 0x00)
                {
                    INCREASE_SOURCE_SEARCH_TIMES(g_ucSearchIndex);

                    if(SysSourceCheckTargetTimes(1) == _TRUE)
                    {
                        if((GET_RGN_SOURCE_JUDGE(GET_SOURCE_AUTO_TARGET()) == _FALSE) &&
                           (GET_RGN_DISPLAY_STATE(GET_SOURCE_AUTO_TARGET()) != _DISPLAY_STATE_NO_SIGNAL) &&
                           (GET_RGN_DISPLAY_ACTION(GET_SOURCE_AUTO_TARGET()) != _DISPLAY_ACTION_NO_SIGNAL))
                        {
                            // Set display no signal for auto search source
                            SysRegionSetDisplayStateBySearchIndex(GET_RGN_SOURCE_INDEX(GET_SOURCE_AUTO_TARGET()), _DISPLAY_STATE_NO_SIGNAL);
                        }

                        // Flag switch finish when all signal
                        if(SysRegionCheckAllDisplayState(_DISPLAY_STATE_NO_SIGNAL) == _TRUE)
                        {
                            SET_SOURCE_SWITCH_FINISH();
                        }
                    }
                }
#endif
                g_ucSearchIndex = (g_ucSearchIndex + 1) % _INPUT_PORT_VALID;

                if(GET_INPUTPORT_GROUP(g_ucSearchIndex) == GET_INPUTPORT_GROUP(ucBackupSearchIndex))
                {
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

                    // Check source valid as fixed port or auto-search candidate
                    if((SysSourceCheckMultiFixedPortTarget(g_ucSearchIndex) == _TRUE) ||
                       (SysSourceCheckMultiAutoSearchTarget(g_ucSearchIndex) == _TRUE))
                    {
                        if((GET_INPUTPORT_GROUP(SysSourceConvertSearchPort(_D0_INPUT_PORT))) == (GET_INPUTPORT_GROUP(SysSourceConvertSearchPort(_D6_INPUT_PORT))))
                        {
                            if(((SysRegionGetDisplayStateCount(_DISPLAY_STATE_NO_SIGNAL) +
                                 SysRegionGetDisplayStateCount(_DISPLAY_STATE_OOR) +
                                 SysRegionGetDisplayStateCount(_DISPLAY_STATE_ACTIVE)) == GET_RGN_MAX_DISPLAY_REGION()) &&
                               (GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE))
                            {
                                ScalerTimerActiveTimerEvent(_SOURCE_DP_SWITCH_TIMEOUT_TIME, _SYSTEM_TIMER_EVENT_SOURCE_DP_SWITCH_TIMEOUT);
                                CLR_SOURCE_DP_SWITCH_TIMEOUT();
                            }

                            if((SysSourceGetInputPort() == _D0_INPUT_PORT) || (SysSourceGetInputPort() == _D6_INPUT_PORT))
                            {
                                if((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE) || (GET_SOURCE_DP_SWITCH_TIMEOUT() == _TRUE))
                                {
                                    if((GET_D6_SWITCH_POWER_STATUS() == _DIGITAL_D6_SWITCH_POWER_ON) && (SysSourceGetInputPort() != GET_D6_SWITCH_SELECT()))
                                    {
                                        if(GET_SOURCE_SEARCH_DELAY_MODE() == _SOURCE_SEARCH_POLLING_MODE)
                                        {
                                            ScalerTimerActiveTimerEvent(_SOURCE_DP_SWITCH_TIMEOUT_TIME, _SYSTEM_TIMER_EVENT_SOURCE_DP_SWITCH_TIMEOUT);
                                            CLR_SOURCE_DP_SWITCH_TIMEOUT();
                                        }

                                        if(SysSourceGetInputPort() == _D0_INPUT_PORT)
                                        {
                                            SET_D6_SWITCH_SELECT(_D0_INPUT_PORT);
                                        }
                                        else if(SysSourceGetInputPort() == _D6_INPUT_PORT)
                                        {
                                            SET_D6_SWITCH_SELECT(_D6_INPUT_PORT);
                                        }

                                        if(ucDpSwitchPortBackup != GET_D6_SWITCH_SELECT())
                                        {
                                            PCB_DIGITAL_D6_SWITCH_POWER(_DIGITAL_D6_SWITCH_POWER_DOWN);
                                            SET_D6_SWITCH_POWER_STATUS(_DIGITAL_D6_SWITCH_POWER_DOWN);

                                            if(GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE)
                                            {
                                                CLR_DP_AUTO_SEARCH_SWITCH();
                                            }
                                            else
                                            {
                                                SET_DP_AUTO_SEARCH_SWITCH();
                                            }

                                            if(GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT)
                                            {
                                                ScalerDpVersionSwitch(_D0_INPUT_PORT, UserInterfaceGetDPVersion(_D0_INPUT_PORT), UserInterfaceGetDpMSTCapablePort());
                                            }
                                            else if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
                                            {
                                                ScalerDpVersionSwitch(_D6_INPUT_PORT, UserInterfaceGetDPVersion(_D6_INPUT_PORT), UserInterfaceGetDpMSTCapablePort());
                                            }
                                        }
                                    }

                                    break;
                                }
                                else
                                {
                                    if(SysSourceGetInputPort() == GET_D6_SWITCH_SELECT())
                                    {
                                        break;
                                    }
                                }
                            }
                            else
                            {
                                if(GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_POLLING_MODE)
                                {
                                    if((SysRegionConvertPortToRegionIndex(_D0_INPUT_PORT) == _REGION_INDEX_NONE) &&
                                       (SysRegionConvertPortToRegionIndex(_D6_INPUT_PORT) == _REGION_INDEX_NONE))
                                    {
                                        SET_D6_SWITCH_SELECT(UserInterfaceGetDpSwitchSelectPort());
                                    }
                                }

                                if(ucDpSwitchPortBackup != GET_D6_SWITCH_SELECT())
                                {
                                    PCB_DIGITAL_D6_SWITCH_POWER(_DIGITAL_D6_SWITCH_POWER_DOWN);
                                    SET_D6_SWITCH_POWER_STATUS(_DIGITAL_D6_SWITCH_POWER_DOWN);
                                    CLR_DP_AUTO_SEARCH_SWITCH();

                                    if(GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT)
                                    {
                                        ScalerDpVersionSwitch(_D0_INPUT_PORT, UserInterfaceGetDPVersion(_D0_INPUT_PORT), UserInterfaceGetDpMSTCapablePort());
                                    }
                                    else if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
                                    {
                                        ScalerDpVersionSwitch(_D6_INPUT_PORT, UserInterfaceGetDPVersion(_D6_INPUT_PORT), UserInterfaceGetDpMSTCapablePort());
                                    }
                                }

                                break;
                            }
                        }
                        else // D0 DP Port and D6 DP Port are Not in the Same Group
                        {
                            if(SysSourceGetInputPort() == _D0_INPUT_PORT)
                            {
                                SET_D6_SWITCH_SELECT(_D0_INPUT_PORT);
                            }
                            else if(SysSourceGetInputPort() == _D6_INPUT_PORT)
                            {
                                SET_D6_SWITCH_SELECT(_D6_INPUT_PORT);
                            }

                            if(ucDpSwitchPortBackup != GET_D6_SWITCH_SELECT())
                            {
                                PCB_DIGITAL_D6_SWITCH_POWER(_DIGITAL_D6_SWITCH_POWER_DOWN);
                                SET_D6_SWITCH_POWER_STATUS(_DIGITAL_D6_SWITCH_POWER_DOWN);
                                CLR_DP_AUTO_SEARCH_SWITCH();

                                if(GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT)
                                {
                                    ScalerDpVersionSwitch(_D0_INPUT_PORT, UserInterfaceGetDPVersion(_D0_INPUT_PORT), UserInterfaceGetDpMSTCapablePort());
                                }
                                else if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
                                {
                                    ScalerDpVersionSwitch(_D6_INPUT_PORT, UserInterfaceGetDPVersion(_D6_INPUT_PORT), UserInterfaceGetDpMSTCapablePort());
                                }
                            }

                            break;
                        }
                    }
#else
                    // Check source valid as fixed port or auto-search candidate
                    if((SysSourceCheckMultiFixedPortTarget(g_ucSearchIndex) == _TRUE) ||
                       (SysSourceCheckMultiAutoSearchTarget(g_ucSearchIndex) == _TRUE))
                    {
                        break;
                    }
#endif
                }
                ucCount++;
            }
            while(ucCount < _INPUT_PORT_VALID);

            if(g_ucSearchIndex != ucBackupSearchIndex)
            {
                SET_SOURCE_SEARCH_TIME_INITIAL();
                SET_SOURCE_SEARCH_PORT_INITIAL();
                SET_SOURCE_SEARCH_TIME_REACTIVE();
            }

            if((g_ucSearchIndex != ucBackupSearchIndex) ||
               (GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_DELAY_REACTIVE_MODE))
            {
                if(GET_MODE_STATE() == _MODE_STATUS_POWER_SAVING)
                {
                    SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);
                }
                else
                {
                    if((SysRegionGetDisplayStateCount(_DISPLAY_STATE_NO_SIGNAL) +
                        SysRegionGetDisplayStateCount(_DISPLAY_STATE_OOR) +
                        SysRegionGetDisplayStateCount(_DISPLAY_STATE_ACTIVE)) ==
                       GET_RGN_MAX_DISPLAY_REGION())
                    {
                        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_POLLING_MODE);
                        SET_SOURCE_SEARCH_TIME_REACTIVE();
                    }
                    else
                    {
                        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);
                    }
                }
            }

            break;

        default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Port Initial Function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceScanPortInitial(void)
{
    SysSourceInterfaceSwitch(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex)), GET_PORT_TYPE(GET_INPUTPORT_TYPE(g_ucSearchIndex)), GET_SOURCE_SEARCH_DELAY_MODE());

    switch(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex)))
    {
        case _A0_INPUT_PORT:

            switch(GET_PORT_TYPE(GET_INPUTPORT_TYPE(g_ucSearchIndex)))
            {
#if(_VGA_SUPPORT == _ON)

                case _PORT_VGA:

                    DebugMessageSystem("7. VGA Port Initial", 1);

                    if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
                    {
                        ScalerSyncProcScanInitial();
                    }

                    break;
#endif

                default:
                    break;
            }

            break;

        case _D0_INPUT_PORT:

            switch(GET_PORT_TYPE(GET_INPUTPORT_TYPE(g_ucSearchIndex)))
            {
#if(_D0_TMDS_SUPPORT == _ON)

                case _PORT_DVI:
                case _PORT_HDMI:
                case _PORT_MHL:

                    DebugMessageSystem("7. D0 Port TMDS Port Initial", 1);

                    if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
                    {
                        ScalerTMDSRx0TMDSScanInitial(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex)));
                    }

                    break;
#endif

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

                case _PORT_DP:

                    DebugMessageSystem("7. D0 DP Port Initial", 1);

                    if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
                    {
                        ScalerSyncDpScanInitial(SysSourceGetInputPort());
                    }

                    break;
#endif

                default:
                    break;
            }

            break;

        case _D1_INPUT_PORT:

            switch(GET_PORT_TYPE(GET_INPUTPORT_TYPE(g_ucSearchIndex)))
            {
#if(_D1_TMDS_SUPPORT == _ON)

                case _PORT_DVI:
                case _PORT_HDMI:
                case _PORT_MHL:

                    DebugMessageSystem("7. D1 Port TMDS Port Initial", 1);

                    if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
                    {
                        ScalerTMDSRx1TMDSScanInitial(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex)));
                    }

                    break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

                case _PORT_DP:

                    DebugMessageSystem("7. D1 DP Port Initial", 1);

                    if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
                    {
                        ScalerSyncDpScanInitial(SysSourceGetInputPort());
                    }

                    break;
#endif
                default:
                    break;
            }

            break;

        case _D2_INPUT_PORT:

            switch(GET_PORT_TYPE(GET_INPUTPORT_TYPE(g_ucSearchIndex)))
            {
#if((_D2_TMDS_SUPPORT == _ON) && (_D2_INPUT_PORT_TYPE != _D2_DUAL_DVI_PORT) && (_D2_INPUT_PORT_TYPE != _D2_NO_PORT))

                case _PORT_DVI:
                case _PORT_HDMI:
                case _PORT_MHL:

                    DebugMessageSystem("7. D2 Port TMDS Port Initial", 1);

                    if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
                    {
                        ScalerTMDSRx2TMDSScanInitial(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex)));
                    }

                    break;
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)

                case _PORT_DUAL_DVI:

                    DebugMessageSystem("7. D2 Port Dual DVI Initial", 1);

                    if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
                    {
                        ScalerTMDSRx2DualDVIScanInitial(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex)));
                    }

                    break;
#endif

                default:
                    break;
            }

            break;

        case _D3_INPUT_PORT:

            switch(GET_PORT_TYPE(GET_INPUTPORT_TYPE(g_ucSearchIndex)))
            {
#if((_D3_TMDS_SUPPORT == _ON) && (_D3_INPUT_PORT_TYPE != _D3_DUAL_DVI_PORT) && (_D3_INPUT_PORT_TYPE != _D3_NO_PORT))

                case _PORT_DVI:
                case _PORT_HDMI:
                case _PORT_MHL:

                    DebugMessageSystem("7. D3 Port TMDS Port Initial", 1);

                    if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
                    {
                        ScalerTMDSRx3TMDSScanInitial(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex)));
                    }

                    break;
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT)

                case _PORT_DUAL_DVI:

                    DebugMessageSystem("7. D3 Port Dual DVI Initial", 1);

                    if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
                    {
                        ScalerTMDSRx3DualDVIScanInitial(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex)));
                    }

                    break;
#endif

                default:
                    break;
            }

            break;

        case _D4_INPUT_PORT:

            switch(GET_PORT_TYPE(GET_INPUTPORT_TYPE(g_ucSearchIndex)))
            {
#if((_D4_TMDS_SUPPORT == _ON) && (_D4_INPUT_PORT_TYPE != _D4_DUAL_DVI_PORT) && (_D4_INPUT_PORT_TYPE != _D4_NO_PORT))

                case _PORT_DVI:
                case _PORT_HDMI:
                case _PORT_MHL:

                    DebugMessageSystem("7. D4 Port TMDS Port Initial", 1);

                    if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
                    {
                        ScalerTMDSRx4TMDSScanInitial(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex)));
                    }

                    break;
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)

                case _PORT_DUAL_DVI:

                    DebugMessageSystem("7. D4 Port Dual DVI Initial", 1);

                    if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
                    {
                        ScalerTMDSRx4DualDVIScanInitial(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex)));
                    }

                    break;
#endif

                default:
                    break;
            }

            break;

        case _D5_INPUT_PORT:

            switch(GET_PORT_TYPE(GET_INPUTPORT_TYPE(g_ucSearchIndex)))
            {
#if((_D5_TMDS_SUPPORT == _ON) && (_D5_INPUT_PORT_TYPE != _D5_NO_PORT))

                case _PORT_DVI:
                case _PORT_HDMI:
                case _PORT_MHL:

                    DebugMessageSystem("7. D5 Port TMDS Port Initial", 1);

                    if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
                    {
                        ScalerTMDSRx5TMDSScanInitial(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex)));
                    }

                    break;
#endif

                default:
                    break;
            }

            break;

        case _D6_INPUT_PORT:

#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)

            DebugMessageSystem("7. D6 DP Port Initial", SysSourceGetInputPort());

            if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
            {
                ScalerSyncDpScanInitial(SysSourceGetInputPort());
            }

#endif // End of #if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)

            break;

        case _D7_INPUT_PORT:

            switch(GET_PORT_TYPE(GET_INPUTPORT_TYPE(g_ucSearchIndex)))
            {
#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)

                case _PORT_DP:

                    DebugMessageSystem("7. D7 DP Port Initial", 1);

                    if(GET_POWER_STATUS() == _POWER_STATUS_NORMAL)
                    {
                        ScalerSyncDpScanInitial(SysSourceGetInputPort());
                    }

                    SET_D7_SWITCH_SELECT(_D7_INPUT_PORT);

                    break;
#endif

                default:
                    break;
            }

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Initial Source Switch Flags
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceInitial(void)
{
    BYTE ucPort = 0;

    SysSourceSetSearchPriority(_NO_INPUT_PORT, _INPUT_PORT_PRIORITY_NONE);
    SysSourceSetSearchGroup(_NO_INPUT_PORT, _INPUT_PORT_GROUP_NONE);
    SysSourceSetDefaultSearchTime(_SOURCE_INPUT_TYPE_VGA, _SOURCE_DEFAULT_SEARCH_TIME_VGA);
    SysSourceSetDefaultSearchTime(_SOURCE_INPUT_TYPE_HDMI, _SOURCE_DEFAULT_SEARCH_TIME_HDMI);
    SysSourceSetDefaultSearchTime(_SOURCE_INPUT_TYPE_DVI, _SOURCE_DEFAULT_SEARCH_TIME_DVI);
    SysSourceSetDefaultSearchTime(_SOURCE_INPUT_TYPE_DP, _SOURCE_DEFAULT_SEARCH_TIME_DP);
    SysSourceSetNoCableSearchTime(_SOURCE_INPUT_TYPE_VGA, _SOURCE_DEFAULT_SEARCH_TIME_VGA_NO_CABLE);
    SysSourceSetNoCableSearchTime(_SOURCE_INPUT_TYPE_HDMI, _SOURCE_DEFAULT_SEARCH_TIME_HDMI_NO_CABLE);
    SysSourceSetNoCableSearchTime(_SOURCE_INPUT_TYPE_DVI, _SOURCE_DEFAULT_SEARCH_TIME_DVI_NO_CABLE);
    SysSourceSetNoCableSearchTime(_SOURCE_INPUT_TYPE_DP, _SOURCE_DEFAULT_SEARCH_TIME_DP_NO_CABLE);

    if((UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != _SOURCE_SWITCH_AUTO_IN_GROUP) &&
       (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != _SOURCE_SWITCH_FIXED_PORT))
    {
        UserCommonNVRamRestoreSystemData();
    }

    SET_SOURCE_SCAN_TYPE(UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE));

#if(_MULTI_DISPLAY_MAX != 0x01)
    SET_SOURCE_AUTO_TARGET(UserCommonNVRamGetSystemData(_AUTO_SEARCH_TARGET));
#else
    SET_SOURCE_AUTO_TARGET(_REGION_INDEX_0);
#endif

    switch(GET_SOURCE_SCAN_TYPE())
    {
        case _SOURCE_SWITCH_FIXED_PORT:
            // Switch to region 0
            g_ucSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0));
            break;

        default:
            // Switch to auto target source
            g_ucSearchIndex = GET_RGN_SOURCE_INDEX(GET_SOURCE_AUTO_TARGET());
            break;
    }

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

    PCB_DIGITAL_D6_SWITCH_POWER(_DIGITAL_D6_SWITCH_POWER_DOWN);
    SET_D6_SWITCH_POWER_STATUS(_DIGITAL_D6_SWITCH_POWER_DOWN);
    CLR_DP_AUTO_SEARCH_SWITCH();

    if((SysSourceGetInputPort() == _D0_INPUT_PORT) || (SysSourceGetInputPort() == _D6_INPUT_PORT))
    {
        if(SysSourceGetInputPort() == _D0_INPUT_PORT)
        {
            SET_D6_SWITCH_SELECT(_D0_INPUT_PORT);
        }
        else if(SysSourceGetInputPort() == _D6_INPUT_PORT)
        {
            SET_D6_SWITCH_SELECT(_D6_INPUT_PORT);
        }
    }
    else
    {
        SET_D6_SWITCH_SELECT(UserInterfaceGetDpSwitchSelectPort());
    }
#endif

    for(ucPort = 0; ucPort < _INPUT_PORT_VALID; ucPort++)
    {
        SET_CABLE_DETECT(ucPort, _FALSE);
    }

#if(_DIGITAL_PORT_SUPPORT == _ON)

    if(UserCommonNVRamGetSystemData(_DP_HOT_PLUG_DC_OFF_HIGH) == _TRUE)
    {
        SET_DP_DC_OFF_HPD_HIGH();
    }
    else
    {
        CLR_DP_DC_OFF_HPD_HIGH();
    }

    if(UserCommonNVRamGetSystemData(_HDMI_HOT_PLUG_SUPPORT) == _TRUE)
    {
        SET_HDMI_HOTPLUG_TOGGLE();
        SET_HDMI_HOTPLUG_TIME(UserCommonNVRamGetSystemData(_HDMI_HOT_PLUG_SUPPORT_TIME));
    }
    else
    {
        CLR_HDMI_HOTPLUG_TOGGLE();
    }

    if(UserCommonNVRamGetSystemData(_DIGITAL_COLOR_INFO_CHANGE_RESET) == _TRUE)
    {
        SET_DIGITAL_COLOR_INFO_CHANGE_RESET();
    }
    else
    {
        CLR_DIGITAL_COLOR_INFO_CHANGE_RESET();
    }
#endif

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
    CLR_SOURCE_DP_SWITCH_TIMEOUT();
#endif

#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
    CLR_SOURCE_DP_DUAL_SWITCH_TIMEOUT();
#endif
}

//--------------------------------------------------
// Description  : Source Stable Check Function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit SysSourceStableCheck(BYTE ucRegionIndex)
{
    BYTE ucSourceType = GET_RGN_SOURCE_TYPE(ucRegionIndex);
    BYTE ucInputPort = GET_RGN_INPUT_PORT(ucRegionIndex);

    switch(ucSourceType)
    {
#if(_VGA_SUPPORT == _ON)
        case _SOURCE_VGA:

            return ScalerSyncProcStableDetect();

            break;
#endif

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
        case _SOURCE_DVI:
        case _SOURCE_HDMI:

            switch(ucInputPort)
            {
#if(_D0_TMDS_SUPPORT == _ON)
                case _D0_INPUT_PORT:
                    return ScalerTMDSRx0TMDSStableDetect(ucSourceType);
#endif

#if(_D1_TMDS_SUPPORT == _ON)
                case _D1_INPUT_PORT:
                    return ScalerTMDSRx1TMDSStableDetect(ucSourceType);
#endif

#if(_D2_TMDS_SUPPORT == _ON)

                case _D2_INPUT_PORT:

#if(_D2_INPUT_PORT_TYPE != _D2_DUAL_DVI_PORT)
                    return ScalerTMDSRx2TMDSStableDetect(ucSourceType);
#else
                    if(ScalerSyncGetDualDVIMode(_D2_INPUT_PORT) == _TRUE)
                    {
                        return ((ScalerTMDSRx2TMDSStableDetect(GET_RGN_SOURCE_TYPE(ucRegionIndex)) == _TRUE) &&
                                (ScalerTMDSRx3TMDSStableDetect(GET_RGN_SOURCE_TYPE(ucRegionIndex)) == _TRUE));
                    }
                    else
                    {
                        return ScalerTMDSRx3TMDSStableDetect(GET_RGN_SOURCE_TYPE(ucRegionIndex));
                    }
#endif

#endif

#if(_D3_TMDS_SUPPORT == _ON)

                case _D3_INPUT_PORT:

#if(_D3_INPUT_PORT_TYPE != _D3_DUAL_DVI_PORT)
                    return ScalerTMDSRx3TMDSStableDetect(ucSourceType);
#else
                    if(ScalerSyncGetDualDVIMode(_D3_INPUT_PORT) == _TRUE)
                    {
                        return ((ScalerTMDSRx3TMDSStableDetect(GET_RGN_SOURCE_TYPE(ucRegionIndex)) == _TRUE) &&
                                (ScalerTMDSRx4TMDSStableDetect(GET_RGN_SOURCE_TYPE(ucRegionIndex)) == _TRUE));
                    }
                    else
                    {
                        return ScalerTMDSRx4TMDSStableDetect(GET_RGN_SOURCE_TYPE(ucRegionIndex));
                    }
#endif

#endif

#if(_D4_TMDS_SUPPORT == _ON)

                case _D4_INPUT_PORT:

#if(_D4_INPUT_PORT_TYPE != _D4_DUAL_DVI_PORT)
                    return ScalerTMDSRx4TMDSStableDetect(ucSourceType);
#else
                    if(ScalerSyncGetDualDVIMode(_D4_INPUT_PORT) == _TRUE)
                    {
                        return ((ScalerTMDSRx4TMDSStableDetect(GET_RGN_SOURCE_TYPE(ucRegionIndex)) == _TRUE) &&
                                (ScalerTMDSRx5TMDSStableDetect(GET_RGN_SOURCE_TYPE(ucRegionIndex)) == _TRUE));
                    }
                    else
                    {
                        return ScalerTMDSRx5TMDSStableDetect(GET_RGN_SOURCE_TYPE(ucRegionIndex));
                    }
#endif

#endif

#if(_D5_TMDS_SUPPORT == _ON)
                case _D5_INPUT_PORT:
                    return ScalerTMDSRx5TMDSStableDetect(ucSourceType);
#endif
                default:
                    break;
            }

            break;
#endif // End of #if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))

#if(_DP_SUPPORT == _ON)
        case _SOURCE_DP:

            return ScalerSyncDpStableDetect(ucInputPort);

            break;
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get Source Type
// Input Value  : None
// Output Value : Source Type --> VGA/DVI/HDMI/DP
//--------------------------------------------------
BYTE SysSourceGetSourceType(void)
{
    return GET_SOURCE_TYPE(g_ucSearchIndex);
}

//--------------------------------------------------
// Description  : Get Input Port
// Input Value  : None
// Output Value : ucInputPort --> Input Port
//--------------------------------------------------
BYTE SysSourceGetInputPort(void)
{
    return SysSourceGetSpecificInputPort(g_ucSearchIndex);
}

//--------------------------------------------------
// Description  : Get Input Port
// Input Value  : Search Index
// Output Value : ucInputPort --> Input Port
//--------------------------------------------------
BYTE SysSourceGetSpecificInputPort(BYTE ucIndex)
{
    return GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucIndex));
}

//--------------------------------------------------
// Description  : Get Input Port Type
// Input Value  : None
// Output Value : ucInputPort --> Input Port Type
//--------------------------------------------------
BYTE SysSourceGetInputPortType(BYTE ucInputPort)
{
    return GET_INPUTPORT_TYPE(SysSourceConvertSearchPort(ucInputPort));
}

#if((_SLEEP_AUDIO_SUPPORT == _ON) && ((_DP_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP))))
//--------------------------------------------------
// Description  : Get Current Playback Search Index
// Input Value  : None
// Output Value : Search Index
//--------------------------------------------------
BYTE SysSourceGetAudioPlaybackPort(void)
{
    return SysSourceGetSpecificInputPort(GET_AUDIO_PLAYBACK_SEARCH_INDEX());
}
#endif

//--------------------------------------------------
// Description  : Get Source Type
// Input Value  : ucInputPort --> Input Port(A0,A1,D0,D1,V1)
// Output Value : None
//--------------------------------------------------
void SysSourceSwitchInputPort(BYTE ucInputPort)
{
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
    BYTE ucDpSwitchPortBackup = GET_D6_SWITCH_SELECT();
#endif

    g_ucSearchIndex = SysSourceConvertSearchPort(ucInputPort);

    // Initialize source search if not judged already
    if(GET_SOURCE_JUDGE(g_ucSearchIndex) == _FALSE)
    {
        SET_SOURCE_DETECTING();
        SET_SOURCE_SEARCH_TIME_INITIAL();
        SET_SOURCE_SEARCH_PORT_INITIAL();
        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);
        SET_SOURCE_SEARCH_TIME_REACTIVE();
        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
    }

    // Check region source index for auto search target
    if(SysRegionConvertPortToRegion(ucInputPort) == _DISPLAY_RGN_NONE)
    {
        if(GET_SOURCE_SCAN_TYPE() != _SOURCE_SWITCH_FIXED_PORT)
        {
            SET_RGN_SOURCE_INDEX(GET_SOURCE_AUTO_TARGET(), g_ucSearchIndex);
        }
    }

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

    if(SysSourceGetInputPort() == _D0_INPUT_PORT)
    {
        SET_D6_SWITCH_SELECT(_D0_INPUT_PORT);
    }
    else if(SysSourceGetInputPort() == _D6_INPUT_PORT)
    {
        SET_D6_SWITCH_SELECT(_D6_INPUT_PORT);
    }
    else
    {
        if((SysRegionConvertPortToRegionIndex(_D0_INPUT_PORT) == _REGION_INDEX_NONE) &&
           (SysRegionConvertPortToRegionIndex(_D6_INPUT_PORT) == _REGION_INDEX_NONE))
        {
            SET_D6_SWITCH_SELECT(UserInterfaceGetDpSwitchSelectPort());
        }
    }

    if(ucDpSwitchPortBackup != GET_D6_SWITCH_SELECT())
    {
        PCB_DIGITAL_D6_SWITCH_POWER(_DIGITAL_D6_SWITCH_POWER_DOWN);
        SET_D6_SWITCH_POWER_STATUS(_DIGITAL_D6_SWITCH_POWER_DOWN);
        CLR_DP_AUTO_SEARCH_SWITCH();

        if(GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT)
        {
            ScalerDpVersionSwitch(_D0_INPUT_PORT, UserInterfaceGetDPVersion(_D0_INPUT_PORT), UserInterfaceGetDpMSTCapablePort());
        }
        else if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
        {
            ScalerDpVersionSwitch(_D6_INPUT_PORT, UserInterfaceGetDPVersion(_D6_INPUT_PORT), UserInterfaceGetDpMSTCapablePort());
        }
    }
#endif

#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
    if(GET_MODE_DISPLAY_MODE() == _DISPLAY_MODE_1P)
    {
        if(SysSourceGetInputPort() == _D7_INPUT_PORT)
        {
            if(UserCommonInterfaceDpGetDualPortEdidSelectStatus() == _FALSE)
            {
                UserCommonInterfaceDpDualPortEdidTableSwitch(_D7_INPUT_PORT);
            }
        }
        else if((SysSourceGetInputPort() == _D0_INPUT_PORT) || (SysSourceGetInputPort() == _D1_INPUT_PORT))
        {
            if(UserCommonInterfaceDpGetDualPortEdidSelectStatus() == _TRUE)
            {
                UserCommonInterfaceDpDualPortEdidTableSwitch(_D0_INPUT_PORT);
                UserCommonInterfaceDpDualPortEdidTableSwitch(_D1_INPUT_PORT);
            }
        }
        else
        {
            if(UserInterfaceGetDpDualDefaultPort() == _TRUE)
            {
                if(UserCommonInterfaceDpGetDualPortEdidSelectStatus() == _FALSE)
                {
                    UserCommonInterfaceDpDualPortEdidTableSwitch(_D7_INPUT_PORT);
                }
            }
            else
            {
                if(UserCommonInterfaceDpGetDualPortEdidSelectStatus() == _TRUE)
                {
                    UserCommonInterfaceDpDualPortEdidTableSwitch(_D0_INPUT_PORT);
                    UserCommonInterfaceDpDualPortEdidTableSwitch(_D1_INPUT_PORT);
                }
            }
        }
    }
    else
    {
        if(UserCommonInterfaceDpGetDualPortEdidSelectStatus() == _TRUE)
        {
            UserCommonInterfaceDpDualPortEdidTableSwitch(_D0_INPUT_PORT);
            UserCommonInterfaceDpDualPortEdidTableSwitch(_D1_INPUT_PORT);
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Get Source Type
// Input Value  : ucInputPort --> Input Port(A0,A1,D0,D1,V1)
// Output Value : None
//--------------------------------------------------
void SysSourceSwitchRegionSearchPort(BYTE ucInputPort)
{
    g_ucSearchIndex = SysSourceConvertSearchPort(ucInputPort);

    // Initialize source search if not judged already
    if(GET_SOURCE_JUDGE(g_ucSearchIndex) == _FALSE)
    {
        SET_SOURCE_DETECTING();
        SET_SOURCE_SEARCH_TIME_INITIAL();
        SET_SOURCE_SEARCH_PORT_INITIAL();
        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);
        SET_SOURCE_SEARCH_TIME_REACTIVE();
        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
    }

    // Check region source index for auto search target
    if(SysRegionConvertPortToRegion(ucInputPort) == _DISPLAY_RGN_NONE)
    {
        if(GET_SOURCE_SCAN_TYPE() != _SOURCE_SWITCH_FIXED_PORT)
        {
            SET_RGN_SOURCE_INDEX(GET_SOURCE_AUTO_TARGET(), g_ucSearchIndex);
        }
    }
}

//--------------------------------------------------
// Description  : Source Search Time Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceSearchTimeReset(void)
{
    BYTE ucCnt = 0x00;

    for(ucCnt = 0; ucCnt < _INPUT_PORT_VALID; ucCnt++)
    {
        CLR_SOURCE_SEARCH_TIMES(ucCnt);
    }
}

//--------------------------------------------------
// Description  : Source Information Reset To Display Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceInfoResetToDisplayInitial(void)
{
    BYTE ucCnt = 0x00;

    for(ucCnt = 0; ucCnt < _INPUT_PORT_VALID; ucCnt++)
    {
        // Reset variables for unused interfaces
        if((GET_SOURCE_JUDGE(ucCnt) == _FALSE) ||
           (SysRegionConvertSourceIndexToRegionIndex(ucCnt) == _REGION_INDEX_NONE))
        {
            SET_SOURCE_TYPE(ucCnt, _SOURCE_NONE);
            CLR_SOURCE_SEARCH_TIMES(ucCnt);
            CLR_SOURCE_JUDGE(ucCnt);
            CLR_SOURCE_PREDETECT(ucCnt);

            // sync reset
            ScalerSyncResetProc(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucCnt)));

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
            {
                ScalerSyncDigitalClrColorimetryChanged(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucCnt)));
                ScalerSyncDigitalClrColorimetryExtChanged(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucCnt)));
                ScalerSyncDigitalClrQuantizationChanged(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucCnt)));
            }
        }
    }

    CLR_SOURCE_SWITCH_FINISH();

    // Clear Source Flags
    if(GET_SOURCE_JUDGE(g_ucSearchIndex) == _FALSE)
    {
        SET_SOURCE_DETECTING();
        SET_SOURCE_SEARCH_TIME_INITIAL();
        SET_SOURCE_SEARCH_TIME_REACTIVE();

#if(_SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT == _ON)
        if((GET_MODE_STATE() == _MODE_STATUS_POWER_OFF) ||
           ((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_DELAY_REACTIVE_MODE) && (GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_DELAY_NVRAM_PORT_MODE)))
#else
        if((GET_MODE_STATE() == _MODE_STATUS_POWER_OFF) || (GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_DELAY_REACTIVE_MODE))
#endif
        {
            SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);
        }

        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
    }
    else
    {
        // Clear source detecting for interface switch
        CLR_SOURCE_DETECTING();
    }

    // Switch off unused interfaces
    SysSourceInterfaceSwitch(GET_INPUT_PORT(GET_INPUTPORT_TYPE(g_ucSearchIndex)), GET_PORT_TYPE(GET_INPUTPORT_TYPE(g_ucSearchIndex)), GET_SOURCE_SEARCH_DELAY_MODE());
}

//--------------------------------------------------
// Description  : Source Information Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceInfoReset(void)
{
    BYTE ucCnt = 0x00;

    for(ucCnt = 0; ucCnt < _INPUT_PORT_VALID; ucCnt++)
    {
        // Interface Reset Process
        SET_SOURCE_TYPE(ucCnt, _SOURCE_NONE);
        CLR_SOURCE_SEARCH_TIMES(ucCnt);
        CLR_SOURCE_JUDGE(ucCnt);
        CLR_SOURCE_PREDETECT(ucCnt);
    }

    SET_SOURCE_SEARCH_PORT_INITIAL();

    // Clear Source Flags
    SET_SOURCE_DETECTING();
    SET_SOURCE_SEARCH_TIME_INITIAL();
    CLR_SOURCE_SWITCH_FINISH();

#if(_SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT == _ON)
    if((GET_MODE_STATE() == _MODE_STATUS_POWER_OFF) ||
       ((GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_DELAY_REACTIVE_MODE) && (GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_DELAY_NVRAM_PORT_MODE)))
#else
    if((GET_MODE_STATE() == _MODE_STATUS_POWER_OFF) || (GET_SOURCE_SEARCH_DELAY_MODE() != _SOURCE_SEARCH_DELAY_REACTIVE_MODE))
#endif
    {
        SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);

        SET_SOURCE_SEARCH_TIME_REACTIVE();
    }

    ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
    CLR_DP_AUTO_SEARCH_SWITCH();
#endif

#if((_D0_INPUT_PORT_TYPE != _D0_NO_PORT) && (_D0_DP_TYPE_C_SUPPORT == _ON))
    SET_D0_DP_TYPE_C_CABLE_DETECT();
#endif

#if((_D1_INPUT_PORT_TYPE != _D1_NO_PORT) && (_D1_DP_TYPE_C_SUPPORT == _ON))
    SET_D1_DP_TYPE_C_CABLE_DETECT();
#endif

#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_DP_TYPE_C_SUPPORT == _ON))
    SET_D6_DP_TYPE_C_CABLE_DETECT();
#endif
}

//--------------------------------------------------
// Description  : Source reset region process
// Input Value  : ucRegionIndex --> region index
// Output Value : None
//--------------------------------------------------
void SysSourceResetRegion(BYTE ucRegionIndex)
{
    if(GET_MODE_DISPLAY_MODE() == _DISPLAY_MODE_1P)
    {
        // Clear all source ready flags
        SysSourceInfoReset();

        // Perform sync reset
        ScalerSyncResetProc(GET_RGN_INPUT_PORT(ucRegionIndex));

        if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
        {
            ScalerSyncDigitalClrColorimetryChanged(GET_RGN_INPUT_PORT(ucRegionIndex));
            ScalerSyncDigitalClrColorimetryExtChanged(GET_RGN_INPUT_PORT(ucRegionIndex));
            ScalerSyncDigitalClrQuantizationChanged(GET_RGN_INPUT_PORT(ucRegionIndex));
        }

        // Cancel timer events
        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING);
        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_NOSUPPORT_STATE);
        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_NOSIGNAL_STATE);
    }
#if(_MULTI_DISPLAY_MAX != 0x01)
    else
    {
        BYTE ucIndex = 0x00;

        // Search for dulicated display region
        for(ucIndex = 0x00; ucIndex < GET_RGN_MAX_DISPLAY_REGION(); ++ucIndex)
        {
            if((ucIndex != ucRegionIndex) &&
               (GET_RGN_SOURCE_INDEX(ucRegionIndex) == GET_RGN_SOURCE_INDEX(ucIndex)))
            {
                break;
            }
        }

        // Reset when no duplicate region exist, or source not judged
        if((ucIndex == GET_RGN_MAX_DISPLAY_REGION()) ||
           (GET_RGN_SOURCE_JUDGE(ucRegionIndex) == _FALSE))
        {
            DebugMessageSystem("SRC reset region", ucRegionIndex);

            // Clear source ready flags
            CLR_SOURCE_JUDGE(GET_RGN_SOURCE_INDEX(ucRegionIndex));
            SET_SOURCE_TYPE(GET_RGN_SOURCE_INDEX(ucRegionIndex), _SOURCE_NONE);
            CLR_SOURCE_PREDETECT(GET_RGN_SOURCE_INDEX(ucRegionIndex));

            // Clear source search times
            if((GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_AUTO_IN_GROUP) &&
               (GET_SOURCE_AUTO_TARGET() == ucRegionIndex))
            {
                SysSourceSearchTimeReset();
            }
            else
            {
                CLR_SOURCE_SEARCH_TIMES(GET_RGN_SOURCE_INDEX(ucRegionIndex));
            }

            // Clear source switch finished flag
            CLR_SOURCE_SWITCH_FINISH();

            // Reset source handler if current search index being reset
            if(GET_RGN_SOURCE_INDEX(ucRegionIndex) == g_ucSearchIndex)
            {
                SET_SOURCE_DETECTING();
                SET_SOURCE_SEARCH_TIME_INITIAL();
                SET_SOURCE_SEARCH_TIME_REACTIVE();
                SET_SOURCE_SEARCH_PORT_INITIAL();
                SET_SOURCE_SEARCH_DELAY_MODE(_SOURCE_SEARCH_DELAY_DEFAULT_MODE);
            }

            // Perform sync reset
            ScalerSyncResetProc(GET_RGN_INPUT_PORT(ucRegionIndex));

            if(GET_DIGITAL_COLOR_INFO_CHANGE_RESET() == _FALSE)
            {
                ScalerSyncDigitalClrColorimetryChanged(GET_RGN_INPUT_PORT(ucRegionIndex));
                ScalerSyncDigitalClrColorimetryExtChanged(GET_RGN_INPUT_PORT(ucRegionIndex));
                ScalerSyncDigitalClrQuantizationChanged(GET_RGN_INPUT_PORT(ucRegionIndex));
            }

            // Cancel measure related timing events
            if(ucRegionIndex == GET_SOURCE_MEASURE_TARGET_INDEX())
            {
                ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_NOSUPPORT_STATE);
                ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_NOSIGNAL_STATE);
            }
        }
    }
#endif
}

//--------------------------------------------------
// Description  : Source Cable Status Detection
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceCableDetection(void)
{
    BYTE ucI = 0;

    // Get Each Cable Status From Pin
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
    SET_A0_CABLE_STATUS(!PCB_A0_PIN());
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
    SET_D0_CABLE_STATUS((!PCB_D0_PIN()) | PCB_D0_MHL_DETECT());
#else
    SET_D0_CABLE_STATUS(!PCB_D0_PIN());
#endif
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
    SET_D1_CABLE_STATUS((!PCB_D1_PIN()) | PCB_D1_MHL_DETECT());
#else
    SET_D1_CABLE_STATUS(!PCB_D1_PIN());
#endif
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
    SET_D2_CABLE_STATUS((!PCB_D2_PIN()) | PCB_D2_MHL_DETECT());
#else
    SET_D2_CABLE_STATUS(!PCB_D2_PIN());
#endif
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
    SET_D3_CABLE_STATUS((!PCB_D3_PIN()) | PCB_D3_MHL_DETECT());
#else
    SET_D3_CABLE_STATUS(!PCB_D3_PIN());
#endif
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
    SET_D4_CABLE_STATUS((!PCB_D4_PIN()) | PCB_D4_MHL_DETECT());
#else
    SET_D4_CABLE_STATUS(!PCB_D4_PIN());
#endif
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
    SET_D5_CABLE_STATUS((!PCB_D5_PIN()) | PCB_D5_MHL_DETECT());
#else
    SET_D5_CABLE_STATUS(!PCB_D5_PIN());
#endif
#endif

#if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)
    SET_D6_CABLE_STATUS(!PCB_D6_PIN());
#endif

    for(ucI = 0; ucI < _INPUT_PORT_VALID; ucI++)
    {
        SET_CABLE_STATUS_CHANGE(ucI, _FALSE);

        switch(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucI)))
        {
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)

            case _A0_INPUT_PORT:
                if(GET_CABLE_DETECT(ucI) != GET_A0_CABLE_STATUS())
                {
                    ScalerTimerDelayXms(10);

                    SET_A0_CABLE_STATUS(!PCB_A0_PIN());

                    if(GET_CABLE_DETECT(ucI) != GET_A0_CABLE_STATUS())
                    {
                        SET_CABLE_DETECT(ucI, GET_A0_CABLE_STATUS());
                        SET_CABLE_STATUS_CHANGE(ucI, _TRUE);

                        DebugMessageSystem("0. Cable Status Chanaged A0", ucI);
                    }
                }
                break;
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)

            case _D0_INPUT_PORT:

#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
                if((GET_CABLE_DETECT(ucI) != GET_D0_CABLE_STATUS()) || (GET_D0_TMDS_MODE() != PCB_D0_MHL_DETECT()))
#else
                if(GET_CABLE_DETECT(ucI) != GET_D0_CABLE_STATUS())
#endif

                {
                    ScalerTimerDelayXms(10);

#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
                    SET_D0_CABLE_STATUS((!PCB_D0_PIN()) | PCB_D0_MHL_DETECT());
#else
                    SET_D0_CABLE_STATUS(!PCB_D0_PIN());
#endif

#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
                    if((GET_CABLE_DETECT(ucI) != GET_D0_CABLE_STATUS()) || (GET_D0_TMDS_MODE() != PCB_D0_MHL_DETECT()))
#else
                    if(GET_CABLE_DETECT(ucI) != GET_D0_CABLE_STATUS())
#endif

                    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
                        if(GET_D0_CABLE_STATUS() == _TRUE)
                        {
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                            if(GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT)
#endif
                            {
                                if((GET_DP_DC_OFF_HPD_HIGH() == _ON) || (GET_POWER_STATUS() != _POWER_STATUS_OFF))
                                {
                                    if(!((GET_POWER_STATUS() == _POWER_STATUS_OFF) && (UserInterfaceGetDpMSTCapablePort() == _DP_MST_RX0_PORT)))
                                    {
                                        ScalerTimerReactiveTimerEvent(SEC(0.1), _SCALER_TIMER_EVENT_DP_RX0_HOTPLUG_ASSERTED);
                                    }
                                }
                            }
                        }
                        else
                        {
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                            if(GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT)
#endif
                            {
#if(_DP_MST_SUPPORT == _ON)
                                // Cable Unplug Reset
                                ScalerDpRxMstCableUnplugReset(_D0_INPUT_PORT);

                                CLR_DP_RX0_VALID_VIDEO_CHECK();

                                // Reset MST Backup
                                ScalerDpRx0MstInfoBackup(_DP_MST_BACKUP_INFO_RESET);
#endif

#if(_AUDIO_SUPPORT == _ON)
                                SysAudioDpAudioSecDataResetProc(_D0_INPUT_PORT);
#else
                                ScalerSyncDpSecDataReset(_D0_INPUT_PORT);
#endif
                                CLR_DP_RX_D0_MARGIN_LINK_HBR_RBR();
                                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HOTPLUG_ASSERTED);
                                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HDCP_LONG_HOTPLUG_EVENT);
                                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_LINK_STATUS_IRQ);

                                ScalerDpRx0HotPlugEvent(_DP_HPD_LOW);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
                                // HDCP2 Reset Proc
                                ScalerDpRx0Hdcp2ResetProc();
#endif
                            }
                        }

#elif(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

#if(_MHL_DEBUG_WITHOUT_CBUS_MODE == _ON)
                        SET_D0_TMDS_MODE(_TMDS_MHL_MODE);
#else
                        SET_D0_TMDS_MODE(PCB_D0_MHL_DETECT());
#endif
                        if(GET_D0_CABLE_STATUS() == _TRUE)
                        {
                            if(GET_D0_TMDS_MODE() == _TMDS_MHL_MODE)
                            {
                                ScalerMHLRx0ModeMHLSetting();

#if(_D0_HDMI_2_0_SUPPORT == _ON)
                                // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                                ScalerTMDSRx0HDMI2HPDRRIRQEnable(_DISABLE);
#endif
                            }
                            else
                            {
                                ScalerMHLRx0ModeHdmiSetting();

#if(_D0_HDMI_2_0_SUPPORT == _ON)
                                // Enable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                                ScalerTMDSRx0HDMI2HPDRRIRQEnable(_ENABLE);
#endif
                            }
                        }
                        else
                        {
                            ScalerMHLRx0ModeHdmiSetting();
                            ScalerTMDSRx0HotPlugEvent();

#if(_D0_HDMI_2_0_SUPPORT == _ON)
                            // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                            ScalerTMDSRx0HDMI2HPDRRIRQEnable(_DISABLE);
#endif

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
                            // HDCP2 Reset Proc
                            // ScalerTMDSRx0Hdcp2ResetProc();
#endif
                        }

#elif(_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT)

                        if(GET_D0_CABLE_STATUS() == _TRUE)
                        {
#if(_D0_HDMI_2_0_SUPPORT == _ON)
                            // Enable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                            ScalerTMDSRx0HDMI2HPDRRIRQEnable(_ENABLE);
#endif
                        }
                        else
                        {
#if(_D0_HDMI_2_0_SUPPORT == _ON)
                            // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                            ScalerTMDSRx0HDMI2HPDRRIRQEnable(_DISABLE);
#endif

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
                            // HDCP2 Reset Proc
                            // ScalerTMDSRx0Hdcp2ResetProc();
#endif
                        }

#endif // End of #if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

                        SET_SOURCE_SEARCH_PORT_INITIAL();
                        SET_CABLE_DETECT(ucI, GET_D0_CABLE_STATUS());
                        SET_CABLE_STATUS_CHANGE(ucI, _TRUE);

                        DebugMessageSystem("0. Cable Status Changed D0", ucI);
                    }
                }

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                if((GET_D6_SWITCH_POWER_STATUS() == _DIGITAL_D6_SWITCH_POWER_DOWN) && (GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT))
                {
                    ScalerTimerActiveTimerEvent(SEC(0.1), _SCALER_TIMER_EVENT_DP_RX0_HOTPLUG_ASSERTED);
                }
#endif

#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_DP_MST_SUPPORT == _ON))
                ScalerDpRx0AuxChPowerStatusCheck(GET_CABLE_DETECT(ucI));
#endif

                break;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)

            case _D1_INPUT_PORT:

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
                if((GET_CABLE_DETECT(ucI) != GET_D1_CABLE_STATUS()) || (GET_D1_TMDS_MODE() != PCB_D1_MHL_DETECT()))
#else
                if(GET_CABLE_DETECT(ucI) != GET_D1_CABLE_STATUS())
#endif
                {
                    ScalerTimerDelayXms(10);

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
                    SET_D1_CABLE_STATUS((!PCB_D1_PIN()) | PCB_D1_MHL_DETECT());
#else
                    SET_D1_CABLE_STATUS(!PCB_D1_PIN());
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
                    if((GET_CABLE_DETECT(ucI) != GET_D1_CABLE_STATUS()) || (GET_D1_TMDS_MODE() != PCB_D1_MHL_DETECT()))
#else
                    if(GET_CABLE_DETECT(ucI) != GET_D1_CABLE_STATUS())
#endif
                    {
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
                        if(GET_D1_CABLE_STATUS() == _TRUE)
                        {
                            if((GET_DP_DC_OFF_HPD_HIGH() == _ON) || (GET_POWER_STATUS() != _POWER_STATUS_OFF))
                            {
                                if(!((GET_POWER_STATUS() == _POWER_STATUS_OFF) && (UserInterfaceGetDpMSTCapablePort() == _DP_MST_RX1_PORT)))
                                {
                                    ScalerTimerReactiveTimerEvent(SEC(0.1), _SCALER_TIMER_EVENT_DP_RX1_HOTPLUG_ASSERTED);
                                }
                            }
                        }
                        else
                        {
#if(_DP_MST_SUPPORT == _ON)
                            // Cable Unplug Reset
                            ScalerDpRxMstCableUnplugReset(_D1_INPUT_PORT);

                            // Reset MST Backup
                            ScalerDpRx1MstInfoBackup(_DP_MST_BACKUP_INFO_RESET);
#endif

#if(_AUDIO_SUPPORT == _ON)
                            SysAudioDpAudioSecDataResetProc(_D1_INPUT_PORT);
#else
                            ScalerSyncDpSecDataReset(_D1_INPUT_PORT);
#endif
                            CLR_DP_RX_D1_MARGIN_LINK_HBR_RBR();
                            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HOTPLUG_ASSERTED);
                            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HDCP_LONG_HOTPLUG_EVENT);
                            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_LINK_STATUS_IRQ);

                            ScalerDpRx1HotPlugEvent(_DP_HPD_LOW);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
                            // HDCP2 Reset Proc
                            ScalerDpRx1Hdcp2ResetProc();
#endif
                        }
#elif(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

#if(_MHL_DEBUG_WITHOUT_CBUS_MODE == _ON)
                        SET_D1_TMDS_MODE(_TMDS_MHL_MODE);
#else
                        SET_D1_TMDS_MODE(PCB_D1_MHL_DETECT());
#endif

                        if(GET_D1_CABLE_STATUS() == _TRUE)
                        {
                            if(GET_D1_TMDS_MODE() == _TMDS_MHL_MODE)
                            {
                                ScalerMHLRx1ModeMHLSetting();

#if(_D1_HDMI_2_0_SUPPORT == _ON)
                                // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                                ScalerTMDSRx1HDMI2HPDRRIRQEnable(_DISABLE);
#endif
                            }
                            else
                            {
                                ScalerMHLRx1ModeHdmiSetting();

#if(_D1_HDMI_2_0_SUPPORT == _ON)
                                // Enable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                                ScalerTMDSRx1HDMI2HPDRRIRQEnable(_ENABLE);
#endif
                            }
                        }
                        else
                        {
                            ScalerMHLRx1ModeHdmiSetting();
                            ScalerTMDSRx1HotPlugEvent();

#if(_D1_HDMI_2_0_SUPPORT == _ON)
                            // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                            ScalerTMDSRx1HDMI2HPDRRIRQEnable(_DISABLE);
#endif

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
                            // ScalerTMDSRx1Hdcp2ResetProc();
#endif
                        }

#elif(_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT)

                        if(GET_D1_CABLE_STATUS() == _TRUE)
                        {
#if(_D1_HDMI_2_0_SUPPORT == _ON)
                            // Enable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                            ScalerTMDSRx1HDMI2HPDRRIRQEnable(_ENABLE);
#endif
                        }
                        else
                        {
#if(_D1_HDMI_2_0_SUPPORT == _ON)
                            // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                            ScalerTMDSRx1HDMI2HPDRRIRQEnable(_DISABLE);
#endif

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
                            // ScalerTMDSRx1Hdcp2ResetProc();
#endif
                        }

#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

                        SET_SOURCE_SEARCH_PORT_INITIAL();
                        SET_CABLE_DETECT(ucI, GET_D1_CABLE_STATUS());
                        SET_CABLE_STATUS_CHANGE(ucI, _TRUE);

                        DebugMessageSystem("0. Cable Status Changed D1", ucI);
                    }
                }

#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_DP_MST_SUPPORT == _ON))
                ScalerDpRx1AuxChPowerStatusCheck(GET_CABLE_DETECT(ucI));
#endif

                break;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)

            case _D2_INPUT_PORT:

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
                if((GET_CABLE_DETECT(ucI) != GET_D2_CABLE_STATUS()) || (GET_D2_TMDS_MODE() != PCB_D2_MHL_DETECT()))
#else
                if(GET_CABLE_DETECT(ucI) != GET_D2_CABLE_STATUS())
#endif
                {
                    ScalerTimerDelayXms(10);

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
                    SET_D2_CABLE_STATUS((!PCB_D2_PIN()) | PCB_D2_MHL_DETECT());
#else
                    SET_D2_CABLE_STATUS(!PCB_D2_PIN());
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
                    if((GET_CABLE_DETECT(ucI) != GET_D2_CABLE_STATUS()) || (GET_D2_TMDS_MODE() != PCB_D2_MHL_DETECT()))
#else
                    if(GET_CABLE_DETECT(ucI) != GET_D2_CABLE_STATUS())
#endif

                    {
#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

#if(_MHL_DEBUG_WITHOUT_CBUS_MODE == _ON)
                        SET_D2_TMDS_MODE(_TMDS_MHL_MODE);
#else
                        SET_D2_TMDS_MODE(PCB_D2_MHL_DETECT());
#endif
                        if(GET_D2_CABLE_STATUS() == _TRUE)
                        {
                            if(GET_D2_TMDS_MODE() == _TMDS_MHL_MODE)
                            {
                                ScalerMHLRx2ModeMHLSetting();

#if(_D2_HDMI_2_0_SUPPORT == _ON)
                                // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                                ScalerTMDSRx2HDMI2HPDRRIRQEnable(_DISABLE);
#endif
                            }
                            else
                            {
                                ScalerMHLRx2ModeHdmiSetting();

#if(_D2_HDMI_2_0_SUPPORT == _ON)
                                // Enable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                                ScalerTMDSRx2HDMI2HPDRRIRQEnable(_ENABLE);
#endif
                            }
                        }
                        else
                        {
                            ScalerMHLRx2ModeHdmiSetting();
                            ScalerTMDSRx2HotPlugEvent();

#if(_D2_HDMI_2_0_SUPPORT == _ON)
                            // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                            ScalerTMDSRx2HDMI2HPDRRIRQEnable(_DISABLE);
#endif

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
                            ScalerTMDSRx2Hdcp2ResetProc();
#endif
                        }

#elif(_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) // Else of #if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

                        if(GET_D2_CABLE_STATUS() == _TRUE)
                        {
#if(_D2_HDMI_2_0_SUPPORT == _ON)
                            // Enable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                            ScalerTMDSRx2HDMI2HPDRRIRQEnable(_ENABLE);
#endif
                        }
                        else
                        {
#if(_D2_HDMI_2_0_SUPPORT == _ON)
                            // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                            ScalerTMDSRx2HDMI2HPDRRIRQEnable(_DISABLE);
#endif

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
                            ScalerTMDSRx2Hdcp2ResetProc();
#endif
                        }
#endif // End of #if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

                        SET_SOURCE_SEARCH_PORT_INITIAL();
                        SET_CABLE_DETECT(ucI, GET_D2_CABLE_STATUS());
                        SET_CABLE_STATUS_CHANGE(ucI, _TRUE);

                        DebugMessageSystem("0. Cable Status Changed D2", ucI);
                    }
                }
                break;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)

            case _D3_INPUT_PORT:

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
                if((GET_CABLE_DETECT(ucI) != GET_D3_CABLE_STATUS()) || (GET_D3_TMDS_MODE() != PCB_D3_MHL_DETECT()))
#else
                if(GET_CABLE_DETECT(ucI) != GET_D3_CABLE_STATUS())
#endif
                {
                    ScalerTimerDelayXms(10);

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
                    SET_D3_CABLE_STATUS((!PCB_D3_PIN()) | PCB_D3_MHL_DETECT());
#else
                    SET_D3_CABLE_STATUS(!PCB_D3_PIN());
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
                    if((GET_CABLE_DETECT(ucI) != GET_D3_CABLE_STATUS()) || (GET_D3_TMDS_MODE() != PCB_D3_MHL_DETECT()))
#else
                    if(GET_CABLE_DETECT(ucI) != GET_D3_CABLE_STATUS())
#endif

                    {
#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)

#if(_MHL_DEBUG_WITHOUT_CBUS_MODE == _ON)
                        SET_D3_TMDS_MODE(_TMDS_MHL_MODE);
#else
                        SET_D3_TMDS_MODE(PCB_D3_MHL_DETECT());
#endif

                        if(GET_D3_CABLE_STATUS() == _TRUE)
                        {
                            if(GET_D3_TMDS_MODE() == _TMDS_MHL_MODE)
                            {
                                ScalerMHLRx3ModeMHLSetting();

#if(_D3_HDMI_2_0_SUPPORT == _ON)
                                // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                                ScalerTMDSRx3HDMI2HPDRRIRQEnable(_DISABLE);
#endif
                            }
                            else
                            {
                                ScalerMHLRx3ModeHdmiSetting();

#if(_D3_HDMI_2_0_SUPPORT == _ON)
                                // Enable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                                ScalerTMDSRx3HDMI2HPDRRIRQEnable(_ENABLE);
#endif
                            }
                        }
                        else
                        {
                            ScalerMHLRx3ModeHdmiSetting();
                            ScalerTMDSRx3HotPlugEvent();

#if(_D3_HDMI_2_0_SUPPORT == _ON)
                            // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                            ScalerTMDSRx3HDMI2HPDRRIRQEnable(_DISABLE);
#endif

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
                            ScalerTMDSRx3Hdcp2ResetProc();
#endif
                        }

#elif(_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) // Else of #if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)

                        if(GET_D3_CABLE_STATUS() == _TRUE)
                        {
#if(_D3_HDMI_2_0_SUPPORT == _ON)
                            // Enable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                            ScalerTMDSRx3HDMI2HPDRRIRQEnable(_ENABLE);
#endif
                        }
                        else
                        {
#if(_D3_HDMI_2_0_SUPPORT == _ON)
                            // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                            ScalerTMDSRx3HDMI2HPDRRIRQEnable(_DISABLE);
#endif

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
                            ScalerTMDSRx3Hdcp2ResetProc();
#endif
                        }
#endif // End of #if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)

                        SET_SOURCE_SEARCH_PORT_INITIAL();
                        SET_CABLE_DETECT(ucI, GET_D3_CABLE_STATUS());
                        SET_CABLE_STATUS_CHANGE(ucI, _TRUE);

                        DebugMessageSystem("0. Cable Status Changed D3", ucI);
                    }
                }
                break;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
            case _D4_INPUT_PORT:

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
                if((GET_CABLE_DETECT(ucI) != GET_D4_CABLE_STATUS()) || (GET_D4_TMDS_MODE() != PCB_D4_MHL_DETECT()))
#else
                if(GET_CABLE_DETECT(ucI) != GET_D4_CABLE_STATUS())
#endif
                {
                    ScalerTimerDelayXms(10);

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
                    SET_D4_CABLE_STATUS((!PCB_D4_PIN()) | PCB_D4_MHL_DETECT());
#else
                    SET_D4_CABLE_STATUS(!PCB_D4_PIN());
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
                    if((GET_CABLE_DETECT(ucI) != GET_D4_CABLE_STATUS()) || (GET_D4_TMDS_MODE() != PCB_D4_MHL_DETECT()))
#else
                    if(GET_CABLE_DETECT(ucI) != GET_D4_CABLE_STATUS())
#endif

                    {
#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)

#if(_MHL_DEBUG_WITHOUT_CBUS_MODE == _ON)
                        SET_D4_TMDS_MODE(_TMDS_MHL_MODE);
#else
                        SET_D4_TMDS_MODE(PCB_D4_MHL_DETECT());
#endif

                        if(GET_D4_CABLE_STATUS() == _TRUE)
                        {
                            if(GET_D4_TMDS_MODE() == _TMDS_MHL_MODE)
                            {
                                ScalerMHLRx4ModeMHLSetting();

#if(_D4_HDMI_2_0_SUPPORT == _ON)
                                // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                                ScalerTMDSRx4HDMI2HPDRRIRQEnable(_DISABLE);
#endif
                            }
                            else
                            {
                                ScalerMHLRx4ModeHdmiSetting();

#if(_D4_HDMI_2_0_SUPPORT == _ON)
                                // Enable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                                ScalerTMDSRx4HDMI2HPDRRIRQEnable(_ENABLE);
#endif
                            }
                        }
                        else
                        {
                            ScalerMHLRx4ModeHdmiSetting();
                            ScalerTMDSRx4HotPlugEvent();

#if(_D4_HDMI_2_0_SUPPORT == _ON)
                            // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                            ScalerTMDSRx4HDMI2HPDRRIRQEnable(_DISABLE);
#endif

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
                            ScalerTMDSRx4Hdcp2ResetProc();
#endif
                        }

#elif(_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) // Else of #if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)

                        if(GET_D4_CABLE_STATUS() == _TRUE)
                        {
#if(_D4_HDMI_2_0_SUPPORT == _ON)
                            // Enable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                            ScalerTMDSRx4HDMI2HPDRRIRQEnable(_ENABLE);
#endif
                        }
                        else
                        {
#if(_D4_HDMI_2_0_SUPPORT == _ON)
                            // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                            ScalerTMDSRx4HDMI2HPDRRIRQEnable(_DISABLE);
#endif

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
                            ScalerTMDSRx4Hdcp2ResetProc();
#endif
                        }
#endif // End of #if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)

                        SET_SOURCE_SEARCH_PORT_INITIAL();
                        SET_CABLE_DETECT(ucI, GET_D4_CABLE_STATUS());
                        SET_CABLE_STATUS_CHANGE(ucI, _TRUE);

                        DebugMessageSystem("0. Cable Status Changed D4", ucI);
                    }
                }

                break;
#endif // End of #if(_D4_INPUT_PORT_TYPE != _D4_INPUT_PORT_TYPE)

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
            case _D5_INPUT_PORT:

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
                if((GET_CABLE_DETECT(ucI) != GET_D5_CABLE_STATUS()) || (GET_D5_TMDS_MODE() != PCB_D5_MHL_DETECT()))
#else
                if(GET_CABLE_DETECT(ucI) != GET_D5_CABLE_STATUS())
#endif
                {
                    ScalerTimerDelayXms(10);

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
                    SET_D5_CABLE_STATUS((!PCB_D5_PIN()) | PCB_D5_MHL_DETECT());
#else
                    SET_D5_CABLE_STATUS(!PCB_D5_PIN());
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
                    if((GET_CABLE_DETECT(ucI) != GET_D5_CABLE_STATUS()) || (GET_D5_TMDS_MODE() != PCB_D5_MHL_DETECT()))
#else
                    if(GET_CABLE_DETECT(ucI) != GET_D5_CABLE_STATUS())
#endif

                    {
#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

#if(_MHL_DEBUG_WITHOUT_CBUS_MODE == _ON)
                        SET_D5_TMDS_MODE(_TMDS_MHL_MODE);
#else
                        SET_D5_TMDS_MODE(PCB_D5_MHL_DETECT());
#endif

                        if(GET_D5_CABLE_STATUS() == _TRUE)
                        {
                            if(GET_D5_TMDS_MODE() == _TMDS_MHL_MODE)
                            {
                                ScalerMHLRx5ModeMHLSetting();

#if(_D5_HDMI_2_0_SUPPORT == _ON)
                                // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                                ScalerTMDSRx5HDMI2HPDRRIRQEnable(_DISABLE);
#endif
                            }
                            else
                            {
                                ScalerMHLRx5ModeHdmiSetting();

#if(_D5_HDMI_2_0_SUPPORT == _ON)
                                // Enable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                                ScalerTMDSRx5HDMI2HPDRRIRQEnable(_ENABLE);
#endif
                            }
                        }
                        else
                        {
                            ScalerMHLRx5ModeHdmiSetting();
                            ScalerTMDSRx5HotPlugEvent();

#if(_D5_HDMI_2_0_SUPPORT == _ON)
                            // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                            ScalerTMDSRx5HDMI2HPDRRIRQEnable(_DISABLE);
#endif

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
                            ScalerTMDSRx5Hdcp2ResetProc();
#endif
                        }

#elif(_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) // Else of #if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

                        if(GET_D5_CABLE_STATUS() == _TRUE)
                        {
#if(_D5_HDMI_2_0_SUPPORT == _ON)
                            // Enable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                            ScalerTMDSRx5HDMI2HPDRRIRQEnable(_ENABLE);
#endif
                        }
                        else
                        {
#if(_D5_HDMI_2_0_SUPPORT == _ON)
                            // Disable HPD Rising to Falling IRQ for HDMI 2.0 Protocol CTS
                            ScalerTMDSRx5HDMI2HPDRRIRQEnable(_DISABLE);
#endif

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
                            ScalerTMDSRx5Hdcp2ResetProc();
#endif
                        }

#endif // End of #if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

                        SET_SOURCE_SEARCH_PORT_INITIAL();
                        SET_CABLE_DETECT(ucI, GET_D5_CABLE_STATUS());
                        SET_CABLE_STATUS_CHANGE(ucI, _TRUE);

                        DebugMessageSystem("0. Cable Status Changed D5", ucI);
                    }
                }
                break;
#endif // End of #if(_D5_INPUT_PORT_TYPE != _D5_INPUT_PORT_TYPE)

#if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)

            case _D6_INPUT_PORT:

                if(GET_CABLE_DETECT(ucI) != GET_D6_CABLE_STATUS())
                {
                    ScalerTimerDelayXms(10);

                    SET_D6_CABLE_STATUS(!PCB_D6_PIN());

                    if(GET_CABLE_DETECT(ucI) != GET_D6_CABLE_STATUS())
                    {
                        if(GET_D6_CABLE_STATUS() == _TRUE)
                        {
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                            if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
#endif
                            {
                                if((GET_DP_DC_OFF_HPD_HIGH() == _ON) || (GET_POWER_STATUS() != _POWER_STATUS_OFF))
                                {
                                    if(!((GET_POWER_STATUS() == _POWER_STATUS_OFF) && (UserInterfaceGetDpMSTCapablePort() == _DP_MST_RX6_PORT)))
                                    {
                                        ScalerTimerReactiveTimerEvent(SEC(0.1), _SCALER_TIMER_EVENT_DP_RX0_HOTPLUG_ASSERTED);
                                    }
                                }
                            }
                        }
                        else
                        {
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                            if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
#endif
                            {
#if(_DP_MST_SUPPORT == _ON)
                                // Cable Unplug Reset
                                ScalerDpRxMstCableUnplugReset(_D0_INPUT_PORT);

                                CLR_DP_RX0_VALID_VIDEO_CHECK();

                                // Reset MST Backup
                                ScalerDpRx6MstInfoBackup(_DP_MST_BACKUP_INFO_RESET);
#endif

#if(_AUDIO_SUPPORT == _ON)
                                SysAudioDpAudioSecDataResetProc(_D0_INPUT_PORT);
#else
                                ScalerSyncDpSecDataReset(_D0_INPUT_PORT);
#endif
                                CLR_DP_RX_D6_MARGIN_LINK_HBR_RBR();
                                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HOTPLUG_ASSERTED);
                                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HDCP_LONG_HOTPLUG_EVENT);
                                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_LINK_STATUS_IRQ);

                                ScalerDpRx0HotPlugEvent(_DP_HPD_LOW);
                            }
                        }

                        SET_CABLE_DETECT(ucI, GET_D6_CABLE_STATUS());
                        SET_CABLE_STATUS_CHANGE(ucI, _TRUE);

                        DebugMessageSystem("0. Cable Status Changed D6", ucI);
                    }
                }

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                if((GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT) && (GET_D6_SWITCH_POWER_STATUS() == _DIGITAL_D6_SWITCH_POWER_DOWN))
                {
                    ScalerTimerActiveTimerEvent(SEC(0.1), _SCALER_TIMER_EVENT_DP_RX0_HOTPLUG_ASSERTED);
                }
#endif

#if(_DP_MST_SUPPORT == _ON)
                ScalerDpRx6AuxChPowerStatusCheck(GET_CABLE_DETECT(ucI));
#endif
                break;

#endif // End of #if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)

#if(_D7_INPUT_PORT_TYPE != _D7_NO_PORT)

            case _D7_INPUT_PORT:

                /////////////////////////////////////////////
                // D7 cable detect
                /////////////////////////////////////////////

                if(GET_CABLE_DETECT(ucI) != (GET_D0_CABLE_STATUS() & GET_D1_CABLE_STATUS()))
                {
                    SET_CABLE_DETECT(ucI, (GET_D0_CABLE_STATUS() & GET_D1_CABLE_STATUS()));
                    SET_CABLE_STATUS_CHANGE(ucI, _TRUE);
                }

                break;
#endif // End of #if(_D7_INPUT_PORT_TYPE != _D7_NO_PORT)

            default:
                break;
        }
    }
}

//--------------------------------------------------
// Description  : Judge Source Search Times
// Input Value  : target search times
// Output Value : True --> search times of valid ports equal to target times
//--------------------------------------------------
bit SysSourceCheckTargetTimes(BYTE ucTargetTimes)
{
    BYTE ucCnt = 0x00;

    for(ucCnt = 0; ucCnt < _INPUT_PORT_VALID; ucCnt++)
    {
        if(GET_SOURCE_SEARCH_TIMES(ucCnt) != ucTargetTimes)
        {
            return _FALSE;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Set Scan Type for User
// Input Value  : Preferred Scan Type
// Output Value : None
//--------------------------------------------------
void SysSourceSetScanType(BYTE ucScanType)
{
    SET_SOURCE_SCAN_TYPE(ucScanType);
}

//--------------------------------------------------
// Description  : Get Scan Type for User
// Input Value  : None
// Output Value : Current Scan Type
//--------------------------------------------------
BYTE SysSourceGetScanType(void)
{
    return GET_SOURCE_SCAN_TYPE();
}

//--------------------------------------------------
// Description  : Convert Search Port to Search Index
// Input Value  : Input Port
// Output Value : Search Index
//--------------------------------------------------
BYTE SysSourceConvertSearchPort(BYTE ucInputPort)
{
    BYTE ucTemp = 0;

    while(ucTemp < _INPUT_PORT_VALID)
    {
        if(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucTemp)) == ucInputPort)
        {
            return ucTemp;
        }

        ucTemp++;
    }

    return 0;
}

//--------------------------------------------------
// Description  : Get Source Cable Detect
// Input Value  : ucInputPort
// Output Value : _TRUE => Cable Detected, _FASLE => Cable Undected
//--------------------------------------------------
bit SysSourceGetCableDetect(BYTE ucInputPort)
{
    return GET_CABLE_DETECT(SysSourceConvertSearchPort(ucInputPort));
}

//--------------------------------------------------
// Description  : Get Source Cable Status Change
// Input Value  : ucInputPort
// Output Value : _TRUE => Cable Status Changed
//--------------------------------------------------
bit SysSourceGetCableStatusChange(BYTE ucInputPort)
{
    return GET_CABLE_STATUS_CHANGE(SysSourceConvertSearchPort(ucInputPort));
}

//--------------------------------------------------
// Description  : Source Reset when Cable Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceCableResetProc(void)
{
}

//--------------------------------------------------
// Description  : Source First Active Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceFirstActiveProc(void)
{
}

//--------------------------------------------------
// Description  : Source Power Off Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourcePowerOffProc(void)
{
    // Clear Display event flag
    CLR_RGN_DISPLAY_INFO_ALL();

    switch(GET_SOURCE_SCAN_TYPE())
    {
        case _SOURCE_SWITCH_FIXED_PORT:
            // Switch to region 0
            g_ucSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0));
            break;

        default:
            // Switch to stored auto target source
            switch(GET_SOURCE_AUTO_TARGET())
            {
                case _REGION_INDEX_0:
                    g_ucSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0));
                    break;
                case _REGION_INDEX_1:
                    g_ucSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_1));
                    break;
                case _REGION_INDEX_2:
                    g_ucSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_2));
                    break;
                case _REGION_INDEX_3:
                    g_ucSearchIndex = SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_3));
                    break;
                default:
                    break;
            }

            SET_RGN_SOURCE_INDEX(GET_SOURCE_AUTO_TARGET(), g_ucSearchIndex);

            break;
    }

    if(GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_DELL_HOTKEY_FIXED)
    {
        SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_FIXED_PORT);
    }
    else if(GET_SOURCE_SCAN_TYPE() == _SOURCE_SWITCH_DELL_HOTKEY_AUTO)
    {
        SET_SOURCE_SCAN_TYPE(_SOURCE_SWITCH_AUTO_IN_GROUP);
    }
}

//--------------------------------------------------
// Description  : Input Port Search Priority Select
// Input Value  : Priority and Input Port
// Output Value : None
//--------------------------------------------------
void SysSourceSetSearchPriority(EnumSourceSearchPort enumPort, EnumSourceSearchPortPriority enumSourcePriority)
{
    BYTE ucSearchIndexBackup = SysSourceConvertSearchPort(enumPort);
    BYTE ucInputPortBackup = SysSourceGetSpecificInputPort(enumSourcePriority);

    if((enumSourcePriority >= _INPUT_PORT_PRIORITY_NONE) || (enumPort >= _NO_INPUT_PORT) || (ucSearchIndexBackup == enumSourcePriority))
    {
        return;
    }

    SET_SOURCE_TYPE_BACKUP(GET_SOURCE_TYPE(enumSourcePriority));
    SET_SOURCE_SEARCH_TIMES_BACKUP(GET_SOURCE_SEARCH_TIMES(enumSourcePriority));
    SET_SOURCE_JUDGE_BACKUP(GET_SOURCE_JUDGE(enumSourcePriority));
    SET_SOURCE_PREDETECT_BACKUP(GET_SOURCE_PREDETECT(enumSourcePriority));
    SET_CABLE_DETECT_BACKUP(GET_CABLE_DETECT(enumSourcePriority));
    SET_CABLE_STATUS_CHANGE_BACKUP(GET_CABLE_STATUS_CHANGE(enumSourcePriority));

    SET_SOURCE_TYPE(enumSourcePriority, GET_SOURCE_TYPE(ucSearchIndexBackup));
    SET_SOURCE_SEARCH_TIMES(enumSourcePriority, GET_SOURCE_SEARCH_TIMES(ucSearchIndexBackup));
    SET_SOURCE_JUDGE(enumSourcePriority, GET_SOURCE_JUDGE(ucSearchIndexBackup));
    SET_SOURCE_PREDETECT(enumSourcePriority, GET_SOURCE_PREDETECT(ucSearchIndexBackup));
    SET_CABLE_DETECT(enumSourcePriority, GET_CABLE_DETECT(ucSearchIndexBackup));
    SET_CABLE_STATUS_CHANGE(enumSourcePriority, GET_CABLE_STATUS_CHANGE(ucSearchIndexBackup));

    SET_SOURCE_TYPE(ucSearchIndexBackup, GET_SOURCE_TYPE_BACKUP());
    SET_SOURCE_SEARCH_TIMES(ucSearchIndexBackup, GET_SOURCE_SEARCH_TIMES_BACKUP());
    SET_SOURCE_JUDGE(ucSearchIndexBackup, GET_SOURCE_JUDGE_BACKUP());
    SET_SOURCE_PREDETECT(ucSearchIndexBackup, GET_SOURCE_PREDETECT_BACKUP());
    SET_CABLE_DETECT(ucSearchIndexBackup, GET_CABLE_DETECT_BACKUP());
    SET_CABLE_STATUS_CHANGE(ucSearchIndexBackup, GET_CABLE_STATUS_CHANGE_BACKUP());

    if(GET_RGN_SOURCE_INDEX(_REGION_INDEX_0) == ucSearchIndexBackup)
    {
        SET_RGN_SOURCE_INDEX(_REGION_INDEX_0, enumSourcePriority);
    }

    if(enumSourcePriority == g_ucSearchIndex)
    {
        g_ucSearchIndex = ucSearchIndexBackup;
    }
    else if(ucSearchIndexBackup == g_ucSearchIndex)
    {
        g_ucSearchIndex = enumSourcePriority;
    }

    g_pucSourceSearchPriority[enumSourcePriority] = enumPort;
    g_pucSourceSearchPriority[ucSearchIndexBackup] = ucInputPortBackup;
}

//--------------------------------------------------
// Description  : Input Port Search Group Select
// Input Value  : Group and Input Port
// Output Value : None
//--------------------------------------------------
void SysSourceSetSearchGroup(EnumSourceSearchPort enumPort, EnumSourceSearchGroup enumSourceGroup)
{
    if((enumPort >= _NO_INPUT_PORT) || (enumSourceGroup >= _INPUT_PORT_GROUP_NONE))
    {
        return;
    }

    g_pucSourceSearchGroup[enumPort] = enumSourceGroup;
}

//--------------------------------------------------
// Description  : Input Port Default Search Time Setting
// Input Value  : enumInputType --> VGA/HDMI/DVI/DP
///               usDefaultSearchTime --> Default Search Time
// Output Value : None
//--------------------------------------------------
void SysSourceSetDefaultSearchTime(EnumSourceInputType enumInputType, WORD usDefaultSearchTime)
{
    switch(enumInputType)
    {
#if(_VGA_PORT_EXIST == _ON)
        case _SOURCE_INPUT_TYPE_VGA:
            g_usSourceDefaultSearchTimeVga = usDefaultSearchTime;
            break;
#endif

#if(_HDMI_PORT_EXIST == _ON)
        case _SOURCE_INPUT_TYPE_HDMI:
            g_usSourceDefaultSearchTimeHdmi = usDefaultSearchTime;
            break;
#endif

#if(_DVI_PORT_EXIST == _ON)
        case _SOURCE_INPUT_TYPE_DVI:
            g_usSourceDefaultSearchTimeDvi = usDefaultSearchTime;
            break;
#endif

#if(_DP_PORT_EXIST == _ON)
        case _SOURCE_INPUT_TYPE_DP:
            g_usSourceDefaultSearchTimeDp = usDefaultSearchTime;
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Input Port No Cable Search Time Setting
// Input Value  : enumInputType --> VGA/HDMI/DVI/DP
///               usNoCableSearchTime --> No Cable Search Time
// Output Value : None
//--------------------------------------------------
void SysSourceSetNoCableSearchTime(EnumSourceInputType enumInputType, WORD usNoCableSearchTime)
{
    switch(enumInputType)
    {
#if(_VGA_PORT_EXIST == _ON)
        case _SOURCE_INPUT_TYPE_VGA:
            g_usSourceNoCableSearchTimeVga = usNoCableSearchTime;
            break;
#endif

#if(_HDMI_PORT_EXIST == _ON)
        case _SOURCE_INPUT_TYPE_HDMI:
            g_usSourceNoCableSearchTimeHdmi = usNoCableSearchTime;
            break;
#endif

#if(_DVI_PORT_EXIST == _ON)
        case _SOURCE_INPUT_TYPE_DVI:
            g_usSourceNoCableSearchTimeDvi = usNoCableSearchTime;
            break;
#endif

#if(_DP_PORT_EXIST == _ON)
        case _SOURCE_INPUT_TYPE_DP:
            g_usSourceNoCableSearchTimeDp = usNoCableSearchTime;
            break;
#endif

        default:
            break;
    }
}

#if(_MULTI_DISPLAY_MAX != 0x01)
//--------------------------------------------------
// Description  : Check whether source can be switch to in auto-search scan mode
// Input Value  : ucSearchIndex --> source index
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit SysSourceCheckMultiFixedPortTarget(BYTE ucSearchIndex)
{
    BYTE ucRegionIndex = 0;

    for(ucRegionIndex = 0; ucRegionIndex < GET_RGN_MAX_DISPLAY_REGION(); ++ucRegionIndex)
    {
        if(GET_RGN_SOURCE_JUDGE(ucRegionIndex) == _TRUE)
        {
            continue;
        }

        if(GET_RGN_SOURCE_INDEX(ucRegionIndex) == ucSearchIndex)
        {
#if(_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_ACER_STYLE)

            if((GET_SOURCE_SCAN_TYPE() != _SOURCE_SWITCH_FIXED_PORT) && (GET_RGN_SOURCE_JUDGE(GET_SOURCE_AUTO_TARGET()) == _FALSE))
            {
                SET_RGN_SOURCE_INDEX(GET_SOURCE_AUTO_TARGET(), g_ucSearchIndex);
            }
#endif
            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check whether source can be switch to in auto-search scan mode
// Input Value  : ucSearchIndex --> source index
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit SysSourceCheckMultiAutoSearchTarget(BYTE ucSearchIndex)
{
#if(_D7_INPUT_PORT_TYPE != _D7_NO_PORT)
    // Skip D7 from multi-display auto-search
    if(GET_INPUT_PORT(GET_INPUTPORT_TYPE(ucSearchIndex)) == _D7_INPUT_PORT)
    {
        return _FALSE;
    }
#endif

    if((GET_RGN_SOURCE_JUDGE(GET_SOURCE_AUTO_TARGET()) == _FALSE) &&
       (UserInterfaceGetRegionAutoSearchStatus(GET_RGN_DISPLAY_REGION(GET_SOURCE_AUTO_TARGET()), SysSourceGetSpecificInputPort(ucSearchIndex)) == _TRUE))
    {
        SET_RGN_SOURCE_INDEX(GET_SOURCE_AUTO_TARGET(), ucSearchIndex);
        return _TRUE;
    }

    return _FALSE;
}
#endif

//--------------------------------------------------
// Description  : Set auto search target region
// Input Value  : enumDisplayRegion --> select region
// Output Value : None
//--------------------------------------------------
void SysSourceSetMultiAutoSearchTarget(EnumDisplayRegion enumDisplayRegion)
{
#if(_MULTI_DISPLAY_MAX == 0x01)

    if(enumDisplayRegion == _DISPLAY_RGN_NONE)
    {
        // Set fixed port scan type
        SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

        // Save system data
        if(GET_SOURCE_SCAN_TYPE() != UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE))
        {
            UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, GET_SOURCE_SCAN_TYPE());
            UserCommonNVRamSaveSystemData();
        }
    }
    else
    {
        // Set auto search scan type
        SET_SOURCE_AUTO_TARGET(_REGION_INDEX_0);
        SysSourceSetScanType(_SOURCE_SWITCH_AUTO_IN_GROUP);

        // Save system data
        if((GET_SOURCE_AUTO_TARGET() != UserCommonNVRamGetSystemData(_AUTO_SEARCH_TARGET)) ||
           (GET_SOURCE_SCAN_TYPE() != UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE)))
        {
            UserCommonNVRamSetSystemData(_AUTO_SEARCH_TARGET, GET_SOURCE_AUTO_TARGET());
            UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, GET_SOURCE_SCAN_TYPE());
            UserCommonNVRamSaveSystemData();
        }

        // Reset search times
        SysSourceSearchTimeReset();
    }

#else

    BYTE ucAutoTargetIndex = ScalerRegionGetIndex(enumDisplayRegion);

    if((enumDisplayRegion == _DISPLAY_RGN_NONE) ||
       (ucAutoTargetIndex > GET_RGN_MAX_DISPLAY_REGION()))
    {
        // Set fixed port scan type
        SysSourceSetScanType(_SOURCE_SWITCH_FIXED_PORT);

        // Save system data
        if(GET_SOURCE_SCAN_TYPE() != UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE))
        {
            UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, GET_SOURCE_SCAN_TYPE());
            UserCommonNVRamSaveSystemData();
        }
    }
    else
    {
        // Set auto search scan type
        SET_SOURCE_AUTO_TARGET(ucAutoTargetIndex);
        SysSourceSetScanType(_SOURCE_SWITCH_AUTO_IN_GROUP);

        // Save system data
        if((GET_SOURCE_AUTO_TARGET() != UserCommonNVRamGetSystemData(_AUTO_SEARCH_TARGET)) ||
           (GET_SOURCE_SCAN_TYPE() != UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE)))
        {
            UserCommonNVRamSetSystemData(_AUTO_SEARCH_TARGET, GET_SOURCE_AUTO_TARGET());
            UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, GET_SOURCE_SCAN_TYPE());
            UserCommonNVRamSaveSystemData();
        }

        // Reset search times
        SysSourceSearchTimeReset();
    }

#endif
}

//--------------------------------------------------
// Description  : Source Switch Between Interfaces
// Input Value  : Current Input Port, Target Source Type, Source Search Mode
// Output Value : None
//--------------------------------------------------
void SysSourceInterfaceSwitch(BYTE ucInputPort, BYTE ucPortType, BYTE ucSourceSearchDelayMode)
{
    struct StructPortSwitchedStatus
    {
        BYTE b1A0 : 1;
        BYTE b1D0 : 1;
        BYTE b1D1 : 1;
        BYTE b1D2 : 1;
        BYTE b1D3 : 1;
        BYTE b1D4 : 1;
        BYTE b1D5 : 1;
        BYTE b1D6 : 1;
    } stPortSwitchedStatus = {0};

    struct StructDpSwitchedStatus
    {
        BYTE b1D0Dp : 1;
        BYTE b1D1Dp : 1;
        BYTE b1D6Dp : 1;
    } stDpSwitchedStatus = {0};

    BYTE ucIndex = 0;

    ucSourceSearchDelayMode = ucSourceSearchDelayMode;

    for(ucIndex = 0; ucIndex < GET_RGN_MAX_DISPLAY_REGION(); ucIndex++)
    {
        // Get Multi P Every Port type
        if(ucInputPort != GET_RGN_INPUT_PORT(ucIndex))
        {
            switch(GET_RGN_INPUT_PORT(ucIndex))
            {
                case _A0_INPUT_PORT:

                    if(stPortSwitchedStatus.b1A0 == _FALSE)
                    {
                        stPortSwitchedStatus.b1A0 = _TRUE;
                    }

                    break;

                case _D0_INPUT_PORT:

                    if(stPortSwitchedStatus.b1D0 == _FALSE)
                    {
                        stPortSwitchedStatus.b1D0 = _TRUE;

                        if(GET_PORT_TYPE(GET_INPUTPORT_TYPE(GET_RGN_SOURCE_INDEX(ucIndex))) == _PORT_DP)
                        {
                            stDpSwitchedStatus.b1D0Dp = _TRUE;
                        }
                    }

                    break;

                case _D1_INPUT_PORT:

                    if(stPortSwitchedStatus.b1D1 == _FALSE)
                    {
                        stPortSwitchedStatus.b1D1 = _TRUE;

                        if(GET_PORT_TYPE(GET_INPUTPORT_TYPE(GET_RGN_SOURCE_INDEX(ucIndex))) == _PORT_DP)
                        {
                            stDpSwitchedStatus.b1D1Dp = _TRUE;
                        }
                    }

                    break;

                case _D2_INPUT_PORT:

                    if(GET_PORT_TYPE(GET_INPUTPORT_TYPE(GET_RGN_SOURCE_INDEX(ucIndex))) == _PORT_DUAL_DVI)
                    {
                        if(stPortSwitchedStatus.b1D3 == _FALSE)
                        {
                            stPortSwitchedStatus.b1D3 = _TRUE;
                        }
                    }

                    if(stPortSwitchedStatus.b1D2 == _FALSE)
                    {
                        stPortSwitchedStatus.b1D2 = _TRUE;
                    }

                    break;

                case _D3_INPUT_PORT:

                    if(GET_PORT_TYPE(GET_INPUTPORT_TYPE(GET_RGN_SOURCE_INDEX(ucIndex))) == _PORT_DUAL_DVI)
                    {
                        if(stPortSwitchedStatus.b1D4 == _FALSE)
                        {
                            stPortSwitchedStatus.b1D4 = _TRUE;
                        }
                    }

                    if(stPortSwitchedStatus.b1D3 == _FALSE)
                    {
                        stPortSwitchedStatus.b1D3 = _TRUE;
                    }

                    break;

                case _D4_INPUT_PORT:

                    if(GET_PORT_TYPE(GET_INPUTPORT_TYPE(GET_RGN_SOURCE_INDEX(ucIndex))) == _PORT_DUAL_DVI)
                    {
                        if(stPortSwitchedStatus.b1D5 == _FALSE)
                        {
                            stPortSwitchedStatus.b1D5 = _TRUE;
                        }
                    }

                    if(stPortSwitchedStatus.b1D4 == _FALSE)
                    {
                        stPortSwitchedStatus.b1D4 = _TRUE;
                    }

                    break;

                case _D5_INPUT_PORT:

                    if(stPortSwitchedStatus.b1D5 == _FALSE)
                    {
                        stPortSwitchedStatus.b1D5 = _TRUE;
                    }

                    break;

                case _D6_INPUT_PORT:

                    if(stPortSwitchedStatus.b1D6 == _FALSE)
                    {
                        stPortSwitchedStatus.b1D6 = _TRUE;

                        if(GET_PORT_TYPE(GET_INPUTPORT_TYPE(GET_RGN_SOURCE_INDEX(ucIndex))) == _PORT_DP)
                        {
                            stDpSwitchedStatus.b1D6Dp = _TRUE;
                        }
                    }

                    break;

                case _D7_INPUT_PORT:

                    if((stPortSwitchedStatus.b1D0 == _FALSE) || (stPortSwitchedStatus.b1D1 == _FALSE))
                    {
                        stPortSwitchedStatus.b1D0 = _TRUE;
                        stPortSwitchedStatus.b1D1 = _TRUE;

                        if(GET_PORT_TYPE(GET_INPUTPORT_TYPE(GET_RGN_SOURCE_INDEX(ucIndex))) == _PORT_DP)
                        {
                            stDpSwitchedStatus.b1D0Dp = _TRUE;
                            stDpSwitchedStatus.b1D1Dp = _TRUE;
                        }
                    }

                    break;

                default:
                    break;
            }
        }
    }

    if((ucInputPort != _A0_INPUT_PORT) && (stPortSwitchedStatus.b1A0 == _FALSE))
    {
        ScalerSyncAdcApllPowerDown();
    }

    if((ucPortType != _PORT_DVI) && (ucPortType != _PORT_HDMI) &&
       (ucPortType != _PORT_MHL) && (ucPortType != _PORT_DUAL_DVI))
    {
#if(_D0_TMDS_SUPPORT == _ON)
        if(stPortSwitchedStatus.b1D0 == _FALSE)
        {
            ScalerTMDSRx0FreqDetectDisable();
        }
#endif

#if(_D1_TMDS_SUPPORT == _ON)
        if(stPortSwitchedStatus.b1D1 == _FALSE)
        {
            ScalerTMDSRx1FreqDetectDisable();
        }
#endif

#if(_D2_TMDS_SUPPORT == _ON)
        if(stPortSwitchedStatus.b1D2 == _FALSE)
        {
            ScalerTMDSRx2FreqDetectDisable();
        }
#endif

#if(_D3_TMDS_SUPPORT == _ON)
        if(stPortSwitchedStatus.b1D3 == _FALSE)
        {
            ScalerTMDSRx3FreqDetectDisable();
        }
#endif

#if(_D4_TMDS_SUPPORT == _ON)
        if(stPortSwitchedStatus.b1D4 == _FALSE)
        {
            ScalerTMDSRx4FreqDetectDisable();
        }
#endif

#if(_D5_TMDS_SUPPORT == _ON)
        if(stPortSwitchedStatus.b1D5 == _FALSE)
        {
            ScalerTMDSRx5FreqDetectDisable();
        }
#endif
    }

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
    if(((ucInputPort != _D0_INPUT_PORT) && (stDpSwitchedStatus.b1D0Dp == _FALSE)) &&
       ((ucInputPort != _D6_INPUT_PORT) && (stDpSwitchedStatus.b1D6Dp == _FALSE)))
#else
    if((ucInputPort != _D0_INPUT_PORT) && (stDpSwitchedStatus.b1D0Dp == _FALSE))
#endif
    {
        ScalerDpRx0InterfaceInitial();
    }
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

    if((ucInputPort != _D1_INPUT_PORT) && (stDpSwitchedStatus.b1D1Dp == _FALSE))
    {
        ScalerDpRx1InterfaceInitial();
    }
#endif

    switch(ucInputPort)
    {
        case _A0_INPUT_PORT:

            if(ucSourceSearchDelayMode != _SOURCE_SEARCH_POLLING_MODE)
            {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)

#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                if((stPortSwitchedStatus.b1D0 == _FALSE) && (stPortSwitchedStatus.b1D6 == _FALSE))
#else
                if(stPortSwitchedStatus.b1D0 == _FALSE)
#endif
                {
                    ScalerSyncInterfaceRx0Proc(_DISABLE);
                }
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
                if(stPortSwitchedStatus.b1D1 == _FALSE)
                {
                    ScalerSyncInterfaceRx1Proc(_DISABLE);
                }
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
                if(stPortSwitchedStatus.b1D2 == _FALSE)
                {
                    ScalerSyncInterfaceRx2Proc(_DISABLE);
                }
#endif

#if((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
                if(stPortSwitchedStatus.b1D3 == _FALSE)
                {
                    ScalerSyncInterfaceRx3Proc(_DISABLE);
                }
#endif

#if((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
                if(stPortSwitchedStatus.b1D4 == _FALSE)
                {
                    ScalerSyncInterfaceRx4Proc(_DISABLE);
                }
#endif

#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
                if(stPortSwitchedStatus.b1D5 == _FALSE)
                {
                    ScalerSyncInterfaceRx5Proc(_DISABLE);
                }
#endif
            }

            break;

        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
            ScalerSyncInterfaceRx0Proc(_ENABLE);
#endif

            if(ucSourceSearchDelayMode != _SOURCE_SEARCH_POLLING_MODE)
            {
#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
                if(stPortSwitchedStatus.b1D1 == _FALSE)
                {
                    ScalerSyncInterfaceRx1Proc(_DISABLE);
                }
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
                if(stPortSwitchedStatus.b1D2 == _FALSE)
                {
                    ScalerSyncInterfaceRx2Proc(_DISABLE);
                }
#endif

#if((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
                if(stPortSwitchedStatus.b1D3 == _FALSE)
                {
                    ScalerSyncInterfaceRx3Proc(_DISABLE);
                }
#endif

#if((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
                if(stPortSwitchedStatus.b1D4 == _FALSE)
                {
                    ScalerSyncInterfaceRx4Proc(_DISABLE);
                }
#endif

#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
                if(stPortSwitchedStatus.b1D5 == _FALSE)
                {
                    ScalerSyncInterfaceRx5Proc(_DISABLE);
                }
#endif
            }

            break;

        case _D1_INPUT_PORT:

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
            ScalerSyncInterfaceRx1Proc(_ENABLE);
#endif

            if(ucSourceSearchDelayMode != _SOURCE_SEARCH_POLLING_MODE)
            {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)

#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                if((stPortSwitchedStatus.b1D0 == _FALSE) && (stPortSwitchedStatus.b1D6 == _FALSE))
#else
                if(stPortSwitchedStatus.b1D0 == _FALSE)
#endif
                {
                    ScalerSyncInterfaceRx0Proc(_DISABLE);
                }
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
                if(stPortSwitchedStatus.b1D2 == _FALSE)
                {
                    ScalerSyncInterfaceRx2Proc(_DISABLE);
                }
#endif

#if((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
                if(stPortSwitchedStatus.b1D3 == _FALSE)
                {
                    ScalerSyncInterfaceRx3Proc(_DISABLE);
                }
#endif

#if((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
                if(stPortSwitchedStatus.b1D4 == _FALSE)
                {
                    ScalerSyncInterfaceRx4Proc(_DISABLE);
                }
#endif

#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
                if(stPortSwitchedStatus.b1D5 == _FALSE)
                {
                    ScalerSyncInterfaceRx5Proc(_DISABLE);
                }
#endif
            }

            break;

        case _D2_INPUT_PORT:

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
            ScalerSyncInterfaceRx2Proc(_ENABLE);
#if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)
            ScalerSyncInterfaceRx3Proc(_ENABLE);
#endif

#endif

            if(ucSourceSearchDelayMode != _SOURCE_SEARCH_POLLING_MODE)
            {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)

#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                if((stPortSwitchedStatus.b1D0 == _FALSE) && (stPortSwitchedStatus.b1D6 == _FALSE))
#else
                if(stPortSwitchedStatus.b1D0 == _FALSE)
#endif
                {
                    ScalerSyncInterfaceRx0Proc(_DISABLE);
                }
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
                if(stPortSwitchedStatus.b1D1 == _FALSE)
                {
                    ScalerSyncInterfaceRx1Proc(_DISABLE);
                }
#endif

#if((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) && (_D2_INPUT_PORT_TYPE != _D2_DUAL_DVI_PORT))
                if(stPortSwitchedStatus.b1D3 == _FALSE)
                {
                    ScalerSyncInterfaceRx3Proc(_DISABLE);
                }
#endif

#if((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
                if(stPortSwitchedStatus.b1D4 == _FALSE)
                {
                    ScalerSyncInterfaceRx4Proc(_DISABLE);
                }
#endif

#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
                if(stPortSwitchedStatus.b1D5 == _FALSE)
                {
                    ScalerSyncInterfaceRx5Proc(_DISABLE);
                }
#endif
            }

            break;

        case _D3_INPUT_PORT:

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
            ScalerSyncInterfaceRx3Proc(_ENABLE);
#if(_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT)
            ScalerSyncInterfaceRx4Proc(_ENABLE);
#endif

#endif

            if(ucSourceSearchDelayMode != _SOURCE_SEARCH_POLLING_MODE)
            {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)

#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                if((stPortSwitchedStatus.b1D0 == _FALSE) && (stPortSwitchedStatus.b1D6 == _FALSE))
#else
                if(stPortSwitchedStatus.b1D0 == _FALSE)
#endif
                {
                    ScalerSyncInterfaceRx0Proc(_DISABLE);
                }
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
                if(stPortSwitchedStatus.b1D1 == _FALSE)
                {
                    ScalerSyncInterfaceRx1Proc(_DISABLE);
                }
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
                if(stPortSwitchedStatus.b1D2 == _FALSE)
                {
                    ScalerSyncInterfaceRx2Proc(_DISABLE);
                }
#endif

#if((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) && (_D3_INPUT_PORT_TYPE != _D3_DUAL_DVI_PORT))
                if(stPortSwitchedStatus.b1D4 == _FALSE)
                {
                    ScalerSyncInterfaceRx4Proc(_DISABLE);
                }
#endif

#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
                if(stPortSwitchedStatus.b1D5 == _FALSE)
                {
                    ScalerSyncInterfaceRx5Proc(_DISABLE);
                }
#endif
            }

            break;

        case _D4_INPUT_PORT:

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
            ScalerSyncInterfaceRx4Proc(_ENABLE);
#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
            ScalerSyncInterfaceRx5Proc(_ENABLE);
#endif
#endif

            if(ucSourceSearchDelayMode != _SOURCE_SEARCH_POLLING_MODE)
            {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)

#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                if((stPortSwitchedStatus.b1D0 == _FALSE) && (stPortSwitchedStatus.b1D6 == _FALSE))
#else
                if(stPortSwitchedStatus.b1D0 == _FALSE)
#endif
                {
                    ScalerSyncInterfaceRx0Proc(_DISABLE);
                }
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
                if(stPortSwitchedStatus.b1D1 == _FALSE)
                {
                    ScalerSyncInterfaceRx1Proc(_DISABLE);
                }
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
                if(stPortSwitchedStatus.b1D2 == _FALSE)
                {
                    ScalerSyncInterfaceRx2Proc(_DISABLE);
                }
#endif

#if((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
                if(stPortSwitchedStatus.b1D3 == _FALSE)
                {
                    ScalerSyncInterfaceRx3Proc(_DISABLE);
                }
#endif

#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) && (_D4_INPUT_PORT_TYPE != _D4_DUAL_DVI_PORT))
                if(stPortSwitchedStatus.b1D5 == _FALSE)
                {
                    ScalerSyncInterfaceRx5Proc(_DISABLE);
                }
#endif
            }

            break;

        case _D5_INPUT_PORT:

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
            ScalerSyncInterfaceRx5Proc(_ENABLE);
#endif

            if(ucSourceSearchDelayMode != _SOURCE_SEARCH_POLLING_MODE)
            {
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)

#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                if((stPortSwitchedStatus.b1D0 == _FALSE) && (stPortSwitchedStatus.b1D6 == _FALSE))
#else
                if(stPortSwitchedStatus.b1D0 == _FALSE)
#endif
                {
                    ScalerSyncInterfaceRx0Proc(_DISABLE);
                }
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
                if(stPortSwitchedStatus.b1D1 == _FALSE)
                {
                    ScalerSyncInterfaceRx1Proc(_DISABLE);
                }
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
                if(stPortSwitchedStatus.b1D2 == _FALSE)
                {
                    ScalerSyncInterfaceRx2Proc(_DISABLE);
                }
#endif

#if((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
                if(stPortSwitchedStatus.b1D3 == _FALSE)
                {
                    ScalerSyncInterfaceRx3Proc(_DISABLE);
                }
#endif

#if((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
                if(stPortSwitchedStatus.b1D4 == _FALSE)
                {
                    ScalerSyncInterfaceRx4Proc(_DISABLE);
                }
#endif
            }

            break;

        case _D7_INPUT_PORT:

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
            ScalerSyncInterfaceRx0Proc(_ENABLE);
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
            ScalerSyncInterfaceRx1Proc(_ENABLE);
#endif

            if(ucSourceSearchDelayMode != _SOURCE_SEARCH_POLLING_MODE)
            {
#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
                if(stPortSwitchedStatus.b1D2 == _FALSE)
                {
                    ScalerSyncInterfaceRx2Proc(_DISABLE);
                }
#endif

#if((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
                if(stPortSwitchedStatus.b1D3 == _FALSE)
                {
                    ScalerSyncInterfaceRx3Proc(_DISABLE);
                }
#endif

#if((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
                if(stPortSwitchedStatus.b1D4 == _FALSE)
                {
                    ScalerSyncInterfaceRx4Proc(_DISABLE);
                }
#endif

#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
                if(stPortSwitchedStatus.b1D5 == _FALSE)
                {
                    ScalerSyncInterfaceRx5Proc(_DISABLE);
                }
#endif
            }

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Update measure target & perform measure process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceMeasureProc(void)
{
    // Update measure target
    if(SysSourceUpdateMeasureTarget() == _TRUE)
    {
        DebugMessageSystem("Measure Target", GET_SOURCE_MEASURE_TARGET_INDEX());

        // Set measure region index
        ScalerMeasureSetIndex(GET_SOURCE_MEASURE_TARGET_INDEX());
        ScalerMeasureSetInputPath(ScalerRegionGetInputDataPath(GET_RGN_DISPLAY_REGION(GET_SOURCE_MEASURE_TARGET_INDEX())));

        // Clear timing double check flag
        CLR_RGN_TIMING_DOUBLE_CHECK(GET_SOURCE_MEASURE_TARGET_INDEX());

#if(_MULTI_DISPLAY_MAX != 0x01)
        // Check duplicate port in 2P/4P mode
        if(SysSourceDuplicateInputTiming() == _FALSE)
#endif
        {
            // Measure input timing
            SysSourceMeasureInputTiming();
        }
    }
}

//--------------------------------------------------
// Description  : Search for measure target
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit SysSourceUpdateMeasureTarget(void)
{
    // Check measure target validity
    if(GET_SOURCE_MEASURE_TARGET_INDEX() >= GET_RGN_MAX_DISPLAY_REGION())
    {
        // Reset measure target related events & flags
        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_NOSIGNAL_STATE);
        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_NOSUPPORT_STATE);
        CLR_RGN_TIMING_CONFIRM(GET_SOURCE_MEASURE_TARGET_INDEX());
        CLR_RGN_TIMING_DOUBLE_CHECK(GET_SOURCE_MEASURE_TARGET_INDEX());
        CLR_RGN_MEASURE_CHECKING(GET_SOURCE_MEASURE_TARGET_INDEX());

        // Reset measure target to 0
        SET_SOURCE_MEASURE_TARGET_INDEX(0);
    }

#if(_MULTI_DISPLAY_MAX != 0x01)
    if(GET_MODE_DISPLAY_MODE() != _DISPLAY_MODE_1P)
    {
        // Skip updating measure target index when checking OOR
        if(GET_RGN_MEASURE_CHECKING(GET_SOURCE_MEASURE_TARGET_INDEX()) == _FALSE)
        {
            // Skip when current target is feasible
            if((GET_RGN_SOURCE_JUDGE(GET_SOURCE_MEASURE_TARGET_INDEX()) == _FALSE) ||
               (GET_RGN_TIMING_CONFIRM(GET_SOURCE_MEASURE_TARGET_INDEX()) == _TRUE))
            {
                BYTE ucRegionIndex = 0x00;

                // Search for new measure target
                do
                {
                    if((GET_RGN_SOURCE_JUDGE(ucRegionIndex) == _TRUE) &&
                       (GET_RGN_TIMING_CONFIRM(ucRegionIndex) == _FALSE))
                    {
                        SET_SOURCE_MEASURE_TARGET_INDEX(ucRegionIndex);

                        DebugMessageSystem("New measure target", GET_SOURCE_MEASURE_TARGET_INDEX());
                        return _TRUE;
                    }
                }while(++ucRegionIndex < GET_RGN_MAX_DISPLAY_REGION());

                // Search failed; Reset measure target to 0
                SET_SOURCE_MEASURE_TARGET_INDEX(0);
                return _FALSE;
            }
        }
    }
#endif // End of #if(_MULTI_DISPLAY_MAX != 0x01)

    return ((GET_RGN_SOURCE_JUDGE(GET_SOURCE_MEASURE_TARGET_INDEX()) == _TRUE) &&
            (GET_RGN_TIMING_CONFIRM(GET_SOURCE_MEASURE_TARGET_INDEX()) == _FALSE));
}

//--------------------------------------------------
// Description  : Measure input timing
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysSourceMeasureInputTiming(void)
{
    // Measure Current Input Timing to gather all required timing Info
    if(ScalerMeasureInputInfo(GET_RGN_SOURCE_TYPE(GET_SOURCE_MEASURE_TARGET_INDEX()), GET_RGN_INPUT_PORT(GET_SOURCE_MEASURE_TARGET_INDEX())) == _TRUE)
    {
        ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_NOSIGNAL_STATE);

        DebugMessageSystem("Input Timing HP", GET_INPUT_TIMING_H_POLARITY());
        DebugMessageSystem("Input Timing VP", GET_INPUT_TIMING_V_POLARITY());
        DebugMessageSystem("Input Timing InterLace", GET_INPUT_TIMING_INTERLACE_FLG());
        DebugMessageSystem("Input Timing HFreq", GET_INPUT_TIMING_HFREQ());
        DebugMessageSystem("Input Timing HTotal", GET_INPUT_TIMING_HTOTAL());
        DebugMessageSystem("Input Timing HStart", GET_INPUT_TIMING_HSTART());
        DebugMessageSystem("Input Timing HWidth", GET_INPUT_TIMING_HWIDTH());
        DebugMessageSystem("Input Timing HSW", GET_INPUT_TIMING_HSYNCWIDTH());
        DebugMessageSystem("Input Timing VFreq", GET_INPUT_TIMING_VFREQ());
        DebugMessageSystem("Input Timing VTotal", GET_INPUT_TIMING_VTOTAL());
        DebugMessageSystem("Input Timing VStart", GET_INPUT_TIMING_VSTART());
        DebugMessageSystem("Input Timing VHeight", GET_INPUT_TIMING_VHEIGHT());
        DebugMessageSystem("Input Timing VSW", GET_INPUT_TIMING_VSYNCWIDTH());

        // Set timing confirmed flag
        SET_RGN_TIMING_CONFIRM(GET_SOURCE_MEASURE_TARGET_INDEX());
        SET_RGN_TIMING_DOUBLE_CHECK(GET_SOURCE_MEASURE_TARGET_INDEX());

        // Perform I-domain OOR check here
        if(UserCommonInterfaceCheckNoSupport(GET_RGN_DISPLAY_REGION(GET_SOURCE_MEASURE_TARGET_INDEX())) == _TRUE)
        {
            // Set measure checking flag
            SET_RGN_MEASURE_CHECKING(GET_SOURCE_MEASURE_TARGET_INDEX());

            // Wait until really into source OOR state
            ScalerTimerActiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_SOURCE_NOSUPPORT_STATE);
        }
        else
        {
            ScalerTimerCancelTimerEvent(_SYSTEM_TIMER_EVENT_SOURCE_NOSUPPORT_STATE);
        }
    }
    else
    {
        DebugMessageSystem("Digital Measure Fail", GET_SOURCE_MEASURE_TARGET_INDEX());

        // If Timing can't be confirmed for 1 sec, clear source judged flag
        ScalerTimerActiveTimerEvent(SEC(1), _SYSTEM_TIMER_EVENT_SOURCE_NOSIGNAL_STATE);
    }
}

#if(_MULTI_DISPLAY_MAX != 0x01)
//--------------------------------------------------
// Description  : Duplicate input timing
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit SysSourceDuplicateInputTiming(void)
{
    BYTE ucDuplicateIndex = 0;

    // Search duplicate port
    for(ucDuplicateIndex = 0; ucDuplicateIndex < GET_RGN_MAX_DISPLAY_REGION(); ++ucDuplicateIndex)
    {
        if((GET_RGN_INPUT_PORT(ucDuplicateIndex) == GET_RGN_INPUT_PORT(GET_SOURCE_MEASURE_TARGET_INDEX())) &&
           (GET_RGN_TIMING_CONFIRM(ucDuplicateIndex) == _TRUE))
        {
            // Duplicate timing info
            if(ScalerMeasureDuplicateInputInfo(ucDuplicateIndex) == _TRUE)
            {
                SET_RGN_TIMING_CONFIRM(GET_SOURCE_MEASURE_TARGET_INDEX());
                SET_RGN_TIMING_DOUBLE_CHECK(GET_SOURCE_MEASURE_TARGET_INDEX());

                DebugMessageSystem("Timing info duplicated", GET_SOURCE_MEASURE_TARGET_INDEX());

                // Perform I-domain OOR check here
                if(UserCommonInterfaceCheckNoSupport(GET_RGN_DISPLAY_REGION(GET_SOURCE_MEASURE_TARGET_INDEX())) == _TRUE)
                {
                    SET_RGN_DISPLAY_ACTION(GET_SOURCE_MEASURE_TARGET_INDEX(), _DISPLAY_ACTION_OOR);
                }
            }
            else
            {
                DebugMessageSystem("Duplicate Fail", GET_SOURCE_MEASURE_TARGET_INDEX());
            }

            return _TRUE;
        }
    }

    return _FALSE;
}
#endif // End of #if(_MULTI_DISPLAY_MAX != 0x01)
