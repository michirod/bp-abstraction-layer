/*
 * bp_ion.h
 *
 * Functions interfacing the ion api
 *
 */

#ifndef BP_ION_H_
#define BP_ION_H_

#include "../bp_types.h"
#include "../bp_errno.h"

bp_error_t bp_ion_open(bp_handle_t* handle);

bp_error_t bp_ion_open_with_IP(char * daemon_api_IP, int daemon_api_port, bp_handle_t * handle);

bp_error_t bp_ion_errno(bp_handle_t handle);

bp_error_t bp_ion_build_local_eid(bp_handle_t handle,
                               bp_endpoint_id_t* local_eid,
                               const char* service_tag);


bp_error_t bp_ion_register(bp_handle_t handle,
                        bp_reg_info_t* reginfo,
                        bp_reg_id_t* newregid);

bp_error_t bp_ion_find_registration(bp_handle_t handle,
						bp_endpoint_id_t * eid,
						bp_reg_id_t * newregid);

bp_error_t bp_ion_send(bp_handle_t handle,
                    bp_reg_id_t regid,
                    bp_bundle_spec_t* spec,
                    bp_bundle_payload_t* payload,
                    bp_bundle_id_t* id);

bp_error_t bp_ion_recv(bp_handle_t handle,
                    bp_bundle_spec_t* spec,
                    bp_bundle_payload_location_t location,
                    bp_bundle_payload_t* payload,
                    bp_timeval_t timeout);

bp_error_t bp_ion_close(bp_handle_t handle);

void bp_ion_copy_eid(bp_endpoint_id_t* dst, bp_endpoint_id_t* src);

bp_error_t bp_ion_parse_eid_string(bp_endpoint_id_t* eid, const char* str);

bp_error_t bp_ion_set_payload(bp_bundle_payload_t* payload,
                           bp_bundle_payload_location_t location,
                           char* val, int len);

void bp_ion_free_payload(bp_bundle_payload_t* payload);


/**
 * converts DTN errors in the corresponding bp_error_t values
 */
bp_error_t bp_ion_error(int err);

#endif /* BP_ION_H_ */
