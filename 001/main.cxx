#include "main.hxx"

signed
main () {

    auto lines = file_lines("input");
    std::vector<uint64_t> calories{};
    calories.reserve(lines.size());

    uint64_t aggregation {0};
    for ( const auto& line : lines ) {
        if ( line == "" ) {
            calories.push_back(aggregation);
            aggregation = 0;
            continue;
        }

        aggregation += std::stoull(line);
    }

    std::sort(calories.begin(), calories.end(), std::greater<uint64_t>());

    std::cout << "part 1: " << calories[0] << std::endl;

    uint64_t top_three {0};
    for ( size_t i = 0; i < 3; ++i ) {
        top_three += calories[i];
    }

    std::cout << "part 2: " << top_three << std::endl;

    return 0;
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
