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
     * @return A pointer to the movie entry at the specified index, or nullptr if the index is out of bounds.
     */
    const movie* VectorDbTable::get(int index) const
    {
        // Check if the index is within the valid range
        return (index >= 0 && index < db.size()) ? &db[index] : nullptr;
    }

    /**
     * Finds a movie entry in the database with the specified ID.
     *
     * @param db The database to search through.
     * @param id The ID of the movie entry to search for.
     * @return A pointer to the movie entry if found, otherwise nullptr.
     */ 
    movie* find_movie_by_id(vector<movie>& db, unsigned long id) {
        // Search for the movie entry with the specified ID using a lambda function
        auto movieIterator = find_if(db.begin(), db.end(), [id](const nwen::movie& m) {
            return m.id == id;
        });
        
        // Return a pointer to the movie if found, otherwise return nullptr
        return (movieIterator != db.end()) ? &(*movieIterator) : nullptr;
    }

    /**
     * Adds an movie entry to the database if it doesn't already exist.
     *
     * @param new_movie The movie to add to the database.
     * @return True if movie was successfully added, false otherwise.
     */
    bool VectorDbTable::add(const movie& new_movie)
    {
        // Check if a movie with the same ID already exists
        if (find_movie_by_id(db, new_movie.id) != nullptr)
            return false; // Movie already exists, do not add it
    
        // Add the new movie to the database
        db.push_back(new_movie);
        return true;
    }

    /**
     * Updates a movie entry in the database with the provided ID.
     * 
     * @param id The ID of the movie to update.
     * @param new_movie The updated movie information.
     * @return True if move was successfully updated, false otherwise.
     */
    bool VectorDbTable::update(unsigned long id, const movie& new_movie)
    {
        // Find the movie entry with the specified ID
        movie* existing_movie = find_movie_by_id(db, id);
        if (existing_movie == nullptr)
            return false; // Movie not found, cannot update

        // Update the movie entry with the new information
        *existing_movie = new_movie;
        return true;
    }

    /**
     * Removes a movie entry from the database with the specified ID.
     *
     * @param id The ID of the movie to remove.
     * @return True if successfully removed, false otherwise.
     */
    bool VectorDbTable::remove(unsigned long id)
    {
        // Find the movie entry with the specified ID
        if (find_movie_by_id(db, id) == nullptr)
            return false; // Movie not found, cannot remove

        // Remove the movie entry from the database
        db.erase(remove_if(db.begin(), db.end(), [id](const movie& m) { return m.id == id; }), db.end());
        return true;
    }
} // namespace nwen