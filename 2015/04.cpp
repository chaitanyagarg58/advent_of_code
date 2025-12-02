#include <iostream>
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

    int answer_1 = 0;
    int answer_2 = 0;
    for (int num = 1; !answer_1 || !answer_2; num++)
    {
        std::string input = key + std::to_string(num);
        std::string hash = md5(input);
        if (answer_1 == 0 && hash.substr(0, 5) == "00000") answer_1 = num;
        if (hash.substr(0, 6) == "000000") answer_2 = num;
    }

    std::cout << "Answer 1 :: " << answer_1 << std::endl;
    std::cout << "Answer 2 :: " << answer_2 << std::endl;
}