#include "mac.h"

void get_id(t_mac *mac)
{
	mac->uid = getuid();
	mac->gid = getgid();
}

void get_user(t_mac *mac)
{
	struct passwd *uid = getpwuid(mac->uid);
	if (!uid)
		error("Getpwuid error");
	mac->user = strdup(uid->pw_name);
}

void drop_privilege(t_mac *mac)
{
	if (seteuid(mac->uid) == -1)
		error("Seteuid error");
	if (setegid(mac->gid) == -1)
		error("Setegid error");
}

int check_authority(t_mac *mac)
{
	if (strstr(mac->document_name, "top_secret.data") != NULL)
	{
		if (mac->access_type > TOP_SECRET)
		{
			printf("ACCESS DENIED\n");
			return (FAIL);
		}
		else
			return (SUCCESS);
	}
	else if (strstr(mac->document_name, "secret.data") != NULL)
	{
		if (mac->access_type > SECRET)
		{
			printf("ACCESS DENIED\n");
			return (FAIL);
		}
		else
			return (SUCCESS);
	}
	else if (strstr(mac->document_name, "confidential.data") != NULL)
	{
		if (mac->access_type > CONFIDENTIAL)
		{
			printf("ACCESS DENIED\n");
			return (FAIL);
		}
		else
			return (SUCCESS);
	}
	else if (strstr(mac->document_name, "unclassified.data") != NULL)
	{
		if (mac->access_type > UNCLASSIFIED)
		{
			printf("ACCESS DENIED\n");
			return (FAIL);
		}
		else
			return (SUCCESS);
	}
	else
	{
		printf("ACCESS DENIED\n");
		return (FAIL);
	}
}
