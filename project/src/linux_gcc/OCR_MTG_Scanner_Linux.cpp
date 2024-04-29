
#include "camera.h"
#include "card_db.h"
#include "config.h"


int main(int argc, char** argv)
{
    //put the card on a contrasting background (contrasting with black)
    //when scanning, limit the shadows of the camera to the card
    
    //Space - scan
    //Esc - exit
    camera cam;
    std::vector<std::string> scanned_cards;
    config_reader config("config.txt");
    mode_options mode;

    if (config.mode != "camera" && config.mode != "folder") {
        std::cout << "Error: Invalid mode" << std::endl;
        return -1;
    }
    else {
        mode = config.mode == "folder" ? Folder : Camera;
    }

    scanned_cards = cam.start_scanning(config.path_to_card_names_only, mode, config.folder_of_images);
    card_db collection;
    collection.add_to_collection(scanned_cards,config.path_to_card_prices, config.currency);

    //different for Linux and Windows
    system("xdg-open card_prices.txt");
    return 0;
}
