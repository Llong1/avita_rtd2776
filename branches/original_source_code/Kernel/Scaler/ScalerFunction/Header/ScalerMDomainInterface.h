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
// ID Code      : ScalerMDomainInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macros of MDomain Input Info.
//--------------------------------------------------
#define GET_MDOMAIN_INPUT_H_POLARITY()                 (g_stMDomainInputData.b1HSP)
#define GET_MDOMAIN_INPUT_V_POLARITY()                 (g_stMDomainInputData.b1VSP)
#define GET_MDOMAIN_INPUT_INTERLACE_FLG()              (g_stMDomainInputData.b1Interlace)
#define GET_MDOMAIN_INPUT_HFREQ()                      (g_stMDomainInputData.usHFreq)
#define GET_MDOMAIN_INPUT_HTOTAL()                     (g_stMDomainInputData.usHTotal)
#define GET_MDOMAIN_INPUT_HWIDTH()                     (g_stMDomainInputData.usHWidth)
#define GET_MDOMAIN_INPUT_HSTART()                     (g_stMDomainInputData.usHStart)
#define GET_MDOMAIN_INPUT_HSYNCWIDTH()                 (g_stMDomainInputData.usHSWidth)
#define GET_MDOMAIN_INPUT_VFREQ()                      (g_stMDomainInputData.usVFreq)
#define GET_MDOMAIN_INPUT_VTOTAL()                     (g_stMDomainInputData.usVTotal)
#define GET_MDOMAIN_INPUT_VHEIGHT()                    (g_stMDomainInputData.usVHeight)
#define GET_MDOMAIN_INPUT_VSTART()                     (g_stMDomainInputData.usVStart)
#define GET_MDOMAIN_INPUT_VSYNCWIDTH()                 (g_stMDomainInputData.usVSWidth)

//--------------------------------------------------
// Macros of MDomain Input info. modification
//--------------------------------------------------
#define SET_MDOMAIN_INPUT_STRUCTURE(x)                 (g_stMDomainInputData = (x))

#define SET_MDOMAIN_INPUT_HSTART(x)                    (g_stMDomainInputData.usHStart = (x))
#define SET_MDOMAIN_INPUT_HWIDTH(x)                    (g_stMDomainInputData.usHWidth = (x))
#define SET_MDOMAIN_INPUT_HTOTAL(x)                    (g_stMDomainInputData.usHTotal = (x))

#define SET_MDOMAIN_INPUT_VSTART(x)                    (g_stMDomainInputData.usVStart = (x))
#define SET_MDOMAIN_INPUT_VHEIGHT(x)                   (g_stMDomainInputData.usVHeight = (x))
#define SET_MDOMAIN_INPUT_VTOTAL(x)                    (g_stMDomainInputData.usVTotal = (x))

//--------------------------------------------------
// Macros of MDomain Output Info.
//--------------------------------------------------
#define GET_MDOMAIN_OUTPUT_DATA_PATH()                 (g_stMDomainOutputData.enumDisplayDataPath)
#define SET_MDOMAIN_OUTPUT_DATA_PATH(x)                (g_stMDomainOutputData.enumDisplayDataPath = (x))

#define GET_MDOMAIN_OUTPUT_HSTART()                    (g_stMDomainOutputData.usHStart)
#define GET_MDOMAIN_OUTPUT_HBSTART()                   (g_stMDomainOutputData.usHBackStart)
#define GET_MDOMAIN_OUTPUT_HWIDTH()                    (g_stMDomainOutputData.usHWidth)
#define GET_MDOMAIN_OUTPUT_HBWIDTH()                   (g_stMDomainOutputData.usHBackWidth)
#define GET_MDOMAIN_OUTPUT_HTOTAL()                    (g_stMDomainOutputData.usHTotal)

#define GET_MDOMAIN_OUTPUT_VSTART()                    (g_stMDomainOutputData.usVStart)
#define GET_MDOMAIN_OUTPUT_VBSTART()                   (g_stMDomainOutputData.usVBackStart)
#define GET_MDOMAIN_OUTPUT_VHEIGHT()                   (g_stMDomainOutputData.usVHeight)
#define GET_MDOMAIN_OUTPUT_VBHEIGHT()                  (g_stMDomainOutputData.usVBackHeight)
#define GET_MDOMAIN_OUTPUT_VTOTAL()                    (g_stMDomainOutputData.usVTotal)

//--------------------------------------------------
// Macros of MDomain Input info. modification
//--------------------------------------------------

#define SET_MDOMAIN_OUTPUT_HSTART(x)                   (g_stMDomainOutputData.usHStart = (x))
#define SET_MDOMAIN_OUTPUT_HBSTART(x)                  (g_stMDomainOutputData.usHBackStart = (x))
#define SET_MDOMAIN_OUTPUT_HWIDTH(x)                   (g_stMDomainOutputData.usHWidth = (x))
#define SET_MDOMAIN_OUTPUT_HBWIDTH(x)                  (g_stMDomainOutputData.usHBackWidth = (x))
#define SET_MDOMAIN_OUTPUT_HTOTAL(x)                   (g_stMDomainOutputData.usHTotal = (x))

#define SET_MDOMAIN_OUTPUT_VSTART(x)                   (g_stMDomainOutputData.usVStart = (x))
#define SET_MDOMAIN_OUTPUT_VBSTART(x)                  (g_stMDomainOutputData.usVBackStart = (x))
#define SET_MDOMAIN_OUTPUT_VHEIGHT(x)                  (g_stMDomainOutputData.usVHeight = (x))
#define SET_MDOMAIN_OUTPUT_VBHEIGHT(x)                 (g_stMDomainOutputData.usVBackHeight = (x))
#define SET_MDOMAIN_OUTPUT_VTOTAL(x)                   (g_stMDomainOutputData.usVTotal = (x))

#define GET_MDOMAIN_DISPLAY_MODE()                     (g_stMDomainInfo.enumDisplayMode)
#define SET_MDOMAIN_DISPLAY_MODE(x)                    (g_stMDomainInfo.enumDisplayMode = (x))
#define CLR_MDOMAIN_DISPLAY_MODE()                     (g_stMDomainInfo.enumDisplayMode = 0)

//--------------------------------------------------
// Macros of D Clock Freq. Info.
//--------------------------------------------------
#define GET_D_CLK_FREQ()                               (g_ulDClkFreq)


#define GET_MEMORY_DVF_SELECT()                        (g_stMDomainInfo.b3DVFSelect)


//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************

extern StructMDomainInfo g_stMDomainInfo;
extern StructTimingInfo g_stMDomainInputData;
extern StructDisplayInfo g_stMDomainOutputData;

extern DWORD g_ulDClkFreq;

//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
extern bit ScalerMDomainControl(void);
extern void ScalerMDomainCheckDisplayFormat(EnumDisplayRegion enumDisplayRegion);
extern void ScalerMDomainSetDisplayTimingGenBackground(EnumDisplayMode enumDisplayMode);

#if((_PIP_DISPLAY_SUPPORT == _ON) || (_PBP_LR_DISPLAY_SUPPORT == _ON))
extern void ScalerMDomainSetSubBackground(void);
extern void ScalerMDomainGetSubBackground(StructTimingFormat *pstTimingFormat);
#endif

#if((_PIP_DISPLAY_SUPPORT == _ON) || (_PBP_LR_DISPLAY_SUPPORT == _ON) || (_4P_DISPLAY_SUPPORT == _ON))
extern void ScalerMDomainSetSubActiveRegion(void);
#endif

extern void ScalerMDomainSetMemoryDataBit(BYTE ucColorDepth);
extern WORD ScalerMDomainGetVerticalAdjustLimit(EnumSourceTypeDef enumSourceTypeDef);

#if(_I_DITHER_SUPPORT == _ON)
extern BYTE ScalerMDomainGetColorDepth(void);
#endif

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
extern void ScalerMDomainAspectOriginMode(bit bOn);
#endif

#if(_OD_SUPPORT == _ON)
#if(_FRC_SUPPORT == _ON)
extern void ScalerMDomainReleaseFRCMemoryBW(EnumInputDataPath enumInputPath);
#endif
#endif

