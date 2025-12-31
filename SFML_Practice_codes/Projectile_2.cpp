#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

int main() {
    // 1. Explicitly define VideoMode
    RenderWindow window(VideoMode(Vector2u(1920, 1080)), "Projectile");
    window.setFramerateLimit(144);

    float groundY = (2.f * 1080.0f) / 3.0f;
    
    // 2. Explicitly use Vector2f instead of {}
    RectangleShape ground(Vector2f(1920.0f, 1080.0f / 3.0f));
    ground.setPosition(Vector2f(0.f, groundY));
    ground.setFillColor(Color::Green);

    float radius = 30.f;
    CircleShape ball(radius, 60);
    ball.setOrigin(Vector2f(radius, radius));
    ball.setPosition(Vector2f(radius, groundY - radius));
    ball.setFillColor(Color::Red);

    Vector2f vel(15.0f, -20.0f); 
    float gravity = 0.5f;

    while (window.isOpen()) {
        // SFML 3 Event Loop
        while (std::optional event = window.pollEvent()) {
            if (event->is<Event::Closed>()) {
                window.close();
            }
        }

        vel.y += gravity;
        ball.move(vel);

        Vector2f ballPos = ball.getPosition();

        // Floor Collision
        if (ballPos.y > groundY - radius) {
            vel.y = -vel.y * 0.8f; 
            vel.x *= 0.99f;
            ball.setPosition(Vector2f(ballPos.x, groundY - radius));
        }

        // Wall Collision
        if (ballPos.x > 1920 - radius || ballPos.x < radius) {
            vel.x = -vel.x;
            if (ballPos.x < radius) ball.setPosition(Vector2f(radius, ballPos.y));
            else ball.setPosition(Vector2f(1920 - radius, ballPos.y));
        }

        window.clear(Color::Black);
        window.draw(ground);
        window.draw(ball);
        window.display();
    }
}