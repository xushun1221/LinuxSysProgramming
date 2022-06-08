#include <stdio.h>
#include <stdlib.h>
int main() {
    FILE *fp_in, *fp_out;
    int ch;
    fp_in = fopen("bigfile.txt", "r");
    fp_out = fopen("bigfile.cp", "w");
    while ((ch = fgetc(fp_in)) != EOF) {
        fputc(ch, fp_out);
    }
    fclose(fp_in);
    fclose(fp_out);
    return 0;
}