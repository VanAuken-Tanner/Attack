#pragma once

#include "Scene.h"

//class for testing scenes only
class Scene_Test : public Scene
{
public:
    Scene_Test();
    ~Scene_Test();

    void OnUpdate(float deltaTine) override;
    void OnRender() override;
    void OnImGuiRender() override;
private:
    
};