// Mitos.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "xs_duo_basic.h"

static volatile bool g_exit = false;

static BOOL WINAPI console_ctrl_handler(DWORD dwCtrlType)
{
	g_exit = true;
	return TRUE;
}

int _tmain(int argc, _TCHAR* argv[])
{
	SetConsoleCtrlHandler(console_ctrl_handler, TRUE);

	Mitos::XsDuoBasic pump;
	pump.init();

	pump.set_port(0, Mitos::valve_position::A);
	pump.set_port(1, Mitos::valve_position::C);

	pump.set_rate(0, 2500);
	pump.fill_syringe(0);

	pump.prepare_pump();

	while (!g_exit){
		if (pump.run()){
			break;
		}
	}
	

	return 0;
}

