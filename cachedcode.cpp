
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {

    // Game g("config.txt");
    // g.run();

    int i = 6;
    int *p;
    p = &i;
    *p = 7;

    unsigned int wWidth = 640;
    unsigned int wHeight = 480;
    std::string wWindowName = "Galaxy Shooter";

    sf::RenderWindow window(sf::VideoMode({wWidth, wHeight}), wWindowName);

    float posX = 100.f;
    float posY = 100.f;

    float speedX = 0.1f;
    float speedY = 0.1f;

    sf::CircleShape circle;

    circle.setRadius(40.f);
    circle.setPosition({posX, posY});
    circle.setFillColor(sf::Color::Red);

    sf::Font myFont;

    if (!myFont.openFromFile("/Library/Fonts/Arial Unicode.ttf")) {
        std::cerr << "Could not load font!\n";
        exit(-1);
    }

    sf::Text text(myFont, "Ball", 24);

    text.setPosition({0, wHeight - (float)text.getCharacterSize()});

    std::vector<sf::RectangleShape> rectangles;

    for (int x = 0; x < 25; x++) {
        for (int y = 0; y < 15; y++) {

            sf::RectangleShape rectangle;
            rectangle.setSize(sf::Vector2f(15, 15));
            rectangle.setPosition({x * 20.f, y * 20.f});
            rectangle.setFillColor(sf::Color(x * 10, y * 10, 0));
            rectangles.push_back(rectangle);
        }
    }

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        posX = circle.getPosition().x;
        posY = circle.getPosition().y;

        if (posX + 80.f >= wWidth || posX <= 0) {
            speedX *= -1;
        }

        if (posY + 80.f >= wHeight || posY <= 0) {
            speedY *= -1;
        }

        circle.setPosition({posX + speedX, posY + speedY});

        window.clear();

        for (auto &rect : rectangles) {
            window.draw(rect);
        }

        window.draw(circle);
        window.draw(text);
        window.display();
    }

    return 0;
}
