Running Simple Dictionary Program
Instructions for Developing and Executing Code on Replit.com

Replit.com provides a user-friendly online IDE that supports multiple programming languages, including C. To get started with your Simple Dictionary program on Replit, follow these steps:

Create a Replit Account
Navigate to Replit.com
Click on Sign up if you do not already have an account or Log in if you do.
You can sign up using an email address or through various social logins (Google, Facebook, GitHub).
Create a New Repl
Once logged in, click the "+" New Repl button.
Select C as the language from the list.
Give your repl a name, such as "linkedListWordDictionary".
Click Create Repl to set up your programming environment.
 Coding Environment
Replit will set up an IDE with an editor, console, and basic files.
By default, Replit creates a main.c file where you can start writing your code.
Developing Your Code

Copy Your Code: Start by copying the C code provided or developed earlier into the main.c file in your Replit environment.

Modify and Save: Make any necessary adjustments to ensure your code runs correctly in the online compiler. Use the file tree on the left if you need to add new files or organize your code.
Executing Your Code

Run Your Program: Use the green Run button at the top of the page to compile and execute your code. The output will appear in the console window at the bottom.

Debug and Iterate: If there are errors or if the output isn't what you expect, make the necessary corrections and run your program again.




What to Expect

When you run the program, you will be presented with a menu that includes several options:

1. Add Sentence to Dictionary: Enter a sentence, and the program will parse each word and add it to the dictionary.
2. Display Complete Dictionary: Displays all words currently stored in the dictionary.
3. Lookup Word in Dictionary: Allows you to search for words based on their first four letters.
4. Add Word to Dictionary: Directly add a single word to the dictionary.
5. Delete Complete Dictionary: Clears all entries from the dictionary.
6. Delete Word from Dictionary: Removes a specific word, with options for case-sensitive or case-insensitive deletion.
7. Exit: Exits the program.

Sample Input 

Hello, world! This is a test, including numbers like 123 and special characters $%^&*(). Testing hyphenated-words and it's not a contraction's error.

Sample Output
Creating new Dictionary 





Adding Sentence to Dictionary



Displaying Dictionary






Lookup Word in Dictionary - Scenario 1


Lookup Word in Dictionary - Scenario 2

Add Word to Dictionary





Add Word to Dictionary - Duplicate word scenario 


Delete complete dictionary 


Delete word from dictionary - Scenario 1


Delete word from dictionary - Scenario 2


Adding Sentences - Adding to existing dictionary Scenario



Deleting complete Dictionary


Terminating program.


Constraints : Avoiding strtok and Dynamic Memory Allocation

In the development of the Simple Dictionary program, certain constraints such as avoiding strtok() for string manipulation and not using dynamic memory allocation are mentioned.

Avoiding strtok

strtok() is commonly used in C to split strings into tokens based on specified delimiters.


To handle string parsing without strtok, a manual approach was adopted:

Character-by-Character Parsing: The program reads the input sentence character by character, using simple conditions to identify delimiters (spaces, punctuation etc.). When a delimiter is found, it concludes the current word and processes it accordingly.
Direct Extraction: Each word is extracted directly into a temporary buffer (currentWord) as characters are read. When a delimiter or end of string is detected, the word is terminated with a null character, and then processed

Avoiding Dynamic Memory Allocation

Dynamic memory allocation, while powerful, introduces complexity such as managing memory allocation and deallocation, potential memory leaks,

Approach Adopted
Static Allocation: The program uses statically allocated arrays for the dictionary. The WordNode array (dictionary) is defined with a maximum size (MAX_WORDS), which limits the number of words but eliminates the need for dynamic memory management.
Fixed Size Elements: Each word's representation in the dictionary (firstFour field of WordNode) is limited to a fixed size (WORD_LENGTH), simplifying memory usage and ensuring predictable memory footprint.
Linked List Management: The linked list used to manage words in the dictionary does not require dynamic nodes thanks to the static next indices within each statically allocated WordNode.

Challenging Parts
Case Sensitivity: Implementing both case-sensitive and case-insensitive search and delete functionalities required careful attention to ensure that string comparisons were handled correctly.
Memory Management: Ensuring that the dictionary efficiently manages memory without leaks or overflows when adding and deleting words was challenging, especially considering the limitations of fixed array sizes in C.

Easy Parts
Data Structures: The basic operations like adding and traversing the list are simple and well-understood.
Menu System: Designing a user-friendly menu system was quite easy as it involves basic input/output operations.
Error Handling: Robustly handling user input and potential errors during dictionary operations (such as trying to delete from an empty dictionary) was straightforward yet required thorough testing.

Detailed Functional Overview
Add Sentence to Dictionary

Input: The input can be any sentence containing letters from A-Z, a-z, 0-9, and special characters such as ', -, $, _, %, !, @, #, and ?. All other characters will be considered delimiters, and the words will be divided and then stored in the dictionary.

Output: A dictionary is created with the first four letters of each word and the length of each word.

Process: 
The program reads the input sentence character by character. After creating a 4-letter word from the given word, it checks whether the dictionary is full. 
It then checks whether a case-sensitive version of the same 4-lettered word is present in the dictionary. For example, if the input is "test," it only checks for the presence of "test" and not variations like "TEST", "Test", "tESt", etc. 
If it is present, the program returns and displays a message indicating a duplicate word was found in the dictionary. Otherwise, it writes the 4-letter word and length into the first empty struct, which is present at the last non-null index. 
After the entire sentence is processed, the sortDictionary() function is executed. The sorted dictionary is formatted with special characters -> 0-9 -> alphabetically sorted mixture of small and capital letters.

Print Dictionary

Input: None.

Output: Prints the complete sorted dictionary.

Process: The program traverses until a null entry is found.
Look Up Word in Dictionary

Input: A word to look into dictionary

Output: Occurrences present in the dictionary.

Process: 
This method asks whether to look for the word in case-sensitive or case-insensitive mode. 
This method accepts any word up to the maximum length defined in the code, extracts the first four letters. 
If case-sensitive mode is selected and the word to look up is "test," it only finds and prints "test" from the dictionary. 
If case-insensitive mode is selected and the word to look up is "test," it matches with all variations of "test" and prints all of them, e.g., "test", "Test", "TEST", "tESt".

Add Word to Dictionary

Input: A new word to add to the dictionary.

Output: None.

Process: 
This method accepts any word up to the maximum length defined in the code, extracts the first four letters, checks if the exact same word is present in the dictionary, and if so, displays a message and returns without adding the word. 
If the word is not present in the dictionary, it adds the word, sorts the dictionary, and then returns.

Delete Complete Dictionary

Input: None.

Output: Deletes the entire dictionary.

Process: Cleans resources and resets all global variables so that a new dictionary can be created from scratch with a complete reset.

Delete Word from Dictionary

Note: This was not mentioned in the original documentation, but it was developed as an interesting feature to work on, and I became passionate about implementing all features for the dictionary.

Input: A word to delete from the dictionary.

Output: Successfully deletes the word from the dictionary if present; otherwise, no changes are made.

Process: 
This function also has two modes: case-sensitive and case-insensitive. 
If case-sensitive is selected and the word to delete is "test", it matches this word and then deletes its entry from the dictionary, while other variations remain. 
If case-insensitive mode is selected and the word to delete is "test", it finds all entries similar to "test".
 In this case, four entries are found. It prints all entries, then asks the user whether to delete all entries.
 If the user agrees, then all entries are deleted, otherwise nothing is deleted, and the loop continues.

Exit

Input: None.

Output: None.

Process: When this option is selected, the program terminates.



