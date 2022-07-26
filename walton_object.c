/// The C structure to hold the data for a Walton object.
typedef struct
{
    PyObject_HEAD

    PyObject*   first;
    PyObject*   last;
    double      height;
    int         number;
} WaltonObject;



/// The definition of the members of Walton objects.
/// The members with getters and setters are not listed here (first & last).
static PyMemberDef waltonMembers[] =
{
    {"height", T_DOUBLE, offsetof(WaltonObject, height), 0, "Height (m)."},
    {"number", T_INT, offsetof(WaltonObject, number), 0, "Custom number."},
    {NULL}  /* Sentinel */
};



/// Getter for the first member.
static PyObject*  waltonGetFirst
(
    WaltonObject*   self,
    void*           closure
)
{
    Py_INCREF(self->first);
    return self->first;
}



/// Setter for the first member.
static int waltonSetFirst
(
    WaltonObject*   self,
    PyObject*       value,
    void*           closure
)
{
    PyObject *tmp;
    if (value == NULL)
    {
        PyErr_SetString(PyExc_TypeError, "Cannot delete the first attribute");
        return -1;
    }
    if (!PyUnicode_Check(value))
    {
        PyErr_SetString(PyExc_TypeError, "The first attribute value must be a string");
        return -1;
    }
    tmp = self->first;
    Py_INCREF(value);
    self->first = value;
    Py_DECREF(tmp);
    return 0;
}



/// Getter for the last member.
static PyObject* waltonGetLast
(
    WaltonObject*   self,
    void*           closure
)
{
    Py_INCREF(self->last);
    return self->last;
}



/// Setter for the first member.
static int waltonSetLast
(
    WaltonObject*   self,
    PyObject*       value,
    void*           closure
)
{
    PyObject *tmp;
    if (value == NULL)
    {
        PyErr_SetString(PyExc_TypeError, "Cannot delete the last attribute");
        return -1;
    }
    if (!PyUnicode_Check(value))
    {
        PyErr_SetString(PyExc_TypeError, "The last attribute value must be a string");
        return -1;
    }
    tmp = self->last;
    Py_INCREF(value);
    self->last = value;
    Py_DECREF(tmp);
    return 0;
}



/// Definition of the setters for the Walton objects.
static PyGetSetDef waltonGetSetters[] =
{
    {"first", (getter)waltonGetFirst, (setter)waltonSetFirst, "First name.", NULL},
    {"last", (getter)waltonGetLast, (setter)waltonSetLast, "Last name.", NULL},
    {NULL}  /* Sentinel */
};



/// Method to release the Walton object.
static void waltonDealloc
(
    WaltonObject* self
)
{
    Py_XDECREF(self->first);
    Py_XDECREF(self->last);
    Py_TYPE(self)->tp_free((PyObject*)self);
}



/// Method to create a new Walton object.
static PyObject* waltonNew
(
    PyTypeObject*   type,
    PyObject*       args,
    PyObject*       kwds
)
{
    WaltonObject* self;
    self = (WaltonObject*)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->first = PyUnicode_FromString("");
        if (self->first == NULL)
        {
            Py_DECREF(self);
            return NULL;
        }
        self->last = PyUnicode_FromString("");
        if (self->last == NULL)
        {
            Py_DECREF(self);
            return NULL;
        }
        self->height = 1.0;
        self->number = 0;
    }
    return (PyObject*) self;
}



/// Method to initialise a Walton object.
static int waltonInit
(
    WaltonObject*   self,
    PyObject*       args,
    PyObject*       kwds
)
{
    static char *kwlist[] = {"first", "last", "height", "number", NULL};
    PyObject *first = NULL, *last = NULL, *tmp;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|UUdi", kwlist, &first, &last, &self->height, &self->number))
    {
        return -1;
    }

    if (first)
    {
        tmp = self->first;
        Py_INCREF(first);
        self->first = first;
        Py_XDECREF(tmp);
    }
    if (last)
    {
        tmp = self->last;
        Py_INCREF(last);
        self->last = last;
        Py_XDECREF(tmp);
    }
    return 0;
}



/// The name method of the Walton object.
static PyObject* waltonName
(
    WaltonObject*   self,
    PyObject*       Py_UNUSED(ignored)
)
{
    if (self->first == NULL)
    {
        PyErr_SetString(PyExc_AttributeError, "first");
        return NULL;
    }
    if (self->last == NULL)
    {
        PyErr_SetString(PyExc_AttributeError, "last");
        return NULL;
    }
    return PyUnicode_FromFormat("%S %S", self->first, self->last);
}



/// Defintion of the methods of the Walton object.
static PyMethodDef waltonMethods[] =
{
    {"name", (PyCFunction)waltonName, METH_NOARGS, "Return the name, combining the first and last name." },
    {NULL}  /* Sentinel */
};



static PyTypeObject waltonType =
{
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "walton_module.Walton",
    .tp_doc = PyDoc_STR("Description of Walton objects."),
    .tp_basicsize = sizeof(WaltonObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = waltonNew,
    .tp_init = (initproc)waltonInit,
    .tp_dealloc = (destructor)waltonDealloc,
    .tp_members = waltonMembers,
    .tp_methods = waltonMethods,
    .tp_getset = waltonGetSetters,
};
