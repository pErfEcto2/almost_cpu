#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <iterator>
#include <stdexcept>

#define N 32

/**
 * @brief A simple vector data structure implementation.
 *
 * @tparam T The type of elements stored in the vector.
 */
template <class T> class Vector {
private:
    int index;        /**< Current index of the vector(aka size). */
    int length;       /**< Capacity of the vector. */
    T *arr;           /**< Array used to store the elements. */

public:
    /**
   * @brief Iterator for the Vector class.
   */
    struct Iterator {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T *;
        using reference = T &;

        /**
     * @brief Constructs an iterator with the given pointer.
     *
     * @param ptr Pointer to an element in the vector.
     */
        Iterator(pointer ptr) : m_ptr{ptr} {}

        reference operator*() const { return *m_ptr; }
        pointer operator->() { return m_ptr; }

        Iterator &operator++() {
            m_ptr++;
            return *this;
        }
        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        /**
     * @brief Equality comparison operator.
     *
     * @param a Iterator to compare.
     * @param b Iterator to compare.
     */
        friend bool operator==(const Iterator &a, const Iterator &b) {
            return a.m_ptr == b.m_ptr;
        }

        /**
     * @brief Inequality comparison operator.
     *
     * @param a Iterator to compare.
     * @param b Iterator to compare.
     */
        friend bool operator!=(const Iterator &a, const Iterator &b) {
            return a.m_ptr != b.m_ptr;
        }

    private:
        pointer m_ptr;   /**< Pointer to an element in the Vector. */
    };

    /**
   * @brief Constructs an empty Vector with an initial capacity = 32.
   */
    Vector() {
        index = 0;
        length = N;
        arr = new T[length];
    }

    /**
   * @brief Destructor for the Vector class.
   */
    ~Vector() { delete[] arr; }

    /**
   * @brief Adds an element to the end of the Vector.
   *
   * If the Vector's capacity is not enough to hold the new element,
   * the capacity is doubled before adding the element.
   *
   * @param elem The element to be added.
   */
    void push_back(T elem) {
        if (index == length - 1) {
            T *tmp = new T[length];
            for (int i{0}; i < index + 1; i++)
                tmp[i] = arr[i];
            length *= 2;
            delete[] arr;
            arr = new T[length];
            for (int i{0}; i < index + 1; i++)
                arr[i] = tmp[i];
            delete[] tmp;
        }

        arr[index] = elem;
        index++;
    }

    /**
   * @brief Removes all elements from the Vector.
   */
    void clear() { index = 0; }

    /**
   * @brief Accesses the element at the specified index.
   * Throws an exception if the index is out of range.
   *
   * @param i The index of the element to be accessed.
   * @throws std::invalid_argument if the index is out of range.
   */
    T &operator[](int i) {
        if (i < 0 || i >= length)
            throw std::invalid_argument("index out of range");
        return arr[i];
    }

    /**
   * @brief Returns the number of elements in the Vector.
   */
    int size() { return index; }

    /**
   * @brief Returns an iterator pointing to the beginning of the Vector.
   */
    Iterator begin() { return Iterator(arr); }

    /**
   * @brief Returns an iterator pointing to the end of the Vector.
   */
    Iterator end() { return Iterator(arr + index); }

    /**
   * @brief Finds elements in the Vector that match the specified value.
   *
   * This method returns a new Vector containing all elements from the
   * current Vector up to (but not including) the first occurrence of
   * the specified value.
   *
   * @param val The value to search for.
   */
    Vector<T> find(T val) {
        Vector<T> res;
        T *tmp = arr;
        for (T &i : *this) {
            if (i == val)
                break;
            tmp++;
        }

        for (int i{0}; i < index - (tmp - arr); i++)
            res.push_back(tmp[i]);

        return res;
    }
};

#endif // VECTOR_H
