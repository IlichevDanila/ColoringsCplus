#ifndef COLORUTILS_CPP
#define COLORUTILS_CPP

#include <functional>
#include <cmath>

#include <SFML/Graphics.hpp>

int
clamp(int val)
{
	return val >= 0 ? (val <= 255 ? val : 255) : 0;
}

struct Triplet
{
	double x, y, z;
	Triplet(double a, double b, double c): x(a), y(b), z(c){}
	Triplet(sf::Color c): x(c.r), y(c.g), z(c.b){}
};

static Triplet
RGBToXYZ(Triplet color)
{
	double R = color.x;
	double G = color.y;
	double B = color.z;

	return Triplet(R * 0.4124 + G * 0.3576 + B * 0.1805, R * 0.2126 + G * 0.7152 + B * 0.0722, R * 0.0193 + G * 0.1192 + B * 0.9505);
}

static Triplet
XYZToLAB(Triplet color)
{
	double X = color.x / 95.047;
	double Y = color.y / 100.0;
	double Z = color.z / 92.149;

	if(X > 0.008856) {
		X = std::pow(X, 1.0/3.0);
	}
	else {
		X = ( 7.787 * X ) + ( 4.0 / 29.0 );
	}
	if(Y > 0.008856) {
		Y = std::pow(Y, 1.0/3.0);
	}
	else {
		Y = ( 7.787 * Y ) + ( 4.0 / 29.0 );
	}
	if(Z > 0.008856) {
		Z = std::pow(Z, 1.0/3.0);
	}
	else {
		Z = ( 7.787 * Z ) + ( 4.0 / 29.0 );
	}

	return Triplet(116.0 * Y - 16.0, 500.0 * (X - Y), 200.0 * (Y - Z));
}

double
distance(const sf::Color &x, const sf::Color &y)
{
	double r = x.r / 255.0;
	double g = x.g / 255.0;
	double b = x.b / 255.0;
	Triplet LABx = XYZToLAB(RGBToXYZ(Triplet(r, g, b)));

	r = y.r / 255.0;
	g = y.g / 255.0;
	b = y.b / 255.0;
	Triplet LABy = XYZToLAB(RGBToXYZ(Triplet(r, g, b)));
	return (LABx.x - LABy.x)*(LABx.x - LABy.x) + (LABx.y - LABy.y)*(LABx.y - LABy.y) + (LABx.z - LABy.z)*(LABx.z - LABy.z);
}

static unsigned int
hexToDec(char c)
{
	if(c >= '0' && c <= '9') {
		return c - '0';
	}
	else if(c >= 'a' && c <= 'f'){
		return c - 'a' + 10;
	}
	else {
		return c - 'A' + 10;
	}
}

sf::Color
colorFromCode(const std::string &code)
{
	std::size_t offset = 0;

	if(code[0] == '#') {
		offset = 1;
	}

	int r = (hexToDec(code[offset]) << 4) + hexToDec(code[offset + 1]);
	int g = (hexToDec(code[offset + 2]) << 4) + hexToDec(code[offset + 3]);
	int b = (hexToDec(code[offset + 4]) << 4) + hexToDec(code[offset + 5]);
	return sf::Color(r, g, b);
}

static char
decToHex(char c)
{
	c = c & 0xf;
	if(c >= 0 && c <= 9) {
		return c + '0';
	}
	return c - 10 + 'a';
}

std::string
codeFromColor(sf::Color color)
{
	std::string res(6, 0);
	res[0] = decToHex(color.r >> 4);
	res[1] = decToHex(color.r & 0xf);
	res[2] = decToHex(color.g >> 4);
	res[3] = decToHex(color.g & 0xf);
	res[4] = decToHex(color.b >> 4);
	res[5] = decToHex(color.b & 0xf);
	return res;
}

#endif