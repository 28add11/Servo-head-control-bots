#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "hardware/pwm.h"

#define SERVO_COUNT 2

int main()
{
    stdio_init_all();

	gpio_set_function(2, GPIO_FUNC_PWM);
	gpio_set_function(3, GPIO_FUNC_PWM);

	uint servoPins[SERVO_COUNT] = {2, 3}; // Index is what we get from the device, and values are the data
	uint sliceNum[SERVO_COUNT] = {pwm_gpio_to_slice_num(2), pwm_gpio_to_slice_num(3)};
	uint channel[SERVO_COUNT] = {pwm_gpio_to_channel(2), pwm_gpio_to_channel(3)};

	for (size_t i = 0; i <= SERVO_COUNT; i++) {
		pwm_set_clkdiv(sliceNum[i], (float)(clock_get_hz(clk_sys) / (50 * 65535)));
		pwm_set_wrap(sliceNum[i], 65535);
		pwm_set_enabled(sliceNum[i], true);
	}

	int angle;
	int servoIndex;
	uint inputDuty;

    while (true) {
        printf("Enter the servo index: ");
		scanf("%i", &servoIndex);
		printf("\nEnter the angle to test: ");
		scanf("%i", &angle);
		printf("\n");
		angle = angle % 180;
		inputDuty = angle / 180.0 * 8000 + 1000; // Turns angle into a val between 0 and 1, then calculates duty with an ez multiplication
		pwm_set_chan_level(sliceNum[servoIndex], channel[servoIndex], inputDuty);
    }
}
