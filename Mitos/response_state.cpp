#include "stdafx.h"
#include "response_state.h"


ResponseState::ResponseState(const std::string msg) : status(false), rsp_type(0), address(0), syringe_motor(0), valve_motor(0), syringe_position(0), valve_position(0), sensor_error(false){

	split(v_resp, msg, is_any_of(" "), token_compress_on);

	std::string header = v_resp[0];

	int rec_rsp_type = std::stoi(v_resp[1]);
	int rec_msg_type = std::atoi(&header[3]);
	int rec_address = std::atoi(&header[2]);

	address = rec_address;  // error here

	if (rec_msg_type == 1){
		status = true;
		rsp_type = rec_rsp_type;
		//std::cout << "msg 1" << std::endl;
	}
	else if (rec_msg_type == 9){
		status = true;
		syringe_motor = std::stoi(v_resp[1]);
		valve_motor = std::stoi(v_resp[2]);
		syringe_position = std::stoi(v_resp[3]);
		valve_position = std::stoi(v_resp[4]);
		//std::cout << "msg 9" << std::endl;
	}
	else if (rec_msg_type == 8){
		sensor_error = true;
	}
	else
	{
		std::cout << "Unknown Response" << std::endl;
	}

}

bool ResponseState::get_status() const {
	return status;
}

int ResponseState::get_address() const{
	return address;
}

int ResponseState::get_rsp_type() const{
	return rsp_type;
}

int ResponseState::get_syringe_position() const{
	return syringe_position;
}

int ResponseState::get_syringe_motor() const{
	return syringe_motor;
}

int ResponseState::get_valve_position() const{
	return valve_position;
}

int ResponseState::get_valve_motor() const{
	return valve_motor;
}


ResponseState::~ResponseState()
{
}
