/* 
 * File:   Dodger.cpp
 * Author: danny
 * 
 * Created on January 8, 2018, 3:32 PM
 */

#include "Dodger.h"

Dodger::Dodger(const hlt::Ship& hltShip) : Pilot(hltShip){

}

Dodger::~Dodger() {
}

void Dodger::play(const hlt::Map& map, hlt::Moves& moves) {
    
}

bool Dodger::can_play(const hlt::Map& map) {
    return false;
}


bool Dodger::has_target() const {
    return false;
}
