#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

struct state{
	vector<string> list;
	string current;
};

bool dist(string first, string second){	//Check to see if a word is adjacent to another word
	int diff=0;
	if(first.length() != second.length() ){
		return false;		//returns 2 so simply so it does not recoginze it as an adjacent word
	}
	for(unsigned int i=0; i<first.length(); ++i){
		if(first[i] != second[i]){
			++diff;
		}
	}
	if(diff == 1){
		return true;
	}
	return false;
}

vector<string> genList(string word){
	vector<string> newList;
	for(unsigned int i=0; i<word.length(); ++i){
		for(unsigned int j=0; j<26; ++j){
			string tempWord=word;
			tempWord[i]=j+'a';
			if(tempWord != word){
				newList.push_back(tempWord);
			}
		}
	}
	return newList;
}

vector<string> solve(string start, string end, unordered_set<string>list){
	queue<state>ladder;						//words to explore
	unordered_set<string> tested;			//words that have been explored
	state first;
	first.list={};
	first.current=start;
	ladder.push(first);
	while(!ladder.empty()){					//if there are still words to explore
		state tempstate=ladder.front();
		string current=tempstate.current;			//the current word to be checked
		vector<string> templadder=tempstate.list;	//the path the curent word has taken
		ladder.pop();
		tested.insert(current);					//add a word to explored set to prevent extra work
		if(dist(end,current)){					//if the current word is one away from the end
			templadder.push_back(current);
			templadder.push_back(end);
			return templadder;
		}
		vector<string> newList=genList(current);				//find all possible combinations of words that are one off of current
		for(unsigned int i=0; i<newList.size(); ++i){
			if(list.find(newList[i]) != list.end()){			//if the word is in the passed in list
				if(tested.find(newList[i])==tested.end()){	//if the word has not be added to the queue yet
					tested.insert(current);	
					state newstate;
					newstate.current=newList[i];
					newstate.list=templadder;
					newstate.list.push_back(current);
					ladder.push(newstate);
				}
			}
		}
	}
	return {};		//return an empty vector if no valid ladder was found
}

int main(int argc, char *argv[]){
//end if argc does not equal 4
	if(argc != 4){
		cout<<"Argc is not 4\n";
		return -1;
	}

//check if the two words are the same length
	string first=argv[1];
	string second=argv[2];
	if(first.length() != second.length()){
		cout<<argv[1]<< " is not the same length as " << argv[2]<<endl;
		return -2;
	}

//open the file and read them into a list
	unordered_set<string> list;
	ifstream dict(argv[3]);
	if(!dict.is_open()){
		cout<<"The file " << argv[3] << "could not be opened\n";
		return -3;
	}
	else{
		string temp;
		while(getline(dict,temp)){
			if(temp.length()==first.length()){
				list.insert(temp);
			}
		}
	}
//find a ladder and print it if there is one
	if(first==second){
		cout<<first<<endl<<second<<endl;
		return 0;
	}
	vector<string>ladder=solve(first,second,list);
	if(!ladder.empty()){
		for(unsigned int i=0; i<ladder.size(); ++i){
			cout<<ladder[i]<<endl;
		}
	}
	else{
		cout<<"There was no valid ladder between "<<first<<" and "<<second<<endl;
	}
	return 0;
}
