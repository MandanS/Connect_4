//
//  savegame.cpp
//  ConnectFour
//
//  Created by mandan sharma on 5/21/16.
//  Copyright © 2016 Mandan Sharma. All rights reserved.
//


#include "connectfour.hpp"

// wiil write data upto (gamed[0].row*gamed[0].coulmn)th element

bool savegame::savegamenow(gameinstance* gamedata){
    std::cout<<"Press enter to clear buffer(Clear buffer)\n";
    std::cin.ignore();
    std::cout<<"Plese enter the file name to be saved (less than "<<MAXCHARACTEROFFILENAME-1<<" characters ): ";
    char filename[MAXCHARACTEROFFILENAME];
    std::cin.getline(filename, MAXCHARACTEROFFILENAME, '\n');
    return savinggame(filename,gamedata);
}





bool savegame::savinggame(const char file[],gameinstance* gamedata){
    std::fstream savedgame;
    savedgame.open(DEFAULTFILELOADER,std::ios::in);
    generaltools tools;
    unsigned int x=tools.numberoflinesinfile();
    filenamehandler files[x+1];
    if (savedgame) {
        for (int i=0; i<x-1; i++) {
            savedgame.getline(files[i].file, MAXCHARACTEROFFILENAME , '\n');
        }
        savedgame.close();
        if (tools.linearsearch(files, x,file)!=-1) {
            std::cout<<"One file already exists as this name \""<<files[tools.linearsearch(files, x,file)].file<<TEXTFILEEXTENSION<<"\"\nSo enter command to coninue\nY      to continue and overwrite the existing file\nN      To re-enter the file name\nQ      To exit the saving widget\n";
            char command;
            std::cin.get(command);
            if (command=='y'||command=='Y') {
                return finalstep(file, files, x+1, gamedata);
            }
            else if(command=='n'||command=='N'){
                return savegamenow(gamedata);
            }
            else if(command=='q'||command=='Q'){
                return false;
            }
            else{
                std::cout<<"Invalid command try again\n";
                return savinggame(file,gamedata);
            }
        }
        else{
            return finalstep(file, files, x+1, gamedata);
        }
    }
    else{
        return finalstep(file, files, x+1, gamedata);
    }
}




bool savegame::finalstep(const char file[],filenamehandler* array,unsigned int arraysize,gameinstance* gamedata){
    if (writeactualgame(file, gamedata)) {
        return entrytotextfile(file, array, arraysize);
    }
    else{
        return false;
    }
}



bool savegame::writeactualgame(const char* filename, gameinstance* gamed){
    std::fstream filetobewritten;
    char filenamen[strlen(filename)+strlen(TEXTFILEEXTENSION)+1];
    strcpy(filenamen,filename);
    strcat(filenamen, TEXTFILEEXTENSION);
    filetobewritten.open( filenamen ,std::ios::out|std::ios::binary);
    if (filetobewritten) {
        for (int i=0; i<(MAXNUMBEROFROWS*MAXNUMBEROFCOULMNS)+1; i++) {
            filetobewritten.write(reinterpret_cast<char *>(&gamed[i]),sizeof(gameinstance));
        }
        filetobewritten.close();
        return true;
    }
    else{
        std::cout<<"Could not write the game to file\n";
        return false;
    }
}




bool savegame::entrytotextfile(const char* file,filenamehandler* array, unsigned int arraysize){
    std::fstream textfile;
    textfile.open(DEFAULTFILELOADER, std::ios::out);
    strcpy(array[arraysize-1].file, file);
    generaltools tools;
    
    arraysize=tools.deleterepeatedelement(array, arraysize);
    
    tools.selectsort(array, arraysize);
    
    if (textfile) {
        for (int i=0; i<arraysize; i++) {
            textfile<<array[i].file<<std::endl;
        }
        textfile.close();
        return true;
    }
    else{
        std::cout<<"Could not make an entry to text file";
        return false;
    }
    
}









