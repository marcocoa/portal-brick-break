#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <algorithm>
#include <thread>

#include "Ball.hpp"
#include "GlobalConstants.hpp"
#include "Player.hpp"
#include "Portal.hpp"
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

  // Idea for later: multiple portal pairs?
  Portal portal1({82, 20}, sf::Color::Cyan);
  Portal portal2({382, 144}, sf::Color::Black);
  portal1.SetExit(&portal2);
  portal2.SetExit(&portal1);

  ball.Freeze();
  while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
    window.clear(sf::Color::White);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
      ball.Unfreeze();
    }

    auto const mouse_pos = sf::Mouse::getPosition(window);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
      // Having to cast these to float is a bit annoying :I
      portal1.MoveTo(
          {static_cast<float>(mouse_pos.x), static_cast<float>(mouse_pos.y)});
    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
      portal2.MoveTo(
          {static_cast<float>(mouse_pos.x), static_cast<float>(mouse_pos.y)});
    }

    if (portal1.BallHasEntered(ball)) {
      portal1.TeleportBall(ball);
    } else if (portal2.BallHasEntered(ball)) {
      portal2.TeleportBall(ball);
    }

    if (player.BallHasCollided(ball)) {
      ball.Bounce(Ball::Bounce::Vertical);
    }

    player.Update();
    ball.Update();

    window.draw(player.DrawableObject());
    window.draw(ball.DrawableObject());
    window.draw(portal1.DrawableObject());
    window.draw(portal2.DrawableObject());
    window.display();

    if (ball.BottomSide() >= GlobalConstants::window_height) break;
  }
}
