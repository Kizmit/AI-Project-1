// AI XS Project 1.cpp : Defines the entry point for the application.
//

#include "BCDiagnosis.h"



/*****backward chaining *******/
/* Install your IF clauses in sequence in the first case
   statement of the main program
   example: if((a1==2) && (a2==6)) s=1;
            if(strcmp(j,NO") != 0) s=1;
   the then part of the above construction always
   contains s=1;
   install your the clauses in sequence in the second
   case statement of the main program
   example strcpy(position,"YES");
*/

char conclusionList[11][3];
char clauseVariableList[50][3];
char variableList[11][3];
char variable[3];
char qualify[4], degree[4];
char discovery[4], position[4];

int instantiatedList[11];
int statementStack[50];
int clauseStack[50], sn, f, i, j, s, k, /*stack pointer */ sp;

float grade, experience;

void determine_member_concl_list(void);
void push_on_stack(void);
void instantiate(void);
using namespace std;
int main()
{
    /***** initialization section ******/
    /* stack space is 10 we initially place stack space at 10+1 */
    sp = 51;
    for (i = 1; i < 11; i++)
    {
        strcpy(conclusionList[i], "");
        strcpy(variableList[i], "");
        instantiatedList[i] = 0;
        statementStack[i] = 0;
        clauseStack[i] = 0;
    }
    for (i = 1; i < 41; i++)
        strcpy(clauseVariableList[i], "");
    /* enter conclusions which are the variables in the then part, 1 at
      a time.  enter the conclusions in exact order starting at the 1st
      if-then.  after last conclusion hit return key for rest of
      conclusions */

      /*** comment 305 *****/
    strcpy(conclusionList[1], "PO");
    strcpy(conclusionList[2], "QU");
    strcpy(conclusionList[3], "PO");
    strcpy(conclusionList[4], "PO");
    strcpy(conclusionList[5], "PO");
    strcpy(conclusionList[6], "PO");
    printf("*** CONCLUSION LIST ***\n");
    for (i = 1; i < 11; i++)
        printf("CONCLUSION %d %s\n", i, conclusionList[i]);

    printf("HIT RETURN TO CONTINUE");
    cin.ignore();
    /* enter variables which are in the if part, 1 at a time in the exact
      order that they occur, up to 3 variables per if statement.  do not
      duplicate any variable names.  any name is used only once.  if no
      more variables left just hit return key. */
    printf("*** VARIABLE LIST *\n");
    /**** comment 367 *****/
    strcpy(variableList[1], "DE");
    strcpy(variableList[2], "DI");
    strcpy(variableList[3], "EX");
    strcpy(variableList[4], "GR");
    for (i = 1; i < 11; i++)
        printf("VARIABLE %d %s\n", i, variableList[i]);
    printf("HIT RETURN KEY TO CONTINUE");
    cin.ignore();
    /* enter variables as they appear in the if clauses.  a maximum of 3
      variables per if statement.  if no more variables hit return key. */
    printf("*** CLAUSE VARIABLE LIST ***\n");
    /***** comment 407 through 409 ***/
    strcpy(clauseVariableList[1], "DE");
    strcpy(clauseVariableList[5], "DE");
    strcpy(clauseVariableList[9], "DE");
    strcpy(clauseVariableList[10], "DI");
    strcpy(clauseVariableList[13], "QU");
    strcpy(clauseVariableList[14], "GR");
    strcpy(clauseVariableList[15], "EX");
    strcpy(clauseVariableList[17], "QU");
    strcpy(clauseVariableList[18], "GR");
    strcpy(clauseVariableList[19], "EX");
    strcpy(clauseVariableList[21], "QU");
    strcpy(clauseVariableList[22], "GR");
    for (i = 1; i < 9; i++)
    {
        printf("** CLAUSE %d\n", i);
        for (j = 1; j < 5; j++)
        {
            k = 4 * (i - 1) + j;
            printf("VARIABLE %d  %s\n", j, clauseVariableList[k]);
        }
        if (i == 4)
        {
            printf("HIT RETURN KEY TO CONTINUE");
            cin.ignore();
        }
    }
    /****** inference section *****/
    printf("** ENTER CONCLUSION ? ");
    cin >> variable;
    /* get conclusion statement number (sn) from the conclusion list (conclusionList) */
    /* first statement starts search */
b520:
    f = 1;
    determine_member_concl_list();
    if (sn != 0)
    {
        /* if sn = 0 then no conclusion of that name */ do
            /* push statement number (sn) and clause number=1 on goal
              stack which is composed of the statement stack (statementStack)
              and clause stack (clauseStack) */
        {
            push_on_stack();
            do
            {
                /* calculate clause location in clause-variable list */
            b545:
                i = (statementStack[sp] - 1) * 4 + clauseStack[sp];
                /* clause variable */
                strcpy(variable, clauseVariableList[i]);
                if (strcmp(variable, "") != 0)
                {
                    /*is this clause variable a conclusion? */
                    f = 1;
                    determine_member_concl_list();
                    if (sn != 0)
                        /* it is a conclusion push it */
                        goto b520;
                    /* check instantiation of this clause */
                    instantiate();
                    clauseStack[sp] = clauseStack[sp] + 1;
                }
            } while (strcmp(variable, "") != 0); /*do-while*/
            /*no more clauses check if part of statement */
            sn = statementStack[sp];
            s = 0;
            /**** if then statements ****/
            /* sample if parts of if then statements from the position knowledge base */
            switch (sn)
            {
                /* if part of statement 1 */
                /****** comment 1500 ****/
            case 1:
                if (strcmp(degree, "NO") == 0)
                    s = 1;
                break;
                /* if part of statement 2 */
                /***** comment 1510 ******/
            case 2:
                if (strcmp(degree, "YES") == 0)
                    s = 1;
                break;
                /* if part of statement 3 */
            case 3:
                if ((strcmp(degree, "YES") == 0) &&
                    (strcmp(discovery, "YES") == 0))
                    s = 1;
                break;
                /* if part of statement 4 */
                /******** comment 1560 ******/
            case 4:
                if ((strcmp(qualify, "YES") == 0) &&
                    (grade < 3.5) && (experience >= 2))
                    s = 1;
                break;
                /******** comment 1570 ********/
                /* if part of statement 5 */
            case 5:
                if ((strcmp(qualify, "YES") == 0) &&
                    (grade < 3) && (experience < 2))
                    s = 1;
                break;
                /* if part of statement 6 */
            case 6:
                if ((strcmp(qualify, "YES") == 0) &&
                    (grade >= 3.5))
                    s = 1;

                break;
                /********* comment 1680 ******/
            }
            /* see if the then part should be invoked */
            if (s != 1)
            {
                /* failed..search rest of statements for same conclusion */
                /* get conclusion */
                i = statementStack[sp];
                strcpy(variable, conclusionList[i]);
                /* search for conclusion starting at the next statement number */
                f = statementStack[sp] + 1;
                determine_member_concl_list();
                sp = sp + 1;
            }
            /* pop old conclusion and put on new one */
        } while ((s != 1) && (sn != 0)); /* outer do-while loop */
        if (sn != 0)
        {
            /* if part true invoke then part */
            /* then part of if-then statements from the position knowledge base */
            switch (sn)
            {
                /* then part of statement 1 */
                /******* comment 1500 *******/
            case 1:
                strcpy(position, "NO");
                printf("PO=NO\n");
                break;
                /* then part of statement 2 */
                /****** comment 1510 ******/
            case 2:
                strcpy(qualify, "YES");
                printf("QU=YES\n");
                break;
                /* then part of statement 3 */
            case 3:
                strcpy(position, "YES");
                printf("PO=RESEARCH\n");
                break;
                /* then part of statement 4 */
                /******** comment 1560 ******/
            case 4:
                strcpy(position, "YES");
                printf("PO=SERVICE ENGINEER\n");
                break;
                /* then part of statement 5 */
                /****** comment 1570 *****/
            case 5:
                strcpy(position, "NO");
                printf("PO=NO");
                break;
                /* then part of statement 6 */
            case 6:
                strcpy(position, "YES");
                printf("PO=PRODUCT ENGINEER\n");
                break;
                /****** comment 1680 ********/
            }
            /* pop the stack */
            sp = sp + 1;
            if (sp >= 11)
                /* finished */
                printf("*** SUCCESS\n");
            else
            {
                /* stack is not empty */
                /* get next clause then continue */
                clauseStack[sp] = clauseStack[sp] + 1;
                goto b545;
            }
        }
    }
}

void determine_member_concl_list()
{
    /* routine to determine if a variable (variable) is a member of the
     conclusion list (conclusionList).  if yes return sn != 0.
     if not a member sn=0;
  */
  /* initially set to not a member */
    sn = 0;
    /* member of conclusion list to be searched is f */
    i = f;
    while ((strcmp(variable, conclusionList[i]) != 0) && (i < 8))
        /* test for membership */
        i = i + 1;
    if (strcmp(variable, conclusionList[i]) == 0)
        sn = i; /* a member */
}

void push_on_stack()
/* routine to push statement number (sn) and a clause number of 1 onto the
conclusion stack which consists of the statement stack (statementStack) and the
clause stack (clauseStack)..to push decrement stack pointer (sp) */
{
    sp = sp - 1;
    statementStack[sp] = sn;
    clauseStack[sp] = 1;
}

void instantiate()
/* routine to instantiate a variable (variable) if it isn't already.  the
instantiate indication (instantiatedList) is a 0 if not, a 1 if it is.  the
variable list (variableList) contains the variable (variable). */
{
    i = 1;
    /* find variable in the list */
    while ((strcmp(variable, variableList[i]) != 0) && (i < 10))
        i = i + 1;
    if ((strcmp(variable, variableList[i]) == 0) && (instantiatedList[i] != 1))
        /*found variable and not already instantiated */
    {
        instantiatedList[i] = 1; /*mark instantiated */
        /* the designer of the
          knowledge base places the input statements to
          instantiate the variables below in the case statement */
        switch (i)
        {
            /***** input statement *****/
            /* input statements for sample position knowledge base */
            /***** comment 1700 ******/
        case 1:
            printf("INPUT YES OR NO FOR DE-? ");
            cin >> (degree);
            break;
        case 2:
            printf("INPUT YES OR NO FOR DI-? ");
            cin >> (discovery);
            break;
        case 3:
            printf("INPUT A REAL NUMBER FOR EX-? ");
            scanf("%f", &experience);
            break;
        case 4:
            printf("INPUT A REAL NUMBER FOR GR-? ");
            scanf("%f", &grade);
            break;
            /***** comment 1715 ****/
        }
        /* end of inputs statements for sample position knowledge base */
    }
}

