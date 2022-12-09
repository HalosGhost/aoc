#include "main.hxx"

signed
main () {

    auto lines = file_lines("input");

    auto dirs = get_dirs(lines);

    for ( auto& d : dirs ) {
        d.sz += get_size(dirs, d.path_segments);
    }

    std::size_t total_under_100k {0};
    for ( const auto& d : dirs ) {
        if ( d.sz <= 100000 ) {
            total_under_100k += d.sz;
        }
    }

    std::cout << "part 1: " << total_under_100k << std::endl;

    auto used_space = dirs[0].sz;

    std::sort(dirs.begin(), dirs.end(),
        [](const Dir& l, const Dir& r) {
            return l.sz < r.sz;
        }
    );

    std::size_t free_space {70000000 - used_space};
    std::size_t needed {30000000};
    std::size_t to_free {needed - free_space};

    std::size_t smallest_viable {};
    for ( const auto& d : dirs ) {
        if ( d.sz >= to_free ) {
            smallest_viable = d.sz;
            break;
        }
    }

    std::cout << "part 2: " << smallest_viable << std::endl;

    return 0;
}

std::size_t
get_size (const std::vector<Dir>& dirs, const std::vector<std::string>& segments) {

    std::size_t sz {0};
    for ( const auto& d : dirs ) {
        if ( is_prefix_of(segments, d.path_segments) ) {
            sz += d.sz;
        }
    }

    return sz;
}

bool
is_prefix_of (const std::vector<std::string>& lhs, const std::vector<std::string>& rhs) {

    if ( lhs.size() >= rhs.size() ) {
        return false;
    }

    for ( std::size_t i {0}; i < lhs.size(); ++i ) {
        if ( lhs[i] != rhs[i] ) {
            return false;
        }
    }

    return true;
}

std::vector<Dir>
get_dirs (const std::vector<std::string>& lines) {

    std::vector<std::string> cwd {};
    std::vector<Dir> dirs {};
    Dir rt {{"/"}, 0};
    dirs.push_back(rt);
    for ( const auto& line : lines ) {
        std::stringstream s {line};
        std::string token {};
        std::size_t sz {};

        switch ( line[0] ) {
            case '$':
                s >> token >> token;

                if ( token == "ls" ) { continue; }

                // token == "cd"
                s >> token;
                if ( token == ".." ) {
                    cwd.pop_back();
                } else {
                    cwd.push_back(token);
                } break;

            case 'd': {
                s >> token >> token;
                Dir d {cwd, 0};
                d.path_segments.push_back(token);
                dirs.push_back(d);
                continue;
            }

            default: {
                auto it = std::find_if(dirs.begin(), dirs.end(),
                    [&cwd](const Dir& d){
                        return d.path_segments == cwd;
                    }
                );
                if ( it != dirs.end() ) {
                    s >> sz;
                    it->sz += sz;
                }
            }
        }
    }

    return dirs;
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
