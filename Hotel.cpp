#include"Hotel.hpp"
#include"Room.hpp"
#include"Reserve.hpp"
#include"Comment.hpp"
#include"SameType.hpp"
#include"NotEnough.hpp"
#include<iomanip>
#include<iostream>
#include<algorithm>
using namespace std;
#define KEY_NUM 1
#define STANDARD_KEY 's'
#define DELUXE_KEY 'd'
#define LUXURY_KEY 'l'
#define PREMIUM_KEY 'p'
#define STANDARD_INDEX 0
#define DELUXE_INDEX 1
#define LUXURY_INDEX 2
#define PREMIUM_INDEX 3
#define MIN_PRICE 0
#define MIN_RATING_NUM 0
#define PRECISION 2
#define KEY_INDEX 0
#define SPACE " "
#define ROOM "Room"
#define CREDIT "Credit"
#define LOCATION "location"
#define CLEANLINESS "cleanliness"
#define STAFF "staff"
#define FACILITIES "facilities"
#define VALUE_FOR_MONEY "value for money"
#define OVERALL_RATING "overall rating"
#define NO_RATING "No Rating"
string Hotel::generate_id(char room_key,int index){
    return (string(KEY_NUM,room_key) + to_string(index));
}
Hotel::Hotel(string id,string name,int rating,string hotel_overview,string amenities,string hotel_city,float hotel_latitude,float hotel_longitude,string hotel_image_url,vector<int> rooms_numbers,vector<int> rooms_prices){
    unique_id = id;
    property_name = name;
    star_rating = rating;
    overview = hotel_overview;
    property_amenities = amenities;
    city = hotel_city;
    latitude = hotel_latitude;
    longitude = hotel_longitude;
    image_url = hotel_image_url;
    determine_rooms(rooms_numbers);
    determine_prices(rooms_prices);
}
void Hotel::determine_rooms(vector<int> rooms_numbers){
    for(int i = 0 ;i<rooms_numbers.size();i++){
        vector<Room*> rooms;
        switch(i){
            case STANDARD_INDEX:
                for(int j=0;j<rooms_numbers[i];j++){
                    rooms.push_back(new Room(generate_id(STANDARD_KEY,j+1),this));
                }
                total_rooms_keys.push_back(STANDARD_KEY);
                total_rooms_indexes[STANDARD_KEY] = STANDARD_INDEX;
                break;
            case DELUXE_INDEX:
                for(int j=0;j<rooms_numbers[i];j++){
                    rooms.push_back(new Room(generate_id(DELUXE_KEY,j+1),this));
                }
                total_rooms_keys.push_back(DELUXE_KEY);
                total_rooms_indexes[DELUXE_KEY] = DELUXE_INDEX;
                break;
            case LUXURY_INDEX:
                for(int j=0;j<rooms_numbers[i];j++){
                    rooms.push_back(new Room(generate_id(LUXURY_KEY,j+1),this));
                }
                total_rooms_keys.push_back(LUXURY_KEY);
                total_rooms_indexes[LUXURY_KEY] = LUXURY_INDEX;
                break;
            case PREMIUM_INDEX:
                for(int j=0;j<rooms_numbers[i];j++){
                    rooms.push_back(new Room(generate_id(PREMIUM_KEY,j+1),this));
                }
                total_rooms_keys.push_back(PREMIUM_KEY);
                total_rooms_indexes[PREMIUM_KEY] = PREMIUM_INDEX;
                break;
        }
        total_rooms.push_back(rooms);
    }
}
void Hotel::determine_prices(vector<int> rooms_prices){
    for(int i = 0;i<rooms_prices.size();i++){
        switch(i){
            case STANDARD_INDEX:
                total_rooms_prices[STANDARD_KEY] = rooms_prices[i];
                break;
            case DELUXE_INDEX:
                total_rooms_prices[DELUXE_KEY] = rooms_prices[i];
                break;
            case LUXURY_INDEX:
                total_rooms_prices[LUXURY_KEY] = rooms_prices[i];
                break;
            case PREMIUM_INDEX:
                total_rooms_prices[PREMIUM_KEY] = rooms_prices[i];
                break;
        }
    }
}
float Hotel::compute_average_price(){
    int prices_sum=0 , room_numbers=0;
    for(int i=0;i<total_rooms_keys.size();i++){
        if(total_rooms_prices[total_rooms_keys[i]] > MIN_PRICE){
            prices_sum += total_rooms_prices[total_rooms_keys[i]];
            room_numbers++;
        }
    }
    float average_price = room_numbers ? (float)prices_sum/room_numbers : MIN_PRICE;
    return average_price;
}
int Hotel::compute_total_rooms(){
    int rooms = 0;
    for(int i=0;i<total_rooms.size();i++){
        rooms += total_rooms[i].size();
    }
    return rooms;
}
void Hotel::print_general_informations(){
    cout<<unique_id<<SPACE<<property_name<<SPACE<<star_rating<<SPACE<<city<<SPACE<<compute_total_rooms()<<SPACE;
    cout<<fixed<<showpoint<<setprecision(PRECISION)<<compute_average_price()<<endl;
}
void Hotel::print_specific_informations(){
    cout<<unique_id<<endl;
    cout<<property_name<<endl;
    cout<<"star: "<< star_rating<<endl;
    cout<<"overview: "<<overview<<endl;
    cout<<"amenities: "<<property_amenities<<endl;
    cout<<"city: "<<city<<endl;
    cout<<"latitude: "<<fixed<<showpoint<<setprecision(PRECISION)<<latitude<<endl;
    cout<<"longitude: "<<fixed<<showpoint<<setprecision(PRECISION)<<longitude<<endl;
    print_rooms_numbers();
    print_rooms_prices();
}
void Hotel::print_rooms_numbers(){
    cout<<"#rooms: ";
    for(int i=0;i<total_rooms.size();i++){
        cout<<total_rooms[i].size();
        if(i!=total_rooms.size() - 1){
            cout<<SPACE;
        }
    }
    cout<<endl;
}
void Hotel::print_rooms_prices(){
    cout<<"price: ";
    for(int i=0;i<total_rooms_keys.size();i++){
        cout<<total_rooms_prices[total_rooms_keys[i]];
        if(i!=total_rooms_keys.size()-1){
            cout<<SPACE;
        }
    }
    cout<<endl;
}
int Hotel::calculate_reserve_cost(string room_type,const Period& chosen_period,int quantity){
    return total_rooms_prices[room_type[KEY_INDEX]]*quantity*chosen_period.calculate_days();
}
bool Hotel::has_enough_room(string room_type,const Period& chosen_period,int quantity,vector<Room*>& selected_rooms){
    selected_rooms.clear();
    for(int i=0;i<total_rooms[total_rooms_indexes[room_type[KEY_INDEX]]].size() && selected_rooms.size()<quantity;i++){
        if(!total_rooms[total_rooms_indexes[room_type[KEY_INDEX]]][i]->is_reserved(chosen_period)){
            selected_rooms.push_back(total_rooms[total_rooms_indexes[room_type[KEY_INDEX]]][i]);
        }
    }
    if(selected_rooms.size() < quantity){
        return false;
    }
    return true;
}
Reserve* Hotel::make_reservation(string room_type,int quantity,int check_in,int check_out,float user_wallet){
    vector<Room*> selected_rooms;
    Period chosen_period(check_in,check_out);
    if(!has_enough_room(room_type,chosen_period,quantity,selected_rooms)){
        throw NotEnough(ROOM);
    }
    if(user_wallet < calculate_reserve_cost(room_type,chosen_period,quantity)){
        throw NotEnough(CREDIT);
    }
    Reserve* new_reserve = new Reserve(calculate_reserve_cost(room_type,chosen_period,quantity),unique_id,room_type,chosen_period,selected_rooms);
    for(int i=0;i<selected_rooms.size();i++){
        selected_rooms[i]->add_reservation(new_reserve);
        cout<<selected_rooms[i]->get_id();
        if(i!=selected_rooms.size()-1){
            cout<<SPACE;
        }
    }
    cout<<endl;
    return new_reserve;
}
Hotel::~Hotel(){
    for(int i=0;i<total_rooms.size();i++){
        for(int j=0;j<total_rooms[i].size();j++){
            delete total_rooms[i][j];
        }
    }
    for(auto comment : total_comments){
        delete comment;
    }
    for(auto rating : total_ratings){
        delete rating;
    }
}
void Hotel::add_new_comment(Comment* new_comment){
    total_comments.push_back(new_comment);
}
void Hotel::show_comments(){
    for(int i=0;i<total_comments.size();i++){
        total_comments[total_comments.size() - 1 - i]->print();
    }
}
void Hotel::add_new_rating(Rating* new_rating){
    auto same_rating_iterator = find_if(total_ratings.begin(),total_ratings.end(),SameRatingType(new_rating));
    if(same_rating_iterator != total_ratings.end()){
        delete (*same_rating_iterator);
        total_ratings.erase(same_rating_iterator);
    }
    total_ratings.push_back(new_rating);
}
void Hotel::show_rating(){
    if(total_ratings.size() == MIN_RATING_NUM){
        cout<<NO_RATING<<endl;
        return;
    }
    float location_sum = 0,cleanliness_sum =0 ,staff_sum = 0,facilities_sum = 0,value_for_money_sum =0,overall_sum=0;
    for(auto rating : total_ratings){
        location_sum += rating->location_rating;
        cleanliness_sum += rating->cleanliness_rating;
        staff_sum += rating->staff_rating;
        facilities_sum += rating->facilities_rating;
        value_for_money_sum += rating->value_for_money_rating;
        overall_sum += rating->overall_rating;
    }
    cout<<LOCATION<<": "<<fixed<<setprecision(PRECISION)<<location_sum/total_ratings.size()<<endl;
    cout<<CLEANLINESS<<": "<<fixed<<setprecision(PRECISION)<<cleanliness_sum/total_ratings.size()<<endl;
    cout<<STAFF<<": "<<fixed<<setprecision(PRECISION)<<staff_sum/total_ratings.size()<<endl;
    cout<<FACILITIES<<": "<<fixed<<setprecision(PRECISION)<<facilities_sum/total_ratings.size()<<endl;
    cout<<VALUE_FOR_MONEY<<": "<<fixed<<setprecision(PRECISION)<<value_for_money_sum/total_ratings.size()<<endl;
    cout<<OVERALL_RATING<<": "<<fixed<<setprecision(PRECISION)<<overall_sum/total_ratings.size()<<endl;
}