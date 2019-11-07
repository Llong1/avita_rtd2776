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
// ID Code      : SysVGA.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SYSTEM_VGA__

#include "SysInclude.h"

#if(_VGA_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of mode search status
//--------------------------------------------------
#define _VGA_MODE_NOSUPPORT                             254

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
EnumDisplayRegion g_enumVgaRegion = _DISPLAY_RGN_NONE;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
EnumDisplayRegion SysVgaGetRegion(void);
void SysVgaWatchDog(bit bEnable);
BYTE SysVgaScanInputPort(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : Get & update VGA display region
// Input Value  : None
// Output Value : display region
//--------------------------------------------------
EnumDisplayRegion SysVgaGetRegion(void)
{
    // Check current VGA region
    if(((EnumDisplayMode)GET_RGN_DISPLAY_MODE(g_enumVgaRegion) == GET_MODE_DISPLAY_MODE()) &&
       (GET_RGN_SOURCE_TYPE(ScalerRegionGetIndex(g_enumVgaRegion)) == _SOURCE_VGA))
    {
        return g_enumVgaRegion;
    }
    else
    {
        // Search VGA region
        BYTE ucRegionIndex = 0;
        g_enumVgaRegion = _DISPLAY_RGN_NONE;

        for(ucRegionIndex = 0; ucRegionIndex < GET_RGN_MAX_DISPLAY_REGION(); ++ucRegionIndex)
        {
            if(GET_RGN_SOURCE_TYPE(ucRegionIndex) == _SOURCE_VGA)
            {
                g_enumVgaRegion = GET_RGN_DISPLAY_REGION(ucRegionIndex);
                break;
            }
        }

        return g_enumVgaRegion;
    }
}

//--------------------------------------------------
// Description  : Enable or disable VGA watchdog
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void SysVgaWatchDog(bit bEnable)
{
    BYTE ucRegionIndex = 0;

    for(ucRegionIndex = 0; ucRegionIndex < GET_RGN_MAX_DISPLAY_REGION(); ++ucRegionIndex)
    {
        if((GET_RGN_SOURCE_TYPE(ucRegionIndex) == _SOURCE_VGA) &&
           (GET_RGN_DISPLAY_STATE(ucRegionIndex) == _DISPLAY_STATE_ACTIVE))
        {
            ScalerGlobalWatchDog(GET_RGN_DISPLAY_REGION(ucRegionIndex), bEnable);
        }
    }
}

//--------------------------------------------------
// Description  : Scan VGA Port
// Input Value  : None
// Output Value : Source Type
//--------------------------------------------------
BYTE SysVgaScanInputPort(void)
{
    BYTE ucModeNo = 0;
    BYTE ucRegionIndex = 0;

    if(ScalerSyncProcPreDetect() == _FALSE)
    {
        return _SOURCE_NONE;
    }

    if(ScalerSyncProcTypeAutoRun() != _NO_SYNC_STATE)
    {
        SET_SOURCE_TYPE(g_ucSearchIndex, _SOURCE_VGA);

        // Initial ADC Clock.
        if(ScalerSyncProcAdcClkInitial() == _FALSE)
        {
            DebugMessageAnalog("Apll initial Fail", 0);

            return _SOURCE_NONE;
        }

        // Search select region for VGA
        ucRegionIndex = SysRegionConvertPortToRegionIndex(_A0_INPUT_PORT);

        if(ucRegionIndex == _REGION_INDEX_NONE)
        {
            DebugMessageSystem("VGA Region Fail", 0);

            return _SOURCE_NONE;
        }

        g_enumVgaRegion = GET_RGN_DISPLAY_REGION(ucRegionIndex);

        // Set VGATOP VGIP
        ScalerVgaTopInputInitial();

        // Store source index
        SET_RGN_SOURCE_INDEX(ucRegionIndex, g_ucSearchIndex);

        CLR_RGN_TIMING_DOUBLE_CHECK(ucRegionIndex);

        // Set measure region index
        ScalerMeasureSetIndex(ucRegionIndex);
        ScalerMeasureSetInputPath(ScalerRegionGetInputDataPath(g_enumVgaRegion));

        // Get Measure Info.
        if(ScalerMeasureVgaInputInfo() == _FALSE)
        {
            DebugMessageSystem("VGA Measure Fail", 0);

            return _SOURCE_NONE;
        }

        DebugMessageSystem("VGA Measure Info", g_enumVgaRegion);
        DebugMessageSystem("Input Timing HP", GET_INPUT_TIMING_H_POLARITY());
        DebugMessageSystem("Input Timing VP", GET_INPUT_TIMING_V_POLARITY());
        DebugMessageSystem("Input Timing InterLace", GET_INPUT_TIMING_INTERLACE_FLG());
        DebugMessageSystem("Input Timing HFreq", GET_INPUT_TIMING_HFREQ());
        DebugMessageSystem("Input Timing HTotal", GET_INPUT_TIMING_HTOTAL());
        DebugMessageSystem("Input Timing HStart", GET_INPUT_TIMING_HSTART());
        DebugMessageSystem("Input Timing HWidth", GET_INPUT_TIMING_HWIDTH());
        DebugMessageSystem("Input Timing HSW", GET_INPUT_TIMING_HSYNCWIDTH());
        DebugMessageSystem("Input Timing VFreq", GET_INPUT_TIMING_VFREQ());
        DebugMessageSystem("Input Timing VTotal", GET_INPUT_TIMING_VTOTAL());
        DebugMessageSystem("Input Timing VStart", GET_INPUT_TIMING_VSTART());
        DebugMessageSystem("Input Timing VHeight", GET_INPUT_TIMING_VHEIGHT());
        DebugMessageSystem("Input Timing VSW", GET_INPUT_TIMING_VSYNCWIDTH());

        // Mode No. match
        ucModeNo = UserCommonModeSearchModeVGA();

        DebugMessageAnalog("9. ucModeNo = ", ucModeNo);

        if(ucModeNo == _VGA_MODE_NOSUPPORT)
        {
            SET_INPUT_TIMING_HWIDTH(0);
            SET_INPUT_TIMING_VHEIGHT(0);
            SET_RGN_DISPLAY_ACTION(ucRegionIndex, _DISPLAY_ACTION_OOR);
        }
        else
        {
            // Confirm Clamp Position Setting.
            ScalerSyncProcClampPosCheck(UserCommonModeSearchGetModeVideoType(ucModeNo));

            // Color format setting.
            ScalerADCClampMode(ScalerColorGetColorSpace(_A0_INPUT_PORT));

            if(ScalerSyncProcAdcClkSetting() == _FALSE)
            {
                return _SOURCE_NONE;
            }

            // Set VGATOP capture
            ScalerVgaTopSetCapture();

            // SOG0 DC Restore Disable
            ScalerADCDCRestoreEn(_OFF);

            // SOG Clamp Enable
            ScalerADCSOGClampEn(_ON);

#if(_VGA_CHROMA_PATTERN12_SUPPORT == _ON)
            // Initial porch voltage check
            ScalerSyncProcSetPorchVoltage();
#endif

            // Double-check for VS synchronize edge
            ScalerVgaTopModifyVsLatchEdge(_WAIT);

            // Clear Sync Changed Status flag bit.
            ScalerSyncProcClearSyncChangeStatus();

            // Re-start on-line measure
            ScalerMeasureSetOnlineMeasure(ScalerRegionGetInputDataPath(g_enumVgaRegion));

#if(_YPBPR_SUPPORT == _ON)
            if(ScalerColorGetColorSpace(_A0_INPUT_PORT) == _COLOR_SPACE_YPBPR)
            {
                ScalerColorSetColorimetry(_A0_INPUT_PORT, UserCommonInterfaceCheckHDTVMode(ucModeNo));
            }
#endif // End of #if (_YPBPR_SUPPORT == _ON)

            // Perform I-domain OOR check here
            if(UserCommonInterfaceCheckNoSupport(g_enumVgaRegion) == _TRUE)
            {
                SET_RGN_DISPLAY_ACTION(ucRegionIndex, _DISPLAY_ACTION_OOR);
            }

            // Re-start on-line measure after APLL clock adjust
            ScalerMeasureSetOnlineMeasure(ScalerRegionGetInputDataPath(g_enumVgaRegion));
        }

        // Set Timing Confirm Flag.
        SET_RGN_TIMING_CONFIRM(ucRegionIndex);
        SET_RGN_TIMING_DOUBLE_CHECK(ucRegionIndex);

        return _SOURCE_VGA;
    }

    // Check sync is invalid
    return _SOURCE_NONE;
}

#endif // End of #if(_VGA_SUPPORT == _ON)
