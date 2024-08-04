#include <bits/stdc++.h>
#include "submittedlab6.cpp"
#include <cassert>
using namespace std;

vector<string> chapters_list;

void get_chapter_list() {
    ifstream inputfile("chapterNames.txt");

    if(!inputfile.is_open()) {
        cerr << "Unable to open file" << endl;
        return;
    }

    string line;
    while(getline(inputfile, line)){
        istringstream iss(line);
        string word;

        while(iss >> word){
            chapters_list.push_back(word);
            cout << word << endl;
        }
    }
}

int failed_tests = 0;

void test_index_entry1(Lexicon* lexicon) {

    vector<IndexEntry> index_entry = lexicon->buildIndex();
    cout<<"hi"<<endl;
    for (auto& entry : index_entry) {
        if (entry.getWord() == "he" && entry.getChapterWordCounts()[0].first == "Chapter1") {
            assert(entry.getChapterWordCounts()[0].second == 17);
        }
        if (entry.getWord() == "cave" && entry.getChapterWordCounts()[0].first == "Chapter1") {
            cout<<entry.getChapterWordCounts()[0].second<<endl;
            assert(entry.getChapterWordCounts()[0].second == 8);
        }
    }
}
void test_index_entry2(Lexicon* lexicon) {
    vector<IndexEntry> index_entry = lexicon->buildIndex();
    cout<<"*************"<<endl;
    cout<<index_entry.size()<<endl;
    for (auto& entry : index_entry) {
        if (entry.getWord() == "anyone" && entry.getChapterWordCounts()[1].first == "Chapter2") {
            assert(entry.getChapterWordCounts()[1].second == 1);
        }
        if (entry.getWord() == "emily" && entry.getChapterWordCounts()[1].first == "Chapter2") {
            assert(entry.getChapterWordCounts()[1].second == 3);
        }
    }
    cout<<"byeee"<<endl;
}

void test_index_entry3(Lexicon* lexicon) {
    vector<IndexEntry> index_entry = lexicon->buildIndex();

    for (auto& entry : index_entry) {
        if (entry.getWord() == "heal" && entry.getChapterWordCounts()[2].first == "Chapter3") {
            assert(entry.getChapterWordCounts()[2].second == 1);
        }
        if (entry.getWord() == "from" && entry.getChapterWordCounts()[2].first == "Chapter3") {
            assert(entry.getChapterWordCounts()[2].second == 1);
        }
    }
}

void test_preorder(Lexicon* lexicon) {
    cout<<"test preorder"<<endl;
    vector<HybridNode*> preorder_traversal = lexicon->getRedBlackTree().preOrderTraversal(lexicon->getRedBlackTree().getRoot(), 9);
    cout<<"Hello"<<endl;
    cout<<preorder_traversal.size()<<endl;
    assert(preorder_traversal.size() == 234);
    cout<<"hihihi"<<endl;
}

void test_black_height(Lexicon* lexicon) {
    assert(lexicon->getRedBlackTree().blackheight(lexicon->getRedBlackTree().getRoot()) == 5);
}

void test_search(Lexicon* lexicon) {
    HybridNode* node = lexicon->getRedBlackTree().search("he");
    assert(node->key == "he");  

    node = lexicon->getRedBlackTree().search("machine");
    assert(node == nullptr);
}

void test_delete(Lexicon* lexicon) {
    lexicon->getRedBlackTree().deleteNode("he");
    assert(lexicon->getRedBlackTree().search("he") == nullptr);    
}

int main() {
    get_chapter_list();
    Lexicon* lexicon = new Lexicon();
    lexicon->readChapters(chapters_list);
    HybridNode* node =lexicon->getRedBlackTree().getRoot();
    cout<<"|||||  out from read chapters ||||||"<<endl;
    // cout<<node->element<<endl;
    // cout<<node->left_child->element<<endl;
    // cout<<lexicon->getRedBlackTree().getRoot()->left_child->key<<endl;
    HybridNode* newnode = lexicon->getRedBlackTree().search("forever");
    cout<<"out of search"<<endl;
    if(newnode != nullptr){
        cout<<"forever is being inserted"<<endl;
    }
    else{
        cout<<"not inserted"<<endl;
    }
    cout<<lexicon->getRedBlackTree().totalnodes(node)<<endl;
    cout<<lexicon->getRedBlackTree().blackheight(node)<<endl;
    std::vector<void(*)(Lexicon* lexicon)> unit_tests_list = {
        test_index_entry1,
        test_index_entry2,
        test_index_entry3,
        test_preorder,
        test_black_height,
        test_search,
        test_delete
    };
    int total = unit_tests_list.size();
     cout<<"prunnn"<<endl;
    for (int i = 0; i < total; ++i) {
        try {
            unit_tests_list[i](lexicon);
        } catch (const std::exception& e) {
            failed_tests++;
            std::cout << "Unit test " << i << " failure: " << e.what() << std::endl;
        }
    }

    if (failed_tests == 0) {
        std::cout << "All tests have passed successfully!" << std::endl;
    } else {
        std::cout << failed_tests << " tests failed!" << std::endl;
    }

    return failed_tests;
}
