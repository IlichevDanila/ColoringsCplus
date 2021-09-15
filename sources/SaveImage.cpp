#ifndef SAVEIMAGE_CPP
#define SAVEIMAGE_CPP

#include <SFML/Graphics.hpp>

#include <SaveImage.hpp>

SaveImage::SaveImage(const std::string &name): path(name){}
SaveImage::~SaveImage(){}

void
SaveImage::apply(sf::Image &image)
{
	image.saveToFile(path);
}

#endif