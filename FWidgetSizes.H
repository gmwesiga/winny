#ifndef FWidgetSizes_H
#define FWidgetSizes_H
    
    struct FwSizes{ //fw for Fltk Widget
        int X;
        int Y;
        int W;
        int H;
    };

//change these to the height and width of largest static design template
#define SCRN_WIDTH 1064 
#define SCRN_HEIGHT 592


//we use these to get ratios 
#define DESIGNSW 1064
#define DESIGNSH  592

#define DX(x) (x)
#define DY(y) (y)

#define SLWH 25 //single Line Wigdets Height 

const FwSizes CONTENT_AREA = {
    261,97,
    (int)(((float)749/DESIGNSW)* SCRN_WIDTH),
    (int)(((float)490/DESIGNSH)*SCRN_HEIGHT),
    };

const FwSizes MENUBAR_AREA = {
    CONTENT_AREA.X,CONTENT_AREA.Y,
    CONTENT_AREA.W,
    40
    };
const int MENUBAR_CH = 20;
const int MBH = 12;


#define DFCX(x)((x)+CONTENT_AREA.X+)

const FwSizes CONTENT_AREA2 ={
    CONTENT_AREA.X,CONTENT_AREA.Y+MENUBAR_AREA.H,
    CONTENT_AREA.W,
    CONTENT_AREA.H - MENUBAR_AREA.H
    };

//macros to be called on all content area objects
#define DCX(x) ((x)+CONTENT_AREA.X)
#define DCY(y) ((y)+CONTENT_AREA2.Y)

#define DMX(x) ((x)+MENUBAR_AREA.X)
#define DMY(y) ((y)+MENUBAR_AREA.Y)


const FwSizes LCLNAV_AREA =  {
    48,70,
    (int)(((float)218/DESIGNSW)* SCRN_WIDTH),
    (int)(((float)491/DESIGNSH)*SCRN_HEIGHT)
    };
const FwSizes LCLNAV_AREA2 = {
    48,97,
    (int)(((float)218/DESIGNSW)* SCRN_WIDTH),
    (int)(((float)465/DESIGNSH)*SCRN_HEIGHT)
    };

const FwSizes NOTFCN_AREA = {
    50,577/*SCRN_HEIGHT-73*/,
    (int)(((float)192/DESIGNSW)* SCRN_WIDTH),
    /*70*/140
};
#endif
