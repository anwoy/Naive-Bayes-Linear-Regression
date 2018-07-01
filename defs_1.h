#ifndef GAURD_defs_1
#define GAURD_defs_1

#define PI 3.14159265359
#define LOG_PI 1.1447298858494002
#define LOG_2 0.69314718055994529

#define Q0 1000000.0
#define A_PRIOR 1.0
#define B_PRIOR 1.0
#define MU1_PRIOR 0.0
#define MU2_PRIOR 0.0
#define MU3_PRIOR 0.0



struct parameters{
	vector<double> W,M,V;
	double MU,LAMBDA;
	
	parameters(const string &filename) { readdata(filename); }
	parameters(const size_t &Q) { initialize(Q); }
	parameters() {}
	
	void initialize(const size_t &);
	void readdata(const string &);
	
	void datatester() const;
	
	void binary_writer(const string &) const;
	void binary_reader(const string &);
	
	void binary_writer(ofstream &) const;
	void binary_reader(ifstream &);
};


void parameters::binary_writer(const string &outfile) const{
	datatester();
	ofstream fout(outfile.c_str(), ios::out | ios::binary);
	const size_t Q( W.size() );
	fout.write((char*)&Q,sizeof(size_t));
	
	for(size_t j(0);j<Q;++j){
		fout.write((char*)&W[j],sizeof(double));
		fout.write((char*)&M[j],sizeof(double));
		fout.write((char*)&V[j],sizeof(double));
	}
	
	fout.write((char*)&MU,sizeof(double));
	fout.write((char*)&LAMBDA,sizeof(double));
}

void parameters::binary_reader(const string &infile){
	ifstream fin(infile.c_str());
	size_t Q;
	fin.read((char*)&Q,sizeof(size_t));
	W = vector<double>(Q);
	M = vector<double>(Q);
	V = vector<double>(Q);
	for(size_t j(0);j<Q;++j){
		fin.read((char*)&W[j],sizeof(size_t));
		fin.read((char*)&M[j],sizeof(size_t));
		fin.read((char*)&V[j],sizeof(size_t));
	}
	
	fin.read((char*)&MU,sizeof(double));
	fin.read((char*)&LAMBDA,sizeof(double));
}

void parameters::binary_writer(ofstream &fout) const{
	datatester();
	const size_t Q( W.size() );
	fout.write((char*)&Q,sizeof(size_t));
	
	for(size_t j(0);j<Q;++j){
		fout.write((char*)&W[j],sizeof(double));
		fout.write((char*)&M[j],sizeof(double));
		fout.write((char*)&V[j],sizeof(double));
	}
	
	fout.write((char*)&MU,sizeof(double));
	fout.write((char*)&LAMBDA,sizeof(double));
}

void parameters::binary_reader(ifstream &fin){
	size_t Q;
	fin.read((char*)&Q,sizeof(size_t));
	W = vector<double>(Q);
	M = vector<double>(Q);
	V = vector<double>(Q);
	for(size_t j(0);j<Q;++j){
		fin.read((char*)&W[j],sizeof(double));
		fin.read((char*)&M[j],sizeof(double));
		fin.read((char*)&V[j],sizeof(double));
	}
	
	fin.read((char*)&MU,sizeof(double));
	fin.read((char*)&LAMBDA,sizeof(double));
}


bool operator==(const parameters &O1,const parameters &O2){
	O1.datatester();
	O2.datatester();
	
	if(!(O1.W == O2.W))
		return 0;
	if(!(O1.M == O2.M))
		return 0;
	if(!(O1.V == O2.V))
		return 0;
	if(O1.MU != O2.MU)
		return 0;
	if(O1.LAMBDA != O2.LAMBDA)
		return 0;
	
	return 1;
}


void parameters::datatester() const {
	const size_t Q( W.size() );
	if(M.size() != Q)
		throw(domain_error("ERROR1 in parameters::datatester"));
	if(V.size() != Q)
		throw(domain_error("ERROR2 in parameters::datatester"));
	
	for(size_t i(0);i<Q;++i)
		if(V[i] <= 0){
			cout<<"i="<<i<<"\n";
			throw(domain_error("ERROR3 in parameters::datatester"));
		}
	
	if(LAMBDA <= 0)
		throw(domain_error("ERROR4 in parameters::datatester"));
	
	//cout<<"all tests passed!!\n";
}


void parameters::initialize(const size_t &Q){
	W = vector<double>(Q);
	M = vector<double>(Q);
	V = vector<double>(Q);
	srand(time(NULL));
	for(size_t i(0);i<Q;++i){
		double temp;
		W[i] = rand()*1.0/RAND_MAX-0.5;
		M[i] = rand()*1.0/RAND_MAX-0.5;
		V[i] = rand()*1.0/RAND_MAX;
	}
	
	MU = rand()*1.0/RAND_MAX-0.5;;
	LAMBDA = rand()*1.0/RAND_MAX;
}



void parameters::readdata(const string &filename){
	ifstream fin(filename.c_str());
	string line;
	getline(fin,line);
	getline(fin,line);
	getline(fin,line);
	
	vector<string> split_line( split(line,',') );
	W = vector<double>(split_line.size());
	for(size_t i(0);i<split_line.size();++i)
		W[i] = atof( split_line[i].c_str() );
	
	getline(fin,line);
	getline(fin,line);
	
	split_line = split(line,',');
	M = vector<double>(split_line.size());
	for(size_t i(0);i<split_line.size();++i)
		M[i] = atof( split_line[i].c_str() );
	
	getline(fin,line);
	getline(fin,line);
	
	split_line = split(line,',');
	V = vector<double>(split_line.size());
	for(size_t i(0);i<split_line.size();++i)
		V[i] = atof( split_line[i].c_str() );
	
	getline(fin,line);
	
	split_line = split(line);
	MU = atof( split_line[split_line.size()-1].c_str() );
	
	getline(fin,line);
	split_line = split(line);
	LAMBDA = atof( split_line[split_line.size()-1].c_str() );
	
}


ostream& operator<<(ostream &out,const parameters &O){
	out<<"Q="<<O.W.size()<<"\n";
	out<<"W:\n";
	out<<O.W<<"\n";
	out<<"M:\n";
	out<<O.M<<"\n";
	out<<"V:\n";
	out<<O.V<<"\n";
	out<<"mu = "<<O.MU<<"\n";
	out<<"LAMBDA = "<<O.LAMBDA<<"\n";
}


struct ABvals{
	double A,B;
	ABvals(const parameters &,const vector<double> &);
	//ABvals() {}
};

ABvals::ABvals(const parameters &PO,const vector<double> &row){
	A = 1.0/PO.LAMBDA;
	B = PO.MU/PO.LAMBDA;
	const size_t Q( row.size() );
	
	if(PO.W.size() != Q)
		throw(domain_error("ERROR1 in ABvals::ABvals"));
	for(size_t j(0);j<Q;++j){
		if(!isnan(row[j])){
			A += PO.W[j]*PO.W[j]/PO.V[j];
			B += PO.W[j]/PO.V[j]*(row[j]-PO.M[j]);
		}
	}
}

ostream& operator<<(ostream &out,const ABvals &O){
	cout<<O.A<<"\t"<<O.B;
	return out;
}

bool operator==(const ABvals &O1,const ABvals &O2){
	if(O1.A == O2.A && O1.B == O2.B)
		return 1;
	else
		return 0;
}

size_t nancounter(const vector<double> &row){
	// tested
	size_t nancount(0);
	for(size_t j(0);j<row.size();++j)
		if(isnan(row[j]))
			nancount += 1;
	return nancount;
}

double priorcontribution(const parameters &PO){
	double lhood(0);
	const size_t Q( PO.W.size() );
	for(size_t j(0);j<Q;++j)
		lhood += -0.5*(LOG_2+LOG_PI+log(Q0)+log(PO.V[j]))*2.0 - 0.5/Q0/PO.V[j]*pow(PO.W[j]-MU1_PRIOR,2.0) - 0.5/Q0/PO.V[j]*pow(PO.M[j]-MU2_PRIOR,2.0) - (A_PRIOR+1.0)*log(PO.V[j]) - B_PRIOR/PO.V[j];
	lhood += -0.5*(LOG_2+LOG_PI+log(Q0)+log(PO.LAMBDA)) - 0.5/Q0/PO.LAMBDA*pow(PO.MU-MU3_PRIOR,2.0) - (A_PRIOR+1.0)*log(PO.LAMBDA) - B_PRIOR/PO.LAMBDA;
}


size_t getQ(const string &PREDfile){
	ifstream fin(PREDfile.c_str());
	string line;
	getline(fin,line);
	getline(fin,line);
	return atoi(line.c_str());
}

size_t getN(const string &PREDfile){
	ifstream fin(PREDfile.c_str());
	string line;
	getline(fin,line);
	return atoi(line.c_str());
}

///////////////

struct NQ{
	size_t N,Q;
	void getvaldat(const string &);
	void getvaltext(const string &);
	
	NQ(const string &filename) { getvaldat(filename); }
	NQ() {}
};

void NQ::getvaldat(const string &filename){
	ifstream fin(filename.c_str(), ios::in | ios::binary);
	fin.read((char*)&N,sizeof(size_t));
	fin.read((char*)&Q,sizeof(size_t));
}

void NQ::getvaltext(const string &filename){
	ifstream fin(filename.c_str());
	fin>>N>>Q;
}

ostream& operator<<(ostream &out,const NQ &NQO){
	out<< NQO.N <<"\n"<< NQO.Q <<"\n";
	return out;
}

void readO(const string &filename,vector<double> &O){
	ifstream fin( filename.c_str() );
	const size_t N( O.size() );
	for(size_t i(0);i<N;++i){
		string val;
		fin>>val;
		O[i] = atof( val.c_str() );
	}
}

struct sumstatsconst{
	vector<vector<vector<double> > > cross;
	vector<vector<double> > domino;
	vector<double> delta;
	vector<double> auk;
	double swastika;
	double diamond;
	size_t Nus;
	vector<double> del;
	vector<size_t> UO;
	
	void initialize_memory(const size_t &);
	void compute(ifstream &,const vector<double> &);
	
	void crossupdate(const vector<double> &,const double &);
	void dominoupdate(const vector<double> &,const double &);
	void deltaupdate(const vector<double> &);
	void aukupdate(const vector<double> &);
	void delupdate(const vector<double> &);
	
	sumstatsconst(ifstream &fin,const vector<double> &O) { compute(fin,O); }
	sumstatsconst() {}
};

ostream& operator<<(ostream &out,const sumstatsconst &O){
	const size_t Q( O.cross.size() );
	out<<"SSC:\n";
	out<<"cross:\n";
	for(size_t j(0);j<Q;++j)
		out<<O.cross[j]<<"\n";
	out<<"domino:\n";
	cout<<O.domino;
	out<<"delta:\n";
	out<<O.delta<<"\n";
	out<<"auk:\n";
	out<<O.auk<<"\n";
	out<<"swastika="<<O.swastika<<"\n";
	out<<"diamond="<<O.diamond<<"\n";
	out<<"Nus="<<O.Nus<<"\n";
	out<<"del:\n";
	out<<O.del<<"\n";
	out<<"UO:\n";
	out<<O.UO<<"\n";
	
	return out;
}

void sumstatsconst::initialize_memory(const size_t &Q){
	cross = vector<vector<vector<double> > >(Q , vector<vector<double> >(2,vector<double>(2,0)) );
	domino = vector<vector<double> >(Q,vector<double>(2,0));
	delta = vector<double>(Q,0);
	auk = vector<double>(Q,0);
	swastika = 0;
	diamond = 0;
	Nus = 0;
	del = vector<double>(Q,0);
	UO = vector<size_t>(0);
}

void sumstatsconst::crossupdate(const vector<double> &row,const double &O){
	const size_t Q( row.size() );
	if(cross.size() != Q)
		throw(domain_error("ERROR1 in sumstatsconst::crossupdate"));
	
	for(size_t j(0);j<Q;++j){
		vector<vector<double> > &val( cross[j] );
		if(val.size() != 2 || val[0].size() != 2 || val[1].size() != 2)
			throw(domain_error("ERROR2 in sumstatsconst::crossupdate"));
		
		if(!isnan(row[j])){
			val[0][0] += O*O;
			val[0][1] += O;
			val[1][0] += O;
			val[1][1] += 1;
		}
	}
}

void sumstatsconst::dominoupdate(const vector<double> &row,const double &O){
	const size_t Q( row.size() );
	if(domino.size() != Q)
		throw(domain_error("ERROR1 in sumstatsconst::dominoupdate"));
	
	for(size_t j(0);j<Q;++j){
		vector<double> &val( domino[j] );
		if(val.size() != 2)
			throw(domain_error("ERROR2 in sumstatsconst::dominoupdate"));
		
		if(!isnan(row[j])){
			val[0] += row[j]*O;
			val[1] += row[j];
		}
	}
}

void sumstatsconst::deltaupdate(const vector<double> &row){
	const size_t Q( row.size() );
	if(delta.size() != Q)
		throw(domain_error("ERROR1 in sumstatsconst::deltaupdate"));
	
	for(size_t j(0);j<Q;++j){
		if(!isnan(row[j]))
			delta[j] += row[j]*row[j];
	}
}

void sumstatsconst::aukupdate(const vector<double> &row){
	const size_t Q( row.size() );
	if(auk.size() != Q)
		throw(domain_error("ERROR1 in sumstatsconst::aukupdate"));
	
	for(size_t j(0);j<Q;++j){
		if(!isnan(row[j]))
			auk[j] += 1;
	}
}

void sumstatsconst::delupdate(const vector<double> &row){
	const size_t Q( row.size() );
	if(del.size() != Q)
		throw(domain_error("ERROR1 in sumstatsconst::delupdate"));
	
	for(size_t j(0);j<Q;++j){
		if(!isnan(row[j]))
			del[j] += row[j];
	}
}


void sumstatsconst::compute(ifstream &fin,const vector<double> &O){
	//cout<<"running sumstatsconst::compute\n";
	fin.seekg(0,ios::beg);
	size_t N,Q;
	fin.read((char*)&N,sizeof(size_t));
	fin.read((char*)&Q,sizeof(size_t));
	initialize_memory(Q);
	
	vector<double> row(Q);
	
	for(size_t i(0);i<N;++i){
		for(size_t j(0);j<Q;++j)
			fin.read((char*)&( row[j] ),sizeof(double));
		const size_t nancount( nancounter(row) );
		if(!(nancount==Q && isnan(O[i]))){
			if(!isnan(O[i])){
				crossupdate(row,O[i]);
				dominoupdate(row,O[i]);
				deltaupdate(row);
				aukupdate(row);
				swastika += O[i]*O[i];
				diamond += O[i];
				Nus += 1;
				delupdate(row);
			}
			else
				UO.push_back(i);
		}
		else{
			//cout<<i<<"\n";
		}
	}
	
}

struct sumstatsvarconst{
	vector<double> delta;
	vector<double> auk;
	size_t Nus;
	vector<double> del;
	
	void initialize_memory(const size_t &);
	void compute(ifstream &,const vector<double> &,const vector<size_t> &);
	
	void deltaupdate(const vector<double> &);
	void aukupdate(const vector<double> &);
	void delupdate(const vector<double> &);
	
	sumstatsvarconst(ifstream &fin,const vector<double> &O,const vector<size_t> &UO) { compute(fin,O,UO); }
	sumstatsvarconst() {}
};

void sumstatsvarconst::initialize_memory(const size_t &Q){
	
	if(delta.size() != Q)
		delta = vector<double>(Q,0);
	else
		for(size_t j(0);j<Q;++j)
			delta[j] = 0;
	
	if(auk.size() != Q)
		auk = vector<double>(Q,0);
	else
		for(size_t j(0);j<Q;++j)
			auk[j] = 0;
	
	Nus = 0;
	
	if(del.size() != Q)
		del = vector<double>(Q,0);
	else
		for(size_t j(0);j<Q;++j)
			del[j] = 0;
	
}


void sumstatsvarconst::deltaupdate(const vector<double> &row){
	const size_t Q( row.size() );
	if(delta.size() != Q)
		throw(domain_error("ERROR1 in sumstatsvarconst::deltaupdate"));
	
	for(size_t j(0);j<Q;++j){
		if(!isnan(row[j]))
			delta[j] += row[j]*row[j];
	}
}

void sumstatsvarconst::aukupdate(const vector<double> &row){
	const size_t Q( row.size() );
	if(auk.size() != Q)
		throw(domain_error("ERROR1 in sumstatsvarconst::aukupdate"));
	
	for(size_t j(0);j<Q;++j){
		if(!isnan(row[j]))
			auk[j] += 1;
	}
}


void sumstatsvarconst::delupdate(const vector<double> &row){
	const size_t Q( row.size() );
	if(del.size() != Q)
		throw(domain_error("ERROR1 in sumstatsvarconst::delupdate"));
	
	for(size_t j(0);j<Q;++j){
		if(!isnan(row[j]))
			del[j] += row[j];
	}
}


void sumstatsvarconst::compute(ifstream &fin,const vector<double> &O,const vector<size_t> &UO){
	//cout<<"running sumstatsvarconst::compute\n";
	fin.seekg(0,ios::beg);
	size_t N,Q;
	fin.read((char*)&N,sizeof(size_t));
	fin.read((char*)&Q,sizeof(size_t));
	initialize_memory(Q);
	
	vector<double> row(Q);
	
	for(size_t i(0);i<UO.size();++i){
		const size_t index(UO[i]);
		const size_t offset(2*sizeof(size_t) + index*Q*sizeof(double));
		if(!isnan(O[index]))
			throw(domain_error("ERROR2 in sumstatsvarconst::compute"));
		
		fin.seekg(offset,ios::beg);
		for(size_t j(0);j<Q;++j)
			fin.read((char*)&( row[j] ),sizeof(double));
		
		const size_t nancount( nancounter(row) );
		if(nancount == Q)
			throw(domain_error("ERROR3 in sumstatsvarconst::compute"));
		
		//cout<<row<<"         "<<"nancount="<<nancount<<"\n";
		
		deltaupdate(row);
		aukupdate(row);
		Nus += 1;
		delupdate(row);
	}
}


struct sumstatsvar{
	vector<vector<vector<double> > > cross;
	vector<vector<double> > domino;
	//vector<double> delta;
	//vector<double> auk;
	double swastika;
	double diamond;
	//size_t Nus;
	//vector<double> del;
	double china;
	
	void initialize_memory(const size_t &);
	void compute(ifstream &,const vector<double> &,const vector<size_t> &,const parameters &);
	
	void crossupdate(const vector<double> &,const ABvals &);
	void dominoupdate(const vector<double> &,const ABvals &);
};

void sumstatsvar::initialize_memory(const size_t &Q){
	if(cross.size() != Q)
		cross = vector<vector<vector<double> > >(Q , vector<vector<double> >(2,vector<double>(2,0)) );
	else
		for(size_t j(0);j<Q;++j){
			vector<vector<double> > &val( cross[j] );
			if(val.size() != 2 || val[0].size() != 2 || val[1].size() != 2)
				throw(domain_error("cross error1"));
			val[0][0] = 0;
			val[0][1] = 0;
			val[1][0] = 0;
			val[1][1] = 0;
		}
	
	if(domino.size() != Q)
		domino = vector<vector<double> >(Q,vector<double>(2,0));
	else
		for(size_t j(0);j<Q;++j){
			vector<double> &val( domino[j] );
			if(val.size() != 2)
				throw(domain_error("domino error1"));
			val[0] = 0;
			val[1] = 0;
		}
	
	swastika = 0;
	diamond = 0;
	
	china = 0;
}

void sumstatsvar::crossupdate(const vector<double> &row,const ABvals &ABVO){
	const size_t Q( row.size() );
	if(cross.size() != Q)
		throw(domain_error("ERROR1 in sumstatsvar::crossupdate"));
	
	const double A(ABVO.A),B(ABVO.B);
	
	for(size_t j(0);j<Q;++j){
		vector<vector<double> > &val( cross[j] );
		if(val.size() != 2 || val[0].size() != 2 || val[1].size() != 2)
			throw(domain_error("ERROR2 in sumstatsvar::crossupdate"));
		
		if(!isnan(row[j])){
			val[0][0] += 1.0/A+B*B/A/A;
			val[0][1] += B/A;
			val[1][0] += B/A;
			val[1][1] += 1.0;
		}
	}
}


void sumstatsvar::dominoupdate(const vector<double> &row,const ABvals &ABVO){
	const size_t Q( row.size() );
	if(domino.size() != Q)
		throw(domain_error("ERROR1 in sumstatsvar::dominoupdate"));
	
	const double A(ABVO.A),B(ABVO.B);
	
	for(size_t j(0);j<Q;++j){
		vector<double> &val( domino[j] );
		if(val.size() != 2)
			throw(domain_error("ERROR2 in sumstatsvar::dominoupdate"));
		
		if(!isnan(row[j])){
			val[0] += row[j]*B/A;
			val[1] += row[j];
		}
		
	}
}



void sumstatsvar::compute(ifstream &fin,const vector<double> &O,const vector<size_t> &UO,const parameters &PO){
	//cout<<"running sumstatsvar::compute\n";
	fin.seekg(0,ios::beg);
	size_t N,Q;
	fin.read((char*)&N,sizeof(size_t));
	fin.read((char*)&Q,sizeof(size_t));
	initialize_memory(Q);
	
	vector<double> row(Q);
	
	if(PO.W.size() != Q)
		throw(domain_error("ERROR1 in sumstatsvar::compute"));
	
	PO.datatester();
	
	for(size_t i(0);i<UO.size();++i){
		const size_t index(UO[i]);
		const size_t offset(2*sizeof(size_t) + index*Q*sizeof(double));
		if(!isnan(O[index]))
			throw(domain_error("ERROR2 in sumstatsvar::compute"));
		
		fin.seekg(offset,ios::beg);
		for(size_t j(0);j<Q;++j)
			fin.read((char*)&( row[j] ),sizeof(double));
		
		const size_t nancount( nancounter(row) );
		if(nancount == Q)
			throw(domain_error("ERROR3 in sumstatsvar::compute"));
		
		//cout<<row<<"         "<<"nancount="<<nancount<<"\n";
		
		const ABvals ABVO(PO,row);
		const double A(ABVO.A),B(ABVO.B);
		
		crossupdate(row,ABVO);
		dominoupdate(row,ABVO);
		swastika += 1.0/A + B*B/A/A;
		diamond += B/A;
		china += 0.5*(LOG_2 + LOG_PI - log(A)) + B*B/2.0/A;
	}
	
}



//////////////


struct wrapper{
	vector<vector<double> > pred;
	vector<double> O;
	
	void readpred(const string &);
	void readO(const string &);
	
	wrapper() {}
	wrapper(const string &predfile,const string &Ofile) { readpred(predfile); readO(Ofile); }
	
	void datatester() const;
};


void wrapper::datatester() const {
	if(pred.size() != O.size())
		throw(domain_error("ERROR1 in wrapper::datatester"));
	
	for(size_t i(1);i<pred.size();++i)
		if(pred[i].size() != pred[0].size())
			throw(domain_error("ERROR2 in wrapper::datatester"));
}

void wrapper::readO(const string &filename){
	ifstream fin(filename.c_str());
	O = vector<double>(0);
	while(!fin.eof()){
		string line;
		getline(fin,line);
		if(line.size()>0){
			O.push_back(atof(line.c_str()));
		}
	}
}

void wrapper::readpred(const string &filename){
	const size_t N( getN(filename) ),Q( getQ(filename) );
	pred = vector<vector<double> >(N,vector<double>(Q));
	ifstream fin(filename.c_str());
	int CRAP;
	fin>>CRAP>>CRAP;
	string val;
	for(size_t i(0);i<N;++i){
		for(size_t j(0);j<Q;++j){
			fin>>val;
			pred[i][j] = atof( val.c_str() );
		}
	}
}

double lhoodcalc(const wrapper &WO,const parameters &PO){
	const vector<vector<double> > &pred( WO.pred );
	const vector<double> &O( WO.O );
	const size_t Q(pred[0].size());
	
	double lhood(0);
	for(size_t i(0);i<O.size();++i){
		//cout<<"mark\n";cout.flush();
		
		const vector<double> &row( pred[i] );
		const size_t nancount( nancounter(row) );
		
		if(!( nancount == Q && isnan(O[i]) )){
			if(!isnan(O[i])){
				for(size_t j(0);j<Q;++j)
					if(!isnan(row[j]))
						lhood += -0.5*(LOG_2+LOG_PI+log(PO.V[j])) - 0.5/PO.V[j]*pow(row[j]-PO.M[j]-PO.W[j]*O[i],2.0);
				lhood += -0.5*(LOG_2+LOG_PI+log(PO.LAMBDA)) - 0.5/PO.LAMBDA*pow(O[i]-PO.MU,2.0);
			}
			else{
				const ABvals ABVO(PO,row);
				const double A(ABVO.A),B(ABVO.B);
				for(size_t j(0);j<Q;++j)
					if(!isnan(row[j]))
						lhood += -0.5*(LOG_2+LOG_PI+log(PO.V[j])) - 0.5/PO.V[j]*pow(row[j]-PO.M[j],2.0);
				lhood += -0.5*(LOG_2+LOG_PI+log(PO.LAMBDA)) - 0.5/PO.LAMBDA*pow(PO.MU,2.0);
				lhood += 0.5*(LOG_2+LOG_PI-log(A)) + B*B/2.0/A; // yes, it's + 0.5(...) not -0.5(...)
			}
		}
	}
	
	return lhood;
}


///////////

vector<vector<double> > WMcalc(const wrapper &WO,const parameters &PO){
	const vector<vector<double> > &pred( WO.pred );
	const vector<double> &O( WO.O );
	const size_t Q(pred[0].size());
	
	vector<vector<vector<double> > > LHSmat(Q,vector<vector<double> >(EYE(2)*(1.0/Q0)));
	const double Lvecmat[]={MU1_PRIOR,MU2_PRIOR};
	const vector<double> Lvec(Lvecmat,Lvecmat+2);
	vector<vector<double> > RHSmat(Q,Lvec*(1.0/Q0));
	
	for(size_t i(0);i<O.size();++i){
		const vector<double> &row( pred[i] );
		const size_t nancount( nancounter(row) );
		
		
		if(!( nancount == Q && isnan(O[i]) )){
			if(!isnan(O[i])){
				for(size_t j(0);j<Q;++j){
					if(!isnan(row[j])){
						LHSmat[j][0][0] += O[i]*O[i];
						LHSmat[j][0][1] += O[i];
						LHSmat[j][1][0] += O[i];
						LHSmat[j][1][1] += 1.0;
						
						RHSmat[j][0] += row[j]*O[i];
						RHSmat[j][1] += row[j];
					}
				}
			}
			else{
				const ABvals ABVO(PO,row);
				const double A(ABVO.A),B(ABVO.B);
				
				for(size_t j(0);j<Q;++j){
					if(!isnan(row[j])){
						LHSmat[j][0][0] += 1.0/A+B*B/A/A;
						LHSmat[j][0][1] += B/A;
						LHSmat[j][1][0] += B/A;
						LHSmat[j][1][1] += 1.0;
						
						RHSmat[j][0] += row[j]*B/A;
						RHSmat[j][1] += row[j];
					}
				}
			}
		}
	}
	
	vector<double> W(Q),M(Q);
	for(size_t j(0);j<Q;++j){
		const vector<vector<double> > temp( InvertMatrix( LHSmat[j] ) );
		const vector<double> temp2( DOT(temp,RHSmat[j]) );
		//const vector<double> temp2( TWODsolver(LHSmat[j],RHSmat[j]) );
		if(temp2.size() != 2)
			throw(domain_error("ERROR_temp2"));
		W[j] = temp2[0];
		M[j] = temp2[1];
	}
	
	vector<vector<double> > ans(2);
	ans[0] = W;
	ans[1] = M;
	
	if(ans.size() != 2 || ans[0].size() != Q || ans[1].size() != Q)
		throw(domain_error("ERROR in WMcalc"));
	
	return ans;
}


double MUcalc(const wrapper &WO,const parameters &PO){
	const vector<vector<double> > &pred( WO.pred );
	const vector<double> &O( WO.O );
	const size_t Q(pred[0].size());
	
	double MUnum(MU3_PRIOR/Q0);
	double MUden(1.0/Q0);
	
	for(size_t i(0);i<O.size();++i){
		const vector<double> &row( pred[i] );
		const size_t nancount( nancounter(row) );
		
		if(!( nancount == Q && isnan(O[i]) )){
			MUden += 1;
			if(!isnan(O[i]))
				MUnum += O[i];
			else{
				ABvals ABVO(PO,row);
				const double A(ABVO.A),B(ABVO.B);
				
				MUnum += B/A;
			}
		}
	}
	
	const double MU(MUnum/MUden);
	
	return MU;
	
}

vector<double> Vcalc(const wrapper &WO,const parameters &PO,const vector<double> &W,const vector<double> &M){
	const vector<vector<double> > &pred( WO.pred );
	const vector<double> &O( WO.O );
	const size_t Q(pred[0].size());
	
	if(W.size() != Q || M.size() != Q)
		throw(domain_error("ERROR1 in Vcalc"));
	
	
	vector<double> Vden(Q,2.0+2.0*(A_PRIOR+1.0));
	vector<double> Vnum(Q);
	for(size_t j(0);j<Q;++j)
		Vnum[j] = pow(W[j]-MU1_PRIOR,2.0)/Q0+pow(M[j]-MU2_PRIOR,2.0)/Q0+2.0*B_PRIOR;
	
	for(size_t i(0);i<O.size();++i){
		const vector<double> &row( pred[i] );
		const size_t nancount( nancounter(row) );
		
		if(!( nancount == Q && isnan(O[i]) )){
			if(!isnan(O[i])){
				for(size_t j(0);j<Q;++j){
					if(!isnan(row[j])){
						Vden[j] += 1.0;
						Vnum[j] += pow(row[j]-W[j]*O[i]-M[j],2.0);
					}
				}
			}
			else{
				ABvals ABVO(PO,row);
				const double A(ABVO.A),B(ABVO.B);
				for(size_t j(0);j<Q;++j){
					if(!isnan(row[j])){
						Vden[j] += 1.0;
						Vnum[j] += row[j]*row[j] + W[j]*W[j]*(1.0/A+B*B/A/A) + M[j]*M[j] - 2.0*row[j]*W[j]*B/A + 2.0*W[j]*B/A*M[j] - 2.0*row[j]*M[j];
					}
				}
			}
		}
	}
	
	vector<double> V(Q);
	for(size_t j(0);j<Q;++j)
		V[j] = Vnum[j]/Vden[j];
	
	return V;
}

double LAMBDAcalc(const wrapper &WO,const parameters &PO,const double &MU){
	const vector<vector<double> > &pred( WO.pred );
	const vector<double> &O( WO.O );
	const size_t Q(pred[0].size());
	
	double LAMBDAden(1.0+2.0*(A_PRIOR+1.0));
	double LAMBDAnum(2.0*B_PRIOR + pow(MU-MU3_PRIOR,2.0)/Q0);
	for(size_t i(0);i<O.size();++i){
		const vector<double> &row( pred[i] );
		const size_t nancount( nancounter(row) );
		
		if(!( nancount == Q && isnan(O[i]) )){
			LAMBDAden += 1;
			if(!isnan(O[i]))
				LAMBDAnum += pow(O[i]-MU,2.0);
			else{
				ABvals ABVO(PO,row);
				const double A(ABVO.A),B(ABVO.B);
				LAMBDAnum += 1.0/A + B*B/A/A + MU*MU - 2.0*MU*B/A;
			}
		}
	}
	
	const double LAMBDA( LAMBDAnum/LAMBDAden );
	return LAMBDA;
}


parameters Pupdate_sectional(const wrapper &WO,const parameters &PO){
	
	const vector<vector<double> > WM( WMcalc(WO,PO) );
	const vector<double> &W( WM[0] );
	const vector<double> &M( WM[1] );
	const double MU( MUcalc(WO,PO) );
	const vector<double> V( Vcalc(WO,PO,W,M) );
	const double LAMBDA( LAMBDAcalc(WO,PO,MU) );
	
	
	
	parameters Onew;
	Onew.W = W;
	Onew.M = M;
	Onew.MU = MU;
	Onew.V = V;
	Onew.LAMBDA = LAMBDA;
	
	return Onew;
}

///////////

ofstream& savedata(const parameters &PO,const vector<double> &MAPs,ofstream &fout){
	PO.binary_writer(fout);
	const size_t L( MAPs.size() );
	fout.write((char*)&L,sizeof(size_t));
	for(size_t i(0);i<L;++i)
		fout.write((char*)&MAPs[i],sizeof(double));
	
	return fout;
}

ifstream& loaddata(parameters &PO,vector<double> &MAPs,ifstream &fin){
	PO.binary_reader(fin);
	size_t Lnew;
	fin.read((char*)&Lnew,sizeof(size_t));
	MAPs = vector<double>(Lnew);
	for(size_t i(0);i<Lnew;++i)
		fin.read((char*)&MAPs[i],sizeof(double));
	
	return fin;
}


void convert_to_binary(const string &Fin,const string &Fout){
	ifstream fin(Fin.c_str());
	ofstream fout(Fout.c_str(), ios::out | ios::binary);
	size_t N,Q;
	fin>>N>>Q;
	cout<<N<<"\t"<<Q<<"\n";
	fout.write((char*)&N,sizeof(size_t));
	fout.write((char*)&Q,sizeof(size_t));
	for(size_t i(0);i<N*Q;++i){
		string val;
		fin>>val;
		const double num( atof(val.c_str()) );
		fout.write((char*)&num,sizeof(double));
	}
}

void convert_to_text(const string &Fin,const string &Fout){
	ifstream fin(Fin.c_str(), ios::in | ios::binary);
	ofstream fout(Fout.c_str());
	size_t N,Q;
	fin.read((char*)&N,sizeof(size_t));
	fin.read((char*)&Q,sizeof(size_t));
	cout<<N<<"\n"<<Q<<"\n";
	fout.precision(12);
	fout<<N<<"\n"<<Q<<"\n";
	for(size_t i(0);i<N;++i){
		for(size_t j(0);j<Q-1;++j){
			double val;
			fin.read((char*)&val,sizeof(double));
			fout<<val<<" ";
		}
		{
			double val;
			fin.read((char*)&val,sizeof(double));
			fout<<val<<"\n";
		}
	}
}


#endif



















