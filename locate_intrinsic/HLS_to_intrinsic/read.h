#ifndef __GOTOH_H__
#define __GOTOH_H__


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// data structure for an ungapped sequence (read it from a FASTA file using gth_read_fasta)
typedef struct nw_Seq nw_Seq;
struct nw_Seq {
    int len;         // number of residues in the sequences (without the terminating NULL character)
    char name[256];     // name of the sequence
    char *res;          // sequence residues (should be A-Z letters); don't forget to free the memory once not needed anymore
};
nw_Seq read_ngimu(const char *filename);

#endif