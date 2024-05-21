#include "abstractdb.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>

namespace nwen {

    /**
     * Saves the contents of the database table to a CSV file.
     */
    bool AbstractDbTable::saveCSV(const std::string &filename) {
        // Open the file for writing and ensure it is emptied
        std::ofstream file(filename, std::ios::out | std::ios::trunc);
        if (!file.is_open()) {
            std::cerr << "Could not open the file " << filename << " for writing." << std::endl;
            return false;
        }

        // Write every record from the table into the file
        for (int i = 0; i < rows(); ++i) {
            const movie* m = get(i);
            if (m) {
                // Construct the CSV line for the current movie record
                std::ostringstream oss;
                oss << m->id << ",\"" << m->title << "\"," << m->year << ",\"" << m->director << "\"\n";
                
                // Write the constructed line to the file
                file << oss.str();
                
                // Check if writing to the file failed
                if (file.fail()) {
                    std::cerr << "Error writing to the file " << filename << std::endl;
                    file.close();
                    return false;
                }
            }
        }

        // Close the file
        file.close();
        return true;
    }

    /**
     * Removes quotes from a string.
     */
    std::string removeQuotes(const std::string &str) {
        if (str.length() > 1 && str.front() == '"' && str.back() == '"') {
            return str.substr(1, str.length() - 2);
        }
        return str;
    }

    /**
     * Loads the contents of a CSV file into the database table.
     */
    bool AbstractDbTable::loadCSV(const std::string &filename) {
        // Open the file for reading
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Could not open the file " << filename << " for reading." << std::endl;
            return false;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream ss(line);
            movie m;
            std::string id, title, year, director;

            // Parse the id
            if (!std::getline(ss, id, ',')) {
                std::cerr << "Error parsing id in line: " << line << std::endl;
                file.close();
                return false;
            }
            m.id = std::stoul(id);

            // Parse the title
            if (!std::getline(ss, title, ',')) {
                std::cerr << "Error parsing title in line: " << line << std::endl;
                file.close();
                return false;
            }
            title = removeQuotes(title);
            std::strncpy(m.title, title.c_str(), sizeof(m.title) - 1);
            m.title[sizeof(m.title) - 1] = '\0'; // Ensure null termination

            // Parse the year
            if (!std::getline(ss, year, ',')) {
                std::cerr << "Error parsing year in line: " << line << std::endl;
                file.close();
                return false;
            }
            m.year = static_cast<unsigned short>(std::stoi(year));

            // Parse the director
            if (!std::getline(ss, director, ',')) {
                std::cerr << "Error parsing director in line: " << line << std::endl;
                file.close();
                return false;
            }
            director = removeQuotes(director);
            std::strncpy(m.director, director.c_str(), sizeof(m.director) - 1);
            m.director[sizeof(m.director) - 1] = '\0'; // Ensure null termination

            // Add the movie to the database
            if (!add(m)) {
                std::cerr << "Error adding movie to the database for line: " << line << std::endl;
                file.close();
                return false;
            }
        }

        // Close the file
        file.close();
        return true;
    }

} // namespace nwen