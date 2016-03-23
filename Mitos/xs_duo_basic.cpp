#include "stdafx.h"
#include "xs_duo_basic.h"

namespace Mitos{

	XsDuoBasic::XsDuoBasic(){
		unsigned long baud = 9600;
		std::string port = "COM4";
		sp = new serial::Serial(port, baud, serial::Timeout::simpleTimeout(2000));

		queues.emplace_back(0);
		queues.emplace_back(1);

		syringes.emplace_back(0);
		syringes.emplace_back(1);

		valves.emplace_back(0);
		valves.emplace_back(1);
	}

	bool XsDuoBasic::set_rate(const int address, const int rate){
		syringes[address].set_rate(rate);
		std::string cmd = syringes[address].get_rate_cmd();
		add_to_queue(address, cmd);
		return true;
	}

	bool XsDuoBasic::set_port(const int address, valve_position position){
		valves[address].set_position(position);
		std::string cmd = valves[address].get_port_cmd();
		add_to_queue(address, cmd);
		return true;
	}

	bool XsDuoBasic::fill_syringe(const int address){
		std::string cmd = syringes[address].get_fill_cmd();
		add_to_queue(address, cmd);
		return true;
	}

	bool XsDuoBasic::empty_syringe(const int address){
		std::string cmd = syringes[address].get_empty_cmd(); 
		add_to_queue(address, cmd);
		return true;
	}

	void  XsDuoBasic::info(){
		std::cout << syringes[0] << std::endl;
		std::cout << syringes[1] << std::endl;

		std::cout << valves[0] << std::endl;
		std::cout << valves[1] << std::endl;

		std::cout << queues[0] << std::endl;
		std::cout << queues[1] << std::endl;

	}

	void XsDuoBasic::run(){
		write_command_status(0);

		while (true) {
			std::string str = listen();
			ResponseState rep = parse_response(str);

			if (rep.get_status()){
				if (process_status(rep)){
					break;
				}
			}
			else if (!rep.get_status()){
				process_command(rep);
			}
			else {
				std::cout << "Unknown message type" << std::endl;
			}
		}
	}

	ResponseState XsDuoBasic::parse_response(const std::string msg){
		ResponseState rep(msg);
		return rep;
	}

	void XsDuoBasic::process_command(const ResponseState rep){
		int address = rep.get_address();
		int res_type = rep.get_rsp_type(); //could use enum here

		switch (res_type){
		case 0:
			std::cout << "Command OK" << std::endl;
			break;
		case 1:
			std::cout << "Invalid Command" << std::endl;
			break;
		case 2:
			std::cout << "Busy - command ignored" << std::endl;
			break;
		case 3:
			std::cout << "Can't Process - input out of range or error" << std::endl;
			break;
		}

		write_command_status(address);
	}

	bool XsDuoBasic::process_status(const ResponseState rep){
		int address = rep.get_address();
		int other_address = (address == 0) ? 1 : 0; 
		int ret = 0;
		bool empty = false;

		// could let syringe have rep and set values
		int _syringe_position = rep.get_syringe_position();
		int _syringe_motor = rep.get_syringe_motor();
		int _valve_position = rep.get_valve_position();
		int _valve_motor = rep.get_valve_motor();

		syringes[address].set_motor(_syringe_motor);
		syringes[address].set_position(_syringe_position);
		valves[address].set_motor(_valve_motor);
		valves[address].set_position(static_cast<valve_position>(_valve_position));

		bool these_motors = valves[address].get_motor() == 1 && syringes[address].get_motor();
		bool other_motors = valves[other_address].get_motor() == 1 && syringes[other_address].get_motor();

		bool motors = these_motors && other_motors;
		empty = queues[address].empty() && queues[other_address].empty();

		if (queues[address].empty() ){
			write_command_status(other_address);
		}
		else {
			if (queues[address].movement()){
				if (these_motors){
					write(queues[address].shift().get_command());
				}
				else {
					write_command_status(other_address);
				}
			}
			else {
				write(queues[address].shift().get_command());
			}
		}

		return empty && motors;
	}

	void XsDuoBasic::write_command_status(const int address){
		queues[address].unshift(STATUS);
		write(queues[address].shift().get_command());
	}

	std::string XsDuoBasic::listen(){
		return sp->readline(20, "\r");
	}

	void XsDuoBasic::init(){

		std::cout << "Init pumps" << std::endl;
		add_to_queue(0, FLUSH);
		add_to_queue(1, FLUSH);

		write(queues[0].shift().get_command());
		write(queues[1].shift().get_command());

		flush_input();

		add_to_queue(0, INITIALIZE_VALVE);
		add_to_queue(1, INITIALIZE_VALVE);
		add_to_queue(0, INITIALIZE_SYRINGE);
		add_to_queue(1, INITIALIZE_SYRINGE);

		while (!queues[0].empty()){
			write(queues[0].shift().get_command());
			std::string rep = listen();
			std::cout << rep << std::endl;
			parse_response(rep);
		}

		while (!queues[1].empty()){
			write(queues[1].shift().get_command());
			std::string rep = listen();
			std::cout << rep << std::endl;
			parse_response(rep);
		}

		Sleep(1000);

		write_command_status(0);
		std::string rep = listen();
		std::cout << rep << std::endl;
		parse_response(rep);

		write_command_status(1);
		rep = listen();
		std::cout << rep << std::endl;
		parse_response(rep);
	}

	void XsDuoBasic::write(std::string cmd){
		std::cout << cmd << std::endl;
		sp->write(cmd);
		Sleep(250);
	}

	void XsDuoBasic::add_to_queue(const int address, const std::string cmd){
		queues[address].push_back(cmd);
	}

	void XsDuoBasic::prepend_queue(const int address, const std::string cmd){
		queues[address].unshift(cmd);
	}

	void XsDuoBasic::flush_input(){
		// dump 7 bytes from input on both queues
		sp->read(7);
		sp->read(7);
		Sleep(1000);
	}

	XsDuoBasic::~XsDuoBasic(){
		delete sp;
	}

}