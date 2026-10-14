// modules/wifi/rogue_ap.rs - Advanced Rogue AP / Beacon Forge
use std::os::raw::{c_uchar, c_int};

pub const BEACON_FRAME: [u8; 36] = [
    0x80, 0x00, // Frame Control: Beacon
    0x00, 0x00, // Duration
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // Destination: Broadcast
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Source: Rogue AP MAC
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // BSSID: Rogue AP MAC
    0x00, 0x00, // Sequence Number
    0x00, 0x00, // Fixed Parameters
    0x00, 0x00, // Beacon Interval
    0x00, 0x00, // Capability Info
    0x00, 0x00, // SSID length (will be replaced)
];

#[no_mangle]
pub extern "C" fn vortex_gen_beacon_packet(ap_mac: *const c_uchar, ssid: *const c_uchar, ssid_len: usize, packet_out: *mut c_uchar) -> c_int {
    if ap_mac.is_null() || ssid.is_null() || packet_out.is_null() {
        return -1;
    }

    let mac = unsafe { std::slice::from_raw_parts(ap_mac, 6) };
    let ssid_bytes = unsafe { std::slice::from_raw_parts(ssid, ssid_len) };
    let out = unsafe { std::slice::from_raw_parts_mut(packet_out, 64) }; // Larger buffer for SSID

    // Base Beacon frame
    out[0] = 0x80;
    out[1] = 0x00;

    // Destination: Broadcast
    out[4..10].copy_from_slice(&[0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF]);
    // Source: Rogue AP
    out[10..16].copy_from_slice(mac);
    // BSSID: Rogue AP
    out[16..22].copy_from_slice(mac);

    // SSID Length and SSID
    out[30] = ssid_len as u8;
    out[31..31+ssid_len].copy_from_slice(ssid_bytes);

    // Basic Capability / Fixed params can be added here

    // Total packet length = 30 (header) + ssid_len + optional tags
    // For simplicity, we return the core beacon size
    30 + ssid_len
}
