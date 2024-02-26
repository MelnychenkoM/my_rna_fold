#ifndef RNA_FOLD_H
#define RNA_FOLD_H

void nussinov(const char rna[], char* structure);
double GC_content(const char* seq);
void populate_matrix(const char rna[], int length, int matrix[length][length]);

#endif