#include "InputSystem.h"

#include <conio.h>

void InputSystem::Update()
{
    m_currentAction = InputAction::None;

    if (!_kbhit())
    {
        return;
    }

    const char key = _getch();

    switch (key)
    {
    case 'w':
    case 'W':
        m_currentAction = InputAction::MoveForward;
        break;

    case 's':
    case 'S':
        m_currentAction = InputAction::MoveBackward;
        break;

    case 'a':
    case 'A':
        m_currentAction = InputAction::MoveLeft;
        break;

    case 'd':
    case 'D':
        m_currentAction = InputAction::MoveRight;
        break;

    case ' ':
        m_currentAction = InputAction::Shoot;
        break;

    case 27:
        m_currentAction = InputAction::Quit;
        break;

    default:
        break;
    }
}

bool InputSystem::IsPressed(InputAction action) const
{
    return m_currentAction == action;
}