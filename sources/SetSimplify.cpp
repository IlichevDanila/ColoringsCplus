#ifndef SETSIMPLIFY_CPP
#define SETSIMPLIFY_CPP

#include <SFML/Graphics.hpp>

#include <SetSimplify.hpp>
#include <ColorSet.hpp>

SetSimplify::SetSimplify(): set(nullptr){}
SetSimplify::SetSimplify(const ColorSet &s): set(&s){}

SetSimplify::~SetSimplify(){}

void
SetSimplify::setSet(const ColorSet &s)
{
	set = &s;
}

sf::Color
SetSimplify::applyLocal(const sf::Image &image, std::size_t x, std::size_t y)
{
	if(set == nullptr) {
		return sf::Color::Black;
	}
	return set->getClosest(image.getPixel(x, y));
}

void
SetSimplify::apply(sf::Image &image)
{
	std::size_t w = image.getSize().x;
	std::size_t h = image.getSize().y;

	std::size_t i, j;

	for(i = 0; i < w; ++i) {
		for(j = 0; j < h; ++j) {
			image.setPixel(i, j, applyLocal(image, i, j));
		}
	}
}

#endif