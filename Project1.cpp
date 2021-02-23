/* insert header */

#include <iostream>
using namespace std;

// TODO: define these functions below main (return types are just placeholder, change if needed)
void readPatientFile(string filename); // FIXME: pass fstream as argument instead?
void diagnosis();
void treatment();

int main() {
  string userInput = '';
  // TODO: define knowledge base, inference base, etc. variables

  // TODO: add welcome message

  // TODO: ask user if they want to enter a patient file (.txt), or enter the info manually.
  cout << "Would you like to userInput a patient file (.txt)? (y/n): ";
  cin >> userInput;
  if (userInput == "y" || userInput == "Y") {
    cout << "Enter the file name: ";
    cin >> userInput;
    readPatientFile(userInput); // FIXME: could probably implemented as a class
  } else {
    // TODO: tediously ask for patient's symptoms
  }

  /* TODO: prompt user to run either function
  diagnosis();
  treatment();
  */

  return 0;
}

// TODO: define functions