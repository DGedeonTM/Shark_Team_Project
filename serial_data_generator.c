#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

int main() {
    int serial_fd;
    struct termios tty;
    
    // Open the serial port (replace "/dev/ttyS0" with your TTY device)
    serial_fd = open("/dev/ttyS0", O_WRONLY | O_NOCTTY | O_SYNC);
    
    if (serial_fd < 0) {
        perror("Error opening serial port");
        return 1;
    }

    // Configure serial port settings
    memset(&tty, 0, sizeof(tty));
    if (tcgetattr(serial_fd, &tty) != 0) {
        perror("Error getting serial port attributes");
        close(serial_fd);
        return 1;
    }

    cfsetospeed(&tty, B9600); // Set your desired baud rate here (e.g., B9600)
    tty.c_cflag |= (CLOCAL | CREAD); // Enable receiver and set local mode
    tty.c_cflag &= ~CSIZE; // Clear data size bits
    tty.c_cflag |= CS8; // 8 data bits
    tty.c_cflag &= ~PARENB; // No parity
    tty.c_cflag &= ~CSTOPB; // 1 stop bit
    //tty.c_cflag &= ~CRTSCTS; // Disable hardware flow control

    // Apply the configuration
    if (tcsetattr(serial_fd, TCSANOW, &tty) != 0) {
        perror("Error setting serial port attributes");
        close(serial_fd);
        return 1;
    }

    // Data to write to the serial port
    char data[] = "Hello, Serial Port!\n";

    // Write data to the serial port
    ssize_t bytes_written = write(serial_fd, data, sizeof(data) - 1);
    
    if (bytes_written < 0) {
        perror("Error writing to serial port");
        close(serial_fd);
        return 1;
    }

    printf("Data written to serial port: %s", data);

    // Close the serial port
    close(serial_fd);

    return 0;
}