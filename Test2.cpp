#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode({ 800, 600 }), "The game", Style::Default, State::Windowed);
    window.setPosition({ 10, 50 });
	window.setFramerateLimit(60);

    CircleShape circle(65.f);
	circle.setFillColor(Color::White);
    circle.setPosition({ window.getSize().x / 2 - circle.getRadius(), window.getSize().y / 2 - circle.getRadius() });

    while (window.isOpen())
    {
        while (const optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();
        }

		Vector2 movement = { 0.f, 0.f };

        if (Keyboard::isKeyPressed(Keyboard::Key::A) && circle.getPosition().x > 1.f) {
            movement.x += -3.f;
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::D) && circle.getPosition().x < 669.f) {
            movement.x += 3.f;
        }

        if (Keyboard::isKeyPressed(Keyboard::Key::W) && circle.getPosition().y > 1.f) {
            movement.y += -3.f;
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::S) && circle.getPosition().y < 469.f) {
            movement.y += 3.f;
        }

        circle.move(movement);

        window.clear(Color::Black);
		window.draw(circle);
        cout << circle.getPosition().x << " - " << circle.getPosition().y << endl;
        window.display();
    }

    return 0;
}