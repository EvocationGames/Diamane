//
// Created by Tom Hancocks on 22/02/2020.
//

#if !defined(DIAMANE_APPLICATION_HPP)
#define DIAMANE_APPLICATION_HPP

#include <memory>
#include <functional>
#include "libDiamane/util/hints.hpp"
#include "libDiamane/util/handle.hpp"
#include "libDiamane/ui/menubar.hpp"
#include "libDiamane/platform/keyset.hpp"

namespace diamane { namespace platform {

    class application : public std::enable_shared_from_this<application>
    {
    private:
        handle m_handle;
        key_set m_current_keys;

        __platform_specific static auto acquire_handle() -> handle;

    public:
        application();

        static auto shared() -> std::shared_ptr<application>;

        __platform_specific auto run(std::function<void()> setupFn) -> void;

        __platform_specific auto set_menubar(std::shared_ptr<diamane::ui::menubar> menubar) -> void;

        __platform_specific auto current_key_set() -> key_set;
    };

}};

#endif //DIAMANE_APPLICATION_HPP
