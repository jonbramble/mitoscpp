/** @file syringe.h
*  @brief Class to represent and the syringe state
*
*
*  @author Jonathan Bramble (mbzjpb)
*  Copyright 2016
*/

#pragma once

#include "stdafx.h"

namespace Mitos {

	const std::string SET_PUMP_RATE = "E2 3";		///< Command to set pump rate
	const std::string MOVE_SYRINGE_POS = "E2 1";		///< Command to move the position
	const std::string SET_POSITION = "I3";			///< Command to set the position

	const int ZERO_POSITION = 30000;			///< Fixed point for full
	const int EMPTY_POSITION = 0;				///< Fixed point for empty

	const int SYRINGE_SIZE = 2500;				///< Hardcoded syringe size in ul

	/**
	*  @brief Class to represent and the syringe state
	*
	*
	*/
	class Syringe
	{
		const int address;
		int position;
		int motor;
		int rate;

	public:
		/**
		*  @brief Construct a syringe object for each syringe by address
		*
		*  @param _address int
		*/
		Syringe(const int _address);
		~Syringe();

		/**
		*  @brief Return command string for syringe fill
		*
		*  @return command string
		*/
		std::string get_fill_cmd() const;

		/**
		*  @brief Return command string for syringe rate 
		*
		*  @return command string
		*/
		std::string get_rate_cmd() const;

		/**
		*  @brief Return command string for syringe empty
		*
		*  @return command string
		*/
		std::string get_empty_cmd() const;

		// print syringe status message
		friend std::ostream& operator<<(std::ostream& os, const Syringe& syringe){
			os << "Syringe" << std::endl
				<< "Address: " << syringe.address << std::endl
				<< "Position: " << syringe.position << std::endl
				<< "Motor: " << syringe.motor << std::endl
				<< "Rate: " << syringe.rate << std::endl;
			return os;
		}

		/**
		*  @brief Return motor state for syringe
		*
		*  @return motor state int
		*/
		int get_motor() const;

		/**
		*  @brief Return position state for syringe
		*
		*  @return motor state int
		*/
		int get_position() const;

		/**
		*  @brief Set the syringe rate
		*
		*  @param _rate int
		*/
		void set_rate(const int _rate);

		/**
		*  @brief Set the motor statue
		*
		*  @param _motor int
		*/
		void set_motor(const int _motor);

		/**
		*  @brief Set the syringe position
		*
		*  @param _position int
		*/
		void set_position(const int _position);

	};


}
