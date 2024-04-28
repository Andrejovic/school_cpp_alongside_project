#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <regex>
struct config_reader
{
public:
	config_reader(std::string path_to_config);
	std::string path_to_card_names_only;
	std::string path_to_card_prices;
	std::string	currency;
	std::string mode;
	std::string folder_of_images;
private:
	std::string trim(const std::string line);
	const int number_of_config_lines = 5;
};

