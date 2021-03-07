#include <iostream>
#include <fstream> // for logging
#include <stack>
#include <queue>
#include <string>
#include "Conclusion.h"
#include "Clause.h"

// constants for data structures:
#define DIAG_VAR_LIST_SIZE 25
#define DIAG_CONC_LIST_SIZE 40
#define DIAG_CLAUSE_VAR_LIST_SIZE 225 // max of six clauses per rule, 6 * 37 = 223