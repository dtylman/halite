/* 
 * File:   Kof.cpp
 * Author: danny
 * 
 * Created on January 8, 2018, 4:37 PM
 */

#include "Kof.h"
#include "hlt/navigation.hpp"

Kof::Kof(const hlt::Ship& hltShip) : Ship(hltShip) {

}

Kof::~Kof() {
}

void Kof::play(const hlt::Map& map, hlt::Moves& moves) {
    if (_halite_ship.docking_status != hlt::ShipDockingStatus::Undocked) {
        return;
    }

    for (const hlt::Planet& planet : map.planets) {
        if (planet.owned) {
            continue;
        }

        if (_halite_ship.can_dock(planet)) {
            moves.push_back(hlt::Move::dock(_halite_ship.entity_id, planet.entity_id));
            return;
        }

        const hlt::possibly<hlt::Move> move =
                hlt::navigation::navigate_ship_to_dock(map, _halite_ship, planet, hlt::constants::MAX_SPEED);
        if (move.second) {
            moves.push_back(move.first);
            return;
        }
    }
}
