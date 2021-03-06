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
// ID Code      : RTD2014Key.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RTD_KEY__

#include "UserCommonInclude.h"
#include <stdio.h>                /* prototype declarations for I/O functions */
#if(_OSD_TYPE == _REALTEK_2014_OSD)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of Key Mask
//--------------------------------------------------
#define _RELEASE_KEY_MASK                           0x00
#define _POWER_KEY_MASK                             0x01
#define _MENU_KEY_MASK                              0x02
#define _RIGHT_KEY_MASK                             0x04
#define _LEFT_KEY_MASK                              0x08
#define _EXIT_KEY_MASK                              0x10
#define _KEY5_MASK                                  0x20
#define _KEY6_MASK                                  0x40
#define _KEY7_MASK                                  0x80

#define _POWER_RIGHT_KEY_MASK                       (_POWER_KEY_MASK | _RIGHT_KEY_MASK)
#define _POWER_MENU_KEY_MASK                        (_POWER_KEY_MASK | _MENU_KEY_MASK)
#define _POWER_LEFT_RIGHT_KEY_MASK                  (_POWER_KEY_MASK | _LEFT_KEY_MASK | _RIGHT_KEY_MASK)

//--------------------------------------------------
// Definitions of IR Key Code
//--------------------------------------------------

#if(_IR_SUPPORT == _IR_HW_SUPPORT)

#if 0
#define _IR_CODE_HEADER							0xBF00
#define _IR_CODE_KEY_POWER                       0xFF00
#define _IR_CODE_KEY_MENU                     0xEF10
#define _IR_CODE_KEY_RIGHT                  0xED12
#define _IR_CODE_KEY_LEFT                      0xEE11
#define _IR_CODE_KEY_EXIT                  0xEA15
#else
#define _IR_CUSTOMER_CODEA   0xCD32
#define _IR_CUSTOMER_CODEB   0xCC33
//#define _IR_CODE_HEADER							0xBF00
#define _IR_CODE_KEY_POWER          0xFFFF     //   0xEE11//        0xFF00
#define _IR_CODE_KEY_MENU                    0xED12//      // 0xEF10
#define _IR_CODE_KEY_RIGHT                   0xE916//       //0xED12
#define _IR_CODE_KEY_LEFT                         0xEB14//  //0xEE11
#define _IR_CODE_KEY_EXIT                         0xE619  //0xEA15
#define _IR_CODE_KEY_ENTER                         0xEA15  //0xEA15
#define _IR_CODE_KEY_FUN1                       0xE41B  //0xEA15
#define _IR_CODE_KEY_FUN2                         0xE31C  //0xEA15
#define _IR_CODE_KEY_FUN3                         0xE21D  //0xEA15
#define _IR_CODE_KEY_POWER_ON                         0xEE11 
#define _IR_CODE_KEY_POWER_OFF                        0xE01F 
#endif


#endif // End of #if(_IR_SUPPORT == _IR_HW_SUPPORT)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE g_ucKeyStatePrev;
BYTE g_ucKeyStateCurr;

#if(_AD_KEY_SUPPORT == _ON)
BYTE g_ucBackupKeyState = 0xFF;
#endif

 BYTE g_stFacFlag;
// bit  g_stPFlag = _FALSE;
//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void UserInterfaceKeyHandler(void);
void RTDKeyInitial(void);
bit RTDKeyScanReady(void);
BYTE RTDKeyScan(void);
bit RTDKeyPowerKeyProc(void);
void RTDKeyPowerKeyMix(void);
void RTDKeyMessageProc(void);
void RTDKeyMessageConvert(BYTE ucKeyMask, BYTE ucKeyMsg);
bit RTDKeySpecialProc(BYTE ucKeyMask);

void RTDKeyHoldKeyTimerCancel(void);
void RTDKeyHoldKeyCheck(void);

#if(_IR_SUPPORT == _IR_HW_SUPPORT)
BYTE RTDIRKeyScan(void);
#endif
       
//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Key Handler, executed in the main loop.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceKeyHandler(void)
{
    // Clear the key message
    if(GET_KEYMESSAGE() != _HOLD_KEY_MESSAGE)
    {
        SET_KEYMESSAGE(_NONE_KEY_MESSAGE);
    }

    if(RTDKeyScanReady() == _TRUE)
    {
        // Store previous key state
        g_ucKeyStatePrev = g_ucKeyStateCurr;

        // Get current key state
        g_ucKeyStateCurr = RTDKeyScan();

        // Power key process, return if power key is pressed
        if(RTDKeyPowerKeyProc() == _TRUE)
        {
            return;
        }
        // Convert key state to key message, store in (ucKeyNotify)
        RTDKeyMessageProc();
    }
}

//--------------------------------------------------
// Description  : Key intial.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDKeyInitial(void)
{
    CLR_KEYSCANREADY();
    CLR_KEYSCANSTART();
}

//--------------------------------------------------
// Description  : Key scan ready process. We wait 0.02 sec in order to keep the keypad debounce
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit RTDKeyScanReady(void)
{
    if((GET_KEYSCANSTART() == _TRUE) &&
       (GET_KEYSCANREADY() == _TRUE))
    {
        return _TRUE;
    }
    else if(GET_KEYSCANSTART() == _FALSE)
    {
        // Set Scan start flag.
        SET_KEYSCANSTART();

        // SET_KEYSCANREADY();
        // Wait 0.02 sec in order to keep the keypad debounce
      ScalerTimerReactiveTimerEvent(SEC(0.01), _USER_TIMER_EVENT_KEY_SCAN_READY);
   
        return _FALSE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get key status
// Input Value  : None
// Output Value : Return Key status
//--------------------------------------------------
BYTE RTDKeyScan(void)
{
    BYTE ucKeyState = 0;
    BYTE ucVoltage0 = 0;
    BYTE ucVoltage1 = 0;
    BYTE ucVoltage2 = 0;
    BYTE ucVoltage3 = 0;

#if(_AD_KEY_SUPPORT == _ON)// go here
    ucVoltage0 = PCB_ADKEY0();
    ucVoltage1 = PCB_ADKEY1();
    ucVoltage2 = PCB_ADKEY2();
    ucVoltage3 = PCB_ADKEY3();

    PCB_KEY_STATE(ucVoltage0, ucVoltage1, ucVoltage2, ucVoltage3, ucKeyState);		
#if(_IR_SUPPORT == _IR_HW_SUPPORT)
    if(ucKeyState == 0x00)
    {
        ucKeyState = RTDIRKeyScan();// 0x00
     //   if(ucKeyState > 0)
	//	printf("ucKeyState = %bd \r\n" , ucKeyState);
    }
#endif // End of #if(_IR_SUPPORT == _IR_HW_SUPPORT)

    if(g_ucBackupKeyState == ucKeyState)
    {
          if(GET_KEYREPEATENABLE() != _ON)
        {
            RTDKeyInitial();
        }
        return g_ucBackupKeyState;
    }
    else
    {
        g_ucBackupKeyState = ucKeyState;
        //ucKeyState = 0;
    }

#else///////////////////////////////////
    PCB_KEY_STATE(ucVoltage0, ucVoltage1, ucVoltage2, ucVoltage3, ucKeyState);
#endif // End of #if(_AD_KEY_SUPPORT == _ON)


    if(ucKeyState != 0)
    {
        RTDKeyInitial();
    }
    return ucKeyState;
}

//--------------------------------------------------
// Description  : Power key process
// Input Value  : None
// Output Value : Return _TRUE if power key is pressed
//--------------------------------------------------
bit RTDKeyPowerKeyProc(void)
{
    if((g_ucKeyStateCurr & _POWER_KEY_MASK) != 0)
    {
        if(((g_ucKeyStatePrev ^ g_ucKeyStateCurr) & _POWER_KEY_MASK) != 0)
        {
            RTDKeyPowerKeyMix();

            if(SysPowerGetPowerStatus() == _POWER_STATUS_OFF)
            {
                SET_OSD_STATE(_MENU_NONE);
                SET_OSD_IN_FACTORY_MENU_STATUS(_FALSE);
                SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);
              //  PCB_USB_POWER(GET_USB_POWER_STATUS());
            }
            else
            {
                 
                   SysPowerSetTargetPowerStatus(_POWER_STATUS_OFF);
                    
            }

            return _TRUE;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : We can add some settings here while combo key with power key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDKeyPowerKeyMix(void)
{
    switch(g_ucKeyStateCurr)
    {
        case _POWER_RIGHT_KEY_MASK:
            break;

        case _POWER_MENU_KEY_MASK:
            break;

        case _POWER_LEFT_RIGHT_KEY_MASK:
            break;

        default:
            break;
    }
}


//--------------------------------------------------
// Description  : Convert keypad status into key message, stores in ucKeyNotify
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDKeyMessageProc(void)
{
    switch(g_ucKeyStateCurr)
    {
        case _MENU_KEY_MASK:
            CLR_KEYREPEATENABLE();
            RTDKeyMessageConvert(_MENU_KEY_MASK, _MENU_KEY_MESSAGE);
            break;

        case _RIGHT_KEY_MASK:
            RTDKeyMessageConvert(_RIGHT_KEY_MASK, _RIGHT_KEY_MESSAGE);
            break;

        case _LEFT_KEY_MASK:
            RTDKeyMessageConvert(_LEFT_KEY_MASK, _LEFT_KEY_MESSAGE);
            break;

        case _EXIT_KEY_MASK:
            CLR_KEYREPEATENABLE();
            RTDKeyMessageConvert(_EXIT_KEY_MASK, _EXIT_KEY_MESSAGE);
            break;
	  case _KEY5_MASK:
            CLR_KEYREPEATENABLE();
            RTDKeyMessageConvert(_KEY5_MASK, _5_KEY_MESSAGE);
            break;		
        case _KEY6_MASK:
            CLR_KEYREPEATENABLE();
            RTDKeyMessageConvert(_KEY6_MASK, _6_KEY_MESSAGE);
            break;
          case _KEY7_MASK:
              CLR_KEYREPEATENABLE();
            RTDKeyMessageConvert(_KEY7_MASK, _7_KEY_MESSAGE);
            break;			
        default:
            if((g_ucKeyStateCurr == _RELEASE_KEY_MASK) &&
               (g_ucKeyStatePrev != _RELEASE_KEY_MASK))
            {

                RTDKeyHoldKeyCheck(); // Check key release
            }
            else{

            }

            CLR_KEYREPEATSTART();
            CLR_KEYREPEATENABLE();
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_KEY_REPEAT_ENABLE);
            break;
    }
}

//--------------------------------------------------
// Description  : Key message translation
// Input Value  : ucKeyMask     --> Key mask
//                ucKeyMsg      --> Key message
// Output Value : None
//--------------------------------------------------
void RTDKeyMessageConvert(BYTE ucKeyMask, BYTE ucKeyMsg)
{
    // Key different
    if((g_ucKeyStatePrev != g_ucKeyStateCurr) && (ucKeyMask == g_ucKeyStateCurr))
    {
        // KeyLock function
        if (RTDKeySpecialProc(ucKeyMask) == _FALSE)
        {
            SET_KEYMESSAGE(ucKeyMsg);
            RTDKeyHoldKeyTimerCancel();
        }
    }
    else // Key the same
    {
        if(GET_KEYREPEATENABLE() == _TRUE)
        {
            if(GET_KEYREPEATSTART() == _TRUE)
            {
                SET_KEYMESSAGE(ucKeyMsg);
            }
            else
            {
                // Set repeat key after 20ms.
                ScalerTimerActiveTimerEvent(SEC(0.5), _USER_TIMER_EVENT_KEY_REPEAT_ENABLE);
            }
        }
    }
}


//--------------------------------------------------
// Description  :  for special key check
// Input Value  : scan Key data
// Output Value : None
//--------------------------------------------------
bit RTDKeySpecialProc(BYTE ucKeyMask)
{
    if((GET_OSD_STATE() == _MENU_NONE) && (ucKeyMask == _LEFT_KEY_MASK))
    {
#if 1//#if(_DP_SUPPORT == _ON)
       ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_FACTORY_MODE);
       SET_KEY_HOLD();
       CLR_KEYREPEATENABLE();
        return _TRUE;
#endif
    }
    else if((GET_OSD_STATE() == _MENU_NONE) && (ucKeyMask == _KEY5_MASK))
    {
    //    ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISPLAYMODE_SELECT);// resume input osd
     //   SET_KEY_HOLD();
     //   CLR_KEYREPEATENABLE();
      //  return _TRUE;
    }
   else if((GET_OSD_STATE() != _MENU_NONE) && (ucKeyMask == _KEY7_MASK))
    {
        g_stFacFlag++;
    
#if(_DEBUG_MESSAGE_IR == _ON)
        DebugMessageIR("g_stFacFlag",g_stFacFlag);
#endif // End of #if(_DEBUG_MESSAGE_IR == _ON)
         ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_FACTORY_MODE);
         SET_KEY_HOLD();
         CLR_KEYREPEATENABLE();

       if(g_stFacFlag>=10)//5s
        {
            RTDFactoryMainMenu();
            g_stFacFlag=0;
       }
    
        return _TRUE;
    
    }
#if 0
#if(_VGA_SUPPORT == _ON)
    // Press Exit key for 3 sec to do Auto color
    else if((GET_OSD_STATE() == _MENU_NONE) &&
            (SysVgaGetRegion() != _DISPLAY_RGN_NONE) &&
            (GET_FAIL_SAFE_MODE(ScalerRegionGetIndex(SysVgaGetRegion())) == _FALSE) &&
            (SysRegionGetDisplayState(SysVgaGetRegion()) == _DISPLAY_STATE_ACTIVE))
    {
    
        if (ucKeyMask == _EXIT_KEY_MASK)
        {
            ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_DO_AUTO_COLOR);
            SET_KEY_HOLD();
            CLR_KEYREPEATENABLE();
            return _TRUE;
           
        }
    }
#endif

	  else if((GET_OSD_STATE() == _MENU_NONE) && (ucKeyMask == _KEY5_MASK))// burn in pattern
	  {
		  ScalerTimerActiveTimerEvent(SEC(5), _USER_TIMER_EVENT_BURN_IN);
		  SET_KEY_HOLD();
		  CLR_KEYREPEATENABLE();
		  return _TRUE;
	  }
	 
#endif
    return _FALSE;
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDKeyHoldKeyTimerCancel(void)
{
    if(GET_KEY_HOLD() == _TRUE)
    {
        CLR_KEY_HOLD();

        // list all off hold key timer event here!!!
        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_DO_AUTO_COLOR);
#if(_DP_SUPPORT == _ON)
        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_DP_VERSION_SELECT);
#endif

        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISPLAYMODE_SELECT);

	// ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_BURN_IN);// cancel burn in

    }
}

//--------------------------------------------------
// Description  : Hold Key check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDKeyHoldKeyCheck(void)
{
    if(GET_KEY_HOLD() == _TRUE)
    {
        switch (g_ucKeyStatePrev)
        {
            case _EXIT_KEY_MASK:
                SET_KEYMESSAGE(_EXIT_KEY_MESSAGE);
                break;
            case _MENU_KEY_MASK:
                SET_KEYMESSAGE(_MENU_KEY_MESSAGE);
                break;
            case _RIGHT_KEY_MASK:
                SET_KEYMESSAGE(_RIGHT_KEY_MESSAGE);
                break;
            case _LEFT_KEY_MASK:
                SET_KEYMESSAGE(_LEFT_KEY_MESSAGE);
                break;
		 case _KEY5_MASK:
                SET_KEYMESSAGE(_5_KEY_MESSAGE);
                break;
		case _KEY6_MASK:
                SET_KEYMESSAGE(_6_KEY_MESSAGE);
                break;
	        case _KEY7_MASK:
                SET_KEYMESSAGE(_7_KEY_MESSAGE);
             break;	
            default:
                break;
        }
        RTDKeyHoldKeyTimerCancel();
    }
}

#if(_IR_SUPPORT == _IR_HW_SUPPORT)
//--------------------------------------------------
// Description  : IR Key Scan
// Input Value  : None
// Output Value : Key Mask
//--------------------------------------------------
BYTE RTDIRKeyScan(void)
{
    BYTE pucIRCodeBuffer[8] = {0};
    WORD usKeyCode = 0;
    BYTE ucKeyState = 0;

    if(ScalerIRHWModeGetData(pucIRCodeBuffer) == _TRUE)
    {
#if(_IR_PROTOCAL == _IR_NEC_DTV328)

       usKeyCode = (WORD)((((WORD)pucIRCodeBuffer[2]) << 8) | pucIRCodeBuffer[3]);
#if 0// alant debug
        if((pucIRCodeBuffer[0] == ~(pucIRCodeBuffer[1])) && (usKeyCode == _IR_CODE_HEADER))
        {
            usKeyCode = (((WORD)pucIRCodeBuffer[0]) << 8) + pucIRCodeBuffer[1];
        }
#else
        
        if((pucIRCodeBuffer[0] == ~(pucIRCodeBuffer[1])) && (usKeyCode == _IR_CUSTOMER_CODEA))
        {
 
               usKeyCode = (WORD)((((WORD)pucIRCodeBuffer[0]) << 8) | pucIRCodeBuffer[1]);
#if((_MODEL_TYPE != _YLI55161) && (_MODEL_TYPE != _KUI32171))	  ///Wesley180309_IR A-Side/B-Side Switch         			   
              if(bIRoption == _ON)//_OFF)//low
		{
         
                    //do nothing
          	}
		else{
                       if(_IR_CODE_KEY_POWER_ON ==usKeyCode || 
                       _IR_CODE_KEY_POWER_OFF ==usKeyCode )
                        {
                                  ///return _POWER_KEY_MASK;
                       }
		        
			    else 
                       {
                          return ucKeyState;
			  }
		}	 
#endif        
#if(_DEBUG_MESSAGE_IR == _ON)
    //    DebugMessageIR("usKeyCode",usKeyCode);
#endif // End of #if(_DEBUG_MESSAGE_IR == _ON)
        }
	 else if((pucIRCodeBuffer[0] == ~(pucIRCodeBuffer[1])) && (usKeyCode == _IR_CUSTOMER_CODEB))
        {
             usKeyCode = (WORD)((((WORD)pucIRCodeBuffer[0]) << 8) | pucIRCodeBuffer[1]);
#if((_MODEL_TYPE != _YLI55161) && (_MODEL_TYPE != _KUI32171))	  ///Wesley180309_IR A-Side/B-Side Switch 
         if(bIRoption ==_OFF)// _ON)
            {
         
		     //do nothing
         	}
		 else{
                     if(_IR_CODE_KEY_POWER_ON ==usKeyCode || 
                       _IR_CODE_KEY_POWER_OFF ==usKeyCode )
                        {
                                  ///return _POWER_KEY_MASK;
                       }
		        
			    else 
                       {
                          return ucKeyState;
			  }

		 }
#endif         
 #if(_DEBUG_MESSAGE_IR == _ON)
 //       DebugMessageIR("usKeyCode",usKeyCode);
#endif // End of #if(_DEBUG_MESSAGE_IR == _ON)
        }
#endif		
		else {
			return  ucKeyState;

			}
		
#elif(_IR_PROTOCAL == _IR_SONY_B102P)
        usKeyCode = (((WORD)pucIRCodeBuffer[0]) << 8) + pucIRCodeBuffer[1];

#elif(_IR_PROTOCAL == _IR_PHILIPS_RC6)
        usKeyCode = (((WORD)pucIRCodeBuffer[2]) << 8) + pucIRCodeBuffer[3];

#endif // End of #if(_IR_PROTOCAL == _IR_NEC_DTV328)

        switch(usKeyCode)
        {
          case _IR_CODE_KEY_POWER_ON:
               
            if(SysPowerGetPowerStatus() == _POWER_STATUS_OFF )
            {
                ucKeyState = _POWER_KEY_MASK;
            }
            else
            {

            

                if(SysPowerGetPowerStatus() == _POWER_STATUS_SAVING) 
                 {
                    PCB_LED_ON();
                    SET_OSD_STATE(_MENU_NONE);
                    SET_OSD_IN_FACTORY_MENU_STATUS(_FALSE);
                    SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);
             	      SET_FORCE_POW_SAV_STATUS(_FALSE);
		 	UserAdjustRegionInputPort(GET_OSD_SYSTEM_DISPLAY_REGION(), GET_OSD_1P_INPUT_SOURCE());
                 
                }
            }     

            
 
          break;
           case _IR_CODE_KEY_POWER_OFF:
            if(SysPowerGetPowerStatus() != _POWER_STATUS_OFF)
            {
                ucKeyState = _POWER_KEY_MASK;
            }
          break;
            case _IR_CODE_KEY_POWER:
                ucKeyState = _POWER_KEY_MASK;
                break;

            case _IR_CODE_KEY_MENU:
                 if(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)
            {
             //   SET_OSD_POWER_SAVING_SHOW_SOURCE(_TRUE);

                if((SysPowerGetPowerStatus() == _POWER_STATUS_SAVING) || (SysPowerGetPowerStatus() == _POWER_STATUS_NOSUPPORT_SAVING))
                {
                    PCB_LED_ON();
                   // PCB_USB_POWER(GET_USB_POWER_STATUS());
                    SET_FORCE_POW_SAV_STATUS(_FALSE);  
                    SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);
                  	UserAdjustRegionInputPort(GET_OSD_SYSTEM_DISPLAY_REGION(), GET_OSD_1P_INPUT_SOURCE());
                    ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_SHOW_MAIN_MENU);
                }
            }
               else{
                  
			if(GET_OSD_STATE() == _MENU_NONE)
		       ucKeyState = _MENU_KEY_MASK;
                }
                break;

            case _IR_CODE_KEY_RIGHT:
                ucKeyState = _RIGHT_KEY_MASK;
                break;

            case _IR_CODE_KEY_LEFT:
                ucKeyState = _LEFT_KEY_MASK;
                break;

            case _IR_CODE_KEY_EXIT:
                ucKeyState = _EXIT_KEY_MASK;
                break;
		case _IR_CODE_KEY_ENTER:
			if(GET_OSD_STATE() != _MENU_NONE)
			ucKeyState = _MENU_KEY_MASK;
		break;
        case _IR_CODE_KEY_FUN3:
             ucKeyState = _KEY7_MASK;
           break;
            default:
          //      ucKeyState = 0x00;
                break;
        }
    }

    return ucKeyState;
}
#endif // End of #if(_IR_SUPPORT == _IR_HW_SUPPORT)

#endif//#if(_OSD_TYPE == _REALTEK_2014_OSD)
