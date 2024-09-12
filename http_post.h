#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/pbuf.h"
#include "lwip/tcp.h"
#include <stdio.h>

// WLAN-Konfiguration
#define WIFI_SSID "MagentaWLAN-7VJV"
#define WIFI_PASSWORD "34076848352324396738"
#define SERVER_IP "192.168.2.172" // IP-Adresse des Apache-Servers
#define SERVER_PORT 80 // Standardport für HTTP

// Struktur zur Speicherung der Temperatur- und Feuchtigkeitsdaten
typedef struct {
    float temperature;
    float humidity;
} temp_humidity_data_t;

// Callback-Funktion zum Empfang der Serverantwort
static err_t on_recv(void *arg, struct tcp_pcb *pcb, struct pbuf *p, err_t err);

// Callback-Funktion, wenn die Verbindung hergestellt wurde
static err_t on_connected(void *arg, struct tcp_pcb *pcb, err_t err);

// Funktion zum Senden der Temperatur- und Luftfeuchtigkeitsdaten an den Server
void send_data_to_server(float temperature, float humidity);

#endif // DATA_STRUCTURES_H
