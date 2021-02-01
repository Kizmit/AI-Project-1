Enclosed a program, which comprises the inference engine based on backward chaining.  You need it for your 
project #1.  The program contains some errors and it is not designed to be efficient. 
Modify the program to make it better and efficient.  Explain in your report how you have modified the
program to make it better.



/*****backward chaining *******/ 
/* Install your IF clauses in sequence in the first case 
   statement of the main program 
   example: if((a1==2) && (a2==6)) s=1; 
                      if(strcmp(j,NO") != 0) s=1; 
   the then part of the above construction always 
   contains s=1; 
   install your the clauses in sequence in the second 
   case statement of the main program 
   example strcpy(po,"YES"); 


/*  conclusion list */ 
char conclt[10][3]; 
/*  variable list */ 
char varlt[10][3]; 
/*  clause vairable list */ 
char clvarlt[40][3]; 
char varble[3]; 
char /* qualify */ qu[4], /* degree*/ de[4]; 
char /* discovery */ di[4], /* position */ po[4]; 
char buff[128]; 

/* instantiated list */ 
int instlt[11]; 
/* statement stack */ 
int statsk[11]; 
int /* clause stack */ clausk[11], sn, f, i, j, s, k, /*stack pointer */ sp; 

float /* grade */ gr, /*experience */ ex; 

void determine_member_concl_list(void); 
void push_on_stack(void); 
void instantiate(void); 

main() 
{ 
        /***** initialization section ******/ 
        /* stack space is 10 we initially place stack space at 10+1 */ 
        sp=11; 
        for (i=1; i<11; i++) 
        { 
                strcpy(conclt[i],""); 
                strcpy(varlt[i],""); 
                instlt[i]=0; 
                statsk[i]=0; 
                clausk[i]=0; 
        } 
        for (i=1; i<41; i++)  strcpy(clvarlt[i],""); 
        /* enter conclusions which are the variables in the then part, 
1 at 
        a time.  enter the conclusions in exact order starting at the 1st 
        if-then.  after last conclusion hit return key for rest of 
        conclusions */ 

        /*** comment 305 *****/ 
        strcpy(conclt[1], "PO"); 
        strcpy(conclt[2], "QU"); 
        strcpy(conclt[3], "PO"); 
        strcpy(conclt[4], "PO"); 
        strcpy(conclt[5], "PO"); 
        strcpy(conclt[6], "PO"); 
        printf("*** CONCLUSION LIST ***\n"); 
        for (i=1; i<11; i++) printf("CONCLUSION %d %s\n", i,conclt[i]); 

        printf("HIT RETURN TO CONTINUE"); 
        gets(buff); 
        /* enter variables which are in the if part, 1 at a time in the 
exact 
        order that they occur, up to 3 variables per if statement.  do not 
        duplicate any variable names.  any name is used only once.  if no 
        more variables left just hit return key. */ 
        printf("*** VARIABLE LIST *\n"); 
        /**** comment 367 *****/ 
        strcpy(varlt[1], "DE"); 
        strcpy(varlt[2], "DI"); 
        strcpy(varlt[3], "EX"); 
        strcpy(varlt[4], "GR"); 
        for(i=1; i<11; i++) printf("VARIABLE %d %s\n", i, varlt[i]); 
        printf("HIT RETURN KEY TO CONTINUE"); 
        gets(buff); 
        /* enter variables as they appear in the if clauses.  a maximum 
of 3 
        variables per if statement.  if no more variables hit return 
key. */ 
        printf("*** CLAUSE VARIABLE LIST ***\n"); 
        /***** comment 407 through 409 ***/ 
        strcpy(clvarlt[1], "DE"); 
        strcpy(clvarlt[5], "DE"); 
        strcpy(clvarlt[9], "DE"); 
        strcpy(clvarlt[10], "DI"); 
        strcpy(clvarlt[13], "QU"); 
        strcpy(clvarlt[14], "GR"); 
        strcpy(clvarlt[15], "EX"); 
        strcpy(clvarlt[17], "QU"); 
        strcpy(clvarlt[18], "GR"); 
        strcpy(clvarlt[19], "EX"); 
        strcpy(clvarlt[21], "QU"); 
        strcpy(clvarlt[22], "GR"); 
        for(i=1; i<9; i++) 
        { 
                printf("** CLAUSE %d\n", i); 
                for(j=1; j<5; j++) 
                { k = 4 * (i-1) + j; 
                  printf("VARIABLE %d  %s\n", j, clvarlt[k]); } 
                if (i==4) 
                { printf("HIT RETURN KEY TO CONTINUE"); gets(buff); } 
        } 
        /****** inference section *****/ 
        printf("** ENTER CONCLUSION ? "); gets(varble); 
        /* get conclusion statement number (sn) from the conclusion list 
           (conclt) */ 
        /* first statement starts search */ 
b520: f=1; 
          determine_member_concl_list(); 
          if (sn != 0){ 
                  /* if sn = 0 then no conclusion of that name */ do 
                  /* push statement number (sn) and clause number=1 on 
goal 
                     stack which is composed of the statement stack 
(statsk) 
                     and clause stack (clausk) */ 
                  { 
                          push_on_stack(); 
                          do 
                          { 
                           /* calculate clause location in clause-variable 
                              list */ 
b545: i= (statsk[sp] -1) *4 + clausk[sp]; 
          /* clause variable */ 
          strcpy(varble, clvarlt[i]); 
          if(strcmp(varble, "") != 0) { 
                  /*is this clause variable a conclusion? */ 
                  f = 1; 
                  determine_member_concl_list(); 
                  if(sn != 0) 
                          /* it is a conclusion push it */ 
                          goto b520; 
                  /* check instantiation of this clause */ 
                  instantiate(); 
                  clausk[sp] = clausk[sp] + 1; 
          } 
                          } while(strcmp(varble, "") != 0); /*do-while*/ 
                          /*no more clauses check if part of statement */ 
                          sn = statsk[sp]; 
                          s = 0; 
                          /**** if then statements ****/ 
                          /* sample if parts of if then statements from 
                             the position knowledge base */ 
                          switch (sn) { 
                                  /* if part of statement 1 */ 
                                  /****** comment 1500 ****/ 
                          case 1: if(strcmp(de, "NO") == 0) s = 1; 
                                  break; 
                                  /* if part of statement 2 */ 
                                  /***** comment 1510 ******/ 
                          case 2: if(strcmp(de, "YES") == 0) s = 1; 
                                  break; 
                                  /* if part of statement 3 */ 
                          case 3: if((strcmp(de, "YES") == 0) && 
                                     (strcmp(di, "YES") == 0)) s =1; 
                                  break; 
                                  /* if part of statement 4 */ 
                                  /******** comment 1560 ******/ 
                          case 4: if((strcmp(qu, "YES") == 0) && 
                                     (gr<3.5) && (ex >= 2)) s = 1; 
                                  break; 
                                  /******** comment 1570 ********/ 
                                  /* if part of statement 5 */ 
                          case 5: if((strcmp(qu, "YES") == 0) && 
                                     (gr<3) && (ex<2)) s = 1; 
                                  break; 
                                  /* if part of statement 6 */ 
                          case 6: if((strcmp(qu, "YES") == 0) && 
                                     (gr >=3.5)) s = 1; 

                                  break; 
                                  /********* comment 1680 ******/ 
                          } 
                          /* see if the then part should be invoked */ 
                          if( s != 1) { 
                                  /* failed..search rest of statements for 
                                     same conclusion */ 
                                  /* get conclusion */ 
                                  i = statsk[sp]; 
                                  strcpy(varble, conclt[i]); 
                                  /* search for conclusion starting at the 
                                     next statement number */ 
                                  f = statsk[sp] + 1; 
                                  determine_member_concl_list(); 
                                  sp = sp+1; 
                          } 
                          /* pop old conclusion and put on new one */ 
                  } while((s != 1) && (sn !=0));  /* outer do-while loop */ 
                  if(sn != 0){ 
                          /* if part true invoke then part */ 
                          /* then part of if-then statements from the 
                             position knowledge base */ 
                          switch (sn) { 
                                  /* then part of statement 1 */ 
                                  /******* comment 1500 *******/ 
                          case 1: strcpy(po, "NO"); 
                                  printf("PO=NO\n"); 
                                  break; 
                                  /* then part of statement 2 */ 
                                  /****** comment 1510 ******/ 
                          case 2: strcpy(qu, "YES"); 
                                  printf("QU=YES\n"); 
                                  break; 
                                  /* then part of statement 3 */ 
                          case 3: strcpy(po, "YES"); 
                                  printf("PO=RESEARCH\n"); 
                                  break; 
                                  /* then part of statement 4 */ 
                                  /******** comment 1560 ******/ 
                          case 4: strcpy(po, "YES"); 
                                  printf("PO=SERVICE ENGINEER\n"); 
                                  break; 
                                  /* then part of statement 5 */ 
                                  /****** comment 1570 *****/ 
                          case 5: strcpy(po, "NO"); 
                                  printf("PO=NO"); 
                                  break; 
                                  /* then part of statement 6 */ 
                          case 6: strcpy(po, "YES"); 
                                  printf("PO=PRODUCT ENGINEER\n"); 
                                  break; 
                                  /****** comment 1680 ********/ 
                          } 
                          /* pop the stack */ 
                          sp=sp+1; 
                          if(sp >= 11) 
                                  /* finished */ 
                                  printf("*** SUCCESS\n"); 
                          else { 
                                  /* stack is not empty */ 
                                  /* get next clause then continue */ 
                                  clausk[sp] = clausk[sp]+1; 
                                  goto b545; 
                          } 
                  } 
        } 
} 

void determine_member_concl_list() { 
/* routine to determine if a variable (varble) is a member of the 
   conclusion list (conclt).  if yes return sn != 0. 
   if not a member sn=0; 
*/ 
        /* initially set to not a member */ 
        sn = 0; 
        /* member of conclusion list to be searched is f */ 
        i = f; 
        while((strcmp(varble, conclt[i]) != 0) && (i<8)) 
                /* test for membership */ 
                i=i+1; 
        if (strcmp(varble, conclt[i]) == 0) sn = i;  /* a member */ 
} 

void push_on_stack() 
/* routine to push statement number (sn) and a clause number of 1 onto the 
conclusion stack which consists of the statement stack (statsk) and the 
clause stack (clausk)..to push decrement stack pointer (sp) */ 
{ 
        sp=sp-1; 
        statsk[sp] = sn; 
        clausk[sp] = 1; 
} 

void instantiate() 
/* routine to instantiate a variable (varble) if it isn't already.  the 
instantiate indication (instlt) is a 0 if not, a 1 if it is.  the 
variable list (varlt) contains the variable (varble). */ 
{ 
        i=1; 
        /* find variable in the list */ 
        while((strcmp(varble, varlt[i]) != 0) && (i<10)) i=i+1; 
        if((strcmp(varble, varlt[i]) == 0) && (instlt[i] != 1)) 
                /*found variable and not already instantiated */ 
        { 
                instlt[i]=1; /*mark instantiated */ 
                /* the designer of the 
               knowledge base places the input statements to 
               instantiate the variables below in the case statement */ 
                switch (i) 
                { 
                        /***** input statement *****/ 
                        /* input statements for sample position knowledge 
                           base */ 
                        /***** comment 1700 ******/ 
                case 1: printf("INPUT YES OR NOW FOR DE-? "); 
                        gets(de); 
                        break; 
                case 2: printf("INPUT YES OR NO FOR DI-? "); 
                        gets(di); 
                        break; 
                case 3: printf("INPUT A REAL NUMBER FOR EX-? "); 
                        scanf("%f", &ex); 
                        break; 
                case 4: printf("INPUT A REAL NUMBER FOR GR-? "); 
                        scanf("%f", &gr); 
                        break; 
                        /***** comment 1715 ****/ 
                } 
                /* end of inputs statements for sample position knowledge 
                   base */ 
        } 
} 



