#pragma once

#include "stdafx.h"

namespace Mitos {

	const std::string SET_PUMP_RATE = "E2 3";
	const std::string MOVE_SYRINGE_POS = "E2 1";
	const std::string SET_POSITION = "I3";

	const int ZERO_POSITION = 30000;
	const int EMPTY_POSITION = 0;

	const int SYRINGE_SIZE = 2500;

	class Syringe
	{
		const int address;
		int position;
		int motor;
		int rate;

	public:
		Syringe(const int _address);
		~Syringe();

		std::string get_fill_cmd() const;
		std::string get_rate_cmd() const;
		std::string get_empty_cmd() const;

		friend std::ostream& operator<<(std::ostream& os, const Syringe& syringe){
			os << "Syringe" << std::endl
				<< "Address: " << syringe.address << std::endl
				<< "Position: " << syringe.position << std::endl
				<< "Motor: " << syringe.motor << std::endl
				<< "Rate: " << syringe.rate << std::endl;
			return os;
		}

		int get_motor() const;
		int get_position() const;

		void set_rate(const int _rate);
		void set_motor(const int _motor);
		void set_position(const int _position);

	};


}