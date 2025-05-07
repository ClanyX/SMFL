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

    const Vector2f fixedResolution({ 800.f,600.f });

    Texture texutre;
    if (!texutre.loadFromFile("img_texture.png")) return -1;

    RectangleShape square(Vector2f({ 50.f, 50.f }));
    square.setFillColor(Color::Black);
    square.setPosition({ 400.f,300.f });

    Sprite bgsprite(texutre);

    Vector2u textureSize = texutre.getSize();
    Vector2u windowSize = window.getSize();

    while (window.isOpen())
    {
        while (const optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();
            else if (event->is<Event::Resized>()) {
                View view(FloatRect({ 0.f, 0.f }, { fixedResolution.x, fixedResolution.y }));
                window.setView(view);
                

                Vector2u textureSize = texutre.getSize();
                Vector2u windowSize = window.getSize();

                bgsprite.setScale(
                    Vector2f(
                        fixedResolution.x / textureSize.x,
                        fixedResolution.y / textureSize.y
                    )
                );
            }
        }

		Vector2 movement = { 0.f, 0.f };

        if (Keyboard::isKeyPressed(Keyboard::Key::A) && square.getPosition().x > 1.f) {
            movement.x += -3.f;
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::D) && square.getPosition().x < (window.getView().getSize().x - 50)) {
            movement.x += 3.f;
        }

        if (Keyboard::isKeyPressed(Keyboard::Key::W) && square.getPosition().y > 1.f) {
            movement.y += -3.f;
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::S) && square.getPosition().y < (window.getView().getSize().y - 50)) {
            movement.y += 3.f;
        }

        square.move(movement);

        window.clear(Color::White);
        window.draw(bgsprite);
		window.draw(square);
        window.display();
    }

    return 0;
}