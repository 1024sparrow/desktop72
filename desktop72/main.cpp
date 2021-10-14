#include <QApplication>
#include "footer.h"

#include <string.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	for (int iArg = 0 ; iArg < argc ; ++iArg)
	{
		char *arg = argv[iArg];
		if (!strcmp(arg, "--help"))
		{
			puts("Desktop72"
				 "version 2.0"
				 "All initialization at statup time."
				 ""
				 "~/.config/desktop72/ - place for all plugins"
				 "  control.fifo - place to write commands"
				 "  pid - my process id for clients to send signals to me");
			return 0;
		}
		else if (arg[0] == '-')
		{
			printf("Unknown key \"%s\". See help.\n", arg);
			return 1;
		}
	}

	QApplication app(argc, argv);

	QWidget *w = new Footer();
	w->setFixedSize(500,500);//boris debug
	w->show();

	return app.exec();
}
