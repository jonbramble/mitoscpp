/** @file xs_duo_basic.h
*  @brief Class to represent the XS Duo Basic Pump
*  Contains all the logic to control the two pumps via
*  two command queues as describe by the Mitos programming guide.
*  Commands to the pump are internally processed. Once all commands have been
*  given the commands can be run. 
*  An instance of XsDuoBasic should be maintained as reinitialisation causes pump to
*  be emptied. 
*  Prototyped in Ruby
*
*  @author Jonathan Bramble (mbzjpb)
*  Copyright 2016
*/
#include "stdafx.h"
#include "serial/serial.h"

#include "queue_entry.h"
#include "command_queue.h"
#include "response_state.h"
#include "syringe.h"
#include "valve.h"

namespace Mitos{

	//command constants
	const std::string FLUSH = "F";
	const std::string INITIALIZE_SYRINGE = "I1";
	const std::string INITIALIZE_VALVE = "I2";
	const std::string STATUS = "S3";
	const std::string STOP = "X";

	class XsDuoBasic{

	public:

		/**
		*  @brief Construct a xs duo basic pump object
		*
		*  The addresses of the pumps are 0 and 1 left to right
		*  Port names on windows eg. COM4
		*  @param Port String
		*/
		XsDuoBasic(std::string _port);

		/**
		*  @brief Construct a xs duo basic pump object on COM4
		*
		*  The addresses of the pumps are 0 and 1 left to right
		*
		*/
		XsDuoBasic();

		~XsDuoBasic();

		/**
		*  @brief Initialise the pump - call this before all other commands
		*
		*/
		void init();

		/**
		*  @brief Set the pump rate ul/min
		*
		*  @param Address int
		*  @param Rate int
		*
		*/
		bool set_rate(const int address, const int rate);

		/**
		*  @brief Set the port position
		*
		*  @param Address int
		*  @param position valve_position
		*
		*/
		bool set_port(const int address, valve_position position);

		/**
		*  @brief Fill the syringe
		*
		*  @param Address int
		*
		*/
		bool fill_syringe(const int address);

		/**
		*  @brief Empty the syringe
		*
		*  @param Address int
		*
		*/
		bool empty_syringe(const int address);


		/**
		*  @brief Empty the syringe
		*
		*  @param Address int
		*
		*/
		void dispense(const int address, const int amount);


		/**
		*  @brief Quick start setup
		*
		*
		*/
		void quick_start();

		/**
		*  @brief returns info to stdout
		*
		*
		*/
		void info();

		/**
		*  @brief Run the commands in the queue
		*
		*
		*/
		bool run();

		/**
		*  @brief Prepare the pump for run, must be called
		*
		*
		*/
		void prepare_pump();

	private:
		serial::Serial *sp;
		std::vector<CommandQueue> queues;			//we have 2 queues 
		std::vector<Syringe> syringes;				// 2 syringes
		std::vector<Valve> valves;					// 2 valves

		void write_command_status(const int);		
		std::string listen();						// returns data from the serial port upto the cr character
		void flush_input();							// ignore inputs on init
		void write(const std::string);				// write the string to the port
		void close();								// close the port on exit

		void clear_queue();							// clear all the queues
		void write_stop();							// stop the pump!

		void add_to_queue(const int address, const std::string cmd);		//add commands to the queue  - need more control here perhaps on what can be written
		void prepend_queue(const int address, const std::string cmd);		//add command to the front of the queue 

		bool process_status(const ResponseState rep);						//processing status logic takes response states
		void process_command(const ResponseState rep);						//processing command logic takes response states

	};

}