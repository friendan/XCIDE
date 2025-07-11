
#include "module_yyjsonobj.h"

CXTextA _uint64a(uint64_t nValue) {
    char buf[24] = {0};
    sprintf_s(buf, 24, "%llu", nValue);
    return buf;
}

CXTextA _int64a(int64_t nValue) {
    char buf[24] = {0};
    sprintf_s(buf, 24, "%lld", nValue);
    return buf;
}

CXTextA _doublea(double nValue) {
    char buf[32] = {0};
    sprintf_s(buf, 32, "%.15f", nValue);
    buf[18] = 0;
    bool z = true;
    for (int i = 17; i >= 0; i--) {
        if (z) {
            if (buf[i] == 0)
                continue;
            else
                z = false;
        }
        if (buf[i] == '0') {
            buf[i] = 0;
        } else if (buf[i] == '.') {
            buf[i] = 0;
            break;
        } else {
            break;
        }
    }
    return buf;
}

CXTextA _readval(yyjson_mut_val* val) {
    char* newchar = yyjson_mut_val_write(val, 0, 0);
    CXTextA text = newchar;
    free(newchar);
    return text;
}

CXTextA _readval(yyjson_val* val) {
    char* newchar = yyjson_val_write(val, 0, 0);
    CXTextA text = newchar;
    free(newchar);
    return text;
}

CXTextA CJsonRead::as_text() {
    switch (yyjson_get_tag(val)) {
        case YYJSON_TYPE_RAW | YYJSON_SUBTYPE_NONE:
            return JSON_NULL_TEXT;
        case YYJSON_TYPE_NULL | YYJSON_SUBTYPE_NONE:
            return "null";
        case YYJSON_TYPE_STR | YYJSON_SUBTYPE_NONE:
            return unsafe_yyjson_get_str(val);
        case YYJSON_TYPE_ARR | YYJSON_SUBTYPE_NONE:
            return JSON_NULL_TEXT;
        case YYJSON_TYPE_OBJ | YYJSON_SUBTYPE_NONE:
            return JSON_NULL_TEXT;
        case YYJSON_TYPE_BOOL | YYJSON_SUBTYPE_TRUE:
            return "true";
        case YYJSON_TYPE_BOOL | YYJSON_SUBTYPE_FALSE:
            return "false";
        case YYJSON_TYPE_NUM | YYJSON_SUBTYPE_UINT:
            return _uint64a(unsafe_yyjson_get_uint(val));
        case YYJSON_TYPE_NUM | YYJSON_SUBTYPE_SINT:
            return _int64a(unsafe_yyjson_get_int(val));
        case YYJSON_TYPE_NUM | YYJSON_SUBTYPE_REAL:
            return _readval(val);
        default:
            return JSON_NULL_TEXT;
    }
}

bool CJsonRead::parse(const char* szJson) {
    doc = yyjson_read(szJson, strlen(szJson), YYJSON_READ_ALLOW_INVALID_UNICODE);
    if (*doc)
        val = yyjson_doc_get_root(*doc);
    else
        val = NULL;
    return *doc != NULL;
}

const char* CJsonRead::get_key(size_t index) {
    size_t nlen = yyjson_obj_size(val);
    if (nlen >= index) {
        yyjson_obj_iter iter = yyjson_obj_iter_with(val);
        yyjson_val* obj = yyjson_obj_iter_next(&iter);
        for (size_t i = 0; i < index; i++) {
            obj = yyjson_obj_iter_next(&iter);
        }
        const char* str = yyjson_get_str(obj);
        return str ? str : JSON_NULL_TEXT;
    }
    return JSON_NULL_TEXT;
}

void CJsonObject::check_key_val() {
    if (mut_key && *mut_doc && mut_root && yyjson_mut_is_obj(mut_root)) {
        size_t key_len = strlen(mut_key);
        uint64_t tag = (((uint64_t)key_len) << YYJSON_TAG_BIT) | YYJSON_TYPE_STR;
        size_t len = yyjson_mut_obj_size(mut_root);
        if (len) {
            yyjson_mut_val* key = ((yyjson_mut_val*)mut_root->uni.ptr)->next->next;
            while (len-- > 0) {
                if (key->tag == tag &&
                    memcmp(key->uni.ptr, mut_key, key_len) == 0) {
                    mut_key = (const char*)key->uni.ptr;
                    mut_val = key->next;
                    break;
                }
                key = key->next->next;
            }
        }
    }
}

bool CJsonObject::add_key_val(yyjson_mut_val* val) {
    yyjson_mut_val* key = yyjson_mut_strcpy(*mut_doc, mut_key);
    if (yyjson_mut_obj_add(mut_root, key, val)) {
        mut_val = val;
        return true;
    } else {
        mut_val = NULL;
        return false;
    }
}

CJsonObject CJsonObject::get_obj(const char* key) {
    if (key && *mut_doc && mut_root) {
        if (mut_lv == 0) {
            if (yyjson_mut_is_obj(mut_root))
                return CJsonObject(mut_doc, mut_root, key);
        } else if (mut_val && yyjson_mut_is_obj(mut_val)) {
            return CJsonObject(mut_doc, mut_val, key);
        }
    }
    return CJsonObject(mut_doc, NULL);
}

CJsonObject CJsonObject::get_obj(size_t index) {
    if (*mut_doc && mut_root) {
        if (mut_lv == 0) {
            if (yyjson_mut_is_arr(mut_root)) {
                yyjson_mut_val* val = yyjson_mut_arr_get(mut_root, index);
                return CJsonObject(mut_doc, mut_root, NULL, val);
            }
        }
        yyjson_mut_val* val = yyjson_mut_arr_get(mut_val, index);
        if (val) return CJsonObject(mut_doc, mut_val, NULL, val);
    }
    return CJsonObject(mut_doc, NULL);
}

bool CJsonObject::add_str(const char* str) {
    if (!str || !mut_root || !*mut_doc) return false;

    if (mut_lv != 0 && mut_val == NULL) {
        mut_val = yyjson_mut_arr(*mut_doc);
        add_key_val(mut_val);
    }

    yyjson_mut_val* self_val = mut_lv == 0 ? mut_root : mut_val;
    yyjson_type self_type = unsafe_yyjson_get_type(self_val);

    switch (self_type) {
        case YYJSON_TYPE_OBJ:
            if (unsafe_yyjson_get_len(self_val) == 0)
                unsafe_yyjson_set_arr(self_val, 0);
            else
                break;
        case YYJSON_TYPE_ARR:
            yyjson_mut_val* val = yyjson_mut_strcpy(*mut_doc, str);
            return yyjson_mut_arr_append(self_val, val);
    }
    return false;
}

bool CJsonObject::add_raw(const char* raw) {
    if (!raw || !mut_root || !*mut_doc) return false;

    if (mut_lv != 0 && mut_val == NULL) {
        mut_val = yyjson_mut_arr(*mut_doc);
        add_key_val(mut_val);
    }

    yyjson_mut_val* self_val = mut_lv == 0 ? mut_root : mut_val;
    yyjson_type self_type = unsafe_yyjson_get_type(self_val);

    switch (self_type) {
        case YYJSON_TYPE_OBJ:
            if (unsafe_yyjson_get_len(self_val) == 0)
                unsafe_yyjson_set_arr(self_val, 0);
            else
                break;
        case YYJSON_TYPE_ARR:
            yyjson_mut_val* val = yyjson_mut_rawcpy(*mut_doc, raw);
            return yyjson_mut_arr_append(self_val, val);
    }
    return false;
}

bool CJsonObject::add_obj(const CJsonObject& object) {
    if (!mut_root || !*mut_doc) return false;

    yyjson_mut_val* copyval = object.mut_lv == 0 ? object.mut_root : object.mut_val;
    yyjson_type valtype = yyjson_mut_get_type(copyval);
    if (valtype < YYJSON_TYPE_ARR) return false;

    if (mut_lv != 0 && mut_val == NULL) {
        mut_val = yyjson_mut_arr(*mut_doc);
        add_key_val(mut_val);
    }

    yyjson_mut_val* self_val = mut_lv == 0 ? mut_root : mut_val;
    yyjson_type self_type = unsafe_yyjson_get_type(self_val);

    switch (self_type) {
        case YYJSON_TYPE_OBJ:
            if (unsafe_yyjson_get_len(self_val) == 0)
                unsafe_yyjson_set_arr(self_val, 0);
            else
                break;
        case YYJSON_TYPE_ARR:
            yyjson_mut_val* val = yyjson_mut_val_mut_copy(*mut_doc, copyval);
            return yyjson_mut_arr_append(self_val, val);
    }
    return false;
}

bool CJsonObject::add_int(int intn) {
    if (!mut_root || !*mut_doc) return false;

    if (mut_lv != 0 && mut_val == NULL) {
        mut_val = yyjson_mut_arr(*mut_doc);
        add_key_val(mut_val);
    }

    yyjson_mut_val* self_val = mut_lv == 0 ? mut_root : mut_val;
    yyjson_type self_type = unsafe_yyjson_get_type(self_val);

    switch (self_type) {
        case YYJSON_TYPE_OBJ:
            if (unsafe_yyjson_get_len(self_val) == 0)
                unsafe_yyjson_set_arr(self_val, 0);
            else
                break;
        case YYJSON_TYPE_ARR:
            yyjson_mut_val* val = yyjson_mut_int(*mut_doc, intn);
            return yyjson_mut_arr_append(self_val, val);
    }
    return false;
}
bool CJsonObject::add_double(double f) {
    if (!mut_root || !*mut_doc) return false;

    if (mut_lv != 0 && mut_val == NULL) {
        mut_val = yyjson_mut_arr(*mut_doc);
        add_key_val(mut_val);
    }

    yyjson_mut_val* self_val = mut_lv == 0 ? mut_root : mut_val;
    yyjson_type self_type = unsafe_yyjson_get_type(self_val);

    switch (self_type) {
        case YYJSON_TYPE_OBJ:
            if (unsafe_yyjson_get_len(self_val) == 0)
                unsafe_yyjson_set_arr(self_val, 0);
            else
                break;
        case YYJSON_TYPE_ARR:
            yyjson_mut_val* val = yyjson_mut_real(*mut_doc, f);
            return yyjson_mut_arr_append(self_val, val);
    }
    return false;
}
bool CJsonObject::add_uint(uint64_t uintn) {
    if (!mut_root || !*mut_doc) return false;

    if (mut_lv != 0 && mut_val == NULL) {
        mut_val = yyjson_mut_arr(*mut_doc);
        add_key_val(mut_val);
    }

    yyjson_mut_val* self_val = mut_lv == 0 ? mut_root : mut_val;
    yyjson_type self_type = unsafe_yyjson_get_type(self_val);

    switch (self_type) {
        case YYJSON_TYPE_OBJ:
            if (unsafe_yyjson_get_len(self_val) == 0)
                unsafe_yyjson_set_arr(self_val, 0);
            else
                break;
        case YYJSON_TYPE_ARR:
            yyjson_mut_val* val = yyjson_mut_uint(*mut_doc, uintn);
            return yyjson_mut_arr_append(self_val, val);
    }
    return false;
}

bool CJsonObject::add_sint(int64_t intn) {
    if (!mut_root || !*mut_doc) return false;

    if (mut_lv != 0 && mut_val == NULL) {
        mut_val = yyjson_mut_arr(*mut_doc);
        add_key_val(mut_val);
    }

    yyjson_mut_val* self_val = mut_lv == 0 ? mut_root : mut_val;
    yyjson_type self_type = unsafe_yyjson_get_type(self_val);

    switch (self_type) {
        case YYJSON_TYPE_OBJ:
            if (unsafe_yyjson_get_len(self_val) == 0)
                unsafe_yyjson_set_arr(self_val, 0);
            else
                break;
        case YYJSON_TYPE_ARR:
            yyjson_mut_val* val = yyjson_mut_sint(*mut_doc, intn);
            return yyjson_mut_arr_append(self_val, val);
    }
    return false;
}

bool CJsonObject::add_bool(bool b) {
    if (!mut_root || !*mut_doc) return false;

    if (mut_lv != 0 && mut_val == NULL) {
        mut_val = yyjson_mut_arr(*mut_doc);
        add_key_val(mut_val);
    }

    yyjson_mut_val* self_val = mut_lv == 0 ? mut_root : mut_val;
    yyjson_type self_type = unsafe_yyjson_get_type(self_val);

    switch (self_type) {
        case YYJSON_TYPE_OBJ:
            if (unsafe_yyjson_get_len(self_val) == 0)
                unsafe_yyjson_set_arr(self_val, 0);
            else
                break;
        case YYJSON_TYPE_ARR:
            yyjson_mut_val* val = b ? yyjson_mut_true(*mut_doc) : yyjson_mut_false(*mut_doc);
            return yyjson_mut_arr_append(self_val, val);
    }
    return false;
}
bool CJsonObject::add_null() {
    if (!mut_root || !*mut_doc) return false;

    if (mut_lv != 0 && mut_val == NULL) {
        mut_val = yyjson_mut_arr(*mut_doc);
        add_key_val(mut_val);
    }

    yyjson_mut_val* self_val = mut_lv == 0 ? mut_root : mut_val;
    yyjson_type self_type = unsafe_yyjson_get_type(self_val);

    switch (self_type) {
        case YYJSON_TYPE_OBJ:
            if (unsafe_yyjson_get_len(self_val) == 0)
                unsafe_yyjson_set_arr(self_val, 0);
            else
                break;
        case YYJSON_TYPE_ARR:
            yyjson_mut_val* val = yyjson_mut_null(*mut_doc);
            return yyjson_mut_arr_append(self_val, val);
    }
    return false;
}

bool CJsonObject::set_str(const char* str) {
    if (str && *mut_doc && mut_root) {
        if (mut_val) {
            const char* new_char = unsafe_yyjson_mut_strncpy(*mut_doc, str, strlen(str));
            return yyjson_mut_set_str(mut_val, new_char);
        } else if (mut_key) {
            return add_key_val(yyjson_mut_strcpy(*mut_doc, str));
        }
    }
    return false;
}

bool CJsonObject::set_raw(const char* raw) {
    if (raw && *mut_doc && mut_root) {
        if (mut_val) {
            size_t nlen = strlen(raw);
            const char* new_char = unsafe_yyjson_mut_strncpy(*mut_doc, raw, nlen);
            return yyjson_mut_set_raw(mut_val, new_char, nlen);
        } else if (mut_key) {
            return add_key_val(yyjson_mut_rawcpy(*mut_doc, raw));
        }
    }
    return false;
}

bool CJsonObject::remove() {
    if (mut_lv != 0 && mut_val && *mut_doc && mut_root) {
        if (mut_key) {
            if (yyjson_mut_obj_remove_key(mut_root, mut_key)) {
                mut_root = NULL;
                mut_key = NULL;
                mut_val = NULL;
                return true;
            }
        } else {
            if (yyjson_mut_is_arr(mut_root)) {
                size_t len = unsafe_yyjson_get_len(mut_root);
                if (len == 1) {
                    unsafe_yyjson_set_len(mut_root, len - 1);
                    mut_root = NULL;
                    mut_key = NULL;
                    mut_val = NULL;
                    return true;
                }
                if (len > 1) {
                    size_t idx = len--;
                    yyjson_mut_val* prev = ((yyjson_mut_val*)mut_root->uni.ptr);
                    yyjson_mut_val* next = prev->next;
                    while (idx-- > 0) {
                        if (next == mut_val) {
                            prev->next = next->next;
                            if ((void*)next == mut_root->uni.ptr)
                                mut_root->uni.ptr = prev;
                            unsafe_yyjson_set_len(mut_root, len);
                            mut_root = NULL;
                            mut_key = NULL;
                            mut_val = NULL;
                            return true;
                        }
                        prev = next;
                        next = next->next;
                    }
                }
            }
        }
    }
    return false;
}

bool CJsonObject::set_aar() {
    if (*mut_doc && mut_root) {
        if (mut_lv == 0) {
            return yyjson_mut_set_arr(mut_root);
        }
        if (mut_val) {
            return yyjson_mut_set_arr(mut_val);
        } else if (mut_key) {
            return add_key_val(yyjson_mut_arr(*mut_doc));
        }
    }
    return false;
}

bool CJsonObject::set_obj() {
    if (*mut_doc && mut_root) {
        if (mut_lv == 0) {
            return yyjson_mut_set_obj(mut_root);
        }
        if (mut_val) {
            return yyjson_mut_set_obj(mut_val);
        } else if (mut_key) {
            return add_key_val(yyjson_mut_obj(*mut_doc));
        }
    }
    return false;
}

bool CJsonObject::set_obj(const CJsonObject& object) {
    if (*mut_doc && mut_root) {
        yyjson_mut_val* copyval = object.mut_lv == 0 ? object.mut_root : object.mut_val;
        yyjson_type valtype = yyjson_mut_get_type(copyval);
        if (valtype < YYJSON_TYPE_ARR) return false;
        if (mut_lv == 0) {
            yyjson_mut_val* m_val = yyjson_mut_val_mut_copy(*mut_doc, copyval);
            if (m_val) {
                mut_root = m_val;
                return true;
            }
            return false;
        }
        if (mut_val) {
            yyjson_mut_val* m_val = yyjson_mut_val_mut_copy(*mut_doc, copyval);
            if (m_val) {
                mut_val->tag = m_val->tag;
                mut_val->uni.u64 = m_val->uni.u64;
                return true;
            }
        } else if (mut_key) {
            return add_key_val(yyjson_mut_val_mut_copy(*mut_doc, copyval));
        }
    }
    return false;
}

bool CJsonObject::set_int(int n) {
    if (*mut_doc && mut_root) {
        if (mut_val) {
            return yyjson_mut_set_int(mut_val, n);
        } else if (mut_key) {
            return add_key_val(yyjson_mut_int(*mut_doc, n));
        }
    }
    return false;
}

bool CJsonObject::set_double(double f) {

    if (*mut_doc && mut_root) {
        if (mut_val) {
            return yyjson_mut_set_real(mut_val, f);
        } else if (mut_key) {
            return add_key_val(yyjson_mut_real(*mut_doc, f));
        }
    }
    return false;
}

bool CJsonObject::set_uint(uint64_t uintn) {
    if (*mut_doc && mut_root) {
        if (mut_val) {
            return yyjson_mut_set_uint(mut_val, uintn);
        } else if (mut_key) {
            return add_key_val(yyjson_mut_uint(*mut_doc, uintn));
        }
    }
    return false;
}
bool CJsonObject::set_sint(int64_t intn) {
    if (*mut_doc && mut_root) {
        if (mut_val) {
            return yyjson_mut_set_sint(mut_val, intn);
        } else if (mut_key) {
            return add_key_val(yyjson_mut_sint(*mut_doc, intn));
        }
    }
    return false;
}

bool CJsonObject::set_bool(bool b) {
    if (*mut_doc && mut_root) {
        if (mut_val) {
            return yyjson_mut_set_bool(mut_val, b);
        } else if (mut_key) {
            return add_key_val(b ? yyjson_mut_true(*mut_doc) : yyjson_mut_false(*mut_doc));
        }
    }
    return false;
}

bool CJsonObject::set_null() {
    if (*mut_doc && mut_root) {
        if (mut_val) {
            return yyjson_mut_set_null(mut_val);
        } else if (mut_key) {
            return add_key_val(yyjson_mut_null(*mut_doc));
        }
    }
    return false;
}

CXTextA CJsonObject::writetext(yyjson_write_flag flg) {
    CXTextA text;
    yyjson_mut_doc_set_root(*mut_doc, mut_lv == 0 ? mut_root : mut_val);
    const char* json = yyjson_mut_write(*mut_doc, flg | YYJSON_WRITE_ALLOW_INVALID_UNICODE, NULL);
    if (json) {
        text = json;
        free((void*)json);
    } else {
        text = JSON_NULL_TEXT;
    }
    return text;
}
const char* CJsonObject::get_key(size_t index) {
    yyjson_mut_val* checkval = mut_lv == 0 ? mut_root : mut_val;
    size_t nlen = yyjson_mut_obj_size(checkval);
    if (nlen >= index) {
        yyjson_mut_obj_iter iter = yyjson_mut_obj_iter_with(checkval);
        yyjson_mut_val* obj = yyjson_mut_obj_iter_next(&iter);
        for (size_t i = 0; i < index; i++) {
            obj = yyjson_mut_obj_iter_next(&iter);
        }
        const char* str = yyjson_mut_get_str(obj);
        return str ? str : JSON_NULL_TEXT;
    }
    return JSON_NULL_TEXT;
}

CXTextA CJsonObject::as_text() {
    switch (yyjson_mut_get_tag(mut_val)) {
        case YYJSON_TYPE_RAW | YYJSON_SUBTYPE_NONE:
            return JSON_NULL_TEXT;
        case YYJSON_TYPE_NULL | YYJSON_SUBTYPE_NONE:
            return "null";
        case YYJSON_TYPE_STR | YYJSON_SUBTYPE_NONE:
            return unsafe_yyjson_get_str(mut_val);
        case YYJSON_TYPE_ARR | YYJSON_SUBTYPE_NONE:
            return JSON_NULL_TEXT;
        case YYJSON_TYPE_OBJ | YYJSON_SUBTYPE_NONE:
            return JSON_NULL_TEXT;
        case YYJSON_TYPE_BOOL | YYJSON_SUBTYPE_TRUE:
            return "true";
        case YYJSON_TYPE_BOOL | YYJSON_SUBTYPE_FALSE:
            return "false";
        case YYJSON_TYPE_NUM | YYJSON_SUBTYPE_UINT:
            return _uint64a(unsafe_yyjson_get_uint(mut_val));
        case YYJSON_TYPE_NUM | YYJSON_SUBTYPE_SINT:
            return _int64a(unsafe_yyjson_get_int(mut_val));
        case YYJSON_TYPE_NUM | YYJSON_SUBTYPE_REAL:
            return _readval(mut_val);
        default:
            return JSON_NULL_TEXT;
    }
}

bool CJsonObject::parse(const char* szJson) {
    yyjson_doc* doc = yyjson_read(szJson, strlen(szJson), YYJSON_READ_ALLOW_INVALID_UNICODE);
    if (doc) {
        yyjson_mut_doc* copydoc = yyjson_doc_mut_copy(doc, NULL);
        if (copydoc) {
            yyjson_mut_val* newroot = yyjson_mut_doc_get_root(copydoc);
            if (newroot) {
                mut_doc = copydoc;
                mut_root = newroot;
                mut_key = NULL;
                mut_val = NULL;
                mut_lv = 0;
                return true;
            }
            yyjson_mut_doc_free(copydoc);
        }
        yyjson_doc_free(doc);
    }
    return false;
}
