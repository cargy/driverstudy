// generated by Fast Light User Interface Designer (fluid) version 2.1000

#include "MainMenuUIAbstract.h"

inline void MainMenuUIAbstract::cb_motorcycleBtn_i(fltk::Button* o, const char* v) {
  cb_start(o,v)
;}
void MainMenuUIAbstract::cb_motorcycleBtn(fltk::Button* o, const char* v) {
  ((MainMenuUIAbstract*)(o->parent()->parent()->parent()->user_data()))->cb_motorcycleBtn_i(o,v);
}

inline void MainMenuUIAbstract::cb_carBtn_i(fltk::Button* o, const char* v) {
  cb_start(o,v)
;}
void MainMenuUIAbstract::cb_carBtn(fltk::Button* o, const char* v) {
  ((MainMenuUIAbstract*)(o->parent()->parent()->parent()->user_data()))->cb_carBtn_i(o,v);
}

inline void MainMenuUIAbstract::cb_truckBtn_i(fltk::Button* o, const char* v) {
  cb_start(o,v)
;}
void MainMenuUIAbstract::cb_truckBtn(fltk::Button* o, const char* v) {
  ((MainMenuUIAbstract*)(o->parent()->parent()->parent()->user_data()))->cb_truckBtn_i(o,v);
}

inline void MainMenuUIAbstract::cb_busBtn_i(fltk::Button* o, const char* v) {
  cb_start(o,v)
;}
void MainMenuUIAbstract::cb_busBtn(fltk::Button* o, const char* v) {
  ((MainMenuUIAbstract*)(o->parent()->parent()->parent()->user_data()))->cb_busBtn_i(o,v);
}

inline void MainMenuUIAbstract::cb_smotorcycleBtn_i(fltk::Button* o, const char* v) {
  cb_start(o,v)
;}
void MainMenuUIAbstract::cb_smotorcycleBtn(fltk::Button* o, const char* v) {
  ((MainMenuUIAbstract*)(o->parent()->parent()->parent()->user_data()))->cb_smotorcycleBtn_i(o,v);
}

inline void MainMenuUIAbstract::cb_scarBtn_i(fltk::Button* o, const char* v) {
  cb_start(o,v)
;}
void MainMenuUIAbstract::cb_scarBtn(fltk::Button* o, const char* v) {
  ((MainMenuUIAbstract*)(o->parent()->parent()->parent()->user_data()))->cb_scarBtn_i(o,v);
}

inline void MainMenuUIAbstract::cb_exitBtn_i(fltk::Button*, void*) {
  cb_exit()
;}
void MainMenuUIAbstract::cb_exitBtn(fltk::Button* o, void* v) {
  ((MainMenuUIAbstract*)(o->parent()->parent()->user_data()))->cb_exitBtn_i(o,v);
}

inline void MainMenuUIAbstract::cb_helpBtn_i(fltk::Button*, void*) {
  cb_help()
;}
void MainMenuUIAbstract::cb_helpBtn(fltk::Button* o, void* v) {
  ((MainMenuUIAbstract*)(o->parent()->parent()->user_data()))->cb_helpBtn_i(o,v);
}

inline void MainMenuUIAbstract::cb_languagePUM_i(fltk::PopupMenu* o, void* v) {
  cb_selectLanguage(o,v)
;}
void MainMenuUIAbstract::cb_languagePUM(fltk::PopupMenu* o, void* v) {
  ((MainMenuUIAbstract*)(o->parent()->parent()->user_data()))->cb_languagePUM_i(o,v);
}

inline void MainMenuUIAbstract::cb_soundBtn_i(fltk::LightButton*, void*) {
  cb_soundToggle()
;}
void MainMenuUIAbstract::cb_soundBtn(fltk::LightButton* o, void* v) {
  ((MainMenuUIAbstract*)(o->parent()->parent()->user_data()))->cb_soundBtn_i(o,v);
}

inline void MainMenuUIAbstract::cb_fullscreenBtn_i(fltk::Button*, void*) {
  cb_fullscreen()
;}
void MainMenuUIAbstract::cb_fullscreenBtn(fltk::Button* o, void* v) {
  ((MainMenuUIAbstract*)(o->parent()->parent()->user_data()))->cb_fullscreenBtn_i(o,v);
}

MainMenuUIAbstract::MainMenuUIAbstract(int x, int y, int width, int height, const char* label): fltk::Widget(x,y,width,height,label) {
  fltk::Group* w;
  
  {
fltk::Group* o = mainContainer = new fltk::Group(0, 0, 800, 580);
    w = o;
    o->shortcut(0xff1b);
    o->user_data((void*)(this));
    o->begin();
    
    {
fltk::Widget* o = appTitle = new fltk::Widget(12, 6, 775, 54, _("Application Title") );
      o->box(fltk::HIGHLIGHT_UP_BOX);
      o->labeltype(fltk::EMBOSSED_LABEL);
      o->labelsize(32);
      o->textsize(32);
    }
    
    {
fltk::Group* o = new fltk::Group(12, 89, 775, 375, _("Select a Test Category") );
      o->box(fltk::ENGRAVED_BOX);
      o->labeltype(fltk::ENGRAVED_LABEL);
      o->labelsize(18);
      o->textsize(18);
      o->begin();
      
      {
fltk::Group* o = new fltk::Group(13, 10, 590, 120);
        o->labeltype(fltk::ENGRAVED_LABEL);
        o->begin();
        
        {
fltk::Button* o = motorcycleBtn = new fltk::Button(0, 0, 130, 120, _("Motorcycle") );
          o->labelsize(14);
          o->textsize(14);
          o->callback((fltk::Callback*)cb_motorcycleBtn, (void*)("motorcycle"));
        }
        
        {
fltk::Button* o = carBtn = new fltk::Button(153, 0, 130, 120, _("Car") );
          o->labelsize(14);
          o->textsize(14);
          o->callback((fltk::Callback*)cb_carBtn, (void*)("car"));
        }
        
        {
fltk::Button* o = truckBtn = new fltk::Button(306, 0, 130, 120, _("Truck") );
          o->labelsize(14);
          o->textsize(14);
          o->callback((fltk::Callback*)cb_truckBtn, (void*)("truck"));
        }
        
        {
fltk::Button* o = busBtn = new fltk::Button(459, 0, 130, 120, _("Bus") );
          o->labelsize(14);
          o->textsize(14);
          o->callback((fltk::Callback*)cb_busBtn, (void*)("bus"));
        }
        o->end();
      }
      
      {
fltk::Group* o = new fltk::Group(13, 140, 590, 120);
        o->begin();
        
        {
fltk::Button* o = smotorcycleBtn = new fltk::Button(0, 0, 130, 120, _("Motorcycle Special Category") );
          o->labelsize(14);
          o->textsize(14);
          o->callback((fltk::Callback*)cb_smotorcycleBtn, (void*)("smotorcycle"));
          o->align(fltk::ALIGN_WRAP);
          o->deactivate();
        }
        
        {
fltk::Button* o = scarBtn = new fltk::Button(153, 0, 130, 120, _("Car Special Category") );
          o->labelsize(14);
          o->textsize(14);
          o->callback((fltk::Callback*)cb_scarBtn, (void*)("scar"));
          o->align(fltk::ALIGN_WRAP);
          o->deactivate();
        }
        o->end();
      }
      o->end();
      fltk::Group::current()->resizable(o);
    }
    
    {
fltk::Group* o = new fltk::Group(12, 471, 775, 85);
      o->box(fltk::ENGRAVED_BOX);
      o->begin();
      
      {
fltk::Button* o = exitBtn = new fltk::Button(18, 11, 60, 60, _("Quit") );
        o->callback((fltk::Callback*)cb_exitBtn);
      }
      
      {
fltk::Button* o = helpBtn = new fltk::Button(536, 11, 60, 60, _("Help") );
        o->callback((fltk::Callback*)cb_helpBtn);
      }
      
      {
fltk::PopupMenu* o = languagePUM = new fltk::PopupMenu(218, 8, 178, 35, _("Select Language") );
        o->labelsize(14);
        o->textsize(14);
        o->callback((fltk::Callback*)cb_languagePUM);
        o->begin();
        
        {
fltk::Item* o = new fltk::Item(_("Greek") );
          o->labelsize(14);
          o->textsize(14);
          o->user_data((void*)("greek"));
        }
        
        {
fltk::Item* o = new fltk::Item(_("English") );
          o->labelsize(14);
          o->textsize(14);
          o->user_data((void*)("english"));
        }
        
        {
fltk::Item* o = new fltk::Item(_("Russian") );
          o->labelsize(14);
          o->textsize(14);
          o->user_data((void*)("russian"));
        }
        
        {
fltk::Item* o = new fltk::Item(_("Albanian") );
          o->labelsize(14);
          o->textsize(14);
          o->user_data((void*)("albanian"));
        }
        o->end();
      }
      
      {
fltk::LightButton* o = soundBtn = new fltk::LightButton(439, 11, 90, 60, _("Dictation") );
        o->labelfont(fltk::HELVETICA_BOLD);
        o->callback((fltk::Callback*)cb_soundBtn);
      }
      
      {
fltk::Button* o = fullscreenBtn = new fltk::Button(216, 50, 180, 26, _("Fullscreen") );
        o->type(fltk::Button::TOGGLE);
        o->shortcut(0xffc8);
        o->callback((fltk::Callback*)cb_fullscreenBtn);
      }
      o->end();
    }
    o->end();
  }
}

void MainMenuUIAbstract::cb_exit() {
}

void MainMenuUIAbstract::cb_help() {
}

void MainMenuUIAbstract::cb_fullscreen() {
}

void MainMenuUIAbstract::cb_start(fltk::Widget* pBtn, const char* tCategory) {
}

void MainMenuUIAbstract::cb_selectLanguage(fltk::Widget* sItem, void* userdata) {
}

void MainMenuUIAbstract::cb_soundToggle() {
}
