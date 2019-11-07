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
// ID Code      : RTD2014UserAdjustOutputGamma.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_ADJUST_OUTPUT_GAMMA__

#include "UserCommonInclude.h"

#if((_OSD_TYPE == _REALTEK_2014_OSD) && (_GAMMA_FUNCTION == _ON))

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************
#if(_OGC_SUPPORT == _ON)
WORD code tGAMMA_OSD_INDEX[] =
{
#if(_OGC_SUPPORT == _ON)
    _OGC_GAMMA1_ADDRESS,
#if(_OGC_TOTAL_GAMMA > 1)
    _OGC_GAMMA2_ADDRESS,
#if(_OGC_TOTAL_GAMMA > 2)
    _OGC_GAMMA3_ADDRESS,
#if(_OGC_TOTAL_GAMMA > 3)
    _OGC_GAMMA4_ADDRESS,
#if(_OGC_TOTAL_GAMMA > 4)
    _OGC_GAMMA5_ADDRESS,
#endif
#endif
#endif
#endif
#endif
};
#endif  // End of #if(_OGC_SUPPORT == _ON)


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_GAMMA_FUNCTION == _ON)
void UserAdjustGamma(EnumSelRegion enumSelRegion, BYTE ucGamma);
void UserAdjustGammaRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn);
#endif
//-------------------------------------------------------
// PCM
//-------------------------------------------------------
#if(_PCM_FUNCTION == _ON)
void UserAdjustPCM(EnumSelRegion enumSelRegion, BYTE ucPCM);
#endif

//-------------------------------------------------------
// HDR
//-------------------------------------------------------
#if(_ULTRA_HDR_SUPPORT == _ON)
void UserAdjustHDR2084(EnumDisplayRegion enumDisplayRegion, EnumHDRMaxMasteringLvType enumHDRMaxMasteringLvType, EnumHDRColorMatrix enumHDRColorMatrix, bit bDarkEnhanceEnable);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_GAMMA_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Adjust Gamma
// Input Value  : Gamma type
// Output Value : None
//--------------------------------------------------
void UserAdjustGamma(EnumSelRegion enumSelRegion, BYTE ucGamma)
{
    EnumSelRegion enumGammaSelRegion = enumSelRegion;

#if((_PCM_FUNCTION == _ON) && (_PCM_TABLE_TYPE == _PCM_GEN_0))
    enumGammaSelRegion = ScalerColorPCMCheckPCMRegion(enumSelRegion);
#endif

    if(ucGamma != _GAMMA_OFF)
    {
#if(_OGC_SUPPORT == _ON)
        ScalerColorOutputGammaAdjust(enumGammaSelRegion, g_pucDISP_CALIBRATION_FLASH + tGAMMA_OSD_INDEX[ucGamma - 1], _OGC_FLASH_BANK);
        RTDNVRamLoadColorSetting(UserAdjustGetOSDSelectRegion(enumSelRegion));

#if(_CONTRAST_SUPPORT == _ON)
        UserAdjustContrast(enumSelRegion, GET_OSD_CONTRAST(UserAdjustGetOSDSelectRegion(enumSelRegion)));
#endif

#else
        ScalerColorOutputGammaAdjust(enumGammaSelRegion, tGAMMA_TABLE[ucGamma - 1], GET_CURRENT_BANK_NUMBER());

#if(_RGB_GAMMA_FUNCTION == _ON)
        UserAdjustRGBGamma(enumGammaSelRegion, ucGamma);
#endif

#endif // End of #if(_OGC_SUPPORT == _ON)
    }
}

//--------------------------------------------------
// Description  : Set Output Gamma Enable Region
// Input Value  : SelRegion and EnumDBApply, and _ON/_OFF
// Output Value : None
//--------------------------------------------------
void UserAdjustGammaRegionEnable(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply, bit bOn)
{
#if((_PCM_FUNCTION == _ON) && (_PCM_TABLE_TYPE == _PCM_GEN_0))
    if(ScalerColorPCMGetStatus() != _HLW_ALL_BYPASS)
    {
        ScalerColorPCMGammaRegionEnable(enumDBApply, bOn);
    }
    else
#endif
    {
        ScalerColorGammaRegionEnable(enumSelRegion, enumDBApply, bOn);
    }
}

#endif // End of #if(_GAMMA_FUNCTION == _ON)

#if(_PCM_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Adjust PCM
// Input Value  : ucPCM
// Output Value : None
//--------------------------------------------------
void UserAdjustPCM(EnumSelRegion enumSelRegion, BYTE ucPCM)
{
    BYTE *pucGammaTableArray;
    BYTE *pucInverseGammaTableArray;
    BYTE ucGammaBankNum = 0;
    EnumSelRegion enumSelRegionInverse = ScalerRegionGetInverse(enumSelRegion);

#if(_GLOBAL_HUE_SATURATION == _ON)
    ScalerColorPCMSetHueSat(_DEFAULT_HUE - GET_OSD_HUE(UserAdjustGetOSDSelectRegion(enumSelRegion)), _DEFAULT_HUE - GET_OSD_HUE(UserAdjustGetOSDSelectRegion(enumSelRegionInverse)), GET_OSD_SATURATION(UserAdjustGetOSDSelectRegion(enumSelRegion)), GET_OSD_SATURATION(UserAdjustGetOSDSelectRegion(enumSelRegionInverse)));
#endif

    if(GET_OSD_GAMMA(UserAdjustGetOSDSelectRegion(enumSelRegion)) == _GAMMA_OFF)
    {
        pucGammaTableArray = _NULL_POINTER;
    }
    else
    {
#if(_OGC_SUPPORT == _ON)
        pucGammaTableArray = g_pucDISP_CALIBRATION_FLASH + tGAMMA_OSD_INDEX[GET_OSD_GAMMA(UserAdjustGetOSDSelectRegion(enumSelRegion)) - 1];
#else
        pucGammaTableArray = tGAMMA_TABLE[GET_OSD_GAMMA(UserAdjustGetOSDSelectRegion(enumSelRegion)) - 1];
#endif
    }

    if(GET_OSD_GAMMA(UserAdjustGetOSDSelectRegion(enumSelRegionInverse)) == _GAMMA_OFF)
    {
        pucInverseGammaTableArray = _NULL_POINTER;
    }
    else
    {
#if(_OGC_SUPPORT == _ON)
        pucInverseGammaTableArray = g_pucDISP_CALIBRATION_FLASH + tGAMMA_OSD_INDEX[GET_OSD_GAMMA(UserAdjustGetOSDSelectRegion(enumSelRegionInverse)) - 1];
#else
        pucInverseGammaTableArray = tGAMMA_TABLE[GET_OSD_GAMMA(UserAdjustGetOSDSelectRegion(enumSelRegionInverse)) - 1];
#endif
    }


#if(_OGC_SUPPORT == _ON)
    ucGammaBankNum = _OGC_FLASH_BANK;
#else
    ucGammaBankNum =  GET_CURRENT_BANK_NUMBER();
#endif

    if(ucPCM == _PCM_OSD_NATIVE)
    {
        ScalerColorPCMOff(enumSelRegion, pucGammaTableArray, pucInverseGammaTableArray, ucGammaBankNum);
    }
    else
    {
#if(_OCC_SUPPORT == _ON)
        if(ucPCM == _PCM_OSD_SRGB)
        {
            ScalerColorPCMAdjust(enumSelRegion, _PCM_SRGB, _NULL_POINTER, g_pucDISP_CALIBRATION_FLASH + _OCC_GAMMA10_ADDRESS, g_pucDISP_CALIBRATION_FLASH + _OCC_SRGBMATRIX_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE, pucInverseGammaTableArray, ucGammaBankNum);
        }
        else if(ucPCM == _PCM_OSD_ADOBE_RGB)
        {
            ScalerColorPCMAdjust(enumSelRegion, _PCM_ADOBE_RGB, _NULL_POINTER, g_pucDISP_CALIBRATION_FLASH + _OCC_GAMMA10_ADDRESS, g_pucDISP_CALIBRATION_FLASH + _OCC_ADOBEMATRIX_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE, pucInverseGammaTableArray, ucGammaBankNum);
        }
#if(_RGB_3D_GAMMA == _ON)
        else if(ucPCM == _PCM_OSD_SOFT_PROFT)
        {
            ScalerColorPCMAdjust(enumSelRegion, _PCM_SOFT_PROFT, _NULL_POINTER, g_pucDISP_CALIBRATION_FLASH + _OCC_GAMMA10_ADDRESS, g_pucDISP_CALIBRATION_FLASH + _OCC_SOFTPROOF_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE, pucInverseGammaTableArray, ucGammaBankNum);
        }
#endif // End of #if(_RGB_3D_GAMMA == _ON)

        else
#endif
        {
            ScalerColorPCMAdjust(enumSelRegion, _PCM_USER_MODE, tPCM_USER_TABLE[(ucPCM - _PCM_OSD_USER) * 3], tPCM_USER_TABLE[((ucPCM - _PCM_OSD_USER) * 3) + 1], tPCM_USER_TABLE[((ucPCM - _PCM_OSD_USER) * 3) + 2], GET_CURRENT_BANK_NUMBER(), _OCC_COLORMATRIX_TABLE_SIZE, pucInverseGammaTableArray, ucGammaBankNum);
        }
    }
}
#endif  // End of #if(_PCM_FUNCTION == _ON)

#if(_ULTRA_HDR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Adjust HDR 2084 force mode
// Input Value  : EnumDisplayRegion, EnumHDRMaxMasteringLvType, EnumHDRColorMatrix, bDarkEnhanceEnable
// Output Value : None
//--------------------------------------------------
void UserAdjustHDR2084(EnumDisplayRegion enumDisplayRegion, EnumHDRMaxMasteringLvType enumHDRMaxMasteringLvType, EnumHDRColorMatrix enumHDRColorMatrix, bit bDarkEnhanceEnable)
{
    WORD usHDRInputGammaFlashAddress = 0x0000;
    WORD usHDRColorMatrixFlashAddress = 0x0000;

    if(enumDisplayRegion < _DISPLAY_RGN_LT)//only support 1P/2P
    {
        // Input Gamma Setting
        switch(enumHDRMaxMasteringLvType)
        {
            case _HDR_MAX_MASTERING_LV_TYPE0:
                usHDRInputGammaFlashAddress = _OGC_HDR_IG_1200_NOR_ADDRESS;
                break;

            case _HDR_MAX_MASTERING_LV_TYPE1:
                usHDRInputGammaFlashAddress = _OGC_HDR_IG_4000_NOR_ADDRESS;
                break;

            case _HDR_MAX_MASTERING_LV_TYPE2:
                usHDRInputGammaFlashAddress = _OGC_HDR_IG_10000_NOR_ADDRESS;
                break;

            default:
                usHDRInputGammaFlashAddress = _OGC_HDR_IG_1200_NOR_ADDRESS;
                break;
        }

        if(bDarkEnhanceEnable == _ON)
        {
            usHDRInputGammaFlashAddress += _OGC_HDR_IG_TABLE_SIZE;
        }

        // Color Matrix Setting
        switch(enumHDRColorMatrix)
        {
            case _HDR_COLOR_MATRIX_SRGB:
                usHDRColorMatrixFlashAddress = _OCC_HDR_SRGB_MATRIX_ADDRESS;
                break;

            case _HDR_COLOR_MATRIX_ADOBE:
                usHDRColorMatrixFlashAddress = _OCC_HDR_ADOBE_MATRIX_ADDRESS;
                break;

            case _HDR_COLOR_MATRIX_DCIP3_D65:
                usHDRColorMatrixFlashAddress = _OCC_HDR_DCIP3_D65_MATRIX_ADDRESS;
                break;

            case _HDR_COLOR_MATRIX_BT2020:
                usHDRColorMatrixFlashAddress = _OCC_HDR_BT2020_MATRIX_ADDRESS;
                break;

            default:
                usHDRColorMatrixFlashAddress = _OCC_HDR_BT2020_MATRIX_ADDRESS;
                break;
        }

#if((_CONTRAST_SUPPORT == _ON) || (_BRIGHTNESS_SUPPORT == _ON))
        ScalerColorBRICTSRegionEnable((EnumSelRegion)enumDisplayRegion, _DB_APPLY_NONE, _OFF);
#endif

#if(_RGB_3D_GAMMA == _ON)
        ScalerColor3DGammaRegionEnable((EnumSelRegion)enumDisplayRegion, _DB_APPLY_NONE, _OFF);
#endif

        ScalerColorPCMAdjust((EnumSelRegion)enumDisplayRegion, _PCM_HDR_2084,
                             (g_pucDISP_CALIBRATION_FLASH + usHDRInputGammaFlashAddress),
                             (g_pucDISP_CALIBRATION_FLASH + _OCC_HDR_GAMMA10_ADDRESS),
                             (g_pucDISP_CALIBRATION_FLASH + usHDRColorMatrixFlashAddress),
                             _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE, _NULL_POINTER, _OGC_FLASH_BANK);
    }
}
#endif

#endif // End of #if((_OSD_TYPE == _REALTEK_2014_OSD) && (_GAMMA_FUNCTION == _ON))
