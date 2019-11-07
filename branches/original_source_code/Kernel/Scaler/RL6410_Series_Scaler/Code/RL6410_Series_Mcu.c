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
// ID Code      : RL6410_Series_Mcu.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions DDCRAM Address
//--------------------------------------------------
#define _EMBEDDED_DDCRAM_VGA_DDC_ADDRESS                    0xE000
#define _EMBEDDED_DDCRAM_DDC0_ADDRESS                       0xE080
#define _EMBEDDED_DDCRAM_DDC1_ADDRESS                       0xE280
#define _EMBEDDED_DDCRAM_DDC2_ADDRESS                       0xE480
#define _EMBEDDED_DDCRAM_DDC3_ADDRESS                       0xE680
#define _EMBEDDED_DDCRAM_DDC4_ADDRESS                       0xE880
#define _EMBEDDED_DDCRAM_DDC5_ADDRESS                       0xEA80

#if(_D6_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)

#if(_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0)
#define _EMBEDDED_DDCRAM_DDC6_ADDRESS                       0xE180
#endif

#endif

#define _EMBEDDED_DDCRAM_DDC0_MHL_ADDRESS                   0xE180
#define _EMBEDDED_DDCRAM_DDC1_MHL_ADDRESS                   0xE380
#define _EMBEDDED_DDCRAM_DDC2_MHL_ADDRESS                   0xE580
#define _EMBEDDED_DDCRAM_DDC3_MHL_ADDRESS                   0xE780
#define _EMBEDDED_DDCRAM_DDC4_MHL_ADDRESS                   0xE980
#define _EMBEDDED_DDCRAM_DDC5_MHL_ADDRESS                   0xEB80

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
//--------------------------------------------------
// Cache Controller (Page FD)
//--------------------------------------------------
volatile BYTE xdata MCU_FDA0_CACHE_FUNCTION                         _at_ 0xFDA0;
volatile BYTE xdata MCU_FDA1_CACHE_OPTION                           _at_ 0xFDA1;
volatile BYTE xdata MCU_FDA2_CACHE_START_ADDRESS_H                  _at_ 0xFDA2;
volatile BYTE xdata MCU_FDA3_CACHE_START_ADDRESS_M                  _at_ 0xFDA3;
volatile BYTE xdata MCU_FDA4_CACHE_START_ADDRESS_L                  _at_ 0xFDA4;
volatile BYTE xdata MCU_FDA5_CACHE_END_ADDRESS_H                    _at_ 0xFDA5;
volatile BYTE xdata MCU_FDA6_CACHE_END_ADDRESS_M                    _at_ 0xFDA6;
volatile BYTE xdata MCU_FDA7_CACHE_END_ADDRESS_L                    _at_ 0xFDA7;
volatile BYTE xdata MCU_FDA8_CACHE_START_ADDRESS_H2                 _at_ 0xFDA8;
volatile BYTE xdata MCU_FDA9_CACHE_START_ADDRESS_M2                 _at_ 0xFDA9;
volatile BYTE xdata MCU_FDAA_CACHE_START_ADDRESS_L2                 _at_ 0xFDAA;
volatile BYTE xdata MCU_FDAB_CACHE_END_ADDRESS_H2                   _at_ 0xFDAB;
volatile BYTE xdata MCU_FDAC_CACHE_END_ADDRESS_M2                   _at_ 0xFDAC;
volatile BYTE xdata MCU_FDAD_CACHE_END_ADDRESS_L2                   _at_ 0xFDAD;
volatile BYTE xdata MCU_FDAE_COMMON_START_ADDRESS_H                 _at_ 0xFDAE;
volatile BYTE xdata MCU_FDAF_COMMON_START_ADDRESS_L                 _at_ 0xFDAF;
volatile BYTE xdata MCU_FDB0_COMMON_END_ADDRESS_H                   _at_ 0xFDB0;
volatile BYTE xdata MCU_FDB1_COMMON_END_ADDRESS_L                   _at_ 0xFDB1;
volatile BYTE xdata MCU_FDB2_CACHE_ADDRESS_WILD_CARD                _at_ 0xFDB2;
volatile BYTE xdata MCU_FDB3_PERFORMANCE_METER_CONTROL              _at_ 0xFDB3;
volatile BYTE xdata MCU_FDB4_PERFORMANCE_METER_INTERRUPT            _at_ 0xFDB4;
volatile BYTE xdata MCU_FDB5_PERFORMANCE_METER_STATUS               _at_ 0xFDB5;
volatile BYTE xdata MCU_FDB6_PERFORMANCE_METER_LAST_ADDRESS_H       _at_ 0xFDB6;
volatile BYTE xdata MCU_FDB7_PERFORMANCE_METER_LAST_ADDRESS_M       _at_ 0xFDB7;
volatile BYTE xdata MCU_FDB8_PERFORMANCE_METER_LAST_ADDRESS_L       _at_ 0xFDB8;
volatile BYTE xdata MCU_FDB9_PERFORMANCE_METER_REF_COUNT_H          _at_ 0xFDB9;
volatile BYTE xdata MCU_FDBA_PERFORMANCE_METER_REF_COUNT_M1         _at_ 0xFDBA;
volatile BYTE xdata MCU_FDBB_PERFORMANCE_METER_REF_COUNT_M0         _at_ 0xFDBB;
volatile BYTE xdata MCU_FDBC_PERFORMANCE_METER_REF_COUNT_L          _at_ 0xFDBC;
volatile BYTE xdata MCU_FDBD_PERFORMANCE_METER_MISS_COUNT_H         _at_ 0xFDBD;
volatile BYTE xdata MCU_FDBE_PERFORMANCE_METER_MISS_COUNT_M1        _at_ 0xFDBE;
volatile BYTE xdata MCU_FDBF_PERFORMANCE_METER_MISS_COUNT_M0        _at_ 0xFDBF;
volatile BYTE xdata MCU_FDC0_PERFORMANCE_METER_MISS_COUNT_L         _at_ 0xFDC0;
volatile BYTE xdata MCU_FDC1_PERFORMANCE_METER_MEM_RESTART_H        _at_ 0xFDC1;
volatile BYTE xdata MCU_FDC2_PERFORMANCE_METER_MEM_RESTART_M1       _at_ 0xFDC2;
volatile BYTE xdata MCU_FDC3_PERFORMANCE_METER_MEM_RESTART_M0       _at_ 0xFDC3;
volatile BYTE xdata MCU_FDC4_PERFORMANCE_METER_MEM_RESTART_L        _at_ 0xFDC4;
volatile BYTE xdata MCU_FDC5_PERFORMANCE_METER_CRC_H                _at_ 0xFDC5;
volatile BYTE xdata MCU_FDC6_PERFORMANCE_METER_CRC_L                _at_ 0xFDC6;
volatile BYTE xdata MCU_FDC7_CACHE_CONTENT_ADDRESS_H                _at_ 0xFDC7;
volatile BYTE xdata MCU_FDC8_CACHE_CONTENT_ADDRESS_L                _at_ 0xFDC8;
volatile BYTE xdata MCU_FDC9_CACHE_CONTENT_DATA                     _at_ 0xFDC9;
volatile BYTE xdata MCU_FDCA_CACHE_SRAM_BIST_CTRL                   _at_ 0xFDCA;
volatile BYTE xdata MCU_FDCB_CACHE_SRAM_DRF_BIST_CTRL               _at_ 0xFDCB;
volatile BYTE xdata MCU_FDCC_CACHE_LOAD_CTRL                        _at_ 0xFDCC;


//--------------------------------------------------
// EMCU (Page FE)
//--------------------------------------------------
volatile BYTE xdata MCU_FE00_PORT40_PIN_REG                         _at_ 0xFE00;
volatile BYTE xdata MCU_FE01_PORT41_PIN_REG                         _at_ 0xFE01;
volatile BYTE xdata MCU_FE02_PORT42_PIN_REG                         _at_ 0xFE02;
volatile BYTE xdata MCU_FE03_PORT43_PIN_REG                         _at_ 0xFE03;
volatile BYTE xdata MCU_FE04_PORT44_PIN_REG                         _at_ 0xFE04;
volatile BYTE xdata MCU_FE05_PORT45_PIN_REG                         _at_ 0xFE05;
volatile BYTE xdata MCU_FE06_PORT46_PIN_REG                         _at_ 0xFE06;
volatile BYTE xdata MCU_FE07_PORT47_PIN_REG                         _at_ 0xFE07;
volatile BYTE xdata MCU_FE08_PORT50_PIN_REG                         _at_ 0xFE08;
volatile BYTE xdata MCU_FE09_PORT51_PIN_REG                         _at_ 0xFE09;
volatile BYTE xdata MCU_FE0A_PORT52_PIN_REG                         _at_ 0xFE0A;
volatile BYTE xdata MCU_FE0B_PORT53_PIN_REG                         _at_ 0xFE0B;
volatile BYTE xdata MCU_FE0C_PORT54_PIN_REG                         _at_ 0xFE0C;
volatile BYTE xdata MCU_FE0D_PORT55_PIN_REG                         _at_ 0xFE0D;
volatile BYTE xdata MCU_FE0E_PORT56_PIN_REG                         _at_ 0xFE0E;
volatile BYTE xdata MCU_FE0F_PORT57_PIN_REG                         _at_ 0xFE0F;
volatile BYTE xdata MCU_FE10_PORT60_PIN_REG                         _at_ 0xFE10;
volatile BYTE xdata MCU_FE11_PORT61_PIN_REG                         _at_ 0xFE11;
volatile BYTE xdata MCU_FE12_PORT62_PIN_REG                         _at_ 0xFE12;
volatile BYTE xdata MCU_FE13_PORT63_PIN_REG                         _at_ 0xFE13;
volatile BYTE xdata MCU_FE14_PORT64_PIN_REG                         _at_ 0xFE14;
volatile BYTE xdata MCU_FE15_PORT65_PIN_REG                         _at_ 0xFE15;
volatile BYTE xdata MCU_FE16_PORT66_PIN_REG                         _at_ 0xFE16;
volatile BYTE xdata MCU_FE17_PORT67_PIN_REG                         _at_ 0xFE17;
volatile BYTE xdata MCU_FE18_PORT70_PIN_REG                         _at_ 0xFE18;
volatile BYTE xdata MCU_FE19_PORT71_PIN_REG                         _at_ 0xFE19;
volatile BYTE xdata MCU_FE1A_PORT72_PIN_REG                         _at_ 0xFE1A;
volatile BYTE xdata MCU_FE1B_PORT73_PIN_REG                         _at_ 0xFE1B;
volatile BYTE xdata MCU_FE1C_PORT74_PIN_REG                         _at_ 0xFE1C;
volatile BYTE xdata MCU_FE1D_PORT75_PIN_REG                         _at_ 0xFE1D;
volatile BYTE xdata MCU_FE1E_PORT76_PIN_REG                         _at_ 0xFE1E;
volatile BYTE xdata MCU_FE1F_PORT77_PIN_REG                         _at_ 0xFE1F;
volatile BYTE xdata MCU_FE20_PORT80_PIN_REG                         _at_ 0xFE20;
volatile BYTE xdata MCU_FE21_PORT81_PIN_REG                         _at_ 0xFE21;
volatile BYTE xdata MCU_FE22_PORT82_PIN_REG                         _at_ 0xFE22;
volatile BYTE xdata MCU_FE23_PORT83_PIN_REG                         _at_ 0xFE23;
volatile BYTE xdata MCU_FE24_PORT84_PIN_REG                         _at_ 0xFE24;
volatile BYTE xdata MCU_FE25_PORT85_PIN_REG                         _at_ 0xFE25;
volatile BYTE xdata MCU_FE26_PORT86_PIN_REG                         _at_ 0xFE26;
volatile BYTE xdata MCU_FE27_PORT87_PIN_REG                         _at_ 0xFE27;
volatile BYTE xdata MCU_FE28_PORT90_PIN_REG                         _at_ 0xFE28;
volatile BYTE xdata MCU_FE29_PORT91_PIN_REG                         _at_ 0xFE29;
volatile BYTE xdata MCU_FE2A_PORT92_PIN_REG                         _at_ 0xFE2A;
volatile BYTE xdata MCU_FE2B_PORT93_PIN_REG                         _at_ 0xFE2B;
volatile BYTE xdata MCU_FE2C_PORT94_PIN_REG                         _at_ 0xFE2C;
volatile BYTE xdata MCU_FE2D_PORT95_PIN_REG                         _at_ 0xFE2D;
volatile BYTE xdata MCU_FE2E_PORT96_PIN_REG                         _at_ 0xFE2E;
volatile BYTE xdata MCU_FE2F_PORT97_PIN_REG                         _at_ 0xFE2F;
volatile BYTE xdata MCU_FE30_PORTA0_PIN_REG                         _at_ 0xFE30;
volatile BYTE xdata MCU_FE31_PORTA1_PIN_REG                         _at_ 0xFE31;
volatile BYTE xdata MCU_FE32_PORTA2_PIN_REG                         _at_ 0xFE32;
volatile BYTE xdata MCU_FE33_PORTA3_PIN_REG                         _at_ 0xFE33;
volatile BYTE xdata MCU_FE34_PORTA4_PIN_REG                         _at_ 0xFE34;
volatile BYTE xdata MCU_FE35_PORTA5_PIN_REG                         _at_ 0xFE35;
volatile BYTE xdata MCU_FE36_PORTA6_PIN_REG                         _at_ 0xFE36;
volatile BYTE xdata MCU_FE37_PORTA7_PIN_REG                         _at_ 0xFE37;
volatile BYTE xdata MCU_FE38_PORTB0_PIN_REG                         _at_ 0xFE38;
volatile BYTE xdata MCU_FE39_PORTB1_PIN_REG                         _at_ 0xFE39;
volatile BYTE xdata MCU_FE3A_PORTB2_PIN_REG                         _at_ 0xFE3A;
volatile BYTE xdata MCU_FE3B_PORTB3_PIN_REG                         _at_ 0xFE3B;
volatile BYTE xdata MCU_FE3C_PORTB4_PIN_REG                         _at_ 0xFE3C;
volatile BYTE xdata MCU_FE3D_PORTB5_PIN_REG                         _at_ 0xFE3D;
volatile BYTE xdata MCU_FE3E_PORTB6_PIN_REG                         _at_ 0xFE3E;
volatile BYTE xdata MCU_FE3F_PORTB7_PIN_REG                         _at_ 0xFE3F;
volatile BYTE xdata MCU_FE40_PORTC0_PIN_REG                         _at_ 0xFE40;
volatile BYTE xdata MCU_FE41_PORTC1_PIN_REG                         _at_ 0xFE41;
volatile BYTE xdata MCU_FE42_PORTC2_PIN_REG                         _at_ 0xFE42;
volatile BYTE xdata MCU_FE43_PORTC3_PIN_REG                         _at_ 0xFE43;
volatile BYTE xdata MCU_FE44_PORTC4_PIN_REG                         _at_ 0xFE44;
volatile BYTE xdata MCU_FE45_PORTC5_PIN_REG                         _at_ 0xFE45;
volatile BYTE xdata MCU_FE46_PORTC6_PIN_REG                         _at_ 0xFE46;
volatile BYTE xdata MCU_FE47_PORTC7_PIN_REG                         _at_ 0xFE47;
volatile BYTE xdata MCU_FE48_PORTD0_PIN_REG                         _at_ 0xFE48;
volatile BYTE xdata MCU_FE49_PORTD1_PIN_REG                         _at_ 0xFE49;
volatile BYTE xdata MCU_FE4A_PORTD2_PIN_REG                         _at_ 0xFE4A;
volatile BYTE xdata MCU_FE4B_PORTD3_PIN_REG                         _at_ 0xFE4B;
volatile BYTE xdata MCU_FE4C_PORTD4_PIN_REG                         _at_ 0xFE4C;
volatile BYTE xdata MCU_FE4D_PORTD5_PIN_REG                         _at_ 0xFE4D;
volatile BYTE xdata MCU_FE4E_PORTD6_PIN_REG                         _at_ 0xFE4E;
volatile BYTE xdata MCU_FE4F_PORTD7_PIN_REG                         _at_ 0xFE4F;
volatile BYTE xdata MCU_FE50_PORTE0_PIN_REG                         _at_ 0xFE50;
volatile BYTE xdata MCU_FE51_PORTE1_PIN_REG                         _at_ 0xFE51;
volatile BYTE xdata MCU_FE52_PORTE2_PIN_REG                         _at_ 0xFE52;
volatile BYTE xdata MCU_FE53_PORTE3_PIN_REG                         _at_ 0xFE53;
volatile BYTE xdata MCU_FE54_PORTE4_PIN_REG                         _at_ 0xFE54;
volatile BYTE xdata MCU_FE55_PORTE5_PIN_REG                         _at_ 0xFE55;
volatile BYTE xdata MCU_FE56_PORTE6_PIN_REG                         _at_ 0xFE56;
volatile BYTE xdata MCU_FE57_PORTE7_PIN_REG                         _at_ 0xFE57;
volatile BYTE xdata MCU_FE58_PORTF0_PIN_REG                         _at_ 0xFE58;
volatile BYTE xdata MCU_FE59_PORTF1_PIN_REG                         _at_ 0xFE59;
volatile BYTE xdata MCU_FE5A_PORTF2_PIN_REG                         _at_ 0xFE5A;
volatile BYTE xdata MCU_FE5B_PORTF3_PIN_REG                         _at_ 0xFE5B;
volatile BYTE xdata MCU_FE5C_PORTF4_PIN_REG                         _at_ 0xFE5C;
volatile BYTE xdata MCU_FE60_PORT_READ_CONTROL                      _at_ 0xFE60;
volatile BYTE xdata MCU_FE61_PORT_READ_CONTROL_2                    _at_ 0xFE61;
volatile BYTE xdata MCU_FE62_DDC2_SEGMENT_ADDRESS                   _at_ 0xFE62;
volatile BYTE xdata MCU_FE63_DDC2_SEGMENT_DATA                      _at_ 0xFE63;
volatile BYTE xdata MCU_FE64_DDC2_DDC_ENABLE                        _at_ 0xFE64;
volatile BYTE xdata MCU_FE65_DDC2_DDC_CONTROL_1                     _at_ 0xFE65;
volatile BYTE xdata MCU_FE66_DDC2_DDC_CONTROL_2                     _at_ 0xFE66;
volatile BYTE xdata MCU_FE67_DDC2_DDC_INDEX                         _at_ 0xFE67;
volatile BYTE xdata MCU_FE68_DDC2_DDC_ACCESS_PORT                   _at_ 0xFE68;
volatile BYTE xdata MCU_FE69_DDC2_EDID_IRQ                          _at_ 0xFE69;
volatile BYTE xdata MCU_FE6A_DDC2_RESERVED                          _at_ 0xFE6A;
volatile BYTE xdata MCU_FE6B_DDC3_SEGMENT_ADDRESS                   _at_ 0xFE6B;
volatile BYTE xdata MCU_FE6C_DDC3_SEGMENT_DATA                      _at_ 0xFE6C;
volatile BYTE xdata MCU_FE6D_DDC3_DDC_ENABLE                        _at_ 0xFE6D;
volatile BYTE xdata MCU_FE6E_DDC3_DDC_CONTROL_1                     _at_ 0xFE6E;
volatile BYTE xdata MCU_FE6F_DDC3_DDC_CONTROL_2                     _at_ 0xFE6F;
volatile BYTE xdata MCU_FE70_DDC3_DDC_INDEX                         _at_ 0xFE70;
volatile BYTE xdata MCU_FE71_DDC3_DDC_ACCESS_PORT                   _at_ 0xFE71;
volatile BYTE xdata MCU_FE72_DDC3_EDID_IRQ                          _at_ 0xFE72;
volatile BYTE xdata MCU_FE73_DDC3_RESERVED                          _at_ 0xFE73;
volatile BYTE xdata MCU_FE74_DDC4_SEGMENT_ADDRESS                   _at_ 0xFE74;
volatile BYTE xdata MCU_FE75_DDC4_SEGMENT_DATA                      _at_ 0xFE75;
volatile BYTE xdata MCU_FE76_DDC4_DDC_ENABLE                        _at_ 0xFE76;
volatile BYTE xdata MCU_FE77_DDC4_DDC_CONTROL_1                     _at_ 0xFE77;
volatile BYTE xdata MCU_FE78_DDC4_DDC_CONTROL_2                     _at_ 0xFE78;
volatile BYTE xdata MCU_FE79_DDC4_DDC_INDEX                         _at_ 0xFE79;
volatile BYTE xdata MCU_FE7A_DDC4_DDC_ACCESS_PORT                   _at_ 0xFE7A;
volatile BYTE xdata MCU_FE7B_DDC4_EDID_IRQ                          _at_ 0xFE7B;
volatile BYTE xdata MCU_FE7C_DDC4_RESERVED                          _at_ 0xFE7C;
volatile BYTE xdata MCU_FE7D_DDC5_SEGMENT_ADDRESS                   _at_ 0xFE7D;
volatile BYTE xdata MCU_FE7E_DDC5_SEGMENT_DATA                      _at_ 0xFE7E;
volatile BYTE xdata MCU_FE7F_DDC5_DDC_ENABLE                        _at_ 0xFE7F;
volatile BYTE xdata MCU_FE80_DDC5_DDC_CONTROL_1                     _at_ 0xFE80;
volatile BYTE xdata MCU_FE81_DDC5_DDC_CONTROL_2                     _at_ 0xFE81;
volatile BYTE xdata MCU_FE82_DDC5_DDC_INDEX                         _at_ 0xFE82;
volatile BYTE xdata MCU_FE83_DDC5_DDC_ACCESS_PORT                   _at_ 0xFE83;
volatile BYTE xdata MCU_FE84_DDC5_EDID_IRQ                          _at_ 0xFE84;
volatile BYTE xdata MCU_FE85_DDC5_RESERVED                          _at_ 0xFE85;
volatile BYTE xdata MCU_FE86_IIC_1_CH_SEL                           _at_ 0xFE86;
volatile BYTE xdata MCU_FE87_IIC_1_SET_SLAVE                        _at_ 0xFE87;
volatile BYTE xdata MCU_FE88_IIC_1_SUB_IN                           _at_ 0xFE88;
volatile BYTE xdata MCU_FE89_IIC_1_DATA_IN                          _at_ 0xFE89;
volatile BYTE xdata MCU_FE8A_IIC_1_DATA_OUT                         _at_ 0xFE8A;
volatile BYTE xdata MCU_FE8B_IIC_1_STATUS                           _at_ 0xFE8B;
volatile BYTE xdata MCU_FE8C_IIC_1_IRQ_CONTROL                      _at_ 0xFE8C;
volatile BYTE xdata MCU_FE8D_IIC_1_STATUS2                          _at_ 0xFE8D;
volatile BYTE xdata MCU_FE8E_IIC_1_IRQ_CONTROL2                     _at_ 0xFE8E;
volatile BYTE xdata MCU_FE8F_IIC_1_CHANNEL_CONTROL                  _at_ 0xFE8F;
volatile BYTE xdata MCU_FE90_DDCCI_1_NULL_BYTE1                     _at_ 0xFE90;
volatile BYTE xdata MCU_FE91_DDCCI_1_NULL_BYTE2                     _at_ 0xFE91;
volatile BYTE xdata MCU_FE92_DDCCI_1_NULL_BYTE3                     _at_ 0xFE92;
volatile BYTE xdata MCU_FE93_DDCCI_1_REMAIN_DATA                    _at_ 0xFE93;
volatile BYTE xdata MCU_FE94_IIC_2_CH_SEL                           _at_ 0xFE94;
volatile BYTE xdata MCU_FE95_IIC_2_SET_SLAVE                        _at_ 0xFE95;
volatile BYTE xdata MCU_FE96_IIC_2_SUB_IN                           _at_ 0xFE96;
volatile BYTE xdata MCU_FE97_IIC_2_DATA_IN                          _at_ 0xFE97;
volatile BYTE xdata MCU_FE98_IIC_2_DATA_OUT                         _at_ 0xFE98;
volatile BYTE xdata MCU_FE99_IIC_2_STATUS                           _at_ 0xFE99;
volatile BYTE xdata MCU_FE9A_IIC_2_IRQ_CONTROL                      _at_ 0xFE9A;
volatile BYTE xdata MCU_FE9B_IIC_2_STATUS2                          _at_ 0xFE9B;
volatile BYTE xdata MCU_FE9C_IIC_2_IRQ_CONTROL2                     _at_ 0xFE9C;
volatile BYTE xdata MCU_FE9D_IIC_2_CHANNEL_CONTROL                  _at_ 0xFE9D;
volatile BYTE xdata MCU_FE9E_DDCCI_2_NULL_BYTE1                     _at_ 0xFE9E;
volatile BYTE xdata MCU_FEA0_DDCCI_2_NULL_BYTE2                     _at_ 0xFEA0;
volatile BYTE xdata MCU_FEA1_DDCCI_2_NULL_BYTE3                     _at_ 0xFEA1;
volatile BYTE xdata MCU_FEA2_DDCCI_2_REMAIN_DATA                    _at_ 0xFEA2;
volatile BYTE xdata MCU_FEA3_IIC_3_CH_SEL                           _at_ 0xFEA3;
volatile BYTE xdata MCU_FEA4_IIC_3_SET_SLAVE                        _at_ 0xFEA4;
volatile BYTE xdata MCU_FEA5_IIC_3_SUB_IN                           _at_ 0xFEA5;
volatile BYTE xdata MCU_FEA6_IIC_3_DATA_IN                          _at_ 0xFEA6;
volatile BYTE xdata MCU_FEA7_IIC_3_DATA_OUT                         _at_ 0xFEA7;
volatile BYTE xdata MCU_FEA8_IIC_3_STATUS                           _at_ 0xFEA8;
volatile BYTE xdata MCU_FEA9_IIC_3_IRQ_CONTROL                      _at_ 0xFEA9;
volatile BYTE xdata MCU_FEAA_IIC_3_STATUS2                          _at_ 0xFEAA;
volatile BYTE xdata MCU_FEAB_IIC_3_IRQ_CONTROL2                     _at_ 0xFEAB;
volatile BYTE xdata MCU_FEAC_IIC_3_CHANNEL_CONTROL                  _at_ 0xFEAC;
volatile BYTE xdata MCU_FEAD_DDCCI_3_NULL_BYTE1                     _at_ 0xFEAD;
volatile BYTE xdata MCU_FEAE_DDCCI_3_NULL_BYTE2                     _at_ 0xFEAE;
volatile BYTE xdata MCU_FEAF_DDCCI_3_NULL_BYTE3                     _at_ 0xFEAF;
volatile BYTE xdata MCU_FEB0_DDCCI_3_REMAIN_DATA                    _at_ 0xFEB0;
volatile BYTE xdata MCU_FEB1_DDCRAM_ST_ADDRESS                      _at_ 0xFEB1;
volatile BYTE xdata MCU_FEB2_XRAM_BIST_CTRL                         _at_ 0xFEB2;
volatile BYTE xdata MCU_FEB3_XRAM_DRF_BIST_CTRL                     _at_ 0xFEB3;
volatile BYTE xdata MCU_FEB4_MCU_DUMMY2                             _at_ 0xFEB4;


//--------------------------------------------------
// EMCU (Page FF)
//--------------------------------------------------
volatile BYTE xdata MCU_FF00_IRQ_STATUS                             _at_ 0xFF00;
volatile BYTE xdata MCU_FF03_TRIPLE_BYTES_OPERATION                 _at_ 0xFF03;
volatile BYTE xdata MCU_FF04_SHIFT_BITS_NUMBER                      _at_ 0xFF04;
volatile BYTE xdata MCU_FF05_SHIFT_BYTE_ADDRESS                     _at_ 0xFF05;
volatile BYTE xdata MCU_FF06_INPUT_TRIPLE_BYTES                     _at_ 0xFF06;
volatile BYTE xdata MCU_FF07_RESULT_TRIPLE_BYTES                    _at_ 0xFF07;
volatile BYTE xdata MCU_FF08_ADC_ACONTROL                           _at_ 0xFF08;
volatile BYTE xdata MCU_FF09_ADC_A0_CONVERT_RESULT                  _at_ 0xFF09;
volatile BYTE xdata MCU_FF0A_ADC_A1_CONVERT_RESULT                  _at_ 0xFF0A;
volatile BYTE xdata MCU_FF0B_ADC_A2_CONVERT_RESULT                  _at_ 0xFF0B;
volatile BYTE xdata MCU_FF0C_ADC_A3_CONVERT_RESULT                  _at_ 0xFF0C;
volatile BYTE xdata MCU_FF0D_ADC_CLK_DIV                            _at_ 0xFF0D;
volatile BYTE xdata MCU_FF0E_AUTO_MODE_CTRL01                       _at_ 0xFF0E;
volatile BYTE xdata MCU_FF0F_ADC0_THRESHOLD_H                       _at_ 0xFF0F;
volatile BYTE xdata MCU_FF10_ADC0_THRESHOLD_L                       _at_ 0xFF10;
volatile BYTE xdata MCU_FF11_ADC1_THRESHOLD_H                       _at_ 0xFF11;
volatile BYTE xdata MCU_FF12_ADC1_THRESHOLD_L                       _at_ 0xFF12;
volatile BYTE xdata MCU_FF13_ADC2_THRESHOLD_H                       _at_ 0xFF13;
volatile BYTE xdata MCU_FF14_ADC2_THRESHOLD_L                       _at_ 0xFF14;
volatile BYTE xdata MCU_FF15_ADC3_THRESHOLD_H                       _at_ 0xFF15;
volatile BYTE xdata MCU_FF16_ADC3_THRESHOLD_L                       _at_ 0xFF16;
volatile BYTE xdata MCU_FF17_CTRL0_WAIT_TIME_VALUE                  _at_ 0xFF17;
volatile BYTE xdata MCU_FF18_BYTE_ADDRESS                           _at_ 0xFF18;
volatile BYTE xdata MCU_FF19_ADC_SEGMENT_ADDRESS                    _at_ 0xFF19;
volatile BYTE xdata MCU_FF1A_ADC_SEGMENT_DATA                       _at_ 0xFF1A;
volatile BYTE xdata MCU_FF1B_ADC_DDC_ENABLE                         _at_ 0xFF1B;
volatile BYTE xdata MCU_FF1C_ADC_DDC_CONTROL_1                      _at_ 0xFF1C;
volatile BYTE xdata MCU_FF1D_ADC_DDC_CONTROL_2                      _at_ 0xFF1D;
volatile BYTE xdata MCU_FF1E_DDC0_DDC_ENABLE                        _at_ 0xFF1E;
volatile BYTE xdata MCU_FF1F_DDC0_DDC_CONTROL_1                     _at_ 0xFF1F;
volatile BYTE xdata MCU_FF20_DDC0_DDC_CONTROL_2                     _at_ 0xFF20;
volatile BYTE xdata MCU_FF22_IIC_CH_SEL                             _at_ 0xFF22;
volatile BYTE xdata MCU_FF23_IIC_SET_SLAVE                          _at_ 0xFF23;
volatile BYTE xdata MCU_FF24_IIC_SUB_IN                             _at_ 0xFF24;
volatile BYTE xdata MCU_FF25_IIC_DATA_IN                            _at_ 0xFF25;
volatile BYTE xdata MCU_FF26_IIC_DATA_OUT                           _at_ 0xFF26;
volatile BYTE xdata MCU_FF27_IIC_STATUS                             _at_ 0xFF27;
volatile BYTE xdata MCU_FF28_IIC_IRQ_CONTROL                        _at_ 0xFF28;
volatile BYTE xdata MCU_FF29_IIC_STATUS2                            _at_ 0xFF29;
volatile BYTE xdata MCU_FF2A_IIC_IRQ_CONTROL2                       _at_ 0xFF2A;
volatile BYTE xdata MCU_FF2B_IIC_CHANNEL_CONTROL                    _at_ 0xFF2B;
volatile BYTE xdata MCU_FF2C_DDC1_DDC_ENABLE                        _at_ 0xFF2C;
volatile BYTE xdata MCU_FF2D_DDC1_DDC_CONTROL_1                     _at_ 0xFF2D;
volatile BYTE xdata MCU_FF2E_DDC1_DDC_CONTROL_2                     _at_ 0xFF2E;
volatile BYTE xdata MCU_FF2F_ADC_DDC_INDEX                          _at_ 0xFF2F;
volatile BYTE xdata MCU_FF30_ADC_DDC_ACCESS_PORT                    _at_ 0xFF30;
volatile BYTE xdata MCU_FF31_DDC0_DDC_INDEX                         _at_ 0xFF31;
volatile BYTE xdata MCU_FF32_DDC0_DDC_ACCESS_PORT                   _at_ 0xFF32;
volatile BYTE xdata MCU_FF33_DDC1_DDC_INDEX                         _at_ 0xFF33;
volatile BYTE xdata MCU_FF34_DDC1_DDC_ACCESS_PORT                   _at_ 0xFF34;
volatile BYTE xdata MCU_FF35_DDCCI_REMAIN_DATA                      _at_ 0xFF35;
volatile BYTE xdata MCU_FF36_DDC0_SEGMENT_ADDRESS                   _at_ 0xFF36;
volatile BYTE xdata MCU_FF37_DDC0_SEGMENT_DATA                      _at_ 0xFF37;
volatile BYTE xdata MCU_FF38_DDC1_SEGMENT_ADDRESS                   _at_ 0xFF38;
volatile BYTE xdata MCU_FF39_DDC1_SEGMENT_DATA                      _at_ 0xFF39;
volatile BYTE xdata MCU_FF3A_PWM_CK_SEL                             _at_ 0xFF3A;
volatile BYTE xdata MCU_FF3B_PWM03_M                                _at_ 0xFF3B;
volatile BYTE xdata MCU_FF3C_PWM45_M                                _at_ 0xFF3C;
volatile BYTE xdata MCU_FF3D_PWM01_N_MSB                            _at_ 0xFF3D;
volatile BYTE xdata MCU_FF3E_PWM0_N_LSB                             _at_ 0xFF3E;
volatile BYTE xdata MCU_FF3F_PWM1_N_LSB                             _at_ 0xFF3F;
volatile BYTE xdata MCU_FF40_PWM23_N_MSB                            _at_ 0xFF40;
volatile BYTE xdata MCU_FF41_PWM2_N_LSB                             _at_ 0xFF41;
volatile BYTE xdata MCU_FF42_PWM3_N_LSB                             _at_ 0xFF42;
volatile BYTE xdata MCU_FF43_PWM45_N_MSB                            _at_ 0xFF43;
volatile BYTE xdata MCU_FF44_PWM4_N_LSB                             _at_ 0xFF44;
volatile BYTE xdata MCU_FF45_PWM5_N_LSB                             _at_ 0xFF45;
volatile BYTE xdata MCU_FF46_PWML                                   _at_ 0xFF46;
volatile BYTE xdata MCU_FF47_PWM_VS_CTRL                            _at_ 0xFF47;
volatile BYTE xdata MCU_FF48_PWM_EN                                 _at_ 0xFF48;
volatile BYTE xdata MCU_FF49_PWM_CK                                 _at_ 0xFF49;
volatile BYTE xdata MCU_FF4A_PWM0H_DUT                              _at_ 0xFF4A;
volatile BYTE xdata MCU_FF4B_PWM1H_DUT                              _at_ 0xFF4B;
volatile BYTE xdata MCU_FF4C_PWM01L_DUT                             _at_ 0xFF4C;
volatile BYTE xdata MCU_FF4D_PWM2H_DUT                              _at_ 0xFF4D;
volatile BYTE xdata MCU_FF4E_PWM3H_DUT                              _at_ 0xFF4E;
volatile BYTE xdata MCU_FF4F_PWM23L_DUT                             _at_ 0xFF4F;
volatile BYTE xdata MCU_FF50_PWM4H_DUT                              _at_ 0xFF50;
volatile BYTE xdata MCU_FF51_PWM5H_DUT                              _at_ 0xFF51;
volatile BYTE xdata MCU_FF52_PWM45L_DUT                             _at_ 0xFF52;
volatile BYTE xdata MCU_FF53_PWM_DUT_TYPE                           _at_ 0xFF53;
volatile BYTE xdata MCU_FF54_PWM_CNT_MODE                           _at_ 0xFF54;
volatile BYTE xdata MCU_FF55_I2CM_CR0                               _at_ 0xFF55;
volatile BYTE xdata MCU_FF56_I2CM_CR1                               _at_ 0xFF56;
volatile BYTE xdata MCU_FF57_I2CM_CR2                               _at_ 0xFF57;
volatile BYTE xdata MCU_FF58_I2CM_CR3                               _at_ 0xFF58;
volatile BYTE xdata MCU_FF59_I2CM_STR0                              _at_ 0xFF59;
volatile BYTE xdata MCU_FF5A_I2CM_STR1                              _at_ 0xFF5A;
volatile BYTE xdata MCU_FF5B_I2CM_STR2                              _at_ 0xFF5B;
volatile BYTE xdata MCU_FF5C_I2CM_STR3                              _at_ 0xFF5C;
volatile BYTE xdata MCU_FF5D_I2CM_SR                                _at_ 0xFF5D;
volatile BYTE xdata MCU_FF5E_I2CM_TD                                _at_ 0xFF5E;
volatile BYTE xdata MCU_FF5F_I2CM_CCR                               _at_ 0xFF5F;
volatile BYTE xdata MCU_FF60_COMMON_INST_EN                         _at_ 0xFF60;
volatile BYTE xdata MCU_FF61_COMMON_OP_CODE                         _at_ 0xFF61;
volatile BYTE xdata MCU_FF62_WREN_OP_CODE                           _at_ 0xFF62;
volatile BYTE xdata MCU_FF63_EWSR_OP_CODE                           _at_ 0xFF63;
volatile BYTE xdata MCU_FF64_FLASH_PROG_ISP0                        _at_ 0xFF64;
volatile BYTE xdata MCU_FF65_FLASH_PROG_ISP1                        _at_ 0xFF65;
volatile BYTE xdata MCU_FF66_FLASH_PROG_ISP2                        _at_ 0xFF66;
volatile BYTE xdata MCU_FF67_COMMON_INST_READ_PORT0                 _at_ 0xFF67;
volatile BYTE xdata MCU_FF68_COMMON_INST_READ_PORT1                 _at_ 0xFF68;
volatile BYTE xdata MCU_FF69_COMMON_INST_READ_PORT2                 _at_ 0xFF69;
volatile BYTE xdata MCU_FF6A_READ_OP_CODE                           _at_ 0xFF6A;
volatile BYTE xdata MCU_FF6B_FAST_READ_OP_CODE                      _at_ 0xFF6B;
volatile BYTE xdata MCU_FF6C_READ_INSTRUCTION                       _at_ 0xFF6C;
volatile BYTE xdata MCU_FF6D_PROGRAM_OP_CODE                        _at_ 0xFF6D;
volatile BYTE xdata MCU_FF6E_READ_STATUS_REGISTER_OP_CODE           _at_ 0xFF6E;
volatile BYTE xdata MCU_FF6F_PROGRAM_INSTRUCTION                    _at_ 0xFF6F;
volatile BYTE xdata MCU_FF70_PROGRAM_DATA_PORT                      _at_ 0xFF70;
volatile BYTE xdata MCU_FF71_PROGRAM_LENGTH                         _at_ 0xFF71;
volatile BYTE xdata MCU_FF72_CRC_END_ADDR0                          _at_ 0xFF72;
volatile BYTE xdata MCU_FF73_CRC_END_ADDR1                          _at_ 0xFF73;
volatile BYTE xdata MCU_FF74_CRC_END_ADDR2                          _at_ 0xFF74;
volatile BYTE xdata MCU_FF75_CRC_RESULT                             _at_ 0xFF75;
volatile BYTE xdata MCU_FF76_CEN_CTRL                               _at_ 0xFF76;
volatile BYTE xdata MCU_FF77_REV_DUMMY4                             _at_ 0xFF77;
volatile BYTE xdata MCU_FF78_ACCESS_FLASH_ADDR_0                    _at_ 0xFF78;
volatile BYTE xdata MCU_FF79_ACCESS_FLASH_ADDR_1                    _at_ 0xFF79;
volatile BYTE xdata MCU_FF7A_ACCESS_FLASH_ADDR_2                    _at_ 0xFF7A;
volatile BYTE xdata MCU_FF7B_ACCESS_FLASH_DATA_PORT                 _at_ 0xFF7B;
volatile BYTE xdata MCU_FF7C_ACCESS_FLASH_DATA_CTRL                 _at_ 0xFF7C;
volatile BYTE xdata MCU_FF80_AAI_MODE_BYTE_NUM                      _at_ 0xFF80;
volatile BYTE xdata MCU_FF81_ISP_CMD_INSERT                         _at_ 0xFF81;
volatile BYTE xdata MCU_FF82_ISP_CMD_LENGTH                         _at_ 0xFF82;
volatile BYTE xdata MCU_FF83_I2CS_CTRL0                             _at_ 0xFF83;
volatile BYTE xdata MCU_FF84_I2CS_CTRL1                             _at_ 0xFF84;
volatile BYTE xdata MCU_FF85_I2CS_CTRL2                             _at_ 0xFF85;
volatile BYTE xdata MCU_FF86_I2CS_STATUS0                           _at_ 0xFF86;
volatile BYTE xdata MCU_FF87_I2CS_STATUS1                           _at_ 0xFF87;
volatile BYTE xdata MCU_FF88_I2CS_BUFLEN                            _at_ 0xFF88;
volatile BYTE xdata MCU_FF90_PWM01_TOTALCNT_MSB                     _at_ 0xFF90;
volatile BYTE xdata MCU_FF91_PWM0_TOTALCNT_LSB                      _at_ 0xFF91;
volatile BYTE xdata MCU_FF92_PWM1_TOTALCNT_LSB                      _at_ 0xFF92;
volatile BYTE xdata MCU_FF93_PWM23_TOTALCNT_MSB                     _at_ 0xFF93;
volatile BYTE xdata MCU_FF94_PWM2_TOTALCNT_LSB                      _at_ 0xFF94;
volatile BYTE xdata MCU_FF95_PWM3_TOTALCNT_LSB                      _at_ 0xFF95;
volatile BYTE xdata MCU_FF96_PWM45_TOTALCNT_MSB                     _at_ 0xFF96;
volatile BYTE xdata MCU_FF97_PWM4_TOTALCNT_LSB                      _at_ 0xFF97;
volatile BYTE xdata MCU_FF98_PWM5_TOTALCNT_LSB                      _at_ 0xFF98;
volatile BYTE xdata MCU_FF99_PWM_CK_SEL_HS                          _at_ 0xFF99;
volatile BYTE xdata MCU_FF9A_PWM01_CYCLE_MAX                        _at_ 0xFF9A;
volatile BYTE xdata MCU_FF9B_PWM23_CYCLE_MAX                        _at_ 0xFF9B;
volatile BYTE xdata MCU_FF9C_PWM45_CYCLE_MAX                        _at_ 0xFF9C;
volatile BYTE xdata MCU_FF9D_SPI_CAL_CTRL                           _at_ 0xFF9D;
volatile BYTE xdata MCU_FF9E_SPI_CAL_RESULT                         _at_ 0xFF9E;
volatile BYTE xdata MCU_FF9F_SPI_CAL_DATA_00                        _at_ 0xFF9F;
volatile BYTE xdata MCU_FFA5_SPI_CAL_DATA_01                        _at_ 0xFFA5;
volatile BYTE xdata MCU_FFA6_SPI_CAL_DATA_02                        _at_ 0xFFA6;
volatile BYTE xdata MCU_FFA7_SPI_CAL_ADR_H                          _at_ 0xFFA7;
volatile BYTE xdata MCU_FFA8_SPI_CAL_ADR_M                          _at_ 0xFFA8;
volatile BYTE xdata MCU_FFA9_SPI_CAL_ADR_L                          _at_ 0xFFA9;
volatile BYTE xdata MCU_FFAA_WATCHDOG_CNT2_VALUE                    _at_ 0xFFAA;
volatile BYTE xdata MCU_FFAB_WATCHDOG_CNT23_VALUE                   _at_ 0xFFAB;
volatile BYTE xdata MCU_FFAC_WATCHDOG_CNT3_VALUE                    _at_ 0xFFAC;
volatile BYTE xdata MCU_FFAD_WATCHDOG_CNT1_VALUE                    _at_ 0xFFAD;
volatile BYTE xdata MCU_FFAE_WATCHDOG_TIMER_THRESHOLD               _at_ 0xFFAE;
volatile BYTE xdata MCU_FFAF_WATCHDOG_TIMER_THRESHOLD_MASK          _at_ 0xFFAF;
volatile BYTE xdata MCU_FFB0_WATCHDOG_TIMER_H_THRESHOLD_MASK        _at_ 0xFFB0;
volatile BYTE xdata MCU_FFB1_DDCCI_NULL_BYTE1                       _at_ 0xFFB1;
volatile BYTE xdata MCU_FFB2_DDCCI_NULL_BYTE2                       _at_ 0xFFB2;
volatile BYTE xdata MCU_FFB3_DDCCI_NULL_BYTE3                       _at_ 0xFFB3;
volatile BYTE xdata MCU_FFB8_EXT_INT0_CONTROL                       _at_ 0xFFB8;
volatile BYTE xdata MCU_FFB9_EXT_INT1_CONTROL                       _at_ 0xFFB9;
volatile BYTE xdata MCU_FFBB_PERI_TEST                              _at_ 0xFFBB;
volatile BYTE xdata MCU_FFBC_CYCLE_GATING                           _at_ 0xFFBC;
volatile BYTE xdata MCU_FFBD_MCU_CLK_DIV_R                          _at_ 0xFFBD;
volatile BYTE xdata MCU_FFBE_MCU_DUMMY                              _at_ 0xFFBE;
volatile BYTE xdata MCU_FFC2_IRQ_PRIORITY_1                         _at_ 0xFFC2;
volatile BYTE xdata MCU_FFC3_IRQ_PRIORITY_2                         _at_ 0xFFC3;
volatile BYTE xdata MCU_FFC4_IRQ_PRIORITY_3                         _at_ 0xFFC4;


//--------------------------------------------------
// EMCU DDCRAM Control (Page FF)
//--------------------------------------------------
volatile BYTE xdata MCU_FFD0_A_DDCRAM_CONTROL                       _at_ 0xFFD0;
volatile BYTE xdata MCU_FFD1_DDCRAM0_CONTROL                        _at_ 0xFFD1;
volatile BYTE xdata MCU_FFD2_DDCRAM1_CONTROL                        _at_ 0xFFD2;
volatile BYTE xdata MCU_FFD3_DDCRAM2_CONTROL                        _at_ 0xFFD3;
volatile BYTE xdata MCU_FFD4_DDCRAM3_CONTROL                        _at_ 0xFFD4;
volatile BYTE xdata MCU_FFD5_DDCRAM4_CONTROL                        _at_ 0xFFD5;
volatile BYTE xdata MCU_FFD6_DDCRAM5_CONTROL                        _at_ 0xFFD6;


//--------------------------------------------------
// EMCU In System Programming Part 1 (Page FF)
//--------------------------------------------------
volatile BYTE xdata MCU_FFE0_ISP_FLAG                               _at_ 0xFFE0;
volatile BYTE xdata MCU_FFE2_PORT1_PIN_REG                          _at_ 0xFFE2;
volatile BYTE xdata MCU_FFE3_PORT3_PIN_REG                          _at_ 0xFFE3;
volatile BYTE xdata MCU_FFE4_DDC0_EDID_IRQ                          _at_ 0xFFE4;
volatile BYTE xdata MCU_FFE5_DDC1_EDID_IRQ                          _at_ 0xFFE5;
volatile BYTE xdata MCU_FFE7_VGA_EDID_IRQ                           _at_ 0xFFE7;
volatile BYTE xdata MCU_FFE8_ISP_CONTROL                            _at_ 0xFFE8;
volatile BYTE xdata MCU_FFE9_MCU_CLK_CONTROL_1                      _at_ 0xFFE9;
volatile BYTE xdata MCU_FFEA_WATCHDOG_TIMER                         _at_ 0xFFEA;
volatile BYTE xdata MCU_FFEB_WDT_TEST                               _at_ 0xFFEB;
volatile BYTE xdata MCU_FFEC_ISP_SLAVE_ADDRESS                      _at_ 0xFFEC;
volatile BYTE xdata MCU_FFED_MCU_CONTROL                            _at_ 0xFFED;
volatile BYTE xdata MCU_FFEE_MCU_CLOCK_CONTROL                      _at_ 0xFFEE;
volatile BYTE xdata MCU_FFEF_RAM_TEST                               _at_ 0xFFEF;
volatile BYTE xdata MCU_FFF0_XDATA_SPI_FLASH_WRITE_PROTECT          _at_ 0xFFF0;
volatile BYTE xdata MCU_FFF1_SCA_WR_INTRVL                          _at_ 0xFFF1;
volatile BYTE xdata MCU_FFF2_PWM_I2C_CLOCK_STOP                     _at_ 0xFFF2;
volatile BYTE xdata MCU_FFF3_SCA_INF_CONTROL                        _at_ 0xFFF3;
volatile BYTE xdata MCU_FFF4_SCA_INF_ADDR                           _at_ 0xFFF4;
volatile BYTE xdata MCU_FFF5_SCA_INF_DATA                           _at_ 0xFFF5;
volatile BYTE xdata MCU_FFF6_SCA_INF_BWR_ADRH                       _at_ 0xFFF6;
volatile BYTE xdata MCU_FFF7_SCA_INF_BWR_ADRM                       _at_ 0xFFF7;
volatile BYTE xdata MCU_FFF8_SCA_INF_BWR_ADRL                       _at_ 0xFFF8;
volatile BYTE xdata MCU_FFF9_SCA_INF_BWR_COUNT_H                    _at_ 0xFFF9;
volatile BYTE xdata MCU_FFFA_SCA_INF_BWR_COUNT_L                    _at_ 0xFFFA;
volatile BYTE xdata MCU_FFFB_SCA_INF_PERIOD                         _at_ 0xFFFB;
volatile BYTE xdata MCU_FFFC_BANK_SWICH_CONTROL                     _at_ 0xFFFC;
volatile BYTE xdata MCU_FFFD_XDATA_BANK_START                       _at_ 0xFFFD;
volatile BYTE xdata MCU_FFFE_XDATA_BANK_SEL                         _at_ 0xFFFE;
volatile BYTE xdata MCU_FFFF_PBANK_SWITCH                           _at_ 0xFFFF;


#if(_A0_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)
BYTE xdata MCU_DDCRAM_A0[_A0_EMBEDDED_DDCRAM_SIZE]          _at_ _EMBEDDED_DDCRAM_VGA_DDC_ADDRESS;
#endif

#if(_D0_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)

#if(_D0_DDC_CHANNEL_SEL == _DDC0)
#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
BYTE xdata MCU_DDCRAM_D0[_D7_D0_EMBEDDED_DDCRAM_SIZE]       _at_ _EMBEDDED_DDCRAM_DDC0_ADDRESS;
#else
BYTE xdata MCU_DDCRAM_D0[_D0_EMBEDDED_DDCRAM_SIZE]          _at_ _EMBEDDED_DDCRAM_DDC0_ADDRESS;
#endif
#endif // End of _DDC_CHANNEL_FOR_D0

#endif // End of #if(_D0_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)

#if(_D1_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)

#if(_D1_DDC_CHANNEL_SEL == _DDC1)
#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
BYTE xdata MCU_DDCRAM_D1[_D7_D1_EMBEDDED_DDCRAM_SIZE]       _at_ _EMBEDDED_DDCRAM_DDC1_ADDRESS;
#else
BYTE xdata MCU_DDCRAM_D1[_D1_EMBEDDED_DDCRAM_SIZE]          _at_ _EMBEDDED_DDCRAM_DDC1_ADDRESS;
#endif
#endif // End of _DDC_CHANNEL_FOR_D1

#endif // End of #if(_D1_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)

#if(_D2_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)

#if(_D2_DDC_CHANNEL_SEL == _DDC2)
BYTE xdata MCU_DDCRAM_D2[_D2_EMBEDDED_DDCRAM_SIZE]          _at_ _EMBEDDED_DDCRAM_DDC2_ADDRESS;
#endif // End of _DDC_CHANNEL_FOR_D2

#endif // End of #if(_D2_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)

#if(_D3_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)

#if(_D3_DDC_CHANNEL_SEL == _DDC3)
BYTE xdata MCU_DDCRAM_D3[_D3_EMBEDDED_DDCRAM_SIZE]          _at_ _EMBEDDED_DDCRAM_DDC3_ADDRESS;
#endif // End of _DDC_CHANNEL_FOR_D3

#endif // End of #if(_D3_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)

#if(_D4_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)

#if(_D4_DDC_CHANNEL_SEL == _DDC4)
BYTE xdata MCU_DDCRAM_D4[_D4_EMBEDDED_DDCRAM_SIZE]          _at_ _EMBEDDED_DDCRAM_DDC4_ADDRESS;
#endif // End of _DDC_CHANNEL_FOR_D4

#endif // End of #if(_D4_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)

#if(_D5_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)

#if(_D5_DDC_CHANNEL_SEL == _DDC5)
BYTE xdata MCU_DDCRAM_D5[_D5_EMBEDDED_DDCRAM_SIZE]          _at_ _EMBEDDED_DDCRAM_DDC5_ADDRESS;
#endif // End of _DDC_CHANNEL_FOR_D5

#endif // End of #if(_D5_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)

#if(_D6_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)
BYTE xdata MCU_DDCRAM_D6[_D6_EMBEDDED_DDCRAM_SIZE]          _at_ _EMBEDDED_DDCRAM_DDC6_ADDRESS;
#endif

#if(_D0_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)
BYTE xdata MCU_DDCRAM_MHL_D0[_D0_MHL_EMBEDDED_DDCRAM_SIZE]  _at_ _EMBEDDED_DDCRAM_DDC0_MHL_ADDRESS;
#endif

#if(_D1_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)
BYTE xdata MCU_DDCRAM_MHL_D1[_D1_MHL_EMBEDDED_DDCRAM_SIZE]  _at_ _EMBEDDED_DDCRAM_DDC1_MHL_ADDRESS;
#endif

#if(_D2_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)
BYTE xdata MCU_DDCRAM_MHL_D2[_D2_MHL_EMBEDDED_DDCRAM_SIZE]  _at_ _EMBEDDED_DDCRAM_DDC2_MHL_ADDRESS;
#endif

#if(_D3_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)
BYTE xdata MCU_DDCRAM_MHL_D3[_D3_MHL_EMBEDDED_DDCRAM_SIZE]  _at_ _EMBEDDED_DDCRAM_DDC3_MHL_ADDRESS;
#endif

#if(_D4_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)
BYTE xdata MCU_DDCRAM_MHL_D4[_D4_MHL_EMBEDDED_DDCRAM_SIZE]  _at_ _EMBEDDED_DDCRAM_DDC4_MHL_ADDRESS;
#endif

#if(_D5_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)
BYTE xdata MCU_DDCRAM_MHL_D5[_D5_MHL_EMBEDDED_DDCRAM_SIZE]  _at_ _EMBEDDED_DDCRAM_DDC5_MHL_ADDRESS;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerMcuDdcDebounceSel(EnumClkSel enumClock);
void ScalerMcuGpioInitial(void);
void ScalerMcuDdcInitial(void);
void ScalerMcuDdcRamEnable(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : DDC Debounce Settings
// Input Value  : Clock --> _EXT_XTAL_CLK/_IOSC_CLK
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcDebounceSel(EnumClkSel enumClock)
{
    if(enumClock == _EXT_XTAL_CLK)
    {
        // VGA_DDC De-bounce Reference Clock(Xtal = 14.318M) div by 2, latch 3 stages
        MCU_FF1C_ADC_DDC_CONTROL_1 &= ~_BIT7;
        MCU_FF1C_ADC_DDC_CONTROL_1 |= (_BIT6 | _BIT5 | _BIT4);

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        // DDC0 De-bounce Reference Clock(Xtal = 14.318M) div by 1, latch 1 stages
        MCU_FF1F_DDC0_DDC_CONTROL_1 &= ~(_BIT7 | _BIT6);
        MCU_FF1F_DDC0_DDC_CONTROL_1 |= _BIT4;
#elif((_D0_INPUT_PORT_TYPE == _D0_DVI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT))
        // DDC0 De-bounce Reference Clock(Xtal = 14.318M) div by 2, latch 3 stages
        MCU_FF1F_DDC0_DDC_CONTROL_1 &= ~_BIT7;
        MCU_FF1F_DDC0_DDC_CONTROL_1 |= (_BIT6 | _BIT5 | _BIT4);
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        // DDC1 De-bounce Reference Clock(Xtal = 14.318M) div by 1, latch 1 stages
        MCU_FF2D_DDC1_DDC_CONTROL_1 &= ~(_BIT7 | _BIT6);
        MCU_FF2D_DDC1_DDC_CONTROL_1 |= _BIT4;
#elif((_D1_INPUT_PORT_TYPE == _D1_DVI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
        // DDC1 De-bounce Reference Clock(Xtal = 14.318M) div by 2, latch 3 stages
        MCU_FF2D_DDC1_DDC_CONTROL_1 &= ~_BIT7;
        MCU_FF2D_DDC1_DDC_CONTROL_1 |= (_BIT6 | _BIT5 | _BIT4);
#endif

#if((_D2_INPUT_PORT_TYPE == _D2_DVI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
        // DDC2 De-bounce Reference Clock(Xtal = 14.318M) div by 2, latch 3 stages
        MCU_FE65_DDC2_DDC_CONTROL_1 &= ~_BIT7;
        MCU_FE65_DDC2_DDC_CONTROL_1 |= (_BIT6 | _BIT5 | _BIT4);
#endif

#if((_D3_INPUT_PORT_TYPE == _D3_DVI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT))
        // DDC3 De-bounce Reference Clock(Xtal = 14.318M) div by 2, latch 3 stages
        MCU_FE6E_DDC3_DDC_CONTROL_1 &= ~_BIT7;
        MCU_FE6E_DDC3_DDC_CONTROL_1 |= (_BIT6 | _BIT5 | _BIT4);
#endif

#if((_D4_INPUT_PORT_TYPE == _D4_DVI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT))
        // DDC4 De-bounce Reference Clock(Xtal = 14.318M) div by 2, latch 3 stages
        MCU_FE77_DDC4_DDC_CONTROL_1 &= ~_BIT7;
        MCU_FE77_DDC4_DDC_CONTROL_1 |= (_BIT6 | _BIT5 | _BIT4);
#endif

#if((_D5_INPUT_PORT_TYPE == _D5_DVI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT))
        // DDC5 De-bounce Reference Clock(Xtal = 14.318M) div by 2, latch 3 stages
        MCU_FE80_DDC5_DDC_CONTROL_1 &= ~_BIT7;
        MCU_FE80_DDC5_DDC_CONTROL_1 |= (_BIT6 | _BIT5 | _BIT4);
#endif
    }
    else
    {
        // VGA_DDC De-bounce Reference Clock(IOSC = 27M) div by 4, latch 3 stages
        MCU_FF1C_ADC_DDC_CONTROL_1 |= (_BIT7 | _BIT6 | _BIT5 | _BIT4);

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        // DDC0 De-bounce Reference Clock(IOSC = 27M) div by 2, latch 1 stages
        MCU_FF1F_DDC0_DDC_CONTROL_1 &= ~(_BIT7);
        MCU_FF1F_DDC0_DDC_CONTROL_1 |= (_BIT6 | _BIT4);
#elif((_D0_INPUT_PORT_TYPE == _D0_DVI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT))
        // DDC0 De-bounce Reference Clock(IOSC = 27M) div by 4, latch 3 stages
        MCU_FF1F_DDC0_DDC_CONTROL_1 |= (_BIT7 | _BIT6 | _BIT5 | _BIT4);
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        // DDC1 De-bounce Reference Clock(IOSC = 27M) div by 2, latch 1 stages
        MCU_FF2D_DDC1_DDC_CONTROL_1 &= ~(_BIT7);
        MCU_FF2D_DDC1_DDC_CONTROL_1 |= (_BIT6 | _BIT4);
#elif((_D1_INPUT_PORT_TYPE == _D1_DVI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
        // DDC1 De-bounce Reference Clock(IOSC = 27M) div by 4, latch 3 stages
        MCU_FF2D_DDC1_DDC_CONTROL_1 |= (_BIT7 | _BIT6 | _BIT5 | _BIT4);
#endif

#if((_D2_INPUT_PORT_TYPE == _D2_DVI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
        // DDC2 De-bounce Reference Clock(IOSC = 27M) div by 4, latch 3 stages
        MCU_FE65_DDC2_DDC_CONTROL_1 |= (_BIT7 | _BIT6 | _BIT5 | _BIT4);
#endif

#if((_D3_INPUT_PORT_TYPE == _D3_DVI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT))
        // DDC3 De-bounce Reference Clock(IOSC = 27M) div by 4, latch 3 stages
        MCU_FE6E_DDC3_DDC_CONTROL_1 |= (_BIT7 | _BIT6 | _BIT5 | _BIT4);
#endif

#if((_D4_INPUT_PORT_TYPE == _D4_DVI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT))
        // DDC4 De-bounce Reference Clock(IOSC = 27M) div by 4, latch 3 stages
        MCU_FE77_DDC4_DDC_CONTROL_1 |= (_BIT7 | _BIT6 | _BIT5 | _BIT4);
#endif

#if((_D5_INPUT_PORT_TYPE == _D5_DVI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT))
        // DDC5 De-bounce Reference Clock(IOSC = 27M) div by 4, latch 3 stages
        MCU_FE80_DDC5_DDC_CONTROL_1 |= (_BIT7 | _BIT6 | _BIT5 | _BIT4);
#endif
    }
}

//--------------------------------------------------
// Description  : GPIO Initial Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuGpioInitial(void)
{
    // Port_pin_reg_n signal is enabled (P1, P3 GPI->Bus Value)
    MCU_FFED_MCU_CONTROL |= _BIT7;

    // Source selection for P1, P3, P5, P6, P7, P8, P9, PA, PB, PC, PD, PE, PF, read back from bus value
    MCU_FE60_PORT_READ_CONTROL = 0xFF;
    MCU_FE61_PORT_READ_CONTROL_2 = 0xFF;

    PCB_D0_HOTPLUG(_D0_HOT_PLUG_LOW);
    PCB_D1_HOTPLUG(_D1_HOT_PLUG_LOW);
    PCB_D2_HOTPLUG(_D2_HOT_PLUG_HIGH);
    PCB_D3_HOTPLUG(_D3_HOT_PLUG_HIGH);
    PCB_D4_HOTPLUG(_D4_HOT_PLUG_HIGH);
    PCB_D5_HOTPLUG(_D5_HOT_PLUG_HIGH);

    PCB_D2_HDMI_MHL_SWITCH(_TMDS_SWITCH_HDMI_HPD);
    PCB_D3_HDMI_MHL_SWITCH(_TMDS_SWITCH_HDMI_HPD);
    PCB_D4_HDMI_MHL_SWITCH(_TMDS_SWITCH_HDMI_HPD);
    PCB_D5_HDMI_MHL_SWITCH(_TMDS_SWITCH_HDMI_HPD);
    PCB_D2_MHL_VBUS_SWITCH(_MHL_VBUS_OFF);
    PCB_D3_MHL_VBUS_SWITCH(_MHL_VBUS_OFF);
    PCB_D4_MHL_VBUS_SWITCH(_MHL_VBUS_OFF);
    PCB_D5_MHL_VBUS_SWITCH(_MHL_VBUS_OFF);

    PCB_A0_EDID_EEPROM_WRITE_PROTECT(_EDID_EEPROM_WP_ENABLE);
    PCB_D2_EDID_EEPROM_WRITE_PROTECT(_EDID_EEPROM_WP_ENABLE);
    PCB_D3_EDID_EEPROM_WRITE_PROTECT(_EDID_EEPROM_WP_ENABLE);
    PCB_D4_EDID_EEPROM_WRITE_PROTECT(_EDID_EEPROM_WP_ENABLE);
    PCB_D5_EDID_EEPROM_WRITE_PROTECT(_EDID_EEPROM_WP_ENABLE);

    PCB_FLASH_WRITE_PROTECT(_FLASH_WRITE_PROTECT_ENABLE);
    PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_ENABLE);

    PCB_VCCK_OFF_POWER(_VCCK_OFF_POWER_ON);

    // Wait for VCCK_OFF Power On Stable
    POLLING_VCCK_OFF_STATUS(_VCCK_OFF_TIME_POLLING_POWER_ON);

    PCB_DDR_POWER(_DDR_POWER_ON);

    PCB_PANEL_POWER(_PANEL_CONTROL_OFF);
    PCB_BACKLIGHT_POWER_PIN(_LIGHT_CONTROL_OFF);
    PCB_LED_AC_ON_INITIAL();

    PCB_GPIO_ON_REGION_INITIAL_SETTING();
}

//--------------------------------------------------
// Description  : DDC Initial Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcInitial(void)
{
    // DDCRAM partition
    MCU_FFE9_MCU_CLK_CONTROL_1 &= ~(_BIT6 | _BIT5);

    MCU_FEB1_DDCRAM_ST_ADDRESS &= ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0);

    // Disable DDC Segment for VGA_DDC
    MCU_FF1D_ADC_DDC_CONTROL_2 &= ~_BIT2;

    // Disable DDC Segment for DDC0
    MCU_FF20_DDC0_DDC_CONTROL_2 &= ~_BIT2;

    // Disable DDC Segment for DDC1
    MCU_FF2E_DDC1_DDC_CONTROL_2 &= ~_BIT2;

    // Disable DDC Segment for DDC2
    MCU_FE66_DDC2_DDC_CONTROL_2 &= ~_BIT2;

    // Disable DDC Segment for DDC3
    MCU_FE6F_DDC3_DDC_CONTROL_2 &= ~_BIT2;

    // Disable DDC Segment for DDC4
    MCU_FE78_DDC4_DDC_CONTROL_2 &= ~_BIT2;

    // Disable DDC Segment for DDC5
    MCU_FE81_DDC5_DDC_CONTROL_2 &= ~_BIT2;

    // Slave address 0xA0 for VGA_DDC
    MCU_FF1B_ADC_DDC_ENABLE &= ~(_BIT7 | _BIT6 | _BIT5);

    // Slave address 0xA0 for DDC0
    MCU_FF1E_DDC0_DDC_ENABLE &= ~(_BIT7 | _BIT6 | _BIT5);

    // Slave address 0xA0 for DDC1
    MCU_FF2C_DDC1_DDC_ENABLE &= ~(_BIT7 | _BIT6 | _BIT5);

    // Slave address 0xA0 for DDC2
    MCU_FE64_DDC2_DDC_ENABLE &= ~(_BIT7 | _BIT6 | _BIT5);

    // Slave address 0xA0 for DDC3
    MCU_FE6D_DDC3_DDC_ENABLE &= ~(_BIT7 | _BIT6 | _BIT5);

    // Slave address 0xA0 for DDC4
    MCU_FE76_DDC4_DDC_ENABLE &= ~(_BIT7 | _BIT6 | _BIT5);

    // Slave address 0xA0 for DDC5
    MCU_FE7F_DDC5_DDC_ENABLE &= ~(_BIT7 | _BIT6 | _BIT5);

    // Force DDC to DDC2 Mode
    MCU_FF1C_ADC_DDC_CONTROL_1 |= _BIT2;
    MCU_FF1F_DDC0_DDC_CONTROL_1 |= _BIT2;
    MCU_FF2D_DDC1_DDC_CONTROL_1 |= _BIT2;
    MCU_FE65_DDC2_DDC_CONTROL_1 |= _BIT2;
    MCU_FE6E_DDC3_DDC_CONTROL_1 |= _BIT2;
    MCU_FE77_DDC4_DDC_CONTROL_1 |= _BIT2;
    MCU_FE80_DDC5_DDC_CONTROL_1 |= _BIT2;

    // VGA_DDC Debounce reference clock from Xtal
    MCU_FF1C_ADC_DDC_CONTROL_1 &= ~_BIT3;

    // DDC0 Debounce reference clock from Xtal
    MCU_FF1F_DDC0_DDC_CONTROL_1 &= ~_BIT3;

    // DDC1 Debounce reference clock from Xtal
    MCU_FF2D_DDC1_DDC_CONTROL_1 &= ~_BIT3;

    // DDC2 Debounce reference clock from Xtal
    MCU_FE65_DDC2_DDC_CONTROL_1 &= ~_BIT3;

    // DDC3 Debounce reference clock from Xtal
    MCU_FE6E_DDC3_DDC_CONTROL_1 &= ~_BIT3;

    // DDC4 Debounce reference clock from Xtal
    MCU_FE77_DDC4_DDC_CONTROL_1 &= ~_BIT3;

    // DDC5 Debounce reference clock from Xtal
    MCU_FE80_DDC5_DDC_CONTROL_1 &= ~_BIT3;

    // DDC Debounce Settings
    ScalerMcuDdcDebounceSel(_EXT_XTAL_CLK);

    // A0 DDC force Nack
    MCU_FFE7_VGA_EDID_IRQ |= _BIT5;

    // D0 DDC force Nack
    MCU_FFE4_DDC0_EDID_IRQ |= _BIT5;

    // D1 DDC force Nack
    MCU_FFE5_DDC1_EDID_IRQ |= _BIT5;

    // D2 DDC force Nack
    MCU_FE69_DDC2_EDID_IRQ |= _BIT5;

    // D3 DDC force Nack
    MCU_FE72_DDC3_EDID_IRQ |= _BIT5;

    // D4 DDC force Nack
    MCU_FE7B_DDC4_EDID_IRQ |= _BIT5;

    // D5 DDC force Nack
    MCU_FE84_DDC5_EDID_IRQ |= _BIT5;

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))

    // Disable DDCRAM0 Start Address Auto Switch for D0/D6 EDID Segment FW Control
    MCU_FFD1_DDCRAM0_CONTROL &= ~_BIT7;
#endif

    /////////////////////////////////////////
    // Release DDC SCL Pin force to Low /////
    /////////////////////////////////////////

    // DDC5
    MCU_FE81_DDC5_DDC_CONTROL_2 &= ~_BIT0;

    // DDC4
    MCU_FE78_DDC4_DDC_CONTROL_2 &= ~_BIT0;

    // DDC3
    MCU_FE6F_DDC3_DDC_CONTROL_2 &= ~_BIT0;

    // DDC2
    MCU_FE66_DDC2_DDC_CONTROL_2 &= ~_BIT0;

    // DDC1
    MCU_FF2E_DDC1_DDC_CONTROL_2 &= ~_BIT0;

    // DDC0
    MCU_FF20_DDC0_DDC_CONTROL_2 &= ~_BIT0;

    // VGA DDC
    MCU_FF1D_ADC_DDC_CONTROL_2 &= ~_BIT0;
}

//--------------------------------------------------
// Description  : Enable DDC Ram
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcRamEnable(void)
{
    // VGA_DDC Debounce Enable, ADC DDC channel enable
    MCU_FF1B_ADC_DDC_ENABLE |= (_BIT1 | _BIT0);

    // DDC0 Debounce Enable, DDC0 channel enable
    MCU_FF1E_DDC0_DDC_ENABLE |= (_BIT1 | _BIT0);

    // DDC1 Debounce Enable, DDC1 channel enable
    MCU_FF2C_DDC1_DDC_ENABLE |= (_BIT1 | _BIT0);

    // DDC2 Debounce Enable, DDC2 channel enable
    MCU_FE64_DDC2_DDC_ENABLE |= (_BIT1 | _BIT0);

    // DDC3 Debounce Enable, DDC3 channel enable
    MCU_FE6D_DDC3_DDC_ENABLE |= (_BIT1 | _BIT0);

    // DDC4 Debounce Enable, DDC4 channel enable
    MCU_FE76_DDC4_DDC_ENABLE |= (_BIT1 | _BIT0);

    // DDC5 Debounce Enable, DDC5 channel enable
    MCU_FE7F_DDC5_DDC_ENABLE |= (_BIT1 | _BIT0);

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
    // Disable DDC5 DDC-CI Channel Switch
    MCU_FE81_DDC5_DDC_CONTROL_2 &= ~_BIT4;
#endif
}

