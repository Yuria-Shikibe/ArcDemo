// ReSharper disable CppClangTidyModernizeUseNodiscard
#pragma once

#include <filesystem>
#include <fstream>

class File{
public:
	std::filesystem::directory_entry entry;

	explicit File(const std::filesystem::path& p) {
		entry = std::filesystem::directory_entry(p);
	}

	std::filesystem::directory_entry* raw(){
		return &entry;
	}

	std::string extension() const{
		return entry.path().extension().string();
	}

	std::string stem() const{
		return entry.path().stem().string();
	}

	std::string name() const{
		return entry.path().stem().string();
	}

	std::filesystem::path path() const{
		return entry.path();
	}

	bool exist() const{
		return entry.exists();
	}

	bool deleteFile() const{
		return exist() ? remove(entry) : false;
	}

	bool copy(const std::filesystem::path& dest) const{
		try{
			std::filesystem::copy(entry, dest);
			return true;
		} catch([[maybe_unused]] std::error_code& ignore){
			return false;
		}
	}

	bool copy(const File& dest) const{
		return copy(dest.path());
	}

	bool isDir() const{
		return is_directory(entry);
	}

	bool isRegular() const{
		return is_regular_file(entry);
	}

	bool createDir(const bool autoCreateParents = true) const{
		return  autoCreateParents ? create_directories(entry) : create_directory(entry);
	}

	File getParent() const{
		return File{ path().parent_path()};
	}

	bool createFile() const{
		if (exist())return false;

		std::ofstream ofStream(path());

		const bool valid = ofStream.is_open();

		ofStream.close();

		return valid;
	}

	void writeString(const std::string& data) const{
		if(std::ofstream ofStream(path()); ofStream.is_open()){
			ofStream << data;
			ofStream.close();
		}
	}

	std::string readString() const{
		if (std::ifstream file_stream(path()); file_stream.is_open()) {
			std::stringstream file_contents;
			std::string line;

			while (std::getline(file_stream, line)) {
				file_contents << line << "\n";
			}

			file_stream.close();
			return file_contents.str();
		}

		return "";
	}
};
