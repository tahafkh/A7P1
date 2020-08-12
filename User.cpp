#include"User.hpp"
#include"Reserve.hpp"
#include"NotFound.hpp"
using namespace std;
#include<iostream>
#include<cmath>
#include<functional>
#define FIRST_RESERVE_ID 1
#define INITAL_WALLET 0
#define EMPTY "Empty"
#define MIN_RESERVES 0
User::User(string user_email,string user_password,string user_username){
    hash<string> hashed_password;
    email = user_email;
    password = hashed_password(user_password);
    username = user_username;
    reservation_id = FIRST_RESERVE_ID;
    wallet = INITAL_WALLET;
    add_wallet();
}
void User::make_reservation(Reserve* new_reserve){
    new_reserve->set_id(generate_reservation_id());
    wallet -= new_reserve->get_cost();
    add_wallet();
    reserves.push_back(new_reserve);
}
void User::cancel_reservation(int reserve_id){
    for(int i=0;i<reserves.size();i++){
        if(reserve_id == reserves[i]->get_id()){
            reserves[i]->cancel_reservation();
            wallet += (float)(reserves[i]->get_cost())/2;
            add_wallet();
            delete reserves[i];
            reserves.erase(reserves.begin() + i);
            return;
        }
    }
    throw NotFound();
}
void User::increase_wallet_value(float amount){
    wallet+=amount;
    add_wallet();
}
void User::show_wallets(int count){
    int wallet_nums = count > wallets.size() ? wallets.size() : count;
    for(int i=0;i<wallet_nums;i++){
        cout<<(int)round(wallets[wallets.size()-1-i])<<endl;
    }
}
void User::show_reservations(){
    for(int i=0;i<reserves.size();i++){
        reserves[reserves.size() - i -1]->print();
    }
    if(reserves.size() == MIN_RESERVES){
        cout<<EMPTY<<endl;
    }
}
User::~User(){
    for(int i=0;i<reserves.size();i++){
        delete reserves[i];
    }
}