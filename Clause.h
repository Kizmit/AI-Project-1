#include <string>

using namespace std;

struct Clause{
    public:
        string name, print;
        int age;        // USed only in the case of an Integer input, Age questions should be the only case. Ex: "How old are you"
        bool instantiated = false;       //Has the patient indicated yes or no to this symptom
        bool experiencing = false;              // Does the patient have this symptom?
        bool markedForInstantiation = true;
        void init(string, string);

}; 