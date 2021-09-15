#ifndef IMAGEPROCESSING_HPP
#define IMAGEPROCESSING_HPP

#include <string>
#include <SFML/Graphics.hpp>

#include <TransformStack.hpp>
#include <ColorSet.hpp>

class ImageProcessing
{
private:
	sf::Image image;

	TransformStack stack;
	ColorSet cs;

public:
	ImageProcessing();
	~ImageProcessing();

	void process(const std::string &);

	sf::Image &getImage();
};

#endif