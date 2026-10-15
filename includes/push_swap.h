#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include "libft.h"

typedef struct s_stack
{
	int				n;
	int				index;
	int				pos;
	int				fit;
	int				move_a;
	int				move_b;
	struct s_stack	*next;
}	t_stack;


#endif