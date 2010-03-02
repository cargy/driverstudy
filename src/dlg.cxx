//      dlg.cxx
//      
//      Copyright 2010 Argyriadis Christos <krizz@Freak>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.



#include <fltk/Window.h>
#include <fltk/x.h>

#include "dlg.h"
#include <fltk/run.h>
#include <fltk/ReturnButton.h>
#include <fltk/SecretInput.h>
#include <fltk/TextDisplay.h>
#include <fltk/string.h>
#include <fltk/Monitor.h>
#include <fltk/events.h>

#ifdef WIN32
# include <windows.h>
#endif

namespace dlg
{

	/*! Set this to change the title of message(), alert(), ask(), choice(), etc. windows. */
	const char* message_window_label= NULL;

	/*! Set this to a positive value to cause the message(), alert(), ask(), choice(), etc. windows to close automatically after this timeout.  If the timeout expires, -1 will be returned by the functions that return int. The timeout value is in seconds. */
	float message_window_timeout= 0;

	/*! When this is set to true, then (all) message windows will use scrollbars if the given message is too long. */
	bool message_window_scrollable = 0;

	/*! You can change this string to convert fltk to a foreign language. */
	const char* no = "&No";
	/*! You can change this string to convert fltk to a foreign language. */
	const char* yes= "&Yes";
	/*! You can change this string to convert fltk to a foreign language. */
	const char* ok = "&OK";
	/*! You can change this string to convert fltk to a foreign language. */
	const char* cancel= "&Cancel";
	
	int min_button_w = 75;
	int min_button_h = 21;

	// beep on dialogs state
	static bool sBeepOnDlg = false;
	
	//set default dialog pos
	static int sDlgPosition = POS_MONITOR_CENTER;

	/*! You get the state enable beep on default message dialog 
		(like ask, choice, input, ...) 
		by  using this function with true (default is false) */
	bool beep_on_dialog() {return sBeepOnDlg;}

	/*! You can enable beep on default message dialog 
		(like ask, choice, input, ...) 
		by  using this function with true (default is false) */
	void beep_on_dialog(bool b) {sBeepOnDlg=b;}
	
	void position(int type) { sDlgPosition=type;}
	
	void format(int bw, int bh, const char* label, int pos)
	{
		min_button_w = bw;
		min_button_h = bh;
		message_window_label = label;
		sDlgPosition = pos;
	}
		

	static void b_revert(fltk::Style* s) {
	  //s->labelsize_ = 16;
	}
	static fltk::NamedStyle b_style("Button", b_revert, &button_style);
	/*! This Style is used for the buttons for all the popup windows.
	  You can change the textfont() or textsize() to make them print
	  differently.
	*/
	fltk::NamedStyle* button_style = &b_style;

	static void m_revert(fltk::Style* s) {
	  s->box_ = fltk::NO_BOX;
	}
	static fltk::NamedStyle m_style("Message", m_revert, &message_style);
	/*! This Style is used for the label area for all the popup windows.
	  You can change the textfont() or textsize() to make them print
	  differently.
	*/
	fltk::NamedStyle* message_style = &m_style;

	static void i_revert(fltk::Style* s) {
	  s->box_ = fltk::THIN_UP_BOX;
	  s->labelfont_ = fltk::TIMES_BOLD;
	  s->labelsize_ = 34;
	  s->color_ = fltk::GRAY99;
	  s->textcolor_ = s->labelcolor_ = fltk::BLUE;
	}
	static fltk::NamedStyle i_style("Icon", i_revert, &icon_style);
	/*! This Style is used for the 50x50 icon area on the left of all
	  the popup windows. You can change the colors or font used here.
	*/
	fltk::NamedStyle* icon_style = &i_style;

	static int button_number;
	static void set_button_number(fltk::Widget* w, long a) {
	  button_number = a;
	  w->window()->make_exec_return(false);
	}

	static int timed_out;
	static void timeout_handler(void *w) {
	  timed_out = 1;
	  ((fltk::Window *)w)->make_exec_return(false);
	}

	static fltk::Input *textfield;

	// In this call the buttons are in backwards order from right to left,
	// this is because "no" (0) is on the right.
	static int innards(
	  const char* iconlabel,
	  const char *istr, int itype,
	  const char* fmt, va_list ap,
	  const char *b0,
	  const char *b1,
	  const char *b2)
	{
	  fltk::Group* saved_current_group = fltk::Group::current();
	  fltk::load_theme();
	  fltk::Window window(3*BORDER_W+ICON_W+INPUT_W, 3*BORDER_H+ICON_H+min_button_h);
	  if(message_window_label && message_window_label[0] != 0)
		window.copy_label(message_window_label);

	  // add message, icon and possibly text input control
	  window.begin();

	  // This keeps the icon from resizing.
	  fltk::Group ig(BORDER_W, BORDER_H, ICON_W, ICON_H);
	  ig.begin();
	  fltk::Widget icon(0, 0, ICON_W, ICON_H);
	  icon.style(icon_style);
	  icon.label(iconlabel);
	  ig.resizable(0); // no, THIS keeps the icon from resizing (when a text input field is present)
	  ig.end();

	  fltk::Widget *shortMessage=NULL;
	  fltk::TextDisplay *longMessage=NULL;
	  fltk::Widget *eitherMessage=NULL;

	  // Determine the complete and formatted message to show to the user
	  char messageBuffer[100*1024]; // 100k max
	  messageBuffer[sizeof(messageBuffer)-1]=0;
	  if (!strcmp(fmt,"%s")) {
		strncpy(messageBuffer,va_arg(ap, const char*),sizeof(messageBuffer)-1);
	  } else if (!strchr(fmt, '%')) {
		strncpy(messageBuffer,fmt,sizeof(messageBuffer)-1);
	  } else {
		vsnprintf(messageBuffer, sizeof(messageBuffer)-1, fmt, ap);
	  }

	  // determine if we need to have a scrollable area or not
	  bool scrollable=false;
	  if(message_window_scrollable) {
		// it's allowed to scroll, let's see if it needs to
		int w=(INPUT_W+3*BORDER_W+ICON_W+10), h=0;
		setfont(window.labelfont(), window.labelsize());
		fltk::measure(messageBuffer, w, h, fltk::ALIGN_INSIDE_TOPLEFT | fltk::ALIGN_WRAP);
		scrollable = h>(480-(3*BORDER_H+min_button_h));
	  }

	  if(scrollable) {
		// Show a scrollable text display for a long message
		eitherMessage=longMessage=new fltk::TextDisplay(2*BORDER_W+ICON_W, BORDER_H, INPUT_W, ICON_H);

		longMessage->wrap_mode(true);
		longMessage->text(messageBuffer);
		
		window.resizable(longMessage);
		window.resize_align(fltk::ALIGN_TOP|fltk::ALIGN_RIGHT);

	  } else {
		// Show a simple label for a short message
		eitherMessage=shortMessage=new fltk::Widget(2*BORDER_W+ICON_W, 0, INPUT_W, BORDER_H+ICON_H);
		shortMessage->set_flag(fltk::ALIGN_LEFT|fltk::ALIGN_INSIDE|fltk::ALIGN_WRAP);
		shortMessage->style(message_style);
	  
		window.resizable(shortMessage);
		window.resize_align(fltk::ALIGN_TOP|fltk::ALIGN_RIGHT);
		//w->size_range(window.w(), window.h(), 0, window.h());

		shortMessage->label(messageBuffer);
	  }
	  
	  // Add the text input field if there should be one
	  if (istr) {
		if (textfield)
		  window.add(textfield);
		else
		  textfield = new fltk::Input(2*BORDER_W+ICON_W, 0, 0, 0);

		textfield->type(itype);
		textfield->text(istr);
		
		int h=(int)textfield->textsize()+10;
		textfield->resize(
		  textfield->x(),
		  (eitherMessage->h())-(h),
		  INPUT_W,
		  h
		);

		eitherMessage->h(eitherMessage->h()-h-(shortMessage ? 0 : BORDER_H));
		window.set_focus(textfield);
	  }

	  window.end();

	  
	  
	  // calculate into (w,h) how much wider and taller the window should become
	  window.layout();
	  int w = 400;
	  int h = 0;
	  if(shortMessage) {
		setfont(eitherMessage->labelfont(), eitherMessage->labelsize());
		fltk::measure(shortMessage->label(), w, h, shortMessage->flags());
		w+=6; h+=2*BORDER_H;
		w -= shortMessage->w(); if (w < 0) w = 0;
		h -= shortMessage->h(); if (h < 0) h = 0;

	  } else /*if(longMessage)*/ {
		w = 640-window.w(); if (w < 0) w = 0;
		h = 400-window.h(); if (h < 0) h = 0;

	  }
	  window.resize(window.x(),window.y(),window.w()+w, window.h()+h);
	  window.layout();


	  // add buttons
	  window.begin();

	  const char* blabels[3];
	  blabels[0] = b0;
	  blabels[1] = b1;
	  blabels[2] = b2;

	  // Button with '*' is default, if none the left-most one is:
	  int default_button = 0;
	  int i;
	  for (i = 2; i >= 0; i--) if (blabels[i]) {
		if (!default_button) default_button = i;
		if (blabels[i][0] == '*') {blabels[i]++; default_button = i;}
	  }

	  int bx = window.w();
	  
	  int bh;// = min_button_h;
	  for (i = 3; i--;) {
		if (blabels[i]) {
		  fltk::Button* button;
		  
		  button = new fltk::Button(0, 0, 0, 0, blabels[i]);
		  
		  button->style(button_style);
		  button->callback(set_button_number, i);
		  
		  // calculate the horizontal size of the button
		  int bw;
		  button->measure_label(bw, bh);

		  // add a 5+5 px padding in button
		  bw += 10; 
		  bh += 10;

		  // and include any glyph width
		  //bw += glyph_width;
		  //bh += glyph_width;

		  // enforce button min size
		  bw = bw < min_button_w ? min_button_w : bw;
		  bh = bh < min_button_h ? min_button_h : bh;

		  // accumulate the horizontal button position based on button widths
		  bx -= bw + BORDER_W;
		  int by = window.h()-(BORDER_H+bh);

		  // finally position and size the button
		  button->resize(bx, by, bw, bh);
		  
		  if (i == default_button) {
			  if ( sDlgPosition == POS_BUTTON_HOTSPOT ) window.hotspot(button);
			  else if ( sDlgPosition == POS_MONITOR_CENTER )
			  {
				  const fltk::Monitor m = fltk::Monitor::find(window.x(),window.y());
				  window.position((m.w() - window.w())/2, (m.h() - window.h())/2);
			  }	
			  else if ( sDlgPosition == POS_WINDOW_CENTER )
			  {
				  // not implemented yet
				  // i have to recognize the parent window
				  // that called me (if any)
			  }
					
			  if (!istr) window.set_focus(button);
			  button->shortcut(fltk::ReturnKey);
			  button->add_shortcut(fltk::KeypadEnter);
		  }

		  		 
		}
	  }

	  window.end();

	  timed_out=0;
	  if(message_window_timeout>0) {
		fltk::add_timeout(message_window_timeout,timeout_handler,&window);
	  }

	  button_number = 0;
	  window.exec();

	  if(message_window_timeout>0) {
		remove_timeout(timeout_handler,&window);
	  }

	  if (istr)
		window.remove(textfield); // don't destroy it yet
	  fltk::Group::current(saved_current_group);

	  delete shortMessage;
	  delete longMessage;

	  return timed_out ? -1 : button_number;
	}



	/*!
	  \image html fl_message.gif
	  Displays a printf-style message in a pop-up box with an "OK" button,
	  waits for the user to hit the button. The message will wrap to fit
	  the window, or may be many lines by putting '\\n' characters into
	  it. The enter key is a shortcut for the OK button.
	*/
	void message(const char *fmt, ...) {
	  if (beep_on_dialog()) (beep(BEEP_MESSAGE));
	  va_list ap;
	  va_start(ap, fmt);
	  innards("i", 0, 0, fmt, ap, ok, 0, 0);
	  va_end(ap);

	}

	/*!
	  \image html fl_alert.gif
	  Same as fltk::message() except for the "!" symbol. 
	*/
	void alert(const char *fmt, ...) {
	  if (beep_on_dialog()) (beep(BEEP_ERROR));
	  va_list ap;
	  va_start(ap, fmt);
	  innards("!", 0, 0, fmt, ap, ok, 0, 0);
	  va_end(ap);
	}

	/*!
	  \image html fl_ask.gif
	  Displays a printf-style message in a pop-up box with an "Yes" and
	  "No" button and waits for the user to hit a button. The return value
	  is 1 if the user hits Yes, 0 if they pick No. The enter key is a
	  shortcut for Yes and ESC is a shortcut for No.

	  If message_window_timeout is used, then -1 will be returned if the
	  timeout expires.
	*/
	int ask(const char *fmt,  ...) {
	  if (beep_on_dialog()) (beep(BEEP_QUESTION));
	  va_list ap;
	  va_start(ap, fmt);
	  int r = innards("?", 0, 0, fmt, ap, no, yes, 0);
	  va_end(ap);
	  return r;
	}
	
	int ask(const char *fmt, const char* dt  ...) {
	  if (beep_on_dialog()) (beep(BEEP_QUESTION));
	  const char* sTitle = message_window_label;
	  message_window_label = dt;
	  va_list ap;
	  va_start(ap, dt);
	  int r = innards("?", 0, 0, fmt, ap, no, yes, 0);
	  va_end(ap);
	  message_window_label = sTitle;
	  return r;
	}

	/*!
	  \image html fl_choice.gif
	  Shows the message with three buttons below it marked with the
	  strings b0, b1, and b2. Returns 0, 1, or 2 depending on which button
	  is hit. If one of the strings begins with the special character '*'
	  then the associated button will be the default which is selected
	  when the enter key is pressed. ESC is a shortcut for b2.

	  If message_window_timeout is used, then -1 will be returned if the
	  timeout expires.
	*/
	int choice(const char*fmt,const char *b0,const char *b1,const char *b2,...){
		if (beep_on_dialog()) (beep(BEEP_QUESTION));
	  va_list ap;
	  va_start(ap, b2);
	  int r = innards("?", 0, 0, fmt, ap, b2, b1, b0);
	  va_end(ap);
	  if(r<0)
		  return r;
	  return 2-r;
	}
	
	int choice(const char*fmt,const char *b0,const char *b1,const char *b2, const char* dt, ...){
		if (beep_on_dialog()) (beep(BEEP_QUESTION));
	  const char* sTitle = message_window_label;
	  message_window_label = dt;
	  va_list ap;
	  va_start(ap, dt);
	  int r = innards("?", 0, 0, fmt, ap, b2, b1, b0);
	  va_end(ap);
	  message_window_label = sTitle;
	  if(r<0)
		  return r;
	  return 2-r;
	}

	/*! Same as choice() except a "!" icon is used instead of a "?" */
	int choice_alert(const char*fmt,const char *b0,const char *b1,const char *b2,...){
	  if (beep_on_dialog()) (beep(BEEP_QUESTION));
	  va_list ap;
	  va_start(ap, b2);
	  int r = innards("!", 0, 0, fmt, ap, b2, b1, b0);
	  va_end(ap);
	  if(r<0)
		  return r;
	  return 2-r;
	}

	static const char* input_innards(const char* fmt, va_list ap,
					 const char* defstr, uchar type) {
	  int r = innards("?", defstr ? defstr : "", type,
			  fmt, ap, dlg::cancel, dlg::ok, 0);
	  return r>0 ? textfield->text() : 0;
	}

	/*!
	  \image html fl_input.gif
	  Pops up a window displaying a string, lets the user edit it, and
	  return the new value. The cancel button returns NULL. The returned
	  pointer is only valid until the next time fltk::input() is
	  called. Due to back-compatability, the arguments to any printf
	  commands in the label are after the default value.

	  If message_window_timeout is used, then 0 will be returned if the
	  timeout expires.
	*/
	const char* input(const char *fmt, const char *defstr, ...) {
	  if (beep_on_dialog()) (beep(BEEP_QUESTION));
	  va_list ap;
	  va_start(ap, defstr);
	  const char* r = input_innards(fmt, ap, defstr, fltk::Input::NORMAL);
	  va_end(ap);
	  return r;
	}

	/*!
	  \image html fl_password.gif
	  Same as dlg::input() except an dlg::SecretInput field is used. 
	*/
	const char *password(const char *fmt, const char *defstr, ...) {
	  if (beep_on_dialog()) (beep(BEEP_PASSWORD));
	  va_list ap;
	  va_start(ap, defstr);
	  const char* r = input_innards(fmt, ap, defstr, fltk::Input::SECRET);
	  va_end(ap);
	  return r;
	}

	/*!
	  Generates a simple beep message 
	*/
	void beep(int type) {
	  switch (type) {
	#if defined(WIN32)
		case BEEP_QUESTION :
		case BEEP_PASSWORD :
		  MessageBeep(MB_ICONQUESTION);
		  break;
		case BEEP_MESSAGE :
		  MessageBeep(MB_ICONASTERISK);
		  break;
		case BEEP_NOTIFICATION :
		  MessageBeep(MB_ICONASTERISK);
		  break;
		case BEEP_ERROR :
		  MessageBeep(MB_ICONERROR);
		  break;
		default :
		  MessageBeep(0xFFFFFFFF);
		  break;
	#elif defined(__APPLE__)
		  //    case fltk::BEEP_DEFAULT :
		  //    case fltk::BEEP_ERROR :
		  //      break;
		default :
		  SysBeep(30); // this is the only simple beep available so use it for all
		  break;
	#else
		case BEEP_DEFAULT :
		case BEEP_ERROR :
		  if (!fltk::xdisplay) fltk::open_display();

		  XBell(fltk::xdisplay, 100);
		  break;
		default :
		  if (!fltk::xdisplay) fltk::open_display();

		  XBell(fltk::xdisplay, 50);
		  break;
	#endif // WIN32
	  }
	}
}

