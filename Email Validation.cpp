#include <iostream>
#include <string>
#include <vector>
#include <regex>

namespace myEmailValidation {
bool IsValidCharForEmail(char c) {
    const char allowedSpecial[] = { '@', '.' };

    for (char ch : allowedSpecial)if (c == ch) return true;

    if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z'))return true;

    return false;
}

bool IsValidStringForEmail(std::string& Email) {
    for (char& c : Email) {
        if (!IsValidCharForEmail(c)) return false;
    }
    return true;
}

bool IsAtPositionValid(std::string email) {
    size_t atPos = email.find('@');
    return(atPos != std::string::npos &&
        atPos != 0 &&
        atPos != email.length() - 1);
}

std::string* SplitEmail(const std::string& email) {
    if (!IsAtPositionValid(email))return nullptr;

    std::string* result = new std::string[2];
    size_t atPos = email.find('@');

    result[0] = email.substr(0, atPos);// Username part
    result[1] = email.substr(atPos + 1);// Domain part

    return result;
}

std::vector<std::string> SplitString(std::string& S1, std::string Delim) {
    std::vector<std::string> vString;
    std::string sWord;
    size_t pos = 0;

    while ((pos = S1.find(Delim)) != std::string::npos) {
        sWord = S1.substr(0, pos);
        if (sWord != "") vString.push_back(sWord);

        S1.erase(0, pos + Delim.length());
        // erase() until positon and move to next word.
    }

    if (S1 != "")vString.push_back(S1);

    return vString;
}

bool IsValidUsername(std::string& UserName) {
    if (UserName[0] == '.') return false;

    size_t UsernameLen = UserName.length();
    size_t max = 30, min = 6;

    if (UsernameLen > max || UsernameLen < min) return false;
    if (UserName[UserName.length() - 1] == '.') return false;
    if (UserName.find("..") != std::string::npos) return false;

    return true;
}

bool IsValidDomainName(std::string DomainName) {
    if (DomainName[0] == '.') return false;
    if (DomainName[DomainName.length() - 1] == '.') return false;
    if (DomainName.find("..") != std::string::npos) return false;
    if (DomainName.find('@') != std::string::npos) return false;
    if (DomainName.rfind('.') == std::string::npos) return false;
    if (DomainName.substr(DomainName.rfind('.')).length() - 1 < 2) return false;

    std::vector<std::string> arrDmainName = SplitString(DomainName, ".");

    for (std::string& s : arrDmainName)
        if (s.length() < 2) return false;

    return true;
}

bool IsValidEmail(std::string Email) {
    //handel more than one (@) user@exa@mple.com

    //or email without (@) like userexample.com
    size_t atCount = std::count(Email.begin(), Email.end(), '@');
    if (atCount != 1)return false;

    //hendel invalid characters like !#$%^&*()_+-= or capital letters
    if (!IsValidStringForEmail(Email))return false;

    //split Email to two parts one for username two for DomainName
    std::string* arrEmail = SplitEmail(Email);
    if (arrEmail == nullptr)return false;

    //handel invalid username like (.user , user. , user1..user2)
    if (!IsValidUsername(arrEmail[0]/*username*/))return false;

    //handel invalid domain name like (.domain , domain. , domain1..domain2)
    if (!IsValidDomainName(arrEmail[1]/*domain name*/))return false;

    //delete dynamic string array
    delete[] arrEmail;

    return true;
}
}

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