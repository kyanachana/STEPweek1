#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=int(a);i<int(b);++i)
#define SIZE 200005
#define INF 1000000005LL
#define MOD 1000000007
using namespace std;
typedef long long int ll;
typedef pair <int,int> P;
vector<pair<string,string> > new_dictionary;

map<char,int> input_char_count;
vector<char> input_in_char;
//入力した文字の文字の含まれる回数と何の文字があるか(使わない)を格納
vector<string> ans;
//適する単語を全て格納する

void cnt(string sorted_word,map<char,int> &char_count,vector<char> &in_char){
    //授業中のコードテストの時のaaabb→a3b2と返すプログラムを使った
    int length = sorted_word.size();
    char succesive_char = sorted_word[0];
    int succesion = 1;
    for(int i=1;i<length;i++){
        if(i==length-1){
            //最後の処理
            if(succesive_char==sorted_word[i]){
                succesion++;
                char_count[succesive_char]=succesion;
                in_char.push_back(succesive_char);
            }else{
                char_count[succesive_char]=succesion;
                char_count[sorted_word[i]]=1;
                in_char.push_back(sorted_word[i]);
                in_char.push_back(succesive_char);
            }  
        }else{
            if(succesive_char==sorted_word[i]){
                succesion ++;
            }else{
                char_count[succesive_char]=succesion;
                in_char.push_back(succesive_char);
                succesive_char = sorted_word[i];
                succesion= 1;
                
            }
        }
        
    }
}

void dictionary_search(){

    for(int i=0;i<new_dictionary.size();i++){
        map<char,int> dictionary_char_count;
        vector<char> dictionary_in_char;
        cnt(new_dictionary[i].first,dictionary_char_count,dictionary_in_char);
        int check=1;
        for(char c : dictionary_in_char){
            //辞書にある単語を１つ１つ確認する
            if(dictionary_char_count[c]>input_char_count[c]){
                check=0;
            }
        }
        if(check==1){
            ans.push_back(new_dictionary[i].second);
        }
    }

}
int main(){
    ifstream ifs("./dictionary.words");
    string str;
    while (getline(ifs, str)){
        string str_before=str;
        transform(str.cbegin(),str.cend(),str.begin(),::tolower);
        sort(str.begin(),str.end());
        new_dictionary.push_back(make_pair(str,str_before));
    }
    string input;
    //入力した単語
    while(cin>>input&&input!="!"){
        //　手間を減らすためにループで入力する
        sort(input.begin(),input.end());
        cnt(input,input_char_count,input_in_char);
        //入力した文字の文字の含まれる回数と何の文字があるか(使わない)を格納
        dictionary_search();
        vector<int> point_data={1,1,2,1,1,2,1,2,1,3,3,2,2,1,1,2,3,1,1,1,1,2,2,3,2,3};
        //アルファベットの点数を記録
        int max_point=-1;
        string max_string;
        for(string possible_word:ans){
            //ansの中から最も点数が高いものを探す
            int point=0;
            for(int i=0;i<possible_word.size();i++){
                //cout<<possible_word<<endl;
                possible_word[i]=tolower(possible_word[i]);
                if(possible_word[i]=='q'){
                    i++;
                }
                point += point_data[int(possible_word[i])-96];
            }
            if(point>max_point){
                max_point=point;
                max_string=possible_word;
        
            }
        }
        cout<<max_string<<endl;
        ans.clear();
        input_char_count.clear();
        input_in_char.clear();
        //初期化
    }
    
  return 0;
}