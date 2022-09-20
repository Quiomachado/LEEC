#include <stdio.h>

typedef struct node
{
  int val;
  struct node *next;
} node;

int ll_equal(const node *a, const node *b)
{
  while (a != NULL && b != NULL)
  {
    if (a->val != b->val)
      return 0;
    a = a->next;
    b = b->next;
  }
  /* lists are equal if a and b are both null */
  return a == b;
}

int main(int argc, char **argv)
{
  int i;
  node nodes[10];

  for (i = 0; i < 10; i++)
  {
    nodes[i].val = 0;
    nodes[i].next = NULL;
  }

  for (i = 0; i < 9; i++)
  {
    nodes[i].next = &nodes[i + 1];
  }

  printf("Equal test 1 result = %d\n", ll_equal(&nodes[0], &nodes[0]));
  printf("Equal test 2 result = %d\n", ll_equal(&nodes[0], &nodes[2]));

  return 0;
}