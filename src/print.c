#include "mac.h"

void error(char *msg)
{
	printf("Error: %s\n", msg);
	exit(1);
}

void write_log(t_mac *mac)
{
	if (mac->operator_type == READ)
		fprintf(mac->log_fp, "%s ", "read");
	else if (mac->operator_type == WRITE)
		fprintf(mac->log_fp, "%s ", "write");
	fprintf(mac->log_fp, "%s", mac->document_name);
	if (mac->operator_type == WRITE)
		fprintf(mac->log_fp, " %s", mac->data);
	fprintf(mac->log_fp, "%s", "\n");
}