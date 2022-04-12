#pragma once
#include <string>
#include "fmt/xchar.h"

enum LogLevel {
	LOG_UNKNOWN = -1,
	LOG_TRACE,
	LOG_INFO,
	LOG_SUCCESS,
	LOG_WARNING,
	LOG_ERROR,
};


class DbgWindow {
	bool valid = false;
	bool attachedToConsole;
	bool writeToFile;
	std::string log_file;

	DbgWindow() = delete;


public:

	DbgWindow(const std::string& name);
	~DbgWindow();

	//output message to window
	void log_message(LogLevel lvl, const char* msg);
	//output message to window wide
	void log_message(LogLevel lvl, const wchar_t* msg);

	//literally spam
	void log_trace(const std::string& msg);
	//literally spam
	void log_trace(const std::wstring& msg);
	//literally spam
	template<typename...Args>
	void log_trace(const std::string& format, const Args &...args) { if (valid)log_trace(fmt::format(format, args...)); }
	//literally spam
	template<typename...Args>
	void log_trace(const std::wstring& format, const Args &...args) { if (valid)log_trace(fmt::format(format, args...)); }

	//some information that can be useful
	void log_info(const std::string& msg);
	//some information that can be useful
	void log_info(const std::wstring& msg);
	//some information that can be useful
	template<typename... Args>
	void log_info(const std::string& format, const Args &... args) { if (valid)log_info(fmt::format(format, args...)); }
	//some information that can be useful
	template<typename... Args>
	void log_info(const std::wstring& format, const Args &... args) { if (valid)log_info(fmt::format(format, args...)); }

	//reporting success of an operation
	void log_success(const std::string& msg);
	//reporting success of an operation
	void log_success(const std::wstring& msg);
	//reporting success of an operation
	template<typename... Args>
	void log_success(const std::string& format, const Args &... args) { if (valid)log_success(fmt::format(format, args...)); }
	//reporting success of an operation
	template<typename... Args>
	void log_success(const std::wstring& format, const Args &... args) { if (valid)log_success(fmt::format(format, args...)); }

	//we wont crash but should be looked into soon
	void log_warning(const std::string& msg);
	//we wont crash but should be looked into soon
	void log_warning(const std::wstring& msg);
	//we wont crash but should be looked into soon
	template<typename... Args>
	void log_warning(const std::string& format, const Args &... args) { if (valid)log_warning(fmt::format(format, args...)); }
	//we wont crash but should be looked into soon
	template<typename... Args>
	void log_warning(const std::wstring& format, const Args &... args) { if (valid)log_warning(fmt::format(format, args...)); }

	//yea this shouldnt be happening at all
	void log_error(const std::string& msg);
	//yea this shouldnt be happening at all
	void log_error(const std::wstring& msg);
	//yea this shouldnt be happening at all
	template<typename... Args>
	void log_error(const std::string& format, const Args &... args) { if (valid)log_error(fmt::format(format, args...)); }
	//yea this shouldnt be happening at all
	template<typename... Args>
	void log_error(const std::wstring& format, const Args &... args) { if (valid)log_error(fmt::format(format, args...)); }


};

//our main console window logger
extern DbgWindow* main_log;

#define DEBUG_TRACE(message,...) (main_log->log_trace(##message,__VA_ARGS__))
#define DEBUG_TRACE_FXN(message,...) (main_log->log_trace(__FUNCTION__ "(): "##message,__VA_ARGS__))
#define DEBUG_INFO(message,...) (main_log->log_info(##message,__VA_ARGS__))
#define DEBUG_INFO_FXN(message,...) (main_log->log_info(__FUNCTION__ "(): "##message,__VA_ARGS__))
#define DEBUG_SUCCESS(message,...) (main_log->log_success(##message,__VA_ARGS__))
#define DEBUG_SUCCESS_FXN(message,...) (main_log->log_success(__FUNCTION__ "(): "##message,__VA_ARGS__))
#define DEBUG_WARNING(message,...) (main_log->log_warning(##message,__VA_ARGS__))
#define DEBUG_WARNING_FXN(message,...) (main_log->log_warning(__FUNCTION__ "(): "##message,__VA_ARGS__))
#define DEBUG_ERROR(message,...) (main_log->log_error(##message,__VA_ARGS__))
#define DEBUG_ERROR_FXN(message,...) (main_log->log_error(__FUNCTION__ "(): "##message,__VA_ARGS__))

//@Lakshay ho gya FXN() use kro toh            FXN() : msg              karke print hoga
//mai chala