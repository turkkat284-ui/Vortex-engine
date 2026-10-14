// modules/network/vuln_scanner.go - High Performance Network Auditor
package scanner

import (
	"fmt"
	"net"
	"time"
	"sync"
)

type ScanResult struct {
	Port    int
	State   string
	Service string
}

// ScanTarget performs a high-speed concurrent port scan on a target IP
func ScanTarget(target string, ports []int, timeout time.Duration) []ScanResult {
	var results []ScanResult
	var mu sync.Mutex
	var wg sync.WaitGroup

	// Semaphore to limit concurrency (prevent OS file descriptor exhaustion)
	semaphore := make(chan struct{}, 1000)

	for _, port := range ports {
		wg.Add(1)
		go func(p int) {
			defer wg.Done()
			semaphore <- struct{}{} // Acquire
			defer func() { <-semaphore }() // Release

			address := fmt.Sprintf("%s:%d", target, p)
			conn, err := net.DialTimeout("tcp", address, timeout)

			if err != nil {
				// Port is closed or filtered
				return
			}
			conn.Close()

			mu.Lock()
			results = append(results, ScanResult{
				Port:    p,
				State:   "Open",
				Service: detectService(p),
			})
			mu.Unlock()
		}(port)
	}

	wg.Wait()
	return results
}

func detectService(port int) string {
	services := map[int]string{
		21:   "FTP",
		22:   "SSH",
		23:   "Telnet",
		25:   "SMTP",
		53:   "DNS",
		80:   "HTTP",
		110:  "POP3",
		143:  "IMAP",
		443:  "HTTPS",
		445:  "SMB",
		3306: "MySQL",
		3389: "RDP",
		5432: "PostgreSQL",
		8080: "HTTP-Proxy",
	}

	if service, ok := services[port]; ok {
		return service
	}
	return "Unknown"
}
