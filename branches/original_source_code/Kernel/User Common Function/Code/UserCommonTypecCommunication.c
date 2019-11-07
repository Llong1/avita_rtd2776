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
// ID Code      : UserCommonTypecCommunication.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_TYPECCOMMUNICATION__

#include "UserCommonInclude.h"

#if(_DP_TYPE_C_SUPPORT == _ON)
#if(_PORT_CONTROLLER_RTS_SMBUS_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _SMBUS_READ_DATA_LEN                        24
#define _SMBUS_WRITE_DATA_LEN                       24

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
union UnionSMBusRDCommandStrct g_unSMBusRdDataPool;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
bit UserCommonTypecCommunicationWrite(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray, BYTE ucInputPort);
bit UserCommonTypecCommunicationRead(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucReadArray, BYTE ucInputPort);
bit UserCommonTypecCommunicationShortRead(BYTE ucDeviceAddr, BYTE *pucReadArray, BYTE ucInputPort);
bit UserCommonTypecCommunicationSMBRead(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucReadArray, BYTE ucSWIICStatus, BYTE ucHwIICPinNum);
bit UserCommonTypecCommunicationSMBWrite(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray, BYTE ucSWIICStatus, BYTE ucHwIICPinNum);
bit UserCommonTypecCommunicationPollingPDReady(BYTE ucDeviceAddr, WORD usTime, BYTE ucInputPort);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Write data to the target device address by SMBus
// Input Value  : ucSlaveAddr       --> Device Address
//                usSubAddr         --> Start address of selected device
//                ucSubAddrLength   --> Sub address length
//                usLength          --> Numbers of data we want to write
//                pReadArray        --> Result array
//                ucInputPort       --> Input Port
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
#pragma save
#pragma OT(8)
bit UserCommonTypecCommunicationWrite(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray, BYTE ucInputPort)
{
    if(ucInputPort == _D0_INPUT_PORT)
    {
#if(_D0_DP_SMBUS_IIC == _SW_IIC_PIN_GPIO)

        if(UserCommonTypecCommunicationSMBWrite(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucWriteArray, _IIC_SMBUS, _D0_DP_SMBUS_IIC) == _FAIL)
        {
            return _FAIL;
        }

#elif(_D0_DP_SMBUS_IIC != _NO_IIC_PIN)

        if(UserCommonTypecCommunicationSMBWrite(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucWriteArray, 0x00, _D0_DP_SMBUS_IIC) == _FAIL)
        {
            return _FAIL;
        }
#endif
    }
    else if(ucInputPort == _D1_INPUT_PORT)
    {
#if(_D1_DP_SMBUS_IIC == _SW_IIC_PIN_GPIO)

        if(UserCommonTypecCommunicationSMBWrite(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucWriteArray, _IIC_SMBUS, _D1_DP_SMBUS_IIC) == _FAIL)
        {
            return _FAIL;
        }

#elif(_D1_DP_SMBUS_IIC != _NO_IIC_PIN)

        if(UserCommonTypecCommunicationSMBWrite(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucWriteArray, 0x00, _D1_DP_SMBUS_IIC) == _FAIL)
        {
            return _FAIL;
        }
#endif
    }
    else if(ucInputPort == _D6_INPUT_PORT)
    {
#if(_D1_DP_SMBUS_IIC == _SW_IIC_PIN_GPIO)

        if(UserCommonTypecCommunicationSMBWrite(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucWriteArray, _IIC_SMBUS, _D6_DP_SMBUS_IIC) == _FAIL)
        {
            return _FAIL;
        }

#elif(_D6_DP_SMBUS_IIC != _NO_IIC_PIN)

        if(UserCommonTypecCommunicationSMBWrite(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucWriteArray, 0x00, _D6_DP_SMBUS_IIC) == _FAIL)
        {
            return _FAIL;
        }
#endif
    }

    return _SUCCESS;
}
#pragma restore

//--------------------------------------------------
// Description  : Read data to the External EEPROM by IIC
// Input Value  : ucSlaveAddr       --> Slave Address
//                usSubAddr         --> Start address of selected device
//                ucSubAddrLength   --> Sub address length, if ucSubAddrLength = 0 represent short read command
//                usLength          --> Numbers of data we want to read
//                pReadArray        --> Result array
//                ucInputPort       --> Input Port
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit UserCommonTypecCommunicationRead(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucReadArray, BYTE ucInputPort)
{
    if(ucInputPort == _D0_INPUT_PORT)
    {
#if(_D0_DP_SMBUS_IIC == _SW_IIC_PIN_GPIO)

        if(UserCommonTypecCommunicationSMBRead(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucReadArray, _IIC_SMBUS, _D0_DP_SMBUS_IIC) == _FAIL)
        {
            return _FAIL;
        }

#elif(_D0_DP_SMBUS_IIC != _NO_IIC_PIN)

        if(UserCommonTypecCommunicationSMBRead(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucReadArray, 0x00, _D0_DP_SMBUS_IIC) == _FAIL)
        {
            return _FAIL;
        }
#endif
    }
    else if(ucInputPort == _D1_INPUT_PORT)
    {
#if(_D1_DP_SMBUS_IIC == _SW_IIC_PIN_GPIO)

        if(UserCommonTypecCommunicationSMBRead(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucReadArray, _IIC_SMBUS, _D1_DP_SMBUS_IIC) == _FAIL)
        {
            return _FAIL;
        }

#elif(_D1_DP_SMBUS_IIC != _NO_IIC_PIN)

        if(UserCommonTypecCommunicationSMBRead(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucReadArray, 0x00, _D1_DP_SMBUS_IIC) == _FAIL)
        {
            return _FAIL;
        }
#endif
    }
    else if(ucInputPort == _D6_INPUT_PORT)
    {
#if(_D6_DP_SMBUS_IIC == _SW_IIC_PIN_GPIO)

        if(UserCommonTypecCommunicationSMBRead(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucReadArray, _IIC_SMBUS, _D6_DP_SMBUS_IIC) == _FAIL)
        {
            return _FAIL;
        }

#elif(_D6_DP_SMBUS_IIC != _NO_IIC_PIN)

        if(UserCommonTypecCommunicationSMBRead(ucSlaveAddr, usSubAddr, ucSubAddrLength, usLength, pucReadArray, 0x00, _D6_DP_SMBUS_IIC) == _FAIL)
        {
            return _FAIL;
        }
#endif
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Short Read Command
// Input Value  : ucDeviceAddr --> Device Address
//                pucReadArray --> Result array
//                ucInputPort  --> Input Port
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit UserCommonTypecCommunicationShortRead(BYTE ucDeviceAddr, BYTE *pucReadArray, BYTE ucInputPort)
{
    if(ucInputPort == _D0_INPUT_PORT)
    {
#if(_D0_DP_SMBUS_IIC == _SW_IIC_PIN_GPIO)

        if(UserCommonTypecCommunicationSMBRead(ucDeviceAddr, 0x00, 0, 1, pucReadArray, _IIC_SMBUS, _D0_DP_SMBUS_IIC) == _FAIL)
        {
            return _FAIL;
        }

#elif(_D0_DP_SMBUS_IIC != _NO_IIC_PIN)

        if(UserCommonTypecCommunicationSMBRead(ucDeviceAddr, 0x00, 0, 1, pucReadArray, 0x00, _D0_DP_SMBUS_IIC) == _FAIL)
        {
            return _FAIL;
        }
#endif
    }
    else if(ucInputPort == _D1_INPUT_PORT)
    {
#if(_D1_DP_SMBUS_IIC == _SW_IIC_PIN_GPIO)

        if(UserCommonTypecCommunicationSMBRead(ucDeviceAddr, 0x00, 0, 1, pucReadArray, _IIC_SMBUS, _D1_DP_SMBUS_IIC) == _FAIL)
        {
            return _FAIL;
        }

#elif(_D1_DP_SMBUS_IIC != _NO_IIC_PIN)

        if(UserCommonTypecCommunicationSMBRead(ucDeviceAddr, 0x00, 0, 1, pucReadArray, 0x00, _D1_DP_SMBUS_IIC) == _FAIL)
        {
            return _FAIL;
        }
#endif
    }
    else if(ucInputPort == _D6_INPUT_PORT)
    {
#if(_D6_DP_SMBUS_IIC == _SW_IIC_PIN_GPIO)

        if(UserCommonTypecCommunicationSMBRead(ucDeviceAddr, 0x00, 0, 1, pucReadArray, _IIC_SMBUS, _D6_DP_SMBUS_IIC) == _FAIL)
        {
            return _FAIL;
        }

#elif(_D6_DP_SMBUS_IIC != _NO_IIC_PIN)

        if(UserCommonTypecCommunicationSMBRead(ucDeviceAddr, 0x00, 0, 1, pucReadArray, 0x00, _D6_DP_SMBUS_IIC) == _FAIL)
        {
            return _FAIL;
        }
#endif
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Read data to the External Device by SMBus
// Input Value  : usSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to read
//                pReadArray   --> Result array
//                ucIICStatus   --> SW IIC Applications
//                ucHwIICPinNum --> HW IIC Pin Used
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit UserCommonTypecCommunicationSMBRead(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucReadArray, BYTE ucSWIICStatus, BYTE ucHwIICPinNum)
{
    BYTE ucSlaveAddress = ucSlaveAddr;
    BYTE ucDataCnt = 0;

#if(_SW_IIC_SUPPORT == _OFF)
    ucSWIICStatus = ucSWIICStatus;
#endif

    if(usLength < 0)
    {
        return _FAIL;
    }

    while(usLength > 0)
    {
        if(ucSubAddrLength == 1)
        {
            ucSlaveAddress = ucSlaveAddr + (BYTE)((usSubAddr & 0xFF00) >> 7);
        }

        // Receive max 30 bytes each time
        ucDataCnt = _SMBUS_READ_DATA_LEN;

        // Check if more than 30 bytes are needed to be received
        if(usLength > ucDataCnt)
        {
            usLength -= ucDataCnt;
        }
        else
        {
            ucDataCnt = usLength;
            usLength = 0;
        }

        // Execute Hardware IIC Read Command
        if(ucHwIICPinNum == _SW_IIC_PIN_GPIO)
        {
#if(_SW_IIC_SUPPORT == _ON)
            SET_SW_IIC_STATUS(ucSWIICStatus);

            if(ScalerMcuIICRead(ucSlaveAddress, ucSubAddrLength, usSubAddr, ucDataCnt, pucReadArray) == _FAIL)
            {
                return _FAIL;
            }
#endif // End of #if(_SW_IIC_SUPPORT == _ON)
        }
        else if(ucHwIICPinNum != _NO_IIC_PIN)
        {
#if(_HW_IIC_SUPPORT == _ON)
            if(ScalerMcuHwIICRead(ucSlaveAddress, ucSubAddrLength, usSubAddr, ucDataCnt, pucReadArray, ucHwIICPinNum) == _FAIL)
            {
                return _FAIL;
            }
#endif // End of #if(_HW_IIC_SUPPORT == _ON)
        }

        // Increase data location
        pucReadArray += ucDataCnt;

        // Increment Sub-Addr for next Read
        usSubAddr += ucDataCnt;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Write data to the System EEPROM by IIC
// Input Value  : usSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to write
//                pReadArray   --> Result array
//                ucIICStatus   --> SW IIC Applications
//                ucHwIICPinNum --> HW IIC Pin Used
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
#pragma save
#pragma OT(8)
bit UserCommonTypecCommunicationSMBWrite(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray, BYTE ucSWIICStatus, BYTE ucHwIICPinNum)
{
    BYTE ucSlaveAddress = ucSlaveAddr;
    BYTE ucDataCnt = 0;
    BYTE pucTempData[_SMBUS_WRITE_DATA_LEN + 2];
    BYTE ucTempCnt = 0;

    ucSWIICStatus = ucSWIICStatus;

    if(usLength <= 0)
    {
        return _FAIL;
    }

    while(usLength > 0)
    {
        if(ucSubAddrLength == 1)
        {
            ucSlaveAddress = ucSlaveAddr + (BYTE)((usSubAddr & 0xFF00) >> 7);
        }

        // Transmit max 30 bytes each time
        ucDataCnt = _SMBUS_WRITE_DATA_LEN;

        if(usLength > ucDataCnt)
        {
            usLength -= ucDataCnt;
        }
        else
        {
            ucDataCnt = usLength;
            usLength = 0;
        }

        // Save the data to be transfered to pData to ensure the data is saved in XDATA SPACE
        memcpy(pucTempData, pucWriteArray, ucDataCnt);

        // Increase data location
        pucWriteArray += ucDataCnt;

        // Execute Hardware IIC Write Command
        if(ucHwIICPinNum == _SW_IIC_PIN_GPIO)
        {
#if(_SW_IIC_SUPPORT == _ON)
            SET_SW_IIC_STATUS(ucSWIICStatus);

            if(ScalerMcuIICWrite(ucSlaveAddress, ucSubAddrLength, usSubAddr, ucDataCnt, pucTempData) == _FAIL)
            {
                return _FAIL;
            }
#endif // End of #if(_SW_IIC_SUPPORT == _ON)
        }
        else if(ucHwIICPinNum != _NO_IIC_PIN)
        {
#if(_HW_IIC_SUPPORT == _ON)
            if(ScalerMcuHwIICWrite(ucSlaveAddress, ucSubAddrLength, usSubAddr, ucDataCnt, pucTempData, ucHwIICPinNum) == _FAIL)
            {
                return _FAIL;
            }
#endif // End of #if(_HW_IIC_SUPPORT == _ON)
        }

        // Increment Sub-Addr for next Write
        usSubAddr += ucDataCnt;
    }

    return _SUCCESS;
}
#pragma restore

//--------------------------------------------------
// Description  : Get External Device IC Status
// Input Value  : ucDeviceAddr --> 5400/5411 Device Address
//                usTime       --> Polling Time, Unit: ms
//                ucInputPort  --> Input Port
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit UserCommonTypecCommunicationPollingPDReady(BYTE ucDeviceAddr, WORD usTime, BYTE ucInputPort)
{
    BYTE ucCmdStatus = 0;

    while(usTime > 0)
    {
        UserCommonTypecCommunicationShortRead(ucDeviceAddr, &ucCmdStatus, ucInputPort);

        switch(ucCmdStatus & (_BIT1 | _BIT0))
        {
            case _SMBUS_CMD_STATUS_COMPLETE:

                return _SUCCESS;

            default:
            case _SMBUS_CMD_STATUS_NOTPROCEED:
            case _SMBUS_CMD_STATUS_DEFER:
                break;
        }
        usTime--;

        ScalerTimerDelayXms(1);
    }

    return _FAIL;
}
#endif // End of #if(_PORT_CONTROLLER_RTS_SMBUS_SUPPORT == _ON)
#endif // End of #if(_DP_TYPE_C_SUPPORT == _ON)
