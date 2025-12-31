#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
using namespace sf;

class ball {
    CircleShape Ball;
    Vector2f vel;
public:
    ball(float rad, Vector2f vel, float posx, float posy) {
        Ball.setRadius(rad);
        Ball.setPointCount(60.0f);
        Ball.setOrigin({rad, rad});
        this->vel = vel;
        Ball.setPosition({posx, posy});
        Ball.setFillColor(Color::Yellow);
    }

    CircleShape& Get_ball() { return Ball; }
    Vector2f Get_velocity() { return vel; }
    void Set_velo(Vector2f newVel) { this->vel = newVel; }

    void stayInside(float up, float down, float right, float left) {
        Vector2f pos = Ball.getPosition();
        float r = Ball.getRadius();
        Vector2f normal(0, 0);
        bool hit = false;

        if (pos.x >= right - r) {
            Ball.setPosition({right - r, pos.y});
            normal += {-1.0f, 0.0f};
            hit = true;
        } else if (pos.x <= left + r) {
            Ball.setPosition({left + r, pos.y});
            normal += {1.0f, 0.0f};
            hit = true;
        }

        if (pos.y <= up + r) {
            Ball.setPosition({pos.x, up + r});
            normal += {0.0f, 1.0f};
            hit = true;
        } else if (pos.y >= down - r) {
            Ball.setPosition({pos.x, down - r});
            normal += {0.0f, -1.0f};
            hit = true;
        }

        if (!hit) return;

        float length = std::hypot(normal.x, normal.y);
        normal /= length;

        float dot = (vel.x * normal.x + vel.y * normal.y);
        vel = vel - (2.0f * dot * normal);
        vel *= 0.98f;
    }

    friend void BallCollison(ball& b1, ball& b2, Vector2f center);
    friend bool DoesBallCollisonHappen(ball& b1, ball& b2, Vector2f center);
};

void BallCollison(ball& b1, ball& b2, Vector2f center) {
    Vector2f ball1_pos_wrt_center = b1.Get_ball().getPosition() - center;
    Vector2f ball2_pos_wrt_center = b2.Get_ball().getPosition() - center;
    Vector2f distanceVector = ball1_pos_wrt_center - ball2_pos_wrt_center;

    float dist = sqrt(pow(distanceVector.x, 2) + pow(distanceVector.y, 2));

    if (dist <= b1.Get_ball().getRadius() + b2.Get_ball().getRadius()) {
        Vector2f normal = distanceVector / dist;
        float overlap = b1.Get_ball().getRadius() + b2.Get_ball().getRadius() - dist;
        b1.Get_ball().move(-normal * overlap * 0.5f);
        b2.Get_ball().move(normal * overlap * 0.5f);

        Vector2f relVelocity = b1.Get_velocity() - b2.Get_velocity();
        float dot = (normal.x * relVelocity.x) + (normal.y * relVelocity.y);
        Vector2f pulse = dot * normal;

        if (dot < 0) {
            b1.Get_ball().setFillColor(Color::Red);
            b2.Get_ball().setFillColor(Color::Cyan);
            b1.Set_velo((b1.Get_velocity() - pulse) * 0.95f);
            b2.Set_velo((b2.Get_velocity() + pulse) * 0.95f);
        }
    }
}

bool DoesBallCollisonHappen(ball& b1, ball& b2, Vector2f center) {
    Vector2f ball1_pos_wrt_center = b1.Get_ball().getPosition() - center;
    Vector2f ball2_pos_wrt_center = b2.Get_ball().getPosition() - center;
    Vector2f distanceVector = ball1_pos_wrt_center - ball2_pos_wrt_center;

    float dist = sqrt(pow(distanceVector.x, 2) + pow(distanceVector.y, 2));

    if (dist <= b1.Get_ball().getRadius() + b2.Get_ball().getRadius()) {
        Vector2f normal = distanceVector / dist;
        Vector2f relVelocity = b1.Get_velocity() - b2.Get_velocity();
        float dot = (normal.x * relVelocity.x) + (normal.y * relVelocity.y);
        if (dot < 0) return true;
    }
    return false;
}

int main() {
    RenderWindow window(VideoMode({1920, 1080}), "Challenge 1");
    window.setFramerateLimit(144);

    bool pauseSignal = false;
    float pauseDuration = 6.0f, pauseTimer = 0, deltaTime = 0.01f;
    float timeElapsed = 0, timekeeper = 0;

    Font font;
    if (!font.openFromFile("arial.ttf")) {
        std::cout << "Error: Could not open font file!" << std::endl;
        return -1;
    }

    Text foundText(font);
    foundText.setString("GHOST BALL FOUND!");
    foundText.setCharacterSize(50);
    foundText.setFillColor(Color::Green);
    foundText.setStyle(Text::Bold);

    FloatRect textRect = foundText.getLocalBounds();
    foundText.setOrigin({textRect.position.x + textRect.size.x / 2.0f, textRect.position.y + textRect.size.y / 2.0f});
    foundText.setPosition({960.0f, 540.0f});

    RectangleShape box({1000, 1000});
    box.setFillColor(Color::Black);
    box.setOutlineThickness(10);
    box.setOutlineColor(Color::White);
    box.setOrigin({500, 500});
    box.setPosition({960, 540});

    float upperwall = 540 - 500 + 10, lowerwall = 540 + 500 - 10;
    float rightwall = 960 + 500 - 10, leftwall = 960 - 500 + 10;

    ball B1(20, {10.f, -10.f}, 960, 540);
    ball B2(20, {10.0f, -10.0f}, 900, 500);
    ball B3(20, {10.0f, -10.0f}, 850, 400);

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<Event::Closed>()) window.close();
        }

        if (pauseSignal) {
            pauseTimer += deltaTime;
            if (pauseTimer >= pauseDuration) {
                pauseSignal = false;
                pauseTimer = 0.0f;
            }
        } else {
            timeElapsed += deltaTime;
            Vector2f v = B1.Get_velocity(), v2 = B2.Get_velocity(), v3 = B3.Get_velocity();
            
            v.y += (9.81f * deltaTime);
            v2.y += (9.81f * deltaTime);
            v3.y += (9.81f * deltaTime);
            B1.Set_velo(v); B2.Set_velo(v2); B3.Set_velo(v3);

            B1.stayInside(upperwall, lowerwall, rightwall, leftwall);
            B2.stayInside(upperwall, lowerwall, rightwall, leftwall);
            B3.stayInside(upperwall, lowerwall, rightwall, leftwall);

            if (DoesBallCollisonHappen(B1, B2, box.getPosition())) {
                timekeeper = timeElapsed;
                pauseSignal = true;
            }
            BallCollison(B1, B2, box.getPosition());
            

            if (timeElapsed - timekeeper >= 5.0f) {
                B1.Get_ball().setFillColor(Color::Yellow);
                B2.Get_ball().setFillColor(Color::Yellow);
                B3.Get_ball().setFillColor(Color::Yellow);
                timekeeper = timeElapsed;
            }

            B1.Get_ball().move(B1.Get_velocity());
            B2.Get_ball().move(B2.Get_velocity());
            B3.Get_ball().move(B3.Get_velocity());
        }

        window.clear(Color::Black);
        window.draw(box);
        window.draw(B1.Get_ball());
        window.draw(B2.Get_ball());
        window.draw(B3.Get_ball());
        if (pauseSignal) window.draw(foundText);
        window.display();
    }
    return 0;
}