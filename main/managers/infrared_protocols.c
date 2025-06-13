#include <stddef.h>
#include "managers/infrared_protocols.h"
#include "managers/infrared_common.h"
#include "managers/infrared_timings.h"

// Forward declare all protocol encoders
void infrared_encoder_nec_reset(InfraredCommonEncoder* encoder, const InfraredMessage* message);
InfraredStatus infrared_encoder_nec_encode_repeat(InfraredCommonEncoder* encoder, uint32_t* duration, bool* level);
void infrared_encoder_kaseikyo_reset(InfraredCommonEncoder* encoder, const InfraredMessage* message);
void infrared_encoder_pioneer_reset(InfraredCommonEncoder* encoder, const InfraredMessage* message);
InfraredStatus infrared_encoder_pioneer_encode_repeat(InfraredCommonEncoder* encoder, uint32_t* duration, bool* level);
void infrared_encoder_rca_reset(InfraredCommonEncoder* encoder, const InfraredMessage* message);
InfraredStatus infrared_encoder_rca_encode_repeat(InfraredCommonEncoder* encoder, uint32_t* duration, bool* level);
void infrared_encoder_samsung_reset(InfraredCommonEncoder* encoder, const InfraredMessage* message);
InfraredStatus infrared_encoder_samsung_encode_repeat(InfraredCommonEncoder* encoder, uint32_t* duration, bool* level);
void infrared_encoder_sirc_reset(InfraredCommonEncoder* encoder, const InfraredMessage* message);
InfraredStatus infrared_encoder_sirc_encode_repeat(InfraredCommonEncoder* encoder, uint32_t* duration, bool* level);


const InfraredCommonProtocolSpec infrared_protocol_nec = {
    .timings = {
        .preamble_mark = INFRARED_NEC_PREAMBLE_MARK,
        .preamble_space = INFRARED_NEC_PREAMBLE_SPACE,
        .bit1_mark = INFRARED_NEC_BIT1_MARK,
        .bit1_space = INFRARED_NEC_BIT1_SPACE,
        .bit0_mark = INFRARED_NEC_BIT0_MARK,
        .bit0_space = INFRARED_NEC_BIT0_SPACE,
        .preamble_tolerance = INFRARED_NEC_PREAMBLE_TOLERANCE,
        .bit_tolerance = INFRARED_NEC_BIT_TOLERANCE,
        .silence_time = INFRARED_NEC_SILENCE,
        .min_split_time = INFRARED_NEC_MIN_SPLIT_TIME,
        .repeat_mark = INFRARED_NEC_REPEAT_MARK,
        .repeat_space = INFRARED_NEC_REPEAT_SPACE,
    },
    .manchester_start_from_space = false,
    .databit_len = {32, 0, 0, 0},
    .reset = infrared_encoder_nec_reset,
    .encode = infrared_common_encode_pdwm,
    .encode_repeat = infrared_encoder_nec_encode_repeat,
    .carrier_frequency = INFRARED_NEC_CARRIER_FREQUENCY,
    .duty_cycle = INFRARED_NEC_DUTY_CYCLE
};

const InfraredCommonProtocolSpec infrared_protocol_kaseikyo = {
    .timings = {
        .preamble_mark = INFRARED_KASEIKYO_PREAMBLE_MARK,
        .preamble_space = INFRARED_KASEIKYO_PREAMBLE_SPACE,
        .bit1_mark = INFRARED_KASEIKYO_BIT1_MARK,
        .bit1_space = INFRARED_KASEIKYO_BIT1_SPACE,
        .bit0_mark = INFRARED_KASEIKYO_BIT0_MARK,
        .bit0_space = INFRARED_KASEIKYO_BIT0_SPACE,
        .preamble_tolerance = INFRARED_KASEIKYO_PREAMBLE_TOLERANCE,
        .bit_tolerance = INFRARED_KASEIKYO_BIT_TOLERANCE,
        .silence_time = INFRARED_KASEIKYO_SILENCE,
        .min_split_time = INFRARED_KASEIKYO_MIN_SPLIT_TIME,
        .repeat_mark = INFRARED_KASEIKYO_REPEAT_MARK,
        .repeat_space = INFRARED_KASEIKYO_REPEAT_SPACE,
    },
    .manchester_start_from_space = false,
    .databit_len = {48, 0, 0, 0},
    .reset = infrared_encoder_kaseikyo_reset,
    .encode = infrared_common_encode_pdwm,
    .encode_repeat = NULL,
    .carrier_frequency = INFRARED_KASEIKYO_CARRIER_FREQUENCY,
    .duty_cycle = INFRARED_KASEIKYO_DUTY_CYCLE
};

const InfraredCommonProtocolSpec infrared_protocol_pioneer = {
    .timings = {
        .preamble_mark = INFRARED_PIONEER_PREAMBLE_MARK,
        .preamble_space = INFRARED_PIONEER_PREAMBLE_SPACE,
        .bit1_mark = INFRARED_PIONEER_BIT1_MARK,
        .bit1_space = INFRARED_PIONEER_BIT1_SPACE,
        .bit0_mark = INFRARED_PIONEER_BIT0_MARK,
        .bit0_space = INFRARED_PIONEER_BIT0_SPACE,
        .preamble_tolerance = INFRARED_PIONEER_PREAMBLE_TOLERANCE,
        .bit_tolerance = INFRARED_PIONEER_BIT_TOLERANCE,
        .silence_time = INFRARED_PIONEER_SILENCE,
        .min_split_time = INFRARED_PIONEER_MIN_SPLIT_TIME,
    },
    .manchester_start_from_space = false,
    .databit_len = {32, 0, 0, 0},
    .reset = infrared_encoder_pioneer_reset,
    .encode = infrared_common_encode_pdwm,
    .encode_repeat = infrared_encoder_pioneer_encode_repeat,
    .carrier_frequency = INFRARED_PIONEER_CARRIER_FREQUENCY,
    .duty_cycle = INFRARED_PIONEER_DUTY_CYCLE
};

const InfraredCommonProtocolSpec infrared_protocol_rca = {
    .timings = {
        .preamble_mark = INFRARED_RCA_PREAMBLE_MARK,
        .preamble_space = INFRARED_RCA_PREAMBLE_SPACE,
        .bit1_mark = INFRARED_RCA_BIT1_MARK,
        .bit1_space = INFRARED_RCA_BIT1_SPACE,
        .bit0_mark = INFRARED_RCA_BIT0_MARK,
        .bit0_space = INFRARED_RCA_BIT0_SPACE,
        .preamble_tolerance = INFRARED_RCA_PREAMBLE_TOLERANCE,
        .bit_tolerance = INFRARED_RCA_BIT_TOLERANCE,
        .silence_time = INFRARED_RCA_SILENCE,
        .min_split_time = INFRARED_RCA_MIN_SPLIT_TIME,
        .repeat_mark = INFRARED_RCA_REPEAT_MARK,
        .repeat_space = INFRARED_RCA_REPEAT_SPACE,
    },
    .manchester_start_from_space = false,
    .databit_len = {24, 0, 0, 0},
    .reset = infrared_encoder_rca_reset,
    .encode = infrared_common_encode_pdwm,
    .encode_repeat = infrared_encoder_rca_encode_repeat,
    .carrier_frequency = INFRARED_COMMON_CARRIER_FREQUENCY,
    .duty_cycle = INFRARED_COMMON_DUTY_CYCLE
};

const InfraredCommonProtocolSpec infrared_protocol_samsung = {
    .timings = {
        .preamble_mark = INFRARED_SAMSUNG_PREAMBLE_MARK,
        .preamble_space = INFRARED_SAMSUNG_PREAMBLE_SPACE,
        .bit1_mark = INFRARED_SAMSUNG_BIT1_MARK,
        .bit1_space = INFRARED_SAMSUNG_BIT1_SPACE,
        .bit0_mark = INFRARED_SAMSUNG_BIT0_MARK,
        .bit0_space = INFRARED_SAMSUNG_BIT0_SPACE,
        .preamble_tolerance = INFRARED_SAMSUNG_PREAMBLE_TOLERANCE,
        .bit_tolerance = INFRARED_SAMSUNG_BIT_TOLERANCE,
        .silence_time = INFRARED_SAMSUNG_SILENCE,
        .min_split_time = INFRARED_SAMSUNG_MIN_SPLIT_TIME,
        .repeat_mark = INFRARED_SAMSUNG_REPEAT_MARK,
        .repeat_space = INFRARED_SAMSUNG_REPEAT_SPACE,
    },
    .manchester_start_from_space = false,
    .databit_len = {32, 0, 0, 0},
    .reset = infrared_encoder_samsung_reset,
    .encode = infrared_common_encode_pdwm,
    .encode_repeat = infrared_encoder_samsung_encode_repeat,
    .carrier_frequency = INFRARED_COMMON_CARRIER_FREQUENCY,
    .duty_cycle = INFRARED_COMMON_DUTY_CYCLE
};

const InfraredCommonProtocolSpec infrared_protocol_sirc = {
    .timings = {
        .preamble_mark = INFRARED_SIRC_PREAMBLE_MARK,
        .preamble_space = INFRARED_SIRC_PREAMBLE_SPACE,
        .bit1_mark = INFRARED_SIRC_BIT1_MARK,
        .bit1_space = INFRARED_SIRC_BIT1_SPACE,
        .bit0_mark = INFRARED_SIRC_BIT0_MARK,
        .bit0_space = INFRARED_SIRC_BIT0_SPACE,
        .preamble_tolerance = INFRARED_SIRC_PREAMBLE_TOLERANCE,
        .bit_tolerance = INFRARED_SIRC_BIT_TOLERANCE,
        .silence_time = INFRARED_SIRC_SILENCE,
        .min_split_time = INFRARED_SIRC_MIN_SPLIT_TIME,
    },
    .manchester_start_from_space = false,
    .databit_len = {12, 0, 0, 0},
    .reset = infrared_encoder_sirc_reset,
    .encode = infrared_common_encode_pdwm,
    .encode_repeat = infrared_encoder_sirc_encode_repeat,
    .carrier_frequency = INFRARED_SIRC_CARRIER_FREQUENCY,
    .duty_cycle = INFRARED_SIRC_DUTY_CYCLE
};

// TODO: definitions for other protocol specs 