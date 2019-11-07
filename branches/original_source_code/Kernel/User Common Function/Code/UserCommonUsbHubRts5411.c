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
// ID Code      : UserCommonUsbHubRts5411.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_USBHUB5411__

#include "UserCommonInclude.h"

#if(_DP_TYPE_C_SUPPORT == _ON)
#if((_D0_DP_TYPE_C_USB_HUB_TYPE == _RTS_5411) || (_D1_DP_TYPE_C_USB_HUB_TYPE == _RTS_5411) || (_D6_DP_TYPE_C_USB_HUB_TYPE == _RTS_5411))

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
code StructSMBusWrSetSSMode tSMBusWrSetSSMode[1] = {{0x31, 0x01, 0x01}};
code StructSMBusWRDetectDSPSSMode tSMBusWDetectDspSSMode[1] = {{0x30, 0x03, 0x00, 0x00, 0x04}};

// Read Command
code StructSMBusRDDetectDSPSSMode tSMBusRdDetectDspSSDevice[1] = {{0x80, 0x04, 0x50, 0x50, 0x50, 0x50}};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
BYTE UserCommonUsbHubGetHubAddr(BYTE ucInputPort);
bit UserCommonUsbHubSetSSMode(BYTE ucInputPort, bit bEn);
BYTE UserCommonUsbHubDetectSSDevicePlugInfo(BYTE ucInputPort);
WORD UserCommonUsbHubSetPollingStep(BYTE ucInputPort);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get Usb Hub Controller Slave Address
// Input Value  : ucInputPort --> Input Port
// Output Value : Slave Address
//--------------------------------------------------
BYTE UserCommonUsbHubGetHubAddr(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
        case _D0_INPUT_PORT:
            return _D0_DP_TYPE_C_RTS5411_SLAVE_ADDRESS;

        case _D1_INPUT_PORT:
            return _D1_DP_TYPE_C_RTS5411_SLAVE_ADDRESS;

        case _D6_INPUT_PORT:
            return _D6_DP_TYPE_C_RTS5411_SLAVE_ADDRESS;

        default:
            break;
    }

    return _D0_DP_TYPE_C_RTS5411_SLAVE_ADDRESS;
}

//--------------------------------------------------
// Description  : Set 5411 into SS Mode
// Input Value  : None
// Output Value : Operation result (Fail/Success)
//--------------------------------------------------
bit UserCommonUsbHubSetSSMode(BYTE ucInputPort, bit bEn)
{
    BYTE ucCnt = 0;
    StructSMBusWrSetSSMode stWrSSMode;
    BYTE ucSlaveAddr = UserCommonUsbHubGetHubAddr(ucInputPort);

    memcpy(&stWrSSMode, &tSMBusWrSetSSMode[0], tSMBusWrSetSSMode[0].ucDataLength + 2);

    if(bEn == _ENABLE)
    {
        // Enable SS Mode
        stWrSSMode.ucByte0 = 0x01;
    }
    else
    {
        // Disable SS Mode
        stWrSSMode.ucByte0 = 0x02;
    }

    // Execute Write Command
    if(UserCommonTypecCommunicationWrite(ucSlaveAddr, stWrSSMode.ucCommandCode, 1, stWrSSMode.ucDataLength + 1, &stWrSSMode.ucDataLength, ucInputPort) == _FAIL)
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
// Description  : Detect 5411 SS Device Plug In
// Input Value  : ucInputPort --> Input Port
// Output Value : Return SS Device Info.
//--------------------------------------------------
BYTE UserCommonUsbHubDetectSSDevicePlugInfo(BYTE ucInputPort)
{
    BYTE ucUsbHubInfo = 0;
    BYTE ucSlaveAddr = UserCommonUsbHubGetHubAddr(ucInputPort);

    // Execute Write Command
    if(UserCommonTypecCommunicationWrite(ucSlaveAddr, tSMBusWDetectDspSSMode[0].ucCommandCode, 1, tSMBusWDetectDspSSMode[0].ucDataLength + 1, &(tSMBusWDetectDspSSMode[0].ucDataLength), ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    // Polling Write Command Operation Status
    if(UserCommonTypecCommunicationPollingPDReady(ucSlaveAddr, 100, ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    // Read Back Device Reply Data
    if(UserCommonTypecCommunicationRead(ucSlaveAddr, tSMBusRdDetectDspSSDevice[0].ucCommandCode, 1, tSMBusRdDetectDspSSDevice[0].ucDataLength, &(g_unSMBusRdDataPool.stRdDetectDspSSMode.ucDataLength), ucInputPort) == _FAIL)
    {
        return _FAIL;
    }

    // Fill in Original Subcommand Code for g_unSMBusRdDataPool structure
    g_unSMBusRdDataPool.stRdDetectDspSSMode.ucCommandCode = tSMBusRdDetectDspSSDevice[0].ucCommandCode;

    if((g_unSMBusRdDataPool.stRdDetectDspSSMode.ucDSP0 == 0x10) || (g_unSMBusRdDataPool.stRdDetectDspSSMode.ucDSP0 == 0x20))
    {
        ucUsbHubInfo |= _BIT0;
    }

    if((g_unSMBusRdDataPool.stRdDetectDspSSMode.ucDSP1 == 0x10) || (g_unSMBusRdDataPool.stRdDetectDspSSMode.ucDSP1 == 0x20))
    {
        ucUsbHubInfo |= _BIT1;
    }

    if((g_unSMBusRdDataPool.stRdDetectDspSSMode.ucDSP2 == 0x10) || (g_unSMBusRdDataPool.stRdDetectDspSSMode.ucDSP2 == 0x20))
    {
        ucUsbHubInfo |= _BIT2;
    }

    if((g_unSMBusRdDataPool.stRdDetectDspSSMode.ucDSP3 == 0x10) || (g_unSMBusRdDataPool.stRdDetectDspSSMode.ucDSP3 == 0x20))
    {
        ucUsbHubInfo |= _BIT3;
    }

    return ucUsbHubInfo;
}

//--------------------------------------------------
// Description  : User Set Usb Hub Polling SS Device Step
// Input Value  : ucInputPort --> Input Port
// Output Value : Usb Hub Polling Step Par.
//--------------------------------------------------
WORD UserCommonUsbHubSetPollingStep(BYTE ucInputPort)
{
    return UserInterfaceTypecUsbHubSetPollingStep(ucInputPort);
}
#endif // End of #if((_D0_DP_TYPE_C_USB_HUB_TYPE == _RTS_5411) || (_D1_DP_TYPE_C_USB_HUB_TYPE == _RTS_5411) || (_D2_DP_TYPE_C_USB_HUB_TYPE == _RTS_5411) || (_D6_DP_TYPE_C_USB_HUB_TYPE == _RTS_5411))
#endif // End of #if(_DP_TYPE_C_SUPPORT == _ON)
