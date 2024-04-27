
#include "camera.h"
#include "card_db.h"


int main()
{
    //put the card on a contrasting background (contrasting with black)
    //when scanning, limit the shadows of the camera to the card
    
    //Space - scan
    //Esc - exit
    camera cam;
    std::vector<std::string> scanned_cards;
    std::string path_to_card_names_only = "card_names_only.txt";
	std::string path_to_card_prices = "card_prices.txt";
    scanned_cards = cam.start_scanning(path_to_card_names_only);
    card_db collection;
    collection.add_to_collection(scanned_cards,path_to_card_prices);

    //different for Linux and Windows
    system("start card_prices.txt");
    return 0;
}
