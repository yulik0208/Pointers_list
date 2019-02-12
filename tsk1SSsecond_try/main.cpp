#include <iostream>
#include<string.h>
#include<stdlib.h>

#include "list.h"
#define NULL 0


int main()
{
	/*unsigned int size1 = 6;
	unsigned int size2 = 5;
	unsigned int size3 = 6;
	unsigned int size4 = 5;

	char* data1 = (char*)malloc(6);
	memcpy((void*)data1, (void*)"12345", size1);

	char* data2 = (char*)malloc(5);
	memcpy((void*)data2, (void*)"6789", size2);

	char* data3 = (char*)malloc(6);
	memcpy((void*)data3, (void*)"qerty", size1);

	char* data4 = (char*)malloc(5);
	memcpy((void*)data4, (void*)"abcd", size2);

	char* values1 = (char*)malloc(16);
	char* values2 = (char*)malloc(16);
	char* values3 = (char*)malloc(16);
	char* values4 = (char*)malloc(16);



	((unsigned int*)values1)[prev] = (unsigned int)NULL;
	((unsigned int*)values1)[next] = (unsigned int)values2;
	((unsigned int*)values1)[data] = (unsigned int)data1;
	((unsigned int*)values1)[size] = (unsigned int)size1 - 1;

	((unsigned int*)values2)[prev] = (unsigned int)values1;
	((unsigned int*)values2)[next] = (unsigned int)values3;
	((unsigned int*)values2)[data] = (unsigned int)data2;
	((unsigned int*)values2)[size] = (unsigned int)size2 - 1;

	((unsigned int*)values3)[prev] = (unsigned int)values2;
	((unsigned int*)values3)[next] = (unsigned int)values4;
	((unsigned int*)values3)[data] = (unsigned int)data3;
	((unsigned int*)values3)[size] = (unsigned int)size3 - 1;

	((unsigned int*)values4)[prev] = (unsigned int)values3;
	((unsigned int*)values4)[next] = (unsigned int)NULL;
	((unsigned int*)values4)[data] = (unsigned int)data4;
	((unsigned int*)values4)[size] = (unsigned int)size4 - 1;


	char* element = values1;

	while (NULL != element)
	{
		unsigned int sizeloop = ((unsigned int*)element)[size];
		char* dataloop = (char*)(((unsigned int*)element)[data]);
		for (int i = 0; i < sizeloop; ++i)
		{
			std::cout << *dataloop;
			++dataloop;
		}
		std::cout << std::endl;
		element = (char*)((unsigned int*)element)[next];
	}*/

	char* list;

	ListInit(&list);

	printf("Press\n"
		"1 to print\n"
		"2 to enter and add string to an array\n"
		"3 to enter and remove string from array\n"
		"4 to get the numbers of strings in array\n"
		"5 to enter a string and find index of it in array\n"
		"6 to remove duplicates\n"
		"7 to sort list\n"
		"8 to enter \"before\" and \"after\" string, and replace all \"before\" by \"after\"\n"
		"q to quit\n");

	char choice = '0';
	char temp_str[50];
    char before[50];
	char after[50];

	while ((choice = getchar()) != 'q')
	{
		if (choice == '\n')
			continue;

		switch (choice)
		{
		case '1':
			PrintList(&list);
			break;
		case '2':
			printf("Enter a string to be added:\n");
			std::cin>>temp_str;
			ListInsertNode(&list, temp_str);
			break;
		case '3':
			printf("Enter a string to remove:\n");
			std::cin >> temp_str;
			ListRemoveNode(&list, temp_str);
			break;
		case '4':
			printf("Number of strings in list:\n");
			printf("%d", ListSize(&list));
			break;
		case '5':
			printf("Destroying list\n");
			ListDestroy(&list);
			break;
		case '6':
			printf("Removing duplicates\n");
			ListRemoveDuplicates(&list);
			break;
		case '7':
			printf("Sort list\n");
			SortList(&list);
			break;
		case '8':
			printf("Replaces every occurrence of the before, in each of the string lists's strings, with after.\n");
			printf("Enter string before: ");
			gets_s(before);
			printf("\nEnter string after: ");
			gets_s(after);
			StringListReplaceInStrings(&list, before, after);
			break;
		default:
			printf("Invalid input");
			break;
		}
	}
	system("pause");
	return 0;
}