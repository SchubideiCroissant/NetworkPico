#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/pbuf.h"
#include "lwip/tcp.h"
#include <stdio.h>
#include "http_post.h"

#define WIFI_SSID "MagentaWLAN-7VJV"
#define WIFI_PASSWORD "34076848352324396738"
#define SERVER_IP "192.168.2.172" // IP-Adresse des Apache-Servers
#define SERVER_PORT 80 // Standardport für HTTP
#ifndef DATA_STRUCTURES_H  // Prüft, ob DATA_STRUCTURES_H noch nicht definiert ist
#define DATA_STRUCTURES_H  // Definiert DATA_STRUCTURES_H, um Mehrfachinklusion zu verhindern

typedef struct {
    float temperature;
    float humidity;
} temp_humidity_data_t;

#endif // DATA_STRUCTURES_H

// Callback-Funktion zum Empfang der Serverantwort
static err_t on_recv(void *arg, struct tcp_pcb *pcb, struct pbuf *p, err_t err) {
    if (err == ERR_OK && p != NULL) {
        // Antwortdaten empfangen
        printf("Received response from server:\n%s\n", (char*)p->payload);

        // Puffer freigeben, aber Verbindung nicht schließen
        pbuf_free(p);
    } else if (p == NULL) {
        // Server hat die Verbindung geschlossen
        printf("Server closed connection\n");
        tcp_close(pcb);
    }
    return ERR_OK;
}

// Callback-Funktion, wenn die Verbindung hergestellt wurde
static err_t on_connected(void *arg, struct tcp_pcb *pcb, err_t err) {
    if (err != ERR_OK) {
        printf("Connection failed: %d\n", err);
        tcp_close(pcb);
        return err;
    }

    printf("Successfully connected to server.\n");

    // Zugriff auf Temperatur- und Feuchtigkeitswerte
    temp_humidity_data_t *data = (temp_humidity_data_t*)arg;

    // HTTP POST-Daten vorbereiten
    char body[200];
    //printf("Body content: %s\n", body);  // Debug-Ausgabe
    snprintf(body, sizeof(body), "temperature=%.2f&humidity=%.2f", data->temperature, data->humidity);

    char post_data[256];
    int content_length = strlen(body);
    snprintf(post_data, sizeof(post_data),
             "POST /server.php HTTP/1.1\r\n"
             "Host: %s\r\n"
             "Content-Type: application/x-www-form-urlencoded\r\n"
             "Content-Length: %d\r\n"
             "\r\n"
             "%s",
             SERVER_IP, // Hostname oder IP-Adresse
             content_length,
             body);

    // Daten senden
    err_t res = tcp_write(pcb, post_data, strlen(post_data), TCP_WRITE_FLAG_COPY);
    if (res != ERR_OK) {
        printf("Failed to send data: %d\n", res);
        tcp_close(pcb);
        return res;
    }

    // Sicherstellen, dass die Daten gesendet werden
    tcp_output(pcb);

    // Setze den Callback für den Empfang von Daten
    tcp_recv(pcb, on_recv);

    return ERR_OK;
}

// Funktion zum Senden der Temperatur- und Luftfeuchtigkeitsdaten an den Server
void send_data_to_server(float temperature, float humidity) {
    struct tcp_pcb *pcb = tcp_new();
    if (pcb == NULL) {
        printf("Failed to create PCB\n");
        return;
    }
 
    ip_addr_t server_addr;
    ipaddr_aton(SERVER_IP, &server_addr);

    // Erstelle eine Struktur für Temperatur und Luftfeuchtigkeit
    temp_humidity_data_t *data = (temp_humidity_data_t*)malloc(sizeof(temp_humidity_data_t));
    if (data == NULL) {
        printf("Failed to allocate memory for data\n");
        tcp_close(pcb);
        return;
    }
    data->temperature = temperature;
    data->humidity = humidity;

    // Verbindung herstellen und Daten an on_connected übergeben
    err_t err = tcp_connect(pcb, &server_addr, SERVER_PORT, on_connected);
    if (err != ERR_OK) {
        printf("Failed to connect: %d\n", err);
        tcp_close(pcb);
        return;
    }

    // Übergabe der Daten (temperature & humidity) als Argument an die Callback-Funktion
    tcp_arg(pcb, data);
    printf("Attempting to connect to PORT %d\n", SERVER_PORT);
}

int main() {
    stdio_init_all();

    if (cyw43_arch_init()) {
        printf("failed to initialise\n");
        return 1;
    }

    cyw43_arch_enable_sta_mode();

    printf("Connecting to Wi-Fi...\n");
    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30000)) {
        printf("failed to connect.\n");
        return 1;
    } else {
        printf("Connected.\n");
    }

    // Beispielwerte
    float temperature = 22.5;
    float humidity = 55.0;

    while (1) {
        printf("Sending data...\n");
        send_data_to_server(temperature, humidity);
        sleep_ms(10000); // 10 Sekunden warten
    }

    cyw43_arch_deinit();
    return 0;
}
