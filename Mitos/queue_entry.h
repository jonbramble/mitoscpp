/** @file queue_entry.h
*  @brief Class to represent the elements in the command queue
*
*  
*  @author Jonathan Bramble (mbzjpb)
*  Copyright 2016
*/

#pragma once

#include "stdafx.h"

namespace Mitos {

	/**
	*  @brief Class to represent the entries in the command queue
	*
	*/
	class QueueEntry {

		std::string command;
		std::string request;
		int address;

	public:

		/**
		*  @brief Construct a command string object
		*
		*  @param _command string
		*  @param _request string
		*  @param _address int
		*/
		QueueEntry(std::string _command, std::string _request, int _address): command(_command), request(_request), address(_address){}

		/**
		*  @brief Get the command string for this entry
		*
		*  @return the command string
		*/
		std::string get_command() const{
			return command;
		}

		/* @brief Get the request for this entry
		*
		*  @return the request string
		*/
		std::string get_request() const{
			return request;
		}

		/* @brief Get the address of the queue for this entry
		*  
		*  @return the address of the queue
		*/
		int get_address() const{
			return address;
		}

		// stream operator for queue entry - debug use
		friend std::ostream& operator<<(std::ostream& os, const QueueEntry& qe){
			os << qe.command << qe.request << std::to_string(qe.address);
			return os;
		}
	};
}

