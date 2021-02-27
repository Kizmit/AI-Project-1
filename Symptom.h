#include <string>

using namespace std;

class Symptom{
    public:
        string name;
        bool instantiated = false;
        bool experiencing;      // Does the patient have this symptom?

        Symptom(string);
};