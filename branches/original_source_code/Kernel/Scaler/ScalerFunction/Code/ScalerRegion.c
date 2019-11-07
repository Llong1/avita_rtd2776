
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
// ID Code      : ScalerRegion.c
// Update Note  :
//----------------------------------------------------------------------------------------------------
#define __SCALER_REGION__

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
EnumRegionIndex ScalerRegionGetIndex(EnumDisplayRegion enumDisplayRegion);
EnumInputDataPath ScalerRegionGetInputDataPath(EnumDisplayRegion enumDisplayRegion);
EnumDisplayDataPath ScalerRegionGetDisplayDataPath(EnumDisplayRegion enumDisplayRegion);
WORD ScalerRegionGetRegisterPage(EnumRegisterDataPosition enumRegisterDataPosition, EnumSelRegion enumSelRegion);
EnumSelRegion ScalerRegionGetInverse(EnumSelRegion enumSelRegion);

#if(_ULTRA_VIVID_SUPPORT == _ON)
BYTE ScalerRegionGetUltraVividActivePath(EnumSelRegion enumSelRegion);
#endif

EnumHLWType ScalerRegionGetSelectArea(EnumSelRegion enumSelRegion);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Convert display region to region index
// Input Value  : enumDisplayRegion --> target region
// Output Value : region index (0 ~ 3) or _REGION_INDEX_NONE
//--------------------------------------------------
EnumRegionIndex ScalerRegionGetIndex(EnumDisplayRegion enumDisplayRegion)
{
    if(enumDisplayRegion == _DISPLAY_RGN_NONE)
    {
        return _REGION_INDEX_NONE;
    }
    else
    {
        return (EnumRegionIndex)((enumDisplayRegion) & 0x03);
    }
}

//--------------------------------------------------
// Description  : Get input data path for select region
// Input Value  : enumSelRegion --> select region
// Output Value : Scaler Data Path
//--------------------------------------------------
EnumInputDataPath ScalerRegionGetInputDataPath(EnumDisplayRegion enumDisplayRegion)
{
    switch(enumDisplayRegion)
    {
        case _DISPLAY_RGN_1P:
#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
            return _INPUT_PATH_ALL;
#else
            return _INPUT_PATH_M1_M2;
#endif

        case _DISPLAY_RGN_MAIN:
        case _DISPLAY_RGN_LEFT:
        case _DISPLAY_RGN_TOP:
            return _INPUT_PATH_M1_M2;

        case _DISPLAY_RGN_SUB:
        case _DISPLAY_RGN_RIGHT:
        case _DISPLAY_RGN_BOTTOM:
            return _INPUT_PATH_S1_S2;

        case _DISPLAY_RGN_LT:
            return _INPUT_PATH_M1;

        case _DISPLAY_RGN_LB:
            return _INPUT_PATH_M2;

        case _DISPLAY_RGN_RT:
            return _INPUT_PATH_S1;

        case _DISPLAY_RGN_RB:
            return _INPUT_PATH_S2;

        default:
            return _INPUT_PATH_NONE;
    }

    return _INPUT_PATH_NONE;
}

//--------------------------------------------------
// Description  : Get input data path for select region
// Input Value  : enumSelRegion --> select region
// Output Value : Scaler Data Path
//--------------------------------------------------
EnumDisplayDataPath ScalerRegionGetDisplayDataPath(EnumDisplayRegion enumDisplayRegion)
{
    switch(enumDisplayRegion)
    {
        case _DISPLAY_RGN_1P:
        case _DISPLAY_RGN_MAIN:
        case _DISPLAY_RGN_LEFT:
        case _DISPLAY_RGN_TOP:
        case _DISPLAY_RGN_LT:
            return _DISPLAY_PATH_M1;

        case _DISPLAY_RGN_BOTTOM:
        case _DISPLAY_RGN_LB:
            return _DISPLAY_PATH_M2;

        case _DISPLAY_RGN_SUB:
        case _DISPLAY_RGN_RIGHT:
        case _DISPLAY_RGN_RT:
            return _DISPLAY_PATH_S1;

        case _DISPLAY_RGN_RB:
            return _DISPLAY_PATH_S2;

        default:
            return _DISPLAY_PATH_NONE;
    }

    return _DISPLAY_PATH_NONE;
}

//--------------------------------------------------
// Description  : Get Page Register From enumSelRegion
// Input Value  : EnumRegisterDataPosition & EnumSelRegion
// Output Value : Page Register
//--------------------------------------------------
WORD ScalerRegionGetRegisterPage(EnumRegisterDataPosition enumRegisterDataPosition, EnumSelRegion enumSelRegion)
{
    switch(enumRegisterDataPosition)
    {
        case _REG_IDOMAIN:
            switch(enumSelRegion)
            {
                case _4P_LB:

                    return _REG_MAIN2_PAGE;

                case _PIP_SUB:
                case _PBP_LR_R:
                case _4P_RT:
                case _PBP_TB_B:

                    return _REG_SUB1_PAGE;

                case _4P_RB:

                    return _REG_SUB2_PAGE;

                case _1P_NORMAL_FULL_REGION:
                case _1P_ROTATION_FULL_REGION:
                case _PIP_MAIN:
                case _PBP_LR_L:
                case _PBP_TB_T:
                case _4P_LT:
                case _PIP_FULL_REGION:
                case _PBP_LR_FULL_REGION:
                case _PBP_TB_FULL_REGION:
                case _4P_FULL_REGION:
                case _4P_LT_OUTSIDE:
                case _4P_LB_OUTSIDE:
                case _4P_RT_OUTSIDE:
                case _4P_RB_OUTSIDE:
                case _1P_NORMAL_DEMO_INSIDE:
                case _1P_NORMAL_DEMO_OUTSIDE:
                case _PIP_DEMO_INSIDE:
                case _PIP_DEMO_OUTSIDE:
                case _PBP_LR_DEMO_INSIDE:
                case _PBP_LR_DEMO_OUTSIDE:
                case _PBP_TB_DEMO_INSIDE:
                case _PBP_TB_DEMO_OUTSIDE:
                case _4P_DEMO_INSIDE:
                case _4P_DEMO_OUTSIDE:
                default:

                    return _REG_MAIN1_PAGE;
            }

        case _REG_DDOMAIN_BEFORE_BLENDING:
            switch(enumSelRegion)
            {
                case _PBP_TB_B:
                case _4P_LB:

                    return _REG_MAIN2_PAGE;

                case _PIP_SUB:
                case _PBP_LR_R:
                case _4P_RT:

                    return _REG_SUB1_PAGE;

                case _4P_RB:

                    return _REG_SUB2_PAGE;

                case _1P_NORMAL_FULL_REGION:
                case _1P_ROTATION_FULL_REGION:
                case _PIP_MAIN:
                case _PBP_LR_L:
                case _PBP_TB_T:
                case _4P_LT:
                case _1P_NORMAL_DEMO_INSIDE:
                case _1P_NORMAL_DEMO_OUTSIDE:
                case _PIP_FULL_REGION:
                case _PBP_LR_FULL_REGION:
                case _PBP_TB_FULL_REGION:
                case _4P_FULL_REGION:
                case _4P_LT_OUTSIDE:
                case _4P_LB_OUTSIDE:
                case _4P_RT_OUTSIDE:
                case _4P_RB_OUTSIDE:
                case _PIP_DEMO_INSIDE:
                case _PIP_DEMO_OUTSIDE:
                case _PBP_LR_DEMO_INSIDE:
                case _PBP_LR_DEMO_OUTSIDE:
                case _PBP_TB_DEMO_INSIDE:
                case _PBP_TB_DEMO_OUTSIDE:
                case _4P_DEMO_INSIDE:
                case _4P_DEMO_OUTSIDE:
                default:

                    return _REG_MAIN1_PAGE;
            }

        case _REG_DDOMAIN_AFTER_BLENDING:
            switch(enumSelRegion)
            {
                case _1P_NORMAL_FULL_REGION:
                case _1P_ROTATION_FULL_REGION:
                case _PIP_FULL_REGION:
                case _PBP_LR_FULL_REGION:
                case _PBP_TB_FULL_REGION:
                case _4P_FULL_REGION:
                case _PIP_MAIN:
                case _PBP_LR_L:
                case _PBP_TB_T:
                case _4P_LT_OUTSIDE:
                case _4P_LB_OUTSIDE:
                case _4P_RT_OUTSIDE:
                case _4P_RB_OUTSIDE:
                case _1P_NORMAL_DEMO_OUTSIDE:
                case _PIP_DEMO_OUTSIDE:
                case _PBP_LR_DEMO_OUTSIDE:
                case _PBP_TB_DEMO_OUTSIDE:
                case _4P_DEMO_OUTSIDE:

                    return _REG_MAIN1_PAGE;

                case _PIP_SUB:
                case _PBP_LR_R:
                case _PBP_TB_B:
                case _4P_LT:
                case _4P_LB:
                case _4P_RT:
                case _4P_RB:
                case _1P_NORMAL_DEMO_INSIDE:
                case _PIP_DEMO_INSIDE:
                case _PBP_LR_DEMO_INSIDE:
                case _PBP_TB_DEMO_INSIDE:
                case _4P_DEMO_INSIDE:
                default:

                    return _REG_MAIN2_PAGE;
            }

        default:
            return _REG_MAIN1_PAGE;
    }

    return _REG_MAIN1_PAGE;
}

//--------------------------------------------------
// Description  : Get Inverse SelRegion from SelRegion
// Input Value  : EnumSelRegion
// Output Value : EnumSelRegion
//--------------------------------------------------
EnumSelRegion ScalerRegionGetInverse(EnumSelRegion enumSelRegion)
{
    switch(enumSelRegion)
    {
        case _1P_NORMAL_FULL_REGION:
        case _1P_ROTATION_FULL_REGION:
        case _PIP_FULL_REGION:
        case _PBP_LR_FULL_REGION:
        case _PBP_TB_FULL_REGION:
        case _4P_FULL_REGION:
            return _NON_REGION;

        case _PIP_SUB:
            return _PIP_MAIN;

        case _PBP_LR_L:
            return _PBP_LR_R;

        case _PBP_TB_T:
            return _PBP_TB_B;

        case _4P_LT:
            return _4P_LT_OUTSIDE;

        case _4P_LB:
            return _4P_LB_OUTSIDE;

        case _4P_RT:
            return _4P_RT_OUTSIDE;

        case _4P_RB:
            return _4P_RB_OUTSIDE;

        case _1P_NORMAL_DEMO_INSIDE:
            return _1P_NORMAL_DEMO_OUTSIDE;

        case _PIP_DEMO_INSIDE:
            return _PIP_DEMO_OUTSIDE;

        case _PBP_LR_DEMO_INSIDE:
            return _PBP_LR_DEMO_OUTSIDE;

        case _PBP_TB_DEMO_INSIDE:
            return _PBP_TB_DEMO_OUTSIDE;

        case _4P_DEMO_INSIDE:
            return _4P_DEMO_OUTSIDE;

        case _PIP_MAIN:
            return _PIP_SUB;

        case _PBP_LR_R:
            return _PBP_LR_L;

        case _PBP_TB_B:
            return _PBP_TB_T;

        case _4P_LT_OUTSIDE:
            return _4P_LT;

        case _4P_LB_OUTSIDE:
            return _4P_LB;

        case _4P_RT_OUTSIDE:
            return _4P_RT;

        case _4P_RB_OUTSIDE:
            return _4P_RB;

        case _1P_NORMAL_DEMO_OUTSIDE:
            return _1P_NORMAL_DEMO_INSIDE;

        case _PIP_DEMO_OUTSIDE:
            return _PIP_DEMO_INSIDE;

        case _PBP_LR_DEMO_OUTSIDE:
            return _PBP_LR_DEMO_INSIDE;

        case _PBP_TB_DEMO_OUTSIDE:
            return _PBP_TB_DEMO_INSIDE;

        case _4P_DEMO_OUTSIDE:
            return _4P_DEMO_INSIDE;

        default:
            return _1P_NORMAL_FULL_REGION;
    }

    return _1P_NORMAL_FULL_REGION;
}

#if(_ULTRA_VIVID_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get UltraVivid Active Path
// Input Value  : enumSelRegion
// Output Value : Active Input Data Path
//--------------------------------------------------
BYTE ScalerRegionGetUltraVividActivePath(EnumSelRegion enumSelRegion)
{
    switch(enumSelRegion)
    {
        case _1P_NORMAL_FULL_REGION:
        case _1P_ROTATION_FULL_REGION:
        case _PIP_MAIN:
        case _PBP_LR_L:
        case _PBP_TB_T:
        case _4P_LT:
        case _1P_NORMAL_DEMO_OUTSIDE:

            return _INPUT_PATH_M1;

        case _4P_LB:
        case _1P_NORMAL_DEMO_INSIDE:

            return _INPUT_PATH_M2;

        case _PBP_TB_B: // IDLTI:S1     LSR,SHP:M2

            return (_INPUT_PATH_M2 | _INPUT_PATH_S1);

        case _PIP_SUB:
        case _PBP_LR_R:
        case _4P_RT:

            return _INPUT_PATH_S1;

        case _4P_RB:

            return _INPUT_PATH_S2;

        case _4P_LT_OUTSIDE:

            return (_INPUT_PATH_M2 | _INPUT_PATH_S1 | _INPUT_PATH_S2);

        case _4P_LB_OUTSIDE:

            return (_INPUT_PATH_M1 | _INPUT_PATH_S1 | _INPUT_PATH_S2);

        case _4P_RT_OUTSIDE:

            return (_INPUT_PATH_M1 | _INPUT_PATH_M2 | _INPUT_PATH_S2);

        case _4P_RB_OUTSIDE:

            return (_INPUT_PATH_M1 | _INPUT_PATH_M2 | _INPUT_PATH_S1);

        case _PIP_DEMO_INSIDE:
        case _PBP_LR_DEMO_INSIDE:

            return (_INPUT_PATH_M2 | _INPUT_PATH_S2);

        case _PIP_DEMO_OUTSIDE:
        case _PBP_LR_DEMO_OUTSIDE:
        case _PIP_FULL_REGION:
        case _PBP_LR_FULL_REGION:

            return (_INPUT_PATH_M1 | _INPUT_PATH_S1);

        case _NON_REGION:

            return _INPUT_PATH_NONE;

        case _PBP_TB_FULL_REGION:
        case _PBP_TB_DEMO_INSIDE:
        case _PBP_TB_DEMO_OUTSIDE:
        case _4P_FULL_REGION:
        case _4P_DEMO_INSIDE:
        case _4P_DEMO_OUTSIDE:
        default:

            return _INPUT_PATH_ALL;
    }
}
#endif

//--------------------------------------------------
// Description  : Check HW Selec Area From SelRegion
// Input Value  : SelRegion
// Output Value : HW Sellect Area Inside/Outside/Full
//--------------------------------------------------
EnumHLWType ScalerRegionGetSelectArea(EnumSelRegion enumSelRegion)
{
    switch(enumSelRegion)
    {
        case _1P_NORMAL_FULL_REGION:
        case _1P_ROTATION_FULL_REGION:
        case _PIP_FULL_REGION:
        case _PBP_LR_FULL_REGION:
        case _PBP_TB_FULL_REGION:
        case _4P_FULL_REGION:
        default:

            return _HLW_FULL_WINDOW;

        case _PIP_SUB:
        case _PBP_LR_R:
        case _PBP_TB_B:
        case _4P_LT:
        case _4P_LB:
        case _4P_RT:
        case _4P_RB:
        case _1P_NORMAL_DEMO_INSIDE:
        case _PIP_DEMO_INSIDE:
        case _PBP_LR_DEMO_INSIDE:
        case _PBP_TB_DEMO_INSIDE:
        case _4P_DEMO_INSIDE:

            return _HLW_INSIDE_WINDOW;

        case _PIP_MAIN:
        case _PBP_LR_L:
        case _PBP_TB_T:
        case _4P_LT_OUTSIDE:
        case _4P_LB_OUTSIDE:
        case _4P_RT_OUTSIDE:
        case _4P_RB_OUTSIDE:
        case _1P_NORMAL_DEMO_OUTSIDE:
        case _PIP_DEMO_OUTSIDE:
        case _PBP_LR_DEMO_OUTSIDE:
        case _PBP_TB_DEMO_OUTSIDE:
        case _4P_DEMO_OUTSIDE:

            return _HLW_OUTSIDE_WINDOW;
    }
}
