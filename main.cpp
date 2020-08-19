#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Ball.hpp"
#include "GlobalConstants.hpp"
#include "Player.hpp"
#include "Pos.hpp"

int main() {
  sf::RenderWindow window(
      {GlobalConstants::window_width, GlobalConstants::window_height},
      "Portal Brick Break");
  window.setFramerateLimit(GlobalConstants::frame_rate);

  Ball ball(
      {GlobalConstants::window_width / 2, GlobalConstants::window_height / 2});
  Player player({GlobalConstants::window_width / 2,
                 GlobalConstants::window_height * 0.95f});

  while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
    window.clear(sf::Color::White);

    player.Update();
    ball.Update();

    window.draw(player.DrawableObject());
    window.draw(ball.DrawableObject());
    window.display();
  }
}
