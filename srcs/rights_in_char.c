#include "../includes/ft_ls.h"

static char	*fullfill_rights_usr(char *s, mode_t mode)
{
	if (mode & S_IRUSR)
		s[0] = 'r';
	else
		s[0] = '-';
	if (mode & S_IWUSR)
		s[1] = 'w';
	else
		s[1] = '-';
	if (mode & S_IXUSR)
		s[2] = 'x';
	else
		s[2] = '-';
	return (s);
}

static char	*fullfill_rights_grp(char *s, mode_t mode)
{
	if (mode & S_IRGRP)
		s[3] = 'r';
	else
		s[3] = '-';
	if (mode & S_IWGRP)
		s[4] = 'w';
	else
		s[4] = '-';
	if (mode & S_IXGRP)
		s[5] = 'x';
	else
		s[5] = '-';
	return (s);
}

static char	*fullfill_rights_oth(char *s, mode_t mode)
{
	if (mode & S_IROTH)
		s[6] = 'r';
	else
		s[6] = '-';
	if (mode & S_IWOTH)
		s[7] = 'w';
	else
		s[7] = '-';
	if (mode & S_IXOTH)
		s[8] = 'x';
	else
		s[8] = '-';
	return (s);
}

char		*rights_in_char(mode_t mode)
{
	char *s;

	s = malloc(sizeof(char) * 10);
	if (s == NULL)
		return (NULL);
	s = fullfill_rights_usr(s, mode);
	s = fullfill_rights_grp(s, mode);
	s = fullfill_rights_oth(s, mode);
	s[9] = '\0';
	return (s);
}
