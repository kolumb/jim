#include <stdio.h>

#define JIM_IMPLEMENTATION
#include "./jim.h"

int main()
{
    Jim jim = {
        .sink = stdout,
        .write = (Jim_Write) fwrite,
    };

    jim_object_begin(&jim);
        jim_member_key(&jim, "null", NULL);
        jim_null(&jim);

        jim_member_key(&jim, "bool", NULL);
        jim_array_begin(&jim);
            jim_bool(&jim, 0);
            jim_bool(&jim, 1);
        jim_array_end(&jim);

        jim_member_key(&jim, "integers", NULL);
        jim_array_begin(&jim);
            for (int i = -3; i <= 3; ++i) {
                jim_integer(&jim, i);
            }
        jim_array_end(&jim);

        jim_member_key(&jim, "floats", NULL);
        jim_array_begin(&jim);
            jim_float(&jim, 3.1415, 4);
            jim_float(&jim, 2.71828, 5);
            jim_float(&jim, 1.6180, 4);
        jim_array_end(&jim);

        jim_member_key(&jim, "string", NULL);
        jim_array_begin(&jim);
            jim_string(&jim, "Hello\tWorld\n", NULL);
            unsigned int size = 4;
            jim_string(&jim, "\0\0\0\0", &size);
        jim_array_end(&jim);
    jim_object_end(&jim);

    if (jim.error != JIM_OK) {
        fprintf(stderr, "ERROR: could not serialize json properly: %s\n",
                jim_error_string(jim.error));
        return -1;
    }

    return 0;
}