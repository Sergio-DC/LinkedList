/**
 * @copyright (c) 2011-2016 Abelardo Lopez Lagunas
 *
 * @file    FileIO.h
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

#define BUFSIZE 256   // Buffer size for string management

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
int GetInt (FILE *fp);

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
char * GetString (FILE *fp);

