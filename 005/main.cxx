#include "main.hxx"

signed
main () {

    auto lines = file_lines("input");

    lifo_execute(lines);

    std::cout << "part 1: ";
    for ( const auto& s : stacks ) {
        std::cout << s.top();
    }
    std::cout << std::endl;

    fifo_execute(lines);

    std::cout << "part 2: ";
    for ( const auto& s : stacks ) {
        std::cout << s.top();
    }
    std::cout << std::endl;

    return 0;
}

void
fifo_execute (const std::vector<std::string>& lines) {

    setup_stacks(lines);
    auto it = lines.begin() + stacks.size();
    for ( ; it != lines.end(); ++it ) {
        std::stringstream s {*it};
        size_t count {};
        size_t from {};
        size_t to {};
        std::string sep {};

        std::stack<char> temp {};

        s >> sep >> count >> sep >> from >> sep >> to;
        for ( auto i = 0UL; i < count; ++i ) {
            temp.push(stacks[from - 1].top());
            stacks[from - 1].pop();
        }

        for ( auto i = 0UL; i < count; ++i ) {
            stacks[to - 1].push(temp.top());
            temp.pop();
        }
    }
}

void
lifo_execute (const std::vector<std::string>& lines) {

    setup_stacks(lines);
    auto it = lines.begin() + stacks.size();
    for ( ; it != lines.end(); ++it ) {
        std::stringstream s {*it};
        size_t count {};
        size_t from {};
        size_t to {};
        std::string sep {};

        s >> sep >> count >> sep >> from >> sep >> to;
        for ( auto i = 0UL; i < count; ++i ) {
            auto t = stacks[from - 1].top();
            stacks[from - 1].pop();
            stacks[to - 1].push(t);
        }
    }
}

void
setup_stacks (const std::vector<std::string>& lines) {

    stacks.clear();
    auto it = lines.begin();
    for ( ; *it != ""; ++it ) { // format manually massaged
        auto& line = *it;

        std::stack<char> s {};

        for ( auto c : line ) {
            s.push(c);
        }

        stacks.push_back(s);
    }
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
