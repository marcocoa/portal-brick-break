#pragma once

#include <SFML/Graphics.hpp>

#include "GlobalConstants.hpp"
#include "Pos.hpp"

class Player {
 private:
  sf::RectangleShape m_rect;
  sf::Vector2f m_velocity;

  float XCoord() const { return m_rect.getPosition().x; }
  float YCoord() const { return m_rect.getPosition().y; }
  float LeftSide() const { return XCoord() - m_rect.getSize().x; }
  float RightSide() const { return XCoord() + m_rect.getSize().x; }
  float TopSide() const { return YCoord() - m_rect.getSize().y; }
  float BottomSide() const { return YCoord() + m_rect.getSize().y; }

 public:
  Player(Pos p) {
    auto constexpr width = 80.0f;
    auto constexpr height = 5.0f;

    m_rect.setPosition(p.x, p.y);
    m_rect.setSize({width, height});
    m_rect.setFillColor(sf::Color::Blue);
    m_rect.setOrigin(width / 2.0f, height / 2.0f);
  }

  void Update() {
    auto constexpr speed_x = 15.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && LeftSide() > 0) {
      m_velocity.x = -speed_x;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
               RightSide() < GlobalConstants::window_width) {
      m_velocity.x = speed_x;
    } else {
      m_velocity.x = 0;
    }
    m_rect.move(m_velocity);
  }

  sf::RectangleShape const& DrawableObject() const { return m_rect; }
};
