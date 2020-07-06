#include <algorithm>
#include <string>
#include <vector>

namespace TIE {
    namespace Vector {

        template<typename T>
        inline bool contains(const std::vector<T>& vector, const T& element) {
            return std::find(vector.begin(), vector.end(), element) != vector.end();
        }

        template<typename T>
        inline void remove(std::vector<T>& vector, const T& element) {
            vector.erase(std::remove(vector.begin(), vector.end(), element), vector.end());
        }
    }
}