#include "host_driver.h"
#include "host.h"
#include "usb_device_state.h"
#include "usb_main.h"

uint8_t keyboard_leds(void);

void send_keyboard(report_keyboard_t *report)
{
    hid_keyboard_send_report(KBD_IN_EP, report->raw, KBD_IN_EP_SIZE);
}

void send_mouse(report_mouse_t *report);

void send_consumer(uint16_t data)
{
    hid_custom_send_report(HIDRAW_IN_EP, &data, HIDRAW_IN_SIZE);
}

void send_system(uint16_t data)
{
    send_consumer(data);
}

void send_programmable_button(uint32_t data);
void send_digitizer(report_digitizer_t *report);

host_driver_t ch582_driver = { keyboard_leds, send_keyboard, send_mouse, send_system, send_consumer, send_programmable_button };

void protocol_setup()
{
    usb_device_state_init();
}

void protocol_pre_init()
{
    // TODO: finish this
    // usb_event_queue_init();
    extern void init_usb_driver();
    init_usb_driver();
}

void protocol_post_init()
{
    host_set_driver(&ch582_driver);
}