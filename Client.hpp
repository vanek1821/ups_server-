//
//  Client.hpp
//  server
//
//  Created by Jakub  Vaněk on 22/11/2018.
//  Copyright © 2018 Jakub  Vaněk. All rights reserved.
//

#ifndef Client_hpp
#define Client_hpp

#include <stdio.h>
#include <iostream>
#include "Color.hpp"

using namespace std;

class Client{
public:
    Client(string name, int socketID);
    int getSocketID()   {return this->socketID;};
    string getName() {return this->name;};
    void setState(int state) {this->state = state;};
    void setColor(COLOR color) {this->color = color;};
    COLOR getColor() {return this->color;};
    
private:
    int socketID, state;
    string name;
    bool inGame;
    COLOR color;
};

#endif /* Client_hpp */
