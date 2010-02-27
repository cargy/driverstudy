// generated by Fast Light User Interface Designer (fluid) version 2.1000

#ifndef MainMenuUIAbstract_h
#define MainMenuUIAbstract_h
#include "config.h"
#include <fltk/Window.h>
#include <fltk/Group.h>
#include <fltk/Widget.h>
#include <fltk/Button.h>
#include <fltk/PopupMenu.h>
#include <fltk/Item.h>
#include <fltk/LightButton.h>
#include <fltk/StatusBarGroup.h>

class MainMenuUIAbstract : public fltk::Window  {
public:
  MainMenuUIAbstract(int x, int y, int width, int height, const char* label);
  fltk::Group *mainContainer;
    fltk::Widget *appTitle;
        fltk::Button *motorcycleBtn;
private:
        inline void cb_motorcycleBtn_i(fltk::Button*, const char*);
        static void cb_motorcycleBtn(fltk::Button*, const char*);
public:
        fltk::Button *carBtn;
private:
        inline void cb_carBtn_i(fltk::Button*, const char*);
        static void cb_carBtn(fltk::Button*, const char*);
public:
        fltk::Button *truckBtn;
private:
        inline void cb_truckBtn_i(fltk::Button*, const char*);
        static void cb_truckBtn(fltk::Button*, const char*);
public:
        fltk::Button *busBtn;
private:
        inline void cb_busBtn_i(fltk::Button*, const char*);
        static void cb_busBtn(fltk::Button*, const char*);
public:
        fltk::Button *smotorcycleBtn;
private:
        inline void cb_smotorcycleBtn_i(fltk::Button*, const char*);
        static void cb_smotorcycleBtn(fltk::Button*, const char*);
public:
        fltk::Button *scarBtn;
private:
        inline void cb_scarBtn_i(fltk::Button*, const char*);
        static void cb_scarBtn(fltk::Button*, const char*);
public:
      fltk::Button *exitBtn;
private:
      inline void cb_exitBtn_i(fltk::Button*, void*);
      static void cb_exitBtn(fltk::Button*, void*);
public:
      fltk::Button *helpBtn;
private:
      inline void cb_helpBtn_i(fltk::Button*, void*);
      static void cb_helpBtn(fltk::Button*, void*);
public:
      fltk::PopupMenu *languagePUM;
private:
      inline void cb_languagePUM_i(fltk::PopupMenu*, void*);
      static void cb_languagePUM(fltk::PopupMenu*, void*);
public:
      fltk::LightButton *soundBtn;
private:
      inline void cb_soundBtn_i(fltk::LightButton*, void*);
      static void cb_soundBtn(fltk::LightButton*, void*);
public:
      fltk::Button *fullscreenBtn;
private:
      inline void cb_fullscreenBtn_i(fltk::Button*, void*);
      static void cb_fullscreenBtn(fltk::Button*, void*);
public:
    fltk::StatusBarGroup *statusBar;
  virtual void cb_exit();
  virtual void cb_help();
  virtual void cb_fullscreen();
  virtual void cb_start(fltk::Widget* pBtn, const char* tCategory);
  virtual void cb_selectLanguage(fltk::Widget* sItem, void* userdata);
  virtual void cb_soundToggle();
};
#endif
