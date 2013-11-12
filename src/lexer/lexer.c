
#line 1 "src/lexer/lexer.rl"

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



#line 126 "src/lexer/lexer.rl"



#line 2 "src/lexer/lexer.c"
static const char _djinn_lexer_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 1, 4, 1, 5, 1, 6, 1, 
	7, 1, 8, 1, 9, 1, 10, 1, 
	11, 1, 12, 1, 13, 1, 14, 1, 
	15, 1, 16, 1, 17
};

static const char _djinn_lexer_key_offsets[] = {
	0, 0, 1, 3, 24, 25, 33, 35
};

static const char _djinn_lexer_trans_keys[] = {
	10, 48, 57, 10, 32, 35, 37, 40, 
	41, 42, 43, 45, 47, 59, 61, 95, 
	9, 13, 48, 57, 65, 90, 97, 122, 
	42, 46, 95, 48, 57, 65, 90, 97, 
	122, 48, 57, 95, 48, 57, 65, 90, 
	97, 122, 0
};

static const char _djinn_lexer_single_lengths[] = {
	0, 1, 0, 13, 1, 2, 0, 1
};

static const char _djinn_lexer_range_lengths[] = {
	0, 0, 1, 4, 0, 3, 1, 3
};

static const char _djinn_lexer_index_offsets[] = {
	0, 0, 2, 4, 22, 24, 30, 32
};

static const char _djinn_lexer_trans_targs[] = {
	3, 1, 6, 3, 3, 3, 1, 3, 
	3, 3, 4, 3, 3, 3, 3, 3, 
	7, 3, 5, 7, 7, 0, 3, 3, 
	2, 7, 5, 7, 7, 3, 6, 3, 
	7, 7, 7, 7, 3, 3, 3, 3, 
	3, 3, 0
};

static const char _djinn_lexer_trans_actions[] = {
	27, 0, 0, 35, 23, 25, 0, 11, 
	17, 19, 0, 13, 15, 21, 23, 7, 
	0, 25, 5, 0, 0, 0, 9, 31, 
	0, 0, 5, 0, 0, 29, 0, 29, 
	0, 0, 0, 0, 33, 35, 31, 29, 
	29, 33, 0
};

static const char _djinn_lexer_to_state_actions[] = {
	0, 0, 0, 1, 0, 0, 0, 0
};

static const char _djinn_lexer_from_state_actions[] = {
	0, 0, 0, 3, 0, 0, 0, 0
};

static const char _djinn_lexer_eof_trans[] = {
	0, 0, 38, 0, 39, 41, 41, 42
};

static const int djinn_lexer_start = 3;
static const int djinn_lexer_first_final = 3;
static const int djinn_lexer_error = 0;

static const int djinn_lexer_en_main = 3;


#line 129 "src/lexer/lexer.rl"

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

    
#line 71 "src/lexer/lexer.c"
	{
	cs = djinn_lexer_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 162 "src/lexer/lexer.rl"

    
#line 77 "src/lexer/lexer.c"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const char *_keys;

	if ( p == pe )
		goto _test_eof;
	if ( cs == 0 )
		goto _out;
_resume:
	_acts = _djinn_lexer_actions + _djinn_lexer_from_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 1:
#line 1 "NONE"
	{ts = p;}
	break;
#line 96 "src/lexer/lexer.c"
		}
	}

	_keys = _djinn_lexer_trans_keys + _djinn_lexer_key_offsets[cs];
	_trans = _djinn_lexer_index_offsets[cs];

	_klen = _djinn_lexer_single_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _djinn_lexer_range_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
_eof_trans:
	cs = _djinn_lexer_trans_targs[_trans];

	if ( _djinn_lexer_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _djinn_lexer_actions + _djinn_lexer_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 2:
#line 1 "NONE"
	{te = p+1;}
	break;
	case 3:
#line 90 "src/lexer/lexer.rl"
	{te = p+1;{
        Parse(lparser, EQUAL, 0, sym_t);
    }}
	break;
	case 4:
#line 52 "src/lexer/lexer.rl"
	{te = p+1;{
        Parse(lparser, POWER, 0, sym_t);
    }}
	break;
	case 5:
#line 56 "src/lexer/lexer.rl"
	{te = p+1;{
        Parse(lparser, MODULO, 0, sym_t);
    }}
	break;
	case 6:
#line 32 "src/lexer/lexer.rl"
	{te = p+1;{
        Parse(lparser, PLUS, 0, sym_t);
    }}
	break;
	case 7:
#line 36 "src/lexer/lexer.rl"
	{te = p+1;{
        Parse(lparser, MINUS, 0, sym_t);
    }}
	break;
	case 8:
#line 48 "src/lexer/lexer.rl"
	{te = p+1;{
        Parse(lparser, OPENP, 0, sym_t);
    }}
	break;
	case 9:
#line 60 "src/lexer/lexer.rl"
	{te = p+1;{
        Parse(lparser, CLOSEP, 0, sym_t);
    }}
	break;
	case 10:
#line 44 "src/lexer/lexer.rl"
	{te = p+1;{
        Parse(lparser, DIVIDE, 0, sym_t);
    }}
	break;
	case 11:
#line 27 "src/lexer/lexer.rl"
	{te = p+1;{
        /* Terminate this calculation. */
        Parse(lparser, 0, 0, sym_t);
    }}
	break;
	case 12:
#line 122 "src/lexer/lexer.rl"
	{te = p+1;}
	break;
	case 13:
#line 27 "src/lexer/lexer.rl"
	{te = p+1;{
        /* Terminate this calculation. */
        Parse(lparser, 0, 0, sym_t);
    }}
	break;
	case 14:
#line 64 "src/lexer/lexer.rl"
	{te = p;p--;{
        char* str = (char*) malloc((te-ts+1) * sizeof(char));
        Token* t = (Token*) malloc(sizeof(Token));

        get_str(ts, te, str);
        t->s = NULL;
        t->n = 0;
        t->t = NUMBER;
        t->v.number = atof(str);

        Parse(lparser, DOUBLE, t, sym_t);
        free(str);
    }}
	break;
	case 15:
#line 40 "src/lexer/lexer.rl"
	{te = p;p--;{
        Parse(lparser, TIMES, 0, sym_t);
    }}
	break;
	case 16:
#line 78 "src/lexer/lexer.rl"
	{te = p;p--;{
        Token* t = (Token*) malloc(sizeof(Token));

        t->s = (char*) malloc((te-ts+1) * sizeof(char));
        t->n = te - ts;
        t->t = UNDEFINED;
        t->v.nil = NULL; 
        get_str(ts, te, t->s);

        Parse(lparser, IDENTIFIER, t, sym_t);
    }}
	break;
	case 17:
#line 64 "src/lexer/lexer.rl"
	{{p = ((te))-1;}{
        char* str = (char*) malloc((te-ts+1) * sizeof(char));
        Token* t = (Token*) malloc(sizeof(Token));

        get_str(ts, te, str);
        t->s = NULL;
        t->n = 0;
        t->t = NUMBER;
        t->v.number = atof(str);

        Parse(lparser, DOUBLE, t, sym_t);
        free(str);
    }}
	break;
#line 266 "src/lexer/lexer.c"
		}
	}

_again:
	_acts = _djinn_lexer_actions + _djinn_lexer_to_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 0:
#line 1 "NONE"
	{ts = 0;}
	break;
#line 277 "src/lexer/lexer.c"
		}
	}

	if ( cs == 0 )
		goto _out;
	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	if ( p == eof )
	{
	if ( _djinn_lexer_eof_trans[cs] > 0 ) {
		_trans = _djinn_lexer_eof_trans[cs] - 1;
		goto _eof_trans;
	}
	}

	_out: {}
	}

#line 164 "src/lexer/lexer.rl"

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

