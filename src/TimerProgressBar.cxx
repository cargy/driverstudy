//      TimerProgressBar.cxx
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

#include "config.h"
#include "TimerProgressBar.h"
#include <fltk/damage.h>
#include <fltk/Box.h>
#include <fltk/draw.h>
#include <fltk/events.h>
#include <stdio.h>
#include <ctime>
#include <time.h>
#ifndef _WIN32
#  include <sys/time.h>
#endif /* !_WIN32 */
using namespace fltk;

TimerProgressBar::TimerProgressBar(int x, int y, int w, int h)
	: fltk::ProgressBar(x,y,w,h)
{
	mMin = mPresent = 0;
	mMax = mPresent = 60;
	mWarning = 10;
	mShowPct = true;
	box(DOWN_BOX);
	selection_color(BLUE);
	warning_color(RED);
	color(WHITE);
	textcolor(BLACK);
	run = false;
}

void TimerProgressBar::start()
{
  #ifdef _WIN32
    repeat_timeout(1.0f);
  #else
    {struct timeval t; gettimeofday(&t, 0);
    float delay = 1.0f-float(t.tv_usec)*.000001f;
    if (delay < .1f || delay > .9f) delay = 1.0f;
    add_timeout(1.0f);}
  #endif	
	run = true;
}

void TimerProgressBar::stop()
{
	remove_timeout();
	run = false;
}
	
int TimerProgressBar::handle(int event) {
	if (!run) return 0;
  switch (event) {
  case SHOW:
    remove_timeout();
    if (!run) break;
  case TIMEOUT:
	if (gettime() < 1 )
	{
		stop();
		//callbak
		do_callback();
	}
	else
	{
		#ifdef _WIN32
		step(-1);
		repeat_timeout(1.0f);
		#else
		{struct timeval t; gettimeofday(&t, 0);
		step(-1);
		float delay = 1.0f-float(t.tv_usec)*.000001f;
		if (delay < .1f || delay > .9f) delay = 1.0f;
		#ifdef DEBUG 
		printf("delay: %f\n", delay );
		#endif
		add_timeout(delay);}
		#endif
	}
    break;
  case HIDE:
    remove_timeout();
    break;
  default:
    return 0;
  }
  return 0;
}

void TimerProgressBar::draw() {
  drawstyle(style(),flags());
  if (damage() & DAMAGE_ALL) draw_box();
  Rectangle r(w(),h());
  box()->inset(r);
  if (mPresent > mMax) mPresent = mMax;
  if (mPresent < mMin) mPresent = mMin;
  double pct = mMax != mMin ? (mPresent - mMin) / (mMax - mMin) : 0;
  int dtime = mPresent;
  
  int hour,min,sec;

	hour=dtime/3600;
	dtime=dtime%3600;
	min=dtime/60;
	dtime=dtime%60;
	sec=dtime;


  if (vertical()) {
    int barHeight = int(r.h()*pct+.5);
    r.y(r.y()+r.h()-barHeight);
    r.h(barHeight);
  } else {
    r.w(int(r.w()*pct+.5));
  }

  setcolor(selection_color());
  if (gettime() <= mWarning ) setcolor(warning_color()); 
  fillrect(r);

  if (mShowPct) {
    char buffer[30];
    //sprintf(buffer, "%d%%", int(pct * 100+.5));
    sprintf(buffer, "%02d:%02d:%02d", hour,min,sec);
    //int fW = 0, fH;
    //fltk::measure( buffer, fW, fH );

    setcolor(textcolor());
    setfont(this->labelfont(), this->labelsize());
    drawtext(buffer, Rectangle(w(),h()), ALIGN_CENTER);
  }
}
