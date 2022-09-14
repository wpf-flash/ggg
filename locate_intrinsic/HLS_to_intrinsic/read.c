#include "read.h"

// read a sequence from a FASTA file
nw_Seq read_ngimu(const char *filename) {

    nw_Seq seq;
    seq.len = 0;
    seq.name[0] = '\0';
    seq.res = NULL;
    FILE *file = fopen(filename, "r");
    if (!file) return seq;

    // // default sequence name is filename
    // strncpy(seq.name, filename, sizeof(seq.name)-1);
    // seq.name[sizeof(seq.name)-1] = '\0';

    // // read sequence name
    // char format[16];
    // sprintf(format, " >%%%lus%%*[^\n]", sizeof(seq.name)-1);
    // fscanf(file, format, seq.name);

    // get sequence size and allocate memory
    long offset = ftell(file);
    while (!feof(file)) {
        int c = fgetc(file);
        if (isalpha(c)) seq.len++;
    }
    if (seq.len == 0) return seq;
    seq.res = (char*) malloc(sizeof(char) * (seq.len+1));

    // read sequence
    if (seq.res != NULL) {
        fseek(file, offset, SEEK_SET);

        size_t i = 0;
        while (!feof(file) && i<seq.len) {
            int c = fgetc(file);
            if (isalpha(c)) seq.res[i++] = toupper(c);
        }
        seq.res[i] = '\0';
    }
    else seq.len = 0;
    
    fclose(file);
    return seq;
}