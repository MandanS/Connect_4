//
//  gameplay.cpp
//  ConnectFour
//
//  Created by mandan sharma on 5/21/16.
//  Copyright © 2016 Mandan Sharma. All rights reserved.
//




#include "connectfour.hpp"





bool gameplay::playthegame(){
    
    initialize init;
    display disp;
    winanddrawconditions wd;
    generaltools tool;
    
    gameinstance game[(MAXNUMBEROFROWS*MAXNUMBEROFCOULMNS)+1];
    
    init.initializethegamewithoutarray(game);
    unsigned int instance=tool.instancefinder(game);
    int g=0;
    
    while (wd.windraw(game[instance-1])==0) {
        std::cout<<"\n Instance Number: "<<instance<<"\n";
        game[instance].currentinstance=true;
        unsigned int temp=instance;
        boardcopy(game[instance], game[instance-1]);
        disp.diplayinstance(game[instance]);
        if(game[instance].playwithcomputer){
            if (game[instance].whoseturn) {
                readandprocesscommand(game, instance);
            }
            else{
                g++;
                
                while (!processtheboard( game, g,instance)) {
                    g++;
                }
                
            }
            
        }
        else{
            readandprocesscommand(game, instance);
        }
        
        game[temp].currentinstance=false;
    }
    if (wd.windraw(game[instance-1])==2) {
        std::cout<<"Congratulations player 1 ( "<<game[instance].playeronename<<" ) won the game! ";
    } else if(wd.windraw(game[instance-1])==1){
        std::cout<<"Congratulations player 2 ( "<<game[instance].playertwoname<<" ) won the game! ";
    }
    else{
        std::cout<<"Well played Game Draw";
    }
    
    
    return true;
}






bool gameplay::readandprocesscommand(gameinstance* gamed,unsigned int &instance){
    std::cout<<"Press enter to clear buffer(Clear buffer) ";
    std::cin.ignore();
    
    int noofdigits=0,coulmn=gamed[instance].coulmn;
    for (; coulmn!=0; ) {
        coulmn/=10;
        noofdigits++;
    }
    char command[noofdigits+1];
    
    std::cout<<"\nS      To save the game\nQ      To quit the game without saving it\nR      To reset the game\nE      To escape the game with saving it\nL      To load new game\n";
    if ((!gamed[instance].playwithcomputer && instance>0 )|| (gamed[instance].playwithcomputer && instance>1)) {
        std::cout<<"U      To undo the move\n";
    }
    std::cout<<"Enter the command: ";
    std::cin.getline(command,noofdigits+1,'\n');
    if ((command[0]=='s' || command[0]=='S') && command[1]=='\0') {
        savegame save;
        save.savegamenow(gamed);
        return true;
    }
    else if ((command[0]=='q' || command[0]=='Q') && command[1]=='\0'){
        std::cout<<"\nThanks for playing conncect "<<CONNECTTHESE<<" Game\n";
        exit(0);
    }
    else if ((command[0]=='r' || command[0]=='R') && command[1]=='\0'){
        initialize init;
        generaltools tool;
        init.initializethegame(gamed);
        instance=tool.instancefinder(gamed);
        return true;
    }
    else if ((command[0]=='l' || command[0]=='L') && command[1]=='\0'){
        initialize init;
        generaltools tool;
        init.initializethegamewithoutarray(gamed);
        instance=tool.instancefinder(gamed);
        return true;
    }
    else if ((command[0]=='e' || command[0]=='E') && command[1]=='\0'){
        savegame save;
        save.savegamenow(gamed);
        std::cout<<"\nThanks for playing conncect "<<CONNECTTHESE<<" Game\n";
        exit(0);
    }
    else if (((command[0]=='u' || command[0]=='U') && command[1]=='\0') && ((!gamed[instance].playwithcomputer && instance>0 )|| (gamed[instance].playwithcomputer && instance>1))){
        if (!gamed[instance].playwithcomputer && instance>0 ) {
            instance--;
        }
        if (gamed[instance].playwithcomputer && instance>1){
            instance-=2;
        }
        return true;
    }
    else if (isdigit(command[0])){
        unsigned int x=atoi(command);
        
        if(x<gamed[instance].coulmn){
            bool flag= processtheboard(gamed, x, instance);
            if (flag) instance++;
            return flag;
        }
        else{
            std::cout<<"Invalid command please try again\n";
            return readandprocesscommand(gamed, instance);
        }
    }
    else{
        std::cout<<"Invalid command please try again\n";
        return readandprocesscommand(gamed, instance);
    }
}



bool gameplay::processtheboard(gameinstance * gamed,const unsigned int x,unsigned int &instance){
    bool flag=true;
    if (gamed[instance].board[0][x]=='\0') {
        for (int i=1; i<gamed[instance].row; i++) {
            if(gamed[instance].board[i][x]!='\0'){
                if(gamed[instance].whoseturn){
                    gamed[instance].board[i-1][x]='1';
                    flag=false;
                    return true;
                    break;
                }
                else {
                    gamed[instance].board[i-1][x]='2';
                    flag=false;
                    return true;
                    break;
                }
            }
        }
        if (flag) {
            if(gamed[instance].whoseturn)
                gamed[instance].board[gamed[instance].row-1][x]='1';
            else gamed[instance].board[gamed[instance].row-1][x]='2';
            return true;
            
        }
    }
    else{
        std::cout<<"Invalid command please try again\n";
        return false;
    }
    return false;
}





void gameplay::boardcopy(gameinstance& instance1,const gameinstance &instance2){
    for (int i=0; i<instance1.row; i++) {
        for (int j=0; j<instance2.coulmn; j++) {
            instance1.board[i][j]=instance2.board[i][j];
        }
    }
}









