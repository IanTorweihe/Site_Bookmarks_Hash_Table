/******************************************************************************
# Program Desc.:      This program is a website bookmarking program. The program
#                     implements a hash table using chaining (pointer array of 
#                     linked lists) to store website information.
# File:               app.cpp
# File Description:   Driver program for website bookmarking program.
# Input:              User input from menu options, data for new websites
#                     and test data for loading (input.txt)
# Output:             Diplay menu options, and data for new groups and
#                     save data (output.txt)
#******************************************************************************/
#include <iostream>
using namespace std;

#include "table.h"
#include "website.h"

//Function Prototypes
void menu(Table &table);
int validateMenuOpt();
// for menu options
void addWebsite(Table &table);
void editWebsite(Table &table);
void removeWebsites(Table &table);
void displayTopicMatches(Table &table);
void displayAll(Table &table);

#include <iostream>
using namespace std;

int main()
{
   Table table;

   table.loadFromFile("input.txt"); // load test data from file

   menu(table);

   return 0;
}

//Function Definitions

// Menu function
void menu(Table &table){
   int menuOption = 0;
   while (menuOption != 9)
   {
      cout << "Website Bookmark Program" << endl
            << "1. Add new website" << endl
            << "2. Display all websites for topic" << endl
            << "3. Edit a website review and rating" << endl
            << "4. Remove 1 star or less websites" << endl
            << "5. Display all" << endl
            << "6. Exit" << endl;
            
      menuOption = validateMenuOpt();

      switch (menuOption)
      {
         case 1:
         {
            // Add new website
            addWebsite(table);
            break;
         }
         case 2:
         {
            // Display by topic
            displayTopicMatches(table);
            break;
         }
         case 3:
         {
            // Edit a website review and rating
            editWebsite(table);
            break;
         }
         case 4:
         {
            // Remove 1 star or less websites
            removeWebsites(table);
            break;
         }
         case 5:
         {
            // Display all
            displayAll(table);
            break;
         }
         case 6:
         {
            // Exit
            cout << "Exiting program..." << endl;
            exit (0);
         }
         default:
         {
            cout << "Invalid option. Please try again." << endl;
            break;
         }
      }
   }
}

//Function to return valid menu option
//Decription: Prompts user for valid menu option between 1 and 7. Returns
//            valid menu option as int or 0. Checks for invalid ints and 
//            non-integer input.
//Input: None
//Output: Valid menu option as int or 0 if invalid
int validateMenuOpt()
{
   int menuOption = 0;
   cout << "Enter menu option: ";
   cin >> menuOption;
   if (cin.fail())
   {
      cin.clear();
      cin.ignore(1000, '\n');
      return menuOption = 0; // return 0 fail
   }
   else if (menuOption < 1 || menuOption > 6)
   {
      return menuOption = 0; // return 0 fail
   }
   cin.ignore(1000, '\n');
   return menuOption; // return valid menu option
}

// addWebsite function
// Description: Prompts user for website data and adds website to 
//              hash table. TODO IF TIME: input validation and duplicate
//              rejection (if website already exists in hash table)
// Input: Table &table
// Output: None
void addWebsite(Table &table)
{
   // variables for website data
   char * topic = new char[MAX_CSTRING];
   char * URL = new char[MAX_CSTRING];
   char * summary = new char[MAX_PARAGRAPH];
   char * review = new char[MAX_PARAGRAPH];
   int rating = 0;
   Website * website = new Website;

   // display prompts and get user input
   cout << "Enter topic: ";
   cin.getline(topic, MAX_CSTRING);
   cout << "Enter URL: ";
   cin.getline(URL, MAX_CSTRING);
   cout << "Enter summary: ";
   cin.getline(summary, MAX_PARAGRAPH);
   cout << "Enter review: ";
   cin.getline(review, MAX_PARAGRAPH);
   cout << "Enter rating: ";
   cin >> rating;
   cin.ignore(1000, '\n');
   cin.clear();
   // set website data
   website->setTopic(topic);
   website->setURL(URL);
   website->setSummary(summary);
   website->setReview(review);
   website->setRating(rating);
   // add website to hash table
   table.insert(*website);
   // deallocate memory
   delete website;
   website = nullptr;
   delete [] topic;
   topic = nullptr;
   delete [] URL;
   URL = nullptr;
   delete [] summary;
   summary = nullptr;
   delete [] review;
   review = nullptr;
}


// displayTopicMatches function
// Description: Prompts user for topic. Then displays all websites with that
//              topic using overloaded display function. Notifies user if no
//              websites match topic.
// Input: Table &table
// Output: None
void displayTopicMatches(Table &table)
{
   // Search topic variable 
   char * searchTopic = new char[MAX_CSTRING];
   // Display prompt and get user input
   cout << "Enter topic: ";
   cin.getline(searchTopic, MAX_CSTRING);
   // Display all websites with matching topic
   if(!table.displayAll(searchTopic))
   {
      cout << "No websites match that topic." << endl;
   }
   // Deallocate memory
   delete [] searchTopic;
   searchTopic = nullptr;
   // Clean buffer
   cin.clear();
}

// editWebsite function
// Description: Prompts user for topic. Then adds all websites with that topic
//              to a temporary array using retrieve function. Then displays
//              all websites in the temporary array using overloaded display
//              function including index + 1 of the website in the array.
//              Prompts user for index of website to edit. Then prompts user
//              for new review and rating. Then calls edit function to edit
//              website in hash table using selected index searchTopic and 
//              searchURL
// Input: Table &table
// Output: None
void editWebsite(Table &table)
{
   //Declare variables
   char * searchTopic = new char[MAX_CSTRING];
   char * searchURL = new char[MAX_CSTRING];
   int tableCapacity = table.getCapacity();
   Website * tempArray = new Website[tableCapacity];
   int tempArraySize = 0;
   int index = 0;
   char * newReview = new char[MAX_PARAGRAPH];
   int newRating = 0;
   // Prompt user for topic
   cout << "Enter topic: ";
   cin.getline(searchTopic, MAX_CSTRING);
   cin.clear();
   // Retrieve all websites with matching topic and deepcopy to temp array
   if(!table.retrieve(searchTopic, tempArray, tempArraySize))
   {
      cout << "No websites match that topic." << endl;
   }
   else // topic match
   {
      // Display all websites with matching topic with index + 1
      for(int i = 0; i < tempArraySize; i++)
      {
         cout << i + 1 << ". ";
         tempArray[i].display();
      }
      // Prompt user for index of website to edit
      cout << "Enter index of website to edit: ";
      cin >> index;
      cin.clear();
      cin.ignore(1000, '\n');
      if(index > tempArraySize || index < 1)
      {
         cout << "Invalid index. Please try again" << endl;
         // Deallocate memory
         delete [] searchTopic;
         searchTopic = nullptr;
         delete [] searchURL;
         searchURL = nullptr;
         delete [] tempArray;
         tempArray = nullptr;
         delete [] newReview;
         newReview = nullptr;
         return;
      }
      // Prompt user for new review and rating
      cout << "Enter new review: ";
      cin.getline(newReview, MAX_PARAGRAPH);
      cin.clear();
      cout << "Enter new rating: ";
      cin >> newRating;
      cin.clear();
      cin.ignore(1000, '\n');
      // Edit website in temp array
      tempArray[index - 1].setReview(newReview);
      tempArray[index - 1].setRating(newRating);
      // copy searchTopic and searchURL from temp array
      strcpy(searchTopic, tempArray[index - 1].getTopic());
      strcpy(searchURL, tempArray[index - 1].getURL());
      // Edit website in hash table
      table.edit(searchTopic, searchURL, newReview, newRating);
      // Done
   }

   // Deallocate memory
   delete [] searchTopic;
   searchTopic = nullptr;
   delete [] searchURL;
   searchURL = nullptr;
   delete [] tempArray;
   tempArray = nullptr;
   delete [] newReview;
   newReview = nullptr;
}

// removeWebsites function
// Description: Removes all websites with a rating of 1 star or less.
// Input: Table &table
// Output: None
void removeWebsites(Table &table)
{
   if(!table.removeOneStar())
   {
      cout << "No websites to remove." << endl;
   }
   else
   {
      cout << "All websites with a rating of 1 star or less have been removed." 
           << endl;
   }
}

// displayAll function
// Description: Displays all websites in hash table using displayAll
//              function or notifies user if no websites in hash table.
//              Also displays hash table stats length of chain at each index 
//              via monitor function and total number of websites in hash table.
// Input: Table &table
// Output: None
void displayAll(Table &table)
{
   if(!table.displayAll())
   {
      cout << "No websites in hash table." << endl;
   }
   else
   {
      int capacity = table.getCapacity();
      cout << "Total websites in hash table: " << table.getSize() << endl;
      cout << "Total capacity of hash table: " << capacity << endl;
      cout << "Displaying length of chain at each index:" << endl;
      for (int i = 0; i < capacity; i++)
      {
         cout << "Index " << i << ": " << table.monitor(i) << endl;
      }
   }
}
