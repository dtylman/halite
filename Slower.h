/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Slower.h
 * Author: danny
 *
 * Created on January 4, 2018, 10:34 AM
 */

#ifndef SLOWER_H
#define SLOWER_H

#include <string>

class Slower {
public:
    Slower();    
    virtual ~Slower();
    static std::string exec(const std::string& cmd);
private:
    
};

#endif /* SLOWER_H */

