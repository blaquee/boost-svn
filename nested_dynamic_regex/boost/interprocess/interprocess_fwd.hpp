//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2007. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_FWD_HPP
#define BOOST_INTERPROCESS_FWD_HPP

#if (defined _MSC_VER) && (_MSC_VER >= 1200)
#  pragma once
#endif

//#include <boost/interprocess/detail/config_begin.hpp>
//#include <boost/interprocess/detail/workaround.hpp>

#include <cstddef>

//////////////////////////////////////////////////////////////////////////////
//                        Standard predeclarations
//////////////////////////////////////////////////////////////////////////////

namespace std {

template <class T>
class allocator;

template <class T>
struct less;

template <class T1, class T2>
struct pair;

template <class CharType> 
struct char_traits;

}  //namespace std {

namespace boost { namespace interprocess {

//////////////////////////////////////////////////////////////////////////////
//                            shared_memory
//////////////////////////////////////////////////////////////////////////////

class shared_memory_object;

#if (defined BOOST_WINDOWS) && !(defined BOOST_DISABLE_WIN32)
class windows_shared_memory;
#endif   //#if (defined BOOST_WINDOWS) && !(defined BOOST_DISABLE_WIN32)

//////////////////////////////////////////////////////////////////////////////
//              mapped file/mapped region/mapped_file
//////////////////////////////////////////////////////////////////////////////

class file_mapping;
class mapped_region;
class mapped_file;

//////////////////////////////////////////////////////////////////////////////
//                               Mutexes
//////////////////////////////////////////////////////////////////////////////

class null_mutex;

class interprocess_mutex;
class interprocess_recursive_mutex;

class named_mutex;
class named_recursive_mutex;

class interprocess_semaphore;
class named_semaphore;

//////////////////////////////////////////////////////////////////////////////
//                         Mutex families
//////////////////////////////////////////////////////////////////////////////

struct mutex_family;
struct null_mutex_family;

//////////////////////////////////////////////////////////////////////////////
//                   Other synchronization classes
//////////////////////////////////////////////////////////////////////////////

class barrier;
class interprocess_sharable_mutex;
class interprocess_condition;

//////////////////////////////////////////////////////////////////////////////
//                              Locks
//////////////////////////////////////////////////////////////////////////////

template <class Mutex>
class scoped_lock;

template <class SharableMutex>
class sharable_lock;

//////////////////////////////////////////////////////////////////////////////
//                      STL compatible allocators
//////////////////////////////////////////////////////////////////////////////

template<class T, class SegmentManager>
class allocator;

template<class T, class SegmentManager, std::size_t NodesPerChunk = 64>
class node_allocator;

template<class T, class SegmentManager, std::size_t NodesPerChunk = 64>
class private_node_allocator;

template<class T, class SegmentManager, std::size_t NodesPerChunk = 64>
class cached_node_allocator;

template<class T, class SegmentManager, std::size_t NodesPerChunk = 64, std::size_t MaxFreeChunks = 2>
class adaptive_pool;

template<class T, class SegmentManager, std::size_t NodesPerChunk = 64, std::size_t MaxFreeChunks = 2>
class private_adaptive_pool;

template<class T, class SegmentManager, std::size_t NodesPerChunk = 64, std::size_t MaxFreeChunks = 2>
class cached_adaptive_pool;


//////////////////////////////////////////////////////////////////////////////
//                            offset_ptr
//////////////////////////////////////////////////////////////////////////////

template <class T>
class offset_ptr;

//////////////////////////////////////////////////////////////////////////////
//                         intersegment_ptr
//////////////////////////////////////////////////////////////////////////////

template <class Mutex>
struct flat_map_intersegment;

template <class T/*, class PT = flat_map_intersegment<interprocess_mutex> */>
class intersegment_ptr;

//////////////////////////////////////////////////////////////////////////////
//                    Memory allocation algorithms
//////////////////////////////////////////////////////////////////////////////

//Single segment memory allocation algorithms
template<class MutexFamily, class VoidMutex = offset_ptr<void> >
class seq_fit;

template<class MutexFamily, class VoidMutex = offset_ptr<void> >
class simple_seq_fit;

template<class MutexFamily, class VoidMutex = offset_ptr<void> >
class rbtree_best_fit;

//Single segment memory allocation algorithms
template<class MutexFamily, class VoidMutex = intersegment_ptr<void> >
class multi_seq_fit;

template<class MutexFamily, class VoidMutex = intersegment_ptr<void> >
class multi_simple_seq_fit;

//////////////////////////////////////////////////////////////////////////////
//                         Index Types
//////////////////////////////////////////////////////////////////////////////

template<class IndexConfig> class flat_map_index;
template<class IndexConfig> class map_index;
template<class IndexConfig> class iset_index;
template<class IndexConfig> class null_index;

//////////////////////////////////////////////////////////////////////////////
//                         Segment manager
//////////////////////////////////////////////////////////////////////////////

template <class CharType
         ,class MemoryAlgorithm
         ,template<class IndexConfig> class IndexType>
class segment_manager;

//////////////////////////////////////////////////////////////////////////////
//                  External buffer managed memory classes
//////////////////////////////////////////////////////////////////////////////

template <class CharType
         ,class MemoryAlgorithm
         ,template<class IndexConfig> class IndexType>
class basic_managed_external_buffer;

typedef basic_managed_external_buffer
   <char
   ,rbtree_best_fit<null_mutex_family>
   ,iset_index>
managed_external_buffer;

typedef basic_managed_external_buffer
   <wchar_t
   ,rbtree_best_fit<null_mutex_family>
   ,iset_index>
wmanaged_external_buffer;

//////////////////////////////////////////////////////////////////////////////
//                      Shared memory managed memory classes
//////////////////////////////////////////////////////////////////////////////

template <class CharType
         ,class MemoryAlgorithm
         ,template<class IndexConfig> class IndexType>
class basic_managed_shared_memory;

typedef basic_managed_shared_memory 
   <char
   ,rbtree_best_fit<mutex_family>
   ,iset_index>
managed_shared_memory;

typedef basic_managed_shared_memory
   <wchar_t
   ,rbtree_best_fit<mutex_family>
   ,iset_index>
wmanaged_shared_memory;


//////////////////////////////////////////////////////////////////////////////
//                      Windows shared memory managed memory classes
//////////////////////////////////////////////////////////////////////////////

#if (defined BOOST_WINDOWS) && !(defined BOOST_DISABLE_WIN32)

template <class CharType
         ,class MemoryAlgorithm
         ,template<class IndexConfig> class IndexType>
class basic_managed_windows_shared_memory;

typedef basic_managed_windows_shared_memory 
   <char
   ,rbtree_best_fit<mutex_family>
   ,iset_index>
managed_windows_shared_memory;

typedef basic_managed_windows_shared_memory
   <wchar_t
   ,rbtree_best_fit<mutex_family>
   ,iset_index>
wmanaged_windows_shared_memory;

#endif   //#if (defined BOOST_WINDOWS) && !(defined BOOST_DISABLE_WIN32)

//////////////////////////////////////////////////////////////////////////////
//                      Fixed address shared memory
//////////////////////////////////////////////////////////////////////////////

typedef basic_managed_shared_memory
   <char
   ,rbtree_best_fit<mutex_family, void*>
   ,iset_index>
fixed_managed_shared_memory;

typedef basic_managed_shared_memory
   <wchar_t
   ,rbtree_best_fit<mutex_family, void*>
   ,iset_index>
wfixed_managed_shared_memory;

//////////////////////////////////////////////////////////////////////////////
//                      Heap memory managed memory classes
//////////////////////////////////////////////////////////////////////////////

template
   <class CharType
   ,class MemoryAlgorithm
   ,template<class IndexConfig> class IndexType>
class basic_managed_heap_memory;

typedef basic_managed_heap_memory
   <char
   ,rbtree_best_fit<null_mutex_family>
   ,iset_index>
managed_heap_memory;

typedef basic_managed_heap_memory
   <wchar_t
   ,rbtree_best_fit<null_mutex_family>
   ,iset_index>
wmanaged_heap_memory;

//////////////////////////////////////////////////////////////////////////////
//                         Mapped file managed memory classes
//////////////////////////////////////////////////////////////////////////////

template
   <class CharType
   ,class MemoryAlgorithm
   ,template<class IndexConfig> class IndexType>
class basic_managed_mapped_file;

typedef basic_managed_mapped_file
   <char
   ,rbtree_best_fit<mutex_family>
   ,iset_index>
managed_mapped_file;

typedef basic_managed_mapped_file
   <wchar_t
   ,rbtree_best_fit<mutex_family>
   ,iset_index>
wmanaged_mapped_file;

//////////////////////////////////////////////////////////////////////////////
//                            Exceptions
//////////////////////////////////////////////////////////////////////////////

class interprocess_exception;
class lock_exception;
class bad_alloc;

//////////////////////////////////////////////////////////////////////////////
//                            Bufferstream
//////////////////////////////////////////////////////////////////////////////

//bufferstream
template <class CharT
         ,class CharTraits = std::char_traits<CharT> >
class basic_bufferbuf;

template <class CharT
         ,class CharTraits = std::char_traits<CharT> >
class basic_ibufferstream;

template <class CharT
         ,class CharTraits = std::char_traits<CharT> >
class basic_obufferstream;

template <class CharT
         ,class CharTraits = std::char_traits<CharT> >
class basic_bufferstream;

//////////////////////////////////////////////////////////////////////////////
//                            Vectorstream
//////////////////////////////////////////////////////////////////////////////

template <class CharVector
         ,class CharTraits = std::char_traits<typename CharVector::value_type> >
class basic_vectorbuf;

template <class CharVector
         ,class CharTraits = std::char_traits<typename CharVector::value_type> >
class basic_ivectorstream;

template <class CharVector
         ,class CharTraits = std::char_traits<typename CharVector::value_type> >
class basic_ovectorstream;

template <class CharVector
         ,class CharTraits = std::char_traits<typename CharVector::value_type> >
class basic_vectorstream;

//////////////////////////////////////////////////////////////////////////////
//                             Smart pointers
//////////////////////////////////////////////////////////////////////////////

template<class T, class Deleter>
class scoped_ptr;

template<class T, class VoidPointer>
class intrusive_ptr;

//////////////////////////////////////////////////////////////////////////////
//                                  IPC
//////////////////////////////////////////////////////////////////////////////

class message_queue;

//////////////////////////////////////////////////////////////////////////////
//                             Containers
//////////////////////////////////////////////////////////////////////////////

//vector class
template <class T
         ,class A = std::allocator<T> >
class vector;

//list class
template <class T
         ,class A = std::allocator<T> >
class list;

//slist class
template <class T
         ,class Alloc = std::allocator<T> >
class slist;

//set class
template <class T
         ,class Pred  = std::less<T>
         ,class Alloc = std::allocator<T> >
class set;

//multiset class
template <class T
         ,class Pred  = std::less<T>
         ,class Alloc = std::allocator<T> >
class multiset;

//map class
template <class Key
         ,class T
         ,class Pred  = std::less<Key>
         ,class Alloc = std::allocator<std::pair<const Key, T> > >
class map;

//multimap class
template <class Key
         ,class T
         ,class Pred  = std::less<Key>
         ,class Alloc = std::allocator<std::pair<const Key, T> > >
class multimap;

//flat_set class
template <class T
         ,class Pred  = std::less<T>
         ,class Alloc = std::allocator<T> >
class flat_set;

//flat_multiset class
template <class T
         ,class Pred  = std::less<T>
         ,class Alloc = std::allocator<T> >
class flat_multiset;

//flat_map class
template <class Key
         ,class T
         ,class Pred  = std::less<Key>
         ,class Alloc = std::allocator<std::pair<Key, T> > >
class flat_map;

//flat_multimap class
template <class Key
         ,class T
         ,class Pred  = std::less<Key>
         ,class Alloc = std::allocator<std::pair<Key, T> > >
class flat_multimap;

//basic_string class
template <class CharT
         ,class Traits = std::char_traits<CharT>
         ,class Alloc  = std::allocator<CharT> > 
class basic_string;

//string class
typedef basic_string
   <char
   ,std::char_traits<char>
   ,std::allocator<char> >
string;

}}  //namespace boost { namespace interprocess {

//#include <boost/interprocess/detail/config_end.hpp>

#endif //#ifndef BOOST_INTERPROCESS_FWD_HPP

