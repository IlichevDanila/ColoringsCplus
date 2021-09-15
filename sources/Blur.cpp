#ifndef BLUR_CPP
#define BLUR_CPP

#include <cstddef>
#include <SFML/Graphics.hpp>

#include <Blur.hpp>
#include <ColorUtils.hpp>

Blur::Blur(std::size_t width, std::size_t height)
{
	//widht and height only allowed to be odd
	this->width = 2*(width / 2) + 1;		
	this->height = 2*(height / 2) + 1;
}


Blur::~Blur(){}

sf::Color
Blur::applyLocal(const sf::Image &image, std::size_t x, std::size_t y)
{
	std::size_t w = image.getSize().x;
	std::size_t h = image.getSize().y;

	std::size_t cx = width / 2;
	std::size_t cy = height / 2;

	std::size_t left = (cx < x) ? 0 : cx - x;
	std::size_t right = (x + cx < w)? 2*cx + 1 : w - x + cx;
	std::size_t down = (cy < y) ? 0 : cy - y;
	std::size_t up = (y + cy < h)? 2*cy + 1 : h - y + cy;

	std::size_t i, j;
	double r = 0.0;
	double g = 0.0;
	double b = 0.0;
	sf::Color pix;
	for(i = left; i < right; ++i) {
		for(j = down; j < up; ++j) {
			pix = image.getPixel(x + i - cx, y + j - cy);
			r += static_cast<float>(pix.r);
			g += static_cast<float>(pix.g);
			b += static_cast<float>(pix.b);
		}
	}

	double area = static_cast<float>(right - left) * static_cast<float>(up - down);
	int res_r = clamp(static_cast<int>(r / area));
	int res_g = clamp(static_cast<int>(g / area));
	int res_b = clamp(static_cast<int>(b / area));
	return sf::Color(res_r, res_g, res_b);
}

void
Blur::apply(sf::Image &image)
{
	std::size_t w = image.getSize().x;
	std::size_t h = image.getSize().y;

	std::size_t i, j;

	sf::Color **new_img = new sf::Color*[w];
	for(i = 0; i < w; ++i) {
		new_img[i] = new sf::Color[h];
		for(j = 0; j < h; ++j) {
			new_img[i][j] = applyLocal(image, i, j);
		}
	}

	for(i = 0; i < w; ++i) {
		for(j = 0; j < h; ++j) {
			image.setPixel(i, j, new_img[i][j]);
		}
		delete[] new_img[i];
	}
	delete[] new_img;
}

#endif