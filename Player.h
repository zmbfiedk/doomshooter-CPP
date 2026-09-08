
#pragma once

#include "InputSystem.h"

class Player
{
public:
    Player();

    void Update(const InputSystem& input);

    void MoveForward();
    void MoveBackward();
    void MoveLeft();
    void MoveRight();

    void RotateLeft();
    void RotateRight();

    void Shoot();

    float GetX() const;
    float GetY() const;
    float GetRotation() const;

private:
    float m_x;
    float m_y;
    float m_rotation;

    float m_moveSpeed;
    float m_rotationSpeed;
};

