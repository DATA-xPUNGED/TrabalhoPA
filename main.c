#include <stdlib.h>
#include <stdio.h>
#include <struct_defines.c>
#include <function_define.c>

int main(){
    fopen("..\\dados.bin", "w+");
    fclose("..\\dados.bin");
    return 0;
}