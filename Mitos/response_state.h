/** @file response_state.h
*  @brief Class to represent and process the response state messages
*
*
*  @author Jonathan Bramble (mbzjpb)
*  Copyright 2016
*/

#pragma once

#include "stdafx.h"
#include <boost/algorithm/string.hpp>  // for tokenizer

using namespace boost;

namespace Mitos {

	class ResponseState{

		bool status;
		int rsp_type;
		int address;
		int syringe_motor;
		int valve_motor;
		int syringe_position;
		int valve_position;
		bool sensor_error;

		typedef std::vector<std::string> split_vector_type;

	public:
		/**
		*  @brief Construct a response state object for each syringe by return message
		*
		*  @param message string
		*/
		ResponseState(const std::string msg);
		~ResponseState();

		/**
		*  @brief Get the status of the response state message
		*
		*  @return status bool
		*/
		bool get_status() const;

		/**
		*  @brief Get the address of the response state message
		*
		*  @return status int
		*/
		int get_address() const;

		/**
		*  @brief Get the response type of the response state message
		*
		*  @return response types int
		*/
		int get_rsp_type() const;

		/**
		*  @brief Get the syringe position of the response state message
		*
		*  @return response types int
		*/
		int get_syringe_position() const;

		/**
		*  @brief Get the syringe motor state of the response state message
		*
		*  @return response types int
		*/
		int get_syringe_motor() const;

		/**
		*  @brief Get the valve position of the response state message
		*
		*  @return response types int
		*/
		int get_valve_position() const;

		/**
		*  @brief Get the valve motor state of the response state message
		*
		*  @return response types int
		*/
		int get_valve_motor() const;

	};

}

