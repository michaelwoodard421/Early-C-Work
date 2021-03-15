#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Guards.h"
#include "Vec.h"

static void _ensure_capacity(Vec *self, size_t n);

/* Constructor / Destructor */

Vec Vec_value(size_t capacity, size_t item_size)
{
    Vec vec = {
        item_size,
        0,
        capacity,
        calloc(capacity, item_size)
    };
    OOM_GUARD(vec.buffer, __FILE__, __LINE__);
    return vec;
}

void Vec_drop(Vec *self)
{
    free(self->buffer);
    self->buffer = NULL;
    self->capacity = 0;
    self->length = 0;
}

/* Accessors */

size_t Vec_length(const Vec *self)
{
    return self->length;
}

void* Vec_ref(const Vec *self, size_t index)
{
    if (index < self->length) {
        return self->buffer + (index * self->item_size);
    } else {
        fprintf(stderr, "%s:%d - Out of Bounds", __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }
}

void Vec_get(const Vec *self, size_t index, void *out) {
   if (index < self->length && index >= 0){
       memcpy(out, Vec_ref(self, index), self->item_size);
   } else {
        fprintf(stderr, "%s:%d - Out of Bounds", __FILE__, __LINE__);
        exit(EXIT_FAILURE);
   }
}

void Vec_set(Vec *self, size_t index, const void *value) {
    if (index <= self->length && index >= 0){
       if (index == self ->length){
           _ensure_capacity(self, self->length + 1);

           self->length++;
       }
       memcpy(Vec_ref(self, index), value, self->item_size);
   } else {
        fprintf(stderr, "%s:%d - Out of Bounds", __FILE__, __LINE__);
        exit(EXIT_FAILURE);
   }
}

bool Vec_equals(const Vec *self, const Vec *other)
{
    if (self->length != other->length) {
        return false;
    }
    size_t commonLength = self->length;
    for (size_t i = 0; i < commonLength; i++){
        if (*((char*)Vec_ref(self, i))!= *((char*)Vec_ref(other, i))){
            return false;
        }
    }
    return true;
}

void Vec_splice(Vec *self, size_t index, size_t delete_count, const void *items, size_t insert_count)
{
    if (index + delete_count > self->length || index < 0){
        fprintf(stderr, "%s:%d - Out of Bounds", __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }

    _ensure_capacity(self, index + insert_count);
    size_t size = self->item_size;
    size_t temp = self->length;

    // first move the items that will be shifted
    memcpy(self->buffer + ((index + insert_count) * size), self->buffer + ((index + delete_count) * size), size * (temp - index - delete_count));

    // then put it new items
    memcpy(self->buffer + (index * size), items, size * insert_count);
    
    self->length = self->length - delete_count + insert_count;
}

static void _ensure_capacity(Vec *self, size_t n)
{
    if (n > self -> capacity) {
        size_t new_capacity = n * 2;
        self->buffer = realloc(self->buffer, new_capacity * self->item_size);
        OOM_GUARD(self->buffer, __FILE__, __LINE__);
        self->capacity = new_capacity;
    }
}
