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
// ID Code      : RTD2014Ddcci.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RTD_DDCCI__

#include "UserCommonInclude.h"

#if(_OSD_TYPE == _REALTEK_2014_OSD)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

#define _DDCCI_FIRMWARE_VERSION                     0x01

#define _DDCCI_BLACKLEVEL_DEFAULT                   0x50

// RC
#define _DDCCI_CMD_GETVCP_RC_NO_ERROR               0x00
#define _DDCCI_CMD_GETVCP_RC_UNSUPPORTED            0x01

// TP
#define _DDCCI_CMD_GETVCP_TP_SET_PARAMETER          0x00
#define _DDCCI_CMD_GETVCP_TP_MOMENTARY              0x01

//--------------------------------------------------
// Definitions of Contrast Range (Real Value)
//--------------------------------------------------
#define _COLORTEMP_USER_MAX                         128/// 255  ///Wesley_AutoColor_20171221
#define _COLORTEMP_USER_MIN                         28/// 0   ///Wesley_AutoColor_20171221
#define _COLORTEMP_USER_CENTER                      (((_COLORTEMP_USER_MAX - _COLORTEMP_USER_MIN) / 2) + _COLORTEMP_USER_MIN)

//--------------------------------------------------
// For DDCCI Set Input Port
//--------------------------------------------------
#define _VGA_1                                      _A0_INPUT_PORT

#if((_PCB_TYPE == _RL6193_QA_A_1A1H4MHL1DP1mDP_DPTX_LVDS_VB1) || (_PCB_TYPE == _RL6193_DEMO_A_1A1H4MHL1DP_DPTX_LVDS_eDP) || (_PCB_TYPE == _RL6193_DEMO_D_1A1H4MHL1DP_DPTX_LVDS_VB1) || (_PCB_TYPE == _RL6193_DEMO_E_1H4MHL1DP1mDP_DPTX_LVDS_VB1))
#define _DVI_1                                      _NO_INPUT_PORT
#define _DVI_2                                      _NO_INPUT_PORT
#define _DP_1                                       _D0_INPUT_PORT
#define _DP_2                                       _NO_INPUT_PORT
#define _HDMI_1                                     _D1_INPUT_PORT
#define _HDMI_2                                     _D2_INPUT_PORT
#elif(_PCB_TYPE == _RL6193_QA_B_1A1H4MHL1DP_DPTX_LVDS_eDP)
#define _DVI_1                                      _NO_INPUT_PORT
#define _DVI_2                                      _NO_INPUT_PORT
#define _DP_1                                       _D1_INPUT_PORT
#define _DP_2                                       _NO_INPUT_PORT
#define _HDMI_1                                     _D0_INPUT_PORT
#define _HDMI_2                                     _D2_INPUT_PORT
#elif(_PCB_TYPE == _RL6193_DEMO_B_1A2MHL1DP1mDP1DUALDVI_DPTX_LVDS_eDP)
#define _DVI_1                                      _D4_INPUT_PORT
#define _DVI_2                                      _NO_INPUT_PORT
#define _DP_1                                       _D0_INPUT_PORT
#define _DP_2                                       _NO_INPUT_PORT
#define _HDMI_1                                     _D1_INPUT_PORT
#define _HDMI_2                                     _D2_INPUT_PORT
#elif(_PCB_TYPE == _RL6193_DEMO_C_1A3MHL1DP_DPTX_LVDS_VB1)
#define _DVI_1                                      _NO_INPUT_PORT
#define _DVI_2                                      _NO_INPUT_PORT
#define _DP_1                                       _D1_INPUT_PORT
#define _DP_2                                       _NO_INPUT_PORT
#define _HDMI_1                                     _D0_INPUT_PORT
#define _HDMI_2                                     _D4_INPUT_PORT
//user could add other PCBs if needed

#elif(_PCB_TYPE == _RL6193_AVITA)
#define _DVI_1                                      _D2_INPUT_PORT
#define _DVI_2                                      _NO_INPUT_PORT
#define _DP_1                                       _NO_INPUT_PORT
#define _DP_2                                       _NO_INPUT_PORT
#define _HDMI_1                                     _D1_INPUT_PORT
#define _HDMI_2                                    _NO_INPUT_PORT//  _D0_INPUT_PORT
//user could add other PCBs if needed
#else

#define _DVI_1                                      _NO_INPUT_PORT
#define _DVI_2                                      _NO_INPUT_PORT
#define _DP_1                                       _D0_INPUT_PORT
#define _DP_2                                       _NO_INPUT_PORT
#define _HDMI_1                                     _D1_INPUT_PORT
#define _HDMI_2                                     _D2_INPUT_PORT
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
BYTE code tCOLORPRESET_VALUE[] = {0x08, 0x06, 0x05, 0x04, 0x01, 0x0B, 0x02};

BYTE code tLANGUAGEDEFINE[] = {0x02, 0x03, 0x04, 0x0a, 0x01, 0x0d, 0x06};



//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE g_ucDdcciRedBlackLevel   = _DDCCI_BLACKLEVEL_DEFAULT;
BYTE g_ucDdcciGreenBlackLevel = _DDCCI_BLACKLEVEL_DEFAULT;
BYTE g_ucDdcciBlueBlackLevel  = _DDCCI_BLACKLEVEL_DEFAULT;
BYTE g_ucDdcciNewControlValue = 1;
BYTE g_ucDdcciActiveValue;
BYTE g_ucColorTempUnSupport;

bit g_bForcePowSavStatus = _FALSE;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void UserDdcciHandler(void);
void RTDDdcciGetVCPFeature(void);
bit RTDDdcciSetVCPFeatureCheck(void);
void RTDDdcciSetVCPFeature(void);
//void RTDDdcciResetAllSettings(void);
void RTDDdcciColorReset(void);
void RTDDdcciGetInputMsg(void);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : DDC Handler Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserDdcciHandler(void)
{
    if(GET_OSD_DDCCI_STATUS() == _ON)
    {
        // Check if Data is needed to be received
        // Reply data to source according to the request
        if(GET_RUN_DDCCI_COMMAND() == _SUCCESS)
        {
            // Copy any rx buffer input message to current DDC-CI port buffer
            RTDDdcciGetInputMsg();

            switch(g_pucDdcciRxBuf[_DDCCI_COMMAND])
            {
                case _DDCCI_CMD_GET_VCP_FEATURE:
                    RTDDdcciGetVCPFeature();
                    break;

                case _DDCCI_CMD_SET_VCP_FEATURE:
                    RTDDdcciSetVCPFeature();
                    break;

                case _DDCCI_CMD_GET_TIMING_REPORT:
                    UserCommonDdcciGetTimingReport(GET_OSD_SYSTEM_DISPLAY_REGION());
                    break;

                case _DDCCI_CMD_SAVE_CURRENT_SETTINGS:
                    break;

                case _DDCCI_CMD_CAPABILITIES_REQUEST:
                    UserCommonDdcciGetCapabilitiesRequest(GET_RUN_DDCCI_HANDLE_CHANNEL());
                    break;

                default:
                    UserCommonDdcciInitTx();
                    break;
            }

            UserCommonDdcciInitRx();

            // Clear current handle ddcci channel command flag
            CLR_RUN_DDCCI_COMMAND(GET_RUN_DDCCI_HANDLE_CHANNEL());
        }
    }
#if((_DP_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))
    else
    {
        // Check if Data is needed to be received
        // Reply data to source according to the request
        if((GET_RUN_DDCCI0_COMMAND() == _SUCCESS) && (UserInterfaceGetDpMSTCapablePort() != _DP_MST_NO_PORT))
        {
            UserCommonDdcciInitTx();

            SET_RUN_DDCCI0_COMMAND(_FAIL);
        }
    }
#endif
}

//--------------------------------------------------
// Description  : DDCCI Get VCP Feature & VCP Feature Reply
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDDdcciGetVCPFeature(void)
{
    BYTE pucTemp[2] = {0};

    g_pucDdcciTxBuf[_DDCCI_SOURCE] = _DDCCI_DEST_ADDRESS;// 0x6E
    g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 0x08;  // 0x88
    g_pucDdcciTxBuf[_DDCCI_COMMAND] = _DDCCI_CMD_GET_VCP_FEATURE_REPLY; // 0x02--VCP reply code
    g_pucDdcciTxBuf[_DDCCI_RESULT_CODE] = _DDCCI_CMD_GETVCP_RC_NO_ERROR; // 0x00
    g_pucDdcciTxBuf[_DDCCI_SINK_OPCODE] = g_pucDdcciRxBuf[_DDCCI_SOURCE_OPCODE]; // opcode

    switch(g_pucDdcciRxBuf[_DDCCI_SOURCE_OPCODE])// opcode
    {
        case _DDCCI_OPCODE_VCP_NEW_CONTROL_VALUE:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x0002, g_ucDdcciNewControlValue);
            break;
        case _DDCCI_OPCODE_VCP_DISPLAY_SCALING : // alant --aspect ratio
	     UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, _OSD_ASPECT_RATIO_AMOUNT, GET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort()));
        break;
        case _DDCCI_OPCODE_VCP_BACKLIGHT_OFFSET:
		UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 20, GET_BL_OFFSET());
        break;
        case _DDCCI_OPCODE_VCP_FACTORY_RESET:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_MOMENTARY, 0x0001, 0x00);
            break;

        case _DDCCI_OPCODE_VCP_RECAL_BRI_CON:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_MOMENTARY, 0x0001, 0x00);
            break;

        case _DDCCI_OPCODE_VCP_GEOMETRY_RESET:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_MOMENTARY, 0x0001, 0x00);
            break;

        case _DDCCI_OPCODE_VCP_COLOR_RESET:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_MOMENTARY, 0x0001, 0x00);
            break;

        case _DDCCI_OPCODE_VCP_COLOR_TEMP_INCREMENT:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x0000, 100);
            break;

        case _DDCCI_OPCODE_VCP_COLOR_TEMP_REQUEST:
            switch(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()))
            {
                case _CT_SRGB:
                    UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, (93 - 30), (40 - 30));
                    break;

                case _CT_9300:
                    UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, (93 - 30), (93 - 30));
                    break;

                case _CT_7500:
                    UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, (93 - 30), (75 - 30));
                    break;

                case _CT_6500:
                    UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, (93 - 30), (65 - 30));
                    break;

                case _CT_5800:
                    UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, (93 - 30), (50 - 30));
                    break;

                default:
                    UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, (93 - 30), (65 - 30));
                    break;
            }
            break;

#if(_VGA_SUPPORT == _ON)
        case _DDCCI_OPCODE_VCP_CLOCK:

#if(_AUTO_CLOCK_SAVE_VALUE_OPTION == _CLOCK_SAVE_PERCENT_VALUE)
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, GET_VGA_MODE_ADJUST_CLOCK());
#else
            {
                WORD usClockRangeMax = 0;
                WORD usClockRangeMin = 0;
                BYTE ucClock = 0;

                usClockRangeMax = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MAX);
                usClockRangeMin = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MIN);
                ucClock = UserCommonAdjustRealValueToPercent(GET_VGA_MODE_ADJUST_CLOCK(), usClockRangeMax, usClockRangeMin, (((usClockRangeMax - usClockRangeMin) / 2) + usClockRangeMin));

                UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, ucClock);
            }
#endif
            break;

#endif // End of #if(_VGA_SUPPORT == _ON)

        case _DDCCI_OPCODE_VCP_BACKLIGHT:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100,
                                            (WORD)UserCommonAdjustRealValueToPercent(GET_OSD_BACKLIGHT(), _BACKLIGHT_MAX, _BACKLIGHT_MIN, _BACKLIGHT_CENTER));
            break;

        case _DDCCI_OPCODE_VCP_CONTRAST:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100,
                                            (WORD)UserCommonAdjustRealValueToPercent(GET_OSD_CONTRAST(GET_OSD_SELECT_REGION()), _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER));
            break;

        case _DDCCI_OPCODE_VCP_SELECT_COLOR_PRESET:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x000B, tCOLORPRESET_VALUE[GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION())]);
            break;

        case _DDCCI_OPCODE_VCP_RED_GAIN:
          //  pucTemp[0] = GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION());

            /*if(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()) != _CT_USER)
            {
                SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_USER);

                RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
            }*/ ///Wesley_AutoColor_20171221

          //  pucTemp[1] = UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_R(),
          //                                                  _COLORTEMP_USER_MAX,
          //                                                  _COLORTEMP_USER_MIN,
          //                                                  _COLORTEMP_USER_CENTER);

            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_R(),
                                                            _COLORTEMP_USER_MAX,
                                                            _COLORTEMP_USER_MIN,
                                                            _COLORTEMP_USER_CENTER));

           // SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), pucTemp[0]);

           // RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
            break;

        case _DDCCI_OPCODE_VCP_GREEN_GAIN:
         //   pucTemp[0] = GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION());

            /*if(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()) != _CT_USER)
            {
                SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_USER);

                RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
            }*/ ///Wesley_AutoColor_20171221

         //   pucTemp[1] = UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_G(),
         //                                                   _COLORTEMP_USER_MAX,
         //                                                   _COLORTEMP_USER_MIN,
         //                                                   _COLORTEMP_USER_CENTER);

            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100,  UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_G(),
                                                            _COLORTEMP_USER_MAX,
                                                            _COLORTEMP_USER_MIN,
                                                            _COLORTEMP_USER_CENTER));

         //   SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), pucTemp[0]);

         //   RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
            break;

        case _DDCCI_OPCODE_VCP_BLUE_GAIN:
           // pucTemp[0] = GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION());

            /*if(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()) != _CT_USER)
            {
                SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_USER);

                RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
            }*/  ///Wesley_AutoColor_20171221

           // pucTemp[1] = UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_B(),
           //                                                 _COLORTEMP_USER_MAX,
           //                                                 _COLORTEMP_USER_MIN,
            //                                                _COLORTEMP_USER_CENTER);

            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_B(),
                                                            _COLORTEMP_USER_MAX,
                                                            _COLORTEMP_USER_MIN,
                                                            _COLORTEMP_USER_CENTER));

          //  SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), pucTemp[0]);

          //  RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
            break;

        case _DDCCI_OPCODE_VCP_AUTO_SET_UP:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_MOMENTARY, 0x0001, 0x00);
            break;

#if(_VGA_SUPPORT == _ON)
        case _DDCCI_OPCODE_VCP_AUTO_COLOR:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x01, 0x01);
            break;
#endif

        case _DDCCI_OPCODE_VCP_HPOSITION:
#if(_VGA_SUPPORT == _ON)
            if(SysVgaGetRegion() != _DISPLAY_RGN_NONE)
            {
                UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, GET_VGA_MODE_ADJUST_H_POSITION());
            }
#endif

            break;

        case _DDCCI_OPCODE_VCP_VPOSITION:
#if(_VGA_SUPPORT == _ON)
            if(SysVgaGetRegion() != _DISPLAY_RGN_NONE)
            {
                UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, GET_VGA_MODE_ADJUST_V_POSITION());
            }
#endif

            break;

#if(_VGA_SUPPORT == _ON)
        case _DDCCI_OPCODE_VCP_CLOCK_PHASE:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, GET_VGA_MODE_ADJUST_PHASE());
            break;
#endif

        case _DDCCI_OPCODE_VCP_ACTIVE_CONTROL:
            break;

        case _DDCCI_OPCODE_VCP_INPUT_SOURCE:
            if((GET_OSD_SYSTEM_SELECT_REGION() & 0x0F) > 0x03)
            {
                break;
            }

            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x03, OsdDispJudgeSourceType());
            break;

#if(_AUDIO_SUPPORT == _ENABLE)
        case _DDCCI_OPCODE_VCP_AUDIO_VOLUME:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, GET_OSD_VOLUME());
            break;
#endif

        case _DDCCI_OPCODE_VCP_RED_BLACK_LEVEL:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, g_ucDdcciRedBlackLevel);
            break;

        case _DDCCI_OPCODE_VCP_GREEN_BLACK_LEVEL:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, g_ucDdcciGreenBlackLevel);
            break;

        case _DDCCI_OPCODE_VCP_BLUE_BLACK_LEVEL:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 100, g_ucDdcciBlueBlackLevel);
            break;

        case _DDCCI_OPCODE_VCP_PRODUCTKEY:
            g_pucDdcciTxBuf[_DDCCI_LENGTH] = _DDCCI_CONTROL_STATUS_FLAG | 9;
            g_pucDdcciTxBuf[_DDCCI_COMMAND] = _DDCCI_CMD_GET_VCP_FEATURE_REPLY;
            break;

        case _DDCCI_OPCODE_VCP_HFREQ:
            // PDATA_DWORD(0) = (DWORD)GET_INPUT_TIMING_HFREQ() * 100;
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, LOWORD(((DWORD)GET_INPUT_TIMING_HFREQ() * 100)), HIWORD(((DWORD)GET_INPUT_TIMING_HFREQ() * 100)));
            break;

        case _DDCCI_OPCODE_VCP_VFREQ:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0xFFFF, GET_INPUT_TIMING_VFREQ()*10);
            break;

        case _DDCCI_OPCODE_VCP_PANEL_TYPE:
		{
            ///UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x01, 1);
			char tmp[_DDCCI_TXBUF_LENGTH]={0};
			BYTE ucCount = 0;
			BYTE ucCheckLen = 0;
			ucCheckLen = strlen(MODEL_TYPE_NAME);

            strncpy(tmp, MODEL_TYPE_NAME, ucCheckLen);

				 g_pucDdcciTxBuf[0] = _DDCCI_DEST_ADDRESS;// 0x6E
				 g_pucDdcciTxBuf[1] = _DDCCI_CONTROL_STATUS_FLAG | (ucCheckLen+4);  // 0x88	--- length
				 g_pucDdcciTxBuf[2] = _DDCCI_CMD_GET_VCP_FEATURE_REPLY; // 0x02--VCP reply code
				 g_pucDdcciTxBuf[3] = _DDCCI_CMD_GETVCP_RC_NO_ERROR; // 0x00
				 g_pucDdcciTxBuf[4] = _DDCCI_OPCODE_VCP_PANEL_TYPE; // opcode --0xC9
				 g_pucDdcciTxBuf[5] = _DDCCI_CMD_GETVCP_TP_SET_PARAMETER; // 0x01
				 //g_pucDdcciTxBuf[6] = 'Y';
				 //g_pucDdcciTxBuf[7] = 'L';
	             // g_pucDdcciTxBuf[8] = 'I';
				 //g_pucDdcciTxBuf[9] = '5';
				 // g_pucDdcciTxBuf[10] = '5';
				 //g_pucDdcciTxBuf[11] = '1';
				 // g_pucDdcciTxBuf[12] = '6';
				 //g_pucDdcciTxBuf[13] = '1';
				 // g_pucDdcciTxBuf[14] = chk;
				 
				 //YLI55161
				 for(ucCount = 0; ucCount < ucCheckLen; ucCount++)
				 {
					g_pucDdcciTxBuf[6+ucCount] = tmp[ucCount];

                    if((6+ucCount)>=(_DDCCI_TXBUF_LENGTH-2))  break; // boundary check            
					
				 }

				 
			 g_pucDdcciTxBuf[6+ucCount+1] = UserCommonDdcciCalCheckSum();

			
		
		    ScalerMcuDdcciSendData(GET_RUN_DDCCI_HANDLE_CHANNEL(), g_pucDdcciTxBuf);
        }
         return ;//   break;

        case _DDCCI_OPCODE_VCP_MONITOR_TYPE:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x05, 3);
            break;

        case _DDCCI_OPCODE_VCP_APPLICATION_ENABLE:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0xFF, 0x5a);
            break;

        case _DDCCI_OPCODE_VCP_CONTROLLER_TYPE:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x0000, 0x0009);
            break;

        case _DDCCI_OPCODE_VCP_FW_LEVEL:
		{

			char tmp[16]={0};
			BYTE ucCount = 0;
			BYTE ucCheckLen = 0;
			
			ucCheckLen = strlen(FW_VERSION);

            strncpy(tmp, FW_VERSION, ucCheckLen);

				 g_pucDdcciTxBuf[0] = _DDCCI_DEST_ADDRESS;// 0x6E
				 g_pucDdcciTxBuf[1] = _DDCCI_CONTROL_STATUS_FLAG | (ucCheckLen+4);  // 0x88	--- length
				 g_pucDdcciTxBuf[2] = _DDCCI_CMD_GET_VCP_FEATURE_REPLY; // 0x02--VCP reply code
				 g_pucDdcciTxBuf[3] = _DDCCI_CMD_GETVCP_RC_NO_ERROR; // 0x00
				 g_pucDdcciTxBuf[4] = _DDCCI_OPCODE_VCP_PANEL_TYPE; // opcode --0xC9
				 g_pucDdcciTxBuf[5] = _DDCCI_CMD_GETVCP_TP_SET_PARAMETER; // 0x01
				 //g_pucDdcciTxBuf[6] = '1';
				 //g_pucDdcciTxBuf[7] = '.';
	             // g_pucDdcciTxBuf[8] = '3';
				 //g_pucDdcciTxBuf[9] = '6';
				 //g_pucDdcciTxBuf[10] = chk;

				 
				 //YLI55161
				 for(ucCount = 0; ucCount < ucCheckLen; ucCount++)
				 {
					g_pucDdcciTxBuf[6+ucCount] = tmp[ucCount];

                    if((6+ucCount)>=(_DDCCI_TXBUF_LENGTH-2))  break; // boundary check            
					
				 }

				 
			 g_pucDdcciTxBuf[6+ucCount+1] = UserCommonDdcciCalCheckSum();

			
		
		    ScalerMcuDdcciSendData(GET_RUN_DDCCI_HANDLE_CHANNEL(), g_pucDdcciTxBuf);
        }	
		
        return ;//    break;

        case _DDCCI_OPCODE_VCP_OSD_ON_OFF:
            if(ScalerOsdGetOsdEnable() == _TRUE)
            {
                pucTemp[0] = 2;
            }
            else
            {
                pucTemp[0] = 1;
            }
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x02, pucTemp[0]);
            break;

        case _DDCCI_OPCODE_VCP_OSD_LANGUAGE:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x0D, tLANGUAGEDEFINE[GET_OSD_LANGUAGE()]);
            break;

        case _DDCCI_OPCODE_VCP_POWER_MODE:
            if(SysPowerGetPowerStatus() == _POWER_STATUS_OFF)
            {
                pucTemp[0] = 4;
            }
            else if(SysPowerGetPowerStatus() == _POWER_STATUS_SAVING)
            {
                pucTemp[0] = 2;
            }
            else
            {
                pucTemp[0] = 1;
            }
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x0005, pucTemp[0]);
            break;

        case _DDCCI_OPCODE_VCP_VERSION:
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0xFFFF, 0x0202);
            break;

        case _DDCCI_OPCODE_VCP_SHARPNESS:
            // MODIFY LATER
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, 0x0004, GET_OSD_SHARPNESS(UserAdjustGetSelectRegionPort()));
            break;
			
		case _DDCCI_OPCODE_VCP_GAMMA:
            // MODIFY LATER
            UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, _GAMMA_AMOUNT, GET_OSD_GAMMA(GET_OSD_SELECT_REGION()));
        break;
		
			
			case _DDCCI_OPCODE_VCP_ROTATION:
				// MODIFY LATER
				UserCommonDdcciSetVCPReplyValue(_DDCCI_CMD_GETVCP_TP_SET_PARAMETER, _DISP_ROTATE_AMOUNT, GET_OSD_DISP_ROTATE());
			break;

        default:
            g_pucDdcciTxBuf[_DDCCI_RESULT_CODE] = _DDCCI_CMD_GETVCP_RC_UNSUPPORTED;
            break;
    }
    g_pucDdcciTxBuf[	_DDCCI_PRESENT_LOW_BYTE + 1] = UserCommonDdcciCalCheckSum();

    ScalerMcuDdcciSendData(GET_RUN_DDCCI_HANDLE_CHANNEL(), g_pucDdcciTxBuf);
}

//--------------------------------------------------
// Description  : Check DDCCI Set VCP Feature
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit RTDDdcciSetVCPFeatureCheck(void)
{
    switch(g_pucDdcciRxBuf[_DDCCI_SOURCE_OPCODE])
    {
        case _DDCCI_OPCODE_VCP_FACTORY_RESET:
        case _DDCCI_OPCODE_VCP_RECAL_BRI_CON:
        case _DDCCI_OPCODE_VCP_GEOMETRY_RESET:
        case _DDCCI_OPCODE_VCP_COLOR_RESET:

            if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0)
            {
                return _FALSE;
            }

            break;

        case _DDCCI_OPCODE_VCP_NEW_CONTROL_VALUE:
        case _DDCCI_OPCODE_VCP_AUTO_SET_UP:
        case _DDCCI_OPCODE_VCP_AUTO_COLOR:

            if((g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0) || (g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] >= 3))
            {
                return _FALSE;
            }

            break;

        case _DDCCI_OPCODE_VCP_SELECT_COLOR_PRESET:

            if((g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0) || (g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] >= 0x0E))
            {
                return _FALSE;
            }

            break;

        case _DDCCI_OPCODE_VCP_OSD_LANGUAGE:

            if((g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0) || (g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] >= 0x26))
            {
                return _FALSE;
            }

            break;

        case _DDCCI_OPCODE_VCP_POWER_MODE:

            if((g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0) || (g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] >= 0x06))
            {
                return _FALSE;
            }

            break;

        default:
            break;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DDCCI Set VCP Feature
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDDdcciSetVCPFeature(void)
{
    BYTE ucTemp = 0;

    if(RTDDdcciSetVCPFeatureCheck() == _FAIL)
    {
        UserCommonDdcciInitTx();
    }
    else
    {
        switch(g_pucDdcciRxBuf[_DDCCI_SOURCE_OPCODE])// opcode
        {
            case _DDCCI_OPCODE_VCP_NEW_CONTROL_VALUE:

                if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0x01)
                {
                    g_ucDdcciNewControlValue = 0x01;
                }

                break;

            case _DDCCI_OPCODE_VCP_DISPLAY_SCALING : // alant--aspect ratio

		     if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] > _OSD_ASPECT_RATIO_AMOUNT)
		     {
			    g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] = _OSD_ASPECT_RATIO_AMOUNT;
		     }
	    
		   SET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort(),  g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
		   UserAdjustResetDisplayByPort(GET_OSD_SYSTEM_DISPLAY_REGION());
		   SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_INPUTPORTDATA_MSG);
	      	
	     break;
           case _DDCCI_OPCODE_VCP_BACKLIGHT_OFFSET:

		   if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] >20)
		   {
		      g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] = 20;
		   }

          SET_BL_OFFSET( g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
	      UserAdjustBacklight(GET_OSD_BACKLIGHT());
	      SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);


	   break;
	    case _DDCCI_OPCODE_VCP_GAMMA: // alant
	    
		
		 if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] >_GAMMA_AMOUNT)
		 {
			g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] = 1;
		 }
		
	     ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
	     UserAdjustGammaRegionEnable(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_NO_POLLING, _OFF);



         SET_OSD_GAMMA(GET_OSD_SELECT_REGION(), g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
    
         if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] <= _GAMMA_AMOUNT)
         {
     
		   UserAdjustGamma(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_GAMMA(GET_OSD_SELECT_REGION()));		 
           ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
	       UserAdjustGammaRegionEnable(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_NO_POLLING, _ON);
	
         }	
	  
          SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

		break;
		  case _DDCCI_OPCODE_VCP_ROTATION: // alant
	    
		
		 if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] >_DISP_ROTATE_AMOUNT)
		 {
			g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] = 0;
		 }
		
	     SET_OSD_DISP_ROTATE(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]); // 0,1,2,3
         SET_OSD_DISP_ROTATION_SIZE_TYPE(_OSD_ROTATE_DISPLAY_FULL); // 0,1,2
	     UserAdjustResetDisplayByPort(GET_OSD_SYSTEM_DISPLAY_REGION());
	     SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
    
		break;
			
#if(_SHARPNESS_SUPPORT == _ON)
            case _DDCCI_OPCODE_VCP_SHARPNESS:

                if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] > 4)
                {
                    g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] = 4;
                }
                SET_OSD_SHARPNESS(UserAdjustGetSelectRegionPort(), g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);

                UserCommonAdjustSharpness(GET_OSD_SYSTEM_SELECT_REGION(), UserAdjustGetSelectRegionPort());
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_INPUTPORTDATA_MSG);

                break;
#endif

            case _DDCCI_OPCODE_VCP_INPUT_SOURCE:

                if((GET_OSD_SYSTEM_SELECT_REGION() & 0x0F) > 0x03)
                {
                    break;
                }

                if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0x01)
                {
                    SET_FORCE_POW_SAV_STATUS(_FALSE);

                    switch(GET_OSD_SYSTEM_SELECT_REGION() & 0x03)
                    {
                        case 0x00:

                            SET_OSD_1P_INPUT_SOURCE(_VGA_1);
                            break;

                        case 0x01:

                            SET_OSD_2P_INPUT_SOURCE(_VGA_1);
                            break;

                        case 0x02:
                            SET_OSD_3P_INPUT_SOURCE(_VGA_1);
                            break;

                        case 0x03:

                            SET_OSD_4P_INPUT_SOURCE(_VGA_1);
                            break;

                        default:
                            break;
                    }

                    UserAdjustRegionInputPort(GET_OSD_SYSTEM_DISPLAY_REGION(), _VGA_1);// switch input source
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_INITIAL);
                }
                else if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0x03)
                {
                    SET_FORCE_POW_SAV_STATUS(_FALSE);

                    switch(GET_OSD_SYSTEM_SELECT_REGION() & 0x03)
                    {
                        case 0x00:

                            SET_OSD_1P_INPUT_SOURCE(_DVI_1);
                            break;

                        case 0x01:

                            SET_OSD_2P_INPUT_SOURCE(_DVI_1);
                            break;

                        case 0x02:

                            SET_OSD_3P_INPUT_SOURCE(_DVI_1);
                            break;

                        case 0x03:

                            SET_OSD_4P_INPUT_SOURCE(_DVI_1);
                            break;

                        default:
                            break;
                    }

                    UserAdjustRegionInputPort(GET_OSD_SYSTEM_DISPLAY_REGION(), _DVI_1);
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_INITIAL);
                }
                else if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0x04)
                {
                    SET_FORCE_POW_SAV_STATUS(_FALSE);

                    switch(GET_OSD_SYSTEM_SELECT_REGION() & 0x03)
                    {
                        case 0x00:

                            SET_OSD_1P_INPUT_SOURCE(_DVI_2);
                            break;

                        case 0x01:

                            SET_OSD_2P_INPUT_SOURCE(_DVI_2);
                            break;

                        case 0x02:

                            SET_OSD_3P_INPUT_SOURCE(_DVI_2);
                            break;

                        case 0x03:

                            SET_OSD_4P_INPUT_SOURCE(_DVI_2);
                            break;

                        default:
                            break;
                    }

                    UserAdjustRegionInputPort(GET_OSD_SYSTEM_DISPLAY_REGION(), _DVI_2);
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_INITIAL);
                }
                else if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0x0F)
                {
                    SET_FORCE_POW_SAV_STATUS(_FALSE);

                    switch(GET_OSD_SYSTEM_SELECT_REGION() & 0x03)
                    {
                        case 0x00:

                            SET_OSD_1P_INPUT_SOURCE(_DP_1);
                            break;

                        case 0x01:

                            SET_OSD_2P_INPUT_SOURCE(_DP_1);
                            break;

                        case 0x02:

                            SET_OSD_3P_INPUT_SOURCE(_DP_1);
                            break;

                        case 0x03:

                            SET_OSD_4P_INPUT_SOURCE(_DP_1);
                            break;

                        default:
                            break;
                    }

                    UserAdjustRegionInputPort(GET_OSD_SYSTEM_DISPLAY_REGION(), _DP_1);
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_INITIAL);
                }
                else if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0x10)
                {
                    SET_FORCE_POW_SAV_STATUS(_FALSE);

                    switch(GET_OSD_SYSTEM_SELECT_REGION() & 0x03)
                    {
                        case 0x00:

                            SET_OSD_1P_INPUT_SOURCE(_DP_2);
                            break;

                        case 0x01:

                            SET_OSD_2P_INPUT_SOURCE(_DP_2);
                            break;

                        case 0x02:

                            SET_OSD_3P_INPUT_SOURCE(_DP_2);
                            break;

                        case 0x03:

                            SET_OSD_4P_INPUT_SOURCE(_DP_2);
                            break;

                        default:
                            break;
                    }

                    UserAdjustRegionInputPort(GET_OSD_SYSTEM_DISPLAY_REGION(), _DP_2);
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_INITIAL);
                }
                else if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0x11)
                {
                    SET_FORCE_POW_SAV_STATUS(_FALSE);

                    switch(GET_OSD_SYSTEM_SELECT_REGION() & 0x03)
                    {
                        case 0x00:

                            SET_OSD_1P_INPUT_SOURCE(_HDMI_1);
                            break;

                        case 0x01:

                            SET_OSD_2P_INPUT_SOURCE(_HDMI_1);
                            break;

                        case 0x02:

                            SET_OSD_3P_INPUT_SOURCE(_HDMI_1);
                            break;

                        case 0x03:

                            SET_OSD_4P_INPUT_SOURCE(_HDMI_1);
                            break;

                        default:
                            break;
                    }

                    UserAdjustRegionInputPort(GET_OSD_SYSTEM_DISPLAY_REGION(), _HDMI_1);
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_INITIAL);
                }
                else if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 0x12)
                {
                    SET_FORCE_POW_SAV_STATUS(_FALSE);

                    switch(GET_OSD_SYSTEM_SELECT_REGION() & 0x03)
                    {
                        case 0x00:

                            SET_OSD_1P_INPUT_SOURCE(_HDMI_2);
                            break;

                        case 0x01:

                            SET_OSD_2P_INPUT_SOURCE(_HDMI_2);
                            break;

                        case 0x02:

                            SET_OSD_3P_INPUT_SOURCE(_HDMI_2);
                            break;

                        case 0x03:

                            SET_OSD_4P_INPUT_SOURCE(_HDMI_2);
                            break;

                        default:
                            break;
                    }

                    UserAdjustRegionInputPort(GET_OSD_SYSTEM_DISPLAY_REGION(), _HDMI_2);// switch source
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_INITIAL);// mode change again
                }

                break;

            case _DDCCI_OPCODE_VCP_FACTORY_RESET:

                OsdDispOsdReset();
/*
                RTDDdcciResetAllSettings();

#if(_VGA_SUPPORT == _ON)
                if(SysVgaGetRegion() != _DISPLAY_RGN_NONE)
                {
                    UserCommonAutoConfig();
                }
#endif
*/
                break;

            case _DDCCI_OPCODE_VCP_RECAL_BRI_CON:
                RTDNVRamRestoreOsdRegionData();
                RTDNVRamLoadOsdRegionData(GET_OSD_DISPLAY_MODE(), GET_OSD_SELECT_REGION());

                // RTDNVRamRestoreOsdInputSourceData();
                RTDNVRamRestoreBacklight();

                UserAdjustBacklight(GET_OSD_BACKLIGHT());

#if(_CONTRAST_SUPPORT == _ON)
                UserAdjustContrast(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_CONTRAST(GET_OSD_SELECT_REGION()));
#endif

#if(_BRIGHTNESS_SUPPORT == _ON)
                UserAdjustBrightness(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_BRIGHTNESS(GET_OSD_SELECT_REGION()));
#endif
                break;

            case _DDCCI_OPCODE_VCP_GEOMETRY_RESET:

#if(_VGA_SUPPORT == _ON)
                if(SysVgaGetRegion() != _DISPLAY_RGN_NONE)
                {
                    UserCommonAutoConfig();
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
                }
#endif

                break;

            case _DDCCI_OPCODE_VCP_COLOR_RESET:

                RTDDdcciColorReset();

                break;

            case _DDCCI_OPCODE_VCP_COLOR_TEMP_REQUEST:

                g_ucColorTempUnSupport = (g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] + 30);
                if(g_ucColorTempUnSupport >= 93)
                {
                    SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_9300);
                }
                else if((g_ucColorTempUnSupport < 85) && (g_ucColorTempUnSupport >= 75))
                {
                    SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_7500);
                }
                else if((g_ucColorTempUnSupport < 75) && (g_ucColorTempUnSupport >= 65))
                {
                    SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_6500);
                }
                else if((g_ucColorTempUnSupport < 60) && (g_ucColorTempUnSupport >= 50))
                {
                    SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_5800);
                }
                else
                {
                    SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_SRGB);
                }

                RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());

#if(_CONTRAST_SUPPORT == _ON)
                UserAdjustContrast(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_CONTRAST(GET_OSD_SELECT_REGION()));
#endif
                OsdDispDisableOsd();

                break;

            case _DDCCI_OPCODE_VCP_CLOCK:

#if(_VGA_SUPPORT == _ON)
                if(SysVgaGetRegion() != _DISPLAY_RGN_NONE)
                {
                    if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] > 100)
                    {
                        g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] = 100;
                    }

#if(_AUTO_CLOCK_SAVE_VALUE_OPTION == _CLOCK_SAVE_PERCENT_VALUE)
                    SET_VGA_MODE_ADJUST_CLOCK(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
#else
                    {
                        WORD usClockRangeMax = 0;
                        WORD usClockRangeMin = 0;

                        usClockRangeMax = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MAX);
                        usClockRangeMin = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MIN);

                        SET_VGA_MODE_ADJUST_CLOCK(UserCommonAdjustPercentToRealValue(GET_VGA_MODE_ADJUST_CLOCK(), usClockRangeMax, usClockRangeMin, (((usClockRangeMax - usClockRangeMin) / 2) + usClockRangeMin)));
                    }
#endif
                    UserCommonAdjustClock(GET_VGA_MODE_ADJUST_CLOCK());
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
                }
#endif // End of #if(_VGA_SUPPORT == _ON)

                break;

         
            case _DDCCI_OPCODE_VCP_BACKLIGHT:

                if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] > 100)
                {
                    g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] = 100;
                }
                SET_OSD_BACKLIGHT(UserCommonAdjustPercentToRealValue(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE], _BACKLIGHT_MAX, _BACKLIGHT_MIN, _BACKLIGHT_CENTER));

                UserAdjustBacklight(GET_OSD_BACKLIGHT());
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

                break;

            case _DDCCI_OPCODE_VCP_CONTRAST:

                if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] > 100)
                {
                    g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] = 100;
                }

                SET_OSD_CONTRAST(GET_OSD_SELECT_REGION(), UserCommonAdjustPercentToRealValue(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE], _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER));

#if(_CONTRAST_SUPPORT == _ON)
                UserAdjustContrast(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_CONTRAST(GET_OSD_SELECT_REGION()));
#endif
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);

                break;

            case _DDCCI_OPCODE_VCP_SELECT_COLOR_PRESET:

                switch(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE])
                {
                    case 0x0B:
                        SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_USER);
                        break;

                    case 0x05:
                        SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_6500);
                        break;

                    case 0x08:
                        SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_9300);
                        break;

                    case 0x01:
                        SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_SRGB);
                        break;

                    case 0x04:
                        SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_5800);
                        break;

                    case 0x06:
                        SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_7500);
                        break;

                    /*
                    case 0x02:
                        SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_OFF);
                        break;
                    */


                }

                RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());

#if(_CONTRAST_SUPPORT == _ON)
                UserAdjustContrast(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_CONTRAST(GET_OSD_SELECT_REGION()));
#endif
                OsdDispDisableOsd();

                break;

            case _DDCCI_OPCODE_VCP_RED_GAIN:
                // Only write at customer color
                if(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()) <= _CT_USER)
                {
                    ucTemp = GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION());

                   // SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_USER);

                    RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());

                    SET_COLOR_TEMP_TYPE_USER_R(UserCommonAdjustPercentToRealValue(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE],
                                                                                  _COLORTEMP_USER_MAX, _COLORTEMP_USER_MIN, _COLORTEMP_USER_CENTER));

                    RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()));

                    SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), ucTemp);

                    RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
                }
                else
                {
                    SET_COLOR_TEMP_TYPE_USER_R(UserCommonAdjustPercentToRealValue(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE],
                                                                                  _COLORTEMP_USER_MAX, _COLORTEMP_USER_MIN, _COLORTEMP_USER_CENTER));

#if(_CONTRAST_SUPPORT == _ON)
                    UserAdjustContrast(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_CONTRAST(GET_OSD_SELECT_REGION()));
#endif
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_COLORPROC_MSG);
                }

                break;

            case _DDCCI_OPCODE_VCP_GREEN_GAIN:
                // Only write at customer color
               if(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()) <= _CT_USER)
                {
                    ucTemp = GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION());

              //      SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_USER);

                    RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());

                    SET_COLOR_TEMP_TYPE_USER_G(UserCommonAdjustPercentToRealValue(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE],
                                                                                  _COLORTEMP_USER_MAX, _COLORTEMP_USER_MIN, _COLORTEMP_USER_CENTER));

                    RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()));

                    SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), ucTemp);

                    RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
                }
                else
                {
                    SET_COLOR_TEMP_TYPE_USER_G(UserCommonAdjustPercentToRealValue(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE],
                                                                                  _COLORTEMP_USER_MAX, _COLORTEMP_USER_MIN, _COLORTEMP_USER_CENTER));

#if(_CONTRAST_SUPPORT == _ON)
                    UserAdjustContrast(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_CONTRAST(GET_OSD_SELECT_REGION()));
#endif
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_COLORPROC_MSG);
                }

                break;

            case _DDCCI_OPCODE_VCP_BLUE_GAIN:
                // Only write at customer color
              if(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()) <= _CT_USER)
                {
                    ucTemp = GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION());

                   // SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), _CT_USER);

                    RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());

                    SET_COLOR_TEMP_TYPE_USER_B(UserCommonAdjustPercentToRealValue(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE],
                                                                                  _COLORTEMP_USER_MAX, _COLORTEMP_USER_MIN, _COLORTEMP_USER_CENTER));

                    RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()));

                    SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), ucTemp);

                    RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
                }
                else
                {
                    SET_COLOR_TEMP_TYPE_USER_B(UserCommonAdjustPercentToRealValue(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE],
                                                                                  _COLORTEMP_USER_MAX, _COLORTEMP_USER_MIN, _COLORTEMP_USER_CENTER));

#if(_CONTRAST_SUPPORT == _ON)
                    UserAdjustContrast(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_CONTRAST(GET_OSD_SELECT_REGION()));
#endif
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_COLORPROC_MSG);
                }

                break;

#if(_VGA_SUPPORT == _ON)
            case _DDCCI_OPCODE_VCP_AUTO_SET_UP:

                if(SysVgaGetRegion() != _DISPLAY_RGN_NONE)
                {
                    if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] != 0)
                    {
                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_DO_AUTO_CONFIG_MSG);
                    }
                }

                break;
#endif

            case _DDCCI_OPCODE_VCP_HPOSITION:

#if(_VGA_SUPPORT == _ON)
                if(SysVgaGetRegion() != _DISPLAY_RGN_NONE)
                {
                    SET_VGA_MODE_ADJUST_H_POSITION(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
                    UserCommonAdjustHPosition(GET_VGA_MODE_ADJUST_H_POSITION(), SysVgaGetRegion());
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
                }
#endif

                break;

            case _DDCCI_OPCODE_VCP_VPOSITION:

#if(_VGA_SUPPORT == _ON)

                if(SysVgaGetRegion() != _DISPLAY_RGN_NONE)
                {
                    SET_VGA_MODE_ADJUST_V_POSITION(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);
                    UserCommonAdjustVPosition(GET_VGA_MODE_ADJUST_V_POSITION(), SysVgaGetRegion());
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
                }
#endif

                break;

#if(_VGA_SUPPORT == _ON)
            case _DDCCI_OPCODE_VCP_CLOCK_PHASE:

                if(SysVgaGetRegion() != _DISPLAY_RGN_NONE)
                {
                    if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] > 100)
                    {
                        g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] = 100;
                    }

                    SET_VGA_MODE_ADJUST_PHASE(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);

                    UserCommonAdjustPhase(GET_VGA_MODE_ADJUST_PHASE());
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
                }

                break;
#endif

            case _DDCCI_OPCODE_VCP_ACTIVE_CONTROL:

                g_ucDdcciActiveValue = g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE];

                break;

#if(_AUDIO_SUPPORT == _ON)
            case _DDCCI_OPCODE_VCP_AUDIO_VOLUME:

                if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] > 100)
                {
                    g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] = 100;
                }

                SET_OSD_VOLUME(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE]);

                UserAdjustAudioVolume(GET_OSD_VOLUME());
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

                break;
#endif // End of #if(_AUDIO_SUPPORT == _ON)

            case _DDCCI_OPCODE_VCP_RED_BLACK_LEVEL:

                g_ucDdcciRedBlackLevel = g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE];
                // UserAdjustBrightness(g_ucDdcciRedBlackLevel);                            // Please don't delete

                break;

            case _DDCCI_OPCODE_VCP_GREEN_BLACK_LEVEL:

                g_ucDdcciGreenBlackLevel = g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE];
                // UserAdjustBrightness(g_ucDdcciGreenBlackLevel);                             // Please don't delete

                break;

            case _DDCCI_OPCODE_VCP_BLUE_BLACK_LEVEL:

                g_ucDdcciBlueBlackLevel = g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE];
                // UserAdjustBrightness(g_ucDdcciGreenBlackLevel);                             // Please don't delete

                break;

            case _DDCCI_OPCODE_VCP_POWER_MODE:

                if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 5)
                {
                    SET_FORCE_POW_SAV_STATUS(_FALSE);
                    SysPowerSetTargetPowerStatus(_POWER_STATUS_OFF);
                }
                else if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 4)
                {
                    SET_FORCE_POW_SAV_STATUS(_TRUE);
                    SysPowerSetTargetPowerStatus(_POWER_STATUS_SAVING);
                }
                else if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 1)
                {
                    SET_FORCE_POW_SAV_STATUS(_FALSE);
                    SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);

                    // Reset to display initial in PS state
                    if(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)
                    {
                        SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_INITIAL);
                    }
                }

                break;

            case _DDCCI_OPCODE_VCP_OSD_LANGUAGE:

                switch(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE])
                {
                  case 0x01:
                      SET_OSD_LANGUAGE(_ENGLISH);
                        break;
                   case 0x02:
                              SET_OSD_LANGUAGE(_CHINESE_T);
                        break;
                    case 0x03:
                          SET_OSD_LANGUAGE(_CHINESE_S);
                        break;
                    case 0x04:
                         SET_OSD_LANGUAGE(_JAPAN);
                        break;
                    case 0x06:
                        SET_OSD_LANGUAGE(_RUSSIAN);
                        break;
                    case 0x0A:
                         SET_OSD_LANGUAGE(_KOREA);
                         break;
                    case 0x0D:
                        break;
                    default:
                        break;
                }

                OsdDispDisableOsd();
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

                break;

            case _DDCCI_OPCODE_VCP_OSD_ON_OFF:

                if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 1)
                {
                    OsdDispDisableOsd();
                }
                else if(g_pucDdcciRxBuf[_DDCCI_SET_LOW_BYTE] == 2)
                {
                    OsdFuncEnableOsd();
                }

                break;

#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON))
            case _DDCCI_OPCODE_VCP_DISP_CALIBRATION:

                UserCommonDdcciDispCalibProcess();

                break;
#endif

            default:

                UserCommonDdcciInitTx();

                break;
        }
    }
}

//--------------------------------------------------
// Description  : Reset monitor
// Input Value  : None
// Output Value : None
//--------------------------------------------------
/*
void RTDDdcciResetAllSettings(void)
{
    UserCommonNVRamRestoreSystemData();
    RTDNVRamRestoreOsdUserData();

#if(_VGA_SUPPORT == _ON)
    UserCommonNVRamRestoreModeUserData();
#endif

    if((UserCommonNVRamGetSystemData(_SEARCH_PORT_0) != SysSourceGetInputPort()) ||
       (UserCommonNVRamGetSystemData(_SOURCE_SCAN_TYPE) != SysSourceGetScanType()))
    {
        UserCommonNVRamSetSystemData(_SEARCH_PORT_0, SysSourceGetInputPort());
        UserCommonNVRamSetSystemData(_SOURCE_SCAN_TYPE, SysSourceGetScanType());
        UserCommonNVRamSaveSystemData();
    }

    RTDDdcciColorReset();
}
*/
//--------------------------------------------------
// Description  : Reset color to default
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDDdcciColorReset(void)
{
    g_ucDdcciRedBlackLevel = _DDCCI_BLACKLEVEL_DEFAULT;
    g_ucDdcciGreenBlackLevel = _DDCCI_BLACKLEVEL_DEFAULT;
    g_ucDdcciBlueBlackLevel = _DDCCI_BLACKLEVEL_DEFAULT;

    RTDNVRamRestoreUserColorSetting();
    RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());

    RTDNVRamRestoreOsdUserData();
    RTDNVRamRestoreBacklight();

    UserAdjustBacklight(GET_OSD_BACKLIGHT());

#if(_CONTRAST_SUPPORT == _ON)
    UserAdjustContrast(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_CONTRAST(GET_OSD_SELECT_REGION()));
#endif

#if(_BRIGHTNESS_SUPPORT == _ON)
    UserAdjustBrightness(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_BRIGHTNESS(GET_OSD_SELECT_REGION()));
#endif
}

//--------------------------------------------------
// Description  : Get DDC-DI Input MSG
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDDdcciGetInputMsg(void)
{
    BYTE ucDDCCIInx = 0;

    for(ucDDCCIInx = 0; ucDDCCIInx < _MULTI_DISPLAY_MAX; ucDDCCIInx++)
    {
        if(((g_ucRunDdcciCommand >> ucDDCCIInx) & _BIT0) != 0)
        {
#if((_OGC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON) || (_OCC_SUPPORT == _ON))

            if(SysModeGetDisplayMode() != _DISPLAY_MODE_1P) // 1P Mode or OGC/OCC Support On
            {
                memcpy(g_pucDdcciRxBuf, g_pucDdcciGroupRxBuf[ucDDCCIInx], _DDCCI_RXBUF_LENGTH);
            }
#else
            memcpy(g_pucDdcciRxBuf, g_pucDdcciGroupRxBuf[ucDDCCIInx], _DDCCI_RXBUF_LENGTH);
#endif

            SET_RUN_DDCCI_HANDLE_CHANNEL(ucDDCCIInx);

            break;
        }
    }
}

#endif//#if(_OSD_TYPE == _REALTEK_2014_OSD)
