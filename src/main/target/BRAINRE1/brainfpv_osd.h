
#ifndef BRAINFPV_OSD_H
#define BRAINFPV_OSD_H

#include <stdint.h>


typedef struct {
    uint8_t sync_threshold;
    uint8_t white_level;
    uint8_t black_level;
    int8_t x_offset;
    uint8_t x_scale;
    uint8_t sbs_3d_enabled;
    uint8_t sbs_3d_right_eye_offset;
    uint8_t ir_system;
    uint16_t ir_trackmate_id;
    uint32_t ir_ilap_id;
} bfOsdConfig_t;


void brainFpvOsdInit(void);
void osdMain(void);
void resetBfOsdConfig(bfOsdConfig_t *bfOsdConfig);

#endif /* BRAINFPV_OSD */
