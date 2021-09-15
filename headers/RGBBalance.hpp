#ifndef RGBBALANCE_HPP
#define RGBBALANCE_HPP

#include <SFML/Graphics.hpp>

#include <Transform.hpp>

class RGBBalance : public Transform
{
private:
	double r, g, b;

public:
	RGBBalance(double, double, double);
	~RGBBalance();

	void apply(sf::Image &);
};

#endif