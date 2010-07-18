/*
 * version.h
 *
 *  Created on: May 30, 2010
 *      Author: krizz
 */

#ifndef VERSION_H_
#define VERSION_H_

#define	DRIVERSTUDY_MAJOR_VERSION	0
#define	DRIVERSTUDY_MINOR_VERSION	9
#define	DRIVERSTUDY_MICRO_VERSION	3

#define STR_VALUE(s) XSTR(s)
#define XSTR(s) #s

#define DRIVERSTUDY_VERSION DRIVERSTUDY_MAJOR_VERSION.DRIVERSTUDY_MINOR_VERSION.DRIVERSTUDY_MICRO_VERSION
#define DRIVERSTUDY_VERSION_STRING STR_VALUE(DRIVERSTUDY_VERSION)


#endif /* VERSION_H_ */
