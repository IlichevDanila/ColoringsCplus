#ifndef SETBRIGHTNESS_HPP
#define SETBRIGHTNESS_HPP

#include <SFML/Graphics.hpp>

#include <Transform.hpp>

class SetBrightness : public Transform
{
private:
	double ratio;

public:
	SetBrightness(double);
	~SetBrightness();

	void apply(sf::Image &) override;
};

#endif