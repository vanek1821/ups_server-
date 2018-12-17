//
//  MessageManager.cpp
//  server
//
//  Created by Jakub  Vaněk on 22/11/2018.
//  Copyright © 2018 Jakub  Vaněk. All rights reserved.
//

#include "MessageManager.hpp"


using namespace std;

void MessageManager::resolveMessage(string msg, int socket){
    char delimeter = ';';
    
    size_t i = msg.find(delimeter); // nalezeni pozice delimitru
    string tok = msg.substr(0, i); // vyparsovani casti stringu do ;
    msg = msg.substr(i+1); // zbytek zpravy
    
    if(strcmp(tok.c_str(), "CONNECT") == 0){
        i = msg.find(delimeter);
        tok = msg.substr(0, i);
        msg = msg.substr(i+1);
        
        if(strcmp(tok.c_str(), "OK") == 0){
            i = msg.find(delimeter);
            tok = msg.substr(0, i);
            GameManager::connectClient(tok, socket);
            msg = "CONNECT;OK;";
            MessageManager::sendMessage(msg, socket);
        }
        else if(strcmp(tok.c_str(), "FAIL") == 0){
            cout << "Připojení hráce se nezdařilo" << endl;
            close(socket);
        }
    }
    
    else if(strcmp(tok.c_str(), "CREATE_MATCH") == 0){
        
        int result = GameManager::createMatch(socket);
        
        if(result == 1){
            msg = "CREATE_MATCH;OK;";
            MessageManager::sendMessage(msg, socket);
        }
        else if(result == -1){
            msg = "CREATE_MATCH;FAIL";
            MessageManager::sendMessage(msg, socket);
        }
    }
    
    else if(strcmp(tok.c_str(), "FIND_MATCH") == 0){
        
        msg = "FOUND_MATCH;";
        msg += GameManager::findMatches();
        MessageManager::sendMessage(msg, socket);
        
    }
    else if(strcmp(tok.c_str(), "JOIN_MATCH") == 0){
        i = msg.find(delimeter);
        tok = msg.substr(0,i);
        int result = GameManager::joinMatch(tok, socket);
        if(result > -1) {
            msg = "JOIN_MATCH;OK;";
            Match* match = GameManager::findMatch(result);
            sendMessage(msg, match->getClient1()->getSocketID());
            sendMessage(msg, match->getClient2()->getSocketID());
        }
        else{
            msg = "JOIN_MATCH;FAIL;";
            sendMessage(msg, socket);
        }
        
    }
}

void MessageManager::sendMessage(string msg, int socket){
    cout << "Odesilam zpravu: " << msg << endl;
    send(socket, msg.data(), msg.length(), 0);
}
/*
 else if(strcmp(tok, "JOIN_MATCH")==0){
 int matchID = atoi(strtok(NULL, ";"));
 
 m = findMatch(matchPool, matchID);
 
 if((m!=NULL)&&(m->ready==false)){
 strcpy(message, "JOIN_MATCH;OK;");
 
 m->c2 = findClient(clientPool, fd);
 tmp = m->c2;
 tmp->state = 3;
 tmp->inGame = true;
 send(fd, message, strlen(message)*sizeof(char),0);
 
 strcpy(message, "JOIN_MATCH;");
 tmp = m->c1;
 tmp->state = 3;
 tmp->inGame = true;
 printf("%d\n", tmp->socketID);
 send(tmp->socketID, message, strlen(message)*sizeof(char),0);
 
 m->ready = true;
 
 printf("jsem tady\n");
 }
 printf("něco se pojebalo");
 */
