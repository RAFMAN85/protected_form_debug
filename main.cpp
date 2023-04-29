#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <unistd.h>
#include <random>
#include <windows.h>

struct LOGIN_INFO{
    std::string login;
    std::string password;
    std::string phone_number;
};


std::string generate_key(const std::string& login, const std::string& password, const std::string& phone) {
    int loginLen = login.length();
    int passwordLen = password.length();
    int phoneLen = phone.length();
    std::string concatenated_str = login + password + phone;
    std::bitset<256> bit_str;
    for (int i = 0; i < concatenated_str.length(); i++) {
        bit_str <<= 8;
        bit_str |= concatenated_str[i];
    }
    std::bitset<256> key;
    for (int i = 0; i < 256; i++) {
        key[i] = bit_str[i] ^ bit_str[(i + loginLen + passwordLen + phoneLen) % 256];
    }
    std::string key_str = "";
    for (int i = 0; i < 32; i++) {
        std::bitset<8> byte;
        for (int j = 0; j < 8; j++) {
            byte[7 - j] = key[i * 8 + j];
        }
        int byte_value = byte.to_ulong();
        int char_index = byte_value % 36;
        if (char_index < 10) {
            key_str += static_cast<char>('0' + char_index); // Numbers 0-9
        } else {
            key_str += static_cast<char>('a' + (char_index - 10)); // Letters a-z
        }
    }

    return key_str;
}

std::string generate_random_string() {
    std::string randomString;
    static const char alphanumeric[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    static const int alphanumericLength = sizeof(alphanumeric) - 1;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, alphanumericLength - 1);
    for (int i = 0; i < 32; ++i) {
        randomString += alphanumeric[dis(gen)];
    }
    return randomString;
}

bool we_passed_upon_the_stair(const std::string& login, const std::string& password){
    bool flag=false;
    if(login==password){
        flag=true;
    }else{
        flag=false;
    }
    return flag;
}

int we_spoke_of_was_and_when(const std::string& phone){
    int loginLen = phone.length();
    int passwordLen = phone.length();
    int phoneLen = phone.length();
    std::string concatenated_str = phone + phone + phone;
    if(we_passed_upon_the_stair(phone, phone)){
        std::cout<<"Why they are equal?";
    }
    return (loginLen+passwordLen)*phoneLen;
}

std::string although_i_was_not_there(const std::string& login, const std::string& password, const std::string& phone){
    if(we_spoke_of_was_and_when(login)>0) {
        std::string result;
        size_t length = login.length();
        for (size_t i = 0; i < length; ++i) {
            result += static_cast<char>(login[i] ^ password[i] ^ phone[i]);
        }
        return result;
    }
}

int main(int argc, char* argv[]) {
    if(argc!=5){
        std::cerr<<"Wrong arguments";
        return 1;
    }
    std::string key_input;
    LOGIN_INFO buffer_info;
    std::string temp_buffer;
    //Uncomment this to use console invitation input
    /*
    std::cout<<"Login (maximum 10 symbols): ";
    std::cin>>buffer_info.login;
    std::cout<<"password(maximum 20 symbols): ";
    std::cin>>buffer_info.password;
    std::cout<<"phone number: ";
    std::cin>>buffer_info.phone_number;
     std::cout<<"Enter key: ";
    std::cin>>key_input;
    */
    buffer_info.login=argv[1];
    buffer_info.password=argv[2];
    buffer_info.phone_number=argv[3];
    key_input=argv[4];

    if(we_spoke_of_was_and_when(buffer_info.login)>0) {
        if (buffer_info.login.length() > 10 || buffer_info.password.length() > 20) {
            std::cout << "Your login or password is too long. True to register again." << std::endl;
            exit(0);
        }
    }

    if(IsDebuggerPresent()){
        temp_buffer = generate_random_string();
    }else{
        temp_buffer = generate_key(buffer_info.login, buffer_info.password, buffer_info.phone_number);
    }

    std::cout<<temp_buffer<<std::endl;
    if(key_input==temp_buffer){
        std::cout<<"Key logging complete!";
    }else{
        std::cout<<"Wrong! Exiting program!";
        std::string he_said_i_was_his_friend= although_i_was_not_there(buffer_info.login, buffer_info.login, buffer_info.login);
    }
    return 0;
}
