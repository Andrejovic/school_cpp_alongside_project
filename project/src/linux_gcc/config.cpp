#include "config.h"

std::string config_reader::trim(const std::string str) {
	std::string trimmed = str;
	size_t start = trimmed.find_first_not_of(" \t\n\r");
	size_t end = trimmed.find_last_not_of(" \t\n\r");

	if (start == std::string::npos || end == std::string::npos) {
		return ""; // Empty string
	}

	return trimmed.substr(start, end - start + 1);
}

config_reader::config_reader(std::string path_to_config) {
	std::ifstream file(path_to_config);
	std::string line;
	std::string key, value;
	size_t pos = 0;

	//extremely non-versatile
	try {
		std::getline(file, line);
		this->path_to_card_names_only = trim(line.substr(line.find('=') + 1));
		std::getline(file, line);
		this->path_to_card_prices = trim(line.substr(line.find('=') + 1));
		std::getline(file, line);
		this->currency = trim(line.substr(line.find('=') + 1));
		std::getline(file, line);
		this->mode = trim(line.substr(line.find('=') + 1));
		std::getline(file, line);
		this->folder_of_images = trim(line.substr(line.find('=') + 1));
	}
	catch (...) {
		std::cout << "Error reading config file" << std::endl;
	}

	file.close();
}