// Mitos.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>
#include <iostream>


#include "serial/serial.h"

using std::vector;


namespace Mitos {

	class XsDuoBasic{
	public:

		serial::Serial *my_serial;

		void enumerate_ports()
		{
			vector<serial::PortInfo> devices_found = serial::list_ports();

			vector<serial::PortInfo>::iterator iter = devices_found.begin();

			while (iter != devices_found.end())
			{
				serial::PortInfo device = *iter++;

				printf("(%s, %s, %s)\n", device.port.c_str(), device.description.c_str(),
					device.hardware_id.c_str());
			}
		}

		XsDuoBasic() {
			unsigned long baud = 9600;
			std::string port = "COM4";
			my_serial = new serial::Serial(port, baud, serial::Timeout::simpleTimeout(1000));

		}

		void write(){

			my_serial->write("$00F\r");
			Sleep(250);
			//my_serial->flushInput();
			my_serial->write("$01F\r");
			Sleep(250);
			//my_serial->flushInput();

			my_serial->write("$00I2\r");
			Sleep(250);

			std::string resp = my_serial->readline();
			std::cout << resp << std::endl;

			my_serial->write("$01I2\r");
			Sleep(250);

			resp = my_serial->readline();
			std::cout << resp << std::endl;


			my_serial->write("$00S3\r");
			resp = my_serial->readline();
			std::cout << resp << std::endl;

			my_serial->write("$01S3\r");
			resp = my_serial->readline();
			std::cout << resp << std::endl;



			//my_serial->write

		}

		~XsDuoBasic(){
			delete my_serial;
		}

	};



}


int _tmain(int argc, _TCHAR* argv[])
{
	
	Mitos::XsDuoBasic p;
	//p.enumerate_ports();

	p.write();

	return 0;
}

