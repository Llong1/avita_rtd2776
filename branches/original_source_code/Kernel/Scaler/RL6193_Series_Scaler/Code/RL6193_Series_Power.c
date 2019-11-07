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
// ID Code      : RL6193_Series_Power.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_MHL_PS_WITHOUT_POWERCUT_SUPPORT == _ON)
#define GET_POWER_MHL_NO_POWERCUT()           (g_bPowerMhlNoPowercut)
#define SET_POWER_MHL_NO_POWERCUT()           (g_bPowerMhlNoPowercut = _TRUE)
#define CLR_POWER_MHL_NO_POWERCUT()           (g_bPowerMhlNoPowercut = _FALSE)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_MHL_PS_WITHOUT_POWERCUT_SUPPORT == _ON)
bit g_bPowerMhlNoPowercut = 0;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
BYTE ScalerPowerIsolation(EnumPowerAction enumSwitch);
void ScalerPowerAllGroupPowerCutReset(BYTE ucOn);
void ScalerPowerGroupCIsolation(BYTE ucOn);
void ScalerPowerGroupDIsolation(BYTE ucOn);
void ScalerPowerGroupEIsolation(BYTE ucOn);
void ScalerPowerGroupAPowerCut(BYTE ucOn);
void ScalerPowerGroupCPowerCut(BYTE ucOn);
void ScalerPowerGroupDPowerCut(BYTE ucOn);
void ScalerPowerGroupEPowerCut(BYTE ucOn);
void ScalerPowerRecoverAGroupIsolationData(void);
void ScalerPowerRecoverCGroupIsolationData(void);
void ScalerPowerRecoverEGroupIsolationData(void);

#if(_MHL_PS_WITHOUT_POWERCUT_SUPPORT == _ON)
void ScalerPowerSetMHLNoPowerCut(void);
void ScalerPowerClrMHLNoPowerCut(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Power cut block flow
// Input Value  : enumSwitch    --> Power action description.
// Output Value : return power group enter isolation area
//--------------------------------------------------
BYTE ScalerPowerIsolation(EnumPowerAction enumSwitch)
{
    BYTE ucPowerIsoFlg = 0x00;

    switch(enumSwitch)
    {
        case _POWER_ACTION_NORMAL_TO_PS:
        case _POWER_ACTION_NOSUPPORT_PS_TO_PS:
        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_AC_ON_INITIAL:
        case _POWER_ACTION_NOSUPPORT_PS_TO_OFF:
        case _POWER_ACTION_FAKE_PS_TO_OFF:

            // Group A block isolation control
            ScalerPowerGroupAIsolation(_ON);
            ucPowerIsoFlg |= _BIT0;

            // Group B block isolation control
            ScalerPowerGroupBIsolation(_ON);
            ucPowerIsoFlg |= _BIT1;

            // Group C block isolation control
            ScalerPowerGroupCIsolation(_ON);
            ucPowerIsoFlg |= _BIT2;

            // Group D block isolation control
            ScalerPowerGroupDIsolation(_ON);
            ucPowerIsoFlg |= _BIT3;

            // Group E block isolation control
            ScalerPowerGroupEIsolation(_ON);
            ucPowerIsoFlg |= _BIT4;

            // Group B power control
            ScalerPowerGroupBPowerCut(_ON);

            // Group C power control
            ScalerPowerGroupCPowerCut(_ON);

            // Group D power control
            ScalerPowerGroupDPowerCut(_ON);

            // Group E power control
            ScalerPowerGroupEPowerCut(_ON);

            // Group A power control control by GPIO
            ScalerPowerGroupAPowerCut(_ON);

            break;

        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:

            // All power group Reset
            ScalerPowerAllGroupPowerCutReset(_ON);

            // Group A power supply control by GPIO
            ScalerPowerGroupAPowerCut(_OFF);

            // Group B power control
            ScalerPowerGroupBPowerCut(_OFF);

            // Group C power control
            ScalerPowerGroupCPowerCut(_OFF);

            // Group D power control
            ScalerPowerGroupDPowerCut(_OFF);

            // Group E power control
            ScalerPowerGroupEPowerCut(_OFF);

            // Group A block isolation control
            ScalerPowerGroupAIsolation(_OFF);

            // Group B block isolation control
            ScalerPowerGroupBIsolation(_OFF);

            // Group C block isolation control
            ScalerPowerGroupCIsolation(_OFF);

            // Group D block isolation control
            ScalerPowerGroupDIsolation(_OFF);

            // Group E block isolation control
            ScalerPowerGroupEIsolation(_OFF);

            // All power group Relase
            ScalerPowerAllGroupPowerCutReset(_OFF);

            break;

        case _POWER_ACTION_NORMAL_TO_NOSUPPORT_PS:

            break;

        case _POWER_ACTION_PS_TO_OFF:

            break;

        default:
            break;
    }

    return ucPowerIsoFlg;
}

//--------------------------------------------------
// Description  : All Group Power reset
// Input Value  : ON --> Reset ; OFF --> Release
// Output Value : None
//--------------------------------------------------
void ScalerPowerAllGroupPowerCutReset(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // Group A Power Cut block Reset
        ScalerSetBit(P0_09_GA_POWER_CTRL, ~_BIT0, _BIT0);

        // Group B Power Cut block Reset
        ScalerSetBit(PC0_0A_GB_POWER_CTRL, ~_BIT0, _BIT0);

        // Group C Power Cut block Reset
        ScalerSetBit(P0_0A_GC_POWER_CTRL, ~_BIT0, _BIT0);

        if((ScalerGetBit(P40_0A_GD_POWER_CTRL, _BIT1) == _BIT1) || (ScalerGetBit(P0_F0_VCCKOFF_CONTROL0, _BIT1) == _BIT1))
        {
            // Group D Power Cut block Reset
            ScalerSetBit(P40_0A_GD_POWER_CTRL, ~_BIT0, _BIT0);
        }

        if((ScalerGetBit(P80_0A_GE_POWER_CTRL, _BIT1) == _BIT1) || (ScalerGetBit(P0_F0_VCCKOFF_CONTROL0, _BIT0) == _BIT0))
        {
            // Group E Power Cut block Reset
            ScalerSetBit(P80_0A_GE_POWER_CTRL, ~_BIT0, _BIT0);
        }
    }
    else
    {
        // Group A Power Cut block Relase
        ScalerSetBit(P0_09_GA_POWER_CTRL, ~_BIT0, 0x00);

        // Group B Power Cut block Relase
        ScalerSetBit(PC0_0A_GB_POWER_CTRL, ~_BIT0, 0x00);

        // Group C Power Cut block Relase
        ScalerSetBit(P0_0A_GC_POWER_CTRL, ~_BIT0, 0x00);

        // Group D Power Cut block Relase
        ScalerSetBit(P40_0A_GD_POWER_CTRL, ~_BIT0, 0x00);

        // Group E Power Cut block Relase
        ScalerSetBit(P80_0A_GE_POWER_CTRL, ~_BIT0, 0x00);
    }
}

//--------------------------------------------------
// Description  : Group C Isolation on/off
// Input Value  : ON --> Group C(Low Power) ; OFF --> Group C (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupCIsolation(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // Analog isolation on
        ScalerSetBit(P0_F0_VCCKOFF_CONTROL0, ~_BIT2, _BIT2);

        // Digital isolation on
        ScalerSetBit(P0_0A_GC_POWER_CTRL, ~_BIT1, _BIT1);
    }
    else
    {
        // Digital isolation off
        ScalerSetBit(P0_0A_GC_POWER_CTRL, ~_BIT1, 0x00);

        // Analog isolation off
        ScalerSetBit(P0_F0_VCCKOFF_CONTROL0, ~_BIT2, 0x00);
    }
}

//--------------------------------------------------
// Description  : Group D Isolation on/off
// Input Value  : ON --> Group D(Low Power) ; OFF --> Group D (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupDIsolation(BYTE ucOn)
{
    if(ucOn == _ON)
    {
#if(_MHL_PS_WITHOUT_POWERCUT_SUPPORT == _ON)
        if(GET_POWER_MHL_NO_POWERCUT() == _FALSE)
#endif
        {
            // Analog isolation on
            ScalerSetBit(P0_F0_VCCKOFF_CONTROL0, ~_BIT1, _BIT1);
        }

        // Digital isolation on
        ScalerSetBit(P40_0A_GD_POWER_CTRL, ~_BIT1, _BIT1);
    }
    else
    {
        // Digital isolation off
        ScalerSetBit(P40_0A_GD_POWER_CTRL, ~_BIT1, 0x00);

        // Analog isolation off
        ScalerSetBit(P0_F0_VCCKOFF_CONTROL0, ~_BIT1, 0x00);
    }
}

//--------------------------------------------------
// Description  : Group E Isolation on/off
// Input Value  : enumSwitch = Power Switch,ON --> Group E(Low Power) ; OFF --> Group E (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupEIsolation(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // Analog isolation on
        ScalerSetBit(P0_F0_VCCKOFF_CONTROL0, ~_BIT0, _BIT0);

        // Digital isolation on
        ScalerSetBit(P80_0A_GE_POWER_CTRL, ~_BIT1, _BIT1);
    }
    else
    {
        // Digital isolation off
        ScalerSetBit(P80_0A_GE_POWER_CTRL, ~_BIT1, 0x00);

        // Analog isolation off
        ScalerSetBit(P0_F0_VCCKOFF_CONTROL0, ~_BIT0, 0x00);
    }
}

//--------------------------------------------------
// Description  : Group A Power on/off
// Input Value  : ON --> Group A(Low Power) ; OFF --> Group A (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupAPowerCut(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        PCB_VCCK_OFF_POWER(_VCCK_OFF_POWER_OFF);
        PCB_DDR_POWER(_DDR_POWER_OFF);

        ScalerTimerDelayXms(200);
    }
    else
    {
        // Group A power block power cut on
        if((ScalerGetBit(P0_F0_VCCKOFF_CONTROL0, _BIT4) == _BIT4) || (ScalerGetBit(P0_09_GA_POWER_CTRL, _BIT1) == _BIT1))
        {
            PCB_DDR_POWER(_DDR_POWER_ON);

            // Wait for DDR stable, can't delete
            ScalerTimerDelayXms(10);

            PCB_VCCK_OFF_POWER(_VCCK_OFF_POWER_ON);

            // Wait for 1.5V stable, can't delete
            ScalerTimerDelayXms(10);
        }
    }
}

//--------------------------------------------------
// Description  : Group C Power on/off
// Input Value  : ON --> Group C(Low Power) ; OFF --> Group C (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupCPowerCut(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // Strong power off
        ScalerSetBit(P0_0A_GC_POWER_CTRL, ~_BIT5, 0x00);

        // Weak power off
        ScalerSetBit(P0_0A_GC_POWER_CTRL, ~_BIT4, 0x00);
    }
    else
    {
        // Group C power block power cut on
        if((ScalerGetBit(P0_F0_VCCKOFF_CONTROL0, _BIT2) == _BIT2) || (ScalerGetBit(P0_0A_GC_POWER_CTRL, _BIT1) == _BIT1))
        {
            // Weak power on
            ScalerSetBit(P0_0A_GC_POWER_CTRL, ~_BIT4, _BIT4);

            // Wait for weak power on flag
            pData[0] = 50;

            while((ScalerGetBit(P0_0A_GC_POWER_CTRL, _BIT6) != _BIT6) && (pData[0]-- > 0))
            {
                Delay5us(g_ucDelay5usN);
            }

            // Strong power on
            ScalerSetBit(P0_0A_GC_POWER_CTRL, ~_BIT5, _BIT5);

            // Wait for strong power on flag
            pData[0] = 50;

            while((ScalerGetBit(P0_0A_GC_POWER_CTRL, _BIT7) != _BIT7) && (pData[0]-- > 0))
            {
                Delay5us(g_ucDelay5usN);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Group D Power on/off
// Input Value  : ON --> Group D(Low Power) ; OFF --> Group D (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupDPowerCut(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // Strong power off
        ScalerSetBit(P40_0A_GD_POWER_CTRL, ~_BIT5, 0x00);

        // Weak power off
        ScalerSetBit(P40_0A_GD_POWER_CTRL, ~_BIT4, 0x00);
    }
    else
    {
        // Group D power block power cut on
        if((ScalerGetBit(P0_F0_VCCKOFF_CONTROL0, _BIT1) == _BIT1) || (ScalerGetBit(P40_0A_GD_POWER_CTRL, _BIT1) == _BIT1))
        {
            // Weak power on
            ScalerSetBit(P40_0A_GD_POWER_CTRL, ~_BIT4, _BIT4);

            // Wait for weak power on flag
            pData[0] = 50;

            while((ScalerGetBit(P40_0A_GD_POWER_CTRL, _BIT6) != _BIT6) && (pData[0]-- > 0))
            {
                Delay5us(g_ucDelay5usN);
            }

            // Strong power on
            ScalerSetBit(P40_0A_GD_POWER_CTRL, ~_BIT5, _BIT5);

            // Wait for strong power on flag
            pData[0] = 50;

            while((ScalerGetBit(P40_0A_GD_POWER_CTRL, _BIT7) != _BIT7) && (pData[0]-- > 0))
            {
                Delay5us(g_ucDelay5usN);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Group E Power on/off
// Input Value  : ON --> Group E(Low Power) ; OFF --> Group E (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupEPowerCut(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // Strong power off
        ScalerSetBit(P80_0A_GE_POWER_CTRL, ~_BIT5, 0x00);

        // Weak power off
        ScalerSetBit(P80_0A_GE_POWER_CTRL, ~_BIT4, 0x00);
    }
    else
    {
        // Group E power block power cut on
        if((ScalerGetBit(P0_F0_VCCKOFF_CONTROL0, _BIT0) == _BIT0) || (ScalerGetBit(P80_0A_GE_POWER_CTRL, _BIT1) == _BIT1))
        {
            // Weak power on
            ScalerSetBit(P80_0A_GE_POWER_CTRL, ~_BIT4, _BIT4);

            // Wait for weak power on flag
            pData[0] = 50;

            while((ScalerGetBit(P80_0A_GE_POWER_CTRL, _BIT6) != _BIT6) && (pData[0]-- > 0))
            {
                Delay5us(g_ucDelay5usN);
            }

            // Strong power on
            ScalerSetBit(P80_0A_GE_POWER_CTRL, ~_BIT5, _BIT5);

            // Wait for strong power on flag
            pData[0] = 50;

            while((ScalerGetBit(P80_0A_GE_POWER_CTRL, _BIT7) != _BIT7) && (pData[0]-- > 0))
            {
                Delay5us(g_ucDelay5usN);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Recover The setting of Group A Power Cut Area.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPowerRecoverAGroupIsolationData(void)
{
    //////////////////////// Pin Share Start /////////////////////////////////////

    PCB_GPIO_OFF_REGION_INITIAL_SETTING();

    ScalerPinsharePowerOnReset();

    //////////////////////// Pin Share End /////////////////////////////////////

    //////////////////////// LVDS + LVDSPLL and VBO block start //////////////////

#if(_PANEL_STYLE == _PANEL_LVDS)
    // LVDS Port Power On recover
    ScalerDisplayLvdsInitialTable();
#elif(_PANEL_STYLE == _PANEL_VBO)
    // VBO Power On recover
    ScalerDisplayVboInitialTable();
#endif

    //////////////////////// LVDS + LVDSPLL and VBO block End ////////////////////


    //////////////////////// DPLL/MPLL/DDR PLL block start ///////////////////////

    // DPLL power up
    ScalerPLLSetDPLLReset();

    //////////////////////// DPLL/MPLL/DDR PLL  block End ////////////////////////


    //////////////////////// DDR DLL + DDR Delaychain start //////////////////////

    //////////////////////// DDR DLL + DDR Delaychain End ////////////////////////
}

//--------------------------------------------------
// Description  : Recover The setting of Group C Power Cut Area.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPowerRecoverCGroupIsolationData(void)
{
    //////////////////////// GDI Tx (eDP)block start /////////////////////////////

#if(_DP_TX_SUPPORT == _ON)
    // AC_ON_TO_NORMAL or OFF_TO_NORMAL or PS_TO_NORMAL
    ScalerSyncDpTxPowerProc(_POWER_ACTION_OFF_TO_NORMAL);
#endif

#if(_PANEL_STYLE == _PANEL_DPTX)
#if(_PANEL_DPTX_LINK_RATE != _PANEL_DPTX_LINK_HBR2)

#if(_DISPLAY_DP_TX_PORT_1 == _ON)
    // Initial DPTx1
    ScalerDisplayDPTx1Initial();
#endif

#if(_DISPLAY_DP_TX_PORT_2 == _ON)
    // Initial DPTx2
    ScalerDisplayDPTx2Initial();
#endif

#else
    // Set Dptx initial setting
    ScalerDisplayDPTxInitial();
#endif // End of #if(_PANEL_DPTX_LINK_RATE != _PANEL_DPTX_LINK_HBR2)
#endif // End of #if(_PANEL_STYLE == _PANEL_DPTX)

    //////////////////////// GDI Tx (eDP) block End //////////////////////////////
}

//--------------------------------------------------
// Description  : Recover The setting of Group E Power Cut Area.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPowerRecoverEGroupIsolationData(void)
{
    //////////////////////// DPLL video GDI0~1 block start ///////////////////////

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    // Set R0' Available HW Mode
    ScalerSetBit(PB_1A_HDCP_IRQ, ~(_BIT5 | _BIT4), _BIT5);

    // Enable DP Link Integrity Enable
    ScalerSetBit(PB_1B_HDCP_INTGT_VRF, ~_BIT7, _BIT7);

    // DP Mac Clock Select to Xtal Clock
    ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT6, _BIT6);

    if(ScalerGetBit(PB_20_HDCP_DEBUG, _BIT7) == _BIT7)
    {
        // HDCP R0 Calculate
        ScalerSetBit(PB_63_DUMMY2, ~_BIT7, _BIT7);
        ScalerSetBit(PB_63_DUMMY2, ~_BIT7, 0x00);
    }
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    // Set R0' Available HW Mode
    ScalerSetBit(PB0_1A_HDCP_IRQ, ~(_BIT5 | _BIT4), _BIT5);

    // Enable DP Link Integrity Enable
    ScalerSetBit(PB0_1B_HDCP_INTGT_VRF, ~_BIT7, _BIT7);

    // DP Mac Clock Select to Xtal Clock
    ScalerSetBit(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT6, _BIT6);

    if(ScalerGetBit(PB0_20_HDCP_DEBUG, _BIT7) == _BIT7)
    {
        // HDCP R0 Calculate
        ScalerSetBit(PB0_63_DUMMY2, ~_BIT7, _BIT7);
        ScalerSetBit(PB0_63_DUMMY2, ~_BIT7, 0x00);
    }
#endif

    //////////////////////// DPLL video GDI0~1 block End /////////////////////////


    //////////////////////// DPLL audio GDI0~1 block start ///////////////////////

    //////////////////////// DPLL audio GDI0~1 block End /////////////////////////


    //////////////////////// DPLL MST to SST0/1 block start //////////////////////

    //////////////////////// DPLL MST to SST0/1 block End /////////////////////////


    //////////////////////// HDMI2.0/DP1.2 Phy GDI0~1 block start /////////////////

    //////////////////////// HDMI2.0/DP1.2 Phy GDI0~1 block End ///////////////////


    //////////////////////// HDMI2.0/DP1.2 Phy DFE GDI2~5 block start /////////////

    //////////////////////// HDMI2.0/DP1.2 Phy DFE GDI2~5 block End ///////////////


    //////////////////////// Format Conversion block start ////////////////////////

    //////////////////////// Format Conversion block End //////////////////////////
}

#if(_MHL_PS_WITHOUT_POWERCUT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Power Fake Saving
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPowerSetMHLNoPowerCut(void)
{
    SET_POWER_MHL_NO_POWERCUT();
}

//--------------------------------------------------
// Description  : Clr Power Fake Saving
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPowerClrMHLNoPowerCut(void)
{
    CLR_POWER_MHL_NO_POWERCUT();
}
#endif
