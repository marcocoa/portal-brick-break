#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

auto constexpr window_width = 800;
auto constexpr window_height = 600;
auto constexpr frame_rate = 60;

class Ball {
 private:
  sf::CircleShape m_circle;
  sf::Vector2f m_velocity;

 public:
  Ball(float x, float y) {
    auto constexpr radius = 8.0f;
    auto constexpr speed_x = 10, speed_y = 10;

    m_circle.setPosition(x, y);
    m_circle.setRadius(radius);
    m_circle.setFillColor(sf::Color::Red);
    m_circle.setOrigin(radius, radius);
    m_velocity = sf::Vector2f(speed_x, speed_y);
  }

  void Move() { m_circle.move(m_velocity); }

  sf::CircleShape const& DrawableObject() { return m_circle; }
};

int main() {
  sf::RenderWindow window({window_width, window_height}, "Portal Brick Break");
  window.setFramerateLimit(frame_rate);

  Ball ball(window_width / 2, window_height / 2);

  while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
    window.clear(sf::Color::White);

    ball.Move();
    window.draw(ball.DrawableObject());

    window.display();
  }
}
