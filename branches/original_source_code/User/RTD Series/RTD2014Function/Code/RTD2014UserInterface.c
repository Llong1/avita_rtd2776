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
// ID Code      : RTD2014UserInterface.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE__

#include "UserCommonInclude.h"

#if(_OSD_TYPE == _REALTEK_2014_OSD)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _USER_SHOW_LOGO_STEP                    18 // frames

#define _EDID_VENDOR_SPEC_0                     160
#define _EDID_CHKSUM                            255

//-------------------------------------------------------
//  Definitions of RCP Key Codes
//-------------------------------------------------------
#define _MHL_RCP_VOLUME_UP                      0x41
#define _MHL_RCP_VOLUME_DOWN                    0x42
#define _MHL_RCP_MUTE                           0x43
#define _MHL_RCP_MUTE_FUNCTION                  0x65
#define _MHL_RCP_RESTORE_VOLUME_FUNCTION        0x66

//--------------------------------------------------
// Definitions of DCR THD Setting
//--------------------------------------------------
#define _DCR_THESHOLD1                          0x20
#define _DCR_THESHOLD2                          0x180

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************
//----------------------------------------------------------------------------------------------------
// EDID Table
//----------------------------------------------------------------------------------------------------
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON))
#if(_DP_SUPPORT == _ON)
BYTE code tEDID_TABLE_DP_1080P[] =
{
#include "./EDID/EdidDp/EDID_DP_1920_1080_60HZ.h"
};

BYTE code tEDID_TABLE_DP_2K1K[] =
{
#include "./EDID/EdidDp/EDID_DP_2560_1440_60HZ_DELL.h"
};

BYTE code tEDID_TABLE_DP_4K2K_30[] =
{
#include "./EDID/EdidDp/EDID_DP_3840_2160_30HZ_DELL.h"
};

BYTE code tEDID_TABLE_DP_4K2K_60[] =
{
#include "./EDID/EdidDp/EDID_DP_3840_2160_60HZ_RTK.h"
};

#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
BYTE code tEDID_TABLE_DP_5K3K_60_D0[] =
{
#if(_D7_D0_EMBEDDED_DDCRAM_SIZE == _EDID_SIZE_384)
#include "./EDID/EdidDp/EDID_DP_5120_2880_60HZ_384.h"
#else
#include "./EDID/EdidDp/EDID_DP_5120_2880_60HZ_256.h"
#endif
};

BYTE code tEDID_TABLE_DP_5K3K_60_D1[] =
{
#if(_D7_D1_EMBEDDED_DDCRAM_SIZE == _EDID_SIZE_384)
#include "./EDID/EdidDp/EDID_DP_5120_2880_60HZ_384.h"
#else
#include "./EDID/EdidDp/EDID_DP_5120_2880_60HZ_256.h"
#endif
};

BYTE code tEDID_TABLE_DP_4K2K_144_D0[] =
{
#if(_D7_D0_EMBEDDED_DDCRAM_SIZE == _EDID_SIZE_384)
#include "./EDID/EdidDp/EDID_DP_3840_2160_144HZ_384.h"
#else
#include "./EDID/EdidDp/EDID_DP_3840_2160_144HZ_256.h"
#endif
};

BYTE code tEDID_TABLE_DP_4K2K_144_D1[] =
{
#if(_D7_D1_EMBEDDED_DDCRAM_SIZE == _EDID_SIZE_384)
#include "./EDID/EdidDp/EDID_DP_3840_2160_144HZ_384.h"
#else
#include "./EDID/EdidDp/EDID_DP_3840_2160_144HZ_256.h"
#endif
};
#endif
#endif

#if(_D0_HDMI_SUPPORT == _ON)

BYTE code tHDMI14_EDID_TABLE_D0[] =
{
#include ".\EDID\EdidHdmi\EDID_HDMI_1920_1080_60HZ.h"
};

BYTE code tHDMI20_EDID_TABLE_D0[] =
{
#if(_HDMI_2_0_YCBCR420_SUPPORT == _ON)
#include ".\EDID\EdidHdmi\EDID_HDMI2_3840_2160_60HZ_NO_HFVSDB_WITH_420.h"
#else
#include ".\EDID\EdidHdmi\EDID_HDMI2_3840_2160_60HZ_NO_HFVSDB_NO_420.h"
#endif
};

BYTE code tHDMI20_HDR_EDID_TABLE_D0[] =
{
#include ".\EDID\EdidHdmi\EDID_HDMI2_3840_2160_60HZ_WITH_HFVSDB_NO_420_HDR.h"
};

#endif

#if(_D1_HDMI_SUPPORT == _ON)

BYTE code tHDMI14_EDID_TABLE_D1[] =
{
#include ".\EDID\EdidHdmi\EDID_HDMI_1920_1080_60HZ.h"
};

BYTE code tHDMI20_EDID_TABLE_D1[] =
{
#if(_HDMI_2_0_YCBCR420_SUPPORT == _ON)
#include ".\EDID\EdidHdmi\EDID_HDMI2_3840_2160_60HZ_NO_HFVSDB_WITH_420.h"
#else
#include ".\EDID\EdidHdmi\EDID_HDMI2_3840_2160_60HZ_NO_HFVSDB_NO_420.h"
#endif
};

BYTE code tHDMI20_HDR_EDID_TABLE_D1[] =
{
#include ".\EDID\EdidHdmi\EDID_HDMI2_3840_2160_60HZ_WITH_HFVSDB_NO_420_HDR.h"
};

#endif

#if(_D2_HDMI_SUPPORT == _ON)

BYTE code tHDMI14_EDID_TABLE_D2[] =
{
#include ".\EDID\EdidHdmi\EDID_HDMI_1920_1080_60HZ.h"
};

BYTE code tHDMI20_EDID_TABLE_D2[] =
{
#if(_HDMI_2_0_YCBCR420_SUPPORT == _ON)
#include ".\EDID\EdidHdmi\EDID_HDMI2_3840_2160_60HZ_NO_HFVSDB_WITH_420.h"
#else
#include ".\EDID\EdidHdmi\EDID_HDMI2_3840_2160_60HZ_NO_HFVSDB_NO_420.h"
#endif
};

BYTE code tHDMI20_HDR_EDID_TABLE_D2[] =
{
#include ".\EDID\EdidHdmi\EDID_HDMI2_3840_2160_60HZ_WITH_HFVSDB_NO_420_HDR.h"
};

#endif

#if(_D3_HDMI_SUPPORT == _ON)

BYTE code tHDMI14_EDID_TABLE_D3[] =
{
#include ".\EDID\EdidHdmi\EDID_HDMI_1920_1080_60HZ.h"
};

BYTE code tHDMI20_EDID_TABLE_D3[] =
{
#if(_HDMI_2_0_YCBCR420_SUPPORT == _ON)
#include ".\EDID\EdidHdmi\EDID_HDMI2_3840_2160_60HZ_NO_HFVSDB_WITH_420.h"
#else
#include ".\EDID\EdidHdmi\EDID_HDMI2_3840_2160_60HZ_NO_HFVSDB_NO_420.h"
#endif
};

BYTE code tHDMI20_HDR_EDID_TABLE_D3[] =
{
#include ".\EDID\EdidHdmi\EDID_HDMI2_3840_2160_60HZ_WITH_HFVSDB_NO_420_HDR.h"
};

#endif

#if(_D4_HDMI_SUPPORT == _ON)

BYTE code tHDMI14_EDID_TABLE_D4[] =
{
#include ".\EDID\EdidHdmi\EDID_HDMI_1920_1080_60HZ.h"
};

BYTE code tHDMI20_EDID_TABLE_D4[] =
{
#if(_HDMI_2_0_YCBCR420_SUPPORT == _ON)
#include ".\EDID\EdidHdmi\EDID_HDMI2_3840_2160_60HZ_NO_HFVSDB_WITH_420.h"
#else
#include ".\EDID\EdidHdmi\EDID_HDMI2_3840_2160_60HZ_NO_HFVSDB_NO_420.h"
#endif
};

BYTE code tHDMI20_HDR_EDID_TABLE_D4[] =
{
#include ".\EDID\EdidHdmi\EDID_HDMI2_3840_2160_60HZ_WITH_HFVSDB_NO_420_HDR.h"
};

#endif

#if(_D5_HDMI_SUPPORT == _ON)

BYTE code tHDMI14_EDID_TABLE_D5[] =
{
#include ".\EDID\EdidHdmi\EDID_HDMI_1920_1080_60HZ.h"
};

BYTE code tHDMI20_EDID_TABLE_D5[] =
{
#if(_HDMI_2_0_YCBCR420_SUPPORT == _ON)
#include ".\EDID\EdidHdmi\EDID_HDMI2_3840_2160_60HZ_NO_HFVSDB_WITH_420.h"
#else
#include ".\EDID\EdidHdmi\EDID_HDMI2_3840_2160_60HZ_NO_HFVSDB_NO_420.h"
#endif
};

BYTE code tHDMI20_HDR_EDID_TABLE_D5[] =
{
#include ".\EDID\EdidHdmi\EDID_HDMI2_3840_2160_60HZ_WITH_HFVSDB_NO_420_HDR.h"
};

#endif

#endif

#if(_SHARPNESS_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// Filter Coefficient Table (Sharpness)
//----------------------------------------------------------------------------------------------------
#if((_HSU_128TAPS_SUPPORT == _ON) || (_VSU_128TAPS_SUPPORT == _ON))
BYTE code tSU_COEF_128_TAPS_0[] =
{
#include "./Sharpness/Sharpness128TapsNormalTable0.h"
};

BYTE code tSU_COEF_128_TAPS_2[] =
{
#include "./Sharpness/Sharpness128TapsNormalTable2.h"
};

BYTE code tSU_COEF_128_TAPS_4[] =
{
#include "./Sharpness/Sharpness128TapsNormalTable4.h"
};

BYTE code tSU_COEF_128_TAPS_6[] =
{
#include "./Sharpness/Sharpness128TapsNormalTable6.h"
};

BYTE code tSU_COEF_128_TAPS_8[] =
{
#include "./Sharpness/Sharpness128TapsNormalTable8.h"
};

code BYTE *tSCALE_128TAPS_NORMAL_COEF_TABLE[] =
{
    tSU_COEF_128_TAPS_0,
    tSU_COEF_128_TAPS_2,
    tSU_COEF_128_TAPS_4,
    tSU_COEF_128_TAPS_6,
    tSU_COEF_128_TAPS_8,
};
#endif // End of #if((_HSU_128TAPS_SUPPORT == _ON) || (_VSU_128TAPS_SUPPORT == _ON))

#if(_HSU_128TAPS_SUPPORT == _ON)
BYTE code tSU_1to1_COEF_128_TAPS_0[] =
{
#include "./Sharpness/Sharpness128Taps1to1Table0.h"
};

BYTE code tSU_1to1_COEF_128_TAPS_2[] =
{
#include "./Sharpness/Sharpness128Taps1to1Table2.h"
};

BYTE code tSU_1to1_COEF_128_TAPS_4[] =
{
#include "./Sharpness/Sharpness128Taps1to1Table4.h"
};

BYTE code tSU_1to1_COEF_128_TAPS_6[] =
{
#include "./Sharpness/Sharpness128Taps1to1Table6.h"
};

BYTE code tSU_1to1_COEF_128_TAPS_8[] =
{
#include "./Sharpness/Sharpness128Taps1to1Table8.h"
};

code BYTE *tSCALE_128TAPS_1to1_COEF_TABLE[] =
{
    tSU_1to1_COEF_128_TAPS_0,
    tSU_1to1_COEF_128_TAPS_2,
    tSU_1to1_COEF_128_TAPS_4,
    tSU_1to1_COEF_128_TAPS_6,
    tSU_1to1_COEF_128_TAPS_8,
};
#endif // End of #if(_HSU_128TAPS_SUPPORT == _ON)

#if((_HSU_96TAPS_SUPPORT == _ON) || (_VSU_96TAPS_SUPPORT == _ON))
BYTE code tSU_COEF_96_TAPS_0[] =
{
#include "./Sharpness/Sharpness96TapsNormalTable0.h"
};

BYTE code tSU_COEF_96_TAPS_2[] =
{
#include "./Sharpness/Sharpness96TapsNormalTable2.h"
};

BYTE code tSU_COEF_96_TAPS_4[] =
{
#include "./Sharpness/Sharpness96TapsNormalTable4.h"
};

BYTE code tSU_COEF_96_TAPS_6[] =
{
#include "./Sharpness/Sharpness96TapsNormalTable6.h"
};

BYTE code tSU_COEF_96_TAPS_8[] =
{
#include "./Sharpness/Sharpness96TapsNormalTable8.h"
};

code BYTE *tSCALE_96TAPS_NORMAL_COEF_TABLE[] =
{
    tSU_COEF_96_TAPS_0,
    tSU_COEF_96_TAPS_2,
    tSU_COEF_96_TAPS_4,
    tSU_COEF_96_TAPS_6,
    tSU_COEF_96_TAPS_8,
};
#endif // End of #if((_HSU_96TAPS_SUPPORT == _ON) || (_VSU_96TAPS_SUPPORT == _ON))

#if(_HSU_96TAPS_SUPPORT == _ON)
BYTE code tSU_1to1_COEF_96_TAPS_0[] =
{
#include "./Sharpness/Sharpness96Taps1to1Table0.h"
};

BYTE code tSU_1to1_COEF_96_TAPS_2[] =
{
#include "./Sharpness/Sharpness96Taps1to1Table2.h"
};

BYTE code tSU_1to1_COEF_96_TAPS_4[] =
{
#include "./Sharpness/Sharpness96Taps1to1Table4.h"
};

BYTE code tSU_1to1_COEF_96_TAPS_6[] =
{
#include "./Sharpness/Sharpness96Taps1to1Table6.h"
};

BYTE code tSU_1to1_COEF_96_TAPS_8[] =
{
#include "./Sharpness/Sharpness96Taps1to1Table8.h"
};

code BYTE *tSCALE_96TAPS_1to1_COEF_TABLE[] =
{
    tSU_1to1_COEF_96_TAPS_0,
    tSU_1to1_COEF_96_TAPS_2,
    tSU_1to1_COEF_96_TAPS_4,
    tSU_1to1_COEF_96_TAPS_6,
    tSU_1to1_COEF_96_TAPS_8,
};
#endif // End of #if(_HSU_96TAPS_SUPPORT == _ON)
#endif // End of #if(_SHARPNESS_SUPPORT == _ON)

#if(_ULTRA_VIVID_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// ULTRAVIVID TABLE
//----------------------------------------------------------------------------------------------------
BYTE code tCOLOR_ULTRAVIVID_SETTING_L[] =
{
#include "./UltraVivid/UltraVividTableL.h"
};

BYTE code tCOLOR_ULTRAVIVID_SETTING_M[] =
{
#include "./UltraVivid/UltraVividTableM.h"
};

BYTE code tCOLOR_ULTRAVIVID_SETTING_H[] =
{
#include "./UltraVivid/UltraVividTableH.h"
};

code BYTE *tCOLOR_ULTRAVIVID_SETTING_TABLE[] =
{
    tCOLOR_ULTRAVIVID_SETTING_L,
    tCOLOR_ULTRAVIVID_SETTING_M,
    tCOLOR_ULTRAVIVID_SETTING_H,
};
#endif  // End of #if(_ULTRA_VIVID_SUPPORT == _ON)


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_UART_SUPPORT == _ON)
//BYTE g_pucUartData[5];
#endif

#if(_DCC_FUNCTION == _ON)
EnumSelRegion g_enumDCCMeasureRegion = _NON_REGION;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void UserInterfaceTimerEventProc(EnumScalerTimerEventID enumEventID);

//-------------------------------------------------------
// INT
//-------------------------------------------------------
#if(_INSTANT_TIMER_EVENT_0 == _ON)
void UserInterfaceTimer0InstantAccess_EXINT(void);
#endif

#if(_INSTANT_TIMER_EVENT_1 == _ON)
void UserInterfaceTimer1InstantAccess_EXINT(void);
#endif

#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
void UserInterfaceTimer2InstantAccess_EXINT(void);
#endif

#if(_UART_SUPPORT == _ON)
void UserInterfaceUartIntHandler_SERIALPORT(void);
#endif

#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
BYTE UserInterfaceGetDdcciStatus_EXINT1(void);
BYTE UserInterfaceGetFactoryCommand_EXINT1(void);

#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
BYTE UserInterfaceDdcciHDMIFreesyncOpcode_EXINT1(BYTE ucOpcode);
#endif
#endif

//-------------------------------------------------------
// EDID & HDCP
//-------------------------------------------------------
#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON))
void UserInterfaceGetEmbeddedEDIDData(EnumInputPortEdid enumInputPort);
#endif

#if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_USER)
void UserInterfaceGetHDCPKeyBksvByUser(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
void UserInterfaceGetHDCPKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);

#if(_DP_TX_SUPPORT == _ON)
void UserInterfaceGetTxHDCPKeyAksvByUser(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
void UserInterfaceGetTxHDCPKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#endif
#endif

#if((_HDCP_2_2_SUPPORT == _ON) && (_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_USER))
void UserInterfaceGetHdcp2CertrxByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserInterfaceGetHdcp2RSADkeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserInterfaceGetHdcp2RSARRModNByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserInterfaceGetHdcp2RSAKPrivByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserInterfaceGetHdcp2RSANpinvByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
void UserInterfaceGetHdcp2LCKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
#endif


//-------------------------------------------------------
// Wait for Panel Power Sequence Delay
//-------------------------------------------------------
void UserInterfaceAdjustWaitPanelT1(void);
void UserInterfaceAdjustWaitPanelT2(void);
void UserInterfaceAdjustWaitPanelT3(void);
void UserInterfaceAdjustWaitPanelT4(void);
void UserInterfaceAdjustWaitPanelT5(void);


//-------------------------------------------------------
//
//-------------------------------------------------------
void UserInterfaceUncallFunction(void);
void UserInterfaceInitial(void);

void UserInterfacePowerSwitch(EnumPowerAction enumSwitch);
void UserInterfaceKeyPadLedControl(BYTE ucKeyPadLed);

//-------------------------------------------------------
// Input Information
//-------------------------------------------------------
EnumDisplayRegion UserInterfaceGetAutoSearchTarget(void);
EnumSourceSearchPort UserInterfaceGetInputPort0(void);

#if(_MULTI_DISPLAY_MAX >= 0x02)
EnumSourceSearchPort UserInterfaceGetInputPort1(void);
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
EnumSourceSearchPort UserInterfaceGetInputPort2(void);
EnumSourceSearchPort UserInterfaceGetInputPort3(void);
#endif

//-------------------------------------------------------
// User Information
//-------------------------------------------------------
bit UserInterfaceGetLogoStatus(void);
bit UserInterfaceGetdNoSupportStatus(EnumDisplayRegion enumDisplayRegion);
bit UserInterfaceGetDclkNoSupportStatus(void);
bit UserInterfaceGetActiveByPassStatus(EnumDisplayRegion enumDisplayRegion);
bit UserInterfaceGetCableResetStatus(EnumDisplayRegion enumDisplayRegion);
bit UserInterfaceGetForcePSStatus(void);
bit UserInterfaceGetIntoPSStatus(void);
bit UserInterfaceGetNVRamDataStatus(EnumNvramCheckType enumNvramCheckType);
bit UserInterfaceGetRegionAutoSearchStatus(EnumDisplayRegion enumDisplayRegion, EnumSourceSearchPort enumSourceSearchPort);
bit UserInterfaceGetDisplaySettingBacklightAction(void);
EnumColorSpace UserInterfaceGetColorFormat(EnumDisplayRegion enumDisplayRegion);
EnumDisplayMode UserInterfaceGetMultiDisplayMode(void);

#if(_OVERSCAN_SUPPORT == _ON)
bit UserInterfaceGetOverScanStatus(EnumDisplayRegion enumDisplayRegion);
#endif

#if(_ASPECT_RATIO_SUPPORT == _ON)
EnumAspectRatioType UserInterfaceGetAspectRatioType(EnumDisplayRegion enumDisplayRegion);
void UserInterfaceGetAspectRatio(EnumDisplayRegion enumDisplayRegion, WORD *pusHRatio, WORD *pusVRatio);
void UserInterfaceAdjustAspectRatio(EnumDisplayRegion enumDisplayRegion);

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
BYTE UserInterfaceGetAspectRatioOriginalRatio(EnumDisplayRegion enumDisplayRegion);
#endif

#endif

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
EnumRotationType UserInterfaceGetRotationDegree(void);
EnumRotationDisplayType UserInterfaceGetRotationDisplayType(void);
#endif

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
BYTE UserInterfaceGetDisplayLatencyRatio(void);
void UserInterfaceGetDVMaxMinFreq(StructDVCustomizedFreq *pstDVCustomizedFreq);
#endif

#if(_OD_SUPPORT == _ON)
EnumFunctionOnOFF UserInterfaceGetODEnableStatus(void);
#endif

#if((_MEMORY_TYPE_CONFIG == _MEMORY_DDR3) && (_DDR3_MULTIPHASE_EXIST == _ON))
void UserInterfaceUpdateDDR3PhaseData(void);
#endif

//-------------------------------------------------------
// Display Timing
//-------------------------------------------------------
void UserInterfaceAdjustInputTiming(EnumDisplayRegion enumDisplayRegion);
void UserInterfaceAdjustDisplayTiming(EnumDisplayRegion enumDisplayRegion);

#if(_PIP_DISPLAY_SUPPORT == _ON)
StructTimingFormat UserInterfaceGetPipSubTimingFormat(void);
#endif

#if((_PBP_LR_DISPLAY_SUPPORT == _ON) && (_D_DOMAIN_PATH != _D_DOMAIN_4_PATH))
StructTimingFormat UserInterfaceGetPbpTimingFormat(EnumDisplayRegion enumDisplayRegion);
#endif

//-------------------------------------------------------
// Color
//-------------------------------------------------------
#if(_RGB_QUANTIZATION_RANGE_SUPPORT == _ON)
bit UserInterfaceGetRGBQuantizationLimitRangeStatus(EnumDisplayRegion enumDisplayRegion, EnumColorRGBQuantization enumColorRGBQuantization);
#endif

#if(_YCC_QUANTIZATION_RANGE_SUPPORT == _ON)
bit UserInterfaceGetYCCQuantizationFullRangeStatus(EnumDisplayRegion enumDisplayRegion, EnumColorYCCQuantization enumColorYCCQuantization);
#endif

void UserInterfaceAdjustInitialColorProc(EnumDisplayMode enumDisplayMode);
void UserInterfaceAdjustColorProc(EnumDisplayRegion enumDisplayRegion);
#if(_ULTRA_HDR_SUPPORT == _ON)
void UserInterfaceAdjustHDRColorProcInitial(EnumDisplayRegion enumDisplayRegion);
#endif
void UserInterfaceAdjustActiveByPassColorProc(EnumDisplayRegion enumDisplayRegion);

#if(_ULTRA_VIVID_SUPPORT == _ON)
void UserInterfaceAdjustUltraVivid(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply);
#endif

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
void UserInterfaceAdjustHighlightWindow(EnumDBApply enumDBApply);
#endif

#if(_BORDER_WINDOW_SUPPORT == _ON)
void UserInterfaceAdjustBorderWindow(EnumDBApply enumDBApply);
#endif

#if(_SHARPNESS_SUPPORT == _ON)
code BYTE *UserInterfaceGetSharpnessCoef(EnumSUCoefType enumSUCoefType, EnumSelRegion enumSelRegion, EnumSourceSearchPort enumSourceSearchPort);
BYTE UserInterfaceGetSharpnessCoefBankNum(void);
bit UserInterfaceSharpnessBypassCheck(void);
#endif

#if(_DCR_SUPPORT == _ON)
void UserInterfaceAdjustDCR(void);
#endif

//-------------------------------------------------------
// Osd
//-------------------------------------------------------
void UserInterfaceAdjustOsdPowerOnInitial(void);
void UserInterfaceAdjustOsdActiveProc(EnumDisplayRegion enumDisplayRegion);
void UserInterfaceAdjustOsdResetProc(void);
void UserInterfaceAdjustOsdResetRegionProc(EnumDisplayRegion enumDisplayRegion);
void UserInterfaceAdjustOsdResumeRegionProc(EnumDisplayRegion enumDisplayRegion);


//-------------------------------------------------------
// Interfaces
//-------------------------------------------------------
#if(_VGA_SUPPORT == _ON)
BYTE UserInterfaceGetVGAConfuseMode(BYTE ucModeIndex);
bit UserInterfaceGetLoadModeTableDefaultStatus(void);
bit UserInterfaceGetFirstAutoConfigStatus(void);
void UserInterfaceGetAutoConfigPercentage(BYTE ucAutoPercentage);

bit UserInterfaceSkipAutoVpos(void);
bit UserInterfaceSkipAutoHpos(void);
#endif

#if(_MHL_SUPPORT == _ON)
bit UserInterfaceAdjustMHLMscRCPProc(BYTE ucKeyCode);
#endif

#if(_FREESYNC_SUPPORT == _ON)
bit UserInterfaceGetFREESYNCEnable(void);
#endif

#if(_DP_SUPPORT == _ON)
EnumDpVersionType UserInterfaceGetDPVersion(BYTE ucInputPort);
EnumDpLaneCount UserInterfaceGetDpLaneCount(BYTE ucInputPort);
EnumDPMSTPort UserInterfaceGetDpMSTCapablePort(void);

#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
bit UserInterfaceGetDpCloneOutputStatus(void);
EnumSourceSearchPort UserInterfaceGetDpCloneOutputUserInputPort(void);
#endif

#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
BYTE UserInterfaceGetDpSwitchSelectPort(void);
#endif

#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
bit UserInterfaceGetDpDualDefaultPort(void);
#endif

#endif // End of #if(_DP_SUPPORT == _ON)

//-------------------------------------------------------
// AUDIO
//-------------------------------------------------------
#if(_AUDIO_SUPPORT == _ON)
bit UserInterfaceGetAudioReadyToPlayStatus(void);
bit UserInterfaceGetAudioMuteStatus(void);
EnumAudioInputSource UserInterfaceGetAudioSource(void);
bit UserInterfaceGetAudioNonLPCMStatus(void);
WORD UserInterfaceGetAudioVolume(void);

#if(_EMBEDDED_DAC_SUPPORT == _ON)
EnumAudioDACOutput UserInterfaceGetAudioDACOutput(void);
bit UserInterfaceGetAudioDACKeepDepopState(void);
#endif

#if(_SLEEP_AUDIO_SUPPORT == _ON)
bit UserInterfaceGetAudioStandAloneStatus(void);
#endif

void UserInterfaceAdjustAudioResetProc(void);
void UserInterfaceAdjustAudioPowerProc(EnumPowerStatus enumPowStatus);
void UserInterfaceAdjustAudioAmpMuteProc(bit bMute);
EnumDisplayRegion UserInterfaceGetAudioDisplayModeRegion(void);
EnumRegionIndex UserInterfaceGetAudioRegionIndex(void);

#if((_LINE_IN_SUPPORT == _ON) && (_HW_AUDIO_LINE_IN_TO_DIGITAL_LR_SWAP == _ON))
void UserInterfaceSwapExternalAudioCodecInput(bit bSwap);
#endif
#endif // End of #if(_AUDIO_SUPPORT == _ON)

#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON) || (_UNIFORMITY_SUPPORT == _ON))
void UserInterfaceAdjustBeforeDisplayCalibration(EnumCaliType enumMode);
void UserInterfaceAdjustAfterDisplayCalibration(EnumCaliType enumMode);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : User timer event process
// Input Value  : Event ID
// Output Value : None
//--------------------------------------------------
void UserInterfaceTimerEventProc(EnumScalerTimerEventID enumEventID)
{
    switch(enumEventID)
    {
        case _USER_TIMER_EVENT_KEY_REPEAT_ENABLE:
            SET_KEYREPEATSTART();
            break;

        case _USER_TIMER_EVENT_KEY_SCAN_READY:
            SET_KEYSCANREADY();
            break;

        case _USER_TIMER_EVENT_OSD_DISABLE_OSD_LOGO:
            OsdDispDisableOsd();
            SET_OSD_LOGO_ON(_OFF);

#if(_INSTANT_TIMER_EVENT_0 == _ON)
            ScalerTimer0SetTimerCount(_TIMER_OFF);
#endif

#if(_PANEL_POW_SEQ_FAST_MODE == _ON)
            UserCommonInterfacePanelPowerAction(_BACKLIGHT_OFF);
#else
            UserCommonInterfacePanelPowerAction(_PANEL_OFF);
#endif
            ScalerDDomainBackgroundEnable(_DISPLAY_PATH_ALL, _ENABLE);
            ScalerDDomainPatternGenEnable(_DISABLE);
            break;

        case _USER_TIMER_EVENT_OSD_SHOW_NO_CABLE:
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SHOW_NOCABLE_MSG);
            break;

        case _USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL:
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SHOW_NOSIGNAL_MSG);
            break;

        case _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING:
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SHOW_POWER_SAVING_EVENT_MSG);
            break;

        case _USER_TIMER_EVENT_GO_TO_POWER_SAVING:
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_GO_TO_POWER_SAVING_EVENT_MSG);
            break;

        case _USER_TIMER_EVENT_OSD_DISABLE:
            OsdDispDisableOsd();
            break;

        case _USER_TIMER_EVENT_PANEL_BACKLIGHT_ON:
            SET_PANELPOWERSTATUS(_READY_FOR_BACKLIGHT);
            break;

        case _USER_TIMER_EVENT_PANEL_POWER_OFF:
            SET_PANELPOWERSTATUS(_PANEL_POWER_OFF_STATE);
            break;

#if(_VGA_SUPPORT == _ON)
        case _USER_TIMER_EVENT_DO_AUTO_COLOR:
            CLR_KEY_HOLD();
            OsdDisplayAutoBalanceProc();
            break;
#endif

        case _USER_TIMER_EVENT_PANEL_USED_TIMER:
            RTDFactoryPanelUsedTimer();
            break;

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
        case _USER_TIMER_EVENT_HLWIN_TYPE5_MOVE:
            UserAdjustHLWinType5Move();
            break;
#endif

        case _USER_TIMER_EVENT_OSD_KEYINFO_UNHIGHLIGHT:
            OsdDispMainMenuKeyInfo(_KEY_INFO_ALL, _OSD_UNHIGHLIGHT);
            break;
#if(_DP_SUPPORT == _ON)
        case _USER_TIMER_EVENT_OSD_SHOW_DP_VERSION_SELECT:
            CLR_KEY_HOLD();
            if(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)
            {
                SET_OSD_POWER_SAVING_SHOW_DP_OPTION(_TRUE);
                if((SysPowerGetPowerStatus() == _POWER_STATUS_SAVING) || (SysPowerGetPowerStatus() == _POWER_STATUS_NOSUPPORT_SAVING))
                {
                    SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);
                }
            }
            else
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SHOW_DP_VERSION_MSG);
            }
            break;
#endif
        case _USER_TIMER_EVENT_OSD_DISPLAYMODE_SELECT:
            CLR_KEY_HOLD();
            // Display mode
            if(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)
            {
                SET_OSD_POWER_SAVING_SHOW_DISPLAY_MODE(_TRUE);

                if((SysPowerGetPowerStatus() == _POWER_STATUS_SAVING) || (SysPowerGetPowerStatus() == _POWER_STATUS_NOSUPPORT_SAVING))
                {
                    SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);
                }
            }
            else if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                OsdDispHotKeyDisplayModeMenu();
            }
            break;

#if(_FREESYNC_SUPPORT == _ON)
        case _USER_TIMER_EVENT_OSD_SHOW_FREESYNC_VFREQ:
            if((GET_OSD_STATE() == _MENU_INFORMATION) && (ScalerSyncGetFREESYNCEnable() == _TRUE))
            {
                g_ucFontPointer1 = GET_FREESYNC_OSD_ADDRESS();
                OsdPropPutStringCenter(ROW(14 + 1), COL(11), WIDTH(_OSD_MESSAGE_CENTER_COL_END), _PFONT_PAGE_1, _STRING_NOW_RESOLUTION, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
                // OsdPropPutString(ROW(14 + 1), COL(16), _PFONT_PAGE_1, _STRING_NOW_RESOLUTION, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
                ScalerTimerActiveTimerEvent(SEC(1), _USER_TIMER_EVENT_OSD_SHOW_FREESYNC_VFREQ);
            }
            break;
#endif
#if(_FREEZE_SUPPORT == _ON)
        case _USER_TIMER_EVENT_OSD_DISABLE_FREEZE_MSG:
            OsdFuncDisableOsd();
            if((SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK) && (GET_OSD_STATE() != _MENU_NONE))
            {
                OsdFuncShowOSDAfterClosedFreezeMsg();
#if(_URGENT_EVENT_CHECK_MODE == _OFF)
                SET_FREEZE_DISABLE_MSG_STATE(_OFF);
#endif
            }
            break;
#endif
#if(_FALSE_COLOR_SUPPORT == _ON)
        case _USER_TIMER_EVENT_OSD_DISABLE_FALSE_COLOR_MSG:
            OsdFuncDisableOsd();
            if((SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK) && (GET_OSD_STATE() != _MENU_NONE))
            {
                OsdFuncShowOSDAfterClosedFalseColorMsg();
#if(_URGENT_EVENT_CHECK_MODE == _OFF)
                SET_FALSE_COLOR_DISABLE_MSG_STATE(_OFF);
#endif
            }
            break;
#endif
        default:
            break;
    }
}

#if(_INSTANT_TIMER_EVENT_0 == _ON)
//--------------------------------------------------
// Description  : Action in Timer0 int defined by User
// Input Value  : None
// Output Value : None
//--------------------------------------------------
#pragma save
#pragma OT(8)
void UserInterfaceTimer0InstantAccess_EXINT(void)
{
    if(GET_OSD_LOGO_ON() == _ON)
    {
        if(g_ucLogoTimerCounter != 0xFF)
        {
            g_ucLogoTimerCounter++;
        }

        switch(g_ucLogoTimerCounter)
        {
            case _USER_SHOW_LOGO_STEP:
            case (_USER_SHOW_LOGO_STEP * 2):
            case (_USER_SHOW_LOGO_STEP * 3):
            case (_USER_SHOW_LOGO_STEP * 4):
            case (_USER_SHOW_LOGO_STEP * 5):
            case (_USER_SHOW_LOGO_STEP * 6):
            case (_USER_SHOW_LOGO_STEP * 7):

                ScalerOsdSetTransparency_EXINT(0xFF - (g_ucLogoTimerCounter / _USER_SHOW_LOGO_STEP) * 36);

                break;

            default:

                break;
        }
    }
}
#pragma restore
#endif // End of #if(_INSTANT_TIMER_EVENT_0 == _ON)

#if(_INSTANT_TIMER_EVENT_1 == _ON)
//--------------------------------------------------
// Description  : Action in Timer1 int defined by User
// Input Value  : None
// Output Value : None
//--------------------------------------------------
#pragma save
#pragma OT(8)
void UserInterfaceTimer1InstantAccess_EXINT(void)
{
}
#pragma restore
#endif // End of #if(_INSTANT_TIMER_EVENT_1 == _ON)

#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)
//--------------------------------------------------
// Description  : Action in Timer2 int defined by User
// Input Value  : None
// Output Value : None
//--------------------------------------------------
#pragma save
#pragma OT(8)
void UserInterfaceTimer2InstantAccess_EXINT(void)
{
}
#pragma restore
#endif // End of #if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _ON)

#if 0//#if(_UART_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Action in Serial Port0 int defined by User
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceUartIntHandler_SERIALPORT(void)
{
    if(GET_UART_RECEIVE_STATUS() == _TRUE)
    {
        g_pucUartData[0] = GET_UART_DATA();

        CLR_UART_RECEIVE_STATUS();
    }
}
#endif // End of #if(_UART_SUPPORT == _ON)

#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
//--------------------------------------------------
// Description  : Get DDC-CI Status for Int1
// Input Value  : None
// Output Value : ucValue --> Value of the Input Data Type
//--------------------------------------------------
BYTE UserInterfaceGetDdcciStatus_EXINT1(void) using 2
{
    return GET_OSD_DDCCI_STATUS();
}

//--------------------------------------------------
// Description  : Get Data from DDCCI Buffer defined by user
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE UserInterfaceGetFactoryCommand_EXINT1(void) using 2
{
    return _FALSE;
}

#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
//--------------------------------------------------
// Description  : Get Source Opcode is HDMI freesync
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE UserInterfaceDdcciHDMIFreesyncOpcode_EXINT1(BYTE ucOpcode) using 2
{
    if(ucOpcode == _DDCCI_OPCODE_VCP_HDMI_FREESYNC_SUPPORT)
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}
#endif // #if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))

#endif // End of #if(_DEBUG_MESSAGE_SUPPORT == _OFF)


#if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Set Embedded EDID Data
// Input Value  : Input Port EDID Select
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetEmbeddedEDIDData(EnumInputPortEdid enumInputPort)
{
    switch(enumInputPort)
    {
        case _A0_INPUT_PORT_EDID:
            break;

        case _D0_INPUT_PORT_EDID:

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            if(UserCommonNVRamGetSystemData(_EDID_D0_SELECT) == _DP_EDID_1080P)
            {
                memcpy(MCU_DDCRAM_D0, tEDID_TABLE_DP_1080P, _D0_EMBEDDED_DDCRAM_SIZE);
            }
            else if(UserCommonNVRamGetSystemData(_EDID_D0_SELECT) == _DP_EDID_2560_1440)
            {
                memcpy(MCU_DDCRAM_D0, tEDID_TABLE_DP_2K1K, _D0_EMBEDDED_DDCRAM_SIZE);
            }
            else if(UserCommonNVRamGetSystemData(_EDID_D0_SELECT) == _DP_EDID_4K2K_30HZ)
            {
                memcpy(MCU_DDCRAM_D0, tEDID_TABLE_DP_4K2K_30, _D0_EMBEDDED_DDCRAM_SIZE);
            }
            else if(UserCommonNVRamGetSystemData(_EDID_D0_SELECT) == _DP_EDID_4K2K_60HZ)
            {
                memcpy(MCU_DDCRAM_D0, tEDID_TABLE_DP_4K2K_60, _D0_EMBEDDED_DDCRAM_SIZE);
            }

#elif(_D0_HDMI_SUPPORT == _ON)

            if(UserCommonNVRamGetSystemData(_EDID_D0_SELECT) == _HDMI_EDID_0)
            {
#if((_D0_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 != _EDID_SIZE_NONE) && (_D0_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 != _EDID_NOT_EXIST))
                memcpy(MCU_DDCRAM_D0, tHDMI14_EDID_TABLE_D0, _D0_EMBEDDED_DDCRAM_SIZE);
#endif
            }
            else if(UserCommonNVRamGetSystemData(_EDID_D0_SELECT) == _HDMI_EDID_1)
            {
#if((_D0_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 != _EDID_SIZE_NONE) && (_D0_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 != _EDID_NOT_EXIST))
                memcpy(MCU_DDCRAM_D0, tHDMI20_EDID_TABLE_D0, _D0_EMBEDDED_DDCRAM_SIZE);
#endif
            }
            else if(UserCommonNVRamGetSystemData(_EDID_D0_SELECT) == _HDMI_EDID_2)
            {
#if((_D0_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 != _EDID_SIZE_NONE) && (_D0_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 != _EDID_NOT_EXIST))
                memcpy(MCU_DDCRAM_D0, tHDMI20_HDR_EDID_TABLE_D0, _D0_EMBEDDED_DDCRAM_SIZE);
#endif
            }
#endif
            break;

        case _D1_INPUT_PORT_EDID:

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            if(UserCommonNVRamGetSystemData(_EDID_D1_SELECT) == _DP_EDID_1080P)
            {
                memcpy(MCU_DDCRAM_D1, tEDID_TABLE_DP_1080P, _D1_EMBEDDED_DDCRAM_SIZE);
            }
            else if(UserCommonNVRamGetSystemData(_EDID_D1_SELECT) == _DP_EDID_2560_1440)
            {
                memcpy(MCU_DDCRAM_D1, tEDID_TABLE_DP_2K1K, _D1_EMBEDDED_DDCRAM_SIZE);
            }
            else if(UserCommonNVRamGetSystemData(_EDID_D1_SELECT) == _DP_EDID_4K2K_30HZ)
            {
                memcpy(MCU_DDCRAM_D1, tEDID_TABLE_DP_4K2K_30, _D1_EMBEDDED_DDCRAM_SIZE);
            }
            else if(UserCommonNVRamGetSystemData(_EDID_D1_SELECT) == _DP_EDID_4K2K_60HZ)
            {
                memcpy(MCU_DDCRAM_D1, tEDID_TABLE_DP_4K2K_60, _D1_EMBEDDED_DDCRAM_SIZE);
            }

#elif(_D1_HDMI_SUPPORT == _ON)

            if(UserCommonNVRamGetSystemData(_EDID_D1_SELECT) == _HDMI_EDID_0)
            {
#if((_D1_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 != _EDID_SIZE_NONE) && (_D1_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 != _EDID_NOT_EXIST))
                memcpy(MCU_DDCRAM_D1, tHDMI14_EDID_TABLE_D1, _D1_EMBEDDED_DDCRAM_SIZE);
#endif
            }
            else if(UserCommonNVRamGetSystemData(_EDID_D1_SELECT) == _HDMI_EDID_1)
            {
#if((_D1_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 != _EDID_SIZE_NONE) && (_D1_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 != _EDID_NOT_EXIST))
                memcpy(MCU_DDCRAM_D1, tHDMI20_EDID_TABLE_D1, _D1_EMBEDDED_DDCRAM_SIZE);
#endif
            }
            else if(UserCommonNVRamGetSystemData(_EDID_D1_SELECT) == _HDMI_EDID_2)
            {
#if((_D1_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 != _EDID_SIZE_NONE) && (_D1_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 != _EDID_NOT_EXIST))
                memcpy(MCU_DDCRAM_D1, tHDMI20_HDR_EDID_TABLE_D1, _D1_EMBEDDED_DDCRAM_SIZE);
#endif
            }
#endif
            break;

        case _D2_INPUT_PORT_EDID:

#if(_D2_HDMI_SUPPORT == _ON)

            if(UserCommonNVRamGetSystemData(_EDID_D2_SELECT) == _HDMI_EDID_0)
            {
#if((_D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 != _EDID_SIZE_NONE) && (_D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 != _EDID_NOT_EXIST))
                memcpy(MCU_DDCRAM_D2, tHDMI14_EDID_TABLE_D2, _D2_EMBEDDED_DDCRAM_SIZE);
#endif
            }
            else if(UserCommonNVRamGetSystemData(_EDID_D2_SELECT) == _HDMI_EDID_1)
            {
#if((_D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 != _EDID_SIZE_NONE) && (_D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 != _EDID_NOT_EXIST))
                memcpy(MCU_DDCRAM_D2, tHDMI20_EDID_TABLE_D2, _D2_EMBEDDED_DDCRAM_SIZE);
#endif
            }
            else if(UserCommonNVRamGetSystemData(_EDID_D2_SELECT) == _HDMI_EDID_2)
            {
#if((_D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 != _EDID_SIZE_NONE) && (_D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 != _EDID_NOT_EXIST))
                memcpy(MCU_DDCRAM_D2, tHDMI20_HDR_EDID_TABLE_D2, _D2_EMBEDDED_DDCRAM_SIZE);
#endif
            }
#endif
            break;

        case _D3_INPUT_PORT_EDID:

#if(_D3_HDMI_SUPPORT == _ON)

            if(UserCommonNVRamGetSystemData(_EDID_D3_SELECT) == _HDMI_EDID_0)
            {
#if((_D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 != _EDID_SIZE_NONE) && (_D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 != _EDID_NOT_EXIST))
                memcpy(MCU_DDCRAM_D3, tHDMI14_EDID_TABLE_D3, _D3_EMBEDDED_DDCRAM_SIZE);
#endif
            }
            else if(UserCommonNVRamGetSystemData(_EDID_D3_SELECT) == _HDMI_EDID_1)
            {
#if((_D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 != _EDID_SIZE_NONE) && (_D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 != _EDID_NOT_EXIST))
                memcpy(MCU_DDCRAM_D3, tHDMI20_EDID_TABLE_D3, _D3_EMBEDDED_DDCRAM_SIZE);
#endif
            }
            else if(UserCommonNVRamGetSystemData(_EDID_D3_SELECT) == _HDMI_EDID_2)
            {
#if((_D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 != _EDID_SIZE_NONE) && (_D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 != _EDID_NOT_EXIST))
                memcpy(MCU_DDCRAM_D3, tHDMI20_HDR_EDID_TABLE_D3, _D3_EMBEDDED_DDCRAM_SIZE);
#endif
            }
#endif
            break;

        case _D4_INPUT_PORT_EDID:

#if(_D4_HDMI_SUPPORT == _ON)

            if(UserCommonNVRamGetSystemData(_EDID_D4_SELECT) == _HDMI_EDID_0)
            {
#if((_D4_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 != _EDID_SIZE_NONE) && (_D4_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 != _EDID_NOT_EXIST))
                memcpy(MCU_DDCRAM_D4, tHDMI14_EDID_TABLE_D4, _D4_EMBEDDED_DDCRAM_SIZE);
#endif
            }
            else if(UserCommonNVRamGetSystemData(_EDID_D4_SELECT) == _HDMI_EDID_1)
            {
#if((_D4_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 != _EDID_SIZE_NONE) && (_D4_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 != _EDID_NOT_EXIST))
                memcpy(MCU_DDCRAM_D4, tHDMI20_EDID_TABLE_D4, _D4_EMBEDDED_DDCRAM_SIZE);
#endif
            }
            else if(UserCommonNVRamGetSystemData(_EDID_D4_SELECT) == _HDMI_EDID_2)
            {
#if((_D4_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 != _EDID_SIZE_NONE) && (_D4_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 != _EDID_NOT_EXIST))
                memcpy(MCU_DDCRAM_D4, tHDMI20_HDR_EDID_TABLE_D4, _D4_EMBEDDED_DDCRAM_SIZE);
#endif
            }
#endif
            break;

        case _D5_INPUT_PORT_EDID:

#if(_D5_HDMI_SUPPORT == _ON)

            if(UserCommonNVRamGetSystemData(_EDID_D5_SELECT) == _HDMI_EDID_0)
            {
#if((_D5_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 != _EDID_SIZE_NONE) && (_D5_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 != _EDID_NOT_EXIST))
                memcpy(MCU_DDCRAM_D5, tHDMI14_EDID_TABLE_D5, _D5_EMBEDDED_DDCRAM_SIZE);
#endif
            }
            else if(UserCommonNVRamGetSystemData(_EDID_D5_SELECT) == _HDMI_EDID_1)
            {
#if((_D5_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 != _EDID_SIZE_NONE) && (_D5_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 != _EDID_NOT_EXIST))
                memcpy(MCU_DDCRAM_D5, tHDMI20_EDID_TABLE_D5, _D5_EMBEDDED_DDCRAM_SIZE);
#endif
            }
            else if(UserCommonNVRamGetSystemData(_EDID_D5_SELECT) == _HDMI_EDID_2)
            {
#if((_D5_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 != _EDID_SIZE_NONE) && (_D5_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 != _EDID_NOT_EXIST))
                memcpy(MCU_DDCRAM_D5, tHDMI20_HDR_EDID_TABLE_D5, _D5_EMBEDDED_DDCRAM_SIZE);
#endif
            }
#endif
            break;

        case _D6_INPUT_PORT_EDID:

#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
            if(UserCommonNVRamGetSystemData(_EDID_D6_SELECT) == _DP_EDID_1080P)
            {
                memcpy(MCU_DDCRAM_D6, tEDID_TABLE_DP_1080P, _D6_EMBEDDED_DDCRAM_SIZE);
            }
            else if(UserCommonNVRamGetSystemData(_EDID_D6_SELECT) == _DP_EDID_2560_1440)
            {
                memcpy(MCU_DDCRAM_D6, tEDID_TABLE_DP_2K1K, _D6_EMBEDDED_DDCRAM_SIZE);
            }
            else if(UserCommonNVRamGetSystemData(_EDID_D6_SELECT) == _DP_EDID_4K2K_30HZ)
            {
                memcpy(MCU_DDCRAM_D6, tEDID_TABLE_DP_4K2K_30, _D6_EMBEDDED_DDCRAM_SIZE);
            }
            else if(UserCommonNVRamGetSystemData(_EDID_D6_SELECT) == _DP_EDID_4K2K_60HZ)
            {
                memcpy(MCU_DDCRAM_D6, tEDID_TABLE_DP_4K2K_60, _D6_EMBEDDED_DDCRAM_SIZE);
            }
#endif
            break;

        case _D7_INPUT_PORT_EDID:

#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
            if(UserCommonNVRamGetSystemData(_DUAL_DP_EDID_SELECT) == _DUAL_DP_EDID_5K3K_60HZ)
            {
                memcpy(MCU_DDCRAM_D0, tEDID_TABLE_DP_5K3K_60_D0, _D7_D0_EMBEDDED_DDCRAM_SIZE);
                memcpy(MCU_DDCRAM_D1, tEDID_TABLE_DP_5K3K_60_D1, _D7_D1_EMBEDDED_DDCRAM_SIZE);
            }
            else if(UserCommonNVRamGetSystemData(_DUAL_DP_EDID_SELECT) == _DUAL_DP_EDID_4K2K_144HZ)
            {
                memcpy(MCU_DDCRAM_D0, tEDID_TABLE_DP_4K2K_144_D0, _D7_D0_EMBEDDED_DDCRAM_SIZE);
                memcpy(MCU_DDCRAM_D1, tEDID_TABLE_DP_4K2K_144_D1, _D7_D1_EMBEDDED_DDCRAM_SIZE);
            }
#endif
            break;

        case _D0_INPUT_PORT_MHL_EDID:
            break;

        case _D1_INPUT_PORT_MHL_EDID:
            break;

        case _D2_INPUT_PORT_MHL_EDID:
            break;

        case _D3_INPUT_PORT_MHL_EDID:
            break;

        case _D4_INPUT_PORT_MHL_EDID:
            break;

        case _D5_INPUT_PORT_MHL_EDID:
            break;

        default:
            break;
    }
}
#endif // End of #if((_EMBEDDED_EDID_SUPPORT == _ON) && (_WRITE_EDID_LOCATION_BY_USER_SUPPORT == _ON))

#if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_USER)
//--------------------------------------------------
// Description  : Get HDCP Bksv By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetHDCPKeyBksvByUser(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray)
{
    ucSubAddr = ucSubAddr;
    ucLength = ucLength;
    pucReadArray = pucReadArray;
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetHDCPKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Tx HDCP Aksv By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetTxHDCPKeyAksvByUser(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray)
{
    ucSubAddr = ucSubAddr;
    ucLength = ucLength;
    pucReadArray = pucReadArray;
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetTxHDCPKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}
#endif // End of #if(_DP_TX_SUPPORT == _ON)
#endif // End of #if(_HDCP_1_4_KEY_LOCATION == _TABLE_LOCATION_USER)

#if((_HDCP_2_2_SUPPORT == _ON) && (_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_USER))
//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetHdcp2CertrxByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetHdcp2RSADkeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetHdcp2RSARRModNByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetHdcp2RSAKPrivByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetHdcp2RSANpinvByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}

//--------------------------------------------------
// Description  : Get HDCP By User Defined Method
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetHdcp2LCKeyByUser(WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    usSubAddr = usSubAddr;
    usLength = usLength;
    pucReadArray = pucReadArray;
}
#endif // End of #if((_HDCP_2_2_SUPPORT == _ON) && (_HDCP_2_2_KEY_LOCATION == _TABLE_LOCATION_USER))

//--------------------------------------------------
// Description  : Wait For Panel Power Sequence T1
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustWaitPanelT1(void)
{
    ScalerTimerDelayXms(_PANEL_POWER_ON_T1);
}

//--------------------------------------------------
// Description  : Wait For Panel Power Sequence T2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustWaitPanelT2(void)
{
#if(_PANEL_STYLE == _PANEL_LVDS)

    ScalerTimerDelayXms(_PANEL_POWER_ON_T2);

#elif(_PANEL_STYLE == _PANEL_VBO)

    ScalerDisplayVboPollingHotPlug(_PANEL_POWER_ON_T2);

#elif(_PANEL_STYLE == _PANEL_DPTX)

    ScalerDisplayDPTxPollingHotPlug(_PANEL_POWER_ON_T2);

#endif
}

//--------------------------------------------------
// Description  : Wait For Panel Power Sequence T3
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustWaitPanelT3(void)
{
    ScalerTimerDelayXms(_PANEL_POWER_ON_T3);
}

//--------------------------------------------------
// Description  : Wait For Panel Power Sequence T4
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustWaitPanelT4(void)
{
    ScalerTimerDelayXms(_PANEL_POWER_OFF_T4);
}

//--------------------------------------------------
// Description  : Wait For Panel Power Sequence T5
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustWaitPanelT5(void)
{
    ScalerTimerDelayXms(_PANEL_POWER_OFF_T5);
}


//--------------------------------------------------
// Description  : Uncall Function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceUncallFunction(void)
{
    bit bUncall = _FALSE;

    if(bUncall == _TRUE)
    {
#if(_FLASH_PARTITION_TYPE == _FLASH_PARTITION_USER)
        bUncall = tFLASH_PARTITION_BOOTTABLE[0];
#endif

#if(_OCC_SUPPORT == _OFF)
        OsdFuncChangeIconColor1Bit(ROW(0), _ITEM_0, WIDTH(0), HEIGHT(0), _CP_BLUE);
#endif

        UserInterfaceGetDisplaySettingBacklightAction();
    }
}

//--------------------------------------------------
// Description  : User Power On Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceInitial(void)
{
    // Call Uncalled Function for Compile Warning
    UserInterfaceUncallFunction();

    PCB_PWM_SETTING();
    RTDNVRamStartup();

    ScalerMcuDdcciSwitchPort(GET_OSD_DDCCI_STATUS());
    UserCommonDdcciMapping();
    RTDKeyInitial();
    SET_PANELPOWERSTATUS(_PANEL_POWER_OFF_STATE);

    // Adjust Backlight
    UserAdjustBacklight(GET_OSD_BACKLIGHT());

    // Adjust IR Decode
#if(_IR_SUPPORT == _IR_HW_SUPPORT)
    UserAdjusIR();
#endif

    SET_OSD_DOUBLE_SIZE(_OFF);
    if((_PANEL_DH_WIDTH >= 3840) && (_PANEL_DV_HEIGHT >= 2160))
    {
        SET_OSD_DOUBLE_SIZE(_ON);
    }
}

//--------------------------------------------------
// Description  : User Power Switch
// Input Value  : ucSwitch --> Power Action
// Output Value : None
//--------------------------------------------------
void UserInterfacePowerSwitch(EnumPowerAction enumSwitch)
{
    switch(enumSwitch)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:

            // Update LED Status
            UserInterfaceKeyPadLedControl(_LED_POWER_ON);

            break;

        case _POWER_ACTION_PS_TO_NORMAL:

            break;

        case _POWER_ACTION_OFF_TO_NORMAL:

            // Update LED Status
            UserInterfaceKeyPadLedControl(_LED_POWER_ON);

            // Set Monitor Power On Status
            UserCommonNVRamSetSystemData(_MONITOR_POWER_STATUS, _ON);

            // Save System Power Status Data.
            UserCommonNVRamSaveSystemData();

            break;


        case _POWER_ACTION_AC_ON_TO_OFF:

            // Update LED Status
            UserInterfaceKeyPadLedControl(_LED_POWER_OFF);

            // Panel pown down.
            UserCommonInterfacePanelPowerAction(_PANEL_OFF);

            break;

        case _POWER_ACTION_NORMAL_TO_OFF:

            // Update LED Status
            UserInterfaceKeyPadLedControl(_LED_POWER_OFF);

            // Panel pown down.
            UserCommonInterfacePanelPowerAction(_PANEL_OFF);

            // Set Monitor Power Off Status
            UserCommonNVRamSetSystemData(_MONITOR_POWER_STATUS, _OFF);

            // Save System Power Status Data.
            UserCommonNVRamSaveSystemData();

            break;


        case _POWER_ACTION_PS_TO_OFF:

            // Update LED Status
            UserInterfaceKeyPadLedControl(_LED_POWER_OFF);

            // Set Monitor Power Off Status
            UserCommonNVRamSetSystemData(_MONITOR_POWER_STATUS, _OFF);

            // Save System Power Status Data.
            UserCommonNVRamSaveSystemData();

            break;

        case _POWER_ACTION_NOSUPPORT_PS_TO_OFF:

            // Update LED Status
            UserInterfaceKeyPadLedControl(_LED_POWER_OFF);

            // Set Monitor Power Off Status
            UserCommonNVRamSetSystemData(_MONITOR_POWER_STATUS, _OFF);

            // Save System Power Status Data.
            UserCommonNVRamSaveSystemData();

            break;

        case _POWER_ACTION_NORMAL_TO_PS:
        case _POWER_ACTION_NORMAL_TO_FAKE_PS:

            // Update LED Status
            UserInterfaceKeyPadLedControl(_LED_POWER_SAVING);

            // Panel pown down.
            UserCommonInterfacePanelPowerAction(_PANEL_OFF);

            break;

        case _POWER_ACTION_NOSUPPORT_PS_TO_PS:

            // Update LED Status
            UserInterfaceKeyPadLedControl(_LED_POWER_SAVING);

            break;

        case _POWER_ACTION_NORMAL_TO_NOSUPPORT_PS:

            // Update LED Status
            UserInterfaceKeyPadLedControl(_LED_POWER_NOSUPPORT_SAVING);

            UserCommonInterfaceOsdResetProc();

            // Panel pown down.
            UserCommonInterfacePanelPowerAction(_PANEL_OFF);

            break;

        default:

            break;
    }

#if(_INSTANT_TIMER_EVENT_0 == _ON)
    ScalerTimer0SetTimerCount(_TIMER_OFF);
#endif
}

//--------------------------------------------------
// Description  : Keypad Led Control
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceKeyPadLedControl(BYTE ucKeyPadLed)
{
    switch(ucKeyPadLed)
    {
        case _LED_POWER_ON:
            PCB_LED_ON();
            break;

        case _LED_POWER_ACTIVE:
            PCB_LED_ACTIVE();
            break;

        case _LED_POWER_SEARCH:
            PCB_LED_IDLE();
            break;

        case _LED_POWER_SAVING:
            PCB_LED_POWER_SAVING();
            break;

        case _LED_POWER_NOSUPPORT:
            PCB_LED_ACTIVE();
            break;

        case _LED_POWER_NOSUPPORT_SAVING:
            PCB_LED_POWER_SAVING();
            break;

        case _LED_POWER_OFF:
            PCB_LED_OFF();
            break;

        case _LED_ALL_OFF:
            PCB_LED_OFF();
            break;

        case _LED_TYPE_1:
            PCB_LED_TYPE1();
            break;

        case _LED_TYPE_2:
            PCB_LED_TYPE2();
            break;

        case _LED_TYPE_3:
            PCB_LED_TYPE3();
            break;

        case _LED_TYPE_4:
            PCB_LED_TYPE4();
            break;

        case _LED_TYPE_5:
            PCB_LED_TYPE5();
            break;

        case _LED_TYPE_FLASH:
            PCB_LED_TYPE_FLASH();
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get user defined auto-search target region
// Input Value  : None
// Output Value : select region
//--------------------------------------------------
EnumDisplayRegion UserInterfaceGetAutoSearchTarget(void)
{
    switch(GET_OSD_DISPLAY_MODE())
    {
        default:
        case _OSD_DM_1P:
            if(GET_OSD_1P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
            {
                return _DISPLAY_RGN_1P;
            }
            break;

#if(_PIP_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_2P_PIP:

            if(GET_OSD_1P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
            {
                return _DISPLAY_RGN_MAIN;
            }
            else if(GET_OSD_2P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
            {
                return _DISPLAY_RGN_SUB;
            }

            break;
#endif

#if(_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_2P_LR:

            if(GET_OSD_1P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
            {
                return _DISPLAY_RGN_LEFT;
            }
            else if(GET_OSD_2P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
            {
                return _DISPLAY_RGN_RIGHT;
            }

            break;
#endif

#if(_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_2P_TB:

            if(GET_OSD_1P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
            {
                return _DISPLAY_RGN_TOP;
            }
            else if(GET_OSD_2P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
            {
                return _DISPLAY_RGN_BOTTOM;
            }

            break;
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_4P:

            if(GET_OSD_1P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
            {
                return _DISPLAY_RGN_LT;
            }
            else if(GET_OSD_2P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
            {
                return _DISPLAY_RGN_LB;
            }
            else if(GET_OSD_3P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
            {
                return _DISPLAY_RGN_RT;
            }
            else if(GET_OSD_4P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
            {
                return _DISPLAY_RGN_RB;
            }

            break;
#endif
    }

    return _DISPLAY_RGN_NONE;
}

//--------------------------------------------------
// Description  : Get input port 0
// Input Value  : None
// Output Value : input port
//--------------------------------------------------
EnumSourceSearchPort UserInterfaceGetInputPort0(void)
{
    if(GET_OSD_1P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
    {
        switch(GET_OSD_DISPLAY_MODE())
        {
            default:
            case _OSD_DM_1P:
                return _INPUT_PORT_SEARCH_PRI_0;

#if(_MULTI_DISPLAY_MAX >= 0x02)
            case _OSD_DM_2P_PIP:
            case _OSD_DM_2P_LR:
            case _OSD_DM_2P_TB:
                if(GET_OSD_2P_INPUT_SOURCE() == _INPUT_PORT_SEARCH_PRI_0)
                {
                    return _INPUT_PORT_SEARCH_PRI_1;
                }
                else
                {
                    return _INPUT_PORT_SEARCH_PRI_0;
                }
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
            case _OSD_DM_4P:
                if((GET_OSD_2P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_0) &&
                   (GET_OSD_3P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_0) &&
                   (GET_OSD_4P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_0))
                {
                    return _INPUT_PORT_SEARCH_PRI_0;
                }
                else if((GET_OSD_2P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_1) &&
                        (GET_OSD_3P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_1) &&
                        (GET_OSD_4P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_1))
                {
                    return _INPUT_PORT_SEARCH_PRI_1;
                }
                else if((GET_OSD_2P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_2) &&
                        (GET_OSD_3P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_2) &&
                        (GET_OSD_4P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_2))
                {
                    return _INPUT_PORT_SEARCH_PRI_2;
                }
                else
                {
                    return _INPUT_PORT_SEARCH_PRI_3;
                }
#endif
        }
    }
    else
    {
        return GET_OSD_1P_INPUT_SOURCE();
    }
}

#if(_MULTI_DISPLAY_MAX >= 0x02)
//--------------------------------------------------
// Description  : Get input port 1
// Input Value  : None
// Output Value : input port
//--------------------------------------------------
EnumSourceSearchPort UserInterfaceGetInputPort1(void)
{
    if(GET_OSD_2P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
    {
        switch(GET_OSD_DISPLAY_MODE())
        {
            default:
            case _OSD_DM_1P:
                return _INPUT_PORT_SEARCH_PRI_0;

#if(_MULTI_DISPLAY_MAX >= 0x02)
            case _OSD_DM_2P_PIP:
            case _OSD_DM_2P_LR:
            case _OSD_DM_2P_TB:
                if(GET_OSD_1P_INPUT_SOURCE() == _INPUT_PORT_SEARCH_PRI_0)
                {
                    return _INPUT_PORT_SEARCH_PRI_1;
                }
                else
                {
                    return _INPUT_PORT_SEARCH_PRI_0;
                }
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
            case _OSD_DM_4P:
                if((GET_OSD_1P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_0) &&
                   (GET_OSD_3P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_0) &&
                   (GET_OSD_4P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_0))
                {
                    return _INPUT_PORT_SEARCH_PRI_0;
                }
                else if((GET_OSD_1P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_1) &&
                        (GET_OSD_3P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_1) &&
                        (GET_OSD_4P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_1))
                {
                    return _INPUT_PORT_SEARCH_PRI_1;
                }
                else if((GET_OSD_1P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_2) &&
                        (GET_OSD_3P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_2) &&
                        (GET_OSD_4P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_2))
                {
                    return _INPUT_PORT_SEARCH_PRI_2;
                }
                else
                {
                    return _INPUT_PORT_SEARCH_PRI_3;
                }
#endif
        }
    }
    else
    {
        return GET_OSD_2P_INPUT_SOURCE();
    }
}
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get input port 2
// Input Value  : None
// Output Value : input port
//--------------------------------------------------
EnumSourceSearchPort UserInterfaceGetInputPort2(void)
{
    if(GET_OSD_3P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
    {
        if((GET_OSD_1P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_0) &&
           (GET_OSD_2P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_0) &&
           (GET_OSD_4P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_0))
        {
            return _INPUT_PORT_SEARCH_PRI_0;
        }
        else if((GET_OSD_1P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_1) &&
                (GET_OSD_2P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_1) &&
                (GET_OSD_4P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_1))
        {
            return _INPUT_PORT_SEARCH_PRI_1;
        }
        else if((GET_OSD_1P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_2) &&
                (GET_OSD_2P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_2) &&
                (GET_OSD_4P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_2))
        {
            return _INPUT_PORT_SEARCH_PRI_2;
        }
        else
        {
            return _INPUT_PORT_SEARCH_PRI_3;
        }
    }
    else
    {
        return GET_OSD_3P_INPUT_SOURCE();
    }
}

//--------------------------------------------------
// Description  : Get input port 3
// Input Value  : None
// Output Value : input port
//--------------------------------------------------
EnumSourceSearchPort UserInterfaceGetInputPort3(void)
{
    if(GET_OSD_4P_INPUT_SOURCE() == _OSD_INPUT_AUTO)
    {
        if((GET_OSD_1P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_0) &&
           (GET_OSD_2P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_0) &&
           (GET_OSD_3P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_0))
        {
            return _INPUT_PORT_SEARCH_PRI_0;
        }
        else if((GET_OSD_1P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_1) &&
                (GET_OSD_2P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_1) &&
                (GET_OSD_3P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_1))
        {
            return _INPUT_PORT_SEARCH_PRI_1;
        }
        else if((GET_OSD_1P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_2) &&
                (GET_OSD_2P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_2) &&
                (GET_OSD_3P_INPUT_SOURCE() != _INPUT_PORT_SEARCH_PRI_2))
        {
            return _INPUT_PORT_SEARCH_PRI_2;
        }
        else
        {
            return _INPUT_PORT_SEARCH_PRI_3;
        }
    }
    else
    {
        return GET_OSD_4P_INPUT_SOURCE();
    }
}
#endif

//--------------------------------------------------
// Description  : User OSD Get LogoOn
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserInterfaceGetLogoStatus(void)
{
    return (GET_OSD_LOGO_ON());
}

//--------------------------------------------------
// Description  : Check Whther to support this timing
// Input Value  : None
// Output Value : TRUE => Go to No Support State
//--------------------------------------------------
bit UserInterfaceGetdNoSupportStatus(EnumDisplayRegion enumDisplayRegion)
{
    enumDisplayRegion = enumDisplayRegion;
    // Add User No Support Check
    return _FALSE;
}

//--------------------------------------------------
// Description  : For User to Check Whether to Support Current DCLK
// Input Value  : None
// Output Value : _TRUE => No Support
//--------------------------------------------------
bit UserInterfaceGetDclkNoSupportStatus(void)
{
    if((GET_D_CLK_FREQ() > ((DWORD)_PANEL_PIXEL_CLOCK_MAX_KHZ)) ||
       (GET_D_CLK_FREQ() < ((DWORD)_PANEL_PIXEL_CLOCK_MIN_KHZ)))
    {
        DebugMessageScaler("D Clock Exceed Panel Supported Range", GET_D_CLK_FREQ());
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get whether to by pass normal active process
// Input Value  : None
// Output Value : _TRUE => By pass normal active process
//--------------------------------------------------
bit UserInterfaceGetActiveByPassStatus(EnumDisplayRegion enumDisplayRegion)
{
    if(SysRegionCheckDisplayEvent(enumDisplayRegion, _DISPLAY_EVENT_FIRST_ACTIVE) == _TRUE)
    {
        // Adjust color format & overscan case
        if((SysRegionGetPortType(GET_OSD_SYSTEM_DISPLAY_REGION()) == SysRegionGetPortType(enumDisplayRegion)) &&
           ((GET_OSD_STATE() == _MENU_COLOR_FORMAT) || (GET_OSD_STATE() == _MENU_COLOR_FORMAT_ADJUST)))
        {
            return _FALSE;
        }

        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : User Define Whether Cable Status Should Reset
// Input Value  : None
// Output Value : _TRUE => Reset
//--------------------------------------------------
bit UserInterfaceGetCableResetStatus(EnumDisplayRegion enumDisplayRegion)
{
    switch(enumDisplayRegion)
    {
        case _DISPLAY_RGN_1P:
            if((SysSourceGetCableStatusChange(UserCommonNVRamGetSystemData(_SEARCH_PORT_0)) == _TRUE) &&
               ((!((SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK) && (SysRegionGetDisplayState(enumDisplayRegion) == _DISPLAY_STATE_NONE))) ||
                (SysSourceGetCableDetect(UserCommonNVRamGetSystemData(_SEARCH_PORT_0)) == _TRUE)))
            {
                SET_FORCE_POW_SAV_STATUS(_FALSE);

                if(SysSourceGetScanType() != _SOURCE_SWITCH_FIXED_PORT)
                {
                    SysSourceSwitchInputPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0));
                }

                return _TRUE;
            }
            break;

        default:
            if(SysSourceGetCableStatusChange(SysRegionGetPortType(enumDisplayRegion)) == _TRUE)
            {
                SET_FORCE_POW_SAV_STATUS(_FALSE);

                SysSourceSwitchInputPort(SysRegionGetPortType(enumDisplayRegion));
                return _TRUE;
            }
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get Forced Power Saving Status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserInterfaceGetForcePSStatus(void)
{
    return (GET_FORCE_POW_SAV_STATUS());
}

//--------------------------------------------------
// Description  : User Check Into Power Saving
// Input Value  : None
// Output Value : True --> User Check Ready to Power Saving
//--------------------------------------------------
bit UserInterfaceGetIntoPSStatus(void)
{
    if(ScalerOsdGetOsdEnable() == _TRUE)
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Check Whther ADC Data is Reasonable
// Input Value  : LOAD or SAVE
// Output Value : _TRUE => Reasonable
//--------------------------------------------------
bit UserInterfaceGetNVRamDataStatus(EnumNvramCheckType enumNvramCheckType)
{
    switch(enumNvramCheckType)
    {
#if(_VGA_SUPPORT == _ON)
        case _CHECK_ADC_LOAD:

            if(g_stAdcData.ucAdcPGA >= 0xF0)
            {
                // Assign Prefered Value
                g_stAdcData.ucAdcPGA = 8;
            }

            break;

        case _CHECK_ADC_SAVE:

            if(g_stAdcData.ucAdcPGA >= 0xF0)
            {
                return _FAIL;
            }
            break;
#endif

        case _CHECK_SYSTEM_DATA_LOAD:
        case _CHECK_SYSTEM_DATA_SAVE:
        case _CHECK_MODE_USER_DATA_LOAD:
        case _CHECK_MODE_USER_DATA_SAVE:

            break;

        default:
            break;
    }

    return _SUCCESS;
}

#if(_MULTI_DISPLAY_MAX != 0x01)
//--------------------------------------------------
// Description  : Check whether a specific port can be auto-searched or not
// Input Value  : enumSelRegion --> select region
//                enumSourceSearchPort  --> search port
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit UserInterfaceGetRegionAutoSearchStatus(EnumDisplayRegion enumDisplayRegion, EnumSourceSearchPort enumSourceSearchPort)
{
    switch(GET_OSD_DISPLAY_MODE())
    {
        case _OSD_DM_1P:
            break;

        case _OSD_DM_4P:

            switch(enumDisplayRegion)
            {
                case _DISPLAY_RGN_LT:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                    if((enumSourceSearchPort == _D0_INPUT_PORT) || (enumSourceSearchPort == _D6_INPUT_PORT))
                    {
                        return (((GET_OSD_2P_INPUT_SOURCE() != _D0_INPUT_PORT) && (GET_OSD_2P_INPUT_SOURCE() != _D6_INPUT_PORT)) &&
                                ((GET_OSD_3P_INPUT_SOURCE() != _D0_INPUT_PORT) && (GET_OSD_3P_INPUT_SOURCE() != _D6_INPUT_PORT)) &&
                                ((GET_OSD_4P_INPUT_SOURCE() != _D0_INPUT_PORT) && (GET_OSD_4P_INPUT_SOURCE() != _D6_INPUT_PORT)));
                    }
#endif
                    return ((GET_OSD_2P_INPUT_SOURCE() != enumSourceSearchPort) &&
                            (GET_OSD_3P_INPUT_SOURCE() != enumSourceSearchPort) &&
                            (GET_OSD_4P_INPUT_SOURCE() != enumSourceSearchPort));

                case _DISPLAY_RGN_LB:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                    if((enumSourceSearchPort == _D0_INPUT_PORT) || (enumSourceSearchPort == _D6_INPUT_PORT))
                    {
                        return (((GET_OSD_1P_INPUT_SOURCE() != _D0_INPUT_PORT) && (GET_OSD_1P_INPUT_SOURCE() != _D6_INPUT_PORT)) &&
                                ((GET_OSD_3P_INPUT_SOURCE() != _D0_INPUT_PORT) && (GET_OSD_3P_INPUT_SOURCE() != _D6_INPUT_PORT)) &&
                                ((GET_OSD_4P_INPUT_SOURCE() != _D0_INPUT_PORT) && (GET_OSD_4P_INPUT_SOURCE() != _D6_INPUT_PORT)));
                    }
#endif
                    return ((GET_OSD_1P_INPUT_SOURCE() != enumSourceSearchPort) &&
                            (GET_OSD_3P_INPUT_SOURCE() != enumSourceSearchPort) &&
                            (GET_OSD_4P_INPUT_SOURCE() != enumSourceSearchPort));

                case _DISPLAY_RGN_RT:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                    if((enumSourceSearchPort == _D0_INPUT_PORT) || (enumSourceSearchPort == _D6_INPUT_PORT))
                    {
                        return (((GET_OSD_1P_INPUT_SOURCE() != _D0_INPUT_PORT) && (GET_OSD_1P_INPUT_SOURCE() != _D6_INPUT_PORT)) &&
                                ((GET_OSD_2P_INPUT_SOURCE() != _D0_INPUT_PORT) && (GET_OSD_2P_INPUT_SOURCE() != _D6_INPUT_PORT)) &&
                                ((GET_OSD_4P_INPUT_SOURCE() != _D0_INPUT_PORT) && (GET_OSD_4P_INPUT_SOURCE() != _D6_INPUT_PORT)));
                    }
#endif
                    return ((GET_OSD_1P_INPUT_SOURCE() != enumSourceSearchPort) &&
                            (GET_OSD_2P_INPUT_SOURCE() != enumSourceSearchPort) &&
                            (GET_OSD_4P_INPUT_SOURCE() != enumSourceSearchPort));

                case _DISPLAY_RGN_RB:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                    if((enumSourceSearchPort == _D0_INPUT_PORT) || (enumSourceSearchPort == _D6_INPUT_PORT))
                    {
                        return (((GET_OSD_1P_INPUT_SOURCE() != _D0_INPUT_PORT) && (GET_OSD_1P_INPUT_SOURCE() != _D6_INPUT_PORT)) &&
                                ((GET_OSD_2P_INPUT_SOURCE() != _D0_INPUT_PORT) && (GET_OSD_2P_INPUT_SOURCE() != _D6_INPUT_PORT)) &&
                                ((GET_OSD_3P_INPUT_SOURCE() != _D0_INPUT_PORT) && (GET_OSD_3P_INPUT_SOURCE() != _D6_INPUT_PORT)));
                    }
#endif
                    return ((GET_OSD_1P_INPUT_SOURCE() != enumSourceSearchPort) &&
                            (GET_OSD_2P_INPUT_SOURCE() != enumSourceSearchPort) &&
                            (GET_OSD_3P_INPUT_SOURCE() != enumSourceSearchPort));

                default:
                    break;
            }

            break;

        default:
            switch(enumDisplayRegion)
            {
                case _DISPLAY_RGN_MAIN:
                case _DISPLAY_RGN_LEFT:
                case _DISPLAY_RGN_TOP:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                    if((enumSourceSearchPort == _D0_INPUT_PORT) || (enumSourceSearchPort == _D6_INPUT_PORT))
                    {
                        return ((GET_OSD_2P_INPUT_SOURCE() != _D0_INPUT_PORT) && (GET_OSD_2P_INPUT_SOURCE() != _D6_INPUT_PORT));
                    }
#endif
                    return (GET_OSD_2P_INPUT_SOURCE() != enumSourceSearchPort);

                default:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                    if((enumSourceSearchPort == _D0_INPUT_PORT) || (enumSourceSearchPort == _D6_INPUT_PORT))
                    {
                        return ((GET_OSD_1P_INPUT_SOURCE() != _D0_INPUT_PORT) && (GET_OSD_1P_INPUT_SOURCE() != _D6_INPUT_PORT));
                    }
#endif
                    return (GET_OSD_1P_INPUT_SOURCE() != enumSourceSearchPort);
            }

            break;
    }

    return _FALSE;
}
#endif

//--------------------------------------------------
// Description  : Get backlight staus when performing display setting
// Input Value  : None
// Output Value : _ENABLE or _DISABLE
//--------------------------------------------------
bit UserInterfaceGetDisplaySettingBacklightAction(void)
{
#if((_PANEL_STYLE == _PANEL_DPTX) ||\
    (_PANEL_STYLE == _PANEL_VBO))

    return _DISABLE;

#else

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    if((GET_ROT_TYPE() != UserInterfaceGetRotationDegree()) ||
       (GET_ROT_DISP_SIZE() != UserInterfaceGetRotationDisplayType()))
    {
        return _DISABLE;
    }
#endif

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    if(GET_ROT_TYPE() != _ROT_DISABLE)
#endif
    {
        if(GET_DISP_LATENCY_RATIO() != UserInterfaceGetDisplayLatencyRatio())
        {
            return _DISABLE;
        }
    }
#endif

    return _ENABLE;

#endif
}

//--------------------------------------------------
// Description  : Get OSD Color Format
// Input Value  : display Region
// Output Value : Color Format
//--------------------------------------------------
EnumColorSpace UserInterfaceGetColorFormat(EnumDisplayRegion enumDisplayRegion)
{
    return GET_OSD_COLOR_FORMAT(SysRegionGetPortType(enumDisplayRegion));
}

//--------------------------------------------------
// Description  : Get OSD display mode
// Input Value  : None
// Output Value : system display mode
//--------------------------------------------------
EnumDisplayMode UserInterfaceGetMultiDisplayMode(void)
{
    switch(GET_OSD_DISPLAY_MODE())
    {
        default:
        case _OSD_DM_1P:
            return _DISPLAY_MODE_1P;

#if(_PIP_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_2P_PIP:
            return _DISPLAY_MODE_PIP;
#endif

#if(_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_2P_LR:
            return _DISPLAY_MODE_PBP_LR;
#endif

#if(_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_2P_TB:
            return _DISPLAY_MODE_PBP_TB;
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_4P:
            return _DISPLAY_MODE_4P;
#endif
    }
}

#if(_OVERSCAN_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Modify Timing For Overscan
// Input Value  : Current Input Timing
// Output Value : Modified Input Timing
//--------------------------------------------------
bit UserInterfaceGetOverScanStatus(EnumDisplayRegion enumDisplayRegion)
{
    bit bDoOverScan = _FALSE;
    BYTE ucTemp = 0;
    WORD code tusOverscanEnTable[][3] =
    {
        // VFreq, HWidth, VHeight,
        {600,  640,  480},    // 480p
        {600,  720,  480},    // 480p
        {600,  960,  480},    // 480p
        {600, 1440,  480},    // 480p

        {500,  720,  576},    // 576p
        {500,  768,  576},    // 576p
        {500,  960,  576},    // 576p
        {500, 1280,  576},    // 576p
        {500, 1440,  576},    // 576p
        {500, 1280,  720},    // 720p
        {600, 1280,  720},    // 720p
        {500, 1920,  1080},   // 1080p
        {600, 1920,  1080},   // 1080p

        // Don't delete it, and place it at last.
        {  0,    0,    0},
    };

    if(GET_OSD_OVERSCAN_STATUS(SysRegionGetPortType(enumDisplayRegion)) == _OFF)
    {
        return _FALSE;
    }

    SysRegionSetMeasureResultPointerRegion(enumDisplayRegion);

    // Decide whether to do over scan
    switch(SysRegionGetSourceType(enumDisplayRegion))
    {
#if(_OVERSCAN_VGA_SUPPORT == _ON)
        case _SOURCE_VGA:

            // Interlaced and YUV Timing Always do overscan
            if(GET_INPUT_TIMING_INTERLACE_FLG() == _TRUE)
            {
                bDoOverScan = _TRUE;
                break;
            }

            if(GET_VGA_COLOR_FORMAT_STATUS() == _COLOR_SPACE_RGB)
            {
                break;
            }

            while(tusOverscanEnTable[ucTemp][0] != 0)
            {
                if((abs(GET_INPUT_TIMING_VFREQ() - tusOverscanEnTable[ucTemp][0]) < 10) &&
                   (abs(GET_INPUT_TIMING_HWIDTH() - tusOverscanEnTable[ucTemp][1]) < 2) &&
                   (GET_INPUT_TIMING_VHEIGHT() == tusOverscanEnTable[ucTemp][2]))
                {
                    bDoOverScan = _TRUE;
                    break;
                }

                ucTemp++;
            }

            break;
#endif // End of #if(_OVERSCAN_VGA_SUPPORT == _ON)

#if(_OVERSCAN_DVI_SUPPORT != _ON)
        case _SOURCE_DVI:
            break;
#endif

#if(_OVERSCAN_HDMI_SUPPORT != _ON)
        case _SOURCE_HDMI:
            break;
#endif

#if(_OVERSCAN_DP_SUPPORT != _ON)
        case _SOURCE_DP:
            break;
#endif

        default:
#if((_OVERSCAN_DVI_SUPPORT == _ON) || (_OVERSCAN_HDMI_SUPPORT == _ON) || (_OVERSCAN_DP_SUPPORT == _ON))
            // Interlaced and YUV Timing Always do overscan
            if(GET_INPUT_TIMING_INTERLACE_FLG() == _TRUE)
            {
                bDoOverScan = _TRUE;
                break;
            }

            if((ScalerColorGetColorSpaceRGB(ScalerColorGetColorSpace(SysRegionGetPortType(enumDisplayRegion))) == _TRUE))
            {
                break;
            }

            while(tusOverscanEnTable[ucTemp][0] != 0)
            {
                if((abs(GET_INPUT_TIMING_VFREQ() - tusOverscanEnTable[ucTemp][0]) < 10) &&
                   (abs(GET_INPUT_TIMING_HWIDTH() - tusOverscanEnTable[ucTemp][1]) < 2) &&
                   (GET_INPUT_TIMING_VHEIGHT() == tusOverscanEnTable[ucTemp][2]))
                {
                    bDoOverScan = _TRUE;
                    break;
                }

                ucTemp++;
            }
#endif // End of #if((_OVERSCAN_DVI_SUPPORT == _ON) || (_OVERSCAN_HDMI_SUPPORT == _ON) || (_OVERSCAN_DP_SUPPORT == _ON))

            break;
    }

    return bDoOverScan;
}
#endif // End of #if(_OVERSCAN_SUPPORT == _ON)

#if(_ASPECT_RATIO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Modify Timing For Aspect Ratio
// Input Value  : enumSelRegion --> select region
// Output Value : aspect ration type
//--------------------------------------------------
EnumAspectRatioType UserInterfaceGetAspectRatioType(EnumDisplayRegion enumDisplayRegion)
{
    switch(GET_OSD_ASPECT_RATIO_TYPE(SysRegionGetPortType(enumDisplayRegion)))
    {
        case _OSD_ASPECT_RATIO_16_BY_9:
        case _OSD_ASPECT_RATIO_4_BY_3:
        case _OSD_ASPECT_RATIO_5_BY_4:

            return _ASPECT_RATIO_FIXED;

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
        case _OSD_ASPECT_RATIO_ORIGIN:

            return _ASPECT_RATIO_ORIGIN;
#endif

        default:
        case _OSD_ASPECT_RATIO_FULL:

            return _ASPECT_RATIO_FULL;
    }
}

//--------------------------------------------------
// Description  : Get user H/V aspect ratio values
// Input Value  : enumSelRegion --> select region
//                usHRatio, usVRatio --> aspect ratio
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetAspectRatio(EnumDisplayRegion enumDisplayRegion, WORD *pusHRatio, WORD *pusVRatio)
{
    switch(GET_OSD_ASPECT_RATIO_TYPE(SysRegionGetPortType(enumDisplayRegion)))
    {
        default:
            break;

        case _OSD_ASPECT_RATIO_16_BY_9:
            *pusHRatio = 16;
            *pusVRatio = 9;
            break;

        case _OSD_ASPECT_RATIO_4_BY_3:
            *pusHRatio = 4;
            *pusVRatio = 3;
            break;

        case _OSD_ASPECT_RATIO_5_BY_4:
            *pusHRatio = 5;
            *pusVRatio = 4;
            break;
    }
}

//--------------------------------------------------
// Description  : User defined aspect ratio process
// Input Value  : select region
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustAspectRatio(EnumDisplayRegion enumDisplayRegion)
{
    enumDisplayRegion = enumDisplayRegion;
}

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get aspect original mode ratio
// Input Value  : select region
// Output Value : Retion display ratio in aspect ratio original mode (0x00 ~ 0xFF)
//--------------------------------------------------
BYTE UserInterfaceGetAspectRatioOriginalRatio(EnumDisplayRegion enumDisplayRegion)
{
    enumDisplayRegion = enumDisplayRegion;
    return 0xFF;
}
#endif
#endif // End of #if(_ASPECT_RATIO_SUPPORT == _ON)

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get current rotation degree
// Input Value  : None
// Output Value : rotation degree
//--------------------------------------------------
EnumRotationType UserInterfaceGetRotationDegree(void)
{
    switch(GET_OSD_DISP_ROTATE())
    {
        default:
        case _DISP_ROTATE_0:
            return _ROT_DISABLE;

#if (_DISPLAY_ROTATION_90_SUPPORT == _ON)
        case _DISP_ROTATE_90:
            return _ROT_CW90;
#endif
#if (_DISPLAY_ROTATION_180_SUPPORT == _ON)
        case _DISP_ROTATE_180:
            return _ROT_CW180;
#endif
#if (_DISPLAY_ROTATION_270_SUPPORT == _ON)
        case _DISP_ROTATE_270:
            return _ROT_CW270;
#endif
#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
        case _DISP_ROTATE_HOR_MIRROR:
            return _ROT_HOR_MIRROR;
#endif
#if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
        case _DISP_ROTATE_VER_MIRROR:
            return _ROT_VER_MIRROR;
#endif
    }
}

//--------------------------------------------------
// Description  : Get current rotation type
// Input Value  : None
// Output Value : rotation type
//--------------------------------------------------
EnumRotationDisplayType UserInterfaceGetRotationDisplayType(void)
{
    switch(GET_OSD_DISP_ROTATION_SIZE_TYPE())
    {
        default:
        case _OSD_ROTATE_DISPLAY_FULL:
            return _ROT_FULL;

        case _OSD_ROTATE_DISPLAY_PIXEL_BY_PIXEL:
            return _ROT_PIXEL_BY_PIXEL;

        case _OSD_ROTATE_DISPLAY_KEEP_SRC_ASPECT_RATIO:
            return _ROT_KEEP_SRC_ASPECT_RATIO;
    }
}
#endif

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Display Latency Ratio
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE UserInterfaceGetDisplayLatencyRatio(void)
{
    switch(GET_OSD_LATENCY())
    {
        default:
        case _LATENCY_L:
            return 0;   // 0%

        case _LATENCY_M:
            return 50;  // 50%

        case _LATENCY_H:
            return 100; // 100%
    }
}

//--------------------------------------------------
// Description  : Adjust Max/Min Freq according to latency
// Input Value  : None
// Output Value : max/min freq
//--------------------------------------------------
void UserInterfaceGetDVMaxMinFreq(StructDVCustomizedFreq *pstDVCustomizedFreq)
{
    switch (GET_OSD_LATENCY())
    {
        default:
        case _LATENCY_H:
        case _LATENCY_M:
        case _LATENCY_L:
            pstDVCustomizedFreq->usMaxFreq = _PANEL_MAX_FRAME_RATE;
            pstDVCustomizedFreq->usTypFreq = _PANEL_TYP_FRAME_RATE;
            pstDVCustomizedFreq->usMinFreq = _PANEL_MIN_FRAME_RATE;
            break;
    }
}

#endif

#if(_OD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get OD enable status
// Input Value  : None
// Output Value : function enable status
//--------------------------------------------------
EnumFunctionOnOFF UserInterfaceGetODEnableStatus(void)
{
    return GET_OSD_OD_STATUS();
}
#endif

#if((_MEMORY_TYPE_CONFIG == _MEMORY_DDR3) && (_DDR3_MULTIPHASE_EXIST == _ON))
//--------------------------------------------------
// Description  : Get DDR3 Phase From GPIO or DDCCI command
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceUpdateDDR3PhaseData(void)
{
    StructDDR3PhaseInfo stUserVedorDdr3PhaseData = {_DDR3_PLL_INITIAL_PHASE_0, _DDR3_PLL_INITIAL_PHASE_1, _DDR3_READ_DQ_DLYN_TAP};
    ScalerPLLGetDDR3PhaseData(&stUserVedorDdr3PhaseData);
}
#endif



//--------------------------------------------------
// Description  : Modify Input Timing Based on User Requirement
// Input Value  : Current Input Timing Info
// Output Value : Modified Input Timing
//--------------------------------------------------
void UserInterfaceAdjustInputTiming(EnumDisplayRegion enumDisplayRegion)
{
    enumDisplayRegion = enumDisplayRegion;
}

//--------------------------------------------------
// Description  : Modify Display Timing Based on User Requirement
// Input Value  : Current Display Timing Info
// Output Value : Modified Display Timing
//--------------------------------------------------
void UserInterfaceAdjustDisplayTiming(EnumDisplayRegion enumDisplayRegion)
{
    enumDisplayRegion = enumDisplayRegion;

#if(_PANEL_STYLE == _PANEL_LVDS)
    // Check display format resolution according to LVDS port count
    SET_MDOMAIN_OUTPUT_HSTART(GET_MDOMAIN_OUTPUT_HSTART() + (GET_MDOMAIN_OUTPUT_HSTART() % ((BYTE)1 << _LVDS_OUTPUT_PORT)));
    SET_MDOMAIN_OUTPUT_HWIDTH(GET_MDOMAIN_OUTPUT_HWIDTH() - (GET_MDOMAIN_OUTPUT_HWIDTH() % ((BYTE)1 << _LVDS_OUTPUT_PORT)));
    SET_MDOMAIN_OUTPUT_HBSTART(GET_MDOMAIN_OUTPUT_HBSTART() + (GET_MDOMAIN_OUTPUT_HBSTART() % ((BYTE)1 << _LVDS_OUTPUT_PORT)));
    SET_MDOMAIN_OUTPUT_HBWIDTH(GET_MDOMAIN_OUTPUT_HBWIDTH() - (GET_MDOMAIN_OUTPUT_HBWIDTH() % ((BYTE)1 << _LVDS_OUTPUT_PORT)));
#endif
}

#if(_PIP_DISPLAY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get PIP sub timing format
// Input Value  : None
// Output Value : timing format
//--------------------------------------------------
StructTimingFormat UserInterfaceGetPipSubTimingFormat(void)
{
    StructTimingFormat stTimingFormat;
    memset(&stTimingFormat, 0, sizeof(StructTimingFormat));

    // Min resolution: default 640x480
    // Min resolution: 1/4 screen size
    if((_PANEL_DH_WIDTH * 100 / _OSD_PIP_SIZE_MIN_H_SIZE) < (_PANEL_DV_HEIGHT * 100 / _OSD_PIP_SIZE_MIN_V_SIZE))
    {
        // H limited
        stTimingFormat.usHWidth = _OSD_PIP_SIZE_MIN_H_SIZE;
        stTimingFormat.usVHeight = (((DWORD)_PANEL_DV_HEIGHT * _OSD_PIP_SIZE_MIN_H_SIZE * 2 / _PANEL_DH_WIDTH) + 1) / 2;
    }
    else
    {
        // V limited
        stTimingFormat.usHWidth = (WORD)(((DWORD)_PANEL_DH_WIDTH * _OSD_PIP_SIZE_MIN_V_SIZE / _PANEL_DV_HEIGHT) + 3) & 0xFFFC; // with factors of 4
        stTimingFormat.usVHeight = _OSD_PIP_SIZE_MIN_V_SIZE;
    }

    stTimingFormat.usHWidth = stTimingFormat.usHWidth + (((_PANEL_DH_WIDTH / 2 - stTimingFormat.usHWidth) / 4) * GET_OSD_PIP_SIZE() / _OSD_PIP_SIZE_MAX) * 4;
    stTimingFormat.usVHeight = stTimingFormat.usVHeight + (_PANEL_DV_HEIGHT / 2 - stTimingFormat.usVHeight) * GET_OSD_PIP_SIZE() / _OSD_PIP_SIZE_MAX;

    // PIP H/V width, height must be even
    stTimingFormat.usHWidth &= 0xFFFE;
    stTimingFormat.usVHeight &= 0xFFFE;

    switch(GET_OSD_PIP_POSITION_TYPE())
    {
        case _PIP_POSITON_LT:
            stTimingFormat.usHStart = _PANEL_DH_START;
            stTimingFormat.usVStart = _PANEL_DV_START;
            break;

        case _PIP_POSITON_RT:
            stTimingFormat.usHStart = (_PANEL_DH_START + _PANEL_DH_WIDTH - stTimingFormat.usHWidth);
            stTimingFormat.usVStart = (_PANEL_DV_START);
            break;

        case _PIP_POSITON_LB:
            stTimingFormat.usHStart = (_PANEL_DH_START);
            stTimingFormat.usVStart = (_PANEL_DV_START + _PANEL_DV_HEIGHT - stTimingFormat.usVHeight);

            break;

        default:
        case _PIP_POSITON_RB:
            stTimingFormat.usHStart = (_PANEL_DH_START + _PANEL_DH_WIDTH - stTimingFormat.usHWidth);
            stTimingFormat.usVStart = (_PANEL_DV_START + _PANEL_DV_HEIGHT - stTimingFormat.usVHeight);

            break;

        case _PIP_POSITON_MIDDLE:
            stTimingFormat.usHStart = (_PANEL_DH_START + (_PANEL_DH_WIDTH / 2) - (stTimingFormat.usHWidth / 2));
            stTimingFormat.usVStart = (_PANEL_DV_START + (_PANEL_DV_HEIGHT / 2) - (stTimingFormat.usVHeight / 2));

            break;

        case _PIP_POSITON_USER:
            stTimingFormat.usHStart = (_PANEL_DH_START + ((DWORD)_PANEL_DH_WIDTH - stTimingFormat.usHWidth) * GET_OSD_PIP_USER_POSITION_H() / _OSD_PIP_USER_POSITION_H_MAX);
            stTimingFormat.usVStart = (_PANEL_DV_START + ((DWORD)_PANEL_DV_HEIGHT - stTimingFormat.usVHeight) * GET_OSD_PIP_USER_POSITION_V() / _OSD_PIP_USER_POSITION_V_MAX);

            break;
    }

    // PIP H/V start must be even
    stTimingFormat.usHStart &= 0xFFFE;
    stTimingFormat.usVStart &= 0xFFFE;

    return stTimingFormat;
}
#endif

#if((_PBP_LR_DISPLAY_SUPPORT == _ON) && (_D_DOMAIN_PATH != _D_DOMAIN_4_PATH))
//--------------------------------------------------
// Description  : Get PBP LR timing format
// Input Value  : enumSelRegion --> L or R
// Output Value : timing format
//--------------------------------------------------
StructTimingFormat UserInterfaceGetPbpTimingFormat(EnumDisplayRegion enumDisplayRegion)
{
    StructTimingFormat stTimingFormat;
    WORD usStep = 0;
    WORD usMaxLeftSize = 0;

    if(_PANEL_DH_WIDTH > (_PANEL_DV_HEIGHT / 9 * 16))
    {
        usMaxLeftSize = (_PANEL_DV_HEIGHT / 9 * 16);
    }
    else if(_PANEL_DH_WIDTH > (_PANEL_DV_HEIGHT / 3 * 4))
    {
        usMaxLeftSize = (_PANEL_DV_HEIGHT / 3 * 4);
    }
    else if(_PANEL_DH_WIDTH > (_PANEL_DV_HEIGHT / 4 * 5))
    {
        usMaxLeftSize = (_PANEL_DV_HEIGHT / 4 * 5);
    }
    else
    {
        usMaxLeftSize = (_PANEL_DH_WIDTH / 4 * 3);
    }

    // Check R size minimum = 640
    if((_PANEL_DH_WIDTH - usMaxLeftSize) < 640)
    {
        usMaxLeftSize = (_PANEL_DH_WIDTH - 640);
    }

    usStep = ((DWORD)usMaxLeftSize - (_PANEL_DH_WIDTH / 2)) * GET_OSD_PBP_LR_RATIO() / _OSD_PBP_LR_RATIO_MAX;
    usStep = usStep & 0xFFFC;

    // Set V timing format
    stTimingFormat.usVStart = _PANEL_DV_START;
    stTimingFormat.usVHeight = _PANEL_DV_HEIGHT;

    // Set H timing format
    if(enumDisplayRegion == _DISPLAY_RGN_LEFT)
    {
        stTimingFormat.usHStart = _PANEL_DH_START;
        stTimingFormat.usHWidth = ((_PANEL_DH_WIDTH / 2) + usStep);
    }
    else
    {
        stTimingFormat.usHStart = _PANEL_DH_START + (_PANEL_DH_WIDTH / 2) + usStep;
        stTimingFormat.usHWidth = ((_PANEL_DH_WIDTH / 2) - usStep);
    }

    return stTimingFormat;
}
#endif

#if(_RGB_QUANTIZATION_RANGE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Judge if Quantization Range is Full or Limited
// Input Value  : EnumDisplayRegion --> display region
//                ucQuanRange --> quantization status
// Output Value : True or False
//--------------------------------------------------
bit UserInterfaceGetRGBQuantizationLimitRangeStatus(EnumDisplayRegion enumDisplayRegion, EnumColorRGBQuantization enumColorRGBQuantization)
{
    enumDisplayRegion = enumDisplayRegion;

    switch(enumColorRGBQuantization)
    {
    // alant - modify full /limit range
        case _RGB_QUANTIZATION_FULL_RANGE:
      //  case _RGB_QUANTIZATION_DEFAULT_RANGE:
        case _RGB_QUANTIZATION_RESERVED:
        default:

            return _FALSE;

       case _RGB_QUANTIZATION_DEFAULT_RANGE:
        case _RGB_QUANTIZATION_LIMIT_RANGE:

            return _TRUE;
    }
    return _FALSE;
}
#endif

#if(_YCC_QUANTIZATION_RANGE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Judge if YCC Quantization Range is Full or Limited
// Input Value  : EnumDisplayRegion --> display region
//                bQuanRange --> quantization status
// Output Value : True or False
//--------------------------------------------------
bit UserInterfaceGetYCCQuantizationFullRangeStatus(EnumDisplayRegion enumDisplayRegion, EnumColorYCCQuantization enumColorYCCQuantization)
{
    enumDisplayRegion = enumDisplayRegion;

    return (enumColorYCCQuantization == _YCC_QUANTIZATION_FULL_RANGE);
}
#endif

//--------------------------------------------------
// Description  : Color process in display initial
// Input Value  : System display mode
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustInitialColorProc(EnumDisplayMode enumDisplayMode)
{
#if(_SIX_COLOR_SUPPORT == _ON)
    BYTE ucIndex = 0;
#endif

    EnumSelRegion enumSelRegion = GET_OSD_SYSTEM_SELECT_REGION();
    EnumSelRegion enumSelRegionInverse = ScalerRegionGetInverse(enumSelRegion);

    enumDisplayMode = enumDisplayMode;

#if(_BORDER_WINDOW_SUPPORT == _ON)
    // Draw border
    UserInterfaceAdjustBorderWindow(_DB_APPLY_NONE);
#endif

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
    UserInterfaceAdjustHighlightWindow(_DB_APPLY_NO_POLLING);
#endif

    // Adjuset Brightness & Contrast
#if(_BRIGHTNESS_SUPPORT == _ON)
    UserAdjustBrightness(enumSelRegion, GET_OSD_BRIGHTNESS(GET_OSD_SELECT_REGION()));
    UserAdjustBrightness(enumSelRegionInverse, GET_OSD_BRIGHTNESS(GET_OSD_INVERSE_REGION()));
#endif

    RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());

#if(_CONTRAST_SUPPORT == _ON)
    UserAdjustContrast(enumSelRegion, GET_OSD_CONTRAST(GET_OSD_SELECT_REGION()));
#endif
    RTDNVRamLoadColorSetting(GET_OSD_INVERSE_REGION());

#if(_CONTRAST_SUPPORT == _ON)
    UserAdjustContrast(enumSelRegionInverse, GET_OSD_CONTRAST(GET_OSD_INVERSE_REGION()));
#endif

#if((_CONTRAST_SUPPORT == _ON) || (_BRIGHTNESS_SUPPORT == _ON))
    ScalerColorBRICTSRegionEnable(enumSelRegion, _DB_APPLY_NONE, _ON);
    ScalerColorBRICTSRegionEnable(enumSelRegionInverse, _DB_APPLY_NONE, _ON);
#endif

#if(_ULTRA_HDR_SUPPORT == _ON)
    if((GET_OSD_REGION_HDR_MODE(UserAdjustGetSelectRegionPort()) == _HDR_MODE_SMPTE_ST_2084) && (enumDisplayMode != _DISPLAY_MODE_4P))
    {
        UserAdjustHDR2084(GET_OSD_SYSTEM_DISPLAY_REGION(), _HDR_MAX_MASTERING_LV_TYPE0, _HDR_COLOR_MATRIX_BT2020, GET_OSD_REGION_DARK_ENHANCE(UserAdjustGetSelectRegionPort()));
    }
    else
#endif
    {
#if(_PCM_FUNCTION == _ON)
#if(_RGB_3D_GAMMA == _ON)
        // Disable 3D Gamma First
        ScalerColor3DGammaRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_POLLING, _OFF);
        UserAdjust3DGamma(GET_OSD_PCM_SOFT_PROFT_MODE());
#endif

#if(_PCM_TABLE_TYPE == _PCM_GEN_1)

        ScalerColorPCMSePCMMode(enumSelRegion, _OGC_MODE);
        ScalerColorPCMSePCMMode(enumSelRegionInverse, _OGC_MODE);

        if((GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()) != _PCM_OSD_NATIVE) || ((GET_OSD_PCM_STATUS(GET_OSD_INVERSE_REGION()) != _PCM_OSD_NATIVE)))
        {
            UserAdjustPCM(enumSelRegion, GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()));
            UserAdjustPCM(enumSelRegionInverse, GET_OSD_PCM_STATUS(GET_OSD_INVERSE_REGION()));

            if(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()) != _PCM_OSD_NATIVE)
            {
#if((_CONTRAST_SUPPORT == _ON) || (_BRIGHTNESS_SUPPORT == _ON))
                ScalerColorBRICTSRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
#endif

#if(_RGB_3D_GAMMA == _ON)
                if(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()) == _PCM_OSD_SOFT_PROFT)
                {
                    ScalerColor3DGammaRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _ON);
                }
#endif
            }

            if((GET_OSD_PCM_STATUS(GET_OSD_INVERSE_REGION()) != _PCM_OSD_NATIVE))
            {
#if((_CONTRAST_SUPPORT == _ON) || (_BRIGHTNESS_SUPPORT == _ON))
                ScalerColorBRICTSRegionEnable(enumSelRegionInverse, _DB_APPLY_NONE, _OFF);
#endif

#if(_RGB_3D_GAMMA == _ON)
                if(GET_OSD_PCM_STATUS(GET_OSD_INVERSE_REGION()) == _PCM_OSD_SOFT_PROFT)
                {
                    ScalerColor3DGammaRegionEnable(enumSelRegionInverse, _DB_APPLY_POLLING, _ON);
                }
#endif
            }
        }
        else
#else // #else of #if(_PCM_TABLE_TYPE == _PCM_GEN_0)

        if((GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()) != _PCM_OSD_NATIVE) && ((GET_OSD_PCM_STATUS(GET_OSD_INVERSE_REGION()) != _PCM_OSD_NATIVE)))
        {
#if(_BRIGHTNESS_SUPPORT == _ON)
            ScalerColorBrightnessEnable(_FUNCTION_OFF);
#endif

#if(_CONTRAST_SUPPORT == _ON)
            ScalerColorContrastEnable(_FUNCTION_OFF);
#endif

            UserAdjustPCM(_1P_NORMAL_FULL_REGION, GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()));

#if(_RGB_3D_GAMMA == _ON)
            if(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()) == _PCM_OSD_SOFT_PROFT)
            {
                ScalerColor3DGammaRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_POLLING, _ON);
            }
#endif
        }
        else if(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()) != _PCM_OSD_NATIVE)
        {
#if((_CONTRAST_SUPPORT == _ON) || (_BRIGHTNESS_SUPPORT == _ON))
            ScalerColorBRICTSRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
#endif
            UserAdjustPCM(enumSelRegion, GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()));

#if(_RGB_3D_GAMMA == _ON)
            if(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()) == _PCM_OSD_SOFT_PROFT)
            {
                ScalerColor3DGammaRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _ON);
            }
#endif
        }
        else if((GET_OSD_PCM_STATUS(GET_OSD_INVERSE_REGION()) != _PCM_OSD_NATIVE))
        {
#if((_CONTRAST_SUPPORT == _ON) || (_BRIGHTNESS_SUPPORT == _ON))
            ScalerColorBRICTSRegionEnable(enumSelRegionInverse, _DB_APPLY_NONE, _OFF);
#endif
            UserAdjustPCM(enumSelRegionInverse, GET_OSD_PCM_STATUS(GET_OSD_INVERSE_REGION()));

#if(_RGB_3D_GAMMA == _ON)
            if(GET_OSD_PCM_STATUS(GET_OSD_INVERSE_REGION()) == _PCM_OSD_SOFT_PROFT)
            {
                ScalerColor3DGammaRegionEnable(enumSelRegionInverse, _DB_APPLY_POLLING, _ON);
            }
#endif
        }
        else
#endif //#if(_PCM_TABLE_TYPE == _PCM_GEN_1)
#endif //#if(_PCM_FUNCTION == _ON)
        {

#if(_PCM_FUNCTION == _ON)
            ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
#endif

#if(_GLOBAL_HUE_SATURATION == _ON)
            ScalerColorSRGBSetEffectiveRegion(enumSelRegion, _DB_APPLY_NONE);
            ScalerColorSRGBRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
            UserAdjustGlobalHueSat(enumSelRegion, GET_OSD_HUE(GET_OSD_SELECT_REGION()), GET_OSD_SATURATION(GET_OSD_SELECT_REGION())); // Set Global hue/sat
            ScalerColorSRGBRegionEnable(enumSelRegionInverse, _DB_APPLY_NO_POLLING, _ON);
            UserAdjustGlobalHueSat(enumSelRegionInverse, GET_OSD_HUE(GET_OSD_INVERSE_REGION()), GET_OSD_SATURATION(GET_OSD_INVERSE_REGION())); // Set Global hue/sat
#endif
            // Adjust Gamma Table
#if(_GAMMA_FUNCTION == _ON)
            ScalerColorGammaSetEffectiveRegion(enumSelRegion, _DB_APPLY_NONE);
            ScalerColorGammaRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
            ScalerColorGammaRegionEnable(enumSelRegionInverse, _DB_APPLY_POLLING, _OFF);

            if(GET_OSD_GAMMA(GET_OSD_SELECT_REGION()) != _GAMMA_OFF)
            {
                UserAdjustGamma(enumSelRegion, GET_OSD_GAMMA(GET_OSD_SELECT_REGION()));
                ScalerColorGammaRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
            }

            if(GET_OSD_GAMMA(GET_OSD_INVERSE_REGION()) != _GAMMA_OFF)
            {
                UserAdjustGamma(enumSelRegionInverse, GET_OSD_GAMMA(GET_OSD_INVERSE_REGION()));
                ScalerColorGammaRegionEnable(enumSelRegionInverse, _DB_APPLY_NO_POLLING, _ON);
            }
#endif
        }
    } // #End of if(GET_OSD_REGION_HDR_MODE(UserAdjustGetSelectRegionPort()) == _HDR_MODE_SMPTE_ST_2084)

#if(_IAPS_SUPPORT == _ON)
    ScalerColorIAPSGainSetEffectiveRegion(enumSelRegion, _DB_APPLY_NONE);
#endif

#if(_UNIFORMITY_SUPPORT == _ON)
    ScalerColorPanelUniformityRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_POLLING, _OFF);

    if((GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION()) == _ON) && (GET_OSD_PANEL_UNIFORMITY(GET_OSD_INVERSE_REGION()) == _ON))
    {
        ScalerColorPanelUniformityRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_NO_POLLING, _ON);
    }
    else if(GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION()) == _ON)
    {
        ScalerColorPanelUniformityRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
    }
    else if(GET_OSD_PANEL_UNIFORMITY(GET_OSD_INVERSE_REGION()) == _ON)
    {
        ScalerColorPanelUniformityRegionEnable(enumSelRegionInverse, _DB_APPLY_NO_POLLING, _ON);
    }
#endif

#if(_DCC_FUNCTION == _ON)
    ScalerColorDCCSetEffectiveRegion(enumSelRegion, _DB_APPLY_NONE);
#endif

#if((_ICM_SUPPORT == _ON) || (_SIX_COLOR_SUPPORT == _ON) || (_ICM_BRI_SUPPORT == _ON) || (_SCM_SUPPORT == _ON))
    ScalerColorICMSCMSetEffectiveRegion(enumSelRegion, _DB_APPLY_NONE);
#endif

    switch(GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()))
    {
        case _COLOREFFECT_STANDARD:
#if(_DCC_FUNCTION == _ON)
            ScalerColorDCCRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
#endif

#if(_ICM_SUPPORT == _ON)
            ScalerColorICMSCMRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
#endif
            break;

        case _COLOREFFECT_USER:
#if(_DCC_FUNCTION == _ON)
            ScalerColorDCCRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
#endif

#if(_ICM_SUPPORT == _ON)
            ScalerColorICMSCMRegionEnable(enumSelRegion, _DB_APPLY_NONE, _ON);
#endif

#if(_SIX_COLOR_SUPPORT == _ON)
            for(ucIndex = 0; ucIndex < 6; ucIndex++)
            {
                SET_OSD_SIX_COLOR(ucIndex);
                OsdDisplaySixColorGetOneColor(enumSelRegion, ucIndex);
                ScalerColorSixColorAdjust(enumSelRegion, ucIndex, GET_OSD_SIX_COLOR_HUE(), GET_OSD_SIX_COLOR_SATURATION());
            }

            ScalerColorSixColorInitial(enumSelRegion);
#endif
            break;

        case _COLOREFFECT_MOVIE:
        case _COLOREFFECT_GAME:
        case _COLOREFFECT_PHOTO:
        case _COLOREFFECT_VIVID:
#if(_DCC_FUNCTION == _ON)
            ScalerColorDCCRegionEnable(enumSelRegion, _DB_APPLY_NONE, _ON);
#endif

#if(_ICM_SUPPORT == _ON)
            ScalerColorICMSCMRegionEnable(enumSelRegion, _DB_APPLY_NONE, _ON);
#endif

#if(_DCC_FUNCTION == _ON)
            UserAdjustDCC(enumSelRegion, GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()));
            ScalerColorSetDCCAutoModeRegion(g_enumDCCMeasureRegion);
#endif

// Adjust SCM Table, Should before ICM Adjust
#if(_SCM_SUPPORT == _ON)
            UserAdjustSCM(enumSelRegion, GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()));
#endif

#if(_ICM_SUPPORT == _ON)
            UserAdjustICM(enumSelRegion, GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()));
#endif
            break;

        default:
            break;
    }

    switch(GET_OSD_COLOR_EFFECT(GET_OSD_INVERSE_REGION()))
    {
        case _COLOREFFECT_STANDARD:
#if(_DCC_FUNCTION == _ON)
            ScalerColorDCCRegionEnable(enumSelRegionInverse, _DB_APPLY_NONE, _OFF);
#endif

#if(_ICM_SUPPORT == _ON)
            ScalerColorICMSCMRegionEnable(enumSelRegionInverse, _DB_APPLY_NONE, _OFF);
#endif
            break;

        case _COLOREFFECT_USER:
#if(_DCC_FUNCTION == _ON)
            ScalerColorDCCRegionEnable(enumSelRegionInverse, _DB_APPLY_NONE, _OFF);
#endif

#if(_ICM_SUPPORT == _ON)
            ScalerColorICMSCMRegionEnable(enumSelRegionInverse, _DB_APPLY_NONE, _ON);
#endif

#if(_SIX_COLOR_SUPPORT == _ON)
            for(ucIndex = 0; ucIndex < 6; ucIndex++)
            {
                SET_OSD_SIX_COLOR(ucIndex);
                OsdDisplaySixColorGetOneColor(enumSelRegionInverse, ucIndex);
                ScalerColorSixColorAdjust(enumSelRegionInverse, ucIndex, GET_OSD_SIX_COLOR_HUE(), GET_OSD_SIX_COLOR_SATURATION());
            }

            ScalerColorSixColorInitial(enumSelRegionInverse);
#endif
            break;

        case _COLOREFFECT_MOVIE:
        case _COLOREFFECT_GAME:
        case _COLOREFFECT_PHOTO:
        case _COLOREFFECT_VIVID:
#if(_DCC_FUNCTION == _ON)
            ScalerColorDCCRegionEnable(enumSelRegionInverse, _DB_APPLY_NONE, _ON);
#endif

#if(_ICM_SUPPORT == _ON)
            ScalerColorICMSCMRegionEnable(enumSelRegionInverse, _DB_APPLY_NONE, _ON);
#endif

#if(_DCC_FUNCTION == _ON)
            UserAdjustDCC(enumSelRegionInverse, GET_OSD_COLOR_EFFECT(GET_OSD_INVERSE_REGION()));
            ScalerColorSetDCCAutoModeRegion(g_enumDCCMeasureRegion);
#endif

// Adjust SCM Table, Should before ICM Adjust
#if(_SCM_SUPPORT == _ON)
            UserAdjustSCM(enumSelRegionInverse, GET_OSD_COLOR_EFFECT(GET_OSD_INVERSE_REGION()));
#endif

#if(_ICM_SUPPORT == _ON)
            UserAdjustICM(enumSelRegionInverse, GET_OSD_COLOR_EFFECT(GET_OSD_INVERSE_REGION()));
#endif
            break;

        default:
            break;
    }
#if (_FALSE_COLOR_SUPPORT == _ON)
    if((enumSelRegion == _1P_NORMAL_FULL_REGION) && (GET_OSD_FALSE_COLOR_STATUS() != _OSD_FALSE_COLOR_OFF))
    {
        UserAdjustFalseColor(enumSelRegion, GET_OSD_FALSE_COLOR_STATUS());
    }
#endif
}

//--------------------------------------------------
// Description  : Set User Required Color Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustColorProc(EnumDisplayRegion enumDisplayRegion)
{
    EnumSourceSearchPort enumSourceSearchPort = SysRegionGetPortType(enumDisplayRegion);
    EnumSourceTypeDef enumSourceTypeDef = SysRegionGetSourceType(enumDisplayRegion);
    // EnumSelRegion enumSelRegionInverse = ScalerRegionGetInverse((EnumSelRegion)enumDisplayRegion);

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
    UserInterfaceAdjustHighlightWindow(_DB_APPLY_NO_POLLING);
#endif

    if(SysRegionCheckDisplayEvent(enumDisplayRegion, _DISPLAY_EVENT_FIRST_ACTIVE) == _FALSE)
    {
        // Set Color Conversion
        if(enumSourceTypeDef == _SOURCE_VGA)
        {
            SET_OSD_COLOR_FORMAT(enumSourceSearchPort, GET_VGA_COLOR_FORMAT_STATUS());
        }
        else if(enumSourceTypeDef == _SOURCE_DVI)
        {
            SET_OSD_COLOR_FORMAT(enumSourceSearchPort, GET_DVI_COLOR_FORMAT_STATUS());
        }
        else
        {
            if(ScalerColorGetColorSpaceRGB(ScalerColorGetColorSpace(enumSourceSearchPort)) == _TRUE)
            {
                SET_OSD_COLOR_FORMAT(enumSourceSearchPort, _COLOR_SPACE_RGB);
            }
            else
            {
                SET_OSD_COLOR_FORMAT(enumSourceSearchPort, _COLOR_SPACE_YPBPR);
            }
        }
    }

    // Adjust Color Space
    if(GET_OSD_COLOR_FORMAT(enumSourceSearchPort) == _COLOR_SPACE_RGB)
    {
        SysModeColorSpaceConvert(enumDisplayRegion, enumSourceSearchPort, _COLOR_SPACE_RGB, _DB_APPLY_NO_POLLING);
    }
    else
    {
        SysModeColorSpaceConvert(enumDisplayRegion, enumSourceSearchPort, _COLOR_SPACE_YPBPR, _DB_APPLY_NO_POLLING);
    }

    // Adjust UltraVivid
#if(_ULTRA_VIVID_SUPPORT == _ON)
    if(GET_OSD_HLWIN_TYPE() != _HL_WIN_OFF)
    {
        UserCommonAdjustUltraVivid(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_NONE);
        UserCommonAdjustUltraVivid(ScalerRegionGetInverse(GET_OSD_SYSTEM_SELECT_REGION()), _DB_APPLY_NO_POLLING);
    }
    else
    {
        UserCommonAdjustUltraVivid((EnumSelRegion)enumDisplayRegion, _DB_APPLY_POLLING);
    }
#endif

#if(_SHARPNESS_SUPPORT == _ON)
    // Adjust Sharpness
    UserCommonAdjustSharpness((EnumSelRegion)enumDisplayRegion, enumSourceSearchPort);
#endif

    // Adjust Backlight
    UserAdjustBacklight(GET_OSD_BACKLIGHT());

    // Adjust Brightness & Contrast
    RTDNVRamLoadOsdInputSourceData(enumSourceTypeDef);

    // Adjust Transparency
    ScalerOsdSetTransparency(GET_OSD_TRANSPARENCY_STATUS());

    // User Adjust Background Color
    ScalerDDomainBackgroundSetColor(ScalerRegionGetDisplayDataPath(enumDisplayRegion), 0, 0, 0);

#if(_OD_SUPPORT == _ON)
    ScalerODAdjustDeltaGain(GET_OSD_OD_GAIN());
    ScalerODEnable(GET_OSD_OD_STATUS());
#endif

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
    // Adjust Highlight Window Effect Space
    UserAdjustHighLightWindowEffectSpace();

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
    if(GET_OSD_ASPECT_RATIO_TYPE(enumSourceSearchPort) != _OSD_ASPECT_RATIO_ORIGIN)
#endif
    {
        if(GET_OSD_HLWIN_TYPE() == _HL_WIN_OFF)
        {
            ScalerColorHLWBorderEnable(_OFF, _OFF, _OFF, _OFF, _DB_APPLY_POLLING);
        }
        else
        {
            UserAdjustHLWinType(GET_OSD_HLWIN_TYPE());
            ScalerColorHLWBorderEnable(_ON, _ON, _ON, _ON, _DB_APPLY_POLLING);
        }
    }
#endif // End of #if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)

    // Adjust Normalize Factor, should after HLW setting
#if(_DCC_FUNCTION == _ON)
    ScalerColorDCCNormalizeFactorAdjust(g_enumDCCMeasureRegion);
#endif

#if(_ULTRA_HDR_SUPPORT == _ON)
    UserInterfaceAdjustHDRColorProcInitial(enumDisplayRegion);
#endif
}

#if(_ULTRA_HDR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Initial HDR Auto Mode using in UserInterfaceAdjustColorProc
// Input Value  : EnumDisplayRegion
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustHDRColorProcInitial(EnumDisplayRegion enumDisplayRegion)
{
    if((GET_OSD_REGION_HDR_MODE(SysRegionGetPortType(enumDisplayRegion)) == _HDR_MODE_AUTO) && (SysModeGetDisplayMode() != _DISPLAY_MODE_4P))
    {
        if(GET_HDR_EOTF(enumDisplayRegion) == _HDR_INFO_EOTF_SMPTE_ST_2084)
        {
            DebugMessageHDR("HDR Auto Mode Initial Set HDR", 0x00);
            UserCommonAdjustHDRAutoMode(enumDisplayRegion, GET_OSD_REGION_DARK_ENHANCE(UserAdjustGetSelectRegionPort()));
            UserAdjustBacklight(_BACKLIGHT_MAX); // Must!!!!
        }
        else
        {
            DebugMessageHDR("HDR Auto Mode Initial Set PCM", 0x00);
            UserAdjustPCM((EnumSelRegion)enumDisplayRegion, GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()));

            if(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()) != _PCM_OSD_NATIVE)
            {
#if((_CONTRAST_SUPPORT == _ON) || (_BRIGHTNESS_SUPPORT == _ON))
                ScalerColorBRICTSRegionEnable((EnumSelRegion)enumDisplayRegion, _DB_APPLY_NONE, _OFF);
#endif

#if(_RGB_3D_GAMMA == _ON)
                if(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()) == _PCM_OSD_SOFT_PROFT)
                {
                    ScalerColor3DGammaRegionEnable((EnumSelRegion)enumDisplayRegion, _DB_APPLY_POLLING, _ON);
                }
#endif
            }
        }
    }
}
#endif

//--------------------------------------------------
// Description  : Set Color in pass normal active process
// Input Value  : None
// Output Value : void
//--------------------------------------------------
void UserInterfaceAdjustActiveByPassColorProc(EnumDisplayRegion enumDisplayRegion)
{
    enumDisplayRegion = enumDisplayRegion;
    return;
}

#if(_ULTRA_VIVID_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set UltraVivid Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustUltraVivid(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply)
{
    BYTE ucUltraVividStatus = GET_OSD_ULTRA_VIVID_STATUS(GET_OSD_INVERSE_REGION());

    if((GET_OSD_SYSTEM_SELECT_REGION() == enumSelRegion) ||
       (GET_OSD_SYSTEM_SELECT_REGION() == _PIP_FULL_REGION) ||
       (GET_OSD_SYSTEM_SELECT_REGION() == _PBP_LR_FULL_REGION) ||
       (GET_OSD_SYSTEM_SELECT_REGION() == _PBP_TB_FULL_REGION) ||
       (GET_OSD_SYSTEM_SELECT_REGION() == _4P_FULL_REGION))
    {
        ucUltraVividStatus = GET_OSD_ULTRA_VIVID_STATUS(GET_OSD_SELECT_REGION());
    }
    else if((GET_OSD_SYSTEM_SELECT_REGION() >= _4P_LT_OUTSIDE) && (GET_OSD_SYSTEM_SELECT_REGION() <= _4P_RB_OUTSIDE))
    {
        if(ScalerRegionGetInverse(GET_OSD_SYSTEM_SELECT_REGION()) != enumSelRegion)
        {
            ucUltraVividStatus = GET_OSD_ULTRA_VIVID_STATUS(GET_OSD_SELECT_REGION());
        }
    }

    if((enumSelRegion == ScalerRegionGetInverse(GET_OSD_SYSTEM_SELECT_REGION())) &&
       ((GET_OSD_SYSTEM_SELECT_REGION() == _4P_DEMO_INSIDE) ||
        (GET_OSD_SYSTEM_SELECT_REGION() == _4P_DEMO_OUTSIDE) ||
        (GET_OSD_SYSTEM_SELECT_REGION() == _PBP_TB_DEMO_INSIDE) ||
        (GET_OSD_SYSTEM_SELECT_REGION() == _PBP_TB_DEMO_OUTSIDE)))
    {
        ucUltraVividStatus = _ULTRA_VIVID_OFF;
    }

    if(ucUltraVividStatus != _ULTRA_VIVID_OFF)
    {
        ScalerColorUltraVividAdjust(enumSelRegion, tCOLOR_ULTRAVIVID_SETTING_TABLE[ucUltraVividStatus - 1], GET_CURRENT_BANK_NUMBER());

        ScalerColorUltraVividRegionEnable(enumSelRegion, enumDBApply, _ON);
    }
    else
    {
        ScalerColorUltraVividRegionEnable(enumSelRegion, enumDBApply, _OFF);
    }
}
#endif  // End of #if(_ULTRA_VIVID_SUPPORT == _ON)

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Adjust hightlight window
// Input Value  : DB apply mode
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustHighlightWindow(EnumDBApply enumDBApply)
{
    ScalerColorHLWSetting(GET_OSD_SYSTEM_SELECT_REGION(), enumDBApply);
}
#endif

#if(_BORDER_WINDOW_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Adjust Select Region Boarder
// Input Value  : DB apply mode
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustBorderWindow(EnumDBApply enumDBApply)
{
#if((_2P_DISPLAY_SUPPORT == _ON) || (_4P_DISPLAY_SUPPORT == _ON))
    if(GET_OSD_SELECT_REGION_WIDTH() == 0x00)
    {
        // Disable border when width = 0
        ScalerColorBorderEnable(_BORDER_WIN1, 0, 0, 0, 0, _DB_APPLY_NONE);
        ScalerColorBorderEnable(_BORDER_WIN2, 0, 0, 0, 0, enumDBApply);
    }
    else
    {
        StructTimingFormat stTimingFormat = {0};

        // Set border color
        switch(GET_OSD_SELECT_REGION_COLOR())
        {
            default:
            case _SELECT_REGION_COLOR_0: // Red
                ScalerColorBorderAdjust(_BORDER_WIN1, GET_OSD_SELECT_REGION_WIDTH(), _OSD_SELECT_REGION_BORDER_RED, 0, 0, _DB_APPLY_NONE);
                ScalerColorBorderAdjust(_BORDER_WIN2, GET_OSD_SELECT_REGION_WIDTH(), _OSD_SELECT_REGION_BORDER_RED, 0, 0, _DB_APPLY_NONE);
                break;

            case _SELECT_REGION_COLOR_1: // Green
                ScalerColorBorderAdjust(_BORDER_WIN1, GET_OSD_SELECT_REGION_WIDTH(), 0, _OSD_SELECT_REGION_BORDER_GREEN, 0, _DB_APPLY_NONE);
                ScalerColorBorderAdjust(_BORDER_WIN2, GET_OSD_SELECT_REGION_WIDTH(), 0, _OSD_SELECT_REGION_BORDER_GREEN, 0, _DB_APPLY_NONE);
                break;

            case _SELECT_REGION_COLOR_2: // Blue
                ScalerColorBorderAdjust(_BORDER_WIN1, GET_OSD_SELECT_REGION_WIDTH(), 0, 0, _OSD_SELECT_REGION_BORDER_BLUE, _DB_APPLY_NONE);
                ScalerColorBorderAdjust(_BORDER_WIN2, GET_OSD_SELECT_REGION_WIDTH(), 0, 0, _OSD_SELECT_REGION_BORDER_BLUE, _DB_APPLY_NONE);
                break;

            case _SELECT_REGION_COLOR_3: // White
                ScalerColorBorderAdjust(_BORDER_WIN1, GET_OSD_SELECT_REGION_WIDTH(), _OSD_SELECT_REGION_BORDER_WHITE, _OSD_SELECT_REGION_BORDER_WHITE, _OSD_SELECT_REGION_BORDER_WHITE, _DB_APPLY_NONE);
                ScalerColorBorderAdjust(_BORDER_WIN2, GET_OSD_SELECT_REGION_WIDTH(), _OSD_SELECT_REGION_BORDER_WHITE, _OSD_SELECT_REGION_BORDER_WHITE, _OSD_SELECT_REGION_BORDER_WHITE, _DB_APPLY_NONE);
                break;
        }

        switch(SysModeGetDisplayMode())
        {
            default:
            case _DISPLAY_MODE_1P:
                // Disable border in 1P mode
                ScalerColorBorderEnable(_BORDER_WIN1, 0, 0, 0, 0, _DB_APPLY_NONE);
                ScalerColorBorderEnable(_BORDER_WIN2, 0, 0, 0, 0, enumDBApply);
                return;

#if(_PBP_LR_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_MODE_PBP_LR:
                ScalerMDomainGetSubBackground(&stTimingFormat);
                ScalerColorBorderPositionAdjust(_BORDER_WIN1, (stTimingFormat.usHStart - _PANEL_DH_START) - GET_OSD_SELECT_REGION_WIDTH() / 2, ((stTimingFormat.usHStart - _PANEL_DH_START) - 1) - GET_OSD_SELECT_REGION_WIDTH(), 0, (_PANEL_DV_HEIGHT - 1), _DB_APPLY_NONE);
                ScalerColorBorderEnable(_BORDER_WIN1, 0, 0, 1, 0, _DB_APPLY_NONE);
                ScalerColorBorderEnable(_BORDER_WIN2, 0, 0, 0, 0, enumDBApply);
                break;
#endif

#if(_PBP_TB_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_MODE_PBP_TB:
                ScalerColorBorderPositionAdjust(_BORDER_WIN1, 0, (_PANEL_DH_WIDTH - 1), 0, (_PANEL_DV_HEIGHT >> 1) - GET_OSD_SELECT_REGION_WIDTH() / 2, _DB_APPLY_NONE);
                ScalerColorBorderEnable(_BORDER_WIN1, 0, 1, 0, 0, _DB_APPLY_NONE);
                ScalerColorBorderEnable(_BORDER_WIN2, 0, 0, 0, 0, enumDBApply);
                break;
#endif

#if(_PIP_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_MODE_PIP:
                ScalerMDomainGetSubBackground(&stTimingFormat);
                ScalerColorBorderPositionAdjust(_BORDER_WIN1,
                                                (stTimingFormat.usHStart - _PANEL_DH_START),
                                                (stTimingFormat.usHWidth - GET_OSD_SELECT_REGION_WIDTH()),
                                                (stTimingFormat.usVStart - _PANEL_DV_START),
                                                (stTimingFormat.usVHeight - GET_OSD_SELECT_REGION_WIDTH()),
                                                _DB_APPLY_NONE);
                ScalerColorBorderEnable(_BORDER_WIN1, 1, 1, 1, 1, _DB_APPLY_NONE);
                ScalerColorBorderEnable(_BORDER_WIN2, 0, 0, 0, 0, enumDBApply);
                break;
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_MODE_4P:
                // Right-bottom
                ScalerColorBorderPositionAdjust(_BORDER_WIN1,
                                                ((_PANEL_DH_WIDTH >> 1) - GET_OSD_SELECT_REGION_WIDTH() / 2),
                                                ((_PANEL_DH_WIDTH >> 1) - 1),
                                                ((_PANEL_DV_HEIGHT >> 1) - GET_OSD_SELECT_REGION_WIDTH() / 2),
                                                (((_PANEL_DV_HEIGHT >> 1) - 1) + GET_OSD_SELECT_REGION_WIDTH()),
                                                _DB_APPLY_NONE);
                ScalerColorBorderEnable(_BORDER_WIN1, 1, 0, 1, 0, _DB_APPLY_NONE);

                // Left-top
                ScalerColorBorderPositionAdjust(_BORDER_WIN2,
                                                0,
                                                ((_PANEL_DH_WIDTH >> 1) - GET_OSD_SELECT_REGION_WIDTH() / 2),
                                                0,
                                                ((_PANEL_DV_HEIGHT >> 1) - GET_OSD_SELECT_REGION_WIDTH() / 2),
                                                _DB_APPLY_NONE);
                ScalerColorBorderEnable(_BORDER_WIN2, 0, 1, 0, 1, enumDBApply);
                break;
#endif
        }
    }
#else

    enumDBApply = enumDBApply;

#endif // End of #if((_4P_DISPLAY_SUPPORT == _ON) || (_2P_DISPLAY_SUPPORT == _ON))

}
#endif

#if(_SHARPNESS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Sharpness Coef
// Input Value  : enumSUCoefType --> SU Coef Type
//                enumSelRegion --> select region
//                enumSourceSearchPort --> select retion port
// Output Value : SU Coef
//--------------------------------------------------
code BYTE *UserInterfaceGetSharpnessCoef(EnumSUCoefType enumSUCoefType, EnumSelRegion enumSelRegion, EnumSourceSearchPort enumSourceSearchPort)
{
    enumSelRegion = enumSelRegion;

    switch(enumSUCoefType)
    {
#if((_HSU_128TAPS_SUPPORT == _ON) || (_VSU_128TAPS_SUPPORT == _ON))
        case _H_V_SU_128TAPS_NORMAL:
            return tSCALE_128TAPS_NORMAL_COEF_TABLE[GET_OSD_SHARPNESS(enumSourceSearchPort)];
#endif

#if((_HSU_96TAPS_SUPPORT == _ON) || (_VSU_96TAPS_SUPPORT == _ON))
        case _H_V_SU_96TAPS_NORMAL:
            return tSCALE_96TAPS_NORMAL_COEF_TABLE[GET_OSD_SHARPNESS(enumSourceSearchPort)];
#endif

#if(_HSU_128TAPS_SUPPORT == _ON)
        case _H_SU_128TAPS_1_TO_1:
            return tSCALE_128TAPS_1to1_COEF_TABLE[GET_OSD_SHARPNESS(enumSourceSearchPort)];
#endif

#if(_HSU_96TAPS_SUPPORT == _ON)
        case _H_SU_96TAPS_1_TO_1:
            return tSCALE_96TAPS_1to1_COEF_TABLE[GET_OSD_SHARPNESS(enumSourceSearchPort)];
#endif
        default:
            return _NULL_POINTER;
    }
}

//--------------------------------------------------
// Description  : Get Sharpness Coef BankNum
// Input Value  : None
// Output Value : BankNum
//--------------------------------------------------
BYTE UserInterfaceGetSharpnessCoefBankNum(void)
{
    return GET_CURRENT_BANK_NUMBER();
}

//--------------------------------------------------
// Description  : User Bypass Check
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit UserInterfaceSharpnessBypassCheck(void)
{
    return _FALSE;
}
#endif

#if(_DCR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Adjust DCR
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustDCR(void)
{
    PDATA_DWORD(0) = ScalerColorDCRReadResult(_DCR_ABOVE_TH1_NUM);
}
#endif // End of #if(_DCR_SUPPORT == _ON)

//--------------------------------------------------
// Description  : OSD Power On Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustOsdPowerOnInitial(void)
{
#if(_IAPS_SUPPORT == _ON)
    EnumSelRegion enumSelRegion = GET_OSD_SYSTEM_SELECT_REGION();
    EnumSelRegion enumSelRegionInverse = ScalerRegionGetInverse(enumSelRegion);
#endif

#if(_UNIFORMITY_SUPPORT == _ON)
    // Uniformity parameters setting
    ScalerColorPanelUniformityInitial(_PANEL_UNIFORMITY_MULTI_LUT_MODE);

    ScalerColorPanelUniformityRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_POLLING, _OFF);

    // Enable Uniformity
    ScalerColorPanelUniformityEnable(_FUNCTION_ON);

    if(GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION()) == _ON)
    {
        UserAdjustPanelUniformityMode(_UNIFORMITY_OSD_TYPE1);
    }
    else if(GET_OSD_PANEL_UNIFORMITY(GET_OSD_INVERSE_REGION()) == _ON)
    {
        UserAdjustPanelUniformityMode(_UNIFORMITY_OSD_TYPE1);
    }
#endif

    // Adjust Color Palette
    OsdPaletteSelectPalette(_PALETTE_RTD_LOGO);

#if(_DCR_SUPPORT == _ON)
    // DCR HLW CTRL
    ScalerColorDCRSetMeasureRegion(_1P_NORMAL_FULL_REGION, _DB_APPLY_NONE);
    // Set threshold
    ScalerColorDCRAdjust(_DCR_THESHOLD1, _DCR_THESHOLD2, _MEASURE_AVERAGE);

#endif

#if(_IAPS_SUPPORT == _ON)
    ScalerColorIAPSGainSoftClampAdjust(enumSelRegion, 0xB0);
    ScalerColorIAPSGainSoftClampAdjust(enumSelRegionInverse, 0xB0);
    ScalerColorIAPSGainValueAdjust(enumSelRegion, 0x2000);
    ScalerColorIAPSGainValueAdjust(enumSelRegionInverse, 0x2000);
#endif

#if(_OD_SUPPORT == _ON)
    UserAdjustOD();
#endif

#if(_PCM_FUNCTION == _ON)
    // Load Default PCM Table
    UserAdjustPCM(_1P_NORMAL_FULL_REGION, _PCM_OSD_USER);
#endif
}

//--------------------------------------------------
// Description  : OSD Active Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustOsdActiveProc(EnumDisplayRegion enumDisplayRegion)
{
    // Save auto search input port
    if((UserInterfaceGetAutoSearchTarget() == enumDisplayRegion) &&
       (SysSourceGetScanType() != _SOURCE_SWITCH_FIXED_PORT))
    {
        switch(ScalerRegionGetIndex(enumDisplayRegion))
        {
            default:
            case 0x00:
                if(UserCommonNVRamGetSystemData(_SEARCH_PORT_0) != SysRegionGetPortType(enumDisplayRegion))
                {
                    UserCommonNVRamSetSystemData(_SEARCH_PORT_0, SysRegionGetPortType(enumDisplayRegion));
                    UserCommonNVRamSaveSystemData();
                }
                break;

#if(_MULTI_DISPLAY_MAX >= 0x02)
            case 0x01:
                if(UserCommonNVRamGetSystemData(_SEARCH_PORT_1) != SysRegionGetPortType(enumDisplayRegion))
                {
                    UserCommonNVRamSetSystemData(_SEARCH_PORT_1, SysRegionGetPortType(enumDisplayRegion));
                    UserCommonNVRamSaveSystemData();
                }
                break;

#if(_4P_DISPLAY_SUPPORT == _ON)
            case 0x02:
                if(UserCommonNVRamGetSystemData(_SEARCH_PORT_2) != SysRegionGetPortType(enumDisplayRegion))
                {
                    UserCommonNVRamSetSystemData(_SEARCH_PORT_2, SysRegionGetPortType(enumDisplayRegion));
                    UserCommonNVRamSaveSystemData();
                }
                break;

            case 0x03:
                if(UserCommonNVRamGetSystemData(_SEARCH_PORT_3) != SysRegionGetPortType(enumDisplayRegion))
                {
                    UserCommonNVRamSetSystemData(_SEARCH_PORT_3, SysRegionGetPortType(enumDisplayRegion));
                    UserCommonNVRamSaveSystemData();
                }
                break;
#endif

#endif
        }
    }

    // DDCCI switch to active port
    ScalerMcuDdcciSwitchPort(GET_OSD_DDCCI_STATUS());
    UserCommonDdcciMapping();

    if(GET_FAIL_SAFE_MODE(ScalerRegionGetIndex(enumDisplayRegion)) == _TRUE)
    {
        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SHOW_FAIL_SAFE_MODE_MSG);
    }
    else
    {
        SET_OSD_EVENT_MESSAGE(_OSDEVENT_ACTIVE_DO_ONE_TIME_MSG);
    }

#if((_OD_SUPPORT == _ON) && (_FREESYNC_SUPPORT == _ON))
    UserAdjustOD();
#endif

#if(_FREEZE_SUPPORT == _ON)
    if(SysModeGetDisplayMode() == _DISPLAY_MODE_1P)
    {
        UserCommonAdjustDisplayFreeze(GET_OSD_FREEZE_STATUS());
    }
#endif

    ScalerDDomainBackgroundEnable(ScalerRegionGetDisplayDataPath(enumDisplayRegion), _DISABLE);

#if(_PIP_BLENDING_SUPPORT == _ON)
    // Adjust PIPBlending level
    UserAdjustPipTransparency();
#endif
}

//--------------------------------------------------
// Description  : OSD Reset Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustOsdResetProc(void)
{
    // Disable OSD
    if(GET_OSD_LOGO_ON() == _OFF)
    {
        OsdDispDisableOsd();
    }

    SET_OSD_LOGO_ON(_OFF);

    // Cancel Timer Events
    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE_OSD_LOGO);
    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);
    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_DO_AUTO_COLOR);
    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_DP_VERSION_SELECT);
    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISPLAYMODE_SELECT);
    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_HLWIN_TYPE5_MOVE);
}

//--------------------------------------------------
// Description  : OSD Reset Region Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustOsdResetRegionProc(EnumDisplayRegion enumDisplayRegion)
{
    switch(GET_OSD_DISPLAY_MODE())
    {
        default:
            break;

        case _OSD_DM_1P:
        case _OSD_DM_2P_LR:
        case _OSD_DM_2P_TB:
        case _OSD_DM_2P_PIP:
        case _OSD_DM_4P:

            switch(SysRegionGetDisplayState(enumDisplayRegion))
            {
                case _DISPLAY_STATE_NO_SIGNAL:
                case _DISPLAY_STATE_OOR:

                    if(GET_OSD_STATE() == _MENU_MESSAGE_DISPLAY) // if display power saving, close Hint message
                    {
                        OsdDispDisableOsd();
                    }

                    // Cancel PS Timer Events
                    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
                    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
                    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
                    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);

                    break;

                default:
                    break;
            }
            break;
    }

    // Update LED status
    if(SysRegionGetDisplayStateCount(_DISPLAY_STATE_ACTIVE) == 0X00)
    {
        UserInterfaceKeyPadLedControl(_LED_POWER_SEARCH);
    }
}

//--------------------------------------------------
// Description  : OSD Resume from NSG Region Process
// Input Value  : display region
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustOsdResumeRegionProc(EnumDisplayRegion enumDisplayRegion)
{
    enumDisplayRegion = enumDisplayRegion;

    if(GET_OSD_STATE() == _MENU_MESSAGE_DISPLAY) // if display power saving, close Hint message
    {
        OsdDispDisableOsd();
    }

    // Cancel PS Timer Events
    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);
}

#if(_VGA_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check ModeIndex
// Input Value  : System ModeIndex
// Output Value : ModeIndex
//--------------------------------------------------
BYTE UserInterfaceGetVGAConfuseMode(BYTE ucModeIndex)
{
    if((ucModeIndex == _MODE_640x480_60HZ) || (ucModeIndex == _MODE_720x480_60HZ_GTF) || (ucModeIndex == _MODE_720x480p_60HZ))
    {
        if(GET_INPUT_TIMING_VSYNCWIDTH() <= 4)
        {
            ucModeIndex = _MODE_640x480_60HZ;

            DebugMessageAnalog("Detected by Special Case to 640x480-60", _MODE_640x480_60HZ);
        }
        else if((GET_INPUT_TIMING_H_POLARITY() == _FALSE) && (GET_INPUT_TIMING_V_POLARITY() == _FALSE))
        {
            ucModeIndex = _MODE_720x480_60HZ_GTF;

            DebugMessageAnalog("Detected by Special Case to 720x480-60_GTF", _MODE_720x480_60HZ_GTF);
        }
        else
        {
            ucModeIndex = _MODE_720x480p_60HZ;

            DebugMessageAnalog("Detected by Special Case to 720x480-60", _MODE_720x480p_60HZ);
        }
    }

    if((ucModeIndex == _MODE_720x400_70HZ) || (ucModeIndex == _MODE_640x400_70HZ))
    {
        if((GET_INPUT_TIMING_H_POLARITY() == _TRUE) && (GET_INPUT_TIMING_V_POLARITY() == _FALSE))
        {
            ucModeIndex = _MODE_640x350_70HZ;

            DebugMessageAnalog("Detected by Special Case to _MODE_640x350_70HZ", _MODE_640x350_70HZ);
        }
    }

    if((ucModeIndex == _MODE_640x400_85HZ) || (ucModeIndex == _MODE_720x400_85HZ))
    {
        if((GET_INPUT_TIMING_H_POLARITY() == _TRUE) && (GET_INPUT_TIMING_V_POLARITY() == _FALSE))
        {
            ucModeIndex = _MODE_640x350_85HZ;
        }

        DebugMessageAnalog("Detected by Special Case to _MODE_640x350_85HZ", _MODE_640x350_85HZ);
    }

    return ucModeIndex;
}

//--------------------------------------------------
// Description  : Check Load Mode Table Value
// Input Value  : None
// Output Value : _TURE -> Force Load Mode Table Value
//--------------------------------------------------
bit UserInterfaceGetLoadModeTableDefaultStatus(void)
{
    return _FALSE;
}

//--------------------------------------------------
// Description  : Check VGA First Auto Config
// Input Value  : None
// Output Value : _TRUE => Do Auto Config
//--------------------------------------------------
bit UserInterfaceGetFirstAutoConfigStatus(void)
{
    if((GET_VGA_MODE_DO_FIRST_AUTO() == _TRUE) &&
       (GET_INPUT_TIMING_HWIDTH() > 720))
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Percentage of AutoConfig
// Input Value  : Percentage
// Output Value : None
//--------------------------------------------------
void UserInterfaceGetAutoConfigPercentage(BYTE ucAutoPercentage)
{
    ucAutoPercentage = ucAutoPercentage;
    g_usAdjustValue = ucAutoPercentage;
}

//--------------------------------------------------
// Description  : VGA Auto Config Flow control for V position
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit UserInterfaceSkipAutoVpos(void)
{
    return _FALSE;
}

//--------------------------------------------------
// Description  : VGA Auto Config Flow control for H position
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit UserInterfaceSkipAutoHpos(void)
{
    return _FALSE;
}
#endif // End of #if(_VGA_SUPPORT == _ON)

#if(_MHL_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User RCP Handler
// Input Value  : RCP Key Code
// Output Value : True or False
//--------------------------------------------------
bit UserInterfaceAdjustMHLMscRCPProc(BYTE ucKeyCode)
{
    // Check RCP Key Code
    switch(ucKeyCode)
    {
#if(_AUDIO_SUPPORT == _ON)
        case _MHL_RCP_VOLUME_UP:

            if(GET_OSD_VOLUME() < 100)
            {
                SET_OSD_VOLUME(GET_OSD_VOLUME() + 1);
            }

            if(UserInterfaceGetAudioReadyToPlayStatus() == _TRUE)
            {
                UserAdjustAudioVolume(GET_OSD_VOLUME());
            }
            break;

        case _MHL_RCP_VOLUME_DOWN:

            if(GET_OSD_VOLUME() > 0)
            {
                SET_OSD_VOLUME(GET_OSD_VOLUME() - 1);
            }

            if(UserInterfaceGetAudioReadyToPlayStatus() == _TRUE)
            {
                UserAdjustAudioVolume(GET_OSD_VOLUME());
            }
            break;

        case _MHL_RCP_MUTE:
        case _MHL_RCP_MUTE_FUNCTION:

            SET_OSD_VOLUME_MUTE(!GET_OSD_VOLUME_MUTE());

            if(UserInterfaceGetAudioReadyToPlayStatus() == _TRUE)
            {
                UserAdjustAudioMuteSwitch();
            }
            break;

        case _MHL_RCP_RESTORE_VOLUME_FUNCTION:

            SET_OSD_VOLUME(50);

            if(UserInterfaceGetAudioReadyToPlayStatus() == _TRUE)
            {
                UserAdjustAudioVolume(GET_OSD_VOLUME());
            }
            break;
#endif

        default:
            return _FALSE;
            break;
    }

    return _TRUE;
}
#endif // End of #if(_MHL_SUPPORT == _ON)

#if(_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Decide whether to Enable FREESYNC Function
// Input Value  : None
// Output Value : Ture or False
//--------------------------------------------------
bit UserInterfaceGetFREESYNCEnable(void)
{
    if(UserInterfaceGetMultiDisplayMode() == _DISPLAY_MODE_1P)
    {
        return GET_OSD_FREE_SYNC_STATUS();
    }
    else
    {
        return _FALSE;
    }
}
#endif

#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get DP Version
// Input Value  : RCP Key Code
// Output Value : DP_VERSION_1_1 or DP_VERSION_1_2
//--------------------------------------------------
EnumDpVersionType UserInterfaceGetDPVersion(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _D0_INPUT_PORT:

            if(GET_OSD_DP_D0_VERSION() == _DP_VER_1_DOT_1)
            {
                if(GET_OSD_DP_MST() == _MST_D0)
                {
                    SET_OSD_DP_MST(_MST_OFF);
                }

                return _DP_VERSION_1_1;
            }
            else if(GET_OSD_DP_D0_VERSION() == _DP_VER_1_DOT_2)
            {
                return _DP_VERSION_1_2;
            }
            else if(GET_OSD_DP_D0_VERSION() == _DP_VER_1_DOT_3)
            {
                return _DP_VERSION_1_3;
            }
            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:

            if(GET_OSD_DP_D1_VERSION() == _DP_VER_1_DOT_1)
            {
                if(GET_OSD_DP_MST() == _MST_D1)
                {
                    SET_OSD_DP_MST(_MST_OFF);
                }

                return _DP_VERSION_1_1;
            }
            else if(GET_OSD_DP_D1_VERSION() == _DP_VER_1_DOT_2)
            {
                return _DP_VERSION_1_2;
            }
            else if(GET_OSD_DP_D1_VERSION() == _DP_VER_1_DOT_3)
            {
                return _DP_VERSION_1_3;
            }
            break;
#endif

#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
        case _D6_INPUT_PORT:

            if(GET_OSD_DP_D6_VERSION() == _DP_VER_1_DOT_1)
            {
                if(GET_OSD_DP_MST() == _MST_D6)
                {
                    SET_OSD_DP_MST(_MST_OFF);
                }

                return _DP_VERSION_1_1;
            }
            else if(GET_OSD_DP_D6_VERSION() == _DP_VER_1_DOT_2)
            {
                return _DP_VERSION_1_2;
            }
            else if(GET_OSD_DP_D6_VERSION() == _DP_VER_1_DOT_3)
            {
                return _DP_VERSION_1_3;
            }
            break;
#endif

#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
        case _D7_INPUT_PORT:

            return _DP_VERSION_1_2;
            break;
#endif

        default:

            break;
    }

    return _DP_VERSION_1_1;
}

//--------------------------------------------------
// Description  : Get DP Lane Count
// Input Value  : InputPort
// Output Value : DP Lane Count
//--------------------------------------------------
EnumDpLaneCount UserInterfaceGetDpLaneCount(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        case _D0_INPUT_PORT:

            return UserCommonNVRamGetSystemData(_DP_D0_LANES);

#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        case _D1_INPUT_PORT:

            return UserCommonNVRamGetSystemData(_DP_D1_LANES);

#endif

#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
        case _D6_INPUT_PORT:

            return UserCommonNVRamGetSystemData(_DP_D6_LANES);

#endif

#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
        case _D7_INPUT_PORT:

            return _DP_LINK_4_LANE;

#endif

        default:

            break;
    }

    return _DP_LINK_4_LANE;
}

//--------------------------------------------------
// Description  : Get Dp MST Capable Port
// Input Value  : None
// Output Value : _DP_MST_RX0 or _DP_MST_RX1
//--------------------------------------------------
EnumDPMSTPort UserInterfaceGetDpMSTCapablePort(void)
{
#if(_DP_MST_SUPPORT == _OFF)

    return _DP_MST_NO_PORT;

#endif

    if(GET_OSD_DISPLAY_MODE() != _OSD_DM_1P)
    {
        return _DP_MST_NO_PORT;
    }

    if((SysSourceGetScanType() == _SOURCE_SWITCH_FIXED_PORT) && (GET_PORT_TYPE(SysSourceGetInputPortType(SysSourceGetInputPort())) == _PORT_DP))
    {
#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_MST_PORT_SUPPORT == _ON))
        if((GET_OSD_DP_MST() == _MST_D0) && (SysSourceGetInputPort() == _D0_INPUT_PORT))
        {
            if(GET_OSD_DP_D0_VERSION() == _DP_VER_1_DOT_1)
            {
                return _DP_MST_NO_PORT;
            }
            else
            {
                return _DP_MST_RX0_PORT;
            }
        }
        else
#endif

#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_MST_PORT_SUPPORT == _ON))
        if((GET_OSD_DP_MST() == _MST_D1) && (SysSourceGetInputPort() == _D1_INPUT_PORT))
        {
            if(GET_OSD_DP_D1_VERSION() == _DP_VER_1_DOT_1)
            {
                return _DP_MST_NO_PORT;
            }
            else
            {
                return _DP_MST_RX1_PORT;
            }
        }
        else
#endif

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) &&\
    ((_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0) && (_D0_DP_MST_PORT_SUPPORT == _ON)))
        if((GET_OSD_DP_MST() == _MST_D6) && (SysSourceGetInputPort() == _D6_INPUT_PORT))
        {
            if(GET_OSD_DP_D6_VERSION() == _DP_VER_1_DOT_1)
            {
                return _DP_MST_NO_PORT;
            }
            else
            {
                return _DP_MST_RX6_PORT;
            }
        }
        else
#endif

#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
        if(SysSourceGetInputPort() == _D7_INPUT_PORT)
        {
            return _DP_MST_NO_PORT;
        }
        else
#endif
        {
            return _DP_MST_NO_PORT;
        }
    }

    return _DP_MST_NO_PORT;
}

#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Decide whether to Clone output to DP Tx
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserInterfaceGetDpCloneOutputStatus(void)
{
    if(GET_OSD_DISPLAY_MODE() == _OSD_DM_1P)
    {
        if(GET_OSD_CLONE_MODE_1P() == _OSD_CLONE_1P_OFF)
        {
            return _FALSE;
        }
    }
    else
    {
        if(GET_OSD_CLONE_MODE_MTP() == _OSD_CLONE_MTP_OFF)
        {
            return _FALSE;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Get Dp Clone Setting by User
// Input Value  : None
// Output Value : Input Port
//--------------------------------------------------
EnumSourceSearchPort UserInterfaceGetDpCloneOutputUserInputPort(void)
{
    return (GET_OSD_CLONE_MODE_MTP() == _OSD_CLONE_MTP_OFF) ? _NO_INPUT_PORT : (GET_OSD_CLONE_MODE_MTP() - 1);
}
#endif

#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
//--------------------------------------------------
// Description  : User Select Externel DP Switch
// Input Value  : None
// Output Value : Only Return _D0_INPUT_PORT or _D6_INPUT_PORT
//--------------------------------------------------
BYTE UserInterfaceGetDpSwitchSelectPort(void)
{
    return _D0_INPUT_PORT;
}
#endif

#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
//--------------------------------------------------
// Description  : User Using D7 Dp Dual Port as Default Port
// Input Value  : None
// Output Value : _TRUE -> Default D7 DP Port ; _FALSE -> D0/D1 DP Port
//--------------------------------------------------
bit UserInterfaceGetDpDualDefaultPort(void)
{
    return _FALSE;
}
#endif

#endif // End of #if(_DP_SUPPORT == _ON)

#if(_AUDIO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Determine whether to User is Ready to play audio
// Input Value  : None
// Output Value : _TRUE => Free to Play
//--------------------------------------------------
bit UserInterfaceGetAudioReadyToPlayStatus(void)
{
    EnumDisplayRegion enumAudioPlayRegion = UserInterfaceGetAudioDisplayModeRegion();

    if(UserInterfaceGetAudioMuteStatus() != _ON)
    {
#if(_EMBEDDED_DAC_SUPPORT == _ON)
        if(ScalerAudioDACGetState() == _AUDIO_DAC_READY)
#endif
        {
#if(_LINE_IN_SUPPORT == _ON)
            if(UserInterfaceGetAudioSource() == _LINE_IN_AUDIO)
            {
#if(_SLEEP_AUDIO_SUPPORT == _ON)
                if(UserInterfaceGetAudioStandAloneStatus() == _TRUE)
                {
#if((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_LINE_IN))
                    return _TRUE;
#endif
                }
#endif

                if((SysRegionGetDisplayStateCount(_DISPLAY_STATE_ACTIVE) != 0) ||
                   ((SysModeGetModeState() == _MODE_STATUS_DISPLAY_SETTING) && (SysAudioGetAudioState() == _AUDIO_STATUS_PLAYBACK)))
                {
                    return _TRUE;
                }
            }
            else
#endif
            {
                if(UserInterfaceGetAudioSource() == _DIGITAL_AUDIO)
                {
                    if(ScalerAudioGetAudioDetected(SysRegionGetPortType(enumAudioPlayRegion)) == _TRUE)
                    {
#if(_SLEEP_AUDIO_SUPPORT == _ON)
                        if(UserInterfaceGetAudioStandAloneStatus() == _TRUE)
                        {
#if((_DP_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))
                            if((SysModeGetDisplayMode() == _DISPLAY_MODE_1P) &&
                               (ScalerAudioGetDigitalAudioSource(SysRegionGetPortType(enumAudioPlayRegion)) == _DIGITAL_AUDIO_SOURCE_DP))
                            {
                                // When Fixed Port, should not play DP Audio at different port
                                if((SysSourceGetScanType() != _SOURCE_SWITCH_FIXED_PORT) || (SysSourceGetAudioPlaybackPort() == SysRegionGetPortType(enumAudioPlayRegion)))
                                {
                                    return _TRUE;
                                }
                            }
#endif
                        }
#endif
                        if((SysRegionGetDisplayState(enumAudioPlayRegion) == _DISPLAY_STATE_ACTIVE) || (SysAudioGetAudioState() == _AUDIO_STATUS_PLAYBACK))
                        {
                            return _TRUE;
                        }
                    }
                }
            }
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get Current Audio Mute Status
// Input Value  : Node
// Output Value : Node
//--------------------------------------------------
bit UserInterfaceGetAudioMuteStatus(void)
{
    return GET_OSD_VOLUME_MUTE();
}

//--------------------------------------------------
// Description  : User OSD Get Audio Source
// Input Value  : None
// Output Value : _DIGITAL_AUDIO or _LINE_IN_AUDIO
//--------------------------------------------------
EnumAudioInputSource UserInterfaceGetAudioSource(void)
{
#if(_INTERNAL_AUDIO_TEST_SUPPORT == _ON)
    if(ScalerAudioGetInternalAudioGenEnable(SysSourceGetInputPort()) == _ENABLE)
    {
        return _DIGITAL_AUDIO;
    }
#endif

#if((_SLEEP_AUDIO_SUPPORT == _ON) && (_LINE_IN_SUPPORT == _ON) && (_PS_AUDIO_INPUT == _PS_AUDIO_LINE_IN) && (_SWITCH_TO_LINE_IN_AUDIO_IN_POWER_SAVING_MODE == _ON))
    if(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)
    {
        return _LINE_IN_AUDIO;
    }
#endif

#if(_LINE_IN_SUPPORT == _ON)
    if(GET_OSD_AUDIO_SOURCE() == _OSD_AUDIO_SOURCE_ANALOG)
    {
        return _LINE_IN_AUDIO;
    }
#endif

    switch(SysRegionGetPortType(UserInterfaceGetAudioDisplayModeRegion()))
    {
        case _A0_INPUT_PORT:

#if(_D0_INPUT_PORT_TYPE == _D0_DVI_PORT)
        case _D0_INPUT_PORT:
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DVI_PORT)
        case _D1_INPUT_PORT:
#endif

#if((_D2_INPUT_PORT_TYPE == _D2_DVI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
        case _D2_INPUT_PORT:
#endif

#if((_D3_INPUT_PORT_TYPE == _D3_DVI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
        case _D3_INPUT_PORT:
#endif

#if((_D4_INPUT_PORT_TYPE == _D4_DVI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
        case _D4_INPUT_PORT:
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_DVI_PORT)
        case _D5_INPUT_PORT:
#endif

#if(_LINE_IN_SUPPORT == _ON)
            return _LINE_IN_AUDIO;
#else
            return _NO_AUDIO_SOURCE;
#endif
        default:

#if((_SLEEP_AUDIO_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_LINE_IN)))
            // Don't Switch Audio Source if Line In is Currently Playing unless Digital Source is found
            if(UserInterfaceGetAudioStandAloneStatus() == _TRUE)
            {
                if((SysRegionGetSourceType(UserInterfaceGetAudioDisplayModeRegion()) == _SOURCE_NONE) && (SysAudioGetAudioState() == _AUDIO_STATUS_PLAYBACK) && (ScalerAudioGetInputSource() == _LINE_IN_AUDIO))
                {
                    return _LINE_IN_AUDIO;
                }
            }
#endif

            return _DIGITAL_AUDIO;
    }
}

//--------------------------------------------------
// Description  : User Decide whether to play non-LPCM Audio
// Input Value  : None
// Output Value : _ON => Mute Audio
//--------------------------------------------------
bit UserInterfaceGetAudioNonLPCMStatus(void)
{
    EnumDisplayRegion enumAudioPlayRegion = UserInterfaceGetAudioDisplayModeRegion();

    if(ScalerAudioLPCMCheckData(SysRegionGetPortType(enumAudioPlayRegion)) == _TRUE)
    {
#if(_HDMI_SUPPORT == _ON)
        if(SysRegionGetSourceType(enumAudioPlayRegion) == _SOURCE_HDMI)
        {
            if(ScalerAudioLPCMCheckInfo(SysRegionGetPortType(enumAudioPlayRegion)) == _TRUE)
            {
                return _OFF;
            }
            else
            {
                return _ON;
            }
        }
#endif

        return _OFF;
    }

    return _ON;
}

//--------------------------------------------------
// Description  : Get Current Audio Volume
// Input Value  : None
// Output Value : Current Volume
//--------------------------------------------------
WORD UserInterfaceGetAudioVolume(void)
{
    return UserAdjustAudioVolumeMapping(GET_OSD_VOLUME());
}

#if(_EMBEDDED_DAC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get DAC Output Switch
// Input Value  : None
// Output Value : EnumAudioDACOutput
//--------------------------------------------------
EnumAudioDACOutput UserInterfaceGetAudioDACOutput(void)
{
    return _AUDIO_DAC_OUTPUT_BOTH;
}

//--------------------------------------------------
// Description  : Get if Keep Audio Depop State
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit UserInterfaceGetAudioDACKeepDepopState(void)
{
    return _FALSE;
}
#endif

#if(_SLEEP_AUDIO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Current Audio Stand Alone Status
// Input Value  : enumPowStatus
// Output Value : Node
//--------------------------------------------------
bit UserInterfaceGetAudioStandAloneStatus(void)
{
    return GET_OSD_AUDIO_STAND_ALONE();
}
#endif

//--------------------------------------------------
// Description  : User Audio Reset Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustAudioResetProc(void)
{
#if(_SLEEP_AUDIO_SUPPORT == _ON)
    if(UserInterfaceGetAudioStandAloneStatus() == _TRUE)
    {
        // if Currently playing digital audio
        if((SysAudioGetAudioState() == _AUDIO_STATUS_PLAYBACK) && (UserInterfaceGetAudioSource() == _DIGITAL_AUDIO))
        {
#if((_DP_SUPPORT == _ON) && ((_PS_AUDIO_INPUT == _PS_AUDIO_BOTH) || (_PS_AUDIO_INPUT == _PS_AUDIO_DP)))
            if(SysSourceGetAudioPlaybackPort() != SysRegionGetPortType(UserInterfaceGetAudioDisplayModeRegion()))
#endif
            {
                DebugMessageAudio("User Audio Reset Process", 0x00);

                SysAudioMuteProc(_ON);
                ScalerAudioWatchDogProc(_OFF, ScalerAudioGetDigitalAudioPortMapping());

                SysAudioChangeAudioState(_AUDIO_STATUS_PREPARING);
            }
        }
    }
    else
#endif
    {
        if(SysAudioGetAudioState() == _AUDIO_STATUS_PLAYBACK)
        {
            DebugMessageAudio("User Audio Reset Process", 0x00);

            SysAudioMuteProc(_ON);
            ScalerAudioWatchDogProc(_OFF, ScalerAudioGetDigitalAudioPortMapping());

            SysAudioChangeAudioState(_AUDIO_STATUS_PREPARING);
        }
    }
}



//--------------------------------------------------
// Description  : Audio Power Process
// Input Value  : enumPowStatus
// Output Value : Node
//--------------------------------------------------
void UserInterfaceAdjustAudioPowerProc(EnumPowerStatus enumPowStatus)
{
    if(enumPowStatus == _POWER_STATUS_NORMAL)
    {
        // Add User interface function

    }
    else if(enumPowStatus == _POWER_STATUS_SAVING)
    {
        // Add User interface function
    }
    else
    {
        // Add User interface function
    }
}

//--------------------------------------------------
// Description  : Control User Audio Mute Process
// Input Value  : bMute
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustAudioAmpMuteProc(bit bMute)
{
    bMute = bMute;

#if(_EMBEDDED_DAC_SUPPORT == _ON)
    if(UserInterfaceGetAudioDACOutput() == _AUDIO_DAC_OUTPUT_BOTH)
    {
        PCB_AMP_MUTE(bMute);
    }
#endif
}

//--------------------------------------------------
// Description  : Get Audio Digital Mode Region By User
// Input Value  : None
// Output Value : Dispaly Region
//--------------------------------------------------
EnumDisplayRegion UserInterfaceGetAudioDisplayModeRegion(void)
{
    BYTE ucTempAudioSource = 0;
    if(GET_OSD_AUDIO_SOURCE() == _OSD_AUDIO_SOURCE_ANALOG)
    {
        return _DISPLAY_RGN_NONE;
    }
    else
    {
        // Sync Audio Source Region Index with Display Region Index
        ucTempAudioSource = GET_OSD_AUDIO_SOURCE() - _OSD_AUDIO_SOURCE_DIGITAL_REGION_1;

        switch(GET_OSD_DISPLAY_MODE())
        {
            case _OSD_DM_4P:

                return (ucTempAudioSource | _DISPLAY_MODE_4P);

            case _OSD_DM_2P_PIP:

                return (ucTempAudioSource | _DISPLAY_MODE_PIP);

            case _OSD_DM_2P_TB:

                return (ucTempAudioSource | _DISPLAY_MODE_PBP_TB);

            case _OSD_DM_2P_LR:

                return (ucTempAudioSource | _DISPLAY_MODE_PBP_LR);

            case _OSD_DM_1P:
            default:

                return _DISPLAY_RGN_1P;
        }
    }
}

//--------------------------------------------------
// Description  : Get Audio Digital Mode Region Index By User
// Input Value  : None
// Output Value : _REGION_INDEX_x
//--------------------------------------------------
EnumRegionIndex UserInterfaceGetAudioRegionIndex(void)
{
    switch(GET_OSD_AUDIO_SOURCE())
    {
        case _OSD_AUDIO_SOURCE_DIGITAL_REGION_2:

            return _REGION_INDEX_1;

        case _OSD_AUDIO_SOURCE_DIGITAL_REGION_3:

            return _REGION_INDEX_2;

        case _OSD_AUDIO_SOURCE_DIGITAL_REGION_4:

            return _REGION_INDEX_3;

        case _OSD_AUDIO_SOURCE_ANALOG:
        case _OSD_AUDIO_SOURCE_DIGITAL_REGION_1:
        default:
            return _REGION_INDEX_0;
    }
}

#if((_LINE_IN_SUPPORT == _ON) && (_HW_AUDIO_LINE_IN_TO_DIGITAL_LR_SWAP == _ON))
//--------------------------------------------------
// Description  : Swap External Audio Codec Input for Line in
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void UserInterfaceSwapExternalAudioCodecInput(bit bSwap)
{
    if(bSwap == _TRUE)
    {
        // Swap External Audio Codec Input(L/R)
    }
    else
    {
        // No Swap External Audio Codec Input(L/R)
    }
}
#endif
#endif // End of #if(_AUDIO_SUPPORT == _ON)

#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON) || (_UNIFORMITY_SUPPORT == _ON))
//--------------------------------------------------
// Description  : User function Before Calibration Start
// Input Value  : EnumCaliType
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustBeforeDisplayCalibration(EnumCaliType enumMode)
{
    if(enumMode == _UNIFORMITY_CAL)// for Uniformity
    {
        UserAdjustBacklight(GET_OSD_BACKLIGHT());
    }
    else // OGC/OCC/DICOM
    {
    }
}

//--------------------------------------------------
// Description  : User function After Calibration Start
// Input Value  : EnumCaliType
// Output Value : None
//--------------------------------------------------
void UserInterfaceAdjustAfterDisplayCalibration(EnumCaliType enumMode)
{
    if(enumMode == _UNIFORMITY_CAL)// for Uniformity
    {
        UserAdjustBacklight(GET_OSD_BACKLIGHT());
    }
    else // OGC/OCC/DICOM
    {
    }
}
#endif

#endif // End of #if(_OSD_TYPE == _REALTEK_2014_OSD)
