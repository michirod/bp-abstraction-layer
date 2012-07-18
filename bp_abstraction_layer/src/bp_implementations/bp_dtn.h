/*
 * bp_dtn.h
 *
 * Functions interfacing the dtn2 api
 *
 */

#ifndef BP_DTN_H_
#define BP_DTN_H_

#include "../bp_types.h"
#include "../bp_errno.h"

#ifdef HAVE_CONFIG_H
#  include <dtn-config.h>
#endif


bp_error_t bp_dtn_open(bp_handle_t* handle);

bp_error_t bp_dtn_open_with_IP(char * daemon_api_IP, int daemon_api_port, bp_handle_t * handle);

bp_error_t bp_dtn_errno(bp_handle_t handle);


bp_error_t bp_dtn_build_local_eid(bp_handle_t handle,
                               bp_endpoint_id_t* local_eid,
                               const char* service_tag);


bp_error_t bp_dtn_register(bp_handle_t handle,
                        bp_reg_info_t* reginfo,
                        bp_reg_id_t* newregid);

bp_error_t bp_dtn_send(bp_handle_t handle,
                    bp_reg_id_t regid,
                    bp_bundle_spec_t* spec,
                    bp_bundle_payload_t* payload,
                    bp_bundle_id_t* id);

bp_error_t bp_dtn_recv(bp_handle_t handle,
                    bp_bundle_spec_t* spec,
                    bp_bundle_payload_location_t location,
                    bp_bundle_payload_t* payload,
                    bp_timeval_t timeout);

bp_error_t bp_dtn_close(bp_handle_t handle);

void bp_dtn_copy_eid(bp_endpoint_id_t* dst, bp_endpoint_id_t* src);

bp_error_t bp_dtn_parse_eid_string(bp_endpoint_id_t* eid, const char* str);

bp_error_t bp_dtn_set_payload(bp_bundle_payload_t* payload,
                           bp_bundle_payload_location_t location,
                           char* val, int len);

void bp_dtn_free_payload(bp_bundle_payload_t* payload);


/**
 * converts DTN errors in the corresponding bp_error_t values
 */
bp_error_t bp_dtn_error(int err);

#endif /* BP_DTN_H_ */
