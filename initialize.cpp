//
//  initialize.cpp
//  ConnectFour
//
//  Created by mandan sharma on 5/20/16.
//  Copyright © 2016 Mandan Sharma. All rights reserved.
//

#include "connectfour.hpp"






bool initialize::initializethegamewithoutarray(gameinstance* array) {
    std::cout<<"Press enter to clear buffer(Clear buffer)\n";
    std::cin.ignore();
    std::cout<<"\nL      To load game from a previously saved file\nD      To play with default\nN      To play the new game with custom settings\nQ      To quit the game\nEnter the command: ";
    char command;
    std::cin.get(command);
    return initializethegamewc(array,command,true);
}



bool initialize::initializethegame(gameinstance* array){
    std::cout<<"Press enter to clear buffer(Clear buffer)\n";
    std::cin.ignore();
    std::cout<<"Enter the command:\nR      To replay the game\nL      To load game from a previously saved file\nD      To play with default settings\nN      To play the new game with custom settings\nQ      To quit the game\nE      To escape the load game menu\n";
    char command;
    std::cin.get(command);
    if (command=='r' || command=='R') {
        return resettheboard(array);
    }
    else if (command=='e' ||command=='E'){
        return true;
    }
    else{
        return initializethegamewc(array,command,false);
    }
}




bool initialize::initializethegamewc(gameinstance* array,char command, bool returnaddress){
    if (command=='l' ||command=='L') {
        return loadfromsavedfile(array, returnaddress);
    }
    else if (command=='d' ||command=='D'){
        return loadwithdefault(array,returnaddress);
    }
    else if (command=='q' ||command=='Q'){
        std::cout<<"Thanks for playing conncect"<<CONNECTTHESE<<" Game\n";
        exit(0);
    }
    else if (command=='n' ||command=='N'){
        return loadwithcustom(array, returnaddress);
    }
    else{
        std::cout<<"Error: Please Try entering valid commands:- ";
        if (returnaddress) {
            return initializethegamewithoutarray(array);
        }
        else{
            return initializethegame(array);
        }
        
    }
}









bool initialize::loadfromsavedfile(gameinstance* array, bool returnaddress){
    std::fstream readingfilenames;
    readingfilenames.open(DEFAULTFILELOADER,std::ios::in);
    generaltools tools;
    unsigned int x=tools.numberoflinesinfile();
    x--;
    filenamehandler files[x];
    if (readingfilenames) {
        for (int i=0; i<x; i++) {
            readingfilenames.getline(files[i].file, MAXCHARACTEROFFILENAME , '\n');
        }
        readingfilenames.close();
        
        x=tools.deleterepeatedelement(files, x);
        
        tools.selectsort(files, x);
        

        
        if (x>=1) {
            
            
            for (int i=0; i<x;i++ ) {
                std::cout<<'\n'<<i+1<<": ";
                for (int o=0; files[i].file[o]!='\0'&&(o<MAXCHARACTEROFFILENAME && files[i].file[o]!='\n'); o++) {
                    std::cout<<files[i].file[o];
                }
            }
            
            
            std::cout<<"\nPress enter to clear buffer(Clear buffer)\n";
            std::cin.ignore();
            
            std::cout<<"Enter the corresponding number to the file you want to open: ";
            unsigned int elementselected;
            std::cin>>elementselected;
            while (elementselected<=0 || elementselected>x) {
                std::cout<<"Try entering valid numbers ≥ 1 and ≤ "<<x<<" : ";
                std::cin>>elementselected;
            }
            elementselected--;
            
            
            if(openthefile(array, files[elementselected].file)){
                std::fstream textfile;
                textfile.open(DEFAULTFILELOADER, std::ios::out);
                if (textfile) {
                    for (int i=0; i<x; i++) {
                        textfile<<files[i].file<<std::endl;
                    }
                    textfile.close();
                    return true;
                }
                else{
                    std::cout<<"Could not make an entry to text file";
                    return false;
                }
                
            }
            else{
                tools.remeovelement(files, elementselected, x);
                x--;
            }
            
            
            
            std::fstream textfile;
            textfile.open(DEFAULTFILELOADER, std::ios::out);
            if (textfile) {
                for (int i=0; i<x; i++) {
                    textfile<<files[i].file<<std::endl;
                }
                textfile.close();
            }
            else{
                std::cout<<"Could not make an entry to text file";
            }
            if(x>=1){
                std::cout<<"\nPlease choose the file again\n";
                return loadfromsavedfile(array, returnaddress);
            }
            else{
                std::cout<<"\nNo more files left to choose please try some other option\n";
                if (returnaddress) {
                    return initializethegamewithoutarray(array);
                }
                else{
                    return initializethegame(array);
                }
            }
            
        }
        else{
            std::cout<<"\nNo saved games found Please try something else.\n";
            if (returnaddress) {
                return initializethegamewithoutarray(array);
            }
            else{
                return initializethegame(array);
            }
        
        }
    }
    else{
        std::cout<<"\nNo saved games found Please try something else.\n";
        if (returnaddress) {
            return initializethegamewithoutarray(array);
        }
        else{
            return initializethegame(array);
        }
    }
}








bool initialize::openthefile(gameinstance* array,char* file){
    char filename[strlen(file)+strlen(TEXTFILEEXTENSION)+1];
    strcpy(filename, file);
    strcat(filename,TEXTFILEEXTENSION );
    std::fstream gamefile;
    gamefile.open(filename,std::ios::in);
    if (gamefile) {
        for (int i=0; i<(MAXNUMBEROFROWS*MAXNUMBEROFCOULMNS)+1; i++) {
            gamefile.read(reinterpret_cast<char*>(&array[i]),sizeof(gameinstance));
        }
        std::cout<<"The game \""<<filename<<"\" succesfully loaded\nNow runing the game\n";
        gamefile.close();
        return true;
    }
    else{
        std::cout<<"The file \""<<filename<<"\" has been renamed, removed,  deleted, or moved to the other folder so could not be opened Try again";
        return false;
    }
}







bool initialize::loadwithcustom(gameinstance* array, bool returnaddress){
    
    std::cout<<"Press enter to clear buffer(Clear buffer)\n";
    std::cin.ignore();

    std::cout<<"Initialize the total number of rows in board: ";
    int row=6,coulmn=7;
    std::cin>>row;
    while (row<CONNECTTHESE || row>MAXNUMBEROFROWS) {
        std::cout<<"Please enter valid inputs between " << CONNECTTHESE << " and "<<MAXNUMBEROFROWS<<" : ";
        std::cin>>row;
    }
    std::cout<<"Initialize the total number of coulmns in board: ";
    std::cin>>coulmn;
    while (coulmn<CONNECTTHESE || coulmn>MAXNUMBEROFCOULMNS) {
        std::cout<<"Please enter valid inputs between " << CONNECTTHESE << " and "<<MAXNUMBEROFCOULMNS<<" : ";
        std::cin>>coulmn;
    }
    
    std::cout<<"\nEnter y if you want to play in multiplayer mode: ";
    char command1,plyr1name[MAXCHARACTEROFPLAYERNAME],plyr2name[MAXCHARACTEROFPLAYERNAME];
    std::cin>>command1;
    bool playwithcomputer,whooseturn;
    if (command1=='y' || command1=='Y') {
        playwithcomputer=false;
        plyr1name[0]='\0';
        while (plyr1name[0]=='\0') {
            std::cout<<"\nEnter the player 1's name (less than"<<MAXCHARACTEROFPLAYERNAME-1<<"characters ): ";
            std::cin.getline(plyr1name, MAXCHARACTEROFPLAYERNAME,'\n');
        }
        
        
        std::cout<<"Press enter to clear buffer(Clear buffer)\n";
        std::cin.ignore();
        
        plyr2name[0]='\0';
        while (plyr2name[0]=='\0') {
            std::cout<<"\nEnter the player 2's name (less than"<<MAXCHARACTEROFPLAYERNAME-1<<"characters ): ";
            std::cin.getline(plyr2name, MAXCHARACTEROFPLAYERNAME,'\n');
        }
        
        std::cout<<"\nPress y if "<<plyr1name<< " wants to take first chance else press n: ";
        std::cin>>command1;
        if (command1=='y' || command1=='Y') {
            whooseturn=true;
        }
        else{
            whooseturn=false;
        }
        
    }
    else{
        playwithcomputer=true;
        plyr1name[0]='\0';
        while (plyr1name[0]=='\0') {
            std::cout<<"\nEnter the player 1's name (less than"<<MAXCHARACTEROFPLAYERNAME-1<<"characters ): ";
            std::cin.getline(plyr1name, MAXCHARACTEROFPLAYERNAME,'\n');
        }
        strcpy(plyr2name, "Computer");
        
        std::cout<<"\nPress y if you want to take first chance else press n: ";
        std::cin>>command1;
        if (command1=='y' || command1=='Y') {
            whooseturn=false;
        }
        else{
            whooseturn=true;
        }
        
    }
    
    return writedata(array, row, coulmn, plyr1name, plyr2name, playwithcomputer , 'h' ,whooseturn);
}



bool initialize::loadwithdefault(gameinstance* array,const bool returnaddress){
    bool flag=true;
    
    int row,coulmn;
    if (MAXNUMBEROFROWS>6) {
        row=6;
    }
    else{
        row=MAXNUMBEROFROWS;
    }
    
    
    if (MAXNUMBEROFCOULMNS>7) {
        coulmn=7;
    }
    else{
        coulmn=MAXNUMBEROFCOULMNS;
    }
    
    
    
    
    flag=writedata(array, row, coulmn, "Anonymus1", "Anonymus2", false, 'h',true);
    
    if(flag){
        return resettheboard(array);
    }
    else{
        std::cout<<"Error: Please Try loading again:- ";
        if (returnaddress) {
            return initializethegamewithoutarray(array);
        }
        else{
            return initializethegame(array);
        }
    }
}


bool initialize::writedata(gameinstance* array,unsigned int row,unsigned int coulmn,const char* player1name,const char* player2name , bool playwithcomputer,char dificultylevel,bool whooseturn){
    
    time_t current;
    time (&current);
    for (int instances=0;instances<(MAXNUMBEROFROWS*MAXNUMBEROFCOULMNS)+1; instances++) {
        array[instances].coulmn=coulmn;
        array[instances].row=row;
        strcpy(array[instances].playeronename,player1name);
        strcpy(array[instances].playertwoname,player2name);
        //array[instances].dificultylevel=dificultylevel;
        array[instances].playwithcomputer=playwithcomputer;
        array[instances].currentinstance=false;
        strcpy(array[instances].timeofmove,ctime(&current));

        if (whooseturn) {
            if(instances & 1){
                array[instances].whoseturn=false;
            }
            else{
                array[instances].whoseturn=true;
            }
        }
        else{
            if(instances & 1){
                array[instances].whoseturn=true;
            }
            else{
                array[instances].whoseturn=false;
            }
        }
        
    }
    
    
    return true;
}




bool initialize::resettheboard(gameinstance* array){
    for (int instance=0; instance<(MAXNUMBEROFROWS*MAXNUMBEROFCOULMNS)+1; instance++) {
        for (int i=0; i<array[instance].row; i++) {
            for (int j=0; j<array[instance].coulmn; j++) {
                array[instance].board[i][j]='\0';
            }
        }
    }
    return true;
}
















