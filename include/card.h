#include<string>

class ManaValue {
	int red,blue,green,black,white,colorless;

	public:
	ManaValue(int red, int blue, int green, int black, int white, int colorless): red(red), blue(blue), green(green), black(black), white(white), colorless(colorless) {}
	std::string to_string();
};

class Card {
	ManaValue *value;

	public:
	Card(ManaValue* value): value(value) {}

	std::string to_string();
};
