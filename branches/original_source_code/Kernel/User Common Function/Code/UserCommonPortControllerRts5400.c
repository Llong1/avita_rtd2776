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
// ID Code      : UserCommonPortControllerRts5400.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_PORTCONTROLLER5400__

#include "UserCommonInclude.h"

#if(_DP_TYPE_C_SUPPORT == _ON)
#if((_D0_DP_TYPE_C_PORT_CONTROLLER_TYPE == _RTS_5400) || (_D1_DP_TYPE_C_PORT_CONTROLLER_TYPE == _RTS_5400) || (_D6_DP_TYPE_C_PORT_CONTROLLER_TYPE == _RTS_5400))

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************
// Write Command
code StructSMBusWRGetICStatus tSMBusWrCmdGetICStatus[1] = {{0x3A, 0x01, 0x14}};
code StructSMBusWRSetDPMultiFunction tSMBusWrCmdSetDPMultiFunction[1] = {{0x08, 0x08, 0x1A, 0x00, 0x01, 0x0D, 0x18, 0x00, 0x00, 0x00}};
code StructSMBusWRReadDPMultiFunction tSMBusWrCmdReadDPMultiFunction[1] = {{0x08, 0x04, 0x9A, 0x00, 0x01, 0x0D}};
code StructSMBusWRSetDPLanes tSMBusWrCmdSetDPLanes[1] = {{0x08, 0x08, 0x1A, 0x00, 0x01, 0x0C, 0x45, 0x00, 0x08, 0x00}};
code StructSMBusWRReadDPLanes tSMBusWrCmdReadDPLanes[1] = {{0x08, 0x04, 0x9A, 0x00, 0x01, 0x0C}};
code StructSMBusWRReadDPLanes tSMBusWrCmdReadDPLanesCfg[1] = {{0x08, 0x04, 0x9A, 0x00, 0x09, 0x0E}};
code StructSMBusWRReconnect tSMBusWrCmdSetReconnect[1] = {{0x08, 0x03, 0x1F, 0x00, 0x01}};

// Read Command
code StructSMBusRDCommandReadyStatus tSMBusRdCmdCommandReadyStatus[1] = {{0x00, 0x00}};
code StructSMBusRDGetICStatus tSMBusRdCmdGetICStatus[1] = {{0x80, 0x14, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
code StructSMBusRDReadDPMultiFunction tSMBusRdCmdDPMultiFunction[1] = {{0x80, 0x04, 0x08, 0x00, 0x00, 0x00}};
code StructSMBusRDReadDPLanes tSMBusRdCmdDPlanes[1] = {{0x80, 0x04, 0x45, 0x00, 0x08, 0x00}};
code StructSMBusRDReadDPLanesCfg tSMBusRdCmdDPlanesCfg[1] = {{0x80, 0x04, 0x06, 0x08, 0x00, 0x00}};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
BYTE UserCommonPortControllerGetPCAddr(BYTE ucInputPort);
bit UserCommonPortControllerGetPCStatus(BYTE ucInputPort);
bit UserCommonPortControllerGetPCCfgStatus(BYTE ucInputPort);
bit UserCommonPortControllerCheckPCEnterAltMode(BYTE ucInputPort);
bit UserCommonPortControllerSetPCDPMultiFunction(BYTE ucInputPort, bit bMultiFunction);
bit UserCommonPortControllerSetPCDPLanes(BYTE ucInputPort, BYTE ucLanes);
bit UserCommonPortControllerReconnect(BYTE ucInputPort);
bit UserCommonPortControllerConfig(BYTE ucInputPort);

#if(_D0_DP_TYPE_C_SUPPORT == _ON)
bit UserCommonPortControllerGetD0PortPower(void);
#endif

#if(_D1_DP_TYPE_C_SUPPORT == _ON)
bit UserCommonPortControllerGetD1PortPower(void);
#endif

#if(_D6_DP_TYPE_C_SUPPORT == _ON)
bit UserCommonPortControllerGetD6PortPower(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get Port Controller Slave Address
// Input Value  : ucInputPort --> Input Port
// Output Value : Slave Address
//--------------------------------------------------
BYTE UserCommonPortControllerGetPCAddr(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:
            return _D0_DP_TYPE_C_RTS5400_SLAVE_ADDRESS;

        case _D1_INPUT_PORT:
            return _D1_DP_TYPE_C_RTS5400_SLAVE_ADDRESS;

        case _D6_INPUT_PORT:
            return _D6_DP_TYPE_C_RTS5400_SLAVE_ADDRESS;

        default:
            break;
    }

    return _D0_DP_TYPE_C_RTS5400_SLAVE_ADDRESS;
}

//--------------------------------------------------
// Description  : Read IC Status from the 5400/5411 by SMBus
// Input Value  : None
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit UserCommonPortControllerGetPCStatus(BYTE ucInputPort)
{
    BYTE ucSlaveAddr = UserCommonPortControllerGetPCAddr(ucInputPort);

    // Execute Write Command
    if(UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWrCmdGetICStatus[0].ucCommandCode, 1, tSMBusWrCmdGetICStatus[0].ucDataLength + 1, &(tSMBusWrCmdGetICStatus[0].ucDataLength), ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    // Polling Write Command Operation Status
    if(UserCommonTypecCommunicationPollingPDReady(ucSlaveAddr, 100, ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    // Read Back Device Reply Data
    if(UserCommonTypecCommunicationRead(ucSlaveAddr, tSMBusRdCmdGetICStatus[0].ucCommandCode, 1, tSMBusRdCmdGetICStatus[0].ucDataLength, &(g_unSMBusRdDataPool.stRdGetICStatus.ucDataLength), ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    // Fill in Original Subcommand Code for g_unSMBusRdDataPool structure
    g_unSMBusRdDataPool.stRdGetICStatus.ucCommandCode = tSMBusRdCmdGetICStatus[0].ucCommandCode;

    return _TRUE;
}

//--------------------------------------------------
// Description  : Read 5400 Type-C Configration Status
// Input Value  : ucInputPort --> Inputput
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit UserCommonPortControllerGetPCCfgStatus(BYTE ucInputPort)
{
    BYTE ucSlaveAddr = UserCommonPortControllerGetPCAddr(ucInputPort);

    // Execute Write Command
    if(UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWrCmdReadDPLanesCfg[0].ucCommandCode, 1, tSMBusWrCmdReadDPLanesCfg[0].ucDataLength + 1, &(tSMBusWrCmdReadDPLanesCfg[0].ucDataLength), ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    // Polling Write Command Operation Status
    if(UserCommonTypecCommunicationPollingPDReady(ucSlaveAddr, 100, ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    // Read Back Device Reply Data
    if(UserCommonTypecCommunicationRead(ucSlaveAddr, tSMBusRdCmdDPlanesCfg[0].ucCommandCode, 1, tSMBusRdCmdDPlanesCfg[0].ucDataLength, &(g_unSMBusRdDataPool.stRdDPlanesCfg[0].ucDataLength), ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    // Fill in Original Subcommand Code for g_unSMBusRdDataPool structure
    g_unSMBusRdDataPool.stRdDPlanesCfg.ucCommandCode = tSMBusRdCmdDPlanesCfg[0].ucCommandCode;

    return _TRUE;
}

//--------------------------------------------------
// Description  : Check 5400 Enter Alt Mode
// Input Value  : ucInputPort --> Inputput
// Output Value : Operation result (Fail/Success)
//--------------------------------------------------
bit UserCommonPortControllerCheckPCEnterAltMode(BYTE ucInputPort)
{
    if(UserInterfaceTypeCPortControllerDecitionAltMode(ucInputPort) == _SUCCESS)
    {
        return _TRUE;
    }

    // Get 5400 Enter Alt Mode
    if(UserCommonPortControllerGetPCCfgStatus(ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    if((g_unSMBusRdDataPool.stRdDPlanesCfg.ucDPCfgPinConfig == 0x04) || (g_unSMBusRdDataPool.stRdDPlanesCfg.ucDPCfgPinConfig == 0x08))
    {
        return _TRUE; // Enter Alt Mode Already
    }

    return _FAIL;
}

//--------------------------------------------------
// Description  : Set 5400 IC DP MultiFunction
// Input Value  : bMultiFunction --> _TRUE: Support Usb + DP Function, _FALSE: DP Function only
// Output Value : Operation result (Fail/Success)
//--------------------------------------------------
bit UserCommonPortControllerSetPCDPMultiFunction(BYTE ucInputPort, bit bMultiFunction)
{
    StructSMBusWRSetDPMultiFunction stDpMultiFunction;
    BYTE ucSlaveAddr = UserCommonPortControllerGetPCAddr(ucInputPort);

    memcpy(&stDpMultiFunction, &tSMBusWrCmdSetDPMultiFunction[0], tSMBusWrCmdSetDPMultiFunction[0].ucDataLength + 2);

    if(bMultiFunction == _TRUE)
    {
        // Set to Multifunction Prefer
        stDpMultiFunction.ucDPCapVDOByte0 = 0x18;
    }
    else
    {
        // Set to Multifunction Not Prefer
        stDpMultiFunction.ucDPCapVDOByte0 = 0x08;
    }

    // Execute Write Command
    if(UserCommonTypecCommunicationWrite(ucSlaveAddr, stDpMultiFunction.ucCommandCode, 1, stDpMultiFunction.ucDataLength + 1, &stDpMultiFunction.ucDataLength, ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    // Polling Write Command Operation Status
    if(UserCommonTypecCommunicationPollingPDReady(ucSlaveAddr, 100, ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Set 5400 DP Lanes Counter
// Input Value  : None
// Output Value : Operation result (Fail/Success)
//--------------------------------------------------
bit UserCommonPortControllerSetPCDPLanes(BYTE ucInputPort, BYTE ucLanes)
{
    StructSMBusWRSetDPLanes stDpLaneConfigPar;
    BYTE ucSlaveAddr = UserCommonPortControllerGetPCAddr(ucInputPort);

    memcpy(&stDpLaneConfigPar, &tSMBusWrCmdSetDPLanes[0], tSMBusWrCmdSetDPLanes[0].ucDataLength + 2);

    if(ucLanes == _DP_FOUR_LANE)
    {
        stDpLaneConfigPar.ucDPCapVDOByte2 = 0x04; // 4 Lane DP Only
    }
    else if(ucLanes == _DP_TWO_LANE)
    {
        stDpLaneConfigPar.ucDPCapVDOByte2 = 0x08; // 2 Lane DP + 2 Lane Usb
    }
    else
    {
        stDpLaneConfigPar.ucDPCapVDOByte2 = 0x0C; // Both 2 Lane/4 Lane
    }

    // Execute Write Command
    if(UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWrCmdSetDPLanes[0].ucCommandCode, 1, tSMBusWrCmdSetDPLanes[0].ucDataLength + 1, &stDpLaneConfigPar.ucDataLength, ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    // Polling Write Command Operation Status
    if(UserCommonTypecCommunicationPollingPDReady(ucSlaveAddr, 100, ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Reconnect 5400 Device
// Input Value  : None
// Output Value : Operation result (Fail/Success)
//--------------------------------------------------
bit UserCommonPortControllerReconnect(BYTE ucInputPort)
{
    BYTE ucSlaveAddr = UserCommonPortControllerGetPCAddr(ucInputPort);

    // Execute Write Command
    if(UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWrCmdSetReconnect[0].ucCommandCode, 1, tSMBusWrCmdSetReconnect[0].ucDataLength + 1, &(tSMBusWrCmdSetReconnect[0].ucDataLength), ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    // Polling Write Command Operation Status
    if(UserCommonTypecCommunicationPollingPDReady(ucSlaveAddr, 500, ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : 5400 Config
// Input Value  : ucInputPort --> Input Port
// Output Value : Operation result (Fail/Success)
//--------------------------------------------------
bit UserCommonPortControllerConfig(BYTE ucInputPort)
{
    BYTE ucDPLanes = _DP_TWO_LANE;

    ucDPLanes = UserInterfaceGetDpLaneCount(ucInputPort);

    // Get 5400 IC Status
    if(UserCommonPortControllerGetPCStatus(ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    // Set Dp Multifuncton
    if(UserCommonPortControllerSetPCDPMultiFunction(ucInputPort, (ucDPLanes == _DP_TWO_LANE) ? _TRUE : _FALSE) == _FAIL)
    {
        return _FAIL;
    }

    // Set Dp Lane
    if(UserCommonPortControllerSetPCDPLanes(ucInputPort, ucDPLanes) == _FAIL)
    {
        return _FAIL;
    }

    if((g_unSMBusRdDataPool.stRdGetICStatus.ucPDTypeCStatus & (_BIT3 | _BIT0)) == (_BIT3 | _BIT0))
    {
        // Set Dp Reconnect
        if(UserCommonPortControllerReconnect(ucInputPort) == _FAIL)
        {
            return _FAIL;
        }
    }

    return _TRUE;
}

#if(_D0_DP_TYPE_C_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get D0 Port Controller Power Status
// Input Value  : None
// Output Value : _ON /_OFF
//--------------------------------------------------
bit UserCommonPortControllerGetD0PortPower(void)
{
    return UserInterfaceTypeCGetD0PortControllerPower();
}
#endif

#if(_D1_DP_TYPE_C_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get D1 Port Controller Power Status
// Input Value  : None
// Output Value : _ON /_OFF
//--------------------------------------------------
bit UserCommonPortControllerGetD1PortPower(void)
{
    return UserInterfaceTypeCGetD1PortControllerPower();
}
#endif

#if(_D6_DP_TYPE_C_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get D6 Port Controller Power Status
// Input Value  : None
// Output Value : _ON /_OFF
//--------------------------------------------------
bit UserCommonPortControllerGetD6PortPower(void)
{
    return UserInterfaceTypeCGetD6PortControllerPower();
}
#endif
#endif // End of #if((_D0_DP_TYPE_C_PORT_CONTROLLER_TYPE == _RTS_5400) || (_D1_DP_TYPE_C_PORT_CONTROLLER_TYPE == _RTS_5400) || (_D2_DP_TYPE_C_PORT_CONTROLLER_TYPE == _RTS_5400) || (_D6_DP_TYPE_C_PORT_CONTROLLER_TYPE == _RTS_5400))
#endif // End of #if(_DP_TYPE_C_SUPPORT == _ON)
