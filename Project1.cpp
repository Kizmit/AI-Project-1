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

  // populating the conclusion list:
  conclusionList[1].init("cancer", "NONE", 1);
  conclusionList[2].init("pos_cancer", "SUB", 2);
  conclusionList[3].init("pos_thy_cancer", "SUB", 3);
  conclusionList[4].init("cant_diag", "CAN'T DIAGNOSE", 4);
  conclusionList[5].init("thy_cancer", "SUB", 5);
  conclusionList[6].init("cancer", "MEDULLARY THYROID CANCER", 6);
  conclusionList[7].init("cancer", "PAPILLARY THYROID CANCER", 7);
  conclusionList[8].init("cancer", "FOLLICULAR THYROID CANCER", 8);
  conclusionList[9].init("cancer", "ANAPLASTIC THYROID CANCER", 9);
  conclusionList[10].init("pos_bla_cancer", "SUB", 10);
  conclusionList[11].init("cant_diag", "CAN'T DIAGNOSE", 11);
  conclusionList[12].init("bla_cancer", "SUB", 12);
  conclusionList[13].init("cancer", "SQUAMOUS CELL CARCINOMA", 13);
  conclusionList[14].init("cancer", "UROTHELIAL CARCINOMA", 14);
  conclusionList[15].init("pos_lung_cancer", "SUB", 15);
  conclusionList[16].init("cant_diag", "CAN'T DIAGNOSE", 16);
  conclusionList[17].init("lung_cancer", "SUB", 17);
  conclusionList[18].init("cancer", "NON-SMALL CELL LUNG CANCER", 18);
  conclusionList[19].init("cancer", "NON-SMALL CELL LUNG CANCER", 19);
  conclusionList[20].init("cancer", "SMALL CELL LUNG CANCER", 20);
  conclusionList[21].init("pos_kid_cancer", "SUB", 21);
  conclusionList[22].init("cant_diag", "CAN'T DIAGNOSE", 22);
  conclusionList[23].init("kid_cancer", "SUB", 23);
  conclusionList[24].init("cancer", "RENAL CELL CARCINOMA", 24);
  conclusionList[25].init("cancer", "UROTHELIAL CARCINOMA", 25);
  conclusionList[26].init("cancer", "SARCOMA OF THE KIDNEY", 26);
  conclusionList[27].init("pos_liver_cancer", "SUB", 27);
  conclusionList[28].init("cant_diag", "CANT'T DIAGNOSE", 28);
  conclusionList[29].init("liver_cancer", "LIVER CANCER", 29);
  conclusionList[30].init("cancer", "HEPATOCELLULAR CARCINOMA", 30);
  conclusionList[31].init("cancer", "ANGIOSARCOMA", 31);
  conclusionList[32].init("cancer", "CHOLANGIOCARCINOMA", 32);
  conclusionList[33].init("panc_cancer", "SUB", 33);
  conclusionList[34].init("cancer", "PANCREATIC NEUROENDOCRINE TUMOR", 34);
  conclusionList[35].init("panc_exo_tumor", "SUB", 35);
  conclusionList[36].init("cancer", "DUCTAL ADENOCARCINOMA", 36);
  conclusionList[37].init("cancer", "ACINAR ADENOCARCINOMA", 37);

  // populating the variable list:
  variableList[1].init("symptoms", "any symptoms");
  variableList[2].init("fat_weLo", "fatigue or weight loss");
  variableList[3].init("neLu_difBre_swNeGl", "neck lump, difficulty breathing, or swollen neck glands");
  variableList[4].init("high_calc", "high calcitonin levels");
  variableList[5].init("age", "AGE");
  variableList[6].init("loss_app", "loss of appetite");
  variableList[7].init("fr_di_paUr", "frequent, difficult, or painful urinating");
  variableList[8].init("hiBlIn_LoTeCaUs", "history of bladder infection or long term cetheter use");
  variableList[9].init("pers_fever", "persistent fever");
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
  
  // populate the clause variable list:
  // rule 1:
  clauseVariableList[1] = "symptoms";
  // rule 2:
  clauseVariableList[7] = "symptoms";
<<<<<<< HEAD

  clauseVariableList[13] = "pos_cancer";
  clauseVariableList[14] = "fat_weLo";

  clauseVariableList[19] = "pos_thy_cancer";
=======
  // rule 3:
  clauseVariableList[13] = "pos_canc";
  clauseVariableList[14] = "fat_wl";
  // rule 4:
  clauseVariableList[19] = "pos_thy_canc";
>>>>>>> 8c88986553a582235450a261f946b19b3fb64961
  clauseVariableList[20] = "neLu_difBre_swNeGl";
  // rule 5:
  clauseVariableList[25] = "neLu_difBre_swNeGl";
<<<<<<< HEAD
  clauseVariableList[26] = "pos_thy_cancer";

  clauseVariableList[31] = "thy_cancer";
  clauseVariableList[32] = "high_calc";
  
  clauseVariableList[37] = "thy_cancer";
  clauseVariableList[38] = "age";
  clauseVariableList[39] = "high_calc";
  
  clauseVariableList[43] = "thy_cancer";
  clauseVariableList[44] = "age";
  clauseVariableList[45] = "high_calc";
  
  clauseVariableList[49] = "thy_cancer";
=======
  clauseVariableList[26] = "pos_thy_canc";
  // rule 6:
  clauseVariableList[31] = "thy_cancer";
  clauseVariableList[32] = "high_calc";
  // rule 7:
  clauseVariableList[37] = "thy_canc";
  clauseVariableList[38] = "age";
  clauseVariableList[39] = "high_calc";
  // rule 8:
  clauseVariableList[43] = "thy_canc";
  clauseVariableList[44] = "age";
  clauseVariableList[45] = "high_calc";
  // rule 9:
  clauseVariableList[49] = "thy_canc";
>>>>>>> 8c88986553a582235450a261f946b19b3fb64961
  clauseVariableList[50] = "age";
  clauseVariableList[51] = "high_calc";
  // rule 10:
  clauseVariableList[55] = "pos_cancer";
  clauseVariableList[56] = "fat_weLo";
  clauseVariableList[57] = "loss_app";
  // rule 11:
  clauseVariableList[61] = "pos_bla_cancer";
  clauseVariableList[62] = "fr_di_paUr";
  // rule 12:
  clauseVariableList[67] = "fr_di_paUr";
  clauseVariableList[68] = "pos_bla_cancer";
  // rule 13:
  clauseVariableList[73] = "bla_cancer";
  clauseVariableList[74] = "hiBlIn_LoTeCaUs";
  // rule 14:
  clauseVariableList[79] = "bla_cancer";
  clauseVariableList[80] = "hiBlIn_LoTeCaUs";
  // rule 15:
  clauseVariableList[85] = "pos_cancer";
  clauseVariableList[86] = "fat_weLo";
  clauseVariableList[87] = "loss_app";
  clauseVariableList[88] = "pers_fever";
  // rule 16:
  clauseVariableList[91] = "pos_lung_cancer";
  clauseVariableList[92] = "shBr_chPa_coBl";
  // rule 17:
  clauseVariableList[97] = "shBr_chPa_coBl";
  clauseVariableList[98] = "pos_lung_cancer";
  // rule 18:
  clauseVariableList[103] = "lung_cancer";
  clauseVariableList[104] = "hiSm_seHaSmEx";
  // rule 19:
  clauseVariableList[109]	= "lung_cancer";
  clauseVariableList[110]	= "hiSm_seHaSmEx";
  clauseVariableList[111]	= "ra_as_urEx";
  // rule 20:
  clauseVariableList[115]	= "lung_cancer";
  clauseVariableList[116]	= "hiSm_seHaSmEx";
  clauseVariableList[117]	= "ra_as_urEx";
  // rule 21:
  clauseVariableList[121]	= "pos_cancer";
  clauseVariableList[122]	= "fat_weLo";
  clauseVariableList[123]	= "loss_app";
  clauseVariableList[124]	= "pers_fever";
  clauseVariableList[125]	= "ja_na_ab_shPa";
  // rule 22:
  clauseVariableList[127]	= "pos_kid_cancer";
  clauseVariableList[128]	= "CVA_an";
  // rule 23:
  clauseVariableList[133]	= "CVA_an";
  clauseVariableList[134]	= "pos_kid_cancer";
  // rule 24:
  clauseVariableList[139]	= "kid_cancer";
  clauseVariableList[140]	= "tubules";
  // rule 25:
  clauseVariableList[145]	= "kid_cancer";
  clauseVariableList[146]	= "tubules";
  clauseVariableList[147]	= "renal_pelvis";
  // rule 26:
  clauseVariableList[151]	= "kid_cancer";
  clauseVariableList[152]	= "tubules";
  clauseVariableList[153]	= "renal_pelvis";
  // rule 27:
  clauseVariableList[157]	= "pos_cancer";
  clauseVariableList[158]	= "fat_weLo";
  clauseVariableList[159]	= "loss_app";
  clauseVariableList[160]	= "pers_fever";
  clauseVariableList[161]	= "ja_na_ab_shPa";
  clauseVariableList[162]	= "sw_ch_buSt_bl";
  // rule 28:
  clauseVariableList[163]	= "pos_liver_cancer";
  clauseVariableList[164]	= "enLi_sp_it_feFuEa";
  // rule 29:
  clauseVariableList[169]	= "pos_liver_cancer";
  clauseVariableList[170]	= "enLi_sp_it_feFuEa";
  // rule 30:
  clauseVariableList[175]	= "liver_cancer";
  clauseVariableList[176]	= "grInLi";
  // rule 31:
  clauseVariableList[181]	= "liver_cancer";
  clauseVariableList[182]	= "grInLi";
  // rule 32:
  clauseVariableList[187]	= "liver_cancer";
  clauseVariableList[188]	= "grInLi";
  clauseVariableList[189]	= "bile_duct";
  // rule 33:
  clauseVariableList[193]	= "pos_cancer";
  clauseVariableList[194]	= "fat_weLo";
  clauseVariableList[195]	= "loss_app";
  clauseVariableList[196]	= "pers_fever";
  clauseVariableList[197]	= "ja_na_ab_shPa";
  clauseVariableList[198]	= "sw_ch_buSt_bl";
  // rule 34:
  clauseVariableList[199]	= "panc_cancer";
  clauseVariableList[200]	= "exocrine_component";
  // rule 35:
  clauseVariableList[205]	= "panc_cancer";
  clauseVariableList[206]	= "exocrine_component";
  // rule 36:
  clauseVariableList[211]	= "panc_exo_tumor";
  clauseVariableList[212]	= "ducts";
  // rule 37:
  clauseVariableList[217]	= "panc_exo_tumor";
  clauseVariableList[218]	= "ducts";

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
 /*
 cout << "1. Identify the conclusion. " << endl // DONE
       << "2. Search the conclusion list for the first instance of the conclusion's name. If found, place the rule on the conclusion stack using the rule number and a (1) to represent the clause number. If not found, notify the user that an answer cannot be found." << endl
       << "3. Instantiate the IF clause (i.e., each condition variable) of the statement." << endl
       << "4. If one of the IF clause variables is not instantiated, as indicated by the variable list, and is not a conclusion variable, that is, not on the conclusion list, ask the user to enter a value." << endl
       << "5. If one of the clauses is a conclusion variable, place the conclusion variable's rule number on the top of the stack and go back to step 3." << endl
       << "6. If the statement on top of the stack cannot be instantiated using the present IF-THEN statement, remove the unit from the top of the stack and search the conclusion list for another instance of that conclusion variable's name." << endl
       << "7. If such a statement is found, go back to step 3." << endl
       << "8. If there are no more conclusions left on the conclusion stack with that name, the rule for the previous conclusion is false. If there is no previous conclusion, then notify the user that an answer cannot be found. If there is a previous conclusion, go back to step 6." << endl
       << "9. If the rule on top of the stack can be instantiated, remove it from the stack. If another conclusion variable is underneath, increment the clause number, and for the remaining clauses go back to step 3. If no other conclusion variable is underneath, we have answered our question. The user can come to a conclusion." << endl;
  */
  for(int i = 1; i <= CONCLUSION_LIST_SIZE && terminateFunction == false; i++){

    //cout << "hit top of for loop" << endl;
    count = 0;

    // Search for the Conclusion
    
    index = searchConclusionList(conclusion, conclusion_Counter);
    conclusion_Counter = index + 1;
    //cout << "Conclusion List Index: " << index << endl;
    //cout << "Conclusion Counter: " << conclusion_Counter << endl;
    
    if(index != 0){   // We found the item in the conclusionList
      conclusionStack.push(conclusionList[index]);    // Step 2 Done?
      cout << "The conclusion '" << conclusion << "' was found in element " << index << " of the conclusion list." << endl;
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
          int varIndex = searchVariableList(clauseVariableList[i + count]);    // Index now holds the location of the corresponding symptom in variableList
          if (varIndex != 0)   // Found the item in varaible list
          {
            if(variableList[varIndex].instantiated == false)
            {
              instantiate(variableList[varIndex].name);    // Step 3 and 4 Done?
            }
          }
          else    // The Item was not on the varaiable list. So it must be a conclusion variable. Handle it!
          {
              int clauseIndex = searchConclusionList(clauseVariableList[i + count], 1);   // Send 1 to start at the beginning of the list. Index will hold the location of the conclusion in conclusion list.
              if(clauseIndex != 0){   // We found the item in the conclusionList. So now we need to push it to the stack.
                conclusionStack.push(conclusionList[clauseIndex]);    
              }
              else{
                continue; // We did not find the conclusion in the conclusion list.
              }
          }
        }
        count++;
    }while(clauseVariableList[i] != "" && count < 6);
    //cout << "HIT 2!" << endl;
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
  // cout << "Conc: " << conc << endl;
  int index = 0;
  for(int i = conclusion_Counter; i <= CONCLUSION_LIST_SIZE; i++)
  {
    // cout << "Searching conclusion list index: " << i << endl;
    if(conc == conclusionList[i].name) 
    {
      index = i;
      return index;
    }
    else{
      cout << "The conclusion '" << conc << "' was not found in this element." << endl << endl;
    };
    index++;
  }
  return index;
}

int searchVariableList(string clauseVariable)
{
  cout << "Variable: " << clauseVariable << endl;
  int index = 0;
  for(int i = 1; i <= VARIABLE_LIST_SIZE; i++)
  {
    if(clauseVariable == variableList[i].name)    
    {
      index = i;
      return index;
    }
    else{
      cout << "The variable '" << clauseVariable << "' was not found in element " << i << "." << endl;
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
      if (answer == "yes" || answer == "YES" || answer == "Yes")
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
  cout << endl;
  cout << "--- Clause Variable List ---" << endl;
  for(int i = 1; i < 9; i++){    // Replace 9 with CONCLUSION_LIST_SIZE when done with small testing
    cout << "Variable at location " << i << ": " << clauseVariableList[i] << endl;
  }

  cout << endl << endl;
  
}

bool useKnowledgeBase(int ruleNumber){
  bool terminateDiagnosisAlgorithm = false;
  
  cout << "Accessing Knowledge Base...." << endl << endl;

  // Create a switch statement and all of the if then statements with the cases. Reference example.

  switch (ruleNumber)
  {
  case 1:
    if(variableList[1].experiencing == false)
    {
      cout << "Case 1 Value (False = 0/True = 1): " << variableList[1].experiencing << endl;
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

  if(terminateDiagnosisAlgorithm == false){
    cout << "Continuing with the diagnosis, hopping out of the knowledge base..." << endl << endl;
  }
  
  return terminateDiagnosisAlgorithm;
}