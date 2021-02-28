#include "Conclusion.h"
struct Conclusion::Conclusion(string n, string finalConclusion, int ruleNumber)
{
    name = n;    
    this.finalConclusion = finalConclusion;
    this.ruleNumber = ruleNumber;
    clauseNumber = (ruleNumber * 6) - 5;
}