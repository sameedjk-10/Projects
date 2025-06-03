#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>  

#define MAX_WORD_LENGTH 100
#define MAX_WORDS 500
#define ENTER 10

// AlL Functions used in typing tutor prototypes:
void displayingInstructions();
void displayingCreators();
int getRandomNumber(int min, int max);
void generateRandomSentence(char** words, int numWordsToGenerate, int numWords);
char** readWordsFromFile(const char* filename, int* numWords);
void compareSentences(char** originalSentence, char (*userInput)[MAX_WORD_LENGTH], int numWordsToGenerate, int wordsEntered, float timeTaken);
void Typing_Tutor();

	int main()
	{
    srand((unsigned int)time(NULL));
	
	#include <stdio.h>

   printf("  _                     ____                     _ \n");
    printf(" | |                   |  _ \\                   | |\n");
    printf(" | | _____ _   _ ______| |_) | ___  _ __ ___  __| |\n");
    printf(" | |/ / _ \\ | | |______|  _ < / _ \\| '__/ _ \\/ _` |\n");
    printf(" |   <  __/ |_| |      | |_) | (_) | | |  __/ (_| |\n");
    printf(" |_|\\_\\___|\\__, |      |____/ \\___/|_|  \\___|\\__,_|\n");
    printf("            __/ |                                  \n");
    printf("           |___/                                   \n");
	
    int choice;
    do {
    	printf("\n\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
        printf("\nMENU:\n");
        printf("1. START\n");
        printf("2. INSTRUCTIONS\n");
        printf("3. CREATORS\n");
        printf("4. EXIT\n");
        printf("\n\n\n");
        printf("Enter your choice (1-4): ");
        scanf("%d", &choice);
		printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n");
		
        switch (choice) 
		{
            case 1:
                // START
                Typing_Tutor();
                break;

            case 2:
                // INSTRUCTIONS
                displayingInstructions();
                break;

            case 3:
                // CREATORS
                displayingCreators();
                break;

            case 4:
                // EXIT
                printf("Exiting the program.\n");
                return 0;

            default:
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
        }
    } while (1);

    return 0;
	}
///////////////////////////////////////////////////////////////////////////////////////////////////
// Menu ka INSTURCTIONN wala fucntion hoga yeh.
	void displayingInstructions() 
	{
    	printf("\n--------INSTRUCTIONS--------\n");
    	printf("\n o Tell us how many words do you want your Typing Test to be.");
    	printf("\n o The timer starts as soon as the 'Original Sentence' is printed.....'BETTER BE QUICK!!!'.");
    	printf("\n o You can only recieve your 'Result' or return to the MENU when you have completed your Typing Test.");
		printf("\n o All the words are randomly generated, if you happen to recieve longer words than you friends....'PLZZ DON'T BE SALTY!!!'.");
    	printf("\n o Hit 'ENTER' instantly when your test is complete to recieve your 'Results'.\n");
    	
	}
//////////////////////////////////////////////////////////////////////////////////////////////////
// Hamare group member are here.
	void displayingCreators() 
	{
    	printf("\n--------CREATORS--------\n");
		printf("**Muhammad Shehryar Choudhary** \nNU-ID: 23K-0503 \n**Krrish Kumar** \nNU-ID: 23K-0641 \n**Muhammad Sameed Jamal Khan** \nNU-ID:23K-0812\n\n");
	}
//////////////////////////////////////////////////////////////////////////////////////////////////
// Getting a random number to be used for random words selection.	
	int getRandomNumber(int min, int max) 
	{
	    return rand() % (max + 1);
	}
//////////////////////////////////////////////////////////////////////////////////////////////////
//Idhar we use the random number generated in the getRandomNumber function to pick a random word from the words.txt file and store it in a string.
	char** readWordsFromFile(const char* filename, int* numWords) 
	{
    	FILE* file = fopen(filename, "r");
    	if (!file) 
		{
    	    fprintf(stderr, "Error opening file: %s\n", filename);
    	    exit(EXIT_FAILURE);
    	}

    	*numWords = 0;
    	char buffer[MAX_WORD_LENGTH];

    	while (fscanf(file, "%s", buffer) == 1) 
		{
    	    (*numWords)++;
    	}

    	char** words = (char**)malloc(*numWords * sizeof(char*));
    	rewind(file);

    	for (int i = 0; i < *numWords; ++i) 
		{
    	    words[i] = (char*)malloc(MAX_WORD_LENGTH * sizeof(char));
    	    fscanf(file, "%s", words[i]);
    	}

    	fclose(file);
    	return words;
	}	
	
//////////////////////////////////////////////////////////////////////////////////////////////////
//Here we are printing that random word from the word[] wali string.
	void generateRandomSentence(char** words, int numWordsToGenerate, int numWords) 
	{
	    printf("\nOriginal Sentence: ");
	    for (int i = 0; i < numWordsToGenerate; ++i) 
		{
	        int randomIndex = getRandomNumber(0, numWords - 1);
	        printf("%s ", words[randomIndex]);
    	}
	    printf("\n");
	}
//////////////////////////////////////////////////////////////////////////////////////////////////
//Abb idhar hamara code compare karta hai user ke re-typed words ko from userInput[] string with the originalSentence[] string jis main words[] ke duplicated words hain.
	void compareSentences(char** originalSentence, char (*userInput)[MAX_WORD_LENGTH], int numWordsToGenerate, int wordsEntered, float timeTaken) 
	{
	    int mistakes = 0;
    	float wpm = (wordsEntered / timeTaken) * 60;

    	// Determine the minimum of numWordsToGenerate and wordsEntered
	    int minWords = (numWordsToGenerate < wordsEntered) ? numWordsToGenerate : wordsEntered;
	
	    for (int i = 0; i < minWords; i++) 
		{
	        if (strcmp(originalSentence[i], userInput[i]) != 0) 
			{
	            printf("Mistake @ word # %d ---------------------> Correct: %s --------> Input: %s\n", i + 1,
	                   originalSentence[i], userInput[i]);
	            mistakes++;
	        }
	    }
		printf("\n**Time Taken: %.2f seconds", timeTaken);
		printf("\n**Accuracy: %.1f Percent !!!", ((float)(wordsEntered - mistakes) / wordsEntered) * 100.0);
	    printf("\n**Words per Minute: %.1f wpm", wpm);
	    if (mistakes == 0) 
		{
	        printf("\n||  You're a genius, aren't you!....No mistakes!!! ||");
	    } 
		else 
		{
	        printf("\n||  Total Mistakes: %d  || \n", mistakes);
	    }
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//Our main TYPING_TUTOR code function that is our actual typing tutor!
	void Typing_Tutor() 
	{
	    srand((unsigned int)time(NULL));
	
	    int numWords;
	    char** words = readWordsFromFile("words.txt", &numWords);

	    int numWordsToGenerate;
	    printf("Enter the number of words to generate: ");
	    scanf("%d", &numWordsToGenerate);
	
	    if (numWordsToGenerate > numWords) 
		{
	        fprintf(stderr, "Word limit is too high!\n");
	        return;
	    }

	    char** originalSentence = (char**)malloc(numWordsToGenerate * sizeof(char*));
	    printf("\nOriginal Sentence: \n");
	    for (int i = 0; i < numWordsToGenerate; ++i) 
		{
	        int randomIndex = getRandomNumber(0, numWords - 1);
	        originalSentence[i] = strdup(words[randomIndex]);
	        printf("%s ", originalSentence[i]);
	    }
	    printf("\n");
	
	    // Allow the user to re-type the sentence
	    char userInput[MAX_WORDS][MAX_WORD_LENGTH];
	    int wordsEntered = 0;
	
	    printf("\nHERE WE GO! START! : \n");
	
	    clock_t start, end;
	    start = clock();
	
	    for (int i = 0; i < numWordsToGenerate; ++i) 
		{
	        int j = 0;
	
	        // Read characters until a non-space character or Enter key is encountered
	        while (1) 
			{
    	        char ch = getchar();
	
	            if (ch == ' '|| ch == ENTER || ch == EOF)
				{
	                // Check if the word is not empty (to avoid leading spaces)
	                if (j > 0) 
					{
	                    break;
	                }
	            } 
				else 
				{
	                userInput[wordsEntered][j++] = ch;
	            }
	        }
	
	        userInput[wordsEntered][j] = '\0'; // Null-terminate the string
	
	        
	
	        wordsEntered++;
	    }
	
	    end = clock();
	    float timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC;
	
	    
	    printf("\n");
	
	    // Compare the original and user-typed sentences
	    printf("|---------Result---------|\n");
	    compareSentences(originalSentence, userInput, numWordsToGenerate, numWordsToGenerate, timeTaken);
	
	    // Free allocated memory
	    for (int i = 0; i < numWordsToGenerate; ++i) 
		{
	        free(originalSentence[i]);
	    }
	    free(originalSentence);
	
	    for (int i = 0; i < numWords; ++i) 
		{
	        free(words[i]);
	    }
	    free(words);
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
	