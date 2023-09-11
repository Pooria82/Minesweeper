#include <string>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <chrono>
#include <string>
#include <iomanip>

using namespace std;

int length, width, realBomb, fakeBomb, correctBomb;
string** board;
bool Exit = false;
bool correct = true;
string Username;

auto Start = chrono::system_clock::now();
int all;

void timer()
{
	auto End = chrono::system_clock::now();
	chrono::duration<double>time = (End - Start);
	all = (int)time.count();
	int seconds = all % 60;
	int minutes = (all % 3600) / 60;
	cout << "    TIME    " << endl;
	cout << " " << setfill('0') << setw(2) << minutes << "min:" << setfill('0') << setw(2) << seconds << "sec" << "" << endl;
	cout << '\n';
}

void printMenu()
{
	if (correct)
	{
		system("cls");
		cout << "1.Play Game" << endl;
		cout << "2.Exit" << endl;
		cout << "Action :";
	}
	else
	{
		system("cls");
		cout << "1.Play Game" << endl;
		cout << "2.Exit" << endl;
		cout << "error!!!" << endl;
		cout << "<<enter the correct word>>" << endl;
		cout << "Action :" ;
	}


}

void printboard()
{
	system("cls");

	timer();

	cout << "  ";
	for (int i = 1; i <= width; i++)
	{
		if (i < 10)
		{
			cout << "  " << i << "  ";
		}
		else
		{
			cout << " " << i << "  ";
		}
	}
	cout << endl;
	for (int i = 1; i < length + 1; i++)
	{
		if (i < 10) {
			cout << " " << i;
		}
		else
		{
			cout << i;
		}
		for (int j = 1; j < width + 1; j++)
		{
			if (board[i][j] == "$")
			{
				cout << "  " << "*" << "  ";
			}
			else
			{
				cout << "  " << board[i][j] << "  ";
			}
		}
		cout << endl;
	}
	cout << "Number of Remaninig Bombs :" << fakeBomb << endl;
	cout << "realBomb :" << realBomb << endl;
	cout << "correctBomb :" << correctBomb << endl;
}

void setBoard(int numberOfBomb)
{
	//set map
	{
		board = new string * [length + 1];
		for (int i = 1; i < length + 1; i++)
		{
			board[i] = new string[width + 1];
			for (int j = 1; j < width + 1; j++)
			{
				board[i][j] = "*";
			}
		}
	}
	//set bomb
	{
		fakeBomb = realBomb;
		srand(time(NULL));
		int bombI, bombJ, LowerBound_I = 1, UpperBound_I = length, LowerBound_J = 1, UpperBound_J = width;
		for (int i = 1; i <= numberOfBomb; i++)
		{
			while (true)
			{
				bombI = (rand() % (UpperBound_I - LowerBound_I + 1)) + LowerBound_I;
				bombJ = (rand() % (UpperBound_J - LowerBound_J + 1)) + LowerBound_J;
				if (board[bombI][bombJ] == "$")
				{
					continue;
				}
				else
				{
					board[bombI][bombJ] = "$";
					break;
				}
			}
		}
	}
	printboard();
}

void playing()
{
	bool end = false;
	while (!end)
	{
		if (correctBomb == realBomb && (fakeBomb + 10) == realBomb) {
			cout << "YOU WIN";
			end = true;
			break;
		}
		int count;
		string action;
		int chooseL, chooseW;

		cout << "1.Choose a Unit" << endl;
		cout << "2.Insert a Flag" << endl;
		cout << "3.Exit" << endl;
		cout << "Action :";
		cin >> action;
		//Unit
		if (action == "1")
		{
			cout << "Enter the desired Length & Width :";
			cin >> chooseL >> chooseW;
			if (board[chooseL][chooseW] == "0" ||
				board[chooseL][chooseW] == "1" ||
				board[chooseL][chooseW] == "2" ||
				board[chooseL][chooseW] == "3" ||
				board[chooseL][chooseW] == "4" ||
				board[chooseL][chooseW] == "5" ||
				board[chooseL][chooseW] == "6" ||
				board[chooseL][chooseW] == "7" ||
				board[chooseL][chooseW] == "8")
			{
				printboard();
				cout << "<<This house has already been selected.>>" << endl;
				cout << "<<try again.>>" << endl;
			}
			else
			{
				if (board[chooseL][chooseW] == "$")
				{
					cout << "YOU LOST THE GAME!";
					end = true;
				}
				else
				{
					count = 0;
					if (chooseL == length)
					{
						for (int i = chooseL - 1; i <= chooseL; i++)
						{
							for (int j = chooseW - 1; j <= chooseW + 1; j++)
							{
								if (board[i][j] == "$")
								{
									count++;
								}
							}
						}
					}
					else if (chooseL == 1)
					{
						for (int i = chooseL; i <= chooseL + 1; i++)
						{
							for (int j = chooseW - 1; j <= chooseW + 1; j++)
							{
								if (board[i][j] == "$")
								{
									count++;
								}
							}
						}
					}
					else {
						for (int i = chooseL - 1; i <= chooseL + 1; i++)
						{
							for (int j = chooseW - 1; j <= chooseW + 1; j++)
							{
								if (board[i][j] == "$")
								{
									count++;
								}
							}
						}
					}
					if (board[chooseL][chooseW] == "@")
					{
						fakeBomb++;
					}
					board[chooseL][chooseW] = to_string(count);
					printboard();
				}
			}
		}
		//Flag
		else if (action == "2")
		{
			cout << "Enter the desired Length & Width :";
			cin >> chooseL >> chooseW;
			if (board[chooseL][chooseW] == "0" ||
				board[chooseL][chooseW] == "1" ||
				board[chooseL][chooseW] == "2" ||
				board[chooseL][chooseW] == "3" ||
				board[chooseL][chooseW] == "4" ||
				board[chooseL][chooseW] == "5" ||
				board[chooseL][chooseW] == "6" ||
				board[chooseL][chooseW] == "7" ||
				board[chooseL][chooseW] == "8" ||
				board[chooseL][chooseW] == "@")
			{
				printboard();
				cout << "<<This house has already been selected.>>" << endl;
				cout << "<<try again.>>" << endl;
			}
			else
			{
				if (board[chooseL][chooseW] == "$")
				{
					correctBomb++;
				}
				fakeBomb--;
				board[chooseL][chooseW] = "@";
				printboard();
			}
		}
		else if (action == "3")
		{
			system("cls");
			cout << "Thanks for Playing" << endl;
			break;
		}
		else
		{
			printboard();
			cout << "error!!!"<<endl;
			cout << "<<enter the correct word>>"<<endl;
			continue;
		}
	}
}

int main()
{
	while (!Exit)
	{
		printMenu();
		string action;
		cin >> action;
		if (action == "1")
		{
			bool difFlag = false;
			system("cls");
			cout << "Enter Your Username: ";
			cin >> Username;
			system("cls");
			correct = true;
			while (!difFlag)
			{
				string difficulty;

				if (correct)
				{
					cout << "Choose Difficulty Level :" << endl;
					cout << "1.Easy" << endl;
					cout << "2.Medium" << endl;
					cout << "3.Hard" << endl;
					cout << "4.Custom Mode" << endl;
					cout << "5.Exit" << endl;
					cout << "Difficulty Level :";
				}
				else
				{
					cout << "Choose Difficulty Level :" << endl;
					cout << "1.Easy" << endl;
					cout << "2.Medium" << endl;
					cout << "3.Hard" << endl;
					cout << "4.Custom Mode" << endl;
					cout << "5.Exit" << endl;
					cout << "error!!!" << endl;
					cout << "<<enter the correct word>>" << endl;
					cout << "Difficulty Level :";
				}
				cin >> difficulty;
				system("cls");

				if (difficulty == "1")
				{
					difFlag = true;
					realBomb = 10;
					length = 10;
					width = 10;
					setBoard(realBomb);
					playing();
				}
				else if (difficulty == "2")
				{
					difFlag = true;
					realBomb = 40;
					length = 16;
					width = 16;
					setBoard(realBomb);
					playing();
				}
				else if (difficulty == "3")
				{
					difFlag = true;
					realBomb = 99;
					length = 16;
					width = 40;
					setBoard(realBomb);
					playing();
				}
				else if (difficulty == "4")
				{
					difFlag = true;
					cout << "Enter Width :";
					cin >> length;
					cout << "Enter Lenght :";
					cin >> width;
					cout << "Enter the Number of Bombs :";
					cin >> realBomb;
					setBoard(realBomb);
					playing();

				}
				else if (difficulty == "5")
				{
					cout << "Thanks for Playing" << endl;
					break;
				}
				else
				{
					correct = false;
					continue;
				}
			}
			Exit = true;
		}
		else if (action == "2")
		{
			Exit = true;
			system("cls");
			cout << "Thanks for Playing";

		}
		else
		{
			correct = false;
			continue;
		}
	}
}
