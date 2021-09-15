#ifndef BORDER_CPP
#define BORDER_CPP

#include <SFML/Graphics.hpp>

#include <Border.hpp>

Border::Border(sf::Color border, sf::Color back): borderColor(border), backColor(back){}
Border::Border(sf::Color border): borderColor(border), backColor(sf::Color::White){}
Border::~Border(){}

sf::Color
Border::applyLocal(const sf::Image &image, std::size_t x, std::size_t y)
{
	std::size_t w = image.getSize().x;
	std::size_t h = image.getSize().y;

	if(x == 0 || x == w - 1 || y == 0 || y == h - 1) {
		return borderColor;
	}

	sf::Color pix = image.getPixel(x, y);
	if(pix != image.getPixel(x - 1, y - 1) || pix != image.getPixel(x - 1, y) || pix != image.getPixel(x - 1, y + 1) ||
		pix != image.getPixel(x, y - 1) || pix != image.getPixel(x, y + 1) ||
		pix != image.getPixel(x + 1, y - 1) || pix != image.getPixel(x + 1, y) || pix != image.getPixel(x + 1, y + 1)) {
		return borderColor;
	}

	return backColor;
}

void
Border::apply(sf::Image &image)
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