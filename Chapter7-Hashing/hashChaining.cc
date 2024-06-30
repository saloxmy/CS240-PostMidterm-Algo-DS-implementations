module HashChain;


int hash(int n, int M){ return n % M; } // hash fcn

struct Node{
    int data;
    Node *next;

    ~Node(){delete next;}
};

struct HashChain {
    int M;
    int n;
    Node **table;

    HashChain(): M{1}, n{0}, table{ new Node*[1] }{}
    HashChain(int m): M{m}, n{0}, table{ new Node*[m] }{ for (int i = 0; i < m; ++i) table[i] = nullptr; } 
    
    void reHash(); // re-sizing when n == m
    void insert(int data);
    int remove(int data);
    int search(int data);
};


void HashChain::reHash(){
    // increase table size
    if (n >= M){
        HashChain newHashChain{M*2};
        copyTable(this->table, newHashChain);
    } else (n < M/2){
        HashChain newHashChain{M/2};
        copyTable(*this, newHashChain);
    }
}
// returns index in list at hashindex in table
int HashChain::search(){
    const int hashindex = hash(data, M);
    if(!(table[hashindex])) return 0;
    int ctr = 0;
    Node *currNode = table[hashindex];
    while(!(currNode->next)){ ++ctr; currNode = currNode->next;}
    return ctr;
}

void HashChain::insert(int data){
    const int hashindex = hash(data, M);
    if(!(table[hashindex])){
        table[hashindex] = new Node{data, nullptr};
        return;
    }
    Node *currNode = table[hashindex];
    while(!(currNode->next)) currNode = currNode->next;
    currNode->next =  new Node{data, nullptr};
}

int HashChain::remove(int data){
    const int hashindex = hash(data, M);
    if(!(table[hashindex])) table[hashindex] = new Node{data, nullptr};
    Node *currNode = table[hashindex];
    while(!(currNode->next)) currNode = currNode->next;
    currNode->next =  new Node{data, nullptr};
}

void copyTable(Node** &table, Node** &newtable, int n, int M){
    Node *currNode = nullptr;
    for (int i = 0; i < n; ++i){
        const int oldTableIndex = hash(i,M); // old hash index
        
        currNode = table[oldTableIndex]; // list in old table
        while(currNode){ // copy vals over
            newTable.insert(currNode->data);
            currNode = currNode->next;
        }

        // delete entire list in old table
        delete oldTable.table[oldTableIndex];
        oldTable.table[oldTableIndex] = nullptr;
    }
}