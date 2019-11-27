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
#include "ScalerColorLibInternalInclude.h"
#include <stdio.h>

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
#if 0//#if(COMPRESS_GAMMA == _ON)  // alant
void delta_decode(uint8_t buffer[1024], uint8_t buf_out[2052], uint16_t length)
{
	uint16_t last = 0;
	uint16_t i =0 , k =0 ;
	
	for (i = 0; i < length; i++)
	{
		//int delta = buffer[i];
		buf_out[k] = (buffer[i] + last)>>8;
		buf_out[k+1] = (buffer[i] + last) & 0xFF;
		last = buffer[i]+last;
		k+=2 ;
	}

	buf_out[2042] = buf_out[2040];
	buf_out[2043] = buf_out[2041];


	buf_out[2044] = buf_out[2040];
	buf_out[2045] = buf_out[2041];


	buf_out[2046] = buf_out[2040];
	buf_out[2047] = buf_out[2041];


	buf_out[2048] = buf_out[2040];
	buf_out[2049] = buf_out[2041];


	buf_out[2050] = 0;
	buf_out[2051] = 0;

}
#endif

bit  check_checksum(BYTE idx , BYTE buf[] , int len)
{
	
	 WORD i =0;
	 BYTE crc= 0;
	 BYTE buf_out=0 ;
	
	 for(i=0 ; i< len ; i++)
	 {
		crc+=buf[i] ;
	 }
	
	RTDEepromLoadGammaCRC(idx, &buf_out);
	
	if(buf_out == crc) return 1 ;

	printf("CRC fail .......\r\n");
	return 0;


}
/*
void NewScalerColorOutputGammaChannelCtrl(BYTE ucColorChannel, WORD usOffset, bit bLocation)
{
    // Select Channel
    ScalerSetBit(P0_67_GAMMA_CTRL_SETA, ~(_BIT7 | _BIT5 | _BIT4 | _BIT2), ((ucColorChannel << 4) | ((BYTE)bLocation << 2)));

    // Specify address
    ScalerSetBit(P0_67_GAMMA_CTRL_SETA, ~_BIT3, _BIT3);
    ScalerSetByte(P0_66_GAMMA_PORT_SETA, HIBYTE(usOffset));
    ScalerSetByte(P0_66_GAMMA_PORT_SETA, LOBYTE(usOffset));
    ScalerSetBit(P0_67_GAMMA_CTRL_SETA, ~(_BIT7 | _BIT3), _BIT7);
}
*/
void NewScalerColorOutputGammaAdjust(EnumSelRegion enumSelRegion, BYTE ucGamma, BYTE ucBankNum)
{
#if 0//#if(COMPRESS_GAMMA == _ON)	
	BYTE pucGammaTableArray[2052] ;
	BYTE  pgamma[1024] ;
    //int i =0;
	WORD usPage = ScalerRegionGetRegisterPage(_REG_DDOMAIN_AFTER_BLENDING, enumSelRegion);
	

    if(ScalerGetBit(P0_67_GAMMA_CTRL_SETA, _BIT6) == _BIT6) // Gamma On
    {
        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
        ScalerColorOutputGammaEnable(_FUNCTION_OFF);

        // Load gamma table of R Channel
        //----------------------------
        memset(pucGammaTableArray ,0 , sizeof(pucGammaTableArray));
        memset(pgamma ,0 , sizeof(pgamma));

	
		RTDNVRamLoadGammaModeData(ucGamma , 0 ,pgamma );
		delta_decode(pgamma, pucGammaTableArray, 1024);


		ScalerColorOutputGammaChannelCtrl(usPage,_GAMMA_RED_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
        //ScalerBurstWrite(pucGammaTableArray, _GAMMA_TABLE_SIZE, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
		// Write Gamma LUT
		ScalerWrite(P0_66_GAMMA_PORT_SETA, _GAMMA_TABLE_SIZE, pucGammaTableArray, _NON_AUTOINC);

        // Load gamma table of G Channel
        //------------------------------------
        memset(pucGammaTableArray ,0 , sizeof(pucGammaTableArray));
        memset(pgamma ,0 , sizeof(pgamma));
		
        RTDNVRamLoadGammaModeData(ucGamma , 1 ,pucGammaTableArray );		
		delta_decode(pgamma, pucGammaTableArray, 1024);
		
		  
        ScalerColorOutputGammaChannelCtrl(usPage,_GAMMA_GREEN_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
        //ScalerBurstWrite(pucGammaTableArray, _GAMMA_TABLE_SIZE, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
	    // Write Gamma LUT
		ScalerWrite(P0_66_GAMMA_PORT_SETA, _GAMMA_TABLE_SIZE, pucGammaTableArray, _NON_AUTOINC);

        // Load gamma table of B Channel
        //-------------------
        memset(pucGammaTableArray ,0 , sizeof(pucGammaTableArray));
        memset(pgamma ,0 , sizeof(pgamma));

        RTDNVRamLoadGammaModeData(ucGamma , 2 ,pucGammaTableArray );
		delta_decode(pgamma, pucGammaTableArray, 1024);

		  
        ScalerColorOutputGammaChannelCtrl(usPage,_GAMMA_BLUE_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
        //ScalerBurstWrite(pucGammaTableArray, _GAMMA_TABLE_SIZE, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

		// Write Gamma LUT
		ScalerWrite(P0_66_GAMMA_PORT_SETA, _GAMMA_TABLE_SIZE, pucGammaTableArray, _NON_AUTOINC);

        // Disable Port Access
        ScalerSetBit(P0_67_GAMMA_CTRL_SETA, ~_BIT7, 0x00);

        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
        ScalerColorOutputGammaEnable(_FUNCTION_ON);
    }
    else
    {
#if 0    
        // Load gamma table of R Channel
        ScalerColorOutputGammaChannelCtrl(_GAMMA_RED_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
        ScalerBurstWrite(pucGammaTableArray, _GAMMA_TABLE_SIZE, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

        // Load gamma table of G Channel
        ScalerColorOutputGammaChannelCtrl(_GAMMA_GREEN_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
        ScalerBurstWrite(pucGammaTableArray + _GAMMA_TABLE_SIZE, _GAMMA_TABLE_SIZE, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

        // Load gamma table of B Channel
        ScalerColorOutputGammaChannelCtrl(_GAMMA_BLUE_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
        ScalerBurstWrite(pucGammaTableArray + (_GAMMA_TABLE_SIZE * 2), _GAMMA_TABLE_SIZE, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
#endif
        // Disable Port Access
        ScalerSetBit(P0_67_GAMMA_CTRL_SETA, ~_BIT7, 0x00);
    }
#else // COMPRESS_GAMMA == _OFF

	BYTE pucGammaTableArray[2052] ;

	WORD usPage = ScalerRegionGetRegisterPage(_REG_DDOMAIN_AFTER_BLENDING, enumSelRegion);
	ucBankNum = GET_CURRENT_BANK_NUMBER();

    if(ScalerGetBit(P0_67_GAMMA_CTRL_SETA, _BIT6) == _BIT6) // Gamma On
    {
        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
        ScalerColorOutputGammaEnable(_FUNCTION_OFF);

        // Load gamma table of R Channel
        //----------------------------
        memset(pucGammaTableArray ,0 , sizeof(pucGammaTableArray));

		RTDNVRamLoadGammaModeData(ucGamma , 0 ,pucGammaTableArray );
	    //  CRC check R only

		if(!check_checksum(ucGamma,pucGammaTableArray , 2052))
		{
			ScalerColorOutputGammaAdjust(enumSelRegion, tGAMMA_TABLE[ucGamma], ucBankNum);
            return ;
		}
			

		 ScalerColorOutputGammaChannelCtrl(usPage,_GAMMA_RED_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
        //ScalerBurstWrite(pucGammaTableArray, _GAMMA_TABLE_SIZE, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
		// Write Gamma LUT
		ScalerWrite(P0_66_GAMMA_PORT_SETA, _GAMMA_TABLE_SIZE, pucGammaTableArray, _NON_AUTOINC);

        // Load gamma table of G Channel
        //------------------------------------
        memset(pucGammaTableArray ,0 , sizeof(pucGammaTableArray));
        RTDNVRamLoadGammaModeData(ucGamma , 1 ,pucGammaTableArray );		
		
		  
        ScalerColorOutputGammaChannelCtrl(usPage,_GAMMA_GREEN_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
        //ScalerBurstWrite(pucGammaTableArray, _GAMMA_TABLE_SIZE, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
	    // Write Gamma LUT
		ScalerWrite(P0_66_GAMMA_PORT_SETA, _GAMMA_TABLE_SIZE, pucGammaTableArray, _NON_AUTOINC);

        // Load gamma table of B Channel
        //-------------------
        memset(pucGammaTableArray ,0 , sizeof(pucGammaTableArray));

        RTDNVRamLoadGammaModeData(ucGamma , 2 ,pucGammaTableArray );
	

		  
         ScalerColorOutputGammaChannelCtrl(usPage,_GAMMA_BLUE_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
        //ScalerBurstWrite(pucGammaTableArray, _GAMMA_TABLE_SIZE, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

		// Write Gamma LUT
		ScalerWrite(P0_66_GAMMA_PORT_SETA, _GAMMA_TABLE_SIZE, pucGammaTableArray, _NON_AUTOINC);

        // Disable Port Access
        ScalerSetBit(P0_67_GAMMA_CTRL_SETA, ~_BIT7, 0x00);

        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
        ScalerColorOutputGammaEnable(_FUNCTION_ON);
    }
    else
    {
#if 0    
        // Load gamma table of R Channel
        ScalerColorOutputGammaChannelCtrl(_GAMMA_RED_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
        ScalerBurstWrite(pucGammaTableArray, _GAMMA_TABLE_SIZE, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

        // Load gamma table of G Channel
        ScalerColorOutputGammaChannelCtrl(_GAMMA_GREEN_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
        ScalerBurstWrite(pucGammaTableArray + _GAMMA_TABLE_SIZE, _GAMMA_TABLE_SIZE, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

        // Load gamma table of B Channel
        ScalerColorOutputGammaChannelCtrl(_GAMMA_BLUE_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
        ScalerBurstWrite(pucGammaTableArray + (_GAMMA_TABLE_SIZE * 2), _GAMMA_TABLE_SIZE, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
#endif
        // Disable Port Access
        ScalerSetBit(P0_67_GAMMA_CTRL_SETA, ~_BIT7, 0x00);
    }


	
#endif
}

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
	    UserAdjustBrightness(enumSelRegion, GET_OSD_BRIGHTNESS(UserAdjustGetOSDSelectRegion(enumSelRegion)));
#endif

#else

#if 1 // alant test

    // if(check_checksum(ucGamma-1))
       NewScalerColorOutputGammaAdjust(enumGammaSelRegion, ucGamma-1, GET_CURRENT_BANK_NUMBER());
    //else
//#else
      //  ScalerColorOutputGammaAdjust(enumGammaSelRegion, tGAMMA_TABLE[ucGamma - 1], GET_CURRENT_BANK_NUMBER());
#endif
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
