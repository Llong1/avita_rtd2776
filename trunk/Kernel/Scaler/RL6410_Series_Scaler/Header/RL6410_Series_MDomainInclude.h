/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2011>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : RL6410_Series_MDomainInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#define GET_FREE_RUN_DVTOTAL(usBackup)              {\
                                                        BYTE pucMacroDvtotalBackup[2];\
                                                        memset(pucMacroDvtotalBackup, 0, sizeof(pucMacroDvtotalBackup));\
                                                        ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_30_FIXED_DVTOTAL_MSB, 2, pucMacroDvtotalBackup, _AUTOINC);\
                                                        (usBackup) = (((pucMacroDvtotalBackup[0] & 0x3F) << 8) | (pucMacroDvtotalBackup[1]));\
                                                    }

#define SET_FREE_RUN_DVTOTAL(usBackup)              {\
                                                        ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_30_FIXED_DVTOTAL_MSB, HIBYTE(usBackup) & 0x3F);\
                                                        ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_31_FIXED_DVTOTAL_LSB, LOBYTE(usBackup));\
                                                    }

#define GET_DVTOTAL_LASTLINE(usBackup)              {\
                                                        (usBackup) = ((((WORD)(ScalerGetByte(P0_46_LAST_LINE_H1) & 0x01) << 13) |\
                                                                       ((WORD)(ScalerGetByte(P0_44_LAST_LINE_H) & 0x1F) << 8) |\
                                                                               ScalerGetByte(P0_45_LAST_LINE_L)) & 0x3FFF);\
                                                    }

#define SET_D_DOMAIN_V_ACT_END(ucPath, usBackup)    {\
                                                        switch(ucPath)\
                                                        {\
                                                            default:\
                                                            case _DISPLAY_PATH_M1:\
                                                                ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_12_DISPLAY_VER_ACT_END_H);\
                                                                ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(usBackup) & 0x1F));\
                                                                ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(usBackup));\
                                                                break;\
                                                            case _DISPLAY_PATH_M2:\
                                                                ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_1C_DISPLAY_VER_ACT_END_H_M2);\
                                                                ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(usBackup) & 0x1F));\
                                                                ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(usBackup));\
                                                                break;\
                                                            case _DISPLAY_PATH_S1:\
                                                                ScalerSetByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_12_DISPLAY_VER_ACT_END_H_S1);\
                                                                ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(usBackup) & 0x1F));\
                                                                ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(usBackup));\
                                                                break;\
                                                            case _DISPLAY_PATH_S2:\
                                                                ScalerSetByte(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_1C_DISPLAY_VER_ACT_END_H_S2);\
                                                                ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(usBackup) & 0x1F));\
                                                                ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(usBackup));\
                                                                break;\
                                                        }\
                                                     }


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerMDomainSetDisplayTimingGenActiveRegion(EnumDisplayDataPath enumDisplayDataPath);
extern bit ScalerMDomainMemoryCheck(EnumInputDataPath enumInputDataPath);
extern void ScalerMDomainSetDisplayFormat(BYTE ucMemorySel);

#if(_OD_SUPPORT == _ON)
#if(_FRC_SUPPORT == _ON)
extern WORD ScalerMDomainGetFRCMemoryBW(void);
#endif // End of #if(_FRC_SUPPORT == _ON)
#endif // End of #if(_OD_SUPPORT == _ON)
