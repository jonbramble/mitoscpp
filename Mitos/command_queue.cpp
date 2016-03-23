#include "stdafx.h"
#include "command_queue.h"

namespace Mitos {

		CommandQueue::CommandQueue(int _address) : address(_address){}

		std::string CommandQueue::command_string(std::string _request){
			const std::string header = "$0";
			const std::string cr = "\r";
			return header + std::to_string(address) + _request + cr;
		}

		void CommandQueue::push_back(std::string _request){
			std::string command = command_string(_request);
			q.emplace_back(command, _request, address);
		}

		// get value from the front
		QueueEntry CommandQueue::shift(){
			QueueEntry entry(q.front()); //copy ctor
			q.pop_front();
			return entry;
		}

		bool CommandQueue::movement(){
			bool ret = false;
			if (!q.empty()){
				QueueEntry entry(q.front());
				std::string req = entry.get_request();
				std::string req_header(req, 0, 2);
				std::cout << "movement: " << req_header << std::endl;
				if (req_header == "E2" || req_header == "I2"){
					ret = true;
				}
			}
			return ret;
		}

		size_t CommandQueue::size(){
			return q.size();
		}

		int CommandQueue::get_address() const{
			return address;
		}

		//void CommandQueue::requests(){
			// not sure what this was for in the ruby version
		//}

		//empty the array here
		void CommandQueue::clear(){
			q.clear();
		}

		//same as shift
		QueueEntry CommandQueue::subscribe(){
			QueueEntry entry(q.front());
			q.pop_front();
			return entry;
		}

		//prepend object to the front
		void CommandQueue::unshift(std::string _request){
			std::string command = command_string(_request);
			q.emplace_front(command, _request, address);
		}

		bool CommandQueue::empty(){
			return q.empty();
		}

		QueueEntry CommandQueue::first(){
			return q.front();
		}

}