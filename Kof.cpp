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
    hlt::Log::log("created kof pilot");

}

Kof::~Kof() {
}

void Kof::play(const hlt::Map& map, hlt::Moves& moves) {
    if (_ship.in_docking_process()) {
        return;
    }

    move_to_dock(map, moves);
}
