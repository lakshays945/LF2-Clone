#include "FileBus.h"
#include <filesystem>

FileBus::FileBus() {

	this->fileHandle = FILE_HANDLE_INVALID;
	this->fileMode = OpenMode::MODE_INVALID;
	this->lastState = FileState::STATE_INVALID;
}

FileBus::FileBus(std::wstring path, OpenMode mode) {

	FileBus::FileBus(path.c_str(), mode);
}

FileBus::FileBus(const wchar_t* path_str, OpenMode mode) {

	this->filePath.assign(path_str);
	this->fileHandle = FILE_HANDLE_INVALID;
	this->fileMode = mode;
	this->lastState = FileState::STATE_IDLE;
}

bool FileBus::PathIsAbsolute() {

	std::filesystem::path base(filePath);
	return base.is_absolute();

}

std::wstring FileBus::GetAbsolutePath() {

	if (PathIsAbsolute())
		return this->filePath;
	//else should be relative path to executeable?
	//log : current directory  = std::filesystem::current_directory()
	return std::filesystem::absolute(this->filePath).wstring();
}

bool FileBus::FileExists() {

	if (lastState == FileState::STATE_MISSING)
		return false;

	std::wstring path = GetAbsolutePath();
	if (!std::filesystem::is_regular_file(path)) {
		lastState = FileState::STATE_MISSING;
		return false;
	}
	lastState = FileState::STATE_IDLE;
	return true;
}

bool FileBus::DeleteExisting() {

	if (!FileExists()) {
		//log : tried deleting a non existing file
		return false;
	}
	lastState = FileState::STATE_DELETING;
	std::wstring path = GetAbsolutePath();
	//try delete
	if (std::filesystem::remove(path))
		return true;

	//log : GetLastError()
	return false;
}

std::wstring FileBus::GetProperties(FileProperty property) {

	if (!FileExists()) {
		//log : tried access a non existing file
		return std::wstring(L"error");
	}

	std::wstring ret;
	std::filesystem::path file(GetAbsolutePath());
	switch (property)
	{
	case FileProperty::PROPERTY_FILE_NAME:
		ret = file.stem().wstring();
		break;
	case FileProperty::PROPERTY_FILE_EXTENSION:
		ret = file.extension().wstring();
		break;
	case FileProperty::PROPERTY_FILE_FOLDER_PATH:
		ret = file.parent_path().wstring();
		break;
	case FileProperty::PROPERTY_FILE_FOLDER_NAME:
		ret = file.parent_path().filename().wstring();
		break;
	case FileProperty::PROPERTY_FILE_FULL_PATH:
		ret = file.wstring();
		break;
	case FileProperty::PROPERTY_FILE_RELATIVE_PATH:
		ret = file.relative_path().wstring(); //this might not always work
		break;
	}
	return ret;
}

size_t FileBus::GetSize() {

	if (!FileExists()){
		//log : tried calling GetSize() on nonexisting file
		return FILE_SIZE_INVALID;
	}
	return std::filesystem::file_size(GetAbsolutePath());
}

void FileBus::ChangeSize(size_t new_size) {

	if (!FileExists()){
		//log : tried calling ChangeSize() on nonexisting file
		return;
	}
	std::filesystem::resize_file(GetAbsolutePath(), new_size);
}
