#include <iostream>
#include <fstream>
#include <random>
#include <memory>

int main(int argc, char **argv){
    if(argc < 2){
        std::cout << "USAGE: ./create_test [output path]\n";
        return 0;
    }
    std::ofstream file;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(-1e9, 1e9);
    auto rng = std::bind(distribution, generator);
    file.open(argv[1]);
    std::cout << "Number of test cases? ";
    int tests; std::cin >> tests;
    std::cout << "Size of matrices? ";
    int n; std::cin >> n;
    file << tests << " " << n << "\n";
    for(int i = 0; i < tests * n; i++){
        for(int j = 0; j < n; j++){
            file << rng() << " ";
        }
        file << "\n";
    }
}