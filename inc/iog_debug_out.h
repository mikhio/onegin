#ifndef IOG_DEBUG_OUT
#define IOG_DEBUG_OUT


//#define IOG_DEBUG_ON


#ifdef IOG_DEBUG_ON

#define IF_DEBUGING_THEN(x) ( x )

#else

#define IF_DEBUGING_THEN(x) {} 

#endif

#endif // IOG_DEBUG_OUT

