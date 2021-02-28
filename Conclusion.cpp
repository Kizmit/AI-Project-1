#include "Conclusion.h"

using namespace std;

/*
Conclusion::Conclusion(string pass_n, string pass_finalConclusion, int pass_ruleNumber)
{
    name = pass_n;    
    finalConclusion = pass_finalConclusion;
    ruleNumber = pass_ruleNumber;
    clauseNumber = (pass_ruleNumber * 6) - 5;
}
*/

Conclusion::setConcInitialValues(string pass_n, string pass_finalConclusion, int pass_ruleNumber)
{
    name = pass_n;    
    finalConclusion = pass_finalConclusion;
    ruleNumber = pass_ruleNumber;
    clauseNumber = (pass_ruleNumber * 6) - 5;
}