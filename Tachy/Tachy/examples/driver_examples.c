/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"

static struct timer_task Timer_task1, Timer_task2;
/**
 * Example of using Timer.
 */
static void Timer_task1_cb(const struct timer_task *const timer_task)
{
}

static void Timer_task2_cb(const struct timer_task *const timer_task)
{
}

void Timer_example(void)
{
	Timer_task1.interval = 100;
	Timer_task1.cb       = Timer_task1_cb;
	Timer_task1.mode     = TIMER_TASK_REPEAT;
	Timer_task2.interval = 200;
	Timer_task2.cb       = Timer_task2_cb;
	Timer_task2.mode     = TIMER_TASK_REPEAT;

	timer_add_task(&Timer, &Timer_task1);
	timer_add_task(&Timer, &Timer_task2);
	timer_start(&Timer);
}

/**
 * Example of using EDBG_0 to write "Hello World" using the IO abstraction.
 */
void EDBG_0_example(void)
{
	struct io_descriptor *io;
	usart_sync_get_io_descriptor(&EDBG_0, &io);
	usart_sync_enable(&EDBG_0);

	io_write(io, (uint8_t *)"Hello World!", 12);
}

void ADXL345_0_example(void)
{
	struct io_descriptor *ADXL345_0_io;

	i2c_m_sync_get_io_descriptor(&ADXL345_0, &ADXL345_0_io);
	i2c_m_sync_enable(&ADXL345_0);
	i2c_m_sync_set_slaveaddr(&ADXL345_0, 0x12, I2C_M_SEVEN);
	io_write(ADXL345_0_io, (uint8_t *)"Hello World!", 12);
}

#define SLCD_EXAMPLE_SEGID SLCD_SEGID(1, 0)
/**
 * Example of using SEGMENT_LCD_0
 */
void SEGMENT_LCD_0_example(void)
{
	slcd_sync_enable(&SEGMENT_LCD_0);
	slcd_sync_seg_on(&SEGMENT_LCD_0, SLCD_EXAMPLE_SEGID);
}
