//
//  display.hpp
//  ConnectFour
//
//  Created by mandan sharma on 5/20/16.
//  Copyright © 2016 Mandan Sharma. All rights reserved.
//

#ifndef connectfour_hpp
#define connectfour_hpp

#include <stdio.h>
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstring>
#include <cstdlib>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////     WARNING:      ////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////// DO NOT TRY LOADING GAME SAVED IN PREVIOUS FORMATS IF YOU HAVE CHANGED ANY OF THESE QUANTITIES /////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const unsigned int MAXNUMBEROFROWS=12,MAXNUMBEROFCOULMNS=12,CONNECTTHESE=4,MAXCHARACTEROFPLAYERNAME=21,MAXCHARACTEROFFILENAME=22;///////////////////
const char TEXTFILEEXTENSION[]=".connect4",DEFAULTFILELOADER[]="savedgame.txt";/////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




struct gameinstance{
    unsigned char board[MAXNUMBEROFROWS][MAXNUMBEROFCOULMNS];
    char playeronename[MAXCHARACTEROFPLAYERNAME],playertwoname[MAXCHARACTEROFPLAYERNAME];
    int row,coulmn;
    char timeofmove[26];// length of the string to display time
    bool whoseturn;// true for player one false for player 2
    bool playwithcomputer; //tru if with computer
    //bool ifplayedthisinstancebefore;
    bool currentinstance;
    //char dificultylevel;
};

struct filenamehandler{
    char file[MAXCHARACTEROFFILENAME];
};


class generaltools{
private:
    void lower(char* );
    bool stingcomparegreater(const char* ,const char* );
    void swapcstring(char* ,char* );
    int repeatelement(const filenamehandler* ,unsigned int );
    
public:
    unsigned int numberoflinesinfile();
    int stringfinder(const filenamehandler [],const int );
    int linearsearch(const filenamehandler [],const int ,const char* );
    void selectsort(filenamehandler* ,const unsigned int );
    unsigned int deleterepeatedelement( filenamehandler* ,unsigned int );
    void remeovelement(filenamehandler*,const unsigned int ,const unsigned int );
    unsigned int instancefinder(gameinstance*);
};



class initialize{
private:
    bool initializethegamewc(gameinstance* , char,const bool);
    bool resettheboard(gameinstance*);
    bool writedata(gameinstance* array,unsigned int row,unsigned int coulmn,const char* player1name,const char* player2name , bool playwithcomputer, char dificultylevel,bool whooseturn);
    bool loadwithdefault(gameinstance* ,const bool);
    bool loadfromsavedfile(gameinstance* , const bool );
    bool loadwithcustom(gameinstance* ,const bool );
    bool openthefile(gameinstance*,char*);
public:
    bool initializethegame(gameinstance* );
    bool initializethegamewithoutarray(gameinstance*);
};


class savegame{
private:
    bool savinggame(const char [],gameinstance* );
    bool writeactualgame(const char* , gameinstance* );
    bool entrytotextfile(const char* file,filenamehandler* , unsigned int );
    bool finalstep(const char [],filenamehandler*,unsigned int ,gameinstance* );
public:
    bool savegamenow(gameinstance* );
};


class display{
private:
    void linesaperatorline(const unsigned int,const gameinstance &);
public:
    void diplayinstance(const gameinstance &);
};



class gameplay{
private:
    bool readandprocesscommand(gameinstance*,unsigned int &);
    bool processtheboard(gameinstance * ,const unsigned int ,unsigned int&);
    void boardcopy(gameinstance& ,const gameinstance &instance2);
public:
    bool playthegame();
};





class winanddrawconditions{
private:
    int rowcheck( const gameinstance &);
    int coulmncheck( const gameinstance &);
    int leftdiagonalcheck( const gameinstance &);
    int rightdiagonalcheck(const gameinstance &);
public:
    int windraw(const  gameinstance &);
};




















#endif /* display_hpp */
