#include "Utils/Logger.h"
#include <chrono>
#include <format>
#include <asio/execution_context.hpp>
#include "../include/AuthServer.h"

#include <iostream>
#include <Utils/SetupParser.h>


int main()
{
	SetConsoleTitleW(L"Microvolts Auth Server");

	auto const time = std::chrono::current_zone()->to_local(std::chrono::system_clock::now());
	auto const time_s = std::format("{:%Y-%m-%d %X}", time);
	Utils::Logger::log("Auth server initialized on " + time_s, Utils::LogType::Info, "AuthServer");

	auto parsedServerInfo = Common::Utils::SetupParser::getInstance().getAuthSetup();
	Utils::Logger::log(std::format("Server Information: IP: {},  Port: {}",
		parsedServerInfo.ip, parsedServerInfo.port), Utils::LogType::Normal);

	asio::io_context io_context;
	Auth::AuthServer srv(io_context, parsedServerInfo.ip, parsedServerInfo.port);
	srv.asyncAccept();
	io_context.run();
}