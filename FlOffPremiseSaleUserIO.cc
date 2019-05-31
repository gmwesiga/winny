#include <FlOffPremiseSaleUserIO.H>
#include <FWidgetSizes.H>
#include <winny_theme.h>
#include <WinnyNames.H>

FlOffPremiseSaleUserIO::FlOffPremiseSaleUserIO(int x, int y, int w, int h)
:Fl_Group(x,y,w,h){

    btnSave = new Fl_Button(DCX(3),DCY(7),57,16,"save");
    set_winny_button_theme(btnSave);
    btnSave->color(WINNY_BACKGROUND_ACCCOLOR);
    btnSave->labelcolor(FL_WHITE);
    btnSave->box(WINNY_THICK_BORDERBOX);

    btnCancel = new Fl_Button(DCX(682),DCY(7),57,16);
    set_winny_button_theme(btnCancel);

    hr1= new Fl_Box(DCX(0),DCY(25),742,1);
    hr1->box(WINNY_TOP_BORDERBOX);

    salesRepName = new Fl_Input(DCX(6),DCY(56),233,26,"Sales Representative");
    set_winny_input_theme(salesRepName);
    salesRepName->input_type(FL_INPUT_READONLY);
    salesRepName->align(FL_ALIGN_TOP_LEFT);
    
    salesDate = new Fl_Input(DCX(250),DCY(56),105,26,"Off Site Sale");
    set_winny_input_theme(salesDate);
    salesDate->input_type(FL_INPUT_READONLY);
    salesDate->align(FL_ALIGN_TOP_LEFT);

    transId = new Fl_Input(DCX(366),DCY(56),105,25);
    set_winny_input_theme(transId);
    transId->input_type(FL_INPUT_READONLY);

    hr2 = new Fl_Box(DCX(0),DCY(115),742,1);
    hr2->box(WINNY_TOP_BORDERBOX);
    
    Documents = new dataset_view(DCX(1),DCY(149),484,180);
    Documents->box(WINNY_TOP_BORDERBOX);

    hr3 = new Fl_Box(DCX(0),DCY(333),742,1);
    hr3->box(WINNY_TOP_BORDERBOX);

    cashRecieved = new Fl_Input(DCX(1),DCY(333),136,20,"Paid");
    set_winny_input_theme(cashRecieved);
    cashRecieved->align(FL_ALIGN_BOTTOM|FL_ALIGN_CENTER);

    salesAmount = new Fl_Input(DCX(342),DCY(333),143,20,"Amount");
    set_winny_input_theme(salesAmount);
    salesAmount->align(FL_ALIGN_BOTTOM|FL_ALIGN_CENTER);

    recievableAmount = new Fl_Input(DCX(499),DCY(333),130,20,"Recievable");
    set_winny_input_theme(recievableAmount);
    recievableAmount->align(FL_ALIGN_BOTTOM|FL_ALIGN_CENTER);

    hr4 = new Fl_Box(DCX(0),DCY(398),742,1);
    hr4->box(WINNY_TOP_BORDERBOX);

    resizer= new Fl_Box(DCX(640),DCY(417),2,1);
    resizable(resizer);
    end();

};




void FlOffPremiseSaleUserIO::show(){
     Fl_Group::show();
};




void FlOffPremiseSaleUserIO::hide(){
    Fl_Group::hide();
};




void FlOffPremiseSaleUserIO::update(){
    Fl_Group::redraw();
};




void FlOffPremiseSaleUserIO::readBuffer(void* buff){
    return;
};



void FlOffPremiseSaleUserIO::writeBuffer(void* buff){
    return;
};

UIname FlOffPremiseSaleUserIO::id(){
    return "Transactions/ Enter OffSite Sale";
};