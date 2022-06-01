#include <SFML/Graphics.hpp>
#include<random>
#include<sstream>
#include"Cars.h"


int getPos(int line) {
		switch (line) {
		case 0:
				return 20;
		case 1:
				return 180;
		case 2:
				return 340;
		case 3:
				return 500;
		}
}

int main()
{
		sf::RenderWindow window(sf::VideoMode(600, 900), "Traffic race");
		window.setFramerateLimit(60);

		sf::Texture backTexture;
		backTexture.loadFromFile("back.jpg");
		sf::Sprite backSprite;
		backSprite.setTexture(backTexture);
		backSprite.scale(1, 1.5);
		backSprite.setPosition(0, 0);

		sf::Texture myCarTexture;
		myCarTexture.loadFromFile("krisha.png");
		sf::Sprite myCarSprite;
		myCarSprite.setTexture(myCarTexture);
		myCarSprite.scale(0.23, 0.22);
		myCarSprite.setPosition(500, 720);

		sf::Texture carTexture;
		carTexture.loadFromFile("car.png");

		sf::Font font;
		font.loadFromFile("Beyond Mars.ttf");
		sf::Text text("", font, 40);
		text.setPosition(20, 20);
		text.setFillColor(sf::Color::White);
		text.setOutlineThickness(2);
		text.setOutlineColor(sf::Color::Black);

		sf::Event event;

		float timer = 0;
		float moveTimer = 0;
		sf::Clock clock;
		int newCar = 0;
		int curLine = 3;
		int score = 0;
		bool isOver = false;
		Cars cars;
		while (window.isOpen())
		{

				float time = clock.getElapsedTime().asMicroseconds();
				clock.restart();
				time = time / 1000;
				moveTimer += time;
				timer += time;
				if (!isOver) {
						if (moveTimer > 10) {
								cars.move(score);
								moveTimer = 0;
						}

						if (timer > newCar) {
								cars.generate();
								std::random_device dev;
								std::mt19937 rng(dev());
								std::uniform_int_distribution<std::mt19937::result_type> dist(2000, 3000);
								newCar = dist(rng);
								timer = 0;
						}
				}
				if (cars.getBack(curLine) >= 540) {
						isOver = true;
				}

				while (window.pollEvent(event))
				{
						if (event.type == sf::Event::Closed) window.close();
						if (event.type == sf::Event::KeyPressed)
						{
								if (event.key.code == sf::Keyboard::Escape) window.close();
								else if (event.key.code == sf::Keyboard::Left && curLine > 0) {
										curLine--;
								}
								else if (event.key.code == sf::Keyboard::Right && curLine < 3) {
										curLine++;
								}
								else if (event.key.code == sf::Keyboard::Enter && isOver == true) {
										cars = Cars();
										isOver = false;
										curLine = 3;
										score = 0;
										text.setPosition(20, 20);
								}
						}
				}

				myCarSprite.setPosition(getPos(curLine), 720);

				// Выполняем необходимые действия по отрисовке
				window.clear();
				window.draw(backSprite);
				std::stringstream ss;
				if (!isOver) {
						ss << score;
						text.setString(ss.str());
						window.draw(text);
						window.draw(myCarSprite);
						cars.draw(carTexture, window);
				}
				else {
						ss << "You overtook " << score << " cars!\nPress Enter to restart";
						text.setPosition(50, 410);
						text.setString(ss.str());
						window.draw(text);
				}
				window.display();
		}

		return 0;
}