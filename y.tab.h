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
extern YYSTYPE yylval;
