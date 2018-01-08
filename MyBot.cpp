#include "hlt/hlt.hpp"
#include "hlt/navigation.hpp"
#include "Ship.h"
#include "MyShips.h"

#define BOT_NAME "shablool"

int main() {
    const hlt::Metadata metadata = hlt::initialize(BOT_NAME);

    const hlt::PlayerId player_id = metadata.player_id;

    const hlt::Map& initial_map = metadata.initial_map;

    // We now have 1 full minute to analyze the initial map.
    std::ostringstream initial_map_intelligence;
    initial_map_intelligence
            << "width: " << initial_map.map_width
            << "; height: " << initial_map.map_height
            << "; players: " << initial_map.ship_map.size()
            << "; my ships: " << initial_map.ship_map.at(player_id).size()
            << "; planets: " << initial_map.planets.size();
    hlt::Log::log(initial_map_intelligence.str());
   
    hlt::Moves moves;
    MyShips ships(metadata);
    
    for (;;) {
        moves.clear();
        const hlt::Map map = hlt::in::get_map();        
        ships.populate(map);        
        ships.play(map, moves);        

        if (!hlt::out::send_moves(moves)) {
            hlt::Log::log("send_moves failed; exiting");
            break;
        }
    }
}
