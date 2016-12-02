//--------------------------------------------//
// ALUNOS: TAGLINE TREICHEL e BRUNO FILLMANN
//--------------------------------------------//

#include "tac.h"
#include "astree.h"

TAC* generateCode(ASTREE *node);
TAC* makeIf(TAC** code);
TAC* makeIfThen(TAC** code);
TAC* makeFuncDecl(HASH_NODE* symbol, TAC** code);
TAC* makeAtribVector(HASH_NODE* symbol, TAC** code);
//TAC* makeFor(TAC** node);
void tac2asm (TAC*node, FILE *fout);

