%include {
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "parser.h"

#include "utils/strht.h"
#include "utils/superfasthash.h"


typedef enum {UNDEFINED, STRING, NUMBER} token__t;
typedef union {void* nil; char* string; double number;} token__v;
typedef struct {
    char* s; /* text of token */
    size_t n; /* size of token text */

    token__t t; /* type of token value*/
    token__v v; /* token value */
} Token;

void token_destroy(Token* t)
{
	if (t != NULL) {
		free(t->s);
		if (t->t == STRING) {
			free (t->v.string);
		}
	}
	free(t);
	t = NULL;
}


}

%extra_argument { hashtab_t* SYM_T } /* points to the global symbol table */

%token_type {Token*}
%token_destructor { token_destroy($$); }

%type expr {double}

%left PLUS MINUS.
%left DIVIDE TIMES MODULO.
%left POWER.


%syntax_error {
  printf("Syntax error.\n");
}

program ::= expr(A). { printf("%g\n", A); }
program ::= IDENTIFIER(A) EQUAL expr(B). {

	/* insert into global symbol table */
	A->t = NUMBER;
	A->v.number = B;
	ht_insert(SYM_T, A->s, A->n, A, sizeof(Token)); /* TODO check for non null */
	/*printf ("Initialization found for variable %s with value %g in %d\n", A->s, A->v.number, (int) SYM_T);*/
	
    token_destroy(A);
}
program ::= . { /* empty lines */ }

expr(A) ::= OPENP expr(B) CLOSEP. { A = (B); }
expr(A) ::= expr(B) POWER expr(C). { 
	double res = 1;
	int i;
	for (i = 0; i < (int) (C + 0.5f); i++) 
	{
		res *= B; 
	}
	A = res;
}
expr(A) ::= expr(B) MODULO expr(C). {
	A = (double)((int) fabs(B + 0.5f) % (int) fabs(C + 0.5f));
}
expr(A) ::= expr(B) PLUS expr(C). { A = B + C; }
expr(A) ::= expr(B) DIVIDE expr(C). { A = B / C; }
expr(A) ::= expr(B) TIMES expr(C). { A = B * C; }
expr(A) ::= expr(B) MINUS expr(C). { A = B - C; }
expr(A) ::= MINUS expr(B). { A = -(B); }
expr(A) ::= PLUS expr(B). { A = B; }
expr(A) ::= DOUBLE(B). { A = B->v.number; token_destroy(B); }
expr(A) ::= IDENTIFIER(B). {

	/* lookup in global symbol table */
	/*printf ("Looking up %s in symbol table %d\n", B->s, (int)SYM_T);*/
	void* lookup = ht_search(SYM_T, B->s, B->n);
	if (lookup != NULL && ((Token*) lookup)->t == NUMBER) 
	{
		B->t = NUMBER;
		B->v.number = ((Token*) lookup)->v.number;
	}

	if (B->t == UNDEFINED)
	{
		printf("DJINN> Undefined variable: %s\n", B->s);
		A = 0; /* using 0 as a "safe" value */
	}
	else if (B->t == NUMBER) { 
		A = B->v.number;
	}
	else
		printf("Bad type for variable %s, expected double.\n", B->s); 
	token_destroy(B);
}

