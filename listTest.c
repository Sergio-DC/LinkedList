/**
 * @copyright (c) 2016 Abelardo López Lagunas. All rights reserved.
 *
 * @file    listTest.c
 *
 * @author  Abelardo López Lagunas
 *
 * @brief   This program tests how the list-management routines work.
 *
 * @date    Fri 06.Feb.2015 14:33 CST
 *
 * Usage    The program reads a text file with the elements that will
 *          be converted into nodes in a linked list. The usage form is:
 * @code
 *   listTest file.txt
 * @endcode
 *
 * References Based on my own code for the Generic Linked lists
 *
 * File formats:
 *          The input file should have two elements per line in ASCII
 *          format. The first one is a number and the second one is a
 *          string.
 *
 * Restrictions:
 *          If the input file is not in ASCII format the program exits.
 *
 * Revision history:
 *
 *          Fri Jan 30 15:34 2014 - Added more tests for the insertion
 *                                  and deletion at the head & middle.
 *          Sun Feb 01 14:47 2014 - Separated the user defined functions
 *                                  into their own files.
 *          Tue Feb 03 11:30 2014 - Commented out the Sort and Duplicate
 *                                  list functions that were not in the
 *                                  TC2025 assignment.
 *          Fri 06 Feb 2015 14:33 - Added doxygen documentation commands
 *          Thu 26 Feb 2015 12:08 - Added final tests for the library
 *          Thu 05 May 2016 10:52 - Changed code to use Glib for lists
 *
 * @warning On any unrecoverable error, the program exits
 *
 * @note    This code will be used as a tutorial on pointers and data
 *          structures, in particular linked lists.
 *
 */
#include <stdio.h>                                    // Used for printf
#include <stdlib.h>                     // Used for malloc, & EXIT codes
#include <assert.h>                         // Used for the assert macro
#include <string.h>                        // For strcmp, strlen, strcpy
#include <glib.h>  // Bring in glib for all doubly-linked list functions
#include "FileIO.h"        // Used for the file access support functions
#include "UserDefined.h"               // All the user defined functions

/** @def  NUMPARAMS
 * @brief This is the expected number of parameters from the command line.
 */
#define NUMPARAMS 2


/*************************************************************************
 *                           Main entry point                            *
 *************************************************************************/
int main (int argc, const char * argv[]) {          // Program entry point
    
   FILE   *fp;                                      // Pointer to the file
   GList * theList_p = NULL;           // Used to test the list operations
   GList * item_p = NULL;                    // Used in the find operation
   node_p  aNode_p;                       // Pointer to a node in the list
   int     nodeValue;         // Test integer for arbitrary integer search

    /* Check if the number of parameters is correct */
    if (argc < NUMPARAMS){
        printf("Need a file with the test data\n");
        printf("Abnormal termination\n");
        exit (EXIT_FAILURE);
    } else {
       fp = fopen (argv[1],"r");           // Open file for read operation
       if (!fp) {                                     // There is an error
            printf ("The filename: %s does not exist or is corrupted\n",
                    argv[1]);
            printf ("Abnormal termination\n");
          exit (EXIT_FAILURE);                    // Terminate the program
        } else {
            
            while (!feof(fp)){

               // Allocate memory for new item from the input file
               /* Note: evaluation order of function arguments is
                * implementation dependent and since both functions read
                * from the SAME input file this can cause problems in some
                * UNIX flavors (e.g. linux/gcc) so serialize the file
                * access
               */
               int number = GetInt(fp);
               char * string = GetString(fp);
               
               aNode_p = NewItem(number, string);
                
#ifdef DEBUG
                printf("Integer read is %d:\n", aNode_p->number);
                printf("String read is %s:\n", aNode_p->theString);
#endif
                /***** Test insertion at the Tail *****/
               theList_p = g_list_append(theList_p, aNode_p);
#ifdef DEBUG
               assert(theList_p != NULL);
#else
               if (theList_p == NULL)
                  perror("Could not insert node");
#endif
            }

            /***** Test deletion at the tail *****/
            printf("Original list:\n");
            if (PrintList(theList_p) != EXIT_SUCCESS)
                printf("Error printing the list\n");

           aNode_p = g_list_last(theList_p)->data;  // Last element address
           theList_p = g_list_remove(theList_p, aNode_p);    // Remove node
           FreeItem(aNode_p);                            // Deallocate data
            
            printf("\n Test deletion from the Tail:\n");
            if (PrintList(theList_p) != EXIT_SUCCESS)
                printf("Error printing the list\n");
            
            /****** Test Insertion at the Head *****/
           aNode_p = NewItem(9, "Gyro Gearloose");          // New element
            
#ifdef DEBUG
            printf("Integer to be inserted at the head %d:\n",
                   aNode_p->number);
            printf("String to be inserted at the head %s:\n",
                   aNode_p->theString);
#endif
           theList_p = g_list_prepend(theList_p, aNode_p);
           printf("\n Test insertion at the Head:\n");
           if (PrintList(theList_p) != EXIT_SUCCESS)
              printf("Error printing the list\n");
            
            /***** Test deletion at the head *****/
           aNode_p = g_list_first(theList_p)->data; // First element address
           theList_p = g_list_remove(theList_p, aNode_p);     // Remove node

#ifdef DEBUG
           assert(aNode_p != NULL);
#else
           if (aNode_p == NULL)
              perror("Could not remove first element from the list");
#endif
           FreeItem(aNode_p);                            // Deallocate data

           printf("\n Test deletion from the Head:\n");
           if (PrintList(theList_p) != EXIT_SUCCESS)
              printf("Error printing the list\n");

           /***** Test finding a node in the list *****/
           item_p = FindInList(theList_p, "Donald", SINGLESTR); // Get index
           if (item_p == NULL){
              perror("Error: failed to find selected node \n");
           }

            /***** Test insertion in the middle *****/
           aNode_p = NewItem(10, "Launchpad");               // New element

           // Insert data before item_p
           theList_p = g_list_insert_before(theList_p, item_p, aNode_p);

#ifdef DEBUG
           assert(theList_p != NULL);
#else
           if (theList_p == NULL)
              perror("Could not insert element somewhere in the middle");
#endif

           printf("\n Test insertion in the middle:\n");
           if (PrintList(theList_p) != EXIT_SUCCESS)
              printf("Error printing the list\n");

           /***** Test deletion in the middle & finding a string *****/
           item_p = FindInList(theList_p, "Donald", SINGLESTR);
           if (item_p == NULL){
              perror("Error: failed to find selected node \n");
           } else {

              aNode_p = item_p->data;
              printf("\nFound element in the list\n");
              PrintItem(aNode_p);

              theList_p = g_list_remove(theList_p, aNode_p); // Remove node
#ifdef DEBUG
              assert(theList_p != NULL);
#else
              if (theList_p == NULL)
                 perror("Could not remove element from middle of the list");
#endif
              FreeItem(aNode_p);                        // Deallocate data

              printf("\n Test deletion from middle:\n");
              if (PrintList(theList_p) != EXIT_SUCCESS)
                 printf("Error printing the list\n");
           }

           /**** Test finding a number in the list ****/
           nodeValue = 6;
           item_p = FindInList(theList_p, &nodeValue, SINGLEINT);
           if (item_p == NULL){
              printf("Error: failed to find selected node \n");
           } else {
              printf("\nFound element %d in the list: \n", nodeValue);
              PrintItem(item_p->data);
           }

           /***** Test copying the list *****/
           printf("\nCreating a copy of the list\n");

           item_p = CopyList(theList_p);
           if (item_p == NULL){
              printf("Error: failed to copy the list \n");
           } else {
              PrintList(item_p);
           }

           /***** Test sorting the list by its number field *****/
           item_p = g_list_sort(item_p, CompareItems);
           if (item_p == NULL){
              printf("Error: failed to sort copy the list \n");
           } else {
              printf("Sorted copy\n");
              PrintList(item_p);
           }

            /***** Destroy the list *****/
           if (DestroyList(theList_p) != EXIT_SUCCESS)
              perror("The list was not destroyed successfully");

           if (DestroyList(item_p) != EXIT_SUCCESS)
              perror("The second list was not destroyed successfullt");
           
        }

        fclose (fp);                        /* Close the input data file */

       return (EXIT_SUCCESS);
    }
}

