/*
 * bp_dtn_conversions.c
 *
 */
#include "bp_dtn_conversions.h"

dtn_handle_t bp_dtn_handle(bp_handle_t handle)
{
	return (dtn_handle_t) handle;
}
bp_handle_t dtn_bp_handle(dtn_handle_t handle)
{
	return (bp_handle_t) handle;
}

dtn_endpoint_id_t bp_dtn_endpoint_id(bp_endpoint_id_t endpoint_id)
{
	dtn_endpoint_id_t dtn_eid;
	strncpy(dtn_eid.uri, endpoint_id.uri, DTN_MAX_ENDPOINT_ID);
	return dtn_eid;
}
bp_endpoint_id_t dtn_bp_endpoint_id(dtn_endpoint_id_t endpoint_id)
{
	bp_endpoint_id_t bp_eid;
	strncpy(bp_eid.uri, endpoint_id.uri, BP_MAX_ENDPOINT_ID);
	return bp_eid;
}

dtn_timeval_t bp_dtn_timeval(bp_timeval_t timeval)
{
	return (bp_timeval_t) timeval;
}
bp_timeval_t dtn_bp_timeval(dtn_timeval_t timeval)
{
	return (dtn_timeval_t) timeval;
}

dtn_timestamp_t bp_dtn_timestamp(bp_timestamp_t timestamp)
{
	dtn_timestamp_t dtn_timestamp;
	dtn_timestamp.secs = timestamp.secs;
	dtn_timestamp.seqno = timestamp.seqno;
	return dtn_timestamp;
}
bp_timestamp_t dtn_bp_timestamp(dtn_timestamp_t timestamp)
{
	bp_timestamp_t bp_timestamp;
	bp_timestamp.secs = timestamp.secs;
	bp_timestamp.seqno = timestamp.seqno;
	return bp_timestamp;
}

dtn_reg_token_t bp_dtn_reg_token(bp_reg_token_t reg_token)
{
	return (dtn_reg_token_t) reg_token;
}
bp_reg_token_t dtn_bp_reg_token(dtn_reg_token_t reg_token)
{
	return (bp_reg_token_t) reg_token;

}

dtn_reg_id_t bp_dtn_reg_id(bp_reg_id_t reg_id)
{
	return (dtn_reg_id_t) reg_id;
}
bp_reg_id_t dtn_bp_reg_id(dtn_reg_id_t reg_id)
{
	return (bp_reg_id_t) reg_id;
}

dtn_reg_info_t bp_dtn_reg_info(bp_reg_info_t reg_info)
{
	dtn_reg_info_t dtn_reginfo;
	dtn_reginfo.endpoint = bp_dtn_endpoint_id(reg_info.endpoint);
	dtn_reginfo.regid = bp_dtn_reg_id(reg_info.regid);
	dtn_reginfo.flags = reg_info.flags;
	dtn_reginfo.replay_flags = reg_info.replay_flags;
	dtn_reginfo.expiration = bp_dtn_timeval(reg_info.expiration);
	dtn_reginfo.reg_token = bp_dtn_reg_token(reg_info.reg_token);
	dtn_reginfo.init_passive = reg_info.init_passive;
	dtn_reginfo.script.script_len = reg_info.script.script_len;
	if (reg_info.script.script_len == 0)
	{
		dtn_reginfo.script.script_val = NULL;
	}
	else
	{
		dtn_reginfo.script.script_val = (char*) malloc(reg_info.script.script_len + 1);
		strncpy(dtn_reginfo.script.script_val, reg_info.script.script_val, reg_info.script.script_len + 1);
	}
	return dtn_reginfo;
}
bp_reg_info_t dtn_bp_reg_info(dtn_reg_info_t reg_info)
{
	bp_reg_info_t bp_reginfo;
	bp_reginfo.endpoint = dtn_bp_endpoint_id(reg_info.endpoint);
	bp_reginfo.regid = dtn_bp_reg_id(reg_info.regid);
	bp_reginfo.flags = reg_info.flags;
	bp_reginfo.replay_flags = reg_info.replay_flags;
	bp_reginfo.expiration = dtn_bp_timeval(reg_info.expiration);
	bp_reginfo.reg_token = dtn_bp_reg_token(reg_info.reg_token);
	bp_reginfo.init_passive = reg_info.init_passive;
	bp_reginfo.script.script_len = reg_info.script.script_len;
	if (reg_info.script.script_len == 0)
	{
		bp_reginfo.script.script_val = NULL;
	}
	else
	{
		bp_reginfo.script.script_val = (char*) malloc(reg_info.script.script_len + 1);
		strncpy(bp_reginfo.script.script_val, reg_info.script.script_val, reg_info.script.script_len + 1);
	}
	return bp_reginfo;
}

dtn_reg_flags_t bp_dtn_reg_flags(bp_reg_flags_t reg_flags)
{
	return (dtn_reg_flags_t) reg_flags;
}
bp_reg_flags_t dtn_bp_reg_flags(dtn_reg_flags_t reg_flags)
{
	return (bp_reg_flags_t) reg_flags;
}

dtn_bundle_delivery_opts_t bp_dtn_bundle_delivery_opts(bp_bundle_delivery_opts_t bundle_delivery_opts)
{
	return (dtn_bundle_delivery_opts_t) bundle_delivery_opts;
}
bp_bundle_delivery_opts_t dtn_bp_bundle_delivery_opts(dtn_bundle_delivery_opts_t bundle_delivery_opts)
{
	return (bp_bundle_delivery_opts_t) bundle_delivery_opts;
}


dtn_bundle_priority_t bp_dtn_bundle_priority(bp_bundle_priority_t bundle_priority)
{
	return (dtn_bundle_priority_t) bundle_priority;
}
bp_bundle_priority_t dtn_bp_bundle_priority(dtn_bundle_priority_t bundle_priority)
{
	return (bp_bundle_priority_t) bundle_priority;
}

dtn_bundle_spec_t bp_dtn_bundle_spec(bp_bundle_spec_t bundle_spec)
{
	dtn_bundle_spec_t dtn_bundle_spec;
	dtn_bundle_spec.source = bp_dtn_endpoint_id(bundle_spec.source);
	dtn_bundle_spec.dest = bp_dtn_endpoint_id(bundle_spec.dest);
	dtn_bundle_spec.replyto = bp_dtn_endpoint_id(bundle_spec.replyto);
	dtn_bundle_spec.priority = bp_dtn_bundle_priority(bundle_spec.priority);
	dtn_bundle_spec.dopts = bp_dtn_bundle_delivery_opts(bundle_spec.dopts);
	dtn_bundle_spec.expiration = bp_dtn_timeval(bundle_spec.expiration);
	dtn_bundle_spec.creation_ts = bp_dtn_timestamp(bundle_spec.creation_ts);
	dtn_bundle_spec.delivery_regid = bp_dtn_reg_id(bundle_spec.delivery_regid);
	return dtn_bundle_spec;
}
bp_bundle_spec_t dtn_bp_bundle_spec(dtn_bundle_spec_t bundle_spec)
{
	bp_bundle_spec_t bp_bundle_spec;
	bp_bundle_spec.source = dtn_bp_endpoint_id(bundle_spec.source);
	bp_bundle_spec.dest = dtn_bp_endpoint_id(bundle_spec.dest);
	bp_bundle_spec.replyto = dtn_bp_endpoint_id(bundle_spec.replyto);
	bp_bundle_spec.priority = dtn_bp_bundle_priority(bundle_spec.priority);
	bp_bundle_spec.dopts = dtn_bp_bundle_delivery_opts(bundle_spec.dopts);
	bp_bundle_spec.expiration = dtn_bp_timeval(bundle_spec.expiration);
	bp_bundle_spec.creation_ts = dtn_bp_timestamp(bundle_spec.creation_ts);
	bp_bundle_spec.delivery_regid = dtn_bp_reg_id(bundle_spec.delivery_regid);
	return bp_bundle_spec;
}

dtn_bundle_payload_location_t bp_dtn_bundle_payload_location(bp_bundle_payload_location_t bundle_payload_location)
{
	return (dtn_bundle_payload_location_t) bundle_payload_location;
}
bp_bundle_payload_location_t dtn_bp_bundle_payload_location(dtn_bundle_payload_location_t bundle_payload_location)
{
	return (bp_bundle_payload_location_t) bundle_payload_location;
}

dtn_status_report_reason_t bp_dtn_status_report_reason(bp_status_report_reason_t status_report_reason)
{
	return (dtn_status_report_reason_t) status_report_reason;
}
bp_status_report_reason_t dtn_bp_status_report_reason(dtn_status_report_reason_t status_report_reason)
{
	return (bp_status_report_reason_t) status_report_reason;
}

dtn_status_report_flags_t bp_dtn_status_report_flags(bp_status_report_flags_t status_report_flags)
{
	return (dtn_status_report_flags_t) status_report_flags;
}
bp_status_report_flags_t dtn_bp_status_report_flags(dtn_status_report_flags_t status_report_flags)
{
	return (bp_status_report_flags_t) status_report_flags;
}

dtn_bundle_id_t bp_dtn_bundle_id(bp_bundle_id_t bundle_id)
{
	dtn_bundle_id_t dtn_bundle_id;
	dtn_bundle_id.source = bp_dtn_endpoint_id(bundle_id.source);
	dtn_bundle_id.creation_ts = bp_dtn_timestamp(bundle_id.creation_ts);
	dtn_bundle_id.frag_offset = bundle_id.frag_offset;
	dtn_bundle_id.orig_length = bundle_id.orig_length;
	return dtn_bundle_id;
}
bp_bundle_id_t dtn_bp_bundle_id(dtn_bundle_id_t bundle_id)
{
	bp_bundle_id_t bp_bundle_id;
	bp_bundle_id.source = dtn_bp_endpoint_id(bundle_id.source);
	bp_bundle_id.creation_ts = dtn_bp_timestamp(bundle_id.creation_ts);
	bp_bundle_id.frag_offset = bundle_id.frag_offset;
	bp_bundle_id.orig_length = bundle_id.orig_length;
	return bp_bundle_id;
}

dtn_bundle_status_report_t bp_dtn_bundle_status_report(bp_bundle_status_report_t bundle_status_report)
{
	dtn_bundle_status_report_t dtn_bundle_status_report;
	dtn_bundle_status_report.bundle_id = bp_dtn_bundle_id(bundle_status_report.bundle_id);
	dtn_bundle_status_report.reason = bp_dtn_status_report_reason(bundle_status_report.reason);
	dtn_bundle_status_report.flags = bp_dtn_status_report_flags(bundle_status_report.flags);
	dtn_bundle_status_report.receipt_ts = bp_dtn_timestamp(bundle_status_report.receipt_ts);
	dtn_bundle_status_report.custody_ts = bp_dtn_timestamp(bundle_status_report.custody_ts);
	dtn_bundle_status_report.forwarding_ts = bp_dtn_timestamp(bundle_status_report.forwarding_ts);
	dtn_bundle_status_report.delivery_ts = bp_dtn_timestamp(bundle_status_report.delivery_ts);
	dtn_bundle_status_report.deletion_ts = bp_dtn_timestamp(bundle_status_report.deletion_ts);
	dtn_bundle_status_report.ack_by_app_ts = bp_dtn_timestamp(bundle_status_report.ack_by_app_ts);
	return dtn_bundle_status_report;
}
bp_bundle_status_report_t dtn_bp_bundle_status_report(dtn_bundle_status_report_t bundle_status_report)
{
	bp_bundle_status_report_t bp_bundle_status_report;
	bp_bundle_status_report.bundle_id = dtn_bp_bundle_id(bundle_status_report.bundle_id);
	bp_bundle_status_report.reason = dtn_bp_status_report_reason(bundle_status_report.reason);
	bp_bundle_status_report.flags = dtn_bp_status_report_flags(bundle_status_report.flags);
	bp_bundle_status_report.receipt_ts = dtn_bp_timestamp(bundle_status_report.receipt_ts);
	bp_bundle_status_report.custody_ts = dtn_bp_timestamp(bundle_status_report.custody_ts);
	bp_bundle_status_report.forwarding_ts = dtn_bp_timestamp(bundle_status_report.forwarding_ts);
	bp_bundle_status_report.delivery_ts = dtn_bp_timestamp(bundle_status_report.delivery_ts);
	bp_bundle_status_report.deletion_ts = dtn_bp_timestamp(bundle_status_report.deletion_ts);
	bp_bundle_status_report.ack_by_app_ts = dtn_bp_timestamp(bundle_status_report.ack_by_app_ts);
	return bp_bundle_status_report;
}

dtn_bundle_payload_t bp_dtn_bundle_payload(bp_bundle_payload_t bundle_payload)
{
	dtn_bundle_payload_t dtn_bundle_payload;
	memset(&dtn_bundle_payload, 0, sizeof(dtn_bundle_payload));
	dtn_bundle_payload.location = bp_dtn_bundle_payload_location(bundle_payload.location);
	dtn_bundle_payload.filename.filename_len = bundle_payload.filename.filename_len;
	if (bundle_payload.filename.filename_len == 0)
	{
		dtn_bundle_payload.filename.filename_val = NULL;
	}
	else
	{
		dtn_bundle_payload.filename.filename_val = (char*) malloc(bundle_payload.filename.filename_len + 1);
		strncpy(dtn_bundle_payload.filename.filename_val, bundle_payload.filename.filename_val, bundle_payload.filename.filename_len + 1);
	}
	dtn_bundle_payload.buf.buf_len = bundle_payload.buf.buf_len;
	if (bundle_payload.buf.buf_len == 0)
	{
		dtn_bundle_payload.buf.buf_val = NULL;
	}
	else
	{
		dtn_bundle_payload.buf.buf_val = (char*) malloc(bundle_payload.buf.buf_len);
		memcpy(dtn_bundle_payload.buf.buf_val, bundle_payload.buf.buf_val, bundle_payload.buf.buf_len);
	}
	if (bundle_payload.status_report == NULL)
	{
		dtn_bundle_payload.status_report = NULL;
	}
	else
	{
		dtn_bundle_status_report_t dtn_bundle_status_report = bp_dtn_bundle_status_report(*(bundle_payload.status_report));
		dtn_bundle_payload.status_report = & dtn_bundle_status_report;
	}
	return dtn_bundle_payload;
}
bp_bundle_payload_t dtn_bp_bundle_payload(dtn_bundle_payload_t bundle_payload)
{
	bp_bundle_payload_t bp_bundle_payload;
	memset(&bp_bundle_payload, 0, sizeof(bp_bundle_payload));
	bp_bundle_payload.location = dtn_bp_bundle_payload_location(bundle_payload.location);
	bp_bundle_payload.filename.filename_len = bundle_payload.filename.filename_len;
	if (bundle_payload.filename.filename_len == 0)
	{
		bp_bundle_payload.filename.filename_val = NULL;
	}
	else
	{
		bp_bundle_payload.filename.filename_val = (char*) malloc(bundle_payload.filename.filename_len + 1);
		strncpy(bp_bundle_payload.filename.filename_val, bundle_payload.filename.filename_val, bundle_payload.filename.filename_len + 1);
	}
	bp_bundle_payload.buf.buf_len = bundle_payload.buf.buf_len;
	if (bundle_payload.buf.buf_len == 0)
	{
		bp_bundle_payload.buf.buf_val = NULL;
	}
	else
	{
		bp_bundle_payload.buf.buf_val = (char*) malloc(bundle_payload.buf.buf_len);
		memcpy(bp_bundle_payload.buf.buf_val, bundle_payload.buf.buf_val, bundle_payload.buf.buf_len);
	}if (bundle_payload.status_report == NULL)
	{
		bp_bundle_payload.status_report = NULL;
	}
	else
	{
		bp_bundle_status_report_t bp_bundle_status_report = dtn_bp_bundle_status_report(*(bundle_payload.status_report));
		bp_bundle_payload.status_report = & bp_bundle_status_report;
	}

	return bp_bundle_payload;
}
