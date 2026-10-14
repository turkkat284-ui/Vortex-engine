#ifndef VORTEX_CORE_H
#define VORTEX_CORE_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    char* interface;
    bool monitor_mode;
    uint32_t tx_rate;
} vortex_config_t;

// Low-level packet injection
int vortex_inject_packet(const uint8_t* packet, size_t length);
bool vortex_set_monitor_mode(const char* interface, bool enable);

#endif
