#include"PriceFilter.hpp"
#include"Hotel.hpp"
using namespace std;
PriceFilter::PriceFilter(float min_price_,float max_price_){
    min_price = min_price_;
    max_price = max_price_;
}
void PriceFilter::apply(const vector<Hotel*>& total_hotels){
    filtered_hotels.clear();
    float hotel_average_price;
    for(int i=0;i<total_hotels.size();i++){
        hotel_average_price = total_hotels[i]->compute_average_price();
        if(hotel_average_price >= min_price && hotel_average_price <= max_price){
            filtered_hotels.push_back(total_hotels[i]);
        }
    }
}
