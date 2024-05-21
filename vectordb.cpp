#include <iostream>
#include "vectordb.hpp"
#include <algorithm>

namespace nwen {

    /**
     * Function to return the number of rows in the table.
     */
    int VectorDbTable::rows() const {
        return database.size();
    }

    /**
     * Function to get a movie record at a given index.
     */
    const movie* VectorDbTable::get(int index) const {
        if (index >= 0 && index < database.size()) {
            return &database[index];
        } else {
            return nullptr;
        }
    }

    /**
     * Function to add a new movie record to the table .
     */
    bool VectorDbTable::add(const movie& movie) {
        // Check if there is an existing record with the same id
        for (const auto& entry : database) {
            if (entry.id == movie.id) {
                return false;
            }
        }
        // Insert the new movie record
        database.push_back(movie);
        return true;
    }

    /**
     * Function to update a movie record in the table.
     */
    bool VectorDbTable::update(unsigned long id, const movie& movie) {
        // Find the movie record with the given id and update it
        for (auto& entry : database) {
            if (entry.id == id) {
                entry = movie;
                return true;
            }
        }
        return false; // Record with the given id not found
    }

    /**
     * Function to remove a movie record from the table.
     */
    bool VectorDbTable::remove(unsigned long id) {
        // Use remove_if algorithm to remove the movie record with the given id
        auto it = std::remove_if(database.begin(), database.end(), [id](const movie& m) {
            return m.id == id;
        });

        // Check if any records were removed
        if (it != database.end()) {
            database.erase(it, database.end());
            return true;
        }
        return false; // Record with the given id not found
    }
} // namespace nwen