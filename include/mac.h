#ifndef MAC_H
# define MAC_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <pwd.h>
# include <unistd.h>

# define READ 1
# define WRITE 2

# define TOP_SECRET 1
# define SECRET 2
# define CONFIDENTIAL 3
# define UNCLASSIFIED 4
# define NOTALLOWED 5

# define FAIL 0
# define SUCCESS 1

typedef struct s_mac
{
	uid_t	uid;
	gid_t	gid;
	char	*document_name;
	char	*data;
	char	*user;
	FILE	*policy_fp;
	FILE	*document_fp;
	FILE	*log_fp;
	int		operator_type;
	int		access_type;
}	t_mac;

// parse.c
void parse_operator(t_mac *mac, char *operator, char *document, char *data);
void parse_policy(t_mac *mac);

// file.c
void open_policy(t_mac *mac);
void open_document(t_mac *mac, char *file);
void open_log(t_mac *mac);

// mac.c
void init_mac(t_mac *mac);
void free_mac(t_mac *mac);

// print.c
void error(char *msg);
void write_log(t_mac *mac);

// authority.c
int check_authority(t_mac *mac);
void get_id(t_mac *mac);
void get_user(t_mac *mac);
void drop_privilege(t_mac *mac);

#endif