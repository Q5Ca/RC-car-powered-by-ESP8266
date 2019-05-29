#ifndef CONFIG_H
#define CONFIG_H

// Set to debug on serial
#define DEBUG 1

// Set to use arduino uno to control
#define dung_arduino 0

// Set to broadcast wifi
#define phat_wifi 1

#if phat_wifi == 0
// Use these 2 config to connect to specific ssid
const char *connect_ssid     = "";
const char *connect_password = "";
#endif

#if phat_wifi == 1
// Or use these to broadcast wifi
const char *ssid     = "";
const char *password = "";
#endif
