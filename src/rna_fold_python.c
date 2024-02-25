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

static struct PyMethodDef methods[] = {
    {"version", (PyCFunction)version, METH_NOARGS},
    {"fold", (PyCFunction)fold, METH_VARARGS, "Returns secondary structure of a nucleotide sequence"},
    {"gc_content", (PyCFunction)gc_content, METH_VARARGS, "GC percentage"},
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