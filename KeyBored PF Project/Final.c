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
void ActuallyChangingTheme(char bg_colour, char text_colour);
void InputtingNewTheme();
void displayLeaderboard();
void updatingLeaderboard(float wpm, float accuracy, char* playerName);
void readingLeaderboard();
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
	
	int check;
    int choice;
    do {
    	printf("\n\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
        printf("\nMENU:\n");
        printf("1. START\n");
        printf("2. INSTRUCTIONS\n");
        printf("3. LEADEBOARD\n");
        printf("4. CHANGE THEME\n");
        printf("5. CREATORS\n");
		printf("6. EXIT\n");
        printf("\n");
        
        while (1)
        {
        	printf("\nEnter your choice (1-6): ");
        	check = scanf("%d", &choice);
        	//Making sure the user of enters a valid integer...covering our corner cases!
	   		if (check == 1) 
	   		{
	   			if (choice >= 1  && choice <= 6)
	   			{
					break;
				}
				else 
				{
					printf("Please choose between 1-6. Try Again :) \n");	
					continue;
				}
				
			}
			else if (check != 1) 
			{
				printf("Please be serious, enter only an integer between 1-6 :(");
				printf("\n");
			}	
    		// Clear the input buffer to avoid infinite loop on invalid input
			fflush(stdin);
		
		}
        
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
				//LEADERBOARD
				displayLeaderboard();
				break;

            case 4:
            	//CHANGE THEME
				InputtingNewTheme();            	
                break;

			case 5:
				// CREATORS
                displayingCreators();
				break;
				
            case 6:
                // EXIT
                printf("Exiting the program.\n");
                return 0;

            default:
                printf("We're Sorry! Please enter a valid value between 1 and 6.\n");
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
		printf("\n o All the words are randomly generated, if you recieve longer words than you friends...'PLZZ DON'T BE SALTY!!!'.");
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
	    float accuracy = ((float)(wordsEntered - mistakes) / wordsEntered) * 100.0;
		printf("\n**Time Taken: %.2f seconds", timeTaken);
		printf("\n**Accuracy: %.1f Percent !!!", accuracy);
	    printf("\n**Words per Minute: %.1f wpm", wpm);
	    if (mistakes == 0) 
		{
	        printf("\n||  You're a genius, aren't you!....No mistakes!!! ||");
	    } 
		else 
		{
	        printf("\n||  Total Mistakes: %d  || \n", mistakes);
	    }
	    printf("\n\nUpdating Leaderboard...\n");
  		char playerName[50];
    	printf("Enter your Name, Sire! : ");
    	scanf("%s", playerName);
    	updatingLeaderboard(wpm, accuracy, playerName);
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//Switch case main input leke display karaiga recirds from the leaderboard.
	void displayLeaderboard() 
	{
    	printf("\n|--------LEADERBOARD--------|\n\n");
    	readingLeaderboard();
	}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////
//This will be called in the compareSentences function to have records be added to Leaderboard. 
	void updatingLeaderboard(float wpm, float accuracy, char* playerName) 
	{
    	FILE* leaderboardFile = fopen("Leaderboard.txt", "a+");
    	if (!leaderboardFile) {
    	    fprintf(stderr, "Sorry! Error opening leaderboard file.\n");
    	    return;
    	}

    	fprintf(leaderboardFile, "| Player: %s	| WPM: %.2f | Accuracy: %.1f |\n", playerName, wpm, accuracy);
	
	    fclose(leaderboardFile);
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Here we raed the leaderboard(records) from the file to be used in the display wala function.
	void readingLeaderboard() 
	{
    	FILE* leaderboardFile = fopen("Leaderboard.txt", "r");
    	if (!leaderboardFile) {
    	    printf("Leaderboard is empty :( .\n");
    	    return;
    	}
	
	    char line[100];
	    while (fgets(line, sizeof(line), leaderboardFile)) {
	        printf("%s", line);
	    }
	
	    fclose(leaderboardFile);
	}
	

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Yahan we do the processing of changing the theme!
	void ActuallyChangingTheme(char bg_colour, char text_colour) 
	{
    	// Here ham format karainge command ko to change the color.
    	char colour[50];
    	sprintf(colour, "color %c%c", bg_colour, text_colour); //Idhar what we're doing is that we giving the the command 'colour' a formaat which is 'color XY' where X=background-colour and Y=text-colour. 
	
	    // Executing command colour using function system.
	    system(colour);
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//This function is where we take the actual values/input as to what should be the new colours/theme.
	void InputtingNewTheme() 
	{
	    char bg_colour;
		char text_colour;
	
		printf("0 = Black       8 = Gray\n1 = Blue        9 = Light Blue\n2 = Green       A = Light Green\n3 = Aqua        B = Light Aqua\n4 = Red         C = Light Red\n5 = Purple      D = Light Purple\n6 = Yellow      E = Light Yellow\n7 = White       F = Bright White\n");
		printf("\n");
	
	
	    // Getting the input values from the user
	    printf("Press 0-9 or A-F: \n");
	    printf("Enter the Background colour-X and Text colour-Y: \n");
	    printf("XY\n");
		scanf(" %c%c", &bg_colour, &text_colour);
	
	
	    // Validate input
	    if ((bg_colour >= '0' && bg_colour <= '9') || (bg_colour >= 'A' && bg_colour <= 'F') &&
	        (text_colour >= '0' && text_colour <= '9') || (text_colour >= 'A' && text_colour <= 'F')) 
		{
	        // Changing our cmd theme
	        ActuallyChangingTheme(bg_colour, text_colour);
	        printf("\nEnjoy you new 'key-Bored' !!!\n");
	    } 
		else 
		{
	        printf("We're Sorry! Please enter valid color values.\n");
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
	    int scanned;
	    
	    while (1)
	    {
	    	printf("\nEnter the number of words to generate: ");
	    	scanned = scanf("%d", &numWordsToGenerate);
	    	
	    	if (scanned == 1)
	   		{
	   			if (numWordsToGenerate < 10)
	   			{
    				printf("Words cannot be less than 10. Please Try Again :) \n");
	   				printf("\n");
					continue;
				}
	    		else if (numWordsToGenerate > numWords) 
				{
    			    fprintf(stderr, "Word limit is too high! :( \n");	    		    
					printf("\n");
	    			continue;
				}
			break;
			}
			
			else if (scanned != 1) 
			{
				printf("Please be serious, enter only an integer :(");
				printf("\n");
			}
    		// Clear the input buffer to avoid infinite loop on invalid input
			fflush(stdin);
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
	