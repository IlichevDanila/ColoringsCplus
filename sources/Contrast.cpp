#ifndef CONTRAST_CPP
#define CONTRAST_CPP

#include <SFML/Graphics.hpp>
#include <cmath>

#include <Contrast.hpp>
#include <ColorUtils.hpp>

Contrast::Contrast(double param = 0.0): p(param > 0.0 ? param : 1e-10){}
Contrast::~Contrast(){}

double
Contrast::interpol(double x)
{
	double res = 255.0 * (std::atan(p*(x - 127.5)) + std::atan(p*127.5));
	res /= 2*std::atan(p*127.5);
	return res;
}

void
Contrast::apply(sf::Image &image)
{
	std::size_t w = image.getSize().x;
	std::size_t h = image.getSize().y;

	int newR, newG, newB;
	sf::Color pix;
	std::size_t i, j;
	for(i = 0; i < w; ++i) {
		for(j = 0; j < h; ++j) {
			pix = image.getPixel(i, j);
			newR = clamp(static_cast<int>(interpol(static_cast<double>(pix.r))));
			newG = clamp(static_cast<int>(interpol(static_cast<double>(pix.g))));
			newB = clamp(static_cast<int>(interpol(static_cast<double>(pix.b))));
			image.setPixel(i, j, sf::Color(newR, newG, newB));
		}
	}
}

#endif