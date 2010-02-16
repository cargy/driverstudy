//      config.c
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
#ifndef CONFIG_H
#define CONFIG_H

#define APPLICATIONTITLE "Driver Study"
#define DRIVERSTUDYVERSION "0.7.5"
#define DEBUG


#define DATABASE "ExerBase.db"
// DATABASE MAPPINGS
#define DBCARID 1
#define DBMOTORCYCLEID 2
#define DBTRUCKID 3
#define DBBUSID 4

#define DBGREEKID 1
#define DBENGLISHID 2
#define DBRUSSIAN 3
#define DBALBANIANID 4

// gettext
#define PACKAGE "DriverStudy"
#define LOCALEDIR "./po"
#include <libintl.h>
#define _(String) gettext (String)
#define gettext_noop(String) String
#define N_(String) gettext_noop (String)
//#define _(String) (String)
//#define N_(String) String
//#define textdomain(Domain)
//#define bindtextdomain(Package, Directory)
     



#define MAXANSWERSIZE 500
#define MAXSNDFILESIZE 255

#define MAXQUESTIONSIZE 500
#define MAXIMGFILESIZE 255

#endif /* CONFIG_H */ 
