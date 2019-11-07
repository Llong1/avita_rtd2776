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
// ID Code      : UserCommonDisplayCalibration.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_DISPLAY_CALIBRATION__

#include "UserCommonInclude.h"

#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON) || (_UNIFORMITY_SUPPORT == _ON))
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of OGC/OCC/DICOM
//--------------------------------------------------
#define _OGC_TYPE                   0
#define _OCC_TYPE                   1
#define _DICOM_TYPE                 2
#define _RGB_GAIN_TYPE              3
#define _COLOR_MATRIX_TYPE          4
#define _OGC_RGBGAMMA_TYPE          5
#define _HDR_TYPE                   6
#define _HEADER_TYPE                7

#define _DISP_CALIB_START           0
#define _DISP_CALIB_PASS            1
#define _DISP_CALIB_ERASE_ERROR     2
#define _DISP_CALIB_FW_ERROR        3
#define _DISP_CALIB_CRC_ERROR       4
#define _DISP_CALIB_FAIL            5

#define _BG_PATTERN                 0
#define _PG_PATTERN                 1
#define _PATTERN_TOP                ((_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT) ? 1023 : 1020)

typedef enum
{
#if(_OGC_SUPPORT == _ON)
    _GAMMA1_POSITION,
#if(_OGC_TOTAL_GAMMA > 1)
    _GAMMA2_POSITION,
#if(_OGC_TOTAL_GAMMA > 2)
    _GAMMA3_POSITION,
#if(_OGC_TOTAL_GAMMA > 3)
    _GAMMA4_POSITION,
#if(_OGC_TOTAL_GAMMA > 4)
    _GAMMA5_POSITION,
#endif
#endif
#endif
#endif
#endif

#if(_OCC_SUPPORT == _ON)
    _OCC_POSITION,
#endif
#if(_OGC_DICOM_SUPPORT == _ON)
    _DICOM_POSITION,
#endif
    _NONE_VALUE,
} EnumOGCTypePos;
//--------------------------------------------------
// Definitions of Uniformity
//--------------------------------------------------
#define _UNIFORMITY_GAIN_TYPE       7
#define _UNIFORMITY_OFFSET_TYPE     6
#define _UNIFORMITY_DECAY_TYPE      5

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************

//--------------------------------------------------
// Table of OGC/OCC/DICOM
//--------------------------------------------------
WORD code tOGC_GRAY_TABLE[] =
{
    252 * 4, 244 * 4, 232 * 4,
    216 * 4, 196 * 4, 172 * 4,
    148 * 4, 124 * 4, 96 * 4,
    68 * 4,  44 * 4,  24 * 4,
    12 * 4,  6 * 4,   2 * 4,
    0
};

#if(_OCC_SUPPORT == _ON)
BYTE code tSRGBByPass[] =
{
    0,0,0,0,0,0,
    0,0,0,0,0,0,
    0,0,0,0,0,0
};
//--------------------------------------------------
// sRGB Table for OCC
//--------------------------------------------------
#if(_OCC_LUT_MODE == _OFF)
WORD code tOCC_SRGB_TABLE[] =
{
    192 * 4,  80 * 4,  80 * 4,
    192 * 4, 192 * 4,  80 * 4,
    96 * 4, 192 * 4,  96 * 4,
    96 * 4, 192 * 4, 192 * 4,
    128 * 4, 128 * 4, 192 * 4,
    192 * 4, 128 * 4, 192 * 4,
    1023, 1023, 1023,
};
#else
WORD code tOCC_SRGB_TABLE[] =
{
    1023,0,0,
    0,1023,0,
    0,0,248 * 4,
    1023,1023,0,
    1023,0,248 * 4,
    0,1023,248 * 4,
    1023,1023,1023,

    128 * 4,0,0,
    0,128 * 4,0,
    0,0,128 * 4,
    128 * 4,128 * 4,0,
    128 * 4,0,128 * 4,
    0,128 * 4,128 * 4,
    96 * 4,96 * 4,96 * 4,

    192 * 4,0,0,
    0,192 * 4,0,
    0,0,192 * 4,
    192 * 4,192 * 4,0,
    192 * 4,0,192 * 4,
    0,192 * 4,192 * 4,
    192 * 4,192 * 4,192 * 4
};
#endif
#endif

WORD code tGAMMA_INDEX[] =
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

#if(_OCC_SUPPORT == _ON)
    _OCC_GAMMA10_ADDRESS,
#endif

#if(_OGC_DICOM_SUPPORT == _ON)
    _OGC_DICOM_ADDRESS,
#endif

};

WORD code tHDRIGAMMA_INDEX[] =
{
    _OGC_HDR_IG_1200_NOR_ADDRESS,
    _OGC_HDR_IG_1200_DARK_ADDRESS,
    _OGC_HDR_IG_4000_NOR_ADDRESS,
    _OGC_HDR_IG_4000_DARK_ADDRESS,
    _OGC_HDR_IG_10000_NOR_ADDRESS,
    _OGC_HDR_IG_10000_DARK_ADDRESS,
};

#if(_UNIFORMITY_SUPPORT == _ON)
WORD code tUNIFORMITY_TYPE_ADDRESS_INDEX[] =
{
    _UNIFORMITY_TYPE1_ADDRESS,
    _UNIFORMITY_TYPE2_ADDRESS,
    _UNIFORMITY_TYPE3_ADDRESS,
    _UNIFORMITY_TYPE4_ADDRESS,
    _UNIFORMITY_TYPE5_ADDRESS,
    _UNIFORMITY_TYPE6_ADDRESS,
};

BYTE code tUNIFORMITY_TYPE_BANK_INDEX[] =
{
    _UNIFORMITY_TYPE1_BANK,
    _UNIFORMITY_TYPE2_BANK,
    _UNIFORMITY_TYPE3_BANK,
    _UNIFORMITY_TYPE4_BANK,
    _UNIFORMITY_TYPE5_BANK,
    _UNIFORMITY_TYPE6_BANK,
};

WORD code tUNIFORMITY_TYPE_CHECKSUM_INDEX[] =
{
    _UNIFORMITY_TYPE1_CHKSUM_ADDRESS,
    _UNIFORMITY_TYPE2_CHKSUM_ADDRESS,
    _UNIFORMITY_TYPE3_CHKSUM_ADDRESS,
    _UNIFORMITY_TYPE4_CHKSUM_ADDRESS,
    _UNIFORMITY_TYPE5_CHKSUM_ADDRESS,
    _UNIFORMITY_TYPE6_CHKSUM_ADDRESS,
};

#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
WORD code tUNIFORMITY_TYPE_OFFSET_ADDRESS_INDEX[] =
{
    _UNIFORMITY_TYPE1_OFFSET_ADDRESS,
    _UNIFORMITY_TYPE2_OFFSET_ADDRESS,
    _UNIFORMITY_TYPE3_OFFSET_ADDRESS,
    _UNIFORMITY_TYPE4_OFFSET_ADDRESS,
    _UNIFORMITY_TYPE5_OFFSET_ADDRESS,
    _UNIFORMITY_TYPE6_OFFSET_ADDRESS,
};

BYTE code tUNIFORMITY_TYPE_OFFSET_BANK_INDEX[] =
{
    _UNIFORMITY_TYPE1_OFFSET_BANK,
    _UNIFORMITY_TYPE2_OFFSET_BANK,
    _UNIFORMITY_TYPE3_OFFSET_BANK,
    _UNIFORMITY_TYPE4_OFFSET_BANK,
    _UNIFORMITY_TYPE5_OFFSET_BANK,
    _UNIFORMITY_TYPE6_OFFSET_BANK,
};

WORD code tUNIFORMITY_TYPE_OFFSET_CHECKSUM_INDEX[] =
{
    _UNIFORMITY_TYPE1_OFFSET_CHKSUM_ADDRESS,
    _UNIFORMITY_TYPE2_OFFSET_CHKSUM_ADDRESS,
    _UNIFORMITY_TYPE3_OFFSET_CHKSUM_ADDRESS,
    _UNIFORMITY_TYPE4_OFFSET_CHKSUM_ADDRESS,
    _UNIFORMITY_TYPE5_OFFSET_CHKSUM_ADDRESS,
    _UNIFORMITY_TYPE6_OFFSET_CHKSUM_ADDRESS,
};

WORD code tUNIFORMITY_TYPE_DECAY_ADDRESS_INDEX[] =
{
    _UNIFORMITY_TYPE1_DECAY_ADDRESS,
    _UNIFORMITY_TYPE2_DECAY_ADDRESS,
    _UNIFORMITY_TYPE3_DECAY_ADDRESS,
    _UNIFORMITY_TYPE4_DECAY_ADDRESS,
    _UNIFORMITY_TYPE5_DECAY_ADDRESS,
    _UNIFORMITY_TYPE6_DECAY_ADDRESS,
};

BYTE code tUNIFORMITY_TYPE_DECAY_BANK_INDEX[] =
{
    _UNIFORMITY_TYPE1_DECAY_BANK,
    _UNIFORMITY_TYPE2_DECAY_BANK,
    _UNIFORMITY_TYPE3_DECAY_BANK,
    _UNIFORMITY_TYPE4_DECAY_BANK,
    _UNIFORMITY_TYPE5_DECAY_BANK,
    _UNIFORMITY_TYPE6_DECAY_BANK,
};

WORD code tUNIFORMITY_TYPE_DECAY_CHECKSUM_INDEX[] =
{
    _UNIFORMITY_TYPE1_DECAY_CHKSUM_ADDRESS,
    _UNIFORMITY_TYPE2_DECAY_CHKSUM_ADDRESS,
    _UNIFORMITY_TYPE3_DECAY_CHKSUM_ADDRESS,
    _UNIFORMITY_TYPE4_DECAY_CHKSUM_ADDRESS,
    _UNIFORMITY_TYPE5_DECAY_CHKSUM_ADDRESS,
    _UNIFORMITY_TYPE6_DECAY_CHKSUM_ADDRESS,
};
#endif // #if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
#endif // End of #if(_UNIFORMITY_SUPPORT == _ON)

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE xdata *g_pucDISP_CALIBRATION_FLASH = _OGC_FLASH_PAGE * _FLASH_PAGE_SIZE;

WORD g_pusGammaCount[][3] =
{
#if(_OGC_SUPPORT == _ON)
    {2052, 2052, 2052},
#if(_OGC_TOTAL_GAMMA > 1)
    {2052, 2052, 2052},
#if(_OGC_TOTAL_GAMMA > 2)
    {2052, 2052, 2052},
#if(_OGC_TOTAL_GAMMA > 3)
    {2052, 2052, 2052},
#if(_OGC_TOTAL_GAMMA > 4)
    {2052, 2052, 2052},
#endif
#endif
#endif
#endif
#endif  // End of #if(_OGC_SUPPORT == _ON)

#if(_OCC_SUPPORT == _ON)
    {2200, 2200, 2200},  // To be Edit
#endif

#if(_OGC_DICOM_SUPPORT == _ON)
    {2052, 2052, 2052},
#endif

};

BYTE g_ucCTGainSavePos;
#if(_UNIFORMITY_SUPPORT == _ON)
BYTE g_ucUniformityLUTSaveBank = _UNIFORMITY_FLASH_BANK0;
BYTE g_ucUniformityLUTStartPosIndex = 0x0000;
WORD g_usUniformityLUTSavePos = 0x0000;
#endif
WORD g_usColorMatrixSavePos;

BYTE g_ucCalibrationType;
BYTE g_ucUniformityChecksumType = 0x0000;// level0, CYShih
BYTE g_ucPatternType = _BG_PATTERN;
#if(_ULTRA_HDR_SUPPORT == _ON)
BYTE g_ucIGLUTSavePos;
#endif
//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void UserCommonDdcciDispCalibShowCalibPattern(WORD usRed, WORD usGreen, WORD usBlue);
void UserCommonDdcciDispCalibCalibPatternEnable(bit bEnable);
void UserCommonDdcciDispCalibProcess(void);
bit UserCommonDdcciDispCalibOGCStart(void);

#if(_OCC_SUPPORT == _ON)
BYTE UserCommonDdcciDispCalibOCCProcess(BYTE ucStep);
#endif

bit UserCommonDdcciDispCalibInitialCheck(void);
void UserCommonDdcciDispCalibSaveLUT(BYTE ucTotalLength);
BYTE UserCommonDdcciDispCalibCalCheckSum(BYTE ucCheckType);
void UserCommonDdcciDispCalibShowGamma(void);
BYTE UserCommonDdcciDispCalibCheckSum(void);

BYTE UserCommonDdcciDispCalibMatrixCheckSum(BYTE ucCheckType);

void UserCommonDdcciDispCalibReplyResult(BYTE ucType);
void UserCommonDdcciDispCalibSaveHeader(void);

#if(_UNIFORMITY_SUPPORT == _ON)

void UserCommonDdcciDispCalibReplyOCCMatrix(BYTE ucPCMType);
void UserCommonDdcciDispCalibReplyOGCHeader(void);
void UserCommonDdcciDispCalibReplyUniformityDefine(void);
void UserCommonDdcciDispCalibReplyCCTGain(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Show Calibration Pattern
// Input Value  : WORD usRed, WORD usGreen, WORD usBlue
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciDispCalibShowCalibPattern(WORD usRed, WORD usGreen, WORD usBlue)
{
    if(g_ucPatternType == _PG_PATTERN)
    {
        ScalerDDomainPatternGenAdjustColor10bit(usRed, usGreen, usBlue);
    }
    else
    {
        ScalerDDomainBackgroundSetColor10bit(usRed, usGreen, usBlue);
    }
}
//--------------------------------------------------
// Description  : Calibration Pattern Enable
// Input Value  : bEnable
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciDispCalibCalibPatternEnable(bit bEnable)
{
    if(g_ucPatternType == _PG_PATTERN)
    {
        ScalerDDomainPatternGenEnable(bEnable);
    }
    else
    {
        ScalerDDomainBackgroundEnable(_DISPLAY_PATH_ALL, bEnable);
    }
}
//--------------------------------------------------
// Description  : Do OGC/OCC/DICOM Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciDispCalibProcess(void)
{
    BYTE ucCalibrationStep = 0;
    BYTE ucFlag = 1;
#if((_OGC_SUPPORT == _ON) || (_UNIFORMITY_SUPPORT == _ON))
    BYTE ucGammaIndex = 0;
#endif

#if(_OGC_SUPPORT == _ON)
    BYTE ucColorTempIndex = 0;
    WORD pusBriTemp[3] = {0x200, 0x200, 0x200};
#endif

    WORD usR = 0;
    WORD usG = 0;
    WORD usB = 0;
    BYTE ucBackupDB = ScalerGetByte(P31_B0_D_DB_CTRL0);
#if(_UNIFORMITY_SUPPORT == _ON)
    BYTE ucCountBank = 0;
    BYTE ucCountPage = 0;
    BYTE ucMaxPage = 0;
    BYTE ucUniformityTypeIndex = 0;
    BYTE ucUniformityModeIndex = 0;
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
    BYTE ucUniformityLevel0Enable = 0;
#endif
#endif
    ScalerSetByte(P31_B0_D_DB_CTRL0, 0x00);

    EX1 = 0;

    ucCalibrationStep = g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_STEP];

    if(UserCommonDdcciDispCalibInitialCheck() == _SUCCESS)
    {
//****************************************************************************************//
//                               MEASURE PROCESS                                          //
//****************************************************************************************//
        /////////////////////////////////////////////////////////////////
        /////////////////////TOOL GET FW DEFINE//////////////////////////
        /////////////////////////////////////////////////////////////////
        if(ucCalibrationStep == _DDCCI_DISP_CALIB_GET_DEFINE)
        {
            UserCommonDdcciDispCalibReplyResult(_DISP_CALIB_START);
            UserInterfaceAdjustBeforeDisplayCalibration(_OGC_CAL);
            ScalerMcuDdcciReleaseScl(GET_RUN_DDCCI_HANDLE_CHANNEL());

            return;
        }
        /////////////////////////////////////////////////////////////////
        /////////////////////END            /////////////////////////////
        /////////////////////////////////////////////////////////////////
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_END)
        {
            UserInterfaceAdjustAfterDisplayCalibration(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_END_TYPE]);
        }

        /////////////////////////////////////////////////////////////////
        //////////////DISPLAY CALIBRATION: MEASURE START/////////////////
        //////////////DISPLAY CALIBRATION: MEASURE RED///////////////////
        /////////////////////////////////////////////////////////////////
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_RED)
        {
            ucFlag = UserCommonDdcciDispCalibOGCStart();

            UserCommonDdcciDispCalibCalibPatternEnable(_ENABLE);
            UserCommonDdcciDispCalibShowCalibPattern(_PATTERN_TOP, 0, 0);

            g_usColorMatrixSavePos = 0;
            g_ucCTGainSavePos = 0;
            // g_nColorMatrixSavePos = 0;
            ucFlag = UserCommonFlashErasePage(_OGC_FLASH_BANK, _OGC_FLASH_PAGE);
            ucFlag = UserCommonFlashErasePage(_OGC_FLASH_BANK, _OGC_FLASH_PAGE + 1);

            if((WORD)_DISP_CALIBRATION_TOTAL_SPACE > (WORD)(_FLASH_PAGE_SIZE * 2))
            {
                ucFlag = UserCommonFlashErasePage(_OGC_FLASH_BANK, _OGC_FLASH_PAGE + 2);
            }
        }
        /////////////////////////////////////////////////////////////////
        //////////////DISPLAY CALIBRATION: MEASURE BLACK/////////////////
        /////////////////////////////////////////////////////////////////
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_BLACK)
        {
            UserCommonDdcciDispCalibShowCalibPattern(0, 0, 0);

            if((WORD)_DISP_CALIBRATION_TOTAL_SPACE > (WORD)(_FLASH_PAGE_SIZE * 3))
            {
                ucFlag = UserCommonFlashErasePage(_OGC_FLASH_BANK, _OGC_FLASH_PAGE + 3);
            }

            if((WORD)_DISP_CALIBRATION_TOTAL_SPACE > (WORD)(_FLASH_PAGE_SIZE * 4))
            {
                ucFlag = UserCommonFlashErasePage(_OGC_FLASH_BANK, _OGC_FLASH_PAGE + 4);
            }

            if((WORD)_DISP_CALIBRATION_TOTAL_SPACE > (WORD)(_FLASH_PAGE_SIZE * 5))
            {
                ucFlag = UserCommonFlashErasePage(_OGC_FLASH_BANK, _OGC_FLASH_PAGE + 5);
            }
        }
        /////////////////////////////////////////////////////////////////
        //////////////DISPLAY CALIBRATION: MEASURE BLUE//////////////////
        /////////////////////////////////////////////////////////////////
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_BLUE)
        {
            UserCommonDdcciDispCalibShowCalibPattern(0, 0, _PATTERN_TOP);

            if((WORD)_DISP_CALIBRATION_TOTAL_SPACE > (WORD)(_FLASH_PAGE_SIZE * 6))
            {
                ucFlag = UserCommonFlashErasePage(_OGC_FLASH_BANK, _OGC_FLASH_PAGE + 6);
            }

            if((WORD)_DISP_CALIBRATION_TOTAL_SPACE > (WORD)(_FLASH_PAGE_SIZE * 7))
            {
                ucFlag = UserCommonFlashErasePage(_OGC_FLASH_BANK, _OGC_FLASH_PAGE + 7);
            }

            if((WORD)_DISP_CALIBRATION_TOTAL_SPACE > (WORD)(_FLASH_PAGE_SIZE * 8))
            {
                ucFlag = UserCommonFlashErasePage(_OGC_FLASH_BANK, _OGC_FLASH_PAGE + 8);
            }
        }

        /////////////////////////////////////////////////////////////////
        //////////////DISPLAY CALIBRATION: MEASURE GREEN/////////////////
        /////////////////////////////////////////////////////////////////
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_GREEN)
        {
            UserCommonDdcciDispCalibShowCalibPattern(0, _PATTERN_TOP, 0);

            if((WORD)_DISP_CALIBRATION_TOTAL_SPACE > (WORD)(_FLASH_PAGE_SIZE * 9))
            {
                ucFlag = UserCommonFlashErasePage(_OGC_FLASH_BANK, _OGC_FLASH_PAGE + 9);
            }

            if((WORD)_DISP_CALIBRATION_TOTAL_SPACE > (WORD)(_FLASH_PAGE_SIZE * 10))
            {
                ucFlag = UserCommonFlashErasePage(_OGC_FLASH_BANK, _OGC_FLASH_PAGE + 10);
            }

            if((WORD)_DISP_CALIBRATION_TOTAL_SPACE > (WORD)_FLASH_PAGE_SIZE * 11)
            {
                ucFlag = UserCommonFlashErasePage(_OGC_FLASH_BANK, _OGC_FLASH_PAGE + 11);
            }
        }

        /////////////////////////////////////////////////////////////////
        //////////////DISPLAY CALIBRATION: MEASURE WHITE/////////////////
        /////////////////////////////////////////////////////////////////
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_WHITE)
        {
            UserCommonDdcciDispCalibShowCalibPattern(_PATTERN_TOP, _PATTERN_TOP, _PATTERN_TOP);

            if((WORD)_DISP_CALIBRATION_TOTAL_SPACE > (WORD)_FLASH_PAGE_SIZE * 12)
            {
                ucFlag = UserCommonFlashErasePage(_OGC_FLASH_BANK, _OGC_FLASH_PAGE + 12);
            }
            if((WORD)_DISP_CALIBRATION_TOTAL_SPACE > (WORD)_FLASH_PAGE_SIZE * 13)
            {
                ucFlag = UserCommonFlashErasePage(_OGC_FLASH_BANK, _OGC_FLASH_PAGE + 13);
            }
            if((WORD)_DISP_CALIBRATION_TOTAL_SPACE > (WORD)_FLASH_PAGE_SIZE * 14)
            {
                ucFlag = UserCommonFlashErasePage(_OGC_FLASH_BANK, _OGC_FLASH_PAGE + 14);
            }
        }

        /////////////////////////////////////////////////////////////////
        ////////////DISPLAY CALIBRATION: MEASURE GRAY1 / GRAY2///////////
        /////////////////////Save RGB CT gains///////////////////////////
        /////////////////////////////////////////////////////////////////
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1)
        {
            if(g_ucCTGainSavePos == 0)
            {
                UserCommonDdcciDispCalibShowCalibPattern(tOGC_GRAY_TABLE[ucCalibrationStep - _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1],
                                                         tOGC_GRAY_TABLE[ucCalibrationStep - _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1],
                                                         tOGC_GRAY_TABLE[ucCalibrationStep - _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1]);
            }

            /****************** Save RGB Gain to Flash******************/
            /* CT/Gamma   Gamma1     Gamma2    Gamma3   Gamma4   Gamma5*/
            /*    CT1     R/G/B      R/G/B     R/G/B    R/G/B    R/G/B */
            /*    CT2     R/G/B      R/G/B     R/G/B    R/G/B    R/G/B */
            /*    CT3     R/G/B      R/G/B     R/G/B    R/G/B    R/G/B */
            /*    CT4     R/G/B      R/G/B     R/G/B    R/G/B    R/G/B */
            /*    CT5     R/G/B      R/G/B     R/G/B    R/G/B    R/G/B */
            /*    User    R/G/B      R/G/B     R/G/B    R/G/B    R/G/B */
            /************************************************************/

#if(_OGC_SUPPORT == _ON)
            UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_RGB_GAIN_ADDRESS + g_ucCTGainSavePos, (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4, &g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_RGB_GAIN]);
            g_ucCTGainSavePos += (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4;
#endif
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY2)
        {
            UserCommonDdcciDispCalibShowCalibPattern(tOGC_GRAY_TABLE[ucCalibrationStep - _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1],
                                                     tOGC_GRAY_TABLE[ucCalibrationStep - _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1],
                                                     tOGC_GRAY_TABLE[ucCalibrationStep - _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1]);

//#if(_UNIFORMITY_SUPPORT == _ON)
            UserCommonDdcciDispCalibSaveHeader();
//#endif
        }

        /////////////////////////////////////////////////////////////////
        ////////////DISPLAY CALIBRATION: MEASURE GRAY3 ~ GRAY20//////////
        //////////////////////////SAVE LUT///////////////////////////////
        /////////////////////////////////////////////////////////////////
        else if((ucCalibrationStep >= _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY3) && (ucCalibrationStep <= _DDCCI_DISP_CALIB_OGC_MEASURE_LAST_GRAY))
        {
            if((g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_LUT_LENGTH] == 2) && (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_LUT_ID] == 0xFF))
            {
                UserCommonDdcciDispCalibShowCalibPattern(tOGC_GRAY_TABLE[ucCalibrationStep - _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1],
                                                         tOGC_GRAY_TABLE[ucCalibrationStep - _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1],
                                                         tOGC_GRAY_TABLE[ucCalibrationStep - _DDCCI_DISP_CALIB_OGC_MEASURE_GRAY1]);
            }
            else
            {
                UserCommonDdcciDispCalibSaveLUT((g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F));
            }
        }

        /////////////////////////////////////////////////////////////////
        //////////////DISPLAY CALIBRATION: MEASURE END///////////////////
        /////////////////////////////////////////////////////////////////
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_END)
        {
            ucFlag = UserCommonDdcciDispCalibCheckSum();

            UserCommonDdcciDispCalibShowGamma();
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_CHK_COLORMATRIX)
        {
            ucFlag = UserCommonDdcciDispCalibMatrixCheckSum(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX_TYPE]);
        }
#if(_ULTRA_HDR_SUPPORT == _ON)
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_SAVE_IGLUT)
        {
            if(g_ucIGLUTSavePos > 195)
            {
                g_ucIGLUTSavePos = 0;
            }

            UserCommonFlashWrite(_OGC_FLASH_BANK, tHDRIGAMMA_INDEX[g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_IGLUT_INDEX]] + g_ucIGLUTSavePos, (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5, &g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_IGLUT_START]);
            g_ucIGLUTSavePos += (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5;
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_SET_HDR_MODE)
        {
            // Set Input Gamma
            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
            ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
            ScalerColorPCMInputGammaAdjust(_1P_NORMAL_FULL_REGION, g_pucDISP_CALIBRATION_FLASH + _OGC_HDR_IG_1200_NOR_ADDRESS + (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_SET_HDR_IG_INDEX] * _OGC_HDR_IG_TABLE_SIZE), _OGC_FLASH_BANK);

            ScalerColorSRGBEnable(_FUNCTION_OFF);

            // Set Output Gamma
            ScalerColorOutputGammaEnable(_FUNCTION_OFF);

            ScalerColorPCMOutputGammaAdjust(_1P_NORMAL_FULL_REGION, g_pucDISP_CALIBRATION_FLASH + _OCC_HDR_GAMMA10_ADDRESS, _OGC_FLASH_BANK);

            // Set Color Matrix
            ScalerColorPCMSRGBAdjust(_1P_NORMAL_FULL_REGION, _SRGB_1_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_HDR_SRGB_MATRIX_ADDRESS + (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_SET_HDR_COLOR_MATRIX] * _OCC_COLORMATRIX_TABLE_SIZE), _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);

            ScalerColorOutputGammaEnable(_FUNCTION_ON);
            ScalerColorSRGBEnable(_FUNCTION_ON);
            ScalerColorPCMInputGammaEnable(_FUNCTION_ON);

            ScalerColorBrightnessEnable(_FUNCTION_OFF);
            ScalerColorContrastEnable(_FUNCTION_OFF);

#if(_UNIFORMITY_SUPPORT == _ON)
            ScalerColorPanelUniformityEnable(_FUNCTION_OFF);
#endif

#if(_RGB_3D_GAMMA == _ON)
            ScalerColorRGB3DGammaEnable(_FUNCTION_OFF);
#endif
        }
#endif

        /////////////////////////////////////////////////////////////////
        ////////////////////////OCC PROCESS//////////////////////////////
        /////////////////////////////////////////////////////////////////
#if(_OCC_SUPPORT == _ON)
        if(((g_ucCalibrationType >> _OCC_TYPE) & 0x01) == _TRUE)
        {
            UserCommonDdcciDispCalibOCCProcess(ucCalibrationStep);
        }
#endif


//****************************************************************************************//
//                               VERIFICATION PROCESS                                     //
//****************************************************************************************//
        /////////////////////////////////////////////////////////////////
        //////////////////////////VERIFICATION///////////////////////////
        /////////////////////////////////////////////////////////////////
        if(ucCalibrationStep == _DDCCI_DISP_CALIB_VERIFICATION)
        {
            usR = (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_VERIFY_RED] << 8) | (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_VERIFY_RED + 1]);
            usG = (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_VERIFY_GREEN] << 8) | (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_VERIFY_GREEN + 1]);
            usB = (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_VERIFY_BLUE] << 8) | (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_VERIFY_BLUE + 1]);

            ScalerDDomainPatternGenAdjustColor10bit(usR, usG, usB);
            ScalerDDomainPatternGenEnable(_ENABLE);
            ScalerDDomainBackgroundEnable(_DISPLAY_PATH_ALL, _DISABLE);
        }

        /////////////////////////////////////////////////////////////////
        ///////////////////////SET GAMMA PROCESS/////////////////////////
        /////////////////////////////////////////////////////////////////
#if(_OGC_SUPPORT == _ON)
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_SET_GAMMA)
        {
            ucGammaIndex = (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_INDEX] >> 4) & 0x0F;
            ucColorTempIndex = g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_INDEX] & 0x0F;

#if(_PCM_FUNCTION == _ON)
            ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
#endif

            ScalerColorSRGBEnable(_FUNCTION_OFF);

            // Set Output Gamma
            ScalerColorOutputGammaEnable(_FUNCTION_OFF);

            ScalerColorGammaSetEffectiveRegion(_1P_NORMAL_FULL_REGION, _DB_APPLY_NONE);

            ScalerColorOutputGammaAdjust(_1P_NORMAL_FULL_REGION, g_pucDISP_CALIBRATION_FLASH + tGAMMA_INDEX[ucGammaIndex], _OGC_FLASH_BANK);
            ScalerColorOutputGammaEnable(_FUNCTION_ON);

            ScalerColorGammaRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_NONE, _ON);
            ScalerColorBRICTSRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_POLLING, _ON);

            ScalerColorBrightnessAdjust(_1P_NORMAL_FULL_REGION, pusBriTemp);
            if(ucColorTempIndex != 0x0F)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) | (ucColorTempIndex * _OGC_TOTAL_GAMMA * 6 + ucGammaIndex * 6 + _OGC_RGB_GAIN_ADDRESS), 6, pData);
            }
            else // Native
            {
                pData[0] = 0x08;
                pData[1] = 0x00;
                pData[2] = 0x08;
                pData[3] = 0x00;
                pData[4] = 0x08;
                pData[5] = 0x00;
            }
            ScalerColorContrastAdjust(_1P_NORMAL_FULL_REGION, (WORD *)pData);
            ScalerColorContrastEnable(_FUNCTION_ON);

#if(_UNIFORMITY_SUPPORT == _ON)
            ScalerColorPanelUniformityRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_POLLING, _OFF);
#endif

#if(_RGB_3D_GAMMA == _ON)
            ScalerColorRGB3DGammaEnable(_FUNCTION_OFF);
#endif
        }
#endif  // End of #if(_OGC_SUPPORT == _ON)

        /////////////////////////////////////////////////////////////////
        ////////////////////////SET PCM PROCESS//////////////////////////
        /////////////////////////////////////////////////////////////////
#if(_OCC_SUPPORT == _ON)
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_SET_PCM)
        {
            // Set PCM Input Gamma
            ScalerTimerWaitForIDDomainEvent(_EVENT_DEN_STOP, _DISPLAY_PATH_ALL);
            ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
            ScalerColorPCMInputGammaLoadTable(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN]);

            ScalerColorSRGBEnable(_FUNCTION_OFF);

            // Set PCM Output Gamma
            ScalerColorOutputGammaEnable(_FUNCTION_OFF);


#if(_PCM_TABLE_TYPE == _PCM_GEN_0)

            ScalerColorPCMOutputGammaAdjust(g_pucDISP_CALIBRATION_FLASH + _OCC_GAMMA10_ADDRESS, _OGC_FLASH_BANK);

            // Set PCM Color Matrix

            if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SRGB)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_SRGBMATRIX_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_ADOBE_RGB)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_ADOBEMATRIX_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_EBU_MODE)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_EBU_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SOFT_PROFT)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_SOFTPROOF_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_REC_709)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_REC709_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_DCI_P3)
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_DCIP3_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else
            {
                ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_SMPTEC_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
#else


            // Set PCM Color Matrix
            ScalerColorPCMSePCMMode(_1P_NORMAL_FULL_REGION, _PCM_MODE);

            ScalerColorPCMOutputGammaAdjust(_1P_NORMAL_FULL_REGION, g_pucDISP_CALIBRATION_FLASH + _OCC_GAMMA10_ADDRESS, _OGC_FLASH_BANK);

            // Set PCM Color Matrix

            if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SRGB)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_FULL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_SRGBMATRIX_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_ADOBE_RGB)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_FULL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_ADOBEMATRIX_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_FULL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_EBU_MODE)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_FULL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_EBU_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SOFT_PROFT)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_FULL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_SOFTPROOF_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_REC_709)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_FULL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_REC709_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_DCI_P3)
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_FULL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_DCIP3_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }
            else
            {
                ScalerColorPCMSRGBAdjust(_1P_NORMAL_FULL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_SMPTEC_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
            }

#endif

            ScalerColorOutputGammaEnable(_FUNCTION_ON);
            ScalerColorSRGBEnable(_FUNCTION_ON);
            ScalerColorPCMInputGammaEnable(_FUNCTION_ON);

            ScalerColorPCMSetEffectiveRegion(_1P_NORMAL_FULL_REGION, _DB_APPLY_NONE);
            ScalerColorPCMRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_POLLING, _ON);

            ScalerColorBrightnessEnable(_FUNCTION_OFF);
            ScalerColorContrastEnable(_FUNCTION_OFF);

#if(_UNIFORMITY_SUPPORT == _ON)
            ScalerColorPanelUniformityRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_POLLING, _OFF);
#endif

#if(_RGB_3D_GAMMA == _ON)
            ScalerColorRGB3DGammaEnable(_FUNCTION_OFF);
#endif
        }
#endif  // End of #if(_OCC_SUPPORT == _ON)

        /////////////////////////////////////////////////////////////////
        ///////////////////////SET DICOM PROCESS/////////////////////////
        /////////////////////////////////////////////////////////////////
#if(_OGC_DICOM_SUPPORT == _ON)
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_SET_DICOM)
        {
            // Set DICOM
            ScalerColorOutputGammaEnable(_FUNCTION_OFF);
            ScalerColorOutputGammaAdjust(_1P_NORMAL_FULL_REGION, g_pucDISP_CALIBRATION_FLASH + _OGC_DICOM_ADDRESS, _OGC_FLASH_BANK);
            ScalerColorOutputGammaEnable(_FUNCTION_ON);

#if(_PCM_FUNCTION == _ON)
            ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
#endif

            ScalerColorSRGBEnable(_FUNCTION_OFF);

#if(_UNIFORMITY_SUPPORT == _ON)
            ScalerColorPanelUniformityRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_POLLING, _OFF);
#endif

#if(_RGB_3D_GAMMA == _ON)
            ScalerColorRGB3DGammaEnable(_FUNCTION_OFF);
#endif
        }
#endif  // End of #if(_OGC_DICOM_SUPPORT == _ON)


        /////////////////////////////////////////////////////////////////
        ///////////////////////VERIFICATION END//////////////////////////
        /////////////////////////////////////////////////////////////////
        else if((ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_VERIFY_END) || (ucCalibrationStep == _DDCCI_DISP_CALIB_OCC_VERIFY_END))
        {
            ScalerDDomainPatternGenEnable(_DISABLE);
            ScalerDDomainPatternGenAdjustColor10bit(0, 0, 0);
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_MEASURE_BG)
        {
            ScalerDDomainBackgroundEnable(_DISPLAY_PATH_ALL, _ENABLE);

            usR = (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_VERIFY_RED] << 8) | (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_VERIFY_RED + 1]);
            usG = (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_VERIFY_GREEN] << 8) | (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_VERIFY_GREEN + 1]);
            usB = (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_VERIFY_BLUE] << 8) | (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_VERIFY_BLUE + 1]);

            ScalerDDomainBackgroundSetColor10bit(usR, usG, usB);
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_BG_OFF)
        {
            ScalerDDomainBackgroundEnable(_DISPLAY_PATH_ALL, _DISABLE);
        }
#if(_UNIFORMITY_SUPPORT == _ON)
        /////////////////////////////////////////////////////////////////
        ///////////////////////SET UNIFORMITY LUT////////////////////////
        /////////////////////////////////////////////////////////////////
        if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_GET_OGC_HEADER)
        {
            UserCommonDdcciDispCalibReplyOGCHeader();
            // ScalerMcuDdcciReleaseScl();
            ScalerMcuDdcciReleaseScl(GET_RUN_DDCCI_HANDLE_CHANNEL());

            return;
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_ERASE_FLASH)
        {
            ucUniformityTypeIndex = (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX] & 0x0F);

            for(ucCountBank = _UNIFORMITY_FLASH_BANK0; ucCountBank <= tUNIFORMITY_TYPE_BANK_INDEX[ucUniformityTypeIndex]; ucCountBank++)
            {
                if(ucCountBank < tUNIFORMITY_TYPE_BANK_INDEX[ucUniformityTypeIndex])
                {
                    ucMaxPage = 15;
                }
                else
                {
                    ucMaxPage = (DWORD)((tUNIFORMITY_TYPE_ADDRESS_INDEX[ucUniformityTypeIndex] + _PANEL_UNIFORMITY_LUT_SIZE) / _FLASH_PAGE_SIZE); // ex: Total size = 4096bytes(4095 LUT + 1 checksum), only need Page0
                }

                for(ucCountPage = 0; ucCountPage <= ucMaxPage; ucCountPage++)
                {
                    ucFlag = UserCommonFlashErasePage(ucCountBank, ucCountPage);
                }
            }
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
            for(ucCountBank = _UNIFORMITY_TYPE1_OFFSET_BANK; ucCountBank <= tUNIFORMITY_TYPE_OFFSET_BANK_INDEX[ucUniformityTypeIndex]; ucCountBank++)
            {
                if(ucCountBank < tUNIFORMITY_TYPE_OFFSET_BANK_INDEX[ucUniformityTypeIndex])
                {
                    ucMaxPage = 15;
                }
                else
                {
                    ucMaxPage = (DWORD)((tUNIFORMITY_TYPE_OFFSET_ADDRESS_INDEX[ucUniformityTypeIndex] + _PANEL_UNIFORMITY_OFFSET_LUT_SIZE + _PANEL_UNIFORMITY_DECAY_LUT_SIZE) / _FLASH_PAGE_SIZE); // ex: Total size = 4096bytes(4095 LUT + 1 checksum), only need Page0
                }

                for(ucCountPage = 0; ucCountPage <= ucMaxPage; ucCountPage++)
                {
                    ucFlag = UserCommonFlashErasePage(ucCountBank, ucCountPage);
                }
            }
#endif
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_SET_GAMMA)
        {
            ucGammaIndex = g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_INDEX] & 0x0F;

            // Set Output Gamma
            ScalerColorOutputGammaEnable(_FUNCTION_OFF);
            ScalerColorGammaSetEffectiveRegion(_1P_NORMAL_FULL_REGION, _DB_APPLY_NONE);
            ScalerColorOutputGammaAdjust(_1P_NORMAL_FULL_REGION, g_pucDISP_CALIBRATION_FLASH + tGAMMA_INDEX[ucGammaIndex], _OGC_FLASH_BANK);
            ScalerColorOutputGammaEnable(_FUNCTION_ON);

            ScalerColorGammaRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_NONE, _ON);

#if(_PCM_FUNCTION == _ON)
            ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
#endif

            ScalerColorPCMRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_POLLING, _OFF);
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_GET_PCM_MATRIX)
        {
            switch((g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX] & 0x07))
            {
                case 0:

                    UserCommonDdcciDispCalibReplyOCCMatrix(_PCM_SRGB);

                    break;

                case 1:

                    UserCommonDdcciDispCalibReplyOCCMatrix(_PCM_ADOBE_RGB);

                    break;
                default:
                    break;
            }
            // UserCommonDdcciDispCalibReplyOCCMatrix(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX]);
            // ScalerMcuDdcciReleaseScl();
            ScalerMcuDdcciReleaseScl(GET_RUN_DDCCI_HANDLE_CHANNEL());

            return;
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_WRITE_START)
        {
            g_usUniformityLUTSavePos = 0;
            g_ucUniformityLUTStartPosIndex = g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX] & 0x0F;
            g_ucUniformityLUTSaveBank = tUNIFORMITY_TYPE_BANK_INDEX[g_ucUniformityLUTStartPosIndex];
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_WRITE)
        {
            UserCommonFlashWrite(g_ucUniformityLUTSaveBank, (((WORD)_UNIFORMITY_FLASH_PAGE) << 12) + tUNIFORMITY_TYPE_ADDRESS_INDEX[g_ucUniformityLUTStartPosIndex] + g_usUniformityLUTSavePos, (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4, &g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX]);
            g_usUniformityLUTSavePos += (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4;
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_WRITE_END)
        {
            g_ucUniformityChecksumType = g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_TYPE];

            g_ucCalibrationType = 0;
            ucFlag = UserCommonDdcciDispCalibCheckSum();
            g_usUniformityLUTSavePos = 0;// level0, CYShih
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_VERIFY_START)
        {
            if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX] == _ON)
            {
                ScalerColorPanelUniformityRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_POLLING, _OFF);
                ucUniformityTypeIndex = (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX + 1] & 0xF0) >> 4;
                ucUniformityModeIndex = g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX + 1] & 0x0F;
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
                ucUniformityLevel0Enable = g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX + 2] & _BIT0;
                if(ucUniformityLevel0Enable == _ON)
                {
                    ScalerColorPanelUniformityOffsetAdjust(g_pucDISP_CALIBRATION_FLASH + tUNIFORMITY_TYPE_OFFSET_ADDRESS_INDEX[ucUniformityTypeIndex], _PANEL_UNIFORMITY_OFFSET_LUT_SIZE, tUNIFORMITY_TYPE_OFFSET_BANK_INDEX[ucUniformityTypeIndex]);// CYShih, fix
                    ScalerColorPanelUniformityDecayAdjust(g_pucDISP_CALIBRATION_FLASH + tUNIFORMITY_TYPE_DECAY_ADDRESS_INDEX[ucUniformityTypeIndex], _PANEL_UNIFORMITY_DECAY_LUT_SIZE, tUNIFORMITY_TYPE_DECAY_BANK_INDEX[ucUniformityTypeIndex], ucUniformityModeIndex, _PANEL_UNIFORMITY_MULTI_LUT_MODE);
                }
                ScalerColorPanelUniformityOffsetEnable(ucUniformityLevel0Enable);
#endif
                ScalerColorPanelUniformityAdjust(g_pucDISP_CALIBRATION_FLASH + tUNIFORMITY_TYPE_ADDRESS_INDEX[ucUniformityTypeIndex], _PANEL_UNIFORMITY_LUT_SIZE, tUNIFORMITY_TYPE_BANK_INDEX[ucUniformityTypeIndex], ucUniformityModeIndex);

                ScalerColorPanelUniformityRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_POLLING, _ON);
            }
            else
            {
                ScalerColorPanelUniformityRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_NONE, _OFF);
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
                ScalerColorPanelUniformityOffsetEnable(_FUNCTION_OFF);
#endif
            }
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_VERIFY_END)
        {
            ScalerColorPanelUniformityRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_NONE, _OFF);
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
            ScalerColorPanelUniformityOffsetEnable(_FUNCTION_OFF);
#endif
            ScalerColorPCMRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_NONE, _OFF);

#if(_PCM_FUNCTION == _ON)
            ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
#endif
            ScalerColorGammaRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_POLLING, _OFF);
            ScalerColorSRGBEnable(_FUNCTION_OFF);
            ScalerColorContrastEnable(_FUNCTION_OFF);
            ScalerColorBrightnessEnable(_FUNCTION_OFF);
            ScalerColorOutputGammaEnable(_FUNCTION_OFF);
            ScalerColorSpaceConvertDDomainEnable(_1P_NORMAL_FULL_REGION, _OFF);
            ScalerColorSpaceConvertIDomainEnable(_1P_NORMAL_FULL_REGION, _OFF);
#if(_DCC_FUNCTION == _ON)
            ScalerColorDCCEnable(_FUNCTION_OFF);
#elif(_IAPS_SUPPORT == _ON)
#if(_IAPS_GAIN_COMPENSATION_TYPE == _IAPS_GAIN_COMPENSATION_GEN_0)
            ScalerColorDCCEnable(_FUNCTION_OFF);
#endif
#endif

#if(_ICM_SUPPORT == _ON)
            ScalerColorICMEnable(_FUNCTION_OFF);
#endif
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_GET_DEFINE)
        {
            // UserCommonDdcciDispCalibReplyResult(_DISP_CALIB_UNIFORMITY);
            UserInterfaceAdjustBeforeDisplayCalibration(_UNIFORMITY_CAL);
            UserCommonDdcciDispCalibReplyUniformityDefine();
            // ScalerMcuDdcciReleaseScl();
            ScalerMcuDdcciReleaseScl(GET_RUN_DDCCI_HANDLE_CHANNEL());
            return;
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_GET_CCT_GAIN)
        {
            UserCommonDdcciDispCalibReplyCCTGain();
            // ScalerMcuDdcciReleaseScl();
            ScalerMcuDdcciReleaseScl(GET_RUN_DDCCI_HANDLE_CHANNEL());
            return;
        }
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_W_OFFSET)
        {
            UserCommonFlashWrite(tUNIFORMITY_TYPE_OFFSET_BANK_INDEX[g_ucUniformityLUTStartPosIndex], (((WORD)_UNIFORMITY_FLASH_PAGE) << 12) + tUNIFORMITY_TYPE_OFFSET_ADDRESS_INDEX[g_ucUniformityLUTStartPosIndex] + g_usUniformityLUTSavePos, (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4, &g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX]);
            g_usUniformityLUTSavePos += (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4;
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_W_OFFSET_END)
        {
            g_ucUniformityChecksumType = g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_TYPE];

            g_ucCalibrationType = 0;
            ucFlag = UserCommonDdcciDispCalibCheckSum();
            g_usUniformityLUTSavePos = 0;// level0, CYShih
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_W_DECAY)
        {
            UserCommonFlashWrite(tUNIFORMITY_TYPE_DECAY_BANK_INDEX[g_ucUniformityLUTStartPosIndex], (((WORD)_UNIFORMITY_FLASH_PAGE) << 12) + tUNIFORMITY_TYPE_DECAY_ADDRESS_INDEX[g_ucUniformityLUTStartPosIndex] + g_usUniformityLUTSavePos, (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4, &g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX]);
            g_usUniformityLUTSavePos += (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4;
        }
        else if(ucCalibrationStep == _DDCCI_DISP_CALIB_UNIFORMITY_W_DECAY_END)
        {
            g_ucUniformityChecksumType = g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_TYPE];

            g_ucCalibrationType = 0;
            ucFlag = UserCommonDdcciDispCalibCheckSum();
        }
#endif  // End of #if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
#endif  // End of #if(_UNIFORMITY_SUPPORT== _ON)

//****************************************************************************************//
//                               FINAL PROCESS                                            //
//****************************************************************************************//
        /////////////////////////////////////////////////////////////////
        ///////////////////////REPLY RESULTS/////////////////////////////
        /////////////////////////////////////////////////////////////////
        if(ucCalibrationStep == _DDCCI_DISP_CALIB_VERIFICATION)
        {
            UserCommonDdcciDispCalibReplyResult(_DISP_CALIB_PASS);
        }
        else
        {
            if(ucFlag == 1)
            {
                UserCommonDdcciDispCalibReplyResult(_DISP_CALIB_PASS);
            }
            else
            {
                if((ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_BLACK) || (ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_GREEN))
                {
                    UserCommonDdcciDispCalibReplyResult(_DISP_CALIB_ERASE_ERROR);
                }
                else if(ucCalibrationStep == _DDCCI_DISP_CALIB_OGC_MEASURE_RED)
                {
                    UserCommonDdcciDispCalibReplyResult(_DISP_CALIB_FW_ERROR);
                }
                else
                {
                    UserCommonDdcciDispCalibReplyResult(_DISP_CALIB_CRC_ERROR);
                }
            }
        }
    }
    else    // else of if(UserCommonDdcciDispCalibInitialCheck() == _SUCCESS)
    {
        UserCommonDdcciDispCalibReplyResult(_DISP_CALIB_FAIL);
    }
    ScalerSetByte(P31_B0_D_DB_CTRL0, ucBackupDB);
    ScalerMcuDdcciReleaseScl(GET_RUN_DDCCI_HANDLE_CHANNEL());
}

//--------------------------------------------------
// Description  : OGC Measure Start Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit UserCommonDdcciDispCalibOGCStart(void)
{
    BYTE ucCnt = 0;
    BYTE ucFlag = 1;

#if(_ULTRA_HDR_SUPPORT == _ON)
    g_ucIGLUTSavePos = 0;
#endif

    // Get Counter Start
#if(_OGC_SUPPORT == _ON)
    for(ucCnt = 0; ucCnt < _OGC_TOTAL_GAMMA; ucCnt++)
    {
        g_pusGammaCount[ucCnt][0] = 2052;
        g_pusGammaCount[ucCnt][1] = 2052;
        g_pusGammaCount[ucCnt][2] = 2052;
    }
#endif  // End of #if(_OGC_SUPPORT == _ON)

#if(_OCC_SUPPORT == _ON)
    g_pusGammaCount[ucCnt][0] = 2200;
    g_pusGammaCount[ucCnt][1] = 2200;
    g_pusGammaCount[ucCnt][2] = 2200;
    ucCnt++;
#endif  // End of #if(_OCC_SUPPORT == _ON)

#if(_OGC_DICOM_SUPPORT == _ON)
    g_pusGammaCount[ucCnt][0] = 2052;
    g_pusGammaCount[ucCnt][1] = 2052;
    g_pusGammaCount[ucCnt][2] = 2052;
    ucCnt++;
#endif  // End of #if(_OGC_DICOM_SUPPORT == _ON)

    // Get Counter End
    g_ucCalibrationType = g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_TYPE];

#if(_OGC_SUPPORT == _OFF)
    if(((g_ucCalibrationType >> _OGC_TYPE) & _BIT0) == _TRUE)
    {
        ucFlag = 0;
    }
#endif  // End of #if(_OGC_SUPPORT == _OFF)

#if(_OCC_SUPPORT == _OFF)
    if(((g_ucCalibrationType >> _OCC_TYPE) & _BIT0) == _TRUE)
    {
        ucFlag = 0;
    }
#endif  // End of #if(_OCC_SUPPORT == _OFF)

#if(_OGC_DICOM_SUPPORT == _OFF)
    if(((g_ucCalibrationType >> _DICOM_TYPE) & _BIT0) == _TRUE)
    {
        ucFlag = 0;
    }
#endif  // End of #if(_OGC_DICOM_SUPPORT == _OFF)

    if(((g_ucCalibrationType >> (_DICOM_TYPE + 1)) & 0x1F) != _OGC_TOTAL_GAMMA)
    {
        ucFlag = 0;
    }

    g_ucPatternType = (g_ucCalibrationType & _BIT6) >> 6;

#if(_OCC_SUPPORT == _ON)
    if(((g_ucCalibrationType >> _OCC_TYPE) & _BIT0) == _TRUE)
    {
        ScalerColorPCMSetEffectiveRegion(_1P_NORMAL_FULL_REGION, _DB_APPLY_NONE);
#if(_PCM_TABLE_TYPE == _PCM_GEN_1)
        ScalerColorPCMSePCMMode(_1P_NORMAL_FULL_REGION, _PCM_MODE);
#endif
        ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
        ScalerColorSRGBSetEffectiveRegion(_1P_NORMAL_FULL_REGION, _DB_APPLY_POLLING);
        ScalerColorPCMInputGammaLoadTable(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_OCC_COLORSPACE]);
        ScalerDDomainPatternGenAdjustColor10bit(tOCC_SRGB_TABLE[0], tOCC_SRGB_TABLE[1], tOCC_SRGB_TABLE[2]);
        ScalerDDomainPatternGenEnable(_ENABLE);
    }
    else
#endif  // End of #if(_OCC_SUPPORT == _ON)
    {

#if(_PCM_FUNCTION == _ON)
        ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
#endif
    }


    ScalerColorOutputGammaEnable(_FUNCTION_OFF);
    ScalerColorSRGBEnable(_FUNCTION_OFF);
    ScalerColorContrastEnable(_FUNCTION_OFF);
    ScalerColorBrightnessEnable(_FUNCTION_OFF);
    ScalerColorSpaceConvertIDomainEnable(_1P_NORMAL_FULL_REGION, _OFF);
    ScalerColorSpaceConvertDDomainEnable(_1P_NORMAL_FULL_REGION, _OFF);

#if(_DCC_FUNCTION == _ON)
    ScalerColorDCCEnable(_FUNCTION_OFF);
#elif(_IAPS_SUPPORT == _ON)
#if(_IAPS_GAIN_COMPENSATION_TYPE == _IAPS_GAIN_COMPENSATION_GEN_0)
    ScalerColorDCCEnable(_FUNCTION_OFF);
#endif
#endif

#if(_ICM_SUPPORT == _ON)
    ScalerColorICMEnable(_FUNCTION_OFF);
#endif

#if(_RGB_3D_GAMMA == _ON)
    ScalerColorRGB3DGammaEnable(_FUNCTION_OFF);
#endif

#if(_UNIFORMITY_SUPPORT == _ON)
    ScalerColorPanelUniformityEnable(_FUNCTION_OFF);
#endif

    return ucFlag;
}

#if(_OCC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Display Calibration OCC Process
// Input Value  : Calibration Step
// Output Value : ucFlag
//--------------------------------------------------
BYTE UserCommonDdcciDispCalibOCCProcess(BYTE ucStep)
{
    BYTE ucFlag = 1;
    BYTE ucPatternEnd = (_OCC_LUT_MODE == _ON) ? _DDCCI_DISP_CALIB_OCC_MEASURE_SRGB21 : _DDCCI_DISP_CALIB_OCC_MEASURE_SRGB7;


    if((ucStep >= _DDCCI_DISP_CALIB_OCC_MEASURE_SRGB1) && (ucStep < ucPatternEnd))
    {
        ScalerDDomainPatternGenAdjustColor10bit(tOCC_SRGB_TABLE[(ucStep - _DDCCI_DISP_CALIB_OCC_MEASURE_SRGB1 + 1) * 3],
                                                tOCC_SRGB_TABLE[(ucStep - _DDCCI_DISP_CALIB_OCC_MEASURE_SRGB1 + 1) * 3 + 1],
                                                tOCC_SRGB_TABLE[(ucStep - _DDCCI_DISP_CALIB_OCC_MEASURE_SRGB1 + 1) * 3 + 2]);
    }
    else if(ucStep == ucPatternEnd)
    {
        UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_SRGBMATRIX_ADDRESS + g_usColorMatrixSavePos, (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5, &g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_OCC_MATRIX]);
        g_usColorMatrixSavePos += (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 5;

        ScalerColorPCMRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_POLLING, _OFF);

#if(_PCM_TABLE_TYPE == _PCM_GEN_0)

        // Set PCM Color Matrix
        if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SRGB)
        {
            ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_SRGBMATRIX_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
        }
        else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_ADOBE_RGB)
        {
            ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_ADOBEMATRIX_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
        }
        else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE)
        {
            ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
        }
        else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_EBU_MODE)
        {
            ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_EBU_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
        }
        else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SOFT_PROFT)
        {
            ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_SOFTPROOF_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
        }
        else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_REC_709)
        {
            ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_REC709_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
        }
        else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_DCI_P3)
        {
            ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_DCIP3_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
        }
        else
        {
            ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_SMPTEC_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
        }
#else
        // Set PCM Color Matrix
        if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SRGB)
        {
            ScalerColorPCMSRGBAdjust(_1P_NORMAL_FULL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_SRGBMATRIX_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
        }
        else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_ADOBE_RGB)
        {
            ScalerColorPCMSRGBAdjust(_1P_NORMAL_FULL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_ADOBEMATRIX_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
        }
        else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_USER_DEFINE)
        {
            ScalerColorPCMSRGBAdjust(_1P_NORMAL_FULL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_USERDEFINE_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
        }
        else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_EBU_MODE)
        {
            ScalerColorPCMSRGBAdjust(_1P_NORMAL_FULL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_EBU_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
        }
        else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_SOFT_PROFT)
        {
            ScalerColorPCMSRGBAdjust(_1P_NORMAL_FULL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_SOFTPROOF_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
        }
        else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_REC_709)
        {
            ScalerColorPCMSRGBAdjust(_1P_NORMAL_FULL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_REC709_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
        }
        else if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_PCM_COLOR_DOMAIN] == _PCM_DCI_P3)
        {
            ScalerColorPCMSRGBAdjust(_1P_NORMAL_FULL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_DCIP3_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
        }
        else
        {
            ScalerColorPCMSRGBAdjust(_1P_NORMAL_FULL_REGION, _SRGB_0_BIT_SHIFT_LEFT, g_pucDISP_CALIBRATION_FLASH + _OCC_SMPTEC_ADDRESS, _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE);
        }
#endif

        ScalerColorSRGBEnable(_FUNCTION_ON);
        ScalerColorPCMRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_POLLING, _ON);

        // Disable Display Pattern Gen. & set (0,0,0)
        ScalerDDomainPatternGenEnable(_DISABLE);
        ScalerDDomainPatternGenAdjustColor10bit(0, 0, 0);
    }
#if(_ULTRA_HDR_SUPPORT == _ON)
    else if(ucStep == _DDCCI_DISP_CALIB_SAVE_HDR_MATRIX)
    {
        UserCommonFlashWrite(_OGC_FLASH_BANK, _OCC_HDR_SRGB_MATRIX_ADDRESS, (g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F) - 4, &g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_HDRMATRIX_START]);
    }
#endif
    return ucFlag;
}
#endif // End of #if(_OCC_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Check if the checksum from Tool is equal to DDCCI data
// Input Value  : None
// Output Value : _SUCCESS/_FAIL
//--------------------------------------------------
bit UserCommonDdcciDispCalibInitialCheck(void)
{
    BYTE ucSum = 0;
    BYTE ucChecksum = 0;
    BYTE ucLength = 0;
    BYTE ucI = 0;

    ucLength = g_pucDdcciRxBuf[_DDCCI_LENGTH] & 0x7F;

    for(ucI = 2; ucI < (ucLength + 1); ucI++)
    {
        ucSum += g_pucDdcciRxBuf[ucI];
    }

    ucChecksum = g_pucDdcciRxBuf[ucLength + 1];

    if(ucSum == ucChecksum)
    {
        return _SUCCESS;
    }
    else
    {
        return _FAIL;
    }
}

//--------------------------------------------------
// Description  : Save LUT Data from DDCCI Rx
// Input Value  : nAddress: address in DISP_CALIBRATION_FLASH;
//                nLength: Data Length
//                ucBuffer: pointer of databuffer
// Output Value : None
//--------------------------------------------------

void UserCommonDdcciDispCalibSaveLUT(BYTE ucTotalLength)
{
    BYTE ucLUTLength = 0;
    BYTE ucPointer = 5;
    BYTE ucGammaIndex = 0;
    BYTE ucRGB = 0;
    WORD usStartAddr = _OGC_GAMMA1_ADDRESS;
    WORD usLastLUT = 0;
    WORD usCurrLUT = 0;
    BYTE pucIntoLUT[128] = {0};
    BYTE ucJ = 0;
    WORD usInto = 0;
    bit bIsLastLUT = _FALSE;
    SWORD shRemain = 0;
    SWORD shCnt = 0;
    // int nNum = 0;
    BYTE ucCurPointer = 0;
    SWORD shWriteCnt = 0;
#if(_OCC_SUPPORT == _ON)
    BYTE ucTempLen = 0;
    bit bWriteDirectly = _FALSE;
#endif

    // ucTotalLength - 1: exclude checksum
    while(ucPointer < (ucTotalLength - 1))
    {
        // LUT Length (exclude ID and Length Bytes)
        ucLUTLength = g_pucDdcciRxBuf[ucPointer] - 2;

        ucGammaIndex = (g_pucDdcciRxBuf[ucPointer + 1] >> 4) & 0x0F;
        ucRGB = g_pucDdcciRxBuf[ucPointer + 1] & 0x0F;
        ucPointer += 2;

#if(_OCC_SUPPORT == _ON)
        if(ucGammaIndex == _OCC_POSITION)
        {
            usStartAddr = tGAMMA_INDEX[_OCC_POSITION] + (ucRGB) * 2200;
        }
        else
#endif
        {
            usStartAddr = tGAMMA_INDEX[ucGammaIndex] + (ucRGB) * 2052;
        }

        bIsLastLUT = _FALSE;
#if(_OCC_SUPPORT == _ON)
        if((ucGammaIndex == _OCC_POSITION) && (g_pusGammaCount[ucGammaIndex][ucRGB] == 2200))
        {
            bIsLastLUT = _TRUE;
        }
        else if((ucGammaIndex != _OCC_POSITION) && (g_pusGammaCount[ucGammaIndex][ucRGB] == 2052))
        {
            bIsLastLUT = _TRUE;
        }
#else
        if(g_pusGammaCount[ucGammaIndex][ucRGB] == 2052)
        {
            bIsLastLUT = _TRUE;
        }
#endif
        if(bIsLastLUT == _TRUE)
        {
            shRemain = (ucLUTLength - 2) * 4 + 4;
        }
        else
        {
#if(_OCC_SUPPORT == _ON)
            if((ucGammaIndex == _OCC_POSITION) && (g_pusGammaCount[ucGammaIndex][ucRGB] <= 164))
            {
                shRemain = ucLUTLength;
            }
            else
#endif
            {
                shRemain = ucLUTLength * 4;
            }
        }
        ucCurPointer = ucPointer + ucLUTLength - 1;

        while(shRemain > 0)
        {
            if(shRemain > 128)
            {
                shCnt = (bIsLastLUT == _TRUE) ? 124 : 128;
                shRemain -= shCnt;
            }
            else
            {
                shCnt = shRemain;
                shRemain = 0;
            }
            shWriteCnt = shCnt;
            shCnt--;
            while(shCnt > 0)
            {
                usCurrLUT = (g_pucDdcciRxBuf[ucCurPointer - 1] << 8) | g_pucDdcciRxBuf[ucCurPointer];

                if(ucCurPointer == ucPointer + ucLUTLength - 1)
                {
                    if(bIsLastLUT == _TRUE)
                    {
                        pucIntoLUT[shCnt--] = 0;
                        pucIntoLUT[shCnt--] = 0;

                        // Save 1024
                        pucIntoLUT[shCnt--] = usCurrLUT & 0xFF;
                        pucIntoLUT[shCnt--] = usCurrLUT >> 8;
                        ucCurPointer -= 2;
                        continue;
                    }
                    else
                    {
                        UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + usStartAddr + g_pusGammaCount[ucGammaIndex][ucRGB], 2, pData);
                        usLastLUT = (pData[0] << 8) | pData[1];
                    }
                }
                else
                {
                    usLastLUT = (g_pucDdcciRxBuf[ucCurPointer + 1] << 8) | g_pucDdcciRxBuf[ucCurPointer + 2];
                }

                if(bIsLastLUT == _TRUE)
                {
                    // Last interpolation: 1020, 1021, 1022; 1023 = 1024
                    pucIntoLUT[shCnt--] = usLastLUT & 0xFF;
                    pucIntoLUT[shCnt--] = (usLastLUT >> 8) & 0x3F;

                    for(ucJ = 1; ucJ < 4; ucJ++)
                    {
                        usInto = usLastLUT - (2 * (DWORD)(usLastLUT - usCurrLUT) * ucJ + 3) / 6;
                        pucIntoLUT[shCnt--] = usInto & 0xFF;
                        pucIntoLUT[shCnt--] = (usInto >> 8);
                    }

                    bIsLastLUT = _FALSE;
                }
                else
                {
#if(_OCC_SUPPORT == _ON)
                    if(ucGammaIndex == _OCC_POSITION)
                    {
                        if(g_pusGammaCount[ucGammaIndex][ucRGB] - (shWriteCnt - shCnt - 1) <= 164) // Latch: No Intopolation
                        {
                            bWriteDirectly = _TRUE;

                            if((shWriteCnt - shCnt - 1) != 0)
                            {
                                UserCommonFlashWrite(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + (usStartAddr + g_pusGammaCount[ucGammaIndex][ucRGB] - (shWriteCnt - shCnt - 1)), shWriteCnt - shCnt - 1, pucIntoLUT + shCnt + 1);
                                g_pusGammaCount[ucGammaIndex][ucRGB] -= shWriteCnt - shCnt - 1;
                            }
                            break;
                        }
                        else
                        {
                            for(ucJ = 1; ucJ <= 4; ucJ++)
                            {
                                usInto = usLastLUT - ((usLastLUT - usCurrLUT) * ucJ + 2) / 4;
                                pucIntoLUT[shCnt--] = usInto & 0xFF;
                                pucIntoLUT[shCnt--] = (usInto >> 8) & 0x3F;
                            }
                        }
                    }
                    else
#endif
                    {
                        for(ucJ = 1; ucJ <= 4; ucJ++)
                        {
                            usInto = usLastLUT - ((usLastLUT - usCurrLUT) * ucJ + 2) / 4;
                            pucIntoLUT[shCnt--] = usInto & 0xFF;
                            pucIntoLUT[shCnt--] = usInto >> 8;
                        }
                    }
                }
                ucCurPointer -= 2;
            }

#if(_OCC_SUPPORT == _ON)
            if(bWriteDirectly == _TRUE)
            {
                if(g_pusGammaCount[ucGammaIndex][ucRGB] <= 148) // Latch: No Intopolation
                {
                    ucTempLen = ucCurPointer - ucPointer + 1;
                    UserCommonFlashWrite(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + (usStartAddr + g_pusGammaCount[ucGammaIndex][ucRGB] - ucTempLen), ucTempLen, &g_pucDdcciRxBuf[ucPointer]);
                    g_pusGammaCount[ucGammaIndex][ucRGB] = g_pusGammaCount[ucGammaIndex][ucRGB] - ucTempLen;
                    bWriteDirectly = _FALSE;
                    break;
                }
                else if(g_pusGammaCount[ucGammaIndex][ucRGB] <= 164) // add 16 0s
                {
                    memset(pData, 0, 16);
                    UserCommonFlashWrite(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + (usStartAddr + g_pusGammaCount[ucGammaIndex][ucRGB] - 16), 16, pData);
                    g_pusGammaCount[ucGammaIndex][ucRGB] = 148;

                    ucTempLen = ucCurPointer - ucPointer + 1;
                    UserCommonFlashWrite(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + (usStartAddr + g_pusGammaCount[ucGammaIndex][ucRGB] - ucTempLen), ucTempLen, &g_pucDdcciRxBuf[ucPointer]);
                    g_pusGammaCount[ucGammaIndex][ucRGB] = g_pusGammaCount[ucGammaIndex][ucRGB] - ucTempLen;
                    bWriteDirectly = _FALSE;
                    break;
                }
                bWriteDirectly = _FALSE;
            }
            else
#endif
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + (usStartAddr + g_pusGammaCount[ucGammaIndex][ucRGB] - shWriteCnt), shWriteCnt, pucIntoLUT);
                g_pusGammaCount[ucGammaIndex][ucRGB] -= shWriteCnt;
            }
        }
        ucPointer += ucLUTLength;
    }
}

//--------------------------------------------------
// Description  : Calculate the checksum of data in Flash
// Input Value  : ucCheckType: 0- OGC, 1-OCC, 2-DICOM, 3-RGB gain, other- color Matrix,
// Output Value : Checksum
//--------------------------------------------------
BYTE UserCommonDdcciDispCalibCalCheckSum(BYTE ucCheckType)
{
    WORD usI = 0;
    WORD usJ = 0;
    BYTE ucBank = 0;
    if(ucCheckType != _UNIFORMITY_GAIN_TYPE)
    {
        if(_OGC_FLASH_BANK < MCU_FFFD_XDATA_BANK_START)
        {
            return _FALSE;
        }

        ucBank = MCU_FFFE_XDATA_BANK_SEL;
        MCU_FFFE_XDATA_BANK_SEL = _OGC_FLASH_BANK - MCU_FFFD_XDATA_BANK_START;
    }

    pData[0] = 0;

    switch(ucCheckType)
    {
        case _OGC_TYPE:
            for(usJ = 0; usJ < 3; usJ++)
            {
                for(usI = 0; usI < 2052; usI = usI + 8)
                {
                    UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_GAMMA1_ADDRESS + usJ * 2052 + usI), 2, pData + 2);
                    pData[0] += pData[2];
                    pData[0] += pData[3];
                }
            }

#if(_OGC_TOTAL_GAMMA == 1)
            MCU_FFFE_XDATA_BANK_SEL = ucBank;
            return pData[0];
#endif

            for(usJ = 0; usJ < 3; usJ++)
            {
                for(usI = 0; usI < 2052; usI = usI + 8)
                {
                    UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_GAMMA2_ADDRESS + usJ * 2052 + usI), 2, pData + 2);
                    pData[0] += pData[2];
                    pData[0] += pData[3];
                }
            }
#if(_OGC_TOTAL_GAMMA == 2)
            MCU_FFFE_XDATA_BANK_SEL = ucBank;
            return pData[0];
#endif
            for(usJ = 0; usJ < 3; usJ++)
            {
                for(usI = 0; usI < 2052; usI = usI + 8)
                {
                    UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_GAMMA3_ADDRESS + usJ * 2052 + usI), 2, pData + 2);
                    pData[0] += pData[2];
                    pData[0] += pData[3];
                }
            }

#if(_OGC_TOTAL_GAMMA == 3)
            MCU_FFFE_XDATA_BANK_SEL = ucBank;
            return pData[0];
#endif

            for(usJ = 0; usJ < 3; usJ++)
            {
                for(usI = 0; usI < 2052; usI = usI + 8)
                {
                    UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_GAMMA4_ADDRESS + usJ * 2052 + usI), 2, pData + 2);
                    pData[0] += pData[2];
                    pData[0] += pData[3];
                }
            }
#if(_OGC_TOTAL_GAMMA == 4)
            MCU_FFFE_XDATA_BANK_SEL = ucBank;
            return pData[0];
#endif

            for(usJ = 0; usJ < 3; usJ++)
            {
                for(usI = 0; usI < 2052; usI = usI + 8)
                {
                    UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_GAMMA5_ADDRESS + usJ * 2052 + usI), 2, pData + 2);
                    pData[0] += pData[2];
                    pData[0] += pData[3];
                }
            }

#if(_OGC_TOTAL_GAMMA == 5)
            MCU_FFFE_XDATA_BANK_SEL = ucBank;
            return pData[0];
#endif
            break;

        case _OCC_TYPE:

            for(usJ = 0; usJ < 3; usJ++)
            {
                for(usI = 0; usI < 148; usI++)
                {
                    UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_GAMMA10_ADDRESS + usJ * 2200 + usI), 1, pData + 2);
                    pData[0] += pData[2];
                }

                for(usI = 164; usI < 2200; usI = usI + 8)
                {
                    UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_GAMMA10_ADDRESS + usJ * 2200 + usI), 2, pData + 2);
                    pData[0] += pData[2];
                    pData[0] += pData[3];
                }
            }

            break;

        case _DICOM_TYPE:

            for(usJ = 0; usJ < 3; usJ++)
            {
                for(usI = 0; usI < 2052; usI = usI + 8)
                {
                    UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_DICOM_ADDRESS + usJ * 2052 + usI), 2, pData + 2);
                    pData[0] += pData[2];
                    pData[0] += pData[3];
                }
            }

            break;

        case _RGB_GAIN_TYPE:

            for(usI = _OGC_RGB_GAIN_ADDRESS; usI < (_OGC_RGB_GAIN_ADDRESS + _OGC_RGB_GAIN_ACTUAL_SIZE); usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + usI), 1, pData + 2);

                pData[0] += pData[2];
            }

            break;

        case _HEADER_TYPE:

            //==========Calculate OGC Header============
            for(usI = _OGC_HEADER_ADDRESS + 3; usI < _OCC_HEADER_ADDRESS; usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + usI), 1, pData + 2);

                pData[0] += pData[2];
            }
            //==========Calculate OCC Header============
            for(usI = _OCC_HEADER_ADDRESS + 3; usI < _DICOM_HEADER_ADDRESS; usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + usI), 1, pData + 2);

                pData[0] += pData[2];
            }
            //==========Calculate DICOM Header============
            for(usI = _DICOM_HEADER_ADDRESS + 3; usI < _WHITE_LV_HEADER_ADDRESS; usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + usI), 1, pData + 2);

                pData[0] += pData[2];
            }
            //==========Calculate White Lv Header============
            for(usI = _WHITE_LV_HEADER_ADDRESS + 3; usI < (_WHITE_LV_HEADER_ADDRESS + _WHITE_LV_HEADER_LENGTH); usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + usI), 1, pData + 2);

                pData[0] += pData[2];
            }

            break;

        case _COLOR_MATRIX_TYPE:

            for(usI = _OCC_SRGBMATRIX_ADDRESS; usI < (_OCC_SRGBMATRIX_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * (_TOTAL_COLORSPACE_NUM - 2)); usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + usI), 1, pData + 2);
                pData[0] += pData[2];
            }

            break;

#if(_ULTRA_HDR_SUPPORT == _ON)
        case _HDR_TYPE:

            for(usI = _OCC_HDR_SRGB_MATRIX_ADDRESS; usI < (_OCC_HDR_SRGB_MATRIX_ADDRESS + _OCC_COLORMATRIX_TABLE_SIZE * 4); usI++)
            {
                UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + usI), 1, pData + 2);
                pData[0] += pData[2];
            }


            for(usJ = 0; usJ < 6; usJ++)
            {
                for(usI = 0; usI < _OGC_HDR_IG_TABLE_SIZE; usI++)
                {
                    UserCommonFlashRead(_OGC_FLASH_BANK, ((((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_HDR_IG_1200_NOR_ADDRESS + _OGC_HDR_IG_TABLE_SIZE * usJ + usI), 1, pData + 2);
                    pData[0] += pData[2];
                }
            }

            break;
#endif

        default:

            break;
    }

    MCU_FFFE_XDATA_BANK_SEL = ucBank;

    return pData[0];
}

//--------------------------------------------------
// Description  : Measure End --> Show Gamma
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciDispCalibShowGamma(void)
{
#if(_OGC_SUPPORT == _ON)
    BYTE ucGammaIndex = 0;
    BYTE ucColorTempIndex = 0;
    WORD pusBriTemp[3] = {0x200, 0x200, 0x200};
#endif

    ScalerColorOutputGammaEnable(_FUNCTION_OFF);

#if(_OGC_SUPPORT == _ON)
    if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_FINAL_TYPE] == _OGC_TYPE)
    {
        ucGammaIndex = (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_OGC_GAMMA_CT_INFO] >> 4) & 0x0F;
        ucColorTempIndex = g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_OGC_GAMMA_CT_INFO] & 0x0F;

        ScalerColorOutputGammaAdjust(_1P_NORMAL_FULL_REGION, g_pucDISP_CALIBRATION_FLASH + tGAMMA_INDEX[ucGammaIndex], _OGC_FLASH_BANK);
        ScalerColorBrightnessAdjust(_1P_NORMAL_FULL_REGION, pusBriTemp);

        if(ucColorTempIndex != 0x0F)
        {
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) | (ucColorTempIndex * _OGC_TOTAL_GAMMA * 6 + ucGammaIndex * 6 + _OGC_RGB_GAIN_ADDRESS), 6, pData);
        }
        else // Native
        {
            pData[0] = 0x08;
            pData[1] = 0x00;
            pData[2] = 0x08;
            pData[3] = 0x00;
            pData[4] = 0x08;
            pData[5] = 0x00;
        }
        ScalerColorContrastAdjust(_1P_NORMAL_FULL_REGION, ((WORD *)pData));
        ScalerColorContrastEnable(_FUNCTION_ON);

#if(_PCM_FUNCTION == _ON)
        ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
        ScalerColorSRGBEnable(_FUNCTION_OFF);
#endif

        UserCommonDdcciDispCalibCalibPatternEnable(_DISABLE);
    }
#endif  // End of #if(_OGC_SUPPORT == _ON)

#if(_OCC_SUPPORT == _ON)
    if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_FINAL_TYPE] == _OCC_TYPE)
    {
        ScalerTimerWaitForIDDomainEvent(_EVENT_DEN_STOP, _DISPLAY_PATH_ALL);
        ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
        ScalerColorOutputGammaEnable(_FUNCTION_OFF);
        ScalerColorSRGBEnable(_FUNCTION_OFF);

#if(_PCM_TABLE_TYPE == _PCM_GEN_0)

        ScalerColorPCMOutputGammaAdjust(g_pucDISP_CALIBRATION_FLASH + _OCC_GAMMA10_ADDRESS, _OGC_FLASH_BANK);
        ScalerColorPCMSRGBAdjust(_SRGB_0_BIT_SHIFT_LEFT, tSRGBByPass, GET_CURRENT_BANK_NUMBER(), 18);
#else
        ScalerColorPCMOutputGammaAdjust(_1P_NORMAL_FULL_REGION, g_pucDISP_CALIBRATION_FLASH + _OCC_GAMMA10_ADDRESS, _OGC_FLASH_BANK);
        ScalerColorPCMSRGBAdjust(_1P_NORMAL_FULL_REGION, _SRGB_0_BIT_SHIFT_LEFT, tSRGBByPass, GET_CURRENT_BANK_NUMBER(), 18);

#endif

        ScalerTimerWaitForIDDomainEvent(_EVENT_DEN_STOP, _DISPLAY_PATH_ALL);

        ScalerColorOutputGammaEnable(_FUNCTION_ON);
        ScalerColorSRGBEnable(_FUNCTION_ON);
        ScalerColorPCMInputGammaEnable(_FUNCTION_ON);
        ScalerColorPCMRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_POLLING, _ON);

        ScalerColorBrightnessEnable(_FUNCTION_OFF);
        ScalerColorContrastEnable(_FUNCTION_OFF);

        if(g_ucPatternType == _PG_PATTERN)
        {
            ScalerDDomainPatternGenAdjustColor10bit(tOCC_SRGB_TABLE[0], tOCC_SRGB_TABLE[1], tOCC_SRGB_TABLE[2]);
        }
        else
        {
            ScalerDDomainBackgroundEnable(_DISPLAY_PATH_ALL, _FALSE);
        }
    }
    else
    {
        UserCommonDdcciDispCalibCalibPatternEnable(_DISABLE);
    }
#endif  // End of #if(_OCC_SUPPORT == _ON)

#if(_OGC_DICOM_SUPPORT == _ON)
    if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_FINAL_TYPE] == _DICOM_TYPE)
    {
        ScalerColorOutputGammaAdjust(_1P_NORMAL_FULL_REGION, g_pucDISP_CALIBRATION_FLASH + _OGC_DICOM_ADDRESS, _OGC_FLASH_BANK);

#if(_PCM_FUNCTION == _ON)
        ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
#endif

        ScalerColorBrightnessEnable(_FUNCTION_OFF);
        ScalerColorContrastEnable(_FUNCTION_OFF);

        ScalerColorSRGBEnable(_FUNCTION_OFF);
        UserCommonDdcciDispCalibCalibPatternEnable(_DISABLE);
    }
#endif  // End of #if(_OGC_DICOM_SUPPORT == _ON)
    ScalerColorOutputGammaEnable(_FUNCTION_ON);
}

//--------------------------------------------------
// Description  : Display Calibration Measure End CheckSum
// Input Value  : None
// Output Value : _SUCCESS/_FAIL
//--------------------------------------------------
BYTE UserCommonDdcciDispCalibCheckSum(void)
{
    BYTE ucFlag = 1;
#if(_UNIFORMITY_SUPPORT == _ON)
    WORD usI = 0;
    BYTE pucTemp[2] = {0, 0};
#endif

#if(_OGC_SUPPORT == _ON)
    if(((g_ucCalibrationType >> _OGC_TYPE) & 0x01) == _TRUE)
    {
        pData[1] = UserCommonDdcciDispCalibCalCheckSum(_OGC_TYPE);
        if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_OGC_CHKSUM] == pData[1])
        {
            UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_CHKSUM_ADDRESS, 1, &pData[1]);
            pData[4] = _OGC_SUPPORT;
            UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_FINISH_ADDRESS, 1, &pData[4]);
        }
        else
        {
            ucFlag = _BIT1;
        }
    }
#endif  // End of #if(_OGC_SUPPORT == _ON)

#if(_OCC_SUPPORT == _ON)
    if(((g_ucCalibrationType >> _OCC_TYPE) & 0x01) == _TRUE)
    {
        pData[2] = UserCommonDdcciDispCalibCalCheckSum(_OCC_TYPE);

        if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_OCC_CHKSUM] == pData[2])
        {
            UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_CHKSUM_ADDRESS, 1, &pData[2]);
            pData[4] = _OCC_SUPPORT;
            UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_FINISH_ADDRESS, 1, &pData[4]);
        }
        else
        {
            ucFlag |= _BIT2;
        }
    }
#endif  // End of #if(_OCC_SUPPORT == _ON)

#if(_OGC_DICOM_SUPPORT == _ON)
    if(((g_ucCalibrationType >> _DICOM_TYPE) & 0x01) == _TRUE)
    {
        pData[3] = UserCommonDdcciDispCalibCalCheckSum(_DICOM_TYPE);

        if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_DICOM_CHKSUM] == pData[3])
        {
            UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_DICOM_CHKSUM_ADDRESS, 1, &pData[3]);
            pData[4] = _OGC_DICOM_SUPPORT;
            UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_DICOM_FINISH_ADDRESS, 1, &pData[4]);
        }
        else
        {
            ucFlag |= _BIT3;
        }
    }
#endif  // End of #if(_OGC_DICOM_SUPPORT == _ON)

#if(_UNIFORMITY_SUPPORT == _ON)
    if(((g_ucUniformityChecksumType >> _UNIFORMITY_GAIN_TYPE) & 0x01) == _TRUE)
    {
        // level0, CYShih
        pucTemp[1] = 0;
        for(usI = tUNIFORMITY_TYPE_ADDRESS_INDEX[g_ucUniformityLUTStartPosIndex]; usI < (tUNIFORMITY_TYPE_ADDRESS_INDEX[g_ucUniformityLUTStartPosIndex] + _PANEL_UNIFORMITY_LUT_SIZE); usI++)
        {
            UserCommonFlashRead(g_ucUniformityLUTSaveBank, ((((WORD)_UNIFORMITY_FLASH_PAGE) << 12) + usI), 1, &pucTemp[0]);
            pucTemp[1] += pucTemp[0];
        }
        //
        UserCommonFlashWrite(g_ucUniformityLUTSaveBank, (((WORD)_UNIFORMITY_FLASH_PAGE) << 12) + tUNIFORMITY_TYPE_CHECKSUM_INDEX[g_ucUniformityLUTStartPosIndex], 1, &pucTemp[1]);
        UserCommonFlashRead(g_ucUniformityLUTSaveBank, (((WORD)_UNIFORMITY_FLASH_PAGE) << 12) + tUNIFORMITY_TYPE_CHECKSUM_INDEX[g_ucUniformityLUTStartPosIndex], 1, &pData[5]);

        if((g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_CHKSUM] == pData[5]) &&
           (pucTemp[1] == pData[5]))
        {
            if((g_ucUniformityLUTStartPosIndex + 1) == _UNIFORMITY_TOTAL_SET)
            {
                pData[4] = _UNIFORMITY_SUPPORT;
                UserCommonFlashWrite(_UNIFORMITY_FLASH_BANK0, (((WORD)_UNIFORMITY_FLASH_PAGE) << 12) + _UNIFORMITY_FINISH_ADDRESS, 1, &pData[4]);
            }
        }
        else
        {
            ucFlag |= _BIT4;
        }
    }
    // level0
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
    if(((g_ucUniformityChecksumType >> _UNIFORMITY_OFFSET_TYPE) & 0x01) == _TRUE)
    {
        // level0
        pucTemp[1] = 0;
        for(usI = tUNIFORMITY_TYPE_OFFSET_ADDRESS_INDEX[g_ucUniformityLUTStartPosIndex]; usI < (tUNIFORMITY_TYPE_OFFSET_ADDRESS_INDEX[g_ucUniformityLUTStartPosIndex] + _PANEL_UNIFORMITY_OFFSET_LUT_SIZE); usI++)
        {
            UserCommonFlashRead(tUNIFORMITY_TYPE_OFFSET_BANK_INDEX[g_ucUniformityLUTStartPosIndex], ((((WORD)_UNIFORMITY_FLASH_PAGE) << 12) + usI), 1, &pucTemp[0]);
            pucTemp[1] += pucTemp[0];
        }
        //
        UserCommonFlashWrite(tUNIFORMITY_TYPE_OFFSET_BANK_INDEX[g_ucUniformityLUTStartPosIndex], (((WORD)_UNIFORMITY_FLASH_PAGE) << 12) + tUNIFORMITY_TYPE_OFFSET_CHECKSUM_INDEX[g_ucUniformityLUTStartPosIndex], 1, &pucTemp[1]);
        UserCommonFlashRead(tUNIFORMITY_TYPE_OFFSET_BANK_INDEX[g_ucUniformityLUTStartPosIndex], (((WORD)_UNIFORMITY_FLASH_PAGE) << 12) + tUNIFORMITY_TYPE_OFFSET_CHECKSUM_INDEX[g_ucUniformityLUTStartPosIndex], 1, &pData[5]);

        if((g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_CHKSUM] == pData[5]) &&
           (pucTemp[1] == pData[5]))
        {
            if((g_ucUniformityLUTStartPosIndex + 1) == _UNIFORMITY_TOTAL_SET)
            {
                pData[4] = _UNIFORMITY_LEVEL0_SUPPORT;
                UserCommonFlashWrite(_UNIFORMITY_TYPE1_OFFSET_BANK, (((WORD)_UNIFORMITY_FLASH_PAGE) << 12) + _UNIFORMITY_OFFSET_FINISH_ADDRESS, 1, &pData[4]);
            }
        }
        else
        {
            ucFlag |= _BIT4;
        }
    }
    if(((g_ucUniformityChecksumType >> _UNIFORMITY_DECAY_TYPE) & 0x01) == _TRUE)
    {
        // level0
        pucTemp[1] = 0;
        for(usI = tUNIFORMITY_TYPE_DECAY_ADDRESS_INDEX[g_ucUniformityLUTStartPosIndex]; usI < (tUNIFORMITY_TYPE_DECAY_ADDRESS_INDEX[g_ucUniformityLUTStartPosIndex] + _PANEL_UNIFORMITY_DECAY_LUT_SIZE); usI++)
        {
            UserCommonFlashRead(tUNIFORMITY_TYPE_DECAY_BANK_INDEX[g_ucUniformityLUTStartPosIndex], ((((WORD)_UNIFORMITY_FLASH_PAGE) << 12) + usI), 1, &pucTemp[0]);
            pucTemp[1] += pucTemp[0];
        }
        //
        UserCommonFlashWrite(tUNIFORMITY_TYPE_DECAY_BANK_INDEX[g_ucUniformityLUTStartPosIndex], (((WORD)_UNIFORMITY_FLASH_PAGE) << 12) + tUNIFORMITY_TYPE_DECAY_CHECKSUM_INDEX[g_ucUniformityLUTStartPosIndex], 1, &pucTemp[1]);
        UserCommonFlashRead(tUNIFORMITY_TYPE_DECAY_BANK_INDEX[g_ucUniformityLUTStartPosIndex], (((WORD)_UNIFORMITY_FLASH_PAGE) << 12) + tUNIFORMITY_TYPE_DECAY_CHECKSUM_INDEX[g_ucUniformityLUTStartPosIndex], 1, &pData[5]);

        if((g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_CHKSUM] != pData[5]) ||
           (pucTemp[1] != pData[5])) // do not set bit0 in flash
        {
            ucFlag |= _BIT4;
        }
    }
#endif
#endif  // End of #if(_UNIFORMITY_SUPPORT == _ON)

    return ucFlag;
}

//--------------------------------------------------
// Description  : Display Calibration OCC Measure End Matrix CheckSum
// Input Value  : ucCheckType: 5- color matrix
// Output Value : _SUCCESS/_FAIL
//--------------------------------------------------
BYTE UserCommonDdcciDispCalibMatrixCheckSum(BYTE ucCheckType)
{
    BYTE ucFlag = 1;
    BYTE pucTemp[2] = {0, 0};

    switch(ucCheckType)
    {
        case _COLOR_MATRIX_TYPE:

            pucTemp[0] = UserCommonDdcciDispCalibCalCheckSum(_COLOR_MATRIX_TYPE);

            if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX_CHECKSUM] == pucTemp[0])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_COLOR_MATRIX_CHKSUM_ADDRESS, 1, &pucTemp[0]);
            }
            else
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OCC_COLOR_MATRIX_CHKSUM_ADDRESS, 1, &pucTemp[0]);
                ucFlag |= _BIT2;
            }

            break;

#if(_ULTRA_HDR_SUPPORT == _ON)
        case _HDR_TYPE:

            pucTemp[0] = UserCommonDdcciDispCalibCalCheckSum(_HDR_TYPE);

            if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_COLORMATRIX_CHECKSUM] == pucTemp[0])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _HDR_CHKSUM_ADDRESS, 1, &pucTemp[0]);
                pucTemp[1] = _ULTRA_HDR_SUPPORT;
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _HDR_FINISH_ADDRESS, 1, &pucTemp[1]);
            }
            else
            {
                ucFlag |= _BIT2;
            }

            break;
#endif
        case _RGB_GAIN_TYPE:

#if(_OGC_SUPPORT == _ON)
            pucTemp[0] = UserCommonDdcciDispCalibCalCheckSum(_RGB_GAIN_TYPE);

            if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_RGB_GAIN_CHKSUM] == pucTemp[0])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_RGB_GAIN_CHKSUM_ADDRESS, 1, &pucTemp[0]);
            }
            else
            {
                ucFlag = _BIT2;
            }
#endif
            pucTemp[1] = UserCommonDdcciDispCalibCalCheckSum(_HEADER_TYPE);

            if(g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_HEADER_CHKSUM] == pucTemp[1])
            {
                UserCommonFlashWrite(_OGC_FLASH_BANK, (((WORD)_OGC_FLASH_PAGE) << 12) + _OGC_HEADER_CHKSUM_ADDRESS, 1, &pucTemp[1]);
            }
            else
            {
                ucFlag |= _BIT2;
            }
            break;

        default:

            break;
    }

    return ucFlag;
}

//--------------------------------------------------
// Description  : Display Calibration Reply Results
// Input Value  : ucType --> Pass or other Fail Errors
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciDispCalibReplyResult(BYTE ucType)
{
    g_pucDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
    g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x04;

    switch(ucType)
    {
        case _DISP_CALIB_START:

            g_pucDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
            g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x04;
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_OGCOCCDICOM_SUPPORT] = (_ULTRA_HDR_SUPPORT << 4) | (_OGC_DICOM_SUPPORT << 2) | (_OCC_SUPPORT << 1) | (_OGC_SUPPORT);
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_OGC_TOTAL_GAMMA] = _OGC_TOTAL_GAMMA;
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_OGC_TOTAL_CT] = _OGC_TOTAL_CT;
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_PANEL_BITNUM] = ((_PANEL_DISP_BIT_MODE << 4) | _OCC_LUT_MODE);
//            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_PANEL_BITNUM] = (_PANEL_DISP_BIT_MODE );
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_PANEL_BITNUM + 1] = UserCommonDdcciCalCheckSum();

            break;

        case _DISP_CALIB_PASS:

            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_1] = 'P';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_2] = 'A';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_3] = 'S';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_4] = 'S';

            break;

        case _DISP_CALIB_ERASE_ERROR:

            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_1] = 'E';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_2] = 'R';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_3] = 'A';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_4] = 'S';

            break;

        case _DISP_CALIB_FW_ERROR:

            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_1] = 'F';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_2] = 'W';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_3] = 'E';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_4] = g_ucCalibrationType;

            break;

        case _DISP_CALIB_CRC_ERROR:

            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_1] = 'C';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_2] = 'R';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_3] = 'C';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_4] = 'E';

            break;

        case _DISP_CALIB_FAIL:

        default:

            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_1] = 'F';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_2] = 'A';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_3] = 'I';
            g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_4] = 'L';

            break;
    }

    g_pucDdcciTxBuf[_DDCCI_DISP_CALIB_STRING_4 + 1] = UserCommonDdcciCalCheckSum();

    ScalerMcuDdcciSendData(GET_RUN_DDCCI_HANDLE_CHANNEL(), g_pucDdcciTxBuf);

    EX1 = 1;
}
//--------------------------------------------------
// Description  : Save OGC/OCC Header
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciDispCalibSaveHeader(void)
{
    // UserCommonFlashWrite(_OGC_FLASH_BANK, 0x0030, g_pucDdcciRxBuf[1] & 0x7F, g_pucDdcciRxBuf);
    //==========Write OGC Header============
    pData[0] = 0x11;
    pData[1] = 0x11;
    pData[2] = _OGC_HEADER_LENGTH;
    pData[3] = g_pucDdcciRxBuf[_OGC_HEADER_IF_DO_OGC]; // 1: Do OGC; 0: not do OGC, even if OGC SUPPORT is on
    UserCommonFlashWrite(_OGC_FLASH_BANK, _OGC_HEADER_ADDRESS, 4, pData);
    UserCommonFlashWrite(_OGC_FLASH_BANK, _OGC_HEADER_ADDRESS + 4, 2 + _OGC_TOTAL_GAMMA + _OGC_TOTAL_CT, g_pucDdcciRxBuf + _OGC_HEADER_GAMMA_CT_INDEX);
    // Gamma Number, Gamma Index1, GammaIndex2,..., Gamma Index n;
    // CT Numer, CT Index1, CT Index 2, ..., CT Index n.

    //==========Write OCC Header============
    pData[0] = 0x22;
    pData[1] = 0x22;
    pData[2] = _OCC_HEADER_LENGTH;
    pData[3] = g_pucDdcciRxBuf[_OCC_HEADER_IF_DO_OCC]; // 1: do OCC; 0: not do OCC, even if OCC support is on
    pData[4] = g_pucDdcciRxBuf[_OCC_HEADER_MATRIX_NUMBER]; // Matrix Number:3/2/1. 1st is sRGB, 2nd is Adobe, 3rd is SoftProof
    UserCommonFlashWrite(_OGC_FLASH_BANK, _OCC_HEADER_ADDRESS, 5, pData);
    //==========Write DICOM Header============
    pData[0] = 0x33;
    pData[1] = 0x33;
    pData[2] = _DICOM_HEADER_LENGTH;
    pData[3] = g_pucDdcciRxBuf[_DICOM_HEADER_IF_DO_DICOM];
    pData[4] = g_pucDdcciRxBuf[_DICOM_HEADER_MODE]; // 0 - By RGB Mode; 1- By Gray Mod
    UserCommonFlashWrite(_OGC_FLASH_BANK, _DICOM_HEADER_ADDRESS, 5, pData);

    //==========Write White Lv Header============
    pData[0] = 0x44;
    pData[1] = 0x44;
    pData[2] = _WHITE_LV_HEADER_LENGTH;
    pData[3] = g_pucDdcciRxBuf[_WHITE_LV_HEADER];
    pData[4] = g_pucDdcciRxBuf[_WHITE_LV_HEADER + 1];
    UserCommonFlashWrite(_OGC_FLASH_BANK, _WHITE_LV_HEADER_ADDRESS, 5, pData);
}

#if(_UNIFORMITY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Display Calibration Reply PCM Matrix
// Input Value  : ucPCMType --> _PCM_OSD_SRGB or ADOBE_RGB
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciDispCalibReplyOCCMatrix(BYTE ucPCMType)
{
    /*if(g_ucUniformityLUTSaveBank < MCU_FFFD_XDATA_BANK_START)
    {
        return _FALSE;
    }*/

    WORD usReadStartPos = 0;
    WORD usTotalLength = 18;
    BYTE ucSendLength = 13;
    BYTE ucBank = 0;

#if(_OCC_LUT_MODE == _ON)
    usTotalLength = 306;
#endif

    ucBank = MCU_FFFE_XDATA_BANK_SEL;
    MCU_FFFE_XDATA_BANK_SEL = g_ucUniformityLUTSaveBank - MCU_FFFD_XDATA_BANK_START;

    g_pucDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;

    usReadStartPos = (WORD)ucSendLength * (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX] >> 3);

    ucSendLength = ((usTotalLength - usReadStartPos) < 13) ? (usTotalLength - usReadStartPos) : 13;

    switch(ucPCMType)
    {
        case _PCM_SRGB:

            g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OCC_SRGBMATRIX_ADDRESS + (WORD)usReadStartPos, ucSendLength, g_pucDdcciTxBuf + _DDCCI_COMMAND);
            g_pucDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

            break;

        case _PCM_ADOBE_RGB:

            g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
            UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OCC_ADOBEMATRIX_ADDRESS + (WORD)usReadStartPos, ucSendLength, g_pucDdcciTxBuf + _DDCCI_COMMAND);
            g_pucDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

            break;

        default:
            break;
    }

    MCU_FFFE_XDATA_BANK_SEL = ucBank;

    // ScalerMcuDdcciSendData(g_pucDdcciTxBuf);
    ScalerMcuDdcciSendData(GET_RUN_DDCCI_HANDLE_CHANNEL(), g_pucDdcciTxBuf);

    EX1 = 1;
}

//--------------------------------------------------
// Description  : Display Calibration Reply OGC Header
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciDispCalibReplyOGCHeader(void)
{
    WORD usReadStartPos = 0;
    BYTE ucSendLength = 13;
    BYTE ucBank = 0;

    ucBank = MCU_FFFE_XDATA_BANK_SEL;
    MCU_FFFE_XDATA_BANK_SEL = _OGC_FLASH_BANK - MCU_FFFD_XDATA_BANK_START;

    g_pucDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;

    usReadStartPos = (WORD)ucSendLength * (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_UNIFORMITY_INDEX] & 0x01);

    ucSendLength = ((_OGC_HEADER_LENGTH - usReadStartPos) < 13) ? (_OGC_HEADER_LENGTH - usReadStartPos) : 13;

    g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | ucSendLength;
    UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) + _OGC_HEADER_ADDRESS + usReadStartPos, ucSendLength, g_pucDdcciTxBuf + _DDCCI_COMMAND);
    g_pucDdcciTxBuf[_DDCCI_COMMAND + ucSendLength] = UserCommonDdcciCalCheckSum();

    MCU_FFFE_XDATA_BANK_SEL = ucBank;

    // ScalerMcuDdcciSendData(g_pucDdcciTxBuf);
    ScalerMcuDdcciSendData(GET_RUN_DDCCI_HANDLE_CHANNEL(), g_pucDdcciTxBuf);

    EX1 = 1;
}

//--------------------------------------------------
// Description  : Display Calibration Reply Define, which Uniformity Tool Needs
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciDispCalibReplyUniformityDefine(void)
{
    g_pucDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
    g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x08;
    g_pucDdcciTxBuf[2] = (_PANEL_UNIFORMITY_MULTI_LUT_MODE << 4) | (_OCC_LUT_MODE << 3) | (_UNIFORMITY_TOTAL_SET & 0x07);
    g_pucDdcciTxBuf[3] = _PANEL_UNIFORMITY_HOR_INTERVAL;
    g_pucDdcciTxBuf[4] = _PANEL_DH_WIDTH & 0xFF;
    g_pucDdcciTxBuf[5] = ((WORD)_PANEL_DH_WIDTH >> 8) & 0xFF;
    g_pucDdcciTxBuf[6] = _PANEL_DV_HEIGHT & 0xFF;
    g_pucDdcciTxBuf[7] = ((WORD)_PANEL_DV_HEIGHT >> 8) & 0xFF;
    g_pucDdcciTxBuf[8] = _OGC_TOTAL_CT & 0x07;
    // Level0, CYShih
    // Offset
    g_pucDdcciTxBuf[9] = (_UNIFORMITY_OFFSET_TYPE5 << 5) | (_UNIFORMITY_OFFSET_TYPE4 << 4) | (_UNIFORMITY_OFFSET_TYPE3 << 3) |
                         (_UNIFORMITY_OFFSET_TYPE2 << 2) | (_UNIFORMITY_OFFSET_TYPE1 << 1) | _UNIFORMITY_OFFSET_TYPE0;
    g_pucDdcciTxBuf[10] = UserCommonDdcciCalCheckSum();// CYShih, 8

    // g_pucDdcciTxBuf[8] = UserCommonDdcciCalCheckSum();

    // ScalerMcuDdcciSendData(g_pucDdcciTxBuf);
    ScalerMcuDdcciSendData(GET_RUN_DDCCI_HANDLE_CHANNEL(), g_pucDdcciTxBuf);

    EX1 = 1;
}
//--------------------------------------------------
// Description  : Reply the CCT gain to uniformity tool
// Input Value  : ucCTGammaIndex, the set of CT and gamma
// Output Value : None
//--------------------------------------------------
void UserCommonDdcciDispCalibReplyCCTGain(void)
{
    BYTE ucGammaIndex = 0;
    BYTE ucColorTempIndex = 0;
    BYTE pucTemp[6] = {0, 0, 0, 0, 0, 0};
    ucGammaIndex = (g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_INDEX] >> 4) & 0x0F;
    ucColorTempIndex = g_pucDdcciRxBuf[_DDCCI_DISP_CALIB_INDEX] & 0x0F;
    if(ucColorTempIndex != 0x0F)
    {
        UserCommonFlashRead(_OGC_FLASH_BANK, ((WORD)_OGC_FLASH_PAGE << 12) | (ucColorTempIndex * _OGC_TOTAL_GAMMA * 6 + ucGammaIndex * 6 + _OGC_RGB_GAIN_ADDRESS), 6, pucTemp);
    }
    else
    {
        pucTemp[0] = 0x08;
        pucTemp[1] = 0x00;
        pucTemp[2] = 0x08;
        pucTemp[3] = 0x00;
        pucTemp[4] = 0x08;
        pucTemp[5] = 0x00;
    }
    g_pucDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;
    g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x06;
    g_pucDdcciTxBuf[2] = pucTemp[0];// R
    g_pucDdcciTxBuf[3] = pucTemp[1];
    g_pucDdcciTxBuf[4] = pucTemp[2];// G
    g_pucDdcciTxBuf[5] = pucTemp[3];
    g_pucDdcciTxBuf[6] = pucTemp[4];// B
    g_pucDdcciTxBuf[7] = pucTemp[5];
    g_pucDdcciTxBuf[8] = UserCommonDdcciCalCheckSum();// CYShih, 8

    // ScalerMcuDdcciSendData(g_pucDdcciTxBuf);
    ScalerMcuDdcciSendData(GET_RUN_DDCCI_HANDLE_CHANNEL(), g_pucDdcciTxBuf);

    EX1 = 1;
}
#endif // End of #if(_UNIFORMITY_SUPPORT == _ON)

#endif // End of #if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON) || (_UNIFORMITY_SUPPORT == _ON))
