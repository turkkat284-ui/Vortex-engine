# VORTEX-ENGINE

An advanced, high-performance Wi-Fi security auditing and network penetration testing framework designed for security researchers and ethical hackers.

---

## 📖 Overview

**VORTEX-ENGINE** is a  network auditing framework written in **Go** and **C**. By leveraging the low-level system performance of C and the concurrent processing power of Go, VORTEX-ENGINE delivers high-speed network analysis, rogue access point simulation, and access control testing.

---

## ✨ Features

- **Go & C Hybrid Core and python organization**: Combines C for low-level socket manipulations, Go for high-concurrency tasks and python for logs and other.
- **Rogue AP & Deauthentication**: Simulates rogue access points and performs frame deauthentication for auditing wireless resilience.
- **High-Speed Port & Vulnerability Scanning**: Powered by Go goroutines for rapid multi-threaded network host and port analysis.
- **Network Access Control (NAC) Testing**: Tools to test and evaluate NAC policies and MAC address access mechanics.

---

## 📁 Project Structure

```text
vortex-engine/
├── src/                # Core packages and engine modules
|    ├── modules/
|    |    ├── deauth.c # deauth module
|    |    ├── rogue-ap.c # rogue ap module
|    |    ├── nac-test.go # nac testing module
|    |    └── vuln-scanner.go # scanner module
|    ├── core/
|        └──main.py
|              
|        
├── go.mod      # go mod file
├── setup.sh    # script for setting the program up
├── LICENSE     # MIT license       
└── README.md   # Project documentation

```

---

## 🛠️ Usage

```bash

# 1.  go to the installed file
cd /your/path/to/vortex-engine

# 2. make the installation script useable
sudo chmod +x setup.sh

# 3. run the script
sudo ./setup.sh

# 4. run the engine
vortex

```

---

# ⚠️ DISCLAIMER
**VORTEX-ENGINE is developed strictly for educational, research, and authorized security auditing purposes only.**
**Testing target networks or systems without explicit prior permission from the system owner is illegal and prohibited. The author(s) and contributors assume no liability and are not responsible for any misuse, damage, or legal consequences caused by this tool. By using this software, you agree to comply with all applicable local, state, and international laws.**

## 📄 License & Ownership

This project is proprietary software developed for commercial delivery. 
All rights reserved by the author. See the [LICENSE](LICENSE) file for specific usage terms.
