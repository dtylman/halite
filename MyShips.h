/* 
 * File:   MyShips.h
 * Author: danny
 *
 * Created on January 8, 2018, 4:11 PM
 */

#ifndef MYSHIPS_H
#define MYSHIPS_H

#include "Ship.h"
#include "hlt/hlt.hpp"

class MyShips {
public:
    MyShips(const hlt::Metadata& metadata);
    virtual ~MyShips();
    
    void populate(const hlt::Map& map);
    
    bool update_ship(const hlt::Ship& ship);
    void add_ship(const hlt::Ship& ship);
    
    void play(const hlt::Map& map, hlt::Moves& moves);
private:
    std::vector<Ship*> _ships;
    const hlt::Metadata _metadata;
};

#endif /* MYSHIPS_H */

