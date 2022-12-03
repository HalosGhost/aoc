#include "main.hxx"

signed
main () {

    auto lines = file_lines("input");

    uint64_t duplicate_priorities {0};
    for ( size_t i = 0; i < lines.size(); ++i ) {
        const auto& line = lines[i];
        duplicate_priorities += priority(compartment_duplicate(line));
    }

    std::cout << "part 1: " << duplicate_priorities << std::endl;

    uint64_t badge_priorities {0};
    for ( size_t i = 0; i < lines.size(); i += 3 ) {
        std::vector<std::string> group {};
        group.reserve(3);
        group.push_back(lines[i]);
        group.push_back(lines[i + 1]);
        group.push_back(lines[i + 2]);

        badge_priorities += priority(badge(group));
    }

    std::cout << "part 2: " << badge_priorities << std::endl;

    return 0;
}

char
badge (const std::vector<std::string>& sacks) {

    std::unordered_set<char> fst {sacks[0].begin(), sacks[0].end()};
    std::unordered_set<char> snd {sacks[1].begin(), sacks[1].end()};
    std::unordered_set<char> trd {sacks[2].begin(), sacks[2].end()};

    std::vector<char> sortable_fst {fst.begin(), fst.end()};
    std::vector<char> sortable_snd {snd.begin(), snd.end()};
    std::vector<char> sortable_trd {trd.begin(), trd.end()};

    std::sort(sortable_fst.begin(), sortable_fst.end());
    std::sort(sortable_snd.begin(), sortable_snd.end());
    std::sort(sortable_trd.begin(), sortable_trd.end());

    std::vector<char> first_common {};
    std::set_intersection(sortable_fst.begin(), sortable_fst.end(),
                          sortable_snd.begin(), sortable_snd.end(),
                          std::back_inserter(first_common));

    std::vector<char> second_common {};
    std::set_intersection(first_common.begin(), first_common.end(),
                          sortable_trd.begin(), sortable_trd.end(),
                          std::back_inserter(second_common));

    return second_common[0];
}

char
compartment_duplicate (const std::string& sack) {

    std::unordered_set<char> fst {};
    fst.reserve(sack.size() / 2);
    std::unordered_set<char> snd {};
    snd.reserve(sack.size() / 2);

    for ( size_t c = 0, sz = sack.size(); c < sz; ++c ) {
        (c < sz / 2 ? fst : snd).insert(sack[c]);
    }

    std::vector<char> sortable_fst {fst.begin(), fst.end()};
    std::vector<char> sortable_snd {snd.begin(), snd.end()};

    std::sort(sortable_fst.begin(), sortable_fst.end());
    std::sort(sortable_snd.begin(), sortable_snd.end());

    std::vector<char> duplicate {};
    std::set_intersection(sortable_fst.begin(), sortable_fst.end(),
                          sortable_snd.begin(), sortable_snd.end(),
                          std::back_inserter(duplicate));

    return duplicate[0];
}

uint64_t
priority (char item) {

    if ( std::islower(static_cast<unsigned char>(item)) ) {
        return item - 'a' + 1;
    } else {
        return item - 'A' + 27;
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
