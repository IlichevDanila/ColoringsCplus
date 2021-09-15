#ifndef SETSIMPLIFY_HPP
#define SETSIMPLIFY_HPP

#include <SFML/Graphics.hpp>

#include <Transform.hpp>
#include <ColorSet.hpp>

class SetSimplify : public Transform
{
private:
	const ColorSet *set;

	sf::Color applyLocal(const sf::Image &, std::size_t, std::size_t);

public:
	SetSimplify(const ColorSet &);
	SetSimplify();
	~SetSimplify();

	void setSet(const ColorSet &);

	void apply(sf::Image &);
};

#endif