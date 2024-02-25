#include <string.h>
#include <stdio.h>
// #include <Python.h>

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

void nussinov(const char rna[]) {
    printf("Input sequence: %s\n", rna);
    int length = strlen(rna);


    printf("The length of the rna sequence: %d\n", length);

    int matrix[length][length];
    char structure[length + 1];

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

    printf("Optimal secondary structure: %s\n", structure);
    // return structure;
}
/*
static PyObject* _hello_world(PyObject* self){
    return PyUnicode_FromString("Hello World!");
}

static PyObject* version(PyObject* self){
    return PyUnicode_FromString("Test version (the algorithm is not verified)");
}

static PyObject* process_string(PyObject* self, PyObject* args) {
    const char* input_str;

    // Parse the input Python string into a C string
    if (!PyArg_ParseTuple(args, "s", &input_str)) {
        return NULL;
    }

    // Process the input string using the nussinov function
    char* processed_str = nussinov(input_str);

    // Check if processing failed
    if (processed_str == NULL) {
        return NULL;
    }

    // Convert the processed C string to a Python string
    PyObject* result = PyUnicode_FromString(processed_str);

    // Free dynamically allocated memory
    free(processed_str);

    return result;
}


static struct PyMethodDef methods[] = {
    {"hello_world", (PyCFunction)_hello_world, METH_NOARGS},
    {"version", (PyCFunction)version, METH_NOARGS},
    {"process_string", process_string, METH_VARARGS, "Process a string"},
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
*/

int main(void){
    char rna[] = "AGACGACAAGGUUGAAUCGCACCCACAGUCUAUGAGUCGGUG";
    nussinov(rna);
}




