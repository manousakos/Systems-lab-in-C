#include "stdio.h"
#include"string.h"

#include "symtable.h"




void SymTable_helperMap(const char *pcKey, void *pvValue, void *pvExtra){


    printf("++++++ pckey: %s, pvValue: %d, pvExtrta: %d +++++\n",pcKey, pvValue, pvExtra);

}


int main(void){


    SymTable_T oSymtable = SymTable_new();
    SymTable_T twoSymtable = SymTable_new();

    int* ip,zp;
    int x=666,y,z=444;
    char *key= "kleidi";
    char* psema = "ayga";
    char* ayga = key;
    char * lefto ="lefteris";

    char *nol = NULL;
    char* yur = key;
    ip = &x;
    zp= &z;

    void (*func_ptr)(const char *, void *, void*);
    func_ptr = SymTable_helperMap;
   
    
    
    printf("Here starts the programm\n");
    

    printf("--> Adding Binding with pckey: %s\n...Now printing whole oSym...\n", yur);
    
    
    
    
    y = SymTable_put(oSymtable,yur, ip);
    SymTable_print(oSymtable);

    printf("--> Adding Binding with pckey: %s\n...Now printing whole oSym, it is not being added on oSym...\n", ayga);
    y = SymTable_put(oSymtable,ayga, ip);
    SymTable_print(oSymtable);

    printf("--> Adding Binding with pckey: %s\n...Now printing whole oSym...\n", "ATONIS");
    y=SymTable_put(oSymtable,"ATONIS", ip);
    SymTable_print(oSymtable);

    printf("--> Adding Binding with pckey: %s\n...Now printing whole oSym...\n", lefto);
    y=SymTable_put(oSymtable, lefto,zp);
    SymTable_print(oSymtable);

    
    printf("\n---\nRemoving %s, success--->  %d\n---\n",ayga,SymTable_remove(oSymtable, ayga));   
    SymTable_print(oSymtable);

    

    ip = SymTable_get(oSymtable, lefto);
    
    SymTable_print(oSymtable);

    
    SymTable_map(oSymtable,func_ptr, zp ); 

    printf("we in suku\n");
    
    SymTable_free(oSymtable);
        


    

    return 0;
}