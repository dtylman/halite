/* 
 * File:   Dodger.cpp
 * Author: danny
 * 
 * Created on January 8, 2018, 3:32 PM
 */

#include "Dodger.h"

Dodger::Dodger(const hlt::Ship& ship) : Pilot(ship){
    log("created dodger");
    _idle = false;
}

Dodger::~Dodger() {
    log("dodger died");
}

void Dodger::play(const hlt::Map& map, hlt::Moves& moves) {
    hlt::Location dodgepoint{1,1};
    if (!_ship.location.equals(dodgepoint)){
        move_to(map,dodgepoint,moves);
        return;
    }
    set_idle(moves,false);
}


int Dodger::target_entity_id() const {
    return -1;
}
