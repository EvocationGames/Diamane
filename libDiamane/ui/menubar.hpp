//
// Created by Tom Hancocks on 23/02/2020.
//

#if !defined(DIAMANE_MENUBAR_HPP)
#define DIAMANE_MENUBAR_HPP

#include <string>
#include <memory>
#include "libDiamane/util/handle.hpp"
#include "libDiamane/util/hints.hpp"

namespace diamane { namespace ui {

    class menubar
    {
    private:
        diamane::handle m_handle;

        __platform_specific static auto acquire_handle() -> handle;
    public:
        menubar();

        static auto create() -> std::shared_ptr<menubar>;

        auto handle() -> diamane::handle;
    };

}};

#endif //DIAMANE_MENUBAR_HPP
