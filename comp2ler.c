//Tzetzis Markos AM : 2142  Giokas Stelios AM : 2230

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

#define falsecharID 0
#define plusID 1
#define minusID 2
#define starID 3
#define slasID 4
#define equalID 5
#define forID 6
#define thenID 7
#define ifID 8
#define beginID 9
#define whileID 10

//telestes susxetiseis
#define smeqID 11		// '<='
#define diffID 12		// '<>'
#define bieqID 13		// '>='
#define bigID 14		// '>'

//sumvolo anatheshs
#define assignID 15

#define commaID 16
#define oparID 17
#define cparID 18
#define quesID 19

//anagnwristika
#define numID 20
#define wordID 21

#define notID 22
#define andID 23
#define varID 24
#define doID 25
#define elseID 26
#define exitID 28
#define procedureID 29
#define functionID 30
#define printID 31
#define inID 33
#define inoutID 34
#define forcaseID 35
#define programID 36
#define orID 37
#define returnID 38
#define copyID 39
#define whenID 40
#define callID 41
#define oagisID 42
#define cagisID 43
#define oagilID 44
#define cagilID   45
#define smallID 46

			/*================= Global variables ================*/
FILE * input;
int line ;
int token ;
char id[30] ;
char relop[30];
char muloper[30];
char addoper[30];
char type[30];
int label;
char num[30];
int where ;
char  funcname[30] ;
			/*=======================intermediate declarations =========================*/



typedef struct quad
{
	int num;
	char *op;	/* Gia tous telestes +, -, *, / */
	char *op1;	/* Prwto ekteloumeno */
	char *op2;	/* Deutero ekteloumeno */
	char *op3;	/* Apotelesma */
	struct quad *next;	/* Deiktis sto epomeno stoixeio */
}QUAD;

typedef struct ptr_quad
{
	QUAD * head;
	QUAD * tail;
}PTR_QUAD;

typedef struct label
{
	int mylabel;
	struct label * next;
}LABEL;

typedef struct ptr_label
{
	LABEL * lhead;
	LABEL * ltail;
}PTR_LABEL;

typedef struct logical_condition
{
	PTR_LABEL mytrue;
	PTR_LABEL myfalse;
}LOGICAL_CONDITION;

PTR_QUAD list_quad;
PTR_LABEL * exit_list;
PTR_LABEL * e ;

            PTR_LABEL * exit_if ;
            PTR_LABEL * exit_for ;
            PTR_LABEL * exit_dowhile;
            PTR_LABEL * exit_while ;


int T_names = 1;
char * name_of_program;
char * name_of_function;
char * name_of_procedure;
int number_of_quads = 1;

int nextquad();
void genquad(PTR_QUAD * list, char *op, char *op1, char *op2, char *op3);
char *newtemp();
void backpatch(PTR_LABEL * label1, PTR_QUAD * quad1, int z);

PTR_LABEL * mergelist(PTR_LABEL *list1, PTR_LABEL * list2);
PTR_LABEL * makelist(int x,PTR_LABEL * list);
PTR_LABEL * emptylist(PTR_LABEL * list);


			/*================ Functions' prototypes =======================*/

void program();
void block() ;
void declarations() ;
void varlist() ;
void subprograms() ;
void func();
void funcbody();
void formalparitem();
void formalparlist();
void formalpars() ;
void sequence() ;
void brackets_seq() ;
void brack_or_stat() ;
void statement() ;
void assigment_stat();
void if_stat();
void while_stat();
void do_while_stat();
void forcase_stat() ;
void call_stat() ;
void return_stat() ;
void print_stat() ;
void else_part() ;

void boolfactor(LOGICAL_CONDITION * Bf);
void boolterm(LOGICAL_CONDITION * Bt);
void condition(LOGICAL_CONDITION * C);

void actualparitem() ;
void actualparlist();
void actualpars();

void optional_sign();
void expression(char * E_place) ;
void term(char * T_place) ;
void factor(char * E_place);
void relational_oper();
void mul_oper() ;
void add_oper();

void id_tail();



/*========= Auxiliary functions =========*/
int findword(char*buff){

    char f[30];
    puts(buff);
    int ret ;
    int i ;
for( i=0;i<30;i++){
    id[i] = '\0';
}
    strcpy(f,"for");
    ret = strcmp(buff , f);

    if (strcmp(buff , f) == 0){

        return forID ;
    }
    strcpy(f,"then");
      if (strcmp(buff , f) == 0){
        return thenID ;
    }
    strcpy(f,"begin");
      if (strcmp(buff , f) == 0){
        return beginID ;
    }
    strcpy(f,"if");
      if (strcmp(buff , f) == 0){
        return ifID ;
    }

    strcpy(f,"while");
      if (strcmp(buff , f) == 0){
        return whileID ;
    }
	strcpy(f,"not");
      if (strcmp(buff , f) == 0){
        return notID ;
    }
	strcpy(f,"and");
      if (strcmp(buff , f) == 0){
        return andID ;
    }
	strcpy(f,"do");
      if (strcmp(buff , f) == 0){

        return doID ;
    }
	strcpy(f,"else");
      if (strcmp(buff , f) == 0){
        return elseID ;
    }
	strcpy(f,"exit");
      if (strcmp(buff , f) == 0){
        return exitID ;
    }
	strcpy(f,"var");
      if (strcmp(buff , f) == 0){
        return varID ;
    }
	strcpy(f,"procedure");
      if (strcmp(buff , f) == 0){
        return procedureID ;
    }
	strcpy(f,"function");
      if (strcmp(buff , f) == 0){
        return functionID ;
    }
	strcpy(f,"print");
      if (strcmp(buff , f) == 0){
        return printID ;
    }
	strcpy(f,"in");
      if (strcmp(buff , f) == 0){
        return inID ;
    }
	strcpy(f,"inout");
      if (strcmp(buff , f) == 0){
        return inoutID ;
    }
	strcpy(f,"forcase");
      if (strcmp(buff , f) == 0){
        return forcaseID ;
    }
	strcpy(f,"program");
      if (strcmp(buff , f) == 0){
        return programID ;
    }
	strcpy(f,"or");
      if (strcmp(buff , f) == 0){
        return orID ;
    }
	strcpy(f,"copy");
      if (strcmp(buff , f) == 0){
        return copyID ;
    }
	strcpy(f,"return");
      if (strcmp(buff , f) == 0){
        return returnID ;
    }
	strcpy(f,"when");
      if (strcmp(buff , f) == 0){
        return whenID ;
    }
	strcpy(f,"call");
      if (strcmp(buff , f) == 0){
        return callID ;
    }

    strcpy(id , buff);

    return wordID ;

}

 		 /*======================== intermediate code functions =============================*/

int nextquad()
{
	return number_of_quads;
}

void genquad(PTR_QUAD * list, char *oper, char *oper1, char *oper2, char *oper3)
{
	QUAD *new_quad;
	new_quad = (QUAD*)malloc(sizeof(QUAD));

	new_quad->op = (char*)malloc(30*sizeof(char));
	new_quad->op1 = (char*)malloc(30*sizeof(char));
	new_quad->op2 = (char*)malloc(30*sizeof(char));
	new_quad->op3 = (char*)malloc(30*sizeof(char));

	strcpy(new_quad->op,oper);
	strcpy(new_quad->op1,oper1);
	strcpy(new_quad->op2,oper2);
	strcpy(new_quad->op3,oper3);

	/* ARITHMOS TETRADAS */
	new_quad->num = number_of_quads;
	number_of_quads++;
	new_quad->next = NULL;

	if(list->head == NULL)
	{
		list->head = new_quad;
		list->tail = new_quad;
	}
	else
	{
		list->tail->next = new_quad;
		list->tail = new_quad;
	}
}

PTR_LABEL * emptylist(PTR_LABEL * list)
{
	list->lhead = NULL;
	list->ltail = NULL;
	return(list);
}

PTR_LABEL * makelist(int x,PTR_LABEL * list)
{
	LABEL * new_label;
	new_label = (LABEL *)malloc(sizeof(LABEL));

	list->lhead = new_label;
	list->ltail = new_label;
	new_label->mylabel = x;
	new_label->next = NULL;

	return(list);
}


PTR_LABEL *mergelist(PTR_LABEL *list1, PTR_LABEL * list2)
{
	if(list1 == NULL)
	{
		return (list2);
	}
	else if(list2 == NULL)
	{
		return (list1);
	}
	else
	{
		list1->ltail->next = list2->lhead;
		list1->ltail = list2->ltail;
		list2->lhead = NULL;
		return (list1);
	}
}

void backpatch(PTR_LABEL * label1, PTR_QUAD * quad1, int z)
{
	QUAD * fori;
	LABEL * forj;

	fori = (QUAD*)malloc(sizeof(QUAD));
	forj = (LABEL*)malloc(sizeof(LABEL));

	for(forj = label1->lhead; forj != NULL; forj = forj->next)
	{
		for(fori = quad1->head; fori !=NULL; fori = fori->next)
		{
			if(fori->num == forj->mylabel)
			{
				sprintf(fori->op3,"%d",z);
				break;
			}
		}
	}
	label1->lhead = NULL;
	label1->ltail = NULL;

}

char* newtemp()
{
        char* s=NULL;

        s=(char*)malloc(sizeof(char));

        sprintf(s,"T_%d",T_names);
        T_names++;

        return s;
}

/*-----------------------------------------------------Pinakas Sumvolwn---------------------------------------------------*/
char * name_of_program;

typedef struct argument
{
	char name_of_arg[30];
	int offset;
	int parmode;
	struct argument * next;
}ARGUMENT;

typedef struct entity
{
	char name_of_entity[30];
	int type_of_entity;
	union utype_of_entity
	{
		struct var		//Periptosi metavlitis
		{
			int offset;
		}VAR;

		struct tempvar		//Periptosi topikis metavlitis
		{
			int offset;
		}TEMPVAR;

		struct parameter	//Periptosi parametrou
		{
			int offset;
			int type;		//0 gia in kai 1 gia inout
		}PARAMETER;

		struct subroutines
		{
			int type;		//0 gia function kai 1 gia procedure
			ARGUMENT * list;	//Lista apo parametrous
			int nestingLevel;	//Epipedo foliasmatos
			int frame_length;
			int start_quad;
		}SUBROUTINES;
	}utype_of_entity;
	struct entity * next;
}ENTITY;
typedef struct scope
{
	int scope_offset;
	int nestingLevel;
	ENTITY * entities;
	struct scope * enclosingScope;
}SCOPE;


	/*==================global gia pinaka sumvolwn ============== */
ENTITY * fpars ;
ENTITY * entity_list = NULL;
SCOPE * scope_list = NULL;
int nestingLevel = 0;


ENTITY * insert_entity(char * name,int type,int type_of_subroutine,int start_quad,int type_of_parameter,SCOPE * list_scope);
ARGUMENT * insert_parameter (ARGUMENT * argum,char * name,int offset,int parmode);
void insert_scope (int offset, int nestingLevel);
void delete_scope();
void search_var (SCOPE * sco);
void display_array(SCOPE * sco);

/*================================synartiseis gia pinaka simvolon======================================*/

ENTITY * insert_entity(char * name,int type,int type_of_subroutine,int start_quad,int type_of_parameter,SCOPE * list_scope)
{
	ENTITY * enti, *enti2;
	enti = (ENTITY*)malloc(sizeof(ENTITY));

	strcpy(enti->name_of_entity,name);
	enti->type_of_entity = type;

	switch(type)
	{
		case 1:		//Periptosi Metavlitis
			enti->utype_of_entity.VAR.offset = list_scope->scope_offset;
			list_scope->scope_offset += 4;
			break;
		case 2:		//Periptosi topikis metavlitis
			enti->utype_of_entity.TEMPVAR.offset = list_scope->scope_offset;
			list_scope->scope_offset += 4;
			break;
		case 3:		//Periptosi parametrou
			enti->utype_of_entity.PARAMETER.offset = list_scope->scope_offset;
			enti->utype_of_entity.PARAMETER.type = type_of_parameter;
			list_scope->scope_offset += 4;
			break;
		case 4:
			enti->utype_of_entity.SUBROUTINES.type = type_of_subroutine;
			enti->utype_of_entity.SUBROUTINES.nestingLevel = list_scope->nestingLevel;
			enti->utype_of_entity.SUBROUTINES.frame_length = list_scope->scope_offset;
			enti->utype_of_entity.SUBROUTINES.start_quad = start_quad;
			enti->utype_of_entity.SUBROUTINES.list = NULL;
			fpars = enti;
			break;
		default:
			printf("ERROR: Incorect Insert\n");
			break;
	}
	enti->next = NULL;

	if(list_scope->entities != NULL)
	{
		enti2 = list_scope->entities;
		while(enti2->next != NULL)
		{
			enti2 = enti2->next;
		}
		enti2->next = enti;
		return (list_scope->entities);
	}
	else
	{
		return (enti);
	}
}

ARGUMENT * insert_parameter (ARGUMENT * argum,char * name,int offset,int parmode)
{
	ARGUMENT * arg, * arg2;

	arg = (ARGUMENT*)malloc(sizeof(ARGUMENT));

	strcpy(arg->name_of_arg,name);
	arg->offset = offset;
	arg->parmode = parmode;
	arg->next = NULL;

	if(argum != NULL)
	{
		arg2 = argum;
		while(arg2->next != NULL)
		{
			arg2 = arg2->next;
		}
		arg2->next = arg;
		return (arg2);
	}
	else
	{
		return (arg);
	}
}

void insert_scope (int offset, int nestingLevel)
{
	SCOPE * sco;
	sco = (SCOPE*)malloc(sizeof(SCOPE));

	sco->scope_offset = offset;
	sco->nestingLevel = nestingLevel;
	sco->enclosingScope = NULL;
	sco->entities = NULL;

	if(scope_list == NULL)
	{
		scope_list = sco;
	}
	else
	{
		sco->enclosingScope = scope_list;
		scope_list = sco;
	}
}

void delete_scope()
{
	scope_list = scope_list->enclosingScope;
}

void search_var (SCOPE * sco)
{
	ENTITY * enti, * enti2;
	char * name1;
	char * name2;
	name1 = (char*)malloc(30*sizeof(char));
	name2 = (char*)malloc(30*sizeof(char));

	enti = sco->entities;

	while(enti!=NULL)
	{
		strcpy(name1,enti->name_of_entity);
		enti2 = enti->next;

		while(enti2!=NULL)
		{
			strcpy(name2,enti2->name_of_entity);

			if(strcmp(name1,name2) == 0)
			{
				printf("ERROR: Previous declaration of %s \n", name1);
				exit (1);
			}
			enti2 = enti2->next;
		}
		enti = enti->next;
	}
}

void display_array(SCOPE * sco)
{
	SCOPE *sco1;
	ENTITY *enti;
	ARGUMENT *arg = NULL;

	sco1 = sco;
	while(sco1 != NULL)
	{
		printf("(%d)->", sco1->nestingLevel);

		enti = sco1->entities;

		while(enti != NULL)
		{
			printf("[%s-", enti->name_of_entity);
			if(enti->type_of_entity == 1)		//Metavliti
			{
				printf("%d]", enti->utype_of_entity.VAR.offset);
			}
			else if(enti->type_of_entity == 2)	//Topiki metavliti
			{
				printf("%d]", enti->utype_of_entity.TEMPVAR.offset);
			}
			else if(enti->type_of_entity == 3)	//Parametros
			{
				printf("%d-", enti->utype_of_entity.PARAMETER.offset);
				if(enti->utype_of_entity.PARAMETER.type == 0)
				{
					printf("IN]");
				}
				else
				{
					printf("INOUT]");
				}
			}
			else if(enti->type_of_entity == 4)	//SUBROUTINES
			{
				arg = enti->utype_of_entity.SUBROUTINES.list;
				if(enti->utype_of_entity.SUBROUTINES.type == 0)
				{
					printf("FUNCTION-");
				}
				else
				{
					printf("PROCEDURE-");
				}
				printf("%d-%d]",enti->utype_of_entity.SUBROUTINES.start_quad,enti->utype_of_entity.SUBROUTINES.frame_length);
				printf("--(");

				while(arg!=NULL)
				{
					printf("<%s-%d-%d> ",arg->name_of_arg,arg->offset,arg->parmode);
					arg = arg->next;
				}
				printf(")");
			}
			enti = enti->next;
		}
		sco1 = sco1->enclosingScope;
		printf("\n");
	}
	printf("\n");
}




/*================================================= Lexical analyzer ==========================================================*/






int lex(){

   // char num[30];
    char buff[30] ;
    char temp [9];
    char c  ; int i=0 ;

while ((c = fgetc(input)) != EOF){


for(i=0;i<30;i++){
    buff[i] = '\0';
}
for(i=0;i<30;i++)
{
    num[i] = '\0';
}


    i = 0 ;
    //counter gia grammes
        if (c == '\n') line ++;


   //gia gramma
        if (isalpha(c)){
            int t ;

            buff[i] = c ;
            i++;

             while((c = fgetc(input)) != EOF ){
                   if (!isspace(c)){
                        buff[i] = c;
                        i++;
                   }
                    if (  !isalpha(c) && ! isdigit(c)  ){

                        ungetc(c , input);


                        t = findword(buff);
                        for(i=0;i<30;i++)
                        {
                            buff[i] = '\0';
                        }



                        return t;
                        break ;
                    }

             }
             if (c == EOF){
                 return findword(buff);

             }

        }
    //gia psifio
        if (isdigit(c)){

            num[i] = c ;
            i++;
            while ((c = fgetc(input)) != EOF){
                if (!isdigit(c)){
                    fseek(input, -1, SEEK_CUR);
                    return numID ;

                    break;
                }
                num[i] = c ;
                i++;

            }
            puts(num);
        }

    //gia alla symvola
    if (c == '+'){return  plusID;}

    if (c == '-' ){return minusID;}

    if (c == '*'){return  starID ;}



    if (c == '='){ return equalID;}

    if (c == '}'){return cagisID;}

    if (c== '{') {return oagisID ;}




    //gia sxolia
    if (c == '/'){

       c = fgetc(input);
       if (c == '*'){

            while(1){
                c = fgetc(input);
                if( c == EOF ) {
                    printf("Error at line %d : EOF came and the comments were open \n", line);
                    exit (0);
				    break;
                }
                if (c == '*'){
                      c = fgetc(input);
                        if(c == '/'){
                            c = fgetc(input);
                            break ;
                        }

                }
            }
        }
        else {
            fseek(input, -1, SEEK_CUR);
            return slasID ;
        }
    }

	// gia <=
	if (c == '<'){
		c= fgetc(input);
		if (c == '='){return smeqID;}
		if (c == '>'){return diffID;}
		else{
			fseek (input , -1 , SEEK_CUR);
			return smallID ;
		}
	}

	//gia >=
	if (c == '>'){
		c= fgetc(input);
		if (c == '='){return bieqID;}

		else{
			fseek (input , -1 , SEEK_CUR);

			return bigID ;

		}
	}

	// gia :=
	if (c == ':'){
		c = fgetc(input);
		if (c == '='){return assignID;}
		else{
			printf("Error at line %d Unexpected character after the ':' \n" , line);
			exit (0) ;
		}
	}


	//ypolipa
    if (c == '}'){
        printf("Error at line %d :Unexpected character '}' \n", line);
        exit(0);
    }



    if (c == ','){return commaID;}

	if (c == '(') {return oparID;}

	if (c == ')') {;return cparID;}

    if (c == ';'){return quesID;}

     if (c == '['){return oagilID;}

      if (c == ']'){return cagilID;}

    if (!isspace(c)){
        printf ("Error unepected character \n");
        return falsecharID ;
    }

   }

}

/*========================================== Syntax analyzer and Intermediate Code ========================================*/



// <PROGRAM> = program id <BLOCK>
void program()
{
    char name[30] ;
	if (token == programID){
		token = lex() ;
        if (token == wordID ){
            strcpy(name , id) ;
			token = lex();

                genquad(&list_quad,"Begin_of Programm",name,"_","_");

                strcpy(name_of_program,name);
				insert_scope(0,nestingLevel);
				nestingLevel++;

			block() ;

                search_var(scope_list);
				display_array(scope_list);
				delete_scope();


                genquad(&list_quad,"End_of_programm",name,"_","_");
		}
		else{
			printf("Error at line %d : Program name expected \n", line);
			exit (0) ;
		}
	}
	else{
		printf("Error at line %d : The keyword program expected \n", line);
		exit(0);
	}

}

void block()
{

	if (token == oagisID){
	    token = lex();
		//while ( token == varID){
			declarations();
		//}
		subprograms() ;
		sequence() ;


		if (token == cagisID ){
			token = lex() ;

		}
		else{
			printf("Error at line %d : } character expected \n", line);
			exit (0) ;
		}
	}
	else {
		printf("Error at line %d : { character expected \n", line);
		exit (0) ;
	}


}

void declarations()
{

	if (token == varID){
       		 token = lex();
	
		varlist();


		if(token == quesID){
			token = lex() ;
		}
		else{
			printf("Error at line %d : Expected the symbol';'  \n", line);
			exit (0) ;
		}
	
	}

}

void varlist()
{
	char * value ;
	value = (char*)malloc(30*sizeof(char));

	if (token == wordID){
       // genquad(&list_quad,"Var",id,"_","_");


        strcpy(value , id);
        scope_list->entities = insert_entity(value,1,-2,-2,-2,scope_list);



		token = lex();

        while ( token == commaID){
			token  = lex();
			if (token == wordID){
                   // genquad(&list_quad,"Var",id,"_","_");

                    strcpy(value , id);
                    scope_list->entities = insert_entity(value,1,-2,-2,-2,scope_list);

                    token = lex();
			}
			else{
				printf("Error at line %d : Expected to find an ID \n", line);
				exit (0) ;
			}
		}
	}

}

void subprograms()
{

	while (token == procedureID || token == functionID){

		func();

	}
}

void func()
{

if ( token == procedureID){
	token = lex();
	if (token == wordID ){
        char namef[30] ;

        strcpy( namef , id );

        scope_list->entities = insert_entity(namef,4,1,number_of_quads,-2,scope_list);
        insert_scope(0,nestingLevel);
        nestingLevel++;

		token = lex();
        genquad(&list_quad,"Begin_Block",namef,"_","_");

		funcbody() ;
        genquad(&list_quad,"End_Block",namef,"_","_");

        search_var(scope_list);
        display_array(scope_list);
        delete_scope();
        nestingLevel--;

	}
	else{
		printf("Error at line %d : Expected an ID \n", line);
		exit (0) ;
	}
}
else if (token == functionID){
    token = lex();
    if (token == wordID ){
        char namef[30] ;

        strcpy( namef , id );

        scope_list->entities = insert_entity(namef,4,0,number_of_quads,-2,scope_list);
        insert_scope(0,nestingLevel);
        nestingLevel++;

		token = lex();
        genquad(&list_quad,"Begin_Block",namef,"_","_");

		funcbody() ;
        genquad(&list_quad,"End_Block",namef,"_","_");

        search_var(scope_list);
        display_array(scope_list);
        delete_scope();
        nestingLevel--;

	}
	else{
		printf("Error at line %d : Expected an ID \n", line);
		exit (0) ;
	}
}

}

void funcbody()
{
	formalpars() ;

	block() ;

}



void formalpars()
{
	if( token == oparID ){
		token = lex();
		formalparlist() ;

		if ( token == cparID ){
			token = lex() ;
		}
		else{
			printf("Error at line %d : Expected ) character \n", line);
			exit (0) ;
		}
	}
}

void formalparlist()
{
		formalparitem();
		while ( token == commaID ){
			token = lex();
			formalparitem() ;
		}
}

void formalparitem()
{
	int offset ;
	char * value ;
	value = (char*)malloc(30*sizeof(char));
    char types[30];
    if(token == inID){ strcpy(types , "CV");}
    if(token == inoutID) { strcpy(types , "RET");}
    if(token == copyID) { strcpy(types , "REF");}


	if (token == inID ){

		token = lex();
		if (token == wordID){
            genquad(&list_quad,"Par",id,types,"_");

            strcpy(value , id);

            scope_list->entities = insert_entity(value,3,-2,-2,0,scope_list);
			offset=scope_list->entities->utype_of_entity.PARAMETER.offset;
			fpars->utype_of_entity.SUBROUTINES.list = insert_parameter(fpars->utype_of_entity.SUBROUTINES.list,value,offset,0);

            token = lex();
		}
		else{
			printf("Error at line %d : Expected to find an ID \n", line);
			exit (0) ;
		}
	}
	else if (token == inoutID || token == copyID){
        token = lex();
		if (token == wordID){
            genquad(&list_quad,"Par",id,types,"_");

            strcpy(value , id);

            scope_list->entities = insert_entity(value,3,-2,-2,1,scope_list);
			offset=scope_list->entities->utype_of_entity.PARAMETER.offset;
			fpars->utype_of_entity.SUBROUTINES.list = insert_parameter(fpars->utype_of_entity.SUBROUTINES.list,value,offset,1);

            token = lex();
		}
		else{
			printf("Error at line %d : Expected to find an ID \n", line);
			exit (0) ;
        }
	}
	else{
		printf("Error at line %d : Expected to find the keywords 'in' or 'inout' or 'copy' \n", line);
		exit (0) ;
	}

}

void sequence()
{

	statement();
	while (token == quesID){
		token = lex();
		statement() ; char buff[30] ;

	}

}

void brackets_seq()
{

	if ( token == oagisID) {
		token = lex();

		sequence();
		if (token == cagisID) {

			token = lex() ;
		}

		else{
			printf("Error at line %d : Expected '}' character  \n", line);
			exit (0) ;
		}
	}
	else{
		printf("Error at line %d : Expected '{' character \n", line);
		exit (0) ;
	}

}

void brack_or_stat()
{

	if(token == oagisID){

		brackets_seq();
	}
	else{
		statement();
	}
}

void statement()
{



	if (token == wordID){
		assigment_stat();

	}
	if (token == ifID){
		token = lex();
		if_stat();

        if(exit_if != NULL){
            int x ;
            x = nextquad();                             
            backpatch(exit_if ,&list_quad ,x );
            free(exit_if);
            exit_if = (PTR_LABEL*)malloc(sizeof(PTR_LABEL));
            exit_if = emptylist(exit_if);

        }


	}
	if (token ==  whileID){
		token = lex();
		while_stat();

		     if ( exit_while != NULL){
                int x ;
                x = nextquad();
                backpatch(exit_while ,&list_quad ,x );
                free(exit_while);
                exit_while = (PTR_LABEL*)malloc(sizeof(PTR_LABEL));
                exit_while = emptylist(exit_while);

        }

	}
	if(token == doID){
		token = lex();
		do_while_stat();

        if ( exit_dowhile != NULL){
            int x ;
            x = nextquad();

            backpatch(exit_dowhile ,&list_quad ,x );
            free(exit_dowhile);
                exit_dowhile = (PTR_LABEL*)malloc(sizeof(PTR_LABEL));
                exit_dowhile = emptylist(exit_dowhile);

        }
	}
	

	if(token == forID){
		token = lex();

		forcase_stat() ;

            if ( exit_for != NULL){
                int x ;
                x = nextquad();
                backpatch(exit_for ,&list_quad ,x );
                free(exit_for);
                exit_for = (PTR_LABEL*)malloc(sizeof(PTR_LABEL));
                exit_for = emptylist(exit_for);

        }

	}
	if(token == callID){
		token = lex();
		call_stat() ;
	}
	if(token == returnID){
		token = lex();
		return_stat() ;
	}
	if(token == printID){
		token = lex();
		print_stat() ;
	}
}

void  assigment_stat()
{
    char * E_place ;
	E_place = (char*)malloc(30*sizeof(char));

	char word_1[30];
	strcpy(word_1 , id);
    token = lex();

    if (token == assignID){
        token = lex();

        expression(E_place);
                    genquad (&list_quad , ":=" , E_place , " " , word_1);
    }
    else{
		printf("Error at line %d : Expected to find ':= ' character \n", line);
		exit (0) ;
	}

}

void if_stat()
{
                                    	PTR_LABEL iflist;
                                        LOGICAL_CONDITION C;
                                        int next1,next2;

    if(token == oparID){
        token = lex();
        condition(&C);
        if (token == cparID){

        	    next1 = nextquad();
				token = lex();
                                    where = 1;

				brack_or_stat();

				int x ;
				x = nextquad();
				makelist(x,&iflist);
				genquad(&list_quad,"jump","_","_","_");
				next2 = nextquad();

				else_part();
				backpatch(&(C.mytrue), &list_quad,next1);
				backpatch(&(C.myfalse), &list_quad,next2);
				backpatch(&iflist, &list_quad,nextquad());

        }
        else{
		printf("Error at line %d : Expected ')' character \n", line);
		exit (0) ;
        }
    }
    else{
		printf("Error at line %d : Expected '(' character \n", line);
		exit (0) ;
	}

}

void else_part()
{
    if (token == elseID){
        token = lex();
        brack_or_stat();

    }
}
void do_while_stat()
{
                             PTR_LABEL dowhilelist ;
                             LOGICAL_CONDITION C ;
                             int next1;
                             int next2 ;
                             int next3 ;

                             next1 = nextquad() ;
                             char next [30];
                             sprintf(next,"%d" ,next1);
    where = 2 ;
    brack_or_stat();
if(token == whileID){
    token = lex() ;
    if(token == oparID){
        token = lex();
        condition(&C);

        backpatch(&(C.myfalse), &list_quad, nextquad());
        backpatch(&(C.mytrue), &list_quad, next1);

        if (token == cparID){

            token = lex();
        }
        else{
		printf("Error at line %d : Expected ')' character \n", line);
		exit (0) ;
        }
    }
    else{
		printf("Error at line %d : Expected '(' character \n", line);
		exit (0) ;
	}
}
else{
    printf("Error at line %d : Expected to find the keyword 'while' \n", line);
    exit (0) ;
   }

}




void return_stat()
{
                                                char * E_place ;
                                                E_place = (char *) malloc (30 * sizeof(char));

    if(token == oparID){
        token = lex();
        expression(E_place);
        if (token == cparID){
            genquad(&list_quad , "retv" , E_place , "_" , "_") ;
            token = lex();
        }
        else{
            printf("Error at line %d : Expected ')' character \n", line);
            exit (0) ;
        }
    }
    else{
		printf("Error at line %d : Expected '(' character \n", line);
		exit (0) ;
	}

}

void print_stat()
{
                                            char * E_place ;
                                            E_place = (char *) malloc (30 * sizeof(char));
    if(token == oparID){
        token = lex();
        expression(E_place);

        if (token == cparID){
            token = lex();
            genquad(&list_quad, "out" , E_place , "_" , "_");

        }
        else{
            printf("Error at line %d : Expected ')' character \n", line);
            exit (0) ;
        }
    }
    else{
		printf("Error at line %d : Expected '(' character \n", line);
		exit (0) ;
	}

}

void while_stat()
{
                                                    PTR_LABEL whilelist ;
                                                    LOGICAL_CONDITION C ;
                                                    int next1;
                                                    char * next ;
                                                    next = (char * ) malloc(30 * sizeof(char));


    if(token == oparID){
        token = lex();

        next1 = nextquad();
        sprintf(next , "%d" , next1);

        condition(&C);

        if (token == cparID){
            token = lex();

            backpatch(&(C.mytrue) ,&list_quad , nextquad());

            where = 4 ;

            brack_or_stat();

            genquad(&list_quad , "jump" , "_" , "_", next);
            backpatch(&(C.myfalse) ,&list_quad , nextquad());

        }
        else{
		printf("Error at line %d : Expected ')' character \n", line);
		exit (0) ;
        }
    }
    else{
		printf("Error at line %d : Expected '(' character \n", line);
		exit (0) ;
	}

}

void forcase_stat()
{
                                                        PTR_LABEL forcaselist ;
                                                        LOGICAL_CONDITION C ;
                                                        int next1;

    if(token == oparID){
        token = lex();
                                                        int next1 = nextquad();
                                                        char next [30];
                                                        sprintf(next,"%d" ,next1);

        condition(&C);
        if (token == cparID){
            token = lex();

            backpatch(&(C.mytrue), &list_quad, nextquad());

            where = 3 ;

            brack_or_stat();

            genquad(& list_quad , "jump" , "_" , "_",next);
            backpatch(&(C.myfalse) ,&list_quad , nextquad());

        }
        else{
		printf("Error at line %d : Expected ')' character \n", line);
		exit (0) ;
        }
    }
    else{
		printf("Error at line %d : Expected '(' character \n", line);
		exit (0) ;
	}
}
void call_stat()
{
                            char * type_of_call;
                            char * ident;
                            type_of_call = (char*)malloc(30*sizeof(char));
                            ident = (char*)malloc(30*sizeof(char));

        strcpy(type_of_call,"call");

		if(token == wordID)
		{
			strcpy(ident,id);
			token = lex();
			actualpars(ident,type_of_call);
		}
		else
		{
			printf("Error at line %d : Expected the name of a fuction/procedure \n", line);
			exit(1);
		}

}

 void id_tail(char * act)
{
	char * call_way;
	call_way = (char*)malloc(30*sizeof(char));

	strcpy(call_way,"idtail");
	if(token == oparID)
	{
		actualpars(act,call_way);
	}
}

void actualpars(char * ident, char * calls_way)
{

    if(token == oparID){
        token = lex();
        actualparlist();

        if (token == cparID){
            token = lex();


            genquad(&list_quad,"call","_","_",ident);

        }
        else{
		printf("Error at line %d : Expected ')' character \n", line);
		exit (0) ;
        }
    }

}

void actualparlist()
{
    actualparitem();

    while (token == commaID){
        token = lex();
        actualparitem();
    }
}

void actualparitem ()
{
                                    char * E_place ;
                                    E_place = (char *)malloc(30*sizeof(char));
    if (token == inID){

        expression(E_place);
        genquad(&list_quad,"par",E_place,"CV","_");
    }


    if((token == inoutID) || (token == copyID)){
        token = lex();
        if(token == wordID){
            char * ace ;
            ace = (char *)malloc(30*sizeof(char));
            strcpy (ace, id);
            genquad(&list_quad,"par",ace,"REF","_");
            token = lex();
        }
        else{
		printf("Error at line %d : Expected to find an ID \n", line);
		exit (0) ;
        }

    }
    else{
		printf("Error at line %d : Expected to find 'inout' or 'copy' keyword \n", line);
		exit (0) ;
        }
}

void condition(LOGICAL_CONDITION * C)
{
                                        PTR_LABEL * mylabel ;
                                        mylabel = (PTR_LABEL*)malloc(sizeof(PTR_LABEL));
                                        LOGICAL_CONDITION Bt1;
                                        LOGICAL_CONDITION Bt2 ;
                                        int next ;

    boolterm(&Bt1);
    C->mytrue = Bt1.mytrue;
    C->myfalse = Bt1.myfalse;

    while(token == orID){
        token = lex();
        next = nextquad();

        boolterm(&Bt2);
        backpatch(&(C->myfalse), &list_quad, next);
        C->myfalse = Bt2.myfalse;
        mylabel = mergelist(&(C->mytrue),&(Bt2.mytrue));
        C->mytrue = *(mylabel);
    }
}


void boolterm(LOGICAL_CONDITION * Bt)
{
                                    PTR_LABEL * mylabel;
                                    int next;
                                    LOGICAL_CONDITION Bf1,Bf2;
                                    mylabel = (PTR_LABEL *)malloc(sizeof(PTR_LABEL));

    boolfactor(&Bf1);
    Bt->mytrue = Bf1.mytrue;
    Bt->myfalse = Bf1.myfalse;

    while(token == andID){
        token = lex();

        next = nextquad();
        boolfactor(&Bf2);

        backpatch(&(Bt->mytrue), &list_quad, next);
        Bt->mytrue = Bf2.mytrue;
        mylabel = mergelist(&(Bt->myfalse),&(Bf2.myfalse));
        Bt->myfalse = *(mylabel);
    }
}

void boolfactor(LOGICAL_CONDITION * Bf)
{
                                     char * E1_place ;
                                     char* E2_place ;
                                     char * E_place ;
                                     E1_place = (char*)malloc(30*sizeof(char));
                                     E_place = (char*)malloc(30*sizeof(char));
                                     E2_place = (char*)malloc(30*sizeof(char));
                                     LOGICAL_CONDITION Bl ;
                                     int next1 ;
                                     int next2 ;

    if(token == notID){
        token = lex();

        Bf->mytrue = Bl.myfalse;
        Bf->myfalse = Bl.mytrue;

        if(token == oagilID){
            token = lex();
            condition(Bf);
            if (token == cagilID){
                token = lex();

            }
            else{
                printf("Error at line %d : Expected to find ']' character \n", line);
                exit (0) ;
            }
        }
        else{
            printf("Error at line %d : Expected to find '[' character \n", line);
            exit (0) ;
        }
    }
    else if (token == oagilID){

            token = lex();
                                		Bf->mytrue = Bl.mytrue;
                                        Bf->myfalse = Bl.myfalse;
            condition(Bf);
            if (token == cagilID){

                token = lex();
            }
            else{
                printf("Error at line %d : Expected to find ']' character \n", line);
                exit (0) ;
            }
        }
    else{

        expression(E_place);
        strcpy(E1_place , E_place) ;

        relational_oper();

        expression(E_place);

        strcpy(E2_place , E_place) ;
        next1 = nextquad();
        makelist(next1,&(Bf->mytrue));
        genquad(&list_quad,relop,E1_place,E2_place,"_");

        next2 = nextquad();
        makelist(next2,&(Bf->myfalse));
        genquad(&list_quad,"jump","_","_","_");

    }


}


void expression(char * E_place)
{

                            char * w ;
                            char * T1_place ;
                            char * T2_place ;
                            char * T_place;
                            w = (char*)malloc(30*sizeof(char));
                            T1_place = (char*)malloc(30*sizeof(char));
                            T2_place = (char*)malloc(30*sizeof(char));
                            T_place = (char*)malloc(30*sizeof(char));

    optional_sign();


    term(T_place);
    strcpy( T1_place , T_place );

    while(token == plusID ||  token == minusID){
        add_oper();

        w = newtemp();
        scope_list->entities = insert_entity(w,2,-2,-2,-2,scope_list);

        term(T_place);
        strcpy(T2_place ,T_place) ;
        genquad(&list_quad , addoper , T1_place , T2_place , w);
        strcpy(T1_place ,w) ;

    }
    strcpy(E_place ,T1_place) ;
}

void term(char * T_place)
{
                            char * w ;
                            char * F1_place ;
                            char * F2_place ;
                            char * F_place ;
                            w = (char*)malloc(30*sizeof(char));
                            F1_place = (char*)malloc(30*sizeof(char));
                            F2_place = (char*)malloc(30*sizeof(char));
                            F_place = (char*)malloc(30*sizeof(char));

    factor(F_place);
    strcpy(F1_place,F_place);

    while(token == starID || token == slasID){

        w = newtemp();

        mul_oper();
        factor(F_place);

        scope_list->entities = insert_entity(w,2,-2,-2,-2,scope_list);

        strcpy(F2_place,F_place);

        genquad(&list_quad , muloper , F1_place , F2_place , w);
       strcpy(F1_place, w) ;

    }
    strcpy(T_place , F1_place) ;
}

void factor(char * F_place)
{

                            char *iden;
                            iden = (char *) malloc (30 * sizeof (char));

    if(token ==  oparID){
        token = lex();
        expression(F_place);
        if(token == cparID){
            token = lex();
        }
        else{
            printf("Error at line %d : Expected to find ')' character \n", line);
            exit (0) ;
        }

    }
    else if(token == wordID){


        strcpy(iden , id);
        strcpy(F_place , iden );

        token = lex();
        id_tail(iden);
    }
    else if (token == numID){

        strcpy(F_place , num) ;
        token = lex();

    }

}
void relational_oper()
{

    if (token == equalID ){
        strcpy(relop , "=");
        token = lex();
    }
    else if (token == bigID){
        strcpy(relop , ">");
        token = lex();
    }
    else if ( token == smeqID){
            strcpy(relop , "<=");
            token = lex();
    }
    else if (token == diffID ){
       strcpy(relop , "<>");
        token = lex();
    }
    else if (token == bieqID ){
        strcpy(relop , ">=");
        token = lex();
    }
    else if (token == smallID ){
        strcpy(relop , "<");
        token = lex();
    }
    else {
                printf("Error at line %d : Unexpected character. Expected to find an relational operator   \n", line);
                exit (0) ;
    }
}

void mul_oper()
{
    if (token == starID){
        strcpy(muloper , "*");
        token = lex();

    }
    else if (token == slasID){
        strcpy(muloper , "/");
        token = lex();
    }
    else{
                printf("Error at line %d : Unexpected character \n", line);
                exit (0) ;
    }
}

void add_oper()
{
    if (token == plusID){
        strcpy(addoper , "+");
        token = lex();
    }
    else if (token == minusID){
        strcpy(addoper , "-");
        token = lex();
    }
    else{
                printf("Error at line %d : Unexpected character \n", line);
                exit (0) ;
    }
}

void optional_sign()
{

   if (token == plusID || token == minusID){
       add_oper();
    }


}



////////////////////////////////////////////////////// main function ///////////////////////////////////////////////

int main (){

    ////// anathesi arxikon timon /////

    name_of_program = (char*) malloc (30 * sizeof(char));
	name_of_procedure = (char*) malloc (30 * sizeof(char));
	name_of_function = (char*) malloc (30 * sizeof(char));

    exit_if = (PTR_LABEL*)malloc(sizeof(PTR_LABEL));
    exit_if = emptylist(exit_if);
    exit_for = (PTR_LABEL*)malloc(sizeof(PTR_LABEL));
    exit_for = emptylist(exit_for);
    exit_dowhile = (PTR_LABEL*)malloc(sizeof(PTR_LABEL));
    exit_dowhile = emptylist(exit_dowhile);
    exit_while = (PTR_LABEL*)malloc(sizeof(PTR_LABEL));
    exit_while = emptylist(exit_while);

	QUAD * myquad;
	myquad = (QUAD*)malloc(sizeof(QUAD));
	list_quad.head = NULL;
	list_quad.tail = NULL;
    line = 1 ; token = 0 ;

    where = 0;


    /////////////////anigma arxeiou////////////////

    int i; int id;
    input = fopen("data2.txt", "r");
    if (input == NULL){
           printf(" File cant be found \n") ;
           perror("data.txt");
		   exit (0) ;
    }

    //////////////////////////////////////////////

  	token = lex();
	program();

    //////////// print gia tetrades/////////////

    printf("\n");
    printf("\n");
    printf("OI TETRADES POU DIMIOURGOUNTAI EINAI: \n");
	for(myquad = list_quad.head; myquad!=NULL; myquad = myquad->next)
	{
		printf("\t%d\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t\n", myquad->num, myquad->op, myquad->op1, myquad->op2, myquad->op3);
	}

    ///////////////////////////////////////////

	fclose ( input );
    return 0 ;
}





