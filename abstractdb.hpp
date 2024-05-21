#ifndef __ABSTRACT_DB_HPP__
#define __ABSTRACT_DB_HPP__

#include <string>

namespace nwen 
{
    // Structure representing a movie
    struct movie {
        unsigned long id;
        char title[50];
        unsigned short year;
        char director[50];
    };

    // Abstract class representing a database table
    class AbstractDbTable {
    public:
        // Pure virtual functions
        virtual int rows() const = 0;
        virtual const movie* get(int index) const = 0;
        virtual bool add(const movie& movie) = 0;
        virtual bool update(unsigned long id, const movie& movie) = 0;
        virtual bool remove(unsigned long id) = 0;

        // Declaration for load and save functions
        bool loadCSV(const std::string &filename);
        bool saveCSV(const std::string &filename);
    };
} // namespace nwen

#endif // __ABSTRACT_DB_HPP__