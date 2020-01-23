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
#include "adxl345_err.h"
#include "adxl345_dev.h"

// =============================================================================
// local types and definitions

// =============================================================================
// local (forward) declarations

// =============================================================================
// local storage

// =============================================================================
// public code

adxl345_err_t adxl345_init(adxl345_t *adxl345, adxl345_dev_t * dev) {
  uint8_t reg;
  adxl345->dev = dev;
  adxl345_err_t err;

  if ((err = adxl345_get_devid_reg(adxl345, &reg)) != ADXL345_ERR_NONE) {
    // failed to read device ID
    return err;

  } else if (reg != ADXL345_DEVICE_ID) {
    // device ID doesn't match
    return ADXL354_ERR_INIT;

  } else {
    // success
    return ADXL345_ERR_NONE;
  }
}

// ==========================================
// low-level register access

adxl345_err_t adxl345_get_devid_reg(adxl345_t *adxl345, uint8_t *val) {
  return adxl345_dev_read_reg(adxl345->dev, ADXL345_REG_DEVID, val);
}

adxl345_err_t adxl345_get_thresh_tap_reg(adxl345_t *adxl345, uint8_t *val) {
  return adxl345_dev_read_reg(adxl345->dev, ADXL345_REG_THRESH_TAP, val);
}

adxl345_err_t adxl345_set_thresh_tap_reg(adxl345_t *adxl345, uint8_t val) {
  return adxl345_dev_write_reg(adxl345->dev, ADXL345_REG_THRESH_TAP, val);
}

adxl345_err_t adxl345_get_ofsx_reg(adxl345_t *adxl345, uint8_t *val) {
  return adxl345_dev_read_reg(adxl345->dev, ADXL345_REG_OFSX, val);
}

adxl345_err_t adxl345_set_ofsx_reg(adxl345_t *adxl345, uint8_t val) {
  return adxl345_dev_write_reg(adxl345->dev, ADXL345_REG_OFSX, val);
}

adxl345_err_t adxl345_get_ofsy_reg(adxl345_t *adxl345, uint8_t *val) {
  return adxl345_dev_read_reg(adxl345->dev, ADXL345_REG_OFSY, val);
}

adxl345_err_t adxl345_set_ofsy_reg(adxl345_t *adxl345, uint8_t val) {
  return adxl345_dev_write_reg(adxl345->dev, ADXL345_REG_OFSX, val);
}

adxl345_err_t adxl345_get_ofsz_reg(adxl345_t *adxl345, uint8_t *val) {
  return adxl345_dev_read_reg(adxl345->dev, ADXL345_REG_OFSZ, val);
}

adxl345_err_t adxl345_set_ofsz_reg(adxl345_t *adxl345, uint8_t val) {
  return adxl345_dev_write_reg(adxl345->dev, ADXL345_REG_OFSZ, val);
}

adxl345_err_t adxl345_get_dur_reg(adxl345_t *adxl345, uint8_t *val) {
  return adxl345_dev_read_reg(adxl345->dev, ADXL345_REG_DUR, val);
}

adxl345_err_t adxl345_set_dur_reg(adxl345_t *adxl345, uint8_t val) {
  return adxl345_dev_write_reg(adxl345->dev, ADXL345_REG_DUR, val);
}

adxl345_err_t adxl345_get_latency_reg(adxl345_t *adxl345, uint8_t *val) {
  return adxl345_dev_read_reg(adxl345->dev, ADXL345_REG_LATENT, val);
}

adxl345_err_t adxl345_set_latency_reg(adxl345_t *adxl345, uint8_t val) {
  return adxl345_dev_write_reg(adxl345->dev, ADXL345_REG_LATENT, val);
}

adxl345_err_t adxl345_get_window_reg(adxl345_t *adxl345, uint8_t *val) {
  return adxl345_dev_read_reg(adxl345->dev, ADXL345_REG_WINDOW, val);
}

adxl345_err_t adxl345_set_window_reg(adxl345_t *adxl345, uint8_t val) {
  return adxl345_dev_write_reg(adxl345->dev, ADXL345_REG_WINDOW, val);
}

adxl345_err_t adxl345_get_thresh_act_reg(adxl345_t *adxl345, uint8_t *val) {
  return adxl345_dev_read_reg(adxl345->dev, ADXL345_REG_THRESH_ACT, val);
}

adxl345_err_t adxl345_set_thresh_act_reg(adxl345_t *adxl345, uint8_t val) {
  return adxl345_dev_write_reg(adxl345->dev, ADXL345_REG_THRESH_ACT, val);
}

adxl345_err_t adxl345_get_thresh_inact_reg(adxl345_t *adxl345, uint8_t *val) {
  return adxl345_dev_read_reg(adxl345->dev, ADXL345_REG_THRESH_INACT, val);
}

adxl345_err_t adxl345_set_thresh_inact_reg(adxl345_t *adxl345, uint8_t val) {
  return adxl345_dev_write_reg(adxl345->dev, ADXL345_REG_THRESH_INACT, val);
}

adxl345_err_t adxl345_get_time_inact_reg(adxl345_t *adxl345, uint8_t *val) {
  return adxl345_dev_read_reg(adxl345->dev, ADXL345_REG_TIME_INACT, val);
}

adxl345_err_t adxl345_set_time_inact_reg(adxl345_t *adxl345, uint8_t val) {
  return adxl345_dev_write_reg(adxl345->dev, ADXL345_REG_TIME_INACT, val);
}

adxl345_err_t adxl345_get_act_inact_ctl_reg(adxl345_t *adxl345, adxl345_act_inact_ctl_reg *val) {
  return adxl345_dev_read_reg(adxl345->dev, ADXL345_REG_ACT_INACT_CTL, val);
}

adxl345_err_t adxl345_set_act_inact_ctl_reg(adxl345_t *adxl345, adxl345_act_inact_ctl_reg val) {
  return adxl345_dev_write_reg(adxl345->dev, ADXL345_REG_ACT_INACT_CTL, val);
}

adxl345_err_t adxl345_get_thresh_ff_reg(adxl345_t *adxl345, uint8_t *val) {
  return adxl345_dev_read_reg(adxl345->dev, ADXL345_REG_THRESH_FF, val);
}

adxl345_err_t adxl345_set_thresh_ff_reg(adxl345_t *adxl345, uint8_t val) {
  return adxl345_dev_write_reg(adxl345->dev, ADXL345_REG_THRESH_FF, val);
}

adxl345_err_t adxl345_get_time_ff_reg(adxl345_t *adxl345, uint8_t *val) {
  return adxl345_dev_read_reg(adxl345->dev, ADXL345_REG_TIME_FF, val);
}

adxl345_err_t adxl345_set_time_ff_reg(adxl345_t *adxl345, uint8_t val) {
  return adxl345_dev_write_reg(adxl345->dev, ADXL345_REG_TIME_FF, val);
}

adxl345_err_t adxl345_get_tap_axes_reg(adxl345_t *adxl345, adxl345_tap_axes_reg *val) {
  return adxl345_dev_read_reg(adxl345->dev, ADXL345_REG_TAP_AXES, val);
}

adxl345_err_t adxl345_set_tap_axes_reg(adxl345_t *adxl345, adxl345_tap_axes_reg val)  {
  return adxl345_dev_write_reg(adxl345->dev, ADXL345_REG_TAP_AXES, val);
}

adxl345_err_t adxl345_get_bw_rate_reg(adxl345_t *adxl345, adxl345_bw_rate_reg *val) {
  return adxl345_dev_read_reg(adxl345->dev, ADXL345_REG_BW_RATE, val);
}

adxl345_err_t adxl345_set_bw_rate_reg(adxl345_t *adxl345, adxl345_bw_rate_reg val) {
  return adxl345_dev_write_reg(adxl345->dev, ADXL345_REG_BW_RATE, val);
}

adxl345_err_t adxl345_get_power_ctl_reg(adxl345_t *adxl345, adxl345_power_ctl_reg *val) {
  return adxl345_dev_read_reg(adxl345->dev, ADXL345_REG_POWER_CTL, val);
}

adxl345_err_t adxl345_set_power_ctl_reg(adxl345_t *adxl345, adxl345_power_ctl_reg val) {
  return adxl345_dev_write_reg(adxl345->dev, ADXL345_REG_POWER_CTL, val);
}

adxl345_err_t adxl345_get_int_enable_reg(adxl345_t *adxl345, adxl345_interrupt_reg *val) {
  return adxl345_dev_read_reg(adxl345->dev, ADXL345_REG_INT_ENABLE, val);
}

adxl345_err_t adxl345_set_int_enable_reg(adxl345_t *adxl345, adxl345_interrupt_reg val) {
  return adxl345_dev_write_reg(adxl345->dev, ADXL345_REG_INT_ENABLE, val);
}

adxl345_err_t adxl345_get_int_map_reg(adxl345_t *adxl345, adxl345_interrupt_reg *val) {
   return adxl345_dev_read_reg(adxl345->dev, ADXL345_REG_INT_MAP, val);
}

adxl345_err_t adxl345_set_int_map_reg(adxl345_t *adxl345, adxl345_interrupt_reg val) {
   return adxl345_dev_write_reg(adxl345->dev, ADXL345_REG_INT_MAP, val);
}

adxl345_err_t adxl345_get_int_source_reg(adxl345_t *adxl345, adxl345_interrupt_reg *val) {
  return adxl345_dev_read_reg(adxl345->dev, ADXL345_REG_INT_SOURCE, val);
}

adxl345_err_t adxl345_get_data_format_reg(adxl345_t *adxl345, adxl345_data_format_reg *val) {
  return adxl345_dev_read_reg(adxl345->dev, ADXL345_REG_DATA_FORMAT, val);
}

adxl345_err_t adxl345_set_data_format_reg(adxl345_t *adxl345, adxl345_data_format_reg val) {
  return adxl345_dev_write_reg(adxl345->dev, ADXL345_REG_DATA_FORMAT, val);
}

adxl345_err_t adxl345_get_data_regs(adxl345_t *adxl345, adxl345_data_regs_t *dst) {
  return adxl345_dev_read_regs(adxl345->dev, ADXL345_REG_DATAX0, (uint8_t *)dst, sizeof(adxl345_data_regs_t));
}

adxl345_err_t adxl345_get_fifo_ctl_reg(adxl345_t *adxl345, adxl345_fifo_mode_reg *val) {
  return adxl345_dev_read_reg(adxl345->dev, ADXL345_REG_FIFO_CTL, val);
}

adxl345_err_t adxl345_set_fifo_ctl_reg(adxl345_t *adxl345, adxl345_fifo_mode_reg val) {
  return adxl345_dev_write_reg(adxl345->dev, ADXL345_REG_FIFO_CTL, val);
}

adxl345_err_t adxl345_get_fifo_status_reg(adxl345_t *adxl345, adxl345_fifo_status_reg *val) {
  return adxl345_dev_read_reg(adxl345->dev, ADXL345_REG_FIFO_STATUS, val);
}

// ==========================================
// higher level functions.  In the functions below,
// _g stands for gravity and _s stands for seconds.

/** @brief Enter measurement mode: start measuring */
adxl345_err_t adxl345_start(adxl345_t *adxl345) {
  uint8_t reg;
  adxl345_err_t err;

  err = adxl345_get_power_ctl_reg(adxl345, &reg);
  if (err != ADXL345_ERR_NONE) return err;

  err = adxl345_set_power_ctl_reg(adxl345, reg | ADXL345_MEASURE);
  return err;
}

/** @brief Enter standby mode: stop measuring */
adxl345_err_t adxl345_stop(adxl345_t *adxl345) {
  uint8_t reg;
  adxl345_err_t err;

  err = adxl345_get_power_ctl_reg(adxl345, &reg);
  if (err != ADXL345_ERR_NONE) return err;

  err = adxl345_set_power_ctl_reg(adxl345, reg & ~ADXL345_MEASURE);
  return err;
}


adxl345_err_t adxl345_get_tap_thresh_g(adxl345_t *adxl345, float *val) {
  uint8_t reg;
  adxl345_err_t err = adxl345_get_thresh_tap_reg(adxl345, &reg);
  *val = (err == ADXL345_ERR_NONE) ? reg * ADXL345_REG_THRESH_TAP_SCALE : 0.0;
  return err;
}

adxl345_err_t adxl345_set_tap_thresh_g(adxl345_t *adxl345, float val) {
  uint8_t reg = val / ADXL345_REG_THRESH_TAP_SCALE;
  return adxl345_set_thresh_tap_reg(adxl345, reg);
}

adxl345_err_t adxl345_get_ofsx_g(adxl345_t *adxl345, float *val) {
  uint8_t reg;
  adxl345_err_t err = adxl345_get_ofsx_reg(adxl345, &reg);
  *val = (err == ADXL345_ERR_NONE) ? reg * ADXL345_OFSx_SCALE : 0.0;
  return err;
}

adxl345_err_t adxl345_set_ofsx_g(adxl345_t *adxl345, float val) {
  uint8_t reg = val / ADXL345_OFSx_SCALE;
  return adxl345_set_ofsx_reg(adxl345, reg);
}

adxl345_err_t adxl345_get_ofsy_g(adxl345_t *adxl345, float *val);
adxl345_err_t adxl345_set_ofsy_g(adxl345_t *adxl345, float val);

adxl345_err_t adxl345_get_ofsz_g(adxl345_t *adxl345, float *val);
adxl345_err_t adxl345_set_ofsz_g(adxl345_t *adxl345, float val);

adxl345_err_t adxl345_get_dur_g(adxl345_t *adxl345, float *val);
adxl345_err_t adxl345_set_dur_g(adxl345_t *adxl345, float val);

adxl345_err_t adxl345_get_latency_s(adxl345_t *adxl345, float *val);
adxl345_err_t adxl345_set_latency_s(adxl345_t *adxl345, float val);

adxl345_err_t adxl345_get_window_s(adxl345_t *adxl345, float *val);
adxl345_err_t adxl345_set_window_s(adxl345_t *adxl345, float val);

adxl345_err_t adxl345_get_thresh_act_g(adxl345_t *adxl345, float *val);
adxl345_err_t adxl345_set_thresh_act_g(adxl345_t *adxl345, float val);

adxl345_err_t adxl345_get_thresh_inact_g(adxl345_t *adxl345, float *val);
adxl345_err_t adxl345_set_thresh_inact_g(adxl345_t *adxl345, float val);

adxl345_err_t adxl345_get_time_inact_s(adxl345_t *adxl345, float *val);
adxl345_err_t adxl345_set_time_inact_s(adxl345_t *adxl345, float val);

adxl345_err_t adxl345_get_thresh_ff_g(adxl345_t *adxl345, float *val);
adxl345_err_t adxl345_set_thresh_ff_g(adxl345_t *adxl345, float val);

adxl345_err_t adxl345_get_time_ff_s(adxl345_t *adxl345, float *val);
adxl345_err_t adxl345_set_time_ff_s(adxl345_t *adxl345, float val);

adxl345_err_t adxl345_sample_is_available(adxl345_t *adxl345, bool *val);

/** @brief Read an x, y, z sample frame.
 */
adxl345_err_t adxl345_get_sample(adxl345_t *adxl345, adxl345_sample_t *sample);

adxl345_err_t adxl345_get_samples(adxl345_t *adxl345, adxl345_sample_t *samples, int num_samples);

// =============================================================================
// local (static) code
