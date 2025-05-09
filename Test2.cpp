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

    Font font;
    if (!font.openFromFile("ARIAL.TTF")) return -1;

    const Vector2f fixedResolution({ 800.f,600.f });

    Texture texutre;
    if (!texutre.loadFromFile("img_texture.png")) return -1;

    RectangleShape square(Vector2f({ 50.f, 50.f }));
    square.setFillColor(Color::Black);
    square.setPosition({ 400.f,300.f });

    Sprite bgsprite(texutre);
  
    Vector2u textureSize = texutre.getSize();
    Vector2u windowSize = window.getSize();

    //button square
    RectangleShape button(Vector2f({ 200.f,60.f }));
    button.setFillColor(Color::Blue);
    button.setPosition({ 200.f, 100.f });

    Text btnText(font);
    btnText.setString("Click");
    btnText.setCharacterSize(24);
    btnText.setFillColor(Color::White);
    btnText.setPosition(
        Vector2f(
            button.getPosition().x + 40,
            button.getPosition().y + 15
        )
    );

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

            if (const auto* mouseButtonPressed = event->getIf<Event::MouseButtonPressed>()) {
                if (mouseButtonPressed->button == Mouse::Button::Left) {
                    Vector2f mousePos = window.mapPixelToCoords({ mouseButtonPressed->position.x, mouseButtonPressed->position.y });
                    if (button.getGlobalBounds().contains(mousePos)) {
                        cout << "Btn clicked";
                    }
                }
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
        window.draw(button);
        window.draw(btnText);
        window.display();
    }

    return 0;
}