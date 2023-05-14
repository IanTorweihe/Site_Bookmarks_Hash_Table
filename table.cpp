/******************************************************************************
# Program Desc.:      This program is a website bookmarking program. The program
#                     implements a hash table using chaining (pointer array of 
#                     linked lists) to store website information.
# File:               table.cpp
# File Description:   Implementation file for the Table ADT class. Contains the
#                     hash table and functions to manipulate the data.
# Input:              None
# Output:             None
#******************************************************************************/
#include "table.h"
#include "website.h"

//Function Definitions

// Default constructor
// Description: Initializes the hash table to NULL
// Input: None
// Output: None
Table::Table()
{  
   size = 0;
   currCapacity = INIT_CAP;
   aTable = new Node*[currCapacity];
   for (int i = 0; i < currCapacity; i++)
   {
      aTable[i] = nullptr;
   }
} 

// Copy constructor
// Description: Copies the hash table from the table passed in
//              into the new table. Uses overloaded assignment
//              operator.
Table::Table(const Table & table)
{
   /*  
   aTable = nullptr;
   size = 0;
   */
   *this = table;
}

// Destructor
Table::~Table()
{
   destroy();
}

// Destroy
// Description: Deallocates all memory associated with the hash table
//              then sets all pointers to nullptr. First checks if
//              the hash table has been initialized.
// Input: None
// Output: None
void Table::destroy()
{
   if (aTable)
   {
      for (int i = 0; i < currCapacity; i++)
      {
         if (aTable[i])
         {
            delete aTable[i];
            aTable[i] = nullptr;
         }
      }
      delete [] aTable;
      aTable = nullptr;
   }
}

// OPT TODO - Maybe create destroyChain here if needed 

// Insert
// Description: Inserts a website into the hash table. If the website
//              already exists, the function returns false. If the
//              website does not exist, the function inserts the
//              website into the hash table and returns true.
// Input: website - the website to be inserted
// Output: true if the website was inserted, false if the website
//         already exists
bool Table::insert(Website& website)
{
   int index = hash(website.getTopic()); // hash the topic
   if (aTable[index]) // if the index is not null
   {
      Node * curr = aTable[index]; // set curr to the index
      while (curr) // while curr is not null
      {
         if (*curr->data == website) // if the website already exists
         {
            return false;
         }
         curr = curr->next;
      }
   }
   Node * newNode = new Node(website);
   newNode->next = aTable[index];
   aTable[index] = newNode;
   size++;
   return true;
}

// hashing function 
// Description: A naive hashing function that only adds the ASCII value of each 
//              char in the key field and mods the capacity of the table. 
//              "abc" and "cba" will result in the same index since it 
//              doesn't consider position value.
// Input: key - the key (Topic) to be hashed as a char *
// Output: the index of the hash table as an int
/*
int Table::hash(const char * key) const
{
   int index = 0;
   for (int i = 0; key[i] != '\0'; i++)
   {
      index += key[i];
   }
   return index % currCapacity;
}
*/

// hashing function (recursive)
// Description: A hasing function that recursivly adds the
//             ASCII value of each char in the key field
//             and mods the capacity of the table. "abc"
//             and "cba" will result in the same index
// Input: key - the key (Topic) to be hashed as a char *
// Output: the index of the hash table as an int

int Table::hash(const char * key) const
{
   int returnVal = 0; // return value
   //get length of key using strlen
   int len = strlen(key);
   //copy key into a new char array
   char * newKey = new char[len + 1];
   strcpy(newKey, key);
   //call recursive helper function
   returnVal = hashHelper(newKey, len - 1); // -1 because of null terminator
   //delete newKey
   delete [] newKey;
   //return the return value
   return returnVal % currCapacity;
}


// hashing function (recursive) helper
// Description: Recurisive helper function for the hash function
// Input: key - the key (Topic) to be hashed as a char *
// Output: the index of the hash table as an int
int Table::hashHelper(char * key, int i) const
{
   if (i == -1) // base case (-1 to get index 0 char)
   {
      return 0;
   }
   else // recursive case
   {
      return key[i] + hashHelper(key, i - 1);
   }
}


// removeOneStar
// Description: Removes all websites from the hash table with a rating of 1. 
//              Decrements size after removal. Returns true if anything removed
//              and false if nothing removed.
// Input: None
// Output: true if something removed, false if nothing removed
bool Table::removeOneStar()
{
   bool removed = false;
   for (int i = 0; i < currCapacity; i++) // for each index in the table
   {
      if (aTable[i]) // chain on index
      {
         Node * curr = aTable[i]; // set curr to the index
         Node * prev = nullptr; // set prev to null
         while (curr)
         {
            if (curr->data->getRating() == 1) // match
            {
               Node * temp = curr; // save curr node before deleting
               if (prev) // removing in middle or at end
               {
                  prev->next = curr->next;
               }
               else // removing at beginning
               {
                  aTable[i] = curr->next;
               }
               curr = curr->next;
               delete temp;
               temp = nullptr;
               size--;
               removed = true;
            }
            else // no match
            {
               prev = curr;
               curr = curr->next;
            }
         }
      }
   }
   return removed; // return true if something removed
}

// retrieve
// Description: Retrieves all websites matching search topic from the hash 
//              table. If the websites exists, the function returns true and 
//              the websites are passed back by reference to an array of
//              websites. 
// Input: searchTopic - the topic to search for
//        websites - the array of websites to be passed back
// Output: true if the websites were found, false if not
bool Table::retrieve(const char * searchTopic, Website websites[], 
                     int& num_found) const
{
   bool found = false;
   int index = hash(searchTopic); // hash the topic
   if (aTable[index]) // if the index is not null
   {
      Node * curr = aTable[index]; // set curr to the index 
      int i = 0; // index for the websites array  
      while (curr) // while curr is not null
      {
         if (strcmp(curr->data->getTopic(), searchTopic) == 0) // topic matches
         {
            websites[i] = *curr->data; // copy website to array
            i++;
            found = true; // set found to true
         }
         curr = curr->next;
      }
      num_found = i; // set num_found to the number of websites found
   }
   return found;
}

// edit
// Description: Edits a website review and rating in the hash table. 
//              If the website exists, the function returns true and the website
//              is edited. If the website does not exist, the
//              function returns false.
// Input: website - the website to be edited
// Output: true if the website was edited, false if the website does not exist
bool Table::edit(char * searchTopic, char * searchURL, char * newReview,
                 int newRating)
{
   int index = hash(searchTopic); // hash the topic
   if (aTable[index]) // if the index is not null
   {
      Node * curr = aTable[index]; // set curr to the index
      while (curr) // while curr is not null
      {
         if (strcmp(curr->data->getTopic(), searchTopic) == 0 && 
             strcmp(curr->data->getURL(), searchURL) == 0) // match
         {
            curr->data->setReview(newReview);
            curr->data->setRating(newRating);
            return true;
         }
         curr = curr->next;
      }
   }
   return false;
}

// displayAll
// Description: Displays all websites in the hash table. If the hash table is
//              empty, the function returns false. If the hash table is not
//              empty, the function returns true.
// Input: None
// Output: true if the hash table is not empty, false if the hash table is
//         empty
bool Table::displayAll() const
{
   if (size == 0) // if the hash table is empty
   {
      return false;
   }
   for (int i = 0; i < currCapacity; i++) // for each index in the table
   {
      if (aTable[i]) // chain on index
      {
         Node * curr = aTable[i]; // set curr to the index   
         while (curr) // while curr is not null
         {
            curr->data->display(); // display the website
            cout << endl;
            curr = curr->next;
         }
      }
   }
   return true;
}

// displayAll (overloaded)
// Description: Displays all websites matching search topic from the hash
//              table. If the websites exists, the function returns true and
//              the websites are displayed. If the websites do not exist, the
//              function returns false.
// Input: searchTopic - the topic to search for
// Output: true if the websites were found, false if not
bool Table::displayAll(char * searchTopic) const
{
   bool found = false;
   int index = hash(searchTopic); // hash the topic
   if (aTable[index]) // if the index is not null
   {
      Node * curr = aTable[index]; // set curr to the index
      while (curr) // while curr is not null
      {
         if (strcmp(curr->data->getTopic(), searchTopic) == 0) // match
         {
            curr->data->display(); // display the website
            cout << endl;
            found = true; // set found to true
         }
         curr = curr->next;
      }
   }
   return found;
}

// monitor
// Description: Displays the length of a chain at a given index in the hash
//              table, 0 if the index is empty, and -1 if the index is out of
//              bounds.
// Input: index - the index to be monitored
// Output: the length of the chain at the index, 0 if the index is empty, and
//         -1 if the index is out of bounds
int Table::monitor(int index) const
{
   if (index < 0 || index >= currCapacity) // if the index is out of bounds
   {
      return -1;
   }
   if (!aTable[index]) // if the index is empty
   {
      return 0;
   }
   int length = 0;
   Node * curr = aTable[index]; // set curr to the index
   while (curr) // while curr is not null
   {
      length++;
      curr = curr->next;
   }
   return length;
}

// getSize()
// Description: Returns the size of the hash table.
// Input: None
// Output: the size of the hash table
int Table::getSize() const
{
   return size;
}

// getCapacity()
// Description: Returns the capacity of the hash table.
// Input: None
// Output: the capacity of the hash table
int Table::getCapacity() const
{
   return currCapacity;
}

// loadFromFile
// Description: Loads websites from file into the hash table. Uses the
//              insert function to insert the websites into the hash table.
// Input: filename - the name of the file to be loaded
// Output: none

void Table::loadFromFile(const char* filename)
{
   // int count = 0;
   ifstream inFile(filename);
   if (!inFile) // if the file cannot be opened
   {
      cout << "Error opening file" << endl;
      return;
   }

   char topic[MAX_CSTRING], url[MAX_CSTRING], summary[MAX_PARAGRAPH], 
        review[MAX_PARAGRAPH];

   int rating = 0;

   while (inFile.getline(topic, MAX_CSTRING)) // while there is data to read
   {
      if (strlen(topic) == 0) // blank line encountered
      {
         continue;
      }

      inFile.getline(url, MAX_CSTRING);
      inFile.getline(summary, MAX_PARAGRAPH);
      inFile.getline(review, MAX_PARAGRAPH);
      inFile >> rating;
      inFile.ignore(); // ignore newline

      // init new website
      Website* website = new Website();
      // set website data
      website->setTopic(topic);
      website->setURL(url);
      website->setSummary(summary);
      website->setReview(review);
      website->setRating(rating);

      insert(*website); // insert into hash table
      
      //PRINT STATEMENTS FOR TESTING
      /*
      count++;
      cout << "Website " << count << " added." << endl;
      cout << *website << endl;
      */

      //Deallocate memory
      delete website; // delete website
      website = nullptr;
   }
}

