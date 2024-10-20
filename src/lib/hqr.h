#ifndef HQR_H
#define HQR_H

#include "common.h"

i32 hqr_get_num_entries(c8 *filename);

i32 hqr_get_entry(u8 * ptr, c8 *filename, i32 index);
i32 hqr_get_entry_size(c8 *filename, i32 index);
i32 hqr_get_entry_alloc(u8 **ptr, c8 *filename, i32 index);
i32 hqr_get_hidden_entry_ptr(u8 **entry_ptr, u8 *hqr_ptr, i32 index);

#endif
