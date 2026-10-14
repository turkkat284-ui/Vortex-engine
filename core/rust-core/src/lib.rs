use rand::Rng;
use std::os::raw::{c_int, c_uchar};

#[no_mangle]
pub extern "C" fn vortex_apply_evasion(packet: *mut c_uchar, length: usize) -> c_int {
    if packet.is_null() {
        return -1;
    }

    let slice = unsafe { std::slice::from_raw_parts_mut(packet, length) };
    let mut rng = rand::thread_rng();

    // 1. Polymorphic Header Manipulation (Simple Example: Randomizing Padding/Reserved bits)
    // In a real scenario, we would target specific protocol fields that don't affect delivery
    if length > 14 {
        // Randomize a non-critical byte in the header to change the packet signature
        let idx = rng.gen_range(0..14);
        slice[idx] ^= 0xAA;
    }

    // 2. Payload Noise (Adding random bytes to avoid signature detection)
    if length > 60 {
        let noise_pos = rng.gen_range(60..length);
        slice[noise_pos] = rng.gen();
    }

    0 // Success
}

#[no_mangle]
pub extern "C" fn vortex_get_jitter_delay() -> u64 {
    let mut rng = rand::thread_rng();
    // Returns a random delay in microseconds (10us to 500us)
    rng.gen_range(10..500)
}
