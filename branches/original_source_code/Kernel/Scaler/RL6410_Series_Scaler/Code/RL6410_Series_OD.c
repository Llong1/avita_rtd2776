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
// ID Code      : RL6410_Series_OD.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6410_SERIES_OD__

#include "ScalerFunctionInclude.h"

#if(_OD_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_2PCS)
#define _OD_ROW_ADDR_SHIFT_BIT_NUM                  12 // 2pcs DDR
#else
#define _OD_ROW_ADDR_SHIFT_BIT_NUM                  11 // 1pc DDR
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
void ScalerODSetMemoryStartAddress(void);

#if(_FRC_SUPPORT == _ON)
void ScalerODIntHandler_EXINT0(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : Initialize OD memory start address
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerODSetMemoryStartAddress(void)
{
    // Effective H_Width & V_Height of each OD path
    WORD usODHWidthPerPath = 0;
    WORD usODVHeightPerPath = 0;
    // Memory usage of each OD path
    DWORD ulODUseSpacePerPath = 0;
    DWORD ulODUseSpacePerPathInRow = 0;

    //=============================================
    // Calculate memory usage of each OD path
    //=============================================
#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
    usODHWidthPerPath = CEILING_OF_INT_DIVISION(_PANEL_DH_WIDTH, 2);
    usODVHeightPerPath = CEILING_OF_INT_DIVISION(_PANEL_DV_HEIGHT, 2);
#else
    usODHWidthPerPath = _PANEL_DH_WIDTH;
    usODVHeightPerPath = CEILING_OF_INT_DIVISION(_PANEL_DV_HEIGHT, 2);
#endif

    ulODUseSpacePerPath = ((DWORD)CEILING(usODHWidthPerPath, _OD_PIXEL_PER_COMP)) * usODVHeightPerPath * GET_OD_USE_BIT() / 10;

    // OD memory access unit: 64bit
    ulODUseSpacePerPath = CEILING(ulODUseSpacePerPath, _OD_FIFO_BUS_WIDTH);

    ulODUseSpacePerPathInRow = ulODUseSpacePerPath / _MEMORY_BIT_NUM / (_MEMORY_COL_PER_BANK * _MEMORY_BANK) + 1;

    //=============================================
    // Set start address
    //=============================================
#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
    // Enable OD Front(M1, M2)/Back(S1, S2) register separation
    ScalerSetBit(P31_F1_FRONT_BACK_REG_SEP_CTRL_LS, ~_BIT7, _BIT7);
#endif

    // OD M1
    PDATA_DWORD(0) = ((DWORD)_MEMORY_ROW - ulODUseSpacePerPathInRow) << _OD_ROW_ADDR_SHIFT_BIT_NUM;
    ScalerSetBit(P3_DA_LS_DDR_START_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[0] & 0x0F));
    ScalerSetByte(P3_DB_LS_DDR_START_ADDR_H, pData[1]);
    ScalerSetByte(P3_DC_LS_DDR_START_ADDR_M, pData[2]);
    ScalerSetByte(P3_DD_LS_DDR_START_ADDR_L, pData[3]);

    // OD M2
    PDATA_DWORD(0) = ((DWORD)_MEMORY_ROW - ulODUseSpacePerPathInRow * 2) << _OD_ROW_ADDR_SHIFT_BIT_NUM;
    ScalerSetBit(P43_DA_LS_DDR_START_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[0] & 0x0F));
    ScalerSetByte(P43_DB_LS_DDR_START_ADDR_H, pData[1]);
    ScalerSetByte(P43_DC_LS_DDR_START_ADDR_M, pData[2]);
    ScalerSetByte(P43_DD_LS_DDR_START_ADDR_L, pData[3]);

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
    // OD S1
    PDATA_DWORD(0) = ((DWORD)_MEMORY_ROW - ulODUseSpacePerPathInRow * 3) << _OD_ROW_ADDR_SHIFT_BIT_NUM;
    ScalerSetBit(P83_DA_LS_DDR_START_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[0] & 0x0F));
    ScalerSetByte(P83_DB_LS_DDR_START_ADDR_H, pData[1]);
    ScalerSetByte(P83_DC_LS_DDR_START_ADDR_M, pData[2]);
    ScalerSetByte(P83_DD_LS_DDR_START_ADDR_L, pData[3]);

    // OD S2
    PDATA_DWORD(0) = ((DWORD)_MEMORY_ROW - ulODUseSpacePerPathInRow * 4) << _OD_ROW_ADDR_SHIFT_BIT_NUM;
    ScalerSetBit(PC3_DA_LS_DDR_START_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (pData[0] & 0x0F));
    ScalerSetByte(PC3_DB_LS_DDR_START_ADDR_H, pData[1]);
    ScalerSetByte(PC3_DC_LS_DDR_START_ADDR_M, pData[2]);
    ScalerSetByte(PC3_DD_LS_DDR_START_ADDR_L, pData[3]);

    // Disable OD Front(M1, M2)/Back(S1, S2) register separation
    ScalerSetBit(P31_F1_FRONT_BACK_REG_SEP_CTRL_LS, ~_BIT7, 0x00);
#endif
}

#if(_FRC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dynamic OD handler interrupt process (EXINT0 only)
//                Dynamically enable/disable OD for memory bandwidth saving
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerODIntHandler_EXINT0(void) using 1
{
    // DEN_START event
    if(ScalerGetBit_EXINT(P0_05_IRQ_CTRL1, (_BIT3 | _BIT2)) == (_BIT3 | _BIT2))
    {
        BYTE ucBackupDataPortAddr = 0;
        BYTE ucFreerunDVSCount = 0;

        // Clear DEN_START IRQ flag
        ScalerSetBit_EXINT(P0_05_IRQ_CTRL1, ~(_BIT6 | _BIT4 | _BIT2), _BIT2);

        //=======================================================
        // Get current serial number in repeated frame sequence
        //=======================================================
        // Backup data port address
        ucBackupDataPortAddr = ScalerGetByte_EXINT(P0_2A_DISPLAY_FORMAT_ADDR_PORT);

        // Get current free run DVS counter
        ScalerSetByte_EXINT(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_28_FREE_RUN_DVS_CNT);
        ucFreerunDVSCount = ScalerGetByte_EXINT(P0_2B_DISPLAY_FORMAT_DATA_PORT);

        // Resume data port address
        ScalerSetByte_EXINT(P0_2A_DISPLAY_FORMAT_ADDR_PORT, ucBackupDataPortAddr);

        //=======================================================
        // Set OD control registers according to current state
        //=======================================================
        switch(GET_MEMORY_DVF_SELECT())
        {
            //====================================
            // DVF = 2 IVF, EX: 30 to 60Hz
            //====================================
            // I-domain frame:          |______F1_______|______F2_______|______F3_______|
            // D-domain frame:           |__F0___|__F0___|__F1___|__F1___|__F2___|__F2___|
            // <Free run DVS count>:     |___0___|___1___|___0___|___1___|___0___|___1___|
            // <OD control>:             |___on__|__off__|___on__|__off__|___on__|__off__|
            // OD actual(DB effective):  |_______|___ON__|__OFF__|___ON__|__OFF__|___ON__|
            // OD memory access:         |_______|_______|___R___|___W___|___R___|___W___|
            case _2_IVF:
                switch(ucFreerunDVSCount)
                {
                    case 0:
                        // Enable OD
                        ScalerSetBit_EXINT(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
                        break;

                    case 1:
                        // Disable OD
                        ScalerSetBit_EXINT(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);
                        break;

                    default:
                        break;
                }
                break;

            //====================================
            // DVF = 2.5 IVF, EX: 24 to 60Hz
            //====================================
            // I-domain frame:          |________F1_________|________F2_________|________F3_________|________F4_________|
            // D-domain frame:           |__F0___|__F0___|__F0___|__F1___|__F1___|__F2___|__F2___|__F2___|__F3___|__F3___|
            // <Free run DVS count>:     |___0___|___1___|___2___|___3___|___4___|___0___|___1___|___2___|___3___|___4___|
            // <OD control>:             |__off__|___on__|__off__|___on__|__off__|__off__|___on__|__off__|___on__|__off__|
            // OD actual(DB effective):  |_______|__OFF__|___ON__|__OFF__|___ON__|__OFF__|__OFF__|___ON__|__OFF__|___ON__|
            // OD memory access:         |_______|_______|___W___|___R___|___W___|___R___|_______|___W___|___R___|___W___|
            case _2_5_IVF:
                switch(ucFreerunDVSCount)
                {
                    case 0:
                    case 2:
                    case 4:
                        // Disable OD
                        ScalerSetBit_EXINT(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);
                        break;

                    case 1:
                    case 3:
                        // Enable OD
                        ScalerSetBit_EXINT(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
                        break;

                    default:
                        break;
                }
                break;

            //====================================
            // DVF = 3 IVF, EX: 24 to 72Hz
            //====================================
            // I-domain frame:          |__________F1___________|__________F2___________|__________F3___________|
            // D-domain frame:           |__F0___|__F0___|__F0___|__F1___|__F1___|__F1___|__F2___|__F2___|__F2___|
            // <Free run DVS count>:     |___0___|___1___|___2___|___0___|___1___|___2___|___0___|___1___|___2___|
            // <OD control>:             |__off__|___on__|__off__|__off__|___on__|__off__|__off__|___on__|__off__|
            // OD actual(DB effective):  |_______|__OFF__|___ON__|__OFF__|__OFF__|___ON__|__OFF__|__OFF__|___ON__|
            // OD memory access:         |_______|_______|___W___|___R___|_______|___W___|___R___|_______|___W___|
            case _3_IVF:
                switch(ucFreerunDVSCount)
                {
                    case 0:
                    case 2:
                        // Disable OD
                        ScalerSetBit_EXINT(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);
                        break;

                    case 1:
                        // Enable OD
                        ScalerSetBit_EXINT(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
                        break;

                    default:
                        break;
                }
                break;

            //====================================
            // Other cases
            //====================================
            default:
                break;
        }// End of switch(GET_MEMORY_DVF_SELECT())
    }// End of if(ScalerGetBit_EXINT(P0_05_IRQ_CTRL1, (_BIT3 | _BIT2)) == (_BIT3 | _BIT2))
} // End of void ScalerODIntHandler_EXINT0()
#endif // End of #if(_FRC_SUPPORT == _ON)
#endif  // End of #if(_OD_SUPPORT == _ON)
