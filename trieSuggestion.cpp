//@Author: Avnish Kumar
//Github: github.com/avnish1306
//Codechef handle: avi130698
//LinkedIn: linkedin.com/in/avnish1306/
//Oct 28, 2019

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define charLen 256
class node {
    public:
        node *childs[charLen];
        bool eow;
        node(){
            for(int i=0;i<charLen;i++){
                this->childs[i] = NULL;
            }
            this->eow = false;   //End Of word
        }
        ~node(){
            delete this->childs;
        }
};
class tree {
    public:
        node *root;
        tree(){
            this->root = new node();
        }
        ~tree(){
            destroy(this->root);
        }
        void destroy(node *leaf){
            if(leaf!=NULL){
                for(int i=0;i<charLen;i++){
                    if(leaf->childs[i]!=NULL){
                        destroy(leaf->childs[i]);
                    }
                }
                delete leaf;
            }
        }
        void insert(string s){
            node *temp = this->root;
            for(int i=0;i<(int)s.length();i++){
                int key=s[i];
                if(temp->childs[key]==NULL){
                    temp->childs[key] = new node();
                }
                temp = temp->childs[key];
            }
            temp->eow=true;
            
        }
        vector<string> getSuggestions(string s){
            string res="";
            vector<string> result;
            node *temp = root;
            for(int i=0;i<s.length();i++){
                int key=s[i];
                if(temp->childs[key]==NULL){
                    return result;
                }else{
                    temp = temp->childs[key];
                    res=res+s[i];
                }
            }
            result = getAllMatch(temp,s);
            return result;
        }
        vector<string> getAllMatch(node *leaf,string bs){
            vector<string> result;
            if(leaf->eow==true){
                result.push_back(bs);
            }
            for(int i=0;i<charLen;i++){
                if(leaf->childs[i]!=NULL){
                    char val = i;
                    vector<string> temp=getAllMatch(leaf->childs[i],(bs+val));
                    result.insert( result.end(), temp.begin(), temp.end() );
                }
            }
            return result;
        }
};
//Input format:
//First Line will contain a number N i.e. Numbers of word to feed
//Next N line will contains words (No spaces) Use getline() or gets() to get space saperated input
// Next line will contain a prefix string
int main(){
    tree *trie = new tree();
    int n;
    cin>>n;
    string x;
    for(int i=0;i<n;i++){
        cin>>x;
        trie->insert(x);
    }
    cin>>x;
    vector<string> res = trie->getSuggestions(x);
    if((int)res.size()==0){
        cout<<"Sorry No Suggestion found!!"<<endl;
    }else{
        cout<<(int)res.size()<<" Suggestions found"<<endl;
    }
    for(int i=0;i<(int)res.size();i++){
        cout<<res[i]<<endl;
    }
    return 0;
}
