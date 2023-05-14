/******************************************************************************
# Program Desc.:      This program is a website bookmarking program. The program
#                     implements a hash table using chaining (pointer array of 
#                     linked lists) to store website information.
# File:               website.cpp
# File Description:   Implementation file for the Website ADT class. Contains 
#                     the website data and functions to manipulate the data.
# Input:              None
# Output:             None
#******************************************************************************/
#include "website.h"

using namespace std;

// Default constructor
Website::Website()
{
   topic = nullptr;
   url = nullptr;
   summary = nullptr;
   review = nullptr;
   rating = -1;
}

// Copy constructor
// Description: Copies the website data from the website passed in
//              into the new website. Uses overloaded assignment
//              operator.
Website::Website(const Website & website)
{
   *this = website;
}

// Destructor
Website::~Website()
{
   destroy();
}

// Destroy
// Description: Deallocates all memory associated with the website
//              then sets all pointers to nullptr. First checks if
//              the website has been initialized.
// Input: None
// Output: None
void Website::destroy()
{
   if (topic)
   {
      delete [] topic;
      topic = nullptr;
   }
   if (url)
   {
      delete [] url;
      url = nullptr;
   }
   if (summary)
   {
      delete [] summary;
      summary = nullptr;
   }
   if (review)
   {
      delete [] review;
      review = nullptr;
   }
   rating = -1;
}

// Display
// Description: Displays all website data. Uses overloaded ostream
//              operator to display the website data. 
// Input: None
// Output: None
void Website::display()
{
   cout << *this;
}

// ACCESSORS

// Set Topic
// Description: Sets the topic of the website. First checks if the
//              topic has been initialized. If so, it deletes the
//              topic and sets the pointer to nullptr. Then it
//              allocates memory for the topic and copies the
//              topic into the website.
// Input: char * topic
// Output: None
void Website::setTopic(char * topic)
{
   if (this->topic) // if topic is not null
   {
      delete [] this->topic;
      this->topic = nullptr;
   }
   this->topic = new char[strlen(topic) + 1];
   strcpy(this->topic, topic);
}

// Set URL
// Description: Sets the URL of the website. First checks if the
//              URL has been initialized. If so, it deletes the
//              URL and sets the pointer to nullptr. Then it
//              allocates memory for the URL and copies the
//              URL into the website.
// Input: char * url
// Output: None
void Website::setURL(char * url)
{
   if (this->url) // if url is not null
   {
      delete [] this->url;
      this->url = nullptr;
   }
   this->url = new char[strlen(url) + 1];
   strcpy(this->url, url);
}

// Set Summary
// Description: Sets the summary of the website. First checks if the
//              summary has been initialized. If so, it deletes the
//              summary and sets the pointer to nullptr. Then it
//              allocates memory for the summary and copies the
//              summary into the website.
// Input: char * summary
// Output: None
void Website::setSummary(char * summary)
{
   if (this->summary) // if summary is not null
   {
      delete [] this->summary;
      this->summary = nullptr;
   }
   this->summary = new char[strlen(summary) + 1];
   strcpy(this->summary, summary);
}

// Set Review
// Description: Sets the review of the website. First checks if the
//              review has been initialized. If so, it deletes the
//              review and sets the pointer to nullptr. Then it
//              allocates memory for the review and copies the
//              review into the website.
// Input: char * review
// Output: None
void Website::setReview(char * review)
{
   if (this->review) // if review is not null
   {
      delete [] this->review;
      this->review = nullptr;
   }
   this->review = new char[strlen(review) + 1];
   strcpy(this->review, review);
}

// Set Rating
// Description: Sets the rating of the website (1-5)
// Input: int rating
// Output: None
void Website::setRating(int rating)
{
   this->rating = rating;
}

// ACCESSORS

// Get Topic
// Description: Returns the topic of the website. Const so
//              it does not modify the website data.
// Input: None
// Output: char * topic
const char * Website::getTopic() const
{
   return topic;
}

// Get URL
// Description: Returns the URL of the website. Const so
//              it does not modify the website data.
// Input: None
// Output: char * url
const char * Website::getURL() const
{
   return url;
}

// Get Summary
// Description: Returns the summary of the website. Const so
//              it does not modify the website data.
// Input: None
// Output: char * summary
const char * Website::getSummary() const
{
   return summary;
}

// Get Review
// Description: Returns the review of the website. Const so
//              it does not modify the website data.
// Input: None
// Output: char * review
const char * Website::getReview() const
{
   return review;
}

// Get Rating
// Description: Returns the rating of the website. Const so
//              it does not modify the website data.
// Input: None
// Output: int rating
const int Website::getRating() const
{
   return rating;
}

// assignment operator overload
// Description: Overloads the assignment operator to copy
//              the data from one website to another.
// Input: const Website & website
// Output: Website & website
const Website & Website::operator=(const Website & website)
{
   if (this != &website)
   {
      destroy();
      setTopic(website.topic);
      setURL(website.url);
      setSummary(website.summary);
      setReview(website.review);
      setRating(website.rating);
   }
   return *this;
}

// ostream operator overload (NO OUTPUT FORMATTING)
// Description: Overloads the ostream operator to display
//              the website data. Only displays cstring data
//              if it is not nullptr. Else displays "N/A".
// Input: ostream & out, const Website & website
// Output: ostream & out

ostream & operator<<(ostream & out, const Website & website)
{
   out << "Topic: ";
   if (website.topic)
      out << website.topic << endl;
   else
      out << "N/A" << endl;
   out << "URL: ";
   if (website.url)
      out << website.url << endl;
   else
      out << "N/A" << endl;
   out << "Summary: ";
   if (website.summary)
      out << website.summary << endl;
   else
      out << "N/A" << endl;
   out << "Review: ";
   if (website.review)
      out << website.review << endl;
   else
      out << "N/A" << endl;
   out << "Rating: ";
   if (website.rating != -1)
      out << website.rating << endl;
   else
      out << "N/A" << endl;
   return out;
}


// ostream operator overload (WITH OUTPUT FORMATTING - FIX IF TIME)
// Description: Overloads the ostream operator to display
//              the website data. Only displays cstring data
//              if it is not nullptr. Else displays "N/A".
// Input: ostream & out, const Website & website
// Output: ostream & out
/*
ostream & operator<<(ostream & out, const Website & website)
{
   int width = 30; // width of the output
   out << "Topic: ";
   if (website.topic)
   {
      out << setw(width) << left << website.topic << endl;
   }
   else
   {
      out << "N/A" << endl;
   }

   out << "URL: ";
   if (website.url)
   {
      out << setw(width) << left << website.url << endl;
   }
   else
   {
      out << "N/A" << endl;
   }

   out << "Summary: ";
   if (website.summary)
   {
      out << setw(width) << left << website.summary << endl;
   }
   else
   {
      out << "N/A" << endl;
   }

   out << "Review: ";
   if (website.review)
   {
      out << setw(width) << left << website.review << endl;
   }
   else
   {
      out << "N/A" << endl;
   }

   out << "Rating: ";
   if (website.rating != -1)
      out << website.rating << endl;
   else
      out << "N/A" << endl;

   return out;
}
*/


// equals operator overload
// Description: Overloads the equals operator to compare
//              the data of two websites. Returns true if
//              URL is equal. Returns false if not equal.
//              Guards against nullptr.
// Input: const Website & lhs rhs
// Output: bool true or false if equal or not equal respectively
bool operator==(const Website & lhs, const Website & rhs)
{
   if (lhs.url && rhs.url) // if both are not null
      return (strcmp(lhs.url, rhs.url) == 0); // if equal return true
   else
      return false; // if not equal return false
}

