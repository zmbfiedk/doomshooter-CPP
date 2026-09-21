#include "InputSystem.h"

#include <SFML/Window/Keyboard.hpp>

void InputSystem::Update()
{
    m_actions.reset();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        m_actions.set(static_cast<size_t>(InputAction::MoveForward));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        m_actions.set(static_cast<size_t>(InputAction::MoveBackward));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        m_actions.set(static_cast<size_t>(InputAction::MoveLeft));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        m_actions.set(static_cast<size_t>(InputAction::MoveRight));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        m_actions.set(static_cast<size_t>(InputAction::RotateLeft));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        m_actions.set(static_cast<size_t>(InputAction::RotateRight));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        m_actions.set(static_cast<size_t>(InputAction::Shoot));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        m_actions.set(static_cast<size_t>(InputAction::Quit));
}

bool InputSystem::IsPressed(InputAction action) const
{
    return m_actions.test(static_cast<size_t>(action));
}