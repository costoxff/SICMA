#ifndef SICMA_PSEUDO_OOC_H
#define SICMA_PSEUDO_OOC_H

#define noargs void *_noargs
#define nulargs 0

typedef struct NullClass {} NullClass;

/* class forward declaration
 * forward declaration is useful when typedef a function pointer
 * who's parameter type is the class itself. And can also reduce 
 * the compiling time.
*/
#define class_fdecl(class_name) \
    typedef struct class_name class_name

/* class
 * please use it with below form
 *
 * class(ClassFoo, ParentFoo,
 *     int member_a;
 *     int member_b;
 *     void (*func_ptr)();
 *     etc.
 * )
*/
#define class(class_name, cls_inherit,...) \
    typedef struct class_name { \
        cls_inherit super; \
        __VA_ARGS__ \
    } class_name;

#define super(self) (self->super)

/* method template for function declare and define
 * please use it with below form
 *
 * for declare:
 * method_tmpl(ClassFoo,
 *             void, foo, int a, int *);
 *
 * for define:
 * method_tmpl(ClassFoo,
 *             void, foo, int a, int *)
 * {
 *     do something   
 * }
*/ 
#define method_tmpl(class_name, ret_type, method_name, ...) \
    ret_type class_name##_##method_name(class_name* self, __VA_ARGS__)

/*
 * calling class method
*/
#define method_call(obj, class_name, method_name, ...) \
    class_name##_##method_name((class_name *) obj, __VA_ARGS__)

/* For another strategy, considered using function pointer in struct like:
 * typedef struct Math Math;
 * typedef int (*math_func_t)(int a, int b);
 * struct Math{
 *     int PI;
 *     math_func_t add, sub;
 * }
 *
 * or
 *
 * typedef struct Object Object;
 * typedef int (*obj_func_t)(Object *);
 * struct Object{
 *     int member_a;
 *     int member_b;
 *     obj_func_t self_operate;
 * }
*/

#define class_declare(struct_name) typedef struct struct_name struct_name
#define class_define(struct_name) struct struct_name

#define callmd(obj, func_name, ...) obj->func_name(obj, __VA_ARGS__)


#define func_tmpl(ret_type, func_name, ...) \
    ret_type func_name(__VA_ARGS__)

#define class_binding_tmpl(ret_type, struct_name, ...) \
    func_tmpl(ret_type, struct_name##_func_binding, __VA_ARGS__)

#define class_init_tmpl(ret_type, struct_name, ...) \
    func_tmpl(ret_type, struct_name##_init, __VA_ARGS__)

#define class_dealloc_tmpl(ret_type, struct_name, ...) \
    func_tmpl(ret_type, struct_name##_dealloc, __VA_ARGS__)


#endif