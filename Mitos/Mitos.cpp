// Mitos.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "xs_duo_basic.h"


int _tmain(int argc, _TCHAR* argv[])
{
	Mitos::XsDuoBasic pump;
	pump.init();

	pump.set_port(0, Mitos::valve_position::A);
	pump.set_port(1, Mitos::valve_position::C);

	pump.set_rate(0, 1000);
	pump.fill_syringe(0);

	pump.info();
	pump.run();

	return 0;
}

