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
// ID Code      : Pcb_Config_Pre_Check.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __PCB_CONFIG_PRE_CHECK_H__
#define __PCB_CONFIG_PRE_CHECK_H__

///////////////////////
// Input Port Config //
///////////////////////

//--------------------------------------------------
// DP Macro Pre-Check
//--------------------------------------------------
#ifdef _D0_INPUT_PORT_TYPE
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

#ifndef PCB_D0_HOTPLUG_DETECT
#warning "PCB_D0_HOTPLUG_DETECT() Should Be Defined!!!"
#endif

#if(_DP_MST_SUPPORT == _ON)
#ifndef GET_PCB_D0_DP_SOURCE_POWER
#warning "GET_PCB_D0_DP_SOURCE_POWER() Should Be Defined!!!"
#endif
#endif

#endif // End of #if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
#endif // End of #ifdef _D0_INPUT_PORT_TYPE

#ifdef _D1_INPUT_PORT_TYPE
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

#ifndef PCB_D1_HOTPLUG_DETECT
#warning "PCB_D1_HOTPLUG_DETECT() Should Be Defined!!!"
#endif

#if(_DP_MST_SUPPORT == _ON)
#ifndef GET_PCB_D1_DP_SOURCE_POWER
#warning "GET_PCB_D1_DP_SOURCE_POWER() Should Be Defined!!!"
#endif
#endif

#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
#endif // End of #ifdef _D1_INPUT_PORT_TYPE

#ifdef _D6_INPUT_PORT_TYPE
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_DP_MST_SUPPORT == _ON))

#ifndef GET_PCB_D6_DP_SOURCE_POWER
#warning "GET_PCB_D6_DP_SOURCE_POWER() Should Be Defined!!!"
#endif

#endif
#endif // End of #ifdef _D6_INPUT_PORT_TYPE

//--------------------------------------------------
// HDMI Macro Pre-Check
//--------------------------------------------------
#ifdef _D0_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0
#if(_D0_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 == _EDID_SIZE_NONE)
#ifndef PCB_D0_EXT_EDID_0_SWITCH
#warning "PCB_D0_EXT_EDID_0_SWITCH Should Be Defined!!!"
#endif
#endif
#endif

#ifdef _D0_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1
#if(_D0_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 == _EDID_SIZE_NONE)
#ifndef PCB_D0_EXT_EDID_1_SWITCH
#warning "PCB_D0_EXT_EDID_1_SWITCH Should Be Defined!!!"
#endif
#endif
#endif

#ifdef _D0_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2
#if(_D0_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 == _EDID_SIZE_NONE)
#ifndef PCB_D0_EXT_EDID_2_GPO
#warning "PCB_D0_EXT_EDID_2_GPO Should Be Defined!!!"
#endif
#endif
#endif

#ifdef _D1_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0
#if(_D1_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 == _EDID_SIZE_NONE)
#ifndef PCB_D1_EXT_EDID_0_SWITCH
#warning "PCB_D1_EXT_EDID_0_SWITCH Should Be Defined!!!"
#endif
#endif
#endif

#ifdef _D1_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1
#if(_D1_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 == _EDID_SIZE_NONE)
#ifndef PCB_D1_EXT_EDID_1_GPO
#warning "PCB_D1_EXT_EDID_1_GPO Should Be Defined!!!"
#endif
#endif
#endif

#ifdef _D1_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2
#if(_D1_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 == _EDID_SIZE_NONE)
#ifndef PCB_D1_EXT_EDID_2_GPO
#warning "PCB_D1_EXT_EDID_2_GPO Should Be Defined!!!"
#endif
#endif
#endif

#ifdef _D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0
#if(_D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 == _EDID_SIZE_NONE)
#ifndef PCB_D2_EXT_EDID_0_SWITCH
#warning "PCB_D2_EXT_EDID_0_SWITCH Should Be Defined!!!"
#endif
#endif
#endif

#ifdef _D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1
#if(_D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 == _EDID_SIZE_NONE)
#ifndef PCB_D2_EXT_EDID_1_SWITCH
#warning "PCB_D2_EXT_EDID_1_SWITCH Should Be Defined!!!"
#endif
#endif
#endif

#ifdef _D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2
#if(_D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 == _EDID_SIZE_NONE)
#ifndef PCB_D2_EXT_EDID_2_SWITCH
#warning "PCB_D2_EXT_EDID_2_SWITCH Should Be Defined!!!"
#endif
#endif
#endif

#ifdef _D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0
#if(_D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 == _EDID_SIZE_NONE)
#ifndef PCB_D3_EXT_EDID_0_SWITCH
#warning "PCB_D3_EXT_EDID_0_SWITCH Should Be Defined!!!"
#endif
#endif
#endif

#ifdef _D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1
#if(_D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 == _EDID_SIZE_NONE)
#ifndef PCB_D3_EXT_EDID_1_SWITCH
#warning "PCB_D3_EXT_EDID_1_SWITCH Should Be Defined!!!"
#endif
#endif
#endif

#ifdef _D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2
#if(_D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 == _EDID_SIZE_NONE)
#ifndef PCB_D3_EXT_EDID_2_SWITCH
#warning "PCB_D3_EXT_EDID_2_SWITCH Should Be Defined!!!"
#endif
#endif
#endif

#ifdef _D4_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0
#if(_D4_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 == _EDID_SIZE_NONE)
#ifndef PCB_D4_EXT_EDID_0_SWITCH
#warning "PCB_D4_EXT_EDID_0_SWITCH Should Be Defined!!!"
#endif
#endif
#endif

#ifdef _D4_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1
#if(_D4_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 == _EDID_SIZE_NONE)
#ifndef PCB_D4_EXT_EDID_1_SWITCH
#warning "PCB_D4_EXT_EDID_1_SWITCH Should Be Defined!!!"
#endif
#endif
#endif

#ifdef _D4_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2
#if(_D4_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 == _EDID_SIZE_NONE)
#ifndef PCB_D4_EXT_EDID_2_SWITCH
#warning "PCB_D4_EXT_EDID_2_SWITCH Should Be Defined!!!"
#endif
#endif
#endif

#ifdef _D5_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0
#if(_D5_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 == _EDID_SIZE_NONE)
#ifndef PCB_D5_EXT_EDID_0_SWITCH
#warning "PCB_D5_EXT_EDID_0_SWITCH Should Be Defined!!!"
#endif
#endif
#endif

#ifdef _D5_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1
#if(_D5_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 == _EDID_SIZE_NONE)
#ifndef PCB_D5_EXT_EDID_1_SWITCH
#warning "PCB_D5_EXT_EDID_1_SWITCH Should Be Defined!!!"
#endif
#endif
#endif

#ifdef _D5_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2
#if(_D5_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 == _EDID_SIZE_NONE)
#ifndef PCB_D5_EXT_EDID_2_SWITCH
#warning "PCB_D5_EXT_EDID_2_SWITCH Should Be Defined!!!"
#endif
#endif
#endif

#endif // End of #ifndef __PCB_CONFIG_PRE_CHECK_H__
