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
// ID Code      : UserCommonInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if 1 // alant

#include "tiling.h"
#include "w74m00av.h"
#endif


#include "Global.h"
#include "Project.h"
#include "ScalerFunctionInterface.h"
#include "SysInterface.h"
#include "UserCommonDdcciDefine.h"
#include "ScalerRegCommonInclude.h"

#if(_SCALER_TYPE == _RL6193_SERIES)
#include "RL6193_Series_RegCommonInclude.h"
#elif(_SCALER_TYPE == _RL6410_SERIES)
#include "RL6410_Series_RegCommonInclude.h"
#endif

#include _USER_FUNCTION_INCLUDE
#include _OSD_INCLUDE
#include _FACTORY_INCLUDE

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Eeprom Page address
//--------------------------------------------------
#define _EEPROM_PAGE0_BANK0                            0
#define _EEPROM_PAGE0_BANK1                            128
#define _EEPROM_PAGE1_BANK0                            256
#define _EEPROM_PAGE1_BANK1                            384
#define _EEPROM_PAGE2_BANK0                            512
#define _EEPROM_PAGE2_BANK1                            640
#define _EEPROM_PAGE3_BANK0                            768
#define _EEPROM_PAGE3_BANK1                            896
#define _EEPROM_PAGE4_BANK0                            1024
#define _EEPROM_PAGE4_BANK1                            1152
#define _EEPROM_PAGE5_BANK0                            1280
#define _EEPROM_PAGE5_BANK1                            1408
#define _EEPROM_PAGE6_BANK0                            1536
#define _EEPROM_PAGE6_BANK1                            1664
#define _EEPROM_PAGE7_BANK0                            1792
#define _EEPROM_PAGE7_BANK1                            1920
#define _EEPROM_PAGE8_BANK0                            2048
#define _EEPROM_PAGE8_BANK1                            2176
#define _EEPROM_PAGE9_BANK0                            2304
#define _EEPROM_PAGE9_BANK1                            2432
#define _EEPROM_PAGEA_BANK0                            2560
#define _EEPROM_PAGEA_BANK1                            2688
#define _EEPROM_PAGEB_BANK0                            2816
#define _EEPROM_PAGEB_BANK1                            2944
#define _EEPROM_PAGEC_BANK0                            3072
#define _EEPROM_PAGEC_BANK1                            3200
#define _EEPROM_PAGED_BANK0                            3328
#define _EEPROM_PAGED_BANK1                            3456
#define _EEPROM_PAGEE_BANK0                            3584
#define _EEPROM_PAGEE_BANK1                            3712
#define _EEPROM_PAGEF_BANK0                            3840
#define _EEPROM_PAGEF_BANK1                            3968
#define _EEPROM_PAGE10_BANK0                           4096
#define _EEPROM_PAGE10_BANK1                           4224
#define _EEPROM_PAGE11_BANK0                           4352
#define _EEPROM_PAGE11_BANK1                           4480
#define _EEPROM_PAGE12_BANK0                           4608
#define _EEPROM_PAGE12_BANK1                           4736
#define _EEPROM_PAGE13_BANK0                           4864
#define _EEPROM_PAGE13_BANK1                           4992
#define _EEPROM_PAGE14_BANK0                           5120
#define _EEPROM_PAGE14_BANK1                           5248
#define _EEPROM_PAGE15_BANK0                           5376
#define _EEPROM_PAGE15_BANK1                           5504
#define _EEPROM_PAGE16_BANK0                           5632
#define _EEPROM_PAGE16_BANK1                           5760
#define _EEPROM_PAGE17_BANK0                           5888
#define _EEPROM_PAGE17_BANK1                           6016
#define _EEPROM_PAGE18_BANK0                           6144
#define _EEPROM_PAGE18_BANK1                           6272
#define _EEPROM_PAGE19_BANK0                           6400
#define _EEPROM_PAGE19_BANK1                           6528
#define _EEPROM_PAGE1A_BANK0                           6656
#define _EEPROM_PAGE1A_BANK1                           6784
#define _EEPROM_PAGE1B_BANK0                           6912
#define _EEPROM_PAGE1B_BANK1                           7040
#define _EEPROM_PAGE1C_BANK0                           7168
#define _EEPROM_PAGE1C_BANK1                           7296
#define _EEPROM_PAGE1D_BANK0                           7424
#define _EEPROM_PAGE1D_BANK1                           7552
#define _EEPROM_PAGE1E_BANK0                           7680
#define _EEPROM_PAGE1E_BANK1                           7808
#define _EEPROM_PAGE1F_BANK0                           7936
#define _EEPROM_PAGE1F_BANK1                           8064

//---------------------------------------------------------------------------------------------------------------------------------------

#define _EEPROM_CHECKSUM_ADDRESS                       (_EEPROM_KERNEL_START_ADDRESS)
#define _EEPROM_VERSION_CODE_ADDRESS                   (_EEPROM_CHECKSUM_ADDRESS + 1)
#define _ADC_SETTING_ADDRESS                           (_EEPROM_VERSION_CODE_ADDRESS + 1)
#define _SYSTEM_DATA_ADDRESS                           (_ADC_SETTING_ADDRESS + sizeof(StructAdcDataType) * (_VGA_SUPPORT + _YPBPR_SUPPORT))
#define _SYSTEM_DATA_ADDRESS_END                       (_SYSTEM_DATA_ADDRESS + sizeof(StructSystemDataType))
//---------------------------------------------------------------------------------------------------------------------------------------

#define _MODE_USER_DATA_ADDRESS                        (_SYSTEM_DATA_ADDRESS_END)
#define _VGA_MODE_DATA_ADDRESS_END                     (_MODE_USER_DATA_ADDRESS + sizeof(StructVGAModeUserDataType) * _MODE_SLOT_AMOUNT * _VGA_SUPPORT)
//---------------------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of Flash Page information
//--------------------------------------------------
#define _OCC_LUT_MODE                                  _OFF

#define _EDID_TABLE_FLASH_PAGE                         (_EDID_ADDRESS_FLASH / _FLASH_PAGE_SIZE)
#define _RX_HDCP_1_4_TABLE_FLASH_PAGE                  (_RX_HDCP_1_4_KEY_ADDRESS_FLASH / _FLASH_PAGE_SIZE)
#define _RX_HDCP_2_2_TABLE_FLASH_PAGE                  (_RX_HDCP_2_2_KEY_ADDRESS_FLASH / _FLASH_PAGE_SIZE)
#define _TX_HDCP_TABLE_FLASH_PAGE                      (_TX_HDCP_KEY_ADDRESS_FLASH / _FLASH_PAGE_SIZE)

//--------------------------------------------------
// Address for OGC/OCC/DICOM
//--------------------------------------------------
#define _OGC_RGB_GAIN_TOTAL_SPACE                      0x100UL
#define _OGC_GAMMA_TABLE_SIZE                          0x1A00UL // 2200*3 = 0x19C8 2052 * 3 = 0x180C
#define _OGC_RGB_GAIN_ACTUAL_SIZE                      (_OGC_TOTAL_GAMMA * _OGC_TOTAL_CT * 6)
#define _OGC_HDR_IG_TABLE_SIZE                         0xC5
#define _OCC_HDR_COLOR_MATRIX_SIZE                     0x50

#define _OCC_COLOR_MATRIX_TOTAL_SPACE                  0x900UL // Max: 324*7 = 972 = 0x3CC ; sRGB/Adobe/SoftProof/Userdefine/EBU/Rec709/DCI-P3
#define _OCC_COLORMATRIX_TABLE_SIZE                    (_OCC_LUT_MODE == _ON ? 312 : 18)
#define _OGC_HEADER_LENGTH                             (4 + (_OGC_TOTAL_GAMMA + 1 + _OGC_TOTAL_CT + 1))
#define _OCC_HEADER_LENGTH                             5
#define _DICOM_HEADER_LENGTH                           5
#define _WHITE_LV_HEADER_LENGTH                        5

#define _OGC_RGB_GAIN_ADDRESS                          0
#define _OGC_HEADER_ADDRESS                            (_OGC_RGB_GAIN_ADDRESS + _OGC_RGB_GAIN_ACTUAL_SIZE)
#define _OCC_HEADER_ADDRESS                            (_OGC_HEADER_ADDRESS + _OGC_HEADER_LENGTH)
#define _DICOM_HEADER_ADDRESS                          (_OCC_HEADER_ADDRESS + _OCC_HEADER_LENGTH)
#define _WHITE_LV_HEADER_ADDRESS                       (_DICOM_HEADER_ADDRESS + _DICOM_HEADER_LENGTH)
#define _OGC_GAMMA1_ADDRESS                            (_OGC_RGB_GAIN_ADDRESS + _OGC_RGB_GAIN_TOTAL_SPACE)
#define _OGC_GAMMA2_ADDRESS                            (_OGC_GAMMA1_ADDRESS + _OGC_GAMMA_TABLE_SIZE * _OGC_SUPPORT * (_OGC_TOTAL_GAMMA > 1 ? 1 : 0))
#define _OGC_GAMMA3_ADDRESS                            (_OGC_GAMMA2_ADDRESS + _OGC_GAMMA_TABLE_SIZE * _OGC_SUPPORT * (_OGC_TOTAL_GAMMA > 2 ? 1 : 0))
#define _OGC_GAMMA4_ADDRESS                            (_OGC_GAMMA3_ADDRESS + _OGC_GAMMA_TABLE_SIZE * _OGC_SUPPORT * (_OGC_TOTAL_GAMMA > 3 ? 1 : 0))
#define _OGC_GAMMA5_ADDRESS                            (_OGC_GAMMA4_ADDRESS + _OGC_GAMMA_TABLE_SIZE * _OGC_SUPPORT * (_OGC_TOTAL_GAMMA > 4 ? 1 : 0))

#define _OCC_GAMMA10_ADDRESS                           (_OGC_GAMMA5_ADDRESS + _OGC_GAMMA_TABLE_SIZE * _OGC_SUPPORT)
#define _OCC_HDR_GAMMA10_ADDRESS                       _OCC_GAMMA10_ADDRESS
#define _OCC_SRGBMATRIX_ADDRESS                        (_OCC_HDR_GAMMA10_ADDRESS + _OGC_GAMMA_TABLE_SIZE * _OCC_SUPPORT)
#define _OCC_ADOBEMATRIX_ADDRESS                       (_OCC_SRGBMATRIX_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * _OCC_SUPPORT)
#define _OCC_USERDEFINE_ADDRESS                        (_OCC_ADOBEMATRIX_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * _OCC_SUPPORT)
#define _OCC_EBU_ADDRESS                               (_OCC_USERDEFINE_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * _OCC_SUPPORT)
#define _OCC_SOFTPROOF_ADDRESS                         (_OCC_USERDEFINE_ADDRESS)
#define _OCC_REC709_ADDRESS                            (_OCC_EBU_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * _OCC_SUPPORT)
#define _OCC_DCIP3_ADDRESS                             (_OCC_REC709_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * _OCC_SUPPORT)
#define _OCC_SMPTEC_ADDRESS                            (_OCC_DCIP3_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * _OCC_SUPPORT)

#define _OGC_DICOM_ADDRESS                             (_OCC_SRGBMATRIX_ADDRESS + _OCC_COLOR_MATRIX_TOTAL_SPACE * _OCC_SUPPORT)

#define _OCC_HDR_SRGB_MATRIX_ADDRESS                   (_OGC_DICOM_ADDRESS + _OGC_GAMMA_TABLE_SIZE * _OGC_DICOM_SUPPORT)
#define _OCC_HDR_ADOBE_MATRIX_ADDRESS                  (_OCC_HDR_SRGB_MATRIX_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * _ULTRA_HDR_SUPPORT)
#define _OCC_HDR_DCIP3_D65_MATRIX_ADDRESS              (_OCC_HDR_ADOBE_MATRIX_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * _ULTRA_HDR_SUPPORT)
#define _OCC_HDR_BT2020_MATRIX_ADDRESS                 (_OCC_HDR_DCIP3_D65_MATRIX_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * _ULTRA_HDR_SUPPORT)

#define _OGC_HDR_IG_1200_NOR_ADDRESS                   (_OCC_HDR_SRGB_MATRIX_ADDRESS + _OCC_HDR_COLOR_MATRIX_SIZE * _ULTRA_HDR_SUPPORT)
#define _OGC_HDR_IG_1200_DARK_ADDRESS                  (_OGC_HDR_IG_1200_NOR_ADDRESS + _OGC_HDR_IG_TABLE_SIZE * _ULTRA_HDR_SUPPORT)
#define _OGC_HDR_IG_4000_NOR_ADDRESS                   (_OGC_HDR_IG_1200_DARK_ADDRESS + _OGC_HDR_IG_TABLE_SIZE * _ULTRA_HDR_SUPPORT)
#define _OGC_HDR_IG_4000_DARK_ADDRESS                  (_OGC_HDR_IG_4000_NOR_ADDRESS + _OGC_HDR_IG_TABLE_SIZE * _ULTRA_HDR_SUPPORT)
#define _OGC_HDR_IG_10000_NOR_ADDRESS                  (_OGC_HDR_IG_4000_DARK_ADDRESS + _OGC_HDR_IG_TABLE_SIZE * _ULTRA_HDR_SUPPORT)
#define _OGC_HDR_IG_10000_DARK_ADDRESS                 (_OGC_HDR_IG_10000_NOR_ADDRESS + _OGC_HDR_IG_TABLE_SIZE * _ULTRA_HDR_SUPPORT)
#define _DISP_CALIBRATION_TOTAL_END                    (_OGC_HDR_IG_10000_NOR_ADDRESS + _OGC_HDR_IG_TABLE_SIZE * _ULTRA_HDR_SUPPORT)
#define _DISP_CALIBRATION_TOTAL_SPACE                  (_DISP_CALIBRATION_TOTAL_END - _OGC_RGB_GAIN_ADDRESS)

#define _OGC_CHKSUM_ADDRESS                            (_OCC_GAMMA10_ADDRESS - 1)
#define _OGC_RGB_GAIN_CHKSUM_ADDRESS                   (_OGC_GAMMA1_ADDRESS - 1)
#define _OGC_HEADER_CHKSUM_ADDRESS                     (_OGC_GAMMA1_ADDRESS - 2)
#define _OCC_CHKSUM_ADDRESS                            (_OCC_SRGBMATRIX_ADDRESS - 1)
#define _OCC_COLOR_MATRIX_CHKSUM_ADDRESS               (_OGC_DICOM_ADDRESS - 1)
#define _OGC_DICOM_CHKSUM_ADDRESS                      (_OGC_DICOM_ADDRESS + _OGC_GAMMA_TABLE_SIZE - 1)
#define _OGC_FINISH_ADDRESS                            (_OGC_CHKSUM_ADDRESS - 1)
#define _OCC_FINISH_ADDRESS                            (_OCC_CHKSUM_ADDRESS - 1)
#define _OGC_DICOM_FINISH_ADDRESS                      (_OGC_DICOM_CHKSUM_ADDRESS - 1)
#define _HDR_CHKSUM_ADDRESS                            (_OGC_HDR_IG_1200_NOR_ADDRESS - 1)
#define _HDR_FINISH_ADDRESS                            (_HDR_CHKSUM_ADDRESS - 1)

#if(_ULTRA_HDR_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of HDR Max Mastering Lv
//--------------------------------------------------
#define _HDR_MAX_MASTERING_LV_1200                     1200
#define _HDR_MAX_MASTERING_LV_4000                     4000
#define _HDR_MAX_MASTERING_LV_10000                    10000
#endif

//--------------------------------------------------
// MACRO of Panel Uniformity
//--------------------------------------------------
#define CEILING_OF_INT_DIVISION(x, y)                  (((x) % (y)) ? (((x) / (y)) + 1) : ((x) / (y)))

//--------------------------------------------------
// Address for Panel Uniformity
//--------------------------------------------------
#define _UNIFORMITY_FINISH_ADDRESS                     0 // _UNIFORMITY_GAIN_FINISH_ADDRESS
#define _UNIFORMITY_OFFSET_FINISH_ADDRESS              0

// The checksum of each type is located in last address. It is the reason why we add "+1" in define.
#define _UNIFORMITY_TYPE1_ADDRESS                      1
#define _UNIFORMITY_TYPE2_ADDRESS                      (((_UNIFORMITY_TYPE1_ADDRESS + 2 * ((DWORD)_PANEL_UNIFORMITY_LUT_SIZE + 1)) > 65535) ? 0 : (_UNIFORMITY_TYPE1_ADDRESS + _PANEL_UNIFORMITY_LUT_SIZE + 1))
#define _UNIFORMITY_TYPE3_ADDRESS                      (((_UNIFORMITY_TYPE2_ADDRESS + 2 * ((DWORD)_PANEL_UNIFORMITY_LUT_SIZE + 1)) > 65535) ? 0 : (_UNIFORMITY_TYPE2_ADDRESS + _PANEL_UNIFORMITY_LUT_SIZE + 1))
#define _UNIFORMITY_TYPE4_ADDRESS                      (((_UNIFORMITY_TYPE3_ADDRESS + 2 * ((DWORD)_PANEL_UNIFORMITY_LUT_SIZE + 1)) > 65535) ? 0 : (_UNIFORMITY_TYPE3_ADDRESS + _PANEL_UNIFORMITY_LUT_SIZE + 1))
#define _UNIFORMITY_TYPE5_ADDRESS                      (((_UNIFORMITY_TYPE4_ADDRESS + 2 * ((DWORD)_PANEL_UNIFORMITY_LUT_SIZE + 1)) > 65535) ? 0 : (_UNIFORMITY_TYPE4_ADDRESS + _PANEL_UNIFORMITY_LUT_SIZE + 1))
#define _UNIFORMITY_TYPE6_ADDRESS                      (((_UNIFORMITY_TYPE5_ADDRESS + 2 * ((DWORD)_PANEL_UNIFORMITY_LUT_SIZE + 1)) > 65535) ? 0 : (_UNIFORMITY_TYPE5_ADDRESS + _PANEL_UNIFORMITY_LUT_SIZE + 1))

#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
#define _UNIFORMITY_TYPE1_OFFSET_ADDRESS               1
#define _UNIFORMITY_TYPE2_OFFSET_ADDRESS               (((_UNIFORMITY_TYPE1_OFFSET_ADDRESS + 2 * ((DWORD)_PANEL_UNIFORMITY_OFFSET_LUT_SIZE + 898)) > 65535) ? 0 : (_UNIFORMITY_TYPE1_OFFSET_ADDRESS + _PANEL_UNIFORMITY_OFFSET_LUT_SIZE + 898))// 898 = 1 + _PANEL_UNIFORMITY_DECAY_SIZE + 1, gain_chksum + _PANEL_UNIFORMITY_DECAY_SIZE + decay_chksum
#define _UNIFORMITY_TYPE3_OFFSET_ADDRESS               (((_UNIFORMITY_TYPE2_OFFSET_ADDRESS + 2 * ((DWORD)_PANEL_UNIFORMITY_OFFSET_LUT_SIZE + 898)) > 65535) ? 0 : (_UNIFORMITY_TYPE2_OFFSET_ADDRESS + _PANEL_UNIFORMITY_OFFSET_LUT_SIZE + 898))
#define _UNIFORMITY_TYPE4_OFFSET_ADDRESS               (((_UNIFORMITY_TYPE3_OFFSET_ADDRESS + 2 * ((DWORD)_PANEL_UNIFORMITY_OFFSET_LUT_SIZE + 898)) > 65535) ? 0 : (_UNIFORMITY_TYPE3_OFFSET_ADDRESS + _PANEL_UNIFORMITY_OFFSET_LUT_SIZE + 898))
#define _UNIFORMITY_TYPE5_OFFSET_ADDRESS               (((_UNIFORMITY_TYPE4_OFFSET_ADDRESS + 2 * ((DWORD)_PANEL_UNIFORMITY_OFFSET_LUT_SIZE + 898)) > 65535) ? 0 : (_UNIFORMITY_TYPE4_OFFSET_ADDRESS + _PANEL_UNIFORMITY_OFFSET_LUT_SIZE + 898))
#define _UNIFORMITY_TYPE6_OFFSET_ADDRESS               (((_UNIFORMITY_TYPE5_OFFSET_ADDRESS + 2 * ((DWORD)_PANEL_UNIFORMITY_OFFSET_LUT_SIZE + 898)) > 65535) ? 0 : (_UNIFORMITY_TYPE5_OFFSET_ADDRESS + _PANEL_UNIFORMITY_OFFSET_LUT_SIZE + 898))

// Level0
#define _UNIFORMITY_TYPE1_DECAY_ADDRESS                (_UNIFORMITY_TYPE1_OFFSET_ADDRESS + _PANEL_UNIFORMITY_OFFSET_LUT_SIZE + 1)
#define _UNIFORMITY_TYPE2_DECAY_ADDRESS                (_UNIFORMITY_TYPE2_OFFSET_ADDRESS + _PANEL_UNIFORMITY_OFFSET_LUT_SIZE + 1)
#define _UNIFORMITY_TYPE3_DECAY_ADDRESS                (_UNIFORMITY_TYPE3_OFFSET_ADDRESS + _PANEL_UNIFORMITY_OFFSET_LUT_SIZE + 1)
#define _UNIFORMITY_TYPE4_DECAY_ADDRESS                (_UNIFORMITY_TYPE4_OFFSET_ADDRESS + _PANEL_UNIFORMITY_OFFSET_LUT_SIZE + 1)
#define _UNIFORMITY_TYPE5_DECAY_ADDRESS                (_UNIFORMITY_TYPE5_OFFSET_ADDRESS + _PANEL_UNIFORMITY_OFFSET_LUT_SIZE + 1)
#define _UNIFORMITY_TYPE6_DECAY_ADDRESS                (_UNIFORMITY_TYPE6_OFFSET_ADDRESS + _PANEL_UNIFORMITY_OFFSET_LUT_SIZE + 1)
#endif // #if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)

#define _UNIFORMITY_TYPE1_BANK                         _UNIFORMITY_FLASH_BANK0
#define _UNIFORMITY_TYPE2_BANK                         (((_UNIFORMITY_TYPE1_ADDRESS + 2 * ((DWORD)_PANEL_UNIFORMITY_LUT_SIZE + 1)) > 65535) ? (_UNIFORMITY_TYPE1_BANK + 1) : _UNIFORMITY_TYPE1_BANK)
#define _UNIFORMITY_TYPE3_BANK                         (((_UNIFORMITY_TYPE2_ADDRESS + 2 * ((DWORD)_PANEL_UNIFORMITY_LUT_SIZE + 1)) > 65535) ? (_UNIFORMITY_TYPE2_BANK + 1) : _UNIFORMITY_TYPE2_BANK)
#define _UNIFORMITY_TYPE4_BANK                         (((_UNIFORMITY_TYPE3_ADDRESS + 2 * ((DWORD)_PANEL_UNIFORMITY_LUT_SIZE + 1)) > 65535) ? (_UNIFORMITY_TYPE3_BANK + 1) : _UNIFORMITY_TYPE3_BANK)
#define _UNIFORMITY_TYPE5_BANK                         (((_UNIFORMITY_TYPE4_ADDRESS + 2 * ((DWORD)_PANEL_UNIFORMITY_LUT_SIZE + 1)) > 65535) ? (_UNIFORMITY_TYPE4_BANK + 1) : _UNIFORMITY_TYPE4_BANK)
#define _UNIFORMITY_TYPE6_BANK                         (((_UNIFORMITY_TYPE5_ADDRESS + 2 * ((DWORD)_PANEL_UNIFORMITY_LUT_SIZE + 1)) > 65535) ? (_UNIFORMITY_TYPE5_BANK + 1) : _UNIFORMITY_TYPE5_BANK)

#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
#define _UNIFORMITY_TYPE1_OFFSET_BANK                  (_UNIFORMITY_TYPE1_BANK + CEILING_OF_INT_DIVISION(_UNIFORMITY_TOTAL_SET, (65535 / (_PANEL_UNIFORMITY_LUT_SIZE + 1))))
#define _UNIFORMITY_TYPE2_OFFSET_BANK                  (((_UNIFORMITY_TYPE1_OFFSET_ADDRESS + 2 * ((DWORD)_PANEL_UNIFORMITY_OFFSET_LUT_SIZE + 1)) > 65535) ? (_UNIFORMITY_TYPE1_OFFSET_BANK + 1) : _UNIFORMITY_TYPE1_OFFSET_BANK)
#define _UNIFORMITY_TYPE3_OFFSET_BANK                  (((_UNIFORMITY_TYPE2_OFFSET_ADDRESS + 2 * ((DWORD)_PANEL_UNIFORMITY_OFFSET_LUT_SIZE + 1)) > 65535) ? (_UNIFORMITY_TYPE2_OFFSET_BANK + 1) : _UNIFORMITY_TYPE2_OFFSET_BANK)
#define _UNIFORMITY_TYPE4_OFFSET_BANK                  (((_UNIFORMITY_TYPE3_OFFSET_ADDRESS + 2 * ((DWORD)_PANEL_UNIFORMITY_OFFSET_LUT_SIZE + 1)) > 65535) ? (_UNIFORMITY_TYPE3_OFFSET_BANK + 1) : _UNIFORMITY_TYPE3_OFFSET_BANK)
#define _UNIFORMITY_TYPE5_OFFSET_BANK                  (((_UNIFORMITY_TYPE4_OFFSET_ADDRESS + 2 * ((DWORD)_PANEL_UNIFORMITY_OFFSET_LUT_SIZE + 1)) > 65535) ? (_UNIFORMITY_TYPE4_OFFSET_BANK + 1) : _UNIFORMITY_TYPE4_OFFSET_BANK)
#define _UNIFORMITY_TYPE6_OFFSET_BANK                  (((_UNIFORMITY_TYPE5_OFFSET_ADDRESS + 2 * ((DWORD)_PANEL_UNIFORMITY_OFFSET_LUT_SIZE + 1)) > 65535) ? (_UNIFORMITY_TYPE5_OFFSET_BANK + 1) : _UNIFORMITY_TYPE5_OFFSET_BANK)
// Level0 Decay
#define _UNIFORMITY_TYPE1_DECAY_BANK                   _UNIFORMITY_TYPE1_OFFSET_BANK
#define _UNIFORMITY_TYPE2_DECAY_BANK                   _UNIFORMITY_TYPE2_OFFSET_BANK
#define _UNIFORMITY_TYPE3_DECAY_BANK                   _UNIFORMITY_TYPE3_OFFSET_BANK
#define _UNIFORMITY_TYPE4_DECAY_BANK                   _UNIFORMITY_TYPE4_OFFSET_BANK
#define _UNIFORMITY_TYPE5_DECAY_BANK                   _UNIFORMITY_TYPE5_OFFSET_BANK
#define _UNIFORMITY_TYPE6_DECAY_BANK                   _UNIFORMITY_TYPE6_OFFSET_BANK
#endif// #if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)

#define _UNIFORMITY_TYPE1_CHKSUM_ADDRESS               (_UNIFORMITY_TYPE1_ADDRESS + _PANEL_UNIFORMITY_LUT_SIZE)
#define _UNIFORMITY_TYPE2_CHKSUM_ADDRESS               (_UNIFORMITY_TYPE2_ADDRESS + _PANEL_UNIFORMITY_LUT_SIZE)
#define _UNIFORMITY_TYPE3_CHKSUM_ADDRESS               (_UNIFORMITY_TYPE3_ADDRESS + _PANEL_UNIFORMITY_LUT_SIZE)
#define _UNIFORMITY_TYPE4_CHKSUM_ADDRESS               (_UNIFORMITY_TYPE4_ADDRESS + _PANEL_UNIFORMITY_LUT_SIZE)
#define _UNIFORMITY_TYPE5_CHKSUM_ADDRESS               (_UNIFORMITY_TYPE5_ADDRESS + _PANEL_UNIFORMITY_LUT_SIZE)
#define _UNIFORMITY_TYPE6_CHKSUM_ADDRESS               (_UNIFORMITY_TYPE6_ADDRESS + _PANEL_UNIFORMITY_LUT_SIZE)

#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
#define _UNIFORMITY_TYPE1_OFFSET_CHKSUM_ADDRESS        (_UNIFORMITY_TYPE1_OFFSET_ADDRESS + _PANEL_UNIFORMITY_OFFSET_LUT_SIZE)
#define _UNIFORMITY_TYPE2_OFFSET_CHKSUM_ADDRESS        (_UNIFORMITY_TYPE2_OFFSET_ADDRESS + _PANEL_UNIFORMITY_OFFSET_LUT_SIZE)
#define _UNIFORMITY_TYPE3_OFFSET_CHKSUM_ADDRESS        (_UNIFORMITY_TYPE3_OFFSET_ADDRESS + _PANEL_UNIFORMITY_OFFSET_LUT_SIZE)
#define _UNIFORMITY_TYPE4_OFFSET_CHKSUM_ADDRESS        (_UNIFORMITY_TYPE4_OFFSET_ADDRESS + _PANEL_UNIFORMITY_OFFSET_LUT_SIZE)
#define _UNIFORMITY_TYPE5_OFFSET_CHKSUM_ADDRESS        (_UNIFORMITY_TYPE5_OFFSET_ADDRESS + _PANEL_UNIFORMITY_OFFSET_LUT_SIZE)
#define _UNIFORMITY_TYPE6_OFFSET_CHKSUM_ADDRESS        (_UNIFORMITY_TYPE6_OFFSET_ADDRESS + _PANEL_UNIFORMITY_OFFSET_LUT_SIZE)
// Level0 Decay
#define _UNIFORMITY_TYPE1_DECAY_CHKSUM_ADDRESS         (_UNIFORMITY_TYPE1_DECAY_ADDRESS + _PANEL_UNIFORMITY_DECAY_LUT_SIZE)
#define _UNIFORMITY_TYPE2_DECAY_CHKSUM_ADDRESS         (_UNIFORMITY_TYPE1_DECAY_ADDRESS + _PANEL_UNIFORMITY_DECAY_LUT_SIZE)
#define _UNIFORMITY_TYPE3_DECAY_CHKSUM_ADDRESS         (_UNIFORMITY_TYPE1_DECAY_ADDRESS + _PANEL_UNIFORMITY_DECAY_LUT_SIZE)
#define _UNIFORMITY_TYPE4_DECAY_CHKSUM_ADDRESS         (_UNIFORMITY_TYPE1_DECAY_ADDRESS + _PANEL_UNIFORMITY_DECAY_LUT_SIZE)
#define _UNIFORMITY_TYPE5_DECAY_CHKSUM_ADDRESS         (_UNIFORMITY_TYPE1_DECAY_ADDRESS + _PANEL_UNIFORMITY_DECAY_LUT_SIZE)
#define _UNIFORMITY_TYPE6_DECAY_CHKSUM_ADDRESS         (_UNIFORMITY_TYPE1_DECAY_ADDRESS + _PANEL_UNIFORMITY_DECAY_LUT_SIZE)
#endif // #if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
//--------------------------------------------------
// Auto config error status
//--------------------------------------------------
#define _AUTO_CONFIG_MEASURE_ERROR                     _BIT0
#define _AUTO_CONFIG_CLOCK_ABORT                       _BIT1
#define _AUTO_CONFIG_PHASE_ABORT                       _BIT2

//--------------------------------------------------
// Auto config Percentage Stage
//--------------------------------------------------
#define _AUTO_CONFIG_CHECK_MULTITIMES_FINISH           5
#define _AUTO_CONFIG_CLOCK_CHECK_WIDTH_FINISH          10
#define _AUTO_CONFIG_CLOCK_ROUGH_ADJUST_FINISH         20
#define _AUTO_CONFIG_CLOCK_FINETUNE_FINISH             75
#define _AUTO_CONFIG_CLOCK_FINISH                      80
#define _AUTO_CONFIG_PHASE_FINISH                      90
#define _AUTO_CONFIG_V_POSITION_FINISH                 95
#define _AUTO_CONFIG_H_POSITION_FINISH                 100

//--------------------------------------------------
// Definitions of Clock Settings Used by COsdFxGetAdcClockRange()
//--------------------------------------------------
#ifndef _CUSTOM_CLOCK_BIAS_VALUE
#define _CLOCK_BIAS                                    50
#else
#define _CLOCK_BIAS                                    _CUSTOM_CLOCK_BIAS_VALUE
#endif

#define _GET_CLOCKRANGE_MAX                            0
#define _GET_CLOCKRANGE_MIN                            1

//--------------------------------------------------
// Definitions of Hor. Position Settings Used by COsdFxGetHPositionRange()
//--------------------------------------------------
#define _HPOSITION_BIAS                                (UserCommonAdjustGetHPositionHBiasValue(enumDisplayRegion))
#define _GET_HPOSITIONRANGE_MAX                        (0)
#define _GET_HPOSITIONRANGE_MIN                        (1)

//--------------------------------------------------
// Definitions of Ver. Position Settings Used by COsdFxGetVPositionRange()
//--------------------------------------------------
#define _VPOSITION_BIAS                                (UserCommonAdjustGetVPositionVBiasValue(enumDisplayRegion))
#define _GET_VPOSITIONRANGE_MAX                        (0)
#define _GET_VPOSITIONRANGE_MIN                        (1)

//--------------------------------------------------
// Definitions of Phase Range
//--------------------------------------------------
#define _ADJUST_PHASE_MAX                              63
#define _ADJUST_PHASE_MIN                              0
#define _ADJUST_PHASE_CENTER                           (((_ADJUST_PHASE_MAX - _ADJUST_PHASE_MIN) / 2) + _ADJUST_PHASE_MIN)

//--------------------------------------------------
// // MACRO for Digital H Position
//--------------------------------------------------
#define GET_DIGITAL_H_POSITION()                       (g_ucDigitalHPosition)
#define SET_DIGITAL_H_POSITION(x)                      (g_ucDigitalHPosition = (x))

//--------------------------------------------------
// // MACRO for Digital H Position
//--------------------------------------------------
#define GET_DIGITAL_V_POSITION()                       (g_ucDigitalVPosition)
#define SET_DIGITAL_V_POSITION(x)                      (g_ucDigitalVPosition = (x))

//--------------------------------------------------
// MACRO of Panel Power Sequence
//--------------------------------------------------
#define GET_PANELPOWERSTATUS()                         (g_ucPanelPowerInfo & (_BIT2 | _BIT1 | _BIT0))
#define SET_PANELPOWERSTATUS(x)                        (g_ucPanelPowerInfo = ((g_ucPanelPowerInfo & ~(_BIT2 | _BIT1 | _BIT0)) | (x)))

//--------------------------------------------------
// MACRO for OSD Fail Safe Mode
//--------------------------------------------------
#define GET_FAIL_SAFE_MODE(index)                      (g_pstRegionUserInfo[index].b1FailSafeMode)
#define SET_FAIL_SAFE_MODE(index, x)                   (g_pstRegionUserInfo[index].b1FailSafeMode = (x))

//--------------------------------------------------
// // MACRO for VGA Mode Adjust H Position
//--------------------------------------------------
#define GET_VGA_MODE_ADJUST_H_POSITION()               (g_stVGAModeUserData.ucUserHPosition)
#define SET_VGA_MODE_ADJUST_H_POSITION(x)              (g_stVGAModeUserData.ucUserHPosition = (x))

//--------------------------------------------------
// // MACRO for VGA Mode Adjust V Position
//--------------------------------------------------
#define GET_VGA_MODE_ADJUST_V_POSITION()               (g_stVGAModeUserData.ucUserVPosition)
#define SET_VGA_MODE_ADJUST_V_POSITION(x)              (g_stVGAModeUserData.ucUserVPosition = (x))

//--------------------------------------------------
// // MACRO for VGA Mode Adjust Clock
//--------------------------------------------------
#define GET_VGA_MODE_ADJUST_CLOCK()                    (g_stVGAModeUserData.usUserClock)
#define SET_VGA_MODE_ADJUST_CLOCK(x)                   (g_stVGAModeUserData.usUserClock = (x))

//--------------------------------------------------
// // MACRO for VGA Mode Adjust Phase
//--------------------------------------------------
#define GET_VGA_MODE_ADJUST_PHASE()                    (g_stVGAModeUserData.ucUserPhase)
#define SET_VGA_MODE_ADJUST_PHASE(x)                   (g_stVGAModeUserData.ucUserPhase = (x))

//--------------------------------------------------
// MACRO for VGA Mode Do Auto
//--------------------------------------------------
#define GET_VGA_MODE_DO_FIRST_AUTO()                   (g_stVGAModeUserData.b1DoFirstAuto)
#define SET_VGA_MODE_DO_FIRST_AUTO(x)                  (g_stVGAModeUserData.b1DoFirstAuto = (x))

#if(_EMBEDDED_EDID_SUPPORT == _ON)
#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
//--------------------------------------------------
// MACRO for DP Dual Port EDID Select
//--------------------------------------------------
#define GET_DP_DUAL_PORT_EDID_STATUS_SELECT()          (g_bDpDualPortEdidSwitchSelect)
#define SET_DP_DUAL_PORT_EDID_STATUS_SELECT()          (g_bDpDualPortEdidSwitchSelect = _TRUE)
#define CLR_DP_DUAL_PORT_EDID_STATUS_SELECT()          (g_bDpDualPortEdidSwitchSelect = _FALSE)
#endif
#endif

typedef enum
{
    _WRITE_SIZE_8 = 8,
    _WRITE_SIZE_16 = 16,
    _WRITE_SIZE_32 = 32,
} EnumEepromWriteSize;



#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
#define UserCommonNVRamRead(x, y, z)                   UserCommonEepromRead(x, y, z)
#define UserCommonNVRamSaveSystemData()                UserCommonEepromSaveSystemData()
#define UserCommonNVRamLoadSystemData()                UserCommonEepromLoadSystemData()
#define UserCommonNVRamRestoreSystemData()             UserCommonEepromRestoreSystemData()

#if(_VGA_SUPPORT == _ON)
#define UserCommonNVRamLoadModeUserData(x)             UserCommonEepromLoadModeUserData(x)
#define UserCommonNVRamSaveModeUserData()              UserCommonEepromSaveModeUserData()
#define UserCommonNVRamLoadModeUserModeNumberData(x)   UserCommonEepromLoadModeUserModeNumberData(x)
#define UserCommonNVRamRestoreModeUserData()           UserCommonEepromRestoreModeUserData()
#define UserCommonNVRamVGAFifoModeIndexOffsetInc()     UserCommonEepromVGAFifoModeIndexOffsetInc()
#define UserCommonNVRamGetMaxFifoGroupCnt()            UserCommonEepromGetMaxFifoGroupCnt()
#define UserCommonNVRamSaveADCSetting(x)               UserCommonEepromSaveADCSetting(x)
#define UserCommonNVRamLoadADCSetting(x)               UserCommonEepromLoadADCSetting(x)
#define UserCommonNVRamRestoreADCSetting()             UserCommonEepromRestoreADCSetting()
#endif // End of #if(_VGA_SUPPORT == _ON)

#else
#define UserCommonNVRamRead(x, y, z)                   UserCommonFlashRead(_SYSTEM_EEPROM_EMULATION_FLASH_BANK, x, y, z)
#define UserCommonNVRamSaveSystemData()                UserCommonFlashSaveSystemData()
#define UserCommonNVRamLoadSystemData()                UserCommonFlashLoadSystemData()
#define UserCommonNVRamRestoreSystemData()             UserCommonFlashRestoreSystemData()

#if(_VGA_SUPPORT == _ON)
#define UserCommonNVRamLoadModeUserData(x)             UserCommonFlashLoadModeUserData(x)
#define UserCommonNVRamSaveModeUserData()              UserCommonFlashSaveModeUserData()
#define UserCommonNVRamLoadModeUserModeNumberData(x)   UserCommonFlashLoadModeUserModeNumberData(x)
#define UserCommonNVRamRestoreModeUserData()           UserCommonFlashRestoreModeUserData()
#define UserCommonNVRamVGAFifoModeIndexOffsetInc()     UserCommonFlashVGAFifoModeIndexOffsetInc()
#define UserCommonNVRamGetMaxFifoGroupCnt()            UserCommonFlashGetMaxFifoGroupCnt()
#define UserCommonNVRamSaveADCSetting(x)               UserCommonFlashSaveADCSetting(x)
#define UserCommonNVRamLoadADCSetting(x)               UserCommonFlashLoadADCSetting(x)
#define UserCommonNVRamRestoreADCSetting()             UserCommonFlashRestoreADCSetting()
#endif // End of #if(_VGA_SUPPORT == _ON)

#endif // End of #if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)


#if(_DIGITAL_PORT_SUPPORT == _ON)
#if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
#define UserCommonNVRamGetHDCPKeyBKsv(x, y, z)         UserCommonEepromGetHDCPKeyBKsv(x, y, z)
#define UserCommonNVRamGetHDCPKey(x, y, z)             UserCommonEepromGetHDCPKey(x, y, z)

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
#define UserCommonNVRamRestoreHDCP1P4(x, y, z)         UserCommonEepromRestoreHDCP1P4(x, y, z)
#endif

#if(_DP_TX_SUPPORT == _ON)
#define UserCommonNVRamGetTxHDCPKeyAKsv(x, y, z)       UserCommonEepromGetTxHDCPKeyAKsv(x, y, z)
#define UserCommonNVRamGetTxHDCPKey(x, y, z)           UserCommonEepromGetTxHDCPKey(x, y, z)
#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
#define UserCommonNVRamRestoreTxHDCP(x, y, z)          UserCommonEepromRestoreTxHDCP(x, y, z)
#endif
#endif // End of #if(_DP_TX_SUPPORT == _ON)

#elif(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH)
#define UserCommonNVRamGetHDCPKeyBKsv(x, y, z)         UserCommonFlashGetHDCPKeyBKsv(x, y, z)
#define UserCommonNVRamGetHDCPKey(x, y, z)             UserCommonFlashGetHDCPKey(x, y, z)

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
#define UserCommonNVRamRestoreHDCP1P4(x, y, z)         UserCommonFlashRestoreHDCP1P4(x, y, z)
#endif

#if(_DP_TX_SUPPORT == _ON)
#define UserCommonNVRamGetTxHDCPKeyAKsv(x, y, z)       UserCommonFlashGetTxHDCPKeyAKsv(x, y, z)
#define UserCommonNVRamGetTxHDCPKey(x, y, z)           UserCommonFlashGetTxHDCPKey(x, y, z)
#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
#define UserCommonNVRamRestoreTxHDCP(x, y, z)          UserCommonFlashRestoreTxHDCP(x, y, z)
#endif
#endif // End of #if(_DP_TX_SUPPORT == _ON)

#endif // End of #if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)

#if(_HDCP_2_2_SUPPORT == _ON)
#if(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
#define UserCommonNVRamGetHdcp2Certrx(x, y, z)         UserCommonEepromGetHdcp2Certrx(x, y, z)
#define UserCommonNVRamGetHdcp2RSADkey(x, y, z)        UserCommonEepromGetHdcp2RSADkey(x, y, z)
#define UserCommonNVRamGetHdcp2RSARRModN(x, y, z)      UserCommonEepromGetHdcp2RSARRModN(x, y, z)
#define UserCommonNVRamGetHdcp2RSAKPriv(x, y, z)       UserCommonEepromGetHdcp2RSAKPriv(x, y, z)
#define UserCommonNVRamGetHdcp2RSANpinv(x, y, z)       UserCommonEepromGetHdcp2RSANpinv(x, y, z)
#define UserCommonNVRamGetHdcp2LCKey(x, y, z)          UserCommonEepromGetHdcp2LCKey(x, y, z)

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
#define UserCommonNVRamRestoreHDCP2(x, y, z)           UserCommonEepromRestoreHDCP2(x, y, z)
#endif

#elif(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH)
#define UserCommonNVRamGetHdcp2Certrx(x, y, z)         UserCommonFlashGetHdcp2Certrx(x, y, z)
#define UserCommonNVRamGetHdcp2RSADkey(x, y, z)        UserCommonFlashGetHdcp2RSADkey(x, y, z)
#define UserCommonNVRamGetHdcp2RSARRModN(x, y, z)      UserCommonFlashGetHdcp2RSARRModN(x, y, z)
#define UserCommonNVRamGetHdcp2RSAKPriv(x, y, z)       UserCommonFlashGetHdcp2RSAKPriv(x, y, z)
#define UserCommonNVRamGetHdcp2RSANpinv(x, y, z)       UserCommonFlashGetHdcp2RSANpinv(x, y, z)
#define UserCommonNVRamGetHdcp2LCKey(x, y, z)          UserCommonFlashGetHdcp2LCKey(x, y, z)

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
#define UserCommonNVRamRestoreHDCP2(x, y, z)           UserCommonFlashRestoreHDCP2(x, y, z)
#endif
#endif // End of #if(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
#endif // End of #if(_HDCP_2_2_SUPPORT == _ON)

#endif // End of #if(_DIGITAL_PORT_SUPPORT == _ON)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE b1FailSafeMode : 1;
} StructRegionUserInfoType;

typedef struct
{
    BYTE b1IsPresetMode : 1;
    BYTE b1DoFirstAuto : 1;
    BYTE ucModeNumber;
    BYTE ucUserHPosition;
    BYTE ucUserVPosition;
    WORD usUserClock;
    BYTE ucUserPhase;
    WORD usCenterHPosition;
    WORD usCenterVPosition;
    WORD usCenterClock;
    BYTE ucCenterPhase;
} StructVGAModeUserDataType;

typedef struct
{
    BYTE b1PowerStatus : 1;                     // Monitor Power Status
    BYTE b1DPHotPlugDCOffHigh : 1;              // DPHotPlugDCOffHigh
    BYTE b3HDMIHotPlugSupportTime : 3;          // HDMIHotPlugSupportTime(Unit : 100ms)
    BYTE b1HDMIHotPlugSupport : 1;              // HDMIHotPlugSupport
    BYTE b2AutoTarget : 2;                      // Auto Search Target
//--------------------------------------------------------
    BYTE b2SourceScanType : 2;                  // Source Scan Type
    BYTE b4SearchPort0 : 4;                     // Search Port 0
    BYTE b4SearchPort1 : 4;                     // Search Port 1
//--------------------------------------------------------
    BYTE b4SearchPort2 : 4;                     // Search Port 2
    BYTE b4SearchPort3 : 4;                     // Search Port 3
//--------------------------------------------------------
    BYTE ucDisplayMode;                         // Display Mode
    BYTE ucModeSlotIndex;                       // Mode Slot Index
    BYTE ucSSC;                                 // SSC
//--------------------------------------------------------
    BYTE b3DPEDIDSelect : 3;                    // DP EDID Select
    BYTE b2DualDPEDIDSelect : 2;                // Dual DP Select
    BYTE b3D0DpLanes : 3;
    BYTE b3D1DpLanes : 3;
    BYTE b3D6DpLanes : 3;
//--------------------------------------------------------
    BYTE b1DigitalColorInfoChageReset : 1;      // Digital Color Info Change Reset
//--------------------------------------------------------
    BYTE b3EdidD0 : 3;                          // DP EDID Select by Port
    BYTE b3EdidD1 : 3;
    BYTE b3EdidD2 : 3;
    BYTE b3EdidD3 : 3;
    BYTE b3EdidD4 : 3;
    BYTE b3EdidD5 : 3;
    BYTE b3EdidD6 : 3;
}StructSystemDataType;

typedef struct
{
    BYTE ucESDcrCurRGBAvgValue;
    BYTE ucESDcrPreRGBAvgValue;
    BYTE ucESDcrPWMTargetValue;
    BYTE ucESDcrPWMAdjustValue;
}StructESDcrInfo;

typedef enum
{
    _DP_EDID_1080P = 0,
    _DP_EDID_2560_1440,
    _DP_EDID_4K2K_30HZ,
    _DP_EDID_4K2K_60HZ,
    _DP_EDID_AMOUNT = _DP_EDID_4K2K_60HZ,
}EnumDpEDIDSelection;

typedef enum
{
    _DUAL_DP_EDID_5K3K_60HZ = 0,
    _DUAL_DP_EDID_4K2K_144HZ,
    _DUAL_DP_EDID_AMOUNT = _DUAL_DP_EDID_4K2K_144HZ,
}EnumDualDpEDIDSelection;

#if(_ULTRA_HDR_SUPPORT == _ON)
typedef enum
{
    _HDR_INFO_EOTF_TRADITIONAL_GAMMA_SDR = 0x00,
    _HDR_INFO_EOTF_TRADITIONAL_GAMMA_HDR = 0x01,
    _HDR_INFO_EOTF_SMPTE_ST_2084 = 0x02,
    _HDR_INFO_EOTF_FUTURE_EOTF = 0x03,
    _HDR_INFO_EOTF_RESERVED = 0x04,
} EnumHDRInfoEOTF;

typedef enum
{
    _HDR_INFO_NO_CHANGE = 0x00,
    _HDR_INFO_EOTF_CHANGE = 0x01,
    _HDR_INFO_PRIMARIES_CHANGE = 0x02,
    _HDR_INFO_MAX_LV_CHANGE = 0x03,
}EnumHDRChangeStatus;

typedef enum
{
    _HDR_TARGET_STATUS_DO_NOTHING,
    _HDR_TARGET_STATUS_TRADITIONAL_GAMMA_SDR,
    _HDR_TARGET_STATUS_SMPTE_ST_2084,
} EnumHDRTargetStatus;

typedef enum
{
    _HDR_MODE_OFF,
    _HDR_MODE_AUTO,
    _HDR_MODE_SMPTE_ST_2084,
}EnumHDRModeDef;
#endif

typedef enum
{
    _HDMI_EDID_0 = 0,
    _HDMI_EDID_1,
    _HDMI_EDID_2,
    _HDMI_EDID_AMOUNT = _HDMI_EDID_2,
}EnumHDMIEDIDSelection;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
//----------------------------------------------------------------------------------------
// Extern functions from UserCommonAdjust.c
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// Extern functions from UserCommonInterface.c
//----------------------------------------------------------------------------------------
extern BYTE g_ucDigitalHPosition;
extern BYTE g_ucDigitalVPosition;
extern BYTE g_ucPanelPowerInfo;
extern StructRegionUserInfoType g_pstRegionUserInfo[_MULTI_DISPLAY_MAX];

//----------------------------------------------------------------------------------------
// Extern functions from UserCommonAuto.c
//----------------------------------------------------------------------------------------
#if(_VGA_SUPPORT == _ON)
extern BYTE g_ucAutoConfigStatus;
#endif

#if(_DCC_FUNCTION == _ON)
extern EnumSelRegion g_enumDCCMeasureRegion;
#endif

//----------------------------------------------------------------------------------------
// Extern functions from UserCommonDdcciFunction.c
//----------------------------------------------------------------------------------------
extern BYTE g_pucDdcciGroupRxBuf[_MULTI_DISPLAY_MAX][_DDCCI_RXBUF_LENGTH];
extern BYTE g_ucDDCCIHandlerInx;

#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON) || (_UNIFORMITY_SUPPORT == _ON))
extern BYTE xdata *g_pucDISP_CALIBRATION_FLASH;
#endif


//----------------------------------------------------------------------------------------
// Extern functions from UserCommonNVRamSystem.c
//----------------------------------------------------------------------------------------
extern StructSystemDataType g_stSystemData;

#if(_VGA_SUPPORT == _ON)
extern StructVGAModeUserDataType g_stVGAModeUserData;
extern StructAdcDataType g_stAdcData;
#endif

//----------------------------------------------------------------------------------------
// Extern functions from UserCommonTypecCommunication.c
//----------------------------------------------------------------------------------------
#if(_DP_TYPE_C_SUPPORT == _ON)
#if(_PORT_CONTROLLER_RTS_SMBUS_SUPPORT == _ON)
extern union UnionSMBusRDCommandStrct g_unSMBusRdDataPool;
#endif
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
//----------------------------------------------------------------------------------------
// UserCommonInterface.c
//----------------------------------------------------------------------------------------
extern void UserCommonInterfacePanelPowerAction(BYTE ucEvent);
extern void UserCommonInterfaceOsdResetProc(void);

#if(_VGA_SUPPORT == _ON)
extern void UserCommonInterfaceAdjustADCData(void);
#endif

#if(_ASPECT_RATIO_SUPPORT == _ON)
extern EnumAspectRatioType UserInterfaceGetAspectRatioType(EnumDisplayRegion enumDisplayRegion);
extern void UserInterfaceGetAspectRatio(EnumDisplayRegion enumDisplayRegion, WORD *pusHRatio, WORD *pusVRatio);
extern void UserInterfaceAdjustAspectRatio(EnumDisplayRegion enumDisplayRegion);
#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
extern BYTE UserInterfaceGetAspectRatioOriginalRatio(EnumDisplayRegion enumDisplayRegion);
#endif
#endif

#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON) || (_UNIFORMITY_SUPPORT == _ON))
extern void UserInterfaceAdjustBeforeDisplayCalibration(EnumCaliType enumMode);
extern void UserInterfaceAdjustAfterDisplayCalibration(EnumCaliType enumMode);
#endif

#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
extern bit UserInterfaceGetDpDualDefaultPort(void);
#endif

#if(_EMBEDDED_EDID_SUPPORT == _ON)
extern void UserCommonInterfaceLoadEmbeddedEdidData(void);
extern void UserCommonInterfaceInputPortLoadEdidData(EnumInputPortEdid enumInputPort);

#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
extern void UserCommonInterfaceDpDualPortEdidTableSwitch(BYTE ucInputPort);
extern bit UserCommonInterfaceDpGetDualPortEdidSelectStatus(void);
#endif
#endif

//----------------------------------------------------------------------------------------
// UserCommonAuto.c
//----------------------------------------------------------------------------------------
#if(_VGA_SUPPORT == _ON)
extern void UserCommonAutoConfig(void);
extern bit UserCommonAutoMeasureMultiTimes(void);
#endif

//----------------------------------------------------------------------------------------
// Extern functions from UserCommonAdjust.c
//----------------------------------------------------------------------------------------
extern void UserCommonAdjustDisplayMode(EnumDisplayMode enumDisplayMode);
extern void UserCommonAdjustRegionInputPort(EnumDisplayRegion enumDisplayRegion, EnumSourceSearchPort enumSourceSearchPort);

#if(_VGA_SUPPORT == _ON)
extern WORD UserCommonAdjustGetAdcClockRange(BYTE ucPar);
extern void UserCommonAdjustClock(WORD usUserIHTotal);
extern void UserCommonAdjustPhase(BYTE ucPhase);

#if(_DIG_FILTER_ENHANCE_PHASE_ENABLE == _ENABLE)
extern void UserCommonAdjustDigitalFilterEnhancePhase(void);
#endif

#if(_RINGING_FILTER_SUPPORT == _ON)
extern void UserCommonAdjustRingingFilter(void);
#endif

#if(_YPBPR_SUPPORT == _ON)
extern bit UserCommonInterfaceCheckHDTVMode(BYTE ucModeNumber);
#endif
#endif // End of #if(_VGA_SUPPORT == _ON)

extern WORD UserCommonAdjustGetHPositionRange(BYTE ucPar, EnumDisplayRegion enumDisplayRegion);
extern WORD UserCommonAdjustGetHPositionHBiasValue(EnumDisplayRegion enumDisplayRegion);
extern WORD UserCommonAdjustGetVPositionRange(BYTE ucPar, EnumDisplayRegion enumDisplayRegion);
extern WORD UserCommonAdjustGetVPositionVBiasValue(EnumDisplayRegion enumDisplayRegion);
extern void UserCommonAdjustHPosition(BYTE ucUserHPosition, EnumDisplayRegion enumDisplayRegion);
extern void UserCommonAdjustVPosition(BYTE ucUserVPosition, EnumDisplayRegion enumDisplayRegion);

extern BYTE UserCommonAdjustRealValueToPercent(WORD usRealValue, WORD usMax, WORD usMin, WORD usCenter);
extern WORD UserCommonAdjustPercentToRealValue(BYTE ucPercentValue, WORD usMax, WORD usMin, WORD usCenter);

#if(_OVERSCAN_SUPPORT == _ON)
extern void UserCommonAdjustOverScan(EnumDisplayRegion enumDisplayRegion);
#endif

#if(_ASPECT_RATIO_SUPPORT == _ON)
extern void UserCommonAdjustAspectRatio(EnumDisplayRegion enumDisplayRegion);
#endif

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
extern void UserCommonAdjustRotationInputSize(void);
extern void UserCommonAdjustRotationDisplaySize(void);
#endif

#if(_PIP_DISPLAY_SUPPORT == _ON)
extern void UserCommonAdjustPipSubTimingFormat(void);
#endif

#if(_I_DITHER_SUPPORT == _ON)
extern void UserCommonAdjustIDither(void);
#endif

#if(_ULTRA_VIVID_SUPPORT == _ON)
extern void UserCommonAdjustUltraVivid(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply);
#endif

#if(_D_DITHER_SUPPORT == _ON)
extern void UserCommonAdjustDDither(void);
#endif

#if(_UNIFORMITY_SUPPORT == _ON)
extern void UserCommonAdjustPanelUniformity(EnumUniformityTypeSelect enumUniformityType, EnumUniformityModeSelect enumUniformityMode);
#endif

// 10  bit Panel
extern WORD UserCommonAdjust10bitPanelCompensate(WORD usData);

#if(_ULTRA_HDR_SUPPORT == _ON)
extern EnumHDRChangeStatus UserCommonAdjustHDRChangeStatus(EnumDisplayRegion enumDisplayRegion);
extern EnumHDRTargetStatus UserCommonAdjustHDRTargetStatus(EnumDisplayRegion enumDisplayRegion);
extern EnumHDRTargetStatus UserCommonAdjustHDRAutoModeInitial(EnumDisplayRegion enumDisplayRegion);
extern EnumHDRMaxMasteringLvType UserCommonAdjustHDRGetLvType(EnumDisplayRegion enumDisplayRegion);
extern void UserCommonAdjustHDRAutoMode(EnumDisplayRegion enumDisplayRegion, bit bDarkEnhanceEnable);
extern bit UserCommonAdjustHDREnableStatus(EnumDisplayRegion enumDisplayRegion, EnumHDRModeDef enumHDRModeDef);
#endif

#if(_DCR_SUPPORT == _ON)
extern void UserCommonAdjustDCR(void);
#endif

#if(_FREEZE_SUPPORT == _ON)
extern void UserCommonAdjustDisplayFreeze(bit bEn);
#endif

#if(_SHARPNESS_SUPPORT == _ON)
extern void UserCommonAdjustSharpness(EnumSelRegion enumSelRegion, EnumSourceSearchPort enumSourceSearchPort);
#endif

#if(_FALSE_COLOR_SUPPORT == _ON)
extern void UserCommonAdjustFalseColorAdjust(EnumSelRegion enumSelRegion, BYTE ucLevel, BYTE ucColorCodeLast, BYTE ucColorCodeCur, BYTE ucColorCodeNext);
extern void UserCommonAdjustFalseColorModeChange(EnumSelRegion enumSelRegion, BYTE *pucFalseColorTable, BYTE ucBankNum);
extern void UserCommonAdjustFalseColorEnable(EnumSelRegion enumSelRegion, EnumFunctionOnOFF enumOn);
#endif

//----------------------------------------------------------------------------------------
// Extern functions from UserCommonNVRamSystem.c
//----------------------------------------------------------------------------------------
extern BYTE UserCommonNVRamGetSystemData(EnumSystemDataItemDataType enumDataType);
extern void UserCommonNVRamSetSystemData(EnumSystemDataItemDataType enumDataType, BYTE ucValue);

#if(_EEPROM_ACCESS_FUNCTION_SUPPORT == _ON)
extern bit UserCommonEepromIICRead(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucReadArray, BYTE ucSWIICStatus, BYTE ucHwIICPinNum);
extern bit UserCommonEepromIICWrite(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray, BYTE ucSWIICStatus, BYTE ucHwIICPinNum, EnumEepromWriteSize enumWriteSize);
#endif

//----------------------------------------------------------------------------------------
// Extern functions from UserCommonTypecCommunication.c
//----------------------------------------------------------------------------------------
#if(_DP_TYPE_C_SUPPORT == _ON)
#if(_PORT_CONTROLLER_RTS_SMBUS_SUPPORT == _ON)
extern bit UserCommonTypecCommunicationWrite(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray, BYTE ucInputPort);
extern bit UserCommonTypecCommunicationRead(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucReadArray, BYTE ucInputPort);
extern bit UserCommonTypecCommunicationShortRead(BYTE ucDeviceAddr, BYTE *pucReadArray, BYTE ucInputPort);
extern bit UserCommonTypecCommunicationSMBRead(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucReadArray, BYTE ucSWIICStatus, BYTE ucHwIICPinNum);
extern bit UserCommonTypecCommunicationSMBWrite(BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray, BYTE ucSWIICStatus, BYTE ucHwIICPinNum);
extern bit UserCommonTypecCommunicationPollingPDReady(BYTE ucDeviceAddr, WORD usTime, BYTE ucInputPort);
#endif
#endif

#if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)
extern bit UserCommonEepromRead(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern bit UserCommonEepromWrite(WORD usSubAddr, WORD usLength, BYTE *pucWriteArray);
extern void UserCommonEepromSaveSystemData(void);
extern void UserCommonEepromLoadSystemData(void);
extern void UserCommonEepromRestoreSystemData(void);

#if(_VGA_SUPPORT == _ON)
extern void UserCommonEepromLoadModeUserData(BYTE ucSlotIndex);
extern void UserCommonEepromSaveModeUserData(void);
extern BYTE UserCommonEepromLoadModeUserModeNumberData(BYTE ucSlotIndex);
extern void UserCommonEepromRestoreModeUserData(void);
extern BYTE UserCommonEepromVGAFifoModeIndexOffsetInc(BYTE ucStep);
extern BYTE UserCommonEepromGetMaxFifoGroupCnt(void);
extern void UserCommonEepromLoadADCSetting(EnumColorSpace enumColorFormat);
extern void UserCommonEepromSaveADCSetting(EnumColorSpace enumColorFormat);
extern void UserCommonEepromRestoreADCSetting(void);
#endif

#else // Else of #if(_SYSTEM_EEPROM_EMULATION_SUPPORT == _OFF)

extern bit UserCommonFlashLoadItem(EnumFlashItemIDType enumItemID, BYTE *pucData, BYTE ucLength);
extern bit UserCommonFlashSaveItem(EnumFlashItemIDType enumItemID, BYTE *pucData, BYTE ucLength);
extern void UserCommonFlashSaveSystemData(void);
extern void UserCommonFlashLoadSystemData(void);
extern void UserCommonFlashRestoreSystemData(void);

#if(_VGA_SUPPORT == _ON)
extern void UserCommonFlashLoadModeUserData(BYTE ucSlotIndex);
extern void UserCommonFlashSaveModeUserData(void);
extern BYTE UserCommonFlashLoadModeUserModeNumberData(BYTE ucSlotIndex);
extern void UserCommonFlashRestoreModeUserData(void);
extern BYTE UserCommonFlashVGAFifoModeIndexOffsetInc(BYTE ucStep);
extern BYTE UserCommonFlashGetMaxFifoGroupCnt(void);
extern void UserCommonFlashLoadADCSetting(EnumColorSpace enumColorFormat);
extern void UserCommonFlashSaveADCSetting(EnumColorSpace enumColorFormat);
extern void UserCommonFlashRestoreADCSetting(void);
#endif

#endif // Else of #elif(_SYSTEM_EEPROM_EMULATION_SUPPORT == _ON)

// EDID
#if((_WRITE_EDID_TO_SYSTEM_EEPROM == _ON) &&\
    ((_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D0_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D1_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D2_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D3_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D4_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM) ||\
     (_D5_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_SYSTEM_EEPROM)))
extern void UserCommonEepromRestoreEDID(WORD usOffset, BYTE ucLength, BYTE *pucBuf);
#endif

#if((_WRITE_EDID_TO_SYSTEM_EEPROM == _ON) &&\
    ((_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D0_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D1_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D2_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D3_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D4_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH) ||\
     (_D5_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)))
extern void UserCommonFlashRestoreEDID(WORD usAddr, BYTE ucLength, BYTE *pucBuf);
#endif

// HDCP
#if(_DIGITAL_PORT_SUPPORT == _ON)
#if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
extern void UserCommonEepromGetHDCPKeyBKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
extern void UserCommonEepromGetHDCPKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);

#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
extern void UserCommonEepromRestoreHDCP1P4(WORD usOffset, BYTE ucLength, BYTE *pucBuf);
#endif

#if(_DP_TX_SUPPORT == _ON)
extern void UserCommonEepromGetTxHDCPKeyAKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
extern void UserCommonEepromGetTxHDCPKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
extern void UserCommonEepromRestoreTxHDCP(WORD usOffset, BYTE ucLength, BYTE *pucBuf);
#endif
#endif // End of #if(_DP_TX_SUPPORT == _ON)

#elif(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_FLASH)

extern void UserCommonFlashGetHDCPKeyBKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
extern void UserCommonFlashGetHDCPKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
extern void UserCommonFlashRestoreHDCP1P4(WORD usAddr, BYTE ucLength, BYTE *pucBuf);
#endif

#if(_DP_TX_SUPPORT == _ON)
extern void UserCommonFlashGetTxHDCPKeyAKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
extern void UserCommonFlashGetTxHDCPKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
extern void UserCommonFlashRestoreTxHDCP(WORD usOffset, BYTE ucLength, BYTE *pucBuf);
#endif
#endif // End of #if(_DP_TX_SUPPORT == _ON)

#endif // End of #if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)

#if(_HDCP_2_2_SUPPORT == _ON)
#if(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
extern void UserCommonEepromGetHdcp2Certrx(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonEepromGetHdcp2RSADkey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonEepromGetHdcp2RSARRModN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonEepromGetHdcp2RSAKPriv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonEepromGetHdcp2RSANpinv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonEepromGetHdcp2LCKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
extern void UserCommonEepromRestoreHDCP2(WORD usOffset, BYTE ucLength, BYTE *pucBuf);
#endif

#elif(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_FLASH)
extern void UserCommonFlashGetHdcp2Certrx(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonFlashGetHdcp2RSADkey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonFlashGetHdcp2RSARRModN(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonFlashGetHdcp2RSAKPriv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonFlashGetHdcp2RSANpinv(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern void UserCommonFlashGetHdcp2LCKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#if(_WRITE_HDCP_TO_SYSTEM_EEPROM == _ON)
extern void UserCommonFlashRestoreHDCP2(WORD usAddr, BYTE ucLength, BYTE *pucBuf);
#endif
#endif // End of #if(_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_SYSTEM_EEPROM)
#endif // End of #if(_HDCP_2_2_SUPPORT == _ON)

#endif // End of #if(_DIGITAL_PORT_SUPPORT == _ON)


#if(_FLASH_ACCESS_FUNCTION_SUPPORT == _ON)
extern bit UserCommonFlashErasePage(BYTE ucBank, BYTE ucPage);
extern bit UserCommonFlashWrite(BYTE ucBank, WORD usAddr, WORD usLength, BYTE *pucData);
extern bit UserCommonFlashRead(BYTE ucBank, WORD usAddr, WORD usLength, BYTE *pucData);
#endif


#if(_FLASH_WR_PROTECT == _ON)
extern void UserCommonFlashWRProtect(void);
#endif

//----------------------------------------------------------------------------------------
// Extern functions from UserCommonDdcciFunction.c
//----------------------------------------------------------------------------------------
extern void UserCommonDdcciInitTx(void);
extern void UserCommonDdcciInitRx(void);
extern BYTE UserCommonDdcciCalCheckSum(void);
extern void UserCommonDdcciSetVCPReplyValue(BYTE ucTypeOpcode, WORD usMax, WORD usPresent);
extern void UserCommonDdcciGetTimingReport(EnumDisplayRegion enumDisplayRegion);
extern void UserCommonDdcciGetCapabilitiesRequest(EnumDDCCIPort enumDdcciChannel);
extern void UserCommonDdcciMapping(void);

//----------------------------------------------------------------------------------------
// Extern functions from UserCommonDisplayCalibration.c
//----------------------------------------------------------------------------------------
#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON))
extern void UserCommonDdcciDispCalibProcess(void);
extern BYTE UserCommonDdcciDispCalibCalCheckSum(BYTE ucCheckType);
#endif

//----------------------------------------------------------------------------------------
// Extern functions from UserModeSearch.c
//----------------------------------------------------------------------------------------
#if(_VGA_SUPPORT == _ON)
extern BYTE UserCommonModeSearchCheckFIFOModeSaved(BYTE ucModeIndex);
extern void UserCommonModeSearchInitalUserAndCenterData(BYTE ucIndex);
extern WORD UserCommonModeSearchGetModetableTimingDataItem(BYTE ucModeNumber, EnumTimingInfoSelect enumTimingInfo);
extern bit UserCommonModeSearchCheckPresetModeTable(BYTE ucMatchmode);
#endif

//----------------------------------------------------------------------------------------
// Extern functions from UserOsd.c
//----------------------------------------------------------------------------------------
extern void UserOsdHandler(void);

#if(_EMBEDDED_EDID_SUPPORT == _ON)
extern void UserCommonInterfaceLoadEmbeddedEdidData(void);
#endif

#if(_HDMI_MULTI_EDID_SUPPORT == _ON)
extern void UserCommonInterfaceHDMISwithEdid(BYTE ucInputport, EnumHDMIEDIDSelection enumHDMIEDIDSelection);
#endif
