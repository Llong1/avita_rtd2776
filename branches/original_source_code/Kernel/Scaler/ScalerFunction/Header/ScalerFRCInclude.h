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
// ID Code      : ScalerFRCInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#if(_FRC_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of FRC address
//--------------------------------------------------
#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_2PCS)
//_1G_16BIT_DDR3_2PCS or _2G_16BIT_GDDR3_2PCS --> bank_remap_wide_enable = 1, Address: Row[27:12],Bnak[11:9],Column[8:0]
//_1G_16BIT_DDR3_1PC or _2G_16BIT_GDDR3_1PC --> bank_remap_wide_enable = 1, Address: Row[26:11],Bnak[10:8],Column[7:0]

//    |================|
//    |  M1 - Block 0  |
//    |----------------|
//    |  M2 - Block 0  |
//    |================|
//    |  M1 - Block 1  |
//    |----------------|
//    |  M2 - Block 1  |
//    |================|
//    |  M1 - Block 2  |
//    |----------------|
//    |  M2 - Block 2  |
//    |================|
//    |       OD       |
//    |================|

#define _FRC_CAP_M1_1ST_BLOCK_STA_ADDR                    ((DWORD)0x000000)
#define _FRC_CAP_M1_2ND_BLOCK_STA_ADDR                    ((DWORD)512 << 12)   // 0x20 0000

#define _FRC_CAP_M2_1ST_BLOCK_STA_ADDR                    ((DWORD)1024 << 12)  // 0x40 0000
#define _FRC_CAP_M2_2ND_BLOCK_STA_ADDR                    ((DWORD)1536 << 12)  // 0x60 0000

#define _FRC_CAP_S1_1ST_BLOCK_STA_ADDR                    ((DWORD)2048 << 12)  // 0x80 0000
#define _FRC_CAP_S1_2ND_BLOCK_STA_ADDR                    ((DWORD)2560 << 12)  // 0xA0 0000

#define _FRC_CAP_S2_1ST_BLOCK_STA_ADDR                    ((DWORD)2304 << 12)  // 0x90 0000
#define _FRC_CAP_S2_2ND_BLOCK_STA_ADDR                    ((DWORD)2816 << 12)  // 0xB0 0000

#elif((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_1PC)

#define _FRC_CAP_M1_1ST_BLOCK_STA_ADDR                    ((DWORD)0x000000)
#define _FRC_CAP_M1_2ND_BLOCK_STA_ADDR                    ((DWORD)512 << 11)   // 0x10 0000

#define _FRC_CAP_M2_1ST_BLOCK_STA_ADDR                    ((DWORD)1024 << 11)  // 0x20 0000
#define _FRC_CAP_M2_2ND_BLOCK_STA_ADDR                    ((DWORD)1536 << 11)  // 0x30 0000

#define _FRC_CAP_S1_1ST_BLOCK_STA_ADDR                    ((DWORD)2048 << 11)  // 0x40 0000
#define _FRC_CAP_S1_2ND_BLOCK_STA_ADDR                    ((DWORD)2560 << 11)  // 0x50 0000

#define _FRC_CAP_S2_1ST_BLOCK_STA_ADDR                    ((DWORD)2304 << 11)  // 0x48 0000
#define _FRC_CAP_S2_2ND_BLOCK_STA_ADDR                    ((DWORD)2816 << 11)  // 0x58 0000

#else

#define _FRC_CAP_M1_1ST_BLOCK_STA_ADDR                    (0x000000)     // ROW = 0
#define _FRC_CAP_M1_2ND_BLOCK_STA_ADDR                    (1365 << 11)    // ROW = 1365
#define _FRC_CAP_M1_3RD_BLOCK_STA_ADDR                    (682 << 11)     // ROW = 682

#define _FRC_CAP_M2_1ST_BLOCK_STA_ADDR                    (341 << 11)     // ROW = 341
#define _FRC_CAP_M2_2ND_BLOCK_STA_ADDR                    (1706 << 11)    // ROW = 1706
#define _FRC_CAP_M2_3RD_BLOCK_STA_ADDR                    (1023 << 11)    // ROW = 1023

#endif
#endif // End of #if(_FRC_SUPPORT == _ON)

//--------------------------------------------------
// Define Pre-read line
//--------------------------------------------------
#define _PRE_READ_MEMORY                                  (3) // before DDEN line
#define _PRE_READ_LINE_BUFFER                             (0) // before DDEN line

//--------------------------------------------------
// Define FRC Access Length
//--------------------------------------------------
#define _FRC_ACCESS_WRITE_LENGTH                          (0x7C)
#define _FRC_ACCESS_READ_LENGTH                           (0x7C)

//--------------------------------------------------
// Deinfe FRC setting path
//--------------------------------------------------
#define _FRC_CAP_MAIN_1                                   (_BIT0)
#define _FRC_CAP_MAIN_2                                   (_BIT1)
#define _FRC_CAP_SUB_1                                    (_BIT2)
#define _FRC_CAP_SUB_2                                    (_BIT3)

#define _FRC_DISP_MAIN_1                                  (_BIT4)
#define _FRC_DISP_MAIN_2                                  (_BIT5)
#define _FRC_DISP_SUB_1                                   (_BIT6)
#define _FRC_DISP_SUB_2                                   (_BIT7) // Only for 4P Case / PBP_TB


#if(_FORMAT_CONVERSION_SUPPORT == _ON)
#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_2PCS)
#define _FRC_ADDR_PBP_TB                                  ((DWORD)6144 << 12)
#else
#define _FRC_ADDR_PBP_TB                                  ((DWORD)6144 << 11)
#endif
#endif

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
#define GET_DISP_LATENCY_RATIO()                          (g_ucDispLatecnyRatio)
#define SET_DISP_LATENCY_RATIO(x)                         (g_ucDispLatecnyRatio = (x))
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _FRC_INPUT_SLOWER,
    _FRC_INPUT_FASTER,
} EnumFRCStyle;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_FRC_SUPPORT == _ON)
extern WORD g_usFRCPageSelect;
extern BYTE g_ucFRCPathCount;
#endif

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
extern BYTE g_ucDispLatecnyRatio;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)
extern DWORD ScalerFRCRegPageSelection(EnumInputDataPath enumInputPath);
extern void ScalerFRCPowerOnInitial(void);
extern void ScalerFRCEn(EnumFRCOnOff enumCapDispOnOff, EnumInputDataPath enumInputPath, bit bEn);
#endif

#if(_FRC_SUPPORT == _ON)
extern WORD ScalerFRCCalculatePreReadLine(WORD usFRCVerSize);
extern void ScalerFRCAdjustIVS2DVSDelay(WORD usFRCVerSize);
extern void ScalerFRCCompareIHFandDHF(WORD usVerSize);
extern WORD ScalerFRCSetOneFrameDVTotal(void);
extern void ScalerFRCSetPreRead(EnumInputDataPath enumInputPath, WORD usPreReadLine);
#endif

extern void ScalerFRCSetDDomainSourceSelect(EnumInputDataPath enumInputPath, EnumDDomainSourceSelect enumSourceSelect);

