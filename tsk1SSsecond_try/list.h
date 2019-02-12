#ifndef LIST_H
#define LIST_H

/*============================================================================*/
/*                    External Function Declarations                          */
/*============================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

	void ListInit(char** list);

	void ListRemoveNode(char** list,
		const char* value);

	void ListInsertNode(char** list,
		const char* value);

	void PrintList(char** list);

	void ListRemoveDuplicates(char** list);
	
	unsigned int ListSize(char** list);

	int IndexOfFirstMatch(char** list,
		const char* str);

	void ListDestroy(char** list);

	void NodeSwap(char** left, 
		char** right);

	void SortList(char** list);

	void StringListReplaceInStrings(char** list,
		const char* before,
		const char* after);

#ifdef __cplusplus
}
#endif

#endif //