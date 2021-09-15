#ifndef TRANSFORMSTACK_CPP
#define TRANSFORMSTACK_CPP

#include <list>
#include <SFML/Graphics.hpp>

#include <TransformStack.hpp>
#include <Blur.hpp>
#include <Border.hpp>
#include <SetSimplify.hpp>
#include <ModeBlur.hpp>
#include <SaveImage.hpp>
#include <SetBrightness.hpp>
#include <RGBBalance.hpp>
#include <Contrast.hpp>

TransformStack::TransformStack(): transforms(){}

TransformStack::~TransformStack()
{
	for(auto itr: transforms) {
		delete itr;
	}
}

void
TransformStack::add(Transform *tr)
{
	transforms.push_back(tr);
}

void
TransformStack::apply(sf::Image &image)
{
	for(auto transform: transforms) {
		transform->apply(image);
	}
}

#endif