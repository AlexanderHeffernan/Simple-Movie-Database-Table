#ifndef __VECTOR_DB_HPP__
#define __VECTOR_DB_HPP__

#include "abstractdb.hpp"
#include <vector>

using namespace std;

namespace nwen {

    /**
     * Class representing a database table implemented with a vector.
     */
    class VectorDbTable : public AbstractDbTable {
    private:
        vector<movie> db;

    public:
        // Default constructor
        VectorDbTable() {}
        
        // Override functions from AbstractDbTable
        int rows() const override;
        const movie* get(int index) const override;
        bool add(const movie& movie) override;
        bool update(unsigned long id, const movie& movie) override;
        bool remove(unsigned long id) override;
    };

} // namespace nwen

#endif /* __VECTOR_DB_HPP__ */