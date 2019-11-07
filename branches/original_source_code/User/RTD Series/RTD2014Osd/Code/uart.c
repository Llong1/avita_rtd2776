#include "UserCommonInclude.h"
#include "uart.h"
#include <stdio.h>                /* prototype declarations for I/O functions */
#include <string.h>
#include <stdlib.h>
#include "UserCommonInterface.h"

#include "tiling.h"
#if(_UART_SUPPORT == _ON)
///////////////////////////////

typedef enum
{
	RCV_EMPTY, // No data packet
	RCV_READY // Data packet received

}UartReceiveStatus;

#define MAX_BUFF_SIZE (24)

struct command {
  char *name;
  void (*function)(char *str);
  char *syntax;
  //char state_needed;
  //char showinfeat;
};



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
void s_source(char*para);
void s_rotate(char*para);
void s_mode(char*para);
void s_pip(char*para);
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

//char acRecvBuf[MAX_BUFF_SIZE]={0};

BYTE g_pucUartData[MAX_BUFF_SIZE]={0};
BYTE gB_RcvCount=0 ;  // alant add
UartReceiveStatus gB_RcvStatus=RCV_EMPTY;
//BYTE gB_RcvComplete=0;
BYTE gB_dummy ;
#define TEST_ARGS_SPLIT " "
#define CMD_SPLIT "\r\n"

///////////////////////////////////////
const struct command commands[] = {

  {"s_contrast", s_contrast, "s_contrast 0~100\r\n"},
  {"s_brightness", s_brightness, "s_brightness 0~100\r\n"},
  {"s_sharpness", s_sharpness, "s_sharpness 0~4\r\n"},
  {"s_backlight", s_backlight, "s_backlight 0~100\r\n"},
  {"s_power",s_power,"s_power 0/1\r\n"} ,
  {"reset",s_reset,"reset:user reset\r\n"} ,
  {"s_colortemp", s_colortemp, "s_colortemp 0~5\r\n"},
  {"s_tiling", s_tiling, "s_tiling row column pos h_bezel v_bezel\r\n"},
  {"s_aspect", s_aspect, "s_aspect 0~4\r\n"},
  {"s_pattern", s_pattern, "s_pattern 0/1 r(0~255) g(0~255) b(0~255)\r\n"}, 
  {"s_rotate", s_rotate, "s_rotate angle(0~3) aspect(0~2)\r\n"},
  {"s_mode", s_mode, "s_mode displaymode(0~3) displayregion(0~2)\r\n"},
  {"s_pip", s_pip, "s_pip postion(0~5) transparency(0~10)\r\n"},
  {"s_source", s_source, "s_source region source\r\n"},
  {"g_colorinfo", g_colorinfo, "g_colorinfo : colorspace colorrange colorimetry \r\n"},
   
  {"g_colortemp", g_colortemp, "g_colortemp:get colotemp value\r\n"},
  {"g_power",g_power,"g_power:get power status\r\n"} ,
  {"g_contrast",g_contrast,"g_contrast:get contrast value\r\n"} ,
  {"g_brightness",g_brightness,"g_brightness:get brightness value\r\n"} ,
  {"g_sharpness", g_sharpness, "g_sharpness:get sharpness value \r\n"},
  {"g_backlight", g_backlight, "g_backlight:get backlight value\r\n"},
  {"g_aspect", g_aspect, "g_aspect:get aspect ratio value\r\n"},
  {"g_paneltime", g_paneltime, "g_paneltime:get panel time (hour min)\r\n"},

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

static void sendUnsupport(void){

    printf("ERR 0\r\n");	 

}
void s_source(char*para)
{
#if 0

    _DISPLAY_RGN_1P = _DISPLAY_MODE_1P,

    _DISPLAY_RGN_MAIN = (_DISPLAY_MODE_PIP | _REGION_INDEX_0),
    _DISPLAY_RGN_SUB = (_DISPLAY_MODE_PIP | _REGION_INDEX_1),

    _DISPLAY_RGN_LEFT = (_DISPLAY_MODE_PBP_LR | _REGION_INDEX_0),
    _DISPLAY_RGN_RIGHT = (_DISPLAY_MODE_PBP_LR | _REGION_INDEX_1),

    _DISPLAY_RGN_TOP = (_DISPLAY_MODE_PBP_TB | _REGION_INDEX_0),
    _DISPLAY_RGN_BOTTOM = (_DISPLAY_MODE_PBP_TB | _REGION_INDEX_1),

    _DISPLAY_RGN_LT = (_DISPLAY_MODE_4P | _REGION_INDEX_0),
    _DISPLAY_RGN_LB = (_DISPLAY_MODE_4P | _REGION_INDEX_1),
    _DISPLAY_RGN_RT = (_DISPLAY_MODE_4P | _REGION_INDEX_2),
    _DISPLAY_RGN_RB = (_DISPLAY_MODE_4P | _REGION_INDEX_3),

    _DISPLAY_RGN_NONE = (_DISPLAY_MODE_NONE | _REGION_INDEX_NONE),

#endif
   WORD gB_source=0 ,gB_region=0 ; 
   
   if(para==NULL) return ;
   
   sscanf(para,  "%d" TEST_ARGS_SPLIT "%d", 
   	&gB_region,&gB_source); // format string
    
    UserAdjustRegionInputPort(gB_region, gB_source);// switch input source
  //  SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
    sendOK(); 
}
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
void s_mode(char*para)
{
   WORD gB_mode=0 ,gB_region=0 ; 
   
   if(para==NULL) return ;
   
   sscanf(para,  "%d" TEST_ARGS_SPLIT "%d",			
     &gB_mode, &gB_region); // format string

 // printf("%d %d %d\r\n",gB_hnum,gB_vnum, gB_pos); 
      SET_OSD_DISPLAY_MODE(gB_mode);
      SET_OSD_SELECT_REGION(gB_region);
      OsdDispDisableOsd();
      UserAdjustDisplayMode();
      SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
      sendOK(); 

}
void s_pip(char*para)
{
   WORD gB_size=0 ,gB_region=0 ; 
   
   if(para==NULL) return ;
   
   sscanf(para,  "%d" TEST_ARGS_SPLIT "%d",	&gB_size, &gB_region); // format string

     if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP)
      {
           SET_OSD_PIP_POSITION_TYPE(gB_size);
           SET_OSD_PIP_TRANSPARENCY(gB_region);

           UserCommonAdjustPipSubTimingFormat();
           UserAdjustPipTransparency();
       }

      SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
   sendOK(); 
}
void s_rotate(char*para)
{

WORD gB_rotate=0 ,gB_size=0 ; 
	
   if(para==NULL) return ;

	sscanf(para,  "%d" TEST_ARGS_SPLIT "%d" ,			 
	&gB_rotate ,  &gB_size); // format string
	
    SET_OSD_DISP_ROTATE(gB_rotate); // 0,1,2,3
    SET_OSD_DISP_ROTATION_SIZE_TYPE(gB_size); // 0,1,2
	UserAdjustResetDisplayByPort(GET_OSD_SYSTEM_DISPLAY_REGION());
	SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

    sendOK(); 
}

void s_pattern(char*para)
{
WORD gB_on=0 ,gB_r=0, gB_g=0, gB_b=0 ; 
	
   if(para==NULL) return ;

	sscanf(para,  "%d" TEST_ARGS_SPLIT "%d" TEST_ARGS_SPLIT "%d" TEST_ARGS_SPLIT "%d",			 
	&gB_on ,  &gB_r, &gB_g, &gB_b); // format string

   if(gB_on) {
   
        ScalerDDomainPatternGenAdjustColor(gB_r, gB_g, gB_b);
        ScalerDDomainPatternGenEnable(_ENABLE);
        ScalerDDomainBackgroundEnable(_DISPLAY_PATH_ALL, _DISABLE);
    
   	}
   else{
   ScalerDDomainPatternGenEnable(_DISABLE);
     
   }
   sendOK(); 

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
    // UserCommonAdjustDisplayFreeze(_ON);
	  SET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort(), u32Para);
	  UserAdjustResetDisplayByPort(GET_OSD_SYSTEM_DISPLAY_REGION());
	  SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_INPUTPORTDATA_MSG);
	//    UserCommonAdjustDisplayFreeze(_OFF);
      sendOK(); 
  }
  else{
 sendERR();

  }


}

void s_tiling(char*para)
{
 
   if(para==NULL) return ;
   
     sscanf(para,  "%d" TEST_ARGS_SPLIT "%d" TEST_ARGS_SPLIT "%d" TEST_ARGS_SPLIT "%d" TEST_ARGS_SPLIT "%d",			
     &gB_hnum, &gB_vnum, &gB_pos,&h_bezel, &v_bezel ); // format string

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
   if(u32Para>=_SHARPNESS_MIN && u32Para<=_SHARPNESS_MAX)
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

static void cutto(char *str, int len)
{
	memmove(str, str + len, strlen(str) - len + 1);
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

static void remove_trim(char*str)
{
	char *p; 
	p = str;

				
	while ((*p) && ((*p == ' ') || (*p == '\t'))) {
		p++;
	}
	memmove(str, p, strlen(str) - (p - str) + 1);


}
BYTE  parsecmd(char *str)
{
	int i;
	str=trimgarbage(str);
	
	
	for (i = 0; commands[i].name; i++) 
       {	/* Parse command */
		if (!strncmp(str, commands[i].name, strlen(commands[i].name))) 
		{
                   
			cutto(str, strlen(commands[i].name));
			remove_trim(str);
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

void UserInterfaceUartIntHandler_SERIALPORT(void)
{
 
  if(RI)
  {
	if ((gB_RcvStatus == RCV_EMPTY) &&	   // Packet not received yet
		 (gB_RcvCount < MAX_BUFF_SIZE))	 // Buffer not ful
	{									   
		g_pucUartData[gB_RcvCount] = SBUF;// Get data from UART
        
		gB_RcvCount++;

		if(strchr(g_pucUartData,'\r') != NULL) 
		{
		    gB_RcvStatus = RCV_READY;
		}
		
		if ((gB_RcvCount % MAX_BUFF_SIZE) ==0) 
		{
		  gB_RcvCount =0 ;
		  memset(g_pucUartData , 0 ,MAX_BUFF_SIZE);
		}


	}
	else{
		gB_dummy = SBUF; // clear the buffer

	}
    RI =0 ;
    
  }

}
void UartHandler(void)
{
  UserInterfaceUartIntHandler_SERIALPORT();

    if(gB_RcvStatus == RCV_READY)
    { 
     //  StopRcvMsg();
	   if(!parsecmd(g_pucUartData))// parse command
       {
         sendUnsupport();

       }
       memset(g_pucUartData , 0 ,MAX_BUFF_SIZE);
       gB_RcvCount=0;
	  // StartRcvMsg();

	   gB_RcvStatus = RCV_EMPTY; 
    }	

 
}
#endif // end uart
