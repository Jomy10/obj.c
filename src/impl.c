#include <obj.h>
#include <string.h>

obj_t obj_create(
  const char* classname,
  size_t size,
  obj_t(*parent_create)(size_t),
  size_t parent_size,
  obj_destructor_t del
) {
  obj_t ptr = OBJ_MALLOC(size + sizeof(struct Base));
  struct Base* base = (struct Base*)ptr;
  base->classname = classname;
  base->refcount = 1;
  if (parent_create) {
    base->parent = parent_create(parent_size);
  } else {
    base->parent = NULL;
  }

  base->destructor = del;

  return ptr + sizeof(struct Base);
}

Base* obj_base(obj_t class) {
  return class - sizeof(struct Base);
}

const char* obj_classname(obj_t class) {
  return obj_base(class)->classname;
}

obj_t obj_parent(obj_t class) {
  return obj_base(class)->parent;
}

obj_t obj_parent_of(obj_t obj, const char* parent_classname) {
  if (strcmp(obj_classname(obj), parent_classname) == 0) {
    return obj;
  } else {
    return obj_parent_of(obj_parent(obj), parent_classname);
  }
}

void obj_retain(obj_t obj) {
  obj_base(obj)->refcount += 1;
}

void obj_release(obj_t obj) {
  struct Base* base = obj_base(obj);
  if (--base->refcount == 0) {
    if (base->parent != NULL) {
      obj_release(base->parent);
    }
    if (base->destructor != NULL) {
      base->destructor(obj);
    }
    OBJ_FREE((void*)base);
  }
}
