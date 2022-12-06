#include "main.hxx"

signed
main () {

    auto lines = file_lines("input");
    auto stream = lines[0];

    auto start_of_packet = end_of_marker(stream, 4);
    std::cout << "part 1: " << start_of_packet << std::endl;

    auto start_of_message = end_of_marker(stream, 14);
    std::cout << "part 2: " << start_of_message << std::endl;

    return 0;
}

size_t
end_of_marker (const std::string& stream, size_t num_distinct) {

    auto it = stream.begin();
    size_t s {0};

    do {
        std::unordered_set<char> st {it, it + num_distinct};
        if ( st.size() == num_distinct ) {
            return s + num_distinct;
        }
        ++s;
    } while ( ++it != stream.end() );

    return stream.size() + 1;
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
