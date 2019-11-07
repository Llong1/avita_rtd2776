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
// ID Code      : RL6193_Series_Scaling.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerScalingUpdateFIFOScalingSize(StructSDRAMDataInfo *pstData);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Decide which scaling size
// Input Value  : Input/Output H/V Active Region
// Output Value : None
//--------------------------------------------------
void ScalerScalingUpdateFIFOScalingSize(StructSDRAMDataInfo *pstData)
{
    BYTE ucDpllSscgDiv = ScalerMDomainGetDpllSscgDivMode();
    WORD usIVtotal = 0;

#if(_FRC_SUPPORT == _ON)
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    // Get Rotation status
    if(ScalerRotationCheckStatus() == _TRUE)
    {
        SET_MEMORY_FRAME_BUFFER(_MEMORY_3_FRAME_BUFFER);
    }
    else
#endif
    {
        if((GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P) & ((GET_MEMORY_DVF_SELECT() == _1_IVF)))
        {
            SET_MEMORY_FRAME_BUFFER(_MEMORY_1_FRAME_BUFFER);
        }
        else
        {
            SET_MEMORY_FRAME_BUFFER(_MEMORY_2_FRAME_BUFFER);
        }
    }
#endif

    //-----------------------------------------------
    // Consider FIFO Input / Output H width
    //-----------------------------------------------
    if(g_stMDomainInputData.usHWidth > g_stMDomainOutputData.usHWidth)
    {
        pstData->usInputHWidth = g_stMDomainOutputData.usHWidth;
        pstData->usOutputHWidth = g_stMDomainOutputData.usHWidth;
    }
    else
    {
        pstData->usInputHWidth = g_stMDomainInputData.usHWidth;
        pstData->usOutputHWidth = g_stMDomainInputData.usHWidth;
    }

    //-----------------------------------------------
    // Consider FIFO Input / Output V Height
    //-----------------------------------------------
    if(g_stMDomainInputData.usVHeight > g_stMDomainOutputData.usVHeight)
    {
        pstData->usInputVHeight = g_stMDomainOutputData.usVHeight;
        pstData->usOutputVHeight = g_stMDomainOutputData.usVHeight;
    }
    else
    {
        pstData->usInputVHeight = g_stMDomainInputData.usVHeight;
        pstData->usOutputVHeight = g_stMDomainInputData.usVHeight;
    }

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    if((ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE) &&
       (((GET_ROT_TYPE() == _ROT_CW90) || (GET_ROT_TYPE() == _ROT_CW270)) && (GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P)))
    {
        if(g_stMDomainInputData.usHWidth > g_stMDomainOutputData.usVHeight)
        {
            pstData->usInputHWidth = g_stMDomainOutputData.usVHeight;
        }
        else
        {
            pstData->usInputHWidth = g_stMDomainInputData.usHWidth;
        }

        if(g_stMDomainInputData.usVHeight > g_stMDomainOutputData.usHWidth)
        {
            pstData->usInputVHeight = g_stMDomainOutputData.usHWidth;
        }
        else
        {
            pstData->usInputVHeight = g_stMDomainInputData.usVHeight;
        }
    }
#endif

#if(_FRC_SUPPORT == _ON)
    //-----------------------------------------------
    // Consider FIFO Input / Output H width in FRC
    //-----------------------------------------------
    if(GET_MEMORY_CONFIG() == _MEMORY_WORK_MODE)
    {
#if(_FREESYNC_SUPPORT == _ON)
        if(GET_FREESYNC_ENABLED() == _TRUE)
        {
            usIVtotal = (DWORD)g_stMDomainInputData.usVHeight * 105 / 100;
        }
        else
#endif
        {
            usIVtotal = g_stMDomainInputData.usVTotal;
        }

        if((ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _FALSE) &&
           (GET_MDOMAIN_DISPLAY_MODE() != _DISPLAY_MODE_4P) &&
           (ScalerGlobalGetIDCode() <= _RL6193_VER_C_ID_CODE))
        {
            PDATA_DWORD(0) = (DWORD)ScalerMDomainGetCurBW() * 100000 / GET_MEMORY_DATA_BIT() * _MEMORY_BUS_WIDTH /
                             ((((DWORD)usIVtotal * g_stMDomainInputData.usVFreq * 2) +
                               ((DWORD)g_stMDomainOutputData.usVTotal * g_usDVFreq) +
                               ((DWORD)g_stMDomainOutputData.usVTotal * g_usDVFreq * ((_DCLK_SPREAD_RANGE / ucDpllSscgDiv) + _DCLK_SPREAD_RANGE_MARGIN) / 4 / 100)) / 10 + 1);
        }
        else
        {
            PDATA_DWORD(0) = (DWORD)ScalerMDomainGetCurBW() * 100000 / GET_MEMORY_DATA_BIT() * _MEMORY_BUS_WIDTH /
                             ((((DWORD)usIVtotal * g_stMDomainInputData.usVFreq) +
                               ((DWORD)g_stMDomainOutputData.usVTotal * g_usDVFreq) +
                               ((DWORD)g_stMDomainOutputData.usVTotal * g_usDVFreq * ((_DCLK_SPREAD_RANGE / ucDpllSscgDiv) + _DCLK_SPREAD_RANGE_MARGIN) / 4 / 100)) / 10 + 1);
        }

        DebugMessageFRC("4. FRC BW limit", ScalerMDomainGetCurBW());
        DebugMessageFRC("4. FRC max SD width", PDATA_DWORD(0));
        DebugMessageFRC("4. FRC current SD width", pstData->usInputHWidth);

        if(pstData->usInputHWidth > PDATA_DWORD(0))
        {
            pstData->usInputHWidth = PDATA_DWORD(0);
        }

        DebugMessageFRC("4.usHSDBW", PDATA_DWORD(0));
    } // End of if(GET_MEMORY_CONFIG() == _MEMORY_WORK_MODE)

    // Let HWidth be multiple of 2.
    pstData->usInputHWidth -= (pstData->usInputHWidth % 2);
    pstData->usOutputHWidth = pstData->usInputHWidth;

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    if((ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE) &&
       (((GET_ROT_TYPE() == _ROT_CW90) || (GET_ROT_TYPE() == _ROT_CW270)) && (GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P)))
    {
        pstData->usOutputHWidth = pstData->usInputVHeight;
        pstData->usOutputVHeight = pstData->usInputHWidth;
    }
#endif // End of #if(_DISPLAY_ROTATION_SUPPORT == _ON)

#endif // End of #if(_FRC_SUPPORT == _ON)
}

