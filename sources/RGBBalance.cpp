#ifndef RGBBALANCE_CPP
#define RGBBALANCE_CPP

#include <SFML/Graphics.hpp>

#include <ColorUtils.hpp>
#include <RGBBalance.hpp>


RGBBalance::RGBBalance(double r, double g, double b): r(r), g(g), b(b){}
RGBBalance::~RGBBalance(){}

void
RGBBalance::apply(sf::Image &image)
{
	std::size_t w = image.getSize().x;
	std::size_t h = image.getSize().y;

	int newR, newG, newB;
	sf::Color pix;
	std::size_t i, j;
	for(i = 0; i < w; ++i) {
		for(j = 0; j < h; ++j) {
			pix = image.getPixel(i, j);
			newR = clamp(static_cast<int>(static_cast<double>(pix.r) * r));
			newG = clamp(static_cast<int>(static_cast<double>(pix.g) * g));
			newB = clamp(static_cast<int>(static_cast<double>(pix.b) * b));
			image.setPixel(i, j, sf::Color(newR, newG, newB));
		}
	}
}

#endif