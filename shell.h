#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

extern char **env;

/**
 * struct data - struct that contains all relevant data on runtime
 * @_argv: argument vector
 * @input: command line written by the user
 * @_argc: tokens of the command line
 * @status: last shell status
 * @count: counts numbe rof lines
 * @_env: environment variable
 * @pid: process ID of the shell
 */
typedef struct data
{
	char **_argv;
	char *input;
	int count;
	char *pid;
	char **_args;
	int stat;
	char **_env;
} _shell;
/**
 * struct seperator_list - linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct seperator_list
{
	char seperator;
	struct seperator_list *next;
} sept_list;
/**
 * struct line_list - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct line_list
{
	char *line;
	struct line_list *next;
} l_list;

/**
 * struct var_list - single linked list
 * @var_len: length of the variable
 * @var_v: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct var_list
{
	int var_len;
	int len_val;
	char *var_v;
	struct var_list *next;
}_var;

/**
 * struct builtin - Builtin struct for command args.
 * @det: details of command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct builtin
{
	char *det;
	int (*f)(_shell *datashell);
} _builtin;

sept_list *add_sep_node_end(sept_list **head, char seperate);
void free_sept_list(sept_list **head);
l_list *add_line_node_end(l_list **head, char *line);
void free_l_list(l_list **head);

/* aux_lists2.c */
_var *add_rvar_node(_var **head, int lvar, char *var, int lval);
void free_rvar_list(_var **head);

/* aux_str functions */
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);

/* aux_mem.c */
void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);

/* aux_str2.c */
char *_strdup(const char *s);
int _strlen(const char *s);
int cmp_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);

/* aux_str3.c */
void rev_string(char *s);

/* check_syntax_error.c */
int repeated_char(char *input, int i);
int error_sep_op(char *input, int i, char last);
int first_char(char *input, int *i);
void print_syntax_error(_shell *datashell, char *input, int i, int bool);
int check_syntax_error(_shell *datashell, char *input);

/* shell_loop.c */
char *without_comment(char *in);
void shell_loop(_shell *datashell);

/* read_line.c */
char *read_line(int *i_eof);

/* split.c */
char *swap_char(char *input, int bool);
void add_nodes(sept_list **head_s, l_list **head_l, char *input);
void go_next(sept_list **list_s, l_list **list_l, _shell *datashell);
int split_commands(_shell *datashell, char *input);
char **split_line(char *input);

/* rep_var.c */
void check_env(_var **h, char *in, _shell *data);
int check_vars(_var **h, char *in, char *st, _shell *data);
char *replaced_input(_var **head, char *input, char *new_input, int nlen);
char *rep_var(char *input, _shell *datashell);

/* get_line.c */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);

/* exec_line */
int exec_line(_shell *datashell);

/* cmd_exec.c */
int is_cdir(char *path, int *i);
char *_which(char *cmd, char **_env);
int is_executable(_shell *datashell);
int check_error_cmd(char *dir, _shell *datashell);
int cmd_exec(_shell *datashell);

/* env1.c */
char *_getenv(const char *name, char **_env);
int _env(_shell *datashell);

/* env2.c */
char *copy_info(char *name, char *value);
void set_env(char *name, char *value, _shell *datashell);
int _setenv(_shell *datashell);
int _unsetenv(_shell *datashell);

/* cd.c */
void cd_dot(_shell *datashell);
void cd_to(_shell *datashell);
void cd_previous(_shell *datashell);
void cd_to_home(_shell *datashell);

/* cd_shell.c */
int cd_shell(_shell *datashell);

/* builtin.c */
int (*handle_builtin(char *cd))(_shell *datashell);

/* _exit.c */
int exit_shell(_shell *datashell);

/* aux_stdlib.c */
int get_len(int n);
char *aux_itoa(int n);
int _atoi(char *s);

/* aux_error1.c */
char *strcat_cd(_shell *, char *, char *, char *);
char *error_get_cd(_shell *datashell);
char *error_not_found(_shell *datashell);
char *error_exit_shell(_shell *datashell);

/* aux_error2.c */
char *error_get_alias(char **_args);
char *error_env(_shell *datashell);
char *error_syntax(char **_args);
char *error_permission(char **_args);
char *error_path_126(_shell *datashell);


/* get_error.c */
int get_error(_shell *datashell, int eval);

/* get_sigint.c */
void get_sigint(int sig);

/* aux_help.c */
void aux_help_env(void);
void aux_help_setenv(void);
void aux_help_unsetenv(void);
void aux_help_general(void);
void aux_help_exit(void);

/* aux_help2.c */
void aux_help(void);
void aux_help_alias(void);
void aux_help_cd(void);

/* get_help.c */
int get_help(_shell *datashell);

#endif
