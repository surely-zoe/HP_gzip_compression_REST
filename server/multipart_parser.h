#include <vector>
#include <string>
#include <tuple>
#include <map>
#include <cpprest/filestream.h>
#include <boost/filesystem.hpp>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include <algorithm>
#include <future>
#include <cpprest/containerstream.h>
namespace fs = boost::filesystem;

namespace web{
namespace http{
struct dirs{
  std::string dir="";
  std::vector<std::pair<std::string,unsigned long>> file; //fname and fsize
  std::vector<std::string> fcontent; 
  std::vector<dirs> subdirs;
};
class MultipartParser
{
public:
  MultipartParser(){
    boundary_ = GenBound();
  }
  inline const std::string body_content(){
    return body_content_;
  }
  inline const std::string boundary(){
    return boundary_;
  }
  inline void AddFile(const std::string &name, const std::string &value){
    files_.push_back(std::move(std::pair<std::string, std::string>(name,value)));
  }
  inline void SetFileDetails(std::string fdetails){
    fdetails_=fdetails;
  }
  
  std::string GenBodyContent(std::string);
  std::vector<std::pair<std::string,std::vector<int>>> GetBodyContent(std::string);
  inline void SetBody(std::string content){
    body_content_= content;
  }
  inline void SetBound(std::string mime){
    int c = mime.find("boundary");
    boundary_ = mime.substr(c+9);
  }
private:
  unsigned long long parse;
  std::string fdetails_;
  static const std::string boundary_prefix_;
  static const std::string rand_chars_;
  std::string boundary_;
  std::string body_content_;
  std::vector<std::pair<std::string, std::string>> files_;
  std::string GenBound();
  dirs GetDirs(fs::directory_iterator);
  std::string GetDirMeta(dirs d);  
  std::string GetDirData(dirs,std::string);
  dirs ParseDirMeta(std::string);
  dirs ParseDirData(dirs);
  void MakeDirs(fs::path,dirs);  
};

} //namespace web::http
} //namespace web
