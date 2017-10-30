/*
 * bp_abstraction_api.h
 *
 */

#ifndef BP_ABSTRACTION_API_H_
#define BP_ABSTRACTION_API_H_

#include "bp_types.h"
#include "bp_errno.h"

/**
 * Find the underlying implementation of bundle protocol
 */
bp_implementation_t bp_get_implementation();

/**
 * Open a new connection to the router.
 *
 * On success, initializes the handle parameter as a new handle to the
 * daemon and returns BP_SUCCESS. On failure, sets handle to NULL and
 * returns a bp_errno error code.
 */
bp_error_t bp_open(bp_handle_t* handle);

/**
 * Open a new connection to the router witha given IP addr and port
 *
 * On success, initializes the handle parameter as a new handle to the
 * daemon and returns BP_SUCCESS. On failure, sets handle to NULL and
 * returns a bp_errno error code.
 */
bp_error_t bp_open_with_ip(char *daemon_api_IP,int daemon_api_port,bp_handle_t* handle);

/**
 * Get the error associated with the given handle.
 */
bp_error_t bp_errno(bp_handle_t handle);

/**
 * Build an appropriate local endpoint id by appending the specified
 * service tag to the daemon's preferred administrative endpoint id.
 */
bp_error_t bp_build_local_eid(bp_handle_t handle,
                               bp_endpoint_id_t* local_eid,
                               const char* service_tag);


/**
 * Create a bp registration. If the init_passive flag in the reginfo
 * struct is true, the registration is initially in passive state,
 * requiring a call to dtn_bind to activate it. Otherwise, the call to
 * dtn_bind is unnecessary as the registration will be created in the
 * active state and bound to the handle.
 */
bp_error_t bp_register(bp_handle_t handle,
                        bp_reg_info_t* reginfo,
                        bp_reg_id_t* newregid);

/**
 * Check for an existing registration on the given endpoint id,
 * returning BP_SUCCSS and filling in the registration id if it
 * exists, or returning ENOENT if it doesn't.
 */
bp_error_t bp_find_registration(bp_handle_t handle,
		bp_endpoint_id_t * eid,
		bp_reg_id_t * newregid);

/**
 * Send a bundle either from memory or from a file.
 */
bp_error_t bp_send(bp_handle_t handle,
                    bp_reg_id_t regid,
                    bp_bundle_spec_t* spec,
                    bp_bundle_payload_t* payload,
                    bp_bundle_id_t* id);


/**
 * Blocking receive for a bundle, filling in the spec and payload
 * structures with the bundle data. The location parameter indicates
 * the manner by which the caller wants to receive payload data (i.e.
 * either in memory or in a file). The timeout parameter specifies an
 * interval in milliseconds to block on the server-side (-1 means
 * infinite wait).
 *
 * Note that it is advisable to call bp_free_payload on the returned
 * structure, otherwise the XDR routines will memory leak.
 */
bp_error_t bp_recv(bp_handle_t handle,
                    bp_bundle_spec_t* spec,
                    bp_bundle_payload_location_t location,
                    bp_bundle_payload_t* payload,
                    bp_timeval_t timeout);

/**
 * Close an open bp handle.  Returns BP_SUCCESS on success.
 */
bp_error_t bp_close(bp_handle_t handle);



/*************************************************************
 *
 *                     Utility Functions
 *
 *************************************************************/

/**
 * Copy the contents of one eid into another.
 */
void bp_copy_eid(bp_endpoint_id_t* dst, bp_endpoint_id_t* src);

/**
 * Parse a string into an endpoint id structure, validating that it is
 * in fact a valid endpoint id (i.e. a URI).
 */
bp_error_t bp_parse_eid_string(bp_endpoint_id_t* eid, const char* str);

/**
 * Returns the null endpoint
 */
bp_error_t bp_get_none_endpoint(bp_endpoint_id_t * eid_none);

/**
 * Sets the value of the given payload structure to either a memory
 * buffer or a file location.
 *
 * Returns: 0 on success, bp_ESIZE if the memory location is
 * selected and the payload is too big.
 */
bp_error_t bp_set_payload(bp_bundle_payload_t* payload,
                           bp_bundle_payload_location_t location,
                           char* val, int len);

/**
 * Frees dynamic storage allocated by the xdr for a bundle payload in
 * bp_recv.
 */
void bp_free_payload(bp_bundle_payload_t* payload);

/**
 * Return a string version of a status report reason code.
 */
const char* bp_status_report_reason_to_str(bp_status_report_reason_t err);

/********************************************************************
 *
 *             HIGHER LEVEL FUNCTIONS
 *
 ********************************************************************/

/**
 * Send bundle
 * Bundle source, destination and reply to eid must be valid bp endpoints
 */
bp_error_t bp_bundle_send(bp_handle_t handle,
							bp_reg_id_t regid,
							bp_bundle_object_t * bundle_object);

/**
 * Receive bundle
 */
bp_error_t bp_bundle_receive(bp_handle_t handle,
							bp_bundle_object_t bundle_object,
							bp_bundle_payload_location_t payload_location,
							bp_timeval_t timeout);

/**
 * Initialize a bundle object
 */
bp_error_t bp_bundle_create(bp_bundle_object_t * bundle_object);

/**
 * Deallocate memory allocated with bp_bundle_create()
 */
bp_error_t bp_bundle_free(bp_bundle_object_t * bundle_object);

/**
 * Get bundle id
 */
bp_error_t bp_bundle_get_id(bp_bundle_object_t bundle_object, bp_bundle_id_t ** bundle_id);

/**
 * Get Bundle payload location
 */

bp_error_t bp_bundle_set_payload_location(bp_bundle_object_t * bundle_object, bp_bundle_payload_location_t location);
/**
 * Get Bundle payload location
 */

bp_error_t bp_bundle_get_payload_location(bp_bundle_object_t bundle_object, bp_bundle_payload_location_t * location);

/**
 * Get payload size
 * if payload location is BP_PAYLOAD_FILE gets the size of the file
 */
bp_error_t bp_bundle_get_payload_size(bp_bundle_object_t bundle_object, u32_t * size);

/**
 * Get filename of payload
 */
bp_error_t bp_bundle_get_payload_file(bp_bundle_object_t bundle_object, char_t ** filename, u32_t * filename_len);

/**
 * Get pointer of payload buffer
 */
bp_error_t bp_bundle_get_payload_mem(bp_bundle_object_t bundle_object, char ** buf, u32_t * buf_len);

/**
 * Set payload from a file
 */
bp_error_t bp_bundle_set_payload_file(bp_bundle_object_t * bundle_object, char_t * filename, u32_t filename_len);

/**
 * Set payload from memory
 */
bp_error_t bp_bundle_set_payload_mem(bp_bundle_object_t * bundle_object, char * buf, u32_t buf_len);

/**
 * Get bundle source eid
 */
bp_error_t bp_bundle_get_source(bp_bundle_object_t bundle_object, bp_endpoint_id_t * source);

/**
 * Set Bundle Source eid
 */
bp_error_t bp_bundle_set_source(bp_bundle_object_t * bundle_object, bp_endpoint_id_t source);

/**
 * Get bundle destination eid
 */
bp_error_t bp_bundle_get_dest(bp_bundle_object_t bundle_object, bp_endpoint_id_t * dest);

/**
 * Set bundle destination eid
 */
bp_error_t bp_bundle_set_dest(bp_bundle_object_t * bundle_object, bp_endpoint_id_t dest);

/**
 * Get bundle reply-to eid
 */
bp_error_t bp_bundle_get_replyto(bp_bundle_object_t bundle_object, bp_endpoint_id_t * replyto);

/**
 * Set bundle reply-to eid
 */
bp_error_t bp_bundle_set_replyto(bp_bundle_object_t * bundle_object, bp_endpoint_id_t replyto);

/**
 * Get bundle priority
 */
bp_error_t bp_bundle_get_priority(bp_bundle_object_t bundle_object, bp_bundle_priority_t * priority);

/**
 * Set bundle priority
 */
bp_error_t bp_bundle_set_priority(bp_bundle_object_t * bundle_object, bp_bundle_priority_t priority);

/**
 * Get bundle expiration time
 */
bp_error_t bp_bundle_get_expiration(bp_bundle_object_t bundle_object, bp_timeval_t * exp);
/**
 * Set bundle expiration time
 */
bp_error_t bp_bundle_set_expiration(bp_bundle_object_t * bundle_object, bp_timeval_t exp);

/**
 * Get bundle creation timestamp
 */
bp_error_t bp_bundle_get_creation_timestamp(bp_bundle_object_t bundle_object, bp_timestamp_t * ts);
/**
 * Set bundle creation timestamp
 */
bp_error_t bp_bundle_set_creation_timestamp(bp_bundle_object_t * bundle_object, bp_timestamp_t ts);

/**
 * Get bundle delivery options
 */
bp_error_t bp_bundle_get_delivery_opts(bp_bundle_object_t bundle_object, bp_bundle_delivery_opts_t * dopts);
/**
 * Set bundle delivery options
 */
bp_error_t bp_bundle_set_delivery_opts(bp_bundle_object_t * bundle_object, bp_bundle_delivery_opts_t dopts);

/**
 * Get status report.
 * If bundle_object is a status report, status_report is filled with a pointer to the status report structure
 * Otherwise status_report is set to NULL.
 * Returns BP_SUCCESS.
 * Returns BP_EINTERNAL if the bundle is malformed
 */
bp_error_t bp_bundle_get_status_report(bp_bundle_object_t bundle_object, bp_bundle_status_report_t ** status_report);

#endif /* BP_ABSTRACTION_API_H_ */
