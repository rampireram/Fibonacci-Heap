#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "heap.h"


void insert_into_root_list(struct heap **H,struct fib **x)//to insert a node into the root list
{
if((*H)->rl==NULL)
	{
		(*H)->rl=*x;
		(*H)->rl->left=(*H)->rl;
		(*H)->rl->right=(*H)->rl;
	}
else
{
(*x)->right=(*H)->rl;
(*x)->left=(*H)->rl->left;
(*H)->rl->left->right=*x;
(*H)->rl->left=*x;
}

}


void insert_into_child_list(struct fib **H,struct fib **x) //insert into child node
{
if((*H)->child==NULL)
	{
		(*H)->child=*x;
		(*H)->child->left=(*H)->child;
		(*H)->child->right=(*H)->child;
	}
else
{
(*x)->right=(*H)->child;
(*x)->left=(*H)->child->left;
(*H)->child->left->right=*x;
(*H)->child->left=*x;
}
(*H)->deg++;
}

void remove_from_root_list(struct fib **z)
{
(*z)->left->right=(*z)->right;
(*z)->right->left=(*z)->left;
}


void insert(struct heap **H,struct fib **x,int k)//to initialize a new node to be inserted
{
(*x)=malloc(sizeof(struct fib));
(*x)->deg=0;
(*x)->key=k;
(*x)->child=NULL;
(*x)->parent=NULL;
(*x)->mark=0;
(*x)->left=NULL;
(*x)->right=NULL;
if((*H)->min==NULL)
	{
		(*H)->rl=malloc(sizeof(struct fib));
		(*H)->rl=NULL;
		insert_into_root_list(H,x);
		(*H)->min=*x;
	}
else
	insert_into_root_list(H,x);
if((*x)->key < (*H)->min->key)
	(*H)->min=*x;
(*H)->n+=1;
}



void view_root_list(struct fib *x)
{
if(!x)
{
	printf("\nNo nodes in this list!");
	return;
}
struct fib *t=x->left;
while(x!=t)
{
	printf("%d ",x->key);
	x=x->right;
}
printf("%d ",x->key);//to print the last node
}



view_child_list(struct heap *H,int n)
{
	struct fib *temp=H->rl;
	struct fib *stop=temp->left;
	while(temp!=stop)
	{
		if(temp->key==n)
			view_root_list(temp->child);
		temp=temp->right;
	}
	if(temp->key==n)
			view_root_list(temp->child);
}


struct fib *fib_heap_link(struct heap **H,struct fib **a,struct fib **b)//to make a node,child of
{																		//another
remove_from_root_list(b);
(*b)->parent=(*a);
(*a)->deg+=1;
insert_into_child_list(a,b);
return (*a);
}


void consolidate(struct heap **H,struct fib **beg)//consolidate the list so as to make each node's
{												//degree different from others'
	int cn=2*((*H)->dn);
	struct fib *A[10];
	int i;
	view_root_list((*H)->rl);
	for(i=0;i<10;i++)
		A[i]=NULL;
	struct fib *stop=(*beg)->left;
	struct fib *temp=(*beg);
	struct fib *next;
	struct fib *x,*y;
	while(temp!=stop)
	{	
		next=temp->right;
		x=temp;
		int d=x->deg;
		while(A[d]!=NULL)
		{
			y=A[d];
			x=temp;
			if(x->key > y->key)
				x=fib_heap_link(H,&y,&x);
			else
				x=fib_heap_link(H,&x,&y);
			A[d]=NULL;
			d++;
		}
		A[d]=x;
		temp=next;
	}
	(*H)->min=NULL;
	(*H)->rl=stop;//first used "STOP"
	temp=stop->right;
	int min=stop->key;
	int max_dn=0;
	while(temp!=stop)
	{
		if(temp->key <= min)
		{
			(*H)->min=temp;
			min=temp->key;
		}
		if(temp->deg >= max_dn)
			max_dn=temp->deg;
		temp=temp->right;
	}
	if(temp->key <= min) //for the last node
			{
				(*H)->min=temp; 
				min=temp->key;
			}



}

struct fib *e_min(struct heap **H)
{
struct fib *z=(*H)->min;
struct fib *t;
struct fib **lcousin,**rcousin;
lcousin=&(z->left);
rcousin=&(z->right);
if(z!=NULL)
	{	if(z->child)
		{	
			t=z->child;
			struct fib *stop=t->left;
			while(t!=stop)
				{
					t->parent=NULL;
					t=t->right;
				}
				t->parent=NULL;
			(*lcousin)->right=z->child;
			(*rcousin)->left=z->child->left;
			struct fib **ztemp=&(z->child->left);
			(*ztemp)->right=(*rcousin);
			ztemp=&(z->child);
			(*ztemp)->left=(*lcousin);
			z->child=NULL;
			
		}
		else
			{
				remove_from_root_list(&z);
			}
	
	(*H)->rl=(*rcousin);
	if(z==z->right)
		(*H)->min=NULL;
	else
		{
			(*H)->min=z->right;
			consolidate(H,rcousin);
		}
	(*H)->n-=1;	
	}
// fixing H->rl imminent.. done in consolidate
t=z;free(z);
return t;

}

void heap_init(struct heap **H)
{
(*H)->rl=NULL;
(*H)->min=NULL;
(*H)->n=0;
(*H)->dn=0;
}


int main()
{
struct fib *x=malloc(sizeof(struct fib));
struct heap *H=malloc(sizeof(struct heap));
heap_init(&H);
int k,in;
struct fib *temp;
do{
printf("\n1.Insert 2.Extract min 3.View Root List 4.View Child list\n");
scanf("%d",&k);
switch(k)
	{
	case 1:
	printf("Data= ");
	scanf("%d",&in);
	insert(&H,&x,in);
	break;
	case 2:
		if(H->min==NULL)
		{
			printf("\nList empty!");break;
		}
		else
		{
		temp=e_min(&H);
		printf("Min= %d\n",temp->key);
		break;
		}
	case 3:
	view_root_list(H->rl);
	break;
	case 4:
	printf("\nEnter the no ");
	scanf("%d",&in);
	view_child_list(H,in);
	default:
	break;
	}
}while(k<=4);
}