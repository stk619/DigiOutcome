#include "netvars.h"
//used in: console logging
#include "../console/console.h"
//used in: obtaining client classes
#include "../../source_engine/interfaces/interfaces.h"

//modified form of this: https://www.unknowncheats.me/forum/counterstrike-global-offensive/209624-fast-easy-netvar-manager.html
//could also dump this to a file, but this is for a project, so i'm not so sure about file management yet
//it's also crucial that the specific types are selected for the netvars are used as they simply don't work otherwise
//even something simple as a int vs short (ItemDefintionIndex) >:|

bool nNetvarManager::allocate()
{
	//loop through the client classes, obtaining all netvars
	for (clientclass_t* ptrClientClass = nInterfaces::ptrClient->get_client_classes(); ptrClientClass; ptrClientClass = ptrClientClass->ptrNext)
		if (ptrClientClass->ptrReceivedTable != nullptr)
			nNetvarManager::dump_vars(ptrClientClass->ptrReceivedTable->szNetTableName, ptrClientClass->ptrReceivedTable);

	sConsole.log(eLogType::LOG, xorstr_("total mapped vars: %i"), nNetvarManager::umOffsets.size());
	sConsole.log(eLogType::MAIN, xorstr_("netvar manager finished allocating"));
	return true;
}

//gets called for every netvar
void nNetvarManager::dump_vars(std::string_view szNetvarName, receivedtable_t* ptrTable, std::size_t uiOffset)
{
	//loop through all props
	for (int iIndex = 0; iIndex < ptrTable->iProps; ++iIndex)
	{
		//get pointer to current prop
		receivedprop_t* ptrProp = &ptrTable->ptrProps[iIndex];
		receivedtable_t* ptrPropChild = ptrProp->ptrDataTable;

		//we dont care about the base class, we already know that
		if (std::strcmp(ptrProp->szVariablename, xorstr_("baseclass")) == 0)
			continue;

		//loop through the netvar trees :D, but only ones beginning with the letter D, this eliminates useless
		//tables, this check dropped the mapped vars from 40k, down to 1.7k saving almost a second on inject time
		if ((ptrPropChild != nullptr) && (ptrPropChild->iProps > 0) && (ptrProp->ptrDataTable->szNetTableName[0] == 'D'))
		{
			//reiterate through the vars, as netvar managers are obviously meant to be recursive functions
			nNetvarManager::dump_vars(szNetvarName, ptrPropChild, ptrProp->iOffset + uiOffset);
		}

		//string constructors aren't nice, but i don't think there's a nice enough conversion
		std::string szConstructedNetvar = std::string(szNetvarName.data()).append(xorstr_("->")).append(ptrProp->szVariablename);
		std::size_t uiHashedNetvar = sHash.hash(szConstructedNetvar);
		
		//add the prop to the unordered_map
		nNetvarManager::umOffsets[uiHashedNetvar] = ptrProp->iOffset + uiOffset;

		//printing out the values here causes the netvar manager to make the cheat load 1.2s slower
		//sConsole.log(eLogType::LOG, xorstr_("netvar found! var: %s->%s, offset: 0x%x"), szNetvarName.data(), ptrProp->szVariablename, ptrProp->iOffset);

		//looking for a specific var
		//if (ptrProp->iOffset == 0x25f)
			//sConsole.log(eLogType::LOG, xorstr_("netvar found! var: %s->%s, offset: 0x%x"), szNetvarName.data(), ptrProp->szVariablename, ptrProp->iOffset);

		/*
		we'd be using the input output stream to list the netvars to a file, again, don't know about including this as of right now
		*/
	}
}