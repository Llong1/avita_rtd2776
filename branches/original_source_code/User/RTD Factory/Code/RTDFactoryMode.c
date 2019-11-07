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
// ID Code      : RTDFactoryMode.c No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------
#define __FACTORY_MODE__

#include "UserCommonInclude.h"

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
BYTE g_ucFactoryPage;
BYTE g_ucBgColorR;
BYTE g_ucBgColorG;
BYTE g_ucBgColorB;
BYTE g_ucAutoColotTypeFontPointer;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void RTDFactoryMenuOperation(void);
void RTDFactoryMainMenu(void);
void RTDFactoryMainMenu1(void);
//============= Auto Color =======================
void RTDFactoryAutoColorEnter(void);
void RTDFactoryAutoColorLeft(void);
void RTDFactoryAutoColorRight(void);
void RTDFactoryAutoColorExit(void);
//============= Auto Color Type =======================
void RTDFactoryAutoColorTypeEnter(void);
void RTDFactoryAutoColorTypeLeft(void);
void RTDFactoryAutoColorTypeRight(void);
void RTDFactoryAutoColorTypeExit(void);
//============= Burnin =======================
void RTDFactoryBurninEnter(void);
void RTDFactoryBurninLeft(void);
void RTDFactoryBurninRight(void);
void RTDFactoryBurninExit(void);
//============= Reset Burnin Time =======================
void RTDFactoryResetBurninTimeEnter(void);
void RTDFactoryResetBurninTimeLeft(void);
void RTDFactoryResetBurninTimeRight(void);
void RTDFactoryResetBurninTimeExit(void);
//============= Reset Panel Time =======================
void RTDFactoryResetPanelTimeEnter(void);
void RTDFactoryResetPanelTimeLeft(void);
void RTDFactoryResetPanelTimeRight(void);
void RTDFactoryResetPanelTimeExit(void);
//============= Colortemp 1 R=======================
void RTDFactoryColortemp1REnter(void);
void RTDFactoryColortemp1RLeft(void);
void RTDFactoryColortemp1RRight(void);
void RTDFactoryColortemp1RExit(void);
//============= Colortemp 1 G=======================
void RTDFactoryColortemp1GEnter(void);
void RTDFactoryColortemp1GLeft(void);
void RTDFactoryColortemp1GRight(void);
void RTDFactoryColortemp1GExit(void);
//============= Colortemp 1 B=======================
void RTDFactoryColortemp1BEnter(void);
void RTDFactoryColortemp1BLeft(void);
void RTDFactoryColortemp1BRight(void);
void RTDFactoryColortemp1BExit(void);
//============= Colortemp 2 R=======================
void RTDFactoryColortemp2REnter(void);
void RTDFactoryColortemp2RLeft(void);
void RTDFactoryColortemp2RRight(void);
void RTDFactoryColortemp2RExit(void);
//============= Colortemp 2 G=======================
void RTDFactoryColortemp2GEnter(void);
void RTDFactoryColortemp2GLeft(void);
void RTDFactoryColortemp2GRight(void);
void RTDFactoryColortemp2GExit(void);
//============= Colortemp 2 B=======================
void RTDFactoryColortemp2BEnter(void);
void RTDFactoryColortemp2BLeft(void);
void RTDFactoryColortemp2BRight(void);
void RTDFactoryColortemp2BExit(void);
//============= Colortemp 3 R=======================
void RTDFactoryColortemp3REnter(void);
void RTDFactoryColortemp3RLeft(void);
void RTDFactoryColortemp3RRight(void);
void RTDFactoryColortemp3RExit(void);
//============= Colortemp 3 G=======================
void RTDFactoryColortemp3GEnter(void);
void RTDFactoryColortemp3GLeft(void);
void RTDFactoryColortemp3GRight(void);
void RTDFactoryColortemp3GExit(void);
//============= Colortemp 3 B=======================
void RTDFactoryColortemp3BEnter(void);
void RTDFactoryColortemp3BLeft(void);
void RTDFactoryColortemp3BRight(void);
void RTDFactoryColortemp3BExit(void);
//============= Colortemp 4 R=======================
void RTDFactoryColortemp4REnter(void);
void RTDFactoryColortemp4RLeft(void);
void RTDFactoryColortemp4RRight(void);
void RTDFactoryColortemp4RExit(void);
//============= Colortemp 4 G=======================
void RTDFactoryColortemp4GEnter(void);
void RTDFactoryColortemp4GLeft(void);
void RTDFactoryColortemp4GRight(void);
void RTDFactoryColortemp4GExit(void);
//============= Colortemp 4 B=======================
void RTDFactoryColortemp4BEnter(void);
void RTDFactoryColortemp4BLeft(void);
void RTDFactoryColortemp4BRight(void);
void RTDFactoryColortemp4BExit(void);
//============= Colortemp 5 R=======================
void RTDFactoryColortemp5REnter(void);
void RTDFactoryColortemp5RLeft(void);
void RTDFactoryColortemp5RRight(void);
void RTDFactoryColortemp5RExit(void);
//============= Colortemp 5 G=======================
void RTDFactoryColortemp5GEnter(void);
void RTDFactoryColortemp5GLeft(void);
void RTDFactoryColortemp5GRight(void);
void RTDFactoryColortemp5GExit(void);
//============= Colortemp 5 B=======================
void RTDFactoryColortemp5BEnter(void);
void RTDFactoryColortemp5BLeft(void);
void RTDFactoryColortemp5BRight(void);
void RTDFactoryColortemp5BExit(void);
//============= Colortemp 6 R=======================
void RTDFactoryColortemp6REnter(void);
void RTDFactoryColortemp6RLeft(void);
void RTDFactoryColortemp6RRight(void);
void RTDFactoryColortemp6RExit(void);
//============= Colortemp 6 G=======================
void RTDFactoryColortemp6GEnter(void);
void RTDFactoryColortemp6GLeft(void);
void RTDFactoryColortemp6GRight(void);
void RTDFactoryColortemp6GExit(void);
//============= Colortemp 6 B=======================
void RTDFactoryColortemp6BEnter(void);
void RTDFactoryColortemp6BLeft(void);
void RTDFactoryColortemp6BRight(void);
void RTDFactoryColortemp6BExit(void);
//============= Adc Gain R=======================
void RTDFactoryAdcGainREnter(void);
void RTDFactoryAdcGainRLeft(void);
void RTDFactoryAdcGainRRight(void);
void RTDFactoryAdcGainRExit(void);
//============= Adc Gain G=======================
void RTDFactoryAdcGainGEnter(void);
void RTDFactoryAdcGainGLeft(void);
void RTDFactoryAdcGainGRight(void);
void RTDFactoryAdcGainGExit(void);
//============= Adc Gain B=======================
void RTDFactoryAdcGainBEnter(void);
void RTDFactoryAdcGainBLeft(void);
void RTDFactoryAdcGainBRight(void);
void RTDFactoryAdcGainBExit(void);
//============= Adc Offset R=======================
void RTDFactoryAdcOffsetREnter(void);
void RTDFactoryAdcOffsetRLeft(void);
void RTDFactoryAdcOffsetRRight(void);
void RTDFactoryAdcOffsetRExit(void);
//============= Adc Offset G=======================
void RTDFactoryAdcOffsetGEnter(void);
void RTDFactoryAdcOffsetGLeft(void);
void RTDFactoryAdcOffsetGRight(void);
void RTDFactoryAdcOffsetGExit(void);
//============= Adc Offset B=======================
void RTDFactoryAdcOffsetBEnter(void);
void RTDFactoryAdcOffsetBLeft(void);
void RTDFactoryAdcOffsetBRight(void);
void RTDFactoryAdcOffsetBExit(void);
//============= Osd Page=======================
void RTDFactoryOsdPageEnter(void);
void RTDFactoryOsdPageLeft(void);
void RTDFactoryOsdPageRight(void);
void RTDFactoryOsdPageExit(void);
//============= Exit=======================
void RTDFactoryExitEnter(void);
void RTDFactoryExitLeft(void);
void RTDFactoryExitRight(void);
void RTDFactoryExitExit(void);
//============= Auto Color Type Select=======================
void RTDFactoryAutoColorTypeSelectEnter(void);
void RTDFactoryAutoColorTypeSelectLeft(void);
void RTDFactoryAutoColorTypeSelectRight(void);
void RTDFactoryAutoColorTypeSelectExit(void);
//============= Burnin On Off=======================
void RTDFactoryBurninOnOffEnter(void);
void RTDFactoryBurninOnOffLeft(void);
void RTDFactoryBurninOnOffRight(void);
void RTDFactoryBurninOnOffExit(void);
//============= Colortemp 1 R Adjust=======================
void RTDFactoryColortemp1RAdjustEnter(void);
void RTDFactoryColortemp1RAdjustLeft(void);
void RTDFactoryColortemp1RAdjustRight(void);
void RTDFactoryColortemp1RAdjustExit(void);
//============= Colortemp 1 G Adjust=======================
void RTDFactoryColortemp1GAdjustEnter(void);
void RTDFactoryColortemp1GAdjustLeft(void);
void RTDFactoryColortemp1GAdjustRight(void);
void RTDFactoryColortemp1GAdjustExit(void);
//============= Colortemp 1 B Adjust=======================
void RTDFactoryColortemp1BAdjustEnter(void);
void RTDFactoryColortemp1BAdjustLeft(void);
void RTDFactoryColortemp1BAdjustRight(void);
void RTDFactoryColortemp1BAdjustExit(void);
//============= Colortemp 2 R Adjust=======================
void RTDFactoryColortemp2RAdjustEnter(void);
void RTDFactoryColortemp2RAdjustLeft(void);
void RTDFactoryColortemp2RAdjustRight(void);
void RTDFactoryColortemp2RAdjustExit(void);
//============= Colortemp 2 G Adjust=======================
void RTDFactoryColortemp2GAdjustEnter(void);
void RTDFactoryColortemp2GAdjustLeft(void);
void RTDFactoryColortemp2GAdjustRight(void);
void RTDFactoryColortemp2GAdjustExit(void);
//============= Colortemp 2 B Adjust=======================
void RTDFactoryColortemp2BAdjustEnter(void);
void RTDFactoryColortemp2BAdjustLeft(void);
void RTDFactoryColortemp2BAdjustRight(void);
void RTDFactoryColortemp2BAdjustExit(void);
//============= Colortemp 3 R Adjust=======================
void RTDFactoryColortemp3RAdjustEnter(void);
void RTDFactoryColortemp3RAdjustLeft(void);
void RTDFactoryColortemp3RAdjustRight(void);
void RTDFactoryColortemp3RAdjustExit(void);
//============= Colortemp 3 G Adjust=======================
void RTDFactoryColortemp3GAdjustEnter(void);
void RTDFactoryColortemp3GAdjustLeft(void);
void RTDFactoryColortemp3GAdjustRight(void);
void RTDFactoryColortemp3GAdjustExit(void);
//============= Colortemp 3 B Adjust=======================
void RTDFactoryColortemp3BAdjustEnter(void);
void RTDFactoryColortemp3BAdjustLeft(void);
void RTDFactoryColortemp3BAdjustRight(void);
void RTDFactoryColortemp3BAdjustExit(void);
//============= Colortemp 4 R Adjust=======================
void RTDFactoryColortemp4RAdjustEnter(void);
void RTDFactoryColortemp4RAdjustLeft(void);
void RTDFactoryColortemp4RAdjustRight(void);
void RTDFactoryColortemp4RAdjustExit(void);
//============= Colortemp 4 G Adjust=======================
void RTDFactoryColortemp4GAdjustEnter(void);
void RTDFactoryColortemp4GAdjustLeft(void);
void RTDFactoryColortemp4GAdjustRight(void);
void RTDFactoryColortemp4GAdjustExit(void);
//============= Colortemp 4 B Adjust=======================
void RTDFactoryColortemp4BAdjustEnter(void);
void RTDFactoryColortemp4BAdjustLeft(void);
void RTDFactoryColortemp4BAdjustRight(void);
void RTDFactoryColortemp4BAdjustExit(void);
//============= Colortemp 5 R Adjust=======================
void RTDFactoryColortemp5RAdjustEnter(void);
void RTDFactoryColortemp5RAdjustLeft(void);
void RTDFactoryColortemp5RAdjustRight(void);
void RTDFactoryColortemp5RAdjustExit(void);
//============= Colortemp 5 G Adjust=======================
void RTDFactoryColortemp5GAdjustEnter(void);
void RTDFactoryColortemp5GAdjustLeft(void);
void RTDFactoryColortemp5GAdjustRight(void);
void RTDFactoryColortemp5GAdjustExit(void);
//============= Colortemp 5 B Adjust=======================
void RTDFactoryColortemp5BAdjustEnter(void);
void RTDFactoryColortemp5BAdjustLeft(void);
void RTDFactoryColortemp5BAdjustRight(void);
void RTDFactoryColortemp5BAdjustExit(void);
//============= Colortemp 6 R Adjust=======================
void RTDFactoryColortemp6RAdjustEnter(void);
void RTDFactoryColortemp6RAdjustLeft(void);
void RTDFactoryColortemp6RAdjustRight(void);
void RTDFactoryColortemp6RAdjustExit(void);
//============= Colortemp 6 G Adjust=======================
void RTDFactoryColortemp6GAdjustEnter(void);
void RTDFactoryColortemp6GAdjustLeft(void);
void RTDFactoryColortemp6GAdjustRight(void);
void RTDFactoryColortemp6GAdjustExit(void);
//============= Colortemp 6 B Adjust=======================
void RTDFactoryColortemp6BAdjustEnter(void);
void RTDFactoryColortemp6BAdjustLeft(void);
void RTDFactoryColortemp6BAdjustRight(void);
void RTDFactoryColortemp6BAdjustExit(void);
//============= Adc Gain R Adjust=======================
void RTDFactoryAdcGainRAdjustEnter(void);
void RTDFactoryAdcGainRAdjustLeft(void);
void RTDFactoryAdcGainRAdjustRight(void);
void RTDFactoryAdcGainRAdjustExit(void);
//============= Adc Gain G Adjust=======================
void RTDFactoryAdcGainGAdjustEnter(void);
void RTDFactoryAdcGainGAdjustLeft(void);
void RTDFactoryAdcGainGAdjustRight(void);
void RTDFactoryAdcGainGAdjustExit(void);
//============= Adc Gain B Adjust=======================
void RTDFactoryAdcGainBAdjustEnter(void);
void RTDFactoryAdcGainBAdjustLeft(void);
void RTDFactoryAdcGainBAdjustRight(void);
void RTDFactoryAdcGainBAdjustExit(void);
//============= Adc Offset R Adjust=======================
void RTDFactoryAdcOffsetRAdjustEnter(void);
void RTDFactoryAdcOffsetRAdjustLeft(void);
void RTDFactoryAdcOffsetRAdjustRight(void);
void RTDFactoryAdcOffsetRAdjustExit(void);
//============= Adc Offset G Adjust=======================
void RTDFactoryAdcOffsetGAdjustEnter(void);
void RTDFactoryAdcOffsetGAdjustLeft(void);
void RTDFactoryAdcOffsetGAdjustRight(void);
void RTDFactoryAdcOffsetGAdjustExit(void);
//============= Adc Offset B Adjust=======================
void RTDFactoryAdcOffsetBAdjustEnter(void);
void RTDFactoryAdcOffsetBAdjustLeft(void);
void RTDFactoryAdcOffsetBAdjustRight(void);
void RTDFactoryAdcOffsetBAdjustExit(void);
//============= Osd Page Adjust=======================
void RTDFactoryOsdPageAdjustEnter(void);
void RTDFactoryOsdPageAdjustLeft(void);
void RTDFactoryOsdPageAdjustRight(void);
void RTDFactoryOsdPageAdjustExit(void);
//============= Background =======================
void RTDFactoryBgEnter(void);
void RTDFactoryBgLeft(void);
void RTDFactoryBgRight(void);
void RTDFactoryBgExit(void);
//============= Background R=======================
void RTDFactoryBgREnter(void);
void RTDFactoryBgRLeft(void);
void RTDFactoryBgRRight(void);
void RTDFactoryBgRExit(void);
//============= Background G=======================
void RTDFactoryBgGEnter(void);
void RTDFactoryBgGLeft(void);
void RTDFactoryBgGRight(void);
void RTDFactoryBgGExit(void);
//============= Background B=======================
void RTDFactoryBgBEnter(void);
void RTDFactoryBgBLeft(void);
void RTDFactoryBgBRight(void);
void RTDFactoryBgBExit(void);
//============= SSC=======================
void RTDFactorySSCEnter(void);
void RTDFactorySSCLeft(void);
void RTDFactorySSCRight(void);
void RTDFactorySSCExit(void);
//============= LVDS=======================
void RTDFactoryLVDSClockEnter(void);
void RTDFactoryLVDSClockLeft(void);
void RTDFactoryLVDSClockRight(void);
void RTDFactoryLVDSClockExit(void);
//============= LVDS Data=======================
void RTDFactoryLVDSDataEnter(void);
void RTDFactoryLVDSDataLeft(void);
void RTDFactoryLVDSDataRight(void);
void RTDFactoryLVDSDataExit(void);
//============= Pattern =======================
void RTDFactoryPatternEnter(void);
void RTDFactoryPatternLeft(void);
void RTDFactoryPatternRight(void);
void RTDFactoryPatternExit(void);
//============= Hot Plug DP DC Off High=======================
void RTDFactoryHotPlugDPDCOffHighEnter(void);
void RTDFactoryHotPlugDPDCOffHighLeft(void);
void RTDFactoryHotPlugDPDCOffHighRight(void);
void RTDFactoryHotPlugDPDCOffHighExit(void);
//============= Hot Plug HDMI Support=======================
void RTDFactoryHotPlugHDMISupportEnter(void);
void RTDFactoryHotPlugHDMISupportLeft(void);
void RTDFactoryHotPlugHDMISupportRight(void);
void RTDFactoryHotPlugHDMISupportExit(void);
//============= Hot Plug HDMI Support Time=======================
void RTDFactoryHotPlugHDMISupportTimeEnter(void);
void RTDFactoryHotPlugHDMISupportTimeLeft(void);
void RTDFactoryHotPlugHDMISupportTimeRight(void);
void RTDFactoryHotPlugHDMISupportTimeExit(void);
//============= DP/HDMI FREESYNC=======================
void RTDFactoryDPFREESYNCEnter(void);
void RTDFactoryDPFREESYNCLeft(void);
void RTDFactoryDPFREESYNCRight(void);
void RTDFactoryDPFREESYNCExit(void);
void RTDFactoryHDMIFREESYNCEnter(void);
void RTDFactoryHDMIFREESYNCLeft(void);
void RTDFactoryHDMIFREESYNCRight(void);
void RTDFactoryHDMIFREESYNCExit(void);
//============= Osd Page 1=======================
void RTDFactoryOsdPage1Enter(void);
void RTDFactoryOsdPage1Left(void);
void RTDFactoryOsdPage1Right(void);
void RTDFactoryOsdPage1Exit(void);
//============= Exit 1=======================
void RTDFactoryExit1Enter(void);
void RTDFactoryExit1Left(void);
void RTDFactoryExit1Right(void);
void RTDFactoryExit1Exit(void);
//============= BG On Off=======================
void RTDFactoryBgOnOffEnter(void);
void RTDFactoryBgOnOffLeft(void);
void RTDFactoryBgOnOffRight(void);
void RTDFactoryBgOnOffExit(void);
//============= BG R Adjust=======================
void RTDFactoryBgRAdjustEnter(void);
void RTDFactoryBgRAdjustLeft(void);
void RTDFactoryBgRAdjustRight(void);
void RTDFactoryBgRAdjustExit(void);
//============= BG G Adjust=======================
void RTDFactoryBgGAdjustEnter(void);
void RTDFactoryBgGAdjustLeft(void);
void RTDFactoryBgGAdjustRight(void);
void RTDFactoryBgGAdjustExit(void);
//============= Adc Gain B Adjust=======================
void RTDFactoryBgBAdjustEnter(void);
void RTDFactoryBgBAdjustLeft(void);
void RTDFactoryBgBAdjustRight(void);
void RTDFactoryBgBAdjustExit(void);
//============= SSC Adjust=======================
void RTDFactorySSCAdjustEnter(void);
void RTDFactorySSCAdjustLeft(void);
void RTDFactorySSCAdjustRight(void);
void RTDFactorySSCAdjustExit(void);
//============= LVDS Clock Current Adjust=======================
void RTDFactoryLVDSClockCurrentAdjustEnter(void);
void RTDFactoryLVDSClockCurrentAdjustLeft(void);
void RTDFactoryLVDSClockCurrentAdjustRight(void);
void RTDFactoryLVDSClockCurrentAdjustExit(void);
//============= LVDS Data Current Adjust=======================
void RTDFactoryLVDSDataCurrentAdjustEnter(void);
void RTDFactoryLVDSDataCurrentAdjustLeft(void);
void RTDFactoryLVDSDataCurrentAdjustRight(void);
void RTDFactoryLVDSDataCurrentAdjustExit(void);
//============= Pattern Adjust=======================
void RTDFactoryPatternAdjustEnter(void);
void RTDFactoryPatternAdjustLeft(void);
void RTDFactoryPatternAdjustRight(void);
void RTDFactoryPatternAdjustExit(void);
//============= Hot Plug DP DC Off High Adjust=======================
void RTDFactoryHotPlugDPDCOffHighAdjustEnter(void);
void RTDFactoryHotPlugDPDCOffHighAdjustLeft(void);
void RTDFactoryHotPlugDPDCOffHighAdjustRight(void);
void RTDFactoryHotPlugDPDCOffHighAdjustExit(void);
//============= Hot Plug HDMI Support Adjus=======================
void RTDFactoryHotPlugHDMISupportAdjustEnter(void);
void RTDFactoryHotPlugHDMISupportAdjustLeft(void);
void RTDFactoryHotPlugHDMISupportAdjustRight(void);
void RTDFactoryHotPlugHDMISupportAdjustExit(void);
//============= Hot Plug HDMI Support Time Adjust=======================
void RTDFactoryHotPlugHDMISupportTimeAdjustEnter(void);
void RTDFactoryHotPlugHDMISupportTimeAdjustLeft(void);
void RTDFactoryHotPlugHDMISupportTimeAdjustRight(void);
void RTDFactoryHotPlugHDMISupportTimeAdjustExit(void);
//============= DP/HDMI FREESYNC=======================
void RTDFactoryDPFREESYNCAdjustEnter(void);
void RTDFactoryDPFREESYNCAdjustLeft(void);
void RTDFactoryDPFREESYNCAdjustRight(void);
void RTDFactoryDPFREESYNCAdjustExit(void);
void RTDFactoryHDMIFREESYNCAdjustEnter(void);
void RTDFactoryHDMIFREESYNCAdjustLeft(void);
void RTDFactoryHDMIFREESYNCAdjustRight(void);
void RTDFactoryHDMIFREESYNCAdjustExit(void);

//============= Osd Page 1 Adjust=======================
void RTDFactoryOsdPage1AdjustEnter(void);
void RTDFactoryOsdPage1AdjustLeft(void);
void RTDFactoryOsdPage1AdjustRight(void);
void RTDFactoryOsdPage1AdjustExit(void);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//----------------------------------------------------------------------------------------------------
// OSD Factory Operation Table
//----------------------------------------------------------------------------------------------------
code void (*OperationFactoryTable[][4])(void) =
{
    {RTDFactoryAutoColorEnter,                      RTDFactoryAutoColorLeft,                        RTDFactoryAutoColorRight,                       RTDFactoryAutoColorExit,},
    {RTDFactoryAutoColorTypeEnter,                  RTDFactoryAutoColorTypeLeft,                    RTDFactoryAutoColorTypeRight,                   RTDFactoryAutoColorTypeExit,},
    {RTDFactoryBurninEnter,                         RTDFactoryBurninLeft,                           RTDFactoryBurninRight,                          RTDFactoryBurninExit,},
    {RTDFactoryResetBurninTimeEnter,                RTDFactoryResetBurninTimeLeft,                  RTDFactoryResetBurninTimeRight,                 RTDFactoryResetBurninTimeExit,},
    {RTDFactoryResetPanelTimeEnter,                 RTDFactoryResetPanelTimeLeft,                   RTDFactoryResetPanelTimeRight,                  RTDFactoryResetPanelTimeExit,},
    {RTDFactoryColortemp1REnter,                    RTDFactoryColortemp1RLeft,                      RTDFactoryColortemp1RRight,                     RTDFactoryColortemp1RExit,},
    {RTDFactoryColortemp1GEnter,                    RTDFactoryColortemp1GLeft,                      RTDFactoryColortemp1GRight,                     RTDFactoryColortemp1GExit,},
    {RTDFactoryColortemp1BEnter,                    RTDFactoryColortemp1BLeft,                      RTDFactoryColortemp1BRight,                     RTDFactoryColortemp1BExit,},
    {RTDFactoryColortemp2REnter,                    RTDFactoryColortemp2RLeft,                      RTDFactoryColortemp2RRight,                     RTDFactoryColortemp2RExit,},
    {RTDFactoryColortemp2GEnter,                    RTDFactoryColortemp2GLeft,                      RTDFactoryColortemp2GRight,                     RTDFactoryColortemp2GExit,},
    {RTDFactoryColortemp2BEnter,                    RTDFactoryColortemp2BLeft,                      RTDFactoryColortemp2BRight,                     RTDFactoryColortemp2BExit,},
    {RTDFactoryColortemp3REnter,                    RTDFactoryColortemp3RLeft,                      RTDFactoryColortemp3RRight,                     RTDFactoryColortemp3RExit,},
    {RTDFactoryColortemp3GEnter,                    RTDFactoryColortemp3GLeft,                      RTDFactoryColortemp3GRight,                     RTDFactoryColortemp3GExit,},
    {RTDFactoryColortemp3BEnter,                    RTDFactoryColortemp3BLeft,                      RTDFactoryColortemp3BRight,                     RTDFactoryColortemp3BExit,},
    {RTDFactoryColortemp4REnter,                    RTDFactoryColortemp4RLeft,                      RTDFactoryColortemp4RRight,                     RTDFactoryColortemp4RExit,},
    {RTDFactoryColortemp4GEnter,                    RTDFactoryColortemp4GLeft,                      RTDFactoryColortemp4GRight,                     RTDFactoryColortemp4GExit,},
    {RTDFactoryColortemp4BEnter,                    RTDFactoryColortemp4BLeft,                      RTDFactoryColortemp4BRight,                     RTDFactoryColortemp4BExit,},
    {RTDFactoryColortemp5REnter,                    RTDFactoryColortemp5RLeft,                      RTDFactoryColortemp5RRight,                     RTDFactoryColortemp5RExit,},
    {RTDFactoryColortemp5GEnter,                    RTDFactoryColortemp5GLeft,                      RTDFactoryColortemp5GRight,                     RTDFactoryColortemp5GExit,},
    {RTDFactoryColortemp5BEnter,                    RTDFactoryColortemp5BLeft,                      RTDFactoryColortemp5BRight,                     RTDFactoryColortemp5BExit,},
    {RTDFactoryColortemp6REnter,                    RTDFactoryColortemp6RLeft,                      RTDFactoryColortemp6RRight,                     RTDFactoryColortemp6RExit,},
    {RTDFactoryColortemp6GEnter,                    RTDFactoryColortemp6GLeft,                      RTDFactoryColortemp6GRight,                     RTDFactoryColortemp6GExit,},
    {RTDFactoryColortemp6BEnter,                    RTDFactoryColortemp6BLeft,                      RTDFactoryColortemp6BRight,                     RTDFactoryColortemp6BExit,},
    {RTDFactoryAdcGainREnter,                       RTDFactoryAdcGainRLeft,                         RTDFactoryAdcGainRRight,                        RTDFactoryAdcGainRExit,},
    {RTDFactoryAdcGainGEnter,                       RTDFactoryAdcGainGLeft,                         RTDFactoryAdcGainGRight,                        RTDFactoryAdcGainGExit,},
    {RTDFactoryAdcGainBEnter,                       RTDFactoryAdcGainBLeft,                         RTDFactoryAdcGainBRight,                        RTDFactoryAdcGainBExit,},
    {RTDFactoryAdcOffsetREnter,                     RTDFactoryAdcOffsetRLeft,                       RTDFactoryAdcOffsetRRight,                      RTDFactoryAdcOffsetRExit,},
    {RTDFactoryAdcOffsetGEnter,                     RTDFactoryAdcOffsetGLeft,                       RTDFactoryAdcOffsetGRight,                      RTDFactoryAdcOffsetGExit,},
    {RTDFactoryAdcOffsetBEnter,                     RTDFactoryAdcOffsetBLeft,                       RTDFactoryAdcOffsetBRight,                      RTDFactoryAdcOffsetBExit,},
    {RTDFactoryOsdPageEnter,                        RTDFactoryOsdPageLeft,                          RTDFactoryOsdPageRight,                         RTDFactoryOsdPageExit,},
    {RTDFactoryExitEnter,                           RTDFactoryExitLeft,                             RTDFactoryExitRight,                            RTDFactoryExitExit,},

    {RTDFactoryAutoColorTypeSelectEnter,            RTDFactoryAutoColorTypeSelectLeft,              RTDFactoryAutoColorTypeSelectRight,             RTDFactoryAutoColorTypeSelectExit,},
    {RTDFactoryBurninOnOffEnter,                    RTDFactoryBurninOnOffLeft,                      RTDFactoryBurninOnOffRight,                     RTDFactoryBurninOnOffExit,},
    {RTDFactoryColortemp1RAdjustEnter,              RTDFactoryColortemp1RAdjustLeft,                RTDFactoryColortemp1RAdjustRight,               RTDFactoryColortemp1RAdjustExit,},
    {RTDFactoryColortemp1GAdjustEnter,              RTDFactoryColortemp1GAdjustLeft,                RTDFactoryColortemp1GAdjustRight,               RTDFactoryColortemp1GAdjustExit,},
    {RTDFactoryColortemp1BAdjustEnter,              RTDFactoryColortemp1BAdjustLeft,                RTDFactoryColortemp1BAdjustRight,               RTDFactoryColortemp1BAdjustExit,},
    {RTDFactoryColortemp2RAdjustEnter,              RTDFactoryColortemp2RAdjustLeft,                RTDFactoryColortemp2RAdjustRight,               RTDFactoryColortemp2RAdjustExit,},
    {RTDFactoryColortemp2GAdjustEnter,              RTDFactoryColortemp2GAdjustLeft,                RTDFactoryColortemp2GAdjustRight,               RTDFactoryColortemp2GAdjustExit,},
    {RTDFactoryColortemp2BAdjustEnter,              RTDFactoryColortemp2BAdjustLeft,                RTDFactoryColortemp2BAdjustRight,               RTDFactoryColortemp2BAdjustExit,},
    {RTDFactoryColortemp3RAdjustEnter,              RTDFactoryColortemp3RAdjustLeft,                RTDFactoryColortemp3RAdjustRight,               RTDFactoryColortemp3RAdjustExit,},
    {RTDFactoryColortemp3GAdjustEnter,              RTDFactoryColortemp3GAdjustLeft,                RTDFactoryColortemp3GAdjustRight,               RTDFactoryColortemp3GAdjustExit,},
    {RTDFactoryColortemp3BAdjustEnter,              RTDFactoryColortemp3BAdjustLeft,                RTDFactoryColortemp3BAdjustRight,               RTDFactoryColortemp3BAdjustExit,},
    {RTDFactoryColortemp4RAdjustEnter,              RTDFactoryColortemp4RAdjustLeft,                RTDFactoryColortemp4RAdjustRight,               RTDFactoryColortemp4RAdjustExit,},
    {RTDFactoryColortemp4GAdjustEnter,              RTDFactoryColortemp4GAdjustLeft,                RTDFactoryColortemp4GAdjustRight,               RTDFactoryColortemp4GAdjustExit,},
    {RTDFactoryColortemp4BAdjustEnter,              RTDFactoryColortemp4BAdjustLeft,                RTDFactoryColortemp4BAdjustRight,               RTDFactoryColortemp4BAdjustExit,},
    {RTDFactoryColortemp5RAdjustEnter,              RTDFactoryColortemp5RAdjustLeft,                RTDFactoryColortemp5RAdjustRight,               RTDFactoryColortemp5RAdjustExit,},
    {RTDFactoryColortemp5GAdjustEnter,              RTDFactoryColortemp5GAdjustLeft,                RTDFactoryColortemp5GAdjustRight,               RTDFactoryColortemp5GAdjustExit,},
    {RTDFactoryColortemp5BAdjustEnter,              RTDFactoryColortemp5BAdjustLeft,                RTDFactoryColortemp5BAdjustRight,               RTDFactoryColortemp5BAdjustExit,},
    {RTDFactoryColortemp6RAdjustEnter,              RTDFactoryColortemp6RAdjustLeft,                RTDFactoryColortemp6RAdjustRight,               RTDFactoryColortemp6RAdjustExit,},
    {RTDFactoryColortemp6GAdjustEnter,              RTDFactoryColortemp6GAdjustLeft,                RTDFactoryColortemp6GAdjustRight,               RTDFactoryColortemp6GAdjustExit,},
    {RTDFactoryColortemp6BAdjustEnter,              RTDFactoryColortemp6BAdjustLeft,                RTDFactoryColortemp6BAdjustRight,               RTDFactoryColortemp6BAdjustExit,},
    {RTDFactoryAdcGainRAdjustEnter,                 RTDFactoryAdcGainRAdjustLeft,                   RTDFactoryAdcGainRAdjustRight,                  RTDFactoryAdcGainRAdjustExit,},
    {RTDFactoryAdcGainGAdjustEnter,                 RTDFactoryAdcGainGAdjustLeft,                   RTDFactoryAdcGainGAdjustRight,                  RTDFactoryAdcGainGAdjustExit,},
    {RTDFactoryAdcGainBAdjustEnter,                 RTDFactoryAdcGainBAdjustLeft,                   RTDFactoryAdcGainBAdjustRight,                  RTDFactoryAdcGainBAdjustExit,},
    {RTDFactoryAdcOffsetRAdjustEnter,               RTDFactoryAdcOffsetRAdjustLeft,                 RTDFactoryAdcOffsetRAdjustRight,                RTDFactoryAdcOffsetRAdjustExit,},
    {RTDFactoryAdcOffsetGAdjustEnter,               RTDFactoryAdcOffsetGAdjustLeft,                 RTDFactoryAdcOffsetGAdjustRight,                RTDFactoryAdcOffsetGAdjustExit,},
    {RTDFactoryAdcOffsetBAdjustEnter,               RTDFactoryAdcOffsetBAdjustLeft,                 RTDFactoryAdcOffsetBAdjustRight,                RTDFactoryAdcOffsetBAdjustExit,},
    {RTDFactoryOsdPageAdjustEnter,                  RTDFactoryOsdPageAdjustLeft,                    RTDFactoryOsdPageAdjustRight,                   RTDFactoryOsdPageAdjustExit,},

    {RTDFactoryBgEnter,                             RTDFactoryBgLeft,                               RTDFactoryBgRight,                              RTDFactoryBgExit,},
    {RTDFactoryBgREnter,                            RTDFactoryBgRLeft,                              RTDFactoryBgRRight,                             RTDFactoryBgRExit,},
    {RTDFactoryBgGEnter,                            RTDFactoryBgGLeft,                              RTDFactoryBgGRight,                             RTDFactoryBgGExit,},
    {RTDFactoryBgBEnter,                            RTDFactoryBgBLeft,                              RTDFactoryBgBRight,                             RTDFactoryBgBExit,},
    {RTDFactorySSCEnter,                            RTDFactorySSCLeft,                              RTDFactorySSCRight,                             RTDFactorySSCExit,},
    {RTDFactoryLVDSClockEnter,                      RTDFactoryLVDSClockLeft,                        RTDFactoryLVDSClockRight,                       RTDFactoryLVDSClockExit,},
    {RTDFactoryLVDSDataEnter,                       RTDFactoryLVDSDataLeft,                         RTDFactoryLVDSDataRight,                        RTDFactoryLVDSDataExit,},
    {RTDFactoryPatternEnter,                        RTDFactoryPatternLeft,                          RTDFactoryPatternRight,                         RTDFactoryPatternExit,},

    {RTDFactoryHotPlugDPDCOffHighEnter,             RTDFactoryHotPlugDPDCOffHighLeft,               RTDFactoryHotPlugDPDCOffHighRight,              RTDFactoryHotPlugDPDCOffHighExit,},
    {RTDFactoryHotPlugHDMISupportEnter,             RTDFactoryHotPlugHDMISupportLeft,               RTDFactoryHotPlugHDMISupportRight,              RTDFactoryHotPlugHDMISupportExit,},
    {RTDFactoryHotPlugHDMISupportTimeEnter,         RTDFactoryHotPlugHDMISupportTimeLeft,           RTDFactoryHotPlugHDMISupportTimeRight,          RTDFactoryHotPlugHDMISupportTimeExit,},

    {RTDFactoryDPFREESYNCEnter,                     RTDFactoryDPFREESYNCLeft,                       RTDFactoryDPFREESYNCRight,                      RTDFactoryDPFREESYNCExit,},
    {RTDFactoryHDMIFREESYNCEnter,                   RTDFactoryHDMIFREESYNCLeft,                     RTDFactoryHDMIFREESYNCRight,                    RTDFactoryHDMIFREESYNCExit,},

    {RTDFactoryOsdPage1Enter,                       RTDFactoryOsdPage1Left,                         RTDFactoryOsdPage1Right,                        RTDFactoryOsdPage1Exit,},
    {RTDFactoryExit1Enter,                          RTDFactoryExit1Left,                            RTDFactoryExit1Right,                           RTDFactoryExit1Exit,},
    {RTDFactoryBgOnOffEnter,                        RTDFactoryBgOnOffLeft,                          RTDFactoryBgOnOffRight,                         RTDFactoryBgOnOffExit,},
    {RTDFactoryBgRAdjustEnter,                      RTDFactoryBgRAdjustLeft,                        RTDFactoryBgRAdjustRight,                       RTDFactoryBgRAdjustExit,},
    {RTDFactoryBgGAdjustEnter,                      RTDFactoryBgGAdjustLeft,                        RTDFactoryBgGAdjustRight,                       RTDFactoryBgGAdjustExit,},
    {RTDFactoryBgBAdjustEnter,                      RTDFactoryBgBAdjustLeft,                        RTDFactoryBgBAdjustRight,                       RTDFactoryBgBAdjustExit,},
    {RTDFactorySSCAdjustEnter,                      RTDFactorySSCAdjustLeft,                        RTDFactorySSCAdjustRight,                       RTDFactorySSCAdjustExit,},
    {RTDFactoryLVDSClockCurrentAdjustEnter,         RTDFactoryLVDSClockCurrentAdjustLeft,           RTDFactoryLVDSClockCurrentAdjustRight,          RTDFactoryLVDSClockCurrentAdjustExit,},
    {RTDFactoryLVDSDataCurrentAdjustEnter,          RTDFactoryLVDSDataCurrentAdjustLeft,            RTDFactoryLVDSDataCurrentAdjustRight,           RTDFactoryLVDSDataCurrentAdjustExit,},
    {RTDFactoryPatternAdjustEnter,                  RTDFactoryPatternAdjustLeft,                    RTDFactoryPatternAdjustRight,                   RTDFactoryPatternAdjustExit,},

    {RTDFactoryHotPlugDPDCOffHighAdjustEnter,       RTDFactoryHotPlugDPDCOffHighAdjustLeft,         RTDFactoryHotPlugDPDCOffHighAdjustRight,        RTDFactoryHotPlugDPDCOffHighAdjustExit,},
    {RTDFactoryHotPlugHDMISupportAdjustEnter,       RTDFactoryHotPlugHDMISupportAdjustLeft,         RTDFactoryHotPlugHDMISupportAdjustRight,        RTDFactoryHotPlugHDMISupportAdjustExit,},
    {RTDFactoryHotPlugHDMISupportTimeAdjustEnter,   RTDFactoryHotPlugHDMISupportTimeAdjustLeft,     RTDFactoryHotPlugHDMISupportTimeAdjustRight,    RTDFactoryHotPlugHDMISupportTimeAdjustExit,},

    {RTDFactoryDPFREESYNCAdjustEnter,               RTDFactoryDPFREESYNCAdjustLeft,                 RTDFactoryDPFREESYNCAdjustRight,                RTDFactoryDPFREESYNCAdjustExit,},
    {RTDFactoryHDMIFREESYNCAdjustEnter,             RTDFactoryHDMIFREESYNCAdjustLeft,               RTDFactoryHDMIFREESYNCAdjustRight,              RTDFactoryHDMIFREESYNCAdjustExit,},

    {RTDFactoryOsdPage1AdjustEnter,                 RTDFactoryOsdPage1AdjustLeft,                   RTDFactoryOsdPage1AdjustRight,                  RTDFactoryOsdPage1AdjustExit,},
};

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void RTDFactoryMenuOperation(void)
{
    if((GET_OSD_STATE() >= _MENU_FACTORY_AUTOCOLOR) &&
       (GET_OSD_STATE() < _MENU_FACTORY_OSD_END) &&
       (GET_KEYMESSAGE() < _KEY_AMOUNT))
    {
        (*OperationFactoryTable[GET_OSD_STATE() - _MENU_FACTORY_AUTOCOLOR][GET_KEYMESSAGE()])();
    }
}

//----------------------------------------------------------------------------------------------------
// OSD Factory
//----------------------------------------------------------------------------------------------------
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void RTDFactoryMainMenu(void)
{
    BYTE ucRowCount = 0;

    g_ucFontPointer0 = _FACTORY_PAGE_0_START;
    g_ucFontPointer1 = _FACTORY_PAGE_1_START;
    g_ucFactoryPage = 0;

    RTDFactoryOsdFuncDisableOsd();
    SET_OSD_STATE(_MENU_FACTORY_EXIT);
    SET_OSD_IN_FACTORY_MENU_STATUS(_TRUE);
    RTDFactoryOsdFuncApplyMap(WIDTH(_FACTORY_OSD_COL), HEIGHT(_FACTORY_OSD_ROW), COLOR(_CP_WHITE, _CP_BG));
//        RTDFactoryOsdLoadHardwareVLCFont(tFONT_FACTORY_GLOBAL,_1BIT_FONT_START_ADDRESS,g_usFontTableStart,GET_OSD_ROTATE_STATUS());
//        RTDFactoryOsdLoadHardwareVLCFont(tFONT_FACTORY_GLOBAL, 0x00, g_usFontTableStart, GET_OSD_ROTATE_STATUS());
    ScalerOsdHardwareVLC(tFONT_FACTORY_GLOBAL, VLC_TABLE_SIZE(tFONT_FACTORY_GLOBAL), GET_CURRENT_BANK_NUMBER(), 0x00, g_usFontTableStart, _OSD_ROTATE_DEGREE_0);

    RTDFactoryOsdFuncClearOsdFont(0, 0, _FACTORY_OSD_COL, _FACTORY_OSD_ROW, _);
/*
    for(ucRowCount = 0; ucRowCount < 20; ucRowCount++)
    {
        RTDFactoryOsdFuncPutStringProp(_FACTORY_PAGE_ROW_COL_TABLE[ucRowCount][0], _FACTORY_PAGE_ROW_COL_TABLE[ucRowCount][1], _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[ucRowCount], _ENGLISH);
    }
*/

    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_MODEL_NAME_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[0], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_MODEL_NAME_ROW), COL(_FACTORY_FUNCTION_COL + 11), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[1], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_MODEL_NAME_ROW), COL(_FACTORY_FUNCTION_COL + 20), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[2], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_AUTOCOLOR_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[3], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_AUTOCOLOR_TYPE_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[20], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_BURNIN_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[4], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_RESET_BURNIN_TIME_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[5], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_BURNIN_TIME_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[6], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_RESET_PANEL_TIME_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[7], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_PANEL_TIME_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[8], _ENGLISH);

    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_COLORTEMP_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[9], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_COLORTEMP1_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[10], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_COLORTEMP2_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[11], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_COLORTEMP3_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[12], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_COLORTEMP4_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[13], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_COLORTEMP5_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[14], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_COLORTEMP6_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[15], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_ADC_GAIN_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[16], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_ADC_OFFSET_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[17], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_OSD_PAGE_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[18], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_EXIT_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_TABLE[19], _ENGLISH);

    for(ucRowCount = 0; ucRowCount < 8; ucRowCount++)
    {
        RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_COLORTEMP1_ROW + ucRowCount), COL(_FACTORY_R_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_RGB_TABLE[0], _ENGLISH);
        RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_COLORTEMP1_ROW + ucRowCount), COL(_FACTORY_G_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_RGB_TABLE[1], _ENGLISH);
        RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_COLORTEMP1_ROW + ucRowCount), COL(_FACTORY_B_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_RGB_TABLE[2], _ENGLISH);
    }

    g_usBackupValue = GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION());
    for(ucRowCount = 0; ucRowCount <= _CT_COLORTEMP_AMOUNT; ucRowCount++)
    {
        SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), ucRowCount);
        RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_COLORTEMP1_ROW + ucRowCount), COL(_FACTORY_R_NUMBER_COL), (g_stColorProcData.usColorTempR >> 4), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_COLORTEMP1_R + ucRowCount * 3);
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_COLORTEMP1_ROW + ucRowCount), COL(_FACTORY_G_NUMBER_COL), (g_stColorProcData.usColorTempG >> 4), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_COLORTEMP1_G + ucRowCount * 3);
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_COLORTEMP1_ROW + ucRowCount), COL(_FACTORY_B_NUMBER_COL), (g_stColorProcData.usColorTempB >> 4), (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_COLORTEMP1_B + ucRowCount * 3);
    }
    SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), g_usBackupValue);
    RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());

#if(_VGA_SUPPORT == _ON)
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_GAIN_ROW), COL(_FACTORY_R_NUMBER_COL), g_stAdcData.pucAdcGainMSB[_AUTO_RED_CHANNEL], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_GAIN_R);
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_GAIN_ROW), COL(_FACTORY_G_NUMBER_COL), g_stAdcData.pucAdcGainMSB[_AUTO_GREEN_CHANNEL], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_GAIN_G);
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_GAIN_ROW), COL(_FACTORY_B_NUMBER_COL), g_stAdcData.pucAdcGainMSB[_AUTO_BLUE_CHANNEL], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_GAIN_B);

    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_OFFSET_ROW), COL(_FACTORY_R_NUMBER_COL), g_stAdcData.pucAdcOffsetMSB[_AUTO_RED_CHANNEL], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_OFFSET_R);
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_OFFSET_ROW), COL(_FACTORY_G_NUMBER_COL), g_stAdcData.pucAdcOffsetMSB[_AUTO_GREEN_CHANNEL], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_OFFSET_G);
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_OFFSET_ROW), COL(_FACTORY_B_NUMBER_COL), g_stAdcData.pucAdcOffsetMSB[_AUTO_BLUE_CHANNEL], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_OFFSET_B);
#else
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_GAIN_ROW), COL(_FACTORY_R_NUMBER_COL), 128, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_GAIN_R);
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_GAIN_ROW), COL(_FACTORY_G_NUMBER_COL), 128, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_GAIN_G);
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_GAIN_ROW), COL(_FACTORY_B_NUMBER_COL), 128, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_GAIN_B);

    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_OFFSET_ROW), COL(_FACTORY_R_NUMBER_COL), 128, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_OFFSET_R);
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_OFFSET_ROW), COL(_FACTORY_G_NUMBER_COL), 128, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_OFFSET_G);
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_OFFSET_ROW), COL(_FACTORY_B_NUMBER_COL), 128, (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_OFFSET_B);
#endif

    // Auto color pass or fail
    // RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_AUTOCOLOR_ROW), COL(_FACTORY_ON_OFF_COL), _PFONT_FACTORY_AUTO_COLOR, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PASS_FAIL_TABLE[0], _ENGLISH);

    // Burnin on or off
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_BURNIN_ROW), COL(_FACTORY_ON_OFF_COL), _PFONT_FACTORY_BURNIN, tFONT_FACTORY_EUROPE, tOSD_FACTORY_ON_OFF_TABLE[0], _ENGLISH);

    // Panel/Burnin Time hour and min.
    for(ucRowCount = 0; ucRowCount < 2; ucRowCount++)
    {
        RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_BURNIN_TIME_ROW + ucRowCount * 2), COL(_FACTORY_TIME_HOUR_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_HOUR_MIN_TABLE[0], _ENGLISH);
        RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_BURNIN_TIME_ROW + ucRowCount * 2), COL(_FACTORY_TIME_MIN_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_HOUR_MIN_TABLE[1], _ENGLISH);
    }

#if(_ADC_SELF_CALIBRATION == _OFF)
    SET_OSD_FACTORY_AUTO_COLOR_TYPE(_AUTO_COLOR_TYPE_EXTERNAL);
#endif

    // Auto color type
    g_ucAutoColotTypeFontPointer = g_ucFontPointer0;
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_AUTOCOLOR_TYPE_ROW), COL(_FACTORY_ON_OFF_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_AUTO_COLOR_TYPE_TABLE[GET_OSD_FACTORY_AUTO_COLOR_TYPE()], _ENGLISH);

    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_BURNIN_TIME_ROW), COL(_FACTORY_BURNIN_TIME_HOUR_NUMBER_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_5), _PFONT_FACTORY_BURNIN_TIME_HOUR);
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_BURNIN_TIME_ROW), COL(_FACTORY_BURNIN_TIME_MIN_NUMBER_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_BURNIN_TIME_MIN);
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_PANEL_TIME_ROW), COL(_FACTORY_PANEL_TIME_HOUR_NUMBER_COL), GET_PANEL_TIME_HOUR(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_5), _PFONT_FACTORY_PANEL_TIME_HOUR);
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_PANEL_TIME_ROW), COL(_FACTORY_PANEL_TIME_MIN_NUMBER_COL), GET_PANEL_TIME_MIN(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_PANEL_TIME_MIN);
    // OSD Page value
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_OSD_PAGE_ROW), COL(_FACTORY_OSD_PAGE_NUMBER_COL), g_ucFactoryPage, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_2), _PFONT_FACTORY_OSD_PAGE);

    RTDFactoryOsdFuncDrawWindow(tOSD_FACTORY_WIN0, 0, 0, _FACTORY_OSD_WINDOW_SIZE_X, _FACTORY_OSD_WINDOW_SIZE_Y, _CP_BLACK);
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_EXIT);

#if(_FACTORY_ONE_PIECE_MARK_SUPPORT == _ON)
    RTDFactoryOnePieceMark();
#endif

    RTDFactoryOsdFuncSetPosition(_FACTORY_OSD, _FACTORY_OSD_H_POS_MIN, _FACTORY_OSD_V_POS_MIN);
    RTDFactoryOsdFuncEnableOsd();
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void RTDFactoryMainMenu1(void)
{
    // BYTE ucRowCount = 0;

    g_ucFontPointer0 = _FACTORY_PAGE_0_START;
    g_ucFontPointer1 = _FACTORY_PAGE_1_START;

    RTDFactoryOsdFuncDisableOsd();
    SET_OSD_STATE(_MENU_FACTORY_EXIT1);
    SET_OSD_IN_FACTORY_MENU_STATUS(_TRUE);
    RTDFactoryOsdFuncApplyMap(WIDTH(_FACTORY_OSD_COL), HEIGHT(_FACTORY_OSD_ROW), COLOR(_CP_WHITE, _CP_BG));
//        RTDFactoryOsdLoadHardwareVLCFont(tFONT_FACTORY_GLOBAL,_1BIT_FONT_START_ADDRESS,g_usFontTableStart,GET_OSD_ROTATE_STATUS());
//        RTDFactoryOsdLoadHardwareVLCFont(tFONT_FACTORY_GLOBAL, 0x00, g_usFontTableStart, GET_OSD_ROTATE_STATUS());
    ScalerOsdHardwareVLC(tFONT_FACTORY_GLOBAL, VLC_TABLE_SIZE(tFONT_FACTORY_GLOBAL), GET_CURRENT_BANK_NUMBER(), 0x00, g_usFontTableStart, _OSD_ROTATE_DEGREE_0);

    RTDFactoryOsdFuncClearOsdFont(0, 0, _FACTORY_OSD_COL, _FACTORY_OSD_ROW, _);

    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_BG_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_1_TABLE[0], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_BG_COLOR_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_1_TABLE[1], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_SSC_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_1_TABLE[2], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_DRIVING_CONTROL_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_1_TABLE[3], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_LVDS_CLOCK_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_1_TABLE[4], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_LVDS_DATA_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_1_TABLE[5], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_IPG_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_1_TABLE[6], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_PATTERN_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_1_TABLE[7], _ENGLISH);

    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_HOT_PLUG_OPTION_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_1_TABLE[8], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_HOT_PLUG_DP_DC_OFF_HIGH_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_1_TABLE[9], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_HOT_PLUG_HDMI_SUPPORT_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_1_TABLE[10], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_HOT_PLUG_HDMI_SUPPORT_TIME_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_1_TABLE[11], _ENGLISH);

    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_DP_FREESYNC_ON_OFF_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_1_TABLE[14], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_HDMI_FREESYNC_ON_OFF_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_1_TABLE[15], _ENGLISH);

    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_OSD_PAGE_1_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_1_TABLE[12], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_EXIT_1_ROW), COL(_FACTORY_FUNCTION_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PAGE_1_TABLE[13], _ENGLISH);

    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_BG_COLOR_ROW), COL(_FACTORY_R_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_RGB_TABLE[0], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_BG_COLOR_ROW), COL(_FACTORY_G_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_RGB_TABLE[1], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_BG_COLOR_ROW), COL(_FACTORY_B_COL), _PFONT_FACTORY_PAGE_0, tFONT_FACTORY_EUROPE, tOSD_FACTORY_RGB_TABLE[2], _ENGLISH);

    // Background on/off value
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_BG_ROW), COL(_FACTORY_ON_OFF_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_BACKGROUND_ON_OFF);

    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_BG_ROW), COL(_FACTORY_ON_OFF_COL), _PFONT_FACTORY_BACKGROUND_ON_OFF, tFONT_FACTORY_EUROPE, tOSD_FACTORY_ON_OFF_TABLE[0], _ENGLISH);

    // Background color R/G/B value
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_BG_COLOR_ROW), COL(_FACTORY_R_NUMBER_COL), g_ucBgColorR, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_BACKGROUND_COLOR_R);
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_BG_COLOR_ROW), COL(_FACTORY_G_NUMBER_COL), g_ucBgColorG, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_BACKGROUND_COLOR_G);
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_BG_COLOR_ROW), COL(_FACTORY_B_NUMBER_COL), g_ucBgColorB, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_BACKGROUND_COLOR_B);

    // SSC value
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_SSC_ROW), COL(_FACTORY_SSC_NUMBER_COL), g_ucFactoryPage, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_2), _PFONT_FACTORY_SSC);

    // LVDS value
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_LVDS_CLOCK_ROW), COL(_FACTORY_LVDS_NUMBER_COL), g_ucFactoryPage, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_2), _PFONT_FACTORY_LVDS_CLOCK);
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_LVDS_DATA_ROW), COL(_FACTORY_LVDS_NUMBER_COL), g_ucFactoryPage, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_2), _PFONT_FACTORY_LVDS_DATA);

    // Pattern value
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_PATTERN_ROW), COL(_FACTORY_PATTERN_NUMBER_COL), g_ucFactoryPage, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_PATTERN);

    // Hot Plug Option
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_HOT_PLUG_DP_DC_OFF_HIGH_ROW), COL(_FACTORY_HOT_PLUG_OPTION_VALUE_COL), _PFONT_FACTORY_HOT_PLUG_DP_DC_OFF_HIGH, tFONT_FACTORY_EUROPE, tOSD_FACTORY_ON_OFF_TABLE[UserCommonNVRamGetSystemData(_DP_HOT_PLUG_DC_OFF_HIGH)], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_HOT_PLUG_HDMI_SUPPORT_ROW), COL(_FACTORY_HOT_PLUG_OPTION_VALUE_COL), _PFONT_FACTORY_HOT_PLUG_HDMI_SUPPORT, tFONT_FACTORY_EUROPE, tOSD_FACTORY_ON_OFF_TABLE[UserCommonNVRamGetSystemData(_HDMI_HOT_PLUG_SUPPORT)], _ENGLISH);
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_HOT_PLUG_HDMI_SUPPORT_TIME_ROW), COL(_FACTORY_HOT_PLUG_OPTION_VALUE_COL), UserCommonNVRamGetSystemData(_HDMI_HOT_PLUG_SUPPORT_TIME), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_HOT_PLUG_HDMI_TIME);

    // FREESYNC function
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_DP_FREESYNC_ON_OFF_ROW), COL(_FACTORY_ON_OFF_COL), _PFONT_FACTORY_DP_FREESYNC_ON_OFF, tFONT_FACTORY_EUROPE, tOSD_FACTORY_ON_OFF_TABLE[GET_OSD_FREE_SYNC_STATUS()], _ENGLISH);
    RTDFactoryOsdFuncPutStringProp(ROW(_FACTORY_HDMI_FREESYNC_ON_OFF_ROW), COL(_FACTORY_ON_OFF_COL), _PFONT_FACTORY_HDMI_FREESYNC_ON_OFF, tFONT_FACTORY_EUROPE, tOSD_FACTORY_ON_OFF_TABLE[GET_OSD_FREE_SYNC_STATUS()], _ENGLISH);

    // OSD Page value
    RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_OSD_PAGE_ROW), COL(_FACTORY_OSD_PAGE_NUMBER_COL), g_ucFactoryPage, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_2), _PFONT_FACTORY_OSD_PAGE);

    RTDFactoryOsdFuncDrawWindow(tOSD_FACTORY_WIN0, 0, 0, _FACTORY_OSD_WINDOW_SIZE_X, _FACTORY_OSD_WINDOW_SIZE_Y, _CP_BLACK);
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_EXIT1);
    RTDFactoryOsdFuncSetPosition(_FACTORY_OSD, _FACTORY_OSD_H_POS_MIN, _FACTORY_OSD_V_POS_MIN);
    RTDFactoryOsdFuncEnableOsd();
}

//----------------------------------------------------------------------------------------------------
// OSD Factory Operation
//----------------------------------------------------------------------------------------------------
//============= Auto Color =======================
void RTDFactoryAutoColorEnter(void)
{
#if(_VGA_SUPPORT == _ON)
    BYTE ucTemp = 0;
    if((SysVgaGetRegion() != _DISPLAY_RGN_NONE) && (SysRegionGetDisplayState(SysVgaGetRegion()) == _DISPLAY_STATE_ACTIVE))
    {
        if(GET_OSD_FACTORY_AUTO_COLOR_TYPE() == _AUTO_COLOR_TYPE_INTERNAL)
        {
            RTDFactoryOsdFuncDisableOsd();
            ucTemp = _AUTO_CALIBRATE_RGB;
        }
        else
        {
            ucTemp = _AUTO_TUNE_RGB;
        }

        if(ScalerAutoDoWhiteBalance(ucTemp) == _AUTO_SUCCESS)
        {
            ScalerAutoGetAutoColorResult(&g_stAdcData);
            RTDFactoryOsdFuncChangeColor1Bit(_FACTORY_AUTOCOLOR_ROW, _FACTORY_ON_OFF_COL, WIDTH(6), 1, COLOR(_CP_BG, _CP_BG));
            RTDFactoryOsdFuncPutStringProp(_FACTORY_AUTOCOLOR_ROW, _FACTORY_ON_OFF_COL, _PFONT_FACTORY_AUTO_COLOR, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PASS_FAIL_TABLE[1], _ENGLISH);
            RTDFactoryOsdFuncChangeColor1Bit(_FACTORY_AUTOCOLOR_ROW, _FACTORY_ON_OFF_COL, WIDTH(6), 1, COLOR(_CP_WHITE, _CP_BG));
            UserCommonNVRamSaveADCSetting(_COLOR_SPACE_RGB);
        }
        else
        {
            RTDFactoryOsdFuncChangeColor1Bit(_FACTORY_AUTOCOLOR_ROW, _FACTORY_ON_OFF_COL, WIDTH(6), 1, COLOR(_CP_BG, _CP_BG));
            RTDFactoryOsdFuncPutStringProp(_FACTORY_AUTOCOLOR_ROW, _FACTORY_ON_OFF_COL, _PFONT_FACTORY_AUTO_COLOR, tFONT_FACTORY_EUROPE, tOSD_FACTORY_PASS_FAIL_TABLE[0], _ENGLISH);
            RTDFactoryOsdFuncChangeColor1Bit(_FACTORY_AUTOCOLOR_ROW, _FACTORY_ON_OFF_COL, WIDTH(6), 1, COLOR(_CP_WHITE, _CP_BG));
            UserCommonNVRamRestoreADCSetting();
        }
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_GAIN_ROW), COL(_FACTORY_R_NUMBER_COL), g_stAdcData.pucAdcGainMSB[_AUTO_RED_CHANNEL], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_GAIN_R);
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_GAIN_ROW), COL(_FACTORY_G_NUMBER_COL), g_stAdcData.pucAdcGainMSB[_AUTO_GREEN_CHANNEL], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_GAIN_G);
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_GAIN_ROW), COL(_FACTORY_B_NUMBER_COL), g_stAdcData.pucAdcGainMSB[_AUTO_BLUE_CHANNEL], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_GAIN_B);

        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_OFFSET_ROW), COL(_FACTORY_R_NUMBER_COL), g_stAdcData.pucAdcOffsetMSB[_AUTO_RED_CHANNEL], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_OFFSET_R);
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_OFFSET_ROW), COL(_FACTORY_G_NUMBER_COL), g_stAdcData.pucAdcOffsetMSB[_AUTO_GREEN_CHANNEL], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_OFFSET_G);
        RTDFactoryOsdFuncShowNumber(ROW(_FACTORY_ADC_OFFSET_ROW), COL(_FACTORY_B_NUMBER_COL), g_stAdcData.pucAdcOffsetMSB[_AUTO_BLUE_CHANNEL], (_ALIGN_RIGHT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_FACTORY_ADC_OFFSET_B);
    }
#endif // End of #if(_VGA_SUPPORT == _ON)
}

void RTDFactoryAutoColorLeft(void)
{
#if(_ADC_SELF_CALIBRATION == _ON)
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_AUTOCOLOR_TYPE);
#else
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BURNIN);
#endif // End of #if(_ADC_SELF_CALIBRATION == _ON)
}

void RTDFactoryAutoColorRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_EXIT);
}

void RTDFactoryAutoColorExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Auto Color Type =======================
void RTDFactoryAutoColorTypeEnter(void)
{
    g_usAdjustValue = GET_OSD_FACTORY_AUTO_COLOR_TYPE();
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_AUTO_COLOR_TYPE);
}

void RTDFactoryAutoColorTypeLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BURNIN);
}

void RTDFactoryAutoColorTypeRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_AUTOCOLOR);
}

void RTDFactoryAutoColorTypeExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Burnin =======================
void RTDFactoryBurninEnter(void)
{
    g_usAdjustValue = 0;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BURNIN_ON_OFF);
}

void RTDFactoryBurninLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_RESET_BURNIN_TIME);
}

void RTDFactoryBurninRight(void)
{
#if(_ADC_SELF_CALIBRATION == _ON)
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_AUTOCOLOR_TYPE);

#else
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_AUTOCOLOR);

#endif // End of #if(_ADC_SELF_CALIBRATION == _ON)
}

void RTDFactoryBurninExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Reset Burnin Time =======================
void RTDFactoryResetBurninTimeEnter(void)
{
}

void RTDFactoryResetBurninTimeLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_RESET_PANEL_TIME);
}

void RTDFactoryResetBurninTimeRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BURNIN);
}

void RTDFactoryResetBurninTimeExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Reset Panel Time =======================
void RTDFactoryResetPanelTimeEnter(void)
{
}

void RTDFactoryResetPanelTimeLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT1_RED);
    RTDFactoryOsdChangColorTemp(_CT_9300);
}

void RTDFactoryResetPanelTimeRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_RESET_BURNIN_TIME);
}

void RTDFactoryResetPanelTimeExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Colortemp 1 R=======================
void RTDFactoryColortemp1REnter(void)
{
    g_usBackupValue = g_stColorProcData.usColorTempR;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT1_RED_ADJ);
}

void RTDFactoryColortemp1RLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT1_GREEN);
}

void RTDFactoryColortemp1RRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_RESET_PANEL_TIME);
}

void RTDFactoryColortemp1RExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Colortemp 1 G=======================
void RTDFactoryColortemp1GEnter(void)
{
    g_usBackupValue = g_stColorProcData.usColorTempG;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT1_GREEN_ADJ);
}

void RTDFactoryColortemp1GLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT1_BLUE);
}

void RTDFactoryColortemp1GRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT1_RED);
}

void RTDFactoryColortemp1GExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Colortemp 1 B=======================
void RTDFactoryColortemp1BEnter(void)
{
    g_usBackupValue = g_stColorProcData.usColorTempB;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT1_BLUE_ADJ);
}

void RTDFactoryColortemp1BLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT2_RED);
    RTDFactoryOsdChangColorTemp(_CT_7500);
}

void RTDFactoryColortemp1BRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT1_GREEN);
}

void RTDFactoryColortemp1BExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Colortemp 2 R=======================
void RTDFactoryColortemp2REnter(void)
{
    g_usBackupValue = g_stColorProcData.usColorTempR;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT2_RED_ADJ);
}

void RTDFactoryColortemp2RLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT2_GREEN);
}

void RTDFactoryColortemp2RRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT1_BLUE);
    RTDFactoryOsdChangColorTemp(_CT_9300);
}

void RTDFactoryColortemp2RExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Colortemp 2 G=======================
void RTDFactoryColortemp2GEnter(void)
{
    g_usBackupValue = g_stColorProcData.usColorTempG;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT2_GREEN_ADJ);
}

void RTDFactoryColortemp2GLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT2_BLUE);
}

void RTDFactoryColortemp2GRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT2_RED);
}

void RTDFactoryColortemp2GExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Colortemp 2 B=======================
void RTDFactoryColortemp2BEnter(void)
{
    g_usBackupValue = g_stColorProcData.usColorTempB;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT2_BLUE_ADJ);
}

void RTDFactoryColortemp2BLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT3_RED);
    RTDFactoryOsdChangColorTemp(_CT_6500);
}

void RTDFactoryColortemp2BRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT2_GREEN);
}

void RTDFactoryColortemp2BExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Colortemp 3 R=======================
void RTDFactoryColortemp3REnter(void)
{
    g_usBackupValue = g_stColorProcData.usColorTempR;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT3_RED_ADJ);
}

void RTDFactoryColortemp3RLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT3_GREEN);
}

void RTDFactoryColortemp3RRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT2_BLUE);
    RTDFactoryOsdChangColorTemp(_CT_7500);
}

void RTDFactoryColortemp3RExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Colortemp 3 G=======================
void RTDFactoryColortemp3GEnter(void)
{
    g_usBackupValue = g_stColorProcData.usColorTempG;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT3_GREEN_ADJ);
}

void RTDFactoryColortemp3GLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT3_BLUE);
}

void RTDFactoryColortemp3GRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT3_RED);
}

void RTDFactoryColortemp3GExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Colortemp 3 B=======================
void RTDFactoryColortemp3BEnter(void)
{
    g_usBackupValue = g_stColorProcData.usColorTempB;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT3_BLUE_ADJ);
}

void RTDFactoryColortemp3BLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT4_RED);
    RTDFactoryOsdChangColorTemp(_CT_5800);
}

void RTDFactoryColortemp3BRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT3_GREEN);
}

void RTDFactoryColortemp3BExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Colortemp 4 R=======================
void RTDFactoryColortemp4REnter(void)
{
    g_usBackupValue = g_stColorProcData.usColorTempR;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT4_RED_ADJ);
}

void RTDFactoryColortemp4RLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT4_GREEN);
}

void RTDFactoryColortemp4RRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT3_BLUE);
    RTDFactoryOsdChangColorTemp(_CT_6500);
}

void RTDFactoryColortemp4RExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Colortemp 4 G=======================
void RTDFactoryColortemp4GEnter(void)
{
    g_usBackupValue = g_stColorProcData.usColorTempG;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT4_GREEN_ADJ);
}

void RTDFactoryColortemp4GLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT4_BLUE);
}

void RTDFactoryColortemp4GRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT4_RED);
}

void RTDFactoryColortemp4GExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Colortemp 4 B=======================
void RTDFactoryColortemp4BEnter(void)
{
    g_usBackupValue = g_stColorProcData.usColorTempB;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT4_BLUE_ADJ);
}

void RTDFactoryColortemp4BLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT5_RED);
    RTDFactoryOsdChangColorTemp(_CT_SRGB);
}

void RTDFactoryColortemp4BRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT4_GREEN);
}

void RTDFactoryColortemp4BExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Colortemp 5 R=======================
void RTDFactoryColortemp5REnter(void)
{
    g_usBackupValue = g_stColorProcData.usColorTempR;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT5_RED_ADJ);
}

void RTDFactoryColortemp5RLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT5_GREEN);
}

void RTDFactoryColortemp5RRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT4_BLUE);
    RTDFactoryOsdChangColorTemp(_CT_5800);
}

void RTDFactoryColortemp5RExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Colortemp 5 G=======================
void RTDFactoryColortemp5GEnter(void)
{
    g_usBackupValue = g_stColorProcData.usColorTempG;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT5_GREEN_ADJ);
}

void RTDFactoryColortemp5GLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT5_BLUE);
}

void RTDFactoryColortemp5GRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT5_RED);
}

void RTDFactoryColortemp5GExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Colortemp 5 B=======================
void RTDFactoryColortemp5BEnter(void)
{
    g_usBackupValue = g_stColorProcData.usColorTempB;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT5_BLUE_ADJ);
}

void RTDFactoryColortemp5BLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT6_RED);
    RTDFactoryOsdChangColorTemp(_CT_USER);
}

void RTDFactoryColortemp5BRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT5_GREEN);
}

void RTDFactoryColortemp5BExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Colortemp 6 R=======================
void RTDFactoryColortemp6REnter(void)
{
    g_usBackupValue = g_stColorProcData.usColorTempR;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT6_RED_ADJ);
}

void RTDFactoryColortemp6RLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT6_GREEN);
}

void RTDFactoryColortemp6RRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT5_BLUE);
    RTDFactoryOsdChangColorTemp(_CT_SRGB);
}

void RTDFactoryColortemp6RExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Colortemp 6 G=======================
void RTDFactoryColortemp6GEnter(void)
{
    g_usBackupValue = g_stColorProcData.usColorTempG;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT6_GREEN_ADJ);
}

void RTDFactoryColortemp6GLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT6_BLUE);
}

void RTDFactoryColortemp6GRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT6_RED);
}

void RTDFactoryColortemp6GExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Colortemp 6 B=======================
void RTDFactoryColortemp6BEnter(void)
{
    g_usBackupValue = g_stColorProcData.usColorTempB;
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT6_BLUE_ADJ);
}

void RTDFactoryColortemp6BLeft(void)
{
#if(_VGA_SUPPORT == _ON)
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_GAIN_RED);
    RTDFactoryOsdChangColorTemp(_CT_9300);
#else
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OSD_PAGE);
#endif
}

void RTDFactoryColortemp6BRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT6_GREEN);
}

void RTDFactoryColortemp6BExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Adc Gain R=======================
void RTDFactoryAdcGainREnter(void)
{
#if(_VGA_SUPPORT == _ON)
    g_usBackupValue = g_stAdcData.pucAdcGainMSB[_AUTO_RED_CHANNEL];
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_GAIN_RED_ADJ);
#endif
}

void RTDFactoryAdcGainRLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_GAIN_GREEN);
}

void RTDFactoryAdcGainRRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT6_BLUE);
    RTDFactoryOsdChangColorTemp(_CT_USER);
}

void RTDFactoryAdcGainRExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Adc Gain G=======================
void RTDFactoryAdcGainGEnter(void)
{
#if(_VGA_SUPPORT == _ON)
    g_usBackupValue = g_stAdcData.pucAdcGainMSB[_AUTO_GREEN_CHANNEL];
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_GAIN_GREEN_ADJ);
#endif
}

void RTDFactoryAdcGainGLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_GAIN_BLUE);
}

void RTDFactoryAdcGainGRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_GAIN_RED);
}

void RTDFactoryAdcGainGExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Adc Gain B=======================
void RTDFactoryAdcGainBEnter(void)
{
#if(_VGA_SUPPORT == _ON)
    g_usBackupValue = g_stAdcData.pucAdcGainMSB[_AUTO_BLUE_CHANNEL];
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_GAIN_BLUE_ADJ);
#endif
}

void RTDFactoryAdcGainBLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OFFSET_RED);
}

void RTDFactoryAdcGainBRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_GAIN_GREEN);
}

void RTDFactoryAdcGainBExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Adc Offset R=======================
void RTDFactoryAdcOffsetREnter(void)
{
#if(_VGA_SUPPORT == _ON)
    g_usBackupValue = g_stAdcData.pucAdcOffsetMSB[_AUTO_RED_CHANNEL];
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OFFSET_RED_ADJ);
#endif
}

void RTDFactoryAdcOffsetRLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OFFSET_GREEN);
}

void RTDFactoryAdcOffsetRRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_GAIN_BLUE);
}

void RTDFactoryAdcOffsetRExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Adc Offset G=======================
void RTDFactoryAdcOffsetGEnter(void)
{
#if(_VGA_SUPPORT == _ON)
    g_usBackupValue = g_stAdcData.pucAdcOffsetMSB[_AUTO_GREEN_CHANNEL];
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OFFSET_GREEN_ADJ);
#endif
}

void RTDFactoryAdcOffsetGLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OFFSET_BLUE);
}

void RTDFactoryAdcOffsetGRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OFFSET_RED);
}

void RTDFactoryAdcOffsetGExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Adc Offset B=======================
void RTDFactoryAdcOffsetBEnter(void)
{
#if(_VGA_SUPPORT == _ON)
    g_usBackupValue = g_stAdcData.pucAdcOffsetMSB[_AUTO_BLUE_CHANNEL];
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OFFSET_BLUE_ADJ);
#endif
}

void RTDFactoryAdcOffsetBLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OSD_PAGE);
}

void RTDFactoryAdcOffsetBRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OFFSET_GREEN);
}

void RTDFactoryAdcOffsetBExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Osd Page=======================
void RTDFactoryOsdPageEnter(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OSD_PAGE_ADJ);
}

void RTDFactoryOsdPageLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_EXIT);
}

void RTDFactoryOsdPageRight(void)
{
#if(_VGA_SUPPORT == _ON)
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OFFSET_BLUE);
#else
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT6_BLUE);
    RTDFactoryOsdChangColorTemp(_CT_USER);
#endif
}

void RTDFactoryOsdPageExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Exit=======================
void RTDFactoryExitEnter(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

void RTDFactoryExitLeft(void)
{
#if(_VGA_SUPPORT == _ON)
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_AUTOCOLOR);
#else
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BURNIN);
#endif
}

void RTDFactoryExitRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OSD_PAGE);
}

void RTDFactoryExitExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}


//============= Auto Color Type Select =======================
void RTDFactoryAutoColorTypeSelectEnter(void)
{
    if(g_usAdjustValue != GET_OSD_FACTORY_AUTO_COLOR_TYPE())
    {
        SET_OSD_FACTORY_AUTO_COLOR_TYPE(g_usAdjustValue);
        RTDNVRamSaveOsdUserData();
    }

    RTDFactoryAutoColorTypeSelectExit();
}

void RTDFactoryAutoColorTypeSelectLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_AUTO_COLOR_TYPE, g_usAdjustValue);
}

void RTDFactoryAutoColorTypeSelectRight(void)
{
    RTDFactoryAutoColorTypeSelectLeft();
}

void RTDFactoryAutoColorTypeSelectExit(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_AUTOCOLOR_TYPE);
}

//============= Burnin On Off=======================
void RTDFactoryBurninOnOffEnter(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BURNIN);
}

void RTDFactoryBurninOnOffLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_BURNIN_ON_OFF, g_usAdjustValue);
}

void RTDFactoryBurninOnOffRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_BURNIN_ON_OFF, g_usAdjustValue);
}

void RTDFactoryBurninOnOffExit(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BURNIN);
}

//============= Colortemp 1 R Adjust=======================
void RTDFactoryColortemp1RAdjustEnter(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempR)
    {
        RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()));
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT1_RED);
}

void RTDFactoryColortemp1RAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT1_RED_ADJ, g_stColorProcData.usColorTempR);
}

void RTDFactoryColortemp1RAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT1_RED_ADJ, g_stColorProcData.usColorTempR);
}

void RTDFactoryColortemp1RAdjustExit(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempR)
    {
        g_stColorProcData.usColorTempR = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_CT1_RED_ADJ, g_stColorProcData.usColorTempR);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT1_RED);
}

//============= Colortemp 1 G Adjust=======================
void RTDFactoryColortemp1GAdjustEnter(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempG)
    {
        RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()));
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT1_GREEN);
}

void RTDFactoryColortemp1GAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT1_GREEN_ADJ, g_stColorProcData.usColorTempG);
}

void RTDFactoryColortemp1GAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT1_GREEN_ADJ, g_stColorProcData.usColorTempG);
}

void RTDFactoryColortemp1GAdjustExit(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempG)
    {
        g_stColorProcData.usColorTempG = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_CT1_GREEN_ADJ, g_stColorProcData.usColorTempG);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT1_GREEN);
}

//============= Colortemp 1 B Adjust=======================
void RTDFactoryColortemp1BAdjustEnter(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempB)
    {
        RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()));
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT1_BLUE);
}

void RTDFactoryColortemp1BAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT1_BLUE_ADJ, g_stColorProcData.usColorTempB);
}

void RTDFactoryColortemp1BAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT1_BLUE_ADJ, g_stColorProcData.usColorTempB);
}

void RTDFactoryColortemp1BAdjustExit(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempB)
    {
        g_stColorProcData.usColorTempB = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_CT1_BLUE_ADJ, g_stColorProcData.usColorTempB);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT1_BLUE);
}

//============= Colortemp 2 R Adjust=======================
void RTDFactoryColortemp2RAdjustEnter(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempR)
    {
        RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()));
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT2_RED);
}

void RTDFactoryColortemp2RAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT2_RED_ADJ, g_stColorProcData.usColorTempR);
}

void RTDFactoryColortemp2RAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT2_RED_ADJ, g_stColorProcData.usColorTempR);
}

void RTDFactoryColortemp2RAdjustExit(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempR)
    {
        g_stColorProcData.usColorTempR = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_CT2_RED_ADJ, g_stColorProcData.usColorTempR);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT2_RED);
}

//============= Colortemp 2 G Adjust=======================
void RTDFactoryColortemp2GAdjustEnter(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempG)
    {
        RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()));
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT2_GREEN);
}

void RTDFactoryColortemp2GAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT2_GREEN_ADJ, g_stColorProcData.usColorTempG);
}

void RTDFactoryColortemp2GAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT2_GREEN_ADJ, g_stColorProcData.usColorTempG);
}

void RTDFactoryColortemp2GAdjustExit(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempG)
    {
        g_stColorProcData.usColorTempG = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_CT2_GREEN_ADJ, g_stColorProcData.usColorTempG);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT2_GREEN);
}

//============= Colortemp 2 B Adjust=======================
void RTDFactoryColortemp2BAdjustEnter(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempB)
    {
        RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()));
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT2_BLUE);
}

void RTDFactoryColortemp2BAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT2_BLUE_ADJ, g_stColorProcData.usColorTempB);
}

void RTDFactoryColortemp2BAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT2_BLUE_ADJ, g_stColorProcData.usColorTempB);
}

void RTDFactoryColortemp2BAdjustExit(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempB)
    {
        g_stColorProcData.usColorTempB = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_CT2_BLUE_ADJ, g_stColorProcData.usColorTempB);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT2_BLUE);
}

//============= Colortemp 3 R Adjust=======================
void RTDFactoryColortemp3RAdjustEnter(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempR)
    {
        RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()));
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT3_RED);
}

void RTDFactoryColortemp3RAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT3_RED_ADJ, g_stColorProcData.usColorTempR);
}

void RTDFactoryColortemp3RAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT3_RED_ADJ, g_stColorProcData.usColorTempR);
}

void RTDFactoryColortemp3RAdjustExit(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempR)
    {
        g_stColorProcData.usColorTempR = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_CT3_RED_ADJ, g_stColorProcData.usColorTempR);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT3_RED);
}

//============= Colortemp 3 G Adjust=======================
void RTDFactoryColortemp3GAdjustEnter(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempG)
    {
        RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()));
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT3_GREEN);
}

void RTDFactoryColortemp3GAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT3_GREEN_ADJ, g_stColorProcData.usColorTempG);
}

void RTDFactoryColortemp3GAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT3_GREEN_ADJ, g_stColorProcData.usColorTempG);
}

void RTDFactoryColortemp3GAdjustExit(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempG)
    {
        g_stColorProcData.usColorTempG = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_CT3_GREEN_ADJ, g_stColorProcData.usColorTempG);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT3_GREEN);
}

//============= Colortemp 3 B Adjust=======================
void RTDFactoryColortemp3BAdjustEnter(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempB)
    {
        RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()));
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT3_BLUE);
}

void RTDFactoryColortemp3BAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT3_BLUE_ADJ, g_stColorProcData.usColorTempB);
}

void RTDFactoryColortemp3BAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT3_BLUE_ADJ, g_stColorProcData.usColorTempB);
}

void RTDFactoryColortemp3BAdjustExit(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempB)
    {
        g_stColorProcData.usColorTempB = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_CT3_BLUE_ADJ, g_stColorProcData.usColorTempB);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT3_BLUE);
}

//============= Colortemp 4 R Adjust=======================
void RTDFactoryColortemp4RAdjustEnter(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempR)
    {
        RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()));
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT4_RED);
}

void RTDFactoryColortemp4RAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT4_RED_ADJ, g_stColorProcData.usColorTempR);
}

void RTDFactoryColortemp4RAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT4_RED_ADJ, g_stColorProcData.usColorTempR);
}

void RTDFactoryColortemp4RAdjustExit(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempR)
    {
        g_stColorProcData.usColorTempR = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_CT4_RED_ADJ, g_stColorProcData.usColorTempR);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT4_RED);
}

//============= Colortemp 4 G Adjust=======================
void RTDFactoryColortemp4GAdjustEnter(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempG)
    {
        RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()));
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT4_GREEN);
}

void RTDFactoryColortemp4GAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT4_GREEN_ADJ, g_stColorProcData.usColorTempG);
}

void RTDFactoryColortemp4GAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT4_GREEN_ADJ, g_stColorProcData.usColorTempG);
}

void RTDFactoryColortemp4GAdjustExit(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempG)
    {
        g_stColorProcData.usColorTempG = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_CT4_GREEN_ADJ, g_stColorProcData.usColorTempG);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT4_GREEN);
}

//============= Colortemp 4 B Adjust=======================
void RTDFactoryColortemp4BAdjustEnter(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempB)
    {
        RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()));
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT4_BLUE);
}

void RTDFactoryColortemp4BAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT4_BLUE_ADJ, g_stColorProcData.usColorTempB);
}

void RTDFactoryColortemp4BAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT4_BLUE_ADJ, g_stColorProcData.usColorTempB);
}

void RTDFactoryColortemp4BAdjustExit(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempB)
    {
        g_stColorProcData.usColorTempB = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_CT4_BLUE_ADJ, g_stColorProcData.usColorTempB);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT4_BLUE);
}

//============= Colortemp 5 R Adjust=======================
void RTDFactoryColortemp5RAdjustEnter(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempR)
    {
        RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()));
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT5_RED);
}

void RTDFactoryColortemp5RAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT5_RED_ADJ, g_stColorProcData.usColorTempR);
}

void RTDFactoryColortemp5RAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT5_RED_ADJ, g_stColorProcData.usColorTempR);
}

void RTDFactoryColortemp5RAdjustExit(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempR)
    {
        g_stColorProcData.usColorTempR = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_CT5_RED_ADJ, g_stColorProcData.usColorTempR);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT5_RED);
}

//============= Colortemp 5 G Adjust=======================
void RTDFactoryColortemp5GAdjustEnter(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempG)
    {
        RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()));
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT5_GREEN);
}

void RTDFactoryColortemp5GAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT5_GREEN_ADJ, g_stColorProcData.usColorTempG);
}

void RTDFactoryColortemp5GAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT5_GREEN_ADJ, g_stColorProcData.usColorTempG);
}

void RTDFactoryColortemp5GAdjustExit(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempG)
    {
        g_stColorProcData.usColorTempG = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_CT5_GREEN_ADJ, g_stColorProcData.usColorTempG);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT5_GREEN);
}

//============= Colortemp 5 B Adjust=======================
void RTDFactoryColortemp5BAdjustEnter(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempB)
    {
        RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()));
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT5_BLUE);
}

void RTDFactoryColortemp5BAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT5_BLUE_ADJ, g_stColorProcData.usColorTempB);
}

void RTDFactoryColortemp5BAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT5_BLUE_ADJ, g_stColorProcData.usColorTempB);
}

void RTDFactoryColortemp5BAdjustExit(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempB)
    {
        g_stColorProcData.usColorTempB = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_CT5_BLUE_ADJ, g_stColorProcData.usColorTempB);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT5_BLUE);
}

//============= Colortemp 6 R Adjust=======================
void RTDFactoryColortemp6RAdjustEnter(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempR)
    {
        RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()));
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT6_RED);
}

void RTDFactoryColortemp6RAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT6_RED_ADJ, g_stColorProcData.usColorTempR);
}

void RTDFactoryColortemp6RAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT6_RED_ADJ, g_stColorProcData.usColorTempR);
}

void RTDFactoryColortemp6RAdjustExit(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempR)
    {
        g_stColorProcData.usColorTempR = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_CT6_RED_ADJ, g_stColorProcData.usColorTempR);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT6_RED);
}

//============= Colortemp 6 G Adjust=======================
void RTDFactoryColortemp6GAdjustEnter(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempG)
    {
        RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()));
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT6_GREEN);
}

void RTDFactoryColortemp6GAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT6_GREEN_ADJ, g_stColorProcData.usColorTempG);
}

void RTDFactoryColortemp6GAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT6_GREEN_ADJ, g_stColorProcData.usColorTempG);
}

void RTDFactoryColortemp6GAdjustExit(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempG)
    {
        g_stColorProcData.usColorTempG = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_CT6_GREEN_ADJ, g_stColorProcData.usColorTempG);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT6_GREEN);
}

//============= Colortemp 6 B Adjust=======================
void RTDFactoryColortemp6BAdjustEnter(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempB)
    {
        RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()));
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT6_BLUE);
}

void RTDFactoryColortemp6BAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT6_BLUE_ADJ, g_stColorProcData.usColorTempB);
}

void RTDFactoryColortemp6BAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_CT6_BLUE_ADJ, g_stColorProcData.usColorTempB);
}

void RTDFactoryColortemp6BAdjustExit(void)
{
    if(g_usBackupValue != g_stColorProcData.usColorTempB)
    {
        g_stColorProcData.usColorTempB = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_CT6_BLUE_ADJ, g_stColorProcData.usColorTempB);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_CT6_BLUE);
}

//============= Adc Gain R Adjust=======================
void RTDFactoryAdcGainRAdjustEnter(void)
{
#if(_VGA_SUPPORT == _ON)
    if(g_usBackupValue != g_stAdcData.pucAdcGainMSB[_AUTO_RED_CHANNEL])
    {
        UserCommonNVRamSaveADCSetting(_COLOR_SPACE_RGB);
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_GAIN_RED);
#endif
}

void RTDFactoryAdcGainRAdjustLeft(void)
{
#if(_VGA_SUPPORT == _ON)
    RTDFactoryOsdDispNumber(_MENU_FACTORY_GAIN_RED_ADJ, g_stAdcData.pucAdcGainMSB[_AUTO_RED_CHANNEL]);
#endif
}

void RTDFactoryAdcGainRAdjustRight(void)
{
#if(_VGA_SUPPORT == _ON)
    RTDFactoryOsdDispNumber(_MENU_FACTORY_GAIN_RED_ADJ, g_stAdcData.pucAdcGainMSB[_AUTO_RED_CHANNEL]);
#endif
}

void RTDFactoryAdcGainRAdjustExit(void)
{
#if(_VGA_SUPPORT == _ON)
    if(g_usBackupValue != g_stAdcData.pucAdcGainMSB[_AUTO_RED_CHANNEL])
    {
        g_stAdcData.pucAdcGainMSB[_AUTO_RED_CHANNEL] = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_GAIN_RED_ADJ, g_stAdcData.pucAdcGainMSB[_AUTO_RED_CHANNEL]);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_GAIN_RED);
#endif
}

//============= Adc Gain G Adjust=======================
void RTDFactoryAdcGainGAdjustEnter(void)
{
#if(_VGA_SUPPORT == _ON)
    if(g_usBackupValue != g_stAdcData.pucAdcGainMSB[_AUTO_GREEN_CHANNEL])
    {
        UserCommonNVRamSaveADCSetting(_COLOR_SPACE_RGB);
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_GAIN_GREEN);
#endif
}

void RTDFactoryAdcGainGAdjustLeft(void)
{
#if(_VGA_SUPPORT == _ON)
    RTDFactoryOsdDispNumber(_MENU_FACTORY_GAIN_GREEN_ADJ, g_stAdcData.pucAdcGainMSB[_AUTO_GREEN_CHANNEL]);
#endif
}

void RTDFactoryAdcGainGAdjustRight(void)
{
#if(_VGA_SUPPORT == _ON)
    RTDFactoryOsdDispNumber(_MENU_FACTORY_GAIN_GREEN_ADJ, g_stAdcData.pucAdcGainMSB[_AUTO_GREEN_CHANNEL]);
#endif
}

void RTDFactoryAdcGainGAdjustExit(void)
{
#if(_VGA_SUPPORT == _ON)
    if(g_usBackupValue != g_stAdcData.pucAdcGainMSB[_AUTO_GREEN_CHANNEL])
    {
        g_stAdcData.pucAdcGainMSB[_AUTO_GREEN_CHANNEL] = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_GAIN_GREEN_ADJ, g_stAdcData.pucAdcGainMSB[_AUTO_GREEN_CHANNEL]);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_GAIN_GREEN);
#endif
}

//============= Adc Gain B Adjust=======================
void RTDFactoryAdcGainBAdjustEnter(void)
{
#if(_VGA_SUPPORT == _ON)
    if(g_usBackupValue != g_stAdcData.pucAdcGainMSB[_AUTO_BLUE_CHANNEL])
    {
        UserCommonNVRamSaveADCSetting(_COLOR_SPACE_RGB);
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_GAIN_BLUE);
#endif
}

void RTDFactoryAdcGainBAdjustLeft(void)
{
#if(_VGA_SUPPORT == _ON)
    RTDFactoryOsdDispNumber(_MENU_FACTORY_GAIN_BLUE_ADJ, g_stAdcData.pucAdcGainMSB[_AUTO_BLUE_CHANNEL]);
#endif
}

void RTDFactoryAdcGainBAdjustRight(void)
{
#if(_VGA_SUPPORT == _ON)
    RTDFactoryOsdDispNumber(_MENU_FACTORY_GAIN_BLUE_ADJ, g_stAdcData.pucAdcGainMSB[_AUTO_BLUE_CHANNEL]);
#endif
}

void RTDFactoryAdcGainBAdjustExit(void)
{
#if(_VGA_SUPPORT == _ON)
    if(g_usBackupValue != g_stAdcData.pucAdcGainMSB[_AUTO_BLUE_CHANNEL])
    {
        g_stAdcData.pucAdcGainMSB[_AUTO_BLUE_CHANNEL] = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_GAIN_BLUE_ADJ, g_stAdcData.pucAdcGainMSB[_AUTO_BLUE_CHANNEL]);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_GAIN_BLUE);
#endif
}

//============= Adc Offset R Adjust=======================
void RTDFactoryAdcOffsetRAdjustEnter(void)
{
#if(_VGA_SUPPORT == _ON)
    if(g_usBackupValue != g_stAdcData.pucAdcOffsetMSB[_AUTO_RED_CHANNEL])
    {
        UserCommonNVRamSaveADCSetting(_COLOR_SPACE_RGB);
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OFFSET_RED);
#endif
}

void RTDFactoryAdcOffsetRAdjustLeft(void)
{
#if(_VGA_SUPPORT == _ON)
    RTDFactoryOsdDispNumber(_MENU_FACTORY_OFFSET_RED_ADJ, g_stAdcData.pucAdcOffsetMSB[_AUTO_RED_CHANNEL]);
#endif
}

void RTDFactoryAdcOffsetRAdjustRight(void)
{
#if(_VGA_SUPPORT == _ON)
    RTDFactoryOsdDispNumber(_MENU_FACTORY_OFFSET_RED_ADJ, g_stAdcData.pucAdcOffsetMSB[_AUTO_RED_CHANNEL]);
#endif
}

void RTDFactoryAdcOffsetRAdjustExit(void)
{
#if(_VGA_SUPPORT == _ON)
    if(g_usBackupValue != g_stAdcData.pucAdcOffsetMSB[_AUTO_RED_CHANNEL])
    {
        g_stAdcData.pucAdcOffsetMSB[_AUTO_RED_CHANNEL] = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_OFFSET_RED_ADJ, g_stAdcData.pucAdcOffsetMSB[_AUTO_RED_CHANNEL]);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OFFSET_RED);
#endif
}

//============= Adc Offset G Adjust=======================
void RTDFactoryAdcOffsetGAdjustEnter(void)
{
#if(_VGA_SUPPORT == _ON)
    if(g_usBackupValue != g_stAdcData.pucAdcOffsetMSB[_AUTO_GREEN_CHANNEL])
    {
        UserCommonNVRamSaveADCSetting(_COLOR_SPACE_RGB);
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OFFSET_GREEN);
#endif
}

void RTDFactoryAdcOffsetGAdjustLeft(void)
{
#if(_VGA_SUPPORT == _ON)
    RTDFactoryOsdDispNumber(_MENU_FACTORY_OFFSET_GREEN_ADJ, g_stAdcData.pucAdcOffsetMSB[_AUTO_GREEN_CHANNEL]);
#endif
}

void RTDFactoryAdcOffsetGAdjustRight(void)
{
#if(_VGA_SUPPORT == _ON)
    RTDFactoryOsdDispNumber(_MENU_FACTORY_OFFSET_GREEN_ADJ, g_stAdcData.pucAdcOffsetMSB[_AUTO_GREEN_CHANNEL]);
#endif
}

void RTDFactoryAdcOffsetGAdjustExit(void)
{
#if(_VGA_SUPPORT == _ON)
    if(g_usBackupValue != g_stAdcData.pucAdcOffsetMSB[_AUTO_GREEN_CHANNEL])
    {
        g_stAdcData.pucAdcOffsetMSB[_AUTO_GREEN_CHANNEL] = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_OFFSET_GREEN_ADJ, g_stAdcData.pucAdcOffsetMSB[_AUTO_GREEN_CHANNEL]);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OFFSET_GREEN);
#endif
}

//============= Adc Offset B Adjust=======================
void RTDFactoryAdcOffsetBAdjustEnter(void)
{
#if(_VGA_SUPPORT == _ON)
    if(g_usBackupValue != g_stAdcData.pucAdcOffsetMSB[_AUTO_BLUE_CHANNEL])
    {
        UserCommonNVRamSaveADCSetting(_COLOR_SPACE_RGB);
    }

    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OFFSET_BLUE);
#endif
}

void RTDFactoryAdcOffsetBAdjustLeft(void)
{
#if(_VGA_SUPPORT == _ON)
    RTDFactoryOsdDispNumber(_MENU_FACTORY_OFFSET_BLUE_ADJ, g_stAdcData.pucAdcOffsetMSB[_AUTO_BLUE_CHANNEL]);
#endif
}

void RTDFactoryAdcOffsetBAdjustRight(void)
{
#if(_VGA_SUPPORT == _ON)
    RTDFactoryOsdDispNumber(_MENU_FACTORY_OFFSET_BLUE_ADJ, g_stAdcData.pucAdcOffsetMSB[_AUTO_BLUE_CHANNEL]);
#endif
}

void RTDFactoryAdcOffsetBAdjustExit(void)
{
#if(_VGA_SUPPORT == _ON)
    if(g_usBackupValue != g_stAdcData.pucAdcOffsetMSB[_AUTO_BLUE_CHANNEL])
    {
        g_stAdcData.pucAdcOffsetMSB[_AUTO_BLUE_CHANNEL] = g_usBackupValue;
        RTDFactoryOsdDispNumber(_MENU_FACTORY_OFFSET_BLUE_ADJ, g_stAdcData.pucAdcOffsetMSB[_AUTO_BLUE_CHANNEL]);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OFFSET_BLUE);
#endif
}

//============= Osd Page Adjust=======================
void RTDFactoryOsdPageAdjustEnter(void)
{
    if(g_ucFactoryPage == 1)
    {
        RTDFactoryMainMenu1();
    }
}

void RTDFactoryOsdPageAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_OSD_PAGE_ADJ, g_ucFactoryPage);
}

void RTDFactoryOsdPageAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_OSD_PAGE_ADJ, g_ucFactoryPage);
}

void RTDFactoryOsdPageAdjustExit(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_EXIT);
}


//============= Background =======================
void RTDFactoryBgEnter(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BG_ON_OFF);
}

void RTDFactoryBgLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BG_RED);
}

void RTDFactoryBgRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_EXIT1);
}

void RTDFactoryBgExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Background R=======================
void RTDFactoryBgREnter(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BG_RED_ADJ);
}

void RTDFactoryBgRLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BG_GREEN);
}

void RTDFactoryBgRRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BG);
}

void RTDFactoryBgRExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Background G=======================
void RTDFactoryBgGEnter(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BG_GREEN_ADJ);
}

void RTDFactoryBgGLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BG_BLUE);
}

void RTDFactoryBgGRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BG_RED);
}

void RTDFactoryBgGExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Background B=======================
void RTDFactoryBgBEnter(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BG_BLUE_ADJ);
}

void RTDFactoryBgBLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_SSC);
}

void RTDFactoryBgBRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BG_GREEN);
}

void RTDFactoryBgBExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= SSC=======================
void RTDFactorySSCEnter(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_SSC_ADJ);
}

void RTDFactorySSCLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_LVDS_CLOCK);
}

void RTDFactorySSCRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BG_BLUE);
}

void RTDFactorySSCExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= LVDS Clock=======================
void RTDFactoryLVDSClockEnter(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_LVDS_CLOCK_CURRENT_ADJ);
}

void RTDFactoryLVDSClockLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_LVDS_DATA);
}

void RTDFactoryLVDSClockRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_SSC);
}

void RTDFactoryLVDSClockExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= LVDS Data=======================
void RTDFactoryLVDSDataEnter(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_LVDS_DATA_CURRENT_ADJ);
}

void RTDFactoryLVDSDataLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_PATTERN);
}

void RTDFactoryLVDSDataRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_LVDS_CLOCK);
}

void RTDFactoryLVDSDataExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Pattern =======================
void RTDFactoryPatternEnter(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_PATTERN_ADJ);
}

void RTDFactoryPatternLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_HOT_PLUG_DP_DC_OFF_HIGH);
}

void RTDFactoryPatternRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_LVDS_DATA);
}

void RTDFactoryPatternExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Hot Plug DP DC Off High=======================
void RTDFactoryHotPlugDPDCOffHighEnter(void)
{
    g_usBackupValue = UserCommonNVRamGetSystemData(_DP_HOT_PLUG_DC_OFF_HIGH);
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_HOT_PLUG_DP_DC_OFF_HIGH_ON_OFF);
}
void RTDFactoryHotPlugDPDCOffHighLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_HOT_PLUG_HDMI_SUPPORT);
}

void RTDFactoryHotPlugDPDCOffHighRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_PATTERN);
}

void RTDFactoryHotPlugDPDCOffHighExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Hot Plug HDMI Support=======================
void RTDFactoryHotPlugHDMISupportEnter(void)
{
    g_usBackupValue = UserCommonNVRamGetSystemData(_HDMI_HOT_PLUG_SUPPORT);
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_HOT_PLUG_HDMI_SUPPORT_ON_OFF);
}
void RTDFactoryHotPlugHDMISupportLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_HOT_PLUG_HDMI_SUPPORT_TIME);
}

void RTDFactoryHotPlugHDMISupportRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_HOT_PLUG_DP_DC_OFF_HIGH);
}

void RTDFactoryHotPlugHDMISupportExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Hot Plug HDMI Support Time=======================
void RTDFactoryHotPlugHDMISupportTimeEnter(void)
{
    g_usBackupValue = UserCommonNVRamGetSystemData(_HDMI_HOT_PLUG_SUPPORT_TIME);
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_HOT_PLUG_HDMI_SUPPORT_TIME_ADJ);
}
void RTDFactoryHotPlugHDMISupportTimeLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_DP_FREESYNC);
}

void RTDFactoryHotPlugHDMISupportTimeRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_HOT_PLUG_HDMI_SUPPORT);
}

void RTDFactoryHotPlugHDMISupportTimeExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}
//============= DP FREESYNC=======================
void RTDFactoryDPFREESYNCEnter(void)
{
    g_usBackupValue = GET_OSD_FREE_SYNC_STATUS();
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_DP_FREESYNC_ON_OFF);
}

void RTDFactoryDPFREESYNCLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_HDMI_FREESYNC);
}

void RTDFactoryDPFREESYNCRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_HOT_PLUG_HDMI_SUPPORT_TIME);
}

void RTDFactoryDPFREESYNCExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= HDMI FREESYNC======================
void RTDFactoryHDMIFREESYNCEnter(void)
{
    g_usBackupValue = GET_OSD_FREE_SYNC_STATUS();
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_HDMI_FREESYNC_ON_OFF);
}

void RTDFactoryHDMIFREESYNCLeft(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OSD_PAGE_1);
}

void RTDFactoryHDMIFREESYNCRight(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_DP_FREESYNC);
}

void RTDFactoryHDMIFREESYNCExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}
//============= Osd Page 1=======================
void RTDFactoryOsdPage1Enter(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OSD_PAGE_1_ADJ);
}

void RTDFactoryOsdPage1Left(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_EXIT1);
}

void RTDFactoryOsdPage1Right(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_HDMI_FREESYNC);
}

void RTDFactoryOsdPage1Exit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Exit=======================
void RTDFactoryExit1Enter(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

void RTDFactoryExit1Left(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BG);
}

void RTDFactoryExit1Right(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_OSD_PAGE_1);
}

void RTDFactoryExit1Exit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= BG On Off=======================
void RTDFactoryBgOnOffEnter(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BG);
}

void RTDFactoryBgOnOffLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_BG_ON_OFF, g_usAdjustValue);
}

void RTDFactoryBgOnOffRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_BG_ON_OFF, g_usAdjustValue);
}

void RTDFactoryBgOnOffExit(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BG);
}

//============= BG R Adjust=======================
void RTDFactoryBgRAdjustEnter(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BG_RED);
}

void RTDFactoryBgRAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_BG_RED_ADJ, g_ucBgColorR);
}

void RTDFactoryBgRAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_BG_RED_ADJ, g_ucBgColorR);
}

void RTDFactoryBgRAdjustExit(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BG_RED);
}

//============= BG G Adjust=======================
void RTDFactoryBgGAdjustEnter(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BG_GREEN);
}

void RTDFactoryBgGAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_BG_GREEN_ADJ, g_ucBgColorG);
}

void RTDFactoryBgGAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_BG_GREEN_ADJ, g_ucBgColorG);
}

void RTDFactoryBgGAdjustExit(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BG_GREEN);
}

//============= Adc Gain B Adjust=======================
void RTDFactoryBgBAdjustEnter(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BG_BLUE);
}

void RTDFactoryBgBAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_BG_BLUE_ADJ, g_ucBgColorB);
}

void RTDFactoryBgBAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_BG_BLUE_ADJ, g_ucBgColorB);
}

void RTDFactoryBgBAdjustExit(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_BG_BLUE);
}

//============= SSC Adjust=======================
void RTDFactorySSCAdjustEnter(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_SSC);
}

void RTDFactorySSCAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_SSC_ADJ, g_usAdjustValue);
}

void RTDFactorySSCAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_SSC_ADJ, g_usAdjustValue);
}

void RTDFactorySSCAdjustExit(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_SSC);
}

//============= LVDS Clock Current Adjust=======================
void RTDFactoryLVDSClockCurrentAdjustEnter(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_LVDS_CLOCK);
}

void RTDFactoryLVDSClockCurrentAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_LVDS_CLOCK_CURRENT_ADJ, g_usAdjustValue);
}

void RTDFactoryLVDSClockCurrentAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_LVDS_CLOCK_CURRENT_ADJ, g_usAdjustValue);
}

void RTDFactoryLVDSClockCurrentAdjustExit(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_LVDS_CLOCK);
}

//============= LVDS Data Current Adjust=======================
void RTDFactoryLVDSDataCurrentAdjustEnter(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_LVDS_DATA);
}

void RTDFactoryLVDSDataCurrentAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_LVDS_DATA_CURRENT_ADJ, g_usAdjustValue);
}

void RTDFactoryLVDSDataCurrentAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_LVDS_DATA_CURRENT_ADJ, g_usAdjustValue);
}

void RTDFactoryLVDSDataCurrentAdjustExit(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_LVDS_DATA);
}

//============= Pattern Adjust=======================
void RTDFactoryPatternAdjustEnter(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_PATTERN);
}

void RTDFactoryPatternAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_PATTERN_ADJ, g_usAdjustValue);
}

void RTDFactoryPatternAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_PATTERN_ADJ, g_usAdjustValue);
}

void RTDFactoryPatternAdjustExit(void)
{
    RTDFactoryOsdFuncDisableOsd();
}

//============= Hot Plug DP DC Off High Adjust=======================
void RTDFactoryHotPlugDPDCOffHighAdjustEnter(void)
{
    if(g_usBackupValue != UserCommonNVRamGetSystemData(_DP_HOT_PLUG_DC_OFF_HIGH))
    {
        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_HOT_PLUG_DP_DC_OFF_HIGH);
}
void RTDFactoryHotPlugDPDCOffHighAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_HOT_PLUG_DP_DC_OFF_HIGH_ON_OFF, UserCommonNVRamGetSystemData(_DP_HOT_PLUG_DC_OFF_HIGH));
}
void RTDFactoryHotPlugDPDCOffHighAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_HOT_PLUG_DP_DC_OFF_HIGH_ON_OFF, UserCommonNVRamGetSystemData(_DP_HOT_PLUG_DC_OFF_HIGH));
}
void RTDFactoryHotPlugDPDCOffHighAdjustExit(void)
{
    if(g_usBackupValue != UserCommonNVRamGetSystemData(_DP_HOT_PLUG_DC_OFF_HIGH))
    {
        UserCommonNVRamSetSystemData(_DP_HOT_PLUG_DC_OFF_HIGH, g_usBackupValue);
        RTDFactoryOsdDispNumber(_MENU_FACTORY_HOT_PLUG_DP_DC_OFF_HIGH_ON_OFF, UserCommonNVRamGetSystemData(_DP_HOT_PLUG_DC_OFF_HIGH));
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_HOT_PLUG_DP_DC_OFF_HIGH);
}

//============= Hot Plug HDMI Support Adjus=======================
void RTDFactoryHotPlugHDMISupportAdjustEnter(void)
{
    if(g_usBackupValue != UserCommonNVRamGetSystemData(_HDMI_HOT_PLUG_SUPPORT))
    {
        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_HOT_PLUG_HDMI_SUPPORT);
}
void RTDFactoryHotPlugHDMISupportAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_HOT_PLUG_HDMI_SUPPORT_ON_OFF, UserCommonNVRamGetSystemData(_HDMI_HOT_PLUG_SUPPORT));
}
void RTDFactoryHotPlugHDMISupportAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_HOT_PLUG_HDMI_SUPPORT_ON_OFF, UserCommonNVRamGetSystemData(_HDMI_HOT_PLUG_SUPPORT));
}
void RTDFactoryHotPlugHDMISupportAdjustExit(void)
{
    if(g_usBackupValue != UserCommonNVRamGetSystemData(_HDMI_HOT_PLUG_SUPPORT))
    {
        UserCommonNVRamSetSystemData(_HDMI_HOT_PLUG_SUPPORT, g_usBackupValue);
        RTDFactoryOsdDispNumber(_MENU_FACTORY_HOT_PLUG_HDMI_SUPPORT_ON_OFF, UserCommonNVRamGetSystemData(_HDMI_HOT_PLUG_SUPPORT));
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_HOT_PLUG_HDMI_SUPPORT);
}

//============= Hot Plug HDMI Support Time Adjust=======================
void RTDFactoryHotPlugHDMISupportTimeAdjustEnter(void)
{
    if(g_usBackupValue != UserCommonNVRamGetSystemData(_HDMI_HOT_PLUG_SUPPORT_TIME))
    {
        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_HOT_PLUG_HDMI_SUPPORT_TIME);
}
void RTDFactoryHotPlugHDMISupportTimeAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_HOT_PLUG_HDMI_SUPPORT_TIME_ADJ, UserCommonNVRamGetSystemData(_HDMI_HOT_PLUG_SUPPORT_TIME));
}
void RTDFactoryHotPlugHDMISupportTimeAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_HOT_PLUG_HDMI_SUPPORT_TIME_ADJ, UserCommonNVRamGetSystemData(_HDMI_HOT_PLUG_SUPPORT_TIME));
}
void RTDFactoryHotPlugHDMISupportTimeAdjustExit(void)
{
    if(g_usBackupValue != UserCommonNVRamGetSystemData(_HDMI_HOT_PLUG_SUPPORT_TIME))
    {
        UserCommonNVRamSetSystemData(_HDMI_HOT_PLUG_SUPPORT_TIME, g_usBackupValue);
        RTDFactoryOsdDispNumber(_MENU_FACTORY_HOT_PLUG_HDMI_SUPPORT_TIME_ADJ, UserCommonNVRamGetSystemData(_HDMI_HOT_PLUG_SUPPORT_TIME));
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_HOT_PLUG_HDMI_SUPPORT_TIME);
}

//============= DP/HDMI FREESYNC  Adjust=======================
void RTDFactoryDPFREESYNCAdjustEnter(void)
{
    if(g_usBackupValue != GET_OSD_FREE_SYNC_STATUS())
    {
        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_DP_FREESYNC);
}

void RTDFactoryDPFREESYNCAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_DP_FREESYNC_ON_OFF, GET_OSD_FREE_SYNC_STATUS());
}

void RTDFactoryDPFREESYNCAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_DP_FREESYNC_ON_OFF, GET_OSD_FREE_SYNC_STATUS());
}

void RTDFactoryDPFREESYNCAdjustExit(void)
{
    if(g_usBackupValue != GET_OSD_FREE_SYNC_STATUS())
    {
        RTDFactoryOsdDispNumber(_MENU_FACTORY_DP_FREESYNC_ON_OFF, GET_OSD_FREE_SYNC_STATUS());
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_DP_FREESYNC);
}

void RTDFactoryHDMIFREESYNCAdjustEnter(void)
{
    if(g_usBackupValue != GET_OSD_FREE_SYNC_STATUS())
    {
        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_HDMI_FREESYNC);
}

void RTDFactoryHDMIFREESYNCAdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_HDMI_FREESYNC_ON_OFF, GET_OSD_FREE_SYNC_STATUS());
}

void RTDFactoryHDMIFREESYNCAdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_HDMI_FREESYNC_ON_OFF, GET_OSD_FREE_SYNC_STATUS());
}

void RTDFactoryHDMIFREESYNCAdjustExit(void)
{
    if(g_usBackupValue != GET_OSD_FREE_SYNC_STATUS())
    {
        RTDFactoryOsdDispNumber(_MENU_FACTORY_HDMI_FREESYNC_ON_OFF, GET_OSD_FREE_SYNC_STATUS());
    }
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_HDMI_FREESYNC);
}

//============= Osd Page 1 Adjust=======================
void RTDFactoryOsdPage1AdjustEnter(void)
{
    if(g_ucFactoryPage == 0)
    {
        RTDFactoryMainMenu();
    }
}

void RTDFactoryOsdPage1AdjustLeft(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_OSD_PAGE_1_ADJ, g_ucFactoryPage);
}

void RTDFactoryOsdPage1AdjustRight(void)
{
    RTDFactoryOsdDispNumber(_MENU_FACTORY_OSD_PAGE_1_ADJ, g_ucFactoryPage);
}

void RTDFactoryOsdPage1AdjustExit(void)
{
    RTDFactoryOsdFuncSelectItem(_MENU_FACTORY_EXIT1);
}


