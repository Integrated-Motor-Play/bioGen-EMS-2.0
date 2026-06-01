#ifndef BIOGEN_CONFIG_H
#define BIOGEN_CONFIG_H

// Demux select lines (channels 1-4)
#define PIN_SEL_A 1
#define PIN_SEL_B 2
#define PIN_SEL_C 3
#define PIN_SEL_D 4

#define EMG_PIN A0

#define SERIAL_BAUD 115200
#define EMG_SAMPLE_INTERVAL_MS 10

// Set to 1 to print EMG CSV on Serial for bench testing
#define EMG_DEBUG_SERIAL 0

// BLE device name
#define BLE_DEVICE_NAME "BioGen-EMS"

// Auto-Paizo compatible UUIDs
#define BIOGEN_SERVICE_UUID "19B10000-E8F2-537E-4F6C-D104768A1214"
#define BIOGEN_CMD_CHAR_UUID "19B10001-E8F2-537E-4F6C-D104768A1214"
#define BIOGEN_EMG_CHAR_UUID "19B10002-E8F2-537E-4F6C-D104768A1214"

#endif
