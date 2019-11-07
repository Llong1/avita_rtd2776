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
// ID Code      : RL6410_Series_McuCommonInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
//--------------------------------------------------
// Cache Controller (Page FD)
//--------------------------------------------------
extern volatile BYTE xdata MCU_FDA0_CACHE_FUNCTION;
extern volatile BYTE xdata MCU_FDA1_CACHE_OPTION;
extern volatile BYTE xdata MCU_FDA2_CACHE_START_ADDRESS_H;
extern volatile BYTE xdata MCU_FDA3_CACHE_START_ADDRESS_M;
extern volatile BYTE xdata MCU_FDA4_CACHE_START_ADDRESS_L;
extern volatile BYTE xdata MCU_FDA5_CACHE_END_ADDRESS_H;
extern volatile BYTE xdata MCU_FDA6_CACHE_END_ADDRESS_M;
extern volatile BYTE xdata MCU_FDA7_CACHE_END_ADDRESS_L;
extern volatile BYTE xdata MCU_FDA8_CACHE_START_ADDRESS_H2;
extern volatile BYTE xdata MCU_FDA9_CACHE_START_ADDRESS_M2;
extern volatile BYTE xdata MCU_FDAA_CACHE_START_ADDRESS_L2;
extern volatile BYTE xdata MCU_FDAB_CACHE_END_ADDRESS_H2;
extern volatile BYTE xdata MCU_FDAC_CACHE_END_ADDRESS_M2;
extern volatile BYTE xdata MCU_FDAD_CACHE_END_ADDRESS_L2;
extern volatile BYTE xdata MCU_FDAE_COMMON_START_ADDRESS_H;
extern volatile BYTE xdata MCU_FDAF_COMMON_START_ADDRESS_L;
extern volatile BYTE xdata MCU_FDB0_COMMON_END_ADDRESS_H;
extern volatile BYTE xdata MCU_FDB1_COMMON_END_ADDRESS_L;
extern volatile BYTE xdata MCU_FDB2_CACHE_ADDRESS_WILD_CARD;
extern volatile BYTE xdata MCU_FDB3_PERFORMANCE_METER_CONTROL;
extern volatile BYTE xdata MCU_FDB4_PERFORMANCE_METER_INTERRUPT;
extern volatile BYTE xdata MCU_FDB5_PERFORMANCE_METER_STATUS;
extern volatile BYTE xdata MCU_FDB6_PERFORMANCE_METER_LAST_ADDRESS_H;
extern volatile BYTE xdata MCU_FDB7_PERFORMANCE_METER_LAST_ADDRESS_M;
extern volatile BYTE xdata MCU_FDB8_PERFORMANCE_METER_LAST_ADDRESS_L;
extern volatile BYTE xdata MCU_FDB9_PERFORMANCE_METER_REF_COUNT_H;
extern volatile BYTE xdata MCU_FDBA_PERFORMANCE_METER_REF_COUNT_M1;
extern volatile BYTE xdata MCU_FDBB_PERFORMANCE_METER_REF_COUNT_M0;
extern volatile BYTE xdata MCU_FDBC_PERFORMANCE_METER_REF_COUNT_L;
extern volatile BYTE xdata MCU_FDBD_PERFORMANCE_METER_MISS_COUNT_H;
extern volatile BYTE xdata MCU_FDBE_PERFORMANCE_METER_MISS_COUNT_M1;
extern volatile BYTE xdata MCU_FDBF_PERFORMANCE_METER_MISS_COUNT_M0;
extern volatile BYTE xdata MCU_FDC0_PERFORMANCE_METER_MISS_COUNT_L;
extern volatile BYTE xdata MCU_FDC1_PERFORMANCE_METER_MEM_RESTART_H;
extern volatile BYTE xdata MCU_FDC2_PERFORMANCE_METER_MEM_RESTART_M1;
extern volatile BYTE xdata MCU_FDC3_PERFORMANCE_METER_MEM_RESTART_M0;
extern volatile BYTE xdata MCU_FDC4_PERFORMANCE_METER_MEM_RESTART_L;
extern volatile BYTE xdata MCU_FDC5_PERFORMANCE_METER_CRC_H;
extern volatile BYTE xdata MCU_FDC6_PERFORMANCE_METER_CRC_L;
extern volatile BYTE xdata MCU_FDC7_CACHE_CONTENT_ADDRESS_H;
extern volatile BYTE xdata MCU_FDC8_CACHE_CONTENT_ADDRESS_L;
extern volatile BYTE xdata MCU_FDC9_CACHE_CONTENT_DATA;
extern volatile BYTE xdata MCU_FDCA_CACHE_SRAM_BIST_CTRL;
extern volatile BYTE xdata MCU_FDCB_CACHE_SRAM_DRF_BIST_CTRL;
extern volatile BYTE xdata MCU_FDCC_CACHE_LOAD_CTRL;


//--------------------------------------------------
// EMCU (Page FE)
//--------------------------------------------------
extern volatile BYTE xdata MCU_FE00_PORT40_PIN_REG;
extern volatile BYTE xdata MCU_FE01_PORT41_PIN_REG;
extern volatile BYTE xdata MCU_FE02_PORT42_PIN_REG;
extern volatile BYTE xdata MCU_FE03_PORT43_PIN_REG;
extern volatile BYTE xdata MCU_FE04_PORT44_PIN_REG;
extern volatile BYTE xdata MCU_FE05_PORT45_PIN_REG;
extern volatile BYTE xdata MCU_FE06_PORT46_PIN_REG;
extern volatile BYTE xdata MCU_FE07_PORT47_PIN_REG;
extern volatile BYTE xdata MCU_FE08_PORT50_PIN_REG;
extern volatile BYTE xdata MCU_FE09_PORT51_PIN_REG;
extern volatile BYTE xdata MCU_FE0A_PORT52_PIN_REG;
extern volatile BYTE xdata MCU_FE0B_PORT53_PIN_REG;
extern volatile BYTE xdata MCU_FE0C_PORT54_PIN_REG;
extern volatile BYTE xdata MCU_FE0D_PORT55_PIN_REG;
extern volatile BYTE xdata MCU_FE0E_PORT56_PIN_REG;
extern volatile BYTE xdata MCU_FE0F_PORT57_PIN_REG;
extern volatile BYTE xdata MCU_FE10_PORT60_PIN_REG;
extern volatile BYTE xdata MCU_FE11_PORT61_PIN_REG;
extern volatile BYTE xdata MCU_FE12_PORT62_PIN_REG;
extern volatile BYTE xdata MCU_FE13_PORT63_PIN_REG;
extern volatile BYTE xdata MCU_FE14_PORT64_PIN_REG;
extern volatile BYTE xdata MCU_FE15_PORT65_PIN_REG;
extern volatile BYTE xdata MCU_FE16_PORT66_PIN_REG;
extern volatile BYTE xdata MCU_FE17_PORT67_PIN_REG;
extern volatile BYTE xdata MCU_FE18_PORT70_PIN_REG;
extern volatile BYTE xdata MCU_FE19_PORT71_PIN_REG;
extern volatile BYTE xdata MCU_FE1A_PORT72_PIN_REG;
extern volatile BYTE xdata MCU_FE1B_PORT73_PIN_REG;
extern volatile BYTE xdata MCU_FE1C_PORT74_PIN_REG;
extern volatile BYTE xdata MCU_FE1D_PORT75_PIN_REG;
extern volatile BYTE xdata MCU_FE1E_PORT76_PIN_REG;
extern volatile BYTE xdata MCU_FE1F_PORT77_PIN_REG;
extern volatile BYTE xdata MCU_FE20_PORT80_PIN_REG;
extern volatile BYTE xdata MCU_FE21_PORT81_PIN_REG;
extern volatile BYTE xdata MCU_FE22_PORT82_PIN_REG;
extern volatile BYTE xdata MCU_FE23_PORT83_PIN_REG;
extern volatile BYTE xdata MCU_FE24_PORT84_PIN_REG;
extern volatile BYTE xdata MCU_FE25_PORT85_PIN_REG;
extern volatile BYTE xdata MCU_FE26_PORT86_PIN_REG;
extern volatile BYTE xdata MCU_FE27_PORT87_PIN_REG;
extern volatile BYTE xdata MCU_FE28_PORT90_PIN_REG;
extern volatile BYTE xdata MCU_FE29_PORT91_PIN_REG;
extern volatile BYTE xdata MCU_FE2A_PORT92_PIN_REG;
extern volatile BYTE xdata MCU_FE2B_PORT93_PIN_REG;
extern volatile BYTE xdata MCU_FE2C_PORT94_PIN_REG;
extern volatile BYTE xdata MCU_FE2D_PORT95_PIN_REG;
extern volatile BYTE xdata MCU_FE2E_PORT96_PIN_REG;
extern volatile BYTE xdata MCU_FE2F_PORT97_PIN_REG;
extern volatile BYTE xdata MCU_FE30_PORTA0_PIN_REG;
extern volatile BYTE xdata MCU_FE31_PORTA1_PIN_REG;
extern volatile BYTE xdata MCU_FE32_PORTA2_PIN_REG;
extern volatile BYTE xdata MCU_FE33_PORTA3_PIN_REG;
extern volatile BYTE xdata MCU_FE34_PORTA4_PIN_REG;
extern volatile BYTE xdata MCU_FE35_PORTA5_PIN_REG;
extern volatile BYTE xdata MCU_FE36_PORTA6_PIN_REG;
extern volatile BYTE xdata MCU_FE37_PORTA7_PIN_REG;
extern volatile BYTE xdata MCU_FE38_PORTB0_PIN_REG;
extern volatile BYTE xdata MCU_FE39_PORTB1_PIN_REG;
extern volatile BYTE xdata MCU_FE3A_PORTB2_PIN_REG;
extern volatile BYTE xdata MCU_FE3B_PORTB3_PIN_REG;
extern volatile BYTE xdata MCU_FE3C_PORTB4_PIN_REG;
extern volatile BYTE xdata MCU_FE3D_PORTB5_PIN_REG;
extern volatile BYTE xdata MCU_FE3E_PORTB6_PIN_REG;
extern volatile BYTE xdata MCU_FE3F_PORTB7_PIN_REG;
extern volatile BYTE xdata MCU_FE40_PORTC0_PIN_REG;
extern volatile BYTE xdata MCU_FE41_PORTC1_PIN_REG;
extern volatile BYTE xdata MCU_FE42_PORTC2_PIN_REG;
extern volatile BYTE xdata MCU_FE43_PORTC3_PIN_REG;
extern volatile BYTE xdata MCU_FE44_PORTC4_PIN_REG;
extern volatile BYTE xdata MCU_FE45_PORTC5_PIN_REG;
extern volatile BYTE xdata MCU_FE46_PORTC6_PIN_REG;
extern volatile BYTE xdata MCU_FE47_PORTC7_PIN_REG;
extern volatile BYTE xdata MCU_FE48_PORTD0_PIN_REG;
extern volatile BYTE xdata MCU_FE49_PORTD1_PIN_REG;
extern volatile BYTE xdata MCU_FE4A_PORTD2_PIN_REG;
extern volatile BYTE xdata MCU_FE4B_PORTD3_PIN_REG;
extern volatile BYTE xdata MCU_FE4C_PORTD4_PIN_REG;
extern volatile BYTE xdata MCU_FE4D_PORTD5_PIN_REG;
extern volatile BYTE xdata MCU_FE4E_PORTD6_PIN_REG;
extern volatile BYTE xdata MCU_FE4F_PORTD7_PIN_REG;
extern volatile BYTE xdata MCU_FE50_PORTE0_PIN_REG;
extern volatile BYTE xdata MCU_FE51_PORTE1_PIN_REG;
extern volatile BYTE xdata MCU_FE52_PORTE2_PIN_REG;
extern volatile BYTE xdata MCU_FE53_PORTE3_PIN_REG;
extern volatile BYTE xdata MCU_FE54_PORTE4_PIN_REG;
extern volatile BYTE xdata MCU_FE55_PORTE5_PIN_REG;
extern volatile BYTE xdata MCU_FE56_PORTE6_PIN_REG;
extern volatile BYTE xdata MCU_FE57_PORTE7_PIN_REG;
extern volatile BYTE xdata MCU_FE58_PORTF0_PIN_REG;
extern volatile BYTE xdata MCU_FE59_PORTF1_PIN_REG;
extern volatile BYTE xdata MCU_FE5A_PORTF2_PIN_REG;
extern volatile BYTE xdata MCU_FE5B_PORTF3_PIN_REG;
extern volatile BYTE xdata MCU_FE5C_PORTF4_PIN_REG;
extern volatile BYTE xdata MCU_FE60_PORT_READ_CONTROL;
extern volatile BYTE xdata MCU_FE61_PORT_READ_CONTROL_2;
extern volatile BYTE xdata MCU_FE62_DDC2_SEGMENT_ADDRESS;
extern volatile BYTE xdata MCU_FE63_DDC2_SEGMENT_DATA;
extern volatile BYTE xdata MCU_FE64_DDC2_DDC_ENABLE;
extern volatile BYTE xdata MCU_FE65_DDC2_DDC_CONTROL_1;
extern volatile BYTE xdata MCU_FE66_DDC2_DDC_CONTROL_2;
extern volatile BYTE xdata MCU_FE67_DDC2_DDC_INDEX;
extern volatile BYTE xdata MCU_FE68_DDC2_DDC_ACCESS_PORT;
extern volatile BYTE xdata MCU_FE69_DDC2_EDID_IRQ;
extern volatile BYTE xdata MCU_FE6A_DDC2_RESERVED;
extern volatile BYTE xdata MCU_FE6B_DDC3_SEGMENT_ADDRESS;
extern volatile BYTE xdata MCU_FE6C_DDC3_SEGMENT_DATA;
extern volatile BYTE xdata MCU_FE6D_DDC3_DDC_ENABLE;
extern volatile BYTE xdata MCU_FE6E_DDC3_DDC_CONTROL_1;
extern volatile BYTE xdata MCU_FE6F_DDC3_DDC_CONTROL_2;
extern volatile BYTE xdata MCU_FE70_DDC3_DDC_INDEX;
extern volatile BYTE xdata MCU_FE71_DDC3_DDC_ACCESS_PORT;
extern volatile BYTE xdata MCU_FE72_DDC3_EDID_IRQ;
extern volatile BYTE xdata MCU_FE73_DDC3_RESERVED;
extern volatile BYTE xdata MCU_FE74_DDC4_SEGMENT_ADDRESS;
extern volatile BYTE xdata MCU_FE75_DDC4_SEGMENT_DATA;
extern volatile BYTE xdata MCU_FE76_DDC4_DDC_ENABLE;
extern volatile BYTE xdata MCU_FE77_DDC4_DDC_CONTROL_1;
extern volatile BYTE xdata MCU_FE78_DDC4_DDC_CONTROL_2;
extern volatile BYTE xdata MCU_FE79_DDC4_DDC_INDEX;
extern volatile BYTE xdata MCU_FE7A_DDC4_DDC_ACCESS_PORT;
extern volatile BYTE xdata MCU_FE7B_DDC4_EDID_IRQ;
extern volatile BYTE xdata MCU_FE7C_DDC4_RESERVED;
extern volatile BYTE xdata MCU_FE7D_DDC5_SEGMENT_ADDRESS;
extern volatile BYTE xdata MCU_FE7E_DDC5_SEGMENT_DATA;
extern volatile BYTE xdata MCU_FE7F_DDC5_DDC_ENABLE;
extern volatile BYTE xdata MCU_FE80_DDC5_DDC_CONTROL_1;
extern volatile BYTE xdata MCU_FE81_DDC5_DDC_CONTROL_2;
extern volatile BYTE xdata MCU_FE82_DDC5_DDC_INDEX;
extern volatile BYTE xdata MCU_FE83_DDC5_DDC_ACCESS_PORT;
extern volatile BYTE xdata MCU_FE84_DDC5_EDID_IRQ;
extern volatile BYTE xdata MCU_FE85_DDC5_RESERVED;
extern volatile BYTE xdata MCU_FE86_IIC_1_CH_SEL;
extern volatile BYTE xdata MCU_FE87_IIC_1_SET_SLAVE;
extern volatile BYTE xdata MCU_FE88_IIC_1_SUB_IN;
extern volatile BYTE xdata MCU_FE89_IIC_1_DATA_IN;
extern volatile BYTE xdata MCU_FE8A_IIC_1_DATA_OUT;
extern volatile BYTE xdata MCU_FE8B_IIC_1_STATUS;
extern volatile BYTE xdata MCU_FE8C_IIC_1_IRQ_CONTROL;
extern volatile BYTE xdata MCU_FE8D_IIC_1_STATUS2;
extern volatile BYTE xdata MCU_FE8E_IIC_1_IRQ_CONTROL2;
extern volatile BYTE xdata MCU_FE8F_IIC_1_CHANNEL_CONTROL;
extern volatile BYTE xdata MCU_FE90_DDCCI_1_NULL_BYTE1;
extern volatile BYTE xdata MCU_FE91_DDCCI_1_NULL_BYTE2;
extern volatile BYTE xdata MCU_FE92_DDCCI_1_NULL_BYTE3;
extern volatile BYTE xdata MCU_FE93_DDCCI_1_REMAIN_DATA;
extern volatile BYTE xdata MCU_FE94_IIC_2_CH_SEL;
extern volatile BYTE xdata MCU_FE95_IIC_2_SET_SLAVE;
extern volatile BYTE xdata MCU_FE96_IIC_2_SUB_IN;
extern volatile BYTE xdata MCU_FE97_IIC_2_DATA_IN;
extern volatile BYTE xdata MCU_FE98_IIC_2_DATA_OUT;
extern volatile BYTE xdata MCU_FE99_IIC_2_STATUS;
extern volatile BYTE xdata MCU_FE9A_IIC_2_IRQ_CONTROL;
extern volatile BYTE xdata MCU_FE9B_IIC_2_STATUS2;
extern volatile BYTE xdata MCU_FE9C_IIC_2_IRQ_CONTROL2;
extern volatile BYTE xdata MCU_FE9D_IIC_2_CHANNEL_CONTROL;
extern volatile BYTE xdata MCU_FE9E_DDCCI_2_NULL_BYTE1;
extern volatile BYTE xdata MCU_FEA0_DDCCI_2_NULL_BYTE2;
extern volatile BYTE xdata MCU_FEA1_DDCCI_2_NULL_BYTE3;
extern volatile BYTE xdata MCU_FEA2_DDCCI_2_REMAIN_DATA;
extern volatile BYTE xdata MCU_FEA3_IIC_3_CH_SEL;
extern volatile BYTE xdata MCU_FEA4_IIC_3_SET_SLAVE;
extern volatile BYTE xdata MCU_FEA5_IIC_3_SUB_IN;
extern volatile BYTE xdata MCU_FEA6_IIC_3_DATA_IN;
extern volatile BYTE xdata MCU_FEA7_IIC_3_DATA_OUT;
extern volatile BYTE xdata MCU_FEA8_IIC_3_STATUS;
extern volatile BYTE xdata MCU_FEA9_IIC_3_IRQ_CONTROL;
extern volatile BYTE xdata MCU_FEAA_IIC_3_STATUS2;
extern volatile BYTE xdata MCU_FEAB_IIC_3_IRQ_CONTROL2;
extern volatile BYTE xdata MCU_FEAC_IIC_3_CHANNEL_CONTROL;
extern volatile BYTE xdata MCU_FEAD_DDCCI_3_NULL_BYTE1;
extern volatile BYTE xdata MCU_FEAE_DDCCI_3_NULL_BYTE2;
extern volatile BYTE xdata MCU_FEAF_DDCCI_3_NULL_BYTE3;
extern volatile BYTE xdata MCU_FEB0_DDCCI_3_REMAIN_DATA;
extern volatile BYTE xdata MCU_FEB1_DDCRAM_ST_ADDRESS;
extern volatile BYTE xdata MCU_FEB2_XRAM_BIST_CTRL;
extern volatile BYTE xdata MCU_FEB3_XRAM_DRF_BIST_CTRL;
extern volatile BYTE xdata MCU_FEB4_MCU_DUMMY2;


//--------------------------------------------------
// EMCU (Page FF)
//--------------------------------------------------
extern volatile BYTE xdata MCU_FF00_IRQ_STATUS;
extern volatile BYTE xdata MCU_FF03_TRIPLE_BYTES_OPERATION;
extern volatile BYTE xdata MCU_FF04_SHIFT_BITS_NUMBER;
extern volatile BYTE xdata MCU_FF05_SHIFT_BYTE_ADDRESS;
extern volatile BYTE xdata MCU_FF06_INPUT_TRIPLE_BYTES;
extern volatile BYTE xdata MCU_FF07_RESULT_TRIPLE_BYTES;
extern volatile BYTE xdata MCU_FF08_ADC_ACONTROL;
extern volatile BYTE xdata MCU_FF09_ADC_A0_CONVERT_RESULT;
extern volatile BYTE xdata MCU_FF0A_ADC_A1_CONVERT_RESULT;
extern volatile BYTE xdata MCU_FF0B_ADC_A2_CONVERT_RESULT;
extern volatile BYTE xdata MCU_FF0C_ADC_A3_CONVERT_RESULT;
extern volatile BYTE xdata MCU_FF0D_ADC_CLK_DIV;
extern volatile BYTE xdata MCU_FF0E_AUTO_MODE_CTRL01;
extern volatile BYTE xdata MCU_FF0F_ADC0_THRESHOLD_H;
extern volatile BYTE xdata MCU_FF10_ADC0_THRESHOLD_L;
extern volatile BYTE xdata MCU_FF11_ADC1_THRESHOLD_H;
extern volatile BYTE xdata MCU_FF12_ADC1_THRESHOLD_L;
extern volatile BYTE xdata MCU_FF13_ADC2_THRESHOLD_H;
extern volatile BYTE xdata MCU_FF14_ADC2_THRESHOLD_L;
extern volatile BYTE xdata MCU_FF15_ADC3_THRESHOLD_H;
extern volatile BYTE xdata MCU_FF16_ADC3_THRESHOLD_L;
extern volatile BYTE xdata MCU_FF17_CTRL0_WAIT_TIME_VALUE;
extern volatile BYTE xdata MCU_FF18_BYTE_ADDRESS;
extern volatile BYTE xdata MCU_FF19_ADC_SEGMENT_ADDRESS;
extern volatile BYTE xdata MCU_FF1A_ADC_SEGMENT_DATA;
extern volatile BYTE xdata MCU_FF1B_ADC_DDC_ENABLE;
extern volatile BYTE xdata MCU_FF1C_ADC_DDC_CONTROL_1;
extern volatile BYTE xdata MCU_FF1D_ADC_DDC_CONTROL_2;
extern volatile BYTE xdata MCU_FF1E_DDC0_DDC_ENABLE;
extern volatile BYTE xdata MCU_FF1F_DDC0_DDC_CONTROL_1;
extern volatile BYTE xdata MCU_FF20_DDC0_DDC_CONTROL_2;
extern volatile BYTE xdata MCU_FF22_IIC_CH_SEL;
extern volatile BYTE xdata MCU_FF23_IIC_SET_SLAVE;
extern volatile BYTE xdata MCU_FF24_IIC_SUB_IN;
extern volatile BYTE xdata MCU_FF25_IIC_DATA_IN;
extern volatile BYTE xdata MCU_FF26_IIC_DATA_OUT;
extern volatile BYTE xdata MCU_FF27_IIC_STATUS;
extern volatile BYTE xdata MCU_FF28_IIC_IRQ_CONTROL;
extern volatile BYTE xdata MCU_FF29_IIC_STATUS2;
extern volatile BYTE xdata MCU_FF2A_IIC_IRQ_CONTROL2;
extern volatile BYTE xdata MCU_FF2B_IIC_CHANNEL_CONTROL;
extern volatile BYTE xdata MCU_FF2C_DDC1_DDC_ENABLE;
extern volatile BYTE xdata MCU_FF2D_DDC1_DDC_CONTROL_1;
extern volatile BYTE xdata MCU_FF2E_DDC1_DDC_CONTROL_2;
extern volatile BYTE xdata MCU_FF2F_ADC_DDC_INDEX;
extern volatile BYTE xdata MCU_FF30_ADC_DDC_ACCESS_PORT;
extern volatile BYTE xdata MCU_FF31_DDC0_DDC_INDEX;
extern volatile BYTE xdata MCU_FF32_DDC0_DDC_ACCESS_PORT;
extern volatile BYTE xdata MCU_FF33_DDC1_DDC_INDEX;
extern volatile BYTE xdata MCU_FF34_DDC1_DDC_ACCESS_PORT;
extern volatile BYTE xdata MCU_FF35_DDCCI_REMAIN_DATA;
extern volatile BYTE xdata MCU_FF36_DDC0_SEGMENT_ADDRESS;
extern volatile BYTE xdata MCU_FF37_DDC0_SEGMENT_DATA;
extern volatile BYTE xdata MCU_FF38_DDC1_SEGMENT_ADDRESS;
extern volatile BYTE xdata MCU_FF39_DDC1_SEGMENT_DATA;
extern volatile BYTE xdata MCU_FF3A_PWM_CK_SEL;
extern volatile BYTE xdata MCU_FF3B_PWM03_M;
extern volatile BYTE xdata MCU_FF3C_PWM45_M;
extern volatile BYTE xdata MCU_FF3D_PWM01_N_MSB;
extern volatile BYTE xdata MCU_FF3E_PWM0_N_LSB;
extern volatile BYTE xdata MCU_FF3F_PWM1_N_LSB;
extern volatile BYTE xdata MCU_FF40_PWM23_N_MSB;
extern volatile BYTE xdata MCU_FF41_PWM2_N_LSB;
extern volatile BYTE xdata MCU_FF42_PWM3_N_LSB;
extern volatile BYTE xdata MCU_FF43_PWM45_N_MSB;
extern volatile BYTE xdata MCU_FF44_PWM4_N_LSB;
extern volatile BYTE xdata MCU_FF45_PWM5_N_LSB;
extern volatile BYTE xdata MCU_FF46_PWML;
extern volatile BYTE xdata MCU_FF47_PWM_VS_CTRL;
extern volatile BYTE xdata MCU_FF48_PWM_EN;
extern volatile BYTE xdata MCU_FF49_PWM_CK;
extern volatile BYTE xdata MCU_FF4A_PWM0H_DUT;
extern volatile BYTE xdata MCU_FF4B_PWM1H_DUT;
extern volatile BYTE xdata MCU_FF4C_PWM01L_DUT;
extern volatile BYTE xdata MCU_FF4D_PWM2H_DUT;
extern volatile BYTE xdata MCU_FF4E_PWM3H_DUT;
extern volatile BYTE xdata MCU_FF4F_PWM23L_DUT;
extern volatile BYTE xdata MCU_FF50_PWM4H_DUT;
extern volatile BYTE xdata MCU_FF51_PWM5H_DUT;
extern volatile BYTE xdata MCU_FF52_PWM45L_DUT;
extern volatile BYTE xdata MCU_FF53_PWM_DUT_TYPE;
extern volatile BYTE xdata MCU_FF54_PWM_CNT_MODE;
extern volatile BYTE xdata MCU_FF55_I2CM_CR0;
extern volatile BYTE xdata MCU_FF56_I2CM_CR1;
extern volatile BYTE xdata MCU_FF57_I2CM_CR2;
extern volatile BYTE xdata MCU_FF58_I2CM_CR3;
extern volatile BYTE xdata MCU_FF59_I2CM_STR0;
extern volatile BYTE xdata MCU_FF5A_I2CM_STR1;
extern volatile BYTE xdata MCU_FF5B_I2CM_STR2;
extern volatile BYTE xdata MCU_FF5C_I2CM_STR3;
extern volatile BYTE xdata MCU_FF5D_I2CM_SR;
extern volatile BYTE xdata MCU_FF5E_I2CM_TD;
extern volatile BYTE xdata MCU_FF5F_I2CM_CCR;
extern volatile BYTE xdata MCU_FF60_COMMON_INST_EN;
extern volatile BYTE xdata MCU_FF61_COMMON_OP_CODE;
extern volatile BYTE xdata MCU_FF62_WREN_OP_CODE;
extern volatile BYTE xdata MCU_FF63_EWSR_OP_CODE;
extern volatile BYTE xdata MCU_FF64_FLASH_PROG_ISP0;
extern volatile BYTE xdata MCU_FF65_FLASH_PROG_ISP1;
extern volatile BYTE xdata MCU_FF66_FLASH_PROG_ISP2;
extern volatile BYTE xdata MCU_FF67_COMMON_INST_READ_PORT0;
extern volatile BYTE xdata MCU_FF68_COMMON_INST_READ_PORT1;
extern volatile BYTE xdata MCU_FF69_COMMON_INST_READ_PORT2;
extern volatile BYTE xdata MCU_FF6A_READ_OP_CODE;
extern volatile BYTE xdata MCU_FF6B_FAST_READ_OP_CODE;
extern volatile BYTE xdata MCU_FF6C_READ_INSTRUCTION;
extern volatile BYTE xdata MCU_FF6D_PROGRAM_OP_CODE;
extern volatile BYTE xdata MCU_FF6E_READ_STATUS_REGISTER_OP_CODE;
extern volatile BYTE xdata MCU_FF6F_PROGRAM_INSTRUCTION;
extern volatile BYTE xdata MCU_FF70_PROGRAM_DATA_PORT;
extern volatile BYTE xdata MCU_FF71_PROGRAM_LENGTH;
extern volatile BYTE xdata MCU_FF72_CRC_END_ADDR0;
extern volatile BYTE xdata MCU_FF73_CRC_END_ADDR1;
extern volatile BYTE xdata MCU_FF74_CRC_END_ADDR2;
extern volatile BYTE xdata MCU_FF75_CRC_RESULT;
extern volatile BYTE xdata MCU_FF76_CEN_CTRL;
extern volatile BYTE xdata MCU_FF77_REV_DUMMY4;
extern volatile BYTE xdata MCU_FF78_ACCESS_FLASH_ADDR_0;
extern volatile BYTE xdata MCU_FF79_ACCESS_FLASH_ADDR_1;
extern volatile BYTE xdata MCU_FF7A_ACCESS_FLASH_ADDR_2;
extern volatile BYTE xdata MCU_FF7B_ACCESS_FLASH_DATA_PORT;
extern volatile BYTE xdata MCU_FF7C_ACCESS_FLASH_DATA_CTRL;
extern volatile BYTE xdata MCU_FF80_AAI_MODE_BYTE_NUM;
extern volatile BYTE xdata MCU_FF81_ISP_CMD_INSERT;
extern volatile BYTE xdata MCU_FF82_ISP_CMD_LENGTH;
extern volatile BYTE xdata MCU_FF83_I2CS_CTRL0;
extern volatile BYTE xdata MCU_FF84_I2CS_CTRL1;
extern volatile BYTE xdata MCU_FF85_I2CS_CTRL2;
extern volatile BYTE xdata MCU_FF86_I2CS_STATUS0;
extern volatile BYTE xdata MCU_FF87_I2CS_STATUS1;
extern volatile BYTE xdata MCU_FF88_I2CS_BUFLEN;
extern volatile BYTE xdata MCU_FF90_PWM01_TOTALCNT_MSB;
extern volatile BYTE xdata MCU_FF91_PWM0_TOTALCNT_LSB;
extern volatile BYTE xdata MCU_FF92_PWM1_TOTALCNT_LSB;
extern volatile BYTE xdata MCU_FF93_PWM23_TOTALCNT_MSB;
extern volatile BYTE xdata MCU_FF94_PWM2_TOTALCNT_LSB;
extern volatile BYTE xdata MCU_FF95_PWM3_TOTALCNT_LSB;
extern volatile BYTE xdata MCU_FF96_PWM45_TOTALCNT_MSB;
extern volatile BYTE xdata MCU_FF97_PWM4_TOTALCNT_LSB;
extern volatile BYTE xdata MCU_FF98_PWM5_TOTALCNT_LSB;
extern volatile BYTE xdata MCU_FF99_PWM_CK_SEL_HS;
extern volatile BYTE xdata MCU_FF9A_PWM01_CYCLE_MAX;
extern volatile BYTE xdata MCU_FF9B_PWM23_CYCLE_MAX;
extern volatile BYTE xdata MCU_FF9C_PWM45_CYCLE_MAX;
extern volatile BYTE xdata MCU_FF9D_SPI_CAL_CTRL;
extern volatile BYTE xdata MCU_FF9E_SPI_CAL_RESULT;
extern volatile BYTE xdata MCU_FF9F_SPI_CAL_DATA_00;
extern volatile BYTE xdata MCU_FFA5_SPI_CAL_DATA_01;
extern volatile BYTE xdata MCU_FFA6_SPI_CAL_DATA_02;
extern volatile BYTE xdata MCU_FFA7_SPI_CAL_ADR_H;
extern volatile BYTE xdata MCU_FFA8_SPI_CAL_ADR_M;
extern volatile BYTE xdata MCU_FFA9_SPI_CAL_ADR_L;
extern volatile BYTE xdata MCU_FFAA_WATCHDOG_CNT2_VALUE;
extern volatile BYTE xdata MCU_FFAB_WATCHDOG_CNT23_VALUE;
extern volatile BYTE xdata MCU_FFAC_WATCHDOG_CNT3_VALUE;
extern volatile BYTE xdata MCU_FFAD_WATCHDOG_CNT1_VALUE;
extern volatile BYTE xdata MCU_FFAE_WATCHDOG_TIMER_THRESHOLD;
extern volatile BYTE xdata MCU_FFAF_WATCHDOG_TIMER_THRESHOLD_MASK;
extern volatile BYTE xdata MCU_FFB0_WATCHDOG_TIMER_H_THRESHOLD_MASK;
extern volatile BYTE xdata MCU_FFB1_DDCCI_NULL_BYTE1;
extern volatile BYTE xdata MCU_FFB2_DDCCI_NULL_BYTE2;
extern volatile BYTE xdata MCU_FFB3_DDCCI_NULL_BYTE3;
extern volatile BYTE xdata MCU_FFB8_EXT_INT0_CONTROL;
extern volatile BYTE xdata MCU_FFB9_EXT_INT1_CONTROL;
extern volatile BYTE xdata MCU_FFBB_PERI_TEST;
extern volatile BYTE xdata MCU_FFBC_CYCLE_GATING;
extern volatile BYTE xdata MCU_FFBD_MCU_CLK_DIV_R;
extern volatile BYTE xdata MCU_FFBE_MCU_DUMMY;
extern volatile BYTE xdata MCU_FFC2_IRQ_PRIORITY_1;
extern volatile BYTE xdata MCU_FFC3_IRQ_PRIORITY_2;
extern volatile BYTE xdata MCU_FFC4_IRQ_PRIORITY_3;


//--------------------------------------------------
// EMCU DDCRAM Control (Page FF)
//--------------------------------------------------
extern volatile BYTE xdata MCU_FFD0_A_DDCRAM_CONTROL;
extern volatile BYTE xdata MCU_FFD1_DDCRAM0_CONTROL;
extern volatile BYTE xdata MCU_FFD2_DDCRAM1_CONTROL;
extern volatile BYTE xdata MCU_FFD3_DDCRAM2_CONTROL;
extern volatile BYTE xdata MCU_FFD4_DDCRAM3_CONTROL;
extern volatile BYTE xdata MCU_FFD5_DDCRAM4_CONTROL;
extern volatile BYTE xdata MCU_FFD6_DDCRAM5_CONTROL;


//--------------------------------------------------
// EMCU In System Programming Part 1 (Page FF)
//--------------------------------------------------
extern volatile BYTE xdata MCU_FFE0_ISP_FLAG;
extern volatile BYTE xdata MCU_FFE2_PORT1_PIN_REG;
extern volatile BYTE xdata MCU_FFE3_PORT3_PIN_REG;
extern volatile BYTE xdata MCU_FFE4_DDC0_EDID_IRQ;
extern volatile BYTE xdata MCU_FFE5_DDC1_EDID_IRQ;
extern volatile BYTE xdata MCU_FFE7_VGA_EDID_IRQ;
extern volatile BYTE xdata MCU_FFE8_ISP_CONTROL;
extern volatile BYTE xdata MCU_FFE9_MCU_CLK_CONTROL_1;
extern volatile BYTE xdata MCU_FFEA_WATCHDOG_TIMER;
extern volatile BYTE xdata MCU_FFEB_WDT_TEST;
extern volatile BYTE xdata MCU_FFEC_ISP_SLAVE_ADDRESS;
extern volatile BYTE xdata MCU_FFED_MCU_CONTROL;
extern volatile BYTE xdata MCU_FFEE_MCU_CLOCK_CONTROL;
extern volatile BYTE xdata MCU_FFEF_RAM_TEST;
extern volatile BYTE xdata MCU_FFF0_XDATA_SPI_FLASH_WRITE_PROTECT;
extern volatile BYTE xdata MCU_FFF1_SCA_WR_INTRVL;
extern volatile BYTE xdata MCU_FFF2_PWM_I2C_CLOCK_STOP;
extern volatile BYTE xdata MCU_FFF3_SCA_INF_CONTROL;
extern volatile BYTE xdata MCU_FFF4_SCA_INF_ADDR;
extern volatile BYTE xdata MCU_FFF5_SCA_INF_DATA;
extern volatile BYTE xdata MCU_FFF6_SCA_INF_BWR_ADRH;
extern volatile BYTE xdata MCU_FFF7_SCA_INF_BWR_ADRM;
extern volatile BYTE xdata MCU_FFF8_SCA_INF_BWR_ADRL;
extern volatile BYTE xdata MCU_FFF9_SCA_INF_BWR_COUNT_H;
extern volatile BYTE xdata MCU_FFFA_SCA_INF_BWR_COUNT_L;
extern volatile BYTE xdata MCU_FFFB_SCA_INF_PERIOD;
extern volatile BYTE xdata MCU_FFFC_BANK_SWICH_CONTROL;
extern volatile BYTE xdata MCU_FFFD_XDATA_BANK_START;
extern volatile BYTE xdata MCU_FFFE_XDATA_BANK_SEL;
extern volatile BYTE xdata MCU_FFFF_PBANK_SWITCH;

