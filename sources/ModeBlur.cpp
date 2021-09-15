#ifndef MODEBLUR_CPP
#define MODEBLUR_CPP

#include <cstddef>
#include <map>
#include <SFML/Graphics.hpp>

#include <ModeBlur.hpp>
#include <ColorUtils.hpp>

ModeBlur::ModeBlur(std::size_t width, std::size_t height)
{
	this->width = 2*(width / 2) + 1;
	this->height = 2*(height / 2) + 1;
}

ModeBlur::~ModeBlur(){}

sf::Color
ModeBlur::applyLocal(const sf::Image &image, std::size_t x, std::size_t y)
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
	std::map<sf::Color, std::size_t> count;
	for(i = left; i < right; ++i) {
		for(j = down; j < up; ++j) {
			++count[image.getPixel(x + i - cx, y + j - cy)];
		}
	}

	sf::Color bestMatch = count.begin()->first;
	std::size_t maxCount = count.begin()->second;
	for(auto itr = ++count.begin(); itr != count.end(); ++itr) {
		if(itr->second > maxCount) {
			maxCount = itr->second;
			bestMatch = itr->first;
		}
	}

	return bestMatch;
}

void
ModeBlur::apply(sf::Image &image)
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