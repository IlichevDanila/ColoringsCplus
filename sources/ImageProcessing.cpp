#ifndef IMAGEPROCESSING_CPP
#define IMAGEPROCESSING_CPP

#include <iostream>
#include <fstream>

#include <ImageProcessing.hpp>
#include <Blur.hpp>
#include <Border.hpp>
#include <SetSimplify.hpp>
#include <ModeBlur.hpp>
#include <SaveImage.hpp>
#include <SetBrightness.hpp>
#include <RGBBalance.hpp>
#include <Contrast.hpp>
#include <TransformStack.hpp>

ImageProcessing::ImageProcessing(): image(), stack(), cs(){}


ImageProcessing::~ImageProcessing(){}

static ColorSet
getColorSetByClicking(const sf::Image &image)
{
	ColorSet cs;

	sf::Texture text;
	text.loadFromImage(image, sf::IntRect(0, 0, image.getSize().x, image.getSize().y));
	
	sf::Sprite imageSprite;
	imageSprite.setTexture(text);
	int originX = 0;
	int originY = 0;
	
	const unsigned int maxWidth = 1000;
	const unsigned int maxHeight = 600;
	
	unsigned int windowWidth = std::min(image.getSize().x, maxWidth);
	unsigned int windowHeight = std::min(image.getSize().y, maxHeight);
	
	const int speed = 15;
	
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "ColorSet Generator");
	
	sf::Event event;
	while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
            else if(event.type == sf::Event::KeyPressed) {
            	switch(event.key.code) {
            	case sf::Keyboard::Enter:
            		window.close();
            		break;
            	case sf::Keyboard::Left:
            		if(originX > 0) {
            			originX -= std::min(speed, originX);
            			imageSprite.setOrigin(originX, originY);
            		}
            		break;
            	case sf::Keyboard::Right:
            		if(originX < image.getSize().x - windowWidth) {
            			originX += std::min(speed, static_cast<int>(image.getSize().x - windowWidth - originX));
            			imageSprite.setOrigin(originX, originY);
            		}
            		break;
            	case sf::Keyboard::Up:
            		if(originY > 0) {
            			originY -= std::min(speed, originY);
            			imageSprite.setOrigin(originX, originY);
            		}
            		break;
            	case sf::Keyboard::Down:
            		if(originY < image.getSize().y - windowHeight) {
            			originY += std::min(speed, static_cast<int>(image.getSize().y - windowHeight - originY));
            			imageSprite.setOrigin(originX, originY);
            		}
            		break;
            	}
            }
            else if(event.type == sf::Event::MouseButtonPressed) {
            	sf::Color px = image.getPixel(event.mouseButton.x + originX, event.mouseButton.y + originY);

            	switch(event.mouseButton.button) {
            	case sf::Mouse::Left:
            		if(cs.size() > 0) {
            			std::cout << "Distance: " << distance(px, cs.getClosest(px)) << std::endl;
            		}
            		cs.add(px, true);
            		std::cout << "Total count: " << cs.size() << " colors" << std::endl << std::endl;
            		break;
            	case sf::Mouse::Right:
            		cs.add(px, false);
            		std::cout << "Total count: " << cs.size() << " colors" << std::endl << std::endl;
            		break;
            	}
            	
            }
        }
	
        window.clear(sf::Color::Black);
        window.draw(imageSprite);
        window.display();
    }

    std::cout << "ColorSet was generated" << std::endl;

    return cs;
}

static ColorSet
getColorSetFromImage(const sf::Image &image)
{
	ColorSet cs;

	unsigned int i, j;
	for(i = 0; i < image.getSize().x; ++i) {
		for(j = 0; j < image.getSize().y; ++j) {
			cs.add(image.getPixel(i, j), true);
		}
	}

	std::cout << "Total count: " << cs.size() << " colors" << std::endl;

	return cs;
}

void
ImageProcessing::process(const std::string &configPath)
{
	std::ifstream fin(configPath);

	std::string filepath;
	fin >> filepath;

	image.loadFromFile(filepath);

	std::string type, name1, name2;
	std::size_t param1, param2;
	double r, g, b;

	while(!fin.eof()) {
		fin >> type;
		if(type == "Blur") {
			fin >> param1 >> param2;
			Blur bl(param1, param2);
			bl.apply(image);
		}
		else if(type == "Border") {
			Border br;
			br.apply(image);
		}
		else if(type == "SetSimplify") {
			fin >> name1;
			SetSimplify ss(cs);
			ss.apply(image);
		}
		else if(type == "GenerateSet") {
			fin >> name1;
			if(name1 == "ByClick") {
				cs = getColorSetByClicking(image);
			}
			else if(name1 == "FromImage") {
				cs = getColorSetFromImage(image);
			}
		}
		else if(type == "ModeBlur") {
			fin >> param1 >> param2;
			ModeBlur mb(param1, param2);
			mb.apply(image);
		}
		else if(type == "SaveImage"){
			fin >> name1;
			SaveImage sv(name1);
			sv.apply(image);
		}
		else if(type == "SetBrightness") {
			fin >> r;
			SetBrightness sb(r);
			sb.apply(image);
		}
		else if(type == "RGBBalance") {
			fin >> r >> g >> b;
			RGBBalance rb(r, g, b);
			rb.apply(image);
		}
		else if(type == "Contrast") {
			fin >> r;
			Contrast c(r);
			c.apply(image);
		}
	}
}

sf::Image &
ImageProcessing::getImage()
{
	return image;
}

#endif