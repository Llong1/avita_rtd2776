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
// ID Code      : SysRegion.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SYSTEM_REGION__

#include "SysInclude.h"

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
StructRegionInfoType g_stRegionInfo;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void SysRegionInitial(void);

void SysRegionUpdateInterface(EnumDisplayRegion enumDisplayRegion, EnumSourceSearchPort enumSourceSearchPort);
void SysRegionResetInfo(void);

EnumDisplayState SysRegionGetDisplayState(EnumDisplayRegion enumDisplayRegion);
EnumSourceTypeDef SysRegionGetSourceType(EnumDisplayRegion enumDisplayRegion);
EnumSourceSearchPort SysRegionGetPortType(EnumDisplayRegion enumDisplayRegion);
EnumDisplayRegion SysRegionGetDisplayRegion(EnumRegionIndex enumRegionIndex);
BYTE SysRegionGetSourceIndex(BYTE ucRgnNum);

bit SysRegionCheckAllDisplayState(EnumDisplayState enumDisplayState);
bit SysRegionCheckSystemDisplayStateChange(void);
bit SysRegionCheckUserDisplayStateChange(void);
bit SysRegionCheckDisplayEvent(EnumDisplayRegion enumDisplayRegion, EnumDisplayEvent enumDisplayEvent);
void SysRegionClearAllDisplayEvent(BYTE ucDisplayEventSet);

void SysRegionSetMeasureResultPointerRegion(EnumDisplayRegion enumDisplayRegion);
EnumDisplayRegion SysRegionGetMeasureResultPointerRegion(void);

EnumDisplayRegion SysRegionConvertPortToRegion(EnumSourceSearchPort enumSourceSearchPort);
EnumRegionIndex SysRegionConvertPortToRegionIndex(EnumSourceSearchPort enumSourceSearchPort);
EnumRegionIndex SysRegionConvertSourceIndexToRegionIndex(BYTE ucSearchIndex);

BYTE SysRegionGetDisplayStateCount(EnumDisplayState enumDisplayState);
void SysRegionSetDisplayStateBySearchIndex(BYTE ucSearchIndex, EnumDisplayState enumDisplayState);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : Initial region related variables
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysRegionInitial(void)
{
    // Load select region
    SET_MODE_DISPLAY_MODE(UserCommonNVRamGetSystemData(_DISPLAY_MODE));

    // Update region count
    UPD_RGN_MAX_DISPLAY_REGION();

    // Load region port index
    SET_RGN_SOURCE_INDEX(0, SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_0)));

#if(_MULTI_DISPLAY_MAX >= 0x02)
    SET_RGN_SOURCE_INDEX(1, SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_1)));

#if(_4P_DISPLAY_SUPPORT == _ON)
    SET_RGN_SOURCE_INDEX(2, SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_2)));
    SET_RGN_SOURCE_INDEX(3, SysSourceConvertSearchPort(UserCommonNVRamGetSystemData(_SEARCH_PORT_3)));
#endif
#endif
}

//--------------------------------------------------
// Description  : Set select region / physical port pair
// Input Value  : Region & select port
// Output Value : None
//--------------------------------------------------
void SysRegionUpdateInterface(EnumDisplayRegion enumDisplayRegion, EnumSourceSearchPort enumSourceSearchPort)
{
    BYTE ucRegionIndex = ScalerRegionGetIndex(enumDisplayRegion);

    DebugMessageSystem("UPD: Region", enumDisplayRegion);
    DebugMessageSystem("UPD: input port", enumSourceSearchPort);

    // Update select retion & search port
    SET_RGN_SOURCE_INDEX(ucRegionIndex, SysSourceConvertSearchPort(enumSourceSearchPort));

    // Reset display status info
    CLR_RGN_DISPLAY_INFO(ucRegionIndex);
}

//--------------------------------------------------
// Description  : Reset select interface info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysRegionResetInfo(void)
{
    memset(&g_stRegionInfo, 0x00, sizeof(StructRegionInfoType));
}

//--------------------------------------------------
// Description  : Get display state of specific region
// Input Value  : select region
// Output Value : display state
//--------------------------------------------------
EnumDisplayState SysRegionGetDisplayState(EnumDisplayRegion enumDisplayRegion)
{
    return GET_RGN_DISPLAY_STATE(ScalerRegionGetIndex(enumDisplayRegion));
}

//--------------------------------------------------
// Description  : Get source type of specific region
// Input Value  : select reigon
// Output Value : source type
//--------------------------------------------------
EnumSourceTypeDef SysRegionGetSourceType(EnumDisplayRegion enumDisplayRegion)
{
    return GET_RGN_SOURCE_TYPE(ScalerRegionGetIndex(enumDisplayRegion));
}

//--------------------------------------------------
// Description  : Get port type of specific region
// Input Value  : select reigon
// Output Value : port type
//--------------------------------------------------
EnumSourceSearchPort SysRegionGetPortType(EnumDisplayRegion enumDisplayRegion)
{
    return GET_RGN_INPUT_PORT(ScalerRegionGetIndex(enumDisplayRegion));
}

//--------------------------------------------------
// Description  : Get display region enum by region index
// Input Value  : region index
// Output Value : display region enum
//--------------------------------------------------
EnumDisplayRegion SysRegionGetDisplayRegion(EnumRegionIndex enumRegionIndex)
{
    return GET_RGN_DISPLAY_REGION(enumRegionIndex);
}

//--------------------------------------------------
// Description  : Get Region Source Index
// Input Value  : ucRgnNum --> Region Number
// Output Value : GET_RGN_SOURCE_INDEX(ucRgnNum)
//--------------------------------------------------
BYTE SysRegionGetSourceIndex(BYTE ucRgnNum)
{
    return GET_RGN_SOURCE_INDEX(ucRgnNum);
}

//--------------------------------------------------
// Description  : Check whether all displays equal to give one
// Input Value  : display state
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit SysRegionCheckAllDisplayState(EnumDisplayState enumDisplayState)
{
    switch(GET_MODE_DISPLAY_MODE())
    {
        case _DISPLAY_MODE_1P:
            return (GET_RGN_DISPLAY_STATE(0) == enumDisplayState);

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_4P:
            return ((GET_RGN_DISPLAY_STATE(0) == enumDisplayState) &&
                    (GET_RGN_DISPLAY_STATE(1) == enumDisplayState) &&
                    (GET_RGN_DISPLAY_STATE(2) == enumDisplayState) &&
                    (GET_RGN_DISPLAY_STATE(3) == enumDisplayState));
#endif

#if(_2P_DISPLAY_SUPPORT == _ON)
        default:
            return ((GET_RGN_DISPLAY_STATE(0) == enumDisplayState) &&
                    (GET_RGN_DISPLAY_STATE(1) == enumDisplayState));
#endif
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Check whether all system display state changed
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit SysRegionCheckSystemDisplayStateChange(void)
{
    switch(GET_MODE_DISPLAY_MODE())
    {
#if(_4P_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_4P:
            return ((GET_RGN_DISPLAY_STATE_CHANGE_SYS(0) == _TRUE) ||
                    (GET_RGN_DISPLAY_STATE_CHANGE_SYS(1) == _TRUE) ||
                    (GET_RGN_DISPLAY_STATE_CHANGE_SYS(2) == _TRUE) ||
                    (GET_RGN_DISPLAY_STATE_CHANGE_SYS(3) == _TRUE));
#endif

#if(_2P_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_PIP:
        case _DISPLAY_MODE_PBP_LR:
        case _DISPLAY_MODE_PBP_TB:
            return ((GET_RGN_DISPLAY_STATE_CHANGE_SYS(0) == _TRUE) ||
                    (GET_RGN_DISPLAY_STATE_CHANGE_SYS(1) == _TRUE));
#endif

        default:
            break;
    }

    return GET_RGN_DISPLAY_STATE_CHANGE_SYS(0);
}

//--------------------------------------------------
// Description  : Check whether all user display state changed
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit SysRegionCheckUserDisplayStateChange(void)
{
    switch(GET_MODE_DISPLAY_MODE())
    {
#if(_4P_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_4P:
            return ((GET_RGN_DISPLAY_STATE_CHANGE_USR(0) == _TRUE) ||
                    (GET_RGN_DISPLAY_STATE_CHANGE_USR(1) == _TRUE) ||
                    (GET_RGN_DISPLAY_STATE_CHANGE_USR(2) == _TRUE) ||
                    (GET_RGN_DISPLAY_STATE_CHANGE_USR(3) == _TRUE));
#endif

#if(_2P_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_PIP:
        case _DISPLAY_MODE_PBP_LR:
        case _DISPLAY_MODE_PBP_TB:
            return ((GET_RGN_DISPLAY_STATE_CHANGE_USR(0) == _TRUE) ||
                    (GET_RGN_DISPLAY_STATE_CHANGE_USR(1) == _TRUE));
#endif

        default:
            break;
    }

    return GET_RGN_DISPLAY_STATE_CHANGE_USR(0);
}

//--------------------------------------------------
// Description  : Check specific region event occurs
// Input Value  : enumDisplayRegion --> select region
//                enumDisplayEvent --> display event
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit SysRegionCheckDisplayEvent(EnumDisplayRegion enumDisplayRegion, EnumDisplayEvent enumDisplayEvent)
{
    BYTE ucRegionIndex = ScalerRegionGetIndex(enumDisplayRegion);

    switch(enumDisplayEvent)
    {
        case _DISPLAY_EVENT_TIMING_CONFIRMED:
            return GET_RGN_TIMING_CONFIRM(ucRegionIndex);

        case _DISPLAY_EVENT_TIMING_DOUBLE_CHECK:
            return GET_RGN_TIMING_DOUBLE_CHECK(ucRegionIndex);

        case _DISPLAY_EVENT_MEASURE_CHECKING:
            return GET_RGN_MEASURE_CHECKING(ucRegionIndex);

        case _DISPLAY_EVENT_FIRST_ACTIVE:
            return GET_RGN_FIRST_ACTIVE(ucRegionIndex);

        case _DISPLAY_EVENT_STATE_CHANGE_SYS:
            return GET_RGN_DISPLAY_STATE_CHANGE_SYS(ucRegionIndex);

        case _DISPLAY_EVENT_STATE_CHANGE_USR:
            return GET_RGN_DISPLAY_STATE_CHANGE_USR(ucRegionIndex);

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Clear display event flags for all regions
// Input Value  : ucDisplayEventSet --> combination of display event
// Output Value : None
//--------------------------------------------------
void SysRegionClearAllDisplayEvent(BYTE ucDisplayEventSet)
{
    BYTE ucIndex = GET_RGN_MAX_DISPLAY_REGION();

    do
    {
        g_stRegionInfo.pstDisplayStatusInfo[--ucIndex].enumDisplayEvent &= ~ucDisplayEventSet;
    }while(ucIndex != 0x00);
}

//--------------------------------------------------
// Description  : Measure Active Start / End using auto-funcgion
// Input Value  : EnumDisplayRegion --> select measure region
// Output Value : None
//--------------------------------------------------
void SysRegionSetMeasureResultPointerRegion(EnumDisplayRegion enumDisplayRegion)
{
    // Set measure result pointer
    g_pstRegionTimingInfoPointer = &(g_pstRegionTimingInfo[ScalerRegionGetIndex(enumDisplayRegion)]);
}

//--------------------------------------------------
// Description  : Measure Active Start / End using auto-funcgion
// Input Value  : EnumDisplayRegion --> select measure region
// Output Value : None
//--------------------------------------------------
EnumDisplayRegion SysRegionGetMeasureResultPointerRegion(void)
{
    return GET_RGN_DISPLAY_REGION(g_pstRegionTimingInfoPointer - g_pstRegionTimingInfo);
}

//--------------------------------------------------
// Description  : Convert input port to select region, if existed
// Input Value  : enumSourceSearchPort --> input port
// Output Value : select region
//--------------------------------------------------
EnumDisplayRegion SysRegionConvertPortToRegion(EnumSourceSearchPort enumSourceSearchPort)
{
    BYTE ucRegionIndex = SysRegionConvertPortToRegionIndex(enumSourceSearchPort);

    if(ucRegionIndex != _REGION_INDEX_NONE)
    {
        return GET_RGN_DISPLAY_REGION(ucRegionIndex);
    }

    return _DISPLAY_RGN_NONE;
}

//--------------------------------------------------
// Description  : Convert input port to region index, if existed
// Input Value  : enumSourceSearchPort --> input port
// Output Value : region index
//--------------------------------------------------
EnumRegionIndex SysRegionConvertPortToRegionIndex(EnumSourceSearchPort enumSourceSearchPort)
{
    BYTE ucIndex = 0;

    for(ucIndex = 0; ucIndex < GET_RGN_MAX_DISPLAY_REGION(); ++ucIndex)
    {
        if(GET_RGN_INPUT_PORT(ucIndex) == enumSourceSearchPort)
        {
            return ucIndex;
        }
    }

    return _REGION_INDEX_NONE;
}

//--------------------------------------------------
// Description  : Convert source search index to region index, if existed
// Input Value  : ucSearchIndex --> source search index
// Output Value : region index
//--------------------------------------------------
EnumRegionIndex SysRegionConvertSourceIndexToRegionIndex(BYTE ucSearchIndex)
{
    BYTE ucIndex = 0;

    for(ucIndex = 0; ucIndex < GET_RGN_MAX_DISPLAY_REGION(); ++ucIndex)
    {
        if(GET_RGN_SOURCE_INDEX(ucIndex) == ucSearchIndex)
        {
            return ucIndex;
        }
    }

    return _REGION_INDEX_NONE;
}

//--------------------------------------------------
// Description  : Calculate current display state numbers
// Input Value  : display state
// Output Value : count result
//--------------------------------------------------
BYTE SysRegionGetDisplayStateCount(EnumDisplayState enumDisplayState)
{
    if(enumDisplayState == _DISPLAY_STATE_MAX)
    {
        return GET_RGN_MAX_DISPLAY_REGION();
    }

    switch(GET_MODE_DISPLAY_MODE())
    {
        case _DISPLAY_MODE_1P:
            return (BYTE)(GET_RGN_DISPLAY_STATE(0) == enumDisplayState);

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_4P:

            return ((BYTE)(GET_RGN_DISPLAY_STATE(0) == enumDisplayState) +
                    (BYTE)(GET_RGN_DISPLAY_STATE(1) == enumDisplayState) +
                    (BYTE)(GET_RGN_DISPLAY_STATE(2) == enumDisplayState) +
                    (BYTE)(GET_RGN_DISPLAY_STATE(3) == enumDisplayState));
#endif

#if(_2P_DISPLAY_SUPPORT == _ON)
        default:
            return ((BYTE)(GET_RGN_DISPLAY_STATE(0) == enumDisplayState) +
                    (BYTE)(GET_RGN_DISPLAY_STATE(1) == enumDisplayState));
#endif
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Set display state for display regions with identical source index
// Input Value  : ucSearchIndex --> source search index
//             enumDisplayState --> display state
// Output Value : None
//--------------------------------------------------
void SysRegionSetDisplayStateBySearchIndex(BYTE ucSearchIndex, EnumDisplayState enumDisplayState)
{
    BYTE ucRegionIndex = 0;

    for(ucRegionIndex = 0; ucRegionIndex < GET_RGN_MAX_DISPLAY_REGION(); ++ucRegionIndex)
    {
        if(GET_RGN_SOURCE_INDEX(ucRegionIndex) == ucSearchIndex)
        {
            DebugMessageSystem("Port state update", ucRegionIndex);

            switch(enumDisplayState)
            {
                case _DISPLAY_STATE_NONE:
                    SET_RGN_DISPLAY_ACTION(ucRegionIndex, _DISPLAY_ACTION_RESET_TO_NONE);
                    break;
                case _DISPLAY_STATE_NO_SIGNAL:
                    SET_RGN_DISPLAY_ACTION(ucRegionIndex, _DISPLAY_ACTION_NO_SIGNAL);
                    break;
                case _DISPLAY_STATE_OOR:
                    SET_RGN_DISPLAY_ACTION(ucRegionIndex, _DISPLAY_ACTION_OOR);
                    break;
                case _DISPLAY_STATE_DISPLAY_READY:
                    SET_RGN_DISPLAY_ACTION(ucRegionIndex, _DISPLAY_ACTION_DISPLAY_READY);
                    break;
                case _DISPLAY_STATE_ACTIVE:
                    SET_RGN_DISPLAY_ACTION(ucRegionIndex, _DISPLAY_ACTION_ACTIVE);
                    break;

                default:
                    break;
            }
        }
    }
}
