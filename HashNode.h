#ifndef HASHNODE_H
#define HASHNODE_H
template <typename K, typename V>
class HashNode{
    private:
    K key;
    V value;
    public:
    HashNode(const K& Key, const V& Value) : key(Key), value(Value){}
    ~HashNode();
    K getKey() const;
    V getValue() const;
};
template <typename K, typename V>
HashNode<K, V>::~HashNode(){

}
template <typename K, typename V>
K HashNode<K, V>::getKey() const{
    return this->key;
}
template <typename K, typename V>
V HashNode<K, V>::getValue() const{
    return this->value;
}

#endif