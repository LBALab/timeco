#ifndef HQR_H
#define HQR_H

#include "common.h"

i32 hqr_get_num_entries(i8 *filename);

i32 hqr_get_entry(u8 * ptr, i8 *filename, i32 index);
i32 hqr_get_entry_size(i8 *filename, i32 index);
i32 hqr_get_entry_alloc(u8 ** ptr, i8 *filename, i32 index);

#endif
