#include <string.h>
#include <stdio.h>
#include <Python.h>

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

// Nussinov algorithm for rna folding
void nussinov(const char rna[], char* structure) {
    int length = strlen(rna);

    printf("Input sequence: %s\n", rna);
    printf("The length of the rna sequence: %d\n", length);

    int matrix[length][length];

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            matrix[i][j] = 0;
        }
    }

    for (int j = 0; j < length; j++) {
        for (int i = 0; i < j; i++) { 
            matrix[i][j] = max(matrix[i][j], matrix[i+1][j]);
            if ((rna[i] == 'A' && rna[j] == 'U') || (rna[i] == 'U' && rna[j] == 'A') ||
                (rna[i] == 'C' && rna[j] == 'G') || (rna[i] == 'G' && rna[j] == 'C')) {
                matrix[i][j] = max(matrix[i][j], matrix[i+1][j-1] + 1);
            }
            for (int k = i+1; k < j-1; k++){
                matrix[i][j] = max(matrix[i][j], matrix[i][k] + matrix[k+1][j]);
            }
        }
    }

    for (int i = 0; i < length; i++) {
        structure[i] = '.'; 
    }
    structure[length] = '\0'; 

    int i = 0;
    int j = length - 1;
    while (i < j) {
        if ((rna[i] == 'A' && rna[j] == 'U') || (rna[i] == 'U' && rna[j] == 'A') ||
            (rna[i] == 'C' && rna[j] == 'G') || (rna[i] == 'G' && rna[j] == 'C')) {
            if (matrix[i][j] == matrix[i + 1][j - 1] + 1) {
                structure[i] = '(';
                structure[j] = ')';
                i++;
                j--;
                continue;
            }
        }
        if (matrix[i][j] == matrix[i + 1][j]) {
            i++;
        } else {
            j--;
        }
    }

    // printf("Optimal secondary structure: %s\n", structure);
}

static PyObject* _hello_world(PyObject* self){
    return PyUnicode_FromString("Hello World!");
}

static PyObject* version(PyObject* self){
    return PyUnicode_FromString("Test version (the algorithm is not verified)");
}

static PyObject* fold(PyObject* self, PyObject* args) {
    const char* input_str;

    // Parse the input Python string into a C string
    if (!PyArg_ParseTuple(args, "s", &input_str)) {
        return NULL;
    }

    int length = strlen(input_str);
    char structure[length + 1];  // Allocate buffer for the structure array

    // Process the input string using the nussinov function
    nussinov(input_str, structure);

    // Convert the processed C string to a Python string
    return PyUnicode_FromString(structure);
}


static struct PyMethodDef methods[] = {
    {"hello_world", (PyCFunction)_hello_world, METH_NOARGS},
    {"version", (PyCFunction)version, METH_NOARGS},
    {"fold", (PyCFunction)fold, METH_VARARGS, "Returns secondary structure of a nucleotide sequence"},
    {NULL, NULL}
};

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "my-rna-folding",
    NULL,
    -1,
    methods
};

PyMODINIT_FUNC PyInit_rna_fold(void){
    return PyModule_Create(&module);
}



