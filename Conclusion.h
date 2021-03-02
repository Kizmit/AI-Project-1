#include <string>

using namespace std;

struct Conclusion{
    
    public:
        string name;
        string finalConclusion;
        int ruleNumber, clauseNumber;
        bool instantiated = false;
        bool value;     // Used to store sub conclusion values

        void init(string, string, int);
};