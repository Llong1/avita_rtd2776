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
// ID Code      : SysMHL.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SYSTEM_MHL__

#include "SysInclude.h"

#if(_MHL_SUPPORT == _ON)

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
void SysMHLMscHandler(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : MHL Handler Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysMHLMscHandler(void)
{
    BYTE ucKeyCode = 0;

    if(GET_MODE_STATE() == _MODE_STATUS_INITIAL)
    {
        CLR_MODE_STATE_CHANGE_MHL();
        return;
    }

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if(ScalerSyncCheckUrgentEvent() == _TRUE)
    {
        return;
    }
#endif

#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

    if(GET_D0_TMDS_MODE() == _TMDS_MHL_MODE)
    {
        ScalerMHLRx0CBUSPhySwitch(_ON);

        if(ScalerMHLRx0MscHandler(SysRegionConvertPortToRegion(_D0_INPUT_PORT), GET_MODE_STATE()) == _TRUE)
        {
            ///////////////
            //RAP Handler//
            ///////////////
            if(ScalerMHLRx0MscRAPHandler() == _FALSE)
            {
                if(GET_RGN_SOURCE_TYPE(SysRegionConvertPortToRegionIndex(_D0_INPUT_PORT)) != _SOURCE_NONE)
                {
                    SysModeResetDataPath(SysRegionConvertPortToRegionIndex(_D0_INPUT_PORT));
                }
            }

            ///////////////
            //RCP Handler//
            ///////////////
            if(ScalerMHLRx0MscRCPGetCommand(&ucKeyCode) == _TRUE)
            {
                if(UserInterfaceAdjustMHLMscRCPProc(ucKeyCode) == _FALSE)
                {
                    ScalerMHLRx0MscSendCommand(_MSC_MSG, _MSC_RCPE, _MSC_RCPE_INEFFECTIVE_CODE);
                }

                ScalerMHLRx0MscSendCommand(_MSC_MSG, _MSC_RCPK, ucKeyCode);
            }

            ///////////////
            //UCP Handler//
            ///////////////
#if(_MHL2_UCP_SUPPORT == _ON)
            if(ScalerMHLRx0MscUCPGetCommand(pData) == _TRUE)
            {
                ScalerMHLRx0MscSendCommand(_MSC_MSG, _MSC_UCPK, ucKeyCode);
            }
#endif  // End of #if(_MHL2_UCP_SUPPORT == _ON)

        }

        /////////////////////////
        //Check SET_INT Process//
        /////////////////////////
        ScalerMHLRx0MscCheckDeviceINT();
    }
#endif  // End of #if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

    if(GET_D1_TMDS_MODE() == _TMDS_MHL_MODE)
    {
        ScalerMHLRx1CBUSPhySwitch(_ON);

        if(ScalerMHLRx1MscHandler(SysRegionConvertPortToRegion(_D1_INPUT_PORT), GET_MODE_STATE()) == _TRUE)
        {
            ///////////////
            //RAP Handler//
            ///////////////
            if(ScalerMHLRx1MscRAPHandler() == _FALSE)
            {
                if(GET_RGN_SOURCE_TYPE(SysRegionConvertPortToRegionIndex(_D1_INPUT_PORT)) != _SOURCE_NONE)
                {
                    SysModeResetDataPath(SysRegionConvertPortToRegionIndex(_D1_INPUT_PORT));
                }
            }

            ///////////////
            //RCP Handler//
            ///////////////
            if(ScalerMHLRx1MscRCPGetCommand(&ucKeyCode) == _TRUE)
            {
                if(UserInterfaceAdjustMHLMscRCPProc(ucKeyCode) == _FALSE)
                {
                    ScalerMHLRx1MscSendCommand(_MSC_MSG, _MSC_RCPE, _MSC_RCPE_INEFFECTIVE_CODE);
                }

                ScalerMHLRx1MscSendCommand(_MSC_MSG, _MSC_RCPK, ucKeyCode);
            }

#if(_MHL2_UCP_SUPPORT == _ON)
            ///////////////
            //UCP Handler//
            ///////////////
            if(ScalerMHLRx1MscUCPGetCommand(&ucKeyCode) == _TRUE)
            {
                ScalerMHLRx1MscSendCommand(_MSC_MSG, _MSC_UCPK, ucKeyCode);
            }
#endif  // End of #if(_MHL2_UCP_SUPPORT == _ON)
        }

        /////////////////////////
        //Check SET_INT Process//
        /////////////////////////
        ScalerMHLRx1MscCheckDeviceINT();
    }
#endif  // End of #if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

    if(GET_D2_TMDS_MODE() == _TMDS_MHL_MODE)
    {
        ScalerMHLRx2CBUSPhySwitch(_ON);

        if(ScalerMHLRx2MscHandler(SysRegionConvertPortToRegion(_D2_INPUT_PORT), GET_MODE_STATE()) == _TRUE)
        {
            ///////////////
            //RAP Handler//
            ///////////////
            if(ScalerMHLRx2MscRAPHandler() == _FALSE)
            {
                if(GET_RGN_SOURCE_TYPE(SysRegionConvertPortToRegionIndex(_D2_INPUT_PORT)) != _SOURCE_NONE)
                {
                    SysModeResetDataPath(SysRegionConvertPortToRegionIndex(_D2_INPUT_PORT));
                }
            }

            ///////////////
            //RCP Handler//
            ///////////////
            if(ScalerMHLRx2MscRCPGetCommand(&ucKeyCode) == _TRUE)
            {
                if(UserInterfaceAdjustMHLMscRCPProc(ucKeyCode) == _FALSE)
                {
                    ScalerMHLRx2MscSendCommand(_MSC_MSG, _MSC_RCPE, _MSC_RCPE_INEFFECTIVE_CODE);
                }

                ScalerMHLRx2MscSendCommand(_MSC_MSG, _MSC_RCPK, ucKeyCode);
            }

            ///////////////
            //UCP Handler//
            ///////////////
#if(_MHL2_UCP_SUPPORT == _ON)
            if(ScalerMHLRx2MscUCPGetCommand(&ucKeyCode) == _TRUE)
            {
                ScalerMHLRx2MscSendCommand(_MSC_MSG, _MSC_UCPK, ucKeyCode);
            }
#endif  // End of #if(_MHL2_UCP_SUPPORT == _ON)

#if(_D2_MHL_VERSION >= _MHL_VERSION_3_0)

            ////////////////
            // ECBUS EMSC //
            ////////////////
            if(ScalerMHL3Rx2ECBUSHandler() == _TRUE)
            {
                ScalerMHL3Rx2ECBUSEMSCRxHandler();

                ScalerMHL3Rx2ECBUSEMSCTxHandler();
            }

#endif // End of #if(_D2_MHL_VERSION >= _MHL_VERSION_3_0)

        }

        /////////////////////////
        //Check SET_INT Process//
        /////////////////////////
        ScalerMHLRx2MscCheckDeviceINT();

#if(_D2_MHL_VERSION >= _MHL_VERSION_3_0)

        ///////////////////////////////
        // Check WRITE_BURST Process //
        ///////////////////////////////
        ScalerMHLRx2CheckWriteBurst();

        /////////////////////////////
        // Check eMSC BIST Process //
        /////////////////////////////
        ScalerMHL3Rx2BISTHandler();

#endif // End of #if(_D2_MHL_VERSION >= _MHL_VERSION_3_0)

    }
#endif  // End of #if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)

    if(GET_D3_TMDS_MODE() == _TMDS_MHL_MODE)
    {
        ScalerMHLRx3CBUSPhySwitch(_ON);

        if(ScalerMHLRx3MscHandler(SysRegionConvertPortToRegion(_D3_INPUT_PORT), GET_MODE_STATE()) == _TRUE)
        {
            ///////////////
            //RAP Handler//
            ///////////////
            if(ScalerMHLRx3MscRAPHandler() == _FALSE)
            {
                if(GET_RGN_SOURCE_TYPE(SysRegionConvertPortToRegionIndex(_D3_INPUT_PORT)) != _SOURCE_NONE)
                {
                    SysModeResetDataPath(SysRegionConvertPortToRegionIndex(_D3_INPUT_PORT));
                }
            }

            ///////////////
            //RCP Handler//
            ///////////////
            if(ScalerMHLRx3MscRCPGetCommand(&ucKeyCode) == _TRUE)
            {
                if(UserInterfaceAdjustMHLMscRCPProc(ucKeyCode) == _FALSE)
                {
                    ScalerMHLRx3MscSendCommand(_MSC_MSG, _MSC_RCPE, _MSC_RCPE_INEFFECTIVE_CODE);
                }

                ScalerMHLRx3MscSendCommand(_MSC_MSG, _MSC_RCPK, ucKeyCode);
            }

#if(_MHL2_UCP_SUPPORT == _ON)
            ///////////////
            //UCP Handler//
            ///////////////
            if(ScalerMHLRx3MscUCPGetCommand(&ucKeyCode) == _TRUE)
            {
                ScalerMHLRx3MscSendCommand(_MSC_MSG, _MSC_UCPK, ucKeyCode);
            }
#endif  // End of #if(_MHL2_UCP_SUPPORT == _ON)

#if(_D3_MHL_VERSION >= _MHL_VERSION_3_0)

            ////////////////
            // ECBUS EMSC //
            ////////////////
            if(ScalerMHL3Rx3ECBUSHandler() == _TRUE)
            {
                ScalerMHL3Rx3ECBUSEMSCRxHandler();

                ScalerMHL3Rx3ECBUSEMSCTxHandler();
            }

#endif // End of #if(_D2_MHL_VERSION >= _MHL_VERSION_3_0)

        }

        /////////////////////////
        //Check SET_INT Process//
        /////////////////////////
        ScalerMHLRx3MscCheckDeviceINT();

#if(_D3_MHL_VERSION >= _MHL_VERSION_3_0)

        ///////////////////////////////
        // Check WRITE_BURST Process //
        ///////////////////////////////
        ScalerMHLRx3CheckWriteBurst();

        /////////////////////////////
        // Check eMSC BIST Process //
        /////////////////////////////
        ScalerMHL3Rx3BISTHandler();

#endif // End of #if(_D3_MHL_VERSION >= _MHL_VERSION_3_0)

    }

#endif  // End of #if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)

    if(GET_D4_TMDS_MODE() == _TMDS_MHL_MODE)
    {
        ScalerMHLRx4CBUSPhySwitch(_ON);

        if(ScalerMHLRx4MscHandler(SysRegionConvertPortToRegion(_D4_INPUT_PORT), GET_MODE_STATE()) == _TRUE)
        {
            ///////////////
            //RAP Handler//
            ///////////////
            if(ScalerMHLRx4MscRAPHandler() == _FALSE)
            {
                if(GET_RGN_SOURCE_TYPE(SysRegionConvertPortToRegionIndex(_D4_INPUT_PORT)) != _SOURCE_NONE)
                {
                    SysModeResetDataPath(SysRegionConvertPortToRegionIndex(_D4_INPUT_PORT));
                }
            }

            ///////////////
            //RCP Handler//
            ///////////////
            if(ScalerMHLRx4MscRCPGetCommand(&ucKeyCode) == _TRUE)
            {
                if(UserInterfaceAdjustMHLMscRCPProc(ucKeyCode) == _FALSE)
                {
                    ScalerMHLRx4MscSendCommand(_MSC_MSG, _MSC_RCPE, _MSC_RCPE_INEFFECTIVE_CODE);
                }

                ScalerMHLRx4MscSendCommand(_MSC_MSG, _MSC_RCPK, ucKeyCode);
            }

            ///////////////
            //UCP Handler//
            ///////////////
#if(_MHL2_UCP_SUPPORT == _ON)
            if(ScalerMHLRx4MscUCPGetCommand(&ucKeyCode) == _TRUE)
            {
                ScalerMHLRx4MscSendCommand(_MSC_MSG, _MSC_UCPK, ucKeyCode);
            }
#endif  // End of #if(_MHL2_UCP_SUPPORT == _ON)

#if(_D4_MHL_VERSION >= _MHL_VERSION_3_0)

            ////////////////
            // ECBUS EMSC //
            ////////////////
            if(ScalerMHL3Rx4ECBUSHandler() == _TRUE)
            {
                ScalerMHL3Rx4ECBUSEMSCRxHandler();

                ScalerMHL3Rx4ECBUSEMSCTxHandler();
            }

#endif // End of #if(_D2_MHL_VERSION >= _MHL_VERSION_3_0)

        }

        /////////////////////////
        //Check SET_INT Process//
        /////////////////////////
        ScalerMHLRx4MscCheckDeviceINT();

#if(_D4_MHL_VERSION >= _MHL_VERSION_3_0)

        ///////////////////////////////
        // Check WRITE_BURST Process //
        ///////////////////////////////
        ScalerMHLRx4CheckWriteBurst();

        /////////////////////////////
        // Check eMSC BIST Process //
        /////////////////////////////
        ScalerMHL3Rx4BISTHandler();

#endif // End of #if(_D4_MHL_VERSION >= _MHL_VERSION_3_0)

    }
#endif  // End of #if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

    if(GET_D5_TMDS_MODE() == _TMDS_MHL_MODE)
    {
        ScalerMHLRx5CBUSPhySwitch(_ON);

        if(ScalerMHLRx5MscHandler(SysRegionConvertPortToRegion(_D5_INPUT_PORT), GET_MODE_STATE()) == _TRUE)
        {
            ///////////////
            //RAP Handler//
            ///////////////
            if(ScalerMHLRx5MscRAPHandler() == _FALSE)
            {
                if(GET_RGN_SOURCE_TYPE(SysRegionConvertPortToRegionIndex(_D5_INPUT_PORT)) != _SOURCE_NONE)
                {
                    SysModeResetDataPath(SysRegionConvertPortToRegionIndex(_D5_INPUT_PORT));
                }
            }

            ///////////////
            //RCP Handler//
            ///////////////
            if(ScalerMHLRx5MscRCPGetCommand(&ucKeyCode) == _TRUE)
            {
                if(UserInterfaceAdjustMHLMscRCPProc(ucKeyCode) == _FALSE)
                {
                    ScalerMHLRx5MscSendCommand(_MSC_MSG, _MSC_RCPE, _MSC_RCPE_INEFFECTIVE_CODE);
                }

                ScalerMHLRx5MscSendCommand(_MSC_MSG, _MSC_RCPK, ucKeyCode);
            }

#if(_MHL2_UCP_SUPPORT == _ON)
            ///////////////
            //UCP Handler//
            ///////////////
            if(ScalerMHLRx5MscUCPGetCommand(&ucKeyCode) == _TRUE)
            {
                ScalerMHLRx5MscSendCommand(_MSC_MSG, _MSC_UCPK, ucKeyCode);
            }
#endif  // End of #if(_MHL2_UCP_SUPPORT == _ON)

#if(_D5_MHL_VERSION >= _MHL_VERSION_3_0)

            ////////////////
            // ECBUS EMSC //
            ////////////////
            if(ScalerMHL3Rx5ECBUSHandler() == _TRUE)
            {
                ScalerMHL3Rx5ECBUSEMSCRxHandler();

                ScalerMHL3Rx5ECBUSEMSCTxHandler();
            }

#endif // End of #if(_D2_MHL_VERSION >= _MHL_VERSION_3_0)

        }

        /////////////////////////
        //Check SET_INT Process//
        /////////////////////////
        ScalerMHLRx5MscCheckDeviceINT();

#if(_D5_MHL_VERSION >= _MHL_VERSION_3_0)

        ///////////////////////////////
        // Check WRITE_BURST Process //
        ///////////////////////////////
        ScalerMHLRx5CheckWriteBurst();

        /////////////////////////////
        // Check eMSC BIST Process //
        /////////////////////////////
        ScalerMHL3Rx5BISTHandler();

#endif // End of #if(_D5_MHL_VERSION >= _MHL_VERSION_3_0)
    }
#endif  // End of #if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

    CLR_MODE_STATE_CHANGE_MHL();
}

#endif // End of #if(_MHL_SUPPORT == _ON)
