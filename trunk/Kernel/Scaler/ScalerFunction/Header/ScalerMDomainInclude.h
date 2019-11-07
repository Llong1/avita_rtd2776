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
// ID Code      : ScalerMDomainInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Define Memory Frame Buffer
//--------------------------------------------------
#define _MEMORY_1_FRAME_BUFFER                          0
#define _MEMORY_2_FRAME_BUFFER                          1
#define _MEMORY_3_FRAME_BUFFER                          2


//--------------------------------------------------
// Macros of Input Info.
//--------------------------------------------------
#define GET_MEMORY_SELECT()                             (g_stMDomainInfo.b3MemorySelect)
#define SET_MEMORY_SELECT(x)                            (g_stMDomainInfo.b3MemorySelect = (x))
#define CLR_MEMORY_SELECT()                             (g_stMDomainInfo.b3MemorySelect = 0)

//--------------------------------------------------
// Macros of Memory Frame buffer
//--------------------------------------------------
#define GET_MEMORY_FRAME_BUFFER()                       (g_stMDomainInfo.b2MemoryFrameBuf)
#define SET_MEMORY_FRAME_BUFFER(x)                      (g_stMDomainInfo.b2MemoryFrameBuf = (x))
#define CLR_MEMORY_FRAME_BUFFER()                       (g_stMDomainInfo.b2MemoryFrameBuf = 0)

//--------------------------------------------------
// Macros of MDomain Input Info.
//--------------------------------------------------
#define GET_MDOMAIN_INPUT_H_POLARITY()                  (g_stMDomainInputData.b1HSP)
#define GET_MDOMAIN_INPUT_V_POLARITY()                  (g_stMDomainInputData.b1VSP)
#define GET_MDOMAIN_INPUT_INTERLACE_FLG()               (g_stMDomainInputData.b1Interlace)
#define GET_MDOMAIN_INPUT_VIDEO_FIELD()                 (g_stMDomainInputData.b1VideoField)
#define GET_MDOMAIN_INPUT_DATA_PATH()                   (g_stMDomainInputData.enumInputDataPath)
#define GET_MDOMAIN_INPUT_HFREQ()                       (g_stMDomainInputData.usHFreq)
#define GET_MDOMAIN_INPUT_HTOTAL()                      (g_stMDomainInputData.usHTotal)
#define GET_MDOMAIN_INPUT_HWIDTH()                      (g_stMDomainInputData.usHWidth)
#define GET_MDOMAIN_INPUT_HSTART()                      (g_stMDomainInputData.usHStart)
#define GET_MDOMAIN_INPUT_HSYNCWIDTH()                  (g_stMDomainInputData.usHSWidth)
#define GET_MDOMAIN_INPUT_VFREQ()                       (g_stMDomainInputData.usVFreq)
#define GET_MDOMAIN_INPUT_VTOTAL()                      (g_stMDomainInputData.usVTotal)
#define GET_MDOMAIN_INPUT_VHEIGHT()                     (g_stMDomainInputData.usVHeight)
#define GET_MDOMAIN_INPUT_VSTART()                      (g_stMDomainInputData.usVStart)
#define GET_MDOMAIN_INPUT_VSYNCWIDTH()                  (g_stMDomainInputData.usVSWidth)

//--------------------------------------------------
// Macros of MDomain Input info. modification
//--------------------------------------------------
#define SET_MDOMAIN_INPUT_STRUCTURE(x)                  (g_stMDomainInputData = (x))

#define SET_MDOMAIN_INPUT_HSTART(x)                     (g_stMDomainInputData.usHStart = (x))
#define SET_MDOMAIN_INPUT_HWIDTH(x)                     (g_stMDomainInputData.usHWidth = (x))
#define SET_MDOMAIN_INPUT_HTOTAL(x)                     (g_stMDomainInputData.usHTotal = (x))

#define SET_MDOMAIN_INPUT_VSTART(x)                     (g_stMDomainInputData.usVStart = (x))
#define SET_MDOMAIN_INPUT_VHEIGHT(x)                    (g_stMDomainInputData.usVHeight = (x))
#define SET_MDOMAIN_INPUT_VTOTAL(x)                     (g_stMDomainInputData.usVTotal = (x))

//--------------------------------------------------
// Macros of MDomain Output Info.
//--------------------------------------------------
#define GET_MDOMAIN_OUTPUT_DATA_PATH()                  (g_stMDomainOutputData.enumDisplayDataPath)

#define GET_MDOMAIN_OUTPUT_HSTART()                     (g_stMDomainOutputData.usHStart)
#define GET_MDOMAIN_OUTPUT_HBSTART()                    (g_stMDomainOutputData.usHBackStart)
#define GET_MDOMAIN_OUTPUT_HWIDTH()                     (g_stMDomainOutputData.usHWidth)
#define GET_MDOMAIN_OUTPUT_HBWIDTH()                    (g_stMDomainOutputData.usHBackWidth)
#define GET_MDOMAIN_OUTPUT_HTOTAL()                     (g_stMDomainOutputData.usHTotal)

#define GET_MDOMAIN_OUTPUT_VSTART()                     (g_stMDomainOutputData.usVStart)
#define GET_MDOMAIN_OUTPUT_VBSTART()                    (g_stMDomainOutputData.usVBackStart)
#define GET_MDOMAIN_OUTPUT_VHEIGHT()                    (g_stMDomainOutputData.usVHeight)
#define GET_MDOMAIN_OUTPUT_VBHEIGHT()                   (g_stMDomainOutputData.usVBackHeight)
#define GET_MDOMAIN_OUTPUT_VTOTAL()                     (g_stMDomainOutputData.usVTotal)

//--------------------------------------------------
// Macros of MDomain Input info. modification
//--------------------------------------------------

#define SET_MDOMAIN_OUTPUT_HSTART(x)                    (g_stMDomainOutputData.usHStart = (x))
#define SET_MDOMAIN_OUTPUT_HBSTART(x)                   (g_stMDomainOutputData.usHBackStart = (x))
#define SET_MDOMAIN_OUTPUT_HWIDTH(x)                    (g_stMDomainOutputData.usHWidth = (x))
#define SET_MDOMAIN_OUTPUT_HBWIDTH(x)                   (g_stMDomainOutputData.usHBackWidth = (x))
#define SET_MDOMAIN_OUTPUT_HTOTAL(x)                    (g_stMDomainOutputData.usHTotal = (x))

#define SET_MDOMAIN_OUTPUT_VSTART(x)                    (g_stMDomainOutputData.usVStart = (x))
#define SET_MDOMAIN_OUTPUT_VBSTART(x)                   (g_stMDomainOutputData.usVBackStart = (x))
#define SET_MDOMAIN_OUTPUT_VHEIGHT(x)                   (g_stMDomainOutputData.usVHeight = (x))
#define SET_MDOMAIN_OUTPUT_VBHEIGHT(x)                  (g_stMDomainOutputData.usVBackHeight = (x))
#define SET_MDOMAIN_OUTPUT_VTOTAL(x)                    (g_stMDomainOutputData.usVTotal = (x))

//--------------------------------------------------
// Macros of D Clock Freq. Info.
//--------------------------------------------------
#define GET_D_CLK_FREQ()                                (g_ulDClkFreq)
#define SET_D_CLK_FREQ(x)                               (g_ulDClkFreq = (x))

//--------------------------------------------------
// Macros of DVF
//--------------------------------------------------
#define GET_MEMORY_DVF_SELECT()                         (g_stMDomainInfo.b3DVFSelect)
#define SET_MEMORY_DVF_SELECT(x)                        (g_stMDomainInfo.b3DVFSelect = (x))
#define CLR_MEMORY_DVF_SELECT()                         (g_stMDomainInfo.b3DVFSelect = 0)

//--------------------------------------------------
// Macros of Memory Config
//--------------------------------------------------
#define GET_MEMORY_CONFIG()                             (g_stMDomainInfo.b2MemoryConf)
#define SET_MEMORY_CONFIG(x)                            (g_stMDomainInfo.b2MemoryConf = (x))
#define CLR_MEMORY_CONFIG()                             (g_stMDomainInfo.b2MemoryConf = 0)

//--------------------------------------------------
// Macros of Data Path
//--------------------------------------------------
#define GET_MDOMAIN_DISPLAY_MODE()                      (g_stMDomainInfo.enumDisplayMode)
#define SET_MDOMAIN_DISPLAY_MODE(x)                     (g_stMDomainInfo.enumDisplayMode = (x))
#define CLR_MDOMAIN_DISPLAY_MODE()                      (g_stMDomainInfo.enumDisplayMode = 0)

#if(_FRC_SUPPORT == _ON)
//--------------------------------------------------
// Macros of FRC Style
//--------------------------------------------------
#if(_MULTI_DISPLAY_MAX > 0x02)
#define GET_MDOMAIN_FRC_STYLE(x)                        (((x) & _INPUT_PATH_M1) ? (g_pstFRCInfo[0].b1PreFRCStyle) :\
                                                        (((x) & _INPUT_PATH_M2) ? (g_pstFRCInfo[1].b1PreFRCStyle) :\
                                                        (((x) & _INPUT_PATH_S1) ? (g_pstFRCInfo[2].b1PreFRCStyle) :\
                                                        (((x) & _INPUT_PATH_S2) ? (g_pstFRCInfo[3].b1PreFRCStyle) : (g_pstFRCInfo[0].b1PreFRCStyle)))))
#define SET_MDOMAIN_FRC_STYLE(x, y)                     (((x) & _INPUT_PATH_M1) ? (g_pstFRCInfo[0].b1PreFRCStyle = (y)) :\
                                                        (((x) & _INPUT_PATH_M2) ? (g_pstFRCInfo[1].b1PreFRCStyle = (y)) :\
                                                        (((x) & _INPUT_PATH_S1) ? (g_pstFRCInfo[2].b1PreFRCStyle = (y)) :\
                                                        (((x) & _INPUT_PATH_S2) ? (g_pstFRCInfo[3].b1PreFRCStyle = (y)) : (g_pstFRCInfo[0].b1PreFRCStyle = (y))))))
#elif(_MULTI_DISPLAY_MAX == 0x02)
#define GET_MDOMAIN_FRC_STYLE(x)                        (((x) & _INPUT_PATH_M1_M2) ? (g_pstFRCInfo[0].b1PreFRCStyle) : (g_pstFRCInfo[1].b1PreFRCStyle))
#define SET_MDOMAIN_FRC_STYLE(x, y)                     (((x) & _INPUT_PATH_M1_M2) ? (g_pstFRCInfo[0].b1PreFRCStyle = (y)) : (g_pstFRCInfo[1].b1PreFRCStyle = (y)))
#else
#define GET_MDOMAIN_FRC_STYLE(x)                        (g_pstFRCInfo[0].b1PreFRCStyle)
#define SET_MDOMAIN_FRC_STYLE(x, y)                     (g_pstFRCInfo[0].b1PreFRCStyle = (y))
#endif // End of #if(_MULTI_DISPLAY_MAX > 0x02)
#endif // End of #if(_FRC_SUPPORT == _ON)

//--------------------------------------------------
// Macros of OD use Info.
//--------------------------------------------------

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
#define GET_ASPECT_ORIGIN_MODE()                        (g_bAspectOriginMode)
#define SET_ASPECT_ORIGIN_MODE(x)                       (g_bAspectOriginMode = (x))
#endif


#define _DCLK_SPREAD_RANGE_MARGIN                       (1)

#define GET_MEMORY_DATA_BIT()                           (g_stMDomainInfo.b5DataBit)
#define SET_MEMORY_DATA_BIT(x)                          (g_stMDomainInfo.b5DataBit = (x))
#define CLR_MEMORY_DATA_BIT()                           (g_stMDomainInfo.b5DataBit = 0)

#if((_OD_SUPPORT == _ON) && (_FRC_SUPPORT == _ON))
//--------------------------------------------------
// Macros of Memory Bandwidth Info.
//--------------------------------------------------
#define GET_MDOMAIN_BW()                                (g_usUseMemoryBW)
#define SET_MDOMAIN_BW(x)                               (g_usUseMemoryBW = (x))
#define CLR_MDOMAIN_BW()                                (g_usUseMemoryBW = 0)

//--------------------------------------------------
// Macros of Memory Bandwidth
//--------------------------------------------------
#if(_MULTI_DISPLAY_MAX > 0x02)
#define GET_MEMORY_BW(x)                                (((x) & _INPUT_PATH_M1) ? (g_pstFRCInfo[0].usUseMemoryBW) :\
                                                        (((x) & _INPUT_PATH_M2) ? (g_pstFRCInfo[1].usUseMemoryBW) :\
                                                        (((x) & _INPUT_PATH_S1) ? (g_pstFRCInfo[2].usUseMemoryBW) :\
                                                        (((x) & _INPUT_PATH_S2) ? (g_pstFRCInfo[3].usUseMemoryBW) : (g_pstFRCInfo[0].usUseMemoryBW)))))
#define SET_MEMORY_BW(x, y)                             (((x) & _INPUT_PATH_M1) ? (g_pstFRCInfo[0].usUseMemoryBW = (y)) :\
                                                        (((x) & _INPUT_PATH_M2) ? (g_pstFRCInfo[1].usUseMemoryBW = (y)) :\
                                                        (((x) & _INPUT_PATH_S1) ? (g_pstFRCInfo[2].usUseMemoryBW = (y)) :\
                                                        (((x) & _INPUT_PATH_S2) ? (g_pstFRCInfo[3].usUseMemoryBW = (y)) : (g_pstFRCInfo[0].usUseMemoryBW = (y))))))
#define CLR_MEMORY_BW(x)                                (((x) & _INPUT_PATH_M1) ? (g_pstFRCInfo[0].usUseMemoryBW = 0) :\
                                                        (((x) & _INPUT_PATH_M2) ? (g_pstFRCInfo[1].usUseMemoryBW = 0) :\
                                                        (((x) & _INPUT_PATH_S1) ? (g_pstFRCInfo[2].usUseMemoryBW = 0) :\
                                                        (((x) & _INPUT_PATH_S2) ? (g_pstFRCInfo[3].usUseMemoryBW = 0) : (g_pstFRCInfo[0].usUseMemoryBW = 0)))))
#elif(_MULTI_DISPLAY_MAX == 0x02)
#define GET_MEMORY_BW(x)                                (((x) == _INPUT_PATH_M1_M2) ? (g_pstFRCInfo[0].usUseMemoryBW) : (g_pstFRCInfo[1].usUseMemoryBW))
#define SET_MEMORY_BW(x, y)                             (((x) == _INPUT_PATH_M1_M2) ? (g_pstFRCInfo[0].usUseMemoryBW = (y)) : (g_pstFRCInfo[1].usUseMemoryBW = (y)))
#define CLR_MEMORY_BW(x)                                (((x) == _INPUT_PATH_M1_M2) ? (g_pstFRCInfo[0].usUseMemoryBW = 0) : (g_pstFRCInfo[1].usUseMemoryBW = 0))
#else
#define GET_MEMORY_BW(x)                                (g_pstFRCInfo[0].usUseMemoryBW)
#define SET_MEMORY_BW(x, y)                             (g_pstFRCInfo[0].usUseMemoryBW = (y))
#define CLR_MEMORY_BW(x)                                (g_pstFRCInfo[0].usUseMemoryBW = 0)
#endif
#endif // End of #if((_OD_SUPPORT == _ON) && (_FRC_SUPPORT == _ON))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_FRC_SUPPORT == _ON)
typedef struct
{
    BYTE b1PreFRCStyle : 1;

#if(_OD_SUPPORT == _ON)
    WORD usUseMemoryBW;
#endif
}StructFRCInfo;
#endif // End of #if(_FRC_SUPPORT == _ON)

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern DWORD g_ulDClkFreq;

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
extern bit g_bAspectOriginMode;
#endif

#if((_OD_SUPPORT == _ON) || (_FRC_SUPPORT == _ON))
extern WORD g_usDVFreq;
#endif

#if((_OD_SUPPORT == _ON) && (_FRC_SUPPORT == _ON))
extern DWORD g_ulFRCMemoryRemainBW;
#endif

#if(_FRC_SUPPORT == _ON)
extern StructFRCInfo g_pstFRCInfo[_MULTI_DISPLAY_MAX];
#endif


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if((_FRAME_SYNC_LINE_BUFFER_SUPPORT == _ON) || (_FREESYNC_SUPPORT == _ON))
#if(_FRC_SUPPORT == _ON)
extern bit ScalerMDomainFSLineBufferDclkDvtotalCheck(void);
#endif
#endif

extern BYTE ScalerMDomainGetDpllSscgDivMode(void);
extern void ScalerMDomainFSVgipDoubleBufferApply(void);
extern void ScalerMDomainSetDisplayTimingGenBackground(EnumDisplayMode enumDisplayMode);

#if((_PIP_DISPLAY_SUPPORT == _ON) || (_PBP_LR_DISPLAY_SUPPORT == _ON))
extern void ScalerMDomainSetSubBackground(void);
#endif

#if((_PIP_DISPLAY_SUPPORT == _ON) || (_PBP_LR_DISPLAY_SUPPORT == _ON) || (_4P_DISPLAY_SUPPORT == _ON))
extern void ScalerMDomainSetSubActiveRegion(void);
#endif

extern BYTE ScalerMDomainMemorySelectConfirm(void);
extern void ScalerMDomainSetMemoryDataBit(BYTE ucColorDepth);

extern DWORD ScalerMDomainGetDisplayActiveRegion(void);

#if(_FRC_SUPPORT == _ON)
extern DWORD ScalerMDomainGetCurBW(void);
#endif

#if(_OD_SUPPORT == _ON)
extern void ScalerMDomainODUseBitInitial(void);
extern WORD ScalerMDomainODCalculateMemoryUseSpace(BYTE ucODbit);
extern WORD ScalerMDomainODCalculateMemoryUseBW(BYTE ucODbit);

#if(_FRC_SUPPORT == _ON)
extern void ScalerMDomainReleaseFRCMemoryBW(EnumInputDataPath enumInputPath);
#endif

#endif // End of #if(_OD_SUPPORT == _ON)

extern void ScalerMDomainSetDisplayTimingGen(EnumDisplayDataPath enumDisplayDataPath);
