#ifndef COLORSET_HPP
#define COLORSET_HPP

#include <cstddef>
#include <set>
#include <string>
#include <SFML/Graphics.hpp>

#include <ColorUtils.hpp>

class ColorSet
{
private:
	std::set<sf::Color> set;

public:
	ColorSet();
	ColorSet(const std::string &);
	~ColorSet();

	ColorSet &operator=(const ColorSet &);

	sf::Color getClosest(const sf::Color &) const;

	void add(sf::Color color, bool reduce = false);

	void write(const std::string &) const;

	std::size_t size() const;
};

#endif