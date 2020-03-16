//
// Created by Tom Hancocks on 22/02/2020.
//

#if !defined(DIAMANE_HANDLE_HPP)
#define DIAMANE_HANDLE_HPP

#include <type_traits>
#include <functional>

namespace diamane
{

    struct handle
    {
    private:
        const void *m_ptr { nullptr };
    public:

        template<typename T, typename std::enable_if<std::is_pointer<T>::value>::type* = nullptr>
        handle(T value) {
            m_ptr = reinterpret_cast<const void *>(value);
        };

        template<typename T, typename std::enable_if<std::is_pointer<T>::value>::type* = nullptr>
        auto get() -> T { return reinterpret_cast<T>(m_ptr); };

    };

    template<typename T, typename std::enable_if<std::is_pointer<T>::value>::type* = nullptr>
    auto make_handle(T value) -> handle { return handle(value); };

};

#endif //DIAMANE_HANDLE_HPP
