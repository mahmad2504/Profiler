#include <windows.h>
#include <stdio.h>
#include <iostream>
typedef struct circular_buffer
{
    void *buffer;     // data buffer
    void *buffer_end; // end of data buffer
    size_t capacity;  // maximum number of items in the buffer
    size_t count;     // number of items in the buffer
    size_t sz;        // size of each item in the buffer
    void *head;       // pointer to head
    void *tail;       // pointer to tail
} circular_buffer;

extern  circular_buffer circ_buff;
inline void cb_init(size_t capacity)
{
	size_t sz = 4;
	circular_buffer *cb = &circ_buff;
    cb->buffer = malloc(capacity * sz);
    if(cb->buffer == NULL)
	{
        // handle error
	}
    cb->buffer_end = (char *)cb->buffer + capacity * sz;
    cb->capacity = capacity;
    cb->count = 0;
    cb->sz = sz;
    cb->head = cb->buffer;
    cb->tail = cb->buffer;
}

inline void cb_free()
{
	circular_buffer *cb = &circ_buff;
    free(cb->buffer);
    // clear out other fields too, just to be safe
}

inline int cb_push_back(int item)
{
	circular_buffer *cb = &circ_buff;
    if(cb->count == cb->capacity)
	{
		printf("Debug Buffer Full\n");
        return -1;
	}
    std::memcpy(cb->head, &item, cb->sz);
    cb->head = (char*)cb->head + cb->sz;
    if(cb->head == cb->buffer_end)
        cb->head = cb->buffer;
    cb->count++;
	return 0;
}

inline int cb_pop_front(int *item)
{
	circular_buffer *cb = &circ_buff;
    if(cb->count == 0)
	{
		return -1;
	}
    memcpy(item, cb->tail, cb->sz);
    cb->tail = (char*)cb->tail + cb->sz;
    if(cb->tail == cb->buffer_end)
        cb->tail = cb->buffer;
    cb->count--;
	return 0;
}


using namespace std;
#define UINT64 __int64
UINT64 NU_Get_Time_Stamp()
{
    LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
    return li.QuadPart;
}

#define NO_OF_PROFILING_READING 50
#define TICKS_PER_MSEC 2823
#define DEBUG_LEVELS 100



#define SP(Tag) LARGE_INTEGER li##Tag; char *tag##Tag = #Tag; cb_push_back((int)tag##Tag); QueryPerformanceCounter(&li##Tag);
#define EP(Tag) LARGE_INTEGER le##Tag; QueryPerformanceCounter(&le##Tag);cb_push_back((int)(li##Tag.QuadPart - le##Tag.QuadPart));


#define PI \
	cb_init(NO_OF_PROFILING_READING*3);

#define PP \
{\
	int value;\
	int tab = 0;\
	while(cb_pop_front(&value) != -1)\
	{\
		if(value <= 0)\
		{\
			tab--;\
			for(int i=0;i<tab;i++)\
				cout << "---";\
			cout << abs(value)/TICKS_PER_MSEC << " msec\n";\
		}\
		else\
		{\
			for(int i=0;i<tab;i++)\
				cout << "---";\
			cout << (char *)(value) << "\n";\
			tab++;\
		}\
	}\
}