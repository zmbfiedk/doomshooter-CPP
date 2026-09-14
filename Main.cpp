#include <iostream>

#include "InputSystem.h"
#include "Player.h"

int main()
{
    InputSystem input;
    Player player;

    bool running = true;

    bool debugInput = true;
    bool debugPlayer = true;

    while (running)
    {
        input.Update();

        if (debugInput)
        {
            if (input.IsPressed(InputAction::MoveForward))
                std::cout << "[INPUT] Forward\n";

            if (input.IsPressed(InputAction::MoveBackward))
                std::cout << "[INPUT] Backward\n";

            if (input.IsPressed(InputAction::MoveLeft))
                std::cout << "[INPUT] Left\n";

            if (input.IsPressed(InputAction::MoveRight))
                std::cout << "[INPUT] Right\n";

            if (input.IsPressed(InputAction::RotateLeft))
                std::cout << "[INPUT] Rotate left\n";

            if (input.IsPressed(InputAction::RotateRight))
                std::cout << "[INPUT] Rotate right\n";

            if (input.IsPressed(InputAction::Shoot))
                std::cout << "[INPUT] Shoot\n";
        }

        if (input.IsPressed(InputAction::Quit))
        {
            running = false;
        }

        player.Update(input);

        if (debugPlayer)
        {
            std::cout << "[PLAYER] X: "
                << player.GetX()
                << " Y: "
                << player.GetY()
                << " Rotation: "
                << player.GetRotation()
                << '\n';
        }
    }

    return 0;
}