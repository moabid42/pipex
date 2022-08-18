#include <stdio.h>
#include <unistd.h>


void ft_fuck(int c)
{
	write(1, &c, 1);
}

int main(void)
{
	ft_fuck(0);
}
