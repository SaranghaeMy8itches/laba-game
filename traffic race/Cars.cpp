#include "Cars.h"
#include <random>

Cars::Cars() : cars_(std::vector<std::list<int> >(4))
{
}

int Cars::getBack(int line)
{
	if (cars_[line].empty())
		return 0;
	return cars_[line].back();
}

void Cars::generate()
{
	bool isFree = false;
	for (auto line : cars_)
	{
		if (line.empty() || line.front() >= 0)
		{
			isFree = true;
		}
	}
	if (!isFree)
	{
		return;
	}
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0, 3);
	int randN = dist(rng);
	while (!cars_[randN].empty() && cars_[randN].front() < 0)
	{
		randN = dist(rng);
	}
	cars_[randN].push_front(-170);
}

void Cars::move(int &score)
{
	for (int i = 0; i < 2; i++)
	{
		for (auto &car : cars_[i])
		{
			car += 4;
		}
		if (!cars_[i].empty() && cars_[i].back() >= 900)
		{
			cars_[i].pop_back();
		}
	}
	for (int i = 2; i < 4; i++)
	{
		for (auto &car : cars_[i])
		{
			car += 2;
		}
		if (!cars_[i].empty() && cars_[i].back() >= 900)
		{
			cars_[i].pop_back();
			score++;
		}
	}
}

void Cars::draw(sf::Texture &texture, sf::RenderWindow &window)
{
	sf::Sprite carSprite;
	carSprite.setTexture(texture);
	carSprite.scale(0.223, 0.22);
	carSprite.rotate(180);
	for (int i = 0; i < 2; i++)
	{
		for (int car : cars_[i])
		{
			carSprite.setPosition(100 + 160 * i, car + 170);
			window.draw(carSprite);
		}
	}
	carSprite.rotate(180);
	for (int i = 2; i < 4; i++)
	{
		for (int car : cars_[i])
		{
			carSprite.setPosition(600 - (100 + 160 * (3 - i)), car);
			window.draw(carSprite);
		}
	}
}
