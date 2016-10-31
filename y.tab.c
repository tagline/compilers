#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20140101

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)

#define YYPREFIX "yy"

#define YYPURE 0

#line 6 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include "astree.c"
#include "tac.c"


#define   SYMBOL_UNDEFINED		0 
#define   SYMBOL_TK_IDENTIFIER  	1 
#define   SYMBOL_LIT_INTEGER  		2 
#define   SYMBOL_LIT_TRUE   		3 
#define   SYMBOL_LIT_FALSE  		4	 
#define   SYMBOL_LIT_CHAR   		5 
#define   SYMBOL_LIT_STRING  		6 
ASTREE *root=0;

#line 44 "parser.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
	struct hash_node* symbol;
	struct astree_node* astree;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 48 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define KW_INT 257
#define KW_FLOAT 258
#define KW_BOOL 259
#define KW_CHAR 260
#define KW_IF 261
#define KW_THEN 262
#define KW_ELSE 263
#define KW_FOR 264
#define KW_READ 265
#define KW_RETURN 266
#define KW_PRINT 267
#define KW_TO 268
#define OPERATOR_LE 269
#define OPERATOR_GE 270
#define OPERATOR_EQ 271
#define OPERATOR_NE 272
#define OPERATOR_AND 273
#define OPERATOR_OR 274
#define TK_IDENTIFIER 275
#define LIT_INTEGER 276
#define LIT_TRUE 277
#define LIT_FALSE 278
#define LIT_CHAR 279
#define LIT_STRING 280
#define TOKEN_ERROR 281
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    7,    7,    8,    8,    8,    9,   11,   11,   14,
   14,   13,   13,   13,   13,   13,   10,   15,   15,   16,
   16,   12,   12,   12,   12,    1,    3,    3,    2,    2,
    2,    2,    2,    2,    2,    2,    2,    2,    2,   17,
   17,   17,   17,    4,    4,    4,    4,    4,    4,    4,
    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
    4,    4,    4,    4,    5,    5,    6,    6,
};
static const short yylen[] = {                            2,
    1,    2,    1,    2,    2,    2,    4,    5,    7,    2,
    1,    1,    1,    1,    1,    1,    6,    3,    0,    4,
    0,    1,    1,    1,    1,    3,    3,    2,    3,    6,
    6,    8,    5,    9,    2,    2,    2,    1,    0,    2,
    2,    1,    1,    1,    1,    1,    1,    1,    4,    4,
    3,    2,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    2,    0,    3,    0,
};
static const short yydefred[] = {                         0,
   22,   23,   24,   25,    0,    0,    3,    0,    0,    0,
    0,    2,    4,    6,    5,    0,    0,    0,    0,   12,
   15,   16,   13,   14,    7,    0,    0,    0,    0,    0,
    0,    0,    0,   18,    0,   17,   11,    0,    0,    0,
    0,    0,    0,    0,    0,   38,    0,    0,   10,    0,
    0,    0,   36,    0,   45,   46,   47,   48,    0,    0,
    0,    0,    0,   35,    0,    0,   28,   26,    0,   20,
    0,    0,    0,    0,    0,   52,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   40,
   41,    0,    0,   27,    0,    0,    0,    0,    0,    0,
   51,   59,   60,   61,   62,    0,    0,    0,    0,    0,
    0,   57,   58,    0,    0,    0,   33,   49,    0,   65,
   50,    0,    0,    0,    0,    0,    0,    0,   67,   32,
    0,   34,
};
static const short yydgoto[] = {                          5,
   46,   47,   48,   63,  100,  120,    6,    7,    8,    9,
   10,   11,   25,   38,   28,   34,   64,
};
static const short yysindex[] = {                      -217,
    0,    0,    0,    0,    0, -217,    0,  -54,  -52,  -39,
 -253,    0,    0,    0,    0,    9, -138, -138, -217,    0,
    0,    0,    0,    0,    0,  -56, -237,    5,  -11,   15,
  -62, -138, -217,    0,  194,    0,    0, -138, -213,   23,
   25, -206,   46,  -27,  -57,    0,   18,  231,    0,   15,
   46,   66,    0,   -8,    0,    0,    0,    0,   46,   46,
  404,  -27,  -12,    0,   46,   46,    0,    0,   22,    0,
  127,   -4,  134,   46,   46,    0,  141,   46,   46,   46,
   46,   46,   46,   46,   46,   46,   46,   46,   46,    0,
    0,  253,  404,    0, -180,   46,  194,  316,  164,   44,
    0,    0,    0,    0,    0,    6,    6,  410,  410,  209,
  209,    0,    0,   27,  194,  171,    0,    0,   46,    0,
    0,   46, -174,   46,  164,  404,  194,  150,    0,    0,
  194,    0,
};
static const short yyrindex[] = {                         0,
    0,    0,    0,    0,    0,   97,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   60,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   43,   62,
    0,    0,    0,    0,   48,    0,    0,   49,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   48,    0,   62,
    0,    0,    0,  -33,    0,    0,    0,    0,    0,    0,
  -43,  -42,  -41,    0,    0,    0,    0,    0,    0,    0,
    0,  157,    0,    0,   68,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  -40,    0,    0,    0,  -36,    0,   70,    0,
    0,    0,    0,    0,    0,   11,   31,   92,  112,   51,
   72,    0,    0,    0,  -36,    0,    0,    0,    0,    0,
    0,    0,   59,    0,   70,  -35,  -36,    0,    0,    0,
  -36,    0,
};
static const short yygindex[] = {                         0,
   89,   32,    0,  477,    0,   -3,    0,  115,    0,    0,
    0,  -18,    7,    0,    0,   73,  -60,
};
#define YYTABLESIZE 684
static const short yytable[] = {                         44,
   27,   90,   91,   66,   13,   59,   14,   44,   44,   44,
   44,   44,   60,   44,   39,   37,   42,   43,   29,   15,
   59,   16,   39,   30,   26,   44,   44,   60,   44,   86,
   84,   75,   85,   65,   87,   75,   29,   30,   37,    1,
    2,    3,    4,   63,   49,   31,   32,   88,   19,   89,
   63,   63,   63,   63,   63,   63,   96,   63,   33,   44,
   35,   50,   51,   64,   52,   88,   17,   89,   53,   63,
   64,   64,   64,   64,   64,   64,   67,   64,   59,   69,
   94,  115,   74,   55,  121,   60,   74,  122,  127,   64,
   55,   55,   55,   55,   55,   55,    1,   55,   59,   18,
   19,    8,   21,   63,   56,   60,   39,    9,   66,   55,
   68,   56,   56,   56,   56,   56,   56,   31,   56,   36,
   12,  129,   70,   64,   53,    0,    0,    0,  117,    0,
   56,   53,   53,    0,   53,   53,   53,   20,   21,   22,
   23,   24,    0,   55,   54,    0,  123,    0,    0,    0,
   53,   54,   54,    0,   54,   54,   54,    0,  130,    0,
    0,    0,  132,    0,   56,    0,    0,   95,   86,   84,
   54,   85,    0,   87,   97,   86,   84,    0,   85,    0,
   87,  101,   86,   84,   53,   85,   88,   87,   89,    0,
  131,   86,   84,   88,   85,   89,   87,   44,   44,   44,
   88,   44,   89,   44,   54,   86,   84,  119,   85,   88,
   87,   89,   86,   84,    0,   85,   44,   87,   44,   37,
   42,   43,   29,   88,    0,   89,   39,   30,    0,   44,
   88,    0,   89,    0,   44,   44,   44,   44,   44,   44,
   44,   44,   44,   44,   44,   44,   44,   54,   55,   56,
   57,   58,   62,    0,    0,    0,   78,   79,   80,   81,
   82,   83,   54,   55,   56,   57,   58,   62,   88,    0,
   89,    0,    0,   63,   78,   79,   80,   81,   63,    0,
    0,    0,    0,   63,   63,   63,   63,   63,   63,   63,
   63,    0,    0,   64,   86,   84,    0,   85,   64,   87,
    0,    0,    0,   64,   64,   64,   64,   64,   64,   64,
   64,    0,   88,   55,   89,    0,   35,    0,   55,    0,
   54,   55,   56,   57,   58,   55,   55,   55,   55,   55,
   55,    0,    0,    0,   56,    0,    0,    0,    0,   56,
   72,   55,   56,   57,   58,  114,   56,   56,   56,   56,
   56,   56,    0,   35,   53,   68,    0,   86,   84,   53,
   85,    0,   87,    0,    0,    0,   53,   53,   53,   53,
   53,   53,    0,    0,   54,   88,    0,   89,    0,   54,
    0,    0,    0,    0,    0,    0,   54,   54,   54,   54,
   54,   54,    0,    0,    0,   78,   79,   80,   81,   82,
   83,    0,   78,   79,   80,   81,   82,   83,  118,   78,
   79,   80,   81,   82,   83,    0,    0,    0,   78,   79,
   80,   81,   82,   83,    0,   44,   44,   44,   44,   44,
   44,    0,   78,   79,   80,   81,   82,   83,  124,   78,
   79,   80,   81,   82,   83,   86,   84,    0,   85,    0,
   87,   86,    0,    0,   40,    0,   87,   41,   42,   43,
   44,    0,    0,   88,    0,   89,    0,    0,   45,   88,
    0,   89,    0,    0,    0,    0,    0,   78,   79,   80,
   81,   82,   83,    0,    0,    0,    0,    0,    0,    0,
    0,   40,    0,    0,   41,   42,   43,   44,    0,    0,
    0,    0,    0,    0,    0,   45,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   61,
    0,   78,   79,   80,   81,   82,   83,   71,   73,    0,
    0,    0,    0,    0,    0,   76,   77,    0,    0,    0,
    0,   92,   93,    0,    0,    0,    0,    0,    0,    0,
   98,   99,    0,    0,  102,  103,  104,  105,  106,  107,
  108,  109,  110,  111,  112,  113,    0,    0,    0,    0,
    0,    0,  116,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   78,   79,   80,   81,   82,   83,
    0,    0,    0,    0,    0,  125,    0,    0,  126,    0,
  128,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   78,   79,   80,   81,   82,   83,   78,   79,
   80,   81,   82,   83,
};
static const short yycheck[] = {                         33,
   19,   62,   63,   61,   59,   33,   59,   41,   42,   43,
   44,   45,   40,   47,   33,   59,   59,   59,   59,   59,
   33,  275,   59,   59,   18,   59,   60,   40,   62,   42,
   43,   40,   45,   91,   47,   40,   93,  275,   32,  257,
  258,  259,  260,   33,   38,   41,   58,   60,   40,   62,
   40,   41,   42,   43,   44,   45,   61,   47,   44,   93,
  123,  275,   40,   33,   40,   60,   58,   62,  275,   59,
   40,   41,   42,   43,   44,   45,   59,   47,   33,   48,
   59,  262,   91,   33,   41,   40,   91,   61,  263,   59,
   40,   41,   42,   43,   44,   45,    0,   47,   33,   91,
   41,   59,   41,   93,   33,   40,   59,   59,   41,   59,
   41,   40,   41,   42,   43,   44,   45,   59,   47,   31,
    6,  125,   50,   93,   33,   -1,   -1,   -1,   97,   -1,
   59,   40,   41,   -1,   43,   44,   45,  276,  277,  278,
  279,  280,   -1,   93,   33,   -1,  115,   -1,   -1,   -1,
   59,   40,   41,   -1,   43,   44,   45,   -1,  127,   -1,
   -1,   -1,  131,   -1,   93,   -1,   -1,   41,   42,   43,
   59,   45,   -1,   47,   41,   42,   43,   -1,   45,   -1,
   47,   41,   42,   43,   93,   45,   60,   47,   62,   -1,
   41,   42,   43,   60,   45,   62,   47,   41,   42,   43,
   60,   45,   62,   47,   93,   42,   43,   44,   45,   60,
   47,   62,   42,   43,   -1,   45,   60,   47,   62,  263,
  263,  263,  263,   60,   -1,   62,  263,  263,   -1,  263,
   60,   -1,   62,   -1,  268,  269,  270,  271,  272,  273,
  274,  275,  276,  277,  278,  279,  280,  275,  276,  277,
  278,  279,  280,   -1,   -1,   -1,  269,  270,  271,  272,
  273,  274,  275,  276,  277,  278,  279,  280,   60,   -1,
   62,   -1,   -1,  263,  269,  270,  271,  272,  268,   -1,
   -1,   -1,   -1,  273,  274,  275,  276,  277,  278,  279,
  280,   -1,   -1,  263,   42,   43,   -1,   45,  268,   47,
   -1,   -1,   -1,  273,  274,  275,  276,  277,  278,  279,
  280,   -1,   60,  263,   62,   -1,  123,   -1,  268,   -1,
  275,  276,  277,  278,  279,  275,  276,  277,  278,  279,
  280,   -1,   -1,   -1,  263,   -1,   -1,   -1,   -1,  268,
  275,  276,  277,  278,  279,   93,  275,  276,  277,  278,
  279,  280,   -1,  123,  263,  125,   -1,   42,   43,  268,
   45,   -1,   47,   -1,   -1,   -1,  275,  276,  277,  278,
  279,  280,   -1,   -1,  263,   60,   -1,   62,   -1,  268,
   -1,   -1,   -1,   -1,   -1,   -1,  275,  276,  277,  278,
  279,  280,   -1,   -1,   -1,  269,  270,  271,  272,  273,
  274,   -1,  269,  270,  271,  272,  273,  274,   93,  269,
  270,  271,  272,  273,  274,   -1,   -1,   -1,  269,  270,
  271,  272,  273,  274,   -1,  269,  270,  271,  272,  273,
  274,   -1,  269,  270,  271,  272,  273,  274,  268,  269,
  270,  271,  272,  273,  274,   42,   43,   -1,   45,   -1,
   47,   42,   -1,   -1,  261,   -1,   47,  264,  265,  266,
  267,   -1,   -1,   60,   -1,   62,   -1,   -1,  275,   60,
   -1,   62,   -1,   -1,   -1,   -1,   -1,  269,  270,  271,
  272,  273,  274,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  261,   -1,   -1,  264,  265,  266,  267,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  275,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   43,
   -1,  269,  270,  271,  272,  273,  274,   51,   52,   -1,
   -1,   -1,   -1,   -1,   -1,   59,   60,   -1,   -1,   -1,
   -1,   65,   66,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   74,   75,   -1,   -1,   78,   79,   80,   81,   82,   83,
   84,   85,   86,   87,   88,   89,   -1,   -1,   -1,   -1,
   -1,   -1,   96,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  269,  270,  271,  272,  273,  274,
   -1,   -1,   -1,   -1,   -1,  119,   -1,   -1,  122,   -1,
  124,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  269,  270,  271,  272,  273,  274,  269,  270,
  271,  272,  273,  274,
};
#define YYFINAL 5
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 281
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? (YYMAXTOKEN + 1) : (a))
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'!'",0,0,0,0,0,0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,0,0,0,0,
0,"':'","';'","'<'","'='","'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,"'['",0,"']'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'{'",0,"'}'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"KW_INT","KW_FLOAT","KW_BOOL","KW_CHAR",
"KW_IF","KW_THEN","KW_ELSE","KW_FOR","KW_READ","KW_RETURN","KW_PRINT","KW_TO",
"OPERATOR_LE","OPERATOR_GE","OPERATOR_EQ","OPERATOR_NE","OPERATOR_AND",
"OPERATOR_OR","TK_IDENTIFIER","LIT_INTEGER","LIT_TRUE","LIT_FALSE","LIT_CHAR",
"LIT_STRING","TOKEN_ERROR","illegal-symbol",
};
static const char *yyrule[] = {
"$accept : programa",
"programa : lista_declaracoes",
"lista_declaracoes : lista_declaracoes declaracoes",
"lista_declaracoes : declaracoes",
"declaracoes : declaracao_vars_globais ';'",
"declaracoes : declaracao_vetores ';'",
"declaracoes : declaracao_funcao ';'",
"declaracao_vars_globais : tipo TK_IDENTIFIER ':' literais",
"declaracao_vetores : tipo TK_IDENTIFIER '[' literais ']'",
"declaracao_vetores : tipo TK_IDENTIFIER '[' literais ']' ':' ARRAYNUM",
"ARRAYNUM : ARRAYNUM literais",
"ARRAYNUM : literais",
"literais : LIT_INTEGER",
"literais : LIT_CHAR",
"literais : LIT_STRING",
"literais : LIT_TRUE",
"literais : LIT_FALSE",
"declaracao_funcao : tipo TK_IDENTIFIER '(' parametros_chamada ')' bloco",
"parametros_chamada : tipo TK_IDENTIFIER parametros_resto",
"parametros_chamada :",
"parametros_resto : ',' tipo TK_IDENTIFIER parametros_resto",
"parametros_resto :",
"tipo : KW_INT",
"tipo : KW_FLOAT",
"tipo : KW_BOOL",
"tipo : KW_CHAR",
"bloco : '{' lista_de_comandos '}'",
"lista_de_comandos : lista_de_comandos comandos ';'",
"lista_de_comandos : comandos ';'",
"comandos : TK_IDENTIFIER '=' expressao",
"comandos : TK_IDENTIFIER '[' expressao ']' '=' expressao",
"comandos : KW_IF '(' expressao ')' KW_THEN comandos",
"comandos : KW_IF '(' expressao ')' KW_THEN comandos KW_ELSE comandos",
"comandos : KW_FOR '(' expressao ')' comandos",
"comandos : KW_FOR '(' TK_IDENTIFIER '=' expressao KW_TO expressao ')' comandos",
"comandos : KW_PRINT print",
"comandos : KW_READ TK_IDENTIFIER",
"comandos : KW_RETURN expressao",
"comandos : bloco",
"comandos :",
"print : LIT_STRING print",
"print : expressao print",
"print : LIT_STRING",
"print : expressao",
"expressao : TK_IDENTIFIER",
"expressao : LIT_INTEGER",
"expressao : LIT_TRUE",
"expressao : LIT_FALSE",
"expressao : LIT_CHAR",
"expressao : TK_IDENTIFIER '[' expressao ']'",
"expressao : TK_IDENTIFIER '(' argumentos ')'",
"expressao : '(' expressao ')'",
"expressao : '!' expressao",
"expressao : expressao '+' expressao",
"expressao : expressao '-' expressao",
"expressao : expressao '*' expressao",
"expressao : expressao '/' expressao",
"expressao : expressao '<' expressao",
"expressao : expressao '>' expressao",
"expressao : expressao OPERATOR_LE expressao",
"expressao : expressao OPERATOR_GE expressao",
"expressao : expressao OPERATOR_EQ expressao",
"expressao : expressao OPERATOR_NE expressao",
"expressao : expressao OPERATOR_AND expressao",
"expressao : expressao OPERATOR_OR expressao",
"argumentos : expressao resto_argumentos",
"argumentos :",
"resto_argumentos : ',' expressao resto_argumentos",
"resto_argumentos :",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    short    *s_base;
    short    *s_mark;
    short    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 214 "parser.y"
ASTREE *get_ASTREE_root ()
{
	return root;

}

int yyerror ()
{
	printf ("Sintax Error: in line number %d\n", getLineNumber());
	exit(3);
}
#line 464 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (short *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack)) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 98 "parser.y"
	{ root = astreeCreate(ASTREE_PROGRAMA, 0, yystack.l_mark[0].astree, 0, 0, 0, getLineNumber()); 
									  astreeDecompile(yystack.l_mark[0].astree,ASTREE_PROGRAMA);
									  setTypes(root);
									  astreePrint(root, 0);
									  checkSemantic(root);
									  /*tacPrintList(generateCode(root));*/

									}
break;
case 2:
#line 108 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_LISTA_DECLARACOES,0,yystack.l_mark[-1].astree,yystack.l_mark[0].astree,0,0, getLineNumber()); }
break;
case 3:
#line 109 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_LISTA_DECLARACOES,0,yystack.l_mark[0].astree,0,0,0, getLineNumber()); }
break;
case 4:
#line 112 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_DECLARACOES,0,yystack.l_mark[-1].astree,0,0,0, getLineNumber()); }
break;
case 5:
#line 113 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_DECLARACOES,0,yystack.l_mark[-1].astree,0,0,0, getLineNumber()); }
break;
case 6:
#line 114 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_DECLARACOES,0,yystack.l_mark[-1].astree,0,0,0, getLineNumber()); }
break;
case 7:
#line 117 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_VARIAVEL,yystack.l_mark[-2].symbol,yystack.l_mark[-3].astree,yystack.l_mark[0].astree,0,0, getLineNumber()); }
break;
case 8:
#line 121 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_VETOR_DECLARADO_1,yystack.l_mark[-3].symbol,yystack.l_mark[-4].astree,yystack.l_mark[-1].astree,0,0, getLineNumber());	}
break;
case 9:
#line 122 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_VETOR_DECLARADO_2,yystack.l_mark[-5].symbol,yystack.l_mark[-6].astree,yystack.l_mark[-3].astree,yystack.l_mark[0].astree,0, getLineNumber());	}
break;
case 10:
#line 125 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_VETOR_CONTEUDO,0,yystack.l_mark[0].astree,yystack.l_mark[-1].astree,0,0, getLineNumber());	}
break;
case 11:
#line 126 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_VETOR_CONTEUDO,0,yystack.l_mark[0].astree,0,0,0, getLineNumber());	}
break;
case 12:
#line 129 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_SYMBOL,yystack.l_mark[0].symbol,0,0,0,0, getLineNumber());	}
break;
case 13:
#line 130 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_SYMBOL,yystack.l_mark[0].symbol,0,0,0,0, getLineNumber());	}
break;
case 14:
#line 131 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_SYMBOL,yystack.l_mark[0].symbol,0,0,0,0, getLineNumber());	}
break;
case 15:
#line 132 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_SYMBOL,yystack.l_mark[0].symbol,0,0,0,0, getLineNumber());	}
break;
case 16:
#line 133 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_SYMBOL,yystack.l_mark[0].symbol,0,0,0,0, getLineNumber());	}
break;
case 17:
#line 136 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_DECLARACAO_FUNCAO,yystack.l_mark[-4].symbol,yystack.l_mark[-5].astree,yystack.l_mark[-2].astree,yystack.l_mark[0].astree,0, getLineNumber());	}
break;
case 18:
#line 139 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_PARAMETROS,yystack.l_mark[-1].symbol,yystack.l_mark[-2].astree,yystack.l_mark[0].astree,0,0, getLineNumber());	}
break;
case 19:
#line 140 "parser.y"
	{ yyval.astree = 0; }
break;
case 20:
#line 143 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_PARAMETROS_RESTO,yystack.l_mark[-1].symbol,yystack.l_mark[-2].astree,yystack.l_mark[0].astree,0,0, getLineNumber());	}
break;
case 21:
#line 144 "parser.y"
	{ yyval.astree = 0; }
break;
case 22:
#line 148 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_INT,0,0,0,0,0, getLineNumber());	}
break;
case 23:
#line 149 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_FLOAT,0,0,0,0,0, getLineNumber());	}
break;
case 24:
#line 150 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_BOOL,0,0,0,0,0, getLineNumber());	}
break;
case 25:
#line 151 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_CHAR,0,0,0,0,0, getLineNumber());	}
break;
case 26:
#line 154 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_BLOCO,0,yystack.l_mark[-1].astree,0,0,0, getLineNumber());	}
break;
case 27:
#line 158 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_LISTA_COMANDOS,0,yystack.l_mark[-2].astree,yystack.l_mark[-1].astree,0,0, getLineNumber());	}
break;
case 28:
#line 159 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_LISTA_COMANDOS,0,yystack.l_mark[-1].astree,0,0,0, getLineNumber());  }
break;
case 29:
#line 162 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_CMD_ATRIBUICAO,yystack.l_mark[-2].symbol,yystack.l_mark[0].astree,0,0,0, getLineNumber());	}
break;
case 30:
#line 163 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_CMD_ATRIBUICAO_VETOR,yystack.l_mark[-5].symbol,yystack.l_mark[-3].astree,yystack.l_mark[0].astree,0,0, getLineNumber());	}
break;
case 31:
#line 164 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_CMD_IF,0,yystack.l_mark[-3].astree,yystack.l_mark[0].astree,0,0, getLineNumber());	}
break;
case 32:
#line 165 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_CMD_IF_ELSE,0,yystack.l_mark[-5].astree,yystack.l_mark[-2].astree,yystack.l_mark[0].astree,0, getLineNumber());	}
break;
case 33:
#line 166 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_CMD_FOR,0,yystack.l_mark[-2].astree,yystack.l_mark[0].astree,0,0, getLineNumber());	}
break;
case 34:
#line 167 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_CMD_FOR_TO,yystack.l_mark[-6].symbol,yystack.l_mark[-4].astree,yystack.l_mark[-2].astree,yystack.l_mark[0].astree,0, getLineNumber()); }
break;
case 35:
#line 168 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_CMD_PRINT,0,yystack.l_mark[0].astree,0,0,0, getLineNumber());	}
break;
case 36:
#line 169 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_CMD_READ,yystack.l_mark[0].symbol,0,0,0,0, getLineNumber());	}
break;
case 37:
#line 170 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_CMD_RETURN,0,yystack.l_mark[0].astree,0,0,0, getLineNumber());	}
break;
case 38:
#line 171 "parser.y"
	{ yyval.astree = yystack.l_mark[0].astree;						}
break;
case 39:
#line 172 "parser.y"
	{ yyval.astree = 0;						}
break;
case 40:
#line 175 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_CMD_PRINT,yystack.l_mark[-1].symbol,yystack.l_mark[0].astree,0,0,0, getLineNumber());	}
break;
case 41:
#line 176 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_CMD_PRINT,0,yystack.l_mark[-1].astree,yystack.l_mark[0].astree,0,0, getLineNumber());	}
break;
case 42:
#line 177 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_CMD_PRINT,yystack.l_mark[0].symbol,0,0,0,0, getLineNumber());       }
break;
case 43:
#line 178 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_CMD_PRINT,0,yystack.l_mark[0].astree,0,0,0, getLineNumber());	}
break;
case 44:
#line 181 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_SYMBOL,yystack.l_mark[0].symbol,0,0,0,0, getLineNumber());		}
break;
case 45:
#line 182 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_SYMBOL,yystack.l_mark[0].symbol,0,0,0,0, getLineNumber());		}
break;
case 46:
#line 183 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_SYMBOL,yystack.l_mark[0].symbol,0,0,0,0, getLineNumber());		}
break;
case 47:
#line 184 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_SYMBOL,yystack.l_mark[0].symbol,0,0,0,0, getLineNumber());		}
break;
case 48:
#line 185 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_SYMBOL,yystack.l_mark[0].symbol,0,0,0,0, getLineNumber());		}
break;
case 49:
#line 186 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_VETOR,yystack.l_mark[-3].symbol,yystack.l_mark[-1].astree,0,0,0, getLineNumber());		}
break;
case 50:
#line 187 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_CHAMADA_FUNCAO,yystack.l_mark[-3].symbol,yystack.l_mark[-1].astree,0,0,0, getLineNumber());}
break;
case 51:
#line 188 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_EXP_PARENTESES,0,yystack.l_mark[-1].astree,0,0,0, getLineNumber()); }
break;
case 52:
#line 189 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_NEGACAO,0,yystack.l_mark[0].astree,0,0,0, getLineNumber());	}
break;
case 53:
#line 190 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_ADD,0,yystack.l_mark[-2].astree,yystack.l_mark[0].astree,0,0, getLineNumber());		}
break;
case 54:
#line 191 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_SUB,0,yystack.l_mark[-2].astree,yystack.l_mark[0].astree,0,0, getLineNumber());		}
break;
case 55:
#line 192 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_MUL,0,yystack.l_mark[-2].astree,yystack.l_mark[0].astree,0,0, getLineNumber());		}
break;
case 56:
#line 193 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_DIV,0,yystack.l_mark[-2].astree,yystack.l_mark[0].astree,0,0, getLineNumber());		}
break;
case 57:
#line 194 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_MENOR,0,yystack.l_mark[-2].astree,yystack.l_mark[0].astree,0,0, getLineNumber());		}
break;
case 58:
#line 195 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_MAIOR,0,yystack.l_mark[-2].astree,yystack.l_mark[0].astree,0,0, getLineNumber());		}
break;
case 59:
#line 196 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_LE,0,yystack.l_mark[-2].astree,yystack.l_mark[0].astree,0,0, getLineNumber());		}
break;
case 60:
#line 197 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_GE,0,yystack.l_mark[-2].astree,yystack.l_mark[0].astree,0,0, getLineNumber());		}
break;
case 61:
#line 198 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_EQ,0,yystack.l_mark[-2].astree,yystack.l_mark[0].astree,0,0, getLineNumber());		}
break;
case 62:
#line 199 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_NE,0,yystack.l_mark[-2].astree,yystack.l_mark[0].astree,0,0, getLineNumber());		}
break;
case 63:
#line 200 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_AND,0,yystack.l_mark[-2].astree,yystack.l_mark[0].astree,0,0, getLineNumber());		}
break;
case 64:
#line 201 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_OR,0,yystack.l_mark[-2].astree,yystack.l_mark[0].astree,0,0, getLineNumber());		}
break;
case 65:
#line 204 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_ARGUMENTOS,0,yystack.l_mark[-1].astree,yystack.l_mark[0].astree,0,0, getLineNumber());	}
break;
case 66:
#line 205 "parser.y"
	{ yyval.astree = 0; }
break;
case 67:
#line 208 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_RESTO_ARGUMENTOS,0,yystack.l_mark[-1].astree,yystack.l_mark[0].astree,0,0, getLineNumber());}
break;
case 68:
#line 209 "parser.y"
	{ yyval.astree = 0; }
break;
#line 945 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (short) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
