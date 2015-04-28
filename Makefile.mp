include ../py/mkenv.mk

# qstr definitions (must come before including py.mk)
QSTR_DEFS = qstrdefsport.h

# include py core make definitions
include ../py/py.mk

OBJ = $(PY_O)

all: $(OBJ)

include ../py/mkrules.mk
