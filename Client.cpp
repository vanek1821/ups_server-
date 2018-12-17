//
//  Client.cpp
//  server
//
//  Created by Jakub  Vaněk on 22/11/2018.
//  Copyright © 2018 Jakub  Vaněk. All rights reserved.
//

#include "Client.hpp"

Client::Client(string name, int socketID){
    this->name = name;
    this->socketID = socketID;
    this->state = 0;
    this->inGame = false;
    
}
