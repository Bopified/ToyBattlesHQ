
#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <string>
#include <sstream>
#include <format>
#include <memory>
#include "../../include/Utils/Logger.h"
#include <Windows.h>

namespace Utils
{
    void Logger::enableAnsiEscapeCodes()
    {
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut == INVALID_HANDLE_VALUE) return;

        DWORD dwMode = 0;
        if (!GetConsoleMode(hOut, &dwMode)) return;
        SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }

    void Logger::printToConsole(const std::string& message, LogType type)
    {
        std::call_once(initFlag, enableAnsiEscapeCodes);

        if (m_loggingEnabled)
        {
            switch (type)
            {
            case LogType::Info:
                std::cout << LogColors::Info << "[Info] " << message << LogColors::Reset << "\n";
                break;
            case LogType::Error:
                std::cout << LogColors::Error << "[Error] " << message << LogColors::Reset << "\n";
                break;
            case LogType::Normal:
                std::cout << LogColors::Normal << message << LogColors::Reset << "\n";
                break;
            case LogType::Warning:
                std::cout << LogColors::Warning << "[Warning] " << message << LogColors::Reset << "\n";
                break;
            }
        }
    }

    void Logger::log(const std::string& message, LogType type, const std::string& functionName)
    {
        std::string logMessage = message;
        if (!functionName.empty())
        {
            logMessage = "[" + functionName + "] " + logMessage;
        }
        printToConsole(logMessage, type);
        newline();
    }

    std::string Logger::getCurrentDateTime()
    {
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);

        std::tm tm_time{};
        localtime_s(&tm_time, &now_c);
        std::stringstream ss;
        ss << std::put_time(&tm_time, "%Y-%m-%d %X");
        return ss.str();
    }

    std::string Logger::logTypeToString(LogType type)
    {
        switch (type) {
        case LogType::Info: return "Info";
        case LogType::Error: return "Error";
        case LogType::Normal: return "Normal";
        case LogType::Warning: return "Warning";
        }
        return "Unknown";
    }
}
