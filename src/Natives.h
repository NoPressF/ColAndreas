#ifndef _INCL_NATIVES
#define _INCL_NATIVES

#include "ColAndreas.h"

namespace ColAndreasNatives
{
	cell AMX_NATIVE_CALL CA_Init(AMX *amx, const cell* params);
	cell AMX_NATIVE_CALL CA_RayCastLine(AMX *amx, const cell* params);
	cell AMX_NATIVE_CALL CA_RayCastLineExtraID(AMX *amx, const cell* params);
	cell AMX_NATIVE_CALL CA_RayCastLineID(AMX *amx, const cell* params);
	cell AMX_NATIVE_CALL CA_RayCastMultiLine(AMX *amx, const cell* params);
	cell AMX_NATIVE_CALL CA_RayCastLineAngle(AMX *amx, const cell* params);
	cell AMX_NATIVE_CALL CA_RayCastReflectionVector(AMX *amx, const cell* params);
	cell AMX_NATIVE_CALL CA_RayCastLineNormal(AMX *amx, const cell* params);
	cell AMX_NATIVE_CALL CA_LoadFromDff(AMX *amx, const cell* params);
	cell AMX_NATIVE_CALL CA_CreateObject(AMX *amx, const cell* params);
	cell AMX_NATIVE_CALL CA_DestroyObject(AMX *amx, const cell* params);
	cell AMX_NATIVE_CALL CA_IsValidObject(AMX *amx, const cell* params);
	cell AMX_NATIVE_CALL CA_EulerToQuat(AMX *amx, const cell* params);
	cell AMX_NATIVE_CALL CA_QuatToEuler(AMX *amx, const cell* params);
	cell AMX_NATIVE_CALL CA_RemoveBuilding(AMX *amx, const cell* params);
	cell AMX_NATIVE_CALL CA_RestoreBuilding(AMX *amx, const cell* params);
	cell AMX_NATIVE_CALL CA_SetObjectPos(AMX *amx, const cell* params);
	cell AMX_NATIVE_CALL CA_SetObjectRot(AMX *amx, const cell* params);
	cell AMX_NATIVE_CALL CA_GetModelBoundingSphere(AMX *amx, const cell* params);
	cell AMX_NATIVE_CALL CA_GetModelBoundingBox(AMX *amx, const cell* params);
	cell AMX_NATIVE_CALL CA_SetObjectExtraID(AMX* amx, const cell* params);
	cell AMX_NATIVE_CALL CA_GetObjectExtraID(AMX* amx, const cell* params);
	cell AMX_NATIVE_CALL CA_ContactTest(AMX *amx, const cell* params);

	// Extended natives
	cell AMX_NATIVE_CALL CA_RayCastLineEx(AMX *amx, const cell* params);
	cell AMX_NATIVE_CALL CA_RayCastLineAngleEx(AMX *amx, const cell* params);
};
#endif
