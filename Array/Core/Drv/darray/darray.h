#ifndef __LIB_DARRAY_H_
#define __LIB_DARRAY_H_

struct _sDARRAY;
typedef struct _sDARRAY _sDARRAY;

enum _Ret;
typedef enum _Ret Ret;


/*************************************************************** 
 * Name:        DataCreateFunc()
 * Input :      const size_t    队列数据空间长度；
 *              const void*     队列数据空间创建函数的参数(可以为NULL)
 * Output:      
 * Return:      队列数据空间
 * Author:      hwl
 * Revise:      V1.0
 * Description: 队列数据空间创建函数
 ***************************************************************/
typedef void* (*DataCreateFunc)(const size_t, const void*);

/*************************************************************** 
 * Name:        darray_create()
 * Input :      p_vCreateFunc 队列数据空间创建函数; 
 *              c_ulLen 队列数据空间长度；
 *              cp_vArg 队列数据空间创建函数的参数(可以为NULL)
 * Output:      p_sOut 生成的队列指针
 * Return:      Ret 创建的状态
 * Author:      hwl
 * Revise:      V1.0
 * Description: 创建队列
 ***************************************************************/
Ret darray_create(DataCreateFunc p_vCreateFunc,
                  const size_t c_ulLen, 
                  const void* cp_vArg,
                  _sDARRAY *p_sOut);

/*************************************************************** 
 * Name:        DataDestroyFunc()
 * Input :      void*           队列数据空间
 *              const void*     队列数据空间销毁函数的参数(可以为NULL)
 * Output:      
 * Return:      
 * Author:      hwl
 * Revise:      V1.0
 * Description: 队列数据空间销毁函数
 ***************************************************************/
typedef void (*DataDestroyFunc)(void* , const void*);

/*************************************************************** 
 * Name:        darray_destory()
 * Input :      thiz          需要销毁的队列;
 *              p_vCreateFunc 队列数据空间销毁函数; 
 *              cp_vArg       队列数据空间销毁函数的参数(可以为NULL)
 * Output:      
 * Return:      Ret 销毁的状态
 * Author:      hwl
 * Revise:      V1.0
 * Description: 销毁队列
 ***************************************************************/      
Ret darray_destory( _sDARRAY* thiz, 
                    DataDestroyFunc p_vDestory, 
                    const void* cp_vArg);

// Ret darray_insert (DArray* thiz, size_t index, void* data);
// Ret darray_prepend(DArray* thiz, void* data);
// Ret darray_append (DArray* thiz, void* data);
// Ret darray_delete (DArray* thiz, size_t index);
// Ret darray_get_by_index (DArray* thiz, size_t index, void** data);
// Ret darray_set_by_index (DArray* thiz, size_t index, void* data);
// size_t darray_length (DArray* thiz);
// int darray_find (DArray* thiz, void* cmp, void* ctx);
// Ret darray_foreach (DArray* thiz, void* visit, void* ctx);


#endif