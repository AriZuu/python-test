/*
 * Copyright (c) 2015, Ari Suutari <ari@stonepile.fi>.
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. The name of the author may not be used to endorse or promote
 *     products derived from this software without specific prior written
 *     permission. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
 * INDIRECT,  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <picoos.h>

#include "py/nlr.h"
#include "py/objtuple.h"
#include "py/objstr.h"
#include "py/runtime.h"
#include "py/stream.h"
#include "py/builtin.h"
#include "driverlib.h"

/*
 * Simple GPIO class.
 */

typedef struct _mp_obj_gpio_t {
    mp_obj_base_t base;
    int pin;
} mp_obj_gpio_t;

STATIC mp_obj_t gpio_set(mp_obj_t self_in, mp_obj_t arg) {

    mp_obj_gpio_t *self = self_in;
    int val = mp_obj_get_int(arg);

    if (val)
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
    else
        GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);

    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_2(gpio_set_obj, gpio_set);

STATIC const mp_map_elem_t gpio_locals_dict_table[] = {
    { MP_OBJ_NEW_QSTR(MP_QSTR_set), (mp_obj_t)&gpio_set_obj },
};

STATIC const mp_obj_type_t gpio_type;

STATIC mp_obj_t gpio_make_new(mp_obj_t type_in, mp_uint_t n_args, mp_uint_t n_kw, const mp_obj_t *args) {

    mp_obj_gpio_t *o = m_new_obj(mp_obj_gpio_t);
    o->base.type = &gpio_type;
    if (n_args > 0) {

        o->pin = mp_obj_get_int(args[0]);
    }
    return o;
}

STATIC MP_DEFINE_CONST_DICT(gpio_locals_dict, gpio_locals_dict_table);

STATIC const mp_obj_type_t gpio_type = {
    { &mp_type_type },
    .name = MP_QSTR_Gpio,
    .print = NULL,
    .make_new = gpio_make_new,
    .getiter = NULL,
    .iternext = NULL,
    .stream_p = NULL,
    .locals_dict = (mp_obj_t)&gpio_locals_dict,
};

/*
 * Launchpad module.
 */
STATIC const mp_map_elem_t mp_module_launchpad_globals_table[] = {

    { MP_OBJ_NEW_QSTR(MP_QSTR___name__), MP_OBJ_NEW_QSTR(MP_QSTR_launchpad) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_Gpio), (mp_obj_t)&gpio_type },
};

STATIC MP_DEFINE_CONST_DICT(mp_module_launchpad_globals, mp_module_launchpad_globals_table);

const mp_obj_module_t mp_module_launchpad = {
    .base = { &mp_type_module },
    .name = MP_QSTR_launchpad,
    .globals = (mp_obj_dict_t*)&mp_module_launchpad_globals,
};
