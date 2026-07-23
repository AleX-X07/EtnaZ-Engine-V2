#pragma once
#include "../Component.h"

class TestComponent final : public Component {
public:
    TestComponent(Object* _owner);
    virtual ~TestComponent() override = default;
};
