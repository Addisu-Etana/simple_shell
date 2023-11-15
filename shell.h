#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct pass_info - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct pass_info
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* Addisu & Anwar    main_loopshell.c */
int main_shell_loop(info_t *, char **);
int find_builtin_command(info_t *);
void find_cmd_path(info_t *);
void fork_cmd_run(info_t *);

/* Addisu_Anwar    exec_path.c */
int our_cmd(info_t *, char *);
char *duplicate_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* Addisu_Anwar   std_err.c */
void input_string(char *);
int wr_char_stderr(char);
int put_xyz(char c, int f_d);
int puts_xyz(char *str, int fd);

/* Addisu_Anwar   length_string.c */
int string_length(char *);
int string_comparison(char *, char *);
char *starts_with_address(const char *, const char *);
char *_strcat(char *, char *);

/*Addisu_Anwar  length_string01.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* Addisu_Anwar    entrance.c */
char *string_copy(char *, char *, int);
char *string_concat(char *, char *, int);
char *string_locates(char *, char);

/* Addisu_Anwar   token_ization.c */
char **split_string_words(char *, char *);
char **split_string_words2(char *, char);

/* Addisu_Anwar   re_allocation.c */
char *fills_memory(char *, char, unsigned int);
void free_string(char **);
void *reallocate_memory(void *, unsigned int, unsigned int);

/* Addisu & anwar    free_memory.c */
int be_free(void **);

/* Addisu_Anwar    string_integer.c */
int interactive_mode(info_t *);
int our_delim(char, char *);
int _isalphabetic(int);
int string_integer_convert(char *);

/* Addisu_ Anwar  std_error2.c */
int error_string_integer(char *);
void print_error_msg(info_t *, char *);
int print_base10(int, int);
char *convert_number(long int, int, int);
void eliminate_comments(char *);

/* Addisu & Anwar     change_dirrectory2.c */
int our_exit(info_t *);
int our_cd(info_t *);
int pwd_help(info_t *);

/* Addisu_Anwar    my_history.c */
int our_history(info_t *);
int our_alias(info_t *);
int _myenv(info_t *);

/*Addisu_Anwar   inform_line.c */
ssize_t get_input_newline(info_t *);
int get_line(info_t *, char **, size_t *);
void sigint_Handler(int);

/* Addisu & Anwar    get_inform.c */
void clear_info_struct(info_t *);
void set_info_struct(info_t *, char **);
void free_info_struct(info_t *, int);

/* Addisu & Anwar   my_env.c */
char *value_getenv(info_t *, const char *);
int new_setenv(info_t *);
int new_setenv(info_t *);
int our_unset_env(info_t *);
int populate_env_list(info_t *);

/* Addisu & Anwar    get_enviro.c */
char **get_return_enviro(info_t *);
int remove_env_variable(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* Addisu & Anwar _remember_sth.c */
char *gethistory_file(info_t *info);
int appends_history(info_t *info);
int read_history_file(info_t *info);
int add_history_list(info_t *info, char *buf, int linecount);
int re_number_history(info_t *info);

/* Addisu & Anwar _queue.c */
list_t *add_node_tolist(list_t **, const char *, int);
list_t *add_node_toend(list_t **, const char *, int);
size_t print_str_list(const list_t *);
int delete_node_atindex(list_t **, unsigned int);
void free_all_list(list_t **);

/* Addisu & Anwar  queue_01.c */
size_t list_length(const list_t *);
char **list_strings(list_t *);
size_t print_list_elements(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* Addisu & Anware_  replace_vars.c */
int our_chain(info_t *, char *, size_t *);
void check_chain_status(info_t *, char *, size_t *, size_t, size_t);
int replace_alias_string(info_t *);
int replace_vars_string(info_t *);
int replace_string(char **, char *);

#endif
