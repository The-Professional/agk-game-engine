#ifndef _deletefuncs_h
#define _deletefuncs_h

// Standard lib dependencies.
#include <map>
#include <unordered_map>
#include <set>
#include <list>
#include <vector>
#include <deque>
#include <algorithm>
#include <functional>

/// *************************************************************************
/// <summary>
/// Namespace containing template inline functions for freeing pointers.
/// </summary>
/// *************************************************************************
namespace NDelFunc
{
    /// *************************************************************************
    /// <summary>
    /// Safe-delete function for a pointer.
    /// </summary>
    /// *************************************************************************
    template <class T>
    inline void Delete(T & ptr)
    {
        // Check for NULL-pointer
        if (ptr != nullptr)
        {
            // Delete object pointed to.
            delete ptr;
            ptr = nullptr;
        }
    }


    /// *************************************************************************
    /// <summary>
    /// Close file.
    /// </summary>
    /// *************************************************************************
    template <class T>
    inline void CloseFileHandle(T & ptr)
    {
        // Check for NULL-pointer
        if (ptr != nullptr)
        {
            // Close file pointed to.
            fclose(ptr);
            ptr = nullptr;
        }
    }


    /// *************************************************************************
    /// <summary>
    /// Safe-delete function for array of pointers.
    /// </summary>
    /// *************************************************************************
    template <class T>
    inline void DeleteArray(T & ptr)
    {
        // Check for NULL-pointer
        if (ptr != nullptr)
        {
            // Delete object pointed to.
            delete [] ptr;
            ptr = nullptr;
        }
    }


    /// *************************************************************************
    /// <summary>
    /// Safe-delete function for vectors of pointers.
    /// </summary>
    /// *************************************************************************
    template <class T>
    inline void DeleteVectorPointers(std::vector<T> & obj)
    {
        // Loop through the vector and delete all objects pointed to.
        std::for_each(obj.begin(), obj.end(), Delete<T>);

        // Clear out the vector.
        obj.clear();
    }

    /// *************************************************************************
    /// <summary>
    /// Safe-delete function for a single pointer in a vector.
    /// </summary>
    /// *************************************************************************
    template <class T>
    inline void DeleteVectorPointer( T ptr, std::vector<T> & obj )
    {
        // Find the pointer in the vector and delete it.
        auto iter = std::find( obj.begin(), obj.end(), ptr );
        if( iter != obj.end() )
        {
            Delete( ptr );
            obj.erase( iter );
        }
    }

    /// *************************************************************************
    /// <summary>
    /// Safe-delete function for vectors of pointers.
    /// </summary>
    /// *************************************************************************
    template <class T>
    inline void DeleteVectorPointerArrays(std::vector<T> & obj)
    {
        // Loop through the vector and delete all objects pointed to.
        std::for_each(obj.begin(), obj.end(), DeleteArray<T>);

        // Clear out the vector.
        obj.clear();
    }


    /// *************************************************************************
    /// <summary>
    /// Safe-delete function for a deque of pointers.
    /// </summary>
    /// *************************************************************************
    template <class T>
    inline void DeleteDequePointers(std::deque<T> & obj)
    {
        // Loop through the vector and delete all objects pointed to.
        std::for_each(obj.begin(), obj.end(), Delete<T>);

        // Clear out the deque.
        obj.clear();
    }


    /// *************************************************************************
    /// <summary>
    /// Safe-delete function for lists of pointers.
    /// </summary>
    /// *************************************************************************
    template <class T>
    inline void DeleteListPointers(std::list<T> & obj)
    {
        // Loop through the list and delete all objects pointed to.
        std::for_each(obj.begin(), obj.end(), Delete<T>);

        // Clear out the list.
        obj.clear();
    }


    /// *************************************************************************
    /// <summary>
    /// Safe-delete function for sets of pointers.
    /// allocated object.
    ///
    /// NOTE: Sets are a very unique beast and can't be deleted in the same
    ///       fashion as lists, vectors, Deques etc.
    /// </summary>
    /// *************************************************************************
    template <class T>
    inline void DeleteSetPointers(std::set<T> & obj)
    {
        // Loop through the list and delete all objects pointed to.
        for( auto it = obj.begin(); 
                 it != obj.end(); ++it )
        {
            delete (*it);
        }

        // Clear out the set.
        obj.clear();
    }


    /// *************************************************************************
    /// <summary>
    /// Safe-delete function for maps where the 'second' is a pointer to an
    /// allocated object.
    /// </summary>
    /// *************************************************************************
    template <class key, class ptr>
    inline void DeleteMapPointers(std::map<key, ptr> & obj)
    {
        // Loop through the map and delete all objects pointed to.
        for( auto iter = obj.begin();
                 iter != obj.end();
                 ++iter)
        {
            // Delete object pointed to by the dereferenced iterator.
            Delete(iter->second);
        }

        // Clear out the map.
        obj.clear();
    }

    /// <summary>
    /// Safe-delete function for maps where the 'second' is a pointer to an
    /// allocated object.
    /// </summary>
    template <class key, class ptr>
    inline void DeleteMapPointers(std::map<const key, ptr> & obj)
    {
        // Loop through the map and delete all objects pointed to.
        for( auto iter = obj.begin();
                 iter != obj.end();
                 ++iter)
        {
            // Delete object pointed to by the dereferenced iterator.
            Delete(iter->second);
        }

        // Clear out the map.
        obj.clear();
    }


    /// *************************************************************************
    /// <summary>
    /// Templetized safe-delete function to delete a single pointer in a map.
    /// </summary>
    /// *************************************************************************
    template <class key, class ptr>
    inline void DeleteMapPointer( key _key, std::map<key, ptr> & obj )
    {
        // Find the object to delete.
        auto iter = obj.find( _key );
        if( iter != obj.end() )
        {
            // Delete the pointer and remove it from the map.
            Delete( iter->second );
            obj.erase( iter );
        }
    }

    /// <summary>
    /// Templetized safe-delete function to delete a single pointer in a map.
    /// </summary>
    template <class key, class ptr>
    inline void DeleteMapPointer( key _key, std::map<const key, ptr> & obj )
    {
        // Find the object to delete.
        auto iter = obj.find( _key );
        if( iter != obj.end() )
        {
            // Delete the pointer and remove it from the map.
            Delete( iter->second );
            obj.erase( iter );
        }
    }


    /// *************************************************************************
    /// <summary>
    /// Safe-delete function for maps where the 'second' is a pointer to an
    /// allocated object.
    /// </summary>
    /// *************************************************************************
    template <class key, class ptr>
    inline void DeleteUnorderedMapPointers(std::unordered_map<key, ptr> & obj)
    {
        // Loop through the map and delete all objects pointed to.
        for( auto iter = obj.begin();
                    iter != obj.end();
                    ++iter)
        {
            // Delete object pointed to by the dereferenced iterator.
            Delete(iter->second);
        }

        // Clear out the map.
        obj.clear();
    }

    /// <summary>
    /// Safe-delete function for maps where the 'second' is a pointer to an
    /// allocated object.
    /// </summary>
    template <class key, class ptr>
    inline void DeleteUnorderedMapPointers(std::unordered_map<const key, ptr> & obj)
    {
        // Loop through the map and delete all objects pointed to.
        for( auto iter = obj.begin();
                    iter != obj.end();
                    ++iter)
        {
            // Delete object pointed to by the dereferenced iterator.
            Delete(iter->second);
        }

        // Clear out the map.
        obj.clear();
    }
    
    /// <summary>
    /// Safe-delete function for maps where the 'second' is a pointer to an
    /// allocated object.
    /// </summary>
    template <class key, class ptr>
    inline void DeleteMultimapPointers(std::multimap<key, ptr> & obj)
    {
        // Loop through the map and delete all objects pointed to.
        for( auto iter = obj.begin();
                 iter != obj.end();
                 ++iter)
        {
            // Delete object pointed to by the dereferenced iterator.
            Delete(iter->second);
        }

        // Clear out the map.
        obj.clear();
    }
    
    /// <summary>
    /// Safe-delete function for maps where the 'second' is a pointer to an
    /// allocated object.
    /// </summary>
    template <class key, class ptr>
    inline void DeleteMultimapPointers(std::multimap<const key, ptr> & obj)
    {
        // Loop through the map and delete all objects pointed to.
        for( auto iter = obj.begin();
                 iter != obj.end();
                 ++iter)
        {
            // Delete object pointed to by the dereferenced iterator.
            Delete(iter->second);
        }

        // Clear out the map.
        obj.clear();
    }


    /// *************************************************************************
    /// <summary>
    /// Safe-delete function for maps where the 'second' is a vector
    /// containing allocated objects.
    /// </summary>
    /// *************************************************************************
    template <class key, class ptr>
    inline void DeleteMapVectorPointers( std::map<key, ptr> & obj )
    {
        // Loop through the map and delete all vectors with pointers.
        for( auto iter = obj.begin();
             iter != obj.end();
             ++iter )
        {
            // Delete vector of pointers.
            DeleteVectorPointers( iter->second );
        }

        // Clear out the map.
        obj.clear();
    }

    /// <summary>
    /// Safe-delete function for maps where the 'second' is a vector
    /// containing allocated objects.
    /// </summary>
    template <class key, class ptr>
    inline void DeleteMapVectorPointers( std::map<const key, ptr> & obj )
    {
        // Loop through the map and delete all vectors with pointers.
        for( auto iter = obj.begin();
             iter != obj.end();
             ++iter )
        {
            // Delete vector of pointers.
            DeleteVectorPointers( iter->second );
        }

        // Clear out the map.
        obj.clear();
    }
    
    /// <summary>
    /// Safe-delete function for maps where the 'second' is a vector
    /// containing allocated objects.
    /// </summary>
    template <class key, class ptr>
    inline void DeleteMapVectorPointers( key _key, std::map<key, ptr> & obj )
    {
        // Find the object to delete.
        auto iter = obj.find( _key );
        if( iter != obj.end() )
        {
            // Delete the vector of pointers and remove it from the map.
            DeleteVectorPointers( iter->second );
            obj.erase( iter );
        }
    }

    /// <summary>
    /// Safe-delete function for maps where the 'second' is a vector
    /// containing allocated objects.
    /// </summary>
    template <class key, class ptr>
    inline void DeleteMapVectorPointers( key _key, std::map<const key, ptr> & obj )
    {
        // Find the object to delete.
        auto iter = obj.find( _key );
        if( iter != obj.end() )
        {
            // Delete the pointer and remove it from the map.
            DeleteVectorPointers( iter->second );
            obj.erase( iter );
        }
    }
}

#endif // _deletefunc_h
