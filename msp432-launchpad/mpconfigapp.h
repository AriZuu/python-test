#define MICROPY_PY_IO               (1)
#define MICROPY_PY_IO_FILEIO        (1)
#define MICROPY_HELPER_LEXER_UNIX   (1)
#define MICROPY_READER_POSIX        (1)
#define MICROPY_PY_SYS_STDFILES     (1)

#define MICROPY_HW_BOARD_NAME "Ti Msp432 Launchpad"
#define MICROPY_HW_MCU_NAME "Arm Cortex-M4"

extern const struct _mp_obj_module_t mp_module_launchpad;

#define MICROPY_APP_BUILTIN_MODULES \
    { MP_OBJ_NEW_QSTR(MP_QSTR_launchpad), (mp_obj_t)&mp_module_launchpad },
