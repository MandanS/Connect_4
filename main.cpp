//
//  main.cpp
//  ConnectFour
//
//  Created by mandan sharma on 5/20/16.
//  Copyright © 2016 Mandan Sharma. All rights reserved.
//

#include "connectfour.hpp"

int main() {
    
    std::cout<<"Welcome to conncect"<<CONNECTTHESE<<" Game\n";
    gameplay p;
    char command;
    do {
        p.playthegame();
        std::cout<<"Press enter to clear buffer(Clear buffer)\n";
        std::cin.ignore();
        std::cout<<"\nDo you want to run the game again?\nY      for yes\nAnything Else    to quit the game\n";
        std::cin.get(command);
    } while (command=='y'||command=='Y');
    
    std::cout<<"Thanks for playing conncect"<<CONNECTTHESE<<" Game\n";
    return 0;
}
