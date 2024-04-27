
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
    scanned_cards = cam.start_scanning("card_names_only.txt");
    card_db collection;
    collection.add_to_collection(scanned_cards,"card_prices.txt");

    //different for Linux and Windows
    system("start card_prices.txt");
    return 0;
}
