//      TimerProgressBar.h
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


#ifndef TIMERPROGRESSBAR_H
#define TIMERPROGRESSBAR_H

#include <fltk/ProgressBar.h>

using namespace fltk;
	
class TimerProgressBar: public fltk::ProgressBar
{
	protected:
		  Color warningColor; // warning progressbar color
		  int handle(int);
		  void draw();
		  
	public:
		TimerProgressBar(int x, int y, int w, int h);
		void warning_color(Color col)	{ warningColor = col; }
		Color warning_color() 	{ return warningColor; }
		void starttime(int stime) { mMax = mPresent = (double)stime; }
		void stoptime(int stime) { mMin = (double)stime; }
		void settime(int stime) { mPresent = (double)stime; redraw();}
		int gettime() { return (int)mPresent; }
		int starttime() { return mMax; }
		void warningtime(int stime) { mWarning = stime; }
		void start();
		void stop();
		bool status() { return run; }
			
	private:
		/* add your private declarations */
		int mWarning;
		bool run;
};

#endif /* TIMERPROGRESSBAR_H */ 
