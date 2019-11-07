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
// ID Code      : UserCommonUsbHubUser.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_USBUSER__

#include "UserCommonInclude.h"

#if(_DP_TYPE_C_SUPPORT == _ON)
#if(_USB_HUB_USERDECITION_SUPPORT == _ON)

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
bit UserCommonUsbHubSetSSMode(BYTE ucInputPort, bit bEn);
BYTE UserCommonUsbHubDetectSSDevicePlugInfo(BYTE ucInputPort);
WORD UserCommonUsbHubSetPollingStep(BYTE ucInputPort);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set 5411 into SS Mode
// Input Value  : None
// Output Value : Operation result (Fail/Success)
//--------------------------------------------------
bit UserCommonUsbHubSetSSMode(BYTE ucInputPort, bit bEn)
{
    return UserInterfaceTypecUsbHubSetSSMode(ucInputPort, bEn);
}

//--------------------------------------------------
// Description  : Detect 5411 SS Device Plug In
// Input Value  : ucInputPort --> Input Port
// Output Value : Return SS Device Info.
//--------------------------------------------------
BYTE UserCommonUsbHubDetectSSDevicePlugInfo(BYTE ucInputPort)
{
    return UserInterfaceTypecUsbHubDetectSSDevicePlugInfo(ucInputPort);
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
#endif // End of #if(_USB_HUB_USERDECITION_SUPPORT == _ON)
#endif // End of #if(_DP_TYPE_C_SUPPORT == _ON)
