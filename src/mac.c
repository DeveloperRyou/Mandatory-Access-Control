#include "mac.h"

void init_mac(t_mac *mac)
{
	mac->data = NULL;
	mac->document_name = NULL;
	mac->user = NULL;
	mac->policy_fp = NULL;
	mac->document_fp = NULL;
	mac->log_fp = NULL;
	mac->operator_type = 0;
	mac->access_type = 0;
}

void free_mac(t_mac *mac)
{
	if (mac->data)
		free(mac->data);
	if (mac->document_name)
		free(mac->document_name);
	if (mac->user)
		free(mac->user);
}

