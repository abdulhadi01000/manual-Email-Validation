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