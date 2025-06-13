#include "managers/infrared_common.h"
#include "managers/infrared_timings.h"
#include <string.h>

// NEC
void infrared_encoder_nec_reset(InfraredCommonEncoder* encoder, const InfraredMessage* message) {
    infrared_common_encoder_reset(encoder);
    uint8_t address = message->address & 0xFF;
    uint8_t command = message->command & 0xFF;
    encoder->data[0] = address;
    encoder->data[1] = ~address;
    encoder->data[2] = command;
    encoder->data[3] = ~command;
    encoder->bits_to_encode = encoder->protocol->databit_len[0];
}

InfraredStatus infrared_encoder_nec_encode_repeat(InfraredCommonEncoder* encoder, uint32_t* duration, bool* level) {
    if(encoder->timings_encoded == 0) {
        *duration = INFRARED_NEC_REPEAT_MARK;
        *level = true;
        encoder->timings_encoded = 1;
        return InfraredStatusOk;
    } else if(encoder->timings_encoded == 1) {
        *duration = INFRARED_NEC_REPEAT_SPACE;
        *level = false;
        encoder->timings_encoded = 2;
        return InfraredStatusOk;
    } else {
        *duration = INFRARED_NEC_BIT1_MARK;
        *level = true;
        return InfraredStatusDone;
    }
}

// Kaseikyo
void infrared_encoder_kaseikyo_reset(InfraredCommonEncoder* encoder, const InfraredMessage* message) {
    infrared_common_encoder_reset(encoder);
    uint32_t addr_le = __builtin_bswap32(message->address);
    uint32_t cmd_le = __builtin_bswap32(message->command);
    uint8_t id = (addr_le >> 24) & 0x03;
    uint16_t vendor_id = (addr_le >> 8) & 0xFFFF;
    uint8_t genre1 = (addr_le >> 4) & 0x0F;
    uint8_t genre2 = addr_le & 0x0F;
    uint16_t data = cmd_le & 0x3FF;
    encoder->data[0] = vendor_id & 0xFF;
    encoder->data[1] = vendor_id >> 8;
    uint8_t vp = encoder->data[0] ^ encoder->data[1];
    vp = (vp & 0x0F) ^ (vp >> 4);
    encoder->data[2] = (vp & 0x0F) | (genre1 << 4);
    encoder->data[3] = ((data & 0x0F) << 4) | genre2;
    encoder->data[4] = (id << 6) | ((data >> 4) & 0x3F);
    encoder->data[5] = encoder->data[2] ^ encoder->data[3] ^ encoder->data[4];
    encoder->bits_to_encode = encoder->protocol->databit_len[0];
}

// Pioneer
void infrared_encoder_pioneer_reset(InfraredCommonEncoder* encoder, const InfraredMessage* message) {
    infrared_common_encoder_reset(encoder);
    uint8_t address = message->address & 0xFF;
    uint8_t command = message->command & 0xFF;
    uint32_t data = (address) | ((~address & 0xFF) << 8) | ((command) << 16) | ((~command & 0xFF) << 24);
    memcpy(encoder->data, &data, 4);
    encoder->bits_to_encode = encoder->protocol->databit_len[0];
}

InfraredStatus infrared_encoder_pioneer_encode_repeat(InfraredCommonEncoder* encoder, uint32_t* duration, bool* level) {
    return InfraredStatusDone; // Pioneer sends the whole frame again
}

// RCA
void infrared_encoder_rca_reset(InfraredCommonEncoder* encoder, const InfraredMessage* message) {
    infrared_common_encoder_reset(encoder);
    uint32_t data = (message->address & 0x0F) | ((message->command & 0xFF) << 4) | ((~message->address & 0x0F) << 12) | ((~message->command & 0xFF) << 16);
    memcpy(encoder->data, &data, 4);
    encoder->bits_to_encode = encoder->protocol->databit_len[0];
}

InfraredStatus infrared_encoder_rca_encode_repeat(InfraredCommonEncoder* encoder, uint32_t* duration, bool* level) {
    if(encoder->timings_encoded == 0) {
        *duration = INFRARED_RCA_REPEAT_MARK;
        *level = true;
        encoder->timings_encoded = 1;
        return InfraredStatusOk;
    } else {
        *duration = INFRARED_RCA_REPEAT_SPACE;
        *level = false;
        return InfraredStatusDone;
    }
}

// Samsung
void infrared_encoder_samsung_reset(InfraredCommonEncoder* encoder, const InfraredMessage* message) {
    infrared_common_encoder_reset(encoder);
    uint32_t data = (message->address & 0xFF) | ((message->address & 0xFF) << 8) | ((message->command & 0xFF) << 16) | ((~message->command & 0xFF) << 24);
    memcpy(encoder->data, &data, 4);
    encoder->bits_to_encode = encoder->protocol->databit_len[0];
}

InfraredStatus infrared_encoder_samsung_encode_repeat(InfraredCommonEncoder* encoder, uint32_t* duration, bool* level) {
    if(encoder->timings_encoded == 0) {
        *duration = INFRARED_SAMSUNG_REPEAT_MARK;
        *level = true;
        encoder->timings_encoded = 1;
        return InfraredStatusOk;
    } else {
        *duration = INFRARED_SAMSUNG_REPEAT_SPACE;
        *level = false;
        return InfraredStatusDone;
    }
}

// SIRC
void infrared_encoder_sirc_reset(InfraredCommonEncoder* encoder, const InfraredMessage* message) {
    infrared_common_encoder_reset(encoder);
    uint8_t cmd = message->command & 0x7F;
    uint8_t addr = message->address & 0x1F;
    uint16_t data = cmd | (addr << 7);
    memcpy(encoder->data, &data, 2);
    encoder->bits_to_encode = encoder->protocol->databit_len[0];
}

InfraredStatus infrared_encoder_sirc_encode_repeat(InfraredCommonEncoder* encoder, uint32_t* duration, bool* level) {
    // SIRC repeats by re-sending the whole frame
    return InfraredStatusDone;
} 