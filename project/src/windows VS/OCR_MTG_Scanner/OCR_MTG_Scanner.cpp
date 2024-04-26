
#include "camera.h"
#include "card_db.h"


int main()
{
    //comparing to a set database

    //pressing chars for different things?
    //Space - scan
    //Esc - exit

    camera cam;
    std::vector<std::string> scanned_cards;
    scanned_cards = cam.start_scanning("test.txt");
    card_db collection;
    collection.add_to_collection(scanned_cards);
    return 0;
}
