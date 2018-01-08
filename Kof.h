/* 
 * File:   Kof.h
 * Author: danny
 *
 * Created on January 8, 2018, 4:37 PM
 */

#ifndef KOF_H
#define KOF_H

#include "Ship.h"


class Kof : public Ship {
public:
    Kof(const hlt::Ship& hltShip);    
    virtual ~Kof();
    void play(const hlt::Map& map, hlt::Moves& moves) override;

private:

};

#endif /* KOF_H */

