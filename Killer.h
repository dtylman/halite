

/* 
 * File:   Killer.h
 * Author: danny
 *
 * Created on January 8, 2018, 3:32 PM
 */

#ifndef KILLER_H
#define KILLER_H

#include "Pilot.h"


class Killer : public Pilot {
public:
    Killer(const hlt::Ship& ship, const hlt::Entity& target);
    virtual ~Killer();
    void play(const hlt::Map& map, hlt::Moves& moves) override;
    bool can_play(const hlt::Map& map) override;

    bool has_target() const override;

private:
    hlt::Entity _target;
};

#endif /* KILLER_H */

