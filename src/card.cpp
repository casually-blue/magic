#include<card.h>
#include<string>

std::string Card::to_string(){
	return this->value->to_string();
}

std::string ManaValue::to_string(){
	return std::string("unimp");
}
