#ifndef HOTEL_H
#define HOTEL_H "HOTEL_H"
#include<string>
#include<vector>
#include<map>
#include"Rating.hpp"
class Reserve;
class Room;
class Period;
class Comment; 
class Hotel{
public:
    Hotel(std::string id,std::string name,int rating,std::string hotel_overview,std::string amenities,std::string hotel_city,float hotel_latitude,float hotel_longitude,std::string hotel_image_url,std::vector<int> rooms_numbers,std::vector<int> rooms_prices);
    ~Hotel();
    void print_general_informations();
    void print_specific_informations();
    Reserve* make_reservation(std::string room_type,int quanitity,int check_in,int check_out,float user_wallet);
    std::string get_id(){ return unique_id;}
    std::string get_city(){ return city;}
    void add_new_comment(Comment* new_comment);
    void show_comments();
    void add_new_rating(Rating* new_rating);
    void show_rating();
    int get_star(){ return star_rating;}
    float compute_average_price();
    bool has_enough_room(std::string room_type,const Period& chosen_period,int quantity,std::vector<Room*>& selected_rooms);
private:
    int compute_total_rooms();
    void determine_rooms(std::vector<int> rooms_numbers);
    void determine_prices(std::vector<int> rooms_prices);
    void print_rooms_numbers();
    void print_rooms_prices();
    std::string generate_id(char room_key,int index);
    std::string unique_id;
    int calculate_reserve_cost(std::string room_type,const Period& chosen_period,int quantity);
    std::string property_name;
    int star_rating;
    std::string overview;
    std::string property_amenities;
    std::string city;
    float latitude;
    float longitude;
    std::string image_url;
    std::vector<std::vector<Room*>> total_rooms;
    std::vector<Rating*> total_ratings;
    std::vector<Comment*> total_comments;
    std::vector<char> total_rooms_keys;
    std::map<char,int> total_rooms_prices;
    std::map<char,int> total_rooms_indexes;
};
#endif