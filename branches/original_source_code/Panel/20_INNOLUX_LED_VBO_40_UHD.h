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

#if(_PANEL_TYPE == _INNOLUX_LED_VBO_40_UHD)
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
#define _PANEL_MANUFACTURER                     _PANEL_INNOLUX

//--------------------------------------------------
// Definitions for Panel Style
//--------------------------------------------------
#define _PANEL_STYLE                            _PANEL_VBO

//--------------------------------------------------
// Definitions for Panel Display Color Depth
//--------------------------------------------------
#define _PANEL_DISP_BIT_MODE                    _PANEL_DISP_30_BIT

//--------------------------------------------------
// Definitions for Vbyone Panel Style
//--------------------------------------------------
#define _VBO_BYTE_MODE                          _VBO_DISP_4_BYTE_MODE     // Depend on _DISP_BIT_MODE

//--------------------------------------------------
// Definitions for Panel Configuration
//--------------------------------------------------
#define _VBO_OUTPUT_PORT                        _VBO_8_DATA_LANE          // _VBO_1_DATA_LANE or _VBO_2_DATA_LANE or _VBO_4_DATA_LANE or _VBO_8_DATA_LANE
#define _VBO_BIT_MODE                           _VBO_DISP_30_BIT          // 30bit -> 4byte mode
#define _VBO_PANEL_SECTION                      _VBO_PANEL_1_SECTION      // Set Panel Display Section
#define _VBO_HS_CONTROL                         _VBO_HS_NORMAL            // Normal Format or Always On or Always Off
#define _VBO_VS_CONTROL                         _VBO_VS_NORMAL            // Normal Format or Always On or Always Off
#define _VBO_VIDEO_TRANSFER_TYPE                _VBO_VIDEO_TRANSFER_IN_VERTICAL_BLANK

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
#define _PANEL_DH_WIDTH                         3840                // Display Horizontal Width
#define _PANEL_DH_END                           3888                // Display Horizontal End Position

#define _PANEL_DH_TOTAL                         4400                // Display Horizontal Total Clock Number in One Display Line
#define _PANEL_DH_TOTAL_MAX                     4800                // Maxinum Display Horizontal Total Clock Number in One Display Line
#define _PANEL_DH_TOTAL_MIN                     4240                // Mininum Display Horizontal Total Clock Number in One Display Line

#define _PANEL_DV_START                         6                   // Display Vertical Start Position
#define _PANEL_DV_HEIGHT                        2160                // Display Vertical Width
#define _PANEL_DV_END                           2166                // Display Vertical End Position

#define _PANEL_DV_TOTAL                         2250                // Display Vertical Total Clock Number in One Display Line
#define _PANEL_DV_TOTAL_MAX                     2350                // Maxinum Display Vertical Total Clock Number in One Display Line
#define _PANEL_DV_TOTAL_MIN                     2208                // Mininum Display Vertical Total Clock Number in One Display Line

#define _PANEL_DH_SYNC_WIDTH                    8                   // Display Horizontal Sync Width
#define _PANEL_DV_SYNC_HEIGHT                   2                   // Display Vertical Sync Height

#define _PANEL_PIXEL_CLOCK                      594                 // Typical Pixel Clock in MHz
#define _PANEL_PIXEL_CLOCK_MAX                  600                 // Maxinum Pixel Clock in MHz
#define _PANEL_PIXEL_CLOCK_MIN                  560                 // Mininum Pixel Clock in MHz


#define _PANEL_POWER_ON_T1                      5                   // Panel Power On T1 (ms)
#define _PANEL_POWER_ON_T2                      200                 // Panel Power On T2 (ms)
#define _PANEL_POWER_ON_T3                      1500                 // Panel Power On T3 (ms)

#define _PANEL_POWER_OFF_T4                     100                 // Panel Power Off T4 (ms)
#define _PANEL_POWER_OFF_T5                     50                  // Panel Power Off T5 (ms)
#define _PANEL_POWER_OFF_T6                     500                 // Panel Power Off T6 (ms)

#define _CDR_TRANSFER_ALN_LATENCY               9                   // Latency between CDR pattern and ALN pattern (us)


//--------------------------------------------------
// Definitions for Color Table
//--------------------------------------------------
#include "./RTDColorDefaultTable/ColorTableInclude.h"

#endif // End of #if(_PANEL_TYPE == _INNOLUX_LED_VBO_40_UHD)
