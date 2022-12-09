#include "main.hxx"

signed
main () {

    auto lines = file_lines("input");
    auto grid = get_grid(lines);

    auto visible = count_visible(grid);
    std::cout << "part 1: " << visible << std::endl;

    std::size_t best_scenic_score {0};
    for ( std::size_t y {1}; y < grid.size() - 1; ++y ) {
        for ( std::size_t x {1}; x < grid[0].size() - 1; ++x ) {
            auto score = scenic_score(grid, y, x);
            if ( score > best_scenic_score ) {
                best_scenic_score = score;
            }
        }
    }
    std::cout << "part 2: " << best_scenic_score << std::endl;

    return 0;
}

std::size_t
scenic_score (const std::vector<std::vector<uint8_t>>& grid, std::size_t y, std::size_t x) {

    auto h = grid.size();
    auto w = grid[0].size();
    auto tree = grid[y][x];

    if ( x == 0 || y == 0 || x == (w - 1) || y == (h - 1) ) {
        return 0;
    }

    std::size_t up {0};
    for ( std::size_t i {y}; i > 0; --i ) {
        ++up;
        if ( grid[i - 1][x] >= tree ) {
            break;
        }
    }
    std::size_t down {0};
    for ( std::size_t i {y + 1}; i < h; ++i ) {
        ++down;
        if ( grid[i][x] >= tree ) {
            break;
        }
    }
    std::size_t left {0};
    for ( std::size_t i {x}; i > 0; --i ) {
        ++left;
        if ( grid[y][i - 1] >= tree ) {
            break;
        }
    }
    std::size_t right {0};
    for ( std::size_t i {x + 1}; i < w; ++i ) {
        ++right;
        if ( grid[y][i] >= tree ) {
            break;
        }
    }

    return up * down * left * right;
}

std::size_t
count_visible (const std::vector<std::vector<uint8_t>>& grid) {

    auto h = grid.size();
    auto w = grid[0].size();

    auto bounding = h * 2 + (w - 2) * 2;

    auto interior {0};
    for ( std::size_t y {1}; y < grid.size() - 1; ++y ) {
        for ( std::size_t x {1}; x < grid[0].size() - 1; ++x ) {
            if ( is_visible(grid, y, x) ) {
                ++interior;
            }
        }
    }

    return bounding + interior;
}

bool
is_visible (const std::vector<std::vector<uint8_t>>& grid, std::size_t y, std::size_t x) {

    auto h = grid.size();
    auto w = grid[0].size();
    auto tree = grid[y][x];

    auto visible = true;
    for ( std::size_t i {0}; i < y; ++i ) {
        visible &= grid[i][x] < tree;
    }
    if ( visible ) { return true; }
    visible = true;
    for ( std::size_t i {y + 1}; i < h; ++i ) {
        visible &= grid[i][x] < tree;
    }
    if ( visible ) { return true; }
    visible = true;
    for ( std::size_t i {0}; i < x; ++i ) {
        visible &= grid[y][i] < tree;
    }
    if ( visible ) { return true; }
    visible = true;
    for ( std::size_t i {x + 1}; i < w; ++i ) {
        visible &= grid[y][i] < tree;
    }

    return visible;
}

std::vector<std::vector<uint8_t>>
get_grid (const std::vector<std::string>& lines) {

    std::vector<std::vector<uint8_t>> grid {};
    grid.reserve(lines.size());
    for ( std::size_t i {0}; i < lines.size(); ++i ) {
        const auto& line = lines[i];
        grid.push_back({});
        grid[i].reserve(line.size());
        for ( char c : line ) {
            grid[i].push_back(c - '0');
        }
    }

    return grid;
}

std::vector<std::string>
file_lines (const std::string& path) {

    std::fstream fs {path};
    if ( !fs.is_open() ) {
        std::cerr << "failed to open " << path << std::endl;
        return {};
    }

    std::vector<std::string> lines{};
    std::string line{};
    while ( std::getline(fs, line) ) {
        lines.emplace_back(line);
    }

    return lines;
}
