#include "mac.h"

void open_policy(t_mac *mac)
{
	FILE *fp = fopen("mac.policy", "r");
	if (fp == NULL)
		error("Policy file error");
	mac->policy_fp = fp;
}

void open_document(t_mac *mac, char *file)
{
	FILE *fp = NULL;
	if (mac->operator_type == READ)
		fp = fopen(file, "r");
	else if (mac->operator_type == WRITE)
		fp = fopen(file, "a");
	if (fp == NULL)
		error("Document file error");
	mac->document_fp = fp;
}

void open_log(t_mac *mac)
{
	char *filename = malloc(strlen(mac->user) + 5);
	strcpy(filename, mac->user);
	strcat(filename, ".log");
	filename[strlen(mac->user) + 4] = '\0';
	int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0640);
	if (fd == -1)
		error("Log file error");
	FILE *fp = fdopen(fd, "a");
	if (fp == NULL)
		error("Log file error");
	mac->log_fp = fp;
	free(filename);
}