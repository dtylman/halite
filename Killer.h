

/* 
 * File:   Killer.h
 * Author: danny
 *
 * Created on January 8, 2018, 3:32 PM
 */

#ifndef KILLER_H
#define KILLER_H

#include "Ship.h"


class Killer : public Ship {
public:
    Killer(const hlt::Ship& hltShip);
    virtual ~Killer();
private:

};

#endif /* KILLER_H */

