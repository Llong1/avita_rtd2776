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
// ID Code      : UserCommonModeSearch.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_MODESEARCH__

#include "UserCommonInclude.h"

#if(_VGA_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//--------------------------------------------------
// Definitions of FIFO Mode Match Status
//--------------------------------------------------
#define _MODE_NOT_EXIST_IN_FIFO                     251

//--------------------------------------------------
// Definitions of VTotal Tolerance For Preset Mode
//--------------------------------------------------
#define _PRESET_MODE_VTOTAL_TOLERANCE               2

//--------------------------------------------------
// Definitions of V Height Tolerance For Preset Mode
//--------------------------------------------------
#define _PRESET_MODE_VHEIGHT_TOLERANCE              2

//--------------------------------------------------
// Definitions of The Diffrence Between GTF Height and Mode Table Height
//--------------------------------------------------
#define _USER_MODE_VHEIGHT_GTF_DIFF_TOL             20
#define _USER_MODE_VHEIGHT_GTF_DIFF_MIN             3

//--------------------------------------------------
// Definitions of H Ratio (IHWidth/IHTotal) Tolerance
//--------------------------------------------------
#define _H_RATIO_TOLERANCE                          150

//--------------------------------------------------
// Marcos for Extracting Mode Table Information
//--------------------------------------------------
#define GET_MODE_TABLE_POLARITY(x)                  ((x).ucMiscFlag & 0x0F)
#define GET_MODE_TABLE_INTERLACED(x)                ((bit)(((x).ucMiscFlag & _INTERLACE_MODE) >> 5))
#define GET_MODE_TABLE_VIDEO(x)                     ((bit)((x).ucMiscFlag & (_VIDEO_MODE_GROUP1 | _VIDEO_MODE_GROUP2 | _VIDEO_MODE_GROUP3)))

//--------------------------------------------------
// Macro of Mode Search Type
//--------------------------------------------------
#define GET_MODE_SEARCH_TYPE()                      ((bit)(g_ucModeCtrl & _BIT0))
#define SET_MODE_SEARCH_TYPE(x)                     (g_ucModeCtrl = ((g_ucModeCtrl & ~(_BIT0)) | ((x) << 0)))

//--------------------------------------------------
// Macro of Input Mode GTF Height
//--------------------------------------------------
#define GET_INPUT_MODE_GTF_HEIGHT()                 (g_usCurrGTFValue)
#define SET_INPUT_MODE_GTF_HEIGHT(x)                (g_usCurrGTFValue = (x))


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//--------------------------------------------------
// Check Mode VGA Result Enum
//--------------------------------------------------
typedef enum
{
    _MODE_INDIRECT_DEFLECTION_PIC = 0,
    _MODE_DIRECT_DEFLECTION_PIC,
    _MODE_INDIRECT_MIN_CLOCK,
    _MODE_DIRECT_MIN_CLOCK,
    _MODE_INDIRECT_SUCCESS,
    _MODE_DIRECT_SUCCESS,
}EnumModeFrameSyncGradeResult;


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE g_ucModeCtrl;
WORD g_usCurrGTFValue;


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
BYTE UserCommonModeSearchModeVGA(void);
bit UserCommonModeSearchOORModeByMeasureInfo(void);
BYTE UserCommonModeSearchPresetMode(void);
BYTE UserCommonModeSearchUserMode(void);
bit UserCommonModeSearchCheckPresetMode(BYTE ucModeIndex);
bit UserCommonModeSearchCheckUserModeMode(BYTE ucModeIndex);
BYTE UserCommonModeSearchBestMode(BYTE ucCurrModeIndex, BYTE ucLastModeIndex);
bit UserCommonModeSearchCheckModeSetting(BYTE ucModeIndex);
bit UserCommonModeSearchPresetModeCheckOOR(BYTE ucModeIndex);
BYTE UserCommonModeSearchCompareByMultipleCondition(BYTE ucCurrModeIndex, BYTE ucLastModeIndex);

#if(_MODE_SEARCH_BY_ACTIVE_MEASURE_SUPPORT == _ON)
bit UserCommonModeSearchCompareIVHeight(BYTE ucLastModeIndex, BYTE ucCurrModeIndex, BYTE *pucModeBestInx);
#endif // #if(_MODE_SEARCH_BY_ACTIVE_MEASURE_SUPPORT == _ON)

WORD UserCommonModeSearchGetHeightByGTF(WORD usVTotal, WORD usVFreq);
bit UserCommonModeSearchCheckHFreq(BYTE ucLastModeCnt, BYTE ucCurrentModeCnt, BYTE *pucModeBestInx);
bit UserCommonModeSearchCheckVFreq(BYTE ucLastModeCnt, BYTE ucCurrentModeCnt, BYTE *pucModeBestInx);
bit UserCommonModeSearchCheckGTFHeight(BYTE ucLastModeCnt, BYTE ucCurrentModeCnt, BYTE *pucModeBestInx);
bit UserCommonModeSearchHVSyncPulseCheck(BYTE ucLastModeCnt, BYTE ucCurrentModeCnt, BYTE *pucModeBestInx);
bit UserCommonModeSearchCompareByPolarity(BYTE ucLastModeCnt, BYTE ucCurrentModeCnt, BYTE *pucModeBestInx);
bit UserCommonModeSearchCompareByInterlace(BYTE ucLastModeCnt, BYTE ucCurrentModeCnt, BYTE *pucModeBestInx);
bit UserCommonModeSearchCompareByVideoModeFlg(BYTE ucLastModeCnt, BYTE ucCurrentModeCnt, BYTE *pucModeBestInx);
void UserCommonModeSearchFIFOSaveModeInfo(BYTE ucIndex);
BYTE UserCommonModeSearchCheckFIFOModeSaved(BYTE ucModeIndex);
void UserCommonModeSearchInitalUserAndCenterData(BYTE ucIndex);
void UserCommonModeSearchUpdateInputDataRefModeTbl(BYTE ucIndex);
void UserCommonModeSearchUpdateInputDataRefFIFO(BYTE ucFifoIndex, BYTE ucIndex);
BYTE UserCommonModeSearchGetModeVideoType(BYTE ucIndex);
bit UserCommonModeSearchCheckFIFOSetting(StructVGAModeUserDataType stFifoUserData, BYTE ucModeIndex);
WORD UserCommonModeSearchGetModetableTimingDataItem(BYTE ucModeNumber, EnumTimingInfoSelect enumTimingInfo);
bit UserCommonModeSearchCheckPresetModeTable(BYTE ucMatchmode);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : Search mode for VGA
// Input Value  : None
// Output Value : Mode number
//--------------------------------------------------
BYTE UserCommonModeSearchModeVGA(void)
{
    BYTE ucModeIndex = _MODE_NOSUPPORT;

    SysRegionSetMeasureResultPointerRegion(SysVgaGetRegion());

    // Check OOR Mode By Measure Information.
    if(UserCommonModeSearchOORModeByMeasureInfo() == _TRUE)
    {
        return _MODE_NOSUPPORT;
    }

    // Search Preset Mode
    ucModeIndex = UserCommonModeSearchPresetMode();

    if((ucModeIndex < _MAX_PRESET_MODE) && (UserCommonModeSearchPresetModeCheckOOR(ucModeIndex) == _TRUE))
    {
        DebugMessageAnalog("Pixel Rate Over 220M ", GET_ADC_LIMIT_CLOCK());

        return _MODE_NOSUPPORT;
    }

    // Check Result
    if(ucModeIndex >= _MAX_PRESET_MODE)
    {
        // Search User Mode
        ucModeIndex = UserCommonModeSearchUserMode();

        DebugMessageAnalog("User Mode Search Mode No. ", ucModeIndex);
    }

    if(ucModeIndex < _MAX_PRESET_MODE)
    {
        // User Check ModeIndex
        ucModeIndex = UserInterfaceGetVGAConfuseMode(ucModeIndex);

        // Save FIFO Mode
        UserCommonModeSearchFIFOSaveModeInfo(ucModeIndex);
    }

    DebugMessageAnalog("3. ucModeIndex_FIFO", ucModeIndex);

    return ucModeIndex;
}

//--------------------------------------------------
// Description  : Search fit OOR Mode
// Input Value  : None
// Output Value : _TRUE : is OOR Mode
//             _FALSE: not OOR Mode
//--------------------------------------------------
bit UserCommonModeSearchOORModeByMeasureInfo(void)
{
    if((GET_INPUT_TIMING_HFREQ() < _OOR_H_FREQ_LOWER_BOUND) ||
       (GET_INPUT_TIMING_HFREQ() > _OOR_H_FREQ_UPPER_BOUND) ||
       (GET_INPUT_TIMING_VFREQ() < _OOR_V_FREQ_LOWER_BOUND) ||
       (GET_INPUT_TIMING_VFREQ() > _OOR_V_FREQ_UPPER_BOUND))
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Search Preset Mode
// Input Value  : None
// Output Value : ModeIndex
//--------------------------------------------------
BYTE UserCommonModeSearchPresetMode(void)
{
    BYTE ucCnt = 0;
    BYTE ucBestModeIndex = _MODE_NOSUPPORT;

    for(ucCnt = 0; ucCnt < _MAX_PRESET_MODE; ++ucCnt)
    {
        if(UserCommonModeSearchCheckPresetMode(ucCnt) == _TRUE)
        {
            DebugMessageAnalog("4. PresetMode Number =", ucCnt);

            ucBestModeIndex = UserCommonModeSearchBestMode(ucCnt, ucBestModeIndex);
        }
    }

    return ucBestModeIndex;
}

//--------------------------------------------------
// Description  : Search User Mode
// Input Value  : None
// Output Value : ModeIndex
//--------------------------------------------------
BYTE UserCommonModeSearchUserMode(void)
{
    BYTE ucCnt = 0;
    BYTE ucBestModeIndex = _MODE_NOSUPPORT;

    SET_INPUT_MODE_GTF_HEIGHT(UserCommonModeSearchGetHeightByGTF(GET_INPUT_TIMING_VTOTAL(), GET_INPUT_TIMING_VFREQ()));

    DebugMessageAnalog("2. GTF Height = ", GET_INPUT_MODE_GTF_HEIGHT());

    // Search Best Mode
    for(ucCnt = 0; ucCnt < _MAX_PRESET_MODE; ++ucCnt)
    {
        if(UserCommonModeSearchCheckUserModeMode(ucCnt) == _TRUE)
        {
            DebugMessageAnalog("4. UserMode Number =", ucCnt);

            ucBestModeIndex = UserCommonModeSearchBestMode(ucCnt, ucBestModeIndex);
        }
    }

    return ucBestModeIndex;
}

//--------------------------------------------------
// Description  : Preset Mode Flag Initial
// Input Value  : ModeIndex
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit UserCommonModeSearchCheckPresetMode(BYTE ucModeIndex)
{
    if(abs(GET_INPUT_TIMING_VFREQ() - tINPUTMODE_PRESET_TABLE[ucModeIndex].usIVFreq) > tINPUTMODE_PRESET_TABLE[ucModeIndex].ucIVFreqTolerance)
    {
        return _FALSE;
    }

    if(abs(GET_INPUT_TIMING_HFREQ() - tINPUTMODE_PRESET_TABLE[ucModeIndex].usIHFreq) > tINPUTMODE_PRESET_TABLE[ucModeIndex].ucIHFreqTolerance)
    {
        return _FALSE;
    }

    if(abs(GET_INPUT_TIMING_VTOTAL() - tINPUTMODE_PRESET_TABLE[ucModeIndex].usIVTotal) > _PRESET_MODE_VTOTAL_TOLERANCE)
    {
        return _FALSE;
    }

    SET_MODE_SEARCH_TYPE(_PRESET_MODE_TYPE);

    return _TRUE;
}

//--------------------------------------------------
// Description  : User Mode Flag Initial
// Input Value  : ModeIndex
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit UserCommonModeSearchCheckUserModeMode(BYTE ucModeIndex)
{
    if(abs(GET_INPUT_MODE_GTF_HEIGHT() - UserCommonModeSearchGetHeightByGTF(tINPUTMODE_PRESET_TABLE[ucModeIndex].usIVTotal, tINPUTMODE_PRESET_TABLE[ucModeIndex].usIVFreq)) > _USER_MODE_VHEIGHT_GTF_DIFF_TOL)
    {
        return _FALSE;
    }

    // Set User Mode Flag
    SET_MODE_SEARCH_TYPE(_USER_MODE_TYPE);

    return _TRUE;
}

//--------------------------------------------------
// Description  : Search the Best Mode between two ModeIndex.
// Input Value  : ucCurrModeIndex --> Current mode number index
//                ucLastModeIndex --> Last mode number index
// Output Value : Best mode number index
//--------------------------------------------------
BYTE UserCommonModeSearchBestMode(BYTE ucCurrModeIndex, BYTE ucLastModeIndex)
{
    if(UserCommonModeSearchCheckModeSetting(ucCurrModeIndex) == _FALSE)
    {
        DebugMessageAnalog("2. Current Mode have problem", ucLastModeIndex);

        return ucLastModeIndex;
    }

    if(ucLastModeIndex >= _MAX_PRESET_MODE)
    {
        DebugMessageAnalog("2. Find Out First Mode", ucCurrModeIndex);

        return ucCurrModeIndex;
    }
    else
    {
        return UserCommonModeSearchCompareByMultipleCondition(ucCurrModeIndex, ucLastModeIndex);
    }

    return ucLastModeIndex;
}

//--------------------------------------------------
// Description  : Check Mode Setting in System
// Input Value  : ModeIndex
// Output Value : _TRUE: The Mode Setting is ok.
//--------------------------------------------------
bit UserCommonModeSearchCheckModeSetting(BYTE ucModeIndex)
{
    if(ucModeIndex >= _MAX_PRESET_MODE)
    {
        return _FALSE;
    }

    if(GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE)
    {
        // InputMode.IHTotal should be less than IHTotal Maximum.
        if(tINPUTMODE_PRESET_TABLE[ucModeIndex].usIHTotal > GET_ADC_LIMIT_CLOCK())
        {
            return _FALSE;
        }
    }

    // Measured IVTotal should be greater than ModeTable.IVHeight
    if(GET_INPUT_TIMING_VTOTAL() <= tINPUTMODE_PRESET_TABLE[ucModeIndex].usIVHeight)
    {
        return _FALSE;
    }

    // Mode table self cheking condition
    if(tINPUTMODE_PRESET_TABLE[ucModeIndex].usIHTotal <= (tINPUTMODE_PRESET_TABLE[ucModeIndex].usIHStartPos + tINPUTMODE_PRESET_TABLE[ucModeIndex].usIHWidth))
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Preset Mode OOR Check
// Input Value  : ModeIndex
// Output Value : _TRUE --> OOR
//--------------------------------------------------
bit UserCommonModeSearchPresetModeCheckOOR(BYTE ucModeIndex)
{
    // InputMode.IHTotal should be less than IHTotal Maximum.
    if(tINPUTMODE_PRESET_TABLE[ucModeIndex].usIHTotal > GET_ADC_LIMIT_CLOCK())
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Compare IHWidth between two ModeIndex.
// Input Value  : ucCurrModeIndex --> Current mode number index
//                ucLastModeIndex --> Last mode number index
// Output Value : Best mode number index
//--------------------------------------------------
BYTE UserCommonModeSearchCompareByMultipleCondition(BYTE ucCurrModeIndex, BYTE ucLastModeIndex)
{
    BYTE ucBestModeInx = ucLastModeIndex;

#if(_MODE_SEARCH_BY_ACTIVE_MEASURE_SUPPORT == _ON)
    DWORD ulRatioM = 0;
#endif // End of #if(_MODE_SEARCH_BY_ACTIVE_MEASURE_SUPPORT == _ON)

    DWORD ulRatio1 = 0;
    DWORD ulRatio2 = 0;

    if((ucCurrModeIndex >= _MAX_PRESET_MODE) && (ucLastModeIndex >= _MAX_PRESET_MODE))
    {
        return _MODE_NOSUPPORT;
    }
    else if(ucCurrModeIndex >= _MAX_PRESET_MODE)
    {
        return ucLastModeIndex;
    }
    else if(ucLastModeIndex >= _MAX_PRESET_MODE)
    {
        return ucCurrModeIndex;
    }

    if(GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE)
    {
        if(UserCommonModeSearchCheckHFreq(ucLastModeIndex, ucCurrModeIndex, &ucBestModeInx) == _TRUE)
        {
            DebugMessageAnalog("2. User Mode Detect By H-Freq", ucBestModeInx);

            return ucBestModeInx;
        }
        else if(UserCommonModeSearchCheckVFreq(ucLastModeIndex, ucCurrModeIndex, &ucBestModeInx) == _TRUE)
        {
            DebugMessageAnalog("2. User Mode Detect By V-Freq", ucBestModeInx);

            return ucBestModeInx;
        }
        else if(UserCommonModeSearchCheckGTFHeight(ucLastModeIndex, ucCurrModeIndex, &ucBestModeInx) == _TRUE)
        {
            DebugMessageAnalog("2. User Mode Detect By GTF Height Closer", ucBestModeInx);

            return ucBestModeInx;
        }

        DebugMessageAnalog("2. User Mode Continue PK By Muti Condition", ucBestModeInx);
    }

#if(_MODE_SEARCH_BY_ACTIVE_MEASURE_SUPPORT == _ON)
    //////////////////////////////////////////////////////////////////////
    //  Ming-Yen :                                                      //
    //                                                                  //
    //                     Measured IHWidth (By Active Measurement)     //
    //  Measured Ratio = --------------------------------------------   //
    //                                g_usAdcClockLimit                 //
    //                                                                  //
    //                                                                  //
    //                             IHWidth 1                            //
    //  R1 (Ratio of Mode 1) = -----------------                        //
    //                             IHTotal 1                            //
    //                                                                  //
    //                                                                  //
    //                             IHWidth 2                            //
    //  R2 (Ratio of Mode 2) = -----------------                        //
    //                             IHTotal 2                            //
    //                                                                  //
    //                                                                  //
    //  If IHWidth 1 < IHWidth 2                                        //
    //                                                                  //
    //  We select Mode 1 if Measured Ration is in the range between     //
    //  R1 - (R2 - R1) * 25% and R1 + (R2 - R1) * 25%, otherwise        //
    //  Mode 2 will always be the winnner.                              //
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    ulRatioM = ((DWORD)GET_INPUT_TIMING_HWIDTH() * 10000 + (GET_INPUT_TIMING_HTOTAL() / 2)) / GET_INPUT_TIMING_HTOTAL();

#endif // End of #if(_MODE_SEARCH_BY_ACTIVE_MEASURE_SUPPORT == _ON)

    ulRatio1 = ((DWORD)tINPUTMODE_PRESET_TABLE[ucCurrModeIndex].usIHWidth * 10000 + (tINPUTMODE_PRESET_TABLE[ucCurrModeIndex].usIHTotal / 2)) / tINPUTMODE_PRESET_TABLE[ucCurrModeIndex].usIHTotal;
    ulRatio2 = ((DWORD)tINPUTMODE_PRESET_TABLE[ucLastModeIndex].usIHWidth * 10000 + (tINPUTMODE_PRESET_TABLE[ucLastModeIndex].usIHTotal / 2)) / tINPUTMODE_PRESET_TABLE[ucLastModeIndex].usIHTotal;

    if(UserCommonModeSearchHVSyncPulseCheck(ucLastModeIndex, ucCurrModeIndex, &ucBestModeInx) == _TRUE)
    {
        DebugMessageAnalog("2. Detect By Pulse", ucBestModeInx);
        return ucBestModeInx;
    }
    else if(UserCommonModeSearchCompareByInterlace(ucLastModeIndex, ucCurrModeIndex, &ucBestModeInx) == _TRUE)
    {
        DebugMessageAnalog("2. Detect By Interlace", ucBestModeInx);
        return ucBestModeInx;
    }
    else if(UserCommonModeSearchCompareByPolarity(ucLastModeIndex, ucCurrModeIndex, &ucBestModeInx) == _TRUE)
    {
        DebugMessageAnalog("2. Detect By Polarity", ucBestModeInx);
        return ucBestModeInx;
    }
    else if(UserCommonModeSearchCompareByVideoModeFlg(ucLastModeIndex, ucCurrModeIndex, &ucBestModeInx) == _TRUE)
    {
        DebugMessageAnalog("2. Detect By Video Flag", ucBestModeInx);
        return ucBestModeInx;
    }
#if(_MODE_SEARCH_BY_ACTIVE_MEASURE_SUPPORT == _ON)
    else if(UserCommonModeSearchCompareIVHeight(ucLastModeIndex, ucCurrModeIndex, &ucBestModeInx) == _TRUE)
    {
        DebugMessageAnalog("2. Detect By IVHeight", ucBestModeInx);
        return ucBestModeInx;
    }
    else if((ABSDWORD(ulRatio1, ulRatio2) > _H_RATIO_TOLERANCE) && (ABSDWORD(ulRatioM, ulRatio1) < ((ABSDWORD(ulRatio1, ulRatio2) + 2) / 4)))
    {
        DebugMessageAnalog("2. Detect By Width 1", ucCurrModeIndex);
        return ucCurrModeIndex;
    }
    else if((ABSDWORD(ulRatio1, ulRatio2) > _H_RATIO_TOLERANCE) && (ABSDWORD(ulRatioM, ulRatio2) < ((ABSDWORD(ulRatio1, ulRatio2) + 2) / 4)))
    {
        DebugMessageAnalog("2. Detect By Width 2", ucLastModeIndex);
        return ucLastModeIndex;
    }
#endif // End of #if(_MODE_SEARCH_BY_ACTIVE_MEASURE_SUPPORT == _ON)
    else
    {
        // Common case select the mode which have a bigger width
        if(tINPUTMODE_PRESET_TABLE[ucCurrModeIndex].usIHWidth > tINPUTMODE_PRESET_TABLE[ucLastModeIndex].usIHWidth)
        {
            DebugMessageAnalog("2. Detect By Bigger Width 1", ucCurrModeIndex);

            return ucCurrModeIndex;
        }
        else
        {
            DebugMessageAnalog("2. Detect By Bigger Width 2", ucLastModeIndex);

            return ucLastModeIndex;
        }
    }

    return ucLastModeIndex;
}

#if(_MODE_SEARCH_BY_ACTIVE_MEASURE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Compare IVHeight between two ModeIndex in preset mode group.
// Input Value  : ucCurrModeIndex --> Current mode number index
//                ucLastModeIndex --> Last mode number index
// Output Value : Mode number index
//--------------------------------------------------
bit UserCommonModeSearchCompareIVHeight(BYTE ucLastModeIndex, BYTE ucCurrModeIndex, BYTE *pucModeBestInx)
{
    if(tINPUTMODE_PRESET_TABLE[ucCurrModeIndex].usIVHeight == tINPUTMODE_PRESET_TABLE[ucLastModeIndex].usIVHeight)
    {
        return _FALSE;
    }

    if(tINPUTMODE_PRESET_TABLE[ucCurrModeIndex].usIVHeight > tINPUTMODE_PRESET_TABLE[ucLastModeIndex].usIVHeight)
    {
        if(GET_INPUT_TIMING_VHEIGHT() > (tINPUTMODE_PRESET_TABLE[ucLastModeIndex].usIVHeight + _PRESET_MODE_VHEIGHT_TOLERANCE))
        {
            *pucModeBestInx = ucCurrModeIndex;

            return _TRUE;
        }
    }
    else
    {
        if(GET_INPUT_TIMING_VHEIGHT() > (tINPUTMODE_PRESET_TABLE[ucCurrModeIndex].usIVHeight + _PRESET_MODE_VHEIGHT_TOLERANCE))
        {
            *pucModeBestInx = ucLastModeIndex;

            return _TRUE;
        }
    }

    return _FALSE;
}
#endif // End of #if(_MODE_SEARCH_BY_ACTIVE_MEASURE_SUPPORT == _ON)

//--------------------------------------------------
// Description : Get A Std Mode Height And Check Is Full
// Input Value  : Measured Height
// Output Value : Verified Height
//--------------------------------------------------
WORD UserCommonModeSearchGetHeightByGTF(WORD usVTotal, WORD usVFreq)
{
    /**********************************************************************************************
    // Cminimum : minimum time of vertical sync + back porch interval, default value is 550 (us) //
    // Cfrontporch : minimum front porch in lines(vertical),default value is 3 (lines)           //
    // Height = Vtotal / (1 + (Vfreq / (20000 / 11 - Vfreq))) - 3                                //
    // Height = Vtotal - (Vtotal * 11 * Vfreq / 200000) - 3                                      //
    **********************************************************************************************/
    return (usVTotal - (WORD)((DWORD)11 * usVTotal * usVFreq / 200000) - 3);
}

//--------------------------------------------------
// Description  : Check Mode By Horizontal Frequency
// Input Value  : ucCurrentModeCnt  --> Current ModeIndex
//                ucLastModeCnt     --> Last ModeIndex
//                pModeBestInx      --> Return ModeIndex Pointer
// Output Value : New ModeIndex
//--------------------------------------------------
bit UserCommonModeSearchCheckHFreq(BYTE ucLastModeCnt, BYTE ucCurrentModeCnt, BYTE *pucModeBestInx)
{
    if((abs(GET_INPUT_TIMING_HFREQ() - tINPUTMODE_PRESET_TABLE[ucLastModeCnt].usIHFreq) <= tINPUTMODE_PRESET_TABLE[ucLastModeCnt].ucIHFreqTolerance) &&
       (abs(GET_INPUT_TIMING_HFREQ() - tINPUTMODE_PRESET_TABLE[ucCurrentModeCnt].usIHFreq) > tINPUTMODE_PRESET_TABLE[ucCurrentModeCnt].ucIHFreqTolerance))
    {
        *pucModeBestInx = ucLastModeCnt;

        return _TRUE;
    }
    else if((abs(GET_INPUT_TIMING_HFREQ() - tINPUTMODE_PRESET_TABLE[ucCurrentModeCnt].usIHFreq) <= tINPUTMODE_PRESET_TABLE[ucCurrentModeCnt].ucIHFreqTolerance) &&
            (abs(GET_INPUT_TIMING_HFREQ() - tINPUTMODE_PRESET_TABLE[ucLastModeCnt].usIHFreq) > tINPUTMODE_PRESET_TABLE[ucLastModeCnt].ucIHFreqTolerance))
    {
        *pucModeBestInx = ucCurrentModeCnt;

        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check Mode By Vertical Frequency
// Input Value  : ucCurrentModeCnt  --> Current ModeIndex
//                ucLastModeCnt     --> Last ModeIndex
//                pModeBestInx      --> Return ModeIndex Pointer
// Output Value : New ModeIndex
//--------------------------------------------------
bit UserCommonModeSearchCheckVFreq(BYTE ucLastModeCnt, BYTE ucCurrentModeCnt, BYTE *pucModeBestInx)
{
    if((abs(GET_INPUT_TIMING_VFREQ() - tINPUTMODE_PRESET_TABLE[ucLastModeCnt].usIVFreq) <= tINPUTMODE_PRESET_TABLE[ucLastModeCnt].ucIVFreqTolerance) &&
       (abs(GET_INPUT_TIMING_VFREQ() - tINPUTMODE_PRESET_TABLE[ucCurrentModeCnt].usIVFreq) > tINPUTMODE_PRESET_TABLE[ucCurrentModeCnt].ucIVFreqTolerance))
    {
        *pucModeBestInx = ucLastModeCnt;

        return _TRUE;
    }
    else if((abs(GET_INPUT_TIMING_VFREQ() - tINPUTMODE_PRESET_TABLE[ucCurrentModeCnt].usIVFreq) <= tINPUTMODE_PRESET_TABLE[ucCurrentModeCnt].ucIVFreqTolerance) &&
            (abs(GET_INPUT_TIMING_VFREQ() - tINPUTMODE_PRESET_TABLE[ucLastModeCnt].usIVFreq) > tINPUTMODE_PRESET_TABLE[ucLastModeCnt].ucIVFreqTolerance))
    {
        *pucModeBestInx = ucCurrentModeCnt;

        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check Mode By GTF Height
// Input Value  : ucCurrentModeCnt  --> Current ModeIndex
//                ucLastModeCnt     --> Last ModeIndex
//                pModeBestInx      --> Return ModeIndex Pointer
// Output Value : New ModeIndex
//--------------------------------------------------
bit UserCommonModeSearchCheckGTFHeight(BYTE ucLastModeCnt, BYTE ucCurrentModeCnt, BYTE *pucModeBestInx)
{
    WORD usDiffCurr = 0;
    WORD usDiffLast = 0;

    // Can't be matched by GTF height closer If the PK Mode are Confuse Mode
    if((abs(tINPUTMODE_PRESET_TABLE[ucLastModeCnt].usIHFreq - tINPUTMODE_PRESET_TABLE[ucCurrentModeCnt].usIHFreq) <= _HFREQ_TOLERANCE) &&
       (abs(tINPUTMODE_PRESET_TABLE[ucLastModeCnt].usIVFreq - tINPUTMODE_PRESET_TABLE[ucCurrentModeCnt].usIVFreq) <= _VFREQ_TOLERANCE) &&
       (abs(tINPUTMODE_PRESET_TABLE[ucLastModeCnt].usIVTotal - tINPUTMODE_PRESET_TABLE[ucCurrentModeCnt].usIVTotal) <= _PRESET_MODE_VTOTAL_TOLERANCE))
    {
        return _FALSE;
    }

    usDiffCurr = abs(GET_INPUT_MODE_GTF_HEIGHT() - tINPUTMODE_PRESET_TABLE[ucCurrentModeCnt].usIVHeight);
    usDiffLast = abs(GET_INPUT_MODE_GTF_HEIGHT() - tINPUTMODE_PRESET_TABLE[ucLastModeCnt].usIVHeight);

    if((usDiffCurr < _USER_MODE_VHEIGHT_GTF_DIFF_MIN) && (usDiffLast < _USER_MODE_VHEIGHT_GTF_DIFF_MIN))
    {
        return _FALSE;
    }
    else if(usDiffCurr == usDiffLast)
    {
        return _FALSE;
    }

    if(usDiffCurr < usDiffLast)
    {
        *pucModeBestInx = ucCurrentModeCnt;
    }
    else
    {
        *pucModeBestInx = ucLastModeCnt;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Check Mode By H and V Sync Pulse
// Input Value  : ucModeCnt --> Current ModeIndex
// Output Value : New ModeIndex
//--------------------------------------------------
bit UserCommonModeSearchHVSyncPulseCheck(BYTE ucLastModeCnt, BYTE ucCurrentModeCnt, BYTE *pucModeBestInx)
{
    BYTE ucCnt = 0;

    // Check H-Sync Pulse count condition
    while(tHSYNC_PULSE_COUNT_MODE_TABLE[ucCnt].ucFirstMode != _MODE_NOSUPPORT)
    {
        if(((ucLastModeCnt == tHSYNC_PULSE_COUNT_MODE_TABLE[ucCnt].ucFirstMode) || (ucLastModeCnt == tHSYNC_PULSE_COUNT_MODE_TABLE[ucCnt].ucSecondMode)) &&
           ((ucCurrentModeCnt == tHSYNC_PULSE_COUNT_MODE_TABLE[ucCnt].ucFirstMode) || (ucCurrentModeCnt == tHSYNC_PULSE_COUNT_MODE_TABLE[ucCnt].ucSecondMode)))
        {
            if(GET_INPUT_TIMING_HSYNCWIDTH() <= (WORD)((DWORD)tHSYNC_PULSE_COUNT_MODE_TABLE[ucCnt].usMidSyncPulseCount * ScalerSyncProcGetCurrentClockFreq() / 27000))
            {
                *pucModeBestInx = tHSYNC_PULSE_COUNT_MODE_TABLE[ucCnt].ucFirstMode;

                DebugMessageAnalog("2. Detect By H-Sync Pulse", *pucModeBestInx);

                return _TRUE;
            }
            else
            {
                *pucModeBestInx = tHSYNC_PULSE_COUNT_MODE_TABLE[ucCnt].ucSecondMode;

                DebugMessageAnalog("2. Detect By H-Sync Pulse", *pucModeBestInx);

                return _TRUE;
            }
        }

        ucCnt++;
    }

    // Reset circle counter
    ucCnt = 0;

    // Check V-Sync Pulse count condition
    while(tVSYNC_PULSE_COUNT_MODE_TABLE[ucCnt].ucFirstMode != _MODE_NOSUPPORT)
    {
        if(((ucLastModeCnt == tVSYNC_PULSE_COUNT_MODE_TABLE[ucCnt].ucFirstMode) || (ucLastModeCnt == tVSYNC_PULSE_COUNT_MODE_TABLE[ucCnt].ucSecondMode)) &&
           ((ucCurrentModeCnt == tVSYNC_PULSE_COUNT_MODE_TABLE[ucCnt].ucFirstMode) || (ucCurrentModeCnt == tVSYNC_PULSE_COUNT_MODE_TABLE[ucCnt].ucSecondMode)))
        {
            // Check H-Sync Pulse condition
            if(GET_INPUT_TIMING_VSYNCWIDTH() <= tVSYNC_PULSE_COUNT_MODE_TABLE[ucCnt].usMidSyncPulseCount)
            {
                *pucModeBestInx = tVSYNC_PULSE_COUNT_MODE_TABLE[ucCnt].ucFirstMode;

                DebugMessageAnalog("2. Detect By V-Sync Pulse", *pucModeBestInx);

                return _TRUE;
            }
            else
            {
                *pucModeBestInx = tVSYNC_PULSE_COUNT_MODE_TABLE[ucCnt].ucSecondMode;

                DebugMessageAnalog("2. Detect By V-Sync Pulse", *pucModeBestInx);

                return _TRUE;
            }
        }

        ucCnt++;
    }


    return _FALSE;
}

//--------------------------------------------------
// Description  : Check Mode By H and V Sync Palority
// Input Value  : ucLastModeCnt --> Last ModeIndex
//             ucCurrentModeCnt --> Current ModeIndex
// Output Value : _TRUE: Polarity matched
//                 pModeBestInx --> Matched successful mode no
//--------------------------------------------------
bit UserCommonModeSearchCompareByPolarity(BYTE ucLastModeCnt, BYTE ucCurrentModeCnt, BYTE *pucModeBestInx)
{
    BYTE ucCnt = 0;
    BYTE ucPolarity = 0;

    if((tINPUTMODE_PRESET_TABLE[ucLastModeCnt].ucMiscFlag & 0x0F) == (tINPUTMODE_PRESET_TABLE[ucCurrentModeCnt].ucMiscFlag & 0x0F))
    {
        return _FALSE;
    }

    if(GET_INPUT_TIMING_H_POLARITY() == _TRUE)
    {
        if(GET_INPUT_TIMING_V_POLARITY() == _TRUE)
        {
            ucPolarity = _SYNC_HP_VP;
        }
        else
        {
            ucPolarity = _SYNC_HP_VN;
        }
    }
    else
    {
        if(GET_INPUT_TIMING_V_POLARITY() == _TRUE)
        {
            ucPolarity = _SYNC_HN_VP;
        }
        else
        {
            ucPolarity = _SYNC_HN_VN;
        }
    }

    // Once the two Mode in Mode table defines the same polarity will not be able to distinguish between them
    if(((tINPUTMODE_PRESET_TABLE[ucLastModeCnt].ucMiscFlag & 0x0F) & ucPolarity) == ((tINPUTMODE_PRESET_TABLE[ucCurrentModeCnt].ucMiscFlag & 0x0F) & ucPolarity))
    {
        return _FALSE;
    }

    // Check polarity condition
    while(tPOLARITY_MODEGROUP_TABLE[ucCnt].ucFirstMode != _MODE_NOSUPPORT)
    {
        if(((ucLastModeCnt == tPOLARITY_MODEGROUP_TABLE[ucCnt].ucFirstMode) || (ucLastModeCnt == tPOLARITY_MODEGROUP_TABLE[ucCnt].ucSecondMode)) &&
           ((ucCurrentModeCnt == tPOLARITY_MODEGROUP_TABLE[ucCnt].ucFirstMode) || (ucCurrentModeCnt == tPOLARITY_MODEGROUP_TABLE[ucCnt].ucSecondMode)))
        {
            if((bit)((tINPUTMODE_PRESET_TABLE[tPOLARITY_MODEGROUP_TABLE[ucCnt].ucFirstMode].ucMiscFlag & 0x0F) & ucPolarity) == _TRUE)
            {
                *pucModeBestInx = tPOLARITY_MODEGROUP_TABLE[ucCnt].ucFirstMode;

                return _TRUE;
            }
            else if((bit)((tINPUTMODE_PRESET_TABLE[tPOLARITY_MODEGROUP_TABLE[ucCnt].ucSecondMode].ucMiscFlag & 0x0F) & ucPolarity) == _TRUE)
            {
                *pucModeBestInx = tPOLARITY_MODEGROUP_TABLE[ucCnt].ucSecondMode;

                return _TRUE;
            }
        }

        ucCnt++;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check Mode By Interlace Flag
// Input Value  : ucLastModeCnt --> Current ModeIndex
//             ucCurrentModeCnt --> Current ModeIndex
// Output Value : _TRUE: Interlace matched
//                 pModeBestInx --> Matched successful mode no
//--------------------------------------------------
bit UserCommonModeSearchCompareByInterlace(BYTE ucLastModeCnt, BYTE ucCurrentModeCnt, BYTE *pucModeBestInx)
{
    BYTE ucCnt = 0;

    if((GET_MODE_TABLE_INTERLACED(tINPUTMODE_PRESET_TABLE[ucLastModeCnt]) == _TRUE) && (GET_MODE_TABLE_INTERLACED(tINPUTMODE_PRESET_TABLE[ucCurrentModeCnt]) == _TRUE))
    {
        return _FALSE;
    }

    // Check interlace condition
    while(tINTERLACE_MODEGROUP_TABLE[ucCnt].ucFirstMode != _MODE_NOSUPPORT)
    {
        if(((ucLastModeCnt == tINTERLACE_MODEGROUP_TABLE[ucCnt].ucFirstMode) || (ucLastModeCnt == tINTERLACE_MODEGROUP_TABLE[ucCnt].ucSecondMode)) &&
           ((ucCurrentModeCnt == tINTERLACE_MODEGROUP_TABLE[ucCnt].ucFirstMode) || (ucCurrentModeCnt == tINTERLACE_MODEGROUP_TABLE[ucCnt].ucSecondMode)))
        {
            if(GET_MODE_TABLE_INTERLACED(tINPUTMODE_PRESET_TABLE[tINTERLACE_MODEGROUP_TABLE[ucCnt].ucFirstMode]) == (bit)GET_INPUT_TIMING_INTERLACE_FLG())
            {
                *pucModeBestInx = tINTERLACE_MODEGROUP_TABLE[ucCnt].ucFirstMode;

                return _TRUE;
            }
            else if(GET_MODE_TABLE_INTERLACED(tINPUTMODE_PRESET_TABLE[tINTERLACE_MODEGROUP_TABLE[ucCnt].ucSecondMode]) == (bit)GET_INPUT_TIMING_INTERLACE_FLG())
            {
                *pucModeBestInx = tINTERLACE_MODEGROUP_TABLE[ucCnt].ucSecondMode;

                return _TRUE;
            }
        }

        ucCnt++;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check Mode By Sync Source Come from
// Input Value  : ucLastModeCnt --> Last ModeIndex
//             ucCurrentModeCnt --> Current ModeIndex
// Output Value : _TRUE: Sync Pad matched
//                 pModeBestInx --> Matched successful mode no
//--------------------------------------------------
bit UserCommonModeSearchCompareByVideoModeFlg(BYTE ucLastModeCnt, BYTE ucCurrentModeCnt, BYTE *pucModeBestInx)
{
    if((GET_MODE_TABLE_VIDEO(tINPUTMODE_PRESET_TABLE[ucLastModeCnt]) != 0x00) &&
       (GET_MODE_TABLE_VIDEO(tINPUTMODE_PRESET_TABLE[ucCurrentModeCnt]) == 0x00))
    {
        if(ScalerSyncProcGetSyncPad() == _TRUE)
        {
            *pucModeBestInx = ucLastModeCnt;
        }
        else
        {
            *pucModeBestInx = ucCurrentModeCnt;
        }

        return _TRUE;
    }
    else if((GET_MODE_TABLE_VIDEO(tINPUTMODE_PRESET_TABLE[ucLastModeCnt]) == 0x00) &&
            (GET_MODE_TABLE_VIDEO(tINPUTMODE_PRESET_TABLE[ucCurrentModeCnt]) != 0x00))
    {
        if(ScalerSyncProcGetSyncPad() == _TRUE)
        {
            *pucModeBestInx = ucCurrentModeCnt;
        }
        else
        {
            *pucModeBestInx = ucLastModeCnt;
        }

        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check FIFO mode for VGA
// Input Value  : ucIndex --> Mode Index
// Output Value : None
//--------------------------------------------------
void UserCommonModeSearchFIFOSaveModeInfo(BYTE ucIndex)
{
    BYTE ucFIFOInx = 0;

    ucFIFOInx = UserCommonModeSearchCheckFIFOModeSaved(ucIndex);

    // Check Current Mode Saved before.
    if(ucFIFOInx == _MODE_NOT_EXIST_IN_FIFO)
    {
        // Initial User Data For The Mode Which Light Up First Time.
        UserCommonModeSearchInitalUserAndCenterData(ucIndex);

        // Save User Data.
        UserCommonNVRamSaveModeUserData();

        // Save System Data
        UserCommonNVRamSaveSystemData();

        // Update Input Timing Info. by Mode Table.
        UserCommonModeSearchUpdateInputDataRefModeTbl(ucIndex);
    }
    else
    {
        UserCommonModeSearchUpdateInputDataRefFIFO(ucFIFOInx, ucIndex);
    }
}

//--------------------------------------------------
// Description  : Check FIFO mode be saved the same mode
// Input Value  : pFIFOIndex --> Mode table index of FIFO mode
// Output Value : _TRUE: There is a same mode saved in FIFO.
//--------------------------------------------------
BYTE UserCommonModeSearchCheckFIFOModeSaved(BYTE ucModeIndex)
{
    BYTE ucFIFOInx = 0;

    // Save Mode data Here.
    for(ucFIFOInx = 0; ucFIFOInx < _MODE_SLOT_AMOUNT; ucFIFOInx++)
    {
        if(UserCommonNVRamLoadModeUserModeNumberData(ucFIFOInx) == ucModeIndex)
        {
            return ucFIFOInx;
        }
    }

    return _MODE_NOT_EXIST_IN_FIFO;
}

//--------------------------------------------------
// Description  : Inital User Data
// Input Value  : ucIndex --> Mode Index
// Output Value : None
//--------------------------------------------------
void UserCommonModeSearchInitalUserAndCenterData(BYTE ucIndex)
{
    // Clear structure
    memset(&g_stVGAModeUserData, 0xFF, sizeof(g_stVGAModeUserData));

    SET_VGA_MODE_ADJUST_H_POSITION(50);
    SET_VGA_MODE_ADJUST_V_POSITION(50);

#if(_AUTO_CLOCK_SAVE_VALUE_OPTION == _CLOCK_SAVE_PERCENT_VALUE)
    SET_VGA_MODE_ADJUST_CLOCK(50);
#else
    SET_VGA_MODE_ADJUST_CLOCK(tINPUTMODE_PRESET_TABLE[ucIndex].usIHTotal);
#endif

    SET_VGA_MODE_ADJUST_PHASE(0);
    SET_VGA_MODE_DO_FIRST_AUTO(_TRUE);

    g_stVGAModeUserData.b1IsPresetMode = GET_MODE_SEARCH_TYPE();
    g_stVGAModeUserData.ucModeNumber = ucIndex;
    g_stVGAModeUserData.usCenterHPosition = tINPUTMODE_PRESET_TABLE[ucIndex].usIHStartPos;
    g_stVGAModeUserData.usCenterVPosition = tINPUTMODE_PRESET_TABLE[ucIndex].usIVStartPos;
    g_stVGAModeUserData.usCenterClock = tINPUTMODE_PRESET_TABLE[ucIndex].usIHTotal;
    g_stVGAModeUserData.ucCenterPhase = 0;
}

//--------------------------------------------------
// Description  : Update Input Timing Info By Mode Table
// Input Value  : ucIndex --> Mode Index
// Output Value : None
//--------------------------------------------------
void UserCommonModeSearchUpdateInputDataRefModeTbl(BYTE ucIndex)
{
    // Modify Input Timing Information Reference Modetable Parameters.
    SET_INPUT_TIMING_HSTART(tINPUTMODE_PRESET_TABLE[ucIndex].usIHStartPos);
    SET_INPUT_TIMING_HWIDTH(tINPUTMODE_PRESET_TABLE[ucIndex].usIHWidth);
    SET_INPUT_TIMING_HTOTAL(tINPUTMODE_PRESET_TABLE[ucIndex].usIHTotal);
    SET_INPUT_TIMING_VSTART(tINPUTMODE_PRESET_TABLE[ucIndex].usIVStartPos);
    SET_INPUT_TIMING_VHEIGHT(tINPUTMODE_PRESET_TABLE[ucIndex].usIVHeight);
}

//--------------------------------------------------
// Description  : Update Input Timing Info By FIFO Table
// Input Value  : ucFifoIndex --> Fifo Mode Index
//                    ucIndex --> Mode Table Index
// Output Value : None
//--------------------------------------------------
void UserCommonModeSearchUpdateInputDataRefFIFO(BYTE ucFifoIndex, BYTE ucIndex)
{
    // Load User Data.
    UserCommonNVRamLoadModeUserData(ucFifoIndex);

    if((UserCommonModeSearchCheckFIFOSetting(g_stVGAModeUserData, ucIndex) == _FALSE) || (UserInterfaceGetLoadModeTableDefaultStatus() == _TRUE))
    {
        // Load Parameters Reference Modetable.
        SET_INPUT_TIMING_HSTART(tINPUTMODE_PRESET_TABLE[ucIndex].usIHStartPos);
        SET_INPUT_TIMING_HWIDTH(tINPUTMODE_PRESET_TABLE[ucIndex].usIHWidth);
        SET_INPUT_TIMING_HTOTAL(tINPUTMODE_PRESET_TABLE[ucIndex].usIHTotal);
        SET_INPUT_TIMING_VSTART(tINPUTMODE_PRESET_TABLE[ucIndex].usIVStartPos);
        SET_INPUT_TIMING_VHEIGHT(tINPUTMODE_PRESET_TABLE[ucIndex].usIVHeight);

        // Initial User Data For The Mode Which Light Up First Time.
        UserCommonModeSearchInitalUserAndCenterData(ucIndex);
    }
    else
    {
        // Modify Input Timing Information Reference Modetable Parameters.
        SET_INPUT_TIMING_HSTART(g_stVGAModeUserData.usCenterHPosition);
        SET_INPUT_TIMING_HWIDTH(tINPUTMODE_PRESET_TABLE[ucIndex].usIHWidth);
        SET_INPUT_TIMING_HTOTAL(g_stVGAModeUserData.usCenterClock);
        SET_INPUT_TIMING_VSTART(g_stVGAModeUserData.usCenterVPosition);
        SET_INPUT_TIMING_VHEIGHT(tINPUTMODE_PRESET_TABLE[ucIndex].usIVHeight);
    }
}

//--------------------------------------------------
// Description  : Get Modetable Video type flag
// Input Value  : ucIndex --> Mode Index
// Output Value : Return Video type flag.
//--------------------------------------------------
BYTE UserCommonModeSearchGetModeVideoType(BYTE ucIndex)
{
    return tINPUTMODE_PRESET_TABLE[ucIndex].ucMiscFlag & (_VIDEO_MODE_GROUP2 | _VIDEO_MODE_GROUP1 | _VIDEO_MODE_GROUP3);
}

//--------------------------------------------------
// Description  : Check FIFO Data Validation(Center Data, User Data)
// Input Value  : ModeIndex
// Output Value : _TRUE: The FIFO Setting is ok.
//--------------------------------------------------
bit UserCommonModeSearchCheckFIFOSetting(StructVGAModeUserDataType stFifoUserData, BYTE ucModeIndex)
{
    WORD usIHCaptureStart = ScalerIDomainVgipIHCaptureMaxEstimate(stFifoUserData.usCenterHPosition);

    if(stFifoUserData.usCenterClock > GET_ADC_LIMIT_CLOCK())
    {
        return _FALSE;
    }

    if(stFifoUserData.usCenterClock < (usIHCaptureStart + tINPUTMODE_PRESET_TABLE[ucModeIndex].usIHWidth))
    {
        return _FALSE;
    }

    // Check CenterVposition Validation
    if(GET_INPUT_TIMING_VTOTAL() < (stFifoUserData.usCenterVPosition + (tINPUTMODE_PRESET_TABLE[ucModeIndex].usIVHeight)))
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Get Mode Table Timing Data Info
// Input Value  : ucDataType --> Data Type in StructTimingInfo
//              : ucModeNumber --> Target Mode Number
// Output Value : ucValue --> Value of the Mode Table Timing Data Type
//--------------------------------------------------
WORD UserCommonModeSearchGetModetableTimingDataItem(BYTE ucModeNumber, EnumTimingInfoSelect enumTimingInfo)
{
    WORD usValue = 0;

    switch(enumTimingInfo)
    {
        case _IHFREQ:
            usValue = (WORD)(tINPUTMODE_PRESET_TABLE[ucModeNumber].usIHFreq);
            break;

        case _IHTOTAL:
            usValue = (WORD)(tINPUTMODE_PRESET_TABLE[ucModeNumber].usIHTotal);
            break;

        case _IHWIDTH:
            usValue = (WORD)(tINPUTMODE_PRESET_TABLE[ucModeNumber].usIHWidth);
            break;

        case _IHSTART:
            usValue = (WORD)(tINPUTMODE_PRESET_TABLE[ucModeNumber].usIHStartPos);
            break;

        case _IVFREQ:
            usValue = (WORD)(tINPUTMODE_PRESET_TABLE[ucModeNumber].usIVFreq);
            break;

        case _IVTOTAL:
            usValue = (WORD)(tINPUTMODE_PRESET_TABLE[ucModeNumber].usIVTotal);
            break;

        case _IVHEIGHT:
            usValue = (WORD)(tINPUTMODE_PRESET_TABLE[ucModeNumber].usIVHeight);
            break;

        case _IVSTART:
            usValue = (WORD)(tINPUTMODE_PRESET_TABLE[ucModeNumber].usIVStartPos);
            break;

        case _MISC:
            usValue = (WORD)(tINPUTMODE_PRESET_TABLE[ucModeNumber].ucMiscFlag);
            break;

        default:
            break;
    }

    return usValue;
}

//--------------------------------------------------
// Description  : Get color rimetry
// Input Value  : ucModeNumber --> Target Mode Number
// Output Value : _TRUE --> current mode is HD TV Mode
//--------------------------------------------------
bit UserCommonModeSearchCheckPresetModeTable(BYTE ucMatchmode)
{
    BYTE ucInx1 = 0;

    if(sizeof(tPRESET_MODE_TABLE) < _MODE_SLOT_AMOUNT)
    {
        for(ucInx1 = 0; ucInx1 < sizeof(tPRESET_MODE_TABLE); ucInx1++)
        {
            if(tPRESET_MODE_TABLE[ucInx1] == ucMatchmode)
            {
                return _TRUE;
            }
        }
    }

    return _FALSE;
}
#endif // End of #if(_VGA_SUPPORT == _ON)
