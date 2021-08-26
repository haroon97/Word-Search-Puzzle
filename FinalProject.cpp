#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
using namespace std;

void readBoard(char wordGrid[][15], ifstream& fin);
void printBoard(char wordGrid[][15]);
void pausedGame(char wordGrid[][15], ofstream& fout);
bool verifyWord(string word);
bool wordComparison(string word1, string word2, int length1, int length2);
bool rowByRowSearch(char wordGrid[][15], string word);
void toUpperCase(string& word);
bool rowByRowComparison(int rowIndex, int colIndex, int stringLength, char wordGrid[][15], string word);
bool colByColSearch(char wordGrid[][15], string word);
bool colByColComparison(int colIndex, int rowIndex, int stringLength, char wordGrid[][15], string word);
void scoreAndLivesCalculator(int& score, int& lives, bool isFoundInRow, bool isFoundInCol);
void pauseGameMenu();
void exitOrResumeGame(string userChoice, char wordGrid[][15]);
void levelSelection(string userChoice, string& level);
void displayHighscore(string userChoice, string players[], int highScores[], int score);
void gameMenu();
bool revRowSearch(char wordGrid[][15], string word);
bool revRowComparison(int rowIndex, int colIndex, int stringLength, char wordGrid[][15], string word);
bool revColSearch(char wordGrid[][15], string word);
bool revColComparison(int colIndex, int rowIndex, int stringLength, char wordGrid[][15], string word);
void scoreCalculatorForMediumDifficulty(int& score, int& lives, bool isFoundInRow, bool isFoundInCol, bool isRevRow, bool isRevCol);
bool forwardDiagonalSearch(char wordGrid[][15], string word);
bool forwardDiagonalComparison(char wordGrid[][15], string word, int rowIndex, int colIndex, int length);
void scoreCalculatorForHardDifficulty(int& score, int& lives, int isFoundInRow, int isFoundInCol, int isRevRow, int isRevCol, int isFoundInFwdDiagonal, int isFoundInBwdDiagonal, int isRevFwdDiagonal);
bool backwardDiagonalSearch(char wordGrid[][15], string word);
bool backwardDiagonalComparison(char wordGrid[][15], string word, int rowIndex, int colIndex, int length);
bool fwdRevDiagonalSearch(char wordGrid[][15], string word);
bool fwdRevDiagonalComparison(char wordGrid[][15], string word, int length, int rowIndex, int colIndex);

int main() {

	// Variables
	char wordGrid[15][15];
	int lives = 3, score = 0;
	int highScores[5] = { 0 };
	string players[5];
	string userChoice, playerName, difficultyLevel = "easy", wordToSearch;
	bool isUserPlaying = false, isWordValid=false, isFoundInRow, isFoundInCol, isFoundInRevRow, isFoundInRevCol, isFoundInFwdDiagonal, isFoundInBwdDiagonal, isFoundInRevFwdDiagonal;

	// Menu for game
	cout << "*** WELCOME TO WORD SEARCH PUZZLE ***" << endl;
	cout << "*** RULES ***" << endl;
	cout << "--- YOU HAVE TO FIND 10 WORDS FROM THE PUZZLE AND YOU HAVE 3 LIVES TO FIND THEM. ---" << endl;
	cout << "--- EVERY FAILED ATTEMPT WILL RESULT IN LOSS OF ONE LIVE AMD EVERY CORRECT ANSWER WILL GIVE YOU 10 POINTS ---" << endl;
	cout << "--- BY DEFAULT THE DIFFICULTY LEVEL IS SET TO EASY ---" << endl;

	ifstream fin("highscore.txt");
	for (int i = 0; i < 5; i++) {
		fin >> players[i];
		fin >> highScores[i];
	}
	fin.close();

	while (userChoice != "n" && userChoice != "e") {   // Game Main Menu
		gameMenu();
		cin >> userChoice;
		levelSelection(userChoice, difficultyLevel);
		displayHighscore(userChoice, players, highScores, score);
		if (userChoice == "r" && isUserPlaying == false) {
			cout << "First start a new game" << endl;
		}
	}

	// New Game logic and menu
	if (userChoice == "n" || userChoice == "N") {
		isUserPlaying = true;
		cout << "Enter your name" << endl;
		cin >> playerName;
		if (difficultyLevel == "easy") {   // difficulty level logic
			ifstream fin("hardboard.txt");
			readBoard(wordGrid, fin);
			fin.close();
			printBoard(wordGrid);
			while (lives != 0 && score != 100 && userChoice != "e") {
				cout << "Enter the word" << endl;
				cin >> wordToSearch;
				if (wordToSearch == "p" || wordToSearch == "P") {   // pause game logic
					ofstream fout("pausedgame.txt");
					pausedGame(wordGrid, fout);
					pauseGameMenu();
					cin >> userChoice;
					exitOrResumeGame(userChoice, wordGrid); // Exit or resume game function
				}
				else {  // word search
					isWordValid = verifyWord(wordToSearch);   // Verifying word from Dictionary file
					if (isWordValid) {
						toUpperCase(wordToSearch);
						isFoundInRow = rowByRowSearch(wordGrid, wordToSearch); // Searching word in row
						isFoundInCol = colByColSearch(wordGrid, wordToSearch); // Searching word in columns
						scoreAndLivesCalculator(score, lives, isFoundInRow, isFoundInCol); // Score and Lives Calculation
						printBoard(wordGrid);
					}
					else {
						cout << "Invalid Word" << endl;
						printBoard(wordGrid);
					}
				}
			}
		}

		else if (difficultyLevel == "medium") {  // Medium Level Difficulty
			ifstream fin("hardboard.txt");
			readBoard(wordGrid, fin);
			fin.close();
			printBoard(wordGrid);
			while (lives != 0 && score != 100 && userChoice != "e") {
				cout << "Enter the word" << endl;
				cin >> wordToSearch;
				if (wordToSearch == "p" || wordToSearch == "P") {   // pause game logic
					ofstream fout("pausedgame.txt");
					pausedGame(wordGrid, fout);
					pauseGameMenu();
					cin >> userChoice;
					exitOrResumeGame(userChoice, wordGrid); // Exit or resume game function
				}
				else {  // word search
					isWordValid = verifyWord(wordToSearch);   // Verifying word from Dictionary file
					if (isWordValid) {
						toUpperCase(wordToSearch);
						isFoundInRow = rowByRowSearch(wordGrid, wordToSearch); // Searching word in row
						isFoundInCol = colByColSearch(wordGrid, wordToSearch); // Searching word in columns
						isFoundInRevRow = revRowSearch(wordGrid, wordToSearch); // Searching word in reverse row
						isFoundInRevCol = revColSearch(wordGrid, wordToSearch); // Searching word in reverse column
						scoreCalculatorForMediumDifficulty(score, lives, isFoundInRow, isFoundInCol, isFoundInRevRow, isFoundInRevCol); // Score and Lives Calculation
						printBoard(wordGrid);
					}
					else {
						cout << "Invalid Word" << endl;
						printBoard(wordGrid);
					}
				}
			}
		}

		else if (difficultyLevel == "hard") {  // Hard Level Difficulty
			ifstream fin("hardboard.txt");
			readBoard(wordGrid, fin);
			fin.close();
			printBoard(wordGrid);
			while (lives != 0 && score != 100 && userChoice != "e") {
				cout << "Enter the word" << endl;
				cin >> wordToSearch;
				if (wordToSearch == "p" || wordToSearch == "P") {   // pause game logic
					ofstream fout("pausedgame.txt");
					pausedGame(wordGrid, fout);
					pauseGameMenu();
					cin >> userChoice;
					exitOrResumeGame(userChoice, wordGrid); // Exit or resume game function
				}
				else {  // word search
					isWordValid = verifyWord(wordToSearch);   // Verifying word from Dictionary file
					if (isWordValid) {
						toUpperCase(wordToSearch);
						isFoundInRow = rowByRowSearch(wordGrid, wordToSearch); // Searching word in row
						isFoundInCol = colByColSearch(wordGrid, wordToSearch); // Searching word in columns
						isFoundInRevRow = revRowSearch(wordGrid, wordToSearch); // Searching word in reverse row
						isFoundInRevCol = revColSearch(wordGrid, wordToSearch); // Searching word in reverse column
						isFoundInFwdDiagonal = forwardDiagonalSearch(wordGrid, wordToSearch); // Searching word in forward Diagonal
						isFoundInBwdDiagonal = backwardDiagonalSearch(wordGrid, wordToSearch); // Searching word in backward diagonal
						isFoundInRevFwdDiagonal = fwdRevDiagonalSearch(wordGrid, wordToSearch); // Searching in reverse forward diagonal
						scoreCalculatorForHardDifficulty(score, lives, isFoundInRow, isFoundInCol, isFoundInRevRow, isFoundInRevCol, isFoundInFwdDiagonal, isFoundInBwdDiagonal, isFoundInRevFwdDiagonal); // Score and Lives Calculation
						printBoard(wordGrid);
					}
					else {
						cout << "Invalid Word" << endl;
						printBoard(wordGrid);
					}
				}
			}
		}
	}

	

	// Highscore
	if (score > 0) {
		fstream file("highscore.txt", ios::in | ios::out | ios::app);
		file << playerName << " " << score << endl;
	}

	if (userChoice == "E" || userChoice == "e") {
		cout << "Goodbye. Thank you for playing" << endl;
	}

	if (lives == 0 || score == 100) {
		cout << playerName << " your score is " << score << endl;
	}

	displayHighscore(userChoice, players, highScores, score);
}

void readBoard(char wordGrid[][15], ifstream& fin) {
	if (fin.is_open()) {
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 15; j++) {
				fin >> wordGrid[i][j];
			}
		}
	}
	else {
		cout << "File not found" << endl;
	}
}

void printBoard(char wordGrid[][15]) {
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			cout << wordGrid[i][j] << " ";
		}
		cout << endl;
	}
}

void pausedGame(char wordGrid[][15], ofstream& fout) {
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			fout << wordGrid[i][j] << " ";
		}
		fout << endl;
	}
}

bool verifyWord(string word) {
	int length = word.length();
	string wordToMatch;
	bool isFound = false;
	ifstream fin("words.txt");
	if (fin.is_open()) {
		while (!fin.eof()) {
			getline(fin, wordToMatch);
			int lengthOfWord = wordToMatch.length();
			isFound = wordComparison(word, wordToMatch, length, lengthOfWord);
			if (isFound) {
				return true;
			}
		}
		fin.close();
		return false;
	}
	else {
		cout << "File not found" << endl;
	}
}

bool wordComparison(string word1, string word2, int length1, int length2) {
	if (length1 == length2 && word1[0] == word2[0]) {
		for (int i = 0; i < length1; i++) {
			if (word1[i] != word2[i]) {
				return false;
			}
		}
		return true;
	}
	return false;
}

bool rowByRowSearch(char wordGrid[][15], string word) {
	bool isFound;
	int length = word.length(), index = 0;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (wordGrid[i][j] == word[0]) {
				index = j + 1;
				isFound = rowByRowComparison(i, index, length, wordGrid, word);
				if (isFound) {
					cout << "Word found at row " << i << " and column " << j << endl;
					return true;
				}
			}
		}
	}
	return false;
}

bool rowByRowComparison(int rowIndex, int colIndex, int stringLength, char wordGrid[][15], string word) {
	for (int k = 1; k < stringLength; k++) {
		if (wordGrid[rowIndex][colIndex] != word[k]) {
			return false;
		}
		colIndex++;
	}
	return true;
}

bool colByColSearch(char wordGrid[][15], string word) {
	bool isFound;
	int length = word.length(), index = 0;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (wordGrid[j][i] == word[0]) {
				index = j + 1;
				isFound = colByColComparison(i, index, length, wordGrid, word);
				if (isFound) {
					cout << "Word found at row " << j << " and column " << i << endl;
					return true;
				}
			}
		}
	}
	return false;
}

bool colByColComparison(int colIndex, int rowIndex, int stringLength, char wordGrid[][15], string word) {
	for (int k = 1; k < stringLength; k++) {
		if (wordGrid[rowIndex][colIndex] != word[k]) {
			return false;
		}
		rowIndex++;
	}
	return true;
}

void toUpperCase(string& word) {
	for (int i = 0; i < word.length(); i++) {
		word[i] = toupper(word[i]);
	}
}

void scoreAndLivesCalculator(int& score, int& lives, bool isFoundInRow, bool isFoundInCol) {
	if (isFoundInCol || isFoundInRow) {
		score += 10;
		cout << "Your new score is: " << score << endl;
	}
	else {
		lives -= 1;
		cout << "Word not found" << endl;
		cout << "Your remaining lives are: " << lives << endl;
	}
}

void pauseGameMenu() {
	cout << "Press e for exit" << endl;
	cout << "Press r for resume" << endl;
}

void exitOrResumeGame(string userChoice, char wordGrid[][15]) {
	if (userChoice == "e" || userChoice == "E") {   // user choice for exit or resume
		cout << "Thank you Playing. Good bye" << endl;
	}
	else if (userChoice == "r" || userChoice == "R") { // Resume game
		ifstream fin("pausedgame.txt");
		readBoard(wordGrid, fin);
		fin.close();
		printBoard(wordGrid);
	}
}

void levelSelection(string userChoice, string& level) {
	if (userChoice == "l" || userChoice == "L") {
		cout << "Enter the level you wanna select" << endl;
		cout << "1. easy" << endl;
		cout << "2. medium" << endl;
		cout << "3. hard" << endl;
		cin >> level;
	}
}

void displayHighscore(string userChoice, string players[], int highScores[], int score) {
	if (userChoice == "h" || userChoice == "H" || score == 100) {
		for (int i = 0; i < 5; i++) {
			cout << players[i] << " " << highScores[i] << endl;
		}
	}
	
}

void gameMenu() {
	cout << "Press n for new game" << endl;
	cout << "Press r for resume game" << endl;
	cout << "Press l for level selection" << endl;
	cout << "Press h for high score" << endl;
	cout << "Press e for exit" << endl;
}

bool revRowSearch(char wordGrid[][15], string word) {
	bool isFound;
	int length = word.length(), index = 0;
	for (int i = 14; i >= 0; i--) {
		for (int j = 14; j >= 0; j--) {
			if (wordGrid[i][j] == word[0]) {
				index = j - 1;
				isFound = revRowComparison(i, index, length, wordGrid, word);
				if (isFound) {
					cout << "Word found at row " << i << " and column " << j << endl;
					return true;
				}
			}
		}
	}
	return false;
}

bool revRowComparison(int rowIndex, int colIndex, int stringLength, char wordGrid[][15], string word) {
	for (int k = 1; k < stringLength; k++) {
		if (wordGrid[rowIndex][colIndex] != word[k]) {
			return false;
		}
		colIndex--;
	}
	return true;
}

bool revColSearch(char wordGrid[][15], string word) {
	bool isFound;
	int length = word.length(), index = 0;
	for (int i = 14; i >= 0; i--) {
		for (int j = 14; j >= 0; j--) {
			if (wordGrid[j][i] == word[0]) {
				index = j - 1;
				isFound = revColComparison(i, index, length, wordGrid, word);
				if (isFound) {
					cout << "Word found at row " << j << " and column " << i << endl;
					return true;
				}
			}
		}
	}
	return false;
}

bool revColComparison(int colIndex, int rowIndex, int stringLength, char wordGrid[][15], string word) {
	for (int k = 1; k < stringLength; k++) {
		if (wordGrid[rowIndex][colIndex] != word[k]) {
			return false;
		}
		rowIndex--;
	}
	return true;
}

void scoreCalculatorForMediumDifficulty(int& score, int& lives, bool isFoundInRow, bool isFoundInCol, bool isRevRow, bool isRevCol) {
	if (isFoundInCol || isFoundInRow || isRevRow || isRevCol) {
		score += 10;
		cout << "Your new score is: " << score << endl;
	}
	else {
		lives -= 1;
		cout << "Word not found" << endl;
		cout << "Your remaining lives are: " << lives << endl;
	}
}

bool forwardDiagonalSearch(char wordGrid[][15], string word) {
	bool isFound = false;
	int length = word.length();
	int rowIndex = 0, colIndex = 0;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (wordGrid[i][j] == word[0]) {
				rowIndex = i + 1;
				colIndex = j + 1;
				if (rowIndex < 14 && colIndex < 14) {
					isFound = forwardDiagonalComparison(wordGrid, word, rowIndex, colIndex, length);
				}
				if (isFound) {
					cout << "Word found at row " << i << " column " << j << endl;
					return true;
				}
			}
		}
	}
	return false;
}

bool forwardDiagonalComparison(char wordGrid[][15], string word, int rowIndex, int colIndex, int length) {
    for (int i = 1; i < length; i++) {
		if (wordGrid[rowIndex][colIndex] != word[i]) {
			return false;
		}
		rowIndex++;
		colIndex++;
	}
	return true;
}

bool backwardDiagonalSearch(char wordGrid[][15], string word) {
	bool isFound = false;
	int length = word.length();
	int rowIndex = 0, colIndex = 0;
	for (int i = 14; i >= 0; i--) {
		for (int j = 14; j >= 0; j--) {
			if (wordGrid[i][j] == word[0]) {
				rowIndex = i - 1;
				colIndex = j - 1;
				if (rowIndex > 0 && colIndex > 0) {
					isFound = backwardDiagonalComparison(wordGrid, word, rowIndex, colIndex, length);
				}
				if (isFound) {
					cout << "Word found at row " << i << " column " << j << endl;
					return true;
				}
			}
		}
	}
	return false;
}

bool backwardDiagonalComparison(char wordGrid[][15], string word, int rowIndex, int colIndex, int length) {
	for (int i = 1; i < length; i++) {
		if (wordGrid[rowIndex][colIndex] != word[i]) {
			return false;
		}
		rowIndex--;
		colIndex--;
	}
	return true;
}

bool fwdRevDiagonalSearch(char wordGrid[][15], string word) {
	bool isFound = false;
	int length = word.length();
	int rowIndex = 0, colIndex = 0;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (wordGrid[i][j] == word[0]) {
				rowIndex = i - 1;
				colIndex = j + 1;
				isFound = fwdRevDiagonalComparison(wordGrid, word, length, rowIndex, colIndex);
				if (isFound) {
					cout << "Word found at row " << i << " column " << j << endl;
					return true;
				}
			}
		}
	}
	return false;
}

bool fwdRevDiagonalComparison(char wordGrid[][15], string word, int length, int rowIndex, int colIndex) {
	for (int i = 1; i < length; i++) {
		if (wordGrid[rowIndex][colIndex] != word[i]) {
			return false;
		}
		rowIndex--;
		colIndex++;
	}
	return true;
}

void scoreCalculatorForHardDifficulty(int& score, int& lives, int isFoundInRow, int isFoundInCol, int isRevRow, int isRevCol, int isFoundInFwdDiagonal, int isFoundInBwdDiagonal, int isRevFwdDiagonal) {
	if (isFoundInCol || isFoundInRow || isRevRow || isRevCol || isFoundInFwdDiagonal || isFoundInBwdDiagonal || isRevFwdDiagonal) {
		score += 10;
		cout << "Your new score is: " << score << endl;
	}
	else {
		lives -= 1;
		cout << "Word not found" << endl;
		cout << "Your remaining lives are: " << lives << endl;
	}
}

