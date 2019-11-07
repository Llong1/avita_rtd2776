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
// ID Code      : ScalerDP.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DP__

#include "ScalerFunctionInclude.h"

#if(_DP_SUPPORT == _ON)

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
void ScalerDpEdidSwitch(BYTE ucInputPort);
void ScalerDpVersionSwitch(BYTE ucInputPort, EnumDpVersionType enumDpVersion, EnumDPMSTPort enumDpRxMstPort);
EnumDpPowerState ScalerDpGetPowerStatus(BYTE ucInputPort);
EnumDpLaneCount ScalerDpGetLaneCount(BYTE ucInputPort);
EnumDpLinkRate ScalerDpGetLinkRate(BYTE ucInputPort);
EnumDpVoltageSwingLevel ScalerDpGetLaneVoltageSwingLv(BYTE ucInputPort, EnumDpLane enumDpLane);
EnumDpPreEmphasisLevel ScalerDpGetLanePreEmpLv(BYTE ucInputPort, EnumDpLane enumDpLane);
bit ScalerDpGetSrcMstEnable(BYTE ucInputPort);
void ScalerDpLaneCountSwitch(BYTE ucInputPort, EnumDpLaneCount enumDpLaneCount);
void ScalerDpSetDpLaneMapping(BYTE ucInputPort, BYTE ucLanetype);

#if(_DP_FREESYNC_SUPPORT == _ON)
BYTE ScalerDpGetAmdSpdInfo(EnumAmdSpdInfoContent enumContent, EnumSourceSearchPort enumSearchPort);
WORD ScalerDpGetHSPeriod(EnumInputDataPath enumInputDataPath);
WORD ScalerDpGetHSW(EnumInputDataPath enumInputDataPath);
WORD ScalerDpGetVFreq(EnumInputDataPath enumInputDataPath);
WORD ScalerDpGetVSPeriod(EnumInputDataPath enumInputDataPath);
#endif

#if(_DP_MST_SUPPORT == _ON)
void ScalerDpMstReset(EnumDPMSTPort enumRxMstPort);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : DP EDID Switch
// Input Value  : Input DP Port
// Output Value : None
//--------------------------------------------------
void ScalerDpEdidSwitch(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _D0_INPUT_PORT:
            SET_DP_RX_D0_EDID_SWITCH();
            SET_DP_RX_CAPABILITY_SWITCHED();
            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:
            SET_DP_RX_D1_EDID_SWITCH();
            SET_DP_RX_CAPABILITY_SWITCHED();
            break;
#endif

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
            SET_DP_RX_D6_EDID_SWITCH();
            SET_DP_RX_CAPABILITY_SWITCHED();
            break;
#endif

#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
        case _D7_INPUT_PORT:
            SET_DP_RX_D7_EDID_SWITCH();
            SET_DP_RX_CAPABILITY_SWITCHED();
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Dp Version Switch
// Input Value  : DP input port, _DP_VERSION_1_1 or _DP_VERSION_1_2
// Output Value : None
//--------------------------------------------------
void ScalerDpVersionSwitch(BYTE ucInputPort, EnumDpVersionType enumDpVersion, EnumDPMSTPort enumDpRxMstPort)
{
    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _D0_INPUT_PORT:
            SET_DP_RX_D0_PORT_TARGET_VERSION(enumDpVersion);
            SET_DP_RX_TARGET_MST_PORT(enumDpRxMstPort);
            SET_DP_RX_CAPABILITY_SWITCHED();
            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:
            SET_DP_RX_D1_PORT_TARGET_VERSION(enumDpVersion);
            SET_DP_RX_TARGET_MST_PORT(enumDpRxMstPort);
            SET_DP_RX_CAPABILITY_SWITCHED();
            break;
#endif

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
            SET_DP_RX_D6_PORT_TARGET_VERSION(enumDpVersion);
            SET_DP_RX_TARGET_MST_PORT(enumDpRxMstPort);
            SET_DP_RX_CAPABILITY_SWITCHED();
            break;
#endif

#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
        case _D7_INPUT_PORT:
            SET_DP_RX_D0_PORT_TARGET_VERSION(enumDpVersion);
            SET_DP_RX_D1_PORT_TARGET_VERSION(enumDpVersion);
            SET_DP_RX_TARGET_MST_PORT(enumDpRxMstPort);
            SET_DP_RX_CAPABILITY_SWITCHED();
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get DP Power Status (DPCD 00600h)
// Input Value  : DP Input Port
// Output Value : DP Power Status
//--------------------------------------------------
EnumDpPowerState ScalerDpGetPowerStatus(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

        case _D6_INPUT_PORT:
#endif
            if(ScalerDpRx0GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT1)
            {
                return _DP_POWER_DOWN;
            }
            else if(ScalerDpRx0GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))
            {
                return _DP_POWER_DOWN_WITH_AUX;
            }

            return _DP_POWER_NORMAL;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

        case _D1_INPUT_PORT:

            if(ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT1)
            {
                return _DP_POWER_DOWN;
            }
            else if(ScalerDpRx1GetDpcdBitInfo(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0))
            {
                return _DP_POWER_DOWN_WITH_AUX;
            }

            return _DP_POWER_NORMAL;
#endif

        default:

            return _DP_POWER_NORMAL;
    }
}

//--------------------------------------------------
// Description  : Get DP Lane Count (DPCD 00101h)
// Input Value  : DP Input Port
// Output Value : DP Lane Count
//--------------------------------------------------
EnumDpLaneCount ScalerDpGetLaneCount(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

        case _D6_INPUT_PORT:
#endif
            return (ScalerDpRx0GetDpcdBitInfo(0x00, 0x01, 0x01, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)));
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

        case _D1_INPUT_PORT:

            return (ScalerDpRx1GetDpcdBitInfo(0x00, 0x01, 0x01, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)));
#endif
        default:

            return _DP_LINK_4_LANE;
    }
}

//--------------------------------------------------
// Description  : Get DP Link Rate (DPCD 00100h)
// Input Value  : DP Input Port
// Output Value : DP Link Rate
//--------------------------------------------------
EnumDpLinkRate ScalerDpGetLinkRate(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

        case _D6_INPUT_PORT:
#endif
            return (ScalerDpRx0GetDpcdInfo(0x00, 0x01, 0x00));
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

        case _D1_INPUT_PORT:

            return (ScalerDpRx1GetDpcdInfo(0x00, 0x01, 0x00));
#endif
        default:

            return _DP_LINK_RBR;
    }
}

//--------------------------------------------------
// Description  : Get DP Voltage Swing Level(DPCD 00103h-00106h [1:0])
// Input Value  : DP Input Port, Lane #
// Output Value : DP Voltage Swing Level of the lane
//--------------------------------------------------
EnumDpVoltageSwingLevel ScalerDpGetLaneVoltageSwingLv(BYTE ucInputPort, EnumDpLane enumDpLane)
{
    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

        case _D6_INPUT_PORT:
#endif
            return (ScalerDpRx0GetDpcdBitInfo(0x00, 0x01, (0x03 + enumDpLane), (_BIT1 | _BIT0)));
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

        case _D1_INPUT_PORT:

            return (ScalerDpRx1GetDpcdBitInfo(0x00, 0x01, (0x03 + enumDpLane), (_BIT1 | _BIT0)));
#endif
        default:

            return 0;
    }
}

//--------------------------------------------------
// Description  : Get DP Pre-emphasis Level(DPCD 00103h-00106h [4:3])
// Input Value  : DP Input Port, Lane #
// Output Value : DP Pre-emphasis Level of the lane
//--------------------------------------------------
EnumDpPreEmphasisLevel ScalerDpGetLanePreEmpLv(BYTE ucInputPort, EnumDpLane enumDpLane)
{
    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

        case _D6_INPUT_PORT:
#endif
            return (ScalerDpRx0GetDpcdBitInfo(0x00, 0x01, (0x03 + enumDpLane), (_BIT4 | _BIT3)) >> 3);
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

        case _D1_INPUT_PORT:

            return (ScalerDpRx1GetDpcdBitInfo(0x00, 0x01, (0x03 + enumDpLane), (_BIT4 | _BIT3)) >> 3);
#endif
        default:

            return 0;
    }
}

//--------------------------------------------------
// Description  : Get DP Source MST enable (DPCD 00111h[0])
// Input Value  : DP Input Port
// Output Value : _TRUE --> MST enable, _FALSE --> SST
//--------------------------------------------------
bit ScalerDpGetSrcMstEnable(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

        case _D6_INPUT_PORT:
#endif
            if(ScalerDpRx0GetDpcdBitInfo(0x00, 0x01, 0x11, _BIT0) == _BIT0)
            {
                return _TRUE;
            }
            else
            {
                return _FALSE;
            }
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

        case _D1_INPUT_PORT:

            if(ScalerDpRx1GetDpcdBitInfo(0x00, 0x01, 0x11, _BIT0) == _BIT0)
            {
                return _TRUE;
            }
            else
            {
                return _FALSE;
            }
#endif
        default:

            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : DP Lane Switch
// Input Value  : DP input port, DP Lane Count
// Output Value : None
//--------------------------------------------------
void ScalerDpLaneCountSwitch(BYTE ucInputPort, EnumDpLaneCount enumDpLaneCount)
{
    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _D0_INPUT_PORT:
            SET_DP_RX_D0_PORT_TARGET_LANE_COUNT(enumDpLaneCount);
            SET_DP_RX_CAPABILITY_SWITCHED();
            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:
            SET_DP_RX_D1_PORT_TARGET_LANE_COUNT(enumDpLaneCount);
            SET_DP_RX_CAPABILITY_SWITCHED();
            break;
#endif

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
            SET_DP_RX_D6_PORT_TARGET_LANE_COUNT(enumDpLaneCount);
            SET_DP_RX_CAPABILITY_SWITCHED();
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Set DP Lane Mapping Type
// Input Value  : ucInputPort--> Input Port
//                ucLanetype --> Lane Mapping Type
// Output Value : None
//--------------------------------------------------
void ScalerDpSetDpLaneMapping(BYTE ucInputPort, BYTE ucLanetype)
{
    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _D0_INPUT_PORT:
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif

            ScalerDpRx0SetDpLaneMapping(ucLanetype);
            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:
            ScalerDpRx1SetDpLaneMapping(ucLanetype);
            break;
#endif


#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
        case _D7_INPUT_PORT:
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            ScalerDpRx0SetDpLaneMapping(ucLanetype);
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            ScalerDpRx1SetDpLaneMapping(ucLanetype);
#endif
            break;
#endif

        default:
            break;
    }
}

#if(_DP_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp Get AMD SPD info
// Input Value  : None
// Output Value :
//--------------------------------------------------
BYTE ScalerDpGetAmdSpdInfo(EnumAmdSpdInfoContent enumContent, EnumSourceSearchPort enumSearchPort)
{
    switch(enumSearchPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _D0_INPUT_PORT:

            return ScalerDpRx0GetAmdSpdBackupInfo(enumContent);
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:

            return ScalerDpRx1GetAmdSpdBackupInfo(enumContent);
#endif

        default:

            return 0;
    }
}
//--------------------------------------------------
// Description  : Get Current DP H Period
// Input Value  : enumInputDataPath --> input data path
// Output Value : H period in nano sec
//--------------------------------------------------
WORD ScalerDpGetHSPeriod(EnumInputDataPath enumInputDataPath)
{
    switch(ScalerFmtCnvGetSourceType(enumInputDataPath))
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _FC_SOURCE_D0:

            return ScalerDpRx0GetHPeriod();
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _FC_SOURCE_D1:

            return ScalerDpRx1GetHPeriod();
#endif

        default:

            return 0;
    }
}
//--------------------------------------------------
// Description  : Get Current DP H Sync Width
// Input Value  : enumInputDataPath --> input data path
// Output Value : H Sync Width in pixel clk
//--------------------------------------------------
WORD ScalerDpGetHSW(EnumInputDataPath enumInputDataPath)
{
    switch(ScalerFmtCnvGetSourceType(enumInputDataPath))
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _FC_SOURCE_D0:

            pData[0] = ((DWORD)ScalerDpRx0GetHSW() * _MEASURE_CLK / GET_D0_INPUT_PIXEL_CLK() / 100);
            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _FC_SOURCE_D1:

            pData[0] = ((DWORD)ScalerDpRx1GetHSW() * _MEASURE_CLK / GET_D1_INPUT_PIXEL_CLK() / 100);
            break;
#endif

        default:
            pData[0] = 0;
            break;
    }

    return ((pData[0] == 0) ? 1 : pData[0]);
}
//--------------------------------------------------
// Description  : Dp Get Vfreq
// Input Value  : enumInputDataPath --> input data path
// Output Value : V freq. in 0.1 Hz
//--------------------------------------------------
WORD ScalerDpGetVFreq(EnumInputDataPath enumInputDataPath)
{
    switch(ScalerFmtCnvGetSourceType(enumInputDataPath))
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _FC_SOURCE_D0:

            return ScalerDpRx0GetVFreq();
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _FC_SOURCE_D1:

            return ScalerDpRx1GetVFreq();
#endif

        default:

            return 0;
    }
}
//--------------------------------------------------
// Description  : Get Current DP V Period
// Input Value  : enumInputDataPath --> input data path
// Output Value : V period in line
//--------------------------------------------------
WORD ScalerDpGetVSPeriod(EnumInputDataPath enumInputDataPath)
{
    switch(ScalerFmtCnvGetSourceType(enumInputDataPath))
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _FC_SOURCE_D0:

            return ScalerDpRx0GetVPeriod();
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _FC_SOURCE_D1:

            return ScalerDpRx1GetVPeriod();
#endif

        default:

            return 0;
    }
}
#endif

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Mst Reset
// Input Value  : _DP_MST_RX0_PORT or _DP_MST_RX1_PORT
// Output Value : None
//--------------------------------------------------
void ScalerDpMstReset(EnumDPMSTPort enumRxMstPort)
{
// HW Reset-----------------------------------
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

    if(enumRxMstPort == _DP_MST_RX0_PORT)
    {
        ScalerDpRx0MstReset();
    }
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

    if(enumRxMstPort == _DP_MST_RX1_PORT)
    {
        ScalerDpRx1MstReset();
    }
#endif

// FW Reset-----------------------------------

    // MSG Status Reset
    SET_DP_RX_MST_MODE_STATE(_DP_RX_MST_MODE_STATUS_NONE_MSG);
    SET_DP_RX_EVENT(_DP_RX_NONE_EVENT);

    // Reset Stream ID Mapping Table
    for(pData[0] = 0; pData[0] < 5; pData[0]++)
    {
        g_pucDpStreamToIdMapping[pData[0]] = 0;
    }

    // Clear Down Request MSG Proc Flags
    CLR_DP_RX_DOWN_REQUEST_ANAL();

    // Clear Down Reply MSG Proc Flags
    CLR_DP_RX_DOWN_REPLY_READY();
    CLR_DP_RX_DOWN_REPLY_SET_HPD();
    CLR_DP_RX_DOWN_REPLY_BYPASS();
    CLR_DP_RX_DOWN_REPLY_DIRECTLY();

#if(_DOWN_REPLY_MANUAL_MODE_SUPPORT == _ON)

    // Clear the Rx Down Reply MSG Segment Count No.
    g_ucDpDownReplyManualMsgCount = 0;

#endif

    // Free Request Pool Array
    SET_DP_REQUEST_POOL_FREE();

    // Free Reply Pool Array
    SET_DP_REPLY_POOL_FREE();

    // Free Reply Buffer
    SET_DP_RX_REPLY_BUF_FREE();

    // Reset Down Request Buffer Priority
    SET_DP_RX_DOWN_REQUEST_BUF_PRIORITY(_DP_DOWN_REQUEST_BUF0);

// Tx Reset-----------------------------------

#if(_DP_TX_SUPPORT == _ON)

    ScalerDpTxMstReset();

#endif
}
#endif // #if(_DP_MST_SUPPORT == _ON)

#endif
