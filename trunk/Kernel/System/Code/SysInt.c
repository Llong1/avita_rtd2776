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
// ID Code      : SysInt.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#define __SYSTEM_INT__

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
// Backup for Burst Write Bug
BYTE g_ucBackup_EXINT0;
BYTE g_ucBackup_EXINT1;
BYTE g_ucBackup_SERIAL;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void SysEXINT0(void);
void SysEXINT1(void);
void SysUartSerialPortIntProc(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Interrupt 0 Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysEXINT0(void)    interrupt 0 using 1
{
    // Backup for Burst Write Bug
    g_ucBackup_EXINT0 = MCU_FFF4_SCA_INF_ADDR;

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    ScalerDpRx0IntHandler_EXINT0();
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    ScalerDpRx1IntHandler_EXINT0();
#endif

#if(_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_BACKLIGHT)
    ScalerGlobalPreventGarbageByBacklight_EXINT0();
#endif

#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
    ScalerMHLRx0IntHandler_EXINT0();
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
    ScalerMHLRx1IntHandler_EXINT0();
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
    ScalerMHLRx2IntHandler_EXINT0();
#if(_D2_MHL_VERSION >= _MHL_VERSION_3_0)
    ScalerMHL3Rx2ECBUSIntHandler_EXINT0();
#endif
#endif

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
    ScalerMHLRx3IntHandler_EXINT0();
#if(_D3_MHL_VERSION >= _MHL_VERSION_3_0)
    ScalerMHL3Rx3ECBUSIntHandler_EXINT0();
#endif
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
    ScalerMHLRx4IntHandler_EXINT0();
#if(_D4_MHL_VERSION >= _MHL_VERSION_3_0)
    ScalerMHL3Rx4ECBUSIntHandler_EXINT0();
#endif
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
    ScalerMHLRx5IntHandler_EXINT0();
#if(_D5_MHL_VERSION >= _MHL_VERSION_3_0)
    ScalerMHL3Rx5ECBUSIntHandler_EXINT0();
#endif
#endif

#if(_HDCP_2_2_SUPPORT == _ON)
    ScalerHdcp2IntHandler_EXINT0();
#endif

    if((GET_POWER_STATUS() != _POWER_STATUS_SAVING) && (GET_POWER_STATUS() != _POWER_STATUS_OFF))
    {
#if(_D0_TMDS_SUPPORT == _ON)
        ScalerTMDSRx0IntHandler_EXINT0();
#endif

#if(_D1_TMDS_SUPPORT == _ON)
        ScalerTMDSRx1IntHandler_EXINT0();
#endif

#if(_D2_TMDS_SUPPORT == _ON)
        ScalerTMDSRx2IntHandler_EXINT0();
#endif

#if(_D3_TMDS_SUPPORT == _ON)
        ScalerTMDSRx3IntHandler_EXINT0();
#endif

#if(_D4_TMDS_SUPPORT == _ON)
        ScalerTMDSRx4IntHandler_EXINT0();
#endif

#if(_D5_TMDS_SUPPORT == _ON)
        ScalerTMDSRx5IntHandler_EXINT0();
#endif
    }
#if(_HDMI_2_0_SUPPORT == _ON)
    else
    {
#if(_D0_HDMI_2_0_SUPPORT == _ON)
        ScalerTMDSRx0PSIntHandler_EXINT0();
#endif

#if(_D1_HDMI_2_0_SUPPORT == _ON)
        ScalerTMDSRx1PSIntHandler_EXINT0();
#endif

#if(_D2_HDMI_2_0_SUPPORT == _ON)
        ScalerTMDSRx2PSIntHandler_EXINT0();
#endif

#if(_D3_HDMI_2_0_SUPPORT == _ON)
        ScalerTMDSRx3PSIntHandler_EXINT0();
#endif

#if(_D4_HDMI_2_0_SUPPORT == _ON)
        ScalerTMDSRx4PSIntHandler_EXINT0();
#endif

#if(_D5_HDMI_2_0_SUPPORT == _ON)
        ScalerTMDSRx5PSIntHandler_EXINT0();
#endif
    }
#endif

#if(_PANEL_STYLE == _PANEL_VBO)
    ScalerDisplayVboIntHandler_EXINT0();
#endif

#if((_OD_SUPPORT == _ON) && (_FRC_SUPPORT == _ON))
    ScalerODIntHandler_EXINT0();
#endif

#if(_DP_TX_SUPPORT == _ON)
    ScalerDpTxIntHandle_EXINT0();
#endif

#if(_IR_SUPPORT == _IR_HW_SUPPORT)
    ScalerIRHWModeIntHandler_EXINT0();
#endif

#if(_DP_SUPPORT == _ON)
    ScalerDpExitIntSetting_EXINT0();
#endif

    // Reload Backup for Burst Write Bug
    MCU_FFF4_SCA_INF_ADDR = g_ucBackup_EXINT0;
}

//--------------------------------------------------
// Description  : Interrupt 1 Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysEXINT1(void)    interrupt 2 using 2
{
    // Backup for Burst Write Bug
    g_ucBackup_EXINT1 = MCU_FFF4_SCA_INF_ADDR;

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
    ScalerSyncDdcDetect_EXINT1();
#endif

#if(_DEBUG_MESSAGE_SUPPORT == _ON)
    ScalerDebugIntProc_EXINT1();
#else
    if((bit)UserInterfaceGetDdcciStatus_EXINT1() == _ON)
    {
        UserCommonInterfaceDdcci0IntGetData_EXINT1();

#if(_MULTI_DISPLAY_MAX >= 0x02)
        UserCommonInterfaceDdcci1IntGetData_EXINT1();
#endif

#if(_MULTI_DISPLAY_MAX >= 0x04)
        UserCommonInterfaceDdcci2IntGetData_EXINT1();
        UserCommonInterfaceDdcci3IntGetData_EXINT1();
#endif
    }
    else
    {
        ScalerDebugIntProc_EXINT1();
    }
#endif

    // Reload Backup for Burst Write Bug
    MCU_FFF4_SCA_INF_ADDR = g_ucBackup_EXINT1;
}

//--------------------------------------------------
// Description  : Serial Port0 Interrupt Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysUartSerialPortIntProc(void)    interrupt 4
{
    // Backup for Burst Write Bug
    g_ucBackup_SERIAL = MCU_FFF4_SCA_INF_ADDR;

#if(_UART_SUPPORT == _ON)
    if(GET_UART_TRANSMIT_STATUS() == _TRUE)
    {
        CLR_UART_TRANSMIT_STATUS();
    }

    UserInterfaceUartIntHandler_SERIALPORT();
#endif

    // Reload Backup for Burst Write Bug
    MCU_FFF4_SCA_INF_ADDR = g_ucBackup_SERIAL;
}

