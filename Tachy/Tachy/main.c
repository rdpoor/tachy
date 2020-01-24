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

#define SAMPLE_BUF_SIZE 512
#define WINDOW_SIZE (SAMPLE_BUF_SIZE / 2)
#define MIN_OFFSET 12

typedef struct {
  int32_t dot_product;
  int offset;
} correlation_t;

// =============================================================================
// local declarations

static void turn_on_segments(void);
static void blink_segments(void);
static void animation_segments(void);
static void display_characters(void);

static void fetch_samples(adxl345_t *adxl345);

static void set_test_pin(bool val);

/** @brief Fetch a sample from the circular buffer */
static int32_t get_sample(int index);

/** @brief Write a sample to the circular buffer */
static void put_sample(int32_t sample);

/** @brief Compute one point of the autocorrlation */
static int32_t dot_product(int offset);

/** @brief Return the offset that produces the highest correlation */
static void autocorrelate(correlation_t *corr);

static void dump_sample_buf(void);

// =============================================================================
// local storage

static uint8_t s_high_water;
static uint32_t s_samples_read;
static int32_t sample_buf[SAMPLE_BUF_SIZE];
static int s_sample_index;


// =============================================================================
// main code

int main(void) {
  atmel_start_init();
  adxl345_err_t err;
  adxl345_t adxl345;
  adxl345_dev_t adxl345_dev;
  correlation_t corr;

  /* Replace with your application code */
  slcd_sync_enable(&SEGMENT_LCD_0);
  turn_on_segments();
  blink_segments();
  animation_segments();
  display_characters();

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
  while (1) {
    fetch_samples(&adxl345);
    autocorrelate(&corr);
    printf("%d %5ld %3d %ld\n", s_high_water, s_samples_read, corr.offset, corr.dot_product);
    // if (s_samples_read > SAMPLE_BUF_SIZE) {
    //   dump_sample_buf();
    //   return 0;
    // }
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

/** @brief Slurp available samples from FIFO and store in circular buffer */
static void fetch_samples(adxl345_t *adxl345) {
  uint8_t available;
  adxl345_isample_t sample;
  // adxl345_err_t err;

  /* err = */ adxl345_available_samples(adxl345, &available);
  // note high water mark
  if (available > s_high_water) s_high_water = available;
  s_samples_read += available;

  for (int i = 0; i < available; i++) {
    /* err = */ adxl345_get_isample(adxl345, &sample);
    // use only the z axis
    // printf("%d\n", sample.z - 245);
    put_sample(sample.z);
  }
}

static void set_test_pin(bool val) {
  gpio_set_pin_level(TEST_PIN, val);  // PC03 on EXT1.10
}

/** @brief Read a sample from the circular buffer.
 *
 * @param index Index into the buffer.  index = 0 is the oldest sample,
 *              index = SAMPLES_BUFFER_SIZE-1 is the newest
 * @return The sample.
 */
static int32_t get_sample(int index) {
  return sample_buf[(s_sample_index + index) % SAMPLE_BUF_SIZE];
}

/** @brief Write a sample into the circular buffer.
 *
 * This replaces the oldest sample with the newest.
 *
 * @param sample The sample to write.
 */
static void put_sample(int32_t sample) {
  sample_buf[s_sample_index++] = sample;
  if (s_sample_index >= SAMPLE_BUF_SIZE) {
    s_sample_index %= SAMPLE_BUF_SIZE;
  }
}

static int32_t dot_product(int offset) {
  int32_t total = 0;
  for (int i=0; i<WINDOW_SIZE; i++) {
    int32_t a = get_sample(i);
    int32_t b = get_sample(i+offset);
    total += a * b;
  }
  return total;
}

static void autocorrelate(correlation_t *corr) {
  set_test_pin(true);  // for scope timing

  // compute first point (makes inner loop more efficient)
  corr->dot_product = dot_product(MIN_OFFSET);
  corr->offset = MIN_OFFSET;

  // compute the rest of the points
  for (int offset=MIN_OFFSET+1; offset<WINDOW_SIZE; offset++) {
    int32_t dp = dot_product(offset);
    if (dp > corr->dot_product) {
      corr->dot_product = dp;
      corr->offset = offset;
    }
  }

  set_test_pin(false); // for scope timing
}

static void dump_sample_buf() {
  for (int i=0; i<SAMPLE_BUF_SIZE; i++) {
    printf("%d, %ld\n", i, get_sample(i));
  }
}
