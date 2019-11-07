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
// ID Code      : RL6410_Series_Pinshare.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6410_SERIES_PINSHARE__

#include "ScalerFunctionInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _GPIO_OPEN_DRAIN                        2

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
void ScalerPinshareInitial(void);
void ScalerPinsharePowerOnReset(void);

#if(_HW_IIC_SUPPORT == _ON)
void ScalerPinshareHwIICPin(BYTE ucHwIICPinNum);
#endif

void ScalerPinshareGpioDdcPinSwitch(BYTE ucPinType);
void ScalerPinshareAdjustConfig(EnumConfigPin enumConfigPin, EnumPinConfigType enumConfigType);
void ScalerPinshareCBUSPinInitialReset(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Pinshare Initial Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPinshareInitial(void)
{
    ScalerSetByte(P10_00_PIN_SHARE_CTRL10, (BYTE)_PIN_Y6); // Page 10-00[2:0], Pin_Y6
    ScalerSetByte(P10_01_PIN_SHARE_CTRL11, (BYTE)_PIN_Y5); // Page 10-01[2:0], Pin_Y5
    ScalerSetByte(P10_02_PIN_SHARE_CTRL12, (BYTE)_PIN_AA6); // Page 10-02[2:0], Pin_AA6
    ScalerSetByte(P10_03_PIN_SHARE_CTRL13, (BYTE)_PIN_AA5); // Page 10-03[2:0], Pin_AA5
    ScalerSetByte(P10_04_PIN_SHARE_CTRL14, (BYTE)_PIN_L4); // Page 10-04[2:0], Pin_L4
    ScalerSetByte(P10_05_PIN_SHARE_CTRL15, (BYTE)_PIN_W6); // Page 10-05[2:0], Pin_W6
    ScalerSetByte(P10_06_PIN_SHARE_CTRL16, (BYTE)_PIN_F4); // Page 10-06[2:0], Pin_F4
    ScalerSetByte(P10_07_PIN_SHARE_CTRL17, (BYTE)_PIN_W5); // Page 10-07[2:0], Pin_W5
    ScalerSetByte(P10_08_PIN_SHARE_CTRL30, (BYTE)_PIN_AJ3); // Page 10-08[2:0], Pin_AJ3
    ScalerSetByte(P10_09_PIN_SHARE_CTRL31, (BYTE)_PIN_AJ1); // Page 10-09[2:0], Pin_AJ1
    ScalerSetByte(P10_0A_PIN_SHARE_CTRL32, (BYTE)_PIN_AJ2); // Page 10-0A[2:0], Pin_AJ2
    ScalerSetByte(P10_0B_PIN_SHARE_CTRL33, (BYTE)_PIN_AK3); // Page 10-0B[2:0], Pin_AK3
    ScalerSetByte(P10_0C_PIN_SHARE_CTRL34, (BYTE)_PIN_AK2); // Page 10-0C[2:0], Pin_AK2
    ScalerSetByte(P10_0D_PIN_SHARE_CTRL35, (BYTE)_PIN_AL3); // Page 10-0D[2:0], Pin_AL3
    ScalerSetByte(P10_0E_PIN_SHARE_CTRL36, (BYTE)_PIN_AL2); // Page 10-0E[2:0], Pin_AL2
    ScalerSetByte(P10_0F_PIN_SHARE_CTRL37, (BYTE)_PIN_AL1); // Page 10-0F[2:0], Pin_AL1

    ScalerSetByte(P10_10_PIN_SHARE_CTRL40, (BYTE)_PIN_AM1); // Page 10-10[2:0], Pin_AM1
    ScalerSetByte(P10_11_PIN_SHARE_CTRL41, (BYTE)_PIN_AH9); // Page 10-11[2:0], Pin_AH9
    ScalerSetByte(P10_12_PIN_SHARE_CTRL42, (BYTE)_PIN_AH8); // Page 10-12[2:0], Pin_AH8
    ScalerSetByte(P10_13_PIN_SHARE_CTRL43, (BYTE)_PIN_AJ9); // Page 10-13[2:0], Pin_AJ9
    ScalerSetByte(P10_14_PIN_SHARE_CTRL44, (BYTE)_PIN_AJ8); // Page 10-14[2:0], Pin_AJ8

    // Check if AL5-AK5 are assigned to DDCSDA_VGA
#if((_PIN_AL5 == 3) && (_PIN_AK5 == 3))
    ScalerPinshareGpioDdcPinSwitch(_DDC_VGA_SWITCH_DDC);
#else
    ScalerSetBit(P10_15_PIN_SHARE_CTRL45, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | ((BYTE)_PIN_AL5))); // Page 10-15[2:0], Pin_AL5
    ScalerSetByte(P10_16_PIN_SHARE_CTRL46, (BYTE)_PIN_AK5); // Page 10-16[2:0], Pin_AK5
#endif

    ScalerSetByte(P10_17_PIN_SHARE_CTRL47, (BYTE)_PIN_AJ5); // Page 10-17[2:0], Pin_AJ5
    ScalerSetByte(P10_18_PIN_SHARE_CTRL50, (BYTE)_PIN_AK4); // Page 10-18[2:0], Pin_AK4
    ScalerSetByte(P10_19_PIN_SHARE_CTRL51, (BYTE)_PIN_AL4); // Page 10-19[2:0], Pin_AL4
    ScalerSetByte(P10_1A_PIN_SHARE_CTRL52, (BYTE)_PIN_AM4); // Page 10-1A[2:0], Pin_AM4
    ScalerSetByte(P10_1B_PIN_SHARE_CTRL53, (BYTE)_PIN_AM2); // Page 10-1B[2:0], Pin_AM2
    ScalerSetByte(P10_1C_PIN_SHARE_CTRL54, (BYTE)_PIN_AM3); // Page 10-1C[2:0], Pin_AM3
    ScalerSetByte(P10_1D_PIN_SHARE_CTRL55, (BYTE)_PIN_G7); // Page 10-1D[2:0], Pin_G7

    // Check if pin J7-H6 are assigned to IIC
#if((_PIN_J7 == 6) && (_PIN_H6 == 6))
    ScalerSetBit(P10_1E_PIN_SHARE_CTRL56, ~_BIT7, _BIT7);  // Enable IIC
#else
    ScalerSetBit(P10_1E_PIN_SHARE_CTRL56, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (BYTE)_PIN_J7); // Page 10-1E[2:0], Pin_J7
    ScalerSetByte(P10_1F_PIN_SHARE_CTRL57, (BYTE)_PIN_H6); // Page 10-1F[2:0], Pin_H6
#endif

    // Check if pin AD28-AH27 are assigned to IIC
#if((_PIN_AD28 == 8) && (_PIN_AH27 == 8))
    ScalerSetBit(P10_24_PIN_SHARE_CTRL64, ~_BIT7, _BIT7);  // Enable IIC
#else
    ScalerSetBit(P10_24_PIN_SHARE_CTRL64, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (BYTE)_PIN_AD28); // Page 10-24[2:0], Pin_AD28
    ScalerSetByte(P10_25_PIN_SHARE_CTRL65, (BYTE)_PIN_AH27); // Page 10-25[2:0], Pin_AH27
#endif

    ScalerSetByte(P10_26_PIN_SHARE_CTRL66, (BYTE)_PIN_N29); // Page 10-26[2:0], Pin_N29
    ScalerSetByte(P10_27_PIN_SHARE_CTRL67, (BYTE)_PIN_N28); // Page 10-27[2:0], Pin_N28
    ScalerSetByte(P10_28_PIN_SHARE_CTRL70, (BYTE)_PIN_M29); // Page 10-28[2:0], Pin_M29
    ScalerSetByte(P10_29_PIN_SHARE_CTRL71, (BYTE)_PIN_M28); // Page 10-29[2:0], Pin_M28
    ScalerSetByte(P10_2A_PIN_SHARE_CTRL72, (BYTE)_PIN_J29); // Page 10-2A[2:0], Pin_J29
    ScalerSetByte(P10_2B_PIN_SHARE_CTRL73, (BYTE)_PIN_AJ28); // Page 10-2B[2:0], Pin_AJ28
    ScalerSetByte(P10_2C_PIN_SHARE_CTRL74, (BYTE)_PIN_N27); // Page 10-2C[2:0], Pin_N27
    ScalerSetByte(P10_2D_PIN_SHARE_CTRL75, (BYTE)_PIN_K27); // Page 10-2D[2:0], Pin_K27
    ScalerSetByte(P10_2E_PIN_SHARE_CTRL76, (BYTE)_PIN_M27); // Page 10-2E[2:0], Pin_M27
    ScalerSetByte(P10_2F_PIN_SHARE_CTRL77, (BYTE)_PIN_K29); // Page 10-2F[2:0], Pin_K29

    ScalerSetByte(P10_30_PIN_SHARE_CTRL80, (BYTE)_PIN_J28); // Page 10-30[2:0], Pin_J28
    ScalerSetByte(P10_31_PIN_SHARE_CTRL81, (BYTE)_PIN_J27); // Page 10-31[2:0], Pin_J27
    ScalerSetByte(P10_32_PIN_SHARE_CTRL82, (BYTE)_PIN_K28); // Page 10-32[2:0], Pin_K28

    // Check if pin AH21-AK21-AJ21-AJ20-AH20 are assigned to SPI
#if((_PIN_AH21 == 4) && (_PIN_AK21 == 4) && (_PIN_AJ21 == 4) && (_PIN_AJ20 == 4) && (_PIN_AH20 == 4))
    ScalerSetBit(P10_33_PIN_SHARE_CTRL83, ~_BIT7, _BIT7); // Enable SPI
#else
    ScalerSetBit(P10_33_PIN_SHARE_CTRL83, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (BYTE)_PIN_AH21); // Page 10-33[2:0], Pin_AH21
    ScalerSetByte(P10_34_PIN_SHARE_CTRL84, (BYTE)_PIN_AK21); // Page 10-34[2:0], Pin_AK21
    ScalerSetByte(P10_35_PIN_SHARE_CTRL85, (BYTE)_PIN_AJ21); // Page 10-35[2:0], Pin_AJ21
    ScalerSetByte(P10_36_PIN_SHARE_CTRL86, (BYTE)_PIN_AJ20); // Page 10-36[2:0], Pin_AJ20
    ScalerSetByte(P10_37_PIN_SHARE_CTRL87, (BYTE)_PIN_AH20); // Page 10-37[2:0], Pin_AH20
#endif

    ScalerSetByte(P10_38_PIN_SHARE_CTRL90, (BYTE)_PIN_AL21); // Page 10-38[2:0], Pin_AL21
    ScalerSetByte(P10_39_PIN_SHARE_CTRL91, (BYTE)_PIN_AA29); // Page 10-39[2:0], Pin_AA29
    ScalerSetByte(P10_3A_PIN_SHARE_CTRL92, (BYTE)_PIN_AA28); // Page 10-3A[2:0], Pin_AA28
    ScalerSetByte(P10_3B_PIN_SHARE_CTRL93, (BYTE)_PIN_AG25); // Page 10-3B[2:0], Pin_AG25
    ScalerSetByte(P10_3C_PIN_SHARE_CTRL94, (BYTE)_PIN_AH26); // Page 10-3C[2:0], Pin_AH26
    ScalerSetByte(P10_3D_PIN_SHARE_CTRL95, (BYTE)_PIN_AG26); // Page 10-3D[2:0], Pin_AG26
    ScalerSetByte(P10_3E_PIN_SHARE_CTRL96, (BYTE)_PIN_AJ26); // Page 10-3E[2:0], Pin_AJ26
    ScalerSetByte(P10_3F_PIN_SHARE_CTRL97, (BYTE)_PIN_AF28); // Page 10-3F[2:0], Pin_AF28

    ScalerSetByte(P10_40_PIN_SHARE_CTRLA0, (BYTE)_PIN_AG24); // Page 10-40[2:0], Pin_AG24

    // Check if pin AE28-AJ27 are assigned to UART
#if((_PIN_AE28 == 8) && (_PIN_AJ27 == 8))
    ScalerSetBit(P10_41_PIN_SHARE_CTRLA1, ~_BIT7, _BIT7); // Enable UART
#else
    ScalerSetBit(P10_41_PIN_SHARE_CTRLA1, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (BYTE)_PIN_AE28); // Page 10-41[2:0], Pin_AE28
    ScalerSetByte(P10_42_PIN_SHARE_CTRLA2, (BYTE)_PIN_AJ27); // Page 10-42[2:0], Pin_AJ27
#endif

    ScalerSetByte(P10_43_PIN_SHARE_CTRLA3, (BYTE)_PIN_AG29); // Page 10-43[2:0], Pin_AG29
    ScalerSetByte(P10_44_PIN_SHARE_CTRLA4, (BYTE)_PIN_AH25); // Page 10-44[2:0], Pin_AH25
    ScalerSetByte(P10_45_PIN_SHARE_CTRLA5, (BYTE)_PIN_AF29); // Page 10-45[2:0], Pin_AF29
    ScalerSetByte(P10_46_PIN_SHARE_CTRLA6, (BYTE)_PIN_AJ25); // Page 10-46[2:0], Pin_AJ25
    ScalerSetByte(P10_47_PIN_SHARE_CTRLA7, (BYTE)_PIN_AG28); // Page 10-47[2:0], Pin_AG28
    ScalerSetByte(P10_48_PIN_SHARE_CTRLB0, (BYTE)_PIN_AH24); // Page 10-48[2:0], Pin_AH24
    ScalerSetByte(P10_49_PIN_SHARE_CTRLB1, (BYTE)_PIN_AF27); // Page 10-49[2:0], Pin_AF27
    ScalerSetByte(P10_4A_PIN_SHARE_CTRLB2, (BYTE)_PIN_AJ24); // Page 10-4A[2:0], Pin_AJ24
    ScalerSetByte(P10_4B_PIN_SHARE_CTRLB3, (BYTE)_PIN_AG27); // Page 10-4B[2:0], Pin_AG27
    ScalerSetByte(P10_4C_PIN_SHARE_CTRLB4, (BYTE)_PIN_AJ18); // Page 10-4C[2:0], Pin_AJ18
    ScalerSetByte(P10_4D_PIN_SHARE_CTRLB5, (BYTE)_PIN_AK18); // Page 10-4D[2:0], Pin_AK18
    ScalerSetByte(P10_4E_PIN_SHARE_CTRLB6, (BYTE)_PIN_AE20); // Page 10-4E[2:0], Pin_AE20
    ScalerSetByte(P10_4F_PIN_SHARE_CTRLB7, (BYTE)_PIN_AL18); // Page 10-4F[2:0], Pin_AL18

    ScalerSetByte(P10_50_PIN_SHARE_CTRLC0, (BYTE)_PIN_AM18); // Page 10-50[2:0], Pin_AM18
    ScalerSetByte(P10_51_PIN_SHARE_CTRLC1, (BYTE)_PIN_AL19); // Page 10-51[2:0], Pin_AL19
    ScalerSetByte(P10_52_PIN_SHARE_CTRLC2, (BYTE)_PIN_AM19); // Page 10-52[2:0], Pin_AM19
    ScalerSetByte(P10_53_PIN_SHARE_CTRLC3, (BYTE)_PIN_AJ11); // Page 10-53[2:0], Pin_AJ11
    ScalerSetByte(P10_54_PIN_SHARE_CTRLC4, (BYTE)_PIN_AJ12); // Page 10-54[2:0], Pin_AJ12
    ScalerSetByte(P10_55_PIN_SHARE_CTRLC5, (BYTE)_PIN_AG6); // Page 10-55[2:0], Pin_AG6
    ScalerSetByte(P10_56_PIN_SHARE_CTRLC6, (BYTE)_PIN_AJ4); // Page 10-56[2:0], Pin_AJ4
    ScalerSetByte(P10_57_PIN_SHARE_CTRLC7, (BYTE)_PIN_AF7); // Page 10-57[2:0], Pin_AF7
    ScalerSetByte(P10_58_PIN_SHARE_CTRLD0, (BYTE)_PIN_AF6); // Page 10-58[2:0], Pin_AF6
    ScalerSetByte(P10_59_PIN_SHARE_CTRLD1, (BYTE)_PIN_AG7); // Page 10-59[2:0], Pin_AG7
    ScalerSetByte(P10_5A_PIN_SHARE_CTRLD2, (BYTE)_PIN_AH7); // Page 10-5A[2:0], Pin_AH7
    ScalerSetByte(P10_5B_PIN_SHARE_CTRLD3, (BYTE)_PIN_AH6); // Page 10-5B[2:0], Pin_AH6

    ScalerSetByte(P10_5C_PIN_SHARE_CTRLD4, (BYTE)_PIN_AH5); // Page 10-5C[2:0], Pin_AH5

    // Check if pin AG8-AG9 are assigned to IIC
#if((_PIN_AG8 == 6) && (_PIN_AG9 == 6))
    ScalerSetBit(P10_5D_PIN_SHARE_CTRLD5, ~_BIT7, _BIT7);  // Enable IIC
#else
    ScalerSetBit(P10_5D_PIN_SHARE_CTRLD5, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (BYTE)_PIN_AG8); // Page 10-5D[2:0], Pin_AG8
    ScalerSetByte(P10_5E_PIN_SHARE_CTRLD6, (BYTE)_PIN_AG9); // Page 10-5E[2:0], Pin_AG9
#endif

    // Check if pin_J6-J5 are assigned to DDC5
#if((_PIN_J6 == 3) && (_PIN_J5 == 3))
    ScalerPinshareGpioDdcPinSwitch(_DDC5_SWITCH_DDC);
#else
    ScalerSetBit(P10_5F_PIN_SHARE_CTRLD7, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | ((BYTE)_PIN_J6))); // Page 10-5F[2:0], Pin_J6
    ScalerSetByte(P10_60_PIN_SHARE_CTRLE0, (BYTE)_PIN_J5); // Page 10-60[2:0], Pin_J5
#endif

    // Check if pin_J6-J5 are assigned to DDC4
#if((_PIN_K6 == 3) && (_PIN_K5 == 3))
    ScalerPinshareGpioDdcPinSwitch(_DDC4_SWITCH_DDC);
#else
    ScalerSetBit(P10_61_PIN_SHARE_CTRLE1, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | ((BYTE)_PIN_K6))); // Page 10-61[2:0], Pin_K6
    ScalerSetByte(P10_62_PIN_SHARE_CTRLE2, (BYTE)_PIN_K5); // Page 10-62[2:0], Pin_K5
#endif

    // Check if pin_L6-L5 are assigned to DDC3
#if((_PIN_L6 == 3) && (_PIN_L5 == 3))
    ScalerPinshareGpioDdcPinSwitch(_DDC3_SWITCH_DDC);
#else
    ScalerSetBit(P10_63_PIN_SHARE_CTRLE3, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | ((BYTE)_PIN_L6))); // Page 10-63[2:0], Pin_L6
    ScalerSetByte(P10_64_PIN_SHARE_CTRLE4, (BYTE)_PIN_L5); // Page 10-64[2:0], Pin_L5
#endif

    // Check if pin_M6-M5 are assigned to DDC2
#if((_PIN_M6 == 3) && (_PIN_M5 == 3))
    ScalerPinshareGpioDdcPinSwitch(_DDC2_SWITCH_DDC);
#else
    ScalerSetBit(P10_65_PIN_SHARE_CTRLE5, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | ((BYTE)_PIN_M6))); // Page 10-65[2:0], Pin_M6
    ScalerSetByte(P10_66_PIN_SHARE_CTRLE6, (BYTE)_PIN_M5); // Page 10-66[2:0], Pin_M5
#endif

    ScalerSetByte(P10_67_PIN_SHARE_CTRLE7, (BYTE)_PIN_H7); // Page 10-67[2:0], Pin_H7
    ScalerSetByte(P10_68_PIN_SHARE_CTRLF0, (BYTE)_PIN_K7); // Page 10-68[2:0], Pin_K7
    ScalerSetByte(P10_69_PIN_SHARE_CTRLF1, (BYTE)_PIN_C8); // Page 10-69[2:0], Pin_C8
    ScalerSetByte(P10_6A_PIN_SHARE_CTRLF2, (BYTE)_PIN_N6); // Page 10-6A[2:0], Pin_N6
    ScalerSetByte(P10_6B_PIN_SHARE_CTRLF3, (BYTE)_PIN_C6); // Page 10-6B[2:0], Pin_C6

    ScalerSetByte(P10_6C_PIN_SHARE_CTRLF4, (BYTE)_PIN_N5); // Page 10-6C[2:0], Pin_N5


    // DDC Driving Current Set High
    ScalerSetBit(P10_B0_PIN_DRIVING_CTRL00, ~(_BIT7 | _BIT4), (_BIT7 | _BIT4));
    ScalerSetBit(P10_B3_PIN_DRIVING_CTRL03, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

    // Set Pin configure to AC ON
    ScalerPinshareConfig(_POWER_STATUS_AC_ON);

    // Pin Config adjust sample (this is a ineffective configuration example aviod uncall worning)
    ScalerPinshareAdjustConfig(_CONFIG_PIN_START, _GPI);
}

//--------------------------------------------------
// Description  : Pinshare Initial Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPinsharePowerOnReset(void)
{
    ScalerSetByte(P10_26_PIN_SHARE_CTRL66, (BYTE)_PIN_N29); // Page 10-26[2:0], Pin_N29
    ScalerSetByte(P10_27_PIN_SHARE_CTRL67, (BYTE)_PIN_N28); // Page 10-27[2:0], Pin_N28
    ScalerSetByte(P10_28_PIN_SHARE_CTRL70, (BYTE)_PIN_M29); // Page 10-28[2:0], Pin_M29
    ScalerSetByte(P10_29_PIN_SHARE_CTRL71, (BYTE)_PIN_M28); // Page 10-29[2:0], Pin_M28
    ScalerSetByte(P10_2A_PIN_SHARE_CTRL72, (BYTE)_PIN_J29); // Page 10-2A[2:0], Pin_J29
    ScalerSetByte(P10_2C_PIN_SHARE_CTRL74, (BYTE)_PIN_N27); // Page 10-2C[2:0], Pin_N27
    ScalerSetByte(P10_2D_PIN_SHARE_CTRL75, (BYTE)_PIN_K27); // Page 10-2D[2:0], Pin_K27
    ScalerSetByte(P10_2E_PIN_SHARE_CTRL76, (BYTE)_PIN_M27); // Page 10-2E[2:0], Pin_M27
    ScalerSetByte(P10_2F_PIN_SHARE_CTRL77, (BYTE)_PIN_K29); // Page 10-2F[2:0], Pin_K29

    ScalerSetByte(P10_30_PIN_SHARE_CTRL80, (BYTE)_PIN_J28); // Page 10-30[2:0], Pin_J28
    ScalerSetByte(P10_31_PIN_SHARE_CTRL81, (BYTE)_PIN_J27); // Page 10-31[2:0], Pin_J27
    ScalerSetByte(P10_32_PIN_SHARE_CTRL82, (BYTE)_PIN_K28); // Page 10-32[2:0], Pin_K28
}

#if(_HW_IIC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set HW IIC Pin Out
// Input Value  : ucHwIICPinNum --> PinJ7_H6 / AD28_AH27 / AG8_AG9
// Output Value : None
//--------------------------------------------------
void ScalerPinshareHwIICPin(BYTE ucHwIICPinNum)
{
    // Set the selected HwIICPinNum to IIC output
    // Set the others as GPI
    switch(ucHwIICPinNum)
    {
        case _HW_IIC_PIN_J7_H6:

            ScalerSetBit(P10_1E_PIN_SHARE_CTRL56, ~_BIT7, _BIT7);

#if((_PIN_AD28 == 8) && (_PIN_AH27 == 8))
            ScalerSetByte(P10_24_PIN_SHARE_CTRL64, 0x00);
            ScalerSetByte(P10_25_PIN_SHARE_CTRL65, 0x00);
#endif

#if((_PIN_AG8 == 6) && (_PIN_AG9 == 6))
            ScalerSetByte(P10_5D_PIN_SHARE_CTRLD5, 0x00);
            ScalerSetByte(P10_5E_PIN_SHARE_CTRLD6, 0x00);
#endif

            break;

        case _HW_IIC_PIN_AD28_AH27:

            ScalerSetBit(P10_24_PIN_SHARE_CTRL64, ~_BIT7, _BIT7);

#if((_PIN_J7 == 6) && (_PIN_H6 == 6))
            ScalerSetByte(P10_1E_PIN_SHARE_CTRL56, 0x00);
            ScalerSetByte(P10_1F_PIN_SHARE_CTRL57, 0x00);
#endif

#if((_PIN_AG8 == 6) && (_PIN_AG9 == 6))
            ScalerSetByte(P10_5D_PIN_SHARE_CTRLD5, 0x00);
            ScalerSetByte(P10_5E_PIN_SHARE_CTRLD6, 0x00);
#endif

            break;

        case _HW_IIC_PIN_AG8_AG9:

            ScalerSetBit(P10_5D_PIN_SHARE_CTRLD5, ~_BIT7, _BIT7);

#if((_PIN_J7 == 6) && (_PIN_H6 == 6))
            ScalerSetByte(P10_1E_PIN_SHARE_CTRL56, 0x00);
            ScalerSetByte(P10_1F_PIN_SHARE_CTRL57, 0x00);
#endif

#if((_PIN_AD28 == 8) && (_PIN_AH27 == 8))
            ScalerSetByte(P10_24_PIN_SHARE_CTRL64, 0x00);
            ScalerSetByte(P10_25_PIN_SHARE_CTRL65, 0x00);
#endif

            break;

        default:

            break;
    }
}
#endif  // End of #if(_HW_IIC_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Switch DDC pin to GPIO or viceversa
// Input Value  : ucPinType --> _PIN_58/59-121/122-123/124_GPIO/DDC
// Output Value : None
//--------------------------------------------------
void ScalerPinshareGpioDdcPinSwitch(BYTE ucPinType)
{
    switch(ucPinType)
    {
        case _DDC2_SWITCH_GPIO:
            ScalerSetBit(P10_65_PIN_SHARE_CTRLE5, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | ((BYTE)_GPIO_OPEN_DRAIN))); // Page 10-65[2:0], Pin_M6
            ScalerSetByte(P10_66_PIN_SHARE_CTRLE6, (BYTE)_GPIO_OPEN_DRAIN); // Page 10-66[2:0], Pin_M5
            break;

        case _DDC2_SWITCH_DDC:
            ScalerSetBit(P10_65_PIN_SHARE_CTRLE5, ~_BIT7, 0x00); // Page 10-65[2:0], Pin_M6
            break;


        case _DDC3_SWITCH_GPIO:
            ScalerSetBit(P10_63_PIN_SHARE_CTRLE3, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | ((BYTE)_GPIO_OPEN_DRAIN))); // Page 10-63[2:0], Pin_L6
            ScalerSetByte(P10_64_PIN_SHARE_CTRLE4, (BYTE)_GPIO_OPEN_DRAIN); // Page 10-64[2:0], Pin_L5
            break;

        case _DDC3_SWITCH_DDC:
            ScalerSetBit(P10_63_PIN_SHARE_CTRLE3, ~_BIT7, 0x00); // Page 10-63[2:0], Pin_L6
            break;


        case _DDC4_SWITCH_GPIO:
            ScalerSetBit(P10_61_PIN_SHARE_CTRLE1, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | ((BYTE)_GPIO_OPEN_DRAIN))); // Page 10-61[2:0], Pin_K6
            ScalerSetByte(P10_62_PIN_SHARE_CTRLE2, (BYTE)_GPIO_OPEN_DRAIN); // Page 10-62[2:0], Pin_K5
            break;

        case _DDC4_SWITCH_DDC:
            ScalerSetBit(P10_61_PIN_SHARE_CTRLE1, ~_BIT7, 0x00); // Page 10-61[2:0], Pin_K6
            break;


        case _DDC5_SWITCH_GPIO:
            ScalerSetBit(P10_5F_PIN_SHARE_CTRLD7, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | ((BYTE)_GPIO_OPEN_DRAIN))); // Page 10-5F[2:0], Pin_J6
            ScalerSetByte(P10_60_PIN_SHARE_CTRLE0, (BYTE)_GPIO_OPEN_DRAIN); // Page 10-60[2:0], Pin_J5
            break;

        case _DDC5_SWITCH_DDC:
            ScalerSetBit(P10_5F_PIN_SHARE_CTRLD7, ~_BIT7, 0x00); // Page 10-5F[2:0], Pin_J6
            break;


        case _DDC_VGA_SWITCH_GPIO:
            ScalerSetBit(P10_15_PIN_SHARE_CTRL45, ~(_BIT7 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | ((BYTE)_GPIO_OPEN_DRAIN))); // Page 10-15[2:0], Pin_AL5
            ScalerSetByte(P10_16_PIN_SHARE_CTRL46, (BYTE)_GPIO_OPEN_DRAIN); // Page 10-16[2:0], Pin_AK5
            break;

        case _DDC_VGA_SWITCH_DDC:
            ScalerSetBit(P10_15_PIN_SHARE_CTRL45, ~_BIT7, 0x00); // Page 10-5F[2:0], Pin_AL5
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Adjust pin share config
// Input Value  : enumConfigPin  --> Pin num
//                enumConfigTyte --> Pin type(GPIO/PWM..Etc.)
// Output Value : None
//--------------------------------------------------
void ScalerPinshareAdjustConfig(EnumConfigPin enumConfigPin, EnumPinConfigType enumConfigType)
{
    switch(enumConfigPin)
    {
        case _CONFIG_PIN_L4:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_04_PIN_SHARE_CTRL14, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_04_PIN_SHARE_CTRL14, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_04_PIN_SHARE_CTRL14, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_W6:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_05_PIN_SHARE_CTRL15, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_05_PIN_SHARE_CTRL15, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_05_PIN_SHARE_CTRL15, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_F4:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_06_PIN_SHARE_CTRL16, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_06_PIN_SHARE_CTRL16, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_06_PIN_SHARE_CTRL16, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_W5:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_07_PIN_SHARE_CTRL17, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_07_PIN_SHARE_CTRL17, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_07_PIN_SHARE_CTRL17, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AJ3:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_08_PIN_SHARE_CTRL30, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_08_PIN_SHARE_CTRL30, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_08_PIN_SHARE_CTRL30, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AJ1:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_09_PIN_SHARE_CTRL31, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_09_PIN_SHARE_CTRL31, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_09_PIN_SHARE_CTRL31, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AJ2:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_0A_PIN_SHARE_CTRL32, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_0A_PIN_SHARE_CTRL32, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_0A_PIN_SHARE_CTRL32, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AK3:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_0B_PIN_SHARE_CTRL33, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_0B_PIN_SHARE_CTRL33, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_0B_PIN_SHARE_CTRL33, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AK2:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_0C_PIN_SHARE_CTRL34, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_0C_PIN_SHARE_CTRL34, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_0C_PIN_SHARE_CTRL34, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AL3:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_0D_PIN_SHARE_CTRL35, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_0D_PIN_SHARE_CTRL35, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_0D_PIN_SHARE_CTRL35, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AL2:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_0E_PIN_SHARE_CTRL36, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_0E_PIN_SHARE_CTRL36, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_0E_PIN_SHARE_CTRL36, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AL1:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_0F_PIN_SHARE_CTRL37, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_0F_PIN_SHARE_CTRL37, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_0F_PIN_SHARE_CTRL37, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AM1:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_10_PIN_SHARE_CTRL40, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_10_PIN_SHARE_CTRL40, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_10_PIN_SHARE_CTRL40, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AK4:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_18_PIN_SHARE_CTRL50, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_18_PIN_SHARE_CTRL50, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_18_PIN_SHARE_CTRL50, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AL4:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_19_PIN_SHARE_CTRL51, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_19_PIN_SHARE_CTRL51, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_19_PIN_SHARE_CTRL51, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AM4:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_1A_PIN_SHARE_CTRL52, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_1A_PIN_SHARE_CTRL52, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_1A_PIN_SHARE_CTRL52, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_N29:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_26_PIN_SHARE_CTRL66, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_26_PIN_SHARE_CTRL66, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_26_PIN_SHARE_CTRL66, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_N28:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_27_PIN_SHARE_CTRL67, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_27_PIN_SHARE_CTRL67, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_27_PIN_SHARE_CTRL67, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_M29:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_28_PIN_SHARE_CTRL70, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_28_PIN_SHARE_CTRL70, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_28_PIN_SHARE_CTRL70, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_M28:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_29_PIN_SHARE_CTRL71, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_29_PIN_SHARE_CTRL71, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_29_PIN_SHARE_CTRL71, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_J29:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_2A_PIN_SHARE_CTRL72, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_2A_PIN_SHARE_CTRL72, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_2A_PIN_SHARE_CTRL72, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AJ28:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_2B_PIN_SHARE_CTRL73, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_2B_PIN_SHARE_CTRL73, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_2B_PIN_SHARE_CTRL73, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_N27:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_2C_PIN_SHARE_CTRL74, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_2C_PIN_SHARE_CTRL74, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_2C_PIN_SHARE_CTRL74, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_K27:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_2D_PIN_SHARE_CTRL75, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_2D_PIN_SHARE_CTRL75, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_2D_PIN_SHARE_CTRL75, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_M27:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_2E_PIN_SHARE_CTRL76, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_2E_PIN_SHARE_CTRL76, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_2E_PIN_SHARE_CTRL76, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_K29:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_2F_PIN_SHARE_CTRL77, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_2F_PIN_SHARE_CTRL77, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_2F_PIN_SHARE_CTRL77, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_J28:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_30_PIN_SHARE_CTRL80, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_30_PIN_SHARE_CTRL80, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_30_PIN_SHARE_CTRL80, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_J27:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_31_PIN_SHARE_CTRL81, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_31_PIN_SHARE_CTRL81, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_31_PIN_SHARE_CTRL81, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_K28:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_32_PIN_SHARE_CTRL82, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_32_PIN_SHARE_CTRL82, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_32_PIN_SHARE_CTRL82, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;


        case _CONFIG_PIN_AA29:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_39_PIN_SHARE_CTRL91, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_39_PIN_SHARE_CTRL91, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_39_PIN_SHARE_CTRL91, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AA28:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_3A_PIN_SHARE_CTRL92, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_3A_PIN_SHARE_CTRL92, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_3A_PIN_SHARE_CTRL92, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AG25:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_3B_PIN_SHARE_CTRL93, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_3B_PIN_SHARE_CTRL93, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_3B_PIN_SHARE_CTRL93, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AH26:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_3C_PIN_SHARE_CTRL94, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_3C_PIN_SHARE_CTRL94, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_3C_PIN_SHARE_CTRL94, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AG26:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_3D_PIN_SHARE_CTRL95, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_3D_PIN_SHARE_CTRL95, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_3D_PIN_SHARE_CTRL95, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                case _PWM3_PP:
                    ScalerSetBit(P10_3D_PIN_SHARE_CTRL95, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
                    break;

                case _PWM3_OD:
                    ScalerSetBit(P10_3D_PIN_SHARE_CTRL95, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AJ26:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_3E_PIN_SHARE_CTRL96, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_3E_PIN_SHARE_CTRL96, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_3E_PIN_SHARE_CTRL96, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AF28:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_3F_PIN_SHARE_CTRL97, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_3F_PIN_SHARE_CTRL97, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_3F_PIN_SHARE_CTRL97, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AG29:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_43_PIN_SHARE_CTRLA3, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_43_PIN_SHARE_CTRLA3, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_43_PIN_SHARE_CTRLA3, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AH25:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_44_PIN_SHARE_CTRLA4, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_44_PIN_SHARE_CTRLA4, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_44_PIN_SHARE_CTRLA4, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AJ25:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_46_PIN_SHARE_CTRLA6, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_46_PIN_SHARE_CTRLA6, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_46_PIN_SHARE_CTRLA6, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AG28:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_47_PIN_SHARE_CTRLA7, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_47_PIN_SHARE_CTRLA7, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_47_PIN_SHARE_CTRLA7, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AJ5:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_17_PIN_SHARE_CTRL47, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_17_PIN_SHARE_CTRL47, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_17_PIN_SHARE_CTRL47, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                case _PWM0_PP:
                    ScalerSetBit(P10_17_PIN_SHARE_CTRL47, ~(_BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
                    break;

                case _PWM0_OD:
                    ScalerSetBit(P10_17_PIN_SHARE_CTRL47, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AJ11:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_53_PIN_SHARE_CTRLC3, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_53_PIN_SHARE_CTRLC3, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_53_PIN_SHARE_CTRLC3, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AJ12:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_54_PIN_SHARE_CTRLC4, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_54_PIN_SHARE_CTRLC4, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_54_PIN_SHARE_CTRLC4, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_AG6:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_55_PIN_SHARE_CTRLC5, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_55_PIN_SHARE_CTRLC5, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_55_PIN_SHARE_CTRLC5, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_H7:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_67_PIN_SHARE_CTRLE7, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_67_PIN_SHARE_CTRLE7, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_67_PIN_SHARE_CTRLE7, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_K7:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_68_PIN_SHARE_CTRLF0, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_68_PIN_SHARE_CTRLF0, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_68_PIN_SHARE_CTRLF0, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_C8:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_69_PIN_SHARE_CTRLF1, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_69_PIN_SHARE_CTRLF1, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_69_PIN_SHARE_CTRLF1, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_N6:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_6A_PIN_SHARE_CTRLF2, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_6A_PIN_SHARE_CTRLF2, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_6A_PIN_SHARE_CTRLF2, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_C6:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_6B_PIN_SHARE_CTRLF3, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_6B_PIN_SHARE_CTRLF3, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_6B_PIN_SHARE_CTRLF3, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;

        case _CONFIG_PIN_N5:

            switch(enumConfigType)
            {
                case _GPI:
                    ScalerSetBit(P10_6C_PIN_SHARE_CTRLF4, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                    break;

                case _GPO_PP:
                    ScalerSetBit(P10_6C_PIN_SHARE_CTRLF4, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
                    break;

                case _GPO_OD:
                    ScalerSetBit(P10_6C_PIN_SHARE_CTRLF4, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);
                    break;

                default:
                    break;
            }

            break;


        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Reset MHL setting when MHL nonsupport
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPinshareCBUSPinInitialReset(void)
{
    if(ScalerGlobalGetIDCode() == _RL6410_VER_A_ID_CODE)
    {
        // Disable 3Ohm Decrease
        ScalerSetBit(P27_0C_ECBUS_PHY_BIST, ~_BIT0, 0x00);
        // Disable 3Ohm Decrease
        ScalerSetBit(P67_0C_ECBUS_PHY_BIST, ~_BIT0, 0x00);
        // Disable 3Ohm Decrease
        ScalerSetBit(P1E_0C_ECBUS_PHY_BIST, ~_BIT0, 0x00);
        // Disable 3Ohm Decrease
        ScalerSetBit(P5E_0C_ECBUS_PHY_BIST, ~_BIT0, 0x00);
    }
}

