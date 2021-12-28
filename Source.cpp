#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include<iomanip>
#include<algorithm>
#include <bits/stdc++.h>

using namespace std;

struct web_page {
	string URL;
	double impressions;
	double CTR;
	double PR;
	double final_rank; //PR normalized
	double score;
	double clicks;
	int index;
	vector<string> Keywords;
	string appended_keywords;
	vector<int> inlinks; //indices of pages pointing to this page  

	web_page() {
		CTR = 0;
		PR = 0;
		score = 0;
		impressions = 0;
		index = 0;
		clicks = 0; // wlaa a3mel call le function t-intialize-oo ??????? see what will happen
		final_rank = 0;
	}
	bool correct_url(string url) {
		if (URL == url)
			return true;
		return false;
	}
};

int V; //number of vertcies(webpages)
int E; //number of edges
vector<web_page> pages(1);
//int iterations = 1;
vector <double> sorted_PR(V);
vector<string> links;
vector <int> displayed_pages; //indices of pages displayed in the search results
vector <double> displayed_scores;
vector <int> show; //have the updated sorted indices 
int pressed_button;
string key_word;

//function takes the url and returns the index
int search(string link) {

	for (int i =0; i< pages.size(); i++)
		if (pages[i].correct_url(link))
			return i;	
}

class WebGraph {
	int V; // total number of webpages (vertices)
	vector<web_page>* Hyberlinks; // vector of other webpage objects (Adjecency list) 
	vector<double> much_change;
	
public:
	WebGraph(int V) {
		this->V = V;
		Hyberlinks = new vector<web_page>[V];
		much_change.resize(V);
	}

	//Add hyberlink outgoing from webpage x to webpage y (i.e. x -> y)
	void Add_hyberlink(web_page p1, web_page p2) {
		Hyberlinks[p1.index].push_back(p2);
	}

	void Display_hyberlinks() {
		for (int i = 0; i < V; i++) {
			cout << i << "->";
			for (auto itr : Hyberlinks[i])
				cout << itr.index << "- " << itr.URL << "  ";
			cout << endl;
		}
	}
	
	void PageRank() {

		//cout << "this is the iteration number: " << iterations << endl;
		//iterations++;

		//boolean variable to indicate when the results of the page ranks become stable
		bool no_change = true;

		for (int i = 0; i < V; i++) much_change[i] = pages[i].PR;
		
		//calculating page rank for 1 iteration
		for (int i = 0; i < V; i++) {
			double new_val = 0;
			for (int j = 0; j < pages[i].inlinks.size(); j++) {

				new_val += (pages[pages[i].inlinks[j]].PR )/ (double) (Hyberlinks[pages[i].inlinks[j]].size());

			}
			pages[i].PR = new_val;
		}

		//we stop iterating when the numbers stop change significantly; i.e. there is no much change happening
		for (int i = 0; i < V; i++) {
			if (abs(much_change[i] - pages[i].PR) >= 0.001)
				no_change = false;
		}

		if (!no_change)
			PageRank();
		else {
			
			for (int i = 0; i < V; i++) sorted_PR[i] = pages[i].PR;
			sort(sorted_PR.begin(), sorted_PR.end()); //descendingly sorted

			//for (int i = 0; i < V; i++) cout << sorted_PR[i] << endl;
			
			vector <bool> checked(V, false);
			int count = 1;
			for (int i = 0; i < V; i++) {
				for (int j = 0; j < V; j++) {
					if (sorted_PR[i] == pages[j].PR && !checked[j]) {
						pages[j].final_rank = count;
						count++;
						checked[j] = true;
					}
				}
			}

			//for (int i = 0; i < V; i++)
			//	cout << pages[i].final_rank << "   " << setprecision(6) << pages[i].PR << endl;

			return;
		}
	}
};

void calculate_CTR() {
	for (int i = 0; i < V; i++) {
		pages[i].CTR = (pages[i].clicks / pages[i].impressions)*100.0;
		//cout << pages[i].CTR << endl;
	}

}
void calculate_score() {
	calculate_CTR();
	for (int i = 0; i < V; i++) {
		pages[i].score = (0.4 * pages[i].final_rank) +
			(0.6 * ((pages[i].final_rank * (1 - (0.1 * pages[i].impressions) / (1 + 0.1 * pages[i].impressions))) +
				(pages[i].CTR * ((0.1 * pages[i].impressions) / (1 + 0.1 * pages[i].impressions)))));
		//cout << pages[i].score <<endl;
	}
}
//arrange the displayed pages according to the score
void arrange_pages() {
	
	calculate_score();
	vector <bool> done(displayed_pages.size(), false);

	bool arranged = false;
	
	for (int i = 0; i < displayed_pages.size(); i++)
		displayed_scores[i] = pages[pages[displayed_pages[i]].index].score;
	
	int maximum = -1;
	while (!arranged)
	{
		double maximum = -1; 
		int max_idx = -1;
		for (int i = 0; i < displayed_pages.size(); i++) {
			if (displayed_scores[i] >= maximum && !done[i]) {
				maximum = displayed_scores[i];
				max_idx = i;
			}
		}
		done[max_idx] = true;
		show.push_back(pages[displayed_pages[max_idx]].index);

		if (show.size() == displayed_pages.size())
			arranged = true;
	}

}
void update_clicks_file() {
	fstream oldfile, newfile;

	// Open the existing file 
	oldfile.open("C:/Users/Dell/Desktop/Spring 2021/Algorithms Lab/Project/clicks.csv", ios::in);

	// Create a new file to store updated data
	newfile.open("C:/Users/Dell/Desktop/Spring 2021/Algorithms Lab/Project/clicks_new.csv", ios::out);

	if (!newfile.is_open()) {

		cout << "Error opening the clicks file to update it!\n";
		return;
	}
	else {

		for (int i = 0; i < V; i++)
			newfile << pages[i].clicks << endl;

	}

	oldfile.close();
	newfile.close();

	// removing the old existing file
	remove("C:/Users/Dell/Desktop/Spring 2021/Algorithms Lab/Project/clicks.csv");

	// renaming the updated file
	rename("C:/Users/Dell/Desktop/Spring 2021/Algorithms Lab/Project/clicks_new.csv",
		"C:/Users/Dell/Desktop/Spring 2021/Algorithms Lab/Project/clicks.csv");
}
void update_impressions_file() {
	fstream oldfile, newfile;

	// Open the existing file 
	oldfile.open("C:/Users/Dell/Desktop/Spring 2021/Algorithms Lab/Project/impr.csv", ios::in);

	// Create a new file to store updated data
	newfile.open("C:/Users/Dell/Desktop/Spring 2021/Algorithms Lab/Project/impr_new.csv", ios::out);

	if (!newfile.is_open()) {

		cout << "Error opening the impressions file to update it!\n";
		return;
	}
	else {

		for (int i = 0; i < V; i++){

			newfile << pages[i].URL << ',' << pages[i].impressions << endl;
		}
	}

	oldfile.close();
	newfile.close();

	// removing the old existing file
	remove("C:/Users/Dell/Desktop/Spring 2021/Algorithms Lab/Project/impr.csv");

	// renaming the updated file
	rename("C:/Users/Dell/Desktop/Spring 2021/Algorithms Lab/Project/impr_new.csv",
		"C:/Users/Dell/Desktop/Spring 2021/Algorithms Lab/Project/impr.csv");

}
void search_query(string entered_str) {
	string modified_str;
	string str1;
	string str2;
	int idx;

	if (entered_str[0] == '"' && entered_str[entered_str.length() - 1] == '"') {

		for (int i = 1; i < entered_str.length() - 1; i++) {
			modified_str += entered_str[i];
			//cout << modified_str;
		}
		for (int i = 0; i < V; i++)
			if (pages[i].appended_keywords.find(modified_str) < pages[i].appended_keywords.length())
				displayed_pages.push_back(i);
	}

	else if (entered_str.find("AND") < entered_str.length()) {
		idx = entered_str.find("AND");
		entered_str.erase(entered_str.find("AND"), 4);
		idx = entered_str.find(' ');
		for (int i = 0; i < idx; i++) str1 += entered_str[i];
		for (int i = idx + 1; i < entered_str.length(); i++) str2 += entered_str[i];

		for (int i = 0; i < V; i++)
			if (pages[i].appended_keywords.find(str1) < pages[i].appended_keywords.length() &&
				pages[i].appended_keywords.find(str2) < pages[i].appended_keywords.length()) {
				displayed_pages.push_back(i);
			}
	}

	else if (entered_str.find("OR") < entered_str.length()) {
		idx = entered_str.find("OR");
		entered_str.erase(entered_str.find("OR"), 3);
		idx = entered_str.find(' ');
		for (int i = 0; i < idx; i++) str1 += entered_str[i];
		for (int i = idx + 1; i < entered_str.length(); i++) str2 += entered_str[i];

		for (int i = 0; i < V; i++)
			if (pages[i].appended_keywords.find(str1) < pages[i].appended_keywords.length() ||
				pages[i].appended_keywords.find(str2) < pages[i].appended_keywords.length())
				displayed_pages.push_back(i);
	}
	else if (entered_str.find(' ') < entered_str.length()){
		idx = entered_str.find(' ');
		for (int i = 0; i < idx; i++) str1 += entered_str[i];
		for (int i = idx + 1; i < entered_str.length(); i++) str2 += entered_str[i];

		for (int i = 0; i < V; i++)
			if (pages[i].appended_keywords.find(str1) < pages[i].appended_keywords.length() ||
				pages[i].appended_keywords.find(str2) < pages[i].appended_keywords.length())
				displayed_pages.push_back(i);
	}
	else {
		for (int i = 0; i < V; i++)
			if (pages[i].appended_keywords.find(entered_str) < pages[i].appended_keywords.length())
				displayed_pages.push_back(i);
	}

	displayed_scores.resize(displayed_pages.size());

}

void search_engine() {
	cout << endl <<"Search results: \n";

	for (int i = 0; i < show.size(); i++) {
		cout << i + 1 << ". " << pages[show[i]].URL << " with score: "<< pages[show[i]].score << endl;
		pages[show[i]].impressions++;
	}
	update_impressions_file();

	cout << "Would you like to: \n" <<
		"1. " << "Choose a webpage to open\n" <<
		"2. " << "New search\n" <<
		"3. " << "Exit\n";
	cout << endl << "Type in your choice : ";
	cin >> pressed_button;
	
	if (pressed_button == 1) {
		cout << endl << "Enter page index: ";
		cin >> pressed_button;

			cout << endl << "You’re now viewing  " << pages[show[pressed_button - 1]].URL << endl << endl;
			pages[show[pressed_button - 1]].clicks++;
			update_clicks_file();

			cout << "Would you like to\n" <<
				"1. " << "Back to search results\n" <<
				"2. " << "New search\n" <<
				"3. " << "Exit\n";

			cout << endl << "Type in your choice : ";
			cin >> pressed_button;
		

		if (pressed_button == 1)
			search_engine();
		else if (pressed_button == 2) {
			show.clear();
			displayed_pages.clear();

			cout << "What do you want to search about? (Keyword) ";
			while (key_word.empty())
			{
				getline(cin, key_word);
			}
			search_query(key_word);
			key_word.clear();

			if (displayed_pages.size() == 0) {
				cout << "Error 404! the keyword does not exist!\n";
				return;
			}
			arrange_pages();
			search_engine();
		}
		else if (pressed_button == 3) {
			cout << "Thank you for using Iman's search engine!";
			return;
		}
		else {
			cout << "Invalid input! program terminated!\n";
			return;

		}
	
	}
	else if (pressed_button == 2) {
		show.clear();
		displayed_pages.clear();
		cout << "What do you want to search about? (Keyword) ";
		while (key_word.empty())
		{
			getline(cin, key_word);
		}
		search_query(key_word);
		key_word.clear();

		if (displayed_pages.size() == 0) {
			cout << "Error 404! the keyword does not exist!\n";
			return;
		}
		arrange_pages();
		search_engine();

	}
	else if (pressed_button == 3){
		cout << "Thank you for using Iman's search engine!";
		return;
	}else{
		cout << "Invalid input! program terminated!\n";
		return;
	}


}

void init_files() {
	ifstream Web_Graph_File("C:/Users/Dell/Desktop/Spring 2021/Algorithms Lab/Project/graph.csv");
	ifstream Keyword_File("C:/Users/Dell/Desktop/Spring 2021/Algorithms Lab/Project/key.csv");
	ifstream Impressions_File("C:/Users/Dell/Desktop/Spring 2021/Algorithms Lab/Project/impr.csv");
	ifstream Clicks_File("C:/Users/Dell/Desktop/Spring 2021/Algorithms Lab/Project/clicks.csv");


	string line;
	int i;


	if (!Keyword_File.is_open()) {
		cout << "error opening the Keyword_File! \n";
		return;
	}
	else {
		i = 0;
		while (getline(Keyword_File, line)) {
			stringstream data(line);
			getline(data, line, ',');
			pages[i].URL = line;
			pages[i].index = i;
			//int j = 0;
			while (getline(data, line, ',')) {
				pages[i].Keywords.push_back(line);
				pages[i].appended_keywords.append(line);
				//cout << pages[i].appended_keywords <<endl;
				//cout << i << "  " << pages[i].URL << " " << pages[i].index << pages[i].Keywords[j] << endl;
				//j++;
			}
			//cout << pages[i].appended_keywords << endl;
			i++;
			pages.resize(i + 1);
		}
	}

	Keyword_File.close();

	V = pages.size() - 1;
	pages.resize(V);
	sorted_PR.resize(V);

	//intializing all the pages ranks by 1/V
	for (i = 0; i < V; i++) pages[i].PR = 1 / (double)V;

	if (!Impressions_File.is_open()) {
		cout << "error opening the Impressions_File! \n";
		return;
	}
	else {
		i = 0;
		while (getline(Impressions_File, line)) {
			stringstream data(line);
			getline(data, line, ',');
			//cout << line << endl;
			getline(data, line);
			//cout << line << endl;
			pages[i].impressions = stoi(line);
			//cout << pages[i].impressions <<endl;
			i++;
		}
	}
	Impressions_File.close();

	if (!Web_Graph_File.is_open()) {
		cout << "error opening the Web_Graph_File! \n";
		return;
	}
	else {

		while (getline(Web_Graph_File, line)) {
			stringstream data(line);
			while (getline(data, line, ',')) {
				links.push_back(line);
			}
		}

	}
	Web_Graph_File.close();

	if (!Clicks_File.is_open()) {
		cout << "error opening the Clicks_File! \n";
		return;
	}
	else {

		while (getline(Clicks_File, line)) {
			for (int i = 0; i < V; i++){
				pages[i].clicks = stoi(line);
		}
	}

}
	Clicks_File.close();

	E = links.size();
	links.resize(E);


}

void testing() {

	WebGraph g(V);
	for (int i = 0; i < E; i = i + 2) {
		g.Add_hyberlink(pages[search(links[i])], pages[search(links[i + 1])]);
		pages[search(links[i + 1])].inlinks.push_back(search(links[i]));
	}

	//for (int i = 0; i < V; i++)
	//	for (int j = 0; j < pages[i].inlinks.size(); j++) cout << "page: "<< i << "  "<<pages[i].inlinks[j] << endl;

	//g.Display_hyberlinks();

	g.PageRank();
	calculate_score();

	
	cout << "Welcome!\n" << "What would you like to do ?\n" << 
		"1. " << "New search\n" << 
		"2. " << "Exit\n";
	cout << endl << "Type in your choice : ";
	cin >> pressed_button;

	if (pressed_button == 1) {

		cout << "What do you want to search about? (Keyword) ";
		while (key_word.empty())
		{
			getline(cin, key_word);
		}

		search_query(key_word);
		key_word.clear();

		if (displayed_pages.size() == 0) {
			cout << "Error 404! the keyword does not exist!\n";
			return;
		}
		arrange_pages();
		search_engine();

	}	
	else if (pressed_button == 2) {
		cout << "Thank you for using Iman's search engine!";
		return; //exit
	}
	else {
		cout << "Invalid input! program terminated!\n";
		return;

	}
}

int main() {

	init_files();
	testing();


	return 0;
}