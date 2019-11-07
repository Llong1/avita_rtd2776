#ifndef __TILING_H
#define __TILING_H


#include "Global.h"
#include "Project.h"

#if(_OVERSCAN_SUPPORT == _ON)

extern WORD gB_hnum ;
extern WORD gB_vnum ; 
extern WORD gB_pos ;


#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

extern void TilingHandler(EnumDisplayRegion enumDisplayRegion);


#endif
#endif

