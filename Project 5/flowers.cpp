#include "utilities.h"
#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

const int MAXWORDS = 9000;
const int MAXINPUT = 99;

const char WORDFILENAME[] = "/Users/apple/Downloads/smallwords.txt";
bool wordlen (char userIn[MAXINPUT + 1]);
bool validword(char userIn[], const char words[][MAXWORDLEN+1], int nWords);
int minpos (int a, int b);

int playOneRound(const char words[][MAXWORDLEN+1], int nWords, int wordnum);

int main()
{
    
    char wordList[MAXWORDS][MAXWORDLEN+1]; // initialize the words list
    
    int nWords = getWords(wordList, MAXWORDS, WORDFILENAME); // get the words into the array
    int round = 0; // initialize the round number
    
    if (nWords<1) // if no words loaded
    {
        cout << "No words were loaded, so I can't play the game." << endl;
        return 0; // Exit
    }
    
    cout << "How many rounds do you want to play? ";
    cin >> round;
    cin.ignore(10000, '\n'); // clean the \n buffer
    
    if (round <= 0) // detect negative sitiation
    {
        cout << "The number of rounds must be positive." << endl;
        return 0;
    }
    
    double sum = 0;
    int max = 0;
    int min = 0;
    double average = 0;
    
    for (int a = 0; a < round; a++)
    {
        cout << endl;
        cout << "Round " << a+1 << endl;
        int wordnum = randInt(0, nWords - 1); // generate a random number for the word index
        cout << "The mystery word is "<<strlen(wordList[wordnum])<<" letters long."<<endl;
        int count = playOneRound(wordList, nWords, wordnum);
        
        if (count == 1) // One trial case
        {
            cout << "You got it in 1 try." << endl;
        }
        else // multiple trial case
        {
        cout << "You got it in " << count << " tries." << endl;
        }
        
        if (a == 0) //max and min for the first round is the trial number
        {
            max = count;
            min = count;
        }
        sum += count;
        if (count > max) // when more than one round, find the max
            max = count;
        if (count < min) // when more than one round, find the min
            min = count;
        average = sum/(a+1); // average
        cout.setf(ios::fixed); //precision to two decimal places
        cout.precision(2);
        cout << "Average: " << average << ", minimum: " << min << ", maximum: " << max << endl;
        }
    }

int playOneRound(const char words[][7], int nWords, int wordnum)
{
    
    bool match = false;
    int count = 0; // how many counts
    int flowercount = 0;
    int beecount = 0;
    
    if(nWords <=0 || wordnum<0 || wordnum >= nWords)
    {
        return -1; // invalid arguments
    }
    for (;match == false;count++) // begin the loop until the word is guessed right
    {
        flowercount = 0;
        beecount = 0;
        char userIn[MAXINPUT + 1]; // give position for '\0'
        
        cout << "Trial word: ";
        cin.getline(userIn, MAXINPUT + 1); // cin.getline() is for cstring
        
        if (not wordlen(userIn)) // call a function to check the length of word
        {
            cout << "Your trial word must be a word of 4 to 6 lower case letters." << endl;
            continue;
        }
        
        if (not validword(userIn, words, nWords)) // call a function to check whether the word entered is in the word list
        {
            cout << "I don't know that word." << endl;
            continue;
        }
        
        if (strcmp(userIn, words[wordnum]) == 0) // if match
        {
            count++;
            break;
        }
        
        char temp[100];
        strcpy(temp, words[wordnum]); // create a temp copy
        char temp2[100];
        strcpy(temp2, userIn);
        int smallpos = minpos(strlen(userIn), strlen(words[wordnum])); // find a smaller word length for flower loop
        
        for (int k = 0; k < smallpos; k++)
        {
            if (temp[k] == userIn[k])
            {
                flowercount++;
                temp[k] = '_';
                temp2[k] = '#';// when find a flower, use _ to eliminate the word
            }
        }

        for (int i = 0; i < strlen(userIn); i++)
        {
             for (int j = 0; j < strlen(words[wordnum]); j++)
             {
                 if (temp[j] == temp2[i]) // use a nested loop to go through every character in a string in every character of another string
                 {
                     beecount++;
                     temp[j] = '_'; // when find a bee, use _ to eliminate the word
                     break;
                 }
             }
        }
        
        cout << "Flowers: " << flowercount << "," << " Bees: " << beecount << endl;
    }
    
    
    return count;
    
}

bool wordlen(char userIn[])
{
    bool temp = false;
    if (strlen(userIn) <= 6 && strlen(userIn) >= 4)
        {
            for (int k = 0; userIn[k] != '\0'; k++)
            {
                if (islower(userIn[k])) // only lower case strings in length 4-6 are valid
                    temp = true;
                else
                {
                    temp = false;
                    break; // otherwise, false
                }
            }
        }
    return temp;
}

bool validword(char userIn[], const char words[][7], int nWords)
{
    for (int k = 0; k != nWords ; k++)
    {
        if (strcmp(userIn,words[k]) == 0) // compare with each letter in the string
        {
            return true;
        }
    }
    return false;
}
int minpos (int a, int b) // find a smaller one for flower loop
{
    if (a < b)
        return a;
    return b;
}


