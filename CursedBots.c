#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "hardware/pwm.h"

int main()
{
    stdio_init_all();

	gpio_set_function(2, GPIO_FUNC_PWM);

	uint slice_num = pwm_gpio_to_slice_num(2);
	uint channel = pwm_gpio_to_channel(2);

	pwm_set_clkdiv(slice_num, (float)(clock_get_hz(clk_sys) / (50 * 65535)));
	pwm_set_wrap(slice_num, 65535);
	pwm_set_enabled(slice_num, true);

	uint8_t angle;
	uint inputDuty;

    while (true) {
        printf("Enter the angle to test: ");
		fgets(&angle, 1, stdin);
		printf("\n");
		angle = angle % 180;
		inputDuty = angle / 180.0 * 8000 + 1000; // Turns angle into a val between 0 and 1, then calculates duty with an ez multiplication
		pwm_set_chan_level(slice_num, channel, inputDuty);
    }
}
