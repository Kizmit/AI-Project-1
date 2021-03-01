#include <string>

using namespace std;

struct Clause{
    public:
        string name, print;
        int age;
        bool instantiated = false;       //Has the patient indicated yes or no to this symptom
        bool experiencing = false;              // Does the patient have this symptom?

        //Clause(string , string);
        //Clause();

        void setClauseInitialValues(string, string);

}; 