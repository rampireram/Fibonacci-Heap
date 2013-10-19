#include <stdio.h>

struct fib
{
struct fib *parent; //parent pointer
struct fib *child; //child pointer to child list
struct fib *left; //left pointer
struct fib *right; //right pointer
int deg;// holds the num of children
int key;//The data part
int mark;//not used right now!
};

struct heap
{
	struct fib *rl;
	struct fib *min;
	int n,dn; //dn - max degree of any node
};