//*********************************************************************************************************//
// ColAndreas by [uL]Pottus & [uL]Chris42O & [uL]Slice ****************************************************//
//*********************************************************************************************************//
#include <Server/Components/Pawn/Impl/pawn_natives.hpp>
#include <Server/Components/Pawn/Impl/pawn_impl.hpp>
#include "ColAndreas.h"
#include "Natives.h"

AMX_NATIVE_INFO natives[] =
{
	{ "CA_Init", ColAndreasNatives::CA_Init },
	{ "CA_RayCastLine", ColAndreasNatives::CA_RayCastLine },
	{ "CA_RayCastLineExtraID", ColAndreasNatives::CA_RayCastLineExtraID },
	{ "CA_RayCastLineID", ColAndreasNatives::CA_RayCastLineID },
	{ "CA_RayCastLineAngle", ColAndreasNatives::CA_RayCastLineAngle },
	{ "CA_RayCastMultiLine", ColAndreasNatives::CA_RayCastMultiLine },
	{ "CA_RayCastReflectionVector", ColAndreasNatives::CA_RayCastReflectionVector },
	{ "CA_RayCastLineNormal", ColAndreasNatives::CA_RayCastLineNormal },
	{ "CA_ContactTest", ColAndreasNatives::CA_ContactTest },
	{ "CA_LoadFromDff", ColAndreasNatives::CA_LoadFromDff },
	{ "CA_CreateObject", ColAndreasNatives::CA_CreateObject },
	{ "CA_DestroyObject", ColAndreasNatives::CA_DestroyObject },
	{ "CA_IsValidObject", ColAndreasNatives::CA_IsValidObject },
	{ "CA_EulerToQuat", ColAndreasNatives::CA_EulerToQuat },
	{ "CA_QuatToEuler", ColAndreasNatives::CA_QuatToEuler },
	{ "CA_RemoveBuilding", ColAndreasNatives::CA_RemoveBuilding },
	{ "CA_RestoreBuilding", ColAndreasNatives::CA_RestoreBuilding },
	{ "CA_SetObjectPos", ColAndreasNatives::CA_SetObjectPos },
	{ "CA_SetObjectRot", ColAndreasNatives::CA_SetObjectRot },
	{ "CA_GetModelBoundingSphere", ColAndreasNatives::CA_GetModelBoundingSphere },
	{ "CA_GetModelBoundingBox", ColAndreasNatives::CA_GetModelBoundingBox },
	{ "CA_SetObjectExtraID", ColAndreasNatives::CA_SetObjectExtraID },
	{ "CA_GetObjectExtraID", ColAndreasNatives::CA_GetObjectExtraID },

	// Extended Natives
	{ "CA_RayCastLineEx", ColAndreasNatives::CA_RayCastLineEx },
	{ "CA_RayCastLineAngleEx", ColAndreasNatives::CA_RayCastLineAngleEx },
	{ 0, 0 }
};

StringView ColAndreasComponent::componentName() const
{
	return "ColAndreas";
}

SemanticVersion ColAndreasComponent::componentVersion() const
{
	return SemanticVersion(1, 5, 0, 0);
}

void ColAndreasComponent::onLoad(ICore* c)
{
	instance_ = this;
	core_ = c;
	setAmxLookups(core_);

	core_->printLn("*********************");
	core_->printLn("** Created By:     **");
	core_->printLn("** [uL]Chris42O    **");
	core_->printLn("** [uL]Slice       **");
	core_->printLn("** [uL]Pottus      **");
	core_->printLn("*********************");

	collisionWorld = new ColAndreasWorld();

	if (collisionWorld->loadCollisionData())
	{
		core_->printLn("Loaded collision data.");
		colDataLoaded = true;
	}
	else
	{
		core_->printLn("No collision data found.");
	}

	core_->printLn("*********************");
	core_->printLn("  ColAndreas Loaded");
	core_->printLn("   " CA_VERSION);
	core_->printLn("*********************");
}

void ColAndreasComponent::onInit(IComponentList* components)
{
	pawn_ = components->queryComponent<IPawnComponent>();

	if (pawn_)
	{
		setAmxLookups(components);
		setAmxFunctions(pawn_->getAmxFunctions());
		pawn_->getEventDispatcher().addEventHandler(this);
	}
}

void ColAndreasComponent::onReady()
{

}

void ColAndreasComponent::onFree(IComponent* component)
{
	if (component == pawn_)
	{
		pawn_ = nullptr;
		setAmxFunctions();
		setAmxLookups();

		core_->printLn("*********************");
		core_->printLn("*ColAndreas Unloaded*");
		core_->printLn("*********************");
	}
}

void ColAndreasComponent::free()
{
	delete this;
}

void ColAndreasComponent::reset()
{

}

void ColAndreasComponent::onAmxLoad(IPawnScript& script)
{
	pawn_natives::AmxLoad(script.GetAMX());
	amx_Register(script.GetAMX(), natives, -1);
}

void ColAndreasComponent::onAmxUnload(IPawnScript& script)
{
	
}

ColAndreasComponent::~ColAndreasComponent()
{
	if (pawn_)
	{
		pawn_->getEventDispatcher().removeEventHandler(this);
	}
}