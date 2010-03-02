//      dlg.h
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


#ifndef DLG_H
#define DLG_H

#include <fltk/Style.h>
namespace dlg
{
	enum {
		BEEP_DEFAULT = 0,
		BEEP_MESSAGE,
		BEEP_ERROR,
		BEEP_QUESTION,
		BEEP_PASSWORD,
		BEEP_NOTIFICATION
	};
	
	enum {
		POS_MONITOR_CENTER = 0,
		POS_WINDOW_CENTER,
		POS_BUTTON_HOTSPOT,
		POS_WM
	};
		

	void message(const char *, ...);
	void alert(const char *, ...);
	int  ask(const char *, ...);
	int  ask(const char *, const char*, ...);
	int  choice(const char *q,
			  const char *b0, const char *b1, const char *b2, ...);
	int  choice(const char *q,
		  const char *b0, const char *b1, const char *b2, const char* dt, ...);
	int  choice_alert(const char *q,
			  const char *b0, const char *b1, const char *b2, ...);
	const char *input(const char *label, const char *deflt = 0, ...);
	const char *password(const char *label, const char *deflt = 0, ...);
	void beep(int type = BEEP_DEFAULT);
	void beep_on_dialog(bool);
	bool beep_on_dialog();
	void position(int type = POS_MONITOR_CENTER);
	
	void format(int bw, int bh, const char* label, int pos);

	extern const char* message_window_label;
	extern float message_window_timeout;

	extern bool message_window_scrollable;

	// pointers you can use to change FLTK to a foreign language:
	extern const char* no;
	extern const char* yes;
	extern const char* ok;
	extern const char* cancel;

	extern fltk::NamedStyle* button_style;
	extern fltk::NamedStyle* message_style;
	extern fltk::NamedStyle* icon_style;

	#define ICON_W 50
	#define ICON_H 50
	#define BORDER_W 10
	#define BORDER_H 10
	#define INPUT_W 270
	extern int min_button_w;
	extern int min_button_h;
};

#endif /* DLG_H */ 
