#ifndef _JERRYSCRIPT_MBED_LIB_ECHO_H
#define _JERRYSCRIPT_MBED_LIB_ECHO_H

#include "jerryscript-mbed-library-registry/wrap_tools.h"
#include "echo-js.h"

DECLARE_JS_WRAPPER_REGISTRATION (echo)
{
    REGISTER_CLASS_CONSTRUCTOR(Echo);
}

#endif // _JERRYSCRIPT_MBED_LIB_ECHO_H
