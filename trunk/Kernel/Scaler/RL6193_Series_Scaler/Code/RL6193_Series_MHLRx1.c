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
// ID Code      : RL6193_Series_MHLRx1.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
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
void ScalerMHLRx1ModeMHLSetting(void);
void ScalerMHLRx1ModeHdmiSetting(void);
void ScalerMHLRx1InitialSettings(void);
void ScalerMHLRx1CBUSPhySwitch(bit bSelect);
void ScalerMHLRx1CBUSSwitchClk(EnumClkSel enumClockSel);
void ScalerMHLRx1CBUSResetProc(void);
void ScalerMHLRx1PowerOffProc(void);
void ScalerMHLRx1IntHandler_EXINT0(void);
bit ScalerMHLRx1MscReadDevCapabilities(EnumMHLMscOffset enumMSCOffset, BYTE *pucData);
BYTE ScalerMHLRx1MscFIFOSendCommand(EnumMHLMscCommand enumMSCCommand, EnumMHLMscOffset enumMSCOffset, EnumMHLMscData enumMSCValue, BYTE ucDataLength, BYTE *pucData);
void ScalerMHLRx1MscCheckDeviceINT(void);
bit ScalerMHLRx1MscHandler(EnumDisplayRegion enumMappedRegion, BYTE ucModeState);
bit ScalerMHLRx1MscRAPHandler(void);

#if(_MHL2_UCP_SUPPORT == _ON)
BYTE ScalerMHLRx1MscUCPGetCommand(BYTE *pucKeyCode);
#endif

bit ScalerMHLRx1PSPreDetect(void);
bit ScalerMHLRx1NormalPreDetect(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : TMDS Settings when MHL Mode for D1 Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx1ModeMHLSetting(void)
{
    CLR_DIGITAL_PORT_SWITCH_TO_D1();

    // Clear CBUS Reset Flag for HTC Butterfly Debug
    CLR_MHL_RX1_CBUS_RESET_FOR_HTC_DONE();

    // Clear CBUS Reset Flag for Other Port Discovery Done
    CLR_MHL_RX1_SWITCH_PORT_DISCOVERY_DONE();

    PCB_D1_HDMI_MHL_SWITCH(_TMDS_SWITCH_MHL_CBUS);
    PCB_D1_MHL_VBUS_SWITCH(_MHL_VBUS_ON);

    // Port 1 Z0 Disable
    ScalerSetBit(PB0_A2_CMU_02, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // Disable Auto K-offset Auto Mode
    ScalerSetBit(PB0_AD_CDR_04, ~_BIT2, 0x00);

    // Enable MHL Mode
    ScalerSetBit(PB0_A0_CMU_00, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // [7] PSM = 1'b0 --> Disable TMDS Lane3 Clock Switch
    ScalerSetBit(PB0_AB_CDR_02, ~_BIT7, 0x00);

#if(_D1_CBUS_CHANNEL_SEL == _CBUS0)
    // GPIO Select to CBUS
    ScalerSetBit(P27_A1_CBUS_EN_1, ~_BIT2, 0x00);

    // Set 1k Manual Code
    ScalerSetByte(P27_A2_CBUS_RES_AUTOK_0, (((ScalerGetByte(PB_B7_BANDGAP_03) & 0xF0) >> 4) - 0x01));

    // Set 100k Manual Code
    ScalerSetByte(P27_A3_CBUS_RES_AUTOK_1, (ScalerGetByte(PB_B7_BANDGAP_03) & 0x0F));

#elif(_D1_CBUS_CHANNEL_SEL == _CBUS1)
    // GPIO Select to CBUS
    ScalerSetBit(P27_A1_CBUS_EN_1, ~_BIT3, 0x00);

    // Set 1k Manual Code
    ScalerSetByte(P27_A2_CBUS_RES_AUTOK_0, (((ScalerGetByte(PB_B7_BANDGAP_03) & 0xF0) >> 4) - 0x01));

    // Set 100k Manual Code
    ScalerSetByte(P27_A3_CBUS_RES_AUTOK_1, (ScalerGetByte(PB_B7_BANDGAP_03) & 0x0F));

#elif(_D1_CBUS_CHANNEL_SEL == _CBUS2)
    // GPIO Select to CBUS
    ScalerSetBit(P67_A1_CBUS_EN_1, ~_BIT2, 0x00);

    // Set 1k Manual Code
    ScalerSetByte(P67_A2_CBUS_RES_AUTOK_0, (((ScalerGetByte(PB_B7_BANDGAP_03) & 0xF0) >> 4) - 0x01));

    // Set 100k Manual Code
    ScalerSetByte(P67_A3_CBUS_RES_AUTOK_1, (ScalerGetByte(PB_B7_BANDGAP_03) & 0x0F));

#elif(_D1_CBUS_CHANNEL_SEL == _CBUS3)
    // GPIO Select to CBUS
    ScalerSetBit(P67_A1_CBUS_EN_1, ~_BIT3, 0x00);

    // Set 1k Manual Code
    ScalerSetByte(P67_A2_CBUS_RES_AUTOK_0, (((ScalerGetByte(PB_B7_BANDGAP_03) & 0xF0) >> 4) - 0x01));

    // Set 100k Manual Code
    ScalerSetByte(P67_A3_CBUS_RES_AUTOK_1, (ScalerGetByte(PB_B7_BANDGAP_03) & 0x0F));

#endif // End of #if(_D1_CBUS_CHANNEL_SEL == _CBUS0)

#if(_D1_DDC_CHANNEL_SEL == _DDC0)
    // Disable DDC Channel
    ScalerPinshareGpioDdcPinSwitch(_DDC0_SWITCH_GPIO);

    // Switch DDCRAM To MHL EDID
    MCU_FEB1_DDCRAM_ST_ADDRESS |= _BIT0;

    // DDC0 Disable Force Nack and disable DDC Toggle IRQ
    MCU_FFE4_DDC0_EDID_IRQ &= ~(_BIT5 | _BIT3 | _BIT1);
#elif(_D1_DDC_CHANNEL_SEL == _DDC1)
    // Disable DDC Channel
    ScalerPinshareGpioDdcPinSwitch(_DDC1_SWITCH_GPIO);

    // Switch DDCRAM To MHL EDID
    MCU_FEB1_DDCRAM_ST_ADDRESS |= _BIT1;

    // DDC1 Disable Force Nack and disable DDC Toggle IRQ
    MCU_FFE5_DDC1_EDID_IRQ &= ~(_BIT5 | _BIT3 | _BIT1);
#elif(_D1_DDC_CHANNEL_SEL == _DDC2)
    // Disable DDC Channel
    ScalerPinshareGpioDdcPinSwitch(_DDC2_SWITCH_GPIO);

    // Switch DDCRAM To MHL EDID
    MCU_FEB1_DDCRAM_ST_ADDRESS |= _BIT2;

    // DDC2 Disable Force Nack and disable DDC Toggle IRQ
    MCU_FE69_DDC2_EDID_IRQ &= ~(_BIT5 | _BIT3 | _BIT1);
#elif(_D1_DDC_CHANNEL_SEL == _DDC3)
    // Disable DDC Channel
    ScalerPinshareGpioDdcPinSwitch(_DDC3_SWITCH_GPIO);

    // Switch DDCRAM To MHL EDID
    MCU_FEB1_DDCRAM_ST_ADDRESS |= _BIT3;

    // DDC3 Disable Force Nack and disable DDC Toggle IRQ
    MCU_FE72_DDC3_EDID_IRQ &= ~(_BIT5 | _BIT3 | _BIT1);
#elif(_D1_DDC_CHANNEL_SEL == _DDC4)
    // Disable DDC Channel
    ScalerPinshareGpioDdcPinSwitch(_DDC4_SWITCH_GPIO);

    // Switch DDCRAM To MHL EDID
    MCU_FEB1_DDCRAM_ST_ADDRESS |= _BIT4;

    // DDC4 Disable Force Nack and disable DDC Toggle IRQ
    MCU_FE7B_DDC4_EDID_IRQ &= ~(_BIT5 | _BIT3 | _BIT1);
#elif(_D1_DDC_CHANNEL_SEL == _DDC5)
    // Disable DDC Channel
    ScalerPinshareGpioDdcPinSwitch(_DDC5_SWITCH_GPIO);

    // Switch DDCRAM To MHL EDID
    MCU_FEB1_DDCRAM_ST_ADDRESS |= _BIT5;

    // DDC5 Disable Force Nack and disable DDC Toggle IRQ
    MCU_FE84_DDC5_EDID_IRQ &= ~(_BIT5 | _BIT3 | _BIT1);
#endif
}

//--------------------------------------------------
// Description  : TMDS Settings when HDMI Mode for D1 Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx1ModeHdmiSetting(void)
{
    ScalerMHLRx1CBUSPhySwitch(_OFF);

    PCB_D1_HDMI_MHL_SWITCH(_TMDS_SWITCH_HDMI_HPD);
    PCB_D1_MHL_VBUS_SWITCH(_MHL_VBUS_OFF);

    // Disable MHL Mode
    ScalerSetBit(PB0_A0_CMU_00, ~(_BIT7 | _BIT6), 0x00);

    // [7] PSM = 1 --> Enable TMDS Lane3 Clock Switch
    ScalerSetBit(PB0_AB_CDR_02, ~_BIT7, _BIT7);

#if(_D1_CBUS_CHANNEL_SEL == _CBUS0)
    // GPIO Select to Hot Plug
    ScalerSetBit(P27_A1_CBUS_EN_1, ~_BIT2, _BIT2);
#elif(_D1_CBUS_CHANNEL_SEL == _CBUS1)
    // GPIO Select to Hot Plug
    ScalerSetBit(P27_A1_CBUS_EN_1, ~_BIT3, _BIT3);
#elif(_D1_CBUS_CHANNEL_SEL == _CBUS2)
    // GPIO Select to Hot Plug
    ScalerSetBit(P67_A1_CBUS_EN_1, ~_BIT2, _BIT2);
#elif(_D1_CBUS_CHANNEL_SEL == _CBUS3)
    // GPIO Select to Hot Plug
    ScalerSetBit(P67_A1_CBUS_EN_1, ~_BIT3, _BIT3);
#endif  // End of #if(_D1_CBUS_CHANNEL_SEL == _CBUS0)

#if(_D1_DDC_CHANNEL_SEL == _DDC0)
    // Enable DDC Channel
    ScalerPinshareGpioDdcPinSwitch(_DDC0_SWITCH_DDC);

    // Switch DDCRAM To HDMI EDID
    MCU_FEB1_DDCRAM_ST_ADDRESS &= ~_BIT0;

#if(_D1_EMBEDDED_DDCRAM_SIZE == _EDID_SIZE_NONE)
    // DDC0 Enable Force Nack
    MCU_FFE4_DDC0_EDID_IRQ |= _BIT5;
#endif

#elif(_D1_DDC_CHANNEL_SEL == _DDC1)
    // Enable DDC Channel
    ScalerPinshareGpioDdcPinSwitch(_DDC1_SWITCH_DDC);

    // Switch DDCRAM To HDMI EDID
    MCU_FEB1_DDCRAM_ST_ADDRESS &= ~_BIT1;

#if(_D1_EMBEDDED_DDCRAM_SIZE == _EDID_SIZE_NONE)
    // DDC1 Enable Force Nack
    MCU_FFE5_DDC1_EDID_IRQ |= _BIT5;
#endif

#elif(_D1_DDC_CHANNEL_SEL == _DDC2)
    // Enable DDC Channel
    ScalerPinshareGpioDdcPinSwitch(_DDC2_SWITCH_DDC);

    // Switch DDCRAM To HDMI EDID
    MCU_FEB1_DDCRAM_ST_ADDRESS &= ~_BIT2;

#if(_D1_EMBEDDED_DDCRAM_SIZE == _EDID_SIZE_NONE)
    // DDC2 Enable Force Nack
    MCU_FE69_DDC2_EDID_IRQ |= _BIT5;
#endif

#elif(_D1_DDC_CHANNEL_SEL == _DDC3)
    // Enable DDC Channel
    ScalerPinshareGpioDdcPinSwitch(_DDC3_SWITCH_DDC);

    // Switch DDCRAM To HDMI EDID
    MCU_FEB1_DDCRAM_ST_ADDRESS &= ~_BIT3;

#if(_D1_EMBEDDED_DDCRAM_SIZE == _EDID_SIZE_NONE)
    // DDC3 Enable Force Nack
    MCU_FE72_DDC3_EDID_IRQ |= _BIT5;
#endif

#elif(_D1_DDC_CHANNEL_SEL == _DDC4)
    // Enable DDC Channel
    ScalerPinshareGpioDdcPinSwitch(_DDC4_SWITCH_DDC);

    // Switch DDCRAM To HDMI EDID
    MCU_FEB1_DDCRAM_ST_ADDRESS &= ~_BIT4;

#if(_D1_EMBEDDED_DDCRAM_SIZE == _EDID_SIZE_NONE)
    // DDC4 Enable Force Nack
    MCU_FE7B_DDC4_EDID_IRQ |= _BIT5;
#endif

#elif(_D1_DDC_CHANNEL_SEL == _DDC5)
    // Enable DDC Channel
    ScalerPinshareGpioDdcPinSwitch(_DDC5_SWITCH_DDC);

    // Switch DDCRAM To HDMI EDID
    MCU_FEB1_DDCRAM_ST_ADDRESS &= ~_BIT5;

#if(_D1_EMBEDDED_DDCRAM_SIZE == _EDID_SIZE_NONE)
    // DDC5 Enable Force Nack
    MCU_FE84_DDC5_EDID_IRQ |= _BIT5;
#endif

#endif // End of #if(_D1_DDC_CHANNEL_SEL == _DDC0)

}

//--------------------------------------------------
// Description  : Calibration for 1K/100K and LDO Level Adjust
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx1InitialSettings(void)
{
#if(_D1_CBUS_CHANNEL_SEL == _CBUS0)
    // Adjust CBUS Input Comparator VIH = 0.9V and VIL = 0.7V
    ScalerSetByte(P27_A6_CBUS_INPUT_CONTROL, 0x09);

    // Set CBUS Min Vih
    ScalerSetBit(P27_A6_CBUS_INPUT_CONTROL, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

#if(_MHL_CBUS_LDO_HIGH == _ENABLE)
    // Set CBUS Max Driving Strength, Set LDO to 1.8V Level
    ScalerSetBit(P27_A7_CBUS_OUTPUT_CONTROL_0, ~(_BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
#else
    // Set CBUS Max Driving Strength, Set LDO to 1.65V Level
    ScalerSetBit(P27_A7_CBUS_OUTPUT_CONTROL_0, ~(_BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT0));
#endif

    // DDC1 CBUS Swap Settings
    ScalerSetBit(P6F_04_CBUS0_MAP_DDC, ~(_BIT2 | _BIT1 | _BIT0), 0x01);

#elif(_D1_CBUS_CHANNEL_SEL == _CBUS1)
    // Adjust CBUS Input Comparator VIH = 0.9V and VIL = 0.7V
    ScalerSetByte(P27_A6_CBUS_INPUT_CONTROL, 0x09);

    // Set CBUS Min Vih
    ScalerSetBit(P27_A6_CBUS_INPUT_CONTROL, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

#if(_MHL_CBUS_LDO_HIGH == _ENABLE)
    // Set CBUS Max Driving Strength, Set LDO to 1.8V Level
    ScalerSetBit(P27_A7_CBUS_OUTPUT_CONTROL_0, ~(_BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
#else
    // Set CBUS Max Driving Strength, Set LDO to 1.65V Level
    ScalerSetBit(P27_A7_CBUS_OUTPUT_CONTROL_0, ~(_BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT0));
#endif

    // DDC1 CBUS Swap Settings
    ScalerSetBit(P6F_05_CBUS1_MAP_DDC, ~(_BIT2 | _BIT1 | _BIT0), 0x01);

#elif(_D1_CBUS_CHANNEL_SEL == _CBUS2)
    // Adjust CBUS Input Comparator VIH = 0.9V and VIL = 0.7V
    ScalerSetByte(P67_A6_CBUS_INPUT_CONTROL, 0x09);

    // Set CBUS Min Vih
    ScalerSetBit(P67_A6_CBUS_INPUT_CONTROL, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

#if(_MHL_CBUS_LDO_HIGH == _ENABLE)
    // Set CBUS Max Driving Strength, Set LDO to 1.8V Level
    ScalerSetBit(P67_A7_CBUS_OUTPUT_CONTROL_0, ~(_BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
#else
    // Set CBUS Max Driving Strength, Set LDO to 1.65V Level
    ScalerSetBit(P67_A7_CBUS_OUTPUT_CONTROL_0, ~(_BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT0));
#endif

    // DDC1 CBUS Swap Settings
    ScalerSetBit(P6F_06_CBUS2_MAP_DDC, ~(_BIT2 | _BIT1 | _BIT0), 0x01);

#elif(_D1_CBUS_CHANNEL_SEL == _CBUS3)
    // Adjust CBUS Input Comparator VIH = 0.9V and VIL = 0.7V
    ScalerSetByte(P67_A6_CBUS_INPUT_CONTROL, 0x09);

    // Set CBUS Min Vih
    ScalerSetBit(P67_A6_CBUS_INPUT_CONTROL, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

#if(_MHL_CBUS_LDO_HIGH == _ENABLE)
    // Set CBUS Max Driving Strength, Set LDO to 1.8V Level
    ScalerSetBit(P67_A7_CBUS_OUTPUT_CONTROL_0, ~(_BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2));
#else
    // Set CBUS Max Driving Strength, Set LDO to 1.65V Level
    ScalerSetBit(P67_A7_CBUS_OUTPUT_CONTROL_0, ~(_BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT0));
#endif

    // DDC1 CBUS Swap Settings
    ScalerSetBit(P6F_07_CBUS3_MAP_DDC, ~(_BIT2 | _BIT1 | _BIT0), 0x01);

#endif

    // Discovery Function Power Down and System Clk Gated
    ScalerSetBit(P29_A0_CBUS_CTRL_00, ~(_BIT6 | _BIT5 | _BIT3 | _BIT2), _BIT6);

    // Set MHL 1MHz Clk Divider
    ScalerSetBit(P29_A1_CBUS_CTRL_01, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT4 | _BIT3 | _BIT2));

    // Set MHL 1KHz Clk Divider and Set Stuck Low Time to 150us
    ScalerSetBit(P29_A2_CBUS_CTRL_02, ~(_BIT4 | _BIT3 | _BIT1 | _BIT0), _BIT0);
    ScalerSetByte(P29_A3_CBUS_CTRL_03, 0xE2);

    // Set HW Bypass Wake Up Pulses Mode
    ScalerSetBit(P29_A4_CBUS_CTRL_04, ~_BIT7, _BIT7);

    // Set MHL Wake pulse boundary 14~26
    ScalerSetBit(P29_A4_CBUS_CTRL_04, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT4 | _BIT3));

    // Set Discovery Upper/Lower Bound
    ScalerSetBit(P29_A5_CBUS_CTRL_05, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x5A);

    // Set Wake Up Pulse Number to 4
    ScalerSetBit(P29_A6_CBUS_CTRL_06, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);

    // Set CBUS (PHY) Power Saving Mode to Manual Mode
    ScalerSetByte(P29_A9_CBUS_CTRL_09, 0x00);
}

//--------------------------------------------------
// Description  : Power Process for CBUS Phy for D1 Port
// Input Value  : bSelect --> _ON/_OFF
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx1CBUSPhySwitch(bit bSelect)
{
    if(bSelect == _ON)
    {
        if(ScalerGetBit(P29_A8_CBUS_CTRL_08, _BIT5) == 0x00)
        {
#if(_D1_CBUS_CHANNEL_SEL == _CBUS0)
            // GPIO Select to CBUS
            ScalerSetBit(P27_A1_CBUS_EN_1, ~_BIT2, 0x00);

            // Enable CBUS Phy, LDO, Input Comparator and Output Driver
            ScalerSetBit(P27_A0_CBUS_EN_0, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));
#elif(_D1_CBUS_CHANNEL_SEL == _CBUS1)
            // GPIO Select to CBUS
            ScalerSetBit(P27_A1_CBUS_EN_1, ~_BIT3, 0x00);

            // Enable CBUS Phy, LDO and Input Comparator
            ScalerSetBit(P27_A0_CBUS_EN_0, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), (_BIT7 | _BIT5 | _BIT3 | _BIT1));
#elif(_D1_CBUS_CHANNEL_SEL == _CBUS2)
            // GPIO Select to CBUS
            ScalerSetBit(P67_A1_CBUS_EN_1, ~_BIT2, 0x00);

            // Enable CBUS Phy, LDO, Input Comparator and Output Driver
            ScalerSetBit(P67_A0_CBUS_EN_0, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));
#elif(_D1_CBUS_CHANNEL_SEL == _CBUS3)
            // GPIO Select to CBUS
            ScalerSetBit(P67_A1_CBUS_EN_1, ~_BIT3, 0x00);

            // Enable CBUS Phy, LDO and Input Comparator
            ScalerSetBit(P67_A0_CBUS_EN_0, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), (_BIT7 | _BIT5 | _BIT3 | _BIT1));
#endif
            // Discovery Function Power On and Enable System Clk
            ScalerSetBit(P29_A0_CBUS_CTRL_00, ~(_BIT6 | _BIT5), _BIT5);

            // Enable Discovery IRQ
            ScalerSetBit(P29_A0_CBUS_CTRL_00, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0));

            // MHL Attached
            ScalerSetBit(P29_A8_CBUS_CTRL_08, ~_BIT5, _BIT5);

            // Internal IRQ Enable (Global)
            ScalerGlobalIRQControl(_ENABLE);

            EX0 = 1;
        }
    }
    else
    {
        if(ScalerGetBit(P29_A8_CBUS_CTRL_08, _BIT5) == _BIT5)
        {
#if(_D1_CBUS_CHANNEL_SEL == _CBUS0)
            // Disable CBUS Phy, LDO, Input Comparator
            ScalerSetBit(P27_A0_CBUS_EN_0, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), 0x00);
#elif(_D1_CBUS_CHANNEL_SEL == _CBUS1)
            // Disable CBUS Phy, LDO, Input Comparator
            ScalerSetBit(P27_A0_CBUS_EN_0, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), 0x00);
#elif(_D1_CBUS_CHANNEL_SEL == _CBUS2)
            // Disable CBUS Phy, LDO, Input Comparator
            ScalerSetBit(P67_A0_CBUS_EN_0, ~(_BIT6 | _BIT4 | _BIT2 | _BIT0), 0x00);
#elif(_D1_CBUS_CHANNEL_SEL == _CBUS3)
            // Disable CBUS Phy, LDO, Input Comparator
            ScalerSetBit(P67_A0_CBUS_EN_0, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), 0x00);
#endif
            // Discovery Function Power Down and System Clk Gated
            ScalerSetBit(P29_A0_CBUS_CTRL_00, ~(_BIT6 | _BIT5), _BIT6);

            // Disable Discovery IRQ
            ScalerSetBit(P29_A0_CBUS_CTRL_00, ~(_BIT2 | _BIT0), _BIT2);

            // MHL Unattached
            ScalerSetBit(P29_A8_CBUS_CTRL_08, ~_BIT5, 0x00);
        }
    }
}

//--------------------------------------------------
// Description  : Clock Select For MHL for D1 Port
// Input Value  : ucClockSel --> System refernce clock select.
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx1CBUSSwitchClk(EnumClkSel enumClockSel)
{
    if((enumClockSel == _M2PLL_CLK) && (ScalerGetBit(P29_A0_CBUS_CTRL_00, _BIT4) != 0x00))
    {
        // Gate CBUS System Clk First (In Case of Digital Clk Glitch)
        ScalerSetBit(P29_A0_CBUS_CTRL_00, ~_BIT5, 0x00);

        // MHL System Clk select to M2PLL
        ScalerSetBit(P29_A0_CBUS_CTRL_00, ~(_BIT4 | _BIT3 | _BIT2), 0x00);

        // Clear Wake Up Pulses Flag
        ScalerSetBit(P29_A0_CBUS_CTRL_00, ~_BIT3, _BIT3);

        // Sys Clk Divider
        ScalerSetBit(P29_A1_CBUS_CTRL_01, ~(_BIT7 | _BIT6 | _BIT5), (_BIT6 | _BIT5));

        // Set Debounce For Core Function Set to 2 cycles
        ScalerSetBit(P29_A2_CBUS_CTRL_02, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);

        // Upper Bound of SYNC Pulse Low Time Period
        ScalerSetByte(P29_AF_CBUS_CTRL_0F, 0xE1);

        // Lower Bound of SYNC Pulse Low Time Period
        ScalerSetByte(P29_B0_CBUS_CTRL_10, 0x83);

        // Upper Bound of SYNC Pulse High Time Period
        ScalerSetByte(P29_B1_CBUS_CTRL_11, 0x55);

        // Lower Bound of SYNC Pulse High Time Period
        ScalerSetByte(P29_B2_CBUS_CTRL_12, 0x25);

        // Absolute Threshold Time
        ScalerSetByte(P29_B4_CBUS_CTRL_14, 0x5A);

        // Parity Bit Time
        ScalerSetByte(P29_B5_CBUS_CTRL_15, 0x75);

        // Parity Error Limit
        ScalerSetBit(P29_B6_CBUS_CTRL_16, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0E);

        // Ack Bit Initial Falling Edge
        ScalerSetBit(P29_B7_CBUS_CTRL_17, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x04);

        // Ack Bit Drive Low Time
        ScalerSetBit(P29_B8_CBUS_CTRL_18, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x3A);

        // Requester Bit Time
        ScalerSetByte(P29_BA_CBUS_CTRL_1A, 0x75);

        // Check Received Ack Bit's Falling Edge
        ScalerSetBit(P29_BC_CBUS_CTRL_1C, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x7A);

        // Check Received Ack Bit's Driving Low Period Upper Bound
        ScalerSetBit(P29_BD_CBUS_CTRL_1D, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x4C);

        // Check Received Ack Bit's Driving Low Period Lower Bound
        ScalerSetBit(P29_BE_CBUS_CTRL_1E, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x24);

        // Actively Driving High Time for CBUS
        ScalerSetBit(P29_C0_CBUS_CTRL_20, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x18);

        // CBUS Requester Transmit Opportunity after Arbitration
        ScalerSetByte(P29_C2_CBUS_CTRL_22, 0x75);

        // CBUS Requester Continue After Ack
        ScalerSetByte(P29_C3_CBUS_CTRL_23, 0x3A);

        // Link Layer Timeout
        ScalerSetBit(P29_C5_CBUS_CTRL_25, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT4 | _BIT3 | _BIT2));

        // Set IIC SCL Clock Frequency
        ScalerSetByte(P29_F9_CBUS_CTRL_59, 0x11);

        // Reset CBUS Core Function After Clk Switch
        ScalerSetBit(P29_A0_CBUS_CTRL_00, ~_BIT7, _BIT7);
        ScalerSetBit(P29_A0_CBUS_CTRL_00, ~_BIT7, 0x00);

        // Enable CBUS System Clk
        ScalerSetBit(P29_A0_CBUS_CTRL_00, ~_BIT5, _BIT5);
    }
    else if((enumClockSel == _IOSC_CLK) && (ScalerGetBit(P29_A0_CBUS_CTRL_00, _BIT4) != _BIT4))
    {
        // Gate CBUS System Clk First (In Case of Digital Clk Glitch)
        ScalerSetBit(P29_A0_CBUS_CTRL_00, ~_BIT5, 0x00);

        // MHL System Clk select to IOSC (Bypass GDI Clk)
        ScalerSetBit(P29_A0_CBUS_CTRL_00, ~(_BIT4 | _BIT3 | _BIT2), _BIT4);
        ScalerSetBit(P29_A2_CBUS_CTRL_02, ~_BIT2, 0x00);

        // Clear Wake Up Pulses Flag
        ScalerSetBit(P29_A0_CBUS_CTRL_00, ~_BIT3, _BIT3);

        // Sys Clk Divider
        ScalerSetBit(P29_A1_CBUS_CTRL_01, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

        // Disable Debounce For Core Function
        ScalerSetBit(P29_A2_CBUS_CTRL_02, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

        // Upper Bound of SYNC Pulse Low Time Period
        ScalerSetByte(P29_AF_CBUS_CTRL_0F, 0x35);

        // Lower Bound of SYNC Pulse Low Time Period
        ScalerSetByte(P29_B0_CBUS_CTRL_10, 0x20);

        // Upper Bound of SYNC Pulse High Time Period
        ScalerSetByte(P29_B1_CBUS_CTRL_11, 0x14);

        // Lower Bound of SYNC Pulse High Time Period
        ScalerSetByte(P29_B2_CBUS_CTRL_12, 0x09);

        // Absolute Threshold Time
        ScalerSetByte(P29_B4_CBUS_CTRL_14, 0x15);

        // Parity Bit Time
        ScalerSetByte(P29_B5_CBUS_CTRL_15, 0x1C);

        // Parity Error Limit
        ScalerSetBit(P29_B6_CBUS_CTRL_16, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);

        // Ack Bit Initial Falling Edge
        ScalerSetBit(P29_B7_CBUS_CTRL_17, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x01);

        // Ack Bit Drive Low Time
        ScalerSetBit(P29_B8_CBUS_CTRL_18, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0D);

        // Requester Bit Time
        ScalerSetByte(P29_BA_CBUS_CTRL_1A, 0x1C);

        // Check Received Ack Bit's Falling Edge
        ScalerSetBit(P29_BC_CBUS_CTRL_1C, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x1C);

        // Check Received Ack Bit's Driving Low Period Upper Bound
        ScalerSetBit(P29_BD_CBUS_CTRL_1D, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x12);

        // Check Received Ack Bit's Driving Low Period Lower Bound
        ScalerSetBit(P29_BE_CBUS_CTRL_1E, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x05);

        // Actively Driving High Time for CBUS
        ScalerSetBit(P29_C0_CBUS_CTRL_20, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

        // CBUS Requester Transmit Opportunity after Arbitration
        ScalerSetByte(P29_C2_CBUS_CTRL_22, 0x1C);

        // CBUS Requester Continue After Ack
        ScalerSetByte(P29_C3_CBUS_CTRL_23, 0x0D);

        // Link Layer Timeout
        ScalerSetBit(P29_C5_CBUS_CTRL_25, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

        // Set IIC SCL Clock Frequency
        ScalerSetByte(P29_F9_CBUS_CTRL_59, 0x03);

        // Reset CBUS Core Function After Clk Switch
        ScalerSetBit(P29_A0_CBUS_CTRL_00, ~_BIT7, _BIT7);
        ScalerSetBit(P29_A0_CBUS_CTRL_00, ~_BIT7, 0x00);

        // Enable CBUS System Clk
        ScalerSetBit(P29_A0_CBUS_CTRL_00, ~_BIT5, _BIT5);
    }
}

//--------------------------------------------------
// Description  : MHL Cbus Reset Proc for D1 Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx1CBUSResetProc(void)
{
    // Disable Stuck Low IRQ and Clear Stuck Low Flags
    ScalerSetBit(P29_A4_CBUS_CTRL_04, ~(_BIT1 | _BIT0), _BIT1);

    // Port 1 Z0 Disable
    ScalerSetBit(PB0_A2_CMU_02, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // Disable Auto K-offset Auto Mode
    ScalerSetBit(PB0_AD_CDR_04, ~_BIT2, 0x00);

    // Manual Enable CBUS PHY PSM
#if(_D1_CBUS_CHANNEL_SEL == _CBUS0)
    ScalerSetBit(P27_A1_CBUS_EN_1, ~_BIT0, _BIT0);
#elif(_D1_CBUS_CHANNEL_SEL == _CBUS1)
    ScalerSetBit(P27_A1_CBUS_EN_1, ~_BIT1, _BIT1);
#elif(_D1_CBUS_CHANNEL_SEL == _CBUS2)
    ScalerSetBit(P67_A1_CBUS_EN_1, ~_BIT0, _BIT0);
#elif(_D1_CBUS_CHANNEL_SEL == _CBUS3)
    ScalerSetBit(P67_A1_CBUS_EN_1, ~_BIT1, _BIT1);
#endif  // End of #if(_D1_CBUS_CHANNEL_SEL == _CBUS0)

    // Force CBUS Floating
    ScalerSetBit(P29_A8_CBUS_CTRL_08, ~_BIT7, _BIT7);

    // Enable Discovery Debounce
    ScalerSetBit(P29_A8_CBUS_CTRL_08, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Reset CBUS Core Function
    ScalerSetBit(P29_A0_CBUS_CTRL_00, ~(_BIT7), _BIT7);
    ScalerSetBit(P29_A0_CBUS_CTRL_00, ~(_BIT7), 0x00);

    SET_MHL_RX1_PROCESS_STATE(_MHL_STATE_INITIAL);
    CLR_MHL_RX1_ADOPTER_ID_HBYTE();
    CLR_MHL_RX1_ADOPTER_ID_LBYTE();
    CLR_MHL_RX1_ADOPTER_ID_DONE();
    CLR_MHL_RX1_CBUS_RESET_FOR_HTC_DONE();
    CLR_MHL_RX1_MHL_VERSION();

    // Enable Discovery Done IRQ and Clear Flag
    ScalerSetBit(P29_A0_CBUS_CTRL_00, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0));
}

//--------------------------------------------------
// Description  : MHL Power Off Process for D1 Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx1PowerOffProc(void)
{
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_MHL_RX1_READY_TO_TRANSMIT);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_MHL_RX1_RECONNECT_1K);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_MHL_RX1_SWITCH_PORT_DISCOVERY_DONE);
}

//--------------------------------------------------
// Description  : Int Process for MHL for D1 Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx1IntHandler_EXINT0(void) using 1
{
    // Check Discovery Pulse
    if(ScalerGetBit_EXINT(P29_A0_CBUS_CTRL_00, (_BIT2 | _BIT0)) == (_BIT2 | _BIT0))
    {
        // Disable Discovery Done IRQ and Clear Discovery Flags
        ScalerSetBit_EXINT(P29_A0_CBUS_CTRL_00, ~(_BIT2 | _BIT0), (_BIT2));

        // Disable Discovery Debounce
        ScalerSetBit_EXINT(P29_A8_CBUS_CTRL_08, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

        // Enable Stuck Low IRQ and Clear Flag
        ScalerSetBit_EXINT(P29_A4_CBUS_CTRL_04, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        if(ScalerGetBit_EXINT(PB0_A2_CMU_02, _BIT4) == 0x00)
        {
            // Suspend Key Calculation before load key
            ScalerSetBit_EXINT(P70_AE_TMDS_RPS, ~_BIT1, 0x00);
        }

        // Enable GDI BandGap
        ScalerSetBit_EXINT(PB_B4_BANDGAP_00, ~_BIT7, _BIT7);

        // Manual Disable CBUS PHY PSM
#if(_D1_CBUS_CHANNEL_SEL == _CBUS0)
        ScalerSetBit_EXINT(P27_A1_CBUS_EN_1, ~_BIT0, 0x00);
#elif(_D1_CBUS_CHANNEL_SEL == _CBUS1)
        ScalerSetBit_EXINT(P27_A1_CBUS_EN_1, ~_BIT1, 0x00);
#elif(_D1_CBUS_CHANNEL_SEL == _CBUS2)
        ScalerSetBit_EXINT(P67_A1_CBUS_EN_1, ~_BIT0, 0x00);
#elif(_D1_CBUS_CHANNEL_SEL == _CBUS3)
        ScalerSetBit_EXINT(P67_A1_CBUS_EN_1, ~_BIT1, 0x00);
#endif  // End of #if(_D1_CBUS_CHANNEL_SEL == _CBUS0)

        // Enable RX_EN
        ScalerSetBit_EXINT(PB0_A1_CMU_01, ~_BIT7, _BIT7);

        // Port 1 Z0 Enable
        ScalerSetBit_EXINT(PB0_A2_CMU_02, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

        // Clear HDCP Flags
        ScalerSetBit_EXINT(P70_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

        SET_MHL_RX1_PROCESS_STATE(_MHL_STATE_DISCOVERY_DONE);
        SET_MHL_RX1_READY_TO_TRANSMIT();
    }

    // Check Stuck Low Flag
    if(ScalerGetBit_EXINT(P29_A4_CBUS_CTRL_04, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
    {
        // Disable Stuck Low IRQ and Clear Stuck Low Flags
        ScalerSetBit_EXINT(P29_A4_CBUS_CTRL_04, ~(_BIT1 | _BIT0), _BIT1);

        // Enable Discovery Done IRQ and Clear Flag
        ScalerSetBit_EXINT(P29_A0_CBUS_CTRL_00, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0));

        CLR_DIGITAL_PORT_SWITCH_TO_D1();

        // Port 1 Z0 Disable
        ScalerSetBit_EXINT(PB0_A2_CMU_02, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

        // Disable Auto K-offset Auto Mode
        ScalerSetBit_EXINT(PB0_AD_CDR_04, ~_BIT2, 0x00);

        // Manual Enable CBUS PHY PSM
#if(_D1_CBUS_CHANNEL_SEL == _CBUS0)
        ScalerSetBit_EXINT(P27_A1_CBUS_EN_1, ~_BIT0, _BIT0);
#elif(_D1_CBUS_CHANNEL_SEL == _CBUS1)
        ScalerSetBit_EXINT(P27_A1_CBUS_EN_1, ~_BIT1, _BIT1);
#elif(_D1_CBUS_CHANNEL_SEL == _CBUS2)
        ScalerSetBit_EXINT(P67_A1_CBUS_EN_1, ~_BIT0, _BIT0);
#elif(_D1_CBUS_CHANNEL_SEL == _CBUS3)
        ScalerSetBit_EXINT(P67_A1_CBUS_EN_1, ~_BIT1, _BIT1);
#endif  // End of #if(_D1_CBUS_CHANNEL_SEL == _CBUS0)

        // Enable Discovery Debounce
        ScalerSetBit_EXINT(P29_A8_CBUS_CTRL_08, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

#if(_MHL_CBUS_CTS_MODE == _ON)
        // Disable DDC Manual
        ScalerSetBit_EXINT(P29_C8_CBUS_CTRL_28, ~_BIT6, 0x00);
#endif
        // Reset CBUS Core Function
        ScalerSetBit_EXINT(P29_A0_CBUS_CTRL_00, ~(_BIT7), _BIT7);
        ScalerSetBit_EXINT(P29_A0_CBUS_CTRL_00, ~(_BIT7), 0x00);

        SET_MHL_RX1_PROCESS_STATE(_MHL_STATE_INITIAL);
        CLR_MHL_RX1_ADOPTER_ID_HBYTE();
        CLR_MHL_RX1_ADOPTER_ID_LBYTE();
        CLR_MHL_RX1_ADOPTER_ID_DONE();
        CLR_MHL_RX1_CBUS_RESET_FOR_HTC_DONE();
        CLR_MHL_RX1_SWITCH_PORT_DISCOVERY_DONE();
        CLR_MHL_RX1_MHL_VERSION();
    }
}

//--------------------------------------------------
// Description  : Read Device Capabilities for D1 Port
// Input Value  : enumMSCOffset --> Device Capability Offset
//                pucData --> Data to be Read
// Output Value : Success or Different Fail Situations
//--------------------------------------------------
bit ScalerMHLRx1MscReadDevCapabilities(EnumMHLMscOffset enumMSCOffset, BYTE *pucData)
{
    BYTE ucResultPacket = 0;

    if(GET_MHL_RX1_READY_TO_TRANSMIT() == _TRUE)
    {
        ucResultPacket = ScalerMHLRx1MscFIFOSendCommand(_MSC_READ_DEVCAP, enumMSCOffset, _MSC_NULL_VALUE, 0, pucData);

        switch(ucResultPacket)
        {
            case _MHL_SUCCESS: // Source reply ACK Packet

                SET_MHL_RX1_READY_TO_TRANSMIT();

                return _SUCCESS;

                break;

            case _MHL_ABORT_FAIL: // Source reply ABORT Packet

                CLR_MHL_RX1_READY_TO_TRANSMIT();
                ScalerTimerActiveTimerEvent(SEC(2.5), _SCALER_TIMER_EVENT_MHL_RX1_READY_TO_TRANSMIT);

                return _FAIL;
                break;

            case _MHL_PROTOCOL_ERROR: // Source Reply Data Packet Instead of Control Packet

                ScalerMHLRx1MscFIFOSendCommand(_MSC_ABORT, _MSC_NULL_ADDRESS, _MSC_NULL_VALUE, 0, _NULL_POINTER);

                return _FAIL;
                break;

            default: // Source Reply No Packet(Timeout) or NACK

                return _FAIL;
                break;
        }
    }
    else
    {
        return _FAIL;
    }

    return _FAIL;
}

//--------------------------------------------------
// Description  : Send MSC HPD Operation for D1 Port
// Input Value  : enumMSCType --> MSC Command
//                enumMSCOffset --> MSC Device Register
//                enumMSCValue --> MSC Device Register Field
// Output Value : Success or Different Fail Situations
//--------------------------------------------------
BYTE ScalerMHLRx1MscFIFOSendCommand(EnumMHLMscCommand enumMSCCommand, EnumMHLMscOffset enumMSCOffset, EnumMHLMscData enumMSCValue, BYTE ucDataLength, BYTE *pucData)
{
    BYTE ucTimeOut = 100;
    BYTE ucSendType = 0;
    BYTE ucWaitType = 0;
    BYTE ucI = 0;

    switch(enumMSCCommand)
    {
        case _MSC_SET_INT:
        case _MSC_MSG:

            ucSendType = _MSC_SEND_COM_OFF_DAT;
            ucWaitType = _MSC_WAIT_COMMAND;
            break;

        case _MSC_READ_DEVCAP:

            ucSendType = _MSC_SEND_COM_OFF;
            ucWaitType = _MSC_WAIT_COM_DAT;
            break;

        case _MSC_SET_HPD:

            ucSendType = _MSC_SEND_COMMAND;
            ucWaitType = _MSC_WAIT_COMMAND;
            break;

        case _MSC_ABORT:

            ucSendType = _MSC_SEND_COMMAND;
            ucWaitType = _MSC_WAIT_NULL;
            break;

        case _MSC_WRITE_BURST:

            ucSendType = _MSC_SEND_COM_OFF_DAT_COM;
            ucWaitType = _MSC_WAIT_COMMAND;
            break;

        default:

            break;
    }

    // Check If Source Has Sent An ABORT Packet
    if(ScalerGetBit(P29_CF_CBUS_CTRL_2F, _BIT2) == _BIT2)
    {
        ScalerSetByte(P29_CF_CBUS_CTRL_2F, _BIT2);

        ScalerTimerActiveTimerEvent(SEC(2.5), _SCALER_TIMER_EVENT_MHL_RX1_READY_TO_TRANSMIT);

        CLR_MHL_RX1_READY_TO_TRANSMIT();

        return _MHL_FAIL;
    }

    // Clear FIFO and Send Command Only
    ScalerSetByte(P29_DE_CBUS_CTRL_3E, (_BIT6 | ucSendType));

    // Set MSC Command
    ScalerSetByte(P29_DF_CBUS_CTRL_3F, enumMSCCommand);

    // Set MSC Offset
    ScalerSetByte(P29_E1_CBUS_CTRL_41, enumMSCOffset);

    if(enumMSCCommand == _MSC_WRITE_BURST)
    {
        // Set MSC Last Command
        ScalerSetByte(P29_E0_CBUS_CTRL_40, _MSC_EOF_PACKET);

        // Set MSC Data
        for(ucI = 0; ucI < ucDataLength; ucI++)
        {
            ScalerSetByte(P29_E2_CBUS_CTRL_42, pucData[ucI]);
        }
    }
    else if(enumMSCCommand != _MSC_READ_DEVCAP)
    {
        // Set MSC Value
        ScalerSetByte(P29_E2_CBUS_CTRL_42, enumMSCValue);
    }

    // MSC Packet and Wait Type
    ScalerSetBit(P29_E3_CBUS_CTRL_43, ~(_BIT7 | _BIT6 | _BIT1 | _BIT0), ((_MSC_PACKET << 6) | ucWaitType));

    // Send Request
    ScalerSetBit(P29_DE_CBUS_CTRL_3E, ~(_BIT7), _BIT7);

    // Check if Process is finished
    while(--ucTimeOut != 0)
    {
        if(ScalerGetBit(P29_CF_CBUS_CTRL_2F, _BIT2) == _BIT2)
        {
            // Clear Flag
            ScalerSetBit(P29_CF_CBUS_CTRL_2F, ~_BIT2, _BIT2);

            return _MHL_ABORT_FAIL;
        }
        else if((ScalerGetBit(P29_F6_CBUS_CTRL_56, _BIT7) == _BIT7) && (ScalerGetBit(P29_F7_CBUS_CTRL_57, _BIT7) == 0x00))
        {
            // Clear Flag
            ScalerSetBit(P29_F6_CBUS_CTRL_56, ~_BIT7, _BIT7);

            if(ucWaitType == _MSC_WAIT_NULL)
            {
                return _MHL_SUCCESS;
            }
            else
            {
                // Check ACK Packet
                if(ScalerGetByte(P29_E4_CBUS_CTRL_44) == _MSC_ACK_PACKET)
                {
                    if(enumMSCCommand == _MSC_READ_DEVCAP)
                    {
                        *pucData = ScalerGetByte(P29_E5_CBUS_CTRL_45);
                    }

                    return _MHL_SUCCESS;
                }
                else
                {
                    return _MHL_FAIL;
                }
            }
        }
        else if((ScalerGetBit(P29_F7_CBUS_CTRL_57, _BIT7) == _BIT7) && (ScalerGetByte(P29_D2_CBUS_CTRL_32) == _MSC_PROTOCOL_ERROR))
        {
            // Clear Flags
            ScalerSetBit(P29_F6_CBUS_CTRL_56, ~_BIT7, _BIT7);
            ScalerSetBit(P29_F7_CBUS_CTRL_57, ~_BIT7, _BIT7);
            ScalerSetByte(P29_D2_CBUS_CTRL_32, 0xFF);

            return _MHL_PROTOCOL_ERROR;
        }

        ScalerTimerDelayXms(1);
    }

    // Clear Flag
    ScalerSetBit(P29_F6_CBUS_CTRL_56, ~_BIT7, _BIT7);
    ScalerSetBit(P29_F7_CBUS_CTRL_57, ~_BIT7, _BIT7);
    ScalerSetByte(P29_D2_CBUS_CTRL_32, 0xFF);

    return _MHL_FAIL;
}

//--------------------------------------------------
// Description  : Check Write Status for D1 Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHLRx1MscCheckDeviceINT(void)
{
    WORD usTmp = 0;
    BYTE ucBirstLength = 0;
    BYTE pucWriteBurstTmp[16];

    /********************************************************/
    /******** Get MSC Command WRITE_STAT or SET_INT *********/
    /********************************************************/

    if((bit)ScalerGetBit(P29_CE_CBUS_CTRL_2E, _BIT7) == _TRUE)
    {
        //----------------------------------------------------------//
        //-------- Check DevCap Ready (DCAP_RDY, DCAP_CHG) ---------//
        //----------------------------------------------------------//
        if((((bit)ScalerGetDataPortBit(P29_AC_CBUS_CTRL_0C, _MSC_CONNECTED_RDY, _MSC_DCAP_RDY) == _TRUE) ||
            ((bit)ScalerGetDataPortBit(P29_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_DCAP_CHG) == _TRUE)))
        {
            if(GET_MHL_RX1_MHL_VERSION() == _MHL_VERSION_NULL)
            {
                // Read Source Device MHL Version
                if(ScalerMHLRx1MscReadDevCapabilities(_MSC_MHL_VERSION_01, &g_ucMHLRx1MhlVersion) == _TRUE)
                {
                    if((bit)ScalerGetDataPortBit(P29_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_DCAP_CHG) == _TRUE)
                    {
                        // Write 1 Clear DevCap_Chg Flag
                        ScalerSetDataPortByte(P29_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_DCAP_CHG);
                    }

                    // Clear Flag
                    ScalerSetBit(P29_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7);
                }
            }

            // Read Source Adopter ID
            if((GET_MHL_RX1_ADOPTER_ID_DONE() == _FALSE) && (GET_MHL_RX1_READY_TO_TRANSMIT() == _TRUE))
            {
                if((ScalerMHLRx1MscReadDevCapabilities(_MSC_ADOPTER_ID_H_03, &g_ucMHLRx1AdopterIDH) == _TRUE) &&
                   (ScalerMHLRx1MscReadDevCapabilities(_MSC_ADOPTER_ID_L_04, &g_ucMHLRx1AdopterIDL) == _TRUE))
                {
                    DebugMessageRx1("D1 MHL Adopter IDH", g_ucMHLRx1AdopterIDH);
                    DebugMessageRx1("D1 MHL Adopter IDL", g_ucMHLRx1AdopterIDL);

                    SET_MHL_RX1_ADOPTER_ID_DONE();

                    if((bit)ScalerGetDataPortBit(P29_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_DCAP_CHG) == _TRUE)
                    {
                        // Write 1 Clear DevCap_Chg Flag
                        ScalerSetDataPortByte(P29_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_DCAP_CHG);
                    }

                    // Clear Flag
                    ScalerSetBit(P29_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6));
                }
            }
        }

        //------------------------------------//
        //------ Check Request To Write ------//
        //------------------------------------//
        if((bit)ScalerGetDataPortBit(P29_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_REQ_WRT) == _TRUE)
        {
            if(ScalerMHLRx1MscSendCommand(_MSC_SET_INT, _MSC_RCHANGE_INT, _MSC_GRT_WRT) == _SUCCESS)
            {
                ScalerSetDataPortByte(P29_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_REQ_WRT);
            }
        }

        //-----------------------------------------------------------//
        //-- Check 3D Request and Reply No Support For All Timings --//
        //-----------------------------------------------------------//
        if((bit)ScalerGetDataPortBit(P29_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_3D_REQ) == _TRUE)
        {
            // 3D_VIC Header
            pucWriteBurstTmp[0] = _MHL_3D_VIC_HB;
            pucWriteBurstTmp[1] = _MHL_3D_VIC_LB;

            // Total Entries -> 0
            pucWriteBurstTmp[3] = 0x00;

            // SEQ -> 1
            pucWriteBurstTmp[4] = 0x01;

            // NUM_ENT -> 0
            pucWriteBurstTmp[5] = 0x00;

            // Checksum -> 256 - Sum{pucWriteBurstTmp[i]}
            pucWriteBurstTmp[2] = 256 - (pucWriteBurstTmp[0] + pucWriteBurstTmp[1] + pucWriteBurstTmp[3] + pucWriteBurstTmp[4] + pucWriteBurstTmp[5]);

            // 3D_DTD Header
            pucWriteBurstTmp[6] = _MHL_3D_DTD_HB;
            pucWriteBurstTmp[7] = _MHL_3D_DTD_LB;

            // Total Entries -> 0
            pucWriteBurstTmp[9] = 0x00;

            // SEQ -> 1
            pucWriteBurstTmp[10] = 0x01;

            // NUM_ENT -> 0
            pucWriteBurstTmp[11] = 0x00;

            // Checksum -> 256 - Sum{pucWriteBurstTmp[i]}
            pucWriteBurstTmp[8] = 256 - (pucWriteBurstTmp[6] + pucWriteBurstTmp[7] + pucWriteBurstTmp[9] + pucWriteBurstTmp[10] + pucWriteBurstTmp[11]);

            ucBirstLength = 6;

            if(ScalerMHLRx1MscSendCommand(_MSC_SET_INT, _MSC_RCHANGE_INT, _MSC_REQ_WRT) == _SUCCESS)
            {
                usTmp = 400;

                while((usTmp-- > 0) && ((bit)ScalerGetDataPortBit(P29_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_GRT_WRT) != _TRUE))
                {
                    ScalerTimerDelayXms(5);
                }

                if(ScalerMHLRx1MscSendWriteBurst(0x40, ucBirstLength, &pucWriteBurstTmp[0], _MHL_WRITE_BURST_WITH_REQ) == _SUCCESS)
                {
                    if(ScalerMHLRx1MscSendCommand(_MSC_SET_INT, _MSC_RCHANGE_INT, _MSC_REQ_WRT) == _SUCCESS)
                    {
                        usTmp = 400;

                        while((usTmp-- > 0) && ((bit)ScalerGetDataPortBit(P29_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_GRT_WRT) != _TRUE))
                        {
                            ScalerTimerDelayXms(5);
                        }

                        if(ScalerMHLRx1MscSendWriteBurst(0x40, ucBirstLength, &pucWriteBurstTmp[ucBirstLength], _MHL_WRITE_BURST_WITH_REQ) == _SUCCESS)
                        {
                            ScalerSetDataPortByte(P29_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_3D_REQ);

                            // Clear Flag
                            ScalerSetBit(P29_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7);
                        }
                    }
                }
            }
        }

        // Clear Flag
        ScalerSetByte(P29_CE_CBUS_CTRL_2E, (BYTE)_BIT7);
    }


    /****************************************************************/
    /******* Source Device Reading Sink Capabilities Ready **********/
    /****************************************************************/

    if((bit)ScalerGetBit(P29_CE_CBUS_CTRL_2E, _BIT6) == _TRUE)
    {
        // Read Source Adopter ID
        if((GET_MHL_RX1_ADOPTER_ID_DONE() == _FALSE) && (GET_MHL_RX1_READY_TO_TRANSMIT() == _TRUE))
        {
            // Delay for Read Adopter ID
            ScalerTimerDelayXms(70);

            if((ScalerMHLRx1MscReadDevCapabilities(_MSC_ADOPTER_ID_H_03, &g_ucMHLRx1AdopterIDH) == _TRUE) &&
               (ScalerMHLRx1MscReadDevCapabilities(_MSC_ADOPTER_ID_L_04, &g_ucMHLRx1AdopterIDL) == _TRUE))
            {
                SET_MHL_RX1_ADOPTER_ID_DONE();

                ScalerSetBit(P29_CE_CBUS_CTRL_2E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT6);
            }
        }
    }

    // Sent Command to Triger VBUS for HTC M8
    if(((GET_MHL_RX1_ADOPTER_ID_HBYTE() == _HTC_BUTTERFLY_ADOPTER_ID_HBYTE) && (GET_MHL_RX1_ADOPTER_ID_LBYTE() == _HTC_BUTTERFLY_ADOPTER_ID_LBYTE)) &&
       (GET_MHL_RX1_SENT_MSC_DCAP_RDY() == _FALSE) && (GET_MHL_RX1_PROCESS_STATE() == _MHL_STATE_SET_DEV_CAP_DONE))
    {
        ScalerMHLRx1MscSendCommand(_MSC_WRITE_STAT, _MSC_CONNECTED_RDY, _MSC_DCAP_RDY);
        DebugMessageRx1("D1 MHL Sent Devies Capabilitly Ready", 0);
        SET_MHL_RX1_SENT_MSC_DCAP_RDY();
    }

    // MHL Version Switch to 1.2 For Samsung Note4
    if(((GET_MHL_RX1_ADOPTER_ID_HBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_HBYTE) && (GET_MHL_RX1_ADOPTER_ID_LBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_LBYTE)) &&
       (GET_MHL_RX1_MHL_VERSION() >= _MHL_VERSION_3_0) && (GET_MHL_RX1_CBUS_RESET_FOR_HTC_DONE() == _FALSE))
    {
        ScalerSetDataPortByte(P29_AC_CBUS_CTRL_0C, _MSC_MHL_VERSION_01, _MHL_VERSION_1_2);

        ScalerMHLRx1MscSendCommand(_MSC_WRITE_STAT, _MSC_CONNECTED_RDY, _MSC_DCAP_RDY);

        SET_MHL_RX1_CBUS_RESET_FOR_HTC_DONE();
    }

#if(_MHL_CBUS_CTS_MODE == _ON)

    if(ScalerGetBit(P29_CE_CBUS_CTRL_2E, _BIT5) == _BIT5)
    {
        ScalerSetByte(P29_C8_CBUS_CTRL_28, _BIT6);

        ScalerSetByte(P29_CE_CBUS_CTRL_2E, _BIT5);
    }

    if(ScalerGetBit(P29_CE_CBUS_CTRL_2E, _BIT4) == _BIT4)
    {
        ScalerSetByte(P29_C8_CBUS_CTRL_28, 0x00);

        ScalerSetByte(P29_CE_CBUS_CTRL_2E, _BIT4);
    }

#endif // Enf of #if(_MHL_CBUS_CTS_MODE == _ON)
}

//--------------------------------------------------
// Description  : MSC Handler for D1 Port
// Input Value  : enumMappedRegion --> Current Active Port
//                ucModeState --> Current Mode State
// Output Value : True or False
//--------------------------------------------------
bit ScalerMHLRx1MscHandler(EnumDisplayRegion enumMappedRegion, BYTE ucModeState)
{
    // Check if Discovery State is done and send HPD & Device Capabilities Ready
    switch(GET_MHL_RX1_PROCESS_STATE())
    {
        case _MHL_STATE_INITIAL:

            ScalerTimerActiveTimerEvent(SEC(5), _SCALER_TIMER_EVENT_MHL_RX1_RECONNECT_1K);

            return _FALSE;
            break;

        case _MHL_STATE_DISCOVERY_DONE:

            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_MHL_RX1_RECONNECT_1K);

            // Enable oCBUS Priority Option for MHL2.2 CTS
            ScalerSetBit(P29_AB_CBUS_CTRL_0B, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT7 | _BIT6));

            // Modify Device Capabilities according to MHL Version
            ScalerSetDataPortByte(P29_AC_CBUS_CTRL_0C, _MSC_MHL_VERSION_01, _D1_MHL_VERSION);

            // Modify RAP/RCP/UCP Support according to MHL Version
            ScalerSetDataPortBit(P29_AC_CBUS_CTRL_0C, _MSC_FEATURE_FLAG_0A, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (((BYTE)_MHL2_UCP_SUPPORT << 4) | (_MHL2_UCP_SUPPORT << 3) | (_BIT2 | _BIT1 | _BIT0)));

            // Adopter ID
            ScalerSetDataPortByte(P29_AC_CBUS_CTRL_0C, _MSC_ADOPTER_ID_H_03, (BYTE)(((WORD)_MHL2_ADOPTER_ID >> 8) & 0x00FF));
            ScalerSetDataPortByte(P29_AC_CBUS_CTRL_0C, _MSC_ADOPTER_ID_L_04, (BYTE)(_MHL2_ADOPTER_ID & 0x00FF));

            // Packed Pixel Mode Support
            ScalerSetDataPortBit(P29_AC_CBUS_CTRL_0C, _MSC_VID_LINK_MODE_05, ~_BIT3, (BYTE)_MHL2_PP_MODE_SUPPORT << 3);

            // Audio Link Mode Support
            ScalerSetDataPortBit(P29_AC_CBUS_CTRL_0C, _MSC_AUD_LINK_MODE_06, ~(_BIT1 | _BIT0), _MHL2_AUD_CHANNEL);

            // Display Support
            ScalerSetDataPortByte(P29_AC_CBUS_CTRL_0C, _MSC_LOG_DEV_MAP_08, 0x01);

            // Set POWLIM DEVCAP Reg.
            ScalerSetDataPortByte(P29_AC_CBUS_CTRL_0C, _MSC_DEV_CAT_02, 0x31);

            // Device ID
            ScalerSetDataPortByte(P29_AC_CBUS_CTRL_0C, _MSC_DEVICE_ID_H_0B, (BYTE)(((WORD)_MHL2_DEVICE_ID >> 8) & 0x00FF));
            ScalerSetDataPortByte(P29_AC_CBUS_CTRL_0C, _MSC_DEVICE_ID_L_0C, (BYTE)(_MHL2_DEVICE_ID & 0x00FF));

            if(ScalerMHLRx1MscSendCommand(_MSC_WRITE_STAT, _MSC_CONNECTED_RDY, _MSC_DCAP_RDY) == _SUCCESS)
            {
                ScalerTimerActiveTimerEvent(SEC(1), _SCALER_TIMER_EVENT_MHL_RX1_SWITCH_PORT_DISCOVERY_DONE);

                DebugMessageDigital("D1 MHL Dev Cap RDY", 0x01);
                SET_MHL_RX1_PROCESS_STATE(_MHL_STATE_DEV_CAP_RDY);
            }

            break;

        default:
            break;
    }

    // Send HPD, PATH_EN and Device Capabilities Ready For Source
    if((enumMappedRegion != _DISPLAY_RGN_NONE) && (ucModeState != _MODE_STATUS_INITIAL) && (ucModeState != _MODE_STATUS_POWER_OFF))
    {
        switch(GET_MHL_RX1_PROCESS_STATE())
        {
            case _MHL_STATE_DEV_CAP_RDY:

                ScalerTimerDelayXms(150);

                if(ScalerMHLRx1MscSendCommand(_MSC_SET_HPD, _MSC_NULL_ADDRESS, _MSC_NULL_VALUE) == _SUCCESS)
                {
                    DebugMessageDigital("D1 MHL HPD Done", 0x01);
                    SET_MHL_RX1_PROCESS_STATE(_MHL_STATE_HPD_DONE);
                }

                return _TRUE;
                break;

            case _MHL_STATE_HPD_DONE:

                if((GET_MHL_RX1_ADOPTER_ID_HBYTE() == _ZTE_NUBIA_Z5_ADOPTER_ID_HBYTE) && (GET_MHL_RX1_ADOPTER_ID_LBYTE() == _ZTE_NUBIA_Z5_ADOPTER_ID_LBYTE))
                {
                    ScalerTimerDelayXms(50);
                }

                if(ScalerMHLRx1MscSendCommand(_MSC_WRITE_STAT, _MSC_LINK_MODE, _MSC_PATH_EN) == _SUCCESS)
                {
                    DebugMessageDigital("D1 MHL Path Enabled", 0x01);
                    SET_MHL_RX1_PROCESS_STATE(_MHL_STATE_PATH_EN_DONE);
                    SET_MHL_RX1_READY_TO_RESEND();

                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_MHL_RX1_SWITCH_PORT_DISCOVERY_DONE);
                }

                return _TRUE;
                break;

            case _MHL_STATE_PATH_EN_DONE:

                if(GET_TMDS_RX1_PHY_SET() == _TRUE)
                {
                    SET_MHL_RX1_PROCESS_STATE(_MHL_STATE_DONE);
                }

                return _TRUE;
                break;

            case _MHL_STATE_DONE:
            default:

                return _TRUE;
                break;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : RAP Process for D1 Port
// Input Value  : None
// Output Value : True or False (False if Content Off)
//--------------------------------------------------
bit ScalerMHLRx1MscRAPHandler(void)
{
    // Check RAP Command
    if((bit)ScalerGetBit(P29_D4_CBUS_CTRL_34, _BIT3) == _TRUE)
    {
        if((ScalerGetByte(P29_DC_CBUS_CTRL_3C) == _MSC_RAP_POLL) ||
           (ScalerGetByte(P29_DC_CBUS_CTRL_3C) == _MSC_RAP_CONTENT_ON) ||
           (ScalerGetByte(P29_DC_CBUS_CTRL_3C) == _MSC_RAP_CONTENT_OFF))
        {
            // Reply RAPK and No Error
            ScalerMHLRx1MscSendCommand(_MSC_MSG, _MSC_RAPK, _MSC_RAPK_NO_ERROR);
        }
        else
        {
            // Reply RAPK and Ineffective Code
            ScalerMHLRx1MscSendCommand(_MSC_MSG, _MSC_RAPK, _MSC_RAPK_UNRECOGNIZE_CODE);
        }

        // Clear Flag
        ScalerSetByte(P29_D4_CBUS_CTRL_34, (BYTE)_BIT3);

        if(ScalerGetByte(P29_DC_CBUS_CTRL_3C) == _MSC_RAP_CONTENT_OFF)
        {
            return _FALSE;
        }
    }

    return _TRUE;
}

#if(_MHL_UCP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get UCP Key Code for D1 Port
// Input Value  : UCP Key Code
// Output Value : True or False
//--------------------------------------------------
BYTE ScalerMHLRx1MscUCPGetCommand(BYTE *pucKeyCode)
{
    // Check UCP Command
    if(((bit)ScalerGetBit(P29_D4_CBUS_CTRL_34, _BIT1) == _TRUE) && (ScalerGetByte(P29_D6_CBUS_CTRL_36) == _MSC_UCP))
    {
        // Clear Flag
        ScalerSetByte(P29_D4_CBUS_CTRL_34, (BYTE)_BIT1);

        pucKeyCode[0] = ScalerGetByte(P29_D7_CBUS_CTRL_37);

        return _TRUE;
    }

    return _FALSE;
}
#endif  // End of #if(_MHL2_UCP_SUPPORT == _ON)


//--------------------------------------------------
// Description  : Signal PreDetection for MHL(Power Saving)
// Input Value  : Input Port
// Output Value : True : TMDS Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerMHLRx1PSPreDetect(void)
{
    // Check RAP Content OFF
    if(ScalerGetByte(P29_DC_CBUS_CTRL_3C) == _MSC_RAP_CONTENT_OFF)
    {
        return _FAIL;
    }

    // PSM --> PNM While Wake Up Pulses Received
    if(ScalerGetBit(P29_A0_CBUS_CTRL_00, (_BIT5 | _BIT4 | _BIT3)) == (_BIT5 | _BIT4 | _BIT3))
    {
        return _TRUE;
    }

    // Pre-Detect True By Switch Back to MHL Port
    if(GET_MHL_RX1_SWITCH_PORT_DISCOVERY_DONE() == _TRUE)
    {
        CLR_MHL_RX1_SWITCH_PORT_DISCOVERY_DONE();
        return _TRUE;
    }

    // [7] PSM = 1 --> Enable TMDS Lane3 Clock Switch
    ScalerSetBit(PB0_AB_CDR_02, ~_BIT7, _BIT7);

    // Disable clk lane Z0
    ScalerSetBit(PB0_A2_CMU_02, ~_BIT7, 0x00);

    // Reset Freq. Detect Counter(Toggle) & Choose Measure Clk to TMDS Clk
    ScalerSetBit(P70_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT5 | _BIT4), 0x00);
    ScalerSetBit(P70_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);

    // Clear Freq. Stable Flag
    ScalerSetBit(P70_EF_HDMI_ERROR_TH, ~_BIT6, _BIT6);

    // Clear Unstable Flag
    ScalerSetBit(P70_E6_HDMI_FREQDET_CTRL, ~_BIT2, _BIT2);

    // Delay enough time for freq. measure (calculated for measure 5 times)
    ScalerTimerDelayXms(5);

    // Detect Freq. Measure Stable
    if((ScalerGetBit(P70_E6_HDMI_FREQDET_CTRL, (_BIT6 | _BIT2)) == _BIT6) && (ScalerGetBit(P70_EF_HDMI_ERROR_TH, _BIT6) == _BIT6))
    {
        // [7] PSM = 1'b0 --> Disable TMDS Lane3 Clock Switch
        ScalerSetBit(PB0_AB_CDR_02, ~_BIT7, 0x00);

        // Enable clk lane Z0
        ScalerSetBit(PB0_A2_CMU_02, ~_BIT7, _BIT7);

        return _TRUE;
    }
    else
    {
        // Disable Freq. Detection
        ScalerSetBit(P70_E6_HDMI_FREQDET_CTRL, ~_BIT7, 0x00);

        // [7] PSM = 1'b0 --> Disable TMDS Lane3 Clock Switch
        ScalerSetBit(PB0_AB_CDR_02, ~_BIT7, 0x00);

        // Enable clk lane Z0
        ScalerSetBit(PB0_A2_CMU_02, ~_BIT7, _BIT7);
    }

    switch(GET_MHL_RX1_PROCESS_STATE())
    {
        case _MHL_STATE_INITIAL:
        case _MHL_STATE_PATH_EN_DONE:
        case _MHL_STATE_DONE:

            return _FAIL;
            break;

        default:

            return _SUCCESS;
            break;
    }

    return _FAIL;
}

//--------------------------------------------------
// Description  : Signal PreDetection for MHL(Power Normal)
// Input Value  : Input Port
// Output Value : True : TMDS Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerMHLRx1NormalPreDetect(void)
{
    // Check RAP Content OFF
    if(ScalerGetByte(P29_DC_CBUS_CTRL_3C) == _MSC_RAP_CONTENT_OFF)
    {
        return _FAIL;
    }

    // Pre-Detect True By Switch Back to MHL Port
    if(GET_MHL_RX1_SWITCH_PORT_DISCOVERY_DONE() == _TRUE)
    {
        CLR_MHL_RX1_SWITCH_PORT_DISCOVERY_DONE();
        return _TRUE;
    }

    ScalerTimerDelayXms(6);

    if(GET_TMDS_RX1_PHY_SET() == _TRUE)
    {
        return _SUCCESS;
    }

    switch(GET_MHL_RX1_PROCESS_STATE())
    {
        case _MHL_STATE_INITIAL:
        case _MHL_STATE_PATH_EN_DONE:

            return _FAIL;
            break;

        default:

            return _SUCCESS;
            break;
    }

    return _FAIL;
}
#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

