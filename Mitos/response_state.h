#pragma once

#include "stdafx.h"

#include <boost/algorithm/string.hpp>

using namespace boost;


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
	ResponseState(const std::string msg);
	~ResponseState();

	bool get_status() const;

	int get_address() const;
	int get_rsp_type() const;

	int get_syringe_position() const;
	int get_syringe_motor() const;
	int get_valve_position() const;
	int get_valve_motor() const;

};

