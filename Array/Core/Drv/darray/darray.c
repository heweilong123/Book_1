#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>

#include "darray.h"

struct _sDARRAY
{
	void** p_vData;        /* 数据指针 */
	size_t _ulAllocSize;  /* 使用的长度 */
	size_t _ulSize;        /* 分配的长度 */
};

enum _Ret
{
	RET_PARAM_INVALID = 0,  /* 参数无效 */
	RET_REALLOC_NULL,       /* 分配空间异常 */
	RET_DESTORY_ERROR,      /* 删除异常 */
	RET_OK,
	RET_MAX,
};

static void** create_int_array(void* p_vArg)
{
	/* 队列最小长度为1 */
	if(p_vArg == NULL)
	{
			return NULL;
	}

	int _iNr = *(int*)p_vArg;
	if(_iNr < 1)
	{
			_iNr = 1;
	}

	/* 创建新队列 */
	int* p_vArray = (int*)malloc(sizeof(int) * _iNr);
	if(p_vArray == NULL)
	{
			return NULL;
	}

	for(int i = 0; i < _iNr; i++)
	{
			p_vArray[i] = rand() % 100;
	}

	return (void**)p_vArray;
}

Ret darray_create(DataCreateFunc p_vCreateFunc,
                  const size_t c_ulLen,
                  const void* cp_vArg,
                  _sDARRAY *p_sOut)
{
    p_sOut = NULL;

    if(p_vCreateFunc == NULL)
    {
        return RET_PARAM_INVALID;
    }
    
    /* 申请空间 */
    _sDARRAY* p_sArray = (_sDARRAY*)malloc(sizeof(_sDARRAY));
    if(p_sArray == NULL)
    {
        return RET_REALLOC_NULL;
    }
    memset(p_sArray, 0, sizeof(_sDARRAY));
    
    /* 申请数据空间 */
    size_t _ulArrayLen = c_ulLen < 1 ? 1 : c_ulLen;
    p_sArray->p_vData = p_vCreateFunc(_ulArrayLen, cp_vArg);
    if(p_sArray->p_vData == NULL)
    {
        free(p_sArray);
        return RET_REALLOC_NULL;
    }
    p_sArray->_ulSize = _ulArrayLen;
    p_sArray->_ulAllocSize = 0;
    p_sOut = p_sArray;
    
    return RET_OK;
}


Ret darray_destory( _sDARRAY* thiz, 
                    DataDestroyFunc p_vDestory, 
                    const void* cp_vArg)
{
    if(thiz == NULL || p_vDestory != NULL)
    {
        return RET_PARAM_INVALID;
    }

    /* 数据空间需要销毁 */
    if(thiz->p_vData != NULL)
    {
        p_vDestory(thiz->p_vData, cp_vArg);
    }

    free(thiz);

    return RET_OK;
}

// #define MIN_PRE_ALLOCATE_NR 10
// /**
//  * @description: 拓展数组大小 每次最少拓展到数组长度的1.5倍
//  * @param {DArray*} thiz 数组指针
//  * @param {size_t} need 拓展大小
//  * @return {Ret}
//  */
// static Ret darray_expend(DArray* thiz, size_t need)
// {
//     if(thiz == NULL)
//     {
//         return RET_PARAM_INVALID;
//     }

//     /* 需要分配更多的空间 */
//     if((thiz->size + need) > thiz->alloc_size)
//     {
//         /* 每次至少扩容1.5倍 + MIN_PRE_ALLOCATE_NR */
//         size_t alloc_size = thiz->alloc_size +
//                             (thiz->alloc_size >> 1) +
//                             MIN_PRE_ALLOCATE_NR;
//         alloc_size = fmax(alloc_size, need);

//         /* 重新分配存储空间 */
//         void** data = (void**) realloc(thiz->data,  sizeof(void*) * alloc_size);
//         if(data == NULL)
//         {
//             return RET_REALLOC_NULL;
//         }
//         else
//         {
//             thiz->data = data;
//             thiz->alloc_size = alloc_size;
//         }
//     }

//     return RET_OK;
// }

// /**
//  * @description: 减小空间
//  * @param {DArray*} thiz
//  * @return {*}
//  */
// static Ret darray_shrink(DArray* thiz)
// {
//     if(thiz == NULL)
//     {
//         return RET_PARAM_INVALID;
//     }

//     /* 使用空间小于总空间一半 && 总空间大于MIN_PRE_ALLOCATE_NR 才减小 */
//     if( thiz->size          < (thiz->alloc_size >> 1) &&
//         thiz->alloc_size    > MIN_PRE_ALLOCATE_NR)
//     {
//         size_t alloc_size = thiz->size + (thiz->size >> 1);
//         void** data = (void**)realloc(thiz->data, sizeof(void*) * alloc_size);
//         if(data == NULL)
//         {
//             return RET_REALLOC_NULL;
//         }
//         else
//         {
//             thiz->data = data;
//             thiz->alloc_size = alloc_size;
//         }
//     }

//     return RET_OK;
// }

// /**
//  * @description: 删除一个数据
//  * @param {DArray*} thiz
//  * @param {size_t} index
//  * @return {*}
//  */
// static Ret darray_destroy_data(DArray* thiz, size_t index)
// {
//     if(thiz == NULL || index >= thiz->size )
//     {
//         return RET_PARAM_INVALID;
//     }

//     //删除的数据之后的数据前移
//     for(size_t i = index; i < thiz->size; i++)
//     {
//         thiz->data[i] = thiz->data[i+1];
//     }

//     thiz->size--;

//     return RET_OK;
// }

// /**
//  * @description: 添加数据
//  * @param {DArray*} thiz
//  * @param {size_t} index
//  * @param {void*} data
//  * @return {*}
//  */
// Ret darray_insert(DArray* thiz, size_t index, void* data)
// {
//     if(thiz == NULL)
//     {
//         return RET_PARAM_INVALID;
//     }
    
//     /* 插入的位置 */
//     size_t cursor = index;
//     cursor = cursor < thiz->size ? cursor : thiz->size;
    
//     /* 数组扩容1位 */
//     if(darray_expend(thiz, 1) == RET_OK)
//     {
//         /* 插入点和插入点之后的数据后移 */
//         for (size_t i = thiz->size; i > cursor; i--)
//         {
//             thiz->data[i] = thiz->data[i - 1];
//         }
        
//         thiz->data[cursor] = data;
//         thiz->size++;

//         return RET_OK;
//     }
//     else
//     {
//         return RET_REALLOC_NULL;
//     }
// }

// /**
//  * @description: 删除数据
//  * @param {DArray*} thiz
//  * @param {size_t} index
//  * @return {*}
//  */
// Ret darray_delete(DArray* thiz, size_t index)
// {
//     if(thiz == NULL)
//     {
//         return RET_PARAM_INVALID;
//     }
    
//     if(darray_destroy_data(thiz, index) == RET_OK)
//     {
//         return darray_shrink(thiz);
//     }
//     else
//     {
//         return  RET_DESTORY_ERROR;
//     }
// }

// /**
//  * @description: 比较函数接口
//  * @param {void*} ctx
//  * @param {void*} data
//  * @return {*} 比较正确返回1; 相等返回0; 比较错误返回-1
//  */
// typedef int (*DataCompareFunc)(void* ctx, void* data);

// /**
//  * @description: 升序比较函数
//  * @param {void*} a
//  * @param {void*} b
//  * @return {*}
//  */
// int int_cmp(void* a, void* b)
// {
//     return *(int*)a - *(int*)b;
// }

// /**
//  * @description: 降序比较函数
//  * @param {void*} a
//  * @param {void*} b
//  * @return {*}
//  */
// int int_cmp(void* a, void* b)
// {
//     return *(int*)b - *(int*)a;
// }


// /**
//  * @description: 冒泡排序
//  * @param {void**} array
//  * @param {size_t} nr
//  * @param {DataCompareFunc} cmp
//  * @return {*}
//  */
// static Ret bulle_sort(void** array, size_t nr, DataCompareFunc cmp)
// {
//     if(array == NULL || cmp == NULL)
//     {
//         return RET_PARAM_INVALID;
//     }

//     if(nr < 2)
//     {
//         return RET_OK;
//     }

//     /*从右开始，每次对左侧的所有数据进行比较*/
//     size_t i = 0, max = 0, right = 0;
//     for(right = nr - 1; right > 0; right--)
//     {
//         for(i = 1; i < right; i++)
//         {
//             if(cmp(array[i], array[right]) > 0)
//             {
//                 max = i;
//             }
//         }

//         /* 判断是否需要改变right */
//         if(cmp(array[max], array[right]) > 0)
//         {
//             void *data = array[right];
//             array[right] = array[max];
//             array[max] = data;
//         }
//     }

//     return RET_OK;
// }













