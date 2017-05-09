#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdlib>
#include<algorithm>

using namespace std;

struct rpos{
	string read;
	string chrom; //reference chromosome where it maps
	int rs;//reference start
	int re;//reference end
	int len;
	bool operator < (const rpos& rp) const
        {
                return(chrom<rp.chrom) || ((chrom == rp.chrom) && (rs<rp.rs));
        }

};

struct sv{
	string cn; //chromosome name
	int st; //start coordinate
	int e;//end coordinate
	bool operator <(const sv& s) const
	{
		return(cn<s.cn)|| ((cn == s.cn) && (st<s.st));
	}
};

void findRead(vector<sv> & vs, vector<rpos> & vr); //reports reads overlapping a given interval

int main(int argc, char * argv[])
{
	if(argc <2)
	{
		cerr<<"Usage: "<<argv[0]<<" foo.filtered.m1 foo.tsv"<<endl;
		exit(EXIT_FAILURE);
	}
	
	vector<rpos> bmap; //bmap is blasr alignment result
	vector<sv> svmap;
	
	rpos temppos;
	sv tsv;

	string str;
	size_t pos,pos1;

	int loc;

	ifstream fin;
	//fin.open("a4.filtered.mito.m1");
	//fin.open("a4.a4asm.filtered.m1");
	fin.open(argv[1]);
	while(getline(fin,str))
	{
		pos = str.find(' ');
		temppos.read = str.substr(0,pos);
//cout<<str.substr(0,pos)<<"\t"<<endl;
		pos1 = str.find(' ',pos+1);
		temppos.chrom = str.substr(pos+1,pos1-pos-1);
//cout<<str.substr(pos+1,pos1-pos-1)<<"\t"<<endl;
		pos = str.find(' ',pos1+1);//next element
		loc = stoi(str.substr(pos1+1,pos-pos1-1));
		temppos.rs = loc;
//cout<<str.substr(pos1+1,pos-pos1-1)<<"\t"<<endl;
		pos1 = str.find(' ',pos+1); 
		loc = stoi(str.substr(pos+1,pos1-pos-1));
		temppos.re = loc;
//cout<<str.substr(pos+1,pos1-pos-1)<<"\t"<<endl;
		pos = str.find(' ',pos1+1);
		loc = stoi(str.substr(pos1+1,pos-pos1-1));
		temppos.len = loc;
//cout<<temppos.read<<" "<<temppos.chrom<<" "<<temppos.rs<<" "<<temppos.re<<" "<<temppos.len<<endl;		
		bmap.push_back(temppos);
//cout<<str.substr(pos1+1,pos-pos1-1)<<endl;
	
	}
	fin.close();	

	sort(bmap.begin(),bmap.end());
	
	//fin.open("foo.bed");//for the genomic intervals containing the SVs
	fin.open(argv[2]);
	while(getline(fin,str))
	{	
		pos = str.find(' ');	
//cout<<str.substr(0,pos)<<endl;	
		tsv.cn = str.substr(0,pos);
		pos1 = str.find(' ',pos+1);
		tsv.st = stoi(str.substr(pos+1,pos1-pos-1));
		pos = str.find(' ',pos1+1);
		tsv.e = stoi(str.substr(pos1+1,pos-pos1-1));
//cout<<tsv.cn<<" "<<tsv.st<<" "<<tsv.e<<endl;	
		svmap.push_back(tsv);
	}
	sort(svmap.begin(),svmap.end());		
	findRead(svmap,bmap);
		
return 0;
}


void findRead(vector<sv> & vs, vector<rpos> & vr)
{
	sv tsv;//temporary sv interval
	rpos trp;//temporary rpos
	for(unsigned int i=0;i<vs.size();i++) //from first to last sv interval
	{
		tsv = vs[i];
		for(unsigned int j=0;j<vr.size();j++)
		{
			trp = vr[j];
		
			if((tsv.cn == trp.chrom) && (tsv.st>trp.rs) && (tsv.e <trp.re))//if same chromosome and sv interval is contained within the read
			{
				cout<<tsv.cn<<" "<<tsv.st<<" "<<tsv.e<<" "<<trp.read<<" "<<trp.rs<<" "<<trp.re<<" "<<trp.re-trp.rs<<endl;
			}
		}
	}
}
