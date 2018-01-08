
/* 
 * File:   Ship.cpp
 * Author: danny
 * 
 * Created on January 8, 2018, 3:40 PM
 */

#include "Ship.h"
#include "Vector2.h"

Ship::Ship(const hlt::Ship& halite_ship) : _halite_ship(halite_ship) {

}

Ship::~Ship() {
}

const hlt::Ship& Ship::halite_ship() {
    return _halite_ship;
}

void Ship::set_halite_ship(const hlt::Ship& halite_ship) {
    _halite_ship = halite_ship;
}
