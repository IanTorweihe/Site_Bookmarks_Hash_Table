/******************************************************************************
# Program Desc.:      This program is a website bookmarking program. The program
#                     implements a hash table using chaining (pointer array of 
#                     linked lists) to store website information.
# File:               table.h
# File Description:   Header file for the Table ADT class. Implemented using a 
#                     hash table with chaining (array of linked lists).
# Input:              None
# Output:             None
#******************************************************************************/
#ifndef TABLE_H
#define TABLE_H
#include <iostream>
#include <cstring>
#include <fstream>

#include "website.h"

using namespace std;

class Table
{
public:
   Table(); // constructor
   Table(const Table& aTable); // copy constructor
   ~Table(); // destructor

   bool insert(Website& aWebsite); // add website to the hash table
   bool removeOneStar(); // remove all websites with a rating of 1
   bool retrieve(const char * topic_keyword, Website all_matches[], 
                 int& num_found) const; // retrieve websites by topic keyword
   bool edit(char * searchTopic, char * searchURL, char * newReview, 
             int newRating); // edit a website review and rating
   bool displayAll(char * searchTopic) const; // display all websites by topic
   bool displayAll() const; // display all websites (overload)
   int monitor(int index) const; // display chain length at index
   int getSize() const; // return size of hash table
   int getCapacity() const; // return capacity of hash table

   void loadFromFile(const char * filename); // load test data from file
   // void saveToFile(const char * filename); // I think this is optional

private:
   struct Node // node struct for vertical chain (column)
   {
      Node(const Website& aWebsite) // node constructor
      {
         data = new Website(aWebsite);
         next = nullptr;
      };
      ~Node() // node destructor
      {
         if(data)
         {
            delete data;
         }
         data = nullptr;
         next = nullptr;
      };
      Website * data = nullptr;
      Node * next = nullptr;
   };
   Node** aTable; // pointer to array of pointers to nodes / chains (row)
   const static int INIT_CAP = 11; // initial capacity of the hash table
   int currCapacity; // current capacity of the hash table
   int size; // current number of websites in the hash table

   // private helper functions
   int hash(const char * key) const; // hash function
   int hashHelper(char * key, int i) const; // helper function for hash()
   //int monitorHelper(Node * head) const; // helper function for monitor()
   void destroy(); // destroy the hash table
};

#endif

