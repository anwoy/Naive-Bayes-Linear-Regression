#ifndef GAURD_defs_2
#define GAURD_defs_2

#define THRESHOLD 1e-8
#define MAXITER 1000


double pupdate(const sumstatsconst &ssco,const sumstatsvarconst &ssvco,const sumstatsvar &ssvo,parameters &PO){
	const size_t Q( PO.W.size() );
	
	double lhood(0);
	{
		double lhood_C(0);
		for(size_t j(0);j<Q;++j){
			lhood_C += -0.5*(LOG_2 + LOG_PI + log(PO.V[j]))*ssco.auk[j];
			
			const double Thetavec[]={PO.W[j],PO.M[j]};
			const vector<double> Theta(Thetavec,Thetavec+2);
			const double term1( DOT(DOT(Theta,ssco.cross[j]),Theta) );
			const double term2( 2.0*DOT(Theta,ssco.domino[j]) );
			
			lhood_C += -0.5/PO.V[j]*(ssco.delta[j] + term1 - term2);
		}
		lhood_C += -0.5*(LOG_2 + LOG_PI +log(PO.LAMBDA))*ssco.Nus;
		lhood_C += -0.5/PO.LAMBDA*(ssco.swastika + PO.MU*PO.MU*ssco.Nus - 2.0*PO.MU*ssco.diamond);
		
		lhood += lhood_C;
	}
	{
		double lhood_V(0);
		for(size_t j(0);j<Q;++j){
			lhood_V += -0.5*(LOG_2 + LOG_PI + log(PO.V[j]))*ssvco.auk[j];
			lhood_V += -0.5/PO.V[j]*(ssvco.delta[j] + PO.M[j]*PO.M[j]*ssvco.auk[j] - 2.0*PO.M[j]*ssvco.del[j] );
		}
		lhood_V += -0.5*(LOG_2 + LOG_PI + log(PO.LAMBDA))*ssvco.Nus - 0.5/PO.LAMBDA*PO.MU*PO.MU*ssvco.Nus + ssvo.china;
		lhood += lhood_V;
	}
	
	vector<double> W(Q),M(Q),V(Q);
	double MU,LAMBDA;
	
	for(size_t j(0);j<Q;++j){
		const vector<vector<double> > LHSmat( ADD( ADD( EYE(2)*(1.0/Q0) , ssco.cross[j] ) , ssvo.cross[j] ) );
		const double Tvec[]={MU1_PRIOR , MU2_PRIOR};
		const vector<double> Tau(Tvec,Tvec+2);
		const vector<double> RHSmat( ADD( ADD( Tau*(1.0/Q0) , ssco.domino[j] ) , ssvo.domino[j] ) );
		
		const vector<double> temp( DOT( InvertMatrix( LHSmat ) , RHSmat ) );
		
		if(temp.size() != 2)
			throw(domain_error("ERROR1 in pupdate"));
		
		W[j] = temp[0];
		M[j] = temp[1];
	}
	
	{
		const double NUM( MU3_PRIOR/Q0 + ssco.diamond + ssvo.diamond );
		const double DEN( 1.0/Q0 + double(ssco.Nus) + double(ssvco.Nus) );
		MU = NUM/DEN;
	}
	
	for(size_t j(0);j<Q;++j){
		const double Tvec[]={MU1_PRIOR , MU2_PRIOR};
		const vector<double> Tau(Tvec,Tvec+2);
		const double Thetavec[]={W[j],M[j]};
		const vector<double> Theta(Thetavec,Thetavec+2);
		
		const double term1( (1.0/Q0)*DOT( ADD(Theta,(-1.0)*Tau) , ADD(Theta,(-1.0)*Tau) ) );
		const double term2( DOT( DOT(Theta , ADD(ssco.cross[j] , ssvo.cross[j]) ), Theta ) );
		const double term3( 2.0*DOT(Theta , ADD(ssco.domino[j] , ssvo.domino[j]) ) );
		
		const double NUM( 2.0*B_PRIOR + term1 + ssco.delta[j] + ssvco.delta[j] + term2 - term3 );
		const double DEN( ssco.auk[j] + ssvco.auk[j] + 2.0 + 2.0*(A_PRIOR + 1.0) );
		V[j] = NUM/DEN;
	}
	
	{
		const double NUM(2.0*B_PRIOR + (MU-MU3_PRIOR)*(MU-MU3_PRIOR)/Q0 + ssco.swastika + ssvo.swastika + MU*MU*(ssco.Nus + ssvco.Nus) - 2.0*MU*(ssco.diamond + ssvo.diamond));
		const double DEN(ssco.Nus + ssvco.Nus + 1.0 + 2.0*(A_PRIOR+1.0));
		LAMBDA = NUM/DEN;
	}
	
	
	for(size_t j(0);j<Q;++j){
		PO.W[j] = W[j];
		PO.M[j] = M[j];
		PO.V[j] = V[j];
		PO.MU = MU;
		PO.LAMBDA = LAMBDA;
	}
	
	
	return lhood;
}


double pupdateML(const sumstatsconst &ssco,const sumstatsvarconst &ssvco,const sumstatsvar &ssvo,parameters &PO){
	const size_t Q( PO.W.size() );
	
	double lhood(0);
	{
		double lhood_C(0);
		for(size_t j(0);j<Q;++j){
			lhood_C += -0.5*(LOG_2 + LOG_PI + log(PO.V[j]))*ssco.auk[j];
			
			const double Thetavec[]={PO.W[j],PO.M[j]};
			const vector<double> Theta(Thetavec,Thetavec+2);
			const double term1( DOT(DOT(Theta,ssco.cross[j]),Theta) );
			const double term2( 2.0*DOT(Theta,ssco.domino[j]) );
			
			lhood_C += -0.5/PO.V[j]*(ssco.delta[j] + term1 - term2);
		}
		lhood_C += -0.5*(LOG_2 + LOG_PI +log(PO.LAMBDA))*ssco.Nus;
		lhood_C += -0.5/PO.LAMBDA*(ssco.swastika + PO.MU*PO.MU*ssco.Nus - 2.0*PO.MU*ssco.diamond);
		
		lhood += lhood_C;
	}
	{
		double lhood_V(0);
		for(size_t j(0);j<Q;++j){
			lhood_V += -0.5*(LOG_2 + LOG_PI + log(PO.V[j]))*ssvco.auk[j];
			lhood_V += -0.5/PO.V[j]*(ssvco.delta[j] + PO.M[j]*PO.M[j]*ssvco.auk[j] - 2.0*PO.M[j]*ssvco.del[j] );
		}
		lhood_V += -0.5*(LOG_2 + LOG_PI + log(PO.LAMBDA))*ssvco.Nus - 0.5/PO.LAMBDA*PO.MU*PO.MU*ssvco.Nus + ssvo.china;
		lhood += lhood_V;
	}
	
	vector<double> W(Q),M(Q),V(Q);
	double MU,LAMBDA;
	
	for(size_t j(0);j<Q;++j){
		const vector<vector<double> > LHSmat( ADD( ssco.cross[j] , ssvo.cross[j] ) );
		//const double Tvec[]={MU1_PRIOR , MU2_PRIOR};
		//const vector<double> Tau(Tvec,Tvec+2);
		const vector<double> RHSmat( ADD( ssco.domino[j] , ssvo.domino[j] ) );
		
		const vector<double> temp( DOT( InvertMatrix( LHSmat ) , RHSmat ) );
		
		if(temp.size() != 2)
			throw(domain_error("ERROR1 in pupdate"));
		
		W[j] = temp[0];
		M[j] = temp[1];
	}
	
	{
		const double NUM( ssco.diamond + ssvo.diamond );
		const double DEN( double(ssco.Nus) + double(ssvco.Nus) );
		MU = NUM/DEN;
	}
	
	for(size_t j(0);j<Q;++j){
		//const double Tvec[]={MU1_PRIOR , MU2_PRIOR};
		//const vector<double> Tau(Tvec,Tvec+2);
		const double Thetavec[]={W[j],M[j]};
		const vector<double> Theta(Thetavec,Thetavec+2);
		
		//const double term1( (1.0/Q0)*DOT( ADD(Theta,(-1.0)*Tau) , ADD(Theta,(-1.0)*Tau) ) );
		const double term2( DOT( DOT(Theta , ADD(ssco.cross[j] , ssvo.cross[j]) ), Theta ) );
		const double term3( 2.0*DOT(Theta , ADD(ssco.domino[j] , ssvo.domino[j]) ) );
		
		const double NUM( ssco.delta[j] + ssvco.delta[j] + term2 - term3 );
		const double DEN( ssco.auk[j] + ssvco.auk[j] );
		V[j] = NUM/DEN;
	}
	
	{
		const double NUM( ssco.swastika + ssvo.swastika + MU*MU*(ssco.Nus + ssvco.Nus) - 2.0*MU*(ssco.diamond + ssvo.diamond));
		const double DEN( ssco.Nus + ssvco.Nus );
		LAMBDA = NUM/DEN;
	}
	
	
	for(size_t j(0);j<Q;++j){
		PO.W[j] = W[j];
		PO.M[j] = M[j];
		PO.V[j] = V[j];
		PO.MU = MU;
		PO.LAMBDA = LAMBDA;
	}
	
	
	return lhood;
}





void learnML(const string &predfilename,const string &Ofilename,const string &parameters_savefile){
	// this function only woks with .dat binary files
	const NQ NQO(predfilename);
	cout<<NQO;
	vector<double> O(NQO.N);
	readO(Ofilename,O);
	
	ifstream fin(predfilename.c_str(), ios::in | ios::binary);
	const sumstatsconst SSCO(fin,O);
	const sumstatsvarconst SSVCO(fin,O,SSCO.UO);
	const size_t MAXiter(MAXITER);
	
	cout<<"const sumstats calculated\n";
	
	sumstatsvar SSVO;
	parameters PO(NQO.Q);
	vector<double> LHOODs(0);
	double diff(0);
	size_t noiterations(0);
	while(noiterations < 2 || diff > THRESHOLD){
		SSVO.compute(fin,O,SSCO.UO,PO);
		//const double prior( priorcontribution(PO) );
		const double LHOOD( pupdateML(SSCO,SSVCO,SSVO,PO) );
		if(LHOODs.size() > 0){
			const double lastval( LHOODs[ LHOODs.size()-1 ] );
			diff = abs(lastval - LHOOD);
		}
		LHOODs.push_back(LHOOD);
		noiterations += 1;
		if(noiterations > MAXiter)
			break;
		if( noiterations % 1 == 0 ){
			cout<<noiterations<<" ";
			cout.flush();
		}
	}
	cout<<"\n";
	
	fin.close();
	ofstream fout(parameters_savefile.c_str() , ios::out | ios::binary);
	savedata(PO,LHOODs,fout);
	fout.close();
}

void learnML(const string &predfilename,const string &Ofilename,const string &parameters_initialfile,const string &parameters_savefile){
	// this function only woks with .dat binary files
	const NQ NQO(predfilename);
	cout<<NQO;
	vector<double> O(NQO.N);
	readO(Ofilename,O);
	
	ifstream fin(predfilename.c_str(), ios::in | ios::binary);
	const sumstatsconst SSCO(fin,O);
	const sumstatsvarconst SSVCO(fin,O,SSCO.UO);
	const size_t MAXiter(MAXITER);
	
	cout<<"const sumstats calculated\n";
	
	sumstatsvar SSVO;
	parameters PO;
	vector<double> LHOODs(0);
	{
		ifstream fintemp(parameters_initialfile.c_str() , ios::in | ios::binary);
		loaddata(PO,LHOODs,fintemp);
		fintemp.close();
	}
	double diff(0);
	size_t noiterations(0);
	while(noiterations < 2 || diff > THRESHOLD){
		SSVO.compute(fin,O,SSCO.UO,PO);
		//const double prior( priorcontribution(PO) );
		const double LHOOD( pupdateML(SSCO,SSVCO,SSVO,PO) );
		if(LHOODs.size() > 0){
			const double lastval( LHOODs[ LHOODs.size()-1 ] );
			diff = abs(lastval - LHOOD);
		}
		LHOODs.push_back(LHOOD);
		noiterations += 1;
		if(noiterations > MAXiter)
			break;
		if( noiterations % 1 == 0){
			cout<<noiterations<<" ";
			cout.flush();
		}
	}
	cout<<"\n";
	
	fin.close();
	ofstream fout(parameters_savefile.c_str() , ios::out | ios::binary);
	savedata(PO,LHOODs,fout);
	fout.close();
}


void learnMAP(const string &predfilename,const string &Ofilename,const string &parameters_savefile){
	// this function only woks with .dat binary files
	const NQ NQO(predfilename);
	cout<<NQO;
	vector<double> O(NQO.N);
	readO(Ofilename,O);
	
	ifstream fin(predfilename.c_str(), ios::in | ios::binary);
	const sumstatsconst SSCO(fin,O);
	const sumstatsvarconst SSVCO(fin,O,SSCO.UO);
	const size_t MAXiter(MAXITER);
	
	cout<<"const sumstats calculated\n";
	
	sumstatsvar SSVO;
	parameters PO(NQO.Q);
	vector<double> MAPs(0);
	double diff(0);
	size_t noiterations(0);
	while(noiterations < 2 || diff > THRESHOLD){
		SSVO.compute(fin,O,SSCO.UO,PO);
		const double prior( priorcontribution(PO) );
		const double MAP( prior + pupdate(SSCO,SSVCO,SSVO,PO) );
		if(MAPs.size() > 0){
			const double lastval( MAPs[ MAPs.size()-1 ] );
			diff = abs(lastval - MAP);
		}
		MAPs.push_back(MAP);
		noiterations += 1;
		if(noiterations > MAXiter)
			break;
		if( noiterations % 1 == 0){
			cout<<noiterations<<" ";
			cout.flush();
		}
	}
	cout<<"\n";
	
	fin.close();
	ofstream fout(parameters_savefile.c_str() , ios::out | ios::binary);
	savedata(PO,MAPs,fout);
	fout.close();
}

void learnMAP(const string &predfilename,const string &Ofilename,const string &parameters_initialfile,const string &parameters_savefile){
	// this function only woks with .dat binary files
	const NQ NQO(predfilename);
	cout<<NQO;
	vector<double> O(NQO.N);
	readO(Ofilename,O);
	
	ifstream fin(predfilename.c_str(), ios::in | ios::binary);
	const sumstatsconst SSCO(fin,O);
	const sumstatsvarconst SSVCO(fin,O,SSCO.UO);
	const size_t MAXiter(MAXITER);
	
	cout<<"const sumstats calculated\n";
	
	sumstatsvar SSVO;
	parameters PO;
	vector<double> MAPs(0);
	{
		ifstream fintemp(parameters_initialfile.c_str() , ios::in | ios::binary);
		loaddata(PO,MAPs,fintemp);
		fintemp.close();
	}
	double diff(0);
	size_t noiterations(0);
	while(noiterations < 2 || diff > THRESHOLD){
		SSVO.compute(fin,O,SSCO.UO,PO);
		const double prior( priorcontribution(PO) );
		const double MAP( prior + pupdate(SSCO,SSVCO,SSVO,PO) );
		if(MAPs.size() > 0){
			const double lastval( MAPs[ MAPs.size()-1 ] );
			diff = abs(lastval - MAP);
		}
		MAPs.push_back(MAP);
		noiterations += 1;
		if(noiterations > MAXiter)
			break;
		if( noiterations % 1 == 0){
			cout<<noiterations<<" ";
			cout.flush();
		}
	}
	cout<<"\n";
	
	fin.close();
	ofstream fout(parameters_savefile.c_str() , ios::out | ios::binary);
	savedata(PO,MAPs,fout);
	fout.close();
}



void predict(const string &predfilename,const string &OUTfilename,const string &parameters_filename){
	parameters PO;
	vector<double> MAPs;
	{
		ifstream fintemp(parameters_filename.c_str(), ios::in | ios::binary);
		loaddata(PO,MAPs,fintemp);
		fintemp.close();
	}
	
	ifstream fin(predfilename.c_str(), ios::in | ios::binary);
	ofstream fout(OUTfilename.c_str());
	fout.precision(12);
	size_t N,Q;
	fin.read((char*)&N,sizeof(size_t));
	fin.read((char*)&Q,sizeof(size_t));
	cout<<N<<"\t"<<Q<<"\n";
	vector<double> row(Q);
	for(size_t i(0);i<N;++i){
		for(size_t j(0);j<Q;++j)
			fin.read((char*)&( row[j] ),sizeof(double));
		//cout<<row<<"\n";
		const ABvals ABVO(PO,row);
		const double A(ABVO.A),B(ABVO.B);
		const double mu( B/A ),sd( pow(1.0/A , 0.5) );
		fout<< mu - sd <<"\t"<< mu <<"\t"<< mu + sd <<"\t\t:"<< sd <<"\n";
	}
}

void displayMO(const string &MOdatfile){
	parameters PO;
	vector<double> MAPs;
	ifstream fin(MOdatfile.c_str(), ios::in | ios::binary);
	loaddata(PO,MAPs,fin);
	cout.precision(20);
	cout<<MAPs<<"\n";
	cout<<PO;
}


#endif




























