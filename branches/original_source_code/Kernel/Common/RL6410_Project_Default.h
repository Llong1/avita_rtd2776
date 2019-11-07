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
// ID Code      : RL6410_Project_Default.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

/////////////
// General //
/////////////

//--------------------------------------------------
// Pcb Option
//--------------------------------------------------
#ifndef _PCB_TYPE
#define _PCB_TYPE                                               _RL6410_PCB_EXAMPLE
#endif

//--------------------------------------------------
// Panel Option
//--------------------------------------------------
#ifndef _PANEL_TYPE
#define _PANEL_TYPE                                             _PANEL_NONE
#endif

#ifndef _PANEL_POW_SEQ_FAST_MODE
#define _PANEL_POW_SEQ_FAST_MODE                                _ON
#endif

//==================== START ======================
#ifndef _PANEL_VBO_UNLOCK_MUTE_BY_FW_POLLING
#define _PANEL_VBO_UNLOCK_MUTE_BY_FW_POLLING                    _OFF
#endif

#ifndef _VBO_BACKLIGHT_BY_USER
#define _VBO_BACKLIGHT_BY_USER                                  _DISABLE
#endif
//===================== END =======================

//-------------------------------------------------
// Multi-Display Option
//-------------------------------------------------
#ifndef _PIP_DISPLAY_SUPPORT
#define _PIP_DISPLAY_SUPPORT                                    _OFF
#endif

#ifndef _PBP_LR_DISPLAY_SUPPORT
#define _PBP_LR_DISPLAY_SUPPORT                                 _OFF
#endif

#ifndef _PBP_TB_DISPLAY_SUPPORT
#define _PBP_TB_DISPLAY_SUPPORT                                 _OFF
#endif

#ifndef _4P_DISPLAY_SUPPORT
#define _4P_DISPLAY_SUPPORT                                     _OFF
#endif

//==================== START ======================

//--------------------------------------------------
// Multi-Display PIP Blending Option
//--------------------------------------------------
#ifndef _PIP_BLENDING_SUPPORT
#define _PIP_BLENDING_SUPPORT                                   _OFF
#endif

//--------------------------------------------------
// Multi-Display Default Option
//--------------------------------------------------
#ifndef _USER_DEFAULT_DISPLAY_MODE
#define _USER_DEFAULT_DISPLAY_MODE                              _DISPLAY_MODE_1P
#endif

#ifndef _USER_DEFAULT_AUTO_TARGET_INDEX
#define _USER_DEFAULT_AUTO_TARGET_INDEX                         _REGION_INDEX_0
#endif

#ifndef _USER_DEFAULT_SOURCE_SCAN_TYPE
#define _USER_DEFAULT_SOURCE_SCAN_TYPE                          _SOURCE_SWITCH_AUTO_IN_GROUP
#endif

#ifndef _USER_DEFAULT_INPUT_PORT_0
#define _USER_DEFAULT_INPUT_PORT_0                              _INPUT_PORT_SEARCH_PRI_0
#endif

#ifndef _USER_DEFAULT_INPUT_PORT_1
#define _USER_DEFAULT_INPUT_PORT_1                              _INPUT_PORT_SEARCH_PRI_1
#endif

#ifndef _USER_DEFAULT_INPUT_PORT_2
#define _USER_DEFAULT_INPUT_PORT_2                              _INPUT_PORT_SEARCH_PRI_2
#endif

#ifndef _USER_DEFAULT_INPUT_PORT_3
#define _USER_DEFAULT_INPUT_PORT_3                              _INPUT_PORT_SEARCH_PRI_3
#endif

//===================== END =======================

//--------------------------------------------------
// Osd Option
//--------------------------------------------------
#ifndef _OSD_TYPE
#define _OSD_TYPE                                               _NONE_OSD
#endif

//--------------------------------------------------
// OSD Window & Font Align to DEN Option
//--------------------------------------------------
#ifndef _OSD_POSITION_OFFSET_CORRECTION
#define _OSD_POSITION_OFFSET_CORRECTION                         _OFF
#endif

//--------------------------------------------------
// OSD Position Align Option
//--------------------------------------------------
#ifndef _OSD_POSITION_SELF_ALIGNMENT
#define _OSD_POSITION_SELF_ALIGNMENT                            _OFF
#endif

//==================== START ======================

//--------------------------------------------------
// Scaler or Translator Option
//--------------------------------------------------
#ifndef _TRANSLATOR_SUPPORT
#define _TRANSLATOR_SUPPORT                                     _OFF
#endif

//--------------------------------------------------
// Flash Partition
//--------------------------------------------------
#ifndef _FLASH_PARTITION_TYPE
#define _FLASH_PARTITION_TYPE                                   _FLASH_PARTITION_NONE
#endif

//===================== END =======================


///////////
// DDCCI //
///////////

//-------------------------------------------------
// DDCCI Option
//-------------------------------------------------
#ifndef _DDCCI0_RXBUF_LENGTH
#define _DDCCI0_RXBUF_LENGTH                                    16 // Only DDC-CI 0 can support OGC/OCC communication, Config length equal to 128 in OGC mode and 16 in other case
#endif

#ifndef _DDCCI_RXBUF_LENGTH
#define _DDCCI_RXBUF_LENGTH                                     16
#endif

#ifndef _DDCCI_TXBUF_LENGTH
#define _DDCCI_TXBUF_LENGTH                                     16
#endif

#ifndef _DDCCI_TIMEOUT_LIMIT
#define _DDCCI_TIMEOUT_LIMIT                                    50 // 0~65535ms
#endif

#ifndef _CAPABILITIES_STRING_VGA
#define _CAPABILITIES_STRING_VGA                                "(prot(monitor)type(LCD)model(RTK)cmds(01 02 03 07 0C E3 F3)vcp(02)mswhql(1)asset_eep(40)mccs_ver(2.2))"
#endif

#ifndef _CAPABILITIES_STRING_DVI
#define _CAPABILITIES_STRING_DVI                                "(prot(monitor)type(LCD)model(RTK)cmds(01 02 03 07 0C E3 F3)vcp(02)mswhql(1)asset_eep(40)mccs_ver(2.2))"
#endif

#ifndef _CAPABILITIES_STRING_HDMI
#define _CAPABILITIES_STRING_HDMI                               "(prot(monitor)type(LCD)model(RTK)cmds(01 02 03 07 0C E3 F3)vcp(02)mswhql(1)asset_eep(40)mccs_ver(2.2))"
#endif

#ifndef _CAPABILITIES_STRING_DP
#define _CAPABILITIES_STRING_DP                                 "(prot(monitor)type(LCD)model(RTK)cmds(01 02 03 07 0C E3 F3)vcp(02)mswhql(1)asset_eep(40)mccs_ver(2.2))"
#endif

//==================== START ======================

//-------------------------------------------------
// DDCCI Auto Switch Option
//-------------------------------------------------
#ifndef _DDCCI_AUTO_SWITCH_SUPPORT
#define _DDCCI_AUTO_SWITCH_SUPPORT                              _OFF
#endif

//-------------------------------------------------
// DDCCI On Line Display Calibration OP Code Option
//-------------------------------------------------
#ifndef _DDCCI_OPCODE_VCP_DISP_CALIBRATION
#define _DDCCI_OPCODE_VCP_DISP_CALIBRATION                      0xFC
#endif

//===================== END =======================


/////////////////////
// Display Setting //
/////////////////////

//-------------------------------------------------
// OD Option
//-------------------------------------------------
#ifndef _OD_SUPPORT
#define _OD_SUPPORT                                             _OFF
#endif

//-------------------------------------------------
// FRC Option
//-------------------------------------------------
#ifndef _FRC_SUPPORT
#define _FRC_SUPPORT                                            _OFF
#endif

//-------------------------------------------------
// Display Rotation Option
//-------------------------------------------------
#ifndef _DISPLAY_ROTATION_SUPPORT
#define _DISPLAY_ROTATION_SUPPORT                               _OFF
#endif

//==================== START ======================
#ifndef _DISPLAY_HOR_MIRROR_SUPPORT
#define _DISPLAY_HOR_MIRROR_SUPPORT                             _OFF
#endif

#ifndef _DISPLAY_VER_MIRROR_SUPPORT
#define _DISPLAY_VER_MIRROR_SUPPORT                             _OFF
#endif
//===================== END =======================

//--------------------------------------------------
// Aspect Ratio Option
//--------------------------------------------------
#ifndef _ASPECT_RATIO_SUPPORT
#define _ASPECT_RATIO_SUPPORT                                   _OFF
#endif

#ifndef _ASPECT_ORIGINAL_MODE_SUPPORT
#define _ASPECT_ORIGINAL_MODE_SUPPORT                           _OFF
#endif

//--------------------------------------------------
// Overscan Option
//--------------------------------------------------
#ifndef _OVERSCAN_VGA_SUPPORT
#define _OVERSCAN_VGA_SUPPORT                                   _OFF
#endif

#ifndef _OVERSCAN_DVI_SUPPORT
#define _OVERSCAN_DVI_SUPPORT                                   _OFF
#endif

#ifndef _OVERSCAN_HDMI_SUPPORT
#define _OVERSCAN_HDMI_SUPPORT                                  _OFF
#endif

#ifndef _OVERSCAN_DP_SUPPORT
#define _OVERSCAN_DP_SUPPORT                                    _OFF
#endif

#ifndef _OVERSCAN_H_RATIO
#define _OVERSCAN_H_RATIO                                       30
#endif

#ifndef _OVERSCAN_V_RATIO
#define _OVERSCAN_V_RATIO                                       30
#endif

//-------------------------------------------------
// Adjust H & V Position Max Range Option
//-------------------------------------------------
#ifndef _MAX_H_POSITION_RANGE
#define _MAX_H_POSITION_RANGE                                   100 // Pixel
#endif

#ifndef _MAX_V_POSITION_RANGE
#define _MAX_V_POSITION_RANGE                                   100 // Line
#endif

//==================== START ======================

//-------------------------------------------------
// Force Display Free Run Option --> For Last Line Issue Panel
//-------------------------------------------------
#ifndef _FORCE_TO_FREE_RUN_SUPPORT
#define _FORCE_TO_FREE_RUN_SUPPORT                              _OFF
#endif

//--------------------------------------------------
// Display Frame Sync Line Buffer Option
//--------------------------------------------------
#ifndef _FRAME_SYNC_LINE_BUFFER_SUPPORT
#define _FRAME_SYNC_LINE_BUFFER_SUPPORT                         _OFF
#endif

//-------------------------------------------------
// Freeze Mode Option
//-------------------------------------------------
#ifndef _FREEZE_SUPPORT
#define _FREEZE_SUPPORT                                         _OFF
#endif

#ifndef _ROTATION_FREEZE_FORCE_TO_BACKGROUND
#define _ROTATION_FREEZE_FORCE_TO_BACKGROUND                    _OFF
#endif

//--------------------------------------------------
// Display Frame Sync Frame Buffer Latency Option
//--------------------------------------------------
#ifndef _DISP_LATENCY_ADJUST_SUPPORT
#define _DISP_LATENCY_ADJUST_SUPPORT                            _OFF
#endif

//--------------------------------------------------
// Force Even/Odd Mode Option
//--------------------------------------------------
#ifndef _FORMAT_CONVERSION_FORCE_EO_MODE
#define _FORMAT_CONVERSION_FORCE_EO_MODE                        _OFF
#endif

//===================== END =======================


////////////////////
// Color Function //
////////////////////

//--------------------------------------------------
// Digital Functional Option
//--------------------------------------------------
#ifndef _I_DITHER_SUPPORT
#define _I_DITHER_SUPPORT                                       _OFF
#endif

#ifndef _D_DITHER_SUPPORT
#define _D_DITHER_SUPPORT                                       _OFF
#endif

#ifndef _GAMMA_FUNCTION
#define _GAMMA_FUNCTION                                         _OFF
#endif

#ifndef _COLOR_FORMAT_CONVERT
#define _COLOR_FORMAT_CONVERT                                   _OFF
#endif

#ifndef _RGB_QUANTIZATION_RANGE_SUPPORT
#define _RGB_QUANTIZATION_RANGE_SUPPORT                         _OFF
#endif

#ifndef _YCC_QUANTIZATION_RANGE_SUPPORT
#define _YCC_QUANTIZATION_RANGE_SUPPORT                         _OFF
#endif

#ifndef _ULTRA_VIVID_SUPPORT
#define _ULTRA_VIVID_SUPPORT                                    _OFF
#endif

#ifndef _DCR_SUPPORT
#define _DCR_SUPPORT                                            _OFF
#endif

#ifndef _DCC_FUNCTION
#define _DCC_FUNCTION                                           _OFF
#endif

#ifndef _DCC_HISTOGRM_INFO
#define _DCC_HISTOGRM_INFO                                      _OFF
#endif

#ifndef _ICM_SUPPORT
#define _ICM_SUPPORT                                            _OFF
#endif

#ifndef _ICM_BRI_SUPPORT
#define _ICM_BRI_SUPPORT                                        _OFF
#endif

#ifndef _SCM_SUPPORT
#define _SCM_SUPPORT                                            _OFF
#endif

#ifndef _SIX_COLOR_SUPPORT
#define _SIX_COLOR_SUPPORT                                      _OFF
#endif

#ifndef _SIX_COLOR_ICM_TYPE
#define _SIX_COLOR_ICM_TYPE                                     _SIX_COLOR_ICM_NORMAL_MODE
#endif

#ifndef _HIGHLIGHT_WINDOW_SUPPORT
#define _HIGHLIGHT_WINDOW_SUPPORT                               _OFF
#endif

#ifndef _RINGING_FILTER_SUPPORT
#define _RINGING_FILTER_SUPPORT                                 _OFF
#endif

#ifndef _BORDER_WINDOW_SUPPORT
#define _BORDER_WINDOW_SUPPORT                                  _OFF
#endif

#ifndef _SHARPNESS_SUPPORT
#define _SHARPNESS_SUPPORT                                      _OFF
#endif

#ifndef _CONTRAST_SUPPORT
#define _CONTRAST_SUPPORT                                       _OFF
#endif

#ifndef _BRIGHTNESS_SUPPORT
#define _BRIGHTNESS_SUPPORT                                     _OFF
#endif

//-------------------------------------------------
// Hue and Saturation Option
//-------------------------------------------------
#ifndef _GLOBAL_HUE_SATURATION
#define _GLOBAL_HUE_SATURATION                                  _OFF
#endif

#ifndef _HUE_MAX
#define _HUE_MAX                                                230
#endif

#ifndef _HUE_MIN
#define _HUE_MIN                                                30
#endif

#ifndef _SATURATION_MAX
#define _SATURATION_MAX                                         200
#endif

#ifndef _SATURATION_MIN
#define _SATURATION_MIN                                         0
#endif

//-------------------------------------------------
// IAPS Option
//-------------------------------------------------
#ifndef _IAPS_SUPPORT
#define _IAPS_SUPPORT                                           _OFF
#endif

//==================== START ======================
#ifndef _IAPS_CONTRAST_TARGET
#define _IAPS_CONTRAST_TARGET                                   0x2000
#endif

#ifndef _IAPS_GAIN_CLAMP_FACTOR
#define _IAPS_GAIN_CLAMP_FACTOR                                 0xB0
#endif

//--------------------------------------------------
// Force YUV format conversion Option
//--------------------------------------------------
#ifndef _M_DOMAIN_FORCE_YUV_FORMAT
#define _M_DOMAIN_FORCE_YUV_FORMAT                              _OFF
#endif

//===================== END ======================


////////////////////////////////////////
// Off-Line Display Color Calibration //
////////////////////////////////////////

//-------------------------------------------------
// PCM (Load Code Table) Option
//-------------------------------------------------
#ifndef _PCM_FUNCTION
#define _PCM_FUNCTION                                           _OFF
#endif

//-------------------------------------------------
// 3D Gamma (Load Code Table) Option
//-------------------------------------------------
#ifndef _RGB_3D_GAMMA
#define _RGB_3D_GAMMA                                           _OFF
#endif

//-------------------------------------------------
// RGB Gamma (Load Code Table) Option
//-------------------------------------------------
#ifndef _RGB_GAMMA_FUNCTION
#define _RGB_GAMMA_FUNCTION                                     _OFF
#endif

//--------------------------------------------------
// False Color Option
//--------------------------------------------------
#ifndef _FALSE_COLOR_SUPPORT
#define _FALSE_COLOR_SUPPORT                                    _OFF
#endif


////////////////////////////////////////
// On-Line Display Color Calibration //
////////////////////////////////////////

//-------------------------------------------------
// OGC and OCC (On-Line Calibration) Option
//-------------------------------------------------
#ifndef _OCC_SUPPORT
#define _OCC_SUPPORT                                            _OFF
#endif

#ifndef _OGC_SUPPORT
#define _OGC_SUPPORT                                            _OFF
#endif

#ifndef _OGC_DICOM_SUPPORT
#define _OGC_DICOM_SUPPORT                                      _OFF
#endif

#ifndef _OGC_TOTAL_GAMMA
#define _OGC_TOTAL_GAMMA                                        1 // 1/2/3/4/5
#endif

#ifndef _OGC_TOTAL_CT
#define _OGC_TOTAL_CT                                           1
#endif

#ifndef _OGC_FLASH_BANK
#define _OGC_FLASH_BANK                                         0
#endif

#ifndef _OGC_FLASH_PAGE
#define _OGC_FLASH_PAGE                                         0
#endif

//-------------------------------------------------
// Uniformity (On-Line Calibration) Option
//-------------------------------------------------
#ifndef _UNIFORMITY_SUPPORT
#define _UNIFORMITY_SUPPORT                                     _OFF
#endif

#ifndef _UNIFORMITY_TOTAL_SET
#define _UNIFORMITY_TOTAL_SET                                   1 // 1/2/3/4/5/6
#endif

#ifndef _UNIFORMITY_FLASH_BANK0
#define _UNIFORMITY_FLASH_BANK0                                 0
#endif

#ifndef _UNIFORMITY_FLASH_PAGE
#define _UNIFORMITY_FLASH_PAGE                                  0
#endif

//==================== START ======================
#ifndef _PANEL_UNIFORMITY_MULTI_LUT_MODE
#define _PANEL_UNIFORMITY_MULTI_LUT_MODE                        _UNIFORMITY_1LEVEL
#endif

#ifndef _UNIFORMITY_LEVEL0_SUPPORT
#define _UNIFORMITY_LEVEL0_SUPPORT                              _OFF
#endif

#ifndef _UNIFORMITY_OFFSET_TYPE0
#define _UNIFORMITY_OFFSET_TYPE0                                _OFF
#endif

#ifndef _UNIFORMITY_OFFSET_TYPE1
#define _UNIFORMITY_OFFSET_TYPE1                                _OFF
#endif

#ifndef _UNIFORMITY_OFFSET_TYPE2
#define _UNIFORMITY_OFFSET_TYPE2                                _OFF
#endif

#ifndef _UNIFORMITY_OFFSET_TYPE3
#define _UNIFORMITY_OFFSET_TYPE3                                _OFF
#endif

#ifndef _UNIFORMITY_OFFSET_TYPE4
#define _UNIFORMITY_OFFSET_TYPE4                                _OFF
#endif

#ifndef _UNIFORMITY_OFFSET_TYPE5
#define _UNIFORMITY_OFFSET_TYPE5                                _OFF
#endif
//===================== END ======================

//-------------------------------------------------
// ULTRA HDR (On-Line Calibration) Option
//-------------------------------------------------
#ifndef _ULTRA_HDR_SUPPORT
#define _ULTRA_HDR_SUPPORT                                      _OFF
#endif


////////////
// Eeprom //
////////////

//-------------------------------------------------
// Eeprom Access Function Option
//-------------------------------------------------
#ifndef _EEPROM_ACCESS_FUNCTION_SUPPORT
#define _EEPROM_ACCESS_FUNCTION_SUPPORT                         _OFF
#endif

#ifndef _EEPROM_KERNEL_START_ADDRESS
#define _EEPROM_KERNEL_START_ADDRESS                            (_EEPROM_PAGE0_BANK0)
#endif


///////////
// Flash //
///////////

//-------------------------------------------------
// Flash Clock Option
//-------------------------------------------------
#ifndef _FLASH_CLK_SPEED
#define _FLASH_CLK_SPEED                                        _FLASH_FAST_SPEED
#endif

//-------------------------------------------------
// Flash Access Function Option
//-------------------------------------------------
#ifndef _FLASH_ACCESS_FUNCTION_SUPPORT
#define _FLASH_ACCESS_FUNCTION_SUPPORT                          _OFF
#endif

#ifndef _FLASH_TYPE_W25X20A_OR_W25X21CL
#define _FLASH_TYPE_W25X20A_OR_W25X21CL                         _FLASH_W25X20A
#endif

#ifndef _FLASH_TYPE_W25X40CL_OR_W25X41CL
#define _FLASH_TYPE_W25X40CL_OR_W25X41CL                        _FLASH_W25X40CL
#endif

#ifndef _FLASH_TYPE_GD25Q16C_OR_GD25Q16
#define _FLASH_TYPE_GD25Q16C_OR_GD25Q16                         _FLASH_GD25Q16C
#endif

#ifndef _FLASH_TYPE_MX25L3206E_OR_MX25L3233F
#define _FLASH_TYPE_MX25L3206E_OR_MX25L3233F                    _FLASH_MX25L3233F
#endif

//-------------------------------------------------
// EEPROM Emulation Option
//-------------------------------------------------
#ifndef _SYSTEM_EEPROM_EMULATION_SUPPORT
#define _SYSTEM_EEPROM_EMULATION_SUPPORT                        _OFF
#endif

#ifndef _SYSTEM_EEPROM_EMULATION_FLASH_BANK
#define _SYSTEM_EEPROM_EMULATION_FLASH_BANK                     0
#endif

#ifndef _SYSTEM_EEPROM_EMULATION_START_PAGE
#define _SYSTEM_EEPROM_EMULATION_START_PAGE                     0
#endif

#ifndef _SYSTEM_EEPROM_EMULATION_END_PAGE
#define _SYSTEM_EEPROM_EMULATION_END_PAGE                       0
#endif

#ifndef _START_OF_PAGEID
#define _START_OF_PAGEID                                        _PAGEID_0
#endif

#ifndef _END_OF_PAGEID
#define _END_OF_PAGEID                                          _PAGEID_0
#endif

#ifndef _CHECKSUM_VERSIONCODE_ID
#define _CHECKSUM_VERSIONCODE_ID                                _PAGEID_0
#endif


//////////
// EDID //
//////////

//-------------------------------------------------
// EDID Location Option
//-------------------------------------------------
#ifndef _EDID_ADDRESS_EEPROM
#define _EDID_ADDRESS_EEPROM                                    (_EEPROM_PAGE0_BANK0)
#endif

#ifndef _EDID_ADDRESS_FLASH
#define _EDID_ADDRESS_FLASH                                     (0)
#endif

#ifndef _EDID_FLASH_BANK
#define _EDID_FLASH_BANK                                        (0)
#endif

//==================== START ======================
#ifndef _WRITE_EDID_TO_SYSTEM_EEPROM
#define _WRITE_EDID_TO_SYSTEM_EEPROM                            _OFF
#endif
//===================== END =======================


//////////////
// HDCP Key //
//////////////

//-------------------------------------------------
// HDCP Key Location Option
//-------------------------------------------------
#ifndef _HDCP_1_4_KEY_LOCATION
#define _HDCP_1_4_KEY_LOCATION                                  _TABLE_LOCATION_SYSTEM_EEPROM
#endif

#ifndef _HDCP_2_2_KEY_LOCATION
#define _HDCP_2_2_KEY_LOCATION                                  _TABLE_LOCATION_CODE
#endif

#ifndef _RX_HDCP_1_4_KEY_ADDRESS_EEPROM
#define _RX_HDCP_1_4_KEY_ADDRESS_EEPROM                         (_EEPROM_PAGE0_BANK0)
#endif

#ifndef _RX_HDCP_1_4_KEY_ADDRESS_FLASH
#define _RX_HDCP_1_4_KEY_ADDRESS_FLASH                          (0)
#endif

#ifndef _RX_HDCP_1_4_KEY_FLASH_BANK
#define _RX_HDCP_1_4_KEY_FLASH_BANK                             (0)
#endif

#ifndef _RX_HDCP_2_2_KEY_ADDRESS_EEPROM
#define _RX_HDCP_2_2_KEY_ADDRESS_EEPROM                         (_EEPROM_PAGE0_BANK0)
#endif

#ifndef _RX_HDCP_2_2_KEY_ADDRESS_FLASH
#define _RX_HDCP_2_2_KEY_ADDRESS_FLASH                          (0)
#endif

#ifndef _RX_HDCP_2_2_KEY_FLASH_BANK
#define _RX_HDCP_2_2_KEY_FLASH_BANK                             (0)
#endif

#ifndef _TX_HDCP_KEY_ADDRESS_EEPROM
#define _TX_HDCP_KEY_ADDRESS_EEPROM                             (_EEPROM_PAGE0_BANK0)
#endif

#ifndef _TX_HDCP_KEY_ADDRESS_FLASH
#define _TX_HDCP_KEY_ADDRESS_FLASH                              (0)
#endif

#ifndef _TX_HDCP_KEY_FLASH_BANK
#define _TX_HDCP_KEY_FLASH_BANK                                 (0)
#endif

//==================== START ======================
#ifndef _WRITE_HDCP_TO_SYSTEM_EEPROM
#define _WRITE_HDCP_TO_SYSTEM_EEPROM                            _OFF
#endif
//===================== END =======================


///////////////////
// System Source //
///////////////////

//-------------------------------------------------
// System Auto Search Style Option
//-------------------------------------------------
#ifndef _SOURCE_AUTO_SEARCH_STYLE
#define _SOURCE_AUTO_SEARCH_STYLE                               _SOURCE_POLLING_IN_SEARCH_STATE
#endif

//-------------------------------------------------
// System Source Search Time Option
//-------------------------------------------------
#ifndef _SOURCE_DEFAULT_SEARCH_TIME_VGA
#define _SOURCE_DEFAULT_SEARCH_TIME_VGA                         SEC(0.5)
#endif

#ifndef _SOURCE_DEFAULT_SEARCH_TIME_HDMI
#define _SOURCE_DEFAULT_SEARCH_TIME_HDMI                        SEC(2)
#endif

#ifndef _SOURCE_DEFAULT_SEARCH_TIME_DVI
#define _SOURCE_DEFAULT_SEARCH_TIME_DVI                         SEC(2)
#endif

#ifndef _SOURCE_DEFAULT_SEARCH_TIME_DP
#define _SOURCE_DEFAULT_SEARCH_TIME_DP                          SEC(3)
#endif

//==================== START ======================

//-------------------------------------------------
// System Default Search Time for all Port --> (_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_IN_SEARCH_STATE)
//-------------------------------------------------
#ifndef _SOURCE_DEFAULT_SEARCH_TIME_ALL_PORT
#define _SOURCE_DEFAULT_SEARCH_TIME_ALL_PORT                    SEC(2)
#endif

//-------------------------------------------------
// System Default Search Time When No Cable Option
//-------------------------------------------------
#ifndef _SOURCE_DEFAULT_SEARCH_TIME_VGA_NO_CABLE
#define _SOURCE_DEFAULT_SEARCH_TIME_VGA_NO_CABLE                SEC(0.5)
#endif

#ifndef _SOURCE_DEFAULT_SEARCH_TIME_HDMI_NO_CABLE
#define _SOURCE_DEFAULT_SEARCH_TIME_HDMI_NO_CABLE               SEC(2)
#endif

#ifndef _SOURCE_DEFAULT_SEARCH_TIME_DVI_NO_CABLE
#define _SOURCE_DEFAULT_SEARCH_TIME_DVI_NO_CABLE                SEC(2)
#endif

#ifndef _SOURCE_DEFAULT_SEARCH_TIME_DP_NO_CABLE
#define _SOURCE_DEFAULT_SEARCH_TIME_DP_NO_CABLE                 SEC(3)
#endif

//-------------------------------------------------
// System Required Time for External or Embedded DP Switch
//-------------------------------------------------
#ifndef _SOURCE_DP_SWITCH_TIMEOUT_TIME
#define _SOURCE_DP_SWITCH_TIMEOUT_TIME                          SEC(4)
#endif

//-------------------------------------------------
// System Required Time for for DP Dual EDID
//-------------------------------------------------
#ifndef _SOURCE_DP_DUAL_SWITCH_TIMEOUT_TIME
#define _SOURCE_DP_DUAL_SWITCH_TIMEOUT_TIME                     SEC(4)
#endif

//--------------------------------------------------
// Double Check NVRAM Port When Searching In Polling Mode Option
//--------------------------------------------------
#ifndef _SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT
#define _SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT                 _OFF
#endif

#ifndef _SOURCE_DOUBLE_CHECK_SEARCH_TIME_NVRAM_PORT
#define _SOURCE_DOUBLE_CHECK_SEARCH_TIME_NVRAM_PORT             SEC(0.5)
#endif

//===================== END =======================


//////////////////
// System Judge //
//////////////////

//-------------------------------------------------
// System Display Setting Check Time Option
//-------------------------------------------------
#ifndef _WAIT_TIME_TO_ACTIVE_VGA
#define _WAIT_TIME_TO_ACTIVE_VGA                                SEC(0.05)
#endif

#ifndef _WAIT_TIME_TO_ACTIVE_DVI
#define _WAIT_TIME_TO_ACTIVE_DVI                                SEC(0.1)
#endif

#ifndef _WAIT_TIME_TO_ACTIVE_HDMI
#define _WAIT_TIME_TO_ACTIVE_HDMI                               SEC(0.1)
#endif

#ifndef _WAIT_TIME_TO_ACTIVE_DP
#define _WAIT_TIME_TO_ACTIVE_DP                                 SEC(0.1)
#endif

//--------------------------------------------------
// System Support Timing Option
//--------------------------------------------------
#ifndef _OOR_H_FREQ_UPPER_BOUND
#define _OOR_H_FREQ_UPPER_BOUND                                 2200 // Unit in 0.1 kHZ
#endif

#ifndef _OOR_H_FREQ_LOWER_BOUND
#define _OOR_H_FREQ_LOWER_BOUND                                 100  // Unit in 0.1 kHZ
#endif

#ifndef _OOR_V_FREQ_UPPER_BOUND
#define _OOR_V_FREQ_UPPER_BOUND                                 1500 // Unit in 0.1 HZ
#endif

#ifndef _OOR_V_FREQ_LOWER_BOUND
#define _OOR_V_FREQ_LOWER_BOUND                                 230  // Unit in 0.1 HZ
#endif

#ifndef _OOR_H_WIDTH_UPPER_BOUND
#define _OOR_H_WIDTH_UPPER_BOUND                                4096 // Unit in pixel
#endif

#ifndef _OOR_V_HEIGHT_LOWER_BOUND
#define _OOR_V_HEIGHT_LOWER_BOUND                               240  // Unit in line
#endif

#ifndef _FAIL_SAVE_H_FREQ_UPPER_BOUND
#define _FAIL_SAVE_H_FREQ_UPPER_BOUND                           2200 // Unit in 0.1 kHZ
#endif

#ifndef _FAIL_SAVE_H_FREQ_LOWER_BOUND
#define _FAIL_SAVE_H_FREQ_LOWER_BOUND                           110  // Unit in 0.1 kHZ
#endif

#ifndef _FAIL_SAVE_V_FREQ_UPPER_BOUND
#define _FAIL_SAVE_V_FREQ_UPPER_BOUND                           1500 // Unit in 0.1 HZ
#endif

#ifndef _FAIL_SAVE_V_FREQ_LOWER_BOUND
#define _FAIL_SAVE_V_FREQ_LOWER_BOUND                           230  // Unit in 0.1 HZ
#endif

#ifndef _INPUTCLOCK_RANG_VGA
#define _INPUTCLOCK_RANG_VGA                                    2100 // Unit in 0.1 MHz
#endif

#ifndef _INPUTCLOCK_RANG_DVI
#define _INPUTCLOCK_RANG_DVI                                    3300 // Unit in 0.1 MHz
#endif

#ifndef _INPUTCLOCK_RANG_HDMI
#define _INPUTCLOCK_RANG_HDMI                                   6000 // Unit in 0.1 MHz
#endif

#ifndef _INPUTCLOCK_RANG_DP
#define _INPUTCLOCK_RANG_DP                                     6000 // Unit in 0.1 MHz
#endif


/////////
// VGA //
/////////

//--------------------------------------------------
// VGA YPBPR Option
//--------------------------------------------------
#ifndef _YPBPR_SUPPORT
#define _YPBPR_SUPPORT                                          _ON
#endif

#ifndef _SOG_SUPPORT
#define _SOG_SUPPORT                                            _ON
#endif

#ifndef _VGA_COMPOSITE_SUPPORT
#define _VGA_COMPOSITE_SUPPORT                                  _ON
#endif

//--------------------------------------------------
// VGA Mode Search condition reference by picture width Option
//--------------------------------------------------
#ifndef _MODE_SEARCH_BY_ACTIVE_MEASURE_SUPPORT
#define _MODE_SEARCH_BY_ACTIVE_MEASURE_SUPPORT                  _OFF
#endif

//--------------------------------------------------
// VGA Auto Adjust Clock Setup Option
//--------------------------------------------------
#ifndef _AUTO_CLOCK_STEP
#define _AUTO_CLOCK_STEP                                        2  // 1 or 2
#endif

#ifndef _AUTO_CLOCK_RANGE
#define _AUTO_CLOCK_RANGE                                       95 // Set Clock Non-adjusting Range (%) by the active region
#endif

#ifndef _AUTO_TOLERANCE_PIXEL
#define _AUTO_TOLERANCE_PIXEL                                   2  // Definitions Of tolerance pixel for Auto Clock
#endif

#ifndef _AUTO_CLOCK_SAVE_VALUE_OPTION
#define _AUTO_CLOCK_SAVE_VALUE_OPTION                           _CLOCK_SAVE_PERCENT_VALUE
#endif

//--------------------------------------------------
// VGA Gain & Offset Defualt Option
//--------------------------------------------------
#ifndef _ADC_RGB_DEFAULT_RED_GAIN
#define _ADC_RGB_DEFAULT_RED_GAIN                               128
#endif

#ifndef _ADC_RGB_DEFAULT_GREEN_GAIN
#define _ADC_RGB_DEFAULT_GREEN_GAIN                             128
#endif

#ifndef _ADC_RGB_DEFAULT_BLUE_GAIN
#define _ADC_RGB_DEFAULT_BLUE_GAIN                              128
#endif

#ifndef _ADC_RGB_DEFAULT_RED_OFFSET
#define _ADC_RGB_DEFAULT_RED_OFFSET                             128
#endif

#ifndef _ADC_RGB_DEFAULT_GREEN_OFFSET
#define _ADC_RGB_DEFAULT_GREEN_OFFSET                           128
#endif

#ifndef _ADC_RGB_DEFAULT_BLUE_OFFSET
#define _ADC_RGB_DEFAULT_BLUE_OFFSET                            128
#endif

#ifndef _ADC_YPBPR_DEFAULT_Y_GAIN
#define _ADC_YPBPR_DEFAULT_Y_GAIN                               159
#endif

#ifndef _ADC_YPBPR_DEFAULT_PB_GAIN
#define _ADC_YPBPR_DEFAULT_PB_GAIN                              154
#endif

#ifndef _ADC_YPBPR_DEFAULT_PR_GAIN
#define _ADC_YPBPR_DEFAULT_PR_GAIN                              154
#endif

#ifndef _ADC_YPBPR_DEFAULT_Y_OFFSET
#define _ADC_YPBPR_DEFAULT_Y_OFFSET                             112
#endif

#ifndef _ADC_YPBPR_DEFAULT_PB_OFFSET
#define _ADC_YPBPR_DEFAULT_PB_OFFSET                            128
#endif

#ifndef _ADC_YPBPR_DEFAULT_PR_OFFSET
#define _ADC_YPBPR_DEFAULT_PR_OFFSET                            128
#endif

//==================== START ======================
#ifndef _ADC_RGB_DEFAULT_PGA_VALUE
#define _ADC_RGB_DEFAULT_PGA_VALUE                              8 // 0 ~ 15
#endif

#ifndef _ADC_YPBPR_DEFAULT_PGA_VALUE
#define _ADC_YPBPR_DEFAULT_PGA_VALUE                            8 // 0 ~ 15
#endif
//===================== END =======================

//--------------------------------------------------
// VGA Self-Calibration Option
//--------------------------------------------------
#ifndef _ADC_SELF_CALIBRATION
#define _ADC_SELF_CALIBRATION                                   _OFF
#endif

#ifndef _CALIBRATION_R_GAIN_BIAS
#define _CALIBRATION_R_GAIN_BIAS                                (0)  // Needs modification for EVERY single source
#endif

#ifndef _CALIBRATION_G_GAIN_BIAS
#define _CALIBRATION_G_GAIN_BIAS                                (0)  // Needs modification for EVERY single source
#endif

#ifndef _CALIBRATION_B_GAIN_BIAS
#define _CALIBRATION_B_GAIN_BIAS                                (0)  // Needs modification for EVERY single source
#endif

#ifndef _CALIBRATION_R_OFFSET_BIAS
#define _CALIBRATION_R_OFFSET_BIAS                              (-3) // Needs modification for EVERY single source
#endif

#ifndef _CALIBRATION_G_OFFSET_BIAS
#define _CALIBRATION_G_OFFSET_BIAS                              (-3) // Needs modification for EVERY single source
#endif

#ifndef _CALIBRATION_B_OFFSET_BIAS
#define _CALIBRATION_B_OFFSET_BIAS                              (-3) // Needs modification for EVERY single source
#endif

//==================== START ======================
#ifndef _SELF_CALIBRATION_CLK
#define _SELF_CALIBRATION_CLK                                   (148) // MHz
#endif
//===================== END =======================

//--------------------------------------------------
// VGA YPBPR Auto Color Method Option
//--------------------------------------------------
#ifndef _YPBPR_AUTO_METHOD
#define _YPBPR_AUTO_METHOD                                      _YPBPR_AUTO_BY_SOURCE
#endif

#ifndef _AUTO_PB_GAIN_BIAS
#define _AUTO_PB_GAIN_BIAS                                      (5)
#endif

#ifndef _AUTO_PR_GAIN_BIAS
#define _AUTO_PR_GAIN_BIAS                                      (5)
#endif

#ifndef _AUTO_Y_GAIN_BIAS
#define _AUTO_Y_GAIN_BIAS                                       (0)
#endif

#ifndef _AUTO_PB_OFFSET_BIAS
#define _AUTO_PB_OFFSET_BIAS                                    (-8)
#endif

#ifndef _AUTO_PR_OFFSET_BIAS
#define _AUTO_PR_OFFSET_BIAS                                    (-8)
#endif

#ifndef _AUTO_Y_OFFSET_BIAS
#define _AUTO_Y_OFFSET_BIAS                                     (-16)
#endif

//--------------------------------------------------
// VGA Digital Filter Option
//--------------------------------------------------
#ifndef _DIG_FILTER_NSMEAR_ENABLE
#define _DIG_FILTER_NSMEAR_ENABLE                               _ENABLE
#endif

#ifndef _DIG_FILTER_PSMEAR_ENABLE
#define _DIG_FILTER_PSMEAR_ENABLE                               _ENABLE
#endif

#ifndef _DIG_FILTER_NRING_ENABLE
#define _DIG_FILTER_NRING_ENABLE                                _ENABLE
#endif

#ifndef _DIG_FILTER_PRING_ENABLE
#define _DIG_FILTER_PRING_ENABLE                                _ENABLE
#endif

#ifndef _DIG_FILTER_EXTENSION_ENABLE
#define _DIG_FILTER_EXTENSION_ENABLE                            _ENABLE
#endif

#ifndef _DIG_FILTER_ENHANCE_PHASE_ENABLE
#define _DIG_FILTER_ENHANCE_PHASE_ENABLE                        _ENABLE
#endif

//==================== START ======================

//--------------------------------------------------
// VGA Digital Phase Filter Option
//--------------------------------------------------
#ifndef _DIG_FILTER_PHASE_ENABLE
#define _DIG_FILTER_PHASE_ENABLE                                _ENABLE
#endif

#ifndef _DIG_FILTER_PHASE_THD
#define _DIG_FILTER_PHASE_THD                                   192 // effective:0~255
#endif

#ifndef _DIG_FILTER_PHASE_DIV_VALUE
#define _DIG_FILTER_PHASE_DIV_VALUE                             0   // effective:0~3
#endif

#ifndef _DIG_FILTER_PHASE_HIGHFREQ_ADCCLOCKTHD
#define _DIG_FILTER_PHASE_HIGHFREQ_ADCCLOCKTHD                  0   // effective:0~210 (MHz)
#endif

#ifndef _DIG_FILTER_PHASE_HIGHFREQ_THD
#define _DIG_FILTER_PHASE_HIGHFREQ_THD                          160 // effective:0~255
#endif

#ifndef _DIG_FILTER_PHASE_HIGHFREQ_DIV_VALUE
#define _DIG_FILTER_PHASE_HIGHFREQ_DIV_VALUE                    0   // effective:0~3
#endif

//--------------------------------------------------
// VGA Chroma Pattern 12 Option
//--------------------------------------------------
#ifndef _VGA_CHROMA_PATTERN12_SUPPORT
#define _VGA_CHROMA_PATTERN12_SUPPORT                           _OFF
#endif

//--------------------------------------------------
// VGA 25MHz Noise Reduce by SF/SHA LPF Option
//--------------------------------------------------
#ifndef _VGA_ADC_SF_SHA_LPF_UNDER_25MHZ_SUPPORT
#define _VGA_ADC_SF_SHA_LPF_UNDER_25MHZ_SUPPORT                 _OFF
#endif

//===================== END =======================


////////////////
// DVI & HDMI //
////////////////

//--------------------------------------------------
// DVI & HDMI Option
//--------------------------------------------------
#ifndef _DVI_DE_ONLY_SUPPORT
#define _DVI_DE_ONLY_SUPPORT                                    _OFF
#endif

#ifndef _HDMI_FROM_DVI_CONNECT
#define _HDMI_FROM_DVI_CONNECT                                  _OFF
#endif

#ifndef _HDMI_FREESYNC_SUPPORT
#define _HDMI_FREESYNC_SUPPORT                                  _OFF
#endif

//==================== START ======================
#ifndef _HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD
#define _HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD                 _MCCS_SWITCH_MODE
#endif
//===================== END =======================


#ifndef _TMDS_HDCP_2_2_SUPPORT
#define _TMDS_HDCP_2_2_SUPPORT                                  _OFF
#endif

//--------------------------------------------------
// HDMI CTS Option
//--------------------------------------------------
#ifndef _TMDS_HDCP_FEATURE
#define _TMDS_HDCP_FEATURE                                      _HDCP_FEATURE_BY_INPUT
#endif

#ifndef _TMDS_Z0_POWER_SAVING_OPTION
#define _TMDS_Z0_POWER_SAVING_OPTION                            _ALL_CHANNEL_CONNECTED_FOR_CTS
#endif


////////
// DP //
////////

//-------------------------------------------------
// DP Capability Option
//-------------------------------------------------
#ifndef _DP_MST_SUPPORT
#define _DP_MST_SUPPORT                                         _OFF
#endif

#ifndef _DP_TX_SUPPORT
#define _DP_TX_SUPPORT                                          _OFF
#endif

#ifndef _DP_FREESYNC_SUPPORT
#define _DP_FREESYNC_SUPPORT                                    _OFF
#endif

#ifndef _DP_HDCP_2_2_SUPPORT
#define _DP_HDCP_2_2_SUPPORT                                    _OFF
#endif

//==================== START ======================

//--------------------------------------------------
// DP ASSR Option
//--------------------------------------------------
#ifndef _DP_ASSR_MODE_SUPPORT
#define _DP_ASSR_MODE_SUPPORT                                   _OFF
#endif

//--------------------------------------------------
// DP MST Option
//--------------------------------------------------
#ifndef _D0_DP_MST_PORT_SUPPORT
#if(_DP_MST_SUPPORT == _ON)
#define _D0_DP_MST_PORT_SUPPORT                                 _ON
#else
#define _D0_DP_MST_PORT_SUPPORT                                 _OFF
#endif
#endif

#ifndef _D1_DP_MST_PORT_SUPPORT
#if(_DP_MST_SUPPORT == _ON)
#define _D1_DP_MST_PORT_SUPPORT                                 _ON
#else
#define _D1_DP_MST_PORT_SUPPORT                                 _OFF
#endif
#endif

//===================== END =======================


/////////
// MHL //
/////////

//--------------------------------------------------
// MHL2.x Option
//--------------------------------------------------
#ifndef _MHL_CBUS_CTS_MODE
#define _MHL_CBUS_CTS_MODE                                      _OFF
#endif

#ifndef _MHL2_UCP_SUPPORT
#define _MHL2_UCP_SUPPORT                                       _OFF
#endif

#ifndef _MHL2_AUD_CHANNEL
#define _MHL2_AUD_CHANNEL                                       _MHL_AUD_2CH
#endif

#ifndef _MHL2_ADOPTER_ID
#define _MHL2_ADOPTER_ID                                        0x0000
#endif

#ifndef _MHL2_DEVICE_ID
#define _MHL2_DEVICE_ID                                         0x0000
#endif

#ifndef _MHL2_PP_MODE_SUPPORT
#define _MHL2_PP_MODE_SUPPORT                                   _ON
#endif

//--------------------------------------------------
// MHL3.x Option
//--------------------------------------------------
#ifndef _MHL3_UCP_SUPPORT
#define _MHL3_UCP_SUPPORT                                       _OFF
#endif

#ifndef _MHL3_AUD_CHANNEL
#define _MHL3_AUD_CHANNEL                                       _MHL_AUD_2CH
#endif

#ifndef _MHL3_ECBUS_HID_SUPPORT
#define _MHL3_ECBUS_HID_SUPPORT                                 _OFF
#endif

#ifndef _MHL3_ADOPTER_ID
#define _MHL3_ADOPTER_ID                                        0x0000
#endif

#ifndef _MHL3_DEVICE_ID
#define _MHL3_DEVICE_ID                                         0x0000
#endif

#ifndef _MHL3_16_BIT_MODE_SUPPORT
#define _MHL3_16_BIT_MODE_SUPPORT                               _ON
#endif

//==================== START ======================
#ifndef _MHL3_ECBUS_HID_SUPPORT
#define _MHL3_ECBUS_HID_SUPPORT                                 _OFF
#endif
//===================== END =======================


///////////
// Audio //
///////////

//-------------------------------------------------
// Audio Option
//-------------------------------------------------
#ifndef _AUDIO_SUPPORT
#define _AUDIO_SUPPORT                                          _OFF
#endif

//-------------------------------------------------
// Audio DAC Option
//-------------------------------------------------
#ifndef _EMBEDDED_DAC_SUPPORT
#define _EMBEDDED_DAC_SUPPORT                                   _OFF
#endif

//==================== START ======================
#ifndef _DAC_SPEAKER_OUTPUT_SWAP
#define _DAC_SPEAKER_OUTPUT_SWAP                                _OFF
#endif

#ifndef _DAC_HP_OUTPUT_SWAP
#define _DAC_HP_OUTPUT_SWAP                                     _OFF
#endif
//===================== END =======================

//-------------------------------------------------
// Audio Line In Option
//-------------------------------------------------
#ifndef _LINE_IN_SUPPORT
#define _LINE_IN_SUPPORT                                        _OFF
#endif

#ifndef _LINE_IN_DAC_AOUT_GAIN_DB
#define _LINE_IN_DAC_AOUT_GAIN_DB                               _AUDIO_DAC_OUTPUT_GAIN_0_DB // 0dB, 1.5dB for each step, Max Gain: 'b111(10.5dB)
#endif

#ifndef _LINE_IN_DAC_HPOUT_GAIN_DB
#define _LINE_IN_DAC_HPOUT_GAIN_DB                              _AUDIO_DAC_OUTPUT_GAIN_0_DB // 0dB, 1.5dB for each step, Max Gain: 'b111(10.5dB)
#endif

#ifndef _LINE_IN_BOOST_GAIN_DB
#define _LINE_IN_BOOST_GAIN_DB                                  0x17                        // 0dB, 1.5dB for each step, Max Gain: 0x3F(30dB)
#endif

#ifndef _LINE_IN_VOLUME_MAX
#define _LINE_IN_VOLUME_MAX                                     0x3FFF                      // MAX: 0x3FFF
#endif

#ifndef _LINE_IN_VOLUME_MIN
#define _LINE_IN_VOLUME_MIN                                     0x0000
#endif

//==================== START ======================

//--------------------------------------------------
// Audio Line In AA DAC Bypass Option
//--------------------------------------------------
#ifndef _LINE_IN_AA_PATH_SUPPORT
#define _LINE_IN_AA_PATH_SUPPORT                                _OFF
#endif

//--------------------------------------------------
// Audio Line In Support For DP TX Clone Option
//--------------------------------------------------
#ifndef _LINE_IN_AUDIO_DP_TX_CLONE_SUPPORT
#define _LINE_IN_AUDIO_DP_TX_CLONE_SUPPORT                      _ON
#endif

//===================== END =======================

//-------------------------------------------------
// Audio Digital Option
//-------------------------------------------------
#ifndef _DIGITAL_DAC_AOUT_GAIN_DB
#define _DIGITAL_DAC_AOUT_GAIN_DB                               _AUDIO_DAC_OUTPUT_GAIN_0_DB // 0dB, 1.5dB for each step, Max Gain: 'b111(10.5dB)
#endif

#ifndef _DIGITAL_DAC_HPOUT_GAIN_DB
#define _DIGITAL_DAC_HPOUT_GAIN_DB                              _AUDIO_DAC_OUTPUT_GAIN_0_DB // 0dB, 1.5dB for each step, Max Gain: 'b111(10.5dB)
#endif

#ifndef _DIGITAL_VOLUME_MAX
#define _DIGITAL_VOLUME_MAX                                     0x3FFF                      // MAX: 0x3FFF
#endif

#ifndef _DIGITAL_VOLUME_MIN
#define _DIGITAL_VOLUME_MIN                                     0x0000
#endif

//-------------------------------------------------
// Audio PS Option
//-------------------------------------------------
#ifndef _SLEEP_AUDIO_SUPPORT
#define _SLEEP_AUDIO_SUPPORT                                    _OFF
#endif

#ifndef _PS_AUDIO_INPUT
#define _PS_AUDIO_INPUT                                         _PS_AUDIO_LINE_IN
#endif

//==================== START ======================

//--------------------------------------------------
// Digital Volume Control Option --> For Audio Mute
//--------------------------------------------------
#ifndef _DVC_ADJUST_TYPE
#define _DVC_ADJUST_TYPE                                        _DB_GAIN
#endif

#ifndef _DB_GAIN_DOWN_VALUE
#define _DB_GAIN_DOWN_VALUE                                     _DB_GAIN_1_8_DB   // For _DB_GAIN
#endif

#ifndef _DB_GAIN_UP_VALUE
#define _DB_GAIN_UP_VALUE                                       _DB_GAIN_1_8_DB   // For _DB_GAIN
#endif

#ifndef _VOLUME_STEP_SIZE_VALUE
#define _VOLUME_STEP_SIZE_VALUE                                 (0x0040 & 0x3FFF) // For _VOLUME_STEP_SIZE
#endif

//--------------------------------------------------
// Audio Manual Sampling Frequency Option
//--------------------------------------------------
#ifndef _AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT
#define _AUDIO_MANUAL_SAMPLING_FREQ_SUPPORT                     _OFF
#endif

#ifndef _FIX_SAMPLING_FREQ_TYPE
#define _FIX_SAMPLING_FREQ_TYPE                                 _FIX_FREQ_48KHZ
#endif

//--------------------------------------------------
// Switch Audio Source to Line In When Entering Power Saving Mode Option
//--------------------------------------------------
#ifndef _SWITCH_TO_LINE_IN_AUDIO_IN_POWER_SAVING_MODE
#define _SWITCH_TO_LINE_IN_AUDIO_IN_POWER_SAVING_MODE           _OFF
#endif

//-------------------------------------------------
// Audio Hard Gain Option
//-------------------------------------------------
#ifndef _AUDIO_DVC_ADJUST_HARD_GAIN_SUPPORT
#define _AUDIO_DVC_ADJUST_HARD_GAIN_SUPPORT                     _OFF
#endif

#ifndef _LINE_IN_HARD_GAIN_VALUE
#define _LINE_IN_HARD_GAIN_VALUE                                _HARD_GAIN_0_DB
#endif

#ifndef _DIGITAL_HARD_GAIN_VALUE
#define _DIGITAL_HARD_GAIN_VALUE                                _HARD_GAIN_0_DB
#endif

//-------------------------------------------------
// Audio Digital Output(I2S/SPDIF) Adjust Volume Option
//-------------------------------------------------
#ifndef _DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT
#define _DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT             _OFF
#endif

//===================== END =======================


///////////////////
// Misc Function //
///////////////////

//-------------------------------------------------
// Instant Timer Events Option
//-------------------------------------------------
#ifndef _INSTANT_TIMER_EVENT_0
#define _INSTANT_TIMER_EVENT_0                                  _OFF
#endif

#ifndef _INSTANT_TIMER_EVENT_1
#define _INSTANT_TIMER_EVENT_1                                  _OFF
#endif

//--------------------------------------------------
// IRDA Option
//--------------------------------------------------
#ifndef _IR_SUPPORT
#define _IR_SUPPORT                                             _IR_OFF
#endif

//==================== START ======================

//--------------------------------------------------
// UART Option
//--------------------------------------------------
#ifndef _UART_SUPPORT
#define _UART_SUPPORT                                           _OFF
#endif

#ifndef _UART_BAUD_RATE_POWER_NORMAL
#define _UART_BAUD_RATE_POWER_NORMAL                            9600 // 5000 ~ 200000Baud (Unit in Baud)
#endif

#ifndef _UART_BAUD_RATE_POWER_SAVING
#define _UART_BAUD_RATE_POWER_SAVING                            9600 // 1000 ~ 60000Baud (Unit in Baud)
#endif

//-------------------------------------------------
// System Timer 250us Option --> SW IR Application
//-------------------------------------------------
#ifndef _SYSTEM_TIMER_QUARTER_RESOLUTION
#define _SYSTEM_TIMER_QUARTER_RESOLUTION                        _OFF
#endif

//--------------------------------------------------
//  Factory Debug Option --> Extern ScalerSetByte, ScalerGetByte, ScalerSetBit, ScalerGetBit to User
//--------------------------------------------------
#ifndef _FACTORY_DEBUG_SUPPORT
#define _FACTORY_DEBUG_SUPPORT                                  _OFF
#endif

//--------------------------------------------------
// Display Garbage Prevent Method Option
//--------------------------------------------------
#ifndef _DISPLAY_PREVENT_GARBAGE_METHOD
#define _DISPLAY_PREVENT_GARBAGE_METHOD                         _GARBAGE_PREVENT_BY_WATCH_DOG
#endif

//-------------------------------------------------
// Panel Power Sequence Control by User Option
//-------------------------------------------------
#ifndef _PANEL_POWER_SEQUENCE_CONTROL_BY_USER
#define _PANEL_POWER_SEQUENCE_CONTROL_BY_USER                   _OFF
#endif

//-------------------------------------------------
// Color Process Control by User Option
//-------------------------------------------------
#ifndef _COLOR_PROCESS_CONTROL_BY_USER
#define _COLOR_PROCESS_CONTROL_BY_USER                          _OFF
#endif

//-------------------------------------------------
// Flash Enable Write protect Option
//-------------------------------------------------
#ifndef _FLASH_WR_PROTECT
#define _FLASH_WR_PROTECT                                       _OFF
#endif


//////////
// Acer //
//////////

//-------------------------------------------------
// Acer TMDS Toggle HPD & Z0 Option
//-------------------------------------------------
#ifndef _TMDS_TOGGLE_HPD_Z0_FOR_ACER
#define _TMDS_TOGGLE_HPD_Z0_FOR_ACER                            _OFF
#endif


//////////
// Asus //
//////////

//-------------------------------------------------
// Asus Auto Search Time Option --> (_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_ASUS_STYLE)
//-------------------------------------------------
#ifndef _SOURCE_ASUS_START_AUTO_TIME
#define _SOURCE_ASUS_START_AUTO_TIME                            SEC(2)
#endif


//////////
// DELL //
//////////

//--------------------------------------------------
// DELL DP D3 Options --> for DELL
//--------------------------------------------------
#ifndef _DP_DELL_D3_TEST_SUPPORT
#define _DP_DELL_D3_TEST_SUPPORT                                _OFF
#endif


/////////////
// PHILIPS //
/////////////

//--------------------------------------------------
// PHILIPS Pixel-shift Support Option
//--------------------------------------------------
#ifndef _PIXEL_SHIFT_SUPPORT
#define _PIXEL_SHIFT_SUPPORT                                    _OFF
#endif


////////
// HP //
////////

//--------------------------------------------------
//  HP Source Scan Define Option
//--------------------------------------------------
#ifndef _HP_SOURCE_SCAN_SUPPORT
#define _HP_SOURCE_SCAN_SUPPORT                                 _OFF
#endif


//////////
// Eizo //
//////////

//--------------------------------------------------
// Eizo DP Sink Support OUI Under Ver1.1 Option
//--------------------------------------------------
#ifndef _DP_SINK_VER11_OUI_SUPPORT
#define _DP_SINK_VER11_OUI_SUPPORT                              _ON
#endif

//--------------------------------------------------
// Eizo DP DPCD Table Value of Sink IEEE OUI Option
//--------------------------------------------------
#ifndef _DP_SINK_RTK_IEEE_OUI_L
#define _DP_SINK_RTK_IEEE_OUI_L                                 0x00
#endif

#ifndef _DP_SINK_RTK_IEEE_OUI_M
#define _DP_SINK_RTK_IEEE_OUI_M                                 0xE0
#endif

#ifndef _DP_SINK_RTK_IEEE_OUI_H
#define _DP_SINK_RTK_IEEE_OUI_H                                 0x4C
#endif

#ifndef _DP_SINK_RTK_ID_STRING_0
#define _DP_SINK_RTK_ID_STRING_0                                0x44
#endif

#ifndef _DP_SINK_RTK_ID_STRING_1
#define _DP_SINK_RTK_ID_STRING_1                                0x70
#endif

#ifndef _DP_SINK_RTK_ID_STRING_2
#define _DP_SINK_RTK_ID_STRING_2                                0x31
#endif

#ifndef _DP_SINK_RTK_ID_STRING_3
#define _DP_SINK_RTK_ID_STRING_3                                0x2E
#endif

#ifndef _DP_SINK_RTK_ID_STRING_4
#define _DP_SINK_RTK_ID_STRING_4                                0x32
#endif

#ifndef _DP_SINK_RTK_ID_STRING_5
#define _DP_SINK_RTK_ID_STRING_5                                0x00
#endif

//--------------------------------------------------
// Eizo DP DPCD Table Value Of Sink HW/FW Version Option
//--------------------------------------------------
#ifndef _DP_SINK_RTK_HW_VERSION
#define _DP_SINK_RTK_HW_VERSION                                 0x00
#endif

#ifndef _DP_SINK_RTK_FW_VERSION_H
#define _DP_SINK_RTK_FW_VERSION_H                               0x00
#endif

#ifndef _DP_SINK_RTK_FW_VERSION_L
#define _DP_SINK_RTK_FW_VERSION_L                               0x00
#endif

//--------------------------------------------------
// Eizo DP DPCD Table Value Of Branch IEEE OUI Option
//--------------------------------------------------
#ifndef _DP_BRANCH_RTK_IEEE_OUI_L
#define _DP_BRANCH_RTK_IEEE_OUI_L                               0x00
#endif

#ifndef _DP_BRANCH_RTK_IEEE_OUI_M
#define _DP_BRANCH_RTK_IEEE_OUI_M                               0xE0
#endif

#ifndef _DP_BRANCH_RTK_IEEE_OUI_H
#define _DP_BRANCH_RTK_IEEE_OUI_H                               0x4C
#endif

#ifndef _DP_BRANCH_RTK_ID_STRING_0
#define _DP_BRANCH_RTK_ID_STRING_0                              0x44
#endif

#ifndef _DP_BRANCH_RTK_ID_STRING_1
#define _DP_BRANCH_RTK_ID_STRING_1                              0x70
#endif

#ifndef _DP_BRANCH_RTK_ID_STRING_2
#define _DP_BRANCH_RTK_ID_STRING_2                              0x31
#endif

#ifndef _DP_BRANCH_RTK_ID_STRING_3
#define _DP_BRANCH_RTK_ID_STRING_3                              0x2E
#endif

#ifndef _DP_BRANCH_RTK_ID_STRING_4
#define _DP_BRANCH_RTK_ID_STRING_4                              0x32
#endif

#ifndef _DP_BRANCH_RTK_ID_STRING_5
#define _DP_BRANCH_RTK_ID_STRING_5                              0x00
#endif

//--------------------------------------------------
// Eizo DP DPCD Table Value Of Branch HW/FW Version Option
//--------------------------------------------------
#ifndef _DP_BRANCH_RTK_HW_VERSION
#define _DP_BRANCH_RTK_HW_VERSION                               0x00
#endif

#ifndef _DP_BRANCH_RTK_FW_VERSION_H
#define _DP_BRANCH_RTK_FW_VERSION_H                             0x00
#endif

#ifndef _DP_BRANCH_RTK_FW_VERSION_L
#define _DP_BRANCH_RTK_FW_VERSION_L                             0x00
#endif


////////
// LG //
////////

//--------------------------------------------------
//  LG DP Power Management
//--------------------------------------------------
#ifndef _DP_POWER_MANAGEMENT_FOR_FAST_DISPLAY_RECOVER
#define _DP_POWER_MANAGEMENT_FOR_FAST_DISPLAY_RECOVER           _OFF
#endif

//--------------------------------------------------
//  LG DP Rx DPCD Link Training AUX RD Interval
//--------------------------------------------------
#ifndef _DP_RX_DPCD_TRAINING_AUX_RD_INTERVAL
#define _DP_RX_DPCD_TRAINING_AUX_RD_INTERVAL                    (0x00 & 0x7F)
#endif
//===================== END =======================
