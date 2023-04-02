#include "mac.h"

void operate(t_mac *mac)
{
	if (mac->operator_type == READ)
	{
		ssize_t read = 0;
		char *line = NULL;
		size_t len = 0;
		while (1)
		{
			read = getline(&line, &len, mac->document_fp);
			if (read < 0)
				break;
			printf("%s", line);
		}
		printf("\n");
		if (line)
			free(line);
	}
	else if (mac->operator_type == WRITE)
	{
		if (fprintf(mac->document_fp, "%s", mac->data) < 0)
			error("Write error");
		if (fprintf(mac->document_fp, "\n") < 0)
			error("Write error");
	}
}

int main(int argc, char **argv)
{
	if (argc < 3 || argc > 5)
		error("Arguments error");

	t_mac mac;
	char *data = NULL;
	if (argc == 4)
		data = argv[3];
	(void)data;
	
	init_mac(&mac);
	
	get_id(&mac);
	get_user(&mac);

	parse_operator(&mac, argv[1], argv[2], data);

	// parse policy
	open_policy(&mac);
	parse_policy(&mac);
	fclose(mac.policy_fp);

	// open document
	if (check_authority(&mac) == SUCCESS)
	{
		open_document(&mac, argv[2]);
		operate(&mac);
		fclose(mac.document_fp);
	}

	// drop privilege
	drop_privilege(&mac);

	// open log
	open_log(&mac);
	write_log(&mac);
	fclose(mac.log_fp);

	free_mac(&mac);
	return (0);
}
