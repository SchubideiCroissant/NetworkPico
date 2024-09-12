# Projekt README

Dieses Projekt umfasst eine einfache Webanwendung, die verwendet wird, um Sensordaten von einem Hauptprogramm zu empfangen und anzuzeigen. Die Webanwendung besteht aus drei Hauptkomponenten:

1. **index.html**: Die Haupt-HTML-Seite, die das Formular zur Eingabe von Temperatur- und Luftfeuchtigkeitswerten bereitstellt. Die eingegebenen Daten werden an den Server gesendet und angezeigt.

2. **server.php**: Das PHP-Skript, das die POST-Daten vom Formular verarbeitet. Es speichert die empfangenen Daten in einer Datei und gibt eine Bestätigung auf der Webseite aus. Die Daten werden zusammen mit einem Zeitstempel gespeichert, um eine chronologische Aufzeichnung der Sensormessungen zu ermöglichen.

3. **script.js**: Das JavaScript-Skript, das für die Interaktivität der Webseite verantwortlich ist. Es sendet die Formulardaten an das PHP-Skript und lädt die gespeicherten Daten regelmäßig neu, um sie auf der Webseite anzuzeigen.

## Zweck der Webseite

Die Webseite dient dazu, Sensordaten vom Hauptprogramm zu verarbeiten und anzuzeigen. Die Daten werden in Echtzeit erfasst und auf der Seite angezeigt, um eine einfache Überwachung und Analyse der Sensorwerte zu ermöglichen.

## Verwendung/Anforderungen
- Ein Webserver mit PHP-Unterstützung (z.B. XAMPP, Apache).
- Die Dateien müssen im Webverzeichnis des Servers platziert werden.
- Der Webserver muss Zugriff auf das Dateisystem haben, um `data_log.txt` zu erstellen und zu beschreiben.

## Installation

1. Kopieren Sie die Dateien `index.html`, `server.php` und `script.js` in das Verzeichnis Ihres Webservers.
2. Stellen Sie sicher, dass der Webserver ordnungsgemäß konfiguriert ist und PHP-Dateien verarbeiten kann.
3. Öffnen Sie die `index.html`-Datei in einem Webbrowser, um die Anwendung zu verwenden.

## Hinweis

Stellen Sie sicher, dass die PHP-Datei und die Logdatei die richtigen Berechtigungen haben, um auf dem Server geschrieben zu werden. Andernfalls kann es zu Problemen beim Speichern der Daten kommen.

---

