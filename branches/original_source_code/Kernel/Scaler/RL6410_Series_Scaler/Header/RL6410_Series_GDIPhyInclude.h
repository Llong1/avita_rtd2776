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
// ID Code      : RL6410_Series_GDIPhyInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of GDI Clk Freq. (in kHz)
//--------------------------------------------------
//#define _GDI_CLK_KHZ                                (DWORD)(_M2PLL_CLK_KHZ / _SYS_CLK_DIV)    // in kHz
#define _GDI_CLK_KHZ                                (DWORD)((bit)ScalerGetBit(P80_06_GDI_CLK_DIVIDER, _BIT4) ? (((DWORD)1000 * _M2PLL_CLK_MHZ) / _GDI_CLK_DIV) : (_SYS_USE_ISO_CLK ? _INTERNAL_OSC_XTAL : _EXT_XTAL))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerGDIPhyBandgap(bit bSelect);

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
extern void ScalerGDIPhyRx0Z0Switch(BYTE ucPortSelect, bit bSelect);
extern void ScalerGDIPhyRx0PowerProc(EnumPowerAction enumPowerAction);
extern void ScalerGDIPhyRx0Power(EnumPowerAction enumPowerAction);
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
extern void ScalerGDIPhyRx1Z0Switch(BYTE ucPortSelect, bit bSelect);
extern void ScalerGDIPhyRx1PowerProc(EnumPowerAction enumPowerAction);
extern void ScalerGDIPhyRx1Power(EnumPowerAction enumPowerAction);
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
extern void ScalerGDIPhyRx2Z0Switch(BYTE ucPortSelect, bit bSelect);
extern void ScalerGDIPhyRx2PowerProc(EnumPowerAction enumPowerAction);
extern void ScalerGDIPhyRx2Power(EnumPowerAction enumPowerAction);
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
extern void ScalerGDIPhyRx3Z0Switch(BYTE ucPortSelect, bit bSelect);
extern void ScalerGDIPhyRx3PowerProc(EnumPowerAction enumPowerAction);
extern void ScalerGDIPhyRx3Power(EnumPowerAction enumPowerAction);
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
extern void ScalerGDIPhyRx4Z0Switch(BYTE ucPortSelect, bit bSelect);
extern void ScalerGDIPhyRx4PowerProc(EnumPowerAction enumPowerAction);
extern void ScalerGDIPhyRx4Power(EnumPowerAction enumPowerAction);
#endif

#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
extern void ScalerGDIPhyRx5Z0Switch(BYTE ucPortSelect, bit bSelect);
extern void ScalerGDIPhyRx5PowerProc(EnumPowerAction enumPowerAction);
extern void ScalerGDIPhyRx5Power(EnumPowerAction enumPowerAction);
#endif
