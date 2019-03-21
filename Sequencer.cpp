/****************************************************************
 
 **This program represents a Sequencer class
 **This program contains functions that reads from a file and populates the DNA,
 **and main menu 
 
 *****************************************************************/

#include "Sequencer.h"
#include<string>
#include<fstream>

using namespace std;

//name: Sequencer (default constructor)
//pre: A linked list (DNA) is available
//post: A linked list (DNA) where m_head and m_tail points to NULL
//      m_size is also populated with SizeOf

Sequencer::Sequencer(string fileName)
{
  DNA m_dna;
  m_fileName = fileName;
  readFile();
  mainMenu();
}

//name: Sequencer (destructor)
//pre: There is an existing linked list (DNA)
//post: A linked list (DNA) is deallocated (including nucleotides) to have no memory leaks!
Sequencer::~Sequencer()
{
  cout<<"DNA removed from memory"<<endl;
  m_dna.Clear();
}

//name: readFile
//pre: Valid file name of characters (Either A, T, G, or C)
//post: Populates the LinkedList (DNA)
void Sequencer::readFile()
{
  ifstream inputFile;
  string fname = m_fileName;
  char ch;

  inputFile.open(fname.c_str());
  inputFile>>ch;
  while(!inputFile.eof())
    {
      m_dna.InsertEnd(ch); //inserting the nucleotides into the linked list
      inputFile>>ch;
    }
  inputFile.close();
  m_dna.SizeOf();
}

//name: mainMenu
//pre: Populated LinkedList (DNA)
//post: None

void Sequencer::mainMenu()
{
  int option;
  bool flag = true;
  int const MIN_VALID = 1; //The minimum valid input
  int const MAX_VALID = 5;//the maximum valid input

  cout<<"New Sequencer loaded"<<endl;
  
  while(flag)
    {

       do{
     
   cout<<"What would you like to do?:"<<endl;
  
   cout<<"1. Display Sequencer (Leading Strand)"<<endl
       <<"2. Display Sequencer (Base Pairs)"<<endl
       <<"3. Inventory Basic Amino Acids"<<endl
       <<"4. Sequence Entire DNA Strand"<<endl
       <<"5. Exit"<<endl;

   cin>>option;
    }while(option < MIN_VALID || option > MAX_VALID);

  switch(option)
    {
    case 1:
      m_dna.Display(option);
      break;
    case 2:
      m_dna.Display(option);
      break;
    case 3:
      m_dna.NumAmino("Tryptophan","TGG");
      m_dna.NumAmino("Phenylalanine","TTT");
      m_dna.NumAmino("Arginine","AGA");
      break;
    case 4:
      m_dna.Sequence();
      break;
    case 5:
      flag = false;
      break;
    }

    }
}
