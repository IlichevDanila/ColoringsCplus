#ifndef TRANSFORMSTACK_HPP
#define TRANSFORMSTACK_HPP

#include <string>
#include <list>
#include <SFML/Graphics.hpp>

#include <Transform.hpp>

class TransformStack
{
private:
	std::list<Transform *> transforms;

public:
	TransformStack();
	~TransformStack();

	void add(Transform *);

	void apply(sf::Image &);
};

#endif