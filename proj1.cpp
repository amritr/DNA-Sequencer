 
/****************************************************************
 **File: proj1.cpp
 **project: CMSC 202 project 1, Spring 2017
 **Author: Dawit Gebremariam
 **Date: 02/23/2017
 **Section:
 **Email: gdawit1@umbc.edu
 **
 **This file contains the main driver program for project 1.
 **This files gives the user an option either to load the map
 **or create new map inorder to play the Manhunt game. Then it
 **leads the investigator to where the target is hidden.
 **
 *****************************************************************/



#include <iostream>
#include <fstream>
#include <string>

using namespace std;


const int SIZE =10; //the size of the two dimenssional array
int invs_X, invs_Y, target_X, target_Y; //the x and y cooridinets of the investigator and target
bool flag;
char pos[SIZE][SIZE];

void loadMap(char map[SIZE][SIZE], char name[]);
void newMap(char map[SIZE][SIZE], int x1, int y1, int x2, int y2);
void move(char position[SIZE][SIZE], char direction);
void printMap(char pos[SIZE][SIZE]);
bool check(char direction);

int main()
{
  int start,play;
  char filename[80];

  for(int i=0; i<SIZE;i++)
    {
      for(int k=0; k<SIZE; k++)
        {
          pos[i][k]='_';
        }
    }

 do
   {

     cout<<"WELCOME TO THE MANHUNT GAME APPLICATION \n";
     cout<<"What would you like to do\n"<<endl;
     cout<<"1. load a simulation form  file\n";
     cout<<"2. start a new simulation\n";
     cout<<"3. Exit\n";
     cout<<"Enter 1-3"<<endl;

     cin>>start;

     switch (start)
       {
       case 1:
	 cout<<"What is the name of the file?\n";
              if (cin.peek() == '\n')
               cin.ignore();
	 cin.getline(filename,sizeof(filename)); //reads the coordinates from the file

	 loadMap(pos,filename);     //load map function that loads the map
	 break;
       case 2:
	 cout<<" enter the x direction of the investigator\n";
	 cin>>invs_X;
	 cout<<" enter the y direction of the investigator\n";
	 cin>>invs_Y;
	 cout<<" enter the x direction of the target\n";
	 cin>>target_X;
	 cout<<" enter the y direction of the target\n";
	 cin>>target_Y;

	 newMap(pos, invs_X, invs_Y, target_X, target_Y);  //creates a new map
	 break;
       case 3:
	 cout<<" Giving up so soon? Good-bye\n";
	 break;
       default:
	 cout<<"you entered an invalid number, try again\n";
       }
   }
 while(start<1||start>3); //loops until the user enter the right input
 if(start==1||start==2)
   {
     flag = true;

   do
     {

       cout<<"WHAT WOULD YOU LIKE TO DO?"<<endl;
       cout<<"\t1. search NORTH "<<endl;
       cout<<"\t2. search EAST "<<endl;
       cout<<"\t3. search SOUTH "<<endl;
       cout<<"\t4. search WEST"<<endl;
       cout<<"\t5. see MAP"<<endl;
       cout<<"\t6. EXIT"<<endl;
       cout<<"Enter 1-6"<<endl;

       cin>>play;

       switch(play)
	 {
	 case 1:
	   move(pos,'N');
	   break;
	 case 2:
	   move(pos,'E');
	   break;
	 case 3:
	   move(pos,'S');
	   break;
	 case 4:
	   move(pos, 'W');
	   break;
	 case 5:
	   printMap(pos);
	   break;
	 case 6:
	   cout<<"Giving up so soon? Good-bye\n";
	   flag = false;
	   break;
	 default:
	   cout<<play<<" is not a valid input. Please enter 1-6\n"<<endl;

	 }

     } while(flag==true);
   }
}

//name: loadMap
//precondition: a two dimenssional array of type char and a c-string
//postcondition:it reads the x and y coordinates of the investigator
//and the target from the file, and loads the map

void loadMap(char map[SIZE][SIZE], char name[])
{
  int x1,y1,x2,y2;
  ifstream inputFile;

  //  if (cin.peek() == '\n')
  // cin.ignore();

  inputFile.open(name);
  inputFile>>x1>>y1>>x2>>y2;

  map[x1][y1]= 'I';

  invs_X=x1;
  invs_Y=y1;
  target_X = x2;
  target_Y = y2;

  printMap(map);

}

//name: newMap
//precondition: a two dimenssional array of type char, and four int values
//(the x and y coordinates of the investigator and the target
//postcondition: creates a new map with the given coordinates

void newMap(char map[SIZE][SIZE], int x1, int y1, int x2, int y2)
{
  map[x1][y1]= 'I';

  invs_X=x1;
  invs_Y=y1;
  target_X = x2;
  target_Y = y2;

  printMap(map);
}


//name:move
//precondition:a two dimenssional array of type char, and type char variable
//postcondition: after checking if the move is valid, it suggests the direction

void move(char position[SIZE][SIZE], char direction)
{

  if(!check(direction))   //check if the direction is valid
    cout<<" it is invalid move, try again please"<<endl;
  else
    {

      switch(direction)
        {
        case 'N':
	  position[invs_X][invs_Y] = '*';
	  position[invs_X-1][invs_Y] = 'I';
	  invs_X = invs_X-1;
	  break;

        case 'S':
	  position[invs_X][invs_Y] = '*';
	  position[invs_X+1][invs_Y] = 'I';

	  invs_X = invs_X+1;
	  break;

        case 'E':
	  position[invs_X][invs_Y] = '*';
	  position[invs_X][invs_Y+1] = 'I';

	  invs_Y = invs_Y+1;
	  break;
        case 'W':
	  position[invs_X][invs_Y] = '*';
	  position[invs_X][invs_Y-1] = 'I';

	  invs_Y = invs_Y-1;
	  break;
        }
      if(invs_X<target_X)
	{
	  cout<<"try searching  south\n"<<endl;
	  printMap(position);
	}

      else if(invs_X> target_X)
        {
	  cout<<"try searching north\n"<<endl;
	  printMap(position);
        }
      else if(invs_Y< target_Y)
	{
	  cout<<"try searching east\n"<<endl;
	  printMap(position);
	}

      else if(invs_Y> target_Y)
	{
	  cout<<"try searching west\n"<<endl;
	  printMap(position);
	}
      else if(invs_X == target_X && invs_Y==target_Y)
        {
          cout<<"you found the target";
	  flag = false;
        }
    }
}

//name:printMap
//precondition: two dimenssional array of type char
//postcondition: prints the map

void printMap(char pos[SIZE][SIZE])
{
  for(int i=0; i<SIZE;i++)
    {

      for(int k=0; k<SIZE; k++)
        {
          cout<<pos[i][k]<<" ";

        }
      cout<<endl;
    }
  cout<<endl;
}

//name:check
//precondition: a value of type char
//postcondition:checks if the direction of the movement is
//valid and returns true if it is valid false otherwise

bool check(char direction)
{
  bool valid = true;
  switch(direction)
    {
    case 'N':
      if(invs_X==0)
        valid = false;
      break;
    case 'S':
      if(invs_X==9)
        valid = false;
      break;
    case 'W':
      if(invs_Y==0)
        valid = false;
      break;
    case 'E':
      if(invs_Y==9)
        valid = false;
      break;

    }

  return valid;
}
