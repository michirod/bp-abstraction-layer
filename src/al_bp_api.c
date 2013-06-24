/********************************************************
 **  Authors: Michele Rodolfi, michele.rodolfi@studio.unibo.it
 **           Anna d'Amico, anna.damico2@studio.unibo.it
 **           Carlo Caini (DTNperf_3 project supervisor), carlo.caini@unibo.it
 **
 **
 **  Alma Mater Studiorum, University of Bologna
 ********************************************************/

/*
 * bp_abstraction_layer.c
 *
 */

#include "includes.h"
#include "al_bp_api.h"

/* Implementations API */
#include "al_bp_dtn.h"
#include "al_bp_ion.h"

static al_bp_implementation_t bp_implementation = BP_NONE;

al_bp_implementation_t al_bp_get_implementation()
{
	if (bp_implementation == BP_NONE)
	{
		char* find_dtnd = "ps ax | grep -w dtnd | grep -v grep > /dev/null";
		char* find_ion = "ps ax | grep -w rfxclock | grep -v grep > /dev/null";
		if (system(find_dtnd) == 0)
			bp_implementation = BP_DTN;
		else if (system(find_ion) == 0)
			bp_implementation = BP_ION;
	}
	return bp_implementation;
}

al_bp_error_t al_bp_open(al_bp_handle_t* handle)
{
	if (handle == NULL)
		return BP_ENULLPNTR;

	switch (al_bp_get_implementation())
	{
	case BP_DTN:
		return bp_dtn_open(handle);

	case BP_ION:
		return bp_ion_attach();

	default: // cannot find bundle protocol implementation
		return BP_ENOBPI;
	}
}

al_bp_error_t al_bp_open_with_ip(char *daemon_api_IP,int daemon_api_port,al_bp_handle_t* handle)
{
	if (handle == NULL)
		return BP_ENULLPNTR;

	switch (al_bp_get_implementation())
	{
	case BP_DTN:
		return bp_dtn_open_with_IP(daemon_api_IP, daemon_api_port, handle);

	case BP_ION:
		return bp_ion_open_with_IP(daemon_api_IP, daemon_api_port, handle);

	default: // cannot find bundle protocol implementation
		return BP_ENOBPI;
	}
}

al_bp_error_t al_bp_errno(al_bp_handle_t handle)
{
	switch (al_bp_get_implementation())
	{
	case BP_DTN:
		return bp_dtn_errno(handle);

	case BP_ION:
		return bp_ion_errno(handle);

	default: // cannot find bundle protocol implementation
		return BP_ENOBPI;
	}
}

al_bp_error_t al_bp_build_local_eid(al_bp_handle_t handle,
									al_bp_endpoint_id_t* local_eid,
									const char* service_tag,
									char * type,
									char * eid_destination)
{
	if (local_eid == NULL)
		return BP_ENULLPNTR;

	switch (al_bp_get_implementation())
	{
	case BP_DTN:
		return bp_dtn_build_local_eid(handle, local_eid, service_tag);

	case BP_ION:
		return bp_ion_build_local_eid(local_eid, service_tag,type,eid_destination);

	default: // cannot find bundle protocol implementation
		return BP_ENOBPI;
	}
}

al_bp_error_t al_bp_register(al_bp_handle_t * handle,
		al_bp_reg_info_t* reginfo,
		al_bp_reg_id_t* newregid)
{
	if (reginfo == NULL)
		return BP_ENULLPNTR;
	if (newregid == NULL)
		return BP_ENULLPNTR;

	switch (al_bp_get_implementation())
	{
	case BP_DTN:
		return bp_dtn_register(*handle, reginfo, newregid);

	case BP_ION:
		return bp_ion_register(handle, reginfo, newregid);

	default: // cannot find bundle protocol implementation
		return BP_ENOBPI;
	}
}

al_bp_error_t al_bp_find_registration(al_bp_handle_t handle,
		al_bp_endpoint_id_t * eid,
		al_bp_reg_id_t * newregid)
{
	if (eid == NULL)
		return BP_ENULLPNTR;

	switch (al_bp_get_implementation())
		{
		case BP_DTN:
			return bp_dtn_find_registration(handle, eid, newregid);

		case BP_ION:
			return bp_ion_find_registration(handle, eid, newregid);

		default: // cannot find bundle protocol implementation
			return BP_ENOBPI;
		}
}

al_bp_error_t al_bp_unregister(al_bp_handle_t handle, al_bp_reg_id_t regid,al_bp_endpoint_id_t eid){

	switch (al_bp_get_implementation())
		{
		case BP_DTN:
			return bp_dtn_unregister(handle, regid);

		case BP_ION:
			return bp_ion_unregister(eid);

		default: // cannot find bundle protocol implementation
			return BP_ENOBPI;
		}
}

al_bp_error_t al_bp_send(al_bp_handle_t handle,
		al_bp_reg_id_t regid,
		al_bp_bundle_spec_t* spec,
		al_bp_bundle_payload_t* payload,
		al_bp_bundle_id_t* id)
{
	if (spec == NULL)
		return BP_ENULLPNTR;
	if (payload == NULL)
		return BP_ENULLPNTR;
	if (id == NULL)
		return BP_ENULLPNTR;

	switch (al_bp_get_implementation())
	{
	case BP_DTN:
		return bp_dtn_send(handle, regid, spec, payload, id);

	case BP_ION:
		return bp_ion_send(handle, regid, spec, payload, id);

	default: // cannot find bundle protocol implementation
		return BP_ENOBPI;
	}
}

al_bp_error_t al_bp_recv(al_bp_handle_t handle,
		al_bp_bundle_spec_t* spec,
		al_bp_bundle_payload_location_t location,
		al_bp_bundle_payload_t* payload,
		al_bp_timeval_t timeout)
{
	if (spec == NULL)
		return BP_ENULLPNTR;
	if (payload == NULL)
		return BP_ENULLPNTR;

	switch (al_bp_get_implementation())
	{
	case BP_DTN:
		return bp_dtn_recv(handle, spec, location, payload, timeout);

	case BP_ION:
		return bp_ion_recv(handle, spec, location, payload, timeout);

	default: // cannot find bundle protocol implementation
		return BP_ENOBPI;
	}
}

al_bp_error_t al_bp_close(al_bp_handle_t handle)
{
	switch (al_bp_get_implementation())
	{
	case BP_DTN:
		return bp_dtn_close(handle);

	case BP_ION:
		return bp_ion_close(handle);

	default: // cannot find bundle protocol implementation
		return BP_ENOBPI;
	}
}

al_bp_error_t al_bp_parse_eid_string(al_bp_endpoint_id_t* eid, const char* str)
{
	if (eid == NULL)
		return BP_ENULLPNTR;

	switch (al_bp_get_implementation())
	{
	case BP_DTN:
		return bp_dtn_parse_eid_string(eid, str);

	case BP_ION:
		return bp_ion_parse_eid_string(eid, str);

	default: // cannot find bundle protocol implementation
		return BP_ENOBPI;
	}
}

void al_bp_copy_eid(al_bp_endpoint_id_t* dst, al_bp_endpoint_id_t* src)
{
	switch (al_bp_get_implementation())
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

al_bp_error_t al_bp_get_none_endpoint(al_bp_endpoint_id_t * eid_none)
{
	switch (al_bp_get_implementation())
	{
	case BP_DTN:
		return bp_dtn_parse_eid_string(eid_none, "dtn:none");

	case BP_ION:
		return bp_ion_parse_eid_string(eid_none, "dtn:none");

	default: // cannot find bundle protocol implementation
		return BP_ENOBPI;
	}
}

al_bp_error_t al_bp_set_payload(al_bp_bundle_payload_t* payload,
		al_bp_bundle_payload_location_t location,
		char* val, int len)
{
	if (payload == NULL)
		return BP_ENULLPNTR;

	switch (al_bp_get_implementation())
	{
	case BP_DTN:
		return bp_dtn_set_payload(payload, location, val, len);

	case BP_ION:
		return bp_ion_set_payload(payload, location, val, len);

	default: // cannot find bundle protocol implementation
		return BP_ENOBPI;
	}
}

void al_bp_free_extension_blocks(al_bp_bundle_spec_t* spec)
{
        switch (al_bp_get_implementation())
	{
	case BP_DTN:
		bp_dtn_free_extension_blocks(spec);
		break;

	case BP_ION:
                // NOT IMPLEMENTED
		break;

	default: // cannot find bundle protocol implementation
		return ;
	}
}

void al_bp_free_metadata_blocks(al_bp_bundle_spec_t* spec)
{
        switch (al_bp_get_implementation())
	{
	case BP_DTN:
		bp_dtn_free_metadata_blocks(spec);
		break;

	case BP_ION:
                // NOT IMPLEMENTED
		break;

	default: // cannot find bundle protocol implementation
		return ;
	}
}

void al_bp_free_payload(al_bp_bundle_payload_t* payload)
{
	payload->status_report = NULL;
	switch (al_bp_get_implementation())
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

const char* al_bp_status_report_reason_to_str(al_bp_status_report_reason_t err)
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
char * al_bp_strerror(int err){
	switch(err) {
	    case BP_SUCCESS: 		return "success";
	    case BP_EINVAL: 		return "invalid argument";
	    case BP_ENULLPNTR:		return "operation on a null pointer";
	    case BP_ECONNECT: 		return "error connecting to server";
	    case BP_ETIMEOUT: 		return "operation timed out";
	    case BP_ESIZE: 			return "payload too large";
	    case BP_ENOTFOUND: 		return "not found";
	    case BP_EINTERNAL: 		return "internal error";
	    case BP_EBUSY:     		return "registration already in use";
	    case BP_ENOSPACE:		return "no storage space";
	    case BP_ENOTIMPL:		return "function not yet implemented";
	    case BP_ENOBPI:			return "cannot find bundle protocol implementation";
	    case BP_EATTACH:		return "cannot attach bundle protocol";
	    case BP_EBUILDEID:		return "cannot build local eid";
	    case BP_EOPEN :			return "cannot open the connection whit bp";
	    case BP_EREG:			return "cannot register the eid";
	    case BP_EPARSEEID:		return "cannot parse the endpoint string";
	    case BP_ESEND:			return "cannot send Bundle";
	    case BP_EUNREG:			return "cannot unregister eid";
	    case BP_ERECV:			return "cannot receive bundle";
	    case BP_ERECVINT:		return "receive bundle interrupted";
	    case -1:				return "(invalid error code -1)";
	    default:		   		break;
	    }
	    // there's a small race condition here in case there are two
		// simultaneous calls that will clobber the same buffer, but this
		// should be rare and the worst that happens is that the output
		// string is garbled
		static char buf[128];
		snprintf(buf, sizeof(buf), "(unknown error %d)", err);
		return buf;
}


/********************************************************************
 *
 *             HIGHER LEVEL FUNCTIONS
 *
 ********************************************************************
 */

al_bp_error_t al_bp_bundle_send(al_bp_handle_t handle,
		al_bp_reg_id_t regid,
		al_bp_bundle_object_t * bundle_object)
{
	if (bundle_object == NULL)
		return BP_ENULLPNTR;
	memset(bundle_object->id, 0, sizeof(al_bp_bundle_id_t));
	return al_bp_send(handle, regid, bundle_object->spec, bundle_object->payload, bundle_object->id);
}
al_bp_error_t al_bp_bundle_receive(al_bp_handle_t handle,
		al_bp_bundle_object_t bundle_object,
		al_bp_bundle_payload_location_t payload_location,
		al_bp_timeval_t timeout)
{
	al_bp_free_payload(bundle_object.payload);
	al_bp_free_extension_blocks(bundle_object.spec);
	al_bp_free_metadata_blocks(bundle_object.spec);
	memset(bundle_object.id, 0, sizeof(al_bp_bundle_id_t));
	memset(bundle_object.payload, 0, sizeof(al_bp_bundle_payload_t));
	memset(bundle_object.spec, 0, sizeof(al_bp_bundle_spec_t));
	return al_bp_recv(handle, bundle_object.spec, payload_location, bundle_object.payload, timeout);
}

al_bp_error_t al_bp_bundle_create(al_bp_bundle_object_t * bundle_object)
{
	if (bundle_object == NULL)
		return BP_ENULLPNTR;
	bundle_object->id = (al_bp_bundle_id_t*) malloc(sizeof(al_bp_bundle_id_t));
	bundle_object->spec = (al_bp_bundle_spec_t*) malloc(sizeof(al_bp_bundle_spec_t));
	bundle_object->spec->blocks.blocks_val =
	                (al_bp_extension_block_t*) malloc(sizeof(al_bp_extension_block_t));
	bundle_object->spec->metadata.metadata_val =
	                (al_bp_extension_block_t*) malloc(sizeof(al_bp_extension_block_t));
	bundle_object->payload = (al_bp_bundle_payload_t*) malloc(sizeof(al_bp_bundle_payload_t));
	memset(bundle_object->id, 0, sizeof(al_bp_bundle_id_t));
	memset(bundle_object->spec, 0, sizeof(al_bp_bundle_spec_t));
	memset(bundle_object->payload, 0, sizeof(al_bp_bundle_payload_t));
	return BP_SUCCESS;
}
al_bp_error_t al_bp_bundle_free(al_bp_bundle_object_t * bundle_object)
{
	if (bundle_object == NULL)
		return BP_ENULLPNTR;
	free(bundle_object->id);
	free(bundle_object->spec);
	al_bp_free_payload(bundle_object->payload);
	free(bundle_object->payload);
	return BP_SUCCESS;
}

al_bp_error_t al_bp_bundle_get_id(al_bp_bundle_object_t bundle_object, al_bp_bundle_id_t ** bundle_id)
{
	if (bundle_object.id == NULL)
		return BP_ENULLPNTR;
	*bundle_id = bundle_object.id;
	return BP_SUCCESS;
}
al_bp_error_t al_bp_bundle_get_payload_location(al_bp_bundle_object_t bundle_object, al_bp_bundle_payload_location_t * location)
{
	if (bundle_object.payload == NULL)
		return BP_ENULLPNTR;

	* location = bundle_object.payload->location;

	return BP_SUCCESS;
}

al_bp_error_t al_bp_bundle_set_payload_location(al_bp_bundle_object_t * bundle_object, al_bp_bundle_payload_location_t location)
{
	if (bundle_object == NULL)
		return BP_ENULLPNTR;
	if (bundle_object->payload == NULL)
		return BP_ENULLPNTR;

	bundle_object->payload->location = location;
	return BP_SUCCESS;
}
al_bp_error_t al_bp_bundle_get_payload_size(al_bp_bundle_object_t bundle_object, u32_t * size)
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

al_bp_error_t al_bp_bundle_get_payload_file(al_bp_bundle_object_t bundle_object, char_t ** filename, u32_t * filename_len)
{
	if (bundle_object.payload->location == BP_PAYLOAD_FILE
			|| bundle_object.payload->location == BP_PAYLOAD_TEMP_FILE)
	{
		if (bundle_object.payload->filename.filename_val == NULL) // filename is null
		{
			return BP_ENULLPNTR;
		}
		if (bundle_object.payload->filename.filename_len <= 0) // filename size error
			return BP_EINTERNAL;
		* filename_len = bundle_object.payload->filename.filename_len;
		(* filename) = bundle_object.payload->filename.filename_val;
		return BP_SUCCESS;
	}
	else // bundle location is not file
		return BP_EINVAL;
}
al_bp_error_t al_bp_bundle_get_payload_mem(al_bp_bundle_object_t bundle_object, char ** buf, u32_t * buf_len)
{
	if (bundle_object.payload->location == BP_PAYLOAD_MEM)
	{
		if (bundle_object.payload->buf.buf_val != NULL)
		{
			*buf_len = bundle_object.payload->buf.buf_len;
			(*buf) = bundle_object.payload->buf.buf_val;
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

al_bp_error_t al_bp_bundle_set_payload_file(al_bp_bundle_object_t * bundle_object, char_t * filename, u32_t filename_len)
{
	if (bundle_object == NULL)
		return BP_ENULLPNTR;
	if (filename == NULL)
		return BP_ENULLPNTR;
	if (filename_len <= 0 )
		return BP_EINVAL;

	al_bp_error_t err;

	if (bundle_object->payload == NULL){
		al_bp_bundle_payload_t bundle_payload;
		memset(&bundle_payload, 0, sizeof(bundle_payload));
		err = al_bp_set_payload(& bundle_payload, BP_PAYLOAD_FILE, filename, filename_len);
		bundle_object->payload = & bundle_payload;
	}
	else // payload not null
	{
		memset(bundle_object->payload, 0, sizeof(al_bp_bundle_payload_t));
		err = al_bp_set_payload(bundle_object->payload, BP_PAYLOAD_FILE, filename, filename_len);
	}
	return err;
}
al_bp_error_t al_bp_bundle_set_payload_mem(al_bp_bundle_object_t * bundle_object, char * buf, u32_t buf_len)
{
	if (bundle_object == NULL)
		return BP_ENULLPNTR;
	if (buf_len < 0)
		return BP_EINVAL;

	al_bp_error_t err;

	if (bundle_object->payload == NULL){
		al_bp_bundle_payload_t bundle_payload;
		memset(&bundle_payload, 0, sizeof(bundle_payload));
		err = al_bp_set_payload(& bundle_payload, BP_PAYLOAD_MEM, buf, buf_len);
		bundle_object->payload = & bundle_payload;
	}
	else //payload not null
	{
		memset(bundle_object->payload, 0, sizeof(al_bp_bundle_payload_t));
		err = al_bp_set_payload(bundle_object->payload, BP_PAYLOAD_MEM, buf, buf_len);
	}
	return err;

}

al_bp_error_t al_bp_bundle_get_source(al_bp_bundle_object_t bundle_object, al_bp_endpoint_id_t * source)
{
	if (bundle_object.spec == NULL)
		return BP_ENULLPNTR;
	* source = bundle_object.spec->source;
	return BP_SUCCESS;

}
al_bp_error_t al_bp_bundle_set_source(al_bp_bundle_object_t * bundle_object, al_bp_endpoint_id_t source)
{
	if (bundle_object == NULL)
		return BP_ENULLPNTR;
	if (bundle_object->spec == NULL)
		return BP_ENULLPNTR;
	al_bp_copy_eid(&(bundle_object->spec->source), &source);
	return BP_SUCCESS;
}

al_bp_error_t al_bp_bundle_get_dest(al_bp_bundle_object_t bundle_object, al_bp_endpoint_id_t * dest)
{
	if (bundle_object.spec == NULL)
		return BP_ENULLPNTR;
	* dest = bundle_object.spec->dest;
	return BP_SUCCESS;

}
al_bp_error_t al_bp_bundle_set_dest(al_bp_bundle_object_t * bundle_object, al_bp_endpoint_id_t dest)
{
	if (bundle_object == NULL)
		return BP_ENULLPNTR;
	if (bundle_object->spec == NULL)
		return BP_ENULLPNTR;
	al_bp_copy_eid(&(bundle_object->spec->dest), &dest);
	return BP_SUCCESS;
}

al_bp_error_t al_bp_bundle_get_replyto(al_bp_bundle_object_t bundle_object, al_bp_endpoint_id_t * replyto)
{
	if (bundle_object.spec == NULL)
		return BP_ENULLPNTR;
	* replyto = bundle_object.spec->replyto;
	return BP_SUCCESS;

}
al_bp_error_t al_bp_bundle_set_replyto(al_bp_bundle_object_t * bundle_object, al_bp_endpoint_id_t replyto)
{
	if (bundle_object == NULL)
		return BP_ENULLPNTR;
	if (bundle_object->spec == NULL)
		return BP_ENULLPNTR;
	al_bp_copy_eid(&(bundle_object->spec->replyto), &replyto);
	return BP_SUCCESS;
}

al_bp_error_t al_bp_bundle_get_priority(al_bp_bundle_object_t bundle_object,al_bp_bundle_priority_t * priority)
{
	if (bundle_object.spec == NULL)
		return BP_ENULLPNTR;
	* priority = bundle_object.spec->priority;
	return BP_SUCCESS;
}
al_bp_error_t al_bp_bundle_set_priority(al_bp_bundle_object_t * bundle_object, al_bp_bundle_priority_t priority)
{
	if (bundle_object == NULL)
		return BP_ENULLPNTR;
	if(bundle_object->spec == NULL)
		return BP_ENULLPNTR;
	bundle_object->spec->priority = priority;
	return BP_SUCCESS;
}

al_bp_error_t al_bp_bundle_set_unreliable(al_bp_bundle_object_t * bundle_object, boolean_t unreliable)
{
	if (bundle_object == NULL)
		return BP_ENULLPNTR;
	if(bundle_object->spec == NULL)
		return BP_ENULLPNTR;
	bundle_object->spec->unreliable = unreliable;
		return BP_SUCCESS;
}

al_bp_error_t al_bp_bundle_get_unreliable(al_bp_bundle_object_t bundle_object, boolean_t * unreliable)
{
	if (bundle_object.spec == NULL)
		return BP_ENULLPNTR;
	*unreliable = bundle_object.spec->unreliable;
	return BP_SUCCESS;
}

al_bp_error_t al_bp_bundle_set_critical(al_bp_bundle_object_t * bundle_object, boolean_t critical)
{
	if (bundle_object == NULL)
		return BP_ENULLPNTR;
	if(bundle_object->spec == NULL)
		return BP_ENULLPNTR;
	bundle_object->spec->critical = critical;
		return BP_SUCCESS;
}

al_bp_error_t al_bp_bundle_get_critical(al_bp_bundle_object_t bundle_object, boolean_t * critical)
{
	if (bundle_object.spec == NULL)
		return BP_ENULLPNTR;
	*critical = bundle_object.spec->critical;
	return BP_SUCCESS;
}

al_bp_error_t al_bp_bundle_set_flow_label(al_bp_bundle_object_t * bundle_object, u32_t flow_label)
{
	if (bundle_object == NULL)
		return BP_ENULLPNTR;
	if(bundle_object->spec == NULL)
		return BP_ENULLPNTR;
	bundle_object->spec->flow_label = flow_label;
		return BP_SUCCESS;
}

al_bp_error_t al_bp_bundle_get_flow_label(al_bp_bundle_object_t bundle_object, u32_t * flow_label)
{
	if (bundle_object.spec == NULL)
		return BP_ENULLPNTR;
	*flow_label = bundle_object.spec->flow_label;
	return BP_SUCCESS;
}

al_bp_error_t al_bp_bundle_get_expiration(al_bp_bundle_object_t bundle_object, al_bp_timeval_t * exp)
{
	if (bundle_object.spec == NULL)
		return BP_ENULLPNTR;
	*exp = bundle_object.spec->expiration;
	return BP_SUCCESS;
}
al_bp_error_t al_bp_bundle_set_expiration(al_bp_bundle_object_t * bundle_object, al_bp_timeval_t exp)
{
	if (bundle_object == NULL)
		return BP_ENULLPNTR;
	if(bundle_object->spec == NULL)
		return BP_ENULLPNTR;
	bundle_object->spec->expiration = exp;
	return BP_SUCCESS;
}

al_bp_error_t al_bp_bundle_get_creation_timestamp(al_bp_bundle_object_t bundle_object, al_bp_timestamp_t * ts)
{
	if (bundle_object.spec == NULL)
		return BP_ENULLPNTR;
	*ts = bundle_object.spec->creation_ts;
	return BP_SUCCESS;
}
al_bp_error_t al_bp_bundle_set_creation_timestamp(al_bp_bundle_object_t * bundle_object, al_bp_timestamp_t ts)
{
	if (bundle_object == NULL)
		return BP_ENULLPNTR;
	if(bundle_object->spec == NULL)
		return BP_ENULLPNTR;
	bundle_object->spec->creation_ts = ts;
	return BP_SUCCESS;
}

al_bp_error_t al_bp_bundle_get_delivery_opts(al_bp_bundle_object_t bundle_object, al_bp_bundle_delivery_opts_t * dopts)
{
	if (bundle_object.spec == NULL)
		return BP_ENULLPNTR;
	* dopts = bundle_object.spec->dopts;
	return BP_SUCCESS;
}
al_bp_error_t al_bp_bundle_set_delivery_opts(al_bp_bundle_object_t * bundle_object, al_bp_bundle_delivery_opts_t dopts)
{
	if (bundle_object == NULL)
		return BP_ENULLPNTR;
	if(bundle_object->spec == NULL)
		return BP_ENULLPNTR;
	bundle_object->spec->dopts = dopts;
	return BP_SUCCESS;
}

al_bp_error_t al_bp_bundle_get_status_report(al_bp_bundle_object_t bundle_object, al_bp_bundle_status_report_t ** status_report)
{
	*status_report = bundle_object.payload->status_report;
	return BP_SUCCESS;
}

uint32_t crc_table[256] = {

    0x00000000U,0x04C11DB7U,0x09823B6EU,0x0D4326D9U,
    0x130476DCU,0x17C56B6BU,0x1A864DB2U,0x1E475005U,
    0x2608EDB8U,0x22C9F00FU,0x2F8AD6D6U,0x2B4BCB61U,
    0x350C9B64U,0x31CD86D3U,0x3C8EA00AU,0x384FBDBDU,
    0x4C11DB70U,0x48D0C6C7U,0x4593E01EU,0x4152FDA9U,
    0x5F15ADACU,0x5BD4B01BU,0x569796C2U,0x52568B75U,
    0x6A1936C8U,0x6ED82B7FU,0x639B0DA6U,0x675A1011U,
    0x791D4014U,0x7DDC5DA3U,0x709F7B7AU,0x745E66CDU,
    0x9823B6E0U,0x9CE2AB57U,0x91A18D8EU,0x95609039U,
    0x8B27C03CU,0x8FE6DD8BU,0x82A5FB52U,0x8664E6E5U,
    0xBE2B5B58U,0xBAEA46EFU,0xB7A96036U,0xB3687D81U,
    0xAD2F2D84U,0xA9EE3033U,0xA4AD16EAU,0xA06C0B5DU,
    0xD4326D90U,0xD0F37027U,0xDDB056FEU,0xD9714B49U,
    0xC7361B4CU,0xC3F706FBU,0xCEB42022U,0xCA753D95U,
    0xF23A8028U,0xF6FB9D9FU,0xFBB8BB46U,0xFF79A6F1U,
    0xE13EF6F4U,0xE5FFEB43U,0xE8BCCD9AU,0xEC7DD02DU,
    0x34867077U,0x30476DC0U,0x3D044B19U,0x39C556AEU,
    0x278206ABU,0x23431B1CU,0x2E003DC5U,0x2AC12072U,
    0x128E9DCFU,0x164F8078U,0x1B0CA6A1U,0x1FCDBB16U,
    0x018AEB13U,0x054BF6A4U,0x0808D07DU,0x0CC9CDCAU,
    0x7897AB07U,0x7C56B6B0U,0x71159069U,0x75D48DDEU,
    0x6B93DDDBU,0x6F52C06CU,0x6211E6B5U,0x66D0FB02U,
    0x5E9F46BFU,0x5A5E5B08U,0x571D7DD1U,0x53DC6066U,
    0x4D9B3063U,0x495A2DD4U,0x44190B0DU,0x40D816BAU,
    0xACA5C697U,0xA864DB20U,0xA527FDF9U,0xA1E6E04EU,
    0xBFA1B04BU,0xBB60ADFCU,0xB6238B25U,0xB2E29692U,
    0x8AAD2B2FU,0x8E6C3698U,0x832F1041U,0x87EE0DF6U,
    0x99A95DF3U,0x9D684044U,0x902B669DU,0x94EA7B2AU,
    0xE0B41DE7U,0xE4750050U,0xE9362689U,0xEDF73B3EU,
    0xF3B06B3BU,0xF771768CU,0xFA325055U,0xFEF34DE2U,
    0xC6BCF05FU,0xC27DEDE8U,0xCF3ECB31U,0xCBFFD686U,
    0xD5B88683U,0xD1799B34U,0xDC3ABDEDU,0xD8FBA05AU,
    0x690CE0EEU,0x6DCDFD59U,0x608EDB80U,0x644FC637U,
    0x7A089632U,0x7EC98B85U,0x738AAD5CU,0x774BB0EBU,
    0x4F040D56U,0x4BC510E1U,0x46863638U,0x42472B8FU,
    0x5C007B8AU,0x58C1663DU,0x558240E4U,0x51435D53U,
    0x251D3B9EU,0x21DC2629U,0x2C9F00F0U,0x285E1D47U,
    0x36194D42U,0x32D850F5U,0x3F9B762CU,0x3B5A6B9BU,
    0x0315D626U,0x07D4CB91U,0x0A97ED48U,0x0E56F0FFU,
    0x1011A0FAU,0x14D0BD4DU,0x19939B94U,0x1D528623U,
    0xF12F560EU,0xF5EE4BB9U,0xF8AD6D60U,0xFC6C70D7U,
    0xE22B20D2U,0xE6EA3D65U,0xEBA91BBCU,0xEF68060BU,
    0xD727BBB6U,0xD3E6A601U,0xDEA580D8U,0xDA649D6FU,
    0xC423CD6AU,0xC0E2D0DDU,0xCDA1F604U,0xC960EBB3U,
    0xBD3E8D7EU,0xB9FF90C9U,0xB4BCB610U,0xB07DABA7U,
    0xAE3AFBA2U,0xAAFBE615U,0xA7B8C0CCU,0xA379DD7BU,
    0x9B3660C6U,0x9FF77D71U,0x92B45BA8U,0x9675461FU,
    0x8832161AU,0x8CF30BADU,0x81B02D74U,0x857130C3U,
    0x5D8A9099U,0x594B8D2EU,0x5408ABF7U,0x50C9B640U,
    0x4E8EE645U,0x4A4FFBF2U,0x470CDD2BU,0x43CDC09CU,
    0x7B827D21U,0x7F436096U,0x7200464FU,0x76C15BF8U,
    0x68860BFDU,0x6C47164AU,0x61043093U,0x65C52D24U,
    0x119B4BE9U,0x155A565EU,0x18197087U,0x1CD86D30U,
    0x029F3D35U,0x065E2082U,0x0B1D065BU,0x0FDC1BECU,
    0x3793A651U,0x3352BBE6U,0x3E119D3FU,0x3AD08088U,
    0x2497D08DU,0x2056CD3AU,0x2D15EBE3U,0x29D4F654U,
    0xC5A92679U,0xC1683BCEU,0xCC2B1D17U,0xC8EA00A0U,
    0xD6AD50A5U,0xD26C4D12U,0xDF2F6BCBU,0xDBEE767CU,
    0xE3A1CBC1U,0xE760D676U,0xEA23F0AFU,0xEEE2ED18U,
    0xF0A5BD1DU,0xF464A0AAU,0xF9278673U,0xFDE69BC4U,
    0x89B8FD09U,0x8D79E0BEU,0x803AC667U,0x84FBDBD0U,
    0x9ABC8BD5U,0x9E7D9662U,0x933EB0BBU,0x97FFAD0CU,
    0xAFB010B1U,0xAB710D06U,0xA6322BDFU,0xA2F33668U,
    0xBCB4666DU,0xB8757BDAU,0xB5365D03U,0xB1F740B4U,

};

/* ------------------------------------------
 * calc_crc32_d8
 *
 * Create 32b of CRC
 * ------------------------------------------ */

uint32_t calc_crc32_d8(uint32_t crc, uint8_t *data, int len)
{

	while (len > 0)
	{
		crc = crc_table[*data ^ ((crc >> 24) & 0xff)] ^ (crc << 8);
		data++;
		len--;
	}

	return crc;

}

