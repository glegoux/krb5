/*
 * Ooops.  This file is completely unncessesary, I think.  <sigh>
 *
 * Barr3y
 */

/*
 * $Source$
 * $Author$
 *
 * Copyright 1990 by the Massachusetts Institute of Technology.
 * All Rights Reserved.
 *
 * For copying and distribution information, please see the file
 * <krb5/copyright.h>.
 *
 * This file contains the source code for krb5_scc_default_name.
 */

#if !defined(lint) && !defined(SABER)
static char rcsid_scc_defnam_c[] =
"$Id$";
#endif /* !lint && !SABER */

#include "scc.h"


static char krb5_default_name_string[KRB5_SCC_MAXLEN] = "";

/*
 * Effects:
 * 
 * Forms the default credential cache name for the current user, which
 * is defined in the following way.  If it is set, the environment
 * variable "KRB5CCACHE" will be used (up to the maximum number of
 * characters of a legal operating system defined path).  Otherwise
 * TKT_ROOT (from scc.h) and the user's uid are concatenated to
 * produce the ticket file name (e.g., "/tmp/tkt123").  The pointer
 * returned is to static storage; the name must be copied elsewhere.
 */

char *
krb5_scc_default_name ()
{
     char *krb5ccache, *getenv();
     int len;

     /* Is the environment variable defined? */
     krb5ccache = getenv("KRB5CCACHE");
     if (krb5ccache != NULL) {
	  len = strlen(krb5ccache);
	  len = (len < sizeof(krb5_default_name_string) ? len :
		 sizeof(krb5_default_name_string));
	  
	  strncpy(krb5_default_name_string, krb5ccache, len);
	  krb5_default_name_string[len] = '\0';
     }

     /* No.  Use TKT_ROOT and uid */
     else {
	  /* XXX It'd be nice if we didn't have to pull in printf */
	  sprintf(krb5_default_name_string, "%s%d", TKT_ROOT, getuid());
     }

     return krb5_default_name_string;
}
