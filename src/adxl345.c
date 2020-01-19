/**
 * MIT License
 *
 * Copyright (c) 2019 R. Dunbar Poor <rdpoor@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

// =============================================================================
// includes

#include "adxl345.h"

// =============================================================================
// local types and definitions

// =============================================================================
// local (forward) declarations

// =============================================================================
// local storage

static adxl345_t s_adxl345;

// =============================================================================
// public code

// ==========================================
// low-level register access

adxl345_err_t adxl345_get_devid_reg(uint8_t *val) {
  return adxl345_read_reg(ADXL345_DEVID, val);
}

adxl345_err_t adxl345_get_thresh_tap_reg(uint8_t *val) {
  return adxl345_read_reg(ADXL345_THRESH_TAP, val);
}

adxl345_err_t adxl345_set_thresh_tap_reg(uint8_t val) {
  return adxl345_write_reg(ADXL345_THRESH_TAP, val);
}

adxl345_err_t adxl345_get_ofsx_reg(uint8_t *val) {
  return adxl345_read_reg(ADXL345_OFSX, val);
}

adxl345_err_t adxl345_set_ofsx_reg(uint8_t val) {
  return adxl345_write_reg(ADXL345_OFSX, val);
}

adxl345_err_t adxl345_get_ofsy_reg(uint8_t *val) {
  return adxl345_read_reg(ADXL345_OFSY, val);
}

adxl345_err_t adxl345_set_ofsy_reg(uint8_t val) {
  return adxl345_write_reg(ADXL345_OFSX, val);
}

adxl345_err_t adxl345_get_ofsz_reg(uint8_t *val) {
  return adxl345_read_reg(ADXL345_OFSZ, val);
}

adxl345_err_t adxl345_set_ofsz_reg(uint8_t val) {
  return adxl345_write_reg(ADXL345_OFSZ, val);
}

adxl345_err_t adxl345_get_dur_reg(uint8_t *val) {
  return adxl345_read_reg(ADXL345_DUR, val);
}

adxl345_err_t adxl345_set_dur_reg(uint8_t val) {
  return adxl345_write_reg(ADXL345_DUR, val);
}

adxl345_err_t adxl345_get_latency_reg(uint8_t *val) {
  return adxl345_read_reg(ADXL345_LATENT, val);
}

adxl345_err_t adxl345_set_latency_reg(uint8_t val) {
  return adxl345_write_reg(ADXL345_LAT, val);
}

adxl345_err_t adxl345_get_window_reg(uint8_t *val) {
  return adxl345_read_reg(ADXL345_WINDOW, val);
}

adxl345_err_t adxl345_set_window_reg(uint8_t val) {
  return adxl345_write_reg(ADXL345_WINDOW, val);
}

adxl345_err_t adxl345_get_thresh_act_reg(uint8_t *val) {
  return adxl345_read_reg(ADXL345_THRESH_ACT, val);
}

adxl345_err_t adxl345_set_thresh_act_reg(uint8_t val) {
  return adxl345_write_reg(ADXL345_THRESH_ACT, val);
}

adxl345_err_t adxl345_get_thresh_inact_reg(uint8_t *val) {
  return adxl345_read_reg(ADXL345_THRESH_INACT, val);
}

adxl345_err_t adxl345_set_thresh_inact_reg(uint8_t val) {
  return adxl345_write_reg(ADXL345_THRESH_INACT, val);
}

adxl345_err_t adxl345_get_time_inact_reg(uint8_t *val) {
  return adxl345_read_reg(ADXL345_TIME_INACT, val);
}

adxl345_err_t adxl345_set_time_inact_reg(uint8_t val) {
  return adxl345_write_reg(ADXL345_TIME_INACT, val);
}

adxl345_err_t adxl345_get_act_inact_ctl_reg(adxl345_act_inact_ctl_reg *val) {
  return adxl345_read_reg(ADXL345_ACT_INACT_CTL, val);
}

adxl345_err_t adxl345_set_act_inact_ctl_reg(adxl345_act_inact_ctl_reg val) {
  return adxl345_write_reg(ADXL345_ACT_INACT_CTL, val);
}

adxl345_err_t adxl345_get_thresh_ff_reg(uint8_t *val) {
  return adxl345_read_reg(ADXL345_THRESH_FF, val);
}

adxl345_err_t adxl345_set_thresh_ff_reg(uint8_t val) {
  return adxl345_write_reg(ADXL345_THRESH_FF, val);
}

adxl345_err_t adxl345_get_time_ff_reg(uint8_t *val) {
  return adxl345_read_reg(ADXL345_TIME_FF, val);
}

adxl345_err_t adxl345_set_time_ff_reg(uint8_t val) {
  return adxl345_write_reg(ADXL345_TIME_FF, val);
}

adxl345_err_t adxl345_tap_axes_reg(adxl345_tap_axes_reg *val) {
  return adxl345_read_reg(ADXL345_TAP_AXES, val);
}

adxl345_err_t adxl345_set_tap_axes_reg(adxl345_tap_axes_reg val)  {
  return adxl345_write_reg(ADXL345_TAP_AXES, val);
}

adxl345_err_t adxl345_get_bw_rate_reg(adxl345_bw_rate_reg *val) {
  return adxl345_read_reg(ADXL345_BW_RATE, val);
}

adxl345_err_t adxl345_set_bw_rate_reg(adxl345_bw_rate_reg val) {
  return adxl345_write_reg(ADXL345_BW_RATE, val);
}

adxl345_err_t adxl345_get_power_ctl_reg(adxl345_power_ctl_reg *val) {
  return adxl345_read_reg(ADXL345_POWER_CTL, val);
}

adxl345_err_t adxl345_set_power_ctl_reg(adxl345_power_ctl_reg val) {
  return adxl345_write_reg(ADXL345_POWER_CTL, val);
}

adxl345_err_t adxl345_get_int_enable_reg(adxl345_interrupt_reg *val) {
  return adxl345_read_reg(ADXL345_INT_ENABLE, val);
}

adxl345_err_t adxl345_set_int_enable_reg(adxl345_interrupt_reg val) {
  return adxl345_write_reg(ADXL345_INT_ENABLE, val);
}

adxl345_err_t adxl345_get_int_map_reg(adxl345_interrupt_reg *val) {
   return adxl345_read_reg(ADXL345_INT_MAP, val);
}

adxl345_err_t adxl345_set_int_map_reg(adxl345_interrupt_reg val) {
   return adxl345_write_reg(ADXL345_INT_MAP, val);
}

adxl345_err_t adxl345_get_int_source_reg(adxl345_interrupt_reg *val) {
  return adxl345_read_reg(ADXL345_INT_SOURCE, val);
}

adxl345_err_t adxl345_get_data_format_reg(adxl345_data_format_reg *val) {
  return adxl345_read_reg(ADXL345_DATA_FORMAT, val);
}

adxl345_err_t adxl345_set_data_format_reg(adxl345_data_format_reg val) {
  return adxl345_write_reg(ADXL345_DATA_FORMAT, val);
}

adxl345_err_t adxl345_get_data_regs(adxl345_data_regs_t *dst) {
  return adxl345_read_regs(ADXL345_DATAX0, dst, sizeof(adxl345_data_t));
}

adxl345_err_t adxl345_get_fifo_ctl_reg(adxl345_fifo_mode_reg *val) {
  return adxl345_read_reg(ADXL345_FIFO_CTL, val);
}

adxl345_err_t adxl345_set_fifo_ctl_reg(adxl345_fifo_mode_reg val) {
  return adxl345_write_reg(ADXL345_FIFO_CTL, val);
}

adxl345_err_t adxl345_get_fifo_status_reg(adxl345_fifo_status_reg *val) {
  return adxl345_read_reg(ADXL345_FIFO_STATUS, val);
}

// ==========================================
// higher level functions.  In the functions below,
// _g stands for gravity and _s stands for seconds.

adxl345_err_t adxl345_get_tap_thresh_g(float *val) {
  uint8_t reg;
  adxl345_err_t err = adxl345_get_tap_thresh_reg(&reg);
  *val = (err == ADXL345_ERR_NONE) ? reg * ADXL345_TAP_THESH_SCALE : 0.0;
  return err;
}

adxl345_err_t adxl345_set_tap_thresh_g(float val) {
  uint8_t reg = val / ADXL345_TAP_THESH_SCALE;
  return adxl345_set_tap_thresh_reg(&reg);
}

adxl345_err_t adxl345_get_ofsx_g(float *val) {
  uint8_t reg;
  adxl345_err_t err = adxl345_get_ofsx_reg(&reg);
  *val = (err == ADXL345_ERR_NONE) ? reg * ADXL345_OFSx_SCALE : 0.0;
  return err;
}

adxl345_err_t adxl345_set_ofsx_g(float val) {
  uint8_t reg = val / ADXL345_OFSx_SCALE;
  return adxl345_set_ofsx_reg(&reg);
}

adxl345_err_t adxl345_get_ofsy_g(float *val);
adxl345_err_t adxl345_set_ofsy_g(float val);

adxl345_err_t adxl345_get_ofsz_g(float *val);
adxl345_err_t adxl345_set_ofsz_g(float val);

adxl345_err_t adxl345_get_dur_g(float *val);
adxl345_err_t adxl345_set_dur_g(float val);

adxl345_err_t adxl345_get_latency_s(float *val);
adxl345_err_t adxl345_set_latency_s(float val);

adxl345_err_t adxl345_get_window_s(float *val);
adxl345_err_t adxl345_set_window_s(float val);

adxl345_err_t adxl345_get_thresh_act_g(float *val);
adxl345_err_t adxl345_set_thresh_act_g(float val);

adxl345_err_t adxl345_get_thresh_inact_g(float *val);
adxl345_err_t adxl345_set_thresh_inact_g(float val);

adxl345_err_t adxl345_get_time_inact_s(float *val);
adxl345_err_t adxl345_set_time_inact_s(float val);

adxl345_err_t adxl345_get_thresh_ff_g(float *val);
adxl345_err_t adxl345_set_thresh_ff_g(float val);

adxl345_err_t adxl345_get_time_ff_s(float *val);
adxl345_err_t adxl345_set_time_ff_s(float val);

adxl345_err_t adxl345_sample_is_available(bool *val);

/** @brief Read an x, y, z sample frame.
 */
adxl345_err_t adxl345_get_sample(adxl345_sample_t *sample);

adxl345_err_t adxl345_get_samples(adxl345_sample_t *samples, int num_samples);

// ============================================
// low-level I/O

/** @brief Read one ADXL345 register.
 *
 * @param addr Address of register to be read
 * @param dst Pointer to destination buffer.
 *
 * @return 0 on success, non-zero on error.
 */
adxl345_err_t adxl345_read_reg(uint8_t saddr, uint8_t *dst);

/** @brief Write one ADXL345 register.
 *
 * @param addr Address of register to be written.
 * @param val Value to be written.
 *
 * @return 0 on success, non-zero on error.
 */
adxl345_err_t adxl345_write_reg(uint8_t addr, uint8_t val);

/** @brief Read multiple registers from the ADXL345.
 *
 * Read one or more consecutive registers in a single I/O operation
 *
 * @param start_addr Address of first register to be read
 * @param dst Pointer to destination buffer.  Must have capacity of n_bytes.
 * @param n_bytes Number of registers to be read.
 *
 * @return 0 on success, non-zero on error.
 */
adxl345_err_t adxl345_read_regs(uint8_t start_addr, uint8_t *dst, uint8_t n_bytes);

/** @brief Write multiple registers to the ADXL345.
 *
 * Write one or more consecutive registers in a single I/O operation
 *
 * @param start_addr Address of first register to be written.
 * @param src Pointer to source data.  Must have capacity of n_bytes.
 * @param n_bytes Number of registers to be written.
 *
 * @return 0 on success, non-zero on error.
 */
adxl345_err_t adxl345_write_regs(uint8_t start_addr, uint8_t *src, uint8_t n_bytes);

// =============================================================================
// local (static) code
