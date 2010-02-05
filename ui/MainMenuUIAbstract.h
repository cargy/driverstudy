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

class MainMenuUIAbstract : public fltk::Window  {
public:
  MainMenuUIAbstract(int x, int y, int width, int height, const char* label);
  fltk::Group *mainContainer;
      fltk::PopupMenu *languagePUM;
};
#endif