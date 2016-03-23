#pragma once

#include "stdafx.h"

namespace Mitos {

	const std::string FOUR_PORT_A = "0";
	const std::string FOUR_PORT_B = "6";
	const std::string FOUR_PORT_C = "12";
	const std::string FOUR_PORT_D = "18";
	const std::string MOVE_VALVE_POS = "E2 2";

	enum class valve_position { A, B, C, D };

	class Valve
	{
		const int address;
		bool initialised;
		int motor;

		valve_position position;

		friend std::ostream& operator<<(std::ostream& os, const Valve& valve){
			
			os << "Valve " << std::endl
				<< "Address: " << valve.address << std::endl
				<< "Motor: " << valve.motor << std::endl
				<< "Position: " << valve.get_position_str() << std::endl;
			return os;
		}

		std::string get_position_str() const; 

	public:
		Valve(const int _address);
		~Valve();

		std::string get_port_cmd() const;

		int get_motor() const;

		void set_position(const valve_position _pos);
		void set_motor(const int _motor);

	};

}

