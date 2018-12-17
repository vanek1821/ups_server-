//
//  GameManager.cpp
//  server
//
//  Created by Jakub  Vaněk on 22/11/2018.
//  Copyright © 2018 Jakub  Vaněk. All rights reserved.
//

#include "GameManager.hpp"

map<int, Client*> GameManager::clientMap;
map<int, Match*> GameManager::matchMap;

void GameManager::connectClient(string name, int socket){
    Client* client = new Client(name, socket);
    addToClientMap(client);
    client->setState(1);
}

void GameManager::addToClientMap(Client* client){
    
    clientMap.insert(make_pair(client->getSocketID(), client));
    
    std::cout << "Klient " << client->getName() << " se socketem " << client->getSocketID() << " byl přidán do mapy." << endl;
}

int GameManager::createMatch(int clientID){
    map<int, Client*>::iterator it = clientMap.find(clientID);
    if(it != clientMap.end()){
        Client* client = it->second;
        
        cout << "Hráč " << client->getName() << " chce vytvořit hru." << endl;
        
        Match* match = new Match(client->getSocketID());
        
        cout << "Hra " << client->getSocketID() << " byla vytvořena" << endl;
        
        matchMap.insert(make_pair(client->getSocketID(), match));
        match->setClient1(client);
        client->setState(2);
        return 1;
    }
    else{
        return -1;
    }
}

string GameManager::findMatches(){
    string msg;
    for(map<int,Match*>::iterator it = matchMap.begin(); it != matchMap.end(); ++it) {
        if(it->second->isReady() == false){
            cout << "Hra s ID: "<< it->first << " nalezena" << endl;
            msg = msg + to_string(it->first);
            msg = msg + "-";
        }
    }
    msg = msg.substr(0, msg.length()-1); //odebrani posledni pomlcky
    cout << "Pridavam ke zprave: " << msg << endl;
    return msg;
}

int GameManager::joinMatch(string matchS, int clientID){
    Match* match = GameManager::findMatch(atoi(matchS.c_str()));
    if(match == NULL) return -1;
    Client* client = GameManager::findClient(clientID);
    if(match == NULL) return -1;
    match->setClient2(client);
    match->setReady(true);
    match->getClient1()->setState(3);
    match->getClient2()->setState(3);
    match->setGame(new Game());
    match->getClient1()->setColor(COLOR::WHITE);
    match->getClient2()->setColor(COLOR::BLACK);
    
    return match->getID();
}

Client* GameManager::findClient(int clientID){
    map<int, Client*>::iterator it = clientMap.find(clientID);
    if(it != clientMap.end()){
        Client* client = it->second;
        return client;
    }
    else{
        cout << "hráč s ID: " << clientID << " nenalezen.";
        return NULL;
    }
}

void GameManager::initGame(int matchID){
    Game* game = new Game();
    Match* match = findMatch(matchID);
    match->setGame(game);
}

Match* GameManager::findMatch(int matchID){
    map<int, Match*>::iterator it = matchMap.find(matchID);
    if(it != matchMap.end()){
        Match* match = it->second;
        return match;
    }
    else{
        cout << "Match s ID: " << matchID << " nenalezen.";
        return NULL;
    }
}
