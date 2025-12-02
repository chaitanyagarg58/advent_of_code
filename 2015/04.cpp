#include <iostream>
#include <climits>
#include <openssl/md5.h>
#include <iomanip>
#include <sstream>


std::string md5(const std::string& input)
{
    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5((unsigned char*)input.c_str(), input.size(), digest);

    std::ostringstream oss;
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)digest[i];

    return oss.str();
}

int main()
{
    std::string key;
    std::cin >> key;

    int answer_1 = 1;
    while (answer_1 < INT_MAX)
    {
        std::string input = key + std::to_string(answer_1);
        std::string hash = md5(input);
        std::cout << hash << std::endl;
        if (hash.substr(0, 5) == "00000") break;
        answer_1++;
    }

    std::cout << "Answer 1 :: " << answer_1 << std::endl;
}