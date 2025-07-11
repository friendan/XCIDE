#pragma once
#ifndef   XC_PUGIXML_WRAP_H
#define  XC_PUGIXML_WRAP_H

#include "lib/yyjson.h"


//@模块名称 YYJSON
//@版本 1
//@日期 1
//@作者 1
//@模块备注 1

//@src "lib/yyjson.c"
/*@声明



struct yyjson_val {
    uint64_t tag;
    yyjson_val_uni uni;
};

struct yyjson_doc {
    yyjson_val *root;
    yyjson_alc alc;
    size_t dat_read;
    size_t val_read;
    char *str_pool;
};

struct yyjson_mut_val {
    yyjson_val_uni uni; 
    yyjson_mut_val *next;
};

void yyjson_arr_foreach(arr, idx, max, val);
void yyjson_obj_foreach(obj, idx, max, key, val);
void yyjson_mut_arr_foreach(arr, idx, max, val);
void yyjson_mut_obj_foreach(obj, idx, max, key, val);
void yyjson_mut_arr_with_func(func);


bool yyjson_alc_pool_init(yyjson_alc *alc, void *buf, size_t size);

yyjson_doc *yyjson_read_opts(char *dat,size_t len,yyjson_read_flag flg,const yyjson_alc *alc,yyjson_read_err *err);


yyjson_doc *yyjson_read_file(const char *path,yyjson_read_flag flg,const yyjson_alc *alc,yyjson_read_err *err);

yyjson_doc *yyjson_read(const char *dat,size_t len,yyjson_read_flag flg);

size_t yyjson_read_max_memory_usage(size_t len,yyjson_read_flag flg);



char *yyjson_write_opts(const yyjson_doc *doc,yyjson_write_flag flg,const yyjson_alc *alc,size_t *len,yyjson_write_err *err);


bool yyjson_write_file(const char *path,const yyjson_doc *doc,yyjson_write_flag flg,const yyjson_alc *alc,yyjson_write_err *err);


char *yyjson_write(const yyjson_doc *doc,yyjson_write_flag flg,size_t *len);


char *yyjson_mut_write_opts(const yyjson_mut_doc *doc,yyjson_write_flag flg,const yyjson_alc *alc,size_t *len,yyjson_write_err *err);


bool yyjson_mut_write_file(const char *path,const yyjson_mut_doc *doc,yyjson_write_flag flg,const yyjson_alc *alc,yyjson_write_err *err);


char *yyjson_mut_write(const yyjson_mut_doc *doc,yyjson_write_flag flg,size_t *len);

char *yyjson_val_write_opts(const yyjson_val *val,yyjson_write_flag flg,const yyjson_alc *alc,size_t *len,yyjson_write_err *err);


bool yyjson_val_write_file(const char *path,const yyjson_val *val,yyjson_write_flag flg,const yyjson_alc *alc,yyjson_write_err *err);


char *yyjson_val_write(const yyjson_val *val,yyjson_write_flag flg,size_t *len);


char *yyjson_mut_val_write_opts(const yyjson_mut_val *val,yyjson_write_flag flg,const yyjson_alc *alc,size_t *len,yyjson_write_err *err);


bool yyjson_mut_val_write_file(const char *path,const yyjson_mut_val *val,yyjson_write_flag flg,const yyjson_alc *alc,yyjson_write_err *err);


char *yyjson_mut_val_write(const yyjson_mut_val *val,yyjson_write_flag flg,size_t *len);






yyjson_val *yyjson_doc_get_root(yyjson_doc *doc);
const char *yyjson_get_str(yyjson_val *val);
size_t yyjson_doc_get_read_size(yyjson_doc *doc);
size_t yyjson_doc_get_val_count(yyjson_doc *doc);
void yyjson_doc_free(yyjson_doc *doc);
bool yyjson_is_raw(yyjson_val *val);
bool yyjson_is_null(yyjson_val *val);
bool yyjson_is_true(yyjson_val *val);
bool yyjson_is_bool(yyjson_val *val);
bool yyjson_is_false(yyjson_val *val);
bool yyjson_is_uint(yyjson_val *val);
bool yyjson_is_sint(yyjson_val *val);
bool yyjson_is_int(yyjson_val *val);
bool yyjson_is_real(yyjson_val *val);
bool yyjson_is_num(yyjson_val *val);
bool yyjson_is_str(yyjson_val *val);
bool yyjson_is_arr(yyjson_val *val);
bool yyjson_is_obj(yyjson_val *val);
bool yyjson_is_ctn(yyjson_val *val);

yyjson_type yyjson_get_type(yyjson_val *val);
yyjson_subtype yyjson_get_subtype(yyjson_val *val);
uint8_t yyjson_get_tag(yyjson_val *val);
const char *yyjson_get_type_desc(yyjson_val *val);
const char *yyjson_get_raw(yyjson_val *val);
uint64_t yyjson_get_uint(yyjson_val *val);
bool yyjson_get_bool(yyjson_val *val);
int64_t yyjson_get_sint(yyjson_val *val);
int yyjson_get_int(yyjson_val *val);
double yyjson_get_real(yyjson_val *val);
bool yyjson_equals_str(yyjson_val *val, const char *str);
size_t yyjson_get_len(yyjson_val *val);
bool yyjson_equals_strn(yyjson_val *val, const char *str,size_t len);
bool yyjson_equals(yyjson_val *lhs, yyjson_val *rhs);
size_t yyjson_arr_size(yyjson_val *arr);
yyjson_val *yyjson_arr_get(yyjson_val *arr, size_t idx);
yyjson_val *yyjson_arr_get_first(yyjson_val *arr);
yyjson_val *yyjson_arr_get_last(yyjson_val *arr);
bool yyjson_arr_iter_init(yyjson_val *arr,yyjson_arr_iter *iter);
bool yyjson_arr_iter_has_next(yyjson_arr_iter *iter);
yyjson_val *yyjson_arr_iter_next(yyjson_arr_iter *iter);


size_t yyjson_obj_size(yyjson_val *obj);
yyjson_val *yyjson_obj_get(yyjson_val *obj, const char *key);
yyjson_val *yyjson_obj_getn(yyjson_val *obj, const char *key,size_t key_len);



bool yyjson_obj_iter_init(yyjson_val *obj,yyjson_obj_iter *iter);

bool yyjson_obj_iter_has_next(yyjson_obj_iter *iter);

yyjson_val *yyjson_obj_iter_next(yyjson_obj_iter *iter);

yyjson_val *yyjson_obj_iter_get_val(yyjson_val *key);


yyjson_val *yyjson_obj_iter_get(yyjson_obj_iter *iter,const char *key);

yyjson_val *yyjson_obj_iter_getn(yyjson_obj_iter *iter,const char *key,size_t key_len);



yyjson_mut_val *yyjson_mut_doc_get_root(yyjson_mut_doc *doc);



void yyjson_mut_doc_set_root(yyjson_mut_doc *doc,yyjson_mut_val *root);


void yyjson_mut_doc_free(yyjson_mut_doc *doc);

yyjson_mut_doc *yyjson_mut_doc_new(const yyjson_alc *alc);

yyjson_mut_doc *yyjson_doc_mut_copy(yyjson_doc *doc,const yyjson_alc *alc);


yyjson_mut_doc *yyjson_mut_doc_mut_copy(yyjson_mut_doc *doc,const yyjson_alc *alc);


yyjson_mut_val *yyjson_val_mut_copy(yyjson_mut_doc *doc,yyjson_val *val);


yyjson_mut_val *yyjson_mut_val_mut_copy(yyjson_mut_doc *doc,yyjson_mut_val *val);

bool yyjson_mut_is_raw(yyjson_mut_val *val);

bool yyjson_mut_is_null(yyjson_mut_val *val);

bool yyjson_mut_is_true(yyjson_mut_val *val);

bool yyjson_mut_is_false(yyjson_mut_val *val);

bool yyjson_mut_is_bool(yyjson_mut_val *val);

bool yyjson_mut_is_uint(yyjson_mut_val *val);

bool yyjson_mut_is_sint(yyjson_mut_val *val);

bool yyjson_mut_is_int(yyjson_mut_val *val);

bool yyjson_mut_is_real(yyjson_mut_val *val);

bool yyjson_mut_is_num(yyjson_mut_val *val);

bool yyjson_mut_is_str(yyjson_mut_val *val);

bool yyjson_mut_is_arr(yyjson_mut_val *val);

bool yyjson_mut_is_obj(yyjson_mut_val *val);

bool yyjson_mut_is_ctn(yyjson_mut_val *val);

yyjson_type yyjson_mut_get_type(yyjson_mut_val *val);

yyjson_subtype yyjson_mut_get_subtype(yyjson_mut_val *val);

uint8_t yyjson_mut_get_tag(yyjson_mut_val *val);

const char *yyjson_mut_get_type_desc(yyjson_mut_val *val);

const char *yyjson_mut_get_raw(yyjson_mut_val *val);

bool yyjson_mut_get_bool(yyjson_mut_val *val);

uint64_t yyjson_mut_get_uint(yyjson_mut_val *val);

int64_t yyjson_mut_get_sint(yyjson_mut_val *val);

int yyjson_mut_get_int(yyjson_mut_val *val);

double yyjson_mut_get_real(yyjson_mut_val *val);

const char *yyjson_mut_get_str(yyjson_mut_val *val);

size_t yyjson_mut_get_len(yyjson_mut_val *val);

bool yyjson_mut_equals_str(yyjson_mut_val *val,const char *str);

bool yyjson_mut_equals_strn(yyjson_mut_val *val,const char *str, size_t len);

bool yyjson_mut_equals(yyjson_mut_val *lhs,yyjson_mut_val *rhs);

yyjson_mut_val *yyjson_mut_raw(yyjson_mut_doc *doc,const char *str);

yyjson_mut_val *yyjson_mut_rawn(yyjson_mut_doc *doc,const char *str,size_t len);

yyjson_mut_val *yyjson_mut_rawcpy(yyjson_mut_doc *doc,const char *str);

yyjson_mut_val *yyjson_mut_rawncpy(yyjson_mut_doc *doc,const char *str,size_t len);

yyjson_mut_val *yyjson_mut_null(yyjson_mut_doc *doc);

yyjson_mut_val *yyjson_mut_true(yyjson_mut_doc *doc);

yyjson_mut_val *yyjson_mut_false(yyjson_mut_doc *doc);

yyjson_mut_val *yyjson_mut_bool(yyjson_mut_doc *doc,bool val);

yyjson_mut_val *yyjson_mut_uint(yyjson_mut_doc *doc,uint64_t num);

yyjson_mut_val *yyjson_mut_sint(yyjson_mut_doc *doc,int64_t num);

yyjson_mut_val *yyjson_mut_int(yyjson_mut_doc *doc,int64_t num);


yyjson_mut_val *yyjson_mut_real(yyjson_mut_doc *doc,double num);


yyjson_mut_val *yyjson_mut_str(yyjson_mut_doc *doc,const char *str);


yyjson_mut_val *yyjson_mut_strn(yyjson_mut_doc *doc,const char *str,size_t len);


yyjson_mut_val *yyjson_mut_strcpy(yyjson_mut_doc *doc,const char *str);


yyjson_mut_val *yyjson_mut_strncpy(yyjson_mut_doc *doc,const char *str,size_t len);



size_t yyjson_mut_arr_size(yyjson_mut_val *arr);

yyjson_mut_val *yyjson_mut_arr_get(yyjson_mut_val *arr,size_t idx);


yyjson_mut_val *yyjson_mut_arr_get_first(yyjson_mut_val *arr);


yyjson_mut_val *yyjson_mut_arr_get_last(yyjson_mut_val *arr);



bool yyjson_mut_arr_iter_init(yyjson_mut_val *arr,yyjson_mut_arr_iter *iter);


bool yyjson_mut_arr_iter_has_next(yyjson_mut_arr_iter *iter);


yyjson_mut_val *yyjson_mut_arr_iter_next(yyjson_mut_arr_iter *iter);


yyjson_mut_val *yyjson_mut_arr_iter_remove(yyjson_mut_arr_iter *iter);


yyjson_mut_val *yyjson_mut_arr(yyjson_mut_doc *doc);


yyjson_mut_val *yyjson_mut_arr_with_bool(yyjson_mut_doc *doc, const bool *vals, size_t count);


yyjson_mut_val *yyjson_mut_arr_with_sint(yyjson_mut_doc *doc, const int64_t *vals, size_t count);


yyjson_mut_val *yyjson_mut_arr_with_uint(yyjson_mut_doc *doc, const uint64_t *vals, size_t count);


yyjson_mut_val *yyjson_mut_arr_with_real(yyjson_mut_doc *doc, const double *vals, size_t count);


yyjson_mut_val *yyjson_mut_arr_with_sint8(yyjson_mut_doc *doc, const int8_t *vals, size_t count);


yyjson_mut_val *yyjson_mut_arr_with_sint16(yyjson_mut_doc *doc, const int16_t *vals, size_t count);


yyjson_mut_val *yyjson_mut_arr_with_sint32(yyjson_mut_doc *doc, const int32_t *vals, size_t count);


yyjson_mut_val *yyjson_mut_arr_with_sint64(yyjson_mut_doc *doc, const int64_t *vals, size_t count);


yyjson_mut_val *yyjson_mut_arr_with_uint8(yyjson_mut_doc *doc, const uint8_t *vals, size_t count);


yyjson_mut_val *yyjson_mut_arr_with_uint16(yyjson_mut_doc *doc, const uint16_t *vals, size_t count);


yyjson_mut_val *yyjson_mut_arr_with_uint32(yyjson_mut_doc *doc, const uint32_t *vals, size_t count);


yyjson_mut_val *yyjson_mut_arr_with_uint64(yyjson_mut_doc *doc, const uint64_t *vals, size_t count);


yyjson_mut_val *yyjson_mut_arr_with_float(yyjson_mut_doc *doc, const float *vals, size_t count);


yyjson_mut_val *yyjson_mut_arr_with_double(yyjson_mut_doc *doc, const double *vals, size_t count);


yyjson_mut_val *yyjson_mut_arr_with_str(yyjson_mut_doc *doc, const char **vals, size_t count);


yyjson_mut_val *yyjson_mut_arr_with_strn(yyjson_mut_doc *doc, const char **vals, const size_t *lens, size_t count);


yyjson_mut_val *yyjson_mut_arr_with_strcpy(yyjson_mut_doc *doc, const char **vals, size_t count);


yyjson_mut_val *yyjson_mut_arr_with_strncpy(yyjson_mut_doc *doc, const char **vals, const size_t *lens, size_t count);


bool yyjson_mut_arr_insert(yyjson_mut_val *arr,yyjson_mut_val *val, size_t idx);


bool yyjson_mut_arr_append(yyjson_mut_val *arr,yyjson_mut_val *val);


bool yyjson_mut_arr_prepend(yyjson_mut_val *arr,yyjson_mut_val *val);


yyjson_mut_val *yyjson_mut_arr_replace(yyjson_mut_val *arr,size_t idx,yyjson_mut_val *val);


yyjson_mut_val *yyjson_mut_arr_remove(yyjson_mut_val *arr,size_t idx);


yyjson_mut_val *yyjson_mut_arr_remove_first(yyjson_mut_val *arr);


yyjson_mut_val *yyjson_mut_arr_remove_last(yyjson_mut_val *arr);


bool yyjson_mut_arr_remove_range(yyjson_mut_val *arr,size_t idx, size_t len);


bool yyjson_mut_arr_clear(yyjson_mut_val *arr);


bool yyjson_mut_arr_rotate(yyjson_mut_val *arr,size_t idx);


bool yyjson_mut_arr_add_val(yyjson_mut_val *arr,yyjson_mut_val *val);


bool yyjson_mut_arr_add_null(yyjson_mut_doc *doc,yyjson_mut_val *arr);


bool yyjson_mut_arr_add_true(yyjson_mut_doc *doc,yyjson_mut_val *arr);


bool yyjson_mut_arr_add_false(yyjson_mut_doc *doc,yyjson_mut_val *arr);


bool yyjson_mut_arr_add_bool(yyjson_mut_doc *doc,yyjson_mut_val *arr,bool val);


bool yyjson_mut_arr_add_uint(yyjson_mut_doc *doc,yyjson_mut_val *arr,uint64_t num);


bool yyjson_mut_arr_add_sint(yyjson_mut_doc *doc,yyjson_mut_val *arr,int64_t num);


bool yyjson_mut_arr_add_int(yyjson_mut_doc *doc,yyjson_mut_val *arr,int64_t num);


bool yyjson_mut_arr_add_real(yyjson_mut_doc *doc,yyjson_mut_val *arr,double num);


bool yyjson_mut_arr_add_str(yyjson_mut_doc *doc,yyjson_mut_val *arr,const char *str);


bool yyjson_mut_arr_add_strn(yyjson_mut_doc *doc,yyjson_mut_val *arr,const char *str,size_t len);


bool yyjson_mut_arr_add_strcpy(yyjson_mut_doc *doc,yyjson_mut_val *arr,const char *str);


bool yyjson_mut_arr_add_strncpy(yyjson_mut_doc *doc,yyjson_mut_val *arr,const char *str,size_t len);


yyjson_mut_val *yyjson_mut_arr_add_arr(yyjson_mut_doc *doc,yyjson_mut_val *arr);


yyjson_mut_val *yyjson_mut_arr_add_obj(yyjson_mut_doc *doc,yyjson_mut_val *arr);


size_t yyjson_mut_obj_size(yyjson_mut_val *obj);

yyjson_mut_val *yyjson_mut_obj_get(yyjson_mut_val *obj,const char *key);


yyjson_mut_val *yyjson_mut_obj_getn(yyjson_mut_val *obj,const char *key,size_t key_len);

bool yyjson_mut_obj_iter_init(yyjson_mut_val *obj,yyjson_mut_obj_iter *iter);


bool yyjson_mut_obj_iter_has_next(yyjson_mut_obj_iter *iter);


yyjson_mut_val *yyjson_mut_obj_iter_next(yyjson_mut_obj_iter *iter);


yyjson_mut_val *yyjson_mut_obj_iter_get_val(yyjson_mut_val *key);


yyjson_mut_val *yyjson_mut_obj_iter_remove(yyjson_mut_obj_iter *iter);


yyjson_mut_val *yyjson_mut_obj_iter_get(yyjson_mut_obj_iter *iter, const char *key);


yyjson_mut_val *yyjson_mut_obj_iter_getn(yyjson_mut_obj_iter *iter, const char *key, size_t key_len);

yyjson_mut_val *yyjson_mut_obj(yyjson_mut_doc *doc);


yyjson_mut_val *yyjson_mut_obj_with_str(yyjson_mut_doc *doc,const char **keys,const char **vals,size_t count);


yyjson_mut_val *yyjson_mut_obj_with_kv(yyjson_mut_doc *doc,const char **kv_pairs,size_t pair_count);


bool yyjson_mut_obj_add(yyjson_mut_val *obj,yyjson_mut_val *key,yyjson_mut_val *val);

bool yyjson_mut_obj_put(yyjson_mut_val *obj,yyjson_mut_val *key,yyjson_mut_val *val);


bool yyjson_mut_obj_insert(yyjson_mut_val *obj,yyjson_mut_val *key,yyjson_mut_val *val,size_t idx);


yyjson_mut_val *yyjson_mut_obj_remove(yyjson_mut_val *obj,yyjson_mut_val *key);


yyjson_mut_val *yyjson_mut_obj_remove_key(yyjson_mut_val *obj, const char *key);


yyjson_mut_val *yyjson_mut_obj_remove_keyn(yyjson_mut_val *obj, const char *key, size_t key_len);


bool yyjson_mut_obj_clear(yyjson_mut_val *obj);


bool yyjson_mut_obj_replace(yyjson_mut_val *obj,yyjson_mut_val *key,yyjson_mut_val *val);


bool yyjson_mut_obj_rotate(yyjson_mut_val *obj,size_t idx);


bool yyjson_mut_obj_add_null(yyjson_mut_doc *doc,yyjson_mut_val *obj,const char *key);

bool yyjson_mut_obj_add_true(yyjson_mut_doc *doc,yyjson_mut_val *obj,const char *key);


bool yyjson_mut_obj_add_false(yyjson_mut_doc *doc,yyjson_mut_val *obj,const char *key);

bool yyjson_mut_obj_add_bool(yyjson_mut_doc *doc,yyjson_mut_val *obj,const char *key, bool val);

bool yyjson_mut_obj_add_uint(yyjson_mut_doc *doc,yyjson_mut_val *obj,const char *key, uint64_t val);

bool yyjson_mut_obj_add_sint(yyjson_mut_doc *doc,yyjson_mut_val *obj,const char *key, int64_t val);

bool yyjson_mut_obj_add_int(yyjson_mut_doc *doc,yyjson_mut_val *obj,const char *key, int64_t val);

bool yyjson_mut_obj_add_real(yyjson_mut_doc *doc,yyjson_mut_val *obj,const char *key, double val);

bool yyjson_mut_obj_add_str(yyjson_mut_doc *doc,yyjson_mut_val *obj,const char *key, const char *val);


bool yyjson_mut_obj_add_strn(yyjson_mut_doc *doc,yyjson_mut_val *obj,const char *key,const char *val, size_t len);


bool yyjson_mut_obj_add_strcpy(yyjson_mut_doc *doc,yyjson_mut_val *obj,const char *key,const char *val);


bool yyjson_mut_obj_add_strncpy(yyjson_mut_doc *doc,yyjson_mut_val *obj,const char *key,const char *val, size_t len);


bool yyjson_mut_obj_add_val(yyjson_mut_doc *doc,yyjson_mut_val *obj,const char *key,yyjson_mut_val *val);


yyjson_mut_val *yyjson_mut_obj_remove_str(yyjson_mut_val *obj, const char *key);


yyjson_mut_val *yyjson_mut_obj_remove_strn(yyjson_mut_val *obj, const char *key, size_t len);


yyjson_val *yyjson_get_pointer(yyjson_val *val,const char *ptr);


yyjson_val *yyjson_get_pointern(yyjson_val *val,const char *ptr,size_t len);


yyjson_val *yyjson_doc_get_pointer(yyjson_doc *doc,const char *ptr);


yyjson_val *yyjson_doc_get_pointern(yyjson_doc *doc,const char *ptr,size_t len);


yyjson_mut_val *yyjson_mut_get_pointer(yyjson_mut_val *val,const char *ptr);


yyjson_mut_val *yyjson_mut_get_pointern(yyjson_mut_val *val,const char *ptr,size_t len);


yyjson_mut_val *yyjson_mut_doc_get_pointer(yyjson_mut_doc *doc, const char *ptr);


yyjson_mut_val *yyjson_mut_doc_get_pointern(yyjson_mut_doc *doc, const char *ptr, size_t len);




yyjson_mut_val *yyjson_merge_patch(yyjson_mut_doc *doc,yyjson_val *orig,yyjson_val *patch);


yyjson_mut_val *yyjson_mut_merge_patch(yyjson_mut_doc *doc,yyjson_mut_val *orig,yyjson_mut_val *patch);



*/



#endif