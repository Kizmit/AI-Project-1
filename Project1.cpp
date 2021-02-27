/*
    Artifical Intelligence Project 1:
    Jeff Wilson
    Joe McAdams
    Brandon Burtchell

    Spring 2021
*/

#include <iostream>
#include "Project1.h"

using namespace std;

int Patient_Age;

string conclusionList[CONCLUSIONS_AMOUNT][LIST_WIDTH];
string variableList[VARIABLE_AMOUNT][LIST_WIDTH];
string clauseVariableList[CLAUSE_VAR_LIST_SIZE];



// TODO: define these functions below main (return types are just placeholder, change if needed)
void diagnosis();
void treatment();

int main() {

  cout << "--- Cancer Diagnosis and Treatment Recommendation ---" << endl << endl;
  cout << "You will be prompted to enter information regarding the patient, answer to the best of your ability." << endl << endl;

  cout<< "Enter the Age of the Patient:  ";
  cin >> Patient_Age; 
  

  diagnosis();
  treatment();

  return 0;
}

// TODO: define functions

void diagnosis(){
  cout << "--- Entered Diagnosis Function ---" << endl << endl;
  cout << "1. Identify the conclusion. " << endl
       << "2. Search the conclusion list for the first instance of the conclusion's name. If found, place the rule on the conclusion stack using the rule number and a (1) to represent the clause number. If not found, notify the user that an answer cannot be found." << endl
       << "3. Instantiate the IF clause (i.e., each condition variable) of the statement." << endl
       << "4. If one of the IF clause variables is not instantiated, as indicated by the variable list, and is not a conclusion variable, that is, not on the conclusion list, ask the user to enter a value." << endl
       << "5. If one of the clauses is a conclusion variable, place the conclusion variable's rule number on the top of the stack and go back to step 3." << endl
       << "6. If the statement on top of the stack cannot be instantiated using the present IF-THEN statement, remove the unit from the top of the stack and search the conclusion list for another instance of that conclusion variable's name." << endl
       << "7. If such a statement is found, go back to step 3." << endl
       << "8. If there are no more conclusions left on the conclusion stack with that name, the rule for the previous conclusion is false. If there is no previous conclusion, then notify the user that an answer cannot be found. If there is a previous conclusion, go back to step 6." << endl
       << "9. If the rule on top of the stack can be instantiated, remove it from the stack. If another conclusion variable is underneath, increment the clause number, and for the remaining clauses go back to step 3. If no other conclusion variable is underneath, we have answered our question. The user can come to a conclusion." << endl;
}

void treatment(){
  cout << "Use Forward Chaining Here!" << endl;
}