#include "stdafx.h"
#include "syringe.h"

namespace Mitos{

	Syringe::Syringe(const int _address) : address(_address), position(0), rate(0), motor(0) 
	{
	}

	Syringe::~Syringe()
	{
	}

	std::string Syringe::get_fill_cmd() const{
		return MOVE_SYRINGE_POS + " " + std::to_string(ZERO_POSITION);
	}

	std::string Syringe::get_rate_cmd() const{
		int pos = rate*ZERO_POSITION / SYRINGE_SIZE;
		return SET_PUMP_RATE + " " + std::to_string(pos);
	}

	std::string Syringe::get_empty_cmd() const{
		return MOVE_SYRINGE_POS + " " + std::to_string(EMPTY_POSITION);
	}

	int Syringe::get_motor() const{
		return motor;
	}

	int Syringe::get_position() const{
		return position;
	}

	void Syringe::set_rate(const int _rate){
		rate = _rate;
	}

	void Syringe::set_motor(const int _motor){
		motor = _motor;
	}

	void Syringe::set_position(const int _position){
		position = _position;
	}

}
