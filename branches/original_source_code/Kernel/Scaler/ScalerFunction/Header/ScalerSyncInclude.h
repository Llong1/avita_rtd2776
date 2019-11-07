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
// ID Code      : ScalerSyncInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))

//--------------------------------------------------
// Definitions of Measure Clk Source
//--------------------------------------------------
#define _CLK_SOURCE_RED                                     0
#define _CLK_SOURCE_BLUE                                    1
#define _CLK_SOURCE_GREEN                                   2
#define _CLK_SOURCE_TMDS                                    3

//--------------------------------------------------
// Define for Clk Freq Detection
//--------------------------------------------------
#define _TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND            (WORD)((DWORD)600 * 1040 / ((_GDI_CLK_KHZ * _TMDS_MEASURE_CLOCK_DIVIDER) / _TMDS_MEASURE_CLOCK_COUNTER)) // (600 / _TMDS_MEASURE_CLOCK_DIVIDER) * (1.04) * _TMDS_MEASURE_CLOCK_COUNTER / _GDI_CLK(Mhz)
#define _TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND             (WORD)((DWORD)340 * 1040 / ((_GDI_CLK_KHZ * _TMDS_MEASURE_CLOCK_DIVIDER) / _TMDS_MEASURE_CLOCK_COUNTER)) // (340 / _TMDS_MEASURE_CLOCK_DIVIDER) * (1.04) * _TMDS_MEASURE_CLOCK_COUNTER / _GDI_CLK(Mhz)
#define _TMDS_FREQ_NORMAL_LOWER_BOUND                       (WORD)((DWORD)_TMDS_CLOCK_MEASURE_LOWER_BOUNDARY * 960 / ((_GDI_CLK_KHZ * _TMDS_MEASURE_CLOCK_DIVIDER) / _TMDS_MEASURE_CLOCK_COUNTER)) // (25 / _TMDS_MEASURE_CLOCK_DIVIDER) * (0.96) * _TMDS_MEASURE_CLOCK_COUNTER / _GDI_CLK(Mhz)

#define _TMDS_FREQ_PS_HIGH_SPEED_UPPER_BOUND                (WORD)((DWORD)600 * 1040 * 10 / ((_INTERNAL_OSC_XTAL * _TMDS_MEASURE_CLOCK_DIVIDER) / _TMDS_MEASURE_CLOCK_COUNTER * 9)) // (600 / _TMDS_MEASURE_CLOCK_DIVIDER) * 1.04 * _TMDS_MEASURE_CLOCK_COUNTER / (_INTERNAL_OSC_XTAL(Mhz) * 0.9)
#define _TMDS_FREQ_PS_LOW_SPEED_UPPER_BOUND                 (WORD)((DWORD)340 * 1040 * 10 / ((_INTERNAL_OSC_XTAL * _TMDS_MEASURE_CLOCK_DIVIDER) / _TMDS_MEASURE_CLOCK_COUNTER * 9)) // (340 / _TMDS_MEASURE_CLOCK_DIVIDER) * (1.04) * _TMDS_MEASURE_CLOCK_COUNTER / (_INTERNAL_OSC_XTAL(Mhz) * 0.9)
#define _TMDS_FREQ_PS_LOWER_BOUND                           (WORD)((DWORD)_TMDS_CLOCK_MEASURE_LOWER_BOUNDARY * 960 * 10 / ((_INTERNAL_OSC_XTAL * _TMDS_MEASURE_CLOCK_DIVIDER) / _TMDS_MEASURE_CLOCK_COUNTER * 11)) // (25 / _TMDS_MEASURE_CLOCK_DIVIDER) * (0.96) * _TMDS_MEASURE_CLOCK_COUNTER / (_INTERNAL_OSC_XTAL(Mhz) * 1.1)

#if(_MHL_SUPPORT == _ON)

#define _TMDS_MHL_FREQ_NORMAL_UPPER_BOUND                   (WORD)((((DWORD)150 * 1040 + (_TMDS_MEASURE_CLOCK_DIVIDER * (_GDI_CLK_KHZ / _TMDS_MEASURE_CLOCK_COUNTER)) / 2) / (_GDI_CLK_KHZ / _TMDS_MEASURE_CLOCK_COUNTER)) / _TMDS_MEASURE_CLOCK_DIVIDER) // (150 / _TMDS_MEASURE_CLOCK_DIVIDER) * (1.04) * _TMDS_MEASURE_CLOCK_COUNTER / _GDI_CLK(Mhz) + 0.5
#define _TMDS_MHL_FREQ_PS_UPPER_BOUND                       (WORD)((((DWORD)150 * 1040 * 10 + (_TMDS_MEASURE_CLOCK_DIVIDER * (_INTERNAL_OSC_XTAL / _TMDS_MEASURE_CLOCK_COUNTER * 9))) / (_INTERNAL_OSC_XTAL / _TMDS_MEASURE_CLOCK_COUNTER * 9)) / _TMDS_MEASURE_CLOCK_DIVIDER) // (150 / _TMDS_MEASURE_CLOCK_DIVIDER) * (1.04) * _TMDS_MEASURE_CLOCK_COUNTER / (_INTERNAL_OSC_XTAL(Mhz) * 0.9) + 1 = 3210

#if(_MHL_3_0_SUPPORT == _ON)

#define _TMDS_MHL3_ECBUS_FREQ_NORMAL_LOWER_BOUND            (WORD)((((DWORD)75 * 960 + (_TMDS_MEASURE_CLOCK_DIVIDER * (_GDI_CLK_KHZ / _TMDS_MEASURE_CLOCK_COUNTER)) / 2) / (_GDI_CLK_KHZ / _TMDS_MEASURE_CLOCK_COUNTER)) / _TMDS_MEASURE_CLOCK_DIVIDER) // (75 / _TMDS_MEASURE_CLOCK_DIVIDER) * (0.96) * _TMDS_MEASURE_CLOCK_COUNTER / _GDI_CLK(Mhz) + 0.5
#define _TMDS_MHL3_ECBUS_FREQ_PS_LOWER_BOUND                (WORD)(((DWORD)75 * 960 * 10 / (_INTERNAL_OSC_XTAL / _TMDS_MEASURE_CLOCK_COUNTER * 11)) / _TMDS_MEASURE_CLOCK_DIVIDER) // (75 / _TMDS_MEASURE_CLOCK_DIVIDER) * (0.96) * _TMDS_MEASURE_CLOCK_COUNTER / (_INTERNAL_OSC_XTAL(Mhz) * 1.1)
#endif

#endif // End of #if(_MHL_SUPPORT == _ON)

//--------------------------------------------------
// Define for Video Detect
//--------------------------------------------------
#define _TMDS_VIDEO_DATA_NONE                               0
#define _TMDS_VIDEO_DATA_DE_ONLY                            1
#define _TMDS_VIDEO_DATA_RGBHV                              2

//--------------------------------------------------
// Define for Watch Dog Type
//--------------------------------------------------
#define _HDMI_AVI_INFO_VARIATION_WD                         _BIT0
#define _HDMI_AV_MUTE_WD                                    _BIT1

//--------------------------------------------------
// Define for Packet Type
//--------------------------------------------------
#define _HDMI_3D_FORMAT                                     0x81
#define _HDMI_AVI_INFO_TYPE                                 0x82
#define _HDMI_AUDIO_INFO_TYPE                               0x84
#define _HDMI_GENERAL_CONTROL_TYPE                          0x03

//--------------------------------------------------
// Definitions of MHL Mode for Physical Settings
//--------------------------------------------------
#define _TMDS_24BIT_PHY_SETTING                             0x00
#define _TMDS_MHL_PPMODE_PHY_SETTING                        0x01
#define _TMDS_MHL_ECBUS_PHY_SETTING                         0x02

#if(_HDMI_2_0_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of HDMI 2.0 SCDC Read Request Done Outcome
//--------------------------------------------------
#define _HDMI_2_0_READ_REQUEST_ACK_DONE                     0x00
#define _HDMI_2_0_READ_REQUEST_ACK_STOP                     0x10
#define _HDMI_2_0_READ_REQUEST_NACK1                        0x20
#define _HDMI_2_0_READ_REQUEST_NACK2                        0x30
#define _HDMI_2_0_READ_REQUEST_NONE                         0x70
#endif // #if(_HDMI_2_0_SUPPORT == _ON)

#endif // #if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))

//--------------------------------------------------
// Define for SPD Packet Type
//--------------------------------------------------
#if(_FREESYNC_SUPPORT == _ON)
#define _SPD_INFO_TYPE                                      0x83
#endif

//--------------------------------------------------
// Define for HDR Packet Type
//--------------------------------------------------
#if(_ULTRA_HDR_SUPPORT == _ON)
#define _HDR_INFO_TYPE                                      0x87
#endif

//--------------------------------------------------
// Define for Audio Time Stamp Packet Type
//--------------------------------------------------
#define _DP_AUDIO_TIMESTAMP                                 0x01

//--------------------------------------------------
// Definition of DP Measure Polling Time
//--------------------------------------------------
#define _DP_MEASURE_POLLING_TIMEOUT                         100

//--------------------------------------------------
// Definition of DP Display Format Parameter
//--------------------------------------------------
#define _DP_VSYNC_FRONT_PORCH                               4
#define _DP_HSYNC_FRONT_PORCH                               8
#define _DP_VSYNC_WIDTH                                     3
#define _DP_HSYNC_WIDTH_MEASURE_COUNTER                     2 // = HSW msa * Measure clk / Pixel clk
#define _DP_DE_ONLY_MODE_HSW                                20
#define _DP_DE_ONLY_MODE_HSTART                             32
#define _DP_DE_ONLY_MODE_VSW                                2
#define _DP_DE_ONLY_MODE_VSTART                             8
#define _DP_FREESYNC_DV_SYNC_HEIGHT                         1
#define _DP_ONE_FRAME_TIME_MAX                              43 // in ms @ 23Hz
#define _DP_TWO_FRAME_TIME_MAX                              86 // in ms @ 23Hz

//--------------------------------------------------
// Definition of Aux Diff Mode
//--------------------------------------------------
#define _DP_AUX_DIFF_MODE                                   _ON

//--------------------------------------------------
// Definitions of DP Link Training Stage
//--------------------------------------------------
#define _DP_TRAINING_PATTERN_END                            0
#define _DP_TRAINING_PATTERN_1                              1
#define _DP_TRAINING_PATTERN_2                              2
#define _DP_TRAINING_PATTERN_3                              3

//--------------------------------------------------
// Definitions of DP HDCP Info
//--------------------------------------------------
#define _DP_HDCP_SHA1_INPUT_SIZE                            64

//--------------------------------------------------
// Definitions of MHL Status
//--------------------------------------------------
#define _MHL_STATE_INITIAL                                  0
#define _MHL_STATE_WAKE_UP_DONE                             1
#define _MHL_STATE_DISCOVERY_DONE                           2
#define _MHL_STATE_SET_DEV_CAP_DONE                         3
#define _MHL_STATE_DEV_CAP_RDY                              4
#define _MHL_STATE_HPD_DONE                                 5
#define _MHL_STATE_PATH_EN_DONE                             6
#define _MHL_STATE_DONE                                     7

#if(_MHL_3_0_SUPPORT == _ON)
#define _MHL_STATE_BIST_TESTING                             8
#endif

//--------------------------------------------------
// Definitions of MHL Packet Types
//--------------------------------------------------
#define _DDC_PACKET                                         0
#define _MSC_PACKET                                         2

#define _MSC_SEND_DATA                                      0
#define _MSC_SEND_COMMAND                                   1
#define _MSC_SEND_COM_DAT                                   2
#define _MSC_SEND_COM_OFF_DAT                               3
#define _MSC_SEND_COM_OFF_DAT_COM                           4
#define _MSC_SEND_COM_OFF                                   5

#define _MSC_WAIT_NULL                                      0
#define _MSC_WAIT_COMMAND                                   1
#define _MSC_WAIT_DATA                                      2
#define _MSC_WAIT_COM_DAT                                   3

#define _MSC_ACK_PACKET                                     0x33
#define _MSC_NACK_PACKET                                    0x34
#define _MSC_ABORT_PACKET                                   0x35
#define _MSC_EOF_PACKET                                     0x32
#define _MSC_PROTOCOL_ERROR                                 0x02

//--------------------------------------------------
// Definitions of MHL Adopter ID
//--------------------------------------------------
#define _HTC_BUTTERFLY_ADOPTER_ID_HBYTE                     0x01
#define _HTC_BUTTERFLY_ADOPTER_ID_LBYTE                     0x6F

#define _SAMSUNG_SII_ADOPTER_ID_HBYTE                       0x00
#define _SAMSUNG_SII_ADOPTER_ID_LBYTE                       0x00

#define _HUAWEI_D2_ADOPTER_ID_HBYTE                         0x01
#define _HUAWEI_D2_ADOPTER_ID_LBYTE                         0x42

#define _ZTE_NUBIA_Z5_ADOPTER_ID_HBYTE                      0x01
#define _ZTE_NUBIA_Z5_ADOPTER_ID_LBYTE                      0x42

#define _ASUS_PADFONE2_ADOPTER_ID_HBYTE                     0x05
#define _ASUS_PADFONE2_ADOPTER_ID_LBYTE                     0x2C

#define _CHROMA_MHL_ADOPTER_ID_HBYTE                        0x05
#define _CHROMA_MHL_ADOPTER_ID_LBYTE                        0xB2

#define _SAMSUNG_NOTE2_ADOPTER_ID_HBYTE                     0x01
#define _SAMSUNG_NOTE2_ADOPTER_ID_LBYTE                     0x41

#define _UTS800_SL863_ADOPTER_ID_HBYTE                      0x01
#define _UTS800_SL863_ADOPTER_ID_LBYTE                      0x42

//--------------------------------------------------
// Macros of MHL Write Burst ID
//--------------------------------------------------
#define _MHL_3D_VIC_HB                                      0x00
#define _MHL_3D_VIC_LB                                      0x10
#define _MHL_3D_DTD_HB                                      0x00
#define _MHL_3D_DTD_LB                                      0x11

#define _MSC_NONE                                           0xFF

#if(_MHL_3_0_SUPPORT == _ON)

#define _MHL_WRITE_BURST_ECBUS_VC_ASSIGN_HBYTE              0x00
#define _MHL_WRITE_BURST_ECBUS_VC_ASSIGN_LBYTE              0x38
#define _MHL_WRITE_BURST_ECBUS_VC_CONFIRM_HBYTE             0x00
#define _MHL_WRITE_BURST_ECBUS_VC_CONFIRM_LBYTE             0x39
#define _MHL_WRITE_BURST_ECBUS_BIST_SETUP_HBYTE             0x00
#define _MHL_WRITE_BURST_ECBUS_BIST_SETUP_LBYTE             0x51
#define _MHL_WRITE_BURST_ECBUS_BIST_RETURN_STAT_HBYTE       0x00
#define _MHL_WRITE_BURST_ECBUS_BIST_RETURN_STAT_LBYTE       0x52
#define _MHL_WRITE_BURST_ECBUS_HEV_VIC_HBYTE                0x00
#define _MHL_WRITE_BURST_ECBUS_HEV_VIC_LBYTE                0x20
#define _MHL_WRITE_BURST_ECBUS_HEV_DTDA_HBYTE               0x00
#define _MHL_WRITE_BURST_ECBUS_HEV_DTDA_LBYTE               0x21
#define _MHL_WRITE_BURST_ECBUS_HEV_DTDB_HBYTE               0x00
#define _MHL_WRITE_BURST_ECBUS_HEV_DTDB_LBYTE               0x22
#define _MHL_WRITE_BURST_ECBUS_EMSC_SUPPORT_HBYTE           0x00
#define _MHL_WRITE_BURST_ECBUS_EMSC_SUPPORT_LBYTE           0x61
#define _MHL_WRITE_BURST_ECBUS_HID_PAYLOAD_HBYTE            0x00
#define _MHL_WRITE_BURST_ECBUS_HID_PAYLOAD_LBYTE            0x62
#define _MHL_WRITE_BURST_ECBUS_BLK_RCV_BUFFER_INFO_HBYTE    0x00
#define _MHL_WRITE_BURST_ECBUS_BLK_RCV_BUFFER_INFO_LBYTE    0x63
#define _MHL_WRITE_BURST_ECBUS_BITS_PER_PIXEL_FMT_HBYTE     0x00
#define _MHL_WRITE_BURST_ECBUS_BITS_PER_PIXEL_FMT_LBYTE     0x64

#define _MHL_ECBUS_EMSC_STANDARD_TRANSPORT_HEADER           0xFF

//--------------------------------------------------
// Macros of ECBUS Virtual Channel Info
//--------------------------------------------------
#define _ECBUS_CBUS1_VC_NUM                                 0
#define _ECBUS_EMSC_VC_NUM                                  1
#define _ECBUS_CBUS1_VC_SIZE                                1

//--------------------------------------------------
// Macros of ECBUS eMSC Length Remaining
//--------------------------------------------------
#define _MHL_ECBUS_REQ_COMMAND_LENGTH                       0x02
#define _MHL_ECBUS_BLK_RCV_BUFFER_INFO_LENGTH               0x04

#define _MHL_ECBUS_EMSC_HID_TRANS_ACK_LENGTH                0x03 // 0x04
#define _MHL_ECBUS_HID_HID_ACK_LENGTH_REMAIN                0x06
#define _MHL_ECBUS_HID_GET_REPORT_DSCRPT_LENGTH_REMAIN      0x05
#define _MHL_ECBUS_HID_GET_MHID_DSCRPT_LENGTH_REMAIN        0x07
#define _MHL_ECBUS_HID_GET_REPORT_LENGTH_REMAIN             0x07
#define _MHL_ECBUS_HID_DSCRPT_UPDATE_LENGTH_REMAIN          0x05

#if(_MHL3_ECBUS_HID_SUPPORT == _ON)
//--------------------------------------------------
// Macros of ECBUS HID Message
//--------------------------------------------------
#define _MHL_ECBUS_EMSC_HID_TRANS_ACK                       0x80
#define _MHL_ECBUS_HID_HID_ACK                              0x00
#define _MHL_ECBUS_HID_REPORT                               0x01
#define _MHL_ECBUS_HID_GET_REPORT_DSCRPT                    0x02
#define _MHL_ECBUS_HID_REPORT_DSCRPT                        0x03
#define _MHL_ECBUS_HID_GET_MHID_DSCRPT                      0x04
#define _MHL_ECBUS_HID_MHID_DSCRPT                          0x05
#define _MHL_ECBUS_HID_GET_REPORT                           0x06
#define _MHL_ECBUS_HID_SET_REPORT                           0x07
#define _MHL_ECBUS_HID_DSCRPT_UPDATE                        0x08

//--------------------------------------------------
// Macros of ECBUS HID Ack Status
//--------------------------------------------------
#define _MHL_ECBUS_HID_ACK_SUCCESS                          0x00
#define _MHL_ECBUS_HID_ACK_NODEV                            0x01
#define _MHL_ECBUS_HID_ACK_NODATA                           0x02
#define _MHL_ECBUS_HID_ACK_WAIT                             0x03
#define _MHL_ECBUS_HID_ACK_TIMEOUT                          0x04
#define _MHL_ECBUS_HID_ACK_PROTV                            0x05
#define _MHL_ECBUS_HID_ACK_WRTYPE                           0x06
#define _MHL_ECBUS_HID_ACK_WRID                             0x07
#define _MHL_ECBUS_HID_ACK_WRFMT                            0x08
#define _MHL_ECBUS_HID_ACK_WRMFMT                           0x09

#endif // End of #if(_MHL3_ECBUS_HID_SUPPORT == _ON)

#endif // End of #if(_MHL_3_0_SUPPORT == _ON)

//--------------------------------------------------
// Macro of Input Pixel Clk (Unit in 0.1MHz)
//--------------------------------------------------
#define GET_A0_INPUT_PIXEL_CLK()                            (g_usA0PixelClk)
#define SET_A0_INPUT_PIXEL_CLK(x)                           (g_usA0PixelClk = (x))
#define CLR_A0_INPUT_PIXEL_CLK()                            (g_usA0PixelClk = 0)

#define GET_D0_INPUT_PIXEL_CLK()                            (g_usD0PixelClk)
#define SET_D0_INPUT_PIXEL_CLK(x)                           (g_usD0PixelClk = (x))
#define CLR_D0_INPUT_PIXEL_CLK()                            (g_usD0PixelClk = 0)

#define GET_D1_INPUT_PIXEL_CLK()                            (g_usD1PixelClk)
#define SET_D1_INPUT_PIXEL_CLK(x)                           (g_usD1PixelClk = (x))
#define CLR_D1_INPUT_PIXEL_CLK()                            (g_usD1PixelClk = 0)

#define GET_D2_INPUT_PIXEL_CLK()                            (g_usD2PixelClk)
#define SET_D2_INPUT_PIXEL_CLK(x)                           (g_usD2PixelClk = (x))
#define CLR_D2_INPUT_PIXEL_CLK()                            (g_usD2PixelClk = 0)

#define GET_D3_INPUT_PIXEL_CLK()                            (g_usD3PixelClk)
#define SET_D3_INPUT_PIXEL_CLK(x)                           (g_usD3PixelClk = (x))
#define CLR_D3_INPUT_PIXEL_CLK()                            (g_usD3PixelClk = 0)

#define GET_D4_INPUT_PIXEL_CLK()                            (g_usD4PixelClk)
#define SET_D4_INPUT_PIXEL_CLK(x)                           (g_usD4PixelClk = (x))
#define CLR_D4_INPUT_PIXEL_CLK()                            (g_usD4PixelClk = 0)

#define GET_D5_INPUT_PIXEL_CLK()                            (g_usD5PixelClk)
#define SET_D5_INPUT_PIXEL_CLK(x)                           (g_usD5PixelClk = (x))
#define CLR_D5_INPUT_PIXEL_CLK()                            (g_usD5PixelClk = 0)

//--------------------------------------------------
// Macro of Input Off Line Measure Get Pixel Clk (Unit in 0.1MHz)
//--------------------------------------------------
#define GET_TMDS_D0_OFFLINE_MEASURE_CLK()                   (g_usTmdsD0OffLineMeasureClk)
#define SET_TMDS_D0_OFFLINE_MEASURE_CLK(x)                  (g_usTmdsD0OffLineMeasureClk = (x))
#define CLR_TMDS_D0_OFFLINE_MEASURE_CLK()                   (g_usTmdsD0OffLineMeasureClk = 0)

#define GET_TMDS_D1_OFFLINE_MEASURE_CLK()                   (g_usTmdsD1OffLineMeasureClk)
#define SET_TMDS_D1_OFFLINE_MEASURE_CLK(x)                  (g_usTmdsD1OffLineMeasureClk = (x))
#define CLR_TMDS_D1_OFFLINE_MEASURE_CLK()                   (g_usTmdsD1OffLineMeasureClk = 0)

#define GET_TMDS_D2_OFFLINE_MEASURE_CLK()                   (g_usTmdsD2OffLineMeasureClk)
#define SET_TMDS_D2_OFFLINE_MEASURE_CLK(x)                  (g_usTmdsD2OffLineMeasureClk = (x))
#define CLR_TMDS_D2_OFFLINE_MEASURE_CLK()                   (g_usTmdsD2OffLineMeasureClk = 0)

#define GET_TMDS_D3_OFFLINE_MEASURE_CLK()                   (g_usTmdsD3OffLineMeasureClk)
#define SET_TMDS_D3_OFFLINE_MEASURE_CLK(x)                  (g_usTmdsD3OffLineMeasureClk = (x))
#define CLR_TMDS_D3_OFFLINE_MEASURE_CLK()                   (g_usTmdsD3OffLineMeasureClk = 0)

#define GET_TMDS_D4_OFFLINE_MEASURE_CLK()                   (g_usTmdsD4OffLineMeasureClk)
#define SET_TMDS_D4_OFFLINE_MEASURE_CLK(x)                  (g_usTmdsD4OffLineMeasureClk = (x))
#define CLR_TMDS_D4_OFFLINE_MEASURE_CLK()                   (g_usTmdsD4OffLineMeasureClk = 0)

#define GET_TMDS_D5_OFFLINE_MEASURE_CLK()                   (g_usTmdsD5OffLineMeasureClk)
#define SET_TMDS_D5_OFFLINE_MEASURE_CLK(x)                  (g_usTmdsD5OffLineMeasureClk = (x))
#define CLR_TMDS_D5_OFFLINE_MEASURE_CLK()                   (g_usTmdsD5OffLineMeasureClk = 0)


#if(_DIGITAL_PORT_SUPPORT == _ON)
//--------------------------------------------------
// Macro of Digital Input Port Switch
//--------------------------------------------------
/*
#define GET_D0_PORT_DIGITAL_SWITCH()                         ((g_ucDigitalSwitch & _BIT7) >> 7)
#define SET_D0_PORT_DIGITAL_SWITCH()                         (g_ucDigitalSwitch |= _BIT7)
#define CLR_D0_PORT_DIGITAL_SWITCH()                         (g_ucDigitalSwitch &= ~_BIT7)

#define GET_D1_PORT_DIGITAL_SWITCH()                         ((g_ucDigitalSwitch & _BIT6) >> 6)
#define SET_D1_PORT_DIGITAL_SWITCH()                         (g_ucDigitalSwitch |= _BIT6)
#define CLR_D1_PORT_DIGITAL_SWITCH()                         (g_ucDigitalSwitch &= ~_BIT6)
*/

#define GET_DIGITAL_PORT_SWITCH_TO_D0()                     ((g_ucDigitalSwitch & _BIT5) >> 5)
#define SET_DIGITAL_PORT_SWITCH_TO_D0()                     (g_ucDigitalSwitch |= _BIT5)
#define CLR_DIGITAL_PORT_SWITCH_TO_D0()                     (g_ucDigitalSwitch &= ~_BIT5)

#define GET_DIGITAL_PORT_SWITCH_TO_D1()                     ((g_ucDigitalSwitch & _BIT4) >> 4)
#define SET_DIGITAL_PORT_SWITCH_TO_D1()                     (g_ucDigitalSwitch |= _BIT4)
#define CLR_DIGITAL_PORT_SWITCH_TO_D1()                     (g_ucDigitalSwitch &= ~_BIT4)

#define GET_DIGITAL_PORT_SWITCH_TO_D2()                     ((g_ucDigitalSwitch & _BIT3) >> 3)
#define SET_DIGITAL_PORT_SWITCH_TO_D2()                     (g_ucDigitalSwitch |= _BIT3)
#define CLR_DIGITAL_PORT_SWITCH_TO_D2()                     (g_ucDigitalSwitch &= ~_BIT3)

#define GET_DIGITAL_PORT_SWITCH_TO_D3()                     ((g_ucDigitalSwitch & _BIT2) >> 2)
#define SET_DIGITAL_PORT_SWITCH_TO_D3()                     (g_ucDigitalSwitch |= _BIT2)
#define CLR_DIGITAL_PORT_SWITCH_TO_D3()                     (g_ucDigitalSwitch &= ~_BIT2)

#define GET_DIGITAL_PORT_SWITCH_TO_D4()                     ((g_ucDigitalSwitch & _BIT1) >> 1)
#define SET_DIGITAL_PORT_SWITCH_TO_D4()                     (g_ucDigitalSwitch |= _BIT1)
#define CLR_DIGITAL_PORT_SWITCH_TO_D4()                     (g_ucDigitalSwitch &= ~_BIT1)

#define GET_DIGITAL_PORT_SWITCH_TO_D5()                     ((g_ucDigitalSwitch & _BIT0) >> 0)
#define SET_DIGITAL_PORT_SWITCH_TO_D5()                     (g_ucDigitalSwitch |= _BIT0)
#define CLR_DIGITAL_PORT_SWITCH_TO_D5()                     (g_ucDigitalSwitch &= ~_BIT0)

#define GET_DIGITAL_PORT_SWITCH_TO_D6()                     ((g_ucDigitalSwitch & _BIT6) >> 0)
#define SET_DIGITAL_PORT_SWITCH_TO_D6()                     (g_ucDigitalSwitch |= _BIT6)
#define CLR_DIGITAL_PORT_SWITCH_TO_D6()                     (g_ucDigitalSwitch &= ~_BIT6)

#define GET_DP_DC_OFF_HPD_HIGH()                            (g_bDpDCOffHPDHigh)
#define SET_DP_DC_OFF_HPD_HIGH()                            (g_bDpDCOffHPDHigh = _TRUE)
#define CLR_DP_DC_OFF_HPD_HIGH()                            (g_bDpDCOffHPDHigh = _FALSE)

#define GET_HDMI_HOTPLUG_TOGGLE()                           ((g_ucHDMIHotPlug & _BIT7) >> 7)
#define SET_HDMI_HOTPLUG_TOGGLE()                           (g_ucHDMIHotPlug |= _BIT7)
#define CLR_HDMI_HOTPLUG_TOGGLE()                           (g_ucHDMIHotPlug &= ~_BIT7)

#define GET_HDMI_HOTPLUG_TIME()                             ((WORD)(g_ucHDMIHotPlug & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) * 100)
#define SET_HDMI_HOTPLUG_TIME(x)                            (g_ucHDMIHotPlug = (g_ucHDMIHotPlug & ~(_BIT3 | _BIT2 | _BIT1 | _BIT0)) | (x))

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of Rx Mst Capability Switch
//--------------------------------------------------
#define GET_DP_RX_D0_PORT_TARGET_VERSION()                  (g_stDpCapSwitch.ucD0Version)
#define SET_DP_RX_D0_PORT_TARGET_VERSION(x)                 (g_stDpCapSwitch.ucD0Version = (x))

#define GET_DP_RX_D1_PORT_TARGET_VERSION()                  (g_stDpCapSwitch.ucD1Version)
#define SET_DP_RX_D1_PORT_TARGET_VERSION(x)                 (g_stDpCapSwitch.ucD1Version = (x))

#define GET_DP_RX_D6_PORT_TARGET_VERSION()                  (g_stDpCapSwitch.ucD6Version)
#define SET_DP_RX_D6_PORT_TARGET_VERSION(x)                 (g_stDpCapSwitch.ucD6Version = (x))

#define GET_DP_RX_D0_PORT_TARGET_LANE_COUNT()               (g_stDpCapSwitch.ucD0LaneCount)
#define SET_DP_RX_D0_PORT_TARGET_LANE_COUNT(x)              (g_stDpCapSwitch.ucD0LaneCount = (x))

#define GET_DP_RX_D1_PORT_TARGET_LANE_COUNT()               (g_stDpCapSwitch.ucD1LaneCount)
#define SET_DP_RX_D1_PORT_TARGET_LANE_COUNT(x)              (g_stDpCapSwitch.ucD1LaneCount = (x))

#define GET_DP_RX_D6_PORT_TARGET_LANE_COUNT()               (g_stDpCapSwitch.ucD6LaneCount)
#define SET_DP_RX_D6_PORT_TARGET_LANE_COUNT(x)              (g_stDpCapSwitch.ucD6LaneCount = (x))

#define GET_DP_RX_D0_EDID_SWITCH()                          (g_stDpCapSwitch.b1D0Edid)
#define SET_DP_RX_D0_EDID_SWITCH()                          (g_stDpCapSwitch.b1D0Edid = _TRUE)
#define CLR_DP_RX_D0_EDID_SWITCH()                          (g_stDpCapSwitch.b1D0Edid = _FALSE)

#define GET_DP_RX_D1_EDID_SWITCH()                          (g_stDpCapSwitch.b1D1Edid)
#define SET_DP_RX_D1_EDID_SWITCH()                          (g_stDpCapSwitch.b1D1Edid = _TRUE)
#define CLR_DP_RX_D1_EDID_SWITCH()                          (g_stDpCapSwitch.b1D1Edid = _FALSE)

#define GET_DP_RX_D6_EDID_SWITCH()                          (g_stDpCapSwitch.b1D6Edid)
#define SET_DP_RX_D6_EDID_SWITCH()                          (g_stDpCapSwitch.b1D6Edid = _TRUE)
#define CLR_DP_RX_D6_EDID_SWITCH()                          (g_stDpCapSwitch.b1D6Edid = _FALSE)

#define GET_DP_RX_D7_EDID_SWITCH()                          (g_stDpCapSwitch.b1D7Edid)
#define SET_DP_RX_D7_EDID_SWITCH()                          (g_stDpCapSwitch.b1D7Edid = _TRUE)
#define CLR_DP_RX_D7_EDID_SWITCH()                          (g_stDpCapSwitch.b1D7Edid = _FALSE)

#define GET_DP_RX_TARGET_MST_PORT()                         (g_stDpCapSwitch.b2MSTPort)
#define SET_DP_RX_TARGET_MST_PORT(x)                        (g_stDpCapSwitch.b2MSTPort = (x))

#define GET_DP_RX_CAPABILITY_SWITCHED()                     (g_stDpCapSwitch.b1MsgSwitched)
#define SET_DP_RX_CAPABILITY_SWITCHED()                     (g_stDpCapSwitch.b1MsgSwitched = _TRUE)
#define CLR_DP_RX_CAPABILITY_SWITCHED()                     (g_stDpCapSwitch.b1MsgSwitched = _FALSE)

//--------------------------------------------------
// Definitions of DP Marginal Link
//--------------------------------------------------
#define GET_DP_RX_D0_MARGIN_LINK_HBR_RBR()                  (g_stDpMarginLink.b1D0MarginLinkHBRRBR)
#define SET_DP_RX_D0_MARGIN_LINK_HBR_RBR()                  (g_stDpMarginLink.b1D0MarginLinkHBRRBR = _TRUE)
#define CLR_DP_RX_D0_MARGIN_LINK_HBR_RBR()                  (g_stDpMarginLink.b1D0MarginLinkHBRRBR = _FALSE)

#define GET_DP_RX_D0_LANE0_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D0Lane0MarginLinkHBRRBR)
#define SET_DP_RX_D0_LANE0_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D0Lane0MarginLinkHBRRBR = _TRUE)
#define CLR_DP_RX_D0_LANE0_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D0Lane0MarginLinkHBRRBR = _FALSE)

#define GET_DP_RX_D0_LANE1_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D0Lane1MarginLinkHBRRBR)
#define SET_DP_RX_D0_LANE1_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D0Lane1MarginLinkHBRRBR = _TRUE)
#define CLR_DP_RX_D0_LANE1_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D0Lane1MarginLinkHBRRBR = _FALSE)

#define GET_DP_RX_D0_LANE2_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D0Lane2MarginLinkHBRRBR)
#define SET_DP_RX_D0_LANE2_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D0Lane2MarginLinkHBRRBR = _TRUE)
#define CLR_DP_RX_D0_LANE2_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D0Lane2MarginLinkHBRRBR = _FALSE)

#define GET_DP_RX_D0_LANE3_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D0Lane3MarginLinkHBRRBR)
#define SET_DP_RX_D0_LANE3_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D0Lane3MarginLinkHBRRBR = _TRUE)
#define CLR_DP_RX_D0_LANE3_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D0Lane3MarginLinkHBRRBR = _FALSE)

#define GET_DP_RX_D1_MARGIN_LINK_HBR_RBR()                  (g_stDpMarginLink.b1D1MarginLinkHBRRBR)
#define SET_DP_RX_D1_MARGIN_LINK_HBR_RBR()                  (g_stDpMarginLink.b1D1MarginLinkHBRRBR = _TRUE)
#define CLR_DP_RX_D1_MARGIN_LINK_HBR_RBR()                  (g_stDpMarginLink.b1D1MarginLinkHBRRBR = _FALSE)

#define GET_DP_RX_D1_LANE0_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D1Lane0MarginLinkHBRRBR)
#define SET_DP_RX_D1_LANE0_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D1Lane0MarginLinkHBRRBR = _TRUE)
#define CLR_DP_RX_D1_LANE0_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D1Lane0MarginLinkHBRRBR = _FALSE)

#define GET_DP_RX_D1_LANE1_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D1Lane1MarginLinkHBRRBR)
#define SET_DP_RX_D1_LANE1_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D1Lane1MarginLinkHBRRBR = _TRUE)
#define CLR_DP_RX_D1_LANE1_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D1Lane1MarginLinkHBRRBR = _FALSE)

#define GET_DP_RX_D1_LANE2_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D1Lane2MarginLinkHBRRBR)
#define SET_DP_RX_D1_LANE2_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D1Lane2MarginLinkHBRRBR = _TRUE)
#define CLR_DP_RX_D1_LANE2_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D1Lane2MarginLinkHBRRBR = _FALSE)

#define GET_DP_RX_D1_LANE3_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D1Lane3MarginLinkHBRRBR)
#define SET_DP_RX_D1_LANE3_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D1Lane3MarginLinkHBRRBR = _TRUE)
#define CLR_DP_RX_D1_LANE3_MARGIN_LINK_HBR_RBR()            (g_stDpMarginLink.b1D1Lane3MarginLinkHBRRBR = _FALSE)

#define GET_DP_RX_D6_MARGIN_LINK_HBR_RBR()                  (g_stDpMarginLink.b1D6MarginLinkHBRRBR)
#define SET_DP_RX_D6_MARGIN_LINK_HBR_RBR()                  (g_stDpMarginLink.b1D6MarginLinkHBRRBR = _TRUE)
#define CLR_DP_RX_D6_MARGIN_LINK_HBR_RBR()                  (g_stDpMarginLink.b1D6MarginLinkHBRRBR = _FALSE)
#endif

#if(_DP_TX_SUPPORT == _ON)
#define GET_DP_RX_HDCP_UPSTREAM_PORT()                      (g_stDpTxStatus.b2HdcpUpstreamPort)
#define SET_DP_RX_HDCP_UPSTREAM_PORT(x)                     (g_stDpTxStatus.b2HdcpUpstreamPort = (x))
#endif

#if(_FREESYNC_SUPPORT == _ON)
#if((_DP_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
#define GET_FREESYNC_ENABLED()                              ((bit)(GET_DP_FREESYNC_ENABLED() | GET_HDMI_FREESYNC_ENABLED()))
#define CLR_FREESYNC_ENABLED()                              {\
                                                                CLR_DP_FREESYNC_ENABLED();\
                                                                CLR_HDMI_FREESYNC_ENABLED();\
                                                            }
#elif(_DP_FREESYNC_SUPPORT == _ON)
#define GET_FREESYNC_ENABLED()                              (GET_DP_FREESYNC_ENABLED())
#define CLR_FREESYNC_ENABLED()                              {\
                                                                CLR_DP_FREESYNC_ENABLED();\
                                                            }
#else
#define GET_FREESYNC_ENABLED()                              (GET_HDMI_FREESYNC_ENABLED())
#define CLR_FREESYNC_ENABLED()                              {\
                                                                CLR_HDMI_FREESYNC_ENABLED();\
                                                            }
#endif

#define GET_FREESYNC_SUPPORT()                              (g_ucFREESYNCSupport)
#define SET_FREESYNC_SUPPORT(x)                             (g_ucFREESYNCSupport = (bit)(x))

#if(_DP_FREESYNC_SUPPORT == _ON)
#define GET_DP_FREESYNC_ENABLED()                           (g_stDpFREESYNCInfo.b1DPFREESYNCEnable)
#define SET_DP_FREESYNC_ENABLED()                           (g_stDpFREESYNCInfo.b1DPFREESYNCEnable = _ENABLE)
#define CLR_DP_FREESYNC_ENABLED()                           (g_stDpFREESYNCInfo.b1DPFREESYNCEnable = _DISABLE)

#define GET_DP_RX0_FREESYNC_SUPPORT()                       (g_stDpFREESYNCInfo.b1DPRX0FREESYNCSupport)
#define SET_DP_RX0_FREESYNC_SUPPORT(x)                      (g_stDpFREESYNCInfo.b1DPRX0FREESYNCSupport = (x))
#define CLR_DP_RX0_FREESYNC_SUPPORT()                       (g_stDpFREESYNCInfo.b1DPRX0FREESYNCSupport = _FALSE)

#define GET_DP_RX1_FREESYNC_SUPPORT()                       (g_stDpFREESYNCInfo.b1DPRX1FREESYNCSupport)
#define SET_DP_RX1_FREESYNC_SUPPORT(x)                      (g_stDpFREESYNCInfo.b1DPRX1FREESYNCSupport = (x))
#define CLR_DP_RX1_FREESYNC_SUPPORT()                       (g_stDpFREESYNCInfo.b1DPRX1FREESYNCSupport = _FALSE)

#define GET_DP_RX0_FREESYNC_CAPABILITY_SWITCH()             (g_stDpFREESYNCInfo.b1DPRX0FREESYNCCapabilitySwitch)
#define SET_DP_RX0_FREESYNC_CAPABILITY_SWITCH()             (g_stDpFREESYNCInfo.b1DPRX0FREESYNCCapabilitySwitch = _TRUE)
#define CLR_DP_RX0_FREESYNC_CAPABILITY_SWITCH()             (g_stDpFREESYNCInfo.b1DPRX0FREESYNCCapabilitySwitch = _FALSE)

#define GET_DP_RX1_FREESYNC_CAPABILITY_SWITCH()             (g_stDpFREESYNCInfo.b1DPRX1FREESYNCCapabilitySwitch)
#define SET_DP_RX1_FREESYNC_CAPABILITY_SWITCH()             (g_stDpFREESYNCInfo.b1DPRX1FREESYNCCapabilitySwitch = _TRUE)
#define CLR_DP_RX1_FREESYNC_CAPABILITY_SWITCH()             (g_stDpFREESYNCInfo.b1DPRX1FREESYNCCapabilitySwitch = _FALSE)

#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
#define GET_DP_MST_FREESYNC_ENABLED()                       (g_stDpFREESYNCInfo.b1DPMSTFREESYNCEnable)
#define SET_DP_MST_FREESYNC_ENABLED()                       (g_stDpFREESYNCInfo.b1DPMSTFREESYNCEnable = _ENABLE)
#define CLR_DP_MST_FREESYNC_ENABLED()                       (g_stDpFREESYNCInfo.b1DPMSTFREESYNCEnable = _DISABLE)
#endif // End of #if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
#endif

#if(_HDMI_FREESYNC_SUPPORT == _ON)
#define GET_HDMI_FREESYNC_ENABLED()                         (g_stHDMIFREESYNCInfo.b1HDMIFREESYNCEnable)
#define SET_HDMI_FREESYNC_ENABLED()                         (g_stHDMIFREESYNCInfo.b1HDMIFREESYNCEnable = _ENABLE)
#define CLR_HDMI_FREESYNC_ENABLED()                         (g_stHDMIFREESYNCInfo.b1HDMIFREESYNCEnable = _DISABLE)

#if(_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE)
#define GET_HDMI_FREESYNC_VCP()                             (g_ucHDMIFREESYNCVCPReceive)
#endif

#define GET_TMDS_RX0_SPD_INFO_FRAME_RECEIVED()              (g_stHDMIFREESYNCInfo.b1HDMIRX0SPDInfoFrameReceived)
#define SET_TMDS_RX0_SPD_INFO_FRAME_RECEIVED()              (g_stHDMIFREESYNCInfo.b1HDMIRX0SPDInfoFrameReceived = _TRUE)
#define CLR_TMDS_RX0_SPD_INFO_FRAME_RECEIVED()              (g_stHDMIFREESYNCInfo.b1HDMIRX0SPDInfoFrameReceived = _FALSE)

#define GET_TMDS_RX1_SPD_INFO_FRAME_RECEIVED()              (g_stHDMIFREESYNCInfo.b1HDMIRX1SPDInfoFrameReceived)
#define SET_TMDS_RX1_SPD_INFO_FRAME_RECEIVED()              (g_stHDMIFREESYNCInfo.b1HDMIRX1SPDInfoFrameReceived = _TRUE)
#define CLR_TMDS_RX1_SPD_INFO_FRAME_RECEIVED()              (g_stHDMIFREESYNCInfo.b1HDMIRX1SPDInfoFrameReceived = _FALSE)

#define GET_TMDS_RX2_SPD_INFO_FRAME_RECEIVED()              (g_stHDMIFREESYNCInfo.b1HDMIRX2SPDInfoFrameReceived)
#define SET_TMDS_RX2_SPD_INFO_FRAME_RECEIVED()              (g_stHDMIFREESYNCInfo.b1HDMIRX2SPDInfoFrameReceived = _TRUE)
#define CLR_TMDS_RX2_SPD_INFO_FRAME_RECEIVED()              (g_stHDMIFREESYNCInfo.b1HDMIRX2SPDInfoFrameReceived = _FALSE)

#define GET_TMDS_RX3_SPD_INFO_FRAME_RECEIVED()              (g_stHDMIFREESYNCInfo.b1HDMIRX3SPDInfoFrameReceived)
#define SET_TMDS_RX3_SPD_INFO_FRAME_RECEIVED()              (g_stHDMIFREESYNCInfo.b1HDMIRX3SPDInfoFrameReceived = _TRUE)
#define CLR_TMDS_RX3_SPD_INFO_FRAME_RECEIVED()              (g_stHDMIFREESYNCInfo.b1HDMIRX3SPDInfoFrameReceived = _FALSE)

#define GET_TMDS_RX4_SPD_INFO_FRAME_RECEIVED()              (g_stHDMIFREESYNCInfo.b1HDMIRX4SPDInfoFrameReceived)
#define SET_TMDS_RX4_SPD_INFO_FRAME_RECEIVED()              (g_stHDMIFREESYNCInfo.b1HDMIRX4SPDInfoFrameReceived = _TRUE)
#define CLR_TMDS_RX4_SPD_INFO_FRAME_RECEIVED()              (g_stHDMIFREESYNCInfo.b1HDMIRX4SPDInfoFrameReceived = _FALSE)

#define GET_TMDS_RX5_SPD_INFO_FRAME_RECEIVED()              (g_stHDMIFREESYNCInfo.b1HDMIRX5SPDInfoFrameReceived)
#define SET_TMDS_RX5_SPD_INFO_FRAME_RECEIVED()              (g_stHDMIFREESYNCInfo.b1HDMIRX5SPDInfoFrameReceived = _TRUE)
#define CLR_TMDS_RX5_SPD_INFO_FRAME_RECEIVED()              (g_stHDMIFREESYNCInfo.b1HDMIRX5SPDInfoFrameReceived = _FALSE)

#define GET_TMDS_RX0_FREESYNC_SUPPORT()                     (g_stHDMIFREESYNCInfo.b1HDMIRX0FREESYNCSupport)
#define SET_TMDS_RX0_FREESYNC_SUPPORT(x)                    (g_stHDMIFREESYNCInfo.b1HDMIRX0FREESYNCSupport = (x))
#define CLR_TMDS_RX0_FREESYNC_SUPPORT()                     (g_stHDMIFREESYNCInfo.b1HDMIRX0FREESYNCSupport = _FALSE)

#define GET_TMDS_RX1_FREESYNC_SUPPORT()                     (g_stHDMIFREESYNCInfo.b1HDMIRX1FREESYNCSupport)
#define SET_TMDS_RX1_FREESYNC_SUPPORT(x)                    (g_stHDMIFREESYNCInfo.b1HDMIRX1FREESYNCSupport = (x))
#define CLR_TMDS_RX1_FREESYNC_SUPPORT()                     (g_stHDMIFREESYNCInfo.b1HDMIRX1FREESYNCSupport = _FALSE)

#define GET_TMDS_RX2_FREESYNC_SUPPORT()                     (g_stHDMIFREESYNCInfo.b1HDMIRX2FREESYNCSupport)
#define SET_TMDS_RX2_FREESYNC_SUPPORT(x)                    (g_stHDMIFREESYNCInfo.b1HDMIRX2FREESYNCSupport = (x))
#define CLR_TMDS_RX2_FREESYNC_SUPPORT()                     (g_stHDMIFREESYNCInfo.b1HDMIRX2FREESYNCSupport = _FALSE)

#define GET_TMDS_RX3_FREESYNC_SUPPORT()                     (g_stHDMIFREESYNCInfo.b1HDMIRX3FREESYNCSupport)
#define SET_TMDS_RX3_FREESYNC_SUPPORT(x)                    (g_stHDMIFREESYNCInfo.b1HDMIRX3FREESYNCSupport = (x))
#define CLR_TMDS_RX3_FREESYNC_SUPPORT()                     (g_stHDMIFREESYNCInfo.b1HDMIRX3FREESYNCSupport = _FALSE)

#define GET_TMDS_RX4_FREESYNC_SUPPORT()                     (g_stHDMIFREESYNCInfo.b1HDMIRX4FREESYNCSupport)
#define SET_TMDS_RX4_FREESYNC_SUPPORT(x)                    (g_stHDMIFREESYNCInfo.b1HDMIRX4FREESYNCSupport = (x))
#define CLR_TMDS_RX4_FREESYNC_SUPPORT()                     (g_stHDMIFREESYNCInfo.b1HDMIRX4FREESYNCSupport = _FALSE)

#define GET_TMDS_RX5_FREESYNC_SUPPORT()                     (g_stHDMIFREESYNCInfo.b1HDMIRX5FREESYNCSupport)
#define SET_TMDS_RX5_FREESYNC_SUPPORT(x)                    (g_stHDMIFREESYNCInfo.b1HDMIRX5FREESYNCSupport = (x))
#define CLR_TMDS_RX5_FREESYNC_SUPPORT()                     (g_stHDMIFREESYNCInfo.b1HDMIRX5FREESYNCSupport = _FALSE)
#endif

#endif // End of #if(_FREESYNC_SUPPORT == _ON)

#define GET_DIGITAL_COLOR_INFO_CHANGE_RESET()               (g_bDigitalColorInfoChangeReset)
#define SET_DIGITAL_COLOR_INFO_CHANGE_RESET()               (g_bDigitalColorInfoChangeReset = _TRUE)
#define CLR_DIGITAL_COLOR_INFO_CHANGE_RESET()               (g_bDigitalColorInfoChangeReset = _FALSE)

#define GET_DIGITAL_COLORIMETRY_CHANGED(port)               (g_pstDigitalColorInfoChanged[port].b1DigitalColorimetryChanged)
#define SET_DIGITAL_COLORIMETRY_CHANGED(port)               (g_pstDigitalColorInfoChanged[port].b1DigitalColorimetryChanged = _TRUE)
#define CLR_DIGITAL_COLORIMETRY_CHANGED(port)               (g_pstDigitalColorInfoChanged[port].b1DigitalColorimetryChanged = _FALSE)

#define GET_DIGITAL_COLORIMETRY_EXT_CHANGED(port)           (g_pstDigitalColorInfoChanged[port].b1DigitalColorimetryExtChanged)
#define SET_DIGITAL_COLORIMETRY_EXT_CHANGED(port)           (g_pstDigitalColorInfoChanged[port].b1DigitalColorimetryExtChanged = _TRUE)
#define CLR_DIGITAL_COLORIMETRY_EXT_CHANGED(port)           (g_pstDigitalColorInfoChanged[port].b1DigitalColorimetryExtChanged = _FALSE)

#define GET_DIGITAL_QUANTIZATION_CHANGED(port)              (g_pstDigitalColorInfoChanged[port].b1DigitalQuantizationChanged)
#define SET_DIGITAL_QUANTIZATION_CHANGED(port)              (g_pstDigitalColorInfoChanged[port].b1DigitalQuantizationChanged = _TRUE)
#define CLR_DIGITAL_QUANTIZATION_CHANGED(port)              (g_pstDigitalColorInfoChanged[port].b1DigitalQuantizationChanged = _FALSE)

#endif // End of #if(_DIGITAL_PORT_SUPPORT == _ON)

#if(_URGENT_EVENT_CHECK_MODE == _ON)
#define GET_URGENT_EVENT_OCCUR_FLG()                        (g_ucCheckUrgentEventOccured)
#define SET_URGENT_EVENT_OCCUR_FLG()                        (g_ucCheckUrgentEventOccured = _TRUE)
#define CLR_URGENT_EVENT_OCCUR_FLG()                        (g_ucCheckUrgentEventOccured = _FALSE)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_DIGITAL_PORT_SUPPORT == _ON)
#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
//--------------------------------------------------
// Structure of TMDS Control Definitions
//--------------------------------------------------
typedef struct
{
    BYTE b1RGBHVDetecting : 1;
    BYTE b1PacketDetecting : 1;
    BYTE b1AVIInfoFrameReceived : 1;
    BYTE b1GCPReceived : 1;
    BYTE b1Z0Asserted : 1;
    BYTE b1TMDSDdcDetected : 1;
    BYTE b1TMDSPhySet : 1;

#if(_HDMI_2_0_SUPPORT == _ON)
    BYTE b1HDMI2FormatResetWaiting : 1;
    BYTE b1HDMI2RREnable : 1;
    BYTE b1HDMI2HighSpeedMode : 1;
#endif

#if(_ULTRA_HDR_SUPPORT == _ON)
    BYTE b1HDRInfoFrameReceived : 1;
#endif

    BYTE b3HPDTriggerEvent : 3;
} StructTMDSCtrlInfo;
#endif // End of #if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))

//--------------------------------------------------
// Definitions for DP Capability Switch
//--------------------------------------------------
typedef struct
{
    BYTE ucD0Version;
    BYTE ucD1Version;
    BYTE ucD6Version;
    BYTE ucD0LaneCount;
    BYTE ucD1LaneCount;
    BYTE ucD6LaneCount;
    BYTE b1D0Edid : 1;
    BYTE b1D1Edid : 1;
    BYTE b1D6Edid : 1;
    BYTE b1D7Edid : 1;
    BYTE b2MSTPort : 2;
    BYTE b1MsgSwitched : 1;
}StructDPCapSwitchInfo;

//--------------------------------------------------
// Definitions for DP Tx
//--------------------------------------------------
typedef struct
{
    BYTE b2HdcpUpstreamPort : 2;
} StructDPTxStatusInfo;

#if(_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of AVI Info Content Types
//--------------------------------------------------
typedef enum
{
    _AVI_COLOR_SPACE_00 = _AVI_COLOR_SPACE_RGB,
    _AVI_COLOR_SPACE_01 = _AVI_COLOR_SPACE_YCC_422,
    _AVI_COLOR_SPACE_10 = _AVI_COLOR_SPACE_YCC_444,
    _AVI_COLOR_SPACE_11 = _AVI_COLOR_SPACE_YCC_420,
    _AVI_COLOR_SPACE_KERNEL_RESERVED = 0x04,
} EnumAviInfoColorSpaceKernel;

typedef enum
{
    _AVI_COLORIMETRY_00 = _AVI_COLORIMETRY_NONE,
    _AVI_COLORIMETRY_01 = _AVI_COLORIMETRY_ITU601,
    _AVI_COLORIMETRY_10 = _AVI_COLORIMETRY_ITU709,
    _AVI_COLORIMETRY_11 = 0x03,
} EnumAviInfoColorimetryKernel;

typedef enum
{
    _AVI_COLORIMETRY_EXT_000 = _AVI_COLORIMETRY_EXT_XVYCC601,
    _AVI_COLORIMETRY_EXT_001 = _AVI_COLORIMETRY_EXT_XVYCC709,
    _AVI_COLORIMETRY_EXT_010 = _AVI_COLORIMETRY_EXT_SYCC601,
    _AVI_COLORIMETRY_EXT_011 = _AVI_COLORIMETRY_EXT_ADOBEYCC601,
    _AVI_COLORIMETRY_EXT_100 = _AVI_COLORIMETRY_EXT_ADOBERGB,
    _AVI_COLORIMETRY_EXT_101 = _AVI_COLORIMETRY_EXT_ITUR_BT2020_1,
    _AVI_COLORIMETRY_EXT_110 = _AVI_COLORIMETRY_EXT_ITUR_BT2020_2,
    _AVI_COLORIMETRY_EXT_111 = 0x07,
} EnumAviInfoColorimetryExtKernel;

#endif

//--------------------------------------------------
// Definitions of Digital Color Info Change
//--------------------------------------------------
typedef struct
{
    BYTE b1DigitalColorimetryChanged : 1;
    BYTE b1DigitalColorimetryExtChanged : 1;
    BYTE b1DigitalQuantizationChanged : 1;
} StructDigitalColorInfoChanged;

//--------------------------------------------------
// Definitions of Digital Color Info PreValue
//--------------------------------------------------
typedef struct
{
    BYTE ucDigitalColorSpacePreValue;
    BYTE b3DigitalColorDepthPreValue : 3;
    BYTE b4DigitalColorimetryPreValue : 4;
    BYTE b4DigitalColorimetryExtPreValue : 4;
    BYTE b2DigitalQuantizationPreValue : 2;
} StructDigitalColorInfo;

#if(_DP_SUPPORT == _ON)

//--------------------------------------------------
// Definitions of DP SDP Packet Type
//--------------------------------------------------
typedef enum
{
    _DP_SDP_TYPE_AUD_TIMESTAMP = 0x01,
    _DP_SDP_TYPE_AUD_STREAM,
    _DP_SDP_TYPE_EXTENSION = 0x04,
    _DP_SDP_TYPE_AUD_COPYMANAGEMENT,
    _DP_SDP_TYPE_ISRC,
    _DP_SDP_TYPE_VSC,
    _DP_SDP_TYPE_CAM_GEN_0,
    _DP_SDP_TYPE_CAM_GEN_1,
    _DP_SDP_TYPE_CAM_GEN_2,
    _DP_SDP_TYPE_CAM_GEN_3,
    _DP_SDP_TYPE_CAM_GEN_4,
    _DP_SDP_TYPE_CAM_GEN_5,
    _DP_SDP_TYPE_CAM_GEN_6,
    _DP_SDP_TYPE_CAM_GEN_7,
    _DP_SDP_TYPE_PPS,
    _DP_SDP_TYPE_VSC_EXT_VESA = 0x20,
    _DP_SDP_TYPE_VSC_EXT_CEA,
    _DP_SDP_TYPE_INFOFRAME_RSV = 0x80,
    _DP_SDP_TYPE_INFOFRAME_VENDOR_SPEC,
    _DP_SDP_TYPE_INFOFRAME_AUX_VID_INFO,
    _DP_SDP_TYPE_INFOFRAME_SRC_PROD_DESC,
    _DP_SDP_TYPE_INFOFRAME_AUDIO,
    _DP_SDP_TYPE_INFOFRAME_MPEG,
    _DP_SDP_TYPE_INFOFRAME_NTSC_VBI,
}EnumDpSdpType;

#if(_HW_DP_INFOFRAME_RSV1_LENGTH != 0)
//--------------------------------------------------
// Definitions for DP Infoframe RSV1 SRAM Address
//--------------------------------------------------
typedef enum
{
    _DP_INFO_RSV1_DB0 = 0x3D,
    _DP_INFO_RSV1_DB1,
    _DP_INFO_RSV1_DB2,
    _DP_INFO_RSV1_DB3,
    _DP_INFO_RSV1_DB4,
    _DP_INFO_RSV1_DB5,
    _DP_INFO_RSV1_DB6,
    _DP_INFO_RSV1_DB7,
    _DP_INFO_RSV1_DB8,
    _DP_INFO_RSV1_DB9,
    _DP_INFO_RSV1_DB10,
    _DP_INFO_RSV1_DB11,
    _DP_INFO_RSV1_DB12,
    _DP_INFO_RSV1_DB13,
    _DP_INFO_RSV1_DB14,
    _DP_INFO_RSV1_DB15,
    _DP_INFO_RSV1_DB16,
    _DP_INFO_RSV1_DB17,
    _DP_INFO_RSV1_DB18,
    _DP_INFO_RSV1_DB19,
    _DP_INFO_RSV1_DB20,
    _DP_INFO_RSV1_DB21,
    _DP_INFO_RSV1_DB22,
    _DP_INFO_RSV1_DB23,
    _DP_INFO_RSV1_DB24,
    _DP_INFO_RSV1_DB25,
    _DP_INFO_RSV1_DB26,
    _DP_INFO_RSV1_DB27,
#if(_HW_DP_INFOFRAME_RSV1_LENGTH == 32)
    _DP_INFO_RSV1_DB28,
    _DP_INFO_RSV1_DB29,
    _DP_INFO_RSV1_DB30,
    _DP_INFO_RSV1_DB31,
#endif
}EnumDpInfoFrameRsv1;
#endif

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of VSC Color Format Types
//--------------------------------------------------
typedef enum
{
    _VSC_COLOR_SPACE_0 = 0x00,
    _VSC_COLOR_SPACE_1 = 0x10,
    _VSC_COLOR_SPACE_2 = 0x20,
    _VSC_COLOR_SPACE_3 = 0x30,
    _VSC_COLOR_SPACE_4 = 0x40,
    _VSC_COLOR_SPACE_5 = 0x50,
} EnumVscColorSpace;

typedef enum
{
    _VSC_COLORIMETRY_0 = 0x00,
    _VSC_COLORIMETRY_1 = 0x01,
    _VSC_COLORIMETRY_2 = 0x02,
    _VSC_COLORIMETRY_3 = 0x03,
    _VSC_COLORIMETRY_4 = 0x04,
    _VSC_COLORIMETRY_5 = 0x05,
    _VSC_COLORIMETRY_6 = 0x06,
    _VSC_COLORIMETRY_7 = 0x07,
} EnumVscColorimetry;
#endif

//--------------------------------------------------
// Definitions of DP Color Quantization Types
//--------------------------------------------------
typedef enum
{
    _DP_COLOR_QUANTIZATION_FULL = 0x00,
    _DP_COLOR_QUANTIZATION_LIMIT = 0x01,
} EnumDPColorQuantization;
#endif // End of #if(_DP_SUPPORT == _ON)

//--------------------------------------------------
// Enumerations of DP Reset Status
//--------------------------------------------------
typedef enum
{
    _DP_DPCD_LINK_STATUS_INITIAL = 0x00,
    _DP_DPCD_LINK_STATUS_IRQ = 0x01,
} EnumDpResetStatus;

//--------------------------------------------------
// Enumerations of DP HDCP B Status Type
//--------------------------------------------------
typedef enum
{
    _DP_HDCP_BSTATUS_V_READY = _BIT0,
    _DP_HDCP_BSTATUS_R0_AVAILABLE = _BIT1,
    _DP_HDCP_BSTATUS_LINK_INTEGRITY_FAIL = _BIT2,
    _DP_HDCP_BSTATUS_REAUTH_REQ = _BIT3,
#if(_DP_HDCP_2_2_SUPPORT == _ON)
    _DP_HDCP2_H_PRIME_AVAILABLE = _BIT4,
    _DP_HDCP2_PARING_AVAILABLE = _BIT5,
#endif
} EnumDpRxBStatusType;

//--------------------------------------------------
// Enumerations of DP Link Clock Valid
//--------------------------------------------------
typedef enum
{
    _DP_LCLK_FAIL = 0x00,
    _DP_LCLK_DIVIDE_BY_1,
    _DP_LCLK_DIVIDE_BY_2,
} EnumDpRefLinkClock;

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Enumerations of HDCP Rx Port
//--------------------------------------------------
typedef enum
{
    _HDCP_NO_PORT,
    _HDCP_D0_PORT,
    _HDCP_D1_PORT,
} EnumDpHdcpUpstreamPort;

//--------------------------------------------------
// Definitions of DP Tx Color Info PreValue
//--------------------------------------------------
typedef struct
{
    BYTE ucColorSpacePreValue;
    BYTE b3ColorDepthPreValue : 3;
} StructDpTxColorInfo;

#endif

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Struct for RX Aux Ch Power Detect
//--------------------------------------------------
typedef struct
{
    BYTE b1DpCheckAuxChNoPowerDebounce : 1;
    BYTE b1DpAuxChPowerOnWakeUp : 1;
    BYTE b1DpCheckAuxChPowerOff : 1;
    BYTE b1DpSourceFirstPowerOn : 1;
    BYTE b1DpMstEnableBackup : 1;
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
    BYTE b1DpRx6MstEnableBackup : 1;
#endif
}StructDPRxMiscInfo;
#endif
#endif // End of #if(_DIGITAL_PORT_SUPPORT == _ON)

#if(_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Struct for DP FREESYNC Support
//--------------------------------------------------
typedef struct
{
    BYTE b1DPFREESYNCEnable : 1;
    BYTE b1DPMSTFREESYNCEnable : 1;
    BYTE b1DPRX0FREESYNCSupport : 1;
    BYTE b1DPRX1FREESYNCSupport : 1;
    BYTE b1DPRX0FREESYNCCapabilitySwitch : 1;
    BYTE b1DPRX1FREESYNCCapabilitySwitch : 1;
} StructDPFREESYNCENABLE;
#endif

//--------------------------------------------------
// Struct for HDMI FREESYNC Support
//--------------------------------------------------
typedef struct
{
    BYTE b1HDMIFREESYNCEnable : 1;
    BYTE b1HDMIRX0SPDInfoFrameReceived : 1;
    BYTE b1HDMIRX1SPDInfoFrameReceived : 1;
    BYTE b1HDMIRX2SPDInfoFrameReceived : 1;
    BYTE b1HDMIRX3SPDInfoFrameReceived : 1;
    BYTE b1HDMIRX4SPDInfoFrameReceived : 1;
    BYTE b1HDMIRX5SPDInfoFrameReceived : 1;

    BYTE b1HDMIRX0FREESYNCSupport : 1;
    BYTE b1HDMIRX1FREESYNCSupport : 1;
    BYTE b1HDMIRX2FREESYNCSupport : 1;
    BYTE b1HDMIRX3FREESYNCSupport : 1;
    BYTE b1HDMIRX4FREESYNCSupport : 1;
    BYTE b1HDMIRX5FREESYNCSupport : 1;
} StructHDMIFREESYNCENABLE;

typedef enum
{
    _DP_INFO_RSV0_DB0 = 0x21,
    _DP_INFO_RSV0_DB1 = 0x22,
    _DP_INFO_RSV0_DB2 = 0x23,
    _DP_INFO_RSV0_DB3 = 0x24,
    _DP_INFO_RSV0_DB4 = 0x25,
    _DP_INFO_RSV0_DB5 = 0x26,
    _DP_INFO_RSV0_DB6 = 0x27,
    _DP_INFO_RSV0_DB7 = 0x28,
    _DP_INFO_RSV0_DB8 = 0x29,
    _DP_INFO_RSV0_DB9 = 0x2A,
    _DP_INFO_RSV0_DB10 = 0x2B,
    _DP_INFO_RSV0_DB11 = 0x2C,
    _DP_INFO_RSV0_DB12 = 0x2D,
    _DP_INFO_RSV0_DB13 = 0x2E,
    _DP_INFO_RSV0_DB14 = 0x2F,
    _DP_INFO_RSV0_DB15 = 0x30,
    _DP_INFO_RSV0_DB16 = 0x31,
    _DP_INFO_RSV0_DB17 = 0x32,
    _DP_INFO_RSV0_DB18 = 0x33,
    _DP_INFO_RSV0_DB19 = 0x34,
    _DP_INFO_RSV0_DB20 = 0x35,
    _DP_INFO_RSV0_DB21 = 0x36,
    _DP_INFO_RSV0_DB22 = 0x37,
    _DP_INFO_RSV0_DB23 = 0x38,
    _DP_INFO_RSV0_DB24 = 0x39,
    _DP_INFO_RSV0_DB25 = 0x3A,
    _DP_INFO_RSV0_DB26 = 0x3B,
    _DP_INFO_RSV0_DB27 = 0x3C,
}EnumDPInfoFrameRSV0;

#if(_ULTRA_HDR_SUPPORT == _ON)
//--------------------------------------------------
// Enum for HDR
//--------------------------------------------------
typedef enum
{
    _HDR_INFO_HDMI_VERSION = 0xAC,
    _HDR_INFO_HDMI_LENGTH = 0xAD,
    _HDR_INFO_HDMI_CHECKSUM = 0xAE,

    // A:chg_
    _HDR_INFO_HDMI_EOTF = 0xAF,

    // B_
    _HDR_INFO_HDMI_STATIC_METADATA_DESCRIPTOR_ID = 0xB0,

    // C:chg
    _HDR_INFO_HDMI_DISPLAY_PRIMARIES_X0_LSB = 0xB1,

    _HDR_INFO_HDMI_DISPLAY_PRIMARIES_Y0_LSB = 0xB3,

    _HDR_INFO_HDMI_DISPLAY_PRIMARIES_X1_LSB = 0xB5,

    _HDR_INFO_HDMI_DISPLAY_PRIMARIES_Y1_LSB = 0xB7,

    _HDR_INFO_HDMI_DISPLAY_PRIMARIES_X2_LSB = 0xB9,

    _HDR_INFO_HDMI_DISPLAY_PRIMARIES_Y2_LSB = 0xBB,

    _HDR_INFO_HDMI_WHITE_POINT_X_LSB = 0xBD,

    _HDR_INFO_HDMI_WHITE_POINT_Y_LSB = 0xBF,

    // D:chg
    _HDR_INFO_HDMI_MAX_LUMINANCE_LSB = 0xC1,

    // E
    _HDR_INFO_HDMI_MIN_LUMINANCE_LSB = 0xC3,

    // F
    _HDR_INFO_HDMI_MAX_CLL_LSB = 0xC5,

    // G
    _HDR_INFO_HDMI_MAX_FALL_LSB = 0xC7,
}EnumHdrMasteringInfoFrameTMDSRSV3;

typedef struct
{
    BYTE b1RSV0PacketDetecting : 1;
    BYTE b1HDRInfoFrameReceive : 1;
    BYTE b1FreesyncInfoFrameReceive : 1;
    BYTE b1AudioInfoFrameReceive : 1;
} StructDPInfoFrameRSV0Ctrl;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern BYTE data pData_EXINT[6];

#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
extern WORD g_usA0PixelClk;
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
extern WORD g_usD0PixelClk;

#if(_D0_TMDS_SUPPORT == _ON)
extern WORD g_usTmdsD0OffLineMeasureClk;
#endif
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
extern WORD g_usD1PixelClk;

#if(_D1_TMDS_SUPPORT == _ON)
extern WORD g_usTmdsD1OffLineMeasureClk;
#endif
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
extern WORD g_usD2PixelClk;
extern WORD g_usTmdsD2OffLineMeasureClk;
#endif

#if((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
extern WORD g_usD3PixelClk;
extern WORD g_usTmdsD3OffLineMeasureClk;
#endif

#if((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
extern WORD g_usD4PixelClk;
extern WORD g_usTmdsD4OffLineMeasureClk;
#endif

#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
extern WORD g_usD5PixelClk;
extern WORD g_usTmdsD5OffLineMeasureClk;
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
extern BYTE idata g_pucHdcpBksvBackup[5];
extern BYTE g_ucDigitalSwitch;
extern bit g_bDpDCOffHPDHigh;
extern BYTE g_ucHDMIHotPlug;

extern bit g_bDigitalColorInfoChangeReset;
extern StructDigitalColorInfo g_pstDigitalColorInfo[];
extern StructDigitalColorInfoChanged g_pstDigitalColorInfoChanged[];
#endif

#if(_DP_SUPPORT == _ON)
extern StructDPCapSwitchInfo g_stDpCapSwitch;
extern StructDPMarginLinkInfo g_stDpMarginLink;
#endif

#if(_DP_TX_SUPPORT == _ON)
extern StructDPTxStatusInfo g_stDpTxStatus;
extern StructDpTxColorInfo g_stDpTxColorInfo;
#endif

#if(_FREESYNC_SUPPORT == _ON)
#if(_DP_FREESYNC_SUPPORT == _ON)
extern StructDPFREESYNCENABLE g_stDpFREESYNCInfo;
#endif

#if(_HDMI_FREESYNC_SUPPORT == _ON)
extern StructHDMIFREESYNCENABLE g_stHDMIFREESYNCInfo;

#if(_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE)
extern BYTE g_ucHDMIFREESYNCVCPReceive;
#endif
#endif

extern BYTE g_ucFREESYNCSupport;
extern WORD g_usFREESYNCVFreq;
#endif

#if(_DP_TX_SUPPORT == _ON)
extern BYTE idata g_pucHdcpAksvBackup[5];
#endif

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
extern WORD g_usDDCDebounceCnt;
#endif

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
extern bit g_bTMDSRx0Z0Toggle;
extern bit g_bTMDSRx1Z0Toggle;
extern bit g_bTMDSRx2Z0Toggle;
extern bit g_bTMDSRx3Z0Toggle;
extern bit g_bTMDSRx4Z0Toggle;
extern bit g_bTMDSRx5Z0Toggle;
extern bit g_bTMDSRx0GlobalZ0Toggle;
extern bit g_bTMDSRx1GlobalZ0Toggle;
extern bit g_bTMDSRx2GlobalZ0Toggle;
extern bit g_bTMDSRx3GlobalZ0Toggle;
extern bit g_bTMDSRx4GlobalZ0Toggle;
extern bit g_bTMDSRx5GlobalZ0Toggle;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

#if(_DP_SUPPORT == _ON)
extern void ScalerSyncDpLowPowerProc(void);
#endif

#if(_DP_TX_SUPPORT == _ON)
extern void ScalerSyncDpTxPowerProc(EnumPowerAction enumPowerAction);
EnumDPRxHDCPUpstreamAuthStatus ScalerSyncDpHdcpGetUpstreamEvent(void);
bit ScalerSyncDpHdcpGetUpstreamEncryptStatus(void);
#endif

#if(_URGENT_EVENT_CHECK_MODE == _ON)
extern bit ScalerSyncCheckUrgentEvent(void);
#endif

#if(_DUAL_DVI_SUPPORT == _ON)
extern bit ScalerSyncGetDualDVIMode(EnumSourceSearchPort enumInputPort);
extern bit ScalerSyncDualDVIDoubleCheck(EnumSourceSearchPort enumSourceSearchPort, WORD usHwidth, WORD usVHeight);
extern void ScalerSyncDualDVIClockInvert(EnumSourceSearchPort enumSourceSearchPort);
#endif

#if(_MHL_SUPPORT == _ON)
extern bit ScalerSyncMHLVBusPowerExist(void);
#endif

extern void ScalerSyncResetProc(BYTE ucInputPort);
extern void ScalerSyncResetAllProc(void);

#if(_D0_HDMI_EXIST == _ON)
extern void ScalerSyncTMDSRx0HdmiVideoSetting(void);
extern bit ScalerSyncTMDSRx0HdmiColorInfoChanged(void);
#endif

#if(_D1_HDMI_EXIST == _ON)
extern void ScalerSyncTMDSRx1HdmiVideoSetting(void);
extern bit ScalerSyncTMDSRx1HdmiColorInfoChanged(void);
#endif

#if(_D2_HDMI_EXIST == _ON)
#if(_D2_INPUT_PORT_TYPE != _D2_DUAL_DVI_PORT)
extern void ScalerSyncTMDSRx2HdmiVideoSetting(void);
#endif
extern bit ScalerSyncTMDSRx2HdmiColorInfoChanged(void);
#endif

#if(_D3_HDMI_EXIST == _ON)
#if(_D3_INPUT_PORT_TYPE != _D3_DUAL_DVI_PORT)
extern void ScalerSyncTMDSRx3HdmiVideoSetting(void);
#endif
extern bit ScalerSyncTMDSRx3HdmiColorInfoChanged(void);
#endif

#if(_D4_HDMI_EXIST == _ON)
#if(_D4_INPUT_PORT_TYPE != _D4_DUAL_DVI_PORT)
extern void ScalerSyncTMDSRx4HdmiVideoSetting(void);
#endif
extern bit ScalerSyncTMDSRx4HdmiColorInfoChanged(void);
#endif

#if(_D5_HDMI_EXIST == _ON)
extern void ScalerSyncTMDSRx5HdmiVideoSetting(void);
extern bit ScalerSyncTMDSRx5HdmiColorInfoChanged(void);
#endif

