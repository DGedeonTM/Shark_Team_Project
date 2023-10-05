<?php
$serialPort = '/dev/ttyS0'; // Replace with your serial port device
$baudRate = 9600; // Set your desired baud rate

$serialHandle = fopen($serialPort, 'r');

if (!$serialHandle) {
    die('Failed to open serial port');
}

// Read data from the serial port
$data = fgets($serialHandle);

fclose($serialHandle);

// Return the data as JSON
header('Content-Type: application/json');
echo json_encode(['data' => $data]);
?>