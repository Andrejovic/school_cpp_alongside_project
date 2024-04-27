#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <time.h>
#include <fstream> 
#include <algorithm>
#include <curl/curl.h>
class card_db
{
public:
	void add_to_collection(std::vector<std::string>& scanned_cards, std::string& path_to_data);
private:
	std::string price_from_data(std::string& response_data);
	std::string name_from_data(std::string& response_data);

	std::string price_db = "https://api.scryfall.com/cards/named?fuzzy=";
};