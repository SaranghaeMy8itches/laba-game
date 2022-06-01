#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <vector>

class Cars
{
public:
  Cars();
  int getBack(int line);
  void generate();
  void move(int &score);
  void draw(sf::Texture &texture, sf::RenderWindow &window);

private:
  std::vector<std::list<int> > cars_;
};
