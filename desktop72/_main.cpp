#include <QCoreApplication>
#include <string.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	for (int iArg = 0 ; iArg < argc ; ++iArg)
	{
		char *arg = argv[iArg];
		if (!strcmp(arg, "--help"))
		{
			puts("Program qqqq");
			return 0;
		}
		else if (arg[0] == '-')
		{
			printf("Unknown key \"%s\". See help.\n", arg);
			return 1;
		}
	}

	QCoreApplication app(argc, argv);

	//

	return app.exec();
}
