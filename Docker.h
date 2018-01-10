/* 
 * File:   Docker.h
 * Author: danny
 *
 * Created on January 8, 2018, 3:32 PM
 */

#ifndef DOCKER_H
#define DOCKER_H

#include "Pilot.h"


class Docker : public Pilot {
public:
    Docker(const hlt::Ship& ship, const hlt::Planet& target);
    virtual ~Docker();
    
    void play(const hlt::Map& map, hlt::Moves& moves) override;
    
    int target_entity_id() const override;

private:
    hlt::Planet _target;
};

#endif /* DOCKER_H */

