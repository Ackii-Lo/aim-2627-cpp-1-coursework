#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <limits>
#include <memory>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

// Assessment 01 Q2; see 题面.pdf.
namespace aim::q2 {
struct LabelEdit { std::string from; std::string to; };

// BEGIN IMPLEMENTATION
// aim-cpp-cw-known
std::string edit_labels(std::string labels, const std::vector<LabelEdit>& edits) {
    for (std::size_t i = 0; i < edits.size(); ++i) {
        const std::string& from = edits[i].from;
        const std::string& to = edits[i].to;

        if (from.empty()) {
            if (to.empty()) {
                continue;
            }
            if (labels.empty()) {
                labels = to;
            } else {
                labels += ',';
                labels += to;
            }
            continue;
        }

        std::size_t cur = 0;
        while (true) {
            std::size_t comma = labels.find(',', cur);
            std::size_t end = (comma == std::string::npos) ? labels.size() : comma;

            if (labels.compare(cur, end - cur, from) == 0) {
                std::size_t seglen = end - cur;
                if (!to.empty()) {
                    labels.replace(cur, seglen, to);
                } else if (comma != std::string::npos) {
                    labels.erase(cur, seglen + 1);
                } else if (cur > 0) {
                    labels.erase(cur - 1, seglen + 1);
                } else {
                    labels.erase(cur, seglen);
                }
                break;
            }

            if (comma == std::string::npos) {
                break;
            }
            cur = comma + 1;
        }
    }
    return labels;
}
// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::q2;
int main() {
    try {
        { CHECK(edit_labels("cam,imu,radar",{{"imu","gyro"},{"cam",""},{"","lidar"}})=="gyro,radar,lidar"); }
        { CHECK(edit_labels("cam,cam2,cam",{{"cam","camera"},{"cam",""}})=="camera,cam2"); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
