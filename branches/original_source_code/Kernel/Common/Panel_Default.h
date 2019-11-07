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
// ID Code      : Panel_Default.h No.0000
// Update Note  :
//-----------------------------------------------------------------------------------------------------

//////////////////
// General Info //
//////////////////

//--------------------------------------------------
// Definitions for Panel Style
//--------------------------------------------------
#ifndef _PANEL_STYLE
#define _PANEL_STYLE                            _PANEL_NONE
#endif

//--------------------------------------------------
// Definitions for LVDS Panel Configuration
//--------------------------------------------------
#ifndef _LVDS_OUTPUT_PORT
#define _LVDS_OUTPUT_PORT                       _LVDS_2_PORT
#endif

#ifndef _LVDS_PANEL_SECTION
#define _LVDS_PANEL_SECTION                     _LVDS_PANEL_1_SECTION
#endif

#ifndef _LVDS_TABLE_TYPE
#define _LVDS_TABLE_TYPE                        _LVDS_BIT_MAP_TABLE_1_3
#endif

#ifndef _LVDS_CABLE_TYPE
#define _LVDS_CABLE_TYPE                        _LVDS_CABLE_TYPE_0
#endif

//--------------------------------------------------
// Definitions for DPTx Panel Configuration
//--------------------------------------------------
#ifndef _PANEL_DPTX_LINK_RATE
#define _PANEL_DPTX_LINK_RATE                   _PANEL_DPTX_LINK_HBR
#endif

#ifndef _PANEL_DPTX_LANE_NUMBER
#define _PANEL_DPTX_LANE_NUMBER                 _PANEL_DPTX_LANE_NUMBER_4
#endif

#ifndef _PANEL_DPTX_PORT_NUMBER_SEL
#define _PANEL_DPTX_PORT_NUMBER_SEL             _DPTX_TX1_PORT
#endif

#ifndef _PANEL_DPTX_VENDOR_SPECIFIC_TYPE
#define _PANEL_DPTX_VENDOR_SPECIFIC_TYPE        _PANEL_DPTX_VENDOR_SPECIFIC_NONE
#endif

#ifndef _PANEL_DPTX_LINK_SEQUENCE_SWAP
#define _PANEL_DPTX_LINK_SEQUENCE_SWAP          _OFF
#endif

//--------------------------------------------------
// Definitions for TTL Panel Configuration
//--------------------------------------------------
#ifndef _TTL_OUTPUT_PORT
#define _TTL_OUTPUT_PORT                        _TTL_2_PORT
#endif

//--------------------------------------------------
// Definitions for VBO Panel Configuration
//--------------------------------------------------
#ifndef _VBO_BYTE_MODE
#define _VBO_BYTE_MODE                          _VBO_DISP_4_BYTE_MODE
#endif

#ifndef _VBO_OUTPUT_PORT
#define _VBO_OUTPUT_PORT                        _VBO_8_DATA_LANE
#endif

#ifndef _VBO_BIT_MODE
#define _VBO_BIT_MODE                           _VBO_DISP_30_BIT
#endif

#ifndef _VBO_PANEL_SECTION
#define _VBO_PANEL_SECTION                      _VBO_PANEL_1_SECTION
#endif

#ifndef _VBO_HS_CONTROL
#define _VBO_HS_CONTROL                         _VBO_HS_NORMAL
#endif

#ifndef _VBO_VS_CONTROL
#define _VBO_VS_CONTROL                         _VBO_VS_NORMAL
#endif

#ifndef _VBO_VIDEO_TRANSFER_TYPE
#define _VBO_VIDEO_TRANSFER_TYPE                _VBO_VIDEO_TRANSFER_IN_VERTICAL_BLANK
#endif

#ifndef _CDR_TRANSFER_ALN_LATENCY
#define _CDR_TRANSFER_ALN_LATENCY               0
#endif

//--------------------------------------------------
// Definitions for MultiPanel Support
//--------------------------------------------------
#ifndef _PANEL_EXIST_MULTIPANEL
#define _PANEL_EXIST_MULTIPANEL                 _OFF
#endif

//--------------------------------------------------
// Definitions for Panel Manufacturer
//--------------------------------------------------
#ifndef _PANEL_MANUFACTURER
#define _PANEL_MANUFACTURER                     _PANEL_NONE_BRAND
#endif

//--------------------------------------------------
// Definitions for Panel Display Color Depth
//--------------------------------------------------
#ifndef _PANEL_DISP_BIT_MODE
#define _PANEL_DISP_BIT_MODE                    _PANEL_DISP_24_BIT
#endif

//--------------------------------------------------
// Definitions for Maximum Panel Frame Rate (Unit: 0.1 Hz)
//--------------------------------------------------
#ifndef _PANEL_TYP_FRAME_RATE
#define _PANEL_TYP_FRAME_RATE                   600
#endif

#ifndef _PANEL_MAX_FRAME_RATE
#define _PANEL_MAX_FRAME_RATE                   860
#endif

#ifndef _PANEL_MIN_FRAME_RATE
#define _PANEL_MIN_FRAME_RATE                   460
#endif

//--------------------------------------------------
// Definitions for FREESYNC Maximum Panel Frame Rate (Unit: 0.1 Hz)
//--------------------------------------------------
#ifndef _PANEL_FREESYNC_MAX_FRAME_RATE
#define _PANEL_FREESYNC_MAX_FRAME_RATE          1440
#endif

#ifndef _PANEL_FREESYNC_MIN_FRAME_RATE
#define _PANEL_FREESYNC_MIN_FRAME_RATE          300
#endif


///////////////
// Parameter //
///////////////

//--------------------------------------------------
// Definitions for Panel Parameter
//--------------------------------------------------
#ifndef _PANEL_DH_START
#define _PANEL_DH_START                         48                  // Display Horizontal Start Position
#endif

#ifndef _PANEL_DH_WIDTH
#define _PANEL_DH_WIDTH                         1920                // Display Horizontal Width
#endif

#ifndef _PANEL_DH_END
#define _PANEL_DH_END                           1968                // Display Horizontal End Position
#endif

#ifndef _PANEL_DH_TOTAL
#define _PANEL_DH_TOTAL                         2100                // Display Horizontal Total Clock Number in One Display Line
#endif

#ifndef _PANEL_DH_TOTAL_MAX
#define _PANEL_DH_TOTAL_MAX                     2200                // Maxinum Display Horizontal Total Clock Number in One Display Line
#endif

#ifndef _PANEL_DH_TOTAL_MIN
#define _PANEL_DH_TOTAL_MIN                     2048                // Mininum Display Horizontal Total Clock Number in One Display Line
#endif

#ifndef _PANEL_DV_START
#define _PANEL_DV_START                         6                   // Display Vertical Start Position
#endif

#ifndef _PANEL_DV_HEIGHT
#define _PANEL_DV_HEIGHT                        1080                // Display Vertical Width
#endif

#ifndef _PANEL_DV_END
#define _PANEL_DV_END                           1086                // Display Vertical End Position
#endif

#ifndef _PANEL_DV_TOTAL
#define _PANEL_DV_TOTAL                         1150                // Display Vertical Total Clock Number in One Display Line
#endif

#ifndef _PANEL_DV_TOTAL_MAX
#define _PANEL_DV_TOTAL_MAX                     1600                // Maxinum Display Vertical Total Clock Number in One Display Line
#endif

#ifndef _PANEL_DV_TOTAL_MIN
#define _PANEL_DV_TOTAL_MIN                     1100                // Mininum Display Vertical Total Clock Number in One Display Line
#endif

#ifndef _PANEL_DH_SYNC_WIDTH
#define _PANEL_DH_SYNC_WIDTH                    8                   // Display Horizontal Sync Width
#endif

#ifndef _PANEL_DV_SYNC_HEIGHT
#define _PANEL_DV_SYNC_HEIGHT                   2                   // Display Vertical Sync Height
#endif

#ifndef _PANEL_PIXEL_CLOCK
#define _PANEL_PIXEL_CLOCK                      144                 // Typical Pixel Clock in MHz
#endif

#ifndef _PANEL_PIXEL_CLOCK_MAX
#define _PANEL_PIXEL_CLOCK_MAX                  230                 // Maxinum Pixel Clock in MHz
#endif

#ifndef _PANEL_PIXEL_CLOCK_MIN
#define _PANEL_PIXEL_CLOCK_MIN                  110                 // Mininum Pixel Clock in MHz
#endif

#ifndef _PANEL_POWER_ON_T1
#define _PANEL_POWER_ON_T1                      100                 // Panel Power On T1 (ms)
#endif

#ifndef _PANEL_POWER_ON_T2
#define _PANEL_POWER_ON_T2                      40                  // Panel Power On T2 (ms)
#endif

#ifndef _PANEL_POWER_ON_T3
#define _PANEL_POWER_ON_T3                      300                 // Panel Power On T3 (ms)
#endif

#ifndef _PANEL_POWER_OFF_T4
#define _PANEL_POWER_OFF_T4                     20                  // Panel Power Off T4 (ms)
#endif

#ifndef _PANEL_POWER_OFF_T5
#define _PANEL_POWER_OFF_T5                     40                  // Panel Power Off T5 (ms)
#endif

#ifndef _PANEL_POWER_OFF_T6
#define _PANEL_POWER_OFF_T6                     600                 // Panel Power Off T6 (ms)
#endif


/////////////
// Display //
/////////////

//--------------------------------------------------
// Definitions for Last Line Finetune Target
//--------------------------------------------------
#ifndef _LAST_LINE_TARGET
#define _LAST_LINE_TARGET                       (_PANEL_DH_TOTAL - 150)
#endif

//--------------------------------------------------
// MN Frame Tracking Fine Tune Last Line
//--------------------------------------------------
#ifndef _MN_FINE_TUNE_LASTLINE_SUPPORT
#define _MN_FINE_TUNE_LASTLINE_SUPPORT          _OFF
#endif

#ifndef _MN_LAST_LINE_MAX
#define _MN_LAST_LINE_MAX                       (_LAST_LINE_TARGET + 25)
#endif

#ifndef _MN_LAST_LINE_MIN
#define _MN_LAST_LINE_MIN                       (_LAST_LINE_TARGET - 25)
#endif

//--------------------------------------------------
// Definitions for Frame Sync Margin (Unit: 0.1Hz)
//--------------------------------------------------
#ifndef _FRAME_SYNC_MARGIN
#define _FRAME_SYNC_MARGIN                      20
#endif

//--------------------------------------------------
// Definitions for panel DVtotal adjust limit
//--------------------------------------------------
#ifndef _PANEL_DV_LINE_CHG_LIMIT
#define _PANEL_DV_LINE_CHG_LIMIT                (_PANEL_DV_TOTAL)
#endif

//--------------------------------------------------
// Definitions for Panel DCLK Unit
//--------------------------------------------------
#ifndef _PANEL_PIXEL_CLOCK_UNIT
#define _PANEL_PIXEL_CLOCK_UNIT                 _PANEL_CLOCK_MHZ
#endif

//--------------------------------------------------
// Definitions for video compensation
//-------------------------------------------------
#ifndef BYPASS_VIDEO_COMPENSATION
#define BYPASS_VIDEO_COMPENSATION(Vin, Vout)    (_FALSE)
#endif


////////////////////
// VGA Auto Color //
////////////////////

//--------------------------------------------------
// Definitions for ADC Gain/Offset Adjust
//--------------------------------------------------
#ifndef _PANEL_ADC_OFFSET_BIAS
#define _PANEL_ADC_OFFSET_BIAS                  (0) // 0~5
#endif

#ifndef _PANEL_ADC_GAIN_BIAS
#define _PANEL_ADC_GAIN_BIAS                    (0) // -5~0
#endif


///////////////////////////
// Color Characteristics //
///////////////////////////

//--------------------------------------------------
// I Dither Option
//--------------------------------------------------
#ifndef _I_DITHER_TEMP
#define _I_DITHER_TEMP                          _ENABLE
#endif

#ifndef _I_DITHER_VALUE_SIGN
#define _I_DITHER_VALUE_SIGN                    _DISABLE
#endif

#ifndef _I_DITHER_V_FRAME_MOD
#define _I_DITHER_V_FRAME_MOD                   _DISABLE
#endif

#ifndef _I_DITHER_H_FRAME_MOD
#define _I_DITHER_H_FRAME_MOD                   _DISABLE
#endif

#ifndef _I_DITHER_MULTI_SEQ_ENABLE
#define _I_DITHER_MULTI_SEQ_ENABLE              _DISABLE
#endif

#ifndef _I_DITHER_SHARE_SEQ_ENABLE
#define _I_DITHER_SHARE_SEQ_ENABLE              _DISABLE
#endif

#ifndef _I_DITHER_SERIES_SEQ_ENABLE
#define _I_DITHER_SERIES_SEQ_ENABLE             _DISABLE
#endif

#ifndef _I_DITHER_SEQ_INV_ENABLE
#define _I_DITHER_SEQ_INV_ENABLE                _DISABLE
#endif

#ifndef _I_DITHER_SEQ_INV_MODE
#define _I_DITHER_SEQ_INV_MODE                  0
#endif

#ifndef _I_DITHER_12_TO_10_TEMP
#define _I_DITHER_12_TO_10_TEMP                 _I_DITHER_TEMP
#endif

#ifndef _I_DITHER_12_TO_10_VALUE_SIGN
#define _I_DITHER_12_TO_10_VALUE_SIGN           _I_DITHER_VALUE_SIGN
#endif

#ifndef _I_DITHER_12_TO_10_V_FRAME_MOD
#define _I_DITHER_12_TO_10_V_FRAME_MOD          _I_DITHER_V_FRAME_MOD
#endif

#ifndef _I_DITHER_12_TO_10_H_FRAME_MOD
#define _I_DITHER_12_TO_10_H_FRAME_MOD          _I_DITHER_H_FRAME_MOD
#endif

#ifndef _I_DITHER_12_TO_10_MULTI_SEQ_ENABLE
#define _I_DITHER_12_TO_10_MULTI_SEQ_ENABLE     _I_DITHER_MULTI_SEQ_ENABLE
#endif

#ifndef _I_DITHER_12_TO_10_SHARE_SEQ_ENABLE
#define _I_DITHER_12_TO_10_SHARE_SEQ_ENABLE     _I_DITHER_SHARE_SEQ_ENABLE
#endif

#ifndef _I_DITHER_12_TO_10_SERIES_SEQ_ENABLE
#define _I_DITHER_12_TO_10_SERIES_SEQ_ENABLE    _I_DITHER_SERIES_SEQ_ENABLE
#endif

#ifndef _I_DITHER_12_TO_10_SEQ_INV_ENABLE
#define _I_DITHER_12_TO_10_SEQ_INV_ENABLE       _I_DITHER_SEQ_INV_ENABLE
#endif

#ifndef _I_DITHER_12_TO_10_SEQ_INV_MODE
#define _I_DITHER_12_TO_10_SEQ_INV_MODE         _I_DITHER_SEQ_INV_MODE  // 0: r,~r,g,~g,b,~b    1:  r,g,b~r,~g,~b
#endif

//--------------------------------------------------
// D Dither Option
//--------------------------------------------------
#ifndef _D_DITHER_TEMP
#define _D_DITHER_TEMP                          _ENABLE
#endif

#ifndef _D_DITHER_V_FRAME_MOD
#define _D_DITHER_V_FRAME_MOD                   _DISABLE
#endif

#ifndef _D_DITHER_H_FRAME_MOD
#define _D_DITHER_H_FRAME_MOD                   _DISABLE
#endif

#ifndef _D_DITHER_MULTI_SEQ_ENABLE
#define _D_DITHER_MULTI_SEQ_ENABLE              _DISABLE
#endif

#ifndef _D_DITHER_SHARE_SEQ_ENABLE
#define _D_DITHER_SHARE_SEQ_ENABLE              _DISABLE
#endif

#ifndef _D_DITHER_SEQ_INV_ENABLE
#define _D_DITHER_SEQ_INV_ENABLE                _DISABLE
#endif

#ifndef _D_DITHER_SEQ_INV_MODE
#define _D_DITHER_SEQ_INV_MODE                  0  // 0: r,~r,g,~g,b,~b    1:  r,g,b~r,~g,~b
#endif

#ifndef _D_DITHER_SERIES_SEQ_ENABLE
#define _D_DITHER_SERIES_SEQ_ENABLE             _DISABLE
#endif

#ifndef _D_DITHER_ADVANCE_SETTING_ENABLE
#define _D_DITHER_ADVANCE_SETTING_ENABLE        _DISABLE
#endif

#if(_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL)
#ifndef _D_DITHER_SUPER_PIXEL_SIZE
#define _D_DITHER_SUPER_PIXEL_SIZE                  ((_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT) ? _DDITHER_SUPER_PIXEL_4X4 : _DDITHER_SUPER_PIXEL_4X8)
#endif
#endif

