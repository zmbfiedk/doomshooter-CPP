#include "Player.h"

#include <cmath>

Player::Player(const Map& map)
    : m_x(map.GetPlayerStartX()),
    m_y(map.GetPlayerStartY()),
    m_rotation(0.0f),
    m_moveSpeed(0.1f),
    m_rotationSpeed(0.1f),
    m_radius(0.2f),
    m_map(map)
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

        const float movementX =
            (sinRotation * normalizedForward + cosRotation * normalizedStrafe) * m_moveSpeed;
        const float movementY =
            (cosRotation * normalizedForward - sinRotation * normalizedStrafe) * m_moveSpeed;

        TryMove(movementX, 0.0f);
        TryMove(0.0f, movementY);
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
    TryMove(0.0f, m_moveSpeed);
}

void Player::MoveBackward()
{
    TryMove(0.0f, -m_moveSpeed);
}

void Player::MoveLeft()
{
    TryMove(-m_moveSpeed, 0.0f);
}

void Player::MoveRight()
{
    TryMove(m_moveSpeed, 0.0f);
}

void Player::TryMove(float deltaX, float deltaY)
{
    const float newX = m_x + deltaX;
    const float newY = m_y + deltaY;

    if (m_map.CanOccupy(newX, newY, m_radius))
    {
        m_x = newX;
        m_y = newY;
    }
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