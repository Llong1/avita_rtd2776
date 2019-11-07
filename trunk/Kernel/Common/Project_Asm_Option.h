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
// ID Code      : Project_Asm_Option.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//-------------------------------------------------
// Flash Partition type
//-------------------------------------------------
#ifndef _FLASH_PARTITION_TYPE
#define _FLASH_PARTITION_TYPE                                   _FLASH_PARTITION_NONE
#endif

#ifndef _FLASH_PARTITION_RELOCATABLE_SUPPORT
#define _FLASH_PARTITION_RELOCATABLE_SUPPORT                    _OFF
#endif

//-------------------------------------------------
// L51 Total bank setting
//-------------------------------------------------
#ifndef _FLASH_PARTITION_TOTAL_BANKS

#if(_FLASH_PARTITION_TYPE != _FLASH_PARTITION_USER)
#define _FLASH_PARTITION_TOTAL_BANKS                            0x10
#else
#define _FLASH_PARTITION_TOTAL_BANKS                            0x20
#endif

#endif

//-------------------------------------------------
// L51 Init bank setting
//-------------------------------------------------
#if(_FLASH_PARTITION_RELOCATABLE_SUPPORT == _ON)

#define _FLASH_PARTITION_INIT_BANK                              0x00

#else

#ifndef _FLASH_PARTITION_INIT_BANK
#if(_FLASH_PARTITION_TYPE != _FLASH_PARTITION_USER)
#define _FLASH_PARTITION_INIT_BANK                              0x00
#else
#define _FLASH_PARTITION_INIT_BANK                              0x10
#endif
#endif

#endif // End of #if(_FLASH_PARTITION_RELOCATABLE_SUPPORT == _ON)

