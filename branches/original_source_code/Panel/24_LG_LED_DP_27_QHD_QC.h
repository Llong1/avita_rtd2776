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

#if(_PANEL_TYPE == _LG_LED_DP_27_QHD_QC)
//----------------------------------------------------------------------------------------------------
// ID Code      : Panel.h No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions for MultiPanel Support
//--------------------------------------------------
#define _PANEL_EXIST_MULTIPANEL                 _OFF

//--------------------------------------------------
// Maximum Panel Frame Rate (Unit: 0.1 Hz)
//--------------------------------------------------
#define _PANEL_TYP_FRAME_RATE                   600
#define _PANEL_MAX_FRAME_RATE                   610
#define _PANEL_MIN_FRAME_RATE                   590

//--------------------------------------------------
// Frame Sync Margin (Unit: 0.1Hz)
//--------------------------------------------------
#define _FRAME_SYNC_MARGIN                      20

//--------------------------------------------------
// Set Last Line Finetune Target (Must Be Larger than 4 Pixel!!)
//--------------------------------------------------
#define _LAST_LINE_TARGET                       (_PANEL_DH_TOTAL - 300)

//--------------------------------------------------
// Definitions for Panel Manufacturer
//--------------------------------------------------
#define _PANEL_MANUFACTURER                     _PANEL_LGD

//--------------------------------------------------
// Definitions for Panel Style
//--------------------------------------------------
#define _PANEL_STYLE                            _PANEL_DPTX
#define _PANEL_DPTX_LINK_RATE                   _PANEL_DPTX_LINK_HBR
#define _PANEL_DPTX_LANE_NUMBER                 _PANEL_DPTX_LANE_NUMBER_4
#define _PANEL_DPTX_VENDOR_SPECIFIC_TYPE        _PANEL_DPTX_VENDOR_SPECIFIC_NONE

//--------------------------------------------------
// Definitions for Panel Display Color Depth
//--------------------------------------------------
#define _PANEL_DISP_BIT_MODE                    _PANEL_DISP_24_BIT

//--------------------------------------------------
// Definitions for Dither Configuration
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
#define _I_DITHER_SEQ_INV_MODE                  0  // 0: r,~r,g,~g,b,~b    1:  r,g,b~r,~g,~b
#endif

#define _D_DITHER_TEMP                          _ENABLE

#if((_DDITHER_TYPE == _DDITHER_GEN_0_4BIT_DITHERTBL) || (_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL))
#define _D_DITHER_V_FRAME_MOD                   _DISABLE
#define _D_DITHER_H_FRAME_MOD                   _DISABLE
#endif

#define _D_DITHER_MULTI_SEQ_ENABLE              _DISABLE
#define _D_DITHER_SHARE_SEQ_ENABLE              _DISABLE

#define _D_DITHER_SEQ_INV_ENABLE                _DISABLE
#define _D_DITHER_SEQ_INV_MODE                  0  // 0: r,~r,g,~g,b,~b    1:  r,g,b~r,~g,~b

#if(_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL)
#define _D_DITHER_SERIES_SEQ_ENABLE             _DISABLE
#define _D_DITHER_ADVANCE_SETTING_ENABLE        _DISABLE
#endif

//--------------------------------------------------
// Definitions for Panel Parameter
//--------------------------------------------------
#define _PANEL_DH_START                         48                  // Display Horizontal Start Position
#define _PANEL_DH_WIDTH                         2560                // Display Horizontal Width
#define _PANEL_DH_END                           2608                // Display Horizontal End Position

#define _PANEL_DH_TOTAL                         3824                // Display Horizontal Total Clock Number in One Display Line
#define _PANEL_DH_TOTAL_MAX                     3900                // Maxinum Display Horizontal Total Clock Number in One Display Line
#define _PANEL_DH_TOTAL_MIN                     3700                // Mininum Display Horizontal Total Clock Number in One Display Line

#define _PANEL_DV_START                         6                   // Display Vertical Start Position
#define _PANEL_DV_HEIGHT                        1440                // Display Vertical Width
#define _PANEL_DV_END                           1446                // Display Vertical End Position

#define _PANEL_DV_TOTAL                         1481                // Display Vertical Total Clock Number in One Display Line
#define _PANEL_DV_TOTAL_MAX                     1483                // Maxinum Display Vertical Total Clock Number in One Display Line
#define _PANEL_DV_TOTAL_MIN                     1479                // Mininum Display Vertical Total Clock Number in One Display Line

#define _PANEL_DH_SYNC_WIDTH                    8                   // Display Horizontal Sync Width
#define _PANEL_DV_SYNC_HEIGHT                   2                   // Display Vertical Sync Height

#define _PANEL_PIXEL_CLOCK                      340                 // Typical Pixel Clock in MHz
#define _PANEL_PIXEL_CLOCK_MAX                  360                 // Maxinum Pixel Clock in MHz
#define _PANEL_PIXEL_CLOCK_MIN                  330                 // Mininum Pixel Clock in MHz

#define _PANEL_POWER_ON_T1                      10                  // Panel Power On T1 (ms)
#define _PANEL_POWER_ON_T2                      50                  // Panel Power On T2 (ms)
#define _PANEL_POWER_ON_T3                      250                 // Panel Power On T3 (ms)

#define _PANEL_POWER_OFF_T4                     50                  // Panel Power Off T4 (ms)
#define _PANEL_POWER_OFF_T5                     10                  // Panel Power Off T5 (ms)
#define _PANEL_POWER_OFF_T6                     300                 // Panel Power Off T6 (ms)


//--------------------------------------------------
// Definitions for Color Table
//--------------------------------------------------
#include "./RTDColorDefaultTable/ColorTableInclude.h"

#endif // End of #if(_PANEL_TYPE == _LG_LED_DP_27_QHD_QC)
