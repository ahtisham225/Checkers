#include <iostream> // for input_1 input_2s
#include <stdlib.h> // for CLEARING screen
#include <cstdlib> // for absolute function
#include <iomanip> //for setting width
#include <windows.h>// for graphics and colors
#include <fstream>//reading and writing into text files
#include <sstream>// string stream to read and write files
using namespace std;


char P1 = 37;      //Player 1 token
char P2 = 38;      //player 2 token
char P1_king =64; //when player 1 become king
char P2_king =35; //when player 2 become king

const int siz=10; //rows and columns size of array





void printBoard(char x[][siz], int sizeofR1, int sizeofC1,int &turn_1,int &turn_2, int &turn, string &legal_or_not, int &winningPLAYER1, int &winningPLAYER2, string player1, string player2); //Print board
void moveYo(char x[][siz], int from_R1, int from_C1, int to_R1, int to_C1, int &turn_1,int &turn_2, int &turn, string &legal_or_not, int &winningPLAYER1, int &winningPLAYER2);//moving tokens

int main()
{
    const int R1 = 10; //two more ROWS added for shape
    const int C1 = 10; //two more COLUMNS added for shape


    int turn = 1;    //by default player 1
    int turn_1 = 0;  //to count the turns of player 1
    int turn_2 = 0;             //to count the turns of player 2
    int winningPLAYER1 = 0;            //condition for winning game of player 1
    int winningPLAYER2 = 0;            //condition for winning game of player 2
    string legal_or_not = "";   // the move is right or wrong
    string winner ="dfaskdfskdj"; // to write winners into text file
    int turns=0; //total number of moves did to win the match






    char checkerboard[R1][C1]= { //P2 0   1   2   3   4   5   6   7   8   9                 /////NORMAL CHESS BOARD
                               {'H','|',P1,'.',P1,'.',P1,'.',P1,'.'},       //0
                               {'G','|','.',P1,'.',P1,'.',P1,'.',P1},       //1
                               {'F','|',' ','.',' ','.',' ','.',' ','.'},   //2
                               {'E','|','.',' ','.',' ','.',' ','.',' '},   //3
                               {'D','|',' ','.',' ','.',' ','.',' ','.'},   //4
                               {'C','|','.',' ','.',' ','.',' ','.',' '},   //5
                               {'B','|',P2,'.',P2,'.',P2,'.',P2,'.'},       //6
                               {'A','|','.',P2,'.',P2,'.',P2,'.',P2},       //7
                               {'_','|','_','_','_','_','_','_','_','_'},   //8
                               {' ','|','1','2','3','4','5','6','7','8'}};  //9


    system("color 4f"); //red console color
    string input_1  = ""; // initial choosen position
    string input_2 = ""; // final choosen  position
    int choose; //either choose to quit
    cout<<setw(60)<<"Welcome to Checkers";
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"1. Start New Game  ";
    cout<<setw(40)<<"   INSTRUCTIONS   ";
    cout<<setw(20)<<"2. Quit Game."<<endl;
    cout<<setw(65)<<" The token of player 1 is \"%\"\n"<<setw(64)<<"The token of player 2 is \"&\""<<endl;
    cout<<setw(68)<<" By default it is Player 1's Turn\n"<<setw(70)<<"Make your input as [row][column] i.e A7"<<endl;
    cout<<setw(74)<<" When Player 1 become king its token changes to \"@\""<<endl;
    cout<<setw(74)<<" When Player 2 become king its token changes to \"#\""<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"Please select 1 or 2:  ";
    cin >> choose;

    while(!(choose==1 || choose == 2 ) && cin.fail())
    {
        cin.clear();
        cin.ignore();
        string ss;
        getline(cin,ss);
        cout<<"Please select 1 or 2:  ";
        cin >> choose;

        }

    string player1;
    cout<<"INPUT NAME OF PLAYER 1:   ";
    cin>>player1;
    string player2;
    cout<<"INPUT NAME OF PLAYER 2:   ";
    cin>>player2;
    if(choose==2)
       {
        return 0;
       }


    while(winningPLAYER1 != 8 && winningPLAYER2 !=8 )
    {

        if (choose == 1 ) //game starts
        printBoard(checkerboard, R1, C1, turn_1, turn_2, turn, legal_or_not, winningPLAYER1,winningPLAYER2,player1,player2);

        cout<<setw(20)<<"Type \"QUIT\" or \"quit\" the game\n"<<endl;
        cout << "move from: " ; cin >> input_1;// A2   would be [7][3] ===> [R1][C1umn]

        if (input_1 == "QUIT" || input_1 == "quit")
        {
            return 0;
        }
        cout << "to:   " ; cin >> input_2; // B3   would be [6][4] ===> [R1][C1umn]
        if (input_2 == "QUIT" || input_2 == "quit")
        {
            return 0;
        }


    //////////////convert crude input_1 values to array index values, use characters ascii number////////////////
        int input_1_R1 = 8-(input_1[0]-64);
        int input_1_C1 = 1+(input_1[1]-48);
        int input_2_R1 = 8-(input_2[0]-64);
        int input_2_C1 = 1+(input_2[1]-48);
        moveYo(checkerboard, input_1_R1, input_1_C1, input_2_R1, input_2_C1,turn_1,turn_2, turn,legal_or_not,winningPLAYER1,winningPLAYER2);

    }

    if(winningPLAYER1==8) // condition when player 1 wins
    {
        winner=player1;
        turns=turn_1;
    }
    else if (winningPLAYER2==8) //condition when player 2 wins
    {
        winner=player2;
        turns=turn_2;
    }
    cout<<"WINNNER IS "<< winner <<endl;
    cout<<endl;
    cout<<endl;
    cout<<"HALL OF FAMES"<<endl;
    cout<<"PLAYERS\t"<<"No of Moves to win"<<endl;

    fstream fileofwinners_("winners.txt", ios::app); //name of player and the moves he did to win the match is being stored
    if(fileofwinners_.is_open())
    {
            fileofwinners_<<winner<<"\t"<<turns;
    }
    else //condition when error in opening file
    {
        cout<<" File cannot open " <<endl;
        return 0;
    }
    fileofwinners_.close();
    char arra[1000]; //array to store the text in the file to show on screen
    ifstream obj("winners.txt");
    while(obj>>winner>>turns)
    {
        cout<<winner<<"\t"<<turns<<endl;
    }

    obj.close();

}



void printBoard(char x[][siz], int sizeofR1, int sizeofC1, int &turn_1, int &turn_2, int &turn, string &legal_or_not, int &winningPLAYER1, int &winningPLAYER2, string player1, string player2)
{

    system("CLS");// white background
    system(" color F0");
        cout<<"__________________________________________________"<<endl;
    for(int r = 0; r < sizeofR1 ; r++) // printing selected board
    {

        for(int c = 0; c < sizeofC1; c++)
        {
            if (x[r][c]==P1 || x[r][c]==P1_king)
            {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),95); //selecting tokens color and its background for P1

            }
            else if (x[r][c]==P2 || x[r][c]==P2_king)
            {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),91); //selecting tokens color and its background for P2
            }
            else if (x[r][c]=='.')
            {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),102);//selecting tokens color and its background for diagonals
            }
            else if (x[r][c]==' ' && c!=0)
            {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),85);//selecting tokens color and its background for other diagonals
            }

            else {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);

            }
            cout<<setw(2)<<" " << x[r][c] << " ";
            cout<<"|";

            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
            cout<<endl;
            cout<<endl;
    }

    cout << "Total moves:   "<<player1<<" : " << turn_1 << "   "<<player2 <<" : "<< turn_2 << " " << endl<<endl;
    cout<< "Total Tokens taken:  "<<player1<<" : "<<winningPLAYER1<<"  "<<player2 <<" : "<<winningPLAYER2<<" "<<endl;
    cout << "Player " << turn  << "'s turn" << endl;

    if(legal_or_not != "") // is the move legal or not
        cout << legal_or_not;
    cout << endl;
}
void moveYo(char x[][siz], int from_R1, int from_C1, int to_R1, int to_C1, int &turn_1,int &turn_2, int &turn, string &legal_or_not, int &winningPLAYER1, int &winningPLAYER2) // moving the piece if legal
{


    char xy; //SWAPPING PLAYER VALUES
    char yz; //SWAPPING PLAYER VALUES
    char kx; //swapping player 1 king values
    char yx; //swapping player 2 king values
    char moveornot; //move if another chance


    int addition_to_R1= from_R1+1; // addition to check player1 conditions
    int subtraction_to_R1= from_R1-1; //subtraction to check player2 conditions
    int decision; //SWAPPING PLAYER ROWS
    int valueoftwo; //value of 2 can be negative and positive according to move
    int counttokens=0; //count the number of tokens a player took from  another player
    int valueofrows;

    if (turn==1)
    {

        if(x[from_R1][from_C1]==P1_king)
        {
            xy=P1_king; //xy is taken as selected token
        }
        else
        {
            xy=P1;

        }
        yz=P2; //other player token
        decision=addition_to_R1;
        valueoftwo=2;
        kx=P1_king;
        yx=P2_king;
        valueofrows=1;
        if(xy==P1)
    {
        if(to_R1<from_R1)//WHEN TOKEN OF PLAYER 1 MOVES BACK
        {
        legal_or_not = "ILLEGALMOV 2R1<FR1";
        return;
        }
    }
    }

     else
        {

        if(x[from_R1][from_C1]==P2_king)
        {
            xy=P2_king;
        }
            else {xy=P2;}
            yz=P1;
            decision=subtraction_to_R1;
            valueoftwo=-2;
            kx=P2_king;
            yx=P1_king;
            valueofrows=-1;
            if(xy==P2)
        {

            if(to_R1>from_R1)//WHEN TOKEN OF PLAYER 2 MOVES BACK
        {
        legal_or_not = "ILLEGAL_2R1>FR1";
        return;
        }
        }
        }


    if (x[from_R1][from_C1]!=xy || x[to_R1][to_C1]==xy || x[to_R1][to_C1]==yz || from_C1 < 2 || from_R1 < 0 || from_C1 > 9 || from_R1 > 7 || to_C1 < 2 || to_R1 < 0 || to_C1 > 9 || to_R1 > 7 || (from_C1+from_R1)%2!=0 || (to_C1+to_R1)%2!=0)
    {
        legal_or_not = "ILLEGALMOST"; // most of the illegal moves are mentioned in this block
        return;
    }

    else
    {
        if (x[from_R1][from_C1]==P1_king || x[from_R1][from_C1]==P2_king) //conditions for kings
        {
            if((x[from_R1+1][from_C1+1]==yz || x[from_R1+1][from_C1+1]==yx) && to_R1-from_R1==2 && to_C1-from_C1==2) //king TAKING TOKEN forward right side
            {
             legal_or_not = "LEGAL-KING-FORWARD-RIGHT";
             x[to_R1][to_C1] = x[from_R1][from_C1];
             x[from_R1][from_C1] = ' ';
             x[from_R1+1][from_C1+1]=' ';
             counttokens++;

                if((x[to_R1+1][to_C1+1]==yz || x[to_R1+1][to_C1+1]==yx) || (x[to_R1+1][from_C1-1]==yz || x[to_R1+1][to_C1-1]==yx)||(x[to_R1-1][to_C1+1]==yz || x[to_R1-1][to_C1+1]==yx) || (x[to_R1-1][from_C1-1]==yz || x[to_R1-1][to_C1-1]==yx) )
            {
                //MOST OF THE CONDITIONS WHEN PLAYER HAS TAKEN ONE TOKEN AND HE HAS TOKENS AVAILABLE ON ITS SIDE

                    cout<<"IF YOU HAVE ANOTHER CHANCE  PRESS 'Y' TO PLAY ANY OTHER KEY TO GO ON:   "<<endl;
                    cin>>moveornot;
                    if(moveornot=='Y'){
                    if (turn==1)
                    {
                        winningPLAYER1+=counttokens;
                    }
                    else if (turn==2)
                    {
                        winningPLAYER2+=counttokens;
                    }
                    return;
            }
            }
            }
            else if((x[from_R1+1][from_C1-1]==yz || x[from_R1+1][from_C1-1]==yx) && to_R1-from_R1==2 && to_C1-from_C1==-2) //KING TAKING TOKEN FORWARD LEFT
                {
             legal_or_not = "LEGAL-KING-FORWARD-LEFT";
             x[to_R1][to_C1] = x[from_R1][from_C1];
             x[from_R1][from_C1] = ' ';
             x[from_R1+1][from_C1-1]=' ';
        counttokens++;

                   if((x[to_R1+1][to_C1+1]==yz || x[to_R1+1][to_C1+1]==yx) || (x[to_R1+1][from_C1-1]==yz || x[to_R1+1][to_C1-1]==yx)||(x[to_R1-1][to_C1+1]==yz || x[to_R1-1][to_C1+1]==yx) || (x[to_R1-1][from_C1-1]==yz || x[to_R1-1][to_C1-1]==yx) )
            {


                    cout<<"IF YOU HAVE ANOTHER CHANCE  PRESS 'Y' TO PLAY ANY OTHER KEY TO GO ON:   "<<endl;
                    cin>>moveornot;
                    if(moveornot=='Y'){
                    if (turn==1)
                    {
                        winningPLAYER1+=counttokens;
                    }
                    else if (turn==2)
                    {
                        winningPLAYER2+=counttokens;
                    }
                    return;
            }
            }
            }
            else if((x[from_R1-1][from_C1+1]==yz || x[from_R1-1][from_C1+1]==yx) && to_R1-from_R1==-2 && to_C1-from_C1==2) //KING TAKING TOKEN BACKWARD RIGHT
                {
             legal_or_not = "LEGAL-KING-BACKWARD-RIGHT";
             x[to_R1][to_C1] = x[from_R1][from_C1];
             x[from_R1][from_C1] = ' ';
             x[from_R1-1][from_C1+1]=' ';
        counttokens++;

                if((x[to_R1+1][to_C1+1]==yz || x[to_R1+1][to_C1+1]==yx) || (x[to_R1+1][from_C1-1]==yz || x[to_R1+1][to_C1-1]==yx)||(x[to_R1-1][to_C1+1]==yz || x[to_R1-1][to_C1+1]==yx) || (x[to_R1-1][from_C1-1]==yz || x[to_R1-1][to_C1-1]==yx) )
            {


                    cout<<"IF YOU HAVE ANOTHER CHANCE  PRESS 'Y' TO PLAY ANY OTHER KEY TO GO ON:   "<<endl;
                    cin>>moveornot;
                    if(moveornot=='Y'){
                    if (turn==1)
                    {
                        winningPLAYER1+=counttokens;
                    }
                    else if (turn==2)
                    {
                        winningPLAYER2+=counttokens;
                    }
                    return;
            }
            }
                         }
            else if((x[from_R1-1][from_C1-1]==yz || x[from_R1-1][from_C1-1]==yx) && to_R1-from_R1==-2 && to_C1-from_C1==-2) //KING TAKING TOKEN BACKWARD LEFT
                {
             legal_or_not = "LEGAL-KING-BACKWARD-LEFT";
             x[to_R1][to_C1] = x[from_R1][from_C1];
             x[from_R1][from_C1] = ' ';
             x[from_R1-1][from_C1-1]=' ';
             counttokens++;

               if((x[to_R1+1][to_C1+1]==yz || x[to_R1+1][to_C1+1]==yx) || (x[to_R1+1][from_C1-1]==yz || x[to_R1+1][to_C1-1]==yx)||(x[to_R1-1][to_C1+1]==yz || x[to_R1-1][to_C1+1]==yx) || (x[to_R1-1][from_C1-1]==yz || x[to_R1-1][to_C1-1]==yx) )
            {


                    cout<<"IF YOU HAVE ANOTHER CHANCE  PRESS 'Y' TO PLAY ANY OTHER KEY TO GO ON:   "<<endl;
                    cin>>moveornot;
                    if(moveornot=='Y'){
                    if (turn==1)
                    {
                        winningPLAYER1+=counttokens;
                    }
                    else if (turn==2)
                    {
                        winningPLAYER2+=counttokens;
                    }
                    return;
            }
            }
             }
            else if( (abs(from_C1-to_C1)>1) || (abs(from_R1-to_R1)>1)) //IF MOVED MORE THAN 1 ROW OR 1 COLUMN WITHOUT TAKING ANY TOKEN

        {
        legal_or_not = "ILLEGAL 1 ";
        return;
        }

        else{ //JUST FOR SINGLE MOVE
            legal_or_not = "LEGAL";
            x[to_R1][to_C1] = x[from_R1][from_C1];
            x[from_R1][from_C1] = ' ';

        }

        }

       else if((x[decision][from_C1+1]==yz || x[decision][from_C1+1]==yx) && to_R1-from_R1==valueoftwo && to_C1-from_C1==2 ) // TAKING TOKEN ON RIGHT SIDE WHEN PLAYER IS NOT A KING
                {
             legal_or_not = "LEGAL-TOKEN-RIGHT";
             x[to_R1][to_C1] = x[from_R1][from_C1];
             x[from_R1][from_C1] = ' ';
             x[decision][from_C1+1]=' ';
             counttokens++;

            if((x[to_R1+valueofrows][to_C1+1]==yz || x[to_R1+valueofrows][to_C1+1]==yx) || (x[to_R1+valueofrows][from_C1-1]==yz || x[to_R1+valueofrows][to_C1-1]==yx) )
            {


                    cout<<"IF YOU HAVE ANOTHER CHANCE  PRESS 'Y' TO PLAY ANY OTHER KEY TO GO ON:   "<<endl;
                    cin>>moveornot;
                    if(moveornot=='Y'){
                    if (turn==1)
                    {
                        winningPLAYER1+=counttokens;
                    }
                    else if(turn==2)
                    {
                        winningPLAYER2+=counttokens;
                    }
                    return;
            }
            }
            }
        else if((x[decision][from_C1-1]==yz || x[decision][from_C1-1]==yx) && to_R1-from_R1==valueoftwo && to_C1-from_C1==-2)//TAKING TOKEN ON LEFT SIDE WHEN PLAYER IS NOT A KING
        {
            legal_or_not = "LEGAL-TOKEN-LEFT";
            x[to_R1][to_C1] = x[from_R1][from_C1];
            x[from_R1][from_C1] = ' ';
            x[decision][from_C1-1]=' ';
            counttokens++;

            if((x[to_R1+valueofrows][to_C1+1]==yz || x[to_R1+valueofrows][to_C1+1]==yx) || (x[to_R1+valueofrows][from_C1-1]==yz || x[to_R1+valueofrows][to_C1-1]==yx) )
            {


                    cout<<"IF YOU HAVE ANOTHER CHANCE  PRESS 'Y' TO PLAY.| INPUT ANY OTHER KEY TO GO ON:   "<<endl;
                    cin>>moveornot;
                    if(moveornot=='Y'){
                    if (turn==1)
                    {
                        winningPLAYER1+=counttokens;
                    }
                    else
                    {
                        winningPLAYER2+=counttokens;
                    }
                    return;
            }
            }
        }

        else if( (x[decision][from_C1+1] != yz || x[decision][from_C1-1] != yz)&&(abs(from_R1-to_R1)>1 || abs(from_C1-to_C1)>1))
    // MOVEMENT OF ROWS AND COLUMNS MUST NOT BE GREATER THAN 1
        {
        legal_or_not = "ILLEGAL";
        return;
        }


        else if ((x[decision][from_C1+1]==yz || x[decision][from_C1-1]==yz)&&(abs(from_R1-to_R1)>1 || abs(from_C1-to_C1)>1))
        { //PLAYER SHOULD NOT MOVE TO THE PLACE WHERE THERE IS ALREADY A TOKEN
            legal_or_not = "ILLEGAL";
            return;
        }
        else{
            legal_or_not = "LEGAL";
            x[to_R1][to_C1] = x[from_R1][from_C1];
            x[from_R1][from_C1] = ' ';

        }
        }


        if(turn==1)
        {
            for(int i =2 ; i<10; i++)
        {
            if (x[7][i]==P1)
            {
                x[7][i]=P1_king;
            }
        }

            turn_1++;//ADDS PLAYER MOVES
            turn = 2;// CHANGES PLAYER TURN
            winningPLAYER1+=counttokens; //ADDS PLAYER TAKEN TOKENS
        }
        else //(turn == 2)
        {

            for(int i =2 ; i<10; i++)
        {
            if (x[0][i]==P2)
            {
                x[0][i]=P2_king;
            }
        }
            turn_2++;
            turn = 1;
            winningPLAYER2+=counttokens;
        }
    }





