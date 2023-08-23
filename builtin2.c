#include "main.h"



void builtin_cd(data *d)
{
	char *dir = d->av[1];
	char cwd[256];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd()");
	_setenv(d, "PWD", cwd);
	if (!dir)
		dir = _getenv("HOME");
	if (chdir(dir) == -1)
		perror("cd");
	else
	{
		_setenv(d, "OLDPWD", _getenv("PWD"));
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			perror("getcwd()");
		_setenv(d, "PWD", cwd);
	}
}
