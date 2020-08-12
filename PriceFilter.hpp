#ifndef PRICEFILTER_H
#define PRICEFILTER_H "PRICEFILTER_H"
#include"Filter.hpp"
class PriceFilter : public Filter{
public:
    PriceFilter(float min_price_,float max_price_);
    void apply(const std::vector<Hotel*>& total_hotels);
private:
    float min_price;
    float max_price;
};
#endif