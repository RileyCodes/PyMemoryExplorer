#pragma once

#define pyPtr __int64

#define CO_MAXBLOCKS 20
#define freefunc pyPtr
#define destructor pyPtr
#define printfunc pyPtr
#define getattrfunc pyPtr
#define getattrofunc pyPtr
#define setattrfunc pyPtr
#define setattrofunc pyPtr
#define cmpfunc pyPtr
#define reprfunc pyPtr
#define hashfunc pyPtr
#define initproc pyPtr
#define newfunc pyPtr
#define allocfunc pyPtr
#define objobjproc pyPtr
#define visitproc pyPtr
#define traverseproc pyPtr
#define binaryfunc pyPtr
#define ternaryfunc pyPtr
#define inquiry pyPtr
#define lenfunc pyPtr
#define coercion pyPtr
#define ssizeargfunc pyPtr
#define ssizessizeargfunc pyPtr
#define intobjargproc pyPtr
#define intintobjargproc pyPtr
#define ssizeobjargproc pyPtr
#define ssizessizeobjargproc pyPtr
#define objobjargproc pyPtr
#define getreadbufferproc pyPtr
#define getwritebufferproc pyPtr
#define getsegcountproc pyPtr
#define getcharbufferproc pyPtr
#define readbufferproc pyPtr
#define writebufferproc pyPtr
#define segcountproc pyPtr
#define charbufferproc pyPtr
#define unaryfunc pyPtr
#define binaryfunc pyPtr
#define ternaryfunc pyPtr
#define inquiry pyPtr
#define lenfunc pyPtr
#define coercion pyPtr
#define ssizeargfunc pyPtr
#define ssizessizeargfunc pyPtr
#define intobjargproc pyPtr
#define intintobjargproc pyPtr
#define ssizeobjargproc pyPtr
#define ssizessizeobjargproc pyPtr
#define objobjargproc pyPtr
#define getreadbufferproc pyPtr
#define getwritebufferproc pyPtr
#define getsegcountproc pyPtr
#define getcharbufferproc pyPtr
#define readbufferproc pyPtr
#define writebufferproc pyPtr
#define segcountproc pyPtr
#define charbufferproc pyPtr


#ifdef PyObject_HEAD
int x = 0;
#endif 

#define PyDict_MINSIZE 8
#include "const.h"
#include <string>
#include <minwinbase.h>

typedef pyPtr Py_ssize_t;

#define PyObject_HEAD                   \
    Py_ssize_t ob_refcnt;               \
    pyPtr ob_type;

#define PyObject_VAR_HEAD               \
    PyObject_HEAD                       \
    Py_ssize_t ob_size; /* Number of items in variable part */

typedef struct  {
	PyObject_HEAD
} PyObject;
typedef struct _is {

	pyPtr next;
	pyPtr tstate_head;

	pyPtr modules;
	pyPtr sysdict;
	pyPtr builtins;
	pyPtr modules_reloading;

	pyPtr codec_search_path;
	pyPtr codec_search_cache;
	pyPtr codec_error_registry;

#ifdef HAVE_DLOPEN
	int dlopenflags;
#endif
#ifdef WITH_TSC
	int tscdump;
#endif

} PyInterpreterState;


typedef struct _ts {
	/* See Python/ceval.c for comments explaining most fields */

	pyPtr next;
	pyPtr interp;

	pyPtr frame;
	int recursion_depth;
	/* 'tracing' keeps track of the execution depth when tracing/profiling.
	   This is to prevent the actual trace/profile code from being recorded in
	   the trace/profile. */
	int tracing;
	int use_tracing;

	pyPtr c_profilefunc;
	pyPtr c_tracefunc;
	pyPtr c_profileobj;
	pyPtr c_traceobj;

	pyPtr curexc_type;
	pyPtr curexc_value;
	pyPtr curexc_traceback;

	pyPtr exc_type;
	pyPtr exc_value;
	pyPtr exc_traceback;

	pyPtr dict;  /* Stores per-thread state */

	/* tick_counter is incremented whenever the check_interval ticker
	 * reaches zero. The purpose is to give a useful measure of the number
	 * of interpreted bytecode instructions in a given thread.  This
	 * extremely lightweight statistic collector may be of interest to
	 * profilers (like psyco.jit()), although nothing in the core uses it.
	 */
	int tick_counter;

	int gilstate_counter;

	pyPtr async_exc; /* Asynchronous exception to raise */
	long thread_id; /* Thread id where this tstate was created */

	int trash_delete_nesting;
	pyPtr trash_delete_later;

	/* XXX signal handlers should also be here */

} PyThreadState;


typedef struct {
    int b_type;			/* what kind of block this is */
    int b_handler;		/* where to jump to find handler */
    int b_level;		/* value stack level to pop to */
} PyTryBlock;




typedef struct {
	/* Cached hash code of me_key.  Note that hash codes are C longs.
	* We have to use Py_ssize_t instead because dict_popitem() abuses
	* me_hash to hold a search finger.
	*/
	Py_ssize_t me_hash;
    pyPtr me_key;
    pyPtr me_value;
} PyDictEntry;

typedef struct _dictobject PyDictObject;
struct _dictobject {
	PyObject_HEAD
	Py_ssize_t ma_fill;  /* # Active + # Dummy */
	Py_ssize_t ma_used;  /* # Active */

						 /* The table contains ma_mask + 1 slots, and that's a power of 2.
						 * We store the mask instead of the size because the mask is more
						 * frequently needed.
						 */
	Py_ssize_t ma_mask;

	/* ma_table points to ma_smalltable for small tables, else to
	* additional malloc'ed memory.  ma_table is never NULL!  This rule
	* saves repeated runtime null-tests in the workhorse getitem and
	* setitem calls.
	*/
    pyPtr ma_table;
	pyPtr ma_lookup;
	PyDictEntry ma_smalltable[PyDict_MINSIZE];
};


typedef struct {
	PyObject_HEAD
    pyPtr di_dict; /* Set to NULL when iterator is exhausted */
	Py_ssize_t di_used;
	Py_ssize_t di_pos;
    pyPtr di_result; /* reusable result tuple for iteritems */
	Py_ssize_t len;
} dictiterobject;


typedef struct {
	PyObject_HEAD
    pyPtr cl_bases;	/* A tuple of class objects */
    pyPtr cl_dict;	/* A dictionary */
    pyPtr cl_name;	/* A string */
							/* The following three are functions or NULL */
    pyPtr cl_getattr;
    pyPtr cl_setattr;
    pyPtr cl_delattr;
	pyPtr    cl_weakreflist; /* List of weak references */
} PyClassObject;

typedef struct {
	PyObject_HEAD
	pyPtr in_class;	/* The class object */
	pyPtr in_dict;	/* A dictionary */
	pyPtr in_weakreflist; /* List of weak references */
} PyInstanceObject;

typedef struct {
	PyObject_VAR_HEAD
    pyPtr ob_item[1];

	/* ob_item contains space for 'ob_size' elements.
	* Items must normally not be NULL, except during construction when
	* the tuple is not yet visible outside the function that builds it.
	*/
} PyTupleObject;


typedef struct {
	PyObject_VAR_HEAD
	long ob_shash;
	int ob_sstate;
	char ob_sval[1];


	/* Invariants:
	*     ob_sval contains space for 'ob_size+1' elements.
	*     ob_sval[ob_size] == 0.
	*     ob_shash is the hash of the string or -1 if not computed yet.
	*     ob_sstate != 0 iff the string object is in stringobject.c's
	*       'interned' dictionary; in this case the two references
	*       from 'interned' to this object are *not counted* in ob_refcnt.
	*/
} PyStringObject;

#define freefunc int



struct PyTypeObject2 {
	PyObject_VAR_HEAD
		pyPtr tp_name; /* For printing, in format "<module>.<name>" */

};


struct PyTypeObject {
	PyObject_VAR_HEAD
		pyPtr tp_name; /* For printing, in format "<module>.<name>" */
	Py_ssize_t tp_basicsize, tp_itemsize; /* For allocation */

										  /* Methods to implement standard operations */

	destructor tp_dealloc;
	printfunc tp_print;
	getattrfunc tp_getattr;
	setattrfunc tp_setattr;
	cmpfunc tp_compare;
	reprfunc tp_repr;

	/* Method suites for standard classes */

	pyPtr tp_as_number;
	pyPtr tp_as_sequence;
	pyPtr tp_as_mapping;

	/* More standard operations (here for binary compatibility) */

	hashfunc tp_hash;
	ternaryfunc tp_call;
	reprfunc tp_str;
	getattrofunc tp_getattro;
	setattrofunc tp_setattro;

	/* Functions to access object as input/output buffer */
	pyPtr tp_as_buffer;

	/* Flags to define presence of optional/expanded features */
	long tp_flags;

	pyPtr tp_doc; /* Documentation string */

						/* Assigned meaning in release 2.0 */
						/* call function for all accessible objects */
	traverseproc tp_traverse;

	/* delete references to contained objects */
	inquiry tp_clear;

	/* Assigned meaning in release 2.1 */
	/* rich comparisons */
	pyPtr tp_richcompare;

	/* weak reference enabler */
	Py_ssize_t tp_weaklistoffset;

	/* Added in release 2.2 */
	/* Iterators */
	pyPtr tp_iter;
	pyPtr tp_iternext;



	/* Attribute descriptor and subclassing stuff */
	pyPtr tp_methods;
	pyPtr tp_members;
	pyPtr tp_getset;
	pyPtr tp_base;
    pyPtr tp_dict;
	pyPtr tp_descr_get;
	pyPtr tp_descr_set;
	Py_ssize_t tp_dictoffset;
	initproc tp_init;
	allocfunc tp_alloc;
	newfunc tp_new;
	freefunc tp_free; /* Low-level free-memory routine */
	inquiry tp_is_gc; /* For PyObject_IS_GC */
    pyPtr tp_bases;
    pyPtr tp_mro; /* method resolution order */
    pyPtr tp_cache;
    pyPtr tp_subclasses;
    pyPtr tp_weaklist;
	destructor tp_del;

	/* Type attribute cache version tag. Added in version 2.6 */
	unsigned int tp_version_tag;

//#ifdef COUNT_ALLOCS
//	/* these must be last and never explicitly initialized */
//	Py_ssize_t tp_allocs;
//	Py_ssize_t tp_frees;
//	Py_ssize_t tp_maxalloc;
//	struct _typeobject *tp_prev;
//	struct _typeobject *tp_next;
//#endif
} ;

#define PY_UNICODE_TYPE wchar_t

typedef PY_UNICODE_TYPE Py_UNICODE;


typedef struct {
	PyObject_HEAD
		Py_ssize_t length;          /* Length of raw Unicode data in buffer */
	pyPtr str;            /* Raw Unicode buffer */
	long hash;                  /* Hash value; -1 if not set */
    pyPtr defenc;           /* (Default) Encoded version as Python
								string, or NULL; this is used for
								implementing the buffer protocol */
} PyUnicodeObject;

typedef unsigned int digit;

struct _longobject {
	PyObject_VAR_HEAD
		digit ob_digit[20];
};



typedef struct {
	PyObject_VAR_HEAD
		/* Vector of pointers to list elements.  list[0] is ob_item[0], etc. */
	pyPtr ob_item;

	/* ob_item contains space for 'allocated' elements.  The number
	* currently in use is ob_size.
	* Invariants:
	*     0 <= ob_size <= allocated
	*     len(list) == ob_size
	*     ob_item == NULL implies ob_size == allocated == 0
	* list.sort() temporarily sets allocated to -1 to detect mutations.
	*
	* Items must normally not be NULL, except during construction when
	* the list is not yet visible outside the function that builds it.
	*/
	Py_ssize_t allocated;
} PyListObject;

typedef struct _longobject PyLongObject; /* Revealed in longintrepr.h */

typedef struct {
	PyObject_HEAD
		double ob_fval;
} PyFloatObject;

typedef struct {
	PyObject_HEAD
		long ob_ival;
} PyIntObject;


typedef union _gc_head {

	struct {
		pyPtr gc_next;
		pyPtr gc_prev;
		Py_ssize_t gc_refs;
	} gc;
	long double dummy;  /* force worst-case alignment */
} PyGC_Head;

struct gc_generation {
	PyGC_Head head;
	int threshold; /* collection threshold */
	int count; /* count of allocations or collections of younger
			   generations */
};

struct test
{
	int aa = 5;
};

#define SIZEOF_SHORT 2
#define SIZEOF_INT 4
#define SIZEOF_LONG 4
#define SIZEOF_LONG_LONG 8
#define SIZEOF_DOUBLE 8
#define SIZEOF_FLOAT 4
#define PyLong_SHIFT	30
#define PyLong_BASE	((digit)1 << PyLong_SHIFT)
#define PyLong_MASK	((digit)(PyLong_BASE - 1))
#	define PY_LONG_LONG __int64




void static PyLong_FromLongLong(PY_LONG_LONG ival, PyLongObject *v)
{
    
    unsigned PY_LONG_LONG abs_ival;
    unsigned PY_LONG_LONG t;  /* unsigned so >> doesn't propagate sign bit */
    int ndigits = 0;
    int negative = 0;

    if (ival < 0) {
        /* avoid signed overflow on negation;  see comments
           in PyLong_FromLong above. */
        abs_ival = (unsigned PY_LONG_LONG)(-1 - ival) + 1;
        negative = 1;
    }
    else {
        abs_ival = (unsigned PY_LONG_LONG)ival;
    }

    /* Count the number of Python digits.
       We used to pick 5 ("big enough for anything"), but that's a
       waste of time and space given that 5*15 = 75 bits are rarely
       needed. */
    t = abs_ival;
    while (t) {
        ++ndigits;
        t >>= PyLong_SHIFT;
    }
    //v = _PyLong_New(ndigits);
    if (v != NULL) {
        digit *p = v->ob_digit;
        v->ob_size = negative ? -ndigits : ndigits;
        t = abs_ival;
        while (t) {
            *p++ = (digit)(t & PyLong_MASK);
            t >>= PyLong_SHIFT;
        }
    }
    return ;
}

static long __forceinline int_hash(PyIntObject *v)
{
    /* XXX If this is changed, you also need to change the way
       Python's long, float and complex types are hashed. */
    long x = v->ob_ival;
    if (x == -1)
        x = -2;
    return x;
}

static long __forceinline long_hash(PyLongObject *v)
{
    unsigned long x;
    Py_ssize_t i;
    int sign;

    /* This is designed so that Python ints and longs with the
       same value hash to the same value, otherwise comparisons
       of mapping keys will turn out weird */
    i = v->ob_size;
    sign = 1;
    x = 0;
    if (i < 0) {
        sign = -1;
        i = -(i);
    }
    /* The following loop produces a C unsigned long x such that x is
       congruent to the absolute value of v modulo ULONG_MAX.  The
       resulting x is nonzero if and only if v is. */
    while (--i >= 0) {
        /* Force a native long #-bits (32 or 64) circular shift */
        x = (x >> (8 * SIZEOF_LONG - PyLong_SHIFT)) | (x << PyLong_SHIFT);
        x += v->ob_digit[i];
        /* If the addition above overflowed we compensate by
           incrementing.  This preserves the value modulo
           ULONG_MAX. */
        if (x < v->ob_digit[i])
            x++;
    }
    x = x * sign;
    if (x == (unsigned long)-1)
        x = (unsigned long)-2;
    return (long)x;
}




static long __forceinline string_hash(std::string string_to_hash)
{
    register Py_ssize_t len;
    register unsigned char *p;
    register long x;

#ifdef Py_DEBUG
    assert(_Py_HashSecret_Initialized);
#endif
    
    len = string_to_hash.length();
    /*
      We make the hash of the empty string be 0, rather than using
      (prefix ^ suffix), since this slightly obfuscates the hash secret
    */
    if (len == 0) {
        return 0;
    }
    p = (unsigned char *)string_to_hash.c_str();
    x = 0; // _Py_HashSecret.prefix;
    x ^= *p << 7;
    while (--len >= 0)
        x = (1000003 * x) ^ *p++;
    x ^= string_to_hash.length();
    x ^= 0;//_Py_HashSecret.suffix;
    if (x == -1)
        x = -2;
    return x;
}