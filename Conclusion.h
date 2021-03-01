#include <string>

using namespace std;

struct Conclusion{
    
    public:
        string name;
        string finalConclusion;
        int ruleNumber, clauseNumber;
        bool value; // Will we need this? We need to track what is set when the rule is accessed.
        bool instantiated = false;

        void init(string, string, int);
};