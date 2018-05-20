//
//  display.cpp
//  ConnectFour
//
//  Created by mandan sharma on 5/20/16.
//  Copyright © 2016 Mandan Sharma. All rights reserved.
//

#include "connectfour.hpp"




void display::diplayinstance(const gameinstance &gamedata){
    std::cout<<"\n\nLast changges made on this instance on: "<<gamedata.timeofmove<<"\n--------------------------------------------------------------------------";
    int noofdigits=0,coulmn=gamedata.coulmn;
    for (; coulmn==0; ) {
        coulmn/=10;
        noofdigits++;
    }
    if (!gamedata.whoseturn) {
        std::cout<<"\nPlayer 1's turn ( "<<gamedata.playeronename<<" ) \n";
    } else {
        std::cout<<"\nPlayer 2's turn ( "<<gamedata.playertwoname<<" ) \n";
    }
    
    
    linesaperatorline(noofdigits+3, gamedata);
    
    
    for (int i=0; i<gamedata.coulmn; i++) {
        std::cout<<std::setw(noofdigits+2)<<i<<" |";
    }
    linesaperatorline(noofdigits+3, gamedata);
    std::cout<<"--------------------------------------------------------------------------";
    linesaperatorline(noofdigits+3, gamedata);
    for (int r=0; r<gamedata.row; r++) {
        for (int c=0; c<gamedata.coulmn;c++ ) {
            if(gamedata.board[r][c]=='\0'){
                std::cout<<std::setw(noofdigits+2)<<0<<" |";
            }
            else if (gamedata.board[r][c]=='2'){
                std::cout<<std::setw(noofdigits+2)<<1<<" |";
            }
            else if (gamedata.board[r][c]=='1'){
                std::cout<<std::setw(noofdigits+2)<<2<<" |";
            }
            else{
                std::cout<<" ERROR |";
            }
        }
        linesaperatorline(noofdigits+3, gamedata);
    }

}






void display::linesaperatorline(const unsigned int spaces,const gameinstance &gamedata){
    std::cout<<"\n";
    for (int j=0; j<gamedata.coulmn; j++) {
        for (int i=0; i<spaces; i++) {
            std::cout<<" ";
        }
        std::cout<<"|";
    }
    std::cout<<"\n";
}








