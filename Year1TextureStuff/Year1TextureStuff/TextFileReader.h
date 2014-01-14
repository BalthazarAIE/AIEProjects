#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
char *textFileReader(const char* a_szFileName) {
 
    FILE *pFilePointer;
    char *content = NULL;
 
    int count=0;
 
    if (a_szFileName != NULL) {
        pFilePointer = fopen(a_szFileName,"r");
 
        if (pFilePointer != NULL) {
 
      fseek(pFilePointer, 0, SEEK_END);
      count = ftell(pFilePointer);
      rewind(pFilePointer);
 
            if (count > 0) {
                content = (char *)malloc(sizeof(char) * (count+1));
                count = fread(content,sizeof(char),count,pFilePointer);
                content[count] = '\0';
            }
            fclose(pFilePointer);
        }
    }
    return content;
}