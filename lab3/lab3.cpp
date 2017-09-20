#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>

#define MAX_PLAYERS 10

using namespace std;

/*
	Class representing an N-sided die
*/
class Dice{
	private:
		int numSides;
	public:
		Dice(int n) : numSides(n) {}
		// Perform a single roll of the die
		int roll() {
			srand(time(NULL));
			return rand() % numSides + 1;
		}
};

/*
	Class representing a Game Player
*/
class Player{
	private:
		string name;
		int score;
		bool alive; // flag boolean for Knock Out, need a way to see who's still in the game
	public:
		Player(string n, int s=0) : name(n), score(s) {}
		// Getter : Player Name
		string getName(){
			return name;
		}
		// Getter : Score
		int getScore(){
			return score;
		}
		// Increases the player's score by a specified value
		void addToScore(int val){
			score += val;
		}
		bool checkAlive(){
			return alive;
		}
		void setAlive(bool val){  // used to eliminate players during Knock Out
			alive = val;
		}
};

/*
	Abstract class DiceGame
*/
class DiceGame{
	protected:
		Player *players[MAX_PLAYERS];
		Dice *dice;
		string input; // dummy variable for getting user input (select which game to play or confirm yes/no)
		int numDice, numPlayers, numSides, playerCount; // playerCount incremented each time new player is added to array
	public:
		DiceGame(){}
		DiceGame(int nP, int nD, int nS) : numPlayers(nP), numDice(nD), numSides(nS), playerCount(0) {
			dice = new Dice(nS);
			createPlayers();
		}
		virtual void play(){}
		void initPlayer(string name, int score=0){
			Player *temp = new Player(name, score); // allocate memory for a new player and add it to player array
			players[playerCount] = temp;
			playerCount++; // increment playerCount so I know what index to add the next player at
		}
		void createPlayers(){ // create players with user-given names
			string name;
			for(int i = 1; i <= numPlayers; i++){
				cout << "Enter player " << i << "'s name: ";
				getline(cin, name);
				initPlayer(name);
			}
		}
		void displayScores(){ // display scores with some formatting
			for(int i = 0; i < playerCount; i++){
				cout << "Player: " << left << setw(20) << players[i]->getName()
					 << "  |  Score: " << players[i]->getScore() << endl;
			}
		}
		void writeScoresToFile(){
			ofstream scorecard("scorecard.txt", ios::app); // append to existing scorecard file rather than overwrite
			if(scorecard.is_open()){
				for(int i = 0; i < playerCount; i++){
					scorecard << "Player: " << left << setw(20) << players[i]->getName()
						      << "  |  Score: " << players[i]->getScore() << endl;
				}
			} else {
				cout << "Unable to open score card file." << endl;
			}
			scorecard.close();
		}
		void getHighestScore(){
			string a, name, c, leader; // leader = name of player with highest registered score
			char b;
			int score, highest = 0;        // highest = associated score of leader
			ifstream scorecard("scorecard.txt");
			if(scorecard.is_open()){
				while(getline(scorecard, input)){
					stringstream ss(input);
					ss >> a >> name >> b >> c >> score; // a, b, and c are just placeholder variables so I could access name and score using stringstream
					if(score > highest){
						highest = score;
						leader = name;
					}
				}
			} else {
				cout << "Unable to open score card file." << endl;
			}
			cout << "___ High Score ___" << endl
			     << "Player: " << left << setw(20) << leader
			     << "  |  Score: " << highest << endl << endl;
		}
		~DiceGame(){
			for(int i = 0; i < playerCount; i++){
				delete players[i];
			}
			delete dice;
		}
};

class knockOut : public DiceGame{
	int knock_out_score, current_roll;
public:
	knockOut(int nP, int nD, int nS) : DiceGame(nP, nD, nS), knock_out_score(0) {}
	void play(){
		int remaining_players, round_number; // declare game variables
		do {
			cout << endl << "Press enter to roll for the Knock Out Score.";
			getline(cin, input);
			knock_out_score = playerRoll();  // calculate a KO score
			cout << "** The Knock Out Score is " << knock_out_score << " **" << endl;
			remaining_players = numPlayers; round_number = 1;               // reset game variables
			for(int i = 0; i < numPlayers; i++) players[i]->setAlive(true); // reset so all players are in the game
			while(remaining_players > 1){                                   // play until only 1 player is left
				cout << endl << "_____ Round " << round_number << " _____"<< endl;
				for(int i = 0; i < numPlayers; i++){
					cout << endl;
					if(players[i]->checkAlive()){  // find the players who are left--only they take a turn
						cout << players[i]->getName() << ", it's your turn." << endl
							 << "Press enter to roll.";
						getline(cin, input);            // I required the user to press enter so the rolls are at least a little randomized
						current_roll = playerRoll();    // execute roll function which is unique to this game (i.e. take a turn)
						cout << players[i]->getName() << "'s total:  " << current_roll << endl;
						if(current_roll == knock_out_score){  // eliminate players if their score is equal to the KO score
							cout << players[i]->getName() << ", you have been eliminated." << endl;
							players[i]->setAlive(false);
							remaining_players--;
						}
					}
					if(remaining_players == 1) break; // we have a winner
				}
				round_number++;
			}
			for(int i = 0; i < numPlayers; i++){
				if(players[i]->checkAlive()){         // determine which player is still left in the game (the winner)
					players[i]->addToScore(50);       // update scores
					cout << endl << "Congratulations, " << players[i]->getName() << "! You won Knock Out! Your reward: 50 points" << endl
						 << "____ New Scores ____" << endl;
						 displayScores();
				}
			}
			cout << "Would you like to play again? (y/n)" << endl;
			getline(cin, input);
		} while(input == "y" || input == "Y");
	}
	int playerRoll(){
		int sum = 0, temp;
		for(int i = 1; i <= numDice; i++){
			temp = dice->roll();
			cout << "Roll " << i << ":  " << temp << endl;
			sum += temp;  // collect rolls in a sum which is the total for the round
			if(i < numDice){
				cout << "Press enter to roll again.";
				getline(cin, input);
			}
		}
		return sum;
	}
};

class Boston : public DiceGame{
public:
	Boston(int nP, int nD, int nS) : DiceGame(nP, nD, nS) {}
	void play(){
		// iterate through players
			// roll N times, store highest roll
				// decrement N, roll N times again, store highest
				// repeat until N == 0
			// sum highest rolls
			// compare sum to previous highest player's sum
				// if this sum is greater, this player is currently in the lead (winner)
		// display who won, prompt to play again
		int total, highest;
		Player *winner;
		do {
			highest = 0; // reset highest score
			for(int i = 0; i < numPlayers; i++){
				cout << endl << "_____ "
				     << players[i]->getName() << "'s Turn _____" << endl
					 << "Press enter to begin your turn.";
				getline(cin, input);
				total = playerRoll(numDice);
				cout << endl << players[i]->getName() << ", your total is " << total << "." << endl;
				if(total > highest){
					highest = total;
					winner = players[i];
					cout << winner->getName() << ", you are currently in the lead with " << highest << "." << endl;
				} else if (total == highest){
					cout << players[i]->getName() << ", you tied " << winner->getName() << "'s score of " << highest << "." << endl
					     << "Unfortunately, only one player can win." << endl;
				} else {
					cout << players[i]->getName() << ", your score of " << total
					     << " is lower than " << winner->getName() << "'s score of " << highest << "." << endl;
				}
			}
			winner->addToScore(25);
			cout << endl << "Congratulations, " << winner->getName() << "! You won the Boston Dice Game! Your reward: 25 points" << endl
				 << "____ New Scores ____" << endl;
			displayScores();
			cout << "Would you like to play again? (y/n)" << endl;
			getline(cin, input);
		} while(input == "y" || input == "Y");
	}
	int playerRoll(int num_of_dice){
		cout << endl << "Now rolling " << num_of_dice << (num_of_dice > 1 ? " dice." : " die.") << endl
		     << "Press enter to roll.";
		getline(cin, input);
		int temp, max = 0;                                 // temp stores the current roll, max stores the highest roll from this round
		for(int i = 1; i <= num_of_dice; i++){
			temp = dice->roll();
			cout << "Roll " << i << ":  " << temp << endl;
			if(temp > max) max = temp;                     // check if this roll is the highest so far - if so, store it in max
			if(i < num_of_dice){
				cout << "Press enter to roll again.";
				getline(cin, input);
			}
		}
		cout << max << " added to your total" << endl;
		if(num_of_dice == 1) return temp;              // base case for recursion - I put it here because of the text output
		return max + playerRoll(num_of_dice - 1);      // recursively roll one less die each time, adding up the highest rolls from each round
	}


};

int main() {
	int game_selection, numPlayers, numDice, numSides;
	string input;
	do {
		do {
			cout << endl
				 << "*** Dice Games ***" << endl
				 << "1. Knock Out" << endl
				 << "2. Boston" << endl
				 << "Select which game you would like to play: ";
				 getline(cin, input);
				 stringstream(input) >> game_selection;
		} while(game_selection != 1 and game_selection != 2); // input control
		cout << endl << "You selected " << (game_selection == 1 ? "Knock Out" : "Boston") << endl;
		do {
			cout << endl << "Enter the number of players (max " << MAX_PLAYERS << "): ";
			getline(cin, input);
			stringstream(input) >> numPlayers;
			if(numPlayers > MAX_PLAYERS){
				cout << "You can only have up to " << MAX_PLAYERS << " players. " << endl;
			} else if (numPlayers < 2){
				cout << "You need at least 2 players" << endl;
			}
		} while(numPlayers > MAX_PLAYERS || numPlayers < 2); // input control
		do {
			cout << "Enter the number of dice: ";
			getline(cin, input);
			stringstream(input) >> numDice;
			if(numDice < 1){
				cout << "You must enter a number greater than or equal to 1." << endl;
			}
		} while(numDice < 1); // input control
		do {
			cout << "Enter the number of sides on each die: ";
			getline(cin, input);
			stringstream(input) >> numSides;
			if(numSides < 6){
				cout << "You must enter a number greater than or equal to 6." << endl;
			}
		} while(numSides < 6);
		DiceGame *game;           // Base class pointer
		if(game_selection == 1){  // store pointer to derived class in pointer to base class (override virtual functions)
			game = new knockOut(numPlayers, numDice, numSides);
		} else if (game_selection == 2){
			game = new Boston(numPlayers, numDice, numSides);
		}
		game->play();
		game->writeScoresToFile();
		game->getHighestScore();
		delete game;
		cout << "Would you like to play a different game? (y/n)" << endl;
		getline(cin, input);
	} while(input == "y" || input == "Y");

}
