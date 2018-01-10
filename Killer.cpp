/* 
 * File:   Killer.cpp
 * Author: danny
 * 
 * Created on January 8, 2018, 3:32 PM
 */

#include "Killer.h"
#include "navigation.hpp"
#include "log.hpp"

Killer::Killer(const hlt::Ship& ship) : Pilot(ship) {
    hlt::Log::log("created killer pilot");
}

Killer::~Killer() {
}

void Killer::play(const hlt::Map& map, hlt::Moves& moves) {
    if (_ship.in_docking_process()){
        return;
    }    
    const hlt::Ship* target = find_nearest_enemy(map);    
    if (target!=NULL){        
//        move_towards(map,target->location,moves);
//        return;
    } 
    
    move_to_dock(map,moves);
}

bool Killer::can_play(const hlt::Map& map) {
    return true;
}

bool Killer::has_target() const {
    return false;
}
