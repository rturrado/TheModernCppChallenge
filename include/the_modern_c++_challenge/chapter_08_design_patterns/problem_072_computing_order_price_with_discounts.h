#pragma once

#include "rtc/pretty_print.h"

#include "fmt/ostream.h"

#include <memory>  // shared_ptr
#include <ostream>
#include <sstream>  // ostringstream
#include <vector>

using namespace rtc::pretty_print;


namespace tmcppc::store {
    // Discount
    //
    struct discount {
        virtual ~discount() = default;

        [[nodiscard]] virtual float percentage(size_t, float) const noexcept = 0;

        virtual void print(std::ostream& os, const indentation& indentation) const noexcept = 0;
    };

    inline void print(
        std::ostream& os,
        const std::vector<std::shared_ptr<discount>>& discounts,
        const indentation& indentation = {}) {

        if (discounts.empty()) {
            fmt::print(os, "{}discounts : []", indentation);
        } else {
            fmt::print(os, "{}discounts : [\n", indentation);
            bool first{ true };
            for (auto&& discount : discounts) {
                fmt::print(os, "{}", first ? "" : ",\n");
                discount->print(os, indentation + 1);
                first = false;
            }
            fmt::print(os, "\n{}]", indentation);
        }
    }

    inline std::ostream& operator<<(std::ostream& os, const tmcppc::store::discount& d) {
        d.print(os, indentation{});
        return os;
    }


    // Article fixed discount
    //
    struct article_fixed_discount : public discount {
        explicit article_fixed_discount(float p)
            : percentage_{ p }
        {}

        void print(std::ostream& os, const indentation& indentation) const noexcept override {
            fmt::print(os, "{}article_fixed_discount(percentage : {})", indentation, percentage_);
        }

    protected:
        [[nodiscard]] float percentage(size_t, float) const noexcept override {
            return percentage_;
        }

    private:
        article_fixed_discount() = default;

        float percentage_{};
    };


    // Order line volume discount
    //
    struct order_line_volume_discount : public discount {
        order_line_volume_discount(float p, size_t q)
            : percentage_{ p }
            , minimum_article_quantity_{ q }
        {}

        void print(std::ostream& os, const indentation& indentation) const noexcept override {
            fmt::print(os, "{}order_line_volume_discount(percentage : {}, minimum_article_quantity : {})",
                indentation, percentage_, minimum_article_quantity_);
        }

    protected:
        [[nodiscard]] float percentage(size_t article_quantity, float) const noexcept override {
            return (article_quantity >= minimum_article_quantity_) ? percentage_ : 0;
        }

    private:
        order_line_volume_discount() = default;

        float percentage_{};
        size_t minimum_article_quantity_{};
    };


    // Order line price discount
    //
    struct order_line_price_discount : public discount {
    public:
        order_line_price_discount(float p, float mtap) : percentage_{ p }, minimum_total_article_price_{ mtap } {}

        void print(std::ostream& os, const indentation& indentation ) const noexcept override {
            fmt::print(os, "{}order_line_price_discount(percentage : {}, minimum_total_article_price : {})",
                indentation, percentage_, minimum_total_article_price_);
        }

    protected:
        [[nodiscard]] float percentage(size_t article_quantity, float article_price) const noexcept override {
            return (static_cast<float>(article_quantity) * article_price > minimum_total_article_price_) ? percentage_ : 0;
        }

    private:
        order_line_price_discount() = default;

        float percentage_{};
        float minimum_total_article_price_{};
    };


    // Order price discount
    //
    struct order_price_discount : public discount {
    public:
        order_price_discount(float p, float mtop) : percentage_{ p }, minimum_total_order_price_{ mtop } {}

        void print(std::ostream& os, const indentation& indentation) const noexcept override {
            fmt::print(os, "{}order_price_discount(percentage : {}, minimum_total_order_price : {})",
                indentation, percentage_, minimum_total_order_price_);
        }

    protected:
        [[nodiscard]] float percentage(size_t, float order_price) const noexcept override {
            return (order_price > minimum_total_order_price_) ? percentage_ : 0;
        }

    private:
        order_price_discount() = default;

        float percentage_{};
        float minimum_total_order_price_{};
    };


    // Article
    //
    struct article_t {
        size_t id{};
        float price{};
        std::vector<std::shared_ptr<discount>> discounts{};

        void print(std::ostream& os, const indentation& indentation) const noexcept {
            fmt::print(os, "{}article(\n", indentation);
            fmt::print(os, "{}id : {},\n", indentation + 1, id);
            fmt::print(os, "{}price : {},\n", indentation + 1, price);
            tmcppc::store::print(os, discounts, indentation + 1);
            fmt::print(os, "\n{})", indentation);
        }
    };

    inline void print(std::ostream& os, const std::vector<std::shared_ptr<article_t>>& articles, const indentation& indentation) {
        bool first{ true };
        for (auto&& article : articles) {
            fmt::print(os, "{}", first ? "" : ",\n");
            article->print(os, indentation);
            first = false;
        }
    }

    inline std::ostream& operator<<(std::ostream& os, const tmcppc::store::article_t& a) {
        a.print(os, indentation{});
        return os;
    }


    // Store
    //
    struct store {
        std::vector<std::shared_ptr<article_t>> articles{};

        void print(std::ostream& os, const indentation& indentation) const noexcept {
            fmt::print(os, "{}store[\n", indentation);
            tmcppc::store::print(os, articles, indentation + 1);
            fmt::print(os, "\n{}]", indentation);
        }
    };

    inline std::ostream& operator<<(std::ostream& os, const store& s) {
        s.print(os, indentation{});
        return os;
    }


    // Customer
    //
    struct customer_t {
        size_t id{};
        std::vector<std::shared_ptr<discount>> discounts{};

        void print(std::ostream& os, const indentation& indentation) const noexcept {
            fmt::print(os, "{}customer(\n", indentation);
            fmt::print(os, "{}id : {},\n", indentation + 1, id);
            tmcppc::store::print(os, discounts, indentation + 1);
            fmt::print(os, "\n{})", indentation);
        }
    };

    inline std::ostream& operator<<(std::ostream& os, const customer_t& c) {
        c.print(os, indentation{});
        return os;
    }


    // Order line
    //
    struct order_line_t {
        std::shared_ptr<article_t> article{};
        size_t quantity{};
        std::vector<std::shared_ptr<discount>> discounts{};

        void print(std::ostream& os, const indentation& indentation) const noexcept {
            fmt::print(os, "{}order_line(\n", indentation);
            article->print(os, indentation + 1);
            fmt::print(os, ",\n");
            fmt::print(os, "{}quantity : {},\n", indentation + 1, quantity);
            tmcppc::store::print(os, discounts, indentation + 1);
            fmt::print(os, "\n{})", indentation);
        }
    };

    inline std::ostream& operator<<(std::ostream& os, const order_line_t& order_line) {
        order_line.print(os, indentation{});
        return os;
    }

    inline void print(std::ostream& os, const std::vector<order_line_t>& order_lines, const indentation& indentation) {
        if (order_lines.empty()) {
            fmt::print(os, "{}order_lines : []", indentation);
        } else {
            fmt::print(os, "{}order_lines : [\n", indentation);
            bool first{ true };
            for (auto&& order_line : order_lines) {
                fmt::print(os, "{}", first ? "" : ",\n");
                order_line.print(os, indentation + 1);
                first = false;
            }
            fmt::print(os, "\n{}]", indentation);
        }
    }


    // Order
    //
    struct order_t {
        size_t id{};
        std::vector<order_line_t> order_lines{};
        std::shared_ptr<customer_t> customer{};
        std::vector<std::shared_ptr<discount>> discounts{};

        void print(std::ostream& os, const indentation& indentation) const noexcept {
            fmt::print(os, "{}order(\n", indentation);
            fmt::print(os, "{}id : {},\n", indentation + 1, id);
            tmcppc::store::print(os, order_lines, indentation + 1);
            fmt::print(os, ",\n");
            customer->print(os, indentation + 1);
            fmt::print(os, ",\n");
            tmcppc::store::print(os, discounts, indentation + 1);
            fmt::print(os, "\n{})", indentation);
        }
    };

    inline std::ostream& operator<<(std::ostream& os, const order_t& order) {
        order.print(os, indentation{});
        return os;
    }


    // Price calculator
    //
    struct price_calculator {
        virtual ~price_calculator() = default;

        [[nodiscard]] virtual float calculate(const order_t& order) const noexcept = 0;
    };


    // Cumulative price calculator
    //
    struct cumulative_price_calculator : public price_calculator {
        [[nodiscard]] float calculate(const order_t& order) const noexcept override {
            float ret{};

            for (auto&& order_line : order.order_lines) {
                auto article{ order_line.article };
                auto price{ article->price };
                auto quantity{ order_line.quantity };
                auto order_line_price{ price * static_cast<float>(quantity) };

                float discount_percentages{};
                for (auto&& article_discount : article->discounts) {
                    discount_percentages += article_discount->percentage(quantity, price);
                }
                for (auto&& order_line_discount : order_line.discounts) {
                    discount_percentages += order_line_discount->percentage(quantity, price);
                }
                order_line_price *= (1.0f - discount_percentages);

                ret += order_line_price;
            }

            float discount_percentages{};
            for (auto&& customer_discount : order.customer->discounts) {
                discount_percentages += customer_discount->percentage(0, ret);
            }
            for (auto&& order_discount : order.discounts) {
                discount_percentages += order_discount->percentage(0, ret);
            }
            ret *= (1.0f - discount_percentages);

            return ret;
        }
    };


    // Non cumulative price calculator
    //
    struct non_cumulative_price_calculator : public price_calculator {
        [[nodiscard]] float calculate(const order_t& order) const noexcept override {
            float ret{};
            float discountable_order_price{};

            for (auto&& order_line : order.order_lines) {
                auto article{ order_line.article };
                auto price{ article->price };
                auto quantity{ order_line.quantity };
                auto order_line_price{ price * static_cast<float>(quantity) };

                float discount_percentages{};
                for (auto&& article_discount : article->discounts) {
                    discount_percentages += article_discount->percentage(quantity, price);
                }
                for (auto&& order_line_discount : order_line.discounts) {
                    discount_percentages += order_line_discount->percentage(quantity, price);
                }
                order_line_price *= (1.0f - discount_percentages);

                ret += order_line_price;

                if (article->discounts.empty() and order_line.discounts.empty()) {
                    discountable_order_price += order_line_price;
                }
            }

            if (discountable_order_price != 0) {
                float discount_percentages{};
                for (auto&& customer_discount : order.customer->discounts) {
                    discount_percentages += customer_discount->percentage(0, discountable_order_price);
                }
                for (auto&& order_discount : order.discounts) {
                    discount_percentages += order_discount->percentage(0, discountable_order_price);
                }
                ret *= (1.0f - discount_percentages);
            }

            return ret;
        }
    };
}  // namespace tmcppc::store


template <>
struct fmt::formatter<tmcppc::store::discount> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::store::discount& d, FormatContext& ctx) const -> decltype(ctx.out()) {
        std::ostringstream oss{};
        d.print(oss, indentation{});
        return fmt::format_to(ctx.out(), "{}", oss.str());
    }
};

template <>
struct fmt::formatter<tmcppc::store::article_t> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::store::article_t& a, FormatContext& ctx) const -> decltype(ctx.out()) {
        std::ostringstream oss{};
        a.print(oss, indentation{});
        return fmt::format_to(ctx.out(), "{}", oss.str());
    }
};

template <>
struct fmt::formatter<tmcppc::store::store> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::store::store& s, FormatContext& ctx) const -> decltype(ctx.out()) {
        std::ostringstream oss{};
        s.print(oss, indentation{});
        return fmt::format_to(ctx.out(), "{}", oss.str());
    }
};

template <>
struct fmt::formatter<tmcppc::store::customer_t> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::store::customer_t& c, FormatContext& ctx) const -> decltype(ctx.out()) {
        std::ostringstream oss{};
        c.print(oss, indentation{});
        return fmt::format_to(ctx.out(), "{}", oss.str());
    }
};

template <>
struct fmt::formatter<tmcppc::store::order_line_t> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::store::order_line_t& order_line, FormatContext& ctx) const -> decltype(ctx.out()) {
        std::ostringstream oss{};
        order_line.print(oss, indentation{});
        return fmt::format_to(ctx.out(), "{}", oss.str());
    }
};

template <>
struct fmt::formatter<tmcppc::store::order_t> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::store::order_t& order, FormatContext& ctx) const -> decltype(ctx.out()) {
        std::ostringstream oss{};
        order.print(oss, indentation{});
        return fmt::format_to(ctx.out(), "{}", oss.str());
    }
};


void problem_72_main(std::ostream& os);
void problem_72_main();
