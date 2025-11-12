#include <pcap.h>
#include <iostream>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <map>
#include <cstring>

using namespace std;

int total_packets = 0;
int tcp_count = 0;
int udp_count = 0;
int icmp_count = 0;
int other_count = 0;

map<string, int> src_ips;

void packet_handler(u_char *userData, const struct pcap_pkthdr *header, const u_char *packet) {
    total_packets++;

    const struct ip ip_header = (struct ip)(packet + 14);
    int ip_header_len = ip_header->ip_hl * 4;
    string src_ip = inet_ntoa(ip_header->ip_src);
    string dst_ip = inet_ntoa(ip_header->ip_dst);

    src_ips[src_ip]++;

    switch (ip_header->ip_p) {
        case IPPROTO_TCP:
            tcp_count++;
            break;
        case IPPROTO_UDP:
            udp_count++;
            break;
        case IPPROTO_ICMP:
            icmp_count++;
            break;
        default:
            other_count++;
            break;
    }

    cout << "Packet #" << total_packets
         << " | Src: " << src_ip
         << " -> Dst: " << dst_ip
         << " | Proto: " << (int)ip_header->ip_p
         << endl;
}

int main() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_if_t *alldevs, *device;

    if (pcap_findalldevs(&alldevs, errbuf) == -1) {
        cerr << "Error finding devices: " << errbuf << endl;
        return 1;
    }

    cout << "Available Network Interfaces:\n";
    int i = 0;
    for (device = alldevs; device; device = device->next) {
        cout << ++i << ". " << device->name;
        if (device->description)
            cout << " (" << device->description << ")";
        cout << endl;
    }

    if (i == 0) {
        cerr << "No interfaces found! Exiting.\n";
        return 1;
    }

    int choice;
    cout << "\nSelect interface number to capture from: ";
    cin >> choice;

    device = alldevs;
    for (int j = 1; j < choice && device; j++) device = device->next;

    if (!device) {
        cerr << "Invalid selection.\n";
        return 1;
    }

    cout << "Starting capture on " << device->name << "...\n";

    pcap_t *handle = pcap_open_live(device->name, BUFSIZ, 1, 1000, errbuf);
    if (!handle) {
        cerr << "Could not open device " << device->name << ": " << errbuf << endl;
        return 1;
    }

    cout << "Capturing packets... (Press Ctrl+C to stop)\n\n";


    pcap_loop(handle, 0, packet_handler, NULL);

    pcap_close(handle);

    cout << "\n==== Capture Summary ====\n";
    cout << "Total Packets: " << total_packets << endl;
    cout << "TCP: " << tcp_count << endl;
    cout << "UDP: " << udp_count << endl;
    cout << "ICMP: " << icmp_count << endl;
    cout << "Others: " << other_count << endl;

    cout << "\nTop Talkers (Source IPs):\n";
    for (auto &pair : src_ips)
        cout << pair.first << " : " << pair.second << " packets\n";

    pcap_freealldevs(alldevs);
    return 0;

}
