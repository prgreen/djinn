
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "utils/strht.h"
#include "utils/superfasthash.h"


/* including the parser as a generated file */
#include "../parser/parser.c" 

#define USED(x) ((void)(x))

void get_str(const char* beg, const char* end, char* str)
{
    strncpy(str, beg, end-beg);
    str[end-beg] = '\0';
}


%%{

    machine djinn_lexer;

    action newline_tok {
        /* Terminate this calculation. */
        Parse(lparser, 0, 0, sym_t);
    }

    action plus_tok {
        Parse(lparser, PLUS, 0, sym_t);
    }

    action minus_tok {
        Parse(lparser, MINUS, 0, sym_t);
    }

    action times_tok {
        Parse(lparser, TIMES, 0, sym_t);
    }

    action divide_tok {
        Parse(lparser, DIVIDE, 0, sym_t);
    }

    action openp_tok {
        Parse(lparser, OPENP, 0, sym_t);
    }

    action power_tok {
        Parse(lparser, POWER, 0, sym_t);
    }

    action modulo_tok {
        Parse(lparser, MODULO, 0, sym_t);
    }

    action closep_tok {
        Parse(lparser, CLOSEP, 0, sym_t);
    }

    action number_tok {
        char* str = (char*) malloc((te-ts+1) * sizeof(char));
        Token* t = (Token*) malloc(sizeof(Token));

        get_str(ts, te, str);
        t->s = NULL;
        t->n = 0;
        t->t = NUMBER;
        t->v.number = atof(str);

        Parse(lparser, DOUBLE, t, sym_t);
        free(str);
    }

    action identifier_tok {
        Token* t = (Token*) malloc(sizeof(Token));

        t->s = (char*) malloc((te-ts+1) * sizeof(char));
        t->n = te - ts;
        t->t = UNDEFINED;
        t->v.nil = NULL; 
        get_str(ts, te, t->s);

        Parse(lparser, IDENTIFIER, t, sym_t);
    }

    action equal_tok {
        Parse(lparser, EQUAL, 0, sym_t);
    }

    
    identifier = (alnum | '_')+;
    comment = '#' [^\n]* '\n';
    equal = '=';
    number = [0-9]+('.'[0-9]+)?;
    modulo = '%';
    power = '**';
    plus = '+';
    minus = '-';
    openp = '(';
    closep = ')';
    times = '*';
    divide = '/';
    newline = '\n' | ';';

main := |*
    equal => equal_tok;
    number => number_tok;
    power => power_tok;
    modulo => modulo_tok;
    plus => plus_tok;
    minus => minus_tok;
    openp => openp_tok;
    closep => closep_tok;
    times => times_tok;
    divide => divide_tok;
    newline => newline_tok;
    identifier => identifier_tok;
    space;
    comment => newline_tok;
    *|;

}%%

%% write data;

typedef struct Scan
{
    void* lparser;
} Scan;

void scan_destroy(Scan* s)
{
    ParseFree(s->lparser, free);
}

void scan_init(Scan* s)
{
    s->lparser = ParseAlloc(malloc);
}

void scan_execute(Scan* s, const char* data, size_t len, hashtab_t* h)
{
    hashtab_t* sym_t = h;
    const char* p = data;
    const char* pe = data + len;
    const char* eof = pe;

    int cs;
    int act;
    const char* ts;
    const char* te;

    void* lparser = s->lparser;

    USED(act);

    %% write init;

    %% write exec;

    /* sending additional termination for last lines
    or when parsing empty files */
    Parse(lparser, 0, 0, sym_t);
}



int main(int argc, char **argv)
{
    char* buffer;
    FILE* f;
    Scan scan;
    long numbytes;
    hashtab_t* sym_t = NULL; 

    /* TODO make it grow as necessary */
    sym_t = ht_init(100, ht_fast_hash); 
    

    if (argc == 1)
    {
        printf("\nYou must provide a filename argument.\n\n");
        printf("Djinn Compiler\nCopyright (C) 2012-2013 Grym\n");
    }
    else if (argc >=2)
    {
        /* TODO check for file existence */
        f = fopen(argv[1], "r");
        fseek(f, 0, SEEK_END);
        numbytes = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = (char *) malloc(numbytes * sizeof(char));
        fread(buffer, 1, numbytes, f);


        scan_init(&scan);
        scan_execute(&scan, buffer, numbytes, sym_t);

        scan_destroy(&scan);
        free(buffer);
        fclose(f);
    }

    ht_destroy(sym_t);

    return 0;
}

