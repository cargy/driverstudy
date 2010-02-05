// generated by Fast Light User Interface Designer (fluid) version 2.1000

#include "MainMenuUIAbstract.h"

MainMenuUIAbstract::MainMenuUIAbstract(int x, int y, int width, int height, const char* label): fltk::Window(x,y,width,height,label,true) {
  fltk::Group* w;
  
  {
fltk::Group* o = mainContainer = new fltk::Group(0, 0, 640, 480);
    w = o;
    o->user_data((void*)(this));
    o->begin();
    new fltk::Widget(12, 6, 615, 110, "_Application Title");
    
    {
fltk::Group* o = new fltk::Group(12, 137, 615, 210);
      o->box(fltk::THIN_UP_BOX);
      o->begin();
      
      {
fltk::Group* o = new fltk::Group(16, 41, 580, 149, "_Select a Test CategoryQ");
        o->begin();
        new fltk::Button(0, 20, 110, 110, "_Motorcycle");
        new fltk::Button(156, 20, 110, 110, "_Car");
        new fltk::Button(313, 20, 110, 110, "_Track");
        new fltk::Button(470, 20, 110, 110, "_Bus");
        o->end();
        fltk::Group::current()->resizable(o);
      }
      o->end();
    }
    
    {
fltk::Group* o = new fltk::Group(12, 369, 615, 100);
      o->box(fltk::THIN_UP_BOX);
      o->begin();
      new fltk::Button(18, 13, 75, 75, "_Exit");
      new fltk::Button(521, 13, 75, 75, "_Help");
      
      {
fltk::PopupMenu* o = languagePUM = new fltk::PopupMenu(213, 30, 178, 41, "_Select Language");
        o->begin();
        new fltk::Item("_Greek");
        new fltk::Item("_English");
        new fltk::Item("_Russian");
        new fltk::Item("_Albanian");
        o->end();
      }
      o->end();
    }
    o->end();
  }
}
