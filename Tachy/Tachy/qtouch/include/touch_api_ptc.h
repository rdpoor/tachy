
/*============================================================================
Filename : touch_api_ptc.h
Project : QTouch Modular Library
Purpose : Includes the Module API header files based on the configured modules,
          prototypes for touch.c file and Application helper API functions

This file is part of QTouch Modular Library Release 7.1 application.

Important Note: Do not edit this file manually.
                Use QTouch Configurator within Atmel Start to apply any
                modifications to this file.

Usage License: Refer license.h file for license information
Support: Visit http://www.microchip.com/support/hottopics.aspx
               to create MySupport case.

------------------------------------------------------------------------------
Copyright (c) 2019 Microchip. All rights reserved.
------------------------------------------------------------------------------
============================================================================*/

#ifndef TOUCH_API_PTC_H
#define TOUCH_API_PTC_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/*----------------------------------------------------------------------------
 *     include files
 *----------------------------------------------------------------------------*/

#include "hal_timer.h"

#include "qtm_common_components_api.h"
#include "qtm_binding_layer_0x0005_api.h"
#include "qtm_acq_saml22_0x0028_api.h"
#include "qtm_touch_key_0x0002_api.h"

/*----------------------------------------------------------------------------
 *   prototypes
 *----------------------------------------------------------------------------*/
/* Application Helper API's */
uint16_t get_sensor_node_signal(uint16_t sensor_node);
void     update_sensor_node_signal(uint16_t sensor_node, uint16_t new_signal);
uint16_t get_sensor_node_reference(uint16_t sensor_node);
void     update_sensor_node_reference(uint16_t sensor_node, uint16_t new_reference);
uint16_t get_sensor_cc_val(uint16_t sensor_node);
void     update_sensor_cc_val(uint16_t sensor_node, uint16_t new_cc_value);
uint8_t  get_sensor_state(uint16_t sensor_node);
void     update_sensor_state(uint16_t sensor_node, uint8_t new_state);
void     calibrate_node(uint16_t sensor_node);
uint8_t  get_scroller_state(uint16_t sensor_node);
uint16_t get_scroller_position(uint16_t sensor_node);

void touch_timer_handler(void);
void touch_init(void);
void touch_process(void);

void Timer_task_cb(const struct timer_task *const timer_task);
void touch_timer_config(void);

#ifdef __cplusplus
}
#endif

#endif /* TOUCH_API_PTC_H */
