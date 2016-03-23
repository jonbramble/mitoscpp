#include "stdafx.h"
#include "valve.h"


namespace Mitos {

	Valve::Valve(const int _address) : address(_address), initialised(false), position(valve_position::A), motor(0)
	{
	}

	std::string Valve::get_port_cmd() const{
		std::string command = "";
		switch (position)
		{
		case valve_position::A:
			command = MOVE_VALVE_POS + " " + FOUR_PORT_A;
			break;
		case valve_position::B:
			command = MOVE_VALVE_POS + " " + FOUR_PORT_B;
			break;
		case valve_position::C:
			command = MOVE_VALVE_POS + " " + FOUR_PORT_C;
			break;
		case valve_position::D:
			command = MOVE_VALVE_POS + " " + FOUR_PORT_D;
			break;
		}
		return command;
	}

	std::string Valve::get_position_str() const{
		std::string command;
		switch (position)
		{
		case valve_position::A:
			command = "A";
			break;
		case valve_position::B:
			command = "B";
			break;
		case valve_position::C:
			command = "C";
			break;
		case valve_position::D:
			command = "D";
			break;
		}
		return command;
	}

	int Valve::get_motor() const{
		return motor;
	}

	void Valve::set_position(const valve_position pos){
		position = pos;
	}

	void Valve::set_motor(const int _motor){
		motor = _motor;
	}


	Valve::~Valve()
	{
	}

}