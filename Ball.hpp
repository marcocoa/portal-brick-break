#pragma once

#include <SFML/Graphics.hpp>

#include "GlobalConstants.hpp"
#include "Pos.hpp"

class Ball {
 private:
  sf::CircleShape m_circle;
  sf::Vector2f m_velocity;
  bool m_freeze = false;

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

  enum class Bounce { Vertical, Horizontal };
  void Bounce(Bounce bounce_dir) {
    switch (bounce_dir) {
      case Bounce::Vertical:
        m_velocity.y *= -1;
        break;
      case Bounce::Horizontal:
        m_velocity.x *= -1;
        break;
      default:
        break;
    }
  }

  void Update() {
    if (m_freeze) return;

    m_circle.move(m_velocity);
    if (LeftSide() < 0 || RightSide() > GlobalConstants::window_width) {
      Bounce(Bounce::Horizontal);
    }
    if (TopSide() < 0 || BottomSide() > GlobalConstants::window_height) {
      Bounce(Bounce::Vertical);
    }
  }

  float XCoord() const { return m_circle.getPosition().x; }
  float YCoord() const { return m_circle.getPosition().y; }
  float LeftSide() const { return XCoord() - m_circle.getRadius(); }
  float RightSide() const { return XCoord() + m_circle.getRadius(); }
  float TopSide() const { return YCoord() - m_circle.getRadius(); }
  float BottomSide() const { return YCoord() + m_circle.getRadius(); }
  void MoveTo(Pos p) { m_circle.setPosition({p.x, p.y}); }
  void Freeze() { m_freeze = true; }
  void Unfreeze() { m_freeze = false; }

  sf::CircleShape const& DrawableObject() { return m_circle; }
};

