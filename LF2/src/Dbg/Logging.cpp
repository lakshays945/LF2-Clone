
#include "Logging.h"
#include "fmt/core.h"
#include "fmt/color.h"
#include <Windows.h>


//our main console window logger
DbgWindow* main_log = nullptr;

DbgWindow::DbgWindow(const std::string& name) {

	//DbgWindow();
	this->log_file = name;

	if (AttachConsole(-1)) {
		//printf("attaching to parent console...\n");
	}
	else {
		DWORD error = GetLastError();
		if (error = ERROR_ACCESS_DENIED)
		{
			//printf("the calling process is already attached to a console");
			//use the existing console no need to retach
		}
		else if (error = ERROR_INVALID_HANDLE)
		{
			//printf("specified process does not have a console");
			AllocConsole();
		}

	}


	SetConsoleTitleA(name.c_str());
	valid = true;
	attachedToConsole = true;
	writeToFile = false;
}
DbgWindow::~DbgWindow() {
	valid = false;
	printf("\ndetaching console...\n");
	//FreeConsole();
}

void DbgWindow::log_message(LogLevel lvl, const char* msg) {

	if (!valid)
		return;
	fmt::color color;
	//fmt::color::steel_blue
	switch (lvl)
	{

	case LOG_INFO:
		color = fmt::color::blue;
		break;

	case LOG_SUCCESS:
		color = fmt::color::lime_green;
		break;

	case LOG_WARNING:
		color = fmt::color::yellow;
		break;

	case LOG_ERROR:
		color = fmt::color::red;
		break;

	case LOG_TRACE:
	case LOG_UNKNOWN:
	default:
		color = fmt::color::white;
	}
	//printerPrintText(msg, color);

	fmt::print(fg(color), msg);
	fmt::print("\n");
}
void DbgWindow::log_message(LogLevel lvl, const wchar_t* msg) {
	if (!valid)
		return;
	fmt::color color;
	//fmt::color::steel_blue
	switch (lvl)
	{

	case LOG_INFO:
		color = fmt::color::steel_blue;
		break;

	case LOG_SUCCESS:
		color = fmt::color::dark_green;
		break;

	case LOG_WARNING:
		color = fmt::color::yellow;
		break;

	case LOG_ERROR:
		color = fmt::color::red;
		break;

	case LOG_TRACE:
	case LOG_UNKNOWN:
	default:
		color = fmt::color::white;
	}
	//printerPrintText(msg, color);

	fmt::print(fg(color), msg);
	fmt::print(L"\n");
}

void DbgWindow::log_trace(const std::string& msg) {
	if (valid)
		this->log_message(LOG_TRACE, msg.c_str());
}
void DbgWindow::log_trace(const std::wstring& msg) {
	if (valid)
		this->log_message(LOG_TRACE, msg.c_str());
}


void DbgWindow::log_info(const std::string& msg) {
	if (valid)
		this->log_message(LOG_INFO, msg.c_str());
}
void DbgWindow::log_info(const std::wstring& msg) {
	if (valid)
		this->log_message(LOG_INFO, msg.c_str());
}

void DbgWindow::log_success(const std::string& msg) {
	if (valid)
		this->log_message(LOG_SUCCESS, msg.c_str());
}
void DbgWindow::log_success(const std::wstring& msg) {
	if (valid)
		this->log_message(LOG_SUCCESS, msg.c_str());
}

void DbgWindow::log_warning(const std::string& msg) {
	if (valid)
		this->log_message(LOG_WARNING, msg.c_str());
}
void DbgWindow::log_warning(const std::wstring& msg) {
	if (valid)
		this->log_message(LOG_WARNING, msg.c_str());
}

void DbgWindow::log_error(const std::string& msg) {
	if (valid)
		this->log_message(LOG_ERROR, msg.c_str());
}
void DbgWindow::log_error(const std::wstring& msg) {
	if (valid)
		this->log_message(LOG_ERROR, msg.c_str());
}
