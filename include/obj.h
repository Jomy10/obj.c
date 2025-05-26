#ifndef OBJ_H
#define OBJ_H

#include <stddef.h>
#include <metalang99.h>

#ifndef OBJ_MALLOC
  #include <stdlib.h>
  #define OBJ_MALLOC(c) malloc(c)
  #define OBJ_FREE(c) free(c)
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef void* obj_t;

typedef obj_t(*__obj_create_t)();

typedef void(*obj_destructor_t)(obj_t);

struct Base {
  const char* classname;
  int refcount;
  obj_t parent;
  obj_destructor_t destructor;
};

typedef struct Base Base;

//==================//
// Class Definition //
//==================//

#define _OBJ_CREATE_FN(ClassName) __obj_create_instance_##ClassName

#define _CLASS_NEW_COMMON_PRE(ClassName) struct ClassName; typedef struct ClassName ClassName;
#define _CLASS_COMMON(...) ML99_OVERLOAD(_CLASS_COMMON_, __VA_ARGS__)
#define _CLASS_COMMON_1(ClassName) _CLASS_COMMON_2(ClassName, NULL)
#define _CLASS_COMMON_2(ClassName, del) _CLASS_NEW_COMMON_PRE(ClassName); \
  static obj_t _OBJ_CREATE_FN(ClassName)(size_t size) { \
    return obj_create(#ClassName, size, NULL, 0, del); \
  } \
  struct ClassName
#define _CLASS_COMMON_3(ClassName, del, parent) _CLASS_NEW_COMMON_PRE(ClassName); \
  static obj_t _OBJ_CREATE_FN(ClassName)(size_t size) { \
    return obj_create(#ClassName, size, _OBJ_CREATE_FN(parent), sizeof(parent), del); \
  } \
  struct ClassName

#define CLASS(...) _CLASS_COMMON(__VA_ARGS__)

#define CLASSI(name, parent) _CLASS_COMMON(name, NULL, parent)
#define CLASSD(name, del) _CLASS_COMMON(name, del)
#define CLASSDI(name, del, parent) _CLASS_COMMON(name, del, parent)

//=================//
// Object Creation //
//=================//

#define OBJ_CREATE(ClassName) _OBJ_CREATE_FN(ClassName)(sizeof(ClassName))

obj_t obj_create(
  const char* classname,
  size_t size,
  obj_t(*parent_create)(size_t),
  size_t parent_size,
  obj_destructor_t del
);

Base* obj_base(obj_t obj);
const char* obj_classname(obj_t obj);
obj_t obj_parent(obj_t obj);

#define OBJ_PARENT_OF(obj, ParentClassName) obj_parent_of(obj, #ParentClassName)

obj_t obj_parent_of(obj_t obj, const char* parent_classname);

void obj_retain(obj_t obj);
void obj_release(obj_t obj);

#ifdef __cplusplus
}
#endif

#endif // OBJ_H
