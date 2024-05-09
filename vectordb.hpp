/**
 * vectordb.hpp
 * C++ header file that should contain declaration for
 * - VectorDbTable class
 * 
 * You need to modify this file to declare VectorDbTable class 
 * as specified in the hand-out (Task 2)
 */ 

 namespace nwen {
    class VectorDbTable : public AbstractDbTable {
    private:
        std::vector<movie> database;

    public:
        int rows() const override {
            return database.size();
        }

        const movie* get(int index) const override {
            if (index >= 0 && index < database.size()) {
                return &database[index];
            } else {
                return nullptr;
            }
        }

        void add(const movie& movie) override {
            database.push_back(movie);
        }

        bool update(unsigned long id, const movie& movie) override {
            for (auto& entry : database) {
                if (entry.id == id) {
                    entry = movie;
                    return true;
                }
            }
            return false;
        }
    }
 }

