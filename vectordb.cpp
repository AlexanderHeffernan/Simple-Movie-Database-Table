#include "vectordb.hpp"
#include <algorithm>

using namespace std;

namespace nwen
{
    /**
     * Gets the number of rows in the database.
     * 
     * @return Number of rows in the database.
     */
    int VectorDbTable::rows() const
    {
        return db.size();
    }

    /**
     * Gets an entry from the database at the specified index.
     * 
     * @param index Index of the entry to get from the database.
     * @return If index is within bounds, return the entry at that index, else, return nullptr.
     */
    const movie* VectorDbTable::get(int index) const
    {
        return (index >= 0 && index < db.size()) ? &db[index] : nullptr;
    }

    /**
     * Adds an entry to the database, assuming the movie is not already in the database.
     *
     * @param new_movie The movie to add to the database.
     * @return True if movie was successfully added, false otherwise.
     */
    bool VectorDbTable::add(const movie& new_movie)
    {
        if (any_of(db.begin(), db.end(), [&new_movie](const movie& m) { return m.id == new_movie.id; }))
            return false; // Movie already exists

        db.push_back(new_movie);
        return true;
    }

    /**
     * Updates a specified entry in the database.
     * 
     * @param id The id of the movie to update.
     * @param new_movie The update of the movie.
     * @return True if move was successfully updated, false otherwise.
     */
    bool VectorDbTable::update(unsigned long id, const movie& new_movie)
    {
        auto movie = find_if(db.begin(), db.end(), [id](const nwen::movie& m) { return m.id == id; });
        if (movie != db.end()) {
            *movie = new_movie;
            return true;
        }
        return false; // Record with the given id not found
    }

    /**
     * Removes a specified entry in the database.
     *
     * @param id The id of the movie to remove.
     * @return True if successfully removed, false otherwise.
     */
    bool VectorDbTable::remove(unsigned long id)
    {
        auto movie = remove_if(db.begin(), db.end(), [id](const nwen::movie& m) { return m.id == id; });
        if (movie != db.end()) {
            db.erase(movie, db.end());
            return true;
        }
        return false; // Record with the given id not found
    }
} // namespace nwen