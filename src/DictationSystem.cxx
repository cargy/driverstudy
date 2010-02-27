//      DictationSystem.cxx
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


#include "DictationSystem.h"
#ifdef DEBUG
#include <cstdio>
#endif
#include <audiere.h>
using namespace audiere;

DictationSystem::DictationSystem()
{
	audio_driver = "";
}

int DictationSystem::initialize()
{
	// Initial global objects.
	device = OpenDevice(audio_driver);
	if (!device) {
		printf("Couldn't initialize audio_driver: %s\n",audio_driver);
		return 0;
	}
	printf("Opened Device: %s\n" ,device->getName() );
	audio_driver = device->getName();
	return 1;
}

bool DictationSystem::initialized()
{
	if (device) return true;
	else return false;
}

void DictationSystem::deinitialize()
{
	if (device) 
	{
		if (sound && sound->isPlaying()) sound->stop();
		device=0;
	}
}

const char* DictationSystem::audio_device()
{
	return audio_driver;
}

int DictationSystem::play(const char* audiofilename)
{
	if (!device) return 0;
	
	if ( sound && sound->isPlaying() ) sound->stop();
	
	char sndFile[255];
	sprintf(sndFile,"%s/%s.%s",VOICE_DIR,audiofilename,VOICE_EXT);
	sound = OutputStreamPtr(OpenSound(device,sndFile, false));
	if (sound) sound->play();
#ifdef DEBUG
	else {printf("Couldn't play file: %s\n",sndFile);return 0;}
	printf("sndFile = %s\n",sndFile);
#else
	else return 0;
#endif //DEBUG
	return 1;
}

