#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>

/**
 * struct variables - variables
 * @av: command line arguments
 * @buffer: buffer of command
 * @env: environment variables
 * @count: count of commands entered
 * @argv: arguments at opening of shell
 * @status: exit status
 * @commands: commands to execute
 */
typedef struct variables
{
	char **av;
	char *buffer;
	char **env;
	size_t count;
	char **argv;
	int status;
	char **commands;
} vars_t;

/**
 * struct builtins - struct for the builtin functions
 * @name: name of builtin command
 * @f: function for corresponding builtin
 */
typedef struct builtins
{
	char *name;
	void (*f)(vars_t *);
} builtins_t;

char **make_envv(char **env);
void free_envv(char **env);

ssize_t _putss(char *str);
char *_strdupp(char *strtodup);
int _strcmprr(char *strcmp1, char *strcmp2);
char *_strcatt(char *strc1, char *strc2);
unsigned int _strlenn(char *str);

char **token(char *buffer, char *delimiter);
char **_reallocc(char **ptr, size_t *size);
char *new_strtokk(char *str, const char *delim);

void (*check_for_builtinss(vars_t *vars))(vars_t *vars);
void new_exitt(vars_t *vars);
void _envv(vars_t *vars);
void new_setenvv(vars_t *vars);
void new_unsetenvv(vars_t *vars);

void add_keyy(vars_t *vars);
char **find_keyy(char **env, char *key);
char *add_valuee(char *key, char *value);
int _atoii(char *str);

void check_for_pathh(vars_t *vars);
int path_executee(char *command, vars_t *vars);
char *find_pathh(char **env);
int execute_cwdd(vars_t *vars);
int check_for_dirr(char *str);

void print_errorr(vars_t *vars, char *msg);
void _putss2(char *str);
char *_uitoaa(unsigned int count);

#endif
