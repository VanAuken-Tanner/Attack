#pragma once

#include "Scene.h"


class Scene_Clear : public Scene
{
public:
    Scene_Clear();
    ~Scene_Clear();

    void OnUpdate(float deltaTine) override;
    void OnRender() override;
    void OnImGuiRender() override;
private:
    float m_clearColor[4];
};
