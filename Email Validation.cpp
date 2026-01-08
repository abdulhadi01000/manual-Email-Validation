#include <iostream>
#include "EmailValidation.h"
namespace regex {
    bool IsValidEmail(std::string email) {
        const std::regex pattern(R"(^[a-z0-9](\.?[a-z0-9]){5,29}@([a-z0-9]{2,}\.)+[a-z0-9]{2,}$)");
        return std::regex_match(email, pattern);
    }
}

void PrintRules() {
    std::cout << "\tEnter a valid email address (user@example.com):\n";
    std::cout << "\tAllowed characters: a-z, 0-9, dot (.), and at symbol (@)\n";
    std::cout << "\tLocal part length: 6 to 30 characters\n";
    std::cout << "\tType 'e' or 'exsit' to end program\n";
    std::cout << "\t--------------------------------------------\n";
}

static std::string lower(const std::string& s) {
    std::string result = s;

    for (size_t i = 0; i < result.length(); i++)
    {
        if (result[i] >= 'A' && result[i] <= 'Z')
            result[i] = result[i] - 'A' + 'a';
    }
    return result;
}

void Application() {
    PrintRules();
    while (true) {
        std::cout << "\t>";
        std::string sEmail;
        std::cin >> sEmail;
        
        if (lower(sEmail) == "exsit" || lower(sEmail) == "e")return;

        if (myEmailValidation::IsValidEmail(sEmail))
            std::cout << "\tMy Validate  --> Valid email address.\n";
        else
            std::cout << "\tMy Validate  --> Invalid email address.\n";

        if (regex::IsValidEmail(sEmail))
            std::cout << "\tRegex        --> Valid email address.\n";
        else                            
            std::cout << "\tRegex        --> Invalid email address.\n";

        std::cout << "\t--------------------------------------------\n";
    }
}


int main() {
    Application();
    return 0;
}