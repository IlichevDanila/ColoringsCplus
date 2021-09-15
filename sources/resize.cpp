#include <fstream>
#include <iostream>
#include <string>

#include <Blur.hpp>
#include <SFML/Graphics.hpp>

int
main()
{
	std::string sourcename;
	std::cin >> sourcename;

	std::string resname;
	std::cin >> resname;

	unsigned int ratio;
	std::cin >> ratio;

	sf::Image image;
	image.loadFromFile(sourcename);

	sf::Image newImage;
	newImage.create(image.getSize().x * ratio, image.getSize().y * ratio);

	for(int i = 0; i < newImage.getSize().x; ++i) {
		for(int j = 0; j < newImage.getSize().y; ++j) {
			newImage.setPixel(i, j, image.getPixel(i / ratio, j / ratio));
		}
	}

	Blur br(ratio, ratio);

	br.apply(newImage);

	newImage.saveToFile(resname);

	return 0;
}