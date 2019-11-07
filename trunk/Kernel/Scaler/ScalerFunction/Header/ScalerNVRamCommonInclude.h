/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2011>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : ScalerNVRamCommonInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Flash Support List
//--------------------------------------------------
#define _FLASH_W25X20A                              0
#define _FLASH_W25X21CL                             1
#define _FLASH_PM25LV020                            2
// This is MX25L2026D, it is not same with MX25L2026E
#define _FLASH_MX25L2026                            3
#define _FLASH_EN25F20                              4
#define _FLASH_PM25LD020                            5
#define _FLASH_MX25L2025                            6
//KH25L4006E use the same _FLASH_MX25L4006E
#define _FLASH_MX25L4006E                           7
#define _FLASH_SST25LF020A                          8
#define _FLASH_W25X41CL                             9
#define _FLASH_FM25F04                              10
#define _FLASH_N25S40                               11
#define _FLASH_A25L040                              12
//W25Q80DV use the same _FLASH_W25Q80BV
#define _FLASH_W25Q80BV                             13
#define _FLASH_PM25LQ020A                           14
#define _FLASH_MX25L4026D                           15
#define _FLASH_W25X40CL                             16
#define _FLASH_MX25L1606E                           17
#define _FLASH_MX25L3206E                           18
#define _FLASH_A25L016                              19
//W25Q16JV use the same _FLASH_W25Q16DV
#define _FLASH_W25Q16DV                             20
#define _FLASH_A25L032                              21
#define _FLASH_W25Q32F                              22
#define _FLASH_GD25Q16                              23
#define _FLASH_MX25L1633E                           24
#define _FLASH_PM25LQ080C                           25
#define _FLASH_GD25Q16C                             26
#define _FLASH_MX25L3233F                           27
#define _FLASH_EN25QH32A                            28
#define _FLASH_MX25L8006E                           29
#define _FLASH_MX25V1635F                           30
#define _FLASH_AT25SF041                            31
#define _FLASH_MX25L6433F                           32
#define _FLASH_PM25LQ016                            33
#define _FLASH_GD25Q32C                             34
#define _FLASH_MX25R8035F                           35
#define _FLASH_TYPE_END                             36
#define _FLASH_TOTAL_COUNT                          _FLASH_TYPE_END
#define _FLASH_DEFAULT_TYPE                         _FLASH_W25X20A
#define _FLASH_UNDETECT                             0xFE

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Definitions of Version Code related Infor.
//--------------------------------------------------
typedef struct
{
    BYTE ucIDCheck1OpCode; // ID check 1 OP code(0x9F/0x90/0xAB)
    BYTE ucIDCheck1_ID0; // ID check 1 ID
    BYTE ucIDCheck1_ID1;
    BYTE ucIDCheck1_ID2;
    BYTE ucIDCheck2OpCode; // ID check 1 OP code(0x90/0xAB)
    BYTE ucIDCheck2_ID0; // ID check 1 ID
    BYTE ucIDCheck2_ID1;
    BYTE ucIDCheck2_ID2;
    BYTE ucWRENOpCode; // WREN OP code
    BYTE ucWRDisOpCode; // WRDis OP code
    BYTE ucPageEraseOpCode; // Page erase OP code
    BYTE ucUnprotectWRSR; // Unprotect status register value
    BYTE ucProtectWRSR; // Protect status register value
}StructFlashInformation;

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern BYTE g_ucFlashType;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerFlashDetectFlashType(void);
extern void ScalerFlashWREN(BYTE ucBank, BYTE ucPage);
extern void ScalerFlashWRDis(void);

extern bit ScalerFlashErasePage(BYTE ucBank, BYTE ucPage);

