#include "list.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define NODE_SIZE 12

#ifdef UINT 
#undef UINT
#endif

#define UINT unsigned int

enum { prev = 0, next = 1, data = 2 };

static void createNode(char** node, const char* value)
{
	char* node_temp = (char*)malloc(NODE_SIZE);
	UINT node_data_size = strlen(value) + 1;
	char* node_data = (char*)malloc(node_data_size);
	memcpy((void*)node_data, (void*)value, node_data_size);
	((UINT*)node_temp)[prev] = NULL;
	((UINT*)node_temp)[next] = NULL;
	((UINT*)node_temp)[data] = (UINT)node_data;
	*node = node_temp;
}

void ListInit(char ** list)
{
	*list = NULL;
}

void ListRemoveNode(char ** list, const char * value)
{
	char* iterator = NULL;
	char* next_iterator = NULL;
	char* prev_iterator = NULL;
	char* node_data = NULL;
	iterator = *list;
	while (NULL != iterator)
	{
		if (0 == strcmp((char*)((UINT*)iterator)[data], value))
		{
			node_data = (char*)((UINT*)iterator)[data];
			free((void*)node_data);
			if (NULL == ((UINT*)iterator)[prev] && NULL == ((UINT*)iterator)[next])
			{
				free((void*)*list);
				*list = NULL;
				return;
			}
			if (NULL == ((UINT*)iterator)[prev])
			{
				*list = (char*)((UINT*)iterator)[next];
				((UINT*)*list)[prev] = NULL;
				free((void*)iterator);
				iterator = *list;
			}
			else if (NULL == ((UINT*)iterator)[next])
			{
				if (*list == iterator)
				{
					*list = (char*)((UINT*)iterator)[prev];
					((UINT*)*list)[next] = NULL;
				}
				else
				{
					prev_iterator = (char*)((UINT*)iterator)[prev];
					((UINT*)prev_iterator)[next] = NULL;
				}
				free((void*)iterator);
				return;
			}
			else 
			{
				prev_iterator = (char*)((UINT*)iterator)[prev];
				next_iterator = (char*)((UINT*)iterator)[next];
				((UINT*)prev_iterator)[next] = (UINT)next_iterator;
				((UINT*)next_iterator)[prev] = (UINT)prev_iterator;
				free((void*)iterator);
				iterator = next_iterator;
			}
		}
		else
		{
			iterator = (char*)((UINT*)iterator)[next];
		}
	}
}

//value must be null string(end with '\0')
void ListInsertNode(char ** list, const char * value)
{
	if (NULL != list)
	{
		char* node = NULL;

		createNode(&node, value);

		char* iterator = NULL;
		char* next_iterator = NULL;

		iterator = *list;

		if (NULL == iterator)
		{
			*list = node;
			return;
		}

		while (1)
		{
			next_iterator = (char*)((UINT*)iterator)[next];
			if (NULL == next_iterator)
			{
				((UINT*)node)[prev] = (UINT)iterator; //add address to previous element
				((UINT*)iterator)[next] = (UINT)node; //add address to next element
				return;
			}
			iterator = next_iterator;
		}
	}
	else printf("Something bad with parametrs:(");
}
	


void PrintList(char** list)
{
	char* node = *list;
	char* node_data = NULL;
	if (NULL == node)
	{
		printf("List is empty!!!\n");
	}
	while (NULL != node)
	{
		node_data = (char*)(((UINT*)node)[data]);
		printf("%s\n", node_data);
		node = (char*)((UINT*)node)[next];
	}
}

void ListRemoveDuplicates(char ** list)
{
	char* iterator = NULL;
	char* next_iterator = NULL;
	char* node_data_buffer = NULL;
	iterator = *list;
	while (NULL != ((UINT*)iterator)[next] && NULL != ((UINT*)*list)[next])
	{
		node_data_buffer = (char*)((UINT*)iterator)[data];
		next_iterator = (char*)((UINT*)iterator)[next];
		ListRemoveNode(&next_iterator, node_data_buffer);
		iterator = next_iterator;
	}
}

unsigned int ListSize(char ** list)
{
	char* iterator = *list;
	UINT counter=0;
	while (NULL != iterator)
	{
		++counter;
		iterator = (char*)((UINT*)iterator)[next];
	}
	return counter;
}

int IndexOfFirstMatch(char ** list, const char * str)
{
	UINT counter = 0;
	char* iterator = *list;

	while (0 != strcmp((char*)((UINT*)iterator)[data], str))
	{
		if (NULL != (char*)((UINT*)iterator)[next])
		{
			++counter;
			iterator = (char*)((UINT*)iterator)[next];
		}
		else
		{
			counter = -1;
			break;  
		}
	}
	
	return counter;
}

void ListDestroy(char ** list)
{
	if (NULL != *list)
	{
		char* next_iterator = *list;
		next_iterator = (char*)((UINT*)next_iterator)[next];
		char* iterator = NULL;

		while (NULL != next_iterator)
		{
			*list = (char*)((UINT*)next_iterator)[next];
			free((void*)((UINT*)next_iterator)[data]);
			free((void*)next_iterator);
			next_iterator = (char*)((UINT*)*list)[next];
		}

		free((void*)((UINT*)*list)[data]);
		free(*list);
		*list = NULL;
	}
	else 
	{
		printf("List is already empty!");
	}
}

void NodeSwap(char ** left, char ** right)//Just swap by value:(
{
	/*char* left_prev = NULL;
	char* right_next = NULL;

	if (NULL != (char*)((UINT*)*left)[prev])
	{
		left_prev = (char*)((UINT*)*left)[prev];
		(char*)((UINT*)left_prev)[next] = (char*)*right;
	}

	if (NULL != (char*)((UINT*)*right)[next])
	{
		right_next = (char*)((UINT*)*right)[next];
		(char*)((UINT*)right_next)[prev] = (char*)*left;
	}


	((UINT*)*left)[next] = (char*)((UINT*)*right)[next];
	((UINT*)*right)[prev] = (char*)((UINT*)*left)[prev];
	((UINT*)*right)[next] = *left;
	((UINT*)*left)[prev] = *right;*/

	char* tmp = (char*)((UINT*)*left)[data];
	(char*)((UINT*)*left)[data] = (char*)((UINT*)*right)[data];
	(char*)((UINT*)*right)[data] = (char*)tmp;
	
}



void SortList(char ** list)
{
	int swapped;
	char*iterator = NULL,next_iterator = NULL;

	/* Checking for empty list */
	if (*list == NULL)
		return;

	do
	{
		swapped = 0;
		iterator = *list;

		while (((UINT*)iterator)[next] != next_iterator && ((UINT*)iterator)[next]!=NULL)
		{
			char* tmp = ((UINT*)iterator)[next];
			if ( 0 < strcmp((char*)((UINT*)iterator)[data], (char*)((UINT*)tmp)[data]))
			{
				NodeSwap(&iterator, &tmp);
				swapped = 1;
			}
			iterator = ((UINT*)iterator)[next];
		}
		next_iterator = iterator;
	}while (swapped);

}

void StringListReplaceInStrings(char** list, const char* before, const char* after)
{
	for (UINT* node = (UINT*)*list; node != NULL; node = (UINT*)node[next])
	{
		if (!strcmp((char*)(UINT*)node[data], before))
		{
			(UINT*)node[data] = realloc((void*)node[data], strlen(after) + 1);
			strcpy((UINT*)node[data], after);
		}
	}
}