#ifndef LIST_ERROR_H
#define LIST_ERROR_H

#define ERRMEM 0
#define ERRNULL 1

int error_routine(unsigned long err)
{
	(void)err;
	exit(EXIT_FAILURE);
}

#endif
