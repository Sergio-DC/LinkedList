/**
 * @copyright (c) 2019 Sergio Gabriel Domínguez Cordero
 *
 * @file    UserDefined.h
 *
 * @author  Sergio Gabriel Domínguez Cordero
 *
 * @date    Sat 2 Feb 2018 22:09 DST
 *
 * @brief   Implements all the user defined functions for handling the
 *          specific user-defined data structure that is pointed to
 *          by the doubly linked list node in Glib.
 *
 * References:
 *          Code loosely based on my Generic Singly linked list algorithm.
 *
 * Revision history:
 *          Fri 06 Feb 2015 14:02 CST -- File created
 *          Thu 05 May 2016 10:45 DST -- Changed to use Glib functions
 *          Mon 09 May 2016 17:07 DST -- Added newItem function
 *          Tue 10 May 2016 12:07 DST -- Added CompareItems function to
 *                          implement sort using g_list_sort()
 *          Fri 20 May 2016 22:09 DST -- Changed DoxyGen comments
 *
 * @warning If there is not enough memory to create a node or a list
 *          the related functions indicate failure. If the DEBUG compiler
 *          flag is set then the program will terminate but more
 *          information is displayed indicating the source of error.
 *
 * @note    The code is meant to show how to implement linked lists
 *          using dynamic memory for the Operating Systems and Advanced
 *          Programming classes.
 *
 */

#include "UserDefined.h"

/**
 *
 * @brief Print the contents of the user-defined data structure.
 *
 * @b PrintItem will traverse the user-defined structure and print each
 * field according to the user's formatting.
 *
 * @param  data_p is a pointer to a user-defined structure element.
 * @return @c EXIT_SUCCESS the item was printed with no problems. Otherwise,
 *         return @c EXIT_FAILURE.
 *
 * @code
 *  PrintItem(item_p->data_p);
 * @endcode
 *
 */
int PrintItem (const void *data_p){
    if(data_p == NULL)//Es verdadero cuando no hay datos en el nodo
        return EXIT_FAILURE;
    else{
        printf("Data Element: %d %s\n", ((node_p)data_p)->number, ((node_p)data_p)->theString);//Mostramos los datos de cada nodo en formato number string
        return EXIT_SUCCESS;
    }
}

/**
 *
 * @brief Print all the elements of a list, based on a user-defined
 * function that handles the actual printing of each data element.
 *
 * @b PrintList will print all the elements of @p myList_p. It calls
 * the user-defined functon @c PrintItem which handles the format of
 * the data portion of the items in the list.
 *
 * @param  myList_p is a pointer to the list to be printed.
 * @return @c EXIT_SUCCESS if the list was sorted with no
 *         problems, otherwise return @c EXIT_FAILURE.
 * @code
 *  if (PrintList(theList_p) != EXIT_SUCCESS)
 *     printf("Error printing the list\n");
 * @endcode
 *
 * @warning This function @b requires a user-defined function to do the
 *          actual printing of the data element.
 *
 */
int PrintList (GList * myList_p){
    if(myList_p == NULL)//
        return EXIT_FAILURE;
    else{
        GList * aux = myList_p;//Puntero auxiliar para recorrer la estructura
        while(aux != NULL)//Recorremos la lista
        {
            if(PrintItem(aux->data)==EXIT_FAILURE)
                return EXIT_FAILURE;

            aux = aux->next;
        }
        
        return EXIT_SUCCESS;
    }
}

/**
 *
 * @brief Allocate memory to a node of the user-defined data structure.
 *
 * @b NewItem will allocate the @c string and @c number inside the
 * user-defined data structure @c myData. The input string will be
 * copied so the caller can dispose of the input argument after
 * calling @c NewItem. The string stored in the new node may not be
 * NULL terminated.
 *
 * @param @c theNumber is the integer input.
 * @param @c theString is the copy of the input string.
 *
 * @code
 *  newNode_p = NewItem(13,"Hello");
 * @endcode
 *
 * @return @c node_p is a pointer to the memory block that holds a copy
 *         of the input string and the input number.
 *
 */

node_p NewItem (int theNumber, char * theString){
    node_p newNode = (node_p)malloc(sizeof(struct myData_));
    newNode->number = theNumber;
    newNode->theString = strdup(theString);

    return newNode;
}

/**
 *
 * @brief De-allocate memory assigned to user-defined data structure.
 *
 * @b FreeItem will de-allocate the @c string inside the user-defined
 * data structure @c myData.
 *
 * @param  data_p is a pointer to the user-defined data structure.
 * @return @c EXIT_SUCCESS the item was de-allocated with no
 *         problems, otherwise return @c EXIT_FAILURE
 *
 * @code
 *  FreeItem(item_p->data_p);
 * @endcode
 *
 * @warning This function must be passed as a parameter when calling
 *          @c DestroyList() since it will call it to de-allocate the
 *          user-defined structure.
 */
int FreeItem (const void *data_p){
    if(data_p == NULL)//No hay datos
        return EXIT_FAILURE;
    else{
        free((void *)data_p);
        return EXIT_SUCCESS;
    }
}

/**
 *
 * @brief De-allocate memory assigned to each user-defined data structure
 * in the list. It also deallocates memory for the list.
 *
 * @b DestroyList() will de-allocate the user-defined data structure
 * @c myData for each element in the list.
 *
 * @param  theList_p is a pointer to the list.
 * @return @c EXIT_SUCCESS the list was de-allocated with no problems.
 *         Otherwise return @c EXIT_FAILURE.
 *
 * @code
 *   DestroyList(theList_p);
 * @endcode
 *
 * @see FreeItem()
 *
 */
int DestroyList (GList * theList_p)
{
    if(theList_p!=NULL)
    {
		GList * l = NULL;  // We create a temporary pointer so that we can cycle through the list
		for(l=theList_p;l!=NULL;l=l->next)
        { // The for loop cycles through every member of our GList
            node_p node = l->data; // We extract the data from the node (a node_p) and assign it to a pointer of type myData
            if(FreeItem(node) == EXIT_FAILURE) // We pass the pointer to FreeItem so that the memory can be liberated 
                return EXIT_FAILURE;	    								 
	  	}
	  	return EXIT_SUCCESS; // We return success if everything is succesfull
	}
    return EXIT_FAILURE; // In case the list is NULL we return a failure
}

/**
 *
 * @brief Compare the user-defined nodes of two list elements using a
 * numeric field in the @c myData structure.
 *
 * @b CompareItems() is a user-defined function needed to compare the
 * user-defined data structure. Only the first numeric field of the
 * user-defined data structure is compared. If other fileds are needed use
 * the @c CompareItemsWithKey() function.
 * The return value matches the expected values for @c g_list_sort().
 *
 * @param item1_p is a pointer to the first @c myData item (user-defined).
 * @param item2_p is a pointer to the second @c myData item (user-defined).
 *
 * @return @c LESS     if input1  < input2.
 *         @c EQUAL    if input1 == input2.
 *         @c GREATER  if input1  > input2.
 * @code
 *   if (CompareItems(p1->data, p2->data) == EQUAL) {
 *       return (p);
 *    } else {
 *       ...
 * @endcode
 *
 */
int CompareItems (const void *item1_p, const void *item2_p)
{
    //node_p node1 = item1_p,node2=item2_p; // We convert our generic void pointers to node_p pointers so that we can manage the structure
	if(((node_p)item1_p)->number < ((node_p)item2_p)->number) // We compare the numbers of the nodes to see if node 1 is less
		return LESS; // We return the enum value LESS 
	else if(((node_p)item1_p)->number > ((node_p)item2_p)->number) // We compare the numbers of the nodes to see if node 1 is more
		return GREATER; // We return the enum value GREATER if the condicion is met
	else
        return EQUAL; // The final option is that they are equal
}

/**
 *
 * @brief Compare a filed of the data portion of two list elements using
 *  some user-defined key.
 *
 * @b CompareItemWithKey() is a user-defined function needed to identify
 * the particular data structure fields to compare.
 * This function can compare the integer portion (@p key = INT), the
 * string portion (@p key = STR), compare an arbitrary string to the
 * string field (@p key = SINGLESTR), or compare the contents of an
 * arbitrary pointer to an integer to the integer field (@p key = SINGLEINT)
 * in the user-defined data structure.
 *
 * @param item1_p is a pointer to the first @c myData item (user-defined).
 * @param item2_p is a pointer to the second @c myData item (user-defined)
 *        or to a string if @p key = SINGLESTR.
 * @param key is an integer that corresponds to the desired field in the
 *        user-defined data structure. The key is an enum of type @c theKey.
 * @return @c LESS     if input1  < input2.
 *         @c EQUAL    if input1 == input2.
 *         @c GREATER  if input1  > input2.
 *         @c NOTEQUAL if the comparison can't be made.
 *
 * @code
 *        if (CompareItemsWithKey(p->data, "Hello", SINGLESTR) == EQUAL) {
 *           return (p);
 *        } else {
 *           ...
 * @endcode
 *
 *
 */
int CompareItemsWithKey (const void *item1_p, const void *item2_p, int key)
{
    //node_p node1=item1_p,node2 = item2_p; // We assume our parameters passed are going to be node_p pointers.
	//int *integer = NULL; //We declare an integer pointer and a char pointer in case the above statement is not true
	//char *string = NULL;
	switch(key)
    { // A switch statement lets us handle each key type individually
		case INT: // INT key case
			return CompareItems(item1_p,item2_p); //In case we just want to compare the number, we call our default compare function
		break;
		case STR: //STR key case
			if(strcmp(((node_p)item1_p)->theString,((node_p)item2_p)->theString)==0) // We compare both nodes' strings to see if they are equal
				return EQUAL;
			else
				return NOTEQUAL; // In case that they are not equal we return the enum NOTEQUAL
		break;
		case SINGLESTR: //SINGLESTR case
			//string = item2_p; // We assign our second generic pointer to the char pointer created earlier
			if(strcmp(((node_p)item1_p)->theString,((char *)item2_p))==0) // We compare the strings as in the previous case to see if they are equal.
				return EQUAL;
			else
				return NOTEQUAL; // In case that they are not equal we return the enum NOTEQUAL
		break;
		case SINGLEINT: //SINGLEINT case
			//integer = item2_p; // We assign our second generic pointer to the int pointer created earlier
			if(((node_p)item1_p)->number==*((int *)item2_p)) //We compare the number in our node with the value stored in the address of the pointer
				return EQUAL;
			else
				return NOTEQUAL; // In case that they are not equal we return the enum NOTEQUAL
		default:
			return NOTEQUAL; // If no valid key is entered a default NOTEQUAL is returned
    }
}

/**
 *
 * @brief Perform a deep copy of an input list.
 *
 * @b DuplicateList() will perform a deep copy of an input list
 * allocating memory for each data element by calling the user-defined
 * CopyItems() function.
 *
 * @param  inputList_p pointer to the list to be copied.
 * @return pointer to the new list.
 *
 * @code
 *  outputList_p = CopyList(inputList_p);
 *  if (outputList == NULL){
 *     printf("Error: failed to find selected node \n");
 *  }
 * @endcode
 *
 * @note   The user must check if the returned pointer is NULL
 *         before de-referencing it.
 */
GList * CopyList (GList * inputList)
{
	GList *theCopy = NULL; // We create an empty GList pointer that will be the starting point for our copy 
	if(inputList!=NULL)
    {
        GList *l; // A temporary pointer is created that will allow us to cycle through our list
        node_p aNode_p=NULL; // A temporary node is created that will let us append new nodes to the list
        for(l=inputList;l!=NULL;l=l->next)
        { // We cycle through the list
            node_p node = l->data; // We extract the data from the current node (a node_p pointer) and assign it to a variable
            aNode_p = NewItem(node->number, node->theString); // We create a new memory location for the copy of the node, copying the same data from the node that comes from the original list
            theCopy = g_list_append(theCopy, aNode_p); // The new node created is appended to the copy of the list
        }
  	}
  	return theCopy; // We return the pointer to the copy of the list, in case the input is NULL the pointer will also be NULL
}

/**
 *
 * @brief Attempts to find a user-defined value in a list
 *
 * @b FindInList() will try to find the user-defined value pointed by
 * @p value_p that matches a particular field @p key in the user-defined
 * data structure which is part of every data portion of the nodes in the
 * linked list.
 *
 * @param  myList_p pointer to the list to be searched.
 * @param  value_p pointer to the user-defined data value to match.
 * @param  key integer that represents which field in the user-defined
 *         data structure to match against @p value_p
 * @return pointer to the element in the list that matches the value
 *         @p value_p. NULL if no match was found.
 *
 * @code
 *  aNode = FindInList(theList_p, "Louie", SINGLESTR);
 *  if (aNode == NULL){
 *     printf("Error: failed to find selected node \n");
 *  }
 * @endcode
 *
 * @note   The user must check if the returned pointer is NULL
 *         before de-referencing it.
 *
 */
GList * FindInList (GList * myList_p, const void *value_p, int key){
    GList *l = NULL; // We create a temporary pointer so that we can cycle through the list
	node_p node = NULL; // We create a variable that will store the pointer to the data in each GList type
	for(l=myList_p;l!=NULL;l=l->next)
    { // We cycle through the list
    	node = l->data; // The data is extracted and stored in the node variable
    	if(CompareItemsWithKey(l->data,value_p,key) == 0) // We compare the value needed in the node depending oon what type of key the user passes. If the function returns zero we have found
    	    return l;									// our node
	}
    return NULL; // In case the node isn't found we return null
}