//
//  winanddrawconditions.cpp
//  ConnectFour
//
//  Created by mandan sharma on 5/21/16.
//  Copyright © 2016 Mandan Sharma. All rights reserved.
//



#include "connectfour.hpp"


// return 0 for playble game 1 if player 1 wins 2 if player 2 wins 3 if game draws


int winanddrawconditions::windraw(const gameinstance &gamed){
    
    int x,y,z,d;
    x=rowcheck(gamed);
    y=coulmncheck(gamed);
    z=leftdiagonalcheck(gamed);
    d=rightdiagonalcheck(gamed);
    if ((x==1 || y==1) ||  (z==1 ||d==1 )) {
        return 1;
    }
    else if ((x==2 || y==2) || ( z==2 ||d==2 )) {
        return 2;
    }
    
    else if((x==0 || y==0) ||  (z==0 ||d==0)){
        return 0;
    }
    
    else if((x==3 || y==3 )||  (z==3 ||d==3)){
        return 3;
    }
    else{
        std::cout<<"Algorithm error for int winanddrawconditions::windraw function\n";
        return -1;
    }
}





int winanddrawconditions::rowcheck( const gameinstance& gamed){
    bool flag,flagtwo=true , player1,player2;
    for (int i=0; i<gamed.row; i++) {
        for (int e=0; e<(gamed.coulmn - CONNECTTHESE)+1; e++) {
            flag=true;
            for (int c=0; c<CONNECTTHESE-1; c++) {
                if (gamed.board[i][e+c]!=gamed.board[i][e+c+1]){
                    flag=false;
                }
            }
            if (flag){
                if (gamed.board[i][e]=='1'){
                    return 1;
                }
                else if (gamed.board[i][e]=='2'){
                    return 2;
                }
                else if (gamed.board[i][e]=='\0'){
                    flagtwo=false;
                }
                else{
                    std::cout<<"Board Error board passed is not correct";
                }
            }
            else{
                player1=false;
                player2=false;
                for (int c=0; c<CONNECTTHESE; c++) {
                    if (gamed.board[i][e+c]=='1'){
                        player1=true;
                    }
                    else if (gamed.board[i][e+c]=='2') {
                        flagtwo=true;
                    }
                }
                if (!player1 || !player2){
                    flagtwo=false;
                }
            }
        }
    }
    if (flagtwo) {
        return 3;
    }
    else return 0;
}



int winanddrawconditions::coulmncheck( const gameinstance &gamed){
    bool flag,flagtwo=true , player1,player2;
    for (int i=0; i<gamed.coulmn; i++) {
        for (int e=0; e<(gamed.row - CONNECTTHESE)+1; e++) {
            flag=true;
            for (int c=0; c<CONNECTTHESE-1; c++) {
                if (gamed.board[e+c][i]!=gamed.board[e+c+1][i]){
                    flag=false;
                }
            }
            if (flag){
                if (gamed.board[e][i]=='1'){
                    return 1;
                }
                else if (gamed.board[e][i]=='2'){
                    return 2;
                }
                else if (gamed.board[e][i]=='\0'){
                    flagtwo=false;
                }
                else{
                    std::cout<<"Board Error board passed is not correct";
                }
            }
            else{
                player1=false;
                player2=false;
                for (int c=0; c<CONNECTTHESE; c++) {
                    if (gamed.board[e+c][i]=='1'){
                        player1=true;
                    }
                    else if (gamed.board[e+c][i]=='2') {
                        flagtwo=true;
                    }
                }
                if (!player1 || !player2){
                    flagtwo=false;
                }
            }
        }
    }
    if (flagtwo) {
        return 3;
    }
    else return 0;
}




int winanddrawconditions::leftdiagonalcheck(const  gameinstance &gamed){
     bool flag,draw=true , player1,player2;
    for (int c=0; c<(gamed.coulmn - CONNECTTHESE) +1 ; c++) {
        for (int r=0; r<(gamed.row - CONNECTTHESE)+1; r++) {
            {
                flag=true;
                for (int d=0; d<CONNECTTHESE-1; d++) {
                    if (gamed.board[r+d][c+d]!=gamed.board[r+d+1][c+d+1]){
                        flag=false;
                    }
                }
                if (flag){
                    if (gamed.board[r][c]=='1'){
                        return 1;
                    }
                    else if (gamed.board[r][c]=='2'){
                        return 2;
                    }
                    else if (gamed.board[r][c]=='\0'){
                        draw=false;
                    }
                    else{
                        std::cout<<"Board Error board passed is not correct";
                    }
                }
                else{
                    player1=false;
                    player2=false;
                    for (int d=0; d<CONNECTTHESE; d++) {
                        if (gamed.board[r+d][c+d]=='1'){
                            player1=true;
                        }
                        else if (gamed.board[r+d][c+d]=='2') {
                            draw=true;
                        }
                    }
                    if (!player1 || !player2){
                        draw=false;
                    }
                }
            }
        }
    }
    if (draw) {
        return 3;
    }
    else return 0;
}





int winanddrawconditions::rightdiagonalcheck(const  gameinstance &gamed){
    bool flag,draw=true , player1,player2;
    for (int c= CONNECTTHESE-1; c<gamed.coulmn ; c++) {
        for (int r=0; r<(gamed.row - CONNECTTHESE)+1; r++) {
            {
                flag=true;
                for (int d=0; d<CONNECTTHESE-1; d++) {
                    if (gamed.board[r-d][c-d]!=gamed.board[r-(d+1)][c-(d+1)]){
                        flag=false;
                    }
                }
                if (flag){
                    if (gamed.board[r][c]=='1'){
                        return 1;
                    }
                    else if (gamed.board[r][c]=='2'){
                        return 2;
                    }
                    else if (gamed.board[r][c]=='\0'){
                        draw=false;
                    }
                    else{
                        std::cout<<"Board Error board passed is not correct";
                    }
                }
                else{
                    player1=false;
                    player2=false;
                    for (int d=0; d<CONNECTTHESE; d++) {
                        if (gamed.board[r-d][c-d]=='1'){
                            player1=true;
                        }
                        else if (gamed.board[r+d][c+d]=='2') {
                            draw=true;
                        }
                    }
                    if (!player1 || !player2){
                        draw=false;
                    }
                }
            }
        }
    }
    if (draw) {
        return 3;
    }
    else return 0;
}






















