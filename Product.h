#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Product{
    private:
    string id;
    string product_name;
    vector<string> category;
    string sell_price;
    string model_num;
    string about_product;
    string product_specs;
    string tech_details;
    string shipping_weight;
    string product_dim;
    string image;
    string variants;
    string product_url;
    string is_amazon;
    public:
    Product(string id = "NA", string product_name = "NA", vector<string> category = {}, 
    string sell_price = "NA",string model_num = "NA",string about_product = "NA", string product_specs = "NA", string tech_details = "NA",
    string shipping_weight = "NA", string product_dim = "NA", string image = "NA", string variants = "NA",
    string product_url = "NA", string is_amazon = "NA");
    string getID() const;
    string getName() const;
    vector<string> getCategory();
    void printDetails();

};