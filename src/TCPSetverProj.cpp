//============================================================================
// Name        : TCPSetverProj.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "TCPServer.h"
#include <iostream>
#include <unistd.h>

//Аргументы коандной строки
class Opts{
private:
	std::string logPath = "/var/log/vcalc.log"; //Путь к файлу с логами
	std::string confPath = "/etc/vcalc.conf"; //Путь к фа
	int port = 33333; //Номер порта
	void usage(const char* progName); //Вывод подсказки

public:
	Opts(int argc, char **argv);
	std::string getLogPath() { return logPath; }
	std::string getConPath() { return confPath; }
	int getPort() { return port; }
};

//Основная программа сервера. Точка входа в программу
int main(int argc, char **argv)
{
    Opts op(argc, argv);

    //Заменить на передачу параментов из командной строки
    TCPServer server = TCPServer(op.getPort(),op.getLogPath(), op.getConPath());

    server.startServer();

   do
    {
      server.handle();
    }
   while(true);

   server.closeServer();

   return 0;
}


Opts::Opts(int argc, char **argv)
{
	int opt;

	//p - порт
	//l - файл логов
	//c - файл бд
	//h - справка
	while((opt = getopt(argc, argv, "p:l:c:h")) != -1)
	{
		switch(opt)
		{
			case 'p':
				port = strtol(optarg, nullptr, 10);
				break;

			case 'l':
				logPath = optarg;
				break;

			case 'c':
				confPath = optarg;
				break;

			case 'h':
			case '?':
			case ':':
				usage(argv[0]);
		}
	}
}

void Opts::usage(const char* progName)
{
	std::cout<<"Usage: "<<progName<<" [-p port] [-l log file path] [-c data base file path] [-h help] \n";
	exit(0);
}

