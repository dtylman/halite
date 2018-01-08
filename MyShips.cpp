/* 
 * File:   MyShips.cpp
 * Author: danny
 * 
 * Created on January 8, 2018, 4:11 PM
 */

#include "MyShips.h"
#include "Docker.h"
#include "Kof.h"

MyShips::MyShips(const hlt::Metadata& metadata) : _metadata(metadata) {

}

MyShips::~MyShips() {
}

void MyShips::populate(const hlt::Map& map) {
    for (const hlt::Ship& ship : map.ships.at(_metadata.player_id)) {
        if (!update_ship(ship)) {
            add_ship(ship);
        }
    }
}

bool MyShips::update_ship(const hlt::Ship& halite_ship) {
    for (auto s : _ships) {
        if (s->halite_ship().entity_id == halite_ship.entity_id) {
            s->set_halite_ship(halite_ship);
            return true;
        }
    }
    return false;
}

void MyShips::add_ship(const hlt::Ship& ship) {
    _ships.push_back(new Kof(ship));
}

void MyShips::play(const hlt::Map& map, hlt::Moves& moves) {
    for (auto s: _ships){
        s->play(map,moves);        
    }    
}
