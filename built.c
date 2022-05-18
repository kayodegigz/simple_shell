#include "main.h"

/**
 * check_for_builtinss - checks if the command is a builtin
 * @vars: variables
 * Return: pointer to the function or NULL
 */
void (*check_for_builtinss(vars_t *vars))(vars_t *vars)
{
        unsigned int i;
        builtins_t check[] = {
                {"exit", new_exitt},
                {"env", _envv},
                {"setenv", new_setenvv},
                {"unsetenv", new_unsetenvv},
                {NULL, NULL}
        };

        for (i = 0; check[i].f != NULL; i++)
        {
                if (_strcmprr(vars->av[0], check[i].name) == 0)
                        break;
        }
        if (check[i].f != NULL)
                check[i].f(vars);
        return (check[i].f);
}

/**
 * new_exitt - exit program
 * @vars: variables
 * Return: void
 */
void new_exitt(vars_t *vars)
{
        int status;

        if (_strcmprr(vars->av[0], "exit") == 0 && vars->av[1] != NULL)
        {
                status = _atoii(vars->av[1]);
                if (status == -1)
                {
                        vars->status = 2;
                        print_errorr(vars, ": Illegal number: ");
                        _putss2(vars->av[1]);
                        _putss2("\n");
                        free(vars->commands);
                        vars->commands = NULL;
                        return;
                }
                vars->status = status;
        }
        free(vars->buffer);
        free(vars->av);
        free(vars->commands);
        free_envv(vars->env);
        exit(vars->status);
}

/**
 * _envv - prints the current environment
 * @vars: struct of variables
 * Return: void.
 */
void _envv(vars_t *vars)
{
        unsigned int i;

        for (i = 0; vars->env[i]; i++)
        {
                _putss(vars->env[i]);
                _putss("\n");
        }
        vars->status = 0;
}

/**
 * new_setenvv - create a new environment variable, or edit an existing variable
 * @vars: pointer to struct of variables
 *
 * Return: void
 */
void new_setenvv(vars_t *vars)
{
        char **key;
        char *var;

        if (vars->av[1] == NULL || vars->av[2] == NULL)
        {
                print_errorr(vars, ": Incorrect number of arguments\n");
                vars->status = 2;
                return;
        }
        key = find_keyy(vars->env, vars->av[1]);
        if (key == NULL)
                add_keyy(vars);
        else
        {
                var = add_valuee(vars->av[1], vars->av[2]);
                if (var == NULL)
                {
                        print_errorr(vars, NULL);
                        free(vars->buffer);
                        free(vars->commands);
                        free(vars->av);
                        free_envv(vars->env);
			exit(127);
                }
                free(*key);
                *key = var;
        }
        vars->status = 0;
}

/**
 * new_unsetenvv - remove an environment variable
 * @vars: pointer to a struct of variables
 *
 * Return: void
 */
void new_unsetenvv(vars_t *vars)
{
        char **key, **newenv;

        unsigned int i, j;

        if (vars->av[1] == NULL)
        {
                print_errorr(vars, ": Incorrect number of arguments\n");
                vars->status = 2;
                return;
        }
        key = find_keyy(vars->env, vars->av[1]);
        if (key == NULL)
        {
                print_errorr(vars, ": No variable to unset");
                return;
        }
        for (i = 0; vars->env[i] != NULL; i++)
                ;
        newenv = malloc(sizeof(char *) * i);
        if (newenv == NULL)
	{
                print_errorr(vars, NULL);
                vars->status = 127;
                new_exitt(vars);
        }
        for (i = 0; vars->env[i] != *key; i++)
                newenv[i] = vars->env[i];
        for (j = i + 1; vars->env[j] != NULL; j++, i++)
                newenv[i] = vars->env[j];
        newenv[i] = NULL;
        free(*key);
        free(vars->env);
        vars->env = newenv;
        vars->status = 0;
}
