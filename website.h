/******************************************************************************
# Program Desc.:      This program is a website bookmarking program. The program
#                     implements a hash table using chaining (pointer array of 
#                     linked lists) to store website information.
# File:               website.h
# File Description:   Header file for the Website ADT class. Contains the
#                     website data and functions to manipulate the data.
# Input:              None
# Output:             None
#******************************************************************************/
#ifndef WEBSITE_H
#define WEBSITE_H

#include <iostream>
#include <iomanip> // for formatting output - setw()
#include <cstring>

using namespace std;

// Global Consts 
const int MAX_CSTRING = 150; // for topic & url
const int MAX_PARAGRAPH = 1000; // for summary and review

class Website
{
    public:
        Website();
        Website(const Website & website);
        ~Website();
        void destroy();

        void display();
        /*
        void displayTopic();
        void displayURL();
        void displaySummary();
        void displayReview();
        */
        void setTopic(char * topic);
        void setURL(char * url);
        void setSummary(char * summary);
        void setReview(char * review);
        void setRating(int rating);
        const char * getTopic() const;
        const char * getURL() const;
        const char * getSummary() const;
        const char * getReview() const;
        const int getRating() const;

        const Website& operator= (const Website & website);
        friend ostream & operator << (ostream & out, const Website & website);
        friend bool operator== (const Website &lhs, const Website &rhs);

    private:
        char * topic = nullptr;
        char * url = nullptr;
        char * summary = nullptr;
        char * review = nullptr;
        int rating; // init as -1
        
        void init(char * topic, char * url, char * summary, char * review);
        // maybe not needed
};

#endif
