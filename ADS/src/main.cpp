#include "include/Porter2.hpp"
#include <iostream>
#include <vector>
#include <system_error>
#include<map>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include<utility>
#include<stdio.h>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

#define BLOCK 1000

//a structure used for storing the id of essay and number of occurrence of a word
typedef struct position 
{
    int essay;
    int times;
}Posi;
typedef map<string, vector<Posi>*> INDEX_TYPE;      //the dictionary INDEX
typedef pair<string, vector<Posi>*> INDEX_VALUE;    //the value type of the dictionary

static int blocknum = 0;                        //used to store the id of block in the output file
static INDEX_TYPE INDEX;
static vector <string> Catalog;
static map <string, int> FILE_ID;               //build a mapping between the name and id of an essay
static map <string, vector<int>*> BLOCK_ID;     //to record the id of block in the output file of each word
static vector<string> stop_words;

//Insert a word into the dictionary
void insert(string x, string essay, FILE *ofINDEX)
{
    auto location = INDEX.find(x);
    if(location == INDEX.end())     //The word doesn't exist in the dictionary
    {
        vector<Posi>* posting_point = new vector<Posi>; //Build a posting list
        Posi newpost = {FILE_ID[essay], 1};             //the id ofthe essay and number of occurrences
        (*posting_point).push_back(newpost);   //insert the new node into the posting list
        INDEX.insert(INDEX_VALUE(x, posting_point));
    }
    else    //The word already exists
    {
        vector<Posi>* posting_point = (*location).second;

        int flag = 1;   //flag = 1, means current word has not appeared in the essay yet
        for(int i=0;i<(*posting_point).size();i++)
        {
            if((*posting_point)[i].essay == FILE_ID[essay])
            {
                flag = 0;
                (*posting_point)[i].times++;    //if this word has appeared in this essay, just add one to the 'times'
                break;
            }
        }
        if(flag)       //insert a new node into the posting list
        {
            Posi newpost = {FILE_ID[essay], 1};
            (*posting_point).push_back(newpost);
        }

        int size = (*posting_point).size();
        if(size == BLOCK)   //the posting list has a length of 1000, then write it into the file
        {
            Posi temp_pose[size];
            for(int i=0;i<size;i++)
            {
                temp_pose[i] = (*posting_point)[i]; //copy all the data into a buffer
            }
            
            fwrite((char*)temp_pose, sizeof(char), 1000*sizeof(Posi)/sizeof(char), ofINDEX);
            (*posting_point).clear();           //remove the data which has been writen into file

            auto it = BLOCK_ID.find(x); 
            if(BLOCK_ID.end() == it)            //If there isn't a block list for current word yet
            {
                vector<int>* block_point = new vector<int>;
                (*block_point).push_back(blocknum);
                BLOCK_ID.insert(pair<string, vector<int>*>(x, block_point));
                blocknum++;
            }
            else    //If there exists
            {
                vector<int>* block_point = (*it).second;
                (*block_point).push_back(blocknum);  //just add a block id
                blocknum++;
            }
        }
    }
}

//for each call of search(), only search one key word
//relavant is used to record the relevance between articles and keywords
void search(string x, int relavant[])
{
    auto location = BLOCK_ID.find(x);
    if(location == BLOCK_ID.end())	    //which means no such key word				
    {
        return;
    }

	FILE *ofINDEX = fopen("INDEXfile.txt", "rb");
	if((*(BLOCK_ID[x])).size() != 0)
	{
		//is_block = true;
		for(int i = 0; i < ((*(BLOCK_ID[x])).size()); i++)
		{
			Posi block_temp[1001];
			int block_num = (*(BLOCK_ID[x]))[i];
            //cout<<block_num<<endl;
			fseek(ofINDEX, block_num*1000*sizeof(Posi), SEEK_SET); //read the blocks with the help of block ID
			fread((char*)block_temp, sizeof(char), 1000*sizeof(Posi)/sizeof(char), ofINDEX);
			for(int j = 0; j < 1000; j++)
            {
                if(block_temp[j].essay == -1) break;
                relavant[block_temp[j].essay] += block_temp[j].times;
                //cout<<block_temp[j].essay<<" ";     //only for test
            }
		}
	}
	fclose(ofINDEX);
    return;
}

//quick sort, used to find the most relavant essays
void sort(int relavant[], int mark_id[], int l, int r)
{
    if(l >= r) return;
    int ls = l, rs = r;
    int mid = (ls + rs)/2;
    swap(mark_id[mid], mark_id[ls]);
    swap(relavant[mid], relavant[ls]);
    
    while(l<r)
    {
        while((-1)*relavant[r]>=(-1)*relavant[ls] && r>l) r--;
        while((-1)*relavant[l]<=(-1)*relavant[ls] && r>l) l++;
        if(r != l)
        {
            swap(mark_id[l], mark_id[r]);
            swap(relavant[l], relavant[r]);
        }
    }
    swap(mark_id[ls], mark_id[l]);
    swap(relavant[ls], relavant[l]);
    sort(relavant, mark_id, ls, l-1);
    sort(relavant, mark_id, l+1, rs);
    return;
}

void read_stop_words(string filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stop_words.push_back(line);
    }
}

bool is_stop_word(string word) {
    for (auto stop_word : stop_words) {
        if (word == stop_word) {
            return true;
        }
    }
    return false;
}

void getTXTfileNames(const fs::path& data_dir, std::vector<std::string>& txt_filenames) {
    try {
        for (const auto& entry : fs::directory_iterator(data_dir)) {
            if (entry.is_regular_file() && entry.path().extension() == ".txt") {
                txt_filenames.push_back(entry.path().filename().string());
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << e.what() << std::endl;
    }
}



int main(void) {

    read_stop_words("stopWords.txt");

    blocknum = 0;
    int line_num = 0, file_num = 0, cnt = 0, build_flag = 1;
    string data_dir = "./data", BUILD_INS;
    
    
    vector<string> txtHTML;
    std::cout<<"Input 're' for rebuilding the index, or 'go' to query section directly."<<endl;
    cin>>BUILD_INS;
    // cerr << "BUILD_INS: " << BUILD_INS << endl;
    if(BUILD_INS == "re")
    {
        build_flag = 0;
        vector<string> txtFileNames;
        getTXTfileNames(data_dir, txtFileNames);
        FILE *ofINDEX = fopen("INDEXfile.txt", "wb");

        for (const auto& txt_filename : txtFileNames) {
            string txt_path = data_dir + "/" + txt_filename;
            ifstream file(txt_path);
            if (!file.is_open()) {
                std::cout << "Failed to open file: " << txt_path << endl;
                return 1;
            } else {
                std::cout << "------- Reading file " << txt_path << " -------" << endl;
            }
            FILE_ID[txt_filename] = file_num++;
            Catalog.push_back(txt_filename);


            string currentHTML;
            getline(file, currentHTML);
            txtHTML.push_back(currentHTML);

            string word;
            while (!file.eof()) {
                file >> word;
                if (is_stop_word(word)) {
                    continue;
                }
                porter2::Stemmer stemmer;
                auto stemmed_word = stemmer.stem(word);
                if (is_stop_word(stemmed_word) || stemmed_word == "") {
                    continue;
                }
                insert(stemmed_word, txt_filename, ofINDEX);
            }
            
        }

        //use an iterater to write the remaining posting list
        //that has not been written to the file to the file
        auto INDEX_it = INDEX.begin();
        while(INDEX_it != INDEX.end())
        {
            Posi buffer[1000];
            vector<Posi>* postpoint = INDEX_it->second;
            for(int i=0;i<postpoint->size();i++)
            {
                buffer[i] = (*postpoint)[i];
                //cout<<INDEX_it->first<<":    "<<buffer[i].essay<<"    "<<buffer[i].times<<endl;
            }
            buffer[postpoint->size()] = {-1, -1};
            fwrite((char*)buffer, sizeof(char), 1000*sizeof(Posi)/sizeof(char), ofINDEX);

            string x = INDEX_it->first;
            auto it = BLOCK_ID.find(x); 
            if(BLOCK_ID.end() == it)            //If there isn't a block list for current word yet
            {
                vector<int>* block_point = new vector<int>;
                (*block_point).push_back(blocknum);
                BLOCK_ID.insert(pair<string, vector<int>*>(x, block_point));
                blocknum++;
            }
            else    //If there exists
            {
                vector<int>* block_point = (*it).second;
                (*block_point).push_back(blocknum);  //just add a block id
                blocknum++;
            }
            INDEX_it++;
        }
        fclose(ofINDEX);
        ofstream ofblock("blockfile.txt");
        cerr<<"Writing blockfile.txt"<<endl;
        auto block_it = BLOCK_ID.begin();
        while(block_it != BLOCK_ID.end())
        {
            string key = block_it->first;
            // if (key == "") {
            //     block_it++;
            //     continue;
            // }
            vector <int>* blocklist = block_it->second;
            ofblock<<key<<" ";
            ofblock<<blocklist->size()<<" ";
            int buffer[blocklist->size()];
            for(int i=0;i<blocklist->size();i++)
            {
                buffer[i] = (*blocklist)[i];
                ofblock<<buffer[i]<<" ";
            }
            
            ofblock<<"\n";
            block_it++;
        }
        ofblock.close();

        ofstream ofall("ALLfile.txt");
        for(int i=0;i<Catalog.size();i++)
        {
            ofall<<Catalog[i]<<"\n";
        }
        ofall.close();

        ofstream ofHTML("HTMLfile.txt");
        for(int i=0;i<txtHTML.size();i++)
        {
            ofHTML<<txtHTML[i]<<"\n";
        }
        ofHTML.close();
    }


    //Query section
    int cnt2 = 0;
    if(build_flag)
    {
        ifstream ifblock("blockfile.txt");
        int num;
        string snum;
        string key;
        cerr<<"Reading blockfile.txt"<<endl;
        while(!ifblock.eof())
        {
            ifblock>>key;
            ifblock>>snum;
            char NUMS[snum.size()+1];
            for(int i=0;i<snum.size();i++)
            NUMS[i] = snum[i];
            NUMS[snum.size()] = '\0';
            num = atoi(NUMS);

            int buffer[num+1];
            for(int i=0;i<num;i++)
            ifblock>>buffer[i];
            vector<int>* blocklist = new vector<int>;
            for(int i=0;i<num;i++)
            (*blocklist).push_back(buffer[i]);
            BLOCK_ID.insert(pair<string, vector<int>*>(key, blocklist));
            cnt2++;
        }
        ifblock.close();

        int cnt3=0;
        string name;
        ifstream ifall("ALLfile.txt");
        cerr<<"Reading ALLfile.txt"<<endl;
        while(getline(ifall, name))
        {
            Catalog.push_back(name);
            FILE_ID[name] = cnt3++;
        }
        file_num = cnt3;
        ifall.close();

        ifstream ifHTML("HTMLfile.txt");
        string html;
        cerr<<"Reading HTMLfile.txt"<<endl;
        while(getline(ifHTML, html))
        {
            txtHTML.push_back(html);
        }
        ifHTML.close();

    }


    // check if the index is built correctly
    cerr << "Catalog size: " << Catalog.size() << endl;
    cerr << "FILE_ID size: " << FILE_ID.size() << endl;
    cerr << "BLOCK_ID size: " << BLOCK_ID.size() << endl;
    cerr << "txtHTML size: " << txtHTML.size() << endl;

    while(1)
    {
        string key, instruction;
        int relavant[file_num], mark_id[file_num];
        for(int i=0;i<file_num;i++)
        {
            mark_id[i] = i;
            relavant[i] = 0;
        }
        //system("CLS");
        std::cout<<"Input your instruction here."<<endl;
        std::cout<<"1. You can input 'S' for searching. And input all the key words after 'S' with '\\g' as the end."<<endl;
        std::cout<<"2. You can input 'E' for ending the searching. And the process will be stopped."<<endl;
        cin>>instruction;
        if (instruction == "E") {
            break;
        } else if (instruction != "S") {
            system("clear");
            std::cout << "Invalid instruction. Reinput!!!" << endl;
            continue;
        }

        while(1)
        {
            //every time input a line, ending with a \g
            //cout the most relavant essays
            cin>>key;
            //porter2::Stemmer stemmer_;
            //auto key1 = stemmer_.stem(key);
            //cout<<key<<endl;
            if (key == "\\g") {
                break;
            } else if (is_stop_word(key)) {
                std::cout << key << " is a stop word." << endl;
                std::cout << "Please input another word." << endl;
                continue;
            } else {
                porter2::Stemmer stemmer;
                auto stemKey = stemmer.stem(key);
                if (is_stop_word(stemKey)) {
                    std::cout << stemKey << " is a stop word." << endl;
                    std::cout << "Please input another word." << endl;
                    continue;
                } else {
                    search(stemKey, relavant);
                }
            }
        }
        sort(relavant, mark_id, 0, file_num-1);
        int range = 0;
        std::cout<< "The Result from " << range << " to " << range + 10 << ":" << endl;
        for(int i=range;i<range+10 && i<file_num;i++)
        std::cout<<i+1<<".  "<<txtHTML[mark_id[i]]<<"     relavant:"<<relavant[i]<<endl;
        while(1)
        {
            std::cout<<"\nInput your instruction here:"<<endl;
            std::cout<<"1. sp: show the previous 10 essays."<<endl;
            std::cout<<"2. sn: show the next 10 essays."<<endl;
            std::cout<<"3. ns: go to the next searching."<<endl;
            string instruction2;
            cin>>instruction2;
            if(instruction2 == "sp") //show previous 10 essays
            {
                if(range >= 10)
                range-=10;
                system("clear");
                std::cout<< "The Result from " << range << " to " << range + 10 << ":" << endl; 
                for(int i=range;i<range+10 && i<file_num;i++)
                std::cout<<i+1<<".  "<<txtHTML[mark_id[i]]<<"     relavant:"<<relavant[i]<<endl;
            }
            else if(instruction2 == "sn")    //show next 10 essays
            {
                if(range+10 < file_num)
                range+=10;
                system("clear");
                std::cout<< "The Result from " << range << " to " << range + 10 << ":" << endl;
                for(int i=range;i<range+10 && i<file_num;i++)
                std::cout<<i+1<<".  "<<txtHTML[mark_id[i]]<<"     relavant:"<<relavant[i]<<endl;
            }
            else if(instruction2 == "ns")    //next search
            {
                system("clear");
                break;
            }
        }
    }

    return 0;

}