#include "stdlib.h"
#ifndef __SYMTABLE_H__
#define __SYMTABLE_H__


 
typedef struct symtable ysymtable;

typedef ysymtable* SymTable_T;




SymTable_T SymTable_new(void);

void SymTable_free(SymTable_T oSymTable);


void SymTable_getTail(SymTable_T oSymtable );

void SymTable_print(SymTable_T oSymtable );

SymTable_T adder(SymTable_T oSymTable, char* pckey, void* pvValue, SymTable_T Prev);

unsigned int SymTable_getLength(SymTable_T oSymTable);

int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue);

int SymTable_remove(SymTable_T oSymTable, const char *pcKey);

int SymTable_contains(SymTable_T oSymTable, const char *pcKey);

void *SymTable_get(SymTable_T oSymTable, const char *pcKey);

void SymTable_map(SymTable_T oSymTable, void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),const void *pvExtra);

#endif