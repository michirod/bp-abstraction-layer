/*
 * bp_abstraction_layer.c
 *
 */

#include "includes.h"
#include "bp_abstraction_api.h"
#include "bp_implementations/bp_dtn.h"
#include "bp_implementations/bp_ion.h"

static bp_implementation_t bp_implementation = BP_NONE;

bp_implementation_t bp_get_implementation()
{
	if (bp_implementation == BP_NONE)
	{
		char* find_dtnd = "ps ax | grep -w dtnd | grep -v grep";
		char* find_ion = "ps ax | grep -w ion | grep -v grep";
		if (system(find_dtnd) == 0)
			bp_implementation = BP_DTN;
		else if (system(find_ion) == 0)
			bp_implementation = BP_ION;
	}
	return bp_implementation;
}

bp_error_t bp_open(bp_handle_t* handle)
{
	if (handle == NULL)
		return BP_ENULLPNTR;

	switch (bp_get_implementation())
	{
	case BP_DTN:
		return bp_dtn_open(handle);

	case BP_ION:
		return bp_ion_open(handle);

	default: // cannot find bundle protocol implementation
		return BP_ENOBPI;
	}
}

bp_error_t bp_open_with_ip(char *daemon_api_IP,int daemon_api_port,bp_handle_t* handle)
{
	if (handle == NULL)
		return BP_ENULLPNTR;

	switch (bp_get_implementation())
	{
	case BP_DTN:
		return bp_dtn_open_with_IP(daemon_api_IP, daemon_api_port, handle);

	case BP_ION:
		return bp_ion_open_with_IP(daemon_api_IP, daemon_api_port, handle);

	default: // cannot find bundle protocol implementation
		return BP_ENOBPI;
	}
}

bp_error_t bp_errno(bp_handle_t handle)
{
	switch (bp_get_implementation())
	{
	case BP_DTN:
		return bp_dtn_errno(handle);

	case BP_ION:
		return bp_ion_errno(handle);

	default: // cannot find bundle protocol implementation
		return BP_ENOBPI;
	}
}


bp_error_t bp_build_local_eid(bp_handle_t handle,
		bp_endpoint_id_t* local_eid,
		const char* service_tag)
{
	if (local_eid == NULL)
		return BP_ENULLPNTR;

	switch (bp_get_implementation())
	{
	case BP_DTN:
		return bp_dtn_build_local_eid(handle, local_eid, service_tag);

	case BP_ION:
		return bp_ion_build_local_eid(handle, local_eid, service_tag);

	default: // cannot find bundle protocol implementation
		return BP_ENOBPI;
	}
}


bp_error_t bp_register(bp_handle_t handle,
		bp_reg_info_t* reginfo,
		bp_reg_id_t* newregid)
{
	if (reginfo == NULL)
		return BP_ENULLPNTR;
	if (newregid == NULL)
		return BP_ENULLPNTR;

	switch (bp_get_implementation())
	{
	case BP_DTN:
		return bp_dtn_register(handle, reginfo, newregid);

	case BP_ION:
		return bp_ion_register(handle, reginfo, newregid);

	default: // cannot find bundle protocol implementation
		return BP_ENOBPI;
	}
}

bp_error_t bp_send(bp_handle_t handle,
		bp_reg_id_t regid,
		bp_bundle_spec_t* spec,
		bp_bundle_payload_t* payload,
		bp_bundle_id_t* id)
{
	if (spec == NULL)
		return BP_ENULLPNTR;
	if (payload == NULL)
		return BP_ENULLPNTR;
	if (id == NULL)
		return BP_ENULLPNTR;

	switch (bp_get_implementation())
	{
	case BP_DTN:
		return bp_dtn_send(handle, regid, spec, payload, id);

	case BP_ION:
		return bp_ion_send(handle, regid, spec, payload, id);

	default: // cannot find bundle protocol implementation
		return BP_ENOBPI;
	}
}

bp_error_t bp_recv(bp_handle_t handle,
		bp_bundle_spec_t* spec,
		bp_bundle_payload_location_t location,
		bp_bundle_payload_t* payload,
		bp_timeval_t timeout)
{
	if (spec == NULL)
		return BP_ENULLPNTR;
	if (payload == NULL)
		return BP_ENULLPNTR;

	switch (bp_get_implementation())
	{
	case BP_DTN:
		return bp_dtn_recv(handle, spec, location, payload, timeout);

	case BP_ION:
		return bp_ion_recv(handle, spec, location, payload, timeout);

	default: // cannot find bundle protocol implementation
		return BP_ENOBPI;
	}
}

bp_error_t bp_close(bp_handle_t handle)
{
	switch (bp_get_implementation())
	{
	case BP_DTN:
		return bp_dtn_close(handle);

	case BP_ION:
		return bp_ion_close(handle);

	default: // cannot find bundle protocol implementation
		return BP_ENOBPI;
	}
}

bp_error_t bp_parse_eid_string(bp_endpoint_id_t* eid, const char* str)
{
	if (eid == NULL)
		return BP_ENULLPNTR;

	switch (bp_get_implementation())
	{
	case BP_DTN:
		return bp_dtn_parse_eid_string(eid, str);

	case BP_ION:
		return bp_ion_parse_eid_string(eid, str);

	default: // cannot find bundle protocol implementation
		return BP_ENOBPI;
	}
}

void bp_copy_eid(bp_endpoint_id_t* dst, bp_endpoint_id_t* src)
{
	switch (bp_get_implementation())
	{
	case BP_DTN:
		bp_dtn_copy_eid(dst, src);
		break;

	case BP_ION:
		bp_ion_copy_eid(dst, src);
		break;

	default: // cannot find bundle protocol implementation
		return ;
	}
}

bp_error_t bp_set_payload(bp_bundle_payload_t* payload,
		bp_bundle_payload_location_t location,
		char* val, int len)
{
	if (payload == NULL)
		return BP_ENULLPNTR;

	switch (bp_get_implementation())
	{
	case BP_DTN:
		return bp_dtn_set_payload(payload, location, val, len);

	case BP_ION:
		return bp_ion_set_payload(payload, location, val, len);

	default: // cannot find bundle protocol implementation
		return BP_ENOBPI;
	}
}

void bp_free_payload(bp_bundle_payload_t* payload)
{
	switch (bp_get_implementation())
	{
	case BP_DTN:
		bp_dtn_free_payload(payload);
		break;

	case BP_ION:
		bp_ion_free_payload(payload);
		break;

	default: // cannot find bundle protocol implementation
		return ;
	}
}

const char* bp_status_report_reason_to_str(bp_status_report_reason_t err)
{
	switch (err) {
	case BP_SR_REASON_NO_ADDTL_INFO:
		return "no additional information";

	case BP_SR_REASON_LIFETIME_EXPIRED:
		return "lifetime expired";

	case BP_SR_REASON_FORWARDED_UNIDIR_LINK:
		return "forwarded over unidirectional link";

	case BP_SR_REASON_TRANSMISSION_CANCELLED:
		return "transmission cancelled";

	case BP_SR_REASON_DEPLETED_STORAGE:
		return "depleted storage";

	case BP_SR_REASON_ENDPOINT_ID_UNINTELLIGIBLE:
		return "endpoint id unintelligible";

	case BP_SR_REASON_NO_ROUTE_TO_DEST:
		return "no known route to destination";

	case BP_SR_REASON_NO_TIMELY_CONTACT:
		return "no timely contact";

	case BP_SR_REASON_BLOCK_UNINTELLIGIBLE:
		return "block unintelligible";

	default:
		return "(unknown reason)";
	}
}

/********************************************************************
 *
 *             HIGHER LEVEL FUNCTIONS
 *
 ********************************************************************
 */

bp_error_t bp_bundle_send(bp_handle_t handle,
		bp_reg_id_t regid,
		bp_bundle_object_t * bundle_object)
{
	if (bundle_object == NULL)
		return BP_ENULLPNTR;
	memset(bundle_object->id, 0, sizeof(bp_bundle_id_t));
	return bp_send(handle, regid, bundle_object->spec, bundle_object->payload, bundle_object->id);
}

bp_error_t bp_bundle_receive(bp_handle_t handle,
		bp_bundle_object_t bundle_object,
		bp_bundle_payload_location_t payload_location,
		bp_timeval_t timeout)
{
	bp_free_payload(bundle_object.payload);
	memset(bundle_object.spec, 0, sizeof(bp_bundle_spec_t));
	return bp_recv(handle, bundle_object.spec, payload_location, bundle_object.payload, timeout);
}

bp_error_t bp_bundle_create(bp_bundle_object_t * bundle_object)
{
	if (bundle_object == NULL)
		return BP_ENULLPNTR;
	bundle_object->id = (bp_bundle_id_t*) malloc(sizeof(bp_bundle_id_t));
	bundle_object->spec = (bp_bundle_spec_t*) malloc(sizeof(bp_bundle_spec_t));
	bundle_object->payload = (bp_bundle_payload_t*) malloc(sizeof(bp_bundle_payload_t));
	memset(bundle_object->id, 0, sizeof(bp_bundle_id_t));
	memset(bundle_object->spec, 0, sizeof(bp_bundle_spec_t));
	memset(bundle_object->payload, 0, sizeof(bp_bundle_payload_t));
	return BP_SUCCESS;
}

bp_error_t bp_bundle_free(bp_bundle_object_t * bundle_object)
{
	if (bundle_object == NULL)
		return BP_ENULLPNTR;
	free(bundle_object->id);
	free(bundle_object->spec);
	free(bundle_object->payload);
	return BP_SUCCESS;
}

bp_error_t bp_bundle_get_id(bp_bundle_object_t bundle_object, bp_bundle_id_t ** bundle_id)
{
	if (bundle_object.id == NULL)
		return BP_ENULLPNTR;
	*bundle_id = bundle_object.id;
	return BP_SUCCESS;
}

bp_error_t bp_bundle_get_payload_location(bp_bundle_object_t bundle_object, bp_bundle_payload_location_t * location)
{
	if (bundle_object.payload == NULL)
		return BP_ENULLPNTR;

	* location = bundle_object.payload->location;

	return BP_SUCCESS;
}

bp_error_t bp_bundle_get_payload_size(bp_bundle_object_t bundle_object, u32_t * size)
{
	if (bundle_object.payload == NULL)
		return BP_ENULLPNTR;

	if (bundle_object.payload->location == BP_PAYLOAD_MEM)
	{
		if (bundle_object.payload->buf.buf_val != NULL)
		{
			* size = bundle_object.payload->buf.buf_len;
			return BP_SUCCESS;
		}
		else
		{ // buffer is null
			return BP_ENULLPNTR;
		}
	}
	else if (bundle_object.payload->location == BP_PAYLOAD_FILE
			|| bundle_object.payload->location == BP_PAYLOAD_TEMP_FILE)
	{
		if (bundle_object.payload->filename.filename_val == NULL) // filename is null
			return BP_ENULLPNTR;

		struct stat st;
		memset(&st, 0, sizeof(st));
		if (stat(bundle_object.payload->filename.filename_val, &st) < 0)
		{
			perror("Error in checking bundle payload file");
			return BP_EINTERNAL;
		}
		*size = st.st_size;
		return BP_SUCCESS;

	}
	else { // wrong payload location
		return BP_EINTERNAL;
	}
}

bp_error_t bp_bundle_get_payload_file(bp_bundle_object_t bundle_object, char_t ** filename, u32_t * filename_len)
{
	if (bundle_object.payload->location == BP_PAYLOAD_FILE
			|| bundle_object.payload->location == BP_PAYLOAD_TEMP_FILE)
	{
		if (bundle_object.payload->filename.filename_val == NULL) // filename is null
			return BP_ENULLPNTR;
		if (bundle_object.payload->filename.filename_len <= 0) // filename size error
			return BP_EINTERNAL;
		* filename_len = bundle_object.payload->filename.filename_len;
		* filename = bundle_object.payload->filename.filename_val;
		return BP_SUCCESS;
	}
	else // bundle location is not file
		return BP_EINVAL;
}

bp_error_t bp_bundle_get_payload_mem(bp_bundle_object_t bundle_object, char ** buf, u32_t * buf_len)
{
	if (bundle_object.payload->location == BP_PAYLOAD_MEM)
	{
		if (bundle_object.payload->buf.buf_val != NULL)
		{
			*buf = bundle_object.payload->buf.buf_val;
			*buf_len = bundle_object.payload->buf.buf_len;
			return BP_SUCCESS;
		}
		else
		{ // buffer is null
			return BP_ENULLPNTR;
		}
	}
	else // bundle location is not memory
		return BP_EINVAL;
}

bp_error_t bp_bundle_set_payload_file(bp_bundle_object_t * bundle_object, char_t * filename, u32_t filename_len)
{
	if (bundle_object == NULL)
		return BP_ENULLPNTR;
	if (filename == NULL)
		return BP_ENULLPNTR;
	if (filename_len <= 0 )
		return BP_EINVAL;

	bp_error_t err;

	if (bundle_object->payload == NULL){
		bp_bundle_payload_t bundle_payload;
		memset(&bundle_payload, 0, sizeof(bundle_payload));
		err = bp_set_payload(& bundle_payload, BP_PAYLOAD_FILE, filename, filename_len);
		bundle_object->payload = & bundle_payload;
	}
	else // payload not null
	{
		memset(bundle_object->payload, 0, sizeof(bp_bundle_payload_t));
		err = bp_set_payload(bundle_object->payload, BP_PAYLOAD_FILE, filename, filename_len);
	}
	return err;
}

bp_error_t bp_bundle_set_payload_mem(bp_bundle_object_t * bundle_object, char * buf, u32_t buf_len)
{
	if (bundle_object == NULL)
		return BP_ENULLPNTR;
	if (buf == NULL )
		return BP_ENULLPNTR;
	if (buf_len < 0)
		return BP_EINVAL;

	bp_error_t err;

	if (bundle_object->payload == NULL){
		bp_bundle_payload_t bundle_payload;
		memset(&bundle_payload, 0, sizeof(bundle_payload));
		err = bp_set_payload(& bundle_payload, BP_PAYLOAD_MEM, buf, buf_len);
		bundle_object->payload = & bundle_payload;
	}
	else //payload not null
	{
		memset(bundle_object->payload, 0, sizeof(bp_bundle_payload_t));
		err = bp_set_payload(bundle_object->payload, BP_PAYLOAD_MEM, buf, buf_len);
	}
	return err;

}

bp_error_t bp_bundle_get_source(bp_bundle_object_t bundle_object, bp_endpoint_id_t * source)
{
	if (bundle_object.spec == NULL)
		return BP_ENULLPNTR;
	* source = bundle_object.spec->source;
	return BP_SUCCESS;

}

bp_error_t bp_bundle_set_source(bp_bundle_object_t * bundle_object, bp_endpoint_id_t source)
{
	if (bundle_object == NULL)
		return BP_ENULLPNTR;
	if (bundle_object->spec == NULL)
		return BP_ENULLPNTR;
	bp_copy_eid(&(bundle_object->spec->source), &source);
	return BP_SUCCESS;
}

bp_error_t bp_bundle_get_dest(bp_bundle_object_t bundle_object, bp_endpoint_id_t * dest)
{
	if (bundle_object.spec == NULL)
		return BP_ENULLPNTR;
	* dest = bundle_object.spec->dest;
	return BP_SUCCESS;

}

bp_error_t bp_bundle_set_dest(bp_bundle_object_t * bundle_object, bp_endpoint_id_t dest)
{
	if (bundle_object == NULL)
		return BP_ENULLPNTR;
	if (bundle_object->spec == NULL)
		return BP_ENULLPNTR;
	bp_copy_eid(&(bundle_object->spec->dest), &dest);
	return BP_SUCCESS;
}

bp_error_t bp_bundle_get_replyto(bp_bundle_object_t bundle_object, bp_endpoint_id_t * replyto)
{
	if (bundle_object.spec == NULL)
		return BP_ENULLPNTR;
	* replyto = bundle_object.spec->replyto;
	return BP_SUCCESS;

}

bp_error_t bp_bundle_set_replyto(bp_bundle_object_t * bundle_object, bp_endpoint_id_t replyto)
{
	if (bundle_object == NULL)
		return BP_ENULLPNTR;
	if (bundle_object->spec == NULL)
		return BP_ENULLPNTR;
	bp_copy_eid(&(bundle_object->spec->replyto), &replyto);
	return BP_SUCCESS;
}

bp_error_t bp_bundle_get_priority(bp_bundle_object_t bundle_object, bp_bundle_priority_t * priority)
{
	if (bundle_object.spec == NULL)
		return BP_ENULLPNTR;
	* priority = bundle_object.spec->priority;
	return BP_SUCCESS;
}

bp_error_t bp_bundle_set_priority(bp_bundle_object_t * bundle_object, bp_bundle_priority_t priority)
{
	if (bundle_object == NULL)
		return BP_ENULLPNTR;
	if(bundle_object->spec == NULL)
		return BP_ENULLPNTR;
	bundle_object->spec->priority = priority;
	return BP_SUCCESS;
}

bp_error_t bp_bundle_get_expiration(bp_bundle_object_t bundle_object, bp_timeval_t * exp)
{
	if (bundle_object.spec == NULL)
		return BP_ENULLPNTR;
	*exp = bundle_object.spec->expiration;
	return BP_SUCCESS;
}
bp_error_t bp_bundle_set_expiration(bp_bundle_object_t * bundle_object, bp_timeval_t exp)
{
	if (bundle_object == NULL)
		return BP_ENULLPNTR;
	if(bundle_object->spec == NULL)
		return BP_ENULLPNTR;
	bundle_object->spec->expiration = exp;
	return BP_SUCCESS;
}


bp_error_t bp_bundle_get_creation_timestamp(bp_bundle_object_t bundle_object, bp_timestamp_t * ts)
{
	if (bundle_object.spec == NULL)
		return BP_ENULLPNTR;
	*ts = bundle_object.spec->creation_ts;
	return BP_SUCCESS;
}
bp_error_t bp_bundle_set_creation_timestamp(bp_bundle_object_t * bundle_object, bp_timestamp_t ts)
{
	if (bundle_object == NULL)
		return BP_ENULLPNTR;
	if(bundle_object->spec == NULL)
		return BP_ENULLPNTR;
	bundle_object->spec->creation_ts = ts;
	return BP_SUCCESS;
}


bp_error_t bp_bundle_get_delivery_opts(bp_bundle_object_t bundle_object, bp_bundle_delivery_opts_t * dopts)
{
	if (bundle_object.spec == NULL)
		return BP_ENULLPNTR;
	* dopts = bundle_object.spec->dopts;
	return BP_SUCCESS;
}

bp_error_t bp_bundle_set_delivery_opts(bp_bundle_object_t * bundle_object, bp_bundle_delivery_opts_t dopts)
{
	if (bundle_object == NULL)
		return BP_ENULLPNTR;
	if(bundle_object->spec == NULL)
		return BP_ENULLPNTR;
	bundle_object->spec->dopts = dopts;
	return BP_SUCCESS;
}



