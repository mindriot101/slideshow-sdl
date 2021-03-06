#ifndef OPTIONAL_H_
#define OPTIONAL_H_

#include <stdexcept>

template <typename T>
struct Option {
    T value;
    bool has_value;

    static Option<T> None() {
        Option option;
        option.has_value = false;
        return option;
    }

    static Option<T> Some(T value) {
        Option option;
        option.value = value;
        option.has_value = true;
        return option;
    }

    bool is_some() const { return has_value; }

    bool is_none() const { return !is_some(); }

    operator bool() const { return is_some(); }

    T val() const {
        if (is_some()) {
            return value;
        }

        throw std::runtime_error("Tried to unwrap a None");
    }
};

#endif // OPTIONAL_H_
