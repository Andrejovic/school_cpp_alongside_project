#include "card_db.h"

using namespace std;

size_t write_data(void* contents, size_t size, size_t nmemb, std::string* data) {
	size_t realsize = size * nmemb;
	data->append((char*)contents, realsize);
	return realsize;
}

void card_db::add_to_collection(vector<string> scanned_cards) {
	ofstream price_data("price_data.txt");
	CURL* curl;
	CURLcode response;
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init;
	string price_db = "https://api.scryfall.com/cards/named?fuzzy=";
	if (!curl) {
		cout << "Curl init failed, check your connection, your scanned cards will be dumped into a file for later use" << endl;
		for (string card : scanned_cards) {
			price_data << card << endl;
		}
		exit(-1);
	}
	struct curl_slist* headers = NULL;
	headers = curl_slist_append(headers, "Accept: application/json");
	for (string card : scanned_cards) {
		curl_easy_setopt(curl, CURLOPT_URL, price_db + card);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		string response_data;
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);
		response = curl_easy_perform(curl);
		if (response != CURLE_OK) {
			std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(response) << std::endl;
		}
		string price = price_from_data(response_data);
	}
	curl_slist_free_all(headers);
	curl_easy_cleanup(curl);
	curl_global_cleanup();
}

string card_db::price_from_data(string& response_data) {
	size_t prices_start = response_data.find("\"prices\":");
	if (prices_start == string::npos) {
		return "NULL";
	}
	size_t prices_end = response_data.find("}", prices_start);
	string prices_data_part = response_data.substr(prices_start, prices_end - prices_start + 1);
	//TODO
}

