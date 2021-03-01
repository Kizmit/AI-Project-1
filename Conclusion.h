#include <string>

using namespace std;

struct Conclusion{
    
    public:
        string name;
        string finalConclusion;
        int ruleNumber, clauseNumber;
        

        void init(string, string, int);
};