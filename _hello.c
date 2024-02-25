#include<Python.h>

static PyObject* _hello_world(PyObject* self){
    return PyUnicode_FromString("Hello World!");
}

static PyObject* _hello(PyObject* self, PyObject* args){
    PyObject* name;
    if (!PyArg_ParseTuple(args, "U", &name) ){
        return NULL;
    }

}


static struct PyMethodDef methods[] = {
    {"r", (PyCFunction)_hello_world, METH_NOARGS},
    {"hello", (PyCFunction)_hello, METH_VARARGS},
    {NULL, NULL}
};

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "_hello",
    NULL,
    -1,
    methods
};

PyMODINIT_FUNC PyInit__hello(void){
    return PyModule_Create(&module);
}