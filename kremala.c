#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
char *wordL[]={"Amsterdam", "Athens", "Berlin", "Bratislava", "Brussels", "Bucharest", "Budapest", "Copenhagen", "Dublin", "Helsinki", "Lisbon", "Ljubljana", "London", "Luxembourg", "Madrid", "Nicosia", "Oslo", "Paris", "Prague", "Riga", "Rome", "Sofia", "Stockholm", "Tallinn", "Valletta", "Vienna", "Vilnius", "Warsaw", "Zagreb"};//array with europian capital cities

char *Random() { // random choose europian capital city
    srand(time(NULL));
    int sizeL = sizeof(wordL) / sizeof(wordL[0]);
    int index = rand() % sizeL;
    return wordL[index];
}
int main() {
    char name[50];//user name 
    int maxTries = 10; // max tries
    int maxWords = 3; // max words the user can guess
    int current = 0; // the number of the currend word 
    int triesUser = 0; // user tries that have been made
    int tries=0;//tries of the current word
    int words=0;//words which user found
    
    printf("welcome to the game!\n");
    printf("give me your name:\n");
    scanf("%s",&name);

    int playAg=1;//flag to control if play again

    while (current < maxWords && playAg) {
        char *word = Random(); // random word which was selected
        int Length = strlen(word); // length word
        char guessedWord[Length]; // chart with condition of the word 
        char guessedCharacters[26]; // chart with guessed characters 
        int wordTries = 0; // tries of the current word
        int lives = maxTries;//tries which are left for the word
        int correctlyGuessed = 0; // Flag to track if the word was correctly guessed

        // initialization  guessedWord with '_'
        for (int i = 0; i < Length; i++) {
            guessedWord[i] = '_';
        }
        guessedWord[Length] = '\0'; // termination string

        // game cycle for each word
        while (wordTries < maxTries) {
            printf("condition: %s\n", guessedWord); // print status
            printf("lives:%d\n",lives);

            // import features from the user
            char guess;
            printf("give me a character: ");
            scanf(" %c", &guess);
            lives--;

            // Check if the character has already been guessed
            int alreadyGuessed = 0;
            for (int i = 0; i < tries; i++) {
                if (guessedCharacters[i] == guess) {
                    alreadyGuessed = 1;
                    break;
                }
            }

            //if user give same character
            if (alreadyGuessed) {
                printf("You have already guessed this character!\n");
                continue;
            }

            guessedCharacters[tries++] = guess; //Record the character as guessed

            // Check if the character exists in the word
            int found = 0;
            for (int i = 0; i < Length; i++) {
                if (tolower(word[i]) == tolower(guess)) {
                    guessedWord[i] = word[i];
                    found = 1;
                }
            }

            if (!found) {//wrong character
                printf("this character doesn't exist in the word.\n");
            } else {//right character
                printf("Congrutsulation!\n");
            }

            // Check if the player has found all the characters
            int allGuessed = 1;
            for (int i = 0; i < Length; i++) {
                if (guessedWord[i] == '_') {
                    allGuessed = 0;
                    break;
                }
            }

            if (allGuessed) {//if user guessed all characters
                printf("Congratulations! You guessed this word \"%s\" with %d Tries!\n", word, wordTries + 1);
                words++;
                current++;
                correctlyGuessed=1;
                break; // output for that word
            }
            // if user run out tries
            if (lives == 0) {
                printf("doesn't exist lives! \"%s\". Right word: %s\n", word, word);
                current++;
                break; //move on to the next word
            }// If the user can try for the next word and the current word was correctly guessed

             if (current < maxWords && words < maxWords && correctlyGuessed) {
               printf("\nTry another word with 10 Tries!\n\n");
             }

            wordTries++;

            // if user run out tries
            if (wordTries == maxTries) {
                printf("Sorry, doesn't exists tries \"%s\". Right word: %s\n", word, word);
                current++;
            }
        }

        // if the user can try for the next word
        if (current < maxWords-1 || words < maxWords) {
            char desicion;
            printf("Do you want play again?(Y/N):");
            scanf(" %c", &desicion);
            getchar();

            if(tolower(desicion)!='Y'){
                playAg=0;
            }
           
        }
        current++;
    }

    printf("Game over!\n");
    return 0;
}