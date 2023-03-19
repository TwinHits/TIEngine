#ifndef VECTOR_UTILS_H
#define VECTOR_UTILS_H

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

        template<typename T>
        inline std::vector<T>& concat(std::vector<T>& vector1, const std::vector<T>& vector2) {
            vector1.insert(vector1.end(), vector2.begin(), vector2.end());
            return vector1;
        }
    }
}

#endif