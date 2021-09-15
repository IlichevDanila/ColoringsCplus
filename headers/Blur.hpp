#ifndef FILTER_HPP
#define FILTER_HPP

#include <cstddef>
#include <SFML/Graphics.hpp>

#include <Transform.hpp>

class Blur : public Transform
{
private:
	std::size_t width;
	std::size_t height;

	sf::Color applyLocal(const sf::Image &, std::size_t, std::size_t);

public:
	Blur(std::size_t, std::size_t);
	~Blur();

	void apply(sf::Image &) override;
};

#endif