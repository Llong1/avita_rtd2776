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
// ID Code      : Pcb_List.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __PCB_LIST_H__
#define __PCB_LIST_H__

//--------------------------------------------------
// Pcb List
//--------------------------------------------------
#define _RL6193_PCB_EXAMPLE                                 0x00
#define _RL6193_QA_A_1A1H4MHL1DP1mDP_DPTX_LVDS_VB1          0x01
#define _RL6193_QA_B_1A1H4MHL1DP_DPTX_LVDS_eDP              0x02
#define _RL6193_DEMO_A_1A1H4MHL1DP_DPTX_LVDS_eDP            0x03
#define _RL6193_DEMO_B_1A2MHL1DP1mDP1DUALDVI_DPTX_LVDS_eDP  0x04
#define _RL6193_DEMO_C_1A3MHL1DP_DPTX_LVDS_VB1              0x05
#define _RL6193_DEMO_D_1A1H4MHL1DP_DPTX_LVDS_VB1            0x06
#define _RL6193_DEMO_E_1H4MHL1DP1mDP_DPTX_LVDS_VB1          0x07

#define _RL6410_PCB_EXAMPLE                                 0x20
#define _RL6410_QA_A_1A4MHL1DP1mDP_DPTX_LVDS_eDP            0x21
#define _RL6410_QA_B_1A6mDP_DPTX_LVDS_eDP                   0x22
#define _RL6410_DEMO_A_1A4MHL2DP_DPTX_LVDS_eDP              0x23
#define _RL6410_DEMO_B_1A4MHL1DP1mDP_DPTX_LVDS_eDP          0x24
#define _RL6410_DEMO_C_1A2MHL1DP1mDP1DUALDVI_DPTX_LVDS_eDP  0x25
#define _RL6410_DEMO_D_1A4MHL1DP1mDP_DPTX_LVDS_VB1          0x26
#define _RL6410_DEMO_E_1A4MHL2DP_DPTX_LVDS_VB1              0x27
#define _RL6410_DEMO_TC_3MHL1DP1TYPEC_DPTX_LVDS_eDP         0x28
#define _RL6410_DEMO_5K3K_2H2DP_LVDS_eDP                    0x29

//----------------------------------------------------------------------------------------------------
// Input Port Setting List
//----------------------------------------------------------------------------------------------------
#define _INPUT_VGA                                          0
#define _INPUT_DVI                                          1
#define _INPUT_HDMI                                         2
#define _INPUT_DP                                           3
#define _INPUT_MHL                                          4
#define _INPUT_NO_PORT                                      5

//--------------------------------------------------
// A0 Port Input Type List
//--------------------------------------------------
#define _A0_NO_PORT                                         ((_A0_INPUT_PORT << 4) | _PORT_NONE)
#define _A0_VGA_PORT                                        ((_A0_INPUT_PORT << 4) | _PORT_VGA)

//--------------------------------------------------
// VGA Connector Type List
//--------------------------------------------------
#define _VGA_CONNECTOR_NORMAL                               0
#define _VGA_CONNECTOR_YPBPR                                1

//--------------------------------------------------
// D0 Port Input Type List
//--------------------------------------------------
#define _D0_NO_PORT                                         ((_D0_INPUT_PORT << 4) | _PORT_NONE)
#define _D0_DVI_PORT                                        ((_D0_INPUT_PORT << 4) | _PORT_DVI)
#define _D0_HDMI_PORT                                       ((_D0_INPUT_PORT << 4) | _PORT_HDMI)
#define _D0_DP_PORT                                         ((_D0_INPUT_PORT << 4) | _PORT_DP)
#define _D0_MHL_PORT                                        ((_D0_INPUT_PORT << 4) | _PORT_MHL)

//--------------------------------------------------
// D1 Port Input Type List
//--------------------------------------------------
#define _D1_NO_PORT                                         ((_D1_INPUT_PORT << 4) | _PORT_NONE)
#define _D1_DVI_PORT                                        ((_D1_INPUT_PORT << 4) | _PORT_DVI)
#define _D1_HDMI_PORT                                       ((_D1_INPUT_PORT << 4) | _PORT_HDMI)
#define _D1_DP_PORT                                         ((_D1_INPUT_PORT << 4) | _PORT_DP)
#define _D1_MHL_PORT                                        ((_D1_INPUT_PORT << 4) | _PORT_MHL)

//--------------------------------------------------
// D2 Port Input Type List
//--------------------------------------------------
#define _D2_NO_PORT                                         ((_D2_INPUT_PORT << 4) | _PORT_NONE)
#define _D2_DVI_PORT                                        ((_D2_INPUT_PORT << 4) | _PORT_DVI)
#define _D2_HDMI_PORT                                       ((_D2_INPUT_PORT << 4) | _PORT_HDMI)
#define _D2_MHL_PORT                                        ((_D2_INPUT_PORT << 4) | _PORT_MHL)
#define _D2_DUAL_DVI_PORT                                   ((_D2_INPUT_PORT << 4) | _PORT_DUAL_DVI)

//--------------------------------------------------
// D3 Port Input Type List
//--------------------------------------------------
#define _D3_NO_PORT                                         ((_D3_INPUT_PORT << 4) | _PORT_NONE)
#define _D3_DVI_PORT                                        ((_D3_INPUT_PORT << 4) | _PORT_DVI)
#define _D3_HDMI_PORT                                       ((_D3_INPUT_PORT << 4) | _PORT_HDMI)
#define _D3_MHL_PORT                                        ((_D3_INPUT_PORT << 4) | _PORT_MHL)
#define _D3_DUAL_DVI_PORT                                   ((_D3_INPUT_PORT << 4) | _PORT_DUAL_DVI)

//--------------------------------------------------
// D4 Port Input Type List
//--------------------------------------------------
#define _D4_NO_PORT                                         ((_D4_INPUT_PORT << 4) | _PORT_NONE)
#define _D4_DVI_PORT                                        ((_D4_INPUT_PORT << 4) | _PORT_DVI)
#define _D4_HDMI_PORT                                       ((_D4_INPUT_PORT << 4) | _PORT_HDMI)
#define _D4_MHL_PORT                                        ((_D4_INPUT_PORT << 4) | _PORT_MHL)
#define _D4_DUAL_DVI_PORT                                   ((_D4_INPUT_PORT << 4) | _PORT_DUAL_DVI)

//--------------------------------------------------
// D5 Port Input Type List
//--------------------------------------------------
#define _D5_NO_PORT                                         ((_D5_INPUT_PORT << 4) | _PORT_NONE)
#define _D5_DVI_PORT                                        ((_D5_INPUT_PORT << 4) | _PORT_DVI)
#define _D5_HDMI_PORT                                       ((_D5_INPUT_PORT << 4) | _PORT_HDMI)
#define _D5_MHL_PORT                                        ((_D5_INPUT_PORT << 4) | _PORT_MHL)

//--------------------------------------------------
// D6 Port Input Type List
//--------------------------------------------------
#define _D6_NO_PORT                                         ((_D6_INPUT_PORT << 4) | _PORT_NONE)
#define _D6_DP_PORT                                         ((_D6_INPUT_PORT << 4) | _PORT_DP)

//--------------------------------------------------
// D7 Port Input Type List
//--------------------------------------------------
#define _D7_NO_PORT                                         ((_D7_INPUT_PORT << 4) | _PORT_NONE)
#define _D7_DP_PORT                                         ((_D7_INPUT_PORT << 4) | _PORT_DP)

//--------------------------------------------------
// DP Connector Type List
//--------------------------------------------------
#define _DP_CONNECTOR_NORMAL                                0
#define _DP_CONNECTOR_MINI                                  1
#define _DP_CONNECTOR_TYPEC                                 2

//--------------------------------------------------
// Type-C Port Controller Type List
//--------------------------------------------------
#define _PORT_CONTOLLER_NONE                                0
#define _RTS_5400                                           1
#define _EMBEDDED                                           2
#define _PORT_CONTOLLER_USER                                3

//--------------------------------------------------
// Type-C Usb Hub Type List
//--------------------------------------------------
#define _USB_HUB_NONE                                       0
#define _RTS_5411                                           1
#define _USB_HUB_USER                                       2

//--------------------------------------------------
// DP Scaler Side Lane List
//--------------------------------------------------
#define _DP_SCALER_LANE0                                    0
#define _DP_SCALER_LANE1                                    1
#define _DP_SCALER_LANE2                                    2
#define _DP_SCALER_LANE3                                    3

//--------------------------------------------------
// DP Lane Mapping Type
//--------------------------------------------------
#define _DP_LANE_MAPPING_NORMAL_TYPE                        0
#define _DP_LANE_MAPPING_TYPE_C_TYPE                        1
#define _DP_LANE_MAPPING_TYPE_C_ASSIGNMENT_E_TYPE           2

//--------------------------------------------------
// D6 DP Port Switch From D0 or D1
//--------------------------------------------------
#define _SWITCH_NONE                                        0
#define _SWITCH_FROM_D0                                     1

//--------------------------------------------------
// HSync Schimitt Trigger Level List
//--------------------------------------------------
#define _HS_SCHMITT_TRIGGER_LEVEL_00                        0
#define _HS_SCHMITT_TRIGGER_LEVEL_01                        1
#define _HS_SCHMITT_TRIGGER_LEVEL_10                        2
#define _HS_SCHMITT_TRIGGER_LEVEL_11                        3

//--------------------------------------------------
// EEPROM Support List
//--------------------------------------------------
#define _EEPROM_24LC16                                      0
#define _EEPROM_24WC64                                      1 // Slave Addr: 1010 XXX0 (Config pin A0 A1 A2 for multiple 24WC64), Start Addr: WORD Type for 8KByte addressing

//--------------------------------------------------
// EMBEDDED EDID TABLE LOCATION List
//--------------------------------------------------
#define _EDID_TABLE_LOCATION_CODE                           0
#define _EDID_TABLE_LOCATION_SYSTEM_EEPROM                  1
#define _EDID_TABLE_LOCATION_FLASH                          2
#define _EDID_TABLE_LOCATION_USER                           3

//--------------------------------------------------
// EMBEDDED EDID Size List
//--------------------------------------------------
#define _EDID_SIZE_NONE                                     0
#define _EDID_SIZE_128                                      0x80U
#define _EDID_SIZE_256                                      0x100U
#define _EDID_SIZE_384                                      0x180U
#define _EDID_SIZE_512                                      0x200U
#define _EDID_NOT_EXIST                                     0xFFFF

//--------------------------------------------------
// AUX DDC Channel Support List
//--------------------------------------------------
#define _NO_AUX                                             0
#define _D0_AUX_MAP_DDC0_PIN                                1
#define _D0_AUX_MAP_DDC1_PIN                                2
#define _D0_AUX_MAP_DDC2_PIN                                3
#define _D1_AUX_MAP_DDC0_PIN                                4
#define _D1_AUX_MAP_DDC1_PIN                                5
#define _D1_AUX_MAP_DDC2_PIN                                6
#define _D2_AUX_MAP_DDC0_PIN                                7
#define _D2_AUX_MAP_DDC1_PIN                                8
#define _D2_AUX_MAP_DDC2_PIN                                9

//--------------------------------------------------
// LVDS Data Port Power Selection
//--------------------------------------------------
#define _LVDS_1_PORT_A                                      0
#define _LVDS_1_PORT_B                                      1
#define _LVDS_1_PORT_C                                      2
#define _LVDS_1_PORT_D                                      3
#define _LVDS_2_PORT_AB                                     4
#define _LVDS_2_PORT_CD                                     5
#define _LVDS_2_PORT_EF                                     6
#define _LVDS_2_PORT_GH                                     7
#define _LVDS_4_PORT_ABCD                                   8
#define _LVDS_4_PORT_CDEF                                   9
#define _LVDS_4_PORT_EFGH                                   10
#define _LVDS_8_PORT_ABCDEFGH                               11

//--------------------------------------------------
// LVDS CLK Position Selection
//--------------------------------------------------
#define _NORMAL_MODE                                        0
#define _MODE_1                                             1
#define _MODE_2                                             2
#define _MODE_3                                             3

//--------------------------------------------------
// LVDS Phase Option List
//--------------------------------------------------
#define _LVDS_PI_PHASE_AB0                                  0
#define _LVDS_PI_PHASE_AB1                                  1
#define _LVDS_PI_PHASE_AB2                                  2
#define _LVDS_PI_PHASE_AB3                                  3

#define _LVDS_PI_PHASE_CD0                                  0
#define _LVDS_PI_PHASE_CD1                                  1
#define _LVDS_PI_PHASE_CD2                                  2
#define _LVDS_PI_PHASE_CD3                                  3

#define _LVDS_PI_PHASE_EF0                                  0
#define _LVDS_PI_PHASE_EF1                                  1
#define _LVDS_PI_PHASE_EF2                                  2
#define _LVDS_PI_PHASE_EF3                                  3

#define _LVDS_PI_PHASE_GH0                                  0
#define _LVDS_PI_PHASE_GH1                                  1
#define _LVDS_PI_PHASE_GH2                                  2
#define _LVDS_PI_PHASE_GH3                                  3

//--------------------------------------------------
// LVDS Phase Control List
//--------------------------------------------------
#define _LVDS_PHASE0                                        0
#define _LVDS_PHASE1                                        1
#define _LVDS_PHASE2                                        2
#define _LVDS_PHASE3                                        3
#define _LVDS_PHASE4                                        4
#define _LVDS_PHASE5                                        5
#define _LVDS_PHASE6                                        6
#define _LVDS_PHASE7                                        7
#define _LVDS_PHASE8                                        8
#define _LVDS_PHASE9                                        9
#define _LVDS_PHASE10                                       10
#define _LVDS_PHASE11                                       11
#define _LVDS_PHASE12                                       12
#define _LVDS_PHASE13                                       13
#define _LVDS_PHASE14                                       14
#define _LVDS_PHASE15                                       15
#define _LVDS_PHASE16                                       16
#define _LVDS_PHASE17                                       17
#define _LVDS_PHASE18                                       18
#define _LVDS_PHASE19                                       19
#define _LVDS_PHASE20                                       20
#define _LVDS_PHASE21                                       21
#define _LVDS_PHASE22                                       22
#define _LVDS_PHASE23                                       23
#define _LVDS_PHASE24                                       24
#define _LVDS_PHASE25                                       25
#define _LVDS_PHASE26                                       26
#define _LVDS_PHASE27                                       27
#define _LVDS_PHASE28                                       28
#define _LVDS_PHASE29                                       29
#define _LVDS_PHASE30                                       30
#define _LVDS_PHASE31                                       31

//--------------------------------------------------
// Panel DPTx Lane Port Selection
//--------------------------------------------------
#define _DPTX_TX1_PORT                                      _BIT0
#define _DPTX_TX2_PORT                                      _BIT1

//--------------------------------------------------
// PWM Support List
//--------------------------------------------------
#define _NO_PWM                                             0x00
#define _PWM0                                               _BIT0
#define _PWM1                                               _BIT1
#define _PWM2                                               _BIT2
#define _PWM3                                               _BIT3
#define _PWM4                                               _BIT4
#define _PWM5                                               _BIT5

//--------------------------------------------------
// PWM Option List
//--------------------------------------------------
#define _PWM_8BIT                                           256U
#define _PWM_12BIT                                          4096U

//--------------------------------------------------
// PWM Support List
//--------------------------------------------------
#define _XTAL27000K                                         27000UL
#define _XTAL24576K                                         24576UL
#define _XTAL24000K                                         24000UL
#define _XTAL14318K                                         14318UL

//--------------------------------------------------
// IIC Application Support List
//--------------------------------------------------
#define _IIC_SYS_EEPROM                                     0
#define _IIC_SMBUS                                          1

//--------------------------------------------------
// IIC SDA/SCL Pin List
//--------------------------------------------------
#define _NO_IIC_PIN                                         0
#define _SW_IIC_PIN_GPIO                                    1
#define _HW_IIC_PIN_J7_H6                                   2
#define _HW_IIC_PIN_K28_K29                                 3
#define _HW_IIC_PIN_AG3_AG4                                 4

#if(_SCALER_TYPE == _RL6410_SERIES)
#define _HW_IIC_PIN_AD28_AH27                               10
#define _HW_IIC_PIN_AG8_AG9                                 11
#endif

//--------------------------------------------------
// HW IIC Speed List
//--------------------------------------------------
#define _HW_IIC_LOW_SPEED_100K                              0
#define _HW_IIC_HIGH_SPEED_400K                             1

//--------------------------------------------------
// DDC Switch GPIO List
//--------------------------------------------------
#define _DDC0_SWITCH_GPIO                                   0
#define _DDC0_SWITCH_DDC                                    1
#define _DDC1_SWITCH_GPIO                                   2
#define _DDC1_SWITCH_DDC                                    3
#define _DDC2_SWITCH_GPIO                                   4
#define _DDC2_SWITCH_DDC                                    5
#define _DDC3_SWITCH_GPIO                                   6
#define _DDC3_SWITCH_DDC                                    7
#define _DDC4_SWITCH_GPIO                                   8
#define _DDC4_SWITCH_DDC                                    9
#define _DDC5_SWITCH_GPIO                                   10
#define _DDC5_SWITCH_DDC                                    11
#define _DDC_VGA_SWITCH_GPIO                                12
#define _DDC_VGA_SWITCH_DDC                                 13

//--------------------------------------------------
// Spread Spectrum Speed
//--------------------------------------------------
#define _SPEED_33K                                          0
#define _SPEED_66K                                          1
#define _SPEED_30K                                          2

//--------------------------------------------------
// PCB Type for DP HBR2
//--------------------------------------------------
#define _DP_HBR2_NORMAL_PCB                                 0
#define _DP_HBR2_AIO_PCB                                    1
#define _DP_HBR2_RE_DRIVER_PCB                              2

//--------------------------------------------------
// DP Swing Level
//--------------------------------------------------
#define _DP_SWING_400_MV                                    0
#define _DP_SWING_600_MV                                    1
#define _DP_SWING_800_MV                                    2
#define _DP_SWING_1200_MV                                   3

//--------------------------------------------------
// DP Preemphasis Level
//--------------------------------------------------
#define _DP_PREEMPHASIS_0_DB                                0
#define _DP_PREEMPHASIS_3_5_DB                              1
#define _DP_PREEMPHASIS_6_DB                                2
#define _DP_PREEMPHASIS_9_5_DB                              3

//--------------------------------------------------
// LVDS Driving Current List
//--------------------------------------------------
#define _LVDS_DRIV_CONTROL_2_0                              0
#define _LVDS_DRIV_CONTROL_2_5                              1
#define _LVDS_DRIV_CONTROL_3_0                              2
#define _LVDS_DRIV_CONTROL_3_5                              3
#define _LVDS_DRIV_CONTROL_1_5                              4

//--------------------------------------------------
// LVDS Slew Rate Control List
//--------------------------------------------------
#define _LVDS_SR_CONTROL_0                                  0
#define _LVDS_SR_CONTROL_1                                  1
#define _LVDS_SR_CONTROL_2                                  2
#define _LVDS_SR_CONTROL_3                                  3

//--------------------------------------------------
// LVDS Shape Adjustment List
//--------------------------------------------------
#define _LVDS_SHAPE_FAST_TO_SLOW                            0
#define _LVDS_SHAPE_SLOW_TO_FAST                            1

//--------------------------------------------------
// LVDS Common Mode Voltage List
//--------------------------------------------------
#define _LVDS_VCM_LOW                                       0
#define _LVDS_VCM_NORMAL                                    1
#define _LVDS_VCM_HIGH                                      2
#define _LVDS_VCM_USER                                      3

//--------------------------------------------------
// LVDS Pre-emphasis Current List
//--------------------------------------------------
#define _LVDS_PRE_EMPHASIS_0                                0
#define _LVDS_PRE_EMPHASIS_1                                1
#define _LVDS_PRE_EMPHASIS_2                                2
#define _LVDS_PRE_EMPHASIS_3                                3

//--------------------------------------------------
// Vbyone Driving Current List
//--------------------------------------------------
#define _VBO_DRIV_CONTROL_2_0                               0
#define _VBO_DRIV_CONTROL_2_5                               1
#define _VBO_DRIV_CONTROL_3_0                               2
#define _VBO_DRIV_CONTROL_3_5                               3

//--------------------------------------------------
// Vbyone Pre-emphasis Current List
//--------------------------------------------------
#define _VBO_PRE_EMPHASIS_0                                 0
#define _VBO_PRE_EMPHASIS_1                                 1
#define _VBO_PRE_EMPHASIS_2                                 2
#define _VBO_PRE_EMPHASIS_3                                 3

//------------------------------------------------
// External Memory Size Options
//------------------------------------------------
#define _EXTERNAL_MEMORY_SIZE_NONE                          _NO_MEMORY
#define _1G_16BIT_DDR3_1PC                                  (_MEMORY_DENSITY_64M_16 | _MEMORY_1PC | _MEMORY_DDR3)
#define _1G_16BIT_DDR3_2PCS                                 (_MEMORY_DENSITY_64M_16 | _MEMORY_2PCS | _MEMORY_DDR3)
#define _2G_16BIT_GDDR3_1PC                                 (_MEMORY_DENSITY_128M_16 | _MEMORY_1PC | _MEMORY_DDR3)
#define _2G_16BIT_GDDR3_2PCS                                (_MEMORY_DENSITY_128M_16 | _MEMORY_2PCS | _MEMORY_DDR3)
#define _4G_16BIT_GDDR3_1PC                                 (_MEMORY_DENSITY_256M_16 | _MEMORY_1PC | _MEMORY_DDR3)
#define _4G_16BIT_GDDR3_2PCS                                (_MEMORY_DENSITY_256M_16 | _MEMORY_2PCS | _MEMORY_DDR3)

//--------------------------------------------------
// Definitions of Cable Connect LEVEL
//--------------------------------------------------
#define _PCB_CABLE_CONNECT_LEVEL                            0
#define _PCB_CABLE_DISCONNECT_LEVEL                         1

//--------------------------------------------------
// Definitions of MHL Cable Connect
//--------------------------------------------------
#define _MHL_CABLE_CONNECT                                  1
#define _MHL_CABLE_DISCONNECT                               0

//-----------------------------------------------
// Macro of MHL/HDMI Detection
//-----------------------------------------------
#define _TMDS_HDMI_MODE                                     0
#define _TMDS_MHL_MODE                                      1

//--------------------------------------------------
// Audio Output Option List
//--------------------------------------------------
#define _I2S                                                0
#define _SPDIF                                              1

#endif // End of #ifndef __PCB_LIST_H__
