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
// ID Code      : ScalerPLLInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#if(_M2PLL_STRUCT_TYPE == _M2PLL_STRUCT_M_N)
//--------------------------------------------------
// Definitions of MN M2PLL Clock Frequency Paramater
//--------------------------------------------------
#if(_EXT_XTAL == _XTAL14318K)
#define _M2PLL_PLL_M                                (47 + 2) // Page1 0xE0[7:0] default value = 0x2F
#define _M2PLL_PLL_N                                (0 + 2)  // Page1 0xE1[3:0] default value = 0x0
#elif(_EXT_XTAL == _XTAL27000K)
#define _M2PLL_PLL_M                                (24 + 2) // Page1 0xE0[7:0] default value = 0x18
#define _M2PLL_PLL_N                                (0 + 2)  // Page1 0xE1[3:0] default value = 0x0
#endif

#define _M2PLL_PLL_O                                1        // Page1 0xE1[5:4] default value = 0x0
#define _DWORD_DIMENSION                            1UL
#define _M2PLL_CLK_KHZ                              (((_DWORD_DIMENSION * _EXT_XTAL * _M2PLL_PLL_M) + ((_DWORD_DIMENSION * _M2PLL_PLL_N * _M2PLL_PLL_O) / 2)) / (_DWORD_DIMENSION * _M2PLL_PLL_N * _M2PLL_PLL_O))
#define _M2PLL_CLK_MHZ                              (((_DWORD_DIMENSION * _EXT_XTAL * _M2PLL_PLL_M) + ((_DWORD_DIMENSION * _M2PLL_PLL_N * _M2PLL_PLL_O * 1000) / 2)) / (_DWORD_DIMENSION * _M2PLL_PLL_N * _M2PLL_PLL_O * 1000))

#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)
#define _DDRPLL_VCO_CLK_1X                          0
#define _DDRPLL_VCO_CLK_2X                          1
#define _DDRPLL_CLK_SOURCE                          _DDRPLL_VCO_CLK_2X
#endif
#endif // End of #if(_M2PLL_STRUCT_TYPE == _M2PLL_STRUCT_M_N)

//--------------------------------------------------
// Definitions of PLL VCO BAND
//--------------------------------------------------
#define _PLL_VCO_BAND_00                            (778)
#define _PLL_VCO_BAND_01                            (1340)
#define _PLL_VCO_BAND_10                            (1880)
#define _PLL_VCO_BAND_11                            (2340)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerM2PLLDiv(BYTE ucDiv);
extern void ScalerPLLSetDPLLReset(void);
extern void ScalerPLLSetDPLLSSC(bit bDclkSpreadSpeed, BYTE ucSpreadRange);
extern void ScalerPLLSetDPLLFreq(DWORD ulFreq);
extern void ScalerDPLLFineTuneFrameSyncLineBuffer(void);
#if(_FRC_SUPPORT == _ON)
extern void ScalerDPLLFineTuneFrameSyncFrameBuffer(void);
#endif

#if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)
extern void ScalerPLLSetMPLLFreq(DWORD ulFreq);
#endif

#if(_VGA_SUPPORT == _ON)
extern bit ScalerAPLLAdjust(WORD usCurrHTotal, WORD usCurrHFreq);
extern WORD ScalerAPLLGetIHTotal(void);
#endif

#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)
extern void ScalerPLLSetDDRPLLFreq(DWORD ulFreq);
#endif

