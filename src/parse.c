#include "mac.h"

void parse_operator(t_mac *mac, char *operator, char *document, char *data)
{
	if (strcmp(operator, "read") == 0)
		mac->operator_type = READ;
	else if (strcmp(operator, "write") == 0)
		mac->operator_type = WRITE;
	else
		error("Operator error");
	if (mac->operator_type == READ && data != NULL)
		error("Read argument error");
	if (mac->operator_type == WRITE && data == NULL)
		error("Write argument error");
	if (mac->operator_type == WRITE && data != NULL)
		mac->data = strdup(data);
	mac->document_name = strdup(document);
}

void parse_policy(t_mac *mac)
{
	ssize_t read = 0;
	size_t len = 0;
	char *line = NULL;

	while (1)
	{
		read = getline(&line, &len, mac->policy_fp);
		if (read < 0)
		{
			mac->access_type = NOTALLOWED;
			break;
		}
		if (strncmp(line, mac->user, strlen(mac->user)) == 0)
		{
			char *token = line + strlen(mac->user) + 1;
			if (strcmp(token, "TOP_SECRET") == 0 || strcmp(token, "TOP_SECRET\n") == 0)
				mac->access_type = TOP_SECRET;
			else if (strcmp(token, "SECRET") == 0 || strcmp(token, "SECRET\n") == 0)
				mac->access_type = SECRET;
			else if (strcmp(token, "CONFIDENTIAL") == 0 || strcmp(token, "CONFIDENTIAL\n") == 0)
				mac->access_type = CONFIDENTIAL;
			else if (strcmp(token, "UNCLASSIFIED") == 0 || strcmp(token, "UNCLASSIFIED\n") == 0)
				mac->access_type = UNCLASSIFIED;
			else
				mac->access_type = NOTALLOWED;
			break;
		}
	}
	if (line)
		free(line);
}
