#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <zlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <sys/stat.h>
#include <sstream>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;
using namespace std;

long long filesize(string fname){
    ifstream i;
    long long size=0;
    char buffer[8192];
    i.open(fname.c_str(), ios::in);
    do{
      i.read(buffer, sizeof(buffer));
      size+=i.gcount();
    }while (i.gcount()>0);
    return size;
}

string compress (string fname, int mode ,string opath){
    ifstream i;
    long long usize=0, csize;
    double per;
    string fin;
    i.open(fname, ios::in | ios::binary );
    fname = fs::path(fname).filename().string();
    string ofile;
    ofile=opath+"/"+to_string(mode)+"_"+fname+".gz";
    string md="w"+to_string(mode)+"b";
    gzFile output = gzopen(ofile.c_str(), md.c_str());
    char buffer[8192];
    auto start = chrono::high_resolution_clock::now(); 
    do{
        i.read(buffer, sizeof(buffer));
        gzwrite(output, buffer, i.gcount());
        usize+=i.gcount();
    }while(i.gcount()>0);
    gzclose(output);
    auto stop = chrono::high_resolution_clock::now();
    i.close();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start); 
    csize = filesize(ofile);
    per = (usize-csize)*100.0/usize;
    fin=fname+"\t"+to_string(mode)+"\t"+to_string(usize)+"\t"+to_string(csize)+"\t"+to_string(per)+"\t"+to_string(duration.count())+"\n";
    return fin;
}


string decompress (string fname,string opath){
    char outbuffer[8192];
    gzFile infile = (gzFile)gzopen(fname.c_str(), "rb");
    vector<char> outfile;
    gzrewind(infile);
    auto start = chrono::high_resolution_clock::now(); 
    while(!gzeof(infile)){
        int len = gzread(infile, outbuffer, sizeof(outbuffer));
        outfile.insert(outfile.end(), outbuffer, outbuffer+len);
    }
    gzclose(infile);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start); 
    fname = fs::path(fname).filename().string();
    string ofile= opath+"/"+fname.substr(0,fname.length()-3);
    ofstream fout(ofile.c_str(), ios::out | ios::binary);
    fout.write((char*)&outfile[0], outfile.size() * sizeof(char));
    fout.close();

    string fin=fname+"\t"+to_string(duration.count())+"\n";
    return fin;
}

string compdir(fs::directory_iterator it,int mode,fs::path opath){
    string s="";
    for(;it!=fs::directory_iterator();++it){
        if(fs::is_directory(it->path())){
            fs::path topath=opath;
            topath/=it->path().filename();
            fs::create_directory(topath);
            if(!fs::is_empty(it->path())){
                s+=compdir(fs::directory_iterator(it->path()),mode,topath);
            }
        }
        else{
            s+=compress(it->path().string(),mode,opath.string());
        }
    }
    return s;
} 
  
string decompdir(fs::directory_iterator it,fs::path opath){
    string s="";
    for(;it!=fs::directory_iterator();++it){
        if(fs::is_directory(it->path())){
            fs::path topath=opath;
            topath/=it->path().filename();
            fs::create_directory(topath);
            if(!fs::is_empty(it->path())){
                s+=decompdir(fs::directory_iterator(it->path()),topath);
            }
        }
        else{
            s+=decompress(it->path().string(),opath.string());
        }
    }
    return s;
} 
    
  
    