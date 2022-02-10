#include "Arguments.h"
#include "NamedPipe.h"

int main(int argc, char *argv[])
{
	write(Arguments(argc, argv));

	return 0;
}
