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

// Evasion Bridge (linked from Rust)
int vortex_apply_evasion(uint8_t* packet, size_t length);
uint64_t vortex_get_jitter_delay();

// Modul Bridge: Deauth
int vortex_gen_deauth_packet(const uint8_t* target_mac, const uint8_t* ap_mac, uint8_t* packet_out);

// Modul Bridge: Rogue AP
int vortex_gen_beacon_packet(const uint8_t* ap_mac, const uint8_t* ssid, size_t ssid_len, uint8_t* packet_out);

#endif
