#pragma once

#include "stdafx.h"

namespace Mitos {

	class QueueEntry {

		std::string command;
		std::string request;
		int address;

	public:
		QueueEntry(std::string _command, std::string _request, int _address): command(_command), request(_request), address(_address){}

		std::string get_command() const{
			return command;
		}

		std::string get_request() const{
			return request;
		}

		int get_address() const{
			return address;
		}

		friend std::ostream& operator<<(std::ostream& os, const QueueEntry& qe){
			os << qe.command << qe.request << std::to_string(qe.address);
			return os;
		}
	};
}

