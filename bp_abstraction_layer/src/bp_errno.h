/*
 * bp_errno.h
 *
 */

#ifndef BP_ERRNO_H_
#define BP_ERRNO_H_

/**
 * BP API error codes
 */
typedef enum bp_error_t
{
	BP_SUCCESS = 0, /* ok */
	BP_ERRBASE,		/* Base error code */
	BP_EINVAL, 		/* invalid argument */
	BP_ENULLPNTR,	/* operation on a null pointer */
	BP_ECONNECT, 	/* error connecting to server */
	BP_ETIMEOUT, 	/* operation timed out */
	BP_ESIZE, 	 	/* payload / eid too large */
	BP_ENOTFOUND, 	/* not found (e.g. reg) */
	BP_EINTERNAL, 	/* misc. internal error */
	BP_EBUSY, 	 	/* registration already in use */
	BP_ENOSPACE,	/* no storage space */
	BP_ENOTIMPL,	/* function not yet implemented */
	BP_ENOBPI		/* error NO Bundle Protocol Implementation */
} bp_error_t;

/**
 * Get a string value associated with the bp error code.
 */
char* bp_strerror(int err);

#endif /* BP_ERRNO_H_ */
