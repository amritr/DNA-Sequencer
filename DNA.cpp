/****************************************************************
 **File: proj3.cpp
 **project: CMSC 202 project 3, Spring 2017
 **Author: Dawit Gebremariam
 **Date: 03/30/2017
 **Section: 8
 **Email: gdawit1@umbc.edu
 **This program represents a DNA
 **This file contains the DNA class that inserts a DNA int a linked list,
 **displays the nucleotides,Searches the linked list for specific sequence
 **and  Displays either name of amino acid or unknown for each trinucleotide 
 **This program also populates the size of the DNA
 **
 *****************************************************************/

#include "DNA.h"
#include<string>
using namespace std;

//name: DNA (default constructor)
//pre: None
//post: A linked list (DNA) where m_head and m_tail points to NULL
DNA::DNA()
{
  m_head = NULL;
  m_tail = NULL;
  SizeOf();
}

//name: ~DNA (destructor)
//pre: There is an existing linked list
//post: A linked list (DNA) is deallocated (including all dynamically
//     allocated nucleotides)
//     to have no memory leaks!
DNA::~DNA()
{
  Clear();
}

//name: InsertEnd
//pre: Takes in a char. Creates new node (nucleotide).
//     Requires a linked list (strand of DNA)
//post: Adds a new node (nucleotide) to the end of the linked list (strand of DNA).
void DNA::InsertEnd(char payload)
{
  
  //if the list is empty
  if(IsEmpty()) 
    {
      Nucleotide* newNode = new Nucleotide;
      newNode->m_payload = payload;
      newNode->m_next = NULL;
      m_head = newNode;
      m_tail = newNode;
    }
  
   //if the list has at least one node
  else
  {
      Nucleotide* newNode = new Nucleotide;
      newNode->m_payload = payload;
      newNode->m_next = NULL;
      m_tail->m_next = newNode;
      m_tail = newNode;
        
    }
}

//name: Display
//pre: Outputs the dna strand(s); Pass it 1 for just the nucleotides;
//     2 for the nucleotides and it's complement (base pair)
//post: None
void DNA::Display(int numStrand)
{
  Nucleotide* temp_ptr;
  temp_ptr = m_head;
  
  switch(numStrand)
    {
    case 1:  //Dispaying the nucleotides that were loaded.
      cout<<"Base Pairs:"<<endl;
      while(temp_ptr!=NULL)
      {	      
	cout<<temp_ptr->m_payload<<endl;
	  temp_ptr = temp_ptr->m_next;
      }
      break;

    case 2: //Displaying the nucleotides and their complements 
      cout<<"Base Pairs:"<<endl;

      while(temp_ptr!=NULL)
       {
        char base = temp_ptr->m_payload;
	switch(base)
	 {
	  case 'A':
	    cout<<"A-T"<<endl;
	    break;
	  case 'T':
	    cout<<"T-A"<<endl;
	    break;
	  case 'G':
	    cout<<"G-C"<<endl;
	    break;
	  case 'C':
	    cout<<"C-G"<<endl;
	    break;
	  }
	temp_ptr = temp_ptr->m_next;
      }
      break;
    }
  cout<<"END"<<endl;
  cout<<m_size<<" base pairs listed"<<endl;
  cout<<(m_size/TRINUCLEOTIDE_SIZE)<<" trinucleotides listed"<<endl;
  cout<<endl;
}


//name: NumAmino
//pre: Takes in an amino acid name and its trinucleotide codon
//     Trinucleotides are just three nucleotides in a row.
//post: Searches the linked list for specific sequence; outputs results
void DNA::NumAmino(string name, string trinucleotide)
{
  int count =0;
  Nucleotide* temp = m_head;
  while(temp!=NULL)
    {
      string codon = "";
      for(int i=0;i<TRINUCLEOTIDE_SIZE;i++)
	{
	  char nucltd = temp->m_payload;
	  codon+= nucltd; 
	  temp = temp->m_next;
	}
      if(codon==trinucleotide)  
	count++;
    }
  cout<<name<<": "<<count<<" identified"<<endl;
}



//name: Sequence
//pre: Takes in full genetic code of one polynucleotide and looks at
//     one trinucleotide at a time.
//     Known amino acids are displayed, others are unknown. Stored in dynamic array.
//post: Displays either name of amino acid or unknown for each trinucleotide

void DNA::Sequence()
{
  int count =0;
  int size = m_size/TRINUCLEOTIDE_SIZE;
  string type = "";

  string* d_array;
  d_array = new string[size];

  Nucleotide* temp;
  temp = m_head;

  while(temp!=NULL)
   {
     for(int i=0;i<TRINUCLEOTIDE_SIZE;i++)  //runs three times to read the trinucleotides
      {                                   
      char nucltd = temp->m_payload;
      type+= nucltd;
      temp = temp->m_next;
     }

    string amino = Translate(type);
    if(amino != "Unknown")
      {
      d_array[count]= amino;
      count++;  //keeps track of the number of amino acids
      }
    type = ""; 
   }

  cout<<"Amino Acid List:"<<endl;
  for(int i=0;i<count;i++)
    {
      cout<<d_array[i]<<endl;
    }
  cout<<"Total Amino Acids Identified: "<<count<<endl;
  cout<<endl;

   delete[] d_array;
   d_array = NULL;
}


//name: Translate (Provided)
//pre: Takes in three nucleotides (must be G,C,T, or A)
//post: Translates a trinucleotide to its amino acid

string DNA::Translate(const string trinucleotide){
  if((trinucleotide=="ATT")||(trinucleotide=="ATC")||(trinucleotide=="ATA"))
      return ("Isoleucine");
    else if((trinucleotide=="CTT")||(trinucleotide=="CTC")||(trinucleotide=="CTA")||
	    (trinucleotide=="CTG")|| (trinucleotide=="TTA")||(trinucleotide=="TTG"))
      return ("Leucine");
    else if((trinucleotide=="GTT")||(trinucleotide=="GTC")||
	    (trinucleotide=="GTA")||(trinucleotide=="GTG"))
      return ("Valine");
    else if((trinucleotide=="TTT")||(trinucleotide=="TTC"))
      return ("Phenylalanine");
    else if((trinucleotide=="ATG"))
      return ("Methionine");
    else if((trinucleotide=="TGT")||(trinucleotide=="TGC"))
      return ("Cysteine");
    else if((trinucleotide=="GCT")||(trinucleotide=="GCC")||
	    (trinucleotide=="GCA")||(trinucleotide=="GCG"))
      return ("Alanine");
    else if((trinucleotide=="GGT")||(trinucleotide=="GGC")||
	    (trinucleotide=="GGA")||(trinucleotide=="GGG"))
      return ("Glycine");
    else if((trinucleotide=="CCT")||(trinucleotide=="CCC")||
	    (trinucleotide=="CCA")||(trinucleotide=="CCG"))
      return ("Proline");
    else if((trinucleotide=="ACT")||(trinucleotide=="ACC")||
	    (trinucleotide=="ACA")||(trinucleotide=="ACG"))
      return ("Threonine");
    else if((trinucleotide=="TCT")||(trinucleotide=="TCC")||
	    (trinucleotide=="TCA")||(trinucleotide=="TCG")||
	    (trinucleotide=="AGT")||(trinucleotide=="AGC"))
      return ("Serine");
    else if((trinucleotide=="TAT")||(trinucleotide=="TAC"))
      return ("Tyrosine");
    else if((trinucleotide=="TGG"))
      return ("Tryptophan");
    else if((trinucleotide=="CAA")||(trinucleotide=="CAG"))
      return ("Glutamine");
    else if((trinucleotide=="AAT")||(trinucleotide=="AAC"))
      return ("Asparagine");
    else if((trinucleotide=="CAT")||(trinucleotide=="CAC"))
      return ("Histidine");
    else if((trinucleotide=="GAA")||(trinucleotide=="GAG"))
      return ("Glutamic acid");
    else if((trinucleotide=="GAT")||(trinucleotide=="GAC"))
      return ("Aspartic acid");
    else if((trinucleotide=="AAA")||(trinucleotide=="AAG"))
      return ("Lysine");
    else if((trinucleotide=="CGT")||(trinucleotide=="CGC")||(trinucleotide=="CGA")||
	    (trinucleotide=="CGG")||(trinucleotide=="AGA")||(trinucleotide=="AGG"))
      return ("Arginine");
    else if((trinucleotide=="TAA")||(trinucleotide=="TAG")||(trinucleotide=="TGA"))
      return ("Stop");
    else
      cout << "returning unknown" << endl;
    return ("Unknown");
}



//name: IsEmpty
//pre: Takes in a linked list (DNA)
//post: Checks to see if the linked list (strand of DNA) is empty or not
bool DNA::IsEmpty()
{
   return (m_head == NULL);
}

//name: SizeOf
//pre: Takes in a linked list (DNA)
//post: Populates m_size with the total number of nucleotides loaded
void DNA::SizeOf()
{
  if(IsEmpty())
    m_size = 0;

  else
    {
      int count = 0;

      Nucleotide* temp;
      temp = m_head;

      while(temp!=NULL)
	{
	  count++;
	  temp = temp->m_next;
	}
      m_size = count;

    }
}

//name Clear
//pre: Takes in a linked list (DNA)
//post: Clears out the linked list (all nodes too)
void DNA::Clear()
{
  Nucleotide* node;

  while(m_head!=NULL)
    {
      node = m_head;
      m_head = m_head->m_next;
      delete node;
      node = NULL;
    }
  m_head = NULL;
  m_tail = NULL;
}

