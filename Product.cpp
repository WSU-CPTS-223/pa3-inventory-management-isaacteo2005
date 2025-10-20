#include "Product.h"

Product::Product(string id, string product_name, vector<string> category, 
    string sell_price,string model_num, string about_product, string product_specs, string tech_details,
    string shipping_weight, string product_dim, string image, string variants,
    string product_url, string is_amazon){
        this->id = id;
        this->product_name = product_name;
        this->category = category;
        this->sell_price = sell_price;
        this->model_num = model_num;
        this->about_product = about_product;
        this->product_specs = product_specs;
        this->tech_details = tech_details;
        this->shipping_weight = shipping_weight;
        this->product_dim = product_dim;
        this->image = image;
        this->variants = variants;
        this->product_url = product_url;
        this->is_amazon = is_amazon;
        if(this->id == ""){
            this->id = "NA";
        }
        if(this->product_name == ""){
            this->product_name = "NA";
        }
        if(this->sell_price == ""){
            this->sell_price = "NA";
        }
        if(this->model_num == ""){
            this->model_num = "NA";
        }
        if(this->about_product == ""){
            this->about_product = "NA";
        }
        if(this->product_specs == ""){
            this->product_specs = "NA";
        }
        if(this->tech_details == ""){
            this->tech_details = "NA";
        }
        if(this->shipping_weight == ""){
            this->shipping_weight = "NA";
        }
        if(this->product_dim == ""){
            this->product_dim = "NA";
        }
        if(this->image == ""){
            this->image = "NA";
        }
        if(this->variants == ""){
            this->variants = "NA";
        }
        if(this->variants == ""){
            this->variants = "NA";
        }
        if(this->is_amazon == ""){
            this->is_amazon = "NA";
        }

    }
string Product::getID() const{
    return this->id;
}
string Product::getName() const{
    return this->product_name;
}
vector<string> Product::getCategory(){
    return this->category;
}
void Product::printDetails(){
    cout << "ID: " << this->id << endl;
    cout << " Name: " << this->product_name << endl; cout << " Categories: " << endl;
    if(category.empty()){
        cout << "NA";
    }
    else{
    for(string x : category){
        cout << x << ", ";
    }
    }   
    cout << endl;
    cout << "Price: " << this->sell_price << endl; 
    cout << " Model Number: " << this->model_num << endl;
    cout << " About:" << this->about_product << endl;
    cout << "Product specs: " << this->product_specs << endl; cout << " Tech Details: " << this->tech_details << endl;
    cout << "Weight: " << this->shipping_weight << endl; cout << " Dimensions: " <<  this->product_dim << endl; cout << " Image: " << this->image << endl;
    cout << "Variants: " << this->variants << endl; cout << " URL: " << this->product_url << endl; cout << " from amazon: " << this->is_amazon << endl;
}



