#include "FileSystem.h"
#include <shlwapi.h>
#include <pathcch.h>
#include <filesystem>


bool FileSystem::Open() {

	if (!FileExists()) {
		//log : tried opening a non existing file
		return false;
	}
	std::filesystem::path file(GetAbsolutePath());
	DWORD accessMode = NULL;
	DWORD sharingMode = FILE_SHARE_READ;
	DWORD creationFlag = OPEN_EXISTING;
	DWORD attribute = FILE_ATTRIBUTE_NORMAL;

	if (this->fileMode == OpenMode::MODE_READ)
		accessMode = GENERIC_READ;
	if (this->fileMode == OpenMode::MODE_WRITE)
		accessMode = GENERIC_WRITE;
	if (this->fileMode == OpenMode::MODE_READWRITE)
		accessMode = GENERIC_READ | GENERIC_WRITE;

	HANDLE ret = CreateFileW(file.c_str(), accessMode, sharingMode, NULL, creationFlag, attribute, NULL);
	if (ret == INVALID_HANDLE_VALUE) {
		//this shouldnt be happening
		//log the path and folder
		this->lastState = FileState::STATE_INVALID;
		this->fileHandle = FILE_HANDLE_INVALID;
		return false;
	}

	//file_open_success
	this->fileHandle = (unsigned long)ret;
	this->lastState = FileState::STATE_OPENING;
	return true;
}

bool FileSystem::Close() {

	if (this->fileHandle == FILE_HANDLE_INVALID) {
		//log : tried closing non existing handle
		return false;
	}
	if (!CloseHandle((HANDLE)this->fileHandle)) {
		//log : error occured while trying to close handle
		return false;
	}
	//file_close_success
	this->lastState = FileState::STATE_CLOSING;
	this->fileHandle = FILE_HANDLE_INVALID;
	return true;
}

bool FileSystem::Create() {

	std::filesystem::path file(GetAbsolutePath());
	std::filesystem::path folderPath = file.parent_path(); // "C:\path1\blah.test"	-->   "C:\path1"

	//Check if folder already exists
	if (!std::filesystem::exists(folderPath)) {

		if (!(std::filesystem::is_directory(folderPath) && std::filesystem::create_directory(folderPath))) {
			//hitting here means something gone wrong
			//either folder path is invalid or CreateDirectory Failed
			//log : GetLastError()
			this->lastState = FileState::STATE_INVALID;
			this->fileHandle = FILE_HANDLE_INVALID;
			return false;
		}

	}
	//now we attempt to create an empty file

	DWORD accessMode = GENERIC_WRITE; //attempt to write
	DWORD sharingMode = 0; //deny file access to any other process for now
	DWORD creationFlag = CREATE_ALWAYS;//we are creating a new file. override if exists
	DWORD attribute = FILE_ATTRIBUTE_NORMAL;
	HANDLE ret = CreateFileW(file.c_str(), accessMode, sharingMode, NULL, creationFlag, attribute, NULL);

	if (ret == INVALID_HANDLE_VALUE) {
		//this shouldnt be happening
		//log the path and folder
		this->lastState = FileState::STATE_INVALID;
		this->fileHandle = FILE_HANDLE_INVALID;
		return false;
	}

	//file_creation_success
	this->fileHandle = (unsigned long)ret;
	this->lastState = FileState::STATE_CREATING;
	//CloseHandle(ret);
	return true;
}

bool FileSystem::Rename(const wchar_t* new_name) {

	//while renaming the current file handle will need an update
	Close();

	if (!FileExists()) {
		//log : tried renaming a non existing file
		return false;
	}

	std::wstring oldPath = GetAbsolutePath();
	std::wstring newPath = std::filesystem::path(oldPath).replace_filename(new_name);

	//if the new file already exists then we will override it else _wrename fails
	if (std::filesystem::exists(newPath))
	{
		std::filesystem::remove(newPath);
		//log : deleted a file while renaming

	}

	if (_wrename(oldPath.c_str(), newPath.c_str()) != 0) {
		//log : error when trying to rename file
		this->lastState = FileState::STATE_INVALID;
		return false;
	}
	//file_rename_success
	this->filePath = newPath;
	this->lastState = FileState::STATE_RENAMING;
	Open();//re init the handle value
	return true;
}

