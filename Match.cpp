//
//  Match.cpp
//  server
//
//  Created by Jakub  Vaněk on 22/11/2018.
//  Copyright © 2018 Jakub  Vaněk. All rights reserved.
//

#include "Match.hpp"
#include "Client.hpp"

Match::Match(int matchID){
    this->ready = false;
    this->matchID = matchID;
    this->c1 = nullptr;
    this->c2 = nullptr;
    this->game = nullptr;
    
}
