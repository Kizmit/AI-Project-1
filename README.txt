[DESCRIPTION]
This project is intended to run properly on the txst linux servers (zeus.cs.txstate.edu/eros.cs.txstate.edu).
It is split into multiple files, with Project1-(netID).cpp being the main program file. See Project1-(netID).docx for
a full report on the data structures, design, code analysis, etc.

[AUTHORS]
Brandon Burtchell
Joe McAdams
Jeff Wilson

[COMPILATION AND RUNNING]
Use the following linux commands to compile and run the program:

g++ -std=c++11 Clause.h Clause.cpp Conclusion.h Conclusion.cpp Project1.h Project1.cpp -o proj1
./proj1

From there, follow the on-screen prompts to navigate the program.

[LOG]
Please note that this program also outputs a log file titled Project1-LOG_ID#(id number).txt, with (id number)
being specified by the user at runtime. This log serves as the way to view intermediate steps of the inference
engine, so as to no clog up the output of the program.