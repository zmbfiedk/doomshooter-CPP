#include "Player.h"

#include <cmath>

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
    const float forward = static_cast<float>(
        input.IsPressed(InputAction::MoveForward) - input.IsPressed(InputAction::MoveBackward));
    const float strafe = static_cast<float>(
        input.IsPressed(InputAction::MoveRight) - input.IsPressed(InputAction::MoveLeft));

    const float movementLength = std::sqrt(forward * forward + strafe * strafe);
    if (movementLength > 0.0f)
    {
        const float normalizedForward = forward / movementLength;
        const float normalizedStrafe = strafe / movementLength;
        const float sinRotation = std::sin(m_rotation);
        const float cosRotation = std::cos(m_rotation);

        m_x += (sinRotation * normalizedForward + cosRotation * normalizedStrafe) * m_moveSpeed;
        m_y += (cosRotation * normalizedForward - sinRotation * normalizedStrafe) * m_moveSpeed;
    }

    if (input.IsPressed(InputAction::RotateLeft))
        RotateLeft();

    if (input.IsPressed(InputAction::RotateRight))
        RotateRight();

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