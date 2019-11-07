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
// ID Code      : Pcb_Option.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __PCB_OPTION_H__
#define __PCB_OPTION_H__

//----------------------------------------------------------------------------------------------------
// ID Code      : PCB_Option.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Input Valid Port Option
//--------------------------------------------------
#define _INPUT_PORT_VALID                           ((_A0_INPUT_PORT_TYPE != _A0_NO_PORT) +\
                                                     (_D0_INPUT_PORT_TYPE != _D0_NO_PORT) +\
                                                     (_D1_INPUT_PORT_TYPE != _D1_NO_PORT) +\
                                                     (_D2_INPUT_PORT_TYPE != _D2_NO_PORT) +\
                                                     (_D3_INPUT_PORT_TYPE != _D3_NO_PORT) +\
                                                     (_D4_INPUT_PORT_TYPE != _D4_NO_PORT) +\
                                                     (_D5_INPUT_PORT_TYPE != _D5_NO_PORT) +\
                                                     (_D6_INPUT_PORT_TYPE != _D6_NO_PORT) +\
                                                     (_D7_INPUT_PORT_TYPE != _D7_NO_PORT))

//--------------------------------------------------
// Interface Support Option
//--------------------------------------------------
#if(_A0_INPUT_PORT_TYPE == _A0_VGA_PORT)
#define _VGA_PORT_EXIST                             _ON
#else
#define _VGA_PORT_EXIST                             _OFF
#endif

#if((_D0_INPUT_PORT_TYPE == _D0_DVI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_DVI_PORT) ||\
    (_D2_INPUT_PORT_TYPE == _D2_DVI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DVI_PORT) ||\
    (_D4_INPUT_PORT_TYPE == _D4_DVI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_DVI_PORT) ||\
    (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT) ||\
    (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
#define _DVI_PORT_EXIST                             _ON
#else
#define _DVI_PORT_EXIST                             _OFF
#endif

#if((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) ||\
    (_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) ||\
    (_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) ||\
    (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT) ||\
    (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT) ||\
    (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT) || (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT))
#define _HDMI_PORT_EXIST                            _ON
#else
#define _HDMI_PORT_EXIST                            _OFF
#endif

#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) || (_D1_INPUT_PORT_TYPE == _D1_DP_PORT))
#define _DP_PORT_EXIST                              _ON
#else
#define _DP_PORT_EXIST                              _OFF
#endif

#if(_VGA_PORT_EXIST == _ON)
#define _VGA_SUPPORT                                _ON
#else
#define _VGA_SUPPORT                                _OFF
#undef _YPBPR_SUPPORT
#define _YPBPR_SUPPORT                              _OFF
#endif

#if((_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
#define _DUAL_DVI_SUPPORT                           _ON
#else
#define _DUAL_DVI_SUPPORT                           _OFF
#endif

#if((_D0_INPUT_PORT_TYPE == _D0_DVI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) ||\
    (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT))
#define _D0_TMDS_SUPPORT                            _ON
#else
#define _D0_TMDS_SUPPORT                            _OFF
#endif

#if((_D1_INPUT_PORT_TYPE == _D1_DVI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) ||\
    (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
#define _D1_TMDS_SUPPORT                            _ON
#else
#define _D1_TMDS_SUPPORT                            _OFF
#endif

#if((_D2_INPUT_PORT_TYPE == _D2_DVI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) ||\
    (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
#define _D2_TMDS_SUPPORT                            _ON
#else
#define _D2_TMDS_SUPPORT                            _OFF
#endif

#if((_D3_INPUT_PORT_TYPE == _D3_DVI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) ||\
    (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT) ||\
    (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
#define _D3_TMDS_SUPPORT                            _ON
#else
#define _D3_TMDS_SUPPORT                            _OFF
#endif

#if((_D4_INPUT_PORT_TYPE == _D4_DVI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) ||\
    (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT) ||\
    (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
#define _D4_TMDS_SUPPORT                            _ON
#else
#define _D4_TMDS_SUPPORT                            _OFF
#endif

#if((_D5_INPUT_PORT_TYPE == _D5_DVI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) ||\
    (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
#define _D5_TMDS_SUPPORT                            _ON
#else
#define _D5_TMDS_SUPPORT                            _OFF
#endif

#if((_D0_TMDS_SUPPORT == _ON) || (_D1_TMDS_SUPPORT == _ON) || (_D2_TMDS_SUPPORT == _ON) ||\
    (_D3_TMDS_SUPPORT == _ON) || (_D4_TMDS_SUPPORT == _ON) || (_D5_TMDS_SUPPORT == _ON))
#define _DVI_SUPPORT                                _ON
#else
#define _DVI_SUPPORT                                _OFF
#endif

#if((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT) ||\
    ((_D0_INPUT_PORT_TYPE == _D0_DVI_PORT) && (_HDMI_FROM_DVI_CONNECT == _ON)))
#define _D0_HDMI_SUPPORT                            _ON
#else
#define _D0_HDMI_SUPPORT                            _OFF
#endif

#if((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT) ||\
    ((_D1_INPUT_PORT_TYPE == _D1_DVI_PORT) && (_HDMI_FROM_DVI_CONNECT == _ON)))
#define _D1_HDMI_SUPPORT                            _ON
#else
#define _D1_HDMI_SUPPORT                            _OFF
#endif

#if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT) ||\
    (((_D2_INPUT_PORT_TYPE == _D2_DVI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)) && (_HDMI_FROM_DVI_CONNECT == _ON)))
#define _D2_HDMI_SUPPORT                            _ON
#else
#define _D2_HDMI_SUPPORT                            _OFF
#endif

#if((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT) ||\
    (((_D3_INPUT_PORT_TYPE == _D3_DVI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT)) && (_HDMI_FROM_DVI_CONNECT == _ON)) ||\
    ((_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT) && (_HDMI_FROM_DVI_CONNECT == _ON)))
#define _D3_HDMI_SUPPORT                            _ON
#else
#define _D3_HDMI_SUPPORT                            _OFF
#endif

#if((_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT) ||\
    (((_D4_INPUT_PORT_TYPE == _D4_DVI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)) && (_HDMI_FROM_DVI_CONNECT == _ON)) ||\
    ((_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT) && (_HDMI_FROM_DVI_CONNECT == _ON)))
#define _D4_HDMI_SUPPORT                            _ON
#else
#define _D4_HDMI_SUPPORT                            _OFF
#endif

#if((_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT) ||\
    ((_D5_INPUT_PORT_TYPE == _D5_DVI_PORT) && (_HDMI_FROM_DVI_CONNECT == _ON)) ||\
    ((_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT) &&  (_HDMI_FROM_DVI_CONNECT == _ON)))
#define _D5_HDMI_SUPPORT                            _ON
#else
#define _D5_HDMI_SUPPORT                            _OFF
#endif

#if((_D0_HDMI_SUPPORT == _ON) || (_D1_HDMI_SUPPORT == _ON) || (_D2_HDMI_SUPPORT == _ON) ||\
    (_D3_HDMI_SUPPORT == _ON) || (_D4_HDMI_SUPPORT == _ON) || (_D5_HDMI_SUPPORT == _ON))
#define _HDMI_SUPPORT                               _ON
#else
#define _HDMI_SUPPORT                               _OFF
#endif

#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) || (_D1_INPUT_PORT_TYPE == _D1_DP_PORT))
#define _DP_SUPPORT                                 _ON
#else
#define _DP_SUPPORT                                 _OFF
#endif

#if((_D0_INPUT_PORT_TYPE == _D0_MHL_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT) ||\
    (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT) || (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT) || (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT))
#define _MHL_SUPPORT                                _ON
#else
#define _MHL_SUPPORT                                _OFF
#endif

#if(((_D0_INPUT_PORT_TYPE == _D0_MHL_PORT) && (_D0_MHL_VERSION >= _MHL_VERSION_3_0)) ||\
    ((_D1_INPUT_PORT_TYPE == _D1_MHL_PORT) && (_D1_MHL_VERSION >= _MHL_VERSION_3_0)) ||\
    ((_D2_INPUT_PORT_TYPE == _D2_MHL_PORT) && (_D2_MHL_VERSION >= _MHL_VERSION_3_0)) ||\
    ((_D3_INPUT_PORT_TYPE == _D3_MHL_PORT) && (_D3_MHL_VERSION >= _MHL_VERSION_3_0)) ||\
    ((_D4_INPUT_PORT_TYPE == _D4_MHL_PORT) && (_D4_MHL_VERSION >= _MHL_VERSION_3_0)) ||\
    ((_D5_INPUT_PORT_TYPE == _D5_MHL_PORT) && (_D5_MHL_VERSION >= _MHL_VERSION_3_0)))
#define _MHL_3_0_SUPPORT                            _ON
#else
#define _MHL_3_0_SUPPORT                            _OFF
#endif

#if((_DVI_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON) || (_DP_SUPPORT == _ON))
#define _DIGITAL_PORT_SUPPORT                       _ON
#else
#define _DIGITAL_PORT_SUPPORT                       _OFF
#endif

//--------------------------------------------------
// HDMI 2.0 Option
//--------------------------------------------------
#if((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT))
#if(_HW_HDMI_2_0_SUPPORT_PORT == _HDMI_2_0_D0_D1)
#define _D0_HDMI_2_0_SUPPORT                        _ON
#endif
#endif

#if((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
#if(_HW_HDMI_2_0_SUPPORT_PORT == _HDMI_2_0_D0_D1)
#define _D1_HDMI_2_0_SUPPORT                        _ON
#endif
#endif

#if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
#if(_HW_HDMI_2_0_SUPPORT_PORT == _HDMI_2_0_D2_D3_D4_D5)
#define _D2_HDMI_2_0_SUPPORT                        _ON
#endif
#endif

#if((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT))
#if(_HW_HDMI_2_0_SUPPORT_PORT == _HDMI_2_0_D2_D3_D4_D5)
#define _D3_HDMI_2_0_SUPPORT                        _ON
#endif
#endif

#if((_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT))
#if(_HW_HDMI_2_0_SUPPORT_PORT == _HDMI_2_0_D2_D3_D4_D5)
#define _D4_HDMI_2_0_SUPPORT                        _ON
#endif
#endif

#if((_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT))
#if(_HW_HDMI_2_0_SUPPORT_PORT == _HDMI_2_0_D2_D3_D4_D5)
#define _D5_HDMI_2_0_SUPPORT                        _ON
#endif
#endif

#ifndef _D0_HDMI_2_0_SUPPORT
#define _D0_HDMI_2_0_SUPPORT                        _OFF
#endif

#ifndef _D1_HDMI_2_0_SUPPORT
#define _D1_HDMI_2_0_SUPPORT                        _OFF
#endif

#ifndef _D2_HDMI_2_0_SUPPORT
#define _D2_HDMI_2_0_SUPPORT                        _OFF
#endif

#ifndef _D3_HDMI_2_0_SUPPORT
#define _D3_HDMI_2_0_SUPPORT                        _OFF
#endif

#ifndef _D4_HDMI_2_0_SUPPORT
#define _D4_HDMI_2_0_SUPPORT                        _OFF
#endif

#ifndef _D5_HDMI_2_0_SUPPORT
#define _D5_HDMI_2_0_SUPPORT                        _OFF
#endif

#if((_D0_HDMI_2_0_SUPPORT == _ON) || (_D1_HDMI_2_0_SUPPORT == _ON) || (_D2_HDMI_2_0_SUPPORT == _ON) ||\
    (_D3_HDMI_2_0_SUPPORT == _ON) || (_D4_HDMI_2_0_SUPPORT == _ON) || (_D5_HDMI_2_0_SUPPORT == _ON))
#define _HDMI_2_0_SUPPORT                           _ON
#else
#define _HDMI_2_0_SUPPORT                           _OFF
#endif

//--------------------------------------------------
// Select DP Aux Channel DDC
//--------------------------------------------------
#if((_SCALER_TYPE == _RL6193_SERIES) || (_SCALER_TYPE == _RL6410_SERIES))

#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DDC_CHANNEL_SEL == _DDC0))
#define _D0_AUX_DDC_CHANNEL                         _D0_AUX_MAP_DDC0_PIN
#else
#define _D0_AUX_DDC_CHANNEL                         _NO_AUX
#endif

#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DDC_CHANNEL_SEL == _DDC1))
#define _D1_AUX_DDC_CHANNEL                         _D1_AUX_MAP_DDC1_PIN
#else
#define _D1_AUX_DDC_CHANNEL                         _NO_AUX
#endif

#endif

//--------------------------------------------------
// Embedded EDID Option
//--------------------------------------------------
#if((_A0_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) || (_D0_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) ||\
    (_D1_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) || (_D2_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) ||\
    (_D3_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) || (_D4_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) ||\
    (_D5_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) || (_D6_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) ||\
    (_D7_D0_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) || (_D7_D1_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) ||\
    (_D0_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) || (_D1_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) ||\
    (_D2_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) || (_D3_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) ||\
    (_D4_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) || (_D5_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE))
#define _EMBEDDED_EDID_SUPPORT                      _ON
#else
#define _EMBEDDED_EDID_SUPPORT                      _OFF
#endif

//-------------------------------------------------
// EDID Location Option
//-------------------------------------------------
#if(((_A0_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)) ||\
    ((_D0_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)) ||\
    ((_D1_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)) ||\
    ((_D2_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)) ||\
    ((_D3_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)) ||\
    ((_D4_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)) ||\
    ((_D5_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)) ||\
    ((_D6_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D6_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)) ||\
    ((_D7_D0_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D7_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)) ||\
    ((_D7_D1_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D7_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)) ||\
    ((_D0_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D0_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)) ||\
    ((_D1_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D1_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)) ||\
    ((_D2_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D2_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)) ||\
    ((_D3_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D3_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)) ||\
    ((_D4_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D4_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)) ||\
    ((_D5_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D5_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_FLASH)))
#define _EDID_TABLE_LOCATED_IN_FLASH                _ON
#else
#define _EDID_TABLE_LOCATED_IN_FLASH                _OFF
#endif

#if(((_A0_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)) ||\
    ((_D0_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)) ||\
    ((_D1_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)) ||\
    ((_D2_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)) ||\
    ((_D3_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)) ||\
    ((_D4_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)) ||\
    ((_D5_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)) ||\
    ((_D6_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D6_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)) ||\
    ((_D7_D0_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D7_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)) ||\
    ((_D7_D1_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D7_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)) ||\
    ((_D0_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D0_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)) ||\
    ((_D1_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D1_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)) ||\
    ((_D2_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D2_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)) ||\
    ((_D3_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D3_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)) ||\
    ((_D4_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D4_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)) ||\
    ((_D5_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D5_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_USER)))
#define _WRITE_EDID_LOCATION_BY_USER_SUPPORT        _ON
#else
#define _WRITE_EDID_LOCATION_BY_USER_SUPPORT        _OFF
#endif

#if(_D0_HDMI_SUPPORT == _ON)
#if((_D0_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 == _EDID_NOT_EXIST) &&\
    (_D0_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 == _EDID_NOT_EXIST) &&\
    (_D0_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 == _EDID_NOT_EXIST))
#define _D0_HDMI_MULTI_EDID_SUPPORT                 _OFF
#else
#define _D0_HDMI_MULTI_EDID_SUPPORT                 _ON
#endif
#else
#define _D0_HDMI_MULTI_EDID_SUPPORT                 _OFF
#endif

#if(_D1_HDMI_SUPPORT == _ON)
#if((_D1_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 == _EDID_NOT_EXIST) &&\
    (_D1_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 == _EDID_NOT_EXIST) &&\
    (_D1_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 == _EDID_NOT_EXIST))
#define _D1_HDMI_MULTI_EDID_SUPPORT                 _OFF
#else
#define _D1_HDMI_MULTI_EDID_SUPPORT                 _ON
#endif
#else
#define _D1_HDMI_MULTI_EDID_SUPPORT                 _OFF
#endif

#if(_D2_HDMI_SUPPORT == _ON)
#if((_D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 == _EDID_NOT_EXIST) &&\
    (_D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 == _EDID_NOT_EXIST) &&\
    (_D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 == _EDID_NOT_EXIST))
#define _D2_HDMI_MULTI_EDID_SUPPORT                 _OFF
#else
#define _D2_HDMI_MULTI_EDID_SUPPORT                 _ON
#endif
#else
#define _D2_HDMI_MULTI_EDID_SUPPORT                 _OFF
#endif

#if(_D3_HDMI_SUPPORT == _ON)
#if((_D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 == _EDID_NOT_EXIST) &&\
    (_D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 == _EDID_NOT_EXIST) &&\
    (_D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 == _EDID_NOT_EXIST))
#define _D3_HDMI_MULTI_EDID_SUPPORT                 _OFF
#else
#define _D3_HDMI_MULTI_EDID_SUPPORT                 _ON
#endif
#else
#define _D3_HDMI_MULTI_EDID_SUPPORT                 _OFF
#endif

#if(_D4_HDMI_SUPPORT == _ON)
#if((_D4_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 == _EDID_NOT_EXIST) &&\
    (_D4_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 == _EDID_NOT_EXIST) &&\
    (_D4_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 == _EDID_NOT_EXIST))
#define _D4_HDMI_MULTI_EDID_SUPPORT                 _OFF
#else
#define _D4_HDMI_MULTI_EDID_SUPPORT                 _ON
#endif
#else
#define _D4_HDMI_MULTI_EDID_SUPPORT                 _OFF
#endif

#if(_D5_HDMI_SUPPORT == _ON)
#if((_D5_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 == _EDID_NOT_EXIST) &&\
    (_D5_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 == _EDID_NOT_EXIST) &&\
    (_D5_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 == _EDID_NOT_EXIST))
#define _D5_HDMI_MULTI_EDID_SUPPORT                 _OFF
#else
#define _D5_HDMI_MULTI_EDID_SUPPORT                 _ON
#endif
#else
#define _D5_HDMI_MULTI_EDID_SUPPORT                 _OFF
#endif

#if((_D0_HDMI_MULTI_EDID_SUPPORT == _ON) || (_D1_HDMI_MULTI_EDID_SUPPORT == _ON) || (_D2_HDMI_MULTI_EDID_SUPPORT == _ON) ||\
    (_D3_HDMI_MULTI_EDID_SUPPORT == _ON) || (_D4_HDMI_MULTI_EDID_SUPPORT == _ON) || (_D5_HDMI_MULTI_EDID_SUPPORT == _ON))
#define _HDMI_MULTI_EDID_SUPPORT                    _ON
#else
#define _HDMI_MULTI_EDID_SUPPORT                    _OFF
#endif

//--------------------------------------------------
// Display Spread Spectrum Option
//--------------------------------------------------
#if(_PANEL_STYLE == _PANEL_LVDS)
#define _DCLK_SPREAD_RANGE                          _LVDS_SPREAD_RANGE
#define _DCLK_SPREAD_SPEED                          _LVDS_SPREAD_SPEED
#elif(_PANEL_STYLE == _PANEL_DPTX)
#define _DCLK_SPREAD_RANGE                          0
#define _DCLK_SPREAD_SPEED                          _SPEED_33K
#elif(_PANEL_STYLE == _PANEL_VBO)
#define _DCLK_SPREAD_RANGE                          _VBO_SPREAD_RANGE
#define _DCLK_SPREAD_SPEED                          _VBO_SPREAD_SPEED
#elif(_PANEL_STYLE == _PANEL_NONE)
#define _DCLK_SPREAD_RANGE                          0
#define _DCLK_SPREAD_SPEED                          _SPEED_33K
#endif

#ifndef _DCLK_SPREAD_RANGE_MAX
#define _DCLK_SPREAD_RANGE_MAX                      _DCLK_SPREAD_RANGE
#endif

//--------------------------------------------------
// PCB power Option
//--------------------------------------------------
#define PCB_POWER_5V_DETECT()                       (_TRUE)

//--------------------------------------------------
// PWM Function Support Option
//--------------------------------------------------
#if((_PWM0_EN == _ON) || (_PWM0_PSAV_EN == _ON) || (_PWM0_PDOW_EN == _ON) ||\
    (_PWM1_EN == _ON) || (_PWM1_PSAV_EN == _ON) || (_PWM1_PDOW_EN == _ON) ||\
    (_PWM2_EN == _ON) || (_PWM2_PSAV_EN == _ON) || (_PWM2_PDOW_EN == _ON) ||\
    (_PWM3_EN == _ON) || (_PWM3_PSAV_EN == _ON) || (_PWM3_PDOW_EN == _ON) ||\
    (_PWM4_EN == _ON) || (_PWM4_PSAV_EN == _ON) || (_PWM4_PDOW_EN == _ON) ||\
    (_PWM5_EN == _ON) || (_PWM5_PSAV_EN == _ON) || (_PWM5_PDOW_EN == _ON))
#define _PWM_FUNCTION_SUPPORT                       _ON
#else
#define _PWM_FUNCTION_SUPPORT                       _OFF
#endif

//--------------------------------------------------
// Type-C Support Define
//--------------------------------------------------
#if((_D0_DP_TYPE_C_PORT_CONTROLLER_TYPE == _RTS_5400) || (_D1_DP_TYPE_C_PORT_CONTROLLER_TYPE == _RTS_5400) || (_D6_DP_TYPE_C_PORT_CONTROLLER_TYPE == _RTS_5400))
#define _PORT_CONTROLLER_RTS_5400_SUPPORT           _ON
#else
#define _PORT_CONTROLLER_RTS_5400_SUPPORT           _OFF
#endif

//--------------------------------------------------
// Type-C SMBus Communication Support Definition
//--------------------------------------------------
#if((_D0_DP_TYPE_C_PORT_CONTROLLER_TYPE == _RTS_5400) || (_D1_DP_TYPE_C_PORT_CONTROLLER_TYPE == _RTS_5400) || (_D6_DP_TYPE_C_PORT_CONTROLLER_TYPE == _RTS_5400) ||\
    (_D0_DP_TYPE_C_USB_HUB_TYPE == _RTS_5411) || (_D1_DP_TYPE_C_USB_HUB_TYPE == _RTS_5411) || (_D6_DP_TYPE_C_USB_HUB_TYPE == _RTS_5411))
#define _PORT_CONTROLLER_RTS_SMBUS_SUPPORT          _ON
#else
#define _PORT_CONTROLLER_RTS_SMBUS_SUPPORT          _OFF
#endif

//--------------------------------------------------
// Type-C Port Controller Support Definition
//--------------------------------------------------
#if((_D0_DP_TYPE_C_PORT_CONTROLLER_TYPE == _EMBEDDED) || (_D1_DP_TYPE_C_PORT_CONTROLLER_TYPE == _EMBEDDED) || (_D6_DP_TYPE_C_PORT_CONTROLLER_TYPE == _EMBEDDED))
#define _PORT_CONTROLLER_EMBEDDED_SUPPORT           _ON
#else
#define _PORT_CONTROLLER_EMBEDDED_SUPPORT           _OFF
#endif

#if((_D0_DP_TYPE_C_PORT_CONTROLLER_TYPE == _PORT_CONTOLLER_USER) || (_D1_DP_TYPE_C_PORT_CONTROLLER_TYPE == _PORT_CONTOLLER_USER) || (_D6_DP_TYPE_C_PORT_CONTROLLER_TYPE == _PORT_CONTOLLER_USER))
#define _PORT_CONTROLLER_USERDECITION_SUPPORT       _ON
#else
#define _PORT_CONTROLLER_USERDECITION_SUPPORT       _OFF
#endif

//--------------------------------------------------
// Type C Support Definition
//--------------------------------------------------
#if(_D0_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPEC)
#define _D0_DP_TYPE_C_SUPPORT                       _ON
#else
#define _D0_DP_TYPE_C_SUPPORT                       _OFF
#endif

#if(_D1_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPEC)
#define _D1_DP_TYPE_C_SUPPORT                       _ON
#else
#define _D1_DP_TYPE_C_SUPPORT                       _OFF
#endif

#if(_D6_DP_CONNECTOR_TYPE == _DP_CONNECTOR_TYPEC)
#define _D6_DP_TYPE_C_SUPPORT                       _ON
#else
#define _D6_DP_TYPE_C_SUPPORT                       _OFF
#endif

#if((_D0_DP_TYPE_C_SUPPORT == _ON) || (_D1_DP_TYPE_C_SUPPORT == _ON) || (_D6_DP_TYPE_C_SUPPORT == _ON))
#define _DP_TYPE_C_SUPPORT                          _ON
#else
#define _DP_TYPE_C_SUPPORT                          _OFF
#endif

//--------------------------------------------------
// Usb Hub Support Definition
//--------------------------------------------------
#if((_D0_DP_TYPE_C_USB_HUB_TYPE == _USB_HUB_USER) || (_D1_DP_TYPE_C_USB_HUB_TYPE == _USB_HUB_USER) || (_D6_DP_TYPE_C_USB_HUB_TYPE == _USB_HUB_USER))
#define _USB_HUB_USERDECITION_SUPPORT               _ON
#else
#define _USB_HUB_USERDECITION_SUPPORT               _OFF
#endif

#if(_D0_DP_TYPE_C_USB_HUB_TYPE != _USB_HUB_NONE)
#define _D0_DP_USB_HUB_SUPPORT                      _ON
#else
#define _D0_DP_USB_HUB_SUPPORT                      _OFF
#endif

#if(_D1_DP_TYPE_C_USB_HUB_TYPE != _USB_HUB_NONE)
#define _D1_DP_USB_HUB_SUPPORT                      _ON
#else
#define _D1_DP_USB_HUB_SUPPORT                      _OFF
#endif

#if(_D6_DP_TYPE_C_USB_HUB_TYPE != _USB_HUB_NONE)
#define _D6_DP_USB_HUB_SUPPORT                      _ON
#else
#define _D6_DP_USB_HUB_SUPPORT                      _OFF
#endif

#if((_D0_DP_USB_HUB_SUPPORT == _ON) || (_D1_DP_USB_HUB_SUPPORT == _ON) || (_D6_DP_USB_HUB_SUPPORT == _ON))
#define _DP_USB_HUB_SUPPORT                         _ON
#else
#define _DP_USB_HUB_SUPPORT                         _OFF
#endif

//--------------------------------------------------
// Enum of Pins support user to adjust configuration
//--------------------------------------------------
#if(_SCALER_TYPE == _RL6193_SERIES)
typedef enum
{
    _CONFIG_PIN_START = 0,
    _CONFIG_PIN_AB5,
    _CONFIG_PIN_Y7,
    _CONFIG_PIN_AB4,
    _CONFIG_PIN_Y6,
    _CONFIG_PIN_AC6,
    _CONFIG_PIN_AC4,
    _CONFIG_PIN_AC5,
    _CONFIG_PIN_AD6,
    _CONFIG_PIN_AD5,
    _CONFIG_PIN_AE6,
    _CONFIG_PIN_AE5,
    _CONFIG_PIN_AE4,
    _CONFIG_PIN_AF4,
    _CONFIG_PIN_AJ1,
    _CONFIG_PIN_AH2,
    _CONFIG_PIN_AH1,
    _CONFIG_PIN_H28,
    _CONFIG_PIN_H29,
    _CONFIG_PIN_J28,
    _CONFIG_PIN_J29,
    _CONFIG_PIN_N29,
    _CONFIG_PIN_N28,
    _CONFIG_PIN_M29,
    _CONFIG_PIN_M28,
    _CONFIG_PIN_L29,
    _CONFIG_PIN_L28,
    _CONFIG_PIN_U28,
    _CONFIG_PIN_T29,
    _CONFIG_PIN_T28,
    _CONFIG_PIN_R29,
    _CONFIG_PIN_R28,
    _CONFIG_PIN_P29,
    _CONFIG_PIN_P28,
    _CONFIG_PIN_AH18,
    _CONFIG_PIN_AH16,
    _CONFIG_PIN_AF28,
    _CONFIG_PIN_AD29,
    _CONFIG_PIN_AF29,
    _CONFIG_PIN_AB29,
    _CONFIG_PIN_AG29,
    _CONFIG_PIN_AH28,
    _CONFIG_PIN_AE29,
    _CONFIG_PIN_AB28,
    _CONFIG_PIN_AH25,
    _CONFIG_PIN_AJ2,
    _CONFIG_PIN_AJ6,
    _CONFIG_PIN_AK6,
    _CONFIG_PIN_AH7,
    _CONFIG_PIN_L7,
    _CONFIG_PIN_K7,
    _CONFIG_PIN_A3,
    _CONFIG_PIN_N6,
    _CONFIG_PIN_A4,
    _CONFIG_PIN_N5,
} EnumConfigPin;
#elif(_SCALER_TYPE == _RL6410_SERIES)
typedef enum
{
    _CONFIG_PIN_START = 0,
    _CONFIG_PIN_Y6,
    _CONFIG_PIN_Y5,
    _CONFIG_PIN_AA6,
    _CONFIG_PIN_AA5,
    _CONFIG_PIN_L4,
    _CONFIG_PIN_W6,
    _CONFIG_PIN_F4,
    _CONFIG_PIN_W5,
    _CONFIG_PIN_AJ3,
    _CONFIG_PIN_AJ1,
    _CONFIG_PIN_AJ2,
    _CONFIG_PIN_AK3,
    _CONFIG_PIN_AK2,
    _CONFIG_PIN_AL3,
    _CONFIG_PIN_AL2,
    _CONFIG_PIN_AL1,
    _CONFIG_PIN_AM1,
    _CONFIG_PIN_AH9,
    _CONFIG_PIN_AH8,
    _CONFIG_PIN_AJ9,
    _CONFIG_PIN_AJ8,
    _CONFIG_PIN_AL5,
    _CONFIG_PIN_AK5,
    _CONFIG_PIN_AJ5,
    _CONFIG_PIN_AK4,
    _CONFIG_PIN_AL4,
    _CONFIG_PIN_AM4,
    _CONFIG_PIN_AM2,
    _CONFIG_PIN_AM3,
    _CONFIG_PIN_G7,
    _CONFIG_PIN_J7,
    _CONFIG_PIN_H6,
    _CONFIG_PIN_AD28,
    _CONFIG_PIN_AH27,
    _CONFIG_PIN_N29,
    _CONFIG_PIN_N28,
    _CONFIG_PIN_M29,
    _CONFIG_PIN_M28,
    _CONFIG_PIN_J29,
    _CONFIG_PIN_AJ28,
    _CONFIG_PIN_N27,
    _CONFIG_PIN_K27,
    _CONFIG_PIN_M27,
    _CONFIG_PIN_K29,
    _CONFIG_PIN_J28,
    _CONFIG_PIN_J27,
    _CONFIG_PIN_K28,
    _CONFIG_PIN_AH21,
    _CONFIG_PIN_AK21,
    _CONFIG_PIN_AJ21,
    _CONFIG_PIN_AJ20,
    _CONFIG_PIN_AH20,
    _CONFIG_PIN_AL21,
    _CONFIG_PIN_AA29,
    _CONFIG_PIN_AA28,
    _CONFIG_PIN_AG25,
    _CONFIG_PIN_AH26,
    _CONFIG_PIN_AG26,
    _CONFIG_PIN_AJ26,
    _CONFIG_PIN_AF28,
    _CONFIG_PIN_AG24,
    _CONFIG_PIN_AF24,
    _CONFIG_PIN_AE28,
    _CONFIG_PIN_AJ27,
    _CONFIG_PIN_AG29,
    _CONFIG_PIN_AH25,
    _CONFIG_PIN_AF29,
    _CONFIG_PIN_AJ25,
    _CONFIG_PIN_AG28,
    _CONFIG_PIN_AH24,
    _CONFIG_PIN_AF27,
    _CONFIG_PIN_AJ24,
    _CONFIG_PIN_AG27,
    _CONFIG_PIN_AJ18,
    _CONFIG_PIN_AK18,
    _CONFIG_PIN_AE20,
    _CONFIG_PIN_AL18,
    _CONFIG_PIN_AM18,
    _CONFIG_PIN_AL19,
    _CONFIG_PIN_AM19,
    _CONFIG_PIN_AJ11,
    _CONFIG_PIN_AJ12,
    _CONFIG_PIN_AG6,
    _CONFIG_PIN_AJ4,
    _CONFIG_PIN_AF7,
    _CONFIG_PIN_AF6,
    _CONFIG_PIN_AG7,
    _CONFIG_PIN_AH7,
    _CONFIG_PIN_AH6,
    _CONFIG_PIN_AH5,
    _CONFIG_PIN_AG8,
    _CONFIG_PIN_AG9,
    _CONFIG_PIN_J6,
    _CONFIG_PIN_J5,
    _CONFIG_PIN_K6,
    _CONFIG_PIN_K5,
    _CONFIG_PIN_L6,
    _CONFIG_PIN_L5,
    _CONFIG_PIN_M6,
    _CONFIG_PIN_M5,
    _CONFIG_PIN_H7,
    _CONFIG_PIN_K7,
    _CONFIG_PIN_C8,
    _CONFIG_PIN_N6,
    _CONFIG_PIN_C6,
    _CONFIG_PIN_N5,
} EnumConfigPin;
#endif

#endif // End of #ifndef __PCB_OPTION_H__
