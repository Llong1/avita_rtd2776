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
// ID Code      : ScalerADC.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_ADC__

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
void ScalerADCBandgap(bit bSelect);

#if(_VGA_SUPPORT == _ON)
void ScalerADCOutputClkSetting(void);
void ScalerADCPowerSetting(void);
void ScalerADCBiasCurrentSetting(void);
void ScalerADCGainAdjust(BYTE *pucGainMSB, BYTE *pucGainLSB);
void ScalerADCOffsetAdjust(BYTE *pucOffsetMSB, BYTE *pucOffsetLSB);
void ScalerADCClampMode(EnumColorSpace enumColorFormat);

#if(_VGA_CHROMA_PATTERN12_SUPPORT == _ON)
bit ScalerADCGetClampToTopStatus(void);
#endif

void ScalerADCBandWidthSetting(DWORD ulAdcClock);
void ScalerADCDCRestoreEn(bit bEn);
void ScalerADCSOGClampEn(bit bEn);
void ScalerADCSchmittTriggerSetting(void);
void ScalerADCNRSetting(void);
#endif


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Power On/Off ADC Bandgap.
// Input Value  : On or Off
// Output Value : None
//--------------------------------------------------
void ScalerADCBandgap(bit bSelect)
{
    if(bSelect == _ON)
    {
        // ADC ldo Output Not Short to Ground
        // ADC Bandgap/mbias On
        ScalerSetBit(P0_C6_ADC_POWER, ~(_BIT4 | _BIT3), _BIT3);

        // Bit3: SOG0 Bias Current from ADC
        // Bit1: Bias Current of SOG normal
        ScalerSetBit(P0_D4_ADC_SOG_CTRL, ~(_BIT3 | _BIT1), _BIT3);
    }
    else
    {
        // Bit3: SOG0 Bias Current from POR
        // Bit1: Bias Current of SOG standby
        ScalerSetBit(P0_D4_ADC_SOG_CTRL, ~(_BIT3 | _BIT1), _BIT1);

        // ADC ldo Output Not Short to Ground
        // ADC Bandgap/mbias Off
        ScalerSetBit(P0_C6_ADC_POWER, ~(_BIT4 | _BIT3), _BIT4);
    }
}

#if(_VGA_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Intial adc output clock setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerADCOutputClkSetting(void)
{
    // Output clock divider Polarity Normal, Output Pixel Dealy 0.56nS, divider = 1
    // ck_data polarity select normal; Clock polarity select positive
    ScalerSetBit(P0_BC_ADC_CK_OUT_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT6);

    // Disable Test Output
    ScalerSetBit(P0_BD_ADC_TEST, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

    // diff clock from APLL, duty set 49.3%
    // ADC sample time duty set 400ps (default)
    ScalerSetBit(P0_BB_ADC_CK_IN_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT5 | _BIT4));
}

//--------------------------------------------------
// Description  : ADC Power Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerADCPowerSetting(void)
{
    // ADC LDO Power On, ADC Clock Power On, SOG_ADC0 Power On, R/G/B ADC Power On
    // ADC ldo Output Not Short to Ground
    ScalerSetBit(P0_C6_ADC_POWER, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT2 | _BIT1 | _BIT0));

    // Set internal 2.5V LDO voltage
    ScalerSetBit(P0_DA_ADC_REG2, ~(_BIT1 | _BIT0), _BIT0);

    // ADCNR Setting
    ScalerADCNRSetting();
}

//--------------------------------------------------
// Description  : Intial adc Bias current setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerADCBiasCurrentSetting(void)
{
    // Set bandgap voltage 1.217V, ADC Regulator 1.145V
    ScalerSetBit(P0_C7_ADC_VOLT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT4));

    // Set SF Bias current relation control register
    // Disable SF LPF, Enable VREF LPF
    ScalerSetBit(P0_C8_ADC_SF_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2), (_BIT6 | _BIT2));

    // Enable meta-stable detect/correction, bias current of SAR Comparator pre-am = 75uA
    ScalerSetBit(P0_D5_ADC_SAR_CTRL, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT4));

    // the bottom plate of sampling cap do not reset in advance
    ScalerSetBit(P0_D9_ADC_REG1, ~_BIT3, 0x00);
}

//--------------------------------------------------
// Description  : Adjust ADC gain
// Input Value  : pGainMSB ---> R/G/B Gain coefficient MSB
//                pGainLSB ---> R/G/B Gain coefficient LSB
// Output Value : None
//--------------------------------------------------
void ScalerADCGainAdjust(BYTE *pucGainMSB, BYTE *pucGainLSB)
{
    // Set ADC Gain High Byte Factor
    ScalerSetByte(P0_C0_ADC_GAI_RED_MSB, pucGainMSB[0]);
    ScalerSetByte(P0_C1_ADC_GAI_GRN_MSB, pucGainMSB[1]);
    ScalerSetByte(P0_C2_ADC_GAI_BLU_MSB, pucGainMSB[2]);

    // Set ADC Gain Low Byte Factor
    ScalerSetByte(P0_BE_ADC_GAI_LSB, ((pucGainLSB[0] & 0x03) << 4) | ((pucGainLSB[1] & 0x03) << 2) | (pucGainLSB[2] & 0x03));
}

//--------------------------------------------------
// Description  : Adjust ADC offset
// Input Value  : pGainMSB ---> R/G/B Offset coefficient MSB
//                pGainLSB ---> R/G/B Offset coefficient LSB
// Output Value : None
//--------------------------------------------------
void ScalerADCOffsetAdjust(BYTE *pucOffsetMSB, BYTE *pucOffsetLSB)
{
    // Set ADC Gain High Byte Factor
    ScalerSetByte(P0_C3_ADC_OFF_RED_MSB, pucOffsetMSB[0]);
    ScalerSetByte(P0_C4_ADC_OFF_GRN_MSB, pucOffsetMSB[1]);
    ScalerSetByte(P0_C5_ADC_OFF_BLU_MSB, pucOffsetMSB[2]);

    // Set ADC Offset Low Byte Factor
    ScalerSetByte(P0_BF_ADC_OFF_LSB, ((pucOffsetLSB[0] & 0x03) << 4) | ((pucOffsetLSB[1] & 0x03) << 2) | (pucOffsetLSB[2] & 0x03));
}

//--------------------------------------------------
// Description  : ADC color format setting
// Input Value  : ucColorFormat ---> SOY or VGA sync type format
// Output Value : None
//--------------------------------------------------
void ScalerADCClampMode(EnumColorSpace enumColorFormat)
{
#if(_VGA_CHROMA_PATTERN12_SUPPORT == _ON)
    if(ScalerADCGetClampToTopStatus() == _TRUE)
    {
        return;
    }
#endif

    if(enumColorFormat == _COLOR_SPACE_YPBPR)
    {
        // Red Channel Set Ypbpr Clamp Mode
        ScalerSetBit(P0_CF_ADC_CTL_RED, ~_BIT7, _BIT7);

        // Green Channel Set RGB Clamp Mode
        ScalerSetBit(P0_D0_ADC_CTL_GRN, ~_BIT7, 0x00);

        // Blue Channel Set Ypbpr Clamp Mode
        ScalerSetBit(P0_D1_ADC_CTL_BLU, ~_BIT7, _BIT7);
    }
    else // RGB format
    {
        // Red Channel Set RGB Clamp Mode
        ScalerSetBit(P0_CF_ADC_CTL_RED, ~_BIT7, 0x00);

        // Green Channel Set RGB Clamp Mode
        ScalerSetBit(P0_D0_ADC_CTL_GRN, ~_BIT7, 0x00);

        // Blue Channel Set RGB Clamp Mode
        ScalerSetBit(P0_D1_ADC_CTL_BLU, ~_BIT7, 0x00);
    }
}

#if(_VGA_CHROMA_PATTERN12_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get clamp-to-top status
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerADCGetClampToTopStatus(void)
{
    return (ScalerGetBit(P0_D6_ADC_CLAMP_TOP, (_BIT2 | _BIT1 | _BIT0)) != 0x00);
}
#endif

//--------------------------------------------------
// Description  : ADC bandwidth and bias current setting
// Input Value  : ulAdcClock ---> ADC Clock frequency
// Output Value : None
//--------------------------------------------------
void ScalerADCBandWidthSetting(DWORD ulAdcClock)
{
    ulAdcClock = ulAdcClock;

#if(_VGA_ADC_SF_SHA_LPF_UNDER_25MHZ_SUPPORT == _ON)
    if(ulAdcClock < 26)
    {
        // Enable SF bandwidth & Set Bandwidth to 150MHz
        ScalerSetBit(P0_C8_ADC_SF_CTRL, ~(_BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT3));
    }
    else
    {
        // Disable SF bandwidth
        ScalerSetBit(P0_C8_ADC_SF_CTRL, ~(_BIT5 | _BIT4 | _BIT3), 0x00);
    }
#endif
}

//--------------------------------------------------
// Description  : DC restore
// Input Value  : bEn---> Disable or enable dcrestore function
// Output Value : None
//--------------------------------------------------
void ScalerADCDCRestoreEn(bit bEn)
{
    if(bEn == _TRUE)
    {
        // Enable DC Restore circut
        ScalerSetBit(P0_D4_ADC_SOG_CTRL, ~_BIT4, _BIT4);
    }
    else
    {
        // Disable DC Restore circut
        ScalerSetBit(P0_D4_ADC_SOG_CTRL, ~_BIT4, 0x00);
    }
}

//--------------------------------------------------
// Description  : SOG Clamp Control
// Input Value  : bEn---> Disable or enable SOG clamp
// Output Value : None
//--------------------------------------------------
void ScalerADCSOGClampEn(bit bEn)
{
    if(bEn == _TRUE)
    {
        // Enable SOG Clamp, normal clamp
        ScalerSetBit(P0_D4_ADC_SOG_CTRL, ~(_BIT5 | _BIT2), _BIT5);

        // 0x19 * 10 = 250mV = [(100 + X) + (400 - X)] / 2;
        // 250mV is fit to Both DC Restore and Clamp Mode.
        if(ScalerGetBit(P0_D7_ADC_SOG_DAC, 0x1F) < 0x19)
        {
            pData[0] = 0x19 - ScalerGetBit(P0_D7_ADC_SOG_DAC, 0x1F);

            // Chanage SOG DAC Setting to 250mV smoothly
            while(pData[0]--)
            {
                ScalerSetBit(P0_D7_ADC_SOG_DAC, ~(0x1F), (0x19 - pData[0]));

                // Delay 1ms for clamp mode rising.
                ScalerTimerDelayXms(1);
            }
        }
    }
    else
    {
        // Disable SOG Clamp
        ScalerSetBit(P0_D4_ADC_SOG_CTRL, ~_BIT5, 0x00);
    }
}

//--------------------------------------------------
// Description  : ADC Schmitt Trigger Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerADCSchmittTriggerSetting(void)
{
    // Enable Schmitt Trigger and Select New Mode
    ScalerSetBit(P0_F4_HS_SCHMITT_TRIGGE_CTRL, ~(_BIT7 | _BIT5), (_BIT7 | _BIT5));

    // Schmitt Trigger Select New 2 Mode (New Mode & New 2 mode both enable, New 2 Mode is effective)
    ScalerSetBit(P0_F2_HS_SCHMITT_TRIGGE_CTRL2, ~_BIT7, _BIT7);

    // HS Schimmit Tigger Polarity Select
    ScalerSetBit(P0_F4_HS_SCHMITT_TRIGGE_CTRL, ~_BIT6, (_VGA_HS_SCHMITT_TRIGGER_POLARITY_SEL << 6));

    // HS Schimmit Tigger Vth Fine tune
    ScalerSetBit(P0_F4_HS_SCHMITT_TRIGGE_CTRL, ~_BIT4, (_VGA_HS_SCHMITT_TRIGGER_VTH_FINE_TUNE << 4));

    // HS Schimmit Trigger Positive Vth Setting
    ScalerSetBit(P0_F4_HS_SCHMITT_TRIGGE_CTRL, ~(_BIT3 | _BIT2), (_VGA_HS_SCHMITT_TRIGGER_POSITIVE_VTH << 2));

    // HS Schimmit Trigger Negative Vth Setting
    ScalerSetBit(P0_F4_HS_SCHMITT_TRIGGE_CTRL, ~(_BIT1 | _BIT0), (_VGA_HS_SCHMITT_TRIGGER_NEGATIVE_VTH));
}


//--------------------------------------------------
// Description  : ADCNR setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerADCNRSetting(void)
{
    // Tone Count Modify Type Select to High mode
    ScalerSetBit(P33_0E_ADCNR_MODIFY, ~_BIT7, _BIT7);

    // Total Frame Number set 1
    ScalerSetBit(P33_01_ADCNR_CTRL2, ~(_BIT5 | _BIT4), _BIT4);

    // Truncate LSB bit to avoid IDither Noise
    ScalerSetBit(P33_02_ADCNR_CTRL3, ~(_BIT7 | _BIT6), _BIT6);

    // Enable ADCNR
    ScalerSetByte(P33_00_ADCNR_CTRL1, 0x9C);

    // ADC offset dither disable
    ScalerSetBit(P0_D9_ADC_REG1, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
}

#endif // End of #if(_VGA_SUPPORT == _ON)
