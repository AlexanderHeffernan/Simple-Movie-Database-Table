#include "abstractdb.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>

using namespace std;

namespace nwen
{
    template<typename Stream> // Allows error function to take in ofstream and ifstream files
    /**
     * Prints a specified error.
     * @return false.
     */
    bool error(const string& errorMessage, Stream& file)
    {
        cerr << errorMessage << endl;
        if (file.is_open())
            file.close();

        return false;
    }

    /**
     * Saves the contents of the database table to a CSV file.
     *
     * @param filename Name of the to save to.
     * @return True if successfully saved, false otherwise.
     */
    bool AbstractDbTable::saveCSV(const string &filename)
    {
        // Open the file for writing
        ofstream file(filename, ios::out | ios::trunc);
        if (!file.is_open())
            return error("Could not open the file " + filename + " for writing.", file);

        // Write each record to the file
        for (int i = 0; i < rows(); ++i) {
            const movie* m = get(i);
            if (!m)
                continue;

            // Format the movie record as CSV and write to file
            file << m->id << ",\"" << m->title << "\"," << m->year << ",\"" << m->director << "\"\n";
            if (file.fail()) // Check for writing errors
                return error("Error writing to the file " + filename, file);
        }

        // Close the file
        file.close();
        return true;
    }

    /**
     * Removes quotes from a string.
     *
     * @param str Strings to remove the quotes from.
     * @return The string with quotes removed.
     */
    string removeQuotes(const string &str) {
        return (str.length() > 1 && str.front() == '"' && str.back() == '"') ? str.substr(1, str.length() - 2) : str;
    }

    /**
     * Loads the contents of a CSV file into the database table.
     * 
     * @param filename The name of the file to load from.
     * @return True if successfully loaded, false otherwise.
     */
    bool AbstractDbTable::loadCSV(const string &filename) {
        // Open the file for reading
        ifstream file(filename);
        if (!file.is_open())
            return error("Could not open the file " + filename + " for reading.", file);

        // Read each line of the CSV file
        string line;
        while (getline(file, line)) {
            istringstream ss(line);
            movie m;
            // Declare strings for the line
            string id, title, year, director;

            // Parse each field from the line
            if (!getline(ss, id, ',') || !getline(ss, title, ',') || !getline(ss, year, ',') || !getline(ss, director, ','))
                return error("Error parsing line: " + line, file);

            try {
                // Convert id to unsigned long
                m.id = stoul(id);

                // Remove quotes from title and copy to movie title
                title = removeQuotes(title);
                strncpy(m.title, title.c_str(), sizeof(m.title) - 1);
                m.title[sizeof(m.title) - 1] = '\0';

                // Convert year to integer
                m.year = stoi(year);

                // Remove ruoes from director and copy to movie director
                director = removeQuotes(director);
                strncpy(m.director, director.c_str(), sizeof(m.director) - 1);
                m.director[sizeof(m.director) - 1] = '\0';

                // Add the movie record to the database
                if (!add(m))
                    error("Error adding movie to the database for line " + line, file);
            } catch (const exception& e) { // Handle exceptions during passing
                return error("Exception parsing line: " + line + " - " + e.what(), file);
            }
        }

        // Close the file
        file.close();
        return true;
    }
} // namespace nwen