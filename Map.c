/*
	Date: June 18, 2012
	File Name: Map.c
	Version: 1.00
	IDE: MPLAB IDE v8.80
	Compiler: C99

	Description:  This file contains all the necessary code
	for manipulating the MAP data structure.  An explination
	of each function can be found in Map.h.

*/

#include "Map.h"

#if (MAP_USE_MALLOC == 1)
	#include "stdlib.h"
#endif // end of USE_MALLOC

MAP *CreateMap(MAP *Map, INT32(*KeyCompareTo)(const void *Key1, const void *Key2), INT32(*ValueCompareTo)(const void *Value1, const void *Value2), void (*KeyCustomFreeMethod)(void *Data), void (*ValueCustomFreeMethod)(void *Data))
{
	MAP *TempMap;

	#if (USING_MAP_SAFE_MODE == 1)
		if(KeyCompareTo == (INT32(*)(const void *, const void *))NULL)
			return (MAP*)NULL;

		#if (USING_MAP_CONTAINS_VALUE == 1)
			if(ValueCompareTo == (INT32(*)(const void *, const void *))NULL)
				return (MAP*)NULL;
		#endif // end of USING_MAP_CONTAINS_VALUE

	#endif // end of USING_MAP_SAFE_MODE

	if(Map == (MAP*)NULL)
	{
		TempMap = (MAP*)MapMemAlloc(sizeof(MAP));

		if(TempMap == (MAP*)NULL)
			return (MAP*)NULL;
	}
	else
	{
		TempMap = Map;
	}

	if(CreateLinkedList(&(TempMap->KeyList), KeyCompareTo, KeyCustomFreeMethod) == (LINKED_LIST*)NULL)
	{
		if(!Map)
			MapMemDealloc(TempMap);

		return (MAP*)NULL;
	}

	if(CreateLinkedList(&(TempMap->ValueList), ValueCompareTo, ValueCustomFreeMethod) == (LINKED_LIST*)NULL)
	{
		if(!Map)
			MapMemDealloc(TempMap);

		return (MAP*)NULL;
	}

	return (MAP*)TempMap;
}
#if (USING_MAP_DELETE_ALL_METHOD == 1)
	BOOL MapDeleteAll(MAP *Map)
	{
		BOOL Outcome1, Outcome2;

		#if (USING_MAP_SAFE_MODE == 1)
			if(Map == (MAP*)NULL)
				return (BOOL)FALSE;
		#endif // end of USING_MAP_SAFE_MODE

		Outcome1 = LinkedListDeleteAll(&(Map->KeyList));

		Outcome2 = LinkedListDeleteAll(&(Map->ValueList));

		return (BOOL)(Outcome1 && Outcome2);
	}
#endif // end of USING_MAP_DELETE_ALL_METHOD

#if (USING_MAP_CONTAINS_KEY == 1)
	BOOL MapContainsKey(MAP *Map, const void *Key)
	{
		UINT32 ReturnVal;

		#if (USING_MAP_SAFE_MODE == 1)
			if(Map == (MAP*)NULL)
				return (BOOL)FALSE;
		#endif // end of USING_MAP_SAFE_MODE

		ReturnVal = LinkedListContains(&(Map->KeyList), Key, FALSE, 0);

		if(ReturnVal)
			return (BOOL)TRUE;

		return (BOOL)FALSE;
	}
#endif // end of USING_MAP_CONTAINS_KEY

#if (USING_MAP_CONTAINS_VALUE == 1)
	BOOL MapContainsValue(MAP *Map, const void *Value)
	{
		UINT32 ReturnVal;

		#if (USING_MAP_SAFE_MODE == 1)
			if(Map == (MAP*)NULL)
				return (BOOL)FALSE;

			if(Map->ValueList.CompareTo == (INT32(*)(const void *, const void*))NULL)
				return (BOOL)FALSE;
		#endif // end of USING_MAP_SAFE_MODE

		ReturnVal = LinkedListContains(&(Map->ValueList), Value, FALSE, 0);

		if(ReturnVal)
			return (BOOL)TRUE;

		return (BOOL)FALSE;
	}
#endif // end of USING_MAP_CONTAINS_VALUE

void *MapGetValue(MAP *Map, const void *Key)
{
	UINT32 Index;

	#if (USING_MAP_SAFE_MODE == 1)
			if(Map == (MAP*)NULL)
				return (void*)NULL;
	#endif // end of USING_MAP_SAFE_MODE

	Index = LinkedListContains(&(Map->KeyList), Key, FALSE, 0);

	if(Index == 0)
		return (void*)NULL;

	return (void*)(LinkedListGetData(&(Map->ValueList), Index));
}

BOOL MapAddValue(MAP *Map, const void *Key, const void *Value)
{
	BOOL Outcome;

	#if (USING_MAP_SAFE_MODE == 1)
			if(Map == (MAP*)NULL)
				return (BOOL)FALSE;
	#endif // end of USING_MAP_SAFE_MODE

	// Make sure the Key remains unique
	if(LinkedListContains(&(Map->KeyList), Key, FALSE, 0) > 0)
		return (BOOL)FALSE;

	Outcome = LinkedListAdd(&(Map->KeyList), Key);

	if(!Outcome)
		return (BOOL)FALSE;

	Outcome = LinkedListAdd(&(Map->ValueList), Value);

	if(!Outcome)
	{
		// Remove the Key we just added in
		LinkedListDeleteNode(&(Map->KeyList), LinkedListContains(&(Map->KeyList), Key, FALSE, 0));
	}

	return (BOOL)TRUE;
}

#if (USING_MAP_DELETE_VALUE == 1)
	BOOL MapDeleteValue(MAP *Map, void *Key)
	{
		UINT32 Index;
		BOOL Outcome1, Outcome2;

		#if (USING_MAP_SAFE_MODE == 1)
			if(Map == (MAP*)NULL)
				return (BOOL)FALSE;

			if(LinkedListGetSize(&(Map->KeyList)) == 0)
				return (BOOL)TRUE;
		#endif // end of USING_MAP_SAFE_MODE

		Index = LinkedListContains(&(Map->KeyList), Key, FALSE, 0);

		if(Index == 0)
			return (BOOL)FALSE;

		Outcome1 = LinkedListDeleteNode(&(Map->KeyList), Index);

		Outcome2 = LinkedListDeleteNode(&(Map->ValueList), Index);

		return (BOOL)(Outcome1 && Outcome2);
	}
#endif // end of USING_MAP_DELETE_VALUE

#if (USING_MAP_GET_SIZE == 1)
	UINT32 MapGetSize(MAP *Map)
	{
		#if (USING_MAP_SAFE_MODE == 1)
			if(Map == (MAP*)NULL)
				return (UINT32)0;
		#endif // end of USING_MAP_SAFE_MODE

		return (UINT32)LinkedListGetSize((LINKED_LIST*)&(Map->KeyList));
	}
#endif // end of USING_MAP_GET_SIZE

#if(USING_MAP_GET_LIBRARY_VERSION == 1)
	const BYTE MapLibraryVersion[] = {"Map Lib v1.00\0"};

	const BYTE *MapGetLibraryVersion(void)
	{
		return (const BYTE*)MapLibraryVersion;
	}
#endif // end of USING_MAP_GET_LIBRARY_VERSION
