#ifndef USER_H
#define USER_H "USER_H"
#include<vector>
#include<string>
class Reserve;
class User{
public:
    User(std::string user_email,std::string user_password,std::string user_username);
    ~User();
    void make_reservation(Reserve* new_reserve);
    void cancel_reservation(int reserve_id);
    std::string get_email(){ return email;}
    std::string get_username(){ return username;}
    void increase_wallet_value(float amout);
    void show_wallets(int count);
    void show_reservations();
    float get_wallet(){ return wallet;}
    size_t get_password(){ return password;}
private:
    int reservation_id;
    float wallet;
    std::vector<float> wallets;
    void add_wallet(){ wallets.push_back(wallet);}
    int generate_reservation_id(){ return reservation_id++;}
    std::string email;
    size_t password;
    std::string username;
    std::vector<Reserve*> reserves; 
};
#endif