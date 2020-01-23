/**
 * \file
 *
 * \brief Application implement
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip
 * Support</a>
 */

#include "adxl345.h"
#include "adxl345_dev.h"
#include "adxl345_err.h"
#include "atmel_start.h"
#include "atmel_start_pins.h"

// =============================================================================
// definitions and typedefs

/* Logo */
#define TSLCD_SEG_B0 SLCD_SEGID(1, 0)
#define TSLCD_SEG_B1 SLCD_SEGID(2, 0)
#define TSLCD_SEG_B2 SLCD_SEGID(0, 0)

/* Narrow */
#define TSLCD_SEG_N0 SLCD_SEGID(3, 0)
#define TSLCD_SEG_N1 SLCD_SEGID(4, 0)
#define TSLCD_SEG_N2 SLCD_SEGID(5, 0)
#define TSLCD_SEG_N3 SLCD_SEGID(6, 0)
#define TSLCD_SEG_N4 SLCD_SEGID(7, 0)

/* symbal */
#define TSLCD_SEG_S0 SLCD_SEGID(0, 21)
#define TSLCD_SEG_S1 SLCD_SEGID(0, 20)
#define TSLCD_SEG_S2 SLCD_SEGID(0, 19)
#define TSLCD_SEG_S3 SLCD_SEGID(0, 22)
#define TSLCD_SEG_S4 SLCD_SEGID(0, 14)
#define TSLCD_SEG_S5 SLCD_SEGID(0, 13)
#define TSLCD_SEG_S6 SLCD_SEGID(0, 15)
#define TSLCD_SEG_S7 SLCD_SEGID(0, 23)

/* Digital */
#define TSLCD_SEG_D01 SLCD_SEGID(0, 16)
#define TSLCD_SEG_D02 SLCD_SEGID(0, 17)
#define TSLCD_SEG_D03 SLCD_SEGID(0, 18)

/* Wifi */
#define TSLCD_SEG_W0 SLCD_SEGID(0, 2)
#define TSLCD_SEG_W1 SLCD_SEGID(0, 3)
#define TSLCD_SEG_W2 SLCD_SEGID(1, 2)
#define TSLCD_SEG_W3 SLCD_SEGID(1, 3)

/* Battery */
#define TSLCD_SEG_BT0 SLCD_SEGID(4, 2)
#define TSLCD_SEG_BT1 SLCD_SEGID(4, 3)
#define TSLCD_SEG_BT2 SLCD_SEGID(5, 2)
#define TSLCD_SEG_BT3 SLCD_SEGID(5, 3)

#define WINDOW_SIZE 256

// =============================================================================
// local declarations

static void turn_on_segments(void);
static void blink_segments(void);
static void animation_segments(void);
static void display_characters(void);

static void process_samples(adxl345_t *adxl345);
static void process_sample(adxl345_t *adxl345);

static int32_t dummy_autoc();
static void set_test_pin(bool val);

// =============================================================================
// local storage

static uint8_t s_high_water;
static uint32_t s_samples_read;
static float s_total_x;
static int32_t s_autoc_buf[WINDOW_SIZE * 2];

// =============================================================================
// main code

int main(void) {
  atmel_start_init();
  adxl345_err_t err;
  adxl345_t adxl345;
  adxl345_dev_t adxl345_dev;

  /* Replace with your application code */
  slcd_sync_enable(&SEGMENT_LCD_0);
  turn_on_segments();
  blink_segments();
  animation_segments();
  display_characters();

  // for (int i=0; i<100; i++) {
  //   dummy_autoc();
  //   delay_ms(10);
  // }
  //
  err = adxl345_dev_init(&adxl345_dev, &ADXL345_0, ADXL345_I2C_PRIMARY_ADDRESS,
                         I2C_M_SEVEN);
  printf("adxl345_dev_init() => %d\n", err);
  err = adxl345_init(&adxl345, &adxl345_dev);
  printf("adxl345_init() => %d\n", err);
  err = adxl345_stop(&adxl345);
  printf("adxl345_stop() => %d\n", err);


  // Configure ADXL345: 100 Hz, FIFO enabled, water mark = 1 sample
  err = adxl345_set_bw_rate_reg(&adxl345, ADXL345_RATE_200);
  printf("adxl345_set_bw_rate_reg() => %d\n", err);
  err = adxl345_set_fifo_ctl_reg(&adxl345, ADXL345_FIFO_MODE_ENABLE | 1);
  printf("adxl345_set_fifo_ctl_reg() => %d\n", err);

  err = adxl345_start(&adxl345);
  printf("adxl345_start() => %d\n", err);

  s_high_water = 0;
  s_samples_read = 0;
  s_total_x = 0.0;
  while (1) {
    process_samples(&adxl345);
    dummy_autoc();
    printf("%d %5ld %f\n", s_high_water, s_samples_read, s_total_x);
  }
}

// =============================================================================
// local functions

static void turn_on_segments(void) {
  slcd_sync_seg_on(&SEGMENT_LCD_0, TSLCD_SEG_N0);
  slcd_sync_seg_on(&SEGMENT_LCD_0, TSLCD_SEG_N1);
  slcd_sync_seg_on(&SEGMENT_LCD_0, TSLCD_SEG_N2);
  slcd_sync_seg_on(&SEGMENT_LCD_0, TSLCD_SEG_N3);
  slcd_sync_seg_on(&SEGMENT_LCD_0, TSLCD_SEG_N4);

  slcd_sync_seg_on(&SEGMENT_LCD_0, TSLCD_SEG_S0);
  slcd_sync_seg_on(&SEGMENT_LCD_0, TSLCD_SEG_S1);
  slcd_sync_seg_on(&SEGMENT_LCD_0, TSLCD_SEG_S2);
  slcd_sync_seg_on(&SEGMENT_LCD_0, TSLCD_SEG_S3);
  slcd_sync_seg_on(&SEGMENT_LCD_0, TSLCD_SEG_S4);
  slcd_sync_seg_on(&SEGMENT_LCD_0, TSLCD_SEG_S5);
  slcd_sync_seg_on(&SEGMENT_LCD_0, TSLCD_SEG_S6);
  slcd_sync_seg_on(&SEGMENT_LCD_0, TSLCD_SEG_S7);

  slcd_sync_seg_on(&SEGMENT_LCD_0, TSLCD_SEG_D01);
  slcd_sync_seg_on(&SEGMENT_LCD_0, TSLCD_SEG_D02);
  slcd_sync_seg_on(&SEGMENT_LCD_0, TSLCD_SEG_D03);
}

static void blink_segments(void) {
  slcd_sync_seg_blink(&SEGMENT_LCD_0, TSLCD_SEG_B0, 1000);
  slcd_sync_seg_blink(&SEGMENT_LCD_0, TSLCD_SEG_B1, 1000);
  slcd_sync_seg_blink(&SEGMENT_LCD_0, TSLCD_SEG_B2, 1000);
}

static void animation_segments(void) {
  uint32_t segs[8] = {TSLCD_SEG_W0,  TSLCD_SEG_W1,  TSLCD_SEG_W2,
                      TSLCD_SEG_W3,  TSLCD_SEG_BT0, TSLCD_SEG_BT1,
                      TSLCD_SEG_BT2, TSLCD_SEG_BT3};
  slcd_sync_start_animation(&SEGMENT_LCD_0, segs, 8, 1000);
}

static void display_characters(void) {
  slcd_sync_write_char(&SEGMENT_LCD_0, '0', 0);
  slcd_sync_write_char(&SEGMENT_LCD_0, '1', 1);
  slcd_sync_write_string(&SEGMENT_LCD_0, (uint8_t *)"234", 3, 2);
  slcd_sync_write_string(&SEGMENT_LCD_0, (uint8_t *)"abcdefgh", 8, 5);
}

static void process_samples(adxl345_t *adxl345) {
  uint8_t reg, available;
  // adxl345_err_t err;

  // Read FIFO status register to find how many samples ara available
  adxl345_get_fifo_status_reg(adxl345, &reg);
  available = reg & 0x1f;
  // note high water mark
  if (available > s_high_water) s_high_water = available;
  for (int i = 0; i < available; i++) {
    process_sample(adxl345);
  }
}

static void process_sample(adxl345_t *adxl345) {
  adxl345_sample_t sample;
  // adxl345_err_t err;

  adxl345_get_sample(adxl345, &sample);
  s_samples_read += 1;
  s_total_x += sample.x;
}

/** @brief Time how long it takes to run the autocorrelation function.
*/
static int32_t dummy_autoc() {
  int32_t i_max, p_max;

  set_test_pin(true);
  p_max = 0;
  i_max = -1;

  for (int i=0; i<WINDOW_SIZE; i++) {
    for (int j=0; j<WINDOW_SIZE; j++) {
      uint32_t p = s_autoc_buf[j] * s_autoc_buf[j+i];
      if ((p > p_max) || (i_max <= 0)) {
        p_max = p;
        i_max = i;
      }
    }
  }
  set_test_pin(false);
  return i_max;
}

static void set_test_pin(bool val) {
  gpio_set_pin_level(TEST_PIN, val);  // PC03 on EXT1.10
}
