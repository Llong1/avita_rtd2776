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
// ID Code      : RL6193_Series_TMDS.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

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

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_HDMI_SUPPORT == _ON)

#if(_HDMI_2_0_SUPPORT == _ON)
void ScalerTMDSHdmiReadRequestTimerEnable_WDINT(void);
void ScalerTMDSHdmi2FormatResetEvent(EnumScalerTimerEventID enumEventID);
#endif

bit ScalerTMDSYUV420SupportCheck(BYTE ucInputPort);

#if(_HDMI_FREESYNC_SUPPORT == _ON)
void ScalerTMDSFreesyncInitial(bit bSupport);
BYTE ScalerTMDSHdmiGetAmdSpdInfo(EnumAmdSpdInfoContent enumContent, EnumSourceSearchPort enumSearchPort);
#endif
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_HDMI_SUPPORT == _ON)

#if(_HDMI_2_0_SUPPORT == _ON)
//--------------------------------------------------
// Description  : TMDS Read Request Timer Event Enable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSHdmiReadRequestTimerEnable_WDINT(void) using 3
{
#if(_D0_HDMI_2_0_SUPPORT == _ON)
    if(GET_HDMI_2_0_RX0_RR_ENABLE() == _TRUE)
    {
        // FW Manual Enable Read Request
        ScalerSetBit_EXINT(P2_1B_HDMI_CTRL_1B, ~_BIT7, _BIT7);
    }
#endif

#if(_D1_HDMI_2_0_SUPPORT == _ON)
    if(GET_HDMI_2_0_RX1_RR_ENABLE() == _TRUE)
    {
        // FW Manual Enable Read Request
        ScalerSetBit_EXINT(P70_1B_HDMI_CTRL_1B, ~_BIT7, _BIT7);
    }
#endif
}

//--------------------------------------------------
// Description  : TMDS Format Reset Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSHdmi2FormatResetEvent(EnumScalerTimerEventID enumEventID)
{
    switch(enumEventID)
    {
#if(_D0_HDMI_2_0_SUPPORT == _ON)

        case _SCALER_TIMER_EVENT_RX0_HDMI2_FORMAT_RESET_WAIT:

            CLR_TMDS_RX0_HDMI_2_0_FORMAT_RESET_WAITING();

            break;
#endif

#if(_D1_HDMI_2_0_SUPPORT == _ON)

        case _SCALER_TIMER_EVENT_RX1_HDMI2_FORMAT_RESET_WAIT:

            CLR_TMDS_RX1_HDMI_2_0_FORMAT_RESET_WAITING();

            break;
#endif
        default:
            break;
    }
}
#endif // End of #if(_HDMI_2_0_SUPPORT == _ON)

//--------------------------------------------------
// Description  : TMDS 420 Color Space Support Check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerTMDSYUV420SupportCheck(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_TMDS_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            // Check YCbCr 420 format; only support 8 bit
            if((ScalerColorGetColorSpace(_D0_INPUT_PORT) == _COLOR_SPACE_YCBCR420) &&
               (ScalerColorGetColorDepth(_D0_INPUT_PORT) > _COLOR_DEPTH_8_BITS))
            {
                return _FALSE;
            }

            break;
#endif

#if(_D1_TMDS_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            // Check YCbCr 420 format; only support 8 bit
            if((ScalerColorGetColorSpace(_D1_INPUT_PORT) == _COLOR_SPACE_YCBCR420) &&
               (ScalerColorGetColorDepth(_D1_INPUT_PORT) > _COLOR_DEPTH_8_BITS))
            {
                return _FALSE;
            }

            break;
#endif

#if(_D2_TMDS_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            if(ScalerColorGetColorSpace(_D2_INPUT_PORT) == _COLOR_SPACE_YCBCR420)
            {
                return _FALSE;
            }

            break;
#endif

#if(_D3_TMDS_SUPPORT == _ON)
        case _D3_INPUT_PORT:

            if(ScalerColorGetColorSpace(_D3_INPUT_PORT) == _COLOR_SPACE_YCBCR420)
            {
                return _FALSE;
            }

            break;
#endif

#if(_D4_TMDS_SUPPORT == _ON)
        case _D4_INPUT_PORT:

            if(ScalerColorGetColorSpace(_D4_INPUT_PORT) == _COLOR_SPACE_YCBCR420)
            {
                return _FALSE;
            }

            break;
#endif

#if(_D5_TMDS_SUPPORT == _ON)
        case _D5_INPUT_PORT:

            if(ScalerColorGetColorSpace(_D5_INPUT_PORT) == _COLOR_SPACE_YCBCR420)
            {
                return _FALSE;
            }

            break;
#endif
        default:
            break;
    }

    return _TRUE;
}

#if(_HDMI_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDMI freesync initial
// Input Value  : support or not
// Output Value :
//--------------------------------------------------
void ScalerTMDSFreesyncInitial(bit bSupport)
{
    SET_FREESYNC_SUPPORT(bSupport);

#if(_D0_HDMI_SUPPORT == _ON)
    SET_TMDS_RX0_FREESYNC_SUPPORT(bSupport);
#endif

#if(_D1_HDMI_SUPPORT == _ON)
    SET_TMDS_RX1_FREESYNC_SUPPORT(bSupport);
#endif

#if(_D2_HDMI_SUPPORT == _ON)
    SET_TMDS_RX2_FREESYNC_SUPPORT(bSupport);
#endif

#if(_D3_HDMI_SUPPORT == _ON)
    SET_TMDS_RX3_FREESYNC_SUPPORT(bSupport);
#endif

#if(_D4_HDMI_SUPPORT == _ON)
    SET_TMDS_RX4_FREESYNC_SUPPORT(bSupport);
#endif

#if(_D5_HDMI_SUPPORT == _ON)
    SET_TMDS_RX5_FREESYNC_SUPPORT(bSupport);
#endif
}

//--------------------------------------------------
// Description  : Dp Get AMD SPD info
// Input Value  : None
// Output Value :
//--------------------------------------------------
BYTE ScalerTMDSHdmiGetAmdSpdInfo(EnumAmdSpdInfoContent enumContent, EnumSourceSearchPort enumSearchPort)
{
    switch(enumSearchPort)
    {
#if(_D0_HDMI_SUPPORT == _ON)
        case _D0_INPUT_PORT:

            return ScalerTMDSRx0HdmiGetAmdSpdInfo(enumContent);
#endif

#if(_D1_HDMI_SUPPORT == _ON)
        case _D1_INPUT_PORT:

            return ScalerTMDSRx1HdmiGetAmdSpdInfo(enumContent);
#endif

#if(_D2_HDMI_SUPPORT == _ON)
        case _D2_INPUT_PORT:

            return ScalerTMDSRx2HdmiGetAmdSpdInfo(enumContent);
#endif

#if(_D3_HDMI_SUPPORT == _ON)
        case _D3_INPUT_PORT:

            return ScalerTMDSRx3HdmiGetAmdSpdInfo(enumContent);
#endif

#if(_D4_HDMI_SUPPORT == _ON)
        case _D4_INPUT_PORT:

            return ScalerTMDSRx4HdmiGetAmdSpdInfo(enumContent);
#endif

#if(_D5_HDMI_SUPPORT == _ON)
        case _D5_INPUT_PORT:

            return ScalerTMDSRx5HdmiGetAmdSpdInfo(enumContent);
#endif

        default:

            return 0;
    }
}
#endif // #if(_HDMI_FREESYNC_SUPPORT == _ON)

#endif
