#include <FlOffPremiseSaleUserIO.H>
#include <FWidgetSizes.H>
#include <winny_theme.h>
#include <WinnyNames.H>
#include <WinnyUserPrompts.H>

void salesRepNameCb(Fl_Widget*o, void* d);

FlOffPremiseSaleUserIO::FlOffPremiseSaleUserIO(int x, int y, int w, int h)
:Fl_Group(x,y,w,h){

    btnSave = new Fl_Button(DCX(5),DCY(32),47,21,"save");
    set_winny_button_theme(btnSave);
    btnSave->color(WINNY_BACKGROUND_ACCCOLOR);
    btnSave->labelcolor(FL_WHITE);
    btnSave->box(WINNY_THICK_BORDERBOX);

    btnCancel = new Fl_Button(DCX(52),DCY(32),47,21);
    set_winny_button_theme(btnCancel);

   /*  hr1= new Fl_Box(DCX(0),DCY(30),742,1);
    hr1->box(WINNY_TOP_BORDERBOX);*/

    bgbox = new Fl_Box(DCX(46),DCY(65),536,385);
    bgbox->box(WINNY_THIN_BORDERBOX);
    bgbox->color(fl_rgb_color(240,240,240));

    salesRepName = new Fl_Input(DCX(76),DCY(109),236,26,"Sales Representative");
    set_winny_input_theme(salesRepName);
    salesRepName->input_type(FL_INPUT_READONLY);
    salesRepName->align(FL_ALIGN_TOP_LEFT);
    salesRepName->callback(salesRepNameCb);
    
    salesDate = new Fl_Input(DCX(320),DCY(109),109,26,"Off Site Sale");
    set_winny_input_theme(salesDate);
    salesDate->input_type(FL_INPUT_READONLY);
    salesDate->align(FL_ALIGN_TOP_LEFT);

    transId = new Fl_Input(DCX(436),DCY(109),105,26);
    set_winny_input_theme(transId);
    transId->input_type(FL_INPUT_READONLY);

    hr2 = new Fl_Box(DCX(76),DCY(163),479,1);
    hr2->box(WINNY_TOP_BORDERBOX);
    
    Documents = new dataset_view(DCX(72),DCY(202),484,180);
    Documents->box(WINNY_THIN_BORDERBOX);

    hr3 = new Fl_Box(DCX(0),DCY(65),739,1);/*Header, body Separator rule */
    hr3->box(WINNY_TOP_BORDERBOX);

    cashRecieved = new Fl_Input(DCX(71),DCY(384),136,SLWH,"Paid");
    set_winny_input_theme(cashRecieved);
    cashRecieved->align(FL_ALIGN_BOTTOM|FL_ALIGN_CENTER);

    salesAmount = new Fl_Input(DCX(436),DCY(385),120,SLWH,"Amount");
    set_winny_input_theme(salesAmount);
    salesAmount->align(FL_ALIGN_BOTTOM|FL_ALIGN_CENTER);

    recievableAmount = new Fl_Input(DCX(320),DCY(385),109,SLWH,"Recievable");
    set_winny_input_theme(recievableAmount);
    recievableAmount->align(FL_ALIGN_BOTTOM|FL_ALIGN_CENTER);

    /* hr4 = new Fl_Box(DCX(0),DCY(398),742,1);
    hr4->box(WINNY_TOP_BORDERBOX);*/

    resizer= new Fl_Box(DCX(606),DCY(465),2,1);
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




void FlOffPremiseSaleUserIO::readBuff(void* buff){
    return;
};



void FlOffPremiseSaleUserIO::writeBuff(void* buff){
    return;
};

UIname FlOffPremiseSaleUserIO::id(){
    return "Transactions/ Enter OffSite Sale";
};

void salesRepNameCb(Fl_Widget*o, void* d){
    string s;
    PromptUser::getProductId(&s);
};