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
// ID Code      : Scaler_Option.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_OPTION_H__
#define __SCALER_OPTION_H__

//--------------------------------------------------
// Memory Type Option
//--------------------------------------------------
#if(_MEMORY_TYPE == _EXTERNAL_MEMORY)

#define _MEMORY_TYPE_CONFIG                         (_EXTERNAL_MEMORY_SIZE_CONFIG & _MEMORY_TYPE_CONFIG_MASK)
#define _MEMORY_SIZE_CONFIG                         _EXTERNAL_MEMORY_SIZE_CONFIG

#if(_MEMORY_TYPE_CONFIG == _NO_MEMORY)
#define _MEMORY_PHASE_CALIBRATION_MODE              _MEMORY_PHASE_CALIBRATION_MODE_NONE
#elif(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)
#define _MEMORY_PHASE_CALIBRATION_MODE              _MEMORY_PHASE_CALIBRATION_FRC_MODE
#endif

#elif(_MEMORY_TYPE == _EMBEDDED_MEMORY)

#define _MEMORY_TYPE_CONFIG                         (_EMBEDDED_MEMORY_SIZE_CONFIG & _MEMORY_TYPE_CONFIG_MASK)
#define _MEMORY_SIZE_CONFIG                         _EMBEDDED_MEMORY_SIZE_CONFIG

#if(_MEMORY_TYPE_CONFIG == _NO_MEMORY)
#define _MEMORY_PHASE_CALIBRATION_MODE              _MEMORY_PHASE_CALIBRATION_MODE_NONE
#elif(_MEMORY_TYPE_CONFIG == _MEMORY_SDRAM)
#define _SDRAM_PHASE_CALIBRATION                    _ON
#define _MEMORY_PHASE_CALIBRATION_MODE              _MEMORY_PHASE_CALIBRATION_MCU_MODE
#define _SDRAM_PHASE_ON_LINE_ADDRESS                (0x1FFDF7) // 2047 row, Bank1, 248 column (remain 8 cell)
#elif(_MEMORY_TYPE_CONFIG == _MEMORY_DDR1)
#define _DDR1_PHASE_CALIBRATION                     _ON
#define _MEMORY_PHASE_CALIBRATION_MODE              _MEMORY_PHASE_CALIBRATION_MCU_MODE
#elif(_MEMORY_TYPE_CONFIG == _MEMORY_DDR2)
#define _DDR2_PHASE_CALIBRATION                     _ON
#define _MEMORY_PHASE_CALIBRATION_MODE              _MEMORY_PHASE_CALIBRATION_MCU_MODE
#endif

#endif // End of #if(_MEMORY_TYPE == _EXTERNAL_MEMORY)

#if(_MEMORY_TYPE_CONFIG != _MEMORY_SDRAM)
#define _SDRAM_PHASE_CALIBRATION                    _OFF
#endif

#if(_MEMORY_TYPE_CONFIG != _MEMORY_DDR1)
#define _DDR1_PHASE_CALIBRATION                     _OFF
#endif

#if(_MEMORY_TYPE_CONFIG != _MEMORY_DDR2)
#define _DDR2_PHASE_CALIBRATION                     _OFF
#endif

//--------------------------------------------------
// D Domain 4 Path for FrameSync Line Buffer Option
//--------------------------------------------------
#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
#undef _FRAME_SYNC_LINE_BUFFER_SUPPORT
#define _FRAME_SYNC_LINE_BUFFER_SUPPORT             _ON
#endif

//--------------------------------------------------
// HDMI2.0 YCbCr420 Option
//--------------------------------------------------
#if(_HDMI_2_0_SUPPORT == _ON)

#if((_SCALER_TYPE == _RL6193_SERIES) || (_SCALER_TYPE == _RL6410_SERIES))
#define _HDMI_2_0_YCBCR420_SUPPORT                  _ON
#else
#define _HDMI_2_0_YCBCR420_SUPPORT                  _OFF
#endif

#else

#define _HDMI_2_0_YCBCR420_SUPPORT                  _OFF

#endif

//--------------------------------------------------
// TMDS Support Macro Option
//--------------------------------------------------
#if(((_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_ALL) && (_DVI_SUPPORT == _ON)) ||\
     (((_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_NONE) || (_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_D1_D2)) && (_D0_TMDS_SUPPORT == _ON)) ||\
     ((_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_D1_D2) && (_DVI_SUPPORT == _ON) && (_D0_TMDS_SUPPORT == _OFF)))
#define _D0_TMDS_EXIST                              _ON
#else
#define _D0_TMDS_EXIST                              _OFF
#endif

#if(((_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_ALL) && (_HDMI_SUPPORT == _ON)) ||\
     (((_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_NONE) || (_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_D1_D2)) && (_D0_HDMI_SUPPORT == _ON)) ||\
     ((_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_D1_D2) && (_HDMI_SUPPORT == _ON) && (_D0_HDMI_SUPPORT == _OFF)))
#define _D0_HDMI_EXIST                              _ON
#else
#define _D0_HDMI_EXIST                              _OFF
#endif

#if((_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_NONE) && (_D1_TMDS_SUPPORT == _ON))
#define _D1_TMDS_EXIST                              _ON
#else
#define _D1_TMDS_EXIST                              _OFF
#endif

#if((_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_NONE) && (_D1_HDMI_SUPPORT == _ON))
#define _D1_HDMI_EXIST                              _ON
#else
#define _D1_HDMI_EXIST                              _OFF
#endif

#if(_D2_TMDS_SUPPORT == _ON)
#define _D2_TMDS_EXIST                              _ON
#else
#define _D2_TMDS_EXIST                              _OFF
#endif

#if(_D2_HDMI_SUPPORT == _ON)
#define _D2_HDMI_EXIST                              _ON
#else
#define _D2_HDMI_EXIST                              _OFF
#endif

#if(_D3_TMDS_SUPPORT == _ON)
#define _D3_TMDS_EXIST                              _ON
#else
#define _D3_TMDS_EXIST                              _OFF
#endif

#if(_D3_HDMI_SUPPORT == _ON)
#define _D3_HDMI_EXIST                              _ON
#else
#define _D3_HDMI_EXIST                              _OFF
#endif

#if(_D4_TMDS_SUPPORT == _ON)
#define _D4_TMDS_EXIST                              _ON
#else
#define _D4_TMDS_EXIST                              _OFF
#endif

#if(_D4_HDMI_SUPPORT == _ON)
#define _D4_HDMI_EXIST                              _ON
#else
#define _D4_HDMI_EXIST                              _OFF
#endif

#if(_D5_TMDS_SUPPORT == _ON)
#define _D5_TMDS_EXIST                              _ON
#else
#define _D5_TMDS_EXIST                              _OFF
#endif

#if(_D5_HDMI_SUPPORT == _ON)
#define _D5_HDMI_EXIST                              _ON
#else
#define _D5_HDMI_EXIST                              _OFF
#endif

//--------------------------------------------------
// DP Support Macro Option
//--------------------------------------------------
#if(((_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_ALL) && (_DP_SUPPORT == _ON)) ||\
     (((_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_NONE) || (_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_D1_D2)) && (_D0_INPUT_PORT_TYPE == _D0_DP_PORT)) ||\
      ((_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_D1_D2) && (_DP_SUPPORT == _ON) && (_D0_INPUT_PORT_TYPE != _D0_DP_PORT)))
#define _D0_DP_EXIST                                _ON
#else
#define _D0_DP_EXIST                                _OFF
#endif

#if((_HW_DIGITAL_PORT_COMBO_PHY_TYPE == _DIGITAL_PORT_COMBO_PHY_NONE) && (_D1_INPUT_PORT_TYPE == _D1_DP_PORT))
#define _D1_DP_EXIST                                _ON
#else
#define _D1_DP_EXIST                                _OFF
#endif

//--------------------------------------------------
// DP MST & DP Tx Option
//--------------------------------------------------
#if(_DP_SUPPORT == _OFF)
#undef _DP_MST_SUPPORT
#undef _DP_TX_SUPPORT
#define _DP_MST_SUPPORT                             _OFF
#define _DP_TX_SUPPORT                              _OFF

#undef _D0_DP_MST_PORT_SUPPORT
#undef _D1_DP_MST_PORT_SUPPORT
#define _D0_DP_MST_PORT_SUPPORT                     _OFF
#define _D1_DP_MST_PORT_SUPPORT                     _OFF
#else

#if(_D0_INPUT_PORT_TYPE != _D0_DP_PORT)
#undef _D0_DP_MST_PORT_SUPPORT
#define _D0_DP_MST_PORT_SUPPORT                     _OFF
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_DP_PORT)
#undef _D1_DP_MST_PORT_SUPPORT
#define _D1_DP_MST_PORT_SUPPORT                     _OFF
#endif

#endif

//--------------------------------------------------
// DP VSC SDP Option
//--------------------------------------------------
#if((_DP_SUPPORT == _ON) && (_HW_DP_VSC_SDP_EXT_CAPABILITY_SUPPORT == _ON) && (_ULTRA_HDR_SUPPORT == _ON))
#define _DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT     _ON
#else
#define _DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT     _OFF
#endif

//--------------------------------------------------
// MHL PS Without Power Cut Option
//--------------------------------------------------
#if((_SCALER_TYPE == _RL6193_SERIES) && (_MHL_SUPPORT == _ON))
#define _MHL_PS_WITHOUT_POWERCUT_SUPPORT            _ON
#else
#define _MHL_PS_WITHOUT_POWERCUT_SUPPORT            _OFF
#endif

//--------------------------------------------------
// MHL3.x Option
//--------------------------------------------------
#if((_MHL_3_0_SUPPORT == _ON) && (_MHL3_ECBUS_HID_SUPPORT == _ON))
#define _USB_SUPPORT                                _ON
#else
#define _USB_SUPPORT                                _OFF
#endif

//--------------------------------------------------
// Flash Idle Mode In Low Power Option
//--------------------------------------------------
#if((_SCALER_TYPE == _RL6193_SERIES) || (_SCALER_TYPE == _RL6410_SERIES) || (_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON))
#define _SYSTEM_LOW_POWER_IDLE_SUPPORT              _OFF
#endif

//--------------------------------------------------
// Watch Dog Timer Event Option
//--------------------------------------------------
#if((_HDMI_2_0_SUPPORT == _ON) || (_MHL_3_0_SUPPORT == _ON))
#define _WD_TIMER_INT_SUPPORT                       _ON
#else
#define _WD_TIMER_INT_SUPPORT                       _OFF
#endif

//--------------------------------------------------
// Record Timer Option
//--------------------------------------------------
#if(_MHL_3_0_SUPPORT == _ON)
#define _RECORD_TIMER_SUPPORT                       _ON
#else
#define _RECORD_TIMER_SUPPORT                       _OFF
#endif

//--------------------------------------------------
// Timer Event ID Enumeration & Structure
//--------------------------------------------------
#include _USER_TIMER_INCLUDE

typedef enum
{
    _SCALER_TIMER_EVENT_INVALID = 0x00,

#include _USER_TIMER_EVENT_ID_INCLUDE
    _USER_TIMER_EVENT_END,

#include "TimerEventIDSystem.h"
    _SYSTEM_TIMER_EVENT_END,

#include "TimerEventIDScaler.h"
    _SCALER_TIMER_EVENT_END,
} EnumScalerTimerEventID;

typedef struct
{
    EnumScalerTimerEventID enumEventID;
    WORD usTime;
} StructTimerEventTableType;

//--------------------------------------------------
// Timer Event Count
//--------------------------------------------------
#if((_HP_SOURCE_SCAN_SUPPORT == _ON) ||\
    (_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_ASUS_STYLE) ||\
    (_D6_INPUT_PORT_TYPE != _D6_NO_PORT) ||\
    (_D7_INPUT_PORT_TYPE != _D7_NO_PORT))
#define _SIMULTANEOUS_SYSTEM_EVENT_COUNT            4
#else
#define _SIMULTANEOUS_SYSTEM_EVENT_COUNT            3
#endif

#if(_DP_SUPPORT == _ON)
#define _SCALER_DP_EVENT_COUNT                      6
#else
#define _SCALER_DP_EVENT_COUNT                      0
#endif

#if(_DP_MST_SUPPORT == _ON)
#define _SCALER_DP_MST_EVENT_COUNT                  3
#else
#define _SCALER_DP_MST_EVENT_COUNT                  0
#endif

#if(_DP_TX_SUPPORT == _ON)
#define _SCALER_DP_TX_EVENT_COUNT                   3
#else
#define _SCALER_DP_TX_EVENT_COUNT                   0
#endif

#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
#if(_D0_MHL_VERSION >= _MHL_VERSION_3_0)
#define _RX0_MHL_SCALER_EVENT_COUNT                 5
#else
#define _RX0_MHL_SCALER_EVENT_COUNT                 3
#endif
#else
#define _RX0_MHL_SCALER_EVENT_COUNT                 0
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
#if(_D1_MHL_VERSION >= _MHL_VERSION_3_0)
#define _RX1_MHL_SCALER_EVENT_COUNT                 5
#else
#define _RX1_MHL_SCALER_EVENT_COUNT                 3
#endif
#else
#define _RX1_MHL_SCALER_EVENT_COUNT                 0
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
#if(_D2_MHL_VERSION >= _MHL_VERSION_3_0)
#define _RX2_MHL_SCALER_EVENT_COUNT                 5
#else
#define _RX2_MHL_SCALER_EVENT_COUNT                 3
#endif
#else
#define _RX2_MHL_SCALER_EVENT_COUNT                 0
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
#if(_D3_MHL_VERSION >= _MHL_VERSION_3_0)
#define _RX3_MHL_SCALER_EVENT_COUNT                 5
#else
#define _RX3_MHL_SCALER_EVENT_COUNT                 3
#endif
#else
#define _RX3_MHL_SCALER_EVENT_COUNT                 0
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
#if(_D4_MHL_VERSION >= _MHL_VERSION_3_0)
#define _RX4_MHL_SCALER_EVENT_COUNT                 5
#else
#define _RX4_MHL_SCALER_EVENT_COUNT                 3
#endif
#else
#define _RX4_MHL_SCALER_EVENT_COUNT                 0
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
#if(_D5_MHL_VERSION >= _MHL_VERSION_3_0)
#define _RX5_MHL_SCALER_EVENT_COUNT                 5
#else
#define _RX5_MHL_SCALER_EVENT_COUNT                 3
#endif
#else
#define _RX5_MHL_SCALER_EVENT_COUNT                 0
#endif

#define _SIMULTANEOUS_SCALER_EVENT_COUNT            (_SCALER_DP_EVENT_COUNT + _SCALER_DP_MST_EVENT_COUNT + _SCALER_DP_TX_EVENT_COUNT +\
                                                     _RX0_MHL_SCALER_EVENT_COUNT + _RX1_MHL_SCALER_EVENT_COUNT +\
                                                     _RX2_MHL_SCALER_EVENT_COUNT + _RX3_MHL_SCALER_EVENT_COUNT +\
                                                     _RX4_MHL_SCALER_EVENT_COUNT + _RX5_MHL_SCALER_EVENT_COUNT)

#define _TIMER_EVENT_COUNT                          (_SIMULTANEOUS_USER_EVENT_COUNT + _SIMULTANEOUS_SYSTEM_EVENT_COUNT + _SIMULTANEOUS_SCALER_EVENT_COUNT)

//--------------------------------------------------
// M2PLL is 243M
// Enumerations of Flash / MCU Speed
// Power Normal:        Flash = 40.5M,  MCU = 81M
// Power Normal Flash Low Speed:
//                      Flash = 20.25M, MCU = 40.5M
//
// M2PLL is 351M
// Enumerations of Flash / MCU Speed
// Power Normal:        Flash = 44M,    MCU = 88M
// Power Normal Flash Low Speed:
//                      Flash = 22M,    MCU = 44M
//
// Power Sav/Down 27:   Flash = 14M,  MCU = 28M for cache enable or Flash = 7M, MCU = 7M for no-cache or disable cache
// Power Saving DP:     Flash = 14M,  MCU = 28M for cache enable or Flash = 7M, MCU = 7M for no-cache or disable cache
// Power Initial:       Flash = 14.3M,  MCU = 14.3M
//--------------------------------------------------
typedef enum
{
#if(_M2PLL_FREQ_SEL == _M2PLL_FREQ_243M)

#if(_FLASH_CLK_SPEED == _FLASH_FAST_SPEED)
    _FLASH_CLK_DIV = _DIV_3,
#elif(_FLASH_CLK_SPEED == _FLASH_LOW_SPEED)
    _FLASH_CLK_DIV = _DIV_6,
    _FLASH_CLK_FAST_DIV = _DIV_3,
#endif

#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
    _FLASH_CLK_PS_DIV = _DIV_1,
#else

#if(_CACHE_PS_SWITCH == _ON)
    _FLASH_CLK_PS_DIV = _DIV_1,
#elif(_CACHE_PS_SWITCH == _OFF)
    _FLASH_CLK_PS_DIV = _DIV_4,
#endif

#endif

#elif(_M2PLL_FREQ_SEL == _M2PLL_FREQ_351M) // Else Of #if(_M2PLL_FREQ_SEL == _M2PLL_FREQ_243M)

#if(_FLASH_CLK_SPEED == _FLASH_FAST_SPEED)
    _FLASH_CLK_DIV = _DIV_4,
#elif(_FLASH_CLK_SPEED == _FLASH_LOW_SPEED)
    _FLASH_CLK_DIV = _DIV_8,
    _FLASH_CLK_FAST_DIV = _DIV_4,
#endif

#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
    _FLASH_CLK_PS_DIV = _DIV_1,
#else
    _FLASH_CLK_PS_DIV = _DIV_1,
#endif

#endif // End of #if(_M2PLL_FREQ_SEL == _M2PLL_FREQ_243M)

    _FLASH_CLK_IN_DIV = _DIV_1,
    _FLASH_CLK_PS_FAST_DIV = _DIV_1, // for DP
} EnumFlashClkDiv;

typedef enum
{
    _FLASH_2_CLK_IN_DIV = _DIV_1,
    _FLASH_2_CLK_DIV = _DIV_2,
#if(_M2PLL_FREQ_SEL == _M2PLL_FREQ_243M)

#if(_CACHE_PS_SWITCH == _ON)
    _FLASH_2_CLK_PS_DIV = _DIV_2,
#elif(_CACHE_PS_SWITCH == _OFF)
    _FLASH_2_CLK_PS_DIV = _DIV_1,
#endif

#elif(_M2PLL_FREQ_SEL == _M2PLL_FREQ_351M)
    _FLASH_2_CLK_PS_DIV = _DIV_2,
#endif

} EnumFlash2ClkDiv;

typedef enum
{
    _MCU_CLK_DIV = _DIV_1,
#if(_M2PLL_FREQ_SEL == _M2PLL_FREQ_243M)
    _MCU_CLK_PS_DIV = _DIV_1,
#elif(_M2PLL_FREQ_SEL == _M2PLL_FREQ_351M)
    _MCU_CLK_PS_DIV = _DIV_1,
#endif

    _MCU_CLK_IN_DIV = _DIV_1,
} EnumMcuClkDiv;

//--------------------------------------------------
// Urgent Event Check Mode
//--------------------------------------------------
#if(((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON)) || (_HDCP_2_2_SUPPORT == _ON))
#undef _URGENT_EVENT_CHECK_MODE
#define _URGENT_EVENT_CHECK_MODE                    _ON
#else
#undef _URGENT_EVENT_CHECK_MODE
#define _URGENT_EVENT_CHECK_MODE                    _OFF
#endif

#endif // End of #ifndef __SCALER_OPTION_H__
