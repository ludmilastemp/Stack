#ifndef STL_hash_
#define STL_hash_

/**
    \brief посчитать хеш
    \param data указатель
           size размер проверяемого отрезка памяти (в байтах)
    \return хеш
*/
long long
CountHash (void* data, long long size);

#endif /* STL_hash_ */
