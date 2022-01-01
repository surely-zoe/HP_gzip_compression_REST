#include "stdafx.h"
#include "messagetypes.h"
#include "MyServer.h"
#include <iostream>
#include<string.h>
#include <cpprest/filestream.h>
#include<thread>
#include<boost/chrono.hpp>
#include <boost/thread/thread.hpp>
#include<unistd.h>
#include "multipart_parser.h"
#include "cmdm.h"
using namespace web; 
using namespace utility;
using namespace http;
using namespace web::http::experimental::listener;
using namespace concurrency::streams; 

MyServer::MyServer(utility::string_t url) : m_listener(url){
    m_listener.support(methods::GET, std::bind(&MyServer::handle_get, this, std::placeholders::_1));
}

void MyServer::handle_get(http_request message){
    long tid = pplx::details::platform::GetCurrentThreadId();
	//boost::this_thread::sleep_for(boost::chrono::milliseconds(10000));
	std::string cli = "client_"+ std::to_string(tid);
	fs::create_directory(fs::path(cli));

	auto path_val = uri::split_path(message.request_uri().path());
	std::string token;
	token = path_val[1];  

	MultipartParser p1; 
    p1.SetBody(message.extract_string(true).get());
    p1.SetBound(message.headers().content_type());
	std::vector<std::pair<std::string,std::vector<int>>> m = p1.GetBodyContent(cli);
	std::vector<pplx::task<std::string>> s;
	MultipartParser p2;
	std::string fname,ftype;
	fs::create_directory(fs::path(cli+"/send"));
	string fin="";
	if(token=="compress"){
		fin+="Filename\tMode\tUsize\tCsize\tPerR\tTime\n";
		for(int i=0;i<m.size();++i){			
			if(fs::is_directory(fs::path(cli+"/receive/"+m[i].first))){
				ftype="folder";
				for(int j=0;j<m[i].second.size();++j){
					s.push_back(pplx::task<std::string>([i,j,&m,cli]()-> std::string{ 
						fs::path p(cli+"/receive/"+m[i].first);
						std::string opath= cli+"/send/"+to_string(m[i].second[j])+"_"+m[i].first;
    					fs::create_directory(fs::path(opath));
						return compdir(fs::directory_iterator(p),m[i].second[j],fs::path(opath));
					}));
					p2.AddFile(ftype,to_string(m[i].second[j])+"_"+m[i].first);
				}				
			}
			else{
				ftype="file";
				for(int j=0;j<m[i].second.size();++j){					
					s.push_back(pplx::task<std::string>([i,j,&m,cli]()-> std::string{
					   fs::path p(cli+"/receive/"+m[i].first);
					   return compress(p.string(),m[i].second[j],cli+"/send");
					}));
					p2.AddFile(ftype,to_string(m[i].second[j])+"_"+m[i].first+".gz");
				}
			}
		}
	}
	else{
		fin+="Filename\tTime\n";
		for(int i=0;i<m.size();++i){			
			if(fs::is_directory(fs::path(cli+"/receive/"+m[i].first))){
				ftype="folder";
				s.push_back(pplx::task<std::string>([i,&m,cli]()-> std::string{ 
					fs::path p(cli+"/receive/"+m[i].first);
					std::string opath = cli+"/send/"+m[i].first;
    				fs::create_directory(fs::path(opath));				
					return decompdir(fs::directory_iterator(p),fs::path(opath));
				}));
				p2.AddFile(ftype,m[i].first);
			}
			else{
				ftype="file";
				s.push_back(pplx::task<std::string>([i,&m,cli]()-> std::string{
					fs::path p(cli+"/receive/"+m[i].first);
					return decompress(p.string(),cli+"/send");
				}));
				p2.AddFile(ftype,m[i].first.substr(0,m[i].first.length()-3));
			}			
		}		
	}
	for(int i=0;i<s.size();++i)
		fin+=s[i].get();
	p2.SetFileDetails(fin);
	std::string boundary = p2.boundary();
    std::string body = p2.GenBodyContent(cli);
	string del = "rm -rf " + cli;
	system(del.c_str());
	message.reply(status_codes::OK,body,U("multipart/form-data; boundary=" + boundary));
};