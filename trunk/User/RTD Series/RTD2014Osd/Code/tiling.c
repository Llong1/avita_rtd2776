#include "UserCommonInclude.h"
#include <stdio.h>                /* prototype declarations for I/O functions */



#if(_OVERSCAN_SUPPORT == _ON)


WORD gB_hnum =1;
WORD gB_vnum=1 ; 
WORD gB_pos=1 ;



void TilingHandler(EnumDisplayRegion enumDisplayRegion)
{
    BYTE ucDelta = 0;
    WORD ucx =0,ucy=0,ucw=0,uch=0;
    WORD h_bezel=0,v_bezel=0;
    BYTE display_h=0 , display_v=0 ;

	//enumDisplayRegion = enumDisplayRegion ;
	
  //printf("ori:x=%d,y=%d,w=%d,h=%d\r\n",
  //	GET_MDOMAIN_INPUT_HSTART(), GET_MDOMAIN_INPUT_VSTART(), GET_MDOMAIN_INPUT_HWIDTH(), GET_MDOMAIN_INPUT_VHEIGHT());
    gB_hnum = MAX(gB_hnum,1);
	gB_vnum = MAX(gB_vnum,1);
	gB_pos = MAX(gB_pos,1);


    display_h = ((gB_pos-1)%gB_hnum)+1; 
	display_v = ((gB_pos-1)/gB_hnum)+1;
	  
	ucx=(GET_MDOMAIN_INPUT_HWIDTH()- ((GET_MDOMAIN_INPUT_HWIDTH()/gB_hnum)-h_bezel))*MAX(display_h-1,0)/MAX(gB_hnum-1,1);  
	ucw= (GET_MDOMAIN_INPUT_HWIDTH()/gB_hnum)- h_bezel;  
	ucy= (GET_MDOMAIN_INPUT_VHEIGHT() - ((GET_MDOMAIN_INPUT_VHEIGHT()/gB_vnum) - v_bezel))*MAX(display_v-1,0)/MAX(gB_vnum-1,1);  
	uch=(GET_MDOMAIN_INPUT_VHEIGHT()/gB_vnum) - v_bezel;
	
	//printf("aft : x=%d,y=%d,w=%d,h=%d\r\n",ucx, ucy, ucw, uch);
#if 1
    // Modify Over Scanned H
    //ucx = GET_MDOMAIN_INPUT_HSTART()+ucx;
    //ucDelta = (BYTE)((DWORD)GET_MDOMAIN_INPUT_HWIDTH() * _OVERSCAN_H_RATIO / 1000);

    // Let Adjusted Value be 2's multiple
    //ucDelta += ucDelta % 2;
      ucx += ucx % 2;
    SET_MDOMAIN_INPUT_HSTART(GET_MDOMAIN_INPUT_HSTART() + ucx);// SET_MDOMAIN_INPUT_HSTART(GET_MDOMAIN_INPUT_HSTART() + ucDelta);
    SET_MDOMAIN_INPUT_HWIDTH(ucw); //SET_MDOMAIN_INPUT_HWIDTH(GET_MDOMAIN_INPUT_HWIDTH() - 2 * ucDelta);

    // Modify Over Scanned V
    //ucDelta = (BYTE)((DWORD)GET_MDOMAIN_INPUT_VHEIGHT() * _OVERSCAN_V_RATIO / 1000);

    if(ScalerFmtCnvFtoPGetStatus(ScalerRegionGetInputDataPath(enumDisplayRegion)) == _TRUE)
    {
        // Let Adjusted Value be 2's multiple under E/O mode
       ucy+=ucy%2;// ucDelta += ucDelta % 2;
    }

   SET_MDOMAIN_INPUT_VSTART(GET_MDOMAIN_INPUT_VSTART() + ucy);// SET_MDOMAIN_INPUT_VSTART(GET_MDOMAIN_INPUT_VSTART() + ucDelta);
   SET_MDOMAIN_INPUT_VHEIGHT(uch);// SET_MDOMAIN_INPUT_VHEIGHT(GET_MDOMAIN_INPUT_VHEIGHT() - 2 * ucDelta);
#endif	
}
#endif  // End of #if(_OVERSCAN_SUPPORT == _ON)


























