/*****************************************************************************
 *  Copyright (C) 2001-2008 The Regents of the University of California.
 *  Produced at Lawrence Livermore National Laboratory (cf, DISCLAIMER).
 *  Written by Andrew Uselton <uselton2@llnl.gov>
 *  UCRL-CODE-2002-008.
 *  
 *  This file is part of PowerMan, a remote power management program.
 *  For details, see <http://www.llnl.gov/linux/powerman/>.
 *  
 *  PowerMan is free software; you can redistribute it and/or modify it under
 *  the terms of the GNU General Public License as published by the Free
 *  Software Foundation; either version 2 of the License, or (at your option)
 *  any later version.
 *  
 *  PowerMan is distributed in the hope that it will be useful, but WITHOUT 
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License 
 *  for more details.
 *  
 *  You should have received a copy of the GNU General Public License along
 *  with PowerMan; if not, write to the Free Software Foundation, Inc.,
 *  59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
\*****************************************************************************/

#ifndef PM_XREGEX_H
#define PM_XREGEX_H

/* A compiled regex.
 */
typedef struct xregex_struct *xregex_t;

/* A container for regexec subexpression match results.
 */
typedef struct xregex_match_struct *xregex_match_t;

/* Create/destroy a regex object.
 */
xregex_t xregex_create(void);
void xregex_destroy(xregex_t x);

/* Compile a regex defined by 's' into a regex object created with 
 * xregex_create().  's' may contain the strings "\n" or "\r" in expanded
 * form and they will be converted into 0xa and 0xd respectively.
 * If 'withsub' is TRUE, the regex will support subexpression matches.
 * Program terminates with detailed message on compilation error.
 */
void xregex_compile(xregex_t x, const char *s, bool withsub);

/* Execute a compiled regex against the provided string 's'.
 * If xm is non-NULL, place match info there.  
 * Returns TRUE on a match.
 */
bool xregex_exec(xregex_t x, const char *s, xregex_match_t xm);

/* Create/destroy/recycle a match result object.  
 * The maximum number of matches is specified at creation in 'nmatch'.
 * Allow one match for main expression, and an additional match for
 * each subexpression.
 */
xregex_match_t xregex_match_create(int nmatch);
void xregex_match_destroy(xregex_match_t xm);
void xregex_match_recycle(xregex_match_t xm);

/* Retrieve a copy of the main/subexpression match specified by 'index',
 * or NULL if no match.   The caller must free result with xfree().
 * Index 0 is for the main expression, other indices are for subexpressions.
 * This function must be called only after xregex_exec().
 */
char *xregex_match_sub_strdup(xregex_match_t xm, int index);

/* Similar to xregex_match_sub_strdup(xm, 0) but includes unmatched 
 * leading text.  Caller must free result with xfree().
 */
char *xregex_match_strdup(xregex_match_t xm);

/* Strlen of above.
 */
int xregex_match_strlen(xregex_match_t xm);

#endif /* PM_XREGEX_H */

/*
 * vi:tabstop=4 shiftwidth=4 expandtab
 */
