
#include "jerryscript-mbed-library-registry/wrap_tools.h"

#include "echo-js.h"
#include "echo.h"

#include <string>

/**
 * Echo#destructor
 *
 * Called if/when the Echo is GC'ed.
 */
void NAME_FOR_CLASS_NATIVE_DESTRUCTOR(Echo)(void* void_ptr) {
    delete static_cast<Echo*>(void_ptr);
}

/**
 * Type infomation of the native Echo pointer
 *
 * Set Echo#destructor as the free callback.
 */
static const jerry_object_native_info_t native_obj_type_info = {
    .free_cb = NAME_FOR_CLASS_NATIVE_DESTRUCTOR(Echo)
};

/**
 * Echo#echoInt (native JavaScript method)
 *
 * Return value back to caller
 *
 * @param value of interger
 * @returns integer from param
 */
DECLARE_CLASS_FUNCTION(Echo, echoInt) {
    CHECK_ARGUMENT_COUNT(Echo, echoInt, (args_count == 1));
    CHECK_ARGUMENT_TYPE_ALWAYS(Echo, echoInt, 0, number);

    // Extract native Echo pointer
    void* void_ptr;
    const jerry_object_native_info_t* type_ptr;
    bool has_ptr = jerry_get_object_native_pointer(this_obj, &void_ptr, &type_ptr);

    if (!has_ptr || type_ptr != &native_obj_type_info) {
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  (const jerry_char_t *) "Failed to get native Echo pointer");
    }

    Echo* native_ptr = static_cast<Echo*>(void_ptr);

    int arg0 = jerry_get_number_value(args[0]);

    int result = native_ptr->echoInt(arg0);
    return jerry_create_number(result);
}

/**
 * Echo#echoNumCalls (native JavaScript method)
 *
 * Return number of calls to echoInt
 *
 * @returns integer num calls to echoInt
 */
DECLARE_CLASS_FUNCTION(Echo, getNumCalls) {
    CHECK_ARGUMENT_COUNT(Echo, getNumCalls, (args_count == 0));

    // Extract native Echo pointer
    void* void_ptr;
    const jerry_object_native_info_t* type_ptr;
    bool has_ptr = jerry_get_object_native_pointer(this_obj, &void_ptr, &type_ptr);

    if (!has_ptr || type_ptr != &native_obj_type_info) {
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  (const jerry_char_t *) "Failed to get native Echo pointer");
    }

    Echo* native_ptr = static_cast<Echo*>(void_ptr);

    int result = native_ptr->getNumCalls();
    return jerry_create_number(result);
}

/**
 * Echo#getNameOfClass (native JavaScript method)
 *
 * Return string with name of class
 *
 * @returns string with name of class
 */
DECLARE_CLASS_FUNCTION(Echo, getNameOfClass) {
    CHECK_ARGUMENT_COUNT(Echo, getNameOfClass, (args_count == 0));

    // Extract native Echo pointer
    void* void_ptr;
    const jerry_object_native_info_t* type_ptr;
    bool has_ptr = jerry_get_object_native_pointer(this_obj, &void_ptr, &type_ptr);

    if (!has_ptr || type_ptr != &native_obj_type_info) {
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  (const jerry_char_t *) "Failed to get native Echo pointer");
    }

    Echo* native_ptr = static_cast<Echo*>(void_ptr);

    const jerry_char_t *result = (const jerry_char_t *) native_ptr->getNameOfClass().c_str();
    return jerry_create_string(  result );
}

/**
 * Echo#printString (native JavaScript method)
 *
 * Print string from c printf
 *
 * @param string to print
 * 
 */
DECLARE_CLASS_FUNCTION(Echo, printString) {
    CHECK_ARGUMENT_COUNT(Echo, printString, (args_count == 1));
    CHECK_ARGUMENT_TYPE_ALWAYS(Echo, printString, 0, string );

    // Extract native Echo pointer
    void* void_ptr;
    const jerry_object_native_info_t* type_ptr;
    bool has_ptr = jerry_get_object_native_pointer(this_obj, &void_ptr, &type_ptr);

    if (!has_ptr || type_ptr != &native_obj_type_info) {
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  (const jerry_char_t *) "Failed to get native Echo pointer");
    }

    Echo* native_ptr = static_cast<Echo*>(void_ptr);

    jerry_char_t buffer[100];
    int res;
    int size = (int) jerry_get_string_size(args[0]);

    if(  size < 100 )
    {
         res = jerry_string_to_char_buffer( args[0], buffer, 100 );
         buffer[size] = '\0';
    }

    if( res == size )
    {
        native_ptr->printString((const char *)buffer, size );
    }
    else
    {
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  (const jerry_char_t *) "Failed to convert string");
    }

    return jerry_create_undefined();
}
/**
 * Echo (native JavaScript constructor)
 *
 * @returns a JavaScript object representing a Echo.
 */
DECLARE_CLASS_CONSTRUCTOR(Echo) {
    //CHECK_ARGUMENT_COUNT(Echo, __constructor, args_count ==  0);

    Echo* native_ptr;

   
    native_ptr = new Echo();    

    // create the jerryscript object
    jerry_value_t js_object = jerry_create_object();
    jerry_set_object_native_pointer(js_object, native_ptr, &native_obj_type_info);

    // attach methods
    ATTACH_CLASS_FUNCTION(js_object, Echo, echoInt);
    ATTACH_CLASS_FUNCTION(js_object, Echo, getNumCalls);
    ATTACH_CLASS_FUNCTION(js_object, Echo, getNameOfClass);
    ATTACH_CLASS_FUNCTION(js_object, Echo, printString);

    return js_object;
}
