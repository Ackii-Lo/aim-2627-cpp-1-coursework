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

// Assessment 01 Q6; see 题面.pdf.
namespace aim::q6 {
struct Target { int id; int x; int y; int hp; bool visible; };

// BEGIN IMPLEMENTATION
// aim-cpp-cw-known
int select_target(const std::vector<Target>& targets, int max_range) {
    if(max_range<0)return -1;
    long long m=max_range;
    long long limit=m*m;
    int best_id = -1;
    long long best_d2 = 0;
    int best_hp=0;
    for(const Target&t: targets){
        if(!t.visible || t.hp<=0){
            continue;
        }
        long long dx=t.x;
        long long dy=t.y;
        long long d2=dx*dx+dy*dy;
        if(d2>limit){
            continue;
        }
        bool better =false;
        if (best_id==-1){
            better=true;
        }else if(t.hp<best_hp){
            better=true;
        }else if(t.hp==best_hp){
            if (d2<best_d2){
                better=true;
            }else if(d2==best_d2&&t.id<best_id){
                better=true;
            }
            
        }
        if(better){
            best_id=t.id;
            best_hp=t.hp;
            best_d2=d2;
        }

    }
    return best_id;
}
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::q6;
int main() {
    try {
        { CHECK(select_target({{7,3,4,20,true},{2,0,5,20,true}},5)==2); }
        { CHECK(select_target({},5)==-1); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
