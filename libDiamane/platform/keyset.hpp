//
// Created by Tom Hancocks on 23/03/2020.
//

#if !defined(DIAMANE_KEYSET_HPP)
#define DIAMANE_KEYSET_HPP

namespace diamane { namespace platform {

    struct key_set
    {
    private:
        bool m_cursor_down;
        bool m_cursor_up;
        bool m_cursor_left;
        bool m_cursor_right;
        bool m_space;
        bool m_esc;
    public:
        key_set();

        auto capture_keys() -> void;
    };

}};

#endif //DIAMANE_KEYSET_HPP
