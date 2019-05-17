#ifndef FWidgetSizes_H
#define FWidgetSizes_H
    
    struct FwSizes{ //fw for Fltk Widget
        int X;
        int Y;
        int W;
        int H;
    };

//change these to the height and width of largest static design template
#define SCRN_WIDTH 1078 
#define SCRN_HEIGHT 600


//we use these to get ratios 
#define DESIGNSW 1077
#define DESIGNSH  511

const FwSizes CONTENT_AREA = {
    228,65,
    (int)(((float)787/DESIGNSW)* SCRN_WIDTH),
    (int)(((float)446/DESIGNSH)*SCRN_HEIGHT),
    };
const FwSizes CONTENT_AREA2 ={
    228,122,
    (int)(((float)787/DESIGNSW)* SCRN_WIDTH),
    (int)(((float)389/DESIGNSH)*SCRN_HEIGHT)
    };
const FwSizes MENUBAR_AREA = {
    228,88,
    (int)(((float)787/DESIGNSW)* SCRN_WIDTH),
    (int)(((float)35/DESIGNSH)*SCRN_HEIGHT)
    };
const FwSizes LCLNAV_AREA =  {
    11,65,
    (int)(((float)171/DESIGNSW)* SCRN_WIDTH),
    (int)(((float)446/DESIGNSH)*SCRN_HEIGHT)
    };
const FwSizes LCLNAV_AREA2 = {
    11,88,
    (int)(((float)171/DESIGNSW)* SCRN_WIDTH),
    (int)(((float)432/DESIGNSH)*SCRN_HEIGHT)
    };

const FwSizes NOTFCN_AREA = {
    355,SCRN_HEIGHT-73,
    (int)(((float)466/DESIGNSW)* SCRN_WIDTH),
    70
};
#endif
