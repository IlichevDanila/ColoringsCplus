#ifndef SETBRIGHTNESS_CPP
#define SETBRIGHTNESS_CPP

#include <SFML/Graphics.hpp>

#include <SetBrightness.hpp>
#include <ColorUtils.hpp>

SetBrightness::SetBrightness(double r): ratio(r){}
SetBrightness::~SetBrightness(){}

void
SetBrightness::apply(sf::Image &image)
{
	std::size_t w = image.getSize().x;
	std::size_t h = image.getSize().y;

	int r, g, b;
	sf::Color pix;
	std::size_t i, j;
	for(i = 0; i < w; ++i) {
		for(j = 0; j < h; ++j) {
			pix = image.getPixel(i, j);
			r = clamp(static_cast<int>(static_cast<double>(pix.r) * ratio));
			g = clamp(static_cast<int>(static_cast<double>(pix.g) * ratio));
			b = clamp(static_cast<int>(static_cast<double>(pix.b) * ratio));
			image.setPixel(i, j, sf::Color(r, g, b));
		}
	}
}	

#endif