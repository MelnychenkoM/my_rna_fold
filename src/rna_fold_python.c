#include <Python.h>
#include "rna_fold.h"

// Returns version and info about the module
static PyObject* version(PyObject* self){
    return PyUnicode_FromString("Test version (the algorithm is not verified)");
};

// Nussinov algorithm for python
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
};

// GC content (Currently only for RNA)
static PyObject* gc_content(PyObject* self, PyObject* args) {
    const char* input_str;

    // Parse the input Python string into a C string
    if (!PyArg_ParseTuple(args, "s", &input_str)) {
        return NULL;
    }
    
    double content = GC_content(input_str);
    
    // Convert the double value to a Python float
    PyObject* py_float = PyFloat_FromDouble(content);
    
    // Check if the conversion was successful
    if (py_float == NULL) {
        return NULL;  // Memory allocation error
    }

    // Return the Python float object
    return py_float;
}

static PyObject* create_matrix(PyObject* self, PyObject* args) {
    const char* rna;

    // Parse the input Python string into a C string
    if (!PyArg_ParseTuple(args, "s", &rna)) {
        return NULL;
    }

    int length = strlen(rna);
    printf("Input sequence: %s\n", rna);
    printf("The length of the RNA sequence: %d\n", length);

    // Create a Python list to hold the rows of the matrix
    PyObject* matrix = PyList_New(length);
    if (!matrix) {
        return NULL; // Memory allocation failed
    }

    // Create a C array to hold the matrix values
    int matrix_values[length][length];

    // Populate the matrix with values
    populate_matrix(rna, length, matrix_values);

    // Populate the Python list with the matrix values
    for (int i = 0; i < length; i++) {
        // Create a Python list to represent each row
        PyObject* row = PyList_New(length);
        if (!row) {
            Py_DECREF(matrix); // Clean up the matrix
            return NULL; // Memory allocation failed
        }

        for (int j = 0; j < length; j++) {
            // Convert the value to a Python integer
            PyObject* py_value = PyLong_FromLong(matrix_values[i][j]);
            if (!py_value) {
                Py_DECREF(row); // Clean up the row
                Py_DECREF(matrix); // Clean up the matrix
                return NULL; // Memory allocation failed
            }
            // Set the Python integer in the row list
            PyList_SET_ITEM(row, j, py_value);
        }

        // Set the row list in the matrix list
        PyList_SET_ITEM(matrix, i, row);
    }

    // Return the populated matrix list
    return matrix;
}

static struct PyMethodDef methods[] = {
    {"version", (PyCFunction)version, METH_NOARGS},
    {"fold", (PyCFunction)fold, METH_VARARGS, "Returns secondary structure of a nucleotide sequence"},
    {"gc_content", (PyCFunction)gc_content, METH_VARARGS, "GC percentage"},
    {"nussinov_matrix", (PyCFunction)create_matrix, METH_VARARGS, "Test"},
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