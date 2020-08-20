#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <thread>

#include "Ball.hpp"
#include "Brick.hpp"
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

  std::vector<Brick> bricks;
  srand(time(0));
  for (float x = 0;
       x < GlobalConstants::window_width - GlobalConstants::brick_width;
       x += GlobalConstants::brick_width + 2) {
    for (float y = 0; y < GlobalConstants::window_height * .60f;
         y += GlobalConstants::brick_height + 2) {
      if (rand() % 100 < 64) {
        bricks.push_back(Pos{x, y});
      }
    }
  }

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

    int active_bricks = 0;
    for (auto& brick : bricks) {
      if (!brick.IsDestroyed()) {
        auto const collision_kind = brick.BallHasCollided(ball);
        if (collision_kind == Brick::Collision::None) {
          ++active_bricks;
          window.draw(brick.DrawableObject());
        } else {
          brick.Destroy();
          auto const bounce_dir = collision_kind == Brick::Collision::Vertical
                                      ? Ball::Bounce::Vertical
                                      : Ball::Bounce::Horizontal;
          ball.Bounce(bounce_dir);
        }
      }
    }
    if (active_bricks == 0) break;

    window.draw(player.DrawableObject());
    window.draw(ball.DrawableObject());
    window.draw(portal1.DrawableObject());
    window.draw(portal2.DrawableObject());
    window.display();

    if (ball.BottomSide() >= GlobalConstants::window_height) break;
  }
}
