#include <iostream>
#include <algorithm>
#include <vector>

namespace Universe {
    template<typename T>
    class universe {
        std::vector<T> m_vec;

    public:

        explicit universe(std::vector<T> vec) {
            m_vec = vec;
        }

        bool is_sorted() {
            return std::is_sorted(m_vec.begin(), m_vec.end(), [](T a, T b) { return a < b; });
        }

        template <typename U>
        friend std::ostream & operator<< (std::ostream &str, const universe<U> & uni);
    };

template <typename U>
std::ostream& operator<< (std::ostream& str, const Universe::universe<U> & uni){
    str << "That's our universe: ";
    for(auto i : uni.m_vec){
        str << i << " ";
    }
    return str;
}

}


template <typename T>
std::vector<Universe::universe<T>> generate_multiverse(std::vector<T>& vec){
    std::vector<Universe::universe<T>> multiverse;

    std::sort(vec.begin(), vec.end(), [](T a, T b){ return a < b;});
    do {
        multiverse.emplace_back(vec);
        //Universe::universe temp(vec);
        //multiverse.push_back(temp);
    } while (std::next_permutation(vec.begin(), vec.end()));
    return move(multiverse);

}

//https://wiki.c2.com/?QuantumBogoSort
template <typename T>
Universe::universe<T> quantum_bogo_sort(std::vector<T>& vec){
    // First step. Divide into n! different universes (roughly, we don't create copies, so n is the # of set of elements).
    // Of course, it would happen simultaneously in a quantum environment.
    // Unfortunately, we'll have to do it the ol' fashioned way.
    std::vector<Universe::universe<T>> multiverse = generate_multiverse(vec);

    // Second step. Destroy every universe, that is not sorted.
    // Again, we're limited here by the fact, that we're using conventional computer

    std::cout << "We start with " << multiverse.size() << " universes\n";

    auto it = std::remove_if(multiverse.begin(), multiverse.end(), [](Universe::universe<T> uni){ return !uni.is_sorted();});
    multiverse.erase(it, multiverse.end());

    std::cout << "We're left with " << multiverse.size() << " universe. That's because we didn't create any copies.\n";
    //Third step. All remaining universes are sorted, so we'll just return the first one

    return *multiverse.begin();

}



int main() {
    std::cout << "Enter numbers count. For n > 10 performance might worsen significantly." << std::endl;
    int n;
    std::cin >> n;
    std::cout << "Enter "<< n << " numbers" << std::endl;
    std::vector<int> vec;
    std::string val;
    for(int i=0; i< n; i++){
        std::string num;
        std::cin >> num;
        vec.push_back( std::stoi(num));
    }

    std::cout << quantum_bogo_sort<int>(vec);
}