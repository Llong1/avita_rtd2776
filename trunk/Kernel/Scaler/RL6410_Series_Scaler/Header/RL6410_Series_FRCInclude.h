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
// ID Code      : RL6410_Series_FRCInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#if(_FRC_SUPPORT == _ON)
#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
//--------------------------------------------------
// Definitions of FRC address
//--------------------------------------------------
#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_2PCS)
#define _FRC_CAP_M1_1ST_BLOCK_STA_ADDR_FB                    ((DWORD)0x000000)
#define _FRC_CAP_M1_2ND_BLOCK_STA_ADDR_FB                    ((DWORD)480 << 12)   // 0x1E 0000

#define _FRC_CAP_M2_1ST_BLOCK_STA_ADDR_FB                    ((DWORD)960 << 12)   // 0x3C 0000
#define _FRC_CAP_M2_2ND_BLOCK_STA_ADDR_FB                    ((DWORD)1440 << 12)  // 0x5A 0000

#define _FRC_CAP_S1_1ST_BLOCK_STA_ADDR_FB                    ((DWORD)1920 << 12)  // 0x78 0000
#define _FRC_CAP_S1_2ND_BLOCK_STA_ADDR_FB                    ((DWORD)2400 << 12)  // 0x96 0000

#define _FRC_CAP_S2_1ST_BLOCK_STA_ADDR_FB                    ((DWORD)2880 << 12)  // 0xB4 0000
#define _FRC_CAP_S2_2ND_BLOCK_STA_ADDR_FB                    ((DWORD)3360 << 12)  // 0xD2 0000

#elif((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_1PC)

#define _FRC_CAP_M1_1ST_BLOCK_STA_ADDR_FB                    ((DWORD)0x000000)
#define _FRC_CAP_M1_2ND_BLOCK_STA_ADDR_FB                    ((DWORD)480 << 11)   // 0x0F 0000

#define _FRC_CAP_M2_1ST_BLOCK_STA_ADDR_FB                    ((DWORD)960 << 11)   // 0x1E 0000
#define _FRC_CAP_M2_2ND_BLOCK_STA_ADDR_FB                    ((DWORD)1440 << 11)  // 0x2D 0000

#define _FRC_CAP_S1_1ST_BLOCK_STA_ADDR_FB                    ((DWORD)1920 << 11)  // 0x3C 0000
#define _FRC_CAP_S1_2ND_BLOCK_STA_ADDR_FB                    ((DWORD)2400 << 11)  // 0x4B 0000

#define _FRC_CAP_S2_1ST_BLOCK_STA_ADDR_FB                    ((DWORD)2880 << 11)  // 0x5A 0000
#define _FRC_CAP_S2_2ND_BLOCK_STA_ADDR_FB                    ((DWORD)3360 << 11)  // 0x69 0000
#endif
#endif // End of #if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
#endif // End of #if(_FRC_SUPPORT == _ON)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)
extern void ScalerFRCInitial(void);
#endif

#if(_FRC_SUPPORT == _ON)
extern void ScalerFRCControl(const StructSDRAMDataInfo *pstFIFOSize);
extern void ScalerFRCInputCtrl(WORD usHorSize, WORD usVerSize);
extern void ScalerFRCDisplayCtrl(WORD usHorSize, WORD usVerSize);
#endif

