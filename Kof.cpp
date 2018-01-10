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

    move_to_dock(map, moves);
}

bool Kof::can_play(const hlt::Map& map) {
    return true;
}

bool Kof::has_target() const {
    return false;
}
