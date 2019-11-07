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
// ID Code      : RL6410_Series_VGATopInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// HS delay Time
//--------------------------------------------------
#define _PHASE_DELAY_TIME_VALUE                     (249) // 249 = 64 * 3.89 (Unit: ns)
#define _PHASE_DELAY_HALF_PERIOD_SHIFT              ((ScalerGetBit(P0_BC_ADC_CK_OUT_CTRL, _BIT5) == _BIT5) ? 32 : 0)

//--------------------------------------------------
// VGATOP auto-function V start offset
//--------------------------------------------------
#define _VGATOP_VSTART_OFFSET                       (((ScalerGetBit(P30_AE_VGATOP_VGIP_HV_DELAY, (_BIT7 | _BIT6)) == 0x00) && (ScalerGetBit(P30_A2_VGATOP_VGIP_DELAY_CTRL, (_BIT4 | _BIT2)) == (_BIT4 | _BIT2))) ? (-1) : 0)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
