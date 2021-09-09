#pragma once
//used in: virtual function grabbing
#include "../../../other/utilities/utilities.h"

//declarations
struct receivedtable_t;

struct clientclass_t
{
public:
	void* ptrCreateFn;
	void* ptrCreateEventFn;
	char* szNetworkedName;
	receivedtable_t* ptrReceivedTable;
	clientclass_t* ptrNext;
	eClassId iClassID;
};

struct IBaseClientDll
{
private:
	enum eIndices
	{
		GETCLIENTCLASSES = 8
	};
public:
	clientclass_t* get_client_classes() //gets our client class list for the netvar manager
	{
		return nUtilities::vfunc<clientclass_t*(__thiscall*)(IBaseClientDll*)>(this, GETCLIENTCLASSES)(this);
	}
};