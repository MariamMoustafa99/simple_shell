
#ifndef SHELL_H
#define SHELL_H

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

#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

#define USING_GETLINE 0
#define USING_STRTOK 0

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONV_LOWERCASE	1
#define CONV_UNSIGNED	2

#define F_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}


/**
 * struct list_str - singly linked list
 * @x: the number field
 * @c: a string
 * @node: points to the next node
 */
typedef struct list_str
{
	int x;
	char *c;
	struct list_str *node;
} struct_list;

/**
 * struct pass_info - struct containing pseudo-arguements
 * to pass into a function
 * @arg: a string generated from getline containing arguements
 * @arg_vec: an array of strings generated from arg
 * @str_path: a string path for the current command
 * @arg_count: the argument count
 * @line_count: the error count
 * @num_err: the error code for exit status
 * @lc_flag: if on count this line of input
 * @file_name: the program filename
 * @en_viron: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @hist: the history node
 * @alias: the alias node
 * @env_change: on if environ was changed
 * @stat: the return status of the last exec'd command
 * @cmd_buffer: address of pointer to cmd_buf, on if chaining
 * @cmd_buffer_type: CMD_type ||, &&, ;
 * @read_fd: the fd from which to read line input
 * @hist_count: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **arg_vec;
	char *str_path;
	int arg_count;
	unsigned int line_count;
	int num_err;
	int lc_flag;
	char *file_name;
	struct_list *en_viron;
	struct_list *hist;
	struct_list *alias;
	char **environ;
	int env_change;
	int stat;

	char **cmd_buffer;
	int cmd_buffer_type;
	int read_fd;
	int hist_count;
} struct_info;

/**
 *  struct built_in - contain builtin string and related functions
 *  @flag: the builtin command flag
 *  @nc: the function
 */
typedef struct built_in
{
	char *flag;
	int (*nc)(struct_info *);
} built_in_table;

/* string_funct1.c */
char *start_with(const char *, const char *);
int str_len(char *);
char *str_concat(char *, char *);
int str_cmp(char *, char *);

/* string_func2.c */
void put_s(char *);
int put_char(char);
char *str_copy(char *, char *);
char *str_dup(const char *);

/* string_func3.c */
char **str_to_word(char *, char *);
char **str_to_word2(char *, char);

/* string_func4.c */
char *str_char(char *, char);
char *char_duplicate(char *, int, int);
char *str_num_copy(char *, char *, int);
char *str_num_concat(char *, char *, int);

/* str_err_func.c */
int put_filedes(char, int);
int puts_filedes(char *, int);
void puts_err(char *);
int putchar_err(char);

/* mem_func */
int free_pointer(void **);
void free_str(char **);
char *memory_set(char *, char, unsigned int);
void *re_allocate(void *, unsigned int, unsigned int);

/* add_func1.c */
void comments_rem(char *);
int inter_active(struct_info *);
char *num_conv(long int, int, int);
void err_pr(struct_info *, char *);
int dec_pr(int, int);

/* add_func2.c */
int de_limiter(char, char *);
int is_alpha(int);
int a_to_i(char *);
int err_a_to_i(char *);

/* hsh.c */
int hsh(struct_info *, char **);
int cmd_builtin(struct_info *);
void cmd_fork(struct_info *);
void cmd_find(struct_info *);

/* PATH.c */
int cmd_exec(struct_info *, char *);
char *path_finder(struct_info *, char *, char *);

/* emulators_01.c */
int my_curr_dir(struct_info *);
int my_alias(struct_info *);
int my_history(struct_info *);
int my_help(struct_info *);
int my_exit(struct_info *);

/* emulators_02.c */
int alias_print(struct_list *);
int alias_rep(struct_info *);
int alias_set(struct_info *, char *);
int alias_unset(struct_info *, char *);

/* get_line.c module */
void signal_handler(int);
ssize_t buffer_read(struct_info *, char *, size_t *);
ssize_t buffer_input(struct_info *, char **, size_t *);
ssize_t get_line_bef(struct_info *);
int get_line_next(struct_info *, char **, size_t *);

/* INFO.c module */
void info_set(struct_info *, char **);
void info_free(struct_info *, int);
void info_clear(struct_info *);

/* environment_01.c module */
int my_environ(struct_info *);
int my_set_environ(struct_info *);
int my_unset_environ(struct_info *);
char *get_environ(struct_info *, const char *);

/* environment_02.c module */
int pop_environ_list(struct_info *);
char **copy_environ(struct_info *);
int set_environ(struct_info *, char *, char *);
int unset_environ(struct_info *, char *);

/* hist_file_func.c */
int hist_read(struct_info *);
char *hist_get(struct_info *);
int hist_write(struct_info *);
int hist_renum(struct_info *);
int hist_add_list(struct_info *, char *, int);

/* str_list1.c module */
size_t list_print(const struct_list *);
size_t str_list_print(const struct_list *);
size_t list_length(const struct_list *);
char **str_list_arr(struct_list *);
void list_free(struct_list **);

/* str_list2.c module */
struct_list *node_begins(struct_list *, char *, char);
ssize_t node_get_index(struct_list *, struct_list *);
struct_list *node_add_start(struct_list **, const char *, int);
struct_list *node_add_end(struct_list **, const char *, int);
int node_del_index(struct_list **, unsigned int);

/* chained.c */
int var_rep(struct_info *);
int str_rep(char **, char *);
int chain_del(struct_info *, char *, size_t *);
void chain_checked(struct_info *, char *, size_t *, size_t, size_t);

#endif
