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
        hlt::Planet planet;
        if (map.get_planet_by_id(_ship.docked_planet, planet)) {
            if (planet.is_full()) {
                moves.push_back(hlt::Move::undock(_ship.entity_id));
                return;
            }
        }
    }
    //try to dock nearest planet.
    if (move_to_dock(map, moves)) {
        return;
    }

    //fight enemy ship
    const hlt::Ship* enemy = find_nearest_enemy(map);
    if (enemy != NULL) {
        hlt::Location near_enemy_ship = _ship.location.get_closest_point(enemy->location, enemy->radius);
        move_to(map, near_enemy_ship, moves);
        return;
    }
    stop_moving(moves);
}

int Kof::target_entity_id() const {
    return -1;
}
