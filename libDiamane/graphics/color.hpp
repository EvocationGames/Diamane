//
// Created by Tom Hancocks on 24/02/2020.
//

#if !defined(DIAMANE_COLOR_HPP)
#define DIAMANE_COLOR_HPP

namespace diamane { namespace gl {

    struct color
    {
    private:
        float m_red;
        float m_green;
        float m_blue;
        float m_alpha;

    public:
        color(float w, float a = 1.0) : m_red(w), m_green(w), m_blue(w), m_alpha(a) {};
        color(float r, float g, float b, float a = 1.0) : m_red(r), m_green(g), m_blue(b), m_alpha(a) {}

        auto red() const -> float { return m_red; };
        auto green() const -> float { return m_green; };
        auto blue() const -> float { return m_blue; };
        auto alpha() const -> float { return m_alpha; };

        auto rgb_value() const -> uint32_t
        {
            auto r = static_cast<uint8_t>(m_red * 255.0);
            auto g = static_cast<uint8_t>(m_green * 255.0);
            auto b = static_cast<uint8_t>(m_blue * 255.0);
            auto a = static_cast<uint8_t>(m_alpha * 255.0);

            return (a << 24) | (b << 16) | (g << 8) | r;
        }

        static auto whiteColor() -> color { return color(1.0); };
        static auto blackColor() -> color { return color(0.0); };
        static auto redColor() -> color { return color(1.0, 0.0, 0.0); };
        static auto orangeColor() -> color { return color(1.0, 0.5, 0.0); };
        static auto yellowColor() -> color { return color(1.0, 1.0, 0.0); };
        static auto greenColor() -> color { return color(0.0, 1.0, 0.0); };
        static auto cyanColor() -> color { return color(0.0, 1.0, 1.0); };
        static auto blueColor() -> color { return color(0.0, 0.0, 1.0); };
        static auto purpleColor() -> color { return color(1.0, 0.0, 1.0); };
        static auto pinkColor() -> color { return color(1.0, 0.0, 0.5); };
    };

}};

#endif //DIAMANE_COLOR_HPP
