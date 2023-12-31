#include <iostream>
using namespace std;

void readAPuzzle(int grid[][9]);
bool search(int grid[][9]);
int getFreeCellList(const int grid[][9], int freeCellList[][2]);
void printGrid(const int grid[][9]);
bool isValid(int i, int j, const int grid[][9]);
bool isValid(const int grid[][9]);

int main()
{
  // Read a Sudoku puzzle
  int grid[9][9];
  readAPuzzle(grid);

  if (!isValid(grid))
    cout << "Invalid input" << endl;
  else if (search(grid))
  {
    cout << "The solution is found:" << endl;
    printGrid(grid);
  }
  else
    cout << "No solution" << endl;

  return 0;
}

/** Read a Sudoku puzzle from the keyboard */
void readAPuzzle(int grid[][9])
{
  // Create a Scanner
  cout << "Enter a Sudoku puzzle:" << endl;
  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++)
      cin >> grid[i][j];
}

/** Obtain a list of free cells from the puzzle */
int getFreeCellList(const int grid[][9], int freeCellList[][2])
{
  // 81 is the maximum number of free cells
  int numberOfFreeCells = 0;

  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++)
      if (grid[i][j] == 0)
      {
        freeCellList[numberOfFreeCells][0] = i;
        freeCellList[numberOfFreeCells][1] = j;
        numberOfFreeCells++;
      }

  return numberOfFreeCells;
}

/** Display the values in the grid */
void printGrid(const int grid[][9])
{
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
      cout << grid[i][j] << " ";
    cout << endl;
  }
}

/** Search for a solution */
bool search(int grid[][9])
{
  int freeCellList[81][2]; // Declare freeCellList
  int numberOfFreeCells = getFreeCellList(grid, freeCellList);
  if (numberOfFreeCells == 0)
    return true; // No free cells

  int k = 0; // Start from the first free cell
  while (true)
  {
    int i = freeCellList[k][0];
    int j = freeCellList[k][1];
    if (grid[i][j] == 0)
      grid[i][j] = 1; // Fill the free cell with number 1

    if (isValid(i, j, grid))
    {
      if (k + 1 == numberOfFreeCells)
      { // No more free cells
        return true; // A solution is found
      }
      else
      { // Move to the next free cell
        k++;
      }
    }
    else if (grid[i][j] < 9)
    {
      // Fill the free cell with the next possible value
      grid[i][j] = grid[i][j] + 1;
    }
    else
    { // grid[i][j] is 9, backtrack
      while (grid[i][j] == 9)
      {
        if (k == 0)
        {
          return false; // No possible value
        }
        grid[i][j] = 0; // Reset to free cell
        k--; // Backtrack to the preceding free cell
        i = freeCellList[k][0];
        j = freeCellList[k][1];
      }

      // Fill the free cell with the next possible value,
      // search continues from this free cell at k
      grid[i][j] = grid[i][j] + 1;
    }
  }

  return true; // A solution is found
}

/** Check whether grid[i][j] is valid in the grid */
bool isValid(int i, int j, const int grid[][9])
{
  // Check whether grid[i][j] is valid at the i's row
  for (int column = 0; column < 9; column++)
    if (column != j && grid[i][column] == grid[i][j])
      return false;

  // Check whether grid[i][j] is valid at the j's column
  for (int row = 0; row < 9; row++)
    if (row != i && grid[row][j] == grid[i][j])
      return false;

  // Check whether grid[i][j] is valid in the 3 by 3 box
  for (int row = (i / 3) * 3; row < (i / 3) * 3 + 3; row++)
    for (int col = (j / 3) * 3; col < (j / 3) * 3 + 3; col++)
      if (row != i && col != j && grid[row][col] == grid[i][j])
        return false;

  return true; // The current value at grid[i][j] is valid
}

/** Check whether the fixed cells are valid in the grid */
bool isValid(const int grid[][9])
{
  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++)
      if (grid[i][j] < 0 || grid[i][j] > 9 ||
         (grid[i][j] != 0 && !isValid(i, j, grid)))
        return false;

  return true; // The fixed cells are valid
}
