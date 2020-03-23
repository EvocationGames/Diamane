//
// Created by Tom Hancocks on 23/03/2020.
//

#if !defined(DIAMANE_FILESYSTEM_HPP)
#define DIAMANE_FILESYSTEM_HPP

#include <string>
#include <vector>
#include "libDiamane/util/hints.hpp"

namespace diamane { namespace platform {

    class filesystem
    {
    public:
        struct path
        {
        private:
            std::vector<std::string> m_components;

            __platform_specific static auto get_components_of_path(const std::string path) -> std::vector<std::string>;
            __platform_specific static auto construct_path_string(const std::vector<std::string> components) -> std::string;

        public:
            path(const std::string filepath);
            path(const path &base, const std::string component);

            auto to_str() const -> std::string;

            auto append_component(const std::string component) -> void;
            auto remove_last_component() -> void;
        };

    private:
        filesystem();

    public:
        filesystem(const filesystem&) = delete;
        filesystem &operator=(const filesystem&) = delete;
        filesystem(filesystem&&) = delete;
        filesystem &operator=(filesystem &&) = delete;

        static auto shared() -> filesystem&;

        __platform_specific static auto application_directory() -> path;
        __platform_specific static auto user_documents_directory() -> path;
        __platform_specific static auto user_directory() -> path;

        __platform_specific auto contents_of_directory(const path dir_path) -> std::vector<path>;
    };

}};

#endif //DIAMANE_FILESYSTEM_HPP
