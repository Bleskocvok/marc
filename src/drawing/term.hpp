#pragma once

#include <drawing/draw.hpp>

#include <ostream>

struct TermDrawer : ImageDrawer {

    void operator()(const Grid& grid, const ImageConfig& config) override {
        Rgb color;

        std::ostream& out = std::cout;

        size_t max_occupancy = config.adjust_colors ? grid.max_occupancy() : grid.block_capacity();

        for (size_t row = 0; row < grid.rows(); ++row) {
            for (size_t col = 0; col < grid.cols(); ++col) {

                float density = grid.count_at(row, col)/(float)max_occupancy;
                color = config.color_palette.sample_color(density);

                // Use ANSI escape sequence to set the RGB color of the background.
                // Most modern terminals should support this.
                out << "\033[48;2;"
                    << unsigned(color.red)   << ";"
                    << unsigned(color.green) << ";"
                    << unsigned(color.blue)  << "m";

                out << "  ";

                // Reset color back to neutral.
                out << "\e[0m";
            }
            out << "\n";
        }
    }
};

