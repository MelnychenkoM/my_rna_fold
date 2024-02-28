#include <Python.h>
#include "rna_fold.h"

// Returns version and info about the module
static PyObject* version(PyObject* self){
    return PyUnicode_FromString("Test version");
};

// Nussinov algorithm for python
static PyObject* fold(PyObject* self, PyObject* args) {
    const char* input_str;

    if (!PyArg_ParseTuple(args, "s", &input_str)) {
        return NULL;
    }

    int length = strlen(input_str);
    char structure[length + 1];

    nussinov(input_str, structure);

    return PyUnicode_FromString(structure);
};

// GC content
static PyObject* gc_content(PyObject* self, PyObject* args) {

    const char* input_str;

    if (!PyArg_ParseTuple(args, "s", &input_str)) {
        return NULL;
    }
    
    double content = GC_content(input_str);
    
    PyObject* py_float = PyFloat_FromDouble(content);
    
    if (py_float == NULL) {
        return NULL;
    }

    return py_float;
}

/*
Return an upper triangular matrix populated with nussinov algorithm values.
e. g. M(1, 5) = 3 is the score for the (1, 5) subsequence.
The best score it at the top right corner with indexes M(0, N - 1) if 0-based indexing.
*/ 
static PyObject* create_matrix(PyObject* self, PyObject* args) {
    const char* rna;

    if (!PyArg_ParseTuple(args, "s", &rna)) {
        return NULL;
    }

    int length = strlen(rna);

    PyObject* matrix = PyList_New(length);
    if (!matrix) {
        return NULL;
    }

    int matrix_values[length][length];

    make_nussinov_matrix(rna, length, matrix_values);

    for (int i = 0; i < length; i++) {

        PyObject* row = PyList_New(length);
        if (!row) {
            Py_DECREF(matrix);
            return NULL;
        }

        for (int j = 0; j < length; j++) {

            PyObject* py_value = PyLong_FromLong(matrix_values[i][j]);
            if (!py_value) {
                Py_DECREF(row);
                Py_DECREF(matrix);
                return NULL;
            }

            PyList_SET_ITEM(row, j, py_value);
        }

        PyList_SET_ITEM(matrix, i, row);
    }

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
    "RNA fold",
    NULL,
    -1,
    methods
};

PyMODINIT_FUNC PyInit_rna_fold(void){
    return PyModule_Create(&module);
}