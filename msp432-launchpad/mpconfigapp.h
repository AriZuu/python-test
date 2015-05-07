extern const struct _mp_obj_module_t mp_module_launchpad;

#define MICROPY_APP_BUILTIN_MODULES \
    { MP_OBJ_NEW_QSTR(MP_QSTR_launchpad), (mp_obj_t)&mp_module_launchpad },
