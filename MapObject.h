/*
	Date: June 18, 2012
	File Name: MapObject.h
	Version: 1.00
	IDE: MPLAB IDE v8.80
	Compiler: C99

	Description: This file contains the definition of the MAP
	data structure.  This file was created just to 
	further seperate out the structure of the library.

*/

#ifndef MAP_OBJECT_H
	#define MAP_OBJECT_H

#include "LinkedList.h"

struct _Map_
{
	LINKED_LIST KeyList;
	LINKED_LIST ValueList;
};

typedef struct _Map_ MAP;
	
#endif // end of MAP_OBJECT_H
