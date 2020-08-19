#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Pos.hpp"

class Ball {
 private:
  sf::CircleShape m_circle;
  sf::Vector2f m_velocity;

 public:
  Ball(Pos pos) {
    auto constexpr radius = 8.0f;
    auto constexpr speed_x = 10, speed_y = 10;

    m_circle.setPosition(pos.x, pos.y);
    m_circle.setRadius(radius);
    m_circle.setFillColor(sf::Color::Red);
    m_circle.setOrigin(radius, radius);
    m_velocity = sf::Vector2f(speed_x, speed_y);
  }

  void Update() { m_circle.move(m_velocity); }
  float XCoord() { return m_circle.getPosition().x; }
  float YCoord() { return m_circle.getPosition().y; }
  float LeftSide() { return XCoord() - m_circle.getRadius(); }
  float RightSide() { return XCoord() + m_circle.getRadius(); }
  float TopSide() { return YCoord() - m_circle.getRadius(); }
  float BottomSide() { return YCoord() + m_circle.getRadius(); }
  sf::CircleShape const& DrawableObject() { return m_circle; }
};

