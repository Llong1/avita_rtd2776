#include "UserCommonInclude.h"
#include "uart.h"
#include <stdio.h>                /* prototype declarations for I/O functions */
#include <string.h>
#include <stdlib.h>
#include "w74m00av.h" 
#if(_UART_SUPPORT == _ON)
///////////////////////////////

// set
void s_help(char *params);
void s_power(char *para);
void s_contrast(char *para) ;
void s_brightness(char *para) ;
void s_sharpness(char *para) ;
void s_backlight(char *para) ;
void s_reset(char *para) ;
void s_reset(char *para) ;
void s_colortemp(char *para) ;
void s_tiling(char*para);
void s_aspect(char*para);
void s_pattern(char*para);
void s_rootkey(char*para);
void s_secureboot(char *para);
void s_pq(char* para);
void s_gamma(char* para);
void s_gdata(char*para);

void g_colorinfo(char*para);
// get
void g_power(char *para);
void g_contrast(char *para) ;
void g_brightness(char* para);
void g_sharpness(char *para) ;
void g_backlight(char *para) ;
void g_colortemp(char *para) ;
void g_aspect(char*para);
void g_paneltime(char*para);
void g_nvram(char*para);


char acRecvBuf[MAX_BUFF_SIZE]={0};

BYTE g_pucUartData[MAX_BUFF_SIZE]={0};
BYTE gB_RcvCount=0 ;  // alant add
BYTE gB_RcvStatus=RCV_EMPTY;
//BYTE gB_RcvComplete=0;
BYTE gB_dummy ;
#define TEST_ARGS_SPLIT " "


///////////////////////////////////////
const struct command commands[] = {

  {"s_contrast", s_contrast, "s_contrast 0~100\r\n"},
  {"s_brightness", s_brightness, "s_brightness 0~100\r\n"},
  {"s_sharpness", s_sharpness, "s_sharpness 0~4\r\n"},
  {"s_backlight", s_backlight, "s_backlight 0~100\r\n"},
  {"s_power",s_power,"s_power 0/1\r\n"} ,
  {"reset",s_reset,"reset:user reset\r\n"} ,
  {"s_colortemp", s_colortemp, "s_colortemp 0~5\r\n"},
  {"s_tiling", s_tiling, "s_tiling row column pos\r\n"},
  {"s_aspect", s_aspect, "s_aspect 0~4\r\n"},
  {"s_pattern", s_pattern, "s_pattern 0/1 r(0~255) g(0~255) b(0~255)\r\n"}, 
  {"s_rootkey", s_rootkey, "s_rootkey \r\n"},
  {"s_secureboot", s_secureboot, "s_rootkey \r\n"},
  {"s_pq", s_pq, "s_pq 0~1\r\n"},
  {"s_gamma", s_gamma, "s_gamma 0~6\r\n"},


  {"g_colorinfo", g_colorinfo, "g_colorinfo : colorspace colorrange colorimetry \r\n"},
   
  {"g_colortemp", g_colortemp, "g_colortemp:get colotemp value\r\n"},
  {"g_power",g_power,"g_power:get power status\r\n"} ,
  {"g_contrast",g_contrast,"g_contrast:get contrast value\r\n"} ,
  {"g_brightness",g_brightness,"g_brightness:get brightness value\r\n"} ,
  {"g_sharpness", g_sharpness, "g_sharpness:get sharpness value \r\n"},
  {"g_backlight", g_backlight, "g_backlight:get backlight value\r\n"},
  {"g_aspect", g_aspect, "g_aspect:get aspect ratio value\r\n"},
  {"g_paneltime", g_paneltime, "g_paneltime:get panel time (hour min)\r\n"},
  {"g_nvram", g_nvram, "g_nvram:idx(0~5), channel(0~2)\r\n"},
  {"s_gdata", s_gdata, "s_gdata \r\n"},

  {"help", s_help,"help:show function\r\n"} ,

   {NULL, NULL, NULL}
	
};


static void sendOK(void){
	printf("OK\r\n");	 


}
static void sendERR(void){ // para error
	printf("ERR 1\r\n");	 

}
static void sendEmpty(void){
	printf("\r\n");	 

}
/*
static void sendUnsupport(void){

    printf("ERR 0\r\n");	 

}*/
void g_colorinfo(char*para)
{

	para= NULL;
//   BYTE u32Para;


  printf("%bd %bd %bd \r\n", 
  ScalerColorGetColorSpace(SysRegionGetPortType(GET_OSD_SYSTEM_DISPLAY_REGION())) ,
  ScalerColorGetRGBQuantizationRange(SysRegionGetPortType(GET_OSD_SYSTEM_DISPLAY_REGION())), 
  ScalerColorGetColorimetry(SysRegionGetPortType(GET_OSD_SYSTEM_DISPLAY_REGION()))
);
  // if(u32Para) {
  //    ScalerColorSetRGBLimitRange(SysRegionGetPortType(GET_OSD_SYSTEM_DISPLAY_REGION()), _TRUE);
    //    sendOK(); 
  // 	}
  // else{
 //ScalerColorSetRGBLimitRange(SysRegionGetPortType(GET_OSD_SYSTEM_DISPLAY_REGION()), _FALSE);
   //  sendOK(); 
  // }

}
void s_pattern(char*para)
{
WORD gB_on=0 ,gB_r=0, gB_g=0, gB_b=0 ; 
	
   if(para==NULL) return ;

	sscanf(para,  "%d" TEST_ARGS_SPLIT "%d" TEST_ARGS_SPLIT "%d" TEST_ARGS_SPLIT "%d",			 
	&gB_on ,  &gB_r, &gB_g, &gB_b); // format string

   if(gB_on) 
   	{
   
        ScalerDDomainPatternGenAdjustColor(gB_r, gB_g, gB_b);
        ScalerDDomainPatternGenEnable(_ENABLE);
        ScalerDDomainBackgroundEnable(_DISPLAY_PATH_ALL, _DISABLE);
        sendOK(); 
   	}
   else
   {
   ScalerDDomainPatternGenEnable(_DISABLE);
     sendOK(); 
   }

}
void g_paneltime(char *para) 
{
 // WORD u32Para;
  para= NULL;
 // u32Para =GET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort());
  printf("%d %bd\r\n" , GET_PANEL_TIME_HOUR() , GET_PANEL_TIME_MIN());  

}


void g_aspect(char *para) 
{
  WORD u32Para;
  para= NULL;
  u32Para =GET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort());
  printf("%d\r\n" , u32Para);  

}

void s_aspect(char*para)
{

  WORD u32Para;

   if (para == NULL)
   {
	   return;
   }

  u32Para = atoi(para);

  if(u32Para>=0 && u32Para<=4)
   {
	  SET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort(), u32Para);
	  UserAdjustResetDisplayByPort(GET_OSD_SYSTEM_DISPLAY_REGION());
	  SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_INPUTPORTDATA_MSG);
      sendOK(); 
  }
  else{
 sendERR();

  }


}
void s_rootkey(char*para)
{

   //WORD u32Para;
   para = NULL;
   WB_RPMC_WrRootKey(0,"WINDBOND");
   sendOK(); 

}

void s_tiling(char*para)
{
   
   if(para==NULL) return ;
   
   sscanf(para,  "%d" TEST_ARGS_SPLIT "%d" TEST_ARGS_SPLIT "%d",			
     &gB_hnum, &gB_vnum, &gB_pos); // format string

 // printf("%d %d %d\r\n",gB_hnum,gB_vnum, gB_pos); 
    SET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort(), 0); // full mode

    UserAdjustResetDisplayByPort(GET_OSD_SYSTEM_DISPLAY_REGION());


}

void s_colortemp(char *para) 
{
   WORD u32Para;

    if (para == NULL)
    {
        return;
    }

   u32Para = atoi(para);

   if(u32Para>=0 && u32Para<=5)
    {
           SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), u32Para);
           RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
          UserAdjustContrast(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_CONTRAST(GET_OSD_SELECT_REGION()));
		   SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
           sendOK(); 
   }
   else{
  sendERR();

   }


}
void g_colortemp(char *para) 
{
  WORD u32Para;
  para= NULL;
  u32Para = GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION());
  printf("%d\r\n" , u32Para);  

}
void s_reset(char *para) 
{
  para =NULL;
  OsdDispOsdReset();
  sendOK();

}
void g_power(char *para) // power command
{

    para =NULL;
      
   if(SysPowerGetPowerStatus() != _POWER_STATUS_OFF) { 
        printf("1\r\n");                    
       }
   else{

      printf("0\r\n");
   }
    


}
void s_power(char *para) // power command
{

    BYTE u32Para;

    if (para == NULL)
    {
        return;
    }

   u32Para = atoi(para);

    if (0 == u32Para)
    {
       // power off
          if(SysPowerGetPowerStatus() != _POWER_STATUS_OFF) {
                 // power off
              SysPowerSetTargetPowerStatus(_POWER_STATUS_OFF);
              UserCommonEepromSaveSystemData();   
              sendOK(); 

              return ;
                    
           }
    }
    
   if (1 == u32Para)
    {
      //power on
       if(SysPowerGetPowerStatus() == _POWER_STATUS_OFF){
           SET_OSD_STATE(_MENU_NONE);
           SET_OSD_IN_FACTORY_MENU_STATUS(_FALSE);
           SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);
            UserCommonEepromSaveSystemData();
            sendOK(); 
        return ;
       }		
        
    }

   sendERR();   

}
void g_contrast(char *para) 
{

  WORD u32Para;
  para= NULL;
  u32Para = UserCommonAdjustRealValueToPercent(GET_OSD_CONTRAST(GET_OSD_SELECT_REGION()), _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER);
  printf("%d\r\n" , u32Para);  
 
}

void s_contrast(char *para) 
{

    WORD u32Para;

    if (para == NULL)
    {
        return;
    }
//printf("\r\n con value =%s \r\n" , para);
   u32Para = atoi(para);
//printf("b : contrast value =%d \r\n" , u32Para);
   // range check

   if(u32Para>=0 && u32Para<=100)
   {
    u32Para = UserCommonAdjustPercentToRealValue(u32Para, _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER);
     SET_OSD_CONTRAST(GET_OSD_SELECT_REGION(), u32Para);
   //  printf("a : contrast value =%d \r\n" , u32Para);
    // UserAdjustContrast(GET_OSD_SYSTEM _SELECT_REGION(), u32Para);
      UserAdjustContrast(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_CONTRAST(GET_OSD_SELECT_REGION()));
         UserAdjustBrightness(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_BRIGHTNESS(GET_OSD_SELECT_REGION()));
     SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
      sendOK();	
   }
   else{
	  sendERR();

   }
}
void g_brightness(char *para) 
{

  WORD u32Para;
  para= NULL;
  u32Para = UserCommonAdjustRealValueToPercent(GET_OSD_BRIGHTNESS(GET_OSD_SELECT_REGION()), _BRIGHTNESS_MAX, _BRIGHTNESS_MIN, _BRIGHTNESS_CENTER);
  printf("%d\r\n" , u32Para);  
 
}
void s_brightness(char *para) 
{

    WORD u32Para;

    if (para == NULL)
    {
        return;
    }

  //  printf("\r\n bri value =%s \r\n" , para);
   u32Para = atoi(para);

    // range check
   if(u32Para>=0 && u32Para<=100)
   {
   u32Para = UserCommonAdjustPercentToRealValue(u32Para, _BRIGHTNESS_MAX, _BRIGHTNESS_MIN, _BRIGHTNESS_CENTER);
     SET_OSD_BRIGHTNESS(GET_OSD_SELECT_REGION(), u32Para);
   //   printf("bri value =%d \r\n" , u32Para);
    // UserAdjustBrightness(GET_OSD_SYSTEM_SELECT_REGION(), u32Para);
      UserAdjustBrightness(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_BRIGHTNESS(GET_OSD_SELECT_REGION()));
    UserAdjustContrast(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_CONTRAST(GET_OSD_SELECT_REGION()));
      SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
        sendOK();	
   }
   else{
   sendERR();	

   }
}
void g_sharpness(char *para) 
{

    WORD u32Para;

    para=NULL;

    u32Para =GET_OSD_SHARPNESS(UserAdjustGetSelectRegionPort());
    printf("%d\r\n" , u32Para); 

}
void s_sharpness(char *para) 
{

    BYTE u32Para;

    if (para == NULL)
    {
        return;
    }

   u32Para = atoi(para);
    // range check
   if(u32Para>=0 && u32Para<=4)
   {
	   SET_OSD_SHARPNESS(UserAdjustGetSelectRegionPort(), u32Para);
	   
	   UserCommonAdjustSharpness(GET_OSD_SYSTEM_SELECT_REGION(), UserAdjustGetSelectRegionPort());
	   SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_INPUTPORTDATA_MSG);
      sendOK();

   }
   else{

	 sendERR();

   }
}
void g_backlight(char *para) 
{

  WORD u32Para;
  para= NULL;
  u32Para = UserCommonAdjustRealValueToPercent(GET_OSD_BACKLIGHT(), _BACKLIGHT_MAX, _BACKLIGHT_MIN, _BACKLIGHT_CENTER);
  printf("%d\r\n" , u32Para);  
 
}
void s_backlight(char *para) 
{

    WORD u32Para;

    if (para == NULL)
    {
        return;
    }

   u32Para = atoi(para);
    // range check
   if(u32Para>=0 && u32Para<=100)
   {
	   u32Para = UserCommonAdjustPercentToRealValue(u32Para, _BACKLIGHT_MAX, _BACKLIGHT_MIN, _BACKLIGHT_CENTER);
	   SET_OSD_BACKLIGHT(u32Para);
       UserAdjustBacklight(GET_OSD_BACKLIGHT());
	   SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

     sendOK();
   }
     else{

	   sendERR();

   }
}
void s_secureboot(char *para)
{

  para =NULL;
//#if(_SECURE_BOOT == _ON)     
  secure_boot(0);
//#endif
  sendOK();

}

void s_pq(char* para)
{
  BYTE u32Para = atoi(para);

  if(u32Para)
  {
	  ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
	  UserAdjustGammaRegionEnable(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_NO_POLLING, _OFF);


	  ScalerColorSRGBEnable(_FUNCTION_ON);// 3x3 matrix
	  ScalerColorDCCEnable(_FUNCTION_ON);
	  ScalerColorICMEnable(_FUNCTION_ON);

	  if(GET_OSD_GAMMA(GET_OSD_SELECT_REGION()) != _GAMMA_OFF)
	  {
	    UserAdjustGamma(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_GAMMA(GET_OSD_SELECT_REGION()));
		
	  }
	  
	   ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
	   UserAdjustGammaRegionEnable(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_NO_POLLING, _ON);

  }
  else // pq off
  {
		  ScalerColorSRGBEnable(_FUNCTION_OFF);// 3x3 matrix
		  ScalerColorBrightnessEnable(_FUNCTION_OFF);
		  ScalerColorContrastEnable(_FUNCTION_OFF);
	  
		//  ScalerColorSpaceConvertIDomainEnable(_OFF);
		//  ScalerColorSpaceConvertDDomainEnable(_OFF);
		  ScalerColorDCCEnable(_FUNCTION_OFF);
		  ScalerColorICMEnable(_FUNCTION_OFF);



  }
 
   sendOK();

}
void s_gamma(char* para)
{
	BYTE u32Para = atoi(para);
	
	ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
	UserAdjustGammaRegionEnable(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_NO_POLLING, _OFF);

    
    if(u32Para <= _GAMMA_AMOUNT && GET_OSD_GAMMA(GET_OSD_SELECT_REGION()) != _GAMMA_OFF)
    {
         SET_OSD_GAMMA(GET_OSD_SELECT_REGION(), u32Para);
      //  UserAdjustGamma(GET_OSD_GAMMA(GET_OSD_SELECT_REGION()),u32Para);

		UserAdjustGamma(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_GAMMA(GET_OSD_SELECT_REGION()));
		 
        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
	    UserAdjustGammaRegionEnable(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_NO_POLLING, _ON);
		 SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
    }	
	
	sendOK();


}
void s_gdata(char*para)
{

  BYTE idx , i=0;
  BYTE channel;
  BYTE gidx =0 ;
  BYTE buf_in[40];
  //------------------
  idx= para[0]-0x30;
  channel = para[1]-0x30;
  gidx = para[2]-0x30;
 
  //---------------------------
  for(i=0; i<40 ;i++)
  {
	  buf_in[idx*40+i] = para[3+i];

  }
  // trasmit gdata completely
  // save gamma data to eeprom directly
 RTDNVRamSaveGammaModeData(idx,  channel ,  gidx , sizeof(buf_in) , buf_in);

 sendOK();

}
//void RTDEepromLoadGammaModeData(uint8_t index , uint8_t channel , uint8_t* buf_out)
void g_nvram(char *para) 
{
   BYTE para1 ;
   BYTE para2 ;
   int i;
   BYTE buf[320]; 

  sscanf(para,  "%d" TEST_ARGS_SPLIT "%d" ,&para1, &para2); // format string

  //printf("%bd %bd\r\n" , para1, para2);  

  RTDNVRamLoadGammaModeData(para1,para2,buf);

  for (i = 0; i < 320; i += 8)
  {
 	printf("%bx,%bx,%bx,%bx,%bx,%bx,%bx,%bx \r\n", buf[i], buf[i + 1], buf[i + 2], buf[i + 3], buf[i+4], buf[i + 5], buf[i + 6], buf[i + 7]);
  }

}


void s_help(char *params)
{
	int i;
	//char acBuf[64]={0};
	params=NULL;
   // printf("support command list\r\n");

	for (i = 0; commands[i].name; i++){

		printf("%s",commands[i].syntax);

	}
}
	

char putchar (char c)  {

 return ScalerMcuUartWrite((BYTE)c);
}

static void cutto(char *str, int len , int buf_size)

{
	int size;// = -len + 1;
	
		size = buf_size - len + 1;
		memmove(str, str + len,  size);
		memset(str+size-1 , '\0' , len);

}
static char* trimgarbage(char*str)
{
	char *p;  /* strlen("ALLOWCOMMAND_XXXX") + 1 == 18 */
	p = str;			/* Remove garbage in the string */
	
	while (*p)
	{
		if ((unsigned char) *p <= 32 || (unsigned char) *p ==0x7F) p++;
		else{
			break;
		}
	}	

    return p;
}

static void remove_trim(char*str , int buf_size)

{
		char* p;
		int size;
		p = str;
	
	
		while (((*p == ' ') || (*p == '\t')))//while ((*p) && ((*p == ' ') || (*p == '\t')))
		{
			p++;
		}
		size = buf_size - (p - str) + 1;
	//	memmove(str, p, strlen(str) - (p - str) + 1);
		memmove(str, p, size);
		memset(str + (size - 1), '\0', (p - str));


}
 BYTE  parsecmd(char *str)
{
		 int i;
	 //  char*p;
		 
		 str=trimgarbage(str);
		 //str = strtok(str,"\r\n");
		 
		 for (i = 0; commands[i].name; i++) 
			{	 /* Parse command */
			 if (!strncmp(str, commands[i].name, strlen(commands[i].name))) 
			 {
						
				 cutto(str, strlen(commands[i].name),MAX_BUFF_SIZE);
				 remove_trim(str,MAX_BUFF_SIZE);
				 commands[i].function(str); // pass parameter to command
				 return _TRUE ;
				 
			 }
			 else // handle unsupported command
			 {
	 
			 }
		 }
			 
		if(!strlen(str))
		 { 
		   // handle enter key only
		   sendEmpty();
		   return _TRUE ;
		 }	 
	   
	   return _FALSE ;


}


void StopRcvMsg(void)
{
   gB_RcvStatus = RCV_READY;						// stop receiving messages

}


void StartRcvMsg(void)
{
   gB_RcvStatus = RCV_EMPTY;						// start receiving messages

}
static bit is_uart_message_complete(void)
{
  return gB_RcvStatus;

}

void UserInterfaceUartIntHandler_SERIALPORT(void)
{
	
	if(RI)
	{
	  if ((gB_RcvStatus == RCV_EMPTY) &&	 // Packet not received yet
		   (gB_RcvCount < MAX_BUFF_SIZE))  // Buffer not ful
	  { 									 
		  g_pucUartData[gB_RcvCount] = SBUF;// Get data from UART
		  
		  gB_RcvCount++;
	
	
		 if((gB_RcvCount > 1) && g_pucUartData[gB_RcvCount-1] == '\n' && g_pucUartData[gB_RcvCount-2] == '\r')	// if(is_uartbuf_ready(g_pucUartData,gB_RcvCount))
		 {
			  StopRcvMsg();
			  memcpy(acRecvBuf, g_pucUartData, gB_RcvCount);
			  memset(g_pucUartData , 0 ,MAX_BUFF_SIZE);
			  gB_RcvCount =0 ;			  
	
		  }
		  
	
		  if ((gB_RcvCount % MAX_BUFF_SIZE) ==0) 
		  {
			  gB_RcvCount =0 ;
		  }
	
	  }
	  else
	  {
		  gB_dummy = SBUF; // clear the buffer
	
	  }
	  
	  RI =0 ;
	  
	}


}
void UartHandler(void)
{
     UserInterfaceUartIntHandler_SERIALPORT();

    if(is_uart_message_complete())
    { 
 
       if(!parsecmd(acRecvBuf))// parse command
       {
            sendERR();
       }

	   memset(acRecvBuf , 0 ,MAX_BUFF_SIZE);
       StartRcvMsg();
    }	

 
}
#endif // end uart
