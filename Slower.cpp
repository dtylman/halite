/* 
 * File:   Slower.cpp
 * Author: danny
 * 
 * Created on January 4, 2018, 10:34 AM
 */

#include <unistd.h>
#include <stdlib.h>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include "Slower.h"
#include "log.hpp"

Slower::Slower() {
    pid_t parent = getppid();
    std::cout << exec("ps --ppid 1998 --no-headers -o pid") << std::endl;
}

Slower::~Slower() {
}

std::string Slower::exec(const std::string& cmd){    
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr){
            result += buffer.data();
        }
        std::cout<<result<< " hoho " <<std::endl;
        
    }
    return result;
}