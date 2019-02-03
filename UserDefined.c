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
        printf("Data Element: %d %s\n", ((node_p)data_p->number), ((node_p)data_p->theString));//Mostramos los datos de cada nodo en formato number string
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
        while(aux != NULL){//Recorremos la lista
            
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