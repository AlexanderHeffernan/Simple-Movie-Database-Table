/**
 * abstractdb.hpp
 * C++ header file that should contain declaration for
 * - struct movie (given)
 * - AbstractDbTable abstract class
 * 
 * You need to modify this file to declare AbstractDbTable abstract class 
 * as specified in the hand-out (Task 1)
 */ 



#ifndef __ABSTRACT_DB_HPP__
#define __ABSTRACT_DB_HPP__

#include <string>

namespace nwen 
{
    struct movie {
        unsigned long id;
        char title[50];
        unsigned short year;
        char director[50];
    };

    // Abstract class representing a database table
    class AbstractDbTable {
    public:
        virtual int rows() const = 0;
        virtual const movie* get(int index) const = 0;
        virtual void add(const movie& movie) = 0;
        virtual bool update(unsigned long id, const movie& movie) = 0;
        virtual bool remove(unsigned long id) = 0;

        bool loadCSV(const std::string &filename) = 0;
        bool saveCSV(const std::string &filename) = 0;
    }
}

#endif /* __ABSTRACT_DB_HPP__ */
