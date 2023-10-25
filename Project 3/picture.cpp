#include "grid.h"
#include<iostream>
#include<string>
#include<cctype>
using namespace std;
const int HORIZ = 0;
const int VERT = 1;

const int FG = 0;
const int BG = 1;
//with redundant breaks just in case

char currentChar = '*';
int currentMode = FG;

bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg){
    if(dir!=0 && dir!=1){
        return false;
    }
    if(fgbg !=0 && fgbg!=1){
        return false;
    }
    if(!isprint(plotChar)){
        return false;
    }   
    if(r > getRows() || c>getCols()){
        return false;
    }
    if(dir == HORIZ){
        if(c+distance < 1 || c+distance > getCols()){
            return false;
        }
        else{
            if(distance>0){
                for(int i =c; i<= c+distance;i++){
                    if(getChar(r,i)==' '){
                        setChar(r,i,plotChar);
                    }
                    else if(fgbg==FG){
                        setChar(r,i,plotChar);
                    }
                }
            }
            else if(distance <0){
                for(int i =c; i>= c+distance;i--){
                    if(getChar(r,i)==' '){
                        setChar(r,i,plotChar);
                    }
                    else if(fgbg==FG){
                        setChar(r,i,plotChar);
                    }
                }
            }
            else{
                if(fgbg==FG){
                    setChar(r,c,plotChar);
                }
            }
        }
        return true;
    }
    else{
        if(r+distance < 1 || r+distance > getRows()){
            return false;
        }
        else{
            if(distance>0){
                for(int i =r; i<= r+distance;i++){
                    if(getChar(i,c)==' '){
                        setChar(i,c,plotChar);
                    }
                    else if(fgbg==FG){
                        setChar(i,c,plotChar);
                    }
                }
            }
            else if(distance <0){
                for(int i =r; i>= r+distance;i--){
                    if(getChar(i,c)==' '){
                        setChar(i,c,plotChar);
                    }
                    else if(fgbg==FG){
                        setChar(i,c,plotChar);
                    }
                }
            }
            else{
                if(fgbg==FG){
                    setChar(r,c,plotChar);
                }
            }
        }
        return true;
    }
    
};


int performCommands(string commandString, char& plotChar, int& mode, int& badPos){
    
    int type = 0; //0 represents command 1 represents the second part of a command
    int distance=0; // used to track the distance for how far the line will go
    int r=1;//r used to track current row
    int c=1;// c used to track current col
    
    // if given plotChar is invalid return error type 2
    if(!isprint(plotChar)){
        return 2; 
    }  
    // if given mode value is invalid return error type 2
    if(mode != BG && mode != FG){
        return 2;
    }
    
    // loop through the string. Used < instead of != because I iterate by more than 1 sometimes
    int i =0;
    while(i<commandString.size()){
        distance=0;
            if(i==commandString.size()-1){
                if(!(commandString[i]=='c') && !(commandString[i]=='C')){
                    badPos = commandString.size();
                    return 1;
                }
            }
            char temp = commandString[i];
            switch(temp){
               
    // -------------------------------------- H CASES --------------------------------------------------       
    //First checks negatives, then one or 2 digit lengths. Then positives 1 or 2 digits lengths. 
               
                case('h'):
                    
               
               
               
                case('H'):
                    //if 'h' is the second to last letter and the last letter is not a number its invalid 
                    if(i==commandString.size()-2 && !isdigit(commandString[i+1])){
                        badPos=i+1;
                        return 1;
                    }
                    //changing direction for negative cases.
                    if(commandString[i+1]=='-'){
                        
                        // the following if is for negative double digit lengths. I first check for string out of bounds then calc.
                        
                        if(i+3 <commandString.size()){
                            if(isdigit(commandString[i+2]) && isdigit(commandString[i+3])){
                                distance = (commandString[i+2]-'0')*10;
                                distance += commandString[i+3]-'0';
                                distance = distance * -1;
                                if(plotLine(r,c,distance,0,plotChar,mode)){
                                    c = c+ distance;
                                    i+=4;
                                }
                                else{
                                    badPos=i;
                                    return 3;
                                }
                            }
                            else if(isdigit(commandString[i+2])){
                                distance = commandString[i+2]-'0';
                                distance = distance*-1;
                                if(plotLine(r,c,distance,0,plotChar,mode)){
                                    c = c+ distance;
                                    i+=3;
                                }
                                else{
                                    badPos=i;
                                    return 3;
                                }
                            }
                        
                        } 
                        //this if checks
                        else if(i+2<commandString.size()){
                            if(isdigit(commandString[i+2])){
                                distance = commandString[i+2]-'0';
                                distance = distance*-1;
                                if(plotLine(r,c,distance,0,plotChar,mode)){
                                    c = c+ distance;
                                    i+=3;
                                }
                                else{
                                    badPos=i;
                                    return 3;
                                }
                            }
                        }
                        else{
                                badPos=i+2;
                                return 1;
                            }
                    }
                        
                    else if(i+2<commandString.size()){   
                        if(isdigit(commandString[i+1]) && isdigit(commandString[i+2])){
                            distance = (commandString[i+1]-'0')*10;
                            distance += commandString[i+2]-'0';
                            if(plotLine(r,c,distance,0,plotChar,mode)){
                                c = c+ distance;
                                i+=3;
                            }
                            else{
                                badPos=i;
                                return 3;
                            }
                        }
                        else if(isdigit(commandString[i+1])){
                            distance = commandString[i+1]-'0';
                            if(plotLine(r,c,distance,0,plotChar,mode)){
                                c = c+ distance;
                                i+=2;

                            }
                            else{
                                badPos=i;
                                return 3;
                                }
                        }
                    }
                    else if(isdigit(commandString[i+1])){
                            distance = commandString[i+1]-'0';
                            if(plotLine(r,c,distance,0,plotChar,mode)){
                                c = c+ distance;
                                i+=2;
                            }
                            else{
                                badPos=i;
                                return 3;
                                }
                        }
                    else{
                        badPos=i+1;
                        return 1;
                    }
                    break;
               
// -------------------------------------- V CASES --------------------------------------------------       
//First checks negatives, then one or 2 digit lengths. Then positives 1 or 2 digits lengths. 

                case('V'):
                    
                case('v'):
                   if(i==commandString.size()-2 && !isdigit(commandString[i+1])){
                        badPos=i+1;
                        return 1;
                    }
                    //changing direction for negative cases.
                    if(commandString[i+1]=='-'){
                        if(i+3 <commandString.size()){
                            if(isdigit(commandString[i+2]) && isdigit(commandString[i+3])){
                                distance = (commandString[i+2]-'0')*10;
                                distance += commandString[i+3]-'0';
                                distance = distance * -1;
                                if(plotLine(r,c,distance,1,plotChar,mode)){
                                    r = r+ distance;
                                    i+=4;
                                }
                                else{
                                    badPos=i;
                                    return 3;
                                }
                            }
                            else if(isdigit(commandString[i+2])){
                                distance = commandString[i+2]-'0';
                                distance = distance*-1;
                                if(plotLine(r,c,distance,1,plotChar,mode)){
                                    r = r+ distance;
                                    i+=3;
                                }
                                else{
                                    badPos=i;
                                    return 3;
                                }
                            }
                        
                        } 
                        else if(i+2<commandString.size()){
                            if(isdigit(commandString[i+2])){
                                distance = commandString[i+2]-'0';
                                distance = distance*-1;
                                if(plotLine(r,c,distance,1,plotChar,mode)){
                                    r = r+ distance;
                                    i+=3;
                                }
                                else{
                                    badPos=i;
                                    return 3;
                                }
                            }
                        }
                        else{
                                badPos=i+2;
                                return 1;
                            }
                    }
                        
                    else if(i+2<commandString.size()){   
                        if(isdigit(commandString[i+1]) && isdigit(commandString[i+2])){
                            distance = (commandString[i+1]-'0')*10;
                            distance += commandString[i+2]-'0';
                            if(plotLine(r,c,distance,1,plotChar,mode)){
                                r = r+ distance;
                                i+=3;
                            }
                            else{
                                badPos=i;
                                return 3;
                            }
                        }
                        else if(isdigit(commandString[i+1])){
                            distance = commandString[i+1]-'0';
                            if(plotLine(r,c,distance,1,plotChar,mode)){
                                r = r+ distance;
                                i+=2;

                            }
                            else{
                                badPos=i;
                                return 3;
                                }
                        }
                    }
                    else if(isdigit(commandString[i+1])){
                            distance = commandString[i+1]-'0';
                            if(plotLine(r,c,distance,1,plotChar,mode)){
                                r = r+ distance;
                                i+=2;
                            }
                            else{
                                badPos=i;
                                return 3;
                                }
                        }
                    else{
                        badPos=i+1;
                        return 1;
                    }
                    break;
                
// -------------------------------------- F CASES --------------------------------------------------        
// changes the value of plotChar and mode to front and iterates by 2 if valid.
                case('F'):

                case('f'):
                    mode=0;
                    if(isprint(commandString[i+1])){
                        plotChar=commandString[i+1];
                        i+=2;
                    }
                    else{
                        badPos=i+1;
                        return 1;
                    }
                    break;

// -------------------------------------- B CASES --------------------------------------------------
//changes the value of plotChar and mode to back and iterates by 2 if valid. 

                case('B'):
                    
                case('b'):
                    mode=1;
                    if(isprint(commandString[i+1])){
                        plotChar=commandString[i+1];
                        i+=2;
                    }
                    else{
                        badPos=i+1;
                        return 1;
                    }
                    break;  
                
// -------------------------------------- C CASES --------------------------------------------------
// simply replaces certain variables and clears grid and iterates i one time since c has no following values if all valid

                case('c'):
                   
                case('C'):
                    clearGrid();
                    r=1;
                    c=1;
                    plotChar='*';
                    mode=0;
                    i+=1;
                    break;
                default:
                    badPos=i;
                    return 1;
            }
    }
    return 0;
};

int main()
{
    for (;;)
    {
        cout << "Enter the number of grid rows and columns (max 30 each): ";
        int nRows;
        int nCols;
        cin >> nRows >> nCols;
        cin.ignore(10000, '\n');
        if (nRows >= 1  &&  nRows <= MAXROWS  &&  nCols >= 1  &&  nCols <= MAXCOLS)
        {
            setSize(nRows, nCols);
            break;
        }
        cout << "The numbers must be between 1 and 30." << endl;
    }
    char currentChar = '*';
    int currentMode = FG;
    for (;;)
    {
        cout << "Enter a command string (empty line to quit): ";
        string cmd;
        getline(cin, cmd);
        if (cmd == "")
            break;
        int position;
        int status = performCommands(cmd, currentChar, currentMode, position);
        switch (status)
        {
          case 0:
            draw();
            break;
          case 1:
            cout << "Syntax error at position " << position << endl;
            break;
          case 2:
            if (!isprint(currentChar))
                cout << "Current charaacter is not printable" << endl;
            if (currentMode != FG  &&  currentMode != BG)
                cout << "Current mode is " << currentMode << ", not FG or BG" << endl;
            break;
          case 3:
            cout << "Cannot perform command at position " << position << endl;
            break;
          default:
              // It should be impossible to get here.
            cout << "performCommands returned " << status << "!" << endl;
        }
    }
}