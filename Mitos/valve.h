/** @file valve.h
*  @brief Class to represent and the valve state
*
*
*  @author Jonathan Bramble (mbzjpb)
*  Copyright 2016
*/

#pragma once

#include "stdafx.h"

namespace Mitos {

	const std::string FOUR_PORT_A = "0";
	const std::string FOUR_PORT_B = "6";
	const std::string FOUR_PORT_C = "12";
	const std::string FOUR_PORT_D = "18";
	const std::string MOVE_VALVE_POS = "E2 2";

	enum class valve_position { A, B, C, D };

	/**
	*  @brief Class to represent and the valve state
	*
	*
	*/
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
		/**
		*  @brief Construct a valve object for each valve by address
		*
		*  @param _address int
		*/
		Valve(const int _address);
		~Valve();

		/**
		*  @brief Return command string for port change
		*
		*  @return command string
		*/
		std::string get_port_cmd() const;

		/**
		*  @brief Return motor state for valve
		*
		*  @return motor state int
		*/
		int get_motor() const;

		/**
		*  @brief Set the valve position
		*
		*  @param _pos valve_position
		*/
		void set_position(const valve_position _pos);

		/**
		*  @brief Set the valve motor state
		*
		*  @param _motor int
		*/
		void set_motor(const int _motor);

	};

}

