#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <unistd.h>
#include <random>

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


int main(int argc, char* argv[]) {
    if(argc!=5){
        std::cerr<<"Wrong arguments";
        return 1;
    }
    std::string key_input;
    LOGIN_INFO buffer_info;
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

    if(buffer_info.login.length() > 10 || buffer_info.password.length() > 20){
        std::cout<<"Your login or password is too long. True to register again."<<std::endl;
        exit(0);
    }

    std::string temp_buffer = generate_key(buffer_info.login, buffer_info.password, buffer_info.phone_number);
    std::cout<<temp_buffer<<std::endl;
    if(key_input==temp_buffer){
        std::cout<<"Key logging complete!";
    }else{
        std::cout<<"Wrong! Exiting program!";
    }
    return 0;
}
