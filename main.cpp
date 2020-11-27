#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cctype>
using namespace std;

void board();
void verify(string &num);
void verify2(string &num);
void win_lose_drawCondition(int &win, int &lose, int &draw, int &start);
void screen(int &win, int &lose, int &draw, int &start);

string tile[5][5] = { { "1", "2", "3", "4", "5" },
{ "6", "7", "8", "9", "10" },
{ "11", "12", "13", "14", "15" },
{ "16", "17", "18", "19", "20" },
{ "21", "22", "23", "24", "25" } };

int main()
{
	string num;
	int row, col, win = 0, lose = 0, draw = 0;

	cout << "T   I   C     T   A   C     T   O   E\n\n";
	board();
	cout << "\nReady? Game Start!";
	int start = clock(); //record the start time

	while (win == 0 || lose == 0 || draw == 0)
	{
		cout << "\nPlease choose a number based on the board above: ";
		getline(cin, num);
		verify(num);
		cout << "\nYour turn: " << endl; //player's turn
		for (int i = 0; i < 5; i++)
		{
			cout << "------------------------------------\n";
			cout << "|";
			for (int j = 0; j < 5; j++)
			{
				if (tile[i][j] == num)
				{
					tile[i][j] = "X";
					win_lose_drawCondition(win, lose, draw, start);
				}
				cout << setw(4) << tile[i][j] << setw(3) << "|";
			}
			cout << endl;
		}
		cout << "------------------------------------";

		cout << "\nMy turn: " << endl; //bot's turn
		srand(time(0));
		row = rand() % 5;
		col = rand() % 5;
		while (tile[row][col] == "X" || tile[row][col] == "O")
		{
			row = rand() % 5;
			col = rand() % 5;
		}
		tile[row][col] = "O";
		win_lose_drawCondition(win, lose, draw, start);
		board();
	}
	return 0;
}

void board() //display tictactoe board
{
	for (int i = 0; i < 5; i++)
	{
		cout << "------------------------------------\n";
		cout << "|";
		for (int j = 0; j < 5; j++)
		{
			cout << setw(4) << tile[i][j] << setw(3) << "|";
		}
		cout << endl;
	}
	cout << "------------------------------------";
}

void verify(string &num) //verify the input is a number in range 1-25
{
	bool flag = false;
	while (flag == false)
	{
		if (num == "\0")
			num = "a";
		for (int i = 0; num[i] != '\0'; i++)
		{
			while (!isdigit(num[i]))
			{
				cout << "Invalid Input!\n";
				cout << "\nPlease choose a number based on the board above: ";
				getline(cin, num);
				i = 0;
			}
		}
		int a = stoi(num);
		if (a > 0 && a <= 25)
			flag = true;
		else
			num = "a";
	}
	verify2(num);
}

void verify2(string &num) //verify the input is a valid move
{
	int count = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (tile[i][j] != "X" && tile[i][j] != "O")
			{
				if (num == tile[i][j])
					count++;
			}
		}
	}
	if (count == 0)
	{
		num = "a";
		verify(num);
	}
}

void win_lose_drawCondition(int &win, int &lose, int &draw, int &start)
{
	//check horizontal:
	for (int i = 0; i < 5; i++)
	{
		win = lose = 0; //reset the value of win and lose after one horizontal line
		for (int j = 0; j < 5; j++)
		{
			if (tile[i][j] == "X")
				win++;
			else if (tile[i][j] == "O")
				lose++;
			if (win == 5 || lose == 5)
				screen(win, lose, draw, start);
		}
	}

	//check vertical:
	for (int j = 0; j < 5; j++)
	{
		win = lose = 0; //reset the value of win and lose after one vertical line
		for (int i = 0; i < 5; i++)
		{
			if (tile[i][j] == "X")
				win++;
			else if (tile[i][j] == "O")
				lose++;
			if (win == 5 || lose == 5)
				screen(win, lose, draw, start);
		}
	}

	//check left diagonal:
	win = lose = 0; //reset the value of win and lose after checking the vertical condition
	for (int i = 0, j = 0; i < 5; i++, j++)
	{
		if (tile[i][j] == "X")
			win++;
		else if (tile[i][j] == "O")
			lose++;
		if (win == 5 || lose == 5)
			screen(win, lose, draw, start);
	}

	//check right diagonal:
	win = lose = 0; //reset the value of win and lose after checking the left diagonal condition
	for (int i = 0, j = 4; i < 5; i++, j--)
	{
		if (tile[i][j] == "X")
			win++;
		else if (tile[i][j] == "O")
			lose++;
		if (win == 5 || lose == 5)
			screen(win, lose, draw, start);
	}

	//check all the tiles whether they are occupied by number or X or O
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (tile[i][j] == "X" || tile[i][j] == "O")
				draw++;
		}
	}

	if (draw == 25) //draw if all the tiles are occupied by X and O
		screen(win, lose, draw, start);
	else
		draw = 0; //reset the value of draw after one turn
}

void screen(int &win, int &lose, int &draw, int &start) //display this screen when the game end
{
	system("cls"); //clear the screen
	board();

	if (win == 5)
		cout << "\nCongratulations! You win! " << endl;
	else if (lose == 5)
		cout << "\nUnfortunately, You lose!" << endl;
	else if (draw == 25)
		cout << "\nDraw!" << endl;

	int time;
	int end = clock(); //record the end time
	time = end - start; //calculate execution time

	cout << "You took approximately " << float(end) / CLOCKS_PER_SEC << " seconds to play this game." << endl;
	exit(0);
}