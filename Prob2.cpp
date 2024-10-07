#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstdint>


//Miller rabin test is used

const int NUM_TESTS = 5;

struct Node {
    uint64_t value; // 64-bit number
    Node* next;
    
    Node(uint64_t val) : value(val), next(nullptr) {}
};

class BigNumber {
private:
    Node* head;

public:
    BigNumber() : head(nullptr) {}

    void insert(uint64_t chunk) {
        Node* newNode = new Node(chunk);
        newNode->next = head;
        head = newNode;
    }

    std::vector<uint64_t> reconstruct() const {
        std::vector<uint64_t> number;
        Node* temp = head;
        while (temp) {
            number.push_back(temp->value);
            temp = temp->next;
        }
        return number;
    }

    uint64_t modExp(uint64_t base, uint64_t exp, uint64_t mod) {
        uint64_t result = 1;
        base = base % mod;
        while (exp > 0) {
            if (exp % 2 == 1) { 
                result = (result * base) % mod;
            }
            exp = exp >> 1;  
            base = (base * base) % mod;
        }
        return result;
    }

    bool millerRabin(uint64_t d, uint64_t n) {
        // Pick a random number in [2, n-2]
        // Corner case for n <= 4 handled elsewhere
        uint64_t a = 2 + rand() % (n - 4);
        uint64_t x = modExp(a, d, n);

        if (x == 1 || x == n - 1)
            return true;

        while (d != n - 1) {
            x = (x * x) % n;
            d *= 2;

            if (x == 1) return false;
            if (x == n - 1) return true;
        }

        return false;
    }

    // Function to check 
    bool isPrime(uint64_t n) {

        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;

        // Find d such that d*2^r = n-1
        uint64_t d = n - 1;
        while (d % 2 == 0)
            d /= 2;

        for (int i = 0; i < NUM_TESTS; i++) {
            if (!millerRabin(d, n)) return false;
        }

        return true;
    }
};

int main() {
    srand(time(0));

    BigNumber bigNum;

    bigNum.insert(1234567890123456789ULL);
    bigNum.insert(9876543210987654321ULL);



    std::vector<uint64_t> fullNumber = bigNum.reconstruct();


    uint64_t smallPrime = 12;
    if (bigNum.isPrime(smallPrime)) {
        std::cout << "The number is prime!" << std::endl;
    } else {
        std::cout << "The number is not prime." << std::endl;
    }

    return 0;
}
