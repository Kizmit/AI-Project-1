/*
    Artifical Intelligence Project 1:
    Jeff Wilson
    Joe McAdams
    Brandon Burtchell

    Spring 2021
*/

#include "Project1.h"

using namespace std;

// diagnosis data structures:
Conclusion diagConcList[DIAG_CONC_LIST_SIZE];
Clause diagVarList[DIAG_VAR_LIST_SIZE];
string diagClauseVarList[DIAG_CLAUSE_VAR_LIST_SIZE];
stack<Conclusion> diagConcStack;
stack<Clause> diagClauseStack;
stack<string> diagTBIVarStack; // to-be-instantiated variable stack

ofstream logFile;

// function declaration:
void printWelcomeMessage();
Conclusion diagnosis();
int searchConclusionList(string, int);
int searchVariableList(string);
void instantiate(string);
void testPrintLists();
bool useDiagnosisKnowledgeBase(int, Conclusion&);

string treatment(string, string*, int);
string useTreatmentKnowledgeBase(int, string, Clause*);

int main()
{
  // Gather the Patient ID and set up the logging information
  string patientID;
  cout << "Enter in the ID# for the patient: ";
  cin >> patientID;

  printWelcomeMessage();

  // Create Log File
  string logName = "Project1_LOG_ID#" + patientID + ".txt";
  logFile.open(logName);
  logFile << "Patient #: " << patientID << endl << endl << endl;

  // populating the diagnosis conclusion list:
  diagConcList[1].init("cancer", "NONE", 1);
  diagConcList[2].init("pos_cancer", "SUB", 2);
  diagConcList[3].init("pos_thy_cancer", "SUB", 3);
  diagConcList[4].init("cancer", "CAN'T DIAGNOSE", 4);
  diagConcList[5].init("thy_cancer", "SUB", 5);
  diagConcList[6].init("cancer", "MEDULLARY THYROID CANCER", 6);
  diagConcList[7].init("cancer", "PAPILLARY THYROID CANCER", 7);
  diagConcList[8].init("cancer", "FOLLICULAR THYROID CANCER", 8);
  diagConcList[9].init("cancer", "ANAPLASTIC THYROID CANCER", 9);
  diagConcList[10].init("pos_bla_cancer", "SUB", 10);
  diagConcList[11].init("cancer", "CAN'T DIAGNOSE", 11);
  diagConcList[12].init("bla_cancer", "SUB", 12);
  diagConcList[13].init("cancer", "SQUAMOUS CELL CARCINOMA", 13);
  diagConcList[14].init("cancer", "UROTHELIAL CARCINOMA", 14);
  diagConcList[15].init("pos_lung_cancer", "SUB", 15);
  diagConcList[16].init("cancer", "CAN'T DIAGNOSE", 16);
  diagConcList[17].init("lung_cancer", "SUB", 17);
  diagConcList[18].init("cancer", "NON-SMALL CELL LUNG CANCER", 18);
  diagConcList[19].init("cancer", "NON-SMALL CELL LUNG CANCER", 19);
  diagConcList[20].init("cancer", "SMALL CELL LUNG CANCER", 20);
  diagConcList[21].init("pos_kid_cancer", "SUB", 21);
  diagConcList[22].init("cancer", "CAN'T DIAGNOSE", 22);
  diagConcList[23].init("kid_cancer", "SUB", 23);
  diagConcList[24].init("cancer", "RENAL CELL CARCINOMA", 24);
  diagConcList[25].init("cancer", "UROTHELIAL CARCINOMA", 25);
  diagConcList[26].init("cancer", "SARCOMA OF THE KIDNEY", 26);
  diagConcList[27].init("pos_liver_cancer", "SUB", 27);
  diagConcList[28].init("cancer", "CAN'T DIAGNOSE", 28);
  diagConcList[29].init("liver_cancer", "LIVER CANCER", 29); // FIXME: does this need to be changed to SUB?
  diagConcList[30].init("cancer", "HEPATOCELLULAR CARCINOMA", 30);
  diagConcList[31].init("cancer", "ANGIOSARCOMA", 31);
  diagConcList[32].init("cancer", "CHOLANGIOCARCINOMA", 32);
  diagConcList[33].init("panc_cancer", "SUB", 33);
  diagConcList[34].init("cancer", "PANCREATIC NEUROENDOCRINE TUMOR", 34);
  diagConcList[35].init("panc_exo_tumor", "SUB", 35);
  diagConcList[36].init("cancer", "DUCTAL ADENOCARCINOMA", 36);
  diagConcList[37].init("cancer", "ACINAR ADENOCARCINOMA", 37);

  // populating the diagnosis variable list:
  diagVarList[1].init("symptoms", "any symptoms");
  diagVarList[2].init("fat_weLo", "fatigue or weight loss");
  diagVarList[3].init("neLu_difBre_swNeGl", "a neck lump, difficulty breathing, or swollen neck glands");
  diagVarList[4].init("high_calc", "high calcitonin levels");
  diagVarList[5].init("age", "AGE"); // Different use case for instantiation(). .> See Function Below. (Taking integer input, not setting boolean.   diagVarList[5].age = userInput. )
  diagVarList[6].init("loss_app", "loss of appetite");
  diagVarList[7].init("fr_di_paUr", "frequent, difficult, or painful urination");
  diagVarList[8].init("hiBlIn_LoTeCaUs", "a history of bladder infection or long term catheter use");
  diagVarList[9].init("pers_fever", "persistent fever");
  diagVarList[10].init("shBr_chPa_coBl", "shortness of breath, chest pain, or coughing up blood");
  diagVarList[11].init("hiSm_seHaSmEx", "a history of smoking or second-hand smoking exposure");
  diagVarList[12].init("ra_as_urEx", "a history of exposure to radon, asbestos, or uranium");
  diagVarList[13].init("ja_na_ab_shPa", "jaundice, nausea, abdominal pain or shoulder pain");
  diagVarList[14].init("CVA_an", "a CVA mass or anemia");
  diagVarList[15].init("tubules", "cancer cells that originated in the tubules of the kidney");
  diagVarList[16].init("renal_pelvis", "cancer cells that originated in the renal pelvis");
  diagVarList[17].init("sw_ch_buSt_bl", "sweats, chills, burning stomach, or bloating");
  diagVarList[18].init("enLi_sp_it_feFuEa", "an enlarged liver or spleen, itching, or feeling full easily");
  diagVarList[19].init("grInLi", "tentacle-like growths or nodules throughout the liver");
  diagVarList[20].init("bile_duct", "cancer cells that originated in the bile duct of the liver");
  diagVarList[21].init("exocrine_component", "cancer cells that originated in the exocrine component of the pancreas");
  diagVarList[22].init("ducts", "cancer cells that originated in the ducts of the pancreas");

  // populate the diagnosis clause variable list:
  // rule 1:
  diagClauseVarList[1] = "symptoms";
  // rule 2:
  diagClauseVarList[7] = "symptoms";
  // rule 3:
  diagClauseVarList[13] = "pos_cancer";
  diagClauseVarList[14] = "fat_weLo";
  // rule 4:
  diagClauseVarList[19] = "pos_thy_cancer";
  diagClauseVarList[20] = "neLu_difBre_swNeGl";
  // rule 5:
  diagClauseVarList[25] = "neLu_difBre_swNeGl";
  diagClauseVarList[26] = "pos_thy_cancer";
  // rule 6:
  diagClauseVarList[31] = "thy_cancer";
  diagClauseVarList[32] = "high_calc";
  // rule 7:
  diagClauseVarList[37] = "thy_cancer";
  diagClauseVarList[38] = "age";
  diagClauseVarList[39] = "high_calc";
  // rule 8:
  diagClauseVarList[43] = "thy_cancer";
  diagClauseVarList[44] = "age";
  diagClauseVarList[45] = "high_calc";
  // rule 9:
  diagClauseVarList[49] = "thy_cancer";
  diagClauseVarList[50] = "age";
  diagClauseVarList[51] = "high_calc";
  // rule 10:
  diagClauseVarList[55] = "pos_cancer";
  diagClauseVarList[56] = "fat_weLo";
  diagClauseVarList[57] = "loss_app";
  // rule 11:
  diagClauseVarList[61] = "pos_bla_cancer";
  diagClauseVarList[62] = "fr_di_paUr";
  // rule 12:
  diagClauseVarList[67] = "fr_di_paUr";
  diagClauseVarList[68] = "pos_bla_cancer";
  // rule 13:
  diagClauseVarList[73] = "bla_cancer";
  diagClauseVarList[74] = "hiBlIn_LoTeCaUs";
  // rule 14:
  diagClauseVarList[79] = "bla_cancer";
  diagClauseVarList[80] = "hiBlIn_LoTeCaUs";
  // rule 15:
  diagClauseVarList[85] = "pos_cancer";
  diagClauseVarList[86] = "fat_weLo";
  diagClauseVarList[87] = "loss_app";
  diagClauseVarList[88] = "pers_fever";
  // rule 16:
  diagClauseVarList[91] = "pos_lung_cancer";
  diagClauseVarList[92] = "shBr_chPa_coBl";
  // rule 17:
  diagClauseVarList[97] = "shBr_chPa_coBl";
  diagClauseVarList[98] = "pos_lung_cancer";
  // rule 18:
  diagClauseVarList[103] = "lung_cancer";
  diagClauseVarList[104] = "hiSm_seHaSmEx";
  // rule 19:
  diagClauseVarList[109] = "lung_cancer";
  diagClauseVarList[110] = "hiSm_seHaSmEx";
  diagClauseVarList[111] = "ra_as_urEx";
  // rule 20:
  diagClauseVarList[115] = "lung_cancer";
  diagClauseVarList[116] = "hiSm_seHaSmEx";
  diagClauseVarList[117] = "ra_as_urEx";
  // rule 21:
  diagClauseVarList[121] = "pos_cancer";
  diagClauseVarList[122] = "fat_weLo";
  diagClauseVarList[123] = "loss_app";
  diagClauseVarList[124] = "pers_fever";
  diagClauseVarList[125] = "ja_na_ab_shPa";
  // rule 22:
  diagClauseVarList[127] = "pos_kid_cancer";
  diagClauseVarList[128] = "CVA_an";
  // rule 23:
  diagClauseVarList[133] = "CVA_an";
  diagClauseVarList[134] = "pos_kid_cancer";
  // rule 24:
  diagClauseVarList[139] = "kid_cancer";
  diagClauseVarList[140] = "tubules";
  // rule 25:
  diagClauseVarList[145] = "kid_cancer";
  diagClauseVarList[146] = "tubules";
  diagClauseVarList[147] = "renal_pelvis";
  // rule 26:
  diagClauseVarList[151] = "kid_cancer";
  diagClauseVarList[152] = "tubules";
  diagClauseVarList[153] = "renal_pelvis";
  // rule 27:
  diagClauseVarList[157] = "pos_cancer";
  diagClauseVarList[158] = "fat_weLo";
  diagClauseVarList[159] = "loss_app";
  diagClauseVarList[160] = "pers_fever";
  diagClauseVarList[161] = "ja_na_ab_shPa";
  diagClauseVarList[162] = "sw_ch_buSt_bl";
  // rule 28:
  diagClauseVarList[163] = "pos_liver_cancer";
  diagClauseVarList[164] = "enLi_sp_it_feFuEa";
  // rule 29:
  diagClauseVarList[169] = "pos_liver_cancer";
  diagClauseVarList[170] = "enLi_sp_it_feFuEa";
  // rule 30:
  diagClauseVarList[175] = "liver_cancer";
  diagClauseVarList[176] = "grInLi";
  // rule 31:
  diagClauseVarList[181] = "liver_cancer";
  diagClauseVarList[182] = "grInLi";
  diagClauseVarList[183] = "bile_duct";
  // rule 32:
  diagClauseVarList[187] = "liver_cancer";
  diagClauseVarList[188] = "grInLi";
  diagClauseVarList[189] = "bile_duct";
  // rule 33:
  diagClauseVarList[193] = "pos_cancer";
  diagClauseVarList[194] = "fat_weLo";
  diagClauseVarList[195] = "loss_app";
  diagClauseVarList[196] = "pers_fever";
  diagClauseVarList[197] = "ja_na_ab_shPa";
  diagClauseVarList[198] = "sw_ch_buSt_bl";
  // rule 34:
  diagClauseVarList[199] = "panc_cancer";
  diagClauseVarList[200] = "exocrine_component";
  // rule 35:
  diagClauseVarList[205] = "panc_cancer";
  diagClauseVarList[206] = "exocrine_component";
  // rule 36:
  diagClauseVarList[211] = "panc_exo_tumor";
  diagClauseVarList[212] = "ducts";
  // rule 37:
  diagClauseVarList[217] = "panc_exo_tumor";
  diagClauseVarList[218] = "ducts";

  // testPrintLists();

  cout << "--- Starting Diagnosis Process For Patient #" << patientID << " ---" << endl << endl;
  logFile << "--- Starting Diagnosis Process For Patient #" << patientID << " ---" << endl << endl;
  Conclusion finalDiagnosis = diagnosis();

  cout << "\n*** Final Diagnosis: " << finalDiagnosis.name << " = " << finalDiagnosis.finalConclusion << endl << endl << endl;
  logFile << "\n*** Final Diagnosis: " << finalDiagnosis.name << " = " << finalDiagnosis.finalConclusion << endl << endl << endl;

  // treatment data initialization:
  const int TREAT_CLAUSE_VAR_LIST_SIZE = 19; // 18 rules + 1
  string treatClauseVarList[TREAT_CLAUSE_VAR_LIST_SIZE] = {"", "NONE", "ANAPLASTIC THYROID CANCER",
    "PAPILLARY THYROID CANCER", "MEDULLARY THYROID CANCER", "FOLLICULAR THYROID CANCER", 
    "UROTHELIAL CARCINOMA", "SQUAMOUS CELL CARCINOMA", "SMALL CELL LUNG CANCER",
    "NON-SMALL CELL LUNG CANCER", "RENAL CELL CARCINOMA", "SARCOMA OF THE KIDNEY",
    "DUCTAL ADENOCARCINOMA", "ACINAR ADENOCARCINOMA", "PANCREATIC NEUROENDOCRINE TUMOR",
    "HEPATOCELLULAR CARCINOMA", "CHOLANGIOCARCINOMA", "ANGIOSARCOMA", "CAN'T DIAGNOSE"};

  cout << "--- Starting Treatment Recommendation Process For Patient #" << patientID << " to recommend a treatment for " << finalDiagnosis.finalConclusion << " ---" << endl << endl;
  logFile << "--- Starting Treatment Recommendation Process For Patient #" << patientID << " ---" << endl << endl;
  string finalTreatment = treatment(finalDiagnosis.finalConclusion, treatClauseVarList, TREAT_CLAUSE_VAR_LIST_SIZE);

  cout << "The recommended treatment for " << finalDiagnosis.finalConclusion << " is " << finalTreatment << endl << endl;

  // Close the log stream
  logFile.close();

  return 0;
}

void printWelcomeMessage()
{
  cout << "\n----------------------------------------------------------------------------------------------------" << endl;
  cout << "--- Cancer Diagnosis and Treatment Recommendation ---" << endl << endl;
  cout << "You will be prompted to enter information regarding the patient, answer to the best of your ability." << endl << endl;
  cout << "Answer Symptom Related Questions with either 'YES' or 'NO'" << endl;
  cout << "----------------------------------------------------------------------------------------------------" << endl << endl;
}

Conclusion diagnosis()
{
  int conclusionCounter = 1;   // Keep track of how far the diagConcList has been traversed. We need to advance in our search.
  string conclusion = "cancer"; // Identify the conclusion
  int index, count, i;
  bool terminateFunction = false; // Will be set to true by knowledge base if we hit a terminating conclusion.
  Conclusion finalDiagnosis; // holds the to-be-returned Conclusion of the function

  i = 1;
  do
  {
    count = 0;

    // Search for the Conclusion
    logFile << "The Conclusion has not been solved yet, searching for an instance now..." << endl;
    index = searchConclusionList(conclusion, conclusionCounter);
    conclusionCounter = index + 1;

    if (index != 0)
    { // We found the item in the diagConcList
      diagConcStack.push(diagConcList[index]); // Step 2 Done
      logFile << "The conclusion '" << conclusion << "' was found in element " << index << " of the conclusion list." << endl;
    }
    else
    {
      cout << "No instances of the conclusion were found in the list. Assuming a non-diagnosis status." << endl;
      logFile << endl << diagConcList[4].name << " set to TRUE!" << endl;
      terminateFunction = true;
      finalDiagnosis = diagConcList[4]; // Can't Diagnose Conclusion
    }

    bool entered = false;
    do
    {
      entered = false;
      count = 0;

      if (diagConcStack.empty() == false)
      {
        i = diagConcStack.top().clauseNumber; // Go to top of the stack
      }

      // Step 3
      do
      {
        if (diagClauseVarList[i + count] != "")
        {

          int varIndex = searchVariableList(diagClauseVarList[i + count]); // Index now holds the location of the corresponding symptom in diagVarList
          if (varIndex != 0)                                                // Found the item in varaible list
          {
            logFile << "The variable '" << diagVarList[varIndex].name << "' was found in element " << index << " of the variable list." << endl;
            if (diagVarList[varIndex].markedForInstantiation == true)
            {
              logFile << "The Variable has not been assigned a value yet. Adding to TBIVarStack: " << diagVarList[varIndex].name << endl;
              diagTBIVarStack.push(diagVarList[varIndex].name);
              diagVarList[varIndex].markedForInstantiation = false;
              entered = true;
              /*logFile << "The Variable has not been assigned a value yet. Now instantiating the variable: " << diagVarList[varIndex].name << endl;
              instantiate(diagVarList[varIndex].name);    // Step 3 and 4 Done?
              entered = true;*/
            }
          }
          else // The Item was not on the varaiable list. So it must be a conclusion variable. Handle it!
          {
            int clauseIndex = searchConclusionList(diagClauseVarList[i + count], 1); // Send 1 to start at the beginning of the list. Index will hold the location of the conclusion in conclusion list.
            if (clauseIndex != 0)
            { // We found the item in the diagConcList. So now we need to push it to the stack.
              diagConcStack.push(diagConcList[clauseIndex]);
              logFile << "Pushing " << diagConcList[clauseIndex].name << " on to the stack!" << endl;
              entered = true;
            }
            else
            {
              continue; // We did not find the conclusion in the conclusion list.
            }
          }
        }
        count++;
      } while (diagClauseVarList[i + count] != "" && count < 6);

    } while (!diagConcStack.empty() && entered == true);

    while (!diagTBIVarStack.empty())
    { //Instantiate the necessary variables to come to a conclusion
      instantiate(diagTBIVarStack.top());
      diagTBIVarStack.pop();
    }

    while (!diagConcStack.empty() && !terminateFunction)
    {
      terminateFunction = useDiagnosisKnowledgeBase(diagConcStack.top().ruleNumber, finalDiagnosis);
    }

  } while (!terminateFunction);

  return finalDiagnosis;
}

int searchConclusionList(string conc, int conclusionCounter)
{
  int index = 0;
  for (int i = conclusionCounter; i <= DIAG_CONC_LIST_SIZE - 1; i++)
  {
    // logFile << "Searching conclusion list index " << i << " for '" << conc << "' " << endl;
    if (conc == diagConcList[i].name)
    {
      index = i;
      logFile << "***\nConclusion Found!" << endl;
      return index;
    }
    else
    {
      // cout << "The conclusion '" << conc << "' was not found in this element." << endl << endl;
    };
    index++;
  }
  return index;
}

int searchVariableList(string clauseVariable)
{
  int index = 0;
  for (int i = 1; i <= DIAG_VAR_LIST_SIZE - 1; i++)
  {
    // logFile << "Searching variable list index " << i << " for '" << clauseVariable << "' " << endl;
    if (clauseVariable == diagVarList[i].name)
    {
      logFile << "***\nVariable Found!" << endl;
      index = i;
      return index;
    }
    else
    {
      // logFile << "ERROR! The variable '" << clauseVariable << "' was not found in element " << i << "." << endl;
      continue;
    };
  }
  return index;
}

void instantiate(string str)
{
  string answer;
  int ageInput;
  for (int i = 1; i <= DIAG_VAR_LIST_SIZE - 1; i++)
  {
    if (diagVarList[i].name == str && !diagVarList[i].instantiated)
    {
      if (diagVarList[i].name != "age")
      { // Everything but age, meaning we are setting a boolean.
        diagVarList[i].instantiated = true;
        cout << "Does the patient have " << diagVarList[i].print << ": ";
        cin >> (answer);
        if (answer == "yes" || answer == "YES" || answer == "Yes")
        {
          diagVarList[i].experiencing = true;
          logFile << diagVarList[i].print << " set to TRUE" << endl;
        }
        break;
      }
      else
      { // The Variable we are trying to instantiate is for the age. So...we need to handle it as an integer.
        diagVarList[i].instantiated = true;
        cout << "Enter the patient's age: ";
        cin >> ageInput;
        diagVarList[i].age = ageInput;
        logFile << "Patient age was set to " << diagVarList[i].age << endl;
        break;
      }
    }
  }
}

void testPrintLists()
{
  cout << "--- Variable List --- " << endl;
  for (int i = 1; i < DIAG_VAR_LIST_SIZE; i++)
  {
    cout << i << " Name: " << diagVarList[i].name << endl;
    cout << i << " Print Name: " << diagVarList[i].print << endl;
    cout << i << " Instantiated: (0 = False, 1 = True) " << diagVarList[i].instantiated << endl;
    cout << i << " Experiencing: (0 = False, 1 = True) " << diagVarList[i].experiencing << endl;
  }
  cout << endl;
  cout << "--- Conclusion List ---" << endl;
  for (int i = 1; i < DIAG_CONC_LIST_SIZE; i++)
  {
    cout << i << " Name: " << diagConcList[i].name << endl;
    cout << i << " Final Conclusion: " << diagConcList[i].finalConclusion << endl;
    cout << i << " Rule Number: " << diagConcList[i].ruleNumber << endl;
  }
  cout << endl;
  cout << "--- Clause Variable List ---" << endl;
  for (int i = 1; i < DIAG_CLAUSE_VAR_LIST_SIZE; i++)
  {
    cout << "Variable at location " << i << ": " << diagClauseVarList[i] << endl;
  }

  cout << endl << endl;
}

bool useDiagnosisKnowledgeBase(int ruleNumber, Conclusion& finalDiagnosis)
{
  bool terminateDiagnosisAlgorithm = false;

  logFile << "Accessing Knowledge Base with Rule Number: " << ruleNumber << endl;

  // Create a switch statement and all of the if then statements with the cases. Reference example.

  switch (ruleNumber)
  {
  case 1:
    if (diagVarList[1].experiencing == false)
    {
      //logFile << endl << diagConcList[1].name << " set to TRUE!" << endl;
      terminateDiagnosisAlgorithm = true;
      finalDiagnosis = diagConcList[1];
    }
    break;

  case 2:
    if (diagVarList[1].experiencing == true)
    {
      //logFile << endl << diagConcList[2].name << " set to TRUE!" << endl;
      diagConcList[2].value = true;
    }
    break;

  case 3:
    if (diagConcList[2].value == true && diagVarList[2].experiencing == false)
    {
      //logFile << endl << diagConcList[3].name << " set to TRUE!" << endl;
      diagConcList[3].value = true;
    }
    break;

  case 4:
    if (diagConcList[3].value == true && diagVarList[3].experiencing == false)
    {
      //logFile << endl << diagConcList[4].name << " set to TRUE!" << endl;
      terminateDiagnosisAlgorithm = true;
      finalDiagnosis = diagConcList[4];
    }
    break;

  case 5:
    if (diagVarList[3].experiencing == true && diagConcList[3].value == true)
    {
      //logFile << endl << diagConcList[5].name << " set to TRUE!" << endl;
      diagConcList[5].value = true;
    }
    break;

  case 6:
    if (diagConcList[5].value == true && diagVarList[4].experiencing == true)
    {
      //logFile << endl << diagConcList[6].name << " set to TRUE!" << endl;
      terminateDiagnosisAlgorithm = true;
      diagConcList[6].value = true;
      finalDiagnosis = diagConcList[6];
    }
    break;

  case 7:
    if (diagConcList[3].value == true && diagVarList[5].age < 51 && diagVarList[4].experiencing == false)
    {
      //logFile << endl << diagConcList[7].name << " set to TRUE!" << endl;
      terminateDiagnosisAlgorithm = true;
      diagConcList[7].value = true;
      finalDiagnosis = diagConcList[7];
    }
    break;

  case 8:
    if (diagConcList[3].value == true && diagVarList[5].age >= 51 && diagVarList[5].age < 61 && diagVarList[4].experiencing == false)
    {
      //logFile << endl << diagConcList[8].name << " set to TRUE!" << endl;
      terminateDiagnosisAlgorithm = true;
      diagConcList[8].value = true;
      finalDiagnosis = diagConcList[8];
    }
    break;

  case 9:
    if (diagConcList[3].value == true && diagVarList[5].age > 61 && diagVarList[4].experiencing == false)
    {
      //logFile << endl << diagConcList[9].name << " set to TRUE!" << endl;
      terminateDiagnosisAlgorithm = true;
      diagConcList[9].value = true;
      finalDiagnosis = diagConcList[9];
    }
    break;

  case 10:
    if (diagConcList[2].value == true && diagVarList[2].experiencing == true && diagVarList[6].experiencing == false)
    {
      //logFile << endl << diagConcList[10].name << " set to TRUE!" << endl;
      diagConcList[10].value = true;
    }
    break;

  case 11:
    if (diagConcList[10].value == true && diagVarList[7].experiencing == false)
    {
      //logFile << endl << diagConcList[11].name << " set to TRUE!" << endl;
      terminateDiagnosisAlgorithm = true;
      diagConcList[11].value = true;
      finalDiagnosis = diagConcList[11];
    }
    break;

  case 12:
    if (diagConcList[10].value == true && diagVarList[7].experiencing == true)
    {
      //logFile << endl << diagConcList[12].name << " set to TRUE!" << endl;
      diagConcList[12].value = true;
    }
    break;

  case 13:
    if (diagConcList[12].value == true && diagVarList[8].experiencing == true)
    {
      //logFile << endl << diagConcList[13].name << " set to TRUE!" << endl;
      terminateDiagnosisAlgorithm = true;
      diagConcList[13].value = true;
      finalDiagnosis = diagConcList[13];
    }
    break;

  case 14:
    if (diagConcList[12].value == true && diagVarList[8].experiencing == false)
    {
      //logFile << endl << diagConcList[14].name << " set to TRUE!" << endl;
      terminateDiagnosisAlgorithm = true;
      diagConcList[14].value = true;
      finalDiagnosis = diagConcList[14];
    }
    break;

  case 15:
    if (diagConcList[2].value == true && diagVarList[2].experiencing == true && diagVarList[9].experiencing == false)
    {
      //logFile << endl << diagConcList[15].name << " set to TRUE!" << endl;
      diagConcList[15].value = true;
    }
    break;

  case 16:
    if (diagConcList[15].value == true && diagVarList[10].experiencing == false)
    {
      //logFile << endl << diagConcList[16].name << " set to TRUE!" << endl;
      terminateDiagnosisAlgorithm = true;
      finalDiagnosis = diagConcList[16];
    }
    break;

  case 17:
    if (diagConcList[15].value == true && diagVarList[10].experiencing == true)
    {
      //logFile << endl << diagConcList[17].name << " set to TRUE!" << endl;
      diagConcList[17].value = true;
    }
    break;

  case 18:
    if (diagConcList[17].value == true && diagVarList[11].experiencing == false)
    {
      //logFile << endl << diagConcList[18].name << " set to TRUE!" << endl;
      terminateDiagnosisAlgorithm = true;
      finalDiagnosis = diagConcList[18];
    }
    break;

  case 19:
    if (diagConcList[17].value == true && diagVarList[11].experiencing == true && diagVarList[12].experiencing == false)
    {
      //logFile << endl << diagConcList[19].name << " set to TRUE!" << endl;
      terminateDiagnosisAlgorithm = true;
      finalDiagnosis = diagConcList[19];
    }
    break;

  case 20:
    if (diagConcList[17].value == true && diagVarList[11].experiencing == true && diagVarList[12].experiencing == true)
    {
      //logFile << endl << diagConcList[20].name << " set to TRUE!" << endl;
      terminateDiagnosisAlgorithm = true;
      finalDiagnosis = diagConcList[20];
    }
    break;

  case 21:
    if (diagConcList[2].value == true && diagVarList[2].experiencing == true && diagVarList[6].experiencing == true && diagVarList[9].experiencing == true && diagVarList[13].experiencing == false)
    {
      //logFile << endl << diagConcList[21].name << " set to TRUE!" << endl;
      diagConcList[21].value = true;
    }
    break;

  case 22:
    if (diagConcList[21].value == true && diagVarList[14].experiencing == false)
    {
      //logFile << endl << diagConcList[22].name << " set to TRUE!" << endl;
      terminateDiagnosisAlgorithm = true;
      finalDiagnosis = diagConcList[22];
    }
    break;

  case 23:
    if (diagConcList[21].value == true && diagVarList[14].experiencing == true)
    {
      //logFile << endl << diagConcList[23].name << " set to TRUE!" << endl;
      diagConcList[23].value = true;
    }
    break;

  case 24:
    if (diagConcList[23].value == true && diagVarList[15].experiencing == true)
    {
      //logFile << endl << diagConcList[24].name << " set to TRUE!" << endl;
      terminateDiagnosisAlgorithm = true;
      finalDiagnosis = diagConcList[24];
    }
    break;

  case 25:
    if (diagConcList[23].value == true && diagVarList[15].experiencing == false && diagVarList[16].experiencing == true)
    {
      //logFile << endl << diagConcList[25].name << " set to TRUE!" << endl;
      terminateDiagnosisAlgorithm = true;
      finalDiagnosis = diagConcList[25];
    }
    break;

  case 26:
    if (diagConcList[23].value == true && diagVarList[15].experiencing == false && diagVarList[16].experiencing == false)
    {
      //logFile << endl << diagConcList[26].name << " set to TRUE!" << endl;
      terminateDiagnosisAlgorithm = true;
      finalDiagnosis = diagConcList[26];
    }
    break;

  case 27:
    if (diagConcList[2].value == true && diagVarList[2].experiencing == true && diagVarList[6].experiencing == true && diagVarList[9].experiencing == true && diagVarList[13].experiencing == true && diagVarList[17].experiencing == false)
    {
      //logFile << endl << diagConcList[27].name << " set to TRUE!" << endl;
      diagConcList[27].value = true;
    }
    break;

  case 28:
    if (diagConcList[27].value == true && diagVarList[18].experiencing == false)
    {
      //logFile << endl << diagConcList[28].name << " set to TRUE!" << endl;
      terminateDiagnosisAlgorithm = true;
      finalDiagnosis = diagConcList[28];
    }
    break;

  case 29:
    if (diagConcList[27].value == true && diagVarList[18].experiencing == true)
    {
      //logFile << endl << diagConcList[29].name << " set to TRUE!" << endl;
      diagConcList[29].value = true;
    }
    break;

  case 30:
    if (diagConcList[29].value == true && diagVarList[19].experiencing == true)
    {
      //logFile << endl << diagConcList[30].name << " set to TRUE!" << endl;
      terminateDiagnosisAlgorithm = true;
      finalDiagnosis = diagConcList[30];
    }
    break;

  case 31:
    if (diagConcList[29].value == true && diagVarList[19].experiencing == false && diagVarList[20].experiencing == false)
    {
      //logFile << endl << diagConcList[31].name << " set to TRUE!" << endl;
      terminateDiagnosisAlgorithm = true;
      finalDiagnosis = diagConcList[31];
    }
    break;

  case 32:
    if (diagConcList[29].value == true && diagVarList[19].experiencing == false && diagVarList[20].experiencing == true)
    {
      //logFile << endl << diagConcList[32].name << " set to TRUE!" << endl;
      terminateDiagnosisAlgorithm = true;
      finalDiagnosis = diagConcList[32];
    }
    break;

  case 33:
    if (diagConcList[2].value == true && diagVarList[2].experiencing == true && diagVarList[6].experiencing == true && diagVarList[9].experiencing == true && diagVarList[13].experiencing == true && diagVarList[17].experiencing == true)
    {
      //logFile << endl << diagConcList[33].name << " set to TRUE!" << endl;
      diagConcList[33].value = true;
    }
    break;

  case 34:
    if (diagConcList[33].value == true && diagVarList[21].experiencing == false)
    {
      //logFile << endl << diagConcList[34].name << " set to TRUE!" << endl;
      terminateDiagnosisAlgorithm = true;
      finalDiagnosis = diagConcList[34];
    }
    break;

  case 35:
    if (diagConcList[33].value == true && diagVarList[21].experiencing == true)
    {
      //logFile << endl << diagConcList[35].name << " set to TRUE!" << endl;
      diagConcList[35].value = true;
    }
    break;

  case 36:
    if (diagConcList[35].value == true && diagVarList[22].experiencing == true)
    {
      //logFile << endl << diagConcList[36].name << " set to TRUE!" << endl;
      terminateDiagnosisAlgorithm = true;
      finalDiagnosis = diagConcList[36];
    }
    break;

  case 37:
    if (diagConcList[35].value == true && diagVarList[22].experiencing == false)
    {
      // logFile << endl << diagConcList[37].name << " set to TRUE!" << endl;
      terminateDiagnosisAlgorithm = true;
      finalDiagnosis = diagConcList[37];
    }
    

  default:
    logFile << endl << diagConcList[4].name << " set to TRUE!" << endl;
    terminateDiagnosisAlgorithm = true;
    finalDiagnosis = diagConcList[4];
  }

  if (terminateDiagnosisAlgorithm == false)
  {
    logFile << "Continuing with the diagnosis, hopping out of the knowledge base..." << endl;
  }
  else
  {
    logFile << "--- Found a terminating conclusion, moving on to treatment recommendation---" << endl;
    cout << "\n--- Found a terminating conclusion, moving on to treatment recommendation---" << endl;
  }

  diagConcStack.pop();
  return terminateDiagnosisAlgorithm;
}

string treatment(string cancerType, string* clauseVarList, int listSize)
{
  queue<string> treatConcQueue;
  string newClause = "INIT VALUE, NO TREATMENT FOUND";
  Clause varList[2];
  varList[0].init("cancer", cancerType);
  varList[0].instantiated = true;
  varList[1].init("treatment", "");

  treatConcQueue.push(cancerType);

  while (!treatConcQueue.empty()) {
    for (int i = 1; i < listSize; i++)
    {
      if (treatConcQueue.front() == clauseVarList[i])
      {
        //logFile << "***\nVariableFound!" << endl;
        newClause = useTreatmentKnowledgeBase(i, clauseVarList[i], varList);
        if (treatConcQueue.back() != newClause)
        { // add to queue if it wasn't already added this round:
          treatConcQueue.push(newClause);
        }
      }
    }
    treatConcQueue.pop();
  }

  return newClause;
}

string useTreatmentKnowledgeBase(int ruleNumber, string clause, Clause* varList) {
  string conclusion;

  switch (ruleNumber)
  {
  case 1:
    if (clause == "NONE")
    {
      conclusion = "NO TREATMENT NECESSARY";
      varList[1].print = conclusion;
      varList[1].instantiated = true;
    }
    break;
  case 2:
    if (clause == "ANAPLASTIC THYROID CANCER")
    {
      conclusion = "THYROIDECTOMY";
      varList[1].print = conclusion;
      varList[1].instantiated = true;
    }
    break;
  case 3:
    if (clause == "PAPILLARY THYROID CANCER")
    {
      conclusion = "THYROIDECTOMY";
      varList[1].print = conclusion;
      varList[1].instantiated = true;
    }
    break;
  case 4:
    if (clause == "MEDULLARY THYROID CANCER")
    {
      conclusion = "THYROIDECTOMY";
      varList[1].print = conclusion;
      varList[1].instantiated = true;
    }
    break;
  case 5:
    if (clause == "FOLLICULAR THYROID CANCER")
    {
      conclusion = "THYROIDECTOMY";
      varList[1].print = conclusion;
      varList[1].instantiated = true;
    }
    break;
  case 6:
    if (clause == "UROTHELIAL CARCINOMA")
    {
      conclusion = "TRANSURETHRAL RESECTION OF BLADDER TUMOR";
      varList[1].print = conclusion;
      varList[1].instantiated = true;
    }
    break;
  case 7:
    if (clause == "SQUAMOUS CELL CARCINOMA")
    {
      conclusion = "CYSTECTOMY";
      varList[1].print = conclusion;
      varList[1].instantiated = true;
    }
    break;
  case 8:
    if (clause == "SMALL CELL LUNG CANCER")
    {
      conclusion = "CHEMOTHERAPY";
      varList[1].print = conclusion;
      varList[1].instantiated = true;
    }
    break;
  case 9:
    if (clause == "NON-SMALL CELL LUNG CANCER")
    {
      conclusion = "LOBECTOMY";
      varList[1].print = conclusion;
      varList[1].instantiated = true;
    }
    break;
  case 10:
    if (clause == "RENAL CELL CARCINOMA")
    {
      conclusion = "NEPHRECTOMY";
      varList[1].print = conclusion;
      varList[1].instantiated = true;
    }
    break;
  case 11:
    if (clause == "SARCOMA OF THE KIDNEY")
    {
      conclusion = "NEPHRECTOMY";
      varList[1].print = conclusion;
      varList[1].instantiated = true;
    }
    break;
  case 12:
    if (clause == "DUCTAL ADENOCARCINOMA")
    {
      conclusion = "CHEMOTHERAPY";
      varList[1].print = conclusion;
      varList[1].instantiated = true;
    }
    break;
  case 13:
    if (clause == "ACINAR ADENOCARCINOMA")
    {
      conclusion = "CHEMOTHERAPY";
      varList[1].print = conclusion;
      varList[1].instantiated = true;
    }
    break;
  case 14:
    if (clause == "PANCREATIC NEUROENDOCRINE TUMOR")
    {
      conclusion = "PANCREATECTOMY";
      varList[1].print = conclusion;
      varList[1].instantiated = true;
    }
    break;
  case 15:
    if (clause == "HEPATOCELLULAR CARCINOMA")
    {
      conclusion = "HEPATECTOMY";
      varList[1].print = conclusion;
      varList[1].instantiated = true;
    }
    break;
  case 16:
    if (clause == "CHOLANGIOCARCINOMA")
    {
      conclusion = "HEPATECTOMY";
      varList[1].print = conclusion;
      varList[1].instantiated = true;
    }
    break;
  case 17:
    if (clause == "ANGIOSARCOMA")
    {
      conclusion = "SURGERY";
      varList[1].print = conclusion;
      varList[1].instantiated = true;
    }
    break;
  case 18:
    if (clause == "CAN'T DIAGNOSE")
    {
      conclusion = "CAN'T TREAT";
      varList[1].print = conclusion;
      varList[1].instantiated = true;
    }
    break;
  default:
    conclusion = "NO RULE FOUND";
  }

  return conclusion;
}