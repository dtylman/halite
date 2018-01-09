/* 
 * File:   Dodger.h
 * Author: danny
 *
 * Created on January 8, 2018, 3:32 PM
 */

#ifndef DODGER_H
#define DODGER_H

#include "Pilot.h"


class Dodger : public Pilot {
public:
    Dodger(const hlt::Ship& hltShip);
    virtual ~Dodger();
    void play(const hlt::Map& map, hlt::Moves& moves) override;

private:

};

#endif /* DODGER_H */

