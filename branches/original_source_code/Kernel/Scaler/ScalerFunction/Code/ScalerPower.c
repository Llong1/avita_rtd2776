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
// ID Code      : ScalerPower.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_POWER__

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


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerPowerXtalPower(BYTE ucOn);
void ScalerPowerGroupAIsolation(BYTE ucOn);
void ScalerPowerGroupBIsolation(BYTE ucOn);
void ScalerPowerGroupBPowerCut(BYTE ucOn);
void ScalerPowerRecoverBGroupIsolationData(void);
void ScalerPowerRecoverDGroupIsolationData(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Xtal Power Control.
// Input Value  : ucOn    --> On/Off Select.
// Output Value : None
//--------------------------------------------------
void ScalerPowerXtalPower(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // Xtal has power down
        if(ScalerGetBit(P80_0E_XTAL_CTRL0, _BIT7) == 0x00)
        {
            // Bit4~3 : 00 --> XI/XO Pad Driving to Strong
            ScalerSetBit(P80_0F_XTAL_CTRL1, ~(_BIT4 | _BIT3), 0x00);

            // Power On External Xtal
            ScalerSetBit(P80_0E_XTAL_CTRL0, ~_BIT7, _BIT7);

            // Waiting for xtal stable.
            ScalerTimerDelayXms(6);
        }

        // Bit4~3 : 00 --> XI/XO Pad Driving to weak
        ScalerSetBit(P80_0F_XTAL_CTRL1, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
    }
    else
    {
        // Power down External Xtal
        ScalerSetBit(P80_0E_XTAL_CTRL0, ~_BIT7, 0x00);

        // Bit4~3 : 00 --> XI/XO Pad Driving to weak
        ScalerSetBit(P80_0F_XTAL_CTRL1, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
    }
}

//--------------------------------------------------
// Description  : Group A Isolation on/off
// Input Value  : ON --> Group A(Low Power) ; OFF --> Group A (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupAIsolation(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // Analog isolation on
        ScalerSetBit(P0_F0_VCCKOFF_CONTROL0, ~_BIT4, _BIT4);

        // Digital isolation on
        ScalerSetBit(P0_09_GA_POWER_CTRL, ~_BIT1, _BIT1);
    }
    else
    {
        // Digital isolation off
        ScalerSetBit(P0_09_GA_POWER_CTRL, ~_BIT1, 0x00);

        // Analog isolation off
        ScalerSetBit(P0_F0_VCCKOFF_CONTROL0, ~_BIT4, 0x00);

        // Wait for VCCK_OFF Power On Stable
        POLLING_VCCK_OFF_STATUS(_VCCK_OFF_TIME_POLLING_POWER_ON);
    }
}

//--------------------------------------------------
// Description  : Group B Isolation on/off
// Input Value  : ON --> Group B(Low Power) ; OFF --> Group B (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupBIsolation(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // Analog isolation on
        ScalerSetBit(P0_F0_VCCKOFF_CONTROL0, ~_BIT3, _BIT3);

        // Digital isolation on
        ScalerSetBit(PC0_0A_GB_POWER_CTRL, ~_BIT1, _BIT1);
    }
    else
    {
        // Digital isolation off
        ScalerSetBit(PC0_0A_GB_POWER_CTRL, ~_BIT1, 0x00);

        // Analog isolation off
        ScalerSetBit(P0_F0_VCCKOFF_CONTROL0, ~_BIT3, 0x00);
    }
}

//--------------------------------------------------
// Description  : Group B Power on/off
// Input Value  : ON --> Group B(Low Power) ; OFF --> Group B (Normal Operation)
// Output Value : None
//--------------------------------------------------
void ScalerPowerGroupBPowerCut(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        // Strong power off
        ScalerSetBit(PC0_0A_GB_POWER_CTRL, ~_BIT5, 0x00);

        // Weak power off
        ScalerSetBit(PC0_0A_GB_POWER_CTRL, ~_BIT4, 0x00);
    }
    else
    {
        // Group B power block power cut on
        if((ScalerGetBit(P0_F0_VCCKOFF_CONTROL0, _BIT3) == _BIT3) || (ScalerGetBit(PC0_0A_GB_POWER_CTRL, _BIT1) == _BIT1))
        {
            // Weak power on
            ScalerSetBit(PC0_0A_GB_POWER_CTRL, ~_BIT4, _BIT4);

            // Wait for weak power on flag
            pData[0] = 50;

            while((ScalerGetBit(PC0_0A_GB_POWER_CTRL, _BIT6) != _BIT6) && (pData[0]-- > 0))
            {
                Delay5us(g_ucDelay5usN);
            }

            // Strong power on
            ScalerSetBit(PC0_0A_GB_POWER_CTRL, ~_BIT5, _BIT5);

            // Wait for strong power on flag
            pData[0] = 50;

            while((ScalerGetBit(PC0_0A_GB_POWER_CTRL, _BIT7) != _BIT7) && (pData[0]-- > 0))
            {
                Delay5us(g_ucDelay5usN);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Recover The setting of Group B Power Cut Area.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPowerRecoverBGroupIsolationData(void)
{
    //////////////////////// Audio DAC block start ///////////////////////////////

    //////////////////////// Audio DAC block End /////////////////////////////////

}

//--------------------------------------------------
// Description  : Recover The setting of Group D Power Cut Area.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPowerRecoverDGroupIsolationData(void)
{
    //////////////////////// DPLL video GDI2~5 block start ///////////////////////

    //////////////////////// DPLL video GDI2~5 block End /////////////////////////


    //////////////////////// DPLL audio GDI2~5 block start ///////////////////////

    //////////////////////// DPLL audio GDI2~5 block End /////////////////////////


    //////////////////////// HDMI1.4 Phy GDI2~5 block start //////////////////////

    //////////////////////// HDMI1.4 Phy GDI2~5 block End ////////////////////////


    //////////////////////// HDMI1.4 Phy DFE GDI2~5 block start //////////////////

    //////////////////////// HDMI1.4 Phy DFE GDI2~5 block End ////////////////////
}
