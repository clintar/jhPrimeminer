#include "global.h"
#include "ticker.h"
//#include<intrin.h>
#include<ctime>
#include<map>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>


//curl


void csNotifyStats(){
	json_object *jsonobj = json_object_new_object();
	if(const int64_t uuid = csGetUUID()){
		json_object_object_add(jsonobj, "key", json_object_new_string(commandlineInput.csApiKey));
		json_object_object_add(jsonobj, "uuid", json_object_new_int(uuid));
		json_object_object_add(jsonobj, "blockend", json_object_new_int(workData.xptClient->blockWorkInfo.nTime));
		json_object_object_add(jsonobj, "blocknum", json_object_new_int(workData.xptClient->blockWorkInfo.height-1));
		json_object_object_add(jsonobj, "val", json_object_new_double(primeStats.fBlockShareValue));
		json_object_object_add(jsonobj, "sieves", json_object_new_double(primeStats.nSieveRounds));
		json_object_object_add(jsonobj, "candidates", json_object_new_double(primeStats.nCandidateCount));
		json_object_object_add(jsonobj, "command", json_object_new_string("notifyStats"));

		std::string url = commandlineInput.centralServer;
		std::string request = json_object_to_json_string(jsonobj);
		std::string response = curl_request(url,request,true);

		json_object *jsonresponse;
		if((jsonresponse = json_tokener_parse(response.data()))){
			if(json_object_get_boolean(json_object_object_get(jsonresponse,"error"))){
				std::cout << "Error from json: " << json_object_get_string(json_object_object_get(jsonresponse,"errormessage")) << std::endl;
				return;
			}
			//notify settings too
			csNotifySettings(true);
		}
		else{
			std::cout << "Error parsing json response" << std::endl;
		}
	}else{
		std::cout << "Error getting UUID" << std::endl;
	}
}



void csNotifySettings(bool runtime){
	json_object *jsonobj = json_object_new_object();
	if(const int64_t uuid = csGetUUID()){

		if(runtime){

		if(OldCommandlineInput.workername != commandlineInput.workername ){
			json_object_object_add(jsonobj, "workername", json_object_new_string(commandlineInput.workername));
			OldCommandlineInput.workername = commandlineInput.workername;
		}
		if(OldCommandlineInput.workerpass != commandlineInput.workerpass ){
			json_object_object_add(jsonobj, "workerpass", json_object_new_string(commandlineInput.workerpass));
			OldCommandlineInput.workerpass = commandlineInput.workerpass;
		}
		if(OldCommandlineInput.host != commandlineInput.host ){
			json_object_object_add(jsonobj, "host", json_object_new_string(commandlineInput.host));
			OldCommandlineInput.host = commandlineInput.host;
		}
		if(OldCommandlineInput.port != commandlineInput.port){
			json_object_object_add(jsonobj, "port", json_object_new_int(commandlineInput.port));
			OldCommandlineInput.port = commandlineInput.port;
		}
		if(OldCommandlineInput.numThreads != commandlineInput.numThreads){
			json_object_object_add(jsonobj, "numthreads", json_object_new_int(commandlineInput.numThreads));
			OldCommandlineInput.numThreads = commandlineInput.numThreads;
		}
		if(OldCommandlineInput.sieveSize != commandlineInput.sieveSize){
			json_object_object_add(jsonobj, "sievesize", json_object_new_int(commandlineInput.sieveSize));
			OldCommandlineInput.sieveSize = commandlineInput.sieveSize;
		}
		if(OldCommandlineInput.sievePercentage != commandlineInput.sievePercentage){
			json_object_object_add(jsonobj, "sievepercentage", json_object_new_int(commandlineInput.sievePercentage));
			OldCommandlineInput.sievePercentage = commandlineInput.sievePercentage;
		}
		if(OldCommandlineInput.roundSievePercentage != commandlineInput.roundSievePercentage){
			json_object_object_add(jsonobj, "roundsievepercentage", json_object_new_int(commandlineInput.roundSievePercentage));
			OldCommandlineInput.roundSievePercentage = commandlineInput.roundSievePercentage;
		}
		if(OldCommandlineInput.sievePrimeLimit != commandlineInput.sievePrimeLimit){
			json_object_object_add(jsonobj, "sieveprimelimit", json_object_new_int(commandlineInput.sievePrimeLimit));
			OldCommandlineInput.sievePrimeLimit = commandlineInput.sievePrimeLimit;
		}
		if(OldCommandlineInput.L1CacheElements != commandlineInput.L1CacheElements){
			json_object_object_add(jsonobj, "cacheelements", json_object_new_int(commandlineInput.L1CacheElements));
			OldCommandlineInput.L1CacheElements = commandlineInput.L1CacheElements;
		}
		if(OldCommandlineInput.primorialMultiplier != commandlineInput.primorialMultiplier){
			json_object_object_add(jsonobj, "primorialmultiplier", json_object_new_int(commandlineInput.primorialMultiplier));
			OldCommandlineInput.primorialMultiplier = commandlineInput.primorialMultiplier;
		}
		if(OldCommandlineInput.enableCacheTunning != commandlineInput.enableCacheTunning){
			json_object_object_add(jsonobj, "cachetuning", json_object_new_boolean(commandlineInput.enableCacheTunning));
			OldCommandlineInput.enableCacheTunning = commandlineInput.enableCacheTunning;
		}
		if(OldCommandlineInput.targetOverride != commandlineInput.targetOverride){
			json_object_object_add(jsonobj, "target", json_object_new_int(commandlineInput.targetOverride));
			OldCommandlineInput.targetOverride = commandlineInput.targetOverride;
		}
		if(OldCommandlineInput.targetBTOverride != commandlineInput.targetBTOverride){
			json_object_object_add(jsonobj, "bttarget", json_object_new_int(commandlineInput.targetBTOverride));
			OldCommandlineInput.targetBTOverride = commandlineInput.targetBTOverride;
		}
		if(OldCommandlineInput.initialPrimorial != commandlineInput.initialPrimorial){
			json_object_object_add(jsonobj, "initialprimorial", json_object_new_int(commandlineInput.initialPrimorial));
			OldCommandlineInput.initialPrimorial = commandlineInput.initialPrimorial;
		}
		if(OldCommandlineInput.centralServer != commandlineInput.centralServer ){
			json_object_object_add(jsonobj, "centralserver", json_object_new_string(commandlineInput.centralServer));
			OldCommandlineInput.centralServer = commandlineInput.centralServer;
		}
		if(OldCommandlineInput.centralServerPort != commandlineInput.centralServerPort){
			json_object_object_add(jsonobj, "centralserverport", json_object_new_int(commandlineInput.centralServerPort));
			OldCommandlineInput.centralServerPort = commandlineInput.centralServerPort;
		}
		if(OldCommandlineInput.sieveExtensions != commandlineInput.sieveExtensions){
			json_object_object_add(jsonobj, "sieveextensions", json_object_new_int(commandlineInput.sieveExtensions));
			OldCommandlineInput.sieveExtensions = commandlineInput.sieveExtensions;
		}
		if(OldCommandlineInput.weakSSL != commandlineInput.weakSSL){
			json_object_object_add(jsonobj, "weakssl", json_object_new_boolean(commandlineInput.weakSSL));
			OldCommandlineInput.weakSSL = commandlineInput.weakSSL;
		}
		if(OldCommandlineInput.quiet != commandlineInput.quiet){
			json_object_object_add(jsonobj, "quiet", json_object_new_boolean(commandlineInput.quiet));
			OldCommandlineInput.quiet = commandlineInput.quiet;
		}
		if(OldCommandlineInput.silent != commandlineInput.silent){
			json_object_object_add(jsonobj, "silent", json_object_new_boolean(commandlineInput.silent));
			OldCommandlineInput.silent = commandlineInput.silent;
		}
		if(OldCommandlineInput.csEnabled != commandlineInput.csEnabled){
			json_object_object_add(jsonobj, "csenabled", json_object_new_boolean(commandlineInput.csEnabled));
			OldCommandlineInput.csEnabled = commandlineInput.csEnabled;
		}
		//now old settings are updated, and all changes are built into json object
		//add json object headers:

		json_object_object_add(jsonobj, "blocknum", json_object_new_int(workData.xptClient->blockWorkInfo.height));

		}

		json_object_object_add(jsonobj, "command", json_object_new_string("syncSettings"));
		json_object_object_add(jsonobj, "key", json_object_new_string(commandlineInput.csApiKey));
		json_object_object_add(jsonobj, "uuid", json_object_new_int(uuid));
		json_object_object_add(jsonobj, "timestamp", json_object_new_int(time(0)));

		std::string url = commandlineInput.centralServer;
		std::string request = json_object_to_json_string(jsonobj);
		std::string response = curl_request(url,request,true);

		json_object *jsonresponse;
		if((jsonresponse = json_tokener_parse(response.data()))){
			if(json_object_get_boolean(json_object_object_get(jsonresponse,"error"))){
				std::cout << "Error from json: " << json_object_to_json_string(jsonresponse) << std::endl;
				return;
			}
			if(json_object_get_boolean(json_object_object_get(jsonresponse,"result"))){
				loadConfigJSON(response.data(),runtime);
			}
		}else{
			std::cout << "Error parsing json response" << std::endl;
		}
	}else{
		std::cout << "Error getting UUID" << std::endl;
	}
}


int64_t csGetUUID(){
	if(commandlineInput.csUUID==NULL){
		json_object *jsonobj = json_object_new_object();
		json_object_object_add(jsonobj, "command", json_object_new_string("getUUID"));
		json_object_object_add(jsonobj, "key", json_object_new_string(commandlineInput.csApiKey));
		std::string url = commandlineInput.centralServer;
		std::string request = json_object_to_json_string(jsonobj);
		std::string response = curl_request(url,request,false);
		json_object *jsonresponse;
		if((jsonresponse = json_tokener_parse(response.data()))){
			if(json_object_get_boolean(json_object_object_get(jsonresponse,"error"))){
				std::cout << "Error from json: " << json_object_to_json_string(jsonresponse) << std::endl;
				return 0;
			}
			if(!(commandlineInput.csUUID = json_object_get_int(json_object_object_get(jsonresponse,"uuid")))){
				std::cout << "Error getting UUID" << std::endl;
				return 0;
			}
		}else{
			std::cout << "Error parsing json response" << std::endl;
		}
	}
	return commandlineInput.csUUID;
}




void csNotifyShare(uint32 shareErrorCode, float shareValue, char* rejectReason){
	//build the stats into a nice json bundle
	json_object *jsonobj = json_object_new_object();
	if(const int64_t uuid = csGetUUID()){
		json_object_object_add(jsonobj, "key", json_object_new_string(commandlineInput.csApiKey));
		json_object_object_add(jsonobj, "uuid", json_object_new_int(uuid));
		bool bValidShare;
		if( shareErrorCode == 0 ){
			bValidShare=true;
		}else{
			bValidShare=false;
		}
		json_object_object_add(jsonobj, "validshare", json_object_new_boolean(bValidShare));
		if( rejectReason[0] != '\0' ){
			json_object_object_add(jsonobj, "rejectreason", json_object_new_string(rejectReason));
		}
		json_object_object_add(jsonobj, "thread", json_object_new_int(primeStats.lastShareThreadIndex));
		json_object_object_add(jsonobj, "diff", json_object_new_double(primeStats.lastShareDiff));
		json_object_object_add(jsonobj, "type", json_object_new_int(primeStats.lastShareType));
		json_object_object_add(jsonobj, "sharevalue", json_object_new_double(shareValue));
		json_object_object_add(jsonobj, "command", json_object_new_string("notifyShare"));

		std::string url = commandlineInput.centralServer;
		std::string request = json_object_to_json_string(jsonobj);
		std::string response = curl_request(url,request,true);

		json_object *jsonresponse;
		if(	jsonresponse = json_tokener_parse(response.data())){
			if(json_object_get_boolean(json_object_object_get(jsonresponse,"error"))){
				std::cout << "Error from json: " << json_object_get_string(json_object_object_get(jsonresponse,"errormessage")) << std::endl;
				return;
			}
		}
		else{
			std::cout << "Error parsing json response" << std::endl;
		}
	}else{
		std::cout << "Error getting UUID" << std::endl;
	}
}


bool loadConfigJSON(std::string configdata,bool runtime){
	json_object *jsonobj;
	bool die = false;
	jsonobj = json_tokener_parse(configdata.c_str());
	if(!jsonobj){
		return false;
	}
	json_object_object_foreach(jsonobj,key,val){
		if(memcmp(key, "workername", 11) == 0){commandlineInput.workername = (char *)json_object_get_string(val);}
		if(memcmp(key, "workerpass", 11) == 0){commandlineInput.workerpass = (char *)json_object_get_string(val);}
		if(memcmp(key, "host", 5) == 0){commandlineInput.host = (char *)json_object_get_string(val);}
		if(memcmp(key, "port", 5) == 0){commandlineInput.port = json_object_get_int(val);}
		if(memcmp(key, "numthreads", 11) == 0){
			int Threads = json_object_get_int(val);
			if(!runtime){
				if(Threads>0){
					commandlineInput.numThreads = Threads;
				}else{
					commandlineInput.numThreads = std::max(getNumThreads(), 1);
				}
			}
		}
		if(memcmp(key, "sievesize", 10) == 0){
			commandlineInput.sieveSize = json_object_get_int(val);
			if (runtime) nMaxSieveSize = commandlineInput.sieveSize;
		}
		if(memcmp(key, "roundsievepercentage", 21) == 0){
			commandlineInput.roundSievePercentage = json_object_get_int(val);
			if(runtime) nRoundSievePercentage = commandlineInput.roundSievePercentage;
		}
		if(memcmp(key, "sieveprimelimit", 16) == 0){commandlineInput.sievePrimeLimit = json_object_get_int(val);}
		if(memcmp(key, "cacheelements", 14) == 0){
			commandlineInput.L1CacheElements = json_object_get_int(val);
			if(runtime)	primeStats.nL1CacheElements = commandlineInput.L1CacheElements;
		}
		if(memcmp(key, "primorialmultiplier", 20) == 0){
			commandlineInput.primorialMultiplier = json_object_get_int(val);
			if (runtime){
				if(commandlineInput.primorialMultiplier>0){
					primeStats.nPrimorialMultiplier = commandlineInput.primorialMultiplier;
					bEnablenPrimorialMultiplierTuning = false;
				}else{
					bEnablenPrimorialMultiplierTuning = true;
				}
			}
		}
		if(memcmp(key, "primetuning", 12) == 0){bEnablenPrimorialMultiplierTuning = json_object_get_int(val);}
		if(memcmp(key, "target", 7) == 0){
			commandlineInput.targetOverride = json_object_get_int(val);
			if(runtime)	nOverrideTargetValue = commandlineInput.targetOverride;
		}
		if(memcmp(key, "bttarget", 9) == 0){
			commandlineInput.targetBTOverride = json_object_get_int(val);
			if(runtime) nOverrideBTTargetValue = commandlineInput.targetBTOverride;
		}
		if(memcmp(key, "initialprimorial", 17) == 0){commandlineInput.initialPrimorial = json_object_get_int(val);}
		if(memcmp(key, "centralserver", 14) == 0){commandlineInput.centralServer = (char *)json_object_get_string(val);}
		if(memcmp(key, "centralserverport", 18) == 0){commandlineInput.centralServerPort = json_object_get_int(val);}
		if(memcmp(key, "apikey", 7) == 0){commandlineInput.csApiKey = (char *)json_object_get_string(val);}
		if(memcmp(key, "sieveextensions", 16) == 0){
			commandlineInput.sieveExtensions = json_object_get_int(val);
			if(runtime)	nSieveExtensions = commandlineInput.sieveExtensions;
		}
		if(memcmp(key, "weakssl", 8) == 0){commandlineInput.weakSSL = json_object_get_boolean(val);}
		if(memcmp(key, "quiet", 6) == 0){commandlineInput.quiet = json_object_get_boolean(val);}
		if(memcmp(key, "silent", 7) == 0){commandlineInput.silent = json_object_get_boolean(val);}
		if(memcmp(key, "csenabled", 10) == 0){commandlineInput.csEnabled = json_object_get_boolean(val);}
		if(memcmp(key, "csstaticuuid", 13) == 0){commandlineInput.csStaticUUID = json_object_get_boolean(val);}
		if(memcmp(key, "uuid", 5) == 0){commandlineInput.csUUID = json_object_get_int(val);}
		if(memcmp(key, "nullsharetimeout", 17) == 0){commandlineInput.nullShareTimeout = json_object_get_int(val);}
	


		
	}

	saveConfigJSON();
	return true;
}


bool saveConfigJSON(){
	json_object *jsonobj = json_object_new_object();
	if(commandlineInput.csStaticUUID){
		json_object_object_add(jsonobj, "uuid", json_object_new_int(csGetUUID()));
		json_object_object_add(jsonobj, "csstaticuuid", json_object_new_boolean(commandlineInput.csEnabled));
	}


	json_object_object_add(jsonobj, "workername", json_object_new_string(commandlineInput.workername));
	json_object_object_add(jsonobj, "workerpass", json_object_new_string(commandlineInput.workerpass));
	json_object_object_add(jsonobj, "host", json_object_new_string(commandlineInput.host));
	json_object_object_add(jsonobj, "port", json_object_new_int(commandlineInput.port));
	json_object_object_add(jsonobj, "numthreads", json_object_new_int(commandlineInput.numThreads));
	json_object_object_add(jsonobj, "sievesize", json_object_new_int(commandlineInput.sieveSize));
	json_object_object_add(jsonobj, "sievepercentage", json_object_new_int(commandlineInput.sievePercentage));
	json_object_object_add(jsonobj, "roundsievepercentage", json_object_new_int(commandlineInput.roundSievePercentage));
	json_object_object_add(jsonobj, "sieveprimelimit", json_object_new_int(commandlineInput.sievePrimeLimit));
	json_object_object_add(jsonobj, "cacheelements", json_object_new_int(commandlineInput.L1CacheElements));
	json_object_object_add(jsonobj, "primorialmultiplier", json_object_new_int(commandlineInput.primorialMultiplier));
	json_object_object_add(jsonobj, "cachetuning", json_object_new_boolean(commandlineInput.enableCacheTunning));
	json_object_object_add(jsonobj, "target", json_object_new_int(commandlineInput.targetOverride));
	json_object_object_add(jsonobj, "bttarget", json_object_new_int(commandlineInput.targetBTOverride));
	json_object_object_add(jsonobj, "initialprimorial", json_object_new_int(commandlineInput.initialPrimorial));
	json_object_object_add(jsonobj, "centralserver", json_object_new_string(commandlineInput.centralServer));
	json_object_object_add(jsonobj, "centralserverport", json_object_new_int(commandlineInput.centralServerPort));
	json_object_object_add(jsonobj, "sieveextensions", json_object_new_int(commandlineInput.sieveExtensions));
	json_object_object_add(jsonobj, "weakssl", json_object_new_boolean(commandlineInput.weakSSL));
	json_object_object_add(jsonobj, "quiet", json_object_new_boolean(commandlineInput.quiet));
	json_object_object_add(jsonobj, "silent", json_object_new_boolean(commandlineInput.silent));
	json_object_object_add(jsonobj, "csenabled", json_object_new_boolean(commandlineInput.csEnabled));
	json_object_object_add(jsonobj, "apikey", json_object_new_string(commandlineInput.csApiKey));
	json_object_object_add(jsonobj, "nullsharetimeout", json_object_new_int(commandlineInput.nullShareTimeout));

	std::ofstream configfile(commandlineInput.configfile);
	configfile << json_object_to_json_string(jsonobj);
	configfile.close();
}




typedef struct
{ 
    void *data; 
    int body_size; 
    int body_pos; 
} postdata; 

size_t static curl_write_callback_func(void *buffer, size_t size, size_t nmemb, void *userp);

/* the function to invoke as the data recieved */
size_t static curl_write_callback_func(void *buffer, size_t size, size_t nmemb, void *userp)
{
	std::string buf = std::string(static_cast<char *>(buffer), size * nmemb);
    std::stringstream *response = static_cast<std::stringstream *>(userp);
    response->write(buf.c_str(), (std::streamsize)buf.size());

    return size * nmemb;
}



std::string curl_request(std::string url,std::string postdata,bool mode){
	CURL *curl;
	CURLcode res;
	/* to keep the response */
	std::stringstream responseData;
	struct curl_slist *headers=NULL; // init to NULL is important 
	curl_global_init(CURL_GLOBAL_DEFAULT);
	headers = curl_slist_append(headers, "Accept: application/json");  
	curl_slist_append( headers, "Content-Type: application/json");
	curl_slist_append( headers, "charsets: utf-8");
	curl = curl_easy_init();
	if(curl) {
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		//default mode = get
		if(postdata.length() > 0){
			//we have data to post, so
			if(mode){
				//mode true = PUT
				curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
			}else{
				//mode false = POST
				curl_easy_setopt(curl, CURLOPT_POST, 1L);
			}
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS,  postdata.c_str());
		}
		//	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		//   curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
		/* setting a callback function to return the data */
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_write_callback_func);
		/* passing the pointer to the response as the callback parameter */
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);
		//curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
		/* Perform the request, res will get the return code */ 
		res = curl_easy_perform(curl);
		/* Check for errors */ 
		//if(res != CURLE_OK)
		//	fprintf(stderr, "curl_easy_perform() failed: %s\n",
		//		curl_easy_strerror(res));
		/* always cleanup */ 
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	return responseData.str();
}