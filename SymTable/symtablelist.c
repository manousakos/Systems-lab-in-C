
#include "assert.h"
#include "stdio.h"
#include "string.h"

#include "symtable.h"

struct symtable{

    char* key;
    void* value;
    SymTable_T next;
};




/* simple function that allocates space of size struct symtable to 
 a Symtable pointer and returns it*/

SymTable_T SymTable_new(void){

    SymTable_T oSymTable= malloc(sizeof(SymTable_T));
    
    if(oSymTable == NULL){
        printf("Error at memory allocation to new SymTable_T in SymTable_new().\n");
        exit(1);
    }

    oSymTable->key = NULL;
    oSymTable->value = NULL;
    oSymTable->next=NULL;

    

    return oSymTable;

}


/* this function

    frees all the space allocated by pckey and oSym*/
void SymTable_free(SymTable_T oSymTable){
    
    printf("KOKOK\n");
    SymTable_T prev = oSymTable;

    unsigned int i=0;

    SymTable_print(oSymTable);
    for(i=0; i< SymTable_getLength(oSymTable); i++){
        
        printf("---> 1\n");
        
        if(prev->key == NULL) {

        
            printf("---> 2\n");
            prev = prev ->next;
            continue;
        }
        if(prev ->next == NULL){
            printf("---> 4\n");
            free(prev->key);
            continue;
        }
        else{
            printf("---> 3\n");
            free(prev->key);
            prev = prev->next;
        }




    }

    for(i = 0; i<SymTable_getLength(oSymTable); i++){

        if( oSymTable->next == NULL){

            free(oSymTable);
        }
        else{
        prev = oSymTable;
        oSymTable = oSymTable->next;
         free( prev);
        }
    }



    /*
    if(oSymTable->next==NULL)   {
    printf("bObOK\n");
        free(oSymTable->key);

        free(oSymTable);


    }
    else{
        counter++;
    
        printf("AMOK\n");
        SymTable_free( oSymTable->next );
        
        
    }
    printf("SOKSOK -1\n");
    free(oSymTable->key);

    printf("SOKSOK -2\n");
        free(oSymTable);
    printf("SOKSOK -3\n");
    */
}


/* helper function that immidiately adds a bindig to the given node , and returns it*/
SymTable_T adder(SymTable_T oSymTable, char* pckey, void* pvValue, SymTable_T Prev ){
    
    printf("we problem?\n");
    oSymTable->key= (char*)calloc(strlen(pckey), sizeof(char));
    printf("noe problem?\n");

    oSymTable->key= strcpy(oSymTable->key, pckey);
    printf("where problem? key: %s\n", oSymTable->key);
    
    oSymTable->value= pvValue;

    if( Prev !=NULL ){

        Prev->next = oSymTable;
        return Prev;
    }

    oSymTable->next =NULL;
    return oSymTable;
}






/* function that prints all the contents of the oSym*/
void SymTable_print(SymTable_T oSymtable ){
    
    
    
    if( oSymtable->next == NULL){
        
         printf("===== key: %s\nvalue: %d\nnext: %u\n\n",oSymtable->key,(int* ) (oSymtable->value), oSymtable->next);
    }
    else{

        printf("===== key: %s\nvalue: %d\nnext: %u\n\n",oSymtable->key,(int* )oSymtable->value, oSymtable->next);
        SymTable_print(oSymtable->next);
    }
    /*
    printf("here we are 1\n");
    printf("key: %s\nvalue: %d\nnext: %u\n\n",oSymtable->key,oSymtable->value, oSymtable->next);
    while(list->next != NULL){
        printf("here we are 2\n");
        printf("key: %s\nvalue: %d\nnext: %u\n\n",oSymtable->key,oSymtable->value, oSymtable->next);
        counter++;        
        list=list->next;
    }
    */
    
}
/*
this function starts counting how many more nodes there are
in the Symtable. It starts counting from the one that we are pasing as an arguement,
So oSymTable should be the head of the symtable
*/
unsigned int SymTable_getLength(SymTable_T oSymTable){
    
    unsigned int counter=1;

    SymTable_T nodes= oSymTable;

    while( (nodes->next)!= NULL ){
        
        counter++;
        nodes = nodes->next;

    }

    return counter;
}

/*
    this function checkes if oSym/pcKey is NULL
    
    then checks if the pckey is already in the list,
    
    if yes, adds it and returns 1,
    else returns 0
    */
int SymTable_contains(SymTable_T oSymTable, const char *pcKey){

    
    SymTable_T nodes= oSymTable;
    unsigned int len = SymTable_getLength(oSymTable);
    unsigned int i = 0 ;

/*  if the struct contains only the head return 0*/
    if(len==0)
    {
    return 0;
    }
    if( oSymTable == NULL) {  
        printf("Symtable given as arguement is NULL, try again.\n");
        exit(1);
    }
    if( pcKey == NULL ) {
        printf("Pckey given as arguement is NULL, try again.\n");
        exit(1);
    }

    nodes= nodes->next; /*  we select the node next of the head */
    /* we start our loop from i=1 because we want to avoid head node*/
    
    for(i=1; i<len; i++){
        if(nodes->key == NULL){ return 0; }
        else if(strcmp(pcKey,nodes->key) == 0){
            
            
            return 1;
        }
        nodes= nodes->next;

    }
    
    return 0;
}


/* this function is checked runtime whether oSym/pckey are NULL

    then it checks whether the pckey is already in the list
    
    if it is not, it adds it, returns 1
    
    otherwise it does not and return 0*/
int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue){

    
    SymTable_T newNode, tailSym= oSymTable;
    
   


    while(tailSym->next != NULL){
        tailSym=tailSym->next;

    }   

    /*  if contains ==1 return 0, the key is on the list */
    if( SymTable_contains(oSymTable, pcKey) == 1  )  {
        return 0;
    }

    /*      else enter the binding to the oSYm*/
    else
    {

    newNode= SymTable_new();

    newNode->key = calloc(strlen(pcKey), sizeof(char));    
    newNode->key = strcat(pcKey,"\0");

    newNode->value = pvValue;

    tailSym->next = newNode;
    
    
    return 1;

    }
    
    /* if something goes wrong, return 0, just in case */
    return 0;

}


/* here we fist check as a cjecked runtime error whether oSym or pckey are null

    later we traverse the list in search of a copy of a key, if contains ==1 valid++

    if(valid++), point the previous' next to cyrrent's next ad free current
    
    */
int SymTable_remove(SymTable_T oSymTable, const char *pcKey){

    SymTable_T prev = oSymTable, curr;
    unsigned int i=0;
    int valid =0;
    
    if(oSymTable == NULL){

        assert("Given Symtable_T on remove() is NULL.\n");
        return 0;
    }

    if(pcKey == NULL){

        assert("Given pcKey on remove() is NULL.\n");
        return 0;
    }

    
     
    
    for(i=0; i<SymTable_getLength(oSymTable); i++){
           

        if(prev->key==NULL){
            if( ( strcmp(pcKey, (*prev->next).key) == 0 ))
            {
                curr= prev->next;

                valid++;

                break;
                
            }
        }
        
       
        else if( ( strcmp(pcKey, (*prev->next).key) == 0 ))
        {
            curr= prev->next;

            valid++;
            break;
        }

       
        prev = prev->next;

    }


    if( valid ==1 ){

        prev->next = curr->next;
        free(curr);
        return 1;
    }


    
    
    
   

    
    

   return 0;
}


/*  in this function we  have checked runtime errors if oSYm/pckey are NULL

    then we traverse the list and check whether it contains key
    
    if contains == 1, return the pointer back 
    
    else return NULL */
void *SymTable_get(SymTable_T oSymTable, const char *pcKey){

    SymTable_T node;
    unsigned int i;

    if(oSymTable == NULL){

        assert("Given Symtable_T on remove() is NULL.\n");
        return 0;
    }

    if(pcKey == NULL){

        assert("Given pcKey on remove() is NULL.\n");
        return 0;
    }

    node= oSymTable;

    for(i=0; i< SymTable_getLength(oSymTable); i++){

        if(node->key ==NULL) {
         
            node = node->next;
            continue;
        }
        else if( strcmp(pcKey,node->key) == 0 ){
            

            return node->value;
        } 
        node= node->next;
    }
    

    return NULL;

}



void SymTable_map(SymTable_T oSymTable, void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),const void *pvExtra){


    unsigned int i;
    SymTable_T node;

    void* ptr;

    if( oSymTable ==NULL){
    }
    if(pfApply == NULL ){
    }

    node = oSymTable;
    for(i = 0; i< SymTable_getLength(oSymTable); i++ ){

        if(node->key == NULL ) {
            node = node->next;
            continue;
        }
        pfApply(node->key,node->value, pvExtra);
        if(node->next == NULL)  {
            break;
        }    
        node = node->next;
    }


}