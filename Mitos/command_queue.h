#pragma once


#include "stdafx.h"
#include "queue_entry.h"

#include <deque>

namespace Mitos {

	class CommandQueue {

	public:

		CommandQueue(const int _address);
		
		int get_address() const;		//address getter

		QueueEntry shift();				//get value from the front
		QueueEntry subscribe();			//same as shift
		QueueEntry first();

		size_t size();					// size of internal queue
		bool empty();					// is the queue empty?
		bool movement();				// is the next element a movement command

		void push_back(const std::string _request);			//add object at the back
		void unshift(const std::string _request);			//prepend object to the front
	
		void clear();										//empty the queue

		// print the queue status
		friend std::ostream& operator<<(std::ostream& os, const CommandQueue& qq){
			os << "Address: " << qq.address << std::endl
				<< "Request: " << qq.first_request() << std::endl;
			return os;
		}

		std::string first_request() const{
			QueueEntry qe(q.front());
			return qe.get_request();
		}

	private:
		std::string command_string(const std::string _request);		// Create command string to send to pump
		std::deque<QueueEntry> q;									// The internal queue
		int address;												// Address of the queue

	};
}