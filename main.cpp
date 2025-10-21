#include <iostream>
#include <string>
#include <cassert>
#include <fstream>
#include <sstream>
#include "HashMap.h"
#include "Product.h"
using namespace std;

void test_insert(){
    //normal case
    cout << "Testing Insert:" << endl;
    HashMap<string, int> map;
    map.insert("Games", 10);
    map.insert("Books", 20);
    map.insert("Movies", 30);
    list<int> values;
    bool found = map.get("Games", values);
    assert(found);
    assert(!values.empty());
    assert(values.front() == 10);
    //edge case
    map.insert("Games", 40);
    map.insert("Games", 50);
    list<int> values1;
    map.get("Games", values1);
    assert(values1.size() == 3);
    cout << "all insert cases passed" << endl;
}
void test_get(){
    //normal case
    cout << "Testing get function" << endl;
    HashMap<string, int> map;
    map.insert("Games", 10);
    map.insert("Games", 20);
    list<int> games;
    bool gotGames = map.get("Games", games);
    assert(gotGames);
    assert(games.size() == 2);
    assert(games.front() == 10);
    //edge case
    bool gotNone = map.get("Unknown", games);
    assert(!gotNone);
    assert(games.size() == 2);
    cout << "All get cases passed" << endl;

}
void test_remove(){
    //normal case
    cout <<"Testing remove function" << endl;
    HashMap<string, int> map;
    map.insert("Games", 10);
    map.insert("Books", 20);
    map.insert("Books", 30);
    bool removed = map.remove("Games");
    assert(removed);
    list<int> afterRemove;
    bool exists = map.get("Games", afterRemove);
    assert(!exists);
    assert(afterRemove.empty());
    //edge cases
    //removing unknown key
    bool removed2 = map.remove("Unknown");
    assert(!removed2);
    //removing key with multiple values
    bool removedBooks = map.remove("Books");
    assert(removedBooks);
    list<int> checkBooks;
    bool existBooks = map.get("Books", checkBooks);
    assert(checkBooks.empty() && !existBooks);
    cout << "All remove cases passed" << endl;
}
void test_rehash(){
    //hash happens automatically after an insert
    //normal case
    cout << "Testing rehash function" << endl;
    HashMap<string, int> map(3);
    for (int i = 0; i < 100; ++i) {
        map.insert(to_string(i), i);
    }
    list<int> values;
    bool found = map.get("5", values);
    assert(found);
    assert(!values.empty());
    assert(values.front() == 5);
    //edge case
    HashMap<string, int> map2(3);
    map2.rehash();
    assert(true);
    cout << "All rehash cases passed" << endl;
}
void test_all(){
    cout << "Testing all cases" << endl;
    test_insert();
    test_get();
    test_remove();
    test_rehash();
    cout << "All cases passed" << endl;
}
void printHelp()
{
    cout << "Supported list of commands: " << endl;
    cout << " 1. find <inventoryid> - Finds if the inventory exists. If exists, prints details. If not, prints 'Inventory not found'." << endl;
    cout << " 2. listInventory <category_string> - Lists just the id and name of all inventory belonging to the specified category. If the category doesn't exists, prints 'Invalid Category'.\n"
         << endl;
    cout << " Use :quit to quit the REPL" << endl;
}

bool validCommand(string line)
{
    return (line == ":help") ||
           (line.rfind("find", 0) == 0) ||
           (line.rfind("listInventory") == 0);
}
void find(string id, HashMap<string, Product>& map_id){
    list<Product> products;
    bool found = map_id.get(id, products);
    if(found){
    Product p = products.front();
    p.printDetails();
    }
    else{
        cout << "Inventory/Product not found" << endl;
    }

}
void listInventory(string category, HashMap<string, Product>& map_category){
    list<Product> products;
    bool found = map_category.get(category, products);
    if(found){
    for(Product product : products){
        cout << "ID: " <<  product.getID() << " Name: " << product.getName() << endl;
    }
    }
    else{
        cout << "Invalid Category" << endl;
    }
}
void evalCommand(string line, HashMap<string, Product>& map_id, HashMap<string, Product>& map_category)
{
    if (line == ":help")
    {
        printHelp();
    }
    // if line starts with find
    else if (line.rfind("find", 0) == 0)
    {
        // Look up the appropriate datastructure to find if the inventory exist
    istringstream iss(line);
    string printString;
    string id;
    if (iss >> printString >> id) {
        find(id, map_id);
    }
    else {
    cout << "Invalid input. Format: <command> <id>\n";
    }
    }
    // if line starts with listInventory
    else if (line.rfind("listInventory") == 0)
    {
        // Look up the appropriate datastructure to find all inventory belonging to a specific category
        istringstream iss(line);
    string printString;
    string category;
    if (iss >> printString) {
        getline(iss >> ws, category);
        if(!category.empty()){
        listInventory(category, map_category);
        }
        else {
        cout << "Invalid input. Format: <command> <category>\n";
        }
    }
    }
}


string cleanString(string s) {
    //removes backslashes
    s.erase(remove(s.begin(), s.end(), '\\'), s.end());

    //removes doublequotes
    s.erase(remove(s.begin(), s.end(), '"'), s.end());

    //Trims leading/trailing whitespaces
    auto notSpace = [](unsigned char ch) { return !std::isspace(ch); };

    //trim front of string of any whitespace
    s.erase(s.begin(), find_if(s.begin(), s.end(), notSpace));
    //trim backs of string of any whitespace
    s.erase(find_if(s.rbegin(), s.rend(), notSpace).base(), s.end());

    return s;
}
string getCSVField(stringstream& ss) {
    string field;
    bool inQuotes = false;
    char c;

    while (ss.get(c)) {
        if (c == '"') {
            inQuotes = !inQuotes; //toggles inQuotes when right before end of the field has been reached
        } 
        else if (c == ',' && !inQuotes) { //checks if the end of the field has been reached and break
            break;
        } 
        else {
            field += c; //adds thr character to the field while still in csv field
        }
    }
    return field;
}

void loadProducts(ifstream& infile, HashMap<string, Product>& map_id, HashMap<string, Product>& map_category){
    if(!(infile.is_open())){
        infile.open("marketing_sample_for_amazon_com-ecommerce__20200101_20200131__10k_data.csv");
    }
    string line;
    getline(infile, line);
    while(getline(infile, line)){
        string id, product_name = "";
        vector<string> category;
        string sell_price, model_num, about_product, product_specs, tech_details, shipping_weight, product_dim, image = "";
        string variants, product_url, is_amazon = "";
        vector<string> fields;
        stringstream ss(line);
        //pushes all the fields to one vector while making sure to get the full field
        while (ss.peek() != EOF) {
            fields.push_back(getCSVField(ss)); 
        }
        id = fields[0];
        product_name = fields[1];
        //getting the categories
        string category_string = fields[4];
        stringstream ss_category(category_string);
        string category_token;
        while(getline(ss_category, category_token, '|')){
            category_token = cleanString(category_token);
            category.push_back(category_token);
        }
        //getting the rest of the fields, indexes skipped are fields skipped in READ ME file
        sell_price = fields[7];
        model_num = fields[9];
        about_product = fields[10];
        product_specs = fields[11];
        tech_details = fields[12];
        shipping_weight = fields[13];
        product_dim = fields[14];
        image = fields[15];
        variants = fields[16];
        product_url = fields[18];
        is_amazon = fields[25];
        //creating the objects then inserting into map
        Product item (id, product_name, category, sell_price, model_num, about_product, product_specs,tech_details, shipping_weight,
        product_dim, image, variants, product_url, is_amazon);
        if(category.empty()){
            map_id.insert(id, item);
            map_category.insert("NA", item);
        }
        else{
            for(string category1 : category){
                map_category.insert(category1, item);
            }
            map_id.insert(id, item);
        }
    }
}
void bootStrap()
{
    cout << "\n Welcome to Amazon Inventory Query System" << endl;
    cout << " enter :quit to exit. or :help to list supported commands." << endl;
    cout << "\n> ";
    // TODO: Do all your bootstrap operations here
    // example: reading from CSV and initializing the data structures
    // Don't dump all code into this single function
    // use proper programming practices
    string line;
    ifstream infile;
    infile.open("marketing_sample_for_amazon_com-ecommerce__20200101_20200131__10k_data.csv");
    HashMap<string, Product> map_id;
    HashMap<string, Product> map_category;
    loadProducts(infile, map_id, map_category);
    while (getline(cin, line) && line != ":quit")
    {
        if (validCommand(line))
        {
            evalCommand(line, map_id, map_category);
        }
        else
        {
            cout << "Command not supported. Enter :help for list of supported commands" << endl;
        }
        cout << "> ";
    }
}
int main(int argc, char const *argv[])
{
    test_all();
    bootStrap();
    return 0;
}
