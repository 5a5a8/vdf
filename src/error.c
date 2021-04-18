#include <sys/errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

enum
{
	SUCCESS,
	UNDERFLOW,
	OVERFLOW,
};

int
check_strtoll_error(long long int strtoll_rval)
{
	extern int errno;
	if (errno == ERANGE)
	{
		if (strtoll_rval == LLONG_MIN)
		{
			fprintf(stderr, "ERROR: Underflow in strtoll return value\n");
			fprintf(stderr, "Check flags are not less than %lld\n", LLONG_MIN);
			exit(UNDERFLOW);
		}
		else if (strtoll_rval == LLONG_MAX)
		{
			fprintf(stderr, "ERROR: Overflow in strtoll return value\n");
			fprintf(stderr, "Check flags are not more than %lld\n", LLONG_MAX);
			exit(OVERFLOW);
		}
	}

	return SUCCESS;
}
