#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <strings.h> // for strcasecmp on POSIX systems

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 50
#define WORD_LENGTH 4

typedef struct {
    char firstFour[WORD_LENGTH + 1];  // stores the first four letters
    int length;                       // stores the word length
    int next;                         // index of the next node
} WordNode;

WordNode dictionary[MAX_WORDS];
int numWords = 0;
int first = -1;
int caseSensitive = 0;
int resetDictionary = 0;

void addWordUnsorted(const char *word, int wordLen) {
    if (numWords >= MAX_WORDS) {
        printf("Dictionary full.\n");
        return;
    }

    strncpy(dictionary[numWords].firstFour, word, WORD_LENGTH);
    dictionary[numWords].firstFour[WORD_LENGTH] = '\0';
    dictionary[numWords].length = wordLen;
    dictionary[numWords].next = -1;

    if (first == -1) {
        first = numWords;
    } else {
        int curr = first;
        while (dictionary[curr].next != -1) {
            curr = dictionary[curr].next;
        }
        dictionary[curr].next = numWords;
    }
    numWords++;
}

void sortDictionary() {
    int sorted = -1;
    int current = first;

    while (current != -1) {
        int next = dictionary[current].next;
        int prev = -1;
        int sortedIndex = sorted;

        while (sortedIndex != -1) {
            int cmpResult = caseSensitive ? 
                strcmp(dictionary[sortedIndex].firstFour, dictionary[current].firstFour) :
                strcasecmp(dictionary[sortedIndex].firstFour, dictionary[current].firstFour);

            if (cmpResult > 0) {
                break;
            }
            prev = sortedIndex;
            sortedIndex = dictionary[sortedIndex].next;
        }

        if (prev == -1) {
            dictionary[current].next = sorted;
            sorted = current;
        } else {
            dictionary[current].next = dictionary[prev].next;
            dictionary[prev].next = current;
        }
        current = next;
    }
    first = sorted;
}

// void parseAndAddWords() {
//     char sentence[1024];
//     printf("Enter words to add (alphanumeric and selected special characters are allowed): ");
//     fgets(sentence, sizeof(sentence), stdin);
//     sentence[strcspn(sentence, "\n")] = '\0';  // Remove the newline character

//     char currentWord[MAX_WORD_LENGTH];
//     int len = 0;
//     char *p = sentence;

//     while (*p) {
//         // Check if the character should be part of a word
//         if (isalnum(*p) || *p == ',' || *p == '\'' || *p == '&' || *p == '$' || *p == '-') {
//             if (len < MAX_WORD_LENGTH - 1) {
//                 currentWord[len++] = *p;  // Add character to current word
//             }
//         } else {
//             // Word boundary is found; process the current word if it's not empty
//             if (len > 0) {
//                 currentWord[len] = '\0';  // Null-terminate the current word
//                 addWordUnsorted(currentWord, len);
//                 len = 0;  // Reset length for the next word
//             }
//         }
//         p++;  // Move to the next character
//     }

//     // Add the last word in the sentence if there is no trailing delimiter
//     if (len > 0) {
//         currentWord[len] = '\0';
//         addWordUnsorted(currentWord, len);
//     }

//     sortDictionary();
// }

void parseAndAddWords() {
    char sentence[1024];
    printf("Enter words to add: ");
    fgets(sentence, sizeof(sentence), stdin);
    sentence[strcspn(sentence, "\n")] = '\0'; // Remove the newline character

    char currentWord[MAX_WORD_LENGTH];
    int len = 0;
    char *p = sentence;

    while (*p) {
        // Include only alphabetic characters in words, allow apostrophes and hyphens within words
        if (isalnum(*p) || *p == '\''  || *p == '-' || *p == '&' || *p == '$' || *p == '-' || *p == '_') {  
            if (len < MAX_WORD_LENGTH - 1) {
                currentWord[len++] = *p;
            }
        } else {
            // Word boundary is found; process the current word if it's not empty
            if (len > 0) {
                currentWord[len] = '\0';  // Null-terminate the current word
                addWordUnsorted(currentWord, len);
                len = 0;  // Reset length for the next word
            }
        }
        p++;  // Move to the next character
    }

    if (len > 0) {  // Add the last word if there is no trailing delimiter
        currentWord[len] = '\0';
        addWordUnsorted(currentWord, len);
    }

    sortDictionary();  // Sort the dictionary after all words are added
}


void printDictionary() {
    int index = first;
    printf("---------------------------------\n");
    if(index == -1) {
        printf("Empty List\n");
    } else {
        while (index != -1) {
            printf("Word: %s, Length: %d\n", dictionary[index].firstFour, dictionary[index].length);
            index = dictionary[index].next;
        }
    }
    printf("---------------------------------\n");
}

void clearDictionary() {
    numWords = 0;
    first = -1;
}

void lookupWord() {
    char searchKey[WORD_LENGTH + 1];
    printf("Enter first four letters of a word to lookup: ");
    scanf("%4s", searchKey);
    getchar();  // Consume newline

    int found = 0;
    int curr = first;
    while (curr != -1) {
        if ((caseSensitive ? strncmp : strncasecmp)(dictionary[curr].firstFour, searchKey, WORD_LENGTH) == 0) {
            printf("Word: %s, Length: %d\n", dictionary[curr].firstFour, dictionary[curr].length);
            found = 1;
        }
        curr = dictionary[curr].next;
    }

    if (!found) {
        printf("No words found starting with '%s'.\n", searchKey);
    }
}

int main() {
    
    printf("Set dictionary mode (0 for Case-Insensitive, 1 for Case-Sensitive): ");
    scanf("%d", &caseSensitive);
    getchar(); // Consume newline
    

    int choice;
    do {
        printf("1. Create Dictionary\n2. Display Dictionary\n3. Delete\n4. Add Word\n5. Lookup\n6. Exit\nChoose an option: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                if (first != -1) {
                    printf("Dictionary already contains words.\n");
                    printf("Do you want to reset and create a new dictionary? (1 for Yes, 0 for No): ");
                    scanf("%d", &resetDictionary);
                    getchar(); 

                    if (resetDictionary) {
                        clearDictionary();  
                        printf("Dictionary has been reset.\n");
                    } else {
                        printf("Continuing with the existing dictionary.\n");
                    }
                } else {
                    printf("Creating new dictionary...\n");
                }
                parseAndAddWords();  
                break;
            case 2:
                printDictionary();
                break;
            case 3:
                clearDictionary();
                break;
            case 4:
                parseAndAddWords();
                break;
            case 5:
                lookupWord();
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please choose again.\n");
        }
    } while (choice != 6);

    return 0;
}
               
/*

*/