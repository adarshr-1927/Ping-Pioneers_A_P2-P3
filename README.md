Abstract:
Monitoring and analysis are key parts of ensuring performance, security, and reliability in modern computer networks. A network traffic analyzer is implemented here using the C++ programming language and based on the libpcap library. The proposed system captures live packets from a selected network interface, classifies them according to protocol types (TCP, UDP, ICMP, etc.), and detects top talkers-in other words, frequently communicating IP addresses. The analyzer provides real-time insight into network activity; such insight is useful for a network administrator, researcher, or security professional.

1. Introduction:
Whereas the exponential growth of the internet has ensured that network traffic monitoring becomes pivotal for anomaly detection, performance optimization, and cybersecurity maintenance, various tools like Wireshark and tcpdump are widely in use; nonetheless, some lightweight and customizable analyzers can offer focused functionality.
The project's work is to create a customized network traffic analyzer in C++ using libpcap to capture, filter, and summarize network packets. This will help to perceive the basic
handling of packets, identify protocols, and perform source-destination communication analysis.

2. Objectives:
The main objectives of the project are:
•	To capture live network traffic using libpcap.
•	To identify and classify packets based on transport layer protocols such as TCP, UDP, ICMP, etc.
•	To keep track of statistics, including total packets and per-protocol counts.
•	To identify top talkers (most active source IP addresses).
•	To display a summary of network activity after the capture session.

3. Literature Review
The currently available tools, such as Wireshark, NetFlow, and tcpdump, are quite powerful packet analyzers. However, they are resource-intensive and generally not suited to embedded or educational environments.
Research in lightweight traffic analyzers shows that minimalist tools can serve target use cases, especially in learning, local monitoring, and IoT networks. libpcap, a packet capture library, offers a portable and efficient interface for developing such applications at the user level.

4. Methodology:

4.1 Tools and Libraries
Language: C++
Library: libpcap (packet capture API)
Headers Used: pcap.h, netinet/ip.h, netinet/tcp.h, netinet/udp.h, arpa/inet.h

4.2 Working Principle
Device Selection:

Program lists available network interfaces and lets the user choose one for monitoring.
Packet Capture:
Packets are captured in real-time using pcap_open_live().
Packet Decoding:
The Ethernet header is skipped, and the IP header is extracted to retrieve source and destination addresses.
Protocol Identification:
Each packet is classified according to the protocol type: TCP, UDP, ICMP, and others.
Statistics Maintenance:
The total and per-protocol packet counts are updated, and a map is maintained of the number of packets per source IP address.
Result Display:
After the capture finishes, summary statistics and the top talkers are printed.
5. Implementation
Code Overview
The program uses a callback function packet_handler(), which is executed for every captured packet. Inside this function:
IP headers are parsed.
The source and destination IPs are extracted.
Protocol types are counted.
A map stores packet counts for each source IP.
The main() function handles device listing, user input, and the start of the capture loop via pcap_loop().
Pseudo-Flow
Start
│

├── List available network interfaces

├── Select an interface to capture

Open the device using pcap_open_live()

├── Capture packets in a loop
│     ├── Parse IP header


│     ├── Identify protocol (TCP/UDP/ICMP)

│     ├── Increment counters
│     └── Store source IP count
├── Display summary and top talkers
└── End

6. Results and Discussion
During execution, the analyzer displays each captured packet in real time, showing its source, destination, and protocol number.
Example Output:
Packet #1 | Src: 192.168.1.10 -> Dst: 8.8.8.8 | Proto: 17
Packet #2 | Src: 192.168.1.5  -> Dst: 192.168.1.1 | Proto: 6
It differs from other children's homes in that it is not an orphanage in the strict sense of the word.

Summary:

==== Capture Summary ====

Total Packets: 250
TCP: 120
UDP: 100
ICMP: 10
Others: 20

Top Talkers:
192.168.1.10 : 75 packets
192.168.1.5  : 60 packets

The analyzer effectively tracks the volume and nature of the traffic across the network. It can be extended with graphical visualization or packet filtering features for deeper analysis.


7. Applications
•	time network monitoring.
•	Intrusion detection assistance.
•	Educational and research tool for network students. Real
•	A light-weight diagnostic tool for LAN administrators.

8. Benefits

Low resource usage:
Real-time traffic insight. Customizable to meet specific needs. Easy to extend for protocol filtering or logging. 9. Limitations Requires administrative privileges for live capture. Limited protocol decoding: basic IP, TCP, UDP, ICMP only. No GUI for visualization. 10. Future Enhancements Addition of a graphical user interface. Support for more protocol layers: HTTP, ARP, DNS among others. Integration with databases for long-term storage. Alert systems for abnormal traffic flow. 11. Conclusion The network traffic analyzer will, in this way, furnish a real-time packet capturing and analysis using C++ with the help of the libpcap library. It gives an overview of network traffic behavior and packet structure. Further advanced network monitoring, intrusion detection, and data analytics systems can thus take this tool as a base.


