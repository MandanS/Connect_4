//
//  generaltools.cpp
//  ConnectFour
//
//  Created by mandan sharma on 5/21/16.
//  Copyright © 2016 Mandan Sharma. All rights reserved.
//

#include "connectfour.hpp"



int generaltools::linearsearch(const filenamehandler array[],const int arraysize,const char* keyword){
    for (int i=0; i<arraysize; i++) {
        if (strcmp(array[i].file,keyword)==0){
            return i;
        }
    }
    return -1;
}


unsigned int generaltools::deleterepeatedelement( filenamehandler* array,unsigned int arraysize){
    while (repeatelement(array,arraysize)!=-1) {
        remeovelement(array,repeatelement(array,arraysize) , arraysize);
        arraysize--;
    }
    return arraysize;
}



int generaltools::repeatelement(const filenamehandler* array,unsigned int arraysize){
    for (int i=0; i<arraysize-1; i++) {
        for (int j=i+1; j<arraysize; j++) {
            if (strcmp(array[i].file, array[j].file)==0) {
                return i;
            }
        }
    }
    
    return -1;
}


void generaltools::remeovelement(filenamehandler* array,const unsigned int elementtoberemoved,const unsigned int arraysize){
    for (int i=elementtoberemoved; i<arraysize-1; i++) {
        strcpy(array[i].file, array[i+1].file);
    }
}


void generaltools::selectsort(filenamehandler* array,const unsigned int arraysize){
    int temp;
    bool flag;
    for (int i=0;i<arraysize-1 ; i++) {
        flag=false;
        temp=i;
        for (int j=i+1; j<arraysize; j++) {
            if (stingcomparegreater(array[j].file,array[temp].file)){
                temp=j;
                flag=true;
            }
        }
        if (flag) {
            swapcstring(array[i].file, array[temp].file);
        }
    }
}

void generaltools::swapcstring(char* str1,char* str2){
    char temp[strlen(str1)+1];
    strcpy(temp, str1);
    strcpy(str1, str2);
    strcpy(str2, temp);
}



bool generaltools::stingcomparegreater(const char* str3,const char* str4){
    char str1[strlen(str3)+1],str2[strlen(str4)+1];
    strcpy(str1, str3);
    strcpy(str2, str4);
    lower(str1);
    lower(str2);
    if (strcmp(str1, str2)<0) {
        return true;
    }
    else{
        return false;
    }
}


void generaltools::lower(char* cstring ){
    
    for (int i=0; cstring[i]!='\0'; i++) {
        cstring[i]=tolower(cstring[i]);
    }
}


// i dont know wether string finder function is usefull or no

int generaltools::stringfinder(const filenamehandler array[],const int arraysize){
    for (int i=0; i<arraysize-1; i++) {
        if(strcmp(array[i].file, array[i+1].file)==0){
            return i;
        }
    }
    return -1;
}

unsigned int generaltools::instancefinder(gameinstance* gamed){
    for (unsigned int i=0; i<(MAXNUMBEROFROWS*MAXNUMBEROFCOULMNS)+1; i++) {
        if (gamed[i].currentinstance){
            return i;
        }
    }
    if (gamed[1].whoseturn) {
        return 2;
    }
    return 1;
}



unsigned int generaltools::numberoflinesinfile(){
    int number_of_lines=0;
    std::fstream file;
    file.open(DEFAULTFILELOADER,std::ios::in);
    std::string line;
    if(file){
        while(!file.eof()){
            getline(file,line);
            number_of_lines++;
        }
        file.close();
    }
    return number_of_lines;
}
