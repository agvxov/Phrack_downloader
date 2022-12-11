/*
	 This header is meant to be a framework for project where links must be pattern matched,
	followed and downloaded from a site.
	  Further optimazations are required.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <regex>
#include <string>
#include <vector>
#include <fstream>
#include <curl/curl.h>

//	size_t store(char *buffer, size_t size, size_t n, void* v);
//	std::string site_text(const char* site){
//	template<typename T, typename S> size_t findall(T &t, S source, const char* pattern){
//	template<typename T> size_t site_findall(T &t, const char* site, const char* pattern){
//	template<typename T> size_t dllist(const T &t){

namespace bot{

	const char href[] = R"d(.*href=["'](.*)["'].*)d";

	size_t store(char *buffer, size_t size, size_t n, void* v);
	std::string site_text(const char* site);
	template<typename T> size_t findall(T &t, const char* source, const char* pattern);
	template<typename T> size_t site_findall(T &t, const char* site, const char* pattern);
	template<typename T> size_t dllist(const T &t);
	template<typename T> size_t dlrellist(const std::string &domain, const T &t);

	size_t store(char *buffer, size_t size, size_t n, void *v){
		*((std::string*)v) += buffer;
		return size*n;
	}

	std::string site_text(const char* site){
		std::string buffer;

		auto c = curl_easy_init();
		if(!c){	throw 1; }
		curl_easy_setopt(c, CURLOPT_URL, site);
		curl_easy_setopt(c, CURLOPT_WRITEFUNCTION, store);
		curl_easy_setopt(c, CURLOPT_WRITEDATA, (void*)&buffer);
		curl_easy_perform(c);

		return buffer;
	}

	template<typename T, typename S> size_t findall(T &t, S source, const char* pattern){
		std::string s = source;

		std::regex r(pattern);
		std::sregex_iterator begin(s.begin(), s.end(), r);
		std::sregex_iterator end;

		for(auto i = begin; i != end; i++){
			t.push_back((*i)[1]);
		}

		return t.size();
	}

	template<typename T> size_t site_findall(T &t, const char* site, const char* pattern){
		return findall(t, site_text(site).c_str(), pattern);
	}

	template<typename T> size_t dllist(const T &t){
		std::ofstream output;
		std::string buffer;

		auto cd = curl_easy_init();
		if(!cd){ return 1; }

		for(auto i : t){
			curl_easy_setopt(cd, CURLOPT_URL, i.c_str());
			curl_easy_setopt(cd, CURLOPT_WRITEFUNCTION, store);
			curl_easy_setopt(cd, CURLOPT_WRITEDATA, (void*)&buffer);
			curl_easy_perform(cd);

			std::string name;
			name.resize(i.size());
			std::replace_copy(i.begin(), i.end(), name.begin(), '/',  '_');

			if(i.size() != 0){
				output.open(name);
				output << buffer;
				output.close();
			}
		}

		return 0;
	}

}
