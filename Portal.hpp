#include <SFML/Graphics.hpp>

#include "Ball.hpp"
#include "Pos.hpp"

class Portal {
 private:
  sf::CircleShape m_circle;
  Portal* m_exit;

 public:
  Portal(Pos p, sf::Color color, Portal* exit = nullptr) {
    auto constexpr radius = 4.0f;

    m_circle.setPosition(p.x, p.y);
    m_circle.setRadius(radius);
    m_circle.setFillColor(color);
    m_circle.setOrigin(radius, radius);

    m_exit = exit;
  }

  float XCoord() const { return m_circle.getPosition().x; }
  float YCoord() const { return m_circle.getPosition().y; }
  float LeftSide() const { return XCoord() - m_circle.getRadius(); }
  float RightSide() const { return XCoord() + m_circle.getRadius(); }
  float TopSide() const { return YCoord() - m_circle.getRadius(); }
  float BottomSide() const { return YCoord() + m_circle.getRadius(); }

  bool BallHasEntered(Ball const& ball) const {
    return TopSide() >= ball.TopSide() && BottomSide() <= ball.BottomSide() &&
           LeftSide() >= ball.LeftSide() && RightSide() <= ball.RightSide();
  }

  void TeleportBall(Ball& ball) const {
    if (m_exit) {
      ball.MoveTo({m_exit->XCoord(), m_exit->YCoord()});
    }
  }

  void MoveTo(Pos p) { m_circle.setPosition(p.x, p.y); }
  void SetExit(Portal* exit) { m_exit = exit; }

  sf::CircleShape const& DrawableObject() const { return m_circle; }
};
