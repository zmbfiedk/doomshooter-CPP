#include "Player.h"

Player::Player()
    : m_x(2.0f),
    m_y(2.0f),
    m_rotation(0.0f),
    m_moveSpeed(0.1f),
    m_rotationSpeed(0.1f)
{
}

void Player::Update(const InputSystem& input)
{
    if (input.IsPressed(InputAction::MoveForward))
        MoveForward();

    if (input.IsPressed(InputAction::MoveBackward))
        MoveBackward();

    if (input.IsPressed(InputAction::MoveLeft))
        MoveLeft();

    if (input.IsPressed(InputAction::MoveRight))
        MoveRight();

    if (input.IsPressed(InputAction::Shoot))
        Shoot();
}

void Player::MoveForward()
{
    m_y += m_moveSpeed;
}

void Player::MoveBackward()
{
    m_y -= m_moveSpeed;
}

void Player::MoveLeft()
{
    m_x -= m_moveSpeed;
}

void Player::MoveRight()
{
    m_x += m_moveSpeed;
}

void Player::RotateLeft()
{
    m_rotation -= m_rotationSpeed;
}

void Player::RotateRight()
{
    m_rotation += m_rotationSpeed;
}

void Player::Shoot()
{
}

float Player::GetX() const
{
    return m_x;
}

float Player::GetY() const
{
    return m_y;
}

float Player::GetRotation() const
{
    return m_rotation;
}