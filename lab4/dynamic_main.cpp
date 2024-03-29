#include <dlfcn.h>

#include <array>
#include <iostream>
#include <sstream>
#include <vector>

class MainRoutine {
   private:
    using Function1Ptr = float(*)(float, float);
    using Function2Ptr = char *(*)(long);

    const char *const Function1Name = "Derivative";
    const char *const Function2Name = "Translation";

    Function1Ptr Derivative;
    Function2Ptr Translation;
    size_t currentMode;
    std::array<void *, 2> dls;

    void SwitchMode() {
        currentMode = 1 - currentMode;
        Derivative = reinterpret_cast<Function1Ptr>(
            dlsym(dls[currentMode], Function1Name));
        Translation = reinterpret_cast<Function2Ptr>(
            dlsym(dls[currentMode], Function2Name));
    }

    static void InvalidArgs() { 
        std::cout << "Invalid arguments\n"; 
    }

    static void MissingArgs() { 
        std::cout << "Missing arguments\n"; 
    }

    void Function1(float a, float deltaX) {
        std::cout << Derivative(a, deltaX) << std::endl;
    }
    
    void Function2(long x) {
        char *str = Translation(x);
        std::cout << str << '\n';
        std::free(str);
    }

    static void Help() {
        std::cout << "  1. help - for help\n";
        std::cout << "  2. exit - exits program\n";
        std::cout << "  3. 1 <a> <deltaX> - calculates derivative of cos(x) of a with specific deltaX\n";
        std::cout << "  4. 2 <x> - translate x to binary number system\n";
        std::cout << "  4. 0 - switch libs\n";
    }

    static std::vector<std::string> Tokenize(const std::string &line) {
        std::vector<std::string> result;
        std::stringstream ss(line);
        while (ss) {
            std::string token;
            ss >> token;
            if (!token.empty()) {
                result.push_back(token);
            }
        }
        return result;
    }

    bool ProceedLine(const std::string &line) {
        std::vector<std::string> tokens = Tokenize(line);
        if (tokens[0] == "help") {
            Help();
        } else if (tokens[0] == "exit") {
            return false;
        } else if (tokens[0] == "1") {
            if (tokens.size() != 3) {
                MissingArgs();
                return true;
            }
            try {
                Function1(std::atof(tokens[1].c_str()), std::atof(tokens[2].c_str()));
            } catch (std::invalid_argument &) {
                InvalidArgs();
            }
        } else if (tokens[0] == "2") {
            if (tokens.size() != 2) {
                MissingArgs();
                return true;
            }
            try {
                long x = std::stol(tokens[1]);
                Function2(x);
            } catch (std::invalid_argument &) {
                InvalidArgs();
            }
        } else if (tokens[0] == "0") {
            SwitchMode();
            std::cout << "Switched\n";
        } else {
            InvalidArgs();
        }
        return true;
    }

   public:
    MainRoutine() = delete;
    MainRoutine(const MainRoutine &) = delete;
    MainRoutine(MainRoutine &&) = delete;
    MainRoutine &operator=(const MainRoutine &) = delete;
    MainRoutine &operator=(MainRoutine &&) = delete;
    MainRoutine(const char *lib1Path, const char *lib2Path) {
        dls[0] = dlopen(lib1Path, RTLD_LOCAL | RTLD_LAZY);
        if (dls[0] == nullptr) {
            throw std::invalid_argument("Can't open first lib.");
        }
        dls[1] = dlopen(lib2Path, RTLD_LOCAL | RTLD_LAZY);
        if (dls[1] == nullptr) {
            throw std::invalid_argument("Can't open second lib.");
        }
        currentMode = 1;
        SwitchMode();
    }

    ~MainRoutine() {
        dlclose(dls[0]);
        dlclose(dls[1]);
    }

    void Start() {
        std::string line;
        std::cout << "> ";

        while (std::getline(std::cin, line)) {
            if (!ProceedLine(line)) {
                break;
            }
            std::cout << "> ";
        }
    }
};

int main() {
    char *pathToLib1 = getenv("PATH_TO_LIB1");
    char *pathToLib2 = getenv("PATH_TO_LIB2");
    if (pathToLib1 == nullptr) {
        std::cerr << "PATH_TO_LIB1 is not specified\n";
        exit(EXIT_FAILURE);
    }
    if (pathToLib2 == nullptr) {
        std::cerr << "PATH_TO_LIB2 is not specified\n";
        exit(EXIT_FAILURE);
    }
    MainRoutine routine(pathToLib1, pathToLib2);
    routine.Start();
}