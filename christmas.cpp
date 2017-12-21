#include <iostream>
#include <vector>
#include "rlutil/rlutil.h"

using namespace std;

bool isOdd(int n) {
	if (n % 2 == 1) {
		return true;
	}
	else {
		return false;
	}
}

int main()
{
	int defaultColor;
	rlutil::saveDefaultColor();

	int rows;

	cout << "Enter the height of the christmas tree: " << endl;
	cin >> rows;
	cout << "Height: " << rows << endl;

	/* 
	 * Generate a christmas tree using the height input by user
	 */
	int spaces;
	int numTiers; 
	int rem; 

	numTiers = rows / 3;
	rem = rows % 3;

	spaces = numTiers + 1;

	if (rem == 1) { spaces++; }

	if (rows == 5) { spaces++; }  // 5 rows makes the output weird. So need this exclusively for 5 rows
	else if (rem == 2) { spaces += 2; }

	/*
 	 * Vector to represent the tree
	 * Using vector allows us a scalable xmas tree
	 * Iterator so we can access each character of the tree to decorate it
	 */
	vector<char> vtree;
	vector<char>::iterator it;

	int leavesInRow = 1;
	int leavesInLastRow;
	int rowCount = 0; // keep track of which row we've just printed 

	for (int i = 0; i < numTiers; i++)  // for each tier
	{
		rowCount = 0;

		while (true) {

			for (int s = 0; s < spaces; s++) {
				vtree.push_back(' ');
			}
			spaces--;

			for (int j = 0; j < leavesInRow; j++)
			{
				vtree.push_back('*');
			}
			rowCount++;  // increment after each row
			vtree.push_back('\n');

			if (rem == 0) {
				if (rowCount == 3) {  // when we've done the 3rd row of the tier
					spaces+=2;
					leavesInRow -= 2;  // set the leaves for next row 
					break;  // move onto next tier
				}
				else {
					leavesInRow += 2;
					leavesInLastRow = leavesInRow;
				}
			}	
			
			else if (rem == 1) {
				if ((rowCount == 3) && (i != numTiers - 1)) { // when we've done third row of the tier and we're not on the last tier
					spaces += 2;
					leavesInRow -= 2;  // set the leaves for next row 
					break;  // move onto next tier
				}
				else if ((rowCount == 3) && (i == numTiers - 1)) { // when we've done third row of the last tier
					spaces += 2;
					leavesInRow += 2;  // set the leaves for the next row
					for (int j = 0; j < leavesInRow; j++)  // add an extra row
					{
						vtree.push_back('*');
					}
					vtree.push_back('\n');
					rowCount++;
					leavesInLastRow = leavesInRow;
					break;  // just done the last tier, so should exit while loop and tier for loop will end
				}
				else {
					leavesInRow += 2;
				}
			}
			
			else {  // if rem==2
				if (rowCount >= 3) { // when we've done the third row
					// check which tier we're on
					if (i == numTiers - 2) {  // if we're on the second to last tier
						leavesInRow += 2;  // set the leaves for the next row
						for (int s = 0; s < spaces; s++) {
							vtree.push_back(' ');
						}
						for (int j = 0; j < leavesInRow; j++)  // add an extra row
						{
							vtree.push_back('*');
						}
						vtree.push_back('\n');
						rowCount++;
						spaces ++;
						leavesInRow -= 2;
						break; // will go to last tier
					}
					else if (i == numTiers - 1) {  // if we're on the last tier
						leavesInRow += 2;  // set the leaves for the next row
						for (int j = 0; j < leavesInRow; j++)  // add an extra row
						{
							vtree.push_back('*');
						}
						vtree.push_back('\n');
						rowCount++;
						leavesInLastRow = leavesInRow;
						break; // will exit as we've done the last tier
					}
					else {
						spaces += 2;
						leavesInRow -= 2;  // set the leaves for next row 
						break;  // move onto next tier
					}
				}
				else {
					leavesInRow += 2;
				}
			}
		}
	}

	/*
	 * Count number of leaves of the tree
	 */
	int numLeaves = 0;

	for (it = vtree.begin(); it != vtree.end(); ++it)
	{
		if (*it == '*') {
			numLeaves++;
		}
	}

	string ans;
	bool valid = false;
	bool decorate;

	while (!valid) {
		cout << "Would you like to decorate the tree? (Y/N)" << endl;
		cin >> ans;
		if (ans == "Y") {
			valid = true;
			decorate = true;
			break;
		}
		if (ans == "N") {
			valid = true;
			decorate = false;
			break;
		}
		cout << "Not a valid answer, please enter Y or N" << endl;
	}

	if (decorate) {
		cout << "You have chosen to decorate the tree." << endl;
		int countLeaves = numLeaves;
		for (it = vtree.begin(); it != vtree.end(); ++it)
		{ 
			numLeaves--;

			if (numLeaves % 4 == 0) {
				if (*it == '*') {
					*it = 'o';
				}
			}
		}
	}
	else {
		cout << "You chose not to decorate the tree." << endl;
	}

	rlutil::setColor(2); // GREEN
	/*
	 * Print the tree
	 */
	for (it=vtree.begin(); it!=vtree.end(); ++it)
	{
		if (*it == 'o') {
			rlutil::setColor(15); // WHITE
			cout << *it;
			rlutil::setColor(2);
		}
		else {
			cout << *it;
		}
	}

	int trunkSize;
	int trunkWidth;
	int trunkHeight;
	
	trunkWidth = leavesInLastRow / 5;

	if (!isOdd(trunkWidth)) {
		trunkWidth--;
	}

	if (numTiers > 1) {
		trunkHeight = numTiers / 2;
	}
	else {
		trunkHeight = numTiers;
	}
	
	trunkSize = trunkWidth * trunkHeight;

	vector<char> vtrunk;
	
	while (trunkSize > 0) {
		for (int i = 0; i < trunkHeight; i++) {
			for (int i = 0; i < (leavesInLastRow/2 - trunkWidth/2); i++) {
				vtrunk.push_back(' ');
			}
			for (int j = 0; j < trunkWidth; j++) {
				vtrunk.push_back('*');
				trunkSize--;
			}
			vtrunk.push_back('\n');
		}
	}
	

	rlutil::setColor(6); // BROWN
	/*
	* Print the trunk
	*/
	for (it = vtrunk.begin(); it != vtrunk.end(); ++it)
	{
		cout << *it;
	}
	

	rlutil::resetColor();

	printf("Number of tiers: %d\n", numTiers);

	return 0;
}
