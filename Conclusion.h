#include <string>

using namespace std;

struct Conclusion{
    
    public:
        string name;
        string finalConclusion;
        int ruleNumber, clauseNumber;
        
        // Conclusion(string n, string, int);

        void setConcInitialValues(string, string, int);
};