/*
	Date: June 18, 2012
	File Name: Map.h
	Version: 1.00
	IDE: MPLAB IDE v8.80
	Compiler: C99

	Description:
		This file contains all the the method headers for interfacing to the
		Map library.  This should be included in any file that references
		a MAP.  All methods and macro's have their documentation above
		their declaration.
*/

/*! \mainpage Map Library
 *  \brief This is a Library written in C for manipulating a Map Data Structure.
 *  \author brodie
 *  \version 1.00
 *  \date   June 18, 2012
 */
 
#ifndef MAP_H
 	#define MAP_H
 	
#include "GenericTypeDefs.h"

#include "MapObject.h"
#include "MapConfig.h"

/*
	Function: MAP *CreateMap(MAP *Map, INT32(*KeyCompareTo)(const void *Key1, const void *Key2), INT32(*ValueCompareTo)(const void *Value1, const void *Value2), void (*KeyCustomFreeMethod)(void *Data), void (*ValueCustomFreeMethod)(void *Data))

	Parameters: 
		MAP *Map - The address at which the MAP will be inititalized.
		If NULL is passed in then this method will create a MAP out of a
		the heap with a call to MapMemAlloc()(User Supplied Define).

		INT32 (*KeyCompareTo)(const void *Data1, const void *Data2) - A pointer to a method that
		the user defines for comparing Keys in the MAP.  This method is called 
		everytime the user calls any adding, deleting, removal, or a contains method.
		This method only looks for equality, not difference since there is no sorting in the MAP.

		INT32 (*ValueCompareTo)(const void *Data1, const void *Data2) - A pointer to a method that
		the user defines for comparing Values in the MAP.  This method is called 
		everytime the user calls the contains method.  Multiple Values can exist in the MAP.
		This method only looks for equality, not difference since there is no sorting in the MAP.

		void(*KeyCustomFreeMethod)(void *Data) - A pointer to a method that the
		user defines.  Each time a MAP entry is deleted this method will
		be called to delete the data at the MAP index.  Leave blank for no special deletion.

		void(*ValueCustomFreeMethod)(void *Data) - A pointer to a method that the
		user defines.  Each time a MAP entry is deleted this method will
		be called to delete the data at the MAP index.  Leave blank for no special deletion.

	Returns:
		MAP* - The address at which the newly initialized MAP resides
		in memory.  If a new MAP could not be created then (MAP*)NULL is returned.

	Description: Creates and/or intializes a MAP in memory.

	Notes: None
*/
/**
		* @brief Creates and/or intializes a MAP in memory.
		* @param *Map - The address at which the MAP will be inititalized.
		If NULL is passed in then this method will create a MAP out of a
		the heap with a call to MapMemAlloc()(User Supplied Define).
		* @param *KeyCompareTo- A pointer to a method that
		the user defines for comparing Keys in the MAP.  This method is called 
		everytime the user calls any adding, deleting, removal, or a contains method.
		This method only looks for equality, not difference since there is no sorting in the MAP.
		* @param *ValueCompareTo - A pointer to a method that
		the user defines for comparing Values in the MAP.  This method is called 
		everytime the user calls the contains method.  Multiple Values can exist in the MAP.
		This method only looks for equality, not difference since there is no sorting in the MAP.
		* @param *KeyCustomFreeMethod - A pointer to a method that the
		user defines.  Each time a MAP entry is deleted this method will
		* @param *ValueCustomFreeMethod - A pointer to a method that the
		user defines.  Each time a MAP entry is deleted this method will
		be called to delete the data at the MAP index.  Leave blank for no special deletion.
		be called to delete the data at the MAP index.  Leave blank for no special deletion.
		* @return MAP* - The address at which the newly initialized MAP resides
		in memory.  If a new MAP could not be created then (MAP*)NULL is returned.
		* @note None
		* @sa MapMemAlloc()
		* @since v1.0
*/
MAP *CreateMap(MAP *Map, INT32(*KeyCompareTo)(const void *Key1, const void *Key2), INT32(*ValueCompareTo)(const void *Value1, const void *Value2), void (*KeyCustomFreeMethod)(void *Data), void (*ValueCustomFreeMethod)(void *Data));

/*
	Function: void *MapGetValue(MAP *Map, const void *Key)

	Parameters:

		MAP *Map - The MAP that will have an entry retieved.

		const void *Key - The unique key that will be used to look the data up.

	Returns:
		void* - The value associated with the key.  (void*)NULL otherwise.

	Description: 
		Retrieves but does not delete a value.  The value retrieved is the associated with the unique key.
	
	Notes: None
*/
/**
		* @brief Retrieves but does not delete a value.  The value retrieved is the associated with the unique key.
		* @param *Map - The MAP that will have an entry retieved.
		* @param *Key - The unique key that will be used to look the data up.
		* @return void* - The value associated with the key.  (void*)NULL otherwise.
		* @note None
		* @sa MapAddValue()
		* @since v1.0
*/
void *MapGetValue(MAP *Map, const void *Key);

/*
	Function: BOOL MapAddValue(MAP *Map, const void *Key, const void *Value)

	Parameters: 
		MAP *Map - The MAP that will have the value added to it.

		const void *Key - The unique key that will be added to the MAP.  The value associated with this
		key is a one to one relationship.  Multiple values of the same value can exist, but they are all
		mapped to a unique key.  Each key must be unique.

		const void *Value - The value that will be associated with the key.

	Returns:
		BOOL - TRUE if the key and value were successfully added to the MAP, FALSE otherwise.

	Description:
		Adds a key and value to a MAP.  The key must unique, meaning the key cannot already exist in the map.

	Notes: None
*/
/**
		* @brief Adds a key and value to a MAP.  The key must unique, meaning the key cannot already exist in the map.
		* @param *Map - The MAP that will have the value added to it.
		* @param *Key - The unique key that will be added to the MAP.  The value associated with this
		key is a one to one relationship.  Multiple values of the same value can exist, but they are all
		mapped to a unique key.  Each key must be unique.
		* @param *Value - The value that will be associated with the key.
		* @return BOOL - TRUE if the key and value were successfully added to the MAP, FALSE otherwise.
		* @note None
		* @sa MapGetValue()
		* @since v1.0
*/
BOOL MapAddValue(MAP *Map, const void *Key, const void *Value);

/*
	Function: BOOL MapContainsKey(MAP *Map, const void *Key)

	Parameters:
		MAP *Map - The MAP which will be searched for the specified key.

		const void *Key - The key to find in the MAP.

	Returns:
		BOOL - TRUE if the key was found, FALSE otherwise.

	Description:
		Searches a MAP for the specified key.

	Notes: USING_MAP_CONTAINS_KEY must be defined as 1 in MapConfig.h in order to use this method.
*/
/**
		* @brief Searches a MAP for the specified key.
		* @param *Map - The MAP which will be searched for the specified key.
		* @param *Key - The key to find in the MAP.
		* @return BOOL - TRUE if the key was found, FALSE otherwise.
		* @note USING_MAP_CONTAINS_KEY must be defined as 1 in MapConfig.h in order to use this method.
		* @sa MapContainsValue()
		* @since v1.0
*/
#if (USING_MAP_CONTAINS_KEY == 1)
	BOOL MapContainsKey(MAP *Map, const void *Key);
#endif // end of USING_MAP_CONTAINS_KEY

/*
	Function: BOOL MapContainsValue(MAP *Map, const void *Value)

	Parameters:
		MAP *Map - The MAP which will be searched for the specified value.

		const void *Value - The value to find in the MAP.

	Returns:
		BOOL - TRUE if the value was found, FALSE otherwise.

	Description: 
		Searches a MAP for the specified value.

	Notes: USING_MAP_CONTAINS_VALUE must be defined as 1 in MapConfig.h in order to use this method.
*/
/**
		* @brief Searches a MAP for the specified value.
		* @param *Map - The MAP which will be searched for the specified value.
		* @param *Value - The value to find in the MAP.
		* @return BOOL - TRUE if the value was found, FALSE otherwise.
		* @note USING_MAP_CONTAINS_VALUE must be defined as 1 in MapConfig.h in order to use this method.
		* @sa MapContainsKey()
		* @since v1.0
*/
#if (USING_MAP_CONTAINS_VALUE == 1)
	BOOL MapContainsValue(MAP *Map, const void *Value);
#endif // end of USING_MAP_CONTAINS_VALUE

/*
	Function: BOOL MapDeleteValue(MAP *Map, void *Key)

	Parameters:
		MAP *Map - The MAP which will have a key and value deleted from it.

		void *Key - The key used to look up which entry to delete.

	Returns:
		BOOL - TRUE if the key and its associated value were found and deleted.  FALSE otherwise.

	Description: 
		Deletes a key and it's associated value within the specified MAP.

	Notes: USING_MAP_DELETE_VALUE must be defined as 1 in MapConfig.h in order to use this method.
*/
/**
		* @brief Deletes a key and it's associated value within the specified MAP.
		* @param *Map - The MAP which will have a key and value deleted from it.
		* @param *Key - The key used to look up which entry to delete.
		* @return BOOL - TRUE if the key and its associated value were found and deleted.  FALSE otherwise.
		* @note USING_MAP_DELETE_VALUE must be defined as 1 in MapConfig.h in order to use this method.
		* @sa MapDeleteAll()
		* @since v1.0
*/
#if (USING_MAP_DELETE_VALUE == 1)
	BOOL MapDeleteValue(MAP *Map, void *Key);
#endif // end of USING_MAP_DELETE_VALUE

/*
	Function: BOOL MapDeleteAll(MAP *Map)

	Parameters: 
		MAP *Map - The MAP that will have all its entries deleted.

	Returns:
		BOOL - TRUE if all entries were deleted, or the MAP was empty.  FALSE otherwise.

	Description:
		Deletes all the entries in a MAP.

	Notes: USING_MAP_DELETE_ALL_METHOD must be defined as 1 in MapConfig.h in order to use this method.
*/
/**
		* @brief Deletes all the entries in a MAP.
		* @param *Map - The MAP that will have all its entries deleted.
		* @return BOOL - TRUE if all entries were deleted, or the MAP was empty.  FALSE otherwise.
		* @note USING_MAP_DELETE_ALL_METHOD must be defined as 1 in MapConfig.h in order to use this method.
		* @sa MapDeleteValue()
		* @since v1.0
*/
#if (USING_MAP_DELETE_ALL_METHOD == 1)
	BOOL MapDeleteAll(MAP *Map);
#endif // end of USING_MAP_DELETE_ALL_METHOD

/*
	Function: UINT32 MapGetSize(MAP *Map)

	Parameters:
		MAP *Map - The MAP that will have it's size returned.

	Returns:
		UINT32 - The number of entries in the MAP.  0 if there was an error.

	Description: 
		Returns the size of the specified MAP.  The size is the number of entries in the MAP.

	Notes: USING_MAP_GET_SIZE must be defined as 1 in MapConfig.h in order to use this method.
*/
/**
		* @brief Returns the size of the specified MAP.  The size is the number of entries in the MAP.
		* @param *Map - The MAP that will have it's size returned.
		* @return UINT32 - The number of entries in the MAP.  0 if there was an error.
		* @note USING_MAP_GET_SIZE must be defined as 1 in MapConfig.h in order to use this method.
		* @sa None
		* @since v1.0
*/
#if (USING_MAP_GET_SIZE == 1)
	UINT32 MapGetSize(MAP *Map);
#endif // end of USING_MAP_GET_SIZE

/*
	Function: const BYTE *MapGetLibraryVersion(void)

	Parameters:
		None

	Returns:
		const BYTE* - The current version of the Map library in human readable form.

	Description:
		Gets the current library version of the Map library.

	Notes: USING_MAP_GET_LIBRARY_VERSION must be defined as 1 in MapConfig.h in order to use this method.
*/
/**
		* @brief Gets the current library version of the Map library.
		* @return const BYTE* - The current version of the Map library in human readable form.
		* @note USING_MAP_GET_LIBRARY_VERSION must be defined as 1 in MapConfig.h in order to use this method.
		* @sa None
		* @since v1.0
*/
#if(USING_MAP_GET_LIBRARY_VERSION == 1)
	const BYTE *MapGetLibraryVersion(void);
#endif // end of USING_MAP_GET_LIBRARY_VERSION
	
#endif // end of MAP_H