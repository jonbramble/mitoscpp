/** @file command_queue.h
*  @brief Queue for commands to send to pump
*
*
*  @author Jonathan Bramble (mbzjpb)
*  Copyright 2016
*/

#pragma once

#include "stdafx.h"
#include "queue_entry.h"

#include <deque>

namespace Mitos {

	class CommandQueue {

	public:

		/**
		*  @brief Construct a command queue for each syringe by address
		*
		*  @param Address int
		*/
		CommandQueue(const int _address);
		
		/**
		*  @brief Get the address for this queue
		*
		*  @return int
		*/
		int get_address() const;

		/**
		*  @brief Get the first value and remove it from the queue
		*
		*  @return QueueEntry
		*/
		QueueEntry shift();				//get value from the front

		/**
		*  @brief Get the first value and remove it from the queue
		*
		*  @return QueueEntry
		*/
		QueueEntry subscribe();			//same as shift

		/**
		*  @brief Get the first value from the queue
		*
		*  @return QueueEntry
		*/
		QueueEntry first() const;

		/**
		*  @brief Get the size of the queue
		*
		*  @return int
		*/
		size_t size() const;	

		/**
		*  @brief Is the queue empty?
		*
		*  @return bool
		*/
		bool empty() const;

		/**
		*  @brief Is the next element a movement command
		*  Defined by mitos pump command lists
		*
		*  @return bool
		*/
		bool movement();			

		/**
		*  @brief Add object at the back of the queue
		*
		*  @param request const string
		*/
		void push_back(const std::string _request);	

		/**
		*  @brief Prepend object to the front of the queue
		*
		*  @param request const string
		*/
		void unshift(const std::string _request);	
	
		/**
		*  @brief empty the queue
		*
		*/
		void clear();

		/**
		*  @brief Get the request from the first queue entry
		*
		*  @return string
		*/
		std::string first_request() const;

		// print the queue status
		friend std::ostream& operator<<(std::ostream& os, const CommandQueue& qq){
			os << "Address: " << qq.address << std::endl
				<< "Request: " << qq.first_request() << std::endl;
			return os;
		}

	private:
		std::string command_string(const std::string _request);		// Create command string to send to pump
		std::deque<QueueEntry> q;									// The internal queue
		int address;												// Address of the queue

	};
}