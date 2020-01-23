/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_init.h"
#include <peripheral_clk_config.h>
#include <utils.h>
#include <hal_init.h>

#include <hpl_rtc_base.h>

struct timer_descriptor     Timer;
struct slcd_sync_descriptor SEGMENT_LCD_0;

struct usart_sync_descriptor EDBG_0;

struct i2c_m_sync_desc ADXL345_0;

/**
 * \brief Timer initialization function
 *
 * Enables Timer peripheral, clocks and initializes Timer driver
 */
static void Timer_init(void)
{
	hri_mclk_set_APBAMASK_RTC_bit(MCLK);
	timer_init(&Timer, RTC, _rtc_get_timer());
}

void EDBG_0_PORT_init(void)
{

	gpio_set_pin_function(PC24, PINMUX_PC24C_SERCOM0_PAD2);

	gpio_set_pin_function(PC25, PINMUX_PC25C_SERCOM0_PAD3);
}

void EDBG_0_CLOCK_init(void)
{
	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM0_GCLK_ID_CORE, CONF_GCLK_SERCOM0_CORE_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM0_GCLK_ID_SLOW, CONF_GCLK_SERCOM0_SLOW_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
	hri_mclk_set_APBCMASK_SERCOM0_bit(MCLK);
}

void EDBG_0_init(void)
{
	EDBG_0_CLOCK_init();
	usart_sync_init(&EDBG_0, SERCOM0, (void *)NULL);
	EDBG_0_PORT_init();
}

void ADXL345_0_PORT_init(void)
{

	gpio_set_pin_pull_mode(PB30,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_UP);

	gpio_set_pin_function(PB30, PINMUX_PB30C_SERCOM1_PAD0);

	gpio_set_pin_pull_mode(PB31,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_UP);

	gpio_set_pin_function(PB31, PINMUX_PB31C_SERCOM1_PAD1);
}

void ADXL345_0_CLOCK_init(void)
{
	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM1_GCLK_ID_CORE, CONF_GCLK_SERCOM1_CORE_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM1_GCLK_ID_SLOW, CONF_GCLK_SERCOM1_SLOW_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
	hri_mclk_set_APBCMASK_SERCOM1_bit(MCLK);
}

void ADXL345_0_init(void)
{
	ADXL345_0_CLOCK_init();
	i2c_m_sync_init(&ADXL345_0, SERCOM1);
	ADXL345_0_PORT_init();
}

void SEGMENT_LCD_0_PORT_init(void)
{

	gpio_set_pin_function(PA06, PINMUX_PA06B_SLCD_LP6);

	gpio_set_pin_function(PA07, PINMUX_PA07B_SLCD_LP7);

	gpio_set_pin_function(PC05, PINMUX_PC05B_SLCD_LP8);

	gpio_set_pin_function(PC06, PINMUX_PC06B_SLCD_LP9);

	gpio_set_pin_function(PC07, PINMUX_PC07B_SLCD_LP10);

	gpio_set_pin_function(PA08, PINMUX_PA08B_SLCD_LP11);

	gpio_set_pin_function(PA09, PINMUX_PA09B_SLCD_LP12);

	gpio_set_pin_function(PA10, PINMUX_PA10B_SLCD_LP13);

	gpio_set_pin_function(PA11, PINMUX_PA11B_SLCD_LP14);

	gpio_set_pin_function(PC08, PINMUX_PC08B_SLCD_LP15);

	gpio_set_pin_function(PC09, PINMUX_PC09B_SLCD_LP16);

	gpio_set_pin_function(PC10, PINMUX_PC10B_SLCD_LP17);

	gpio_set_pin_function(PC11, PINMUX_PC11B_SLCD_LP18);

	gpio_set_pin_function(PC12, PINMUX_PC12B_SLCD_LP19);

	gpio_set_pin_function(PC13, PINMUX_PC13B_SLCD_LP20);

	gpio_set_pin_function(PB11, PINMUX_PB11B_SLCD_LP21);

	gpio_set_pin_function(PB12, PINMUX_PB12B_SLCD_LP22);

	gpio_set_pin_function(PB13, PINMUX_PB13B_SLCD_LP23);

	gpio_set_pin_function(PB14, PINMUX_PB14B_SLCD_LP24);

	gpio_set_pin_function(PB15, PINMUX_PB15B_SLCD_LP25);

	gpio_set_pin_function(PC14, PINMUX_PC14B_SLCD_LP26);

	gpio_set_pin_function(PC15, PINMUX_PC15B_SLCD_LP27);

	gpio_set_pin_function(PA14, PINMUX_PA14B_SLCD_LP30);

	gpio_set_pin_function(PA15, PINMUX_PA15B_SLCD_LP31);

	gpio_set_pin_function(PC16, PINMUX_PC16B_SLCD_LP36);

	gpio_set_pin_function(PC17, PINMUX_PC17B_SLCD_LP37);

	gpio_set_pin_function(PC18, PINMUX_PC18B_SLCD_LP38);

	gpio_set_pin_function(PC19, PINMUX_PC19B_SLCD_LP39);

	gpio_set_pin_function(PC20, PINMUX_PC20B_SLCD_LP40);

	gpio_set_pin_function(PC21, PINMUX_PC21B_SLCD_LP41);

	gpio_set_pin_function(PB16, PINMUX_PB16B_SLCD_LP42);

	gpio_set_pin_function(PB17, PINMUX_PB17B_SLCD_LP43);
}
/**
 * \brief SLCD initialization function
 *
 * Enables SLCD peripheral, clocks and initializes SLCD driver
 */
void SEGMENT_LCD_0_init(void)
{
	hri_mclk_set_APBCMASK_SLCD_bit(SLCD);
	slcd_sync_init(&SEGMENT_LCD_0, SLCD);
	SEGMENT_LCD_0_PORT_init();
}

/**
 * \brief PTC initialization function
 *
 * Enables PTC peripheral, clocks and initializes PTC driver
 */
static void PTC_clock_init(void)
{
	hri_gclk_write_PCHCTRL_reg(GCLK, PTC_GCLK_ID, CONF_GCLK_PTC_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
	hri_mclk_set_APBCMASK_PTC_bit(MCLK);
}

void system_init(void)
{
	init_mcu();

	Timer_init();

	EDBG_0_init();

	ADXL345_0_init();
	SEGMENT_LCD_0_init();

	PTC_clock_init();
}
