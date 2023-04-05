#include <stdio.h>
#include <stdarg.h> // for va_list and va_arg

int _printf(const char* format, ...) {
    va_list args; // declare a variable of type va_list to hold the variable argument list
    va_start(args, format); // initialize the va_list with the last fixed argument

    int num_chars_printed = 0; // initialize the counter for number of characters printed
    char ch; // declare a variable to hold each character of the format string
    while ((ch = *format++) != '\0') { // iterate over each character of the format string
        if (ch != '%') { // if the current character is not a conversion specifier
            putchar(ch); // print the character to stdout
            num_chars_printed++;
        }
        else { // if the current character is a conversion specifier
            ch = *format++; // get the next character after the '%'
            switch (ch) {
                case 'c': {
                    char c = (char) va_arg(args, int); // retrieve the next argument as a char
                    putchar(c); // print the char to stdout
                    num_chars_printed++;
                    break;
                }
                case 's': {
                    char* s = va_arg(args, char*); // retrieve the next argument as a string
                    while (*s != '\0') { // iterate over each character of the string
                        putchar(*s); // print the character to stdout
                        s++;
                        num_chars_printed++;
                    }
                    break;
                }
                case 'd':
                case 'i': {
                    int num = va_arg(args, int); // retrieve the next argument as an int
                    if (num < 0) { // handle negative numbers
                        putchar('-');
                        num = -num;
                        num_chars_printed++;
                    }
                    int div = 1;
                    while (num / div >= 10) { // calculate the divisor to extract each digit of the number
                        div *= 10;
                    }
                    while (div > 0) { // extract each digit of the number and print it to stdout
                        int digit = num / div;
                        putchar(digit + '0');
                        num = num % div;
                        div /= 10;
                        num_chars_printed++;
                    }
                    break;
                }
                case '%': {
                    putchar(ch); // print a '%' character to stdout
                    num_chars_printed++;
                    break;
                }
                default: {
                    putchar('%'); // print the '%' character followed by the invalid specifier character to stdout
                    putchar(ch);
                    num_chars_printed += 2;
                    break;
                }
            }
        }
    }

    va_end(args); // clean up the va_list
    return num_chars_printed;
}
