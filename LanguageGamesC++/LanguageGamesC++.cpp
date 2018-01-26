// LanguageGamesC++.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Switch to get the game, based on input from the menu
string doGame(int gameNum, string input);

// Functions to do the various games
string doEncryption(string input);
string doTutnese(string input);
string doPigLatin(string input);

// Helper functions for the various games
char getEncLetter(vector<char> encArray, int lettPos, int numLetters);
int indexOf(vector<char> haystack, char needle);
bool isVowel(char toCheck);
bool isConsonant(char toCheck);
vector<string> splitString(string sentence, char separator);

// Arrays to hold various data related to the games
vector<char> vowels{ 'a', 'e', 'i', 'o', 'u' };
vector<char> consonants{ 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z' };
vector<string> tutOut = { "bub", "cash", "dud", "fuf", "gug", "hash", "jay", "kuck", "lu", "mum", "nun", "pub", "quack", "rug", "sus", "tut", "vuv", "wack", "ex", "yub", "zub" };
vector<char> wordEnds = { '.', '?', '!', ',', '/', '\\' };

int main()
{
	string input = "";
	int gameNum = -1;
	const int gameMax = 3;

	// Loop until quit
	while (gameNum != (gameMax + 1))
	{
		// Display a menu to choose which game to play
		while (gameNum <= 0 || gameNum > (gameMax + 1))
		{
			input = "";
			std::cout << "Games:" << endl;
			std::cout << "1: Encryption" << endl;
			std::cout << "2: Tutnese" << endl;
			std::cout << "3: Pig Latin" << endl;
			std::cout << (gameMax + 1) << ": To Quit" << endl;
			std::cout << "Please select a game: ";
			std::cin >> gameNum;

			if (gameNum < 0 || gameNum > gameMax + 1)
			{
				std::cout << "Not a valid game, please try again." << endl;
			}
		}

		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');

		while (input != "-1" && gameNum != (gameMax + 1))
		{
			// Trying to do character-at-a-time input doesn't really work in C++, unfortunately.
			/*system("cls");

			std::cout << doGame(gameNum, input) << "\n\n\n\n\n\n";
			std::cout << "Enter some text: " << input;
			input.append(1, _getch());*/

			// Accept some input, apply whatever transformation, and output, loop until quit
			std::cout << "Enter some text: ";
			getline(std::cin, input);

			if (input != "-1")
			{
				std::cout << "\nTranslated: " << doGame(gameNum, input) << endl << endl;
			}
			else
			{
				gameNum = -1;
			}
		}
	}

	std::cout << "Okay." << endl;

    return 0;
}

// Determine which transformation to apply, based on user input
string doGame(int gameNum, string input)
{
	switch (gameNum)
	{
		case 1:
			return doEncryption(input);
		case 2:
			return doTutnese(input);
		case 3:
			return doPigLatin(input);
		default:
			return "Fail.";
	}
}

/**********************************************************
* For each letter in the input string, if it is a letter, *
* check to see if it's lowercase, and record.             *
* Check to see if a vowel, if not, it's a consonant.      *
* Using the appropriate array (consonant or vowel),       *
* and the number of approriate letter types,              *
* find the encrypted letter and output.                   *
* I.e., the string "ABCD" would come out "ECFH"           *
* (adding 1 to the A to get E, then 1 to B to get C,      *
* then 2 to C to get F, and 3 to D to get H).             *
* Then outputs the complete string.                       *
**********************************************************/
string doEncryption(string input)
{
	string output = "";
	int numVowels = 1;
	int numConsonants = 1;

	for each (char toEnc in input)
	{
		if (isalpha(toEnc))
		{
			bool isUpper = false;

			if (isupper(toEnc))
			{
				isUpper = true;
				toEnc = tolower(toEnc);
			}

			int lettPos = indexOf(vowels, toEnc);

			if (lettPos >= 0)
			{
				toEnc = getEncLetter(vowels, lettPos, numVowels);
				numVowels++;
			}
			else
			{
				lettPos = indexOf(consonants, toEnc);
				toEnc = getEncLetter(consonants, lettPos, numConsonants);
				numConsonants++;
			}

			if (isUpper)
			{
				toEnc = toupper(toEnc);
			}
		}

		output.append(1, toEnc);
	}

	return output;
}

/**********************************************************
* For each character in the string, if it is a consonant, *
* find the appropriate position in the tutOut array, and  *
* replace it with the appropriate word. Otherwise, simply *
* output the word.
**********************************************************/
string doTutnese(string input)
{
	string output = "";

	for each (char toEnc in input)
	{
		int lettPos = indexOf(consonants, tolower(toEnc));

		if (lettPos > -1)
		{
			string tutOutStr = tutOut[lettPos];

			if (isupper(toEnc))
			{
				tutOutStr[0] = toupper(tutOutStr[0]);
			}

			output.append(tutOutStr);
		}
		else
		{
			output.append(1, toEnc);
		}
	}

	return output;
}

/**************************************************************
* Split the input into words. For each word, find two things: *
* 1) The position of the first consonant in the word (if any) *
* 2) The last position of a "word ender" piece of punctuation *
*        (i.e., a comma, period, and so on)                   *
* Split the word into three pieces: pre-vowel, post-vowel,    *
* and punctuation. Add "ay" if the word starts with a         *
* consonant, "yay" if it doesn't, then put the word back      *
* together as post-vowel, pre-vowel, punctuation.             *
**************************************************************/
string doPigLatin(string input)
{
	if (input.size() == 0)
	{
		return "";
	}

	string output = "";
	vector<string> sentence = splitString(input, ' ');

	for each(string currWord in sentence)
	{
		bool isUpper = false;

		if (isalpha(currWord[0]) && isupper(currWord[0]))
		{
			isUpper = true;
			currWord[0] = tolower(currWord[0]);
		}

		int i = 0;
		int j = currWord.size() - 1;

		for (; i < currWord.size() && !isVowel(currWord[i]); i++);
		for (; j >= 0 &&  indexOf(wordEnds, currWord[j]) >= 0; j--);

		string punct;

		if (j > 0 || (currWord.size() > 1 && indexOf(wordEnds, currWord[j]) >= 0))
		{
			punct = currWord.substr(j + 1, currWord.size() - 1);
			currWord.erase(j + 1, currWord.size() - 1);
		}

		if (i > 0)
		{
			string preVowel = currWord.substr(0, i);
			currWord.erase(0, i);
			currWord += preVowel + "ay";
		}
		else if (currWord != "")
		{
			currWord += "yay";
		}

		if (isUpper)
		{
			currWord[0] = toupper(currWord[0]);
		}

		if (output != "")
		{
			output += " ";
		}

		output += currWord + punct;
	}

	return output;
}

int indexOf(vector<char> haystack, char needle)
{
	for (int i = 0; i < haystack.size(); i++)
	{
		if (haystack[i] == needle)
		{
			return i;
		}
	}

	return -1;
}

char getEncLetter(vector<char> encArray, int lettPos, int numLetters)
{
	lettPos += numLetters;

	for (; lettPos >= encArray.size(); lettPos -= encArray.size());

	return encArray[lettPos];
}

bool isVowel(char toCheck)
{
	return (indexOf(vowels, toCheck) >= 0 ? true : false);
}

bool isConsonant(char toCheck)
{
	return (indexOf(consonants, toCheck) >= 0 ? true : false);
}

vector<string> splitString(string sentence, char separator)
{
	vector<string> output;
	output.resize(count(sentence.begin(), sentence.end(), separator) + 1);

	size_t pos = 0;
	for (int i = 0; (pos = sentence.find(separator)) != string::npos; i++)
	{
		output[i] = sentence.substr(0, pos);
		sentence.erase(0, pos + 1);
	}

	output[output.size() - 1] = sentence;

	return output;
}