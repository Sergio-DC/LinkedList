/**
 * @copyright (c) 2011-2016 Abelardo Lopez Lagunas
 *
 * @file    FileIO.c
 *
 * @author  Abelardo Lopez Lagunas
 *
 * @date    May 16 09:14 2016
 *
 * @brief Support routines that handle reading ASCII files
 *
 * References:
 *          Based on my own code, but won't be surprised if it is
 *          similar to other code out there
 *
 * Restrictions:
 *          Functions return (-1) or NULL in case something went wrong
 *
 * Revision history:
 *          Feb  4 15:15 2011 -- File created
 *
 *          May 22 09:13 2012 -- Added recognition of negative numbers.
 *
 *          Jan 30 15:44 2014 -- Added recognition of strings
 *
 *          Jan 31 17:02 2014 - Fixed potential memory leak by redefining
 *                              how GetString works.
 *
 *          May 16 09:14 2016 - Changed function documentation
 *                              to support Doxygen.
 *
 * @note    Support routine that reads an ASCII file and returns an
 *          integer value skiping over non-numeric data.
 *
 */

#include <stdlib.h>              /* Used for getc() and feof() functions */
#include <ctype.h>                    /* Used for the isdigit() function */
#include <stdio.h>                       /* Used to handle the FILE type */
#include <string.h>                                /* Used for strdup() */
#include <assert.h>                       /* Used for the asser function */
#include "FileIO.h"                                   /* Function header */

/**
 *
 * @brief Read an input file and return an integer value.
 *
 * @b GetInt will read the input file and return an integer representing
 * the ASCII characters that form a number. It skips over comments, which
 * begin a line with a #, and other ASCII characters that do not represent
 * numbers.
 *
 * @param  fp is a pointer to the input text file to parse.
 *
 * @return @c integer value. If the end of file is reached @c EXIT_FAILURE
 * is returned.
 *
 * @code
 *  value = GetInt(inputFile);
 * @endcode
 *
 */
int GetInt (FILE *fp) {
    int	c,i;		 /* Character read and integer representation of it */
    int sign = 1;

    do {
        c = getc (fp); 	                           /* Get next character */
        if ( c == '#' )	                             /* Skip the comment */
            do {
                c = getc (fp);
            } while ( c != '\n');
        if ( c == '-')
            sign = -1;
    } while (!isdigit(c) && !feof(fp));

    if (feof(fp)){
       return (EOF);
    } else {
        /* Found 1st digit, begin conversion until a non-digit is found */
        i = 0;
        while (isdigit (c) && !feof(fp)){
            i = (i*10) + (c - '0');
            c = getc (fp);
        }

     // If the last line is read, the end of file has not been reached
      c = getc (fp);               // See if it was the last line
      if (c != EOF) {
         ungetc(c, fp);            // Not the end put it back
      }

        return (i*sign);
    }
}

/**
 *  @brief Read an input file and return a string value.
 *
 *  @b GetString will read the input file and return a string. It skips over
 *  comments, which begin a line with a #, and other ASCII characters that do
 *  not represent alphabetic characters.
 *
 *  The maximum length of the string is 256 characters. Memory is allocated
 *  by this function and should be freed by the caller.
 *
 * @param  fp is a pointer to the input text file to parse.
 *
 * @return @c string pointer. If the end of file is reached @c EXIT_FAILURE
 * is returned.
 *
 * @code
 *   theString = GetString(inputFile);
 * @endcode
 *
 */
char * GetString (FILE *fp){
   int	c,i;		           // Character read and index of the buffer
   char buffer[BUFSIZE];       // Assume maximum length

   do {
      c = getc (fp); 	                           /* Get next character */
      if ( c == '#' )	                             /* Skip the comment */
         do {
            c = getc (fp);
         } while ( c != '\n');
   } while (!isalpha(c) && !feof(fp));

   if (feof(fp)){
      return (NULL); /* End of file reached and no string was found */
   } else {
      /* Found 1st character, begin conversion until a digit is found */
      i = 0;
      while (isalpha (c) && !feof(fp) && (i < BUFSIZE)){
         buffer[i] = (char) c;
         i++;
         c = getc (fp);
      }
      buffer[i] = '\0';             /* Note how string may be truncated */

      // If the last line is read, the end of file has not been reached
      c = getc (fp);               // See if it was the last line
      if (c != EOF) {
         ungetc(c, fp);            // Not the end put it back
      }

      // Now make a copy fo the buffer and make it into a string
      return strdup(buffer);
   }
}

