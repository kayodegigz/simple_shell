#include "main.h"

/**
 * print_errorr - prints error messages to standard error
 * @vars: pointer to struct of variables
 * @msg: message to print
 *
 * Return: void
 */
void print_errorr(vars_t *vars, char *msg)
{
        char *count;

        _putss2(vars->argv[0]);
        _putss2(": ");
        count = _uitoaa(vars->count);
        _putss2(count);
        free(count);
        _putss2(": ");
        _putss2(vars->av[0]);
        if (msg)
        {
                _putss2(msg);
        }
        else
                perror("");
}

/**
 * _putss2 - prints a string to standard error
 * @str: string to print
 *
 * Return: void
 */
void _putss2(char *str)
{
        ssize_t num, len;

        num = _strlenn(str);
        len = write(STDERR_FILENO, str, num);
        if (len != num)
        {
                perror("Fatal Error");
                exit(1);
        }

}

/**
 * _uitoaa - converts an unsigned int to a string
 * @count: unsigned int to convert
 *
 * Return: pointer to the converted string
 */
char *_uitoaa(unsigned int count)
{
        char *numstr;
        unsigned int tmp, digits;

        tmp = count;
        for (digits = 0; tmp != 0; digits++)
                tmp /= 10;
        numstr = malloc(sizeof(char) * (digits + 1));
        if (numstr == NULL)
        {
                perror("Fatal Error1");
                exit(127);
        }
        numstr[digits] = '\0';
        for (--digits; count; --digits)
        {
                numstr[digits] = (count % 10) + '0';
                count /= 10;
        }
        return (numstr);
}
