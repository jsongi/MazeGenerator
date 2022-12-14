#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <random>
#include <vector>
#include <utility>

//This implementation of a maze generating algorithm uses a randomized version of Prim's algorithm
//   https://en.wikipedia.org/wiki/Maze_generation_algorithm

void generateMaze();
void printMenu();



int main()
{
	char userInput;
	
	printMenu();
	std::cin >> userInput;

	while(userInput != 'x')
	{
		switch (userInput)
		{
			case 'p':
			{
				generateMaze();
				break;
			}
		};
		
		printMenu();
		std::cin >> userInput;
	}
	return 0;
}

void generateMaze()
{
	//Dimensions of the board (needs to be odd numbers)
	const int row = 23;
	const int col = 63;

	//Board
	char maze[row][col];
	
	//Holds coordinates for walls to check
	std::vector<std::pair<int, int>> wallList;
	int selectedWall = 0;
	int selectedRow = 0;
	int selectedCol = 0;

	//Tracks number of non wall cells around a specified wall
	int visitedCells = 0;

	//Logic to prevent walls that may not be adjacent to other walls
	bool oppositeSides = false;
	int topVisitedCells = 0;
	int bottomVisitedCells = 0;
	int leftVisitedCells = 0;
	int rightVisitedCells = 0;

	//Handles game / user data
	std::pair<int, int> playerPosition;
	bool win = false;
	char userInput;

	//Initialize board
	for (int rows = 0; rows < row; rows++)
	{
		for (int cols = 0; cols < col; cols++)
		{
			maze[rows][cols] = '#';
		}
	}

	//Set players position
	playerPosition.first = row - 2;
	playerPosition.second = 1;

	//Add a starting location to the wall list
	wallList.push_back(std::make_pair(row - 2, 1));

	//This is definitely not the proper implementation of the algorithm I was looking but its functional

	//While there are walls in the list
	while (wallList.size() > 0)
	{
		//Select a random wall from the list
		selectedWall = rand() % wallList.size();

		//Get the x y coordinates of the selected wall
		selectedRow = wallList.at(selectedWall).first;
		selectedCol = wallList.at(selectedWall).second;

		//Determines if there are existing cells that are on opposite sides
		for (int rows = -1; rows < 2; rows++)
		{
			if (maze[selectedRow - rows][selectedCol - 1] != '#')
			{
				leftVisitedCells++;
			}
			if (maze[selectedRow - rows][selectedCol + 1] != '#')
			{
				rightVisitedCells++;
			}
		}
		for (int cols = -1; cols < 2; cols++)
		{
			if (maze[selectedRow - 1][selectedCol + cols] != '#')
			{
				topVisitedCells++;
			}
			if (maze[selectedRow + 1][selectedCol - cols] != '#')
			{
				bottomVisitedCells++;
			}
		}

		//If there are not cells that exist on opposite sides of the selected wall
		if (!(topVisitedCells > 0 && bottomVisitedCells > 0) && !(leftVisitedCells > 0 && rightVisitedCells > 0))
		{
			//If only one of the cells that the wall divides is visited
			for (int rows = -1; rows < 2; rows++)
			{
				for (int cols = -1; cols < 2; cols++)
				{
					if (maze[selectedRow - rows][selectedCol - cols] != '#')
					{
						visitedCells++;
					}
				}
			}
		}
		else
		{
			visitedCells = 3;
		}

		//Make the wall a passage (' ') and mark the unvisited cell as part of the maze (visited)
		//Adds only the adjacent cells to the wallList
		if (visitedCells < 3)
		{
			maze[selectedRow][selectedCol] = ' ';

			if (selectedRow - 1 != 0)
			{
				if (maze[selectedRow - 1][selectedCol] != ' ')
				{
					wallList.push_back(std::make_pair(selectedRow - 1, selectedCol));
				}
			}
			if (selectedRow + 1 != row - 1)
			{
				if (maze[selectedRow + 1][selectedCol] != ' ')
				{
					wallList.push_back(std::make_pair(selectedRow + 1, selectedCol));
				}
			}
			if (selectedCol - 1 != 0)
			{
				if (maze[selectedRow][selectedCol - 1] != ' ')
				{
					wallList.push_back(std::make_pair(selectedRow, selectedCol - 1));
				}
			}
			if (selectedCol + 1 != col - 1)
			{
				if (maze[selectedRow][selectedCol + 1] != ' ')
				{
					wallList.push_back(std::make_pair(selectedRow, selectedCol + 1));
				}
			}
		}

		//Remove wall from the list
		wallList.erase(wallList.begin() + selectedWall);
		visitedCells = 0;
		topVisitedCells = 0;
		bottomVisitedCells = 0;
		leftVisitedCells = 0;
		rightVisitedCells = 0;
	}

	//Set player and end position characters
	maze[row - 2][1] = 'p';
	maze[1][col - 2] = 'e';

	//Displays board
	for (int rows = 0; rows < row; rows++)
	{
		for (int cols = 0; cols < col; cols++)
		{
			std::cout << maze[rows][cols];
		}
		std::cout << std::endl;
	}

	//Game logic
	while (!win)
	{
		std::cout << "> ";
		std::cin >> userInput;
		//this should be a switch case..
		switch (userInput)
		{
			case 'w':
			{
				if (maze[playerPosition.first - 1][playerPosition.second] == ' ')
				{
					maze[playerPosition.first - 1][playerPosition.second] = 'p';
					maze[playerPosition.first][playerPosition.second] = ' ';
					playerPosition.first = playerPosition.first - 1;
				}
				else
					if (maze[playerPosition.first - 1][playerPosition.second] == 'e')
						win = true;
				break;
			}
			case 'a':
			{
				if (maze[playerPosition.first][playerPosition.second - 1] == ' ')
				{
					maze[playerPosition.first][playerPosition.second - 1] = 'p';
					maze[playerPosition.first][playerPosition.second] = ' ';
					playerPosition.second = playerPosition.second - 1;
				}
				else
					if (maze[playerPosition.first][playerPosition.second - 1] == 'e')
						win = true;
				break;
			}
			case 's':
			{
				if (maze[playerPosition.first + 1][playerPosition.second] == ' ')
				{
					maze[playerPosition.first + 1][playerPosition.second] = 'p';
					maze[playerPosition.first][playerPosition.second] = ' ';
					playerPosition.first = playerPosition.first + 1;
				}
				else
					if (maze[playerPosition.first + 1][playerPosition.second] == 'e')
						win = true;
				break;
			}
			case 'd':
			{
				if (maze[playerPosition.first][playerPosition.second + 1] == ' ')
				{
					maze[playerPosition.first][playerPosition.second + 1] = 'p';
					maze[playerPosition.first][playerPosition.second] = ' ';
					playerPosition.second = playerPosition.second + 1;
				}
				else
					if (maze[playerPosition.first][playerPosition.second + 1] == 'e')
						win = true;
				break;
			}
			default:
			{
				std::cout << "Invalid input\n";
				break;
			}
		}
		for (int rows = 0; rows < row; rows++)
		{
			for (int cols = 0; cols < col; cols++)
			{
				std::cout << maze[rows][cols];
			}
			std::cout << std::endl;
		}

	}
}

//Prints out option menu
void printMenu()
{
	std::cout << "--=*=--          MENU          --=*=--" << std::endl << std::endl;
	std::cout << "           Start game [ p ]" << std::endl << std::endl;
	std::cout << "            Exit game [ x ]" << std::endl << std::endl;
	std::cout << "--=*=--                        --=*=--" << std::endl;
	std::cout << "> ";
}