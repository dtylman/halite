/* 
 * File:   Kof.cpp
 * Author: danny
 * 
 * Created on January 8, 2018, 4:37 PM
 */

#include "Kof.h"
#include "hlt/navigation.hpp"
#include "log.hpp"

Kof::Kof(const hlt::Ship& hltShip) : Pilot(hltShip) {
    log("created");
}

Kof::~Kof() {
    log("destroyed");
}

void Kof::play(const hlt::Map& map, hlt::Moves& moves) {
    if (_ship.in_docking_process()) {
        return;
    }
        
//    const hlt::Ship* target = find_nearest_enemy(map);    
//    if (target!=NULL){        
//        move_towards(map,target->location,moves);
//        return;
//    } 

    move_to_dock(map, moves);
}

bool Kof::can_play(const hlt::Map& map) {
    return true;
}

int Kof::target_entity_id() const {
    return -1;
}
