#include "main.hxx"

signed
main () {

    auto lines = file_lines("input");

    uint64_t first_total {0};
    uint64_t second_total {0};

    for ( const auto& line : lines ) {
        std::stringstream s {line};
        char fst;
        char snd;

        s >> fst >> snd;

        auto theirs = parse_shape(fst);
        auto opt1 = parse_shape(snd);
        auto opt2 = strategize(theirs, snd);

        first_total += score(theirs, opt1);
        second_total += score(theirs, opt2);
    }

    std::cout << "part 1: " << first_total << std::endl;
    std::cout << "part 2: " << second_total << std::endl;

    return 0;
}

uint64_t
score (Shape theirs, Shape ours) {

    uint64_t total {0};

    switch ( ours ) {
        case Shape::Rock:     total = 1; break;
        case Shape::Paper:    total = 2; break;
        case Shape::Scissors: total = 3; break;
    }

    total += outcome(theirs, ours);

    return total;
}

uint64_t
outcome (Shape theirs, Shape ours) {

    if ( theirs == ours ) {
        return 3;
    }

    if ( ours == Shape::Rock ) {
        return static_cast<uint64_t>(theirs == Shape::Scissors) * 6;
    } else if ( theirs == Shape::Rock ) {
        return static_cast<uint64_t>(ours != Shape::Scissors) * 6;
    }

    return static_cast<uint64_t>(ours > theirs) * 6;
}

Shape
parse_shape (char c) {

    switch ( c ) {
        case 'A':
        case 'X': return Shape::Rock;

        case 'B':
        case 'Y': return Shape::Paper;

        case 'C':
        case 'Z': return Shape::Scissors;
    }

    __builtin_unreachable();
}

Shape
strategize (Shape theirs, char plan) {

    auto tval = (signed )theirs;
    auto mod = (signed )Shape::Scissors;

    switch ( plan ) {
        case 'X':
            return theirs == Shape::Rock ? Shape::Scissors
                : (Shape )(tval - 1);

        case 'Y': return theirs;

        case 'Z':
            return theirs == Shape::Scissors ? Shape::Rock
                : (Shape )((tval + 1) % (mod + 1));
    }

    __builtin_unreachable();
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
