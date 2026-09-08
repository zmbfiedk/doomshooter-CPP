#pragma once

#include "InputAction.h"

class InputSystem
{
public:
    void Update();

    bool IsPressed(InputAction action) const;

private:
    InputAction m_currentAction = InputAction::None;
};