#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include "Conclusion.h"
#include "Clause.h"

// Actual Amount of Entries each list will contain. Useful for parsing more efficiently.
#define VARIABLE_AMOUNT 43
#define CONCLUSIONS_AMOUNT 37
#define CLAUSE_VAR_LIST_ENTIRES 172 // VARIABLE_AMOUNT * 4

// Create the Structures with some overheard, based off the amount of variables. (Per example .cpp files)
#define VARIABLE_LIST_SIZE 50
#define CONCLUSION_LIST_SIZE 40
#define CLAUSE_VAR_LIST_SIZE 225 //223 needed as each rule may have up to 6 clause variables (6*37)
#define CONC_STACK_SIZE 20

#define LIST_WIDTH 3