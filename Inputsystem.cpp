#include "InputSystem.h"

#include <conio.h>

void InputSystem::Update()
{
    m_actions.reset();

    while (_kbhit())
    {
        const int key = _getch();

        if (key == 0 || key == 224)
        {
            if (!_kbhit())
                continue;

            switch (_getch())
            {
            case 75:
                m_actions.set(static_cast<size_t>(InputAction::RotateLeft));
                break;

            case 77:
                m_actions.set(static_cast<size_t>(InputAction::RotateRight));
                break;

            default:
                break;
            }

            continue;
        }

        switch (key)
        {
        case 'w':
        case 'W':
            m_actions.set(static_cast<size_t>(InputAction::MoveForward));
            break;

        case 's':
        case 'S':
            m_actions.set(static_cast<size_t>(InputAction::MoveBackward));
            break;

        case 'a':
        case 'A':
            m_actions.set(static_cast<size_t>(InputAction::MoveLeft));
            break;

        case 'd':
        case 'D':
            m_actions.set(static_cast<size_t>(InputAction::MoveRight));
            break;

        case ' ':
            m_actions.set(static_cast<size_t>(InputAction::Shoot));
            break;

        case 27:
            m_actions.set(static_cast<size_t>(InputAction::Quit));
            break;

        default:
            break;
        }
    }
}

bool InputSystem::IsPressed(InputAction action) const
{
    return m_actions.test(static_cast<size_t>(action));
}