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

#if(_PANEL_TYPE == _PANEL_DPTX_EXAMPLE)
//----------------------------------------------------------------------------------------------------
// ID Code      : _PANEL_DPTX_EXAMPLE.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//////////////////
// General Info //
//////////////////

//--------------------------------------------------
// Definitions for Panel Style
//--------------------------------------------------
#define _PANEL_STYLE                            _PANEL_DPTX

//--------------------------------------------------
// Definitions for DPTx Panel Configuration
//--------------------------------------------------
#define _PANEL_DPTX_LINK_RATE                   _PANEL_DPTX_LINK_HBR
#define _PANEL_DPTX_LANE_NUMBER                 _PANEL_DPTX_LANE_NUMBER_4
#define _PANEL_DPTX_PORT_NUMBER_SEL             _DPTX_TX1_PORT
#define _PANEL_DPTX_VENDOR_SPECIFIC_TYPE        _PANEL_DPTX_VENDOR_SPECIFIC_NONE
#define _PANEL_DPTX_LINK_SEQUENCE_SWAP          _OFF

//--------------------------------------------------
// Definitions for MultiPanel Support
//--------------------------------------------------
#define _PANEL_EXIST_MULTIPANEL                 _OFF

//--------------------------------------------------
// Definitions for Panel Manufacturer
//--------------------------------------------------
#define _PANEL_MANUFACTURER                     _PANEL_NONE_BRAND

//--------------------------------------------------
// Definitions for Panel Display Color Depth
//--------------------------------------------------
#define _PANEL_DISP_BIT_MODE                    _PANEL_DISP_24_BIT

//--------------------------------------------------
// Definitions for Maximum Panel Frame Rate (Unit: 0.1 Hz)
//--------------------------------------------------
#define _PANEL_TYP_FRAME_RATE                   600
#define _PANEL_MAX_FRAME_RATE                   860
#define _PANEL_MIN_FRAME_RATE                   460

//--------------------------------------------------
// Definitions for FREESYNC Maximum Panel Frame Rate (Unit: 0.1 Hz)
//--------------------------------------------------
#define _PANEL_FREESYNC_MAX_FRAME_RATE          1440
#define _PANEL_FREESYNC_MIN_FRAME_RATE          300


///////////////
// Parameter //
///////////////

//--------------------------------------------------
// Definitions for Panel Parameter
//--------------------------------------------------
#define _PANEL_DH_START                         48                  // Display Horizontal Start Position
#define _PANEL_DH_WIDTH                         1920                // Display Horizontal Width
#define _PANEL_DH_END                           1968                // Display Horizontal End Position

#define _PANEL_DH_TOTAL                         2100                // Display Horizontal Total Clock Number in One Display Line
#define _PANEL_DH_TOTAL_MAX                     2200                // Maxinum Display Horizontal Total Clock Number in One Display Line
#define _PANEL_DH_TOTAL_MIN                     2048                // Mininum Display Horizontal Total Clock Number in One Display Line

#define _PANEL_DV_START                         6                   // Display Vertical Start Position
#define _PANEL_DV_HEIGHT                        1080                // Display Vertical Width
#define _PANEL_DV_END                           1086                // Display Vertical End Position

#define _PANEL_DV_TOTAL                         1150                // Display Vertical Total Clock Number in One Display Line
#define _PANEL_DV_TOTAL_MAX                     1600                // Maxinum Display Vertical Total Clock Number in One Display Line
#define _PANEL_DV_TOTAL_MIN                     1100                // Mininum Display Vertical Total Clock Number in One Display Line

#define _PANEL_DH_SYNC_WIDTH                    8                   // Display Horizontal Sync Width
#define _PANEL_DV_SYNC_HEIGHT                   2                   // Display Vertical Sync Height

#define _PANEL_PIXEL_CLOCK                      144                 // Typical Pixel Clock in MHz
#define _PANEL_PIXEL_CLOCK_MAX                  230                 // Maxinum Pixel Clock in MHz
#define _PANEL_PIXEL_CLOCK_MIN                  110                 // Mininum Pixel Clock in MHz

#define _PANEL_POWER_ON_T1                      100                 // Panel Power On T1 (ms)
#define _PANEL_POWER_ON_T2                      40                  // Panel Power On T2 (ms)
#define _PANEL_POWER_ON_T3                      300                 // Panel Power On T3 (ms)

#define _PANEL_POWER_OFF_T4                     20                  // Panel Power Off T4 (ms)
#define _PANEL_POWER_OFF_T5                     40                  // Panel Power Off T5 (ms)
#define _PANEL_POWER_OFF_T6                     600                 // Panel Power Off T6 (ms)


/////////////
// Display //
/////////////

//--------------------------------------------------
// Definitions for Last Line Finetune Target
//--------------------------------------------------
#define _LAST_LINE_TARGET                       (_PANEL_DH_TOTAL - 150)

//--------------------------------------------------
// MN Frame Tracking Fine Tune Last Line
//--------------------------------------------------
#define _MN_FINE_TUNE_LASTLINE_SUPPORT          _OFF
#define _MN_LAST_LINE_MAX                       (_LAST_LINE_TARGET + 25)
#define _MN_LAST_LINE_MIN                       (_LAST_LINE_TARGET - 25)

//--------------------------------------------------
// Definitions for Frame Sync Margin (Unit: 0.1Hz)
//--------------------------------------------------
#define _FRAME_SYNC_MARGIN                      20

//--------------------------------------------------
// Definitions for panel DVtotal adjust limit
//--------------------------------------------------
#define _PANEL_DV_LINE_CHG_LIMIT                (_PANEL_DV_TOTAL)

//--------------------------------------------------
// Definitions for Panel DCLK Unit
//--------------------------------------------------
#define _PANEL_PIXEL_CLOCK_UNIT                 _PANEL_CLOCK_MHZ


////////////////////
// VGA Auto Color //
////////////////////

//--------------------------------------------------
// Definitions for ADC Gain/Offset Adjust
//--------------------------------------------------
#define _PANEL_ADC_OFFSET_BIAS                  (0) // 0~5
#define _PANEL_ADC_GAIN_BIAS                    (0) // -5~0


///////////////////////////
// Color Characteristics //
///////////////////////////

//--------------------------------------------------
// I Dither Option
//--------------------------------------------------
#define _I_DITHER_TEMP                          _ENABLE

#if((_IDITHER_TYPE == _IDITHER_GEN_0_1_SEQ_TRUNCATE_2_0_BIT) || (_IDITHER_TYPE == _IDITHER_GEN_1_4_SEQ_TRUNCATE_4_2_BIT))
#define _I_DITHER_VALUE_SIGN                    _DISABLE
#define _I_DITHER_V_FRAME_MOD                   _DISABLE
#define _I_DITHER_H_FRAME_MOD                   _DISABLE
#endif

#if(_IDITHER_TYPE == _IDITHER_GEN_1_4_SEQ_TRUNCATE_4_2_BIT)
#define _I_DITHER_MULTI_SEQ_ENABLE              _DISABLE
#define _I_DITHER_SHARE_SEQ_ENABLE              _DISABLE
#define _I_DITHER_SERIES_SEQ_ENABLE             _DISABLE
#define _I_DITHER_SEQ_INV_ENABLE                _DISABLE
#define _I_DITHER_SEQ_INV_MODE                  0
#endif

#define _I_DITHER_12_TO_10_TEMP                 _I_DITHER_TEMP
#define _I_DITHER_12_TO_10_VALUE_SIGN           _I_DITHER_VALUE_SIGN
#define _I_DITHER_12_TO_10_V_FRAME_MOD          _I_DITHER_V_FRAME_MOD
#define _I_DITHER_12_TO_10_H_FRAME_MOD          _I_DITHER_H_FRAME_MOD
#define _I_DITHER_12_TO_10_MULTI_SEQ_ENABLE     _I_DITHER_MULTI_SEQ_ENABLE
#define _I_DITHER_12_TO_10_SHARE_SEQ_ENABLE     _I_DITHER_SHARE_SEQ_ENABLE
#define _I_DITHER_12_TO_10_SERIES_SEQ_ENABLE    _I_DITHER_SERIES_SEQ_ENABLE
#define _I_DITHER_12_TO_10_SEQ_INV_ENABLE       _I_DITHER_SEQ_INV_ENABLE
#define _I_DITHER_12_TO_10_SEQ_INV_MODE         _I_DITHER_SEQ_INV_MODE // 0: r,~r,g,~g,b,~b    1:  r,g,b~r,~g,~b

//--------------------------------------------------
// D Dither Option
//--------------------------------------------------
#define _D_DITHER_TEMP                          _ENABLE

#if((_DDITHER_TYPE == _DDITHER_GEN_0_4BIT_DITHERTBL) || (_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL))
#define _D_DITHER_V_FRAME_MOD                   _DISABLE
#define _D_DITHER_H_FRAME_MOD                   _DISABLE
#endif

#define _D_DITHER_MULTI_SEQ_ENABLE              _DISABLE
#define _D_DITHER_SHARE_SEQ_ENABLE              _DISABLE
#define _D_DITHER_SEQ_INV_ENABLE                _DISABLE
#define _D_DITHER_SEQ_INV_MODE                  0 // 0: r,~r,g,~g,b,~b    1:  r,g,b~r,~g,~b

#if(_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL)
#define _D_DITHER_SERIES_SEQ_ENABLE             _DISABLE
#define _D_DITHER_ADVANCE_SETTING_ENABLE        _DISABLE
#endif

#endif // End of #if(_PANEL_TYPE == _PANEL_DPTX_EXAMPLE)
