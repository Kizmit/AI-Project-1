/*
    Artifical Intelligence Project 1:
    Jeff Wilson
    Joe McAdams
    Brandon Burtchell

    Spring 2021
*/


#include "Project1.h"
using namespace std;

// Will be Instantiated in main() - See Below **** Will probably be changed
struct conclusionList[CONCLUSION_LIST_SIZE]//[LIST_WIDTH]; commented this out for now; I think we don't need 2D here
struct variableList[VARIABLE_LIST_SIZE]//[LIST_WIDTH];
string clauseVariableList[CLAUSE_VAR_LIST_SIZE];
stack<struct> conclusionStack;
stack<struct> clauseStack;


// TODO: define these functions below main (return types are just placeholder, change if needed)
void diagnosis();
void treatment();

int main() {
  cout << "--- Cancer Diagnosis and Treatment Recommendation ---" << endl << endl;
  cout << "You will be prompted to enter information regarding the patient, answer to the best of your ability." << endl << endl;
  cout << "Answer Symptom Related Questions with either 'YES' or 'NO'" << endl;

  /*
  cout<< "Enter the Age of the Patient:  ";
  cin >> Patient_Age; 
  */ 

  //TODO: Agree on the Structure List Google Doc, then do the below items.

  //TODO: Manually Instantiate conclusionList.
  //How it would look with a 2D array; it doesn't make much sense
  /*conclusionList[1][0] = "1"; //Conclusion 1 corresponds to rule 1 (is this really necessary? index will correspond to rule #)
  conclusionList[1][1] = "canc"; //Conclusion 1 is cancer
  conclusionList[1][2] = "symp"; //Condition is whether or not patient has symptoms (is this really necessary? clauseVarList has corresponding conditions)
  conclusionList[2][0] = "2"
  conclusionList[2][1] = "canc"
  conclusionList[2][2] = "symp"
  conclusionList[3][0] = "3"
  conclusionList[3][1] = "pos_thy_canc"
  conclusionList[3][2] = "pos_canc, fat_wl"*/

  conclusionList[1] = struct Conclusion("cancer", "NONE", 1);
  conclusionList[2] = struct Conclusion("pos_cancer", "SUB", 2);
  conclusionList[3] = struct Conclusion("pos_thy_cancer", "SUB", 3);
  conclusionList[4] = struct Conclusion("cant_diag", "SUB", 4);
  conclusionList[5] = struct Conclusion("thy_cancer", "SUB", 5);
  conclusionList[6] = struct Conclusion("cancer", "MEDULLARY THYROID", 6);
  conclusionList[7] = struct Conclusion("cancer", "PAPILLARY THYROID", 7);
  conclusionList[8] = struct Conclusion("cancer", "FOLLICULAR THYROID", 8);
  conclusionList[9] = struct Conclusion("cancer", "ANAPLASTIC THYROID", 9);

  //TODO: Manually Instantiate variableList.
  //index 2 of each variables index in the list would be the value of the variable; update with user input as program goes
  /*variableList[1][0] = "symptoms"; //variable corresponds to rule 1
  variableList[1][1] = "NI";  //initially not instantiated
  variableList[2][0] = "fatigue"; 
  variableList[2][1] = "NI";
  variableList[3][0] = "weight_loss"; 
  variableList[3][1] = "NI";
  variableList[4][0] = "neck_lu"; 
  variableList[4][1] = "NI";
  variableList[5][0] = "dif_bre"; 
  variableList[5][1] = "NI";
  variableList[6][0] = "swol_neck_glands"; 
  variableList[6][1] = "NI";
  variableList[7][0] = "high_calc"; 
  variableList[7][1] = "NI";
  variableList[8][0] = "age"; 
  variableList[8][1] = "NI";*/

  variableList[1] = struct Clause("symptoms", "symptoms");
  variableList[2] = struct Clause("fat_wl", "fatigue or weight loss");
  variableList[3] = struct Clause("neLu_difBre_swNeGl", "any of the following: neck lump, difficulty breathing, or swollen neck glands");
  variableList[4] = struct Clause("high_calc", "high calcitonin levels");
  variableList[5] = struct Clause("age");
  
  
  //TODO: Manually Instantiate clauseVariableList.
  clauseVariableList[1] = "symptoms";
  clauseVariableList[7] = "symptoms";
  clauseVariableList[13] = "pos_canc";
  clauseVariableList[14] = "fat_wl";
  clauseVariableList[19] = "pos_thy_canc";
  clauseVariableList[20] = "neLu_difBre_swNeGl";
  clauseVariableList[25] = "cant_diag";
  clauseVariableList[26] = "pos_thy_canc";
  clauseVariableList[31] = "thy_canc";
  clauseVariableList[32] = "high_calc";
  clauseVariableList[37] = "thy_canc";
  clauseVariableList[38] = "age";
  clauseVariableList[39] = "high_calc";
  clauseVariableList[43] = "thy_canc";
  clauseVariableList[44] = "age";
  clauseVariableList[45] = "high_calc";
  clauseVariableList[49] = "thy_canc";
  clauseVariableList[50] = "age";
  clauseVariableList[51] = "high_calc"; 
 
  diagnosis();
  treatment();

  return 0;
}

// TODO: define functions

void diagnosis(){
 int conclusion_Counter = 1;
 int index, count, i;
 count = 0;
 bool flag = false;
 cout << "1. Identify the conclusion. " << endl
       << "2. Search the conclusion list for the first instance of the conclusion's name. If found, place the rule on the conclusion stack using the rule number and a (1) to represent the clause number. If not found, notify the user that an answer cannot be found." << endl
       << "3. Instantiate the IF clause (i.e., each condition variable) of the statement." << endl
       << "4. If one of the IF clause variables is not instantiated, as indicated by the variable list, and is not a conclusion variable, that is, not on the conclusion list, ask the user to enter a value." << endl
       << "5. If one of the clauses is a conclusion variable, place the conclusion variable's rule number on the top of the stack and go back to step 3." << endl
       << "6. If the statement on top of the stack cannot be instantiated using the present IF-THEN statement, remove the unit from the top of the stack and search the conclusion list for another instance of that conclusion variable's name." << endl
       << "7. If such a statement is found, go back to step 3." << endl
       << "8. If there are no more conclusions left on the conclusion stack with that name, the rule for the previous conclusion is false. If there is no previous conclusion, then notify the user that an answer cannot be found. If there is a previous conclusion, go back to step 6." << endl
       << "9. If the rule on top of the stack can be instantiated, remove it from the stack. If another conclusion variable is underneath, increment the clause number, and for the remaining clauses go back to step 3. If no other conclusion variable is underneath, we have answered our question. The user can come to a conclusion." << endl;
  
  index = searchConclusionList("cancer");
  
  while (flag == false){
    conclusionStack.push(conclusionList[index]);
    count++;
    do{
      i = conlusionStack.top().clauseNumber;
      if (clauseVariableList[i] != "")
      {
        index = searchConclusionList(clauseVariableList[i])
        if (index != 0)
        {
          flag = true;
        }
        else
        {
          instantiate(clauseVariableList[index]);
        }
      }
    }while(clauseVariableList[i] != "" && count < 6); //LEFT OFF HERE. LOOPS ARENT CONTROLLED QUITE RIGHT
  }

}

int searchConclusionList(string conc)
{
  int index = 0;
  for(int i = 1; i <= conclusionList.size(); i++)
  {
    if(conc = conclusionList[i].name)
    {
      index = i;
      break;
    }
    else continue;
  }
  return index;
}

void instantiate(string str)
{
  string answer;
  for(int i = 1; i <= variableList.size(); i++)
  {
    if (variableList[i].name == str && !variableList[i].instantiated)
    {
      variableList[i].instantiated = true;
      printf("Do you have %s", variableList[i].print);
      cin >> (answer);
      if (answer == "yes" || answer == "YES")
        variableList[i].experiencing = true;
      break;
    }
  }
}


void treatment(){
  cout << "Use Forward Chaining Here!" << endl;
}