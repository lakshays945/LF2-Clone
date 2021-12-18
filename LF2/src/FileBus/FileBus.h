#pragma once
#include <string>

#define MAX_FILE_SYSTEM_BUFFER 0x100
#define FILE_HANDLE_INVALID -1
#define FILE_SIZE_INVALID -1

class FileBus
{
public:
	enum class OpenMode {
		MODE_INVALID,
		MODE_READ,
		MODE_WRITE,
		MODE_READWRITE,
	};

	enum class FileState {
		STATE_INVALID,
		STATE_IDLE,
		STATE_OPENING,
		STATE_MISSING,
		STATE_CREATING,
		STATE_CLOSING,
		STATE_READING,
		STATE_WRITING,
		STATE_DELETING,
		STATE_RENAMING,
	};

	enum class FileProperty {
		PROPERTY_FILE_NAME,
		PROPERTY_FILE_EXTENSION,
		PROPERTY_FILE_FOLDER_PATH,
		PROPERTY_FILE_FOLDER_NAME,
		PROPERTY_FILE_FULL_PATH,
		PROPERTY_FILE_RELATIVE_PATH,
	};
	

	//constructors
	FileBus();
	FileBus(std::wstring path, OpenMode mode = OpenMode::MODE_READ);
	FileBus(const wchar_t* path_str, OpenMode mode = OpenMode::MODE_READ);

	//returns true if file is opened for operations
	bool Open();
	//returns true if a new empty file is successfully created
	bool Create();
	//returns true if all file operations are successfully closed
	bool Close();
	//returns true if the file exists on disk
	bool FileExists();
	//returns true if file on disk was successfully deleted
	bool DeleteExisting();
	//returns properties of filePath
	std::wstring GetProperties(FileProperty property);
	//returns true if successfully wrote data to opened file
	bool WriteData(size_t size, void* buffer);
	//returns true if successfully read data from opened file
	bool ReadData(size_t size,void* buffer);
	//returns true if current file was successfully renamed
	bool Rename(const wchar_t* new_name);
	bool SetPosition(unsigned long offset);
	//returns the size of the target file if present
	size_t GetSize();
	//changes the size of a regular file by truncation or zero-fill if present
	void ChangeSize(size_t new_size);

private:
	//Todo : Get rid of HANDLE based system as it is Windows-only
	unsigned long fileHandle;
	//what mode user is trying to access the file
	OpenMode fileMode;
	//last file operation performed
	FileState lastState;
	//path to the file (can be absolute/relative)
	std::wstring filePath;

	//returns if filePath is a absolute path
	bool PathIsAbsolute();
	//returns absolute path representation
	std::wstring GetAbsolutePath();
};