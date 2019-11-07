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
// ID Code      : ScalerNVRam.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCLAER_NVRAM__

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
#if((_FLASH_ACCESS_FUNCTION_SUPPORT == _ON) || (_FLASH_WR_PROTECT == _ON))
StructFlashInformation code tFlashInformation[] =
{
    // _FLASH_W25X20A; ucUnprotectWRSR is not used here
    {0x9F, 0xEF, 0x30, 0x12, 0x90, 0xEF, 0x11, 0x00, 0x06, 0x04, 0x20, 0x28, 0xBC},
    // _FLASH_W25X21CL; ucUnprotectWRSR is not used here
    {0x9F, 0xEF, 0x30, 0x12, 0x90, 0xEF, 0x11, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC},
    // _FLASH_PM25LV020; ucUnprotectWRSR is not used here
    {0x9F, 0x7F, 0x9D, 0x7D, 0xAB, 0x9D, 0x7D, 0x7F, 0x26, 0x24, 0xD7, 0x00, 0x9C},
    // _FLASH_MX25L2026; ucUnprotectWRSR is not used here
    {0x9F, 0xC2, 0x20, 0x12, 0x90, 0xC2, 0x03, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC},
    // _FLASH_EN25F20; ucUnprotectWRSR is not used here
    {0x9F, 0x1C, 0x31, 0x12, 0x90, 0x1C, 0x11, 0x00, 0x06, 0x04, 0x20, 0x02, 0x9C},
    // _FLASH_PM25LD020; ucUnprotectWRSR is not used here
    {0x9F, 0x7F, 0x9D, 0x22, 0x90, 0x9D, 0x11, 0x7F, 0x26, 0x24, 0xD7, 0x00, 0x9C},
    // _FLASH_MX25L2025; ucUnprotectWRSR is not used here
    {0x9F, 0xC2, 0x20, 0x12, 0x90, 0xC2, 0x11, 0x00, 0x06, 0x04, 0x20, 0x02, 0x8C},
    // _FLASH_MX25L4006E; ucUnprotectWRSR is not used here
    {0X9F, 0xC2, 0x20, 0x13, 0x90, 0xC2, 0x12, 0x00, 0x06, 0x04, 0x20, 0x02, 0x9C},
    // _FLASH_SST25LF020A
    {0x90, 0xBF, 0x43, 0x00, 0x90, 0xBF, 0x43, 0x00, 0x06, 0x04, 0x20, 0x02, 0x9C},
    // _FLASH_W25X41CL; ucUnprotectWRSR is not used here
    {0x9F, 0xEF, 0x30, 0x13, 0x90, 0xEF, 0x12, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC},
    // _FLASH_FM25F04; ucUnprotectWRSR is not used here
    {0x9F, 0xA1, 0x31, 0x13, 0x90, 0xA1, 0x12, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC},
    // _FLASH_N25S40; ucUnprotectWRSR is not used here
    {0x9F, 0xD5, 0x30, 0x13, 0x90, 0xD5, 0x12, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC},
    // _FLASH_A25L040; ucUnprotectWRSR is not used here
    {0x9F, 0x37, 0x30, 0x13, 0x90, 0x37, 0x12, 0x00, 0x06, 0x04, 0x20, 0x02, 0x9C},
    // _FLASH_W25Q80BV; ucUnprotectWRSR is not used here
    {0x9F, 0xEF, 0x40, 0x14, 0x90, 0xEF, 0x13, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC},
    // _FLASH_PM25LQ020A; ucUnprotectWRSR is not used here
    {0x9F, 0x7F, 0x9D, 0x42, 0x90, 0x9D, 0x11, 0x7F, 0x26, 0x24, 0x20, 0x02, 0x9C},
    // _FLASH_MX25L4026D; ucUnprotectWRSR is not used here
    {0x9F, 0xC2, 0x20, 0x13, 0x90, 0xC2, 0x04, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC},
    // _FLASH_W25X40CL; ucUnprotectWRSR is not used here
    {0x9F, 0xEF, 0x30, 0x13, 0x90, 0xEF, 0x12, 0x00, 0x06, 0x04, 0x20, 0x02, 0xBC},
    // _FLASH_MX25L1606E; ucUnprotectWRSR is not used here
    {0x9F, 0xC2, 0x20, 0x15, 0x90, 0xC2, 0x14, 0x00, 0x06, 0x04, 0x20, 0x02, 0xBC},
    // _FLASH_MX25L3206E; ucUnprotectWRSR is not used here
    {0x9F, 0xC2, 0x20, 0x16, 0x90, 0xC2, 0x15, 0x00, 0x06, 0x04, 0x20, 0x02, 0xBC},
    // _FLASH_A25L016; ucUnprotectWRSR is not used here
    {0x9F, 0x37, 0x30, 0x15, 0x90, 0x37, 0x14, 0x00, 0x06, 0x04, 0x20, 0x02, 0x9C},
    // _FLASH_W25Q16DV; ucUnprotectWRSR is not used here
    {0x9F, 0xEF, 0x40, 0x15, 0x90, 0xEF, 0x14, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC},
    // _FLASH_A25L032; ucUnprotectWRSR is not used here
    {0x9F, 0x37, 0x30, 0x16, 0x90, 0x37, 0x15, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC},
    // _FLASH_W25Q32F; ucUnprotectWRSR is not used here
    {0x9F, 0xEF, 0x40, 0x16, 0x90, 0xEF, 0x15, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC},
    // _FLASH_GD25Q16; ucUnprotectWRSR is not used here
    {0x9F, 0xC8, 0x40, 0x15, 0x90, 0xC8, 0x14, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC},
    // _FLASH_MX25L1633E; ucUnprotectWRSR is not used here
    {0x9F, 0xC2, 0x24, 0x15, 0x90, 0xC2, 0x24, 0x00, 0x06, 0x04, 0x20, 0x02, 0xBC},
    // _FLASH_PM25LQ080C; ucUnprotectWRSR is not used here
    {0x9F, 0x9D, 0x13, 0x44, 0x90, 0x9D, 0x13, 0x7F, 0x26, 0x24, 0xD7, 0x00, 0xBC},
    // _FLASH_GD25Q16C; ucUnprotectWRSR is not used here
    {0x9F, 0xC8, 0x40, 0x15, 0x90, 0xC8, 0x14, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC},
    // _FLASH_MX25L3233F; ucUnprotectWRSR is not used here
    {0x9F, 0xC2, 0x20, 0x16, 0x90, 0xC2, 0x15, 0x00, 0x06, 0x04, 0x20, 0x02, 0xBC},
    // _FLASH_EN25QH32A; ucUnprotectWRSR is not used here
    {0x9F, 0x1C, 0x70, 0x16, 0x90, 0x1C, 0x15, 0x00, 0x06, 0x04, 0x20, 0x02, 0xBC},
    // _FLASH_MX25L8006E; ucUnprotectWRSR is not used here
    {0X9F, 0xC2, 0x20, 0x14, 0x90, 0xC2, 0x13, 0x00, 0x06, 0x04, 0x20, 0x02, 0x9C},
    // _FLASH_MX25V1635F; ucUnprotectWRSR is not used here
    {0x9F, 0xC2, 0x23, 0x15, 0x90, 0xC2, 0x15, 0x00, 0x06, 0x04, 0x20, 0x02, 0xBC},
    // _FLASH_AT25SF041; ucUnprotectWRSR is not used here
    {0x9F, 0x1F, 0x84, 0x01, 0x90, 0x1F, 0x12, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC},
    // _FLASH_MX25L6433F; ucUnprotectWRSR is not used here
    {0x9F, 0xC2, 0x20, 0x17, 0x90, 0xC2, 0x16, 0x00, 0x06, 0x04, 0x20, 0x02, 0xBC},
    // _FLASH_PM25LQ016; ucUnprotectWRSR is not used here
    {0x9F, 0x9D, 0x14, 0x45, 0x90, 0x9D, 0x14, 0x7F, 0x26, 0x24, 0x20, 0x02, 0xBC},
    // _FLASH_GD25Q32C; ucUnprotectWRSR is not used here
    {0x9F, 0xC8, 0x40, 0x16, 0x90, 0xC8, 0X15, 0x00, 0x06, 0x04, 0x20, 0x02, 0xFC},
    // _FLASH_MX25R8035F; ucUnprotectWRSR is not used here
    {0x9F, 0xC2, 0x28, 0x14, 0x90, 0xC2, 0x14, 0x00, 0x06, 0x04, 0x20, 0x02, 0xBC},
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE g_ucFlashType = _FLASH_UNDETECT;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerFlashDetectFlashType(void);
bit ScalerFlashReadFlashIDCode(BYTE ucRDIDOPCode, BYTE *pucIDArry);

#if(_FLASH_ACCESS_FUNCTION_SUPPORT == _ON)
void ScalerFlashWREN(BYTE ucBank, BYTE ucPage);
void ScalerFlashWRDis(void);
#endif

void ScalerFlashSetWREN(BYTE ucOpCode);
void ScalerFlashSetWRSR(BYTE ucWRSR, bit bIsSST);
void ScalerFlashSet2ByteWRSR(BYTE ucWRSR1, BYTE ucWRSR2, bit bIsSST);
void ScalerFlashSet2ByteWRSRonebyone(BYTE ucWRSR1, BYTE ucWRSR2, bit bIsSST);

#if(_FLASH_ACCESS_FUNCTION_SUPPORT == _ON)
bit ScalerFlashErasePage(BYTE ucBank, BYTE ucPage);
#endif

#if(_FLASH_WR_PROTECT == _ON)
void ScalerFlashWRProtect(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Auto detect current flash type
// Input Value  : None
// Output Value : Detected flash type index
//--------------------------------------------------
void ScalerFlashDetectFlashType(void)
{
    BYTE ucIndex = 0;
    BYTE ucIDCheck1PassFlashCount = 0;
    BYTE pucIDArry[3];
    BYTE pucFlashType[8];

    memset(pucIDArry, 0, sizeof(pucIDArry));
    memset(pucFlashType, 0, sizeof(pucFlashType));

    // ID check 1, use 0x9F/0x90/0xAB op code base on flash spec
    for(ucIndex = 0; ucIndex < _FLASH_TOTAL_COUNT; ucIndex++)
    {
        if(ScalerFlashReadFlashIDCode(tFlashInformation[ucIndex].ucIDCheck1OpCode, pucIDArry) == _TRUE)
        {
            // ID = 0 means ignore
            if((tFlashInformation[ucIndex].ucIDCheck1_ID0 == 0x00) || (pucIDArry[0] == tFlashInformation[ucIndex].ucIDCheck1_ID0))
            {
                if((tFlashInformation[ucIndex].ucIDCheck1_ID1 == 0x00) || (pucIDArry[1] == tFlashInformation[ucIndex].ucIDCheck1_ID1))
                {
                    if((tFlashInformation[ucIndex].ucIDCheck1_ID2 == 0x00) || (pucIDArry[2] == tFlashInformation[ucIndex].ucIDCheck1_ID2))
                    {
                        // Save matched flash type index to buffer
                        pucFlashType[ucIDCheck1PassFlashCount] = ucIndex;
                        ucIDCheck1PassFlashCount++;
                    }
                }
            }
        }
        else
        {
            // Read ID code failed
            g_ucFlashType = _FLASH_DEFAULT_TYPE;
            return;
        }
    }

    // Find only one matched flash type in ID check 1
    if(ucIDCheck1PassFlashCount == 1)
    {
        g_ucFlashType = pucFlashType[0];
        return;
    }
    // Find more than one flash type in ID check 1
    else if(ucIDCheck1PassFlashCount > 1)
    {
        // Find more than 1 types in ID check 1, use ID check 2 to choose
        for(ucIndex = 0; ucIndex < ucIDCheck1PassFlashCount; ucIndex++)
        {
            // ID check 2
            if(ScalerFlashReadFlashIDCode(tFlashInformation[pucFlashType[ucIndex]].ucIDCheck2OpCode, pucIDArry) == _TRUE)
            {
                // ID = 0 means ignore
                if((tFlashInformation[pucFlashType[ucIndex]].ucIDCheck2_ID0 != 0x00) && (pucIDArry[0] != tFlashInformation[pucFlashType[ucIndex]].ucIDCheck2_ID0))
                {
                    continue;
                }

                if((tFlashInformation[pucFlashType[ucIndex]].ucIDCheck2_ID1 != 0x00) && (pucIDArry[1] != tFlashInformation[pucFlashType[ucIndex]].ucIDCheck2_ID1))
                {
                    continue;
                }

                if((tFlashInformation[pucFlashType[ucIndex]].ucIDCheck2_ID2 != 0x00) && (pucIDArry[2] != tFlashInformation[pucFlashType[ucIndex]].ucIDCheck2_ID2))
                {
                    continue;
                }

                break;
            }
        }

        if(ucIndex >= ucIDCheck1PassFlashCount)
        {
            g_ucFlashType = pucFlashType[0];
            return;
        }
        else
        {
            g_ucFlashType = pucFlashType[ucIndex];

#if(_FLASH_TYPE_W25X20A_OR_W25X21CL == _FLASH_W25X20A)
            if(g_ucFlashType == _FLASH_W25X21CL)
            {
                g_ucFlashType = _FLASH_W25X20A;
            }
#else
            if(g_ucFlashType == _FLASH_W25X20A)
            {
                g_ucFlashType = _FLASH_W25X21CL;
            }
#endif

#if(_FLASH_TYPE_W25X40CL_OR_W25X41CL == _FLASH_W25X40CL)
            if(g_ucFlashType == _FLASH_W25X41CL)
            {
                g_ucFlashType = _FLASH_W25X40CL;
            }
#else
            if(g_ucFlashType == _FLASH_W25X40CL)
            {
                g_ucFlashType = _FLASH_W25X41CL;
            }
#endif

#if(_FLASH_TYPE_GD25Q16C_OR_GD25Q16 == _FLASH_GD25Q16C)
            if(g_ucFlashType == _FLASH_GD25Q16)
            {
                g_ucFlashType = _FLASH_GD25Q16C;
            }
#else
            if(g_ucFlashType == _FLASH_GD25Q16C)
            {
                g_ucFlashType = _FLASH_GD25Q16;
            }
#endif

#if(_FLASH_TYPE_MX25L3206E_OR_MX25L3233F == _FLASH_MX25L3233F)
            if(g_ucFlashType == _FLASH_MX25L3206E)
            {
                g_ucFlashType = _FLASH_MX25L3233F;
            }
#else
            if(g_ucFlashType == _FLASH_MX25L3233F)
            {
                g_ucFlashType = _FLASH_MX25L3206E;
            }
#endif
            return;
        }
    }
    else
    {
        // Do not find 1 type in ID check 1
        g_ucFlashType = _FLASH_DEFAULT_TYPE;
        return;
    }

    g_ucFlashType = _FLASH_DEFAULT_TYPE;
}

//--------------------------------------------------
// Description  : Read flash ID code
// Input Value  : ucRDIDOPCode: Read ID code op code
//                pucIDArry: Saved the ID code read from flash
// Output Value : _TRUE for read success, else return _FALSE
//--------------------------------------------------
bit ScalerFlashReadFlashIDCode(BYTE ucRDIDOPCode, BYTE *pucIDArry)
{
    BYTE ucIndex = 0;
    BYTE ucTryCount = 10;
    BYTE ucID0 = 0;
    BYTE ucID1 = 0;
    BYTE ucID2 = 0;

    switch(ucRDIDOPCode)
    {
        case 0x9F:

            //////////////////////////////////////////////////////////////////////////
            // Use JEDECID Instruction to get Flash Manufacture ID, Device ID       //
            //////////////////////////////////////////////////////////////////////////
            MCU_FF60_COMMON_INST_EN = 0x46;
            MCU_FF61_COMMON_OP_CODE = ucRDIDOPCode;
            MCU_FF60_COMMON_INST_EN = 0x47;
            pucIDArry[0] = MCU_FF67_COMMON_INST_READ_PORT0;
            pucIDArry[1] = MCU_FF68_COMMON_INST_READ_PORT1;
            pucIDArry[2] = MCU_FF69_COMMON_INST_READ_PORT2;

            // Repeatedly read flash ID code and check flash ID code data between twice RDID instructions
            for(ucIndex = 0; ucIndex < ucTryCount; ucIndex++)
            {
                MCU_FF60_COMMON_INST_EN = 0x46;
                MCU_FF61_COMMON_OP_CODE = ucRDIDOPCode;
                MCU_FF60_COMMON_INST_EN = 0x47;
                ucID0 = MCU_FF67_COMMON_INST_READ_PORT0;
                ucID1 = MCU_FF68_COMMON_INST_READ_PORT1;
                ucID2 = MCU_FF69_COMMON_INST_READ_PORT2;

                if((pucIDArry[0] == ucID0) && (pucIDArry[1] == ucID1) && (pucIDArry[2] == ucID2))
                {
                    break;
                }
                else
                {
                    pucIDArry[0] = ucID0;
                    pucIDArry[1] = ucID1;
                    pucIDArry[2] = ucID2;
                }
            }

            if(ucIndex >= ucTryCount)
            {
                return _FALSE;
            }

            break;

        case 0x90:
        case 0xAB:

            //////////////////////////////////////////////////////////////////////////////////
            // Use RDID(0x90/0xAB) Instruction first to get Flash Manufacture ID, Device ID //
            //////////////////////////////////////////////////////////////////////////////////
            MCU_FF60_COMMON_INST_EN = 0x5E;
            MCU_FF61_COMMON_OP_CODE = ucRDIDOPCode;
            MCU_FF64_FLASH_PROG_ISP0 = 0x00;
            MCU_FF65_FLASH_PROG_ISP1 = 0x00;
            MCU_FF66_FLASH_PROG_ISP2 = 0x00;
            MCU_FF60_COMMON_INST_EN = 0x5F;

            pucIDArry[0] = MCU_FF67_COMMON_INST_READ_PORT0;
            pucIDArry[1] = MCU_FF68_COMMON_INST_READ_PORT1;
            pucIDArry[2] = MCU_FF69_COMMON_INST_READ_PORT2;

            for(ucIndex = 0; ucIndex < ucTryCount; ucIndex++)
            {
                MCU_FF60_COMMON_INST_EN = 0x5E;
                MCU_FF61_COMMON_OP_CODE = ucRDIDOPCode;
                MCU_FF64_FLASH_PROG_ISP0 = 0x00;
                MCU_FF65_FLASH_PROG_ISP1 = 0x00;
                MCU_FF66_FLASH_PROG_ISP2 = 0x00;
                MCU_FF60_COMMON_INST_EN = 0x5F;

                ucID0 = MCU_FF67_COMMON_INST_READ_PORT0;
                ucID1 = MCU_FF68_COMMON_INST_READ_PORT1;
                ucID2 = MCU_FF69_COMMON_INST_READ_PORT2;

                if((pucIDArry[0] == ucID0) && (pucIDArry[1] == ucID1) && (pucIDArry[2] == ucID2))
                {
                    break;
                }
                else
                {
                    pucIDArry[0] = ucID0;
                    pucIDArry[1] = ucID1;
                    pucIDArry[2] = ucID2;
                }
            }

            if(ucIndex >= ucTryCount)
            {
                return _FALSE;
            }

            break;

        default:
            break;
    }

    return _TRUE;
}

#if(_FLASH_ACCESS_FUNCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Write enable process for serial flash
// Input Value  : ucBank: bank index
//                ucPage: page index (0 ~ 15)
// Output Value : Return _TURE if succeed, else return _FALSE
//--------------------------------------------------
void ScalerFlashWREN(BYTE ucBank, BYTE ucPage)
{
    BYTE ucWRSR = 0x00;
    BYTE ucWRSR1 = 0x00;

    // Clear watch dog
    MCU_FFEA_WATCHDOG_TIMER |= 0x40;

    switch(g_ucFlashType)
    {
        case _FLASH_PM25LV020:
        case _FLASH_PM25LD020:
        case _FLASH_PM25LQ020A:
        case _FLASH_PM25LQ080C:
        case _FLASH_PM25LQ016:

            // Unprotect Enable
            MCU_FF60_COMMON_INST_EN = 0x78;
            MCU_FF61_COMMON_OP_CODE = tFlashInformation[g_ucFlashType].ucWRENOpCode;
            MCU_FF64_FLASH_PROG_ISP0 = ucBank;
            MCU_FF65_FLASH_PROG_ISP1 = (BYTE)((ucPage << 4) & 0xF0);
            MCU_FF66_FLASH_PROG_ISP2 = 0x00;
            MCU_FF60_COMMON_INST_EN = MCU_FF60_COMMON_INST_EN | _BIT0;
            break;

        case _FLASH_W25X20A:
            switch(ucBank)
            {
                case 0:
                case 1:
                    ucWRSR = 0x0A;
                    break;

                case 2:
                case 3:
                    ucWRSR = 0x2A;
                    break;

                default:
                    ucWRSR = 0x02;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_FM25F04:
            switch(ucBank)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                    ucWRSR = 0x02;
                    break;

                case 4:
                case 5:
                    ucWRSR = 0x1A;
                    break;

                case 6:
                    ucWRSR = 0x16;
                    break;

                case 7:
                    ucWRSR = 0x12;
                    break;

                default:
                    ucWRSR = 0x02;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_N25S40:
            switch(ucBank)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                    ucWRSR = 0x0E;
                    break;

                case 4:
                case 5:
                    ucWRSR = 0x3A;
                    break;

                case 6:
                    ucWRSR = 0x36;
                    break;

                case 7:
                    ucWRSR = 0x32;
                    break;

                default:
                    ucWRSR = 0x02;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_MX25L2025:
            switch(ucBank)
            {
                case 0:
                case 1:
                    ucWRSR = 0x0A;
                    break;

                case 2:
                    ucWRSR = 0x06;
                    break;

                case 3:
                    ucWRSR = 0x02;
                    break;

                default:
                    ucWRSR = 0x02;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_MX25L4006E:
        case _FLASH_A25L040:
            switch(ucBank)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                    ucWRSR = 0x0E;
                    break;
                case 4:
                case 5:
                    ucWRSR = 0x0A;
                    break;
                case 6:
                    ucWRSR = 0x06;
                    break;
                case 7:
                    ucWRSR = 0x02;
                    break;
                default:
                    ucWRSR = 0x02;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_W25Q80BV:
            switch(ucBank)
            {
                case 0:
                    if(ucPage == 0)
                    {
                        ucWRSR = 0x66;
                    }
                    else if(ucPage == 1)
                    {
                        ucWRSR = 0x6A;
                    }
                    else if((ucPage == 2) || (ucPage == 3))
                    {
                        ucWRSR = 0x6E;
                    }
                    else if((ucPage >= 4) && (ucPage <= 7))
                    {
                        ucWRSR = 0x72;
                    }
                    else
                    {
                        ucWRSR = 0x26;
                    }
                    ucWRSR1 = 0x40;
                    break;

                case 1:
                    ucWRSR = 0x2A;
                    ucWRSR1 = 0x40;
                    break;

                case 2:
                case 3:
                    ucWRSR = 0x2E;
                    ucWRSR1 = 0x40;
                    break;

                case 4:
                case 5:
                case 6:
                case 7:
                    ucWRSR = 0x32;
                    ucWRSR1 = 0x40;
                    break;

                case 8:
                case 9:
                case 10:
                case 11:
                    ucWRSR = 0x12;
                    ucWRSR1 = 0x40;
                    break;

                case 12:
                case 13:
                    ucWRSR = 0x0E;
                    ucWRSR1 = 0x40;
                    break;

                case 14:
                    ucWRSR = 0x0A;
                    ucWRSR1 = 0x40;
                    break;

                case 15:
                    if(ucPage == 15)
                    {
                        ucWRSR = 0x46;
                    }
                    else if(ucPage == 14)
                    {
                        ucWRSR = 0x4A;
                    }
                    else if((ucPage == 12) || (ucPage == 13))
                    {
                        ucWRSR = 0x4E;
                    }
                    else if((ucPage >= 8) && (ucPage <= 11))
                    {
                        ucWRSR = 0x52;
                    }
                    else
                    {
                        ucWRSR = 0x06;
                    }
                    ucWRSR1 = 0x40;
                    break;

                default:
                    ucWRSR = 0x02;
                    ucWRSR1 = 0x00;
                    break;
            }
            // Set unprotect status register
            ScalerFlashSet2ByteWRSR(ucWRSR, ucWRSR1, _FALSE);
            break;

        case _FLASH_EN25F20:
            switch(ucBank)
            {
                case 0:
                case 1:
                    ucWRSR = 0x0A;
                    break;

                case 2:
                    ucWRSR = 0x06;
                    break;

                case 3:
                    if((ucPage == 12) || (ucPage == 13))
                    {
                        ucWRSR = 0x16;
                    }
                    else if((ucPage == 14) || (ucPage == 15))
                    {
                        ucWRSR = 0x1A;
                    }
                    else
                    {
                        ucWRSR = 0x12;
                    }
                    break;

                default:
                    ucWRSR = 0x02;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_W25X21CL:
            switch(ucBank)
            {
                case 0:
                case 1:
                case 2:
                    ucWRSR = 0x3E;
                    break;

                case 3:
                    if(ucPage < 10)
                    {
                        ucWRSR = 0x3E;
                    }
                    else if((ucPage >= 10) && (ucPage <= 11))
                    {
                        ucWRSR = 0x5E;
                    }
                    else if((ucPage >= 12) && (ucPage <= 13))
                    {
                        ucWRSR = 0x6E;
                    }
                    else if(ucPage == 14)
                    {
                        ucWRSR = 0x76;
                    }
                    else if(ucPage == 15)
                    {
                        ucWRSR = 0x7A;
                    }
                    break;

                default:
                    ucWRSR = 0x02;
                    break;
            }

            // Use general unprotect if BP4(bit6) do not need unlock, else use burst write to unlock BP4
            if((ucWRSR & _BIT6) == _BIT6)
            {
                // Set SRWD = 0
                ScalerFlashSetWRSR(ucWRSR & 0x7F, _FALSE);
                // Set unprotect register
                ScalerFlashSetWRSR(ucWRSR, _FALSE);
            }
            else
            {
                // Special unprotect area is not supported
            }
            break;

        case _FLASH_MX25L2026:
            switch(ucBank)
            {
                case 0:
                case 1:
                case 2:
                    ucWRSR = 0x3E;
                    break;

                case 3:
                    if(ucPage < 10)
                    {
                        ucWRSR = 0x3E;
                    }
                    else if((ucPage >= 10) && (ucPage <= 11))
                    {
                        ucWRSR = 0x5E;
                    }
                    else if((ucPage >= 12) && (ucPage <= 13))
                    {
                        ucWRSR = 0x6E;
                    }
                    else if(ucPage == 14)
                    {
                        ucWRSR = 0x76;
                    }
                    else if(ucPage == 15)
                    {
                        ucWRSR = 0x7A;
                    }
                    break;

                default:
                    ucWRSR = 0x02;
                    break;
            }

            // Use general unprotect if BP4(bit6) do not need unlock, else use burst write to unlock BP4
            if((ucWRSR & _BIT6) == _BIT6)
            {
                // Set SRWD = 0
                ScalerFlashSetWRSR(ucWRSR & 0x7F, _FALSE);
                // Set unprotect register
                ScalerFlashSetWRSR(ucWRSR, _FALSE);
            }
            else
            {
                // Special unprotect area is not supported
            }
            break;

        case _FLASH_MX25L4026D:
            switch(ucBank)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                    ucWRSR = 0x3E;
                    break;

                case 7:
                    if(ucPage < 10)
                    {
                        ucWRSR = 0x3E;
                    }
                    else if((ucPage >= 10) && (ucPage <= 11))
                    {
                        ucWRSR = 0x5E;
                    }
                    else if((ucPage >= 12) && (ucPage <= 13))
                    {
                        ucWRSR = 0x6E;
                    }
                    else if(ucPage == 14)
                    {
                        ucWRSR = 0x76;
                    }
                    else if(ucPage == 15)
                    {
                        ucWRSR = 0x7A;
                    }
                    break;

                default:
                    ucWRSR = 0x02;
                    break;
            }

            // Use general unprotect if BP4(bit6) do not need unlock, else use burst write to unlock BP4
            if((ucWRSR & _BIT6) == _BIT6)
            {
                // Set SRWD = 0
                ScalerFlashSetWRSR(ucWRSR & 0x7F, _FALSE);
                // Set unprotect register
                ScalerFlashSetWRSR(ucWRSR, _FALSE);
            }
            else
            {
                // Special unprotect area is not supported
            }
            break;

        case _FLASH_SST25LF020A:
            ScalerFlashSetWRSR(tFlashInformation[g_ucFlashType].ucUnprotectWRSR, _FALSE);
            break;

        case _FLASH_W25X41CL:
            if((ucBank < 7) || ((ucBank == 7) && (ucPage < 10)))
            {
                ucWRSR = 0x3E;
            }
            else if(ucBank == 7)
            {
                if((ucPage >= 10) && (ucPage <= 11))
                {
                    ucWRSR = 0x5E;
                }
                else if((ucPage >= 12) && (ucPage <= 13))
                {
                    ucWRSR = 0x6E;
                }
                else if(ucPage == 14)
                {
                    ucWRSR = 0x76;
                }
                else if(ucPage == 15)
                {
                    ucWRSR = 0x7A;
                }
            }
            else
            {
                ucWRSR = 0x02;
            }

            // Use general unprotect if BP4(bit6) do not need unlock, else use burst write to unlock BP4
            if((ucWRSR & _BIT6) == _BIT6)
            {
                // Set SRWD = 0
                ScalerFlashSetWRSR(ucWRSR & 0x7F, _FALSE);
                // Set unprotect register
                ScalerFlashSetWRSR(ucWRSR, _FALSE);
            }
            else
            {
                // Special unprotect area is not supported
            }
            break;

        case _FLASH_W25X40CL:
            switch(ucBank)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                    ucWRSR = 0x0E;
                    break;

                case 4:
                case 5:
                case 6:
                case 7:
                    ucWRSR = 0x2E;
                    break;

                default:
                    ucWRSR = 0x02;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_MX25L1606E:
        case _FLASH_MX25L1633E:
            switch(ucBank)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    // Protect Bank 16~31
                    ucWRSR = 0x16;
                    break;

                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                    // Protect Bank 0~15
                    ucWRSR = 0x2A;
                    break;

                case 24:
                case 25:
                case 26:
                case 27:
                    // Protect Bank 0~23
                    ucWRSR = 0x2E;
                    break;

                case 28:
                case 29:
                    // Protect Bank 0~27
                    ucWRSR = 0x32;
                    break;

                case 30:
                    // Protect Bank 0~29
                    ucWRSR = 0x36;
                    break;

                case 31:
                    // Protect Bank 0~30
                    ucWRSR = 0x3A;
                    break;

                default:
                    ucWRSR = 0x02;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_MX25L3206E:
            switch(ucBank)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                case 24:
                case 25:
                case 26:
                case 27:
                case 28:
                case 29:
                case 30:
                case 31:
                    // Protect Bank 32~63
                    ucWRSR = 0x1A;
                    break;

                case 32:
                case 33:
                case 34:
                case 35:
                case 36:
                case 37:
                case 38:
                case 39:
                case 40:
                case 41:
                case 42:
                case 43:
                case 44:
                case 45:
                case 46:
                case 47:
                    // Protect Bank 0~31
                    ucWRSR = 0x26;
                    break;

                case 48:
                case 49:
                case 50:
                case 51:
                case 52:
                case 53:
                case 54:
                case 55:
                    // Protect Bank 0~47
                    ucWRSR = 0x2A;
                    break;

                case 56:
                case 57:
                case 58:
                case 59:
                    // Protect Bank 0~55
                    ucWRSR = 0x2E;
                    break;

                case 60:
                case 61:
                    // Protect Bank 0~59
                    ucWRSR = 0x32;
                    break;

                case 62:
                    // Protect Bank 0~61
                    ucWRSR = 0x36;
                    break;

                case 63:
                    // Protect Bank 0~62
                    ucWRSR = 0x3A;
                    break;

                default:
                    ucWRSR = 0x02;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_A25L016:
            switch(ucBank)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    // Protect Bank 16~31
                    ucWRSR = 0x16;
                    break;

                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                    // Protect Bank 24~31
                    ucWRSR = 0x12;
                    break;

                case 24:
                case 25:
                case 26:
                case 27:
                    // Protect Bank 28~31
                    ucWRSR = 0x0E;
                    break;

                case 28:
                case 29:
                    // Protect Bank 30~31
                    ucWRSR = 0x0A;
                    break;

                case 30:
                    // Protect Bank 31
                    ucWRSR = 0x06;
                    break;

                case 31:
                    // Protect Bank None
                    ucWRSR = 0x02;
                    break;

                default:
                    ucWRSR = 0x02;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_W25Q16DV:
        case _FLASH_GD25Q16C:
            switch(ucBank)
            {
                case 0:
                    if(ucPage == 0)
                    {
                        // Protect Sector 1~511
                        ucWRSR = 0x66;
                    }
                    else if(ucPage == 1)
                    {
                        // Protect Sector 2~511
                        ucWRSR = 0x6A;
                    }
                    else if((ucPage == 2) || (ucPage == 3))
                    {
                        // Protect Sector 4~511
                        ucWRSR = 0x6E;
                    }
                    else if((ucPage >= 4) && (ucPage <= 7))
                    {
                        // Protect Sector 8~511
                        ucWRSR = 0x72;
                    }
                    else
                    {
                        // Protect Sector 16~511
                        ucWRSR = 0x26;
                    }
                    ucWRSR1 = 0x40;
                    break;

                case 1:
                    // Protect Bank 2~31
                    ucWRSR = 0x2A;
                    ucWRSR1 = 0x40;
                    break;

                case 2:
                case 3:
                    // Protect Bank 4~31
                    ucWRSR = 0x2E;
                    ucWRSR1 = 0x40;
                    break;

                case 4:
                case 5:
                case 6:
                case 7:
                    // Protect Bank 8~31
                    ucWRSR = 0x32;
                    ucWRSR1 = 0x40;
                    break;

                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    // Protect Bank 16~31
                    ucWRSR = 0x36;
                    ucWRSR1 = 0x40;
                    break;

                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                    // Protect Bank 0~15
                    ucWRSR = 0x16;
                    ucWRSR1 = 0x40;
                    break;

                case 24:
                case 25:
                case 26:
                case 27:
                    // Protect Bank 0~23
                    ucWRSR = 0x12;
                    ucWRSR1 = 0x40;
                    break;

                case 28:
                case 29:
                    // Protect Bank 0~27
                    ucWRSR = 0x0E;
                    ucWRSR1 = 0x40;
                    break;

                case 30:
                    // Protect Bank 0~29
                    ucWRSR = 0x0A;
                    ucWRSR1 = 0x40;
                    break;

                case 31:
                    if(ucPage == 15)
                    {
                        // Protect Sector 0~510
                        ucWRSR = 0x46;
                    }
                    else if(ucPage == 14)
                    {
                        // Protect Sector 0~509
                        ucWRSR = 0x4A;
                    }
                    else if((ucPage == 12) || (ucPage == 13))
                    {
                        // Protect Sector 0~507
                        ucWRSR = 0x4E;
                    }
                    else if((ucPage >= 8) && (ucPage <= 11))
                    {
                        // Protect Sector 0~503
                        ucWRSR = 0x52;
                    }
                    else
                    {
                        // Protect Sector 0~495
                        ucWRSR = 0x06;
                    }
                    ucWRSR1 = 0x40;
                    break;

                default:
                    ucWRSR = 0x02;
                    ucWRSR1 = 0x00;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSet2ByteWRSR(ucWRSR, ucWRSR1, _FALSE);
            break;

        case _FLASH_A25L032:
        case _FLASH_W25Q32F:
            switch(ucBank)
            {
                case 0:
                    if(ucPage == 0)
                    {
                        ucWRSR = 0x66;
                    }
                    else if(ucPage == 1)
                    {
                        ucWRSR = 0x6A;
                    }
                    else if((ucPage == 2) || (ucPage == 3))
                    {
                        ucWRSR = 0x6E;
                    }
                    else if((ucPage >= 4) && (ucPage <= 7))
                    {
                        ucWRSR = 0x72;
                    }
                    else
                    {
                        // Protect Bank 1~63
                        ucWRSR = 0x26;
                    }
                    ucWRSR1 = 0x40;
                    break;

                case 1:
                    // Protect Bank 2~63
                    ucWRSR = 0x2A;
                    ucWRSR1 = 0x40;
                    break;

                case 2:
                case 3:
                    // Protect Bank 4~63
                    ucWRSR = 0x2E;
                    ucWRSR1 = 0x40;
                    break;

                case 4:
                case 5:
                case 6:
                case 7:
                    // Protect Bank 8~63
                    ucWRSR = 0x32;
                    ucWRSR1 = 0x40;
                    break;

                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    // Protect Bank 16~63
                    ucWRSR = 0x36;
                    ucWRSR1 = 0x40;
                    break;

                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                case 24:
                case 25:
                case 26:
                case 27:
                case 28:
                case 29:
                case 30:
                case 31:
                    // Protect Bank 32~63
                    ucWRSR = 0x3A;
                    ucWRSR1 = 0x40;
                    break;

                case 32:
                case 33:
                case 34:
                case 35:
                case 36:
                case 37:
                case 38:
                case 39:
                case 40:
                case 41:
                case 42:
                case 43:
                case 44:
                case 45:
                case 46:
                case 47:
                    // Protect Bank 0~31
                    ucWRSR = 0x1A;
                    ucWRSR1 = 0x40;
                    break;

                case 48:
                case 49:
                case 50:
                case 51:
                case 52:
                case 53:
                case 54:
                case 55:
                    // Protect Bank 0~47
                    ucWRSR = 0x16;
                    ucWRSR1 = 0x40;
                    break;

                case 56:
                case 57:
                case 58:
                case 59:
                    // Protect Bank 0~55
                    ucWRSR = 0x12;
                    ucWRSR1 = 0x40;
                    break;

                case 60:
                case 61:
                    // Protect Bank 0~59
                    ucWRSR = 0x0E;
                    ucWRSR1 = 0x40;
                    break;

                case 62:
                    // Protect Bank 0~61
                    ucWRSR = 0x0A;
                    ucWRSR1 = 0x40;
                    break;

                case 63:
                    if(ucPage == 15)
                    {
                        ucWRSR = 0x46;
                    }
                    else if(ucPage == 14)
                    {
                        ucWRSR = 0x4A;
                    }
                    else if((ucPage == 12) || (ucPage == 13))
                    {
                        ucWRSR = 0x4E;
                    }
                    else if((ucPage >= 8) && (ucPage <= 11))
                    {
                        ucWRSR = 0x52;
                    }
                    else
                    {
                        // Protect Bank 0~62
                        ucWRSR = 0x06;
                    }
                    ucWRSR1 = 0x40;
                    break;

                default:
                    ucWRSR = 0x02;
                    ucWRSR1 = 0x00;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSet2ByteWRSR(ucWRSR, ucWRSR1, _FALSE);
            break;

        case _FLASH_GD25Q16:
            switch(ucBank)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    // Protect Bank 16~31
                    ucWRSR = 0x16;
                    break;

                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                case 24:
                case 25:
                case 26:
                case 27:
                case 28:
                case 29:
                case 30:
                case 31:
                    // Protect Bank 0~15
                    ucWRSR = 0x36;
                    break;

                default:
                    ucWRSR = 0x02;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;


        case _FLASH_MX25L8006E:
        case _FLASH_MX25R8035F:
            switch(ucBank)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                    // Protect Bank 8~15
                    ucWRSR = 0x12;
                    break;
                case 8:
                case 9:
                case 10:
                case 11:
                    // Protect Bank 12~15
                    ucWRSR = 0x0E;
                    break;
                case 12:
                case 13:
                    // Protect Bank 14~15
                    ucWRSR = 0x0A;
                    break;
                case 14:
                    // Protect Bank 15
                    ucWRSR = 0x06;
                    break;
                case 15:
                    // Protect Bank None
                    ucWRSR = 0x02;
                    break;
                default:
                    ucWRSR = 0x02;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_MX25L3233F:
            switch(ucBank)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                case 24:
                case 25:
                case 26:
                case 27:
                case 28:
                case 29:
                case 30:
                case 31:
                    // Protect Bank 32~63
                    ucWRSR = 0x1A;
                    break;

                case 32:
                case 33:
                case 34:
                case 35:
                case 36:
                case 37:
                case 38:
                case 39:
                case 40:
                case 41:
                case 42:
                case 43:
                case 44:
                case 45:
                case 46:
                case 47:
                    // Protect Bank 48~63
                    ucWRSR = 0x16;
                    break;

                case 48:
                case 49:
                case 50:
                case 51:
                case 52:
                case 53:
                case 54:
                case 55:
                    // Protect Bank 56~63
                    ucWRSR = 0x12;
                    break;

                case 56:
                case 57:
                case 58:
                case 59:
                    // Protect Bank 60~63
                    ucWRSR = 0x0E;
                    break;

                case 60:
                case 61:
                    // Protect Bank 62~63
                    ucWRSR = 0x0A;
                    break;

                case 62:
                    // Protect Bank 63
                    ucWRSR = 0x06;
                    break;

                default:
                    ucWRSR = 0x02;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_EN25QH32A:
            if((ucBank >= 0) && (ucBank <= 31))
            {
                // Protect Bank 32~63
                ucWRSR = 0x5A;
            }
            else if((ucBank >= 32) && (ucBank <= 63))
            {
                // Protect Bank 0~31
                ucWRSR = 0x7A;
            }
            else
            {
                ucWRSR = 0x42;
            }
            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_MX25V1635F:
            switch(ucBank)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    // Protect Bank 16~31
                    ucWRSR = 0x16;
                    break;

                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                    // Protect Bank 0~15
                    ucWRSR = 0x2A;
                    break;

                case 24:
                case 25:
                case 26:
                case 27:
                    // Protect Bank 0~23
                    ucWRSR = 0x2E;
                    break;

                case 28:
                case 29:
                    // Protect Bank 0~27
                    ucWRSR = 0x32;
                    break;

                case 30:
                    // Protect Bank 0~29
                    ucWRSR = 0x36;
                    break;

                case 31:
                    // Protect Bank 0~30
                    ucWRSR = 0x3A;
                    break;

                default:
                    ucWRSR = 0x02;
                    break;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_AT25SF041:
            switch(ucBank)
            {
                case 0:
                    // Protect Bank 1~7
                    ucWRSR = 0x26;
                    ucWRSR1 = 0x40;
                    break;

                case 1:
                    // Protect Bank 2~7
                    ucWRSR = 0x02A;
                    ucWRSR1 = 0x40;
                    break;

                case 2:
                case 3:
                    // Protect Bank 4~7
                    ucWRSR = 0x02E;
                    ucWRSR1 = 0x40;
                    break;

                case 4:
                case 5:
                    // Protect Bank 0~3
                    ucWRSR = 0x0E;
                    ucWRSR1 = 0x40;
                    break;

                case 6:
                    // Protect Bank 0~5
                    ucWRSR = 0x0A;
                    ucWRSR1 = 0x40;
                    break;

                case 7:
                    // Protect Bank 0~6
                    ucWRSR = 0x06;
                    ucWRSR1 = 0x40;
                    break;

                default:
                    ucWRSR = 0x02;
                    ucWRSR1 = 0x00;
                    break;
            }
            // Set unprotect status register
            ScalerFlashSet2ByteWRSR(ucWRSR, ucWRSR1, _FALSE);
            break;

        case _FLASH_MX25L6433F:
            if((ucBank >= 0) && (ucBank <= 63))
            {
                // Protect Bank 64~127
                ucWRSR = 0x1E;
            }
            else if((ucBank >= 64) && (ucBank <= 95))
            {
                // Protect Bank 96~127
                ucWRSR = 0x1A;
            }
            else if((ucBank >= 96) && (ucBank <= 111))
            {
                // Protect Bank 112~127
                ucWRSR = 0x26;
            }
            else if((ucBank >= 112) && (ucBank <= 119))
            {
                // Protect Bank 120~127
                ucWRSR = 0x12;
            }
            else if((ucBank >= 120) && (ucBank <= 123))
            {
                // Protect Bank 124~127
                ucWRSR = 0x0E;
            }
            else if((ucBank >= 124) && (ucBank <= 125))
            {
                // Protect Bank 126~127
                ucWRSR = 0x0A;
            }
            else if(ucBank == 126)
            {
                // Protect Bank 127
                ucWRSR = 0x06;
            }
            else
            {
                ucWRSR = 0x02;
            }

            // Set unprotect status register
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;

        case _FLASH_GD25Q32C:
            switch(ucBank)
            {
                case 0:
                    if(ucPage == 0)
                    {
                        ucWRSR = 0x66;
                    }
                    else if(ucPage == 1)
                    {
                        ucWRSR = 0x6A;
                    }
                    else if((ucPage == 2) || (ucPage == 3))
                    {
                        ucWRSR = 0x6E;
                    }
                    else if((ucPage >= 4) && (ucPage <= 7))
                    {
                        ucWRSR = 0x72;
                    }
                    else
                    {
                        // Protect Bank 1~63
                        ucWRSR = 0x26;
                    }
                    ucWRSR1 = 0x40;
                    break;

                case 1:
                    // Protect Bank 2~63
                    ucWRSR = 0x2A;
                    ucWRSR1 = 0x40;
                    break;

                case 2:
                case 3:
                    // Protect Bank 4~63
                    ucWRSR = 0x2E;
                    ucWRSR1 = 0x40;
                    break;

                case 4:
                case 5:
                case 6:
                case 7:
                    // Protect Bank 8~63
                    ucWRSR = 0x32;
                    ucWRSR1 = 0x40;
                    break;

                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    // Protect Bank 16~63
                    ucWRSR = 0x36;
                    ucWRSR1 = 0x40;
                    break;

                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                case 24:
                case 25:
                case 26:
                case 27:
                case 28:
                case 29:
                case 30:
                case 31:
                    // Protect Bank 32~63
                    ucWRSR = 0x3A;
                    ucWRSR1 = 0x40;
                    break;

                case 32:
                case 33:
                case 34:
                case 35:
                case 36:
                case 37:
                case 38:
                case 39:
                case 40:
                case 41:
                case 42:
                case 43:
                case 44:
                case 45:
                case 46:
                case 47:
                    // Protect Bank 0~31
                    ucWRSR = 0x1A;
                    ucWRSR1 = 0x40;
                    break;

                case 48:
                case 49:
                case 50:
                case 51:
                case 52:
                case 53:
                case 54:
                case 55:
                    // Protect Bank 0~47
                    ucWRSR = 0x16;
                    ucWRSR1 = 0x40;
                    break;

                case 56:
                case 57:
                case 58:
                case 59:
                    // Protect Bank 0~55
                    ucWRSR = 0x12;
                    ucWRSR1 = 0x40;
                    break;

                case 60:
                case 61:
                    // Protect Bank 0~59
                    ucWRSR = 0x0E;
                    ucWRSR1 = 0x40;
                    break;

                case 62:
                    // Protect Bank 0~61
                    ucWRSR = 0x0A;
                    ucWRSR1 = 0x40;
                    break;

                case 63:
                    if(ucPage == 15)
                    {
                        ucWRSR = 0x46;
                    }
                    else if(ucPage == 14)
                    {
                        ucWRSR = 0x4A;
                    }
                    else if((ucPage == 12) || (ucPage == 13))
                    {
                        ucWRSR = 0x4E;
                    }
                    else if((ucPage >= 8) && (ucPage <= 11))
                    {
                        ucWRSR = 0x52;
                    }
                    else
                    {
                        // Protect Bank 0~62
                        ucWRSR = 0x06;
                    }
                    ucWRSR1 = 0x40;
                    break;

                default:
                    ucWRSR = 0x02;
                    ucWRSR1 = 0x00;
                    break;
            }

            // Set unprotect status register

            ScalerFlashSet2ByteWRSRonebyone(ucWRSR, ucWRSR1, _FALSE);
            break;

        default:
            ScalerFlashSetWRSR(ucWRSR, _FALSE);
            break;
    }

    // Program OP Code
    MCU_FF6D_PROGRAM_OP_CODE = 0x02;
    // Disable Command OP code
    MCU_FF61_COMMON_OP_CODE = 0xFF;
}

//--------------------------------------------------
// Description  : Write disable process for serial flash
// Input Value  : None
// Output Value : Return _TURE if succeed, else return _FALSE
//--------------------------------------------------
void ScalerFlashWRDis(void)
{
    // Clear watch dog
    MCU_FFEA_WATCHDOG_TIMER |= 0x40;

    switch(g_ucFlashType)
    {
        case _FLASH_PM25LV020:
        case _FLASH_PM25LD020:
        case _FLASH_PM25LQ020A:
        case _FLASH_PM25LQ080C:
            // Sector Unprotect Disable
            ScalerFlashSetWREN(tFlashInformation[g_ucFlashType].ucWRDisOpCode);
            break;

        case _FLASH_W25X20A:
        case _FLASH_MX25L2026:
        case _FLASH_EN25F20:
        case _FLASH_MX25L2025:
        case _FLASH_MX25L4006E:
        case _FLASH_W25X21CL:
        case _FLASH_W25X41CL:
        case _FLASH_FM25F04:
        case _FLASH_N25S40:
        case _FLASH_A25L040:
        case _FLASH_W25Q80BV:
        case _FLASH_MX25L4026D:
        case _FLASH_W25X40CL:
        case _FLASH_MX25L1606E:
        case _FLASH_MX25L3206E:
        case _FLASH_A25L016:
        case _FLASH_W25Q16DV:
        case _FLASH_A25L032:
        case _FLASH_GD25Q16:
        case _FLASH_MX25L1633E:
        case _FLASH_GD25Q16C:
        case _FLASH_MX25L3233F:
        case _FLASH_EN25QH32A:
        case _FLASH_MX25L8006E:
        case _FLASH_MX25V1635F:
        case _FLASH_AT25SF041:
        case _FLASH_MX25L6433F:
        case _FLASH_PM25LQ016:
        case _FLASH_MX25R8035F:
            ScalerFlashSetWRSR(tFlashInformation[g_ucFlashType].ucProtectWRSR, _FALSE);
            ScalerFlashSetWREN(tFlashInformation[g_ucFlashType].ucWRDisOpCode);
            break;

        case _FLASH_SST25LF020A:
            ScalerFlashSetWRSR(tFlashInformation[g_ucFlashType].ucProtectWRSR, _TRUE);
            ScalerFlashSetWREN(tFlashInformation[g_ucFlashType].ucWRDisOpCode);
            break;

        case _FLASH_W25Q32F:
            ScalerFlashSet2ByteWRSR(tFlashInformation[g_ucFlashType].ucProtectWRSR, 0x00, _FALSE);
            ScalerFlashSetWREN(tFlashInformation[g_ucFlashType].ucWRDisOpCode);
            break;

        case _FLASH_GD25Q32C:
            ScalerFlashSet2ByteWRSRonebyone(tFlashInformation[g_ucFlashType].ucProtectWRSR, 0x00, _FALSE);
            ScalerFlashSetWREN(tFlashInformation[g_ucFlashType].ucWRDisOpCode);
            break;

        default:
            ScalerFlashSetWRSR(0xFF, _FALSE);
            ScalerFlashSetWREN(0x04);
            break;
    }

    // Disable Program OP code
    MCU_FF6D_PROGRAM_OP_CODE = 0xFF;

    // Disable Command OP code
    MCU_FF61_COMMON_OP_CODE = 0xFF;
}
#endif

//--------------------------------------------------
// Description  : WREN instructions for serial flash
// Input Value  : ucOpCode: WREN instruction op code
// Output Value : None
//--------------------------------------------------
void ScalerFlashSetWREN(BYTE ucOpCode)
{
    // WREN instructions
    MCU_FF60_COMMON_INST_EN = 0x20;
    MCU_FF61_COMMON_OP_CODE = ucOpCode;
    MCU_FF60_COMMON_INST_EN = MCU_FF60_COMMON_INST_EN | _BIT0;

    // No need to polling, 8051 will halt when common instruction executes
}

//--------------------------------------------------
// Description  : WRSR instructions for Serial Flash
// Input Value  : ucWRSR: value written to Flash Status Reg
//                ucIsSST: _TRUE for SST Flash, _FALSE for other flash
// Output Value : None
//--------------------------------------------------
void ScalerFlashSetWRSR(BYTE ucWRSR, bit bIsSST)
{
    PCB_FLASH_WRITE_PROTECT(_FLASH_WRITE_PROTECT_DISABLE);

    // WRSR
    if(bIsSST == _TRUE)
    {
        MCU_FF60_COMMON_INST_EN = 0x88;
    }
    else
    {
        MCU_FF60_COMMON_INST_EN = 0x68;
    }

    MCU_FF61_COMMON_OP_CODE = 0x01;
    MCU_FF64_FLASH_PROG_ISP0 = ucWRSR;
    MCU_FF60_COMMON_INST_EN = MCU_FF60_COMMON_INST_EN | _BIT0;

    // No need to polling, 8051 will halt when common instruction executes

    // Disable Command OP code
    MCU_FF61_COMMON_OP_CODE = 0xFF;

    PCB_FLASH_WRITE_PROTECT(_FLASH_WRITE_PROTECT_ENABLE);
}

//--------------------------------------------------
// Description  : WRSR instructions for Serial Flash
// Input Value  : ucWRSR1: value written to Flash Status Register-1
//              : ucWRSR2: value written to Flash Status Register-2
//                ucIsSST: _TRUE for SST Flash, _FALSE for other flash
// Output Value : None
//--------------------------------------------------
void ScalerFlashSet2ByteWRSR(BYTE ucWRSR1, BYTE ucWRSR2, bit bIsSST)
{
    PCB_FLASH_WRITE_PROTECT(_FLASH_WRITE_PROTECT_DISABLE);

    // WRSR
    if(bIsSST == _TRUE)
    {
        MCU_FF60_COMMON_INST_EN = 0x90;
    }
    else
    {
        MCU_FF60_COMMON_INST_EN = 0x70;
    }

    MCU_FF61_COMMON_OP_CODE = 0x01;
    MCU_FF64_FLASH_PROG_ISP0 = ucWRSR1;
    MCU_FF65_FLASH_PROG_ISP1 = ucWRSR2;
    MCU_FF60_COMMON_INST_EN = MCU_FF60_COMMON_INST_EN | _BIT0;

    // No need to polling, 8051 will halt when common instruction executes

    // Disable Command OP code
    MCU_FF61_COMMON_OP_CODE = 0xFF;

    PCB_FLASH_WRITE_PROTECT(_FLASH_WRITE_PROTECT_ENABLE);
}

//--------------------------------------------------
// Description  : WRSR instructions on two SR one by one for Serial Flash
// Input Value  : ucWRSR1: value written to Flash Status Register-1
//              : ucWRSR2: value written to Flash Status Register-2
//                ucIsSST: _TRUE for SST Flash, _FALSE for other flash
// Output Value : None
//--------------------------------------------------
void ScalerFlashSet2ByteWRSRonebyone(BYTE ucWRSR1, BYTE ucWRSR2, bit bIsSST)
{
    PCB_FLASH_WRITE_PROTECT(_FLASH_WRITE_PROTECT_DISABLE);

    // WRSR
    if(bIsSST == _TRUE)
    {
        MCU_FF60_COMMON_INST_EN = 0x88;
    }
    else
    {
        MCU_FF60_COMMON_INST_EN = 0x68;
    }

    MCU_FF61_COMMON_OP_CODE = 0x01;
    MCU_FF64_FLASH_PROG_ISP0 = ucWRSR1;
    MCU_FF60_COMMON_INST_EN = MCU_FF60_COMMON_INST_EN | _BIT0;

    // No need to polling, 8051 will halt when common instruction executes

    if(bIsSST == _TRUE)
    {
        MCU_FF60_COMMON_INST_EN = 0x88;
    }
    else
    {
        MCU_FF60_COMMON_INST_EN = 0x68;
    }

    MCU_FF61_COMMON_OP_CODE = 0x31;
    MCU_FF64_FLASH_PROG_ISP0 = ucWRSR2;
    MCU_FF60_COMMON_INST_EN = MCU_FF60_COMMON_INST_EN | _BIT0;

    // No need to polling, 8051 will halt when common instruction executes

    // Disable Command OP code
    MCU_FF61_COMMON_OP_CODE = 0xFF;

    PCB_FLASH_WRITE_PROTECT(_FLASH_WRITE_PROTECT_ENABLE);
}

#if(_FLASH_ACCESS_FUNCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Erase page
// Input Value  : ucBank: bank index
//                ucPage: page index (0 ~ 15)
// Output Value : _TRUE for erase success and _FALSE for erase fail
//--------------------------------------------------
bit ScalerFlashErasePage(BYTE ucBank, BYTE ucPage)
{
    // The access bank is smaller than than the start bank
    if(ucBank < MCU_FFFD_XDATA_BANK_START)
    {
        return _FALSE;
    }

    if(g_ucFlashType == _FLASH_UNDETECT)
    {
        ScalerFlashDetectFlashType();
    }

    ScalerFlashWREN(ucBank, ucPage);

    // Sector Erase
    MCU_FF60_COMMON_INST_EN = 0xB8;
    MCU_FF61_COMMON_OP_CODE = tFlashInformation[g_ucFlashType].ucPageEraseOpCode;
    // Set WR address
    MCU_FF64_FLASH_PROG_ISP0 = ucBank;
    MCU_FF65_FLASH_PROG_ISP1 = (BYTE)((ucPage << 4) & 0xF0);
    MCU_FF66_FLASH_PROG_ISP2 = 0x00;
    // Start Bit0
    MCU_FF60_COMMON_INST_EN = MCU_FF60_COMMON_INST_EN | _BIT0;

    // No need to polling, 8051 will halt when common instruction executes

    MCU_FF61_COMMON_OP_CODE = 0xFF;

    ScalerFlashWRDis();

    return _TRUE;
}
#endif // End of #if(_FLASH_ACCESS_FUNCTION_SUPPORT == _ON)

#if(_FLASH_WR_PROTECT == _ON)
//--------------------------------------------------
// Description  : Set SR to protect flash
// Input Value  : None
// Output Value : Return _TURE if succeed, else return _FALSE
//--------------------------------------------------
void ScalerFlashWRProtect(void)
{
    BYTE ucRDSR = 0;

    // Clear watch dog
    MCU_FFEA_WATCHDOG_TIMER |= 0x40;

    // Detect flash type first
    if(g_ucFlashType == _FLASH_UNDETECT)
    {
        ScalerFlashDetectFlashType();
    }

    if((g_ucFlashType == _FLASH_PM25LV020) ||
       (g_ucFlashType == _FLASH_PM25LD020) ||
       (g_ucFlashType == _FLASH_PM25LQ020A) ||
       (g_ucFlashType == _FLASH_PM25LQ080C) ||
       (g_ucFlashType == _FLASH_W25X20A) ||
       (g_ucFlashType == _FLASH_MX25L2026) ||
       (g_ucFlashType == _FLASH_EN25F20) ||
       (g_ucFlashType == _FLASH_MX25L2025) ||
       (g_ucFlashType == _FLASH_MX25L4006E) ||
       (g_ucFlashType == _FLASH_W25X21CL) ||
       (g_ucFlashType == _FLASH_W25X41CL) ||
       (g_ucFlashType == _FLASH_FM25F04) ||
       (g_ucFlashType == _FLASH_N25S40) ||
       (g_ucFlashType == _FLASH_A25L040) ||
       (g_ucFlashType == _FLASH_W25Q80BV) ||
       (g_ucFlashType == _FLASH_MX25L4026D) ||
       (g_ucFlashType == _FLASH_W25X40CL) ||
       (g_ucFlashType == _FLASH_MX25L1606E) ||
       (g_ucFlashType == _FLASH_MX25L3206E) ||
       (g_ucFlashType == _FLASH_A25L016) ||
       (g_ucFlashType == _FLASH_W25Q16DV) ||
       (g_ucFlashType == _FLASH_A25L032) ||
       (g_ucFlashType == _FLASH_GD25Q16) ||
       (g_ucFlashType == _FLASH_MX25L1633E) ||
       (g_ucFlashType == _FLASH_GD25Q16C) ||
       (g_ucFlashType == _FLASH_MX25L3233F) ||
       (g_ucFlashType == _FLASH_EN25QH32A) ||
       (g_ucFlashType == _FLASH_MX25L8006E) ||
       (g_ucFlashType == _FLASH_MX25V1635F) ||
       (g_ucFlashType == _FLASH_AT25SF041) ||
       (g_ucFlashType == _FLASH_MX25L6433F) ||
       (g_ucFlashType == _FLASH_PM25LQ016) ||
       (g_ucFlashType == _FLASH_MX25R8035F))

    {
        // Read SR
        MCU_FF60_COMMON_INST_EN = 0x42;
        MCU_FF61_COMMON_OP_CODE = 0x05;
        MCU_FF60_COMMON_INST_EN = MCU_FF60_COMMON_INST_EN | _BIT0;
        ucRDSR = MCU_FF67_COMMON_INST_READ_PORT0;

        if(ucRDSR != tFlashInformation[g_ucFlashType].ucProtectWRSR)
        {
            ScalerFlashSetWRSR(tFlashInformation[g_ucFlashType].ucProtectWRSR, _FALSE);
            ScalerFlashSetWREN(tFlashInformation[g_ucFlashType].ucWRDisOpCode);
        }
    }
    else if(g_ucFlashType == _FLASH_SST25LF020A)
    {
        // Read SR
        MCU_FF60_COMMON_INST_EN = 0x42;
        MCU_FF61_COMMON_OP_CODE = 0x05;
        MCU_FF60_COMMON_INST_EN = MCU_FF60_COMMON_INST_EN | _BIT0;
        ucRDSR = MCU_FF67_COMMON_INST_READ_PORT0;

        if(ucRDSR != tFlashInformation[g_ucFlashType].ucProtectWRSR)
        {
            ScalerFlashSetWRSR(tFlashInformation[g_ucFlashType].ucProtectWRSR, _TRUE);
            ScalerFlashSetWREN(tFlashInformation[g_ucFlashType].ucWRDisOpCode);
        }
    }
    else if(g_ucFlashType == _FLASH_W25Q32F)
    {
        // Read SR
        MCU_FF60_COMMON_INST_EN = 0x42;
        MCU_FF61_COMMON_OP_CODE = 0x05;
        MCU_FF60_COMMON_INST_EN = MCU_FF60_COMMON_INST_EN | _BIT0;
        ucRDSR = MCU_FF67_COMMON_INST_READ_PORT0;

        if(ucRDSR != tFlashInformation[g_ucFlashType].ucProtectWRSR)
        {
            ScalerFlashSet2ByteWRSR(tFlashInformation[g_ucFlashType].ucProtectWRSR, 0x00, _FALSE);
            ScalerFlashSetWREN(tFlashInformation[g_ucFlashType].ucWRDisOpCode);
        }
    }
    else if(g_ucFlashType == _FLASH_GD25Q32C)
    {
        // Read SR
        MCU_FF60_COMMON_INST_EN = 0x42;
        MCU_FF61_COMMON_OP_CODE = 0x05;
        MCU_FF60_COMMON_INST_EN = MCU_FF60_COMMON_INST_EN | _BIT0;
        ucRDSR = MCU_FF67_COMMON_INST_READ_PORT0;

        if(ucRDSR != tFlashInformation[g_ucFlashType].ucProtectWRSR)
        {
            ScalerFlashSet2ByteWRSRonebyone(tFlashInformation[g_ucFlashType].ucProtectWRSR, 0x00, _FALSE);
            ScalerFlashSetWREN(tFlashInformation[g_ucFlashType].ucWRDisOpCode);
        }
    }
    else
    {
        // Read SR
        MCU_FF60_COMMON_INST_EN = 0x42;
        MCU_FF61_COMMON_OP_CODE = 0x05;
        MCU_FF60_COMMON_INST_EN = MCU_FF60_COMMON_INST_EN | _BIT0;
        ucRDSR = MCU_FF67_COMMON_INST_READ_PORT0;

        if(ucRDSR != 0xFF)
        {
            ScalerFlashSetWRSR(0xFF, _FALSE);
            ScalerFlashSetWREN(0x04);
        }
    }

    // Disable Program OP code
    MCU_FF6D_PROGRAM_OP_CODE = 0xFF;

    // Disable Command OP code
    MCU_FF61_COMMON_OP_CODE = 0xFF;
}

#endif // End of #if(_FLASH_WR_PROTECT ==_ON)
#endif // End of #if((_FLASH_ACCESS_FUNCTION_SUPPORT == _ON) || (_FLASH_WR_PROTECT ==_ON))
