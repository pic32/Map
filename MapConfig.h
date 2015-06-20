/*
	Date: June 18, 2012
	File Name: MapConfig.h
	Version: 1.00
	IDE: MPLAB IDE v8.80
	Compiler: C99

	Description:  This file contains all the necessary definitions
	for configuring the Map Library.

*/

#ifndef MAP_CONFIG_H
	#define MAP_CONFIG_H

#define USING_MAP_DELETE_ALL_METHOD							1
#define USING_MAP_CONTAINS_KEY								1
#define USING_MAP_CONTAINS_VALUE							1
#define USING_MAP_DELETE_VALUE								1
#define USING_MAP_GET_SIZE									1

/*
	*If USING_MAP_GET_LIBRARY_VERSION is set to 1 then
	MapGetLibraryVersion() is available.
*/
#define USING_MAP_GET_LIBRARY_VERSION						1

#define USING_MAP_SAFE_MODE									1

/**
	*This defines what method the Map library will use to 
	allocate memory and deallocated.  This allows the Map 
	library to be integrated into an OS.
*/
#define MapMemAlloc(Mem)									malloc(Mem)

/**
	*The method used for freeing up memory.
*/
#define MapMemDealloc(Mem)									free(Mem)

/**
	*Define USE_MALLOC as 1 to enable the stdlib.h file included
	with Map.c.
*/
#define MAP_USE_MALLOC										1

/**
	*If the user isn't using malloc then include the file that will
	be needed for accessing whatever method MemAlloc() and MemDealloc()
	implement, below.
*/
//#include "Your memory file here.h"
	
#endif // end of MAP_CONFIG_H