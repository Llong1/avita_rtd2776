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
// ID Code      : RTD2014UserBoot.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_BOOT__

#include "UserCommonInclude.h"

#if(_FLASH_PARTITION_TYPE != _FLASH_PARTITION_NONE)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _FLASH_PARTITION_BOOTTABLE_BANK                          (0x10)
#define _FLASH_PARTITION_BOOTTABLE_ADDRESS                       ((volatile BYTE xdata *)0xF8FE)
#define _FLASH_PARTITION_BOOTTABLE_DATA                          0xAA, 0x55


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************
BYTE code tFLASH_PARTITION_BOOTTABLE[] =
{
    _FLASH_PARTITION_BOOTTABLE_DATA
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_FLASH_PARTITION_TYPE == _FLASH_PARTITION_BOOT)
BYTE UserInterfaceGetUserCodeLocation(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_FLASH_PARTITION_TYPE == _FLASH_PARTITION_BOOT)
//--------------------------------------------------
// Description  : Check boot/user code status
// Input Value  : None
// Output Value : Bank number of user code
//--------------------------------------------------
BYTE UserInterfaceGetUserCodeLocation(void)
{
    // Select XDATA BANK start
    MCU_FFFD_XDATA_BANK_START = 0x00;

    // Select 32th bank for XDATA access
    MCU_FFFE_XDATA_BANK_SEL = _FLASH_PARTITION_BOOTTABLE_BANK;

    // Check user-defined user/boot code id
    if(memcmp((volatile BYTE xdata *)_FLASH_PARTITION_BOOTTABLE_ADDRESS,
              tFLASH_PARTITION_BOOTTABLE,
              sizeof(tFLASH_PARTITION_BOOTTABLE)) == 0)
    {
#if(_FLASH_PARTITION_RELOCATABLE_SUPPORT == _ON)
        // Set bank offset for user code
        SET_BANK_SWITCH_OFFSET(_FLASH_PARTITION_BOOTTABLE_BANK);
#endif

        // Check success; return user bank address
        return _FLASH_PARTITION_BOOTTABLE_BANK;
    }

    // Check fail; return init bank
    return _FLASH_PARTITION_INIT_BANK;
}
#endif

#endif // End of #if(_FLASH_PARTITION_TYPE != _FLASH_PARTITION_NONE)

