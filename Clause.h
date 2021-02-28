#include <string>

struct Clause{
    public:
        string name, print;
        int age;
        bool instantiated = false;       //Has the patient indicated yes or no to this symptom
        bool experiencing = false;              // Does the patient have this symptom?

        //Symptom(string) Maybe instantiate as needed with user input?
}; 