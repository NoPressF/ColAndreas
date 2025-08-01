#pragma once

#include <sdk.hpp>
#include "SDK/amx/amx.h"
#include "SDK/plugincommon.h"
#include <Server/Components/Pawn/pawn.hpp>
#include "DynamicWorld.h"

class ColAndreasWorld;

class ColAndreasComponent final : public IComponent, public PawnEventHandler
{
public:
    PROVIDE_UID(0xA88D09ECC0F8B9A5);

    ICore* core_;
    IPawnComponent* pawn_;
    inline static ColAndreasComponent* instance_ = nullptr;

    StringView componentName() const override;
    SemanticVersion componentVersion() const override;
    void onLoad(ICore* c) override;
    void onInit(IComponentList* components) override;
    void onReady() override;
    void onAmxLoad(IPawnScript& script) override;
    void onAmxUnload(IPawnScript& script) override;
    void onFree(IComponent* component) override;
    void reset() override;
    void free() override;

    bool colInit = false;
    bool colDataLoaded = false;
    ColAndreasWorld* collisionWorld;

    ~ColAndreasComponent();
};
