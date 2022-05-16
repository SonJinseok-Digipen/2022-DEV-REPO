/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Logger.cpp
Project: CS230
Author:Jinseok Son
Creation date:
-----------------------------------------------------------------*/
#include <iostream>    // cout.rdbuf
#include "Logger.h"

CS230::Logger::Logger(Severity severity, bool useConsole) : outStream("Trace.log"), minLevel(severity),startTime(std::chrono::system_clock::now())
{
	if (useConsole == true)
	{
		outStream.set_rdbuf(std::cout.rdbuf());
	}
}

CS230::Logger::~Logger()
{
	outStream.flush();
	outStream.close();
}

void CS230::Logger::Log(Severity severity, std::string message)
{
	if (severity >= minLevel && severity<=Severity::Error)
	{
		switch (severity)
		{
		case Severity::Verbose:
			outStream.precision(4);
			outStream << '[' << std::fixed << GetSecondsSinceStart() << "]\t";
			outStream << "Verb " << "\t" << message << '\n';
			break;
		case Severity::Error:
			outStream.precision(4);
			outStream << '[' << std::fixed << GetSecondsSinceStart() << "]\t";
			outStream << "Error" << "\t" << message << '\n';
			break;
		case Severity::Debug:
			outStream.precision(4);
			outStream << '[' << std::fixed << GetSecondsSinceStart() << "]\t";
			outStream << "Debug" << "\t" << message << '\n';
			break;
		case Severity::Event:
			outStream.precision(4);
			outStream << '[' << std::fixed << GetSecondsSinceStart() << "]\t";
			outStream << "Event" << "\t" << message << '\n';
			break;
		}
	}

}

double CS230::Logger::GetSecondsSinceStart()
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	double timer = std::chrono::duration<double>(now - startTime).count();
	return timer;
}
