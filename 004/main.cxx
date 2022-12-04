#include "main.hxx"

signed
main () {

    auto lines = file_lines("input");

    uint64_t fully_contained {0};
    uint64_t overlaps {0};
    for ( const auto& line : lines ) {
        std::stringstream s{line};

        uint64_t l;
        uint64_t r;
        char sep;

        s >> l >> sep >> r;
        Interval fst {l, r};

        s >> sep >> l >> sep >> r;
        Interval snd {l, r};

        if ( ival_contains(fst, snd) || ival_contains(snd, fst) ) {
            ++fully_contained;
        }

        if ( ival_overlaps(fst, snd) ) {
            ++overlaps;
        }
    }

    std::cout << "part 1: " << fully_contained << std::endl;
    std::cout << "part 2: " << overlaps << std::endl;

    return 0;
}

bool
ival_overlaps (const Interval& l, const Interval& r) {

    return !(l.upper < r.lower) && !(l.lower > r.upper);
}

bool
ival_contains (const Interval& l, const Interval& r) {

    return l.lower <= r.lower && l.upper >= r.upper;
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
