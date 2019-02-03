/**
 * @copyright (c) 2016 Abelardo López Lagunas
 *
 * @file    UserDefined.h
 *
 * @author  Abelardo López Lagunas
 *
 * @date    Fri 20 May 2016 22:09 DST
 *
 * @brief   Declares all the user defined functions for handling the
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

#include <glib.h>

/**
 * @struct myData
 *
 * @brief This is the basic user-defined element of the linked list
 *
 * The user-defined data structure is an @c int and a @c string. These
 * are used just to show how to implement user-defined structures.
 *
 */
typedef struct myData_{
    int    number;                         /**< number is an unsigned int */
    char * theString;               /**< theString is a pointer to a char */
}myData;

/**
 * @typedef node_p
 *
 * @brief Declares a pointer type to the user-defined data structure
 *
 */
typedef struct myData_ *node_p;  /**< Simplify declaration of ptr to node */

/**
 * @enum order
 *
 * @brief Used to identify order in the SortList() and FindInList()
 * functions.
 *
 * The @c order enum describes the possible outcomes {LESS, EQUAL, GREATER,
 * NOTEQUAL} of comparing elements in the SortList() and FindInList()
 * functions.
 *
 */
enum order {LESS = -1, EQUAL = 0, GREATER = 1, NOTEQUAL = 2};

/**
 * @enum theKey
 *
 * @brief Used to identify which field in the user-defined data structure
 * to search for {INT, STR, SINGLEINT, SINGLESTR}.
 * An extra entry is added if the user wants to search for a user-supplied
 * @c string and not for the @c string field of a particular user-defined
 * node.
 */
enum theKey {INT = 1, STR, SINGLEINT, SINGLESTR};

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
int PrintItem (const void *data_p);

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
int PrintList (GList * myList_p);

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
node_p NewItem (int theNumber, char * theString);

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
int FreeItem (const void *data_p);

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
int DestroyList (GList * theList_p);

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
int CompareItems (const void *item1_p, const void *item2_p);

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
int CompareItemsWithKey (const void *item1_p, const void *item2_p, int key);

/**
 *
 * @brief Allocate memory to hold a copy of a user-defined item.
 *
 * @b CopyItems() will allocate memory and copy the user defined
 * data structure @c myData. The caller is responsible for
 * de-allocating the new item.
 *
 * @param  source_p is a pointer to the user-defined data structure.
 * @return pointer to the new data item @c data_p or NULL.
 *
 * @code
 *      myList_p = CreateList(FreeItem, PrintItem, CompareItems,
 *                            CopyItems);
 *        NodeData(dstNode_p) = sourceList_p->copy(NodeData(srcNode_p));
 * @endcode
 *
 * @see CreateList()
 *
 * @warning This function must be passed as a parameter when calling
 *          DuplicateList () since it will call it to allocate the
 *          user-defined structure.
 *          The caller is responsible for de-allocating the new item.
 */
void * CopyItems (const void *source_p);

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
GList * CopyList (GList * inputList);

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
GList * FindInList (GList * myList_p, const void *value_p, int key);
