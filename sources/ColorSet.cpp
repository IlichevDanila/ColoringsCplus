#ifndef COLORSET_CPP
#define COLORSET_CPP

#include <cstddef>
#include <set>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>

#include <ColorUtils.hpp>
#include <ColorSet.hpp>

ColorSet::ColorSet(): set(){}

void
ColorSet::add(sf::Color color, bool reduce)
{
	if(!reduce || set.empty() || (distance(getClosest(color), color) > 1.0)){
		set.insert(color);
	}
}

ColorSet::ColorSet(const std::string &filepath): set()
{
	std::string input;
	std::ifstream fin(filepath);
	while(!fin.eof()) {
		fin >> input;
		if(input.size() >= 2 && input[0] == '/' && input[1] == '/') {
			continue;
		}
		set.insert(colorFromCode(input));
	}
}

ColorSet::~ColorSet(){}

ColorSet &
ColorSet::operator=(const ColorSet &rhs)
{
	set.clear();
	for(auto itr: rhs.set) {
		set.insert(itr);
	}
}

sf::Color
ColorSet::getClosest(const sf::Color &color) const
{
	if(set.empty()) {
		return sf::Color::Black;
	}

	sf::Color bestMatch = *set.begin();
	double bestDstSqr = distance(bestMatch, color);
	double currDstSqr = 0;

	for(auto itr = ++set.begin(); itr != set.end(); ++itr) {
		currDstSqr = distance(*itr, color);
		if(currDstSqr < bestDstSqr) {
			bestDstSqr = currDstSqr;
			bestMatch = *itr;
		}
	}

	return bestMatch;
}

void
ColorSet::write(const std::string &path) const
{
	std::ofstream fout(path);
	for(auto itr: set) {
		fout << codeFromColor(itr) << std::endl;
	}
}

std::size_t
ColorSet::size() const
{
	return set.size();
}

#endif