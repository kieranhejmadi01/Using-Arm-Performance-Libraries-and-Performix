#include <iostream>
#include <optional>

using namespace std;

struct Foo{
int x;
};

std::optional<Foo> bar(bool flag){
    if(flag){
        return Foo{5};
    } else{
        return std::nullopt;
    }
}
int main(){

    auto ans2 = bar(false);
    auto ans = bar(true);

    std::cout << ans.has_value() << ans2.has_value() << std::endl;

    return 0;
}