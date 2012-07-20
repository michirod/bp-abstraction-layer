/*
 * bp_dtn_conversions.h
 *
 * Conversions from bp abstract types to dtn types and viceversa
 *
 */

#ifndef BP_DTN_CONVERSIONS_H_
#define BP_DTN_CONVERSIONS_H_
#include <dtn_types.h>
#include <dtn_api.h>

#include "../bp_types.h"

/*
 * These functions convert bp abstract types in dtn types and viceversa
 * The prefix bp_dtn means the function takes a bp abstract type in and returns a dtn type
 * so the conversion is bp -> dtn
 * The prefix dtn_bp means the function takes a dtn type in and returns a bp abstract type
 * so the conversion is dtn -> bp
 */

dtn_handle_t bp_dtn_handle(bp_handle_t handle);
bp_handle_t dtn_bp_handle(dtn_handle_t handle);

dtn_endpoint_id_t bp_dtn_endpoint_id(bp_endpoint_id_t endpoint_id);
bp_endpoint_id_t dtn_bp_endpoint_id(dtn_endpoint_id_t endpoint_id);

dtn_timeval_t bp_dtn_timeval(bp_timeval_t timeval);
bp_timeval_t dtn_bp_timeval(dtn_timeval_t);

dtn_timestamp_t bp_dtn_timestamp(bp_timestamp_t timestamp);
bp_timestamp_t dtn_bp_timestamp(dtn_timestamp_t timestamp);

dtn_reg_token_t bp_dtn_reg_token(bp_reg_token_t reg_token);
bp_reg_token_t dtn_bp_reg_token(dtn_reg_token_t reg_token);

dtn_reg_id_t bp_dtn_reg_id(bp_reg_id_t reg_id);
bp_reg_id_t dtn_bp_reg_id(dtn_reg_id_t reg_id);

dtn_reg_info_t bp_dtn_reg_info(bp_reg_info_t reg_info);
bp_reg_info_t dtn_bp_reg_info(dtn_reg_info_t reg_info);

dtn_reg_flags_t bp_dtn_reg_flags(bp_reg_flags_t reg_flags);
bp_reg_flags_t dtn_bp_reg_flags(dtn_reg_flags_t reg_flags);

dtn_bundle_delivery_opts_t bp_dtn_bundle_delivery_opts(bp_bundle_delivery_opts_t bundle_delivery_opts);
bp_bundle_delivery_opts_t dtn_bp_bundle_delivery_opts(dtn_bundle_delivery_opts_t bundle_delivery_opts);

dtn_bundle_priority_t bp_dtn_bundle_priority(bp_bundle_priority_t bundle_priority);
bp_bundle_priority_t dtn_bp_bunlde_priority(dtn_bundle_priority_t bundle_priority);

dtn_bundle_spec_t bp_dtn_bundle_spec(bp_bundle_spec_t bundle_spec);
bp_bundle_spec_t dtn_bp_bundle_spec(dtn_bundle_spec_t bundle_spec);

dtn_bundle_payload_location_t bp_dtn_bundle_payload_location(bp_bundle_payload_location_t bundle_payload_location);
bp_bundle_payload_location_t dtn_bp_bundle_payload_location(dtn_bundle_payload_location_t bundle_payload_location);

dtn_status_report_reason_t bp_dtn_status_report_reason(bp_status_report_reason_t status_report_reason);
bp_status_report_reason_t dtn_bp_status_report_reason(dtn_status_report_reason_t status_report_reason);

dtn_status_report_flags_t bp_dtn_status_report_flags(bp_status_report_flags_t status_repot_flags);
bp_status_report_flags_t dtn_bp_status_report_flags(dtn_status_report_flags_t status_repot_flags);

dtn_bundle_id_t bp_dtn_bundle_id(bp_bundle_id_t bundle_id);
bp_bundle_id_t dtn_bp_bundle_id(dtn_bundle_id_t bundle_id);

dtn_bundle_status_report_t bp_dtn_bundle_status_report(bp_bundle_status_report_t bundle_status_report);
bp_bundle_status_report_t dtn_bp_bundle_status_report(dtn_bundle_status_report_t bundle_status_report);

bp_bundle_payload_t dtn_bp_bundle_payload(dtn_bundle_payload_t bundle_payload);
dtn_bundle_payload_t bp_dtn_bundle_payload(bp_bundle_payload_t bundle_payload);

#endif /* BP_DTN_CONVERSIONS_H_ */
