#include "card_db.h"

using namespace std;

//function for curl call
size_t write_data(void* contents, size_t size, size_t nmemb, std::string* data) {
	size_t realsize = size * nmemb;
	data->append((char*)contents, realsize);
	return realsize;
}

//put a card name to lowercase
void string_tolower(string& s) {
	for (char& c : s)
		c = tolower(c);
}

//method to add all cards to a file with prices
void card_db::add_to_collection(vector<string>& scanned_cards, string& path_to_data, string& currency) {
	string price;
	string name;
	string price_db_call;
	ofstream price_data(path_to_data, ios::app);
	CURL* curl = curl_easy_init();
	CURLcode response;
	float price_total = 0.0;
	curl_global_init(CURL_GLOBAL_ALL);
	if (!curl) {
		cout << "Curl init failed, check your connection, your scanned cards will be dumped into a file, without prices for later use" << endl;
		for (string card : scanned_cards) {
			price_data << card << endl;
		}
		exit(-1);
	}
	struct curl_slist* headers = NULL;
	headers = curl_slist_append(headers, "Accept: application/json");
	for (string card : scanned_cards) {

		string_tolower(card);
		size_t pos = 0;
		while ((pos = card.find(' ', pos)) != string::npos) {
			card.replace(pos, 1, "%20");
		}

		price_db_call = this->price_db + card;
		const char* url = (price_db_call).c_str();
		
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		string response_data;
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);
		response = curl_easy_perform(curl);
		if (response != CURLE_OK) {
			std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(response) << std::endl;
		}
		price = price_from_data(response_data, currency);
		name = name_from_data(response_data);
		if (price != "NULL")
			price_total += stof(price);
		price_data << name << ": " << price << endl;
		
	}
	curl_slist_free_all(headers);


	curl_easy_cleanup(curl);
	curl_global_cleanup();
	price_data << "------------------------------------------" << endl;
	price_data << "Total: " << price_total << " " << currency << endl;
	price_data << "------------------------------------------" << endl;
	price_data.close();
}

string find_given_price(string prices_data_part, string currency) {
	size_t price_start = prices_data_part.find(currency);
	size_t price_end = prices_data_part.find(",", price_start);

	string price = prices_data_part.substr(price_start + currency.length() + 1, price_end - price_start - (currency.length() + 2));
	return price;
}

string card_db::price_from_data(string& response_data, string& currency) {
	size_t prices_start = response_data.find("\"prices\":");
	if (prices_start == string::npos) {
		return "NULL";
	}
	size_t prices_end = response_data.find("}", prices_start);
	string prices_data_part = response_data.substr(prices_start, prices_end - prices_start + 1);
	if (currency == "eur" || currency == "usd") {
		string prices = find_given_price(prices_data_part, "\"" + currency + "\":");
		return (prices + " " + currency);
	}
	return "use eur or usd";
}

string card_db::name_from_data(string& response_data) {
	size_t name_start = response_data.find("\"name\":");
	if (name_start == string::npos) {
		return "NULL";
	}
	size_t name_end = response_data.find("\"", name_start + 8);
	string name = response_data.substr(name_start + 8, name_end - name_start - 8);
	return name;
}