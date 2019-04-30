#include <FlLocalNavDisplay.H>
#include <FWidgetSizes.H>
#include <winny_theme.h>

FlLocalNavDisplay::FlLocalNavDisplay():
    Fl_Tree(LCLNAV_AREA2.X,LCLNAV_AREA2.Y,LCLNAV_AREA2.W,LCLNAV_AREA2.H,"Administrator")
{
    align(FL_ALIGN_TOP_LEFT);
    labelcolor(WINNY_TITLETEXT_COLOR);
    labelsize(WINNY_TITLETEXT_FONTSIZE);
    labelfont(WINNY_BOLDFONT);
    showroot(0); //remove it
    connectorstyle(FL_TREE_CONNECTOR_NONE);
    connectorwidth(0);
    linespacing(5);
    selection_color(SELECTION_BACKCOLOR());
    marginleft(0);
    item_labelfgcolor(WINNY_LINKTEXT_COLOR);
    item_labelsize(WINNY_NORMALTEXT_FONTSIZE);

    add("Product Managment");
    add("Contact Managment");
    box(WINNY_TOP_BORDERBOX);

}