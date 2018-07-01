#ifndef GAURD_basic_operations
#define GAURD_basic_operations


bool COMPARE(const vector<double> &v1,const vector<double> &v2){
	if(v1.size() != v2.size())
		return 0;
	
	for(size_t i(0);i<v1.size();++i)
		if(v1[i] != v2[i])
			return 0;
	
	return 1;
}


vector<string> split(const string &line,const char &separator){
	vector<string> ans;
	string::const_iterator i(line.begin()),j(line.begin());
	while(i!=line.end()){
		j=i;
		while(*j!=separator && j!=line.end())
			++j;
		string temp(i,j);
		ans.push_back(temp);
		
		i=j;
		if(i!=line.end())
			++i;
		if(j!=line.end() && i==line.end())
			ans.push_back(string(""));
	}
	
	return ans;
}

vector<string> split(const string &line,const char &separator,const size_t Q){
	// tested
	vector<string> ans(Q,"");
	size_t index(0);
	
	string::const_iterator i(line.begin()),j(line.begin());
	while(i!=line.end()){
		j=i;
		while(*j!=separator && j!=line.end())
			++j;
		string temp(i,j);
		ans[index]=temp;
		index += 1;
		if(index == Q)
			break;
		
		i=j;
		if(i!=line.end())
			++i;
		if(j!=line.end() && i==line.end()){
			ans[index]=temp;
			index += 1;
			if(index == Q)
				break;
		}
	}
	
	return ans;
}

void split(const string &line,const char &separator,vector<string> &ans){
	// tested
	const size_t Q( ans.size() );
	size_t index(0);
	
	string::const_iterator i(line.begin()),j(line.begin());
	while(i!=line.end()){
		j=i;
		while(*j!=separator && j!=line.end())
			++j;
		string temp(i,j);
		ans[index]=temp;
		index += 1;
		if(index == Q)
			break;
		
		i=j;
		if(i!=line.end())
			++i;
		if(j!=line.end() && i==line.end()){
			ans[index]=temp;
			index += 1;
			if(index == Q)
				break;
		}
	}
}


vector<string> split(const string &line){
	vector<string> ans;
	string::const_iterator i(line.begin()),j(line.begin());
	while(i!=line.end()){
		while(isspace(*i))
			++i;
		j=i;
		while(j!=line.end() && !isspace(*j))
			++j;
		string temp(i,j);
		if(temp.size()>0)
			ans.push_back(temp);
		i=j;
	}
	return ans;
}

template<class T>
ostream& operator<<(ostream &out,const vector<T> &V){
	if(V.size() > 0){
		for(size_t i(0);i<V.size()-1;++i)
			out<<V[i]<<",";
		out<<V[V.size()-1];
	}
	return out;
}

template<class T>
ostream& operator<<(ostream &out,const vector<vector<T> > &V){
	for(int i(0);i<V.size();++i)
		out<<V[i]<<"\n";
	return out;
}







#endif






























