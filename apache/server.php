<?php
// PHP-Code zur Verarbeitung der POST-Daten
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $temperature = $_POST['temperature'] ?? 'N/A';
    $humidity = $_POST['humidity'] ?? 'N/A';
    $timestamp = date('Y-m-d H:i:s'); // Zeitstempel im Format "Jahr-Monat-Tag Stunde:Minute:Sekunde"
    
    echo "<p>Temperature: $temperature&#8451; </p>";
    echo "<p>Humidity: $humidity%</p>";
    
    // Speichern der Daten
    $file = 'data_log.txt';
    $data = "$timestamp - Temperature: $temperature&#8451, Humidity: $humidity%\n";
    file_put_contents($file, $data, FILE_APPEND);
    
    echo "<p>Daten erfolgreich gespeichert.</p>";
} else {
    echo "<p>Invalid request method!</p>";
}
?>
