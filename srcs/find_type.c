#include "../includes/ft_ls.h"

char		find_type(t_ent *ent)
{
	if (ent->dirent->d_type == DT_DIR)
		return ('d');
	else if (ent->dirent->d_type == DT_LNK)
		return ('l');
	else if (ent->dirent->d_type == DT_BLK)
		return ('b');
	else if (ent->dirent->d_type == DT_CHR)
		return ('c');
	else if (ent->dirent->d_type == DT_FIFO)
		return ('p');
	else if (ent->dirent->d_type == DT_SOCK)
		return ('s');
	else if (ent->dirent->d_type == DT_UNKNOWN)
		return ('?');
	else
		return ('-');
}
