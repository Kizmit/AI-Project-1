#include "Conclusion.h"

using namespace std;

void Conclusion::init(string pass_n, string pass_finalConclusion, int pass_ruleNumber)
{
  name = pass_n;
  finalConclusion = pass_finalConclusion;
  ruleNumber = pass_ruleNumber;
  clauseNumber = (pass_ruleNumber * 6) - 5;
}