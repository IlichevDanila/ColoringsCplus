#ifndef CONTRAST_HPP
#define CONTRAST_HPP

#include <SFML/Graphics.hpp>

#include <Transform.hpp>

class Contrast : public Transform
{
private:
	double p;

	double interpol(double);

public:
	Contrast(double);
	~Contrast();

	void apply(sf::Image &) override;
};

#endif