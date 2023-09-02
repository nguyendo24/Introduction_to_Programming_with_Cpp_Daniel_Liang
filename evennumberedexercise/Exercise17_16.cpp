#include <iostream>
using namespace std;

int countMoves = 0;

/* The function for finding the solution to move n disks from fromTower to toTower with auxTower */
void moveDisks(int n, char fromTower, char toTower, char auxTower)
{
  countMoves++;

  if (n == 1) // Stopping condition
         cout << "Move disk " << n << " from " << fromTower << " to " << toTower << endl;
  else
  {
    moveDisks(n - 1, fromTower, auxTower, toTower);
    cout << "Move disk " << n << " from " << fromTower << " to " << toTower << endl;
    moveDisks(n - 1, auxTower, toTower, fromTower);
  }
}

int main()
{
  // Read number of disks, n
  cout << "Enter number of disks: ";
  int n;
  cin >> n;

  // Find the solution recursively
  cout << "The moves are: " << endl;
  moveDisks(n, 'A', 'B', 'C');

  cout << "The number of the moves is " << countMoves << endl;

  return 0;
}
