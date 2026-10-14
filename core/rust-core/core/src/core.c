#include "vortex_core.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <arpa/inet.h>
#include <unistd.h>

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

    if (sendto(sock, packet, length, 0, (struct sockaddr*)&socket_address, sizeof(socket_address)) < 0) {
        perror("Sendto error");
        close(sock);
        return -1;
    }

    close(sock);
    return 0;
}

bool vortex_set_monitor_mode(const char* interface, bool enable) {
    printf("[Core] Setting %s to monitor mode: %s\n", interface, enable ? "ON" : "OFF");
    // Gerçek implementasyonda ioctl() çağrıları ile ifconfig/iwconfig benzeri işlem yapılır
    return true;
}
