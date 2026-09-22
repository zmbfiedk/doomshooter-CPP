
#pragma once

#include "InputSystem.h"
#include "Map.h"

class Player 
{
public:
    explicit Player(const Map& map);

    void Update(const InputSystem& input, float deltaTime);

    void MoveForward();
    void MoveBackward();
    void MoveLeft();
    void MoveRight();

    void RotateLeft();
    void RotateRight();

    float GetX() const;
    float GetY() const;
    float GetRotation() const;

private:
    float m_x;
    float m_y;
    float m_rotation;

    float m_moveSpeed;
    float m_rotationSpeed;
    float m_radius;

    const Map& m_map;

    void TryMove(float deltaX, float deltaY);
};

