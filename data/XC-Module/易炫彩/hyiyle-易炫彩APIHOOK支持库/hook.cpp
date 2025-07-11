#include "module_XAPIHOOK.h"

BOOL XHOOK_SetHook(PVOID* ppSystemFunction, PVOID pHookFunction){
	return Mhook_SetHook(ppSystemFunction, pHookFunction);
}

BOOL XHOOK_Unhook(PVOID* ppHookedFunction){
	return Mhook_Unhook(ppHookedFunction);
}