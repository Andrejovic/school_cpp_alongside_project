#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <fstream> 
#include <algorithm>
#include <curl/curl.h>
class card_db
{
public:
	void add_to_collection(std::vector<std::string>& scanned_cards, std::string& path_to_data, std::string& currency);
private:
	std::string price_from_data(std::string& response_data, std::string& currency);
	std::string name_from_data(std::string& response_data);

	std::string price_db = "https://api.scryfall.com/cards/named?fuzzy="; //fuzzy enables ocr to not have to be precise
};