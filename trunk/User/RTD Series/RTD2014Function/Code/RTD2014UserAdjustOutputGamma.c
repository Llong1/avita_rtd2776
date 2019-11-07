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
//void NewScalerColorOutputGammaAdjust(EnumSelRegion enumSelRegion,BYTE *pucGammaTableArray, BYTE ucBankNum);

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
#if 1  // alant

void uncompress(uint8_t pgamma[320] , uint8_t buf[2052]) // 256*10bit to 1024*14bit
{
	uint16_t i, k, decimal;
	uint16_t Now[8];
	uint32_t Start, End;
	uint32_t idx = 0;
	//uint8_t a, b;
	
	decimal = pgamma[0];
	
	Start = ((pgamma[1] << 2) + (pgamma[0] & 0x03)) << 4;//14 bit --0
	
	for (i = 2; i < 319; i++)//1016
	{
		if ((i % 5) == 0)
		{
			decimal = pgamma[i];//0x3f
			i++;
		
		}
	
		End = ((pgamma[i] << 2) + (decimal & 0x03)) << 4;//14 bit  --0x35c0
		decimal >>= 2;//0x0f

		for (k = 0; k < 4; k++)
		{
			Now[k] = (End * k + (4 - k) * Start) >> 2;//14 bit
			//if(i<=50)
			buf[idx] = Now[k] >> 8;
			buf[idx + 1] = Now[k] & 0x00FF;
			//printf("0x%x , 0x%x \r\n", buf[idx], buf[idx + 1]);
			idx=idx+2;
			//printf("now[k]=0x%x\r\n", buf[idx], buf[idx+1]);
		}
		
		Start = End;

		
	}
	
	End = (((pgamma[319] << 2) + (decimal & 0x03)) << 4) + 0x0F;//14 bit
	
	for (k = 0; k < 8; k++)//8 
	{
		Now[k] = (End * k + (8 - k) * Start) >> 3;//14 bit
		buf[idx] = Now[k] >> 8;
		buf[idx + 1] = Now[k] & 0x00FF;

		idx = idx + 2;
	}

	//printf("idx=%d \r\n",idx);
	Now[7] = End;

//	a= buf[2040];
//	b= buf[2041];
	
	buf[2042] = buf[2040];
	buf[2043] = buf[2041];

	buf[2044] = buf[2040];
	buf[2045] = buf[2041];

	buf[2046] =buf[2040];
	buf[2047] =buf[2041];
	
	buf[2048] = buf[2040];
	buf[2049] = buf[2041];

	buf[2050] = 0;
	buf[2051] = 0;



}

BYTE calucalte_checksum(BYTE buf[] , int len)
{

 BYTE i ;
 BYTE crc ;
 
	  
 for(i=0 ; i<len ; i++ ) 
 {
   crc+=buf[i];
 }
 
 return crc ;

}


bit check_checksum(void)
{

#define CRC_SIZE 8

	  bit ret = _FALSE;
	  BYTE buf_out ;
	  BYTE crc[CRC_SIZE] ;
	
	  UserCommonEepromRead(GAMMA_MODE1_ADDRESS_START, 1, (BYTE *)(&buf_out));
	  UserCommonEepromRead(GAMMA_MODE1_ADDRESS, 8, (BYTE *)(&crc));
     if(buf_out == calucalte_checksum(crc, CRC_SIZE))
	 	ret= _TRUE;
     
	
	  return ret ;
}





#endif
void NewScalerColorOutputGammaAdjust(EnumSelRegion enumSelRegion, BYTE ucGamma, BYTE ucBankNum)
{
	
	BYTE pucGammaTableArray[320] ;
	BYTE  pgamma[2052] ;

	WORD usPage = ScalerRegionGetRegisterPage(_REG_DDOMAIN_AFTER_BLENDING, enumSelRegion);
	

	

    if(ScalerGetBit(P0_67_GAMMA_CTRL_SETA, _BIT6) == _BIT6) // Gamma On
    {
        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
        ScalerColorOutputGammaEnable(_FUNCTION_OFF);

        // Load gamma table of R Channel
        //----------------------------
        memset(pucGammaTableArray ,0 , sizeof(pucGammaTableArray));
        memset(pgamma ,0 , sizeof(pgamma));
	
        RTDEepromLoadGammaModeData(ucGamma , _GAMMA_RED_CHANNEL ,pucGammaTableArray );
	    uncompress(pucGammaTableArray, pgamma);

		ScalerColorOutputGammaChannelCtrl(usPage,_GAMMA_RED_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
        ScalerBurstWrite(pgamma, _GAMMA_TABLE_SIZE, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

        // Load gamma table of G Channel
        //------------------------------------
        memset(pucGammaTableArray ,0 , sizeof(pucGammaTableArray));
        memset(pgamma ,0 , sizeof(pgamma));
		
        RTDEepromLoadGammaModeData(ucGamma , _GAMMA_GREEN_CHANNEL ,pucGammaTableArray );
		uncompress(pucGammaTableArray, pgamma);
		  
        ScalerColorOutputGammaChannelCtrl(usPage,_GAMMA_GREEN_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
        ScalerBurstWrite(pgamma + _GAMMA_TABLE_SIZE, _GAMMA_TABLE_SIZE, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

        // Load gamma table of B Channel
        //-------------------
        memset(pucGammaTableArray ,0 , sizeof(pucGammaTableArray));
        memset(pgamma ,0 , sizeof(pgamma));

        RTDEepromLoadGammaModeData(ucGamma , _GAMMA_BLUE_CHANNEL ,pucGammaTableArray );
		uncompress(pucGammaTableArray, pgamma);
		  
        ScalerColorOutputGammaChannelCtrl(usPage,_GAMMA_BLUE_CHANNEL, 0x0000, _GAMMA_WRITE_TO_SRAM);
        ScalerBurstWrite(pgamma + (_GAMMA_TABLE_SIZE * 2), _GAMMA_TABLE_SIZE, ucBankNum, P0_66_GAMMA_PORT_SETA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

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
#endif

#else

#if 1  // alant test

    	if(check_checksum())// && secure_boot(0))
       NewScalerColorOutputGammaAdjust(enumGammaSelRegion, ucGamma-1, GET_CURRENT_BANK_NUMBER());
      else
      	
	  ScalerColorOutputGammaAdjust(enumGammaSelRegion, tGAMMA_TABLE[ucGamma - 1], GET_CURRENT_BANK_NUMBER());
#else
        ScalerColorOutputGammaAdjust(enumGammaSelRegion, tGAMMA_TABLE[ucGamma - 1], GET_CURRENT_BANK_NUMBER());

#endif
#if 0//#if(_RGB_GAMMA_FUNCTION == _ON)
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
