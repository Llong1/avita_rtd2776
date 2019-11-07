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
// ID Code      : Project_Config_Check.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __PROJECT_CONFIG_CHECK_H__
#define __PROJECT_CONFIG_CHECK_H__

//--------------------------------------------------
// Memory Config Check
//--------------------------------------------------
#if(_OD_SUPPORT == _ON)
#if(_MEMORY_TYPE_CONFIG == _NO_MEMORY)
#warning "_OD_SUPPORT Can Not Be Supported With No Memory!!!"
#endif
#endif

#if(_FRC_SUPPORT == _ON)
#if(_MEMORY_TYPE_CONFIG == _NO_MEMORY)
#warning "_FRC_SUPPORT Can Not Be Supported With No Memory!!!"
#endif
#endif

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
#if(_MEMORY_TYPE_CONFIG == _NO_MEMORY)
#warning "_DISPLAY_ROTATION_SUPPORT Can Not Be Supported With No Memory!!!"
#endif
#endif

#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
#if(_MEMORY_TYPE_CONFIG == _NO_MEMORY)
#warning "_DISPLAY_HOR_MIRROR_SUPPORT Can Not Be Supported With No Memory!!!"
#endif
#endif

#if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
#if(_MEMORY_TYPE_CONFIG == _NO_MEMORY)
#warning "_DISPLAY_VER_MIRROR_SUPPORT Can Not Be Supported With No Memory!!!"
#endif
#endif

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
#if(_MEMORY_TYPE_CONFIG == _NO_MEMORY)
#warning "_DISP_LATENCY_ADJUST_SUPPORT Can Not Be Supported With No Memory!!!"
#endif
#endif


//--------------------------------------------------
// Display Setting Check
//--------------------------------------------------
#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
#if(_FRC_SUPPORT == _OFF)
#warning "_FRC_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_FORCE_TO_FREE_RUN_SUPPORT == _ON)
#if(_FRC_SUPPORT == _OFF)
#warning "_FRC_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_FREEZE_SUPPORT == _ON)
#if(_FRC_SUPPORT == _OFF)
#warning "_FRC_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
#if(_FRC_SUPPORT == _OFF)
#warning "_FRC_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
#if(_FRC_SUPPORT == _OFF)
#warning "_FRC_SUPPORT Should Be _ON!!!"
#endif
#endif

#if((_FRAME_SYNC_LINE_BUFFER_SUPPORT == _OFF) && (_FRC_SUPPORT == _OFF))
#if(_PANEL_STYLE != _PANEL_NONE)
#warning "_FRAME_SYNC_LINE_BUFFER_SUPPORT or _FRC_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
#if(_ASPECT_RATIO_SUPPORT == _OFF)
#warning "_ASPECT_RATIO_SUPPORT Should Be _ON!!!"
#endif
#endif

#if((_DISPLAY_HOR_MIRROR_SUPPORT == _ON) || (_DISPLAY_VER_MIRROR_SUPPORT == _ON))
#if(_DISPLAY_ROTATION_SUPPORT == _OFF)
#warning "_DISPLAY_ROTATION_SUPPORT Should Be _ON!!!"
#endif
#endif

#if((_FORCE_TO_FREE_RUN_SUPPORT == _ON) || (_FREEZE_SUPPORT == _ON))
#if(_FRAME_SYNC_LINE_BUFFER_SUPPORT == _ON)
#warning "_FRAME_SYNC_LINE_BUFFER_SUPPORT Should Be _OFF!!!"
#endif
#endif

#if((_FREEZE_SUPPORT == _ON) && (_DISPLAY_ROTATION_SUPPORT == _ON))
#if(_ROTATION_FREEZE_FORCE_TO_BACKGROUND == _OFF)
#warning "_ROTATION_FREEZE_FORCE_TO_BACKGROUND Should Be _ON!!!"
#endif
#endif

//-------------------------------------------------
// ICM
//-------------------------------------------------
#if(_ICM_BRI_SUPPORT == _ON)
#if(_ICM_SUPPORT == _OFF)
#warning "_ICM_SUPPORT Should Be _ON!!!"
#endif
#endif

//--------------------------------------------------
// SCM Config Check
//--------------------------------------------------
#if(_SCM_SUPPORT == _ON)
#if(_ICM_SUPPORT == _OFF)
#warning "_ICM_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_SIX_COLOR_SUPPORT == _ON)
#if(_ICM_SUPPORT == _OFF)
#warning "_ICM_SUPPORT Should Be _ON!!!"
#endif
#endif

//--------------------------------------------------
// SixColor Config Check
//--------------------------------------------------
#if(_SCALER_TYPE == _RL6193_SERIES)
#if(_SIX_COLOR_ICM_TYPE == _SIX_COLOR_ICM_DELL_MODE)
#warning "_SIX_COLOR_ICM_DELL_MODE Can Not Be Supported!!!"
#endif
#endif

//-------------------------------------------------
// IAPS & DCR & DCC
//-------------------------------------------------
#if((_IAPS_SUPPORT == _ON) && (_DCR_SUPPORT == _ON))
#warning "_IAPS_SUPPORT or _IAPS_SUPPORT Should Be _OFF!!!"
#endif

#if(_IAPS_GAIN_COMPENSATION_TYPE == _IAPS_GAIN_COMPENSATION_GEN_0)

#if(_IAPS_SUPPORT == _ON)
#if(_DCC_HISTOGRM_INFO == _OFF)
#warning "_DCC_HISTOGRM_INFO Should Be _ON!!!"
#endif
#endif

#if(_ULTRA_HDR_SUPPORT == _ON)
#if(_DCC_HISTOGRM_INFO == _ON)
#warning "_DCC_HISTOGRM_INFO Should Be _OFF!!!"
#endif
#endif

#if((_IAPS_SUPPORT == _ON) && (_DCC_FUNCTION == _ON))
#warning "_IAPS_SUPPORT or _DCC_FUNCTION Should Be _OFF!!!"
#endif

#endif // End of #if(_IAPS_GAIN_COMPENSATION_TYPE == _IAPS_GAIN_COMPENSATION_GEN_0)

//-------------------------------------------------
// Color Cailibration
//-------------------------------------------------
#if(_OGC_SUPPORT == _ON)
#if(_GAMMA_FUNCTION == _OFF)
#warning "_GAMMA_FUNCTION Should Be _ON!!!"
#endif
#endif

#if((_OGC_SUPPORT == _ON) || (_FALSE_COLOR_SUPPORT == _ON))
#if(_CONTRAST_SUPPORT == _OFF)
#warning "_CONTRAST_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_OCC_SUPPORT == _ON)
#if(_GAMMA_FUNCTION == _OFF)
#warning "_GAMMA_FUNCTION Should Be _ON!!!"
#endif
#endif

#if(_RGB_GAMMA_FUNCTION == _ON)
#if(_GAMMA_FUNCTION == _OFF)
#warning "_GAMMA_FUNCTION Should Be _ON!!!"
#endif
#endif

#if(_OGC_DICOM_SUPPORT == _ON)
#if(_GAMMA_FUNCTION == _OFF)
#warning "_GAMMA_FUNCTION Should Be _ON!!!"
#endif
#endif

#if(_OCC_SUPPORT == _ON)
#if(_PCM_FUNCTION == _OFF)
#warning "_PCM_FUNCTION Should Be _ON!!!"
#endif
#endif

#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON))
#if(_DDCCI0_RXBUF_LENGTH < 128)
#warning "_DDCCI0_RXBUF_LENGTH Should Be >= 128!!!"
#endif

#if((_DDCCI_OPCODE_VCP_DISP_CALIBRATION < 0xF0) || (_DDCCI_OPCODE_VCP_DISP_CALIBRATION > 0xFF))
#warning "Unreasonable OPCODE for Color Calibration!!!"
#endif

#if(_FLASH_ACCESS_FUNCTION_SUPPORT == _OFF)
#warning "_FLASH_ACCESS_FUNCTION_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_UNIFORMITY_SUPPORT == _ON)
#if((_OGC_SUPPORT == _OFF) && (_OCC_SUPPORT == _OFF))
#warning "_OGC_SUPPORT or _OGC_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
#if(_SCALER_TYPE == _RL6193_SERIES)
#warning "RL6193 Can Not Support _UNIFORMITY_LEVEL0!!!"
#elif(_UNIFORMITY_SUPPORT == _OFF)
#warning "_UNIFORMITY_SUPPORT Should BE _ON!!!"
#endif
#endif

#if(_PANEL_EXIST_MULTIPANEL == _OFF)
#if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
#if(_CONTRAST_SUPPORT == _OFF)
#warning "_CONTRAST_SUPPORT Should Be _ON!!!"
#endif
#endif
#endif

#if((_ULTRA_HDR_SUPPORT == _ON) && (_HW_DP_VSC_SDP_EXT_CAPABILITY_SUPPORT == _OFF))
#warning "_ULTRA_HDR_SUPPORT Should Be _OFF!!!"
#endif

#if(_ULTRA_HDR_SUPPORT == _ON)
#if(_OCC_SUPPORT == _OFF)
#warning "_OCC_SUPPORT Should Be _ON!!!"
#endif
#endif

//-------------------------------------------------
// Color Conversion Check
//-------------------------------------------------
#if((_ULTRA_VIVID_SUPPORT == _ON) ||\
    (_RGB_QUANTIZATION_RANGE_SUPPORT == _ON) ||\
    (_YCC_QUANTIZATION_RANGE_SUPPORT == _ON) ||\
    (_M_DOMAIN_FORCE_YUV_FORMAT == _ON))
#if(_COLOR_FORMAT_CONVERT == _OFF)
#warning "_COLOR_FORMAT_CONVERT Should Be _ON!!!"
#endif
#endif

//-------------------------------------------------
// System Eeprom Check
//-------------------------------------------------
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
#if(_EEPROM_ACCESS_FUNCTION_SUPPORT == _OFF)
#warning "_EEPROM_ACCESS_FUNCTION_SUPPORT Should Be _ON!!!"
#endif
#endif

//-------------------------------------------------
// System Eeprom Emulation
//-------------------------------------------------
#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _ON)
#if(_FLASH_ACCESS_FUNCTION_SUPPORT == _OFF)
#warning "_FLASH_ACCESS_FUNCTION_SUPPORT Should Be _ON!!!"
#endif

#if((_OGC_FLASH_BANK == _SYSTEM_EEPROM_EMULATION_FLASH_BANK) &&\
    ((_SYSTEM_EEPROM_EMULATION_END_PAGE >= _OGC_FLASH_PAGE) &&\
    (_SYSTEM_EEPROM_EMULATION_START_PAGE < (_OGC_FLASH_PAGE + (((_OGC_SUPPORT == _ON) ? 2 : 0) + (((_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON)) ? 1 : 0))))))
#error "System Data Page & Color Calibration Data Page Overlap!!!"
#endif

#if(_SYSTEM_EEPROM_EMULATION_END_PAGE > 14)
#error "System Eeprom Emulation End Page Error!!!"
#endif

#if((_SYSTEM_EEPROM_EMULATION_END_PAGE - _SYSTEM_EEPROM_EMULATION_START_PAGE) < (_END_OF_PAGEID - _START_OF_PAGEID + 1))
#warning "Flash Page Number and Page ID Number Warning!!!"
#endif
#endif

//-------------------------------------------------
// EDID Check
//-------------------------------------------------
#if(_EDID_TABLE_LOCATED_IN_FLASH == _ON)
#if(_FLASH_ACCESS_FUNCTION_SUPPORT == _OFF)
#warning "_FLASH_ACCESS_FUNCTION_SUPPORT Should Be _ON!!!"
#endif
#endif

//-------------------------------------------------
// HDCP 2.2 Check
//-------------------------------------------------
#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
#if(_TMDS_HDCP_2_2_FUNCTION_SUPPORT == _OFF)
#warning "_TMDS_HDCP_2_2_SUPPORT Can Not Be Supported!!!"
#endif
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
#if(_DP_HDCP_2_2_FUNCTION_SUPPORT == _OFF)
#warning "_DP_HDCP_2_2_SUPPORT Can Not Be Supported!!!"
#endif
#endif

//--------------------------------------------------
// HDCP Key Location Check
//--------------------------------------------------
#ifdef __USER_COMMON_INTERFACE__

#if((_DIGITAL_PORT_SUPPORT == _ON) && ((_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_CODE) || ((_HDCP_2_2_SUPPORT == _ON) && (_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_CODE))))
#warning "Please check HDCP KEY location!!"
#endif

#endif // End of #ifdef __USER_COMMON_INTERFACE__

//-------------------------------------------------
// HDCP Key Check
//-------------------------------------------------
#if((_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH) || (_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH))
#if(_FLASH_ACCESS_FUNCTION_SUPPORT == _OFF)
#warning "_FLASH_ACCESS_FUNCTION_SUPPORT Should Be _ON!!!"
#endif
#endif

#if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_EFUSE)
#if(_HDCP_1_4_KEY_EFUSE_SUPPORT == _OFF)
#warning "_HDCP_1_4_KEY_LOCATION Should Be _OFF!!! "
#endif
#endif

#if(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_EFUSE)
#warning "_HDCP_2_2_KEY_LOCATION eFuse Can Not Be Supported!!! "
#endif

//--------------------------------------------------
// Write EDID/HDCP Table to NVRAM Check
//--------------------------------------------------
#ifdef __USER_COMMON_NVRAM_SYSTEM__

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
#warning "_WRITE_HDCP_TO_SYSTEM_EEPROM _ON!!"
#endif

#if(_WRITE_EDID_TO_SYSTEM_EEPROM == _ON)
#warning "_WRITE_EDID_TO_SYSTEM_EEPROM _ON!!"
#endif

#endif // End of #ifdef __USER_COMMON_NVRAM_SYSTEM__

//--------------------------------------------------
// External or Embedded 2 DP Switch Config Check
//--------------------------------------------------
#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
#if((_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_IN_SEARCH_STATE) ||\
    (_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_ASUS_STYLE) ||\
    (_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_DELL_STYLE))
#warning "_SOURCE_AUTO_SEARCH_STYLE you choose can't be supported when using External or Embedded DP Switch!!!"
#endif
#endif

//--------------------------------------------------
// DP Dual Port Config Check
//--------------------------------------------------
#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
#if((_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_IN_SEARCH_STATE) ||\
    (_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_ASUS_STYLE) ||\
    (_SOURCE_AUTO_SEARCH_STYLE == _SOURCE_POLLING_DELL_STYLE))
#warning "_SOURCE_AUTO_SEARCH_STYLE you choose can't be supported when using DP Dual Port!!!"
#endif
#endif

//--------------------------------------------------
// VGA Check
//--------------------------------------------------
#if((_YPBPR_SUPPORT == _ON) && (_SOG_SUPPORT == _OFF))
#if(_SOG_SUPPORT == _OFF)
#warning "_SOG_SUPPORT Should Be _ON!!!"
#endif
#endif

//--------------------------------------------------
// Free Sync Check
//--------------------------------------------------
#if((_FORCE_TO_FREE_RUN_SUPPORT == _ON) || (_FREEZE_SUPPORT == _ON))
#if(_FREESYNC_SUPPORT == _ON)
#warning "_FREESYNC_SUPPORT Should Be _OFF!!!"
#endif
#endif

#if(_HDMI_FREESYNC_SUPPORT == _ON)
#if((_DDCCI_AUTO_SWITCH_SUPPORT == _OFF) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
#warning "_DDCCI_AUTO_SWITCH_SUPPORT Should Be _ON!!!"
#endif
#endif

//--------------------------------------------------
// Source Switch Check
//--------------------------------------------------
#if(_HP_SOURCE_SCAN_SUPPORT == _ON)
#if(_SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT == _ON)
#warning "_SOURCE_DOUBLE_CHECK_NVRAM_PORT_SUPPORT Should Be _OFF!!!"
#endif
#endif

//-------------------------------------------------
// DP Check
//-------------------------------------------------
#if(_DP_MST_SUPPORT == _ON)
#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D1_INPUT_PORT_TYPE == _D1_DP_PORT))

#if((_D0_DP_MST_PORT_SUPPORT == _OFF) && (_D1_DP_MST_PORT_SUPPORT == _OFF))
#warning "_D0_DP_MST_PORT_SUPPORT or _D1_DP_MST_PORT_SUPPORT Should Be _ON!!!"
#endif

#elif(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

#if(_D0_DP_MST_PORT_SUPPORT == _OFF)
#warning "_D0_DP_MST_PORT_SUPPORT Should Be _ON!!!"
#endif

#elif(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

#if(_D1_DP_MST_PORT_SUPPORT == _OFF)
#warning "_D1_DP_MST_PORT_SUPPORT Should Be _ON!!!"
#endif

#endif
#endif // End of #if(_DP_MST_SUPPORT == _ON)

//--------------------------------------------------
// Audio Check
//--------------------------------------------------
#if((_SLEEP_AUDIO_SUPPORT == _ON) && (_PS_AUDIO_INPUT != _PS_AUDIO_DP))
#if(_LINE_IN_SUPPORT == _OFF)
#warning "_LINE_IN_SUPPORT Should Be _ON!!!"
#endif
#endif

#if((_SLEEP_AUDIO_SUPPORT == _ON) && (_PS_AUDIO_INPUT != _PS_AUDIO_LINE_IN))
#if(_SWITCH_TO_LINE_IN_AUDIO_IN_POWER_SAVING_MODE == _ON)
#warning "_PS_AUDIO_INPUT Should Be _PS_AUDIO_LINE_IN!!!"
#endif
#endif

#if((_EMBEDDED_DAC_SUPPORT == _OFF) || (_LINE_IN_SUPPORT == _OFF))
#if(_LINE_IN_AA_PATH_SUPPORT == _ON)
#warning "_LINE_IN_AA_PATH_SUPPORT Should Be _OFF!!!"
#endif
#endif

#if(_HW_AUDIO_DIGITAL_OUTPUT_ADJUST_VOLUME == _OFF)
#if(_DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT == _ON)
#warning "_DIGITAL_AUDIO_OUTPUT_ADJUST_VOLUME_SUPPORT Can Not Be Supported!!!"
#endif
#endif

#endif // End of #ifndef __PROJECT_CONFIG_CHECK_H__
