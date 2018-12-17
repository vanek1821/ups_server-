//
//  GameManager.hpp
//  server
//
//  Created by Jakub  Vaněk on 22/11/2018.
//  Copyright © 2018 Jakub  Vaněk. All rights reserved.
//

#ifndef GameManager_hpp
#define GameManager_hpp

#include <stdio.h>
#include <iostream>
#include <map>
#include "Client.hpp"
#include "Match.hpp"
#include "Color.hpp"

using namespace std;

class GameManager{
public:
    static void addToClientMap(Client* client);
    static void connectClient(string name, int socket);
    static int createMatch(int clientID);
    static int joinMatch(string matchS, int clientID);
    static void initGame(int matchID);
    static string findMatches();
    static Client* findClient(int clientID);
    static Match* findMatch(int matchID);
private:
    
    static map<int, Client*> clientMap;
    static map<int, Match*> matchMap;
};

#endif /* GameManager_hpp */
