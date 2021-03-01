/*
    Artifical Intelligence Project 1:
    Jeff Wilson
    Joe McAdams
    Brandon Burtchell

    Spring 2021
*/

#include "Project1.h"

using namespace std;

Conclusion conclusionList[CONCLUSION_LIST_SIZE];
Clause variableList[VARIABLE_LIST_SIZE];
string clauseVariableList[CLAUSE_VAR_LIST_SIZE];
stack<Conclusion> conclusionStack;
stack<Clause> clauseStack;

// TODO: define these functions below main (return types are just placeholder, change if needed)
void diagnosis();
void treatment();
int searchConclusionList(string, int);
int searchVariableList(string);
void instantiate(string);
void testPrintLists();
bool useKnowledgeBase(int);

Conclusion finalDiagnosis;    // This will hold the result of our diagnosis functions.

int main() {
  cout << "--- Cancer Diagnosis and Treatment Recommendation ---" << endl << endl;
  cout << "You will be prompted to enter information regarding the patient, answer to the best of your ability." << endl << endl;
  cout << "Answer Symptom Related Questions with either 'YES' or 'NO'" << endl;

  // manually instantiating the conclusion list:
  conclusionList[1].init("cancer", "NONE", 1);
  conclusionList[2].init("pos_cancer", "SUB", 2);
  conclusionList[3].init("pos_thy_cancer", "SUB", 3);
  conclusionList[4].init("cant_diag", "SUB", 4);
  conclusionList[5].init("thy_cancer", "SUB", 5);
  conclusionList[6].init("cancer", "MEDULLARY THYROID", 6);
  conclusionList[7].init("cancer", "PAPILLARY THYROID", 7);
  conclusionList[8].init("cancer", "FOLLICULAR THYROID", 8);
  conclusionList[9].init("cancer", "ANAPLASTIC THYROID", 9);

  // manually instantiating the variable list:
  variableList[1].init("symptoms", "any symptoms");
  variableList[2].init("fat_wl", "fatigue or weight loss");
  variableList[3].init("neLu_difBre_swNeGl", "neck lump, difficulty breathing, or swollen neck glands");
  variableList[4].init("high_calc", "high calcitonin levels");
  variableList[5].init("age", "AGE");
  variableList[6].init("loss_app", "loss of appetite");
  variableList[7].init("fr_di_paUr", "frequent, difficult, or painful urinating");
  variableList[8].init("hiBlIn_LoTeCaUs", "history of bladder infection or long term cetheter use");
  variableList[9].init("persFever", "persistent fever");
  variableList[10].init("shBr_chPa_coBl", "shortness of breath, chest pain, or coughing up blood");
  variableList[11].init("hiSm_seHaSmEx", "history of smoking or second-hand smoking exposure");
  variableList[12].init("ra_as_urEx", "radon, asbestos, or uranium exposure");
  variableList[13].init("ja_na_ab_shPa", "jaundice, nausea, or abdominal or shoulder pain");
  variableList[14].init("CVA_an", "CVA mass or anemia");
  variableList[15].init("tubules", "cancer cells originated tubules");
  variableList[16].init("renal_pelvis", "cancer cells originated in renal pelvis");
  variableList[17].init("sw_ch_buSt_bl", "sweats, chills, burning stomach, or bloating");
  variableList[18].init("enLi_sp_it_feFuEa", "enlarged liver or spleen, itching, or feeling full easily");
  variableList[19].init("grInLi", "tentacle or nodule growth in liver");
  variableList[20].init("bile_duct", "cancer cells originated in bilde duct");
  variableList[21].init("exocrine_component", "cancer cells originated in exocrine component of the pancreas");
  variableList[22].init("ducts", "cancer cells originated in ducts of the pancreas");
  
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

  testPrintLists();
 
  diagnosis();
  //treatment();

  return 0;
}

void diagnosis(){
 int conclusion_Counter = 1;  // Keep track of how far the conclusionList has been traversed. We need to advance in our search.
 string conclusion = "cancer";  // Identify the conclusion
 int index, count, i;
 bool terminateFunction = false;    // Will be set to true by knowledge base if we hit a terminating conclusion.
 cout << "1. Identify the conclusion. " << endl // DONE
       << "2. Search the conclusion list for the first instance of the conclusion's name. If found, place the rule on the conclusion stack using the rule number and a (1) to represent the clause number. If not found, notify the user that an answer cannot be found." << endl
       << "3. Instantiate the IF clause (i.e., each condition variable) of the statement." << endl
       << "4. If one of the IF clause variables is not instantiated, as indicated by the variable list, and is not a conclusion variable, that is, not on the conclusion list, ask the user to enter a value." << endl
       << "5. If one of the clauses is a conclusion variable, place the conclusion variable's rule number on the top of the stack and go back to step 3." << endl
       << "6. If the statement on top of the stack cannot be instantiated using the present IF-THEN statement, remove the unit from the top of the stack and search the conclusion list for another instance of that conclusion variable's name." << endl
       << "7. If such a statement is found, go back to step 3." << endl
       << "8. If there are no more conclusions left on the conclusion stack with that name, the rule for the previous conclusion is false. If there is no previous conclusion, then notify the user that an answer cannot be found. If there is a previous conclusion, go back to step 6." << endl
       << "9. If the rule on top of the stack can be instantiated, remove it from the stack. If another conclusion variable is underneath, increment the clause number, and for the remaining clauses go back to step 3. If no other conclusion variable is underneath, we have answered our question. The user can come to a conclusion." << endl;

  for(int i = 1; i <= CONCLUSION_LIST_SIZE && terminateFunction == false; i++){

    cout << "hit top of for loop" << endl;
    count = 0;

    // Search for the Conclusion
    
    index = searchConclusionList(conclusion, conclusion_Counter);
    conclusion_Counter = index + 1;
    cout << "Index: " << index << endl;
    cout << "Conclusion Counter: " << conclusion_Counter << endl;
    
    if(index != 0){   // We found the item in the conclusionList
      conclusionStack.push(conclusionList[index]);    // Step 2 Done?
    }
    else{
      continue; // We did not find the conclusion
    }

    if(conclusionStack.empty() == false){
        i = conclusionStack.top().clauseNumber;   // Go to top of the stack
    }

    // Search for the Variables
    do{
        if (clauseVariableList[i + count] != "")
        {
          index = searchVariableList(clauseVariableList[i + count]);    // Index now holds the location of the corresponding symptom in variableList
          if (index != 0)   // Found the item in varaible list
          {
            if(variableList[index].instantiated == false)
            {
              instantiate(variableList[index].name);    // Step 3 and 4 Done?
            }
          }
          else    // The Item was not on the varaiable list. So it must be a conclusion variable. Handle it!
          {
              index = searchConclusionList(clauseVariableList[i + count], 1);   // Send 1 to start at the beginning of the list. Index will hold the location of the conclusion in conclusion list.
              if(index != 0){   // We found the item in the conclusionList. So now we need to push it to the stack.
                conclusionStack.push(conclusionList[index]);    
              }
              else{
                continue; // We did not find the conclusion in the conclusion list.
              }
          }
        }
        count++;
    }while(clauseVariableList[i] != "" && count < 6);
    cout << "HIT 2!" << endl;
    terminateFunction = useKnowledgeBase(conclusionStack.top().ruleNumber);
  }

  if(terminateFunction == true){
    cout << "Final Diagnosis: " << finalDiagnosis.name << " = " << finalDiagnosis.finalConclusion << endl;
  }
  // testPrintLists();
  // useKnowledgeBase(conclusionStack.top().ruleNumber);

}

    
  


int searchConclusionList(string conc, int conclusion_Counter)
{
  cout << "Conc: " << conc << endl;
  int index = 0;
  for(int i = conclusion_Counter; i <= CONCLUSION_LIST_SIZE; i++)
  {
    if(conc == conclusionList[i].name) // (conc.compare(conclusionList[i].name) != 0)???
    {
      index = i;
      break;
    }
    else{
      cout << "Error! The item '" << conc << "' could not be found." << endl;
      break;
    };
  }
  return index;
}

int searchVariableList(string clauseVariable)
{
  cout << "Variable: " << clauseVariable << endl;
  int index = 0;
  for(int i = 1; i <= VARIABLE_LIST_SIZE; i++)
  {
    cout << variableList[i].name << endl;
    if(clauseVariable == variableList[i].name)    // (conc.compare(conclusionList[i].name) != 0)???
    {
      index = i;
      return index;
    }
    else{
      cout << "Error! The item '" << clauseVariable << "' could not be found." << endl;
    };
  }
  return index;
}

void instantiate(string str)
{
  string answer;
  for(int i = 1; i <= VARIABLE_LIST_SIZE; i++)
  {
    if (variableList[i].name == str && !variableList[i].instantiated)
    {
      variableList[i].instantiated = true;
      cout << "Do you have " << variableList[i].print << "?" << endl;
      cin >> (answer);
      if (answer == "yes" || answer == "YES")
        variableList[i].experiencing = true;
      // cout << "HIT BREAK!" << endl;
      break;
    }
  }
}


void treatment(){
  cout << "Use Forward Chaining Here!" << endl;
}

void testPrintLists()
{
  cout << "--- Varaible List --- " << endl;
  for(int i = 1; i < 9; i++){    // Replace 9 with VARIABLE_LIST_SIZE when done with small testing
    cout << i << " Name: " << variableList[i].name << endl;
    cout << i << " Print Name: " << variableList[i].print << endl;
    cout << i << " Instantiated: (0 = False, 1 = True) " << variableList[i].instantiated << endl;
    cout << i << " Experiencing: (0 = False, 1 = True) " << variableList[i].experiencing << endl;
  }
  cout << endl;
  cout << "--- Conclusion List ---" << endl;
  for(int i = 1; i < 9; i++){    // Replace 9 with CONCLUSION_LIST_SIZE when done with small testing
    cout << i << " Name: " << conclusionList[i].name << endl;
    cout << i << " Final Conclusion: " << conclusionList[i].finalConclusion << endl;
    cout << i << " Rule Number: " << conclusionList[i].ruleNumber << endl;
  }
  
}

bool useKnowledgeBase(int ruleNumber){
  bool terminateDiagnosisAlgorithm = false;
  
  cout << "Hit KB!" << endl;

  // Create a switch statement and all of the if then statements with the cases. Reference example.

  switch (ruleNumber)
  {
  case 1:
    if(variableList[1].experiencing == false)
    {
      cout << "Case 1 Value: " << variableList[1].experiencing << endl;
      terminateDiagnosisAlgorithm = true;
      finalDiagnosis = conclusionList[ruleNumber];
    }
    else{
      conclusionStack.pop();
    }
    break;
  
  default:
    cout << "You should not be here!" << endl;
    break;
  }
  
  return terminateDiagnosisAlgorithm;
}