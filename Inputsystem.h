#pragma once

#include <bitset>

#include "InputAction.h"

class InputSystem
{
public:
    void Update();

    bool IsPressed(InputAction action) const;

private:
    std::bitset<static_cast<size_t>(InputAction::Count)> m_actions;
};