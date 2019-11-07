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
// ID Code      : RL6193_Series_Osd.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6193_SERIES_OSD__

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
void ScalerOsdDoubleFunction(EnumOsdDoubleWidthType enumOsdDoubleWidthType, EnumOsdDoubleHeightType enumOsdDoubleHeightType);
void ScalerOsdMapRotation(EnumOsdRotateType enumOsdRotateType, EnumOsdRotateMapA enumOsdRotateMapA, BYTE ucMapARowSize, EnumOsdRotateMapB enumOsdRotateMapB, BYTE ucMapBRowSize, EnumOsdRotateFontLib enumOsdRotateFontLib);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Osd double function
// Input Value  : enumOsdDoubleWidthType  -> _OSD_DOUBLE_WIDTH_DISABLE or _OSD_DOUBLE_WIDTH_ENABLE
//              : enumOsdDoubleHeightType -> _OSD_DOUBLE_HEIGHT_DISABLE or _OSD_DOUBLE_HEIGHT_ENABLE
// Output Value : None
// Example      : ScalerOsdDoubleFunction(_OSD_DOUBLE_WIDTH_ENABLE, _OSD_DOUBLE_HEIGHT_ENABLE);:
//--------------------------------------------------
void ScalerOsdDoubleFunction(EnumOsdDoubleWidthType enumOsdDoubleWidthType, EnumOsdDoubleHeightType enumOsdDoubleHeightType)
{
#if(_OSD_POSITION_OFFSET_CORRECTION == _OFF)
    if((enumOsdDoubleWidthType == _OSD_DOUBLE_WIDTH_ENABLE) && (enumOsdDoubleHeightType == _OSD_DOUBLE_HEIGHT_ENABLE))
    {
        ScalerOsdPositionOffset(_OSD_POSITION_OFFSET_GLOBAL, X_POS(_OSD_DOUBLE_POSITION_OFFSET_H), Y_POS(_OSD_DOUBLE_POSITION_OFFSET_V));

        ScalerSetBit(P3A_1E_FRAME_CTRL_1E, ~(_BIT7 | _BIT3), (_BIT7 | _BIT3));
    }
    else
    {
        ScalerOsdPositionOffset(_OSD_POSITION_OFFSET_GLOBAL, X_POS(_OSD_POSITION_OFFSET_H), Y_POS(_OSD_POSITION_OFFSET_V));

        ScalerSetBit(P3A_1E_FRAME_CTRL_1E, ~(_BIT7 | _BIT3), 0x00);
    }
#endif

    // Set Double Height Enable/Disable (For All OSD Including Windows And Characters)
    ScalerSetBit(P3A_0A_FRAME_CTRL_0A, ~(_BIT0), enumOsdDoubleHeightType);

    // Set Double Width Enable/Disable (For All OSD Including Windows And Characters)
    ScalerSetBit(P3A_0A_FRAME_CTRL_0A, ~(_BIT1), (enumOsdDoubleWidthType << 1));


#if(_OSD_POSITION_OFFSET_CORRECTION == _ON)
    ScalerOsdPositionOffsetCorrection();
#endif
}

//--------------------------------------------------
// Description  : Set Osd rotation
// Input Value  : ucRotateFlage -> Rotate status (now)
//                enumOsdRotateType    -> _OSD_ROTATE_DEGREE_0 or _OSD_ROTATE_DEGREE_90 or _OSD_ROTATE_DEGREE_270 or _OSD_ROTATE_DEGREE_180
//                enumOsdRotateMapA    -> _OSD_MAP_A_REMAPPING_DISABLE or _OSD_MAP_A_REMAPPING_ENABLE
//                ucMapARowSize        -> MapA Row size
//                enumOsdRotateMapB    -> _OSD_MAP_B_REMAPPING_DISABLE or _OSD_MAP_B_REMAPPING_ENABLE
//                ucMapBRowSize        -> MapB Row size
//                enumOsdRotateFontLib -> _OSD_FONT_LIB_ROTATION_DISABLE or _OSD_FONT_LIB_ROTATION_ENABLE
// Output Value : None
// Note         : Font Scale up, Double Width/Height, and Auto Rotation&Remap. These three features cannot be open at the same time.
//--------------------------------------------------
void ScalerOsdMapRotation(EnumOsdRotateType enumOsdRotateType, EnumOsdRotateMapA enumOsdRotateMapA, BYTE ucMapARowSize, EnumOsdRotateMapB enumOsdRotateMapB, BYTE ucMapBRowSize, EnumOsdRotateFontLib enumOsdRotateFontLib)
{
    BYTE ucTemp = 0;

    ucTemp = ScalerGetByte(P3A_41_FRAME_CTRL_41);

    // _BIT2 : Enable Font A Remapping, _BIT1 : Enable Font B Remapping.
    ScalerSetBit(P3A_41_FRAME_CTRL_41, ~(_BIT2 | _BIT1), ((enumOsdRotateMapA << 2) | (enumOsdRotateMapB << 1)));

    if((ucTemp & _BIT0) == _BIT0) // OSD Auto Rotation Enable
    {
        if((ucTemp & _BIT4) == _BIT4)  // OSD Auto Rotation Direction
        {
            ucTemp = _OSD_ROTATE_DEGREE_90;     // CW
        }
        else
        {
            ucTemp = _OSD_ROTATE_DEGREE_270;    // CCW
        }
    }
    else
    {
        ucTemp = _OSD_ROTATE_DEGREE_0;
    }

    // Set Row Total Number
    ScalerSetByte(P3A_3E_FRAME_CTRL_3E, ucMapARowSize);

    // Set Font A Row Total Number
    ScalerSetByte(P3A_3F_FRAME_CTRL_3F, ucMapARowSize);

    // Set Font B Row Total Number
    ScalerSetByte(P3A_40_FRAME_CTRL_40, ucMapBRowSize);

#if(_OSD_POSITION_OFFSET_CORRECTION == _ON)

    if(ucTemp != enumOsdRotateType)
    {
        // rotate to 0 degree
        switch(ucTemp)
        {
            case _OSD_ROTATE_DEGREE_0:
                break;

            case _OSD_ROTATE_DEGREE_90:
                ScalerSetByte(P3A_0B_FRAME_CTRL_0B, 0x00);
                ScalerSetByte(P3A_41_FRAME_CTRL_41, (_BIT4 | _BIT3)); // _OSD_ROTATE_CW
                ScalerOsdFontLibraryRotation();
                break;

            case _OSD_ROTATE_DEGREE_270:
                ScalerSetByte(P3A_0B_FRAME_CTRL_0B, 0x00);
                ScalerSetByte(P3A_41_FRAME_CTRL_41, (_BIT3)); // _OSD_ROTATE_CW
                ScalerOsdFontLibraryRotation();
                break;

            default:
                break;
        }

        if(ScalerGetBit(P3A_02_FRAME_CTRL_02, _BIT0) != _BIT0)
        {
            ScalerOsdCircuitActivated(_ENABLE);
            ScalerTimerWaitForIDDomainEvent(_EVENT_DVS, _DISPLAY_PATH_ALL);
            ScalerTimerWaitForIDDomainEvent(_EVENT_DVS, _DISPLAY_PATH_ALL);
            ScalerTimerWaitForIDDomainEvent(_EVENT_DVS, _DISPLAY_PATH_ALL);
        }

        // rotate to target direction
        switch(enumOsdRotateType)
        {
            case _OSD_ROTATE_DEGREE_0:
                break;

            case _OSD_ROTATE_DEGREE_90:
                ScalerSetByte(P3A_0B_FRAME_CTRL_0B, 0x01);
                ScalerSetByte(P3A_41_FRAME_CTRL_41, ((_BIT4 | (BYTE)enumOsdRotateFontLib << 3 | (BYTE)enumOsdRotateMapA << 2 | (BYTE)enumOsdRotateMapB << 1) | _BIT0));       // _OSD_ROTATE_CW
                ScalerOsdFontLibraryRotation();
                break;

            case _OSD_ROTATE_DEGREE_270:
                ScalerSetByte(P3A_0B_FRAME_CTRL_0B, 0x01);
                ScalerSetByte(P3A_41_FRAME_CTRL_41, (((BYTE)enumOsdRotateFontLib << 3 | (BYTE)enumOsdRotateMapA << 2 | (BYTE)enumOsdRotateMapB << 1) | _BIT0));               // _OSD_ROTATE_CCW
                ScalerOsdFontLibraryRotation();
                break;

            default:
                break;
        }
    }

    // align window & font
    ScalerOsdFontWindowVericalAlignemnt(_ENABLE);
    if((enumOsdRotateType == _OSD_ROTATE_DEGREE_90) || (enumOsdRotateType == _OSD_ROTATE_DEGREE_270))
    {
        ScalerOsdPositionOffset(_OSD_POSITION_OFFSET_WINDOW, X_POS(11), Y_POS(0));
    }
    else
    {
        ScalerOsdPositionOffset(_OSD_POSITION_OFFSET_WINDOW, X_POS(10), Y_POS(0));
    }

    // correct offset
    ScalerOsdPositionOffsetCorrection();

#else
    if(ucTemp == enumOsdRotateType)
    {
        return;
    }

    if(ucTemp == _OSD_ROTATE_DEGREE_90)
    {
        ScalerSetByte(P3A_0B_FRAME_CTRL_0B, 0x00);
        ScalerSetByte(P3A_41_FRAME_CTRL_41, (_BIT4 | _BIT3)); // _OSD_ROTATE_CW

        ScalerOsdFontLibraryRotation();
    }
    else if(ucTemp == _OSD_ROTATE_DEGREE_270)
    {
        ScalerSetByte(P3A_0B_FRAME_CTRL_0B, 0x00);
        ScalerSetByte(P3A_41_FRAME_CTRL_41, (_BIT3)); // _OSD_ROTATE_CW

        ScalerOsdFontLibraryRotation();
    }

    if(ScalerGetBit(P3A_02_FRAME_CTRL_02, _BIT0) != _BIT0)
    {
        ScalerOsdCircuitActivated(_ENABLE);
        ScalerTimerWaitForIDDomainEvent(_EVENT_DVS, _DISPLAY_PATH_ALL);
        ScalerTimerWaitForIDDomainEvent(_EVENT_DVS, _DISPLAY_PATH_ALL);
        ScalerTimerWaitForIDDomainEvent(_EVENT_DVS, _DISPLAY_PATH_ALL);
    }

    if((ScalerGetBit(P3A_0A_FRAME_CTRL_0A, _BIT0) == _BIT0) && (ScalerGetBit(P3A_0A_FRAME_CTRL_0A, _BIT1) == _BIT1))
    {
        if((enumOsdRotateType == _OSD_ROTATE_DEGREE_90) || (enumOsdRotateType == _OSD_ROTATE_DEGREE_270))
        {
            ScalerOsdPositionOffset(_OSD_POSITION_OFFSET_GLOBAL, X_POS(_OSD_DOUBLE_POSITION_OFFSET_H - 1), Y_POS(_OSD_DOUBLE_POSITION_OFFSET_V));
        }
        else
        {
            ScalerOsdPositionOffset(_OSD_POSITION_OFFSET_GLOBAL, X_POS(_OSD_DOUBLE_POSITION_OFFSET_H), Y_POS(_OSD_DOUBLE_POSITION_OFFSET_V));
        }
    }
    else
    {
        if((enumOsdRotateType == _OSD_ROTATE_DEGREE_90) || (enumOsdRotateType == _OSD_ROTATE_DEGREE_270))
        {
            ScalerOsdPositionOffset(_OSD_POSITION_OFFSET_GLOBAL, X_POS(_OSD_POSITION_OFFSET_H - 1), Y_POS(_OSD_POSITION_OFFSET_V));
        }
        else
        {
            ScalerOsdPositionOffset(_OSD_POSITION_OFFSET_GLOBAL, X_POS(_OSD_POSITION_OFFSET_H), Y_POS(_OSD_POSITION_OFFSET_V));
        }
    }

    if(enumOsdRotateType == _OSD_ROTATE_DEGREE_0)
    {
        return;
    }
    else if(enumOsdRotateType == _OSD_ROTATE_DEGREE_90)
    {
        ScalerSetByte(P3A_0B_FRAME_CTRL_0B, 0x01);
        ScalerSetByte(P3A_41_FRAME_CTRL_41, ((_BIT4 | (BYTE)enumOsdRotateFontLib << 3 | (BYTE)enumOsdRotateMapA << 2 | (BYTE)enumOsdRotateMapB << 1) | _BIT0));       // _OSD_ROTATE_CW
    }
    else if(enumOsdRotateType == _OSD_ROTATE_DEGREE_270)
    {
        ScalerSetByte(P3A_0B_FRAME_CTRL_0B, 0x01);
        ScalerSetByte(P3A_41_FRAME_CTRL_41, (((BYTE)enumOsdRotateFontLib << 3 | (BYTE)enumOsdRotateMapA << 2 | (BYTE)enumOsdRotateMapB << 1) | _BIT0));               // _OSD_ROTATE_CCW
    }

    ScalerOsdFontLibraryRotation();
#endif
}

