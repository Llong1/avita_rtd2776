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
// ID Code      : ScalerGlobal.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_GLOBAL__

#include "ScalerFunctionInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_2PCS)

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
#define _DB_FRAME_BUF_BLK_ADDR_OFFSET       ((DWORD)3840 << 12)  // 0xF0 0000
#else
#define _DB_FRAME_BUF_BLK_ADDR_OFFSET       ((DWORD)3072 << 12)  // 0xC0 0000
#endif

#elif((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_1PC)

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
#define _DB_FRAME_BUF_BLK_ADDR_OFFSET       ((DWORD)3840 << 11)  // 0x78 0000
#else
#define _DB_FRAME_BUF_BLK_ADDR_OFFSET       ((DWORD)3072 << 11)  // 0x60 0000
#endif

#endif

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
void ScalerGlobalDisplayInitial(EnumDisplayMode enumDisplayMode);
void ScalerGlobalIRQControl(bit bEn);
void ScalerGlobalSetIRQControl(BYTE ucIRQControl);
BYTE ScalerGlobalGetIRQControl(void);

void ScalerGlobalAddPortMapping(EnumSourceSearchPort enumSourceSearchPort, EnumDisplayDataPath enumDisplayDataPath);
void ScalerGlobalRemovePortMapping(EnumSourceSearchPort enumSourceSearchPort, EnumDisplayDataPath enumDisplayDataPath);
void ScalerGlobalResetPortMapping(void);

void ScalerGlobalWholeChipReset(void);

void ScalerGlobalSetWatchDogMapping(EnumDisplayMode enumDisplayMode);
void ScalerGlobalWatchDog(EnumDisplayRegion enumDisplayRegion, bit bEnable);

void ScalerGlobalCrystalClkSel(EnumClkSel enumSel);
void ScalerGlobalOsdInitial(void);
void ScalerGlobalResetProc(BYTE ucResetTarget);
void ScalerGlobalFirstActiveProc(BYTE ucSourceType, BYTE ucGetInputPort);
void ScalerGlobalSystemClkSel(EnumClkSel enumClockSel);

void ScalerGlobalDoubleBufferEnable(bit bEn);
void ScalerGlobalIDDomainDBSetTriggerEvent(EnumInputDataPath enumSelectedDataPath, EnumDBIDomainTriggerEvent enumTriggerEvent);
void ScalerGlobalIDDomainDBSetBufferAddress(StructDBDataPathGroup *pstDataPathGroupInfo);
void ScalerGlobalDDomainDBApply(EnumDBApply enumDBApply);
void ScalerGlobalIDomainDBApply(EnumInputDataPath enumInputDataPath, EnumDBApply enumDBApply);
void ScalerGlobalIDDomainDBGetDataPathGroup(EnumInputDataPath enumSelectedDataPath, StructDBDataPathGroup *pstDataPathGroupInfo);

#if((_OD_SUPPORT == _ON) && (_FRC_SUPPORT == _ON))
void ScalerGlobalSetInterrupt(EnumIRQ enumIRQType, BYTE ucEn);
#endif

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
void ScalerGlobalResetExtension(void);
#endif
bit ScalerGlobalGetDBStatus(void);
bit ScalerGlobalGetDDomainDBStatus(void);
bit ScalerGlobalGetIDomainDBStatus(void);
void ScalerGlobalIDDomainDBClearReadyBit(EnumInputDataPath enumSelectedDataPath);

#if(_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_BACKLIGHT)
void ScalerGlobalPreventGarbageByBacklight_EXINT0(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Global display initial process
// Input Value  : enumDisplayMode --> display mode
// Output Value : None
//--------------------------------------------------
void ScalerGlobalDisplayInitial(EnumDisplayMode enumDisplayMode)
{
    // Set scaling initial setting
    ScalerScalingSetInitial();

    // Disable FRC
    ScalerFRCEn(_FRC_ALL_ONOFF, _INPUT_PATH_ALL, _DISABLE);

    // Use information form Frame-Sync Mode
    ScalerFRCSetDDomainSourceSelect(_INPUT_PATH_ALL, _DDOMAIN_SRC_FRAM_FRAME_SYNC_MODE);

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    // Disable rotation
    ScalerRotationSetFRCEn(_FRC_ALL_ONOFF, _DISABLE);

    // Use information form Frame-Sync Mode
    ScalerRotationSetDDomainSourceSelect(_DDOMAIN_SRC_FRAM_FRAME_SYNC_MODE);
#endif

    // Set FRC Pre-Read
    ScalerFRCSetPreRead(_INPUT_PATH_ALL, _PRE_READ_MEMORY - 1);

#if(_OD_SUPPORT == _ON)

#if(_FRC_SUPPORT == _ON)
    // Release all FRC bandwidth
    ScalerMDomainReleaseFRCMemoryBW(_INPUT_PATH_ALL);
#endif

    ScalerMDomainODUseBitInitial();
#endif

    // Update watchdog mapping
    ScalerGlobalSetWatchDogMapping(enumDisplayMode);

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
    // Set DB sync mode
    ScalerGlobalSetDBSyncMode();
#endif

    // Enable global double buffer
    ScalerGlobalDoubleBufferEnable(_ENABLE);
}

//--------------------------------------------------
// Description  : Set Global IRQ Control Register
// Input Value  : CM_14_IRQ_CTRL0 Register Value
// Output Value : None
//--------------------------------------------------
void ScalerGlobalIRQControl(bit bEn)
{
    if(bEn == _ENABLE)
    {
        ScalerSetBit(P0_04_IRQ_CTRL0, ~_BIT7, _BIT7);
    }
    else
    {
        ScalerSetBit(P0_04_IRQ_CTRL0, ~_BIT7, 0x00);
    }
}

//--------------------------------------------------
// Description  : Set Global IRQ Control Register
// Input Value  : P0_04 and P40_04 register
// Output Value : None
//--------------------------------------------------
void ScalerGlobalSetIRQControl(BYTE ucIRQControl)
{
    ScalerSetByte(P0_04_IRQ_CTRL0, ucIRQControl);
}

//--------------------------------------------------
// Description  : Get Global IRQ Control Register
// Input Value  : None
// Output Value : P0_04 and P40_04 register
//--------------------------------------------------
BYTE ScalerGlobalGetIRQControl(void)
{
    return (ScalerGetByte(P0_04_IRQ_CTRL0));
}

//--------------------------------------------------
// Description  : Add Input Port Mapping
// Input Value  : enumSourceSearchPort --> Input Port
//                enumDisplayDataPath --> display data path
// Output Value : None
//--------------------------------------------------
void ScalerGlobalAddPortMapping(EnumSourceSearchPort enumSourceSearchPort, EnumDisplayDataPath enumDisplayDataPath)
{
    enumDisplayDataPath = enumDisplayDataPath;

    DebugMessageSystem("Add: port mapping", (((WORD)enumSourceSearchPort << 8) | enumDisplayDataPath));

    // Update source-data path mapping
    switch(enumSourceSearchPort)
    {
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
        case _A0_INPUT_PORT:

            break;
#endif


#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:

#if(_D0_TMDS_SUPPORT == _ON)
            SET_TMDS_RX0_FORCE_BCKGRD_PATH(enumDisplayDataPath);
#endif

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            SET_DP_RX0_FORCE_BCKGRD_PATH(enumDisplayDataPath);
#endif
            break;
#endif // End of #if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)


#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:

#if(_D1_TMDS_SUPPORT == _ON)
            SET_TMDS_RX1_FORCE_BCKGRD_PATH(enumDisplayDataPath);
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            SET_DP_RX1_FORCE_BCKGRD_PATH(enumDisplayDataPath);
#endif
            break;
#endif // End of #if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)


#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:

#if(_D2_TMDS_SUPPORT == _ON)
            SET_TMDS_RX2_FORCE_BCKGRD_PATH(enumDisplayDataPath);
#endif
            break;
#endif // End of #if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)


#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        case _D3_INPUT_PORT:

#if(_D3_TMDS_SUPPORT == _ON)
            SET_TMDS_RX3_FORCE_BCKGRD_PATH(enumDisplayDataPath);
#endif

            break;
#endif // End of #if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)


#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        case _D4_INPUT_PORT:

#if(_D4_TMDS_SUPPORT == _ON)
            SET_TMDS_RX4_FORCE_BCKGRD_PATH(enumDisplayDataPath);
#endif

            break;
#endif // End of #if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)


#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
        case _D5_INPUT_PORT:

#if(_D5_TMDS_SUPPORT == _ON)
            SET_TMDS_RX5_FORCE_BCKGRD_PATH(enumDisplayDataPath);
#endif
            break;
#endif // End of #if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)


#if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)
        case _D6_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
            SET_DP_RX0_FORCE_BCKGRD_PATH(enumDisplayDataPath);
#endif
            break;
#endif // End of #if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)


#if(_D7_INPUT_PORT_TYPE != _D7_NO_PORT)
        case _D7_INPUT_PORT:

#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
            switch(GET_D7_SWITCH_SELECT())
            {
                case _D0_INPUT_PORT:
                    SET_DP_RX0_FORCE_BCKGRD_PATH(enumDisplayDataPath);
                    break;
                case _D1_INPUT_PORT:
                    SET_DP_RX1_FORCE_BCKGRD_PATH(enumDisplayDataPath);
                    break;
                default:
                case _D7_INPUT_PORT:
                    SET_DP_RX0_FORCE_BCKGRD_PATH(enumDisplayDataPath);
                    SET_DP_RX1_FORCE_BCKGRD_PATH(enumDisplayDataPath);
                    break;
            }
#endif

            break;
#endif // End of #if(_D7_INPUT_PORT_TYPE != _D7_NO_PORT)


        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Remove Input Port Mapping
// Input Value  : enumSourceSearchPort --> Input Port
//                enumDisplayDataPath --> display data path
// Output Value : None
//--------------------------------------------------
void ScalerGlobalRemovePortMapping(EnumSourceSearchPort enumSourceSearchPort, EnumDisplayDataPath enumDisplayDataPath)
{
    enumDisplayDataPath = enumDisplayDataPath;

    DebugMessageSystem("Remove: port mapping", (((WORD)enumSourceSearchPort << 8) | enumDisplayDataPath));

    // Update source-data path mapping
    switch(enumSourceSearchPort)
    {
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
        case _A0_INPUT_PORT:

            break;
#endif


#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:

#if(_D0_TMDS_SUPPORT == _ON)
            CLR_TMDS_RX0_FORCE_BCKGRD_PATH(enumDisplayDataPath);
#endif

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            CLR_DP_RX0_FORCE_BCKGRD_PATH(enumDisplayDataPath);
#endif
            break;
#endif // End of #if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)


#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:

#if(_D1_TMDS_SUPPORT == _ON)
            CLR_TMDS_RX1_FORCE_BCKGRD_PATH(enumDisplayDataPath);
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            CLR_DP_RX1_FORCE_BCKGRD_PATH(enumDisplayDataPath);
#endif
            break;
#endif // End of #if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)


#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:

#if(_D2_TMDS_SUPPORT == _ON)
            CLR_TMDS_RX2_FORCE_BCKGRD_PATH(enumDisplayDataPath);
#endif
            break;
#endif // End of #if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)


#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        case _D3_INPUT_PORT:

#if(_D3_TMDS_SUPPORT == _ON)
            CLR_TMDS_RX3_FORCE_BCKGRD_PATH(enumDisplayDataPath);
#endif

            break;
#endif // End of #if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)


#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        case _D4_INPUT_PORT:

#if(_D4_TMDS_SUPPORT == _ON)
            CLR_TMDS_RX4_FORCE_BCKGRD_PATH(enumDisplayDataPath);
#endif

            break;
#endif // End of #if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)


#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
        case _D5_INPUT_PORT:

#if(_D5_TMDS_SUPPORT == _ON)
            CLR_TMDS_RX5_FORCE_BCKGRD_PATH(enumDisplayDataPath);
#endif
            break;
#endif // End of #if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)


#if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)
        case _D6_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
            CLR_DP_RX0_FORCE_BCKGRD_PATH(enumDisplayDataPath);
#endif
            break;
#endif // End of #if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)


#if(_D7_INPUT_PORT_TYPE != _D7_NO_PORT)
        case _D7_INPUT_PORT:

#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
            CLR_DP_RX0_FORCE_BCKGRD_PATH(enumDisplayDataPath);
            CLR_DP_RX1_FORCE_BCKGRD_PATH(enumDisplayDataPath);
#endif

            break;
#endif // End of #if(_D7_INPUT_PORT_TYPE != _D7_NO_PORT)


        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Reset port mapping
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGlobalResetPortMapping(void)
{
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
#if(_D0_TMDS_SUPPORT == _ON)
    CLR_TMDS_RX0_FORCE_BCKGRD_PATH(_DISPLAY_PATH_ALL);
#endif

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    CLR_DP_RX0_FORCE_BCKGRD_PATH(_DISPLAY_PATH_ALL);
#endif
#endif // End of #if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)


#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
#if(_D1_TMDS_SUPPORT == _ON)
    CLR_TMDS_RX1_FORCE_BCKGRD_PATH(_DISPLAY_PATH_ALL);
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    CLR_DP_RX1_FORCE_BCKGRD_PATH(_DISPLAY_PATH_ALL);
#endif
#endif // End of #if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)


#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
#if(_D2_TMDS_SUPPORT == _ON)
    CLR_TMDS_RX2_FORCE_BCKGRD_PATH(_DISPLAY_PATH_ALL);
#endif
#endif // End of #if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)


#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
#if(_D3_TMDS_SUPPORT == _ON)
    CLR_TMDS_RX3_FORCE_BCKGRD_PATH(_DISPLAY_PATH_ALL);
#endif
#endif // End of #if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)


#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
#if(_D4_TMDS_SUPPORT == _ON)
    CLR_TMDS_RX4_FORCE_BCKGRD_PATH(_DISPLAY_PATH_ALL);
#endif
#endif // End of #if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)


#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
#if(_D5_TMDS_SUPPORT == _ON)
    CLR_TMDS_RX5_FORCE_BCKGRD_PATH(_DISPLAY_PATH_ALL);
#endif
#endif // End of #if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)


#if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
    CLR_DP_RX0_FORCE_BCKGRD_PATH(_DISPLAY_PATH_ALL);
#endif
#endif // End of #if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)


#if(_D7_INPUT_PORT_TYPE != _D7_NO_PORT)
#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
    CLR_DP_RX0_FORCE_BCKGRD_PATH(_DISPLAY_PATH_ALL);
    CLR_DP_RX1_FORCE_BCKGRD_PATH(_DISPLAY_PATH_ALL);
#endif
#endif // End of #if(_D7_INPUT_PORT_TYPE != _D7_NO_PORT)
}

//--------------------------------------------------
// Description  : Scaler Whole Chip Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGlobalWholeChipReset(void)
{
    // Whole chip reset
    ScalerSetBit(P0_01_HOST_CTRL, ~_BIT0, _BIT0);

    // For Delay 10 ms
    ScalerTimerDelayXms(10);

    // Clear to 0
    ScalerSetBit(P0_01_HOST_CTRL, ~_BIT0, 0x00);
}

//--------------------------------------------------
// Description  : Set WD mapping between I/D domains
// Input Value  : display mode
// Output Value : None
//--------------------------------------------------
void ScalerGlobalSetWatchDogMapping(EnumDisplayMode enumDisplayMode)
{
    switch(enumDisplayMode)
    {
        case _DISPLAY_MODE_1P:

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
            // Map M1/M2/S1/S2 to M1
            ScalerSetByte(P0_0E_I_D_MAPPING, 0x00);
#else
            ScalerSetByte(P0_0E_I_D_MAPPING, 0x0B);
#endif
            break;

#if((_PIP_DISPLAY_SUPPORT == _ON) || (_PBP_LR_DISPLAY_SUPPORT == _ON))

#if(_PIP_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_PIP:
#endif

#if(_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_PBP_LR:
#endif

            // Set I-S1 to D-S1, I-S2 to D-S2 to prevent field signal error in display sub
            ScalerSetByte(P0_0E_I_D_MAPPING, 0x0B);
            break;

#endif // End of #if((_PIP_DISPLAY_SUPPORT == _ON) ||(_PBP_LR_DISPLAY_SUPPORT == _ON))

#if(_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_PBP_TB:

            ScalerSetByte(P0_0E_I_D_MAPPING, 0x07);
            break;
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_4P:

            ScalerSetByte(P0_0E_I_D_MAPPING, 0x1B);
            break;
#endif

        default:

            ScalerSetByte(P0_0E_I_D_MAPPING, 0x0B);
            break;
    }
}

//--------------------------------------------------
// Description  : Enabel Global Watch Dog by Region
// Input Value  : enumDisplayRegion --> system select region
//                bEnable -->_ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerGlobalWatchDog(EnumDisplayRegion enumDisplayRegion, bit bEnable)
{
    ScalerGlobalPathWatchDog(ScalerRegionGetInputDataPath(enumDisplayRegion), bEnable);
}

//--------------------------------------------------
// Description  : Select internal oscillator Clock.
// Input Value  : IOSC/ Xtal
// Output Value : None
//--------------------------------------------------
void ScalerGlobalCrystalClkSel(EnumClkSel enumSel)
{
    if(enumSel == _IOSC_CLK)
    {
        // Select at internal Xtal.
        ScalerSetBit(P0_09_GA_POWER_CTRL, ~_BIT3, _BIT3);
    }
    else if(enumSel == _EXT_XTAL_CLK)
    {
        // Select at external Xtal.
        ScalerSetBit(P0_09_GA_POWER_CTRL, ~_BIT3, 0x00);
    }
}

//--------------------------------------------------
// Description  : Initialize OSD Position Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGlobalOsdInitial(void)
{
    ScalerOsdVerticalStartSelect(_OSD_VSYNC_SELECT_DVS);
    ScalerOsdGlobalDoubleBuffer(_DISABLE);

    // Set OSD position global offset
    ScalerOsdPositionOffset(_OSD_POSITION_OFFSET_GLOBAL,
                            (ScalerOsdGetDoubleFunctionH() == _ENABLE) ? X_POS(_OSD_DOUBLE_POSITION_OFFSET_H) : X_POS(_OSD_POSITION_OFFSET_H),
                            (ScalerOsdGetDoubleFunctionV() == _ENABLE) ? Y_POS(_OSD_DOUBLE_POSITION_OFFSET_V) : Y_POS(_OSD_POSITION_OFFSET_V));

#if(_OSD_POSITION_OFFSET_CORRECTION == _ON)
    // window & font alignment
    ScalerOsdFontWindowVericalAlignemnt(_ENABLE);
    ScalerOsdPositionOffset(_OSD_POSITION_OFFSET_WINDOW, X_POS(_OSD_OFFSET_DRAW_WINDOW_H), Y_POS(_OSD_OFFSET_DRAW_WINDOW_V));

#else

#if(_OSD_POSITION_SELF_ALIGNMENT == _ON)
    ScalerOsdFontWindowVericalAlignemnt(_ENABLE);
    ScalerOsdPositionOffset(_OSD_POSITION_OFFSET_WINDOW, X_POS(_OSD_OFFSET_DRAW_WINDOW_H), Y_POS(_OSD_OFFSET_DRAW_WINDOW_V));
#else
    ScalerOsdFontWindowVericalAlignemnt(_DISABLE);
    ScalerOsdPositionOffset(_OSD_POSITION_OFFSET_WINDOW, X_POS(0), Y_POS(0));
#endif // End of #if(_OSD_POSITION_SELF_ALIGNMENT == _OFF)

#endif // End of #if(_OSD_POSITION_OFFSET_CORRECTION == _OFF)

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
    // Enable OSD shift mode; Set inside/outside shift & boundary value
    ScalerOsdFBShiftValue(_OSD_FRONT_BACK_SHIFT_OUTSIDE, 0x00);
    ScalerOsdFBShiftValue(_OSD_FRONT_BACK_SHIFT_INSIDE, 0x00);
    ScalerOsdFBShiftBoundarySize(0x00, 0x00);
    ScalerOsdFBShiftEn(_ENABLE);
#endif
}

//--------------------------------------------------
// Description  : Global Reset Event
// Input Value  : ucResetTarget --> Reset target action
// Output Value : None
//--------------------------------------------------
void ScalerGlobalResetProc(BYTE ucResetTarget)
{
    switch(ucResetTarget)
    {
        case _MODE_ACTION_RESET_TO_DISPLAY_INITIAL:

            // Set Background Color to Black
            ScalerDDomainBackgroundSetColor(_DISPLAY_PATH_ALL, 0, 0, 0);
            ScalerDDomainBackgroundEnable(_DISPLAY_PATH_ALL, _ENABLE);

            // Disable WD
            ScalerGlobalPathWatchDog(_INPUT_PATH_ALL, _DISABLE);

            // Reset port mapping data path
            ScalerGlobalResetPortMapping();

#if(_VGA_SUPPORT == _ON)
            // Disable Vga Top Double Buffer
            ScalerVgaTopDoubleBufferEnable(_DISABLE);
#endif

            ScalerGlobalDoubleBufferEnable(_DISABLE);

            // Reset I-domain
            ScalerIDomainResetDataPath(_INPUT_PATH_ALL);

#if(_OD_SUPPORT == _ON)
            // Disable OD function
            ScalerODEnable(_FUNCTION_OFF);
#endif

            break;

        case _MODE_ACTION_RESET_TO_DISPLAY_SETTING:

            // Set Background Color to Black
            ScalerTimerWaitForIDDomainEvent(_EVENT_DEN_STOP, _DISPLAY_PATH_M1);
            ScalerDDomainBackgroundSetColor(GET_MDOMAIN_OUTPUT_DATA_PATH(), 0, 0, 0);
            ScalerDDomainBackgroundEnable(GET_MDOMAIN_OUTPUT_DATA_PATH(), _ENABLE);

            ScalerGlobalPathWatchDog(GET_MDOMAIN_INPUT_DATA_PATH(), _DISABLE);

#if((_FRC_SUPPORT == _ON) && (_OD_SUPPORT == _ON))
            // Release FRC bandwidth
            ScalerMDomainReleaseFRCMemoryBW(GET_MDOMAIN_INPUT_DATA_PATH());
#endif

            break;

        case _MODE_ACTION_RESET_TO_DISPLAY_SETTING_WITHOUT_FORCETOBG:
            ScalerGlobalPathWatchDog(GET_MDOMAIN_INPUT_DATA_PATH(), _DISABLE);

#if((_FRC_SUPPORT == _ON) && (_OD_SUPPORT == _ON))
            // Release FRC bandwidth
            ScalerMDomainReleaseFRCMemoryBW(GET_MDOMAIN_INPUT_DATA_PATH());
#endif

            break;

        case _MODE_ACTION_RESET_TO_POWER_SAVING:
        case _MODE_ACTION_RESET_TO_POWER_OFF:

            // Disable WD
            ScalerGlobalPathWatchDog(_INPUT_PATH_ALL, _DISABLE);

            // Reset all interface block WD/Irq/Timer Event....
            ScalerSyncResetAllProc();

            // Reset timing info
            ScalerMeasureResetTimingInfo(_INPUT_PATH_ALL);

#if(_OD_SUPPORT == _ON)
            // Disable OD function
            ScalerODEnable(_FUNCTION_OFF);
#endif

            break;

        default:

            break;
    }

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    ScalerRotationSetEnable(_DISABLE);
#endif
}

//--------------------------------------------------
// Description  : Process Required when Switched to Active State
// Input Value  : Input Source
// Output Value : None
//--------------------------------------------------
void ScalerGlobalFirstActiveProc(BYTE ucSourceType, BYTE ucGetInputPort)
{
    // Add port mapping to display data path
    ScalerGlobalAddPortMapping(ucGetInputPort, GET_MDOMAIN_OUTPUT_DATA_PATH());

    // Enable Watch Dog
    ScalerGlobalPathWatchDog(GET_MDOMAIN_INPUT_DATA_PATH(), _ENABLE);

    switch(ucSourceType)
    {
#if(_VGA_SUPPORT == _ON)
        case _SOURCE_VGA:

            // Enable Vga Top Double Buffer
            ScalerVgaTopDoubleBufferEnable(_ENABLE);

            break;
#endif

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
        case _SOURCE_DVI:
        case _SOURCE_HDMI:

            switch(ucGetInputPort)
            {
#if(_D0_TMDS_SUPPORT == _ON)
                case _D0_INPUT_PORT:
                    ScalerTMDSRx0FirstActiveProc(ucSourceType);
                    break;
#endif


#if(_D1_TMDS_SUPPORT == _ON)
                case _D1_INPUT_PORT:
                    ScalerTMDSRx1FirstActiveProc(ucSourceType);
                    break;
#endif

#if(_D2_TMDS_SUPPORT == _ON)
                case _D2_INPUT_PORT:
                    ScalerTMDSRx2FirstActiveProc(ucSourceType);
                    break;
#endif

#if(_D3_TMDS_SUPPORT == _ON)
                case _D3_INPUT_PORT:
                    ScalerTMDSRx3FirstActiveProc(ucSourceType);
                    break;
#endif

#if(_D4_TMDS_SUPPORT == _ON)
                case _D4_INPUT_PORT:
                    ScalerTMDSRx4FirstActiveProc(ucSourceType);
                    break;
#endif

#if(_D5_TMDS_SUPPORT == _ON)
                case _D5_INPUT_PORT:
                    ScalerTMDSRx5FirstActiveProc(ucSourceType);
                    break;
#endif

                default:
                    break;
            }

            break;
#endif

#if(_DP_SUPPORT == _ON)
        case _SOURCE_DP:

            switch(ucGetInputPort)
            {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

                case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                case _D6_INPUT_PORT:
#endif
                    // Enable DP Fifo Under/OverFlow Watch Dog
                    ScalerDpRx0SetFifoWD(_ENABLE);

                    // Enable DP overflow/ underflow IRQ
                    ScalerDpRx0SetFifoIRQ(_ENABLE);

                    break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
                case _D1_INPUT_PORT:

                    // Enable DP Fifo Under/OverFlow Watch Dog
                    ScalerDpRx1SetFifoWD(_ENABLE);

                    // Enable DP overflow/ underflow IRQ
                    ScalerDpRx1SetFifoIRQ(_ENABLE);

                    break;
#endif


#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
                case _D7_INPUT_PORT:

                    switch(GET_D7_SWITCH_SELECT())
                    {
                        case _D0_INPUT_PORT:
                            // Enable DP Fifo Under/OverFlow Watch Dog
                            ScalerDpRx0SetFifoWD(_ENABLE);

                            // Enable DP overflow/ underflow IRQ
                            ScalerDpRx0SetFifoIRQ(_ENABLE);
                            break;

                        case _D1_INPUT_PORT:
                            // Enable DP Fifo Under/OverFlow Watch Dog
                            ScalerDpRx1SetFifoWD(_ENABLE);

                            // Enable DP overflow/ underflow IRQ
                            ScalerDpRx1SetFifoIRQ(_ENABLE);
                            break;

                        case _D7_INPUT_PORT:
                            // Enable DP Fifo Under/OverFlow Watch Dog
                            ScalerDpRx0SetFifoWD(_ENABLE);

                            // Enable DP overflow/ underflow IRQ
                            ScalerDpRx0SetFifoIRQ(_ENABLE);

                            // Enable DP Fifo Under/OverFlow Watch Dog
                            ScalerDpRx1SetFifoWD(_ENABLE);

                            // Enable DP overflow/ underflow IRQ
                            ScalerDpRx1SetFifoIRQ(_ENABLE);
                            break;

                        default:
                            break;
                    }

                    break;
#endif

                default:
                    break;
            }

            break;
#endif

        default:
            break;
    }
}



//--------------------------------------------------
// Description  : Set I domain double buffer trigger event
// Input Value  : DB path select, DB I domain trigger event
// Output Value : None
//--------------------------------------------------
void ScalerGlobalIDDomainDBSetTriggerEvent(EnumInputDataPath enumSelectedDataPath, EnumDBIDomainTriggerEvent enumTriggerEvent)
{
    BYTE ucDBTriggerEventCtrl = 0;
    BYTE ucCtrlBits = 0;
    BYTE ucTriggerEvent = ((enumTriggerEvent == _DB_TRIGGER_EVENT_IEN_STOP) ? 1 : 0);

    if((enumSelectedDataPath & _INPUT_PATH_M1) == _INPUT_PATH_M1)
    {
        ucDBTriggerEventCtrl |= (ucTriggerEvent << 3);
        ucCtrlBits |= (_BIT3 | _BIT7);
        if(GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_4P)
        {
            ucDBTriggerEventCtrl &= (~_BIT7);
        }
        else
        {
            if(enumTriggerEvent == _DB_TRIGGER_EVENT_IVS)
            {
                ucDBTriggerEventCtrl &= (~_BIT7);
            }
            else
            {
                ucDBTriggerEventCtrl |= _BIT7;
            }
        }
    }

    if((enumSelectedDataPath & _INPUT_PATH_M2) == _INPUT_PATH_M2)
    {
        ucDBTriggerEventCtrl |= (ucTriggerEvent << 2);
        ucCtrlBits |= (_BIT2 | _BIT6);
        if(GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_4P)
        {
            ucDBTriggerEventCtrl |= _BIT6;
        }
        else
        {
            if(enumTriggerEvent == _DB_TRIGGER_EVENT_IVS)
            {
                ucDBTriggerEventCtrl &= (~_BIT6);
            }
            else
            {
                ucDBTriggerEventCtrl |= _BIT6;
            }
        }
    }

    if((enumSelectedDataPath & _INPUT_PATH_S1) == _INPUT_PATH_S1)
    {
        ucDBTriggerEventCtrl |= (ucTriggerEvent << 1);
        ucCtrlBits |= (_BIT1 | _BIT5);
        if(GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_4P)
        {
            ucDBTriggerEventCtrl &= (~_BIT5);
        }
        else
        {
            if(enumTriggerEvent == _DB_TRIGGER_EVENT_IVS)
            {
                ucDBTriggerEventCtrl &= (~_BIT5);
            }
            else
            {
                ucDBTriggerEventCtrl |= _BIT5;
            }
        }
    }

    if((enumSelectedDataPath & _INPUT_PATH_S2) == _INPUT_PATH_S2)
    {
        ucDBTriggerEventCtrl |= ucTriggerEvent;
        ucCtrlBits |= (_BIT0 | _BIT4);
        if(GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_4P)
        {
            ucDBTriggerEventCtrl |= _BIT4;
        }
        else
        {
            if(enumTriggerEvent == _DB_TRIGGER_EVENT_IVS)
            {
                ucDBTriggerEventCtrl &= (~_BIT4);
            }
            else
            {
                ucDBTriggerEventCtrl |= _BIT4;
            }
        }
    }

    ScalerSetBit(P31_A1_I_DB_CTRL1, ~ucCtrlBits, ucDBTriggerEventCtrl);

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
    if(enumTriggerEvent == _DB_TRIGGER_EVENT_IVS)
    {
        // I_main_sub_sync select sub reference main: M1 IVS in 4 path mode
        ScalerSetBit(P31_A2_I_DB_CTRL2, ~(_BIT2 | _BIT1), _BIT2);
    }
    else if(enumTriggerEvent == _DB_TRIGGER_EVENT_IEN_STOP)
    {
        // I_main_sub_sync select main reference sub: S2 IEN stop in 4 path mode
        ScalerSetBit(P31_A2_I_DB_CTRL2, ~(_BIT2 | _BIT1), _BIT1);
    }
#endif
}

//--------------------------------------------------
// Description  : Set DB Cap/Disp buffer start address
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGlobalIDDomainDBSetBufferAddress(StructDBDataPathGroup *pstDataPathGroupInfo)
{
    DWORD ulStartAddrBlk1 = 0x00000000;
    DWORD ulStartAddrBlk2 = 0x00000000;
    WORD usSelectedPage = 0x0000;
    BYTE ucGroupIndex = 0x00;
    BYTE ucDataPathIndex = 0x00;
    BYTE ucPathCount = 0x00;
#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    DWORD ulDispLineStep = 0x00;
    bit bSizeOverRange = _FALSE;
#endif

    for(ucGroupIndex = 0; ucGroupIndex < (pstDataPathGroupInfo->ucGroupNum); ucGroupIndex++)
    {
#if(_FORMAT_CONVERSION_SUPPORT == _ON)
        ulDispLineStep = 0;
        bSizeOverRange = _FALSE;
#endif

        switch(pstDataPathGroupInfo->penumGroup[ucGroupIndex])
        {
            case _INPUT_PATH_M1:
                usSelectedPage = _REG_MAIN1_PAGE;
                ucPathCount = 1;
                break;

            case _INPUT_PATH_M2:
                usSelectedPage = _REG_MAIN2_PAGE;
                ucPathCount = 1;
                break;

            case _INPUT_PATH_S1:
                usSelectedPage = _REG_SUB1_PAGE;
                ucPathCount = 1;
                break;

            case _INPUT_PATH_S2:
                usSelectedPage = _REG_SUB2_PAGE;
                ucPathCount = 1;
                break;

            case _INPUT_PATH_M1_M2:
                usSelectedPage = _REG_MAIN1_PAGE;
                ucPathCount = 2;
                break;

            case _INPUT_PATH_S1_S2:
                usSelectedPage = _REG_SUB1_PAGE;
                ucPathCount = 2;
                break;

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
            case _INPUT_PATH_ALL:
                usSelectedPage = _REG_MAIN1_PAGE;
                ucPathCount = 4;
                break;
#endif

            default:
                usSelectedPage = _REG_MAIN1_PAGE;
                ucPathCount = 0;
        }

        for(ucDataPathIndex = 0; ucDataPathIndex < ucPathCount; ucDataPathIndex++)
        {
            // Fetch current start address of block 1 & block 2
            ulStartAddrBlk1 = ((DWORD)ScalerGetBit(P5_00_CAP_M1_MEM_ADDR_MSB + usSelectedPage, 0x0F) << 24) |
                              ((DWORD)ScalerGetByte(P5_01_CAP_M1_MEM_ADDR_H + usSelectedPage) << 16) |
                              ((DWORD)ScalerGetByte(P5_02_CAP_M1_MEM_ADDR_M + usSelectedPage) << 8) |
                              ((DWORD)ScalerGetByte(P5_03_CAP_M1_MEM_ADDR_L + usSelectedPage));

            ulStartAddrBlk2 = ((DWORD)ScalerGetBit(P5_04_CAP_M1_BL2_ADDR_MSB + usSelectedPage, 0x0F) << 24) |
                              ((DWORD)ScalerGetByte(P5_05_CAP_M1_BL2_ADDR_H + usSelectedPage) << 16) |
                              ((DWORD)ScalerGetByte(P5_06_CAP_M1_BL2_ADDR_M + usSelectedPage) << 8) |
                              ((DWORD)ScalerGetByte(P5_07_CAP_M1_BL2_ADDR_L + usSelectedPage));

            // Toggle block start address
            if(ulStartAddrBlk1 < _DB_FRAME_BUF_BLK_ADDR_OFFSET)
            {
                ulStartAddrBlk1 += _DB_FRAME_BUF_BLK_ADDR_OFFSET;
                ulStartAddrBlk2 += _DB_FRAME_BUF_BLK_ADDR_OFFSET;
            }
            else
            {
                ulStartAddrBlk1 -= _DB_FRAME_BUF_BLK_ADDR_OFFSET;
                ulStartAddrBlk2 -= _DB_FRAME_BUF_BLK_ADDR_OFFSET;
            }

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
            if((ScalerFmtCnvFtoPGetStatus(pstDataPathGroupInfo->penumGroup[ucGroupIndex]) == _FALSE) &&
               (usSelectedPage == _REG_MAIN2_PAGE) &&
               (GET_MDOMAIN_DISPLAY_MODE() != _DISPLAY_MODE_4P))
            {
                ScalerGetDataPortByte(P0_30_FIFO_WINDOW_ADDR_PORT, _P0_31_PT_04_DISPLAY_READ_WID_BSU_H_M2, 4, &pData[0], _AUTOINC);
                // FIFO H Width
                PDATA_WORD(2) = ((((WORD)pData[3] & 0x10) << 8) | (((WORD)pData[0] & 0xF0) << 4) | pData[1]);
                // FIFO V Height
                PDATA_WORD(3) = ((((WORD)pData[3] & 0x01) << 12) | (((WORD)pData[0] & 0x0F) << 8) | pData[2]);
                // Get Data Bit
                pData[8] = (ScalerGetBit(P45_AE_DISP_M2_DISP_CTRL2, _BIT7) == _BIT7) ? (_COLOR_DEPTH_10_BITS * 3) : (_COLOR_DEPTH_8_BITS * 3);

                // Calculate Data Size (unit: row)
                PDATA_DWORD(0) = (((DWORD)PDATA_WORD(2) * PDATA_WORD(3) * pData[8]) / _MEMORY_BIT_NUM / _MEMORY_BANK / _MEMORY_COL_PER_BANK);
#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_2PCS)
                PDATA_DWORD(0) = (PDATA_DWORD(0) << 12);
#else
                PDATA_DWORD(0) = (PDATA_DWORD(0) << 11);
#endif

                if(PDATA_DWORD(0) > (_FRC_CAP_M1_2ND_BLOCK_STA_ADDR - _FRC_CAP_M1_1ST_BLOCK_STA_ADDR))
                {
                    bSizeOverRange = _TRUE;
                }
            }
#endif

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
            if(bSizeOverRange == _FALSE)
#endif
            {
#if(_FORMAT_CONVERSION_SUPPORT == _ON)
                if((ScalerFmtCnvFtoPGetStatus(pstDataPathGroupInfo->penumGroup[ucGroupIndex]) == _FALSE) &&
                   (GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_PBP_TB) && (usSelectedPage == _REG_SUB2_PAGE))

                {
                }
                else
#endif
                {
                    // Set capture block 1 address
                    PDATA_DWORD(0) = ulStartAddrBlk1;
                    ScalerSetBit(P5_00_CAP_M1_MEM_ADDR_MSB + usSelectedPage, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[0] & 0x0F));
                    ScalerSetByte(P5_01_CAP_M1_MEM_ADDR_H + usSelectedPage, (pData[1] & 0xFF));
                    ScalerSetByte(P5_02_CAP_M1_MEM_ADDR_M + usSelectedPage, (pData[2] & 0xFF));
                    ScalerSetByte(P5_03_CAP_M1_MEM_ADDR_L + usSelectedPage, (pData[3] & 0xFF));

                    // Set capture block 2 address
                    PDATA_DWORD(1) = ulStartAddrBlk2;
                    ScalerSetBit(P5_04_CAP_M1_BL2_ADDR_MSB + usSelectedPage, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[4] & 0x0F));
                    ScalerSetByte(P5_05_CAP_M1_BL2_ADDR_H + usSelectedPage, (pData[5] & 0xFF));
                    ScalerSetByte(P5_06_CAP_M1_BL2_ADDR_M + usSelectedPage, (pData[6] & 0xFF));
                    ScalerSetByte(P5_07_CAP_M1_BL2_ADDR_L + usSelectedPage, (pData[7] & 0xFF));
                }
            }

#if(_D_DOMAIN_PATH != _D_DOMAIN_4_PATH)
            // If runs in PIP and PBP_LR mode, S2 display block address is left unchanged
            if((usSelectedPage == _REG_SUB2_PAGE) &&
               ((GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_PIP) || (GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_PBP_LR)))
            {
                continue;
            }
#endif

            // Set display block 1 address
#if(_FORMAT_CONVERSION_SUPPORT == _ON)
            if((ScalerFmtCnvFtoPGetStatus(pstDataPathGroupInfo->penumGroup[ucGroupIndex]) == _FALSE) &&
               (GET_MDOMAIN_DISPLAY_MODE() != _DISPLAY_MODE_4P))
            {
                if(usSelectedPage == _REG_MAIN2_PAGE)
                {
                    // Get Display M1 line step
                    ulDispLineStep = ((DWORD)ScalerGetBit(P5_99_DISP_M1_LINE_STEP_MSB, 0x0F) << 24) |
                                     ((DWORD)ScalerGetByte(P5_9A_DISP_M1_LINE_STEP_H) << 16) |
                                     ((DWORD)ScalerGetByte(P5_9B_DISP_M1_LINE_STEP_M) << 8) |
                                     ((DWORD)ScalerGetByte(P5_9C_DISP_M1_LINE_STEP_L));
                    ulDispLineStep = ulDispLineStep >> 1;

                    PDATA_DWORD(0) = ((DWORD)ScalerGetBit(P5_00_CAP_M1_MEM_ADDR_MSB, 0x0F) << 24) |
                                     ((DWORD)ScalerGetByte(P5_01_CAP_M1_MEM_ADDR_H) << 16) |
                                     ((DWORD)ScalerGetByte(P5_02_CAP_M1_MEM_ADDR_M) << 8) |
                                     ((DWORD)ScalerGetByte(P5_03_CAP_M1_MEM_ADDR_L));
                    PDATA_DWORD(1) = ((DWORD)ScalerGetBit(P5_04_CAP_M1_BL2_ADDR_MSB, 0x0F) << 24) |
                                     ((DWORD)ScalerGetByte(P5_05_CAP_M1_BL2_ADDR_H) << 16) |
                                     ((DWORD)ScalerGetByte(P5_06_CAP_M1_BL2_ADDR_M) << 8) |
                                     ((DWORD)ScalerGetByte(P5_07_CAP_M1_BL2_ADDR_L));
                }
                else if(usSelectedPage == _REG_SUB2_PAGE)
                {
                    ulDispLineStep = ((DWORD)ScalerGetBit(P85_99_DISP_S1_LINE_STEP_MSB, 0x0F) << 24) |
                                     ((DWORD)ScalerGetByte(P85_9A_DISP_S1_LINE_STEP_H) << 16) |
                                     ((DWORD)ScalerGetByte(P85_9B_DISP_S1_LINE_STEP_M) << 8) |
                                     ((DWORD)ScalerGetByte(P85_9C_DISP_S1_LINE_STEP_L));
                    ulDispLineStep = ulDispLineStep >> 1;

                    PDATA_DWORD(0) = ((DWORD)ScalerGetBit(P85_00_CAP_S1_MEM_ADDR_MSB, 0x0F) << 24) |
                                     ((DWORD)ScalerGetByte(P85_01_CAP_S1_MEM_ADDR_H) << 16) |
                                     ((DWORD)ScalerGetByte(P85_02_CAP_S1_MEM_ADDR_M) << 8) |
                                     ((DWORD)ScalerGetByte(P85_03_CAP_S1_MEM_ADDR_L));
                    PDATA_DWORD(1) = ((DWORD)ScalerGetBit(P85_04_CAP_S1_BL2_ADDR_MSB, 0x0F) << 24) |
                                     ((DWORD)ScalerGetByte(P85_05_CAP_S1_BL2_ADDR_H) << 16) |
                                     ((DWORD)ScalerGetByte(P85_06_CAP_S1_BL2_ADDR_M) << 8) |
                                     ((DWORD)ScalerGetByte(P85_07_CAP_S1_BL2_ADDR_L));
                }
                PDATA_DWORD(0) = (PDATA_DWORD(0) + ulDispLineStep);
                PDATA_DWORD(1) = (PDATA_DWORD(1) + ulDispLineStep);
            }
#endif

            ScalerSetBit(P5_80_DISP_M1_READ_ADDR_MSB + usSelectedPage, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[0] & 0x0F));
            ScalerSetByte(P5_81_DISP_M1_READ_ADDR_H + usSelectedPage, (pData[1] & 0xFF));
            ScalerSetByte(P5_82_DISP_M1_READ_ADDR_M + usSelectedPage, (pData[2] & 0xFF));
            ScalerSetByte(P5_83_DISP_M1_READ_ADDR_L + usSelectedPage, (pData[3] & 0xFF));

            // Set display block 2 address
            ScalerSetBit(P5_84_DISP_M1_BL2_ADDR_MSB + usSelectedPage, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[4] & 0x0F));
            ScalerSetByte(P5_85_DISP_M1_BL2_ADDR_H + usSelectedPage, (pData[5] & 0xFF));
            ScalerSetByte(P5_86_DISP_M1_BL2_ADDR_M + usSelectedPage, (pData[6] & 0xFF));
            ScalerSetByte(P5_87_DISP_M1_BL2_ADDR_L + usSelectedPage, (pData[7] & 0xFF));

            usSelectedPage += _REG_PAGE_OFFSET;
        }
    }
}

//--------------------------------------------------
// Description  : Set D domain double buffer apply
// Input Value  : DB apply polling/ no polling/ none
// Output Value : None
//--------------------------------------------------
void ScalerGlobalDDomainDBApply(EnumDBApply enumDBApply)
{
    // Set D-domain DB trigger source & trigger event
    ScalerSetBit(P31_B0_D_DB_CTRL0, ~_BIT5, _BIT5);

    switch(enumDBApply)
    {
        case _DB_APPLY_NO_POLLING:

            // Set D apply bit
            ScalerSetBit(P31_B0_D_DB_CTRL0, ~(_BIT6), (_BIT6));

            break;

        case _DB_APPLY_POLLING:

            // Set D apply bit
            ScalerSetBit(P31_B0_D_DB_CTRL0, ~(_BIT6), (_BIT6));

            if(enumDBApply == _DB_APPLY_POLLING)
            {
                // Wait D double buffer
                ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P31_B0_D_DB_CTRL0, (_BIT6), 0);
            }

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Set I domain double buffer apply
//
// The actual I_DB-applied path will be determined
// by both selected path and display mode.
//
// * In 1P Mode:
//      I_DB apply on M1 & M2, regardless of selected path.
//
// * In PIP, PBP_LR and PBP_TB Mode:
//      I_DB apply on M1 & M2 as long as at least one of them is selected.
//      I_DB apply on S1 & S2 as long as at least one of them is selected.
//
// * In 4P Mode:
//      I_DB apply on each selected path.
//
// Input Value  : DB path select, DB apply polling/ no polling/ none
// Output Value : None
//--------------------------------------------------
void ScalerGlobalIDomainDBApply(EnumInputDataPath enumInputDataPath, EnumDBApply enumDBApply)
{
    BYTE ucDataPathIndex = 0x00;
    EnumInputDataPath enumDataPath = 0x00;
    BYTE ucDBctrl = 0x00;

    if(enumDBApply != _DB_APPLY_NONE)
    {
        switch(GET_MDOMAIN_DISPLAY_MODE())
        {
            case _DISPLAY_MODE_1P:
#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
                ucDBctrl |= (_BIT3 | _BIT2 | _BIT1 | _BIT0);
#else
                ucDBctrl |= (_BIT3 | _BIT2);
#endif
                break;

            case _DISPLAY_MODE_PIP:
            case _DISPLAY_MODE_PBP_LR:
            case _DISPLAY_MODE_PBP_TB:
                if((enumInputDataPath & _INPUT_PATH_M1_M2) != 0x00)
                {
                    ucDBctrl |= (_BIT3 | _BIT2);
                }

                if((enumInputDataPath & _INPUT_PATH_S1_S2) != 0x00)
                {
                    ucDBctrl |= (_BIT1 | _BIT0);
                }
                break;

            case _DISPLAY_MODE_4P:
                for(ucDataPathIndex = 0; ucDataPathIndex < 4; ucDataPathIndex++)
                {
                    enumDataPath = ((BYTE)_BIT0 << ucDataPathIndex);

                    if((enumInputDataPath & enumDataPath) == enumDataPath)
                    {
                        ucDBctrl |= ((BYTE)_BIT3 >> ucDataPathIndex);
                    }
                }
                break;

            default:
                break;
        }

        // Set I apply bit
        ScalerSetBit(P31_A0_I_DB_CTRL0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucDBctrl);

        if(enumDBApply == _DB_APPLY_POLLING)
        {
            // Wait I double buffer
            ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P31_A0_I_DB_CTRL0, ucDBctrl, 0);
        }
    }
}

//--------------------------------------------------
// Description  : Divide input data path into several groups
//                (e.g. (M1_M2, S1_S2) or (M2, M3, M4))
// Input Value  : DB path select, pointer to struct of group info
// Output Value : None
//--------------------------------------------------
void ScalerGlobalIDDomainDBGetDataPathGroup(EnumInputDataPath enumSelectedDataPath, StructDBDataPathGroup *pstDataPathGroupInfo)
{
#if(_4P_DISPLAY_SUPPORT == _ON)
    BYTE ucDataPathIndex = 0x00;
    EnumInputDataPath enumDataPath = 0x00;
#endif

    enumSelectedDataPath = enumSelectedDataPath;

    pstDataPathGroupInfo->ucGroupNum = 0;

    switch(GET_MDOMAIN_DISPLAY_MODE())
    {
        case _DISPLAY_MODE_1P:
#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
            pstDataPathGroupInfo->penumGroup[(pstDataPathGroupInfo->ucGroupNum)++] = _INPUT_PATH_ALL;
#else
            pstDataPathGroupInfo->penumGroup[(pstDataPathGroupInfo->ucGroupNum)++] = _INPUT_PATH_M1_M2;
#endif
            break;

#if(_2P_DISPLAY_SUPPORT == _ON)

#if(_PIP_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_PIP:
#endif

#if(_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_PBP_LR:
#endif

#if(_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_PBP_TB:
#endif

            if((enumSelectedDataPath & _INPUT_PATH_M1_M2) != 0x00)
            {
                pstDataPathGroupInfo->penumGroup[(pstDataPathGroupInfo->ucGroupNum)++] = _INPUT_PATH_M1_M2;
            }

            if((enumSelectedDataPath & _INPUT_PATH_S1_S2) != 0x00)
            {
                pstDataPathGroupInfo->penumGroup[(pstDataPathGroupInfo->ucGroupNum)++] = _INPUT_PATH_S1_S2;
            }
            break;

#endif // End of #if(_2P_DISPLAY_SUPPORT == _ON)

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_4P:
            for(ucDataPathIndex = 0; ucDataPathIndex < 4; ucDataPathIndex++)
            {
                enumDataPath = ((BYTE)_BIT0 << ucDataPathIndex);

                if((enumSelectedDataPath & enumDataPath) == enumDataPath)
                {
                    pstDataPathGroupInfo->penumGroup[(pstDataPathGroupInfo->ucGroupNum)++] = enumDataPath;
                }
            }
            break;
#endif

        default:
            break;
    }
}

#if((_OD_SUPPORT == _ON) && (_FRC_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Set IRQ
// Input Value  : En : Enable / Disable
// Output Value : None
//--------------------------------------------------
void ScalerGlobalSetInterrupt(EnumIRQ enumIRQType, BYTE ucEn)
{
    switch(enumIRQType)
    {
        case _IRQ_DEN:
            // Clear DEN start IRQ flag
            ScalerSetBit(P0_05_IRQ_CTRL1, ~(_BIT6 | _BIT4 | _BIT2), _BIT2);

            // Enable/Disable DEN start IRQ
            ScalerSetBit(P0_05_IRQ_CTRL1, ~(_BIT6 | _BIT4 | _BIT3 | _BIT2), (ucEn << 3));
            break;

        default:
            // For compiler warning
            ucEn = ucEn;
            break;
    }
}
#endif // End of #if(_OD_SUPPORT == _ON)

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
//--------------------------------------------------
// Description  : Reset extension size to default
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGlobalResetExtension(void)
{
    // Reset format conversion extension
    ScalerSetBit(P31_63_FB_MASK_CTRL, ~_BIT0, 0x00);
    ScalerSetByte(P31_64_FRONT_MASK_NUM, 0x00);
    ScalerSetByte(P31_65_BACK_MASK_NUM, 0x00);
    ScalerSetBit(P31_66_EXTENSION_NUM, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Reset SD extension
    ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_3A_SD_OUT_EXTENSION_M1, 0x00);
    ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_3A_SD_OUT_EXTENSION_M2, 0x00);
    ScalerSetDataPortByte(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_00_V_SD_INIT_S1, 0x00);
    ScalerSetDataPortByte(PC0_24_SD_ADDRESS_PORT_S2, _PC0_25_PT_00_V_SD_INIT_S2, 0x00);

    // Reset I-domain drop extension
    ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_60_DROP_EXTENSION_M1, 0x00);
    ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_60_DROP_EXTENSION_M2, 0x00);
    ScalerSetDataPortByte(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_60_DROP_EXTENSION_S1, 0x00);
    ScalerSetDataPortByte(PC0_24_SD_ADDRESS_PORT_S2, _PC0_25_PT_60_DROP_EXTENSION_S2, 0x00);

    // Reset FIFO extension
    ScalerSetDataPortByte(P0_30_FIFO_WINDOW_ADDR_PORT, _P0_31_PT_08_DISPLAY_READ_EXTENSION_MAIN, 0x00);
    ScalerSetDataPortByte(P80_30_FIFO_WINDOW_ADDR_PORT_S, _P80_31_PT_08_DISPLAY_READ_EXTENSION_SUB, 0x00);

    // Reset D-domain extension
    ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_1F_DISPLAY_EXTENSION_FB_MAIN, 0x00);
    ScalerSetDataPortByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_1F_DISPLAY_EXTENSION_FB_SUB, 0x00);

    // Reset D-domain extension extract
    ScalerSetBit(P35_30_EXTENSION_EXTRA_WIN, ~_BIT0, 0x00);

    // Reset display conversion extension
    ScalerSetByte(P39_1E_DSPC_TIMING_CTRL0, 0x00);
}
#endif

//--------------------------------------------------
// Description  : Get double buffer status
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerGlobalGetDBStatus(void)
{
    return (ScalerGlobalGetIDomainDBStatus() & ScalerGlobalGetDDomainDBStatus());
}

//--------------------------------------------------
// Description  : Get D-Domain double buffer status
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerGlobalGetDDomainDBStatus(void)
{
    return ((bit)ScalerGetBit(P31_B0_D_DB_CTRL0, _BIT7));
}

//--------------------------------------------------
// Description  : Get I-Domain double buffer status
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerGlobalGetIDomainDBStatus(void)
{
    return ((bit)ScalerGetBit(P31_A0_I_DB_CTRL0, _BIT7));
}

//--------------------------------------------------
// Description  : Clear I/D domain DB ready bit of selected path
// Input Value  : DB path selection
// Output Value : None
//--------------------------------------------------
void ScalerGlobalIDDomainDBClearReadyBit(EnumInputDataPath enumSelectedDataPath)
{
    BYTE ucIDomainDBCtrl = 0x00;

    ucIDomainDBCtrl |= (((enumSelectedDataPath & _INPUT_PATH_M1) == _INPUT_PATH_M1) ? _BIT3 : 0x00);
    ucIDomainDBCtrl |= (((enumSelectedDataPath & _INPUT_PATH_M2) == _INPUT_PATH_M2) ? _BIT2 : 0x00);
    ucIDomainDBCtrl |= (((enumSelectedDataPath & _INPUT_PATH_S1) == _INPUT_PATH_S1) ? _BIT1 : 0x00);
    ucIDomainDBCtrl |= (((enumSelectedDataPath & _INPUT_PATH_S2) == _INPUT_PATH_S2) ? _BIT0 : 0x00);

    // Wait for finish of I-domain DB
    if(ScalerGetBit(P31_A0_I_DB_CTRL0, ucIDomainDBCtrl) != 0x00)
    {
        ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P31_A0_I_DB_CTRL0, ucIDomainDBCtrl, 0);
    }

    // Wait for finish of D-domain DB
    if(ScalerGetBit(P31_B0_D_DB_CTRL0, _BIT6) != 0x00)
    {
        ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P31_B0_D_DB_CTRL0, _BIT6, 0);
    }

    // Clear I-domain DB ready bit after timeout
    ScalerSetBit(P31_A0_I_DB_CTRL0, ~ucIDomainDBCtrl, 0x00);

    // Clear D-domain DB ready bit after timeout
    ScalerSetBit(P31_B0_D_DB_CTRL0, ~_BIT6, 0x00);
}

#if(_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_BACKLIGHT)
//--------------------------------------------------
// Description  : Check if IHV error, turn off backlight
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGlobalPreventGarbageByBacklight_EXINT0(void) using 1
{
    if((ScalerGetBit_EXINT(P0_02_STATUS0, (_BIT6 | _BIT5)) != 0x00) && (ScalerGetBit_EXINT(P0_04_IRQ_CTRL0, _BIT5) == _BIT5))
    {
        PCB_BACKLIGHT_POWER_PIN(_LIGHT_CONTROL_OFF);

        // Set force to background and free run mode
        ScalerSetBit_EXINT(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~(_BIT5 | _BIT3), _BIT5);

        // Disable Input HVsync error IRQ
        ScalerSetBit_EXINT(P0_04_IRQ_CTRL0, ~_BIT5, 0x00);
    }
}
#endif
