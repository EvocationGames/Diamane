//
// Created by Tom Hancocks on 24/02/2020.
//

#if !defined(DIAMANE_TEXTURE_HPP)
#define DIAMANE_TEXTURE_HPP

#include <memory>
#include <vector>
#include <functional>
#include "libDiamane/util/geometry.hpp"
#include "libDiamane/graphics/graphics.hpp"

namespace diamane { namespace gl {

    class texture: public std::enable_shared_from_this<texture>
    {
    private:
        std::vector<uint32_t> m_data;
        diamane::size m_size;
        int64_t m_handle { -1 };
        std::vector<diamane::rect> m_uv_map;

    public:

        texture(std::vector<uint32_t> raw_data, diamane::size size);
        static auto blank(diamane::size size) -> std::shared_ptr<texture>;
        static auto from_raw(std::vector<uint32_t> raw_data, diamane::size size) -> std::shared_ptr<texture>;

        auto size() const -> diamane::size;
        auto raw() const -> const void *;

        auto handle() -> int64_t;
        auto _set_handle(int64_t handle) -> void;

        auto is_registered() const -> bool;
        auto register_texture() -> void;

        auto uv(int index) const -> diamane::rect;
        auto setup_single_uv() -> void;

        auto draw(diamane::point point, int uv_index = 0) -> void;
        auto draw(diamane::rect rect, int uv_index = 0) -> void;

        auto clear_uvs() -> void;
        auto add_uv(const diamane::rect& r) -> int;

        auto paint(std::function<void(std::shared_ptr<diamane::gl::graphics>)> fn) -> void;

    };

}};

#endif //DIAMANE_TEXTURE_HPP
