#ifndef __UART_H
#define __UART_H

#if(_UART_SUPPORT == _ON)
	
#define MAX_BUFF_SIZE (250)

struct command {
  char *name;
  void (*function)(char *str);
  char *syntax;
  //char state_needed;
  //char showinfeat;
};

enum
{
   RCV_EMPTY,                              // No data packet
   RCV_READY                               // Data packet received
};



extern void UartHandler(void);



#endif




#endif