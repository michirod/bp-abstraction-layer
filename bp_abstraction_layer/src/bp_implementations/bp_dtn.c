/*
 * bp_dtn.c
 *
 */

#include "bp_dtn.h"
#include "bp_dtn_conversions.h"

bp_error_t bp_dtn_open(bp_handle_t* handle)
{
	dtn_handle_t dtn_handle = bp_dtn_handle(*handle);
	int result = dtn_open(& dtn_handle);
	* handle = dtn_bp_handle(dtn_handle);
	return bp_dtn_error(result);
}

bp_error_t bp_dtn_open_with_IP(char * daemon_api_IP, int daemon_api_port, bp_handle_t * handle)
{
	dtn_handle_t dtn_handle = bp_dtn_handle(*handle);
	int result = dtn_open_with_IP(daemon_api_IP, daemon_api_port, & dtn_handle);
	* handle = dtn_bp_handle(dtn_handle);
	return bp_dtn_error(result);
}

bp_error_t bp_dtn_errno(bp_handle_t handle)
{
	dtn_handle_t dtn_handle = bp_dtn_handle(handle);
	int result = dtn_errno(dtn_handle);
	handle = dtn_bp_handle(dtn_handle);
	return bp_dtn_error(result);
}

bp_error_t bp_dtn_build_local_eid(bp_handle_t handle,
                               bp_endpoint_id_t* local_eid,
                               const char* service_tag)
{
	dtn_handle_t dtn_handle = bp_dtn_handle(handle);
	dtn_endpoint_id_t dtn_local_eid = bp_dtn_endpoint_id(*local_eid);
	int result = dtn_build_local_eid(dtn_handle, & dtn_local_eid, service_tag);
	handle = dtn_bp_handle(dtn_handle);
	* local_eid = dtn_bp_endpoint_id(dtn_local_eid);
	return bp_dtn_error(result);

}


bp_error_t bp_dtn_register(bp_handle_t handle,
                        bp_reg_info_t* reginfo,
                        bp_reg_id_t* newregid)
{
	dtn_handle_t dtn_handle = bp_dtn_handle(handle);
	dtn_reg_info_t dtn_reginfo = bp_dtn_reg_info(*reginfo);
	dtn_reg_id_t dtn_newregid = bp_dtn_reg_id(*newregid);
	int result = dtn_register(dtn_handle, & dtn_reginfo, & dtn_newregid);
	handle = dtn_bp_handle(dtn_handle);
	*reginfo = dtn_bp_reg_info(dtn_reginfo);
	*newregid = dtn_bp_reg_id(dtn_newregid);
	return bp_dtn_error(result);
}

bp_error_t bp_dtn_send(bp_handle_t handle,
                    bp_reg_id_t regid,
                    bp_bundle_spec_t* spec,
                    bp_bundle_payload_t* payload,
                    bp_bundle_id_t* id)
{
	dtn_handle_t dtn_handle = bp_dtn_handle(handle);
	dtn_reg_id_t dtn_regid = bp_dtn_reg_id(regid);
	dtn_bundle_spec_t dtn_spec = bp_dtn_bundle_spec(*spec);
	dtn_bundle_payload_t dtn_payload = bp_dtn_bundle_payload(*payload);
	dtn_bundle_id_t dtn_id = bp_dtn_bundle_id(*id);
	int result = dtn_send(dtn_handle, dtn_regid, & dtn_spec, & dtn_payload, & dtn_id);
	handle = dtn_bp_handle(dtn_handle);
	regid = dtn_bp_reg_id(dtn_regid);
	*spec = dtn_bp_bundle_spec(dtn_spec);
	*payload = dtn_bp_bundle_payload(dtn_payload);
	*id = dtn_bp_bundle_id(dtn_id);
	return bp_dtn_error(result);
}

bp_error_t bp_dtn_recv(bp_handle_t handle,
                    bp_bundle_spec_t* spec,
                    bp_bundle_payload_location_t location,
                    bp_bundle_payload_t* payload,
                    bp_timeval_t timeout)
{
	dtn_handle_t dtn_handle = bp_dtn_handle(handle);
	dtn_bundle_spec_t dtn_spec = bp_dtn_bundle_spec(*spec);
	dtn_bundle_payload_location_t dtn_location = bp_dtn_bundle_payload_location(location);
	dtn_bundle_payload_t dtn_payload = bp_dtn_bundle_payload(*payload);
	dtn_timeval_t dtn_timeout = bp_dtn_timeval(timeout);
 	int result = dtn_recv(dtn_handle, & dtn_spec, dtn_location, & dtn_payload, dtn_timeout);
	handle = dtn_bp_handle(dtn_handle);
	*spec = dtn_bp_bundle_spec(dtn_spec);
	location = dtn_bp_bundle_payload_location(dtn_location);
	*payload = dtn_bp_bundle_payload(dtn_payload);
	timeout = dtn_bp_timeval(dtn_timeout);
	return bp_dtn_error(result);
}

bp_error_t bp_dtn_close(bp_handle_t handle)
{
	dtn_handle_t dtn_handle = bp_dtn_handle(handle);
	int result = dtn_close(dtn_handle);
	handle = dtn_bp_handle(dtn_handle);
	return bp_dtn_error(result);
}

void bp_dtn_copy_eid(bp_endpoint_id_t* dst, bp_endpoint_id_t* src)
{
	dtn_endpoint_id_t dtn_dst = bp_dtn_endpoint_id(*dst);
	dtn_endpoint_id_t dtn_src = bp_dtn_endpoint_id(*src);
	dtn_copy_eid(& dtn_dst, & dtn_src);
	*dst = dtn_bp_endpoint_id(dtn_dst);
	*src = dtn_bp_endpoint_id(dtn_src);
}

bp_error_t bp_dtn_parse_eid_string(bp_endpoint_id_t* eid, const char* str)
{
	dtn_endpoint_id_t dtn_eid = bp_dtn_endpoint_id(*eid);
	int result =  dtn_parse_eid_string(& dtn_eid, str);
	*eid = dtn_bp_endpoint_id(dtn_eid);
	return bp_dtn_error(result);
}

bp_error_t bp_dtn_set_payload(bp_bundle_payload_t* payload,
                           bp_bundle_payload_location_t location,
                           char* val, int len)
{
	dtn_bundle_payload_t dtn_payload = bp_dtn_bundle_payload(*payload);
	dtn_bundle_payload_location_t dtn_location = bp_dtn_bundle_payload_location(location);
	int result = dtn_set_payload(& dtn_payload, dtn_location, val, len);
	*payload = dtn_bp_bundle_payload(dtn_payload);
	return bp_dtn_error(result);
}

void bp_dtn_free_payload(bp_bundle_payload_t* payload)
{
	dtn_bundle_payload_t dtn_payload = bp_dtn_bundle_payload(*payload);
	dtn_free_payload(&dtn_payload);
	*payload = dtn_bp_bundle_payload(dtn_payload);
}


bp_error_t bp_dtn_error(int err)
{
	switch (err)
	{
	case DTN_SUCCESS:	return BP_SUCCESS;
	case DTN_EINVAL:	return BP_EINVAL;
	case DTN_ECONNECT:	return BP_ECONNECT;
	case DTN_ETIMEOUT:	return BP_ETIMEOUT;
	case DTN_ESIZE:		return BP_ESIZE;
	case DTN_ENOTFOUND:	return BP_ENOTFOUND;
	case DTN_EINTERNAL: return BP_EINTERNAL;
	case DTN_EBUSY:     return BP_EBUSY;
	case DTN_ENOSPACE:	return BP_ENOSPACE;
	default: 			return -1;
	}
}
