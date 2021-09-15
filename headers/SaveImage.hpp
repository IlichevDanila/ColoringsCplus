#ifndef SAVEIMAGE_HPP
#define SAVEIMAGE_HPP

#include <SFML/Graphics.hpp>

#include <Transform.hpp>

class SaveImage : public Transform
{
private:
	std::string path;

public:
	SaveImage(const std::string &);
	~SaveImage();

	void apply(sf::Image &) override;
};

#endif