# BME280 Test Firmare

test firmware for bme280 bug investigation

## Requirements

- Zephyr v4.1.0
- Zephyr SDK 0.17.0
- nRF52840DK with BME280 pimoroni module


## Build and flash

```sh
west build -b nrf52840dk/nrf52840 && west flash
```
