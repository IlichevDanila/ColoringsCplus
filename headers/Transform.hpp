#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <SFML/Graphics.hpp>

class Transform
{
public:
	virtual void apply(sf::Image &) = 0;
};

#endif