# Simple Database Table Implementation in C++

This project is part of an assignment aimed at implementing a simple database table using C++ programming constructs. The database table, which stores movie records, supports basic operations such as adding, updating, and removing records.

## Features

- **Database Operations**: The implementation supports adding, updating, and removing movie records.
- **Movie Records**: Each record contains an ID, title, year, and director.
- **Vector Storage**: The database is implemented using the `std::vector` container for dynamic array management.
- **CSV Support**: Functions to save the database to a CSV file and load it from a CSV file are provided.

## Technologies Used

- **Language**: C++
- **Libraries**: Standard C++ Library, including `<vector>`, `<algorithm>`, and `<string>`
- **File I/O**: Utilizes C++ file streams for reading and writing CSV files.

## Class Overview

### AbstractDbTable

An abstract class defining the interface for a database table, including pure virtual functions for basic CRUD operations and functions for CSV file operations.

### VectorDbTable

A concrete class that extends `AbstractDbTable` and provides implementations for all virtual functions using a `std::vector` to store movie records.

### Movie Structure

A structure representing a movie record with fields for ID, title, year, and director.

## Usage

1. **Clone the repository**:
    ```sh
    git clone <repository_url>
    ```

2. **Compile the code**:
    ```sh
    g++ -o vectordb vectordb.cpp
    ```

3. **Run the executable**:
    ```sh
    ./vectordb
    ```

4. **Interact with the Database**:
    - Use the member functions of `VectorDbTable` to add, update, and remove movie records.
    - Use the `loadCSV` and `saveCSV` functions to interact with CSV files.

## Example Usage

```cpp
#include "vectordb.hpp"
#include <iostream>

using namespace nwen;

int main() {
    VectorDbTable db;
    
    // Create a new movie
    movie m1 = {1, "The Matrix", 1999, "Lana Wachowski, Lilly Wachowski"};
    db.add(m1);

    // Update the movie
    movie m2 = {1, "The Matrix Reloaded", 2003, "Lana Wachowski, Lilly Wachowski"};
    db.update(1, m2);

    // Save to CSV
    db.saveCSV("movies.csv");

    // Load from CSV
    db.loadCSV("movies.csv");

    // Print the number of rows
    std::cout << "Number of rows: " << db.rows() << std::endl;

    return 0;
}
```
## Acknowledgements

These implementations were developed as part of a project for NWEN241 at Victoria University of Wellington.
