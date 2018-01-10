/* 
 * File:   Kof.h
 * Author: danny
 *
 * Created on January 8, 2018, 4:37 PM
 */

#ifndef KOF_H
#define KOF_H

#include "Pilot.h"


class Kof : public Pilot {
public:
    Kof(const hlt::Ship& hltShip);    
    virtual ~Kof();
    void play(const hlt::Map& map, hlt::Moves& moves) override;
    bool can_play(const hlt::Map& map) override;    
    int target_entity_id() const override;

private:

};

#endif /* KOF_H */

