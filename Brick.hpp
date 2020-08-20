#include <SFML/Graphics.hpp>

#include "Ball.hpp"
#include "GlobalConstants.hpp"
#include "Pos.hpp"

class Brick {
 private:
  sf::RectangleShape m_rect;
  bool m_destroyed = false;

  float XCoord() const { return m_rect.getPosition().x; }
  float YCoord() const { return m_rect.getPosition().y; }
  float LeftSide() const { return XCoord() - m_rect.getSize().x; }
  float RightSide() const { return XCoord() + m_rect.getSize().x; }
  float TopSide() const { return YCoord() - m_rect.getSize().y; }
  float BottomSide() const { return YCoord() + m_rect.getSize().y; }

 public:
  enum class Collision { None, Vertical, Horizontal };

  Brick(Pos p) {
    m_rect.setPosition(p.x, p.y);
    m_rect.setSize(
        {GlobalConstants::brick_width, GlobalConstants::brick_height});
    m_rect.setFillColor(sf::Color::Yellow);
    m_rect.setOrigin(GlobalConstants::brick_width / 2.0f,
                     GlobalConstants::brick_height / 2.0f);
  }

  Collision BallHasCollided(Ball const& ball) const {
    bool const has_collided_vertically =
        ((ball.TopSide() <= BottomSide() &&
          ball.BottomSide() >= BottomSide()) ||
         (ball.BottomSide() >= TopSide() && ball.TopSide() <= TopSide())) &&
        ball.LeftSide() >= LeftSide() && ball.RightSide() <= RightSide();

    // TODO: bounce horizontally, lol
    bool const has_collided_horizontally = false;

    if (has_collided_vertically)
      return Collision::Vertical;
    else if (has_collided_horizontally)
      return Collision::Horizontal;
    else
      return Collision::None;
  }

  void Destroy() { m_destroyed = true; }
  bool IsDestroyed() { return m_destroyed; }

  sf::RectangleShape const& DrawableObject() const { return m_rect; }
};
