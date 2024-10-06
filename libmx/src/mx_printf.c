#include "../inc/libmx.h"

// A simplified version of mx_printf without va_list
void mx_printf(const char *format, const char *arg1, const char *arg2, const char *arg3) {
    int arg_index = 0;  // To track which argument is being used

    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%' && format[i + 1] != '\0') {
            i++;                     // Move past '%'
            const char *arg = NULL;  // Placeholder for the current argument

            // Get the current argument based on its index
            switch (arg_index) {
                case 0:
                    arg = arg1;
                    break;
                case 1:
                    arg = arg2;
                    break;
                case 2:
                    arg = arg3;
                    break;
                default:
                    arg = "";
                    break;  // No more arguments available
            }

            // Print argument based on format specifier
            switch (format[i]) {
                case 's': {
                    if (arg) mx_printstr(arg);  // Print string argument
                    break;
                }
                case 'd': {
                    int num = mx_atoi(arg);  // Convert string to int
                    mx_printint(num);
                    break;
                }
                case 'c': {
                    mx_printchar(arg[0]);  // Print first character of string
                    break;
                }
                case '%': {
                    mx_printchar('%');  // Handle %%
                    break;
                }
                default: {
                    // If an unknown specifier is found, print it literally
                    mx_printchar('%');
                    mx_printchar(format[i]);
                    break;
                }
            }
            arg_index++;  // Move to the next argument
        } else {
            // Normal character, print as is
            mx_printchar(format[i]);
        }
    }
}
