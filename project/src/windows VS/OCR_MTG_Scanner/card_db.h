#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <time.h>
#include <fstream>
#include <curl/curl.h>
class card_db
{
public:
	void add_to_collection(std::vector<std::string>);
private:
	std::string price_from_data(std::string& response_data);
};

