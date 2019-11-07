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
// ID Code      : ScalerDisplay.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DISPLAY__

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


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_PANEL_STYLE == _PANEL_VBO)
StructVboInfo g_stVboInfo =
{
    _FAIL,
    _FALSE,
    _DISABLE,
};
#endif // #if(_PANEL_STYLE == _PANEL_VBO)

#if(_FRC_SUPPORT == _ON)
StructDVCustomizedFreq g_stDVCustomizedFreq;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_PANEL_STYLE == _PANEL_LVDS)

void ScalerDisplayLvdsTxDataSel(void);
void ScalerDisplayLvdsTxPortSwap(void);

#elif(_PANEL_STYLE == _PANEL_VBO)

void ScalerDisplayVboMac(bit bOn);
void ScalerDisplayVboPhy(bit bOn);
void ScalerDisplayVboAnalogPhyConrol(bit bEnable);
void ScalerDisplayVboCdr2AlnLatency(void);

void ScalerDisplayVboHtpdnSetFwControl(bit bEnable);
void ScalerDisplayVboForceVideoOutput(bit bEnable);
void ScalerDisplayVboSetLocknInterrupt(bit bEnable);
void ScalerDisplayVboSetUnLocknInterrupt(bit bEnable);
void ScalerDisplayVboPollingHotPlug(WORD usNum);
void ScalerDisplayVboHtpdnHandler(void);
void ScalerDisplayVboLocknHandler(void);
bit ScalerDisplayVboLocknStatus(void);
void ScalerDisplayVboPanelSetFastOff(bit bEnable);
bit ScalerDisplayVboPanelFastOffCheck(void);
void ScalerDisplayVboPanelBacklightReTurnOn(void);
void ScalerDisplayVboIntHandler_EXINT0(void);

#endif // #if(_PANEL_STYLE == _PANEL_LVDS)

#if((_FRC_SUPPORT == _ON) || (_OD_SUPPORT == _ON))
BYTE ScalerDisplaySelectDVFMode(void);
void ScalerDisplaySetDVFreq(void);
#endif // #if((_FRC_SUPPORT == _ON) || (_OD_SUPPORT == _ON))

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

#if(_PANEL_STYLE == _PANEL_LVDS)
//--------------------------------------------------
// Description  : LVDS TX Port output Data Selection
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsTxDataSel(void)
{
#if(_LVDS_PORT_SEL == _LVDS_2_PORT_AB)

    ScalerSetByte(P39_02_LVDS_DISPLAY_CONV_CTRL1, ((_LVDS_PORT_MIRROR == _DISABLE) ? 0x01 : 0x10));

    // Set LVDS Port AB Strongly Pull Down Initially
    ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~_BIT6, _BIT6);
    ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~_BIT6, _BIT6);

#if(_LVDS_TERMINATION_CONTROL == _ENABLE)

    // Set LVDS Port AB Output Termination Enable
    ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

#else // #if(_LVDS_TERMINATION_CONTROL == _ENABLE)

    // Set LVDS Port AB Output Termination Disable
    ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#endif // #if(_LVDS_TERMINATION_CONTROL == _ENABLE)


#elif(_LVDS_PORT_SEL == _LVDS_2_PORT_CD)

    ScalerSetByte(P39_03_LVDS_DISPLAY_CONV_CTRL2, ((_LVDS_PORT_MIRROR == _DISABLE) ? 0x01 : 0x10));

    // Set LVDS Port CD Strongly Pull Down Initially
    ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~_BIT6, _BIT6);
    ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~_BIT6, _BIT6);

#if(_LVDS_TERMINATION_CONTROL == _ENABLE)

    // Set LVDS Port CD Output Termination Enable
    ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

#else // #if(_LVDS_TERMINATION_CONTROL == _ENABLE)

    // Set LVDS Port CD Output Termination Disable
    ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#endif // #if(_LVDS_TERMINATION_CONTROL == _ENABLE)


#elif(_LVDS_PORT_SEL == _LVDS_2_PORT_EF)

    ScalerSetByte(P39_04_LVDS_DISPLAY_CONV_CTRL3, ((_LVDS_PORT_MIRROR == _DISABLE) ? 0x01 : 0x10));

    // Set LVDS Port EF Strongly Pull Down Initially
    ScalerSetBit(P95_26_LVDS_PORTA_CTRL6, ~_BIT6, _BIT6);
    ScalerSetBit(P95_36_LVDS_PORTB_CTRL6, ~_BIT6, _BIT6);

#if(_LVDS_TERMINATION_CONTROL == _ENABLE)

    // Set LVDS Port EF Output Termination Enable
    ScalerSetBit(P95_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P95_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

#else // #if(_LVDS_TERMINATION_CONTROL == _ENABLE)

    // Set LVDS Port EF Output Termination Disable
    ScalerSetBit(P95_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P95_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#endif // #if(_LVDS_TERMINATION_CONTROL == _ENABLE)


#elif(_LVDS_PORT_SEL == _LVDS_2_PORT_GH)

    ScalerSetByte(P39_05_LVDS_DISPLAY_CONV_CTRL4, ((_LVDS_PORT_MIRROR == _DISABLE) ? 0x01 : 0x10));

    // Set LVDS Port GH Strongly Pull Down Initially
    ScalerSetBit(PD5_26_LVDS_PORTA_CTRL6, ~_BIT6, _BIT6);
    ScalerSetBit(PD5_36_LVDS_PORTB_CTRL6, ~_BIT6, _BIT6);

#if(_LVDS_TERMINATION_CONTROL == _ENABLE)

    // Set LVDS Port GH Output Termination Enable
    ScalerSetBit(PD5_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(PD5_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

#else // #if(_LVDS_TERMINATION_CONTROL == _ENABLE)

    // Set LVDS Port GH Output Termination Disable
    ScalerSetBit(PD5_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(PD5_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#endif // #if(_LVDS_TERMINATION_CONTROL == _ENABLE)


#elif(_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD)

    ScalerSetByte(P39_02_LVDS_DISPLAY_CONV_CTRL1, ((_LVDS_PORT_MIRROR == _DISABLE) ? 0x01 : 0x32));
    ScalerSetByte(P39_03_LVDS_DISPLAY_CONV_CTRL2, ((_LVDS_PORT_MIRROR == _DISABLE) ? 0x23 : 0x10));

    // Set LVDS Port ABCD Strongly Pull Down Initially
    ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~_BIT6, _BIT6);
    ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~_BIT6, _BIT6);
    ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~_BIT6, _BIT6);
    ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~_BIT6, _BIT6);

#if(_LVDS_TERMINATION_CONTROL == _ENABLE)

    // Set LVDS Port ABCD Output Termination Enable
    ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

#else // #if(_LVDS_TERMINATION_CONTROL == _ENABLE)

    // Set LVDS Port ABCD Output Termination Disable
    ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#endif // #if(_LVDS_TERMINATION_CONTROL == _ENABLE)


#elif(_LVDS_PORT_SEL == _LVDS_4_PORT_CDEF)

    ScalerSetByte(P39_03_LVDS_DISPLAY_CONV_CTRL2, ((_LVDS_PORT_MIRROR == _DISABLE) ? 0x01 : 0x32));
    ScalerSetByte(P39_04_LVDS_DISPLAY_CONV_CTRL3, ((_LVDS_PORT_MIRROR == _DISABLE) ? 0x23 : 0x10));

    // Set LVDS Port CDEF Strongly Pull Down Initially
    ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~_BIT6, _BIT6);
    ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~_BIT6, _BIT6);
    ScalerSetBit(P95_26_LVDS_PORTA_CTRL6, ~_BIT6, _BIT6);
    ScalerSetBit(P95_36_LVDS_PORTB_CTRL6, ~_BIT6, _BIT6);

#if(_LVDS_TERMINATION_CONTROL == _ENABLE)

    // Set LVDS Port CDEF Output Termination Enable
    ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P95_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P95_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

#else // #if(_LVDS_TERMINATION_CONTROL == _ENABLE)

    // Set LVDS Port CDEF Output Termination Disable
    ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P95_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P95_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#endif // #if(_LVDS_TERMINATION_CONTROL == _ENABLE)


#elif(_LVDS_PORT_SEL == _LVDS_4_PORT_EFGH)

    ScalerSetByte(P39_04_LVDS_DISPLAY_CONV_CTRL3, ((_LVDS_PORT_MIRROR == _DISABLE) ? 0x01 : 0x32));
    ScalerSetByte(P39_05_LVDS_DISPLAY_CONV_CTRL4, ((_LVDS_PORT_MIRROR == _DISABLE) ? 0x23 : 0x10));

    // Set LVDS Port EFGH Strongly Pull Down Initially
    ScalerSetBit(P95_26_LVDS_PORTA_CTRL6, ~_BIT6, _BIT6);
    ScalerSetBit(P95_36_LVDS_PORTB_CTRL6, ~_BIT6, _BIT6);
    ScalerSetBit(PD5_26_LVDS_PORTA_CTRL6, ~_BIT6, _BIT6);
    ScalerSetBit(PD5_36_LVDS_PORTB_CTRL6, ~_BIT6, _BIT6);

#if(_LVDS_TERMINATION_CONTROL == _ENABLE)

    // Set LVDS Port EFGH Output Termination Enable
    ScalerSetBit(P95_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P95_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(PD5_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(PD5_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

#else // #if(_LVDS_TERMINATION_CONTROL == _ENABLE)

    // Set LVDS Port EFGH Output Termination Disable
    ScalerSetBit(P95_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P95_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(PD5_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(PD5_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#endif // #if(_LVDS_TERMINATION_CONTROL == _ENABLE)


#elif(_LVDS_PORT_SEL == _LVDS_8_PORT_ABCDEFGH)

    ScalerSetByte(P39_02_LVDS_DISPLAY_CONV_CTRL1, ((_LVDS_PORT_MIRROR == _DISABLE) ? 0x01 : 0x76));
    ScalerSetByte(P39_03_LVDS_DISPLAY_CONV_CTRL2, ((_LVDS_PORT_MIRROR == _DISABLE) ? 0x23 : 0x54));
    ScalerSetByte(P39_04_LVDS_DISPLAY_CONV_CTRL3, ((_LVDS_PORT_MIRROR == _DISABLE) ? 0x45 : 0x32));
    ScalerSetByte(P39_05_LVDS_DISPLAY_CONV_CTRL4, ((_LVDS_PORT_MIRROR == _DISABLE) ? 0x67 : 0x10));

    // Set LVDS Port ABCDEFGH Strongly Pull Down Initially
    ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~_BIT6, _BIT6);
    ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~_BIT6, _BIT6);
    ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~_BIT6, _BIT6);
    ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~_BIT6, _BIT6);
    ScalerSetBit(P95_26_LVDS_PORTA_CTRL6, ~_BIT6, _BIT6);
    ScalerSetBit(P95_36_LVDS_PORTB_CTRL6, ~_BIT6, _BIT6);
    ScalerSetBit(PD5_26_LVDS_PORTA_CTRL6, ~_BIT6, _BIT6);
    ScalerSetBit(PD5_36_LVDS_PORTB_CTRL6, ~_BIT6, _BIT6);

#if(_LVDS_TERMINATION_CONTROL == _ENABLE)

    // Set LVDS Port ABCDEFGH Output Termination Enable
    ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P95_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P95_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(PD5_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(PD5_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

#else // #if(_LVDS_TERMINATION_CONTROL == _ENABLE)

    // Set LVDS Port ABCDEFGH Output Termination Disable
    ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P95_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P95_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(PD5_26_LVDS_PORTA_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(PD5_36_LVDS_PORTB_CTRL6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#endif // #if(_LVDS_TERMINATION_CONTROL == _ENABLE)


#endif // #if(_LVDS_PORT_SEL == _LVDS_2_PORT_AB)
}

//--------------------------------------------------
// Description  : LVDS TX Port output Data Swap Selection
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsTxPortSwap(void)
{
    BYTE ucLvdsPortSwapIndex = 0;

    // Port AB Swap
    ucLvdsPortSwapIndex = ((_LVDS_PORT_AB_SWAP == _DISABLE) ? 0 : 4);

    ScalerSetByte(P39_02_LVDS_DISPLAY_CONV_CTRL1, (((ScalerGetBit(P39_02_LVDS_DISPLAY_CONV_CTRL1, (_BIT7 | _BIT6 | _BIT5 | _BIT4))) >> ucLvdsPortSwapIndex) | ((ScalerGetBit(P39_02_LVDS_DISPLAY_CONV_CTRL1, (_BIT3 | _BIT2 | _BIT1 | _BIT0))) << ucLvdsPortSwapIndex)));

    // Port CD Swap
    ucLvdsPortSwapIndex = ((_LVDS_PORT_CD_SWAP == _DISABLE) ? 0 : 4);

    ScalerSetByte(P39_03_LVDS_DISPLAY_CONV_CTRL2, (((ScalerGetBit(P39_03_LVDS_DISPLAY_CONV_CTRL2, (_BIT7 | _BIT6 | _BIT5 | _BIT4))) >> ucLvdsPortSwapIndex) | ((ScalerGetBit(P39_03_LVDS_DISPLAY_CONV_CTRL2, (_BIT3 | _BIT2 | _BIT1 | _BIT0))) << ucLvdsPortSwapIndex)));

    // Port EF Swap
    ucLvdsPortSwapIndex = ((_LVDS_PORT_EF_SWAP == _DISABLE) ? 0 : 4);

    ScalerSetByte(P39_04_LVDS_DISPLAY_CONV_CTRL3, (((ScalerGetBit(P39_04_LVDS_DISPLAY_CONV_CTRL3, (_BIT7 | _BIT6 | _BIT5 | _BIT4))) >> ucLvdsPortSwapIndex) | ((ScalerGetBit(P39_04_LVDS_DISPLAY_CONV_CTRL3, (_BIT3 | _BIT2 | _BIT1 | _BIT0))) << ucLvdsPortSwapIndex)));

    // Port GH Swap
    ucLvdsPortSwapIndex = ((_LVDS_PORT_GH_SWAP == _DISABLE) ? 0 : 4);

    ScalerSetByte(P39_05_LVDS_DISPLAY_CONV_CTRL4, (((ScalerGetBit(P39_05_LVDS_DISPLAY_CONV_CTRL4, (_BIT7 | _BIT6 | _BIT5 | _BIT4))) >> ucLvdsPortSwapIndex) | ((ScalerGetBit(P39_05_LVDS_DISPLAY_CONV_CTRL4, (_BIT3 | _BIT2 | _BIT1 | _BIT0))) << ucLvdsPortSwapIndex)));
}



#elif(_PANEL_STYLE == _PANEL_VBO)
// Jeyu_test: Transmit ALN pattern, setting PLL parameter with 1 lane condition
//--------------------------------------------------
// Description  : Settings for Vbyone MAC
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboMac(bit bOn)
{
    if(bOn == _ON)
    {
        // Set Vby1 MAC
        ScalerSetBit(P38_0A_TRANSMIT_CONTROL_H1, ~_BIT7, _BIT7);
    }

    else
    {
        // Reset Vby1 MAC
        ScalerSetBit(P38_0A_TRANSMIT_CONTROL_H1, ~_BIT7, 0x00);
    }
}

//--------------------------------------------------
// Description  : Settings for Vbyone Digital Phy
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboPhy(bit bOn)
{
    if(bOn == _ON)
    {
        // Set Vby1 Digital Phy
        ScalerSetBit(P38_00_VIDEO_FORMAT_H, ~_BIT4, _BIT4);

        // Enable Digital Phy output
        ScalerSetByte(P38_8E_PHY0_TXBIST_02_H1, 0xFF);
    }

    else
    {
        // Disable Digital Phy output
        ScalerSetByte(P38_8E_PHY0_TXBIST_02_H1, 0x00);

        // Reset Vby1 Digital Phy
        ScalerSetBit(P38_00_VIDEO_FORMAT_H, ~_BIT4, 0x00);
    }
}

//--------------------------------------------------
// Description  : Control Vby1 Phy
// Input Value  : bit bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboAnalogPhyConrol(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Vby1 Power on
        ScalerDisplayVboPower(_ON);

        // Vby1 PLL on
        ScalerDisplayVboPLL(_ON);

        // Set Vby1 MAC
        ScalerDisplayVboMac(_ON);

        // Set Vby1 Digital Phy, Enable Output
        ScalerDisplayVboPhy(_ON);
    }
    else
    {
        // Reset Vby1 Digital Phy, disable Output
        ScalerDisplayVboPhy(_OFF);

        // Reset Vby1 MAC
        ScalerDisplayVboMac(_OFF);

        // Vby1 PLL off
        ScalerDisplayVboPLL(_OFF);

        // Vby1 Power off
        ScalerDisplayVboPower(_OFF);
    }
}

//--------------------------------------------------
// Description  : Vbyone Latency between CDR and ALN pattern
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboCdr2AlnLatency(void)
{
    DWORD ulCdr2AlnLatency = 0;

    ulCdr2AlnLatency = (_CDR_TRANSFER_ALN_LATENCY * 27);

    ScalerSetBit(P38_0A_TRANSMIT_CONTROL_H1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ulCdr2AlnLatency >> 16) & 0x3F));
    ScalerSetByte(P38_0B_TRANSMIT_CONTROL_L2, ((ulCdr2AlnLatency >> 8) & 0xFF));
    ScalerSetByte(P38_0C_TRANSMIT_CONTROL_L1, (ulCdr2AlnLatency & 0xFF));
}

//--------------------------------------------------
// Description  : Vbyone HTPDN Interrupt Enable
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboHtpdnSetFwControl(bit bEnable)
{
    // Write Clear the HTDPN and LOCKN Flag
    ScalerSetBit(P38_28_VBY1_IRQ_CTRL, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4));

    if(bEnable == _ENABLE)
    {
        // Set HTPDN Interrupt Disable
        ScalerSetBit(P38_28_VBY1_IRQ_CTRL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), 0x00);

        // Set HTPDN Pull High
        ScalerSetBit(P38_27_VBY1_FW_CTRL, ~_BIT1, _BIT1);

        // Set Vby1 HTPDN controlled by F/W
        ScalerSetBit(P38_27_VBY1_FW_CTRL, ~_BIT7, _BIT7);
    }

    else
    {
        // Set HTPDN Interrupt Enable
        ScalerSetBit(P38_28_VBY1_IRQ_CTRL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), _BIT6);

        // Set Vby1 HTPDN controlled by H/W
        ScalerSetBit(P38_27_VBY1_FW_CTRL, ~_BIT7, 0x00);
    }
}

//--------------------------------------------------
// Description  : Vbyone Video Output Enable
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboForceVideoOutput(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Set Vby1 LOCKN controlled by F/W
        ScalerSetBit(P38_27_VBY1_FW_CTRL, ~_BIT6, _BIT6);

        // Set LOCKN Pull Low
        ScalerSetBit(P38_27_VBY1_FW_CTRL, ~_BIT0, 0x00);
    }
    else
    {
        // Disable Detect Lock Status
        ScalerDisplayVboSetLocknInterrupt(_DISABLE);

        // Disable Detect UnLock Stauts
        ScalerDisplayVboSetUnLocknInterrupt(_DISABLE);

        // Set LOCKN Pull High
        ScalerSetBit(P38_27_VBY1_FW_CTRL, ~_BIT0, _BIT0);

        // Set Vby1 LOCKN controlled by H/W
        ScalerSetBit(P38_27_VBY1_FW_CTRL, ~_BIT6, 0x00);

        // Clear all flag
        ScalerSetBit(P38_28_VBY1_IRQ_CTRL, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT1 | _BIT0));

        // LOCKN status initial: Fail
        g_stVboInfo.b1VboLocknStatus = _FAIL;

        // LOCKN Ripped off status initial: False
        g_stVboInfo.b1VboLocknRippedOff = _FALSE;

        // Set Panel Fast Off Disable
        g_stVboInfo.b1PanelFastOffStatus = _DISABLE;
    }
}

//--------------------------------------------------
// Description  : Vbyone LOCKN Interrupt Enable
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboSetLocknInterrupt(bit bEnable)
{
    // Write Clear the Lock Flag
    ScalerSetBit(P38_28_VBY1_IRQ_CTRL, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), _BIT5);

    if(bEnable == _ENABLE)
    {
        // Set LOCKN Interrupt Enable
        ScalerSetBit(P38_28_VBY1_IRQ_CTRL, ~(_BIT7 | _BIT5 | _BIT4 | _BIT1 | _BIT0), _BIT7);
    }

    else
    {
        // Set LOCKN Interrupt Disable
        ScalerSetBit(P38_28_VBY1_IRQ_CTRL, ~(_BIT7 | _BIT5 | _BIT4 | _BIT1 | _BIT0), 0x00);
    }
}

//--------------------------------------------------
// Description  : Vbyone LOCKN_FAIL Interrupt Enable
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboSetUnLocknInterrupt(bit bEnable)
{
    // Write Clear the UnLock Flag
    ScalerSetBit(P38_28_VBY1_IRQ_CTRL, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), _BIT1);

    if(bEnable == _ENABLE)
    {
        // Set LOCKN_FAIL Interrupt Enable
        ScalerSetBit(P38_28_VBY1_IRQ_CTRL, ~(_BIT5 | _BIT4 | _BIT3 | _BIT1 | _BIT0), _BIT3);
    }

    else
    {
        // Set LOCKN_FAIL Interrupt Disable
        ScalerSetBit(P38_28_VBY1_IRQ_CTRL, ~(_BIT5 | _BIT4 | _BIT3 | _BIT1 | _BIT0), 0x00);
    }
}

//--------------------------------------------------
// Description  : Wait for Vbyone Htpdn
// Input Value  : WORD usNum
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboPollingHotPlug(WORD usNum)
{
    ScalerTimerPollingFlagProc(usNum, P38_28_VBY1_IRQ_CTRL, _BIT4, _TRUE);
}

//--------------------------------------------------
// Description  : Vbyone Hot Plug Detect n Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboHtpdnHandler(void)
{
    if(ScalerGetBit(P38_28_VBY1_IRQ_CTRL, _BIT4) != _BIT4)
    {
        // Set HTPDN Interrupt Disable
        ScalerSetBit(P38_28_VBY1_IRQ_CTRL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), 0x00);

        // Set UnLOCKN Status: None
        g_stVboInfo.b1VboLocknRippedOff = _FALSE;

        // Set Vby1 HTPDN controlled by F/W
        ScalerSetBit(P38_27_VBY1_FW_CTRL, ~_BIT7, _BIT7);

        // Set HTPDN Pull Low
        ScalerSetBit(P38_27_VBY1_FW_CTRL, ~_BIT1, 0x00);

        // Set LOCKN Interrupt Enable
        ScalerDisplayVboSetLocknInterrupt(_ENABLE);
    }

    // Set Detect UnLock Interrupt Enable
    ScalerDisplayVboSetUnLocknInterrupt(_ENABLE);
}

//--------------------------------------------------
// Description  : Vbyone Lockn Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboLocknHandler(void)
{
    // Check Vbyone Lockn status success
    if(ScalerDisplayVboLocknStatus() != _SUCCESS)
    {
        // Force transfer to ALN pattern, and enable video output
        ScalerDisplayVboForceVideoOutput(_ENABLE);

        // Wait Delay time for ALN patern
        ScalerTimerDelayXms(80);
    }
}

//--------------------------------------------------
// Description  : Vbyone LOCKN Check
// Input Value  : None
// Output Value : _SUCCESS or _FAIL
//--------------------------------------------------
bit ScalerDisplayVboLocknStatus(void)
{
    return g_stVboInfo.b1VboLocknStatus;
}

//--------------------------------------------------
// Description  : Vbyone Panel Fast Off Setting
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboPanelSetFastOff(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        g_stVboInfo.b1PanelFastOffStatus = _ENABLE;
    }
    else
    {
        g_stVboInfo.b1PanelFastOffStatus = _DISABLE;
    }
}

//--------------------------------------------------
// Description  : Vbyone Panel Fast Off Check
// Input Value  : None
// Output Value : _ENABLE or _DISABLE
//--------------------------------------------------
bit ScalerDisplayVboPanelFastOffCheck(void)
{
    return g_stVboInfo.b1PanelFastOffStatus;
}

//--------------------------------------------------
// Description  : Vbyone LOCKN Re Lock, Re-Turn on Backlight
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboPanelBacklightReTurnOn(void)
{
    // When CDR Re-Lock: Backlight Re-Turn on
    if(g_stVboInfo.b1VboLocknRippedOff == _TRUE)
    {
        if((ScalerDisplayVboLocknStatus() == _SUCCESS) || (ScalerGetBit(P38_0D_TRANSMIT_STATUS, _BIT1) == _BIT1))
        {
            ScalerTimerDelayXms(_PANEL_POWER_ON_T3);

            // Check Vby1 ALN_En flag, when Vby1 CDR locked, this flag will be triggered
            if(ScalerGetBit(P38_0D_TRANSMIT_STATUS, _BIT1) == _BIT1)
            {
                // Backlight Turn On
                PCB_BACKLIGHT_POWER_PIN(_LIGHT_CONTROL_ON);

                // Set CDR re-lock Status: None
                g_stVboInfo.b1VboLocknRippedOff = _FALSE;

                // Set LOCKN Status: Success
                g_stVboInfo.b1VboLocknStatus = _SUCCESS;
            }
            else
            {
#if(_PANEL_VBO_UNLOCK_MUTE_BY_FW_POLLING == _ON)
                // Backlight Turn Off
                PCB_BACKLIGHT_POWER_PIN(_LIGHT_CONTROL_OFF);
#endif
                // Set LOCKN Status: Fail
                g_stVboInfo.b1VboLocknStatus = _FAIL;
            }
        }
#if(_PANEL_VBO_UNLOCK_MUTE_BY_FW_POLLING == _ON)
        else
        {
            // Backlight Turn Off
            PCB_BACKLIGHT_POWER_PIN(_LIGHT_CONTROL_OFF);

            // Set LOCKN Status: Fail
            g_stVboInfo.b1VboLocknStatus = _FAIL;
        }
#endif
    }
}

//--------------------------------------------------
// Description  : Vbyone Interrupt Handler: HTPDN, LOCKN
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboIntHandler_EXINT0(void) using 1
{
    // HTPDN: Plug-In Flag
    if(ScalerGetBit_EXINT(P38_28_VBY1_IRQ_CTRL, (_BIT6 | _BIT4)) == (_BIT6 | _BIT4))
    {
        // Set LOCKN Interrupt Enable
        ScalerSetBit_EXINT(P38_28_VBY1_IRQ_CTRL, ~(_BIT7 | _BIT5 | _BIT4 | _BIT1 | _BIT0), _BIT7);

        // Disable HPTDN Interrupt
        ScalerSetBit_EXINT(P38_28_VBY1_IRQ_CTRL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), 0x00);

        // Set UnLOCKN Status: None
        g_stVboInfo.b1VboLocknRippedOff = _FALSE;
    }

    // LOCKN: LOCK-In Flag
    if(ScalerGetBit_EXINT(P38_28_VBY1_IRQ_CTRL, (_BIT7 | _BIT5)) == (_BIT7 | _BIT5))
    {
        // Write Clear the Lock Flag
        ScalerSetBit_EXINT(P38_28_VBY1_IRQ_CTRL, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), _BIT5);

        // Set LOCKN Status: Success
        g_stVboInfo.b1VboLocknStatus = _SUCCESS;
    }

    // LOCKN: Un-LOCK Flag
    // HTPDN: Un-Plug Flag
    // if((ScalerGetBit_EXINT(P38_28_VBY1_IRQ_CTRL, (_BIT3 | _BIT1)) == (_BIT3 | _BIT1)) || (ScalerGetBit_EXINT(P38_28_VBY1_IRQ_CTRL, (_BIT2 | _BIT0)) == (_BIT2 | _BIT0)))

    // LOCKN: Un-LOCK Flag
    if(ScalerGetBit_EXINT(P38_28_VBY1_IRQ_CTRL, (_BIT3 | _BIT1)) == (_BIT3 | _BIT1))
    {
        // Write Clear the UnLock Flag
        ScalerSetBit_EXINT(P38_28_VBY1_IRQ_CTRL, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), _BIT1);

#if(_PANEL_VBO_UNLOCK_MUTE_BY_FW_POLLING == _OFF)
        // Backlight Turn Off when CDR unlock
        PCB_BACKLIGHT_POWER_PIN(_LIGHT_CONTROL_OFF);
#endif
        // Set UnLOCKN Status: Ripped off
        g_stVboInfo.b1VboLocknRippedOff = _TRUE;

        // Set LOCKN Status: Fail
        g_stVboInfo.b1VboLocknStatus = _FAIL;
    }
}

#endif // #if(_PANEL_STYLE == _PANEL_LVDS)

#if((_FRC_SUPPORT == _ON) || (_OD_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Set display DVF mode by V freq.
// Input Value  : stDVCustomizedFreq --> custim V freq. range
// Output Value : None
//--------------------------------------------------
BYTE ScalerDisplaySelectDVFMode(void)
{
#if(_FRC_SUPPORT == _ON)
    if(GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P)
    {
#if(_FREESYNC_SUPPORT == _ON)
        if(GET_FREESYNC_ENABLED() == _TRUE)
        {
            return _1_IVF;
        }
        else
#endif
        {
#if(_FORCE_TO_FREE_RUN_SUPPORT == _ON)
            return _PANEL_TYP_FRAME_RATE_FREE_RUN;
#else
            // margin only for narrow range frequency and current frequency is approching typical frequency
            if(((g_stDVCustomizedFreq.usMaxFreq - g_stDVCustomizedFreq.usMinFreq) < (g_stDVCustomizedFreq.usTypFreq >> 4)) &&
               (abs(g_stMDomainInputData.usVFreq - g_stDVCustomizedFreq.usTypFreq) < (g_stDVCustomizedFreq.usTypFreq >> 4)))
            {
                g_stDVCustomizedFreq.usMaxFreq += _FRAME_SYNC_MARGIN;
                g_stDVCustomizedFreq.usMinFreq -= _FRAME_SYNC_MARGIN;
            }

            if((g_stMDomainInputData.usVFreq <= (g_stDVCustomizedFreq.usMaxFreq)) &&
               (g_stMDomainInputData.usVFreq >= (g_stDVCustomizedFreq.usMinFreq)))
            {
                return _1_IVF;
            }
            else
            {
                if((g_stMDomainInputData.usVFreq <= (g_stDVCustomizedFreq.usMaxFreq / 2)) &&
                   (g_stMDomainInputData.usVFreq >= (g_stDVCustomizedFreq.usMinFreq / 2))) // DVF = 2 * IVF
                {
                    // For 1080p_30
                    return _2_IVF;
                }
                else if((g_stMDomainInputData.usVFreq <= (g_stDVCustomizedFreq.usMaxFreq * 2 / 5)) &&
                        (g_stMDomainInputData.usVFreq >= (g_stDVCustomizedFreq.usMinFreq * 2 / 5))) // DVF = 2.5 * IVF
                {
                    // For 1080p_25, 1080p_24
                    return _2_5_IVF;
                }
                else if((g_stMDomainInputData.usVFreq <= (g_stDVCustomizedFreq.usMaxFreq / 3)) &&
                        (g_stMDomainInputData.usVFreq >= (g_stDVCustomizedFreq.usMinFreq / 3))) // DVF = 3 * IVF
                {
                    return _3_IVF;
                }
                else
                {
                    return _PANEL_TYP_FRAME_RATE_FREE_RUN;
                }
            }
#endif
        }
    }
    else
    {
        return _PANEL_TYP_FRAME_RATE_FREE_RUN;
    }
#else // else of #if(_FRC_SUPPORT == _ON)

    return _1_IVF;

#endif // End of #if(_FRC_SUPPORT == _ON)
}

//--------------------------------------------------
// Description  : Set DVfreq.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplaySetDVFreq(void)
{
    switch(GET_MEMORY_DVF_SELECT())
    {
        case _1_IVF:
#if(_FRC_SUPPORT == _ON)
#if(_FREESYNC_SUPPORT == _ON)
            if(GET_FREESYNC_ENABLED() == _TRUE)
            {
                g_usDVFreq = g_usFREESYNCVFreq;
            }
            else
#endif
#endif
            {
                g_usDVFreq = g_stMDomainInputData.usVFreq;
            }
            break;

#if(_FRC_SUPPORT == _ON)
        case _2_IVF:
            g_usDVFreq = 2 * g_stMDomainInputData.usVFreq;
            break;

        case _3_IVF:
            g_usDVFreq = 3 * g_stMDomainInputData.usVFreq;
            break;

        case _5_4_IVF:
            g_usDVFreq = 4 * g_stMDomainInputData.usVFreq / 5;
            break;

        case _6_5_IVF:
            g_usDVFreq = 5 * g_stMDomainInputData.usVFreq / 6;
            break;

        case _2_5_IVF:
            g_usDVFreq = 5 * g_stMDomainInputData.usVFreq / 2;
            break;

        case _PANEL_TYP_FRAME_RATE_FREE_RUN:
            g_usDVFreq = g_stDVCustomizedFreq.usTypFreq;
            break;
#endif

        default:
            g_usDVFreq = g_stMDomainInputData.usVFreq;
            break;
    }
}

#endif // End of #if((_FRC_SUPPORT == _ON) || (_OD_SUPPORT == _ON))
