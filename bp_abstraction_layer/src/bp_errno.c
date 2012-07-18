/*
 * bp_errno.c
 *
 */


#include <stdio.h>
#include "bp_errno.h"

//----------------------------------------------------------------------

char* bp_strerror(int err)
{
    switch(err) {
    case BP_SUCCESS: 	return "success";
    case BP_EINVAL: 	return "invalid argument";
    case BP_ENULLPNTR:	return "operation on a null pointer";
    case BP_ECONNECT: 	return "error connecting to server";
    case BP_ETIMEOUT: 	return "operation timed out";
    case BP_ESIZE: 		return "payload too large";
    case BP_ENOTFOUND: 	return "not found";
    case BP_EINTERNAL: 	return "internal error";
    case BP_EBUSY:     	return "registration already in use";
    case BP_ENOSPACE:	return "no storage space";
    case BP_ENOTIMPL:	return "function not yet implemented";
    case BP_ENOBPI:		return "cannot find bundle protocol implementation";
    case -1:            return "(invalid error code -1)";
    default:		   	break;
    }
    // there's a small race condition here in case there are two
	// simultaneous calls that will clobber the same buffer, but this
	// should be rare and the worst that happens is that the output
	// string is garbled
	static char buf[128];
	snprintf(buf, sizeof(buf), "(unknown error %d)", err);
	return buf;
}
