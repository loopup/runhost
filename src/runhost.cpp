/*
 * runhost
 * Host application configured via command line to handle signals and return code to host.
 * https://github.com/loopup/runhost
 * 
 * Copyright 2019 LoopUp LLC. All rights reserved.
 *
 */

#include <signal.h>

#include <iostream>
#include <string>

#include <Windows.h>
#include <winsvc.h>


void SignalHandler(int signalId)
{
	using namespace std;

	cout << " - Signal [" << signalId << "]" << endl;
	exit(signalId);
}


BOOL WINAPI OnConsoleHandler(DWORD dwCtrlType)
{
	using namespace std;

	cout << " - OnConsoleHandler:Killed " << dwCtrlType << endl;
	exit(SIGTERM);
	return SIGTERM;
}


int main(int argc, char** argv)
{
	using namespace std;

	// The following should fire under unix/linux.
	signal(SIGABRT, SignalHandler);
	signal(SIGTERM, SignalHandler);
	signal(SIGBREAK, SignalHandler);
	signal(SIGABRT_COMPAT, SignalHandler);
	signal(SIGINT, SignalHandler);
	// Specifically for commanline applications; docker engine on windows should fire here.
	SetConsoleCtrlHandler(OnConsoleHandler, TRUE);

#ifdef _DEBUG
	cout << "argc: " << argc << endl;
	for (int i = 0; i < argc; i++)
	{
		cout << "[" << i << "] - " << argv[i] << endl;
	}
#endif

	char x{};

	do
	{
		cout << "Waiting for signal (or hit `q` to quit)..";
		x = getchar();
	} while (x != 'q');

	cout << endl
		 << "Bye, bye." << endl;

	return 0;
}

void ServiceControlShutdown(const char* arg_ServiceName)
{
	SC_HANDLE	  myService = NULL;
	SC_HANDLE	  mySCM = NULL;
	int			   rc = 0;
	SERVICE_STATUS myServiceStatus;

	mySCM = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
	if (mySCM != NULL)
	{
		//	Open the service to control..
		myService = OpenServiceA(mySCM, arg_ServiceName, SC_MANAGER_ALL_ACCESS);
		if (myService != NULL)
		{
			//	Send the service a shutdown event.
			if (ControlService(myService, SERVICE_CONTROL_STOP, &myServiceStatus))
			{
			}
			else
			{
				rc = GetLastError();
			}

			CloseServiceHandle(myService);
		}
		else
		{
			rc = GetLastError();
		}

		CloseServiceHandle(mySCM);
	}
}


void ServiceControlStart(const char* arg_ServiceName)
{
	SC_HANDLE myService = NULL;
	SC_HANDLE mySCM = NULL;
	int		  rc = 0;

	mySCM = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
	if (mySCM != NULL)
	{
		//	Open the service to control..
		myService = OpenServiceA(mySCM, arg_ServiceName, SC_MANAGER_ALL_ACCESS);
		if (myService != NULL)
		{
			//	Send the service a start event.
			if (StartService(myService, NULL, NULL))
			{
			}
			else
			{
				rc = GetLastError();
			}

			CloseServiceHandle(myService);
		}
		else
		{
			rc = GetLastError();
		}

		CloseServiceHandle(mySCM);
	}
}
