#ifndef RATING_H
#define RATING_H "RATING_H"
class User;
struct UserRating{
    UserRating(float location,float cleanliness,float staff,float facilities
    ,float value,float overall,User* user_){
        location_rating = location;
        cleanliness_rating = cleanliness;
        staff_rating = staff;
        facilities_rating = facilities;
        value_for_money_rating = value;
        overall_rating = overall;
        user = user_;

    }
    float location_rating;
    float cleanliness_rating;
    float staff_rating;
    float facilities_rating;
    float value_for_money_rating;
    float overall_rating;
    User* user;
};
typedef struct UserRating Rating;
#endif