#ifndef MODEBLUR_HPP
#define MODEBLUR_HPP

#include <Transform.hpp>

class ModeBlur : public Transform
{
private:
	std::size_t width, height;

	sf::Color applyLocal(const sf::Image &, std::size_t, std::size_t);

public:
	ModeBlur(std::size_t, std::size_t);
	~ModeBlur();

	void apply(sf::Image &) override;
};

#endif