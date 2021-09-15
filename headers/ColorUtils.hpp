#ifndef COLORUTILS_HPP
#define COLORUTILS_HPP

#include <string>
#include <functional>
#include <SFML/Graphics.hpp>

template<>
struct std::less<sf::Color>
{
	bool operator()(sf::Color const &x, sf::Color const &y) const{
		if(x.r < y.r) {
			return true;
		}
		if(x.r > y.r) {
			return false;
		}
	
		if(x.g < y.g) {
			return true;
		}
		if(x.g > y.g) {
			return false;
		}
	
		return x.b < y.b;
	}
};

extern int clamp(int);
extern double distance(const sf::Color &, const sf::Color &);
extern sf::Color colorFromCode(const std::string &);
extern std::string codeFromColor(sf::Color);

#endif