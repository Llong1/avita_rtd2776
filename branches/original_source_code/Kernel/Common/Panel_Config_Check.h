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
// ID Code      : Panel_Config_Check.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __PANEL_CONFIG_CHECK_H__
#define __PANEL_CONFIG_CHECK_H__

#if(_PANEL_EXIST_MULTIPANEL == _OFF)

#if(_SCALER_TYPE == _RL6193_SERIES)

#if(_PANEL_PIXEL_CLOCK_MAX_KHZ > 630000)
#warning "_PANEL_PIXEL_CLOCK_MAX_KHZ > 630M"
#endif

#elif((_SCALER_TYPE == _RL6369_SERIES) || (_SCALER_TYPE == _RL6463_SERIES))

#if(_PANEL_PIXEL_CLOCK_MAX_KHZ > 250000)
#warning "_PANEL_PIXEL_CLOCK_MAX_KHZ > 250M"
#endif

#elif(_SCALER_TYPE == _RL6410_SERIES)

#if(_D_DOMAIN_PATH == _D_DOMAIN_2_PATH)
#if(_PANEL_PIXEL_CLOCK_MAX_KHZ > 630000)
#warning "_PANEL_PIXEL_CLOCK_MAX_KHZ > 630M (2 PATH)"
#endif
#elif(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
#if(_PANEL_PIXEL_CLOCK_MAX_KHZ > 1200000)
#warning "_PANEL_PIXEL_CLOCK_MAX_KHZ > 1200M (4 PATH)"
#endif
#endif

#elif(_SCALER_TYPE == _RL6432_SERIES)

#if(_PANEL_PIXEL_CLOCK_MAX_KHZ > 360000)
#warning "_PANEL_PIXEL_CLOCK_MAX_KHZ > 360M"
#endif

#elif(_SCALER_TYPE == _RL6449_SERIES)

#if(_PANEL_PIXEL_CLOCK_MAX_KHZ > 630000)
#warning "_PANEL_PIXEL_CLOCK_MAX_KHZ > 630M"
#endif

#endif // End of #if(_SCALER_TYPE == _RL6193_SERIES)

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
#warning "Rotation/ Mirror not supported under 5k3k panel!! _DISPLAY_ROTATION_SUPPORT Set _OFF"
#endif

#if((_DISPLAY_VER_MIRROR_SUPPORT == _ON) || (_DISPLAY_HOR_MIRROR_SUPPORT == _ON))
#warning "Mirror not supported under 5k3k panel!! _DISPLAY_VER_MIRROR_SUPPORT/ _DISPLAY_HOR_MIRROR_SUPPORT Set _OFF"
#endif

#endif

//--------------------------------------------------
// Modification of Panel Parameters
//--------------------------------------------------
#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)

#if((_PANEL_DH_SYNC_WIDTH % 4) != 0)
#warning "_PANEL_DH_SYNC_WIDTH Should Be Multiple of 4 in Front_Back Mode"
#endif

#if(_PANEL_DH_START < 72)
#warning "_PANEL_DH_START Should Be Larger than 72 in Front_Back Mode"
#endif

#if((_PANEL_DH_START % 8) != 0)
#warning "_PANEL_DH_START Should Be Multiple of 8 in Front_Back Mode"
#endif

#if((_PANEL_DH_WIDTH % 4) != 0)
#warning "_PANEL_DH_WIDTH Should Be Multiple of 4 in Front_Back Mode"
#endif

#if((_PANEL_DH_END % 4) != 0)
#warning "_PANEL_DH_END Should Be Multiple of 4 in Front_Back Mode"
#endif

#if((_PANEL_DH_TOTAL % 8) != 0)
#warning "_PANEL_DH_TOTAL Should Be Multiple of 8 in Front_Back Mode"
#endif

#if((_PANEL_DH_TOTAL_MAX % 8) != 0)
#warning "_PANEL_DH_TOTAL_MAX Should Be Multiple of 8 in Front_Back Mode"
#endif

#if((_PANEL_DH_TOTAL_MIN % 8) != 0)
#warning "_PANEL_DH_TOTAL_MIN Should Be Multiple of 8 in Front_Back Mode"
#endif

#elif(_D_DOMAIN_PATH == _D_DOMAIN_2_PATH)

#if((_PANEL_DH_SYNC_WIDTH % 2) != 0)
#warning "_PANEL_DH_SYNC_WIDTH Should Be Multiple of 2 in Even_Odd Mode"
#endif

#if(_PANEL_DH_START < 36)
#warning "_PANEL_DH_START Should Be Larger than 36 in Even_Odd Mode"
#endif

#if((_PANEL_DH_START % 2) != 0)
#warning "_PANEL_DH_START Should Be Multiple of 2 in Even_Odd Mode"
#endif

#if((_PANEL_DH_WIDTH % 2) != 0)
#warning "_PANEL_DH_WIDTH Should Be Multiple of 2 in Even_Odd Mode"
#endif

#if((_PANEL_DH_END % 2) != 0)
#warning "_PANEL_DH_END Should Be Multiple of 2 in Even_Odd Mode"
#endif

#if((_PANEL_DH_TOTAL % 4) != 0)
#warning "_PANEL_DH_TOTAL Should Be Multiple of 4 in Even_Odd Mode"
#endif

#if((_PANEL_DH_TOTAL_MAX % 4) != 0)
#warning "_PANEL_DH_TOTAL_MAX Should Be Multiple of 4 in Even_Odd Mode"
#endif

#if((_PANEL_DH_TOTAL_MIN % 4) != 0)
#warning "_PANEL_DH_TOTAL_MIN Should Be Multiple of 4 in Even_Odd Mode"
#endif

#else

#if(_PANEL_DH_START < 18)
#warning "_PANEL_DH_START Should Be Larger than 18 in Single Mode"
#endif

#if((_PANEL_DH_TOTAL % 2) != 0)
#warning "_PANEL_DH_TOTAL Should Be Multiple of 2 in Single Mode"
#endif

#if((_PANEL_DH_TOTAL_MAX % 2) != 0)
#warning "_PANEL_DH_TOTAL_MAX Should Be Multiple of 2 in Single Mode"
#endif

#if((_PANEL_DH_TOTAL_MIN % 2) != 0)
#warning "_PANEL_DH_TOTAL_MIN Should Be Multiple of 2 in Single Mode"
#endif

#endif // End of #if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)


#if(_PANEL_DV_SYNC_HEIGHT < 2)
#warning "_PANEL_DV_SYNC_HEIGHT Should Be Larger than 2"
#endif

#if(_PANEL_DV_START < 2)
#warning "_PANEL_DV_START Should Be Larger than 2"
#endif

#if(_PANEL_DH_TOTAL_MIN < (_PANEL_DH_START + _PANEL_DH_WIDTH))
#warning "_PANEL_DH_TOTAL_MIN Should Be Large Than (_PANEL_DH_START + _PANEL_DH_WIDTH)"
#endif

#if(_PANEL_DH_SYNC_WIDTH >= _PANEL_DH_START)
#warning "_PANEL_DH_SYNC_WIDTH Should Be Less Than _PANEL_DH_START"
#endif

#if(_PANEL_DV_TOTAL_MIN < (_PANEL_DV_START + _PANEL_DV_HEIGHT))
#warning "_PANEL_DV_TOTAL_MIN Should Be Large Than (_PANEL_DV_START + _PANEL_DV_HEIGHT)"
#endif

#if(_PANEL_DV_SYNC_HEIGHT >= _PANEL_DV_START)
#warning "_PANEL_DV_SYNC_HEIGHT Should Be Less Than _PANEL_DV_START"
#endif

#if(_PANEL_DV_TOTAL_MAX > 8100)
#warning "_PANEL_DV_TOTAL_MAX Should Be Less Than 8100"
#endif

#if((_PANEL_DH_TOTAL % _PANEL_OUTPUT_NUM) != 0)
#warning "DHTotal Should Be Multiple of Dispaly Outport"
#endif

#if((_PANEL_DH_TOTAL_MAX % _PANEL_OUTPUT_NUM) != 0)
#warning "DHTotal Max Should Be Multiple of Dispaly Outport"
#endif

#if((_PANEL_DH_TOTAL_MIN % _PANEL_OUTPUT_NUM) != 0)
#warning "DHTotal Min Should Be Multiple of Dispaly Outport"
#endif

#if((_PANEL_DH_START % _PANEL_OUTPUT_NUM) != 0)
#warning "DHStart Should Be Multiple of Dispaly Outport"
#endif

#if((_PANEL_DH_WIDTH % _PANEL_OUTPUT_NUM) != 0)
#warning "DHWidth Should Be Multiple of Dispaly Outport"
#endif

#if((_PANEL_DH_END % _PANEL_OUTPUT_NUM) != 0)
#warning "DHWidth End Should Be Multiple of Dispaly Outport"
#endif

#if(_PANEL_STYLE == _PANEL_LVDS)

#if(_LVDS_PANEL_SECTION > _LVDS_OUTPUT_PORT)
#warning "_LVDS_PANEL_SECTION Should Be Less than or Equal to _LVDS_OUTPUT_PORT"
#endif

#if((_SCALER_TYPE == _RL6369_SERIES) || (_SCALER_TYPE == _RL6463_SERIES))
#if(_LVDS_OUTPUT_PORT > _LVDS_2_PORT)
#warning "LVDS Output Port Shold Be Less Than or Equal to 2-Port"
#endif

#elif(_SCALER_TYPE == _RL6410_SERIES)
#if(_LVDS_OUTPUT_PORT > _LVDS_4_PORT)
#warning "LVDS Output Port Shold Be Less Than or Equal to 4-Port"
#endif

#elif(_SCALER_TYPE == _RL6432_SERIES)
#if(_LVDS_OUTPUT_PORT > _LVDS_4_PORT)
#warning "LVDS Output Port Shold Be Less Than or Equal to 4-Port"
#endif

#elif(_SCALER_TYPE == _RL6449_SERIES)
#warning "_PANEL_STYLE Can Not Be _PANEL_LVDS"
#endif

#elif(_PANEL_STYLE == _PANEL_VBO)

#if(_VBO_PANEL_SECTION > _VBO_OUTPUT_PORT)
#warning "_VBO_PANEL_SECTION Should Be Less than or Equal to _VBO_OUTPUT_PORT"
#endif

#if(_PANEL_POW_SEQ_FAST_MODE == _ON)
#warning "_PANEL_POW_SEQ_FAST_MODE Should Be Off When Panel Style As VBy1"
#endif

#elif(_PANEL_STYLE == _PANEL_DPTX)

#if(_MN_LAST_LINE_MAX > (_PANEL_DH_TOTAL * 95 / 100))
#warning "_MN_LAST_LINE_MAX should be less than 0.95 _PANEL_DH_TOTAL"
#endif

#if(_MN_LAST_LINE_MIN < (_PANEL_DH_TOTAL * 5 / 100))
#warning "_MN_LAST_LINE_MIN should be larger than 0.05 _PANEL_DH_TOTAL"
#endif

#if(_MN_LAST_LINE_MAX >= _PANEL_DH_TOTAL_MIN)
#warning "_MN_LAST_LINE_MAX should be less than _PANEL_DH_TOTAL_MIN"
#endif

#if((_LAST_LINE_TARGET > _MN_LAST_LINE_MAX) || (_LAST_LINE_TARGET < _MN_LAST_LINE_MIN))
#warning "_LAST_LINE_TARGET should be in the range from _MN_LAST_LINE_MIN to _MN_LAST_LINE_MAX"
#endif

//--------------------------------------------------
// Definitions for Panel Configuration
//--------------------------------------------------
#ifndef _PANEL_DPTX_LINK_RATE
#warning "Link Rate for eDP Panel isn't define by User"
#endif

#ifndef _PANEL_DPTX_LANE_NUMBER
#warning "Lane Number for eDP Panel isn't define by User"
#endif

#if(_SCALER_TYPE == _RL6193_SERIES)
#if(_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_HBR2)
#if(_DP_TX_SUPPORT == _ON)
#warning "_DP_TX_SUPPORT Should Be Off When eDPTX Panel Support HBR2"
#endif
#endif
#endif

#if(_SCALER_TYPE == _RL6432_SERIES)
#if(_PANEL_DPTX_PORT_NUMBER_SEL != _DPTX_TX1_PORT)
#warning "Port number for Panel DPTx must be define as tx1 port by user"
#endif

#if(_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_HBR2)
#warning "Link Rate for Panel DPTx can not support HBR2 5.4G "
#endif

#if(_PANEL_DPTX_LANE_NUMBER > _PANEL_DPTX_LANE_NUMBER_4)
#warning "Lane number for Panel DPTx can not exceed 4 lane "
#endif
#endif
#endif

#if(_PANEL_STYLE == _PANEL_VBO)

#if((_PANEL_DH_TOTAL * _PANEL_DV_TOTAL / 10 * _PANEL_TYP_FRAME_RATE / 1000) > (_PANEL_PIXEL_CLOCK_MAX_KHZ - (_PANEL_PIXEL_CLOCK_MAX_KHZ / 100) - (_PANEL_PIXEL_CLOCK_MAX_KHZ * _DCLK_SPREAD_RANGE_MAX * 5 / 2000 / _DIV_8)))
#warning "(_PANEL_DH_TOTAL * _PANEL_DV_TOTAL * _PANEL_TYP_FRAME_RATE) should be less than Pixel clk max with SSCG"
#endif

#if((_PANEL_DH_TOTAL * _PANEL_DV_TOTAL / 10 * _PANEL_TYP_FRAME_RATE / 1000) < (_PANEL_PIXEL_CLOCK_MIN_KHZ + (_PANEL_PIXEL_CLOCK_MIN_KHZ / 100) + (_PANEL_PIXEL_CLOCK_MIN_KHZ * _DCLK_SPREAD_RANGE_MAX * 5 / 2000 / _DIV_8)))
#warning "(_PANEL_DH_TOTAL * _PANEL_DV_TOTAL * _PANEL_TYP_FRAME_RATE) should be larger than Pixel clk min with SSCG"
#endif

#else

#if((_PANEL_DH_TOTAL * _PANEL_DV_TOTAL / 10 * _PANEL_TYP_FRAME_RATE / 1000) > (_PANEL_PIXEL_CLOCK_MAX_KHZ - (_PANEL_PIXEL_CLOCK_MAX_KHZ / 100) - (_PANEL_PIXEL_CLOCK_MAX_KHZ * _DCLK_SPREAD_RANGE_MAX * 5 / 2000 / _DIV_1)))
#warning "(_PANEL_DH_TOTAL * _PANEL_DV_TOTAL * _PANEL_TYP_FRAME_RATE) should be less than Pixel clk max with SSCG"
#endif

#if((_PANEL_DH_TOTAL * _PANEL_DV_TOTAL / 10 * _PANEL_TYP_FRAME_RATE / 1000) < (_PANEL_PIXEL_CLOCK_MIN_KHZ + (_PANEL_PIXEL_CLOCK_MIN_KHZ / 100) + (_PANEL_PIXEL_CLOCK_MIN_KHZ * _DCLK_SPREAD_RANGE_MAX * 5 / 2000 / _DIV_1)))
#warning "(_PANEL_DH_TOTAL * _PANEL_DV_TOTAL * _PANEL_TYP_FRAME_RATE) should be larger than Pixel clk min with SSCG"
#endif

#endif

//--------------------------------------------------
// Definitions for FREESYNC Panel Parameters
//--------------------------------------------------
#if(_FREESYNC_SUPPORT == _ON)
#ifndef _PANEL_FREESYNC_MAX_FRAME_RATE
#warning "Please Define _PANEL_FREESYNC_MAX_FRAME_RATE at Panel.h for Freesync"
#endif

#ifndef _PANEL_FREESYNC_MIN_FRAME_RATE
#warning "Please Define _PANEL_FREESYNC_MIN_FRAME_RATE at Panel.h for Freesync"
#endif

#if(_TRANSLATOR_SUPPORT == _OFF)
#if(_PANEL_DV_TOTAL_MAX < ((_PANEL_DV_TOTAL * _PANEL_FREESYNC_MAX_FRAME_RATE) / _PANEL_FREESYNC_MIN_FRAME_RATE))
#warning "_PANEL_DV_TOTAL_MAX Should Be Larger than (DVTotal * FreeSync Vfreq Ratio)!"
#endif
#endif
#endif

//--------------------------------------------------
// I Dither Option
//--------------------------------------------------
#if(_I_DITHER_SUPPORT == _ON)
#if(_IDITHER_TYPE != _IDITHER_GEN_1_4_SEQ_TRUNCATE_4_2_BIT)
#if((_I_DITHER_MULTI_SEQ_ENABLE == _ENABLE) || (_I_DITHER_SHARE_SEQ_ENABLE == _ENABLE) || (_I_DITHER_SERIES_SEQ_ENABLE == _ENABLE) || (_I_DITHER_SEQ_INV_ENABLE == _ENABLE))
#warning "IDither Multi, Share, Series, Inv Function can't be used by this Gen!"
#endif
#endif

#if(_IDITHER_TYPE == _IDITHER_GEN_2_1_SEQ_NO_TEMPO_TRUNCATE_2_0_BIT)
#if((_I_DITHER_VALUE_SIGN == _ENABLE) || (_I_DITHER_V_FRAME_MOD == _ENABLE) || (_I_DITHER_H_FRAME_MOD == _ENABLE))
#warning "IDither Sign, VModu, HModu Function can't be used by this Gen!"
#endif
#endif

#endif

//--------------------------------------------------
// D Dither Option
//--------------------------------------------------
#if(_D_DITHER_SUPPORT == _ON)
#if(_DDITHER_TYPE != _DDITHER_GEN_1_6BIT_DITHERTBL)
#if((_D_DITHER_SERIES_SEQ_ENABLE == _ENABLE) || (_D_DITHER_ADVANCE_SETTING_ENABLE == _ENABLE))
#warning "DDither Series,Advance Function can't be used by this Gen!"
#endif
#endif

#if(_DDITHER_TYPE == _DDITHER_GEN_2_4_SEQ_NO_TEMPO_4BIT_DITHERTBL)
#if((_D_DITHER_V_FRAME_MOD == _ENABLE) || (_D_DITHER_H_FRAME_MOD == _ENABLE))
#warning "DDither H/V Modulation Function can't be used by this Gen!"
#endif
#endif

#endif

#endif // End of #if(_PANEL_EXIST_MULTIPANEL == _OFF)

#endif // End of #ifndef __PANEL_CONFIG_CHECK_H__
