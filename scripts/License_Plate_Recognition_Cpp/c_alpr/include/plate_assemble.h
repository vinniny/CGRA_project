#ifndef PLATE_ASSEMBLE_H
#define PLATE_ASSEMBLE_H

#include "alpr_types.h"

int alpr_assemble_plate_text(
    const AlprCharacterArray* chars,
    AlprPlateType plate_type,
    char* out,
    int out_size
);

#endif
