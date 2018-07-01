#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <time.h>


#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/lu.hpp>


using namespace std;
#include "basic_operations.h"
#include "matrix_operations.h"
#include "defs_1.h"
#include "defs_2.h"





int main(int argc,char *argv[]){
	
	if(argc>1){
		if(string(argv[1])==string("--convert_to_binary")){
			if(argc == 4){
				const string Fin(argv[2]);
				const string Fout(argv[3]);
				convert_to_binary(Fin,Fout);
			}
			else{
				cout<<"ERROR: wrong number of arguments for this option\n";
				cout<<"usage:\n";
				cout<<"nblr --convert_to_binary <textfile> <binarydatfilename>\n";
			}
			return 0;
		}
		
		if(string(argv[1])==string("--convert_to_text")){
			if(argc == 4){
				const string Fin(argv[2]);
				const string Fout(argv[3]);
				convert_to_text(Fin,Fout);
			}
			else{
				cout<<"ERROR: wrong number of arguments for this option\n";
				cout<<"usage:\n";
				cout<<"nblr --convert_to_text <binarydatfile> <textfilename>\n";
			}
			return 0;
		}
		
		if(string(argv[1])==string("--learnML")){
			if(argc == 5){
				const string preddatfile(argv[2]) , Otxtfile(argv[3]) , MOdatfile(argv[4]);
				learnML(preddatfile,Otxtfile,MOdatfile);
			}
			else
				if(argc == 6){
					const string preddatfile(argv[2]) , Otxtfile(argv[3]) , MOdatfile_init(argv[4]) , MOdatfile_save(argv[5]);
					learnML(preddatfile,Otxtfile,MOdatfile_init,MOdatfile_save);
				}
				else{
					cout<<"ERROR: wrong number of arguments for this option\n";
					cout<<"usage:\n";
					cout<<"nblr --learnML <preddatfile> <Otxtfile> <MOdatfiletosavein>\n";
					cout<<"nblr --learnML <preddatfile> <Otxtfile> <MOdatfileinitial> <MOdatfiletosavein>\n";
				}
			return 0;
		}
		
		if(string(argv[1])==string("--learnMAP")){
			if(argc == 5){
				const string preddatfile(argv[2]) , Otxtfile(argv[3]) , MOdatfile(argv[4]);
				learnMAP(preddatfile,Otxtfile,MOdatfile);
			}
			else
				if(argc == 6){
					const string preddatfile(argv[2]) , Otxtfile(argv[3]) , MOdatfile_init(argv[4]) , MOdatfile_save(argv[5]);
					learnMAP(preddatfile,Otxtfile,MOdatfile_init,MOdatfile_save);
				}
				else{
					cout<<"ERROR: wrong number of arguments for this option\n";
					cout<<"usage:\n";
					cout<<"nblr --learnMAP <preddatfile> <Otxtfile> <MOdatfiletosavein>\n";
					cout<<"nblr --learnMAP <preddatfile> <Otxtfile> <MOdatfileinitial> <MOdatfiletosavein>\n";
				}
			return 0;
		}
		
		if(string(argv[1])==string("--predict")){
			if(argc == 5){
				const string preddatfile(argv[2]) , Onewtxtfile(argv[3]) , MOdatfile(argv[4]);
				predict(preddatfile,Onewtxtfile,MOdatfile);
			}
			else{
				cout<<"ERROR: wrong number of arguments for this option\n";
				cout<<"usage:\n";
				cout<<"nblr --predict <preddatfile> <Onewtxtfilename> <MOdatfile>\n";
			}
			
			return 0;
		}
		
		if(string(argv[1])==string("--displayMO")){
			if(argc == 3){
				displayMO(string(argv[2]));
			}
			else{
				cout<<"ERROR: wrong number of arguments for this option\n";
				cout<<"usage:\n";
				cout<<"nblr --displayMO <MOdatfile>\n";
			}
			return 0;
		}
		
		{
			cout<<"usage:\n";
			cout<<"nblr --convert_to_binary <textfile> <binarydatfilename>\n";
			cout<<"nblr --convert_to_text <binarydatfile> <textfilename>\n";
			cout<<"nblr --learnML <preddatfile> <Otxtfile> <MOdatfiletosavein>\n";
			cout<<"nblr --learnML <preddatfile> <Otxtfile> <MOdatfileinitial> <MOdatfiletosavein>\n";
			cout<<"nblr --learnMAP <preddatfile> <Otxtfile> <MOdatfiletosavein>\n";
			cout<<"nblr --learnMAP <preddatfile> <Otxtfile> <MOdatfileinitial> <MOdatfiletosavein>\n";
			cout<<"nblr --predict <preddatfile> <Onewtxtfilename> <MOdatfile>\n";
			cout<<"nblr --displayMO <MOdatfile>\n";
			return 0;
		}
	}
	else{
		cout<<"usage:\n";
		cout<<"nblr --convert_to_binary <textfile> <binarydatfilename>\n";
		cout<<"nblr --convert_to_text <binarydatfile> <textfilename>\n";
		cout<<"nblr --learnML <preddatfile> <Otxtfile> <MOdatfiletosavein>\n";
		cout<<"nblr --learnML <preddatfile> <Otxtfile> <MOdatfileinitial> <MOdatfiletosavein>\n";
		cout<<"nblr --learnMAP <preddatfile> <Otxtfile> <MOdatfiletosavein>\n";
		cout<<"nblr --learnMAP <preddatfile> <Otxtfile> <MOdatfileinitial> <MOdatfiletosavein>\n";
		cout<<"nblr --predict <preddatfile> <Onewtxtfilename> <MOdatfile>\n";
		cout<<"nblr --displayMO <MOdatfile>\n";
		return 0;
	}
	
	
	
	return 0;
}








