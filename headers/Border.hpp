#ifndef BORDER_HPP
#define BORDER_HPP

#include <SFML/Graphics.hpp>

#include <Transform.hpp>

class Border : public Transform
{
private:
	sf::Color borderColor;
	sf::Color backColor;

	sf::Color applyLocal(const sf::Image &, std::size_t, std::size_t);

public:
	Border(sf::Color, sf::Color);
	Border(sf::Color bcolor = sf::Color(150, 150, 150));
	~Border();

	void apply(sf::Image &) override;
};

#endif