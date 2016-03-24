
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

		XsDuoBasic();
		~XsDuoBasic();

		void init();

		bool set_rate(const int address, const int rate);
		bool set_port(const int address, valve_position position);
		bool fill_syringe(const int address);
		bool empty_syringe(const int address);

		void dispense(const int address, const int amount);

		void quick_start();

		void info();
		bool run();

		void prepare_pump(); //this must be called

	private:
		serial::Serial *sp;
		std::vector<CommandQueue> queues; //we have 2 queues
		std::vector<Syringe> syringes;
		std::vector<Valve> valves;

		void write_command_status(const int);
		std::string listen();
		void flush_input();
		void write(const std::string);
		void close();

		void clear_queue();
		void write_stop();

		void add_to_queue(const int address, const std::string cmd);
		void prepend_queue(const int address, const std::string cmd);

		bool process_status(const ResponseState rep);
		void process_command(const ResponseState rep);

	};

}