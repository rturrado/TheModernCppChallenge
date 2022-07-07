#pragma once

#include "doc.h"
#include "layouter.h"

#include "PDFWriter/AbstractContentContext.h"

#include <cmath>  // max
#include <string>
#include <utility>  // pair


namespace tmcppc::pdf {
    class image_list_layouter : public layouter {
        using ImageOptions = AbstractContentContext::ImageOptions;

    public:
        [[nodiscard]] virtual image_control position_image(doc* doc, double image_width, double image_height) override {
            auto [scaled_image_width, scaled_image_height] = scale_image_to_fit_page(image_width, image_height);

            if (not image_fits_in_current_page(scaled_image_height)) {
                doc->start_page(page_width_, page_height_);
                reset_cursor();
            }

            auto scaled_image_y{ current_y_ - scaled_image_height - get_current_image_spacing() };
            auto image_options{ create_image_options_for_scaled_image(scaled_image_width, scaled_image_height) };
            reset_cursor(scaled_image_y);

            return image_control{ margin_left_, scaled_image_y, image_options };
        }

        [[nodiscard]] virtual line_control position_line() override { return {}; }
        [[nodiscard]] virtual text_control position_text(doc*, const std::string&, bool, const text_alignment&) override { return {}; }
        [[nodiscard]] virtual text_control position_title(doc*, const std::string&, const text_alignment&) override { return {}; }

    private:
        [[nodiscard]] double get_current_image_spacing() {
            return equals(current_y_, page_height_ - margin_top_) ? 0 : image_spacing_;
        }

        [[nodiscard]] bool image_fits_in_current_page(double image_height) {
            return less_than(image_height + get_current_image_spacing(), current_y_ - margin_bottom_);
        }

        [[nodiscard]] std::pair<double, double> scale_image_to_fit_page(double image_width, double image_height) {
            auto ratio{ 1.0 };
            auto width_ratio{ image_width / page_width_available_ };
            auto height_ratio{ image_height / page_height_available_ };
            if (less_than(1.0, width_ratio) or less_than(1.0, height_ratio)) {
                ratio = std::max(width_ratio, height_ratio);
            }
            return std::pair<double, double>{ image_width / ratio, image_height / ratio };
        }

        [[nodiscard]] ImageOptions create_image_options_for_scaled_image(double scaled_image_width, double scaled_image_height) {
            ImageOptions image_options{};
            image_options.transformationMethod = AbstractContentContext::eFit;
            image_options.boundingBoxWidth = scaled_image_width;
            image_options.boundingBoxHeight = scaled_image_height;
            image_options.fitProportional = true;
            return image_options;
        }
    };
}  // namespace tmcppc::pdf
