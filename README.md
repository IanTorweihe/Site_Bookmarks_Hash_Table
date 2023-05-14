# Website Bookmarking Program

This is a C++ program designed to manage and maintain website bookmarks. It implements a hash table using chaining (pointer array of linked lists) to store website information.

## Features

- Adding new websites with related information.
- Displaying all websites for a specific topic.
- Editing a website's review and rating.
- Removing websites with a rating of 1 star or less.
- Displaying all stored websites.

## File Structure

- `app.cpp` : This is the driver program for the website bookmarking program.
- `table.h` : This file includes the class definition for the Table class which is used to implement a hash table.
- `website.h` : This file includes the class definition for the Website class which is used to store and manage website information.

## Usage

To run this program:

1. Compile the program using a C++ compiler.
2. Run the executable created after the compilation.

The program will load test data from `input.txt` file and save data to `output.txt` file.