#include <iostream>
#include <limits>
#include <stdlib.h>

using namespace std;

//13 is for X 15 is for O
bool place(int board[], int c, bool player1){
    //if number is greater than 9 or less than 0 then number input is wrong
    if(c>9 || c<0)
        return false;
    
    //if already filled
    if(board[c] == 13 || board[c] == 15)
        return false;
    
    //fills according to chance
    if(player1)
        board[c] = 13;
    else
        board[c] = 15;
    
    return true;
}

int check(int board[]){
    //checks for both values 13 for X and 15 for O
    for(int k=13;k<=15;k+=2){
        //row wise
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(board[(i*3)+j]!=k)
                    break;
                else if(j==2)
                    return k;
            }
        }
        //column wise
        for(int j=0;j<3;j++){
            for(int i=0;i<3;i++){
                if(board[(i*3)+j]!=k)
                    break;
                else if(i==2)
                    return k;
            }
        }
        //diagonals
        for(int r=0;r<3;r++){
            if(board[(3*r)+r]!=k)
                break;
            else if(r==2)
                return k;
        }
        for(int r=0;r<3;r++){
            if(board[(3*r)+2-r]!=k)
                break;
            else if(r==2)
                return k;
        }
    }

    //check if board is not full
    for(int i=0;i<9;i++){
        if(board[i]<=9)
            return 0;
    }
    //if full return -1
    return -1;
}

void printBoard(int board[]){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cout<<" ";
            if(board[(i*3)+j] < 10)
                cout << board[(i*3)+j];
            else{
                if(board[(i*3)+j]==13)
                    cout << "X";
                else
                    cout << "O";
            }
            cout << " ";
            if(j<2) cout << "|";
        }
        if(i<2) cout << endl << "---+---+---";
        cout << endl;
    }
}

int main(){
    int board[9];
    //board gets initialized
    for(int i=0;i<9;i++){board[i] = i+1;}

    //to store which players chance
    bool player1 = true;

    //to store which position on board and check() func return value
    int boardPos,checkVal;

    //game loop
    while(true){
        printBoard(board);
        cout << "Enter Input Player";
        
        if(player1)
            cout << "1 ( X ): " << endl;
        else
            cout << "2 ( O ): " << endl;
        
        cin >> boardPos;
        //code snippet so we always get a number in input
        while(true){
            if(cin.fail()){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout<<"Enter Numeric values only!"<<endl;
                cin>>boardPos;
            }
            if(!cin.fail())
                break;
        }

        //if number can be placed
        if(place(board,boardPos-1,player1)==false)
            continue;

        //clear the screen
        system("CLS");


        checkVal = check(board);
        if(checkVal == -1){
            cout << "Nobody Wins" << endl;
            break;
        }
        else if(checkVal == 13){
            cout << "Player 1 Wins" << endl;
            break;
        }
        else if(checkVal == 15){
            cout << "Player 2 Wins" << endl;
            break;
        }

        //inverts false to true and vice versa as after loop other player gets to play
        player1 = (player1)?false:true;
    }

    printBoard(board);
    return 0;
}