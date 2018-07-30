////============================================================================
//// Name        : rock_paper_impl.cpp
//// Author      :
//// Version     :
//// Copyright   : Your copyright notice
//// Description : Hello World in C++, Ansi-style
////============================================================================
//
//#include <iostream>
//#include "Joker.h"
//#include <vector>
//#include <string.h>
//#include <fstream>
//#include <map>
//#include <typeinfo>
//
//using namespace std;
//
//vector<string> split(string str, string sep){
//    char* cstr=const_cast<char*>(str.c_str());
//    char* current;
//    vector<std::string> arr;
//    current=strtok(cstr,sep.c_str());
//    while(current != NULL){
//        arr.push_back(current);
//        current=strtok(NULL, sep.c_str());
//    }
//    return arr;
//}
//
//int main() {
//	cout << "Welcome, here we eat all blini possible" << endl; // prints !!!Hello World!!!
//	ifstream inf("test.txt");
//	string temp;
//	string del = " ";
//	for(; getline(inf, temp); ) {
//		vector<string> tarr = split(temp, del);
//		// cout << tarr << endl;
//		vector<string>::const_iterator it = tarr.begin();
//		for(; it != tarr.end(); ++it) {
//			cout << *it << ',';
//		}
//		cout << endl;
//	}
//	//std::map<BasicPiece, int> temp_map;
//	//temp_map[BasicPiece(PieceChar::BOMB, true)] = 3;
//	//temp_map[BasicPiece(PieceChar::ROCK, true)] = 4;
//	//temp_map[BasicPiece(PieceChar::FLAG, true)] = 5;
//	//temp_map[BasicPiece(PieceChar::SCISSORS, true)] = 15;
//	//temp_map[BasicPiece(PieceChar::PAPER, true)] = 34;
//	//temp_map[Joker(PieceChar::BOMB, true)] = 20;
//	//temp_map.insert(std::pair<BasicPiece, int>(BasicPiece(PieceChar::BOMB, true), 3));
//	//temp_map.insert(std::pair<BasicPiece, int>(BasicPiece(PieceChar::ROCK, true), 5));
//	//temp_map.insert(std::pair<BasicPiece, int>(BasicPiece(PieceChar::FLAG, true), 6));
//	if (!(BasicPiece(PieceChar::BOMB, true) == BasicPiece(PieceChar::ROCK, true))) {
//		std::cout << "fffffffffuuuuckkk" << std::endl;
//	}
//	//cout << temp_map.size() << endl;
//	//std::map<BasicPiece, int>::iterator it = temp_map.begin();
//	//for(; it != temp_map.end(); ++it) {
//	//	std::cout << it->first << " " << it->second << std::endl;
//	//}
//
////	std::vector<std::pair<BasicPiece, int> > temp_vec;
////	temp_vec.push_back(std::make_pair(BasicPiece(PieceChar::BOMB, true), 3));
////	temp_vec.push_back(std::make_pair(BasicPiece(PieceChar::ROCK, true), 4));
////	temp_vec.push_back(std::make_pair(BasicPiece(PieceChar::FLAG, true), 10));
////	temp_vec.push_back(std::make_pair(Joker(PieceChar::BOMB, true), 10));
////
////	//cout << typeid(BasicPiece(PieceChar::BOMB, true)) << endl;
////	//cout << typeid(Joker(PieceChar::BOMB, true)) << endl;
////
////	if (typeid(BasicPiece(PieceChar::BOMB, true)) == typeid(Joker(PieceChar::BOMB, true))) {
////		cout << "equal" << endl;
////	} else {
////		cout << "not" << endl;
////	}
////
//// 	std::vector<std::pair<BasicPiece, int> >::const_iterator it = temp_vec.begin();
////	for (; it != temp_vec.end(); ++it) {
////		cout << it->first << " " << it->second << endl;
////		const Joker* l_ptrJkr = dynamic_cast<const Joker*>(&it->first);
////		if (l_ptrJkr != NULL)
////		{
////			cout << "Yes" << endl;
////			//return false; // could not dynamic cast, therefore piece is not joker
////			//cout << " this is a joker mother fucker " << it->first << " " << it->second << endl;
////		}
////	}
//
//	int N = 10;
//	int M = 10;
//	BasicPiece p(PieceChar::EMPTY, true);
//	std::vector<std::vector<BasicPiece*> > temp_mat(N, std::vector<BasicPiece*>(M, &p));
//	std::vector<std::vector<BasicPiece*>>::const_iterator out_it = temp_mat.begin();
//	for (; out_it != temp_mat.end(); ++out_it) {
//		std::vector<BasicPiece*>::const_iterator inner_it = (*out_it).begin();
//		for (; inner_it != (*out_it).end(); ++inner_it) {
//			cout << (*inner_it)->getSymbol() << endl;
//		}
//		cout << "" << endl;
//	}
//
//	std::cout << "@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
//
//	BasicPiece p1(PieceChar::BOMB, true);
//	temp_mat[0][2] = &p1;
//	out_it = temp_mat.begin();
//	for (; out_it != temp_mat.end(); ++out_it) {
//		std::vector<BasicPiece*>::const_iterator inner_it = (*out_it).begin();
//		for (; inner_it != (*out_it).end(); ++inner_it) {
//			cout << (*inner_it)->getSymbol() << endl;
//		}
//		cout << "" << endl;
//	}
//
//	Joker p3(PieceChar::BOMB, true);
//	std::vector<std::pair<BasicPiece*, int> > temp_vec;
//	//temp_vec.push_back(std::make_pair(&BasicPiece(PieceChar::BOMB, true), 3));
//	//temp_vec.push_back(std::make_pair(&BasicPiece(PieceChar::ROCK, true), 4));
//	temp_vec.push_back(std::make_pair(&p1, 10));
//	temp_vec.push_back(std::make_pair(&p3, 10));
//
//	//cout << typeid(BasicPiece(PieceChar::BOMB, true)) << endl;
//	//cout << typeid(Joker(PieceChar::BOMB, true)) << endl;
//
//
// 	std::vector<std::pair<BasicPiece*, int> >::const_iterator it = temp_vec.begin();
//	for (; it != temp_vec.end(); ++it) {
//		cout << *(it->first) << " " << it->second << endl;
//		cout << (*(it->first)).getType() << endl;
//
//	}
//
//	//cout << temp_vec[&p3] << endl;
//
//
////	string del = "]";
////	vector<string>::iterator it = tarr.begin();
////	for(; it != tarr.end(); ++it) {
////		//cout << *it << ',';
////
////	}
////	cout << endl;
////	BasicPiece a('R');
////	std::cout << a << endl;
////	Joker b('S');
////	std::cout << b << endl;
////	Joker c('r');
////	bool equal = a==c;
////	std::cout << "IS rock equals rock" << endl;
////	std::cout << equal << endl;
////	bool equal2 = a==b;
////	std::cout << "IS rock equals  SCISSORS" << endl;
////	std::cout << equal2 << endl;
////	equal2 = a<b;
////	std::cout << "IS rock smaller THAN SCISSORS" << endl;
////	std::cout << equal2 << endl;
////	std::cout << "IS ROCK GREATER THAN SCISSORS" << endl;
////	equal = a>b;
////	std::cout << equal << endl;
////	std::cout << "IS something greater than itself?" << endl;
////	equal2 = a>c;
////	std::cout << equal2 << endl;
////	std::cout << "IS something smaller than itself?" << endl;
////	equal2 = a<c;
////	std::cout << equal2 << endl;
////	std::cout << "IS SCISSORS smaller THAN rock" << endl;
////	equal = b<a;
////	std::cout << equal << endl;
////	a = b;
////	std::cout << a << endl;
////	BasicPiece  d = b;
////	std::cout << d << endl;
////	b.setSymbol('B');
////	std::cout << b << endl;
//	return 0;
//}
