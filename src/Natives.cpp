#include "Natives.h"
#include "DynamicWorld.h"
#include <renderware.h>

// Maximum number of raycasts
#define MAX_MULTICAST_SIZE 99

//*********************************************************************************************************//
// native functions ***************************************************************************************//
//*********************************************************************************************************//

cell AMX_NATIVE_CALL ColAndreasNatives::CA_Init(AMX *amx, cell* params)
{
	if (ColAndreasComponent::instance_->colDataLoaded == true)
	{
		if (ColAndreasComponent::instance_->colInit == false)
		{
			ColAndreasComponent::instance_->core_->printLn("Loading Map.");
			ColAndreasComponent::instance_->collisionWorld->colandreasInitMap();
			ColAndreasComponent::instance_->colInit = true;
			ColAndreasComponent::instance_->core_->printLn("Loaded Map.                             ");
			return 1;
		}
		else
		{
			ColAndreasComponent::instance_->core_->printLn("Tried to reload Map.");
			return 1;
		}
	}
	return 0;
}


cell AMX_NATIVE_CALL ColAndreasNatives::CA_RayCastLine(AMX *amx, cell* params)
{
	cell* addr[3];

	// Adding a small value prevents a potential crash if all values are the same
	btVector3 Start = btVector3(btScalar(amx_ctof(params[1]) + 0.00001), btScalar(amx_ctof(params[2]) + 0.00001), btScalar(amx_ctof(params[3]) + 0.00001));
	btVector3 End = btVector3(btScalar(amx_ctof(params[4])), btScalar(amx_ctof(params[5])), btScalar(amx_ctof(params[6])));
	btVector3 Result;
	int32_t Model = 0;

	if (ColAndreasComponent::instance_->collisionWorld->performRayTest(Start, End, Result, Model))
	{
		//Get our adderesses for the last 3
		amx_GetAddr(amx, params[7], &addr[0]);
		amx_GetAddr(amx, params[8], &addr[1]);
		amx_GetAddr(amx, params[9], &addr[2]);

		*addr[0] = amx_ftoc(Result.getX());
		*addr[1] = amx_ftoc(Result.getY());
		*addr[2] = amx_ftoc(Result.getZ());

		return Model;
	}
	return 0;
}


cell AMX_NATIVE_CALL ColAndreasNatives::CA_RayCastLineID(AMX *amx, cell* params)
{
	cell* addr[3];

	// Adding a small value prevents a potential crash if all values are the same
	btVector3 Start = btVector3(btScalar(amx_ctof(params[1]) + 0.00001), btScalar(amx_ctof(params[2]) + 0.00001), btScalar(amx_ctof(params[3]) + 0.00001));
	btVector3 End = btVector3(btScalar(amx_ctof(params[4])), btScalar(amx_ctof(params[5])), btScalar(amx_ctof(params[6])));
	btVector3 Result;
	uint16_t Index = 0;

	if (ColAndreasComponent::instance_->collisionWorld->performRayTestID(Start, End, Result, Index))
	{
		//Get our adderesses for the last 3
		amx_GetAddr(amx, params[7], &addr[0]);
		amx_GetAddr(amx, params[8], &addr[1]);
		amx_GetAddr(amx, params[9], &addr[2]);

		*addr[0] = amx_ftoc(Result.getX());
		*addr[1] = amx_ftoc(Result.getY());
		*addr[2] = amx_ftoc(Result.getZ());

		return Index;
	}
	return 0;
}


cell AMX_NATIVE_CALL ColAndreasNatives::CA_RayCastLineExtraID(AMX *amx, cell* params)
{
	cell* addr[3];

	// Adding a small value prevents a potential crash if all values are the same
	btVector3 Start = btVector3(btScalar(amx_ctof(params[2]) + 0.00001), btScalar(amx_ctof(params[3]) + 0.00001), btScalar(amx_ctof(params[4]) + 0.00001));
	btVector3 End = btVector3(btScalar(amx_ctof(params[5])), btScalar(amx_ctof(params[6])), btScalar(amx_ctof(params[7])));
	btVector3 Result;
	uint16_t Data = 0;

	if (ColAndreasComponent::instance_->collisionWorld->performRayTestExtraID(Start, End, Result, params[1], Data))
	{
		//Get our adderesses for the last 3
		amx_GetAddr(amx, params[8], &addr[0]);
		amx_GetAddr(amx, params[9], &addr[1]);
		amx_GetAddr(amx, params[10], &addr[2]);

		*addr[0] = amx_ftoc(Result.getX());
		*addr[1] = amx_ftoc(Result.getY());
		*addr[2] = amx_ftoc(Result.getZ());

		return Data;
	}
	return 0;
}


cell AMX_NATIVE_CALL ColAndreasNatives::CA_RayCastLineEx(AMX *amx, cell* params)
{
	cell* addr[10];

	// Adding a small value prevents a potential crash if all values are the same
	btVector3 Start = btVector3(btScalar(amx_ctof(params[1]) + 0.00001), btScalar(amx_ctof(params[2]) + 0.00001), btScalar(amx_ctof(params[3]) + 0.00001));
	btVector3 End = btVector3(btScalar(amx_ctof(params[4])), btScalar(amx_ctof(params[5])), btScalar(amx_ctof(params[6])));
	btVector3 Position;
	btQuaternion Rotation;
	btVector3 Result;
	int32_t Model = 0;

	if (ColAndreasComponent::instance_->collisionWorld->performRayTestEx(Start, End, Result, Rotation, Position, Model))
	{
		amx_GetAddr(amx, params[7], &addr[0]);
		amx_GetAddr(amx, params[8], &addr[1]);
		amx_GetAddr(amx, params[9], &addr[2]);
		amx_GetAddr(amx, params[10], &addr[3]);
		amx_GetAddr(amx, params[11], &addr[4]);
		amx_GetAddr(amx, params[12], &addr[5]);
		amx_GetAddr(amx, params[13], &addr[6]);
		amx_GetAddr(amx, params[14], &addr[7]);
		amx_GetAddr(amx, params[15], &addr[8]);
		amx_GetAddr(amx, params[16], &addr[9]);

		*addr[0] = amx_ftoc(Result.getX());
		*addr[1] = amx_ftoc(Result.getY());
		*addr[2] = amx_ftoc(Result.getZ());
		*addr[3] = amx_ftoc(Rotation.getX());
		*addr[4] = amx_ftoc(Rotation.getY());
		*addr[5] = amx_ftoc(Rotation.getZ());
		*addr[6] = amx_ftoc(Rotation.getW());
		*addr[7] = amx_ftoc(Position.getX());
		*addr[8] = amx_ftoc(Position.getY());
		*addr[9] = amx_ftoc(Position.getZ());

		return Model;
	}
	return 0;
}

cell AMX_NATIVE_CALL ColAndreasNatives::CA_RayCastLineAngle(AMX *amx, cell* params)
{
	cell* addr[6];

	// Adding a small value prevents a potential crash if all values are the same
	btVector3 Start = btVector3(btScalar(amx_ctof(params[1]) + 0.00001), btScalar(amx_ctof(params[2]) + 0.00001), btScalar(amx_ctof(params[3]) + 0.00001));
	btVector3 End = btVector3(btScalar(amx_ctof(params[4])), btScalar(amx_ctof(params[5])), btScalar(amx_ctof(params[6])));
	btVector3 Result;
	btVector3 Rotation;
	btScalar RX;
	btScalar RY;
	btScalar RZ;
	int32_t model = 0;

	if (ColAndreasComponent::instance_->collisionWorld->performRayTestAngle(Start, End, Result, RX, RY, RZ, model))
	{
		//Get our adderesses for the last 6
		amx_GetAddr(amx, params[7], &addr[0]);
		amx_GetAddr(amx, params[8], &addr[1]);
		amx_GetAddr(amx, params[9], &addr[2]);
		amx_GetAddr(amx, params[10], &addr[3]);
		amx_GetAddr(amx, params[11], &addr[4]);
		amx_GetAddr(amx, params[12], &addr[5]);

		*addr[0] = amx_ftoc(Result.getX());
		*addr[1] = amx_ftoc(Result.getY());
		*addr[2] = amx_ftoc(Result.getZ());
		*addr[3] = amx_ftoc(RX);
		*addr[4] = amx_ftoc(RY);
		*addr[5] = amx_ftoc(RZ);

		return model;
	}
	return 0;
}

cell AMX_NATIVE_CALL ColAndreasNatives::CA_RayCastLineAngleEx(AMX *amx, cell* params)
{
	cell* addr[12];

	// Adding a small value prevents a potential crash if all values are the same
	btVector3 Start = btVector3(btScalar(amx_ctof(params[1]) + 0.00001), btScalar(amx_ctof(params[2]) + 0.00001), btScalar(amx_ctof(params[3]) + 0.00001));
	btVector3 End = btVector3(btScalar(amx_ctof(params[4])), btScalar(amx_ctof(params[5])), btScalar(amx_ctof(params[6])));
	btVector3 Result;
	btVector3 Rotation;
	btQuaternion ObjectRotation;
	btVector3 ObjectPosition;
	btScalar RX;
	btScalar RY;
	btScalar RZ;
	int32_t Model = 0;

	if (ColAndreasComponent::instance_->collisionWorld->performRayTestAngleEx(Start, End, Result, RX, RY, RZ, ObjectRotation, ObjectPosition, Model))
	{
		//Get our adderesses for the last 5
		amx_GetAddr(amx, params[7], &addr[0]);
		amx_GetAddr(amx, params[8], &addr[1]);
		amx_GetAddr(amx, params[9], &addr[2]);
		amx_GetAddr(amx, params[10], &addr[3]);
		amx_GetAddr(amx, params[11], &addr[4]);
		amx_GetAddr(amx, params[12], &addr[5]);

		amx_GetAddr(amx, params[13], &addr[6]);
		amx_GetAddr(amx, params[14], &addr[7]);
		amx_GetAddr(amx, params[15], &addr[8]);
		amx_GetAddr(amx, params[16], &addr[9]);
		amx_GetAddr(amx, params[17], &addr[10]);
		amx_GetAddr(amx, params[18], &addr[11]);


		*addr[0] = amx_ftoc(Result.getX());
		*addr[1] = amx_ftoc(Result.getY());
		*addr[2] = amx_ftoc(Result.getZ());
		*addr[3] = amx_ftoc(RX);
		*addr[4] = amx_ftoc(RY);
		*addr[5] = amx_ftoc(RZ);

		*addr[6] = amx_ftoc(ObjectPosition.getX());
		*addr[7] = amx_ftoc(ObjectPosition.getY());
		*addr[8] = amx_ftoc(ObjectPosition.getZ());

		ColAndreasComponent::instance_->collisionWorld->QuatToEuler(ObjectRotation, Result);

		*addr[9] = amx_ftoc(Result.getX());
		*addr[10] = amx_ftoc(Result.getY());
		*addr[11] = amx_ftoc(Result.getZ());

		return Model;
	}
	return 0;
}


cell AMX_NATIVE_CALL ColAndreasNatives::CA_RayCastMultiLine(AMX *amx, cell* params)
{
	// Adding a small value prevents a potential crash if all values are the same
	btVector3 Start = btVector3(btScalar(amx_ctof(params[1]) + 0.00001), btScalar(amx_ctof(params[2]) + 0.00001), btScalar(amx_ctof(params[3]) + 0.00001));
	btVector3 End = btVector3(btScalar(amx_ctof(params[4])), btScalar(amx_ctof(params[5])), btScalar(amx_ctof(params[6])));
	btAlignedObjectArray < btVector3 > Result;

	int size = params[12];

	// Invalid size
	if (size <= 0 || size > MAX_MULTICAST_SIZE) return -1;

	int *ModelIDs;
	ModelIDs = new int[size];

	for (int i = 0; i < size; i++)
		ModelIDs[i] = 0;

	if (ColAndreasComponent::instance_->collisionWorld->performRayTestAll(Start, End, Result, ModelIDs, size))
	{
		if (Result.size() <= size)
		{
			cell* rawDataX = NULL;
			cell* rawDataY = NULL;
			cell* rawDataZ = NULL;
			cell* rawDataDist = NULL;
			cell* rawDataModel = NULL;

			amx_GetAddr(amx, params[7], &rawDataX);
			amx_GetAddr(amx, params[8], &rawDataY);
			amx_GetAddr(amx, params[9], &rawDataZ);
			amx_GetAddr(amx, params[10], &rawDataDist);
			amx_GetAddr(amx, params[11], &rawDataModel);

			for (uint16_t i = 0; i < Result.size(); i++)
			{
				rawDataX[i] = amx_ftoc(Result[i].getX());
				rawDataY[i] = amx_ftoc(Result[i].getY());
				rawDataZ[i] = amx_ftoc(Result[i].getZ());

				btScalar distance = ColAndreasComponent::instance_->collisionWorld->getDist3D(Start, btVector3(Result[i].getX(), Result[i].getY(), Result[i].getZ()));
				rawDataDist[i] = amx_ftoc(distance);
				rawDataModel[i] = ModelIDs[i];
			}
			return Result.size();
		}
		return -1;
	}
	return 0;
}


cell AMX_NATIVE_CALL ColAndreasNatives::CA_LoadFromDff(AMX *amx, cell* params)
{
	if (!ColAndreasComponent::instance_->colDataLoaded)
	{
		ColAndreasComponent::instance_->core_->printLn("ERROR: CA_LoadFromDff : ColAndreas.cadb not loaded; you need it even if you only want custom models collision");
		return -1;
	}

	int32_t modelid = static_cast<int32_t>(params[1]);
	char* _dffModelName;
	amx_StrParam(amx, params[2], _dffModelName);
	std::string dffModelName = std::string("models/") + _dffModelName;

	rw::Clump dffData;
	std::ifstream file(dffModelName, std::ios::binary);
	if (file.fail()) 
	{
		ColAndreasComponent::instance_->core_->printLn("ERROR: CA_LoadFromDff: File %s not found in models directory.", _dffModelName);
		return -1;
	}

	if (dffData.read(file, modelid))
	{
		ColAndreasComponent::instance_->core_->printLn("ColAndreas: Loaded custom model collision. ID: %d, Model Name: %s", modelid, _dffModelName);
		return 1;
	}

	ColAndreasComponent::instance_->core_->printLn("ColAndreas: Unable to load collision from given dff file (Corrupted data or no collision). ID: %d, Model Name: %s", modelid, _dffModelName);
	return 0;
}

cell AMX_NATIVE_CALL ColAndreasNatives::CA_CreateObject(AMX *amx, cell* params)
{
	if(!ColAndreasComponent::instance_->colDataLoaded)
	{
		ColAndreasComponent::instance_->core_->printLn("ERROR: CA_CreateObject : Collision data not found.");
		return -1;
	}
	
	int32_t modelid = static_cast<int32_t>(params[1]);
	uint16_t addtomanager = static_cast<uint16_t>(params[8]);

	if (ColAndreasComponent::instance_->collisionWorld->getModelRef(modelid) != 65535)
	{
		btVector3 position = btVector3(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
		btVector3 rotation = btVector3(amx_ctof(params[5]), amx_ctof(params[6]), amx_ctof(params[7]));

		btQuaternion quatrotation;
		ColAndreasComponent::instance_->collisionWorld->EulerToQuat(rotation, quatrotation);

		return ColAndreasComponent::instance_->collisionWorld->createColAndreasMapObject(addtomanager, modelid, quatrotation, position);
	}

	// Model had no collision
	return -1;
}


cell AMX_NATIVE_CALL ColAndreasNatives::CA_DestroyObject(AMX *amx, cell* params)
{
	uint16_t index = static_cast<uint16_t>(params[1]);

	if (index >= MAX_MAP_OBJECTS) return -1;
	return ColAndreasComponent::instance_->collisionWorld->objectManager->removeObjectManager(index);
}

cell AMX_NATIVE_CALL ColAndreasNatives::CA_IsValidObject(AMX *amx, cell* params)
{
	uint16_t index = static_cast<uint16_t>(params[1]);

	if (index >= MAX_MAP_OBJECTS) return -1;
	return ColAndreasComponent::instance_->collisionWorld->objectManager->validObjectManager(index);
}

cell AMX_NATIVE_CALL ColAndreasNatives::CA_EulerToQuat(AMX *amx, cell* params)
{
	cell* addr[4];

	btQuaternion Result;

	btVector3 rotation = btVector3(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3]));

	ColAndreasComponent::instance_->collisionWorld->EulerToQuat(rotation, Result);

	amx_GetAddr(amx, params[4], &addr[0]);
	amx_GetAddr(amx, params[5], &addr[1]);
	amx_GetAddr(amx, params[6], &addr[2]);
	amx_GetAddr(amx, params[7], &addr[3]);

	*addr[0] = amx_ftoc(Result.getX());
	*addr[1] = amx_ftoc(Result.getY());
	*addr[2] = amx_ftoc(Result.getZ());
	*addr[3] = amx_ftoc(Result.getW());

	return 1;
}


cell AMX_NATIVE_CALL ColAndreasNatives::CA_QuatToEuler(AMX *amx, cell* params)
{
	cell* addr[3];

	btVector3 Result;

	btQuaternion rotation = btQuaternion(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));

	ColAndreasComponent::instance_->collisionWorld->QuatToEuler(rotation, Result);

	amx_GetAddr(amx, params[5], &addr[0]);
	amx_GetAddr(amx, params[6], &addr[1]);
	amx_GetAddr(amx, params[7], &addr[2]);

	*addr[0] = amx_ftoc(Result.getX());
	*addr[1] = amx_ftoc(Result.getY());
	*addr[2] = amx_ftoc(Result.getZ());

	return 1;
}

cell AMX_NATIVE_CALL ColAndreasNatives::CA_RemoveBuilding(AMX *amx, cell* params)
{
	if (!ColAndreasComponent::instance_->colInit)
	{
		removeBuildingData tmp;
		tmp.r_Model = static_cast<int16_t>(params[1]);

		tmp.r_X = amx_ctof(params[2]);
		tmp.r_Y = amx_ctof(params[3]);
		tmp.r_Z = amx_ctof(params[4]);
		tmp.r_Radius = amx_ctof(params[5]);
		ColAndreasComponent::instance_->collisionWorld->removedManager->addBuilding(tmp);
		return 1;
	}
	else
	{
		ColAndreasComponent::instance_->core_->printLn("ERROR: CA_RemoveBuilding : Map has already been initialized. Use this before CA_Init.");
	}
	return 0;
}

cell AMX_NATIVE_CALL ColAndreasNatives::CA_RestoreBuilding(AMX *amx, cell* params)
{
	if (ColAndreasComponent::instance_->colInit)
	{
		removeBuildingData tmp;
		tmp.r_Model = static_cast<int16_t>(params[1]);

		tmp.r_X = amx_ctof(params[2]);
		tmp.r_Y = amx_ctof(params[3]);
		tmp.r_Z = amx_ctof(params[4]);
		tmp.r_Radius = amx_ctof(params[5]);
		ColAndreasComponent::instance_->collisionWorld->removedManager->restoreBuilding(tmp);
		return 1;
	}
	else
	{
		ColAndreasComponent::instance_->core_->printLn("ERROR: CA_RestoreBuilding : Map is not initialized yet. Use this after CA_Init.");
	}
	return 0;
}

cell AMX_NATIVE_CALL ColAndreasNatives::CA_SetObjectPos(AMX *amx, cell* params)
{
	uint16_t index = static_cast<uint16_t>(params[1]);
	btVector3 position = btVector3(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
	return ColAndreasComponent::instance_->collisionWorld->objectManager->setObjectPosition(index, position);
}

cell AMX_NATIVE_CALL ColAndreasNatives::CA_SetObjectRot(AMX *amx, cell* params)
{
	uint16_t index = static_cast<uint16_t>(params[1]);
	btQuaternion result;
	btVector3 rotation = btVector3(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
	ColAndreasComponent::instance_->collisionWorld->EulerToQuat(rotation, result);
	return ColAndreasComponent::instance_->collisionWorld->objectManager->setObjectRotation(index, result);
}


cell AMX_NATIVE_CALL ColAndreasNatives::CA_GetModelBoundingSphere(AMX *amx, cell* params)
{
	int32_t modelid = static_cast<int32_t>(params[1]);
	
	if ((modelid >= 0 && modelid < 20000) || (modelid <= -1000 && modelid > -30000))
	{
		btScalar Radius;
		btVector3 Center;

		if (ColAndreasComponent::instance_->collisionWorld->objectManager->getBoundingSphere(modelid, Center, Radius))
		{
			cell* addr[4];
			amx_GetAddr(amx, params[2], &addr[0]);
			amx_GetAddr(amx, params[3], &addr[1]);
			amx_GetAddr(amx, params[4], &addr[2]);
			amx_GetAddr(amx, params[5], &addr[3]);

			*addr[0] = amx_ftoc(Center.getX());
			*addr[1] = amx_ftoc(Center.getY());
			*addr[2] = amx_ftoc(Center.getZ());
			*addr[3] = amx_ftoc(Radius);

			return 1;
		}
	}
	return 0;
}


cell AMX_NATIVE_CALL ColAndreasNatives::CA_GetModelBoundingBox(AMX *amx, cell* params)
{
	int32_t modelid = static_cast<int32_t>(params[1]);
	
	if ((modelid >= 0 && modelid < 20000) || (modelid <= -1000 && modelid > -30000))
	{
		btVector3 Min;
		btVector3 Max;

		if (ColAndreasComponent::instance_->collisionWorld->objectManager->getBoundingBox(modelid, Min, Max))
		{
			cell* addr[6];
			amx_GetAddr(amx, params[2], &addr[0]);
			amx_GetAddr(amx, params[3], &addr[1]);
			amx_GetAddr(amx, params[4], &addr[2]);
			amx_GetAddr(amx, params[5], &addr[3]);
			amx_GetAddr(amx, params[6], &addr[4]);
			amx_GetAddr(amx, params[7], &addr[5]);
			
			*addr[0] = amx_ftoc(Min.getX());
			*addr[1] = amx_ftoc(Min.getY());
			*addr[2] = amx_ftoc(Min.getZ());
			*addr[3] = amx_ftoc(Max.getX());
			*addr[4] = amx_ftoc(Max.getY());
			*addr[5] = amx_ftoc(Max.getZ());

			return 1;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL ColAndreasNatives::CA_SetObjectExtraID(AMX *amx, cell* params)
{
	uint16_t index = static_cast<uint16_t>(params[1]);
	ColAndreasComponent::instance_->collisionWorld->setMyExtraID(index, params[2], params[3]);
	return 1;
}

cell AMX_NATIVE_CALL ColAndreasNatives::CA_GetObjectExtraID(AMX *amx, cell* params)
{
	uint16_t index = static_cast<uint16_t>(params[1]);
	return ColAndreasComponent::instance_->collisionWorld->getMyExtraID(index, params[2]);
}


// CA_RayCastReflectionVector(Float:startx, Float:starty, Float:startz, Float:endx, Float:endy, Float:endz, &Float:vector);
cell AMX_NATIVE_CALL ColAndreasNatives::CA_RayCastReflectionVector(AMX *amx, cell* params)
{
	cell* addr[6];

	// Adding a small value prevents a potential crash if all values are the same
	btVector3 Start = btVector3(btScalar(amx_ctof(params[1]) + 0.00001), btScalar(amx_ctof(params[2]) + 0.00001), btScalar(amx_ctof(params[3]) + 0.00001));
	btVector3 End = btVector3(btScalar(amx_ctof(params[4])), btScalar(amx_ctof(params[5])), btScalar(amx_ctof(params[6])));
	btVector3 Result;
	btVector3 Position;
	int32_t model;

	if (ColAndreasComponent::instance_->collisionWorld->performRayTestReflection(Start, End, Position, Result, model))
	{
		amx_GetAddr(amx, params[7], &addr[0]);
		amx_GetAddr(amx, params[8], &addr[1]);
		amx_GetAddr(amx, params[9], &addr[2]);
		amx_GetAddr(amx, params[10], &addr[3]);
		amx_GetAddr(amx, params[11], &addr[4]);
		amx_GetAddr(amx, params[12], &addr[5]);

		// Return normal
		*addr[0] = amx_ftoc(Position.getX());
		*addr[1] = amx_ftoc(Position.getY());
		*addr[2] = amx_ftoc(Position.getZ());

		// Return collision vector
		*addr[3] = amx_ftoc(Result.getX());
		*addr[4] = amx_ftoc(Result.getY());
		*addr[5] = amx_ftoc(Result.getZ());

		return model;
	}
	return 0;
}



// CA_RayCastLineNormal(Float:startx, Float:starty, Float:startz, Float:endx, Float:endy, Float:endz, &Float:vector);
cell AMX_NATIVE_CALL ColAndreasNatives::CA_RayCastLineNormal(AMX *amx, cell* params)
{
	cell* addr[6];

	// Adding a small value prevents a potential crash if all values are the same
	btVector3 Start = btVector3(btScalar(amx_ctof(params[1]) + 0.00001), btScalar(amx_ctof(params[2]) + 0.00001), btScalar(amx_ctof(params[3]) + 0.00001));
	btVector3 End = btVector3(btScalar(amx_ctof(params[4])), btScalar(amx_ctof(params[5])), btScalar(amx_ctof(params[6])));
	btVector3 Result;
	btVector3 Position;
	int32_t model;

	if (ColAndreasComponent::instance_->collisionWorld->performRayTestNormal(Start, End, Position, Result, model))
	{
		amx_GetAddr(amx, params[7], &addr[0]);
		amx_GetAddr(amx, params[8], &addr[1]);
		amx_GetAddr(amx, params[9], &addr[2]);
		amx_GetAddr(amx, params[10], &addr[3]);
		amx_GetAddr(amx, params[11], &addr[4]);
		amx_GetAddr(amx, params[12], &addr[5]);

		// Return normal
		*addr[0] = amx_ftoc(Position.getX());
		*addr[1] = amx_ftoc(Position.getY());
		*addr[2] = amx_ftoc(Position.getZ());

		// Return collision vector
		*addr[3] = amx_ftoc(Result.getX());
		*addr[4] = amx_ftoc(Result.getY());
		*addr[5] = amx_ftoc(Result.getZ());

		return model;
	}
	return 0;
}

cell AMX_NATIVE_CALL ColAndreasNatives::CA_ContactTest(AMX *amx, cell* params)
{
	int32_t modelid = static_cast<int32_t>(params[1]);
	
	btVector3 position = btVector3(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
	btVector3 rotation = btVector3(amx_ctof(params[5]), amx_ctof(params[6]), amx_ctof(params[7]));
	
	btQuaternion quatrotation;
	ColAndreasComponent::instance_->collisionWorld->EulerToQuat(rotation, quatrotation);
	
	return ColAndreasComponent::instance_->collisionWorld->performContactTest(modelid, position, quatrotation);
}
